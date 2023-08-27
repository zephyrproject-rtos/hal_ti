/******************************************************************************
*  Filename:       hw_flash_h
******************************************************************************
*  Copyright (c) 2021 Texas Instruments Incorporated. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*
*  3) Neither the name of the copyright holder nor the names of its contributors
*     may be used to endorse or promote products derived from this software
*     without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#ifndef __HW_FLASH_H__
#define __HW_FLASH_H__

//*****************************************************************************
//
// This section defines the register offsets of
// FLASH component
//
//*****************************************************************************
// Interrupt Mask Register
#define FLASH_O_IMASK                                               0x00000028U

// Raw Interrupt Status Register
#define FLASH_O_RIS                                                 0x00000030U

// Masked Interrupt Status Register
#define FLASH_O_MIS                                                 0x00000038U

// Interrupt Set Register
#define FLASH_O_ISET                                                0x00000040U

// Interrupt Clear Register
#define FLASH_O_ICLR                                                0x00000048U

// Hardware Version Description Register
#define FLASH_O_DESC                                                0x000000FCU

// Command Execute Register
#define FLASH_O_CMDEXEC                                             0x00000100U

// Command Type Register
#define FLASH_O_CMDTYPE                                             0x00000104U

// Command Control Register
#define FLASH_O_CMDCTL                                              0x00000108U

// Command Address Register
#define FLASH_O_CMDADDR                                             0x00000120U

// Command Program Byte Enable Register
#define FLASH_O_CMDBYTEN                                            0x00000124U

// Command Data Register 0
#define FLASH_O_CMDDATA0                                            0x00000130U

// Command Data Register 1
#define FLASH_O_CMDDATA1                                            0x00000134U

// Command Data Register 2
#define FLASH_O_CMDDATA2                                            0x00000138U

// Command Data Register Bits 127:96
#define FLASH_O_CMDDATA3                                            0x0000013CU

// Command Write Erase Protect A Register
#define FLASH_O_CMDWEPROTA                                          0x000001D0U

// Command Write Erase Protect B Register
#define FLASH_O_CMDWEPROTB                                          0x000001D4U

// Command Write Erase Protect Non-Main Register
#define FLASH_O_CMDWEPROTNM                                         0x00000210U

// Command Write Erase Protect Trim Register
#define FLASH_O_CMDWEPROTTR                                         0x00000214U

// Command Write Erase Protect Engr Register
#define FLASH_O_CMDWEPROTEN                                         0x00000218U

// Command Configuration Register
#define FLASH_O_CFGCMD                                              0x000003B0U

// Pulse Counter Configuration Register
#define FLASH_O_CFGPCNT                                             0x000003B4U

// Command Status Register
#define FLASH_O_STATCMD                                             0x000003D0U

// Address Status Register
#define FLASH_O_STATADDR                                            0x000003D4U

// Pulse Count Status Register
#define FLASH_O_STATPCNT                                            0x000003D8U

// Mode Status Register
#define FLASH_O_STATMODE                                            0x000003DCU

// Global Information Register 0
#define FLASH_O_GBLINFO0                                            0x000003F0U

// Global Information Register 1
#define FLASH_O_GBLINFO1                                            0x000003F4U

// Global Information Register 2
#define FLASH_O_GBLINFO2                                            0x000003F8U

// Bank Information Register 0 for Bank 0
#define FLASH_O_BANK0INFO0                                          0x00000400U

// Bank Information Register 1 for Bank 0
#define FLASH_O_BANK0INFO1                                          0x00000404U

//*****************************************************************************
//
// Register: FLASH_O_IMASK
//
//*****************************************************************************
// Field:     [0] DONE
//
// Interrupt mask for DONE:
// 0: Interrupt is disabled in MIS register
// 1: Interrupt is enabled in MIS register
// ENUMs:
// ENABLED                  Interrupt will request an interrupt service
//                          routine and corresponding bit in IPSTANDARD.MIS
//                          will be set
// DISABLED                 Interrupt is masked out
#define FLASH_IMASK_DONE                                            0x00000001U
#define FLASH_IMASK_DONE_M                                          0x00000001U
#define FLASH_IMASK_DONE_S                                                   0U
#define FLASH_IMASK_DONE_ENABLED                                    0x00000001U
#define FLASH_IMASK_DONE_DISABLED                                   0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_RIS
//
//*****************************************************************************
// Field:     [0] DONE
//
// Flash wrapper operation completed.
// This interrupt bit is set by firmware or the corresponding bit in the ISET
// register.
// It is cleared by the corresponding bit in in the ICLR register or reading
// the IIDX register when this interrupt is the highest priority.
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define FLASH_RIS_DONE                                              0x00000001U
#define FLASH_RIS_DONE_M                                            0x00000001U
#define FLASH_RIS_DONE_S                                                     0U
#define FLASH_RIS_DONE_SET                                          0x00000001U
#define FLASH_RIS_DONE_CLR                                          0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_MIS
//
//*****************************************************************************
// Field:     [0] DONE
//
// Flash wrapper operation completed.
// This masked interrupt bit reflects the bitwise AND of the corresponding RIS
// and IMASK bits.
// ENUMs:
// SET                      Masked interrupt occurred
// CLR                      Masked interrupt did not occur
#define FLASH_MIS_DONE                                              0x00000001U
#define FLASH_MIS_DONE_M                                            0x00000001U
#define FLASH_MIS_DONE_S                                                     0U
#define FLASH_MIS_DONE_SET                                          0x00000001U
#define FLASH_MIS_DONE_CLR                                          0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_ISET
//
//*****************************************************************************
// Field:     [0] DONE
//
// 0: No effect
// 1: Set the DONE interrupt in the RIS register
// ENUMs:
// SET                      Set IPSTANDARD.RIS bit
// NO_EFFECT                Writing a 0 has no effect
#define FLASH_ISET_DONE                                             0x00000001U
#define FLASH_ISET_DONE_M                                           0x00000001U
#define FLASH_ISET_DONE_S                                                    0U
#define FLASH_ISET_DONE_SET                                         0x00000001U
#define FLASH_ISET_DONE_NO_EFFECT                                   0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_ICLR
//
//*****************************************************************************
// Field:     [0] DONE
//
// 0: No effect
// 1: Clear the DONE interrupt in the RIS register
// ENUMs:
// CLR                      Clear IPSTANDARD.RIS bit
// NO_EFFECT                Writing a 0 has no effect
#define FLASH_ICLR_DONE                                             0x00000001U
#define FLASH_ICLR_DONE_M                                           0x00000001U
#define FLASH_ICLR_DONE_S                                                    0U
#define FLASH_ICLR_DONE_CLR                                         0x00000001U
#define FLASH_ICLR_DONE_NO_EFFECT                                   0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODULEID
//
// Module ID
// ENUMs:
// MAXIMUM                  Highest possible value
// MINIMUM                  Smallest value
#define FLASH_DESC_MODULEID_W                                               16U
#define FLASH_DESC_MODULEID_M                                       0xFFFF0000U
#define FLASH_DESC_MODULEID_S                                               16U
#define FLASH_DESC_MODULEID_MAXIMUM                                 0xFFFF0000U
#define FLASH_DESC_MODULEID_MINIMUM                                 0x00000000U

// Field: [15:12] FEATUREVER
//
// Feature set
// ENUMs:
// MAXIMUM                  Maximum Value
// MINIMUM                  Minimum Value
#define FLASH_DESC_FEATUREVER_W                                              4U
#define FLASH_DESC_FEATUREVER_M                                     0x0000F000U
#define FLASH_DESC_FEATUREVER_S                                             12U
#define FLASH_DESC_FEATUREVER_MAXIMUM                               0x0000F000U
#define FLASH_DESC_FEATUREVER_MINIMUM                               0x00000000U

// Field:  [11:8] INSTNUM
//
// Instance number
// ENUMs:
// MAXIMUM                  Highest possible value
// MINIMUM                  Smallest value
#define FLASH_DESC_INSTNUM_W                                                 4U
#define FLASH_DESC_INSTNUM_M                                        0x00000F00U
#define FLASH_DESC_INSTNUM_S                                                 8U
#define FLASH_DESC_INSTNUM_MAXIMUM                                  0x00000F00U
#define FLASH_DESC_INSTNUM_MINIMUM                                  0x00000000U

// Field:   [7:4] MAJREV
//
// Major Revision
// ENUMs:
// MAXIMUM                  Highest possible value
// MINIMUM                  Smallest value
#define FLASH_DESC_MAJREV_W                                                  4U
#define FLASH_DESC_MAJREV_M                                         0x000000F0U
#define FLASH_DESC_MAJREV_S                                                  4U
#define FLASH_DESC_MAJREV_MAXIMUM                                   0x000000F0U
#define FLASH_DESC_MAJREV_MINIMUM                                   0x00000000U

// Field:   [3:0] MINREV
//
// Minor Revision
// ENUMs:
// MAXIMUM                  Highest possible value
// MINIMUM                  Smallest value
#define FLASH_DESC_MINREV_W                                                  4U
#define FLASH_DESC_MINREV_M                                         0x0000000FU
#define FLASH_DESC_MINREV_S                                                  0U
#define FLASH_DESC_MINREV_MAXIMUM                                   0x0000000FU
#define FLASH_DESC_MINREV_MINIMUM                                   0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDEXEC
//
//*****************************************************************************
// Field:     [0] VAL
//
// Command Execute value
// Initiates execution of the command specified in the CMDTYPE register.
// ENUMs:
// EXECUTE                  Command will execute or is executing in flash
//                          wrapper
// NOEXECUTE                Command will not execute or is not executing in
//                          flash wrapper
#define FLASH_CMDEXEC_VAL                                           0x00000001U
#define FLASH_CMDEXEC_VAL_M                                         0x00000001U
#define FLASH_CMDEXEC_VAL_S                                                  0U
#define FLASH_CMDEXEC_VAL_EXECUTE                                   0x00000001U
#define FLASH_CMDEXEC_VAL_NOEXECUTE                                 0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDTYPE
//
//*****************************************************************************
// Field:   [6:4] SIZE
//
// Command size
// ENUMs:
// BANK                     Operate on an entire flash bank
// SECTOR                   Operate on a flash sector
// EIGHTWORD                Operate on 8 flash words
// FOURWORD                 Operate on 4 flash words
// TWOWORD                  Operate on 2 flash words
// ONEWORD                  Operate on 1 flash word
#define FLASH_CMDTYPE_SIZE_W                                                 3U
#define FLASH_CMDTYPE_SIZE_M                                        0x00000070U
#define FLASH_CMDTYPE_SIZE_S                                                 4U
#define FLASH_CMDTYPE_SIZE_BANK                                     0x00000050U
#define FLASH_CMDTYPE_SIZE_SECTOR                                   0x00000040U
#define FLASH_CMDTYPE_SIZE_EIGHTWORD                                0x00000030U
#define FLASH_CMDTYPE_SIZE_FOURWORD                                 0x00000020U
#define FLASH_CMDTYPE_SIZE_TWOWORD                                  0x00000010U
#define FLASH_CMDTYPE_SIZE_ONEWORD                                  0x00000000U

// Field:   [2:0] COMMAND
//
// Command type
// ENUMs:
// BLANKVERIFY              Blank Verify - Check whether a flash word is in
//                          the erased state.
//                          This command may only be
//                          used with CMDTYPE.SIZE = ONEWORD
// CLEARSTATUS              Clear Status - Clear status bits in FW_SMSTAT
//                          only.
// MODECHANGE               Mode Change - Perform a mode change only, no other
//                          operation.
// ERASE                    Erase
// PROGRAM                  Program
// NOOP                     No Operation
#define FLASH_CMDTYPE_COMMAND_W                                              3U
#define FLASH_CMDTYPE_COMMAND_M                                     0x00000007U
#define FLASH_CMDTYPE_COMMAND_S                                              0U
#define FLASH_CMDTYPE_COMMAND_BLANKVERIFY                           0x00000006U
#define FLASH_CMDTYPE_COMMAND_CLEARSTATUS                           0x00000005U
#define FLASH_CMDTYPE_COMMAND_MODECHANGE                            0x00000004U
#define FLASH_CMDTYPE_COMMAND_ERASE                                 0x00000002U
#define FLASH_CMDTYPE_COMMAND_PROGRAM                               0x00000001U
#define FLASH_CMDTYPE_COMMAND_NOOP                                  0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDCTL
//
//*****************************************************************************
// Field:    [21] DATAVEREN
//
// Enable invalid data verify.
// This checks for 0->1 transitions in the memory when
// a program operation is initiated.  If such a transition is found, the
// program will
// fail with an error without executing the program.
// ENUMs:
// ENABLE                   Enable
// DISABLE                  Disable
#define FLASH_CMDCTL_DATAVEREN                                      0x00200000U
#define FLASH_CMDCTL_DATAVEREN_M                                    0x00200000U
#define FLASH_CMDCTL_DATAVEREN_S                                            21U
#define FLASH_CMDCTL_DATAVEREN_ENABLE                               0x00200000U
#define FLASH_CMDCTL_DATAVEREN_DISABLE                              0x00000000U

// Field:    [20] SSERASEDIS
//
// Disable Stair-Step Erase.  If set, the default VHV trim voltage setting will
// be used
// for all erase pulses.
// By default, this bit is reset, meaning that the VHV voltage will be stepped
// during
// successive erase pulses.  The step count, step voltage, begin and end
// voltages
// are all hard-wired.
// ENUMs:
// DISABLE                  Disable
// ENABLE                   Enable
#define FLASH_CMDCTL_SSERASEDIS                                     0x00100000U
#define FLASH_CMDCTL_SSERASEDIS_M                                   0x00100000U
#define FLASH_CMDCTL_SSERASEDIS_S                                           20U
#define FLASH_CMDCTL_SSERASEDIS_DISABLE                             0x00100000U
#define FLASH_CMDCTL_SSERASEDIS_ENABLE                              0x00000000U

// Field:    [16] ADDRXLATEOVR
//
// Override hardware address translation of address in CMDADDR from a
// system address to a bank address and bank ID.  Use data written to
// CMDADDR directly as the bank address.  Use the value written to
// CMDCTL.BANKSEL directly as the bank ID.  Use the value written to
// CMDCTL.REGIONSEL directly as the region ID.
// ENUMs:
// OVERRIDE                 Override
// NOOVERRIDE               Do not override
#define FLASH_CMDCTL_ADDRXLATEOVR                                   0x00010000U
#define FLASH_CMDCTL_ADDRXLATEOVR_M                                 0x00010000U
#define FLASH_CMDCTL_ADDRXLATEOVR_S                                         16U
#define FLASH_CMDCTL_ADDRXLATEOVR_OVERRIDE                          0x00010000U
#define FLASH_CMDCTL_ADDRXLATEOVR_NOOVERRIDE                        0x00000000U

// Field:  [12:9] REGIONSEL
//
// Bank Region
// A specific region ID can be written to this field to indicate to which
// region an
// operation is to be applied if CMDCTL.ADDRXLATEOVR is set.
// ENUMs:
// ENGR                     Engr Region
// TRIM                     Trim Region
// NONMAIN                  Non-Main Region
// MAIN                     Main Region
#define FLASH_CMDCTL_REGIONSEL_W                                             4U
#define FLASH_CMDCTL_REGIONSEL_M                                    0x00001E00U
#define FLASH_CMDCTL_REGIONSEL_S                                             9U
#define FLASH_CMDCTL_REGIONSEL_ENGR                                 0x00001000U
#define FLASH_CMDCTL_REGIONSEL_TRIM                                 0x00000800U
#define FLASH_CMDCTL_REGIONSEL_NONMAIN                              0x00000400U
#define FLASH_CMDCTL_REGIONSEL_MAIN                                 0x00000200U

// Field:   [3:0] MODESEL
//
// Mode
// This field is only used for the Mode Change command type.  Otherwise, bank
// and pump modes are set automaticlly through the NW hardware.
// ENUMs:
// ERASEBNK                 Erase Bank
// PGMMW                    Program Multiple Word
// ERASESECT                Erase Sector
// ERASEVER                 Erase Verify Mode
// PGMSW                    Program Single Word
// PGMVER                   Program Verify Mode
// RDMARG1B                 Read Margin 1B Mode
// RDMARG0B                 Read Margin 0B Mode
// RDMARG1                  Read Margin 1 Mode
// RDMARG0                  Read Margin 0 Mode
// READ                     Read Mode
#define FLASH_CMDCTL_MODESEL_W                                               4U
#define FLASH_CMDCTL_MODESEL_M                                      0x0000000FU
#define FLASH_CMDCTL_MODESEL_S                                               0U
#define FLASH_CMDCTL_MODESEL_ERASEBNK                               0x0000000FU
#define FLASH_CMDCTL_MODESEL_PGMMW                                  0x0000000EU
#define FLASH_CMDCTL_MODESEL_ERASESECT                              0x0000000CU
#define FLASH_CMDCTL_MODESEL_ERASEVER                               0x0000000BU
#define FLASH_CMDCTL_MODESEL_PGMSW                                  0x0000000AU
#define FLASH_CMDCTL_MODESEL_PGMVER                                 0x00000009U
#define FLASH_CMDCTL_MODESEL_RDMARG1B                               0x00000007U
#define FLASH_CMDCTL_MODESEL_RDMARG0B                               0x00000006U
#define FLASH_CMDCTL_MODESEL_RDMARG1                                0x00000004U
#define FLASH_CMDCTL_MODESEL_RDMARG0                                0x00000002U
#define FLASH_CMDCTL_MODESEL_READ                                   0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDADDR
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Address value
// ENUMs:
// MAXIMUM                  Maximum value of VAL
// MINIMUM                  Minimum value of VAL
#define FLASH_CMDADDR_VAL_W                                                 32U
#define FLASH_CMDADDR_VAL_M                                         0xFFFFFFFFU
#define FLASH_CMDADDR_VAL_S                                                  0U
#define FLASH_CMDADDR_VAL_MAXIMUM                                   0xFFFFFFFFU
#define FLASH_CMDADDR_VAL_MINIMUM                                   0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDBYTEN
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Command Byte Enable value.
// A 1-bit per flash word byte value is placed in this register.
// ENUMs:
// MAXIMUM                  Maximum value of VAL
// MINIMUM                  Minimum value of VAL
#define FLASH_CMDBYTEN_VAL_W                                                16U
#define FLASH_CMDBYTEN_VAL_M                                        0x0000FFFFU
#define FLASH_CMDBYTEN_VAL_S                                                 0U
#define FLASH_CMDBYTEN_VAL_MAXIMUM                                  0x0003FFFFU
#define FLASH_CMDBYTEN_VAL_MINIMUM                                  0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDDATA0
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// A 32-bit data value is placed in this field.
// ENUMs:
// MAXIMUM                  Maximum value of VAL
// MINIMUM                  Minimum value of VAL
#define FLASH_CMDDATA0_VAL_W                                                32U
#define FLASH_CMDDATA0_VAL_M                                        0xFFFFFFFFU
#define FLASH_CMDDATA0_VAL_S                                                 0U
#define FLASH_CMDDATA0_VAL_MAXIMUM                                  0xFFFFFFFFU
#define FLASH_CMDDATA0_VAL_MINIMUM                                  0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDDATA1
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// A 32-bit data value is placed in this field.
// ENUMs:
// MAXIMUM                  Maximum value of VAL
// MINIMUM                  Minimum value of VAL
#define FLASH_CMDDATA1_VAL_W                                                32U
#define FLASH_CMDDATA1_VAL_M                                        0xFFFFFFFFU
#define FLASH_CMDDATA1_VAL_S                                                 0U
#define FLASH_CMDDATA1_VAL_MAXIMUM                                  0xFFFFFFFFU
#define FLASH_CMDDATA1_VAL_MINIMUM                                  0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDDATA2
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// A 32-bit data value is placed in this field.
// ENUMs:
// MAXIMUM                  Maximum value of VAL
// MINIMUM                  Minimum value of VAL
#define FLASH_CMDDATA2_VAL_W                                                32U
#define FLASH_CMDDATA2_VAL_M                                        0xFFFFFFFFU
#define FLASH_CMDDATA2_VAL_S                                                 0U
#define FLASH_CMDDATA2_VAL_MAXIMUM                                  0xFFFFFFFFU
#define FLASH_CMDDATA2_VAL_MINIMUM                                  0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDDATA3
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// A 32-bit data value is placed in this field.
// ENUMs:
// MAXIMUM                  Maximum value of VAL
// MINIMUM                  Minimum value of VAL
#define FLASH_CMDDATA3_VAL_W                                                32U
#define FLASH_CMDDATA3_VAL_M                                        0xFFFFFFFFU
#define FLASH_CMDDATA3_VAL_S                                                 0U
#define FLASH_CMDDATA3_VAL_MAXIMUM                                  0xFFFFFFFFU
#define FLASH_CMDDATA3_VAL_MINIMUM                                  0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDWEPROTA
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Each bit protects 1 sector.
//
// bit [0]:	When 1, sector 0 of the flash memory will be protected from program
// 		and erase.
// bit [1]:	When 1, sector 1 of the flash memory will be protected from program
// 		and erase.
// 	:
// 	:
// bit [31]:	When 1, sector 31 of the flash memory will be protected from
// program
// 		and erase.
// ENUMs:
// MAXIMUM                  Maximum value of VAL
// MINIMUM                  Minimum value of VAL
#define FLASH_CMDWEPROTA_VAL_W                                              32U
#define FLASH_CMDWEPROTA_VAL_M                                      0xFFFFFFFFU
#define FLASH_CMDWEPROTA_VAL_S                                               0U
#define FLASH_CMDWEPROTA_VAL_MAXIMUM                                0xFFFFFFFFU
#define FLASH_CMDWEPROTA_VAL_MINIMUM                                0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDWEPROTB
//
//*****************************************************************************
// Field:  [27:0] VAL
//
// Each bit protects a group of 8 sectors.  When a bit is 1, the associated 8
// sectors
// in the flash will be protected from program and erase.  A maximum of 256
// sectors can be protected with this register.
// ENUMs:
// MAXIMUM                  Maximum value of VAL
// MINIMUM                  Minimum value of VAL
#define FLASH_CMDWEPROTB_VAL_W                                              28U
#define FLASH_CMDWEPROTB_VAL_M                                      0x0FFFFFFFU
#define FLASH_CMDWEPROTB_VAL_S                                               0U
#define FLASH_CMDWEPROTB_VAL_MAXIMUM                                0xFFFFFFFFU
#define FLASH_CMDWEPROTB_VAL_MINIMUM                                0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDWEPROTNM
//
//*****************************************************************************
// Field:     [0] VAL
//
// Each bit protects 1 sector.
//
// bit [0]:	When 1, sector 0 of the non-main region will be protected from
// program
// 		and erase.
// bit [1]:	When 1, sector 1 of the non-main region will be protected from
// program
// 		and erase.
// 	:
// 	:
// bit [31]:	When 1, sector 31 of the non-main will be protected from program
// 		and erase.
// ENUMs:
// MAXIMUM                  Maximum value of VAL
// MINIMUM                  Minimum value of VAL
#define FLASH_CMDWEPROTNM_VAL                                       0x00000001U
#define FLASH_CMDWEPROTNM_VAL_M                                     0x00000001U
#define FLASH_CMDWEPROTNM_VAL_S                                              0U
#define FLASH_CMDWEPROTNM_VAL_MAXIMUM                               0xFFFFFFFFU
#define FLASH_CMDWEPROTNM_VAL_MINIMUM                               0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDWEPROTTR
//
//*****************************************************************************
// Field:     [0] VAL
//
// Each bit protects 1 sector.
//
// bit [0]:	When 1, sector 0 of the engr region will be protected from program
// 		and erase.
// bit [1]:	When 1, sector 1 of the engr region will be protected from program
// 		and erase.
// 	:
// 	:
// bit [31]:	When 1, sector 31 of the engr region will be protected from
// program
// 		and erase.
// ENUMs:
// MAXIMUM                  Maximum value of VAL
// MINIMUM                  Minimum value of VAL
#define FLASH_CMDWEPROTTR_VAL                                       0x00000001U
#define FLASH_CMDWEPROTTR_VAL_M                                     0x00000001U
#define FLASH_CMDWEPROTTR_VAL_S                                              0U
#define FLASH_CMDWEPROTTR_VAL_MAXIMUM                               0xFFFFFFFFU
#define FLASH_CMDWEPROTTR_VAL_MINIMUM                               0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CMDWEPROTEN
//
//*****************************************************************************
// Field:     [0] VAL
//
// Each bit protects 1 sector.
//
// bit [0]:	When 1, sector 0 of the engr region will be protected from program
// 		and erase.
// bit [1]:	When 1, sector 1 of the engr region will be protected from program
// 		and erase.
// 	:
// 	:
// bit [31]:	When 1, sector 31 of the engr region will be protected from
// program
// 		and erase.
// ENUMs:
// MAXIMUM                  Maximum value of VAL
// MINIMUM                  Minimum value of VAL
#define FLASH_CMDWEPROTEN_VAL                                       0x00000001U
#define FLASH_CMDWEPROTEN_VAL_M                                     0x00000001U
#define FLASH_CMDWEPROTEN_VAL_S                                              0U
#define FLASH_CMDWEPROTEN_VAL_MAXIMUM                               0xFFFFFFFFU
#define FLASH_CMDWEPROTEN_VAL_MINIMUM                               0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CFGCMD
//
//*****************************************************************************
// Field:   [3:0] WAITSTATE
//
// Wait State setting for verify reads
// ENUMs:
// MAXIMUM                  Maximum value
// MINIMUM                  Minimum value
#define FLASH_CFGCMD_WAITSTATE_W                                             4U
#define FLASH_CFGCMD_WAITSTATE_M                                    0x0000000FU
#define FLASH_CFGCMD_WAITSTATE_S                                             0U
#define FLASH_CFGCMD_WAITSTATE_MAXIMUM                              0x0000000FU
#define FLASH_CFGCMD_WAITSTATE_MINIMUM                              0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_CFGPCNT
//
//*****************************************************************************
// Field:  [11:4] MAXPCNTVAL
//
// Override maximum pulse counter with this value.
// If MAXPCNTOVR = 0, then this field is ignored.
// If MAXPCNTOVR = 1 and MAXERSPCNTOVR = 0, then this value will be used
// to override the max pulse count for both program and erase.  Full max value
// will be {4'h0, MAXPCNTVAL} .
// If MAXPCNTOVR = 1 and MAXERSPCNTOVR = 1, then this value will be used
// to override the max pulse count for program only.  Full max value will be
// {4'h0, MAXPCNTVAL}.
// ENUMs:
// MAXIMUM                  Maximum value
// MINIMUM                  Minimum value
#define FLASH_CFGPCNT_MAXPCNTVAL_W                                           8U
#define FLASH_CFGPCNT_MAXPCNTVAL_M                                  0x00000FF0U
#define FLASH_CFGPCNT_MAXPCNTVAL_S                                           4U
#define FLASH_CFGPCNT_MAXPCNTVAL_MAXIMUM                            0x00000FF0U
#define FLASH_CFGPCNT_MAXPCNTVAL_MINIMUM                            0x00000000U

// Field:     [0] MAXPCNTOVR
//
// Override hard-wired maximum pulse count.  If MAXERSPCNTOVR
// is not set, then setting this value alone will override the max pulse count
// for
// both program and erase.  If MAXERSPCNTOVR is set, then this bit will only
// control the max pulse count setting for program.
// By default, this bit is 0, and a hard-wired max pulse count is used.
// ENUMs:
// OVERRIDE                 Use value from MAXPCNTVAL field as maximum puse
//                          count
// DEFAULT                  Use hard-wired (default) value for maximum pulse
//                          count
#define FLASH_CFGPCNT_MAXPCNTOVR                                    0x00000001U
#define FLASH_CFGPCNT_MAXPCNTOVR_M                                  0x00000001U
#define FLASH_CFGPCNT_MAXPCNTOVR_S                                           0U
#define FLASH_CFGPCNT_MAXPCNTOVR_OVERRIDE                           0x00000001U
#define FLASH_CFGPCNT_MAXPCNTOVR_DEFAULT                            0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_STATCMD
//
//*****************************************************************************
// Field:    [12] FAILMISC
//
// Command failed due to error other than write/erase protect violation or
// verify
// error.  This is an extra bit in case a new failure mechanism is added which
// requires a status bit.
// ENUMs:
// STATFAIL                 Fail
// STATNOFAIL               No Fail
#define FLASH_STATCMD_FAILMISC                                      0x00001000U
#define FLASH_STATCMD_FAILMISC_M                                    0x00001000U
#define FLASH_STATCMD_FAILMISC_S                                            12U
#define FLASH_STATCMD_FAILMISC_STATFAIL                             0x00001000U
#define FLASH_STATCMD_FAILMISC_STATNOFAIL                           0x00000000U

// Field:     [8] FAILINVDATA
//
// Program command failed because an attempt was made to program a stored
// 0 value to a 1.
// ENUMs:
// STATFAIL                 Fail
// STATNOFAIL               No Fail
#define FLASH_STATCMD_FAILINVDATA                                   0x00000100U
#define FLASH_STATCMD_FAILINVDATA_M                                 0x00000100U
#define FLASH_STATCMD_FAILINVDATA_S                                          8U
#define FLASH_STATCMD_FAILINVDATA_STATFAIL                          0x00000100U
#define FLASH_STATCMD_FAILINVDATA_STATNOFAIL                        0x00000000U

// Field:     [7] FAILMODE
//
// Command failed because a bank has been set to a mode other than READ.
// Program and Erase commands cannot be initiated unless all banks are in READ
// mode.
// ENUMs:
// STATFAIL                 Fail
// STATNOFAIL               No Fail
#define FLASH_STATCMD_FAILMODE                                      0x00000080U
#define FLASH_STATCMD_FAILMODE_M                                    0x00000080U
#define FLASH_STATCMD_FAILMODE_S                                             7U
#define FLASH_STATCMD_FAILMODE_STATFAIL                             0x00000080U
#define FLASH_STATCMD_FAILMODE_STATNOFAIL                           0x00000000U

// Field:     [6] FAILILLADDR
//
// Command failed due to the use of an illegal address
// ENUMs:
// STATFAIL                 Fail
// STATNOFAIL               No Fail
#define FLASH_STATCMD_FAILILLADDR                                   0x00000040U
#define FLASH_STATCMD_FAILILLADDR_M                                 0x00000040U
#define FLASH_STATCMD_FAILILLADDR_S                                          6U
#define FLASH_STATCMD_FAILILLADDR_STATFAIL                          0x00000040U
#define FLASH_STATCMD_FAILILLADDR_STATNOFAIL                        0x00000000U

// Field:     [5] FAILVERIFY
//
// Command failed due to verify error
// ENUMs:
// STATFAIL                 Fail
// STATNOFAIL               No Fail
#define FLASH_STATCMD_FAILVERIFY                                    0x00000020U
#define FLASH_STATCMD_FAILVERIFY_M                                  0x00000020U
#define FLASH_STATCMD_FAILVERIFY_S                                           5U
#define FLASH_STATCMD_FAILVERIFY_STATFAIL                           0x00000020U
#define FLASH_STATCMD_FAILVERIFY_STATNOFAIL                         0x00000000U

// Field:     [4] FAILWEPROT
//
// Command failed due to Write/Erase Protect Sector Violation
// ENUMs:
// STATFAIL                 Fail
// STATNOFAIL               No Fail
#define FLASH_STATCMD_FAILWEPROT                                    0x00000010U
#define FLASH_STATCMD_FAILWEPROT_M                                  0x00000010U
#define FLASH_STATCMD_FAILWEPROT_S                                           4U
#define FLASH_STATCMD_FAILWEPROT_STATFAIL                           0x00000010U
#define FLASH_STATCMD_FAILWEPROT_STATNOFAIL                         0x00000000U

// Field:     [2] CMDINPROGRESS
//
// Command In Progress
// ENUMs:
// STATINPROGRESS           In Progress
// STATCOMPLETE             Complete
#define FLASH_STATCMD_CMDINPROGRESS                                 0x00000004U
#define FLASH_STATCMD_CMDINPROGRESS_M                               0x00000004U
#define FLASH_STATCMD_CMDINPROGRESS_S                                        2U
#define FLASH_STATCMD_CMDINPROGRESS_STATINPROGRESS                  0x00000004U
#define FLASH_STATCMD_CMDINPROGRESS_STATCOMPLETE                    0x00000000U

// Field:     [1] CMDPASS
//
// Command Pass - valid when CMD_DONE field is 1
// ENUMs:
// STATPASS                 Pass
// STATFAIL                 Fail
#define FLASH_STATCMD_CMDPASS                                       0x00000002U
#define FLASH_STATCMD_CMDPASS_M                                     0x00000002U
#define FLASH_STATCMD_CMDPASS_S                                              1U
#define FLASH_STATCMD_CMDPASS_STATPASS                              0x00000002U
#define FLASH_STATCMD_CMDPASS_STATFAIL                              0x00000000U

// Field:     [0] CMDDONE
//
// Command Done
// ENUMs:
// STATDONE                 Done
// STATNOTDONE              Not Done
#define FLASH_STATCMD_CMDDONE                                       0x00000001U
#define FLASH_STATCMD_CMDDONE_M                                     0x00000001U
#define FLASH_STATCMD_CMDDONE_S                                              0U
#define FLASH_STATCMD_CMDDONE_STATDONE                              0x00000001U
#define FLASH_STATCMD_CMDDONE_STATNOTDONE                           0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_STATADDR
//
//*****************************************************************************
// Field: [25:21] BANKID
//
// Current Bank ID
// A bank indicator is stored in this register which represents the current
// bank on
// which the state  machine is operating.  There is 1 bit per bank.
// ENUMs:
// BANK4                    Bank 4
// BANK3                    Bank 3
// BANK2                    Bank 2
// BANK1                    Bank 1
// BANK0                    Bank 0
#define FLASH_STATADDR_BANKID_W                                              5U
#define FLASH_STATADDR_BANKID_M                                     0x03E00000U
#define FLASH_STATADDR_BANKID_S                                             21U
#define FLASH_STATADDR_BANKID_BANK4                                 0x02000000U
#define FLASH_STATADDR_BANKID_BANK3                                 0x01000000U
#define FLASH_STATADDR_BANKID_BANK2                                 0x00800000U
#define FLASH_STATADDR_BANKID_BANK1                                 0x00400000U
#define FLASH_STATADDR_BANKID_BANK0                                 0x00200000U

// Field: [20:16] REGIONID
//
// Current Region ID
// A region indicator is stored in this register which represents the current
// flash
// region on which the state  machine is operating.
// ENUMs:
// ENGR                     Engr Region
// TRIM                     Trim Region
// NONMAIN                  Non-Main Region
// MAIN                     Main Region
#define FLASH_STATADDR_REGIONID_W                                            5U
#define FLASH_STATADDR_REGIONID_M                                   0x001F0000U
#define FLASH_STATADDR_REGIONID_S                                           16U
#define FLASH_STATADDR_REGIONID_ENGR                                0x00080000U
#define FLASH_STATADDR_REGIONID_TRIM                                0x00040000U
#define FLASH_STATADDR_REGIONID_NONMAIN                             0x00020000U
#define FLASH_STATADDR_REGIONID_MAIN                                0x00010000U

// Field:  [15:0] BANKADDR
//
// Current Bank Address
// A bank offset address is stored in this register.
// ENUMs:
// MAXIMUM                  Maximum value
// MINIMUM                  Minimum value
#define FLASH_STATADDR_BANKADDR_W                                           16U
#define FLASH_STATADDR_BANKADDR_M                                   0x0000FFFFU
#define FLASH_STATADDR_BANKADDR_S                                            0U
#define FLASH_STATADDR_BANKADDR_MAXIMUM                             0x0000FFFFU
#define FLASH_STATADDR_BANKADDR_MINIMUM                             0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_STATPCNT
//
//*****************************************************************************
// Field:  [11:0] PULSECNT
//
// Current Pulse Counter Value
// ENUMs:
// MAXIMUM                  Maximum value
// MINIMUM                  Minimum value
#define FLASH_STATPCNT_PULSECNT_W                                           12U
#define FLASH_STATPCNT_PULSECNT_M                                   0x00000FFFU
#define FLASH_STATPCNT_PULSECNT_S                                            0U
#define FLASH_STATPCNT_PULSECNT_MAXIMUM                             0x00000FFFU
#define FLASH_STATPCNT_PULSECNT_MINIMUM                             0x00000000U

//*****************************************************************************
//
// Register: FLASH_O_STATMODE
//
//*****************************************************************************
// Field:    [17] BANK1TRDY
//
// Bank 1T Ready.
// Bank(s) are ready for 1T access.  This is accomplished when the bank and
// pump
// have been trimmed.
// ENUMs:
// TRUE                     Ready
// FALSE                    Not ready
#define FLASH_STATMODE_BANK1TRDY                                    0x00020000U
#define FLASH_STATMODE_BANK1TRDY_M                                  0x00020000U
#define FLASH_STATMODE_BANK1TRDY_S                                          17U
#define FLASH_STATMODE_BANK1TRDY_TRUE                               0x00020000U
#define FLASH_STATMODE_BANK1TRDY_FALSE                              0x00000000U

// Field:    [16] BANK2TRDY
//
// Bank 2T Ready.
// Bank(s) are ready for 2T access.  This is accomplished when the pump has
// fully driven power rails to the bank(s).
// ENUMs:
// TRUE                     Ready
// FALSE                    Not ready
#define FLASH_STATMODE_BANK2TRDY                                    0x00010000U
#define FLASH_STATMODE_BANK2TRDY_M                                  0x00010000U
#define FLASH_STATMODE_BANK2TRDY_S                                          16U
#define FLASH_STATMODE_BANK2TRDY_TRUE                               0x00010000U
#define FLASH_STATMODE_BANK2TRDY_FALSE                              0x00000000U

// Field:  [11:8] BANKMODE
//
// Indicates mode of bank(s) that are not in READ mode
// ENUMs:
// ERASEBNK                 Erase Bank
// PGMMW                    Program Multiple Word
// ERASESECT                Erase Sector
// ERASEVER                 Erase Verify Mode
// PGMSW                    Program Single Word
// PGMVER                   Program Verify Mode
// RDMARG1B                 Read Margin 1B Mode
// RDMARG0B                 Read Margin 0B Mode
// RDMARG1                  Read Margin 1 Mode
// RDMARG0                  Read Margin 0 Mode
// READ                     Read Mode
#define FLASH_STATMODE_BANKMODE_W                                            4U
#define FLASH_STATMODE_BANKMODE_M                                   0x00000F00U
#define FLASH_STATMODE_BANKMODE_S                                            8U
#define FLASH_STATMODE_BANKMODE_ERASEBNK                            0x00000F00U
#define FLASH_STATMODE_BANKMODE_PGMMW                               0x00000E00U
#define FLASH_STATMODE_BANKMODE_ERASESECT                           0x00000C00U
#define FLASH_STATMODE_BANKMODE_ERASEVER                            0x00000B00U
#define FLASH_STATMODE_BANKMODE_PGMSW                               0x00000A00U
#define FLASH_STATMODE_BANKMODE_PGMVER                              0x00000900U
#define FLASH_STATMODE_BANKMODE_RDMARG1B                            0x00000700U
#define FLASH_STATMODE_BANKMODE_RDMARG0B                            0x00000600U
#define FLASH_STATMODE_BANKMODE_RDMARG1                             0x00000400U
#define FLASH_STATMODE_BANKMODE_RDMARG0                             0x00000200U
#define FLASH_STATMODE_BANKMODE_READ                                0x00000000U

// Field:     [0] BANKNOTINRD
//
// Bank not in read mode.
// Indicates which banks are not in READ mode.  There is 1 bit per bank.
// ENUMs:
// BANK4                    Bank 4
// BANK3                    Bank 3
// BANK2                    Bank 2
// BANK1                    Bank 1
// BANK0                    Bank 0
#define FLASH_STATMODE_BANKNOTINRD                                  0x00000001U
#define FLASH_STATMODE_BANKNOTINRD_M                                0x00000001U
#define FLASH_STATMODE_BANKNOTINRD_S                                         0U
#define FLASH_STATMODE_BANKNOTINRD_BANK4                            0x00000010U
#define FLASH_STATMODE_BANKNOTINRD_BANK3                            0x00000008U
#define FLASH_STATMODE_BANKNOTINRD_BANK2                            0x00000004U
#define FLASH_STATMODE_BANKNOTINRD_BANK1                            0x00000002U
#define FLASH_STATMODE_BANKNOTINRD_BANK0                            0x00000001U

//*****************************************************************************
//
// Register: FLASH_O_GBLINFO0
//
//*****************************************************************************
// Field: [18:16] NUMBANKS
//
// Number of banks instantiated
// Minimum:	1
// Maximum:	5
// ENUMs:
// MAXIMUM                  Maximum value
// MINIMUM                  Minimum value
#define FLASH_GBLINFO0_NUMBANKS_W                                            3U
#define FLASH_GBLINFO0_NUMBANKS_M                                   0x00070000U
#define FLASH_GBLINFO0_NUMBANKS_S                                           16U
#define FLASH_GBLINFO0_NUMBANKS_MAXIMUM                             0x00050000U
#define FLASH_GBLINFO0_NUMBANKS_MINIMUM                             0x00010000U

// Field:  [15:0] SECTORSIZE
//
// Sector size in bytes
// ENUMs:
// TWOKB                    Sector size is TWOKB
// ONEKB                    Sector size is ONEKB
#define FLASH_GBLINFO0_SECTORSIZE_W                                         16U
#define FLASH_GBLINFO0_SECTORSIZE_M                                 0x0000FFFFU
#define FLASH_GBLINFO0_SECTORSIZE_S                                          0U
#define FLASH_GBLINFO0_SECTORSIZE_TWOKB                             0x00000800U
#define FLASH_GBLINFO0_SECTORSIZE_ONEKB                             0x00000400U

//*****************************************************************************
//
// Register: FLASH_O_GBLINFO1
//
//*****************************************************************************
// Field: [18:16] REDWIDTH
//
// Redundant data width in bits
// ENUMs:
// W4BIT                    Redundant data width is 4 bits
// W2BIT                    Redundant data width is 2 bits
// W0BIT                    Redundant data width is 0.  Redundancy/Repair not
//                          present.
#define FLASH_GBLINFO1_REDWIDTH_W                                            3U
#define FLASH_GBLINFO1_REDWIDTH_M                                   0x00070000U
#define FLASH_GBLINFO1_REDWIDTH_S                                           16U
#define FLASH_GBLINFO1_REDWIDTH_W4BIT                               0x00040000U
#define FLASH_GBLINFO1_REDWIDTH_W2BIT                               0x00020000U
#define FLASH_GBLINFO1_REDWIDTH_W0BIT                               0x00000000U

// Field:  [12:8] ECCWIDTH
//
// ECC data width in bits
// ENUMs:
// W16BIT                   ECC data width is 16 bits
// W8BIT                    ECC data width is 8 bits
// W0BIT                    ECC data width is 0.  ECC not used.
#define FLASH_GBLINFO1_ECCWIDTH_W                                            5U
#define FLASH_GBLINFO1_ECCWIDTH_M                                   0x00001F00U
#define FLASH_GBLINFO1_ECCWIDTH_S                                            8U
#define FLASH_GBLINFO1_ECCWIDTH_W16BIT                              0x00001000U
#define FLASH_GBLINFO1_ECCWIDTH_W8BIT                               0x00000800U
#define FLASH_GBLINFO1_ECCWIDTH_W0BIT                               0x00000000U

// Field:   [7:0] DATAWIDTH
//
// Data width in bits
// ENUMs:
// W128BIT                  Data width is 128 bits
// W64BIT                   Data width is 64 bits
#define FLASH_GBLINFO1_DATAWIDTH_W                                           8U
#define FLASH_GBLINFO1_DATAWIDTH_M                                  0x000000FFU
#define FLASH_GBLINFO1_DATAWIDTH_S                                           0U
#define FLASH_GBLINFO1_DATAWIDTH_W128BIT                            0x00000080U
#define FLASH_GBLINFO1_DATAWIDTH_W64BIT                             0x00000040U

//*****************************************************************************
//
// Register: FLASH_O_GBLINFO2
//
//*****************************************************************************
// Field:   [3:0] DATAREGISTERS
//
// Number of data registers present.
// ENUMs:
// MAXIMUM                  Maximum value of DATAREGISTERS
// MINIMUM                  Minimum value of DATAREGISTERS
#define FLASH_GBLINFO2_DATAREGISTERS_W                                       4U
#define FLASH_GBLINFO2_DATAREGISTERS_M                              0x0000000FU
#define FLASH_GBLINFO2_DATAREGISTERS_S                                       0U
#define FLASH_GBLINFO2_DATAREGISTERS_MAXIMUM                        0x00000008U
#define FLASH_GBLINFO2_DATAREGISTERS_MINIMUM                        0x00000001U

//*****************************************************************************
//
// Register: FLASH_O_BANK0INFO0
//
//*****************************************************************************
// Field:  [11:0] MAINSIZE
//
// Main region size in sectors
// Minimum:	0x8 (8)
// Maximum:	0x200 (512)
// ENUMs:
// MAXSECTORS               Maximum value of MAINSIZE
// MINSECTORS               Minimum value of MAINSIZE
#define FLASH_BANK0INFO0_MAINSIZE_W                                         12U
#define FLASH_BANK0INFO0_MAINSIZE_M                                 0x00000FFFU
#define FLASH_BANK0INFO0_MAINSIZE_S                                          0U
#define FLASH_BANK0INFO0_MAINSIZE_MAXSECTORS                        0x00000200U
#define FLASH_BANK0INFO0_MAINSIZE_MINSECTORS                        0x00000008U

//*****************************************************************************
//
// Register: FLASH_O_BANK0INFO1
//
//*****************************************************************************
// Field: [23:16] ENGRSIZE
//
// Engr region size in sectors
// Minimum:	0x0 (0)
// Maximum:	0x10 (16)
// ENUMs:
// MAXSECTORS               Maximum value of ENGRSIZE
// MINSECTORS               Minimum value of ENGRSIZE
#define FLASH_BANK0INFO1_ENGRSIZE_W                                          8U
#define FLASH_BANK0INFO1_ENGRSIZE_M                                 0x00FF0000U
#define FLASH_BANK0INFO1_ENGRSIZE_S                                         16U
#define FLASH_BANK0INFO1_ENGRSIZE_MAXSECTORS                        0x00200000U
#define FLASH_BANK0INFO1_ENGRSIZE_MINSECTORS                        0x00000000U

// Field:  [15:8] TRIMSIZE
//
// Trim region size in sectors
// Minimum:	0x0 (0)
// Maximum:	0x10 (16)
// ENUMs:
// MAXSECTORS               Maximum value of TRIMSIZE
// MINSECTORS               Minimum value of TRIMSIZE
#define FLASH_BANK0INFO1_TRIMSIZE_W                                          8U
#define FLASH_BANK0INFO1_TRIMSIZE_M                                 0x0000FF00U
#define FLASH_BANK0INFO1_TRIMSIZE_S                                          8U
#define FLASH_BANK0INFO1_TRIMSIZE_MAXSECTORS                        0x00002000U
#define FLASH_BANK0INFO1_TRIMSIZE_MINSECTORS                        0x00000000U

// Field:   [7:0] NONMAINSIZE
//
// Non-main region size in sectors
// Minimum:	0x0 (0)
// Maximum:	0x10 (16)
// ENUMs:
// MAXSECTORS               Maximum value of NONMAINSIZE
// MINSECTORS               Minimum value of NONMAINSIZE
#define FLASH_BANK0INFO1_NONMAINSIZE_W                                       8U
#define FLASH_BANK0INFO1_NONMAINSIZE_M                              0x000000FFU
#define FLASH_BANK0INFO1_NONMAINSIZE_S                                       0U
#define FLASH_BANK0INFO1_NONMAINSIZE_MAXSECTORS                     0x00000020U
#define FLASH_BANK0INFO1_NONMAINSIZE_MINSECTORS                     0x00000000U


#endif // __FLASH__
