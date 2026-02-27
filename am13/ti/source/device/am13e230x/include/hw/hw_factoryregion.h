/*****************************************************************************

  Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/

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

#ifndef hw_factoryregion__include
#define hw_factoryregion__include

/* NOTE: This file is from MSPM33. This will be updated once the source xml is available.*/

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
* FACTORYREGION Registers
******************************************************************************/


/** @addtogroup FACTORYREGION
  @{
*/

typedef struct {
  __I  uint32_t TRACEID;                           /* !< (@ 0x60111000) Defined by TI, during ATE, based on wafer */
  __I  uint32_t DEVICEID;                          /* !< (@ 0x60111004) This is the JTAGIDCODE that comes from the Ramp
                                                      system */
  __I  uint32_t USERID;                            /* !< (@ 0x60111008) Defined by TI, depending on device spin */
  __I  uint32_t BSLPIN_UART;                       /* !< (@ 0x6011100C) BSL UART Pin Configuration */
  __I  uint32_t BSLPIN_I2C;                        /* !< (@ 0x60111010) BSL I2C Pin Configuration */
  __I  uint32_t BSLPIN_CAN;                        /* !< (@ 0x60111014) BSL CAN Pin Configuration */
  __I  uint32_t BSLPIN_INVOKE;                     /* !< (@ 0x60111018) BSL Pin Invocation Configuration */
  __I  uint32_t ROM_SRAMFLASH;                     /* !< (@ 0x6011101C) */
  __I  uint32_t PLLSTARTUP0_4_8MHZ;                /* !< (@ 0x60111020) */
  __I  uint32_t PLLSTARTUP1_4_8MHZ;                /* !< (@ 0x60111024) System PLL Paramater 1 MMR --- Data from Flash
                                                      Table Lookup */
  __I  uint32_t PLLSTARTUP0_8_16MHZ;               /* !< (@ 0x60111028) */
  __I  uint32_t PLLSTARTUP1_8_16MHZ;               /* !< (@ 0x6011102C) System PLL Paramater 1 MMR --- Data from Flash
                                                      Table Lookup */
  __I  uint32_t PLLSTARTUP0_16_32MHZ;              /* !< (@ 0x60111030) */
  __I  uint32_t PLLSTARTUP1_16_32MHZ;              /* !< (@ 0x60111034) System PLL Paramater 1 MMR --- Data from Flash
                                                      Table Lookup */
  __I  uint32_t PLLSTARTUP0_32_48MHZ;              /* !< (@ 0x60111038) */
  __I  uint32_t PLLSTARTUP1_32_48MHZ;              /* !< (@ 0x6011103C) System PLL Paramater 1 MMR --- Data from Flash
                                                      Table Lookup */
  __I  uint32_t TEMP_SENSE0;                       /* !< (@ 0x60111040) Temperature sensor room temperature calibration
                                                      code. This is ADC conversion results of temperature sensor output
                                                      voltage.  Included in BOOTCRC calculation. */
  __I  uint32_t BOOTCRC;                           /* !< (@ 0x60111044) BOOTCRC records the 32-bit CRC of all locations in
                                                      OPEN including reserved locations. */
  __I  uint32_t RESERVED00;                        /* !< (@ 0x60111048) */
  __I  uint32_t ROM_VERSION;                       /* !< (@ 0x6011104C) */
  __I  uint32_t ROM_INM_VERSION;                   /* !< (@ 0x60111050) */
  __I  uint32_t SYSPLLPARAM2;                      /* !< (@ 0x60111054) */
  __I  uint32_t SYSPLLLDOCTL;                      /* !< (@ 0x60111058) */
  __I  uint32_t SYSPLLLDOPROG;                     /* !< (@ 0x6011105C) */
  __I  uint32_t EXTREF_MP3;                        /* !< (@ 0x60111060) External Reference MP3 Temp Sense */
  __I  uint32_t INTREF_MP3;                        /* !< (@ 0x60111064) Internal Refernce Temp Sene */
  __I  uint32_t TSCODE_MP1;                        /* !< (@ 0x60111068) Tempsense Code MP1 */
  __I  uint32_t TSCODE_MP3;                        /* !< (@ 0x6011106C) Tempsense code MP3 */
  __I  uint32_t TSTEMP;                            /* !< (@ 0x60111070) Temperature sense TEMP */
  __I  uint32_t SRAMFLASH;                         /* !< (@ 0x60111074) Number of banks , sram size and flash size */
  __I  uint32_t RESERVED07;                        /* !< (@ 0x60111078) */
  __I  uint32_t RESERVED08;                        /* !< (@ 0x6011107C) */
  __I  uint32_t RESERVED13;                        /* !< (@ 0x6011107C) */
  __I  uint32_t RESERVED14;                        /* !< (@ 0x60111080) */
} FACTORYREGION_Regs;

/*@}*/ /* end of group FACTORYREGION */



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* FACTORYREGION Register Control Bits
******************************************************************************/

/* FACTORYREGION_TRACEID Bits */
/* FACTORYREGION_TRACEID[DATA] Bits */
#define FACTORYREGION_TRACEID_DATA_OFS           (0)                             /* !< DATA Offset */
#define FACTORYREGION_TRACEID_DATA_MASK          ((uint32_t)0xFFFFFFFFU)

/* FACTORYREGION_DEVICEID Bits */
/* FACTORYREGION_DEVICEID[VERSION] Bits */
#define FACTORYREGION_DEVICEID_VERSION_OFS       (28)                            /* !< VERSION Offset */
#define FACTORYREGION_DEVICEID_VERSION_MASK      ((uint32_t)0xF0000000U)         /* !< Revision of the device. This field
                                                                                    should change each time that the
                                                                                    logic or mask set of the device is
                                                                                    revised. */
/* FACTORYREGION_DEVICEID[PARTNUM] Bits */
#define FACTORYREGION_DEVICEID_PARTNUM_OFS       (12)                            /* !< PARTNUM Offset */
#define FACTORYREGION_DEVICEID_PARTNUM_MASK      ((uint32_t)0x0FFFF000U)         /* !< Part number of the device. */
/* FACTORYREGION_DEVICEID[MANUFACTURER] Bits */
#define FACTORYREGION_DEVICEID_MANUFACTURER_OFS  (1)                             /* !< MANUFACTURER Offset */
#define FACTORYREGION_DEVICEID_MANUFACTURER_MASK ((uint32_t)0x00000FFEU)         /* !< TI's JEDEC bank and company code,
                                                                                    which is: 00000010111b */
/* FACTORYREGION_DEVICEID[ALWAYS_1] Bits */
#define FACTORYREGION_DEVICEID_ALWAYS_1_OFS      (0)                             /* !< ALWAYS_1 Offset */
#define FACTORYREGION_DEVICEID_ALWAYS_1_MASK     ((uint32_t)0x00000001U)         /* !< This is always 1 */

/* FACTORYREGION_USERID Bits */
/* FACTORYREGION_USERID[PART] Bits */
#define FACTORYREGION_USERID_PART_OFS            (0)                             /* !< PART Offset */
#define FACTORYREGION_USERID_PART_MASK           ((uint32_t)0x0000FFFFU)         /* !< Bit pattern that uniquely
                                                                                    identifying a part. This is used to
                                                                                    identify the specific part based on
                                                                                    the die identified in
                                                                                    DEVICEID.device. This number shall be
                                                                                    selected at random among the
                                                                                    remaining numbers for DEVICEID.device
                                                                                    such that the order of creation
                                                                                    cannot be inferred by the number.
                                                                                    This value does not encode the part
                                                                                    number directly. */
/* FACTORYREGION_USERID[VARIANT] Bits */
#define FACTORYREGION_USERID_VARIANT_OFS         (16)                            /* !< VARIANT Offset */
#define FACTORYREGION_USERID_VARIANT_MASK        ((uint32_t)0x00FF0000U)         /* !< Bit pattern uniquely identifying a
                                                                                    variant of a part. This is used to
                                                                                    indicate memory or package variations
                                                                                    of the same part number. This number
                                                                                    shall be selected at random among the
                                                                                    remaining numbers for the relevant
                                                                                    combination of IDCODE.device and
                                                                                    USERCODE.part such that the order of
                                                                                    creation cannot be inferred by the
                                                                                    number. The variant number does not
                                                                                    encode specifics of the variant
                                                                                    directly. */
/* FACTORYREGION_USERID[MINORREV] Bits */
#define FACTORYREGION_USERID_MINORREV_OFS        (24)                            /* !< MINORREV Offset */
#define FACTORYREGION_USERID_MINORREV_MASK       ((uint32_t)0x0F000000U)         /* !< Monotonic increasing value
                                                                                    indicating a new revision of the SKU
                                                                                    that preserves compatibility with
                                                                                    lesser minorrev values. New
                                                                                    capability may be introduced such
                                                                                    that lesser minorrev numbers may not
                                                                                    be compatible with greater if the new
                                                                                    capability is used. */
/* FACTORYREGION_USERID[MAJORREV] Bits */
#define FACTORYREGION_USERID_MAJORREV_OFS        (28)                            /* !< MAJORREV Offset */
#define FACTORYREGION_USERID_MAJORREV_MASK       ((uint32_t)0x70000000U)         /* !< Monotonic increasing value
                                                                                    indicating a new revision of the SKU
                                                                                    significant enough that users of the
                                                                                    device may have to revise PCB or or
                                                                                    software design */
/* FACTORYREGION_USERID[START] Bits */
#define FACTORYREGION_USERID_START_OFS           (31)                            /* !< START Offset */
#define FACTORYREGION_USERID_START_MASK          ((uint32_t)0x80000000U)

/* FACTORYREGION_BSLPIN_UART Bits */
/* FACTORYREGION_BSLPIN_UART[UART_RXD_PAD] Bits */
#define FACTORYREGION_BSLPIN_UART_UART_RXD_PAD_OFS (0)                             /* !< UART_RXD_PAD Offset */
#define FACTORYREGION_BSLPIN_UART_UART_RXD_PAD_MASK ((uint32_t)0x000000FFU)         /* !< UART RXD Pad used by BSL */
/* FACTORYREGION_BSLPIN_UART[UART_RXD_PF] Bits */
#define FACTORYREGION_BSLPIN_UART_UART_RXD_PF_OFS (8)                             /* !< UART_RXD_PF Offset */
#define FACTORYREGION_BSLPIN_UART_UART_RXD_PF_MASK ((uint32_t)0x0000FF00U)         /* !< UART RXD Pin Function Selection
                                                                                    Value */
/* FACTORYREGION_BSLPIN_UART[UART_TXD_PAD] Bits */
#define FACTORYREGION_BSLPIN_UART_UART_TXD_PAD_OFS (16)                            /* !< UART_TXD_PAD Offset */
#define FACTORYREGION_BSLPIN_UART_UART_TXD_PAD_MASK ((uint32_t)0x00FF0000U)         /* !< UART TXD Pin used by BSL */
/* FACTORYREGION_BSLPIN_UART[UART_TXD_PF] Bits */
#define FACTORYREGION_BSLPIN_UART_UART_TXD_PF_OFS (24)                            /* !< UART_TXD_PF Offset */
#define FACTORYREGION_BSLPIN_UART_UART_TXD_PF_MASK ((uint32_t)0xFF000000U)         /* !< UART TXD Pin Function Selection
                                                                                    Value */

/* FACTORYREGION_BSLPIN_I2C Bits */
/* FACTORYREGION_BSLPIN_I2C[I2C_SDA_PAD] Bits */
#define FACTORYREGION_BSLPIN_I2C_I2C_SDA_PAD_OFS (0)                             /* !< I2C_SDA_PAD Offset */
#define FACTORYREGION_BSLPIN_I2C_I2C_SDA_PAD_MASK ((uint32_t)0x000000FFU)         /* !< I2C SDA Pin used by BSL */
/* FACTORYREGION_BSLPIN_I2C[I2C_SDA_PF] Bits */
#define FACTORYREGION_BSLPIN_I2C_I2C_SDA_PF_OFS  (8)                             /* !< I2C_SDA_PF Offset */
#define FACTORYREGION_BSLPIN_I2C_I2C_SDA_PF_MASK ((uint32_t)0x0000FF00U)         /* !< I2C SDA Pin Function Selection
                                                                                    Value */
/* FACTORYREGION_BSLPIN_I2C[I2C_SCL_PAD] Bits */
#define FACTORYREGION_BSLPIN_I2C_I2C_SCL_PAD_OFS (16)                            /* !< I2C_SCL_PAD Offset */
#define FACTORYREGION_BSLPIN_I2C_I2C_SCL_PAD_MASK ((uint32_t)0x00FF0000U)         /* !< I2C SCL Pin used by BSL */
/* FACTORYREGION_BSLPIN_I2C[I2C_SCL_PF] Bits */
#define FACTORYREGION_BSLPIN_I2C_I2C_SCL_PF_OFS  (24)                            /* !< I2C_SCL_PF Offset */
#define FACTORYREGION_BSLPIN_I2C_I2C_SCL_PF_MASK ((uint32_t)0xFF000000U)         /* !< I2C SCL Pin Function Selection
                                                                                    Value */

/* FACTORYREGION_BSLPIN_CAN Bits */
/* FACTORYREGION_BSLPIN_CAN[CAN_RX_PAD] Bits */
#define FACTORYREGION_BSLPIN_CAN_CAN_RX_PAD_OFS  (0)                             /* !< CAN_RX_PAD Offset */
#define FACTORYREGION_BSLPIN_CAN_CAN_RX_PAD_MASK ((uint32_t)0x000000FFU)         /* !< MCAN RX Pin used by BSL */
/* FACTORYREGION_BSLPIN_CAN[CAN_RX_PF] Bits */
#define FACTORYREGION_BSLPIN_CAN_CAN_RX_PF_OFS   (8)                             /* !< CAN_RX_PF Offset */
#define FACTORYREGION_BSLPIN_CAN_CAN_RX_PF_MASK  ((uint32_t)0x0000FF00U)         /* !< MCAN RX Pin Function Selection
                                                                                    Value */
/* FACTORYREGION_BSLPIN_CAN[CAN_TX_PAD] Bits */
#define FACTORYREGION_BSLPIN_CAN_CAN_TX_PAD_OFS  (16)                            /* !< CAN_TX_PAD Offset */
#define FACTORYREGION_BSLPIN_CAN_CAN_TX_PAD_MASK ((uint32_t)0x00FF0000U)         /* !< MCAN TX Pin used by BSL */
/* FACTORYREGION_BSLPIN_CAN[CAN_TX_PF] Bits */
#define FACTORYREGION_BSLPIN_CAN_CAN_TX_PF_OFS   (24)                            /* !< CAN_TX_PF Offset */
#define FACTORYREGION_BSLPIN_CAN_CAN_TX_PF_MASK  ((uint32_t)0xFF000000U)         /* !< MCAN TX Pin Function Selection
                                                                                    Value */

/* FACTORYREGION_BSLPIN_INVOKE Bits */
/* FACTORYREGION_BSLPIN_INVOKE[BSL_PAD] Bits */
#define FACTORYREGION_BSLPIN_INVOKE_BSL_PAD_OFS  (0)                             /* !< BSL_PAD Offset */
#define FACTORYREGION_BSLPIN_INVOKE_BSL_PAD_MASK ((uint32_t)0x0000007FU)         /* !< BSL Invocation Pin Number */
/* FACTORYREGION_BSLPIN_INVOKE[GPIO_LEVEL] Bits */
#define FACTORYREGION_BSLPIN_INVOKE_GPIO_LEVEL_OFS (7)                             /* !< GPIO_LEVEL Offset */
#define FACTORYREGION_BSLPIN_INVOKE_GPIO_LEVEL_MASK ((uint32_t)0x00000080U)         /* !< GPIO Level Configuration for BSL
                                                                                    Invocation */
/* FACTORYREGION_BSLPIN_INVOKE[GPIO_PIN_SEL] Bits */
#define FACTORYREGION_BSLPIN_INVOKE_GPIO_PIN_SEL_OFS (8)                             /* !< GPIO_PIN_SEL Offset */
#define FACTORYREGION_BSLPIN_INVOKE_GPIO_PIN_SEL_MASK ((uint32_t)0x00001F00U)         /* !< GPIO Pin Number in GPIO Module */
/* FACTORYREGION_BSLPIN_INVOKE[GPIO_REG_SEL] Bits */
#define FACTORYREGION_BSLPIN_INVOKE_GPIO_REG_SEL_OFS (13)                            /* !< GPIO_REG_SEL Offset */
#define FACTORYREGION_BSLPIN_INVOKE_GPIO_REG_SEL_MASK ((uint32_t)0x00006000U)         /* !< GPIO Module Selection */

/* FACTORYREGION_ROM_SRAMFLASH Bits */
/* FACTORYREGION_ROM_SRAMFLASH[MAINFLASH_SZ] Bits */
#define FACTORYREGION_ROM_SRAMFLASH_MAINFLASH_SZ_OFS (0)                             /* !< MAINFLASH_SZ Offset */
#define FACTORYREGION_ROM_SRAMFLASH_MAINFLASH_SZ_MASK ((uint32_t)0x00000FFFU)         /* !< The encoding of the field is that
                                                                                    the value of the field is an integer
                                                                                    to be interpreted as number of KBs.
                                                                                    For eg: if the value of the field id
                                                                                    4, then it is 4KB, if the value is
                                                                                    32, then 32KB, and so on. */
/* FACTORYREGION_ROM_SRAMFLASH[SRAM_SZ] Bits */
#define FACTORYREGION_ROM_SRAMFLASH_SRAM_SZ_OFS  (16)                            /* !< SRAM_SZ Offset */
#define FACTORYREGION_ROM_SRAMFLASH_SRAM_SZ_MASK ((uint32_t)0x03FF0000U)         /* !< The encoding of the field is that
                                                                                    the value of the field is an integer
                                                                                    to be interpreted as number of KBs.
                                                                                    For eg: if the value of the field id
                                                                                    4, then it is 4KB, if the value is
                                                                                    32, then 32KB, and so on. */
/* FACTORYREGION_ROM_SRAMFLASH[MAINNUMBANKS] Bits */
#define FACTORYREGION_ROM_SRAMFLASH_MAINNUMBANKS_OFS (12)                            /* !< MAINNUMBANKS Offset */
#define FACTORYREGION_ROM_SRAMFLASH_MAINNUMBANKS_MASK ((uint32_t)0x00003000U)         /* !< Defines the number of main flash
                                                                                    banks */
/* FACTORYREGION_ROM_SRAMFLASH[DATAFLASH_SZ] Bits */
#define FACTORYREGION_ROM_SRAMFLASH_DATAFLASH_SZ_OFS (26)                            /* !< DATAFLASH_SZ Offset */
#define FACTORYREGION_ROM_SRAMFLASH_DATAFLASH_SZ_MASK ((uint32_t)0xFC000000U)         /* !< The encoding of the field is that
                                                                                    the value of the field is an integer
                                                                                    to be interpreted as number of KBs.
                                                                                    For eg: if the value of the field id
                                                                                    4, then it is 4KB, if the value is
                                                                                    32, then 32KB, and so on. */

/* FACTORYREGION_PLLSTARTUP0_4_8MHZ Bits */
/* FACTORYREGION_PLLSTARTUP0_4_8MHZ[STARTTIME] Bits */
#define FACTORYREGION_PLLSTARTUP0_4_8MHZ_STARTTIME_OFS (0)                             /* !< STARTTIME Offset */
#define FACTORYREGION_PLLSTARTUP0_4_8MHZ_STARTTIME_MASK ((uint32_t)0x0000003FU)         /* !< Startup time from Enable to Locked
                                                                                    Clock in resolution of 1usec */
/* FACTORYREGION_PLLSTARTUP0_4_8MHZ[STARTTIMELP] Bits */
#define FACTORYREGION_PLLSTARTUP0_4_8MHZ_STARTTIMELP_OFS (8)                             /* !< STARTTIMELP Offset */
#define FACTORYREGION_PLLSTARTUP0_4_8MHZ_STARTTIMELP_MASK ((uint32_t)0x00003F00U)         /* !< Startup time from Low Power Exit to
                                                                                    Locked Clock in resolution of 1usec */
/* FACTORYREGION_PLLSTARTUP0_4_8MHZ[CPCURRENT] Bits */
#define FACTORYREGION_PLLSTARTUP0_4_8MHZ_CPCURRENT_OFS (16)                            /* !< CPCURRENT Offset */
#define FACTORYREGION_PLLSTARTUP0_4_8MHZ_CPCURRENT_MASK ((uint32_t)0x003F0000U)         /* !< Charge Pump Current */
/* FACTORYREGION_PLLSTARTUP0_4_8MHZ[CAPBVAL] Bits */
#define FACTORYREGION_PLLSTARTUP0_4_8MHZ_CAPBVAL_OFS (24)                            /* !< CAPBVAL Offset */
#define FACTORYREGION_PLLSTARTUP0_4_8MHZ_CAPBVAL_MASK ((uint32_t)0x1F000000U)         /* !< Override Value for Cap B */
/* FACTORYREGION_PLLSTARTUP0_4_8MHZ[CAPBOVERRIDE] Bits */
#define FACTORYREGION_PLLSTARTUP0_4_8MHZ_CAPBOVERRIDE_OFS (31)                            /* !< CAPBOVERRIDE Offset */
#define FACTORYREGION_PLLSTARTUP0_4_8MHZ_CAPBOVERRIDE_MASK ((uint32_t)0x80000000U)         /* !< Override Enable For Cap B */
#define FACTORYREGION_PLLSTARTUP0_4_8MHZ_CAPBOVERRIDE_DISABLE ((uint32_t)0x00000000U)
#define FACTORYREGION_PLLSTARTUP0_4_8MHZ_CAPBOVERRIDE_ENABLE ((uint32_t)0x80000000U)

/* FACTORYREGION_PLLSTARTUP1_4_8MHZ Bits */
/* FACTORYREGION_PLLSTARTUP1_4_8MHZ[LPFCAPA] Bits */
#define FACTORYREGION_PLLSTARTUP1_4_8MHZ_LPFCAPA_OFS (0)                             /* !< LPFCAPA Offset */
#define FACTORYREGION_PLLSTARTUP1_4_8MHZ_LPFCAPA_MASK ((uint32_t)0x0000001FU)         /* !< Loop Filter Cap A */
/* FACTORYREGION_PLLSTARTUP1_4_8MHZ[LPFRESA] Bits */
#define FACTORYREGION_PLLSTARTUP1_4_8MHZ_LPFRESA_OFS (8)                             /* !< LPFRESA Offset */
#define FACTORYREGION_PLLSTARTUP1_4_8MHZ_LPFRESA_MASK ((uint32_t)0x0003FF00U)         /* !< Loop Filter Res A */
/* FACTORYREGION_PLLSTARTUP1_4_8MHZ[LPFRESC] Bits */
#define FACTORYREGION_PLLSTARTUP1_4_8MHZ_LPFRESC_OFS (24)                            /* !< LPFRESC Offset */
#define FACTORYREGION_PLLSTARTUP1_4_8MHZ_LPFRESC_MASK ((uint32_t)0xFF000000U)         /* !< Loop Filter Res C */

/* FACTORYREGION_PLLSTARTUP0_8_16MHZ Bits */
/* FACTORYREGION_PLLSTARTUP0_8_16MHZ[STARTTIME] Bits */
#define FACTORYREGION_PLLSTARTUP0_8_16MHZ_STARTTIME_OFS (0)                             /* !< STARTTIME Offset */
#define FACTORYREGION_PLLSTARTUP0_8_16MHZ_STARTTIME_MASK ((uint32_t)0x0000003FU)         /* !< Startup time from Enable to Locked
                                                                                    Clock in resolution of 1usec */
/* FACTORYREGION_PLLSTARTUP0_8_16MHZ[STARTTIMELP] Bits */
#define FACTORYREGION_PLLSTARTUP0_8_16MHZ_STARTTIMELP_OFS (8)                             /* !< STARTTIMELP Offset */
#define FACTORYREGION_PLLSTARTUP0_8_16MHZ_STARTTIMELP_MASK ((uint32_t)0x00003F00U)         /* !< Startup time from Low Power Exit to
                                                                                    Locked Clock in resolution of 1usec */
/* FACTORYREGION_PLLSTARTUP0_8_16MHZ[CPCURRENT] Bits */
#define FACTORYREGION_PLLSTARTUP0_8_16MHZ_CPCURRENT_OFS (16)                            /* !< CPCURRENT Offset */
#define FACTORYREGION_PLLSTARTUP0_8_16MHZ_CPCURRENT_MASK ((uint32_t)0x003F0000U)         /* !< Charge Pump Current */
/* FACTORYREGION_PLLSTARTUP0_8_16MHZ[CAPBVAL] Bits */
#define FACTORYREGION_PLLSTARTUP0_8_16MHZ_CAPBVAL_OFS (24)                            /* !< CAPBVAL Offset */
#define FACTORYREGION_PLLSTARTUP0_8_16MHZ_CAPBVAL_MASK ((uint32_t)0x1F000000U)         /* !< Override Value for Cap B */
/* FACTORYREGION_PLLSTARTUP0_8_16MHZ[CAPBOVERRIDE] Bits */
#define FACTORYREGION_PLLSTARTUP0_8_16MHZ_CAPBOVERRIDE_OFS (31)                            /* !< CAPBOVERRIDE Offset */
#define FACTORYREGION_PLLSTARTUP0_8_16MHZ_CAPBOVERRIDE_MASK ((uint32_t)0x80000000U)         /* !< Override Enable For Cap B */
#define FACTORYREGION_PLLSTARTUP0_8_16MHZ_CAPBOVERRIDE_DISABLE ((uint32_t)0x00000000U)
#define FACTORYREGION_PLLSTARTUP0_8_16MHZ_CAPBOVERRIDE_ENABLE ((uint32_t)0x80000000U)

/* FACTORYREGION_PLLSTARTUP1_8_16MHZ Bits */
/* FACTORYREGION_PLLSTARTUP1_8_16MHZ[LPFCAPA] Bits */
#define FACTORYREGION_PLLSTARTUP1_8_16MHZ_LPFCAPA_OFS (0)                             /* !< LPFCAPA Offset */
#define FACTORYREGION_PLLSTARTUP1_8_16MHZ_LPFCAPA_MASK ((uint32_t)0x0000001FU)         /* !< Loop Filter Cap A */
/* FACTORYREGION_PLLSTARTUP1_8_16MHZ[LPFRESA] Bits */
#define FACTORYREGION_PLLSTARTUP1_8_16MHZ_LPFRESA_OFS (8)                             /* !< LPFRESA Offset */
#define FACTORYREGION_PLLSTARTUP1_8_16MHZ_LPFRESA_MASK ((uint32_t)0x0003FF00U)         /* !< Loop Filter Res A */
/* FACTORYREGION_PLLSTARTUP1_8_16MHZ[LPFRESC] Bits */
#define FACTORYREGION_PLLSTARTUP1_8_16MHZ_LPFRESC_OFS (24)                            /* !< LPFRESC Offset */
#define FACTORYREGION_PLLSTARTUP1_8_16MHZ_LPFRESC_MASK ((uint32_t)0xFF000000U)         /* !< Loop Filter Res C */

/* FACTORYREGION_PLLSTARTUP0_16_32MHZ Bits */
/* FACTORYREGION_PLLSTARTUP0_16_32MHZ[STARTTIME] Bits */
#define FACTORYREGION_PLLSTARTUP0_16_32MHZ_STARTTIME_OFS (0)                             /* !< STARTTIME Offset */
#define FACTORYREGION_PLLSTARTUP0_16_32MHZ_STARTTIME_MASK ((uint32_t)0x0000003FU)         /* !< Startup time from Enable to Locked
                                                                                    Clock in resolution of 1usec */
/* FACTORYREGION_PLLSTARTUP0_16_32MHZ[STARTTIMELP] Bits */
#define FACTORYREGION_PLLSTARTUP0_16_32MHZ_STARTTIMELP_OFS (8)                             /* !< STARTTIMELP Offset */
#define FACTORYREGION_PLLSTARTUP0_16_32MHZ_STARTTIMELP_MASK ((uint32_t)0x00003F00U)         /* !< Startup time from Low Power Exit to
                                                                                    Locked Clock in resolution of 1usec */
/* FACTORYREGION_PLLSTARTUP0_16_32MHZ[CPCURRENT] Bits */
#define FACTORYREGION_PLLSTARTUP0_16_32MHZ_CPCURRENT_OFS (16)                            /* !< CPCURRENT Offset */
#define FACTORYREGION_PLLSTARTUP0_16_32MHZ_CPCURRENT_MASK ((uint32_t)0x003F0000U)         /* !< Charge Pump Current */
/* FACTORYREGION_PLLSTARTUP0_16_32MHZ[CAPBVAL] Bits */
#define FACTORYREGION_PLLSTARTUP0_16_32MHZ_CAPBVAL_OFS (24)                            /* !< CAPBVAL Offset */
#define FACTORYREGION_PLLSTARTUP0_16_32MHZ_CAPBVAL_MASK ((uint32_t)0x1F000000U)         /* !< Override Value for Cap B */
/* FACTORYREGION_PLLSTARTUP0_16_32MHZ[CAPBOVERRIDE] Bits */
#define FACTORYREGION_PLLSTARTUP0_16_32MHZ_CAPBOVERRIDE_OFS (31)                            /* !< CAPBOVERRIDE Offset */
#define FACTORYREGION_PLLSTARTUP0_16_32MHZ_CAPBOVERRIDE_MASK ((uint32_t)0x80000000U)         /* !< Override Enable For Cap B */
#define FACTORYREGION_PLLSTARTUP0_16_32MHZ_CAPBOVERRIDE_DISABLE ((uint32_t)0x00000000U)
#define FACTORYREGION_PLLSTARTUP0_16_32MHZ_CAPBOVERRIDE_ENABLE ((uint32_t)0x80000000U)

/* FACTORYREGION_PLLSTARTUP1_16_32MHZ Bits */
/* FACTORYREGION_PLLSTARTUP1_16_32MHZ[LPFCAPA] Bits */
#define FACTORYREGION_PLLSTARTUP1_16_32MHZ_LPFCAPA_OFS (0)                             /* !< LPFCAPA Offset */
#define FACTORYREGION_PLLSTARTUP1_16_32MHZ_LPFCAPA_MASK ((uint32_t)0x0000001FU)         /* !< Loop Filter Cap A */
/* FACTORYREGION_PLLSTARTUP1_16_32MHZ[LPFRESA] Bits */
#define FACTORYREGION_PLLSTARTUP1_16_32MHZ_LPFRESA_OFS (8)                             /* !< LPFRESA Offset */
#define FACTORYREGION_PLLSTARTUP1_16_32MHZ_LPFRESA_MASK ((uint32_t)0x0003FF00U)         /* !< Loop Filter Res A */
/* FACTORYREGION_PLLSTARTUP1_16_32MHZ[LPFRESC] Bits */
#define FACTORYREGION_PLLSTARTUP1_16_32MHZ_LPFRESC_OFS (24)                            /* !< LPFRESC Offset */
#define FACTORYREGION_PLLSTARTUP1_16_32MHZ_LPFRESC_MASK ((uint32_t)0xFF000000U)         /* !< Loop Filter Res C */

/* FACTORYREGION_PLLSTARTUP0_32_48MHZ Bits */
/* FACTORYREGION_PLLSTARTUP0_32_48MHZ[STARTTIME] Bits */
#define FACTORYREGION_PLLSTARTUP0_32_48MHZ_STARTTIME_OFS (0)                             /* !< STARTTIME Offset */
#define FACTORYREGION_PLLSTARTUP0_32_48MHZ_STARTTIME_MASK ((uint32_t)0x0000003FU)         /* !< Startup time from Enable to Locked
                                                                                    Clock in resolution of 1usec */
/* FACTORYREGION_PLLSTARTUP0_32_48MHZ[STARTTIMELP] Bits */
#define FACTORYREGION_PLLSTARTUP0_32_48MHZ_STARTTIMELP_OFS (8)                             /* !< STARTTIMELP Offset */
#define FACTORYREGION_PLLSTARTUP0_32_48MHZ_STARTTIMELP_MASK ((uint32_t)0x00003F00U)         /* !< Startup time from Low Power Exit to
                                                                                    Locked Clock in resolution of 1usec */
/* FACTORYREGION_PLLSTARTUP0_32_48MHZ[CPCURRENT] Bits */
#define FACTORYREGION_PLLSTARTUP0_32_48MHZ_CPCURRENT_OFS (16)                            /* !< CPCURRENT Offset */
#define FACTORYREGION_PLLSTARTUP0_32_48MHZ_CPCURRENT_MASK ((uint32_t)0x003F0000U)         /* !< Charge Pump Current */
/* FACTORYREGION_PLLSTARTUP0_32_48MHZ[CAPBVAL] Bits */
#define FACTORYREGION_PLLSTARTUP0_32_48MHZ_CAPBVAL_OFS (24)                            /* !< CAPBVAL Offset */
#define FACTORYREGION_PLLSTARTUP0_32_48MHZ_CAPBVAL_MASK ((uint32_t)0x1F000000U)         /* !< Override Value for Cap B */
/* FACTORYREGION_PLLSTARTUP0_32_48MHZ[CAPBOVERRIDE] Bits */
#define FACTORYREGION_PLLSTARTUP0_32_48MHZ_CAPBOVERRIDE_OFS (31)                            /* !< CAPBOVERRIDE Offset */
#define FACTORYREGION_PLLSTARTUP0_32_48MHZ_CAPBOVERRIDE_MASK ((uint32_t)0x80000000U)         /* !< Override Enable For Cap B */
#define FACTORYREGION_PLLSTARTUP0_32_48MHZ_CAPBOVERRIDE_DISABLE ((uint32_t)0x00000000U)
#define FACTORYREGION_PLLSTARTUP0_32_48MHZ_CAPBOVERRIDE_ENABLE ((uint32_t)0x80000000U)

/* FACTORYREGION_PLLSTARTUP1_32_48MHZ Bits */
/* FACTORYREGION_PLLSTARTUP1_32_48MHZ[LPFCAPA] Bits */
#define FACTORYREGION_PLLSTARTUP1_32_48MHZ_LPFCAPA_OFS (0)                             /* !< LPFCAPA Offset */
#define FACTORYREGION_PLLSTARTUP1_32_48MHZ_LPFCAPA_MASK ((uint32_t)0x0000001FU)         /* !< Loop Filter Cap A */
/* FACTORYREGION_PLLSTARTUP1_32_48MHZ[LPFRESA] Bits */
#define FACTORYREGION_PLLSTARTUP1_32_48MHZ_LPFRESA_OFS (8)                             /* !< LPFRESA Offset */
#define FACTORYREGION_PLLSTARTUP1_32_48MHZ_LPFRESA_MASK ((uint32_t)0x0003FF00U)         /* !< Loop Filter Res A */
/* FACTORYREGION_PLLSTARTUP1_32_48MHZ[LPFRESC] Bits */
#define FACTORYREGION_PLLSTARTUP1_32_48MHZ_LPFRESC_OFS (24)                            /* !< LPFRESC Offset */
#define FACTORYREGION_PLLSTARTUP1_32_48MHZ_LPFRESC_MASK ((uint32_t)0xFF000000U)         /* !< Loop Filter Res C */

/* FACTORYREGION_TEMP_SENSE0 Bits */
/* FACTORYREGION_TEMP_SENSE0[DATA] Bits */
#define FACTORYREGION_TEMP_SENSE0_DATA_OFS       (0)                             /* !< DATA Offset */
#define FACTORYREGION_TEMP_SENSE0_DATA_MASK      ((uint32_t)0xFFFFFFFFU)

/* FACTORYREGION_BOOTCRC Bits */
/* FACTORYREGION_BOOTCRC[DATA] Bits */
#define FACTORYREGION_BOOTCRC_DATA_OFS           (0)                             /* !< DATA Offset */
#define FACTORYREGION_BOOTCRC_DATA_MASK          ((uint32_t)0xFFFFFFFFU)

/* FACTORYREGION_ROM_VERSION Bits */
/* FACTORYREGION_ROM_VERSION[ROM_PATCH_VER] Bits */
#define FACTORYREGION_ROM_VERSION_ROM_PATCH_VER_OFS (0)                             /* !< ROM_PATCH_VER Offset */
#define FACTORYREGION_ROM_VERSION_ROM_PATCH_VER_MASK ((uint32_t)0x000000FFU)
/* FACTORYREGION_ROM_VERSION[ROM_MINOR_VER] Bits */
#define FACTORYREGION_ROM_VERSION_ROM_MINOR_VER_OFS (8)                             /* !< ROM_MINOR_VER Offset */
#define FACTORYREGION_ROM_VERSION_ROM_MINOR_VER_MASK ((uint32_t)0x0000FF00U)
/* FACTORYREGION_ROM_VERSION[ROM_MAJOR_VER] Bits */
#define FACTORYREGION_ROM_VERSION_ROM_MAJOR_VER_OFS (16)                            /* !< ROM_MAJOR_VER Offset */
#define FACTORYREGION_ROM_VERSION_ROM_MAJOR_VER_MASK ((uint32_t)0x00FF0000U)
/* FACTORYREGION_ROM_VERSION[ROM_PG_VER] Bits */
#define FACTORYREGION_ROM_VERSION_ROM_PG_VER_OFS (24)                            /* !< ROM_PG_VER Offset */
#define FACTORYREGION_ROM_VERSION_ROM_PG_VER_MASK ((uint32_t)0xFF000000U)

/* FACTORYREGION_ROM_INM_VERSION Bits */
/* FACTORYREGION_ROM_INM_VERSION[ROM_INM_PATCH_VER] Bits */
#define FACTORYREGION_ROM_INM_VERSION_ROM_INM_PATCH_VER_OFS (0)                             /* !< ROM_INM_PATCH_VER Offset */
#define FACTORYREGION_ROM_INM_VERSION_ROM_INM_PATCH_VER_MASK ((uint32_t)0x000000FFU)
/* FACTORYREGION_ROM_INM_VERSION[ROM_INM_MINOR_VER] Bits */
#define FACTORYREGION_ROM_INM_VERSION_ROM_INM_MINOR_VER_OFS (8)                             /* !< ROM_INM_MINOR_VER Offset */
#define FACTORYREGION_ROM_INM_VERSION_ROM_INM_MINOR_VER_MASK ((uint32_t)0x0000FF00U)
/* FACTORYREGION_ROM_INM_VERSION[ROM_INM_MAJOR_VER] Bits */
#define FACTORYREGION_ROM_INM_VERSION_ROM_INM_MAJOR_VER_OFS (16)                            /* !< ROM_INM_MAJOR_VER Offset */
#define FACTORYREGION_ROM_INM_VERSION_ROM_INM_MAJOR_VER_MASK ((uint32_t)0x00FF0000U)
/* FACTORYREGION_ROM_INM_VERSION[ROM_INM_PG_VER] Bits */
#define FACTORYREGION_ROM_INM_VERSION_ROM_INM_PG_VER_OFS (24)                            /* !< ROM_INM_PG_VER Offset */
#define FACTORYREGION_ROM_INM_VERSION_ROM_INM_PG_VER_MASK ((uint32_t)0xFF000000U)

/* FACTORYREGION_SYSPLLPARAM2 Bits */
/* FACTORYREGION_SYSPLLPARAM2[LPFCAPC] Bits */
#define FACTORYREGION_SYSPLLPARAM2_LPFCAPC_OFS   (0)                             /* !< LPFCAPC Offset */
#define FACTORYREGION_SYSPLLPARAM2_LPFCAPC_MASK  ((uint32_t)0x00000003U)
/* FACTORYREGION_SYSPLLPARAM2[RNGIXVCOIBIASCFG] Bits */
#define FACTORYREGION_SYSPLLPARAM2_RNGIXVCOIBIASCFG_OFS (3)                             /* !< RNGIXVCOIBIASCFG Offset */
#define FACTORYREGION_SYSPLLPARAM2_RNGIXVCOIBIASCFG_MASK ((uint32_t)0x00000008U)

/* FACTORYREGION_SYSPLLLDOCTL Bits */
/* FACTORYREGION_SYSPLLLDOCTL[LDOCTLLOWV] Bits */
#define FACTORYREGION_SYSPLLLDOCTL_LDOCTLLOWV_OFS (0)                             /* !< LDOCTLLOWV Offset */
#define FACTORYREGION_SYSPLLLDOCTL_LDOCTLLOWV_MASK ((uint32_t)0x0000FFFFU)

/* FACTORYREGION_SYSPLLLDOPROG Bits */
/* FACTORYREGION_SYSPLLLDOPROG[LDOVOUTPROGLOWV] Bits */
#define FACTORYREGION_SYSPLLLDOPROG_LDOVOUTPROGLOWV_OFS (0)                             /* !< LDOVOUTPROGLOWV Offset */
#define FACTORYREGION_SYSPLLLDOPROG_LDOVOUTPROGLOWV_MASK ((uint32_t)0x00000007U)

/* FACTORYREGION_EXTREF_MP3 Bits */
/* FACTORYREGION_EXTREF_MP3[TSGAIN_EXTREF_MP3] Bits */
#define FACTORYREGION_EXTREF_MP3_TSGAIN_EXTREF_MP3_OFS (0)                             /* !< TSGAIN_EXTREF_MP3 Offset */
#define FACTORYREGION_EXTREF_MP3_TSGAIN_EXTREF_MP3_MASK ((uint32_t)0x0000FFFFU)         /* !< Temperature sensor gain is recorded
                                                                                    here */
/* FACTORYREGION_EXTREF_MP3[TSOFFSET_EXTREF_MP3] Bits */
#define FACTORYREGION_EXTREF_MP3_TSOFFSET_EXTREF_MP3_OFS (16)                            /* !< TSOFFSET_EXTREF_MP3 Offset */
#define FACTORYREGION_EXTREF_MP3_TSOFFSET_EXTREF_MP3_MASK ((uint32_t)0xFFFF0000U)         /* !< Temperature sensor offset is
                                                                                    recorded here */

/* FACTORYREGION_INTREF_MP3 Bits */
/* FACTORYREGION_INTREF_MP3[TSGAIN_INTREF_MP3] Bits */
#define FACTORYREGION_INTREF_MP3_TSGAIN_INTREF_MP3_OFS (0)                             /* !< TSGAIN_INTREF_MP3 Offset */
#define FACTORYREGION_INTREF_MP3_TSGAIN_INTREF_MP3_MASK ((uint32_t)0x0000FFFFU)         /* !< Temperature sensor gain is recorded
                                                                                    here */
/* FACTORYREGION_INTREF_MP3[TSOFFSET_INTREF_MP3] Bits */
#define FACTORYREGION_INTREF_MP3_TSOFFSET_INTREF_MP3_OFS (16)                            /* !< TSOFFSET_INTREF_MP3 Offset */
#define FACTORYREGION_INTREF_MP3_TSOFFSET_INTREF_MP3_MASK ((uint32_t)0xFFFF0000U)         /* !< Temperature sensor offset is
                                                                                    recorded here */

/* FACTORYREGION_TSCODE_MP1 Bits */
/* FACTORYREGION_TSCODE_MP1[TSCODE_EXTREF_MP1] Bits */
#define FACTORYREGION_TSCODE_MP1_TSCODE_EXTREF_MP1_OFS (0)                             /* !< TSCODE_EXTREF_MP1 Offset */
#define FACTORYREGION_TSCODE_MP1_TSCODE_EXTREF_MP1_MASK ((uint32_t)0x0000FFFFU)         /* !< Temperature sensor value at 30C
                                                                                    stored at this location */
/* FACTORYREGION_TSCODE_MP1[TSCODE_INTREF_MP1] Bits */
#define FACTORYREGION_TSCODE_MP1_TSCODE_INTREF_MP1_OFS (16)                            /* !< TSCODE_INTREF_MP1 Offset */
#define FACTORYREGION_TSCODE_MP1_TSCODE_INTREF_MP1_MASK ((uint32_t)0xFFFF0000U)         /* !< Temperature sensor value at 30C
                                                                                    stored at this location */

/* FACTORYREGION_TSCODE_MP3 Bits */
/* FACTORYREGION_TSCODE_MP3[TSCODE_EXTREF_MP3] Bits */
#define FACTORYREGION_TSCODE_MP3_TSCODE_EXTREF_MP3_OFS (0)                             /* !< TSCODE_EXTREF_MP3 Offset */
#define FACTORYREGION_TSCODE_MP3_TSCODE_EXTREF_MP3_MASK ((uint32_t)0x0000FFFFU)         /* !< Temperature sensor value at 125C
                                                                                    stored at this location */
/* FACTORYREGION_TSCODE_MP3[TSCODE_INTREF_MP3] Bits */
#define FACTORYREGION_TSCODE_MP3_TSCODE_INTREF_MP3_OFS (16)                            /* !< TSCODE_INTREF_MP3 Offset */
#define FACTORYREGION_TSCODE_MP3_TSCODE_INTREF_MP3_MASK ((uint32_t)0xFFFF0000U)         /* !< Temperature sensor value at 125C
                                                                                    stored at this location */

/* FACTORYREGION_TSTEMP Bits */
/* FACTORYREGION_TSTEMP[TSTEMP_MP1] Bits */
#define FACTORYREGION_TSTEMP_TSTEMP_MP1_OFS      (0)                             /* !< TSTEMP_MP1 Offset */
#define FACTORYREGION_TSTEMP_TSTEMP_MP1_MASK     ((uint32_t)0x0000FFFFU)         /* !< Test temperature (30C) is recorded
                                                                                    here */
/* FACTORYREGION_TSTEMP[TSTEMP_MP3] Bits */
#define FACTORYREGION_TSTEMP_TSTEMP_MP3_OFS      (16)                            /* !< TSTEMP_MP3 Offset */
#define FACTORYREGION_TSTEMP_TSTEMP_MP3_MASK     ((uint32_t)0xFFFF0000U)         /* !< Test temperature (125C) is recorded
                                                                                    here */

/* FACTORYREGION_SRAMFLASH Bits */
/* FACTORYREGION_SRAMFLASH[MAINFLASH_SZ] Bits */
#define FACTORYREGION_SRAMFLASH_MAINFLASH_SZ_OFS (0)                             /* !< MAINFLASH_SZ Offset */
#define FACTORYREGION_SRAMFLASH_MAINFLASH_SZ_MASK ((uint32_t)0x00000FFFU)         /* !< For eg: if the value of the field
                                                                                    id 4, then it is 4KB, if the value is
                                                                                    32, then 32KB, and so on. */
/* FACTORYREGION_SRAMFLASH[SRAM_SZ] Bits */
#define FACTORYREGION_SRAMFLASH_SRAM_SZ_OFS      (16)                            /* !< SRAM_SZ Offset */
#define FACTORYREGION_SRAMFLASH_SRAM_SZ_MASK     ((uint32_t)0x03FF0000U)         /* !< The encoding of the field is that
                                                                                    the value of the field is an integer
                                                                                    to be interpreted as number of KBs. */
/* FACTORYREGION_SRAMFLASH[MAINNUMBANKS] Bits */
#define FACTORYREGION_SRAMFLASH_MAINNUMBANKS_OFS (12)                            /* !< MAINNUMBANKS Offset */
#define FACTORYREGION_SRAMFLASH_MAINNUMBANKS_MASK ((uint32_t)0x00003000U)         /* !< Defines the number of main flash
                                                                                    banks */
/* FACTORYREGION_SRAMFLASH[DATAFLASH_SZ] Bits */
#define FACTORYREGION_SRAMFLASH_DATAFLASH_SZ_OFS (26)                            /* !< DATAFLASH_SZ Offset */
#define FACTORYREGION_SRAMFLASH_DATAFLASH_SZ_MASK ((uint32_t)0xFC000000U)         /* !< The encoding of the field is that
                                                                                    the value of the field is an integer
                                                                                    to be interpreted as number of KBs.
                                                                                    For eg: if the value of the field id
                                                                                    4, then it is 4KB, if the value is
                                                                                    32, then 32KB, and so on. */


#ifdef __cplusplus
}
#endif

#endif /* hw_factoryregion__include */