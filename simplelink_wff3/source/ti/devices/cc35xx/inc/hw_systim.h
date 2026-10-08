/******************************************************************************
*  Filename:       hw_systim.h
*
*  Description:    Defines and prototypes for the SYSTIM peripheral.
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
#ifndef __HW_SYSTIM_H__
#define __HW_SYSTIM_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the SYSTIM component

--------------------------------------------------------------------------------- */

//This register identifies the peripheral and its exact version
#define SYSTIM_O_DESC                                                0x00000000U

//INTERRUPT BIT MASK
#define SYSTIM_O_IBM                                                 0x00000044U

//Raw interrupt status reflects all pending interrupts, regardless of masking
#define SYSTIM_O_RIS                                                 0x00000048U

//Masked interrupt status
#define SYSTIM_O_MIS                                                 0x0000004CU

//Interrupt set
#define SYSTIM_O_ISET                                                0x00000050U

//Interrupt clear
#define SYSTIM_O_ICLR                                                0x00000054U

//Interrupt mask set
#define SYSTIM_O_IMSET                                               0x00000058U

//Interrupt mask clear
#define SYSTIM_O_IMCLR                                               0x0000005CU

//This register can be used by the software developer to control the behavior of the peripheral relative to the CPU Halted input
#define SYSTIM_O_EMU                                                 0x00000060U

//Digital Test Bus
#define SYSTIM_O_DTB                                                 0x00000064U

//Systimer Counter Value[31:0]
#define SYSTIM_O_TIME250N                                            0x00000100U

//Systimer Counter Value[33:2]
#define SYSTIM_O_TIME1U                                              0x00000104U

//SYSTIMER'S Channel Output Event Values
#define SYSTIM_O_OUT                                                 0x00000108U

//SYSTIMER channel 0 configuration
#define SYSTIM_O_CH0CFG                                              0x0000010CU

//SYSTIMER channel 1 configuration
#define SYSTIM_O_CH1CFG                                              0x00000110U

//System Timer Channel 0 Capture/Compare Register
#define SYSTIM_O_CH0CC                                               0x00000120U

//System Timer Channel 1 Capture/Compare Register
#define SYSTIM_O_CH1CC                                               0x00000124U

//This Register will be used to specify which TIME bit is required by LGPT to be forwarded from SYSTIMER
#define SYSTIM_O_TIMEBIT                                             0x00000134U

//PI filter's Proportional Gain Value
#define SYSTIM_O_KP                                                  0x00000138U

//PI filter's Accumulator's Gain Value
#define SYSTIM_O_KI                                                  0x0000013CU

//STATUS
#define SYSTIM_O_STA                                                 0x00000140U

//ARMSET on read gives out the status of the 2 channels
#define SYSTIM_O_ARMSET                                              0x00000144U

//ARMCLR on read gives out the status of the 2 channels
#define SYSTIM_O_ARMCLR                                              0x00000148U

//Save/restore alias registers Channel 0
#define SYSTIM_O_CH0CCSR                                             0x0000014CU

//Save/restore alias registers Channel 1
#define SYSTIM_O_CH1CCSR                                             0x00000150U

//CLOCK CONFIG
#define SYSTIM_O_CLKCFG                                              0x00001000U



/*-----------------------------------REGISTER------------------------------------
    Register name:       DESC
    Offset name:         SYSTIM_O_DESC
    Relative address:    0x0
    Description:         This register identifies the peripheral and its exact version.
    Default Value:       0x94431010

        Field:           MINREV
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Minor revision of IP 0-15.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_DESC_MINREV_W                                         4U
#define SYSTIM_DESC_MINREV_M                                         0x0000000FU
#define SYSTIM_DESC_MINREV_S                                         0U
#define SYSTIM_DESC_MINREV_MINIMUM                                   0x00000000U
#define SYSTIM_DESC_MINREV_MAXIMUM                                   0x0000000FU
/*

        Field:           MAJREV
        From..to bits:   4...7
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Major revision of IP 0-15

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_DESC_MAJREV_W                                         4U
#define SYSTIM_DESC_MAJREV_M                                         0x000000F0U
#define SYSTIM_DESC_MAJREV_S                                         4U
#define SYSTIM_DESC_MAJREV_MINIMUM                                   0x00000000U
#define SYSTIM_DESC_MAJREV_MAXIMUM                                   0x000000F0U
/*

        Field:           INSTIDX
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     If multiple instances of IP exists in SOC, this field can identify the instance number 0-15

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_DESC_INSTIDX_W                                        4U
#define SYSTIM_DESC_INSTIDX_M                                        0x00000F00U
#define SYSTIM_DESC_INSTIDX_S                                        8U
#define SYSTIM_DESC_INSTIDX_MINIMUM                                  0x00000000U
#define SYSTIM_DESC_INSTIDX_MAXIMUM                                  0x00000F00U
/*

        Field:           STDIPOFF
        From..to bits:   12...15
        DefaultValue:    0x1
        Access type:     read-only
        Description:     64 B standard IP MMR block (beginning with aggregated IRQ registers)

                         0: STDIP MMRs do not exist
                         1:15: These MMRs begin at offset 64*STDIPOFF from IP base address

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_DESC_STDIPOFF_W                                       4U
#define SYSTIM_DESC_STDIPOFF_M                                       0x0000F000U
#define SYSTIM_DESC_STDIPOFF_S                                       12U
#define SYSTIM_DESC_STDIPOFF_MINIMUM                                 0x00000000U
#define SYSTIM_DESC_STDIPOFF_MAXIMUM                                 0x0000F000U
/*

        Field:           MODID
        From..to bits:   16...31
        DefaultValue:    0x9443
        Access type:     read-only
        Description:     Module identifier MODID[15:0]. Used to uniquely identify this IP. See comment about derivation below

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_DESC_MODID_W                                          16U
#define SYSTIM_DESC_MODID_M                                          0xFFFF0000U
#define SYSTIM_DESC_MODID_S                                          16U
#define SYSTIM_DESC_MODID_MINIMUM                                    0x00000000U
#define SYSTIM_DESC_MODID_MAXIMUM                                    0xFFFF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IBM
    Offset name:         SYSTIM_O_IBM
    Relative address:    0x44
    Description:         INTERRUPT BIT MASK

                        Interrupt Mask. If a bit is cleared, then corresponding interrupt is masked.
    Default Value:       0x00000000

        Field:           EVT0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Mask EVENT0 in MIS register.

        ENUMs:
            CLR:                         Clear Interrupt Mask
            SET:                         Set Interrupt Mask
*/
#define SYSTIM_IBM_EVT0                                              0x00000001U
#define SYSTIM_IBM_EVT0_M                                            0x00000001U
#define SYSTIM_IBM_EVT0_S                                            0U
#define SYSTIM_IBM_EVT0_CLR                                          0x00000000U
#define SYSTIM_IBM_EVT0_SET                                          0x00000001U
/*

        Field:           EVT1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Mask EVENT1 in MIS register.

        ENUMs:
            CLR:                         Clear Interrupt Mask
            SET:                         Set Interrrupt Mask
*/
#define SYSTIM_IBM_EVT1                                              0x00000002U
#define SYSTIM_IBM_EVT1_M                                            0x00000002U
#define SYSTIM_IBM_EVT1_S                                            1U
#define SYSTIM_IBM_EVT1_CLR                                          0x00000000U
#define SYSTIM_IBM_EVT1_SET                                          0x00000002U
/*

        Field:           OVFL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Mask Timer Overflow Event in MIS register.

        ENUMs:
            CLR:                         Clear Interrupt Mask
            SET:                         Set Interrrupt Mask
*/
#define SYSTIM_IBM_OVFL                                              0x00000040U
#define SYSTIM_IBM_OVFL_M                                            0x00000040U
#define SYSTIM_IBM_OVFL_S                                            6U
#define SYSTIM_IBM_OVFL_CLR                                          0x00000000U
#define SYSTIM_IBM_OVFL_SET                                          0x00000040U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RIS
    Offset name:         SYSTIM_O_RIS
    Relative address:    0x48
    Description:         Raw interrupt status reflects all pending interrupts, regardless of masking. The RIS register allows the user to implement a poll scheme. A flag set in this register can be cleared by writing 1 to the ICLR register bit even if the corresponding IMASK bit is not enabled.
    Default Value:       0x00000000

        Field:           EVT0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for EVENT0.


                         This bit is set to 1 when an event is received on EVENT0 channel.

        ENUMs:
            CLR:                         Interrupt did not occur
            SET:                         Interrupt occured
*/
#define SYSTIM_RIS_EVT0                                              0x00000001U
#define SYSTIM_RIS_EVT0_M                                            0x00000001U
#define SYSTIM_RIS_EVT0_S                                            0U
#define SYSTIM_RIS_EVT0_CLR                                          0x00000000U
#define SYSTIM_RIS_EVT0_SET                                          0x00000001U
/*

        Field:           EVT1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for EVENT1.


                         This bit is set to 1 when an event is received on EVENT1 channel.

        ENUMs:
            CLR:                         Interrupt did not occur
            SET:                         Interrupt occured
*/
#define SYSTIM_RIS_EVT1                                              0x00000002U
#define SYSTIM_RIS_EVT1_M                                            0x00000002U
#define SYSTIM_RIS_EVT1_S                                            1U
#define SYSTIM_RIS_EVT1_CLR                                          0x00000000U
#define SYSTIM_RIS_EVT1_SET                                          0x00000002U
/*

        Field:           OVFL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for Timer Overflow EVENT.


                         This bit is set to 1 when an event is received on Timer Ovreflow EVENT channel.

        ENUMs:
            CLR:                         Interrupt did not occur
            SET:                         Interrupt occured
*/
#define SYSTIM_RIS_OVFL                                              0x00000040U
#define SYSTIM_RIS_OVFL_M                                            0x00000040U
#define SYSTIM_RIS_OVFL_S                                            6U
#define SYSTIM_RIS_OVFL_CLR                                          0x00000000U
#define SYSTIM_RIS_OVFL_SET                                          0x00000040U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MIS
    Offset name:         SYSTIM_O_MIS
    Relative address:    0x4C
    Description:         Masked interrupt status. This is an AND of the IMASK and RIS registers.
    Default Value:       0x00000000

        Field:           EVT0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Mask interrupt status for EVENT0

        ENUMs:
            CLR:                         Interrupt did not occur
            SET:                         Interrupt occured
*/
#define SYSTIM_MIS_EVT0                                              0x00000001U
#define SYSTIM_MIS_EVT0_M                                            0x00000001U
#define SYSTIM_MIS_EVT0_S                                            0U
#define SYSTIM_MIS_EVT0_CLR                                          0x00000000U
#define SYSTIM_MIS_EVT0_SET                                          0x00000001U
/*

        Field:           EVT1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Mask interrupt status for EVENT1

        ENUMs:
            CLR:                         Interrupt did not occur
            SET:                         Interrupt occured
*/
#define SYSTIM_MIS_EVT1                                              0x00000002U
#define SYSTIM_MIS_EVT1_M                                            0x00000002U
#define SYSTIM_MIS_EVT1_S                                            1U
#define SYSTIM_MIS_EVT1_CLR                                          0x00000000U
#define SYSTIM_MIS_EVT1_SET                                          0x00000002U
/*

        Field:           OVFL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Mask Interrupt Status Timer Overflow Event in MIS register.

        ENUMs:
            CLR:                         Interrupt did not occur
            SET:                         Interrupt occured
*/
#define SYSTIM_MIS_OVFL                                              0x00000040U
#define SYSTIM_MIS_OVFL_M                                            0x00000040U
#define SYSTIM_MIS_OVFL_S                                            6U
#define SYSTIM_MIS_OVFL_CLR                                          0x00000000U
#define SYSTIM_MIS_OVFL_SET                                          0x00000040U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ISET
    Offset name:         SYSTIM_O_ISET
    Relative address:    0x50
    Description:         Interrupt set. Allows interrupts to be set by software (useful in diagnostics and safety checks). Writing a 1 to a bit in ISET will set the event and therefore the related RIS bit also gets set. If the interrupt is enabled through the mask, then the corresponding MIS bit is also set.
    Default Value:       0x00000000

        Field:           EVT0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Sets channel0 EVENT in RIS


        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            SET:                         Set Interrupt
*/
#define SYSTIM_ISET_EVT0                                             0x00000001U
#define SYSTIM_ISET_EVT0_M                                           0x00000001U
#define SYSTIM_ISET_EVT0_S                                           0U
#define SYSTIM_ISET_EVT0_NO_EFFECT                                   0x00000000U
#define SYSTIM_ISET_EVT0_SET                                         0x00000001U
/*

        Field:           EVT1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Sets channel1 EVENT in RIS

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            SET:                         Set Interrupt
*/
#define SYSTIM_ISET_EVT1                                             0x00000002U
#define SYSTIM_ISET_EVT1_M                                           0x00000002U
#define SYSTIM_ISET_EVT1_S                                           1U
#define SYSTIM_ISET_EVT1_NO_EFFECT                                   0x00000000U
#define SYSTIM_ISET_EVT1_SET                                         0x00000002U
/*

        Field:           OVFL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Sets Timer Overflow EVENT in RIS

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            SET:                         Set Interrupt
*/
#define SYSTIM_ISET_OVFL                                             0x00000040U
#define SYSTIM_ISET_OVFL_M                                           0x00000040U
#define SYSTIM_ISET_OVFL_S                                           6U
#define SYSTIM_ISET_OVFL_NO_EFFECT                                   0x00000000U
#define SYSTIM_ISET_OVFL_SET                                         0x00000040U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ICLR
    Offset name:         SYSTIM_O_ICLR
    Relative address:    0x54
    Description:         Interrupt clear. Write a 1 to clear corresponding Interrupt.
    Default Value:       0x00000000

        Field:           EVT0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clears EVENT0 in RIS

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            CLR:                         Clear Interrupt
*/
#define SYSTIM_ICLR_EVT0                                             0x00000001U
#define SYSTIM_ICLR_EVT0_M                                           0x00000001U
#define SYSTIM_ICLR_EVT0_S                                           0U
#define SYSTIM_ICLR_EVT0_NO_EFFECT                                   0x00000000U
#define SYSTIM_ICLR_EVT0_CLR                                         0x00000001U
/*

        Field:           EVT1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clears EVENT1 in RIS

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            CLR:                         Clear Interrupt
*/
#define SYSTIM_ICLR_EVT1                                             0x00000002U
#define SYSTIM_ICLR_EVT1_M                                           0x00000002U
#define SYSTIM_ICLR_EVT1_S                                           1U
#define SYSTIM_ICLR_EVT1_NO_EFFECT                                   0x00000000U
#define SYSTIM_ICLR_EVT1_CLR                                         0x00000002U
/*

        Field:           OVFL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Overflow

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            CLR:                         Clear Interrupt
*/
#define SYSTIM_ICLR_OVFL                                             0x00000040U
#define SYSTIM_ICLR_OVFL_M                                           0x00000040U
#define SYSTIM_ICLR_OVFL_S                                           6U
#define SYSTIM_ICLR_OVFL_NO_EFFECT                                   0x00000000U
#define SYSTIM_ICLR_OVFL_CLR                                         0x00000040U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMSET
    Offset name:         SYSTIM_O_IMSET
    Relative address:    0x58
    Description:         Interrupt mask set. Writing a 1 to a bit in IMSET will set the related IMASK bit.
    Default Value:       0x00000000

        Field:           EVT0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Sets channel0 Event

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            SET:                         Set interrupt mask
*/
#define SYSTIM_IMSET_EVT0                                            0x00000001U
#define SYSTIM_IMSET_EVT0_M                                          0x00000001U
#define SYSTIM_IMSET_EVT0_S                                          0U
#define SYSTIM_IMSET_EVT0_NO_EFFECT                                  0x00000000U
#define SYSTIM_IMSET_EVT0_SET                                        0x00000001U
/*

        Field:           EVT1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Sets channel1 Event

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            SET:                         Set interrupt mask
*/
#define SYSTIM_IMSET_EVT1                                            0x00000002U
#define SYSTIM_IMSET_EVT1_M                                          0x00000002U
#define SYSTIM_IMSET_EVT1_S                                          1U
#define SYSTIM_IMSET_EVT1_NO_EFFECT                                  0x00000000U
#define SYSTIM_IMSET_EVT1_SET                                        0x00000002U
/*

        Field:           OVFL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Sets Timer Overflow Event.

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            SET:                         Set interrupt mask
*/
#define SYSTIM_IMSET_OVFL                                            0x00000040U
#define SYSTIM_IMSET_OVFL_M                                          0x00000040U
#define SYSTIM_IMSET_OVFL_S                                          6U
#define SYSTIM_IMSET_OVFL_NO_EFFECT                                  0x00000000U
#define SYSTIM_IMSET_OVFL_SET                                        0x00000040U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMCLR
    Offset name:         SYSTIM_O_IMCLR
    Relative address:    0x5C
    Description:         Interrupt mask clear. Writing a 1 to a bit in IMCLR will clear the related IMASK bit.
    Default Value:       0x00000000

        Field:           EVT0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clears channel0 Event.

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            CLR:                         Clear interrupt mask
*/
#define SYSTIM_IMCLR_EVT0                                            0x00000001U
#define SYSTIM_IMCLR_EVT0_M                                          0x00000001U
#define SYSTIM_IMCLR_EVT0_S                                          0U
#define SYSTIM_IMCLR_EVT0_NO_EFFECT                                  0x00000000U
#define SYSTIM_IMCLR_EVT0_CLR                                        0x00000001U
/*

        Field:           EVT1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clears channel1 Event.

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            CLR:                         Clear interrupt mask
*/
#define SYSTIM_IMCLR_EVT1                                            0x00000002U
#define SYSTIM_IMCLR_EVT1_M                                          0x00000002U
#define SYSTIM_IMCLR_EVT1_S                                          1U
#define SYSTIM_IMCLR_EVT1_NO_EFFECT                                  0x00000000U
#define SYSTIM_IMCLR_EVT1_CLR                                        0x00000002U
/*

        Field:           OVFL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clears Timer Overflow Event.

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            CLR:                         Clear interrupt mask
*/
#define SYSTIM_IMCLR_OVFL                                            0x00000040U
#define SYSTIM_IMCLR_OVFL_M                                          0x00000040U
#define SYSTIM_IMCLR_OVFL_S                                          6U
#define SYSTIM_IMCLR_OVFL_NO_EFFECT                                  0x00000000U
#define SYSTIM_IMCLR_OVFL_CLR                                        0x00000040U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EMU
    Offset name:         SYSTIM_O_EMU
    Relative address:    0x60
    Description:         This register can be used by the software developer to control the behavior of the peripheral relative to the CPU Halted input.
    Default Value:       0x00000000

        Field:           HALT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit controls peripheral behavior at CPU halt condition.

        ENUMs:
            RUN:                         Peripheral ignores the state of the CPU Halted input
            STOP:                        Peripheral freezes functionality immediately or at appropriate time when the CPU Halted input is asserted and resumes when it is deasserted
*/
#define SYSTIM_EMU_HALT                                              0x00000001U
#define SYSTIM_EMU_HALT_M                                            0x00000001U
#define SYSTIM_EMU_HALT_S                                            0U
#define SYSTIM_EMU_HALT_RUN                                          0x00000000U
#define SYSTIM_EMU_HALT_STOP                                         0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DTB
    Offset name:         SYSTIM_O_DTB
    Relative address:    0x64
    Description:         Digital Test Bus. This register is used to bring out some internal signals of the peripheral on digital test bus (DTB).
    Default Value:       0x00000000

        Field:           SEL
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit field is used to select DTB mux digital output signals.

        ENUMs:
            DISABLE:                     DTB output from peripheral is 0x0.
            GRP1:                        Selects test group 1
            GRP2:                        Selects test group 2
            GRP3:                        Selects test group 3
            GRP4:                        Selects test group 4
            GRP5:                        Selects test group 5
            GRP6:                        Selects test group 6
            GRP7:                        Selects test group 7
            GRP8:                        Selects test group 7
            GRP9:                        Selects test group 7
            GRP10:                       Selects test group 7
            GRP11:                       Selects test group 7
            GRP12:                       Selects test group 7
            GRP13:                       Selects test group 7
            GRP14:                       Selects test group 7
            GRP15:                       Selects test group 7
*/
#define SYSTIM_DTB_SEL_W                                             4U
#define SYSTIM_DTB_SEL_M                                             0x0000000FU
#define SYSTIM_DTB_SEL_S                                             0U
#define SYSTIM_DTB_SEL_DISABLE                                       0x00000000U
#define SYSTIM_DTB_SEL_GRP1                                          0x00000001U
#define SYSTIM_DTB_SEL_GRP2                                          0x00000002U
#define SYSTIM_DTB_SEL_GRP3                                          0x00000003U
#define SYSTIM_DTB_SEL_GRP4                                          0x00000004U
#define SYSTIM_DTB_SEL_GRP5                                          0x00000005U
#define SYSTIM_DTB_SEL_GRP6                                          0x00000006U
#define SYSTIM_DTB_SEL_GRP7                                          0x00000007U
#define SYSTIM_DTB_SEL_GRP8                                          0x00000008U
#define SYSTIM_DTB_SEL_GRP9                                          0x00000009U
#define SYSTIM_DTB_SEL_GRP10                                         0x0000000AU
#define SYSTIM_DTB_SEL_GRP11                                         0x0000000BU
#define SYSTIM_DTB_SEL_GRP12                                         0x0000000CU
#define SYSTIM_DTB_SEL_GRP13                                         0x0000000DU
#define SYSTIM_DTB_SEL_GRP14                                         0x0000000EU
#define SYSTIM_DTB_SEL_GRP15                                         0x0000000FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       TIME250N
    Offset name:         SYSTIM_O_TIME250N
    Relative address:    0x100
    Description:         Systimer Counter Value[31:0]. Time with 250ns resolution from systimer
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Counter Value. This is not writable while the systimer counter is enabled

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_TIME250N_VAL_W                                        32U
#define SYSTIM_TIME250N_VAL_M                                        0xFFFFFFFFU
#define SYSTIM_TIME250N_VAL_S                                        0U
#define SYSTIM_TIME250N_VAL_MINIMUM                                  0x00000000U
#define SYSTIM_TIME250N_VAL_MAXIMUM                                  0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       TIME1U
    Offset name:         SYSTIM_O_TIME1U
    Relative address:    0x104
    Description:         Systimer Counter Value[33:2]. Time with 1us resolution from systimer
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Counter Value. This is not writable while the systimer counter is enabled

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_TIME1U_VAL_W                                          32U
#define SYSTIM_TIME1U_VAL_M                                          0xFFFFFFFFU
#define SYSTIM_TIME1U_VAL_S                                          0U
#define SYSTIM_TIME1U_VAL_MINIMUM                                    0x00000000U
#define SYSTIM_TIME1U_VAL_MAXIMUM                                    0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       OUT
    Offset name:         SYSTIM_O_OUT
    Relative address:    0x108
    Description:         SYSTIMER'S Channel Output Event Values
    Default Value:       0x00000000

        Field:           OUT0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Output Value of channel 0.

        ENUMs:
            CLR:                         Event did not occur.
            SET:                         Event occured
*/
#define SYSTIM_OUT_OUT0                                              0x00000001U
#define SYSTIM_OUT_OUT0_M                                            0x00000001U
#define SYSTIM_OUT_OUT0_S                                            0U
#define SYSTIM_OUT_OUT0_CLR                                          0x00000000U
#define SYSTIM_OUT_OUT0_SET                                          0x00000001U
/*

        Field:           OUT1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Output Value of channel 1.

        ENUMs:
            CLR:                         Event did not occur.
            SET:                         Event occured
*/
#define SYSTIM_OUT_OUT1                                              0x00000002U
#define SYSTIM_OUT_OUT1_M                                            0x00000002U
#define SYSTIM_OUT_OUT1_S                                            1U
#define SYSTIM_OUT_OUT1_CLR                                          0x00000000U
#define SYSTIM_OUT_OUT1_SET                                          0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0CFG
    Offset name:         SYSTIM_O_CH0CFG
    Relative address:    0x10C
    Description:         SYSTIMER channel 0 configuration
    Default Value:       0x00000000

        Field:           MODE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Decides the channel mode.

        ENUMs:
            DIS:                         Channel is disabled
            CAPT:                        Channel is in capture mode
*/
#define SYSTIM_CH0CFG_MODE                                           0x00000001U
#define SYSTIM_CH0CFG_MODE_M                                         0x00000001U
#define SYSTIM_CH0CFG_MODE_S                                         0U
#define SYSTIM_CH0CFG_MODE_DIS                                       0x00000000U
#define SYSTIM_CH0CFG_MODE_CAPT                                      0x00000001U
/*

        Field:           INP
        From..to bits:   1...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Decides the channel input signal's mode. Setting the Value as 2'b11 selects the Rise Function.

        ENUMs:
            RISE:                        Capture on rising edge
            FALL:                        Capture on Falling Edge
            BOTH:                        Capture on both Edge
*/
#define SYSTIM_CH0CFG_INP_W                                          2U
#define SYSTIM_CH0CFG_INP_M                                          0x00000006U
#define SYSTIM_CH0CFG_INP_S                                          1U
#define SYSTIM_CH0CFG_INP_RISE                                       0x00000000U
#define SYSTIM_CH0CFG_INP_FALL                                       0x00000002U
#define SYSTIM_CH0CFG_INP_BOTH                                       0x00000004U
/*

        Field:           REARM
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     When Rearm is enabled the channel remains in continuous capture mode. Otherwise it'll be in One shot capture mode. Rearm is only valid for capture mode.

        ENUMs:
            EN:                          Re arm is enabled
            NS:                          Re Arm is disabled
*/
#define SYSTIM_CH0CFG_REARM                                          0x00000008U
#define SYSTIM_CH0CFG_REARM_M                                        0x00000008U
#define SYSTIM_CH0CFG_REARM_S                                        3U
#define SYSTIM_CH0CFG_REARM_EN                                       0x00000008U
#define SYSTIM_CH0CFG_REARM_NS                                       0x00000000U
/*

        Field:           RES
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit decides the RESOLUTION of the channel that will be used.

        ENUMs:
            US:                          Channel Works in Timer's 1us Resolution.
            NS:                          Channel Works in Timer's 250ns resolution
*/
#define SYSTIM_CH0CFG_RES                                            0x00000010U
#define SYSTIM_CH0CFG_RES_M                                          0x00000010U
#define SYSTIM_CH0CFG_RES_S                                          4U
#define SYSTIM_CH0CFG_RES_US                                         0x00000000U
#define SYSTIM_CH0CFG_RES_NS                                         0x00000010U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1CFG
    Offset name:         SYSTIM_O_CH1CFG
    Relative address:    0x110
    Description:         SYSTIMER channel 1 configuration
    Default Value:       0x00000000

        Field:           MODE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Decides the channel mode.

        ENUMs:
            DIS:                         Channel is disabled

            CAPT:                        Channel is in capture mode

*/
#define SYSTIM_CH1CFG_MODE                                           0x00000001U
#define SYSTIM_CH1CFG_MODE_M                                         0x00000001U
#define SYSTIM_CH1CFG_MODE_S                                         0U
#define SYSTIM_CH1CFG_MODE_DIS                                       0x00000000U
#define SYSTIM_CH1CFG_MODE_CAPT                                      0x00000001U
/*

        Field:           INP
        From..to bits:   1...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Decides the channel input signal's mode. Setting the Value as 2'b11 selects the Rise Function

        ENUMs:
            RISE:                        Capture on rising edge

            FALL:                        Capture on Falling Edge

            BOTH:                        Capture on both Edge

*/
#define SYSTIM_CH1CFG_INP_W                                          2U
#define SYSTIM_CH1CFG_INP_M                                          0x00000006U
#define SYSTIM_CH1CFG_INP_S                                          1U
#define SYSTIM_CH1CFG_INP_RISE                                       0x00000000U
#define SYSTIM_CH1CFG_INP_FALL                                       0x00000002U
#define SYSTIM_CH1CFG_INP_BOTH                                       0x00000004U
/*

        Field:           REARM
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     When Rearm is enabled the channel remains in continous capture mode. Otherwise it'll be in One shot capture mode. Rearm is only valid for capture mode.

        ENUMs:
            EN:                          Re arm is enabled
            NS:                          Re Arm is disabled
*/
#define SYSTIM_CH1CFG_REARM                                          0x00000008U
#define SYSTIM_CH1CFG_REARM_M                                        0x00000008U
#define SYSTIM_CH1CFG_REARM_S                                        3U
#define SYSTIM_CH1CFG_REARM_EN                                       0x00000008U
#define SYSTIM_CH1CFG_REARM_NS                                       0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0CC
    Offset name:         SYSTIM_O_CH0CC
    Relative address:    0x120
    Description:         System Timer Channel 0 Capture/Compare Register. This Register when written with any compare value will arm the channel to work in compare mode.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture/compare value

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_CH0CC_VAL_W                                           32U
#define SYSTIM_CH0CC_VAL_M                                           0xFFFFFFFFU
#define SYSTIM_CH0CC_VAL_S                                           0U
#define SYSTIM_CH0CC_VAL_MINIMUM                                     0x00000000U
#define SYSTIM_CH0CC_VAL_MAXIMUM                                     0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1CC
    Offset name:         SYSTIM_O_CH1CC
    Relative address:    0x124
    Description:         System Timer Channel 1 Capture/Compare Register. This Register when written with any compare value will arm the channel to work in compare mode.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture/compare value

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_CH1CC_VAL_W                                           32U
#define SYSTIM_CH1CC_VAL_M                                           0xFFFFFFFFU
#define SYSTIM_CH1CC_VAL_S                                           0U
#define SYSTIM_CH1CC_VAL_MINIMUM                                     0x00000000U
#define SYSTIM_CH1CC_VAL_MAXIMUM                                     0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       TIMEBIT
    Offset name:         SYSTIM_O_TIMEBIT
    Relative address:    0x134
    Description:         This Register will be used to specify which TIME bit is required by LGPT to be forwarded from SYSTIMER.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The corresponding bit will have value '1' rest should be '0'. If more than one bit is asserted, output is "or" of all the bits.

        ENUMs:
            NOBIT:                       No bit is forwarded to the event fabric.
            BIT3:                        Bit3 is forwarded to the event fabric.
            BIT4:                        Bit4 is forwarded to the event fabric.
            BIT5:                        Bit5 is forwarded to the event fabric.
            BIT6:                        Bit6 is forwarded to the event fabric.
            BIT7:                        Bit7 is forwarded to the event fabric.
            BIT8:                        Bit8 is forwarded to the event fabric.
            BIT9:                        Bit9 is forwarded to the event fabric.
            BIT10:                       Bit10 is forwarded to the event fabric.
            BIT11:                       Bit11 is forwarded to the event fabric.
            BIT12:                       Bit12 is forwarded to the event fabric.
            BIT13:                       Bit13 is forwarded to the event fabric.
            BIT14:                       Bit14 is forwarded to the event fabric.
            BIT15:                       Bit15 is forwarded to the event fabric.
            BIT16:                       Bit16 is forwarded to the event fabric.
            BIT17:                       Bit17 is forwarded to the event fabric.
            BIT2:                        Bit2 is forwarded to the event fabric.
*/
#define SYSTIM_TIMEBIT_VAL_W                                         16U
#define SYSTIM_TIMEBIT_VAL_M                                         0x0000FFFFU
#define SYSTIM_TIMEBIT_VAL_S                                         0U
#define SYSTIM_TIMEBIT_VAL_NOBIT                                     0x00000000U
#define SYSTIM_TIMEBIT_VAL_BIT3                                      0x00000002U
#define SYSTIM_TIMEBIT_VAL_BIT4                                      0x00000004U
#define SYSTIM_TIMEBIT_VAL_BIT5                                      0x00000008U
#define SYSTIM_TIMEBIT_VAL_BIT6                                      0x00000010U
#define SYSTIM_TIMEBIT_VAL_BIT7                                      0x00000020U
#define SYSTIM_TIMEBIT_VAL_BIT8                                      0x00000040U
#define SYSTIM_TIMEBIT_VAL_BIT9                                      0x00000080U
#define SYSTIM_TIMEBIT_VAL_BIT10                                     0x00000100U
#define SYSTIM_TIMEBIT_VAL_BIT11                                     0x00000200U
#define SYSTIM_TIMEBIT_VAL_BIT12                                     0x00000400U
#define SYSTIM_TIMEBIT_VAL_BIT13                                     0x00000800U
#define SYSTIM_TIMEBIT_VAL_BIT14                                     0x00001000U
#define SYSTIM_TIMEBIT_VAL_BIT15                                     0x00002000U
#define SYSTIM_TIMEBIT_VAL_BIT16                                     0x00004000U
#define SYSTIM_TIMEBIT_VAL_BIT17                                     0x00008000U
#define SYSTIM_TIMEBIT_VAL_BIT2                                      0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       KP
    Offset name:         SYSTIM_O_KP
    Relative address:    0x138
    Description:         PI filter's Proportional Gain Value
    Default Value:       0x00000004

        Field:           VAL
        From..to bits:   0...3
        DefaultValue:    0x4
        Access type:     read-write
        Description:     Proportional Error is left shifted by this value.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_KP_VAL_W                                              4U
#define SYSTIM_KP_VAL_M                                              0x0000000FU
#define SYSTIM_KP_VAL_S                                              0U
#define SYSTIM_KP_VAL_MINIMUM                                        0x00000000U
#define SYSTIM_KP_VAL_MAXIMUM                                        0x0000000FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       KI
    Offset name:         SYSTIM_O_KI
    Relative address:    0x13C
    Description:         PI filter's Accumulator's Gain Value
    Default Value:       0x00000001

        Field:           VAL
        From..to bits:   0...3
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Accumulated Error is left shifted by this value.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_KI_VAL_W                                              4U
#define SYSTIM_KI_VAL_M                                              0x0000000FU
#define SYSTIM_KI_VAL_S                                              0U
#define SYSTIM_KI_VAL_MINIMUM                                        0x00000000U
#define SYSTIM_KI_VAL_MAXIMUM                                        0x0000000FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STA
    Offset name:         SYSTIM_O_STA
    Relative address:    0x140
    Description:         STATUS

                        This is the system timer status register.
    Default Value:       0x00000010

        Field:           VAL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:      This bit indicates if the system time is initialized and running.

        ENUMs:
            STOP:                        system timer is not running.
            RUN:                         system timer is running
*/
#define SYSTIM_STA_VAL                                               0x00000001U
#define SYSTIM_STA_VAL_M                                             0x00000001U
#define SYSTIM_STA_VAL_S                                             0U
#define SYSTIM_STA_VAL_STOP                                          0x00000000U
#define SYSTIM_STA_VAL_RUN                                           0x00000001U
/*

        Field:           SYNCUP
        From..to bits:   4...4
        DefaultValue:    0x1
        Access type:     read-only
        Description:     This bit indicates the status of resyncup of systimer with RTC. The bitfield has a reset value of '1' , as out of reset the systimer syncs up with RTC, after the first_synced_lftick occurs the SYNCUP bit goes to zero.

        ENUMs:
            CLR:                         SYNC UP with RTC is not happening
            SET:                         Any write to STATUS register, triggers the SYNCUP with RTC and this bit is set.
*/
#define SYSTIM_STA_SYNCUP                                            0x00000010U
#define SYSTIM_STA_SYNCUP_M                                          0x00000010U
#define SYSTIM_STA_SYNCUP_S                                          4U
#define SYSTIM_STA_SYNCUP_CLR                                        0x00000000U
#define SYSTIM_STA_SYNCUP_SET                                        0x00000010U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ARMSET
    Offset name:         SYSTIM_O_ARMSET
    Relative address:    0x144
    Description:         ARMSET on read gives out the status of the 2 channels
                        	1.	Channel state UNARMED returns 0
                        	2.	Channel state CAPTURE or COMPARE returns 1
                        A write to ARMSET has for each channel the following effect:
                        1.	If ARMSTA[x]==0  -> no effect
                        2.	If ARMSTA[x]==1 and channel x is in CAPTURE state then no effect on the channel
                        3.	Else Set channel in COMPARE mode using existing CHxVAL value
    Default Value:       0x00000000

        Field:           CH0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Arming Channel 0 for either compare or capture operation.

        ENUMs:
            NOEFFECT:                    No effect on the channel
            SET:                         if channel 0 is in CAPTURE state then no effect on the channel
                         3.	Else ; Set channel in COMPARE mode using existing CH0VAL value
*/
#define SYSTIM_ARMSET_CH0                                            0x00000001U
#define SYSTIM_ARMSET_CH0_M                                          0x00000001U
#define SYSTIM_ARMSET_CH0_S                                          0U
#define SYSTIM_ARMSET_CH0_NOEFFECT                                   0x00000000U
#define SYSTIM_ARMSET_CH0_SET                                        0x00000001U
/*

        Field:           CH1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Arming Channel 1 for either compare or capture operation.

        ENUMs:
            NOEFFECT:                    No effect on the channel
            SET:                         if channel 1 is in CAPTURE state then no effect on the channel Else ; Set channel in COMPARE mode using existing CH1VAL value
*/
#define SYSTIM_ARMSET_CH1                                            0x00000002U
#define SYSTIM_ARMSET_CH1_M                                          0x00000002U
#define SYSTIM_ARMSET_CH1_S                                          1U
#define SYSTIM_ARMSET_CH1_NOEFFECT                                   0x00000000U
#define SYSTIM_ARMSET_CH1_SET                                        0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ARMCLR
    Offset name:         SYSTIM_O_ARMCLR
    Relative address:    0x148
    Description:         ARMCLR on read gives out the status of the 2 channels
                        	1.	Channel state UNARMED returns 0
                        	2.	Channel state CAPTURE or COMPARE returns 1
                        A write to ARMCLR has for each channel the following effect:
                        	1.	If ARMCLR[x]==0 no effect
                        	2.	Else Set channel in UNARMED state without triggering event unless a compare/capture event happens in the same cycle
    Default Value:       0x00000000

        Field:           CH0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Disarming Channel 0

        ENUMs:
            NOEFFECT:                    No effect on the channel
            CLR:                         Set channel in UNARMED state without triggering event unless a compare/capture event happens in the same cycle
*/
#define SYSTIM_ARMCLR_CH0                                            0x00000001U
#define SYSTIM_ARMCLR_CH0_M                                          0x00000001U
#define SYSTIM_ARMCLR_CH0_S                                          0U
#define SYSTIM_ARMCLR_CH0_NOEFFECT                                   0x00000000U
#define SYSTIM_ARMCLR_CH0_CLR                                        0x00000001U
/*

        Field:           CH1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Disarming Channel 1

        ENUMs:
            NOEFFECT:                    No effect on the channel
            CLR:                         Set channel in UNARMED state without triggering event unless a compare/capture event happens in the same cycle
*/
#define SYSTIM_ARMCLR_CH1                                            0x00000002U
#define SYSTIM_ARMCLR_CH1_M                                          0x00000002U
#define SYSTIM_ARMCLR_CH1_S                                          1U
#define SYSTIM_ARMCLR_CH1_NOEFFECT                                   0x00000000U
#define SYSTIM_ARMCLR_CH1_CLR                                        0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0CCSR
    Offset name:         SYSTIM_O_CH0CCSR
    Relative address:    0x14C
    Description:         Save/restore alias registers Channel 0. i.	A read to CH0SR behaves exactly as a read to CH0VAL.
                        A write to CH0SR sets CH0VAL value of register without affecting channel state or configuration
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture/compare value

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_CH0CCSR_VAL_W                                         32U
#define SYSTIM_CH0CCSR_VAL_M                                         0xFFFFFFFFU
#define SYSTIM_CH0CCSR_VAL_S                                         0U
#define SYSTIM_CH0CCSR_VAL_MINIMUM                                   0x00000000U
#define SYSTIM_CH0CCSR_VAL_MAXIMUM                                   0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1CCSR
    Offset name:         SYSTIM_O_CH1CCSR
    Relative address:    0x150
    Description:         Save/restore alias registers Channel 1. i.	A read to CH1SR behaves exactly as a read to CH1VAL.
                        A write to CH1SR sets CH1VAL value of register without affecting channel state or configuration.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture/compare value

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_CH1CCSR_VAL_W                                         32U
#define SYSTIM_CH1CCSR_VAL_M                                         0xFFFFFFFFU
#define SYSTIM_CH1CCSR_VAL_S                                         0U
#define SYSTIM_CH1CCSR_VAL_MINIMUM                                   0x00000000U
#define SYSTIM_CH1CCSR_VAL_MAXIMUM                                   0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCFG
    Offset name:         SYSTIM_O_CLKCFG
    Relative address:    0x1000
    Description:         CLOCK CONFIG
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ENABLE

                         '1' - enable systimer clk
                         '0' - disable systimer clk

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define SYSTIM_CLKCFG_EN                                             0x00000001U
#define SYSTIM_CLKCFG_EN_M                                           0x00000001U
#define SYSTIM_CLKCFG_EN_S                                           0U
#define SYSTIM_CLKCFG_EN_MINIMUM                                     0x00000000U
#define SYSTIM_CLKCFG_EN_MAXIMUM                                     0xFFFFFFFFU

#endif /* __HW_SYSTIM_H__*/
