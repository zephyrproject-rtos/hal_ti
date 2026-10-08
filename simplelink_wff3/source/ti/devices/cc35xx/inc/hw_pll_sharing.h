/******************************************************************************
*  Filename:       hw_pll_sharing.h
*
*  Description:    Defines and prototypes for the PLL_SHARING peripheral.
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
#ifndef __HW_PLL_SHARING_H__
#define __HW_PLL_SHARING_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the PLL_SHARING component

--------------------------------------------------------------------------------- */

//WCS PLL M
#define PLL_SHARING_O_WCSPLLM                                        0x00000000U

//WCS PLL N
#define PLL_SHARING_O_WCSPLLN                                        0x00000004U

//WCS Q FACTOR CONFIG
#define PLL_SHARING_O_WCSQFACCFG                                     0x00000008U

//WCS P FACTOR CONFIG
#define PLL_SHARING_O_WCSPFACCFG                                     0x0000000CU

//WCS PLL swallowing logic gen cfg
#define PLL_SHARING_O_WCSPLLSWAL                                     0x00000010U

//WCS PLL CONFIG
#define PLL_SHARING_O_WCSPLLCFG                                      0x00000014U

//CORE configuration for PLL Sharing
#define PLL_SHARING_O_CR                                             0x00000018U

//GENERAL
#define PLL_SHARING_O_GEN                                            0x0000001CU

//WCS CONFIG
#define PLL_SHARING_O_WCSCFG                                         0x00000020U

//GENERAL CONFIGURATION
#define PLL_SHARING_O_GENCFG                                         0x00000024U

//Lock status reg
#define PLL_SHARING_O_LOCK                                           0x00000028U

//SOP MASK
#define PLL_SHARING_O_SOPBM                                          0x0000002CU

//DEBUGSS
#define PLL_SHARING_O_DBGSS                                          0x00000030U

//ICG
#define PLL_SHARING_O_ICG                                            0x00000034U



/*-----------------------------------REGISTER------------------------------------
    Register name:       WCSPLLM
    Offset name:         PLL_SHARING_O_WCSPLLM
    Relative address:    0x0
    Description:         WCS PLL M

                        divider configuration for WCS PLL - primary reference
    Default Value:       0x000000A0

        Field:           VAL
        From..to bits:   0...8
        DefaultValue:    0xA0
        Access type:     read-write
        Description:     In all modes value should be 160

*/
#define PLL_SHARING_WCSPLLM_VAL_W                                    9U
#define PLL_SHARING_WCSPLLM_VAL_M                                    0x000001FFU
#define PLL_SHARING_WCSPLLM_VAL_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WCSPLLN
    Offset name:         PLL_SHARING_O_WCSPLLN
    Relative address:    0x4
    Description:         WCS PLL N

                        pre divider configuration for WCS PLL - primary reference
    Default Value:       0x00000014

        Field:           VAL
        From..to bits:   0...6
        DefaultValue:    0x14
        Access type:     read-write
        Description:     10MHz - 5
                         26MHz - 13
                         40MHz - 20
                         52MHz - 26

*/
#define PLL_SHARING_WCSPLLN_VAL_W                                    7U
#define PLL_SHARING_WCSPLLN_VAL_M                                    0x0000007FU
#define PLL_SHARING_WCSPLLN_VAL_S                                    0U
/*

        Field:           NSEL
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     N SELECTOR

                         '1' - use MMR N value
                         '0' - use HW auto detection (default)

*/
#define PLL_SHARING_WCSPLLN_NSEL                                     0x00000080U
#define PLL_SHARING_WCSPLLN_NSEL_M                                   0x00000080U
#define PLL_SHARING_WCSPLLN_NSEL_S                                   7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WCSQFACCFG
    Offset name:         PLL_SHARING_O_WCSQFACCFG
    Relative address:    0x8
    Description:         WCS Q FACTOR CONFIG

                        swallowing logic configuration for WCS PLL for primary reference clock input - 16 LSB : 16.2MHz - 801 : 16.368MHz - 3751 : 16.8MHz - disabled : 19.2MHz - disabled : 26MHz - disabled : 32.736MHz - 3751 : 33.6MHz - disabled : 38.4MHz - disabled : 52MHz - disabled
    Default Value:       0x00000000

        Field:           SWAL
        From..to bits:   0...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SWALLOWING

                         swallowing logic configuration  Q factor

*/
#define PLL_SHARING_WCSQFACCFG_SWAL_W                                24U
#define PLL_SHARING_WCSQFACCFG_SWAL_M                                0x00FFFFFFU
#define PLL_SHARING_WCSQFACCFG_SWAL_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WCSPFACCFG
    Offset name:         PLL_SHARING_O_WCSPFACCFG
    Relative address:    0xC
    Description:         WCS P FACTOR CONFIG

                        swallowing logic configuration for WCS PLL for primary reference clock input - 16 LSB : P factor 16 LSB : 16.2MHz - 4 : 16.368MHz - 4 : 16.8MHz - disabled : 19.2MHz - disabled : 26MHz - disabled : 32.736MHz - 4 : 33.6MHz - disabled : 38.4MHz - disabled : 52MHz - disabled
    Default Value:       0x00000000

        Field:           SWAL
        From..to bits:   0...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SWALLOWING

                          swallowing logic configuration P factor

*/
#define PLL_SHARING_WCSPFACCFG_SWAL_W                                20U
#define PLL_SHARING_WCSPFACCFG_SWAL_M                                0x000FFFFFU
#define PLL_SHARING_WCSPFACCFG_SWAL_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WCSPLLSWAL
    Offset name:         PLL_SHARING_O_WCSPLLSWAL
    Relative address:    0x10
    Description:         WCS PLL swallowing logic gen cfg
    Default Value:       0x00000012

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     enable the swallowing logic - disable when not using the bypass option

*/
#define PLL_SHARING_WCSPLLSWAL_EN                                    0x00000001U
#define PLL_SHARING_WCSPLLSWAL_EN_M                                  0x00000001U
#define PLL_SHARING_WCSPLLSWAL_EN_S                                  0U
/*

        Field:           BYP
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     bypass the swallowing logic

*/
#define PLL_SHARING_WCSPLLSWAL_BYP                                   0x00000002U
#define PLL_SHARING_WCSPLLSWAL_BYP_M                                 0x00000002U
#define PLL_SHARING_WCSPLLSWAL_BYP_S                                 1U
/*

        Field:           PRBSEN
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     enable prbs for adding randomization (jittering)- disable by default

*/
#define PLL_SHARING_WCSPLLSWAL_PRBSEN                                0x00000004U
#define PLL_SHARING_WCSPLLSWAL_PRBSEN_M                              0x00000004U
#define PLL_SHARING_WCSPLLSWAL_PRBSEN_S                              2U
/*

        Field:           PRBSGN
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PRBS GAIN

                         1: prbs addition is 5 bits to the right of MSB
                         0: prbs addition is 3 bits to the right of MSB

*/
#define PLL_SHARING_WCSPLLSWAL_PRBSGN                                0x00000008U
#define PLL_SHARING_WCSPLLSWAL_PRBSGN_M                              0x00000008U
#define PLL_SHARING_WCSPLLSWAL_PRBSGN_S                              3U
/*

        Field:           CONSWAL
        From..to bits:   4...5
        DefaultValue:    0x1
        Access type:     read-write
        Description:     CONSECUTIVE SWALLOWING

                         valid values (1-3) - number of consecutive clock swallows
                         once accumulator reached Q value for WCS PLL

*/
#define PLL_SHARING_WCSPLLSWAL_CONSWAL_W                             2U
#define PLL_SHARING_WCSPLLSWAL_CONSWAL_M                             0x00000030U
#define PLL_SHARING_WCSPLLSWAL_CONSWAL_S                             4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WCSPLLCFG
    Offset name:         PLL_SHARING_O_WCSPLLCFG
    Relative address:    0x14
    Description:         WCS PLL CONFIG

                        gen cfg for WCS PLL
    Default Value:       0x012A0270

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     enable like any other IP request

*/
#define PLL_SHARING_WCSPLLCFG_EN                                     0x00000001U
#define PLL_SHARING_WCSPLLCFG_EN_M                                   0x00000001U
#define PLL_SHARING_WCSPLLCFG_EN_S                                   0U
/*

        Field:           OV
        From..to bits:   1...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override register for WCS PLL enable

*/
#define PLL_SHARING_WCSPLLCFG_OV_W                                   2U
#define PLL_SHARING_WCSPLLCFG_OV_M                                   0x00000006U
#define PLL_SHARING_WCSPLLCFG_OV_S                                   1U
/*

        Field:           LOCKCNT
        From..to bits:   3...6
        DefaultValue:    0xE
        Access type:     read-write
        Description:     LOCK COUNT

                         time (sclk) from enabling the PLL until valid signal will rise.
                         Default is 14 since the PLL lock can go up to 200us and assuming

                         untrimmed slow clk is 15us we need at least 14 cycles
                         This value can be optimized by half  by s/w (Once we have trimmed slow clk)

*/
#define PLL_SHARING_WCSPLLCFG_LOCKCNT_W                              4U
#define PLL_SHARING_WCSPLLCFG_LOCKCNT_M                              0x00000078U
#define PLL_SHARING_WCSPLLCFG_LOCKCNT_S                              3U
/*

        Field:           USELOCKMON
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     USE LOCKMON

                         Do not enable this bit because Analog APLL design might have lock stays '1' even when FREF is dropped to OFF.
                         From safety POV, No DCC is used in Osprey, so having a counter based for PLL assumed Lock is ok for the level of safety required

                         1: use the PLL lock indication for lock
                         0: use the timer (mem_pllsh_wcs_pll_lock_cnt) for the lock

*/
#define PLL_SHARING_WCSPLLCFG_USELOCKMON                             0x00000080U
#define PLL_SHARING_WCSPLLCFG_USELOCKMON_M                           0x00000080U
#define PLL_SHARING_WCSPLLCFG_USELOCKMON_S                           7U
/*

        Field:           DISCNT
        From..to bits:   8...10
        DefaultValue:    0x2
        Access type:     read-write
        Description:     DISABLE COUNTER

                         time (sclk) from pll request goes low to the time PLL input will go low - keep >= 2

*/
#define PLL_SHARING_WCSPLLCFG_DISCNT_W                               3U
#define PLL_SHARING_WCSPLLCFG_DISCNT_M                               0x00000700U
#define PLL_SHARING_WCSPLLCFG_DISCNT_S                               8U
/*

        Field:           FCLKSEL
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FREF CLOCK SELECT

                         select bypass option to use external clock in case PLL not working

*/
#define PLL_SHARING_WCSPLLCFG_FCLKSEL                                0x00000800U
#define PLL_SHARING_WCSPLLCFG_FCLKSEL_M                              0x00000800U
#define PLL_SHARING_WCSPLLCFG_FCLKSEL_S                              11U
/*

        Field:           GLMFCLKSEL
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     GLITCH LESS MUX FREF CLOCK SELECT

                         select bypass option to use external clock in case PLL not working

*/
#define PLL_SHARING_WCSPLLCFG_GLMFCLKSEL                             0x00001000U
#define PLL_SHARING_WCSPLLCFG_GLMFCLKSEL_M                           0x00001000U
#define PLL_SHARING_WCSPLLCFG_GLMFCLKSEL_S                           12U
/*

        Field:           FCLKFSOV
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FREF CLOCK FUSE OVERRIDE

                         '1' - override the PLL_BYPASS fuse with PLL_BYPASS MMR: mem_pllsh_fref_clk_sel; '0' do not override

*/
#define PLL_SHARING_WCSPLLCFG_FCLKFSOV                               0x00002000U
#define PLL_SHARING_WCSPLLCFG_FCLKFSOV_M                             0x00002000U
#define PLL_SHARING_WCSPLLCFG_FCLKFSOV_S                             13U
/*

        Field:           LOCKOV
        From..to bits:   14...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     LOCK OVERRIDE

                         override option for WCS PLL lock indication - should be used when using the override option for PLL enable

*/
#define PLL_SHARING_WCSPLLCFG_LOCKOV_W                               2U
#define PLL_SHARING_WCSPLLCFG_LOCKOV_M                               0x0000C000U
#define PLL_SHARING_WCSPLLCFG_LOCKOV_S                               14U
/*

        Field:           LFREQMODEN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     LOW FREQUENCY MODE ENABLE

                         connected to WCS PLL LOWFREQ_MODE_EN input : 0:Normal mode : 1: Divide by 2 the PLL clock out

*/
#define PLL_SHARING_WCSPLLCFG_LFREQMODEN                             0x00010000U
#define PLL_SHARING_WCSPLLCFG_LFREQMODEN_M                           0x00010000U
#define PLL_SHARING_WCSPLLCFG_LFREQMODEN_S                           16U
/*

        Field:           HFREQMODEN
        From..to bits:   17...17
        DefaultValue:    0x1
        Access type:     read-write
        Description:     HIGH FREQUENCY MODE ENABLE

                         connected to WCS PLL HIGHFREQ_MODE_EN input : 0: 300M-500M ICO disabled : 1: 300M-400M/400M-500M ICO enabled : based on CONTROL bits [7:6]

*/
#define PLL_SHARING_WCSPLLCFG_HFREQMODEN                             0x00020000U
#define PLL_SHARING_WCSPLLCFG_HFREQMODEN_M                           0x00020000U
#define PLL_SHARING_WCSPLLCFG_HFREQMODEN_S                           17U
/*

        Field:           CLRVCOSLP
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CLEAR VCO DURING SLEEP

                         '1' - during sleep VCO 300-400MHz will be gated
                         '0' - during sleep VCO 300-400MHz will stay high

*/
#define PLL_SHARING_WCSPLLCFG_CLRVCOSLP                              0x00040000U
#define PLL_SHARING_WCSPLLCFG_CLRVCOSLP_M                            0x00040000U
#define PLL_SHARING_WCSPLLCFG_CLRVCOSLP_S                            18U
/*

        Field:           PHSEL
        From..to bits:   19...23
        DefaultValue:    0x5
        Access type:     read-write
        Description:     PHASE SELECT

                         the following values should be used:
                         10MHz - up to decimal 0..31
                         26MHz - up to decimal 0..11
                         40MHz - up to decimal 0..7
                         52MHz - up to decimal 0..5
                         notes:
                         *delayes are set in 320MHz clk
                         *due to sync issues delay could get +1 of the setting value

*/
#define PLL_SHARING_WCSPLLCFG_PHSEL_W                                5U
#define PLL_SHARING_WCSPLLCFG_PHSEL_M                                0x00F80000U
#define PLL_SHARING_WCSPLLCFG_PHSEL_S                                19U
/*

        Field:           PHASEOV
        From..to bits:   24...24
        DefaultValue:    0x1
        Access type:     read-write
        Description:     PHASE OVERRIDE

                         '1' - Overrideing phase control implementation.

*/
#define PLL_SHARING_WCSPLLCFG_PHASEOV                                0x01000000U
#define PLL_SHARING_WCSPLLCFG_PHASEOV_M                              0x01000000U
#define PLL_SHARING_WCSPLLCFG_PHASEOV_S                              24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CR
    Offset name:         PLL_SHARING_O_CR
    Relative address:    0x18
    Description:         CORE configuration for PLL Sharing
    Default Value:       0x00000000

        Field:           PLLEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PLL ENABLE

                         register for Core to enable PLLs according to the type instead of using HW request core_pll_en

*/
#define PLL_SHARING_CR_PLLEN                                         0x00000001U
#define PLL_SHARING_CR_PLLEN_M                                       0x00000001U
#define PLL_SHARING_CR_PLLEN_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GEN
    Offset name:         PLL_SHARING_O_GEN
    Relative address:    0x1C
    Description:         GENERAL

                        PLL divider configuration
    Default Value:       0x0008015E

        Field:           CRDIV2OV
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CORE DIVIDER 2 OVERRIDE

                         1: no division (80MHz clock) : 0: divide by 2 (40MHz clock)

*/
#define PLL_SHARING_GEN_CRDIV2OV                                     0x00000001U
#define PLL_SHARING_GEN_CRDIV2OV_M                                   0x00000001U
#define PLL_SHARING_GEN_CRDIV2OV_S                                   0U
/*

        Field:           CRM3DIV2OV
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     CORE M3 DIVIDER OVERRIDE

                         1: no division (80MHz clock) : 0: divide by 2 (40MHz clock)

*/
#define PLL_SHARING_GEN_CRM3DIV2OV                                   0x00000002U
#define PLL_SHARING_GEN_CRM3DIV2OV_M                                 0x00000002U
#define PLL_SHARING_GEN_CRM3DIV2OV_S                                 1U
/*

        Field:           SOCDIV2OV
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     SOC DIVIDER 2 OVERRIDE

                         1: no division (80MHz clock) : 0: divide by 2 (40MHz clock)

*/
#define PLL_SHARING_GEN_SOCDIV2OV                                    0x00000004U
#define PLL_SHARING_GEN_SOCDIV2OV_M                                  0x00000004U
#define PLL_SHARING_GEN_SOCDIV2OV_S                                  2U
/*

        Field:           PPLLDIVVAL
        From..to bits:   4...5
        DefaultValue:    0x1
        Access type:     read-write
        Description:     PSCON PLL DIVIDER OVERRIDE

                         0: no division (80MHz clock) : PSCON div val. Set the PSCON clock period:  0-1us; 1-2us; 2-4us; 3-16us

*/
#define PLL_SHARING_GEN_PPLLDIVVAL_W                                 2U
#define PLL_SHARING_GEN_PPLLDIVVAL_M                                 0x00000030U
#define PLL_SHARING_GEN_PPLLDIVVAL_S                                 4U
/*

        Field:           PPLLLDDIVV
        From..to bits:   6...6
        DefaultValue:    0x1
        Access type:     read-write
        Description:     PSCON PLL LOAD DIVIDER VALUE

                         Load div value indication. Default is 1

*/
#define PLL_SHARING_GEN_PPLLLDDIVV                                   0x00000040U
#define PLL_SHARING_GEN_PPLLLDDIVV_M                                 0x00000040U
#define PLL_SHARING_GEN_PPLLLDDIVV_S                                 6U
/*

        Field:           PCLKSRCCNG
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PSCON CLOCK SOURCE CHANGE

                         Change divider input clock

*/
#define PLL_SHARING_GEN_PCLKSRCCNG                                   0x00000080U
#define PLL_SHARING_GEN_PCLKSRCCNG_M                                 0x00000080U
#define PLL_SHARING_GEN_PCLKSRCCNG_S                                 7U
/*

        Field:           PDIVEN
        From..to bits:   8...8
        DefaultValue:    0x1
        Access type:     read-write
        Description:     PSCON DIVIDER ENABLE

                         divider enable. Default is 1. Enabled.

*/
#define PLL_SHARING_GEN_PDIVEN                                       0x00000100U
#define PLL_SHARING_GEN_PDIVEN_M                                     0x00000100U
#define PLL_SHARING_GEN_PDIVEN_S                                     8U
/*

        Field:           PHYDIV2OV
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PHY DIVIDER 2 OVERRIDE

                         1: no division (80MHz clock) : 0: divide by 2 (40MHz clock)

*/
#define PLL_SHARING_GEN_PHYDIV2OV                                    0x00000200U
#define PLL_SHARING_GEN_PHYDIV2OV_M                                  0x00000200U
#define PLL_SHARING_GEN_PHYDIV2OV_S                                  9U
/*

        Field:           CRM3ICGOV
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CORE M3 ICG OVERRIDE

                         '0' - No Override
                         '1' - Enables CORE M3 80MHz CLK

*/
#define PLL_SHARING_GEN_CRM3ICGOV                                    0x00010000U
#define PLL_SHARING_GEN_CRM3ICGOV_M                                  0x00010000U
#define PLL_SHARING_GEN_CRM3ICGOV_S                                  16U
/*

        Field:           SOCICGOV
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SOC ICG OVERRIDE

                         '0' - No Override
                         '1' - Enables SOC 80MHz CLK

*/
#define PLL_SHARING_GEN_SOCICGOV                                     0x00020000U
#define PLL_SHARING_GEN_SOCICGOV_M                                   0x00020000U
#define PLL_SHARING_GEN_SOCICGOV_S                                   17U
/*

        Field:           HICGOV
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HOST ICG OVERRIDE

                         '0' - No Override
                         '1' - Enables HOST CLKs

*/
#define PLL_SHARING_GEN_HICGOV                                       0x00040000U
#define PLL_SHARING_GEN_HICGOV_M                                     0x00040000U
#define PLL_SHARING_GEN_HICGOV_S                                     18U
/*

        Field:           PICGOV
        From..to bits:   19...19
        DefaultValue:    0x1
        Access type:     read-write
        Description:     PSCON ICG OVERRIDE

                         Default is 1

*/
#define PLL_SHARING_GEN_PICGOV                                       0x00080000U
#define PLL_SHARING_GEN_PICGOV_M                                     0x00080000U
#define PLL_SHARING_GEN_PICGOV_S                                     19U
/*

        Field:           GPADCICGOV
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     GPADC ICG OVERRIDE

                         '1' - enable gpadc clk
                         '0' - disable clock

*/
#define PLL_SHARING_GEN_GPADCICGOV                                   0x00100000U
#define PLL_SHARING_GEN_GPADCICGOV_M                                 0x00100000U
#define PLL_SHARING_GEN_GPADCICGOV_S                                 20U
/*

        Field:           CRICGOV
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CORE ICG OVERRIDE

                         1: ICG of PLL to Core is forced enable : 0: ICG is enabled according to elp request and core_pll_en

*/
#define PLL_SHARING_GEN_CRICGOV                                      0x00200000U
#define PLL_SHARING_GEN_CRICGOV_M                                    0x00200000U
#define PLL_SHARING_GEN_CRICGOV_S                                    21U
/*

        Field:           PHYICGOV
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PHY ICG OVERRIDE

                         1: ICG of PLL to PHY is forced enable : 0: ICG is enabled according to elp request and phy_pll_en

*/
#define PLL_SHARING_GEN_PHYICGOV                                     0x00400000U
#define PLL_SHARING_GEN_PHYICGOV_M                                   0x00400000U
#define PLL_SHARING_GEN_PHYICGOV_S                                   22U
/*

        Field:           UALGNPHYCR
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UNALIGNED PHY TO CORE

                         1: PHY and core clk will get phase difference

*/
#define PLL_SHARING_GEN_UALGNPHYCR                                   0x01000000U
#define PLL_SHARING_GEN_UALGNPHYCR_M                                 0x01000000U
#define PLL_SHARING_GEN_UALGNPHYCR_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WCSCFG
    Offset name:         PLL_SHARING_O_WCSCFG
    Relative address:    0x20
    Description:         WCS CONFIG

                         WCS PLL control input : Refer to WCSPLL spec
    Default Value:       0x00045100

        Field:           CTL
        From..to bits:   0...31
        DefaultValue:    0x45100
        Access type:     read-write
        Description:     CONTROL

*/
#define PLL_SHARING_WCSCFG_CTL_W                                     32U
#define PLL_SHARING_WCSCFG_CTL_M                                     0xFFFFFFFFU
#define PLL_SHARING_WCSCFG_CTL_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GENCFG
    Offset name:         PLL_SHARING_O_GENCFG
    Relative address:    0x24
    Description:         GENERAL CONFIGURATION

                        PLL sharing module general configurations
    Default Value:       0x00000000

        Field:           DFTWCSPICGOV
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DFT WCS PLL ICG OVERRIDE

                         control WCS PLL clock toward test ctrl

*/
#define PLL_SHARING_GENCFG_DFTWCSPICGOV                              0x00000001U
#define PLL_SHARING_GENCFG_DFTWCSPICGOV_M                            0x00000001U
#define PLL_SHARING_GENCFG_DFTWCSPICGOV_S                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LOCK
    Offset name:         PLL_SHARING_O_LOCK
    Relative address:    0x28
    Description:         Lock status reg
    Default Value:       0x00000000

        Field:           STS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     STATUS

                         PLL Timer for Lock status register
                         in case MEM_USE_LOCKMON = 1 - this indication is similar to LOCKMON_STS
                         in case MEM_USE_LOCKMON = 0 - this indication reflect the Lock Timer (configured by PLL_LOCK_CNT) status (1 means elapsed)

*/
#define PLL_SHARING_LOCK_STS                                         0x00000001U
#define PLL_SHARING_LOCK_STS_M                                       0x00000001U
#define PLL_SHARING_LOCK_STS_S                                       0U
/*

        Field:           MONSTS
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LOCK MONITOR STATUS

                         PLL Lock status register

*/
#define PLL_SHARING_LOCK_MONSTS                                      0x00000002U
#define PLL_SHARING_LOCK_MONSTS_M                                    0x00000002U
#define PLL_SHARING_LOCK_MONSTS_S                                    1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SOPBM
    Offset name:         PLL_SHARING_O_SOPBM
    Relative address:    0x2C
    Description:         SOP MASK

                        PLL sharing module SOP mask config
    Default Value:       0x00000000

        Field:           PLLEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PLL ENABLE

                         SOP mask - Mask SOPs Bypass so PLL can be enabled. Default is 0  - "do not mask SOP"

*/
#define PLL_SHARING_SOPBM_PLLEN                                      0x00000001U
#define PLL_SHARING_SOPBM_PLLEN_M                                    0x00000001U
#define PLL_SHARING_SOPBM_PLLEN_S                                    0U
/*

        Field:           FREFSEL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FREF SELECTOR

                         SOP mask - Mask SOPs Bypass so PLL FREF selected from HFXT over DIO pin. Default is 0 - "do not mask SOP"

*/
#define PLL_SHARING_SOPBM_FREFSEL                                    0x00000002U
#define PLL_SHARING_SOPBM_FREFSEL_M                                  0x00000002U
#define PLL_SHARING_SOPBM_FREFSEL_S                                  1U
/*

        Field:           BYPSEL
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     BYPASS SELECTOR

                         SOP mask - Mask SOPs Bypass so PLL Bypass can be can be bypassed by SoC PLL. Default is 0 - "do not mask SOP"

*/
#define PLL_SHARING_SOPBM_BYPSEL                                     0x00000004U
#define PLL_SHARING_SOPBM_BYPSEL_M                                   0x00000004U
#define PLL_SHARING_SOPBM_BYPSEL_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGSS
    Offset name:         PLL_SHARING_O_DBGSS
    Relative address:    0x30
    Description:         DEBUGSS
    Default Value:       0x00000000

        Field:           FSEL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FAST SELECTOR

                         Lock status register; clear upon read by S/W

*/
#define PLL_SHARING_DBGSS_FSEL                                       0x00000001U
#define PLL_SHARING_DBGSS_FSEL_M                                     0x00000001U
#define PLL_SHARING_DBGSS_FSEL_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ICG
    Offset name:         PLL_SHARING_O_ICG
    Relative address:    0x34
    Description:         ICG
    Default Value:       0x00000050

        Field:           CRM3DIS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CORE M3 DISABLE

                         ICG Disable control
                         '1' - disable
                         '0' - enable

*/
#define PLL_SHARING_ICG_CRM3DIS                                      0x00000001U
#define PLL_SHARING_ICG_CRM3DIS_M                                    0x00000001U
#define PLL_SHARING_ICG_CRM3DIS_S                                    0U
/*

        Field:           CRDIS
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CORE ICS DISABLE

                         ICG Disable control
                         '1' - disable
                         '0' - enable

*/
#define PLL_SHARING_ICG_CRDIS                                        0x00000002U
#define PLL_SHARING_ICG_CRDIS_M                                      0x00000002U
#define PLL_SHARING_ICG_CRDIS_S                                      1U
/*

        Field:           SOCDIS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SOC DISABLE

                         ICG Disable control
                         '1' - disable
                         '0' - enable

*/
#define PLL_SHARING_ICG_SOCDIS                                       0x00000004U
#define PLL_SHARING_ICG_SOCDIS_M                                     0x00000004U
#define PLL_SHARING_ICG_SOCDIS_S                                     2U
/*

        Field:           HDIS
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HOST DISABLE

                         ICG Disable control
                         '1' - disable
                         '0' - enable

*/
#define PLL_SHARING_ICG_HDIS                                         0x00000008U
#define PLL_SHARING_ICG_HDIS_M                                       0x00000008U
#define PLL_SHARING_ICG_HDIS_S                                       3U
/*

        Field:           PLL32DIS
        From..to bits:   4...4
        DefaultValue:    0x1
        Access type:     read-write
        Description:     PLL 32 DISABLE

                         ICG control
                         '1' - disable
                         '0' - enable

*/
#define PLL_SHARING_ICG_PLL32DIS                                     0x00000010U
#define PLL_SHARING_ICG_PLL32DIS_M                                   0x00000010U
#define PLL_SHARING_ICG_PLL32DIS_S                                   4U
/*

        Field:           PHYDIS
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PHY DISABLE

                         ICG Disable control
                         '1' - disable
                         '0' - enable

*/
#define PLL_SHARING_ICG_PHYDIS                                       0x00000020U
#define PLL_SHARING_ICG_PHYDIS_M                                     0x00000020U
#define PLL_SHARING_ICG_PHYDIS_S                                     5U
/*

        Field:           SOCPSWLDIS
        From..to bits:   6...6
        DefaultValue:    0x1
        Access type:     read-write
        Description:     SOC PSWL DISABLE

                         ICG Disable control
                         '1' - disable
                         '0' - enable

*/
#define PLL_SHARING_ICG_SOCPSWLDIS                                   0x00000040U
#define PLL_SHARING_ICG_SOCPSWLDIS_M                                 0x00000040U
#define PLL_SHARING_ICG_SOCPSWLDIS_S                                 6U

#endif /* __HW_PLL_SHARING_H__*/
