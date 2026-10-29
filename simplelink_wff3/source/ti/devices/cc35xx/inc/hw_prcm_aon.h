/******************************************************************************
*  Filename:       hw_prcm_aon.h
*
*  Description:    Defines and prototypes for the PRCM_AON peripheral.
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
#ifndef __HW_PRCM_AON_H__
#define __HW_PRCM_AON_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the PRCM_AON component

--------------------------------------------------------------------------------- */

//PSCON Memory Groups Control Host Flex
#define PRCM_AON_O_HFLXGRP                                           0x00001034U

//PSCON Memory Groups Indication Host Flex
#define PRCM_AON_O_HFLXGRPIND                                        0x00001038U

//PSCON Memory Status Refresh
#define PRCM_AON_O_REFCTL                                            0x00001048U

//Memory Refresh Status
#define PRCM_AON_O_REFSTA                                            0x0000104CU

//PSCON Memory Groups Control Host Static
#define PRCM_AON_O_HSTATICGRP                                        0x00001054U

//Memory bank from this group is shared
#define PRCM_AON_O_HSTATICGRPIND                                     0x00001058U

//Logic Host Memory Status
#define PRCM_AON_O_LOGHMEMSTA                                        0x0000105CU

//Connectivity Stop
#define PRCM_AON_O_CONNSTP                                           0x00001060U

//HOST RESET OV CONTROL
#define PRCM_AON_O_HRSTOV                                            0x00001064U

//The register holds sleepdeep command for the host_mcu for debugging
#define PRCM_AON_O_SLPDEEP                                           0x00001068U

//SHARED PRECISE
#define PRCM_AON_O_SHPRECISE                                         0x00002000U

//LFXT CONTROL
#define PRCM_AON_O_LFXTCTL                                           0x00002008U

//LFXT SPARE
#define PRCM_AON_O_LFXTSPARE                                         0x0000200CU

//LFOSC ENABLE
#define PRCM_AON_O_LFOSCEN                                           0x00002010U

//FUSE DATA 5
#define PRCM_AON_O_FUSEDATA5                                         0x00002014U

//FUSE DATA 6
#define PRCM_AON_O_FUSEDATA6                                         0x00002018U

//FUSE DATA 7
#define PRCM_AON_O_FUSEDATA7                                         0x0000201CU

//FUSE DATA 8
#define PRCM_AON_O_FUSEDATA8                                         0x00002020U

//FUSE DATA 9
#define PRCM_AON_O_FUSEDATA9                                         0x00002024U

//FUSE DATA 10
#define PRCM_AON_O_FUSEDATA10                                        0x00002028U

//FUSE DATA 11
#define PRCM_AON_O_FUSEDATA11                                        0x0000202CU

//FUSE DATA 12
#define PRCM_AON_O_FUSEDATA12                                        0x00002030U

//FUSE DATA 13
#define PRCM_AON_O_FUSEDATA13                                        0x00002034U

//FUSE DATA 14
#define PRCM_AON_O_FUSEDATA14                                        0x00002038U

//PRCM RAW FUSE 0
#define PRCM_AON_O_PRCMRAWFS0                                        0x0000203CU

//PRCM RAW FUSE 1
#define PRCM_AON_O_PRCMRAWFS1                                        0x00002040U

//PRCM RAW FUSE 2
#define PRCM_AON_O_PRCMRAWFS2                                        0x00002044U

//PRCM RAW FUSE 3
#define PRCM_AON_O_PRCMRAWFS3                                        0x00002048U

//PRCM RAW FUSE 4
#define PRCM_AON_O_PRCMRAWFS4                                        0x0000204CU

//PRCM RAW FUSE 5
#define PRCM_AON_O_PRCMRAWFS5                                        0x00002050U

//PRCM RAW FUSE 6
#define PRCM_AON_O_PRCMRAWFS6                                        0x00002054U

//PRCM RAW FUSE 7
#define PRCM_AON_O_PRCMRAWFS7                                        0x00002058U

//PRCM RAW FUSE 8
#define PRCM_AON_O_PRCMRAWFS8                                        0x0000205CU

//PRCM RAW FUSE 9
#define PRCM_AON_O_PRCMRAWFS9                                        0x00002060U

//PRCM RAW FUSE 10
#define PRCM_AON_O_PRCMRAWFS10                                       0x00002064U

//FAST CLK DETECTION
#define PRCM_AON_O_FCLKDET                                           0x00002068U

//SOC PLL LOCK LOSS CONFIG
#define PRCM_AON_O_PLOCKLOSCFG                                       0x0000206CU

//SOC PLL LOCK LOSS STATUS
#define PRCM_AON_O_PLOCKLOSSTA                                       0x00002070U

//RTC CONTROL
#define PRCM_AON_O_RTCCTL                                            0x00002074U

//LFINC CONTROL
#define PRCM_AON_O_LFINCCTL                                          0x00002078U

//LFCLK STATUS
#define PRCM_AON_O_LFCLKSTA                                          0x0000207CU

//LFINC OVERRIDE
#define PRCM_AON_O_LFINCOVR                                          0x00002080U

//Low frequency clock qualification control
#define PRCM_AON_O_LFQUALCTL                                         0x00002084U

//Low frequency time increment value
#define PRCM_AON_O_LFINCCTLI                                         0x00002088U

//SLOW CLK COUNT
#define PRCM_AON_O_SCLKCNT                                           0x0000208CU

//SLOW CLOCK COUNTER CONTROL
#define PRCM_AON_O_SCLKCNTCTL                                        0x00002090U

//SLOW CLK COUNT START KICK
#define PRCM_AON_O_SCLKCNTSTRT                                       0x00002094U

//SLOW CLK CONTROL
#define PRCM_AON_O_SCLKCTL                                           0x00002098U

//PRCM STATUS
#define PRCM_AON_O_STA                                               0x0000209CU

//[0]- indication at slow CLK calibration for one shot mode
#define PRCM_AON_O_INTERUPT                                          0x000020A0U

//HOST PRCM SHARED
#define PRCM_AON_O_HPRCMSHAR                                         0x000020A4U

//CORE SLEEP INDICATION
#define PRCM_AON_O_CRSLPIND                                          0x000020A8U

//HOST SLEEP INDICATION
#define PRCM_AON_O_HSLPIND                                           0x000020ACU

//PRCM functional selection towards FAST CLK DETECTION
#define PRCM_AON_O_FNCLKMUXCTL                                       0x000020B0U

//RESET CONTROL
#define PRCM_AON_O_RSTCTL                                            0x000020B4U

//LFOSC OVERRIDE STATUS
#define PRCM_AON_O_LFOSC                                             0x000020B8U

//FUSE CONFIG
#define PRCM_AON_O_FSCFG                                             0x00007000U

//PMCIO
#define PRCM_AON_O_PMCIO                                             0x00007004U

//BODCTL
#define PRCM_AON_O_BOD                                               0x0000700CU

//RVM HIGH CONTROL
#define PRCM_AON_O_RVMH                                              0x00007010U

//RVM LOW CONTROL
#define PRCM_AON_O_RVML                                              0x00007014U

//PSCON MEMORY DELAY CONTROL
#define PRCM_AON_O_PSCON                                             0x00007018U

//digital bandgap enable register
#define PRCM_AON_O_DBGAPEN                                           0x0000701CU

//DBGAP override register
#define PRCM_AON_O_OVDBGAP1                                          0x00007020U

//DBGAP override register
#define PRCM_AON_O_OVDBGAP2                                          0x00007024U

//SLEEP REFERENCE
#define PRCM_AON_O_SLPREF                                            0x00007028U

//Digital Band Gap GM
#define PRCM_AON_O_DBGGM                                             0x0000702CU

//PMU RTRIM
#define PRCM_AON_O_PMURTRIM                                          0x00007030U

//VNWA CONTROL
#define PRCM_AON_O_VNWACTL                                           0x00007034U

//SRAM KA trim register
#define PRCM_AON_O_SRAMKATRIM                                        0x00007038U

//VALUE
#define PRCM_AON_O_VAL                                               0x00007040U

//SRAM KA ENABLE
#define PRCM_AON_O_SRAMKAEN                                          0x00007044U

//DIG LDO ENABLE
#define PRCM_AON_O_DLDOEN                                            0x00007048U

//override register for DIG LDO TRIM
#define PRCM_AON_O_DLDOVTRIM                                         0x0000704CU

//DIG KA ENABLE
#define PRCM_AON_O_DKAEN                                             0x00007050U

//DIG KA trim register
#define PRCM_AON_O_DKATRIM                                           0x00007054U

//DIGITAL LDO LOW POWER MODE
#define PRCM_AON_O_DLDOLPMOD                                         0x00007058U

//DIGITAL LDO CONFIG
#define PRCM_AON_O_DLDOCFG                                           0x0000705CU

//RVM TRIM CONTROL
#define PRCM_AON_O_RVMTRIMCTL                                        0x00007060U

//RVM TRIM PMU STATUS
#define PRCM_AON_O_RVMTRIMPMUSTA                                     0x00007064U

//RVML TRIM CONTROL
#define PRCM_AON_O_RVMLTRIMCTL                                       0x00007068U

//I2V CIRCUIT CONTROL
#define PRCM_AON_O_I2VCIRCITCTL                                      0x0000706CU

//PMBIST CONTROL
#define PRCM_AON_O_PMBISTCTL                                         0x00007070U

//PMU COMPARATOR
#define PRCM_AON_O_PMUCOMP                                           0x00007074U

//Analog band gap rtrim
#define PRCM_AON_O_ABGRTRIM                                          0x00007078U

//ABGAP TRIM TEMP
#define PRCM_AON_O_ABGTRIMTMP                                        0x0000707CU

//CKM SPARE
#define PRCM_AON_O_CKMSPARE                                          0x00007080U

//ABGAP ENABLE
#define PRCM_AON_O_ABGPEN                                            0x00007084U

//ABGAP TRIM MAG
#define PRCM_AON_O_ABGPTRIMMAG                                       0x00007088U

//FAST CLK REQUEST ABGAP DELAY
#define PRCM_AON_O_FCLKREQABGPDLY                                    0x0000708CU

//FAST CLK LDO DELAY
#define PRCM_AON_O_FCLKLDODLY                                        0x00007090U

//FAST CLK ABGAP SET DELAY
#define PRCM_AON_O_FCBGSETDLY                                        0x00007094U

//FAST CLK ABGAP FAST CHARGE DELAY
#define PRCM_AON_O_FCLKABGPFCDLY                                     0x00007098U

//analog bandgap disabling time register
#define PRCM_AON_O_ABGPDISDLY                                        0x0000709CU

//ABGAP TEST MODE
#define PRCM_AON_O_ABGPTSTMOD                                        0x000070A0U

//PRIMARY SLICER LDO ILOAD
#define PRCM_AON_O_PRIMSLDOILOD                                      0x000070A4U

//primary slicer LDO configurations
#define PRCM_AON_O_PRIMSLIC                                          0x000070A8U

//FAST CLK DISABLE HFXT DELAY
#define PRCM_AON_O_FCLKDISHFXTDLY                                    0x000070ACU

//CLK SLICER ENABLE
#define PRCM_AON_O_CLKSLIEN                                          0x000070B0U

//CLK SLICER ITRIM
#define PRCM_AON_O_CLKSLIITRIM                                       0x000070B4U

//primary clock rtrim cfg register
#define PRCM_AON_O_PRIMSLIRTRIM                                      0x000070B8U

//PRIMARY OSCILLATOR
#define PRCM_AON_O_PRIMOSC                                           0x000070BCU

//OSC ENABLE
#define PRCM_AON_O_OSCEN                                             0x000070C0U

//oscillator itrim cfg register
#define PRCM_AON_O_OSCITRIM                                          0x000070C4U

//OSC BOOST DELAY
#define PRCM_AON_O_OSCBSTDLY                                         0x000070C8U

//OSC NORMAL DELAY
#define PRCM_AON_O_OSCNORMDLY                                        0x000070CCU

//core and dig buffer control register
#define PRCM_AON_O_CRDIGBUFCTRL                                      0x000070D0U

//OSCILLATOR DELAY
#define PRCM_AON_O_OSCDLY                                            0x000070D4U

//startup clock module ldo control
#define PRCM_AON_O_STRUCMLDOCTL                                      0x000070D8U

//SHADOW FAST CLK CONTROL
#define PRCM_AON_O_SHDOWFCLKCTL                                      0x000070DCU

//slicer bias bypass control reg
#define PRCM_AON_O_SLIBIBYPCTL                                       0x000070E0U

//EXTERNAL CLOCK REQUEST DELAY
#define PRCM_AON_O_ECLKREQDLY                                        0x000070E4U

//OSC GAIN
#define PRCM_AON_O_OSCGN                                             0x000070E8U

//Primary EN TMUX CFG
#define PRCM_AON_O_PRIMENTMUX                                        0x000070ECU

//PRIMARY ENABLE
#define PRCM_AON_O_PRIMEN                                            0x000070F0U

//PUSH PULL ENABLE
#define PRCM_AON_O_PUSHPULEN                                         0x000070F4U

//FAST CLOCK DISABLE CLK OUT DELAY
#define PRCM_AON_O_FCLKDISCODLY                                      0x000070F8U

//FAST CLK VALID EXTEND DELAY
#define PRCM_AON_O_FCLKVLDEXNDLY                                     0x000070FCU

//PRIMARY EXIT SLEEP DELAY
#define PRCM_AON_O_PRIMEXITSLPDLY                                    0x00007100U

//fast CLK control over selectors and overrides
#define PRCM_AON_O_FCLK                                              0x00007108U

//Primary TMUX CFG
#define PRCM_AON_O_FCLKDURDLY                                        0x0000710CU

//FREF DETECTION
#define PRCM_AON_O_FREFDET                                           0x00007110U

//this is a SOP OV reg, which is a shadow register
#define PRCM_AON_O_FCLKFSMSOPOV                                      0x00007114U

//HW connected to PMCIO - To enable the Rnwell calibration
#define PRCM_AON_O_PMSRNWCAL                                         0x00007118U

//PMCIO test configurations
#define PRCM_AON_O_PMSTEST                                           0x0000711CU

//Test mux control signals
#define PRCM_AON_O_PMSTMUXCTL                                        0x00007120U

//PMS SPARE REG 0
#define PRCM_AON_O_PMSSPAR0                                          0x00007124U

//PMS SPARE REG 1
#define PRCM_AON_O_PMSSPAR1                                          0x00007128U

//PMS SPARE REG 2
#define PRCM_AON_O_PMSSPAR2                                          0x0000712CU

//PMS CONTROL STATUS
#define PRCM_AON_O_PMSCTLSTA                                         0x00007130U

//PMS SPARE INPUT
#define PRCM_AON_O_PMSSPARIN                                         0x00007134U

//PMS POR TEST CONTROL
#define PRCM_AON_O_PMSPORTSTCTL                                      0x00007138U

//PMS SPARE 3
#define PRCM_AON_O_PMSSPAR3                                          0x00007140U

//PMS SPARE 4
#define PRCM_AON_O_PMSSPAR4                                          0x00007144U

//PMS DELAYS
#define PRCM_AON_O_PMSDLY                                            0x00007148U

//DIGITAL BANDGAP DISABLE BANDGAP ENABLE DELAY
#define PRCM_AON_O_BGDISBGENDLY                                      0x0000714CU

//SW ENABLE SW DISABLE DELAY
#define PRCM_AON_O_SWENSWDISDLY                                      0x00007150U

//BANDGAP ENABLE SW ENABLE SLEEP DELAY
#define PRCM_AON_O_BGENSWENDLY                                       0x00007154U

//SW DISABLE BANDGAP DISABLE DELAY
#define PRCM_AON_O_SWDISBGDISDLY                                     0x00007158U

//ICG CONTROL
#define PRCM_AON_O_ICGCTL                                            0x0000715CU

//HALT
#define PRCM_AON_O_HALT                                              0x00007160U

//LOGIC CAPTURE
#define PRCM_AON_O_LOGICCA                                           0x0000716CU

//LOGIC MEMORY STATUS
#define PRCM_AON_O_LOGICMEMSTA                                       0x00007170U

//HOLISTIC FSM
#define PRCM_AON_O_HOL                                               0x00007174U

//PSCON HANDLER GENERAL
#define PRCM_AON_O_PSCONHGEN                                         0x00007178U

//IO PROCESS BITS
#define PRCM_AON_O_IOPROCSBIT                                        0x0000717CU

//SLOW CLOCK COUNT CONTROL CORE
#define PRCM_AON_O_SCLKCNTCTLCR                                      0x00007180U

//STATUS CORE
#define PRCM_AON_O_STACR                                             0x00007184U

//AAON LOGIC CAPTURE
#define PRCM_AON_O_AAONLOGCAPT                                       0x0000718CU

//HOST WATCH DOG TIMER
#define PRCM_AON_O_HWDT                                              0x00007190U

//SLOW CLK COUNT CORE
#define PRCM_AON_O_SCLKCNTCR                                         0x00007194U

//SRAM LDO gen cfg register
#define PRCM_AON_O_SRAMLDO                                           0x00007198U

//DEBUG
#define PRCM_AON_O_DBG                                               0x0000719CU

//reset override control register, active low polarity:
#define PRCM_AON_O_RSTOVCTL                                          0x000071A0U

//PMU RESET CLEAR
#define PRCM_AON_O_PMURSTCLR                                         0x000071A4U

//MEMORY GROUP CONTROL CORE STATIC 1
#define PRCM_AON_O_MEMGCTLCRSTAT1                                    0x000071A8U

//MEMORY GROUP CONTROL CORE FLEX
#define PRCM_AON_O_MEMGCTLCRFLEX                                     0x000071ACU

//CORE SHARED
#define PRCM_AON_O_CRSH                                              0x000071B0U



/*-----------------------------------REGISTER------------------------------------
    Register name:       HFLXGRP
    Offset name:         PRCM_AON_O_HFLXGRP
    Relative address:    0x1034
    Description:         PSCON Memory Groups Control Host Flex.

                        Applicable only if MODE selected flex as HOST memory.
                        Bank power State When owner IP Active/Sleep (power domain is ON/OFF)

                        0 - OFF/OFF
                        1 - Reserved
                        2 - ON/OFF
                        3 - ON/RET
    Default Value:       0x000FFFFF

        Field:           PWRSTATE1
        From..to bits:   0...1
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 1

                         Group 1

*/
#define PRCM_AON_HFLXGRP_PWRSTATE1_W                                 2U
#define PRCM_AON_HFLXGRP_PWRSTATE1_M                                 0x00000003U
#define PRCM_AON_HFLXGRP_PWRSTATE1_S                                 0U
/*

        Field:           PWRSTATE2
        From..to bits:   2...3
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 2

                         Group 2

*/
#define PRCM_AON_HFLXGRP_PWRSTATE2_W                                 2U
#define PRCM_AON_HFLXGRP_PWRSTATE2_M                                 0x0000000CU
#define PRCM_AON_HFLXGRP_PWRSTATE2_S                                 2U
/*

        Field:           PWRSTATE3
        From..to bits:   4...5
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 3

                         Group 3

*/
#define PRCM_AON_HFLXGRP_PWRSTATE3_W                                 2U
#define PRCM_AON_HFLXGRP_PWRSTATE3_M                                 0x00000030U
#define PRCM_AON_HFLXGRP_PWRSTATE3_S                                 4U
/*

        Field:           PWRSTATE4
        From..to bits:   6...7
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 4

                         Group 4

*/
#define PRCM_AON_HFLXGRP_PWRSTATE4_W                                 2U
#define PRCM_AON_HFLXGRP_PWRSTATE4_M                                 0x000000C0U
#define PRCM_AON_HFLXGRP_PWRSTATE4_S                                 6U
/*

        Field:           PWRSTATE5
        From..to bits:   8...9
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 5

                         Group 5

*/
#define PRCM_AON_HFLXGRP_PWRSTATE5_W                                 2U
#define PRCM_AON_HFLXGRP_PWRSTATE5_M                                 0x00000300U
#define PRCM_AON_HFLXGRP_PWRSTATE5_S                                 8U
/*

        Field:           PWRSTATE6
        From..to bits:   10...11
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 6

                         Group 6

*/
#define PRCM_AON_HFLXGRP_PWRSTATE6_W                                 2U
#define PRCM_AON_HFLXGRP_PWRSTATE6_M                                 0x00000C00U
#define PRCM_AON_HFLXGRP_PWRSTATE6_S                                 10U
/*

        Field:           PWRSTATE7
        From..to bits:   12...13
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 7

                         Group 7

*/
#define PRCM_AON_HFLXGRP_PWRSTATE7_W                                 2U
#define PRCM_AON_HFLXGRP_PWRSTATE7_M                                 0x00003000U
#define PRCM_AON_HFLXGRP_PWRSTATE7_S                                 12U
/*

        Field:           PWRSTATE8
        From..to bits:   14...15
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 8

                         Group 8

*/
#define PRCM_AON_HFLXGRP_PWRSTATE8_W                                 2U
#define PRCM_AON_HFLXGRP_PWRSTATE8_M                                 0x0000C000U
#define PRCM_AON_HFLXGRP_PWRSTATE8_S                                 14U
/*

        Field:           PWRSTATE9
        From..to bits:   16...17
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 9

                         Group 9

*/
#define PRCM_AON_HFLXGRP_PWRSTATE9_W                                 2U
#define PRCM_AON_HFLXGRP_PWRSTATE9_M                                 0x00030000U
#define PRCM_AON_HFLXGRP_PWRSTATE9_S                                 16U
/*

        Field:           PWRSTATE10
        From..to bits:   18...19
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 10

                         Group 10

*/
#define PRCM_AON_HFLXGRP_PWRSTATE10_W                                2U
#define PRCM_AON_HFLXGRP_PWRSTATE10_M                                0x000C0000U
#define PRCM_AON_HFLXGRP_PWRSTATE10_S                                18U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HFLXGRPIND
    Offset name:         PRCM_AON_O_HFLXGRPIND
    Relative address:    0x1038
    Description:         PSCON Memory Groups Indication Host Flex

                        Applicable only if MODE selected flex as HOST memory.
                        Memory bank from this group is shared

                        1 - Shared
                        0 - Not Shared
    Default Value:       0x00000000

        Field:           ISSHARED1
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 1

                         Group 1

*/
#define PRCM_AON_HFLXGRPIND_ISSHARED1                                0x00000001U
#define PRCM_AON_HFLXGRPIND_ISSHARED1_M                              0x00000001U
#define PRCM_AON_HFLXGRPIND_ISSHARED1_S                              0U
/*

        Field:           ISSHARED2
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 2

                         Group 2

*/
#define PRCM_AON_HFLXGRPIND_ISSHARED2                                0x00000002U
#define PRCM_AON_HFLXGRPIND_ISSHARED2_M                              0x00000002U
#define PRCM_AON_HFLXGRPIND_ISSHARED2_S                              1U
/*

        Field:           ISSHARED3
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 3

                         Group 3

*/
#define PRCM_AON_HFLXGRPIND_ISSHARED3                                0x00000004U
#define PRCM_AON_HFLXGRPIND_ISSHARED3_M                              0x00000004U
#define PRCM_AON_HFLXGRPIND_ISSHARED3_S                              2U
/*

        Field:           ISSHARED4
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 4

                         Group 4

*/
#define PRCM_AON_HFLXGRPIND_ISSHARED4                                0x00000008U
#define PRCM_AON_HFLXGRPIND_ISSHARED4_M                              0x00000008U
#define PRCM_AON_HFLXGRPIND_ISSHARED4_S                              3U
/*

        Field:           ISSHARED5
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 5

                         Group 5

*/
#define PRCM_AON_HFLXGRPIND_ISSHARED5                                0x00000010U
#define PRCM_AON_HFLXGRPIND_ISSHARED5_M                              0x00000010U
#define PRCM_AON_HFLXGRPIND_ISSHARED5_S                              4U
/*

        Field:           ISSHARED6
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 6

                         Group 6

*/
#define PRCM_AON_HFLXGRPIND_ISSHARED6                                0x00000020U
#define PRCM_AON_HFLXGRPIND_ISSHARED6_M                              0x00000020U
#define PRCM_AON_HFLXGRPIND_ISSHARED6_S                              5U
/*

        Field:           ISSHARED7
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 7

                         Group 7

*/
#define PRCM_AON_HFLXGRPIND_ISSHARED7                                0x00000040U
#define PRCM_AON_HFLXGRPIND_ISSHARED7_M                              0x00000040U
#define PRCM_AON_HFLXGRPIND_ISSHARED7_S                              6U
/*

        Field:           ISSHARED8
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 8

                         Group 8

*/
#define PRCM_AON_HFLXGRPIND_ISSHARED8                                0x00000080U
#define PRCM_AON_HFLXGRPIND_ISSHARED8_M                              0x00000080U
#define PRCM_AON_HFLXGRPIND_ISSHARED8_S                              7U
/*

        Field:           ISSHARED9
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 9

                         Group 9

*/
#define PRCM_AON_HFLXGRPIND_ISSHARED9                                0x00000100U
#define PRCM_AON_HFLXGRPIND_ISSHARED9_M                              0x00000100U
#define PRCM_AON_HFLXGRPIND_ISSHARED9_S                              8U
/*

        Field:           ISSHARED10
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 10

                         Group 10

*/
#define PRCM_AON_HFLXGRPIND_ISSHARED10                               0x00000200U
#define PRCM_AON_HFLXGRPIND_ISSHARED10_M                             0x00000200U
#define PRCM_AON_HFLXGRPIND_ISSHARED10_S                             9U


/*-----------------------------------REGISTER------------------------------------
    Register name:       REFCTL
    Offset name:         PRCM_AON_O_REFCTL
    Relative address:    0x1048
    Description:         PSCON Memory Status Refresh
    Default Value:       0x00010000

        Field:           SETKICK
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Memory Host Set Refresh

                         write clear
                         triggers the refresh cycle.
                         first set all memories to desired status, then fire the "refresh" pulse

*/
#define PRCM_AON_REFCTL_SETKICK                                      0x00000001U
#define PRCM_AON_REFCTL_SETKICK_M                                    0x00000001U
#define PRCM_AON_REFCTL_SETKICK_S                                    0U
/*

        Field:           ENISO
        From..to bits:   16...16
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Enable ISO During Refresh

                         '1' - set ISO during refresh
                         '0' - don't set ISO

*/
#define PRCM_AON_REFCTL_ENISO                                        0x00010000U
#define PRCM_AON_REFCTL_ENISO_M                                      0x00010000U
#define PRCM_AON_REFCTL_ENISO_S                                      16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       REFSTA
    Offset name:         PRCM_AON_O_REFSTA
    Relative address:    0x104C
    Description:         Memory Refresh Status
    Default Value:       0x00000001

        Field:           DONE
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-only
        Description:     memories status refresh is done

*/
#define PRCM_AON_REFSTA_DONE                                         0x00000001U
#define PRCM_AON_REFSTA_DONE_M                                       0x00000001U
#define PRCM_AON_REFSTA_DONE_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HSTATICGRP
    Offset name:         PRCM_AON_O_HSTATICGRP
    Relative address:    0x1054
    Description:         PSCON Memory Groups Control Host Static.

                        Bank power State When owner IP Active/Sleep (power domain is ON/OFF)

                        0 - OFF/OFF
                        1 - Reserved
                        2 - ON/OFF
                        3 - ON/RET
    Default Value:       0x0BEEFFFF

        Field:           PWRSTAT1
        From..to bits:   0...1
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 1

                         Group 23

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT1_W                               2U
#define PRCM_AON_HSTATICGRP_PWRSTAT1_M                               0x00000003U
#define PRCM_AON_HSTATICGRP_PWRSTAT1_S                               0U
/*

        Field:           PWRSTAT2
        From..to bits:   2...3
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 2

                         Group 24

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT2_W                               2U
#define PRCM_AON_HSTATICGRP_PWRSTAT2_M                               0x0000000CU
#define PRCM_AON_HSTATICGRP_PWRSTAT2_S                               2U
/*

        Field:           PWRSTAT3
        From..to bits:   4...5
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 3

                         Group 25

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT3_W                               2U
#define PRCM_AON_HSTATICGRP_PWRSTAT3_M                               0x00000030U
#define PRCM_AON_HSTATICGRP_PWRSTAT3_S                               4U
/*

        Field:           PWRSTAT4
        From..to bits:   6...7
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 4

                         Group 26

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT4_W                               2U
#define PRCM_AON_HSTATICGRP_PWRSTAT4_M                               0x000000C0U
#define PRCM_AON_HSTATICGRP_PWRSTAT4_S                               6U
/*

        Field:           PWRSTAT5
        From..to bits:   8...9
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 5

                         Group 27

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT5_W                               2U
#define PRCM_AON_HSTATICGRP_PWRSTAT5_M                               0x00000300U
#define PRCM_AON_HSTATICGRP_PWRSTAT5_S                               8U
/*

        Field:           PWRSTAT6
        From..to bits:   10...11
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 6

                         Group 28

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT6_W                               2U
#define PRCM_AON_HSTATICGRP_PWRSTAT6_M                               0x00000C00U
#define PRCM_AON_HSTATICGRP_PWRSTAT6_S                               10U
/*

        Field:           PWRSTAT7
        From..to bits:   12...13
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 7

                         Group 29

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT7_W                               2U
#define PRCM_AON_HSTATICGRP_PWRSTAT7_M                               0x00003000U
#define PRCM_AON_HSTATICGRP_PWRSTAT7_S                               12U
/*

        Field:           PWRSTAT8
        From..to bits:   14...15
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 8

                         Group 30

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT8_W                               2U
#define PRCM_AON_HSTATICGRP_PWRSTAT8_M                               0x0000C000U
#define PRCM_AON_HSTATICGRP_PWRSTAT8_S                               14U
/*

        Field:           PWRSTAT9
        From..to bits:   16...17
        DefaultValue:    0x2
        Access type:     read-write
        Description:     POWER STATE 9

                         Group 31

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT9_W                               2U
#define PRCM_AON_HSTATICGRP_PWRSTAT9_M                               0x00030000U
#define PRCM_AON_HSTATICGRP_PWRSTAT9_S                               16U
/*

        Field:           PWRSTAT10
        From..to bits:   18...19
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 10

                         Group 32

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT10_W                              2U
#define PRCM_AON_HSTATICGRP_PWRSTAT10_M                              0x000C0000U
#define PRCM_AON_HSTATICGRP_PWRSTAT10_S                              18U
/*

        Field:           PWRSTAT11
        From..to bits:   20...21
        DefaultValue:    0x2
        Access type:     read-write
        Description:     POWER STATE 11

                         Group 33

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT11_W                              2U
#define PRCM_AON_HSTATICGRP_PWRSTAT11_M                              0x00300000U
#define PRCM_AON_HSTATICGRP_PWRSTAT11_S                              20U
/*

        Field:           PWRSTAT12
        From..to bits:   22...23
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 12

                         HIF Group 34  - being used as shared memory

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT12_W                              2U
#define PRCM_AON_HSTATICGRP_PWRSTAT12_M                              0x00C00000U
#define PRCM_AON_HSTATICGRP_PWRSTAT12_S                              22U
/*

        Field:           PWRSTAT13
        From..to bits:   24...25
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 13

                         Group 35

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT13_W                              2U
#define PRCM_AON_HSTATICGRP_PWRSTAT13_M                              0x03000000U
#define PRCM_AON_HSTATICGRP_PWRSTAT13_S                              24U
/*

        Field:           PWRSTAT14
        From..to bits:   26...27
        DefaultValue:    0x2
        Access type:     read-write
        Description:     POWER STATE 14

                         Group 36

*/
#define PRCM_AON_HSTATICGRP_PWRSTAT14_W                              2U
#define PRCM_AON_HSTATICGRP_PWRSTAT14_M                              0x0C000000U
#define PRCM_AON_HSTATICGRP_PWRSTAT14_S                              26U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HSTATICGRPIND
    Offset name:         PRCM_AON_O_HSTATICGRPIND
    Relative address:    0x1058
    Description:         Memory bank from this group is shared

                        1 - Shared
                        0 - Not Shared
    Default Value:       0x00000000

        Field:           ISSHARED1
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 1

                         Group 23

*/
#define PRCM_AON_HSTATICGRPIND_ISSHARED1                             0x00000001U
#define PRCM_AON_HSTATICGRPIND_ISSHARED1_M                           0x00000001U
#define PRCM_AON_HSTATICGRPIND_ISSHARED1_S                           0U
/*

        Field:           ISSHARED2
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 2

                         Group 24

*/
#define PRCM_AON_HSTATICGRPIND_ISSHARED2                             0x00000002U
#define PRCM_AON_HSTATICGRPIND_ISSHARED2_M                           0x00000002U
#define PRCM_AON_HSTATICGRPIND_ISSHARED2_S                           1U
/*

        Field:           ISSHARED3
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 3

                         Group 25

*/
#define PRCM_AON_HSTATICGRPIND_ISSHARED3                             0x00000004U
#define PRCM_AON_HSTATICGRPIND_ISSHARED3_M                           0x00000004U
#define PRCM_AON_HSTATICGRPIND_ISSHARED3_S                           2U
/*

        Field:           ISSHARED4
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS SHARED 4

                         Group 26

*/
#define PRCM_AON_HSTATICGRPIND_ISSHARED4                             0x00000008U
#define PRCM_AON_HSTATICGRPIND_ISSHARED4_M                           0x00000008U
#define PRCM_AON_HSTATICGRPIND_ISSHARED4_S                           3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LOGHMEMSTA
    Offset name:         PRCM_AON_O_LOGHMEMSTA
    Relative address:    0x105C
    Description:         Logic Host Memory Status
    Default Value:       0x00000000

        Field:           AONIN
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Host Memory AONIN indication

*/
#define PRCM_AON_LOGHMEMSTA_AONIN_W                                  14U
#define PRCM_AON_LOGHMEMSTA_AONIN_M                                  0x00003FFFU
#define PRCM_AON_LOGHMEMSTA_AONIN_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CONNSTP
    Offset name:         PRCM_AON_O_CONNSTP
    Relative address:    0x1060
    Description:         Connectivity Stop
    Default Value:       0x00000001

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     '1' - Connectivity Stop
                         '0' - Connectivity Start

*/
#define PRCM_AON_CONNSTP_SET                                         0x00000001U
#define PRCM_AON_CONNSTP_SET_M                                       0x00000001U
#define PRCM_AON_CONNSTP_SET_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HRSTOV
    Offset name:         PRCM_AON_O_HRSTOV
    Relative address:    0x1064
    Description:         HOST RESET OV CONTROL

                        reset override control register, active low polarity:
                        '0' - override reset (force reset line to 0, reset asserted, active low)
                        '1' - don't override reset
    Default Value:       0x00000000

        Field:           PULSE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     PULSE

                         write clear

*/
#define PRCM_AON_HRSTOV_PULSE                                        0x00000001U
#define PRCM_AON_HRSTOV_PULSE_M                                      0x00000001U
#define PRCM_AON_HRSTOV_PULSE_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SLPDEEP
    Offset name:         PRCM_AON_O_SLPDEEP
    Relative address:    0x1068
    Description:         The register holds sleepdeep command for the host_mcu for debugging
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Set this field to force HOST deepsleep.
                         It will cleared by HW when [HSLPIND] is '1'.

*/
#define PRCM_AON_SLPDEEP_SET                                         0x00000001U
#define PRCM_AON_SLPDEEP_SET_M                                       0x00000001U
#define PRCM_AON_SLPDEEP_SET_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SHPRECISE
    Offset name:         PRCM_AON_O_SHPRECISE
    Relative address:    0x2000
    Description:         SHARED PRECISE

                        override values for PRCM SHARED Modules
    Default Value:       0x00000000

        Field:           PMSFREFPU
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PMS FREF PLL UP

                         SET precise duration for CORE PRCM Shared UP - factor 4 slow CLK resolution
                         0 - 1 Slow CLKs
                         1 - 5 Slow CLKs
                         2 - 9 Slow CLKs
                         3 - 13 Slow CLKs
                         ...
                         127 - 509 Slow CLKs

*/
#define PRCM_AON_SHPRECISE_PMSFREFPU_W                               7U
#define PRCM_AON_SHPRECISE_PMSFREFPU_M                               0x0000007FU
#define PRCM_AON_SHPRECISE_PMSFREFPU_S                               0U
/*

        Field:           COREPDU
        From..to bits:   8...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CORE POWER DOMAIN UP

                         SET precise duration for CORE Power Domain UP - factor 4 slow CLK resolution
                         0 - 1 Slow CLKs
                         1 - 5 Slow CLKs
                         2 - 9 Slow CLKs
                         3 - 13 Slow CLKs
                         ...
                         127 - 509 Slow CLKs

*/
#define PRCM_AON_SHPRECISE_COREPDU_W                                 7U
#define PRCM_AON_SHPRECISE_COREPDU_M                                 0x00007F00U
#define PRCM_AON_SHPRECISE_COREPDU_S                                 8U
/*

        Field:           HOSTPDU
        From..to bits:   16...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HOST POWER DOMAIN UP

                         SET precise duration for HOST Power Domain UP - factor 4 slow CLK resolution
                         0 - 1 Slow CLKs
                         1 - 5 Slow CLKs
                         2 - 9 Slow CLKs
                         3 - 13 Slow CLKs
                         ...
                         127 - 509 Slow CLKs

*/
#define PRCM_AON_SHPRECISE_HOSTPDU_W                                 7U
#define PRCM_AON_SHPRECISE_HOSTPDU_M                                 0x007F0000U
#define PRCM_AON_SHPRECISE_HOSTPDU_S                                 16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFXTCTL
    Offset name:         PRCM_AON_O_LFXTCTL
    Relative address:    0x2008
    Description:         LFXT CONTROL
    Default Value:       0x00000000

        Field:           OSCEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Oscillator core enable

*/
#define PRCM_AON_LFXTCTL_OSCEN                                       0x00000001U
#define PRCM_AON_LFXTCTL_OSCEN_M                                     0x00000001U
#define PRCM_AON_LFXTCTL_OSCEN_S                                     0U
/*

        Field:           IBIASEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable constant-gm bias

*/
#define PRCM_AON_LFXTCTL_IBIASEN                                     0x00000002U
#define PRCM_AON_LFXTCTL_IBIASEN_M                                   0x00000002U
#define PRCM_AON_LFXTCTL_IBIASEN_S                                   1U
/*

        Field:           CPHPMODEN
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     COMP HP MODE EN

                         Comparator high current mode

*/
#define PRCM_AON_LFXTCTL_CPHPMODEN                                   0x00000004U
#define PRCM_AON_LFXTCTL_CPHPMODEN_M                                 0x00000004U
#define PRCM_AON_LFXTCTL_CPHPMODEN_S                                 2U
/*

        Field:           CPEN
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Comparator (slicer) enable

*/
#define PRCM_AON_LFXTCTL_CPEN                                        0x00000008U
#define PRCM_AON_LFXTCTL_CPEN_M                                      0x00000008U
#define PRCM_AON_LFXTCTL_CPEN_S                                      3U
/*

        Field:           BYPASS
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Bypass LFXT

*/
#define PRCM_AON_LFXTCTL_BYPASS                                      0x00000010U
#define PRCM_AON_LFXTCTL_BYPASS_M                                    0x00000010U
#define PRCM_AON_LFXTCTL_BYPASS_S                                    4U
/*

        Field:           BOOSTMODE
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     BOOST MODE

                         Start-up pulse for bias current generation

*/
#define PRCM_AON_LFXTCTL_BOOSTMODE                                   0x00000020U
#define PRCM_AON_LFXTCTL_BOOSTMODE_M                                 0x00000020U
#define PRCM_AON_LFXTCTL_BOOSTMODE_S                                 5U
/*

        Field:           AMPREGEN
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AMPLITUDE REGULATION ENABLE

                         Enable amplitude regulation

*/
#define PRCM_AON_LFXTCTL_AMPREGEN                                    0x00000040U
#define PRCM_AON_LFXTCTL_AMPREGEN_M                                  0x00000040U
#define PRCM_AON_LFXTCTL_AMPREGEN_S                                  6U
/*

        Field:           IBIASITRIM
        From..to bits:   7...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IBIAS ITRIM

                         Constant gm bias current trim

*/
#define PRCM_AON_LFXTCTL_IBIASITRIM_W                                5U
#define PRCM_AON_LFXTCTL_IBIASITRIM_M                                0x00000F80U
#define PRCM_AON_LFXTCTL_IBIASITRIM_S                                7U
/*

        Field:           AMPREGRTRIM
        From..to bits:   12...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AMPLITUDE REGULATION RESISTOR TRIM

                         Amplitude regulation resistor ladder trim

*/
#define PRCM_AON_LFXTCTL_AMPREGRTRIM_W                               5U
#define PRCM_AON_LFXTCTL_AMPREGRTRIM_M                               0x0001F000U
#define PRCM_AON_LFXTCTL_AMPREGRTRIM_S                               12U
/*

        Field:           IBIASRTRIM
        From..to bits:   17...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IBIAS RTRIM

                         Constant gm bias resistor ladder trim

*/
#define PRCM_AON_LFXTCTL_IBIASRTRIM_W                                5U
#define PRCM_AON_LFXTCTL_IBIASRTRIM_M                                0x003E0000U
#define PRCM_AON_LFXTCTL_IBIASRTRIM_S                                17U
/*

        Field:           AMPREGITRIM
        From..to bits:   22...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AMPLITUDE REGULATION CURRENT TRIM

                         Amplitude regulation current trim

*/
#define PRCM_AON_LFXTCTL_AMPREGITRIM_W                               5U
#define PRCM_AON_LFXTCTL_AMPREGITRIM_M                               0x07C00000U
#define PRCM_AON_LFXTCTL_AMPREGITRIM_S                               22U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFXTSPARE
    Offset name:         PRCM_AON_O_LFXTSPARE
    Relative address:    0x200C
    Description:         LFXT SPARE
    Default Value:       0x00000000

        Field:           CTL
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CTL

                         lfxt spare reg

*/
#define PRCM_AON_LFXTSPARE_CTL_W                                     16U
#define PRCM_AON_LFXTSPARE_CTL_M                                     0x0000FFFFU
#define PRCM_AON_LFXTSPARE_CTL_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFOSCEN
    Offset name:         PRCM_AON_O_LFOSCEN
    Relative address:    0x2010
    Description:         LFOSC ENABLE
    Default Value:       0x00000000

        Field:           GOOD
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CLK GOOD

                         LFOSC clock good indication based on clock qualification logic

*/
#define PRCM_AON_LFOSCEN_GOOD                                        0x00000001U
#define PRCM_AON_LFOSCEN_GOOD_M                                      0x00000001U
#define PRCM_AON_LFOSCEN_GOOD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSEDATA5
    Offset name:         PRCM_AON_O_FUSEDATA5
    Relative address:    0x2014
    Description:         FUSE DATA 5
    Default Value:       0x00000000

        Field:           DEVX
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVX

*/
#define PRCM_AON_FUSEDATA5_DEVX_W                                    12U
#define PRCM_AON_FUSEDATA5_DEVX_M                                    0x00000FFFU
#define PRCM_AON_FUSEDATA5_DEVX_S                                    0U
/*

        Field:           DEVY
        From..to bits:   12...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVY

*/
#define PRCM_AON_FUSEDATA5_DEVY_W                                    12U
#define PRCM_AON_FUSEDATA5_DEVY_M                                    0x00FFF000U
#define PRCM_AON_FUSEDATA5_DEVY_S                                    12U
/*

        Field:           DEVWAF
        From..to bits:   24...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVWAF

*/
#define PRCM_AON_FUSEDATA5_DEVWAF_W                                  6U
#define PRCM_AON_FUSEDATA5_DEVWAF_M                                  0x3F000000U
#define PRCM_AON_FUSEDATA5_DEVWAF_S                                  24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSEDATA6
    Offset name:         PRCM_AON_O_FUSEDATA6
    Relative address:    0x2018
    Description:         FUSE DATA 6
    Default Value:       0x00000000

        Field:           DEVLOT
        From..to bits:   0...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVLOT

*/
#define PRCM_AON_FUSEDATA6_DEVLOT_W                                  24U
#define PRCM_AON_FUSEDATA6_DEVLOT_M                                  0x00FFFFFFU
#define PRCM_AON_FUSEDATA6_DEVLOT_S                                  0U
/*

        Field:           DEVFAB
        From..to bits:   24...28
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVFAB

*/
#define PRCM_AON_FUSEDATA6_DEVFAB_W                                  5U
#define PRCM_AON_FUSEDATA6_DEVFAB_M                                  0x1F000000U
#define PRCM_AON_FUSEDATA6_DEVFAB_S                                  24U
/*

        Field:           DEVFABBE
        From..to bits:   29...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVFABBE

*/
#define PRCM_AON_FUSEDATA6_DEVFABBE_W                                3U
#define PRCM_AON_FUSEDATA6_DEVFABBE_M                                0xE0000000U
#define PRCM_AON_FUSEDATA6_DEVFABBE_S                                29U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSEDATA7
    Offset name:         PRCM_AON_O_FUSEDATA7
    Relative address:    0x201C
    Description:         FUSE DATA 7
    Default Value:       0x00000000

        Field:           DBGCURVE1
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG CURVE 1St INSERTION
                         For the first insertion.
                         This field is used for trimming at boot after shift done.

*/
#define PRCM_AON_FUSEDATA7_DBGCURVE1_W                               7U
#define PRCM_AON_FUSEDATA7_DBGCURVE1_M                               0x0000007FU
#define PRCM_AON_FUSEDATA7_DBGCURVE1_S                               0U
/*

        Field:           DBGMAG1
        From..to bits:   7...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG MAG 1ST INSERTION
                         For the first insertion.
                         This field is used for trimming at boot after shift done.

*/
#define PRCM_AON_FUSEDATA7_DBGMAG1_W                                 8U
#define PRCM_AON_FUSEDATA7_DBGMAG1_M                                 0x00007F80U
#define PRCM_AON_FUSEDATA7_DBGMAG1_S                                 7U
/*

        Field:           DBGRTRIM1
        From..to bits:   15...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG RTRIM 1ST INSERTION
                         For the first insertion.
                         This field is used for trimming at boot after shift done.

*/
#define PRCM_AON_FUSEDATA7_DBGRTRIM1_W                               5U
#define PRCM_AON_FUSEDATA7_DBGRTRIM1_M                               0x000F8000U
#define PRCM_AON_FUSEDATA7_DBGRTRIM1_S                               15U
/*

        Field:           DBGGMI1
        From..to bits:   20...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG GMI 1ST INSERTION
                         For the first insertion.
                         This field is used for trimming at boot after shift done.

*/
#define PRCM_AON_FUSEDATA7_DBGGMI1_W                                 5U
#define PRCM_AON_FUSEDATA7_DBGGMI1_M                                 0x01F00000U
#define PRCM_AON_FUSEDATA7_DBGGMI1_S                                 20U
/*

        Field:           PMCTEMPSNS1
        From..to bits:   25...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     PMCIO TEMP SENSOR 1ST INSERTION
                         For the first insertion.

*/
#define PRCM_AON_FUSEDATA7_PMCTEMPSNS1_W                             7U
#define PRCM_AON_FUSEDATA7_PMCTEMPSNS1_M                             0xFE000000U
#define PRCM_AON_FUSEDATA7_PMCTEMPSNS1_S                             25U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSEDATA8
    Offset name:         PRCM_AON_O_FUSEDATA8
    Relative address:    0x2020
    Description:         FUSE DATA 8
    Default Value:       0x00000000

        Field:           DEVDESREV
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVDesREV

*/
#define PRCM_AON_FUSEDATA8_DEVDESREV_W                               5U
#define PRCM_AON_FUSEDATA8_DEVDESREV_M                               0x0000001FU
#define PRCM_AON_FUSEDATA8_DEVDESREV_S                               0U
/*

        Field:           MEMREPAIR
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     memrepair

*/
#define PRCM_AON_FUSEDATA8_MEMREPAIR                                 0x00000020U
#define PRCM_AON_FUSEDATA8_MEMREPAIR_M                               0x00000020U
#define PRCM_AON_FUSEDATA8_MEMREPAIR_S                               5U
/*

        Field:           MKDASHDEF
        From..to bits:   6...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Make-defined

*/
#define PRCM_AON_FUSEDATA8_MKDASHDEF_W                               11U
#define PRCM_AON_FUSEDATA8_MKDASHDEF_M                               0x0001FFC0U
#define PRCM_AON_FUSEDATA8_MKDASHDEF_S                               6U
/*

        Field:           CHECKSUM
        From..to bits:   17...30
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Checksum_TI_ DIEID_FUSE_DATA_5_6_8

*/
#define PRCM_AON_FUSEDATA8_CHECKSUM_W                                14U
#define PRCM_AON_FUSEDATA8_CHECKSUM_M                                0x7FFE0000U
#define PRCM_AON_FUSEDATA8_CHECKSUM_S                                17U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSEDATA9
    Offset name:         PRCM_AON_O_FUSEDATA9
    Relative address:    0x2024
    Description:         FUSE DATA 9
    Default Value:       0x00000000

        Field:           DBGCURVE2
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG CURVE 2ND INSERTION

                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_FUSEDATA9_DBGCURVE2_W                               7U
#define PRCM_AON_FUSEDATA9_DBGCURVE2_M                               0x0000007FU
#define PRCM_AON_FUSEDATA9_DBGCURVE2_S                               0U
/*

        Field:           DBGMAG2
        From..to bits:   7...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG MAG 2ND INSERTION

                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_FUSEDATA9_DBGMAG2_W                                 8U
#define PRCM_AON_FUSEDATA9_DBGMAG2_M                                 0x00007F80U
#define PRCM_AON_FUSEDATA9_DBGMAG2_S                                 7U
/*

        Field:           DBGRTRIM2
        From..to bits:   15...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG RTRIM 2ND INSERTION

                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_FUSEDATA9_DBGRTRIM2_W                               5U
#define PRCM_AON_FUSEDATA9_DBGRTRIM2_M                               0x000F8000U
#define PRCM_AON_FUSEDATA9_DBGRTRIM2_S                               15U
/*

        Field:           DBGGMI2
        From..to bits:   20...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG GMI 2ND INSERTION
                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_FUSEDATA9_DBGGMI2_W                                 5U
#define PRCM_AON_FUSEDATA9_DBGGMI2_M                                 0x01F00000U
#define PRCM_AON_FUSEDATA9_DBGGMI2_S                                 20U
/*

        Field:           PMCTEMPSNS2
        From..to bits:   25...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     PMCIO TEMP SENSOR 2ND INSERTION

                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_FUSEDATA9_PMCTEMPSNS2_W                             7U
#define PRCM_AON_FUSEDATA9_PMCTEMPSNS2_M                             0xFE000000U
#define PRCM_AON_FUSEDATA9_PMCTEMPSNS2_S                             25U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSEDATA10
    Offset name:         PRCM_AON_O_FUSEDATA10
    Relative address:    0x2028
    Description:         FUSE DATA 10
    Default Value:       0x00000000

        Field:           LOWRVMTRIM
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Low Digital Supply RVM Trimming

*/
#define PRCM_AON_FUSEDATA10_LOWRVMTRIM_W                             7U
#define PRCM_AON_FUSEDATA10_LOWRVMTRIM_M                             0x0000007FU
#define PRCM_AON_FUSEDATA10_LOWRVMTRIM_S                             0U
/*

        Field:           HIRVMTRIM
        From..to bits:   7...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     High Digital Supply RVM Trimming

*/
#define PRCM_AON_FUSEDATA10_HIRVMTRIM_W                              6U
#define PRCM_AON_FUSEDATA10_HIRVMTRIM_M                              0x00001F80U
#define PRCM_AON_FUSEDATA10_HIRVMTRIM_S                              7U
/*

        Field:           ENLOWRVMPROT
        From..to bits:   13...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Enable Low RVM protection (Specify whether to use the indication from RVM to reset the device).
                         The RVM Enable can be override by SW (Boot RAM/Privilege mode).
                         0 - Disable (Ignore indication from RVM)
                         Other (1-7) - Enable (Do not ignore indication from RVM)

*/
#define PRCM_AON_FUSEDATA10_ENLOWRVMPROT_W                           3U
#define PRCM_AON_FUSEDATA10_ENLOWRVMPROT_M                           0x0000E000U
#define PRCM_AON_FUSEDATA10_ENLOWRVMPROT_S                           13U
/*

        Field:           ENHIRVMPROTECT
        From..to bits:   16...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Enable High RVM protection (Specify whether to use the indication from RVM to reset the device).
                         The RVM Enable can be override by SW (Boot RAM/Privilege mode).
                         0 - Disable (Ignore indication from RVM)
                         Other (1-7) - Enable (Do not ignore indication from RVM)
                         Consider Splitting the enables (including CRC)

*/
#define PRCM_AON_FUSEDATA10_ENHIRVMPROTECT_W                         3U
#define PRCM_AON_FUSEDATA10_ENHIRVMPROTECT_M                         0x00070000U
#define PRCM_AON_FUSEDATA10_ENHIRVMPROTECT_S                         16U
/*

        Field:           I2VCIRCUIT
        From..to bits:   19...25
        DefaultValue:    0x0
        Access type:     read-only
        Description:     I2V Circuit (Measure Current using GPADC)

*/
#define PRCM_AON_FUSEDATA10_I2VCIRCUIT_W                             7U
#define PRCM_AON_FUSEDATA10_I2VCIRCUIT_M                             0x03F80000U
#define PRCM_AON_FUSEDATA10_I2VCIRCUIT_S                             19U
/*

        Field:           BROWNOUTTRIM
        From..to bits:   26...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Brownout Trims

*/
#define PRCM_AON_FUSEDATA10_BROWNOUTTRIM_W                           6U
#define PRCM_AON_FUSEDATA10_BROWNOUTTRIM_M                           0xFC000000U
#define PRCM_AON_FUSEDATA10_BROWNOUTTRIM_S                           26U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSEDATA11
    Offset name:         PRCM_AON_O_FUSEDATA11
    Relative address:    0x202C
    Description:         FUSE DATA 11
    Default Value:       0x00000000

        Field:           ABGAPTEMP1
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ANABGAP TEMP 1ST INSERTION Trimming.

                         For the first insertion.
                         This field is used for trimming at boot after shift done.

*/
#define PRCM_AON_FUSEDATA11_ABGAPTEMP1_W                             5U
#define PRCM_AON_FUSEDATA11_ABGAPTEMP1_M                             0x0000001FU
#define PRCM_AON_FUSEDATA11_ABGAPTEMP1_S                             0U
/*

        Field:           ABGAPMAG1
        From..to bits:   6...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ANA BGAP MAG 1St INSERTION
                         For the first insertion.
                         This field is used for trimming at boot after shift done.

*/
#define PRCM_AON_FUSEDATA11_ABGAPMAG1_W                              5U
#define PRCM_AON_FUSEDATA11_ABGAPMAG1_M                              0x000007C0U
#define PRCM_AON_FUSEDATA11_ABGAPMAG1_S                              6U
/*

        Field:           ABGAPTEMP2
        From..to bits:   11...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ANABGAP TEMP 2ND INSERTION Trimming.
                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_FUSEDATA11_ABGAPTEMP2_W                             5U
#define PRCM_AON_FUSEDATA11_ABGAPTEMP2_M                             0x0000F800U
#define PRCM_AON_FUSEDATA11_ABGAPTEMP2_S                             11U
/*

        Field:           ABGAPMAG2
        From..to bits:   17...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ANA BGAP MAG 2ND INSERTION
                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_FUSEDATA11_ABGAPMAG2_W                              5U
#define PRCM_AON_FUSEDATA11_ABGAPMAG2_M                              0x003E0000U
#define PRCM_AON_FUSEDATA11_ABGAPMAG2_S                              17U
/*

        Field:           ABGRTRIM
        From..to bits:   22...25
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ANA BG RTRIM

                         This field is calculated bases on the 'RF_NWELL_Efuse' trimming results
                         ANABG RTRIM (REFSYS_REG0<9:6>)

*/
#define PRCM_AON_FUSEDATA11_ABGRTRIM_W                               4U
#define PRCM_AON_FUSEDATA11_ABGRTRIM_M                               0x03C00000U
#define PRCM_AON_FUSEDATA11_ABGRTRIM_S                               22U
/*

        Field:           RFNWELL
        From..to bits:   26...30
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RF NWELL

                         Will be used to calculate during production the PMREF_V2I_RTRIM - Reference current to the RFCIO RX/TX modules
                         (Can be part of OCP\, Not used in cold boot)

*/
#define PRCM_AON_FUSEDATA11_RFNWELL_W                                5U
#define PRCM_AON_FUSEDATA11_RFNWELL_M                                0x7C000000U
#define PRCM_AON_FUSEDATA11_RFNWELL_S                                26U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSEDATA12
    Offset name:         PRCM_AON_O_FUSEDATA12
    Relative address:    0x2030
    Description:         FUSE DATA 12
    Default Value:       0x00000000

        Field:           DELTATEMP12
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DELTA TEMP 1ST 2ND INSERTIONS

                         Defines the delta temperature between the 1st and 2nd insertion in degC

*/
#define PRCM_AON_FUSEDATA12_DELTATEMP12_W                            8U
#define PRCM_AON_FUSEDATA12_DELTATEMP12_M                            0x000000FFU
#define PRCM_AON_FUSEDATA12_DELTATEMP12_S                            0U
/*

        Field:           LFOSCRESTRIM
        From..to bits:   8...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LFOSC Resistor Trimming

*/
#define PRCM_AON_FUSEDATA12_LFOSCRESTRIM_W                           7U
#define PRCM_AON_FUSEDATA12_LFOSCRESTRIM_M                           0x00007F00U
#define PRCM_AON_FUSEDATA12_LFOSCRESTRIM_S                           8U
/*

        Field:           LFOSCFSEL
        From..to bits:   15...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LFOSC Frequency Trimming

*/
#define PRCM_AON_FUSEDATA12_LFOSCFSEL_W                              2U
#define PRCM_AON_FUSEDATA12_LFOSCFSEL_M                              0x00018000U
#define PRCM_AON_FUSEDATA12_LFOSCFSEL_S                              15U
/*

        Field:           BROWNOUTEN
        From..to bits:   17...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Brownout Enable/Disable:
                         0 - Disable
                         Other (1-7) - Enable
                         (When HW check these bits: if equal to '0' disable  otherwise enable)

*/
#define PRCM_AON_FUSEDATA12_BROWNOUTEN_W                             3U
#define PRCM_AON_FUSEDATA12_BROWNOUTEN_M                             0x000E0000U
#define PRCM_AON_FUSEDATA12_BROWNOUTEN_S                             17U
/*

        Field:           IOPMOS
        From..to bits:   26...28
        DefaultValue:    0x0
        Access type:     read-only
        Description:     IO PMOS

*/
#define PRCM_AON_FUSEDATA12_IOPMOS_W                                 3U
#define PRCM_AON_FUSEDATA12_IOPMOS_M                                 0x1C000000U
#define PRCM_AON_FUSEDATA12_IOPMOS_S                                 26U
/*

        Field:           IONMOS
        From..to bits:   29...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     IO NMOS

*/
#define PRCM_AON_FUSEDATA12_IONMOS_W                                 3U
#define PRCM_AON_FUSEDATA12_IONMOS_M                                 0xE0000000U
#define PRCM_AON_FUSEDATA12_IONMOS_S                                 29U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSEDATA13
    Offset name:         PRCM_AON_O_FUSEDATA13
    Relative address:    0x2034
    Description:         FUSE DATA 13
    Default Value:       0x00000000

        Field:           CRNMOSRFCODP
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CORE NMOS RFCIO ODP

*/
#define PRCM_AON_FUSEDATA13_CRNMOSRFCODP_W                           4U
#define PRCM_AON_FUSEDATA13_CRNMOSRFCODP_M                           0x0000000FU
#define PRCM_AON_FUSEDATA13_CRNMOSRFCODP_S                           0U
/*

        Field:           AFNMOSRFCODP
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AF NMOS RFCIO ODP

*/
#define PRCM_AON_FUSEDATA13_AFNMOSRFCODP_W                           4U
#define PRCM_AON_FUSEDATA13_AFNMOSRFCODP_M                           0x000000F0U
#define PRCM_AON_FUSEDATA13_AFNMOSRFCODP_S                           4U
/*

        Field:           CRPMOSRFCODP
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CORE PMOS RFCIO ODP

*/
#define PRCM_AON_FUSEDATA13_CRPMOSRFCODP_W                           4U
#define PRCM_AON_FUSEDATA13_CRPMOSRFCODP_M                           0x00000F00U
#define PRCM_AON_FUSEDATA13_CRPMOSRFCODP_S                           8U
/*

        Field:           AFPMOSRFCODP
        From..to bits:   12...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AF PMOS RFCIO ODP

*/
#define PRCM_AON_FUSEDATA13_AFPMOSRFCODP_W                           4U
#define PRCM_AON_FUSEDATA13_AFPMOSRFCODP_M                           0x0000F000U
#define PRCM_AON_FUSEDATA13_AFPMOSRFCODP_S                           12U
/*

        Field:           COREPMOS
        From..to bits:   16...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CORE PMOS SOC ODP

*/
#define PRCM_AON_FUSEDATA13_COREPMOS_W                               3U
#define PRCM_AON_FUSEDATA13_COREPMOS_M                               0x00070000U
#define PRCM_AON_FUSEDATA13_COREPMOS_S                               16U
/*

        Field:           CORENMOS
        From..to bits:   19...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CORE NMOS SOC ODP

*/
#define PRCM_AON_FUSEDATA13_CORENMOS_W                               3U
#define PRCM_AON_FUSEDATA13_CORENMOS_M                               0x00380000U
#define PRCM_AON_FUSEDATA13_CORENMOS_S                               19U
/*

        Field:           BYPASSPLL
        From..to bits:   22...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bypass SoC PLL

                         Other (0-6) - Do not bypass SoC PLL
                         7 - Bypass SoC PLL

*/
#define PRCM_AON_FUSEDATA13_BYPASSPLL_W                              3U
#define PRCM_AON_FUSEDATA13_BYPASSPLL_M                              0x01C00000U
#define PRCM_AON_FUSEDATA13_BYPASSPLL_S                              22U
/*

        Field:           GPADCOFFSET
        From..to bits:   25...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     GPADC OFFSET

                         Capture the offset error of the GPADC

*/
#define PRCM_AON_FUSEDATA13_GPADCOFFSET_W                            7U
#define PRCM_AON_FUSEDATA13_GPADCOFFSET_M                            0xFE000000U
#define PRCM_AON_FUSEDATA13_GPADCOFFSET_S                            25U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSEDATA14
    Offset name:         PRCM_AON_O_FUSEDATA14
    Relative address:    0x2038
    Description:         FUSE DATA 14
    Default Value:       0x00000000

        Field:           CLKMRTRIM
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CLKM RTRIM

                         This field is calculated base on the 'RF_NWELL_Efuse ' trimming results
                         (CKM_SLICER_REG0<4:0>)

*/
#define PRCM_AON_FUSEDATA14_CLKMRTRIM_W                              5U
#define PRCM_AON_FUSEDATA14_CLKMRTRIM_M                              0x0000001FU
#define PRCM_AON_FUSEDATA14_CLKMRTRIM_S                              0U
/*

        Field:           XTITRIMCTRL
        From..to bits:   5...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     XTAL ITRIM control (CKM_OSC_REG0<6:1>)

*/
#define PRCM_AON_FUSEDATA14_XTITRIMCTRL_W                            6U
#define PRCM_AON_FUSEDATA14_XTITRIMCTRL_M                            0x000007E0U
#define PRCM_AON_FUSEDATA14_XTITRIMCTRL_S                            5U
/*

        Field:           SLITRIMCTRL
        From..to bits:   11...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Slicer ITRIM Control (CKM_SLICER_REG0<7:5>)

*/
#define PRCM_AON_FUSEDATA14_SLITRIMCTRL_W                            3U
#define PRCM_AON_FUSEDATA14_SLITRIMCTRL_M                            0x00003800U
#define PRCM_AON_FUSEDATA14_SLITRIMCTRL_S                            11U
/*

        Field:           PALDOMON
        From..to bits:   14...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     PA LDO IN MONITOR

                         PA LDO In ('Battery') Sensor Trimming for 3V

*/
#define PRCM_AON_FUSEDATA14_PALDOMON_W                               5U
#define PRCM_AON_FUSEDATA14_PALDOMON_M                               0x0007C000U
#define PRCM_AON_FUSEDATA14_PALDOMON_S                               14U
/*

        Field:           SOCPROCES
        From..to bits:   19...20
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SOC PROCESS

                         The value is calculated based on Core PMOS/NMOS (SoC ODP)
                         2b'00 - Nominal
                         2b'01 - Weak
                         2b'10 - Strong

*/
#define PRCM_AON_FUSEDATA14_SOCPROCES_W                              2U
#define PRCM_AON_FUSEDATA14_SOCPROCES_M                              0x00180000U
#define PRCM_AON_FUSEDATA14_SOCPROCES_S                              19U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRCMRAWFS0
    Offset name:         PRCM_AON_O_PRCMRAWFS0
    Relative address:    0x203C
    Description:         PRCM RAW FUSE 0

                        fuse line 5
    Default Value:       0x00000000

        Field:           DEVX
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVX

*/
#define PRCM_AON_PRCMRAWFS0_DEVX_W                                   12U
#define PRCM_AON_PRCMRAWFS0_DEVX_M                                   0x00000FFFU
#define PRCM_AON_PRCMRAWFS0_DEVX_S                                   0U
/*

        Field:           DEVY
        From..to bits:   12...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVY

*/
#define PRCM_AON_PRCMRAWFS0_DEVY_W                                   12U
#define PRCM_AON_PRCMRAWFS0_DEVY_M                                   0x00FFF000U
#define PRCM_AON_PRCMRAWFS0_DEVY_S                                   12U
/*

        Field:           DEVWAF
        From..to bits:   24...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVWAF

*/
#define PRCM_AON_PRCMRAWFS0_DEVWAF_W                                 6U
#define PRCM_AON_PRCMRAWFS0_DEVWAF_M                                 0x3F000000U
#define PRCM_AON_PRCMRAWFS0_DEVWAF_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRCMRAWFS1
    Offset name:         PRCM_AON_O_PRCMRAWFS1
    Relative address:    0x2040
    Description:         PRCM RAW FUSE 1

                        fuse line 6
    Default Value:       0x00000000

        Field:           DEVLOT
        From..to bits:   0...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVLOT

*/
#define PRCM_AON_PRCMRAWFS1_DEVLOT_W                                 24U
#define PRCM_AON_PRCMRAWFS1_DEVLOT_M                                 0x00FFFFFFU
#define PRCM_AON_PRCMRAWFS1_DEVLOT_S                                 0U
/*

        Field:           DEVFAB
        From..to bits:   24...28
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVFAB

*/
#define PRCM_AON_PRCMRAWFS1_DEVFAB_W                                 5U
#define PRCM_AON_PRCMRAWFS1_DEVFAB_M                                 0x1F000000U
#define PRCM_AON_PRCMRAWFS1_DEVFAB_S                                 24U
/*

        Field:           DEVFABBE
        From..to bits:   29...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVFABBE

*/
#define PRCM_AON_PRCMRAWFS1_DEVFABBE_W                               3U
#define PRCM_AON_PRCMRAWFS1_DEVFABBE_M                               0xE0000000U
#define PRCM_AON_PRCMRAWFS1_DEVFABBE_S                               29U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRCMRAWFS2
    Offset name:         PRCM_AON_O_PRCMRAWFS2
    Relative address:    0x2044
    Description:         PRCM RAW FUSE 2

                        fuse line 7
    Default Value:       0x00000000

        Field:           DIGBGCURVE1
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG CURVE 1ST INSERTION
                         For the first insertion.
                         This field is used for trimming at boot after shift done.

*/
#define PRCM_AON_PRCMRAWFS2_DIGBGCURVE1_W                            7U
#define PRCM_AON_PRCMRAWFS2_DIGBGCURVE1_M                            0x0000007FU
#define PRCM_AON_PRCMRAWFS2_DIGBGCURVE1_S                            0U
/*

        Field:           DIGBGMAG1
        From..to bits:   7...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG MAG 1ST INSERTION
                         For the first insertion.
                         This field is used for trimming at boot after shift done.

*/
#define PRCM_AON_PRCMRAWFS2_DIGBGMAG1_W                              8U
#define PRCM_AON_PRCMRAWFS2_DIGBGMAG1_M                              0x00007F80U
#define PRCM_AON_PRCMRAWFS2_DIGBGMAG1_S                              7U
/*

        Field:           DIGBGRTRIM1
        From..to bits:   15...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG RTRIM 1ST INSERTION
                         For the first insertion.
                         This field is used for trimming at boot after shift done.

*/
#define PRCM_AON_PRCMRAWFS2_DIGBGRTRIM1_W                            5U
#define PRCM_AON_PRCMRAWFS2_DIGBGRTRIM1_M                            0x000F8000U
#define PRCM_AON_PRCMRAWFS2_DIGBGRTRIM1_S                            15U
/*

        Field:           DIGBGGMI1
        From..to bits:   20...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG GMI 1ST INSERTION
                         For the first insertion.
                         This field is used for trimming at boot after shift done.

*/
#define PRCM_AON_PRCMRAWFS2_DIGBGGMI1_W                              5U
#define PRCM_AON_PRCMRAWFS2_DIGBGGMI1_M                              0x01F00000U
#define PRCM_AON_PRCMRAWFS2_DIGBGGMI1_S                              20U
/*

        Field:           PMCTEMPSNS1
        From..to bits:   25...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     PMCIO TEMP SENSOR 1ST INSERTION
                         For the first insertion.

*/
#define PRCM_AON_PRCMRAWFS2_PMCTEMPSNS1_W                            7U
#define PRCM_AON_PRCMRAWFS2_PMCTEMPSNS1_M                            0xFE000000U
#define PRCM_AON_PRCMRAWFS2_PMCTEMPSNS1_S                            25U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRCMRAWFS3
    Offset name:         PRCM_AON_O_PRCMRAWFS3
    Relative address:    0x2048
    Description:         PRCM RAW FUSE 3

                        fuse line 8
    Default Value:       0x00000000

        Field:           DEVDESREV
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEVDesREV

*/
#define PRCM_AON_PRCMRAWFS3_DEVDESREV_W                              5U
#define PRCM_AON_PRCMRAWFS3_DEVDESREV_M                              0x0000001FU
#define PRCM_AON_PRCMRAWFS3_DEVDESREV_S                              0U
/*

        Field:           MEMREPAIR
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     memrepair

*/
#define PRCM_AON_PRCMRAWFS3_MEMREPAIR                                0x00000020U
#define PRCM_AON_PRCMRAWFS3_MEMREPAIR_M                              0x00000020U
#define PRCM_AON_PRCMRAWFS3_MEMREPAIR_S                              5U
/*

        Field:           MKDASHDEFINED
        From..to bits:   6...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Make-defined

*/
#define PRCM_AON_PRCMRAWFS3_MKDASHDEFINED_W                          11U
#define PRCM_AON_PRCMRAWFS3_MKDASHDEFINED_M                          0x0001FFC0U
#define PRCM_AON_PRCMRAWFS3_MKDASHDEFINED_S                          6U
/*

        Field:           CHECKSUM
        From..to bits:   17...30
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Checksum_TI_ DIEID_FUSE_DATA_5_6_8

*/
#define PRCM_AON_PRCMRAWFS3_CHECKSUM_W                               14U
#define PRCM_AON_PRCMRAWFS3_CHECKSUM_M                               0x7FFE0000U
#define PRCM_AON_PRCMRAWFS3_CHECKSUM_S                               17U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRCMRAWFS4
    Offset name:         PRCM_AON_O_PRCMRAWFS4
    Relative address:    0x204C
    Description:         PRCM RAW FUSE 4

                        fuse line 9
    Default Value:       0x00000000

        Field:           DIGBGCUR2
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG CURVE 2ND INSERTION
                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_PRCMRAWFS4_DIGBGCUR2_W                              7U
#define PRCM_AON_PRCMRAWFS4_DIGBGCUR2_M                              0x0000007FU
#define PRCM_AON_PRCMRAWFS4_DIGBGCUR2_S                              0U
/*

        Field:           DIGBGMAG2
        From..to bits:   7...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG MAG 2ND INSERTION
                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_PRCMRAWFS4_DIGBGMAG2_W                              8U
#define PRCM_AON_PRCMRAWFS4_DIGBGMAG2_M                              0x00007F80U
#define PRCM_AON_PRCMRAWFS4_DIGBGMAG2_S                              7U
/*

        Field:           DIGBGRTRIM2
        From..to bits:   15...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG RTRIM 2ND INSERTION

                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_PRCMRAWFS4_DIGBGRTRIM2_W                            5U
#define PRCM_AON_PRCMRAWFS4_DIGBGRTRIM2_M                            0x000F8000U
#define PRCM_AON_PRCMRAWFS4_DIGBGRTRIM2_S                            15U
/*

        Field:           DIGBGGMI2
        From..to bits:   20...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DIGBG GMI 2ND INSERTION

                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_PRCMRAWFS4_DIGBGGMI2_W                              5U
#define PRCM_AON_PRCMRAWFS4_DIGBGGMI2_M                              0x01F00000U
#define PRCM_AON_PRCMRAWFS4_DIGBGGMI2_S                              20U
/*

        Field:           PMCTMPSNS2
        From..to bits:   25...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     PMCIO TEMP SENSOR 2ND INSERTION
                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_PRCMRAWFS4_PMCTMPSNS2_W                             7U
#define PRCM_AON_PRCMRAWFS4_PMCTMPSNS2_M                             0xFE000000U
#define PRCM_AON_PRCMRAWFS4_PMCTMPSNS2_S                             25U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRCMRAWFS5
    Offset name:         PRCM_AON_O_PRCMRAWFS5
    Relative address:    0x2050
    Description:         PRCM RAW FUSE 5

                        fuse line 10
    Default Value:       0x00000000

        Field:           LOWRVMTRIM
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Low Digital Supply RVM Trimming

*/
#define PRCM_AON_PRCMRAWFS5_LOWRVMTRIM_W                             7U
#define PRCM_AON_PRCMRAWFS5_LOWRVMTRIM_M                             0x0000007FU
#define PRCM_AON_PRCMRAWFS5_LOWRVMTRIM_S                             0U
/*

        Field:           HIRVMTRIM
        From..to bits:   7...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     High Digital Supply RVM Trimming

*/
#define PRCM_AON_PRCMRAWFS5_HIRVMTRIM_W                              6U
#define PRCM_AON_PRCMRAWFS5_HIRVMTRIM_M                              0x00001F80U
#define PRCM_AON_PRCMRAWFS5_HIRVMTRIM_S                              7U
/*

        Field:           ENLOWRVMPROT
        From..to bits:   13...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Enable Low RVM protection (Specify whether to use the indication from RVM to reset the device).
                         The RVM Enable can be override by SW (Boot RAM/Privilege mode).
                         0 - Disable (Ignore indication from RVM)
                         Other (1-7) - Enable (Do not ignore indication from RVM)

*/
#define PRCM_AON_PRCMRAWFS5_ENLOWRVMPROT_W                           3U
#define PRCM_AON_PRCMRAWFS5_ENLOWRVMPROT_M                           0x0000E000U
#define PRCM_AON_PRCMRAWFS5_ENLOWRVMPROT_S                           13U
/*

        Field:           ENHIRVMPROT
        From..to bits:   16...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Enable High RVM protection (Specify whether to use the indication from RVM to reset the device).
                         The RVM Enable can be override by SW (Boot RAM/Privilege mode).
                         0 - Disable (Ignore indication from RVM)
                         Other (1-7) - Enable (Do not ignore indication from RVM)
                         Consider Splitting the enables (including CRC)

*/
#define PRCM_AON_PRCMRAWFS5_ENHIRVMPROT_W                            3U
#define PRCM_AON_PRCMRAWFS5_ENHIRVMPROT_M                            0x00070000U
#define PRCM_AON_PRCMRAWFS5_ENHIRVMPROT_S                            16U
/*

        Field:           I2VCIRCUIT
        From..to bits:   19...25
        DefaultValue:    0x0
        Access type:     read-only
        Description:     I2V Circuit (Measure Current using GPADC)

*/
#define PRCM_AON_PRCMRAWFS5_I2VCIRCUIT_W                             7U
#define PRCM_AON_PRCMRAWFS5_I2VCIRCUIT_M                             0x03F80000U
#define PRCM_AON_PRCMRAWFS5_I2VCIRCUIT_S                             19U
/*

        Field:           BROWNOUTTRIM
        From..to bits:   26...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Brownout Trims

*/
#define PRCM_AON_PRCMRAWFS5_BROWNOUTTRIM_W                           6U
#define PRCM_AON_PRCMRAWFS5_BROWNOUTTRIM_M                           0xFC000000U
#define PRCM_AON_PRCMRAWFS5_BROWNOUTTRIM_S                           26U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRCMRAWFS6
    Offset name:         PRCM_AON_O_PRCMRAWFS6
    Relative address:    0x2054
    Description:         PRCM RAW FUSE 6

                        fuse line 11
    Default Value:       0x00000000

        Field:           ABGAPTMP1
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ANABGAP TEMP 1ST INSERTION Trimming.
                         For the first insertion.
                         This field is used for trimming at boot after shift done.

*/
#define PRCM_AON_PRCMRAWFS6_ABGAPTMP1_W                              5U
#define PRCM_AON_PRCMRAWFS6_ABGAPTMP1_M                              0x0000001FU
#define PRCM_AON_PRCMRAWFS6_ABGAPTMP1_S                              0U
/*

        Field:           ABGAPMAG1
        From..to bits:   6...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ANA BGAP MAG 1ST INSERTION
                         For the first insertion.
                         This field is used for trimming at boot after shift done.

*/
#define PRCM_AON_PRCMRAWFS6_ABGAPMAG1_W                              5U
#define PRCM_AON_PRCMRAWFS6_ABGAPMAG1_M                              0x000007C0U
#define PRCM_AON_PRCMRAWFS6_ABGAPMAG1_S                              6U
/*

        Field:           ABGAPTMP2
        From..to bits:   11...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ANABGAP TEMP 2ND INSERTION Trimming.
                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_PRCMRAWFS6_ABGAPTMP2_W                              5U
#define PRCM_AON_PRCMRAWFS6_ABGAPTMP2_M                              0x0000F800U
#define PRCM_AON_PRCMRAWFS6_ABGAPTMP2_S                              11U
/*

        Field:           ABGAPMAG2
        From..to bits:   17...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ANA BGAP MAG 2ND INSERTION

                         For the second insertion.
                         This field is used by SW only.

*/
#define PRCM_AON_PRCMRAWFS6_ABGAPMAG2_W                              5U
#define PRCM_AON_PRCMRAWFS6_ABGAPMAG2_M                              0x003E0000U
#define PRCM_AON_PRCMRAWFS6_ABGAPMAG2_S                              17U
/*

        Field:           ANABGRTRIM
        From..to bits:   22...25
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ANA BG RTRIM

                         This field is calculated bases on the 'RF_NWELL_Efuse' trimming results
                         ANABG RTRIM (REFSYS_REG0<9:6>)

*/
#define PRCM_AON_PRCMRAWFS6_ANABGRTRIM_W                             4U
#define PRCM_AON_PRCMRAWFS6_ANABGRTRIM_M                             0x03C00000U
#define PRCM_AON_PRCMRAWFS6_ANABGRTRIM_S                             22U
/*

        Field:           RFNWELL
        From..to bits:   26...30
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RF NWELL EFUSE

                         Will be used to calculate during production the PMREF_V2I_RTRIM - Reference current to the RFCIO RX/TX modules
                         (Can be part of OCP\, Not used in cold boot)

*/
#define PRCM_AON_PRCMRAWFS6_RFNWELL_W                                5U
#define PRCM_AON_PRCMRAWFS6_RFNWELL_M                                0x7C000000U
#define PRCM_AON_PRCMRAWFS6_RFNWELL_S                                26U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRCMRAWFS7
    Offset name:         PRCM_AON_O_PRCMRAWFS7
    Relative address:    0x2058
    Description:         PRCM RAW FUSE 7

                        fuse line 12
    Default Value:       0x00000000

        Field:           DELTATMP12
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DELTA TEMPERATURE 1ST 2ND INSERTIONS

                         Defines the delta temperature between the 1st and 2nd insertion in degC

*/
#define PRCM_AON_PRCMRAWFS7_DELTATMP12_W                             8U
#define PRCM_AON_PRCMRAWFS7_DELTATMP12_M                             0x000000FFU
#define PRCM_AON_PRCMRAWFS7_DELTATMP12_S                             0U
/*

        Field:           LFORESTRIM
        From..to bits:   8...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LFOSC Resistor Trimming

*/
#define PRCM_AON_PRCMRAWFS7_LFORESTRIM_W                             7U
#define PRCM_AON_PRCMRAWFS7_LFORESTRIM_M                             0x00007F00U
#define PRCM_AON_PRCMRAWFS7_LFORESTRIM_S                             8U
/*

        Field:           LFOSCFSEL
        From..to bits:   15...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LFOSC Frequency Trimming

*/
#define PRCM_AON_PRCMRAWFS7_LFOSCFSEL_W                              2U
#define PRCM_AON_PRCMRAWFS7_LFOSCFSEL_M                              0x00018000U
#define PRCM_AON_PRCMRAWFS7_LFOSCFSEL_S                              15U
/*

        Field:           BROWNOUTEN
        From..to bits:   17...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Brownout Enable/Disable:
                         0 - Disable
                         Other (1-7) - Enable
                         (When HW check these bits: if equal to '0' disable  otherwise enable)

*/
#define PRCM_AON_PRCMRAWFS7_BROWNOUTEN_W                             3U
#define PRCM_AON_PRCMRAWFS7_BROWNOUTEN_M                             0x000E0000U
#define PRCM_AON_PRCMRAWFS7_BROWNOUTEN_S                             17U
/*

        Field:           IOPMOS
        From..to bits:   26...28
        DefaultValue:    0x0
        Access type:     read-only
        Description:     IO PMOS

*/
#define PRCM_AON_PRCMRAWFS7_IOPMOS_W                                 3U
#define PRCM_AON_PRCMRAWFS7_IOPMOS_M                                 0x1C000000U
#define PRCM_AON_PRCMRAWFS7_IOPMOS_S                                 26U
/*

        Field:           IONMOS
        From..to bits:   29...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     IO NMOS

*/
#define PRCM_AON_PRCMRAWFS7_IONMOS_W                                 3U
#define PRCM_AON_PRCMRAWFS7_IONMOS_M                                 0xE0000000U
#define PRCM_AON_PRCMRAWFS7_IONMOS_S                                 29U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRCMRAWFS8
    Offset name:         PRCM_AON_O_PRCMRAWFS8
    Relative address:    0x205C
    Description:         PRCM RAW FUSE 8

                        fuse line 13
    Default Value:       0x00000000

        Field:           CRNMOSRFCODP
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CORE NMOS RFCIO ODP

*/
#define PRCM_AON_PRCMRAWFS8_CRNMOSRFCODP_W                           4U
#define PRCM_AON_PRCMRAWFS8_CRNMOSRFCODP_M                           0x0000000FU
#define PRCM_AON_PRCMRAWFS8_CRNMOSRFCODP_S                           0U
/*

        Field:           AFNMOSRFCODP
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AF NMOS RFCIO ODP

*/
#define PRCM_AON_PRCMRAWFS8_AFNMOSRFCODP_W                           4U
#define PRCM_AON_PRCMRAWFS8_AFNMOSRFCODP_M                           0x000000F0U
#define PRCM_AON_PRCMRAWFS8_AFNMOSRFCODP_S                           4U
/*

        Field:           CRPMOSRFCODP
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CORE PMOS RFCIO ODP

*/
#define PRCM_AON_PRCMRAWFS8_CRPMOSRFCODP_W                           4U
#define PRCM_AON_PRCMRAWFS8_CRPMOSRFCODP_M                           0x00000F00U
#define PRCM_AON_PRCMRAWFS8_CRPMOSRFCODP_S                           8U
/*

        Field:           AFPMOSRFCODP
        From..to bits:   12...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AF PMOS RFCIO ODP

*/
#define PRCM_AON_PRCMRAWFS8_AFPMOSRFCODP_W                           4U
#define PRCM_AON_PRCMRAWFS8_AFPMOSRFCODP_M                           0x0000F000U
#define PRCM_AON_PRCMRAWFS8_AFPMOSRFCODP_S                           12U
/*

        Field:           COREPMOS
        From..to bits:   16...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CORE PMOS SOC ODP

*/
#define PRCM_AON_PRCMRAWFS8_COREPMOS_W                               3U
#define PRCM_AON_PRCMRAWFS8_COREPMOS_M                               0x00070000U
#define PRCM_AON_PRCMRAWFS8_COREPMOS_S                               16U
/*

        Field:           CORENMOS
        From..to bits:   19...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CORE NMOS SOC ODP

*/
#define PRCM_AON_PRCMRAWFS8_CORENMOS_W                               3U
#define PRCM_AON_PRCMRAWFS8_CORENMOS_M                               0x00380000U
#define PRCM_AON_PRCMRAWFS8_CORENMOS_S                               19U
/*

        Field:           BYPASSPLL
        From..to bits:   22...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bypass SoC PLL
                         Other (0-6) - Do not bypass SoC PLL
                         7 - Bypass SoC PLL

*/
#define PRCM_AON_PRCMRAWFS8_BYPASSPLL_W                              3U
#define PRCM_AON_PRCMRAWFS8_BYPASSPLL_M                              0x01C00000U
#define PRCM_AON_PRCMRAWFS8_BYPASSPLL_S                              22U
/*

        Field:           GPADCOFFSET
        From..to bits:   25...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     GPADC OFFSET

                         Capture the offset error of the GPADC

*/
#define PRCM_AON_PRCMRAWFS8_GPADCOFFSET_W                            7U
#define PRCM_AON_PRCMRAWFS8_GPADCOFFSET_M                            0xFE000000U
#define PRCM_AON_PRCMRAWFS8_GPADCOFFSET_S                            25U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRCMRAWFS9
    Offset name:         PRCM_AON_O_PRCMRAWFS9
    Relative address:    0x2060
    Description:         PRCM RAW FUSE 9

                        fuse line 14
    Default Value:       0x00000000

        Field:           CMRTRIM
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CLKM RTRIM

                         This field is calculated base on the 'RF_NWELL_Efuse ' trimming results
                         (CKM_SLICER_REG0<4:0>)

*/
#define PRCM_AON_PRCMRAWFS9_CMRTRIM_W                                5U
#define PRCM_AON_PRCMRAWFS9_CMRTRIM_M                                0x0000001FU
#define PRCM_AON_PRCMRAWFS9_CMRTRIM_S                                0U
/*

        Field:           XTITRIMCTRL
        From..to bits:   5...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     XTAL ITRIM control (CKM_OSC_REG0<6:1>)

*/
#define PRCM_AON_PRCMRAWFS9_XTITRIMCTRL_W                            6U
#define PRCM_AON_PRCMRAWFS9_XTITRIMCTRL_M                            0x000007E0U
#define PRCM_AON_PRCMRAWFS9_XTITRIMCTRL_S                            5U
/*

        Field:           SLITRIMCTRL
        From..to bits:   11...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Slicer ITRIM Control (CKM_SLICER_REG0<7:5>)

*/
#define PRCM_AON_PRCMRAWFS9_SLITRIMCTRL_W                            3U
#define PRCM_AON_PRCMRAWFS9_SLITRIMCTRL_M                            0x00003800U
#define PRCM_AON_PRCMRAWFS9_SLITRIMCTRL_S                            11U
/*

        Field:           PALDOINMON
        From..to bits:   14...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     PA LDO IN MONITOR

                         PA LDO In ('Battery') Sensor Trimming for 3V

*/
#define PRCM_AON_PRCMRAWFS9_PALDOINMON_W                             5U
#define PRCM_AON_PRCMRAWFS9_PALDOINMON_M                             0x0007C000U
#define PRCM_AON_PRCMRAWFS9_PALDOINMON_S                             14U
/*

        Field:           SOCPROCES
        From..to bits:   19...20
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SOC PROCESS

                         The value is calculated based on Core PMOS/NMOS (SoC ODP)
                         2b'00 - Nominal
                         2b'01 - Weak
                         2b'10 - Strong

*/
#define PRCM_AON_PRCMRAWFS9_SOCPROCES_W                              2U
#define PRCM_AON_PRCMRAWFS9_SOCPROCES_M                              0x00180000U
#define PRCM_AON_PRCMRAWFS9_SOCPROCES_S                              19U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRCMRAWFS10
    Offset name:         PRCM_AON_O_PRCMRAWFS10
    Relative address:    0x2064
    Description:         PRCM RAW FUSE 10

                        fuse line 15
    Default Value:       0x00000000

*/

/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLKDET
    Offset name:         PRCM_AON_O_FCLKDET
    Relative address:    0x2068
    Description:         FAST CLK DETECTION

                        primary clock detection result
    Default Value:       0x00000000

        Field:           FREQVAL
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FAST CLK FREQUENCY DETECTION VALUE

                         fast clock detection value :
                         0: 10MHz
                         1: 26MHz
                         2: 40MHz
                         3: 52MHz

*/
#define PRCM_AON_FCLKDET_FREQVAL_W                                   3U
#define PRCM_AON_FCLKDET_FREQVAL_M                                   0x00000007U
#define PRCM_AON_FCLKDET_FREQVAL_S                                   0U
/*

        Field:           FAILED
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     fast clock detection FSM failed
                         counter was no in any FREQ boundaries
                         '1' - failed
                         '0' - OK

*/
#define PRCM_AON_FCLKDET_FAILED                                      0x00000010U
#define PRCM_AON_FCLKDET_FAILED_M                                    0x00000010U
#define PRCM_AON_FCLKDET_FAILED_S                                    4U
/*

        Field:           OVERLAP
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Not in use.

                         '1' - if FREF value is overlapping at 40/48MHz or 48/52MHz

*/
#define PRCM_AON_FCLKDET_OVERLAP                                     0x00000020U
#define PRCM_AON_FCLKDET_OVERLAP_M                                   0x00000020U
#define PRCM_AON_FCLKDET_OVERLAP_S                                   5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PLOCKLOSCFG
    Offset name:         PRCM_AON_O_PLOCKLOSCFG
    Relative address:    0x206C
    Description:         SOC PLL LOCK LOSS CONFIG
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     CLEAR

                         write clear

                         Clear Lock Loss Status.

*/
#define PRCM_AON_PLOCKLOSCFG_CLR                                     0x00000001U
#define PRCM_AON_PLOCKLOSCFG_CLR_M                                   0x00000001U
#define PRCM_AON_PLOCKLOSCFG_CLR_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PLOCKLOSSTA
    Offset name:         PRCM_AON_O_PLOCKLOSSTA
    Relative address:    0x2070
    Description:         SOC PLL LOCK LOSS STATUS
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     STATUS

                         Lock Loss Status. Set when SOC PLL is low during active (PD Core ON).
                         This indication is latch asynchronously since lock low implies no SOC PLL clock is available.
                         In PLL Bypass mode (e.g. SOP = DoA) this indication is ignored.
                         (Yet, in SOP = DoA , when SOP bypass is applied, and SOC PLL is no more bypassed, this indication is valid)

*/
#define PRCM_AON_PLOCKLOSSTA_STA                                     0x00000001U
#define PRCM_AON_PLOCKLOSSTA_STA_M                                   0x00000001U
#define PRCM_AON_PLOCKLOSSTA_STA_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RTCCTL
    Offset name:         PRCM_AON_O_RTCCTL
    Relative address:    0x2074
    Description:         RTC CONTROL
    Default Value:       0x00000002

        Field:           LFTICKSEL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     LFTICK SELECT

                         '1' - use real LFTICK
                         '0' - use fake LFTICK

*/
#define PRCM_AON_RTCCTL_LFTICKSEL                                    0x00000001U
#define PRCM_AON_RTCCTL_LFTICKSEL_M                                  0x00000001U
#define PRCM_AON_RTCCTL_LFTICKSEL_S                                  0U
/*

        Field:           DISIMMINENT
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     NOT USED - DO NOT CHANGE VALUE

                         '1' - disables imminent option towards SYSTIMER
                         '0' - enables imminent

*/
#define PRCM_AON_RTCCTL_DISIMMINENT                                  0x00000002U
#define PRCM_AON_RTCCTL_DISIMMINENT_M                                0x00000002U
#define PRCM_AON_RTCCTL_DISIMMINENT_S                                1U
/*

        Field:           LFTICKSTA
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LFTICK STATE

                         '1101' - Real LFTICK
                         '1100' - Gate RTC CLK
                         '1110' - Force LFTICK high
                         '1010' - Switch RTC CLK low
                         '0010' - Standby
                         '0000' - Force LFTICK low
                         '0100' - switch RTC CLK high
                         '0101' - Ungate RTC CLK

*/
#define PRCM_AON_RTCCTL_LFTICKSTA_W                                  4U
#define PRCM_AON_RTCCTL_LFTICKSTA_M                                  0x00000F00U
#define PRCM_AON_RTCCTL_LFTICKSTA_S                                  8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFINCCTL
    Offset name:         PRCM_AON_O_LFINCCTL
    Relative address:    0x2078
    Description:         LFINC CONTROL

                        Low frequency time increment control
    Default Value:       0x00000002

        Field:           SOFTRSTRT
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SOFT RESTART

                         Use a higher gear after re-enabling / wake-up.

                         The filter will require 16-24 LFCLK periods to settle (depending on [STOPGEAR]), but may respond faster to frequency changes during STANDBY.

        ENUMs:
            ON:                          Use soft gearing restarts
            OFF:                         Don't use soft gearing restarts
*/
#define PRCM_AON_LFINCCTL_SOFTRSTRT                                  0x00000004U
#define PRCM_AON_LFINCCTL_SOFTRSTRT_M                                0x00000004U
#define PRCM_AON_LFINCCTL_SOFTRSTRT_S                                2U
#define PRCM_AON_LFINCCTL_SOFTRSTRT_ON                               0x00000004U
#define PRCM_AON_LFINCCTL_SOFTRSTRT_OFF                              0x00000000U
/*

        Field:           GEARRSTRT
        From..to bits:   3...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     GEAR RESTART

                         Controls gearing restart of the LFINC filter.

        ENUMs:
            TWOTHR:                      Restart gearing when the error accumulator crosses the threshold twice in a row.
            ONETHR:                      Restart gearing when the error accumulator crosses the threshold once.
            NEVER:                       Never restart gearing. Very stable filter value, but very slow response on frequency changes.
*/
#define PRCM_AON_LFINCCTL_GEARRSTRT_W                                2U
#define PRCM_AON_LFINCCTL_GEARRSTRT_M                                0x00000018U
#define PRCM_AON_LFINCCTL_GEARRSTRT_S                                3U
#define PRCM_AON_LFINCCTL_GEARRSTRT_TWOTHR                           0x00000010U
#define PRCM_AON_LFINCCTL_GEARRSTRT_ONETHR                           0x00000008U
#define PRCM_AON_LFINCCTL_GEARRSTRT_NEVER                            0x00000000U
/*

        Field:           ERRTHR
        From..to bits:   5...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ERROR THRESHOLD

                         Controls the threshold for gearing restart of the LFINC filter.

                         Only effective if [GEARRSTRT] is not ONETHR or TWOTHR.

        ENUMs:
            MIDSMALL:                    Middle value towards SMALL.
            MIDLARGE:                    Middle value towards LARGE.
            LARGE:                       Restart gearing on large error. Fewer false restarts, slower response on small frequency shifts.
            SMALL:                       Restart gearing on small error. Potentially more false restarts, faster response on small frequency shifts.
*/
#define PRCM_AON_LFINCCTL_ERRTHR_W                                   2U
#define PRCM_AON_LFINCCTL_ERRTHR_M                                   0x00000060U
#define PRCM_AON_LFINCCTL_ERRTHR_S                                   5U
#define PRCM_AON_LFINCCTL_ERRTHR_MIDSMALL                            0x00000040U
#define PRCM_AON_LFINCCTL_ERRTHR_MIDLARGE                            0x00000020U
#define PRCM_AON_LFINCCTL_ERRTHR_LARGE                               0x00000000U
#define PRCM_AON_LFINCCTL_ERRTHR_SMALL                               0x00000060U
/*

        Field:           STOPGEAR
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     STOP GEAR

                         Controls the final gear of the LFINC filter.

        ENUMs:
            LOW:                         Lowest final gear. Best settling, but less dynamic frequency tracking.
            HIGH:                        Highest final gear. Best dynamic frequency tracking, but higher variation in filter value.
*/
#define PRCM_AON_LFINCCTL_STOPGEAR                                   0x00000080U
#define PRCM_AON_LFINCCTL_STOPGEAR_M                                 0x00000080U
#define PRCM_AON_LFINCCTL_STOPGEAR_S                                 7U
#define PRCM_AON_LFINCCTL_STOPGEAR_LOW                               0x00000000U
#define PRCM_AON_LFINCCTL_STOPGEAR_HIGH                              0x00000080U
/*

        Field:           FKLFTICKSEL
        From..to bits:   8...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FAKE LFTICK SELECTOR

                         '00' - default - LOKI + corner case scenario
                         '01' - first integration
                         '10' - LOKI
                         '11' - always enable

        ENUMs:
            MIDSMALL:                    Middle value towards SMALL.
            MIDLARGE:                    Middle value towards LARGE.
            LARGE:                       Restart gearing on large error. Fewer false restarts, slower response on small frequency shifts.
            SMALL:                       Restart gearing on small error. Potentially more false restarts, faster response on small frequency shifts.
*/
#define PRCM_AON_LFINCCTL_FKLFTICKSEL_W                              2U
#define PRCM_AON_LFINCCTL_FKLFTICKSEL_M                              0x00000300U
#define PRCM_AON_LFINCCTL_FKLFTICKSEL_S                              8U
#define PRCM_AON_LFINCCTL_FKLFTICKSEL_MIDSMALL                       0x00000200U
#define PRCM_AON_LFINCCTL_FKLFTICKSEL_MIDLARGE                       0x00000100U
#define PRCM_AON_LFINCCTL_FKLFTICKSEL_LARGE                          0x00000000U
#define PRCM_AON_LFINCCTL_FKLFTICKSEL_SMALL                          0x00000300U
/*

        Field:           PREVSTBY
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PREVENT STANDBY

                         Controls if the LFINC filter prevents STANDBY entry until settled.

        ENUMs:
            OFF:                         Disable. Do not prevent STANDBY entry.
            ON:                          Enable. Prevent STANDBY entry.
*/
#define PRCM_AON_LFINCCTL_PREVSTBY                                   0x80000000U
#define PRCM_AON_LFINCCTL_PREVSTBY_M                                 0x80000000U
#define PRCM_AON_LFINCCTL_PREVSTBY_S                                 31U
#define PRCM_AON_LFINCCTL_PREVSTBY_OFF                               0x00000000U
#define PRCM_AON_LFINCCTL_PREVSTBY_ON                                0x80000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFCLKSTA
    Offset name:         PRCM_AON_O_LFCLKSTA
    Relative address:    0x207C
    Description:         LFCLK STATUS

                        Low-frequency clock status
    Default Value:       NA

        Field:           LFINC
        From..to bits:   0...21
        DefaultValue:    NA
        Access type:     read-only
        Description:     Measured value of LFCLKSTAT_LFINC.

                         Given in microseconds with 16 fractional bits.
                         This value is calculated by Hardware.
                         It is the LFCLK period according to CLKULL cycles.

*/
#define PRCM_AON_LFCLKSTA_LFINC_W                                    22U
#define PRCM_AON_LFCLKSTA_LFINC_M                                    0x003FFFFFU
#define PRCM_AON_LFCLKSTA_LFINC_S                                    0U
/*

        Field:           LFINCSRC
        From..to bits:   22...23
        DefaultValue:    NA
        Access type:     read-only
        Description:     Source of LFINC used by the RTC.

                         This value depends on [LFINCOVR.OVERRIDE], LF clock availability, HF tracking loop status and the device state (ACTIVE/STANDBY).

        ENUMs:
            OVERRIDE:                    Using override value from [LFINCOVR.LFINC]
            MEAS:                        Using measured value.
                         This value is updated by hardware and can be read from [LFINC].
            AVG:                         Using filtered / average value.
                         This value is updated by hardware and can be read and updated in [LFINCCTL.INT].
            FAKE:                        Using FAKE LFTICKs with corresponding LFINC value.
*/
#define PRCM_AON_LFCLKSTA_LFINCSRC_W                                 2U
#define PRCM_AON_LFCLKSTA_LFINCSRC_M                                 0x00C00000U
#define PRCM_AON_LFCLKSTA_LFINCSRC_S                                 22U
#define PRCM_AON_LFCLKSTA_LFINCSRC_OVERRIDE                          0x00800000U
#define PRCM_AON_LFCLKSTA_LFINCSRC_MEAS                              0x00000000U
#define PRCM_AON_LFCLKSTA_LFINCSRC_AVG                               0x00400000U
#define PRCM_AON_LFCLKSTA_LFINCSRC_FAKE                              0x00C00000U
/*

        Field:           LFTICKSRC
        From..to bits:   24...24
        DefaultValue:    NA
        Access type:     read-only
        Description:     Source of LFTICK.

        ENUMs:
            LFCLK:                       LFTICK generated from the selected LFCLK
            FAKE:                        LFTICK generated from CLKULL (LFCLK not available)
*/
#define PRCM_AON_LFCLKSTA_LFTICKSRC                                  0x01000000U
#define PRCM_AON_LFCLKSTA_LFTICKSRC_M                                0x01000000U
#define PRCM_AON_LFCLKSTA_LFTICKSRC_S                                24U
#define PRCM_AON_LFCLKSTA_LFTICKSRC_LFCLK                            0x00000000U
#define PRCM_AON_LFCLKSTA_LFTICKSRC_FAKE                             0x01000000U
/*

        Field:           FLTSETLED
        From..to bits:   25...25
        DefaultValue:    NA
        Access type:     read-only
        Description:     FILTER SETTLED

                         LFINC filter is running and settled.

*/
#define PRCM_AON_LFCLKSTA_FLTSETLED                                  0x02000000U
#define PRCM_AON_LFCLKSTA_FLTSETLED_M                                0x02000000U
#define PRCM_AON_LFCLKSTA_FLTSETLED_S                                25U
/*

        Field:           GOOD
        From..to bits:   31...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Low frequency clock good

                         Note: This is only a coarse frequency check based on [LFQUALCTL.*]. The clock may not be accurate enough for timing purposes.

*/
#define PRCM_AON_LFCLKSTA_GOOD                                       0x80000000U
#define PRCM_AON_LFCLKSTA_GOOD_M                                     0x80000000U
#define PRCM_AON_LFCLKSTA_GOOD_S                                     31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFINCOVR
    Offset name:         PRCM_AON_O_LFINCOVR
    Relative address:    0x2080
    Description:         LFINC OVERRIDE

                        Low frequency time increment override control
    Default Value:       0x00000000

        Field:           LFINC
        From..to bits:   0...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     LF increment value

                         This value is used when [OVERRIDE] is set to 1.
                         Otherwise the value is calculated automatically.

*/
#define PRCM_AON_LFINCOVR_LFINC_W                                    22U
#define PRCM_AON_LFINCOVR_LFINC_M                                    0x003FFFFFU
#define PRCM_AON_LFINCOVR_LFINC_S                                    0U
/*

        Field:           OV
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Override LF increment

                         Use the value provided in [LFINC] instead of the value calculated by Hardware.

*/
#define PRCM_AON_LFINCOVR_OV                                         0x80000000U
#define PRCM_AON_LFINCOVR_OV_M                                       0x80000000U
#define PRCM_AON_LFINCOVR_OV_S                                       31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFQUALCTL
    Offset name:         PRCM_AON_O_LFQUALCTL
    Relative address:    0x2084
    Description:         Low frequency clock qualification control
    Default Value:       0x00000020

        Field:           CONSEC
        From..to bits:   0...7
        DefaultValue:    0x20
        Access type:     read-write
        Description:     Number of consecutive times the LFCLK period error has to be
                         smaller than [MAXERR] to be considered "good".
                         Setting this value to 0 will bypass clock qualification,
                         and the "good" indicator will always be 1.

*/
#define PRCM_AON_LFQUALCTL_CONSEC_W                                  8U
#define PRCM_AON_LFQUALCTL_CONSEC_M                                  0x000000FFU
#define PRCM_AON_LFQUALCTL_CONSEC_S                                  0U
/*

        Field:           MAXERR
        From..to bits:   8...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Maximum LFCLK period error.

                         Value given in microseconds, 3 integer bits + 3 fractional bits.

*/
#define PRCM_AON_LFQUALCTL_MAXERR_W                                  6U
#define PRCM_AON_LFQUALCTL_MAXERR_M                                  0x00003F00U
#define PRCM_AON_LFQUALCTL_MAXERR_S                                  8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFINCCTLI
    Offset name:         PRCM_AON_O_LFINCCTLI
    Relative address:    0x2088
    Description:         Low frequency time increment value
    Default Value:       0x001E8480

        Field:           INT
        From..to bits:   0...21
        DefaultValue:    0x1E8480
        Access type:     read-write
        Description:     Increment override value

                         write opt

                         SW and HW can write this value

                         Integral part of the LFINC filter.

                         This value is updated by Hardware to reflect the current state of the filter.
                         It can also be written to change the current state.

*/
#define PRCM_AON_LFINCCTLI_INT_W                                     22U
#define PRCM_AON_LFINCCTLI_INT_M                                     0x003FFFFFU
#define PRCM_AON_LFINCCTLI_INT_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SCLKCNT
    Offset name:         PRCM_AON_O_SCLKCNT
    Relative address:    0x208C
    Description:         SLOW CLK COUNT
    Default Value:       0x00000000

        Field:           DET
        From..to bits:   0...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FAST CLK DETECTION COUNTER VALUE

                         Counter results for 4 slow clock
                         freq        lower 	upper
                         (MHz)    (dec)          (dec)
                         10          1190          1503
                         26          3094          3908
                         40   	      4760          6012
                         52          6188          7815

*/
#define PRCM_AON_SCLKCNT_DET_W                                       15U
#define PRCM_AON_SCLKCNT_DET_M                                       0x00007FFFU
#define PRCM_AON_SCLKCNT_DET_S                                       0U
/*

        Field:           PERVAL
        From..to bits:   16...22
        DefaultValue:    0x0
        Access type:     read-only
        Description:     PERIOD VALUE

                         slow CLK current value.
                         bounds are 0 to slow_clk_counter_period

*/
#define PRCM_AON_SCLKCNT_PERVAL_W                                    7U
#define PRCM_AON_SCLKCNT_PERVAL_M                                    0x007F0000U
#define PRCM_AON_SCLKCNT_PERVAL_S                                    16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SCLKCNTCTL
    Offset name:         PRCM_AON_O_SCLKCNTCTL
    Relative address:    0x2090
    Description:         SLOW CLOCK COUNTER CONTROL
    Default Value:       0x0000000C

        Field:           MODE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MODE

                         Determine the Slow clock counter mode-
                         0x3 - Reserved
                         0x2 - Periodic
                         0x1 - One Shot
                         0x0 - Disable

*/
#define PRCM_AON_SCLKCNTCTL_MODE_W                                   2U
#define PRCM_AON_SCLKCNTCTL_MODE_M                                   0x00000003U
#define PRCM_AON_SCLKCNTCTL_MODE_S                                   0U
/*

        Field:           PER
        From..to bits:   2...8
        DefaultValue:    0x3
        Access type:     read-write
        Description:     PERIOD

                         Determine the Slow clock counter period (Slow Clock cycles), 1 - 128.
                         '0' - 1 CLK cycle
                         '1' - 2 CLK cycles
                         '2' - 3 CLK cycles
                         ...
                         '127' - 128 CLK cycles

*/
#define PRCM_AON_SCLKCNTCTL_PER_W                                    7U
#define PRCM_AON_SCLKCNTCTL_PER_M                                    0x000001FCU
#define PRCM_AON_SCLKCNTCTL_PER_S                                    2U
/*

        Field:           RESULT
        From..to bits:   9...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RESULT

                         Slow Clock counter result

*/
#define PRCM_AON_SCLKCNTCTL_RESULT_W                                 15U
#define PRCM_AON_SCLKCNTCTL_RESULT_M                                 0x00FFFE00U
#define PRCM_AON_SCLKCNTCTL_RESULT_S                                 9U
/*

        Field:           RESULTVAL
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RESULT VALID

                         read clear pulse

                         Determine whether the measurement is in progress or done:
                         0x0 - In progress (Relevant in one shot only)
                         0x1 - Done (when finish measurement and result ready)

*/
#define PRCM_AON_SCLKCNTCTL_RESULTVAL                                0x01000000U
#define PRCM_AON_SCLKCNTCTL_RESULTVAL_M                              0x01000000U
#define PRCM_AON_SCLKCNTCTL_RESULTVAL_S                              24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SCLKCNTSTRT
    Offset name:         PRCM_AON_O_SCLKCNTSTRT
    Relative address:    0x2094
    Description:         SLOW CLK COUNT START KICK
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     ENABLE

                         write clear

                         start the FREQUENCY DETECTION.
                         MEM_SLOW_CLK_COUNTER_MODE should be set prior to the start indication

*/
#define PRCM_AON_SCLKCNTSTRT_EN                                      0x00000001U
#define PRCM_AON_SCLKCNTSTRT_EN_M                                    0x00000001U
#define PRCM_AON_SCLKCNTSTRT_EN_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SCLKCTL
    Offset name:         PRCM_AON_O_SCLKCTL
    Relative address:    0x2098
    Description:         SLOW CLK CONTROL
    Default Value:       0x00000000

        Field:           LFOSCSEL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     LFOSC SELECTOR

                         0 - select RCOSC
                         1 - select LFXT/EXT/XTAL

*/
#define PRCM_AON_SCLKCTL_LFOSCSEL                                    0x00000001U
#define PRCM_AON_SCLKCTL_LFOSCSEL_M                                  0x00000001U
#define PRCM_AON_SCLKCTL_LFOSCSEL_S                                  0U
/*

        Field:           SDIVCLKSEL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SLOW CLOCK DIVISION SELECTOR

                         1 - select LFXT/EXT/XTAL CLK DIV 8
                         0 - select LFXT/EXT/XTAL CLK

*/
#define PRCM_AON_SCLKCTL_SDIVCLKSEL                                  0x00000002U
#define PRCM_AON_SCLKCTL_SDIVCLKSEL_M                                0x00000002U
#define PRCM_AON_SCLKCTL_SDIVCLKSEL_S                                1U
/*

        Field:           P32CLKSEL
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PLL CLOCK SELECTOR

                         '0' - LFCLK (real tick should be selected)
                         '1' - PLL32 CLK (fake tick should be selected)

*/
#define PRCM_AON_SCLKCTL_P32CLKSEL                                   0x00000004U
#define PRCM_AON_SCLKCTL_P32CLKSEL_M                                 0x00000004U
#define PRCM_AON_SCLKCTL_P32CLKSEL_S                                 2U
/*

        Field:           GOOD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     '1' - set LFXT CLK good

*/
#define PRCM_AON_SCLKCTL_GOOD                                        0x00000008U
#define PRCM_AON_SCLKCTL_GOOD_M                                      0x00000008U
#define PRCM_AON_SCLKCTL_GOOD_S                                      3U
/*

        Field:           DETGOOD
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DETECTION GOOD

                         '1' - means 5 edges detected of LFXT/EXT/XTAL

*/
#define PRCM_AON_SCLKCTL_DETGOOD                                     0x00000010U
#define PRCM_AON_SCLKCTL_DETGOOD_M                                   0x00000010U
#define PRCM_AON_SCLKCTL_DETGOOD_S                                   4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STA
    Offset name:         PRCM_AON_O_STA
    Relative address:    0x209C
    Description:         PRCM STATUS
    Default Value:       0x00000000

        Field:           FCLKDETFAIL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FAST CLK DETECTIOn FAILED

                         '1' - FREF detection failed

*/
#define PRCM_AON_STA_FCLKDETFAIL                                     0x00000001U
#define PRCM_AON_STA_FCLKDETFAIL_M                                   0x00000001U
#define PRCM_AON_STA_FCLKDETFAIL_S                                   0U
/*

        Field:           XTALMOD
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     XTAL MODE

                         '1' - XTAL mode
                         '0' - TCXO External mode

*/
#define PRCM_AON_STA_XTALMOD                                         0x00000002U
#define PRCM_AON_STA_XTALMOD_M                                       0x00000002U
#define PRCM_AON_STA_XTALMOD_S                                       1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTERUPT
    Offset name:         PRCM_AON_O_INTERUPT
    Relative address:    0x20A0
    Description:         [0]- indication at slow CLK calibration for one shot mode.
                        [1] - lfinc_updated
                        [2] - lfinc_gearing_restart
                        [3] - lfclk_oor
                        [4] - lfclk_loss
                        [5] - NU
                        [6] - NU
                        [7] - NU
    Default Value:       0x00000000

        Field:           IRQSTARAW
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     PRCM IRQ Clear indication and raw status

                         read clear

*/
#define PRCM_AON_INTERUPT_IRQSTARAW_W                                8U
#define PRCM_AON_INTERUPT_IRQSTARAW_M                                0x000000FFU
#define PRCM_AON_INTERUPT_IRQSTARAW_S                                0U
/*

        Field:           IRQBM
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PRCM IRQ mask option

*/
#define PRCM_AON_INTERUPT_IRQBM_W                                    8U
#define PRCM_AON_INTERUPT_IRQBM_M                                    0x0000FF00U
#define PRCM_AON_INTERUPT_IRQBM_S                                    8U
/*

        Field:           IRQSTABM
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     IRQs indication after Mask

*/
#define PRCM_AON_INTERUPT_IRQSTABM_W                                 8U
#define PRCM_AON_INTERUPT_IRQSTABM_M                                 0x00FF0000U
#define PRCM_AON_INTERUPT_IRQSTABM_S                                 16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HPRCMSHAR
    Offset name:         PRCM_AON_O_HPRCMSHAR
    Relative address:    0x20A4
    Description:         HOST PRCM SHARED

                        override values for PRCM SHARED Modules
    Default Value:       0x00000000

        Field:           PMSREQOV
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PMS REQUEST OVERRIDE

                         '1' - keeps awake at sleep state
                         '0' - regular operation

*/
#define PRCM_AON_HPRCMSHAR_PMSREQOV                                  0x00000001U
#define PRCM_AON_HPRCMSHAR_PMSREQOV_M                                0x00000001U
#define PRCM_AON_HPRCMSHAR_PMSREQOV_S                                0U
/*

        Field:           FREFREQOV
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FREF REQUEST OVERRIDE

                         '1' - keeps awake at sleep state
                         '0' - regular operation

                         note: in order to set this field as '1', PMS OV must be set as well.

*/
#define PRCM_AON_HPRCMSHAR_FREFREQOV                                 0x00000002U
#define PRCM_AON_HPRCMSHAR_FREFREQOV_M                               0x00000002U
#define PRCM_AON_HPRCMSHAR_FREFREQOV_S                               1U
/*

        Field:           PSHREQOV
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PLL REQUEST OVERRIDE

                         '1' - keeps awake at sleep state
                         '0' - regular operation

                         note: in order to set this field as '1', FREF OV and PMS OV must be set as well.

*/
#define PRCM_AON_HPRCMSHAR_PSHREQOV                                  0x00000004U
#define PRCM_AON_HPRCMSHAR_PSHREQOV_M                                0x00000004U
#define PRCM_AON_HPRCMSHAR_PSHREQOV_S                                2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CRSLPIND
    Offset name:         PRCM_AON_O_CRSLPIND
    Relative address:    0x20A8
    Description:         CORE SLEEP INDICATION
    Default Value:       0x00000000

        Field:           CTLSTAT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CONTROL STATE

                         '1' - CORE is SLEEP
                         '0' - CORE is in ACTIVE or gets into ACTIVE

*/
#define PRCM_AON_CRSLPIND_CTLSTAT                                    0x00000001U
#define PRCM_AON_CRSLPIND_CTLSTAT_M                                  0x00000001U
#define PRCM_AON_CRSLPIND_CTLSTAT_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HSLPIND
    Offset name:         PRCM_AON_O_HSLPIND
    Relative address:    0x20AC
    Description:         HOST SLEEP INDICATION
    Default Value:       0x00000000

        Field:           CTLSTAT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CONTROL STATE

                         '1' - HOST is SLEEP
                         '0' - HOST is in ACTIVE or gets into ACTIVE

*/
#define PRCM_AON_HSLPIND_CTLSTAT                                     0x00000001U
#define PRCM_AON_HSLPIND_CTLSTAT_M                                   0x00000001U
#define PRCM_AON_HSLPIND_CTLSTAT_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FNCLKMUXCTL
    Offset name:         PRCM_AON_O_FNCLKMUXCTL
    Relative address:    0x20B0
    Description:         PRCM functional selection towards FAST CLK DETECTION

                        '00000' - prcm_fast_clock
                        'xxx01' - ospr_hsm_tst_fro_clk_out
                        'xxx10' - clk_gpadc_clk
                        'xxx11' - fref_2m_socpll_1p8v
                        'xx100' - rf_pll_divided_clk
                        '01000' - src_clk_40
                        '10000' - lfxt / xtal / ext
                        '11000' - rcosc
    Default Value:       0x00000000

        Field:           DBGCLKSEL
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Debug and Fast CLK detection selector

                         'x00' - prcm_fast_clock.
                         'x01' - ospr_hsm_tst_fro_clk_out
                         'x10' - clk_gpadc_clk
                         'x11' - fref_2m_socpll_1p8v
                         '100' - rf_pll_divided_clk


*/
#define PRCM_AON_FNCLKMUXCTL_DBGCLKSEL_W                             3U
#define PRCM_AON_FNCLKMUXCTL_DBGCLKSEL_M                             0x00000007U
#define PRCM_AON_FNCLKMUXCTL_DBGCLKSEL_S                             0U
/*

        Field:           SEL
        From..to bits:   3...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Fast CLK detection selector
                         MEM_DBG_CLK_SEL should be set 3'b0 for this reg to take place

                         '00' - prcm_fast_clock.
                         '01' - src_clk_40
                         '10' - lfxt / xtal / ext
                         '11' - rcosc

*/
#define PRCM_AON_FNCLKMUXCTL_SEL_W                                   2U
#define PRCM_AON_FNCLKMUXCTL_SEL_M                                   0x00000018U
#define PRCM_AON_FNCLKMUXCTL_SEL_S                                   3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RSTCTL
    Offset name:         PRCM_AON_O_RSTCTL
    Relative address:    0x20B4
    Description:         RESET CONTROL
    Default Value:       0x00000000

        Field:           SOCAON
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     SOC AON

                         write clear

                         '1' - set reset

*/
#define PRCM_AON_RSTCTL_SOCAON                                       0x00000001U
#define PRCM_AON_RSTCTL_SOCAON_M                                     0x00000001U
#define PRCM_AON_RSTCTL_SOCAON_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFOSC
    Offset name:         PRCM_AON_O_LFOSC
    Relative address:    0x20B8
    Description:         LFOSC OVERRIDE STATUS
    Default Value:       0x00000000

        Field:           FSFSEL
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LFOSC frequency trim value

*/
#define PRCM_AON_LFOSC_FSFSEL_W                                      2U
#define PRCM_AON_LFOSC_FSFSEL_M                                      0x00000003U
#define PRCM_AON_LFOSC_FSFSEL_S                                      0U
/*

        Field:           SELOVFSEL
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE FSEL

                         LFOSC frequency trim override select

*/
#define PRCM_AON_LFOSC_SELOVFSEL                                     0x00000004U
#define PRCM_AON_LFOSC_SELOVFSEL_M                                   0x00000004U
#define PRCM_AON_LFOSC_SELOVFSEL_S                                   2U
/*

        Field:           OVFSELVAL
        From..to bits:   3...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE FSEL SELECTOR VALUE

                         LFOSC frequency trim override value

*/
#define PRCM_AON_LFOSC_OVFSELVAL_W                                   2U
#define PRCM_AON_LFOSC_OVFSELVAL_M                                   0x00000018U
#define PRCM_AON_LFOSC_OVFSELVAL_S                                   3U
/*

        Field:           FSRESTRIM
        From..to bits:   5...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FUSE RESISTOR TRIM

                         Analog band gap rtrimfuse value for LFOSC rtrim

*/
#define PRCM_AON_LFOSC_FSRESTRIM_W                                   7U
#define PRCM_AON_LFOSC_FSRESTRIM_M                                   0x00000FE0U
#define PRCM_AON_LFOSC_FSRESTRIM_S                                   5U
/*

        Field:           SELOVRESTRIM
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECTOR OVERRIDE RESISTOR TRIM

                         LFOSC RES trim override select

*/
#define PRCM_AON_LFOSC_SELOVRESTRIM                                  0x00001000U
#define PRCM_AON_LFOSC_SELOVRESTRIM_M                                0x00001000U
#define PRCM_AON_LFOSC_SELOVRESTRIM_S                                12U
/*

        Field:           OVRESTRIMVAL
        From..to bits:   13...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE RESISTOR SELECTOR VALUE

                         LFOSC RES trim override value

*/
#define PRCM_AON_LFOSC_OVRESTRIMVAL_W                                7U
#define PRCM_AON_LFOSC_OVRESTRIMVAL_M                                0x000FE000U
#define PRCM_AON_LFOSC_OVRESTRIMVAL_S                                13U
/*

        Field:           SELOVOSCEN
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECTOR OVERRIDE OSC ENABLE

                         LFOSC enable override select

*/
#define PRCM_AON_LFOSC_SELOVOSCEN                                    0x00100000U
#define PRCM_AON_LFOSC_SELOVOSCEN_M                                  0x00100000U
#define PRCM_AON_LFOSC_SELOVOSCEN_S                                  20U
/*

        Field:           OVOSCEN
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE OSC EN

                         LFOSC enable override value

*/
#define PRCM_AON_LFOSC_OVOSCEN                                       0x00200000U
#define PRCM_AON_LFOSC_OVOSCEN_M                                     0x00200000U
#define PRCM_AON_LFOSC_OVOSCEN_S                                     21U
/*

        Field:           OVOSCSTOPEN
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE OSC STOP EN

                         LFOSC STOP enable override value

*/
#define PRCM_AON_LFOSC_OVOSCSTOPEN                                   0x00400000U
#define PRCM_AON_LFOSC_OVOSCSTOPEN_M                                 0x00400000U
#define PRCM_AON_LFOSC_OVOSCSTOPEN_S                                 22U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FSCFG
    Offset name:         PRCM_AON_O_FSCFG
    Relative address:    0x7000
    Description:         FUSE CONFIG

                        config efc ready
    Default Value:       0x00000002

        Field:           SELOVEFCRDY
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE EFC READY

                         '1' selects ov_efc_ready reg

*/
#define PRCM_AON_FSCFG_SELOVEFCRDY                                   0x00000001U
#define PRCM_AON_FSCFG_SELOVEFCRDY_M                                 0x00000001U
#define PRCM_AON_FSCFG_SELOVEFCRDY_S                                 0U
/*

        Field:           OVEFCRDY
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OVERRIDE EFC READY VALUE

*/
#define PRCM_AON_FSCFG_OVEFCRDY                                      0x00000002U
#define PRCM_AON_FSCFG_OVEFCRDY_M                                    0x00000002U
#define PRCM_AON_FSCFG_OVEFCRDY_S                                    1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMCIO
    Offset name:         PRCM_AON_O_PMCIO
    Relative address:    0x7004
    Description:         PMCIO
    Default Value:       0x00000000

        Field:           SOPSTA
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SOP status output from POL sequencer

*/
#define PRCM_AON_PMCIO_SOPSTA_W                                      2U
#define PRCM_AON_PMCIO_SOPSTA_M                                      0x00000003U
#define PRCM_AON_PMCIO_SOPSTA_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BOD
    Offset name:         PRCM_AON_O_BOD
    Relative address:    0x700C
    Description:         BODCTL
    Default Value:       0x04000003

        Field:           COMPEN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     BOD COMPARATOR ENABLE

                         Enable value

*/
#define PRCM_AON_BOD_COMPEN                                          0x00000001U
#define PRCM_AON_BOD_COMPEN_M                                        0x00000001U
#define PRCM_AON_BOD_COMPEN_S                                        0U
/*

        Field:           IPEN
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     IP ENABLE

                         BOD Comparator input Enable value

*/
#define PRCM_AON_BOD_IPEN                                            0x00000002U
#define PRCM_AON_BOD_IPEN_M                                          0x00000002U
#define PRCM_AON_BOD_IPEN_S                                          1U
/*

        Field:           SELOVLOIQ
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECTOR OVERRIDE BOD LOW IQ

                         BOD Comparator low IQ power mode override select

*/
#define PRCM_AON_BOD_SELOVLOIQ                                       0x00000008U
#define PRCM_AON_BOD_SELOVLOIQ_M                                     0x00000008U
#define PRCM_AON_BOD_SELOVLOIQ_S                                     3U
/*

        Field:           OVLOIQ
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE LOW IQ

                         BOD Comparator low IQ power mode override value

*/
#define PRCM_AON_BOD_OVLOIQ                                          0x00000010U
#define PRCM_AON_BOD_OVLOIQ_M                                        0x00000010U
#define PRCM_AON_BOD_OVLOIQ_S                                        4U
/*

        Field:           FSMLOIQ
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM bod low IQ status

*/
#define PRCM_AON_BOD_FSMLOIQ                                         0x00000020U
#define PRCM_AON_BOD_FSMLOIQ_M                                       0x00000020U
#define PRCM_AON_BOD_FSMLOIQ_S                                       5U
/*

        Field:           FSTRIM
        From..to bits:   6...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     BOD fuse trim value

*/
#define PRCM_AON_BOD_FSTRIM_W                                        6U
#define PRCM_AON_BOD_FSTRIM_M                                        0x00000FC0U
#define PRCM_AON_BOD_FSTRIM_S                                        6U
/*

        Field:           SELOVTRIM
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     BOD trim override select

*/
#define PRCM_AON_BOD_SELOVTRIM                                       0x00001000U
#define PRCM_AON_BOD_SELOVTRIM_M                                     0x00001000U
#define PRCM_AON_BOD_SELOVTRIM_S                                     12U
/*

        Field:           OVTRIM
        From..to bits:   13...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     BOD trim override value

*/
#define PRCM_AON_BOD_OVTRIM_W                                        6U
#define PRCM_AON_BOD_OVTRIM_M                                        0x0007E000U
#define PRCM_AON_BOD_OVTRIM_S                                        13U
/*

        Field:           HYSTCTL
        From..to bits:   19...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     BOD hysteresis control

*/
#define PRCM_AON_BOD_HYSTCTL_W                                       2U
#define PRCM_AON_BOD_HYSTCTL_M                                       0x00180000U
#define PRCM_AON_BOD_HYSTCTL_S                                       19U
/*

        Field:           SELOVENPROT
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     select BOD protection enable
                         '1' - select override
                         '0' - select fuse

*/
#define PRCM_AON_BOD_SELOVENPROT                                     0x00200000U
#define PRCM_AON_BOD_SELOVENPROT_M                                   0x00200000U
#define PRCM_AON_BOD_SELOVENPROT_S                                   21U
/*

        Field:           OVENPROT
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for BOD protection enable

*/
#define PRCM_AON_BOD_OVENPROT                                        0x00400000U
#define PRCM_AON_BOD_OVENPROT_M                                      0x00400000U
#define PRCM_AON_BOD_OVENPROT_S                                      22U
/*

        Field:           FSENPROT
        From..to bits:   23...25
        DefaultValue:    0x0
        Access type:     read-only
        Description:     bod protection enable fuse value

*/
#define PRCM_AON_BOD_FSENPROT_W                                      3U
#define PRCM_AON_BOD_FSENPROT_M                                      0x03800000U
#define PRCM_AON_BOD_FSENPROT_S                                      23U
/*

        Field:           BTFDBACKEN
        From..to bits:   26...26
        DefaultValue:    0x1
        Access type:     read-only
        Description:     boot feedback for bod enable status

*/
#define PRCM_AON_BOD_BTFDBACKEN                                      0x04000000U
#define PRCM_AON_BOD_BTFDBACKEN_M                                    0x04000000U
#define PRCM_AON_BOD_BTFDBACKEN_S                                    26U
/*

        Field:           RSTCAUSECLR
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     BOD reset cause clear value
                         Set '1' to this field will automated a pulse to pmu.
                         clear this field to '0' after use.

*/
#define PRCM_AON_BOD_RSTCAUSECLR                                     0x80000000U
#define PRCM_AON_BOD_RSTCAUSECLR_M                                   0x80000000U
#define PRCM_AON_BOD_RSTCAUSECLR_S                                   31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RVMH
    Offset name:         PRCM_AON_O_RVMH
    Relative address:    0x7010
    Description:         RVM HIGH CONTROL
    Default Value:       0x00000003

        Field:           COMPEN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     RVMH COMPARATOR Enable

*/
#define PRCM_AON_RVMH_COMPEN                                         0x00000001U
#define PRCM_AON_RVMH_COMPEN_M                                       0x00000001U
#define PRCM_AON_RVMH_COMPEN_S                                       0U
/*

        Field:           IPEN
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     RVMH Comparator input Enable

*/
#define PRCM_AON_RVMH_IPEN                                           0x00000002U
#define PRCM_AON_RVMH_IPEN_M                                         0x00000002U
#define PRCM_AON_RVMH_IPEN_S                                         1U
/*

        Field:           FSENPROT
        From..to bits:   2...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RVMH Comparator En protection fuse data

*/
#define PRCM_AON_RVMH_FSENPROT_W                                     3U
#define PRCM_AON_RVMH_FSENPROT_M                                     0x0000001CU
#define PRCM_AON_RVMH_FSENPROT_S                                     2U
/*

        Field:           SELOVENPROT
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RVMH Comparator En protection power mode override select (override fuse value)

*/
#define PRCM_AON_RVMH_SELOVENPROT                                    0x00000020U
#define PRCM_AON_RVMH_SELOVENPROT_M                                  0x00000020U
#define PRCM_AON_RVMH_SELOVENPROT_S                                  5U
/*

        Field:           OVENPROT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RVMH Comparator En protection mode override value  (Override the fuse value)
                         1 - RVM Hi violation will NOT be detected by device (PMU.POL)
                         1 - RVM Hi violation will be detected by device (PMU.POL)

*/
#define PRCM_AON_RVMH_OVENPROT                                       0x00000040U
#define PRCM_AON_RVMH_OVENPROT_M                                     0x00000040U
#define PRCM_AON_RVMH_OVENPROT_S                                     6U
/*

        Field:           SELOVLOIQ
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RVMH Comparator low IQ power mode override select

*/
#define PRCM_AON_RVMH_SELOVLOIQ                                      0x00000080U
#define PRCM_AON_RVMH_SELOVLOIQ_M                                    0x00000080U
#define PRCM_AON_RVMH_SELOVLOIQ_S                                    7U
/*

        Field:           OVLOIQ
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RVMH Comparator low IQ power mode override value

*/
#define PRCM_AON_RVMH_OVLOIQ                                         0x00000100U
#define PRCM_AON_RVMH_OVLOIQ_M                                       0x00000100U
#define PRCM_AON_RVMH_OVLOIQ_S                                       8U
/*

        Field:           FSMLOIQ
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM rvml lo IQ status

*/
#define PRCM_AON_RVMH_FSMLOIQ                                        0x00000200U
#define PRCM_AON_RVMH_FSMLOIQ_M                                      0x00000200U
#define PRCM_AON_RVMH_FSMLOIQ_S                                      9U
/*

        Field:           HYSTCTL
        From..to bits:   10...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RVMH hysteresis control

*/
#define PRCM_AON_RVMH_HYSTCTL_W                                      2U
#define PRCM_AON_RVMH_HYSTCTL_M                                      0x00000C00U
#define PRCM_AON_RVMH_HYSTCTL_S                                      10U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RVML
    Offset name:         PRCM_AON_O_RVML
    Relative address:    0x7014
    Description:         RVM LOW CONTROL
    Default Value:       0x00000003

        Field:           COMPEN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     RVML Enable override value

*/
#define PRCM_AON_RVML_COMPEN                                         0x00000001U
#define PRCM_AON_RVML_COMPEN_M                                       0x00000001U
#define PRCM_AON_RVML_COMPEN_S                                       0U
/*

        Field:           IPEN
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     RVML Comparator input Enable override value

*/
#define PRCM_AON_RVML_IPEN                                           0x00000002U
#define PRCM_AON_RVML_IPEN_M                                         0x00000002U
#define PRCM_AON_RVML_IPEN_S                                         1U
/*

        Field:           FSENPROT
        From..to bits:   2...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RVML Comparator En protection fuse data

*/
#define PRCM_AON_RVML_FSENPROT_W                                     3U
#define PRCM_AON_RVML_FSENPROT_M                                     0x0000001CU
#define PRCM_AON_RVML_FSENPROT_S                                     2U
/*

        Field:           SELOVENPROT
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RVML Comparator En protection power mode override select (override fuse value)

*/
#define PRCM_AON_RVML_SELOVENPROT                                    0x00000020U
#define PRCM_AON_RVML_SELOVENPROT_M                                  0x00000020U
#define PRCM_AON_RVML_SELOVENPROT_S                                  5U
/*

        Field:           OVENPROT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RVML Comparator En protection mode override value  (Override the fuse value)
                         1 - RVM Low violation will NOT be detected by device (PMU.POL)
                         1 - RVM Low violation will be detected by device (PMU.POL)

*/
#define PRCM_AON_RVML_OVENPROT                                       0x00000040U
#define PRCM_AON_RVML_OVENPROT_M                                     0x00000040U
#define PRCM_AON_RVML_OVENPROT_S                                     6U
/*

        Field:           SELOVLOIQ
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RVML Comparator low IQ power mode override select

*/
#define PRCM_AON_RVML_SELOVLOIQ                                      0x00000080U
#define PRCM_AON_RVML_SELOVLOIQ_M                                    0x00000080U
#define PRCM_AON_RVML_SELOVLOIQ_S                                    7U
/*

        Field:           OVLOIQ
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RVML Comparator low IQ power mode override value

*/
#define PRCM_AON_RVML_OVLOIQ                                         0x00000100U
#define PRCM_AON_RVML_OVLOIQ_M                                       0x00000100U
#define PRCM_AON_RVML_OVLOIQ_S                                       8U
/*

        Field:           FSMLOIQ
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM rvml lo IQ status

*/
#define PRCM_AON_RVML_FSMLOIQ                                        0x00000200U
#define PRCM_AON_RVML_FSMLOIQ_M                                      0x00000200U
#define PRCM_AON_RVML_FSMLOIQ_S                                      9U
/*

        Field:           HYSTCTL
        From..to bits:   10...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RVMH hysteresis control

*/
#define PRCM_AON_RVML_HYSTCTL_W                                      2U
#define PRCM_AON_RVML_HYSTCTL_M                                      0x00000C00U
#define PRCM_AON_RVML_HYSTCTL_S                                      10U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PSCON
    Offset name:         PRCM_AON_O_PSCON
    Relative address:    0x7018
    Description:         PSCON MEMORY DELAY CONTROL
    Default Value:       0x00001108

        Field:           DLYPONPGOOD
        From..to bits:   0...4
        DefaultValue:    0x8
        Access type:     read-write
        Description:     DELAY BETWEEN PON to PGOOD

                         0000:0.8us; 0001:1.6us; 0010:2.4us; 0011:3.2us;...;1001:8us;1111:12.8us

*/
#define PRCM_AON_PSCON_DLYPONPGOOD_W                                 5U
#define PRCM_AON_PSCON_DLYPONPGOOD_M                                 0x0000001FU
#define PRCM_AON_PSCON_DLYPONPGOOD_S                                 0U
/*

        Field:           DLYAONAGOOD
        From..to bits:   5...8
        DefaultValue:    0x8
        Access type:     read-write
        Description:     DELAY BETWEEN AON to AGOOD

                         0000:0.8us; 0001:1.6us; 0010:2.4us; 0011:3.2us;...;1001:8us;1111:12.8us

*/
#define PRCM_AON_PSCON_DLYAONAGOOD_W                                 4U
#define PRCM_AON_PSCON_DLYAONAGOOD_M                                 0x000001E0U
#define PRCM_AON_PSCON_DLYAONAGOOD_S                                 5U
/*

        Field:           DLYRTAONGOOD
        From..to bits:   9...12
        DefaultValue:    0x8
        Access type:     read-write
        Description:     DELAY BETWEEn RTAOn to RTAGOOD

                         0000:0.8us; 0001:1.6us; 0010:3us; 0011:3.2us;...;1001:8us;1111:12.8us

*/
#define PRCM_AON_PSCON_DLYRTAONGOOD_W                                4U
#define PRCM_AON_PSCON_DLYRTAONGOOD_M                                0x00001E00U
#define PRCM_AON_PSCON_DLYRTAONGOOD_S                                9U
/*

        Field:           DLYPGOODRETUP
        From..to bits:   13...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DELAY BETWEEN PGOOD to RET UP

                         0000:0.8us; 0001:1.6us; 0010:2.4us; 0011:3.2us;...;1001:8us;1111:12.8us

*/
#define PRCM_AON_PSCON_DLYPGOODRETUP_W                               5U
#define PRCM_AON_PSCON_DLYPGOODRETUP_M                               0x0003E000U
#define PRCM_AON_PSCON_DLYPGOODRETUP_S                               13U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGAPEN
    Offset name:         PRCM_AON_O_DBGAPEN
    Relative address:    0x701C
    Description:         digital bandgap enable register
    Default Value:       0x00000003

        Field:           FSMEN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-only
        Description:     FSM DIGBG enable status

*/
#define PRCM_AON_DBGAPEN_FSMEN                                       0x00000001U
#define PRCM_AON_DBGAPEN_FSMEN_M                                     0x00000001U
#define PRCM_AON_DBGAPEN_FSMEN_S                                     0U
/*

        Field:           OVEN
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     override value for DBGAP enable

*/
#define PRCM_AON_DBGAPEN_OVEN                                        0x00000002U
#define PRCM_AON_DBGAPEN_OVEN_M                                      0x00000002U
#define PRCM_AON_DBGAPEN_OVEN_S                                      1U
/*

        Field:           SELOVEN
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE ENABLE

                         1: select override value for DBGAP enable : 0: DBGAP enable according to FSM

*/
#define PRCM_AON_DBGAPEN_SELOVEN                                     0x00000004U
#define PRCM_AON_DBGAPEN_SELOVEN_M                                   0x00000004U
#define PRCM_AON_DBGAPEN_SELOVEN_S                                   2U
/*

        Field:           ISCONST1
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS CONSTANT 1

                         1: keep the DBGAP on during sleep BG enable and SW enable
                         0: allow hibernate

*/
#define PRCM_AON_DBGAPEN_ISCONST1                                    0x00000008U
#define PRCM_AON_DBGAPEN_ISCONST1_M                                  0x00000008U
#define PRCM_AON_DBGAPEN_ISCONST1_S                                  3U
/*

        Field:           ISCONST0
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IS CONSTANT 0

                         1: keep the DBGAP off during sleep BG disable and SW disable
                         0: allow hibernate

*/
#define PRCM_AON_DBGAPEN_ISCONST0                                    0x00000010U
#define PRCM_AON_DBGAPEN_ISCONST0_M                                  0x00000010U
#define PRCM_AON_DBGAPEN_ISCONST0_S                                  4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OVDBGAP1
    Offset name:         PRCM_AON_O_OVDBGAP1
    Relative address:    0x7020
    Description:         DBGAP override register
    Default Value:       0x00000000

        Field:           OVCURVTRIM
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for DBGAP curve trim : used until fuse chain or when selected

*/
#define PRCM_AON_OVDBGAP1_OVCURVTRIM_W                               7U
#define PRCM_AON_OVDBGAP1_OVCURVTRIM_M                               0x0000007FU
#define PRCM_AON_OVDBGAP1_OVCURVTRIM_S                               0U
/*

        Field:           SELOVCURVTRIM
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE CURVE VTRIM

                         1: select override for curve trim : 0: select curve trim from fuse

*/
#define PRCM_AON_OVDBGAP1_SELOVCURVTRIM                              0x00000080U
#define PRCM_AON_OVDBGAP1_SELOVCURVTRIM_M                            0x00000080U
#define PRCM_AON_OVDBGAP1_SELOVCURVTRIM_S                            7U
/*

        Field:           FSCURVTRIM2
        From..to bits:   8...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FS 2nd insertion curve

*/
#define PRCM_AON_OVDBGAP1_FSCURVTRIM2_W                              7U
#define PRCM_AON_OVDBGAP1_FSCURVTRIM2_M                              0x00007F00U
#define PRCM_AON_OVDBGAP1_FSCURVTRIM2_S                              8U
/*

        Field:           FSCURVTRIM1
        From..to bits:   15...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FS 1st insertion curve

*/
#define PRCM_AON_OVDBGAP1_FSCURVTRIM1_W                              7U
#define PRCM_AON_OVDBGAP1_FSCURVTRIM1_M                              0x003F8000U
#define PRCM_AON_OVDBGAP1_FSCURVTRIM1_S                              15U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OVDBGAP2
    Offset name:         PRCM_AON_O_OVDBGAP2
    Relative address:    0x7024
    Description:         DBGAP override register
    Default Value:       0x00000000

        Field:           OVVMAGTRIM
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for DBGAP mag trim : used until fuse chain or when selected

*/
#define PRCM_AON_OVDBGAP2_OVVMAGTRIM_W                               8U
#define PRCM_AON_OVDBGAP2_OVVMAGTRIM_M                               0x000000FFU
#define PRCM_AON_OVDBGAP2_OVVMAGTRIM_S                               0U
/*

        Field:           SELOVVMAGTRIM
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE MAG TRIM

                         1: select override for mag trim : 0: select mag trim from fuse

*/
#define PRCM_AON_OVDBGAP2_SELOVVMAGTRIM                              0x00000100U
#define PRCM_AON_OVDBGAP2_SELOVVMAGTRIM_M                            0x00000100U
#define PRCM_AON_OVDBGAP2_SELOVVMAGTRIM_S                            8U
/*

        Field:           FSVMAGTRIM1
        From..to bits:   9...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     fuse value for magnitude 1st insertion trim

*/
#define PRCM_AON_OVDBGAP2_FSVMAGTRIM1_W                              8U
#define PRCM_AON_OVDBGAP2_FSVMAGTRIM1_M                              0x0001FE00U
#define PRCM_AON_OVDBGAP2_FSVMAGTRIM1_S                              9U
/*

        Field:           FSVMAGTRIM2
        From..to bits:   17...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     fuse value for magnitude 2nd insertion trim

*/
#define PRCM_AON_OVDBGAP2_FSVMAGTRIM2_W                              8U
#define PRCM_AON_OVDBGAP2_FSVMAGTRIM2_M                              0x01FE0000U
#define PRCM_AON_OVDBGAP2_FSVMAGTRIM2_S                              17U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SLPREF
    Offset name:         PRCM_AON_O_SLPREF
    Relative address:    0x7028
    Description:         SLEEP REFERENCE
    Default Value:       0x00000360

        Field:           SELOVDBGIREFEN
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE DBGAP IREF ENABLE

*/
#define PRCM_AON_SLPREF_SELOVDBGIREFEN                               0x00000010U
#define PRCM_AON_SLPREF_SELOVDBGIREFEN_M                             0x00000010U
#define PRCM_AON_SLPREF_SELOVDBGIREFEN_S                             4U
/*

        Field:           OVDBGIREFEN
        From..to bits:   5...5
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OVERRIDE DBGAP IREF EN

*/
#define PRCM_AON_SLPREF_OVDBGIREFEN                                  0x00000020U
#define PRCM_AON_SLPREF_OVDBGIREFEN_M                                0x00000020U
#define PRCM_AON_SLPREF_OVDBGIREFEN_S                                5U
/*

        Field:           FSMDIGBGIREFEN
        From..to bits:   6...6
        DefaultValue:    0x1
        Access type:     read-only
        Description:     FSM digital band gap iref enable status

*/
#define PRCM_AON_SLPREF_FSMDIGBGIREFEN                               0x00000040U
#define PRCM_AON_SLPREF_FSMDIGBGIREFEN_M                             0x00000040U
#define PRCM_AON_SLPREF_FSMDIGBGIREFEN_S                             6U
/*

        Field:           SELOVLKSWON
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE LEAKAGE SWITCH ON

                         1: select override value for the DBGAP switch on : 0: prcm_leakage_sw_on controlled by FSM

*/
#define PRCM_AON_SLPREF_SELOVLKSWON                                  0x00000080U
#define PRCM_AON_SLPREF_SELOVLKSWON_M                                0x00000080U
#define PRCM_AON_SLPREF_SELOVLKSWON_S                                7U
/*

        Field:           OVLKSWON
        From..to bits:   8...8
        DefaultValue:    0x1
        Access type:     read-write
        Description:     override value for DBGAP switch en

*/
#define PRCM_AON_SLPREF_OVLKSWON                                     0x00000100U
#define PRCM_AON_SLPREF_OVLKSWON_M                                   0x00000100U
#define PRCM_AON_SLPREF_OVLKSWON_S                                   8U
/*

        Field:           FDBGENCAPSW
        From..to bits:   9...9
        DefaultValue:    0x1
        Access type:     read-only
        Description:     FSM digital bad gap enable cap status

*/
#define PRCM_AON_SLPREF_FDBGENCAPSW                                  0x00000200U
#define PRCM_AON_SLPREF_FDBGENCAPSW_M                                0x00000200U
#define PRCM_AON_SLPREF_FDBGENCAPSW_S                                9U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGGM
    Offset name:         PRCM_AON_O_DBGGM
    Relative address:    0x702C
    Description:         Digital Band Gap GM

                        GMBIAS config register
    Default Value:       0x00070040

        Field:           OVGMITRIM
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for dbgap_gmi_trim

*/
#define PRCM_AON_DBGGM_OVGMITRIM_W                                   5U
#define PRCM_AON_DBGGM_OVGMITRIM_M                                   0x0000001FU
#define PRCM_AON_DBGGM_OVGMITRIM_S                                   0U
/*

        Field:           SELOVGMITRIM
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE GMI TRIM

                         1: select override value for dbgap_gmi_trim : 0: fuse value

*/
#define PRCM_AON_DBGGM_SELOVGMITRIM                                  0x00000020U
#define PRCM_AON_DBGGM_SELOVGMITRIM_M                                0x00000020U
#define PRCM_AON_DBGGM_SELOVGMITRIM_S                                5U
/*

        Field:           FSTRIM1
        From..to bits:   6...10
        DefaultValue:    0x1
        Access type:     read-only
        Description:     fuse value for gmi 1st insertion trim

                         Trim for GMBIAS IREF current

*/
#define PRCM_AON_DBGGM_FSTRIM1_W                                     5U
#define PRCM_AON_DBGGM_FSTRIM1_M                                     0x000007C0U
#define PRCM_AON_DBGGM_FSTRIM1_S                                     6U
/*

        Field:           FSTRIM2
        From..to bits:   11...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     fuse value for gmi 2nd insertion trim

*/
#define PRCM_AON_DBGGM_FSTRIM2_W                                     5U
#define PRCM_AON_DBGGM_FSTRIM2_M                                     0x0000F800U
#define PRCM_AON_DBGGM_FSTRIM2_S                                     11U
/*

        Field:           ENBIAS
        From..to bits:   16...16
        DefaultValue:    0x1
        Access type:     read-write
        Description:     dedicated enable for GMBIAS module

*/
#define PRCM_AON_DBGGM_ENBIAS                                        0x00010000U
#define PRCM_AON_DBGGM_ENBIAS_M                                      0x00010000U
#define PRCM_AON_DBGGM_ENBIAS_S                                      16U
/*

        Field:           ENBIASSTRTU
        From..to bits:   17...17
        DefaultValue:    0x1
        Access type:     read-write
        Description:     ENABLE BOAS STARTUP

                         Startup control from PRCM to power-up GMBIAS.

*/
#define PRCM_AON_DBGGM_ENBIASSTRTU                                   0x00020000U
#define PRCM_AON_DBGGM_ENBIASSTRTU_M                                 0x00020000U
#define PRCM_AON_DBGGM_ENBIASSTRTU_S                                 17U
/*

        Field:           ENBIASTRIM
        From..to bits:   18...18
        DefaultValue:    0x1
        Access type:     read-write
        Description:     ENABLE BIAS TRIM

                         Enable Trim to GMBIAS module

*/
#define PRCM_AON_DBGGM_ENBIASTRIM                                    0x00040000U
#define PRCM_AON_DBGGM_ENBIASTRIM_M                                  0x00040000U
#define PRCM_AON_DBGGM_ENBIASTRIM_S                                  18U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMURTRIM
    Offset name:         PRCM_AON_O_PMURTRIM
    Relative address:    0x7030
    Description:         PMU RTRIM
    Default Value:       0x00000000

        Field:           OV
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE value for PMU RTRIM

*/
#define PRCM_AON_PMURTRIM_OV_W                                       5U
#define PRCM_AON_PMURTRIM_OV_M                                       0x0000001FU
#define PRCM_AON_PMURTRIM_OV_S                                       0U
/*

        Field:           SELOV
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE

*/
#define PRCM_AON_PMURTRIM_SELOV                                      0x00000020U
#define PRCM_AON_PMURTRIM_SELOV_M                                    0x00000020U
#define PRCM_AON_PMURTRIM_SELOV_S                                    5U
/*

        Field:           FSDBGAP1
        From..to bits:   6...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     fuse value for resistor trim 1st insertion

*/
#define PRCM_AON_PMURTRIM_FSDBGAP1_W                                 5U
#define PRCM_AON_PMURTRIM_FSDBGAP1_M                                 0x000007C0U
#define PRCM_AON_PMURTRIM_FSDBGAP1_S                                 6U
/*

        Field:           FSDBGAP2
        From..to bits:   11...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     fuse value for resistor trim 2st insertion

*/
#define PRCM_AON_PMURTRIM_FSDBGAP2_W                                 5U
#define PRCM_AON_PMURTRIM_FSDBGAP2_M                                 0x0000F800U
#define PRCM_AON_PMURTRIM_FSDBGAP2_S                                 11U


/*-----------------------------------REGISTER------------------------------------
    Register name:       VNWACTL
    Offset name:         PRCM_AON_O_VNWACTL
    Relative address:    0x7034
    Description:         VNWA CONTROL
    Default Value:       0x00000000

        Field:           SELOVTPEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE TOP ENABLE

*/
#define PRCM_AON_VNWACTL_SELOVTPEN                                   0x00000001U
#define PRCM_AON_VNWACTL_SELOVTPEN_M                                 0x00000001U
#define PRCM_AON_VNWACTL_SELOVTPEN_S                                 0U
/*

        Field:           OVTOPEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE TOP ENABLE

*/
#define PRCM_AON_VNWACTL_OVTOPEN                                     0x00000002U
#define PRCM_AON_VNWACTL_OVTOPEN_M                                   0x00000002U
#define PRCM_AON_VNWACTL_OVTOPEN_S                                   1U
/*

        Field:           OVVDDSEN
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE VDD ENABLE

*/
#define PRCM_AON_VNWACTL_OVVDDSEN                                    0x00000004U
#define PRCM_AON_VNWACTL_OVVDDSEN_M                                  0x00000004U
#define PRCM_AON_VNWACTL_OVVDDSEN_S                                  2U
/*

        Field:           SELOVSRENSCNMOD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE SRAM ENABLE SCREEN MODE

*/
#define PRCM_AON_VNWACTL_SELOVSRENSCNMOD                             0x00000008U
#define PRCM_AON_VNWACTL_SELOVSRENSCNMOD_M                           0x00000008U
#define PRCM_AON_VNWACTL_SELOVSRENSCNMOD_S                           3U
/*

        Field:           OVSRENSCRNMOD
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE SRAM ENABLE SCREEN MODE

*/
#define PRCM_AON_VNWACTL_OVSRENSCRNMOD                               0x00000010U
#define PRCM_AON_VNWACTL_OVSRENSCRNMOD_M                             0x00000010U
#define PRCM_AON_VNWACTL_OVSRENSCRNMOD_S                             4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SRAMKATRIM
    Offset name:         PRCM_AON_O_SRAMKATRIM
    Relative address:    0x7038
    Description:         SRAM KA trim register
    Default Value:       0x000012C0

        Field:           RTA
        From..to bits:   0...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SRAM KA trim value in RTA mode - default mode

*/
#define PRCM_AON_SRAMKATRIM_RTA_W                                    6U
#define PRCM_AON_SRAMKATRIM_RTA_M                                    0x0000003FU
#define PRCM_AON_SRAMKATRIM_RTA_S                                    0U
/*

        Field:           NORTA
        From..to bits:   6...11
        DefaultValue:    0xB
        Access type:     read-write
        Description:     SRAM KA trim value in NON RTA mode 0.6v : FSM can move memories to NON RTA mode when feature is enabled and WLAN in OFF : When WLAN is ON the BRG HP memories don't support such low array value

*/
#define PRCM_AON_SRAMKATRIM_NORTA_W                                  6U
#define PRCM_AON_SRAMKATRIM_NORTA_M                                  0x00000FC0U
#define PRCM_AON_SRAMKATRIM_NORTA_S                                  6U
/*

        Field:           SLPNORTAMOD
        From..to bits:   12...12
        DefaultValue:    0x1
        Access type:     read-write
        Description:     SLEEP NO RTA MODE

                          when '1' chooses  the no rta mode trim value

*/
#define PRCM_AON_SRAMKATRIM_SLPNORTAMOD                              0x00001000U
#define PRCM_AON_SRAMKATRIM_SLPNORTAMOD_M                            0x00001000U
#define PRCM_AON_SRAMKATRIM_SLPNORTAMOD_S                            12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       VAL
    Offset name:         PRCM_AON_O_VAL
    Relative address:    0x7040
    Description:         VALUE
    Default Value:       0x00000000

        Field:           SPARE
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SPARE REG for SRAM LDO

*/
#define PRCM_AON_VAL_SPARE_W                                         7U
#define PRCM_AON_VAL_SPARE_M                                         0x0000007FU
#define PRCM_AON_VAL_SPARE_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SRAMKAEN
    Offset name:         PRCM_AON_O_SRAMKAEN
    Relative address:    0x7044
    Description:         SRAM KA ENABLE
    Default Value:       0x00000002

        Field:           FSM
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     status of final SRAM KA enable

*/
#define PRCM_AON_SRAMKAEN_FSM                                        0x00000001U
#define PRCM_AON_SRAMKAEN_FSM_M                                      0x00000001U
#define PRCM_AON_SRAMKAEN_FSM_S                                      0U
/*

        Field:           OV
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     override value for SRAM KA

*/
#define PRCM_AON_SRAMKAEN_OV                                         0x00000002U
#define PRCM_AON_SRAMKAEN_OV_M                                       0x00000002U
#define PRCM_AON_SRAMKAEN_OV_S                                       1U
/*

        Field:           SELOV
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE

                         1: select override value for SRAM KA enable : 0: SRAM KA enable from FSM

*/
#define PRCM_AON_SRAMKAEN_SELOV                                      0x00000004U
#define PRCM_AON_SRAMKAEN_SELOV_M                                    0x00000004U
#define PRCM_AON_SRAMKAEN_SELOV_S                                    2U
/*

        Field:           TLOAD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable test load for SRAM keep alive

*/
#define PRCM_AON_SRAMKAEN_TLOAD                                      0x00000008U
#define PRCM_AON_SRAMKAEN_TLOAD_M                                    0x00000008U
#define PRCM_AON_SRAMKAEN_TLOAD_S                                    3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DLDOEN
    Offset name:         PRCM_AON_O_DLDOEN
    Relative address:    0x7048
    Description:         DIG LDO ENABLE
    Default Value:       0x00000003

        Field:           FSM
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-only
        Description:     status of FSM DIG LDO enable

*/
#define PRCM_AON_DLDOEN_FSM                                          0x00000001U
#define PRCM_AON_DLDOEN_FSM_M                                        0x00000001U
#define PRCM_AON_DLDOEN_FSM_S                                        0U
/*

        Field:           OV
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     override value for DIG LDO

*/
#define PRCM_AON_DLDOEN_OV                                           0x00000002U
#define PRCM_AON_DLDOEN_OV_M                                         0x00000002U
#define PRCM_AON_DLDOEN_OV_S                                         1U
/*

        Field:           SELOV
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1: select override value for DIG LDO enable : 0: DIG LDO enable from FSM

*/
#define PRCM_AON_DLDOEN_SELOV                                        0x00000004U
#define PRCM_AON_DLDOEN_SELOV_M                                      0x00000004U
#define PRCM_AON_DLDOEN_SELOV_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DLDOVTRIM
    Offset name:         PRCM_AON_O_DLDOVTRIM
    Relative address:    0x704C
    Description:         override register for DIG LDO TRIM
    Default Value:       0x00000007

        Field:           OPP1
        From..to bits:   0...5
        DefaultValue:    0x7
        Access type:     read-write
        Description:     digital ldo vtrim value 1.1V

*/
#define PRCM_AON_DLDOVTRIM_OPP1_W                                    6U
#define PRCM_AON_DLDOVTRIM_OPP1_M                                    0x0000003FU
#define PRCM_AON_DLDOVTRIM_OPP1_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DKAEN
    Offset name:         PRCM_AON_O_DKAEN
    Relative address:    0x7050
    Description:         DIG KA ENABLE
    Default Value:       0x00000000

        Field:           FSM
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     status of FSM DIG KA enable

*/
#define PRCM_AON_DKAEN_FSM                                           0x00000001U
#define PRCM_AON_DKAEN_FSM_M                                         0x00000001U
#define PRCM_AON_DKAEN_FSM_S                                         0U
/*

        Field:           OV
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for DIG KA

*/
#define PRCM_AON_DKAEN_OV                                            0x00000002U
#define PRCM_AON_DKAEN_OV_M                                          0x00000002U
#define PRCM_AON_DKAEN_OV_S                                          1U
/*

        Field:           SELOV
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1: select override value for DIG KA enable : 0: DIG KA enable from FSM

*/
#define PRCM_AON_DKAEN_SELOV                                         0x00000004U
#define PRCM_AON_DKAEN_SELOV_M                                       0x00000004U
#define PRCM_AON_DKAEN_SELOV_S                                       2U
/*

        Field:           TLOAD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable test load for DIG keep alive

*/
#define PRCM_AON_DKAEN_TLOAD                                         0x00000008U
#define PRCM_AON_DKAEN_TLOAD_M                                       0x00000008U
#define PRCM_AON_DKAEN_TLOAD_S                                       3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DKATRIM
    Offset name:         PRCM_AON_O_DKATRIM
    Relative address:    0x7054
    Description:         DIG KA trim register
    Default Value:       0x00000019

        Field:           VAL
        From..to bits:   0...5
        DefaultValue:    0x19
        Access type:     read-write
        Description:     DIGITAL KEEP ALIVE VTRIM VALUE

*/
#define PRCM_AON_DKATRIM_VAL_W                                       6U
#define PRCM_AON_DKATRIM_VAL_M                                       0x0000003FU
#define PRCM_AON_DKATRIM_VAL_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DLDOLPMOD
    Offset name:         PRCM_AON_O_DLDOLPMOD
    Relative address:    0x7058
    Description:         DIGITAL LDO LOW POWER MODE

                        Enable Low Power Mode for DIGLDO register
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     set DIG LDO LDO mode

*/
#define PRCM_AON_DLDOLPMOD_EN                                        0x00000001U
#define PRCM_AON_DLDOLPMOD_EN_M                                      0x00000001U
#define PRCM_AON_DLDOLPMOD_EN_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DLDOCFG
    Offset name:         PRCM_AON_O_DLDOCFG
    Relative address:    0x705C
    Description:         DIGITAL LDO CONFIG
    Default Value:       0x0000023E

        Field:           TLOADEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TEST LOAD ENABLE

                         Enable test load for DIG LDO

*/
#define PRCM_AON_DLDOCFG_TLOADEN                                     0x00000001U
#define PRCM_AON_DLDOCFG_TLOADEN_M                                   0x00000001U
#define PRCM_AON_DLDOCFG_TLOADEN_S                                   0U
/*

        Field:           SCPROTEN
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     SHORT CIRCUIT PROTECT ENABLE

                         Enable short circuit protection for DIG LDO

*/
#define PRCM_AON_DLDOCFG_SCPROTEN                                    0x00000002U
#define PRCM_AON_DLDOCFG_SCPROTEN_M                                  0x00000002U
#define PRCM_AON_DLDOCFG_SCPROTEN_S                                  1U
/*

        Field:           SCITRIM
        From..to bits:   2...3
        DefaultValue:    0x3
        Access type:     read-write
        Description:     Short circuit current trim bits for DIG LDO

*/
#define PRCM_AON_DLDOCFG_SCITRIM_W                                   2U
#define PRCM_AON_DLDOCFG_SCITRIM_M                                   0x0000000CU
#define PRCM_AON_DLDOCFG_SCITRIM_S                                   2U
/*

        Field:           IQTRIM
        From..to bits:   4...5
        DefaultValue:    0x3
        Access type:     read-write
        Description:     Quiescent current trim bits for DIG LDO

*/
#define PRCM_AON_DLDOCFG_IQTRIM_W                                    2U
#define PRCM_AON_DLDOCFG_IQTRIM_M                                    0x00000030U
#define PRCM_AON_DLDOCFG_IQTRIM_S                                    4U
/*

        Field:           ENINRSHLIM
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable Inrush Current Limit Mask

*/
#define PRCM_AON_DLDOCFG_ENINRSHLIM                                  0x00000040U
#define PRCM_AON_DLDOCFG_ENINRSHLIM_M                                0x00000040U
#define PRCM_AON_DLDOCFG_ENINRSHLIM_S                                6U
/*

        Field:           SELENINRSHLIM
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Select for S/W Enabling the Inrush Current Limit Mask

*/
#define PRCM_AON_DLDOCFG_SELENINRSHLIM                               0x00000080U
#define PRCM_AON_DLDOCFG_SELENINRSHLIM_M                             0x00000080U
#define PRCM_AON_DLDOCFG_SELENINRSHLIM_S                             7U
/*

        Field:           SUBREGEN
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SUB REGULATION ENABLE

                         Sub Regulation switch from RBYR TO LDO

*/
#define PRCM_AON_DLDOCFG_SUBREGEN                                    0x00000100U
#define PRCM_AON_DLDOCFG_SUBREGEN_M                                  0x00000100U
#define PRCM_AON_DLDOCFG_SUBREGEN_S                                  8U
/*

        Field:           IQTRIMINRSH
        From..to bits:   9...10
        DefaultValue:    0x1
        Access type:     read-write
        Description:     IQ TRIM INRUSH

                         Value of IQ TRIM selected Dynamically by H/W on exit sleep. Default = 0x1

*/
#define PRCM_AON_DLDOCFG_IQTRIMINRSH_W                               2U
#define PRCM_AON_DLDOCFG_IQTRIMINRSH_M                               0x00000600U
#define PRCM_AON_DLDOCFG_IQTRIMINRSH_S                               9U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RVMTRIMCTL
    Offset name:         PRCM_AON_O_RVMTRIMCTL
    Relative address:    0x7060
    Description:         RVM TRIM CONTROL
    Default Value:       0x00000000

        Field:           SELOVRVMHTRIM
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE RVMH TRIM

                         '1' uses ov input
                         '0' uses fs input

*/
#define PRCM_AON_RVMTRIMCTL_SELOVRVMHTRIM                            0x00000001U
#define PRCM_AON_RVMTRIMCTL_SELOVRVMHTRIM_M                          0x00000001U
#define PRCM_AON_RVMTRIMCTL_SELOVRVMHTRIM_S                          0U
/*

        Field:           OV
        From..to bits:   1...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     defines override value for rvmh fuse

*/
#define PRCM_AON_RVMTRIMCTL_OV_W                                     6U
#define PRCM_AON_RVMTRIMCTL_OV_M                                     0x0000007EU
#define PRCM_AON_RVMTRIMCTL_OV_S                                     1U
/*

        Field:           SELOVFSM
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE FSM

                         '1' uses ov input
                         '0' uses fsm input

*/
#define PRCM_AON_RVMTRIMCTL_SELOVFSM                                 0x00000080U
#define PRCM_AON_RVMTRIMCTL_SELOVFSM_M                               0x00000080U
#define PRCM_AON_RVMTRIMCTL_SELOVFSM_S                               7U
/*

        Field:           OVFSM
        From..to bits:   8...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE FSM

                         defines override value for rvml fsm

*/
#define PRCM_AON_RVMTRIMCTL_OVFSM_W                                  2U
#define PRCM_AON_RVMTRIMCTL_OVFSM_M                                  0x00000300U
#define PRCM_AON_RVMTRIMCTL_OVFSM_S                                  8U
/*

        Field:           SELOVRVMLTRIM
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE RVML TRIM

                         '1' uses ov input
                         '0' uses fs input

*/
#define PRCM_AON_RVMTRIMCTL_SELOVRVMLTRIM                            0x00000400U
#define PRCM_AON_RVMTRIMCTL_SELOVRVMLTRIM_M                          0x00000400U
#define PRCM_AON_RVMTRIMCTL_SELOVRVMLTRIM_S                          10U
/*

        Field:           RVMRSTCAUSCLR
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RVM RESET CAUSE CLEAR

                         Set '1' to this field will automated a pulse to pmu.
                         clear this field to '0' after use.

*/
#define PRCM_AON_RVMTRIMCTL_RVMRSTCAUSCLR                            0x80000000U
#define PRCM_AON_RVMTRIMCTL_RVMRSTCAUSCLR_M                          0x80000000U
#define PRCM_AON_RVMTRIMCTL_RVMRSTCAUSCLR_S                          31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RVMTRIMPMUSTA
    Offset name:         PRCM_AON_O_RVMTRIMPMUSTA
    Relative address:    0x7064
    Description:         RVM TRIM PMU STATUS
    Default Value:       0x00000000

        Field:           RVMH
        From..to bits:   0...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RVMH trim status value to pmu

*/
#define PRCM_AON_RVMTRIMPMUSTA_RVMH_W                                6U
#define PRCM_AON_RVMTRIMPMUSTA_RVMH_M                                0x0000003FU
#define PRCM_AON_RVMTRIMPMUSTA_RVMH_S                                0U
/*

        Field:           FSRVMH
        From..to bits:   6...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RVMH fuse trim value

*/
#define PRCM_AON_RVMTRIMPMUSTA_FSRVMH_W                              6U
#define PRCM_AON_RVMTRIMPMUSTA_FSRVMH_M                              0x00000FC0U
#define PRCM_AON_RVMTRIMPMUSTA_FSRVMH_S                              6U
/*

        Field:           RVML
        From..to bits:   12...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RVML trim status value to pmu

*/
#define PRCM_AON_RVMTRIMPMUSTA_RVML_W                                7U
#define PRCM_AON_RVMTRIMPMUSTA_RVML_M                                0x0007F000U
#define PRCM_AON_RVMTRIMPMUSTA_RVML_S                                12U
/*

        Field:           FSRVML
        From..to bits:   19...25
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RVML fuse trim value

*/
#define PRCM_AON_RVMTRIMPMUSTA_FSRVML_W                              7U
#define PRCM_AON_RVMTRIMPMUSTA_FSRVML_M                              0x03F80000U
#define PRCM_AON_RVMTRIMPMUSTA_FSRVML_S                              19U
/*

        Field:           FSMRVML
        From..to bits:   26...27
        DefaultValue:    0x0
        Access type:     read-only
        Description:     status of FSM RVML TRIM value

*/
#define PRCM_AON_RVMTRIMPMUSTA_FSMRVML_W                             2U
#define PRCM_AON_RVMTRIMPMUSTA_FSMRVML_M                             0x0C000000U
#define PRCM_AON_RVMTRIMPMUSTA_FSMRVML_S                             26U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RVMLTRIMCTL
    Offset name:         PRCM_AON_O_RVMLTRIMCTL
    Relative address:    0x7068
    Description:         RVML TRIM CONTROL
    Default Value:       0x00000000

        Field:           OVOPP1
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE OPP1

                         defines trim opp1 value

*/
#define PRCM_AON_RVMLTRIMCTL_OVOPP1_W                                7U
#define PRCM_AON_RVMLTRIMCTL_OVOPP1_M                                0x0000007FU
#define PRCM_AON_RVMLTRIMCTL_OVOPP1_S                                0U
/*

        Field:           OVSLP
        From..to bits:   7...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE SLEEP

                         defines trim sleep value

*/
#define PRCM_AON_RVMLTRIMCTL_OVSLP_W                                 7U
#define PRCM_AON_RVMLTRIMCTL_OVSLP_M                                 0x00003F80U
#define PRCM_AON_RVMLTRIMCTL_OVSLP_S                                 7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       I2VCIRCITCTL
    Offset name:         PRCM_AON_O_I2VCIRCITCTL
    Relative address:    0x706C
    Description:         I2V CIRCUIT CONTROL
    Default Value:       0x00000200

        Field:           FS
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     fuse value of I2V circuit

*/
#define PRCM_AON_I2VCIRCITCTL_FS_W                                   7U
#define PRCM_AON_I2VCIRCITCTL_FS_M                                   0x0000007FU
#define PRCM_AON_I2VCIRCITCTL_FS_S                                   0U
/*

        Field:           SELOV
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE

                         I2V circuit trim override select

*/
#define PRCM_AON_I2VCIRCITCTL_SELOV                                  0x00000080U
#define PRCM_AON_I2VCIRCITCTL_SELOV_M                                0x00000080U
#define PRCM_AON_I2VCIRCITCTL_SELOV_S                                7U
/*

        Field:           OV
        From..to bits:   8...14
        DefaultValue:    0x2
        Access type:     read-write
        Description:     I2V circuit trim override value

*/
#define PRCM_AON_I2VCIRCITCTL_OV_W                                   7U
#define PRCM_AON_I2VCIRCITCTL_OV_M                                   0x00007F00U
#define PRCM_AON_I2VCIRCITCTL_OV_S                                   8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMBISTCTL
    Offset name:         PRCM_AON_O_PMBISTCTL
    Relative address:    0x7070
    Description:         PMBIST CONTROL
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     one hot bit decoder 4 to 16

*/
#define PRCM_AON_PMBISTCTL_VAL_W                                     4U
#define PRCM_AON_PMBISTCTL_VAL_M                                     0x0000000FU
#define PRCM_AON_PMBISTCTL_VAL_S                                     0U
/*

        Field:           BM
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     BIT MASK

                         '1' - mask bit 0

*/
#define PRCM_AON_PMBISTCTL_BM                                        0x00000010U
#define PRCM_AON_PMBISTCTL_BM_M                                      0x00000010U
#define PRCM_AON_PMBISTCTL_BM_S                                      4U
/*

        Field:           EN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     '1' - enable PMBIST module

*/
#define PRCM_AON_PMBISTCTL_EN                                        0x00000020U
#define PRCM_AON_PMBISTCTL_EN_M                                      0x00000020U
#define PRCM_AON_PMBISTCTL_EN_S                                      5U
/*

        Field:           PORCMPBMEN
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     POR COMP BIT MASK ENABLE

                         '1' - enable propagation of POR Comparator output
                         '0' - disable Comparator

*/
#define PRCM_AON_PMBISTCTL_PORCMPBMEN                                0x00000040U
#define PRCM_AON_PMBISTCTL_PORCMPBMEN_M                              0x00000040U
#define PRCM_AON_PMBISTCTL_PORCMPBMEN_S                              6U
/*

        Field:           VTDETCMPBMEN
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     VT DETECTOR COMPARATOR BIT MASK ENABLE

                         '1' - enable propagation of VTDET Comparator output
                         '0' - disable Comparator

*/
#define PRCM_AON_PMBISTCTL_VTDETCMPBMEN                              0x00000080U
#define PRCM_AON_PMBISTCTL_VTDETCMPBMEN_M                            0x00000080U
#define PRCM_AON_PMBISTCTL_VTDETCMPBMEN_S                            7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMUCOMP
    Offset name:         PRCM_AON_O_PMUCOMP
    Relative address:    0x7074
    Description:         PMU COMPARATOR
    Default Value:       0x00000000

        Field:           BOD
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     BOD

*/
#define PRCM_AON_PMUCOMP_BOD                                         0x00000001U
#define PRCM_AON_PMUCOMP_BOD_M                                       0x00000001U
#define PRCM_AON_PMUCOMP_BOD_S                                       0U
/*

        Field:           RVML
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RVML

*/
#define PRCM_AON_PMUCOMP_RVML                                        0x00000002U
#define PRCM_AON_PMUCOMP_RVML_M                                      0x00000002U
#define PRCM_AON_PMUCOMP_RVML_S                                      1U
/*

        Field:           RVMH
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RVMH

*/
#define PRCM_AON_PMUCOMP_RVMH                                        0x00000004U
#define PRCM_AON_PMUCOMP_RVMH_M                                      0x00000004U
#define PRCM_AON_PMUCOMP_RVMH_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ABGRTRIM
    Offset name:         PRCM_AON_O_ABGRTRIM
    Relative address:    0x7078
    Description:         Analog band gap rtrim
    Default Value:       0x00000000

        Field:           OV
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for abgap rtrim

*/
#define PRCM_AON_ABGRTRIM_OV_W                                       4U
#define PRCM_AON_ABGRTRIM_OV_M                                       0x0000000FU
#define PRCM_AON_ABGRTRIM_OV_S                                       0U
/*

        Field:           SEL
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1: select override option over the use value : 0: fuse value

*/
#define PRCM_AON_ABGRTRIM_SEL                                        0x00000020U
#define PRCM_AON_ABGRTRIM_SEL_M                                      0x00000020U
#define PRCM_AON_ABGRTRIM_SEL_S                                      5U
/*

        Field:           FS
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     fuse value for abgap rtrim

*/
#define PRCM_AON_ABGRTRIM_FS_W                                       4U
#define PRCM_AON_ABGRTRIM_FS_M                                       0x00000F00U
#define PRCM_AON_ABGRTRIM_FS_S                                       8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ABGTRIMTMP
    Offset name:         PRCM_AON_O_ABGTRIMTMP
    Relative address:    0x707C
    Description:         ABGAP TRIM TEMP

                        override option over the fuse value for abgap trimcurve
    Default Value:       0x00000000

        Field:           OV
        From..to bits:   0...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for abgap trimcurve

*/
#define PRCM_AON_ABGTRIMTMP_OV_W                                     6U
#define PRCM_AON_ABGTRIMTMP_OV_M                                     0x0000003FU
#define PRCM_AON_ABGTRIMTMP_OV_S                                     0U
/*

        Field:           SEL
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1: select the override option : 0: fuse value

*/
#define PRCM_AON_ABGTRIMTMP_SEL                                      0x00000100U
#define PRCM_AON_ABGTRIMTMP_SEL_M                                    0x00000100U
#define PRCM_AON_ABGTRIMTMP_SEL_S                                    8U
/*

        Field:           FS
        From..to bits:   9...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     fuse value for abgap trim temp
                         To adjust output of amp to 1.224V
                         Nom = 0,0,0,0,0,1 or 1,0,0,0,0,1
                         Strong = 0,1,1,1,0,0 or 1,1,1,1,0,0
                         Weak = 0,0,0,1,1,0 or 1,0,0,1,1,0

*/
#define PRCM_AON_ABGTRIMTMP_FS_W                                     5U
#define PRCM_AON_ABGTRIMTMP_FS_M                                     0x00003E00U
#define PRCM_AON_ABGTRIMTMP_FS_S                                     9U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CKMSPARE
    Offset name:         PRCM_AON_O_CKMSPARE
    Relative address:    0x7080
    Description:         CKM SPARE

                        HW connected to abgap
    Default Value:       0x00000000

        Field:           LDOREG0
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     LDO REGISTER 0

*/
#define PRCM_AON_CKMSPARE_LDOREG0_W                                  2U
#define PRCM_AON_CKMSPARE_LDOREG0_M                                  0x00000003U
#define PRCM_AON_CKMSPARE_LDOREG0_S                                  0U
/*

        Field:           OSCREG0
        From..to bits:   2...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OSC REGISTER 0

*/
#define PRCM_AON_CKMSPARE_OSCREG0_W                                  2U
#define PRCM_AON_CKMSPARE_OSCREG0_M                                  0x0000000CU
#define PRCM_AON_CKMSPARE_OSCREG0_S                                  2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ABGPEN
    Offset name:         PRCM_AON_O_ABGPEN
    Relative address:    0x7084
    Description:         ABGAP ENABLE

                        general abgap config
    Default Value:       0x00008601

        Field:           FFSM
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-only
        Description:     FAST FSM

                         final abgap enable signal to abgap

*/
#define PRCM_AON_ABGPEN_FFSM                                         0x00000001U
#define PRCM_AON_ABGPEN_FFSM_M                                       0x00000001U
#define PRCM_AON_ABGPEN_FFSM_S                                       0U
/*

        Field:           OV
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for abgap en

*/
#define PRCM_AON_ABGPEN_OV                                           0x00000002U
#define PRCM_AON_ABGPEN_OV_M                                         0x00000002U
#define PRCM_AON_ABGPEN_OV_S                                         1U
/*

        Field:           SELOV
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1: select override value for abgap enable : 0: use HW FSM for abgap enable :  : the override value should be written first and then the sel_ov_*; after writing the sel_ov_* the value of the override cannot be changed.

*/
#define PRCM_AON_ABGPEN_SELOV                                        0x00000004U
#define PRCM_AON_ABGPEN_SELOV_M                                      0x00000004U
#define PRCM_AON_ABGPEN_SELOV_S                                      2U
/*

        Field:           SELOVFC
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE FAST CHARGE

                         1: select override value for abgap fast charge : 0: use HW FSM for abgap fast charge enable

*/
#define PRCM_AON_ABGPEN_SELOVFC                                      0x00000008U
#define PRCM_AON_ABGPEN_SELOVFC_M                                    0x00000008U
#define PRCM_AON_ABGPEN_SELOVFC_S                                    3U
/*

        Field:           OVFC
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE FAST CHARGE

                         override value for the abgap fast charge
                         Enable Fast Charge
                         "H" = Enable Fast charging, "L" = Disable

*/
#define PRCM_AON_ABGPEN_OVFC                                         0x00000010U
#define PRCM_AON_ABGPEN_OVFC_M                                       0x00000010U
#define PRCM_AON_ABGPEN_OVFC_S                                       4U
/*

        Field:           FFSMFC
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FAST FSM FAST CHARGE

                         FSM status - analog band gap FC enable

*/
#define PRCM_AON_ABGPEN_FFSMFC                                       0x00000020U
#define PRCM_AON_ABGPEN_FFSMFC_M                                     0x00000020U
#define PRCM_AON_ABGPEN_FFSMFC_S                                     5U
/*

        Field:           FILTTRIM
        From..to bits:   9...12
        DefaultValue:    0x3
        Access type:     read-write
        Description:     FILT TRIM

                         HW connected to abgap filt trim
                         each bit according to the description below-
                         Control bit for 150k
                         "H" = Bypass resistor , "L" = Enable resistor

*/
#define PRCM_AON_ABGPEN_FILTTRIM_W                                   4U
#define PRCM_AON_ABGPEN_FILTTRIM_M                                   0x00001E00U
#define PRCM_AON_ABGPEN_FILTTRIM_S                                   9U
/*

        Field:           SELOVV2I
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE V2I

*/
#define PRCM_AON_ABGPEN_SELOVV2I                                     0x00002000U
#define PRCM_AON_ABGPEN_SELOVV2I_M                                   0x00002000U
#define PRCM_AON_ABGPEN_SELOVV2I_S                                   13U
/*

        Field:           OVV2I
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE V2I

                         Enable BG's internal V2I which supplies LDOs
                         "L" = Disable V2I, "H" = Enable V2I

*/
#define PRCM_AON_ABGPEN_OVV2I                                        0x00004000U
#define PRCM_AON_ABGPEN_OVV2I_M                                      0x00004000U
#define PRCM_AON_ABGPEN_OVV2I_S                                      14U
/*

        Field:           FFSMV2I
        From..to bits:   15...15
        DefaultValue:    0x1
        Access type:     read-only
        Description:     FAST FSM V2I

                         FSM status - analog band gap V2I enable

*/
#define PRCM_AON_ABGPEN_FFSMV2I                                      0x00008000U
#define PRCM_AON_ABGPEN_FFSMV2I_M                                    0x00008000U
#define PRCM_AON_ABGPEN_FFSMV2I_S                                    15U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ABGPTRIMMAG
    Offset name:         PRCM_AON_O_ABGPTRIMMAG
    Relative address:    0x7088
    Description:         ABGAP TRIM MAG

                        analog bandgap trimming register
    Default Value:       0x00000000

        Field:           OV
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for abgap trimming
                         To adjust output of BG to 800mV
                         Nom = 0,0,0,0,0
                         Strong = 0,0,0,0,1
                         Weak = 0,0,0,0,0

*/
#define PRCM_AON_ABGPTRIMMAG_OV_W                                    5U
#define PRCM_AON_ABGPTRIMMAG_OV_M                                    0x0000001FU
#define PRCM_AON_ABGPTRIMMAG_OV_S                                    0U
/*

        Field:           SELOV
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE

                         1: select override value over the fuse value : 0: use fuse value

*/
#define PRCM_AON_ABGPTRIMMAG_SELOV                                   0x00000040U
#define PRCM_AON_ABGPTRIMMAG_SELOV_M                                 0x00000040U
#define PRCM_AON_ABGPTRIMMAG_SELOV_S                                 6U
/*

        Field:           FS
        From..to bits:   8...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     fuse value for abgap trimming
                         To adjust output of BG to 800mV
                         Nom = 0,0,0,0,0
                         Strong = 0,0,0,0,1
                         Weak = 0,0,0,0,0

*/
#define PRCM_AON_ABGPTRIMMAG_FS_W                                    5U
#define PRCM_AON_ABGPTRIMMAG_FS_M                                    0x00001F00U
#define PRCM_AON_ABGPTRIMMAG_FS_S                                    8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLKREQABGPDLY
    Offset name:         PRCM_AON_O_FCLKREQABGPDLY
    Relative address:    0x708C
    Description:         FAST CLK REQUEST ABGAP DELAY

                        host clock settling time in FSM
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   3...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     time (sclk) from primary CLK req until FSM enable abgap
                         resolution 250us
                         (need to add 1 to value in register)
                         0 - 1 slow CLK cycle delay
                         1 - 2 * 8 sclk cycle delays
                         2 - 3 * 8 sclk cycle delay
                         ...
                         write [10:3] as 250us resolution
                         read [10:0] - reflect the multiplication by 8 already

*/
#define PRCM_AON_FCLKREQABGPDLY_VAL_W                                8U
#define PRCM_AON_FCLKREQABGPDLY_VAL_M                                0x000007F8U
#define PRCM_AON_FCLKREQABGPDLY_VAL_S                                3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLKLDODLY
    Offset name:         PRCM_AON_O_FCLKLDODLY
    Relative address:    0x7090
    Description:         FAST CLK LDO DELAY

                        primary clock FSM timers
    Default Value:       0x0001000E

        Field:           SLICER
        From..to bits:   0...3
        DefaultValue:    0xE
        Access type:     read-write
        Description:     settling time (sclk) for slicer LDO en. (at least 3-5 slow clks minimum):
                         time from FSM enables the slicer LDO to the time it enables the ldo startup
                         (need to add 1 to value in register)
                         0 - 1 cycle delay
                         1 - 2 cycle delay

*/
#define PRCM_AON_FCLKLDODLY_SLICER_W                                 4U
#define PRCM_AON_FCLKLDODLY_SLICER_M                                 0x0000000FU
#define PRCM_AON_FCLKLDODLY_SLICER_S                                 0U
/*

        Field:           STRTUP
        From..to bits:   16...17
        DefaultValue:    0x1
        Access type:     read-write
        Description:     delay time for LDO STARTUP to slicer enable or osc_sli_bias_startup
                         (need to add 1 to value in register)
                         0 - 1 cycle delay
                         1 - 2 cycle delay

*/
#define PRCM_AON_FCLKLDODLY_STRTUP_W                                 2U
#define PRCM_AON_FCLKLDODLY_STRTUP_M                                 0x00030000U
#define PRCM_AON_FCLKLDODLY_STRTUP_S                                 16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCBGSETDLY
    Offset name:         PRCM_AON_O_FCBGSETDLY
    Relative address:    0x7094
    Description:         FAST CLK ABGAP SET DELAY

                        analog bandgap settling time
    Default Value:       0x00000007

        Field:           VAL
        From..to bits:   0...3
        DefaultValue:    0x7
        Access type:     read-write
        Description:     time (sclk) for analog bandgap settling by fast clock FSM.
                         time from enabling the ABGAP to the time enabling the fast slicer LDO enable
                         (need to add 1 to value in register)
                         0 - skip the ABGAP fast charge altogether and ABGAP will be enabled simultaneously with slicer LDO configurable time (CLK_REQ_ABGAP_DELAY) after the clock request from ELP is issued
                         1 - 2 cycle delay

*/
#define PRCM_AON_FCBGSETDLY_VAL_W                                    4U
#define PRCM_AON_FCBGSETDLY_VAL_M                                    0x0000000FU
#define PRCM_AON_FCBGSETDLY_VAL_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLKABGPFCDLY
    Offset name:         PRCM_AON_O_FCLKABGPFCDLY
    Relative address:    0x7098
    Description:         FAST CLK ABGAP FAST CHARGE DELAY

                        analog bandgap fast charge settling time
    Default Value:       0x00000013

        Field:           VAL
        From..to bits:   0...4
        DefaultValue:    0x13
        Access type:     read-write
        Description:     time (sclk) that the ABGAP will be in fast charge mode after enable (default 6 RTC clocks - confirmed with ABGAP design)
                         (need to add 1 to value in register)
                         0 - 1 cycle delay
                         1 - 2 cycle delay

*/
#define PRCM_AON_FCLKABGPFCDLY_VAL_W                                 5U
#define PRCM_AON_FCLKABGPFCDLY_VAL_M                                 0x0000001FU
#define PRCM_AON_FCLKABGPFCDLY_VAL_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ABGPDISDLY
    Offset name:         PRCM_AON_O_ABGPDISDLY
    Relative address:    0x709C
    Description:         analog bandgap disabling time register

                        Prior initiating SW SOC-AON RST or Debugger SOC-AON RST,
                        this reg should be initialized to it's default value
    Default Value:       0x00000008

        Field:           VAL
        From..to bits:   0...3
        DefaultValue:    0x8
        Access type:     read-write
        Description:     delay (sclk) from the time fast clock is no valid to the time the ABGAP enable will fall

                         0 - no delay
                         1 - 1 sclk cycle delay = 31.25us
                         2 - 2 sclk cycle delay = 62.5us
                         3 - 3 sclk cycle delay = 93.75us
                         ...

*/
#define PRCM_AON_ABGPDISDLY_VAL_W                                    4U
#define PRCM_AON_ABGPDISDLY_VAL_M                                    0x0000000FU
#define PRCM_AON_ABGPDISDLY_VAL_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ABGPTSTMOD
    Offset name:         PRCM_AON_O_ABGPTSTMOD
    Relative address:    0x70A0
    Description:         ABGAP TEST MODE

                        HW connected to analog bandgap testmode input
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HW connected to analog bandgap testmode input
                         bit[1] - Bring out "BG_PRETRIM_0P8V" through TMUX
                         bit[0] - Bring out "BG_1P2V" through TMUX

*/
#define PRCM_AON_ABGPTSTMOD_VAL_W                                    2U
#define PRCM_AON_ABGPTSTMOD_VAL_M                                    0x00000003U
#define PRCM_AON_ABGPTSTMOD_VAL_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIMSLDOILOD
    Offset name:         PRCM_AON_O_PRIMSLDOILOD
    Relative address:    0x70A4
    Description:         PRIMARY SLICER LDO ILOAD

                        primary slicer LDO configurations
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Slicer LDO internal load test condition

*/
#define PRCM_AON_PRIMSLDOILOD_VAL_W                                  2U
#define PRCM_AON_PRIMSLDOILOD_VAL_M                                  0x00000003U
#define PRCM_AON_PRIMSLDOILOD_VAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIMSLIC
    Offset name:         PRCM_AON_O_PRIMSLIC
    Relative address:    0x70A8
    Description:         primary slicer LDO configurations
    Default Value:       0x00000801

        Field:           FSMEN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-only
        Description:     FSM ENABLE

                         final primary slicer ldo signal going to CLKM

*/
#define PRCM_AON_PRIMSLIC_FSMEN                                      0x00000001U
#define PRCM_AON_PRIMSLIC_FSMEN_M                                    0x00000001U
#define PRCM_AON_PRIMSLIC_FSMEN_S                                    0U
/*

        Field:           OVEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE ENABLE

                         override value for primary slicer

*/
#define PRCM_AON_PRIMSLIC_OVEN                                       0x00000002U
#define PRCM_AON_PRIMSLIC_OVEN_M                                     0x00000002U
#define PRCM_AON_PRIMSLIC_OVEN_S                                     1U
/*

        Field:           SELOVEN
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE ENABLE

                         1: select override option for primary slicer ldo : 0:primary slicer driven by FSM

*/
#define PRCM_AON_PRIMSLIC_SELOVEN                                    0x00000004U
#define PRCM_AON_PRIMSLIC_SELOVEN_M                                  0x00000004U
#define PRCM_AON_PRIMSLIC_SELOVEN_S                                  2U
/*

        Field:           BYPASS
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HW connected to slicer ldo bypass input in CLKM

*/
#define PRCM_AON_PRIMSLIC_BYPASS                                     0x00000010U
#define PRCM_AON_PRIMSLIC_BYPASS_M                                   0x00000010U
#define PRCM_AON_PRIMSLIC_BYPASS_S                                   4U
/*

        Field:           CMLDOPPUDNCTL
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CLKM LDO PMOS PULL DOWN EN

                         clock module ldo pmos pull down ctrl
                         '1' - disable
                         '0' - enable

*/
#define PRCM_AON_PRIMSLIC_CMLDOPPUDNCTL                              0x00000100U
#define PRCM_AON_PRIMSLIC_CMLDOPPUDNCTL_M                            0x00000100U
#define PRCM_AON_PRIMSLIC_CMLDOPPUDNCTL_S                            8U
/*

        Field:           CMLDOSTRTUMOD2
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CLOCK MODULE LDO STARTUP MODE 2

                         clock module ldo startup mode 2

*/
#define PRCM_AON_PRIMSLIC_CMLDOSTRTUMOD2                             0x00000200U
#define PRCM_AON_PRIMSLIC_CMLDOSTRTUMOD2_M                           0x00000200U
#define PRCM_AON_PRIMSLIC_CMLDOSTRTUMOD2_S                           9U
/*

        Field:           CMLDOSTRTUMOD1
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CLK MODULE LDO STARTUP MODE 1

                         clock module ldo startup mode 1

*/
#define PRCM_AON_PRIMSLIC_CMLDOSTRTUMOD1                             0x00000400U
#define PRCM_AON_PRIMSLIC_CMLDOSTRTUMOD1_M                           0x00000400U
#define PRCM_AON_PRIMSLIC_CMLDOSTRTUMOD1_S                           10U
/*

        Field:           FFSMCMBIEN
        From..to bits:   11...11
        DefaultValue:    0x1
        Access type:     read-only
        Description:     FAST FSM CKM BIAS ENABLE

                         final primary slicer ldo signal going to CLKM

*/
#define PRCM_AON_PRIMSLIC_FFSMCMBIEN                                 0x00000800U
#define PRCM_AON_PRIMSLIC_FFSMCMBIEN_M                               0x00000800U
#define PRCM_AON_PRIMSLIC_FFSMCMBIEN_S                               11U
/*

        Field:           OVFCLKMBIEN
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE FAST CLK MODULE BIAS ENABLE

                         override value for CKM bias en

*/
#define PRCM_AON_PRIMSLIC_OVFCLKMBIEN                                0x00001000U
#define PRCM_AON_PRIMSLIC_OVFCLKMBIEN_M                              0x00001000U
#define PRCM_AON_PRIMSLIC_OVFCLKMBIEN_S                              12U
/*

        Field:           SELOVFCLKMBIEN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE FAST CLK MODULE BIAS ENABLE

                         1: select override option for CKM bias en 0:CKM bias en driven by FSM

*/
#define PRCM_AON_PRIMSLIC_SELOVFCLKMBIEN                             0x00002000U
#define PRCM_AON_PRIMSLIC_SELOVFCLKMBIEN_M                           0x00002000U
#define PRCM_AON_PRIMSLIC_SELOVFCLKMBIEN_S                           13U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLKDISHFXTDLY
    Offset name:         PRCM_AON_O_FCLKDISHFXTDLY
    Relative address:    0x70AC
    Description:         FAST CLK DISABLE HFXT DELAY

                        delay from primary clock valid goes low to buffer and slicer LDO disable

                        Prior initiating SW SOC-AON RST or Debugger SOC-AON RST,
                        this reg should be initialized to it's default value
    Default Value:       0x00000008

        Field:           VAL
        From..to bits:   0...3
        DefaultValue:    0x8
        Access type:     read-write
        Description:     delay from fast clock valid goes low to slicer ldo, ldo startup, osc enable and slicer enable to disable mode.

                         0 - no delay
                         1 - 1 sclk cycle delay = 31.25us
                         2 - 2 sclk cycle delay = 62.5us
                         3 - 3 sclk cycle delay = 93.75us
                         ...

*/
#define PRCM_AON_FCLKDISHFXTDLY_VAL_W                                4U
#define PRCM_AON_FCLKDISHFXTDLY_VAL_M                                0x0000000FU
#define PRCM_AON_FCLKDISHFXTDLY_VAL_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKSLIEN
    Offset name:         PRCM_AON_O_CLKSLIEN
    Relative address:    0x70B0
    Description:         CLK SLICER ENABLE

                        enable options for primary slicer
    Default Value:       0x00000001

        Field:           FSM
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-only
        Description:     final primary slicer enable signal to CLKM

*/
#define PRCM_AON_CLKSLIEN_FSM                                        0x00000001U
#define PRCM_AON_CLKSLIEN_FSM_M                                      0x00000001U
#define PRCM_AON_CLKSLIEN_FSM_S                                      0U
/*

        Field:           OV
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for primary slicer enable signal

*/
#define PRCM_AON_CLKSLIEN_OV                                         0x00000002U
#define PRCM_AON_CLKSLIEN_OV_M                                       0x00000002U
#define PRCM_AON_CLKSLIEN_OV_S                                       1U
/*

        Field:           SELOV
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1: select override value for primary slicer en : 0: primary slicer enable from FSM

*/
#define PRCM_AON_CLKSLIEN_SELOV                                      0x00000004U
#define PRCM_AON_CLKSLIEN_SELOV_M                                    0x00000004U
#define PRCM_AON_CLKSLIEN_SELOV_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKSLIITRIM
    Offset name:         PRCM_AON_O_CLKSLIITRIM
    Relative address:    0x70B4
    Description:         CLK SLICER ITRIM

                        primary slicer trimming register
    Default Value:       0x00000000

        Field:           OV
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     primary slicer trimming override value

*/
#define PRCM_AON_CLKSLIITRIM_OV_W                                    3U
#define PRCM_AON_CLKSLIITRIM_OV_M                                    0x00000007U
#define PRCM_AON_CLKSLIITRIM_OV_S                                    0U
/*

        Field:           SELOV
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1: select override value for primary slicer trimming over max hold logic : 0: select max hold logic :  : the override value should be written first and then the sel_ov_*; after writing the sel_ov_* the value of the override cannot be changed.

*/
#define PRCM_AON_CLKSLIITRIM_SELOV                                   0x00000008U
#define PRCM_AON_CLKSLIITRIM_SELOV_M                                 0x00000008U
#define PRCM_AON_CLKSLIITRIM_SELOV_S                                 3U
/*

        Field:           FS
        From..to bits:   4...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     final primary slicer trimming value to CLKM : max hold mechanism of IPs requests

*/
#define PRCM_AON_CLKSLIITRIM_FS_W                                    3U
#define PRCM_AON_CLKSLIITRIM_FS_M                                    0x00000070U
#define PRCM_AON_CLKSLIITRIM_FS_S                                    4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIMSLIRTRIM
    Offset name:         PRCM_AON_O_PRIMSLIRTRIM
    Relative address:    0x70B8
    Description:         primary clock rtrim cfg register
    Default Value:       0x00000000

        Field:           OV
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for clock module rtrim

*/
#define PRCM_AON_PRIMSLIRTRIM_OV_W                                   5U
#define PRCM_AON_PRIMSLIRTRIM_OV_M                                   0x0000001FU
#define PRCM_AON_PRIMSLIRTRIM_OV_S                                   0U
/*

        Field:           SELOV
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1: select override option over the fuse value : 0: select override value until efuse shift done and then fuse value

*/
#define PRCM_AON_PRIMSLIRTRIM_SELOV                                  0x00000020U
#define PRCM_AON_PRIMSLIRTRIM_SELOV_M                                0x00000020U
#define PRCM_AON_PRIMSLIRTRIM_SELOV_S                                5U
/*

        Field:           FS
        From..to bits:   6...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     final fast clock rtrim value to CLKM I/F

*/
#define PRCM_AON_PRIMSLIRTRIM_FS_W                                   5U
#define PRCM_AON_PRIMSLIRTRIM_FS_M                                   0x000007C0U
#define PRCM_AON_PRIMSLIRTRIM_FS_S                                   6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIMOSC
    Offset name:         PRCM_AON_O_PRIMOSC
    Relative address:    0x70BC
    Description:         PRIMARY OSCILLATOR
    Default Value:       0x00000000

        Field:           SELBISTRT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT BIAS START

                         Override control Start-up bit for the Osc/Slicer Bias

*/
#define PRCM_AON_PRIMOSC_SELBISTRT                                   0x00000001U
#define PRCM_AON_PRIMOSC_SELBISTRT_M                                 0x00000001U
#define PRCM_AON_PRIMOSC_SELBISTRT_S                                 0U
/*

        Field:           OVBISTRT
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE BIAS START

                         Override Start-up bit for the Osc/Slicer Bias

*/
#define PRCM_AON_PRIMOSC_OVBISTRT                                    0x00000002U
#define PRCM_AON_PRIMOSC_OVBISTRT_M                                  0x00000002U
#define PRCM_AON_PRIMOSC_OVBISTRT_S                                  1U
/*

        Field:           BISTRT
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     BIAS START

                         Override control Start-up bit for the Osc/Slicer Bias

*/
#define PRCM_AON_PRIMOSC_BISTRT                                      0x00000004U
#define PRCM_AON_PRIMOSC_BISTRT_M                                    0x00000004U
#define PRCM_AON_PRIMOSC_BISTRT_S                                    2U
/*

        Field:           CLDOVOSCLEN
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CKM LDO VOUT SCL EN

                         Control bit for bringing out LDO_Vout/2 to GPADC

*/
#define PRCM_AON_PRIMOSC_CLDOVOSCLEN                                 0x00000008U
#define PRCM_AON_PRIMOSC_CLDOVOSCLEN_M                               0x00000008U
#define PRCM_AON_PRIMOSC_CLDOVOSCLEN_S                               3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OSCEN
    Offset name:         PRCM_AON_O_OSCEN
    Relative address:    0x70C0
    Description:         OSC ENABLE

                        XTAL cfg register
    Default Value:       0x00000010

        Field:           FSM
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     final osc enable signal to CLKM

*/
#define PRCM_AON_OSCEN_FSM                                           0x00000001U
#define PRCM_AON_OSCEN_FSM_M                                         0x00000001U
#define PRCM_AON_OSCEN_FSM_S                                         0U
/*

        Field:           OV
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for osc enable signal

*/
#define PRCM_AON_OSCEN_OV                                            0x00000002U
#define PRCM_AON_OSCEN_OV_M                                          0x00000002U
#define PRCM_AON_OSCEN_OV_S                                          1U
/*

        Field:           SELOV
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1: select override value for osc enable signal : 0: osc enable comes from FSM

*/
#define PRCM_AON_OSCEN_SELOV                                         0x00000004U
#define PRCM_AON_OSCEN_SELOV_M                                       0x00000004U
#define PRCM_AON_OSCEN_SELOV_S                                       2U
/*

        Field:           ISNEEDED
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     fast clock detection FSM indication that XTAL oscillator was detected

*/
#define PRCM_AON_OSCEN_ISNEEDED                                      0x00000008U
#define PRCM_AON_OSCEN_ISNEEDED_M                                    0x00000008U
#define PRCM_AON_OSCEN_ISNEEDED_S                                    3U
/*

        Field:           XTSNSPU
        From..to bits:   4...4
        DefaultValue:    0x1
        Access type:     read-write
        Description:     XTAL SENSE PULL UP

                         enable for the pull resistor in CLKM that detects XTAL mode

*/
#define PRCM_AON_OSCEN_XTSNSPU                                       0x00000010U
#define PRCM_AON_OSCEN_XTSNSPU_M                                     0x00000010U
#define PRCM_AON_OSCEN_XTSNSPU_S                                     4U
/*

        Field:           CMXTMODSNS
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CM XTAL MODE SENSE

                         Read value of CLK_IN_PRIMARY_M (XTAL_M) input

*/
#define PRCM_AON_OSCEN_CMXTMODSNS                                    0x00000200U
#define PRCM_AON_OSCEN_CMXTMODSNS_M                                  0x00000200U
#define PRCM_AON_OSCEN_CMXTMODSNS_S                                  9U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OSCITRIM
    Offset name:         PRCM_AON_O_OSCITRIM
    Relative address:    0x70C4
    Description:         oscillator itrim cfg register
    Default Value:       0x00002F00

        Field:           SELOV
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1: select override for osc gain normal values, need to use fast_osc_gain_norm
                         0: Logic select itrim value

*/
#define PRCM_AON_OSCITRIM_SELOV                                      0x00000001U
#define PRCM_AON_OSCITRIM_SELOV_M                                    0x00000001U
#define PRCM_AON_OSCITRIM_SELOV_S                                    0U
/*

        Field:           FSNORMGN
        From..to bits:   1...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FUSE normal gain value

*/
#define PRCM_AON_OSCITRIM_FSNORMGN_W                                 6U
#define PRCM_AON_OSCITRIM_FSNORMGN_M                                 0x0000007EU
#define PRCM_AON_OSCITRIM_FSNORMGN_S                                 1U
/*

        Field:           SELOVOSCGN
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1: select override for osc gain values, need to use fast_osc_gain_boost (debug only)
                         0: Logic select between normal and boost values

*/
#define PRCM_AON_OSCITRIM_SELOVOSCGN                                 0x00000080U
#define PRCM_AON_OSCITRIM_SELOVOSCGN_M                               0x00000080U
#define PRCM_AON_OSCITRIM_SELOVOSCGN_S                               7U
/*

        Field:           FSM
        From..to bits:   8...13
        DefaultValue:    0x2F
        Access type:     read-only
        Description:     final XTAL oscillator trimming value to CLKM

*/
#define PRCM_AON_OSCITRIM_FSM_W                                      6U
#define PRCM_AON_OSCITRIM_FSM_M                                      0x00003F00U
#define PRCM_AON_OSCITRIM_FSM_S                                      8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OSCBSTDLY
    Offset name:         PRCM_AON_O_OSCBSTDLY
    Relative address:    0x70C8
    Description:         OSC BOOST DELAY

                        XTAL OSC boost trim cfg
    Default Value:       0x000000F0

        Field:           VAL
        From..to bits:   3...9
        DefaultValue:    0x1E
        Access type:     read-write
        Description:     time (sclk) while osc itrim gets boost value before moving to normal value in the clock FSM (default 4ms)
                         resolution 250us
                         (need to add 1 to value in register)

                         0 - 1 slow CLK cycle delay
                         1 - 2 * 8 sclk cycle delays
                         2 - 3 * 8 sclk cycle delay
                         ...
                         write [9:3] as 250us resolution
                         read [9:0] - reflect the multiplication by 8 already

*/
#define PRCM_AON_OSCBSTDLY_VAL_W                                     7U
#define PRCM_AON_OSCBSTDLY_VAL_M                                     0x000003F8U
#define PRCM_AON_OSCBSTDLY_VAL_S                                     3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OSCNORMDLY
    Offset name:         PRCM_AON_O_OSCNORMDLY
    Relative address:    0x70CC
    Description:         OSC NORMAL DELAY

                        XTAL OSC normal trim
    Default Value:       0x00000078

        Field:           VAL
        From..to bits:   3...8
        DefaultValue:    0xF
        Access type:     read-write
        Description:     time (sclk) while osc itrim gets normal value before moving to next state of opening the buffer in the clock FSM
                         (need to add 1 to value in register)

                         0 - 1 slow CLK cycle delay
                         1 - 2 * 8 sclk cycle delays
                         2 - 3 * 8 sclk cycle delay
                         ...
                         write [8:3] as 250us resolution
                         read [8:0] - reflect the multiplication by 8 already

*/
#define PRCM_AON_OSCNORMDLY_VAL_W                                    6U
#define PRCM_AON_OSCNORMDLY_VAL_M                                    0x000001F8U
#define PRCM_AON_OSCNORMDLY_VAL_S                                    3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CRDIGBUFCTRL
    Offset name:         PRCM_AON_O_CRDIGBUFCTRL
    Relative address:    0x70D0
    Description:         core and dig buffer control register
    Default Value:       0x00000024

        Field:           OVCRBUFEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override core buf enable value

*/
#define PRCM_AON_CRDIGBUFCTRL_OVCRBUFEN                              0x00000001U
#define PRCM_AON_CRDIGBUFCTRL_OVCRBUFEN_M                            0x00000001U
#define PRCM_AON_CRDIGBUFCTRL_OVCRBUFEN_S                            0U
/*

        Field:           SELOVCRBUFEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE CORE BUFFER ENABLE

                         select override value or FSM
                         '1' - override
                         '0' - FSM

*/
#define PRCM_AON_CRDIGBUFCTRL_SELOVCRBUFEN                           0x00000002U
#define PRCM_AON_CRDIGBUFCTRL_SELOVCRBUFEN_M                         0x00000002U
#define PRCM_AON_CRDIGBUFCTRL_SELOVCRBUFEN_S                         1U
/*

        Field:           FSMCRBUFEN
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-only
        Description:     FAST FSM CORE BUFFER ENABLE

                         core buf enable status

*/
#define PRCM_AON_CRDIGBUFCTRL_FSMCRBUFEN                             0x00000004U
#define PRCM_AON_CRDIGBUFCTRL_FSMCRBUFEN_M                           0x00000004U
#define PRCM_AON_CRDIGBUFCTRL_FSMCRBUFEN_S                           2U
/*

        Field:           OVDBUFEN
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override digital buffer enable value

*/
#define PRCM_AON_CRDIGBUFCTRL_OVDBUFEN                               0x00000008U
#define PRCM_AON_CRDIGBUFCTRL_OVDBUFEN_M                             0x00000008U
#define PRCM_AON_CRDIGBUFCTRL_OVDBUFEN_S                             3U
/*

        Field:           SELOVDBUFEN
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE DIGITAL BUFFER ENABLE

                          select override value or FSM
                         '1' - override
                         '0' - FSM

*/
#define PRCM_AON_CRDIGBUFCTRL_SELOVDBUFEN                            0x00000010U
#define PRCM_AON_CRDIGBUFCTRL_SELOVDBUFEN_M                          0x00000010U
#define PRCM_AON_CRDIGBUFCTRL_SELOVDBUFEN_S                          4U
/*

        Field:           FSMDBUFEN
        From..to bits:   5...5
        DefaultValue:    0x1
        Access type:     read-only
        Description:     FSM DIGITAL BUFFER ENABLE

                         dig buf enable status

*/
#define PRCM_AON_CRDIGBUFCTRL_FSMDBUFEN                              0x00000020U
#define PRCM_AON_CRDIGBUFCTRL_FSMDBUFEN_M                            0x00000020U
#define PRCM_AON_CRDIGBUFCTRL_FSMDBUFEN_S                            5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OSCDLY
    Offset name:         PRCM_AON_O_OSCDLY
    Relative address:    0x70D4
    Description:         OSCILLATOR DELAY

                        XTAL OSC normal trim
    Default Value:       0x00000005

        Field:           STRTCR
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     START CORE

                         time (sclk) while fast CLK  FSM slicer is enabled and osc_and_sli_bias to boost mode or to disable osc mode (not in xtal)
                         need to add 1 to value in register)
                         0 - 1 cycle delay
                         1 - 2 cycle delay

*/
#define PRCM_AON_OSCDLY_STRTCR_W                                     2U
#define PRCM_AON_OSCDLY_STRTCR_M                                     0x00000003U
#define PRCM_AON_OSCDLY_STRTCR_S                                     0U
/*

        Field:           DISSLIBI
        From..to bits:   2...3
        DefaultValue:    0x1
        Access type:     read-write
        Description:     DISABLE SLICER BIAS

                         time (sclk) while fast CLK fsm move from normal gain to disabling the osc_and_sli_bias
                         (need to add 1 to value in register)
                         0 - 1 cycle delay
                         1 - 2 cycle delay

*/
#define PRCM_AON_OSCDLY_DISSLIBI_W                                   2U
#define PRCM_AON_OSCDLY_DISSLIBI_M                                   0x0000000CU
#define PRCM_AON_OSCDLY_DISSLIBI_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STRUCMLDOCTL
    Offset name:         PRCM_AON_O_STRUCMLDOCTL
    Relative address:    0x70D8
    Description:         startup clock module ldo control
    Default Value:       0x00000004

        Field:           SELOV
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     '1' selects FSM
                         '0' selects override

*/
#define PRCM_AON_STRUCMLDOCTL_SELOV                                  0x00000001U
#define PRCM_AON_STRUCMLDOCTL_SELOV_M                                0x00000001U
#define PRCM_AON_STRUCMLDOCTL_SELOV_S                                0U
/*

        Field:           OV
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override value for startup clock module LDO

*/
#define PRCM_AON_STRUCMLDOCTL_OV                                     0x00000002U
#define PRCM_AON_STRUCMLDOCTL_OV_M                                   0x00000002U
#define PRCM_AON_STRUCMLDOCTL_OV_S                                   1U
/*

        Field:           FSM
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-only
        Description:     startup clock module fsm value

*/
#define PRCM_AON_STRUCMLDOCTL_FSM                                    0x00000004U
#define PRCM_AON_STRUCMLDOCTL_FSM_M                                  0x00000004U
#define PRCM_AON_STRUCMLDOCTL_FSM_S                                  2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SHDOWFCLKCTL
    Offset name:         PRCM_AON_O_SHDOWFCLKCTL
    Relative address:    0x70DC
    Description:         SHADOW FAST CLK CONTROL

                        dummy regs control
    Default Value:       0x00000033

        Field:           LDOVOUT
        From..to bits:   0...4
        DefaultValue:    0x13
        Access type:     read-write
        Description:     LDO VOUT

                         clock ldo vout value to push towards dummy once FSM is SLI_LDO_EN

*/
#define PRCM_AON_SHDOWFCLKCTL_LDOVOUT_W                              5U
#define PRCM_AON_SHDOWFCLKCTL_LDOVOUT_M                              0x0000001FU
#define PRCM_AON_SHDOWFCLKCTL_LDOVOUT_S                              0U
/*

        Field:           HPMODEN
        From..to bits:   5...5
        DefaultValue:    0x1
        Access type:     read-write
        Description:     HP MODE ENABLE

                         clock module HP mode enable value to push towards dummy once FSM is SLI_LDO_EN

*/
#define PRCM_AON_SHDOWFCLKCTL_HPMODEN                                0x00000020U
#define PRCM_AON_SHDOWFCLKCTL_HPMODEN_M                              0x00000020U
#define PRCM_AON_SHDOWFCLKCTL_HPMODEN_S                              5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SLIBIBYPCTL
    Offset name:         PRCM_AON_O_SLIBIBYPCTL
    Relative address:    0x70E0
    Description:         slicer bias bypass control reg
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     '1' - slicer bias bypass

*/
#define PRCM_AON_SLIBIBYPCTL_VAL_W                                   3U
#define PRCM_AON_SLIBIBYPCTL_VAL_M                                   0x00000007U
#define PRCM_AON_SLIBIBYPCTL_VAL_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ECLKREQDLY
    Offset name:         PRCM_AON_O_ECLKREQDLY
    Relative address:    0x70E4
    Description:         EXTERNAL CLOCK REQUEST DELAY

                        XTAL OSC normal trim
    Default Value:       0x00000108

        Field:           VAL
        From..to bits:   3...10
        DefaultValue:    0x21
        Access type:     read-write
        Description:     time (sclk) while fast CLK FSM move from ext_CLK_req_wait state to to buffer enable or ip buffer enable
                         resolution 250us
                         (need to add 1 to value in register)

                         0 - 1 slow CLK cycle delay
                         1 - 2 * 8 sclk cycle delays
                         2 - 3 * 8 sclk cycle delay
                         ...
                         write [10:3] as 250us resolution
                         read [10:0] - reflect the multiplication by 8 already

*/
#define PRCM_AON_ECLKREQDLY_VAL_W                                    8U
#define PRCM_AON_ECLKREQDLY_VAL_M                                    0x000007F8U
#define PRCM_AON_ECLKREQDLY_VAL_S                                    3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OSCGN
    Offset name:         PRCM_AON_O_OSCGN
    Relative address:    0x70E8
    Description:         OSC GAIN

                        XTAL oscillator gain control cfg register
    Default Value:       0x0000066F

        Field:           BOOST
        From..to bits:   0...5
        DefaultValue:    0x2F
        Access type:     read-write
        Description:     gain for boost mode - when enabling

*/
#define PRCM_AON_OSCGN_BOOST_W                                       6U
#define PRCM_AON_OSCGN_BOOST_M                                       0x0000003FU
#define PRCM_AON_OSCGN_BOOST_S                                       0U
/*

        Field:           OV_NORM
        From..to bits:   6...11
        DefaultValue:    0x19
        Access type:     read-write
        Description:     gain for normal mode - when enabling

*/
#define PRCM_AON_OSCGN_OV_NORM_W                                     6U
#define PRCM_AON_OSCGN_OV_NORM_M                                     0x00000FC0U
#define PRCM_AON_OSCGN_OV_NORM_S                                     6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIMENTMUX
    Offset name:         PRCM_AON_O_PRIMENTMUX
    Relative address:    0x70EC
    Description:         Primary EN TMUX CFG
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HW connected to CLKM - enables the primary slicer ldo output to test mux

*/
#define PRCM_AON_PRIMENTMUX_VAL_W                                    3U
#define PRCM_AON_PRIMENTMUX_VAL_M                                    0x00000007U
#define PRCM_AON_PRIMENTMUX_VAL_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIMEN
    Offset name:         PRCM_AON_O_PRIMEN
    Relative address:    0x70F0
    Description:         PRIMARY ENABLE

                        primary top digital clock division
    Default Value:       0x00000000

        Field:           OVDIV4
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override divide by 4

*/
#define PRCM_AON_PRIMEN_OVDIV4                                       0x00000001U
#define PRCM_AON_PRIMEN_OVDIV4_M                                     0x00000001U
#define PRCM_AON_PRIMEN_OVDIV4_S                                     0U
/*

        Field:           OVDIV2
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     override divide by 2

*/
#define PRCM_AON_PRIMEN_OVDIV2                                       0x00000002U
#define PRCM_AON_PRIMEN_OVDIV2_M                                     0x00000002U
#define PRCM_AON_PRIMEN_OVDIV2_S                                     1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PUSHPULEN
    Offset name:         PRCM_AON_O_PUSHPULEN
    Relative address:    0x70F4
    Description:         PUSH PULL ENABLE

                        cfg option for the clock to the host
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     '1' - enables push pull

*/
#define PRCM_AON_PUSHPULEN_VAL                                       0x00000001U
#define PRCM_AON_PUSHPULEN_VAL_M                                     0x00000001U
#define PRCM_AON_PUSHPULEN_VAL_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLKDISCODLY
    Offset name:         PRCM_AON_O_FCLKDISCODLY
    Relative address:    0x70F8
    Description:         FAST CLOCK DISABLE CLK OUT DELAY

                        cfg to hold the clock request out high while FSM is turning off

                        Prior initiating SW SOC-AON RST or Debugger SOC-AON RST,
                        this reg should be initialized to it's default value
    Default Value:       0x00000008

        Field:           VAL
        From..to bits:   0...3
        DefaultValue:    0x8
        Access type:     read-write
        Description:     time (sclk) from FSM exit EXTEND state (enter CLK_STOP state) to primary clock request out goes low

                         0 - no delay
                         1 - 1 sclk cycle delay = 31.25us
                         2 - 2 sclk cycle delay = 62.5us
                         3 - 3 sclk cycle delay = 93.75us
                         ...

*/
#define PRCM_AON_FCLKDISCODLY_VAL_W                                  4U
#define PRCM_AON_FCLKDISCODLY_VAL_M                                  0x0000000FU
#define PRCM_AON_FCLKDISCODLY_VAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLKVLDEXNDLY
    Offset name:         PRCM_AON_O_FCLKVLDEXNDLY
    Relative address:    0x70FC
    Description:         FAST CLK VALID EXTEND DELAY

                        timers for stopping the primary clock
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     time (sclk) from primary clock valid goes down to the point when the clock actually stops
                         (need to add 1 to value in register)
                         0 - 1 cycle delay
                         1 - 2 cycle delay

*/
#define PRCM_AON_FCLKVLDEXNDLY_VAL_W                                 3U
#define PRCM_AON_FCLKVLDEXNDLY_VAL_M                                 0x00000007U
#define PRCM_AON_FCLKVLDEXNDLY_VAL_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIMEXITSLPDLY
    Offset name:         PRCM_AON_O_PRIMEXITSLPDLY
    Relative address:    0x7100
    Description:         PRIMARY EXIT SLEEP DELAY
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     time (sclk) from IPs stop asking for primary clock to the time the valid will go down
                         (need to add 1 to value in register)
                         0 - 1 cycle delay
                         1 - 2 cycle delay

*/
#define PRCM_AON_PRIMEXITSLPDLY_VAL_W                                3U
#define PRCM_AON_PRIMEXITSLPDLY_VAL_M                                0x00000007U
#define PRCM_AON_PRIMEXITSLPDLY_VAL_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLK
    Offset name:         PRCM_AON_O_FCLK
    Relative address:    0x7108
    Description:         fast CLK control over selectors and overrides
    Default Value:       0x00000840

        Field:           SELOVVAL
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE VALUE

                         fast CLK valid select
                         Override fref valid

*/
#define PRCM_AON_FCLK_SELOVVAL                                       0x00000010U
#define PRCM_AON_FCLK_SELOVVAL_M                                     0x00000010U
#define PRCM_AON_FCLK_SELOVVAL_S                                     4U
/*

        Field:           OVVAL
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE VALUE

                         fast CLK valid override
                         Override fref valid

*/
#define PRCM_AON_FCLK_OVVAL                                          0x00000020U
#define PRCM_AON_FCLK_OVVAL_M                                        0x00000020U
#define PRCM_AON_FCLK_OVVAL_S                                        5U
/*

        Field:           VAL
        From..to bits:   6...6
        DefaultValue:    0x1
        Access type:     read-only
        Description:     primary clock valid indication status

*/
#define PRCM_AON_FCLK_VAL                                            0x00000040U
#define PRCM_AON_FCLK_VAL_M                                          0x00000040U
#define PRCM_AON_FCLK_VAL_S                                          6U
/*

        Field:           SELOVREQOUT
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     fast CLK request out select
                         Override CLK req to pad (A)

*/
#define PRCM_AON_FCLK_SELOVREQOUT                                    0x00000080U
#define PRCM_AON_FCLK_SELOVREQOUT_M                                  0x00000080U
#define PRCM_AON_FCLK_SELOVREQOUT_S                                  7U
/*

        Field:           OVREQOUT
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     fast CLK request out override
                         Override CLK req to pad (A)

*/
#define PRCM_AON_FCLK_OVREQOUT                                       0x00000100U
#define PRCM_AON_FCLK_OVREQOUT_M                                     0x00000100U
#define PRCM_AON_FCLK_OVREQOUT_S                                     8U
/*

        Field:           SELOVREQGZ
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     fast CLK request gz select
                         Override CLK req to pad (GZ)

*/
#define PRCM_AON_FCLK_SELOVREQGZ                                     0x00000200U
#define PRCM_AON_FCLK_SELOVREQGZ_M                                   0x00000200U
#define PRCM_AON_FCLK_SELOVREQGZ_S                                   9U
/*

        Field:           OVREQGZ
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     fast CLK request gz override
                         Override CLK req to pad (GZ)

*/
#define PRCM_AON_FCLK_OVREQGZ                                        0x00000400U
#define PRCM_AON_FCLK_OVREQGZ_M                                      0x00000400U
#define PRCM_AON_FCLK_OVREQGZ_S                                      10U
/*

        Field:           FSMREQIN
        From..to bits:   11...11
        DefaultValue:    0x1
        Access type:     read-only
        Description:     primary clock request indication to FSM

*/
#define PRCM_AON_FCLK_FSMREQIN                                       0x00000800U
#define PRCM_AON_FCLK_FSMREQIN_M                                     0x00000800U
#define PRCM_AON_FCLK_FSMREQIN_S                                     11U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLKDURDLY
    Offset name:         PRCM_AON_O_FCLKDURDLY
    Relative address:    0x710C
    Description:         Primary TMUX CFG
    Default Value:       0x00000001

        Field:           STOP
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     time (sclk) from end of CLK_STOP state elapse to CLK_OFF
                         '0' - bypass
                         '1' - 1 +  8 sclks delay ~250us
                         '2' - 1 + 16 sclks delay ~500us
                         '3' - 1 + 32 sclks delay ~1ms

*/
#define PRCM_AON_FCLKDURDLY_STOP_W                                   2U
#define PRCM_AON_FCLKDURDLY_STOP_M                                   0x00000003U
#define PRCM_AON_FCLKDURDLY_STOP_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FREFDET
    Offset name:         PRCM_AON_O_FREFDET
    Relative address:    0x7110
    Description:         FREF DETECTION
    Default Value:       0x00000002

        Field:           SELOV
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     '1' - fref detection value to pll sharing will be override
                         '0' - fast CLK fsm (fref) value is selected

*/
#define PRCM_AON_FREFDET_SELOV                                       0x00000001U
#define PRCM_AON_FREFDET_SELOV_M                                     0x00000001U
#define PRCM_AON_FREFDET_SELOV_S                                     0U
/*

        Field:           OV
        From..to bits:   1...3
        DefaultValue:    0x1
        Access type:     read-write
        Description:     0: 10MHz
                         1: 26MHz
                         2: 40MHz
                         3: 52MHz

*/
#define PRCM_AON_FREFDET_OV_W                                        3U
#define PRCM_AON_FREFDET_OV_M                                        0x0000000EU
#define PRCM_AON_FREFDET_OV_S                                        1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLKFSMSOPOV
    Offset name:         PRCM_AON_O_FCLKFSMSOPOV
    Relative address:    0x7114
    Description:         this is a SOP OV reg, which is a shadow register.
                        user need to lower ELP CLK req and rise it again in order for the OV reg to take action.
    Default Value:       0x00000000

        Field:           SEL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     '1' - use sop override for fast CLK fsm
                         '0' - use sop status

*/
#define PRCM_AON_FCLKFSMSOPOV_SEL                                    0x00000001U
#define PRCM_AON_FCLKFSMSOPOV_SEL_M                                  0x00000001U
#define PRCM_AON_FCLKFSMSOPOV_SEL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMSRNWCAL
    Offset name:         PRCM_AON_O_PMSRNWCAL
    Relative address:    0x7118
    Description:         HW connected to PMCIO - To enable the Rnwell calibration
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     To enable the Rnwell calibration

*/
#define PRCM_AON_PMSRNWCAL_EN                                        0x00000001U
#define PRCM_AON_PMSRNWCAL_EN_M                                      0x00000001U
#define PRCM_AON_PMSRNWCAL_EN_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMSTEST
    Offset name:         PRCM_AON_O_PMSTEST
    Relative address:    0x711C
    Description:         PMCIO test configurations
    Default Value:       0x00000000

        Field:           LDTRIM
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HW connected to PMCIO - Trim bist for LDO test loads

*/
#define PRCM_AON_PMSTEST_LDTRIM_W                                    3U
#define PRCM_AON_PMSTEST_LDTRIM_M                                    0x00000007U
#define PRCM_AON_PMSTEST_LDTRIM_S                                    0U
/*

        Field:           ENTMUX
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HW connected to PMCIO - Enable signal for test mux

*/
#define PRCM_AON_PMSTEST_ENTMUX                                      0x00000100U
#define PRCM_AON_PMSTEST_ENTMUX_M                                    0x00000100U
#define PRCM_AON_PMSTEST_ENTMUX_S                                    8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMSTMUXCTL
    Offset name:         PRCM_AON_O_PMSTMUXCTL
    Relative address:    0x7120
    Description:         Test mux control signals. To be decoded one hot
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     value             switch number  Signal
                         0x00000000  None                 hi-Z
                         0x00000001  0                       irefn_bg_2u_1p8v[1]
                         0x00000002  1                       irefn_slp_1u_1p8v[1]
                         0x00000004  2                       vref_0p9v_post_filt_pmu
                         0x00000008  3                       vbg_1p22v_lowv
                         0x00000010  4                       sramka_testout_1p8v
                         0x00000020  5                       vdd_sram_sense_lowv
                         0x00000040  6                       no-connect
                         0x00000080  7                       gen_rf_1p8v
                         0x00000100  8                       digka_testout_1p8v
                         0x00000200  9                       mask_digldo_en_1p2_subreg_lowv
                         0x00000400  10                      vcntrl_socpll_1p8v
                         0x00000800  11                      ibias_socpll_1p8v
                         0x00001000  12                      test_comp_out_bod_rvm
                         0x00002000  13                      test_rlad_bod_rvm
                         0x00004000  14                      crude_ref_lowv
                         0x00008000  15                      all_supplies_ok_1p8v
                         0x00010000  16                      vt_det_1p8v
                         0x00020000  17                      test_out_dig_sup_mux
                         0x00040000  18                      iref_bg_test_10u_1p8v
                         0x00080000  19                      irefp_v2i_test_10u_1p8v
                         0x00100000  20                      vdd_core_lowv
                         0x00200000  21                      no-connect
                         0x00400000  22                      no-connect
                         0x00800000  23                      no-connect
                         0x01000000  24                      no-connect
                         0x02000000  25                      no-connect
                         0x04000000  26                      gpadc_input_buf_lowv
                         0x08000000  27                      irefp_v2i_test_10u_1p8v_mirrored
                         0x10000000  28                      don't enable
                         0x20000000  29                      no-connect
                         0x40000000  30                      no-connect
                         0x80000000  31                      no-connect

*/
#define PRCM_AON_PMSTMUXCTL_VAL_W                                    32U
#define PRCM_AON_PMSTMUXCTL_VAL_M                                    0xFFFFFFFFU
#define PRCM_AON_PMSTMUXCTL_VAL_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMSSPAR0
    Offset name:         PRCM_AON_O_PMSSPAR0
    Relative address:    0x7124
    Description:         PMS SPARE REG 0

                        HW connected to PMCIO
    Default Value:       0x00000000

        Field:           DIGLDO
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DIGITAL LDO

*/
#define PRCM_AON_PMSSPAR0_DIGLDO_W                                   16U
#define PRCM_AON_PMSSPAR0_DIGLDO_M                                   0x0000FFFFU
#define PRCM_AON_PMSSPAR0_DIGLDO_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMSSPAR1
    Offset name:         PRCM_AON_O_PMSSPAR1
    Relative address:    0x7128
    Description:         PMS SPARE REG 1

                        HW connected to PMCIO
    Default Value:       0x000000C0

        Field:           RCOSC
        From..to bits:   0...7
        DefaultValue:    0xC0
        Access type:     read-write
        Description:     RCOSC SPARE REG

*/
#define PRCM_AON_PMSSPAR1_RCOSC_W                                    8U
#define PRCM_AON_PMSSPAR1_RCOSC_M                                    0x000000FFU
#define PRCM_AON_PMSSPAR1_RCOSC_S                                    0U
/*

        Field:           DIGBG
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DIGITAL BAND GAP SPARE REGISTER

*/
#define PRCM_AON_PMSSPAR1_DIGBG_W                                    8U
#define PRCM_AON_PMSSPAR1_DIGBG_M                                    0x0000FF00U
#define PRCM_AON_PMSSPAR1_DIGBG_S                                    8U
/*

        Field:           DIGKA
        From..to bits:   24...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DIGITAL KEEP ALIVE SPARE REGISTER

*/
#define PRCM_AON_PMSSPAR1_DIGKA_W                                    8U
#define PRCM_AON_PMSSPAR1_DIGKA_M                                    0xFF000000U
#define PRCM_AON_PMSSPAR1_DIGKA_S                                    24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMSSPAR2
    Offset name:         PRCM_AON_O_PMSSPAR2
    Relative address:    0x712C
    Description:         PMS SPARE REG 2

                        HW connected to PMCIO
    Default Value:       0x00007E00

        Field:           VAL
        From..to bits:   0...15
        DefaultValue:    0x7E00
        Access type:     read-write
        Description:     VALUE

                         [9:5] - dig ldo test mux control
                         [4:0] - sram test mux control

*/
#define PRCM_AON_PMSSPAR2_VAL_W                                      16U
#define PRCM_AON_PMSSPAR2_VAL_M                                      0x0000FFFFU
#define PRCM_AON_PMSSPAR2_VAL_S                                      0U
/*

        Field:           OUT
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     VALUE

*/
#define PRCM_AON_PMSSPAR2_OUT_W                                      16U
#define PRCM_AON_PMSSPAR2_OUT_M                                      0xFFFF0000U
#define PRCM_AON_PMSSPAR2_OUT_S                                      16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMSCTLSTA
    Offset name:         PRCM_AON_O_PMSCTLSTA
    Relative address:    0x7130
    Description:         PMS CONTROL STATUS

                        PMS FSM cfg register
    Default Value:       0x00000036

        Field:           STA
        From..to bits:   0...7
        DefaultValue:    0x36
        Access type:     read-only
        Description:     PMS STATE

                         Following FSM controls PMU for mode transition from ACTIVE to HIBERNATE/LPDS and vice-versa
                         Power Mode PMU sequence:
                                                 (Go to sleep sequence example. Wakeup is reversed order)
                         bit[0] - LDOs_KA        (enable KA LDO's...               - wait 1c)
                         bit[1] - LDO_SRAM       (disable SRAM LDO...              - wait 1c)
                         bit[2] - LDO_DIG        (disable DIG  LDO...              - wait 1c)
                         bit[3] - RVM_LPM        (enable RVM Low Power Mode...     - wait 1c)
                         bit[4] - BG_CAP_SW      (disable BandGap Cap switch...    - wait 1c)
                         bit[5] - BG             (disable BandGap                  - wait 1c)

                         localparam [7:0]
                         PM_ACT                               = 8'b00_110110 , // ACTIVE - Steady State nr. 1
                         PM_GTS_LDO_KA_EN          = 8'b00_110111 ,
                         PM_GTS_LDO_SRAM_DIS    = 8'b00_110101 ,
                         PM_GTS_LDO_DIG_DIS       = 8'b00_110001 ,
                         PM_GTS_RVM_LPM_EN       = 8'b00_111001 ,
                         PM_GTS_BG_CAP_SW_DIS = 8'b00_101001 ,
                         PM_GTS_BG_DIS                = 8'b00_001001 ,
                         PM_SLP                              = 8'b01_001001 , // SLEEP  - Steady State nr. 2 (up to 20ms)
                         PM_SLP_TO_RFRSH            = 8'b01_101001 ,
                         PM_RFRSH                          = 8'b01_111001 , // Refresh - Steady State nr. 3 (up to 100us)
                         PM_RFRSH_TO_SLP            = 8'b10_101001 ,
                         PM_WKU_BG_EN                = 8'b11_101001 ,
                         PM_WKU_BG_CAP_SW_EN = 8'b11_111001 ,
                         PM_WKU_RVM_LPM_DIS     = 8'b11_110001 ,
                         PM_WKU_LDO_DIG_EN       = 8'b11_110101 ,
                         PM_WKU_LDO_SRAM_EN    = 8'b11_110111 ,
                         PM_WKU_LDO_KA_DIS        = 8'b11_110110 ;

*/
#define PRCM_AON_PMSCTLSTA_STA_W                                     8U
#define PRCM_AON_PMSCTLSTA_STA_M                                     0x000000FFU
#define PRCM_AON_PMSCTLSTA_STA_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMSSPARIN
    Offset name:         PRCM_AON_O_PMSSPARIN
    Relative address:    0x7134
    Description:         PMS SPARE INPUT

                        HW connected to PMCIO - spare input from PMCIO
    Default Value:       0x00000000

        Field:           REG0
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGISTER 0

                         <11> - '1' mask BOD and RVMs for 2 cycles in LPDS entry

*/
#define PRCM_AON_PMSSPARIN_REG0_W                                    16U
#define PRCM_AON_PMSSPARIN_REG0_M                                    0x0000FFFFU
#define PRCM_AON_PMSSPARIN_REG0_S                                    0U
/*

        Field:           GEBM
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SPARE_REG1 bit map [10]:
                         used for VBOXLO test

*/
#define PRCM_AON_PMSSPARIN_GEBM                                      0x04000000U
#define PRCM_AON_PMSSPARIN_GEBM_M                                    0x04000000U
#define PRCM_AON_PMSSPARIN_GEBM_S                                    26U
/*

        Field:           REG1
        From..to bits:   27...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SPARE_REG1 bit map [15:11]
                         bit <15>-
                         in PMU: no usage. Should not be used.
                         In PRCM: selects MMR control (S/W) mem_bod_comp_en/mem_rvml_comp_en/mem_rvmh_comp_en over the default control (H/W) for comparators BOD/RVML/RVMH enable respectively

*/
#define PRCM_AON_PMSSPARIN_REG1_W                                    5U
#define PRCM_AON_PMSSPARIN_REG1_M                                    0xF8000000U
#define PRCM_AON_PMSSPARIN_REG1_S                                    27U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMSPORTSTCTL
    Offset name:         PRCM_AON_O_PMSPORTSTCTL
    Relative address:    0x7138
    Description:         PMS POR TEST CONTROL

                        Test Mode control for POR POL block
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HW connected to PMCIO

*/
#define PRCM_AON_PMSPORTSTCTL_VAL_W                                  8U
#define PRCM_AON_PMSPORTSTCTL_VAL_M                                  0x000000FFU
#define PRCM_AON_PMSPORTSTCTL_VAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMSSPAR3
    Offset name:         PRCM_AON_O_PMSSPAR3
    Relative address:    0x7140
    Description:         PMS SPARE 3

                        HW connected to PMCIO
    Default Value:       0x01F2F200

        Field:           INT
        From..to bits:   2...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     INTERNAL

*/
#define PRCM_AON_PMSSPAR3_INT_W                                      4U
#define PRCM_AON_PMSSPAR3_INT_M                                      0x0000003CU
#define PRCM_AON_PMSSPAR3_INT_S                                      2U
/*

        Field:           SRAMKA
        From..to bits:   17...23
        DefaultValue:    0x79
        Access type:     read-write
        Description:     SRAM KEEP ALIVE

*/
#define PRCM_AON_PMSSPAR3_SRAMKA_W                                   7U
#define PRCM_AON_PMSSPAR3_SRAMKA_M                                   0x00FE0000U
#define PRCM_AON_PMSSPAR3_SRAMKA_S                                   17U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMSSPAR4
    Offset name:         PRCM_AON_O_PMSSPAR4
    Relative address:    0x7144
    Description:         PMS SPARE 4

                        HW connected to PMCIO
    Default Value:       0x00007E00

        Field:           PMBIST
        From..to bits:   0...15
        DefaultValue:    0x7E00
        Access type:     read-write
        Description:     [5:4] - rfcio test switch
                         [3:2] - adc test switch
                         [1]    - vdd main divider enable
                         [0]    - i2v divider enable

*/
#define PRCM_AON_PMSSPAR4_PMBIST_W                                   16U
#define PRCM_AON_PMSSPAR4_PMBIST_M                                   0x0000FFFFU
#define PRCM_AON_PMSSPAR4_PMBIST_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMSDLY
    Offset name:         PRCM_AON_O_PMSDLY
    Relative address:    0x7148
    Description:         PMS DELAYS

                        HW connected to PMCIO - spare input from PMCIO
    Default Value:       0x00155000

        Field:           GTS1
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     GO TO SLEEP DELAY 1

                         delay from PM_GTS_LDO_KA_EN to PM_GTS_LDO_SRAM_DIS

                         for additional details please review following page:
                         https://confluence.itg.ti.com/pages/viewpage.action?spaceKey=WNG&title=Osprey+PRCM+-+PMU

*/
#define PRCM_AON_PMSDLY_GTS1_W                                       2U
#define PRCM_AON_PMSDLY_GTS1_M                                       0x00000003U
#define PRCM_AON_PMSDLY_GTS1_S                                       0U
/*

        Field:           GTS2
        From..to bits:   2...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     GO TO SLEEP DELAY 2

                         delay from PM_GTS_LDO_SRAM_DIS to PM_GTS_LDO_DIG_DIS

                         for additional details please review following page:
                         https://confluence.itg.ti.com/pages/viewpage.action?spaceKey=WNG&title=Osprey+PRCM+-+PMU

*/
#define PRCM_AON_PMSDLY_GTS2_W                                       2U
#define PRCM_AON_PMSDLY_GTS2_M                                       0x0000000CU
#define PRCM_AON_PMSDLY_GTS2_S                                       2U
/*

        Field:           GTS3
        From..to bits:   4...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     GO TO SLEEP DELAY 3

                         delay from PM_GTS_LDO_DIG_DIS to PM_GTS_RVM_LPM_EN

                         for additional details please review following page:
                         https://confluence.itg.ti.com/pages/viewpage.action?spaceKey=WNG&title=Osprey+PRCM+-+PMU

*/
#define PRCM_AON_PMSDLY_GTS3_W                                       2U
#define PRCM_AON_PMSDLY_GTS3_M                                       0x00000030U
#define PRCM_AON_PMSDLY_GTS3_S                                       4U
/*

        Field:           GTS4
        From..to bits:   6...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     GO TO SLEEP DELAY 4

                         delay from PM_GTS_RVM_LPM_EN to PM_GTS_BG_CAP_SW_DIS

                         for additional details please review following page:
                         https://confluence.itg.ti.com/pages/viewpage.action?spaceKey=WNG&title=Osprey+PRCM+-+PMU

*/
#define PRCM_AON_PMSDLY_GTS4_W                                       2U
#define PRCM_AON_PMSDLY_GTS4_M                                       0x000000C0U
#define PRCM_AON_PMSDLY_GTS4_S                                       6U
/*

        Field:           GTS5
        From..to bits:   8...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     GO TO SLEEP DELAY 5

                         delay from PM_GTS_BG_CAP_SW_DIS to PM_GTS_BG_DIS

                         for additional details please review following page:
                         https://confluence.itg.ti.com/pages/viewpage.action?spaceKey=WNG&title=Osprey+PRCM+-+PMU

*/
#define PRCM_AON_PMSDLY_GTS5_W                                       2U
#define PRCM_AON_PMSDLY_GTS5_M                                       0x00000300U
#define PRCM_AON_PMSDLY_GTS5_S                                       8U
/*

        Field:           WU1
        From..to bits:   12...13
        DefaultValue:    0x1
        Access type:     read-write
        Description:     WAKEUP DELAY 1

                         delay from PM_WKU_BG_EN to PM_WKU_BG_CAP_SW_EN

                         for additional details please review following page:
                         https://confluence.itg.ti.com/pages/viewpage.action?spaceKey=WNG&title=Osprey+PRCM+-+PMU

*/
#define PRCM_AON_PMSDLY_WU1_W                                        2U
#define PRCM_AON_PMSDLY_WU1_M                                        0x00003000U
#define PRCM_AON_PMSDLY_WU1_S                                        12U
/*

        Field:           WU2
        From..to bits:   14...15
        DefaultValue:    0x1
        Access type:     read-write
        Description:     WAKEUP DELAY 2

                         delay from PM_WKU_BG_CAP_SW_EN to PM_WKU_RVM_LPM_DIS

                         for additional details please review following page:
                         https://confluence.itg.ti.com/pages/viewpage.action?spaceKey=WNG&title=Osprey+PRCM+-+PMU

*/
#define PRCM_AON_PMSDLY_WU2_W                                        2U
#define PRCM_AON_PMSDLY_WU2_M                                        0x0000C000U
#define PRCM_AON_PMSDLY_WU2_S                                        14U
/*

        Field:           WU3
        From..to bits:   16...17
        DefaultValue:    0x1
        Access type:     read-write
        Description:     WAKEUP DELAY 3

                         delay from PM_WKU_RVM_LPM_DIS to PM_WKU_LDO_DIG_EN

                         for additional details please review following page:
                         https://confluence.itg.ti.com/pages/viewpage.action?spaceKey=WNG&title=Osprey+PRCM+-+PMU

*/
#define PRCM_AON_PMSDLY_WU3_W                                        2U
#define PRCM_AON_PMSDLY_WU3_M                                        0x00030000U
#define PRCM_AON_PMSDLY_WU3_S                                        16U
/*

        Field:           WU4
        From..to bits:   18...19
        DefaultValue:    0x1
        Access type:     read-write
        Description:     WAKEUP DELAY 4

                         delay from PM_WKU_LDO_DIG_EN to PM_WKU_LDO_SRAM_EN

                         for additional details please review following page:
                         https://confluence.itg.ti.com/pages/viewpage.action?spaceKey=WNG&title=Osprey+PRCM+-+PMU

*/
#define PRCM_AON_PMSDLY_WU4_W                                        2U
#define PRCM_AON_PMSDLY_WU4_M                                        0x000C0000U
#define PRCM_AON_PMSDLY_WU4_S                                        18U
/*

        Field:           WU5
        From..to bits:   20...23
        DefaultValue:    0x1
        Access type:     read-write
        Description:     WAKEUP DELAY 5

                         delay from PM_WKU_LDO_SRAM_EN to PM_WKU_LDO_KA_DIS

                         for additional details please review following page:
                         https://confluence.itg.ti.com/pages/viewpage.action?spaceKey=WNG&title=Osprey+PRCM+-+PMU

                         Also used as LDO inrush Limit timer:
                         0- inrush limit to LDO's will be set 1 slow clock cycle (32us) after DIG LDO has been set
                         1- inrush limit to LDO's will be set 2 slow clock cycles (64us) after DIG LDO has been set (default)
                         2- inrush limit to LDO's will be set 3 slow clock cycles (96us) after DIG LDO has been set
                         ...
                         15- inrush limit to LDO's will be set 16 slow clock cycles (16*32us) after DIG LDO has been set
                         Note that SRAM LDO is set 1-4 cycles (1 is default) before DIG LDO is set. Inrush Limit covers both.

*/
#define PRCM_AON_PMSDLY_WU5_W                                        4U
#define PRCM_AON_PMSDLY_WU5_M                                        0x00F00000U
#define PRCM_AON_PMSDLY_WU5_S                                        20U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BGDISBGENDLY
    Offset name:         PRCM_AON_O_BGDISBGENDLY
    Relative address:    0x714C
    Description:         DIGITAL BANDGAP DISABLE BANDGAP ENABLE DELAY

                        time (sclk) in DBGAP hibernate mode
    Default Value:       0x00000005

        Field:           SLP
        From..to bits:   0...2
        DefaultValue:    0x5
        Access type:     read-write
        Description:     SLEEP

                         The sleep duration between refresh intervals - from BG disable (Going to Sleep) to BG enable (waking for refresh).
                         Granularity is 128 clocks (clock period is 31.25us) hence:
                         "000"  - N.A
                         "001"  -  4ms
                         "010"  -  8ms
                         "011"  -  12ms
                         "100"  -  16ms
                         "101"  -  20ms  (default)
                         "110"  -  24ms
                         "111"  -  28ms

*/
#define PRCM_AON_BGDISBGENDLY_SLP_W                                  3U
#define PRCM_AON_BGDISBGENDLY_SLP_M                                  0x00000007U
#define PRCM_AON_BGDISBGENDLY_SLP_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWENSWDISDLY
    Offset name:         PRCM_AON_O_SWENSWDISDLY
    Relative address:    0x7150
    Description:         SW ENABLE SW DISABLE DELAY

                        time (sclk) in DBGAP hibernate mode
    Default Value:       0x00000003

        Field:           SLP
        From..to bits:   0...2
        DefaultValue:    0x3
        Access type:     read-write
        Description:     SLEEP

                         The Refresh duration -  from Switch enable (go in refresh) to Switch disable (go out of refresh).
                         Granularity is 1 clock (clock period is 31.25us) hence:
                         "000"  -  31.25us
                         "001"  -  62.5us
                         "010"  -  93.75us
                         "011"  -  125us (default)
                         "100"  -  156.25us
                         "101"  -  187.5us
                         "110"  -  218.75us
                         "111"  -  250us

*/
#define PRCM_AON_SWENSWDISDLY_SLP_W                                  3U
#define PRCM_AON_SWENSWDISDLY_SLP_M                                  0x00000007U
#define PRCM_AON_SWENSWDISDLY_SLP_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BGENSWENDLY
    Offset name:         PRCM_AON_O_BGENSWENDLY
    Relative address:    0x7154
    Description:         BANDGAP ENABLE SW ENABLE SLEEP DELAY

                         time (sclk) in DBGAP hibernate mode
    Default Value:       0x00000001

        Field:           SLP
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     SLEEP

                         The duration from BG enable to SW enable (transition to refresh).
                         Granularity is 1 clock (clock period is 31.25us) hence:
                         "000"  -  31.25us
                         "001"  -  62.5us (default)
                         "010"  -  93.75us
                         "011"  -  125us
                         "100"  -  156.25us
                         "101"  -  187.5us
                         "110"  -  218.75us
                         "111"  -  250us

*/
#define PRCM_AON_BGENSWENDLY_SLP_W                                   2U
#define PRCM_AON_BGENSWENDLY_SLP_M                                   0x00000003U
#define PRCM_AON_BGENSWENDLY_SLP_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWDISBGDISDLY
    Offset name:         PRCM_AON_O_SWDISBGDISDLY
    Relative address:    0x7158
    Description:         SW DISABLE BANDGAP DISABLE DELAY

                        time (sclk) in DBGAP hibernate mode
    Default Value:       0x00000001

        Field:           SLP
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     SLEEP

                         The duration from SW disable to BG disable (transition from refresh).
                         Granularity is 1 clock (clock period is 31.25us) hence:
                         "000"  -  31.25us
                         "001"  -  62.5us (default)
                         "010"  -  93.75us
                         "011"  -  125us
                         "100"  -  156.25us
                         "101"  -  187.5us
                         "110"  -  218.75us
                         "111"  -  250us

*/
#define PRCM_AON_SWDISBGDISDLY_SLP_W                                 2U
#define PRCM_AON_SWDISBGDISDLY_SLP_M                                 0x00000003U
#define PRCM_AON_SWDISBGDISDLY_SLP_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ICGCTL
    Offset name:         PRCM_AON_O_ICGCTL
    Relative address:    0x715C
    Description:         ICG CONTROL
    Default Value:       0x0000000F

        Field:           COEXCLKREQ
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     '1' - request CLK for coex

*/
#define PRCM_AON_ICGCTL_COEXCLKREQ                                   0x00000001U
#define PRCM_AON_ICGCTL_COEXCLKREQ_M                                 0x00000001U
#define PRCM_AON_ICGCTL_COEXCLKREQ_S                                 0U
/*

        Field:           OCLACLKREQ
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     '1' - request CLK for ocla

*/
#define PRCM_AON_ICGCTL_OCLACLKREQ                                   0x00000002U
#define PRCM_AON_ICGCTL_OCLACLKREQ_M                                 0x00000002U
#define PRCM_AON_ICGCTL_OCLACLKREQ_S                                 1U
/*

        Field:           DBGSCLKREQ
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     '1' - request CLK for debugss

*/
#define PRCM_AON_ICGCTL_DBGSCLKREQ                                   0x00000004U
#define PRCM_AON_ICGCTL_DBGSCLKREQ_M                                 0x00000004U
#define PRCM_AON_ICGCTL_DBGSCLKREQ_S                                 2U
/*

        Field:           SFSCLKREQ
        From..to bits:   3...3
        DefaultValue:    0x1
        Access type:     read-write
        Description:     SLOW FUSE CLK REQ

                         '1' - request CLK for prcm fuse farm. default is '1'. S/W will clr to save power

*/
#define PRCM_AON_ICGCTL_SFSCLKREQ                                    0x00000008U
#define PRCM_AON_ICGCTL_SFSCLKREQ_M                                  0x00000008U
#define PRCM_AON_ICGCTL_SFSCLKREQ_S                                  3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HALT
    Offset name:         PRCM_AON_O_HALT
    Relative address:    0x7160
    Description:         HALT
    Default Value:       0x00000000

        Field:           DBGSEL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     select debug halt source:
                         0 - M33 Halt
                         1 - M3 Halt

*/
#define PRCM_AON_HALT_DBGSEL                                         0x00000001U
#define PRCM_AON_HALT_DBGSEL_M                                       0x00000001U
#define PRCM_AON_HALT_DBGSEL_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LOGICCA
    Offset name:         PRCM_AON_O_LOGICCA
    Relative address:    0x716C
    Description:         LOGIC CAPTURE
    Default Value:       0x0000000A

        Field:           PON0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     read clear

                         CORE PON indication fall

*/
#define PRCM_AON_LOGICCA_PON0                                        0x00000001U
#define PRCM_AON_LOGICCA_PON0_M                                      0x00000001U
#define PRCM_AON_LOGICCA_PON0_S                                      0U
/*

        Field:           PON1
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-only
        Description:     read clear

                         CORE PON indication set

*/
#define PRCM_AON_LOGICCA_PON1                                        0x00000002U
#define PRCM_AON_LOGICCA_PON1_M                                      0x00000002U
#define PRCM_AON_LOGICCA_PON1_S                                      1U
/*

        Field:           PGOOD0
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     read clear

                         CORE PGOOD indication fall

*/
#define PRCM_AON_LOGICCA_PGOOD0                                      0x00000004U
#define PRCM_AON_LOGICCA_PGOOD0_M                                    0x00000004U
#define PRCM_AON_LOGICCA_PGOOD0_S                                    2U
/*

        Field:           PGOOD1
        From..to bits:   3...3
        DefaultValue:    0x1
        Access type:     read-only
        Description:     read clear

                         CORE PGOOD indication set

*/
#define PRCM_AON_LOGICCA_PGOOD1                                      0x00000008U
#define PRCM_AON_LOGICCA_PGOOD1_M                                    0x00000008U
#define PRCM_AON_LOGICCA_PGOOD1_S                                    3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LOGICMEMSTA
    Offset name:         PRCM_AON_O_LOGICMEMSTA
    Relative address:    0x7170
    Description:         LOGIC MEMORY STATUS
    Default Value:       0x13000000

        Field:           CRAONIN
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CORE AONIN

*/
#define PRCM_AON_LOGICMEMSTA_CRAONIN_W                               12U
#define PRCM_AON_LOGICMEMSTA_CRAONIN_M                               0x00000FFFU
#define PRCM_AON_LOGICMEMSTA_CRAONIN_S                               0U
/*

        Field:           FLXAONIN
        From..to bits:   16...25
        DefaultValue:    0x300
        Access type:     read-only
        Description:     FLEX AONIN

*/
#define PRCM_AON_LOGICMEMSTA_FLXAONIN_W                              10U
#define PRCM_AON_LOGICMEMSTA_FLXAONIN_M                              0x03FF0000U
#define PRCM_AON_LOGICMEMSTA_FLXAONIN_S                              16U
/*

        Field:           CRPONIN
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CORE PONIN

*/
#define PRCM_AON_LOGICMEMSTA_CRPONIN                                 0x04000000U
#define PRCM_AON_LOGICMEMSTA_CRPONIN_M                               0x04000000U
#define PRCM_AON_LOGICMEMSTA_CRPONIN_S                               26U
/*

        Field:           AAONPONIN
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AAON PONIN

*/
#define PRCM_AON_LOGICMEMSTA_AAONPONIN                               0x08000000U
#define PRCM_AON_LOGICMEMSTA_AAONPONIN_M                             0x08000000U
#define PRCM_AON_LOGICMEMSTA_AAONPONIN_S                             27U
/*

        Field:           CRISO
        From..to bits:   28...28
        DefaultValue:    0x1
        Access type:     read-only
        Description:     CORE ISO

*/
#define PRCM_AON_LOGICMEMSTA_CRISO                                   0x10000000U
#define PRCM_AON_LOGICMEMSTA_CRISO_M                                 0x10000000U
#define PRCM_AON_LOGICMEMSTA_CRISO_S                                 28U
/*

        Field:           AAONISO
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     AAON ISO

*/
#define PRCM_AON_LOGICMEMSTA_AAONISO                                 0x20000000U
#define PRCM_AON_LOGICMEMSTA_AAONISO_M                               0x20000000U
#define PRCM_AON_LOGICMEMSTA_AAONISO_S                               29U
/*

        Field:           MEMSPWRUDNE
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-only
        Description:     MEMORIES POWERUP DONE

*/
#define PRCM_AON_LOGICMEMSTA_MEMSPWRUDNE                             0x40000000U
#define PRCM_AON_LOGICMEMSTA_MEMSPWRUDNE_M                           0x40000000U
#define PRCM_AON_LOGICMEMSTA_MEMSPWRUDNE_S                           30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HOL
    Offset name:         PRCM_AON_O_HOL
    Relative address:    0x7174
    Description:         HOLISTIC FSM
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     STATE

                         HOL_IDLE              		= 5'b00000
                         HOL_HW_BOOT1          		= 5'b00001
                         HOL_HW_BOOT2          		= 5'b00010
                         HOL_HW_BOOT3          		= 5'b00011
                         HOL_ACTIVE2           		= 5'b00100 (CORE & HOST active)
                         HOL_ACTIVE3           		= 5'b00101 (CORE sleep, HOST active)
                         HOL_ACTIVE4           		= 5'b00110 (CORE active, HOST sleep)
                         HOL_TRN_TRUE_SLEEP1		= 5'b00111
                         HOL_TRN_TRUE_SLEEP2		= 5'b01000
                         HOL_TRN_TRUE_SLEEP3		= 5'b01001
                         HOL_TRUE_SLEEP        		= 5'b01010 (CORE & HOST sleep)
                         HOL_PRCM_VLD_ACTIVE3  		= 5'b01011
                         HOL_AAON_ACTIVE3      		= 5'b01100
                         HOL_CORE_SLP_ACTIVE3  		= 5'b01101
                         HOL_CORE_ACT_ACTIVE3  		= 5'b01110
                         HOL_PRCM_VLD_ACTIVE4  		= 5'b01111
                         HOL_AAON_ACTIVE4      		= 5'b10000
                         HOL_HOST_SLP_ACTIVE4  		= 5'b10001
                         HOL_HOST_ACT_ACTIVE4  		= 5'b10010

*/
#define PRCM_AON_HOL_STA_W                                           5U
#define PRCM_AON_HOL_STA_M                                           0x0000001FU
#define PRCM_AON_HOL_STA_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PSCONHGEN
    Offset name:         PRCM_AON_O_PSCONHGEN
    Relative address:    0x7178
    Description:         PSCON HANDLER GENERAL
    Default Value:       0x00000004

        Field:           RTABHVEMOD
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     NU at MDB
                         Determine the RTA behavior in sleep/true sleep:
                         [0] - SLEEP MODE
                         [1] - TRUE SLEEP MODE

                         0 - OFF/OFF : in case issues with RTA toggling in sleep
                         1 - OFF/ON  : in case no ret in true sleep + in case issues with RTA toggling in sleep
                         2 - ON/OFF  : POR
                         3 - ON/ON   : In case use ret in true sleep

*/
#define PRCM_AON_PSCONHGEN_RTABHVEMOD_W                              2U
#define PRCM_AON_PSCONHGEN_RTABHVEMOD_M                              0x00000003U
#define PRCM_AON_PSCONHGEN_RTABHVEMOD_S                              0U
/*

        Field:           LOGUGTEBP
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     LOGIC UNGATE BYPASS

                         '1' - bypass the logic UNGATE request option
                         '0' - logic will generate ungate request

*/
#define PRCM_AON_PSCONHGEN_LOGUGTEBP                                 0x00000004U
#define PRCM_AON_PSCONHGEN_LOGUGTEBP_M                               0x00000004U
#define PRCM_AON_PSCONHGEN_LOGUGTEBP_S                               2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IOPROCSBIT
    Offset name:         PRCM_AON_O_IOPROCSBIT
    Relative address:    0x717C
    Description:         IO PROCESS BITS
    Default Value:       0x00000000

        Field:           OVPROGION
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE PROGIO N

                         Bit 2 is inverted between MMR and PAD -> so to configure the values 1,3,6 according to the corner, we need to set the registers to 5,7,2:

                         MAX: MMR --> p=n=2 ; PAD --> p=n=6
                         NOM: MMR --> p=n=7 ; PAD --> p=n=3
                         MIN: MMR --> p=n=5 ; PAD --> p=n=1

*/
#define PRCM_AON_IOPROCSBIT_OVPROGION_W                              3U
#define PRCM_AON_IOPROCSBIT_OVPROGION_M                              0x00000007U
#define PRCM_AON_IOPROCSBIT_OVPROGION_S                              0U
/*

        Field:           SELOVPROGION
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE PROIO N

                         process bit to io set

*/
#define PRCM_AON_IOPROCSBIT_SELOVPROGION                             0x00000008U
#define PRCM_AON_IOPROCSBIT_SELOVPROGION_M                           0x00000008U
#define PRCM_AON_IOPROCSBIT_SELOVPROGION_S                           3U
/*

        Field:           OVPROGIOP
        From..to bits:   4...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE PROGIO P

                         OVERRIDE PROGIO N

                         Bit 2 is inverted between MMR and PAD -> so to configure the values 1,3,6 according to the corner, we need to set the registers to 5,7,2:

                         MAX: MMR --> p=n=2 ; PAD --> p=n=6
                         NOM: MMR --> p=n=7 ; PAD --> p=n=3
                         MIN: MMR --> p=n=5 ; PAD --> p=n=1

*/
#define PRCM_AON_IOPROCSBIT_OVPROGIOP_W                              3U
#define PRCM_AON_IOPROCSBIT_OVPROGIOP_M                              0x00000070U
#define PRCM_AON_IOPROCSBIT_OVPROGIOP_S                              4U
/*

        Field:           SELOVPROGIOP
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE PROGIO P

                         process bit to io set

*/
#define PRCM_AON_IOPROCSBIT_SELOVPROGIOP                             0x00000080U
#define PRCM_AON_IOPROCSBIT_SELOVPROGIOP_M                           0x00000080U
#define PRCM_AON_IOPROCSBIT_SELOVPROGIOP_S                           7U
/*

        Field:           FSPROGION
        From..to bits:   8...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FUSE PROGIO N

                         OVERRIDE PROGIO N

                         Bit 2 is inverted between MMR and PAD -> so to configure the values 1,3,6 according to the corner, we need to set the registers to 5,7,2:

                         MAX: MMR --> p=n=2 ; PAD --> p=n=6
                         NOM: MMR --> p=n=7 ; PAD --> p=n=3
                         MIN: MMR --> p=n=5 ; PAD --> p=n=1

*/
#define PRCM_AON_IOPROCSBIT_FSPROGION_W                              3U
#define PRCM_AON_IOPROCSBIT_FSPROGION_M                              0x00000700U
#define PRCM_AON_IOPROCSBIT_FSPROGION_S                              8U
/*

        Field:           FSPROGIOP
        From..to bits:   12...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FUSE PROGIO P

                         OVERRIDE PROGIO N

                         Bit 2 is inverted between MMR and PAD -> so to configure the values 1,3,6 according to the corner, we need to set the registers to 5,7,2:

                         MAX: MMR --> p=n=2 ; PAD --> p=n=6
                         NOM: MMR --> p=n=7 ; PAD --> p=n=3
                         MIN: MMR --> p=n=5 ; PAD --> p=n=1

*/
#define PRCM_AON_IOPROCSBIT_FSPROGIOP_W                              3U
#define PRCM_AON_IOPROCSBIT_FSPROGIOP_M                              0x00007000U
#define PRCM_AON_IOPROCSBIT_FSPROGIOP_S                              12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SCLKCNTCTLCR
    Offset name:         PRCM_AON_O_SCLKCNTCTLCR
    Relative address:    0x7180
    Description:         SLOW CLOCK COUNT CONTROL CORE
    Default Value:       0x0000000C

        Field:           MOD
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     MODE

                         Determine the Slow clock counter mode-
                         0x3 - Reserved
                         0x2 - Periodic
                         0x1 - One Shot
                         0x0 - Disable

*/
#define PRCM_AON_SCLKCNTCTLCR_MOD_W                                  2U
#define PRCM_AON_SCLKCNTCTLCR_MOD_M                                  0x00000003U
#define PRCM_AON_SCLKCNTCTLCR_MOD_S                                  0U
/*

        Field:           PER
        From..to bits:   2...8
        DefaultValue:    0x3
        Access type:     read-only
        Description:     Determine the Slow clock counter period (Slow Clock cycles), 1 - 128.
                         '0' - 1 CLK cycle
                         '1' - 2 CLK cycles
                         '2' - 3 CLK cycles
                         ...
                         '127' - 128 CLK cycles

*/
#define PRCM_AON_SCLKCNTCTLCR_PER_W                                  7U
#define PRCM_AON_SCLKCNTCTLCR_PER_M                                  0x000001FCU
#define PRCM_AON_SCLKCNTCTLCR_PER_S                                  2U
/*

        Field:           RESULT
        From..to bits:   9...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Slow Clock counter result

*/
#define PRCM_AON_SCLKCNTCTLCR_RESULT_W                               15U
#define PRCM_AON_SCLKCNTCTLCR_RESULT_M                               0x00FFFE00U
#define PRCM_AON_SCLKCNTCTLCR_RESULT_S                               9U
/*

        Field:           RESULTVAL
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RESULT VALID

                         Determine whether the measurement is in progress or done:
                         0x0 - In progress (Relevant in one shot only)
                         0x1 - Done (when finish measurement and result ready)

*/
#define PRCM_AON_SCLKCNTCTLCR_RESULTVAL                              0x01000000U
#define PRCM_AON_SCLKCNTCTLCR_RESULTVAL_M                            0x01000000U
#define PRCM_AON_SCLKCNTCTLCR_RESULTVAL_S                            24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STACR
    Offset name:         PRCM_AON_O_STACR
    Relative address:    0x7184
    Description:         STATUS CORE
    Default Value:       0x00000000

        Field:           FREQDETVAL
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     fast clock frequency detection value :
                         0: 10MHz
                         1: 26MHz
                         2: 40MHz
                         3: 52MHz

*/
#define PRCM_AON_STACR_FREQDETVAL_W                                  2U
#define PRCM_AON_STACR_FREQDETVAL_M                                  0x00000003U
#define PRCM_AON_STACR_FREQDETVAL_S                                  0U
/*

        Field:           BODCOMP
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     '1' - GOOD

*/
#define PRCM_AON_STACR_BODCOMP                                       0x00000004U
#define PRCM_AON_STACR_BODCOMP_M                                     0x00000004U
#define PRCM_AON_STACR_BODCOMP_S                                     2U
/*

        Field:           RVMHCOMP
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     '1' - GOOD

*/
#define PRCM_AON_STACR_RVMHCOMP                                      0x00000008U
#define PRCM_AON_STACR_RVMHCOMP_M                                    0x00000008U
#define PRCM_AON_STACR_RVMHCOMP_S                                    3U
/*

        Field:           RVMLCOMP
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     '1' - GOOD

*/
#define PRCM_AON_STACR_RVMLCOMP                                      0x00000010U
#define PRCM_AON_STACR_RVMLCOMP_M                                    0x00000010U
#define PRCM_AON_STACR_RVMLCOMP_S                                    4U
/*

        Field:           PLOCK
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     '1' - pll sharing pll lock

*/
#define PRCM_AON_STACR_PLOCK                                         0x00000020U
#define PRCM_AON_STACR_PLOCK_M                                       0x00000020U
#define PRCM_AON_STACR_PLOCK_S                                       5U
/*

        Field:           PLOCKMON
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     PLL SHARING LOCK MONITOR

*/
#define PRCM_AON_STACR_PLOCKMON                                      0x00000040U
#define PRCM_AON_STACR_PLOCKMON_M                                    0x00000040U
#define PRCM_AON_STACR_PLOCKMON_S                                    6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AAONLOGCAPT
    Offset name:         PRCM_AON_O_AAONLOGCAPT
    Relative address:    0x718C
    Description:         AAON LOGIC CAPTURE
    Default Value:       0x0000000A

        Field:           PON0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     read clear

                         AAON PON indication fall

*/
#define PRCM_AON_AAONLOGCAPT_PON0                                    0x00000001U
#define PRCM_AON_AAONLOGCAPT_PON0_M                                  0x00000001U
#define PRCM_AON_AAONLOGCAPT_PON0_S                                  0U
/*

        Field:           PON1
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-only
        Description:     read clear

                         AAON PON indication set

*/
#define PRCM_AON_AAONLOGCAPT_PON1                                    0x00000002U
#define PRCM_AON_AAONLOGCAPT_PON1_M                                  0x00000002U
#define PRCM_AON_AAONLOGCAPT_PON1_S                                  1U
/*

        Field:           PGOOD0
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     read clear

                         AAON PGOOD indication fall

*/
#define PRCM_AON_AAONLOGCAPT_PGOOD0                                  0x00000004U
#define PRCM_AON_AAONLOGCAPT_PGOOD0_M                                0x00000004U
#define PRCM_AON_AAONLOGCAPT_PGOOD0_S                                2U
/*

        Field:           PGOOD1
        From..to bits:   3...3
        DefaultValue:    0x1
        Access type:     read-only
        Description:     read clear

                         AAON PGOOD indication set

*/
#define PRCM_AON_AAONLOGCAPT_PGOOD1                                  0x00000008U
#define PRCM_AON_AAONLOGCAPT_PGOOD1_M                                0x00000008U
#define PRCM_AON_AAONLOGCAPT_PGOOD1_S                                3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HWDT
    Offset name:         PRCM_AON_O_HWDT
    Relative address:    0x7190
    Description:         HOST WATCH DOG TIMER
    Default Value:       0x00000000

        Field:           FSENOV
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FUSE ENABLE OVERRIDE

                         '1'- override fuse bit value (regular operation)
                         '0'- use fuse bit value.

*/
#define PRCM_AON_HWDT_FSENOV                                         0x00000001U
#define PRCM_AON_HWDT_FSENOV_M                                       0x00000001U
#define PRCM_AON_HWDT_FSENOV_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SCLKCNTCR
    Offset name:         PRCM_AON_O_SCLKCNTCR
    Relative address:    0x7194
    Description:         SLOW CLK COUNT CORE
    Default Value:       0x00000000

        Field:           FCLKDET
        From..to bits:   0...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FAST CLK DETECTION COUNTER

                         Counter results for 4 slow clock
                         freq        lower 	upper
                         (MHz)    (dec)          (dec)
                         10          1190          1503
                         26          3094          3908
                         40   	      4760          6012
                         52          6188          7815

*/
#define PRCM_AON_SCLKCNTCR_FCLKDET_W                                 15U
#define PRCM_AON_SCLKCNTCR_FCLKDET_M                                 0x00007FFFU
#define PRCM_AON_SCLKCNTCR_FCLKDET_S                                 0U
/*

        Field:           PERVAL
        From..to bits:   16...22
        DefaultValue:    0x0
        Access type:     read-only
        Description:     PERIOD VALUE

                         slow CLK current value.
                         bounds are 0 to slow_clk_counter_period

*/
#define PRCM_AON_SCLKCNTCR_PERVAL_W                                  7U
#define PRCM_AON_SCLKCNTCR_PERVAL_M                                  0x007F0000U
#define PRCM_AON_SCLKCNTCR_PERVAL_S                                  16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SRAMLDO
    Offset name:         PRCM_AON_O_SRAMLDO
    Relative address:    0x7198
    Description:         SRAM LDO gen cfg register
    Default Value:       0x00000002

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ENABLE

                         status of final SRAM LDO enable

*/
#define PRCM_AON_SRAMLDO_EN                                          0x00000001U
#define PRCM_AON_SRAMLDO_EN_M                                        0x00000001U
#define PRCM_AON_SRAMLDO_EN_S                                        0U
/*

        Field:           OVEN
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OVERRIDE ENABLE

                         override value for SRAM LDO

*/
#define PRCM_AON_SRAMLDO_OVEN                                        0x00000002U
#define PRCM_AON_SRAMLDO_OVEN_M                                      0x00000002U
#define PRCM_AON_SRAMLDO_OVEN_S                                      1U
/*

        Field:           SELOVEN
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT OVERRIDE ENABLE

                         1: select override value for SRAM LDO enable : 0: SRAM LDO enable from FSM

*/
#define PRCM_AON_SRAMLDO_SELOVEN                                     0x00000004U
#define PRCM_AON_SRAMLDO_SELOVEN_M                                   0x00000004U
#define PRCM_AON_SRAMLDO_SELOVEN_S                                   2U
/*

        Field:           WKUINRSHLIM
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     WAKEUP INRUSH LIMIT

                         status of final SRAM LDO enable

*/
#define PRCM_AON_SRAMLDO_WKUINRSHLIM                                 0x00000008U
#define PRCM_AON_SRAMLDO_WKUINRSHLIM_M                               0x00000008U
#define PRCM_AON_SRAMLDO_WKUINRSHLIM_S                               3U
/*

        Field:           ENINRSHLIM
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable Inrush Current Limit Mask

*/
#define PRCM_AON_SRAMLDO_ENINRSHLIM                                  0x00000010U
#define PRCM_AON_SRAMLDO_ENINRSHLIM_M                                0x00000010U
#define PRCM_AON_SRAMLDO_ENINRSHLIM_S                                4U
/*

        Field:           SELENINRSHLIM
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECT ENABLE INRUSH LIMIT

                         Select for S/W Enabling the Inrush Current Limit Mask

*/
#define PRCM_AON_SRAMLDO_SELENINRSHLIM                               0x00000020U
#define PRCM_AON_SRAMLDO_SELENINRSHLIM_M                             0x00000020U
#define PRCM_AON_SRAMLDO_SELENINRSHLIM_S                             5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBG
    Offset name:         PRCM_AON_O_DBG
    Relative address:    0x719C
    Description:         DEBUG
    Default Value:       0x00000000

        Field:           CLKSEL
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CLOCK SELECT

                         Debug and Fast CLK detection selector

                         'x00' - prcm_fast_clock.
                         'x01' - ospr_hsm_tst_fro_clk_out
                         'x10' - clk_gpadc_clk
                         'x11' - fref_2m_socpll_1p8v
                         '100' - rf_pll_divided_clk


*/
#define PRCM_AON_DBG_CLKSEL_W                                        3U
#define PRCM_AON_DBG_CLKSEL_M                                        0x00000007U
#define PRCM_AON_DBG_CLKSEL_S                                        0U
/*

        Field:           SHADWSET
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SHADOW SET

                         '1' - override condition to load shadow values at FREF and PLLSH

*/
#define PRCM_AON_DBG_SHADWSET                                        0x00010000U
#define PRCM_AON_DBG_SHADWSET_M                                      0x00010000U
#define PRCM_AON_DBG_SHADWSET_S                                      16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RSTOVCTL
    Offset name:         PRCM_AON_O_RSTOVCTL
    Relative address:    0x71A0
    Description:         reset override control register, active low polarity:
                        '0' - override reset (force reset line to 0, reset asserted, active low)
                        '1' - don't override reset
    Default Value:       0x00000000

        Field:           SDIO
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     NOT USED

                         write clear

                         '1' - request CLK for sdio sw

*/
#define PRCM_AON_RSTOVCTL_SDIO                                       0x00000001U
#define PRCM_AON_RSTOVCTL_SDIO_M                                     0x00000001U
#define PRCM_AON_RSTOVCTL_SDIO_S                                     0U
/*

        Field:           SDIOAO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     NOT USED

                         write clear

                         '1' - request CLK for sdio ao

*/
#define PRCM_AON_RSTOVCTL_SDIOAO                                     0x00000002U
#define PRCM_AON_RSTOVCTL_SDIOAO_M                                   0x00000002U
#define PRCM_AON_RSTOVCTL_SDIOAO_S                                   1U
/*

        Field:           PSCON
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     '1' - request CLK for sdio PSCON

                         write clear

*/
#define PRCM_AON_RSTOVCTL_PSCON                                      0x00000004U
#define PRCM_AON_RSTOVCTL_PSCON_M                                    0x00000004U
#define PRCM_AON_RSTOVCTL_PSCON_S                                    2U
/*

        Field:           CR
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     CORE

                         write clear

                         '1' - request CLK for sdio CORE

*/
#define PRCM_AON_RSTOVCTL_CR                                         0x00000008U
#define PRCM_AON_RSTOVCTL_CR_M                                       0x00000008U
#define PRCM_AON_RSTOVCTL_CR_S                                       3U
/*

        Field:           PRCMREGS
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     NOT USED

                         write clear

*/
#define PRCM_AON_RSTOVCTL_PRCMREGS                                   0x00000010U
#define PRCM_AON_RSTOVCTL_PRCMREGS_M                                 0x00000010U
#define PRCM_AON_RSTOVCTL_PRCMREGS_S                                 4U
/*

        Field:           DBGSS
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     DEBUGSS

                         write clear

                         '1' - request CLK for sdio DEBUGSS

*/
#define PRCM_AON_RSTOVCTL_DBGSS                                      0x00000020U
#define PRCM_AON_RSTOVCTL_DBGSS_M                                    0x00000020U
#define PRCM_AON_RSTOVCTL_DBGSS_S                                    5U
/*

        Field:           TEST
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     NOT USED

                         write clear

*/
#define PRCM_AON_RSTOVCTL_TEST                                       0x00000080U
#define PRCM_AON_RSTOVCTL_TEST_M                                     0x00000080U
#define PRCM_AON_RSTOVCTL_TEST_S                                     7U
/*

        Field:           HOSTAON
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     HOSTAON

                         write clear

                         '1' - request CLK for sdio HOST AON

*/
#define PRCM_AON_RSTOVCTL_HOSTAON                                    0x00000100U
#define PRCM_AON_RSTOVCTL_HOSTAON_M                                  0x00000100U
#define PRCM_AON_RSTOVCTL_HOSTAON_S                                  8U
/*

        Field:           CRAON
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     CORE AON

                         write clear

                         '1' - request CLK for sdio CORE AON

*/
#define PRCM_AON_RSTOVCTL_CRAON                                      0x00000200U
#define PRCM_AON_RSTOVCTL_CRAON_M                                    0x00000200U
#define PRCM_AON_RSTOVCTL_CRAON_S                                    9U
/*

        Field:           MEMSS
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     MEMORY SUB SYSTEM

                         write clear

*/
#define PRCM_AON_RSTOVCTL_MEMSS                                      0x00000800U
#define PRCM_AON_RSTOVCTL_MEMSS_M                                    0x00000800U
#define PRCM_AON_RSTOVCTL_MEMSS_S                                    11U
/*

        Field:           FUSE
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     write-only
        Description:     FUSE FARM

                         write clear


                         '1' - request CLK for sdio FUSEFARM

*/
#define PRCM_AON_RSTOVCTL_FUSE                                       0x00001000U
#define PRCM_AON_RSTOVCTL_FUSE_M                                     0x00001000U
#define PRCM_AON_RSTOVCTL_FUSE_S                                     12U
/*

        Field:           GPADC
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     write-only
        Description:     GPADC

                         write clear

                         '1' - request CLK for sdio GPADC

*/
#define PRCM_AON_RSTOVCTL_GPADC                                      0x00002000U
#define PRCM_AON_RSTOVCTL_GPADC_M                                    0x00002000U
#define PRCM_AON_RSTOVCTL_GPADC_S                                    13U
/*

        Field:           TSENSE
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     write-only
        Description:     NOT USED

                         write clear

                         '1' - no reset

*/
#define PRCM_AON_RSTOVCTL_TSENSE                                     0x00004000U
#define PRCM_AON_RSTOVCTL_TSENSE_M                                   0x00004000U
#define PRCM_AON_RSTOVCTL_TSENSE_S                                   14U
/*

        Field:           FREF
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     write-only
        Description:     FREF

                         write clear

                         '1' - request CLK for FREF

*/
#define PRCM_AON_RSTOVCTL_FREF                                       0x00008000U
#define PRCM_AON_RSTOVCTL_FREF_M                                     0x00008000U
#define PRCM_AON_RSTOVCTL_FREF_S                                     15U
/*

        Field:           AAON
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     AAON

                         write clear

                         '1' - request CLK for sdio AAON

*/
#define PRCM_AON_RSTOVCTL_AAON                                       0x00010000U
#define PRCM_AON_RSTOVCTL_AAON_M                                     0x00010000U
#define PRCM_AON_RSTOVCTL_AAON_S                                     16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PMURSTCLR
    Offset name:         PRCM_AON_O_PMURSTCLR
    Relative address:    0x71A4
    Description:         PMU RESET CLEAR

                        Level registers- need to set high and low to clear WDT or DEBUGSS indications.
                        Set '1' to those fields will automated a pulse to pmu.
                        clear this field to '0' after use.
    Default Value:       0x00000000

        Field:           WDTCAUS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PRCM SPARE REG 1

                         [7] - mem_rst_wdt_cause_clr
                         '1' - clear wdt reset cause

*/
#define PRCM_AON_PMURSTCLR_WDTCAUS                                   0x00000001U
#define PRCM_AON_PMURSTCLR_WDTCAUS_M                                 0x00000001U
#define PRCM_AON_PMURSTCLR_WDTCAUS_S                                 0U
/*

        Field:           DBGSSCAUS
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PRCM SPARE REG 1

                         [8] - mem_rst_debugss_cause_clr
                         '1' - clear debugss reset cause

*/
#define PRCM_AON_PMURSTCLR_DBGSSCAUS                                 0x00000002U
#define PRCM_AON_PMURSTCLR_DBGSSCAUS_M                               0x00000002U
#define PRCM_AON_PMURSTCLR_DBGSSCAUS_S                               1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMGCTLCRSTAT1
    Offset name:         PRCM_AON_O_MEMGCTLCRSTAT1
    Relative address:    0x71A8
    Description:         MEMORY GROUP CONTROL CORE STATIC 1

                        Bank power State When owner IP Active/Sleep (power domain is ON/OFF)

                        0 - OFF/OFF
                        1 - Reserved
                        2 - ON/OFF
                        3 - ON/RET
    Default Value:       0xFFFFFFFF

        Field:           PWRSTA1
        From..to bits:   0...1
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 1

                         Group 11

*/
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA1_W                            2U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA1_M                            0x00000003U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA1_S                            0U
/*

        Field:           PWRSTA2
        From..to bits:   2...3
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 2

                         Group 12

*/
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA2_W                            2U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA2_M                            0x0000000CU
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA2_S                            2U
/*

        Field:           PWRSTA3
        From..to bits:   4...5
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 3

                         Group 13

*/
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA3_W                            2U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA3_M                            0x00000030U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA3_S                            4U
/*

        Field:           PWRSTA4
        From..to bits:   6...7
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 4

                         Group 14

*/
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA4_W                            2U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA4_M                            0x000000C0U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA4_S                            6U
/*

        Field:           PWRSTA5
        From..to bits:   8...9
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 5

                         Group 15

*/
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA5_W                            2U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA5_M                            0x00000300U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA5_S                            8U
/*

        Field:           PWRSTA6
        From..to bits:   10...11
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 6

                         Group 16

*/
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA6_W                            2U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA6_M                            0x00000C00U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA6_S                            10U
/*

        Field:           PWRSTA7
        From..to bits:   12...13
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 7

                         Group 17

*/
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA7_W                            2U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA7_M                            0x00003000U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA7_S                            12U
/*

        Field:           PWRSTA8
        From..to bits:   14...15
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 8

                         Group 18

*/
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA8_W                            2U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA8_M                            0x0000C000U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA8_S                            14U
/*

        Field:           PWRSTA9
        From..to bits:   16...17
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 9

                         Group 19

*/
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA9_W                            2U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA9_M                            0x00030000U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA9_S                            16U
/*

        Field:           PWRSTA10
        From..to bits:   18...19
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 10

                         Group 20

*/
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA10_W                           2U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA10_M                           0x000C0000U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA10_S                           18U
/*

        Field:           PWRSTA11
        From..to bits:   20...21
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 11

                         Group 21

*/
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA11_W                           2U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA11_M                           0x00300000U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA11_S                           20U
/*

        Field:           PWRSTA12
        From..to bits:   22...23
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 12

                         Group 22

*/
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA12_W                           2U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA12_M                           0x00C00000U
#define PRCM_AON_MEMGCTLCRSTAT1_PWRSTA12_S                           22U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMGCTLCRFLEX
    Offset name:         PRCM_AON_O_MEMGCTLCRFLEX
    Relative address:    0x71AC
    Description:         MEMORY GROUP CONTROL CORE FLEX

                        Applicable only if MODE selected flex as CORE memory.
                        Bank power State When owner IP Active/Sleep (power domain is ON/OFF)

                        0 - OFF/OFF
                        1 - Reserved
                        2 - ON/OFF
                        3 - ON/RET
    Default Value:       0x000FFFFF

        Field:           PWRSTA1
        From..to bits:   0...1
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 1

                         Group 1

*/
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA1_W                             2U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA1_M                             0x00000003U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA1_S                             0U
/*

        Field:           PWRSTA2
        From..to bits:   2...3
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 2

                         Group 2

*/
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA2_W                             2U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA2_M                             0x0000000CU
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA2_S                             2U
/*

        Field:           PWRSTA3
        From..to bits:   4...5
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 3

                         Group 3

*/
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA3_W                             2U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA3_M                             0x00000030U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA3_S                             4U
/*

        Field:           PWRSTA4
        From..to bits:   6...7
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 4

                         Group 4

*/
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA4_W                             2U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA4_M                             0x000000C0U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA4_S                             6U
/*

        Field:           PWRSTA5
        From..to bits:   8...9
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 5

                         Group 5

*/
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA5_W                             2U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA5_M                             0x00000300U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA5_S                             8U
/*

        Field:           PWRSTA6
        From..to bits:   10...11
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 6

                         Group 6

*/
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA6_W                             2U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA6_M                             0x00000C00U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA6_S                             10U
/*

        Field:           PWRSTA7
        From..to bits:   12...13
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 7

                         Group 7

*/
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA7_W                             2U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA7_M                             0x00003000U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA7_S                             12U
/*

        Field:           PWRSTA8
        From..to bits:   14...15
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 8

                         Group 8

*/
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA8_W                             2U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA8_M                             0x0000C000U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA8_S                             14U
/*

        Field:           PWRSTA9
        From..to bits:   16...17
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 9

                         Group 9

*/
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA9_W                             2U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA9_M                             0x00030000U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA9_S                             16U
/*

        Field:           PWRSTA10
        From..to bits:   18...19
        DefaultValue:    0x3
        Access type:     read-write
        Description:     POWER STATE 10

                         Group 10

*/
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA10_W                            2U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA10_M                            0x000C0000U
#define PRCM_AON_MEMGCTLCRFLEX_PWRSTA10_S                            18U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CRSH
    Offset name:         PRCM_AON_O_CRSH
    Relative address:    0x71B0
    Description:         CORE SHARED

                        override values for PRCM SHARED Modules
    Default Value:       0x00000000

        Field:           PMSREQOV
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PMS REQUEST OVERRIDE

                         '1' - keeps awake at sleep state
                         '0' - regular operation

*/
#define PRCM_AON_CRSH_PMSREQOV                                       0x00000001U
#define PRCM_AON_CRSH_PMSREQOV_M                                     0x00000001U
#define PRCM_AON_CRSH_PMSREQOV_S                                     0U
/*

        Field:           FREFREQOV
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FREF REQUEST OVERRIDE

                         '1' - keeps awake at sleep state
                         '0' - regular operation

                         note: in order to set this field as '1', PMS OV must be set as well.

*/
#define PRCM_AON_CRSH_FREFREQOV                                      0x00000002U
#define PRCM_AON_CRSH_FREFREQOV_M                                    0x00000002U
#define PRCM_AON_CRSH_FREFREQOV_S                                    1U
/*

        Field:           PLLSHREQOV
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PLL SHAREING REQUEST OVERRIDE

                         '1' - keeps awake at sleep state
                         '0' - regular operation

                         note: in order to set this field as '1', FREF OV and PMS OV must be set as well.

*/
#define PRCM_AON_CRSH_PLLSHREQOV                                     0x00000004U
#define PRCM_AON_CRSH_PLLSHREQOV_M                                   0x00000004U
#define PRCM_AON_CRSH_PLLSHREQOV_S                                   2U

#endif /* __HW_PRCM_AON_H__*/
