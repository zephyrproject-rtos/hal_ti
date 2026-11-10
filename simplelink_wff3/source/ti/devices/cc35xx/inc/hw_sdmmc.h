/******************************************************************************
*  Filename:       hw_sdmmc.h
*
*  Description:    Defines and prototypes for the SDMMC peripheral.
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
#ifndef __HW_SDMMC_H__
#define __HW_SDMMC_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the SDMMC component

--------------------------------------------------------------------------------- */

//This register allows controlling various parameters of the OCP interface
#define SDMMC_O_SYSCFG                                               0x00000110U

//This register provides status information about the module excluding the interrupt status information
#define SDMMC_O_SYSSTA                                               0x00000114U

//Card Status Response Error Detection
#define SDMMC_O_CSRE                                                 0x00000124U

//SDMMC System Test Register
#define SDMMC_O_SYSTEST                                              0x00000128U

//SDMMC Configuration Register
#define SDMMC_O_CON                                                  0x0000012CU

//SDMMC Power counter register
#define SDMMC_O_PWCNT                                                0x00000130U

//DMA System Address
#define SDMMC_O_SDMASA                                               0x00000200U

//Transfer Length Configuration Register
#define SDMMC_O_BLK                                                  0x00000204U

//Command argument register
#define SDMMC_O_ARG                                                  0x00000208U

//Command and data transfer register
#define SDMMC_O_CMD                                                  0x0000020CU

//Response register 10
#define SDMMC_O_RSP10                                                0x00000210U

//Response register 32
#define SDMMC_O_RSP32                                                0x00000214U

//Response register 54
#define SDMMC_O_RSP54                                                0x00000218U

//Response register 76
#define SDMMC_O_RSP76                                                0x0000021CU

//Data register
#define SDMMC_O_DATA                                                 0x00000220U

//SDMMC controller status register
#define SDMMC_O_PSTATE                                               0x00000224U

//Host Control Register
#define SDMMC_O_HCTL                                                 0x00000228U

//SD System Control Register
#define SDMMC_O_SYSCTL                                               0x0000022CU

//The interrupt status regroups all the status of the module internal events that can generate an interrupt
#define SDMMC_O_STAT                                                 0x00000230U

//This register allows to enable/disable the module to set status bits on an event-by-event basis
#define SDMMC_O_IE                                                   0x00000234U

//This register allows to enable/disable the module internal interrupt signaling on an event-by-event basis
#define SDMMC_O_ISE                                                  0x00000238U

//SD_AC12 Error register
#define SDMMC_O_AC12                                                 0x0000023CU

//Capability register
#define SDMMC_O_CAPA                                                 0x00000240U

//Current capability register
#define SDMMC_O_CURCAPA                                              0x00000248U

//Revision register
#define SDMMC_O_REV                                                  0x000002FCU

//The Force Event register is not a physically implemented register
#define SDMMC_O_FE                                                   0x00000250U

//Test-Port select
#define SDMMC_O_TPSEL                                                0x00001040U

//DMA mode select:
#define SDMMC_O_DMAMODE                                              0x00001048U

//DMA indication select:
#define SDMMC_O_DMAIND                                               0x00001050U

//This register define the functional clock frequency, and whether the clock is synchronized to main clock
#define SDMMC_O_CLKSEL                                               0x00001054U

//Event mode register
#define SDMMC_O_EVTMODE                                              0x000010E0U

//This register identifies the peripheral and its exact version
#define SDMMC_O_DESC                                                 0x000010FCU

//SDMMC Status register
#define SDMMC_O_SDMMCSTAT                                            0x00001100U

//SRAM Data Access Registers
#define SDMMC_O_BUFIF                                                0x00001110U

//Clock Enable Register
#define SDMMC_O_CLKCFG                                               0x00004000U



/*-----------------------------------REGISTER------------------------------------
    Register name:       SYSCFG
    Offset name:         SDMMC_O_SYSCFG
    Relative address:    0x110
    Description:         This register allows controlling various parameters of the OCP interface.
    Default Value:       0x00002015

        Field:           AUTOIDLE
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Internal Clock gating strategy
                         0: 	Clocks are free-running
                         1: 	Automatic clock gating strategy is applied, based on the OCP and MMC interface activity


        ENUMs:
            OFF:                         Clocks are free-running
            ON:                          Automatic clock gating strategy is applied
*/
#define SDMMC_SYSCFG_AUTOIDLE                                        0x00000001U
#define SDMMC_SYSCFG_AUTOIDLE_M                                      0x00000001U
#define SDMMC_SYSCFG_AUTOIDLE_S                                      0U
#define SDMMC_SYSCFG_AUTOIDLE_OFF                                    0x00000000U
#define SDMMC_SYSCFG_AUTOIDLE_ON                                     0x00000001U
/*

        Field:           SOFTRST
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Software reset.

                         The bit is automatically reset by the hardware.  During reset, it always returns 0.


*/
#define SDMMC_SYSCFG_SOFTRST                                         0x00000002U
#define SDMMC_SYSCFG_SOFTRST_M                                       0x00000002U
#define SDMMC_SYSCFG_SOFTRST_S                                       1U
/*

        Field:           WUEN
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     This field controls the wakeup capability of the module.

        ENUMs:
            OFF:                         Wakeup capability is disabled
            EN:                          Wakeup capability is enabled
*/
#define SDMMC_SYSCFG_WUEN                                            0x00000004U
#define SDMMC_SYSCFG_WUEN_M                                          0x00000004U
#define SDMMC_SYSCFG_WUEN_S                                          2U
#define SDMMC_SYSCFG_WUEN_OFF                                        0x00000000U
#define SDMMC_SYSCFG_WUEN_EN                                         0x00000004U
/*

        Field:           SIDLEMODE
        From..to bits:   3...4
        DefaultValue:    0x2
        Access type:     read-write
        Description:     Power management
                         We are using this register only to change CON.DVAL,
                         else these bit fields are *not used*, since Idle request is not supported.

*/
#define SDMMC_SYSCFG_SIDLEMODE_W                                     2U
#define SDMMC_SYSCFG_SIDLEMODE_M                                     0x00000018U
#define SDMMC_SYSCFG_SIDLEMODE_S                                     3U
/*

        Field:           CLKIDLECFG
        From..to bits:   8...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clock idle policy register, Clocks activity during wake up mode period.
                         Bit8: OCP interface clock
                         Bit9: Functional clock


        ENUMs:
            OFF:                         Interface and Functional clock may be switched off
            INT:                         Interface clock is maintained. Functional clock may be switched-off.
            FUNC:                        Functional clock is maintained. Interface clock may be switched-off.
            ALL:                         Interface and Functional clocks are maintained.
*/
#define SDMMC_SYSCFG_CLKIDLECFG_W                                    2U
#define SDMMC_SYSCFG_CLKIDLECFG_M                                    0x00000300U
#define SDMMC_SYSCFG_CLKIDLECFG_S                                    8U
#define SDMMC_SYSCFG_CLKIDLECFG_OFF                                  0x00000000U
#define SDMMC_SYSCFG_CLKIDLECFG_INT                                  0x00000100U
#define SDMMC_SYSCFG_CLKIDLECFG_FUNC                                 0x00000200U
#define SDMMC_SYSCFG_CLKIDLECFG_ALL                                  0x00000300U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SYSSTA
    Offset name:         SDMMC_O_SYSSTA
    Relative address:    0x114
    Description:         This register provides status information about the module excluding the interrupt status information.
    Default Value:       0x00000000

        Field:           RSTDONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Internal Reset Monitoring
                         Note: The debounce clock , the interface clock and the functional clock must be provided to the SDMMC host controller to allow the internal reset monitoring.

        ENUMs:
            ONGOING:                     Internal module reset is on-going
            COMPLETE:                    Reset completed
*/
#define SDMMC_SYSSTA_RSTDONE                                         0x00000001U
#define SDMMC_SYSSTA_RSTDONE_M                                       0x00000001U
#define SDMMC_SYSSTA_RSTDONE_S                                       0U
#define SDMMC_SYSSTA_RSTDONE_ONGOING                                 0x00000000U
#define SDMMC_SYSSTA_RSTDONE_COMPLETE                                0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CSRE
    Offset name:         SDMMC_O_CSRE
    Relative address:    0x124
    Description:         Card Status Response Error Detection
                        This register enables the host controller to detect card status errors of response type R1, R1b for all cards and of R5, R5b and R6 response for cards types SD or SDIO. When a bit SD_SD_CSRE[i] is set to 1, if the corresponding bit at the same position in the response RSP10[i] is set to 1, the host controller indicates a card error (SD_STAT.CERR bit) interrupt status to avoid the host driver reading the response register (RSP10).
                        No automatic card error detection for autoCMD12 is implemented; the host system has to check autoCMD12 response register (RSP76) for possible card errors.
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card status response error

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_CSRE_STA_W                                             32U
#define SDMMC_CSRE_STA_M                                             0xFFFFFFFFU
#define SDMMC_CSRE_STA_S                                             0U
#define SDMMC_CSRE_STA_MINIMUM                                       0x00000000U
#define SDMMC_CSRE_STA_MAXIMUM                                       0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       SYSTEST
    Offset name:         SDMMC_O_SYSTEST
    Relative address:    0x128
    Description:         SDMMC System Test Register
                        This register is used to control the signals that connect to I/O pins when the module is configured in system test (SD_SYSTEST) mode for boundary connectivity verification. In SD_SYSTEST mode, a write into SD_CMD register will not start a transfer.
    Default Value:       0x00000000

        Field:           MCKD
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MMC clock output signal data value

        ENUMs:
            LOW:                         The output clock is driven low
            HIGH:                        The output clock is driven high
*/
#define SDMMC_SYSTEST_MCKD                                           0x00000001U
#define SDMMC_SYSTEST_MCKD_M                                         0x00000001U
#define SDMMC_SYSTEST_MCKD_S                                         0U
#define SDMMC_SYSTEST_MCKD_LOW                                       0x00000000U
#define SDMMC_SYSTEST_MCKD_HIGH                                      0x00000001U
/*

        Field:           CDIR
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Control of the CMD pin direction

        ENUMs:
            OUT:                         The CMD line is an output (host to card)
            IN:                          The CMD line is an input (card to host)
*/
#define SDMMC_SYSTEST_CDIR                                           0x00000002U
#define SDMMC_SYSTEST_CDIR_M                                         0x00000002U
#define SDMMC_SYSTEST_CDIR_S                                         1U
#define SDMMC_SYSTEST_CDIR_OUT                                       0x00000000U
#define SDMMC_SYSTEST_CDIR_IN                                        0x00000002U
/*

        Field:           CDAT
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CMD input/output signal data value

        ENUMs:
            LOW:                         If SD_SYSTEST.CDIR bit = 0 (output mode direction), the CMD line is driven low. If SD_SYSTEST.CDIR bit = 1 (input mode direction), no effect.
            HIGH:                        If SD_SYSTEST.CDIR bit = 0 (output mode direction), the CMD line is driven high. If SD_SYSTEST.CDIR bit = 1 (input mode direction), no effect.
*/
#define SDMMC_SYSTEST_CDAT                                           0x00000004U
#define SDMMC_SYSTEST_CDAT_M                                         0x00000004U
#define SDMMC_SYSTEST_CDAT_S                                         2U
#define SDMMC_SYSTEST_CDAT_LOW                                       0x00000000U
#define SDMMC_SYSTEST_CDAT_HIGH                                      0x00000004U
/*

        Field:           DDIR
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Control of the DAT[7:0] pins direction

        ENUMs:
            OUT:                         The DAT lines are outputs (host to card)
            IN:                          The DAT lines are inputs (card to host)
*/
#define SDMMC_SYSTEST_DDIR                                           0x00000008U
#define SDMMC_SYSTEST_DDIR_M                                         0x00000008U
#define SDMMC_SYSTEST_DDIR_S                                         3U
#define SDMMC_SYSTEST_DDIR_OUT                                       0x00000000U
#define SDMMC_SYSTEST_DDIR_IN                                        0x00000008U
/*

        Field:           D0D
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DAT0 input/output signal data value

        ENUMs:
            LOW:                         If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT0 line is driven low. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
            HIGH:                        If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT0 line is driven high. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
*/
#define SDMMC_SYSTEST_D0D                                            0x00000010U
#define SDMMC_SYSTEST_D0D_M                                          0x00000010U
#define SDMMC_SYSTEST_D0D_S                                          4U
#define SDMMC_SYSTEST_D0D_LOW                                        0x00000000U
#define SDMMC_SYSTEST_D0D_HIGH                                       0x00000010U
/*

        Field:           D1D
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DAT1 input/output signal data value

        ENUMs:
            LOW:                         If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT1 line is driven low. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
            HIGH:                        If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT1 line is driven high. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
*/
#define SDMMC_SYSTEST_D1D                                            0x00000020U
#define SDMMC_SYSTEST_D1D_M                                          0x00000020U
#define SDMMC_SYSTEST_D1D_S                                          5U
#define SDMMC_SYSTEST_D1D_LOW                                        0x00000000U
#define SDMMC_SYSTEST_D1D_HIGH                                       0x00000020U
/*

        Field:           D2D
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DAT2 input/output signal data value

        ENUMs:
            LOW:                         If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT2 line is driven low. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
            HIGH:                        If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT2 line is driven high. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
*/
#define SDMMC_SYSTEST_D2D                                            0x00000040U
#define SDMMC_SYSTEST_D2D_M                                          0x00000040U
#define SDMMC_SYSTEST_D2D_S                                          6U
#define SDMMC_SYSTEST_D2D_LOW                                        0x00000000U
#define SDMMC_SYSTEST_D2D_HIGH                                       0x00000040U
/*

        Field:           D3D
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DAT3 input/output signal data value

        ENUMs:
            LOW:                         If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT3 line is driven low. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
            HIGH:                        If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT3 line is driven high. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
*/
#define SDMMC_SYSTEST_D3D                                            0x00000080U
#define SDMMC_SYSTEST_D3D_M                                          0x00000080U
#define SDMMC_SYSTEST_D3D_S                                          7U
#define SDMMC_SYSTEST_D3D_LOW                                        0x00000000U
#define SDMMC_SYSTEST_D3D_HIGH                                       0x00000080U
/*

        Field:           D4D
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DAT4 input/output signal data value

        ENUMs:
            LOW:                         If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT4 line is driven low. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
            HIGH:                        If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT4 line is driven high. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
*/
#define SDMMC_SYSTEST_D4D                                            0x00000100U
#define SDMMC_SYSTEST_D4D_M                                          0x00000100U
#define SDMMC_SYSTEST_D4D_S                                          8U
#define SDMMC_SYSTEST_D4D_LOW                                        0x00000000U
#define SDMMC_SYSTEST_D4D_HIGH                                       0x00000100U
/*

        Field:           D5D
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DAT5 input/output signal data value

        ENUMs:
            LOW:                         If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT5 line is driven low. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
            HIGH:                        If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT5 line is driven high. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
*/
#define SDMMC_SYSTEST_D5D                                            0x00000200U
#define SDMMC_SYSTEST_D5D_M                                          0x00000200U
#define SDMMC_SYSTEST_D5D_S                                          9U
#define SDMMC_SYSTEST_D5D_LOW                                        0x00000000U
#define SDMMC_SYSTEST_D5D_HIGH                                       0x00000200U
/*

        Field:           D6D
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DAT6 input/output signal data value

        ENUMs:
            LOW:                         If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT6 line is driven low. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
            HIGH:                        If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT6 line is driven high. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
*/
#define SDMMC_SYSTEST_D6D                                            0x00000400U
#define SDMMC_SYSTEST_D6D_M                                          0x00000400U
#define SDMMC_SYSTEST_D6D_S                                          10U
#define SDMMC_SYSTEST_D6D_LOW                                        0x00000000U
#define SDMMC_SYSTEST_D6D_HIGH                                       0x00000400U
/*

        Field:           D7D
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DAT7 input/output signal data value

        ENUMs:
            LOW:                         If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT7 line is driven low. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
            HIGH:                        If SD_SYSTEST.DDIR bit = 0 (output mode direction), the DAT7 line is driven high. If SD_SYSTEST.DDIR bit = 1 (input mode direction), no effect.
*/
#define SDMMC_SYSTEST_D7D                                            0x00000800U
#define SDMMC_SYSTEST_D7D_M                                          0x00000800U
#define SDMMC_SYSTEST_D7D_S                                          11U
#define SDMMC_SYSTEST_D7D_LOW                                        0x00000000U
#define SDMMC_SYSTEST_D7D_HIGH                                       0x00000800U
/*

        Field:           SSB
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Set status bit
                         This bit must be cleared prior attempting to clear a status bit of the interrupt status register (SD_STAT).

        ENUMs:
            LOW:                         Clears this SSB bit field.
                         Writing 0 does not clear already set status bits
            HIGH:                        Force to 1 all status bits of the interrupt status register (SD_STAT) only if the corresponding bit field in the Interrupt signal enable register (SD_ISE) is set.
*/
#define SDMMC_SYSTEST_SSB                                            0x00001000U
#define SDMMC_SYSTEST_SSB_M                                          0x00001000U
#define SDMMC_SYSTEST_SSB_S                                          12U
#define SDMMC_SYSTEST_SSB_LOW                                        0x00000000U
#define SDMMC_SYSTEST_SSB_HIGH                                       0x00001000U
/*

        Field:           WAKD
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Wake request output signal data value

        ENUMs:
            LOW:                         The pin SWAKEUP is driven low
            HIGH:                        The pin SWAKEUP is driven high
*/
#define SDMMC_SYSTEST_WAKD                                           0x00002000U
#define SDMMC_SYSTEST_WAKD_M                                         0x00002000U
#define SDMMC_SYSTEST_WAKD_S                                         13U
#define SDMMC_SYSTEST_WAKD_LOW                                       0x00000000U
#define SDMMC_SYSTEST_WAKD_HIGH                                      0x00002000U
/*

        Field:           SDWP
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Write protect input signal (SDWP) data value

        ENUMs:
            LOW:                         The write protect pin SDWP is driven low
            HIGH:                        The write protect pin SDWP is driven high
*/
#define SDMMC_SYSTEST_SDWP                                           0x00004000U
#define SDMMC_SYSTEST_SDWP_M                                         0x00004000U
#define SDMMC_SYSTEST_SDWP_S                                         14U
#define SDMMC_SYSTEST_SDWP_LOW                                       0x00000000U
#define SDMMC_SYSTEST_SDWP_HIGH                                      0x00004000U
/*

        Field:           SDCD
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Card detect input signal (SDCD) data value

        ENUMs:
            LOW:                         The card detect pin is driven low
            HIGH:                        The card detect pin is driven high
*/
#define SDMMC_SYSTEST_SDCD                                           0x00008000U
#define SDMMC_SYSTEST_SDCD_M                                         0x00008000U
#define SDMMC_SYSTEST_SDCD_S                                         15U
#define SDMMC_SYSTEST_SDCD_LOW                                       0x00000000U
#define SDMMC_SYSTEST_SDCD_HIGH                                      0x00008000U
/*

        Field:           OBI
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Out-Of-Band Interrupt (OBI) data value
                         Note: Out-Of-Band Interrupt (OBI) is not supported.

*/
#define SDMMC_SYSTEST_OBI                                            0x00010000U
#define SDMMC_SYSTEST_OBI_M                                          0x00010000U
#define SDMMC_SYSTEST_OBI_S                                          16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CON
    Offset name:         SDMMC_O_CON
    Relative address:    0x12C
    Description:         SDMMC Configuration Register.
                        This register is used:
                         - to select the functional mode or the SYSTEST mode for any card.
                         - to send an initialization sequence to any card.
                         - to enable the detection on DAT[1] of a card interrupt for SDIO cards only.
                        and also to configure :
                         - specific data and command transfers for MMC cards only.
                         - the parameters related to the card detect and write protect input signals.

    Default Value:       0x00000600

        Field:           OD
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card open drain mode
                         This bit must be set to 1 for MMC card commands 1, 2, 3 and 40, and if the MMC card bus is operating in open-drain mode during the response phase to the command sent. Typically, during card identification mode when the card is either in idle, ready or ident state.
                         It is also necessary to set this bit to 1, for a broadcast host response (see Broadcast host response register SD_CON.HR).


        ENUMs:
            OFF:                         No Open Drain
            ON:                          Open Drain or Broadcast host response
*/
#define SDMMC_CON_OD                                                 0x00000001U
#define SDMMC_CON_OD_M                                               0x00000001U
#define SDMMC_CON_OD_S                                               0U
#define SDMMC_CON_OD_OFF                                             0x00000000U
#define SDMMC_CON_OD_ON                                              0x00000001U
/*

        Field:           INIT
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Send initialization stream (all cards)
                         When this bit is set to 1, and the card is idle, an initialization sequence is sent to the card.
                         An initialization sequence consists of setting the mmc_cmd line to 1 during 80 clock cycles.
                         The initialization sequence is mandatory - but it is not required to do it through this bit - this bit makes it easier.
                         Clock divider should be set to ensure that 80 clock periods are greater than 1ms.

                         Note: In this mode, there is no command sent to the card and no response is expected.

                         A command complete interrupt will be generated once the initialization sequence is completed.

        ENUMs:
            OFF:                         The host does not send an initialization sequence
            ON:                          The host sends an initialization sequence
*/
#define SDMMC_CON_INIT                                               0x00000002U
#define SDMMC_CON_INIT_M                                             0x00000002U
#define SDMMC_CON_INIT_S                                             1U
#define SDMMC_CON_INIT_OFF                                           0x00000000U
#define SDMMC_CON_INIT_ON                                            0x00000002U
/*

        Field:           HR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Broadcast host response (MMC cards only)
                         This register is used to force the host to generate a 48-bit response for bc command type.
                         It can be used to terminate the interrupt mode by generating a CMD40 response by the core.
                         In order to have the host response to be generated in open drain mode, the IO must be configured accordingly in EXT_IOMUX.
                         When SD_CON.CEATA bit is set to 1 and SD_ARG cleared to 0, when writing the value of 0 into SD_CMD register, the host controller performs a 'command completion signal disable' token (i.e., mmc_cmd line held to 0 during 47 cycles followed by a 1).

        ENUMs:
            OFF:                         The host does not generate a 48-bit response instead of a command
            ON:                          The host generates a 48-bit response instead of a command or a command completion signal disable token
*/
#define SDMMC_CON_HR                                                 0x00000004U
#define SDMMC_CON_HR_M                                               0x00000004U
#define SDMMC_CON_HR_S                                               2U
#define SDMMC_CON_HR_OFF                                             0x00000000U
#define SDMMC_CON_HR_ON                                              0x00000004U
/*

        Field:           STR
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Stream command (MMC cards only)
                         This bit must be set to 1 only for the stream data transfers (read or write) of the adtc commands.
                         Stream read is a class 1 command (CMD11READ_DAT_UNTIL_STOP).
                         Stream write is a class 3 command (CMD20WRITE_DAT_UNTIL_STOP).

        ENUMs:
            BLOCK:                       Block oriented data transfer
            STREAM:                      Stream oriented data transfer
*/
#define SDMMC_CON_STR                                                0x00000008U
#define SDMMC_CON_STR_M                                              0x00000008U
#define SDMMC_CON_STR_S                                              3U
#define SDMMC_CON_STR_BLOCK                                          0x00000000U
#define SDMMC_CON_STR_STREAM                                         0x00000008U
/*

        Field:           MODE
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Mode select (all cards)
                         This bit selects the functional mode.

        ENUMs:
            FUNC:                        Functional mode.
                         Transfers to the MMC/SD/SDIO cards follow the card protocol. The MMC clock is enabled. MMC/SD transfers are operated under the control of the SD_CMD register.
            SYSTST:                      SYSTEST mode.
                         The signal pins are configured as general-purpose input/output and the 1024-byte buffer is configured as a stack memory accessible only by the local host or system DMA. The pins retain their default type (input, output or inout).
                         SYSTEST mode is operated under the control of the SD_SYSTEST register.
*/
#define SDMMC_CON_MODE                                               0x00000010U
#define SDMMC_CON_MODE_M                                             0x00000010U
#define SDMMC_CON_MODE_S                                             4U
#define SDMMC_CON_MODE_FUNC                                          0x00000000U
#define SDMMC_CON_MODE_SYSTST                                        0x00000010U
/*

        Field:           DW8
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     8-bit mode MMC select (MMC cards only)
                         For SD/SDIO cards, this bit must be cleared to 0.
                         For MMC card, this bit must be set following a valid SWITCH command (CMD6) with the correct value and extend CSD index written in the argument.
                         Prior to this command, the MMC card configuration register (CSD and EXT_CSD) must be verified for compliancy with MMC standard specification.

        ENUMs:
            _1OR4BIT:                    1-bit or 4-bit data width
            _8BIT:                       Open drain or broadcast host response
*/
#define SDMMC_CON_DW8                                                0x00000020U
#define SDMMC_CON_DW8_M                                              0x00000020U
#define SDMMC_CON_DW8_S                                              5U
#define SDMMC_CON_DW8__1OR4BIT                                       0x00000000U
#define SDMMC_CON_DW8__8BIT                                          0x00000020U
/*

        Field:           MIT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MMC interrupt command (MMC cards only).
                         This bit must be set to 1, when the next write access to the command register (SD_CMD) is for writing a MMC interrupt command (CMD40) requiring the command timeout detection to be disabled for the command response.

        ENUMs:
            OFF:                         MMC interrupt command not possible, command timeout enabled
            ON:                          MMC interrupt command possible, Command timeout disabled
*/
#define SDMMC_CON_MIT                                                0x00000040U
#define SDMMC_CON_MIT_M                                              0x00000040U
#define SDMMC_CON_MIT_S                                              6U
#define SDMMC_CON_MIT_OFF                                            0x00000000U
#define SDMMC_CON_MIT_ON                                             0x00000040U
/*

        Field:           CDP
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card detect polarity
                         All cards

                         This bit selects the active level of the card detect input signal (SDCD).
                         The usage of the card detect input signal (SDCD) is optional and depends on the system integration and the type of the connector housing that accommodates the card.


        ENUMs:
            LOW:                         Active low level
            HIGH:                        Active high level
*/
#define SDMMC_CON_CDP                                                0x00000080U
#define SDMMC_CON_CDP_M                                              0x00000080U
#define SDMMC_CON_CDP_S                                              7U
#define SDMMC_CON_CDP_LOW                                            0x00000000U
#define SDMMC_CON_CDP_HIGH                                           0x00000080U
/*

        Field:           WPP
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write protect polarity
                         For SD and SDIO cards only

                         This bit selects the active level of the write protect input signal (SDWP).
                         The usage of the write protect input signal (SDWP) is optional and depends on the system integration and the type of the connector housing that accommodates the card.


        ENUMs:
            LOW:                         Active low level
            HIGH:                        Active high level
*/
#define SDMMC_CON_WPP                                                0x00000100U
#define SDMMC_CON_WPP_M                                              0x00000100U
#define SDMMC_CON_WPP_S                                              8U
#define SDMMC_CON_WPP_LOW                                            0x00000000U
#define SDMMC_CON_WPP_HIGH                                           0x00000100U
/*

        Field:           DVAL
        From..to bits:   9...10
        DefaultValue:    0x3
        Access type:     read-write
        Description:     Debounce filter value (all cards)
                         This register is used to define a debounce period to filter the card detect input signal (SDCD).
                         The usage of the card detect input signal (SDCD) is optional and depends on the system integration and the type of the connector housing that accommodates the card.

        ENUMs:
            DEB0:                        33 us debounce period
            DEB1:                        231 us debounce period
            DEB2:                        1 ms debounce period
            DEB3:                        8.4 ms debounce period
*/
#define SDMMC_CON_DVAL_W                                             2U
#define SDMMC_CON_DVAL_M                                             0x00000600U
#define SDMMC_CON_DVAL_S                                             9U
#define SDMMC_CON_DVAL_DEB0                                          0x00000000U
#define SDMMC_CON_DVAL_DEB1                                          0x00000200U
#define SDMMC_CON_DVAL_DEB2                                          0x00000400U
#define SDMMC_CON_DVAL_DEB3                                          0x00000600U
/*

        Field:           CTPL
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Control Power for DAT[1] line

                         MMC and SD cards:
                         By default, this bit is set to 0 and the host controller automatically disables all the input buffers outside of a transaction to minimize the leakage current.

                         SDIO cards:
                         When this bit is set to 1, the host controller automatically disables all the input buffers except the buffer of DAT[1]  outside of a transaction in order to detect asynchronous card interrupt on DAT[1] line and minimize the leakage current of the buffers.


        ENUMs:
            ALL:                         Disable all the input buffers outside of a transaction
            NOTDAT1:                     Disable all the input buffers except the buffer of DAT[1] outside of a transaction

*/
#define SDMMC_CON_CTPL                                               0x00000800U
#define SDMMC_CON_CTPL_M                                             0x00000800U
#define SDMMC_CON_CTPL_S                                             11U
#define SDMMC_CON_CTPL_ALL                                           0x00000000U
#define SDMMC_CON_CTPL_NOTDAT1                                       0x00000800U
/*

        Field:           CEATA
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CE-ATA control mode (MMC cards compliant with CE-ATA)
                         This bit is used to indicate that next commands are considered as specific CE-ATA commands that potentially use 'command completion' features.

        ENUMs:
            STANDARD:                    Standard MMC/SD/SDIO mode
            CEATA:                       CE-ATA mode. Next commands are considered as CE-ATA commands.
*/
#define SDMMC_CON_CEATA                                              0x00001000U
#define SDMMC_CON_CEATA_M                                            0x00001000U
#define SDMMC_CON_CEATA_S                                            12U
#define SDMMC_CON_CEATA_STANDARD                                     0x00000000U
#define SDMMC_CON_CEATA_CEATA                                        0x00001000U
/*

        Field:           OBIP
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Out-of-Band Interrupt Polarity
                         Note: The Out-of-Band (OBI) interrupt is not supported.

        ENUMs:
            MIN:                         Minimum value
            MAX:                         Maximum value
*/
#define SDMMC_CON_OBIP                                               0x00002000U
#define SDMMC_CON_OBIP_M                                             0x00002000U
#define SDMMC_CON_OBIP_S                                             13U
#define SDMMC_CON_OBIP_MIN                                           0x00000000U
#define SDMMC_CON_OBIP_MAX                                           0x00002000U
/*

        Field:           OBIE
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Out-of-Band Interrupt Enable.
                         Note: The Out-of-Band (OBI) interrupt is not supported.

        ENUMs:
            MIN:                         Minimum value
            MAX:                         Maximum value
*/
#define SDMMC_CON_OBIE                                               0x00004000U
#define SDMMC_CON_OBIE_M                                             0x00004000U
#define SDMMC_CON_OBIE_S                                             14U
#define SDMMC_CON_OBIE_MIN                                           0x00000000U
#define SDMMC_CON_OBIE_MAX                                           0x00004000U
/*

        Field:           PADEN
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Control Power for MMC Lines.
                         Note: Power control is not supported using this bit.

        ENUMs:
            MIN:                         Minimum value
            MAX:                         Maximum value
*/
#define SDMMC_CON_PADEN                                              0x00008000U
#define SDMMC_CON_PADEN_M                                            0x00008000U
#define SDMMC_CON_PADEN_S                                            15U
#define SDMMC_CON_PADEN_MIN                                          0x00000000U
#define SDMMC_CON_PADEN_MAX                                          0x00008000U
/*

        Field:           CLKEXTFREE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     External clock free running
                         This register is used to maintain card clock out of transfer transaction to enable peripheral module (for example to generate a synchronous interrupt on mmc_dat[1] ).
                         The Clock will be maintained only if SD_SYSCTL.CEN bit is set.

        ENUMs:
            OFF:                         External card clock is cut off outside active transaction period
            ON:                          External card clock is maintained even out of active transaction period only if SD_SYSCTL.CEN bit is set.
*/
#define SDMMC_CON_CLKEXTFREE                                         0x00010000U
#define SDMMC_CON_CLKEXTFREE_M                                       0x00010000U
#define SDMMC_CON_CLKEXTFREE_S                                       16U
#define SDMMC_CON_CLKEXTFREE_OFF                                     0x00000000U
#define SDMMC_CON_CLKEXTFREE_ON                                      0x00010000U
/*

        Field:           REVERVED
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA Master or Slave selection
                         Note:  these bit fields are *not used*, since the IP not support MDMA.

*/
#define SDMMC_CON_REVERVED                                           0x00100000U
#define SDMMC_CON_REVERVED_M                                         0x00100000U
#define SDMMC_CON_REVERVED_S                                         20U
/*

        Field:           SDMALNE
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Peripheral DMA Level/Edge Request
                         The waveform of the DMA request can be configured either edge sensitive with early de-assertion on first access to SD_DATA register or late de-assertion, request remains active until last allowed data written into SD_DATA.

        ENUMs:
            EDGE:                        peripheral DMA edge sensitive
            LEVEL:                       peripheral DMA level sensitive
*/
#define SDMMC_CON_SDMALNE                                            0x00200000U
#define SDMMC_CON_SDMALNE_M                                          0x00200000U
#define SDMMC_CON_SDMALNE_S                                          21U
#define SDMMC_CON_SDMALNE_EDGE                                       0x00000000U
#define SDMMC_CON_SDMALNE_LEVEL                                      0x00200000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PWCNT
    Offset name:         SDMMC_O_PWCNT
    Relative address:    0x130
    Description:         SDMMC Power counter register
                        This register is used to program a MMC counter to delay command transfers after activating the PAD power, this value depends on PAD characteristics and voltage.
    Default Value:       0x00000000

        Field:           NUMDEL
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Power counter
                         This register is used to introduce a delay between the PAD ACTIVE pin assertion and the command issued.
                         0h = No additional delay added
                         1h = TCF delay (card clock period)
                         2h = TCF x 2 delay (card clock period)
                         FFFEh = TCF x 65534 delay (card clock period)
                         FFFFh = TCF x 65535 delay (card clock period)

        ENUMs:
            MINIMUM:                     Minimum value of PWCNT
            MAXIMUM:                     Maximum value of PWCNT
*/
#define SDMMC_PWCNT_NUMDEL_W                                         16U
#define SDMMC_PWCNT_NUMDEL_M                                         0x0000FFFFU
#define SDMMC_PWCNT_NUMDEL_S                                         0U
#define SDMMC_PWCNT_NUMDEL_MINIMUM                                   0x00000000U
#define SDMMC_PWCNT_NUMDEL_MAXIMUM                                   0x0000FFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       SDMASA
    Offset name:         SDMMC_O_SDMASA
    Relative address:    0x200
    Description:         DMA System Address
                        This register contains the system memory address for a SDMA transfer.
                        When the Host Controller stops a SDMA transfer, this register shall point to the system address of the next contiguous data position. It can be accessed only if no transaction is executing (i.e., after a transaction has stopped).
                        Read operations during transfers may return an invalid value.
                        The Host Driver shall initialize this register before starting a SDMA transaction.
                        After SDMA has stopped, the next system address of the next contiguous data position can be read from this register.
                        The SDMA transfer waits at the every boundary specified by the Host SDMA Buffer Boundary in the Block Size register.
                        The Host Controller generates DMA Interrupt to request the Host Driver to update this register.
                        The Host Driver sets the next system address of the next data position to this register.
                        When the most upper byte of this register (003h) is written, the Host Controller restarts the SDMA transfer.
                        When restarting SDMA by the Resume command or by setting Continue Request in the Block Gap Control register, the Host Controller shall start at the next contiguous address stored here in the SDMA System Address register.

    Default Value:       0x00000000

        Field:           ADDR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SDMA System Address register

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_SDMASA_ADDR_W                                          32U
#define SDMMC_SDMASA_ADDR_M                                          0xFFFFFFFFU
#define SDMMC_SDMASA_ADDR_S                                          0U
#define SDMMC_SDMASA_ADDR_MINIMUM                                    0x00000000U
#define SDMMC_SDMASA_ADDR_MAXIMUM                                    0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       BLK
    Offset name:         SDMMC_O_BLK
    Relative address:    0x204
    Description:         Transfer Length Configuration Register

                        BLEN is the block size register.
                        NBLK is the block count register.

                        This register shall be used for any card.

    Default Value:       0x00000000

        Field:           BLEN
        From..to bits:   0...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transfer block size
                         This register is enabled when Block Count Enable (SD_CMD.BCE) is set to 1 and is valid only for multiple block transfers. It specifies the block size for block data transfers.
                         Read operations during transfers may return an invalid value, and write operations are ignored.
                         0h = No data transfer
                         1h = 1 byte block length
                         2h = 2 bytes block length
                         3h = 3 bytes block length
                         1FFh = 511 bytes block length
                         200h = 512 bytes block length
                         3FFh = 1023 bytes block length
                         400h = 1024 bytes block length


        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_BLK_BLEN_W                                             11U
#define SDMMC_BLK_BLEN_M                                             0x000007FFU
#define SDMMC_BLK_BLEN_S                                             0U
#define SDMMC_BLK_BLEN_MINIMUM                                       0x00000000U
#define SDMMC_BLK_BLEN_MAXIMUM                                       0x000007FFU
/*

        Field:           NBLK
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Block count for current transfer
                         This register is enabled when Block count Enable (SD_CMD.BCE bit) is set to 1 and is valid only for multiple block transfers.
                         Setting the block count to 0 results no data blocks being transferred.
                         Note: The host controller decrements the block count after each block transfer and stops when the count reaches zero.
                         This register can be accessed only if no transaction is executing (i.e., after a transaction has stopped). Read operations during transfers may return an invalid value and write operation will be ignored.
                         0h = Stop count
                         1h = 1 block
                         2h = 2 blocks
                         FFFFh = 65535 blocks

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_BLK_NBLK_W                                             16U
#define SDMMC_BLK_NBLK_M                                             0xFFFF0000U
#define SDMMC_BLK_NBLK_S                                             16U
#define SDMMC_BLK_NBLK_MINIMUM                                       0x00000000U
#define SDMMC_BLK_NBLK_MAXIMUM                                       0xFFFF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ARG
    Offset name:         SDMMC_O_ARG
    Relative address:    0x208
    Description:         Command argument register
                        This register contains command argument specified as bit 39-8 of Command-Format. These registers must be initialized prior to sending the command itself to the card (write action into the register SD_CMD register). Only exception is for a command index specifying stuff bits in arguments, making a write unnecessary.
    Default Value:       0x00000000

        Field:           CMDARG
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command argument

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_ARG_CMDARG_W                                           32U
#define SDMMC_ARG_CMDARG_M                                           0xFFFFFFFFU
#define SDMMC_ARG_CMDARG_S                                           0U
#define SDMMC_ARG_CMDARG_MINIMUM                                     0x00000000U
#define SDMMC_ARG_CMDARG_MAXIMUM                                     0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       CMD
    Offset name:         SDMMC_O_CMD
    Relative address:    0x20C
    Description:         Command and data transfer register
                        This register configures the data and command transfers. A write into the most significant byte send the command. A write into SD_CMD[15:0] during data transfer has no effect. This register can be used for any card. In SYSTEST mode, a write to the SD_CMD register will not start a transfer.
    Default Value:       0x00000000

        Field:           DE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA enable
                         DMA can be enabled only if DMA Support bit in the Capabilities register is set. If this bit is set to 1, a DMA operation starts when the host writes to the upper byte of Command register (00Fh).

        ENUMs:
            ENABLE:                      DMA mode enable
            DISABLE:                     DMA mode disable
*/
#define SDMMC_CMD_DE                                                 0x00000001U
#define SDMMC_CMD_DE_M                                               0x00000001U
#define SDMMC_CMD_DE_S                                               0U
#define SDMMC_CMD_DE_ENABLE                                          0x00000001U
#define SDMMC_CMD_DE_DISABLE                                         0x00000000U
/*

        Field:           BCE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Block Count Enable
                         This bit is used to enable the Block count register, which is only relevant for multiple block transfers.
                         When this bit is 0, the Block Count register is disabled, which is useful in executing an infinite transfer.

        ENUMs:
            ENABLE:                      Block count enabled for multiple block transfer with known number of blocks
            DISABLE:                     Block count disabled for infinite transfer
*/
#define SDMMC_CMD_BCE                                                0x00000002U
#define SDMMC_CMD_BCE_M                                              0x00000002U
#define SDMMC_CMD_BCE_S                                              1U
#define SDMMC_CMD_BCE_ENABLE                                         0x00000002U
#define SDMMC_CMD_BCE_DISABLE                                        0x00000000U
/*

        Field:           ACEN
        From..to bits:   2...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Auto CMD Enable
                         This field determines use of auto command functions.
                         There are two methods to stop Multiple-block read and write operation

                         (1) Auto CMD12 Enable
                         When this field is set to 01b, the Host Controller issues CMD12 automatically when last block transfer is completed. Auto CMD12 error is indicated to the Auto CMD Error Status register. The Host Driver shall not set this bit if the command does not require CMD12. In particular, secure commands defined in the Part 3 File Security specification do not require CMD12.

                         (2) Auto CMD23 Enable
                         When this bit field is set to 10b, the Host Controller issues a CMD23 automatically before issuing a command specified in the Command Register. The Host Controller Version 3.00 and later shall support this function. The following conditions are required to use the Auto CMD23.
                         - Auto CMD23 Supported (Host Controller Version is 3.00 or later)
                         - A memory card that supports CMD23 (SCR[33]=1)
                         - If DMA is used, it shall be ADMA.
                         - Only when CMD18 or CMD25 is issued
                         (Note, the Host Controller does not check command index.)

                         Auto CMD23 can be used with or without ADMA. By writing the Command register, the Host Controller issues a CMD23 first and then issues a command specified by the Command Index in Command register. If response errors of CMD23 are detected, the second command is not issued. A CMD23 error is indicated in the Auto CMD Error Status register. 32-bit block count value for CMD23 is set to SDMA System Address / Argument 2 register.


        ENUMs:
            ENA12:                       Auto CMD12 enable or CCS detection enabled
            DISABLE:                     Auto CMD12 disable
            ENA23:                       Auto CMD23 enable
*/
#define SDMMC_CMD_ACEN_W                                             2U
#define SDMMC_CMD_ACEN_M                                             0x0000000CU
#define SDMMC_CMD_ACEN_S                                             2U
#define SDMMC_CMD_ACEN_ENA12                                         0x00000004U
#define SDMMC_CMD_ACEN_DISABLE                                       0x00000000U
#define SDMMC_CMD_ACEN_ENA23                                         0x00000008U
/*

        Field:           DDIR
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data transfer Direction Select
                         This bit defines the data transfer direction

        ENUMs:
            READ:                        Data Read (card to host)
            WRITE:                       Data Write (host to card)
*/
#define SDMMC_CMD_DDIR                                               0x00000010U
#define SDMMC_CMD_DDIR_M                                             0x00000010U
#define SDMMC_CMD_DDIR_S                                             4U
#define SDMMC_CMD_DDIR_READ                                          0x00000010U
#define SDMMC_CMD_DDIR_WRITE                                         0x00000000U
/*

        Field:           MSBS
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Multi/Single block select
                         This bit must be set to 1 for data transfer in case of multi block command.
                         For any others command this bit must be cleared to 0.

        ENUMs:
            BLOCK:                       Multiple block
            SINGLE:                      Single block
*/
#define SDMMC_CMD_MSBS                                               0x00000020U
#define SDMMC_CMD_MSBS_M                                             0x00000020U
#define SDMMC_CMD_MSBS_S                                             5U
#define SDMMC_CMD_MSBS_BLOCK                                         0x00000020U
#define SDMMC_CMD_MSBS_SINGLE                                        0x00000000U
/*

        Field:           RSPTYPE
        From..to bits:   16...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Response type
                         This bits defines the response type of the command.

        ENUMs:
            LEN136:                      Response Length 136 bits
            NORESP:                      No response
            LEN48:                       Response Length 48 bits
            LEN48BUSY:                   Response Length 48 bits with busy after response
*/
#define SDMMC_CMD_RSPTYPE_W                                          2U
#define SDMMC_CMD_RSPTYPE_M                                          0x00030000U
#define SDMMC_CMD_RSPTYPE_S                                          16U
#define SDMMC_CMD_RSPTYPE_LEN136                                     0x00010000U
#define SDMMC_CMD_RSPTYPE_NORESP                                     0x00000000U
#define SDMMC_CMD_RSPTYPE_LEN48                                      0x00020000U
#define SDMMC_CMD_RSPTYPE_LEN48BUSY                                  0x00030000U
/*

        Field:           CCCE
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command CRC check enable
                         If this bit is set to 1, the host checks the CRC field in the response. If an error is detected, it is reported as a Command CRC Error.
                         If this bit is set to 0, the CRC field is not checked.

        ENUMs:
            ENABLE:                      CRC field check enable
            DISABLE:                     CRC field check disable
*/
#define SDMMC_CMD_CCCE                                               0x00080000U
#define SDMMC_CMD_CCCE_M                                             0x00080000U
#define SDMMC_CMD_CCCE_S                                             19U
#define SDMMC_CMD_CCCE_ENABLE                                        0x00080000U
#define SDMMC_CMD_CCCE_DISABLE                                       0x00000000U
/*

        Field:           CICE
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command Index check enable
                         If this bit is set to 1, the host checks the index field in the response to see if it has the same value as the command index. If it is not, it is reported as a Command Index Error.
                         If this bit is set to 0, the Index field is not checked.

        ENUMs:
            ENABLE:                      Index check enable
            DISABLE:                     Index check disable
*/
#define SDMMC_CMD_CICE                                               0x00100000U
#define SDMMC_CMD_CICE_M                                             0x00100000U
#define SDMMC_CMD_CICE_S                                             20U
#define SDMMC_CMD_CICE_ENABLE                                        0x00100000U
#define SDMMC_CMD_CICE_DISABLE                                       0x00000000U
/*

        Field:           DP
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data present select
                         This register indicates that data is present and DAT line(s) shall be used.
                         It must be cleared to 0 in the following conditions:
                         - Command using only CMD line
                         - Command with no data transfer but using busy signal on DAT[0] line
                         - Resume command

        ENUMs:
            DAT:                         Command with data transfer
            NODAT:                       Command with no data transfer
*/
#define SDMMC_CMD_DP                                                 0x00200000U
#define SDMMC_CMD_DP_M                                               0x00200000U
#define SDMMC_CMD_DP_S                                               21U
#define SDMMC_CMD_DP_DAT                                             0x00200000U
#define SDMMC_CMD_DP_NODAT                                           0x00000000U
/*

        Field:           CMDTYP
        From..to bits:   22...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command type
                         This bitfield specifies three types of special commands:
                         - Suspend
                         - Resume
                         - Abort
                         The bitfield is cleared to 0 for all other commands.

        ENUMs:
            SUSPEND:                     Upon CMD52 "Bus Suspend" operation
            OTHER:                       Others commands
            RESUME:                      Upon CMD52 "Function Select" operation
            ABORT:                       Upon CMD12 or CMD52 "I/O Abort" command
*/
#define SDMMC_CMD_CMDTYP_W                                           2U
#define SDMMC_CMD_CMDTYP_M                                           0x00C00000U
#define SDMMC_CMD_CMDTYP_S                                           22U
#define SDMMC_CMD_CMDTYP_SUSPEND                                     0x00400000U
#define SDMMC_CMD_CMDTYP_OTHER                                       0x00000000U
#define SDMMC_CMD_CMDTYP_RESUME                                      0x00800000U
#define SDMMC_CMD_CMDTYP_ABORT                                       0x00C00000U
/*

        Field:           IDX
        From..to bits:   24...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command index
                         Binary encoded value from 0 to 63 specifying the command number to send to card.
                         Examples:
                         - INDEX = 7h, sends CMD7 to the card
                         - INDEX = 29h, sends CMD41 to the card

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_CMD_IDX_W                                              6U
#define SDMMC_CMD_IDX_M                                              0x3F000000U
#define SDMMC_CMD_IDX_S                                              24U
#define SDMMC_CMD_IDX_MINIMUM                                        0x00000000U
#define SDMMC_CMD_IDX_MAXIMUM                                        0x3F000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RSP10
    Offset name:         SDMMC_O_RSP10
    Relative address:    0x210
    Description:         Response register 10
                        This 32-bit register holds bits positions [31:0] of command response type R1, R1b, R2, R3, R4, R5, R5b or R6.
    Default Value:       0x00000000

        Field:           RSP0
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command Response [15:0]

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_RSP10_RSP0_W                                           16U
#define SDMMC_RSP10_RSP0_M                                           0x0000FFFFU
#define SDMMC_RSP10_RSP0_S                                           0U
#define SDMMC_RSP10_RSP0_MINIMUM                                     0x00000000U
#define SDMMC_RSP10_RSP0_MAXIMUM                                     0x0000FFFFU
/*

        Field:           RSP1
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command Response [31:16]

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_RSP10_RSP1_W                                           16U
#define SDMMC_RSP10_RSP1_M                                           0xFFFF0000U
#define SDMMC_RSP10_RSP1_S                                           16U
#define SDMMC_RSP10_RSP1_MINIMUM                                     0x00000000U
#define SDMMC_RSP10_RSP1_MAXIMUM                                     0xFFFF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RSP32
    Offset name:         SDMMC_O_RSP32
    Relative address:    0x214
    Description:         Response register 32
                        This 32-bit register holds bits positions [63:32] of command response type R2.
    Default Value:       0x00000000

        Field:           RSP2
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command Response [47:32]

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_RSP32_RSP2_W                                           16U
#define SDMMC_RSP32_RSP2_M                                           0x0000FFFFU
#define SDMMC_RSP32_RSP2_S                                           0U
#define SDMMC_RSP32_RSP2_MINIMUM                                     0x00000000U
#define SDMMC_RSP32_RSP2_MAXIMUM                                     0x0000FFFFU
/*

        Field:           RSP3
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command Response [63:48]

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_RSP32_RSP3_W                                           16U
#define SDMMC_RSP32_RSP3_M                                           0xFFFF0000U
#define SDMMC_RSP32_RSP3_S                                           16U
#define SDMMC_RSP32_RSP3_MINIMUM                                     0x00000000U
#define SDMMC_RSP32_RSP3_MAXIMUM                                     0xFFFF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RSP54
    Offset name:         SDMMC_O_RSP54
    Relative address:    0x218
    Description:         Response register 54
                        This 32-bit register holds bits positions [95:64] of command response type R2.
    Default Value:       0x00000000

        Field:           RSP4
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command Response [79:64]

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_RSP54_RSP4_W                                           16U
#define SDMMC_RSP54_RSP4_M                                           0x0000FFFFU
#define SDMMC_RSP54_RSP4_S                                           0U
#define SDMMC_RSP54_RSP4_MINIMUM                                     0x00000000U
#define SDMMC_RSP54_RSP4_MAXIMUM                                     0x0000FFFFU
/*

        Field:           RSP5
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command Response [95:80]

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_RSP54_RSP5_W                                           16U
#define SDMMC_RSP54_RSP5_M                                           0xFFFF0000U
#define SDMMC_RSP54_RSP5_S                                           16U
#define SDMMC_RSP54_RSP5_MINIMUM                                     0x00000000U
#define SDMMC_RSP54_RSP5_MAXIMUM                                     0xFFFF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RSP76
    Offset name:         SDMMC_O_RSP76
    Relative address:    0x21C
    Description:         Response register 76
                        This 32-bit register holds bits positions [127:96] of command response type R2.
    Default Value:       0x00000000

        Field:           RSP6
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command Response [111:96]

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_RSP76_RSP6_W                                           16U
#define SDMMC_RSP76_RSP6_M                                           0x0000FFFFU
#define SDMMC_RSP76_RSP6_S                                           0U
#define SDMMC_RSP76_RSP6_MINIMUM                                     0x00000000U
#define SDMMC_RSP76_RSP6_MAXIMUM                                     0x0000FFFFU
/*

        Field:           RSP7
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command Response [127:112]

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_RSP76_RSP7_W                                           16U
#define SDMMC_RSP76_RSP7_M                                           0xFFFF0000U
#define SDMMC_RSP76_RSP7_S                                           16U
#define SDMMC_RSP76_RSP7_MINIMUM                                     0x00000000U
#define SDMMC_RSP76_RSP7_MAXIMUM                                     0xFFFF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DATA
    Offset name:         SDMMC_O_DATA
    Relative address:    0x220
    Description:         Data register
                        This register is the 32-bit entry point of the buffer for read or write data transfers.
                        The buffer size is 32bits x 256 (1024 bytes). Bytes within a word are stored and read in little endian format. This buffer can be used as two 512 byte buffers to transfer data efficiently without reducing the throughput. Sequential and contiguous access is necessary to increment the pointer correctly. Random or skipped access is not allowed.
                        If the local host accesses this register byte-wise or 16bit-wise, the least significant byte (bits [7:0]) must always be written/read first. The update of the buffer address is done on the most significant byte write.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Buffer data register
                         In functional mode (SD_CON.MODE = FUNC):
                         - a read access to this register is allowed only when the buffer read enable status is set to 1 (SD_PSTATE.BREN), otherwise a bad access (SD_STAT.BADA) is signaled.
                         - a write access to this register is allowed only when the buffer write enable status is set to 1 (SD_PSTATE.BWEN), otherwise a bad access (SD_STAT.BADA) is signaled and the data is not written.

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_DATA_VAL_W                                             32U
#define SDMMC_DATA_VAL_M                                             0xFFFFFFFFU
#define SDMMC_DATA_VAL_S                                             0U
#define SDMMC_DATA_VAL_MINIMUM                                       0x00000000U
#define SDMMC_DATA_VAL_MAXIMUM                                       0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       PSTATE
    Offset name:         SDMMC_O_PSTATE
    Relative address:    0x224
    Description:         SDMMC controller status register
                        The host can get the status of the SDMMC controller from this 32-bit read only register.
    Default Value:       0x00000000

        Field:           CMDI
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command Inhibit (CMD) (SD Mode Only)
                         If this bit is 0, it indicates the CMD line is not in use and the host can issue a SD command using the CMD line. This bit is set immediately after the Command register (00Fh) is written. This bit is cleared when the command response is received. Even if the Command Inhibit (DAT) is set to 1, Commands using only the CMD line can be issued if this bit is 0. Changing from 1 to 0 generates a Command complete interrupt. If the host cannot issue the command because of a command conflict error or because of Command Not Issued By Auto CMD12 Error, this bit shall remain 1 and the Command Complete is not set. Status issuing Auto CMD12 is not read from this bit.
                         Auto CMD12 and Auto CMD23 consist of two responses. In this case, this bit is not cleared by the response of CMD12 or CMD23 but cleared by the response of a read/write command. Status issuing Auto CMD12 is not read from this bit. So if a command is issued during Auto CMD12 operation, Host Controller shall manage to issue two commands: CMD12 and a command set by Command register.

        ENUMs:
            NOTALLOWED:                  Issuing of command using mmc_cmd line is not allowed
            ALLOWED:                     Issuing of command using mmc_cmd line is allowed
*/
#define SDMMC_PSTATE_CMDI                                            0x00000001U
#define SDMMC_PSTATE_CMDI_M                                          0x00000001U
#define SDMMC_PSTATE_CMDI_S                                          0U
#define SDMMC_PSTATE_CMDI_NOTALLOWED                                 0x00000001U
#define SDMMC_PSTATE_CMDI_ALLOWED                                    0x00000000U
/*

        Field:           DATI
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command Inhibit (DAT) (SD Mode Only)
                         This status bit is generated if either the DAT Line Active or the Read transfer Active is set to 1. If this bit is 0, it indicates the host can issue the next SD command. Commands with busy signal belong to Command Inhibit (DAT) (ex. R1b, R5b type).
                         Changing from 1 to 0 generates a Transfer Complete interrupt.
                         Note: The SD Host Driver can save registers in the range of 000-00Dh for a suspend transaction after this bit has changed from 1 to 0.

        ENUMs:
            NOTALLOWED:                  Issuing of command using DAT lines is not allowed
            ALLOWED:                     Issuing of command using the DAT lines is allowed
*/
#define SDMMC_PSTATE_DATI                                            0x00000002U
#define SDMMC_PSTATE_DATI_M                                          0x00000002U
#define SDMMC_PSTATE_DATI_S                                          1U
#define SDMMC_PSTATE_DATI_NOTALLOWED                                 0x00000002U
#define SDMMC_PSTATE_DATI_ALLOWED                                    0x00000000U
/*

        Field:           DLA
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DATA Line Active (SD Mode only)
                         This bit indicates whether one of the DATA lines on SD bus is in use.

        ENUMs:
            ACTIVE:                      mmc_data line active
            INACTIVE:                    mmc_data line inactive
*/
#define SDMMC_PSTATE_DLA                                             0x00000004U
#define SDMMC_PSTATE_DLA_M                                           0x00000004U
#define SDMMC_PSTATE_DLA_S                                           2U
#define SDMMC_PSTATE_DLA_ACTIVE                                      0x00000004U
#define SDMMC_PSTATE_DLA_INACTIVE                                    0x00000000U
/*

        Field:           WTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Write transfer active
                         This status indicates a write transfer active. If this bit is 0, it means no valid write data exists.
                         This bit is set in either of the following cases:
                         - After the end bit of the write command.
                         - When writing a 1 to Continue Request in the Block Gap Control register to restart a write transfer.
                         This bit is cleared in either of the following cases:
                         - After getting the CRC status of the last data block as specified by the transfer count (Single or Multiple)
                         - After getting a CRC status of any block where data transmission is about to be stopped by a Stop At Block Gap Request. During a write transaction, a Block Gap Event interrupt is generated when this bit is changed to 0, as a result of the Stop At Block Gap Request being set. This status is useful for the host to determine when to issue commands during write busy.

        ENUMs:
            ACTIVE:                      Write data transfer on going
            NODATA:                      No valid data

*/
#define SDMMC_PSTATE_WTA                                             0x00000100U
#define SDMMC_PSTATE_WTA_M                                           0x00000100U
#define SDMMC_PSTATE_WTA_S                                           8U
#define SDMMC_PSTATE_WTA_ACTIVE                                      0x00000100U
#define SDMMC_PSTATE_WTA_NODATA                                      0x00000000U
/*

        Field:           RTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Read transfer active (SD mode only)
                         This status is used for detecting completion of a read transfer.
                         This bit is set to 1 for either of the following conditions:
                         - After the end bit of the read command
                         - When writing a 1 to continue Request in the Block Gap Control register to restart a read transfer
                         This bit is cleared to 0 for either of the following conditions:
                         - When the last data block as specified by block length is transferred to the system.
                         - When all valid data blocks have been transferred to the system and no current block transfers are being sent as a result of the Stop At Block Gap Request set to 1. A transfer complete interrupt is generated when this bit changes to 0.

        ENUMs:
            ACTIVE:                      Read data transfer on going
            NODATA:                      No valid data
*/
#define SDMMC_PSTATE_RTA                                             0x00000200U
#define SDMMC_PSTATE_RTA_M                                           0x00000200U
#define SDMMC_PSTATE_RTA_S                                           9U
#define SDMMC_PSTATE_RTA_ACTIVE                                      0x00000200U
#define SDMMC_PSTATE_RTA_NODATA                                      0x00000000U
/*

        Field:           BWE
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Buffer write enable
                         This status is used for non-DMA write transfers.
                         This read only flag indicates if space is available for write data. If this bit is 1, data can be written to the buffer.
                         A change of this bit from 1 to 0 occurs when all the block data is written to the buffer.
                         A change of this bit from 0 to 1 occurs when top of block data can be written to the buffer and generates the Buffer Write Ready Interrupt.

        ENUMs:
            SPACE:                       There is enough space in the buffer to write BLEN bytes of data
            NOSPACE:                     There is no room left in the buffer to write BLEN bytes of data.
*/
#define SDMMC_PSTATE_BWE                                             0x00000400U
#define SDMMC_PSTATE_BWE_M                                           0x00000400U
#define SDMMC_PSTATE_BWE_S                                           10U
#define SDMMC_PSTATE_BWE_SPACE                                       0x00000400U
#define SDMMC_PSTATE_BWE_NOSPACE                                     0x00000000U
/*

        Field:           BRE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Buffer read enable
                         This bit is used for non-DMA read transfers.
                         This read only flag indicates that valid data exists in the host side buffer status. If this bit is 1, readable data exists in the buffer.
                         A change of this bit from 1 to 0 occurs when all the block data is read from the buffer.
                         A change of this bit from 0 to 1 occurs when all the block data is ready in the buffer and generates the Buffer Read Ready Interrupt.

        ENUMs:
            ENABLE:                      Read BLEN bytes enable. Readable data exists in the buffer.
            DISABLE:                     Read BLEN bytes disable
*/
#define SDMMC_PSTATE_BRE                                             0x00000800U
#define SDMMC_PSTATE_BRE_M                                           0x00000800U
#define SDMMC_PSTATE_BRE_S                                           11U
#define SDMMC_PSTATE_BRE_ENABLE                                      0x00000800U
#define SDMMC_PSTATE_BRE_DISABLE                                     0x00000000U
/*

        Field:           CINS
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Card inserted
                         This bit is the debounced value of the card detect input pin (SDCD).
                         An inactive to active transition of the card detect input pin (SDCD) will generate a card insertion interrupt (SD_STAT.CINS).
                         An active to inactive transition of the card detect input pin (SDCD) will generate a card removal interrupt (SD_STAT.REM).
                         This bit is not affected by a software reset.

        ENUMs:
            CARD:                        Card is detected
                         Note: SD_CON.CDP need to reflect the correct active level of the write protect input signal (SDCD).
            NOCARD:                      No card is detected
                         Note: SD_CON.CDP need to reflect the correct active level of the write protect input signal (SDCD).
*/
#define SDMMC_PSTATE_CINS                                            0x00010000U
#define SDMMC_PSTATE_CINS_M                                          0x00010000U
#define SDMMC_PSTATE_CINS_S                                          16U
#define SDMMC_PSTATE_CINS_CARD                                       0x00010000U
#define SDMMC_PSTATE_CINS_NOCARD                                     0x00000000U
/*

        Field:           CSS
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Card State Stable
                         This bit is used for testing.
                         It is set to 1 only when Card Detect Pin Level is stable (SD_PSTATE.CPDL).
                         Debouncing is performed on the card detect input pin (SDCD) to detect card stability.
                         This bit is not affected by software reset.

        ENUMs:
            STABLE:                      Card detect pin level is stable
            DEBOUNCE:                    Card detect pin level is debouncing
*/
#define SDMMC_PSTATE_CSS                                             0x00020000U
#define SDMMC_PSTATE_CSS_M                                           0x00020000U
#define SDMMC_PSTATE_CSS_S                                           17U
#define SDMMC_PSTATE_CSS_STABLE                                      0x00020000U
#define SDMMC_PSTATE_CSS_DEBOUNCE                                    0x00000000U
/*

        Field:           CDPL
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Card Detect Pin Level
                         This bit reflects the inverse value of the card detect input pin (SDCD).

        ENUMs:
            LOW:                         The value of the card detect input pin (SDCD) is 0
            HIGH:                        The value of the card detect input pin (SDCD) is 1
*/
#define SDMMC_PSTATE_CDPL                                            0x00040000U
#define SDMMC_PSTATE_CDPL_M                                          0x00040000U
#define SDMMC_PSTATE_CDPL_S                                          18U
#define SDMMC_PSTATE_CDPL_LOW                                        0x00040000U
#define SDMMC_PSTATE_CDPL_HIGH                                       0x00000000U
/*

        Field:           WP
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Write Protect
                         This bit reflects the write protect input pin (SDWP) level.

        ENUMs:
            NOPROTECT:                   The card is not write protected
                         Note: SD_CON.WPP need to reflect the correct active setting of the write protect input signal (SDWP).
            PROTECT:                     The card is write protected.
                         Note: SD_CON.WPP need to reflect the correct active setting of the write protect input signal (SDWP).
*/
#define SDMMC_PSTATE_WP                                              0x00080000U
#define SDMMC_PSTATE_WP_M                                            0x00080000U
#define SDMMC_PSTATE_WP_S                                            19U
#define SDMMC_PSTATE_WP_NOPROTECT                                    0x00080000U
#define SDMMC_PSTATE_WP_PROTECT                                      0x00000000U
/*

        Field:           DLEV
        From..to bits:   20...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DATA line 0 to 3 signal level
                         Bit 3 reflects DATA[3] signal level.
                         Bit 2 reflects DATA[2] signal level.
                         Bit 1 reflects DATA[1] signal level.
                         Bit 0 reflects DATA[0] signal level.
                         This status is used to check DAT line level to recover from errors, and for debugging.
                         This is especially useful in detecting the busy signal level from DAT[0].

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_PSTATE_DLEV_W                                          4U
#define SDMMC_PSTATE_DLEV_M                                          0x00F00000U
#define SDMMC_PSTATE_DLEV_S                                          20U
#define SDMMC_PSTATE_DLEV_MINIMUM                                    0x00000000U
#define SDMMC_PSTATE_DLEV_MAXIMUM                                    0x00F00000U
/*

        Field:           CLEV
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command line signal level
                         This status is used to check the CMD line level to recover from errors, and for debugging.

        ENUMs:
            LOW:                         The mmc_cmd line level is 0
            HIGH:                        The mmc_cmd line level is 1
*/
#define SDMMC_PSTATE_CLEV                                            0x01000000U
#define SDMMC_PSTATE_CLEV_M                                          0x01000000U
#define SDMMC_PSTATE_CLEV_S                                          24U
#define SDMMC_PSTATE_CLEV_LOW                                        0x00000000U
#define SDMMC_PSTATE_CLEV_HIGH                                       0x01000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HCTL
    Offset name:         SDMMC_O_HCTL
    Relative address:    0x228
    Description:         Host Control Register

                        This register defines the host controls to set power, wakeup and transfer parameters.

                        SD_HCTL[31:24] = Wakeup control
                        SD_HCTL[23:16] = Block gap control
                        SD_HCTL[15:8] = Power control
                        SD_HCTL[7:0] = Host control

    Default Value:       0x00000000

        Field:           DTW
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data transfer width
                         This bit must be set following a valid SET_BUS_WIDTH command (ACMD6) with the value written in bit 1 of the argument.
                         Prior to this command, the SD card configuration register (SCR) must be verified for the supported bus width by the SD card.

        ENUMs:
            WIDTH_1:                     1-bit Data width (mmc_dat0 used)
            WIDTH_4:                     4-bit Data width (mmc_dat[3:0] used)
*/
#define SDMMC_HCTL_DTW                                               0x00000002U
#define SDMMC_HCTL_DTW_M                                             0x00000002U
#define SDMMC_HCTL_DTW_S                                             1U
#define SDMMC_HCTL_DTW_WIDTH_1                                       0x00000000U
#define SDMMC_HCTL_DTW_WIDTH_4                                       0x00000002U
/*

        Field:           HSPE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     High Speed Enable
                         Before setting this bit, the Host Driver shall check the High Speed Support in the Capabilities register.
                         If this bit is cleared to 0 (default), the Host Controller outputs CMD line and DAT lines at the falling edge of the SD Clock.
                         If this bit is set to 1, the Host Controller outputs CMD line and DAT lines at the rising edge of the SD Clock.

        ENUMs:
            NOMAL:                       Normal speed mode
            HIGH:                        High speed mode
*/
#define SDMMC_HCTL_HSPE                                              0x00000004U
#define SDMMC_HCTL_HSPE_M                                            0x00000004U
#define SDMMC_HCTL_HSPE_S                                            2U
#define SDMMC_HCTL_HSPE_NOMAL                                        0x00000000U
#define SDMMC_HCTL_HSPE_HIGH                                         0x00000004U
/*

        Field:           DMAS
        From..to bits:   3...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA Select Mode
                         Note: This functionality is not is not supported, since MADMA_EN = 0 by design.

        ENUMs:
            MINIMUM:                     Minimum value
            MAX:                         Maximum value
*/
#define SDMMC_HCTL_DMAS_W                                            2U
#define SDMMC_HCTL_DMAS_M                                            0x00000018U
#define SDMMC_HCTL_DMAS_S                                            3U
#define SDMMC_HCTL_DMAS_MINIMUM                                      0x00000000U
#define SDMMC_HCTL_DMAS_MAX                                          0x00000018U
/*

        Field:           CDTL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card Detect Test Level
                         This bit is only functional when the Card Detect Signal Selection selects the Card Detect Test Level mode (SD_HCTL.CDSS = 1).

        ENUMs:
            NOCARD:                      No card
            CARD:                        Card inserted
*/
#define SDMMC_HCTL_CDTL                                              0x00000040U
#define SDMMC_HCTL_CDTL_M                                            0x00000040U
#define SDMMC_HCTL_CDTL_S                                            6U
#define SDMMC_HCTL_CDTL_NOCARD                                       0x00000000U
#define SDMMC_HCTL_CDTL_CARD                                         0x00000040U
/*

        Field:           CDSS
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card Detect Signal Selection
                         This bit selects the source for the card detection.
                         When the source for the card detection is switched, the Card insertion and removal interrupts should be disabled to avoid unexpected interrupts.
                         In Card Detect Test Level mode, the card insertion and removal signal can be controlled by SD_HCTL.CDTL.

        ENUMs:
            SDCD:                        SDCD signal is selected (for normal use)
            TEST:                        The Card Detect Test Level is selected (for test purposes)
*/
#define SDMMC_HCTL_CDSS                                              0x00000080U
#define SDMMC_HCTL_CDSS_M                                            0x00000080U
#define SDMMC_HCTL_CDSS_S                                            7U
#define SDMMC_HCTL_CDSS_SDCD                                         0x00000000U
#define SDMMC_HCTL_CDSS_TEST                                         0x00000080U
/*

        Field:           SDBP
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SD bus power.
                         Before setting this bit, the host driver shall select the SD bus voltage (SD_HCTL[11:9] SDVS bits).
                         If the host controller detects the No card state, this bit is automatically cleared to 0.
                         If the module is power off, a write in the command register (SD_CMD) will not start the transfer.
                         A write to this bit has no effect if the selected SD bus voltage is not supported according to capability register (SD_CAPA[26] VS18 bit, SD_CAPA[25] VS30 bit or SD_CAPA[24] VS33 bit).

        ENUMs:
            OFF:                         Power off
            ON:                          Power on
*/
#define SDMMC_HCTL_SDBP                                              0x00000100U
#define SDMMC_HCTL_SDBP_M                                            0x00000100U
#define SDMMC_HCTL_SDBP_S                                            8U
#define SDMMC_HCTL_SDBP_OFF                                          0x00000000U
#define SDMMC_HCTL_SDBP_ON                                           0x00000100U
/*

        Field:           SDVS
        From..to bits:   9...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SD bus voltage select (All cards).
                         The host driver should set these bits to select the voltage level for the card according to the voltage supported by the system (SD_CAPA[26] VS18 bit, SD_CAPA[25] VS30 bit, SD_CAPA[24] VS33 bit) before starting a transfer.

        ENUMs:
            MID:                         3.0V (Typical)
            LOW:                         1.8V (Typical)
            HIGH:                        3.3V (Typical)
*/
#define SDMMC_HCTL_SDVS_W                                            3U
#define SDMMC_HCTL_SDVS_M                                            0x00000E00U
#define SDMMC_HCTL_SDVS_S                                            9U
#define SDMMC_HCTL_SDVS_MID                                          0x00000C00U
#define SDMMC_HCTL_SDVS_LOW                                          0x00000A00U
#define SDMMC_HCTL_SDVS_HIGH                                         0x00000E00U
/*

        Field:           SBGR
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Stop at block gap request
                         This bit is used to stop executing a transaction at the next block gap.
                         The transfer can restart with a continue request (SD_HCTL.CR) or during a suspend/resume sequence.
                         In case of read transfer, the card must support read wait control.
                         In case of write transfer, the host driver must set this bit after all block data written.
                         Until the transfer completion (SD_STAT.TC bit set to 1), the host driver must leave this bit set to 1. If this bit is set, the local host may not write to the data register (DATA).

        ENUMs:
            TRANS:                       Transfer mode
            STOP:                        Stop at block gap
*/
#define SDMMC_HCTL_SBGR                                              0x00010000U
#define SDMMC_HCTL_SBGR_M                                            0x00010000U
#define SDMMC_HCTL_SBGR_S                                            16U
#define SDMMC_HCTL_SBGR_TRANS                                        0x00000000U
#define SDMMC_HCTL_SBGR_STOP                                         0x00010000U
/*

        Field:           CR
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Continue request
                         This bit is used to restart a transaction that was stopped by requesting a stop at block gap (SD_HCTL[16] SBGR bit).
                         Set this bit to 1 restarts the transfer.
                         The bit is automatically cleared to 0 by the host controller when transfer has restarted, that is, mmc_dat line is active (SD_PSTATE.DLA) or transferring data (SD_PSTATE.WTA).
                         The Stop at block gap request must be disabled (SD_HCTL[16]
                         SBGR bit =0) before setting this bit.

        ENUMs:
            NOEFFECT:                    No effect
            RESTART:                     Transfer restart
*/
#define SDMMC_HCTL_CR                                                0x00020000U
#define SDMMC_HCTL_CR_M                                              0x00020000U
#define SDMMC_HCTL_CR_S                                              17U
#define SDMMC_HCTL_CR_NOEFFECT                                       0x00000000U
#define SDMMC_HCTL_CR_RESTART                                        0x00020000U
/*

        Field:           RWC
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Read wait control
                         The read wait function is optional only for SDIO cards.
                         If the card supports read wait, this bit must be enabled, then requesting a stop at block gap (SD_HCTL.SBGR) generates a read wait period after the current end of block.
                         Note: If read wait is not supported it may cause a conflict on mmc_dat line.

        ENUMs:
            DISABLE:                     Disable read wait control. Suspend/resume cannot be supported
            ENABLE:                      Enable read wait control
*/
#define SDMMC_HCTL_RWC                                               0x00040000U
#define SDMMC_HCTL_RWC_M                                             0x00040000U
#define SDMMC_HCTL_RWC_S                                             18U
#define SDMMC_HCTL_RWC_DISABLE                                       0x00000000U
#define SDMMC_HCTL_RWC_ENABLE                                        0x00040000U
/*

        Field:           IBG
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Interrupt block at gap
                         This bit is valid only in 4-bit mode of SDIO card to enable interrupt detection in the interrupt cycle at block gap for a multiple block transfer.
                         For MMC cards and for SD card this bit should be cleared to 0.

        ENUMs:
            DISABLE:                     Disable interrupt detection at the block gap in 4-bit mode
            ENABLE:                      Enable interrupt detection at the block gap in 4-bit mode
*/
#define SDMMC_HCTL_IBG                                               0x00080000U
#define SDMMC_HCTL_IBG_M                                             0x00080000U
#define SDMMC_HCTL_IBG_S                                             19U
#define SDMMC_HCTL_IBG_DISABLE                                       0x00000000U
#define SDMMC_HCTL_IBG_ENABLE                                        0x00080000U
/*

        Field:           IWE
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Wakeup event enable on SD card interrupt
                         Note: This bit has no effect since the wakeup output is unconnected

        ENUMs:
            MIN:                         Minimum value
            MAX:                         Maximum value
*/
#define SDMMC_HCTL_IWE                                               0x01000000U
#define SDMMC_HCTL_IWE_M                                             0x01000000U
#define SDMMC_HCTL_IWE_S                                             24U
#define SDMMC_HCTL_IWE_MIN                                           0x00000000U
#define SDMMC_HCTL_IWE_MAX                                           0x01000000U
/*

        Field:           INS
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Wakeup event enable on SD card insertion
                         Note: This bit has no effect since the wakeup output is unconnected

        ENUMs:
            MIN:                         Minimum value
            MAX:                         Maximum value
*/
#define SDMMC_HCTL_INS                                               0x02000000U
#define SDMMC_HCTL_INS_M                                             0x02000000U
#define SDMMC_HCTL_INS_S                                             25U
#define SDMMC_HCTL_INS_MIN                                           0x00000000U
#define SDMMC_HCTL_INS_MAX                                           0x02000000U
/*

        Field:           REM
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Wakeup event enable on SD card removal
                         Note: This bit has no effect since the wakeup output is unconnected

        ENUMs:
            MIN:                         Minimum value
            MAX:                         Maximum value
*/
#define SDMMC_HCTL_REM                                               0x04000000U
#define SDMMC_HCTL_REM_M                                             0x04000000U
#define SDMMC_HCTL_REM_S                                             26U
#define SDMMC_HCTL_REM_MIN                                           0x00000000U
#define SDMMC_HCTL_REM_MAX                                           0x04000000U
/*

        Field:           OBWE
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Wakeup event enable for 'Out-of-Band' Interrupt
                         Note: This bit has no effect since the wakeup output is unconnected
                         Note: Out-of-Band Interrupt (OBI) is not supported

        ENUMs:
            MIN:                         Minimum value
            MAX:                         Maximum value
*/
#define SDMMC_HCTL_OBWE                                              0x08000000U
#define SDMMC_HCTL_OBWE_M                                            0x08000000U
#define SDMMC_HCTL_OBWE_S                                            27U
#define SDMMC_HCTL_OBWE_MIN                                          0x00000000U
#define SDMMC_HCTL_OBWE_MAX                                          0x08000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SYSCTL
    Offset name:         SDMMC_O_SYSCTL
    Relative address:    0x22C
    Description:         SD System Control Register

                        This register defines the system controls  clock frequency management and data timeout.

                        SD_SYSCTL[23:16] = Timeout control
                        SD_SYSCTL[15:0] =  Clock control

    Default Value:       0x00000000

        Field:           ICE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Internal clock enable
                         This bit controls the internal clock activity. In very low power state, the internal clock is stopped.
                         Note: The activity of the debounce clock (used for wake-up events) and the interface clock (used for reads and writes to the module register map) are not affected by this register.

        ENUMs:
            STOP:                        The internal clock is stopped (very low power state).
            RUN:                         The internal clock oscillates and can be automatically gated when SD_SYSCONFIG.AUTOIDLE bit is set to 1 (default value).
*/
#define SDMMC_SYSCTL_ICE                                             0x00000001U
#define SDMMC_SYSCTL_ICE_M                                           0x00000001U
#define SDMMC_SYSCTL_ICE_S                                           0U
#define SDMMC_SYSCTL_ICE_STOP                                        0x00000000U
#define SDMMC_SYSCTL_ICE_RUN                                         0x00000001U
/*

        Field:           ICS
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Internal clock stable (status)
                         This bit indicates that the internal clock is stable

        ENUMs:
            NOSTAB:                      The internal clock is not stable
            STAB:                        The internal clock is stable after enabling the clock (SD_SYSCTL.ICEN) or after changing the clock ratio (SD_SYSCTL.CLKD).
*/
#define SDMMC_SYSCTL_ICS                                             0x00000002U
#define SDMMC_SYSCTL_ICS_M                                           0x00000002U
#define SDMMC_SYSCTL_ICS_S                                           1U
#define SDMMC_SYSCTL_ICS_NOSTAB                                      0x00000000U
#define SDMMC_SYSCTL_ICS_STAB                                        0x00000002U
/*

        Field:           CEN
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card clock enable
                         This bit controls the clock to the card.

        ENUMs:
            OFF:                         The clock is not provided to the card . Clock frequency can be changed.
            ON:                          The clock is provided to the card and can be automatically gated when SD_SYSCONFIG.AUTOIDLE bit is set to 1 (default value). The host driver must wait to set this bit to 1 until the internal clock is stable (SYSSTAT.ICS).
*/
#define SDMMC_SYSCTL_CEN                                             0x00000004U
#define SDMMC_SYSCTL_CEN_M                                           0x00000004U
#define SDMMC_SYSCTL_CEN_S                                           2U
#define SDMMC_SYSCTL_CEN_OFF                                         0x00000000U
#define SDMMC_SYSCTL_CEN_ON                                          0x00000004U
/*

        Field:           CLKD
        From..to bits:   6...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clock frequency select
                         This bitfield defines the ratio between a reference clock frequency (system dependent) and the output clock frequency on the mmc_clk pin of the memory card (MMC, SD, or SDIO).
                         0h = Clock Ref bypass
                         1h = Clock Ref bypass
                         2h = Clock Ref / 2
                         3h = Clock Ref / 3
                         3FFh = Clock Ref / 1023

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_SYSCTL_CLKD_W                                          10U
#define SDMMC_SYSCTL_CLKD_M                                          0x0000FFC0U
#define SDMMC_SYSCTL_CLKD_S                                          6U
#define SDMMC_SYSCTL_CLKD_MINIMUM                                    0x00000000U
#define SDMMC_SYSCTL_CLKD_MAXIMUM                                    0x0000FFC0U
/*

        Field:           DTO
        From..to bits:   16...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data timeout counter value and busy timeout
                         This value determines the interval to detect mmc_dat lines timeouts.
                         The host driver needs to set this bitfield based on:
                         - the maximum read access time (NAC) (Refer to the SD Specification Part1 Physical Layer)
                         - the data read access time values (TAAC and NSAC) in the card specific data register (CSD) of the card
                         - the timeout clock base frequency (SD_CAPA.TCF)
                         If the card does not respond within the specified number of cycles, a data timeout error occurs (SD_STAT.DTO).
                         The Data timeout counter can also be used to check busy duration, to generate busy timeout for commands with busy response or for busy programming during a write command.
                         Timeout on CRC status is generated if no CRC token is present after a block write.
                         0h = TCF x 2^13
                         1h = TCF x 2^14
                         Eh = TCF x 2^27
                         Fh = Reserved

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_SYSCTL_DTO_W                                           4U
#define SDMMC_SYSCTL_DTO_M                                           0x000F0000U
#define SDMMC_SYSCTL_DTO_S                                           16U
#define SDMMC_SYSCTL_DTO_MINIMUM                                     0x00000000U
#define SDMMC_SYSCTL_DTO_MAXIMUM                                     0x000E0000U
/*

        Field:           SRA
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Software reset for all
                         This bit is set to 1 for reset, and released to 0 when completed.
                         Note: This subreset should not to be used by software, as it can lead to unexpected side-effects. Reset of the SDMMC module should always be through GPRCM.RSTCTL.RESETASSERT

        ENUMs:
            COMPL:                       Reset completed
            ASSERT:                      Reset asserted
*/
#define SDMMC_SYSCTL_SRA                                             0x01000000U
#define SDMMC_SYSCTL_SRA_M                                           0x01000000U
#define SDMMC_SYSCTL_SRA_S                                           24U
#define SDMMC_SYSCTL_SRA_COMPL                                       0x00000000U
#define SDMMC_SYSCTL_SRA_ASSERT                                      0x01000000U
/*

        Field:           SRC
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Software reset for mmc_cmd line
                         This bit is set to 1 for reset and released to 0 when completed.
                         Note: This subreset should not to be used by software, as it can lead to unexpected side-effects. Reset of the SDMMC module should always be through GPRCM.RSTCTL.RESETASSERT

        ENUMs:
            COMPL:                       Reset completed
            ASSERT:                      Reset asserted
*/
#define SDMMC_SYSCTL_SRC                                             0x02000000U
#define SDMMC_SYSCTL_SRC_M                                           0x02000000U
#define SDMMC_SYSCTL_SRC_S                                           25U
#define SDMMC_SYSCTL_SRC_COMPL                                       0x00000000U
#define SDMMC_SYSCTL_SRC_ASSERT                                      0x02000000U
/*

        Field:           SRD
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Software reset for mmc_dat line
                         This bit is set to 1 for reset and released to 0 when completed.
                         Note: This subreset should not to be used by software, as it can lead to unexpected side-effects. Reset of the SDMMC module should always be through GPRCM.RSTCTL.RESETASSERT

        ENUMs:
            COMPL:                       Reset completed
            ASSERT:                      Reset asserted
*/
#define SDMMC_SYSCTL_SRD                                             0x04000000U
#define SDMMC_SYSCTL_SRD_M                                           0x04000000U
#define SDMMC_SYSCTL_SRD_S                                           26U
#define SDMMC_SYSCTL_SRD_COMPL                                       0x00000000U
#define SDMMC_SYSCTL_SRD_ASSERT                                      0x04000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STAT
    Offset name:         SDMMC_O_STAT
    Relative address:    0x230
    Description:         The interrupt status regroups all the status of the module internal events that can generate an interrupt.
                        SD_STAT[31:16] = Error Interrupt Status
                        SD_STAT[15:0] = Normal Interrupt Status

                        The error bits are located in the upper 16 bits of the SD_STAT register. All bits are cleared by writing a 1 to them.
                        Additionally, bits 15 and 8 serve as special error bits. These cannot be cleared by writing a 1 to them. Bit 15 (ERRI) is automatically cleared when the error causing to ERRI to be set is handled. (that is, when bits 31:16 are cleared, bit 15 will be automatically cleared). Bit 8 (CIRQ) is cleared by writing a 0 to SD_IE[8] (masking the interrupt) and servicing the interrupt.
    Default Value:       0x00000000

        Field:           CC
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command complete.
                         This bit is set when a 1-to-0 transition occurs in the register command inhibit (SD_PSTATE[0] CMDI bit)
                         0h (W) = Status bit unchanged
                         0h (R) = No command complete
                         1h (W) = Status is cleared
                         1h (R) = Command complete

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_CC                                                0x00000001U
#define SDMMC_STAT_CC_M                                              0x00000001U
#define SDMMC_STAT_CC_S                                              0U
#define SDMMC_STAT_CC_NOINT                                          0x00000000U
#define SDMMC_STAT_CC_INT                                            0x00000001U
/*

        Field:           TC
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transfer completed.
                         This bit is always set when a read/write transfer is completed or between two blocks when the transfer is stopped due to a stop at block gap request (SD_HCTL[16] SBGR bit).
                         0h (W) = Status bit unchanged
                         0h (R) = No transfer complete
                         1h (W) = Status is cleared
                         1h (R) = Data transfer complete

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_TC                                                0x00000002U
#define SDMMC_STAT_TC_M                                              0x00000002U
#define SDMMC_STAT_TC_S                                              1U
#define SDMMC_STAT_TC_NOINT                                          0x00000000U
#define SDMMC_STAT_TC_INT                                            0x00000002U
/*

        Field:           BGE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Block gap event.
                         When a stop at block gap is requested (SD_HCTL[16] SBGR bit), this bit is automatically set when transaction is stopped at the block gap during a read or write operation.
                         0h (W) = Status bit unchanged
                         0h (R) = No block gap event
                         1h (W) = Status is cleared
                         1h (R) = Transaction stopped at block gap

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_BGE                                               0x00000004U
#define SDMMC_STAT_BGE_M                                             0x00000004U
#define SDMMC_STAT_BGE_S                                             2U
#define SDMMC_STAT_BGE_NOINT                                         0x00000000U
#define SDMMC_STAT_BGE_INT                                           0x00000004U
/*

        Field:           DMA
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA Interrupt
                         This status is set when an interrupt is required after the data transfer is complete.

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_DMA                                               0x00000008U
#define SDMMC_STAT_DMA_M                                             0x00000008U
#define SDMMC_STAT_DMA_S                                             3U
#define SDMMC_STAT_DMA_NOINT                                         0x00000000U
#define SDMMC_STAT_DMA_INT                                           0x00000008U
/*

        Field:           BWR
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Buffer write ready.
                         This bit is set automatically during a write operation to the card (see class 4 - block oriented write command) when the host can write a complete block as specified by SD_BLK [10:0] BLEN.
                         It indicates that the memory card has emptied one block from the buffer and that the local host is able to write one block of data into the buffer.
                         Note: If the DMA transmit mode is enabled, this bit is never set instead, a DMA transmit request to the main DMA controller of the system is generated.
                         0h (W) = Status bit unchanged
                         0h (R) = Not ready to write buffer
                         1h (W) = Status is cleared.
                         1h (R) = Ready to write buffer

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_BWR                                               0x00000010U
#define SDMMC_STAT_BWR_M                                             0x00000010U
#define SDMMC_STAT_BWR_S                                             4U
#define SDMMC_STAT_BWR_NOINT                                         0x00000000U
#define SDMMC_STAT_BWR_INT                                           0x00000010U
/*

        Field:           BRR
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Buffer read ready.
                         This bit is set automatically during a read operation to the card (see class 2 - block oriented read commands) when one block specified by the SD_BLK [10:0] BLEN bit field is completely written in the buffer.
                         It indicates that the memory card has filled out the buffer and that the local host needs to empty the buffer by reading it.
                         Note: If the DMA receive-mode is enabled, this bit is never set instead a DMA receive request to the main DMA controller of the system is generated.
                         0h (W) = Status bit unchanged
                         0h (R) = Not ready to read buffer
                         1h (W) = Status is cleared.
                         1h (R) = Ready to read buffer

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_BRR                                               0x00000020U
#define SDMMC_STAT_BRR_M                                             0x00000020U
#define SDMMC_STAT_BRR_S                                             5U
#define SDMMC_STAT_BRR_NOINT                                         0x00000000U
#define SDMMC_STAT_BRR_INT                                           0x00000020U
/*

        Field:           CINS
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card Insertion.
                         This bit is set automatically when SD_PSTATE[CINS] changes from 0 to 1.
                         A clear of this bit doesn't affect Card inserted present state (SD_PSTATE[CINS]).
                         0h (W) = Status bit unchanged
                         0h (R) = Card State stable or debouncing
                         1h (W) = Status is cleared.
                         1h (R) = Card inserted

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_CINS                                              0x00000040U
#define SDMMC_STAT_CINS_M                                            0x00000040U
#define SDMMC_STAT_CINS_S                                            6U
#define SDMMC_STAT_CINS_NOINT                                        0x00000000U
#define SDMMC_STAT_CINS_INT                                          0x00000040U
/*

        Field:           CREM
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card Removal.
                         This bit is set automatically when SD_PSTATE[CINS] changes from 1 to 0.
                         A clear of this bit doesn't affect Card inserted present state (SD_PSTATE[CINS]).
                         0h (W) = Status bit unchanged
                         0h (R) = Card State stable or debouncing
                         1h (W) = Status is cleared
                         1h (R) = Card Removed

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_CREM                                              0x00000080U
#define SDMMC_STAT_CREM_M                                            0x00000080U
#define SDMMC_STAT_CREM_S                                            7U
#define SDMMC_STAT_CREM_NOINT                                        0x00000000U
#define SDMMC_STAT_CREM_INT                                          0x00000080U
/*

        Field:           CIRQ
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Card interrupt.
                         This bit is only used for SD and SDIO cards.
                         In 1-bit mode, interrupt source is asynchronous (can be a source of asynchronous wake-up).
                         In 4-bit mode, interrupt source is sampled during the interrupt cycle.
                         In CE-ATA mode, interrupt source is detected when the card drives mmc_cmd line to zero during one cycle after data transmission end.
                         All modes above are fully exclusive.
                         The controller interrupt must be clear by setting SD_IE[8] CIRQ_ENABLE to 0, then the host driver must start the interrupt service with card (clearing card interrupt status) to remove card interrupt source.
                         Otherwise the Controller interrupt will be reasserted as soon as SD_IE[8] CIRQ_ENABLE is set to 1.
                         Writes to this bit are ignored.
                         0h (R) = No card interrupt
                         1h (R) = Generate card interrupt

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_CIRQ                                              0x00000100U
#define SDMMC_STAT_CIRQ_M                                            0x00000100U
#define SDMMC_STAT_CIRQ_S                                            8U
#define SDMMC_STAT_CIRQ_NOINT                                        0x00000000U
#define SDMMC_STAT_CIRQ_INT                                          0x00000100U
/*

        Field:           OBI
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Out-of-band interrupt (This interrupt is only useful for MMC card).
                         Note: Out-of-band interrupt (OBI) is not supported.


        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_OBI                                               0x00000200U
#define SDMMC_STAT_OBI_M                                             0x00000200U
#define SDMMC_STAT_OBI_S                                             9U
#define SDMMC_STAT_OBI_NOINT                                         0x00000000U
#define SDMMC_STAT_OBI_INT                                           0x00000200U
/*

        Field:           ERRI
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Error interrupt.
                         If any of the bits in the Error Interrupt Status register (SD_STAT [31:16]) are set, then this bit is set to 1.
                         Therefore the host driver can efficiently test for an error by checking this bit first.
                         Writes to this bit are ignored.
                         0h (R) = No interrupt
                         1h (R) = Error interrupt event(s) occurred

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_ERRI                                              0x00008000U
#define SDMMC_STAT_ERRI_M                                            0x00008000U
#define SDMMC_STAT_ERRI_S                                            15U
#define SDMMC_STAT_ERRI_NOINT                                        0x00000000U
#define SDMMC_STAT_ERRI_INT                                          0x00008000U
/*

        Field:           CTO
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command timeout error.
                         This bit is set automatically when no response is received within 64 clock cycles from the end bit of the command.
                         For commands that reply within 5 clock cycles - the timeout is still detected at 64 clock cycles.
                         0h (W) = Status bit unchanged
                         0h (R) = No error
                         1h (W) = Status is cleared.
                         1h (R) = Time Out

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_CTO                                               0x00010000U
#define SDMMC_STAT_CTO_M                                             0x00010000U
#define SDMMC_STAT_CTO_S                                             16U
#define SDMMC_STAT_CTO_NOINT                                         0x00000000U
#define SDMMC_STAT_CTO_INT                                           0x00010000U
/*

        Field:           CCRC
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command CRC error.
                         This bit is set automatically when there is a CRC7 error in the command response depending on the enable bit (SD_CMD[19] CCCE).
                         0h (W) = Status bit unchanged
                         0h (R) = No error
                         1h (W) = Status is cleared.
                         1h (R) = Command CRC error

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_CCRC                                              0x00020000U
#define SDMMC_STAT_CCRC_M                                            0x00020000U
#define SDMMC_STAT_CCRC_S                                            17U
#define SDMMC_STAT_CCRC_NOINT                                        0x00000000U
#define SDMMC_STAT_CCRC_INT                                          0x00020000U
/*

        Field:           CEB
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command end bit error.
                         This bit is set automatically when detecting a 0 at the end bit position of a command response.
                         0h (W) = Status bit unchanged
                         0h (R) = No error
                         1h (W) = Status is cleared.
                         1h (R) = Command end bit error

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_CEB                                               0x00040000U
#define SDMMC_STAT_CEB_M                                             0x00040000U
#define SDMMC_STAT_CEB_S                                             18U
#define SDMMC_STAT_CEB_NOINT                                         0x00000000U
#define SDMMC_STAT_CEB_INT                                           0x00040000U
/*

        Field:           CIE
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command index error.
                         This bit is set automatically when response index differs from corresponding command index previously emitted.
                         It depends on the enable bit (SD_CMD[20] CICE).
                         0h (W) = Status bit unchanged
                         0h (R) = No error
                         1h (W) = Status is cleared.
                         1h (R) = Command index error

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_CIE                                               0x00080000U
#define SDMMC_STAT_CIE_M                                             0x00080000U
#define SDMMC_STAT_CIE_S                                             19U
#define SDMMC_STAT_CIE_NOINT                                         0x00000000U
#define SDMMC_STAT_CIE_INT                                           0x00080000U
/*

        Field:           DTO
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data timeout error.
                         This bit is set automatically according to the following conditions:
                         Busy timeout for R1b, R5b response type.
                         Busy timeout after write CRC status.
                         Write CRC status timeout.
                         Read data timeout.
                         0h (W) = Status bit unchanged
                         0h (R) = No error
                         1h (W) = Status is cleared.
                         1h (R) = Time out

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_DTO                                               0x00100000U
#define SDMMC_STAT_DTO_M                                             0x00100000U
#define SDMMC_STAT_DTO_S                                             20U
#define SDMMC_STAT_DTO_NOINT                                         0x00000000U
#define SDMMC_STAT_DTO_INT                                           0x00100000U
/*

        Field:           DCRC
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data CRC Error.
                         This bit is set automatically when there is a CRC16 error in the data phase response following a block read command or if there is a 3-bit CRC status different of a position "010" token during a block write command.
                         0h (W) = Status bit unchanged
                         0h (R) = No error
                         1h (W) = Status is cleared.
                         1h (R) = Data CRC error

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_DCRC                                              0x00200000U
#define SDMMC_STAT_DCRC_M                                            0x00200000U
#define SDMMC_STAT_DCRC_S                                            21U
#define SDMMC_STAT_DCRC_NOINT                                        0x00000000U
#define SDMMC_STAT_DCRC_INT                                          0x00200000U
/*

        Field:           DEB
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data End Bit error.
                         This bit is set automatically when detecting a 0 at the end bit position of read data on mmc_dat line or at the end position of the CRC status in write mode.
                         0h (W) = Status bit unchanged
                         0h (R) = No error
                         1h (W) = Status is cleared.
                         1h (R) = Data end bit error

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_DEB                                               0x00400000U
#define SDMMC_STAT_DEB_M                                             0x00400000U
#define SDMMC_STAT_DEB_S                                             22U
#define SDMMC_STAT_DEB_NOINT                                         0x00000000U
#define SDMMC_STAT_DEB_INT                                           0x00400000U
/*

        Field:           ACE
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Auto CMD12 error.
                         This bit is set automatically when one of the bits in Auto CMD12 Error status register has changed from 0 to 1.
                         0h (W) = Status bit unchanged
                         0h (R) = No error
                         1h (W) = Status is cleared.
                         1h (R) = AutoCMD12 error

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_ACE                                               0x01000000U
#define SDMMC_STAT_ACE_M                                             0x01000000U
#define SDMMC_STAT_ACE_S                                             24U
#define SDMMC_STAT_ACE_NOINT                                         0x00000000U
#define SDMMC_STAT_ACE_INT                                           0x01000000U
/*

        Field:           CERR
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card error.
                         This bit is set automatically when there is at least one error in a response of type R1, R1b, R6, R5 or R5b.
                         Only bits referenced as type E (error) in status field in the response can set a card status error.
                         An error bit in the response is flagged only if corresponding bit in card status response error SD_CSRE in set.
                         There is no card error detection for autoCMD12 command.
                         The host driver shall read SD_RSP76 register to detect error bits in the command response.
                         0h (W) = Status bit unchanged
                         0h (R) = No error
                         1h (W) = Status is cleared.
                         1h (R) = Card error

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_CERR                                              0x10000000U
#define SDMMC_STAT_CERR_M                                            0x10000000U
#define SDMMC_STAT_CERR_S                                            28U
#define SDMMC_STAT_CERR_NOINT                                        0x00000000U
#define SDMMC_STAT_CERR_INT                                          0x10000000U
/*

        Field:           BADA
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Bad access to data space.
                         This bit is set automatically to indicate a bad access to buffer when not allowed: During a read access to the data register (SD_DATA) while buffer reads are not allowed (SD_PSTATE[11] BRE bit =0).
                         During a write access to the data register (SD_DATA) while buffer writes are not allowed (SD_PSTATE[10] BWE bit=0).
                         0h (W) = Status bit unchanged
                         0h (R) = No interrupt
                         1h (W) = Status is cleared.
                         1h (R) = Bad access

        ENUMs:
            NOINT:                       No interrupt occured
            INT:                         Interrupt occured
*/
#define SDMMC_STAT_BADA                                              0x20000000U
#define SDMMC_STAT_BADA_M                                            0x20000000U
#define SDMMC_STAT_BADA_S                                            29U
#define SDMMC_STAT_BADA_NOINT                                        0x00000000U
#define SDMMC_STAT_BADA_INT                                          0x20000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IE
    Offset name:         SDMMC_O_IE
    Relative address:    0x234
    Description:         This register allows to enable/disable the module to set status bits on an event-by-event basis.
                        SD_IE[31:16] = Error Interrupt Status Enable
                        SD_IE[15:0] = Normal Interrupt Status Enable
    Default Value:       0x00000000

        Field:           CCEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command completed interrupt enable

        ENUMs:
            MSK:                         Interrupt masked
            ENABLE:                      Interrupt enabled
*/
#define SDMMC_IE_CCEN                                                0x00000001U
#define SDMMC_IE_CCEN_M                                              0x00000001U
#define SDMMC_IE_CCEN_S                                              0U
#define SDMMC_IE_CCEN_MSK                                            0x00000000U
#define SDMMC_IE_CCEN_ENABLE                                         0x00000001U
/*

        Field:           TCEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transfer completed interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_TCEN                                                0x00000002U
#define SDMMC_IE_TCEN_M                                              0x00000002U
#define SDMMC_IE_TCEN_S                                              1U
#define SDMMC_IE_TCEN_ENABLE                                         0x00000002U
#define SDMMC_IE_TCEN_MSK                                            0x00000000U
/*

        Field:           BGEEN
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Block gap event interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_BGEEN                                               0x00000004U
#define SDMMC_IE_BGEEN_M                                             0x00000004U
#define SDMMC_IE_BGEEN_S                                             2U
#define SDMMC_IE_BGEEN_ENABLE                                        0x00000004U
#define SDMMC_IE_BGEEN_MSK                                           0x00000000U
/*

        Field:           DMAEN
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_DMAEN                                               0x00000008U
#define SDMMC_IE_DMAEN_M                                             0x00000008U
#define SDMMC_IE_DMAEN_S                                             3U
#define SDMMC_IE_DMAEN_ENABLE                                        0x00000008U
#define SDMMC_IE_DMAEN_MSK                                           0x00000000U
/*

        Field:           BWREN
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Buffer write ready interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_BWREN                                               0x00000010U
#define SDMMC_IE_BWREN_M                                             0x00000010U
#define SDMMC_IE_BWREN_S                                             4U
#define SDMMC_IE_BWREN_ENABLE                                        0x00000010U
#define SDMMC_IE_BWREN_MSK                                           0x00000000U
/*

        Field:           BRREN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Buffer read ready interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_BRREN                                               0x00000020U
#define SDMMC_IE_BRREN_M                                             0x00000020U
#define SDMMC_IE_BRREN_S                                             5U
#define SDMMC_IE_BRREN_ENABLE                                        0x00000020U
#define SDMMC_IE_BRREN_MSK                                           0x00000000U
/*

        Field:           CINSEN
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card Insertion interrupt Enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_CINSEN                                              0x00000040U
#define SDMMC_IE_CINSEN_M                                            0x00000040U
#define SDMMC_IE_CINSEN_S                                            6U
#define SDMMC_IE_CINSEN_ENABLE                                       0x00000040U
#define SDMMC_IE_CINSEN_MSK                                          0x00000000U
/*

        Field:           CREMEN
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card Removal interrupt Enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_CREMEN                                              0x00000080U
#define SDMMC_IE_CREMEN_M                                            0x00000080U
#define SDMMC_IE_CREMEN_S                                            7U
#define SDMMC_IE_CREMEN_ENABLE                                       0x00000080U
#define SDMMC_IE_CREMEN_MSK                                          0x00000000U
/*

        Field:           CIRQEN
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card interrupt enable.
                         A clear of this bit also clears the corresponding status bit.
                         During 1-bit mode, if the interrupt routine does not remove the source of a card interrupt in the SDIO card, the status bit is reasserted when this bit is set to 1.

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_CIRQEN                                              0x00000100U
#define SDMMC_IE_CIRQEN_M                                            0x00000100U
#define SDMMC_IE_CIRQEN_S                                            8U
#define SDMMC_IE_CIRQEN_ENABLE                                       0x00000100U
#define SDMMC_IE_CIRQEN_MSK                                          0x00000000U
/*

        Field:           OBIEN
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Out-of-band interrupt enable
                         A write to this register when SD_CON[14] OBIE is cleared to 0 is ignored.
                         Note: The OBI functionallity is not supported!

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_OBIEN                                               0x00000200U
#define SDMMC_IE_OBIEN_M                                             0x00000200U
#define SDMMC_IE_OBIEN_S                                             9U
#define SDMMC_IE_OBIEN_ENABLE                                        0x00000200U
#define SDMMC_IE_OBIEN_MSK                                           0x00000000U
/*

        Field:           NOUSE0
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     No use
                         Note: Writing values other than 0 might produce undesired results.
                         Always set this bits to 0.

        ENUMs:
            MIN:                         Minimum value
            MAX:                         Maximum value
*/
#define SDMMC_IE_NOUSE0                                              0x00000400U
#define SDMMC_IE_NOUSE0_M                                            0x00000400U
#define SDMMC_IE_NOUSE0_S                                            10U
#define SDMMC_IE_NOUSE0_MIN                                          0x00000000U
#define SDMMC_IE_NOUSE0_MAX                                          0x00000400U
/*

        Field:           NULL
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Fixed to 0.
                         The host driver shall control error interrupts using the Error Interrupt Signal Enable register.
                         Writes to this bit are ignored.

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_NULL                                                0x00008000U
#define SDMMC_IE_NULL_M                                              0x00008000U
#define SDMMC_IE_NULL_S                                              15U
#define SDMMC_IE_NULL_ENABLE                                         0x00008000U
#define SDMMC_IE_NULL_MSK                                            0x00000000U
/*

        Field:           CTOEN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command timeout error interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_CTOEN                                               0x00010000U
#define SDMMC_IE_CTOEN_M                                             0x00010000U
#define SDMMC_IE_CTOEN_S                                             16U
#define SDMMC_IE_CTOEN_ENABLE                                        0x00010000U
#define SDMMC_IE_CTOEN_MSK                                           0x00000000U
/*

        Field:           CCRCEN
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command CRC error interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_CCRCEN                                              0x00020000U
#define SDMMC_IE_CCRCEN_M                                            0x00020000U
#define SDMMC_IE_CCRCEN_S                                            17U
#define SDMMC_IE_CCRCEN_ENABLE                                       0x00020000U
#define SDMMC_IE_CCRCEN_MSK                                          0x00000000U
/*

        Field:           CEBEN
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command end bit error interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_CEBEN                                               0x00040000U
#define SDMMC_IE_CEBEN_M                                             0x00040000U
#define SDMMC_IE_CEBEN_S                                             18U
#define SDMMC_IE_CEBEN_ENABLE                                        0x00040000U
#define SDMMC_IE_CEBEN_MSK                                           0x00000000U
/*

        Field:           CIEEN
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command index error interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_CIEEN                                               0x00080000U
#define SDMMC_IE_CIEEN_M                                             0x00080000U
#define SDMMC_IE_CIEEN_S                                             19U
#define SDMMC_IE_CIEEN_ENABLE                                        0x00080000U
#define SDMMC_IE_CIEEN_MSK                                           0x00000000U
/*

        Field:           DTOEN
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data timeout error interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_DTOEN                                               0x00100000U
#define SDMMC_IE_DTOEN_M                                             0x00100000U
#define SDMMC_IE_DTOEN_S                                             20U
#define SDMMC_IE_DTOEN_ENABLE                                        0x00100000U
#define SDMMC_IE_DTOEN_MSK                                           0x00000000U
/*

        Field:           DCRCEN
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data CRC error interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_DCRCEN                                              0x00200000U
#define SDMMC_IE_DCRCEN_M                                            0x00200000U
#define SDMMC_IE_DCRCEN_S                                            21U
#define SDMMC_IE_DCRCEN_ENABLE                                       0x00200000U
#define SDMMC_IE_DCRCEN_MSK                                          0x00000000U
/*

        Field:           DEBEN
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data end bit error interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_DEBEN                                               0x00400000U
#define SDMMC_IE_DEBEN_M                                             0x00400000U
#define SDMMC_IE_DEBEN_S                                             22U
#define SDMMC_IE_DEBEN_ENABLE                                        0x00400000U
#define SDMMC_IE_DEBEN_MSK                                           0x00000000U
/*

        Field:           ACEEN
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Auto CMD12 error interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_ACEEN                                               0x01000000U
#define SDMMC_IE_ACEEN_M                                             0x01000000U
#define SDMMC_IE_ACEEN_S                                             24U
#define SDMMC_IE_ACEEN_ENABLE                                        0x01000000U
#define SDMMC_IE_ACEEN_MSK                                           0x00000000U
/*

        Field:           ADMAEEN
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ADMA Error Status Enable
                         Note: This functionality is not supported, since MADMA_EN is set to 0 in the design.

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_ADMAEEN                                             0x02000000U
#define SDMMC_IE_ADMAEEN_M                                           0x02000000U
#define SDMMC_IE_ADMAEEN_S                                           25U
#define SDMMC_IE_ADMAEEN_ENABLE                                      0x02000000U
#define SDMMC_IE_ADMAEEN_MSK                                         0x00000000U
/*

        Field:           NOUSE1
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     No use
                         Note: Writing values other than 0 might produce undesired results.
                         Always set this bits to 0.

        ENUMs:
            MIN:                         Minimum value
            MAX:                         Maximum value
*/
#define SDMMC_IE_NOUSE1                                              0x04000000U
#define SDMMC_IE_NOUSE1_M                                            0x04000000U
#define SDMMC_IE_NOUSE1_S                                            26U
#define SDMMC_IE_NOUSE1_MIN                                          0x00000000U
#define SDMMC_IE_NOUSE1_MAX                                          0x04000000U
/*

        Field:           CERREN
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card error interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_CERREN                                              0x10000000U
#define SDMMC_IE_CERREN_M                                            0x10000000U
#define SDMMC_IE_CERREN_S                                            28U
#define SDMMC_IE_CERREN_ENABLE                                       0x10000000U
#define SDMMC_IE_CERREN_MSK                                          0x00000000U
/*

        Field:           BADAEN
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Bad access to data space interrupt enable

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_IE_BADAEN                                              0x20000000U
#define SDMMC_IE_BADAEN_M                                            0x20000000U
#define SDMMC_IE_BADAEN_S                                            29U
#define SDMMC_IE_BADAEN_ENABLE                                       0x20000000U
#define SDMMC_IE_BADAEN_MSK                                          0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ISE
    Offset name:         SDMMC_O_ISE
    Relative address:    0x238
    Description:         This register allows to enable/disable the module internal interrupt signaling on an event-by-event basis.
                        SD_ISE[31:16] = Error Interrupt Signal Enable
                        SD_ISE[15:0] = Normal Interrupt Signal Enable
    Default Value:       0x00000000

        Field:           CCSEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command completed signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_CCSEN                                              0x00000001U
#define SDMMC_ISE_CCSEN_M                                            0x00000001U
#define SDMMC_ISE_CCSEN_S                                            0U
#define SDMMC_ISE_CCSEN_DISABLE                                      0x00000000U
#define SDMMC_ISE_CCSEN_ENABLE                                       0x00000001U
/*

        Field:           TCSEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transfer completed signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_TCSEN                                              0x00000002U
#define SDMMC_ISE_TCSEN_M                                            0x00000002U
#define SDMMC_ISE_TCSEN_S                                            1U
#define SDMMC_ISE_TCSEN_DISABLE                                      0x00000000U
#define SDMMC_ISE_TCSEN_ENABLE                                       0x00000002U
/*

        Field:           BGESEN
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Block gap event signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_BGESEN                                             0x00000004U
#define SDMMC_ISE_BGESEN_M                                           0x00000004U
#define SDMMC_ISE_BGESEN_S                                           2U
#define SDMMC_ISE_BGESEN_DISABLE                                     0x00000000U
#define SDMMC_ISE_BGESEN_ENABLE                                      0x00000004U
/*

        Field:           DMASEN
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_DMASEN                                             0x00000008U
#define SDMMC_ISE_DMASEN_M                                           0x00000008U
#define SDMMC_ISE_DMASEN_S                                           3U
#define SDMMC_ISE_DMASEN_DISABLE                                     0x00000000U
#define SDMMC_ISE_DMASEN_ENABLE                                      0x00000008U
/*

        Field:           BWRSEN
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Buffer write ready signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_BWRSEN                                             0x00000010U
#define SDMMC_ISE_BWRSEN_M                                           0x00000010U
#define SDMMC_ISE_BWRSEN_S                                           4U
#define SDMMC_ISE_BWRSEN_DISABLE                                     0x00000000U
#define SDMMC_ISE_BWRSEN_ENABLE                                      0x00000010U
/*

        Field:           BRRSEN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Buffer read ready signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_BRRSEN                                             0x00000020U
#define SDMMC_ISE_BRRSEN_M                                           0x00000020U
#define SDMMC_ISE_BRRSEN_S                                           5U
#define SDMMC_ISE_BRRSEN_DISABLE                                     0x00000000U
#define SDMMC_ISE_BRRSEN_ENABLE                                      0x00000020U
/*

        Field:           CINSSEN
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card Insertion signal status enable.

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_CINSSEN                                            0x00000040U
#define SDMMC_ISE_CINSSEN_M                                          0x00000040U
#define SDMMC_ISE_CINSSEN_S                                          6U
#define SDMMC_ISE_CINSSEN_DISABLE                                    0x00000000U
#define SDMMC_ISE_CINSSEN_ENABLE                                     0x00000040U
/*

        Field:           CREMSEN
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card Removal signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_CREMSEN                                            0x00000080U
#define SDMMC_ISE_CREMSEN_M                                          0x00000080U
#define SDMMC_ISE_CREMSEN_S                                          7U
#define SDMMC_ISE_CREMSEN_DISABLE                                    0x00000000U
#define SDMMC_ISE_CREMSEN_ENABLE                                     0x00000080U
/*

        Field:           CIRQSEN
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card interrupt signal status enable.
                         A clear of this bit also clears the corresponding status bit.
                         During 1-bit mode, if the interrupt routine does not remove the source of a card interrupt in the SDIO card, the status bit is reasserted when this bit is set to 1.

        ENUMs:
            ENABLE:                      Status Interrupt signaling enabled
            DISABLE:                     Status Interrupt signaling disabled
*/
#define SDMMC_ISE_CIRQSEN                                            0x00000100U
#define SDMMC_ISE_CIRQSEN_M                                          0x00000100U
#define SDMMC_ISE_CIRQSEN_S                                          8U
#define SDMMC_ISE_CIRQSEN_ENABLE                                     0x00000100U
#define SDMMC_ISE_CIRQSEN_DISABLE                                    0x00000000U
/*

        Field:           OBISEN
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Out-of-band interrupt signal status enable.
                         A write to this register when SD_CON[14] OBIE is cleared to 0 is ignored.
                         Note: The OBI functionallity is not supported!

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_OBISEN                                             0x00000200U
#define SDMMC_ISE_OBISEN_M                                           0x00000200U
#define SDMMC_ISE_OBISEN_S                                           9U
#define SDMMC_ISE_OBISEN_DISABLE                                     0x00000000U
#define SDMMC_ISE_OBISEN_ENABLE                                      0x00000200U
/*

        Field:           NOUSE0
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     No use
                         Note: Writing values other than 0 might produce undesired results.
                         Always set this bit to 0.

        ENUMs:
            LOW:                         Always set this bit to 0
            HIGH:                        Do not set this bit
*/
#define SDMMC_ISE_NOUSE0                                             0x00000400U
#define SDMMC_ISE_NOUSE0_M                                           0x00000400U
#define SDMMC_ISE_NOUSE0_S                                           10U
#define SDMMC_ISE_NOUSE0_LOW                                         0x00000000U
#define SDMMC_ISE_NOUSE0_HIGH                                        0x00000400U
/*

        Field:           NULL
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Fixed to 0.
                         The host driver shall control error interrupts using the Error Interrupt Signal Enable register.
                         Writes to this bit are ignored.

        ENUMs:
            ENABLE:                      Interrupt enabled
            MSK:                         Interrupt masked
*/
#define SDMMC_ISE_NULL                                               0x00008000U
#define SDMMC_ISE_NULL_M                                             0x00008000U
#define SDMMC_ISE_NULL_S                                             15U
#define SDMMC_ISE_NULL_ENABLE                                        0x00008000U
#define SDMMC_ISE_NULL_MSK                                           0x00000000U
/*

        Field:           CTOSEN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command timeout error signal status enable

        ENUMs:
            ENABLE:                      Status Interrupt signaling enabled
            DISABLE:                     Status Interrupt signaling disabled
*/
#define SDMMC_ISE_CTOSEN                                             0x00010000U
#define SDMMC_ISE_CTOSEN_M                                           0x00010000U
#define SDMMC_ISE_CTOSEN_S                                           16U
#define SDMMC_ISE_CTOSEN_ENABLE                                      0x00010000U
#define SDMMC_ISE_CTOSEN_DISABLE                                     0x00000000U
/*

        Field:           CCRCSEN
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command CRC error signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_CCRCSEN                                            0x00020000U
#define SDMMC_ISE_CCRCSEN_M                                          0x00020000U
#define SDMMC_ISE_CCRCSEN_S                                          17U
#define SDMMC_ISE_CCRCSEN_DISABLE                                    0x00000000U
#define SDMMC_ISE_CCRCSEN_ENABLE                                     0x00020000U
/*

        Field:           CEBSEN
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command end bit error signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_CEBSEN                                             0x00040000U
#define SDMMC_ISE_CEBSEN_M                                           0x00040000U
#define SDMMC_ISE_CEBSEN_S                                           18U
#define SDMMC_ISE_CEBSEN_DISABLE                                     0x00000000U
#define SDMMC_ISE_CEBSEN_ENABLE                                      0x00040000U
/*

        Field:           CIESEN
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command index error signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_CIESEN                                             0x00080000U
#define SDMMC_ISE_CIESEN_M                                           0x00080000U
#define SDMMC_ISE_CIESEN_S                                           19U
#define SDMMC_ISE_CIESEN_DISABLE                                     0x00000000U
#define SDMMC_ISE_CIESEN_ENABLE                                      0x00080000U
/*

        Field:           DTOSEN
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data timeout error signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_DTOSEN                                             0x00100000U
#define SDMMC_ISE_DTOSEN_M                                           0x00100000U
#define SDMMC_ISE_DTOSEN_S                                           20U
#define SDMMC_ISE_DTOSEN_DISABLE                                     0x00000000U
#define SDMMC_ISE_DTOSEN_ENABLE                                      0x00100000U
/*

        Field:           DCRCSEN
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data CRC error signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_DCRCSEN                                            0x00200000U
#define SDMMC_ISE_DCRCSEN_M                                          0x00200000U
#define SDMMC_ISE_DCRCSEN_S                                          21U
#define SDMMC_ISE_DCRCSEN_DISABLE                                    0x00000000U
#define SDMMC_ISE_DCRCSEN_ENABLE                                     0x00200000U
/*

        Field:           DEBSEN
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data end bit error signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_DEBSEN                                             0x00400000U
#define SDMMC_ISE_DEBSEN_M                                           0x00400000U
#define SDMMC_ISE_DEBSEN_S                                           22U
#define SDMMC_ISE_DEBSEN_DISABLE                                     0x00000000U
#define SDMMC_ISE_DEBSEN_ENABLE                                      0x00400000U
/*

        Field:           ACESEN
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Auto CMD12 error signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_ACESEN                                             0x01000000U
#define SDMMC_ISE_ACESEN_M                                           0x01000000U
#define SDMMC_ISE_ACESEN_S                                           24U
#define SDMMC_ISE_ACESEN_DISABLE                                     0x00000000U
#define SDMMC_ISE_ACESEN_ENABLE                                      0x01000000U
/*

        Field:           ADMAESEN
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ADMA Error Signal Enable
                         Note: This functionality is not supported, since MADMA_EN is set to 0 in the design.

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_ADMAESEN                                           0x02000000U
#define SDMMC_ISE_ADMAESEN_M                                         0x02000000U
#define SDMMC_ISE_ADMAESEN_S                                         25U
#define SDMMC_ISE_ADMAESEN_DISABLE                                   0x00000000U
#define SDMMC_ISE_ADMAESEN_ENABLE                                    0x02000000U
/*

        Field:           NOUSE1
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     No use
                         Note: Writing values other than 0 might produce undesired results.
                         Always set this bit to 0.

        ENUMs:
            LOW:                         Always set this bit to 0
            HIGH:                        Do not set this bit
*/
#define SDMMC_ISE_NOUSE1                                             0x04000000U
#define SDMMC_ISE_NOUSE1_M                                           0x04000000U
#define SDMMC_ISE_NOUSE1_S                                           26U
#define SDMMC_ISE_NOUSE1_LOW                                         0x00000000U
#define SDMMC_ISE_NOUSE1_HIGH                                        0x04000000U
/*

        Field:           CERRSEN
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Card error interrupt signal status enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_CERRSEN                                            0x10000000U
#define SDMMC_ISE_CERRSEN_M                                          0x10000000U
#define SDMMC_ISE_CERRSEN_S                                          28U
#define SDMMC_ISE_CERRSEN_DISABLE                                    0x00000000U
#define SDMMC_ISE_CERRSEN_ENABLE                                     0x10000000U
/*

        Field:           BADASEN
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Bad access to data space interrupt enable

        ENUMs:
            DISABLE:                     Status Interrupt signaling disabled
            ENABLE:                      Status Interrupt signaling enabled
*/
#define SDMMC_ISE_BADASEN                                            0x20000000U
#define SDMMC_ISE_BADASEN_M                                          0x20000000U
#define SDMMC_ISE_BADASEN_S                                          29U
#define SDMMC_ISE_BADASEN_DISABLE                                    0x00000000U
#define SDMMC_ISE_BADASEN_ENABLE                                     0x20000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AC12
    Offset name:         SDMMC_O_AC12
    Relative address:    0x23C
    Description:         SD_AC12 Error register
                        The host driver may determine which of the errors cases related to Auto CMD12 has occurred by checking this SD_AC12 register when an auto CMD12 error interrupt occurs. This register is valid only when auto CMD12 is enabled (SD_CMD.ACEN) and auto CMD12Error (SD_STAT.ACE) is set to 1.
                        These bits are automatically reset when starting a new adtc command with data.
    Default Value:       0x00000000

        Field:           ACNE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Auto CMD12 not executed.
                         This bit is set to 1 if multiple block data transfer command has started and if an error occurs in command before auto CMD12 starts.

        ENUMs:
            NOERR:                       Auto CMD12 executed
            ERR:                         Auto CMD12 not executed
*/
#define SDMMC_AC12_ACNE                                              0x00000001U
#define SDMMC_AC12_ACNE_M                                            0x00000001U
#define SDMMC_AC12_ACNE_S                                            0U
#define SDMMC_AC12_ACNE_NOERR                                        0x00000000U
#define SDMMC_AC12_ACNE_ERR                                          0x00000001U
/*

        Field:           ACTO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Auto CMD12 timeout error.
                         This bit is set to 1 if no response is received within 64 clock cycles from the end bit of the auto CMD12 command.

        ENUMs:
            NOERR:                       No error
            ERR:                         Error occurred
*/
#define SDMMC_AC12_ACTO                                              0x00000002U
#define SDMMC_AC12_ACTO_M                                            0x00000002U
#define SDMMC_AC12_ACTO_S                                            1U
#define SDMMC_AC12_ACTO_NOERR                                        0x00000000U
#define SDMMC_AC12_ACTO_ERR                                          0x00000002U
/*

        Field:           ACCE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Auto CMD12 CRC error.
                         This bit is set to 1 when a CRC7 error is detected in the auto CMD12 command response.

        ENUMs:
            NOERR:                       No error
            ERR:                         Error occurred
*/
#define SDMMC_AC12_ACCE                                              0x00000004U
#define SDMMC_AC12_ACCE_M                                            0x00000004U
#define SDMMC_AC12_ACCE_S                                            2U
#define SDMMC_AC12_ACCE_NOERR                                        0x00000000U
#define SDMMC_AC12_ACCE_ERR                                          0x00000004U
/*

        Field:           ACEB
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Auto CMD12 end bit error.
                         This bit is set to 1 when detecting a 0 at the end bit position of auto CMD12 command response.

        ENUMs:
            NOERR:                       No error
            ERR:                         Error occurred
*/
#define SDMMC_AC12_ACEB                                              0x00000008U
#define SDMMC_AC12_ACEB_M                                            0x00000008U
#define SDMMC_AC12_ACEB_S                                            3U
#define SDMMC_AC12_ACEB_NOERR                                        0x00000000U
#define SDMMC_AC12_ACEB_ERR                                          0x00000008U
/*

        Field:           ACIE
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Auto CMD12 index error
                         This bit is a set to 1 when response index differs from corresponding command auto CMD12 index previously emitted.
                         This bit depends on the command index check enable (SD_CMD.CICEN).

        ENUMs:
            NOERR:                       No error
            ERR:                         Error occurred
*/
#define SDMMC_AC12_ACIE                                              0x00000010U
#define SDMMC_AC12_ACIE_M                                            0x00000010U
#define SDMMC_AC12_ACIE_S                                            4U
#define SDMMC_AC12_ACIE_NOERR                                        0x00000000U
#define SDMMC_AC12_ACIE_ERR                                          0x00000010U
/*

        Field:           CNI
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command not issue by auto CMD12 error
                         If this bit is set to 1, a pending command is not executed due to auto CMD12 error ACEB, ACCE, ACTO, or ACNE.

        ENUMs:
            NOERR:                       No error
            ERR:                         Error occurred
*/
#define SDMMC_AC12_CNI                                               0x00000080U
#define SDMMC_AC12_CNI_M                                             0x00000080U
#define SDMMC_AC12_CNI_S                                             7U
#define SDMMC_AC12_CNI_NOERR                                         0x00000000U
#define SDMMC_AC12_CNI_ERR                                           0x00000080U
/*

        Field:           UHSMS
        From..to bits:   16...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     UHS Mode Select
                         This field is used to select one of UHS-I modes or e.MMC HS200 mode and effective when 1.8V Signaling Enable is set to 1.

                         Note: Dragon does not support 1.8V signaling and UHS modes.
                         Always set this bitfield to 0.

        ENUMs:
            SDR12:                       SDR12
            SDR25:                       SDR25
            SDR50:                       SDR50
            SDR104:                      SDR104 / HS200
            DDR50:                       DDR50
*/
#define SDMMC_AC12_UHSMS_W                                           3U
#define SDMMC_AC12_UHSMS_M                                           0x00070000U
#define SDMMC_AC12_UHSMS_S                                           16U
#define SDMMC_AC12_UHSMS_SDR12                                       0x00000000U
#define SDMMC_AC12_UHSMS_SDR25                                       0x00010000U
#define SDMMC_AC12_UHSMS_SDR50                                       0x00020000U
#define SDMMC_AC12_UHSMS_SDR104                                      0x00030000U
#define SDMMC_AC12_UHSMS_DDR50                                       0x00040000U
/*

        Field:           V1P8SEN
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1.8V Signaling Enable

                         This bit controls voltage regulator for I/O cell. 3.3V is supplied to the card regardless of signaling voltage.
                         Setting this bit from 0 to 1 starts changing signal voltage from 3.3V to 1.8V. 1.8V regulator output shall be stable within 5ms. Host Controller clears this bit if switching to 1.8V signaling fails.
                         Clearing this bit from 1 to 0 starts changing signal voltage from 1.8V to 3.3V. 3.3V regulator output shall be stable within 5ms.

                         Host Driver can set this bit to 1 when Host Controller supports 1.8V signaling (One of support bits is set to 1: SDR50, SDR104 or DDR50 in the Capabilities register) and the card or device supports UHS-I (S18A=1. Refer to Bus Signal Voltage Switch Sequence in the Physical Layer Specification Version 3.0x).

                         Note: Dragon supports only 3.3V.
                         Always set this bit to 0.

        ENUMs:
            DISABLE:                     3.3V Signaling
            ENABLE:                      1.8V Signaling
*/
#define SDMMC_AC12_V1P8SEN                                           0x00080000U
#define SDMMC_AC12_V1P8SEN_M                                         0x00080000U
#define SDMMC_AC12_V1P8SEN_S                                         19U
#define SDMMC_AC12_V1P8SEN_DISABLE                                   0x00000000U
#define SDMMC_AC12_V1P8SEN_ENABLE                                    0x00080000U
/*

        Field:           DSSEL
        From..to bits:   20...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Driver Strength Select

                         Host Controller output driver in 1.8V signaling is selected by this bit. In 3.3V signaling, this field is not effective. This field can be set depends on Driver Type A, C and D support bits in the Capabilities register.



        ENUMs:
            TYPE_B:                      Driver Type B is selected
            TYPE_A:                      Driver Type A is selected
            TYPE_C:                      Driver Type C is selected
            TYPE_D:                      Driver Type D is selected
*/
#define SDMMC_AC12_DSSEL_W                                           2U
#define SDMMC_AC12_DSSEL_M                                           0x00300000U
#define SDMMC_AC12_DSSEL_S                                           20U
#define SDMMC_AC12_DSSEL_TYPE_B                                      0x00000000U
#define SDMMC_AC12_DSSEL_TYPE_A                                      0x00100000U
#define SDMMC_AC12_DSSEL_TYPE_C                                      0x00200000U
#define SDMMC_AC12_DSSEL_TYPE_D                                      0x00300000U
/*

        Field:           NOUSE0
        From..to bits:   22...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     No use
                         Note: Writing values other than 0 might produce undesired results.
                         Always set this bit to 0.

        ENUMs:
            LOW:                         Always set this bit to 0
            HIGH:                        Do not set this bit
*/
#define SDMMC_AC12_NOUSE0_W                                          2U
#define SDMMC_AC12_NOUSE0_M                                          0x00C00000U
#define SDMMC_AC12_NOUSE0_S                                          22U
#define SDMMC_AC12_NOUSE0_LOW                                        0x00000000U
#define SDMMC_AC12_NOUSE0_HIGH                                       0x00400000U
/*

        Field:           AIEN
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Asynchronous Interrupt Enable

                         This bit can be set to 1 if a card supports asynchronous interrupts and Asynchronous Interrupt Support is set to 1 in the Capabilities register. Asynchronous interrupt is effective when DAT[1] interrupt is used in 4-bit SD mode (and zero is set to Interrupt Pin Select in the Shared Bus Control register). If this bit is set to 1, the Host Driver can stop the SDCLK during asynchronous interrupt period to save power. During this period, the Host Controller continues to deliver the Card Interrupt to the host when it is asserted by the Card.


        ENUMs:
            DISABLE:                     Asynchronous Interrupt disabled
            ENABLE:                      Asynchronous Interrupt enabled
*/
#define SDMMC_AC12_AIEN                                              0x40000000U
#define SDMMC_AC12_AIEN_M                                            0x40000000U
#define SDMMC_AC12_AIEN_S                                            30U
#define SDMMC_AC12_AIEN_DISABLE                                      0x00000000U
#define SDMMC_AC12_AIEN_ENABLE                                       0x40000000U
/*

        Field:           NOUSE1
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     No use
                         Note: Writing values other than 0 might produce undesired results.
                         Always set this bit to 0.

        ENUMs:
            LOW:                         Always set this bit to 0
            HIGH:                        Do not set this bit
*/
#define SDMMC_AC12_NOUSE1                                            0x80000000U
#define SDMMC_AC12_NOUSE1_M                                          0x80000000U
#define SDMMC_AC12_NOUSE1_S                                          31U
#define SDMMC_AC12_NOUSE1_LOW                                        0x00000000U
#define SDMMC_AC12_NOUSE1_HIGH                                       0x80000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CAPA
    Offset name:         SDMMC_O_CAPA
    Relative address:    0x240
    Description:         Capability register
                        This register lists the capabilities of the MMC/SD/SDIO host controller.
    Default Value:       0x20E10080

        Field:           TCF
        From..to bits:   0...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Timeout clock frequency
                         The timeout clock frequency is used to detect Data Timeout Error (DTO interrupt).
                         The timeout clock frequency depends on the frequency of the clock provided to the card. The value of the timeout clock frequency is not available in this register.

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_CAPA_TCF_W                                             6U
#define SDMMC_CAPA_TCF_M                                             0x0000003FU
#define SDMMC_CAPA_TCF_S                                             0U
#define SDMMC_CAPA_TCF_MINIMUM                                       0x00000000U
#define SDMMC_CAPA_TCF_MAXIMUM                                       0x0000003FU
/*

        Field:           TCU
        From..to bits:   7...7
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Timeout clock unit
                         This bit shows the unit of base clock frequency used to detect Data Timeout Error.

        ENUMs:
            KHZ:                         kHz
            MHZ:                         MHz
*/
#define SDMMC_CAPA_TCU                                               0x00000080U
#define SDMMC_CAPA_TCU_M                                             0x00000080U
#define SDMMC_CAPA_TCU_S                                             7U
#define SDMMC_CAPA_TCU_KHZ                                           0x00000000U
#define SDMMC_CAPA_TCU_MHZ                                           0x00000080U
/*

        Field:           BCF
        From..to bits:   8...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Base clock frequency for clock provided to the card.
                         ARRAY(0x1bfe1b0)

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_CAPA_BCF_W                                             6U
#define SDMMC_CAPA_BCF_M                                             0x00003F00U
#define SDMMC_CAPA_BCF_S                                             8U
#define SDMMC_CAPA_BCF_MINIMUM                                       0x00000000U
#define SDMMC_CAPA_BCF_MAXIMUM                                       0x00003F00U
/*

        Field:           MBL
        From..to bits:   16...17
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Maximum block length
                         This value indicates the maximum block size that the host driver can read and write to the buffer in the host controller.
                         The host controller supports 512 bytes and 1024 bytes block transfers.
                         0h = 512 bytes
                         1h = 1024 bytes
                         2h = 2048 bytes

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_CAPA_MBL_W                                             2U
#define SDMMC_CAPA_MBL_M                                             0x00030000U
#define SDMMC_CAPA_MBL_S                                             16U
#define SDMMC_CAPA_MBL_MINIMUM                                       0x00000000U
#define SDMMC_CAPA_MBL_MAXIMUM                                       0x00030000U
/*

        Field:           AD2S
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This bit indicates whether the Host Controller is capable of using ADMA2.

        ENUMs:
            SUPPORT:                     Supported
            NOSUPPORT:                   Not supported
*/
#define SDMMC_CAPA_AD2S                                              0x00080000U
#define SDMMC_CAPA_AD2S_M                                            0x00080000U
#define SDMMC_CAPA_AD2S_S                                            19U
#define SDMMC_CAPA_AD2S_SUPPORT                                      0x00080000U
#define SDMMC_CAPA_AD2S_NOSUPPORT                                    0x00000000U
/*

        Field:           HSS
        From..to bits:   21...21
        DefaultValue:    0x1
        Access type:     read-only
        Description:     High-speed support
                         This bit indicates that the host controller supports high speed operations and can supply an up-to-52 MHz clock to the card.

        ENUMs:
            NOSUPPORT:                   Not supported
            SUPPORT:                     Supported
*/
#define SDMMC_CAPA_HSS                                               0x00200000U
#define SDMMC_CAPA_HSS_M                                             0x00200000U
#define SDMMC_CAPA_HSS_S                                             21U
#define SDMMC_CAPA_HSS_NOSUPPORT                                     0x00000000U
#define SDMMC_CAPA_HSS_SUPPORT                                       0x00200000U
/*

        Field:           DS
        From..to bits:   22...22
        DefaultValue:    0x1
        Access type:     read-only
        Description:     DMA support
                         This bit indicates that the Host controller is able to use DMA to transfer data between system memory and the Host controller directly.

        ENUMs:
            NOSUPPORT:                   Not supported
            SUPPORT:                     Supported
*/
#define SDMMC_CAPA_DS                                                0x00400000U
#define SDMMC_CAPA_DS_M                                              0x00400000U
#define SDMMC_CAPA_DS_S                                              22U
#define SDMMC_CAPA_DS_NOSUPPORT                                      0x00000000U
#define SDMMC_CAPA_DS_SUPPORT                                        0x00400000U
/*

        Field:           SRS
        From..to bits:   23...23
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Suspend/resume support (SDIO cards only).
                         This bit indicates whether the host controller supports suspend/resume functionality.

        ENUMs:
            NOSUPPORT:                   Not supported
            SUPPORT:                     Supported
*/
#define SDMMC_CAPA_SRS                                               0x00800000U
#define SDMMC_CAPA_SRS_M                                             0x00800000U
#define SDMMC_CAPA_SRS_S                                             23U
#define SDMMC_CAPA_SRS_NOSUPPORT                                     0x00000000U
#define SDMMC_CAPA_SRS_SUPPORT                                       0x00800000U
/*

        Field:           VS33
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Voltage support 3.3V
                         Initialization of this register (via a write access to this register) depends on the system capabilities.
                         The host driver shall not modify this register after the initialization.
                         This register is only reinitialized by a hard reset (via mmc_RESET signal).
                         0h (W) = 3.3 V not supported
                         0h (R) = 3.3 V not supported
                         1h (W) = 3.3 V supported
                         1h (R) = 3.3 V supported

        ENUMs:
            NOSUPPORT:                   Not supported
            SUPPORT:                     Supported
*/
#define SDMMC_CAPA_VS33                                              0x01000000U
#define SDMMC_CAPA_VS33_M                                            0x01000000U
#define SDMMC_CAPA_VS33_S                                            24U
#define SDMMC_CAPA_VS33_NOSUPPORT                                    0x00000000U
#define SDMMC_CAPA_VS33_SUPPORT                                      0x01000000U
/*

        Field:           VS30
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Voltage support 3.0V
                         Initialization of this register (via a write access to this register) depends on the system capabilities.
                         The host driver shall not modify this register after the initialization.
                         This register is only reinitialized by a hard reset (via mmc_RESET signal).
                         0h (W) = 3.0 V not supported
                         0h (R) = 3.0 V not supported
                         1h (W) = 3.0 V supported
                         1h (R) = 3.0 V supported

        ENUMs:
            NOSUPPORT:                   Not supported
            SUPPORT:                     Supported
*/
#define SDMMC_CAPA_VS30                                              0x02000000U
#define SDMMC_CAPA_VS30_M                                            0x02000000U
#define SDMMC_CAPA_VS30_S                                            25U
#define SDMMC_CAPA_VS30_NOSUPPORT                                    0x00000000U
#define SDMMC_CAPA_VS30_SUPPORT                                      0x02000000U
/*

        Field:           VS18
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Voltage support 1.8 V
                         Initialization of this register (via a write access to this register) depends on the system capabilities.
                         The host driver shall not modify this register after the initialization.
                         This register is only reinitialized by a hard reset (via mmc_RESET signal).
                         0h (W) = 1.8 V not supported
                         0h (R) = 1.8 V not supported
                         1h (W) = 1.8 V supported
                         1h (R) = 1.8 V supported

        ENUMs:
            NOSUPPORT:                   Not supported
            SUPPORT:                     Supported
*/
#define SDMMC_CAPA_VS18                                              0x04000000U
#define SDMMC_CAPA_VS18_M                                            0x04000000U
#define SDMMC_CAPA_VS18_S                                            26U
#define SDMMC_CAPA_VS18_NOSUPPORT                                    0x00000000U
#define SDMMC_CAPA_VS18_SUPPORT                                      0x04000000U
/*

        Field:           BUS64BIT
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-only
        Description:     64 Bit System Bus Support
                         Setting 1 to this bit indicates that the Host Controller supports 64-bit address descriptor mode and is connected to 64-bit address system bus.
                         0h (R) = 32-bit System bus address
                         1h (R) = 64-bit System bus address

        ENUMs:
            NOSUPPORT:                   Not supported
            SUPPORT:                     Supported
*/
#define SDMMC_CAPA_BUS64BIT                                          0x10000000U
#define SDMMC_CAPA_BUS64BIT_M                                        0x10000000U
#define SDMMC_CAPA_BUS64BIT_S                                        28U
#define SDMMC_CAPA_BUS64BIT_NOSUPPORT                                0x00000000U
#define SDMMC_CAPA_BUS64BIT_SUPPORT                                  0x10000000U
/*

        Field:           AIS
        From..to bits:   29...29
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Asynchronous Interrupt Support
                         Refer to SDIO Specification Version 3.00 about asynchronous interrupt.

        ENUMs:
            NOSUPPORT:                   Not supported
            SUPPORT:                     Supported
*/
#define SDMMC_CAPA_AIS                                               0x20000000U
#define SDMMC_CAPA_AIS_M                                             0x20000000U
#define SDMMC_CAPA_AIS_S                                             29U
#define SDMMC_CAPA_AIS_NOSUPPORT                                     0x00000000U
#define SDMMC_CAPA_AIS_SUPPORT                                       0x20000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CURCAPA
    Offset name:         SDMMC_O_CURCAPA
    Relative address:    0x248
    Description:         Current capability register
                        This register indicates the maximum current capability for each voltage.
    Default Value:       0x00000000

        Field:           CUR33
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Maximum current for 3.3V
                         The maximum current capability for this voltage is not available. Feature not implemented.

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_CURCAPA_CUR33_W                                        8U
#define SDMMC_CURCAPA_CUR33_M                                        0x000000FFU
#define SDMMC_CURCAPA_CUR33_S                                        0U
#define SDMMC_CURCAPA_CUR33_MINIMUM                                  0x00000000U
#define SDMMC_CURCAPA_CUR33_MAXIMUM                                  0x000000FFU
/*

        Field:           CUR30
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Maximum current for 3.0V
                         The maximum current capability for this voltage is not available. Feature not implemented.

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_CURCAPA_CUR30_W                                        8U
#define SDMMC_CURCAPA_CUR30_M                                        0x0000FF00U
#define SDMMC_CURCAPA_CUR30_S                                        8U
#define SDMMC_CURCAPA_CUR30_MINIMUM                                  0x00000000U
#define SDMMC_CURCAPA_CUR30_MAXIMUM                                  0x0000FF00U
/*

        Field:           CUR18
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Maximum current for 1.8V
                         The maximum current capability for this voltage is not available. Feature not implemented.

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_CURCAPA_CUR18_W                                        8U
#define SDMMC_CURCAPA_CUR18_M                                        0x00FF0000U
#define SDMMC_CURCAPA_CUR18_S                                        16U
#define SDMMC_CURCAPA_CUR18_MINIMUM                                  0x00000000U
#define SDMMC_CURCAPA_CUR18_MAXIMUM                                  0x00FF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       REV
    Offset name:         SDMMC_O_REV
    Relative address:    0x2FC
    Description:         Revision register
                        This register contains the hard coded RTL vendor revision number, the version number of SD specification compliancy.
    Default Value:       0x33020000

        Field:           SIS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Slot Interrupt Status
                         This status bit indicates the inverted state of interrupt signal for the module.
                         By a power on reset or by setting a software reset for all, the interrupt signal shall be deasserted and this status shall read 0.

        ENUMs:
            NOINT:                       No interrupt is asserted
            INT:                         Interrupt is asserted
*/
#define SDMMC_REV_SIS                                                0x00000001U
#define SDMMC_REV_SIS_M                                              0x00000001U
#define SDMMC_REV_SIS_S                                              0U
#define SDMMC_REV_SIS_NOINT                                          0x00000000U
#define SDMMC_REV_SIS_INT                                            0x00000001U
/*

        Field:           SREV
        From..to bits:   16...23
        DefaultValue:    0x2
        Access type:     read-only
        Description:     Specification Version Number
                         This status indicates the Standard SD Host Controller Specification Version.
                         The upper and lower 4 bits indicate the version.
                         0h: 	SD Host Specification Version 1.00.
                         1h: 	SD Host Specification Version 2.00.
                         2h: 	SD Host Specification Version 3.00.
                         3h: 	Reserved


        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_REV_SREV_W                                             8U
#define SDMMC_REV_SREV_M                                             0x00FF0000U
#define SDMMC_REV_SREV_S                                             16U
#define SDMMC_REV_SREV_MINIMUM                                       0x00000000U
#define SDMMC_REV_SREV_MAXIMUM                                       0x00FF0000U
/*

        Field:           VREV
        From..to bits:   24...31
        DefaultValue:    0x33
        Access type:     read-only
        Description:     Vendor Version Number
                         Bits 7 to 4 are the major revision, bits 3 to 0 are the minor revision.
                         Examples: 0x10 for 1.0 and 0x21 for 2.1.
                         Reset value is 0x31.

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_REV_VREV_W                                             8U
#define SDMMC_REV_VREV_M                                             0xFF000000U
#define SDMMC_REV_VREV_S                                             24U
#define SDMMC_REV_VREV_MINIMUM                                       0x00000000U
#define SDMMC_REV_VREV_MAXIMUM                                       0xFF000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FE
    Offset name:         SDMMC_O_FE
    Relative address:    0x250
    Description:         The Force Event register is not a physically implemented register. Rather, it is an address at which the Error Interrupt Status register can be written. The effect of a write to this address will be reflected in the Error Interrupt Status Register, if corresponding bit of the Error Interrupt Status Enable Register is set.
    Default Value:       0x00000000

        Field:           ACNE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Auto CMD12 not executed.

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_ACNE                                                0x00000001U
#define SDMMC_FE_ACNE_M                                              0x00000001U
#define SDMMC_FE_ACNE_S                                              0U
#define SDMMC_FE_ACNE_NOINT                                          0x00000000U
#define SDMMC_FE_ACNE_INT                                            0x00000001U
/*

        Field:           ACTO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Auto CMD12 timeout error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_ACTO                                                0x00000002U
#define SDMMC_FE_ACTO_M                                              0x00000002U
#define SDMMC_FE_ACTO_S                                              1U
#define SDMMC_FE_ACTO_NOINT                                          0x00000000U
#define SDMMC_FE_ACTO_INT                                            0x00000002U
/*

        Field:           ACCE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Auto CMD12 CRC error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_ACCE                                                0x00000004U
#define SDMMC_FE_ACCE_M                                              0x00000004U
#define SDMMC_FE_ACCE_S                                              2U
#define SDMMC_FE_ACCE_NOINT                                          0x00000000U
#define SDMMC_FE_ACCE_INT                                            0x00000004U
/*

        Field:           ACEB
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Auto CMD12 end bit error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_ACEB                                                0x00000008U
#define SDMMC_FE_ACEB_M                                              0x00000008U
#define SDMMC_FE_ACEB_S                                              3U
#define SDMMC_FE_ACEB_NOINT                                          0x00000000U
#define SDMMC_FE_ACEB_INT                                            0x00000008U
/*

        Field:           ACIE
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Auto CMD12 index error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_ACIE                                                0x00000010U
#define SDMMC_FE_ACIE_M                                              0x00000010U
#define SDMMC_FE_ACIE_S                                              4U
#define SDMMC_FE_ACIE_NOINT                                          0x00000000U
#define SDMMC_FE_ACIE_INT                                            0x00000010U
/*

        Field:           CNI
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Command not issue by Auto CMD12 error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_CNI                                                 0x00000080U
#define SDMMC_FE_CNI_M                                               0x00000080U
#define SDMMC_FE_CNI_S                                               7U
#define SDMMC_FE_CNI_NOINT                                           0x00000000U
#define SDMMC_FE_CNI_INT                                             0x00000080U
/*

        Field:           CTO
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Command Timeout error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_CTO                                                 0x00010000U
#define SDMMC_FE_CTO_M                                               0x00010000U
#define SDMMC_FE_CTO_S                                               16U
#define SDMMC_FE_CTO_NOINT                                           0x00000000U
#define SDMMC_FE_CTO_INT                                             0x00010000U
/*

        Field:           CCRC
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Comemand CRC error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_CCRC                                                0x00020000U
#define SDMMC_FE_CCRC_M                                              0x00020000U
#define SDMMC_FE_CCRC_S                                              17U
#define SDMMC_FE_CCRC_NOINT                                          0x00000000U
#define SDMMC_FE_CCRC_INT                                            0x00020000U
/*

        Field:           CEB
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Command end bit error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_CEB                                                 0x00040000U
#define SDMMC_FE_CEB_M                                               0x00040000U
#define SDMMC_FE_CEB_S                                               18U
#define SDMMC_FE_CEB_NOINT                                           0x00000000U
#define SDMMC_FE_CEB_INT                                             0x00040000U
/*

        Field:           CIE
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Command index error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_CIE                                                 0x00080000U
#define SDMMC_FE_CIE_M                                               0x00080000U
#define SDMMC_FE_CIE_S                                               19U
#define SDMMC_FE_CIE_NOINT                                           0x00000000U
#define SDMMC_FE_CIE_INT                                             0x00080000U
/*

        Field:           DTO
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Data timeout error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_DTO                                                 0x00100000U
#define SDMMC_FE_DTO_M                                               0x00100000U
#define SDMMC_FE_DTO_S                                               20U
#define SDMMC_FE_DTO_NOINT                                           0x00000000U
#define SDMMC_FE_DTO_INT                                             0x00100000U
/*

        Field:           DCRC
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Data CRC error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_DCRC                                                0x00200000U
#define SDMMC_FE_DCRC_M                                              0x00200000U
#define SDMMC_FE_DCRC_S                                              21U
#define SDMMC_FE_DCRC_NOINT                                          0x00000000U
#define SDMMC_FE_DCRC_INT                                            0x00200000U
/*

        Field:           DEB
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Data End Bit error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_DEB                                                 0x00400000U
#define SDMMC_FE_DEB_M                                               0x00400000U
#define SDMMC_FE_DEB_S                                               22U
#define SDMMC_FE_DEB_NOINT                                           0x00000000U
#define SDMMC_FE_DEB_INT                                             0x00400000U
/*

        Field:           ACE
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Auto CMD12 error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_ACE                                                 0x01000000U
#define SDMMC_FE_ACE_M                                               0x01000000U
#define SDMMC_FE_ACE_S                                               24U
#define SDMMC_FE_ACE_NOINT                                           0x00000000U
#define SDMMC_FE_ACE_INT                                             0x01000000U
/*

        Field:           CERR
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Card error

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_CERR                                                0x10000000U
#define SDMMC_FE_CERR_M                                              0x10000000U
#define SDMMC_FE_CERR_S                                              28U
#define SDMMC_FE_CERR_NOINT                                          0x00000000U
#define SDMMC_FE_CERR_INT                                            0x10000000U
/*

        Field:           BADA
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Force Event Bad access to data space

        ENUMs:
            NOINT:                       No interrupt
            INT:                         Interrupt forced
*/
#define SDMMC_FE_BADA                                                0x20000000U
#define SDMMC_FE_BADA_M                                              0x20000000U
#define SDMMC_FE_BADA_S                                              29U
#define SDMMC_FE_BADA_NOINT                                          0x00000000U
#define SDMMC_FE_BADA_INT                                            0x20000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TPSEL
    Offset name:         SDMMC_O_TPSEL
    Relative address:    0x1040
    Description:         Test-Port select.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Test port 0 or 1

        ENUMs:
            TEST_PORT1:
            TEST_PORT2:
*/
#define SDMMC_TPSEL_VAL                                              0x00000001U
#define SDMMC_TPSEL_VAL_M                                            0x00000001U
#define SDMMC_TPSEL_VAL_S                                            0U
#define SDMMC_TPSEL_VAL_TEST_PORT1                                   0x00000000U
#define SDMMC_TPSEL_VAL_TEST_PORT2                                   0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMAMODE
    Offset name:         SDMMC_O_DMAMODE
    Relative address:    0x1048
    Description:         DMA mode select:
                        This register define the behavior of DMA request signal that allow tranmission of data.

    Default Value:       0x00000001

        Field:           VAL
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     0h = In this case, DMA required to read/write data from SD_DATA register,
                                  the value of DMA_INDICATION_SELECT register is d'ont care
                                  and the trigger to transmit data from the internal FIFO defined by SD_BLK.BLEN register as a threshold.

                         1h = DMA required to read/write data from BUFIF register
                                   the value of DMA_INDICATION_SELECT define the trigger of the internal FIFO.

        ENUMs:
            DISABLE:                     Disable to trig the internal FIFO with threshold, using DMA indication instead
            ENABLE:                      Enable to trig the internal FIFO with threshold
*/
#define SDMMC_DMAMODE_VAL                                            0x00000001U
#define SDMMC_DMAMODE_VAL_M                                          0x00000001U
#define SDMMC_DMAMODE_VAL_S                                          0U
#define SDMMC_DMAMODE_VAL_DISABLE                                    0x00000000U
#define SDMMC_DMAMODE_VAL_ENABLE                                     0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMAIND
    Offset name:         SDMMC_O_DMAIND
    Relative address:    0x1050
    Description:         DMA indication select:
                        This register define the behavior of transmitting data from/to the card using DMA
                        If DMA_MODE_SELECT =1, then the value of of this register is d'ont care,
                        else it define the trigger of the internal FIFO



    Default Value:       0x00000001

        Field:           VAL
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     0h = IP  transmit the data to/from the card after each DMA 'BLOCK' transmitted.
                                  In this case  SDMMC.SD_BLK.BLEN shoud be equal to HOST_DMA.JOB_CTRL_CH7.MEM_JOB_CTRL_CHAN_7_BLOCK_SIZE

                         1h = IP  transmit the data to the card after each DMA 'JOB' transmitted.
                                 In this case  SDMMC.SD_BLK.BLEN shoud be equal to HOST_DMA.TRANS_CTRL_CH7.MEM_TRANS_CTRL_CHAN_7_TRANS_NUM_B


        ENUMs:
            DMA_BLK:                     The IP transmit the data to/from the card, after each DMA transmitted block.
            DMA_JOB:                     The IP transmit the data to/from the card, only in the end of the DMA job.
*/
#define SDMMC_DMAIND_VAL                                             0x00000001U
#define SDMMC_DMAIND_VAL_M                                           0x00000001U
#define SDMMC_DMAIND_VAL_S                                           0U
#define SDMMC_DMAIND_VAL_DMA_BLK                                     0x00000000U
#define SDMMC_DMAIND_VAL_DMA_JOB                                     0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKSEL
    Offset name:         SDMMC_O_CLKSEL
    Relative address:    0x1054
    Description:         This register define the functional clock frequency, and whether the clock is synchronized to main clock.

    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0h = 40MHz post-swallowing

                         1h = 80MHz pro-swallowing

        ENUMs:
            SYNC:                        post-swallowing  40MHz clock to main clock
            ASYNC:                       pre-swallowing  80MHz clock
*/
#define SDMMC_CLKSEL_VAL                                             0x00000001U
#define SDMMC_CLKSEL_VAL_M                                           0x00000001U
#define SDMMC_CLKSEL_VAL_S                                           0U
#define SDMMC_CLKSEL_VAL_SYNC                                        0x00000000U
#define SDMMC_CLKSEL_VAL_ASYNC                                       0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EVTMODE
    Offset name:         SDMMC_O_EVTMODE
    Relative address:    0x10E0
    Description:         Event mode register. It is used to select whether each line is disabled, in software mode (software clears the RIS) or in hardware mode (hardware clears the RIS)
    Default Value:       0x00000001

        Field:           INT0CFG
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Event line mode select for event corresponding to [IPSTANDARD.INT_EVENT0]

        ENUMs:
            DISABLE:                     The interrupt or event line is disabled.
            SOFTWARE:                    The interrupt or event line is in software mode. Software must clear the RIS.
            HARDWARE:                    The interrupt or event line is in hardware mode. The hardware (another module) clears automatically the associated RIS flag.
*/
#define SDMMC_EVTMODE_INT0CFG_W                                      2U
#define SDMMC_EVTMODE_INT0CFG_M                                      0x00000003U
#define SDMMC_EVTMODE_INT0CFG_S                                      0U
#define SDMMC_EVTMODE_INT0CFG_DISABLE                                0x00000000U
#define SDMMC_EVTMODE_INT0CFG_SOFTWARE                               0x00000001U
#define SDMMC_EVTMODE_INT0CFG_HARDWARE                               0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DESC
    Offset name:         SDMMC_O_DESC
    Relative address:    0x10FC
    Description:         This register identifies the peripheral and its exact version.
    Default Value:       0x02111000

        Field:           MINREV
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Minor rev of the IP

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SDMMC_DESC_MINREV_W                                          4U
#define SDMMC_DESC_MINREV_M                                          0x0000000FU
#define SDMMC_DESC_MINREV_S                                          0U
#define SDMMC_DESC_MINREV_MINIMUM                                    0x00000000U
#define SDMMC_DESC_MINREV_MAXIMUM                                    0x0000000FU
/*

        Field:           MAJREV
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Major rev of the IP

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SDMMC_DESC_MAJREV_W                                          4U
#define SDMMC_DESC_MAJREV_M                                          0x000000F0U
#define SDMMC_DESC_MAJREV_S                                          4U
#define SDMMC_DESC_MAJREV_MINIMUM                                    0x00000000U
#define SDMMC_DESC_MAJREV_MAXIMUM                                    0x000000F0U
/*

        Field:           INSTNUM
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Instance Number within the device. This will be a parameter to the RTL for modules that can have multiple instances

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SDMMC_DESC_INSTNUM_W                                         4U
#define SDMMC_DESC_INSTNUM_M                                         0x00000F00U
#define SDMMC_DESC_INSTNUM_S                                         8U
#define SDMMC_DESC_INSTNUM_MINIMUM                                   0x00000000U
#define SDMMC_DESC_INSTNUM_MAXIMUM                                   0x00000F00U
/*

        Field:           FEATURST
        From..to bits:   12...15
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Feature Set for the module *instance*

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SDMMC_DESC_FEATURST_W                                        4U
#define SDMMC_DESC_FEATURST_M                                        0x0000F000U
#define SDMMC_DESC_FEATURST_S                                        12U
#define SDMMC_DESC_FEATURST_MINIMUM                                  0x00000000U
#define SDMMC_DESC_FEATURST_MAXIMUM                                  0x0000F000U
/*

        Field:           MODULEID
        From..to bits:   16...31
        DefaultValue:    0x211
        Access type:     read-only
        Description:     Module identification contains a unique peripheral identification number. The assignments are maintained in a central database for all of the platform modules to ensure uniqueness.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SDMMC_DESC_MODULEID_W                                        16U
#define SDMMC_DESC_MODULEID_M                                        0xFFFF0000U
#define SDMMC_DESC_MODULEID_S                                        16U
#define SDMMC_DESC_MODULEID_MINIMUM                                  0x00000000U
#define SDMMC_DESC_MODULEID_MAXIMUM                                  0xFFFF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SDMMCSTAT
    Offset name:         SDMMC_O_SDMMCSTAT
    Relative address:    0x1100
    Description:         SDMMC Status register

    Default Value:       0x00000000

        Field:           STATE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SDMMC state indication

        ENUMs:
            NORMAL:                      IP is active but is not transmitting
            ACTIVE:                      IP is active and transmitting
*/
#define SDMMC_SDMMCSTAT_STATE                                        0x00000001U
#define SDMMC_SDMMCSTAT_STATE_M                                      0x00000001U
#define SDMMC_SDMMCSTAT_STATE_S                                      0U
#define SDMMC_SDMMCSTAT_STATE_NORMAL                                 0x00000000U
#define SDMMC_SDMMCSTAT_STATE_ACTIVE                                 0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BUFIF
    Offset name:         SDMMC_O_BUFIF
    Relative address:    0x1110
    Description:         SRAM Data Access Registers
                        These registers are the 32-bit entry point of the SRAM buffer for read or write data transfers to and from the SDMMC card.
                        Data[1] register is an alias for the SD_BUFIF register and needs to be used for normal (non safety, non burst) buffer accesses.
                        Data[1..4] registers need to be used for non safety, incremental VBUSP burst accesses.
                        For safety accesses (write with readback and double read), DataS[1..4] registers need to be used.

                        The SRAM buffer size is 32bits x 256 (1024 bytes). Bytes within a word are stored and read in little endian format. This buffer can be used as two 512 byte buffers to transfer data efficiently without reducing the throughput. Sequential and contiguous access is necessary to increment the pointer correctly. Random or skipped access is not allowed.
                        If the local host accesses this register byte-wise or 16bit-wise, the least significant byte (bits [7:0]) must always be written/read first. The update of the buffer address is done on the most significant byte write.

    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Buffer data register
                         In functional mode (SD_CON.MODE = FUNC):
                         - a read access to this register is allowed only when the buffer read enable status is set to 1 (SD_PSTATE.BREN), otherwise a bad access (SD_STAT.BADA) is signaled.
                         - a write access to this register is allowed only when the buffer write enable status is set to 1 (SD_PSTATE.BWEN), otherwise a bad access (SD_STAT.BADA) is signaled and the data is not written.

        ENUMs:
            MINIMUM:                     Minimum value
            MAXIMUM:                     Maximum value
*/
#define SDMMC_BUFIF_DATA_W                                           32U
#define SDMMC_BUFIF_DATA_M                                           0xFFFFFFFFU
#define SDMMC_BUFIF_DATA_S                                           0U
#define SDMMC_BUFIF_DATA_MINIMUM                                     0x00000000U
#define SDMMC_BUFIF_DATA_MAXIMUM                                     0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCFG
    Offset name:         SDMMC_O_CLKCFG
    Relative address:    0x4000
    Description:         Clock Enable Register
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clock Disable / Enable for:
                         * bus_clk (main clock) - 80MHz ;
                         * card_clk (pll_clk) - 40MHz ;
                         * lf_clk (slow_clk) - 32KHz ;

*/
#define SDMMC_CLKCFG_EN                                              0x00000001U
#define SDMMC_CLKCFG_EN_M                                            0x00000001U
#define SDMMC_CLKCFG_EN_S                                            0U

#endif /* __HW_SDMMC_H__*/
