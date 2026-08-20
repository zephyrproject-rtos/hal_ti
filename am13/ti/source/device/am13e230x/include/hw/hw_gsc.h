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

#ifndef hw_gsc__include
#define hw_gsc__include


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
* GSC Registers
******************************************************************************/


/** @addtogroup GSC
  @{
*/

typedef struct {
       uint32_t RESERVED0[1025];
  __IO uint32_t SPC_ATTRIBVIOLP_CONFIG;            /* !< (@ 0x00001004) SRAM Privilege Access Attribute Violation
                                                      Configuration Register */
       uint32_t RESERVED1[3];
  __IO uint32_t PPC_ATTRIBVIOLP_CONFIG;            /* !< (@ 0x00001014) Peripheral Privilege Access Attribute Violation
                                                      Configuration Register */
       uint32_t RESERVED2[3];
  __IO uint32_t FPC_ATTRIBVIOLP_CONFIG;            /* !< (@ 0x00001024) Flash Privilege Access Attribute Violation
                                                      Configuration Register */
       uint32_t RESERVED3[6];
  __IO uint32_t FPC_HDPPROT0_CONFIG;               /* !< (@ 0x00001040) Flash Hide Protection for Bank0 Configuration
                                                      Register */
  __IO uint32_t FPC_HDPPROT1_CONFIG;               /* !< (@ 0x00001044) Flash Hide Protection for Bank1 Configuration
                                                      Register */
       uint32_t RESERVED4;
  __IO uint32_t FPC_HDPPROT_CONTROL;               /* !< (@ 0x0000104C) Flash Hide Protection Control Register */
  __IO uint32_t FPC_HDPEN_CONTROL;                 /* !< (@ 0x00001050) Flash Hide Protection Enable Control Register */
  __IO uint32_t FPC_NONMAIN0_HDPPROT_CONTROL;      /* !< (@ 0x00001054) Flash NONMAIN Bank0 Hide Protection Control
                                                      Register */
  __IO uint32_t FPC_NONMAIN1_HDPPROT_CONTROL;      /* !< (@ 0x00001058) Flash NONMAIN Bank1 Hide Protection Control
                                                      Register */
  __IO uint32_t FPC_TRIM0_HDPPROT_CONTROL;         /* !< (@ 0x0000105C) Flash TRIM Bank0 Hide Protection Control Register */
  __IO uint32_t FPC_TRIM1_HDPPROT_CONTROL;         /* !< (@ 0x00001060) Flash TRIM Bank1 Hide Protection Control Register */
  __IO uint32_t FPC_ENGR0_HDPPROT_CONTROL;         /* !< (@ 0x00001064) Flash ENGR Bank0 Hide Protection Control Register */
  __IO uint32_t FPC_ENGR1_HDPPROT_CONTROL;         /* !< (@ 0x00001068) Flash ENGR Bank1 Hide Protection Control Register */
       uint32_t RESERVED5[38];
  __IO uint32_t PPC_PRIVATTRIB_ADC;                /* !< (@ 0x00001104) Peripheral Privilege Access ADC */
       uint32_t RESERVED6;
  __IO uint32_t PPC_PRIVATTRIB_TIMER;              /* !< (@ 0x0000110C) Peripheral Privilege Access Timer */
       uint32_t RESERVED7;
  __IO uint32_t PPC_PRIVATTRIB_UNICOMM;            /* !< (@ 0x00001114) Peripheral Privilege Access UniComm */
       uint32_t RESERVED8;
  __IO uint32_t PPC_PRIVATTRIB_GPIO;               /* !< (@ 0x0000111C) Peripheral Privilege Access GPIO */
       uint32_t RESERVED9;
  __IO uint32_t PPC_PRIVATTRIB_MCAN;               /* !< (@ 0x00001124) Peripheral Privilege Access CAN */
       uint32_t RESERVED10[3];
  __IO uint32_t PPC_PRIVATTRIB_CMPSS;              /* !< (@ 0x00001134) Peripheral Privilege Access CMPSS */
       uint32_t RESERVED11;
  __IO uint32_t PPC_PRIVATTRIB_WDT;                /* !< (@ 0x0000113C) Peripheral Privilege Access Watchdog */
       uint32_t RESERVED12[3];
  __IO uint32_t PPC_PRIVATTRIB_CRC;                /* !< (@ 0x0000114C) Peripheral Privilege Access CRC */
       uint32_t RESERVED13;
  __IO uint32_t PPC_PRIVATTRIB_AES;                /* !< (@ 0x00001154) Peripheral Privilege Access AES */
       uint32_t RESERVED14[5];
  __IO uint32_t PPC_PRIVATTRIB_IOMUX;              /* !< (@ 0x0000116C) Peripheral Privilege Access IOMUX */
       uint32_t RESERVED15[5];
  __IO uint32_t PPC_PRIVATTRIB_DEBUGSS;            /* !< (@ 0x00001184) Peripheral Privilege Access DEBUGSS */
       uint32_t RESERVED16[3];
  __IO uint32_t PPC_PRIVATTRIB_KEYSTORECTL;        /* !< (@ 0x00001194) Peripheral Privilege Access KEYSTORECTL */
       uint32_t RESERVED17;
  __IO uint32_t PPC_PRIVATTRIB_EAM;                /* !< (@ 0x0000119C) Peripheral Privilege Access EAM */
       uint32_t RESERVED18;
  __IO uint32_t PPC_PRIVATTRIB_WUC;                /* !< (@ 0x000011A4) Peripheral Privilege Access WUC */
       uint32_t RESERVED19;
  __IO uint32_t PPC_PRIVATTRIB_FRIREGS;            /* !< (@ 0x000011AC) Peripheral Privilege Access FRIREGS */
       uint32_t RESERVED20;
  __IO uint32_t PPC_PRIVATTRIB_MEMCFG;             /* !< (@ 0x000011B4) Peripheral Privilege Access MEMCFG */
       uint32_t RESERVED21[21];
  __IO uint32_t PPC_PRIVATTRIB_SYSCTL;             /* !< (@ 0x0000120C) Peripheral Privilege Access System Control */
       uint32_t RESERVED22;
  __IO uint32_t PPC_PRIVATTRIB_DMA;                /* !< (@ 0x00001214) Peripheral Privilege Access DMA */
       uint32_t RESERVED23;
  __IO uint32_t PPC_PRIVATTRIB_GSC;                /* !< (@ 0x0000121C) Peripheral Privilege Access GSC */
       uint32_t RESERVED24;
  __IO uint32_t PPC_PRIVATTRIB_COPROC;             /* !< (@ 0x00001224) Peripheral Privilege Access Co-processor */
       uint32_t RESERVED25;
  __IO uint32_t PPC_PRIVATTRIB_EPI;                /* !< (@ 0x0000122C) Peripheral Privilege Access EPI */
       uint32_t RESERVED26;
  __IO uint32_t PPC_PRIVATTRIB_PGA;                /* !< (@ 0x00001234) Peripheral Privilege Access PGA */
       uint32_t RESERVED27;
  __IO uint32_t PPC_PRIVATTRIB_XBAR;               /* !< (@ 0x0000123C) Peripheral Privilege Access XBAR */
       uint32_t RESERVED28[32];
  __IO uint32_t SPC_PRIVATTRIB0;                   /* !< (@ 0x000012C0) SRAM Privilege Attribute-0 Register */
  __IO uint32_t SPC_PRIVATTRIB1;                   /* !< (@ 0x000012C4) SRAM Privilege Attribute-1 Register */
       uint32_t RESERVED29[78];
  __IO uint32_t FPC_PRIVATTRIBA0;                  /* !< (@ 0x00001400) Flash Privilege Attribute Register A0 */
  __IO uint32_t FPC_PRIVATTRIBA1;                  /* !< (@ 0x00001404) Flash Privilege Attribute Register A1 */
  __IO uint32_t FPC_PRIVATTRIBB0;                  /* !< (@ 0x00001408) Flash Privilege Attribute Register B0 */
  __IO uint32_t FPC_PRIVATTRIBB1;                  /* !< (@ 0x0000140C) Flash Privilege Attribute Register B1 */
  __IO uint32_t FPC_NONMAIN_PRIVATTRIB0;           /* !< (@ 0x00001410) Flash Non-Main Privilege Attribute Register B0 */
  __IO uint32_t FPC_NONMAIN_PRIVATTRIB1;           /* !< (@ 0x00001414) Flash Non-Main Privilege Attribute Register B1 */
  __IO uint32_t FPC_TRIM_PRIVATTRIB0;              /* !< (@ 0x00001418) Flash Trim Privilege Attribute Register B0 */
  __IO uint32_t FPC_TRIM_PRIVATTRIB1;              /* !< (@ 0x0000141C) Flash Trim Privilege Attribute Register B1 */
  __IO uint32_t FPC_ENGR_PRIVATTRIB0;              /* !< (@ 0x00001420) Flash Engr Privilege Attribute Register B0 */
  __IO uint32_t FPC_ENGR_PRIVATTRIB1;              /* !< (@ 0x00001424) Flash Engr Privilege Attribute Register B1 */
       uint32_t RESERVED30[118];
  __IO uint32_t FPC_WEPROTA0;                      /* !< (@ 0x00001600) Flash Write Protect Attribute Register A0 */
  __IO uint32_t FPC_WEPROTA1;                      /* !< (@ 0x00001604) Flash Write Protect Attribute Register A1 */
  __IO uint32_t FPC_WEPROTB0;                      /* !< (@ 0x00001608) Flash Write Protect Attribute Register B0 */
  __IO uint32_t FPC_WEPROTB1;                      /* !< (@ 0x0000160C) Flash Write Protect Attribute Register B1 */
  __IO uint32_t FPC_WEPROTNONMAIN0;                /* !< (@ 0x00001610) Flash Non-Main Write Protect Attribute Register B0 */
  __IO uint32_t FPC_WEPROTNONMAIN1;                /* !< (@ 0x00001614) Flash Non-Main Write Protect Attribute Register B1 */
  __IO uint32_t FPC_WEPROTTRIM0;                   /* !< (@ 0x00001618) Flash Trim Write Protect Attribute Register B0 */
  __IO uint32_t FPC_WEPROTTRIM1;                   /* !< (@ 0x0000161C) Flash Trim Write Protect Attribute Register B1 */
  __IO uint32_t FPC_WEPROTENGR0;                   /* !< (@ 0x00001620) Flash Engr Write Protect Attribute Register B0 */
  __IO uint32_t FPC_WEPROTENGR1;                   /* !< (@ 0x00001624) Flash Engr Write Protect Attribute Register B1 */
       uint32_t RESERVED31[118];
  __IO uint32_t FPC_FLSEMREQ;                      /* !< (@ 0x00001800) Flash semaphore request register */
  __IO uint32_t FPC_FLSEMCLR;                      /* !< (@ 0x00001804) Flash semaphore release register */
  __IO uint32_t FPC_FLSEMSTAT;                     /* !< (@ 0x00001808) Flash semaphore statys registers */
       uint32_t RESERVED32[222];
  __IO uint32_t VTOR_NS;                           /* !< (@ 0x00001B84) Non - Secure Vector Table Offset Register */
       uint32_t RESERVED33[62];
  __IO uint32_t DTB_MUXSEL;                        /* !< (@ 0x00001C80) Digital Test Bus MUX Selection */
       uint32_t RESERVED34[63];
  __IO uint32_t GSC_LOCK;                          /* !< (@ 0x00001D80) GSC Lock configuration register */
  __IO uint32_t GSC_COMMIT;                        /* !< (@ 0x00001D84) GSC commit configuration register */
       uint32_t RESERVED35[157];
  __IO uint32_t GSC_REVISION;                      /* !< (@ 0x00001FFC) GSC Revision register */
} GSC_Regs;

/*@}*/ /* end of group GSC */



/******************************************************************************
* GSC Register Offsets
******************************************************************************/
#define GSC_SPC_ATTRIBVIOLP_CONFIG               (0x00001004U)
#define GSC_PPC_ATTRIBVIOLP_CONFIG               (0x00001014U)
#define GSC_FPC_ATTRIBVIOLP_CONFIG               (0x00001024U)
#define GSC_FPC_HDPPROT0_CONFIG                  (0x00001040U)
#define GSC_FPC_HDPPROT1_CONFIG                  (0x00001044U)
#define GSC_FPC_HDPPROT_CONTROL                  (0x0000104CU)
#define GSC_FPC_HDPEN_CONTROL                    (0x00001050U)
#define GSC_FPC_NONMAIN0_HDPPROT_CONTROL         (0x00001054U)
#define GSC_FPC_NONMAIN1_HDPPROT_CONTROL         (0x00001058U)
#define GSC_FPC_TRIM0_HDPPROT_CONTROL            (0x0000105CU)
#define GSC_FPC_TRIM1_HDPPROT_CONTROL            (0x00001060U)
#define GSC_FPC_ENGR0_HDPPROT_CONTROL            (0x00001064U)
#define GSC_FPC_ENGR1_HDPPROT_CONTROL            (0x00001068U)
#define GSC_PPC_PRIVATTRIB_ADC                   (0x00001104U)
#define GSC_PPC_PRIVATTRIB_TIMER                 (0x0000110CU)
#define GSC_PPC_PRIVATTRIB_UNICOMM               (0x00001114U)
#define GSC_PPC_PRIVATTRIB_GPIO                  (0x0000111CU)
#define GSC_PPC_PRIVATTRIB_MCAN                  (0x00001124U)
#define GSC_PPC_PRIVATTRIB_CMPSS                 (0x00001134U)
#define GSC_PPC_PRIVATTRIB_WDT                   (0x0000113CU)
#define GSC_PPC_PRIVATTRIB_CRC                   (0x0000114CU)
#define GSC_PPC_PRIVATTRIB_AES                   (0x00001154U)
#define GSC_PPC_PRIVATTRIB_IOMUX                 (0x0000116CU)
#define GSC_PPC_PRIVATTRIB_DEBUGSS               (0x00001184U)
#define GSC_PPC_PRIVATTRIB_KEYSTORECTL           (0x00001194U)
#define GSC_PPC_PRIVATTRIB_EAM                   (0x0000119CU)
#define GSC_PPC_PRIVATTRIB_WUC                   (0x000011A4U)
#define GSC_PPC_PRIVATTRIB_FRIREGS               (0x000011ACU)
#define GSC_PPC_PRIVATTRIB_MEMCFG                (0x000011B4U)
#define GSC_PPC_PRIVATTRIB_SYSCTL                (0x0000120CU)
#define GSC_PPC_PRIVATTRIB_DMA                   (0x00001214U)
#define GSC_PPC_PRIVATTRIB_GSC                   (0x0000121CU)
#define GSC_PPC_PRIVATTRIB_COPROC                (0x00001224U)
#define GSC_PPC_PRIVATTRIB_EPI                   (0x0000122CU)
#define GSC_PPC_PRIVATTRIB_PGA                   (0x00001234U)
#define GSC_PPC_PRIVATTRIB_XBAR                  (0x0000123CU)
#define GSC_SPC_PRIVATTRIB0                      (0x000012C0U)
#define GSC_SPC_PRIVATTRIB1                      (0x000012C4U)
#define GSC_FPC_PRIVATTRIBA0                     (0x00001400U)
#define GSC_FPC_PRIVATTRIBA1                     (0x00001404U)
#define GSC_FPC_PRIVATTRIBB0                     (0x00001408U)
#define GSC_FPC_PRIVATTRIBB1                     (0x0000140CU)
#define GSC_FPC_NONMAIN_PRIVATTRIB0              (0x00001410U)
#define GSC_FPC_NONMAIN_PRIVATTRIB1              (0x00001414U)
#define GSC_FPC_TRIM_PRIVATTRIB0                 (0x00001418U)
#define GSC_FPC_TRIM_PRIVATTRIB1                 (0x0000141CU)
#define GSC_FPC_ENGR_PRIVATTRIB0                 (0x00001420U)
#define GSC_FPC_ENGR_PRIVATTRIB1                 (0x00001424U)
#define GSC_FPC_WEPROTA0                         (0x00001600U)
#define GSC_FPC_WEPROTA1                         (0x00001604U)
#define GSC_FPC_WEPROTB0                         (0x00001608U)
#define GSC_FPC_WEPROTB1                         (0x0000160CU)
#define GSC_FPC_WEPROTNONMAIN0                   (0x00001610U)
#define GSC_FPC_WEPROTNONMAIN1                   (0x00001614U)
#define GSC_FPC_WEPROTTRIM0                      (0x00001618U)
#define GSC_FPC_WEPROTTRIM1                      (0x0000161CU)
#define GSC_FPC_WEPROTENGR0                      (0x00001620U)
#define GSC_FPC_WEPROTENGR1                      (0x00001624U)
#define GSC_FPC_FLSEMREQ                         (0x00001800U)
#define GSC_FPC_FLSEMCLR                         (0x00001804U)
#define GSC_FPC_FLSEMSTAT                        (0x00001808U)
#define GSC_VTOR_NS                              (0x00001B84U)
#define GSC_DTB_MUXSEL                           (0x00001C80U)
#define GSC_GSC_LOCK                             (0x00001D80U)
#define GSC_GSC_COMMIT                           (0x00001D84U)
#define GSC_GSC_REVISION                         (0x00001FFCU)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* GSC Register Control Bits
******************************************************************************/

/* GSC_SPC_ATTRIBVIOLP_CONFIG Bits */
/* GSC_SPC_ATTRIBVIOLP_CONFIG[PRIVVIOL] Bits */
#define GSC_SPC_ATTRIBVIOLP_CONFIG_PRIVVIOL_OFS  (0)                             /* !< PRIVVIOL Offset */
#define GSC_SPC_ATTRIBVIOLP_CONFIG_PRIVVIOL_MASK ((uint32_t)0x00000001U)         /* !< Privilege access to non-privilege
                                                                                    SRAM */

/* GSC_PPC_ATTRIBVIOLP_CONFIG Bits */
/* GSC_PPC_ATTRIBVIOLP_CONFIG[PRIVVIOL] Bits */
#define GSC_PPC_ATTRIBVIOLP_CONFIG_PRIVVIOL_OFS  (0)                             /* !< PRIVVIOL Offset */
#define GSC_PPC_ATTRIBVIOLP_CONFIG_PRIVVIOL_MASK ((uint32_t)0x00000001U)         /* !< Privilege access to non-privilege
                                                                                    Peripheral */

/* GSC_FPC_ATTRIBVIOLP_CONFIG Bits */
/* GSC_FPC_ATTRIBVIOLP_CONFIG[PRIVVIOL] Bits */
#define GSC_FPC_ATTRIBVIOLP_CONFIG_PRIVVIOL_OFS  (0)                             /* !< PRIVVIOL Offset */
#define GSC_FPC_ATTRIBVIOLP_CONFIG_PRIVVIOL_MASK ((uint32_t)0x00000001U)         /* !< Privilege access to non-privilege
                                                                                    Flash */

/* GSC_FPC_HDPPROT0_CONFIG Bits */
/* GSC_FPC_HDPPROT0_CONFIG[HDPEND] Bits */
#define GSC_FPC_HDPPROT0_CONFIG_HDPEND_OFS       (0)                             /* !< HDPEND Offset */
#define GSC_FPC_HDPPROT0_CONFIG_HDPEND_MASK      ((uint32_t)0x000000FFU)         /* !< HDPPROT0 end sector number */
/* GSC_FPC_HDPPROT0_CONFIG[HDPSTART] Bits */
#define GSC_FPC_HDPPROT0_CONFIG_HDPSTART_OFS     (16)                            /* !< HDPSTART Offset */
#define GSC_FPC_HDPPROT0_CONFIG_HDPSTART_MASK    ((uint32_t)0x00FF0000U)         /* !< HDPPROT0 start sector number */

/* GSC_FPC_HDPPROT1_CONFIG Bits */
/* GSC_FPC_HDPPROT1_CONFIG[HDPEND] Bits */
#define GSC_FPC_HDPPROT1_CONFIG_HDPEND_OFS       (0)                             /* !< HDPEND Offset */
#define GSC_FPC_HDPPROT1_CONFIG_HDPEND_MASK      ((uint32_t)0x000000FFU)         /* !< HDPPROT1 end sector number */
/* GSC_FPC_HDPPROT1_CONFIG[HDPSTART] Bits */
#define GSC_FPC_HDPPROT1_CONFIG_HDPSTART_OFS     (16)                            /* !< HDPSTART Offset */
#define GSC_FPC_HDPPROT1_CONFIG_HDPSTART_MASK    ((uint32_t)0x00FF0000U)         /* !< HDPPROT1 start sector number */

/* GSC_FPC_HDPPROT_CONTROL Bits */
/* GSC_FPC_HDPPROT_CONTROL[HDPPROT0ACCDIS] Bits */
#define GSC_FPC_HDPPROT_CONTROL_HDPPROT0ACCDIS_OFS (0)                             /* !< HDPPROT0ACCDIS Offset */
#define GSC_FPC_HDPPROT_CONTROL_HDPPROT0ACCDIS_MASK ((uint32_t)0x00000001U)         /* !< HDP region-0 enable */
/* GSC_FPC_HDPPROT_CONTROL[HDPPROT1ACCDIS] Bits */
#define GSC_FPC_HDPPROT_CONTROL_HDPPROT1ACCDIS_OFS (1)                             /* !< HDPPROT1ACCDIS Offset */
#define GSC_FPC_HDPPROT_CONTROL_HDPPROT1ACCDIS_MASK ((uint32_t)0x00000002U)         /* !< HDP region-1 enable */

/* GSC_FPC_HDPEN_CONTROL Bits */
/* GSC_FPC_HDPEN_CONTROL[HDPEN] Bits */
#define GSC_FPC_HDPEN_CONTROL_HDPEN_OFS          (0)                             /* !< HDPEN Offset */
#define GSC_FPC_HDPEN_CONTROL_HDPEN_MASK         ((uint32_t)0x00000001U)         /* !< HDP mode enable */

/* GSC_FPC_NONMAIN0_HDPPROT_CONTROL Bits */
/* GSC_FPC_NONMAIN0_HDPPROT_CONTROL[HDPROTACCDIS] Bits */
#define GSC_FPC_NONMAIN0_HDPPROT_CONTROL_HDPROTACCDIS_OFS (0)                             /* !< HDPROTACCDIS Offset */
#define GSC_FPC_NONMAIN0_HDPPROT_CONTROL_HDPROTACCDIS_MASK ((uint32_t)0x00000003U)         /* !< HDP enable for NONMAIN region of
                                                                                    Bank0 */

/* GSC_FPC_NONMAIN1_HDPPROT_CONTROL Bits */
/* GSC_FPC_NONMAIN1_HDPPROT_CONTROL[HDPROTACCDIS] Bits */
#define GSC_FPC_NONMAIN1_HDPPROT_CONTROL_HDPROTACCDIS_OFS (0)                             /* !< HDPROTACCDIS Offset */
#define GSC_FPC_NONMAIN1_HDPPROT_CONTROL_HDPROTACCDIS_MASK ((uint32_t)0x00000003U)         /* !< HDP enable for NONMAIN region of
                                                                                    Bank1 */

/* GSC_FPC_TRIM0_HDPPROT_CONTROL Bits */
/* GSC_FPC_TRIM0_HDPPROT_CONTROL[HDPROTACCDIS] Bits */
#define GSC_FPC_TRIM0_HDPPROT_CONTROL_HDPROTACCDIS_OFS (0)                             /* !< HDPROTACCDIS Offset */
#define GSC_FPC_TRIM0_HDPPROT_CONTROL_HDPROTACCDIS_MASK ((uint32_t)0x00000001U)         /* !< HDP enable for TRIM region of Bank0 */
/* GSC_FPC_TRIM0_HDPPROT_CONTROL[HDPROTACCDIS1] Bits */
#define GSC_FPC_TRIM0_HDPPROT_CONTROL_HDPROTACCDIS1_OFS (1)                             /* !< HDPROTACCDIS1 Offset */
#define GSC_FPC_TRIM0_HDPPROT_CONTROL_HDPROTACCDIS1_MASK ((uint32_t)0x00000002U)         /* !< Redundant */

/* GSC_FPC_TRIM1_HDPPROT_CONTROL Bits */
/* GSC_FPC_TRIM1_HDPPROT_CONTROL[HDPROTACCDIS] Bits */
#define GSC_FPC_TRIM1_HDPPROT_CONTROL_HDPROTACCDIS_OFS (0)                             /* !< HDPROTACCDIS Offset */
#define GSC_FPC_TRIM1_HDPPROT_CONTROL_HDPROTACCDIS_MASK ((uint32_t)0x00000001U)         /* !< HDP enable for TRIM region of Bank1 */
/* GSC_FPC_TRIM1_HDPPROT_CONTROL[HDPROTACCDIS1] Bits */
#define GSC_FPC_TRIM1_HDPPROT_CONTROL_HDPROTACCDIS1_OFS (1)                             /* !< HDPROTACCDIS1 Offset */
#define GSC_FPC_TRIM1_HDPPROT_CONTROL_HDPROTACCDIS1_MASK ((uint32_t)0x00000002U)         /* !< Redundant */

/* GSC_FPC_ENGR0_HDPPROT_CONTROL Bits */
/* GSC_FPC_ENGR0_HDPPROT_CONTROL[HDPROTACCDIS] Bits */
#define GSC_FPC_ENGR0_HDPPROT_CONTROL_HDPROTACCDIS_OFS (0)                             /* !< HDPROTACCDIS Offset */
#define GSC_FPC_ENGR0_HDPPROT_CONTROL_HDPROTACCDIS_MASK ((uint32_t)0x00000001U)         /* !< HDP enable for ENGR region of Bank0 */
/* GSC_FPC_ENGR0_HDPPROT_CONTROL[HDPROTACCDIS1] Bits */
#define GSC_FPC_ENGR0_HDPPROT_CONTROL_HDPROTACCDIS1_OFS (1)                             /* !< HDPROTACCDIS1 Offset */
#define GSC_FPC_ENGR0_HDPPROT_CONTROL_HDPROTACCDIS1_MASK ((uint32_t)0x00000002U)         /* !< Redundant */

/* GSC_FPC_ENGR1_HDPPROT_CONTROL Bits */
/* GSC_FPC_ENGR1_HDPPROT_CONTROL[HDPROTACCDIS] Bits */
#define GSC_FPC_ENGR1_HDPPROT_CONTROL_HDPROTACCDIS_OFS (0)                             /* !< HDPROTACCDIS Offset */
#define GSC_FPC_ENGR1_HDPPROT_CONTROL_HDPROTACCDIS_MASK ((uint32_t)0x00000001U)         /* !< HDP enable for ENGR region of Bank1 */
/* GSC_FPC_ENGR1_HDPPROT_CONTROL[HDPROTACCDIS1] Bits */
#define GSC_FPC_ENGR1_HDPPROT_CONTROL_HDPROTACCDIS1_OFS (1)                             /* !< HDPROTACCDIS1 Offset */
#define GSC_FPC_ENGR1_HDPPROT_CONTROL_HDPROTACCDIS1_MASK ((uint32_t)0x00000002U)         /* !< Redundant */

/* GSC_PPC_PRIVATTRIB_ADC Bits */
/* GSC_PPC_PRIVATTRIB_ADC[PRIV_ADC0] Bits */
#define GSC_PPC_PRIVATTRIB_ADC_PRIV_ADC0_OFS     (0)                             /* !< PRIV_ADC0 Offset */
#define GSC_PPC_PRIVATTRIB_ADC_PRIV_ADC0_MASK    ((uint32_t)0x00000001U)         /* !< Privilege access for ADC0 */
/* GSC_PPC_PRIVATTRIB_ADC[PRIV_ADC1] Bits */
#define GSC_PPC_PRIVATTRIB_ADC_PRIV_ADC1_OFS     (1)                             /* !< PRIV_ADC1 Offset */
#define GSC_PPC_PRIVATTRIB_ADC_PRIV_ADC1_MASK    ((uint32_t)0x00000002U)         /* !< Privilege access for ADC1 */
/* GSC_PPC_PRIVATTRIB_ADC[PRIV_ADC2] Bits */
#define GSC_PPC_PRIVATTRIB_ADC_PRIV_ADC2_OFS     (2)                             /* !< PRIV_ADC2 Offset */
#define GSC_PPC_PRIVATTRIB_ADC_PRIV_ADC2_MASK    ((uint32_t)0x00000004U)         /* !< Privilege access for ADC2 */

/* GSC_PPC_PRIVATTRIB_TIMER Bits */
/* GSC_PPC_PRIVATTRIB_TIMER[PRIV_PWM0] Bits */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_PWM0_OFS   (0)                             /* !< PRIV_PWM0 Offset */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_PWM0_MASK  ((uint32_t)0x00000001U)         /* !< Privilege access for PWM0 */
/* GSC_PPC_PRIVATTRIB_TIMER[PRIV_PWM1] Bits */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_PWM1_OFS   (1)                             /* !< PRIV_PWM1 Offset */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_PWM1_MASK  ((uint32_t)0x00000002U)         /* !< Privilege access for PWM1 */
/* GSC_PPC_PRIVATTRIB_TIMER[PRIV_PWM2] Bits */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_PWM2_OFS   (2)                             /* !< PRIV_PWM2 Offset */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_PWM2_MASK  ((uint32_t)0x00000004U)         /* !< Privilege access for PWM2 */
/* GSC_PPC_PRIVATTRIB_TIMER[PRIV_PWM3] Bits */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_PWM3_OFS   (3)                             /* !< PRIV_PWM3 Offset */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_PWM3_MASK  ((uint32_t)0x00000008U)         /* !< Privilege access for PWM3 */
/* GSC_PPC_PRIVATTRIB_TIMER[PRIV_PWM4] Bits */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_PWM4_OFS   (4)                             /* !< PRIV_PWM4 Offset */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_PWM4_MASK  ((uint32_t)0x00000010U)         /* !< Privilege access for PWM4 */
/* GSC_PPC_PRIVATTRIB_TIMER[PRIV_ECAP0] Bits */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_ECAP0_OFS  (8)                             /* !< PRIV_ECAP0 Offset */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_ECAP0_MASK ((uint32_t)0x00000100U)         /* !< Privilege access for ECAP0 */
/* GSC_PPC_PRIVATTRIB_TIMER[PRIV_ECAP1] Bits */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_ECAP1_OFS  (9)                             /* !< PRIV_ECAP1 Offset */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_ECAP1_MASK ((uint32_t)0x00000200U)         /* !< Privilege access for ECAP1 */
/* GSC_PPC_PRIVATTRIB_TIMER[PRIV_EQEP0] Bits */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_EQEP0_OFS  (16)                            /* !< PRIV_EQEP0 Offset */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_EQEP0_MASK ((uint32_t)0x00010000U)         /* !< Privilege access for EQEP0 */
/* GSC_PPC_PRIVATTRIB_TIMER[PRIV_EQEP1] Bits */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_EQEP1_OFS  (17)                            /* !< PRIV_EQEP1 Offset */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_EQEP1_MASK ((uint32_t)0x00020000U)         /* !< Privilege access for EQEP1 */
/* GSC_PPC_PRIVATTRIB_TIMER[PRIV_EQEP2] Bits */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_EQEP2_OFS  (18)                            /* !< PRIV_EQEP2 Offset */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_EQEP2_MASK ((uint32_t)0x00040000U)         /* !< Privilege access for EQEP2 */
/* GSC_PPC_PRIVATTRIB_TIMER[PRIV_TIMG4_0] Bits */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_TIMG4_0_OFS (24)                            /* !< PRIV_TIMG4_0 Offset */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_TIMG4_0_MASK ((uint32_t)0x01000000U)         /* !< Privilege access for TIMG4_0 */
/* GSC_PPC_PRIVATTRIB_TIMER[PRIV_TIMG12_0] Bits */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_TIMG12_0_OFS (25)                            /* !< PRIV_TIMG12_0 Offset */
#define GSC_PPC_PRIVATTRIB_TIMER_PRIV_TIMG12_0_MASK ((uint32_t)0x02000000U)         /* !< Privilege access for TIMG12_0 */

/* GSC_PPC_PRIVATTRIB_UNICOMM Bits */
/* GSC_PPC_PRIVATTRIB_UNICOMM[PRIV_S0U0] Bits */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S0U0_OFS (0)                             /* !< PRIV_S0U0 Offset */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S0U0_MASK ((uint32_t)0x00000001U)         /* !< Privilege access for UniComm S0U0 */
/* GSC_PPC_PRIVATTRIB_UNICOMM[PRIV_S0U1] Bits */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S0U1_OFS (1)                             /* !< PRIV_S0U1 Offset */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S0U1_MASK ((uint32_t)0x00000002U)         /* !< Privilege access for UniComm S0U1 */
/* GSC_PPC_PRIVATTRIB_UNICOMM[PRIV_S0U2] Bits */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S0U2_OFS (2)                             /* !< PRIV_S0U2 Offset */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S0U2_MASK ((uint32_t)0x00000004U)         /* !< Privilege access for UniComm S0U2 */
/* GSC_PPC_PRIVATTRIB_UNICOMM[PRIV_S1U3] Bits */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S1U3_OFS (3)                             /* !< PRIV_S1U3 Offset */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S1U3_MASK ((uint32_t)0x00000008U)         /* !< Privilege access for UniComm S1U3 */
/* GSC_PPC_PRIVATTRIB_UNICOMM[PRIV_S1U4] Bits */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S1U4_OFS (4)                             /* !< PRIV_S1U4 Offset */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S1U4_MASK ((uint32_t)0x00000010U)         /* !< Privilege access for UniComm S1U4 */
/* GSC_PPC_PRIVATTRIB_UNICOMM[PRIV_S1U5] Bits */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S1U5_OFS (5)                             /* !< PRIV_S1U5 Offset */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S1U5_MASK ((uint32_t)0x00000020U)         /* !< Privilege access for UniComm S1U5 */
/* GSC_PPC_PRIVATTRIB_UNICOMM[PRIV_S0_COMMON] Bits */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S0_COMMON_OFS (24)                            /* !< PRIV_S0_COMMON Offset */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S0_COMMON_MASK ((uint32_t)0x01000000U)         /* !< Privilege access for UniComm S0
                                                                                    common region */
/* GSC_PPC_PRIVATTRIB_UNICOMM[PRIV_S1_COMMON] Bits */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S1_COMMON_OFS (25)                            /* !< PRIV_S1_COMMON Offset */
#define GSC_PPC_PRIVATTRIB_UNICOMM_PRIV_S1_COMMON_MASK ((uint32_t)0x02000000U)         /* !< Privilege access for UniComm S1
                                                                                    common region */

/* GSC_PPC_PRIVATTRIB_GPIO Bits */
/* GSC_PPC_PRIVATTRIB_GPIO[PRIV_GPIO0] Bits */
#define GSC_PPC_PRIVATTRIB_GPIO_PRIV_GPIO0_OFS   (0)                             /* !< PRIV_GPIO0 Offset */
#define GSC_PPC_PRIVATTRIB_GPIO_PRIV_GPIO0_MASK  ((uint32_t)0x00000001U)         /* !< Privilege access for GPIO0 */
/* GSC_PPC_PRIVATTRIB_GPIO[PRIV_GPIO1] Bits */
#define GSC_PPC_PRIVATTRIB_GPIO_PRIV_GPIO1_OFS   (1)                             /* !< PRIV_GPIO1 Offset */
#define GSC_PPC_PRIVATTRIB_GPIO_PRIV_GPIO1_MASK  ((uint32_t)0x00000002U)         /* !< Privilege access for GPIO1 */
/* GSC_PPC_PRIVATTRIB_GPIO[PRIV_GPIO2] Bits */
#define GSC_PPC_PRIVATTRIB_GPIO_PRIV_GPIO2_OFS   (2)                             /* !< PRIV_GPIO2 Offset */
#define GSC_PPC_PRIVATTRIB_GPIO_PRIV_GPIO2_MASK  ((uint32_t)0x00000004U)         /* !< Privilege access for GPIO2 */
/* GSC_PPC_PRIVATTRIB_GPIO[PRIV_GPIO3] Bits */
#define GSC_PPC_PRIVATTRIB_GPIO_PRIV_GPIO3_OFS   (3)                             /* !< PRIV_GPIO3 Offset */
#define GSC_PPC_PRIVATTRIB_GPIO_PRIV_GPIO3_MASK  ((uint32_t)0x00000008U)         /* !< Privilege access for GPIO3 */

/* GSC_PPC_PRIVATTRIB_MCAN Bits */
/* GSC_PPC_PRIVATTRIB_MCAN[PRIV_MCAN] Bits */
#define GSC_PPC_PRIVATTRIB_MCAN_PRIV_MCAN_OFS    (0)                             /* !< PRIV_MCAN Offset */
#define GSC_PPC_PRIVATTRIB_MCAN_PRIV_MCAN_MASK   ((uint32_t)0x00000001U)         /* !< Privilege access for MCAN */

/* GSC_PPC_PRIVATTRIB_CMPSS Bits */
/* GSC_PPC_PRIVATTRIB_CMPSS[PRIV_CMPSS0] Bits */
#define GSC_PPC_PRIVATTRIB_CMPSS_PRIV_CMPSS0_OFS (0)                             /* !< PRIV_CMPSS0 Offset */
#define GSC_PPC_PRIVATTRIB_CMPSS_PRIV_CMPSS0_MASK ((uint32_t)0x00000001U)         /* !< Privilege access for CMPSS0 */
/* GSC_PPC_PRIVATTRIB_CMPSS[PRIV_CMPSS1] Bits */
#define GSC_PPC_PRIVATTRIB_CMPSS_PRIV_CMPSS1_OFS (1)                             /* !< PRIV_CMPSS1 Offset */
#define GSC_PPC_PRIVATTRIB_CMPSS_PRIV_CMPSS1_MASK ((uint32_t)0x00000002U)         /* !< Privilege access for CMPSS1 */
/* GSC_PPC_PRIVATTRIB_CMPSS[PRIV_CMPSS2] Bits */
#define GSC_PPC_PRIVATTRIB_CMPSS_PRIV_CMPSS2_OFS (2)                             /* !< PRIV_CMPSS2 Offset */
#define GSC_PPC_PRIVATTRIB_CMPSS_PRIV_CMPSS2_MASK ((uint32_t)0x00000004U)         /* !< Privilege access for CMPSS2 */
/* GSC_PPC_PRIVATTRIB_CMPSS[PRIV_CMPSS3] Bits */
#define GSC_PPC_PRIVATTRIB_CMPSS_PRIV_CMPSS3_OFS (3)                             /* !< PRIV_CMPSS3 Offset */
#define GSC_PPC_PRIVATTRIB_CMPSS_PRIV_CMPSS3_MASK ((uint32_t)0x00000008U)         /* !< Privilege access for CMPSS3 */

/* GSC_PPC_PRIVATTRIB_WDT Bits */
/* GSC_PPC_PRIVATTRIB_WDT[PRIV_WWDT] Bits */
#define GSC_PPC_PRIVATTRIB_WDT_PRIV_WWDT_OFS     (0)                             /* !< PRIV_WWDT Offset */
#define GSC_PPC_PRIVATTRIB_WDT_PRIV_WWDT_MASK    ((uint32_t)0x00000001U)         /* !< Privilege access for Windowed
                                                                                    Watchdog */

/* GSC_PPC_PRIVATTRIB_CRC Bits */
/* GSC_PPC_PRIVATTRIB_CRC[PRIV_CRC] Bits */
#define GSC_PPC_PRIVATTRIB_CRC_PRIV_CRC_OFS      (0)                             /* !< PRIV_CRC Offset */
#define GSC_PPC_PRIVATTRIB_CRC_PRIV_CRC_MASK     ((uint32_t)0x00000001U)         /* !< Privilege access for CRC */

/* GSC_PPC_PRIVATTRIB_AES Bits */
/* GSC_PPC_PRIVATTRIB_AES[PRIV_AES] Bits */
#define GSC_PPC_PRIVATTRIB_AES_PRIV_AES_OFS      (0)                             /* !< PRIV_AES Offset */
#define GSC_PPC_PRIVATTRIB_AES_PRIV_AES_MASK     ((uint32_t)0x00000001U)         /* !< Privilege access for AES */

/* GSC_PPC_PRIVATTRIB_IOMUX Bits */
/* GSC_PPC_PRIVATTRIB_IOMUX[PRIV_IOMUX] Bits */
#define GSC_PPC_PRIVATTRIB_IOMUX_PRIV_IOMUX_OFS  (0)                             /* !< PRIV_IOMUX Offset */
#define GSC_PPC_PRIVATTRIB_IOMUX_PRIV_IOMUX_MASK ((uint32_t)0x00000001U)         /* !< Privilege access for IOMUX */

/* GSC_PPC_PRIVATTRIB_DEBUGSS Bits */
/* GSC_PPC_PRIVATTRIB_DEBUGSS[PRIV_DEBUGSS] Bits */
#define GSC_PPC_PRIVATTRIB_DEBUGSS_PRIV_DEBUGSS_OFS (0)                             /* !< PRIV_DEBUGSS Offset */
#define GSC_PPC_PRIVATTRIB_DEBUGSS_PRIV_DEBUGSS_MASK ((uint32_t)0x00000001U)         /* !< Privilege access for DEBUGSS */

/* GSC_PPC_PRIVATTRIB_KEYSTORECTL Bits */
/* GSC_PPC_PRIVATTRIB_KEYSTORECTL[PRIV_KEYSTORECTL] Bits */
#define GSC_PPC_PRIVATTRIB_KEYSTORECTL_PRIV_KEYSTORECTL_OFS (0)                             /* !< PRIV_KEYSTORECTL Offset */
#define GSC_PPC_PRIVATTRIB_KEYSTORECTL_PRIV_KEYSTORECTL_MASK ((uint32_t)0x00000001U)         /* !< Privilege access for KEYSTORECTL */

/* GSC_PPC_PRIVATTRIB_EAM Bits */
/* GSC_PPC_PRIVATTRIB_EAM[PRIV_EAM] Bits */
#define GSC_PPC_PRIVATTRIB_EAM_PRIV_EAM_OFS      (0)                             /* !< PRIV_EAM Offset */
#define GSC_PPC_PRIVATTRIB_EAM_PRIV_EAM_MASK     ((uint32_t)0x00000001U)         /* !< Privilege access for EAM */

/* GSC_PPC_PRIVATTRIB_WUC Bits */
/* GSC_PPC_PRIVATTRIB_WUC[PRIV_WUC] Bits */
#define GSC_PPC_PRIVATTRIB_WUC_PRIV_WUC_OFS      (0)                             /* !< PRIV_WUC Offset */
#define GSC_PPC_PRIVATTRIB_WUC_PRIV_WUC_MASK     ((uint32_t)0x00000001U)         /* !< Privilege access for WUC */

/* GSC_PPC_PRIVATTRIB_FRIREGS Bits */
/* GSC_PPC_PRIVATTRIB_FRIREGS[PRIV_FRIREGS] Bits */
#define GSC_PPC_PRIVATTRIB_FRIREGS_PRIV_FRIREGS_OFS (0)                             /* !< PRIV_FRIREGS Offset */
#define GSC_PPC_PRIVATTRIB_FRIREGS_PRIV_FRIREGS_MASK ((uint32_t)0x00000001U)         /* !< Privilege access for FRIREGS */

/* GSC_PPC_PRIVATTRIB_MEMCFG Bits */
/* GSC_PPC_PRIVATTRIB_MEMCFG[PRIV_MEMCFG] Bits */
#define GSC_PPC_PRIVATTRIB_MEMCFG_PRIV_MEMCFG_OFS (0)                             /* !< PRIV_MEMCFG Offset */
#define GSC_PPC_PRIVATTRIB_MEMCFG_PRIV_MEMCFG_MASK ((uint32_t)0x00000001U)         /* !< Privilege access for MEMCFG */

/* GSC_PPC_PRIVATTRIB_SYSCTL Bits */
/* GSC_PPC_PRIVATTRIB_SYSCTL[PRIV_SYSCTL] Bits */
#define GSC_PPC_PRIVATTRIB_SYSCTL_PRIV_SYSCTL_OFS (0)                             /* !< PRIV_SYSCTL Offset */
#define GSC_PPC_PRIVATTRIB_SYSCTL_PRIV_SYSCTL_MASK ((uint32_t)0x00000001U)         /* !< Privilege access for SYSCTL */

/* GSC_PPC_PRIVATTRIB_DMA Bits */
/* GSC_PPC_PRIVATTRIB_DMA[PRIV_DMA] Bits */
#define GSC_PPC_PRIVATTRIB_DMA_PRIV_DMA_OFS      (0)                             /* !< PRIV_DMA Offset */
#define GSC_PPC_PRIVATTRIB_DMA_PRIV_DMA_MASK     ((uint32_t)0x00000001U)         /* !< Privilege access for DMA */

/* GSC_PPC_PRIVATTRIB_GSC Bits */
/* GSC_PPC_PRIVATTRIB_GSC[PRIV_GSC] Bits */
#define GSC_PPC_PRIVATTRIB_GSC_PRIV_GSC_OFS      (0)                             /* !< PRIV_GSC Offset */
#define GSC_PPC_PRIVATTRIB_GSC_PRIV_GSC_MASK     ((uint32_t)0x00000001U)         /* !< Privilege access for GSC */

/* GSC_PPC_PRIVATTRIB_COPROC Bits */
/* GSC_PPC_PRIVATTRIB_COPROC[PRIV_TINIE] Bits */
#define GSC_PPC_PRIVATTRIB_COPROC_PRIV_TINIE_OFS (0)                             /* !< PRIV_TINIE Offset */
#define GSC_PPC_PRIVATTRIB_COPROC_PRIV_TINIE_MASK ((uint32_t)0x00000001U)         /* !< Privilege access for TINIE */

/* GSC_PPC_PRIVATTRIB_EPI Bits */
/* GSC_PPC_PRIVATTRIB_EPI[PRIV_EPI] Bits */
#define GSC_PPC_PRIVATTRIB_EPI_PRIV_EPI_OFS      (0)                             /* !< PRIV_EPI Offset */
#define GSC_PPC_PRIVATTRIB_EPI_PRIV_EPI_MASK     ((uint32_t)0x00000001U)         /* !< Privilege access for EPI */

/* GSC_PPC_PRIVATTRIB_PGA Bits */
/* GSC_PPC_PRIVATTRIB_PGA[PRIV_PGA0] Bits */
#define GSC_PPC_PRIVATTRIB_PGA_PRIV_PGA0_OFS     (0)                             /* !< PRIV_PGA0 Offset */
#define GSC_PPC_PRIVATTRIB_PGA_PRIV_PGA0_MASK    ((uint32_t)0x00000001U)         /* !< Privilege access for PGA0 */
/* GSC_PPC_PRIVATTRIB_PGA[PRIV_PGA1] Bits */
#define GSC_PPC_PRIVATTRIB_PGA_PRIV_PGA1_OFS     (1)                             /* !< PRIV_PGA1 Offset */
#define GSC_PPC_PRIVATTRIB_PGA_PRIV_PGA1_MASK    ((uint32_t)0x00000002U)         /* !< Privilege access for PGA1 */
/* GSC_PPC_PRIVATTRIB_PGA[PRIV_PGA2] Bits */
#define GSC_PPC_PRIVATTRIB_PGA_PRIV_PGA2_OFS     (2)                             /* !< PRIV_PGA2 Offset */
#define GSC_PPC_PRIVATTRIB_PGA_PRIV_PGA2_MASK    ((uint32_t)0x00000004U)         /* !< Privilege access for PGA2 */

/* GSC_PPC_PRIVATTRIB_XBAR Bits */
/* GSC_PPC_PRIVATTRIB_XBAR[PRIV_ALL_XBAR_CONFIG] Bits */
#define GSC_PPC_PRIVATTRIB_XBAR_PRIV_ALL_XBAR_CONFIG_OFS (0)                             /* !< PRIV_ALL_XBAR_CONFIG Offset */
#define GSC_PPC_PRIVATTRIB_XBAR_PRIV_ALL_XBAR_CONFIG_MASK ((uint32_t)0x00000001U)         /* !< Privilege access for
                                                                                    ALL_XBAR_CONFIG */
/* GSC_PPC_PRIVATTRIB_XBAR[PRIV_XBAR_INPUT_FLAGS] Bits */
#define GSC_PPC_PRIVATTRIB_XBAR_PRIV_XBAR_INPUT_FLAGS_OFS (1)                             /* !< PRIV_XBAR_INPUT_FLAGS Offset */
#define GSC_PPC_PRIVATTRIB_XBAR_PRIV_XBAR_INPUT_FLAGS_MASK ((uint32_t)0x00000002U)         /* !< Privilege access for
                                                                                    XBAR_INPUT_FLAGS */
/* GSC_PPC_PRIVATTRIB_XBAR[PRIV_OUTPUT_XBAR_FLAGS] Bits */
#define GSC_PPC_PRIVATTRIB_XBAR_PRIV_OUTPUT_XBAR_FLAGS_OFS (2)                             /* !< PRIV_OUTPUT_XBAR_FLAGS Offset */
#define GSC_PPC_PRIVATTRIB_XBAR_PRIV_OUTPUT_XBAR_FLAGS_MASK ((uint32_t)0x00000004U)         /* !< Privilege access for
                                                                                    OUTPUT_XBAR_FLAGS */

/* GSC_SPC_PRIVATTRIB0 Bits */
/* GSC_SPC_PRIVATTRIB0[C0B0_512B] Bits */
#define GSC_SPC_PRIVATTRIB0_C0B0_512B_OFS        (0)                             /* !< C0B0_512B Offset */
#define GSC_SPC_PRIVATTRIB0_C0B0_512B_MASK       ((uint32_t)0x00000001U)         /* !< privilege access for first 512 byte
                                                                                    in chunk 0 */
/* GSC_SPC_PRIVATTRIB0[C0B1_512B] Bits */
#define GSC_SPC_PRIVATTRIB0_C0B1_512B_OFS        (1)                             /* !< C0B1_512B Offset */
#define GSC_SPC_PRIVATTRIB0_C0B1_512B_MASK       ((uint32_t)0x00000002U)         /* !< privilege access for second 512
                                                                                    byte in chunk 0 */
/* GSC_SPC_PRIVATTRIB0[C0B0_1KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C0B0_1KB_OFS         (2)                             /* !< C0B0_1KB Offset */
#define GSC_SPC_PRIVATTRIB0_C0B0_1KB_MASK        ((uint32_t)0x00000004U)         /* !< privilege access for 1KB in chunk 0 */
/* GSC_SPC_PRIVATTRIB0[C0B0_2KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C0B0_2KB_OFS         (3)                             /* !< C0B0_2KB Offset */
#define GSC_SPC_PRIVATTRIB0_C0B0_2KB_MASK        ((uint32_t)0x00000008U)         /* !< privilege access for 2KB in chunk 0 */
/* GSC_SPC_PRIVATTRIB0[C0B0_4KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C0B0_4KB_OFS         (4)                             /* !< C0B0_4KB Offset */
#define GSC_SPC_PRIVATTRIB0_C0B0_4KB_MASK        ((uint32_t)0x00000010U)         /* !< privilege access for first 4KB in
                                                                                    chunk 0 */
/* GSC_SPC_PRIVATTRIB0[C0B1_4KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C0B1_4KB_OFS         (5)                             /* !< C0B1_4KB Offset */
#define GSC_SPC_PRIVATTRIB0_C0B1_4KB_MASK        ((uint32_t)0x00000020U)         /* !< privilege access for second 4KB in
                                                                                    chunk 0 */
/* GSC_SPC_PRIVATTRIB0[C0B2_4KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C0B2_4KB_OFS         (6)                             /* !< C0B2_4KB Offset */
#define GSC_SPC_PRIVATTRIB0_C0B2_4KB_MASK        ((uint32_t)0x00000040U)         /* !< privilege access for third 4KB in
                                                                                    chunk 0 */
/* GSC_SPC_PRIVATTRIB0[C1B0_512B] Bits */
#define GSC_SPC_PRIVATTRIB0_C1B0_512B_OFS        (8)                             /* !< C1B0_512B Offset */
#define GSC_SPC_PRIVATTRIB0_C1B0_512B_MASK       ((uint32_t)0x00000100U)         /* !< privilege access for first 512 byte
                                                                                    in chunk 1 */
/* GSC_SPC_PRIVATTRIB0[C1B1_512B] Bits */
#define GSC_SPC_PRIVATTRIB0_C1B1_512B_OFS        (9)                             /* !< C1B1_512B Offset */
#define GSC_SPC_PRIVATTRIB0_C1B1_512B_MASK       ((uint32_t)0x00000200U)         /* !< privilege access for second 512
                                                                                    byte in chunk 1 */
/* GSC_SPC_PRIVATTRIB0[C1B0_1KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C1B0_1KB_OFS         (10)                            /* !< C1B0_1KB Offset */
#define GSC_SPC_PRIVATTRIB0_C1B0_1KB_MASK        ((uint32_t)0x00000400U)         /* !< privilege access for 1KB in chunk 1 */
/* GSC_SPC_PRIVATTRIB0[C1B0_2KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C1B0_2KB_OFS         (11)                            /* !< C1B0_2KB Offset */
#define GSC_SPC_PRIVATTRIB0_C1B0_2KB_MASK        ((uint32_t)0x00000800U)         /* !< privilege access for 2KB in chunk 1 */
/* GSC_SPC_PRIVATTRIB0[C1B0_4KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C1B0_4KB_OFS         (12)                            /* !< C1B0_4KB Offset */
#define GSC_SPC_PRIVATTRIB0_C1B0_4KB_MASK        ((uint32_t)0x00001000U)         /* !< privilege access for first 4KB in
                                                                                    chunk 1 */
/* GSC_SPC_PRIVATTRIB0[C1B1_4KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C1B1_4KB_OFS         (13)                            /* !< C1B1_4KB Offset */
#define GSC_SPC_PRIVATTRIB0_C1B1_4KB_MASK        ((uint32_t)0x00002000U)         /* !< privilege access for second 4KB in
                                                                                    chunk 1 */
/* GSC_SPC_PRIVATTRIB0[C1B2_4KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C1B2_4KB_OFS         (14)                            /* !< C1B2_4KB Offset */
#define GSC_SPC_PRIVATTRIB0_C1B2_4KB_MASK        ((uint32_t)0x00004000U)         /* !< privilege access for third 4KB in
                                                                                    chunk 1 */
/* GSC_SPC_PRIVATTRIB0[C2B0_512B] Bits */
#define GSC_SPC_PRIVATTRIB0_C2B0_512B_OFS        (16)                            /* !< C2B0_512B Offset */
#define GSC_SPC_PRIVATTRIB0_C2B0_512B_MASK       ((uint32_t)0x00010000U)         /* !< privilege access for first 512 byte
                                                                                    in chunk 2 */
/* GSC_SPC_PRIVATTRIB0[C2B1_512B] Bits */
#define GSC_SPC_PRIVATTRIB0_C2B1_512B_OFS        (17)                            /* !< C2B1_512B Offset */
#define GSC_SPC_PRIVATTRIB0_C2B1_512B_MASK       ((uint32_t)0x00020000U)         /* !< privilege access for second 512
                                                                                    byte in chunk 2 */
/* GSC_SPC_PRIVATTRIB0[C2B0_1KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C2B0_1KB_OFS         (18)                            /* !< C2B0_1KB Offset */
#define GSC_SPC_PRIVATTRIB0_C2B0_1KB_MASK        ((uint32_t)0x00040000U)         /* !< privilege access for 1KB in chunk 2 */
/* GSC_SPC_PRIVATTRIB0[C2B0_2KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C2B0_2KB_OFS         (19)                            /* !< C2B0_2KB Offset */
#define GSC_SPC_PRIVATTRIB0_C2B0_2KB_MASK        ((uint32_t)0x00080000U)         /* !< privilege access for 2KB in chunk 2 */
/* GSC_SPC_PRIVATTRIB0[C2B0_4KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C2B0_4KB_OFS         (20)                            /* !< C2B0_4KB Offset */
#define GSC_SPC_PRIVATTRIB0_C2B0_4KB_MASK        ((uint32_t)0x00100000U)         /* !< privilege access for first 4KB in
                                                                                    chunk 2 */
/* GSC_SPC_PRIVATTRIB0[C2B1_4KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C2B1_4KB_OFS         (21)                            /* !< C2B1_4KB Offset */
#define GSC_SPC_PRIVATTRIB0_C2B1_4KB_MASK        ((uint32_t)0x00200000U)         /* !< privilege access for second 4KB in
                                                                                    chunk 2 */
/* GSC_SPC_PRIVATTRIB0[C2B2_4KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C2B2_4KB_OFS         (22)                            /* !< C2B2_4KB Offset */
#define GSC_SPC_PRIVATTRIB0_C2B2_4KB_MASK        ((uint32_t)0x00400000U)         /* !< privilege access for third 4KB in
                                                                                    chunk 2 */
/* GSC_SPC_PRIVATTRIB0[C3B0_512B] Bits */
#define GSC_SPC_PRIVATTRIB0_C3B0_512B_OFS        (24)                            /* !< C3B0_512B Offset */
#define GSC_SPC_PRIVATTRIB0_C3B0_512B_MASK       ((uint32_t)0x01000000U)         /* !< privilege access for first 512 byte
                                                                                    in chunk 3 */
/* GSC_SPC_PRIVATTRIB0[C3B1_512B] Bits */
#define GSC_SPC_PRIVATTRIB0_C3B1_512B_OFS        (25)                            /* !< C3B1_512B Offset */
#define GSC_SPC_PRIVATTRIB0_C3B1_512B_MASK       ((uint32_t)0x02000000U)         /* !< privilege access for second 512
                                                                                    byte in chunk 3 */
/* GSC_SPC_PRIVATTRIB0[C3B0_1KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C3B0_1KB_OFS         (26)                            /* !< C3B0_1KB Offset */
#define GSC_SPC_PRIVATTRIB0_C3B0_1KB_MASK        ((uint32_t)0x04000000U)         /* !< privilege access for 1KB in chunk 3 */
/* GSC_SPC_PRIVATTRIB0[C3B0_2KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C3B0_2KB_OFS         (27)                            /* !< C3B0_2KB Offset */
#define GSC_SPC_PRIVATTRIB0_C3B0_2KB_MASK        ((uint32_t)0x08000000U)         /* !< privilege access for 2KB in chunk 3 */
/* GSC_SPC_PRIVATTRIB0[C3B0_4KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C3B0_4KB_OFS         (28)                            /* !< C3B0_4KB Offset */
#define GSC_SPC_PRIVATTRIB0_C3B0_4KB_MASK        ((uint32_t)0x10000000U)         /* !< privilege access for first 4KB in
                                                                                    chunk 3 */
/* GSC_SPC_PRIVATTRIB0[C3B1_4KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C3B1_4KB_OFS         (29)                            /* !< C3B1_4KB Offset */
#define GSC_SPC_PRIVATTRIB0_C3B1_4KB_MASK        ((uint32_t)0x20000000U)         /* !< privilege access for second 4KB in
                                                                                    chunk 3 */
/* GSC_SPC_PRIVATTRIB0[C3B2_4KB] Bits */
#define GSC_SPC_PRIVATTRIB0_C3B2_4KB_OFS         (30)                            /* !< C3B2_4KB Offset */
#define GSC_SPC_PRIVATTRIB0_C3B2_4KB_MASK        ((uint32_t)0x40000000U)         /* !< privilege access for third 4KB in
                                                                                    chunk 3 */

/* GSC_SPC_PRIVATTRIB1 Bits */
/* GSC_SPC_PRIVATTRIB1[C0B0_512B] Bits */
#define GSC_SPC_PRIVATTRIB1_C0B0_512B_OFS        (0)                             /* !< C0B0_512B Offset */
#define GSC_SPC_PRIVATTRIB1_C0B0_512B_MASK       ((uint32_t)0x00000001U)         /* !< privilege access for first 512 byte
                                                                                    in chunk 0 */
/* GSC_SPC_PRIVATTRIB1[C0B1_512B] Bits */
#define GSC_SPC_PRIVATTRIB1_C0B1_512B_OFS        (1)                             /* !< C0B1_512B Offset */
#define GSC_SPC_PRIVATTRIB1_C0B1_512B_MASK       ((uint32_t)0x00000002U)         /* !< privilege access for second 512
                                                                                    byte in chunk 0 */
/* GSC_SPC_PRIVATTRIB1[C0B0_1KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C0B0_1KB_OFS         (2)                             /* !< C0B0_1KB Offset */
#define GSC_SPC_PRIVATTRIB1_C0B0_1KB_MASK        ((uint32_t)0x00000004U)         /* !< privilege access for 1KB in chunk 0 */
/* GSC_SPC_PRIVATTRIB1[C0B0_2KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C0B0_2KB_OFS         (3)                             /* !< C0B0_2KB Offset */
#define GSC_SPC_PRIVATTRIB1_C0B0_2KB_MASK        ((uint32_t)0x00000008U)         /* !< privilege access for 2KB in chunk 0 */
/* GSC_SPC_PRIVATTRIB1[C0B0_4KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C0B0_4KB_OFS         (4)                             /* !< C0B0_4KB Offset */
#define GSC_SPC_PRIVATTRIB1_C0B0_4KB_MASK        ((uint32_t)0x00000010U)         /* !< privilege access for first 4KB in
                                                                                    chunk 0 */
/* GSC_SPC_PRIVATTRIB1[C0B1_4KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C0B1_4KB_OFS         (5)                             /* !< C0B1_4KB Offset */
#define GSC_SPC_PRIVATTRIB1_C0B1_4KB_MASK        ((uint32_t)0x00000020U)         /* !< privilege access for second 4KB in
                                                                                    chunk 0 */
/* GSC_SPC_PRIVATTRIB1[C0B2_4KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C0B2_4KB_OFS         (6)                             /* !< C0B2_4KB Offset */
#define GSC_SPC_PRIVATTRIB1_C0B2_4KB_MASK        ((uint32_t)0x00000040U)         /* !< privilege access for third 4KB in
                                                                                    chunk 0 */
/* GSC_SPC_PRIVATTRIB1[C1B0_512B] Bits */
#define GSC_SPC_PRIVATTRIB1_C1B0_512B_OFS        (8)                             /* !< C1B0_512B Offset */
#define GSC_SPC_PRIVATTRIB1_C1B0_512B_MASK       ((uint32_t)0x00000100U)         /* !< privilege access for first 512 byte
                                                                                    in chunk 1 */
/* GSC_SPC_PRIVATTRIB1[C1B1_512B] Bits */
#define GSC_SPC_PRIVATTRIB1_C1B1_512B_OFS        (9)                             /* !< C1B1_512B Offset */
#define GSC_SPC_PRIVATTRIB1_C1B1_512B_MASK       ((uint32_t)0x00000200U)         /* !< privilege access for second 512
                                                                                    byte in chunk 1 */
/* GSC_SPC_PRIVATTRIB1[C1B0_1KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C1B0_1KB_OFS         (10)                            /* !< C1B0_1KB Offset */
#define GSC_SPC_PRIVATTRIB1_C1B0_1KB_MASK        ((uint32_t)0x00000400U)         /* !< privilege access for 1KB in chunk 1 */
/* GSC_SPC_PRIVATTRIB1[C1B0_2KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C1B0_2KB_OFS         (11)                            /* !< C1B0_2KB Offset */
#define GSC_SPC_PRIVATTRIB1_C1B0_2KB_MASK        ((uint32_t)0x00000800U)         /* !< privilege access for 2KB in chunk 1 */
/* GSC_SPC_PRIVATTRIB1[C1B0_4KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C1B0_4KB_OFS         (12)                            /* !< C1B0_4KB Offset */
#define GSC_SPC_PRIVATTRIB1_C1B0_4KB_MASK        ((uint32_t)0x00001000U)         /* !< privilege access for first 4KB in
                                                                                    chunk 1 */
/* GSC_SPC_PRIVATTRIB1[C1B1_4KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C1B1_4KB_OFS         (13)                            /* !< C1B1_4KB Offset */
#define GSC_SPC_PRIVATTRIB1_C1B1_4KB_MASK        ((uint32_t)0x00002000U)         /* !< privilege access for second 4KB in
                                                                                    chunk 1 */
/* GSC_SPC_PRIVATTRIB1[C1B2_4KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C1B2_4KB_OFS         (14)                            /* !< C1B2_4KB Offset */
#define GSC_SPC_PRIVATTRIB1_C1B2_4KB_MASK        ((uint32_t)0x00004000U)         /* !< privilege access for third 4KB in
                                                                                    chunk 1 */
/* GSC_SPC_PRIVATTRIB1[C2B0_512B] Bits */
#define GSC_SPC_PRIVATTRIB1_C2B0_512B_OFS        (16)                            /* !< C2B0_512B Offset */
#define GSC_SPC_PRIVATTRIB1_C2B0_512B_MASK       ((uint32_t)0x00010000U)         /* !< privilege access for first 512 byte
                                                                                    in chunk 2 */
/* GSC_SPC_PRIVATTRIB1[C2B1_512B] Bits */
#define GSC_SPC_PRIVATTRIB1_C2B1_512B_OFS        (17)                            /* !< C2B1_512B Offset */
#define GSC_SPC_PRIVATTRIB1_C2B1_512B_MASK       ((uint32_t)0x00020000U)         /* !< privilege access for second 512
                                                                                    byte in chunk 2 */
/* GSC_SPC_PRIVATTRIB1[C2B0_1KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C2B0_1KB_OFS         (18)                            /* !< C2B0_1KB Offset */
#define GSC_SPC_PRIVATTRIB1_C2B0_1KB_MASK        ((uint32_t)0x00040000U)         /* !< privilege access for 1KB in chunk 2 */
/* GSC_SPC_PRIVATTRIB1[C2B0_2KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C2B0_2KB_OFS         (19)                            /* !< C2B0_2KB Offset */
#define GSC_SPC_PRIVATTRIB1_C2B0_2KB_MASK        ((uint32_t)0x00080000U)         /* !< privilege access for 2KB in chunk 2 */
/* GSC_SPC_PRIVATTRIB1[C2B0_4KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C2B0_4KB_OFS         (20)                            /* !< C2B0_4KB Offset */
#define GSC_SPC_PRIVATTRIB1_C2B0_4KB_MASK        ((uint32_t)0x00100000U)         /* !< privilege access for first 4KB in
                                                                                    chunk 2 */
/* GSC_SPC_PRIVATTRIB1[C2B1_4KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C2B1_4KB_OFS         (21)                            /* !< C2B1_4KB Offset */
#define GSC_SPC_PRIVATTRIB1_C2B1_4KB_MASK        ((uint32_t)0x00200000U)         /* !< privilege access for second 4KB in
                                                                                    chunk 2 */
/* GSC_SPC_PRIVATTRIB1[C2B2_4KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C2B2_4KB_OFS         (22)                            /* !< C2B2_4KB Offset */
#define GSC_SPC_PRIVATTRIB1_C2B2_4KB_MASK        ((uint32_t)0x00400000U)         /* !< privilege access for third 4KB in
                                                                                    chunk 2 */
/* GSC_SPC_PRIVATTRIB1[C3B0_512B] Bits */
#define GSC_SPC_PRIVATTRIB1_C3B0_512B_OFS        (24)                            /* !< C3B0_512B Offset */
#define GSC_SPC_PRIVATTRIB1_C3B0_512B_MASK       ((uint32_t)0x01000000U)         /* !< privilege access for first 512 byte
                                                                                    in chunk 3 */
/* GSC_SPC_PRIVATTRIB1[C3B1_512B] Bits */
#define GSC_SPC_PRIVATTRIB1_C3B1_512B_OFS        (25)                            /* !< C3B1_512B Offset */
#define GSC_SPC_PRIVATTRIB1_C3B1_512B_MASK       ((uint32_t)0x02000000U)         /* !< privilege access for second 512
                                                                                    byte in chunk 3 */
/* GSC_SPC_PRIVATTRIB1[C3B0_1KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C3B0_1KB_OFS         (26)                            /* !< C3B0_1KB Offset */
#define GSC_SPC_PRIVATTRIB1_C3B0_1KB_MASK        ((uint32_t)0x04000000U)         /* !< privilege access for 1KB in chunk 3 */
/* GSC_SPC_PRIVATTRIB1[C3B0_2KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C3B0_2KB_OFS         (27)                            /* !< C3B0_2KB Offset */
#define GSC_SPC_PRIVATTRIB1_C3B0_2KB_MASK        ((uint32_t)0x08000000U)         /* !< privilege access for 2KB in chunk 3 */
/* GSC_SPC_PRIVATTRIB1[C3B0_4KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C3B0_4KB_OFS         (28)                            /* !< C3B0_4KB Offset */
#define GSC_SPC_PRIVATTRIB1_C3B0_4KB_MASK        ((uint32_t)0x10000000U)         /* !< privilege access for first 4KB in
                                                                                    chunk 3 */
/* GSC_SPC_PRIVATTRIB1[C3B1_4KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C3B1_4KB_OFS         (29)                            /* !< C3B1_4KB Offset */
#define GSC_SPC_PRIVATTRIB1_C3B1_4KB_MASK        ((uint32_t)0x20000000U)         /* !< privilege access for second 4KB in
                                                                                    chunk 3 */
/* GSC_SPC_PRIVATTRIB1[C3B2_4KB] Bits */
#define GSC_SPC_PRIVATTRIB1_C3B2_4KB_OFS         (30)                            /* !< C3B2_4KB Offset */
#define GSC_SPC_PRIVATTRIB1_C3B2_4KB_MASK        ((uint32_t)0x40000000U)         /* !< privilege access for third 4KB in
                                                                                    chunk 3 */

/* GSC_FPC_PRIVATTRIBA0 Bits */
/* GSC_FPC_PRIVATTRIBA0[PRIV_PAGE] Bits */
#define GSC_FPC_PRIVATTRIBA0_PRIV_PAGE_OFS       (0)                             /* !< PRIV_PAGE Offset */
#define GSC_FPC_PRIVATTRIBA0_PRIV_PAGE_MASK      ((uint32_t)0xFFFFFFFFU)         /* !< Privilege access for lower sectors
                                                                                    of Bank0 */

/* GSC_FPC_PRIVATTRIBA1 Bits */
/* GSC_FPC_PRIVATTRIBA1[PRIV_PAGE] Bits */
#define GSC_FPC_PRIVATTRIBA1_PRIV_PAGE_OFS       (0)                             /* !< PRIV_PAGE Offset */
#define GSC_FPC_PRIVATTRIBA1_PRIV_PAGE_MASK      ((uint32_t)0xFFFFFFFFU)         /* !< Privilege access for lower sectors
                                                                                    of Bank1 */

/* GSC_FPC_PRIVATTRIBB0 Bits */
/* GSC_FPC_PRIVATTRIBB0[PRIV_PAGE] Bits */
#define GSC_FPC_PRIVATTRIBB0_PRIV_PAGE_OFS       (4)                             /* !< PRIV_PAGE Offset */
#define GSC_FPC_PRIVATTRIBB0_PRIV_PAGE_MASK      ((uint32_t)0x0000FFF0U)         /* !< Privilege access for higher sectors
                                                                                    of Bank0 */

/* GSC_FPC_PRIVATTRIBB1 Bits */
/* GSC_FPC_PRIVATTRIBB1[PRIV_PAGE] Bits */
#define GSC_FPC_PRIVATTRIBB1_PRIV_PAGE_OFS       (4)                             /* !< PRIV_PAGE Offset */
#define GSC_FPC_PRIVATTRIBB1_PRIV_PAGE_MASK      ((uint32_t)0x0000FFF0U)         /* !< Privilege access for higher sectors
                                                                                    of Bank1 */

/* GSC_FPC_NONMAIN_PRIVATTRIB0 Bits */
/* GSC_FPC_NONMAIN_PRIVATTRIB0[PRIV_PAGE] Bits */
#define GSC_FPC_NONMAIN_PRIVATTRIB0_PRIV_PAGE_OFS (0)                             /* !< PRIV_PAGE Offset */
#define GSC_FPC_NONMAIN_PRIVATTRIB0_PRIV_PAGE_MASK ((uint32_t)0x00000003U)         /* !< Privilege access for Nonmain region
                                                                                    of Bank0 */

/* GSC_FPC_NONMAIN_PRIVATTRIB1 Bits */
/* GSC_FPC_NONMAIN_PRIVATTRIB1[PRIV_PAGE] Bits */
#define GSC_FPC_NONMAIN_PRIVATTRIB1_PRIV_PAGE_OFS (0)                             /* !< PRIV_PAGE Offset */
#define GSC_FPC_NONMAIN_PRIVATTRIB1_PRIV_PAGE_MASK ((uint32_t)0x00000003U)         /* !< Privilege access for Nonmain region
                                                                                    of Bank1 */

/* GSC_FPC_TRIM_PRIVATTRIB0 Bits */
/* GSC_FPC_TRIM_PRIVATTRIB0[PRIV_PAGE] Bits */
#define GSC_FPC_TRIM_PRIVATTRIB0_PRIV_PAGE_OFS   (0)                             /* !< PRIV_PAGE Offset */
#define GSC_FPC_TRIM_PRIVATTRIB0_PRIV_PAGE_MASK  ((uint32_t)0x00000001U)         /* !< Privilege access for TRIM region of
                                                                                    Bank0 */

/* GSC_FPC_TRIM_PRIVATTRIB1 Bits */
/* GSC_FPC_TRIM_PRIVATTRIB1[PRIV_PAGE] Bits */
#define GSC_FPC_TRIM_PRIVATTRIB1_PRIV_PAGE_OFS   (0)                             /* !< PRIV_PAGE Offset */
#define GSC_FPC_TRIM_PRIVATTRIB1_PRIV_PAGE_MASK  ((uint32_t)0x00000001U)         /* !< Privilege access for TRIM region of
                                                                                    Bank1 */

/* GSC_FPC_ENGR_PRIVATTRIB0 Bits */
/* GSC_FPC_ENGR_PRIVATTRIB0[PRIV_PAGE] Bits */
#define GSC_FPC_ENGR_PRIVATTRIB0_PRIV_PAGE_OFS   (0)                             /* !< PRIV_PAGE Offset */
#define GSC_FPC_ENGR_PRIVATTRIB0_PRIV_PAGE_MASK  ((uint32_t)0x00000001U)         /* !< Privilege access for ENGR region of
                                                                                    Bank0 */

/* GSC_FPC_ENGR_PRIVATTRIB1 Bits */
/* GSC_FPC_ENGR_PRIVATTRIB1[PRIV_PAGE] Bits */
#define GSC_FPC_ENGR_PRIVATTRIB1_PRIV_PAGE_OFS   (0)                             /* !< PRIV_PAGE Offset */
#define GSC_FPC_ENGR_PRIVATTRIB1_PRIV_PAGE_MASK  ((uint32_t)0x00000001U)         /* !< Privilege access for ENGR region of
                                                                                    Bank1 */

/* GSC_FPC_WEPROTA0 Bits */
/* GSC_FPC_WEPROTA0[WEPROT_PAGE] Bits */
#define GSC_FPC_WEPROTA0_WEPROT_PAGE_OFS         (0)                             /* !< WEPROT_PAGE Offset */
#define GSC_FPC_WEPROTA0_WEPROT_PAGE_MASK        ((uint32_t)0xFFFFFFFFU)         /* !< Erase/program protection for lower
                                                                                    sectors of Flash Bank0 */

/* GSC_FPC_WEPROTA1 Bits */
/* GSC_FPC_WEPROTA1[WEPROT_PAGE] Bits */
#define GSC_FPC_WEPROTA1_WEPROT_PAGE_OFS         (0)                             /* !< WEPROT_PAGE Offset */
#define GSC_FPC_WEPROTA1_WEPROT_PAGE_MASK        ((uint32_t)0xFFFFFFFFU)         /* !< Erase/program protection for lower
                                                                                    sectors of Flash Bank1 */

/* GSC_FPC_WEPROTB0 Bits */
/* GSC_FPC_WEPROTB0[WEPROT_PAGE] Bits */
#define GSC_FPC_WEPROTB0_WEPROT_PAGE_OFS         (4)                             /* !< WEPROT_PAGE Offset */
#define GSC_FPC_WEPROTB0_WEPROT_PAGE_MASK        ((uint32_t)0x0000FFF0U)         /* !< Erase/program protection for higher
                                                                                    sectors of Flash Bank0 */

/* GSC_FPC_WEPROTB1 Bits */
/* GSC_FPC_WEPROTB1[WEPROT_PAGE] Bits */
#define GSC_FPC_WEPROTB1_WEPROT_PAGE_OFS         (4)                             /* !< WEPROT_PAGE Offset */
#define GSC_FPC_WEPROTB1_WEPROT_PAGE_MASK        ((uint32_t)0x0000FFF0U)         /* !< Erase/program protection for higher
                                                                                    sectors of Flash Bank1 */

/* GSC_FPC_WEPROTNONMAIN0 Bits */
/* GSC_FPC_WEPROTNONMAIN0[WEPROT_PAGE] Bits */
#define GSC_FPC_WEPROTNONMAIN0_WEPROT_PAGE_OFS   (0)                             /* !< WEPROT_PAGE Offset */
#define GSC_FPC_WEPROTNONMAIN0_WEPROT_PAGE_MASK  ((uint32_t)0x00000003U)         /* !< Erase/program protection for Flash
                                                                                    NONMAIN region of Bank0 */

/* GSC_FPC_WEPROTNONMAIN1 Bits */
/* GSC_FPC_WEPROTNONMAIN1[WEPROT_PAGE] Bits */
#define GSC_FPC_WEPROTNONMAIN1_WEPROT_PAGE_OFS   (0)                             /* !< WEPROT_PAGE Offset */
#define GSC_FPC_WEPROTNONMAIN1_WEPROT_PAGE_MASK  ((uint32_t)0x00000003U)         /* !< Erase/program protection for Flash
                                                                                    NONMAIN region of Bank1 */

/* GSC_FPC_WEPROTTRIM0 Bits */
/* GSC_FPC_WEPROTTRIM0[WEPROT_PAGE] Bits */
#define GSC_FPC_WEPROTTRIM0_WEPROT_PAGE_OFS      (0)                             /* !< WEPROT_PAGE Offset */
#define GSC_FPC_WEPROTTRIM0_WEPROT_PAGE_MASK     ((uint32_t)0x00000003U)         /* !< Erase/program protection for Flash
                                                                                    TRIM region of Bank0 */

/* GSC_FPC_WEPROTTRIM1 Bits */
/* GSC_FPC_WEPROTTRIM1[WEPROT_PAGE] Bits */
#define GSC_FPC_WEPROTTRIM1_WEPROT_PAGE_OFS      (0)                             /* !< WEPROT_PAGE Offset */
#define GSC_FPC_WEPROTTRIM1_WEPROT_PAGE_MASK     ((uint32_t)0x00000003U)         /* !< Erase/program protection for Flash
                                                                                    TRIM region of Bank1 */

/* GSC_FPC_WEPROTENGR0 Bits */
/* GSC_FPC_WEPROTENGR0[WEPROT_PAGE] Bits */
#define GSC_FPC_WEPROTENGR0_WEPROT_PAGE_OFS      (0)                             /* !< WEPROT_PAGE Offset */
#define GSC_FPC_WEPROTENGR0_WEPROT_PAGE_MASK     ((uint32_t)0x00000003U)         /* !< Erase/program protection for Flash
                                                                                    ENGR region of Bank0 */

/* GSC_FPC_WEPROTENGR1 Bits */
/* GSC_FPC_WEPROTENGR1[WEPROT_PAGE] Bits */
#define GSC_FPC_WEPROTENGR1_WEPROT_PAGE_OFS      (0)                             /* !< WEPROT_PAGE Offset */
#define GSC_FPC_WEPROTENGR1_WEPROT_PAGE_MASK     ((uint32_t)0x00000003U)         /* !< Erase/program protection for Flash
                                                                                    ENGR region of Bank1 */

/* GSC_FPC_FLSEMREQ Bits */
/* GSC_FPC_FLSEMREQ[REQ] Bits */
#define GSC_FPC_FLSEMREQ_REQ_OFS                 (0)                             /* !< REQ Offset */
#define GSC_FPC_FLSEMREQ_REQ_MASK                ((uint32_t)0x00000001U)         /* !< Request Semaphore Ownership */

/* GSC_FPC_FLSEMCLR Bits */
/* GSC_FPC_FLSEMCLR[CLR] Bits */
#define GSC_FPC_FLSEMCLR_CLR_OFS                 (0)                             /* !< CLR Offset */
#define GSC_FPC_FLSEMCLR_CLR_MASK                ((uint32_t)0x00000001U)         /* !< Release Semaphore Ownership */

/* GSC_FPC_FLSEMSTAT Bits */
/* GSC_FPC_FLSEMSTAT[PRIV] Bits */
#define GSC_FPC_FLSEMSTAT_PRIV_OFS               (8)                             /* !< PRIV Offset */
#define GSC_FPC_FLSEMSTAT_PRIV_MASK              ((uint32_t)0x00000100U)         /* !< Semaphore Privilage attribute */
/* GSC_FPC_FLSEMSTAT[DBGACC] Bits */
#define GSC_FPC_FLSEMSTAT_DBGACC_OFS             (16)                            /* !< DBGACC Offset */
#define GSC_FPC_FLSEMSTAT_DBGACC_MASK            ((uint32_t)0x00010000U)         /* !< Semaphore debug access */
/* GSC_FPC_FLSEMSTAT[MATCH] Bits */
#define GSC_FPC_FLSEMSTAT_MATCH_OFS              (30)                            /* !< MATCH Offset */
#define GSC_FPC_FLSEMSTAT_MATCH_MASK             ((uint32_t)0x40000000U)         /* !< Match Status Bit */
/* GSC_FPC_FLSEMSTAT[ASSIGNED] Bits */
#define GSC_FPC_FLSEMSTAT_ASSIGNED_OFS           (31)                            /* !< ASSIGNED Offset */
#define GSC_FPC_FLSEMSTAT_ASSIGNED_MASK          ((uint32_t)0x80000000U)         /* !< Assigned Flag */

/* GSC_VTOR_NS Bits */
/* GSC_VTOR_NS[VTOR_NS] Bits */
#define GSC_VTOR_NS_VTOR_NS_OFS                  (0)                             /* !< VTOR_NS Offset */
#define GSC_VTOR_NS_VTOR_NS_MASK                 ((uint32_t)0xFFFFFFFFU)         /* !< Non - Secure Vector Table Offset */

/* GSC_DTB_MUXSEL Bits */
/* GSC_DTB_MUXSEL[DTB_MUX_SEL_CPU] Bits */
#define GSC_DTB_MUXSEL_DTB_MUX_SEL_CPU_OFS       (0)                             /* !< DTB_MUX_SEL_CPU Offset */
#define GSC_DTB_MUXSEL_DTB_MUX_SEL_CPU_MASK      ((uint32_t)0x00000007U)         /* !< CPU DTB MUX sel */
/* GSC_DTB_MUXSEL[DTB_MUX_SEL_WUC] Bits */
#define GSC_DTB_MUXSEL_DTB_MUX_SEL_WUC_OFS       (5)                             /* !< DTB_MUX_SEL_WUC Offset */
#define GSC_DTB_MUXSEL_DTB_MUX_SEL_WUC_MASK      ((uint32_t)0x000003E0U)         /* !< WUC DTB MUX sel */

/* GSC_GSC_LOCK Bits */
/* GSC_GSC_LOCK[ATTRIBVIOL_CONFIG] Bits */
#define GSC_GSC_LOCK_ATTRIBVIOL_CONFIG_OFS       (0)                             /* !< ATTRIBVIOL_CONFIG Offset */
#define GSC_GSC_LOCK_ATTRIBVIOL_CONFIG_MASK      ((uint32_t)0x00000001U)         /* !< Register lock configuration */
/* GSC_GSC_LOCK[PPC_AATRIB] Bits */
#define GSC_GSC_LOCK_PPC_AATRIB_OFS              (1)                             /* !< PPC_AATRIB Offset */
#define GSC_GSC_LOCK_PPC_AATRIB_MASK             ((uint32_t)0x00000002U)         /* !< Register lock configuration */
/* GSC_GSC_LOCK[SPC_AATRIB] Bits */
#define GSC_GSC_LOCK_SPC_AATRIB_OFS              (2)                             /* !< SPC_AATRIB Offset */
#define GSC_GSC_LOCK_SPC_AATRIB_MASK             ((uint32_t)0x00000004U)         /* !< Register lock configuration */
/* GSC_GSC_LOCK[FPPC_AATRIB] Bits */
#define GSC_GSC_LOCK_FPPC_AATRIB_OFS             (3)                             /* !< FPPC_AATRIB Offset */
#define GSC_GSC_LOCK_FPPC_AATRIB_MASK            ((uint32_t)0x00000008U)         /* !< Register lock configuration */
/* GSC_GSC_LOCK[VTOR] Bits */
#define GSC_GSC_LOCK_VTOR_OFS                    (5)                             /* !< VTOR Offset */
#define GSC_GSC_LOCK_VTOR_MASK                   ((uint32_t)0x00000020U)         /* !< Register lock configuration */
/* GSC_GSC_LOCK[DTB_MUXSEL] Bits */
#define GSC_GSC_LOCK_DTB_MUXSEL_OFS              (7)                             /* !< DTB_MUXSEL Offset */
#define GSC_GSC_LOCK_DTB_MUXSEL_MASK             ((uint32_t)0x00000080U)         /* !< Register lock configuration */
/* GSC_GSC_LOCK[KEY] Bits */
#define GSC_GSC_LOCK_KEY_OFS                     (16)                            /* !< KEY Offset */
#define GSC_GSC_LOCK_KEY_MASK                    ((uint32_t)0xFFFF0000U)         /* !< Register lock configuration key */

/* GSC_GSC_COMMIT Bits */
/* GSC_GSC_COMMIT[ATTRIBVIOL_CONFIG] Bits */
#define GSC_GSC_COMMIT_ATTRIBVIOL_CONFIG_OFS     (0)                             /* !< ATTRIBVIOL_CONFIG Offset */
#define GSC_GSC_COMMIT_ATTRIBVIOL_CONFIG_MASK    ((uint32_t)0x00000001U)         /* !< Register lock committed */
/* GSC_GSC_COMMIT[PPC_AATRIB] Bits */
#define GSC_GSC_COMMIT_PPC_AATRIB_OFS            (1)                             /* !< PPC_AATRIB Offset */
#define GSC_GSC_COMMIT_PPC_AATRIB_MASK           ((uint32_t)0x00000002U)         /* !< Register lock committed */
/* GSC_GSC_COMMIT[SPC_AATRIB] Bits */
#define GSC_GSC_COMMIT_SPC_AATRIB_OFS            (2)                             /* !< SPC_AATRIB Offset */
#define GSC_GSC_COMMIT_SPC_AATRIB_MASK           ((uint32_t)0x00000004U)         /* !< Register lock committed */
/* GSC_GSC_COMMIT[FPPC_AATRIB] Bits */
#define GSC_GSC_COMMIT_FPPC_AATRIB_OFS           (3)                             /* !< FPPC_AATRIB Offset */
#define GSC_GSC_COMMIT_FPPC_AATRIB_MASK          ((uint32_t)0x00000008U)         /* !< Register lock committed */
/* GSC_GSC_COMMIT[VTOR] Bits */
#define GSC_GSC_COMMIT_VTOR_OFS                  (5)                             /* !< VTOR Offset */
#define GSC_GSC_COMMIT_VTOR_MASK                 ((uint32_t)0x00000020U)         /* !< Register lock committed */
/* GSC_GSC_COMMIT[DTB_MUXSEL] Bits */
#define GSC_GSC_COMMIT_DTB_MUXSEL_OFS            (7)                             /* !< DTB_MUXSEL Offset */
#define GSC_GSC_COMMIT_DTB_MUXSEL_MASK           ((uint32_t)0x00000080U)         /* !< Register lock committed */
/* GSC_GSC_COMMIT[KEY] Bits */
#define GSC_GSC_COMMIT_KEY_OFS                   (16)                            /* !< KEY Offset */
#define GSC_GSC_COMMIT_KEY_MASK                  ((uint32_t)0xFFFF0000U)         /* !< Register lock commit key */

/* GSC_GSC_REVISION Bits */
/* GSC_GSC_REVISION[MINREV] Bits */
#define GSC_GSC_REVISION_MINREV_OFS              (0)                             /* !< MINREV Offset */
#define GSC_GSC_REVISION_MINREV_MASK             ((uint32_t)0x000000FFU)         /* !< Minor Revision Number */
/* GSC_GSC_REVISION[MAJREV] Bits */
#define GSC_GSC_REVISION_MAJREV_OFS              (8)                             /* !< MAJREV Offset */
#define GSC_GSC_REVISION_MAJREV_MASK             ((uint32_t)0x0000FF00U)         /* !< Major Revision Number */


#ifdef __cplusplus
}
#endif

#endif /* hw_gsc__include */

