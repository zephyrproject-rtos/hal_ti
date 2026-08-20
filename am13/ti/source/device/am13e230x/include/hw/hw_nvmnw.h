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

#ifndef hw_nvmnw__include
#define hw_nvmnw__include


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
* NVMNW Registers
******************************************************************************/
#define NVMNW_GEN_OFS                            ((uint32_t)0x00000000U)


/** @addtogroup NVMNW_GEN
  @{
*/

typedef struct {
       uint32_t RESERVED0[288];
  __IO uint32_t CPU_CONNECT_0;                     /* !< (@ 0x00000480) CPU Connect */
       uint32_t RESERVED1[743];
  __I  uint32_t IIDX;                              /* !< (@ 0x00001020) Interrupt Index Register */
       uint32_t RESERVED2;
  __IO uint32_t IMASK;                             /* !< (@ 0x00001028) Interrupt Mask Register */
       uint32_t RESERVED3;
  __I  uint32_t RIS;                               /* !< (@ 0x00001030) Raw Interrupt Status Register */
       uint32_t RESERVED4;
  __I  uint32_t MIS;                               /* !< (@ 0x00001038) Masked Interrupt Status Register */
       uint32_t RESERVED5;
  __O  uint32_t ISET;                              /* !< (@ 0x00001040) Interrupt Set Register */
       uint32_t RESERVED6;
  __O  uint32_t ICLR;                              /* !< (@ 0x00001048) Interrupt Clear Register */
       uint32_t RESERVED7[45];
  __IO uint32_t CMDEXEC;                           /* !< (@ 0x00001100) Command Execute Register */
  __IO uint32_t CMDTYPE;                           /* !< (@ 0x00001104) Command Type Register */
  __IO uint32_t CMDCTL;                            /* !< (@ 0x00001108) Command Control Register */
       uint32_t RESERVED8[5];
  __IO uint32_t CMDADDR;                           /* !< (@ 0x00001120) Command Address Register */
  __IO uint32_t CMDBYTEN;                          /* !< (@ 0x00001124) Command Program Byte Enable Register */
       uint32_t RESERVED9;
  __IO uint32_t CMDDATAINDEX;                      /* !< (@ 0x0000112C) Command Data Index Register */
  __IO uint32_t CMDDATA0;                          /* !< (@ 0x00001130) Command Data Register 0 */
  __IO uint32_t CMDDATA1;                          /* !< (@ 0x00001134) Command Data Register 1 */
  __IO uint32_t CMDDATA2;                          /* !< (@ 0x00001138) Command Data Register 2 */
  __IO uint32_t CMDDATA3;                          /* !< (@ 0x0000113C) Command Data Register Bits 127:96 */
  __IO uint32_t CMDDATA4;                          /* !< (@ 0x00001140) Command Data Register 4 */
  __IO uint32_t CMDDATA5;                          /* !< (@ 0x00001144) Command Data Register 5 */
  __IO uint32_t CMDDATA6;                          /* !< (@ 0x00001148) Command Data Register 6 */
  __IO uint32_t CMDDATA7;                          /* !< (@ 0x0000114C) Command Data Register 7 */
  __IO uint32_t CMDDATA8;                          /* !< (@ 0x00001150) Command Data Register 8 */
  __IO uint32_t CMDDATA9;                          /* !< (@ 0x00001154) Command Data Register 9 */
  __IO uint32_t CMDDATA10;                         /* !< (@ 0x00001158) Command Data Register 10 */
  __IO uint32_t CMDDATA11;                         /* !< (@ 0x0000115C) Command Data Register 11 */
  __IO uint32_t CMDDATA12;                         /* !< (@ 0x00001160) Command Data Register 12 */
  __IO uint32_t CMDDATA13;                         /* !< (@ 0x00001164) Command Data Register 13 */
  __IO uint32_t CMDDATA14;                         /* !< (@ 0x00001168) Command Data Register 14 */
  __IO uint32_t CMDDATA15;                         /* !< (@ 0x0000116C) Command Data Register 15 */
       uint32_t RESERVED10[16];
  __IO uint32_t CMDDATAECC0;                       /* !< (@ 0x000011B0) Command Data Register ECC 0 */
  __IO uint32_t CMDDATAECC1;                       /* !< (@ 0x000011B4) Command Data Register ECC 1 */
  __IO uint32_t CMDDATAECC2;                       /* !< (@ 0x000011B8) Command Data Register ECC 2 */
  __IO uint32_t CMDDATAECC3;                       /* !< (@ 0x000011BC) Command Data Register ECC 3 */
       uint32_t RESERVED11[4];
  __IO uint32_t CMDWEPROTA;                        /* !< (@ 0x000011D0) Command Write Erase Protect A Register */
  __IO uint32_t CMDWEPROTB;                        /* !< (@ 0x000011D4) Command Write Erase Protect B Register */
       uint32_t RESERVED12[14];
  __IO uint32_t CMDWEPROTNM;                       /* !< (@ 0x00001210) Command Write Erase Protect Non-Main Register */
       uint32_t RESERVED13[111];
  __I  uint32_t STATCMD;                           /* !< (@ 0x000013D0) Command Status Register */
       uint32_t RESERVED14;
  __I  uint32_t STATPCNT;                          /* !< (@ 0x000013D8) Pulse Count Status Register */
} NVMNW_GEN_Regs;

/*@}*/ /* end of group NVMNW_GEN */

/** @addtogroup NVMNW
  @{
*/

typedef struct {
  NVMNW_GEN_Regs  GEN;                               /* !< (@ 0x00000000) */
} NVMNW_Regs;

/*@}*/ /* end of group NVMNW */



/******************************************************************************
* NVMNW Register Offsets
******************************************************************************/

#define NVMNW_CPU_CONNECT_0                      (0x00000480U)
#define NVMNW_IIDX                               (0x00001020U)
#define NVMNW_IMASK                              (0x00001028U)
#define NVMNW_RIS                                (0x00001030U)
#define NVMNW_MIS                                (0x00001038U)
#define NVMNW_ISET                               (0x00001040U)
#define NVMNW_ICLR                               (0x00001048U)
#define NVMNW_CMDEXEC                            (0x00001100U)
#define NVMNW_CMDTYPE                            (0x00001104U)
#define NVMNW_CMDCTL                             (0x00001108U)
#define NVMNW_CMDADDR                            (0x00001120U)
#define NVMNW_CMDBYTEN                           (0x00001124U)
#define NVMNW_CMDDATAINDEX                       (0x0000112CU)
#define NVMNW_CMDDATA0                           (0x00001130U)
#define NVMNW_CMDDATA1                           (0x00001134U)
#define NVMNW_CMDDATA2                           (0x00001138U)
#define NVMNW_CMDDATA3                           (0x0000113CU)
#define NVMNW_CMDDATA4                           (0x00001140U)
#define NVMNW_CMDDATA5                           (0x00001144U)
#define NVMNW_CMDDATA6                           (0x00001148U)
#define NVMNW_CMDDATA7                           (0x0000114CU)
#define NVMNW_CMDDATA8                           (0x00001150U)
#define NVMNW_CMDDATA9                           (0x00001154U)
#define NVMNW_CMDDATA10                          (0x00001158U)
#define NVMNW_CMDDATA11                          (0x0000115CU)
#define NVMNW_CMDDATA12                          (0x00001160U)
#define NVMNW_CMDDATA13                          (0x00001164U)
#define NVMNW_CMDDATA14                          (0x00001168U)
#define NVMNW_CMDDATA15                          (0x0000116CU)
#define NVMNW_CMDDATAECC0                        (0x000011B0U)
#define NVMNW_CMDDATAECC1                        (0x000011B4U)
#define NVMNW_CMDDATAECC2                        (0x000011B8U)
#define NVMNW_CMDDATAECC3                        (0x000011BCU)
#define NVMNW_CMDWEPROTA                         (0x000011D0U)
#define NVMNW_CMDWEPROTB                         (0x000011D4U)
#define NVMNW_CMDWEPROTNM                        (0x00001210U)
#define NVMNW_STATCMD                            (0x000013D0U)
#define NVMNW_STATPCNT                           (0x000013D8U)



#if defined ( __CC_ARM )
#pragma no_anon_unions
#endif

/******************************************************************************
* NVMNW Register Control Bits
******************************************************************************/

/* NVMNW_CPU_CONNECT_0 Bits */
/* NVMNW_CPU_CONNECT_0[CPUSS0_CONN] Bits */
#define NVMNW_CPU_CONNECT_0_CPUSS0_CONN_OFS      (1)                             /* !< CPUSS0_CONN Offset */
#define NVMNW_CPU_CONNECT_0_CPUSS0_CONN_MASK     ((uint32_t)0x00000002U)         /* !< CPUSS0 connect bit. */
#define NVMNW_CPU_CONNECT_0_CPUSS0_CONN_UNCONNECTED ((uint32_t)0x00000000U)         /* !< The CPU is not connected. */
#define NVMNW_CPU_CONNECT_0_CPUSS0_CONN_CONNECTED ((uint32_t)0x00000002U)         /* !< The CPU is connected. */

/* NVMNW_IIDX Bits */
/* NVMNW_IIDX[STAT] Bits */
#define NVMNW_IIDX_STAT_OFS                      (0)                             /* !< STAT Offset */
#define NVMNW_IIDX_STAT_MASK                     ((uint32_t)0x00000001U)         /* !< Indicates which interrupt has
                                                                                    fired. 0x0 means no event pending.
                                                                                    The priority order is fixed. On each
                                                                                    read, only one interrupt is
                                                                                    indicated. On a read, the current
                                                                                    interrupt (highest priority) is
                                                                                    automatically cleared by the hardware
                                                                                    and the corresponding interrupt flags
                                                                                    in the RIS and MIS are cleared as
                                                                                    well. After a read from the CPU (not
                                                                                    from the debug interface), the
                                                                                    register must be updated with the
                                                                                    next highest priority interrupt. */
#define NVMNW_IIDX_STAT_NO_INTR                  ((uint32_t)0x00000000U)         /* !< No Interrupt Pending */
#define NVMNW_IIDX_STAT_DONE                     ((uint32_t)0x00000001U)         /* !< DONE Interrupt Pending */

/* NVMNW_IMASK Bits */
/* NVMNW_IMASK[DONE] Bits */
#define NVMNW_IMASK_DONE_OFS                     (0)                             /* !< DONE Offset */
#define NVMNW_IMASK_DONE_MASK                    ((uint32_t)0x00000001U)         /* !< Interrupt mask for DONE: 0:
                                                                                    Interrupt is disabled in MIS register
                                                                                    1: Interrupt is enabled in MIS
                                                                                    register */
#define NVMNW_IMASK_DONE_DISABLED                ((uint32_t)0x00000000U)         /* !< Interrupt is masked out */
#define NVMNW_IMASK_DONE_ENABLED                 ((uint32_t)0x00000001U)         /* !< Interrupt will request an interrupt
                                                                                    service routine and corresponding bit
                                                                                    in [IPSTANDARD.MIS] will be set */

/* NVMNW_RIS Bits */
/* NVMNW_RIS[DONE] Bits */
#define NVMNW_RIS_DONE_OFS                       (0)                             /* !< DONE Offset */
#define NVMNW_RIS_DONE_MASK                      ((uint32_t)0x00000001U)         /* !< Flash wrapper operation completed.
                                                                                    This interrupt bit is set by firmware
                                                                                    or the corresponding bit in the ISET
                                                                                    register. It is cleared by the
                                                                                    corresponding bit in in the ICLR
                                                                                    register or reading the IIDX register
                                                                                    when this interrupt is the highest
                                                                                    priority. */
#define NVMNW_RIS_DONE_CLR                       ((uint32_t)0x00000000U)         /* !< Interrupt did not occur */
#define NVMNW_RIS_DONE_SET                       ((uint32_t)0x00000001U)         /* !< Interrupt occurred */

/* NVMNW_MIS Bits */
/* NVMNW_MIS[DONE] Bits */
#define NVMNW_MIS_DONE_OFS                       (0)                             /* !< DONE Offset */
#define NVMNW_MIS_DONE_MASK                      ((uint32_t)0x00000001U)         /* !< Flash wrapper operation completed.
                                                                                    This masked interrupt bit reflects
                                                                                    the bitwise AND of the corresponding
                                                                                    RIS and IMASK bits. */
#define NVMNW_MIS_DONE_CLR                       ((uint32_t)0x00000000U)         /* !< Masked interrupt did not occur */
#define NVMNW_MIS_DONE_SET                       ((uint32_t)0x00000001U)         /* !< Masked interrupt occurred */

/* NVMNW_ISET Bits */
/* NVMNW_ISET[DONE] Bits */
#define NVMNW_ISET_DONE_OFS                      (0)                             /* !< DONE Offset */
#define NVMNW_ISET_DONE_MASK                     ((uint32_t)0x00000001U)         /* !< 0: No effect 1: Set the DONE
                                                                                    interrupt in the RIS register */
#define NVMNW_ISET_DONE_NO_EFFECT                ((uint32_t)0x00000000U)         /* !< Writing a 0 has no effect */
#define NVMNW_ISET_DONE_SET                      ((uint32_t)0x00000001U)         /* !< Set [IPSTANDARD.RIS] bit */

/* NVMNW_ICLR Bits */
/* NVMNW_ICLR[DONE] Bits */
#define NVMNW_ICLR_DONE_OFS                      (0)                             /* !< DONE Offset */
#define NVMNW_ICLR_DONE_MASK                     ((uint32_t)0x00000001U)         /* !< 0: No effect 1: Clear the DONE
                                                                                    interrupt in the RIS register */
#define NVMNW_ICLR_DONE_NO_EFFECT                ((uint32_t)0x00000000U)         /* !< Writing a 0 has no effect */
#define NVMNW_ICLR_DONE_CLR                      ((uint32_t)0x00000001U)         /* !< Clear [IPSTANDARD.RIS] bit */

/* NVMNW_CMDEXEC Bits */
/* NVMNW_CMDEXEC[VAL] Bits */
#define NVMNW_CMDEXEC_VAL_OFS                    (0)                             /* !< VAL Offset */
#define NVMNW_CMDEXEC_VAL_MASK                   ((uint32_t)0x00000001U)         /* !< Command Execute value Initiates
                                                                                    execution of the command specified in
                                                                                    the CMDTYPE register. */
#define NVMNW_CMDEXEC_VAL_NOEXECUTE              ((uint32_t)0x00000000U)         /* !< Command will not execute or is not
                                                                                    executing in flash wrapper */
#define NVMNW_CMDEXEC_VAL_EXECUTE                ((uint32_t)0x00000001U)         /* !< Command will execute or is
                                                                                    executing in flash wrapper */

/* NVMNW_CMDTYPE Bits */
/* NVMNW_CMDTYPE[COMMAND] Bits */
#define NVMNW_CMDTYPE_COMMAND_OFS                (0)                             /* !< COMMAND Offset */
#define NVMNW_CMDTYPE_COMMAND_MASK               ((uint32_t)0x00000007U)         /* !< Command type */
#define NVMNW_CMDTYPE_COMMAND_NOOP               ((uint32_t)0x00000000U)         /* !< No Operation */
#define NVMNW_CMDTYPE_COMMAND_PROGRAM            ((uint32_t)0x00000001U)         /* !< Program */
#define NVMNW_CMDTYPE_COMMAND_ERASE              ((uint32_t)0x00000002U)         /* !< Erase */
#define NVMNW_CMDTYPE_COMMAND_READVERIFY__SECRET_ENUM ((uint32_t)0x00000003U)         /* !< ReadVerify - Perform a standalone
                                                                                    ReadVerify operation. */
#define NVMNW_CMDTYPE_COMMAND_MODECHANGE         ((uint32_t)0x00000004U)         /* !< Mode Change - Perform a mode change
                                                                                    only, no other operation. */
#define NVMNW_CMDTYPE_COMMAND_CLEARSTATUS        ((uint32_t)0x00000005U)         /* !< Clear Status - Clear status bits in
                                                                                    FW_SMSTAT only. */
#define NVMNW_CMDTYPE_COMMAND_BLANKVERIFY        ((uint32_t)0x00000006U)         /* !< Blank Verify - Check whether a
                                                                                    flash word is in the erased state.
                                                                                    This command may only be used with
                                                                                    CMDTYPE.SIZE = ONEWORD */
/* NVMNW_CMDTYPE[SIZE] Bits */
#define NVMNW_CMDTYPE_SIZE_OFS                   (4)                             /* !< SIZE Offset */
#define NVMNW_CMDTYPE_SIZE_MASK                  ((uint32_t)0x00000070U)         /* !< Command size */
#define NVMNW_CMDTYPE_SIZE_ONEWORD               ((uint32_t)0x00000000U)         /* !< Operate on 1 flash word */
#define NVMNW_CMDTYPE_SIZE_TWOWORD               ((uint32_t)0x00000010U)         /* !< Operate on 2 flash words */
#define NVMNW_CMDTYPE_SIZE_FOURWORD              ((uint32_t)0x00000020U)         /* !< Operate on 4 flash words */
#define NVMNW_CMDTYPE_SIZE_EIGHTWORD             ((uint32_t)0x00000030U)         /* !< Operate on 8 flash words */
#define NVMNW_CMDTYPE_SIZE_SECTOR                ((uint32_t)0x00000040U)         /* !< Operate on a flash sector */
#define NVMNW_CMDTYPE_SIZE_BANK                  ((uint32_t)0x00000050U)         /* !< Operate on an entire flash bank */

/* NVMNW_CMDCTL Bits */
/* NVMNW_CMDCTL[MODESEL] Bits */
#define NVMNW_CMDCTL_MODESEL_OFS                 (0)                             /* !< MODESEL Offset */
#define NVMNW_CMDCTL_MODESEL_MASK                ((uint32_t)0x0000000FU)         /* !< Mode This field is only used for
                                                                                    the Mode Change command type.
                                                                                    Otherwise, bank and pump modes are
                                                                                    set automaticlly through the NW
                                                                                    hardware. */
#define NVMNW_CMDCTL_MODESEL_READ                ((uint32_t)0x00000000U)         /* !< Read Mode */
#define NVMNW_CMDCTL_MODESEL_RDMARG0             ((uint32_t)0x00000002U)         /* !< Read Margin 0 Mode */
#define NVMNW_CMDCTL_MODESEL_RDMARG1             ((uint32_t)0x00000004U)         /* !< Read Margin 1 Mode */
#define NVMNW_CMDCTL_MODESEL_RDMARG0B            ((uint32_t)0x00000006U)         /* !< Read Margin 0B Mode */
#define NVMNW_CMDCTL_MODESEL_RDMARG1B            ((uint32_t)0x00000007U)         /* !< Read Margin 1B Mode */
#define NVMNW_CMDCTL_MODESEL_PGMVER              ((uint32_t)0x00000009U)         /* !< Program Verify Mode */
#define NVMNW_CMDCTL_MODESEL_PGMSW               ((uint32_t)0x0000000AU)         /* !< Program Single Word */
#define NVMNW_CMDCTL_MODESEL_ERASEVER            ((uint32_t)0x0000000BU)         /* !< Erase Verify Mode */
#define NVMNW_CMDCTL_MODESEL_ERASESECT           ((uint32_t)0x0000000CU)         /* !< Erase Sector */
#define NVMNW_CMDCTL_MODESEL_PGMMW               ((uint32_t)0x0000000EU)         /* !< Program Multiple Word */
#define NVMNW_CMDCTL_MODESEL_ERASEBNK            ((uint32_t)0x0000000FU)         /* !< Erase Bank */
/* NVMNW_CMDCTL[BANKSEL] Bits */
#define NVMNW_CMDCTL_BANKSEL_OFS                 (4)                             /* !< BANKSEL Offset */
#define NVMNW_CMDCTL_BANKSEL_MASK                ((uint32_t)0x00000030U)         /* !< Bank Select A specific Bank ID can
                                                                                    be written to this field to indicate
                                                                                    to which bank an  operation is to be
                                                                                    applied if CMDCTL.ADDRXLATEOVR is
                                                                                    set. */
#define NVMNW_CMDCTL_BANKSEL_BANK0               ((uint32_t)0x00000010U)         /* !< Bank 0 */
#define NVMNW_CMDCTL_BANKSEL_BANK1               ((uint32_t)0x00000020U)         /* !< Bank 1 */
#define NVMNW_CMDCTL_BANKSEL_BANK2               ((uint32_t)0x00000040U)         /* !< Bank 2 */
#define NVMNW_CMDCTL_BANKSEL_BANK3               ((uint32_t)0x00000080U)         /* !< Bank 3 */
#define NVMNW_CMDCTL_BANKSEL_BANK4               ((uint32_t)0x00000100U)         /* !< Bank 4 */
/* NVMNW_CMDCTL[REGIONSEL] Bits */
#define NVMNW_CMDCTL_REGIONSEL_OFS               (9)                             /* !< REGIONSEL Offset */
#define NVMNW_CMDCTL_REGIONSEL_MASK              ((uint32_t)0x00001E00U)         /* !< Bank Region A specific region ID
                                                                                    can be written to this field to
                                                                                    indicate to which region an
                                                                                    operation is to be applied if
                                                                                    CMDCTL.ADDRXLATEOVR is set. */
#define NVMNW_CMDCTL_REGIONSEL_MAIN              ((uint32_t)0x00000200U)         /* !< Main Region */
#define NVMNW_CMDCTL_REGIONSEL_NONMAIN           ((uint32_t)0x00000400U)         /* !< Non-Main Region */
#define NVMNW_CMDCTL_REGIONSEL_TRIM              ((uint32_t)0x00000800U)         /* !< Trim Region */
#define NVMNW_CMDCTL_REGIONSEL_ENGR              ((uint32_t)0x00001000U)         /* !< Engr Region */
/* NVMNW_CMDCTL[ECCGENOVR] Bits */
#define NVMNW_CMDCTL_ECCGENOVR_OFS               (17)                            /* !< ECCGENOVR Offset */
#define NVMNW_CMDCTL_ECCGENOVR_MASK              ((uint32_t)0x00020000U)         /* !< Override hardware generation of ECC
                                                                                    data for program.  Use data written
                                                                                    to  CMDDATAECC*. */
#define NVMNW_CMDCTL_ECCGENOVR_NOOVERRIDE        ((uint32_t)0x00000000U)         /* !< Do not override */
#define NVMNW_CMDCTL_ECCGENOVR_OVERRIDE          ((uint32_t)0x00020000U)         /* !< Override */
/* NVMNW_CMDCTL[ADDRXLATEOVR] Bits */
#define NVMNW_CMDCTL_ADDRXLATEOVR_OFS            (16)                            /* !< ADDRXLATEOVR Offset */
#define NVMNW_CMDCTL_ADDRXLATEOVR_MASK           ((uint32_t)0x00010000U)         /* !< Override hardware address
                                                                                    translation of address in CMDADDR
                                                                                    from a  system address to a bank
                                                                                    address and bank ID.  Use data
                                                                                    written to  CMDADDR directly as the
                                                                                    bank address.  Use the value written
                                                                                    to  CMDCTL.BANKSEL directly as the
                                                                                    bank ID.  Use the value written to
                                                                                    CMDCTL.REGIONSEL directly as the
                                                                                    region ID. */
#define NVMNW_CMDCTL_ADDRXLATEOVR_NOOVERRIDE     ((uint32_t)0x00000000U)         /* !< Do not override */
#define NVMNW_CMDCTL_ADDRXLATEOVR_OVERRIDE       ((uint32_t)0x00010000U)         /* !< Override */
/* NVMNW_CMDCTL[SSERASEDIS] Bits */
#define NVMNW_CMDCTL_SSERASEDIS_OFS              (20)                            /* !< SSERASEDIS Offset */
#define NVMNW_CMDCTL_SSERASEDIS_MASK             ((uint32_t)0x00100000U)         /* !< Disable Stair-Step Erase.  If set,
                                                                                    the default VHV trim voltage setting
                                                                                    will be used for all erase pulses. By
                                                                                    default, this bit is reset, meaning
                                                                                    that the VHV voltage will be stepped
                                                                                    during successive erase pulses.  The
                                                                                    step count, step voltage, begin and
                                                                                    end voltages are all hard-wired. */
#define NVMNW_CMDCTL_SSERASEDIS_ENABLE           ((uint32_t)0x00000000U)         /* !< Enable */
#define NVMNW_CMDCTL_SSERASEDIS_DISABLE          ((uint32_t)0x00100000U)         /* !< Disable */
/* NVMNW_CMDCTL[DATAVEREN] Bits */
#define NVMNW_CMDCTL_DATAVEREN_OFS               (21)                            /* !< DATAVEREN Offset */
#define NVMNW_CMDCTL_DATAVEREN_MASK              ((uint32_t)0x00200000U)         /* !< Enable invalid data verify.   This
                                                                                    checks for 0->1 transitions in the
                                                                                    memory when a program operation is
                                                                                    initiated.  If such a transition is
                                                                                    found, the program will fail with an
                                                                                    error without executing the program. */
#define NVMNW_CMDCTL_DATAVEREN_DISABLE           ((uint32_t)0x00000000U)         /* !< Disable */
#define NVMNW_CMDCTL_DATAVEREN_ENABLE            ((uint32_t)0x00200000U)         /* !< Enable */

/* NVMNW_CMDADDR Bits */
/* NVMNW_CMDADDR[VAL] Bits */
#define NVMNW_CMDADDR_VAL_OFS                    (0)                             /* !< VAL Offset */
#define NVMNW_CMDADDR_VAL_MASK                   ((uint32_t)0xFFFFFFFFU)         /* !< Address value */
#define NVMNW_CMDADDR_VAL_MINIMUM                ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDADDR_VAL_MAXIMUM                ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDBYTEN Bits */
/* NVMNW_CMDBYTEN[VAL] Bits */
#define NVMNW_CMDBYTEN_VAL_OFS                   (0)                             /* !< VAL Offset */
#define NVMNW_CMDBYTEN_VAL_MASK                  ((uint32_t)0x0003FFFFU)         /* !< Command Byte Enable value. A 1-bit
                                                                                    per flash word byte value is placed
                                                                                    in this register. */
#define NVMNW_CMDBYTEN_VAL_MINIMUM               ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDBYTEN_VAL_MAXIMUM               ((uint32_t)0x0003FFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATAINDEX Bits */
/* NVMNW_CMDDATAINDEX[VAL] Bits */
#define NVMNW_CMDDATAINDEX_VAL_OFS               (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATAINDEX_VAL_MASK              ((uint32_t)0x00000003U)         /* !< Data register index */
#define NVMNW_CMDDATAINDEX_VAL_MINIMUM           ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATAINDEX_VAL_MAXIMUM           ((uint32_t)0x00000007U)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA0 Bits */
/* NVMNW_CMDDATA0[VAL] Bits */
#define NVMNW_CMDDATA0_VAL_OFS                   (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA0_VAL_MASK                  ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA0_VAL_MINIMUM               ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA0_VAL_MAXIMUM               ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA1 Bits */
/* NVMNW_CMDDATA1[VAL] Bits */
#define NVMNW_CMDDATA1_VAL_OFS                   (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA1_VAL_MASK                  ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA1_VAL_MINIMUM               ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA1_VAL_MAXIMUM               ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA2 Bits */
/* NVMNW_CMDDATA2[VAL] Bits */
#define NVMNW_CMDDATA2_VAL_OFS                   (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA2_VAL_MASK                  ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA2_VAL_MINIMUM               ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA2_VAL_MAXIMUM               ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA3 Bits */
/* NVMNW_CMDDATA3[VAL] Bits */
#define NVMNW_CMDDATA3_VAL_OFS                   (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA3_VAL_MASK                  ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA3_VAL_MINIMUM               ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA3_VAL_MAXIMUM               ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA4 Bits */
/* NVMNW_CMDDATA4[VAL] Bits */
#define NVMNW_CMDDATA4_VAL_OFS                   (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA4_VAL_MASK                  ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. T */
#define NVMNW_CMDDATA4_VAL_MINIMUM               ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA4_VAL_MAXIMUM               ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA5 Bits */
/* NVMNW_CMDDATA5[VAL] Bits */
#define NVMNW_CMDDATA5_VAL_OFS                   (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA5_VAL_MASK                  ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA5_VAL_MINIMUM               ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA5_VAL_MAXIMUM               ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA6 Bits */
/* NVMNW_CMDDATA6[VAL] Bits */
#define NVMNW_CMDDATA6_VAL_OFS                   (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA6_VAL_MASK                  ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA6_VAL_MINIMUM               ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA6_VAL_MAXIMUM               ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA7 Bits */
/* NVMNW_CMDDATA7[VAL] Bits */
#define NVMNW_CMDDATA7_VAL_OFS                   (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA7_VAL_MASK                  ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA7_VAL_MINIMUM               ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA7_VAL_MAXIMUM               ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA8 Bits */
/* NVMNW_CMDDATA8[VAL] Bits */
#define NVMNW_CMDDATA8_VAL_OFS                   (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA8_VAL_MASK                  ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA8_VAL_MINIMUM               ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA8_VAL_MAXIMUM               ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA9 Bits */
/* NVMNW_CMDDATA9[VAL] Bits */
#define NVMNW_CMDDATA9_VAL_OFS                   (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA9_VAL_MASK                  ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA9_VAL_MINIMUM               ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA9_VAL_MAXIMUM               ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA10 Bits */
/* NVMNW_CMDDATA10[VAL] Bits */
#define NVMNW_CMDDATA10_VAL_OFS                  (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA10_VAL_MASK                 ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA10_VAL_MINIMUM              ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA10_VAL_MAXIMUM              ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA11 Bits */
/* NVMNW_CMDDATA11[VAL] Bits */
#define NVMNW_CMDDATA11_VAL_OFS                  (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA11_VAL_MASK                 ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA11_VAL_MINIMUM              ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA11_VAL_MAXIMUM              ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA12 Bits */
/* NVMNW_CMDDATA12[VAL] Bits */
#define NVMNW_CMDDATA12_VAL_OFS                  (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA12_VAL_MASK                 ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA12_VAL_MINIMUM              ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA12_VAL_MAXIMUM              ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA13 Bits */
/* NVMNW_CMDDATA13[VAL] Bits */
#define NVMNW_CMDDATA13_VAL_OFS                  (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA13_VAL_MASK                 ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA13_VAL_MINIMUM              ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA13_VAL_MAXIMUM              ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA14 Bits */
/* NVMNW_CMDDATA14[VAL] Bits */
#define NVMNW_CMDDATA14_VAL_OFS                  (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA14_VAL_MASK                 ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA14_VAL_MINIMUM              ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA14_VAL_MAXIMUM              ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATA15 Bits */
/* NVMNW_CMDDATA15[VAL] Bits */
#define NVMNW_CMDDATA15_VAL_OFS                  (0)                             /* !< VAL Offset */
#define NVMNW_CMDDATA15_VAL_MASK                 ((uint32_t)0xFFFFFFFFU)         /* !< A 32-bit data value is placed in
                                                                                    this field. */
#define NVMNW_CMDDATA15_VAL_MINIMUM              ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDDATA15_VAL_MAXIMUM              ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDDATAECC0 Bits */
/* NVMNW_CMDDATAECC0[VAL0] Bits */
#define NVMNW_CMDDATAECC0_VAL0_OFS               (0)                             /* !< VAL0 Offset */
#define NVMNW_CMDDATAECC0_VAL0_MASK              ((uint32_t)0x000000FFU)         /* !< ECC data for bits 63:0 of the data
                                                                                    is placed here. */
#define NVMNW_CMDDATAECC0_VAL0_MINIMUM           ((uint32_t)0x00000000U)         /* !< Minimum value */
#define NVMNW_CMDDATAECC0_VAL0_MAXIMUM           ((uint32_t)0x000000FFU)         /* !< Maximum value */
/* NVMNW_CMDDATAECC0[VAL1] Bits */
#define NVMNW_CMDDATAECC0_VAL1_OFS               (8)                             /* !< VAL1 Offset */
#define NVMNW_CMDDATAECC0_VAL1_MASK              ((uint32_t)0x0000FF00U)         /* !< ECC data for bits 127:64 of the
                                                                                    data is placed here. */
#define NVMNW_CMDDATAECC0_VAL1_MINIMUM           ((uint32_t)0x00000000U)         /* !< Minimum value */
#define NVMNW_CMDDATAECC0_VAL1_MAXIMUM           ((uint32_t)0x0000FF00U)         /* !< Maximum value */

/* NVMNW_CMDDATAECC1 Bits */
/* NVMNW_CMDDATAECC1[VAL0] Bits */
#define NVMNW_CMDDATAECC1_VAL0_OFS               (0)                             /* !< VAL0 Offset */
#define NVMNW_CMDDATAECC1_VAL0_MASK              ((uint32_t)0x000000FFU)         /* !< ECC data for bits 63:0 of the data
                                                                                    is placed here. */
#define NVMNW_CMDDATAECC1_VAL0_MINIMUM           ((uint32_t)0x00000000U)         /* !< Minimum value */
#define NVMNW_CMDDATAECC1_VAL0_MAXIMUM           ((uint32_t)0x000000FFU)         /* !< Maximum value */
/* NVMNW_CMDDATAECC1[VAL1] Bits */
#define NVMNW_CMDDATAECC1_VAL1_OFS               (8)                             /* !< VAL1 Offset */
#define NVMNW_CMDDATAECC1_VAL1_MASK              ((uint32_t)0x0000FF00U)         /* !< ECC data for bits 127:64 of the
                                                                                    data is placed here. */
#define NVMNW_CMDDATAECC1_VAL1_MINIMUM           ((uint32_t)0x00000000U)         /* !< Minimum value */
#define NVMNW_CMDDATAECC1_VAL1_MAXIMUM           ((uint32_t)0x0000FF00U)         /* !< Maximum value */

/* NVMNW_CMDDATAECC2 Bits */
/* NVMNW_CMDDATAECC2[VAL0] Bits */
#define NVMNW_CMDDATAECC2_VAL0_OFS               (0)                             /* !< VAL0 Offset */
#define NVMNW_CMDDATAECC2_VAL0_MASK              ((uint32_t)0x000000FFU)         /* !< ECC data for bits 63:0 of the data
                                                                                    is placed here. */
#define NVMNW_CMDDATAECC2_VAL0_MINIMUM           ((uint32_t)0x00000000U)         /* !< Minimum value */
#define NVMNW_CMDDATAECC2_VAL0_MAXIMUM           ((uint32_t)0x000000FFU)         /* !< Maximum value */
/* NVMNW_CMDDATAECC2[VAL1] Bits */
#define NVMNW_CMDDATAECC2_VAL1_OFS               (8)                             /* !< VAL1 Offset */
#define NVMNW_CMDDATAECC2_VAL1_MASK              ((uint32_t)0x0000FF00U)         /* !< ECC data for bits 127:64 of the
                                                                                    data is placed here. */
#define NVMNW_CMDDATAECC2_VAL1_MINIMUM           ((uint32_t)0x00000000U)         /* !< Minimum value */
#define NVMNW_CMDDATAECC2_VAL1_MAXIMUM           ((uint32_t)0x0000FF00U)         /* !< Maximum value */

/* NVMNW_CMDDATAECC3 Bits */
/* NVMNW_CMDDATAECC3[VAL0] Bits */
#define NVMNW_CMDDATAECC3_VAL0_OFS               (0)                             /* !< VAL0 Offset */
#define NVMNW_CMDDATAECC3_VAL0_MASK              ((uint32_t)0x000000FFU)         /* !< ECC data for bits 63:0 of the data
                                                                                    is placed here. */
#define NVMNW_CMDDATAECC3_VAL0_MINIMUM           ((uint32_t)0x00000000U)         /* !< Minimum value */
#define NVMNW_CMDDATAECC3_VAL0_MAXIMUM           ((uint32_t)0x000000FFU)         /* !< Maximum value */
/* NVMNW_CMDDATAECC3[VAL1] Bits */
#define NVMNW_CMDDATAECC3_VAL1_OFS               (8)                             /* !< VAL1 Offset */
#define NVMNW_CMDDATAECC3_VAL1_MASK              ((uint32_t)0x0000FF00U)         /* !< ECC data for bits 127:64 of the
                                                                                    data is placed here. */
#define NVMNW_CMDDATAECC3_VAL1_MINIMUM           ((uint32_t)0x00000000U)         /* !< Minimum value */
#define NVMNW_CMDDATAECC3_VAL1_MAXIMUM           ((uint32_t)0x0000FF00U)         /* !< Maximum value */

/* NVMNW_CMDWEPROTA Bits */
/* NVMNW_CMDWEPROTA[VAL] Bits */
#define NVMNW_CMDWEPROTA_VAL_OFS                 (0)                             /* !< VAL Offset */
#define NVMNW_CMDWEPROTA_VAL_MASK                ((uint32_t)0xFFFFFFFFU)         /* !< Each bit protects 1 sector.  bit
                                                                                    [0]:	When 1, sector 0 of the flash
                                                                                    memory will be protected from program
                                                                                    and erase. bit [1]:	When 1, sector
                                                                                    1 of the flash memory will be
                                                                                    protected from program 		and erase.
                                                                                    : 	: bit [31]:	When 1, sector 31 of
                                                                                    the flash memory will be protected
                                                                                    from program 		and erase. */
#define NVMNW_CMDWEPROTA_VAL_MINIMUM             ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDWEPROTA_VAL_MAXIMUM             ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDWEPROTB Bits */
/* NVMNW_CMDWEPROTB[VAL] Bits */
#define NVMNW_CMDWEPROTB_VAL_OFS                 (0)                             /* !< VAL Offset */
#define NVMNW_CMDWEPROTB_VAL_MASK                ((uint32_t)0x00000FFFU)         /* !< Each bit protects a group of 8
                                                                                    sectors.  When a bit is 1, the
                                                                                    associated 8 sectors in the flash
                                                                                    will be protected from program and
                                                                                    erase.  A maximum of 256 sectors can
                                                                                    be protected with this register. */
#define NVMNW_CMDWEPROTB_VAL_MINIMUM             ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDWEPROTB_VAL_MAXIMUM             ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_CMDWEPROTNM Bits */
/* NVMNW_CMDWEPROTNM[VAL] Bits */
#define NVMNW_CMDWEPROTNM_VAL_OFS                (0)                             /* !< VAL Offset */
#define NVMNW_CMDWEPROTNM_VAL_MASK               ((uint32_t)0x00000003U)         /* !< Each bit protects 1 sector.  bit
                                                                                    [0]:	When 1, sector 0 of the non-main
                                                                                    region will be protected from program
                                                                                    and erase. bit [1]:	When 1, sector
                                                                                    1 of the non-main region will be
                                                                                    protected from program 		and erase.
                                                                                    : 	: bit [31]:	When 1, sector 31 of
                                                                                    the non-main will be protected from
                                                                                    program 		and erase. */
#define NVMNW_CMDWEPROTNM_VAL_MINIMUM            ((uint32_t)0x00000000U)         /* !< Minimum value of [VAL] */
#define NVMNW_CMDWEPROTNM_VAL_MAXIMUM            ((uint32_t)0xFFFFFFFFU)         /* !< Maximum value of [VAL] */

/* NVMNW_STATCMD Bits */
/* NVMNW_STATCMD[CMDDONE] Bits */
#define NVMNW_STATCMD_CMDDONE_OFS                (0)                             /* !< CMDDONE Offset */
#define NVMNW_STATCMD_CMDDONE_MASK               ((uint32_t)0x00000001U)         /* !< Command Done */
#define NVMNW_STATCMD_CMDDONE_STATNOTDONE        ((uint32_t)0x00000000U)         /* !< Not Done */
#define NVMNW_STATCMD_CMDDONE_STATDONE           ((uint32_t)0x00000001U)         /* !< Done */
/* NVMNW_STATCMD[CMDPASS] Bits */
#define NVMNW_STATCMD_CMDPASS_OFS                (1)                             /* !< CMDPASS Offset */
#define NVMNW_STATCMD_CMDPASS_MASK               ((uint32_t)0x00000002U)         /* !< Command Pass - valid when CMD_DONE
                                                                                    field is 1 */
#define NVMNW_STATCMD_CMDPASS_STATFAIL           ((uint32_t)0x00000000U)         /* !< Fail */
#define NVMNW_STATCMD_CMDPASS_STATPASS           ((uint32_t)0x00000002U)         /* !< Pass */
/* NVMNW_STATCMD[CMDINPROGRESS] Bits */
#define NVMNW_STATCMD_CMDINPROGRESS_OFS          (2)                             /* !< CMDINPROGRESS Offset */
#define NVMNW_STATCMD_CMDINPROGRESS_MASK         ((uint32_t)0x00000004U)         /* !< Command In Progress */
#define NVMNW_STATCMD_CMDINPROGRESS_STATCOMPLETE ((uint32_t)0x00000000U)         /* !< Complete */
#define NVMNW_STATCMD_CMDINPROGRESS_STATINPROGRESS ((uint32_t)0x00000004U)         /* !< In Progress */
/* NVMNW_STATCMD[FAILWEPROT] Bits */
#define NVMNW_STATCMD_FAILWEPROT_OFS             (4)                             /* !< FAILWEPROT Offset */
#define NVMNW_STATCMD_FAILWEPROT_MASK            ((uint32_t)0x00000010U)         /* !< Command failed due to Write/Erase
                                                                                    Protect Sector Violation */
#define NVMNW_STATCMD_FAILWEPROT_STATNOFAIL      ((uint32_t)0x00000000U)         /* !< No Fail */
#define NVMNW_STATCMD_FAILWEPROT_STATFAIL        ((uint32_t)0x00000010U)         /* !< Fail */
/* NVMNW_STATCMD[FAILVERIFY] Bits */
#define NVMNW_STATCMD_FAILVERIFY_OFS             (5)                             /* !< FAILVERIFY Offset */
#define NVMNW_STATCMD_FAILVERIFY_MASK            ((uint32_t)0x00000020U)         /* !< Command failed due to verify error */
#define NVMNW_STATCMD_FAILVERIFY_STATNOFAIL      ((uint32_t)0x00000000U)         /* !< No Fail */
#define NVMNW_STATCMD_FAILVERIFY_STATFAIL        ((uint32_t)0x00000020U)         /* !< Fail */
/* NVMNW_STATCMD[FAILMISC] Bits */
#define NVMNW_STATCMD_FAILMISC_OFS               (12)                            /* !< FAILMISC Offset */
#define NVMNW_STATCMD_FAILMISC_MASK              ((uint32_t)0x00001000U)         /* !< Command failed due to error other
                                                                                    than write/erase protect violation or
                                                                                    verify error.  This is an extra bit
                                                                                    in case a new failure mechanism is
                                                                                    added which requires a status bit. */
#define NVMNW_STATCMD_FAILMISC_STATNOFAIL        ((uint32_t)0x00000000U)         /* !< No Fail */
#define NVMNW_STATCMD_FAILMISC_STATFAIL          ((uint32_t)0x00001000U)         /* !< Fail */
/* NVMNW_STATCMD[FAILILLADDR] Bits */
#define NVMNW_STATCMD_FAILILLADDR_OFS            (6)                             /* !< FAILILLADDR Offset */
#define NVMNW_STATCMD_FAILILLADDR_MASK           ((uint32_t)0x00000040U)         /* !< Command failed due to the use of an
                                                                                    illegal address */
#define NVMNW_STATCMD_FAILILLADDR_STATNOFAIL     ((uint32_t)0x00000000U)         /* !< No Fail */
#define NVMNW_STATCMD_FAILILLADDR_STATFAIL       ((uint32_t)0x00000040U)         /* !< Fail */
/* NVMNW_STATCMD[FAILMODE] Bits */
#define NVMNW_STATCMD_FAILMODE_OFS               (7)                             /* !< FAILMODE Offset */
#define NVMNW_STATCMD_FAILMODE_MASK              ((uint32_t)0x00000080U)         /* !< Command failed because a bank has
                                                                                    been set to a mode other than READ.
                                                                                    Program and Erase commands cannot be
                                                                                    initiated unless all banks are in
                                                                                    READ mode. */
#define NVMNW_STATCMD_FAILMODE_STATNOFAIL        ((uint32_t)0x00000000U)         /* !< No Fail */
#define NVMNW_STATCMD_FAILMODE_STATFAIL          ((uint32_t)0x00000080U)         /* !< Fail */
/* NVMNW_STATCMD[FAILINVDATA] Bits */
#define NVMNW_STATCMD_FAILINVDATA_OFS            (8)                             /* !< FAILINVDATA Offset */
#define NVMNW_STATCMD_FAILINVDATA_MASK           ((uint32_t)0x00000100U)         /* !< Program command failed because an
                                                                                    attempt was made to program a stored
                                                                                    0 value to a 1. */
#define NVMNW_STATCMD_FAILINVDATA_STATNOFAIL     ((uint32_t)0x00000000U)         /* !< No Fail */
#define NVMNW_STATCMD_FAILINVDATA_STATFAIL       ((uint32_t)0x00000100U)         /* !< Fail */

/* NVMNW_STATPCNT Bits */
/* NVMNW_STATPCNT[PULSECNT] Bits */
#define NVMNW_STATPCNT_PULSECNT_OFS              (0)                             /* !< PULSECNT Offset */
#define NVMNW_STATPCNT_PULSECNT_MASK             ((uint32_t)0x00000FFFU)         /* !< Current Pulse Counter Value */
#define NVMNW_STATPCNT_PULSECNT_MINIMUM          ((uint32_t)0x00000000U)         /* !< Minimum value */
#define NVMNW_STATPCNT_PULSECNT_MAXIMUM          ((uint32_t)0x00000FFFU)         /* !< Maximum value */


#ifdef __cplusplus
}
#endif

#endif /* hw_nvmnw__include */
