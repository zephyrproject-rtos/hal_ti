/******************************************************************************
*  Filename:       hw_core_aon.h
*
*  Description:    Defines and prototypes for the CORE_AON peripheral.
*
*  Copyright (c) 2023, Texas Instruments Incorporated
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
#ifndef __HW_CORE_AON_H__
#define __HW_CORE_AON_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the CORE_AON component

--------------------------------------------------------------------------------- */

//INIT
#define CORE_AON_O_INIT                                              0x00000004U

//WUC SKIP
#define CORE_AON_O_WUCSKP                                            0x00000008U

//CPU WAIT
#define CORE_AON_O_CPUWAIT                                           0x00000014U

//CORE MEDIUM BUSY CONTROL
#define CORE_AON_O_CRMBCTL                                           0x00000018U

//CONFIG WAKE UP TYPE
#define CORE_AON_O_CFGWUTP                                           0x0000001CU

//CONFIG WICSENSE
#define CORE_AON_O_CFGWICSNS                                         0x00000024U

//CONFIG TIMER WAKEUP
#define CORE_AON_O_CFGTMRWU                                          0x0000002CU

//CONFIG WATCHDOG TIMER
#define CORE_AON_O_CFGWDT                                            0x00000034U

//WAKEUP REQUEST
#define CORE_AON_O_WUREQ                                             0x00000038U

//CONFIG SHORT SLEEP
#define CORE_AON_O_CFGSHSLP                                          0x00000040U

//FAST CLOCK FROM ARM CMD
#define CORE_AON_O_FCLKARMCMD                                        0x00000054U

//SLEEP TIME SLOW
#define CORE_AON_O_SLPTIMSL                                          0x00000058U

//TIMER ENABLE
#define CORE_AON_O_TMREN                                             0x0000005CU

//COEX ANTENNA CONTROL SELECT OVERRIDE
#define CORE_AON_O_CATLSELOV                                         0x0000006CU

//SLEEP TIME FAST
#define CORE_AON_O_SLPTIMFAST                                        0x00000074U

//GPIO WAKEUP AND LOGIC IRQ
#define CORE_AON_O_IOWUANDIRQ                                        0x0000009CU

//GPIO WAKEUP OR LOGIC IRQ
#define CORE_AON_O_IOWUORIRQ                                         0x000000A0U

//GPIO WAKEUP AND LOGIC IRQ 1
#define CORE_AON_O_IOWUANDIRQ1                                       0x000000A4U

//GPIO WAKEUP OR LOGIC IRQ 1
#define CORE_AON_O_IOWUORIRQ1                                        0x000000A8U

//TIMER WAKEUP REQUEST
#define CORE_AON_O_TMRWUREQ                                          0x000000ACU

//WATCHDOG TIMER REQUEST
#define CORE_AON_O_WDTREQ                                            0x000000B0U

//FORCE CORE
#define CORE_AON_O_FRCCR                                             0x000000D8U

//CORE ICG
#define CORE_AON_O_CRICG                                             0x000000DCU

//CORE WUC
#define CORE_AON_O_CRWUC                                             0x000000E0U

//NAB HOST IRQ CONFIG
#define CORE_AON_O_NABHIRQCFG                                        0x000000E4U

//GPIO TO PAD 0
#define CORE_AON_O_IOTP0                                             0x000000E8U

//GPIO TO PAD 1
#define CORE_AON_O_IOTP1                                             0x000000ECU

//GPIO OUT ENABLE CONFIG 0
#define CORE_AON_O_IOOENCFG0                                         0x000000F8U

//GPIO OUT ENABLE CONFIG 1
#define CORE_AON_O_IOOENCFG1                                         0x000000FCU



/*-----------------------------------REGISTER------------------------------------
    Register name:       INIT
    Offset name:         CORE_AON_O_INIT
    Relative address:    0x4
    Description:         INIT
    Default Value:       0x00000000

        Field:           DISMMU
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DISABLE MMU

                         0 - MMU memories, VLUT and MBLR are initiated when getting out of reset (at power up or when back from sleep)
                         1 - MMU memories, VLUT and MBLR are not initiated when getting out of reset (as they're held in retention)

*/
#define CORE_AON_INIT_DISMMU                                         0x00000001U
#define CORE_AON_INIT_DISMMU_M                                       0x00000001U
#define CORE_AON_INIT_DISMMU_S                                       0U
/*

        Field:           TPDESCRF
        From..to bits:   4...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TYPE DESCRF

                         0 - Descriptor FIFO memory (mem per bit) is initiated when getting out of reset (at power up or when back from sleep)
                         1 - Descriptor FIFO memory (mem per bit) is not initiated when getting out of reset (as it's held in retention)

                         MEM_INIT_TYPE_DESCRF[0] = disable INIT of link_table
                         MEM_INIT_TYPE_DESCRF[1] = disable INIT of queue_db
                         MEM_INIT_TYPE_DESCRF[2] = disable INIT of seq_num

*/
#define CORE_AON_INIT_TPDESCRF_W                                     3U
#define CORE_AON_INIT_TPDESCRF_M                                     0x00000070U
#define CORE_AON_INIT_TPDESCRF_S                                     4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WUCSKP
    Offset name:         CORE_AON_O_WUCSKP
    Relative address:    0x8
    Description:         WUC SKIP
    Default Value:       0x00000000

        Field:           PRCMVLD
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PRCM VLD

                         Enable skip precise duration for PRCM Shared UP if wakup event type is '0':
                         '0' - don't skip
                         '1' - skip

*/
#define CORE_AON_WUCSKP_PRCMVLD                                      0x00000001U
#define CORE_AON_WUCSKP_PRCMVLD_M                                    0x00000001U
#define CORE_AON_WUCSKP_PRCMVLD_S                                    0U
/*

        Field:           PDVLD
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     POWER DOMAIN VALID

                         Enable skip precise duration for Power Domain if wakup event type is '0':
                         '0' - don't skip
                         '1' - skip

*/
#define CORE_AON_WUCSKP_PDVLD                                        0x00000002U
#define CORE_AON_WUCSKP_PDVLD_M                                      0x00000002U
#define CORE_AON_WUCSKP_PDVLD_S                                      1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CPUWAIT
    Offset name:         CORE_AON_O_CPUWAIT
    Relative address:    0x14
    Description:         CPU WAIT
    Default Value:       0x00000012

        Field:           M3
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     M3

                         The CPUWAIT  allows the boot sequence of the processor M3 to be delayed.
                         This is useful in the case where the Teal processor is used in a SoC,
                         and the program code has to be loaded into SRAM first (e.g. via DMA under the control of another processor).

                         In this case, instead of hold the processor in reset, we can use CPUWAIT de-assertion
                         to defer the start up sequence and allow the system to start after the program code
                         has been successfully loaded into the program SRAM.

*/
#define CORE_AON_CPUWAIT_M3                                          0x00000001U
#define CORE_AON_CPUWAIT_M3_M                                        0x00000001U
#define CORE_AON_CPUWAIT_M3_S                                        0U
/*

        Field:           OVSEL
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OVERRIDE SELECTOR

                         override selector for using the MMR of CPU wait or the ELP FSM
                         '1' - use the MMR mem_m3_cpu_wait
                         '0' - use ELP FSM

*/
#define CORE_AON_CPUWAIT_OVSEL                                       0x00000002U
#define CORE_AON_CPUWAIT_OVSEL_M                                     0x00000002U
#define CORE_AON_CPUWAIT_OVSEL_S                                     1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CRMBCTL
    Offset name:         CORE_AON_O_CRMBCTL
    Relative address:    0x18
    Description:         CORE MEDIUM BUSY CONTROL

                        Medium busy AON override option towards IOMUX
    Default Value:       0x00000000

        Field:           OVEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE ENABLE

*/
#define CORE_AON_CRMBCTL_OVEN                                        0x00000001U
#define CORE_AON_CRMBCTL_OVEN_M                                      0x00000001U
#define CORE_AON_CRMBCTL_OVEN_S                                      0U
/*

        Field:           OVVAL
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE VALUE

*/
#define CORE_AON_CRMBCTL_OVVAL                                       0x00000100U
#define CORE_AON_CRMBCTL_OVVAL_M                                     0x00000100U
#define CORE_AON_CRMBCTL_OVVAL_S                                     8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGWUTP
    Offset name:         CORE_AON_O_CFGWUTP
    Relative address:    0x1C
    Description:         CONFIG WAKE UP TYPE
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     VALUE

                         Set 0 - Slow Wake up (precise WU).
                         Set 1 - Fast Wake up (MX device, assume system is already active when event is triggered).

                         Bit 0  : tmr_wakeup_req
                         Bit 1  : hif_wakeup_int
                         Bit 2  : gpio_wakeup_src[0]
                         Bit 3  : gpio_wakeup_src[1]
                         Bit 4  : evt_mng_m3_irq0
                         Bit 5  : evt_mng_m3_irq1
                         Bit 6  : evt_mng_m3_irq2
                         Bit 7  : evt_mng_m3_irq3
                         Bit 8  : evt_mng_m3_irq4
                         Bit 9  : evt_mng_m3_irq5
                         Bit 10 : evt_mng_m3_irq6
                         Bit 11 : evt_mng_m3_irq7
                         Bit 12 : evt_mng_m3_irq8
                         Bit 13 : evt_mng_m3_irq9
                         Bit 14 : doorbell0_m2_irq
                         Bit 15 : doorbell1_m2_irq
                         Bit 16 : doorbell2_m2_irq
                         Bit 17 : doorbell3_m2_irq
                         Bit 18 : doorbell4_m2_irq
                         Bit 19 : doorbell5_m2_irq
                         Bit 20 : doorbell6_m2_irq
                         Bit 21 : doorbell7_m2_irq
                         Bit 22 : mem_ns_sw_interrupt_to_cm3
                         Bit 23 : mem_sec_sw_interrupt_to_cm3
                         Bit 24 : debugss_core_forceactive

*/
#define CORE_AON_CFGWUTP_VAL_W                                       25U
#define CORE_AON_CFGWUTP_VAL_M                                       0x01FFFFFFU
#define CORE_AON_CFGWUTP_VAL_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGWICSNS
    Offset name:         CORE_AON_O_CFGWICSNS
    Relative address:    0x24
    Description:         CONFIG WICSENSE
    Default Value:       0x00000001

        Field:           VAL
        From..to bits:   0...24
        DefaultValue:    0x1
        Access type:     read-write
        Description:     VALUE

                         Set 1 - Enable wakeup source.
                         Set 0 - Disable wakeup source.

                         Bit 0  : tmr_wakeup_req
                         Bit 1  : hif_wakeup_int
                         Bit 2  : gpio_wakeup_src[0]
                         Bit 3  : gpio_wakeup_src[1]
                         Bit 4  : evt_mng_m3_irq0
                         Bit 5  : evt_mng_m3_irq1
                         Bit 6  : evt_mng_m3_irq2
                         Bit 7  : evt_mng_m3_irq3
                         Bit 8  : evt_mng_m3_irq4
                         Bit 9  : evt_mng_m3_irq5
                         Bit 10 : evt_mng_m3_irq6
                         Bit 11 : evt_mng_m3_irq7
                         Bit 12 : evt_mng_m3_irq8
                         Bit 13 : evt_mng_m3_irq9
                         Bit 14 : doorbell0_m2_irq
                         Bit 15 : doorbell1_m2_irq
                         Bit 16 : doorbell2_m2_irq
                         Bit 17 : doorbell3_m2_irq
                         Bit 18 : doorbell4_m2_irq
                         Bit 19 : doorbell5_m2_irq
                         Bit 20 : doorbell6_m2_irq
                         Bit 21 : doorbell7_m2_irq
                         Bit 22 : mem_ns_sw_interrupt_to_cm3
                         Bit 23 : mem_sec_sw_interrupt_to_cm3
                         Bit 24 : debugss_core_forceactive

*/
#define CORE_AON_CFGWICSNS_VAL_W                                     25U
#define CORE_AON_CFGWICSNS_VAL_M                                     0x01FFFFFFU
#define CORE_AON_CFGWICSNS_VAL_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGTMRWU
    Offset name:         CORE_AON_O_CFGTMRWU
    Relative address:    0x2C
    Description:         CONFIG TIMER WAKEUP
    Default Value:       0x00000000

        Field:           THR
        From..to bits:   0...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     THRESHOLD

                         Upon reaching this value wakeup event is generated towards the WUC (if not masked in WICSENSE).
                         Resolution slow clock cycles.

                         value must be greater than 1

*/
#define CORE_AON_CFGTMRWU_THR_W                                      31U
#define CORE_AON_CFGTMRWU_THR_M                                      0x7FFFFFFFU
#define CORE_AON_CFGTMRWU_THR_S                                      0U
/*

        Field:           EN
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ENABLE

                         Set 1 - Enable BCN threshold IRQ.
                         Set 0 - Otherwise.

                         Timer is kicked upon moving from ACTIVE to POWER DOWN.

*/
#define CORE_AON_CFGTMRWU_EN                                         0x80000000U
#define CORE_AON_CFGTMRWU_EN_M                                       0x80000000U
#define CORE_AON_CFGTMRWU_EN_S                                       31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGWDT
    Offset name:         CORE_AON_O_CFGWDT
    Relative address:    0x34
    Description:         CONFIG WATCHDOG TIMER
    Default Value:       0x00000000

        Field:           THR
        From..to bits:   8...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     THRESHOLD

                         Upon reaching this value wakeup event is generated towards the WUC (if not masked in WICSENSE).
                         Resolution slow clock cycles (min val ~8ms).

                         value must be greater than 1

*/
#define CORE_AON_CFGWDT_THR_W                                        23U
#define CORE_AON_CFGWDT_THR_M                                        0x7FFFFF00U
#define CORE_AON_CFGWDT_THR_S                                        8U
/*

        Field:           EN
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ENABLE

                         Set 1 - Enable WDT.
                         Set 0 - Disable WDT.

*/
#define CORE_AON_CFGWDT_EN                                           0x80000000U
#define CORE_AON_CFGWDT_EN_M                                         0x80000000U
#define CORE_AON_CFGWDT_EN_S                                         31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WUREQ
    Offset name:         CORE_AON_O_WUREQ
    Relative address:    0x38
    Description:         WAKEUP REQUEST

                        Bit 0 : wdt_wakeup_req
    Default Value:       0x00000000

        Field:           EVTVAL
        From..to bits:   0...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     EVENT VALUE

                         Bit 0  : tmr_wakeup_req
                         Bit 1  : hif_wakeup_int
                         Bit 2  : gpio_wakeup_src[0]
                         Bit 3  : gpio_wakeup_src[1]
                         Bit 4  : evt_mng_m3_irq0
                         Bit 5  : evt_mng_m3_irq1
                         Bit 6  : evt_mng_m3_irq2
                         Bit 7  : evt_mng_m3_irq3
                         Bit 8  : evt_mng_m3_irq4
                         Bit 9  : evt_mng_m3_irq5
                         Bit 10 : evt_mng_m3_irq6
                         Bit 11 : evt_mng_m3_irq7
                         Bit 12 : evt_mng_m3_irq8
                         Bit 13 : evt_mng_m3_irq9
                         Bit 14 : doorbell0_m2_irq
                         Bit 15 : doorbell1_m2_irq
                         Bit 16 : doorbell2_m2_irq
                         Bit 17 : doorbell3_m2_irq
                         Bit 18 : doorbell4_m2_irq
                         Bit 19 : doorbell5_m2_irq
                         Bit 20 : doorbell6_m2_irq
                         Bit 21 : doorbell7_m2_irq
                         Bit 22 : mem_ns_sw_interrupt_to_cm3
                         Bit 23 : mem_sec_sw_interrupt_to_cm3
                         Bit 24 : debugss_core_forceactive

*/
#define CORE_AON_WUREQ_EVTVAL_W                                      25U
#define CORE_AON_WUREQ_EVTVAL_M                                      0x01FFFFFFU
#define CORE_AON_WUREQ_EVTVAL_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CFGSHSLP
    Offset name:         CORE_AON_O_CFGSHSLP
    Relative address:    0x40
    Description:         CONFIG SHORT SLEEP

                        Hold the device clock request high, to save fref setting time during power up.
    Default Value:       0x00000000

        Field:           CLKREQ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CLOCK REQUEST

*/
#define CORE_AON_CFGSHSLP_CLKREQ                                     0x00000001U
#define CORE_AON_CFGSHSLP_CLKREQ_M                                   0x00000001U
#define CORE_AON_CFGSHSLP_CLKREQ_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLKARMCMD
    Offset name:         CORE_AON_O_FCLKARMCMD
    Relative address:    0x54
    Description:         FAST CLOCK FROM ARM CMD

                        Latched counter value reflecting the number of fast clocks (clk_core_clk) from rise of SLEEPDEEP indication until ELP WUC start power down sequence.
                        This value should capture the uncertainty of 2-3 slow clocks of synchronization of ARM CMD.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     VALUE

*/
#define CORE_AON_FCLKARMCMD_VAL_W                                    16U
#define CORE_AON_FCLKARMCMD_VAL_M                                    0x0000FFFFU
#define CORE_AON_FCLKARMCMD_VAL_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SLPTIMSL
    Offset name:         CORE_AON_O_SLPTIMSL
    Relative address:    0x58
    Description:         SLEEP TIME SLOW

                        Sleep time value from last ELP sleep entry (slow clock synced ARM CMD).
                        Slow Clock - Reflects the number of slow clocks in ELP timer.
    Default Value:       0x00000000

        Field:           CLK
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CLOCK

                         read clear

*/
#define CORE_AON_SLPTIMSL_CLK_W                                      32U
#define CORE_AON_SLPTIMSL_CLK_M                                      0xFFFFFFFFU
#define CORE_AON_SLPTIMSL_CLK_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TMREN
    Offset name:         CORE_AON_O_TMREN
    Relative address:    0x5C
    Description:         TIMER ENABLE

                        1 - ELP Timer is running.
                        0 - Otherwise.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     VALUE

*/
#define CORE_AON_TMREN_VAL                                           0x00000001U
#define CORE_AON_TMREN_VAL_M                                         0x00000001U
#define CORE_AON_TMREN_VAL_S                                         0U
/*

        Field:           TMRSWCTL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TIMER SOFTWARE CONTROL

                         '0' - HW CTRL
                         '1' - SW CTRL.

*/
#define CORE_AON_TMREN_TMRSWCTL                                      0x00000002U
#define CORE_AON_TMREN_TMRSWCTL_M                                    0x00000002U
#define CORE_AON_TMREN_TMRSWCTL_S                                    1U
/*

        Field:           TMRSET
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TIMER SET

                         starts the timer

*/
#define CORE_AON_TMREN_TMRSET                                        0x00000004U
#define CORE_AON_TMREN_TMRSET_M                                      0x00000004U
#define CORE_AON_TMREN_TMRSET_S                                      2U
/*

        Field:           TMRRST
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TIMER RESET

                         setting this bit will stop the timer

*/
#define CORE_AON_TMREN_TMRRST                                        0x00000008U
#define CORE_AON_TMREN_TMRRST_M                                      0x00000008U
#define CORE_AON_TMREN_TMRRST_S                                      3U
/*

        Field:           TMRLD
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TIMER LOAD

                         setting this bit will load the value 2 to the timer

*/
#define CORE_AON_TMREN_TMRLD                                         0x00010000U
#define CORE_AON_TMREN_TMRLD_M                                       0x00010000U
#define CORE_AON_TMREN_TMRLD_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CATLSELOV
    Offset name:         CORE_AON_O_CATLSELOV
    Relative address:    0x6C
    Description:         COEX ANTENNA CONTROL SELECT OVERRIDE
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ENABLE

*/
#define CORE_AON_CATLSELOV_EN                                        0x00000001U
#define CORE_AON_CATLSELOV_EN_M                                      0x00000001U
#define CORE_AON_CATLSELOV_EN_S                                      0U
/*

        Field:           VAL
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     VALUE

*/
#define CORE_AON_CATLSELOV_VAL_W                                     4U
#define CORE_AON_CATLSELOV_VAL_M                                     0x00000F00U
#define CORE_AON_CATLSELOV_VAL_S                                     8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SLPTIMFAST
    Offset name:         CORE_AON_O_SLPTIMFAST
    Relative address:    0x74
    Description:         SLEEP TIME FAST

                        Sleep time value from last ELP sleep entry (slow clock synced ARM CMD).
                        Fast Clock - Reflects the number of fast clocks from last Slow clock rise until OCP Read.
                        Note, fast counter value is latched upon OCP Read of ELP_SLEEP_TIME_SLOW.
                        Counts up t0 51 microsecond.
    Default Value:       0x00000000

        Field:           CLK
        From..to bits:   0...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CLOCK

*/
#define CORE_AON_SLPTIMFAST_CLK_W                                    11U
#define CORE_AON_SLPTIMFAST_CLK_M                                    0x000007FFU
#define CORE_AON_SLPTIMFAST_CLK_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IOWUANDIRQ
    Offset name:         CORE_AON_O_IOWUANDIRQ
    Relative address:    0x9C
    Description:         GPIO WAKEUP AND LOGIC IRQ
    Default Value:       0x00000000

        Field:           0T31BM
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 TO 31 BITMASK

                         select 0-31 GPIOs as wakeup source.

*/
#define CORE_AON_IOWUANDIRQ_0T31BM_W                                 32U
#define CORE_AON_IOWUANDIRQ_0T31BM_M                                 0xFFFFFFFFU
#define CORE_AON_IOWUANDIRQ_0T31BM_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IOWUORIRQ
    Offset name:         CORE_AON_O_IOWUORIRQ
    Relative address:    0xA0
    Description:         GPIO WAKEUP OR LOGIC IRQ
    Default Value:       0x00000000

        Field:           0T31BM
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 TO 31 BITMASK

                         select 0-31 GPIOs as wakeup source.

*/
#define CORE_AON_IOWUORIRQ_0T31BM_W                                  32U
#define CORE_AON_IOWUORIRQ_0T31BM_M                                  0xFFFFFFFFU
#define CORE_AON_IOWUORIRQ_0T31BM_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IOWUANDIRQ1
    Offset name:         CORE_AON_O_IOWUANDIRQ1
    Relative address:    0xA4
    Description:         GPIO WAKEUP AND LOGIC IRQ 1
    Default Value:       0x00000000

        Field:           32T44BM
        From..to bits:   0...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 TO 44 BITMASK

                         select 32-44 GPIOs as wakeup source.

*/
#define CORE_AON_IOWUANDIRQ1_32T44BM_W                               13U
#define CORE_AON_IOWUANDIRQ1_32T44BM_M                               0x00001FFFU
#define CORE_AON_IOWUANDIRQ1_32T44BM_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IOWUORIRQ1
    Offset name:         CORE_AON_O_IOWUORIRQ1
    Relative address:    0xA8
    Description:         GPIO WAKEUP OR LOGIC IRQ 1
    Default Value:       0x00000000

        Field:           32T44BM
        From..to bits:   0...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 TO 44 BITMASK

                         select 32-44 GPIOs as wakeup source.

*/
#define CORE_AON_IOWUORIRQ1_32T44BM_W                                13U
#define CORE_AON_IOWUORIRQ1_32T44BM_M                                0x00001FFFU
#define CORE_AON_IOWUORIRQ1_32T44BM_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TMRWUREQ
    Offset name:         CORE_AON_O_TMRWUREQ
    Relative address:    0xAC
    Description:         TIMER WAKEUP REQUEST
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     CLEAR

                         write clear

*/
#define CORE_AON_TMRWUREQ_CLR                                        0x00000001U
#define CORE_AON_TMRWUREQ_CLR_M                                      0x00000001U
#define CORE_AON_TMRWUREQ_CLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WDTREQ
    Offset name:         CORE_AON_O_WDTREQ
    Relative address:    0xB0
    Description:         WATCHDOG TIMER REQUEST
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     CLEAR

                         write clear

*/
#define CORE_AON_WDTREQ_CLR                                          0x00000001U
#define CORE_AON_WDTREQ_CLR_M                                        0x00000001U
#define CORE_AON_WDTREQ_CLR_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FRCCR
    Offset name:         CORE_AON_O_FRCCR
    Relative address:    0xD8
    Description:         FORCE CORE
    Default Value:       0x00000000

        Field:           ON
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ON

                         host to write here '1' to keep the core awake

*/
#define CORE_AON_FRCCR_ON                                            0x00000001U
#define CORE_AON_FRCCR_ON_M                                          0x00000001U
#define CORE_AON_FRCCR_ON_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CRICG
    Offset name:         CORE_AON_O_CRICG
    Relative address:    0xDC
    Description:         CORE ICG
    Default Value:       0x00000000

        Field:           CLRTHR
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CLEAR THRESHOLD

                         Delay Counter value to gate CORE clk-
                         The time we will wait from the moment M3 CLK stopped

*/
#define CORE_AON_CRICG_CLRTHR_W                                      3U
#define CORE_AON_CRICG_CLRTHR_M                                      0x00000007U
#define CORE_AON_CRICG_CLRTHR_S                                      0U
/*

        Field:           SETTHR
        From..to bits:   8...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SET THRESHOLD

                         Delay Counter value to EN CORE clk-
                         The time we will wait from the moment M3 CLK Enabled

*/
#define CORE_AON_CRICG_SETTHR_W                                      3U
#define CORE_AON_CRICG_SETTHR_M                                      0x00000700U
#define CORE_AON_CRICG_SETTHR_S                                      8U
/*

        Field:           OVEN
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE ENABLE

                         use Override  value for core ICG-
                         '0' - don't use override
                         '1' - use override

*/
#define CORE_AON_CRICG_OVEN                                          0x00000800U
#define CORE_AON_CRICG_OVEN_M                                        0x00000800U
#define CORE_AON_CRICG_OVEN_S                                        11U
/*

        Field:           OVVAL
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OVERRIDE VALUE

                         once override en is '1', the ICG will work according to the below-
                         '0' - CORE ICG disable
                         '1' - CORE ICG enable

*/
#define CORE_AON_CRICG_OVVAL                                         0x00001000U
#define CORE_AON_CRICG_OVVAL_M                                       0x00001000U
#define CORE_AON_CRICG_OVVAL_S                                       12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CRWUC
    Offset name:         CORE_AON_O_CRWUC
    Relative address:    0xE0
    Description:         CORE WUC
    Default Value:       0x00000004

        Field:           STA
        From..to bits:   0...2
        DefaultValue:    0x4
        Access type:     read-only
        Description:     STATE

                         3'b000 - PD_PWR_DN
                         3'b001 - SHARED_UP
                         3'b010 - PD_PWR_UP
                         3'b011 - ACTIVE
                         3'b100 - DEEPSLEEP

*/
#define CORE_AON_CRWUC_STA_W                                         3U
#define CORE_AON_CRWUC_STA_M                                         0x00000007U
#define CORE_AON_CRWUC_STA_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       NABHIRQCFG
    Offset name:         CORE_AON_O_NABHIRQCFG
    Relative address:    0xE4
    Description:         NAB HOST IRQ CONFIG
    Default Value:       0x00000000

        Field:           POL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     POLARITY

                         "1" for negative polarity
                         "0" for positive polarity
                         (GuyS: in order to preserve this at sleep (retention)  - ISO latch needs to be implemented. Alternatively, move this polarity cfg bit to upper H/W layer above Nab)

*/
#define CORE_AON_NABHIRQCFG_POL                                      0x00000001U
#define CORE_AON_NABHIRQCFG_POL_M                                    0x00000001U
#define CORE_AON_NABHIRQCFG_POL_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IOTP0
    Offset name:         CORE_AON_O_IOTP0
    Relative address:    0xE8
    Description:         GPIO TO PAD 0
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     VALUE

                         SW value to be reflected on GPIO to pad.

*/
#define CORE_AON_IOTP0_VAL_W                                         32U
#define CORE_AON_IOTP0_VAL_M                                         0xFFFFFFFFU
#define CORE_AON_IOTP0_VAL_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IOTP1
    Offset name:         CORE_AON_O_IOTP1
    Relative address:    0xEC
    Description:         GPIO TO PAD 1
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     VALUE

                         SW value to be reflected on GPIO to pad.

*/
#define CORE_AON_IOTP1_VAL_W                                         13U
#define CORE_AON_IOTP1_VAL_M                                         0x00001FFFU
#define CORE_AON_IOTP1_VAL_S                                         0U
/*

        Field:           SRC
        From..to bits:   24...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SOURCE

                         Set 1 - Used HW source.
                         Set 0 - Used SW source.

                         bit[0] - GPIO3
                         bit[1] - GPIO4
                         bit[2] - GPIO5
                         bit[3] - GPIO6
                         bit[4] - GPIO26
                         bit[5] - GPIO27
                         bit[6] - GPIO28
                         bit[7] - GPIO29

*/
#define CORE_AON_IOTP1_SRC_W                                         8U
#define CORE_AON_IOTP1_SRC_M                                         0xFF000000U
#define CORE_AON_IOTP1_SRC_S                                         24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IOOENCFG0
    Offset name:         CORE_AON_O_IOOENCFG0
    Relative address:    0xF8
    Description:         GPIO OUT ENABLE CONFIG 0
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     VALUE

                         Set 0 - Output.
                         Set 1 - Input.

*/
#define CORE_AON_IOOENCFG0_VAL_W                                     32U
#define CORE_AON_IOOENCFG0_VAL_M                                     0xFFFFFFFFU
#define CORE_AON_IOOENCFG0_VAL_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IOOENCFG1
    Offset name:         CORE_AON_O_IOOENCFG1
    Relative address:    0xFC
    Description:         GPIO OUT ENABLE CONFIG 1
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     VALUE

                         Set 0 - Output.
                         Set 1 - Input.

*/
#define CORE_AON_IOOENCFG1_VAL_W                                     13U
#define CORE_AON_IOOENCFG1_VAL_M                                     0x00001FFFU
#define CORE_AON_IOOENCFG1_VAL_S                                     0U

#endif /* __HW_CORE_AON_H__*/
