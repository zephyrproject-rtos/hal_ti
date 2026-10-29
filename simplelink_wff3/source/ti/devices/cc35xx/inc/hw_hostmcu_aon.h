/******************************************************************************
*  Filename:       hw_hostmcu_aon.h
*
*  Description:    Defines and prototypes for the HOSTMCU_AON peripheral.
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
#ifndef __HW_HOSTMCU_AON_H__
#define __HW_HOSTMCU_AON_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the HOSTMCU_AON component

--------------------------------------------------------------------------------- */

//Wake up Control Skip Configuration
#define HOSTMCU_AON_O_WUCSKPCFG                                      0x00000004U

//Configure WIC SENSE
#define HOSTMCU_AON_O_CFGWICSNS                                      0x00000008U

//ELP Wake-up Type Configuration
#define HOSTMCU_AON_O_CFGWUTP                                        0x0000000CU

//ELP Timer Enable
#define HOSTMCU_AON_O_ELPTMREN                                       0x00000010U

//Timer Wake-up Configuration
#define HOSTMCU_AON_O_CFGTMRWU                                       0x00000014U

//Timer Wake-up Request Clear
#define HOSTMCU_AON_O_TMRWUREQ                                       0x00000018U

//Watch Dog Timer Configuration
#define HOSTMCU_AON_O_CFGWDT                                         0x0000001CU

//Watch Dog Timer Request Clear
#define HOSTMCU_AON_O_WDTREQ                                         0x00000020U

//GPIO Wake-up AND IRQ Configuration
#define HOSTMCU_AON_O_GPWUAND                                        0x00000028U

//GPIO Wake-up OR IRQ Configuration
#define HOSTMCU_AON_O_GPWUOR                                         0x0000002CU

//GPIO Wake-up AND IRQ Configuration
#define HOSTMCU_AON_O_GPWUAND1                                       0x00000030U

//GPIO Wake-up OR IRQ Configuration
#define HOSTMCU_AON_O_GPWUOR1                                        0x00000034U

//Fast Clock From ARM Command
#define HOSTMCU_AON_O_FCLKARM                                        0x00000038U

//Sleep Time Slow Clock
#define HOSTMCU_AON_O_SLPTIMES                                       0x0000003CU

//Sleep Time Fast Clock
#define HOSTMCU_AON_O_SLPTIMEF                                       0x00000040U

//Wake up Request Status
#define HOSTMCU_AON_O_WUREQ                                          0x0000004CU

//OSPI Reference Clock
#define HOSTMCU_AON_O_OREFCLK                                        0x00000050U

//Wake-up Control State
#define HOSTMCU_AON_O_WUC                                            0x0000005CU



/*-----------------------------------REGISTER------------------------------------
    Register name:       WUCSKPCFG
    Offset name:         HOSTMCU_AON_O_WUCSKPCFG
    Relative address:    0x4
    Description:         Wake up Control Skip Configuration
    Default Value:       0x00000000

        Field:           SKPPRCMVLD
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SKIP PRCM VALID

                         Enable skip precise duration for PRCM Shared UP if wake up event type is '0':
                         '0' - don't skip
                         '1' - skip

        ENUMs:
            DIS:                         Don't Skip
            EN:                          Skip
*/
#define HOSTMCU_AON_WUCSKPCFG_SKPPRCMVLD                             0x00000001U
#define HOSTMCU_AON_WUCSKPCFG_SKPPRCMVLD_M                           0x00000001U
#define HOSTMCU_AON_WUCSKPCFG_SKPPRCMVLD_S                           0U
#define HOSTMCU_AON_WUCSKPCFG_SKPPRCMVLD_DIS                         0x00000000U
#define HOSTMCU_AON_WUCSKPCFG_SKPPRCMVLD_EN                          0x00000001U
/*

        Field:           SKPPDVLD
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SKIP POWER DOMAIN VALID

                         Enable skip precise duration for Power Domain if wake up event type is '0':
                         '0' - don't skip
                         '1' - skip

        ENUMs:
            DIS:                         Don't skip
            EN:                          Skip
*/
#define HOSTMCU_AON_WUCSKPCFG_SKPPDVLD                               0x00000002U
#define HOSTMCU_AON_WUCSKPCFG_SKPPDVLD_M                             0x00000002U
#define HOSTMCU_AON_WUCSKPCFG_SKPPDVLD_S                             1U
#define HOSTMCU_AON_WUCSKPCFG_SKPPDVLD_DIS                           0x00000000U
#define HOSTMCU_AON_WUCSKPCFG_SKPPDVLD_EN                            0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGWICSNS
    Offset name:         HOSTMCU_AON_O_CFGWICSNS
    Relative address:    0x8
    Description:         Configure WIC SENSE
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Field to control wake up source

                         Set 1 - Enable wake up source.
                         Set 0 - Disable wake up source.

                         Bit 0   : ELP TMR Wake up request
                         Bit 1   : GPIO wake up src 0
                         Bit 2   : GPIO wake up src 1
                         Bit 3   : doorbell 0
                         Bit 4   : doorbell 1
                         Bit 5   : doorbell 2
                         Bit 6   : doorbell 3
                         Bit 7   : doorbell 4
                         Bit 8   : doorbell 5
                         Bit 9   : doorbell 6
                         Bit 10 : doorbell 7
                         Bit 11 : nab_host_irq
                         Bit 12 : ble_rfc_gpo_8_irq
                         Bit 13 : RTC
                         Bit 14 : DebugSS Csyspwrupreq
                         Bit 15 : DebugSS Forceactive
                         Bit 16 : secured_error_irq
                         Bit 17 : core wdt irq

                         Note: GPIO wakeup src 0 is AND of wakeup sources and GPIO wakup src 1 is OR of wakeup sources

        ENUMs:
            DIS:                         Disable wakeup source
            TMRREQ_EN:                   ELP timer wakeup request
            WUSRC0_EN:                   AND of wakeup sources
            WUSRC1_EN:                   OR of wakeup sources
            DRBL0_EN:                    Doorbell 0
            DRBL1_EN:                    Doorbell 1
            DRBL2_EN:                    Doorbell 2
            DRBL3_EN:                    Doorbell 3
            DRBL4_EN:                    Doorbell 4
            DRBL5_EN:                    Doorbell 5
            DRBL6_EN:                    Doorbell 6
            DRBL7_EN:                    Doorbell 7
            NAB_EN:                      NAB host irq
            BLERFCGPO_EN:                BLE RFC GPO 9 irq
            RTC_EN:                      RTC
            DBGPWRUP_EN:                 Debugss Csyspwrupreq
            DBGFRCACT_EN:                Debugss forecactive
            SECERR_EN:                   Secure error irq
            COREWDT_EN:                  Core WDT request
*/
#define HOSTMCU_AON_CFGWICSNS_VAL_W                                  18U
#define HOSTMCU_AON_CFGWICSNS_VAL_M                                  0x0003FFFFU
#define HOSTMCU_AON_CFGWICSNS_VAL_S                                  0U
#define HOSTMCU_AON_CFGWICSNS_VAL_DIS                                0x00000000U
#define HOSTMCU_AON_CFGWICSNS_VAL_TMRREQ_EN                          0x00000001U
#define HOSTMCU_AON_CFGWICSNS_VAL_WUSRC0_EN                          0x00000002U
#define HOSTMCU_AON_CFGWICSNS_VAL_WUSRC1_EN                          0x00000004U
#define HOSTMCU_AON_CFGWICSNS_VAL_DRBL0_EN                           0x00000008U
#define HOSTMCU_AON_CFGWICSNS_VAL_DRBL1_EN                           0x00000010U
#define HOSTMCU_AON_CFGWICSNS_VAL_DRBL2_EN                           0x00000020U
#define HOSTMCU_AON_CFGWICSNS_VAL_DRBL3_EN                           0x00000040U
#define HOSTMCU_AON_CFGWICSNS_VAL_DRBL4_EN                           0x00000080U
#define HOSTMCU_AON_CFGWICSNS_VAL_DRBL5_EN                           0x00000100U
#define HOSTMCU_AON_CFGWICSNS_VAL_DRBL6_EN                           0x00000200U
#define HOSTMCU_AON_CFGWICSNS_VAL_DRBL7_EN                           0x00000400U
#define HOSTMCU_AON_CFGWICSNS_VAL_NAB_EN                             0x00000800U
#define HOSTMCU_AON_CFGWICSNS_VAL_BLERFCGPO_EN                       0x00001000U
#define HOSTMCU_AON_CFGWICSNS_VAL_RTC_EN                             0x00002000U
#define HOSTMCU_AON_CFGWICSNS_VAL_DBGPWRUP_EN                        0x00004000U
#define HOSTMCU_AON_CFGWICSNS_VAL_DBGFRCACT_EN                       0x00008000U
#define HOSTMCU_AON_CFGWICSNS_VAL_SECERR_EN                          0x00010000U
#define HOSTMCU_AON_CFGWICSNS_VAL_COREWDT_EN                         0x00020000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGWUTP
    Offset name:         HOSTMCU_AON_O_CFGWUTP
    Relative address:    0xC
    Description:         ELP Wake-up Type Configuration.

                        Register to configure wake up type
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Field to configure wake up type

                         Set 0 - Slow Wake up (precise WU).
                         Set 1 - Fast Wake up (assume system is already active when event is triggered).

                         Bit 0   : ELP TMR Wake up request
                         Bit 1   : GPIO wake up src 0
                         Bit 2   : GPIO wake up src 1
                         Bit 3   : doorbell 0
                         Bit 4   : doorbell 1
                         Bit 5   : doorbell 2
                         Bit 6   : doorbell 3
                         Bit 7   : doorbell 4
                         Bit 8   : doorbell 5
                         Bit 9   : doorbell 6
                         Bit 10 : doorbell 7
                         Bit 11 : nab_host_irq
                         Bit 12 : ble_rfc_gpo_8_irq
                         Bit 13 : RTC
                         Bit 14 : DebugSS Csyspwrupreq
                         Bit 15 : DebugSS Forceactive
                         Bit 16 : secured_error_irq
                         Bit 17 : core wdt irq

                         Note: GPIO wakeup src 0 is AND of wakeup sources and GPIO wakup src 1 is OR of wakeup sources

        ENUMs:
            SLOW:                        Slow wakeup(precise wakup)
            TMRREQ:                      Fast Wake up
            WUSRC0:                      Fast Wake up
            WUSRC1:                      Fast Wake up
            DRBL0:                       Fast Wake up
            DRBL1:                       Fast Wake up
            DRBL2:                       Fast Wake up
            DRBL3:                       Fast Wake up
            DRBL4:                       Fast Wake up
            DRBL5:                       Fast Wake up
            DRBL6:                       Fast Wake up
            DRBL7:                       Fast Wake up
            NAB:                         Fast Wake up
            BLERFCGPO:                   Fast Wake up
            RTC:                         Fast Wake up
            DBGPWRUP:                    Fast Wake up
            DBGFRCACT:                   Fast Wake up
            SECERR:                      Fast Wake up
            COREWDT:                     Fast Wake up
*/
#define HOSTMCU_AON_CFGWUTP_VAL_W                                    18U
#define HOSTMCU_AON_CFGWUTP_VAL_M                                    0x0003FFFFU
#define HOSTMCU_AON_CFGWUTP_VAL_S                                    0U
#define HOSTMCU_AON_CFGWUTP_VAL_SLOW                                 0x00000000U
#define HOSTMCU_AON_CFGWUTP_VAL_TMRREQ                               0x00000001U
#define HOSTMCU_AON_CFGWUTP_VAL_WUSRC0                               0x00000002U
#define HOSTMCU_AON_CFGWUTP_VAL_WUSRC1                               0x00000004U
#define HOSTMCU_AON_CFGWUTP_VAL_DRBL0                                0x00000008U
#define HOSTMCU_AON_CFGWUTP_VAL_DRBL1                                0x00000010U
#define HOSTMCU_AON_CFGWUTP_VAL_DRBL2                                0x00000020U
#define HOSTMCU_AON_CFGWUTP_VAL_DRBL3                                0x00000040U
#define HOSTMCU_AON_CFGWUTP_VAL_DRBL4                                0x00000080U
#define HOSTMCU_AON_CFGWUTP_VAL_DRBL5                                0x00000100U
#define HOSTMCU_AON_CFGWUTP_VAL_DRBL6                                0x00000200U
#define HOSTMCU_AON_CFGWUTP_VAL_DRBL7                                0x00000400U
#define HOSTMCU_AON_CFGWUTP_VAL_NAB                                  0x00000800U
#define HOSTMCU_AON_CFGWUTP_VAL_BLERFCGPO                            0x00001000U
#define HOSTMCU_AON_CFGWUTP_VAL_RTC                                  0x00002000U
#define HOSTMCU_AON_CFGWUTP_VAL_DBGPWRUP                             0x00004000U
#define HOSTMCU_AON_CFGWUTP_VAL_DBGFRCACT                            0x00008000U
#define HOSTMCU_AON_CFGWUTP_VAL_SECERR                               0x00010000U
#define HOSTMCU_AON_CFGWUTP_VAL_COREWDT                              0x00020000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ELPTMREN
    Offset name:         HOSTMCU_AON_O_ELPTMREN
    Relative address:    0x10
    Description:         ELP Timer Enable.

                        Register to configure ELP Timer enable
    Default Value:       0x00000002

        Field:           VAL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Field to enable ELP Timer

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define HOSTMCU_AON_ELPTMREN_VAL                                     0x00000001U
#define HOSTMCU_AON_ELPTMREN_VAL_M                                   0x00000001U
#define HOSTMCU_AON_ELPTMREN_VAL_S                                   0U
#define HOSTMCU_AON_ELPTMREN_VAL_DIS                                 0x00000000U
#define HOSTMCU_AON_ELPTMREN_VAL_EN                                  0x00000001U
/*

        Field:           TMRSWCTL
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Field to configure the type of timer control

        ENUMs:
            HW:                          Hardware control
            SW:                          Software control
*/
#define HOSTMCU_AON_ELPTMREN_TMRSWCTL                                0x00000002U
#define HOSTMCU_AON_ELPTMREN_TMRSWCTL_M                              0x00000002U
#define HOSTMCU_AON_ELPTMREN_TMRSWCTL_S                              1U
#define HOSTMCU_AON_ELPTMREN_TMRSWCTL_HW                             0x00000000U
#define HOSTMCU_AON_ELPTMREN_TMRSWCTL_SW                             0x00000002U
/*

        Field:           ELPTMRSET
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ELP TIMER SET

                         starts the timer

*/
#define HOSTMCU_AON_ELPTMREN_ELPTMRSET                               0x00000004U
#define HOSTMCU_AON_ELPTMREN_ELPTMRSET_M                             0x00000004U
#define HOSTMCU_AON_ELPTMREN_ELPTMRSET_S                             2U
/*

        Field:           ELPTMRRST
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ELP TIMER RESET

                         setting this bit will stop the timer

*/
#define HOSTMCU_AON_ELPTMREN_ELPTMRRST                               0x00000008U
#define HOSTMCU_AON_ELPTMREN_ELPTMRRST_M                             0x00000008U
#define HOSTMCU_AON_ELPTMREN_ELPTMRRST_S                             3U
/*

        Field:           ELPTMRLD
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     ELP TIMER LOAD

                         setting this bit will load the value 2 to the timer

*/
#define HOSTMCU_AON_ELPTMREN_ELPTMRLD                                0x00010000U
#define HOSTMCU_AON_ELPTMREN_ELPTMRLD_M                              0x00010000U
#define HOSTMCU_AON_ELPTMREN_ELPTMRLD_S                              16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGTMRWU
    Offset name:         HOSTMCU_AON_O_CFGTMRWU
    Relative address:    0x14
    Description:         Timer Wake-up Configuration.

                        Register to configure Timer wake up
    Default Value:       0x00000000

        Field:           THR
        From..to bits:   0...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Field to configure the Threshold of timer wake up

                         Upon reaching this value wake up event is generated towards the WUC (if not masked in WICSENSE).
                         Resolution slow clock cycles.

                         value must be greater than 1

*/
#define HOSTMCU_AON_CFGTMRWU_THR_W                                   31U
#define HOSTMCU_AON_CFGTMRWU_THR_M                                   0x7FFFFFFFU
#define HOSTMCU_AON_CFGTMRWU_THR_S                                   0U
/*

        Field:           EN
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Field to enable timer wake up

                         Set 1 - Enable BCN threshold IRQ.
                         Set 0 - Otherwise.

                         Timer is kicked upon moving from ACTIVE to POWER DOWN.

        ENUMs:
            DIS:                         otherwise
            EN:                          Enable BCN threshold IRQ
*/
#define HOSTMCU_AON_CFGTMRWU_EN                                      0x80000000U
#define HOSTMCU_AON_CFGTMRWU_EN_M                                    0x80000000U
#define HOSTMCU_AON_CFGTMRWU_EN_S                                    31U
#define HOSTMCU_AON_CFGTMRWU_EN_DIS                                  0x00000000U
#define HOSTMCU_AON_CFGTMRWU_EN_EN                                   0x80000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TMRWUREQ
    Offset name:         HOSTMCU_AON_O_TMRWUREQ
    Relative address:    0x18
    Description:         Timer Wake-up Request Clear.

                        Register to configure timer wake up request
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Field to clear timer wake up request. Set this bit to clear

*/
#define HOSTMCU_AON_TMRWUREQ_CLR                                     0x00000001U
#define HOSTMCU_AON_TMRWUREQ_CLR_M                                   0x00000001U
#define HOSTMCU_AON_TMRWUREQ_CLR_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGWDT
    Offset name:         HOSTMCU_AON_O_CFGWDT
    Relative address:    0x1C
    Description:         Watch Dog Timer Configuration.

                        Register to configure watchdog timer
    Default Value:       0x800EA600

        Field:           THR
        From..to bits:   8...30
        DefaultValue:    0xEA6
        Access type:     read-write
        Description:     Field to configure watchdog timer threshold

                         Upon reaching this value wake up event is generated towards the WUC (if not masked in WICSENSE).
                         Resolution slow clock cycles (min val ~8ms).

                         value must be greater than 1

*/
#define HOSTMCU_AON_CFGWDT_THR_W                                     23U
#define HOSTMCU_AON_CFGWDT_THR_M                                     0x7FFFFF00U
#define HOSTMCU_AON_CFGWDT_THR_S                                     8U
/*

        Field:           EN
        From..to bits:   31...31
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Field to enable watchdog timer

        ENUMs:
            DIS:
            EN:
*/
#define HOSTMCU_AON_CFGWDT_EN                                        0x80000000U
#define HOSTMCU_AON_CFGWDT_EN_M                                      0x80000000U
#define HOSTMCU_AON_CFGWDT_EN_S                                      31U
#define HOSTMCU_AON_CFGWDT_EN_DIS                                    0x00000000U
#define HOSTMCU_AON_CFGWDT_EN_EN                                     0x80000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WDTREQ
    Offset name:         HOSTMCU_AON_O_WDTREQ
    Relative address:    0x20
    Description:         Watch Dog Timer Request Clear.

                        Register to clear watchdog timer request
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Field to clear watchdog timer request. Set this bet to clear

*/
#define HOSTMCU_AON_WDTREQ_CLR                                       0x00000001U
#define HOSTMCU_AON_WDTREQ_CLR_M                                     0x00000001U
#define HOSTMCU_AON_WDTREQ_CLR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPWUAND
    Offset name:         HOSTMCU_AON_O_GPWUAND
    Relative address:    0x28
    Description:         GPIO Wake-up AND IRQ Configuration.

                        Field to configure *GPIO* wake up AND *IRQ* 0 to 31
    Default Value:       0xFFFFFFFF

        Field:           BM0T31
        From..to bits:   0...31
        DefaultValue:    0xFFFFFFFF
        Access type:     read-write
        Description:     Field to bit mask GPIO 0 to 31

                         select 0-31 GPIOs as wake up source.

*/
#define HOSTMCU_AON_GPWUAND_BM0T31_W                                 32U
#define HOSTMCU_AON_GPWUAND_BM0T31_M                                 0xFFFFFFFFU
#define HOSTMCU_AON_GPWUAND_BM0T31_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPWUOR
    Offset name:         HOSTMCU_AON_O_GPWUOR
    Relative address:    0x2C
    Description:         GPIO Wake-up OR IRQ Configuration.

                        Field to configure *GPIO* wake up OR gate *IRQ*
    Default Value:       0xFFFFFFFF

        Field:           BM0T31
        From..to bits:   0...31
        DefaultValue:    0xFFFFFFFF
        Access type:     read-write
        Description:     Field to bit mask GPIO 0 to 31

                         select 0-31 GPIOs as wake up source.

*/
#define HOSTMCU_AON_GPWUOR_BM0T31_W                                  32U
#define HOSTMCU_AON_GPWUOR_BM0T31_M                                  0xFFFFFFFFU
#define HOSTMCU_AON_GPWUOR_BM0T31_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPWUAND1
    Offset name:         HOSTMCU_AON_O_GPWUAND1
    Relative address:    0x30
    Description:         GPIO Wake-up AND IRQ Configuration.

                        Field to configure *GPIO* wake up AND *IRQ* 32 to 44
    Default Value:       0x000FFFFF

        Field:           BM32T44
        From..to bits:   0...12
        DefaultValue:    0x1FFF
        Access type:     read-write
        Description:     Field to bit mask 32 to 44

                         select 32-44 GPIOs as wake up source.

*/
#define HOSTMCU_AON_GPWUAND1_BM32T44_W                               13U
#define HOSTMCU_AON_GPWUAND1_BM32T44_M                               0x00001FFFU
#define HOSTMCU_AON_GPWUAND1_BM32T44_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPWUOR1
    Offset name:         HOSTMCU_AON_O_GPWUOR1
    Relative address:    0x34
    Description:         GPIO Wake-up OR IRQ Configuration.

                        Field to configure *GPIO* wake up OR *IRQ* 32 to 44
    Default Value:       0x000FFFFF

        Field:           BM32T44
        From..to bits:   0...12
        DefaultValue:    0x1FFF
        Access type:     read-write
        Description:     Field to bit mask 32 to 44

                         select 32-44 GPIOs as wake up source.

*/
#define HOSTMCU_AON_GPWUOR1_BM32T44_W                                13U
#define HOSTMCU_AON_GPWUOR1_BM32T44_M                                0x00001FFFU
#define HOSTMCU_AON_GPWUOR1_BM32T44_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLKARM
    Offset name:         HOSTMCU_AON_O_FCLKARM
    Relative address:    0x38
    Description:         Fast Clock From ARM Command
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command
                         Latched counter value reflecting the number of fast clocks (host_clk) from rise of SLEEPDEEP indication until ELP WUC start power down sequence.
                         This value should capture the uncertainty of 2-3 slow clocks of synchronization of ARM CMD

*/
#define HOSTMCU_AON_FCLKARM_CMD_W                                    16U
#define HOSTMCU_AON_FCLKARM_CMD_M                                    0x0000FFFFU
#define HOSTMCU_AON_FCLKARM_CMD_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SLPTIMES
    Offset name:         HOSTMCU_AON_O_SLPTIMES
    Relative address:    0x3C
    Description:         Sleep Time Slow Clock.

                        Register for sleep time on slow clock
    Default Value:       0x00000000

        Field:           CLK
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Sleep time value from last ELP sleep entry (slow clock synced ARM CMD).
                         Slow Clock - Reflects the number of slow clocks in ELP timer.

*/
#define HOSTMCU_AON_SLPTIMES_CLK_W                                   32U
#define HOSTMCU_AON_SLPTIMES_CLK_M                                   0xFFFFFFFFU
#define HOSTMCU_AON_SLPTIMES_CLK_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SLPTIMEF
    Offset name:         HOSTMCU_AON_O_SLPTIMEF
    Relative address:    0x40
    Description:         Sleep Time Fast Clock.

                        Register for sleep time on fast clock
    Default Value:       0x00000000

        Field:           CLK
        From..to bits:   0...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Sleep time value from last ELP sleep entry (slow clock synced ARM CMD).
                         Fast Clock - Reflects the number of fast clocks from last Slow clock rise until OCP Read.
                         Note, fast counter value is latched upon OCP Read of ELP_SLEEP_TIME_SLOW.
                         Counts up t0 51 microsecond.

*/
#define HOSTMCU_AON_SLPTIMEF_CLK_W                                   11U
#define HOSTMCU_AON_SLPTIMEF_CLK_M                                   0x000007FFU
#define HOSTMCU_AON_SLPTIMEF_CLK_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WUREQ
    Offset name:         HOSTMCU_AON_O_WUREQ
    Relative address:    0x4C
    Description:         Wake up Request Status
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Field to show the event request

                         Bit 0   : ELP TMR Wake up request
                         Bit 1   : GPIO wake up src 0
                         Bit 2   : GPIO wake up src 1
                         Bit 3   : doorbell 0
                         Bit 4   : doorbell 1
                         Bit 5   : doorbell 2
                         Bit 6   : doorbell 3
                         Bit 7   : doorbell 4
                         Bit 8   : doorbell 5
                         Bit 9   : doorbell 6
                         Bit 10 : doorbell 7
                         Bit 11 : nab_host_irq
                         Bit 12 : ble_rfc_gpo_8_irq
                         Bit 13 : RTC
                         Bit 14 : DebugSS Csyspwrupreq
                         Bit 15 : DebugSS Force-active
                         Bit 16 : secured_error_irq
                         Bit 17 : core wdt irq
                         Note: GPIO wakeup src 0 is AND of wakeup sources and GPIO wakup src 1 is OR of wakeup sources

        ENUMs:
            CLEAR:                       No event request
            TMRREQ:                      ELP timer wakeup request
            WUSRC0:                      AND of wakeup sources
            WUSRC1:                      OR of wakeup sources
            DRBL0:                       Doorbell 0
            DRBL1:                       Doorbell 1
            DRBL2:                       Doorbell 2
            DRBL3:                       Doorbell 3
            DRBL4:                       Doorbell 4
            DRBL5:                       Doorbell 5
            DRBL6:                       Doorbell 6
            DRBL7:                       Doorbell 7
            NAB:                         NAB host irq
            BLERFCGPO:                   BLE RFC GPO 9 irq
            RTC:                         RTC
            DBGPWRUP:                    Debugss Csyspwrupreq
            DBGFRCACT:                   Debugss forecactive
            SECERR:                      Secure error irq
            COREWDT:                     Core WDT request
*/
#define HOSTMCU_AON_WUREQ_VAL_W                                      18U
#define HOSTMCU_AON_WUREQ_VAL_M                                      0x0003FFFFU
#define HOSTMCU_AON_WUREQ_VAL_S                                      0U
#define HOSTMCU_AON_WUREQ_VAL_CLEAR                                  0x00000000U
#define HOSTMCU_AON_WUREQ_VAL_TMRREQ                                 0x00000001U
#define HOSTMCU_AON_WUREQ_VAL_WUSRC0                                 0x00000002U
#define HOSTMCU_AON_WUREQ_VAL_WUSRC1                                 0x00000004U
#define HOSTMCU_AON_WUREQ_VAL_DRBL0                                  0x00000008U
#define HOSTMCU_AON_WUREQ_VAL_DRBL1                                  0x00000010U
#define HOSTMCU_AON_WUREQ_VAL_DRBL2                                  0x00000020U
#define HOSTMCU_AON_WUREQ_VAL_DRBL3                                  0x00000040U
#define HOSTMCU_AON_WUREQ_VAL_DRBL4                                  0x00000080U
#define HOSTMCU_AON_WUREQ_VAL_DRBL5                                  0x00000100U
#define HOSTMCU_AON_WUREQ_VAL_DRBL6                                  0x00000200U
#define HOSTMCU_AON_WUREQ_VAL_DRBL7                                  0x00000400U
#define HOSTMCU_AON_WUREQ_VAL_NAB                                    0x00000800U
#define HOSTMCU_AON_WUREQ_VAL_BLERFCGPO                              0x00001000U
#define HOSTMCU_AON_WUREQ_VAL_RTC                                    0x00002000U
#define HOSTMCU_AON_WUREQ_VAL_DBGPWRUP                               0x00004000U
#define HOSTMCU_AON_WUREQ_VAL_DBGFRCACT                              0x00008000U
#define HOSTMCU_AON_WUREQ_VAL_SECERR                                 0x00010000U
#define HOSTMCU_AON_WUREQ_VAL_COREWDT                                0x00020000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OREFCLK
    Offset name:         HOSTMCU_AON_O_OREFCLK
    Relative address:    0x50
    Description:         OSPI Reference Clock.

                        Field to select the OSPI  reference clock
    Default Value:       0x00000012

        Field:           SEL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SELECTOR

                         '0' - default host clk div2
                         '1' host clk div 4

        ENUMs:
            SEL_0:                       Host clock div2
            SEL_1:                       Host clock div4
*/
#define HOSTMCU_AON_OREFCLK_SEL                                      0x00000001U
#define HOSTMCU_AON_OREFCLK_SEL_M                                    0x00000001U
#define HOSTMCU_AON_OREFCLK_SEL_S                                    0U
#define HOSTMCU_AON_OREFCLK_SEL_SEL_0                                0x00000000U
#define HOSTMCU_AON_OREFCLK_SEL_SEL_1                                0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WUC
    Offset name:         HOSTMCU_AON_O_WUC
    Relative address:    0x5C
    Description:         Wake-up Control State.

                        Register for Host wake up state
    Default Value:       0x00000004

        Field:           STA
        From..to bits:   0...2
        DefaultValue:    0x4
        Access type:     read-only
        Description:     Field showing the host wake up state

                         3'b000 - PD_PWR_DN
                         3'b001 - SHARED_UP
                         3'b010 - PD_PWR_UP
                         3'b011 - ACTIVE
                         3'b100 - DEEPSLEEP

        ENUMs:
            RD_0:                        PD power down
            RD_1:                        Shared domain up
            RD_2:                        PD power up
            RD_3:                        Active
*/
#define HOSTMCU_AON_WUC_STA_W                                        3U
#define HOSTMCU_AON_WUC_STA_M                                        0x00000007U
#define HOSTMCU_AON_WUC_STA_S                                        0U
#define HOSTMCU_AON_WUC_STA_RD_0                                     0x00000000U
#define HOSTMCU_AON_WUC_STA_RD_1                                     0x00000001U
#define HOSTMCU_AON_WUC_STA_RD_2                                     0x00000002U
#define HOSTMCU_AON_WUC_STA_RD_3                                     0x00000003U

#endif /* __HW_HOSTMCU_AON_H__*/
