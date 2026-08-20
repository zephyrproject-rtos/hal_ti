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

#ifndef hw_adc__include
#define hw_adc__include


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
* ADC Registers
******************************************************************************/
#define ADC_GPRCM_OFS                            ((uint32_t)0x00000800U)


/** @addtogroup ADC_RESULT
  @{
*/

typedef struct {
  __IO uint16_t ADCRESULT0;                        /* !< (@ 0x00000000) ADC Result 0 Register */
  __IO uint16_t ADCRESULT1;                        /* !< (@ 0x00000002) ADC Result 1 Register */
  __IO uint16_t ADCRESULT2;                        /* !< (@ 0x00000004) ADC Result 2 Register */
  __IO uint16_t ADCRESULT3;                        /* !< (@ 0x00000006) ADC Result 3 Register */
  __IO uint16_t ADCRESULT4;                        /* !< (@ 0x00000008) ADC Result 4 Register */
  __IO uint16_t ADCRESULT5;                        /* !< (@ 0x0000000A) ADC Result 5 Register */
  __IO uint16_t ADCRESULT6;                        /* !< (@ 0x0000000C) ADC Result 6 Register */
  __IO uint16_t ADCRESULT7;                        /* !< (@ 0x0000000E) ADC Result 7 Register */
  __IO uint16_t ADCRESULT8;                        /* !< (@ 0x00000010) ADC Result 8 Register */
  __IO uint16_t ADCRESULT9;                        /* !< (@ 0x00000012) ADC Result 9 Register */
  __IO uint16_t ADCRESULT10;                       /* !< (@ 0x00000014) ADC Result 10 Register */
  __IO uint16_t ADCRESULT11;                       /* !< (@ 0x00000016) ADC Result 11 Register */
  __IO uint16_t ADCRESULT12;                       /* !< (@ 0x00000018) ADC Result 12 Register */
  __IO uint16_t ADCRESULT13;                       /* !< (@ 0x0000001A) ADC Result 13 Register */
  __IO uint16_t ADCRESULT14;                       /* !< (@ 0x0000001C) ADC Result 14 Register */
  __IO uint16_t ADCRESULT15;                       /* !< (@ 0x0000001E) ADC Result 15 Register */
       uint32_t RESERVED0[8];
  __IO uint32_t ADCPPB1RESULT;                     /* !< (@ 0x00000040) ADC Post Processing Block 1 Result Register */
  __IO uint32_t ADCPPB2RESULT;                     /* !< (@ 0x00000044) ADC Post Processing Block 2 Result Register */
  __IO uint32_t ADCPPB3RESULT;                     /* !< (@ 0x00000048) ADC Post Processing Block 3 Result Register */
  __IO uint32_t ADCPPB4RESULT;                     /* !< (@ 0x0000004C) ADC Post Processing Block 4 Result Register */
  __IO uint32_t ADCPPB1SUM;                        /* !< (@ 0x00000050) ADC PPB 1 Final Sum Result Register */
  __IO uint16_t ADCPPB1COUNT;                      /* !< (@ 0x00000054) ADC PPB1 Final Conversion Count Register */
       uint16_t RESERVED1;
  __IO uint32_t ADCPPB2SUM;                        /* !< (@ 0x00000058) ADC PPB 2 Final Sum Result Register */
  __IO uint16_t ADCPPB2COUNT;                      /* !< (@ 0x0000005C) ADC PPB2 Final Conversion Count Register */
       uint16_t RESERVED2;
  __IO uint32_t ADCPPB3SUM;                        /* !< (@ 0x00000060) ADC PPB 3 Final Sum Result Register */
  __IO uint16_t ADCPPB3COUNT;                      /* !< (@ 0x00000064) ADC PPB3 Final Conversion Count Register */
       uint16_t RESERVED3;
  __IO uint32_t ADCPPB4SUM;                        /* !< (@ 0x00000068) ADC PPB 4 Final Sum Result Register */
  __IO uint16_t ADCPPB4COUNT;                      /* !< (@ 0x0000006C) ADC PPB4 Final Conversion Count Register */
       uint16_t RESERVED4[41];
  __IO uint32_t ADCSEQ1FIFORESULT;                 /* !< (@ 0x000000C0) ADC Sequence 1 FIFO Result Register */
  __IO uint32_t ADCSEQ2FIFORESULT;                 /* !< (@ 0x000000C4) ADC Sequence 2 FIFO Result Register */
  __IO uint32_t ADCSEQ3FIFORESULT;                 /* !< (@ 0x000000C8) ADC Sequence 3 FIFO Result Register */
  __IO uint32_t ADCSEQ4FIFORESULT;                 /* !< (@ 0x000000CC) ADC Sequence 4 FIFO Result Register */
  __IO uint32_t ADCSEQ1FIFOSTATUS;                 /* !< (@ 0x000000D0) ADC Sequence 1 FIFO Status */
  __IO uint32_t ADCSEQ2FIFOSTATUS;                 /* !< (@ 0x000000D4) ADC Sequence 2 FIFO Status */
  __IO uint32_t ADCSEQ3FIFOSTATUS;                 /* !< (@ 0x000000D8) ADC Sequence 3 FIFO Status */
  __IO uint32_t ADCSEQ4FIFOSTATUS;                 /* !< (@ 0x000000DC) ADC Sequence 4 FIFO Status */
} ADC_RESULT_Regs;

/*@}*/ /* end of group ADC_RESULT */

/** @addtogroup ADC_GPRCM
  @{
*/

typedef struct {
  __IO uint32_t PWREN;                             /* !< (@ 0x00000800) Power enable */
  __O  uint32_t RSTCTL;                            /* !< (@ 0x00000804) Reset Control */
       uint32_t RESERVED0[3];
  __I  uint32_t STAT;                              /* !< (@ 0x00000814) Status Register */
} ADC_GPRCM_Regs;

/*@}*/ /* end of group ADC_GPRCM */

/** @addtogroup ADC
  @{
*/

typedef struct {
       uint32_t RESERVED0[512];
  ADC_GPRCM_Regs  GPRCM;                             /* !< (@ 0x00000800) */
       uint32_t RESERVED1[506];
  __IO uint32_t ADCCTL1;                           /* !< (@ 0x00001000) ADC Control 1 Register */
  __IO uint32_t ADCCTL2;                           /* !< (@ 0x00001004) ADC Control 2 Register */
       uint32_t RESERVED2[2];
  __IO uint32_t ADCINTSEL;                         /* !< (@ 0x00001010) ADC Interrupt 1, 2, 3 and 4 Selection Register */
  __IO uint32_t ADCDMAINTSEL;                      /* !< (@ 0x00001014) ADC DMA Interrupt 1, 2, 3 and 4 Selection Register */
  __IO uint32_t ADCRAWINTFLG;                      /* !< (@ 0x00001018) ADC Raw Interrupt Flag Register */
  __IO uint32_t ADCINTFLG;                         /* !< (@ 0x0000101C) ADC Interrupt Flag Register */
  __IO uint32_t ADCINTFLGFRC;                      /* !< (@ 0x00001020) ADC Interrupt Flag Force Register */
  __IO uint32_t ADCINTFLGCLR;                      /* !< (@ 0x00001024) ADC Interrupt Flag Clear Register */
  __IO uint32_t ADCINTOVF;                         /* !< (@ 0x00001028) ADC Interrupt Overflow Register */
  __IO uint32_t ADCINTOVFCLR;                      /* !< (@ 0x0000102C) ADC Interrupt Overflow Clear Register */
       uint32_t RESERVED3[3];
  __IO uint32_t ADCSOCFLG1;                        /* !< (@ 0x0000103C) ADC SOC Flag 1 Register */
       uint32_t RESERVED4;
  __IO uint32_t ADCSOCOVF1;                        /* !< (@ 0x00001044) ADC SOC Overflow 1 Register */
  __IO uint32_t ADCSOCOVFCLR1;                     /* !< (@ 0x00001048) ADC SOC Overflow Clear 1 Register */
  __IO uint32_t ADCSOC0CTL;                        /* !< (@ 0x0000104C) ADC SOC0 Control Register */
  __IO uint32_t ADCSOC1CTL;                        /* !< (@ 0x00001050) ADC SOC1 Control Register */
  __IO uint32_t ADCSOC2CTL;                        /* !< (@ 0x00001054) ADC SOC2 Control Register */
  __IO uint32_t ADCSOC3CTL;                        /* !< (@ 0x00001058) ADC SOC3 Control Register */
  __IO uint32_t ADCSOC4CTL;                        /* !< (@ 0x0000105C) ADC SOC4 Control Register */
  __IO uint32_t ADCSOC5CTL;                        /* !< (@ 0x00001060) ADC SOC5 Control Register */
  __IO uint32_t ADCSOC6CTL;                        /* !< (@ 0x00001064) ADC SOC6 Control Register */
  __IO uint32_t ADCSOC7CTL;                        /* !< (@ 0x00001068) ADC SOC7 Control Register */
  __IO uint32_t ADCSOC8CTL;                        /* !< (@ 0x0000106C) ADC SOC8 Control Register */
  __IO uint32_t ADCSOC9CTL;                        /* !< (@ 0x00001070) ADC SOC9 Control Register */
  __IO uint32_t ADCSOC10CTL;                       /* !< (@ 0x00001074) ADC SOC10 Control Register */
  __IO uint32_t ADCSOC11CTL;                       /* !< (@ 0x00001078) ADC SOC11 Control Register */
  __IO uint32_t ADCSOC12CTL;                       /* !< (@ 0x0000107C) ADC SOC12 Control Register */
  __IO uint32_t ADCSOC13CTL;                       /* !< (@ 0x00001080) ADC SOC13 Control Register */
  __IO uint32_t ADCSOC14CTL;                       /* !< (@ 0x00001084) ADC SOC14 Control Register */
  __IO uint32_t ADCSOC15CTL;                       /* !< (@ 0x00001088) ADC SOC15 Control Register */
       uint32_t RESERVED5[16];
  __IO uint32_t ADCEVTSTAT;                        /* !< (@ 0x000010CC) ADC Event Status Register */
  __IO uint32_t ADCEVTCLR;                         /* !< (@ 0x000010D0) ADC Event Clear Register */
  __IO uint32_t ADCEVTSEL;                         /* !< (@ 0x000010D4) ADC Event Selection Register */
  __IO uint32_t ADCEVTINTSEL;                      /* !< (@ 0x000010D8) ADC Event Interrupt Selection Register */
       uint32_t RESERVED6[2];
  __IO uint32_t ADCREV;                            /* !< (@ 0x000010E4) ADC Revision Register */
  __IO uint32_t ADCOFFTRIM;                        /* !< (@ 0x000010E8) ADC Offset Trim Register 1 */
       uint32_t RESERVED7[5];
  __IO uint32_t ADCPPB1CONFIG;                     /* !< (@ 0x00001100) ADC PPB1 Config Register */
       uint32_t RESERVED8[3];
  __IO uint32_t ADCPPB1TRIPHI;                     /* !< (@ 0x00001110) ADC PPB1 Trip High Register */
  __IO uint32_t ADCPPB1TRIPLO;                     /* !< (@ 0x00001114) ADC PPB1 Trip Low/Trigger Time Stamp Register */
       uint32_t RESERVED9[2];
  __IO uint32_t ADCPPB2CONFIG;                     /* !< (@ 0x00001120) ADC PPB2 Config Register */
       uint32_t RESERVED10[3];
  __IO uint32_t ADCPPB2TRIPHI;                     /* !< (@ 0x00001130) ADC PPB2 Trip High Register */
  __IO uint32_t ADCPPB2TRIPLO;                     /* !< (@ 0x00001134) ADC PPB2 Trip Low/Trigger Time Stamp Register */
       uint32_t RESERVED11[2];
  __IO uint32_t ADCPPB3CONFIG;                     /* !< (@ 0x00001140) ADC PPB3 Config Register */
       uint32_t RESERVED12[3];
  __IO uint32_t ADCPPB3TRIPHI;                     /* !< (@ 0x00001150) ADC PPB3 Trip High Register */
  __IO uint32_t ADCPPB3TRIPLO;                     /* !< (@ 0x00001154) ADC PPB3 Trip Low/Trigger Time Stamp Register */
       uint32_t RESERVED13[2];
  __IO uint32_t ADCPPB4CONFIG;                     /* !< (@ 0x00001160) ADC PPB4 Config Register */
       uint32_t RESERVED14[3];
  __IO uint32_t ADCPPB4TRIPHI;                     /* !< (@ 0x00001170) ADC PPB4 Trip High Register */
  __IO uint32_t ADCPPB4TRIPLO;                     /* !< (@ 0x00001174) ADC PPB4 Trip Low/Trigger Time Stamp Register */
       uint32_t RESERVED15[2];
  __IO uint32_t ADCINTCYCLE;                       /* !< (@ 0x00001180) ADC Early Interrupt Generation Cycle */
       uint32_t RESERVED16[6];
  __IO uint32_t ADCREV2;                           /* !< (@ 0x0000119C) ADC Wrapper Revision Register */
       uint32_t RESERVED17[24];
  __IO uint32_t ADCPPB1LIMIT;                      /* !< (@ 0x00001200) ADC PPB1Conversion Count Limit Register */
  __IO uint32_t ADCPPB1PCOUNT;                     /* !< (@ 0x00001204) ADC PPB1 Partial Conversion Count Register */
  __IO uint32_t ADCPPB1CONFIG2;                    /* !< (@ 0x00001208) ADC PPB1 Sum Shift Register */
  __IO uint32_t ADCPPB1PSUM;                       /* !< (@ 0x0000120C) ADC PPB1 Partial Sum Register */
       uint32_t RESERVED18[12];
  __IO uint32_t ADCPPB2LIMIT;                      /* !< (@ 0x00001240) ADC PPB2Conversion Count Limit Register */
  __IO uint32_t ADCPPB2PCOUNT;                     /* !< (@ 0x00001244) ADC PPB2 Partial Conversion Count Register */
  __IO uint32_t ADCPPB2CONFIG2;                    /* !< (@ 0x00001248) ADC PPB2 Sum Shift Register */
  __IO uint32_t ADCPPB2PSUM;                       /* !< (@ 0x0000124C) ADC PPB2 Partial Sum Register */
       uint32_t RESERVED19[12];
  __IO uint32_t ADCPPB3LIMIT;                      /* !< (@ 0x00001280) ADC PPB3Conversion Count Limit Register */
  __IO uint32_t ADCPPB3PCOUNT;                     /* !< (@ 0x00001284) ADC PPB3 Partial Conversion Count Register */
  __IO uint32_t ADCPPB3CONFIG2;                    /* !< (@ 0x00001288) ADC PPB3 Sum Shift Register */
  __IO uint32_t ADCPPB3PSUM;                       /* !< (@ 0x0000128C) ADC PPB3 Partial Sum Register */
       uint32_t RESERVED20[12];
  __IO uint32_t ADCPPB4LIMIT;                      /* !< (@ 0x000012C0) ADC PPB4Conversion Count Limit Register */
  __IO uint32_t ADCPPB4PCOUNT;                     /* !< (@ 0x000012C4) ADC PPB4 Partial Conversion Count Register */
  __IO uint32_t ADCPPB4CONFIG2;                    /* !< (@ 0x000012C8) ADC PPB4 Sum Shift Register */
  __IO uint32_t ADCPPB4PSUM;                       /* !< (@ 0x000012CC) ADC PPB4 Partial Sum Register */
       uint32_t RESERVED21[20];
  __IO uint32_t ADCSEQCTL;                         /* !< (@ 0x00001320) ADC Sequencer common control Register */
  __IO uint32_t ADCSEQ1CONFIG;                     /* !< (@ 0x00001324) ADC Sequencer 1 Config register */
  __IO uint32_t ADCSEQ2CONFIG;                     /* !< (@ 0x00001328) ADC Sequencer 2 Config register */
  __IO uint32_t ADCSEQ3CONFIG;                     /* !< (@ 0x0000132C) ADC Sequencer 3 Config register */
  __IO uint32_t ADCSEQ4CONFIG;                     /* !< (@ 0x00001330) ADC Sequencer 4 Config register */
} ADC_Regs;

/*@}*/ /* end of group ADC */



/******************************************************************************
* ADC Register Offsets
******************************************************************************/
#define ADC_ADCCTL1                              (0x00001000U)
#define ADC_ADCCTL2                              (0x00001004U)
#define ADC_ADCINTSEL                            (0x00001010U)
#define ADC_ADCDMAINTSEL                         (0x00001014U)
#define ADC_ADCRAWINTFLG                         (0x00001018U)
#define ADC_ADCINTFLG                            (0x0000101CU)
#define ADC_ADCINTFLGFRC                         (0x00001020U)
#define ADC_ADCINTFLGCLR                         (0x00001024U)
#define ADC_ADCINTOVF                            (0x00001028U)
#define ADC_ADCINTOVFCLR                         (0x0000102CU)
#define ADC_ADCSOCFLG1                           (0x0000103CU)
#define ADC_ADCSOCOVF1                           (0x00001044U)
#define ADC_ADCSOCOVFCLR1                        (0x00001048U)
#define ADC_ADCSOC0CTL                           (0x0000104CU)
#define ADC_ADCSOC1CTL                           (0x00001050U)
#define ADC_ADCSOC2CTL                           (0x00001054U)
#define ADC_ADCSOC3CTL                           (0x00001058U)
#define ADC_ADCSOC4CTL                           (0x0000105CU)
#define ADC_ADCSOC5CTL                           (0x00001060U)
#define ADC_ADCSOC6CTL                           (0x00001064U)
#define ADC_ADCSOC7CTL                           (0x00001068U)
#define ADC_ADCSOC8CTL                           (0x0000106CU)
#define ADC_ADCSOC9CTL                           (0x00001070U)
#define ADC_ADCSOC10CTL                          (0x00001074U)
#define ADC_ADCSOC11CTL                          (0x00001078U)
#define ADC_ADCSOC12CTL                          (0x0000107CU)
#define ADC_ADCSOC13CTL                          (0x00001080U)
#define ADC_ADCSOC14CTL                          (0x00001084U)
#define ADC_ADCSOC15CTL                          (0x00001088U)
#define ADC_ADCEVTSTAT                           (0x000010CCU)
#define ADC_ADCEVTCLR                            (0x000010D0U)
#define ADC_ADCEVTSEL                            (0x000010D4U)
#define ADC_ADCEVTINTSEL                         (0x000010D8U)
#define ADC_ADCREV                               (0x000010E4U)
#define ADC_ADCOFFTRIM                           (0x000010E8U)
#define ADC_ADCPPB1CONFIG                        (0x00001100U)
#define ADC_ADCPPB1TRIPHI                        (0x00001110U)
#define ADC_ADCPPB1TRIPLO                        (0x00001114U)
#define ADC_ADCPPB2CONFIG                        (0x00001120U)
#define ADC_ADCPPB2TRIPHI                        (0x00001130U)
#define ADC_ADCPPB2TRIPLO                        (0x00001134U)
#define ADC_ADCPPB3CONFIG                        (0x00001140U)
#define ADC_ADCPPB3TRIPHI                        (0x00001150U)
#define ADC_ADCPPB3TRIPLO                        (0x00001154U)
#define ADC_ADCPPB4CONFIG                        (0x00001160U)
#define ADC_ADCPPB4TRIPHI                        (0x00001170U)
#define ADC_ADCPPB4TRIPLO                        (0x00001174U)
#define ADC_ADCINTCYCLE                          (0x00001180U)
#define ADC_ADCREV2                              (0x0000119CU)
#define ADC_ADCPPB1LIMIT                         (0x00001200U)
#define ADC_ADCPPB1PCOUNT                        (0x00001204U)
#define ADC_ADCPPB1CONFIG2                       (0x00001208U)
#define ADC_ADCPPB1PSUM                          (0x0000120CU)
#define ADC_ADCPPB2LIMIT                         (0x00001240U)
#define ADC_ADCPPB2PCOUNT                        (0x00001244U)
#define ADC_ADCPPB2CONFIG2                       (0x00001248U)
#define ADC_ADCPPB2PSUM                          (0x0000124CU)
#define ADC_ADCPPB3LIMIT                         (0x00001280U)
#define ADC_ADCPPB3PCOUNT                        (0x00001284U)
#define ADC_ADCPPB3CONFIG2                       (0x00001288U)
#define ADC_ADCPPB3PSUM                          (0x0000128CU)
#define ADC_ADCPPB4LIMIT                         (0x000012C0U)
#define ADC_ADCPPB4PCOUNT                        (0x000012C4U)
#define ADC_ADCPPB4CONFIG2                       (0x000012C8U)
#define ADC_ADCPPB4PSUM                          (0x000012CCU)
#define ADC_ADCSEQCTL                            (0x00001320U)
#define ADC_ADCSEQ1CONFIG                        (0x00001324U)
#define ADC_ADCSEQ2CONFIG                        (0x00001328U)
#define ADC_ADCSEQ3CONFIG                        (0x0000132CU)
#define ADC_ADCSEQ4CONFIG                        (0x00001330U)

#define ADC_PWREN                                (0x00000800U)
#define ADC_RSTCTL                               (0x00000804U)
#define ADC_STAT                                 (0x00000814U)

#define ADC_ADCRESULT0                           (0x00000000U)
#define ADC_ADCRESULT1                           (0x00000002U)
#define ADC_ADCRESULT2                           (0x00000004U)
#define ADC_ADCRESULT3                           (0x00000006U)
#define ADC_ADCRESULT4                           (0x00000008U)
#define ADC_ADCRESULT5                           (0x0000000AU)
#define ADC_ADCRESULT6                           (0x0000000CU)
#define ADC_ADCRESULT7                           (0x0000000EU)
#define ADC_ADCRESULT8                           (0x00000010U)
#define ADC_ADCRESULT9                           (0x00000012U)
#define ADC_ADCRESULT10                          (0x00000014U)
#define ADC_ADCRESULT11                          (0x00000016U)
#define ADC_ADCRESULT12                          (0x00000018U)
#define ADC_ADCRESULT13                          (0x0000001AU)
#define ADC_ADCRESULT14                          (0x0000001CU)
#define ADC_ADCRESULT15                          (0x0000001EU)
#define ADC_ADCPPB1RESULT                        (0x00000040U)
#define ADC_ADCPPB2RESULT                        (0x00000044U)
#define ADC_ADCPPB3RESULT                        (0x00000048U)
#define ADC_ADCPPB4RESULT                        (0x0000004CU)
#define ADC_ADCPPB1SUM                           (0x00000050U)
#define ADC_ADCPPB1COUNT                         (0x00000054U)
#define ADC_ADCPPB2SUM                           (0x00000058U)
#define ADC_ADCPPB2COUNT                         (0x0000005CU)
#define ADC_ADCPPB3SUM                           (0x00000060U)
#define ADC_ADCPPB3COUNT                         (0x00000064U)
#define ADC_ADCPPB4SUM                           (0x00000068U)
#define ADC_ADCPPB4COUNT                         (0x0000006CU)
#define ADC_ADCSEQ1FIFORESULT                    (0x000000C0U)
#define ADC_ADCSEQ2FIFORESULT                    (0x000000C4U)
#define ADC_ADCSEQ3FIFORESULT                    (0x000000C8U)
#define ADC_ADCSEQ4FIFORESULT                    (0x000000CCU)
#define ADC_ADCSEQ1FIFOSTATUS                    (0x000000D0U)
#define ADC_ADCSEQ2FIFOSTATUS                    (0x000000D4U)
#define ADC_ADCSEQ3FIFOSTATUS                    (0x000000D8U)
#define ADC_ADCSEQ4FIFOSTATUS                    (0x000000DCU)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* ADC Register Control Bits
******************************************************************************/

/* ADC_ADCRESULT0 Bits */
/* ADC_ADCRESULT0[RESULT] Bits */
#define ADC_ADCRESULT0_RESULT_OFS                (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT0_RESULT_MASK               ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT1 Bits */
/* ADC_ADCRESULT1[RESULT] Bits */
#define ADC_ADCRESULT1_RESULT_OFS                (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT1_RESULT_MASK               ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT2 Bits */
/* ADC_ADCRESULT2[RESULT] Bits */
#define ADC_ADCRESULT2_RESULT_OFS                (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT2_RESULT_MASK               ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT3 Bits */
/* ADC_ADCRESULT3[RESULT] Bits */
#define ADC_ADCRESULT3_RESULT_OFS                (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT3_RESULT_MASK               ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT4 Bits */
/* ADC_ADCRESULT4[RESULT] Bits */
#define ADC_ADCRESULT4_RESULT_OFS                (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT4_RESULT_MASK               ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT5 Bits */
/* ADC_ADCRESULT5[RESULT] Bits */
#define ADC_ADCRESULT5_RESULT_OFS                (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT5_RESULT_MASK               ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT6 Bits */
/* ADC_ADCRESULT6[RESULT] Bits */
#define ADC_ADCRESULT6_RESULT_OFS                (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT6_RESULT_MASK               ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT7 Bits */
/* ADC_ADCRESULT7[RESULT] Bits */
#define ADC_ADCRESULT7_RESULT_OFS                (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT7_RESULT_MASK               ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT8 Bits */
/* ADC_ADCRESULT8[RESULT] Bits */
#define ADC_ADCRESULT8_RESULT_OFS                (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT8_RESULT_MASK               ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT9 Bits */
/* ADC_ADCRESULT9[RESULT] Bits */
#define ADC_ADCRESULT9_RESULT_OFS                (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT9_RESULT_MASK               ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT10 Bits */
/* ADC_ADCRESULT10[RESULT] Bits */
#define ADC_ADCRESULT10_RESULT_OFS               (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT10_RESULT_MASK              ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT11 Bits */
/* ADC_ADCRESULT11[RESULT] Bits */
#define ADC_ADCRESULT11_RESULT_OFS               (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT11_RESULT_MASK              ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT12 Bits */
/* ADC_ADCRESULT12[RESULT] Bits */
#define ADC_ADCRESULT12_RESULT_OFS               (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT12_RESULT_MASK              ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT13 Bits */
/* ADC_ADCRESULT13[RESULT] Bits */
#define ADC_ADCRESULT13_RESULT_OFS               (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT13_RESULT_MASK              ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT14 Bits */
/* ADC_ADCRESULT14[RESULT] Bits */
#define ADC_ADCRESULT14_RESULT_OFS               (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT14_RESULT_MASK              ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCRESULT15 Bits */
/* ADC_ADCRESULT15[RESULT] Bits */
#define ADC_ADCRESULT15_RESULT_OFS               (0)                             /* !< RESULT Offset */
#define ADC_ADCRESULT15_RESULT_MASK              ((uint16_t)0x0000FFFFU)         /* !< ADC Result */

/* ADC_ADCPPB1RESULT Bits */
/* ADC_ADCPPB1RESULT[PPBRESULT] Bits */
#define ADC_ADCPPB1RESULT_PPBRESULT_OFS          (0)                             /* !< PPBRESULT Offset */
#define ADC_ADCPPB1RESULT_PPBRESULT_MASK         ((uint32_t)0x00001FFFU)         /* !< ADC Post Processing Block Result */
/* ADC_ADCPPB1RESULT[SIGN] Bits */
#define ADC_ADCPPB1RESULT_SIGN_OFS               (13)                            /* !< SIGN Offset */
#define ADC_ADCPPB1RESULT_SIGN_MASK              ((uint32_t)0xFFFFE000U)         /* !< Sign Extended Bits */

/* ADC_ADCPPB2RESULT Bits */
/* ADC_ADCPPB2RESULT[PPBRESULT] Bits */
#define ADC_ADCPPB2RESULT_PPBRESULT_OFS          (0)                             /* !< PPBRESULT Offset */
#define ADC_ADCPPB2RESULT_PPBRESULT_MASK         ((uint32_t)0x00001FFFU)         /* !< ADC Post Processing Block Result */
/* ADC_ADCPPB2RESULT[SIGN] Bits */
#define ADC_ADCPPB2RESULT_SIGN_OFS               (13)                            /* !< SIGN Offset */
#define ADC_ADCPPB2RESULT_SIGN_MASK              ((uint32_t)0xFFFFE000U)         /* !< Sign Extended Bits */

/* ADC_ADCPPB3RESULT Bits */
/* ADC_ADCPPB3RESULT[PPBRESULT] Bits */
#define ADC_ADCPPB3RESULT_PPBRESULT_OFS          (0)                             /* !< PPBRESULT Offset */
#define ADC_ADCPPB3RESULT_PPBRESULT_MASK         ((uint32_t)0x00001FFFU)         /* !< ADC Post Processing Block Result */
/* ADC_ADCPPB3RESULT[SIGN] Bits */
#define ADC_ADCPPB3RESULT_SIGN_OFS               (13)                            /* !< SIGN Offset */
#define ADC_ADCPPB3RESULT_SIGN_MASK              ((uint32_t)0xFFFFE000U)         /* !< Sign Extended Bits */

/* ADC_ADCPPB4RESULT Bits */
/* ADC_ADCPPB4RESULT[PPBRESULT] Bits */
#define ADC_ADCPPB4RESULT_PPBRESULT_OFS          (0)                             /* !< PPBRESULT Offset */
#define ADC_ADCPPB4RESULT_PPBRESULT_MASK         ((uint32_t)0x00001FFFU)         /* !< ADC Post Processing Block Result */
/* ADC_ADCPPB4RESULT[SIGN] Bits */
#define ADC_ADCPPB4RESULT_SIGN_OFS               (13)                            /* !< SIGN Offset */
#define ADC_ADCPPB4RESULT_SIGN_MASK              ((uint32_t)0xFFFFE000U)         /* !< Sign Extended Bits */

/* ADC_ADCPPB1SUM Bits */
/* ADC_ADCPPB1SUM[SUM] Bits */
#define ADC_ADCPPB1SUM_SUM_OFS                   (0)                             /* !< SUM Offset */
#define ADC_ADCPPB1SUM_SUM_MASK                  ((uint32_t)0x0000FFFFU)         /* !< Post Processing Block 1
                                                                                    Oversampling Sum */
/* ADC_ADCPPB1SUM[SIGN] Bits */
#define ADC_ADCPPB1SUM_SIGN_OFS                  (16)                            /* !< SIGN Offset */
#define ADC_ADCPPB1SUM_SIGN_MASK                 ((uint32_t)0xFFFF0000U)         /* !< Sign Extended Bits */

/* ADC_ADCPPB1COUNT Bits */
/* ADC_ADCPPB1COUNT[COUNT] Bits */
#define ADC_ADCPPB1COUNT_COUNT_OFS               (0)                             /* !< COUNT Offset */
#define ADC_ADCPPB1COUNT_COUNT_MASK              ((uint16_t)0x0000000FU)         /* !< Post Processing Block 1 Final Count */

/* ADC_ADCPPB2SUM Bits */
/* ADC_ADCPPB2SUM[SUM] Bits */
#define ADC_ADCPPB2SUM_SUM_OFS                   (0)                             /* !< SUM Offset */
#define ADC_ADCPPB2SUM_SUM_MASK                  ((uint32_t)0x0000FFFFU)         /* !< Post Processing Block 2
                                                                                    Oversampling Sum */
/* ADC_ADCPPB2SUM[SIGN] Bits */
#define ADC_ADCPPB2SUM_SIGN_OFS                  (16)                            /* !< SIGN Offset */
#define ADC_ADCPPB2SUM_SIGN_MASK                 ((uint32_t)0xFFFF0000U)         /* !< Sign Extended Bits */

/* ADC_ADCPPB2COUNT Bits */
/* ADC_ADCPPB2COUNT[COUNT] Bits */
#define ADC_ADCPPB2COUNT_COUNT_OFS               (0)                             /* !< COUNT Offset */
#define ADC_ADCPPB2COUNT_COUNT_MASK              ((uint16_t)0x0000000FU)         /* !< Post Processing Block 2 Final Count */

/* ADC_ADCPPB3SUM Bits */
/* ADC_ADCPPB3SUM[SUM] Bits */
#define ADC_ADCPPB3SUM_SUM_OFS                   (0)                             /* !< SUM Offset */
#define ADC_ADCPPB3SUM_SUM_MASK                  ((uint32_t)0x0000FFFFU)         /* !< Post Processing Block 3
                                                                                    Oversampling Sum */
/* ADC_ADCPPB3SUM[SIGN] Bits */
#define ADC_ADCPPB3SUM_SIGN_OFS                  (16)                            /* !< SIGN Offset */
#define ADC_ADCPPB3SUM_SIGN_MASK                 ((uint32_t)0xFFFF0000U)         /* !< Sign Extended Bits */

/* ADC_ADCPPB3COUNT Bits */
/* ADC_ADCPPB3COUNT[COUNT] Bits */
#define ADC_ADCPPB3COUNT_COUNT_OFS               (0)                             /* !< COUNT Offset */
#define ADC_ADCPPB3COUNT_COUNT_MASK              ((uint16_t)0x0000000FU)         /* !< Post Processing Block 3 Final Count */

/* ADC_ADCPPB4SUM Bits */
/* ADC_ADCPPB4SUM[SUM] Bits */
#define ADC_ADCPPB4SUM_SUM_OFS                   (0)                             /* !< SUM Offset */
#define ADC_ADCPPB4SUM_SUM_MASK                  ((uint32_t)0x0000FFFFU)         /* !< Post Processing Block 4
                                                                                    Oversampling Sum */
/* ADC_ADCPPB4SUM[SIGN] Bits */
#define ADC_ADCPPB4SUM_SIGN_OFS                  (16)                            /* !< SIGN Offset */
#define ADC_ADCPPB4SUM_SIGN_MASK                 ((uint32_t)0xFFFF0000U)         /* !< Sign Extended Bits */

/* ADC_ADCPPB4COUNT Bits */
/* ADC_ADCPPB4COUNT[COUNT] Bits */
#define ADC_ADCPPB4COUNT_COUNT_OFS               (0)                             /* !< COUNT Offset */
#define ADC_ADCPPB4COUNT_COUNT_MASK              ((uint16_t)0x0000000FU)         /* !< Post Processing Block 4 Final Count */

/* ADC_ADCSEQ1FIFORESULT Bits */
/* ADC_ADCSEQ1FIFORESULT[SEQFIFORESULT] Bits */
#define ADC_ADCSEQ1FIFORESULT_SEQFIFORESULT_OFS  (0)                             /* !< SEQFIFORESULT Offset */
#define ADC_ADCSEQ1FIFORESULT_SEQFIFORESULT_MASK ((uint32_t)0xFFFFFFFFU)         /* !< Sequencer 1 Result in FIFO mode */

/* ADC_ADCSEQ2FIFORESULT Bits */
/* ADC_ADCSEQ2FIFORESULT[SEQFIFORESULT] Bits */
#define ADC_ADCSEQ2FIFORESULT_SEQFIFORESULT_OFS  (0)                             /* !< SEQFIFORESULT Offset */
#define ADC_ADCSEQ2FIFORESULT_SEQFIFORESULT_MASK ((uint32_t)0xFFFFFFFFU)         /* !< Sequencer 2 Result in FIFO mode */

/* ADC_ADCSEQ3FIFORESULT Bits */
/* ADC_ADCSEQ3FIFORESULT[SEQFIFORESULT] Bits */
#define ADC_ADCSEQ3FIFORESULT_SEQFIFORESULT_OFS  (0)                             /* !< SEQFIFORESULT Offset */
#define ADC_ADCSEQ3FIFORESULT_SEQFIFORESULT_MASK ((uint32_t)0xFFFFFFFFU)         /* !< Sequencer 3 Result in FIFO mode */

/* ADC_ADCSEQ4FIFORESULT Bits */
/* ADC_ADCSEQ4FIFORESULT[SEQFIFORESULT] Bits */
#define ADC_ADCSEQ4FIFORESULT_SEQFIFORESULT_OFS  (0)                             /* !< SEQFIFORESULT Offset */
#define ADC_ADCSEQ4FIFORESULT_SEQFIFORESULT_MASK ((uint32_t)0xFFFFFFFFU)         /* !< Sequencer 4 Result in FIFO mode */

/* ADC_ADCSEQ1FIFOSTATUS Bits */
/* ADC_ADCSEQ1FIFOSTATUS[SEQFIFOVALID] Bits */
#define ADC_ADCSEQ1FIFOSTATUS_SEQFIFOVALID_OFS   (0)                             /* !< SEQFIFOVALID Offset */
#define ADC_ADCSEQ1FIFOSTATUS_SEQFIFOVALID_MASK  ((uint32_t)0x00000001U)         /* !< Sequencer 1 FIFO Valid */
/* ADC_ADCSEQ1FIFOSTATUS[SEQFIFOPENDREAD] Bits */
#define ADC_ADCSEQ1FIFOSTATUS_SEQFIFOPENDREAD_OFS (1)                             /* !< SEQFIFOPENDREAD Offset */
#define ADC_ADCSEQ1FIFOSTATUS_SEQFIFOPENDREAD_MASK ((uint32_t)0x0000001EU)         /* !< Sequencer 1 FIFO Pending reads */

/* ADC_ADCSEQ2FIFOSTATUS Bits */
/* ADC_ADCSEQ2FIFOSTATUS[SEQFIFOVALID] Bits */
#define ADC_ADCSEQ2FIFOSTATUS_SEQFIFOVALID_OFS   (0)                             /* !< SEQFIFOVALID Offset */
#define ADC_ADCSEQ2FIFOSTATUS_SEQFIFOVALID_MASK  ((uint32_t)0x00000001U)         /* !< Sequencer 2 FIFO Valid */
/* ADC_ADCSEQ2FIFOSTATUS[SEQFIFOPENDREAD] Bits */
#define ADC_ADCSEQ2FIFOSTATUS_SEQFIFOPENDREAD_OFS (1)                             /* !< SEQFIFOPENDREAD Offset */
#define ADC_ADCSEQ2FIFOSTATUS_SEQFIFOPENDREAD_MASK ((uint32_t)0x0000001EU)         /* !< Sequencer 2 FIFO Pending reads */

/* ADC_ADCSEQ3FIFOSTATUS Bits */
/* ADC_ADCSEQ3FIFOSTATUS[SEQFIFOVALID] Bits */
#define ADC_ADCSEQ3FIFOSTATUS_SEQFIFOVALID_OFS   (0)                             /* !< SEQFIFOVALID Offset */
#define ADC_ADCSEQ3FIFOSTATUS_SEQFIFOVALID_MASK  ((uint32_t)0x00000001U)         /* !< Sequencer 3 FIFO Valid */
/* ADC_ADCSEQ3FIFOSTATUS[SEQFIFOPENDREAD] Bits */
#define ADC_ADCSEQ3FIFOSTATUS_SEQFIFOPENDREAD_OFS (1)                             /* !< SEQFIFOPENDREAD Offset */
#define ADC_ADCSEQ3FIFOSTATUS_SEQFIFOPENDREAD_MASK ((uint32_t)0x0000001EU)         /* !< Sequencer 3 FIFO Pending reads */

/* ADC_ADCSEQ4FIFOSTATUS Bits */
/* ADC_ADCSEQ4FIFOSTATUS[SEQFIFOVALID] Bits */
#define ADC_ADCSEQ4FIFOSTATUS_SEQFIFOVALID_OFS   (0)                             /* !< SEQFIFOVALID Offset */
#define ADC_ADCSEQ4FIFOSTATUS_SEQFIFOVALID_MASK  ((uint32_t)0x00000001U)         /* !< Sequencer 4 FIFO Valid */
/* ADC_ADCSEQ4FIFOSTATUS[SEQFIFOPENDREAD] Bits */
#define ADC_ADCSEQ4FIFOSTATUS_SEQFIFOPENDREAD_OFS (1)                             /* !< SEQFIFOPENDREAD Offset */
#define ADC_ADCSEQ4FIFOSTATUS_SEQFIFOPENDREAD_MASK ((uint32_t)0x0000001EU)         /* !< Sequencer 4 FIFO Pending reads */

/* ADC_PWREN Bits */
/* ADC_PWREN[ENABLE] Bits */
#define ADC_PWREN_ENABLE_OFS                     (0)                             /* !< ENABLE Offset */
#define ADC_PWREN_ENABLE_MASK                    ((uint32_t)0x00000001U)         /* !< Power Enable */
#define ADC_PWREN_ENABLE_DISABLE                 ((uint32_t)0x00000000U)         /* !< Disable Power */
#define ADC_PWREN_ENABLE_ENABLE                  ((uint32_t)0x00000001U)         /* !< Enable Power */
/* ADC_PWREN[KEY] Bits */
#define ADC_PWREN_KEY_OFS                        (24)                            /* !< KEY Offset */
#define ADC_PWREN_KEY_MASK                       ((uint32_t)0xFF000000U)         /* !< KEY to allow Power State Change */
#define ADC_PWREN_KEY_UNLOCK_W                   ((uint32_t)0x26000000U)         /* !< KEY to allow write access to this
                                                                                    register */

/* ADC_RSTCTL Bits */
/* ADC_RSTCTL[RESETSTKYCLR] Bits */
#define ADC_RSTCTL_RESETSTKYCLR_OFS              (1)                             /* !< RESETSTKYCLR Offset */
#define ADC_RSTCTL_RESETSTKYCLR_MASK             ((uint32_t)0x00000002U)         /* !< Reset sticky bit clear */
#define ADC_RSTCTL_RESETSTKYCLR_NOP              ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define ADC_RSTCTL_RESETSTKYCLR_CLR              ((uint32_t)0x00000002U)         /* !< Clear reset sticky bit */
/* ADC_RSTCTL[RESETASSERT] Bits */
#define ADC_RSTCTL_RESETASSERT_OFS               (0)                             /* !< RESETASSERT Offset */
#define ADC_RSTCTL_RESETASSERT_MASK              ((uint32_t)0x00000001U)         /* !< Reset assertion to the peripheral */
#define ADC_RSTCTL_RESETASSERT_NOP               ((uint32_t)0x00000000U)         /* !< Writing 0 has no effect */
#define ADC_RSTCTL_RESETASSERT_ASSERT            ((uint32_t)0x00000001U)         /* !< Assert reset */
/* ADC_RSTCTL[KEY] Bits */
#define ADC_RSTCTL_KEY_OFS                       (24)                            /* !< KEY Offset */
#define ADC_RSTCTL_KEY_MASK                      ((uint32_t)0xFF000000U)         /* !< Unlock key */
#define ADC_RSTCTL_KEY_UNLOCK_W                  ((uint32_t)0xB1000000U)         /* !< KEY to allow write access to this
                                                                                    register */

/* ADC_STAT Bits */
/* ADC_STAT[RESETSTKYCLR] Bits */
#define ADC_STAT_RESETSTKYCLR_OFS                (16)                            /* !< RESETSTKYCLR Offset */
#define ADC_STAT_RESETSTKYCLR_MASK               ((uint32_t)0x00010000U)         /* !< Reset sticky bit */
#define ADC_STAT_RESETSTKYCLR_NORES              ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define ADC_STAT_RESETSTKYCLR_RESET              ((uint32_t)0x00010000U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */

/* ADC_ADCCTL1 Bits */
/* ADC_ADCCTL1[INTPULSEPOS] Bits */
#define ADC_ADCCTL1_INTPULSEPOS_OFS              (2)                             /* !< INTPULSEPOS Offset */
#define ADC_ADCCTL1_INTPULSEPOS_MASK             ((uint32_t)0x00000004U)         /* !< ADC Interrupt Pulse Position */
/* ADC_ADCCTL1[ADCPWDNZ] Bits */
#define ADC_ADCCTL1_ADCPWDNZ_OFS                 (7)                             /* !< ADCPWDNZ Offset */
#define ADC_ADCCTL1_ADCPWDNZ_MASK                ((uint32_t)0x00000080U)         /* !< ADC Power Down */
/* ADC_ADCCTL1[ADCBSYCHN] Bits */
#define ADC_ADCCTL1_ADCBSYCHN_OFS                (8)                             /* !< ADCBSYCHN Offset */
#define ADC_ADCCTL1_ADCBSYCHN_MASK               ((uint32_t)0x00000F00U)         /* !< ADC Busy Channel */
/* ADC_ADCCTL1[ADCBSY] Bits */
#define ADC_ADCCTL1_ADCBSY_OFS                   (13)                            /* !< ADCBSY Offset */
#define ADC_ADCCTL1_ADCBSY_MASK                  ((uint32_t)0x00002000U)         /* !< ADC Busy */

/* ADC_ADCCTL2 Bits */
/* ADC_ADCCTL2[PRESCALE] Bits */
#define ADC_ADCCTL2_PRESCALE_OFS                 (0)                             /* !< PRESCALE Offset */
#define ADC_ADCCTL2_PRESCALE_MASK                ((uint32_t)0x0000000FU)         /* !< ADC Clock Prescaler */

/* ADC_ADCINTSEL Bits */
/* ADC_ADCINTSEL[INT1SEL] Bits */
#define ADC_ADCINTSEL_INT1SEL_OFS                (0)                             /* !< INT1SEL Offset */
#define ADC_ADCINTSEL_INT1SEL_MASK               ((uint32_t)0x0000000FU)         /* !< ADCINT1 EOC Source Select */
/* ADC_ADCINTSEL[INT1CONT] Bits */
#define ADC_ADCINTSEL_INT1CONT_OFS               (6)                             /* !< INT1CONT Offset */
#define ADC_ADCINTSEL_INT1CONT_MASK              ((uint32_t)0x00000040U)         /* !< ADCINT1 Continue to Interrupt Mode */
/* ADC_ADCINTSEL[INT1E] Bits */
#define ADC_ADCINTSEL_INT1E_OFS                  (7)                             /* !< INT1E Offset */
#define ADC_ADCINTSEL_INT1E_MASK                 ((uint32_t)0x00000080U)         /* !< ADCINT1 Interrupt Enable */
/* ADC_ADCINTSEL[INT2SEL] Bits */
#define ADC_ADCINTSEL_INT2SEL_OFS                (8)                             /* !< INT2SEL Offset */
#define ADC_ADCINTSEL_INT2SEL_MASK               ((uint32_t)0x00000F00U)         /* !< ADCINT2 EOC Source Select */
/* ADC_ADCINTSEL[INT2CONT] Bits */
#define ADC_ADCINTSEL_INT2CONT_OFS               (14)                            /* !< INT2CONT Offset */
#define ADC_ADCINTSEL_INT2CONT_MASK              ((uint32_t)0x00004000U)         /* !< ADCINT2 Continue to Interrupt Mode */
/* ADC_ADCINTSEL[INT2E] Bits */
#define ADC_ADCINTSEL_INT2E_OFS                  (15)                            /* !< INT2E Offset */
#define ADC_ADCINTSEL_INT2E_MASK                 ((uint32_t)0x00008000U)         /* !< ADCINT2 Interrupt Enable */
/* ADC_ADCINTSEL[INT3SEL] Bits */
#define ADC_ADCINTSEL_INT3SEL_OFS                (16)                            /* !< INT3SEL Offset */
#define ADC_ADCINTSEL_INT3SEL_MASK               ((uint32_t)0x000F0000U)         /* !< ADCINT3 EOC Source Select */
/* ADC_ADCINTSEL[INT3CONT] Bits */
#define ADC_ADCINTSEL_INT3CONT_OFS               (22)                            /* !< INT3CONT Offset */
#define ADC_ADCINTSEL_INT3CONT_MASK              ((uint32_t)0x00400000U)         /* !< ADCINT3 Continue to Interrupt Mode */
/* ADC_ADCINTSEL[INT3E] Bits */
#define ADC_ADCINTSEL_INT3E_OFS                  (23)                            /* !< INT3E Offset */
#define ADC_ADCINTSEL_INT3E_MASK                 ((uint32_t)0x00800000U)         /* !< ADCINT3 Interrupt Enable */
/* ADC_ADCINTSEL[INT4SEL] Bits */
#define ADC_ADCINTSEL_INT4SEL_OFS                (24)                            /* !< INT4SEL Offset */
#define ADC_ADCINTSEL_INT4SEL_MASK               ((uint32_t)0x0F000000U)         /* !< ADCINT4 EOC Source Select */
/* ADC_ADCINTSEL[INT4CONT] Bits */
#define ADC_ADCINTSEL_INT4CONT_OFS               (30)                            /* !< INT4CONT Offset */
#define ADC_ADCINTSEL_INT4CONT_MASK              ((uint32_t)0x40000000U)         /* !< ADCINT4 Continue to Interrupt Mode */
/* ADC_ADCINTSEL[INT4E] Bits */
#define ADC_ADCINTSEL_INT4E_OFS                  (31)                            /* !< INT4E Offset */
#define ADC_ADCINTSEL_INT4E_MASK                 ((uint32_t)0x80000000U)         /* !< ADCINT4 Interrupt Enable */

/* ADC_ADCDMAINTSEL Bits */
/* ADC_ADCDMAINTSEL[DMAINT1SEL] Bits */
#define ADC_ADCDMAINTSEL_DMAINT1SEL_OFS          (0)                             /* !< DMAINT1SEL Offset */
#define ADC_ADCDMAINTSEL_DMAINT1SEL_MASK         ((uint32_t)0x0000000FU)         /* !< ADCDMAINT1 EOC Source Select */
/* ADC_ADCDMAINTSEL[DMAINT1CONT] Bits */
#define ADC_ADCDMAINTSEL_DMAINT1CONT_OFS         (6)                             /* !< DMAINT1CONT Offset */
#define ADC_ADCDMAINTSEL_DMAINT1CONT_MASK        ((uint32_t)0x00000040U)         /* !< ADCDMAINT1 Continue to Interrupt
                                                                                    Mode */
/* ADC_ADCDMAINTSEL[DMAINT1E] Bits */
#define ADC_ADCDMAINTSEL_DMAINT1E_OFS            (7)                             /* !< DMAINT1E Offset */
#define ADC_ADCDMAINTSEL_DMAINT1E_MASK           ((uint32_t)0x00000080U)         /* !< ADCDMAINT1 Interrupt Enable */
/* ADC_ADCDMAINTSEL[DMAINT2SEL] Bits */
#define ADC_ADCDMAINTSEL_DMAINT2SEL_OFS          (8)                             /* !< DMAINT2SEL Offset */
#define ADC_ADCDMAINTSEL_DMAINT2SEL_MASK         ((uint32_t)0x00000F00U)         /* !< ADCDMAINT2 EOC Source Select */
/* ADC_ADCDMAINTSEL[DMAINT2CONT] Bits */
#define ADC_ADCDMAINTSEL_DMAINT2CONT_OFS         (14)                            /* !< DMAINT2CONT Offset */
#define ADC_ADCDMAINTSEL_DMAINT2CONT_MASK        ((uint32_t)0x00004000U)         /* !< ADCDMAINT2 Continue to Interrupt
                                                                                    Mode */
/* ADC_ADCDMAINTSEL[DMAINT2E] Bits */
#define ADC_ADCDMAINTSEL_DMAINT2E_OFS            (15)                            /* !< DMAINT2E Offset */
#define ADC_ADCDMAINTSEL_DMAINT2E_MASK           ((uint32_t)0x00008000U)         /* !< ADCDMAINT2 Interrupt Enable */
/* ADC_ADCDMAINTSEL[DMAINT3SEL] Bits */
#define ADC_ADCDMAINTSEL_DMAINT3SEL_OFS          (16)                            /* !< DMAINT3SEL Offset */
#define ADC_ADCDMAINTSEL_DMAINT3SEL_MASK         ((uint32_t)0x000F0000U)         /* !< ADCDMAINT3 EOC Source Select */
/* ADC_ADCDMAINTSEL[DMAINT3CONT] Bits */
#define ADC_ADCDMAINTSEL_DMAINT3CONT_OFS         (22)                            /* !< DMAINT3CONT Offset */
#define ADC_ADCDMAINTSEL_DMAINT3CONT_MASK        ((uint32_t)0x00400000U)         /* !< ADCDMAINT3 Continue to Interrupt
                                                                                    Mode */
/* ADC_ADCDMAINTSEL[DMAINT3E] Bits */
#define ADC_ADCDMAINTSEL_DMAINT3E_OFS            (23)                            /* !< DMAINT3E Offset */
#define ADC_ADCDMAINTSEL_DMAINT3E_MASK           ((uint32_t)0x00800000U)         /* !< ADCDMAINT3 Interrupt Enable */
/* ADC_ADCDMAINTSEL[DMAINT4SEL] Bits */
#define ADC_ADCDMAINTSEL_DMAINT4SEL_OFS          (24)                            /* !< DMAINT4SEL Offset */
#define ADC_ADCDMAINTSEL_DMAINT4SEL_MASK         ((uint32_t)0x0F000000U)         /* !< ADCDMAINT4 EOC Source Select */
/* ADC_ADCDMAINTSEL[DMAINT4CONT] Bits */
#define ADC_ADCDMAINTSEL_DMAINT4CONT_OFS         (30)                            /* !< DMAINT4CONT Offset */
#define ADC_ADCDMAINTSEL_DMAINT4CONT_MASK        ((uint32_t)0x40000000U)         /* !< ADCDMAINT4 Continue to Interrupt
                                                                                    Mode */
/* ADC_ADCDMAINTSEL[DMAINT4E] Bits */
#define ADC_ADCDMAINTSEL_DMAINT4E_OFS            (31)                            /* !< DMAINT4E Offset */
#define ADC_ADCDMAINTSEL_DMAINT4E_MASK           ((uint32_t)0x80000000U)         /* !< ADCDMAINT4 Interrupt Enable */

/* ADC_ADCRAWINTFLG Bits */
/* ADC_ADCRAWINTFLG[ADCRAWINT1] Bits */
#define ADC_ADCRAWINTFLG_ADCRAWINT1_OFS          (0)                             /* !< ADCRAWINT1 Offset */
#define ADC_ADCRAWINTFLG_ADCRAWINT1_MASK         ((uint32_t)0x00000001U)         /* !< ADC Raw Interrupt 1 Flag */
/* ADC_ADCRAWINTFLG[ADCRAWINT2] Bits */
#define ADC_ADCRAWINTFLG_ADCRAWINT2_OFS          (1)                             /* !< ADCRAWINT2 Offset */
#define ADC_ADCRAWINTFLG_ADCRAWINT2_MASK         ((uint32_t)0x00000002U)         /* !< ADC Raw Interrupt 2 Flag */
/* ADC_ADCRAWINTFLG[ADCRAWINT3] Bits */
#define ADC_ADCRAWINTFLG_ADCRAWINT3_OFS          (2)                             /* !< ADCRAWINT3 Offset */
#define ADC_ADCRAWINTFLG_ADCRAWINT3_MASK         ((uint32_t)0x00000004U)         /* !< ADC Raw Interrupt 3 Flag */
/* ADC_ADCRAWINTFLG[ADCRAWINT4] Bits */
#define ADC_ADCRAWINTFLG_ADCRAWINT4_OFS          (3)                             /* !< ADCRAWINT4 Offset */
#define ADC_ADCRAWINTFLG_ADCRAWINT4_MASK         ((uint32_t)0x00000008U)         /* !< ADC Raw Interrupt 4 Flag */
/* ADC_ADCRAWINTFLG[ADCDMARAWINT1] Bits */
#define ADC_ADCRAWINTFLG_ADCDMARAWINT1_OFS       (16)                            /* !< ADCDMARAWINT1 Offset */
#define ADC_ADCRAWINTFLG_ADCDMARAWINT1_MASK      ((uint32_t)0x00010000U)         /* !< ADC DMA Raw Interrupt 1 Flag */
/* ADC_ADCRAWINTFLG[ADCDMARAWINT2] Bits */
#define ADC_ADCRAWINTFLG_ADCDMARAWINT2_OFS       (17)                            /* !< ADCDMARAWINT2 Offset */
#define ADC_ADCRAWINTFLG_ADCDMARAWINT2_MASK      ((uint32_t)0x00020000U)         /* !< ADC DMA Raw Interrupt 2 Flag */
/* ADC_ADCRAWINTFLG[ADCDMARAWINT3] Bits */
#define ADC_ADCRAWINTFLG_ADCDMARAWINT3_OFS       (18)                            /* !< ADCDMARAWINT3 Offset */
#define ADC_ADCRAWINTFLG_ADCDMARAWINT3_MASK      ((uint32_t)0x00040000U)         /* !< ADC DMA Raw Interrupt 3 Flag */
/* ADC_ADCRAWINTFLG[ADCDMARAWINT4] Bits */
#define ADC_ADCRAWINTFLG_ADCDMARAWINT4_OFS       (19)                            /* !< ADCDMARAWINT4 Offset */
#define ADC_ADCRAWINTFLG_ADCDMARAWINT4_MASK      ((uint32_t)0x00080000U)         /* !< ADC DMA Raw Interrupt 4 Flag */

/* ADC_ADCINTFLG Bits */
/* ADC_ADCINTFLG[ADCINT1] Bits */
#define ADC_ADCINTFLG_ADCINT1_OFS                (0)                             /* !< ADCINT1 Offset */
#define ADC_ADCINTFLG_ADCINT1_MASK               ((uint32_t)0x00000001U)         /* !< ADC Interrupt 1 Flag */
/* ADC_ADCINTFLG[ADCINT2] Bits */
#define ADC_ADCINTFLG_ADCINT2_OFS                (1)                             /* !< ADCINT2 Offset */
#define ADC_ADCINTFLG_ADCINT2_MASK               ((uint32_t)0x00000002U)         /* !< ADC Interrupt 2 Flag */
/* ADC_ADCINTFLG[ADCINT3] Bits */
#define ADC_ADCINTFLG_ADCINT3_OFS                (2)                             /* !< ADCINT3 Offset */
#define ADC_ADCINTFLG_ADCINT3_MASK               ((uint32_t)0x00000004U)         /* !< ADC Interrupt 3 Flag */
/* ADC_ADCINTFLG[ADCINT4] Bits */
#define ADC_ADCINTFLG_ADCINT4_OFS                (3)                             /* !< ADCINT4 Offset */
#define ADC_ADCINTFLG_ADCINT4_MASK               ((uint32_t)0x00000008U)         /* !< ADC Interrupt 4 Flag */
/* ADC_ADCINTFLG[ADCINT1RESULT] Bits */
#define ADC_ADCINTFLG_ADCINT1RESULT_OFS          (8)                             /* !< ADCINT1RESULT Offset */
#define ADC_ADCINTFLG_ADCINT1RESULT_MASK         ((uint32_t)0x00000100U)         /* !< ADC Interrupt 1 Results Ready */
/* ADC_ADCINTFLG[ADCINT2RESULT] Bits */
#define ADC_ADCINTFLG_ADCINT2RESULT_OFS          (9)                             /* !< ADCINT2RESULT Offset */
#define ADC_ADCINTFLG_ADCINT2RESULT_MASK         ((uint32_t)0x00000200U)         /* !< ADC Interrupt 2 Results Ready */
/* ADC_ADCINTFLG[ADCINT3RESULT] Bits */
#define ADC_ADCINTFLG_ADCINT3RESULT_OFS          (10)                            /* !< ADCINT3RESULT Offset */
#define ADC_ADCINTFLG_ADCINT3RESULT_MASK         ((uint32_t)0x00000400U)         /* !< ADC Interrupt 3 Results Ready */
/* ADC_ADCINTFLG[ADCINT4RESULT] Bits */
#define ADC_ADCINTFLG_ADCINT4RESULT_OFS          (11)                            /* !< ADCINT4RESULT Offset */
#define ADC_ADCINTFLG_ADCINT4RESULT_MASK         ((uint32_t)0x00000800U)         /* !< ADC Interrupt 4 Results Ready */
/* ADC_ADCINTFLG[ADCDMAINT1] Bits */
#define ADC_ADCINTFLG_ADCDMAINT1_OFS             (16)                            /* !< ADCDMAINT1 Offset */
#define ADC_ADCINTFLG_ADCDMAINT1_MASK            ((uint32_t)0x00010000U)         /* !< ADC DMA Interrupt 1 Flag */
/* ADC_ADCINTFLG[ADCDMAINT2] Bits */
#define ADC_ADCINTFLG_ADCDMAINT2_OFS             (17)                            /* !< ADCDMAINT2 Offset */
#define ADC_ADCINTFLG_ADCDMAINT2_MASK            ((uint32_t)0x00020000U)         /* !< ADC DMA Interrupt 2 Flag */
/* ADC_ADCINTFLG[ADCDMAINT3] Bits */
#define ADC_ADCINTFLG_ADCDMAINT3_OFS             (18)                            /* !< ADCDMAINT3 Offset */
#define ADC_ADCINTFLG_ADCDMAINT3_MASK            ((uint32_t)0x00040000U)         /* !< ADC DMA Interrupt 3 Flag */
/* ADC_ADCINTFLG[ADCDMAINT4] Bits */
#define ADC_ADCINTFLG_ADCDMAINT4_OFS             (19)                            /* !< ADCDMAINT4 Offset */
#define ADC_ADCINTFLG_ADCDMAINT4_MASK            ((uint32_t)0x00080000U)         /* !< ADC DMA Interrupt 4 Flag */

/* ADC_ADCINTFLGFRC Bits */
/* ADC_ADCINTFLGFRC[ADCINT1] Bits */
#define ADC_ADCINTFLGFRC_ADCINT1_OFS             (0)                             /* !< ADCINT1 Offset */
#define ADC_ADCINTFLGFRC_ADCINT1_MASK            ((uint32_t)0x00000001U)         /* !< ADC Interrupt 1 Flag Force */
/* ADC_ADCINTFLGFRC[ADCINT2] Bits */
#define ADC_ADCINTFLGFRC_ADCINT2_OFS             (1)                             /* !< ADCINT2 Offset */
#define ADC_ADCINTFLGFRC_ADCINT2_MASK            ((uint32_t)0x00000002U)         /* !< ADC Interrupt 2 Flag Force */
/* ADC_ADCINTFLGFRC[ADCINT3] Bits */
#define ADC_ADCINTFLGFRC_ADCINT3_OFS             (2)                             /* !< ADCINT3 Offset */
#define ADC_ADCINTFLGFRC_ADCINT3_MASK            ((uint32_t)0x00000004U)         /* !< ADC Interrupt 3 Flag Force */
/* ADC_ADCINTFLGFRC[ADCINT4] Bits */
#define ADC_ADCINTFLGFRC_ADCINT4_OFS             (3)                             /* !< ADCINT4 Offset */
#define ADC_ADCINTFLGFRC_ADCINT4_MASK            ((uint32_t)0x00000008U)         /* !< ADC Interrupt 4 Flag Force */
/* ADC_ADCINTFLGFRC[ADCDMAINT1] Bits */
#define ADC_ADCINTFLGFRC_ADCDMAINT1_OFS          (16)                            /* !< ADCDMAINT1 Offset */
#define ADC_ADCINTFLGFRC_ADCDMAINT1_MASK         ((uint32_t)0x00010000U)         /* !< ADC DMA Interrupt 1 Flag Force */
/* ADC_ADCINTFLGFRC[ADCDMAINT2] Bits */
#define ADC_ADCINTFLGFRC_ADCDMAINT2_OFS          (17)                            /* !< ADCDMAINT2 Offset */
#define ADC_ADCINTFLGFRC_ADCDMAINT2_MASK         ((uint32_t)0x00020000U)         /* !< ADC DMA Interrupt 2 Flag Force */
/* ADC_ADCINTFLGFRC[ADCDMAINT3] Bits */
#define ADC_ADCINTFLGFRC_ADCDMAINT3_OFS          (18)                            /* !< ADCDMAINT3 Offset */
#define ADC_ADCINTFLGFRC_ADCDMAINT3_MASK         ((uint32_t)0x00040000U)         /* !< ADC DMA Interrupt 3 Flag Force */
/* ADC_ADCINTFLGFRC[ADCDMAINT4] Bits */
#define ADC_ADCINTFLGFRC_ADCDMAINT4_OFS          (19)                            /* !< ADCDMAINT4 Offset */
#define ADC_ADCINTFLGFRC_ADCDMAINT4_MASK         ((uint32_t)0x00080000U)         /* !< ADC DMA Interrupt 4 Flag Force */

/* ADC_ADCINTFLGCLR Bits */
/* ADC_ADCINTFLGCLR[ADCINT1] Bits */
#define ADC_ADCINTFLGCLR_ADCINT1_OFS             (0)                             /* !< ADCINT1 Offset */
#define ADC_ADCINTFLGCLR_ADCINT1_MASK            ((uint32_t)0x00000001U)         /* !< ADC Interrupt 1 Flag Clear */
/* ADC_ADCINTFLGCLR[ADCINT2] Bits */
#define ADC_ADCINTFLGCLR_ADCINT2_OFS             (1)                             /* !< ADCINT2 Offset */
#define ADC_ADCINTFLGCLR_ADCINT2_MASK            ((uint32_t)0x00000002U)         /* !< ADC Interrupt 2 Flag Clear */
/* ADC_ADCINTFLGCLR[ADCINT3] Bits */
#define ADC_ADCINTFLGCLR_ADCINT3_OFS             (2)                             /* !< ADCINT3 Offset */
#define ADC_ADCINTFLGCLR_ADCINT3_MASK            ((uint32_t)0x00000004U)         /* !< ADC Interrupt 3 Flag Clear */
/* ADC_ADCINTFLGCLR[ADCINT4] Bits */
#define ADC_ADCINTFLGCLR_ADCINT4_OFS             (3)                             /* !< ADCINT4 Offset */
#define ADC_ADCINTFLGCLR_ADCINT4_MASK            ((uint32_t)0x00000008U)         /* !< ADC Interrupt 4 Flag Clear */
/* ADC_ADCINTFLGCLR[ADCDMAINT1] Bits */
#define ADC_ADCINTFLGCLR_ADCDMAINT1_OFS          (16)                            /* !< ADCDMAINT1 Offset */
#define ADC_ADCINTFLGCLR_ADCDMAINT1_MASK         ((uint32_t)0x00010000U)         /* !< ADC DMA Interrupt 1 Flag Clear */
/* ADC_ADCINTFLGCLR[ADCDMAINT2] Bits */
#define ADC_ADCINTFLGCLR_ADCDMAINT2_OFS          (17)                            /* !< ADCDMAINT2 Offset */
#define ADC_ADCINTFLGCLR_ADCDMAINT2_MASK         ((uint32_t)0x00020000U)         /* !< ADC DMA Interrupt 2 Flag Clear */
/* ADC_ADCINTFLGCLR[ADCDMAINT3] Bits */
#define ADC_ADCINTFLGCLR_ADCDMAINT3_OFS          (18)                            /* !< ADCDMAINT3 Offset */
#define ADC_ADCINTFLGCLR_ADCDMAINT3_MASK         ((uint32_t)0x00040000U)         /* !< ADC DMA Interrupt 3 Flag Clear */
/* ADC_ADCINTFLGCLR[ADCDMAINT4] Bits */
#define ADC_ADCINTFLGCLR_ADCDMAINT4_OFS          (19)                            /* !< ADCDMAINT4 Offset */
#define ADC_ADCINTFLGCLR_ADCDMAINT4_MASK         ((uint32_t)0x00080000U)         /* !< ADC DMA Interrupt 4 Flag Clear */

/* ADC_ADCINTOVF Bits */
/* ADC_ADCINTOVF[ADCINT1OVF] Bits */
#define ADC_ADCINTOVF_ADCINT1OVF_OFS             (0)                             /* !< ADCINT1OVF Offset */
#define ADC_ADCINTOVF_ADCINT1OVF_MASK            ((uint32_t)0x00000001U)         /* !< ADC Interrupt 1 Overflow Flags */
/* ADC_ADCINTOVF[ADCINT2OVF] Bits */
#define ADC_ADCINTOVF_ADCINT2OVF_OFS             (1)                             /* !< ADCINT2OVF Offset */
#define ADC_ADCINTOVF_ADCINT2OVF_MASK            ((uint32_t)0x00000002U)         /* !< ADC Interrupt 2 Overflow Flags */
/* ADC_ADCINTOVF[ADCINT3OVF] Bits */
#define ADC_ADCINTOVF_ADCINT3OVF_OFS             (2)                             /* !< ADCINT3OVF Offset */
#define ADC_ADCINTOVF_ADCINT3OVF_MASK            ((uint32_t)0x00000004U)         /* !< ADC Interrupt 3 Overflow Flags */
/* ADC_ADCINTOVF[ADCINT4OVF] Bits */
#define ADC_ADCINTOVF_ADCINT4OVF_OFS             (3)                             /* !< ADCINT4OVF Offset */
#define ADC_ADCINTOVF_ADCINT4OVF_MASK            ((uint32_t)0x00000008U)         /* !< ADC Interrupt 4 Overflow Flags */
/* ADC_ADCINTOVF[ADCDMAINT1OVF] Bits */
#define ADC_ADCINTOVF_ADCDMAINT1OVF_OFS          (16)                            /* !< ADCDMAINT1OVF Offset */
#define ADC_ADCINTOVF_ADCDMAINT1OVF_MASK         ((uint32_t)0x00010000U)         /* !< ADC DMA Interrupt 1 Overflow Flags */
/* ADC_ADCINTOVF[ADCDMAINT2OVF] Bits */
#define ADC_ADCINTOVF_ADCDMAINT2OVF_OFS          (17)                            /* !< ADCDMAINT2OVF Offset */
#define ADC_ADCINTOVF_ADCDMAINT2OVF_MASK         ((uint32_t)0x00020000U)         /* !< ADC DMA Interrupt 2 Overflow Flags */
/* ADC_ADCINTOVF[ADCDMAINT3OVF] Bits */
#define ADC_ADCINTOVF_ADCDMAINT3OVF_OFS          (18)                            /* !< ADCDMAINT3OVF Offset */
#define ADC_ADCINTOVF_ADCDMAINT3OVF_MASK         ((uint32_t)0x00040000U)         /* !< ADC DMA Interrupt 3 Overflow Flags */
/* ADC_ADCINTOVF[ADCDMAINT4OVF] Bits */
#define ADC_ADCINTOVF_ADCDMAINT4OVF_OFS          (19)                            /* !< ADCDMAINT4OVF Offset */
#define ADC_ADCINTOVF_ADCDMAINT4OVF_MASK         ((uint32_t)0x00080000U)         /* !< ADC DMA Interrupt 4 Overflow Flags */

/* ADC_ADCINTOVFCLR Bits */
/* ADC_ADCINTOVFCLR[ADCINT1OVF] Bits */
#define ADC_ADCINTOVFCLR_ADCINT1OVF_OFS          (0)                             /* !< ADCINT1OVF Offset */
#define ADC_ADCINTOVFCLR_ADCINT1OVF_MASK         ((uint32_t)0x00000001U)         /* !< ADC Interrupt 1 Overflow Clear Bits */
/* ADC_ADCINTOVFCLR[ADCINT2OVF] Bits */
#define ADC_ADCINTOVFCLR_ADCINT2OVF_OFS          (1)                             /* !< ADCINT2OVF Offset */
#define ADC_ADCINTOVFCLR_ADCINT2OVF_MASK         ((uint32_t)0x00000002U)         /* !< ADC Interrupt 2 Overflow Clear Bits */
/* ADC_ADCINTOVFCLR[ADCINT3OVF] Bits */
#define ADC_ADCINTOVFCLR_ADCINT3OVF_OFS          (2)                             /* !< ADCINT3OVF Offset */
#define ADC_ADCINTOVFCLR_ADCINT3OVF_MASK         ((uint32_t)0x00000004U)         /* !< ADC Interrupt 3 Overflow Clear Bits */
/* ADC_ADCINTOVFCLR[ADCINT4OVF] Bits */
#define ADC_ADCINTOVFCLR_ADCINT4OVF_OFS          (3)                             /* !< ADCINT4OVF Offset */
#define ADC_ADCINTOVFCLR_ADCINT4OVF_MASK         ((uint32_t)0x00000008U)         /* !< ADC Interrupt 4 Overflow Clear Bits */
/* ADC_ADCINTOVFCLR[ADCDMAINT1OVF] Bits */
#define ADC_ADCINTOVFCLR_ADCDMAINT1OVF_OFS       (16)                            /* !< ADCDMAINT1OVF Offset */
#define ADC_ADCINTOVFCLR_ADCDMAINT1OVF_MASK      ((uint32_t)0x00010000U)         /* !< ADC DMA Interrupt 1 Overflow Clear
                                                                                    Bits */
/* ADC_ADCINTOVFCLR[ADCDMAINT2OVF] Bits */
#define ADC_ADCINTOVFCLR_ADCDMAINT2OVF_OFS       (17)                            /* !< ADCDMAINT2OVF Offset */
#define ADC_ADCINTOVFCLR_ADCDMAINT2OVF_MASK      ((uint32_t)0x00020000U)         /* !< ADC DMA Interrupt 2 Overflow Clear
                                                                                    Bits */
/* ADC_ADCINTOVFCLR[ADCDMAINT3OVF] Bits */
#define ADC_ADCINTOVFCLR_ADCDMAINT3OVF_OFS       (18)                            /* !< ADCDMAINT3OVF Offset */
#define ADC_ADCINTOVFCLR_ADCDMAINT3OVF_MASK      ((uint32_t)0x00040000U)         /* !< ADC DMA Interrupt 3 Overflow Clear
                                                                                    Bits */
/* ADC_ADCINTOVFCLR[ADCDMAINT4OVF] Bits */
#define ADC_ADCINTOVFCLR_ADCDMAINT4OVF_OFS       (19)                            /* !< ADCDMAINT4OVF Offset */
#define ADC_ADCINTOVFCLR_ADCDMAINT4OVF_MASK      ((uint32_t)0x00080000U)         /* !< ADC DMA Interrupt 4 Overflow Clear
                                                                                    Bits */

/* ADC_ADCSOCFLG1 Bits */
/* ADC_ADCSOCFLG1[SOC0] Bits */
#define ADC_ADCSOCFLG1_SOC0_OFS                  (0)                             /* !< SOC0 Offset */
#define ADC_ADCSOCFLG1_SOC0_MASK                 ((uint32_t)0x00000001U)         /* !< SOC0 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC1] Bits */
#define ADC_ADCSOCFLG1_SOC1_OFS                  (1)                             /* !< SOC1 Offset */
#define ADC_ADCSOCFLG1_SOC1_MASK                 ((uint32_t)0x00000002U)         /* !< SOC1 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC2] Bits */
#define ADC_ADCSOCFLG1_SOC2_OFS                  (2)                             /* !< SOC2 Offset */
#define ADC_ADCSOCFLG1_SOC2_MASK                 ((uint32_t)0x00000004U)         /* !< SOC2 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC3] Bits */
#define ADC_ADCSOCFLG1_SOC3_OFS                  (3)                             /* !< SOC3 Offset */
#define ADC_ADCSOCFLG1_SOC3_MASK                 ((uint32_t)0x00000008U)         /* !< SOC3 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC4] Bits */
#define ADC_ADCSOCFLG1_SOC4_OFS                  (4)                             /* !< SOC4 Offset */
#define ADC_ADCSOCFLG1_SOC4_MASK                 ((uint32_t)0x00000010U)         /* !< SOC4 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC5] Bits */
#define ADC_ADCSOCFLG1_SOC5_OFS                  (5)                             /* !< SOC5 Offset */
#define ADC_ADCSOCFLG1_SOC5_MASK                 ((uint32_t)0x00000020U)         /* !< SOC5 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC6] Bits */
#define ADC_ADCSOCFLG1_SOC6_OFS                  (6)                             /* !< SOC6 Offset */
#define ADC_ADCSOCFLG1_SOC6_MASK                 ((uint32_t)0x00000040U)         /* !< SOC6 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC7] Bits */
#define ADC_ADCSOCFLG1_SOC7_OFS                  (7)                             /* !< SOC7 Offset */
#define ADC_ADCSOCFLG1_SOC7_MASK                 ((uint32_t)0x00000080U)         /* !< SOC7 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC8] Bits */
#define ADC_ADCSOCFLG1_SOC8_OFS                  (8)                             /* !< SOC8 Offset */
#define ADC_ADCSOCFLG1_SOC8_MASK                 ((uint32_t)0x00000100U)         /* !< SOC8 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC9] Bits */
#define ADC_ADCSOCFLG1_SOC9_OFS                  (9)                             /* !< SOC9 Offset */
#define ADC_ADCSOCFLG1_SOC9_MASK                 ((uint32_t)0x00000200U)         /* !< SOC9 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC10] Bits */
#define ADC_ADCSOCFLG1_SOC10_OFS                 (10)                            /* !< SOC10 Offset */
#define ADC_ADCSOCFLG1_SOC10_MASK                ((uint32_t)0x00000400U)         /* !< SOC10 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC11] Bits */
#define ADC_ADCSOCFLG1_SOC11_OFS                 (11)                            /* !< SOC11 Offset */
#define ADC_ADCSOCFLG1_SOC11_MASK                ((uint32_t)0x00000800U)         /* !< SOC11 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC12] Bits */
#define ADC_ADCSOCFLG1_SOC12_OFS                 (12)                            /* !< SOC12 Offset */
#define ADC_ADCSOCFLG1_SOC12_MASK                ((uint32_t)0x00001000U)         /* !< SOC12 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC13] Bits */
#define ADC_ADCSOCFLG1_SOC13_OFS                 (13)                            /* !< SOC13 Offset */
#define ADC_ADCSOCFLG1_SOC13_MASK                ((uint32_t)0x00002000U)         /* !< SOC13 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC14] Bits */
#define ADC_ADCSOCFLG1_SOC14_OFS                 (14)                            /* !< SOC14 Offset */
#define ADC_ADCSOCFLG1_SOC14_MASK                ((uint32_t)0x00004000U)         /* !< SOC14 Start of Conversion Flag */
/* ADC_ADCSOCFLG1[SOC15] Bits */
#define ADC_ADCSOCFLG1_SOC15_OFS                 (15)                            /* !< SOC15 Offset */
#define ADC_ADCSOCFLG1_SOC15_MASK                ((uint32_t)0x00008000U)         /* !< SOC15 Start of Conversion Flag */

/* ADC_ADCSOCOVF1 Bits */
/* ADC_ADCSOCOVF1[SOC0OVF] Bits */
#define ADC_ADCSOCOVF1_SOC0OVF_OFS               (0)                             /* !< SOC0OVF Offset */
#define ADC_ADCSOCOVF1_SOC0OVF_MASK              ((uint32_t)0x00000001U)         /* !< SOC0 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC1OVF] Bits */
#define ADC_ADCSOCOVF1_SOC1OVF_OFS               (1)                             /* !< SOC1OVF Offset */
#define ADC_ADCSOCOVF1_SOC1OVF_MASK              ((uint32_t)0x00000002U)         /* !< SOC1 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC2OVF] Bits */
#define ADC_ADCSOCOVF1_SOC2OVF_OFS               (2)                             /* !< SOC2OVF Offset */
#define ADC_ADCSOCOVF1_SOC2OVF_MASK              ((uint32_t)0x00000004U)         /* !< SOC2 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC3OVF] Bits */
#define ADC_ADCSOCOVF1_SOC3OVF_OFS               (3)                             /* !< SOC3OVF Offset */
#define ADC_ADCSOCOVF1_SOC3OVF_MASK              ((uint32_t)0x00000008U)         /* !< SOC3 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC4OVF] Bits */
#define ADC_ADCSOCOVF1_SOC4OVF_OFS               (4)                             /* !< SOC4OVF Offset */
#define ADC_ADCSOCOVF1_SOC4OVF_MASK              ((uint32_t)0x00000010U)         /* !< SOC4 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC5OVF] Bits */
#define ADC_ADCSOCOVF1_SOC5OVF_OFS               (5)                             /* !< SOC5OVF Offset */
#define ADC_ADCSOCOVF1_SOC5OVF_MASK              ((uint32_t)0x00000020U)         /* !< SOC5 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC6OVF] Bits */
#define ADC_ADCSOCOVF1_SOC6OVF_OFS               (6)                             /* !< SOC6OVF Offset */
#define ADC_ADCSOCOVF1_SOC6OVF_MASK              ((uint32_t)0x00000040U)         /* !< SOC6 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC7OVF] Bits */
#define ADC_ADCSOCOVF1_SOC7OVF_OFS               (7)                             /* !< SOC7OVF Offset */
#define ADC_ADCSOCOVF1_SOC7OVF_MASK              ((uint32_t)0x00000080U)         /* !< SOC7 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC8OVF] Bits */
#define ADC_ADCSOCOVF1_SOC8OVF_OFS               (8)                             /* !< SOC8OVF Offset */
#define ADC_ADCSOCOVF1_SOC8OVF_MASK              ((uint32_t)0x00000100U)         /* !< SOC8 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC9OVF] Bits */
#define ADC_ADCSOCOVF1_SOC9OVF_OFS               (9)                             /* !< SOC9OVF Offset */
#define ADC_ADCSOCOVF1_SOC9OVF_MASK              ((uint32_t)0x00000200U)         /* !< SOC9 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC10OVF] Bits */
#define ADC_ADCSOCOVF1_SOC10OVF_OFS              (10)                            /* !< SOC10OVF Offset */
#define ADC_ADCSOCOVF1_SOC10OVF_MASK             ((uint32_t)0x00000400U)         /* !< SOC10 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC11OVF] Bits */
#define ADC_ADCSOCOVF1_SOC11OVF_OFS              (11)                            /* !< SOC11OVF Offset */
#define ADC_ADCSOCOVF1_SOC11OVF_MASK             ((uint32_t)0x00000800U)         /* !< SOC11 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC12OVF] Bits */
#define ADC_ADCSOCOVF1_SOC12OVF_OFS              (12)                            /* !< SOC12OVF Offset */
#define ADC_ADCSOCOVF1_SOC12OVF_MASK             ((uint32_t)0x00001000U)         /* !< SOC12 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC13OVF] Bits */
#define ADC_ADCSOCOVF1_SOC13OVF_OFS              (13)                            /* !< SOC13OVF Offset */
#define ADC_ADCSOCOVF1_SOC13OVF_MASK             ((uint32_t)0x00002000U)         /* !< SOC13 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC14OVF] Bits */
#define ADC_ADCSOCOVF1_SOC14OVF_OFS              (14)                            /* !< SOC14OVF Offset */
#define ADC_ADCSOCOVF1_SOC14OVF_MASK             ((uint32_t)0x00004000U)         /* !< SOC14 Start of Conversion Overflow
                                                                                    Flag */
/* ADC_ADCSOCOVF1[SOC15OVF] Bits */
#define ADC_ADCSOCOVF1_SOC15OVF_OFS              (15)                            /* !< SOC15OVF Offset */
#define ADC_ADCSOCOVF1_SOC15OVF_MASK             ((uint32_t)0x00008000U)         /* !< SOC15 Start of Conversion Overflow
                                                                                    Flag */

/* ADC_ADCSOCOVFCLR1 Bits */
/* ADC_ADCSOCOVFCLR1[SOC0OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC0OVF_OFS            (0)                             /* !< SOC0OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC0OVF_MASK           ((uint32_t)0x00000001U)         /* !< SOC0 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC1OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC1OVF_OFS            (1)                             /* !< SOC1OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC1OVF_MASK           ((uint32_t)0x00000002U)         /* !< SOC1 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC2OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC2OVF_OFS            (2)                             /* !< SOC2OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC2OVF_MASK           ((uint32_t)0x00000004U)         /* !< SOC2 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC3OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC3OVF_OFS            (3)                             /* !< SOC3OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC3OVF_MASK           ((uint32_t)0x00000008U)         /* !< SOC3 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC4OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC4OVF_OFS            (4)                             /* !< SOC4OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC4OVF_MASK           ((uint32_t)0x00000010U)         /* !< SOC4 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC5OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC5OVF_OFS            (5)                             /* !< SOC5OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC5OVF_MASK           ((uint32_t)0x00000020U)         /* !< SOC5 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC6OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC6OVF_OFS            (6)                             /* !< SOC6OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC6OVF_MASK           ((uint32_t)0x00000040U)         /* !< SOC6 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC7OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC7OVF_OFS            (7)                             /* !< SOC7OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC7OVF_MASK           ((uint32_t)0x00000080U)         /* !< SOC7 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC8OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC8OVF_OFS            (8)                             /* !< SOC8OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC8OVF_MASK           ((uint32_t)0x00000100U)         /* !< SOC8 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC9OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC9OVF_OFS            (9)                             /* !< SOC9OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC9OVF_MASK           ((uint32_t)0x00000200U)         /* !< SOC9 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC10OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC10OVF_OFS           (10)                            /* !< SOC10OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC10OVF_MASK          ((uint32_t)0x00000400U)         /* !< SOC10 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC11OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC11OVF_OFS           (11)                            /* !< SOC11OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC11OVF_MASK          ((uint32_t)0x00000800U)         /* !< SOC11 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC12OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC12OVF_OFS           (12)                            /* !< SOC12OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC12OVF_MASK          ((uint32_t)0x00001000U)         /* !< SOC12 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC13OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC13OVF_OFS           (13)                            /* !< SOC13OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC13OVF_MASK          ((uint32_t)0x00002000U)         /* !< SOC13 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC14OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC14OVF_OFS           (14)                            /* !< SOC14OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC14OVF_MASK          ((uint32_t)0x00004000U)         /* !< SOC14 Clear Start of Conversion
                                                                                    Overflow Bit */
/* ADC_ADCSOCOVFCLR1[SOC15OVF] Bits */
#define ADC_ADCSOCOVFCLR1_SOC15OVF_OFS           (15)                            /* !< SOC15OVF Offset */
#define ADC_ADCSOCOVFCLR1_SOC15OVF_MASK          ((uint32_t)0x00008000U)         /* !< SOC15 Clear Start of Conversion
                                                                                    Overflow Bit */

/* ADC_ADCSOC0CTL Bits */
/* ADC_ADCSOC0CTL[CHSEL] Bits */
#define ADC_ADCSOC0CTL_CHSEL_OFS                 (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC0CTL_CHSEL_MASK                ((uint32_t)0x000F8000U)         /* !< SOC0 Channel Select */
/* ADC_ADCSOC0CTL[COMPEN] Bits */
#define ADC_ADCSOC0CTL_COMPEN_OFS                (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC0CTL_COMPEN_MASK               ((uint32_t)0x02000000U)         /* !< SOC0 Threshold comparator enable */

/* ADC_ADCSOC1CTL Bits */
/* ADC_ADCSOC1CTL[CHSEL] Bits */
#define ADC_ADCSOC1CTL_CHSEL_OFS                 (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC1CTL_CHSEL_MASK                ((uint32_t)0x000F8000U)         /* !< SOC1 Channel Select */
/* ADC_ADCSOC1CTL[COMPEN] Bits */
#define ADC_ADCSOC1CTL_COMPEN_OFS                (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC1CTL_COMPEN_MASK               ((uint32_t)0x02000000U)         /* !< SOC1 Threshold comparator enable */

/* ADC_ADCSOC2CTL Bits */
/* ADC_ADCSOC2CTL[CHSEL] Bits */
#define ADC_ADCSOC2CTL_CHSEL_OFS                 (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC2CTL_CHSEL_MASK                ((uint32_t)0x000F8000U)         /* !< SOC2 Channel Select */
/* ADC_ADCSOC2CTL[COMPEN] Bits */
#define ADC_ADCSOC2CTL_COMPEN_OFS                (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC2CTL_COMPEN_MASK               ((uint32_t)0x02000000U)         /* !< SOC2 Threshold comparator enable */

/* ADC_ADCSOC3CTL Bits */
/* ADC_ADCSOC3CTL[CHSEL] Bits */
#define ADC_ADCSOC3CTL_CHSEL_OFS                 (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC3CTL_CHSEL_MASK                ((uint32_t)0x000F8000U)         /* !< SOC3 Channel Select */
/* ADC_ADCSOC3CTL[COMPEN] Bits */
#define ADC_ADCSOC3CTL_COMPEN_OFS                (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC3CTL_COMPEN_MASK               ((uint32_t)0x02000000U)         /* !< SOC3 Threshold comparator enable */

/* ADC_ADCSOC4CTL Bits */
/* ADC_ADCSOC4CTL[CHSEL] Bits */
#define ADC_ADCSOC4CTL_CHSEL_OFS                 (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC4CTL_CHSEL_MASK                ((uint32_t)0x000F8000U)         /* !< SOC4 Channel Select */
/* ADC_ADCSOC4CTL[COMPEN] Bits */
#define ADC_ADCSOC4CTL_COMPEN_OFS                (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC4CTL_COMPEN_MASK               ((uint32_t)0x02000000U)         /* !< SOC4 Threshold comparator enable */

/* ADC_ADCSOC5CTL Bits */
/* ADC_ADCSOC5CTL[CHSEL] Bits */
#define ADC_ADCSOC5CTL_CHSEL_OFS                 (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC5CTL_CHSEL_MASK                ((uint32_t)0x000F8000U)         /* !< SOC5 Channel Select */
/* ADC_ADCSOC5CTL[COMPEN] Bits */
#define ADC_ADCSOC5CTL_COMPEN_OFS                (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC5CTL_COMPEN_MASK               ((uint32_t)0x02000000U)         /* !< SOC5 Threshold comparator enable */

/* ADC_ADCSOC6CTL Bits */
/* ADC_ADCSOC6CTL[CHSEL] Bits */
#define ADC_ADCSOC6CTL_CHSEL_OFS                 (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC6CTL_CHSEL_MASK                ((uint32_t)0x000F8000U)         /* !< SOC6 Channel Select */
/* ADC_ADCSOC6CTL[COMPEN] Bits */
#define ADC_ADCSOC6CTL_COMPEN_OFS                (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC6CTL_COMPEN_MASK               ((uint32_t)0x02000000U)         /* !< SOC6 Threshold comparator enable */

/* ADC_ADCSOC7CTL Bits */
/* ADC_ADCSOC7CTL[CHSEL] Bits */
#define ADC_ADCSOC7CTL_CHSEL_OFS                 (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC7CTL_CHSEL_MASK                ((uint32_t)0x000F8000U)         /* !< SOC7 Channel Select */
/* ADC_ADCSOC7CTL[COMPEN] Bits */
#define ADC_ADCSOC7CTL_COMPEN_OFS                (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC7CTL_COMPEN_MASK               ((uint32_t)0x02000000U)         /* !< SOC7 Threshold comparator enable */

/* ADC_ADCSOC8CTL Bits */
/* ADC_ADCSOC8CTL[CHSEL] Bits */
#define ADC_ADCSOC8CTL_CHSEL_OFS                 (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC8CTL_CHSEL_MASK                ((uint32_t)0x000F8000U)         /* !< SOC8 Channel Select */
/* ADC_ADCSOC8CTL[COMPEN] Bits */
#define ADC_ADCSOC8CTL_COMPEN_OFS                (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC8CTL_COMPEN_MASK               ((uint32_t)0x02000000U)         /* !< SOC8 Threshold comparator enable */

/* ADC_ADCSOC9CTL Bits */
/* ADC_ADCSOC9CTL[CHSEL] Bits */
#define ADC_ADCSOC9CTL_CHSEL_OFS                 (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC9CTL_CHSEL_MASK                ((uint32_t)0x000F8000U)         /* !< SOC9 Channel Select */
/* ADC_ADCSOC9CTL[COMPEN] Bits */
#define ADC_ADCSOC9CTL_COMPEN_OFS                (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC9CTL_COMPEN_MASK               ((uint32_t)0x02000000U)         /* !< SOC9 Threshold comparator enable */

/* ADC_ADCSOC10CTL Bits */
/* ADC_ADCSOC10CTL[CHSEL] Bits */
#define ADC_ADCSOC10CTL_CHSEL_OFS                (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC10CTL_CHSEL_MASK               ((uint32_t)0x000F8000U)         /* !< SOC10 Channel Select */
/* ADC_ADCSOC10CTL[COMPEN] Bits */
#define ADC_ADCSOC10CTL_COMPEN_OFS               (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC10CTL_COMPEN_MASK              ((uint32_t)0x02000000U)         /* !< SOC10 Threshold comparator enable */

/* ADC_ADCSOC11CTL Bits */
/* ADC_ADCSOC11CTL[CHSEL] Bits */
#define ADC_ADCSOC11CTL_CHSEL_OFS                (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC11CTL_CHSEL_MASK               ((uint32_t)0x000F8000U)         /* !< SOC11 Channel Select */
/* ADC_ADCSOC11CTL[COMPEN] Bits */
#define ADC_ADCSOC11CTL_COMPEN_OFS               (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC11CTL_COMPEN_MASK              ((uint32_t)0x02000000U)         /* !< SOC11 Threshold comparator enable */

/* ADC_ADCSOC12CTL Bits */
/* ADC_ADCSOC12CTL[CHSEL] Bits */
#define ADC_ADCSOC12CTL_CHSEL_OFS                (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC12CTL_CHSEL_MASK               ((uint32_t)0x000F8000U)         /* !< SOC12 Channel Select */
/* ADC_ADCSOC12CTL[COMPEN] Bits */
#define ADC_ADCSOC12CTL_COMPEN_OFS               (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC12CTL_COMPEN_MASK              ((uint32_t)0x02000000U)         /* !< SOC12 Threshold comparator enable */

/* ADC_ADCSOC13CTL Bits */
/* ADC_ADCSOC13CTL[CHSEL] Bits */
#define ADC_ADCSOC13CTL_CHSEL_OFS                (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC13CTL_CHSEL_MASK               ((uint32_t)0x000F8000U)         /* !< SOC13 Channel Select */
/* ADC_ADCSOC13CTL[COMPEN] Bits */
#define ADC_ADCSOC13CTL_COMPEN_OFS               (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC13CTL_COMPEN_MASK              ((uint32_t)0x02000000U)         /* !< SOC13 Threshold comparator enable */

/* ADC_ADCSOC14CTL Bits */
/* ADC_ADCSOC14CTL[CHSEL] Bits */
#define ADC_ADCSOC14CTL_CHSEL_OFS                (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC14CTL_CHSEL_MASK               ((uint32_t)0x000F8000U)         /* !< SOC14 Channel Select */
/* ADC_ADCSOC14CTL[COMPEN] Bits */
#define ADC_ADCSOC14CTL_COMPEN_OFS               (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC14CTL_COMPEN_MASK              ((uint32_t)0x02000000U)         /* !< SOC14 Threshold comparator enable */

/* ADC_ADCSOC15CTL Bits */
/* ADC_ADCSOC15CTL[CHSEL] Bits */
#define ADC_ADCSOC15CTL_CHSEL_OFS                (15)                            /* !< CHSEL Offset */
#define ADC_ADCSOC15CTL_CHSEL_MASK               ((uint32_t)0x000F8000U)         /* !< SOC15 Channel Select */
/* ADC_ADCSOC15CTL[COMPEN] Bits */
#define ADC_ADCSOC15CTL_COMPEN_OFS               (25)                            /* !< COMPEN Offset */
#define ADC_ADCSOC15CTL_COMPEN_MASK              ((uint32_t)0x02000000U)         /* !< SOC15 Threshold comparator enable */

/* ADC_ADCEVTSTAT Bits */
/* ADC_ADCEVTSTAT[PPB1TRIPHI] Bits */
#define ADC_ADCEVTSTAT_PPB1TRIPHI_OFS            (0)                             /* !< PPB1TRIPHI Offset */
#define ADC_ADCEVTSTAT_PPB1TRIPHI_MASK           ((uint32_t)0x00000001U)         /* !< Post Processing Block 1 Trip High
                                                                                    Flag */
/* ADC_ADCEVTSTAT[PPB1TRIPLO] Bits */
#define ADC_ADCEVTSTAT_PPB1TRIPLO_OFS            (1)                             /* !< PPB1TRIPLO Offset */
#define ADC_ADCEVTSTAT_PPB1TRIPLO_MASK           ((uint32_t)0x00000002U)         /* !< Post Processing Block 1 Trip Low
                                                                                    Flag */
/* ADC_ADCEVTSTAT[PPB1INLIMIT] Bits */
#define ADC_ADCEVTSTAT_PPB1INLIMIT_OFS           (3)                             /* !< PPB1INLIMIT Offset */
#define ADC_ADCEVTSTAT_PPB1INLIMIT_MASK          ((uint32_t)0x00000008U)         /* !< Post Processing Block 1 Within trip
                                                                                    limit Flag */
/* ADC_ADCEVTSTAT[PPB2TRIPHI] Bits */
#define ADC_ADCEVTSTAT_PPB2TRIPHI_OFS            (4)                             /* !< PPB2TRIPHI Offset */
#define ADC_ADCEVTSTAT_PPB2TRIPHI_MASK           ((uint32_t)0x00000010U)         /* !< Post Processing Block 2 Trip High
                                                                                    Flag */
/* ADC_ADCEVTSTAT[PPB2TRIPLO] Bits */
#define ADC_ADCEVTSTAT_PPB2TRIPLO_OFS            (5)                             /* !< PPB2TRIPLO Offset */
#define ADC_ADCEVTSTAT_PPB2TRIPLO_MASK           ((uint32_t)0x00000020U)         /* !< Post Processing Block 2 Trip Low
                                                                                    Flag */
/* ADC_ADCEVTSTAT[PPB2INLIMIT] Bits */
#define ADC_ADCEVTSTAT_PPB2INLIMIT_OFS           (7)                             /* !< PPB2INLIMIT Offset */
#define ADC_ADCEVTSTAT_PPB2INLIMIT_MASK          ((uint32_t)0x00000080U)         /* !< Post Processing Block 2 Within trip
                                                                                    limit Flag */
/* ADC_ADCEVTSTAT[PPB3TRIPHI] Bits */
#define ADC_ADCEVTSTAT_PPB3TRIPHI_OFS            (8)                             /* !< PPB3TRIPHI Offset */
#define ADC_ADCEVTSTAT_PPB3TRIPHI_MASK           ((uint32_t)0x00000100U)         /* !< Post Processing Block 3 Trip High
                                                                                    Flag */
/* ADC_ADCEVTSTAT[PPB3TRIPLO] Bits */
#define ADC_ADCEVTSTAT_PPB3TRIPLO_OFS            (9)                             /* !< PPB3TRIPLO Offset */
#define ADC_ADCEVTSTAT_PPB3TRIPLO_MASK           ((uint32_t)0x00000200U)         /* !< Post Processing Block 3 Trip Low
                                                                                    Flag */
/* ADC_ADCEVTSTAT[PPB3INLIMIT] Bits */
#define ADC_ADCEVTSTAT_PPB3INLIMIT_OFS           (11)                            /* !< PPB3INLIMIT Offset */
#define ADC_ADCEVTSTAT_PPB3INLIMIT_MASK          ((uint32_t)0x00000800U)         /* !< Post Processing Block 3 Within trip
                                                                                    limit Flag */
/* ADC_ADCEVTSTAT[PPB4TRIPHI] Bits */
#define ADC_ADCEVTSTAT_PPB4TRIPHI_OFS            (12)                            /* !< PPB4TRIPHI Offset */
#define ADC_ADCEVTSTAT_PPB4TRIPHI_MASK           ((uint32_t)0x00001000U)         /* !< Post Processing Block 4 Trip High
                                                                                    Flag */
/* ADC_ADCEVTSTAT[PPB4TRIPLO] Bits */
#define ADC_ADCEVTSTAT_PPB4TRIPLO_OFS            (13)                            /* !< PPB4TRIPLO Offset */
#define ADC_ADCEVTSTAT_PPB4TRIPLO_MASK           ((uint32_t)0x00002000U)         /* !< Post Processing Block 4 Trip Low
                                                                                    Flag */
/* ADC_ADCEVTSTAT[PPB4INLIMIT] Bits */
#define ADC_ADCEVTSTAT_PPB4INLIMIT_OFS           (15)                            /* !< PPB4INLIMIT Offset */
#define ADC_ADCEVTSTAT_PPB4INLIMIT_MASK          ((uint32_t)0x00008000U)         /* !< Post Processing Block 4 Within trip
                                                                                    limit Flag */

/* ADC_ADCEVTCLR Bits */
/* ADC_ADCEVTCLR[PPB1TRIPHI] Bits */
#define ADC_ADCEVTCLR_PPB1TRIPHI_OFS             (0)                             /* !< PPB1TRIPHI Offset */
#define ADC_ADCEVTCLR_PPB1TRIPHI_MASK            ((uint32_t)0x00000001U)         /* !< Post Processing Block 1 Trip High
                                                                                    Clear */
/* ADC_ADCEVTCLR[PPB1TRIPLO] Bits */
#define ADC_ADCEVTCLR_PPB1TRIPLO_OFS             (1)                             /* !< PPB1TRIPLO Offset */
#define ADC_ADCEVTCLR_PPB1TRIPLO_MASK            ((uint32_t)0x00000002U)         /* !< Post Processing Block 1 Trip Low
                                                                                    Clear */
/* ADC_ADCEVTCLR[PPB1INLIMIT] Bits */
#define ADC_ADCEVTCLR_PPB1INLIMIT_OFS            (3)                             /* !< PPB1INLIMIT Offset */
#define ADC_ADCEVTCLR_PPB1INLIMIT_MASK           ((uint32_t)0x00000008U)         /* !< Post Processing Block 1 Within trip
                                                                                    limit flag Clear */
/* ADC_ADCEVTCLR[PPB2TRIPHI] Bits */
#define ADC_ADCEVTCLR_PPB2TRIPHI_OFS             (4)                             /* !< PPB2TRIPHI Offset */
#define ADC_ADCEVTCLR_PPB2TRIPHI_MASK            ((uint32_t)0x00000010U)         /* !< Post Processing Block 2 Trip High
                                                                                    Clear */
/* ADC_ADCEVTCLR[PPB2TRIPLO] Bits */
#define ADC_ADCEVTCLR_PPB2TRIPLO_OFS             (5)                             /* !< PPB2TRIPLO Offset */
#define ADC_ADCEVTCLR_PPB2TRIPLO_MASK            ((uint32_t)0x00000020U)         /* !< Post Processing Block 2 Trip Low
                                                                                    Clear */
/* ADC_ADCEVTCLR[PPB2INLIMIT] Bits */
#define ADC_ADCEVTCLR_PPB2INLIMIT_OFS            (7)                             /* !< PPB2INLIMIT Offset */
#define ADC_ADCEVTCLR_PPB2INLIMIT_MASK           ((uint32_t)0x00000080U)         /* !< Post Processing Block 2 Within trip
                                                                                    limit flag Clear */
/* ADC_ADCEVTCLR[PPB3TRIPHI] Bits */
#define ADC_ADCEVTCLR_PPB3TRIPHI_OFS             (8)                             /* !< PPB3TRIPHI Offset */
#define ADC_ADCEVTCLR_PPB3TRIPHI_MASK            ((uint32_t)0x00000100U)         /* !< Post Processing Block 3 Trip High
                                                                                    Clear */
/* ADC_ADCEVTCLR[PPB3TRIPLO] Bits */
#define ADC_ADCEVTCLR_PPB3TRIPLO_OFS             (9)                             /* !< PPB3TRIPLO Offset */
#define ADC_ADCEVTCLR_PPB3TRIPLO_MASK            ((uint32_t)0x00000200U)         /* !< Post Processing Block 3 Trip Low
                                                                                    Clear */
/* ADC_ADCEVTCLR[PPB3INLIMIT] Bits */
#define ADC_ADCEVTCLR_PPB3INLIMIT_OFS            (11)                            /* !< PPB3INLIMIT Offset */
#define ADC_ADCEVTCLR_PPB3INLIMIT_MASK           ((uint32_t)0x00000800U)         /* !< Post Processing Block 3 Within trip
                                                                                    limit flag Clear */
/* ADC_ADCEVTCLR[PPB4TRIPHI] Bits */
#define ADC_ADCEVTCLR_PPB4TRIPHI_OFS             (12)                            /* !< PPB4TRIPHI Offset */
#define ADC_ADCEVTCLR_PPB4TRIPHI_MASK            ((uint32_t)0x00001000U)         /* !< Post Processing Block 4 Trip High
                                                                                    Clear */
/* ADC_ADCEVTCLR[PPB4TRIPLO] Bits */
#define ADC_ADCEVTCLR_PPB4TRIPLO_OFS             (13)                            /* !< PPB4TRIPLO Offset */
#define ADC_ADCEVTCLR_PPB4TRIPLO_MASK            ((uint32_t)0x00002000U)         /* !< Post Processing Block 4 Trip Low
                                                                                    Clear */
/* ADC_ADCEVTCLR[PPB4INLIMIT] Bits */
#define ADC_ADCEVTCLR_PPB4INLIMIT_OFS            (15)                            /* !< PPB4INLIMIT Offset */
#define ADC_ADCEVTCLR_PPB4INLIMIT_MASK           ((uint32_t)0x00008000U)         /* !< Post Processing Block 4 Within trip
                                                                                    limit flag Clear */

/* ADC_ADCEVTSEL Bits */
/* ADC_ADCEVTSEL[PPB1TRIPHI] Bits */
#define ADC_ADCEVTSEL_PPB1TRIPHI_OFS             (0)                             /* !< PPB1TRIPHI Offset */
#define ADC_ADCEVTSEL_PPB1TRIPHI_MASK            ((uint32_t)0x00000001U)         /* !< Post Processing Block 1 Trip High
                                                                                    Event Enable */
/* ADC_ADCEVTSEL[PPB1TRIPLO] Bits */
#define ADC_ADCEVTSEL_PPB1TRIPLO_OFS             (1)                             /* !< PPB1TRIPLO Offset */
#define ADC_ADCEVTSEL_PPB1TRIPLO_MASK            ((uint32_t)0x00000002U)         /* !< Post Processing Block 1 Trip Low
                                                                                    Event Enable */
/* ADC_ADCEVTSEL[PPB1INLIMIT] Bits */
#define ADC_ADCEVTSEL_PPB1INLIMIT_OFS            (3)                             /* !< PPB1INLIMIT Offset */
#define ADC_ADCEVTSEL_PPB1INLIMIT_MASK           ((uint32_t)0x00000008U)         /* !< Post Processing Block 1 Within trip
                                                                                    limit event enable */
/* ADC_ADCEVTSEL[PPB2TRIPHI] Bits */
#define ADC_ADCEVTSEL_PPB2TRIPHI_OFS             (4)                             /* !< PPB2TRIPHI Offset */
#define ADC_ADCEVTSEL_PPB2TRIPHI_MASK            ((uint32_t)0x00000010U)         /* !< Post Processing Block 2 Trip High
                                                                                    Event Enable */
/* ADC_ADCEVTSEL[PPB2TRIPLO] Bits */
#define ADC_ADCEVTSEL_PPB2TRIPLO_OFS             (5)                             /* !< PPB2TRIPLO Offset */
#define ADC_ADCEVTSEL_PPB2TRIPLO_MASK            ((uint32_t)0x00000020U)         /* !< Post Processing Block 2 Trip Low
                                                                                    Event Enable */
/* ADC_ADCEVTSEL[PPB2INLIMIT] Bits */
#define ADC_ADCEVTSEL_PPB2INLIMIT_OFS            (7)                             /* !< PPB2INLIMIT Offset */
#define ADC_ADCEVTSEL_PPB2INLIMIT_MASK           ((uint32_t)0x00000080U)         /* !< Post Processing Block 2 Within trip
                                                                                    limit event enable */
/* ADC_ADCEVTSEL[PPB3TRIPHI] Bits */
#define ADC_ADCEVTSEL_PPB3TRIPHI_OFS             (8)                             /* !< PPB3TRIPHI Offset */
#define ADC_ADCEVTSEL_PPB3TRIPHI_MASK            ((uint32_t)0x00000100U)         /* !< Post Processing Block 3 Trip High
                                                                                    Event Enable */
/* ADC_ADCEVTSEL[PPB3TRIPLO] Bits */
#define ADC_ADCEVTSEL_PPB3TRIPLO_OFS             (9)                             /* !< PPB3TRIPLO Offset */
#define ADC_ADCEVTSEL_PPB3TRIPLO_MASK            ((uint32_t)0x00000200U)         /* !< Post Processing Block 3 Trip Low
                                                                                    Event Enable */
/* ADC_ADCEVTSEL[PPB3INLIMIT] Bits */
#define ADC_ADCEVTSEL_PPB3INLIMIT_OFS            (11)                            /* !< PPB3INLIMIT Offset */
#define ADC_ADCEVTSEL_PPB3INLIMIT_MASK           ((uint32_t)0x00000800U)         /* !< Post Processing Block 3 Within trip
                                                                                    limit event enable */
/* ADC_ADCEVTSEL[PPB4TRIPHI] Bits */
#define ADC_ADCEVTSEL_PPB4TRIPHI_OFS             (12)                            /* !< PPB4TRIPHI Offset */
#define ADC_ADCEVTSEL_PPB4TRIPHI_MASK            ((uint32_t)0x00001000U)         /* !< Post Processing Block 4 Trip High
                                                                                    Event Enable */
/* ADC_ADCEVTSEL[PPB4TRIPLO] Bits */
#define ADC_ADCEVTSEL_PPB4TRIPLO_OFS             (13)                            /* !< PPB4TRIPLO Offset */
#define ADC_ADCEVTSEL_PPB4TRIPLO_MASK            ((uint32_t)0x00002000U)         /* !< Post Processing Block 4 Trip Low
                                                                                    Event Enable */
/* ADC_ADCEVTSEL[PPB4INLIMIT] Bits */
#define ADC_ADCEVTSEL_PPB4INLIMIT_OFS            (15)                            /* !< PPB4INLIMIT Offset */
#define ADC_ADCEVTSEL_PPB4INLIMIT_MASK           ((uint32_t)0x00008000U)         /* !< Post Processing Block 4 Within trip
                                                                                    limit event enable */

/* ADC_ADCEVTINTSEL Bits */
/* ADC_ADCEVTINTSEL[PPB1TRIPHI] Bits */
#define ADC_ADCEVTINTSEL_PPB1TRIPHI_OFS          (0)                             /* !< PPB1TRIPHI Offset */
#define ADC_ADCEVTINTSEL_PPB1TRIPHI_MASK         ((uint32_t)0x00000001U)         /* !< Post Processing Block 1 Trip High
                                                                                    Interrupt Enable */
/* ADC_ADCEVTINTSEL[PPB1TRIPLO] Bits */
#define ADC_ADCEVTINTSEL_PPB1TRIPLO_OFS          (1)                             /* !< PPB1TRIPLO Offset */
#define ADC_ADCEVTINTSEL_PPB1TRIPLO_MASK         ((uint32_t)0x00000002U)         /* !< Post Processing Block 1 Trip Low
                                                                                    Interrupt Enable */
/* ADC_ADCEVTINTSEL[PPB1INLIMIT] Bits */
#define ADC_ADCEVTINTSEL_PPB1INLIMIT_OFS         (3)                             /* !< PPB1INLIMIT Offset */
#define ADC_ADCEVTINTSEL_PPB1INLIMIT_MASK        ((uint32_t)0x00000008U)         /* !< Post Processing Block 1 Within trip
                                                                                    limit interrupt enable */
/* ADC_ADCEVTINTSEL[PPB2TRIPHI] Bits */
#define ADC_ADCEVTINTSEL_PPB2TRIPHI_OFS          (4)                             /* !< PPB2TRIPHI Offset */
#define ADC_ADCEVTINTSEL_PPB2TRIPHI_MASK         ((uint32_t)0x00000010U)         /* !< Post Processing Block 2 Trip High
                                                                                    Interrupt Enable */
/* ADC_ADCEVTINTSEL[PPB2TRIPLO] Bits */
#define ADC_ADCEVTINTSEL_PPB2TRIPLO_OFS          (5)                             /* !< PPB2TRIPLO Offset */
#define ADC_ADCEVTINTSEL_PPB2TRIPLO_MASK         ((uint32_t)0x00000020U)         /* !< Post Processing Block 2 Trip Low
                                                                                    Interrupt Enable */
/* ADC_ADCEVTINTSEL[PPB2INLIMIT] Bits */
#define ADC_ADCEVTINTSEL_PPB2INLIMIT_OFS         (7)                             /* !< PPB2INLIMIT Offset */
#define ADC_ADCEVTINTSEL_PPB2INLIMIT_MASK        ((uint32_t)0x00000080U)         /* !< Post Processing Block 2 Within trip
                                                                                    limit interrupt enable */
/* ADC_ADCEVTINTSEL[PPB3TRIPHI] Bits */
#define ADC_ADCEVTINTSEL_PPB3TRIPHI_OFS          (8)                             /* !< PPB3TRIPHI Offset */
#define ADC_ADCEVTINTSEL_PPB3TRIPHI_MASK         ((uint32_t)0x00000100U)         /* !< Post Processing Block 3 Trip High
                                                                                    Interrupt Enable */
/* ADC_ADCEVTINTSEL[PPB3TRIPLO] Bits */
#define ADC_ADCEVTINTSEL_PPB3TRIPLO_OFS          (9)                             /* !< PPB3TRIPLO Offset */
#define ADC_ADCEVTINTSEL_PPB3TRIPLO_MASK         ((uint32_t)0x00000200U)         /* !< Post Processing Block 3 Trip Low
                                                                                    Interrupt Enable */
/* ADC_ADCEVTINTSEL[PPB3INLIMIT] Bits */
#define ADC_ADCEVTINTSEL_PPB3INLIMIT_OFS         (11)                            /* !< PPB3INLIMIT Offset */
#define ADC_ADCEVTINTSEL_PPB3INLIMIT_MASK        ((uint32_t)0x00000800U)         /* !< Post Processing Block 3 Within trip
                                                                                    limit interrupt enable */
/* ADC_ADCEVTINTSEL[PPB4TRIPHI] Bits */
#define ADC_ADCEVTINTSEL_PPB4TRIPHI_OFS          (12)                            /* !< PPB4TRIPHI Offset */
#define ADC_ADCEVTINTSEL_PPB4TRIPHI_MASK         ((uint32_t)0x00001000U)         /* !< Post Processing Block 4 Trip High
                                                                                    Interrupt Enable */
/* ADC_ADCEVTINTSEL[PPB4TRIPLO] Bits */
#define ADC_ADCEVTINTSEL_PPB4TRIPLO_OFS          (13)                            /* !< PPB4TRIPLO Offset */
#define ADC_ADCEVTINTSEL_PPB4TRIPLO_MASK         ((uint32_t)0x00002000U)         /* !< Post Processing Block 4 Trip Low
                                                                                    Interrupt Enable */
/* ADC_ADCEVTINTSEL[PPB4INLIMIT] Bits */
#define ADC_ADCEVTINTSEL_PPB4INLIMIT_OFS         (15)                            /* !< PPB4INLIMIT Offset */
#define ADC_ADCEVTINTSEL_PPB4INLIMIT_MASK        ((uint32_t)0x00008000U)         /* !< Post Processing Block 4 Within trip
                                                                                    limit interrupt enable */

/* ADC_ADCREV Bits */
/* ADC_ADCREV[TYPE] Bits */
#define ADC_ADCREV_TYPE_OFS                      (0)                             /* !< TYPE Offset */
#define ADC_ADCREV_TYPE_MASK                     ((uint32_t)0x000000FFU)         /* !< ADC Type */
/* ADC_ADCREV[REV] Bits */
#define ADC_ADCREV_REV_OFS                       (8)                             /* !< REV Offset */
#define ADC_ADCREV_REV_MASK                      ((uint32_t)0xFFFFFF00U)         /* !< ADC Revision */

/* ADC_ADCOFFTRIM Bits */
/* ADC_ADCOFFTRIM[OFFTRIM] Bits */
#define ADC_ADCOFFTRIM_OFFTRIM_OFS               (0)                             /* !< OFFTRIM Offset */
#define ADC_ADCOFFTRIM_OFFTRIM_MASK              ((uint32_t)0x000000FFU)         /* !< ADC Offset Trim */

/* ADC_ADCPPB1CONFIG Bits */
/* ADC_ADCPPB1CONFIG[CBCEN] Bits */
#define ADC_ADCPPB1CONFIG_CBCEN_OFS              (5)                             /* !< CBCEN Offset */
#define ADC_ADCPPB1CONFIG_CBCEN_MASK             ((uint32_t)0x00000020U)         /* !< Cycle By Cycle Enable */

/* ADC_ADCPPB1TRIPHI Bits */
/* ADC_ADCPPB1TRIPHI[LIMITHI] Bits */
#define ADC_ADCPPB1TRIPHI_LIMITHI_OFS            (0)                             /* !< LIMITHI Offset */
#define ADC_ADCPPB1TRIPHI_LIMITHI_MASK           ((uint32_t)0x0000FFFFU)         /* !< ADC Post Processing Block 1 Trip
                                                                                    High Limit */

/* ADC_ADCPPB1TRIPLO Bits */
/* ADC_ADCPPB1TRIPLO[LIMITLO] Bits */
#define ADC_ADCPPB1TRIPLO_LIMITLO_OFS            (0)                             /* !< LIMITLO Offset */
#define ADC_ADCPPB1TRIPLO_LIMITLO_MASK           ((uint32_t)0x0000FFFFU)         /* !< ADC Post Processing Block 1 Trip
                                                                                    Low Limit */

/* ADC_ADCPPB2CONFIG Bits */
/* ADC_ADCPPB2CONFIG[CBCEN] Bits */
#define ADC_ADCPPB2CONFIG_CBCEN_OFS              (5)                             /* !< CBCEN Offset */
#define ADC_ADCPPB2CONFIG_CBCEN_MASK             ((uint32_t)0x00000020U)         /* !< Cycle By Cycle Enable */

/* ADC_ADCPPB2TRIPHI Bits */
/* ADC_ADCPPB2TRIPHI[LIMITHI] Bits */
#define ADC_ADCPPB2TRIPHI_LIMITHI_OFS            (0)                             /* !< LIMITHI Offset */
#define ADC_ADCPPB2TRIPHI_LIMITHI_MASK           ((uint32_t)0x0000FFFFU)         /* !< ADC Post Processing Block 2 Trip
                                                                                    High Limit */

/* ADC_ADCPPB2TRIPLO Bits */
/* ADC_ADCPPB2TRIPLO[LIMITLO] Bits */
#define ADC_ADCPPB2TRIPLO_LIMITLO_OFS            (0)                             /* !< LIMITLO Offset */
#define ADC_ADCPPB2TRIPLO_LIMITLO_MASK           ((uint32_t)0x0000FFFFU)         /* !< ADC Post Processing Block 2 Trip
                                                                                    Low Limit */

/* ADC_ADCPPB3CONFIG Bits */
/* ADC_ADCPPB3CONFIG[CBCEN] Bits */
#define ADC_ADCPPB3CONFIG_CBCEN_OFS              (5)                             /* !< CBCEN Offset */
#define ADC_ADCPPB3CONFIG_CBCEN_MASK             ((uint32_t)0x00000020U)         /* !< Cycle By Cycle Enable */

/* ADC_ADCPPB3TRIPHI Bits */
/* ADC_ADCPPB3TRIPHI[LIMITHI] Bits */
#define ADC_ADCPPB3TRIPHI_LIMITHI_OFS            (0)                             /* !< LIMITHI Offset */
#define ADC_ADCPPB3TRIPHI_LIMITHI_MASK           ((uint32_t)0x0000FFFFU)         /* !< ADC Post Processing Block 3 Trip
                                                                                    High Limit */

/* ADC_ADCPPB3TRIPLO Bits */
/* ADC_ADCPPB3TRIPLO[LIMITLO] Bits */
#define ADC_ADCPPB3TRIPLO_LIMITLO_OFS            (0)                             /* !< LIMITLO Offset */
#define ADC_ADCPPB3TRIPLO_LIMITLO_MASK           ((uint32_t)0x0000FFFFU)         /* !< ADC Post Processing Block 3 Trip
                                                                                    Low Limit */

/* ADC_ADCPPB4CONFIG Bits */
/* ADC_ADCPPB4CONFIG[CBCEN] Bits */
#define ADC_ADCPPB4CONFIG_CBCEN_OFS              (5)                             /* !< CBCEN Offset */
#define ADC_ADCPPB4CONFIG_CBCEN_MASK             ((uint32_t)0x00000020U)         /* !< Cycle By Cycle Enable */

/* ADC_ADCPPB4TRIPHI Bits */
/* ADC_ADCPPB4TRIPHI[LIMITHI] Bits */
#define ADC_ADCPPB4TRIPHI_LIMITHI_OFS            (0)                             /* !< LIMITHI Offset */
#define ADC_ADCPPB4TRIPHI_LIMITHI_MASK           ((uint32_t)0x0000FFFFU)         /* !< ADC Post Processing Block 4 Trip
                                                                                    High Limit */

/* ADC_ADCPPB4TRIPLO Bits */
/* ADC_ADCPPB4TRIPLO[LIMITLO] Bits */
#define ADC_ADCPPB4TRIPLO_LIMITLO_OFS            (0)                             /* !< LIMITLO Offset */
#define ADC_ADCPPB4TRIPLO_LIMITLO_MASK           ((uint32_t)0x0000FFFFU)         /* !< ADC Post Processing Block 4 Trip
                                                                                    Low Limit */

/* ADC_ADCINTCYCLE Bits */
/* ADC_ADCINTCYCLE[DELAY] Bits */
#define ADC_ADCINTCYCLE_DELAY_OFS                (0)                             /* !< DELAY Offset */
#define ADC_ADCINTCYCLE_DELAY_MASK               ((uint32_t)0x0000003FU)         /* !< Delay from ADCSOC fall edge to
                                                                                    early interrupt generation. */

/* ADC_ADCREV2 Bits */
/* ADC_ADCREV2[WRAPPERTYPE] Bits */
#define ADC_ADCREV2_WRAPPERTYPE_OFS              (0)                             /* !< WRAPPERTYPE Offset */
#define ADC_ADCREV2_WRAPPERTYPE_MASK             ((uint32_t)0x000000FFU)         /* !< ADC Wrapper Type */
/* ADC_ADCREV2[WRAPPERREV] Bits */
#define ADC_ADCREV2_WRAPPERREV_OFS               (8)                             /* !< WRAPPERREV Offset */
#define ADC_ADCREV2_WRAPPERREV_MASK              ((uint32_t)0xFFFFFF00U)         /* !< ADC Wrapper Revision */

/* ADC_ADCPPB1LIMIT Bits */
/* ADC_ADCPPB1LIMIT[LIMIT] Bits */
#define ADC_ADCPPB1LIMIT_LIMIT_OFS               (0)                             /* !< LIMIT Offset */
#define ADC_ADCPPB1LIMIT_LIMIT_MASK              ((uint32_t)0x00000003U)         /* !< Post Processing Block 1 Limit */

/* ADC_ADCPPB1PCOUNT Bits */
/* ADC_ADCPPB1PCOUNT[PCOUNT] Bits */
#define ADC_ADCPPB1PCOUNT_PCOUNT_OFS             (0)                             /* !< PCOUNT Offset */
#define ADC_ADCPPB1PCOUNT_PCOUNT_MASK            ((uint32_t)0x00000007U)         /* !< Post Processing Block 1 Partial
                                                                                    Count */

/* ADC_ADCPPB1CONFIG2 Bits */
/* ADC_ADCPPB1CONFIG2[SHIFT] Bits */
#define ADC_ADCPPB1CONFIG2_SHIFT_OFS             (0)                             /* !< SHIFT Offset */
#define ADC_ADCPPB1CONFIG2_SHIFT_MASK            ((uint32_t)0x00000007U)         /* !< Post Processing Block 1 Right Shift */
/* ADC_ADCPPB1CONFIG2[SYNCINSEL] Bits */
#define ADC_ADCPPB1CONFIG2_SYNCINSEL_OFS         (4)                             /* !< SYNCINSEL Offset */
#define ADC_ADCPPB1CONFIG2_SYNCINSEL_MASK        ((uint32_t)0x000001F0U)         /* !< Post Processing Block 1 Sync. Input
                                                                                    Select */
/* ADC_ADCPPB1CONFIG2[SWSYNC] Bits */
#define ADC_ADCPPB1CONFIG2_SWSYNC_OFS            (11)                            /* !< SWSYNC Offset */
#define ADC_ADCPPB1CONFIG2_SWSYNC_MASK           ((uint32_t)0x00000800U)         /* !< Post Processing Block 1 Software
                                                                                    Force Sync. */
/* ADC_ADCPPB1CONFIG2[COMPSEL] Bits */
#define ADC_ADCPPB1CONFIG2_COMPSEL_OFS           (15)                            /* !< COMPSEL Offset */
#define ADC_ADCPPB1CONFIG2_COMPSEL_MASK          ((uint32_t)0x00008000U)         /* !< Post Processing Block 1 Compare
                                                                                    Source Select */

/* ADC_ADCPPB1PSUM Bits */
/* ADC_ADCPPB1PSUM[PSUM] Bits */
#define ADC_ADCPPB1PSUM_PSUM_OFS                 (0)                             /* !< PSUM Offset */
#define ADC_ADCPPB1PSUM_PSUM_MASK                ((uint32_t)0x0000FFFFU)         /* !< Post Processing Block 1
                                                                                    Oversampling Partial Sum */
/* ADC_ADCPPB1PSUM[SIGN] Bits */
#define ADC_ADCPPB1PSUM_SIGN_OFS                 (16)                            /* !< SIGN Offset */
#define ADC_ADCPPB1PSUM_SIGN_MASK                ((uint32_t)0xFFFF0000U)         /* !< Sign Extended Bits */

/* ADC_ADCPPB2LIMIT Bits */
/* ADC_ADCPPB2LIMIT[LIMIT] Bits */
#define ADC_ADCPPB2LIMIT_LIMIT_OFS               (0)                             /* !< LIMIT Offset */
#define ADC_ADCPPB2LIMIT_LIMIT_MASK              ((uint32_t)0x00000003U)         /* !< Post Processing Block 2 Limit */

/* ADC_ADCPPB2PCOUNT Bits */
/* ADC_ADCPPB2PCOUNT[PCOUNT] Bits */
#define ADC_ADCPPB2PCOUNT_PCOUNT_OFS             (0)                             /* !< PCOUNT Offset */
#define ADC_ADCPPB2PCOUNT_PCOUNT_MASK            ((uint32_t)0x00000007U)         /* !< Post Processing Block 2 Partial
                                                                                    Count */

/* ADC_ADCPPB2CONFIG2 Bits */
/* ADC_ADCPPB2CONFIG2[SHIFT] Bits */
#define ADC_ADCPPB2CONFIG2_SHIFT_OFS             (0)                             /* !< SHIFT Offset */
#define ADC_ADCPPB2CONFIG2_SHIFT_MASK            ((uint32_t)0x00000007U)         /* !< Post Processing Block 2 Right Shift */
/* ADC_ADCPPB2CONFIG2[SYNCINSEL] Bits */
#define ADC_ADCPPB2CONFIG2_SYNCINSEL_OFS         (4)                             /* !< SYNCINSEL Offset */
#define ADC_ADCPPB2CONFIG2_SYNCINSEL_MASK        ((uint32_t)0x000001F0U)         /* !< Post Processing Block 2 Sync. Input
                                                                                    Select */
/* ADC_ADCPPB2CONFIG2[SWSYNC] Bits */
#define ADC_ADCPPB2CONFIG2_SWSYNC_OFS            (11)                            /* !< SWSYNC Offset */
#define ADC_ADCPPB2CONFIG2_SWSYNC_MASK           ((uint32_t)0x00000800U)         /* !< Post Processing Block 2 Software
                                                                                    Force Sync. */
/* ADC_ADCPPB2CONFIG2[COMPSEL] Bits */
#define ADC_ADCPPB2CONFIG2_COMPSEL_OFS           (15)                            /* !< COMPSEL Offset */
#define ADC_ADCPPB2CONFIG2_COMPSEL_MASK          ((uint32_t)0x00008000U)         /* !< Post Processing Block 2 Compare
                                                                                    Source Select */

/* ADC_ADCPPB2PSUM Bits */
/* ADC_ADCPPB2PSUM[PSUM] Bits */
#define ADC_ADCPPB2PSUM_PSUM_OFS                 (0)                             /* !< PSUM Offset */
#define ADC_ADCPPB2PSUM_PSUM_MASK                ((uint32_t)0x0000FFFFU)         /* !< Post Processing Block 2
                                                                                    Oversampling Partial Sum */
/* ADC_ADCPPB2PSUM[SIGN] Bits */
#define ADC_ADCPPB2PSUM_SIGN_OFS                 (16)                            /* !< SIGN Offset */
#define ADC_ADCPPB2PSUM_SIGN_MASK                ((uint32_t)0xFFFF0000U)         /* !< Sign Extended Bits */

/* ADC_ADCPPB3LIMIT Bits */
/* ADC_ADCPPB3LIMIT[LIMIT] Bits */
#define ADC_ADCPPB3LIMIT_LIMIT_OFS               (0)                             /* !< LIMIT Offset */
#define ADC_ADCPPB3LIMIT_LIMIT_MASK              ((uint32_t)0x00000003U)         /* !< Post Processing Block 3 Limit */

/* ADC_ADCPPB3PCOUNT Bits */
/* ADC_ADCPPB3PCOUNT[PCOUNT] Bits */
#define ADC_ADCPPB3PCOUNT_PCOUNT_OFS             (0)                             /* !< PCOUNT Offset */
#define ADC_ADCPPB3PCOUNT_PCOUNT_MASK            ((uint32_t)0x00000007U)         /* !< Post Processing Block 3 Partial
                                                                                    Count */

/* ADC_ADCPPB3CONFIG2 Bits */
/* ADC_ADCPPB3CONFIG2[SHIFT] Bits */
#define ADC_ADCPPB3CONFIG2_SHIFT_OFS             (0)                             /* !< SHIFT Offset */
#define ADC_ADCPPB3CONFIG2_SHIFT_MASK            ((uint32_t)0x00000007U)         /* !< Post Processing Block 3 Right Shift */
/* ADC_ADCPPB3CONFIG2[SYNCINSEL] Bits */
#define ADC_ADCPPB3CONFIG2_SYNCINSEL_OFS         (4)                             /* !< SYNCINSEL Offset */
#define ADC_ADCPPB3CONFIG2_SYNCINSEL_MASK        ((uint32_t)0x000001F0U)         /* !< Post Processing Block 3 Sync. Input
                                                                                    Select */
/* ADC_ADCPPB3CONFIG2[SWSYNC] Bits */
#define ADC_ADCPPB3CONFIG2_SWSYNC_OFS            (11)                            /* !< SWSYNC Offset */
#define ADC_ADCPPB3CONFIG2_SWSYNC_MASK           ((uint32_t)0x00000800U)         /* !< Post Processing Block 3 Software
                                                                                    Force Sync. */
/* ADC_ADCPPB3CONFIG2[COMPSEL] Bits */
#define ADC_ADCPPB3CONFIG2_COMPSEL_OFS           (15)                            /* !< COMPSEL Offset */
#define ADC_ADCPPB3CONFIG2_COMPSEL_MASK          ((uint32_t)0x00008000U)         /* !< Post Processing Block 3 Compare
                                                                                    Source Select */

/* ADC_ADCPPB3PSUM Bits */
/* ADC_ADCPPB3PSUM[PSUM] Bits */
#define ADC_ADCPPB3PSUM_PSUM_OFS                 (0)                             /* !< PSUM Offset */
#define ADC_ADCPPB3PSUM_PSUM_MASK                ((uint32_t)0x0000FFFFU)         /* !< Post Processing Block 3
                                                                                    Oversampling Partial Sum */
/* ADC_ADCPPB3PSUM[SIGN] Bits */
#define ADC_ADCPPB3PSUM_SIGN_OFS                 (16)                            /* !< SIGN Offset */
#define ADC_ADCPPB3PSUM_SIGN_MASK                ((uint32_t)0xFFFF0000U)         /* !< Sign Extended Bits */

/* ADC_ADCPPB4LIMIT Bits */
/* ADC_ADCPPB4LIMIT[LIMIT] Bits */
#define ADC_ADCPPB4LIMIT_LIMIT_OFS               (0)                             /* !< LIMIT Offset */
#define ADC_ADCPPB4LIMIT_LIMIT_MASK              ((uint32_t)0x00000003U)         /* !< Post Processing Block 4 Limit */

/* ADC_ADCPPB4PCOUNT Bits */
/* ADC_ADCPPB4PCOUNT[PCOUNT] Bits */
#define ADC_ADCPPB4PCOUNT_PCOUNT_OFS             (0)                             /* !< PCOUNT Offset */
#define ADC_ADCPPB4PCOUNT_PCOUNT_MASK            ((uint32_t)0x00000007U)         /* !< Post Processing Block 4 Partial
                                                                                    Count */

/* ADC_ADCPPB4CONFIG2 Bits */
/* ADC_ADCPPB4CONFIG2[SHIFT] Bits */
#define ADC_ADCPPB4CONFIG2_SHIFT_OFS             (0)                             /* !< SHIFT Offset */
#define ADC_ADCPPB4CONFIG2_SHIFT_MASK            ((uint32_t)0x00000007U)         /* !< Post Processing Block 4 Right Shift */
/* ADC_ADCPPB4CONFIG2[SYNCINSEL] Bits */
#define ADC_ADCPPB4CONFIG2_SYNCINSEL_OFS         (4)                             /* !< SYNCINSEL Offset */
#define ADC_ADCPPB4CONFIG2_SYNCINSEL_MASK        ((uint32_t)0x000001F0U)         /* !< Post Processing Block 4 Sync. Input
                                                                                    Select */
/* ADC_ADCPPB4CONFIG2[SWSYNC] Bits */
#define ADC_ADCPPB4CONFIG2_SWSYNC_OFS            (11)                            /* !< SWSYNC Offset */
#define ADC_ADCPPB4CONFIG2_SWSYNC_MASK           ((uint32_t)0x00000800U)         /* !< Post Processing Block 4 Software
                                                                                    Force Sync. */
/* ADC_ADCPPB4CONFIG2[COMPSEL] Bits */
#define ADC_ADCPPB4CONFIG2_COMPSEL_OFS           (15)                            /* !< COMPSEL Offset */
#define ADC_ADCPPB4CONFIG2_COMPSEL_MASK          ((uint32_t)0x00008000U)         /* !< Post Processing Block 4 Compare
                                                                                    Source Select */

/* ADC_ADCPPB4PSUM Bits */
/* ADC_ADCPPB4PSUM[PSUM] Bits */
#define ADC_ADCPPB4PSUM_PSUM_OFS                 (0)                             /* !< PSUM Offset */
#define ADC_ADCPPB4PSUM_PSUM_MASK                ((uint32_t)0x0000FFFFU)         /* !< Post Processing Block 4
                                                                                    Oversampling Partial Sum */
/* ADC_ADCPPB4PSUM[SIGN] Bits */
#define ADC_ADCPPB4PSUM_SIGN_OFS                 (16)                            /* !< SIGN Offset */
#define ADC_ADCPPB4PSUM_SIGN_MASK                ((uint32_t)0xFFFF0000U)         /* !< Sign Extended Bits */

/* ADC_ADCSEQCTL Bits */
/* ADC_ADCSEQCTL[SEQEND] Bits */
#define ADC_ADCSEQCTL_SEQEND_OFS                 (0)                             /* !< SEQEND Offset */
#define ADC_ADCSEQCTL_SEQEND_MASK                ((uint32_t)0x0000000FU)         /* !< END SOC of SEQ4 */
/* ADC_ADCSEQCTL[SEQPREEMPT] Bits */
#define ADC_ADCSEQCTL_SEQPREEMPT_OFS             (16)                            /* !< SEQPREEMPT Offset */
#define ADC_ADCSEQCTL_SEQPREEMPT_MASK            ((uint32_t)0x00030000U)         /* !< SOC Sequnece Preempt and restart
                                                                                    setting */

/* ADC_ADCSEQ1CONFIG Bits */
/* ADC_ADCSEQ1CONFIG[ACQPS] Bits */
#define ADC_ADCSEQ1CONFIG_ACQPS_OFS              (0)                             /* !< ACQPS Offset */
#define ADC_ADCSEQ1CONFIG_ACQPS_MASK             ((uint32_t)0x000000FFU)         /* !< SEQ1 Acquisition Prescale */
/* ADC_ADCSEQ1CONFIG[SAMPCAPRESETDISABLE] Bits */
#define ADC_ADCSEQ1CONFIG_SAMPCAPRESETDISABLE_OFS (9)                             /* !< SAMPCAPRESETDISABLE Offset */
#define ADC_ADCSEQ1CONFIG_SAMPCAPRESETDISABLE_MASK ((uint32_t)0x00000200U)         /* !< SEQ1 Sample Cap Reset Enable */
/* ADC_ADCSEQ1CONFIG[SAMPCAPRESETSEL] Bits */
#define ADC_ADCSEQ1CONFIG_SAMPCAPRESETSEL_OFS    (10)                            /* !< SAMPCAPRESETSEL Offset */
#define ADC_ADCSEQ1CONFIG_SAMPCAPRESETSEL_MASK   ((uint32_t)0x00000400U)         /* !< SEQ1 Sample Cap Reset Select */
/* ADC_ADCSEQ1CONFIG[SEQSTART] Bits */
#define ADC_ADCSEQ1CONFIG_SEQSTART_OFS           (15)                            /* !< SEQSTART Offset */
#define ADC_ADCSEQ1CONFIG_SEQSTART_MASK          ((uint32_t)0x00078000U)         /* !< Beginning SOC of SEQ1 */
/* ADC_ADCSEQ1CONFIG[TRIGSEL] Bits */
#define ADC_ADCSEQ1CONFIG_TRIGSEL_OFS            (20)                            /* !< TRIGSEL Offset */
#define ADC_ADCSEQ1CONFIG_TRIGSEL_MASK           ((uint32_t)0x01F00000U)         /* !< SEQ1 Trigger Source Select */
/* ADC_ADCSEQ1CONFIG[SEQSWFRC] Bits */
#define ADC_ADCSEQ1CONFIG_SEQSWFRC_OFS           (30)                            /* !< SEQSWFRC Offset */
#define ADC_ADCSEQ1CONFIG_SEQSWFRC_MASK          ((uint32_t)0x40000000U)         /* !< SEQ1 Software Force */
/* ADC_ADCSEQ1CONFIG[SEQENABLE] Bits */
#define ADC_ADCSEQ1CONFIG_SEQENABLE_OFS          (31)                            /* !< SEQENABLE Offset */
#define ADC_ADCSEQ1CONFIG_SEQENABLE_MASK         ((uint32_t)0x80000000U)         /* !< SEQ1Enable */

/* ADC_ADCSEQ2CONFIG Bits */
/* ADC_ADCSEQ2CONFIG[ACQPS] Bits */
#define ADC_ADCSEQ2CONFIG_ACQPS_OFS              (0)                             /* !< ACQPS Offset */
#define ADC_ADCSEQ2CONFIG_ACQPS_MASK             ((uint32_t)0x000000FFU)         /* !< SEQ2 Acquisition Prescale */
/* ADC_ADCSEQ2CONFIG[SAMPCAPRESETDISABLE] Bits */
#define ADC_ADCSEQ2CONFIG_SAMPCAPRESETDISABLE_OFS (9)                             /* !< SAMPCAPRESETDISABLE Offset */
#define ADC_ADCSEQ2CONFIG_SAMPCAPRESETDISABLE_MASK ((uint32_t)0x00000200U)         /* !< SEQ2 Sample Cap Reset Enable */
/* ADC_ADCSEQ2CONFIG[SAMPCAPRESETSEL] Bits */
#define ADC_ADCSEQ2CONFIG_SAMPCAPRESETSEL_OFS    (10)                            /* !< SAMPCAPRESETSEL Offset */
#define ADC_ADCSEQ2CONFIG_SAMPCAPRESETSEL_MASK   ((uint32_t)0x00000400U)         /* !< SEQ2 Sample Cap Reset Select */
/* ADC_ADCSEQ2CONFIG[SEQSTART] Bits */
#define ADC_ADCSEQ2CONFIG_SEQSTART_OFS           (15)                            /* !< SEQSTART Offset */
#define ADC_ADCSEQ2CONFIG_SEQSTART_MASK          ((uint32_t)0x00078000U)         /* !< Beginning SOC of SEQ2 */
/* ADC_ADCSEQ2CONFIG[TRIGSEL] Bits */
#define ADC_ADCSEQ2CONFIG_TRIGSEL_OFS            (20)                            /* !< TRIGSEL Offset */
#define ADC_ADCSEQ2CONFIG_TRIGSEL_MASK           ((uint32_t)0x01F00000U)         /* !< SEQ2 Trigger Source Select */
/* ADC_ADCSEQ2CONFIG[SEQSWFRC] Bits */
#define ADC_ADCSEQ2CONFIG_SEQSWFRC_OFS           (30)                            /* !< SEQSWFRC Offset */
#define ADC_ADCSEQ2CONFIG_SEQSWFRC_MASK          ((uint32_t)0x40000000U)         /* !< SEQ2 Software Force */
/* ADC_ADCSEQ2CONFIG[SEQENABLE] Bits */
#define ADC_ADCSEQ2CONFIG_SEQENABLE_OFS          (31)                            /* !< SEQENABLE Offset */
#define ADC_ADCSEQ2CONFIG_SEQENABLE_MASK         ((uint32_t)0x80000000U)         /* !< SEQ2Enable */

/* ADC_ADCSEQ3CONFIG Bits */
/* ADC_ADCSEQ3CONFIG[ACQPS] Bits */
#define ADC_ADCSEQ3CONFIG_ACQPS_OFS              (0)                             /* !< ACQPS Offset */
#define ADC_ADCSEQ3CONFIG_ACQPS_MASK             ((uint32_t)0x000000FFU)         /* !< SEQ3 Acquisition Prescale */
/* ADC_ADCSEQ3CONFIG[SAMPCAPRESETDISABLE] Bits */
#define ADC_ADCSEQ3CONFIG_SAMPCAPRESETDISABLE_OFS (9)                             /* !< SAMPCAPRESETDISABLE Offset */
#define ADC_ADCSEQ3CONFIG_SAMPCAPRESETDISABLE_MASK ((uint32_t)0x00000200U)         /* !< SEQ3 Sample Cap Reset Enable */
/* ADC_ADCSEQ3CONFIG[SAMPCAPRESETSEL] Bits */
#define ADC_ADCSEQ3CONFIG_SAMPCAPRESETSEL_OFS    (10)                            /* !< SAMPCAPRESETSEL Offset */
#define ADC_ADCSEQ3CONFIG_SAMPCAPRESETSEL_MASK   ((uint32_t)0x00000400U)         /* !< SEQ3 Sample Cap Reset Select */
/* ADC_ADCSEQ3CONFIG[SEQSTART] Bits */
#define ADC_ADCSEQ3CONFIG_SEQSTART_OFS           (15)                            /* !< SEQSTART Offset */
#define ADC_ADCSEQ3CONFIG_SEQSTART_MASK          ((uint32_t)0x00078000U)         /* !< Beginning SOC of SEQ3 */
/* ADC_ADCSEQ3CONFIG[TRIGSEL] Bits */
#define ADC_ADCSEQ3CONFIG_TRIGSEL_OFS            (20)                            /* !< TRIGSEL Offset */
#define ADC_ADCSEQ3CONFIG_TRIGSEL_MASK           ((uint32_t)0x01F00000U)         /* !< SEQ3 Trigger Source Select */
/* ADC_ADCSEQ3CONFIG[SEQSWFRC] Bits */
#define ADC_ADCSEQ3CONFIG_SEQSWFRC_OFS           (30)                            /* !< SEQSWFRC Offset */
#define ADC_ADCSEQ3CONFIG_SEQSWFRC_MASK          ((uint32_t)0x40000000U)         /* !< SEQ3 Software Force */
/* ADC_ADCSEQ3CONFIG[SEQENABLE] Bits */
#define ADC_ADCSEQ3CONFIG_SEQENABLE_OFS          (31)                            /* !< SEQENABLE Offset */
#define ADC_ADCSEQ3CONFIG_SEQENABLE_MASK         ((uint32_t)0x80000000U)         /* !< SEQ3Enable */

/* ADC_ADCSEQ4CONFIG Bits */
/* ADC_ADCSEQ4CONFIG[ACQPS] Bits */
#define ADC_ADCSEQ4CONFIG_ACQPS_OFS              (0)                             /* !< ACQPS Offset */
#define ADC_ADCSEQ4CONFIG_ACQPS_MASK             ((uint32_t)0x000000FFU)         /* !< SEQ4 Acquisition Prescale */
/* ADC_ADCSEQ4CONFIG[SAMPCAPRESETDISABLE] Bits */
#define ADC_ADCSEQ4CONFIG_SAMPCAPRESETDISABLE_OFS (9)                             /* !< SAMPCAPRESETDISABLE Offset */
#define ADC_ADCSEQ4CONFIG_SAMPCAPRESETDISABLE_MASK ((uint32_t)0x00000200U)         /* !< SEQ4 Sample Cap Reset Enable */
/* ADC_ADCSEQ4CONFIG[SAMPCAPRESETSEL] Bits */
#define ADC_ADCSEQ4CONFIG_SAMPCAPRESETSEL_OFS    (10)                            /* !< SAMPCAPRESETSEL Offset */
#define ADC_ADCSEQ4CONFIG_SAMPCAPRESETSEL_MASK   ((uint32_t)0x00000400U)         /* !< SEQ4 Sample Cap Reset Select */
/* ADC_ADCSEQ4CONFIG[SEQSTART] Bits */
#define ADC_ADCSEQ4CONFIG_SEQSTART_OFS           (15)                            /* !< SEQSTART Offset */
#define ADC_ADCSEQ4CONFIG_SEQSTART_MASK          ((uint32_t)0x00078000U)         /* !< Beginning SOC of SEQ4 */
/* ADC_ADCSEQ4CONFIG[TRIGSEL] Bits */
#define ADC_ADCSEQ4CONFIG_TRIGSEL_OFS            (20)                            /* !< TRIGSEL Offset */
#define ADC_ADCSEQ4CONFIG_TRIGSEL_MASK           ((uint32_t)0x01F00000U)         /* !< SEQ4 Trigger Source Select */
/* ADC_ADCSEQ4CONFIG[SEQSWFRC] Bits */
#define ADC_ADCSEQ4CONFIG_SEQSWFRC_OFS           (30)                            /* !< SEQSWFRC Offset */
#define ADC_ADCSEQ4CONFIG_SEQSWFRC_MASK          ((uint32_t)0x40000000U)         /* !< SEQ4 Software Force */
/* ADC_ADCSEQ4CONFIG[SEQENABLE] Bits */
#define ADC_ADCSEQ4CONFIG_SEQENABLE_OFS          (31)                            /* !< SEQENABLE Offset */
#define ADC_ADCSEQ4CONFIG_SEQENABLE_MASK         ((uint32_t)0x80000000U)         /* !< SEQ4Enable */


#ifdef __cplusplus
}
#endif

#endif /* hw_adc__include */
