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

#ifndef hw_sysctl__include
#define hw_sysctl__include


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
* SYSCTL Registers
******************************************************************************/
#define SYSCTL_SOCLOCK_OFS                       ((uint32_t)0x00001000U)


/** @addtogroup SYSCTL_SOCLOCK
  @{
*/

typedef struct {
       uint32_t RESERVED0[8];
  __I  uint32_t IIDX;                              /* !< (@ 0x00001020) SYSCTL interrupt index */
       uint32_t RESERVED1;
  __IO uint32_t IMASK;                             /* !< (@ 0x00001028) SYSCTL interrupt mask */
       uint32_t RESERVED2;
  __I  uint32_t RIS;                               /* !< (@ 0x00001030) SYSCTL raw interrupt status */
       uint32_t RESERVED3;
  __I  uint32_t MIS;                               /* !< (@ 0x00001038) SYSCTL masked interrupt status */
       uint32_t RESERVED4;
  __O  uint32_t ISET;                              /* !< (@ 0x00001040) SYSCTL interrupt set */
       uint32_t RESERVED5;
  __O  uint32_t ICLR;                              /* !< (@ 0x00001048) SYSCTL interrupt clear */
       uint32_t RESERVED6;
  __I  uint32_t NMIIIDX;                           /* !< (@ 0x00001050) NMI interrupt index */
       uint32_t RESERVED7[3];
  __I  uint32_t NMIRIS;                            /* !< (@ 0x00001060) NMI raw interrupt status */
       uint32_t RESERVED8[3];
  __O  uint32_t NMIISET;                           /* !< (@ 0x00001070) NMI interrupt set */
       uint32_t RESERVED9;
  __O  uint32_t NMIICLR;                           /* !< (@ 0x00001078) NMI interrupt clear */
       uint32_t RESERVED10[33];
  __IO uint32_t SYSOSCCFG;                         /* !< (@ 0x00001100) SYSOSC configuration */
  __IO uint32_t MCLKCFG;                           /* !< (@ 0x00001104) Main clock (MCLK) configuration */
  __IO uint32_t HSCLKEN;                           /* !< (@ 0x00001108) High-speed clock (HSCLK) source enable/disable */
  __IO uint32_t HSCLKCFG;                          /* !< (@ 0x0000110C) High-speed clock (HSCLK) source selection */
  __IO uint32_t HFCLKCLKCFG;                       /* !< (@ 0x00001110) High-frequency clock (HFCLK) configuration */
       uint32_t RESERVED11[3];
  __IO uint32_t SYSPLLCFG0;                        /* !< (@ 0x00001120) SYSPLL reference and output configuration */
  __IO uint32_t SYSPLLCFG1;                        /* !< (@ 0x00001124) SYSPLL reference and feedback divider */
  __IO uint32_t SYSPLLPARAM0;                      /* !< (@ 0x00001128) SYSPLL PARAM0 (load from FACTORY region) */
  __IO uint32_t SYSPLLPARAM1;                      /* !< (@ 0x0000112C) SYSPLL PARAM1 (load from FACTORY region) */
  __IO uint32_t SYSPLLPARAM2;                      /* !< (@ 0x00001130) SYSPLL PARAM2 (load from FACTORY region) */
  __IO uint32_t SYSPLLLDOCTL;                      /* !< (@ 0x00001134) SYSPLL LDO CTL (load from FACTORY region) */
  __IO uint32_t SYSPLLLDOPROG;                     /* !< (@ 0x00001138) SYSPLL LDO VOUT PROG (load from FACTORY region) */
  __IO uint32_t GENCLKEN;                          /* !< (@ 0x0000113C) General clock enable control */
  __IO uint32_t GENCLKCFG;                         /* !< (@ 0x00001140) General clock configuration */
  __IO uint32_t PMODECFG;                          /* !< (@ 0x00001144) Power mode configuration */
  __IO uint32_t MLDOLPENCFG;                       /* !< (@ 0x00001148) LDO Configuration Control */
       uint32_t RESERVED12;
  __I  uint32_t FCC;                               /* !< (@ 0x00001150) Frequency clock counter (FCC) count */
  __IO uint32_t PMULDOSPARECTL;                    /* !< (@ 0x00001154) LDO Spare Control */
  __IO uint32_t SYSCTL_ECO_REG1;                   /* !< (@ 0x00001158) Sysctl ECO Reg 1 */
  __IO uint32_t SYSCTL_ECO_REG2;                   /* !< (@ 0x0000115C) Sysctl ECO Reg 2 */
       uint32_t RESERVED13[8];
  __IO uint32_t SYSTEMCFG;                         /* !< (@ 0x00001180) System configuration */
  __IO uint32_t SRAMCFG;                           /* !< (@ 0x00001184) System SRAM configuration */
       uint32_t RESERVED14[30];
  __IO uint32_t WRITELOCK;                         /* !< (@ 0x00001200) SYSCTL register write lockout */
  __I  uint32_t CLKSTATUS;                         /* !< (@ 0x00001204) Clock module (CKM) status */
  __I  uint32_t SYSSTATUS;                         /* !< (@ 0x00001208) System status information */
       uint32_t RESERVED15[5];
  __I  uint32_t RSTCAUSE;                          /* !< (@ 0x00001220) Reset cause */
       uint32_t RESERVED16[55];
  __IO uint32_t RESETLEVEL;                        /* !< (@ 0x00001300) Reset level for application-triggered reset
                                                      command */
  __O  uint32_t RESETCMD;                          /* !< (@ 0x00001304) Execute an application-triggered reset command */
       uint32_t RESERVED17[2];
  __O  uint32_t SYSOSCFCLCTL;                      /* !< (@ 0x00001310) SYSOSC frequency correction loop (FCL) ROSC enable */
       uint32_t RESERVED18[2];
  __O  uint32_t SHDNIOREL;                         /* !< (@ 0x0000131C) SHUTDOWN IO release control */
  __O  uint32_t EXRSTPIN;                          /* !< (@ 0x00001320) Disable the reset function of the NRST pin */
  __O  uint32_t SYSSTATUSCLR;                      /* !< (@ 0x00001324) Clear sticky bits of SYSSTATUS */
  __O  uint32_t SWDJCFG;                           /* !< (@ 0x00001328) Disable the SWD/JTAG function on the SWD/JTAG pins */
  __O  uint32_t FCCCMD;                            /* !< (@ 0x0000132C) Frequency clock counter start capture */
       uint32_t RESERVED19[52];
  __IO uint32_t SHUTDNSTORE0;                      /* !< (@ 0x00001400) Shutdown storage memory (byte 0) */
  __IO uint32_t SHUTDNSTORE1;                      /* !< (@ 0x00001404) Shutdown storage memory (byte 1) */
  __IO uint32_t SHUTDNSTORE2;                      /* !< (@ 0x00001408) Shutdown storage memory (byte 2) */
  __IO uint32_t SHUTDNSTORE3;                      /* !< (@ 0x0000140C) Shutdown storage memory (byte 3) */
  __IO uint32_t ADCSEQFRCGB;                       /* !< (@ 0x00001410) ADC Global Sequence Force */
  __IO uint32_t ADCSEQFRCGBSEL;                    /* !< (@ 0x00001414) ADC Global Sequence Force Select */
  __IO uint32_t M33SPARESOCLOCK1;                  /* !< (@ 0x00001418) M33C1 Spare SOC LOCK Reg 1 */
  __IO uint32_t M33SPARESOCLOCK2;                  /* !< (@ 0x0000141C) M33C1 Spare SOC LOCK Reg 2 */
  __IO uint32_t SYSCTL_READ_REG;                   /* !< (@ 0x00001420) Sysctl read only Reg */
  __IO uint32_t PWREN_MCPERIPH;                    /* !< (@ 0x00001424) Register to control the power state */
  __O  uint32_t RSTCTL_ASSERT_MCPERIPH;            /* !< (@ 0x00001428) rstctl assert register to control reset assertion
                                                      - Write Only Register, Always Read as 0 */
  __O  uint32_t RSTCTL_CLEAR_MCPERIPH;             /* !< (@ 0x0000142C) rstctl clear register to control reset
                                                      de-assertion - Write Only Register, Always Read as 0 */
  __I  uint32_t STAT_MCPERIPH;                     /* !< (@ 0x00001430) IP State Register - Read Only */
  __IO uint32_t PWREN_SYSPERIPH;                   /* !< (@ 0x00001434) Register to control the power state */
  __O  uint32_t RSTCTL_ASSERT_SYSPERIPH;           /* !< (@ 0x00001438) rstcl assert Register - Write Only Register,
                                                      Always Read as 0 */
  __O  uint32_t RSTCTL_CLEAR_SYSPERIPH;            /* !< (@ 0x0000143C) rstctl clear register to control reset
                                                      de-assertion - Write Only Register, Always Read as 0 */
  __I  uint32_t STAT_SYSPERIPH;                    /* !< (@ 0x00001440) IP State Register - Read Only */
  __IO uint32_t CMPHPMXSEL;                        /* !< (@ 0x00001444) Bits to select one of the many sources on CompHP
                                                      inputs. Refer to Pinmux diagram for details. */
       uint32_t RESERVED20;
  __IO uint32_t CMPLPMXSEL;                        /* !< (@ 0x0000144C) Bits to select one of the many sources on CompLP
                                                      inputs. Refer to Pinmux diagram for details. */
  __IO uint32_t CMPHNMXSEL;                        /* !< (@ 0x00001450) Bits to select one of the many sources on CompHN
                                                      inputs. Refer to Pinmux diagram for details. */
  __IO uint32_t CMPLNMXSEL;                        /* !< (@ 0x00001454) Bits to select one of the many sources on CompLN
                                                      inputs. Refer to Pinmux diagram for details. */
  __IO uint32_t TSNSCFG;                           /* !< (@ 0x00001458) Temperature Sensor Config Register */
  __IO uint32_t TSNSSCTL;                          /* !< (@ 0x0000145C) Temperature Sensor Control Register */
  __IO uint32_t PGACONFIG;                         /* !< (@ 0x00001460) PGA Configuration Register */
  __IO uint32_t REFCONFIGA;                        /* !< (@ 0x00001464) Reference Configuration Regsiter */
  __IO uint32_t INTERNALTESTCTL;                   /* !< (@ 0x00001468) Internal Test Node Control Register */
  __IO uint32_t I2VCTL;                            /* !< (@ 0x0000146C) I2V Logic Control */
  __IO uint32_t ADCDACLOOPBACK;                    /* !< (@ 0x00001470) Not used in AM13 */
  __IO uint32_t XTALCR;                            /* !< (@ 0x00001474) XTAL Control Register */
  __IO uint32_t XTALCR2;                           /* !< (@ 0x00001478) XTAL Control Register for pad init */
  __IO uint32_t X1CNT;                             /* !< (@ 0x0000147C) x1cnt status register */
  __IO uint32_t CMPSSCTL;                          /* !< (@ 0x00001480) CMPSS control register */
  __IO uint32_t CMPSSDACBUFCONFIG;                 /* !< (@ 0x00001484) Config bits for CMPSS DAC buffer */
  __IO uint32_t ANAREFCTL;                         /* !< (@ 0x00001488) Analog Reference Select */
  __IO uint32_t PERCLKCR;                          /* !< (@ 0x0000148C) PWM Time Base Clock sync */
  __IO uint32_t ADC_MMR_OVRD_CTL;                  /* !< (@ 0x00001490) ADC MMR Override control register for DFT: Control
                                                      ADC enable override */
  __IO uint32_t ADC_MMR_OVRD_VAL;                  /* !< (@ 0x00001494) ADC MMR Override value register for DFT : Value of
                                                      ADC enable override */
  __IO uint32_t VREGCONFIGDEBUG;                   /* !< (@ 0x00001498) VREG Configuration Debug Register */
  __IO uint32_t VREGCONFIGDFT;                     /* !< (@ 0x0000149C) VREG Configuration DFT Register */
  __IO uint32_t AM13SPAREIREFENSOCLOCK;            /* !< (@ 0x000014A0) AM13 Spare IREFEN SOC LOCK Reg */
  __IO uint32_t AM13SPARESOCLOCK2;                 /* !< (@ 0x000014A4) AM13 Spare SOC LOCK Reg 2 */
  __IO uint32_t AM13SPARESOCLOCK3;                 /* !< (@ 0x000014A8) AM13 Spare SOC LOCK Reg 3 */
  __IO uint32_t AM13SPARESOCLOCK4;                 /* !< (@ 0x000014AC) AM13 Spare SOC LOCK Reg 4 */
} SYSCTL_SOCLOCK_Regs;

/*@}*/ /* end of group SYSCTL_SOCLOCK */

/** @addtogroup SYSCTL
  @{
*/

typedef struct {
       uint32_t RESERVED0[1024];
  SYSCTL_SOCLOCK_Regs  SOCLOCK;                           /* !< (@ 0x00001000) SYSCTL SOCLOCK Region */
} SYSCTL_Regs;

/*@}*/ /* end of group SYSCTL */



/******************************************************************************
* SYSCTL Register Offsets
******************************************************************************/

#define SYSCTL_IIDX                              (0x00001020U)
#define SYSCTL_IMASK                             (0x00001028U)
#define SYSCTL_RIS                               (0x00001030U)
#define SYSCTL_MIS                               (0x00001038U)
#define SYSCTL_ISET                              (0x00001040U)
#define SYSCTL_ICLR                              (0x00001048U)
#define SYSCTL_NMIIIDX                           (0x00001050U)
#define SYSCTL_NMIRIS                            (0x00001060U)
#define SYSCTL_NMIISET                           (0x00001070U)
#define SYSCTL_NMIICLR                           (0x00001078U)
#define SYSCTL_SYSOSCCFG                         (0x00001100U)
#define SYSCTL_MCLKCFG                           (0x00001104U)
#define SYSCTL_HSCLKEN                           (0x00001108U)
#define SYSCTL_HSCLKCFG                          (0x0000110CU)
#define SYSCTL_HFCLKCLKCFG                       (0x00001110U)
#define SYSCTL_SYSPLLCFG0                        (0x00001120U)
#define SYSCTL_SYSPLLCFG1                        (0x00001124U)
#define SYSCTL_SYSPLLPARAM0                      (0x00001128U)
#define SYSCTL_SYSPLLPARAM1                      (0x0000112CU)
#define SYSCTL_SYSPLLPARAM2                      (0x00001130U)
#define SYSCTL_SYSPLLLDOCTL                      (0x00001134U)
#define SYSCTL_SYSPLLLDOPROG                     (0x00001138U)
#define SYSCTL_GENCLKEN                          (0x0000113CU)
#define SYSCTL_GENCLKCFG                         (0x00001140U)
#define SYSCTL_PMODECFG                          (0x00001144U)
#define SYSCTL_MLDOLPENCFG                       (0x00001148U)
#define SYSCTL_FCC                               (0x00001150U)
#define SYSCTL_PMULDOSPARECTL                    (0x00001154U)
#define SYSCTL_SYSCTL_ECO_REG1                   (0x00001158U)
#define SYSCTL_SYSCTL_ECO_REG2                   (0x0000115CU)
#define SYSCTL_SYSTEMCFG                         (0x00001180U)
#define SYSCTL_SRAMCFG                           (0x00001184U)
#define SYSCTL_WRITELOCK                         (0x00001200U)
#define SYSCTL_CLKSTATUS                         (0x00001204U)
#define SYSCTL_SYSSTATUS                         (0x00001208U)
#define SYSCTL_RSTCAUSE                          (0x00001220U)
#define SYSCTL_RESETLEVEL                        (0x00001300U)
#define SYSCTL_RESETCMD                          (0x00001304U)
#define SYSCTL_SYSOSCFCLCTL                      (0x00001310U)
#define SYSCTL_SHDNIOREL                         (0x0000131CU)
#define SYSCTL_EXRSTPIN                          (0x00001320U)
#define SYSCTL_SYSSTATUSCLR                      (0x00001324U)
#define SYSCTL_SWDJCFG                           (0x00001328U)
#define SYSCTL_FCCCMD                            (0x0000132CU)
#define SYSCTL_SHUTDNSTORE0                      (0x00001400U)
#define SYSCTL_SHUTDNSTORE1                      (0x00001404U)
#define SYSCTL_SHUTDNSTORE2                      (0x00001408U)
#define SYSCTL_SHUTDNSTORE3                      (0x0000140CU)
#define SYSCTL_ADCSEQFRCGB                       (0x00001410U)
#define SYSCTL_ADCSEQFRCGBSEL                    (0x00001414U)
#define SYSCTL_M33SPARESOCLOCK1                  (0x00001418U)
#define SYSCTL_M33SPARESOCLOCK2                  (0x0000141CU)
#define SYSCTL_SYSCTL_READ_REG                   (0x00001420U)
#define SYSCTL_PWREN_MCPERIPH                    (0x00001424U)
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH            (0x00001428U)
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH             (0x0000142CU)
#define SYSCTL_STAT_MCPERIPH                     (0x00001430U)
#define SYSCTL_PWREN_SYSPERIPH                   (0x00001434U)
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH           (0x00001438U)
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH            (0x0000143CU)
#define SYSCTL_STAT_SYSPERIPH                    (0x00001440U)
#define SYSCTL_CMPHPMXSEL                        (0x00001444U)
#define SYSCTL_CMPLPMXSEL                        (0x0000144CU)
#define SYSCTL_CMPHNMXSEL                        (0x00001450U)
#define SYSCTL_CMPLNMXSEL                        (0x00001454U)
#define SYSCTL_TSNSCFG                           (0x00001458U)
#define SYSCTL_TSNSSCTL                          (0x0000145CU)
#define SYSCTL_PGACONFIG                         (0x00001460U)
#define SYSCTL_REFCONFIGA                        (0x00001464U)
#define SYSCTL_INTERNALTESTCTL                   (0x00001468U)
#define SYSCTL_I2VCTL                            (0x0000146CU)
#define SYSCTL_ADCDACLOOPBACK                    (0x00001470U)
#define SYSCTL_XTALCR                            (0x00001474U)
#define SYSCTL_XTALCR2                           (0x00001478U)
#define SYSCTL_X1CNT                             (0x0000147CU)
#define SYSCTL_CMPSSCTL                          (0x00001480U)
#define SYSCTL_CMPSSDACBUFCONFIG                 (0x00001484U)
#define SYSCTL_ANAREFCTL                         (0x00001488U)
#define SYSCTL_PERCLKCR                          (0x0000148CU)
#define SYSCTL_ADC_MMR_OVRD_CTL                  (0x00001490U)
#define SYSCTL_ADC_MMR_OVRD_VAL                  (0x00001494U)
#define SYSCTL_VREGCONFIGDEBUG                   (0x00001498U)
#define SYSCTL_VREGCONFIGDFT                     (0x0000149CU)
#define SYSCTL_AM13SPAREIREFENSOCLOCK            (0x000014A0U)
#define SYSCTL_AM13SPARESOCLOCK2                 (0x000014A4U)
#define SYSCTL_AM13SPARESOCLOCK3                 (0x000014A8U)
#define SYSCTL_AM13SPARESOCLOCK4                 (0x000014ACU)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* SYSCTL Register Control Bits
******************************************************************************/

/* SYSCTL_IIDX Bits */
/* SYSCTL_IIDX[STAT] Bits */
#define SYSCTL_IIDX_STAT_OFS                     (0)                             /* !< STAT Offset */
#define SYSCTL_IIDX_STAT_MASK                    ((uint32_t)0x00000007U)         /* !< The SYSCTL interrupt index (IIDX)
                                                                                    register generates a value
                                                                                    corresponding to the highest priority
                                                                                    pending interrupt source.  This value
                                                                                    may be used as an address offset for
                                                                                    fast, deterministic handling in the
                                                                                    interrupt service routine.  A read of
                                                                                    the IIDX register will clear the
                                                                                    corresponding interrupt status in the
                                                                                    RIS and MIS registers. */
#define SYSCTL_IIDX_STAT_NO_INTR                 ((uint32_t)0x00000000U)         /* !< No interrupt pending */
#define SYSCTL_IIDX_STAT_LFOSCGOOD               ((uint32_t)0x00000001U)         /* !< LFOSCGOOD interrupt pending */
#define SYSCTL_IIDX_STAT_ANACLKERR               ((uint32_t)0x00000002U)
#define SYSCTL_IIDX_STAT_FLASHSEC                ((uint32_t)0x00000003U)
#define SYSCTL_IIDX_STAT_SRAMSEC                 ((uint32_t)0x00000004U)
#define SYSCTL_IIDX_STAT_HFCLKGOOD               ((uint32_t)0x00000005U)
#define SYSCTL_IIDX_STAT_SYSPLLGOOD              ((uint32_t)0x00000006U)
#define SYSCTL_IIDX_STAT_HSCLKGOOD               ((uint32_t)0x00000007U)

/* SYSCTL_IMASK Bits */
/* SYSCTL_IMASK[LFOSCGOOD] Bits */
#define SYSCTL_IMASK_LFOSCGOOD_OFS               (0)                             /* !< LFOSCGOOD Offset */
#define SYSCTL_IMASK_LFOSCGOOD_MASK              ((uint32_t)0x00000001U)         /* !< Enable or disable the LFOSCGOOD
                                                                                    interrupt. LFOSCGOOD indicates that
                                                                                    the LFOSC has started successfully. */
#define SYSCTL_IMASK_LFOSCGOOD_DISABLE           ((uint32_t)0x00000000U)         /* !< Interrupt disabled */
#define SYSCTL_IMASK_LFOSCGOOD_ENABLE            ((uint32_t)0x00000001U)         /* !< Interrupt enabled */
/* SYSCTL_IMASK[HFCLKGOOD] Bits */
#define SYSCTL_IMASK_HFCLKGOOD_OFS               (4)                             /* !< HFCLKGOOD Offset */
#define SYSCTL_IMASK_HFCLKGOOD_MASK              ((uint32_t)0x00000010U)         /* !< HFCLK GOOD */
#define SYSCTL_IMASK_HFCLKGOOD_DISABLE           ((uint32_t)0x00000000U)
#define SYSCTL_IMASK_HFCLKGOOD_ENABLE            ((uint32_t)0x00000010U)
/* SYSCTL_IMASK[SYSPLLGOOD] Bits */
#define SYSCTL_IMASK_SYSPLLGOOD_OFS              (5)                             /* !< SYSPLLGOOD Offset */
#define SYSCTL_IMASK_SYSPLLGOOD_MASK             ((uint32_t)0x00000020U)         /* !< SYSPLL GOOD */
#define SYSCTL_IMASK_SYSPLLGOOD_DISABLE          ((uint32_t)0x00000000U)
#define SYSCTL_IMASK_SYSPLLGOOD_ENABLE           ((uint32_t)0x00000020U)
/* SYSCTL_IMASK[HSCLKGOOD] Bits */
#define SYSCTL_IMASK_HSCLKGOOD_OFS               (6)                             /* !< HSCLKGOOD Offset */
#define SYSCTL_IMASK_HSCLKGOOD_MASK              ((uint32_t)0x00000040U)         /* !< HSCLK GOOD */
#define SYSCTL_IMASK_HSCLKGOOD_DISABLE           ((uint32_t)0x00000000U)
#define SYSCTL_IMASK_HSCLKGOOD_ENABLE            ((uint32_t)0x00000040U)
/* SYSCTL_IMASK[FLASHSEC] Bits */
#define SYSCTL_IMASK_FLASHSEC_OFS                (2)                             /* !< FLASHSEC Offset */
#define SYSCTL_IMASK_FLASHSEC_MASK               ((uint32_t)0x00000004U)         /* !< Flash Single Error Correct */
#define SYSCTL_IMASK_FLASHSEC_DISABLE            ((uint32_t)0x00000000U)
#define SYSCTL_IMASK_FLASHSEC_ENABLE             ((uint32_t)0x00000004U)

/* SYSCTL_RIS Bits */
/* SYSCTL_RIS[LFOSCGOOD] Bits */
#define SYSCTL_RIS_LFOSCGOOD_OFS                 (0)                             /* !< LFOSCGOOD Offset */
#define SYSCTL_RIS_LFOSCGOOD_MASK                ((uint32_t)0x00000001U)         /* !< Raw status of the LFOSCGOOD
                                                                                    interrupt. */
#define SYSCTL_RIS_LFOSCGOOD_FALSE               ((uint32_t)0x00000000U)         /* !< No interrupt pending */
#define SYSCTL_RIS_LFOSCGOOD_TRUE                ((uint32_t)0x00000001U)         /* !< Interrupt pending */
/* SYSCTL_RIS[HFCLKGOOD] Bits */
#define SYSCTL_RIS_HFCLKGOOD_OFS                 (4)                             /* !< HFCLKGOOD Offset */
#define SYSCTL_RIS_HFCLKGOOD_MASK                ((uint32_t)0x00000010U)         /* !< HFCLK GOOD */
#define SYSCTL_RIS_HFCLKGOOD_FALSE               ((uint32_t)0x00000000U)
#define SYSCTL_RIS_HFCLKGOOD_TRUE                ((uint32_t)0x00000010U)
/* SYSCTL_RIS[SYSPLLGOOD] Bits */
#define SYSCTL_RIS_SYSPLLGOOD_OFS                (5)                             /* !< SYSPLLGOOD Offset */
#define SYSCTL_RIS_SYSPLLGOOD_MASK               ((uint32_t)0x00000020U)         /* !< SYSPLL GOOD */
#define SYSCTL_RIS_SYSPLLGOOD_FALSE              ((uint32_t)0x00000000U)
#define SYSCTL_RIS_SYSPLLGOOD_TRUE               ((uint32_t)0x00000020U)
/* SYSCTL_RIS[HSCLKGOOD] Bits */
#define SYSCTL_RIS_HSCLKGOOD_OFS                 (6)                             /* !< HSCLKGOOD Offset */
#define SYSCTL_RIS_HSCLKGOOD_MASK                ((uint32_t)0x00000040U)         /* !< HSCLK GOOD */
#define SYSCTL_RIS_HSCLKGOOD_FALSE               ((uint32_t)0x00000000U)
#define SYSCTL_RIS_HSCLKGOOD_TRUE                ((uint32_t)0x00000040U)
/* SYSCTL_RIS[FLASHSEC] Bits */
#define SYSCTL_RIS_FLASHSEC_OFS                  (2)                             /* !< FLASHSEC Offset */
#define SYSCTL_RIS_FLASHSEC_MASK                 ((uint32_t)0x00000004U)         /* !< Flash Single Error Correct */
#define SYSCTL_RIS_FLASHSEC_FALSE                ((uint32_t)0x00000000U)
#define SYSCTL_RIS_FLASHSEC_TRUE                 ((uint32_t)0x00000004U)

/* SYSCTL_MIS Bits */
/* SYSCTL_MIS[LFOSCGOOD] Bits */
#define SYSCTL_MIS_LFOSCGOOD_OFS                 (0)                             /* !< LFOSCGOOD Offset */
#define SYSCTL_MIS_LFOSCGOOD_MASK                ((uint32_t)0x00000001U)         /* !< Masked status of the LFOSCGOOD
                                                                                    interrupt. */
#define SYSCTL_MIS_LFOSCGOOD_FALSE               ((uint32_t)0x00000000U)         /* !< No interrupt pending */
#define SYSCTL_MIS_LFOSCGOOD_TRUE                ((uint32_t)0x00000001U)         /* !< Interrupt pending */
/* SYSCTL_MIS[HFCLKGOOD] Bits */
#define SYSCTL_MIS_HFCLKGOOD_OFS                 (4)                             /* !< HFCLKGOOD Offset */
#define SYSCTL_MIS_HFCLKGOOD_MASK                ((uint32_t)0x00000010U)         /* !< HFCLK GOOD */
#define SYSCTL_MIS_HFCLKGOOD_FALSE               ((uint32_t)0x00000000U)
#define SYSCTL_MIS_HFCLKGOOD_TRUE                ((uint32_t)0x00000010U)
/* SYSCTL_MIS[SYSPLLGOOD] Bits */
#define SYSCTL_MIS_SYSPLLGOOD_OFS                (5)                             /* !< SYSPLLGOOD Offset */
#define SYSCTL_MIS_SYSPLLGOOD_MASK               ((uint32_t)0x00000020U)         /* !< SYSPLL GOOD */
#define SYSCTL_MIS_SYSPLLGOOD_FALSE              ((uint32_t)0x00000000U)
#define SYSCTL_MIS_SYSPLLGOOD_TRUE               ((uint32_t)0x00000020U)
/* SYSCTL_MIS[HSCLKGOOD] Bits */
#define SYSCTL_MIS_HSCLKGOOD_OFS                 (6)                             /* !< HSCLKGOOD Offset */
#define SYSCTL_MIS_HSCLKGOOD_MASK                ((uint32_t)0x00000040U)         /* !< HSCLK GOOD */
#define SYSCTL_MIS_HSCLKGOOD_FALSE               ((uint32_t)0x00000000U)
#define SYSCTL_MIS_HSCLKGOOD_TRUE                ((uint32_t)0x00000040U)
/* SYSCTL_MIS[FLASHSEC] Bits */
#define SYSCTL_MIS_FLASHSEC_OFS                  (2)                             /* !< FLASHSEC Offset */
#define SYSCTL_MIS_FLASHSEC_MASK                 ((uint32_t)0x00000004U)         /* !< Flash Single Error Correct */
#define SYSCTL_MIS_FLASHSEC_FALSE                ((uint32_t)0x00000000U)
#define SYSCTL_MIS_FLASHSEC_TRUE                 ((uint32_t)0x00000004U)

/* SYSCTL_ISET Bits */
/* SYSCTL_ISET[LFOSCGOOD] Bits */
#define SYSCTL_ISET_LFOSCGOOD_OFS                (0)                             /* !< LFOSCGOOD Offset */
#define SYSCTL_ISET_LFOSCGOOD_MASK               ((uint32_t)0x00000001U)         /* !< Set the LFOSCGOOD interrupt. */
#define SYSCTL_ISET_LFOSCGOOD_NO_EFFECT          ((uint32_t)0x00000000U)         /* !< Writing 0h has no effect */
#define SYSCTL_ISET_LFOSCGOOD_SET                ((uint32_t)0x00000001U)         /* !< Set interrupt */
/* SYSCTL_ISET[HFCLKGOOD] Bits */
#define SYSCTL_ISET_HFCLKGOOD_OFS                (4)                             /* !< HFCLKGOOD Offset */
#define SYSCTL_ISET_HFCLKGOOD_MASK               ((uint32_t)0x00000010U)         /* !< HFCLK GOOD */
#define SYSCTL_ISET_HFCLKGOOD_NO_EFFECT          ((uint32_t)0x00000000U)
#define SYSCTL_ISET_HFCLKGOOD_SET                ((uint32_t)0x00000010U)
/* SYSCTL_ISET[SYSPLLGOOD] Bits */
#define SYSCTL_ISET_SYSPLLGOOD_OFS               (5)                             /* !< SYSPLLGOOD Offset */
#define SYSCTL_ISET_SYSPLLGOOD_MASK              ((uint32_t)0x00000020U)         /* !< SYSPLL GOOD */
#define SYSCTL_ISET_SYSPLLGOOD_NO_EFFECT         ((uint32_t)0x00000000U)
#define SYSCTL_ISET_SYSPLLGOOD_SET               ((uint32_t)0x00000020U)
/* SYSCTL_ISET[HSCLKGOOD] Bits */
#define SYSCTL_ISET_HSCLKGOOD_OFS                (6)                             /* !< HSCLKGOOD Offset */
#define SYSCTL_ISET_HSCLKGOOD_MASK               ((uint32_t)0x00000040U)         /* !< HSCLK GOOD */
#define SYSCTL_ISET_HSCLKGOOD_NO_EFFECT          ((uint32_t)0x00000000U)
#define SYSCTL_ISET_HSCLKGOOD_SET                ((uint32_t)0x00000040U)
/* SYSCTL_ISET[FLASHSEC] Bits */
#define SYSCTL_ISET_FLASHSEC_OFS                 (2)                             /* !< FLASHSEC Offset */
#define SYSCTL_ISET_FLASHSEC_MASK                ((uint32_t)0x00000004U)         /* !< Flash Single Error Correct */
#define SYSCTL_ISET_FLASHSEC_NO_EFFECT           ((uint32_t)0x00000000U)
#define SYSCTL_ISET_FLASHSEC_SET                 ((uint32_t)0x00000004U)

/* SYSCTL_ICLR Bits */
/* SYSCTL_ICLR[LFOSCGOOD] Bits */
#define SYSCTL_ICLR_LFOSCGOOD_OFS                (0)                             /* !< LFOSCGOOD Offset */
#define SYSCTL_ICLR_LFOSCGOOD_MASK               ((uint32_t)0x00000001U)         /* !< Clear the LFOSCGOOD interrupt. */
#define SYSCTL_ICLR_LFOSCGOOD_NO_EFFECT          ((uint32_t)0x00000000U)         /* !< Writing 0h has no effect */
#define SYSCTL_ICLR_LFOSCGOOD_CLR                ((uint32_t)0x00000001U)         /* !< Clear interrupt */
/* SYSCTL_ICLR[HFCLKGOOD] Bits */
#define SYSCTL_ICLR_HFCLKGOOD_OFS                (4)                             /* !< HFCLKGOOD Offset */
#define SYSCTL_ICLR_HFCLKGOOD_MASK               ((uint32_t)0x00000010U)         /* !< HFCLK GOOD */
#define SYSCTL_ICLR_HFCLKGOOD_NO_EFFECT          ((uint32_t)0x00000000U)
#define SYSCTL_ICLR_HFCLKGOOD_CLR                ((uint32_t)0x00000010U)
/* SYSCTL_ICLR[SYSPLLGOOD] Bits */
#define SYSCTL_ICLR_SYSPLLGOOD_OFS               (5)                             /* !< SYSPLLGOOD Offset */
#define SYSCTL_ICLR_SYSPLLGOOD_MASK              ((uint32_t)0x00000020U)         /* !< SYSPLL GOOD */
#define SYSCTL_ICLR_SYSPLLGOOD_NO_EFFECT         ((uint32_t)0x00000000U)
#define SYSCTL_ICLR_SYSPLLGOOD_CLR               ((uint32_t)0x00000020U)
/* SYSCTL_ICLR[HSCLKGOOD] Bits */
#define SYSCTL_ICLR_HSCLKGOOD_OFS                (6)                             /* !< HSCLKGOOD Offset */
#define SYSCTL_ICLR_HSCLKGOOD_MASK               ((uint32_t)0x00000040U)         /* !< HSCLK GOOD */
#define SYSCTL_ICLR_HSCLKGOOD_NO_EFFECT          ((uint32_t)0x00000000U)
#define SYSCTL_ICLR_HSCLKGOOD_CLR                ((uint32_t)0x00000040U)
/* SYSCTL_ICLR[FLASHSEC] Bits */
#define SYSCTL_ICLR_FLASHSEC_OFS                 (2)                             /* !< FLASHSEC Offset */
#define SYSCTL_ICLR_FLASHSEC_MASK                ((uint32_t)0x00000004U)         /* !< Flash Single Error Correct */
#define SYSCTL_ICLR_FLASHSEC_NO_EFFECT           ((uint32_t)0x00000000U)
#define SYSCTL_ICLR_FLASHSEC_CLR                 ((uint32_t)0x00000004U)

/* SYSCTL_NMIIIDX Bits */
/* SYSCTL_NMIIIDX[STAT] Bits */
#define SYSCTL_NMIIIDX_STAT_OFS                  (0)                             /* !< STAT Offset */
#define SYSCTL_NMIIIDX_STAT_MASK                 ((uint32_t)0x00000007U)         /* !< The NMI interrupt index (NMIIIDX)
                                                                                    register generates a value
                                                                                    corresponding to the highest priority
                                                                                    pending NMI source.  This value may
                                                                                    be used as an address offset for
                                                                                    fast, deterministic handling in the
                                                                                    NMI service routine.  A read of the
                                                                                    NMIIIDX register will clear the
                                                                                    corresponding interrupt status in the
                                                                                    NMIRIS register. */
#define SYSCTL_NMIIIDX_STAT_NO_INTR              ((uint32_t)0x00000000U)         /* !< No NMI pending */
#define SYSCTL_NMIIIDX_STAT_BORLVL               ((uint32_t)0x00000001U)         /* !< Reserved */
#define SYSCTL_NMIIIDX_STAT_WWDT0                ((uint32_t)0x00000002U)
#define SYSCTL_NMIIIDX_STAT_SECURITY             ((uint32_t)0x00000003U)
#define SYSCTL_NMIIIDX_STAT_FLASHDED             ((uint32_t)0x00000004U)
#define SYSCTL_NMIIIDX_STAT_SRAMPAR              ((uint32_t)0x00000005U)
#define SYSCTL_NMIIIDX_STAT_TMUROMPAR            ((uint32_t)0x00000006U)
#define SYSCTL_NMIIIDX_STAT_SYSMEMACC            ((uint32_t)0x00000007U)

/* SYSCTL_NMIRIS Bits */
/* SYSCTL_NMIRIS[SECURITY] Bits */
#define SYSCTL_NMIRIS_SECURITY_OFS               (2)                             /* !< SECURITY Offset */
#define SYSCTL_NMIRIS_SECURITY_MASK              ((uint32_t)0x00000004U)         /* !< Security Fault */
#define SYSCTL_NMIRIS_SECURITY_FALSE             ((uint32_t)0x00000000U)
#define SYSCTL_NMIRIS_SECURITY_TRUE              ((uint32_t)0x00000004U)
/* SYSCTL_NMIRIS[SYSMEMACC] Bits */
#define SYSCTL_NMIRIS_SYSMEMACC_OFS              (6)                             /* !< SYSMEMACC Offset */
#define SYSCTL_NMIRIS_SYSMEMACC_MASK             ((uint32_t)0x00000040U)         /* !< SYSMEM Access error */
#define SYSCTL_NMIRIS_SYSMEMACC_FALSE            ((uint32_t)0x00000000U)
#define SYSCTL_NMIRIS_SYSMEMACC_TRUE             ((uint32_t)0x00000040U)
/* SYSCTL_NMIRIS[TMUROMPAR] Bits */
#define SYSCTL_NMIRIS_TMUROMPAR_OFS              (5)                             /* !< TMUROMPAR Offset */
#define SYSCTL_NMIRIS_TMUROMPAR_MASK             ((uint32_t)0x00000020U)         /* !< TMU ROM Parity error */
#define SYSCTL_NMIRIS_TMUROMPAR_FALSE            ((uint32_t)0x00000000U)
#define SYSCTL_NMIRIS_TMUROMPAR_TRUE             ((uint32_t)0x00000020U)
/* SYSCTL_NMIRIS[FLASHDED] Bits */
#define SYSCTL_NMIRIS_FLASHDED_OFS               (3)                             /* !< FLASHDED Offset */
#define SYSCTL_NMIRIS_FLASHDED_MASK              ((uint32_t)0x00000008U)         /* !< Flash Double Error Detect */
#define SYSCTL_NMIRIS_FLASHDED_FALSE             ((uint32_t)0x00000000U)
#define SYSCTL_NMIRIS_FLASHDED_TRUE              ((uint32_t)0x00000008U)
/* SYSCTL_NMIRIS[WWDT0] Bits */
#define SYSCTL_NMIRIS_WWDT0_OFS                  (1)                             /* !< WWDT0 Offset */
#define SYSCTL_NMIRIS_WWDT0_MASK                 ((uint32_t)0x00000002U)         /* !< Watch Dog 0 Fault */
#define SYSCTL_NMIRIS_WWDT0_FALSE                ((uint32_t)0x00000000U)
#define SYSCTL_NMIRIS_WWDT0_TRUE                 ((uint32_t)0x00000002U)
/* SYSCTL_NMIRIS[SRAMPAR] Bits */
#define SYSCTL_NMIRIS_SRAMPAR_OFS                (4)                             /* !< SRAMPAR Offset */
#define SYSCTL_NMIRIS_SRAMPAR_MASK               ((uint32_t)0x00000010U)         /* !< SRAM Parity Error Detect */
#define SYSCTL_NMIRIS_SRAMPAR_FALSE              ((uint32_t)0x00000000U)
#define SYSCTL_NMIRIS_SRAMPAR_TRUE               ((uint32_t)0x00000010U)

/* SYSCTL_NMIISET Bits */
/* SYSCTL_NMIISET[SECURITY] Bits */
#define SYSCTL_NMIISET_SECURITY_OFS              (2)                             /* !< SECURITY Offset */
#define SYSCTL_NMIISET_SECURITY_MASK             ((uint32_t)0x00000004U)         /* !< Security Fault */
#define SYSCTL_NMIISET_SECURITY_NO_EFFECT        ((uint32_t)0x00000000U)
#define SYSCTL_NMIISET_SECURITY_SET              ((uint32_t)0x00000004U)
/* SYSCTL_NMIISET[SYSMEMACC] Bits */
#define SYSCTL_NMIISET_SYSMEMACC_OFS             (6)                             /* !< SYSMEMACC Offset */
#define SYSCTL_NMIISET_SYSMEMACC_MASK            ((uint32_t)0x00000040U)         /* !< SYSMEM Access error */
#define SYSCTL_NMIISET_SYSMEMACC_NO_EFFECT       ((uint32_t)0x00000000U)
#define SYSCTL_NMIISET_SYSMEMACC_SET             ((uint32_t)0x00000040U)
/* SYSCTL_NMIISET[TMUROMPAR] Bits */
#define SYSCTL_NMIISET_TMUROMPAR_OFS             (5)                             /* !< TMUROMPAR Offset */
#define SYSCTL_NMIISET_TMUROMPAR_MASK            ((uint32_t)0x00000020U)         /* !< TMU ROM Parity error */
#define SYSCTL_NMIISET_TMUROMPAR_NO_EFFECT       ((uint32_t)0x00000000U)
#define SYSCTL_NMIISET_TMUROMPAR_SET             ((uint32_t)0x00000020U)
/* SYSCTL_NMIISET[FLASHDED] Bits */
#define SYSCTL_NMIISET_FLASHDED_OFS              (3)                             /* !< FLASHDED Offset */
#define SYSCTL_NMIISET_FLASHDED_MASK             ((uint32_t)0x00000008U)         /* !< Flash Double Error Detect */
#define SYSCTL_NMIISET_FLASHDED_NO_EFFECT        ((uint32_t)0x00000000U)
#define SYSCTL_NMIISET_FLASHDED_SET              ((uint32_t)0x00000008U)
/* SYSCTL_NMIISET[WWDT0] Bits */
#define SYSCTL_NMIISET_WWDT0_OFS                 (1)                             /* !< WWDT0 Offset */
#define SYSCTL_NMIISET_WWDT0_MASK                ((uint32_t)0x00000002U)         /* !< Watch Dog 0 Fault */
#define SYSCTL_NMIISET_WWDT0_NO_EFFECT           ((uint32_t)0x00000000U)
#define SYSCTL_NMIISET_WWDT0_SET                 ((uint32_t)0x00000002U)
/* SYSCTL_NMIISET[SRAMPAR] Bits */
#define SYSCTL_NMIISET_SRAMPAR_OFS               (4)                             /* !< SRAMPAR Offset */
#define SYSCTL_NMIISET_SRAMPAR_MASK              ((uint32_t)0x00000010U)         /* !< SRAM Parity Error Detect */
#define SYSCTL_NMIISET_SRAMPAR_NO_EFFECT         ((uint32_t)0x00000000U)
#define SYSCTL_NMIISET_SRAMPAR_SET               ((uint32_t)0x00000010U)

/* SYSCTL_NMIICLR Bits */
/* SYSCTL_NMIICLR[SECURITY] Bits */
#define SYSCTL_NMIICLR_SECURITY_OFS              (2)                             /* !< SECURITY Offset */
#define SYSCTL_NMIICLR_SECURITY_MASK             ((uint32_t)0x00000004U)         /* !< Security Fault */
#define SYSCTL_NMIICLR_SECURITY_NO_EFFECT        ((uint32_t)0x00000000U)
#define SYSCTL_NMIICLR_SECURITY_CLR              ((uint32_t)0x00000004U)
/* SYSCTL_NMIICLR[SYSMEMACC] Bits */
#define SYSCTL_NMIICLR_SYSMEMACC_OFS             (6)                             /* !< SYSMEMACC Offset */
#define SYSCTL_NMIICLR_SYSMEMACC_MASK            ((uint32_t)0x00000040U)         /* !< SYSMEM Access error */
#define SYSCTL_NMIICLR_SYSMEMACC_NO_EFFECT       ((uint32_t)0x00000000U)
#define SYSCTL_NMIICLR_SYSMEMACC_CLR             ((uint32_t)0x00000040U)
/* SYSCTL_NMIICLR[TMUROMPAR] Bits */
#define SYSCTL_NMIICLR_TMUROMPAR_OFS             (5)                             /* !< TMUROMPAR Offset */
#define SYSCTL_NMIICLR_TMUROMPAR_MASK            ((uint32_t)0x00000020U)         /* !< TMU ROM Parity error */
#define SYSCTL_NMIICLR_TMUROMPAR_NO_EFFECT       ((uint32_t)0x00000000U)
#define SYSCTL_NMIICLR_TMUROMPAR_CLR             ((uint32_t)0x00000020U)
/* SYSCTL_NMIICLR[FLASHDED] Bits */
#define SYSCTL_NMIICLR_FLASHDED_OFS              (3)                             /* !< FLASHDED Offset */
#define SYSCTL_NMIICLR_FLASHDED_MASK             ((uint32_t)0x00000008U)         /* !< Flash Double Error Detect */
#define SYSCTL_NMIICLR_FLASHDED_NO_EFFECT        ((uint32_t)0x00000000U)
#define SYSCTL_NMIICLR_FLASHDED_CLR              ((uint32_t)0x00000008U)
/* SYSCTL_NMIICLR[WWDT0] Bits */
#define SYSCTL_NMIICLR_WWDT0_OFS                 (1)                             /* !< WWDT0 Offset */
#define SYSCTL_NMIICLR_WWDT0_MASK                ((uint32_t)0x00000002U)         /* !< Watch Dog 0 Fault */
#define SYSCTL_NMIICLR_WWDT0_NO_EFFECT           ((uint32_t)0x00000000U)
#define SYSCTL_NMIICLR_WWDT0_CLR                 ((uint32_t)0x00000002U)
/* SYSCTL_NMIICLR[SRAMPAR] Bits */
#define SYSCTL_NMIICLR_SRAMPAR_OFS               (4)                             /* !< SRAMPAR Offset */
#define SYSCTL_NMIICLR_SRAMPAR_MASK              ((uint32_t)0x00000010U)         /* !< SRAM Parity Error Detect */
#define SYSCTL_NMIICLR_SRAMPAR_NO_EFFECT         ((uint32_t)0x00000000U)
#define SYSCTL_NMIICLR_SRAMPAR_CLR               ((uint32_t)0x00000010U)

/* SYSCTL_SYSOSCCFG Bits */
/* SYSCTL_SYSOSCCFG[BLOCKASYNCALL] Bits */
#define SYSCTL_SYSOSCCFG_BLOCKASYNCALL_OFS       (16)                            /* !< BLOCKASYNCALL Offset */
#define SYSCTL_SYSOSCCFG_BLOCKASYNCALL_MASK      ((uint32_t)0x00010000U)         /* !< BLOCKASYNCALL may be used to mask
                                                                                    block all asynchronous fast clock
                                                                                    requests, preventing hardware from
                                                                                    dynamically changing the active clock
                                                                                    configuration when operating in a
                                                                                    given mode. */
#define SYSCTL_SYSOSCCFG_BLOCKASYNCALL_DISABLE   ((uint32_t)0x00000000U)         /* !< Asynchronous fast clock requests
                                                                                    are controlled by the requesting
                                                                                    peripheral */
#define SYSCTL_SYSOSCCFG_BLOCKASYNCALL_ENABLE    ((uint32_t)0x00010000U)         /* !< All asynchronous fast clock
                                                                                    requests are blocked */
/* SYSCTL_SYSOSCCFG[DISABLE] Bits */
#define SYSCTL_SYSOSCCFG_DISABLE_OFS             (10)                            /* !< DISABLE Offset */
#define SYSCTL_SYSOSCCFG_DISABLE_MASK            ((uint32_t)0x00000400U)         /* !< DISABLE sets the SYSOSC
                                                                                    enable/disable policy.  SYSOSC may be
                                                                                    powered off in RUN, SLEEP, and STOP
                                                                                    modes to reduce power consumption.
                                                                                    When SYSOSC is disabled, MCLK and
                                                                                    ULPCLK are sourced from LFCLK. */
#define SYSCTL_SYSOSCCFG_DISABLE_DISABLE         ((uint32_t)0x00000000U)         /* !< Do not disable SYSOSC */
#define SYSCTL_SYSOSCCFG_DISABLE_ENABLE          ((uint32_t)0x00000400U)         /* !< Disable SYSOSC immediately and
                                                                                    source MCLK and ULPCLK from LFCLK */
/* SYSCTL_SYSOSCCFG[FASTCPUEVENT] Bits */
#define SYSCTL_SYSOSCCFG_FASTCPUEVENT_OFS        (17)                            /* !< FASTCPUEVENT Offset */
#define SYSCTL_SYSOSCCFG_FASTCPUEVENT_MASK       ((uint32_t)0x00020000U)         /* !< if disabled  CPU will not wakeup
                                                                                    and continue in STANDBY */
#define SYSCTL_SYSOSCCFG_FASTCPUEVENT_DISABLE    ((uint32_t)0x00000000U)         /* !< An interrupt to the CPU will not
                                                                                    assert a fast clock request */
#define SYSCTL_SYSOSCCFG_FASTCPUEVENT_ENABLE     ((uint32_t)0x00020000U)         /* !< An interrupt to the CPU will assert
                                                                                    a fast clock request */

/* SYSCTL_MCLKCFG Bits */
/* SYSCTL_MCLKCFG[USEHSCLK] Bits */
#define SYSCTL_MCLKCFG_USEHSCLK_OFS              (16)                            /* !< USEHSCLK Offset */
#define SYSCTL_MCLKCFG_USEHSCLK_MASK             ((uint32_t)0x00010000U)         /* !< USEHSCLK, together with USELFCLK,
                                                                                    sets the MCLK source policy.  Set
                                                                                    USEHSCLK to use HSCLK (HFCLK or
                                                                                    SYSPLL) as the MCLK source in RUN and
                                                                                    SLEEP modes. */
#define SYSCTL_MCLKCFG_USEHSCLK_DISABLE          ((uint32_t)0x00000000U)         /* !< MCLK will not use the high speed
                                                                                    clock (HSCLK) */
#define SYSCTL_MCLKCFG_USEHSCLK_ENABLE           ((uint32_t)0x00010000U)         /* !< MCLK will use the high speed clock
                                                                                    (HSCLK) in RUN and SLEEP mode */
/* SYSCTL_MCLKCFG[USELFCLK] Bits */
#define SYSCTL_MCLKCFG_USELFCLK_OFS              (20)                            /* !< USELFCLK Offset */
#define SYSCTL_MCLKCFG_USELFCLK_MASK             ((uint32_t)0x00100000U)         /* !< LFCLK is not an MCLK sourcei in
                                                                                    PD1, tied 0. */
#define SYSCTL_MCLKCFG_USELFCLK_DISABLE          ((uint32_t)0x00000000U)         /* !< MCLK will not use the low frequency
                                                                                    clock (LFCLK) */
#define SYSCTL_MCLKCFG_USELFCLK_ENABLE           ((uint32_t)0x00100000U)         /* !< MCLK will use the low frequency
                                                                                    clock (LFCLK) */
/* SYSCTL_MCLKCFG[MCLKDIVCFG] Bits */
#define SYSCTL_MCLKCFG_MCLKDIVCFG_OFS            (24)                            /* !< MCLKDIVCFG Offset */
#define SYSCTL_MCLKCFG_MCLKDIVCFG_MASK           ((uint32_t)0x07000000U)         /* !< MCLK Divider Configuration bits
                                                                                    [1:0] are defined as MCLK4 is Bypass,
                                                                                    MCLK2 is Bypass */
#define SYSCTL_MCLKCFG_MCLKDIVCFG_RATIO_1_1_1    ((uint32_t)0x00000000U)         /* !< MCLK: No Divide, MCLK2: No Divide,
                                                                                    MCLK4: No Divide */
#define SYSCTL_MCLKCFG_MCLKDIVCFG_RATIO_1_1_2    ((uint32_t)0x01000000U)         /* !< MCLK: No Divide, MCLK2: No Divide,
                                                                                    MCLK4: Divide MCLK by 2 */
#define SYSCTL_MCLKCFG_MCLKDIVCFG_RATIO_1_1_4    ((uint32_t)0x03000000U)         /* !< MCLK: No Divide, MCLK2: No Divide,
                                                                                    MCLK4: Divide MCLK by 4 */
#define SYSCTL_MCLKCFG_MCLKDIVCFG_RATIO_1_2_2    ((uint32_t)0x05000000U)         /* !< MCLK: No Divide, MCLK2: Divide MCLK
                                                                                    by 2, MCLK4: Divide MCLK by 2 */
#define SYSCTL_MCLKCFG_MCLKDIVCFG_RATIO_1_2_4    ((uint32_t)0x07000000U)         /* !< MCLK: No Divide, MCLK2: Divide MCLK
                                                                                    by 2, MCLK4: MCLK by 4 */
/* SYSCTL_MCLKCFG[STOPCLKSTBY] Bits */
#define SYSCTL_MCLKCFG_STOPCLKSTBY_OFS           (21)                            /* !< STOPCLKSTBY Offset */
#define SYSCTL_MCLKCFG_STOPCLKSTBY_MASK          ((uint32_t)0x00200000U)         /* !< STOPCLKSTBY sets the STANDBY mode
                                                                                    policy (STANDBY0 or STANDBY1).  When
                                                                                    set, ULPCLK and LFCLK are disabled to
                                                                                    all peripherals in STANDBY mode, with
                                                                                    the exception of TIMG0 and TIMG1
                                                                                    which continue to run.  Wake-up is
                                                                                    only possible via an asynchronous
                                                                                    fast clock request. */
#define SYSCTL_MCLKCFG_STOPCLKSTBY_DISABLE       ((uint32_t)0x00000000U)         /* !< ULPCLK/LFCLK runs to all PD0
                                                                                    peripherals in STANDBY mode */
#define SYSCTL_MCLKCFG_STOPCLKSTBY_ENABLE        ((uint32_t)0x00200000U)         /* !< ULPCLK/LFCLK is disabled to all
                                                                                    peripherals in STANDBY mode except
                                                                                    TIMG0 and TIMG1 */
/* SYSCTL_MCLKCFG[MCLKDEADCHK] Bits */
#define SYSCTL_MCLKCFG_MCLKDEADCHK_OFS           (22)                            /* !< MCLKDEADCHK Offset */
#define SYSCTL_MCLKCFG_MCLKDEADCHK_MASK          ((uint32_t)0x00400000U)         /* !< MCLKDEADCHK enables or disables the
                                                                                    continuous MCLK dead check monitor.
                                                                                    LFCLK must be running before
                                                                                    MCLKDEADCHK is enabled. */
#define SYSCTL_MCLKCFG_MCLKDEADCHK_DISABLE       ((uint32_t)0x00000000U)         /* !< The MCLK dead check monitor is
                                                                                    disabled */
#define SYSCTL_MCLKCFG_MCLKDEADCHK_ENABLE        ((uint32_t)0x00400000U)         /* !< The MCLK dead check monitor is
                                                                                    enabled */

/* SYSCTL_HSCLKEN Bits */
/* SYSCTL_HSCLKEN[USEEXTHFCLK] Bits */
#define SYSCTL_HSCLKEN_USEEXTHFCLK_OFS           (16)                            /* !< USEEXTHFCLK Offset */
#define SYSCTL_HSCLKEN_USEEXTHFCLK_MASK          ((uint32_t)0x00010000U)         /* !< USEEXTHFCLK selects the HFCLK_IN
                                                                                    digital clock input to be the source
                                                                                    for HFCLK. */
#define SYSCTL_HSCLKEN_USEEXTHFCLK_DISABLE       ((uint32_t)0x00000000U)         /* !< Use XTAL as the HFCLK source */
#define SYSCTL_HSCLKEN_USEEXTHFCLK_ENABLE        ((uint32_t)0x00010000U)         /* !< Use the HFCLK_IN digital clock
                                                                                    input as the HFCLK source */
/* SYSCTL_HSCLKEN[SYSPLLEN] Bits */
#define SYSCTL_HSCLKEN_SYSPLLEN_OFS              (8)                             /* !< SYSPLLEN Offset */
#define SYSCTL_HSCLKEN_SYSPLLEN_MASK             ((uint32_t)0x00000100U)         /* !< SYSPLLEN enables or disables the
                                                                                    system phase-lock loop (SYSPLL). */
#define SYSCTL_HSCLKEN_SYSPLLEN_DISABLE          ((uint32_t)0x00000000U)         /* !< Disable the SYSPLL */
#define SYSCTL_HSCLKEN_SYSPLLEN_ENABLE           ((uint32_t)0x00000100U)         /* !< Enable the SYSPLL */

/* SYSCTL_HSCLKCFG Bits */
/* SYSCTL_HSCLKCFG[HSCLKSEL] Bits */
#define SYSCTL_HSCLKCFG_HSCLKSEL_OFS             (0)                             /* !< HSCLKSEL Offset */
#define SYSCTL_HSCLKCFG_HSCLKSEL_MASK            ((uint32_t)0x00000001U)         /* !< HSCLKSEL selects the HSCLK source
                                                                                    (SYSPLL or HFCLK). */
#define SYSCTL_HSCLKCFG_HSCLKSEL_SYSPLL          ((uint32_t)0x00000000U)         /* !< HSCLK is sourced from the SYSPLL */
#define SYSCTL_HSCLKCFG_HSCLKSEL_HFCLKCLK        ((uint32_t)0x00000001U)         /* !< HSCLK is sourced from the HFCLK */

/* SYSCTL_HFCLKCLKCFG Bits */
/* SYSCTL_HFCLKCLKCFG[XTALTIME] Bits */
#define SYSCTL_HFCLKCLKCFG_XTALTIME_OFS          (0)                             /* !< XTALTIME Offset */
#define SYSCTL_HFCLKCLKCFG_XTALTIME_MASK         ((uint32_t)0x000000FFU)         /* !< XTALTIME specifies the XTAL startup
                                                                                    time in 64us resolution.  If the
                                                                                    HFCLK startup monitor is enabled
                                                                                    (HFCLKFLTCHK), XTAL will be checked
                                                                                    after this time expires. */
#define SYSCTL_HFCLKCLKCFG_XTALTIME_MINSTARTTIME ((uint32_t)0x00000000U)         /* !< Minimum startup time (approximatly
                                                                                    zero) */
#define SYSCTL_HFCLKCLKCFG_XTALTIME_MAXSTARTTIME ((uint32_t)0x000000FFU)         /* !< Maximum startup time (approximatly
                                                                                    16.32ms) */
/* SYSCTL_HFCLKCLKCFG[HFCLKFLTCHK] Bits */
#define SYSCTL_HFCLKCLKCFG_HFCLKFLTCHK_OFS       (28)                            /* !< HFCLKFLTCHK Offset */
#define SYSCTL_HFCLKCLKCFG_HFCLKFLTCHK_MASK      ((uint32_t)0x10000000U)         /* !< HFCLKFLTCHK enables or disables the
                                                                                    HFCLK startup monitor. */
#define SYSCTL_HFCLKCLKCFG_HFCLKFLTCHK_DISABLE   ((uint32_t)0x00000000U)         /* !< HFCLK startup is not checked */
#define SYSCTL_HFCLKCLKCFG_HFCLKFLTCHK_ENABLE    ((uint32_t)0x10000000U)         /* !< HFCLK startup is checked */

/* SYSCTL_SYSPLLCFG0 Bits */
/* SYSCTL_SYSPLLCFG0[ENABLECLK0] Bits */
#define SYSCTL_SYSPLLCFG0_ENABLECLK0_OFS         (4)                             /* !< ENABLECLK0 Offset */
#define SYSCTL_SYSPLLCFG0_ENABLECLK0_MASK        ((uint32_t)0x00000010U)         /* !< ENABLECLK0 enables or disables the
                                                                                    SYSPLLCLK0 output. */
#define SYSCTL_SYSPLLCFG0_ENABLECLK0_DISABLE     ((uint32_t)0x00000000U)         /* !< SYSPLLCLK0 is disabled */
#define SYSCTL_SYSPLLCFG0_ENABLECLK0_ENABLE      ((uint32_t)0x00000010U)         /* !< SYSPLLCLK0 is enabled */
/* SYSCTL_SYSPLLCFG0[ENABLECLK1] Bits */
#define SYSCTL_SYSPLLCFG0_ENABLECLK1_OFS         (5)                             /* !< ENABLECLK1 Offset */
#define SYSCTL_SYSPLLCFG0_ENABLECLK1_MASK        ((uint32_t)0x00000020U)         /* !< ENABLECLK1 enables or disables the
                                                                                    SYSPLLCLK1 output. */
#define SYSCTL_SYSPLLCFG0_ENABLECLK1_DISABLE     ((uint32_t)0x00000000U)         /* !< SYSPLLCLK1 is disabled */
#define SYSCTL_SYSPLLCFG0_ENABLECLK1_ENABLE      ((uint32_t)0x00000020U)         /* !< SYSPLLCLK1 is enabled */
/* SYSCTL_SYSPLLCFG0[RDIVCLK1] Bits */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_OFS           (12)                            /* !< RDIVCLK1 Offset */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_MASK          ((uint32_t)0x0000F000U)         /* !< RDIVCLK1 sets the final divider for
                                                                                    the SYSPLLCLK1 output. */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV2      ((uint32_t)0x00000000U)         /* !< SYSPLLCLK1 is divided by 2 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV4      ((uint32_t)0x00001000U)         /* !< SYSPLLCLK1 is divided by 4 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV6      ((uint32_t)0x00002000U)         /* !< SYSPLLCLK1 is divided by 6 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV8      ((uint32_t)0x00003000U)         /* !< SYSPLLCLK1 is divided by 8 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV10     ((uint32_t)0x00004000U)         /* !< SYSPLLCLK1 is divided by 10 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV12     ((uint32_t)0x00005000U)         /* !< SYSPLLCLK1 is divided by 12 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV14     ((uint32_t)0x00006000U)         /* !< SYSPLLCLK1 is divided by 14 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV16     ((uint32_t)0x00007000U)         /* !< SYSPLLCLK1 is divided by 16 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV18     ((uint32_t)0x00008000U)         /* !< SYSPLLCLK1 is divided by 18 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV20     ((uint32_t)0x00009000U)         /* !< SYSPLLCLK1 is divided by 20 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV22     ((uint32_t)0x0000A000U)         /* !< SYSPLLCLK1 is divided by 22 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV24     ((uint32_t)0x0000B000U)         /* !< SYSPLLCLK1 is divided by 24 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV26     ((uint32_t)0x0000C000U)         /* !< SYSPLLCLK1 is divided by 26 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV28     ((uint32_t)0x0000D000U)         /* !< SYSPLLCLK1 is divided by 28 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV30     ((uint32_t)0x0000E000U)         /* !< SYSPLLCLK1 is divided by 30 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK1_CLK1DIV32     ((uint32_t)0x0000F000U)         /* !< SYSPLLCLK1 is divided by 32 */
/* SYSCTL_SYSPLLCFG0[RDIVCLK0] Bits */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_OFS           (8)                             /* !< RDIVCLK0 Offset */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_MASK          ((uint32_t)0x00000F00U)         /* !< RDIVCLK0 sets the final divider for
                                                                                    the SYSPLLCLK0 output. */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV2      ((uint32_t)0x00000000U)         /* !< SYSPLLCLK0 is divided by 2 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV4      ((uint32_t)0x00000100U)         /* !< SYSPLLCLK0 is divided by 4 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV6      ((uint32_t)0x00000200U)         /* !< SYSPLLCLK0 is divided by 6 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV8      ((uint32_t)0x00000300U)         /* !< SYSPLLCLK0 is divided by 8 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV10     ((uint32_t)0x00000400U)         /* !< SYSPLLCLK0 is divided by 10 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV12     ((uint32_t)0x00000500U)         /* !< SYSPLLCLK0 is divided by 12 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV14     ((uint32_t)0x00000600U)         /* !< SYSPLLCLK0 is divided by 14 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV16     ((uint32_t)0x00000700U)         /* !< SYSPLLCLK0 is divided by 16 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV18     ((uint32_t)0x00000800U)         /* !< SYSPLLCLK0 is divided by 18 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV20     ((uint32_t)0x00000900U)         /* !< SYSPLLCLK0 is divided by 20 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV22     ((uint32_t)0x00000A00U)         /* !< SYSPLLCLK0 is divided by 22 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV24     ((uint32_t)0x00000B00U)         /* !< SYSPLLCLK0 is divided by 24 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV26     ((uint32_t)0x00000C00U)         /* !< SYSPLLCLK0 is divided by 26 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV28     ((uint32_t)0x00000D00U)         /* !< SYSPLLCLK0 is divided by 28 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV30     ((uint32_t)0x00000E00U)         /* !< SYSPLLCLK0 is divided by 30 */
#define SYSCTL_SYSPLLCFG0_RDIVCLK0_CLK0DIV32     ((uint32_t)0x00000F00U)         /* !< SYSPLLCLK0 is divided by 32 */
/* SYSCTL_SYSPLLCFG0[SYSPLLREF] Bits */
#define SYSCTL_SYSPLLCFG0_SYSPLLREF_OFS          (0)                             /* !< SYSPLLREF Offset */
#define SYSCTL_SYSPLLCFG0_SYSPLLREF_MASK         ((uint32_t)0x00000001U)         /* !< SYSPLLREF selects the system PLL
                                                                                    (SYSPLL) reference clock source. */
#define SYSCTL_SYSPLLCFG0_SYSPLLREF_SYSOSC       ((uint32_t)0x00000000U)         /* !< SYSPLL reference is SYSOSC */
#define SYSCTL_SYSPLLCFG0_SYSPLLREF_HFCLK        ((uint32_t)0x00000001U)         /* !< SYSPLL reference is HFCLK */

/* SYSCTL_SYSPLLCFG1 Bits */
/* SYSCTL_SYSPLLCFG1[PDIV] Bits */
#define SYSCTL_SYSPLLCFG1_PDIV_OFS               (0)                             /* !< PDIV Offset */
#define SYSCTL_SYSPLLCFG1_PDIV_MASK              ((uint32_t)0x00000003U)         /* !< PDIV selects the SYSPLL reference
                                                                                    clock prescale divider. */
#define SYSCTL_SYSPLLCFG1_PDIV_REFDIV1           ((uint32_t)0x00000000U)         /* !< SYSPLLREF is not divided */
#define SYSCTL_SYSPLLCFG1_PDIV_REFDIV2           ((uint32_t)0x00000001U)         /* !< SYSPLLREF is divided by 2 */
#define SYSCTL_SYSPLLCFG1_PDIV_REFDIV4           ((uint32_t)0x00000002U)         /* !< SYSPLLREF is divided by 4 */
#define SYSCTL_SYSPLLCFG1_PDIV_REFDIV8           ((uint32_t)0x00000003U)         /* !< SYSPLLREF is divided by 8 */
/* SYSCTL_SYSPLLCFG1[QDIV] Bits */
#define SYSCTL_SYSPLLCFG1_QDIV_OFS               (8)                             /* !< QDIV Offset */
#define SYSCTL_SYSPLLCFG1_QDIV_MASK              ((uint32_t)0x00007F00U)         /* !< QDIV selects the SYSPLL feedback
                                                                                    path divider. */
#define SYSCTL_SYSPLLCFG1_QDIV_INVALID           ((uint32_t)0x00000000U)         /* !< Divide-by-one is not a valid QDIV
                                                                                    option */
#define SYSCTL_SYSPLLCFG1_QDIV_QDIVMIN           ((uint32_t)0x00000100U)         /* !< Feedback path is divided by 2 */
#define SYSCTL_SYSPLLCFG1_QDIV_QDIVMAX           ((uint32_t)0x00007E00U)         /* !< Feedback path is divided by 127
                                                                                    (0x7E) */

/* SYSCTL_SYSPLLPARAM0 Bits */
/* SYSCTL_SYSPLLPARAM0[CPCURRENT] Bits */
#define SYSCTL_SYSPLLPARAM0_CPCURRENT_OFS        (16)                            /* !< CPCURRENT Offset */
#define SYSCTL_SYSPLLPARAM0_CPCURRENT_MASK       ((uint32_t)0x003F0000U)         /* !< Charge pump current */
/* SYSCTL_SYSPLLPARAM0[CAPBOVERRIDE] Bits */
#define SYSCTL_SYSPLLPARAM0_CAPBOVERRIDE_OFS     (31)                            /* !< CAPBOVERRIDE Offset */
#define SYSCTL_SYSPLLPARAM0_CAPBOVERRIDE_MASK    ((uint32_t)0x80000000U)         /* !< CAPBOVERRIDE controls the override
                                                                                    for Cap B */
#define SYSCTL_SYSPLLPARAM0_CAPBOVERRIDE_DISABLE ((uint32_t)0x00000000U)         /* !< Cap B override disabled */
#define SYSCTL_SYSPLLPARAM0_CAPBOVERRIDE_ENABLE  ((uint32_t)0x80000000U)         /* !< Cap B override enabled */
/* SYSCTL_SYSPLLPARAM0[STARTTIME] Bits */
#define SYSCTL_SYSPLLPARAM0_STARTTIME_OFS        (0)                             /* !< STARTTIME Offset */
#define SYSCTL_SYSPLLPARAM0_STARTTIME_MASK       ((uint32_t)0x0000007FU)         /* !< Startup time from enable to locked
                                                                                    clock, in 1us resolution */
/* SYSCTL_SYSPLLPARAM0[CAPBVAL] Bits */
#define SYSCTL_SYSPLLPARAM0_CAPBVAL_OFS          (24)                            /* !< CAPBVAL Offset */
#define SYSCTL_SYSPLLPARAM0_CAPBVAL_MASK         ((uint32_t)0x1F000000U)         /* !< Override value for Cap B */
/* SYSCTL_SYSPLLPARAM0[STARTTIMELP] Bits */
#define SYSCTL_SYSPLLPARAM0_STARTTIMELP_OFS      (8)                             /* !< STARTTIMELP Offset */
#define SYSCTL_SYSPLLPARAM0_STARTTIMELP_MASK     ((uint32_t)0x00007F00U)         /* !< Startup time from low power mode
                                                                                    exit to locked clock, in 1us
                                                                                    resolution */

/* SYSCTL_SYSPLLPARAM1 Bits */
/* SYSCTL_SYSPLLPARAM1[LPFCAPA] Bits */
#define SYSCTL_SYSPLLPARAM1_LPFCAPA_OFS          (0)                             /* !< LPFCAPA Offset */
#define SYSCTL_SYSPLLPARAM1_LPFCAPA_MASK         ((uint32_t)0x0000001FU)         /* !< Loop filter Cap A */
/* SYSCTL_SYSPLLPARAM1[LPFRESC] Bits */
#define SYSCTL_SYSPLLPARAM1_LPFRESC_OFS          (24)                            /* !< LPFRESC Offset */
#define SYSCTL_SYSPLLPARAM1_LPFRESC_MASK         ((uint32_t)0xFF000000U)         /* !< Loop filter Res C */
/* SYSCTL_SYSPLLPARAM1[LPFRESA] Bits */
#define SYSCTL_SYSPLLPARAM1_LPFRESA_OFS          (8)                             /* !< LPFRESA Offset */
#define SYSCTL_SYSPLLPARAM1_LPFRESA_MASK         ((uint32_t)0x0003FF00U)         /* !< Loop filter Res A */

/* SYSCTL_SYSPLLPARAM2 Bits */
/* SYSCTL_SYSPLLPARAM2[RNGFIXVCOIBIASCFG] Bits */
#define SYSCTL_SYSPLLPARAM2_RNGFIXVCOIBIASCFG_OFS (3)                             /* !< RNGFIXVCOIBIASCFG Offset */
#define SYSCTL_SYSPLLPARAM2_RNGFIXVCOIBIASCFG_MASK ((uint32_t)0x00000008U)         /* !< 0 value for Temperature
                                                                                    Compensation R addition */
/* SYSCTL_SYSPLLPARAM2[LPFCAPC] Bits */
#define SYSCTL_SYSPLLPARAM2_LPFCAPC_OFS          (0)                             /* !< LPFCAPC Offset */
#define SYSCTL_SYSPLLPARAM2_LPFCAPC_MASK         ((uint32_t)0x00000003U)         /* !< Loop filter Cap C */

/* SYSCTL_SYSPLLLDOCTL Bits */
/* SYSCTL_SYSPLLLDOCTL[LDOCTLLOWV] Bits */
#define SYSCTL_SYSPLLLDOCTL_LDOCTLLOWV_OFS       (0)                             /* !< LDOCTLLOWV Offset */
#define SYSCTL_SYSPLLLDOCTL_LDOCTLLOWV_MASK      ((uint32_t)0x0000FFFFU)         /* !< LDO Configurability */

/* SYSCTL_SYSPLLLDOPROG Bits */
/* SYSCTL_SYSPLLLDOPROG[LDOVOUTPROGLOWV] Bits */
#define SYSCTL_SYSPLLLDOPROG_LDOVOUTPROGLOWV_OFS (0)                             /* !< LDOVOUTPROGLOWV Offset */
#define SYSCTL_SYSPLLLDOPROG_LDOVOUTPROGLOWV_MASK ((uint32_t)0x00000007U)         /* !< HPLL LDO Vout Prog */

/* SYSCTL_GENCLKEN Bits */
/* SYSCTL_GENCLKEN[EXTDIVMCLK] Bits */
#define SYSCTL_GENCLKEN_EXTDIVMCLK_OFS           (8)                             /* !< EXTDIVMCLK Offset */
#define SYSCTL_GENCLKEN_EXTDIVMCLK_MASK          ((uint32_t)0x00000700U)         /* !< EXTDIVMCLK selects the divider
                                                                                    value for the divider for the PLL
                                                                                    Source MCLK. */
#define SYSCTL_GENCLKEN_EXTDIVMCLK_DIV2          ((uint32_t)0x00000000U)         /* !< CLK_OUT source is divided by 2 */
#define SYSCTL_GENCLKEN_EXTDIVMCLK_DIV4          ((uint32_t)0x00000100U)         /* !< CLK_OUT source is divided by 4 */
#define SYSCTL_GENCLKEN_EXTDIVMCLK_DIV6          ((uint32_t)0x00000200U)         /* !< CLK_OUT source is divided by 6 */
#define SYSCTL_GENCLKEN_EXTDIVMCLK_DIV8          ((uint32_t)0x00000300U)         /* !< CLK_OUT source is divided by 8 */
#define SYSCTL_GENCLKEN_EXTDIVMCLK_DIV10         ((uint32_t)0x00000400U)         /* !< CLK_OUT source is divided by 10 */
#define SYSCTL_GENCLKEN_EXTDIVMCLK_DIV12         ((uint32_t)0x00000500U)         /* !< CLK_OUT source is divided by 12 */
#define SYSCTL_GENCLKEN_EXTDIVMCLK_DIV14         ((uint32_t)0x00000600U)         /* !< CLK_OUT source is divided by 14 */
#define SYSCTL_GENCLKEN_EXTDIVMCLK_DIV16         ((uint32_t)0x00000700U)         /* !< CLK_OUT source is divided by 16 */
/* SYSCTL_GENCLKEN[EXCLKEN] Bits */
#define SYSCTL_GENCLKEN_EXCLKEN_OFS              (0)                             /* !< EXCLKEN Offset */
#define SYSCTL_GENCLKEN_EXCLKEN_MASK             ((uint32_t)0x00000001U)         /* !< EXCLKEN enables the CLK_OUT
                                                                                    external clock output block. */
#define SYSCTL_GENCLKEN_EXCLKEN_DISABLE          ((uint32_t)0x00000000U)         /* !< CLK_OUT block is disabled */
#define SYSCTL_GENCLKEN_EXCLKEN_ENABLE           ((uint32_t)0x00000001U)         /* !< CLK_OUT block is enabled */
/* SYSCTL_GENCLKEN[MCLKEXTDIVEN] Bits */
#define SYSCTL_GENCLKEN_MCLKEXTDIVEN_OFS         (11)                            /* !< MCLKEXTDIVEN Offset */
#define SYSCTL_GENCLKEN_MCLKEXTDIVEN_MASK        ((uint32_t)0x00000800U)         /* !< MCLKEXTDIVEN enables or disables
                                                                                    the divider function of the PLL
                                                                                    Source to MCLK. */
#define SYSCTL_GENCLKEN_MCLKEXTDIVEN_PASSTHRU    ((uint32_t)0x00000000U)         /* !< CLock divider is disabled
                                                                                    (passthrough, EXTDIVMCLK is not
                                                                                    applied) */
#define SYSCTL_GENCLKEN_MCLKEXTDIVEN_ENABLE      ((uint32_t)0x00000800U)         /* !< Clock divider is enabled
                                                                                    (EXTDIVMCLK is applied) */
/* SYSCTL_GENCLKEN[EXTDIVCAN] Bits */
#define SYSCTL_GENCLKEN_EXTDIVCAN_OFS            (12)                            /* !< EXTDIVCAN Offset */
#define SYSCTL_GENCLKEN_EXTDIVCAN_MASK           ((uint32_t)0x00007000U)         /* !< EXTDIVCAN selects the divider value
                                                                                    for the divider for the PLL Source to
                                                                                    CAN. */
#define SYSCTL_GENCLKEN_EXTDIVCAN_DIV2           ((uint32_t)0x00000000U)         /* !< CLK_OUT source is divided by 2 */
#define SYSCTL_GENCLKEN_EXTDIVCAN_DIV4           ((uint32_t)0x00001000U)         /* !< CLK_OUT source is divided by 4 */
#define SYSCTL_GENCLKEN_EXTDIVCAN_DIV6           ((uint32_t)0x00002000U)         /* !< CLK_OUT source is divided by 6 */
#define SYSCTL_GENCLKEN_EXTDIVCAN_DIV8           ((uint32_t)0x00003000U)         /* !< CLK_OUT source is divided by 8 */
#define SYSCTL_GENCLKEN_EXTDIVCAN_DIV10          ((uint32_t)0x00004000U)         /* !< CLK_OUT source is divided by 10 */
#define SYSCTL_GENCLKEN_EXTDIVCAN_DIV12          ((uint32_t)0x00005000U)         /* !< CLK_OUT source is divided by 12 */
#define SYSCTL_GENCLKEN_EXTDIVCAN_DIV14          ((uint32_t)0x00006000U)         /* !< CLK_OUT source is divided by 14 */
#define SYSCTL_GENCLKEN_EXTDIVCAN_DIV16          ((uint32_t)0x00007000U)         /* !< CLK_OUT source is divided by 16 */
/* SYSCTL_GENCLKEN[CANEXTDIVEN] Bits */
#define SYSCTL_GENCLKEN_CANEXTDIVEN_OFS          (15)                            /* !< CANEXTDIVEN Offset */
#define SYSCTL_GENCLKEN_CANEXTDIVEN_MASK         ((uint32_t)0x00008000U)         /* !< CANEXTDIVEN enables or disables the
                                                                                    divider function of the PLL Source to
                                                                                    CAN. */
#define SYSCTL_GENCLKEN_CANEXTDIVEN_PASSTHRU     ((uint32_t)0x00000000U)         /* !< CLock divider is disabled
                                                                                    (passthrough, EXTDIVCAN is not
                                                                                    applied) */
#define SYSCTL_GENCLKEN_CANEXTDIVEN_ENABLE       ((uint32_t)0x00008000U)         /* !< Clock divider is enabled (EXTDIVCAN
                                                                                    is applied) */

/* SYSCTL_GENCLKCFG Bits */
/* SYSCTL_GENCLKCFG[CANCLKSRC] Bits */
#define SYSCTL_GENCLKCFG_CANCLKSRC_OFS           (8)                             /* !< CANCLKSRC Offset */
#define SYSCTL_GENCLKCFG_CANCLKSRC_MASK          ((uint32_t)0x00000100U)         /* !< CANCLKSRC selects the CANCLK
                                                                                    source. */
#define SYSCTL_GENCLKCFG_CANCLKSRC_HFCLK         ((uint32_t)0x00000000U)         /* !< CANCLK source is HFCLK */
#define SYSCTL_GENCLKCFG_CANCLKSRC_SYSPLLOUT     ((uint32_t)0x00000100U)         /* !< CANCLK source is SYSPLLCLK */
/* SYSCTL_GENCLKCFG[FCCTRIGCNT] Bits */
#define SYSCTL_GENCLKCFG_FCCTRIGCNT_OFS          (24)                            /* !< FCCTRIGCNT Offset */
#define SYSCTL_GENCLKCFG_FCCTRIGCNT_MASK         ((uint32_t)0x1F000000U)         /* !< FCCTRIGCNT specifies the number of
                                                                                    trigger clock periods in the trigger
                                                                                    window. FCCTRIGCNT=0h (one trigger
                                                                                    clock period) up to 1Fh (32 trigger
                                                                                    clock periods) may be specified. */
/* SYSCTL_GENCLKCFG[FCCSELCLK] Bits */
#define SYSCTL_GENCLKCFG_FCCSELCLK_OFS           (16)                            /* !< FCCSELCLK Offset */
#define SYSCTL_GENCLKCFG_FCCSELCLK_MASK          ((uint32_t)0x000F0000U)         /* !< FCCSELCLK selectes the frequency
                                                                                    clock counter (FCC) clock source. */
#define SYSCTL_GENCLKCFG_FCCSELCLK_MCLKBY4       ((uint32_t)0x00000000U)         /* !< FCC clock is MCLK/4 */
#define SYSCTL_GENCLKCFG_FCCSELCLK_SYSOSC        ((uint32_t)0x00010000U)         /* !< FCC clock is SYSOSC */
#define SYSCTL_GENCLKCFG_FCCSELCLK_HFCLK         ((uint32_t)0x00020000U)         /* !< FCC clock is HFCLK */
#define SYSCTL_GENCLKCFG_FCCSELCLK_EXTCLK        ((uint32_t)0x00030000U)         /* !< FCC clock is the CLK_OUT selection */
#define SYSCTL_GENCLKCFG_FCCSELCLK_SYSPLLCLK0    ((uint32_t)0x00040000U)         /* !< FCC clock is SYSPLLCLK0 */
#define SYSCTL_GENCLKCFG_FCCSELCLK_SYSPLLCLK1    ((uint32_t)0x00050000U)         /* !< FCC clock is SYSPLLCLK1 */
#define SYSCTL_GENCLKCFG_FCCSELCLK_FCCIN         ((uint32_t)0x00070000U)         /* !< FCC clock is the FCCIN external
                                                                                    input */
/* SYSCTL_GENCLKCFG[FCCTRIGSRC] Bits */
#define SYSCTL_GENCLKCFG_FCCTRIGSRC_OFS          (20)                            /* !< FCCTRIGSRC Offset */
#define SYSCTL_GENCLKCFG_FCCTRIGSRC_MASK         ((uint32_t)0x00100000U)         /* !< FCCTRIGSRC selects the frequency
                                                                                    clock counter (FCC) trigger source. */
#define SYSCTL_GENCLKCFG_FCCTRIGSRC_EXTPIN       ((uint32_t)0x00000000U)         /* !< FCC trigger is the external pin */
#define SYSCTL_GENCLKCFG_FCCTRIGSRC_LFCLK        ((uint32_t)0x00100000U)         /* !< FCC trigger is the LFCLK */
/* SYSCTL_GENCLKCFG[FCCLVLTRIG] Bits */
#define SYSCTL_GENCLKCFG_FCCLVLTRIG_OFS          (21)                            /* !< FCCLVLTRIG Offset */
#define SYSCTL_GENCLKCFG_FCCLVLTRIG_MASK         ((uint32_t)0x00200000U)         /* !< FCCLVLTRIG selects the frequency
                                                                                    clock counter (FCC) trigger mode. */
#define SYSCTL_GENCLKCFG_FCCLVLTRIG_RISE2RISE    ((uint32_t)0x00000000U)         /* !< Rising edge to rising edge
                                                                                    triggered */
#define SYSCTL_GENCLKCFG_FCCLVLTRIG_LEVEL        ((uint32_t)0x00200000U)         /* !< Level triggered */
/* SYSCTL_GENCLKCFG[EXCLKSRC] Bits */
#define SYSCTL_GENCLKCFG_EXCLKSRC_OFS            (0)                             /* !< EXCLKSRC Offset */
#define SYSCTL_GENCLKCFG_EXCLKSRC_MASK           ((uint32_t)0x00000007U)         /* !< EXCLKSRC selects the source for the
                                                                                    CLK_OUT external clock output block.
                                                                                    ULPCLK and MFPCLK require the CLK_OUT
                                                                                    divider (EXCLKDIVEN) to be enabled */
#define SYSCTL_GENCLKCFG_EXCLKSRC_SYSOSC         ((uint32_t)0x00000000U)         /* !< CLK_OUT is SYSOSC */
#define SYSCTL_GENCLKCFG_EXCLKSRC_ULPCLK         ((uint32_t)0x00000001U)         /* !< CLK_OUT is ULPCLK (EXCLKDIVEN must
                                                                                    be enabled) */
#define SYSCTL_GENCLKCFG_EXCLKSRC_LFCLK          ((uint32_t)0x00000002U)         /* !< CLK_OUT is LFCLK */
#define SYSCTL_GENCLKCFG_EXCLKSRC_MFPCLK         ((uint32_t)0x00000003U)         /* !< CLK_OUT is MFPCLK (EXCLKDIVEN must
                                                                                    be enabled) */
#define SYSCTL_GENCLKCFG_EXCLKSRC_HFCLK          ((uint32_t)0x00000004U)         /* !< CLK_OUT is HFCLK */
#define SYSCTL_GENCLKCFG_EXCLKSRC_SYSPLLOUT1     ((uint32_t)0x00000005U)         /* !< CLK_OUT is SYSPLLCLK1 (SYSPLLCLK1
                                                                                    must be <=48MHz) */
/* SYSCTL_GENCLKCFG[EXCLKDIVVAL] Bits */
#define SYSCTL_GENCLKCFG_EXCLKDIVVAL_OFS         (4)                             /* !< EXCLKDIVVAL Offset */
#define SYSCTL_GENCLKCFG_EXCLKDIVVAL_MASK        ((uint32_t)0x00000070U)         /* !< EXCLKDIVVAL selects the divider
                                                                                    value for the divider in the CLK_OUT
                                                                                    external clock output block. */
#define SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV2        ((uint32_t)0x00000000U)         /* !< CLK_OUT source is divided by 2 */
#define SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV4        ((uint32_t)0x00000010U)         /* !< CLK_OUT source is divided by 4 */
#define SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV6        ((uint32_t)0x00000020U)         /* !< CLK_OUT source is divided by 6 */
#define SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV8        ((uint32_t)0x00000030U)         /* !< CLK_OUT source is divided by 8 */
#define SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV10       ((uint32_t)0x00000040U)         /* !< CLK_OUT source is divided by 10 */
#define SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV12       ((uint32_t)0x00000050U)         /* !< CLK_OUT source is divided by 12 */
#define SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV14       ((uint32_t)0x00000060U)         /* !< CLK_OUT source is divided by 14 */
#define SYSCTL_GENCLKCFG_EXCLKDIVVAL_DIV16       ((uint32_t)0x00000070U)         /* !< CLK_OUT source is divided by 16 */
/* SYSCTL_GENCLKCFG[EXCLKDIVEN] Bits */
#define SYSCTL_GENCLKCFG_EXCLKDIVEN_OFS          (7)                             /* !< EXCLKDIVEN Offset */
#define SYSCTL_GENCLKCFG_EXCLKDIVEN_MASK         ((uint32_t)0x00000080U)         /* !< EXCLKDIVEN enables or disables the
                                                                                    divider function of the CLK_OUT
                                                                                    external clock output block. */
#define SYSCTL_GENCLKCFG_EXCLKDIVEN_PASSTHRU     ((uint32_t)0x00000000U)         /* !< CLock divider is disabled
                                                                                    (passthrough, EXCLKDIVVAL is not
                                                                                    applied) */
#define SYSCTL_GENCLKCFG_EXCLKDIVEN_ENABLE       ((uint32_t)0x00000080U)         /* !< Clock divider is enabled
                                                                                    (EXCLKDIVVAL is applied) */

/* SYSCTL_PMODECFG Bits */
/* SYSCTL_PMODECFG[DSLEEP] Bits */
#define SYSCTL_PMODECFG_DSLEEP_OFS               (0)                             /* !< DSLEEP Offset */
#define SYSCTL_PMODECFG_DSLEEP_MASK              ((uint32_t)0x00000003U)         /* !< DSLEEP selects the operating mode
                                                                                    to enter upon a DEEPSLEEP request
                                                                                    from the CPU. */
#define SYSCTL_PMODECFG_DSLEEP_STOP              ((uint32_t)0x00000000U)         /* !< STOP mode is entered */
#define SYSCTL_PMODECFG_DSLEEP_STANDBY           ((uint32_t)0x00000001U)         /* !< STANDBY mode is entered */
#define SYSCTL_PMODECFG_DSLEEP_SHUTDOWN          ((uint32_t)0x00000002U)         /* !< SHUTDOWN mode is entered */

/* SYSCTL_MLDOLPENCFG Bits */
/* SYSCTL_MLDOLPENCFG[CVLODIS] Bits */
#define SYSCTL_MLDOLPENCFG_CVLODIS_OFS           (0)                             /* !< CVLODIS Offset */
#define SYSCTL_MLDOLPENCFG_CVLODIS_MASK          ((uint32_t)0x00000001U)         /* !< Control to disable lowering the
                                                                                    core voltage for STOP and STANDBY */
#define SYSCTL_MLDOLPENCFG_CVLODIS_FALSE         ((uint32_t)0x00000000U)         /* !< Lower Core Voltage for STOP and
                                                                                    STANDBY mode */
#define SYSCTL_MLDOLPENCFG_CVLODIS_TRUE          ((uint32_t)0x00000001U)         /* !< Do Not Lower Core Voltage for STOP
                                                                                    and STANDBY mode to provide faster
                                                                                    wakeup */

/* SYSCTL_FCC Bits */
/* SYSCTL_FCC[DATA] Bits */
#define SYSCTL_FCC_DATA_OFS                      (0)                             /* !< DATA Offset */
#define SYSCTL_FCC_DATA_MASK                     ((uint32_t)0x003FFFFFU)         /* !< Frequency clock counter (FCC) count
                                                                                    value. */

/* SYSCTL_PMULDOSPARECTL Bits */

/* SYSCTL_SYSCTL_ECO_REG1 Bits */
/* SYSCTL_SYSCTL_ECO_REG1[ECOREG] Bits */
#define SYSCTL_SYSCTL_ECO_REG1_ECOREG_OFS        (0)                             /* !< ECOREG Offset */
#define SYSCTL_SYSCTL_ECO_REG1_ECOREG_MASK       ((uint32_t)0xFFFFFFFFU)         /* !< ECO Reg 1 for M33 */

/* SYSCTL_SYSCTL_ECO_REG2 Bits */
/* SYSCTL_SYSCTL_ECO_REG2[ECOREG] Bits */
#define SYSCTL_SYSCTL_ECO_REG2_ECOREG_OFS        (0)                             /* !< ECOREG Offset */
#define SYSCTL_SYSCTL_ECO_REG2_ECOREG_MASK       ((uint32_t)0xFFFFFFFFU)         /* !< ECO Reg 2 for M33 */

/* SYSCTL_SYSTEMCFG Bits */
/* SYSCTL_SYSTEMCFG[KEY] Bits */
#define SYSCTL_SYSTEMCFG_KEY_OFS                 (24)                            /* !< KEY Offset */
#define SYSCTL_SYSTEMCFG_KEY_MASK                ((uint32_t)0xFF000000U)         /* !< The key value of 1Bh (27) must be
                                                                                    written to KEY together with contents
                                                                                    to be updated. Reads as 0 */
#define SYSCTL_SYSTEMCFG_KEY_VALUE               ((uint32_t)0x1B000000U)         /* !< Issue write */
/* SYSCTL_SYSTEMCFG[FLASHECCRSTDIS] Bits */
#define SYSCTL_SYSTEMCFG_FLASHECCRSTDIS_OFS      (2)                             /* !< FLASHECCRSTDIS Offset */
#define SYSCTL_SYSTEMCFG_FLASHECCRSTDIS_MASK     ((uint32_t)0x00000004U)         /* !< FLASHECCRSTDIS specifies whether a
                                                                                    flash ECC double error detect (DED)
                                                                                    will trigger a SYSRST or an NMI. */
#define SYSCTL_SYSTEMCFG_FLASHECCRSTDIS_FALSE    ((uint32_t)0x00000000U)         /* !< Flash ECC DED will trigger a SYSRST */
#define SYSCTL_SYSTEMCFG_FLASHECCRSTDIS_TRUE     ((uint32_t)0x00000004U)         /* !< Flash ECC DED will trigger a NMI */
/* SYSCTL_SYSTEMCFG[WWDTLP0RSTDIS] Bits */
#define SYSCTL_SYSTEMCFG_WWDTLP0RSTDIS_OFS       (0)                             /* !< WWDTLP0RSTDIS Offset */
#define SYSCTL_SYSTEMCFG_WWDTLP0RSTDIS_MASK      ((uint32_t)0x00000001U)         /* !< WWDTLP0RSTDIS specifies whether a
                                                                                    WWDT Error Event will trigger a
                                                                                    BOOTRST or an NMI. */
#define SYSCTL_SYSTEMCFG_WWDTLP0RSTDIS_FALSE     ((uint32_t)0x00000000U)         /* !< WWDTLP0 Error Event will trigger a
                                                                                    BOOTRST */
#define SYSCTL_SYSTEMCFG_WWDTLP0RSTDIS_TRUE      ((uint32_t)0x00000001U)         /* !< WWDTLP0 Error Event will trigger an
                                                                                    NMI */

/* SYSCTL_SRAMCFG Bits */
/* SYSCTL_SRAMCFG[KEY] Bits */
#define SYSCTL_SRAMCFG_KEY_OFS                   (24)                            /* !< KEY Offset */
#define SYSCTL_SRAMCFG_KEY_MASK                  ((uint32_t)0xFF000000U)         /* !< The key value of B5h (181) must be
                                                                                    written to KEY together with contents
                                                                                    to be updated. Reads as 0 */
#define SYSCTL_SRAMCFG_KEY_VALUE                 ((uint32_t)0xB5000000U)         /* !< Issue write */
/* SYSCTL_SRAMCFG[BANKINITDIS3] Bits */
#define SYSCTL_SRAMCFG_BANKINITDIS3_OFS          (19)                            /* !< BANKINITDIS3 Offset */
#define SYSCTL_SRAMCFG_BANKINITDIS3_MASK         ((uint32_t)0x00080000U)         /* !< SRAM BANK3 Initialization */
#define SYSCTL_SRAMCFG_BANKINITDIS3_FALSE        ((uint32_t)0x00000000U)         /* !< SRAM BANK3 will Initialize when
                                                                                    transitioning from OFF to ON */
#define SYSCTL_SRAMCFG_BANKINITDIS3_TRUE         ((uint32_t)0x00080000U)         /* !< SRAM BANK3 will NOT Initialize when
                                                                                    transitioning from OFF to ON */
/* SYSCTL_SRAMCFG[BANKINITDIS2] Bits */
#define SYSCTL_SRAMCFG_BANKINITDIS2_OFS          (18)                            /* !< BANKINITDIS2 Offset */
#define SYSCTL_SRAMCFG_BANKINITDIS2_MASK         ((uint32_t)0x00040000U)         /* !< SRAM BANK2 Initialization */
#define SYSCTL_SRAMCFG_BANKINITDIS2_FALSE        ((uint32_t)0x00000000U)         /* !< SRAM BANK2 will Initialize when
                                                                                    transitioning from OFF to ON */
#define SYSCTL_SRAMCFG_BANKINITDIS2_TRUE         ((uint32_t)0x00040000U)         /* !< SRAM BANK2 will NOT Initialize when
                                                                                    transitioning from OFF to ON */
/* SYSCTL_SRAMCFG[BANKINITDIS0] Bits */
#define SYSCTL_SRAMCFG_BANKINITDIS0_OFS          (16)                            /* !< BANKINITDIS0 Offset */
#define SYSCTL_SRAMCFG_BANKINITDIS0_MASK         ((uint32_t)0x00010000U)         /* !< SRAM BANK0 Initialization */
#define SYSCTL_SRAMCFG_BANKINITDIS0_FALSE        ((uint32_t)0x00000000U)         /* !< SRAM BANK0 will Initialize when
                                                                                    transitioning from OFF to ON */
#define SYSCTL_SRAMCFG_BANKINITDIS0_TRUE         ((uint32_t)0x00010000U)         /* !< SRAM BANK0 will NOT Initialize when
                                                                                    transitioning from OFF to ON */
/* SYSCTL_SRAMCFG[BANKINITDIS1] Bits */
#define SYSCTL_SRAMCFG_BANKINITDIS1_OFS          (17)                            /* !< BANKINITDIS1 Offset */
#define SYSCTL_SRAMCFG_BANKINITDIS1_MASK         ((uint32_t)0x00020000U)         /* !< SRAM BANK1 Initialization */
#define SYSCTL_SRAMCFG_BANKINITDIS1_FALSE        ((uint32_t)0x00000000U)         /* !< SRAM BANK1 will Initialize when
                                                                                    transitioning from OFF to ON */
#define SYSCTL_SRAMCFG_BANKINITDIS1_TRUE         ((uint32_t)0x00020000U)         /* !< SRAM BANK1 will NOT Initialize when
                                                                                    transitioning from OFF to ON */

/* SYSCTL_WRITELOCK Bits */
/* SYSCTL_WRITELOCK[ACTIVE] Bits */
#define SYSCTL_WRITELOCK_ACTIVE_OFS              (0)                             /* !< ACTIVE Offset */
#define SYSCTL_WRITELOCK_ACTIVE_MASK             ((uint32_t)0x00000001U)         /* !< ACTIVE controls whether critical
                                                                                    SYSCTL registers are write protected
                                                                                    or not. */
#define SYSCTL_WRITELOCK_ACTIVE_DISABLE          ((uint32_t)0x00000000U)         /* !< Allow writes to lockable registers */
#define SYSCTL_WRITELOCK_ACTIVE_ENABLE           ((uint32_t)0x00000001U)         /* !< Disallow writes to lockable
                                                                                    registers */

/* SYSCTL_CLKSTATUS Bits */
/* SYSCTL_CLKSTATUS[LFOSCGOOD] Bits */
#define SYSCTL_CLKSTATUS_LFOSCGOOD_OFS           (11)                            /* !< LFOSCGOOD Offset */
#define SYSCTL_CLKSTATUS_LFOSCGOOD_MASK          ((uint32_t)0x00000800U)         /* !< LFOSCGOOD indicates when the LFOSC
                                                                                    startup has completed and the LFOSC
                                                                                    is ready for use. */
#define SYSCTL_CLKSTATUS_LFOSCGOOD_FALSE         ((uint32_t)0x00000000U)         /* !< LFOSC is not ready */
#define SYSCTL_CLKSTATUS_LFOSCGOOD_TRUE          ((uint32_t)0x00000800U)         /* !< LFOSC is ready */
/* SYSCTL_CLKSTATUS[HFCLKGOOD] Bits */
#define SYSCTL_CLKSTATUS_HFCLKGOOD_OFS           (8)                             /* !< HFCLKGOOD Offset */
#define SYSCTL_CLKSTATUS_HFCLKGOOD_MASK          ((uint32_t)0x00000100U)         /* !< HFCLKGOOD indicates that the HFCLK
                                                                                    started correctly.  When the XTAL is
                                                                                    started or HFCLK_IN is selected as
                                                                                    the HFCLK source,  this bit will be
                                                                                    set by hardware if a valid HFCLK is
                                                                                    detected, and cleared if HFCLK is not
                                                                                    operating within the expected range. */
#define SYSCTL_CLKSTATUS_HFCLKGOOD_FALSE         ((uint32_t)0x00000000U)         /* !< HFCLK did not start correctly */
#define SYSCTL_CLKSTATUS_HFCLKGOOD_TRUE          ((uint32_t)0x00000100U)         /* !< HFCLK started correctly */
/* SYSCTL_CLKSTATUS[HSCLKDEAD] Bits */
#define SYSCTL_CLKSTATUS_HSCLKDEAD_OFS           (20)                            /* !< HSCLKDEAD Offset */
#define SYSCTL_CLKSTATUS_HSCLKDEAD_MASK          ((uint32_t)0x00100000U)         /* !< HSCLKDEAD is set by hardware if the
                                                                                    selected source for HSCLK was started
                                                                                    but did not start successfully. */
#define SYSCTL_CLKSTATUS_HSCLKDEAD_FALSE         ((uint32_t)0x00000000U)         /* !< The HSCLK source was not started or
                                                                                    started correctly */
#define SYSCTL_CLKSTATUS_HSCLKDEAD_TRUE          ((uint32_t)0x00100000U)         /* !< The HSCLK source did not start
                                                                                    correctly */
/* SYSCTL_CLKSTATUS[SYSPLLBLKUPD] Bits */
#define SYSCTL_CLKSTATUS_SYSPLLBLKUPD_OFS        (29)                            /* !< SYSPLLBLKUPD Offset */
#define SYSCTL_CLKSTATUS_SYSPLLBLKUPD_MASK       ((uint32_t)0x20000000U)         /* !< SYSPLLBLKUPD indicates when writes
                                                                                    to SYSPLLCFG0/1 and SYSPLLPARAM0/1
                                                                                    are blocked. */
#define SYSCTL_CLKSTATUS_SYSPLLBLKUPD_FALSE      ((uint32_t)0x00000000U)         /* !< writes to SYSPLLCFG0/1 and
                                                                                    SYSPLLPARAM0/1 are allowed */
#define SYSCTL_CLKSTATUS_SYSPLLBLKUPD_TRUE       ((uint32_t)0x20000000U)         /* !< writes to SYSPLLCFG0/1 and
                                                                                    SYSPLLPARAM0/1 are blocked */
/* SYSCTL_CLKSTATUS[HFCLKOFF] Bits */
#define SYSCTL_CLKSTATUS_HFCLKOFF_OFS            (13)                            /* !< HFCLKOFF Offset */
#define SYSCTL_CLKSTATUS_HFCLKOFF_MASK           ((uint32_t)0x00002000U)         /* !< HFCLKOFF indicates if the HFCLK is
                                                                                    disabled or was dead at startup.
                                                                                    When the HFCLK is started, HFCLKOFF
                                                                                    is cleared by hardware.  Following
                                                                                    startup of the HFCLK, if the HFCLK
                                                                                    startup monitor determines that the
                                                                                    HFCLK was not started correctly,
                                                                                    HFCLKOFF is set. */
#define SYSCTL_CLKSTATUS_HFCLKOFF_FALSE          ((uint32_t)0x00000000U)         /* !< HFCLK started correctly and is
                                                                                    enabled */
#define SYSCTL_CLKSTATUS_HFCLKOFF_TRUE           ((uint32_t)0x00002000U)         /* !< HFCLK is disabled or was dead at
                                                                                    startup */
/* SYSCTL_CLKSTATUS[HFCLKBLKUPD] Bits */
#define SYSCTL_CLKSTATUS_HFCLKBLKUPD_OFS         (28)                            /* !< HFCLKBLKUPD Offset */
#define SYSCTL_CLKSTATUS_HFCLKBLKUPD_MASK        ((uint32_t)0x10000000U)         /* !< HFCLKBLKUPD indicates when writes
                                                                                    to the HFCLKCLKCFG register are
                                                                                    blocked. */
#define SYSCTL_CLKSTATUS_HFCLKBLKUPD_FALSE       ((uint32_t)0x00000000U)         /* !< Writes to HFCLKCLKCFG are allowed */
#define SYSCTL_CLKSTATUS_HFCLKBLKUPD_TRUE        ((uint32_t)0x10000000U)         /* !< Writes to HFCLKCLKCFG are blocked */
/* SYSCTL_CLKSTATUS[HSCLKGOOD] Bits */
#define SYSCTL_CLKSTATUS_HSCLKGOOD_OFS           (21)                            /* !< HSCLKGOOD Offset */
#define SYSCTL_CLKSTATUS_HSCLKGOOD_MASK          ((uint32_t)0x00200000U)         /* !< HSCLKGOOD is set by hardware if the
                                                                                    selected clock source for HSCLK
                                                                                    started successfully. */
#define SYSCTL_CLKSTATUS_HSCLKGOOD_FALSE         ((uint32_t)0x00000000U)         /* !< The HSCLK source did not start
                                                                                    correctly */
#define SYSCTL_CLKSTATUS_HSCLKGOOD_TRUE          ((uint32_t)0x00200000U)         /* !< The HSCLK source started correctly */
/* SYSCTL_CLKSTATUS[SYSPLLGOOD] Bits */
#define SYSCTL_CLKSTATUS_SYSPLLGOOD_OFS          (9)                             /* !< SYSPLLGOOD Offset */
#define SYSCTL_CLKSTATUS_SYSPLLGOOD_MASK         ((uint32_t)0x00000200U)         /* !< SYSPLLGOOD indicates if the SYSPLL
                                                                                    started correctly.  When the SYSPLL
                                                                                    is started, SYSPLLGOOD is cleared by
                                                                                    hardware.  After the startup settling
                                                                                    time has expired, the SYSPLL status
                                                                                    is tested.  If the SYSPLL started
                                                                                    successfully the SYSPLLGOOD bit is
                                                                                    set, else it is left cleared. */
#define SYSCTL_CLKSTATUS_SYSPLLGOOD_FALSE        ((uint32_t)0x00000000U)         /* !< SYSPLL did not start correctly */
#define SYSCTL_CLKSTATUS_SYSPLLGOOD_TRUE         ((uint32_t)0x00000200U)         /* !< SYSPLL started correctly */
/* SYSCTL_CLKSTATUS[HSCLKMUX] Bits */
#define SYSCTL_CLKSTATUS_HSCLKMUX_OFS            (4)                             /* !< HSCLKMUX Offset */
#define SYSCTL_CLKSTATUS_HSCLKMUX_MASK           ((uint32_t)0x00000010U)         /* !< HSCLKMUX indicates if MCLK is
                                                                                    currently sourced from the high-speed
                                                                                    clock (HSCLK). */
#define SYSCTL_CLKSTATUS_HSCLKMUX_SYSOSC         ((uint32_t)0x00000000U)         /* !< MCLK is not sourced from HSCLK */
#define SYSCTL_CLKSTATUS_HSCLKMUX_HSCLK          ((uint32_t)0x00000010U)         /* !< MCLK is sourced from HSCLK */
/* SYSCTL_CLKSTATUS[SYSOSCFREQ] Bits */
#define SYSCTL_CLKSTATUS_SYSOSCFREQ_OFS          (0)                             /* !< SYSOSCFREQ Offset */
#define SYSCTL_CLKSTATUS_SYSOSCFREQ_MASK         ((uint32_t)0x00000003U)         /* !< SYSOSCFREQ indicates the current
                                                                                    SYSOSC operating frequency. */
#define SYSCTL_CLKSTATUS_SYSOSCFREQ_SYSOSC32M    ((uint32_t)0x00000000U)         /* !< SYSOSC is at base frequency (32MHz) */
#define SYSCTL_CLKSTATUS_SYSOSCFREQ_SYSOSC4M     ((uint32_t)0x00000001U)         /* !< SYSOSC is at low frequency (4MHz) */
/* SYSCTL_CLKSTATUS[HSCLKSOFF] Bits */
#define SYSCTL_CLKSTATUS_HSCLKSOFF_OFS           (12)                            /* !< HSCLKSOFF Offset */
#define SYSCTL_CLKSTATUS_HSCLKSOFF_MASK          ((uint32_t)0x00001000U)         /* !< HSCLKSOFF is set when the high
                                                                                    speed clock sources (SYSPLL, HFCLK)
                                                                                    are disabled or dead.  It is the
                                                                                    logical AND of HFCLKOFF and
                                                                                    SYSPLLOFF. */
#define SYSCTL_CLKSTATUS_HSCLKSOFF_FALSE         ((uint32_t)0x00000000U)         /* !< SYSPLL, HFCLK, or both were started
                                                                                    correctly and remain enabled */
#define SYSCTL_CLKSTATUS_HSCLKSOFF_TRUE          ((uint32_t)0x00001000U)         /* !< SYSPLL and HFCLK are both either
                                                                                    off or dead */
/* SYSCTL_CLKSTATUS[FCLMODE] Bits */
#define SYSCTL_CLKSTATUS_FCLMODE_OFS             (24)                            /* !< FCLMODE Offset */
#define SYSCTL_CLKSTATUS_FCLMODE_MASK            ((uint32_t)0x01000000U)         /* !< FCLMODE indicates if the SYSOSC
                                                                                    frequency correction loop (FCL) is
                                                                                    enabled. */
#define SYSCTL_CLKSTATUS_FCLMODE_DISABLED        ((uint32_t)0x00000000U)         /* !< SYSOSC FCL is disabled */
#define SYSCTL_CLKSTATUS_FCLMODE_ENABLED         ((uint32_t)0x01000000U)         /* !< SYSOSC FCL is enabled */
/* SYSCTL_CLKSTATUS[CURHSCLKSEL] Bits */
#define SYSCTL_CLKSTATUS_CURHSCLKSEL_OFS         (16)                            /* !< CURHSCLKSEL Offset */
#define SYSCTL_CLKSTATUS_CURHSCLKSEL_MASK        ((uint32_t)0x00010000U)         /* !< CURHSCLKSEL indicates the current
                                                                                    clock source for HSCLK. */
#define SYSCTL_CLKSTATUS_CURHSCLKSEL_SYSPLL      ((uint32_t)0x00000000U)         /* !< HSCLK is currently sourced from the
                                                                                    SYSPLL */
#define SYSCTL_CLKSTATUS_CURHSCLKSEL_HFCLK       ((uint32_t)0x00010000U)         /* !< HSCLK is currently sourced from the
                                                                                    HFCLK */
/* SYSCTL_CLKSTATUS[FCCDONE] Bits */
#define SYSCTL_CLKSTATUS_FCCDONE_OFS             (25)                            /* !< FCCDONE Offset */
#define SYSCTL_CLKSTATUS_FCCDONE_MASK            ((uint32_t)0x02000000U)         /* !< FCCDONE indicates when a frequency
                                                                                    clock counter capture is complete. */
#define SYSCTL_CLKSTATUS_FCCDONE_NOTDONE         ((uint32_t)0x00000000U)         /* !< FCC capture is not done */
#define SYSCTL_CLKSTATUS_FCCDONE_DONE            ((uint32_t)0x02000000U)         /* !< FCC capture is done */
/* SYSCTL_CLKSTATUS[SYSPLLOFF] Bits */
#define SYSCTL_CLKSTATUS_SYSPLLOFF_OFS           (14)                            /* !< SYSPLLOFF Offset */
#define SYSCTL_CLKSTATUS_SYSPLLOFF_MASK          ((uint32_t)0x00004000U)         /* !< SYSPLLOFF indicates if the SYSPLL
                                                                                    is disabled or was dead at startup.
                                                                                    When the SYSPLL is started, SYSPLLOFF
                                                                                    is cleared by hardware.  Following
                                                                                    startup of the SYSPLL, if the SYSPLL
                                                                                    startup monitor determines that the
                                                                                    SYSPLL was not started correctly,
                                                                                    SYSPLLOFF is set. */
#define SYSCTL_CLKSTATUS_SYSPLLOFF_FALSE         ((uint32_t)0x00000000U)         /* !< SYSPLL started correctly and is
                                                                                    enabled */
#define SYSCTL_CLKSTATUS_SYSPLLOFF_TRUE          ((uint32_t)0x00004000U)         /* !< SYSPLL is disabled or was dead
                                                                                    startup */

/* SYSCTL_SYSSTATUS Bits */
/* SYSCTL_SYSSTATUS[SHDNIOLOCK] Bits */
#define SYSCTL_SYSSTATUS_SHDNIOLOCK_OFS          (14)                            /* !< SHDNIOLOCK Offset */
#define SYSCTL_SYSSTATUS_SHDNIOLOCK_MASK         ((uint32_t)0x00004000U)         /* !< SHDNIOLOCK indicates when IO is
                                                                                    locked due to SHUTDOWN */
#define SYSCTL_SYSSTATUS_SHDNIOLOCK_FALSE        ((uint32_t)0x00000000U)         /* !< IO IS NOT Locked due to SHUTDOWN */
#define SYSCTL_SYSSTATUS_SHDNIOLOCK_TRUE         ((uint32_t)0x00004000U)         /* !< IO IS Locked due to SHUTDOWN */
/* SYSCTL_SYSSTATUS[EXTRSTPINDIS] Bits */
#define SYSCTL_SYSSTATUS_EXTRSTPINDIS_OFS        (12)                            /* !< EXTRSTPINDIS Offset */
#define SYSCTL_SYSSTATUS_EXTRSTPINDIS_MASK       ((uint32_t)0x00001000U)         /* !< EXTRSTPINDIS indicates when user
                                                                                    has disabled the use of external
                                                                                    reset pin */
#define SYSCTL_SYSSTATUS_EXTRSTPINDIS_FALSE      ((uint32_t)0x00000000U)         /* !< External Reset Pin Enabled */
#define SYSCTL_SYSSTATUS_EXTRSTPINDIS_TRUE       ((uint32_t)0x00001000U)         /* !< External Reset Pin Disabled */
/* SYSCTL_SYSSTATUS[SRAMBANK3READY] Bits */
#define SYSCTL_SYSSTATUS_SRAMBANK3READY_OFS      (19)                            /* !< SRAMBANK3READY Offset */
#define SYSCTL_SYSSTATUS_SRAMBANK3READY_MASK     ((uint32_t)0x00080000U)         /* !< SRAM BANK3 READY STATE */
#define SYSCTL_SYSSTATUS_SRAMBANK3READY_FALSE    ((uint32_t)0x00000000U)         /* !< SRAM BANK3 is NOT READY for access */
#define SYSCTL_SYSSTATUS_SRAMBANK3READY_TRUE     ((uint32_t)0x00080000U)         /* !< SRAM BANK3 is READY for access */
/* SYSCTL_SYSSTATUS[MCAN0READY] Bits */
#define SYSCTL_SYSSTATUS_MCAN0READY_OFS          (8)                             /* !< MCAN0READY Offset */
#define SYSCTL_SYSSTATUS_MCAN0READY_MASK         ((uint32_t)0x00000100U)         /* !< MCAN0READY indicates when the MCAN0
                                                                                    peripheral is ready. */
#define SYSCTL_SYSSTATUS_MCAN0READY_FALSE        ((uint32_t)0x00000000U)         /* !< MCAN0 is not ready */
#define SYSCTL_SYSSTATUS_MCAN0READY_TRUE         ((uint32_t)0x00000100U)         /* !< MCAN0 is ready */
/* SYSCTL_SYSSTATUS[FLASHDED] Bits */
#define SYSCTL_SYSSTATUS_FLASHDED_OFS            (0)                             /* !< FLASHDED Offset */
#define SYSCTL_SYSSTATUS_FLASHDED_MASK           ((uint32_t)0x00000001U)         /* !< FLASHDED indicates if a flash ECC
                                                                                    double bit error was detected (DED). */
#define SYSCTL_SYSSTATUS_FLASHDED_FALSE          ((uint32_t)0x00000000U)         /* !< No flash ECC double bit error
                                                                                    detected */
#define SYSCTL_SYSSTATUS_FLASHDED_TRUE           ((uint32_t)0x00000001U)         /* !< Flash ECC double bit error detected */
/* SYSCTL_SYSSTATUS[FLASHSEC] Bits */
#define SYSCTL_SYSSTATUS_FLASHSEC_OFS            (1)                             /* !< FLASHSEC Offset */
#define SYSCTL_SYSSTATUS_FLASHSEC_MASK           ((uint32_t)0x00000002U)         /* !< FLASHSEC indicates if a flash ECC
                                                                                    single bit error was detected and
                                                                                    corrected (SEC). */
#define SYSCTL_SYSSTATUS_FLASHSEC_FALSE          ((uint32_t)0x00000000U)         /* !< No flash ECC single bit error
                                                                                    detected */
#define SYSCTL_SYSSTATUS_FLASHSEC_TRUE           ((uint32_t)0x00000002U)         /* !< Flash ECC single bit error was
                                                                                    detected and corrected */
/* SYSCTL_SYSSTATUS[SRAMBANK1READY] Bits */
#define SYSCTL_SYSSTATUS_SRAMBANK1READY_OFS      (17)                            /* !< SRAMBANK1READY Offset */
#define SYSCTL_SYSSTATUS_SRAMBANK1READY_MASK     ((uint32_t)0x00020000U)         /* !< SRAM BANK1 READY STATE */
#define SYSCTL_SYSSTATUS_SRAMBANK1READY_FALSE    ((uint32_t)0x00000000U)         /* !< SRAM BANK1 is NOT READY for access */
#define SYSCTL_SYSSTATUS_SRAMBANK1READY_TRUE     ((uint32_t)0x00020000U)         /* !< SRAM BANK1 is READY for access */
/* SYSCTL_SYSSTATUS[PMUIREFGOOD] Bits */
#define SYSCTL_SYSSTATUS_PMUIREFGOOD_OFS         (6)                             /* !< PMUIREFGOOD Offset */
#define SYSCTL_SYSSTATUS_PMUIREFGOOD_MASK        ((uint32_t)0x00000040U)         /* !< PMUIREFGOOD is set by hardware when
                                                                                    the PMU current reference is ready. */
#define SYSCTL_SYSSTATUS_PMUIREFGOOD_FALSE       ((uint32_t)0x00000000U)         /* !< IREF is not ready */
#define SYSCTL_SYSSTATUS_PMUIREFGOOD_TRUE        ((uint32_t)0x00000040U)         /* !< IREF is ready */
/* SYSCTL_SYSSTATUS[SRAMBANK2READY] Bits */
#define SYSCTL_SYSSTATUS_SRAMBANK2READY_OFS      (18)                            /* !< SRAMBANK2READY Offset */
#define SYSCTL_SYSSTATUS_SRAMBANK2READY_MASK     ((uint32_t)0x00040000U)         /* !< SRAM BANK2 READY STATE */
#define SYSCTL_SYSSTATUS_SRAMBANK2READY_FALSE    ((uint32_t)0x00000000U)         /* !< SRAM BANK2 is NOT READY for access */
#define SYSCTL_SYSSTATUS_SRAMBANK2READY_TRUE     ((uint32_t)0x00040000U)         /* !< SRAM BANK2 is READY for access */
/* SYSCTL_SYSSTATUS[REBOOTATTEMPTS] Bits */
#define SYSCTL_SYSSTATUS_REBOOTATTEMPTS_OFS      (30)                            /* !< REBOOTATTEMPTS Offset */
#define SYSCTL_SYSSTATUS_REBOOTATTEMPTS_MASK     ((uint32_t)0xC0000000U)         /* !< REBOOTATTEMPTS indicates the number
                                                                                    of boot attempts taken before the
                                                                                    user application starts. */
/* SYSCTL_SYSSTATUS[SRAMBANK0READY] Bits */
#define SYSCTL_SYSSTATUS_SRAMBANK0READY_OFS      (16)                            /* !< SRAMBANK0READY Offset */
#define SYSCTL_SYSSTATUS_SRAMBANK0READY_MASK     ((uint32_t)0x00010000U)         /* !< SRAM BANK0 READY STATE */
#define SYSCTL_SYSSTATUS_SRAMBANK0READY_FALSE    ((uint32_t)0x00000000U)         /* !< SRAM BANK0 is NOT READY for access */
#define SYSCTL_SYSSTATUS_SRAMBANK0READY_TRUE     ((uint32_t)0x00010000U)         /* !< SRAM BANK0 is READY for access */
/* SYSCTL_SYSSTATUS[SWDJCFGDIS] Bits */
#define SYSCTL_SYSSTATUS_SWDJCFGDIS_OFS          (13)                            /* !< SWDJCFGDIS Offset */
#define SYSCTL_SYSSTATUS_SWDJCFGDIS_MASK         ((uint32_t)0x00002000U)         /* !< SWDJCFGDIS indicates when user has
                                                                                    disabled the use of SWD/JTAG Port */
#define SYSCTL_SYSSTATUS_SWDJCFGDIS_FALSE        ((uint32_t)0x00000000U)         /* !< SWD/JTAG Port Enabled */
#define SYSCTL_SYSSTATUS_SWDJCFGDIS_TRUE         ((uint32_t)0x00002000U)         /* !< SWD/JTAG Port Disabled */

/* SYSCTL_RSTCAUSE Bits */
/* SYSCTL_RSTCAUSE[ID] Bits */
#define SYSCTL_RSTCAUSE_ID_OFS                   (0)                             /* !< ID Offset */
#define SYSCTL_RSTCAUSE_ID_MASK                  ((uint32_t)0x0000001FU)         /* !< ID is a read-to-clear field which
                                                                                    indicates the lowest level reset
                                                                                    cause since the last read. */
#define SYSCTL_RSTCAUSE_ID_NORST                 ((uint32_t)0x00000000U)         /* !< No reset since last read */
#define SYSCTL_RSTCAUSE_ID_PORHWFAIL             ((uint32_t)0x00000001U)         /* !< POR- violation, SHUTDNSTOREx or PMU
                                                                                    trim parity fault */
#define SYSCTL_RSTCAUSE_ID_POREXNRST             ((uint32_t)0x00000002U)         /* !< NRST triggered POR (>1s hold) */
#define SYSCTL_RSTCAUSE_ID_PORSW                 ((uint32_t)0x00000003U)         /* !< Software triggered POR */
#define SYSCTL_RSTCAUSE_ID_BORSUPPLY             ((uint32_t)0x00000004U)         /* !< BOR0- violation */
#define SYSCTL_RSTCAUSE_ID_BORWAKESHUTDN         ((uint32_t)0x00000005U)         /* !< SHUTDOWN mode exit */
#define SYSCTL_RSTCAUSE_ID_BOOTNONPMUPARITY      ((uint32_t)0x00000008U)         /* !< Non-PMU trim parity fault */
#define SYSCTL_RSTCAUSE_ID_BOOTCLKFAIL           ((uint32_t)0x00000009U)         /* !< Fatal clock failure */
#define SYSCTL_RSTCAUSE_ID_BOOTEXNRST            ((uint32_t)0x0000000CU)         /* !< NRST triggered BOOTRST (<1s hold) */
#define SYSCTL_RSTCAUSE_ID_BOOTSW                ((uint32_t)0x0000000DU)         /* !< Software triggered BOOTRST */
#define SYSCTL_RSTCAUSE_ID_BOOTWWDT0             ((uint32_t)0x0000000EU)         /* !< WWDT0 violation */
#define SYSCTL_RSTCAUSE_ID_SYSBSLEXIT            ((uint32_t)0x00000010U)         /* !< BSL exit */
#define SYSCTL_RSTCAUSE_ID_SYSBSLENTRY           ((uint32_t)0x00000011U)         /* !< BSL entry */
#define SYSCTL_RSTCAUSE_ID_SYSFLASHECC           ((uint32_t)0x00000014U)         /* !< Flash uncorrectable ECC error */
#define SYSCTL_RSTCAUSE_ID_SYSCPULOCK            ((uint32_t)0x00000015U)         /* !< CPULOCK violation */
#define SYSCTL_RSTCAUSE_ID_SYSDBG                ((uint32_t)0x0000001AU)         /* !< Debug triggered SYSRST */
#define SYSCTL_RSTCAUSE_ID_SYSSW                 ((uint32_t)0x0000001BU)         /* !< Software triggered SYSRST */
#define SYSCTL_RSTCAUSE_ID_CPUDBG                ((uint32_t)0x0000001CU)         /* !< Debug triggered CPURST */
#define SYSCTL_RSTCAUSE_ID_CPUSW                 ((uint32_t)0x0000001DU)         /* !< Software triggered CPURST */

/* SYSCTL_RESETLEVEL Bits */
/* SYSCTL_RESETLEVEL[LEVEL] Bits */
#define SYSCTL_RESETLEVEL_LEVEL_OFS              (0)                             /* !< LEVEL Offset */
#define SYSCTL_RESETLEVEL_LEVEL_MASK             ((uint32_t)0x00000007U)         /* !< LEVEL is used to specify the type
                                                                                    of reset to be issued when RESETCMD
                                                                                    is set to generate a software
                                                                                    triggered reset. */
#define SYSCTL_RESETLEVEL_LEVEL_SYS              ((uint32_t)0x00000000U)         /* !< Issue a SYSRST (CPU plus
                                                                                    peripherals only) */
#define SYSCTL_RESETLEVEL_LEVEL_BOOT             ((uint32_t)0x00000001U)         /* !< Issue a BOOTRST (CPU, peripherals,
                                                                                    and boot configuration routine) */
#define SYSCTL_RESETLEVEL_LEVEL_BOOTLOADERENTRY  ((uint32_t)0x00000002U)         /* !< Issue a SYSRST and enter the boot
                                                                                    strap loader (BSL) */
#define SYSCTL_RESETLEVEL_LEVEL_POR              ((uint32_t)0x00000003U)         /* !< Issue a power-on reset (POR) */
#define SYSCTL_RESETLEVEL_LEVEL_BOOTLOADEREXIT   ((uint32_t)0x00000004U)         /* !< Issue a SYSRST and exit the boot
                                                                                    strap loader (BSL) */

/* SYSCTL_RESETCMD Bits */
/* SYSCTL_RESETCMD[KEY] Bits */
#define SYSCTL_RESETCMD_KEY_OFS                  (24)                            /* !< KEY Offset */
#define SYSCTL_RESETCMD_KEY_MASK                 ((uint32_t)0xFF000000U)         /* !< The key value of E4h (228) must be
                                                                                    written to KEY together with GO to
                                                                                    trigger the reset. */
#define SYSCTL_RESETCMD_KEY_VALUE                ((uint32_t)0xE4000000U)         /* !< Issue reset */
/* SYSCTL_RESETCMD[GO] Bits */
#define SYSCTL_RESETCMD_GO_OFS                   (0)                             /* !< GO Offset */
#define SYSCTL_RESETCMD_GO_MASK                  ((uint32_t)0x00000001U)         /* !< Execute the reset specified in
                                                                                    RESETLEVEL.LEVEL.  Must be written
                                                                                    together with the KEY. */
#define SYSCTL_RESETCMD_GO_TRUE                  ((uint32_t)0x00000001U)         /* !< Issue reset */

/* SYSCTL_SYSOSCFCLCTL Bits */
/* SYSCTL_SYSOSCFCLCTL[KEY] Bits */
#define SYSCTL_SYSOSCFCLCTL_KEY_OFS              (24)                            /* !< KEY Offset */
#define SYSCTL_SYSOSCFCLCTL_KEY_MASK             ((uint32_t)0xFF000000U)         /* !< The key value of 2Ah (42) must be
                                                                                    written to KEY together with
                                                                                    SETUSEFCL to enable the FCL. */
#define SYSCTL_SYSOSCFCLCTL_KEY_VALUE            ((uint32_t)0x2A000000U)         /* !< Issue Command */
/* SYSCTL_SYSOSCFCLCTL[SETUSEFCL] Bits */
#define SYSCTL_SYSOSCFCLCTL_SETUSEFCL_OFS        (0)                             /* !< SETUSEFCL Offset */
#define SYSCTL_SYSOSCFCLCTL_SETUSEFCL_MASK       ((uint32_t)0x00000001U)         /* !< Set SETUSEFCL to enable the
                                                                                    frequency correction loop in SYSOSC.
                                                                                    Once enabled, this state is locked
                                                                                    until the next BOOTRST. */
#define SYSCTL_SYSOSCFCLCTL_SETUSEFCL_TRUE       ((uint32_t)0x00000001U)         /* !< Enable the SYSOSC FCL */

/* SYSCTL_SHDNIOREL Bits */
/* SYSCTL_SHDNIOREL[KEY] Bits */
#define SYSCTL_SHDNIOREL_KEY_OFS                 (24)                            /* !< KEY Offset */
#define SYSCTL_SHDNIOREL_KEY_MASK                ((uint32_t)0xFF000000U)         /* !< The key value 91h must be written
                                                                                    to KEY together with RELEASE to set
                                                                                    RELEASE. */
#define SYSCTL_SHDNIOREL_KEY_VALUE               ((uint32_t)0x91000000U)         /* !< Issue command */
/* SYSCTL_SHDNIOREL[RELEASE] Bits */
#define SYSCTL_SHDNIOREL_RELEASE_OFS             (0)                             /* !< RELEASE Offset */
#define SYSCTL_SHDNIOREL_RELEASE_MASK            ((uint32_t)0x00000001U)         /* !< Set RELEASE to release the IO after
                                                                                    a SHUTDOWN mode exit. */
#define SYSCTL_SHDNIOREL_RELEASE_TRUE            ((uint32_t)0x00000001U)         /* !< Release IO */

/* SYSCTL_EXRSTPIN Bits */
/* SYSCTL_EXRSTPIN[KEY] Bits */
#define SYSCTL_EXRSTPIN_KEY_OFS                  (24)                            /* !< KEY Offset */
#define SYSCTL_EXRSTPIN_KEY_MASK                 ((uint32_t)0xFF000000U)         /* !< The key value 1Eh must be written
                                                                                    together with DISABLE to disable the
                                                                                    reset function. */
#define SYSCTL_EXRSTPIN_KEY_VALUE                ((uint32_t)0x1E000000U)         /* !< Issue command */
/* SYSCTL_EXRSTPIN[DISABLE] Bits */
#define SYSCTL_EXRSTPIN_DISABLE_OFS              (0)                             /* !< DISABLE Offset */
#define SYSCTL_EXRSTPIN_DISABLE_MASK             ((uint32_t)0x00000001U)         /* !< Set DISABLE to disable the reset
                                                                                    function of the NRST pin.  Once set,
                                                                                    this configuration is locked until
                                                                                    the next POR. */
#define SYSCTL_EXRSTPIN_DISABLE_FALSE            ((uint32_t)0x00000000U)         /* !< Reset function of NRST pin is
                                                                                    enabled */
#define SYSCTL_EXRSTPIN_DISABLE_TRUE             ((uint32_t)0x00000001U)         /* !< Reset function of NRST pin is
                                                                                    disabled */

/* SYSCTL_SYSSTATUSCLR Bits */
/* SYSCTL_SYSSTATUSCLR[KEY] Bits */
#define SYSCTL_SYSSTATUSCLR_KEY_OFS              (24)                            /* !< KEY Offset */
#define SYSCTL_SYSSTATUSCLR_KEY_MASK             ((uint32_t)0xFF000000U)         /* !< The key value CEh (206) must be
                                                                                    written to KEY together with ALLECC
                                                                                    to clear the ECC state. */
#define SYSCTL_SYSSTATUSCLR_KEY_VALUE            ((uint32_t)0xCE000000U)         /* !< Issue command */
/* SYSCTL_SYSSTATUSCLR[ALLECC] Bits */
#define SYSCTL_SYSSTATUSCLR_ALLECC_OFS           (0)                             /* !< ALLECC Offset */
#define SYSCTL_SYSSTATUSCLR_ALLECC_MASK          ((uint32_t)0x00000001U)         /* !< Set ALLECC to clear all ECC related
                                                                                    SYSSTATUS indicators. */
#define SYSCTL_SYSSTATUSCLR_ALLECC_CLEAR         ((uint32_t)0x00000001U)         /* !< Clear ECC error state */

/* SYSCTL_SWDJCFG Bits */
/* SYSCTL_SWDJCFG[KEY] Bits */
#define SYSCTL_SWDJCFG_KEY_OFS                   (24)                            /* !< KEY Offset */
#define SYSCTL_SWDJCFG_KEY_MASK                  ((uint32_t)0xFF000000U)         /* !< The key value 62h (98) must be
                                                                                    written to KEY together with DISBALE
                                                                                    to disable the SWD/JTAG functions. */
#define SYSCTL_SWDJCFG_KEY_VALUE                 ((uint32_t)0x62000000U)         /* !< Issue command */
/* SYSCTL_SWDJCFG[DISABLE] Bits */
#define SYSCTL_SWDJCFG_DISABLE_OFS               (0)                             /* !< DISABLE Offset */
#define SYSCTL_SWDJCFG_DISABLE_MASK              ((uint32_t)0x00000001U)         /* !< Set DISABLE to disable the SWD/JTAG
                                                                                    function on SWD/JTAG pins, allowing
                                                                                    the SWD/JTAG pins to be used as GPIO. */
#define SYSCTL_SWDJCFG_DISABLE_TRUE              ((uint32_t)0x00000001U)         /* !< Disable SWD/JTAG function on
                                                                                    SWD/JTAG pins */

/* SYSCTL_FCCCMD Bits */
/* SYSCTL_FCCCMD[KEY] Bits */
#define SYSCTL_FCCCMD_KEY_OFS                    (24)                            /* !< KEY Offset */
#define SYSCTL_FCCCMD_KEY_MASK                   ((uint32_t)0xFF000000U)         /* !< The key value 0Eh (14) must be
                                                                                    written with GO to start a capture. */
#define SYSCTL_FCCCMD_KEY_VALUE                  ((uint32_t)0x0E000000U)         /* !< Issue command */
/* SYSCTL_FCCCMD[GO] Bits */
#define SYSCTL_FCCCMD_GO_OFS                     (0)                             /* !< GO Offset */
#define SYSCTL_FCCCMD_GO_MASK                    ((uint32_t)0x00000001U)         /* !< Set GO to start a capture with the
                                                                                    frequency clock counter (FCC). */
#define SYSCTL_FCCCMD_GO_TRUE                    ((uint32_t)0x00000001U)

/* SYSCTL_SHUTDNSTORE0 Bits */
/* SYSCTL_SHUTDNSTORE0[DATA] Bits */
#define SYSCTL_SHUTDNSTORE0_DATA_OFS             (0)                             /* !< DATA Offset */
#define SYSCTL_SHUTDNSTORE0_DATA_MASK            ((uint32_t)0x000000FFU)         /* !< Shutdown storage byte 0 */

/* SYSCTL_SHUTDNSTORE1 Bits */
/* SYSCTL_SHUTDNSTORE1[DATA] Bits */
#define SYSCTL_SHUTDNSTORE1_DATA_OFS             (0)                             /* !< DATA Offset */
#define SYSCTL_SHUTDNSTORE1_DATA_MASK            ((uint32_t)0x000000FFU)         /* !< Shutdown storage byte 1 */

/* SYSCTL_SHUTDNSTORE2 Bits */
/* SYSCTL_SHUTDNSTORE2[DATA] Bits */
#define SYSCTL_SHUTDNSTORE2_DATA_OFS             (0)                             /* !< DATA Offset */
#define SYSCTL_SHUTDNSTORE2_DATA_MASK            ((uint32_t)0x000000FFU)         /* !< Shutdown storage byte 2 */

/* SYSCTL_SHUTDNSTORE3 Bits */
/* SYSCTL_SHUTDNSTORE3[DATA] Bits */
#define SYSCTL_SHUTDNSTORE3_DATA_OFS             (0)                             /* !< DATA Offset */
#define SYSCTL_SHUTDNSTORE3_DATA_MASK            ((uint32_t)0x000000FFU)         /* !< Shutdown storage byte 3 */

/* SYSCTL_ADCSEQFRCGB Bits */
/* SYSCTL_ADCSEQFRCGB[SEQ3] Bits */
#define SYSCTL_ADCSEQFRCGB_SEQ3_OFS              (3)                             /* !< SEQ3 Offset */
#define SYSCTL_ADCSEQFRCGB_SEQ3_MASK             ((uint32_t)0x00000008U)         /* !< Generate synchronous SW trigger for
                                                                                    SEQ3 */
/* SYSCTL_ADCSEQFRCGB[SEQ2] Bits */
#define SYSCTL_ADCSEQFRCGB_SEQ2_OFS              (2)                             /* !< SEQ2 Offset */
#define SYSCTL_ADCSEQFRCGB_SEQ2_MASK             ((uint32_t)0x00000004U)         /* !< Generate synchronous SW trigger for
                                                                                    SEQ2 */
/* SYSCTL_ADCSEQFRCGB[SEQ0] Bits */
#define SYSCTL_ADCSEQFRCGB_SEQ0_OFS              (0)                             /* !< SEQ0 Offset */
#define SYSCTL_ADCSEQFRCGB_SEQ0_MASK             ((uint32_t)0x00000001U)         /* !< Generate synchronous SW trigger for
                                                                                    SEQ0 */
/* SYSCTL_ADCSEQFRCGB[SEQ1] Bits */
#define SYSCTL_ADCSEQFRCGB_SEQ1_OFS              (1)                             /* !< SEQ1 Offset */
#define SYSCTL_ADCSEQFRCGB_SEQ1_MASK             ((uint32_t)0x00000002U)         /* !< Generate synchronous SW trigger for
                                                                                    SEQ1 */

/* SYSCTL_ADCSEQFRCGBSEL Bits */
/* SYSCTL_ADCSEQFRCGBSEL[ADCB] Bits */
#define SYSCTL_ADCSEQFRCGBSEL_ADCB_OFS           (1)                             /* !< ADCB Offset */
#define SYSCTL_ADCSEQFRCGBSEL_ADCB_MASK          ((uint32_t)0x00000002U)         /* !< Generate synchronous SW trigger for
                                                                                    ADCB */
/* SYSCTL_ADCSEQFRCGBSEL[ADCC] Bits */
#define SYSCTL_ADCSEQFRCGBSEL_ADCC_OFS           (2)                             /* !< ADCC Offset */
#define SYSCTL_ADCSEQFRCGBSEL_ADCC_MASK          ((uint32_t)0x00000004U)         /* !< Generate synchronous SW trigger for
                                                                                    ADCC */
/* SYSCTL_ADCSEQFRCGBSEL[ADCA] Bits */
#define SYSCTL_ADCSEQFRCGBSEL_ADCA_OFS           (0)                             /* !< ADCA Offset */
#define SYSCTL_ADCSEQFRCGBSEL_ADCA_MASK          ((uint32_t)0x00000001U)         /* !< Generate synchronous SW trigger for
                                                                                    ADCA */

/* SYSCTL_M33SPARESOCLOCK1 Bits */
/* SYSCTL_M33SPARESOCLOCK1[SPARE] Bits */
#define SYSCTL_M33SPARESOCLOCK1_SPARE_OFS        (0)                             /* !< SPARE Offset */
#define SYSCTL_M33SPARESOCLOCK1_SPARE_MASK       ((uint32_t)0xFFFFFFFFU)         /* !< Spare SOC LOCK Register 1 */

/* SYSCTL_M33SPARESOCLOCK2 Bits */
/* SYSCTL_M33SPARESOCLOCK2[SPARE] Bits */
#define SYSCTL_M33SPARESOCLOCK2_SPARE_OFS        (0)                             /* !< SPARE Offset */
#define SYSCTL_M33SPARESOCLOCK2_SPARE_MASK       ((uint32_t)0xFFFFFFFFU)         /* !< Spare SOC LOCK Register 2 */

/* SYSCTL_SYSCTL_READ_REG Bits */
/* SYSCTL_SYSCTL_READ_REG[ECOREG] Bits */
#define SYSCTL_SYSCTL_READ_REG_ECOREG_OFS        (0)                             /* !< ECOREG Offset */
#define SYSCTL_SYSCTL_READ_REG_ECOREG_MASK       ((uint32_t)0xFFFFFFFFU)         /* !< Read only register */

/* SYSCTL_PWREN_MCPERIPH Bits */
/* SYSCTL_PWREN_MCPERIPH[KEY] Bits */
#define SYSCTL_PWREN_MCPERIPH_KEY_OFS            (24)                            /* !< KEY Offset */
#define SYSCTL_PWREN_MCPERIPH_KEY_MASK           ((uint32_t)0xFF000000U)         /* !< KEY to Allow Enable State Change --
                                                                                    0x26 */
#define SYSCTL_PWREN_MCPERIPH_KEY_UNLOCK         ((uint32_t)0x26000000U)
/* SYSCTL_PWREN_MCPERIPH[EQEP0] Bits */
#define SYSCTL_PWREN_MCPERIPH_EQEP0_OFS          (0)                             /* !< EQEP0 Offset */
#define SYSCTL_PWREN_MCPERIPH_EQEP0_MASK         ((uint32_t)0x00000001U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_EQEP0_DISABLE      ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_EQEP0_ENABLE       ((uint32_t)0x00000001U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[EQEP1] Bits */
#define SYSCTL_PWREN_MCPERIPH_EQEP1_OFS          (1)                             /* !< EQEP1 Offset */
#define SYSCTL_PWREN_MCPERIPH_EQEP1_MASK         ((uint32_t)0x00000002U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_EQEP1_DISABLE      ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_EQEP1_ENABLE       ((uint32_t)0x00000002U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[EQEP2] Bits */
#define SYSCTL_PWREN_MCPERIPH_EQEP2_OFS          (2)                             /* !< EQEP2 Offset */
#define SYSCTL_PWREN_MCPERIPH_EQEP2_MASK         ((uint32_t)0x00000004U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_EQEP2_DISABLE      ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_EQEP2_ENABLE       ((uint32_t)0x00000004U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[ECAP0] Bits */
#define SYSCTL_PWREN_MCPERIPH_ECAP0_OFS          (3)                             /* !< ECAP0 Offset */
#define SYSCTL_PWREN_MCPERIPH_ECAP0_MASK         ((uint32_t)0x00000008U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_ECAP0_DISABLE      ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_ECAP0_ENABLE       ((uint32_t)0x00000008U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[ECAP1] Bits */
#define SYSCTL_PWREN_MCPERIPH_ECAP1_OFS          (4)                             /* !< ECAP1 Offset */
#define SYSCTL_PWREN_MCPERIPH_ECAP1_MASK         ((uint32_t)0x00000010U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_ECAP1_DISABLE      ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_ECAP1_ENABLE       ((uint32_t)0x00000010U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[PWM0] Bits */
#define SYSCTL_PWREN_MCPERIPH_PWM0_OFS           (5)                             /* !< PWM0 Offset */
#define SYSCTL_PWREN_MCPERIPH_PWM0_MASK          ((uint32_t)0x00000020U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_PWM0_DISABLE       ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_PWM0_ENABLE        ((uint32_t)0x00000020U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[PWM1] Bits */
#define SYSCTL_PWREN_MCPERIPH_PWM1_OFS           (6)                             /* !< PWM1 Offset */
#define SYSCTL_PWREN_MCPERIPH_PWM1_MASK          ((uint32_t)0x00000040U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_PWM1_DISABLE       ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_PWM1_ENABLE        ((uint32_t)0x00000040U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[PWM2] Bits */
#define SYSCTL_PWREN_MCPERIPH_PWM2_OFS           (7)                             /* !< PWM2 Offset */
#define SYSCTL_PWREN_MCPERIPH_PWM2_MASK          ((uint32_t)0x00000080U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_PWM2_DISABLE       ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_PWM2_ENABLE        ((uint32_t)0x00000080U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[PWM3] Bits */
#define SYSCTL_PWREN_MCPERIPH_PWM3_OFS           (8)                             /* !< PWM3 Offset */
#define SYSCTL_PWREN_MCPERIPH_PWM3_MASK          ((uint32_t)0x00000100U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_PWM3_DISABLE       ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_PWM3_ENABLE        ((uint32_t)0x00000100U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[PWM4] Bits */
#define SYSCTL_PWREN_MCPERIPH_PWM4_OFS           (9)                             /* !< PWM4 Offset */
#define SYSCTL_PWREN_MCPERIPH_PWM4_MASK          ((uint32_t)0x00000200U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_PWM4_DISABLE       ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_PWM4_ENABLE        ((uint32_t)0x00000200U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[CMPSS0] Bits */
#define SYSCTL_PWREN_MCPERIPH_CMPSS0_OFS         (10)                            /* !< CMPSS0 Offset */
#define SYSCTL_PWREN_MCPERIPH_CMPSS0_MASK        ((uint32_t)0x00000400U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_CMPSS0_DISABLE     ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_CMPSS0_ENABLE      ((uint32_t)0x00000400U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[CMPSS1] Bits */
#define SYSCTL_PWREN_MCPERIPH_CMPSS1_OFS         (11)                            /* !< CMPSS1 Offset */
#define SYSCTL_PWREN_MCPERIPH_CMPSS1_MASK        ((uint32_t)0x00000800U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_CMPSS1_DISABLE     ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_CMPSS1_ENABLE      ((uint32_t)0x00000800U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[CMPSS2] Bits */
#define SYSCTL_PWREN_MCPERIPH_CMPSS2_OFS         (12)                            /* !< CMPSS2 Offset */
#define SYSCTL_PWREN_MCPERIPH_CMPSS2_MASK        ((uint32_t)0x00001000U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_CMPSS2_DISABLE     ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_CMPSS2_ENABLE      ((uint32_t)0x00001000U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[CMPSS3] Bits */
#define SYSCTL_PWREN_MCPERIPH_CMPSS3_OFS         (13)                            /* !< CMPSS3 Offset */
#define SYSCTL_PWREN_MCPERIPH_CMPSS3_MASK        ((uint32_t)0x00002000U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_CMPSS3_DISABLE     ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_CMPSS3_ENABLE      ((uint32_t)0x00002000U)         /* !< Enable Power */
/* SYSCTL_PWREN_MCPERIPH[XBAR] Bits */
#define SYSCTL_PWREN_MCPERIPH_XBAR_OFS           (14)                            /* !< XBAR Offset */
#define SYSCTL_PWREN_MCPERIPH_XBAR_MASK          ((uint32_t)0x00004000U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_MCPERIPH_XBAR_DISABLE       ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_MCPERIPH_XBAR_ENABLE        ((uint32_t)0x00004000U)         /* !< Enable Power */

/* SYSCTL_RSTCTL_ASSERT_MCPERIPH Bits */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[KEY] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_KEY_OFS    (24)                            /* !< KEY Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_KEY_MASK   ((uint32_t)0xFF000000U)         /* !< KEY to Allow Enable State Change --
                                                                                    0xb1 */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_KEY_UNLOCK ((uint32_t)0xB1000000U)
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_EQEP0] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_EQEP0_OFS (0)                             /* !< RESETASSERT_EQEP0 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_EQEP0_MASK ((uint32_t)0x00000001U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_EQEP0_ASSERT ((uint32_t)0x00000001U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_EQEP1] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_EQEP1_OFS (1)                             /* !< RESETASSERT_EQEP1 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_EQEP1_MASK ((uint32_t)0x00000002U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_EQEP1_ASSERT ((uint32_t)0x00000002U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_EQEP2] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_EQEP2_OFS (2)                             /* !< RESETASSERT_EQEP2 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_EQEP2_MASK ((uint32_t)0x00000004U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_EQEP2_ASSERT ((uint32_t)0x00000004U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_ECAP0] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_ECAP0_OFS (3)                             /* !< RESETASSERT_ECAP0 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_ECAP0_MASK ((uint32_t)0x00000008U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_ECAP0_ASSERT ((uint32_t)0x00000008U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_ECAP1] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_ECAP1_OFS (4)                             /* !< RESETASSERT_ECAP1 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_ECAP1_MASK ((uint32_t)0x00000010U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_ECAP1_ASSERT ((uint32_t)0x00000010U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_PWM0] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM0_OFS (5)                             /* !< RESETASSERT_PWM0 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM0_MASK ((uint32_t)0x00000020U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM0_ASSERT ((uint32_t)0x00000020U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_PWM1] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM1_OFS (6)                             /* !< RESETASSERT_PWM1 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM1_MASK ((uint32_t)0x00000040U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM1_ASSERT ((uint32_t)0x00000040U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_PWM2] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM2_OFS (7)                             /* !< RESETASSERT_PWM2 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM2_MASK ((uint32_t)0x00000080U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM2_ASSERT ((uint32_t)0x00000080U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_PWM3] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM3_OFS (8)                             /* !< RESETASSERT_PWM3 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM3_MASK ((uint32_t)0x00000100U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM3_ASSERT ((uint32_t)0x00000100U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_PWM4] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM4_OFS (9)                             /* !< RESETASSERT_PWM4 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM4_MASK ((uint32_t)0x00000200U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_PWM4_ASSERT ((uint32_t)0x00000200U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_CMPSS0] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_CMPSS0_OFS (10)                            /* !< RESETASSERT_CMPSS0 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_CMPSS0_MASK ((uint32_t)0x00000400U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_CMPSS0_ASSERT ((uint32_t)0x00000400U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_CMPSS1] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_CMPSS1_OFS (11)                            /* !< RESETASSERT_CMPSS1 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_CMPSS1_MASK ((uint32_t)0x00000800U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_CMPSS1_ASSERT ((uint32_t)0x00000800U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_CMPSS2] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_CMPSS2_OFS (12)                            /* !< RESETASSERT_CMPSS2 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_CMPSS2_MASK ((uint32_t)0x00001000U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_CMPSS2_ASSERT ((uint32_t)0x00001000U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_CMPSS3] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_CMPSS3_OFS (13)                            /* !< RESETASSERT_CMPSS3 Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_CMPSS3_MASK ((uint32_t)0x00002000U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_CMPSS3_ASSERT ((uint32_t)0x00002000U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_MCPERIPH[RESETASSERT_XBAR] Bits */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_XBAR_OFS (14)                            /* !< RESETASSERT_XBAR Offset */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_XBAR_MASK ((uint32_t)0x00004000U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_MCPERIPH_RESETASSERT_XBAR_ASSERT ((uint32_t)0x00004000U)         /* !< Assert reset */

/* SYSCTL_RSTCTL_CLEAR_MCPERIPH Bits */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[KEY] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_KEY_OFS     (24)                            /* !< KEY Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_KEY_MASK    ((uint32_t)0xFF000000U)         /* !< KEY to Allow Enable State Change --
                                                                                    0xb1 */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_KEY_UNLOCK  ((uint32_t)0xB1000000U)
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_EQEP0] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_EQEP0_OFS (0)                             /* !< RESETSTKYCLR_EQEP0 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_EQEP0_MASK ((uint32_t)0x00000001U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_EQEP0_CLEAR ((uint32_t)0x00000001U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_EQEP1] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_EQEP1_OFS (1)                             /* !< RESETSTKYCLR_EQEP1 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_EQEP1_MASK ((uint32_t)0x00000002U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_EQEP1_CLEAR ((uint32_t)0x00000002U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_EQEP2] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_EQEP2_OFS (2)                             /* !< RESETSTKYCLR_EQEP2 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_EQEP2_MASK ((uint32_t)0x00000004U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_EQEP2_CLEAR ((uint32_t)0x00000004U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_ECAP0] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_ECAP0_OFS (3)                             /* !< RESETSTKYCLR_ECAP0 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_ECAP0_MASK ((uint32_t)0x00000008U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_ECAP0_CLEAR ((uint32_t)0x00000008U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_ECAP1] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_ECAP1_OFS (4)                             /* !< RESETSTKYCLR_ECAP1 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_ECAP1_MASK ((uint32_t)0x00000010U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_ECAP1_CLEAR ((uint32_t)0x00000010U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_PWM0] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM0_OFS (5)                             /* !< RESETSTKYCLR_PWM0 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM0_MASK ((uint32_t)0x00000020U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM0_CLEAR ((uint32_t)0x00000020U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_PWM1] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM1_OFS (6)                             /* !< RESETSTKYCLR_PWM1 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM1_MASK ((uint32_t)0x00000040U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM1_CLEAR ((uint32_t)0x00000040U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_PWM2] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM2_OFS (7)                             /* !< RESETSTKYCLR_PWM2 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM2_MASK ((uint32_t)0x00000080U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM2_CLEAR ((uint32_t)0x00000080U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_PWM3] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM3_OFS (8)                             /* !< RESETSTKYCLR_PWM3 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM3_MASK ((uint32_t)0x00000100U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM3_CLEAR ((uint32_t)0x00000100U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_PWM4] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM4_OFS (9)                             /* !< RESETSTKYCLR_PWM4 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM4_MASK ((uint32_t)0x00000200U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_PWM4_CLEAR ((uint32_t)0x00000200U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_CMPSS0] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_CMPSS0_OFS (10)                            /* !< RESETSTKYCLR_CMPSS0 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_CMPSS0_MASK ((uint32_t)0x00000400U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_CMPSS0_CLEAR ((uint32_t)0x00000400U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_CMPSS1] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_CMPSS1_OFS (11)                            /* !< RESETSTKYCLR_CMPSS1 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_CMPSS1_MASK ((uint32_t)0x00000800U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_CMPSS1_CLEAR ((uint32_t)0x00000800U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_CMPSS2] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_CMPSS2_OFS (12)                            /* !< RESETSTKYCLR_CMPSS2 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_CMPSS2_MASK ((uint32_t)0x00001000U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_CMPSS2_CLEAR ((uint32_t)0x00001000U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_CMPSS3] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_CMPSS3_OFS (13)                            /* !< RESETSTKYCLR_CMPSS3 Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_CMPSS3_MASK ((uint32_t)0x00002000U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_CMPSS3_CLEAR ((uint32_t)0x00002000U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_MCPERIPH[RESETSTKYCLR_XBAR] Bits */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_XBAR_OFS (14)                            /* !< RESETSTKYCLR_XBAR Offset */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_XBAR_MASK ((uint32_t)0x00004000U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_MCPERIPH_RESETSTKYCLR_XBAR_CLEAR ((uint32_t)0x00004000U)         /* !< Clear reset sticky bit */

/* SYSCTL_STAT_MCPERIPH Bits */
/* SYSCTL_STAT_MCPERIPH[EQEP0] Bits */
#define SYSCTL_STAT_MCPERIPH_EQEP0_OFS           (0)                             /* !< EQEP0 Offset */
#define SYSCTL_STAT_MCPERIPH_EQEP0_MASK          ((uint32_t)0x00000001U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_EQEP0_CLR           ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_EQEP0_RESET         ((uint32_t)0x00000001U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[EQEP1] Bits */
#define SYSCTL_STAT_MCPERIPH_EQEP1_OFS           (1)                             /* !< EQEP1 Offset */
#define SYSCTL_STAT_MCPERIPH_EQEP1_MASK          ((uint32_t)0x00000002U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_EQEP1_CLR           ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_EQEP1_RESET         ((uint32_t)0x00000002U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[EQEP2] Bits */
#define SYSCTL_STAT_MCPERIPH_EQEP2_OFS           (2)                             /* !< EQEP2 Offset */
#define SYSCTL_STAT_MCPERIPH_EQEP2_MASK          ((uint32_t)0x00000004U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_EQEP2_CLR           ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_EQEP2_RESET         ((uint32_t)0x00000004U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[ECAP0] Bits */
#define SYSCTL_STAT_MCPERIPH_ECAP0_OFS           (3)                             /* !< ECAP0 Offset */
#define SYSCTL_STAT_MCPERIPH_ECAP0_MASK          ((uint32_t)0x00000008U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_ECAP0_CLR           ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_ECAP0_RESET         ((uint32_t)0x00000008U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[ECAP1] Bits */
#define SYSCTL_STAT_MCPERIPH_ECAP1_OFS           (4)                             /* !< ECAP1 Offset */
#define SYSCTL_STAT_MCPERIPH_ECAP1_MASK          ((uint32_t)0x00000010U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_ECAP1_CLR           ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_ECAP1_RESET         ((uint32_t)0x00000010U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[PWM0] Bits */
#define SYSCTL_STAT_MCPERIPH_PWM0_OFS            (5)                             /* !< PWM0 Offset */
#define SYSCTL_STAT_MCPERIPH_PWM0_MASK           ((uint32_t)0x00000020U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_PWM0_CLR            ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_PWM0_RESET          ((uint32_t)0x00000020U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[PWM1] Bits */
#define SYSCTL_STAT_MCPERIPH_PWM1_OFS            (6)                             /* !< PWM1 Offset */
#define SYSCTL_STAT_MCPERIPH_PWM1_MASK           ((uint32_t)0x00000040U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_PWM1_CLR            ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_PWM1_RESET          ((uint32_t)0x00000040U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[PWM2] Bits */
#define SYSCTL_STAT_MCPERIPH_PWM2_OFS            (7)                             /* !< PWM2 Offset */
#define SYSCTL_STAT_MCPERIPH_PWM2_MASK           ((uint32_t)0x00000080U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_PWM2_CLR            ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_PWM2_RESET          ((uint32_t)0x00000080U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[PWM3] Bits */
#define SYSCTL_STAT_MCPERIPH_PWM3_OFS            (8)                             /* !< PWM3 Offset */
#define SYSCTL_STAT_MCPERIPH_PWM3_MASK           ((uint32_t)0x00000100U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_PWM3_CLR            ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_PWM3_RESET          ((uint32_t)0x00000100U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[PWM4] Bits */
#define SYSCTL_STAT_MCPERIPH_PWM4_OFS            (9)                             /* !< PWM4 Offset */
#define SYSCTL_STAT_MCPERIPH_PWM4_MASK           ((uint32_t)0x00000200U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_PWM4_CLR            ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_PWM4_RESET          ((uint32_t)0x00000200U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[CMPSS0] Bits */
#define SYSCTL_STAT_MCPERIPH_CMPSS0_OFS          (10)                            /* !< CMPSS0 Offset */
#define SYSCTL_STAT_MCPERIPH_CMPSS0_MASK         ((uint32_t)0x00000400U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_CMPSS0_CLR          ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_CMPSS0_RESET        ((uint32_t)0x00000400U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[CMPSS1] Bits */
#define SYSCTL_STAT_MCPERIPH_CMPSS1_OFS          (11)                            /* !< CMPSS1 Offset */
#define SYSCTL_STAT_MCPERIPH_CMPSS1_MASK         ((uint32_t)0x00000800U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_CMPSS1_CLR          ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_CMPSS1_RESET        ((uint32_t)0x00000800U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[CMPSS2] Bits */
#define SYSCTL_STAT_MCPERIPH_CMPSS2_OFS          (12)                            /* !< CMPSS2 Offset */
#define SYSCTL_STAT_MCPERIPH_CMPSS2_MASK         ((uint32_t)0x00001000U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_CMPSS2_CLR          ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_CMPSS2_RESET        ((uint32_t)0x00001000U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[CMPSS3] Bits */
#define SYSCTL_STAT_MCPERIPH_CMPSS3_OFS          (13)                            /* !< CMPSS3 Offset */
#define SYSCTL_STAT_MCPERIPH_CMPSS3_MASK         ((uint32_t)0x00002000U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_CMPSS3_CLR          ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_CMPSS3_RESET        ((uint32_t)0x00002000U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_MCPERIPH[XBAR] Bits */
#define SYSCTL_STAT_MCPERIPH_XBAR_OFS            (14)                            /* !< XBAR Offset */
#define SYSCTL_STAT_MCPERIPH_XBAR_MASK           ((uint32_t)0x00004000U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_XBAR_CLR            ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_MCPERIPH_XBAR_RESET          ((uint32_t)0x00004000U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */

/* SYSCTL_PWREN_SYSPERIPH Bits */
/* SYSCTL_PWREN_SYSPERIPH[KEY] Bits */
#define SYSCTL_PWREN_SYSPERIPH_KEY_OFS           (24)                            /* !< KEY Offset */
#define SYSCTL_PWREN_SYSPERIPH_KEY_MASK          ((uint32_t)0xFF000000U)         /* !< KEY to Allow Enable State Change --
                                                                                    0x26 */
#define SYSCTL_PWREN_SYSPERIPH_KEY_UNLOCK        ((uint32_t)0x26000000U)
/* SYSCTL_PWREN_SYSPERIPH[TINIE] Bits */
#define SYSCTL_PWREN_SYSPERIPH_TINIE_OFS         (0)                             /* !< TINIE Offset */
#define SYSCTL_PWREN_SYSPERIPH_TINIE_MASK        ((uint32_t)0x00000001U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_SYSPERIPH_TINIE_DISABLE     ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_SYSPERIPH_TINIE_ENABLE      ((uint32_t)0x00000001U)         /* !< Enable Power */
/* SYSCTL_PWREN_SYSPERIPH[PGA0] Bits */
#define SYSCTL_PWREN_SYSPERIPH_PGA0_OFS          (1)                             /* !< PGA0 Offset */
#define SYSCTL_PWREN_SYSPERIPH_PGA0_MASK         ((uint32_t)0x00000002U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_SYSPERIPH_PGA0_DISABLE      ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_SYSPERIPH_PGA0_ENABLE       ((uint32_t)0x00000002U)         /* !< Enable Power */
/* SYSCTL_PWREN_SYSPERIPH[PGA1] Bits */
#define SYSCTL_PWREN_SYSPERIPH_PGA1_OFS          (2)                             /* !< PGA1 Offset */
#define SYSCTL_PWREN_SYSPERIPH_PGA1_MASK         ((uint32_t)0x00000004U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_SYSPERIPH_PGA1_DISABLE      ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_SYSPERIPH_PGA1_ENABLE       ((uint32_t)0x00000004U)         /* !< Enable Power */
/* SYSCTL_PWREN_SYSPERIPH[PGA2] Bits */
#define SYSCTL_PWREN_SYSPERIPH_PGA2_OFS          (3)                             /* !< PGA2 Offset */
#define SYSCTL_PWREN_SYSPERIPH_PGA2_MASK         ((uint32_t)0x00000008U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_SYSPERIPH_PGA2_DISABLE      ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_SYSPERIPH_PGA2_ENABLE       ((uint32_t)0x00000008U)         /* !< Enable Power */
/* SYSCTL_PWREN_SYSPERIPH[EPI] Bits */
#define SYSCTL_PWREN_SYSPERIPH_EPI_OFS           (4)                             /* !< EPI Offset */
#define SYSCTL_PWREN_SYSPERIPH_EPI_MASK          ((uint32_t)0x00000010U)         /* !< Enable the power to IP, KEY must be
                                                                                    set to 26h to write to this bit */
#define SYSCTL_PWREN_SYSPERIPH_EPI_DISABLE       ((uint32_t)0x00000000U)         /* !< Disable Power */
#define SYSCTL_PWREN_SYSPERIPH_EPI_ENABLE        ((uint32_t)0x00000010U)         /* !< Enable Power */

/* SYSCTL_RSTCTL_ASSERT_SYSPERIPH Bits */
/* SYSCTL_RSTCTL_ASSERT_SYSPERIPH[KEY] Bits */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_KEY_OFS   (24)                            /* !< KEY Offset */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_KEY_MASK  ((uint32_t)0xFF000000U)         /* !< KEY to Allow Enable State Change --
                                                                                    0xb1 */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_KEY_UNLOCK ((uint32_t)0xB1000000U)
/* SYSCTL_RSTCTL_ASSERT_SYSPERIPH[RESETASSERT_TINIE] Bits */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_TINIE_OFS (0)                             /* !< RESETASSERT_TINIE Offset */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_TINIE_MASK ((uint32_t)0x00000001U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_TINIE_ASSERT ((uint32_t)0x00000001U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_SYSPERIPH[RESETASSERT_PGA0] Bits */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_PGA0_OFS (1)                             /* !< RESETASSERT_PGA0 Offset */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_PGA0_MASK ((uint32_t)0x00000002U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_PGA0_ASSERT ((uint32_t)0x00000002U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_SYSPERIPH[RESETASSERT_PGA1] Bits */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_PGA1_OFS (2)                             /* !< RESETASSERT_PGA1 Offset */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_PGA1_MASK ((uint32_t)0x00000004U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_PGA1_ASSERT ((uint32_t)0x00000004U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_SYSPERIPH[RESETASSERT_PGA2] Bits */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_PGA2_OFS (3)                             /* !< RESETASSERT_PGA2 Offset */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_PGA2_MASK ((uint32_t)0x00000008U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_PGA2_ASSERT ((uint32_t)0x00000008U)         /* !< Assert reset */
/* SYSCTL_RSTCTL_ASSERT_SYSPERIPH[RESETASSERT_EPI] Bits */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_EPI_OFS (4)                             /* !< RESETASSERT_EPI Offset */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_EPI_MASK ((uint32_t)0x00000010U)         /* !< assert reset to the peripheral, KEY
                                                                                    must be set to B1h to write to this
                                                                                    bit */
#define SYSCTL_RSTCTL_ASSERT_SYSPERIPH_RESETASSERT_EPI_ASSERT ((uint32_t)0x00000010U)         /* !< Assert reset */

/* SYSCTL_RSTCTL_CLEAR_SYSPERIPH Bits */
/* SYSCTL_RSTCTL_CLEAR_SYSPERIPH[KEY] Bits */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_KEY_OFS    (24)                            /* !< KEY Offset */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_KEY_MASK   ((uint32_t)0xFF000000U)         /* !< KEY to Allow Enable State Change --
                                                                                    0xb1 */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_KEY_UNLOCK ((uint32_t)0xB1000000U)
/* SYSCTL_RSTCTL_CLEAR_SYSPERIPH[RESETSTKYCLR_TINIE] Bits */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_TINIE_OFS (0)                             /* !< RESETSTKYCLR_TINIE Offset */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_TINIE_MASK ((uint32_t)0x00000001U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_TINIE_CLEAR ((uint32_t)0x00000001U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_SYSPERIPH[RESETSTKYCLR_PGA0] Bits */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_PGA0_OFS (1)                             /* !< RESETSTKYCLR_PGA0 Offset */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_PGA0_MASK ((uint32_t)0x00000002U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_PGA0_CLEAR ((uint32_t)0x00000002U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_SYSPERIPH[RESETSTKYCLR_PGA1] Bits */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_PGA1_OFS (2)                             /* !< RESETSTKYCLR_PGA1 Offset */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_PGA1_MASK ((uint32_t)0x00000004U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_PGA1_CLEAR ((uint32_t)0x00000004U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_SYSPERIPH[RESETSTKYCLR_PGA2] Bits */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_PGA2_OFS (3)                             /* !< RESETSTKYCLR_PGA2 Offset */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_PGA2_MASK ((uint32_t)0x00000008U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_PGA2_CLEAR ((uint32_t)0x00000008U)         /* !< Clear reset sticky bit */
/* SYSCTL_RSTCTL_CLEAR_SYSPERIPH[RESETSTKYCLR_EPI] Bits */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_EPI_OFS (4)                             /* !< RESETSTKYCLR_EPI Offset */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_EPI_MASK ((uint32_t)0x00000010U)         /* !< Clear the RESETSTKY bit in the STAT
                                                                                    register, KEY must be set to B1h to
                                                                                    write to this bit */
#define SYSCTL_RSTCTL_CLEAR_SYSPERIPH_RESETSTKYCLR_EPI_CLEAR ((uint32_t)0x00000010U)         /* !< Clear reset sticky bit */

/* SYSCTL_STAT_SYSPERIPH Bits */
/* SYSCTL_STAT_SYSPERIPH[TINIE] Bits */
#define SYSCTL_STAT_SYSPERIPH_TINIE_OFS          (0)                             /* !< TINIE Offset */
#define SYSCTL_STAT_SYSPERIPH_TINIE_MASK         ((uint32_t)0x00000001U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_SYSPERIPH_TINIE_CLR          ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_SYSPERIPH_TINIE_RESET        ((uint32_t)0x00000001U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_SYSPERIPH[PGA0] Bits */
#define SYSCTL_STAT_SYSPERIPH_PGA0_OFS           (1)                             /* !< PGA0 Offset */
#define SYSCTL_STAT_SYSPERIPH_PGA0_MASK          ((uint32_t)0x00000002U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_SYSPERIPH_PGA0_CLR           ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_SYSPERIPH_PGA0_RESET         ((uint32_t)0x00000002U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_SYSPERIPH[PGA1] Bits */
#define SYSCTL_STAT_SYSPERIPH_PGA1_OFS           (2)                             /* !< PGA1 Offset */
#define SYSCTL_STAT_SYSPERIPH_PGA1_MASK          ((uint32_t)0x00000004U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_SYSPERIPH_PGA1_CLR           ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_SYSPERIPH_PGA1_RESET         ((uint32_t)0x00000004U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_SYSPERIPH[PGA2] Bits */
#define SYSCTL_STAT_SYSPERIPH_PGA2_OFS           (3)                             /* !< PGA2 Offset */
#define SYSCTL_STAT_SYSPERIPH_PGA2_MASK          ((uint32_t)0x00000008U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_SYSPERIPH_PGA2_CLR           ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_SYSPERIPH_PGA2_RESET         ((uint32_t)0x00000008U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */
/* SYSCTL_STAT_SYSPERIPH[EPI] Bits */
#define SYSCTL_STAT_SYSPERIPH_EPI_OFS            (4)                             /* !< EPI Offset */
#define SYSCTL_STAT_SYSPERIPH_EPI_MASK           ((uint32_t)0x00000010U)         /* !< This bit indicates, if the
                                                                                    peripheral was reset, since this bit
                                                                                    was cleared by RESETSTKYCLR in the
                                                                                    RSTCTL register */
#define SYSCTL_STAT_SYSPERIPH_EPI_CLR            ((uint32_t)0x00000000U)         /* !< The peripheral has not been reset
                                                                                    since this bit was last cleared by
                                                                                    RESETSTKYCLR in the RSTCTL register */
#define SYSCTL_STAT_SYSPERIPH_EPI_RESET          ((uint32_t)0x00000010U)         /* !< The peripheral was reset since the
                                                                                    last bit clear */

/* SYSCTL_CMPHPMXSEL Bits */
/* SYSCTL_CMPHPMXSEL[CMP3HPMXSEL] Bits */
#define SYSCTL_CMPHPMXSEL_CMP3HPMXSEL_OFS        (9)                             /* !< CMP3HPMXSEL Offset */
#define SYSCTL_CMPHPMXSEL_CMP3HPMXSEL_MASK       ((uint32_t)0x00000E00U)         /* !< CMP3HPMXSEL bits */
/* SYSCTL_CMPHPMXSEL[CMP1HPMXSEL] Bits */
#define SYSCTL_CMPHPMXSEL_CMP1HPMXSEL_OFS        (3)                             /* !< CMP1HPMXSEL Offset */
#define SYSCTL_CMPHPMXSEL_CMP1HPMXSEL_MASK       ((uint32_t)0x00000038U)         /* !< CMP1HPMXSEL bits */
/* SYSCTL_CMPHPMXSEL[CMP2HPMXSEL] Bits */
#define SYSCTL_CMPHPMXSEL_CMP2HPMXSEL_OFS        (6)                             /* !< CMP2HPMXSEL Offset */
#define SYSCTL_CMPHPMXSEL_CMP2HPMXSEL_MASK       ((uint32_t)0x000001C0U)         /* !< CMP2HPMXSEL bits */
/* SYSCTL_CMPHPMXSEL[CMP0HPMXSEL] Bits */
#define SYSCTL_CMPHPMXSEL_CMP0HPMXSEL_OFS        (0)                             /* !< CMP0HPMXSEL Offset */
#define SYSCTL_CMPHPMXSEL_CMP0HPMXSEL_MASK       ((uint32_t)0x00000007U)         /* !< CMP0HPMXSEL bits */

/* SYSCTL_CMPLPMXSEL Bits */
/* SYSCTL_CMPLPMXSEL[CMP0LPMXSEL] Bits */
#define SYSCTL_CMPLPMXSEL_CMP0LPMXSEL_OFS        (0)                             /* !< CMP0LPMXSEL Offset */
#define SYSCTL_CMPLPMXSEL_CMP0LPMXSEL_MASK       ((uint32_t)0x00000007U)         /* !< CMP0LPMXSEL bits */
/* SYSCTL_CMPLPMXSEL[CMP1LPMXSEL] Bits */
#define SYSCTL_CMPLPMXSEL_CMP1LPMXSEL_OFS        (3)                             /* !< CMP1LPMXSEL Offset */
#define SYSCTL_CMPLPMXSEL_CMP1LPMXSEL_MASK       ((uint32_t)0x00000038U)         /* !< CMP1LPMXSEL bits */
/* SYSCTL_CMPLPMXSEL[CMP3LPMXSEL] Bits */
#define SYSCTL_CMPLPMXSEL_CMP3LPMXSEL_OFS        (9)                             /* !< CMP3LPMXSEL Offset */
#define SYSCTL_CMPLPMXSEL_CMP3LPMXSEL_MASK       ((uint32_t)0x00000E00U)         /* !< CMP3LPMXSEL bits */
/* SYSCTL_CMPLPMXSEL[CMP2LPMXSEL] Bits */
#define SYSCTL_CMPLPMXSEL_CMP2LPMXSEL_OFS        (6)                             /* !< CMP2LPMXSEL Offset */
#define SYSCTL_CMPLPMXSEL_CMP2LPMXSEL_MASK       ((uint32_t)0x000001C0U)         /* !< CMP2LPMXSEL bits */

/* SYSCTL_CMPHNMXSEL Bits */
/* SYSCTL_CMPHNMXSEL[CMP3HNMXSEL] Bits */
#define SYSCTL_CMPHNMXSEL_CMP3HNMXSEL_OFS        (3)                             /* !< CMP3HNMXSEL Offset */
#define SYSCTL_CMPHNMXSEL_CMP3HNMXSEL_MASK       ((uint32_t)0x00000008U)         /* !< CMP3HNMXSEL bits */
/* SYSCTL_CMPHNMXSEL[CMP2HNMXSEL] Bits */
#define SYSCTL_CMPHNMXSEL_CMP2HNMXSEL_OFS        (2)                             /* !< CMP2HNMXSEL Offset */
#define SYSCTL_CMPHNMXSEL_CMP2HNMXSEL_MASK       ((uint32_t)0x00000004U)         /* !< CMP2HNMXSEL bits */
/* SYSCTL_CMPHNMXSEL[CMP1HNMXSEL] Bits */
#define SYSCTL_CMPHNMXSEL_CMP1HNMXSEL_OFS        (1)                             /* !< CMP1HNMXSEL Offset */
#define SYSCTL_CMPHNMXSEL_CMP1HNMXSEL_MASK       ((uint32_t)0x00000002U)         /* !< CMP1HNMXSEL bits */
/* SYSCTL_CMPHNMXSEL[CMP0HNMXSEL] Bits */
#define SYSCTL_CMPHNMXSEL_CMP0HNMXSEL_OFS        (0)                             /* !< CMP0HNMXSEL Offset */
#define SYSCTL_CMPHNMXSEL_CMP0HNMXSEL_MASK       ((uint32_t)0x00000001U)         /* !< CMP0HNMXSEL bits */

/* SYSCTL_CMPLNMXSEL Bits */
/* SYSCTL_CMPLNMXSEL[CMP0LNMXSEL] Bits */
#define SYSCTL_CMPLNMXSEL_CMP0LNMXSEL_OFS        (0)                             /* !< CMP0LNMXSEL Offset */
#define SYSCTL_CMPLNMXSEL_CMP0LNMXSEL_MASK       ((uint32_t)0x00000001U)         /* !< CMP0LNMXSEL bits */
/* SYSCTL_CMPLNMXSEL[CMP1LNMXSEL] Bits */
#define SYSCTL_CMPLNMXSEL_CMP1LNMXSEL_OFS        (1)                             /* !< CMP1LNMXSEL Offset */
#define SYSCTL_CMPLNMXSEL_CMP1LNMXSEL_MASK       ((uint32_t)0x00000002U)         /* !< CMP1LNMXSEL bits */
/* SYSCTL_CMPLNMXSEL[CMP3LNMXSEL] Bits */
#define SYSCTL_CMPLNMXSEL_CMP3LNMXSEL_OFS        (3)                             /* !< CMP3LNMXSEL Offset */
#define SYSCTL_CMPLNMXSEL_CMP3LNMXSEL_MASK       ((uint32_t)0x00000008U)         /* !< CMP3LNMXSEL bits */
/* SYSCTL_CMPLNMXSEL[CMP2LNMXSEL] Bits */
#define SYSCTL_CMPLNMXSEL_CMP2LNMXSEL_OFS        (2)                             /* !< CMP2LNMXSEL Offset */
#define SYSCTL_CMPLNMXSEL_CMP2LNMXSEL_MASK       ((uint32_t)0x00000004U)         /* !< CMP2LNMXSEL bits */

/* SYSCTL_TSNSCFG Bits */

/* SYSCTL_TSNSSCTL Bits */
/* SYSCTL_TSNSSCTL[ENABLE] Bits */
#define SYSCTL_TSNSSCTL_ENABLE_OFS               (0)                             /* !< ENABLE Offset */
#define SYSCTL_TSNSSCTL_ENABLE_MASK              ((uint32_t)0x00000001U)         /* !< Temperature Sensor Enable */

/* SYSCTL_PGACONFIG Bits */

/* SYSCTL_REFCONFIGA Bits */

/* SYSCTL_INTERNALTESTCTL Bits */
/* SYSCTL_INTERNALTESTCTL[TESTSEL] Bits */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_OFS       (0)                             /* !< TESTSEL Offset */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_MASK      ((uint32_t)0x0000003FU)         /* !< Test Select */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL1      ((uint32_t)0x00000001U)         /* !< VDDCORE */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL2      ((uint32_t)0x00000002U)         /* !< VDDA */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL3      ((uint32_t)0x00000003U)         /* !< VSSA */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL4      ((uint32_t)0x00000004U)         /* !< VREFLOAC */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL5      ((uint32_t)0x00000005U)         /* !< CDAC1H */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL6      ((uint32_t)0x00000006U)         /* !< CDAC1L */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL7      ((uint32_t)0x00000007U)         /* !< CDAC2H */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL8      ((uint32_t)0x00000008U)         /* !< CDAC2H */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL9      ((uint32_t)0x00000009U)         /* !< CDAC2H */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL10     ((uint32_t)0x0000000AU)         /* !< CDAC2H */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL11     ((uint32_t)0x0000000BU)         /* !< CDAC2H */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL12     ((uint32_t)0x0000000CU)         /* !< CDAC2H */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL14     ((uint32_t)0x0000001DU)         /* !< ENZ_CALIB_GAIN_3P3V will be made
                                                                                    low. ADCA and ADCC will be in gain
                                                                                    calibration mode, and 0.9xVREFHIAB
                                                                                    pin voltage will be sampled by both
                                                                                    ADCs through internal test-mux output */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL15     ((uint32_t)0x0000001EU)         /* !< CMPSS1 VDDA sense on TESTANA0,VSSA
                                                                                    sense on TESTANA1 */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL16     ((uint32_t)0x0000001FU)         /* !< ADCA VDDA sense on TESTANA0,VSSA
                                                                                    sense on TESTANA1 */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL17     ((uint32_t)0x00000020U)         /* !< COMP DAC BUFFER VDDA sense on
                                                                                    TESTANA0,VSSA sense on TESTANA1 */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL18     ((uint32_t)0x00000021U)         /* !< PGA1 VDDA sense on TESTANA0,VSSA
                                                                                    sense on TESTANA1 */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL19     ((uint32_t)0x00000022U)         /* !< ADCCIO_TESTANA0_INT */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL20     ((uint32_t)0x00000023U)         /* !< PMM/HPLL/INTOSC TESTANA0_INT */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL21     ((uint32_t)0x00000024U)         /* !< ADCCIO_TESTANA1_INT */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL22     ((uint32_t)0x00000025U)         /* !< PMM/HPLL/INTOSC TESTANA1_INT */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL23     ((uint32_t)0x00000026U)         /* !< Enable resistor for I2V conversion.
                                                                                    The same control enables the sampling
                                                                                    of voltage across a resistor by ADC.
                                                                                    R=2.5k, 38: R=10k, 39: R=35k */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL24     ((uint32_t)0x00000029U)         /* !< USB_TESTANA0_INT */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL25     ((uint32_t)0x0000002AU)         /* !< USB_TESTANA1_INT */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL26     ((uint32_t)0x0000002BU)         /* !< USB_TESTANA0_INT & USB_TESTANA1_INT */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL27     ((uint32_t)0x0000002CU)         /* !< VSS */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL28     ((uint32_t)0x0000002DU)         /* !< Bring FLT3 & TESTPAD3 of flash on
                                                                                    TESTANA1 */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL29     ((uint32_t)0x0000002EU)         /* !< Enable resistor for I2V conversion.
                                                                                    The same control enables the sampling
                                                                                    of voltage across a resistor by ADC.
                                                                                    R=2.5k, 47: R=10k, 48: R=35k */
#define SYSCTL_INTERNALTESTCTL_TESTSEL_SEL30     ((uint32_t)0x00000031U)         /* !< VREFLOAC */

/* SYSCTL_I2VCTL Bits */

/* SYSCTL_ADCDACLOOPBACK Bits */

/* SYSCTL_XTALCR Bits */
/* SYSCTL_XTALCR[SE] Bits */
#define SYSCTL_XTALCR_SE_OFS                     (1)                             /* !< SE Offset */
#define SYSCTL_XTALCR_SE_MASK                    ((uint32_t)0x00000002U)         /* !< XTAL Oscilator in Single-Ended */
#define SYSCTL_XTALCR_SE_FALSE                   ((uint32_t)0x00000000U)         /* !< XTAL oscillator in Crystal mode */
#define SYSCTL_XTALCR_SE_TRUE                    ((uint32_t)0x00000002U)         /* !< XTAL oscilator in single-ended mode
                                                                                    (through X1) */
/* SYSCTL_XTALCR[OSCOFF] Bits */
#define SYSCTL_XTALCR_OSCOFF_OFS                 (0)                             /* !< OSCOFF Offset */
#define SYSCTL_XTALCR_OSCOFF_MASK                ((uint32_t)0x00000001U)         /* !< This bit if 1, powers-down the XTAL
                                                                                    oscillator macro and hence doesnt let
                                                                                    X2 to be driven by the XTAL
                                                                                    oscillator. If a crystal is connected
                                                                                    to X1/X2, user needs to first clear
                                                                                    this bit, wait for the oscillator to
                                                                                    power up (using X1CNT) and then only
                                                                                    switch the clock source to X1/X2 */
#define SYSCTL_XTALCR_OSCOFF_FALSE               ((uint32_t)0x00000000U)         /* !< XTAL Oscillator powered-up using
                                                                                    X1/X2 */
#define SYSCTL_XTALCR_OSCOFF_TRUE                ((uint32_t)0x00000001U)         /* !< XTAL Oscillator powered-down */

/* SYSCTL_XTALCR2 Bits */
/* SYSCTL_XTALCR2[FEN] Bits */
#define SYSCTL_XTALCR2_FEN_OFS                   (2)                             /* !< FEN Offset */
#define SYSCTL_XTALCR2_FEN_MASK                  ((uint32_t)0x00000004U)         /* !< XOSC pads initialisation enable.
                                                                                    Configures XTAL oscillator pad
                                                                                    initilisation. This register has
                                                                                    effect only when XOSC is OFF (no SE ,
                                                                                    no XTAL mode). If this register is
                                                                                    set during XOSC off state (XOSCOFF=1
                                                                                    & SE=0); then upon change of these
                                                                                    controls this bit gets reset and
                                                                                    rearmed */
#define SYSCTL_XTALCR2_FEN_FALSE                 ((uint32_t)0x00000000U)         /* !< XOSC pads are not driven through
                                                                                    GPIO connection. */
#define SYSCTL_XTALCR2_FEN_TRUE                  ((uint32_t)0x00000004U)         /* !< XOSC pads are driven through
                                                                                    connected GPIO as per XIF & XOF
                                                                                    values. */
/* SYSCTL_XTALCR2[XOF] Bits */
#define SYSCTL_XTALCR2_XOF_OFS                   (1)                             /* !< XOF Offset */
#define SYSCTL_XTALCR2_XOF_MASK                  ((uint32_t)0x00000002U)         /* !< XO Initial value deposited before
                                                                                    XOSC start. Polarity selection to
                                                                                    initialise XO/X2 pad of the XOSC
                                                                                    before start-up. This value shall be
                                                                                    deposited on the pad before XOSC
                                                                                    started (XOSCOFF=1). If FEN=0 or XOSC
                                                                                    is in XTAL or SE mode; then this
                                                                                    value will not be applied to the pad. */
/* SYSCTL_XTALCR2[FKEEPXI] Bits */
#define SYSCTL_XTALCR2_FKEEPXI_OFS               (16)                            /* !< FKEEPXI Offset */
#define SYSCTL_XTALCR2_FKEEPXI_MASK              ((uint32_t)0xFFFF0000U)         /* !< This field when written 0xface
                                                                                    allows to hold the force value on XI
                                                                                    as programmed on XIF. 0xface: Force
                                                                                    on XI is continued as per XIF value
                                                                                    regardless of XOSC ON/OFF state only
                                                                                    in XTAL mode. In Single ended mode
                                                                                    this field has no impact. Any other
                                                                                    value: Force on XI is removed with
                                                                                    enabling of XOSC as per FEN function. */
/* SYSCTL_XTALCR2[XIF] Bits */
#define SYSCTL_XTALCR2_XIF_OFS                   (0)                             /* !< XIF Offset */
#define SYSCTL_XTALCR2_XIF_MASK                  ((uint32_t)0x00000001U)         /* !< XI Initial value deposited before
                                                                                    XOSC start. Polarity selection to
                                                                                    initialise XI/X1 pad of the XOSC
                                                                                    before start-up. This value shall be
                                                                                    deposited on the pad before XOSC
                                                                                    started (XOSCOFF=1). If FEN=0 or XOSC
                                                                                    is in XTAL or SE mode; then this
                                                                                    value will not be applied to the pad. */

/* SYSCTL_X1CNT Bits */
/* SYSCTL_X1CNT[CLR] Bits */
#define SYSCTL_X1CNT_CLR_OFS                     (16)                            /* !< CLR Offset */
#define SYSCTL_X1CNT_CLR_MASK                    ((uint32_t)0x00010000U)         /* !< X1 Counter clear: A write of 1 to
                                                                                    this bit field clears the X1CNT and
                                                                                    makes it count from 0x0 again
                                                                                    (provided X1 clock is ticking).
                                                                                    Writes of 0 are ignore to this bit
                                                                                    field */
/* SYSCTL_X1CNT[X1CNT] Bits */
#define SYSCTL_X1CNT_X1CNT_OFS                   (0)                             /* !< X1CNT Offset */
#define SYSCTL_X1CNT_X1CNT_MASK                  ((uint32_t)0x000007FFU)         /* !< This counter increments on every X1
                                                                                    CLOCKs positive-edge. Once it reaches
                                                                                    the values of 0x7ff, it freezes.
                                                                                    Before switching from SYSOSC/PLL
                                                                                    clock to X1, application must check
                                                                                    this counter and make sure that it
                                                                                    has saturated. This will ensure that
                                                                                    the Crystal connected to X1/X2 is
                                                                                    oscillating */

/* SYSCTL_CMPSSCTL Bits */
/* SYSCTL_CMPSSCTL[CMPSSCTLEN] Bits */
#define SYSCTL_CMPSSCTL_CMPSSCTLEN_OFS           (31)                            /* !< CMPSSCTLEN Offset */
#define SYSCTL_CMPSSCTL_CMPSSCTLEN_MASK          ((uint32_t)0x80000000U)         /* !< Enable the CMPSSCTL Register */
/* SYSCTL_CMPSSCTL[CMP3LDACOUTEN] Bits */
#define SYSCTL_CMPSSCTL_CMP3LDACOUTEN_OFS        (1)                             /* !< CMP3LDACOUTEN Offset */
#define SYSCTL_CMPSSCTL_CMP3LDACOUTEN_MASK       ((uint32_t)0x00000002U)         /* !< Enable general purpose DAC
                                                                                    functionality for CMPSS3 COMPDACL */
/* SYSCTL_CMPSSCTL[CMP2LDACOUTEN] Bits */
#define SYSCTL_CMPSSCTL_CMP2LDACOUTEN_OFS        (0)                             /* !< CMP2LDACOUTEN Offset */
#define SYSCTL_CMPSSCTL_CMP2LDACOUTEN_MASK       ((uint32_t)0x00000001U)         /* !< Enable general purpose DAC
                                                                                    functionality for CMPSS2 COMPDACL */

/* SYSCTL_CMPSSDACBUFCONFIG Bits */

/* SYSCTL_ANAREFCTL Bits */
/* SYSCTL_ANAREFCTL[ANAREF2P5SEL] Bits */
#define SYSCTL_ANAREFCTL_ANAREF2P5SEL_OFS        (8)                             /* !< ANAREF2P5SEL Offset */
#define SYSCTL_ANAREFCTL_ANAREF2P5SEL_MASK       ((uint32_t)0x00000100U)         /* !< Analog reference 2.5V source
                                                                                    select.  In internal reference mode,
                                                                                    this bit selects which voltage the
                                                                                    internal reference buffer drives onto
                                                                                    the VREFHI pin.  The buffer can drive
                                                                                    either 1.65V onto the pin, resulting
                                                                                    in a reference range of 0 to 3.3V, or
                                                                                    the buffer can drive 2.5V onto the
                                                                                    pin, resulting in a reference range
                                                                                    of 0 to 2.5V.  If switching between
                                                                                    these two modes, the user must allow
                                                                                    adequate time for the external
                                                                                    capacitor to charge to the new
                                                                                    voltage before using the ADC or
                                                                                    buffered DAC. 0 - Internal 1.65V
                                                                                    reference mode (3.3V reference range)
                                                                                    1 - Internal 2.5V reference mode
                                                                                    (2.5V reference range) */
/* SYSCTL_ANAREFCTL[ANAREFSEL] Bits */
#define SYSCTL_ANAREFCTL_ANAREFSEL_OFS           (0)                             /* !< ANAREFSEL Offset */
#define SYSCTL_ANAREFCTL_ANAREFSEL_MASK          ((uint32_t)0x00000001U)         /* !< Analog reference mode select.  This
                                                                                    bit selects whether the VREFHI pin
                                                                                    uses internal reference mode (the
                                                                                    device drives a voltage onto the
                                                                                    VREFHI pin) or external reference
                                                                                    mode (the system is expected to drive
                                                                                    a voltage into the VREFHI pin). 0 -
                                                                                    Internal reference mode 1 - External
                                                                                    reference mode */

/* SYSCTL_PERCLKCR Bits */
/* SYSCTL_PERCLKCR[TBCLKSYNC] Bits */
#define SYSCTL_PERCLKCR_TBCLKSYNC_OFS            (0)                             /* !< TBCLKSYNC Offset */
#define SYSCTL_PERCLKCR_TBCLKSYNC_MASK           ((uint32_t)0x00000001U)         /* !< PWM Time Base Clock sync: When set
                                                                                    PWM time bases of all the PWM modules
                                                                                    belonging to the same CPU-Subsystem
                                                                                    (as partitioned using their CPUSEL
                                                                                    bits) start counting */

/* SYSCTL_ADC_MMR_OVRD_CTL Bits */

/* SYSCTL_ADC_MMR_OVRD_VAL Bits */

/* SYSCTL_VREGCONFIGDEBUG Bits */

/* SYSCTL_VREGCONFIGDFT Bits */

/* SYSCTL_AM13SPAREIREFENSOCLOCK Bits */
/* SYSCTL_AM13SPAREIREFENSOCLOCK[SPARE] Bits */
#define SYSCTL_AM13SPAREIREFENSOCLOCK_SPARE_OFS  (0)                             /* !< SPARE Offset */
#define SYSCTL_AM13SPAREIREFENSOCLOCK_SPARE_MASK ((uint32_t)0x0000003FU)         /* !< Spare IREFEN SOC LOCK Register */

/* SYSCTL_AM13SPARESOCLOCK2 Bits */
/* SYSCTL_AM13SPARESOCLOCK2[SPARE] Bits */
#define SYSCTL_AM13SPARESOCLOCK2_SPARE_OFS       (1)                             /* !< SPARE Offset */
#define SYSCTL_AM13SPARESOCLOCK2_SPARE_MASK      ((uint32_t)0xFFFFFFFEU)         /* !< Spare SOC LOCK Register 2 */
/* SYSCTL_AM13SPARESOCLOCK2[SRAM3_STATIC_MUX_SEL] Bits */
#define SYSCTL_AM13SPARESOCLOCK2_SRAM3_STATIC_MUX_SEL_OFS (0)                             /* !< SRAM3_STATIC_MUX_SEL Offset */
#define SYSCTL_AM13SPARESOCLOCK2_SRAM3_STATIC_MUX_SEL_MASK ((uint32_t)0x00000001U)         /* !< SRAM3 static mux select between
                                                                                    CBUS and SBUS */
#define SYSCTL_AM13SPARESOCLOCK2_SRAM3_STATIC_MUX_SEL_SBUS ((uint32_t)0x00000000U)         /* !< SBUS path is selected */
#define SYSCTL_AM13SPARESOCLOCK2_SRAM3_STATIC_MUX_SEL_CBUS ((uint32_t)0x00000001U)         /* !< CBUS path is selected */

/* SYSCTL_AM13SPARESOCLOCK3 Bits */
/* SYSCTL_AM13SPARESOCLOCK3[SPARE] Bits */
#define SYSCTL_AM13SPARESOCLOCK3_SPARE_OFS       (0)                             /* !< SPARE Offset */
#define SYSCTL_AM13SPARESOCLOCK3_SPARE_MASK      ((uint32_t)0xFFFFFFFFU)         /* !< Spare SOC LOCK Register 3 */

/* SYSCTL_AM13SPARESOCLOCK4 Bits */
/* SYSCTL_AM13SPARESOCLOCK4[SPARE] Bits */
#define SYSCTL_AM13SPARESOCLOCK4_SPARE_OFS       (0)                             /* !< SPARE Offset */
#define SYSCTL_AM13SPARESOCLOCK4_SPARE_MASK      ((uint32_t)0xFFFFFFFFU)         /* !< Spare SOC LOCK Register 4 */


#ifdef __cplusplus
}
#endif

#endif /* hw_sysctl__include */
