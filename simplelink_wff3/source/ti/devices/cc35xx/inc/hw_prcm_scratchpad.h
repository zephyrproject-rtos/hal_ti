/******************************************************************************
*  Filename:       hw_prcm_scratchpad.h
*
*  Description:    Defines and prototypes for the PRCM_SCRATCHPAD peripheral.
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
#ifndef __HW_PRCM_SCRATCHPAD_H__
#define __HW_PRCM_SCRATCHPAD_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the PRCM_SCRATCHPAD component

--------------------------------------------------------------------------------- */

//PRCM SCRATCHPAD
#define PRCM_SCRATCHPAD_O_LINE1                                      0x00000000U

//RESET CAUSE
#define PRCM_SCRATCHPAD_O_RSTCAUS                                    0x00000004U

//OSPREY PRCM AON scratch pad, this register bank is not deleted in SOC AON RESET and kept through reset/low power and brownout events
#define PRCM_SCRATCHPAD_O_LINE0                                      0x00000008U

//OSPREY PRCM AON scratch pad, this register bank is not deleted in SOC AON RESET and kept through reset/low power and brownout events
#define PRCM_SCRATCHPAD_O_LOCK                                       0x0000000CU

//PRCM SCRATCHPAD 2
#define PRCM_SCRATCHPAD_O_LINE2                                      0x00001000U



/*-----------------------------------REGISTER------------------------------------
    Register name:       LINE1
    Offset name:         PRCM_SCRATCHPAD_O_LINE1
    Relative address:    0x0
    Description:         PRCM SCRATCHPAD

                        m3 messages which should survive AON Reset and provide additional info on reset cause:

                        Critical error types + indication if reset applied for this error-  number of bits?
                        Max number of failures for reset apply - one common value for all errors with reset apply set
                        Counter
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     VALUE LINE 1

                         Scratch pad line 1

*/
#define PRCM_SCRATCHPAD_LINE1_VAL_W                                  32U
#define PRCM_SCRATCHPAD_LINE1_VAL_M                                  0xFFFFFFFFU
#define PRCM_SCRATCHPAD_LINE1_VAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RSTCAUS
    Offset name:         PRCM_SCRATCHPAD_O_RSTCAUS
    Relative address:    0x4
    Description:         RESET CAUSE

                        OSPREY PRCM AON scratch pad, this register bank is not deleted in SOC AON RESET and kept through reset/low power and brownout events
    Default Value:       NA

        Field:           RSTLINE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     Reset line

*/
#define PRCM_SCRATCHPAD_RSTCAUS_RSTLINE                              0x00000001U
#define PRCM_SCRATCHPAD_RSTCAUS_RSTLINE_M                            0x00000001U
#define PRCM_SCRATCHPAD_RSTCAUS_RSTLINE_S                            0U
/*

        Field:           POR
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     POR

*/
#define PRCM_SCRATCHPAD_RSTCAUS_POR                                  0x00000002U
#define PRCM_SCRATCHPAD_RSTCAUS_POR_M                                0x00000002U
#define PRCM_SCRATCHPAD_RSTCAUS_POR_S                                1U
/*

        Field:           RVML
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-only
        Description:     RVM low detect of fault injection  ; applicable only when protection RVML is disabled

*/
#define PRCM_SCRATCHPAD_RSTCAUS_RVML                                 0x00000004U
#define PRCM_SCRATCHPAD_RSTCAUS_RVML_M                               0x00000004U
#define PRCM_SCRATCHPAD_RSTCAUS_RVML_S                               2U
/*

        Field:           RVMH
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     read-only
        Description:     RVM high detect of fault injection ; applicable only when protection RVMH is disabled

*/
#define PRCM_SCRATCHPAD_RSTCAUS_RVMH                                 0x00000008U
#define PRCM_SCRATCHPAD_RSTCAUS_RVMH_M                               0x00000008U
#define PRCM_SCRATCHPAD_RSTCAUS_RVMH_S                               3U
/*

        Field:           BOD
        From..to bits:   4...4
        DefaultValue:    NA
        Access type:     read-only
        Description:     BOD;  applicable only when protection BOD  is disabled

*/
#define PRCM_SCRATCHPAD_RSTCAUS_BOD                                  0x00000010U
#define PRCM_SCRATCHPAD_RSTCAUS_BOD_M                                0x00000010U
#define PRCM_SCRATCHPAD_RSTCAUS_BOD_S                                4U
/*

        Field:           SOCAON
        From..to bits:   5...5
        DefaultValue:    NA
        Access type:     read-only
        Description:     SOC AON

                         Device self reset (SOC AON by CORE )

*/
#define PRCM_SCRATCHPAD_RSTCAUS_SOCAON                               0x00000020U
#define PRCM_SCRATCHPAD_RSTCAUS_SOCAON_M                             0x00000020U
#define PRCM_SCRATCHPAD_RSTCAUS_SOCAON_S                             5U
/*

        Field:           DBGSS
        From..to bits:   6...6
        DefaultValue:    NA
        Access type:     read-only
        Description:     DEBUGSS REQUEST

                         Debug req reset

*/
#define PRCM_SCRATCHPAD_RSTCAUS_DBGSS                                0x00000040U
#define PRCM_SCRATCHPAD_RSTCAUS_DBGSS_M                              0x00000040U
#define PRCM_SCRATCHPAD_RSTCAUS_DBGSS_S                              6U
/*

        Field:           M33WD
        From..to bits:   7...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     M33 WATCH DOG

*/
#define PRCM_SCRATCHPAD_RSTCAUS_M33WD                                0x00000080U
#define PRCM_SCRATCHPAD_RSTCAUS_M33WD_M                              0x00000080U
#define PRCM_SCRATCHPAD_RSTCAUS_M33WD_S                              7U
/*

        Field:           SOCAONH
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-only
        Description:     SOC AON by HOST

*/
#define PRCM_SCRATCHPAD_RSTCAUS_SOCAONH                              0x00000100U
#define PRCM_SCRATCHPAD_RSTCAUS_SOCAONH_M                            0x00000100U
#define PRCM_SCRATCHPAD_RSTCAUS_SOCAONH_S                            8U
/*

        Field:           OOFSLP
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-only
        Description:     OUT OF SLEEP

                         Exit sleep on wakeup event only

*/
#define PRCM_SCRATCHPAD_RSTCAUS_OOFSLP                               0x00000200U
#define PRCM_SCRATCHPAD_RSTCAUS_OOFSLP_M                             0x00000200U
#define PRCM_SCRATCHPAD_RSTCAUS_OOFSLP_S                             9U
/*

        Field:           M33CRSLSTA
        From..to bits:   10...10
        DefaultValue:    NA
        Access type:     read-only
        Description:     M33 CORE SL START

                         Core CONN STOP (M33 driven)

*/
#define PRCM_SCRATCHPAD_RSTCAUS_M33CRSLSTA                           0x00000400U
#define PRCM_SCRATCHPAD_RSTCAUS_M33CRSLSTA_M                         0x00000400U
#define PRCM_SCRATCHPAD_RSTCAUS_M33CRSLSTA_S                         10U
/*

        Field:           M3WD
        From..to bits:   11...11
        DefaultValue:    NA
        Access type:     read-only
        Description:     M3 Watch Dog

*/
#define PRCM_SCRATCHPAD_RSTCAUS_M3WD                                 0x00000800U
#define PRCM_SCRATCHPAD_RSTCAUS_M3WD_M                               0x00000800U
#define PRCM_SCRATCHPAD_RSTCAUS_M3WD_S                               11U
/*

        Field:           CLR
        From..to bits:   16...16
        DefaultValue:    NA
        Access type:     write-only
        Description:     CLEAR

                         write clear

                         Reset cause clear on write - first initiate relevant source reset clear
                         RVM - RVMTRIMCTL.RVMRSTCAUSCLR
                         BOD - BODCTL.RSTCAUSECLR
                         DEBUGSS - PMURSTCLR.DBGSSCAUS
                         WDT - PMURSTCLR.WDTCAUS

*/
#define PRCM_SCRATCHPAD_RSTCAUS_CLR                                  0x00010000U
#define PRCM_SCRATCHPAD_RSTCAUS_CLR_M                                0x00010000U
#define PRCM_SCRATCHPAD_RSTCAUS_CLR_S                                16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LINE0
    Offset name:         PRCM_SCRATCHPAD_O_LINE0
    Relative address:    0x8
    Description:         OSPREY PRCM AON scratch pad, this register bank is not deleted in SOC AON RESET and kept through reset/low power and brownout events

                        keep approved authenticated debug requests locked to allow OTA debug

                        allow write only during M3 boot - M3 Privilege mode (before soc_boot_done)

                        Allow read by M3/M33 according to configuration/firewall
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     VALUE LINE 0

                         Scratch pad line 0

*/
#define PRCM_SCRATCHPAD_LINE0_VAL_W                                  32U
#define PRCM_SCRATCHPAD_LINE0_VAL_M                                  0xFFFFFFFFU
#define PRCM_SCRATCHPAD_LINE0_VAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LOCK
    Offset name:         PRCM_SCRATCHPAD_O_LOCK
    Relative address:    0xC
    Description:         OSPREY PRCM AON scratch pad, this register bank is not deleted in SOC AON RESET and kept through reset/low power and brownout events
                        Lock is released on power on reset

                        allow write only during M3 boot - M3 Privilege mode (before soc_boot_done)
    Default Value:       NA

        Field:           SPLOCK
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     SCRATCHPAD LOCK

*/
#define PRCM_SCRATCHPAD_LOCK_SPLOCK                                  0x00000001U
#define PRCM_SCRATCHPAD_LOCK_SPLOCK_M                                0x00000001U
#define PRCM_SCRATCHPAD_LOCK_SPLOCK_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LINE2
    Offset name:         PRCM_SCRATCHPAD_O_LINE2
    Relative address:    0x1000
    Description:         PRCM SCRATCHPAD 2

                        m33 messages which should survive AON Reset:

                        OTA info -number of bits?
                        Critical error types + indication if reset applied for this error-  number of bits?
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     VALUE LINE 2

                         Scratch pad line 2


*/
#define PRCM_SCRATCHPAD_LINE2_VAL_W                                  32U
#define PRCM_SCRATCHPAD_LINE2_VAL_M                                  0xFFFFFFFFU
#define PRCM_SCRATCHPAD_LINE2_VAL_S                                  0U

#endif /* __HW_PRCM_SCRATCHPAD_H__*/
