/******************************************************************************
*  Filename:       hw_soc_debugss.h
*
*  Description:    Defines and prototypes for the SOC_DEBUGSS peripheral.
*
*  Copyright (c) 2023-2025, Texas Instruments Incorporated
*  All rights reserved.
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
*  3) Neither the name of the ORGANIZATION nor the names of its contributors may
*     be used to endorse or promote products derived from this software without
*     specific prior written permission.
*
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
*
******************************************************************************/
#ifndef __HW_SOC_DEBUGSS_H__
#define __HW_SOC_DEBUGSS_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the SOC_DEBUGSS component

--------------------------------------------------------------------------------- */

//CFGAP Device ID
#define SOC_DEBUGSS_O_CFGAPDEVID                                     0x00000000U

//CFGAP Device User Code
#define SOC_DEBUGSS_O_CFGAPDEVUC                                     0x00000004U

//CFGAP DEBUGSS Version
#define SOC_DEBUGSS_O_DBGSSVER                                       0x00000008U

//CFGAP Boot Diag
#define SOC_DEBUGSS_O_CFGAPBOOT                                      0x00000010U

//CFGAP Life-cycle
#define SOC_DEBUGSS_O_CFGAPLCST                                      0x00000014U

//DFT Enable
#define SOC_DEBUGSS_O_DFTEN                                          0x00000018U

//Reset Request
#define SOC_DEBUGSS_O_RSTREQ                                         0x0000001CU

//CFGAP Unique Device 0
#define SOC_DEBUGSS_O_CFGAPUDID0                                     0x00000028U

//CFGAP Unique Device 1
#define SOC_DEBUGSS_O_CFGAPUDID1                                     0x0000002CU

//CFGAP Identification Register
#define SOC_DEBUGSS_O_CFGAPIDR                                       0x000000FCU

//Sub-Domain PREC Register
#define SOC_DEBUGSS_O_PWRAPDP0                                       0x00000100U

//Sub-Domain PREC Register
#define SOC_DEBUGSS_O_PWRAPDP1                                       0x00000104U

//Sub-Domain PREC Register
#define SOC_DEBUGSS_O_PWRAPDP2                                       0x00000108U

//Sub-Domain PREC Register
#define SOC_DEBUGSS_O_PWRAPDP3                                       0x0000010CU

//PWEAP Identification Register
#define SOC_DEBUGSS_O_PWRAPIDR                                       0x000001FCU

//Transmit Data Register
#define SOC_DEBUGSS_O_SECAPTXD                                       0x00000200U

//Transmit Control Register
#define SOC_DEBUGSS_O_SECAPTXCTL                                     0x00000204U

//Receive Data Register
#define SOC_DEBUGSS_O_SECAPRXD                                       0x00000208U

//Receive Control Register
#define SOC_DEBUGSS_O_RXCTL                                          0x0000020CU

//AP Identification Register
#define SOC_DEBUGSS_O_SECAPIDR                                       0x000002FCU

//ETAP Register Selector
#define SOC_DEBUGSS_O_ETAPSEL                                        0x00000300U

//ETAP Capability Control
#define SOC_DEBUGSS_O_ETAPCAPCTL                                     0x00000304U

//ETAP Status Read
#define SOC_DEBUGSS_O_ETAPSTARD                                      0x00000308U

//ETAP Domain Control
#define SOC_DEBUGSS_O_ETAPDMNCTL                                     0x0000030CU

//ETAP Identification Register
#define SOC_DEBUGSS_O_ETAPIDR                                        0x000003FCU



/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGAPDEVID
    Offset name:         SOC_DEBUGSS_O_CFGAPDEVID
    Relative address:    0x0
    Description:         CFGAP Device ID.

                        The device identification register allows the manufacturer, part number, and version of a component to be determined. This is the same 32-bit value obtained via the IDCODE instruction in the optional ICEPickM Scan module and is determined by tie-offs at DebugSS boundary.
    Default Value:       0x0000002F

        Field:           ALWAYSONE
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-only
        Description:     The value 1 in bit 0 of a JTAG IDCODE means that a 32-bit scan register exists. This is replicated here for completeness.

*/
#define SOC_DEBUGSS_CFGAPDEVID_ALWAYSONE                             0x00000001U
#define SOC_DEBUGSS_CFGAPDEVID_ALWAYSONE_M                           0x00000001U
#define SOC_DEBUGSS_CFGAPDEVID_ALWAYSONE_S                           0U
/*

        Field:           MAN
        From..to bits:   1...11
        DefaultValue:    0x17
        Access type:     read-only
        Description:     TI's JEDEC bank and company code, which is 00000010111b

*/
#define SOC_DEBUGSS_CFGAPDEVID_MAN_W                                 11U
#define SOC_DEBUGSS_CFGAPDEVID_MAN_M                                 0x00000FFEU
#define SOC_DEBUGSS_CFGAPDEVID_MAN_S                                 1U
/*

        Field:           PARTNUM
        From..to bits:   12...27
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Identifies the part

*/
#define SOC_DEBUGSS_CFGAPDEVID_PARTNUM_W                             16U
#define SOC_DEBUGSS_CFGAPDEVID_PARTNUM_M                             0x0FFFF000U
#define SOC_DEBUGSS_CFGAPDEVID_PARTNUM_S                             12U
/*

        Field:           VER
        From..to bits:   28...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Revision of the device. This field should change each time that the logic or mask set of the device is revised.

*/
#define SOC_DEBUGSS_CFGAPDEVID_VER_W                                 4U
#define SOC_DEBUGSS_CFGAPDEVID_VER_M                                 0xF0000000U
#define SOC_DEBUGSS_CFGAPDEVID_VER_S                                 28U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGAPDEVUC
    Offset name:         SOC_DEBUGSS_O_CFGAPDEVUC
    Relative address:    0x4
    Description:         CFGAP Device User Code.

                        The Device Usercode register is used in conjunction with the Device Identification Register to provide extended device information. This is the same 32-bit value obtained via the USERCODE instruction in the optional ICEPickM Scan module and is determined by tie-offs at DebugSS boundary.
    Default Value:       0x00000000

        Field:           USERCODE
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The Device Usercode register is used in conjunction with the Device Identification Register to provide extended device information. This is the same 32-bit value obtained via the USERCODE instruction in the optional ICEPickM Scan module and is determined by tie-offs at DebugSS boundary.

*/
#define SOC_DEBUGSS_CFGAPDEVUC_USERCODE_W                            32U
#define SOC_DEBUGSS_CFGAPDEVUC_USERCODE_M                            0xFFFFFFFFU
#define SOC_DEBUGSS_CFGAPDEVUC_USERCODE_S                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGSSVER
    Offset name:         SOC_DEBUGSS_O_DBGSSVER
    Relative address:    0x8
    Description:         CFGAP DEBUGSS Version.

                        The DebugSS Configuration Register provides information on the configuration of this particular instance of the subsystem.
    Default Value:       0x40000098

        Field:           TRACE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     A value of '1' indicates this subsystem instance contains a Trace submodule

*/
#define SOC_DEBUGSS_DBGSSVER_TRACE                                   0x00000001U
#define SOC_DEBUGSS_DBGSSVER_TRACE_M                                 0x00000001U
#define SOC_DEBUGSS_DBGSSVER_TRACE_S                                 0U
/*

        Field:           TRIG
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     A value of '1' indicates this subsystem instance contains Cross Trigger submodule

*/
#define SOC_DEBUGSS_DBGSSVER_TRIG                                    0x00000002U
#define SOC_DEBUGSS_DBGSSVER_TRIG_M                                  0x00000002U
#define SOC_DEBUGSS_DBGSSVER_TRIG_S                                  1U
/*

        Field:           ICEPICKM
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     A value of '1' indicates this subsystem instance contains an ICEPickM Scan module for extended scan support

*/
#define SOC_DEBUGSS_DBGSSVER_ICEPICKM                                0x00000004U
#define SOC_DEBUGSS_DBGSSVER_ICEPICKM_M                              0x00000004U
#define SOC_DEBUGSS_DBGSSVER_ICEPICKM_S                              2U
/*

        Field:           ETAP
        From..to bits:   3...3
        DefaultValue:    0x1
        Access type:     read-only
        Description:     A value of '1' indicates this subsystem instance contains an EnergyTrace AP

*/
#define SOC_DEBUGSS_DBGSSVER_ETAP                                    0x00000008U
#define SOC_DEBUGSS_DBGSSVER_ETAP_M                                  0x00000008U
#define SOC_DEBUGSS_DBGSSVER_ETAP_S                                  3U
/*

        Field:           SECAP
        From..to bits:   4...4
        DefaultValue:    0x1
        Access type:     read-only
        Description:     A value of '1' indicates this subsystem instance contains a Secure AP

*/
#define SOC_DEBUGSS_DBGSSVER_SECAP                                   0x00000010U
#define SOC_DEBUGSS_DBGSSVER_SECAP_M                                 0x00000010U
#define SOC_DEBUGSS_DBGSSVER_SECAP_S                                 4U
/*

        Field:           APBAP
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     A value of '1' indicates this subsystem instance contains an ABP-AP for accessing system level debug components

*/
#define SOC_DEBUGSS_DBGSSVER_APBAP                                   0x00000020U
#define SOC_DEBUGSS_DBGSSVER_APBAP_M                                 0x00000020U
#define SOC_DEBUGSS_DBGSSVER_APBAP_S                                 5U
/*

        Field:           SYSTEMAP
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     A value of '1' indicates this subsystem instance contains an AHB-AP module for system bus mastering

*/
#define SOC_DEBUGSS_DBGSSVER_SYSTEMAP                                0x00000040U
#define SOC_DEBUGSS_DBGSSVER_SYSTEMAP_M                              0x00000040U
#define SOC_DEBUGSS_DBGSSVER_SYSTEMAP_S                              6U
/*

        Field:           PWRAP
        From..to bits:   7...7
        DefaultValue:    0x1
        Access type:     read-only
        Description:     A value of '1' indicates this subsystem instance contains a Power-AP module

*/
#define SOC_DEBUGSS_DBGSSVER_PWRAP                                   0x00000080U
#define SOC_DEBUGSS_DBGSSVER_PWRAP_M                                 0x00000080U
#define SOC_DEBUGSS_DBGSSVER_PWRAP_S                                 7U
/*

        Field:           REVMIN
        From..to bits:   24...27
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indicates the minor revision of this Subsystem instance. Currently 0000b

*/
#define SOC_DEBUGSS_DBGSSVER_REVMIN_W                                4U
#define SOC_DEBUGSS_DBGSSVER_REVMIN_M                                0x0F000000U
#define SOC_DEBUGSS_DBGSSVER_REVMIN_S                                24U
/*

        Field:           REVMAJ
        From..to bits:   28...31
        DefaultValue:    0x4
        Access type:     read-only
        Description:     Indicates the major revision of this Subsystem instance.

*/
#define SOC_DEBUGSS_DBGSSVER_REVMAJ_W                                4U
#define SOC_DEBUGSS_DBGSSVER_REVMAJ_M                                0xF0000000U
#define SOC_DEBUGSS_DBGSSVER_REVMAJ_S                                28U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGAPBOOT
    Offset name:         SOC_DEBUGSS_O_CFGAPBOOT
    Relative address:    0x10
    Description:         CFGAP Boot Diag.

                        This register provides feedback on the boot process
    Default Value:       0x00000000

        Field:           DIAGVAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This register provides feedback on the boot process
                         [3:0]     PG_Version
                         [5:3]     Metal_Version
                         [8:6]     Memory Stacking
                         [11:9]   Package type
                         [13:12] Temperature
                         [17:14] Device PartNumber
                         [18]      Disable 5GHz
                         [19]      Disable 6GHz
                         [20]      Disable BLE
                         [21]      Disable BLE M0+
                         [22]      Disable CAN FD
                         [25:23] Boot ROM Version (FMU)
                         [26]       Launch pad Mode
                         [28:27]  SDIO Product ID
                         [31:29]  TI Fuse ROM Structure Version

*/
#define SOC_DEBUGSS_CFGAPBOOT_DIAGVAL_W                              32U
#define SOC_DEBUGSS_CFGAPBOOT_DIAGVAL_M                              0xFFFFFFFFU
#define SOC_DEBUGSS_CFGAPBOOT_DIAGVAL_S                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGAPLCST
    Offset name:         SOC_DEBUGSS_O_CFGAPLCST
    Relative address:    0x14
    Description:         CFGAP Life-cycle.

                        Indicates the current device lifecycle state
    Default Value:       0x00000000

        Field:           LCSVAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Life cycle state

                         [3:0]     PG_Version
                         [5:3]     Metal_Version
                         [8:6]     Memory Stacking
                         [11:9]   Package type
                         [13:12] Temperature
                         [17:14] Device PartNumber
                         [18]      Disable 5GHz
                         [19]      Disable 6GHz
                         [20]      Disable BLE
                         [21]      Disable BLE M0+
                         [22]      Disable CAN FD
                         [25:23] Boot ROM Version (FMU)
                         [26]       Launch pad Mode
                         [28:27]  SDIO Product ID
                         [31:29]  TI Fuse ROM Structure Version

*/
#define SOC_DEBUGSS_CFGAPLCST_LCSVAL_W                               32U
#define SOC_DEBUGSS_CFGAPLCST_LCSVAL_M                               0xFFFFFFFFU
#define SOC_DEBUGSS_CFGAPLCST_LCSVAL_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DFTEN
    Offset name:         SOC_DEBUGSS_O_DFTEN
    Relative address:    0x18
    Description:         DFT Enable.

                        This bit can be configured to enable multiplexing of JTAG signals on device pins.
    Default Value:       NA

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     This bit can be configured to enable multiplexing of JTAG signals on device pins. Pin #2 --> TCK ;Pin #3 --> TMS ; Pin #10 --> TDI ; Pin #15 --> TDO. Refer to pinout_iomux.xls for more information.

*/
#define SOC_DEBUGSS_DFTEN_EN                                         0x00000001U
#define SOC_DEBUGSS_DFTEN_EN_M                                       0x00000001U
#define SOC_DEBUGSS_DFTEN_EN_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RSTREQ
    Offset name:         SOC_DEBUGSS_O_RSTREQ
    Relative address:    0x1C
    Description:         Reset Request.

                        This bit can be configured to request reset.
    Default Value:       NA

        Field:           REQ
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit can be configured to request device reset

*/
#define SOC_DEBUGSS_RSTREQ_REQ                                       0x00000001U
#define SOC_DEBUGSS_RSTREQ_REQ_M                                     0x00000001U
#define SOC_DEBUGSS_RSTREQ_REQ_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGAPUDID0
    Offset name:         SOC_DEBUGSS_O_CFGAPUDID0
    Relative address:    0x28
    Description:         CFGAP Unique Device 0.

                        Used to provide a unique device ID/token for security authentication of
                        tester and tools.
                        Unique device ID is 64bit value and this register reads lower 32 bits.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Used to provide a unique divide ID/token for security authentication of
                         tester and tools

*/
#define SOC_DEBUGSS_CFGAPUDID0_VAL_W                                 32U
#define SOC_DEBUGSS_CFGAPUDID0_VAL_M                                 0xFFFFFFFFU
#define SOC_DEBUGSS_CFGAPUDID0_VAL_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGAPUDID1
    Offset name:         SOC_DEBUGSS_O_CFGAPUDID1
    Relative address:    0x2C
    Description:         CFGAP Unique Device 1.

                        Used to provide a unique device ID/token for security authentication of
                        tester and tools.
                        Unique device ID is 64bit value and this register reads upper 32 bits.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Used to provide a unique devide ID/token for security authentication of
                         tester and tools

*/
#define SOC_DEBUGSS_CFGAPUDID1_VAL_W                                 32U
#define SOC_DEBUGSS_CFGAPUDID1_VAL_M                                 0xFFFFFFFFU
#define SOC_DEBUGSS_CFGAPUDID1_VAL_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGAPIDR
    Offset name:         SOC_DEBUGSS_O_CFGAPIDR
    Relative address:    0xFC
    Description:         CFGAP Identification Register.

                        AP Identification Register.  The AP identification register allows tools to determine the manufacturer and the type of AP.
    Default Value:       0x102E0001

        Field:           APTYPE
        From..to bits:   0...3
        DefaultValue:    0x1
        Access type:     read-only
        Description:     The AP Type Register.  TI Subsystem Config APs have a type of 0001b

*/
#define SOC_DEBUGSS_CFGAPIDR_APTYPE_W                                4U
#define SOC_DEBUGSS_CFGAPIDR_APTYPE_M                                0x0000000FU
#define SOC_DEBUGSS_CFGAPIDR_APTYPE_S                                0U
/*

        Field:           APVAR
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AP Variant.  There is only one variant for this AP Type and it is 0.

*/
#define SOC_DEBUGSS_CFGAPIDR_APVAR_W                                 4U
#define SOC_DEBUGSS_CFGAPIDR_APVAR_M                                 0x000000F0U
#define SOC_DEBUGSS_CFGAPIDR_APVAR_S                                 4U
/*

        Field:           APCLASS
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AP Class.  0 indicates that this AP is not a bridge to a memory interconnect (not a Memory Access Port).

*/
#define SOC_DEBUGSS_CFGAPIDR_APCLASS                                 0x00010000U
#define SOC_DEBUGSS_CFGAPIDR_APCLASS_M                               0x00010000U
#define SOC_DEBUGSS_CFGAPIDR_APCLASS_S                               16U
/*

        Field:           JEPIDS
        From..to bits:   17...27
        DefaultValue:    0x17
        Access type:     read-only
        Description:     Manufacturer JEP106 ID.  The concatenated JEP106 ID and continuation ID for TI. This is 00000010111b.

*/
#define SOC_DEBUGSS_CFGAPIDR_JEPIDS_W                                11U
#define SOC_DEBUGSS_CFGAPIDR_JEPIDS_M                                0x0FFE0000U
#define SOC_DEBUGSS_CFGAPIDR_JEPIDS_S                                17U
/*

        Field:           REV
        From..to bits:   28...31
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Component Revision.  Indicates the revision of this AP instance. Currently 0001b

*/
#define SOC_DEBUGSS_CFGAPIDR_REV_W                                   4U
#define SOC_DEBUGSS_CFGAPIDR_REV_M                                   0xF0000000U
#define SOC_DEBUGSS_CFGAPIDR_REV_S                                   28U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PWRAPDP0
    Offset name:         SOC_DEBUGSS_O_PWRAPDP0
    Relative address:    0x100
    Description:         Sub-Domain PREC Register
                        This register provides an interface for debug tooling to obtain status and override the power, reset and execution state of debug targets in dynamically controlled sub-domains.
    Default Value:       0x00000000

        Field:           COREPRES
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     1 indicates that WSOC MCU is present in this Osprey device.

*/
#define SOC_DEBUGSS_PWRAPDP0_COREPRES                                0x00000001U
#define SOC_DEBUGSS_PWRAPDP0_COREPRES_M                              0x00000001U
#define SOC_DEBUGSS_PWRAPDP0_COREPRES_S                              0U
/*

        Field:           CORESACC
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from DSSM. Indicate that WSOC MCU Power-AP overrides are writable.

*/
#define SOC_DEBUGSS_PWRAPDP0_CORESACC                                0x00000002U
#define SOC_DEBUGSS_PWRAPDP0_CORESACC_M                              0x00000002U
#define SOC_DEBUGSS_PWRAPDP0_CORESACC_S                              1U
/*

        Field:           CLKSTATE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from CPU-SS. "1" indicated that WSOC MCU is clocked by it's functional clock.

*/
#define SOC_DEBUGSS_PWRAPDP0_CLKSTATE                                0x00000004U
#define SOC_DEBUGSS_PWRAPDP0_CLKSTATE_M                              0x00000004U
#define SOC_DEBUGSS_PWRAPDP0_CLKSTATE_S                              2U
/*

        Field:           FORCEACT
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Provides debug override of the default state of the CORE P.D power and clock.

*/
#define SOC_DEBUGSS_PWRAPDP0_FORCEACT                                0x00000008U
#define SOC_DEBUGSS_PWRAPDP0_FORCEACT_M                              0x00000008U
#define SOC_DEBUGSS_PWRAPDP0_FORCEACT_S                              3U
/*

        Field:           CLKDWNDES
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     "1" indicated that WSOC MCU is clocked artificially.

*/
#define SOC_DEBUGSS_PWRAPDP0_CLKDWNDES                               0x00000010U
#define SOC_DEBUGSS_PWRAPDP0_CLKDWNDES_M                             0x00000010U
#define SOC_DEBUGSS_PWRAPDP0_CLKDWNDES_S                             4U
/*

        Field:           PWR
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from PRCM. "1" indicates CORE domain is powered.

*/
#define SOC_DEBUGSS_PWRAPDP0_PWR                                     0x00000020U
#define SOC_DEBUGSS_PWRAPDP0_PWR_M                                   0x00000020U
#define SOC_DEBUGSS_PWRAPDP0_PWR_S                                   5U
/*

        Field:           PWRDWNDES
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from ELP. Indicates that CORE domain can be shutdown.

*/
#define SOC_DEBUGSS_PWRAPDP0_PWRDWNDES                               0x00000080U
#define SOC_DEBUGSS_PWRAPDP0_PWRDWNDES_M                             0x00000080U
#define SOC_DEBUGSS_PWRAPDP0_PWRDWNDES_S                             7U
/*

        Field:           DBGATT
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from CPU-SS. "1" indicate that WSOC MCU is halted and in debug mode.

*/
#define SOC_DEBUGSS_PWRAPDP0_DBGATT                                  0x00000400U
#define SOC_DEBUGSS_PWRAPDP0_DBGATT_M                                0x00000400U
#define SOC_DEBUGSS_PWRAPDP0_DBGATT_S                                10U
/*

        Field:           DBGMOD
        From..to bits:   11...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used to define debug properties. Not used in MX.

*/
#define SOC_DEBUGSS_PWRAPDP0_DBGMOD_W                                2U
#define SOC_DEBUGSS_PWRAPDP0_DBGMOD_M                                0x00001800U
#define SOC_DEBUGSS_PWRAPDP0_DBGMOD_S                                11U
/*

        Field:           DBGEN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Defines operating mode of debug logic in Cortex. Not used in MX.

*/
#define SOC_DEBUGSS_PWRAPDP0_DBGEN                                   0x00002000U
#define SOC_DEBUGSS_PWRAPDP0_DBGEN_M                                 0x00002000U
#define SOC_DEBUGSS_PWRAPDP0_DBGEN_S                                 13U
/*

        Field:           RSTCTL
        From..to bits:   14...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Following are the field values with their description.
                         000 -> Normal Operation;
                         001 -> Wait in Reset (Reset Ext);
                         010 -> Block Reset;
                         100- > Reset Req.

*/
#define SOC_DEBUGSS_PWRAPDP0_RSTCTL_W                                3U
#define SOC_DEBUGSS_PWRAPDP0_RSTCTL_M                                0x0001C000U
#define SOC_DEBUGSS_PWRAPDP0_RSTCTL_S                                14U
/*

        Field:           IRSTRELWIR
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Input from PRCM. "1" indicates WSOC MCU is in reset. Setting this bit shall release the extended SYSRSTn to WSOc MCU.

*/
#define SOC_DEBUGSS_PWRAPDP0_IRSTRELWIR                              0x00020000U
#define SOC_DEBUGSS_PWRAPDP0_IRSTRELWIR_M                            0x00020000U
#define SOC_DEBUGSS_PWRAPDP0_IRSTRELWIR_S                            17U
/*

        Field:           UNNATRST
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     input from PRCM. "1" indicate that WSOC MCU (SYSRSTn) reset is extended.

*/
#define SOC_DEBUGSS_PWRAPDP0_UNNATRST                                0x00040000U
#define SOC_DEBUGSS_PWRAPDP0_UNNATRST_M                              0x00040000U
#define SOC_DEBUGSS_PWRAPDP0_UNNATRST_S                              18U
/*

        Field:           DBGPWR
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Used to indicate power state of debug logic in the associated domain. 0 -> Debug logic is off. 1 -> Debug logic is powered.

*/
#define SOC_DEBUGSS_PWRAPDP0_DBGPWR                                  0x00080000U
#define SOC_DEBUGSS_PWRAPDP0_DBGPWR_M                                0x00080000U
#define SOC_DEBUGSS_PWRAPDP0_DBGPWR_S                                19U
/*

        Field:           PWRLOSS
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Input from PRCM. Used by debug tools. A sticky bit Indicate that a power loss to CORE has happened since last time tools checked. Cleared on write by the tool.

*/
#define SOC_DEBUGSS_PWRAPDP0_PWRLOSS                                 0x00200000U
#define SOC_DEBUGSS_PWRAPDP0_PWRLOSS_M                               0x00200000U
#define SOC_DEBUGSS_PWRAPDP0_PWRLOSS_S                               21U
/*

        Field:           RSTOCC
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Input from CPU-SS. Used by debug tools. A sticky bit Indicate that a reset to WSOC MCU has happened since last time tools checked. Cleared on write  by the tool.

*/
#define SOC_DEBUGSS_PWRAPDP0_RSTOCC                                  0x00400000U
#define SOC_DEBUGSS_PWRAPDP0_RSTOCC_M                                0x00400000U
#define SOC_DEBUGSS_PWRAPDP0_RSTOCC_S                                22U
/*

        Field:           RETENTION
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Used to indicate that the domain entered retention since the bit is cleared. Not supported in MX.

*/
#define SOC_DEBUGSS_PWRAPDP0_RETENTION                               0x00800000U
#define SOC_DEBUGSS_PWRAPDP0_RETENTION_M                             0x00800000U
#define SOC_DEBUGSS_PWRAPDP0_RETENTION_S                             23U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PWRAPDP1
    Offset name:         SOC_DEBUGSS_O_PWRAPDP1
    Relative address:    0x104
    Description:         Sub-Domain PREC Register
                        This register provides an interface for debug tooling to obtain status and override the power, reset and execution state of debug targets in dynamically controlled sub-domains.
    Default Value:       0x00000000

        Field:           COREPRES
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     1 indicates that WPHY MCU is present in this Osprey device.

*/
#define SOC_DEBUGSS_PWRAPDP1_COREPRES                                0x00000001U
#define SOC_DEBUGSS_PWRAPDP1_COREPRES_M                              0x00000001U
#define SOC_DEBUGSS_PWRAPDP1_COREPRES_S                              0U
/*

        Field:           CORESACC
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from DSSM. Indicate that WSOC MCU, WPHY and LRF MCU (CORE domain cores) Power-AP overrides are writable.

*/
#define SOC_DEBUGSS_PWRAPDP1_CORESACC                                0x00000002U
#define SOC_DEBUGSS_PWRAPDP1_CORESACC_M                              0x00000002U
#define SOC_DEBUGSS_PWRAPDP1_CORESACC_S                              1U
/*

        Field:           CLKSTATE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from CPU-SS. "1" indicated that WPHY MCU is clocked by it's functional clock.

*/
#define SOC_DEBUGSS_PWRAPDP1_CLKSTATE                                0x00000004U
#define SOC_DEBUGSS_PWRAPDP1_CLKSTATE_M                              0x00000004U
#define SOC_DEBUGSS_PWRAPDP1_CLKSTATE_S                              2U
/*

        Field:           FORCEACT
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Provides debug override of the default state of the CORE P.D power and clock.

*/
#define SOC_DEBUGSS_PWRAPDP1_FORCEACT                                0x00000008U
#define SOC_DEBUGSS_PWRAPDP1_FORCEACT_M                              0x00000008U
#define SOC_DEBUGSS_PWRAPDP1_FORCEACT_S                              3U
/*

        Field:           CLKDWNDES
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from ?. "1" indicated that WPHY MCU is clocked artificially.

*/
#define SOC_DEBUGSS_PWRAPDP1_CLKDWNDES                               0x00000010U
#define SOC_DEBUGSS_PWRAPDP1_CLKDWNDES_M                             0x00000010U
#define SOC_DEBUGSS_PWRAPDP1_CLKDWNDES_S                             4U
/*

        Field:           PWR
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from PRCM. "1" indicates CORE domain is powered.

*/
#define SOC_DEBUGSS_PWRAPDP1_PWR                                     0x00000020U
#define SOC_DEBUGSS_PWRAPDP1_PWR_M                                   0x00000020U
#define SOC_DEBUGSS_PWRAPDP1_PWR_S                                   5U
/*

        Field:           PWRDWNDES
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from ELP. Indicates that CORE domain can be shutdown.

*/
#define SOC_DEBUGSS_PWRAPDP1_PWRDWNDES                               0x00000080U
#define SOC_DEBUGSS_PWRAPDP1_PWRDWNDES_M                             0x00000080U
#define SOC_DEBUGSS_PWRAPDP1_PWRDWNDES_S                             7U
/*

        Field:           DBGATT
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from CPU-SS. "1" indicate that WPHY MCU is halted and in debug mode.

*/
#define SOC_DEBUGSS_PWRAPDP1_DBGATT                                  0x00000400U
#define SOC_DEBUGSS_PWRAPDP1_DBGATT_M                                0x00000400U
#define SOC_DEBUGSS_PWRAPDP1_DBGATT_S                                10U
/*

        Field:           DBGMOD
        From..to bits:   11...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used to define debug properties. Not used in MX.

*/
#define SOC_DEBUGSS_PWRAPDP1_DBGMOD_W                                2U
#define SOC_DEBUGSS_PWRAPDP1_DBGMOD_M                                0x00001800U
#define SOC_DEBUGSS_PWRAPDP1_DBGMOD_S                                11U
/*

        Field:           DBGEN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Defines operating mode of debug logic in Cortex. Not used in MX.

*/
#define SOC_DEBUGSS_PWRAPDP1_DBGEN                                   0x00002000U
#define SOC_DEBUGSS_PWRAPDP1_DBGEN_M                                 0x00002000U
#define SOC_DEBUGSS_PWRAPDP1_DBGEN_S                                 13U
/*

        Field:           RSTCTL
        From..to bits:   14...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Following are the field values with their description.
                         000 -> Normal Operation;
                         001 -> Wait in Reset (Reset Ext);
                         010 -> Block Reset;
                         100- > Reset Req.

*/
#define SOC_DEBUGSS_PWRAPDP1_RSTCTL_W                                3U
#define SOC_DEBUGSS_PWRAPDP1_RSTCTL_M                                0x0001C000U
#define SOC_DEBUGSS_PWRAPDP1_RSTCTL_S                                14U
/*

        Field:           INRST
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from PRCM. "1" indicates WPHY MCU is in reset.

*/
#define SOC_DEBUGSS_PWRAPDP1_INRST                                   0x00020000U
#define SOC_DEBUGSS_PWRAPDP1_INRST_M                                 0x00020000U
#define SOC_DEBUGSS_PWRAPDP1_INRST_S                                 17U
/*

        Field:           DBGPWR
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Used to indicate power state of debug logic in the associated domain. 0 -> Debug logic is off. 1 -> Debug logic is powered.

*/
#define SOC_DEBUGSS_PWRAPDP1_DBGPWR                                  0x00080000U
#define SOC_DEBUGSS_PWRAPDP1_DBGPWR_M                                0x00080000U
#define SOC_DEBUGSS_PWRAPDP1_DBGPWR_S                                19U
/*

        Field:           PWRLOSS
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Input from PRCM. Used by debug tools. A sticky bit Indicate that a power loss to CORE has happened since last time tools checked. Cleared on write by the tool.

*/
#define SOC_DEBUGSS_PWRAPDP1_PWRLOSS                                 0x00200000U
#define SOC_DEBUGSS_PWRAPDP1_PWRLOSS_M                               0x00200000U
#define SOC_DEBUGSS_PWRAPDP1_PWRLOSS_S                               21U
/*

        Field:           RSTOCC
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Input from CPU-SS. Used by debug tools. A sticky bit Indicate that a reset to WPHY MCU has happened since last time tools checked. Cleared on write  by the tool.

*/
#define SOC_DEBUGSS_PWRAPDP1_RSTOCC                                  0x00400000U
#define SOC_DEBUGSS_PWRAPDP1_RSTOCC_M                                0x00400000U
#define SOC_DEBUGSS_PWRAPDP1_RSTOCC_S                                22U
/*

        Field:           RETENTION
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Used to indicate that the domain entered retention since the bit is cleared. Not supported in MX.

*/
#define SOC_DEBUGSS_PWRAPDP1_RETENTION                               0x00800000U
#define SOC_DEBUGSS_PWRAPDP1_RETENTION_M                             0x00800000U
#define SOC_DEBUGSS_PWRAPDP1_RETENTION_S                             23U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PWRAPDP2
    Offset name:         SOC_DEBUGSS_O_PWRAPDP2
    Relative address:    0x108
    Description:         Sub-Domain PREC Register
                        This register provides an interface for debug tooling to obtain status and override the power, reset and execution state of debug targets in dynamically controlled sub-domains.
    Default Value:       0x00000000

        Field:           COREPRES
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     1 indicates that LRF MCU is present in this Osprey device.

*/
#define SOC_DEBUGSS_PWRAPDP2_COREPRES                                0x00000001U
#define SOC_DEBUGSS_PWRAPDP2_COREPRES_M                              0x00000001U
#define SOC_DEBUGSS_PWRAPDP2_COREPRES_S                              0U
/*

        Field:           CORESACC
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from DSSM. Indicate that WSOC MCU, WPHY and LRF MCU (CORE domain cores) Power-AP overrides are writable.

*/
#define SOC_DEBUGSS_PWRAPDP2_CORESACC                                0x00000002U
#define SOC_DEBUGSS_PWRAPDP2_CORESACC_M                              0x00000002U
#define SOC_DEBUGSS_PWRAPDP2_CORESACC_S                              1U
/*

        Field:           CLKSTATE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from CPU-SS. "1" indicated that LRF MCU is clocked by it's functional clock.

*/
#define SOC_DEBUGSS_PWRAPDP2_CLKSTATE                                0x00000004U
#define SOC_DEBUGSS_PWRAPDP2_CLKSTATE_M                              0x00000004U
#define SOC_DEBUGSS_PWRAPDP2_CLKSTATE_S                              2U
/*

        Field:           FORCEACT
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Provides debug override of the default state of the CORE P.D power and clock.

*/
#define SOC_DEBUGSS_PWRAPDP2_FORCEACT                                0x00000008U
#define SOC_DEBUGSS_PWRAPDP2_FORCEACT_M                              0x00000008U
#define SOC_DEBUGSS_PWRAPDP2_FORCEACT_S                              3U
/*

        Field:           CLKDWNDES
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from ?. "1" indicated that LRF MCU is clocked artificially.

*/
#define SOC_DEBUGSS_PWRAPDP2_CLKDWNDES                               0x00000010U
#define SOC_DEBUGSS_PWRAPDP2_CLKDWNDES_M                             0x00000010U
#define SOC_DEBUGSS_PWRAPDP2_CLKDWNDES_S                             4U
/*

        Field:           PWR
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from PRCM. "1" indicates CORE domain is powered.

*/
#define SOC_DEBUGSS_PWRAPDP2_PWR                                     0x00000020U
#define SOC_DEBUGSS_PWRAPDP2_PWR_M                                   0x00000020U
#define SOC_DEBUGSS_PWRAPDP2_PWR_S                                   5U
/*

        Field:           PWRDWNDES
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from ELP. Indicates that CORE domain can be shutdown.

*/
#define SOC_DEBUGSS_PWRAPDP2_PWRDWNDES                               0x00000080U
#define SOC_DEBUGSS_PWRAPDP2_PWRDWNDES_M                             0x00000080U
#define SOC_DEBUGSS_PWRAPDP2_PWRDWNDES_S                             7U
/*

        Field:           DBGATT
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from CPU-SS. "1" indicate that LRF MCU is halted and in debug mode.

*/
#define SOC_DEBUGSS_PWRAPDP2_DBGATT                                  0x00000400U
#define SOC_DEBUGSS_PWRAPDP2_DBGATT_M                                0x00000400U
#define SOC_DEBUGSS_PWRAPDP2_DBGATT_S                                10U
/*

        Field:           DBGMOD
        From..to bits:   11...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used to define debug properties. Not used in MX.

*/
#define SOC_DEBUGSS_PWRAPDP2_DBGMOD_W                                2U
#define SOC_DEBUGSS_PWRAPDP2_DBGMOD_M                                0x00001800U
#define SOC_DEBUGSS_PWRAPDP2_DBGMOD_S                                11U
/*

        Field:           DBGEN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Defines operating mode of debug logic in Cortex. Not used in MX.

*/
#define SOC_DEBUGSS_PWRAPDP2_DBGEN                                   0x00002000U
#define SOC_DEBUGSS_PWRAPDP2_DBGEN_M                                 0x00002000U
#define SOC_DEBUGSS_PWRAPDP2_DBGEN_S                                 13U
/*

        Field:           RSTCTL
        From..to bits:   14...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Following are the field values with their description.
                         000 -> Normal Operation;
                         001 -> Wait in Reset (Reset Ext);
                         010 -> Block Reset;
                         100- > Reset Req.

*/
#define SOC_DEBUGSS_PWRAPDP2_RSTCTL_W                                3U
#define SOC_DEBUGSS_PWRAPDP2_RSTCTL_M                                0x0001C000U
#define SOC_DEBUGSS_PWRAPDP2_RSTCTL_S                                14U
/*

        Field:           INRST
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from PRCM. "1" indicates LRF MCU is in reset.

*/
#define SOC_DEBUGSS_PWRAPDP2_INRST                                   0x00020000U
#define SOC_DEBUGSS_PWRAPDP2_INRST_M                                 0x00020000U
#define SOC_DEBUGSS_PWRAPDP2_INRST_S                                 17U
/*

        Field:           DBGPWR
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Used to indicate power state of debug logic in the associated domain. 0 -> Debug logic is off. 1 -> Debug logic is powered.

*/
#define SOC_DEBUGSS_PWRAPDP2_DBGPWR                                  0x00080000U
#define SOC_DEBUGSS_PWRAPDP2_DBGPWR_M                                0x00080000U
#define SOC_DEBUGSS_PWRAPDP2_DBGPWR_S                                19U
/*

        Field:           PWRLOSS
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Input from PRCM. Used by debug tools. A sticky bit Indicate that a power loss to CORE has happened since last time tools checked. Cleared on write by the tool.

*/
#define SOC_DEBUGSS_PWRAPDP2_PWRLOSS                                 0x00200000U
#define SOC_DEBUGSS_PWRAPDP2_PWRLOSS_M                               0x00200000U
#define SOC_DEBUGSS_PWRAPDP2_PWRLOSS_S                               21U
/*

        Field:           RSTOCC
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Input from CPU-SS. Used by debug tools. A sticky bit Indicate that a reset to LRF MCU has happened since last time tools checked. Cleared on write  by the tool.

*/
#define SOC_DEBUGSS_PWRAPDP2_RSTOCC                                  0x00400000U
#define SOC_DEBUGSS_PWRAPDP2_RSTOCC_M                                0x00400000U
#define SOC_DEBUGSS_PWRAPDP2_RSTOCC_S                                22U
/*

        Field:           RETN
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Used to indicate that the domain entered retention since the bit is cleared. Not supported in MX.

*/
#define SOC_DEBUGSS_PWRAPDP2_RETN                                    0x00800000U
#define SOC_DEBUGSS_PWRAPDP2_RETN_M                                  0x00800000U
#define SOC_DEBUGSS_PWRAPDP2_RETN_S                                  23U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PWRAPDP3
    Offset name:         SOC_DEBUGSS_O_PWRAPDP3
    Relative address:    0x10C
    Description:         Sub-Domain PREC Register
                        This register provides an interface for debug tooling to obtain status and override the power, reset and execution state of debug targets in dynamically controlled sub-domains.
    Default Value:       0x00000000

        Field:           COREPRES
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     1 indicates that APP MCU is present in this Osprey device.

*/
#define SOC_DEBUGSS_PWRAPDP3_COREPRES                                0x00000001U
#define SOC_DEBUGSS_PWRAPDP3_COREPRES_M                              0x00000001U
#define SOC_DEBUGSS_PWRAPDP3_COREPRES_S                              0U
/*

        Field:           CORESACC
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from DSSM. Indicate that HOST Power-AP overrides are writable.

*/
#define SOC_DEBUGSS_PWRAPDP3_CORESACC                                0x00000002U
#define SOC_DEBUGSS_PWRAPDP3_CORESACC_M                              0x00000002U
#define SOC_DEBUGSS_PWRAPDP3_CORESACC_S                              1U
/*

        Field:           CLKSTATE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from CPU-SS. "1" indicated that APP MCU is clocked by it's functional clock.

*/
#define SOC_DEBUGSS_PWRAPDP3_CLKSTATE                                0x00000004U
#define SOC_DEBUGSS_PWRAPDP3_CLKSTATE_M                              0x00000004U
#define SOC_DEBUGSS_PWRAPDP3_CLKSTATE_S                              2U
/*

        Field:           FORCEACT
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Provides debug override of the default state of the HOST P.D power and clock.

*/
#define SOC_DEBUGSS_PWRAPDP3_FORCEACT                                0x00000008U
#define SOC_DEBUGSS_PWRAPDP3_FORCEACT_M                              0x00000008U
#define SOC_DEBUGSS_PWRAPDP3_FORCEACT_S                              3U
/*

        Field:           CLKDWNDES
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from ?. "1" indicated that APP MCU is clocked artificially.

*/
#define SOC_DEBUGSS_PWRAPDP3_CLKDWNDES                               0x00000010U
#define SOC_DEBUGSS_PWRAPDP3_CLKDWNDES_M                             0x00000010U
#define SOC_DEBUGSS_PWRAPDP3_CLKDWNDES_S                             4U
/*

        Field:           PWR
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from PRCM. "1" indicates HOST domain is powered.

*/
#define SOC_DEBUGSS_PWRAPDP3_PWR                                     0x00000020U
#define SOC_DEBUGSS_PWRAPDP3_PWR_M                                   0x00000020U
#define SOC_DEBUGSS_PWRAPDP3_PWR_S                                   5U
/*

        Field:           PWRDWNDES
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from ?. Indicates that HOST domain can be shutdown.

*/
#define SOC_DEBUGSS_PWRAPDP3_PWRDWNDES                               0x00000080U
#define SOC_DEBUGSS_PWRAPDP3_PWRDWNDES_M                             0x00000080U
#define SOC_DEBUGSS_PWRAPDP3_PWRDWNDES_S                             7U
/*

        Field:           DBGATT
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from CPU-SS. "1" indicate that APP MCU is halted and in debug mode.

*/
#define SOC_DEBUGSS_PWRAPDP3_DBGATT                                  0x00000400U
#define SOC_DEBUGSS_PWRAPDP3_DBGATT_M                                0x00000400U
#define SOC_DEBUGSS_PWRAPDP3_DBGATT_S                                10U
/*

        Field:           DBGMOD
        From..to bits:   11...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used to define debug properties. Not used in MX.

*/
#define SOC_DEBUGSS_PWRAPDP3_DBGMOD_W                                2U
#define SOC_DEBUGSS_PWRAPDP3_DBGMOD_M                                0x00001800U
#define SOC_DEBUGSS_PWRAPDP3_DBGMOD_S                                11U
/*

        Field:           DBGEN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Defines operating mode of debug logic in Cortex. Not used in MX.

*/
#define SOC_DEBUGSS_PWRAPDP3_DBGEN                                   0x00002000U
#define SOC_DEBUGSS_PWRAPDP3_DBGEN_M                                 0x00002000U
#define SOC_DEBUGSS_PWRAPDP3_DBGEN_S                                 13U
/*

        Field:           RSTCTL
        From..to bits:   14...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Following are the field values with their description.
                         000 -> Normal Operation;
                         001 -> Wait in Reset (Reset Ext);
                         010 -> Block Reset;
                         100- > Reset Req.

*/
#define SOC_DEBUGSS_PWRAPDP3_RSTCTL_W                                3U
#define SOC_DEBUGSS_PWRAPDP3_RSTCTL_M                                0x0001C000U
#define SOC_DEBUGSS_PWRAPDP3_RSTCTL_S                                14U
/*

        Field:           IRSTRELWIR
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Input from PRCM. "1" indicates APP MCU is in reset.

*/
#define SOC_DEBUGSS_PWRAPDP3_IRSTRELWIR                              0x00020000U
#define SOC_DEBUGSS_PWRAPDP3_IRSTRELWIR_M                            0x00020000U
#define SOC_DEBUGSS_PWRAPDP3_IRSTRELWIR_S                            17U
/*

        Field:           UNNATRST
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     input from PRCM. "1" indicate that APPCPU (SYSRSTn) reset is extended.

*/
#define SOC_DEBUGSS_PWRAPDP3_UNNATRST                                0x00040000U
#define SOC_DEBUGSS_PWRAPDP3_UNNATRST_M                              0x00040000U
#define SOC_DEBUGSS_PWRAPDP3_UNNATRST_S                              18U
/*

        Field:           DBGPWR
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Used to indicate power state of debug logic in the associated domain. 0 -> Debug logic is off. 1 -> Debug logic is powered.

*/
#define SOC_DEBUGSS_PWRAPDP3_DBGPWR                                  0x00080000U
#define SOC_DEBUGSS_PWRAPDP3_DBGPWR_M                                0x00080000U
#define SOC_DEBUGSS_PWRAPDP3_DBGPWR_S                                19U
/*

        Field:           PWRLOSS
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Input from PRCM. Used by debug tools. A sticky bit Indicate that a power loss to HOST has happened since last time tools checked. Cleared on write  by the tool.

*/
#define SOC_DEBUGSS_PWRAPDP3_PWRLOSS                                 0x00200000U
#define SOC_DEBUGSS_PWRAPDP3_PWRLOSS_M                               0x00200000U
#define SOC_DEBUGSS_PWRAPDP3_PWRLOSS_S                               21U
/*

        Field:           RSTOCC
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Input from CPU-SS. Used by debug tools. A sticky bit Indicate that a reset to APP MCU has happened since last time tools checked. Cleared on write  by the tool.

*/
#define SOC_DEBUGSS_PWRAPDP3_RSTOCC                                  0x00400000U
#define SOC_DEBUGSS_PWRAPDP3_RSTOCC_M                                0x00400000U
#define SOC_DEBUGSS_PWRAPDP3_RSTOCC_S                                22U
/*

        Field:           RETENTION
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Used to indicate that the domain entered retention since the bit is cleared. Not supported in MX.

*/
#define SOC_DEBUGSS_PWRAPDP3_RETENTION                               0x00800000U
#define SOC_DEBUGSS_PWRAPDP3_RETENTION_M                             0x00800000U
#define SOC_DEBUGSS_PWRAPDP3_RETENTION_S                             23U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PWRAPIDR
    Offset name:         SOC_DEBUGSS_O_PWRAPIDR
    Relative address:    0x1FC
    Description:         PWEAP Identification Register.

                        The AP identification register allows tools to determine the manufacturer and the type of AP.
    Default Value:       0x002E0002

        Field:           APTYPE
        From..to bits:   0...3
        DefaultValue:    0x2
        Access type:     read-only
        Description:     The AP Type Register.  TI Subsystem Config APs have a type of 0001b

*/
#define SOC_DEBUGSS_PWRAPIDR_APTYPE_W                                4U
#define SOC_DEBUGSS_PWRAPIDR_APTYPE_M                                0x0000000FU
#define SOC_DEBUGSS_PWRAPIDR_APTYPE_S                                0U
/*

        Field:           APVAR
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AP Variant.  There is only one variant for this AP Type and it is 0.

*/
#define SOC_DEBUGSS_PWRAPIDR_APVAR_W                                 4U
#define SOC_DEBUGSS_PWRAPIDR_APVAR_M                                 0x000000F0U
#define SOC_DEBUGSS_PWRAPIDR_APVAR_S                                 4U
/*

        Field:           APCLASS
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AP Class.  0 indicates that this is AP is not a bridge to a memory interconnect (not a Memory Access Port).

*/
#define SOC_DEBUGSS_PWRAPIDR_APCLASS                                 0x00010000U
#define SOC_DEBUGSS_PWRAPIDR_APCLASS_M                               0x00010000U
#define SOC_DEBUGSS_PWRAPIDR_APCLASS_S                               16U
/*

        Field:           JEPIDS
        From..to bits:   17...27
        DefaultValue:    0x17
        Access type:     read-only
        Description:     Manufacturer JEP106 ID.  The concatenated JEP106 ID and continuation ID for TI. This is 00000010111b.

*/
#define SOC_DEBUGSS_PWRAPIDR_JEPIDS_W                                11U
#define SOC_DEBUGSS_PWRAPIDR_JEPIDS_M                                0x0FFE0000U
#define SOC_DEBUGSS_PWRAPIDR_JEPIDS_S                                17U
/*

        Field:           REV
        From..to bits:   28...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Component Revision.  Indicates the revision of this AP instance. Currently 0000b

*/
#define SOC_DEBUGSS_PWRAPIDR_REV_W                                   4U
#define SOC_DEBUGSS_PWRAPIDR_REV_M                                   0xF0000000U
#define SOC_DEBUGSS_PWRAPIDR_REV_S                                   28U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SECAPTXD
    Offset name:         SOC_DEBUGSS_O_SECAPTXD
    Relative address:    0x200
    Description:         Transmit Data Register.

                        This register is used to pass data to the system security logic.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transmit Data Register.  This register is used to pass data to the system security logic.

*/
#define SOC_DEBUGSS_SECAPTXD_VAL_W                                   32U
#define SOC_DEBUGSS_SECAPTXD_VAL_M                                   0xFFFFFFFFU
#define SOC_DEBUGSS_SECAPTXD_VAL_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SECAPTXCTL
    Offset name:         SOC_DEBUGSS_O_SECAPTXCTL
    Relative address:    0x204
    Description:         Transmit Control Register.  This register provides the handshake for the TX Data Register and can also be used to pass control data to the system security logic.
    Default Value:       0x00000000

        Field:           DATAVAIL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Transmit Data Available.  Set automatically when the TX data Register is written
                         Cleared automatically when the system debug logic indicates it has accepted the TX data

*/
#define SOC_DEBUGSS_SECAPTXCTL_DATAVAIL                              0x00000001U
#define SOC_DEBUGSS_SECAPTXCTL_DATAVAIL_M                            0x00000001U
#define SOC_DEBUGSS_SECAPTXCTL_DATAVAIL_S                            0U
/*

        Field:           TXCTL
        From..to bits:   1...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Device specific control information from the system security logic

*/
#define SOC_DEBUGSS_SECAPTXCTL_TXCTL_W                               31U
#define SOC_DEBUGSS_SECAPTXCTL_TXCTL_M                               0xFFFFFFFEU
#define SOC_DEBUGSS_SECAPTXCTL_TXCTL_S                               1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SECAPRXD
    Offset name:         SOC_DEBUGSS_O_SECAPRXD
    Relative address:    0x208
    Description:         Receive Data Register.  This register is used to pass data from the system security logic.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Receive Data Register.  This register is used to pass data from the system security logic.

*/
#define SOC_DEBUGSS_SECAPRXD_VAL_W                                   32U
#define SOC_DEBUGSS_SECAPRXD_VAL_M                                   0xFFFFFFFFU
#define SOC_DEBUGSS_SECAPRXD_VAL_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RXCTL
    Offset name:         SOC_DEBUGSS_O_RXCTL
    Relative address:    0x20C
    Description:         Receive Control Register.  This register provides the handshake for the RX Data Register and can also be used to pass control data from the system security logic.
    Default Value:       0x00000000

        Field:           DATAVAIL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set automatically when the system security logic indicates that RX Data Register is valid.
                         Cleared automatically when the RX data Register is read.

*/
#define SOC_DEBUGSS_RXCTL_DATAVAIL                                   0x00000001U
#define SOC_DEBUGSS_RXCTL_DATAVAIL_M                                 0x00000001U
#define SOC_DEBUGSS_RXCTL_DATAVAIL_S                                 0U
/*

        Field:           RXCTL
        From..to bits:   1...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Device specific control information from the system security logic

*/
#define SOC_DEBUGSS_RXCTL_RXCTL_W                                    31U
#define SOC_DEBUGSS_RXCTL_RXCTL_M                                    0xFFFFFFFEU
#define SOC_DEBUGSS_RXCTL_RXCTL_S                                    1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SECAPIDR
    Offset name:         SOC_DEBUGSS_O_SECAPIDR
    Relative address:    0x2FC
    Description:         AP Identification Register.  The AP identification register allows tools to determine the manufacturer and the type of AP.
    Default Value:       0x002E0000

        Field:           APTYPE
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The AP Type Register.

*/
#define SOC_DEBUGSS_SECAPIDR_APTYPE_W                                4U
#define SOC_DEBUGSS_SECAPIDR_APTYPE_M                                0x0000000FU
#define SOC_DEBUGSS_SECAPIDR_APTYPE_S                                0U
/*

        Field:           APVAR
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AP Variant.  There is only one variant for this AP Type and it is 0.

*/
#define SOC_DEBUGSS_SECAPIDR_APVAR_W                                 4U
#define SOC_DEBUGSS_SECAPIDR_APVAR_M                                 0x000000F0U
#define SOC_DEBUGSS_SECAPIDR_APVAR_S                                 4U
/*

        Field:           APCLASS
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AP Class.  0 indicates that this AP is not a bridge to a memory interconnect (not a Memory Access Port).

*/
#define SOC_DEBUGSS_SECAPIDR_APCLASS                                 0x00010000U
#define SOC_DEBUGSS_SECAPIDR_APCLASS_M                               0x00010000U
#define SOC_DEBUGSS_SECAPIDR_APCLASS_S                               16U
/*

        Field:           JEPIDS
        From..to bits:   17...27
        DefaultValue:    0x17
        Access type:     read-only
        Description:     Manufacturer JEP106 ID.  The concatenated JEP106 ID and continuation ID for TI. This is 00000010111b.

*/
#define SOC_DEBUGSS_SECAPIDR_JEPIDS_W                                11U
#define SOC_DEBUGSS_SECAPIDR_JEPIDS_M                                0x0FFE0000U
#define SOC_DEBUGSS_SECAPIDR_JEPIDS_S                                17U
/*

        Field:           REVISION
        From..to bits:   28...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Component Revision.  Indicates the revision of this AP instance.

*/
#define SOC_DEBUGSS_SECAPIDR_REVISION_W                              4U
#define SOC_DEBUGSS_SECAPIDR_REVISION_M                              0xF0000000U
#define SOC_DEBUGSS_SECAPIDR_REVISION_S                              28U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ETAPSEL
    Offset name:         SOC_DEBUGSS_O_ETAPSEL
    Relative address:    0x300
    Description:         ETAP Register Selector.

                        Has a bit associated with each 32-bit  Status Bitfield in the status array. Bit 0
                        corresponds to Status Bitfield 0. At reset all available Status Bitfields are selected. After writing this bitfield STATREAD will return the value of the status bitfield with the lowest selected index.
    Default Value:       0x000000FF

        Field:           VAL
        From..to bits:   0...7
        DefaultValue:    0xFF
        Access type:     read-write
        Description:     Has a bit associated with each 32-bit  Status Bitfield in the status array. Bit 0
                         corresponds to Status Bitfield 0. At reset all available Status Bitfields are selected. After writing this bitfield [ETAPSTARD.*] will return the value of the status bitfield with the lowest selected index.

                         Attempting to select an unimplemented register will not set the associated bit.

*/
#define SOC_DEBUGSS_ETAPSEL_VAL_W                                    8U
#define SOC_DEBUGSS_ETAPSEL_VAL_M                                    0x000000FFU
#define SOC_DEBUGSS_ETAPSEL_VAL_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ETAPCAPCTL
    Offset name:         SOC_DEBUGSS_O_ETAPCAPCTL
    Relative address:    0x304
    Description:         ETAP Capability Control.

                        This register can be used to read out the capability parameters of EnergyTrace and allows controlling the function.
    Default Value:       0x00000007

        Field:           NUMREGS
        From..to bits:   0...7
        DefaultValue:    0x7
        Access type:     read-only
        Description:     Indicates the number of available 32bit register containing EnergyTrace data.  Actual registers is NUMREGS + 1.

*/
#define SOC_DEBUGSS_ETAPCAPCTL_NUMREGS_W                             8U
#define SOC_DEBUGSS_ETAPCAPCTL_NUMREGS_M                             0x000000FFU
#define SOC_DEBUGSS_ETAPCAPCTL_NUMREGS_S                             0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ETAPSTARD
    Offset name:         SOC_DEBUGSS_O_ETAPSTARD
    Relative address:    0x308
    Description:         ETAP Status Read.

                        Returns the value of the EnergyTrace++ status bitfields. After writing the [ETAPSEL.*] bitfield, this register will return the value of the first available status bitfield.
                        Subsequent reads will return the remaining bitfields as selected with [ETAPSEL.*].
    Default Value:       0x00000000

        Field:           FLAGS
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Returns the value of the EnergyTrace++ status bitfields. After writing the [ETAPSEL.*] bitfield, this register will return the value of the first available status bitfield.
                         Subsequent reads will return the remaining bitfields as selected with [ETAPSEL.*].

*/
#define SOC_DEBUGSS_ETAPSTARD_FLAGS_W                                32U
#define SOC_DEBUGSS_ETAPSTARD_FLAGS_M                                0xFFFFFFFFU
#define SOC_DEBUGSS_ETAPSTARD_FLAGS_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ETAPDMNCTL
    Offset name:         SOC_DEBUGSS_O_ETAPDMNCTL
    Relative address:    0x30C
    Description:         ETAP Domain Control.

                        Controls which async domains are included in the async handshake sequence for data capture.
    Default Value:       0x00000000

        Field:           DMNINC
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Each bit in this bitfield is associated with one of the 16 async domain controls (req/ack) supported by the ET-AP

                         0 = The domain is not included in the handshake request
                         1 = The domain is included in the handshake request

                         Osprey MDB, all 8 ET status buses are synchronous, this register will read all zeroes and writes will be ignored.

                         The mapping of domains to specific ET data sources is in device specific documentation

*/
#define SOC_DEBUGSS_ETAPDMNCTL_DMNINC_W                              8U
#define SOC_DEBUGSS_ETAPDMNCTL_DMNINC_M                              0x000000FFU
#define SOC_DEBUGSS_ETAPDMNCTL_DMNINC_S                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ETAPIDR
    Offset name:         SOC_DEBUGSS_O_ETAPIDR
    Relative address:    0x3FC
    Description:         ETAP Identification Register.

                        AP Identification Register.  The AP identification register allows tools to determine the manufacturer and the type of AP.
    Default Value:       0x002E0003

        Field:           APTYPE
        From..to bits:   0...3
        DefaultValue:    0x3
        Access type:     read-only
        Description:     The AP Type Register.

*/
#define SOC_DEBUGSS_ETAPIDR_APTYPE_W                                 4U
#define SOC_DEBUGSS_ETAPIDR_APTYPE_M                                 0x0000000FU
#define SOC_DEBUGSS_ETAPIDR_APTYPE_S                                 0U
/*

        Field:           APVAR
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AP Variant.  There is only one variant for this AP Type and it is 0.

*/
#define SOC_DEBUGSS_ETAPIDR_APVAR_W                                  4U
#define SOC_DEBUGSS_ETAPIDR_APVAR_M                                  0x000000F0U
#define SOC_DEBUGSS_ETAPIDR_APVAR_S                                  4U
/*

        Field:           APCLASS
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AP Class.  0 indicates that this is AP is not a bridge to a memory interconnect (not a Memory Access Port).

*/
#define SOC_DEBUGSS_ETAPIDR_APCLASS                                  0x00010000U
#define SOC_DEBUGSS_ETAPIDR_APCLASS_M                                0x00010000U
#define SOC_DEBUGSS_ETAPIDR_APCLASS_S                                16U
/*

        Field:           JEPIDS
        From..to bits:   17...27
        DefaultValue:    0x17
        Access type:     read-only
        Description:     Manufacturer JEP106 ID.  The concatenated JEP106 ID and continuation ID for TI. This is 00000010111b.

*/
#define SOC_DEBUGSS_ETAPIDR_JEPIDS_W                                 11U
#define SOC_DEBUGSS_ETAPIDR_JEPIDS_M                                 0x0FFE0000U
#define SOC_DEBUGSS_ETAPIDR_JEPIDS_S                                 17U
/*

        Field:           REVISION
        From..to bits:   28...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Component Revision.  Indicates the revision of this AP instance. Currently 0000b

*/
#define SOC_DEBUGSS_ETAPIDR_REVISION_W                               4U
#define SOC_DEBUGSS_ETAPIDR_REVISION_M                               0xF0000000U
#define SOC_DEBUGSS_ETAPIDR_REVISION_S                               28U

#endif /* __HW_SOC_DEBUGSS_H__*/
