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

#ifndef hw_tinielite__include
#define hw_tinielite__include


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
* TINIELITE Registers
******************************************************************************/
#define TINIELITE_REGFILE_OFS                    ((uint32_t)0x00002800U)
#define TINIELITE_INSTMEM_OFS                    ((uint32_t)0x00002000U)
#define TINIELITE_ACCREG_OFS                     ((uint32_t)0x00001C00U)
#define TINIELITE_ADDRREG_OFS                    ((uint32_t)0x00001154U)
#define TINIELITE_LCREG_OFS                      ((uint32_t)0x00001138U)


/** @addtogroup TINIELITE_REGFILE
  @{
*/

typedef struct {
  __I  uint32_t IIDX;                              /* !< (@ 0x00001020) Interrupt index */
       uint32_t RESERVED0;
  __IO uint32_t IMASK;                             /* !< (@ 0x00001028) Interrupt mask */
       uint32_t RESERVED1;
  __I  uint32_t RIS;                               /* !< (@ 0x00001030) Raw interrupt status */
       uint32_t RESERVED2;
  __I  uint32_t MIS;                               /* !< (@ 0x00001038) Masked interrupt status */
       uint32_t RESERVED3;
  __O  uint32_t ISET;                              /* !< (@ 0x00001040) Interrupt set */
       uint32_t RESERVED4;
  __O  uint32_t ICLR;                              /* !< (@ 0x00001048) Interrupt clear */
       uint32_t RESERVED5;
} NPU_INT_EVENT_Regs;

typedef struct {
  __IO uint32_t RFDATA[512];                       /* !< (@ 0x00002800) Register file data. */
} TINIELITE_REGFILE_Regs;

/*@}*/ /* end of group TINIELITE_REGFILE */

/** @addtogroup TINIELITE_INSTMEM
  @{
*/

typedef struct {
  __IO uint32_t INSTMEM[256];                      /* !< (@ 0x00002000) Instruction memory word. */
} TINIELITE_INSTMEM_Regs;

/*@}*/ /* end of group TINIELITE_INSTMEM */

/** @addtogroup TINIELITE_ACCREG
  @{
*/

typedef struct {
  __IO uint32_t ACCVAL[32];                        /* !< (@ 0x00001C00) Register file data. */
} TINIELITE_ACCREG_Regs;

/*@}*/ /* end of group TINIELITE_ACCREG */

/** @addtogroup TINIELITE_ADDRREG
  @{
*/

typedef struct {
  __IO uint32_t AREG[20];                          /* !< (@ 0x00001154) Address registers. */
} TINIELITE_ADDRREG_Regs;

/*@}*/ /* end of group TINIELITE_ADDRREG */

/** @addtogroup TINIELITE_LCREG
  @{
*/

typedef struct {
  __IO uint32_t LC[6];                             /* !< (@ 0x00001138) Loop count registers. */
} TINIELITE_LCREG_Regs;

/*@}*/ /* end of group TINIELITE_LCREG */

/** @addtogroup TINIELITE
  @{
*/

typedef struct {
      // uint32_t RESERVED0[1096];
      uint32_t RESERVED0[1032];  /* Reserved TILL 0x1020 */
  NPU_INT_EVENT_Regs CPU_INT; /* Possible location of interrupt regs */
      uint32_t RESERVED00[52];  /* 0x1050 onward reserved */

  __IO uint32_t CTL5;                              /* !< (@ 0x00001120) CTL5 register */
  __IO uint32_t CTL4;                              /* !< (@ 0x00001124) */
  __IO uint32_t CTL3;                              /* !< (@ 0x00001128) */
  __IO uint32_t CTL2;                              /* !< (@ 0x0000112C) CTL2 register */
  __IO uint32_t CTL1;                              /* !< (@ 0x00001130) CTL1 register */
  __IO uint32_t CTL0;                              /* !< (@ 0x00001134) CTL0 register */
  TINIELITE_LCREG_Regs  LCREG;                             /* !< (@ 0x00001138) */
  __IO uint32_t PC;                                /* !< (@ 0x00001150) Program count register */
  TINIELITE_ADDRREG_Regs  ADDRREG;                           /* !< (@ 0x00001154) */
       uint32_t RESERVED1[347];
  __IO uint32_t DATAIN[2];                         /* !< (@ 0x00001710) Input Data registers, used to load data from
                                                      memory. */
       uint32_t RESERVED2[2];
  __IO uint32_t DATAOUT;                           /* !< (@ 0x00001720) Output Data registers, used to store data to
                                                      memory. */
       uint32_t RESERVED3[3];
  __IO uint32_t SS0LOW;                            /* !< (@ 0x00001730) Scale and shift register 0, lower 32 bits. */
  __IO uint32_t SS0HIGH;                           /* !< (@ 0x00001734) Scale and shift register 0, upper 32 bits. */
  __IO uint32_t SS1LOW;                            /* !< (@ 0x00001738) Scale and shift register 1, lower 32 bits. */
  __IO uint32_t SS1HIGH;                           /* !< (@ 0x0000173C) Scale and shift register 1, upper 32 bits. */
       uint32_t RESERVED4[4];
  __IO uint32_t WGHT0LOW;                          /* !< (@ 0x00001750) Weight register 0, lower 32 bits. */
  __IO uint32_t WGHT0HIGH;                         /* !< (@ 0x00001754) Weight register 0, upper 32 bits. */
  __IO uint32_t WGHT1LOW;                          /* !< (@ 0x00001758) Weight register 1, lower 32 bits. */
  __IO uint32_t WGHT1HIGH;                         /* !< (@ 0x0000175C) Weight register 1, upper 32 bits. */
       uint32_t RESERVED5[296];
  TINIELITE_ACCREG_Regs  ACCREG;                            /* !< (@ 0x00001C00) */
       uint32_t RESERVED6[224];
  TINIELITE_INSTMEM_Regs  INSTMEM;                           /* !< (@ 0x00002000) */
       uint32_t RESERVED7[256];
  TINIELITE_REGFILE_Regs  REGFILE;                           /* !< (@ 0x00002800) */
} TINIELITE_Regs;

/*@}*/ /* end of group TINIELITE */



/******************************************************************************
* TINIELITE Register Offsets
******************************************************************************/
#define TINIELITE_CTL5                           (0x00001120U)
#define TINIELITE_CTL4                           (0x00001124U)
#define TINIELITE_CTL3                           (0x00001128U)
#define TINIELITE_CTL2                           (0x0000112CU)
#define TINIELITE_CTL1                           (0x00001130U)
#define TINIELITE_CTL0                           (0x00001134U)
#define TINIELITE_PC                             (0x00001150U)
#define TINIELITE_DATAIN(i)                      (0x00001710U + 4U * (i)) // 0 <= i < 2
#define TINIELITE_DATAOUT                        (0x00001720U)
#define TINIELITE_SS0LOW                         (0x00001730U)
#define TINIELITE_SS0HIGH                        (0x00001734U)
#define TINIELITE_SS1LOW                         (0x00001738U)
#define TINIELITE_SS1HIGH                        (0x0000173CU)
#define TINIELITE_WGHT0LOW                       (0x00001750U)
#define TINIELITE_WGHT0HIGH                      (0x00001754U)
#define TINIELITE_WGHT1LOW                       (0x00001758U)
#define TINIELITE_WGHT1HIGH                      (0x0000175CU)

#define TINIELITE_LC(i)                          (0x00001138U + 4U * (i)) // 0 <= i < 6

#define TINIELITE_AREG(i)                        (0x00001154U + 4U * (i)) // 0 <= i < 20

#define TINIELITE_ACCVAL(i)                      (0x00001C00U + 4U * (i)) // 0 <= i < 32

#define TINIELITE_INSTMEM_INSTMEM(i)             (0x00002000U + 4U * (i)) // 0 <= i < 256

#define TINIELITE_RFDATA(i)                      (0x00002800U + 4U * (i)) // 0 <= i < 512



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* TINIELITE Register Control Bits
******************************************************************************/

/* TINIELITE_RFDATA Bits */
/* TINIELITE_RFDATA[DATA] Bits */
#define TINIELITE_RFDATA_DATA_OFS                (0)                             /* !< DATA Offset */
#define TINIELITE_RFDATA_DATA_MASK               ((uint32_t)0xFFFFFFFFU)         /* !< Data word. */

/* TINIELITE_INSTMEM_INSTMEM Bits */
/* TINIELITE_INSTMEM_INSTMEM[MEM] Bits */
#define TINIELITE_INSTMEM_INSTMEM_MEM_OFS        (0)                             /* !< MEM Offset */
#define TINIELITE_INSTMEM_INSTMEM_MEM_MASK       ((uint32_t)0xFFFFFFFFU)         /* !< Instruction memory word. */

/* TINIELITE_ACCVAL Bits */
/* TINIELITE_ACCVAL[DATA] Bits */
#define TINIELITE_ACCVAL_DATA_OFS                (0)                             /* !< DATA Offset */
#define TINIELITE_ACCVAL_DATA_MASK               ((uint32_t)0x0003FFFFU)         /* !< Data word. */

/* TINIELITE_AREG Bits */
/* TINIELITE_AREG[DATA] Bits */
#define TINIELITE_AREG_DATA_OFS                  (0)                             /* !< DATA Offset */
#define TINIELITE_AREG_DATA_MASK                 ((uint32_t)0x0000FFFFU)         /* !< Data word. */

/* TINIELITE_LC Bits */
/* TINIELITE_LC[CNT] Bits */
#define TINIELITE_LC_CNT_OFS                     (0)                             /* !< CNT Offset */
#define TINIELITE_LC_CNT_MASK                    ((uint32_t)0x0000FFFFU)         /* !< Loop count. */

/* TINIELITE_CTL5 Bits */
/* TINIELITE_CTL5[RUN] Bits */
#define TINIELITE_CTL5_RUN_OFS                   (0)                             /* !< RUN Offset */
#define TINIELITE_CTL5_RUN_MASK                  ((uint32_t)0x00000001U)         /* !< Start the accelerator. Writing a 1
                                                                                    to this bit starts the accelerator.
                                                                                    When the STOP instruction is executed
                                                                                    this bit is cleared by hardware and
                                                                                    DONE interrupt flag is set. */
/* TINIELITE_CTL5[ENIFMAPCIRC] Bits */
#define TINIELITE_CTL5_ENIFMAPCIRC_OFS           (8)                             /* !< ENIFMAPCIRC Offset */
#define TINIELITE_CTL5_ENIFMAPCIRC_MASK          ((uint32_t)0x00000100U)         /* !< Enable circular addressing on input
                                                                                    feature map read address. */
#define TINIELITE_CTL5_ENIFMAPCIRC_DISABLE       ((uint32_t)0x00000000U)
#define TINIELITE_CTL5_ENIFMAPCIRC_ENABLE        ((uint32_t)0x00000100U)         /* !< Enable circular buffering on the
                                                                                    input feature map */
/* TINIELITE_CTL5[ENOFMAPCIRC] Bits */
#define TINIELITE_CTL5_ENOFMAPCIRC_OFS           (9)                             /* !< ENOFMAPCIRC Offset */
#define TINIELITE_CTL5_ENOFMAPCIRC_MASK          ((uint32_t)0x00000200U)         /* !< Enable circular addressing on
                                                                                    output feature map read address. */
#define TINIELITE_CTL5_ENOFMAPCIRC_DISABLE       ((uint32_t)0x00000000U)         /* !< Disable circular buffering on the
                                                                                    output feature map */
#define TINIELITE_CTL5_ENOFMAPCIRC_ENABLE        ((uint32_t)0x00000200U)         /* !< Enable circular buffering on the
                                                                                    output feature map */

/* TINIELITE_CTL4 Bits */
/* TINIELITE_CTL4[OFMAPCIRSTART] Bits */
#define TINIELITE_CTL4_OFMAPCIRSTART_OFS         (0)                             /* !< OFMAPCIRSTART Offset */
#define TINIELITE_CTL4_OFMAPCIRSTART_MASK        ((uint32_t)0x0000FFFFU)         /* !< Circular buffer output feature map
                                                                                    start address. */
/* TINIELITE_CTL4[OFMAPCIREND] Bits */
#define TINIELITE_CTL4_OFMAPCIREND_OFS           (16)                            /* !< OFMAPCIREND Offset */
#define TINIELITE_CTL4_OFMAPCIREND_MASK          ((uint32_t)0xFFFF0000U)         /* !< Circular buffer output feature map
                                                                                    end address. */

/* TINIELITE_CTL3 Bits */
/* TINIELITE_CTL3[IFMAPCIRSTART] Bits */
#define TINIELITE_CTL3_IFMAPCIRSTART_OFS         (0)                             /* !< IFMAPCIRSTART Offset */
#define TINIELITE_CTL3_IFMAPCIRSTART_MASK        ((uint32_t)0x0000FFFFU)         /* !< Circular buffer input feature map
                                                                                    start address */
/* TINIELITE_CTL3[IFMAPCIREND] Bits */
#define TINIELITE_CTL3_IFMAPCIREND_OFS           (16)                            /* !< IFMAPCIREND Offset */
#define TINIELITE_CTL3_IFMAPCIREND_MASK          ((uint32_t)0xFFFF0000U)         /* !< Circular buffer input feature map
                                                                                    end address */

/* TINIELITE_CTL2 Bits */
/* TINIELITE_CTL2[CLLOW] Bits */
#define TINIELITE_CTL2_CLLOW_OFS                 (0)                             /* !< CLLOW Offset */
#define TINIELITE_CTL2_CLLOW_MASK                ((uint32_t)0x000001FFU)         /* !< Lower clamp value */
/* TINIELITE_CTL2[CLHIGH] Bits */
#define TINIELITE_CTL2_CLHIGH_OFS                (16)                            /* !< CLHIGH Offset */
#define TINIELITE_CTL2_CLHIGH_MASK               ((uint32_t)0x01FF0000U)         /* !< Upper clamp value */

/* TINIELITE_CTL1 Bits */
/* TINIELITE_CTL1[IFMAPSTARTHI] Bits */
#define TINIELITE_CTL1_IFMAPSTARTHI_OFS          (0)                             /* !< IFMAPSTARTHI Offset */
#define TINIELITE_CTL1_IFMAPSTARTHI_MASK         ((uint32_t)0x0000FFFFU)         /* !< Start address (Higher 16 bits) of
                                                                                    input feature map data. */
/* TINIELITE_CTL1[OFMAPSTARTHI] Bits */
#define TINIELITE_CTL1_OFMAPSTARTHI_OFS          (16)                            /* !< OFMAPSTARTHI Offset */
#define TINIELITE_CTL1_OFMAPSTARTHI_MASK         ((uint32_t)0xFFFF0000U)         /* !< Start address (Higher 16 bits) of
                                                                                    output feature map data. */

/* TINIELITE_CTL0 Bits */
/* TINIELITE_CTL0[WTYPE] Bits */
#define TINIELITE_CTL0_WTYPE_OFS                 (12)                            /* !< WTYPE Offset */
#define TINIELITE_CTL0_WTYPE_MASK                ((uint32_t)0x0000F000U)         /* !< Weight Type */
#define TINIELITE_CTL0_WTYPE__2T                 ((uint32_t)0x00000000U)         /* !< +1,-1,0 */
#define TINIELITE_CTL0_WTYPE_BINARY              ((uint32_t)0x00001000U)         /* !< Binary data type, +1 or -1 */
#define TINIELITE_CTL0_WTYPE_SIGNED_2BIT         ((uint32_t)0x00002000U)         /* !< Unsigned 8 bit data type */
#define TINIELITE_CTL0_WTYPE_SIGNED_4BIT         ((uint32_t)0x00003000U)         /* !< Signed 4 bit data type */
#define TINIELITE_CTL0_WTYPE_SIGNED_8BIT         ((uint32_t)0x00004000U)         /* !< Signed 8 bit data type */
/* TINIELITE_CTL0[IFMAPTYPE] Bits */
#define TINIELITE_CTL0_IFMAPTYPE_OFS             (0)                             /* !< IFMAPTYPE Offset */
#define TINIELITE_CTL0_IFMAPTYPE_MASK            ((uint32_t)0x0000000FU)         /* !< Input feature map type, */
#define TINIELITE_CTL0_IFMAPTYPE_UNSIGNED_16BIT  ((uint32_t)0x00000000U)
#define TINIELITE_CTL0_IFMAPTYPE_UNSIGNED_8BIT   ((uint32_t)0x00000001U)         /* !< Unsigned 8 bit data type */
#define TINIELITE_CTL0_IFMAPTYPE_UNSIGNED_4BIT   ((uint32_t)0x00000002U)         /* !< Unsigned 4 bit data type */
#define TINIELITE_CTL0_IFMAPTYPE_BINARY          ((uint32_t)0x00000003U)         /* !< Binary data type */
#define TINIELITE_CTL0_IFMAPTYPE_SIGNED_16BIT    ((uint32_t)0x00000008U)
#define TINIELITE_CTL0_IFMAPTYPE_SIGNED_8BIT     ((uint32_t)0x00000009U)         /* !< Signed 8 bit data type */
#define TINIELITE_CTL0_IFMAPTYPE_SIGNED_4BIT     ((uint32_t)0x0000000AU)         /* !< Signed 4 bit data type */
/* TINIELITE_CTL0[OFMAPTYPE] Bits */
#define TINIELITE_CTL0_OFMAPTYPE_OFS             (4)                             /* !< OFMAPTYPE Offset */
#define TINIELITE_CTL0_OFMAPTYPE_MASK            ((uint32_t)0x000000F0U)         /* !< Output feature map type. */
#define TINIELITE_CTL0_OFMAPTYPE_UNSIGNED_16BIT  ((uint32_t)0x00000000U)
#define TINIELITE_CTL0_OFMAPTYPE_UNSIGNED_8BIT   ((uint32_t)0x00000010U)         /* !< Unsigned 8 bit data type */
#define TINIELITE_CTL0_OFMAPTYPE_UNSIGNED_4BIT   ((uint32_t)0x00000020U)         /* !< Unsigned 4 bit data type */
#define TINIELITE_CTL0_OFMAPTYPE_BINARY          ((uint32_t)0x00000030U)         /* !< Binary data type */
#define TINIELITE_CTL0_OFMAPTYPE_SIGNED_16BIT    ((uint32_t)0x00000080U)
#define TINIELITE_CTL0_OFMAPTYPE_SIGNED_8BIT     ((uint32_t)0x00000090U)         /* !< Signed 8 bit data type */
#define TINIELITE_CTL0_OFMAPTYPE_SIGNED_4BIT     ((uint32_t)0x000000A0U)         /* !< Signed 4 bit data type */
/* TINIELITE_CTL0[LAYERTYPE] Bits */
#define TINIELITE_CTL0_LAYERTYPE_OFS             (20)                            /* !< LAYERTYPE Offset */
#define TINIELITE_CTL0_LAYERTYPE_MASK            ((uint32_t)0x01F00000U)         /* !< Layer type */
#define TINIELITE_CTL0_LAYERTYPE_FCONV           ((uint32_t)0x00000000U)
#define TINIELITE_CTL0_LAYERTYPE_DW              ((uint32_t)0x00200000U)
#define TINIELITE_CTL0_LAYERTYPE_PW              ((uint32_t)0x00300000U)
#define TINIELITE_CTL0_LAYERTYPE_CONV            ((uint32_t)0x00500000U)
#define TINIELITE_CTL0_LAYERTYPE_FC              ((uint32_t)0x00600000U)
#define TINIELITE_CTL0_LAYERTYPE_AVGPOOL         ((uint32_t)0x00700000U)
#define TINIELITE_CTL0_LAYERTYPE_MAXPOOL         ((uint32_t)0x00800000U)
#define TINIELITE_CTL0_LAYERTYPE_FCONV_RESIDUAL  ((uint32_t)0x01000000U)
#define TINIELITE_CTL0_LAYERTYPE_DW_RESIDUAL     ((uint32_t)0x01200000U)
#define TINIELITE_CTL0_LAYERTYPE_PW_RESIDUAL     ((uint32_t)0x01300000U)
#define TINIELITE_CTL0_LAYERTYPE_CONV_RESIDUAL   ((uint32_t)0x01500000U)
#define TINIELITE_CTL0_LAYERTYPE_FC_RESIDUAL     ((uint32_t)0x01600000U)
#define TINIELITE_CTL0_LAYERTYPE_AVGPOOL_RESIDUAL ((uint32_t)0x01700000U)
#define TINIELITE_CTL0_LAYERTYPE_MAXPOOL_RESIDUAL ((uint32_t)0x01800000U)
/* TINIELITE_CTL0[RESIFMAPTYPE] Bits */
#define TINIELITE_CTL0_RESIFMAPTYPE_OFS          (26)                            /* !< RESIFMAPTYPE Offset */
#define TINIELITE_CTL0_RESIFMAPTYPE_MASK         ((uint32_t)0x3C000000U)         /* !< Residual Input feature map type, */
#define TINIELITE_CTL0_RESIFMAPTYPE_UNSIGNED_16BIT ((uint32_t)0x00000000U)
#define TINIELITE_CTL0_RESIFMAPTYPE_UNSIGNED_8BIT ((uint32_t)0x04000000U)         /* !< Unsigned 8 bit data type */
#define TINIELITE_CTL0_RESIFMAPTYPE_UNSIGNED_4BIT ((uint32_t)0x08000000U)         /* !< Unsigned 4 bit data type */
#define TINIELITE_CTL0_RESIFMAPTYPE_SIGNED_16BIT ((uint32_t)0x20000000U)
#define TINIELITE_CTL0_RESIFMAPTYPE_SIGNED_8BIT  ((uint32_t)0x24000000U)         /* !< Signed 8 bit data type */
#define TINIELITE_CTL0_RESIFMAPTYPE_SIGNED_4BIT  ((uint32_t)0x28000000U)         /* !< Signed 4 bit data type */

/* TINIELITE_PC Bits */
/* TINIELITE_PC[VALUE] Bits */
#define TINIELITE_PC_VALUE_OFS                   (0)                             /* !< VALUE Offset */
#define TINIELITE_PC_VALUE_MASK                  ((uint32_t)0x0000FFFFU)         /* !< Program count value. */

/* TINIELITE_DATAIN Bits */
/* TINIELITE_DATAIN[VALUE] Bits */
#define TINIELITE_DATAIN_VALUE_OFS               (0)                             /* !< VALUE Offset */
#define TINIELITE_DATAIN_VALUE_MASK              ((uint32_t)0xFFFFFFFFU)         /* !< Data value */

/* TINIELITE_DATAOUT Bits */
/* TINIELITE_DATAOUT[VALUE] Bits */
#define TINIELITE_DATAOUT_VALUE_OFS              (0)                             /* !< VALUE Offset */
#define TINIELITE_DATAOUT_VALUE_MASK             ((uint32_t)0xFFFFFFFFU)         /* !< Data out value. */

/* TINIELITE_SS0LOW Bits */
/* TINIELITE_SS0LOW[VALUE] Bits */
#define TINIELITE_SS0LOW_VALUE_OFS               (0)                             /* !< VALUE Offset */
#define TINIELITE_SS0LOW_VALUE_MASK              ((uint32_t)0xFFFFFFFFU)         /* !< Value */

/* TINIELITE_SS0HIGH Bits */
/* TINIELITE_SS0HIGH[VALUE] Bits */
#define TINIELITE_SS0HIGH_VALUE_OFS              (0)                             /* !< VALUE Offset */
#define TINIELITE_SS0HIGH_VALUE_MASK             ((uint32_t)0xFFFFFFFFU)         /* !< Value */

/* TINIELITE_SS1LOW Bits */
/* TINIELITE_SS1LOW[VALUE] Bits */
#define TINIELITE_SS1LOW_VALUE_OFS               (0)                             /* !< VALUE Offset */
#define TINIELITE_SS1LOW_VALUE_MASK              ((uint32_t)0xFFFFFFFFU)         /* !< Value */

/* TINIELITE_SS1HIGH Bits */
/* TINIELITE_SS1HIGH[VALUE] Bits */
#define TINIELITE_SS1HIGH_VALUE_OFS              (0)                             /* !< VALUE Offset */
#define TINIELITE_SS1HIGH_VALUE_MASK             ((uint32_t)0xFFFFFFFFU)         /* !< Value */

/* TINIELITE_WGHT0LOW Bits */
/* TINIELITE_WGHT0LOW[VALUE] Bits */
#define TINIELITE_WGHT0LOW_VALUE_OFS             (0)                             /* !< VALUE Offset */
#define TINIELITE_WGHT0LOW_VALUE_MASK            ((uint32_t)0xFFFFFFFFU)         /* !< Value */

/* TINIELITE_WGHT0HIGH Bits */
/* TINIELITE_WGHT0HIGH[VALUE] Bits */
#define TINIELITE_WGHT0HIGH_VALUE_OFS            (0)                             /* !< VALUE Offset */
#define TINIELITE_WGHT0HIGH_VALUE_MASK           ((uint32_t)0xFFFFFFFFU)         /* !< Value */

/* TINIELITE_WGHT1LOW Bits */
/* TINIELITE_WGHT1LOW[VALUE] Bits */
#define TINIELITE_WGHT1LOW_VALUE_OFS             (0)                             /* !< VALUE Offset */
#define TINIELITE_WGHT1LOW_VALUE_MASK            ((uint32_t)0xFFFFFFFFU)         /* !< Value */

/* TINIELITE_WGHT1HIGH Bits */
/* TINIELITE_WGHT1HIGH[VALUE] Bits */
#define TINIELITE_WGHT1HIGH_VALUE_OFS            (0)                             /* !< VALUE Offset */
#define TINIELITE_WGHT1HIGH_VALUE_MASK           ((uint32_t)0xFFFFFFFFU)         /* !< Value */


#ifdef __cplusplus
}
#endif

#endif /* hw_tinielite__include */
