/******************************************************************************
*  Filename:       hw_wsoc_ocla.h
*
*  Description:    Defines and prototypes for the WSOC_OCLA peripheral.
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
#ifndef __HW_WSOC_OCLA_H__
#define __HW_WSOC_OCLA_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the WSOC_OCLA component

--------------------------------------------------------------------------------- */

//Events Mode and Source
#define WSOC_OCLA_O_EVTMOD                                           0x00000000U

//OCLA Event A Mask
#define WSOC_OCLA_O_AMASK                                            0x00000004U

//OCLA Event A Compare
#define WSOC_OCLA_O_ACOMP                                            0x00000008U

//OCLA Event B Mask
#define WSOC_OCLA_O_BMASK                                            0x0000000CU

//OCLA Event B Compare
#define WSOC_OCLA_O_BCOMP                                            0x00000010U

//OCLA Event C Mask
#define WSOC_OCLA_O_CMASK                                            0x00000014U

//OCLA Event C Compare
#define WSOC_OCLA_O_CCOMP                                            0x00000018U

//OCLA Event F Mask
#define WSOC_OCLA_O_FMASK                                            0x0000002CU

//OCLA Event F Compare
#define WSOC_OCLA_O_FCOMP                                            0x00000030U

//make sub trigger from the events (A,B,C,D,E,F)
#define WSOC_OCLA_O_SUBTRIGX                                         0x00000034U

//make sub trigger from the events (A,B,C,D,E,F)
#define WSOC_OCLA_O_SUBTRIGY                                         0x00000038U

//make sub trigger from the events (A,B,C,D,E,F)
#define WSOC_OCLA_O_SUBTRIGZ                                         0x0000003CU

//OCLA Clk Configuration
#define WSOC_OCLA_O_CLKCFG                                           0x00000040U

//Triggers
#define WSOC_OCLA_O_TRIGS                                            0x00000044U

//OCLA Time
#define WSOC_OCLA_O_TIME                                             0x00000048U

//main mode configurations, memory params, and output params
#define WSOC_OCLA_O_MODE                                             0x0000004CU

//OCLA Memory Size
#define WSOC_OCLA_O_MEMSIZE                                          0x00000050U

//Memory Size After Event
#define WSOC_OCLA_O_MEMSIZEEVT                                       0x00000054U

//Memory SW Info
#define WSOC_OCLA_O_MEMSWINF                                         0x00000058U

//Hold the pointer to the place in memory which event happened
#define WSOC_OCLA_O_STATESTA                                         0x0000005CU

//Read Debug 0
#define WSOC_OCLA_O_RDDBG0                                           0x00000060U

//Read Debug 1
#define WSOC_OCLA_O_RDDBG1                                           0x00000064U

//Read Max Time
#define WSOC_OCLA_O_RDMAXTIME                                        0x0000006CU

//Memory Start Address
#define WSOC_OCLA_O_MEMCTL                                           0x00000070U

//OCLA Inject Control
#define WSOC_OCLA_O_INJECTCTL                                        0x00000074U

//Debug Port CFG 0
#define WSOC_OCLA_O_PORTCFG0                                         0x00000078U

//Debug Port CFG 1
#define WSOC_OCLA_O_PORTCFG1                                         0x0000007CU

//Debug Port CFG 2
#define WSOC_OCLA_O_PORTCFG2                                         0x00000080U

//Debug Port CFG 3
#define WSOC_OCLA_O_PORTCFG3                                         0x00000084U

//Debug Port CFG 4
#define WSOC_OCLA_O_PORTCFG4                                         0x00000088U

//Debug Port TP1 or TP2
#define WSOC_OCLA_O_TPSEL                                            0x0000008CU

//Debug Port Selector
#define WSOC_OCLA_O_PORTSEL                                          0x00000090U

//Debug Out Selector
#define WSOC_OCLA_O_OUTSEL                                           0x00000094U

//GPIO Out Value
#define WSOC_OCLA_O_OUTVAL                                           0x00000098U

//GPIO Out Value Set
#define WSOC_OCLA_O_OUTVALSET                                        0x0000009CU

//GPIO Out Value Clear
#define WSOC_OCLA_O_OUTVALCLR                                        0x000000A0U

//GPIO Out Value Toggle
#define WSOC_OCLA_O_OUTVALTGL                                        0x000000A4U

//GPIO Out Value Pulse
#define WSOC_OCLA_O_OUTVALPLS                                        0x000000A8U

//TSF on Trigger
#define WSOC_OCLA_O_TFSONTRG                                         0x000000B0U



/*-----------------------------------REGISTER------------------------------------
    Register name:       EVTMOD
    Offset name:         WSOC_OCLA_O_EVTMOD
    Relative address:    0x0
    Description:         Events Mode and Source.
    Default Value:       0x00000000

        Field:           ASRC
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which part of the monitor bus enter event A:
                                0x0. event_a_input = mon_in_en[31:0];
                                0x1. event_a_input = mon_in_en[47:16];
                                0x2. event_a_input = mon_in_en[63:32];
                                0x3. event_a_input = mon_in_en[79:48];
                                0x4. event_a_input = mon_in_en[95:64];
                                0x5. event_a_input = {mon_in_en[95:80], mon_in_en[15:0]};

*/
#define WSOC_OCLA_EVTMOD_ASRC_W                                      3U
#define WSOC_OCLA_EVTMOD_ASRC_M                                      0x00000007U
#define WSOC_OCLA_EVTMOD_ASRC_S                                      0U
/*

        Field:           AMOD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Event A mode:

                         0. Equal
                         1. Great then

*/
#define WSOC_OCLA_EVTMOD_AMOD                                        0x00000008U
#define WSOC_OCLA_EVTMOD_AMOD_M                                      0x00000008U
#define WSOC_OCLA_EVTMOD_AMOD_S                                      3U
/*

        Field:           BSRC
        From..to bits:   4...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which part of the monitor bus enter event B:
                                0x0. event_b_input = mon_in_en[31:0];
                                0x1. event_b_input = mon_in_en[47:16];
                                0x2. event_b_input = mon_in_en[63:32];
                                0x3. event_b_input = mon_in_en[79:48];
                                0x4. event_b_input = mon_in_en[95:64];
                                0x5. event_b_input = {mon_in_en[95:80], mon_in_en[15:0]};

*/
#define WSOC_OCLA_EVTMOD_BSRC_W                                      3U
#define WSOC_OCLA_EVTMOD_BSRC_M                                      0x00000070U
#define WSOC_OCLA_EVTMOD_BSRC_S                                      4U
/*

        Field:           BMOD
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Event B mode:

                         0. Equal
                         1. Great then

*/
#define WSOC_OCLA_EVTMOD_BMOD                                        0x00000080U
#define WSOC_OCLA_EVTMOD_BMOD_M                                      0x00000080U
#define WSOC_OCLA_EVTMOD_BMOD_S                                      7U
/*

        Field:           CSRC
        From..to bits:   8...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which part of the monitor bus enter event C:
                                0x0. event_c_input = mon_in_en[31:0];
                                0x1. event_c_input = mon_in_en[47:16];
                                0x2. event_c_input = mon_in_en[63:32];
                                0x3. event_c_input = mon_in_en[79:48];
                                0x4. event_c_input = mon_in_en[95:64];
                                0x5. event_c_input = {mon_in_en[95:80], mon_in_en[15:0]};

*/
#define WSOC_OCLA_EVTMOD_CSRC_W                                      3U
#define WSOC_OCLA_EVTMOD_CSRC_M                                      0x00000700U
#define WSOC_OCLA_EVTMOD_CSRC_S                                      8U
/*

        Field:           CMOD
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Event C mode:

                         0. Equal
                         1. Great then

*/
#define WSOC_OCLA_EVTMOD_CMOD                                        0x00000800U
#define WSOC_OCLA_EVTMOD_CMOD_M                                      0x00000800U
#define WSOC_OCLA_EVTMOD_CMOD_S                                      11U
/*

        Field:           DSRC
        From..to bits:   12...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which part of the monitor bus enter event D:
                                0x0. event_d_input = mon_in_en[31:0];
                                0x1. event_d_input = mon_in_en[47:16];
                                0x2. event_d_input = mon_in_en[63:32];
                                0x3. event_d_input = mon_in_en[79:48];
                                0x4. event_d_input = mon_in_en[95:64];
                                0x5. event_d_input = {mon_in_en[95:80], mon_in_en[15:0]};

*/
#define WSOC_OCLA_EVTMOD_DSRC_W                                      3U
#define WSOC_OCLA_EVTMOD_DSRC_M                                      0x00007000U
#define WSOC_OCLA_EVTMOD_DSRC_S                                      12U
/*

        Field:           DMOD
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Event D mode:

                         0. Equal
                         1. Great then

*/
#define WSOC_OCLA_EVTMOD_DMOD                                        0x00008000U
#define WSOC_OCLA_EVTMOD_DMOD_M                                      0x00008000U
#define WSOC_OCLA_EVTMOD_DMOD_S                                      15U
/*

        Field:           ESRC
        From..to bits:   16...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which part of the monitor bus enter event E:
                                0x0. event_e_input = mon_in_en[31:0];
                                0x1. event_e_input = mon_in_en[47:16];
                                0x2. event_e_input = mon_in_en[63:32];
                                0x3. event_e_input = mon_in_en[79:48];
                                0x4. event_e_input = mon_in_en[95:64];
                                0x5. event_e_input = {mon_in_en[95:80], mon_in_en[15:0]};

*/
#define WSOC_OCLA_EVTMOD_ESRC_W                                      3U
#define WSOC_OCLA_EVTMOD_ESRC_M                                      0x00070000U
#define WSOC_OCLA_EVTMOD_ESRC_S                                      16U
/*

        Field:           FSRC
        From..to bits:   20...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which part of the monitor bus enter event F:
                                0x0. event_f_input = mon_in_en[31:0];
                                0x1. event_f_input = mon_in_en[47:16];
                                0x2. event_f_input = mon_in_en[63:32];
                                0x3. event_f_input = mon_in_en[79:48];
                                0x4. event_f_input = mon_in_en[95:64];
                                0x5. event_f_input = {mon_in_en[95:80], mon_in_en[15:0]};

*/
#define WSOC_OCLA_EVTMOD_FSRC_W                                      3U
#define WSOC_OCLA_EVTMOD_FSRC_M                                      0x00700000U
#define WSOC_OCLA_EVTMOD_FSRC_S                                      20U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AMASK
    Offset name:         WSOC_OCLA_O_AMASK
    Relative address:    0x4
    Description:         OCLA Event A Mask.
    Default Value:       0x00000000

        Field:           MASK
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     mask bit which set to 0 is mask

*/
#define WSOC_OCLA_AMASK_MASK_W                                       32U
#define WSOC_OCLA_AMASK_MASK_M                                       0xFFFFFFFFU
#define WSOC_OCLA_AMASK_MASK_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ACOMP
    Offset name:         WSOC_OCLA_O_ACOMP
    Relative address:    0x8
    Description:         OCLA Event A Compare.
    Default Value:       0x00000000

        Field:           COMP
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Compare value for event A

*/
#define WSOC_OCLA_ACOMP_COMP_W                                       32U
#define WSOC_OCLA_ACOMP_COMP_M                                       0xFFFFFFFFU
#define WSOC_OCLA_ACOMP_COMP_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BMASK
    Offset name:         WSOC_OCLA_O_BMASK
    Relative address:    0xC
    Description:         OCLA Event B Mask.
    Default Value:       0x00000000

        Field:           MASK
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     mask bit which set to 0 is mask

*/
#define WSOC_OCLA_BMASK_MASK_W                                       32U
#define WSOC_OCLA_BMASK_MASK_M                                       0xFFFFFFFFU
#define WSOC_OCLA_BMASK_MASK_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BCOMP
    Offset name:         WSOC_OCLA_O_BCOMP
    Relative address:    0x10
    Description:         OCLA Event B Compare.
    Default Value:       0x00000000

        Field:           COMP
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Compare value for event B

*/
#define WSOC_OCLA_BCOMP_COMP_W                                       32U
#define WSOC_OCLA_BCOMP_COMP_M                                       0xFFFFFFFFU
#define WSOC_OCLA_BCOMP_COMP_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CMASK
    Offset name:         WSOC_OCLA_O_CMASK
    Relative address:    0x14
    Description:         OCLA Event C Mask.
    Default Value:       0x00000000

        Field:           MASK
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     mask bit which set to 0 is mask

*/
#define WSOC_OCLA_CMASK_MASK_W                                       32U
#define WSOC_OCLA_CMASK_MASK_M                                       0xFFFFFFFFU
#define WSOC_OCLA_CMASK_MASK_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCOMP
    Offset name:         WSOC_OCLA_O_CCOMP
    Relative address:    0x18
    Description:         OCLA Event C Compare.
    Default Value:       0x00000000

        Field:           COMP
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Compare value for event C

*/
#define WSOC_OCLA_CCOMP_COMP_W                                       32U
#define WSOC_OCLA_CCOMP_COMP_M                                       0xFFFFFFFFU
#define WSOC_OCLA_CCOMP_COMP_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FMASK
    Offset name:         WSOC_OCLA_O_FMASK
    Relative address:    0x2C
    Description:         OCLA Event F Mask.
    Default Value:       0x00000000

        Field:           MASK
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     mask bit which set to 0 is mask

*/
#define WSOC_OCLA_FMASK_MASK_W                                       32U
#define WSOC_OCLA_FMASK_MASK_M                                       0xFFFFFFFFU
#define WSOC_OCLA_FMASK_MASK_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCOMP
    Offset name:         WSOC_OCLA_O_FCOMP
    Relative address:    0x30
    Description:         OCLA Event F Compare.
    Default Value:       0x00000000

        Field:           COMP
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Compare value for event F

*/
#define WSOC_OCLA_FCOMP_COMP_W                                       32U
#define WSOC_OCLA_FCOMP_COMP_M                                       0xFFFFFFFFU
#define WSOC_OCLA_FCOMP_COMP_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SUBTRIGX
    Offset name:         WSOC_OCLA_O_SUBTRIGX
    Relative address:    0x34
    Description:         make sub trigger from the events (A,B,C,D,E,F)
                        And and not on the events which will case for example:
                        A & B & ~C.
                        For this configure the AND to 6'h7 (C,B,A)
                        and the not to 6'h4 (C)
                        The order of the events are {F,E,D,C,B,A}.
    Default Value:       0x00000000

        Field:           AND
        From..to bits:   0...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which event will be in the and

*/
#define WSOC_OCLA_SUBTRIGX_AND_W                                     6U
#define WSOC_OCLA_SUBTRIGX_AND_M                                     0x0000003FU
#define WSOC_OCLA_SUBTRIGX_AND_S                                     0U
/*

        Field:           NOT
        From..to bits:   8...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which event will have not

*/
#define WSOC_OCLA_SUBTRIGX_NOT_W                                     6U
#define WSOC_OCLA_SUBTRIGX_NOT_M                                     0x00003F00U
#define WSOC_OCLA_SUBTRIGX_NOT_S                                     8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SUBTRIGY
    Offset name:         WSOC_OCLA_O_SUBTRIGY
    Relative address:    0x38
    Description:         make sub trigger from the events (A,B,C,D,E,F)
                        And and not on the events which will case for example:
                        A & B & ~C.
                        For this configure the AND to 6'h7 (C,B,A)
                        and the not to 6'h4 (C)
                        The order of the events are {F,E,D,C,B,A}.
    Default Value:       0x00000000

        Field:           AND
        From..to bits:   0...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which event will be in the and

*/
#define WSOC_OCLA_SUBTRIGY_AND_W                                     6U
#define WSOC_OCLA_SUBTRIGY_AND_M                                     0x0000003FU
#define WSOC_OCLA_SUBTRIGY_AND_S                                     0U
/*

        Field:           NOT
        From..to bits:   8...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which event will have not

*/
#define WSOC_OCLA_SUBTRIGY_NOT_W                                     6U
#define WSOC_OCLA_SUBTRIGY_NOT_M                                     0x00003F00U
#define WSOC_OCLA_SUBTRIGY_NOT_S                                     8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SUBTRIGZ
    Offset name:         WSOC_OCLA_O_SUBTRIGZ
    Relative address:    0x3C
    Description:         make sub trigger from the events (A,B,C,D,E,F)
                        And and not on the events which will case for example:
                        A & B & ~C.
                        For this configure the AND to 6'h7 (C,B,A)
                        and the not to 6'h4 (C)
                        The order of the events are {F,E,D,C,B,A}.
    Default Value:       0x00000000

        Field:           AND
        From..to bits:   0...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which event will be in the and

*/
#define WSOC_OCLA_SUBTRIGZ_AND_W                                     6U
#define WSOC_OCLA_SUBTRIGZ_AND_M                                     0x0000003FU
#define WSOC_OCLA_SUBTRIGZ_AND_S                                     0U
/*

        Field:           NOT
        From..to bits:   8...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which event will have not

*/
#define WSOC_OCLA_SUBTRIGZ_NOT_W                                     6U
#define WSOC_OCLA_SUBTRIGZ_NOT_M                                     0x00003F00U
#define WSOC_OCLA_SUBTRIGZ_NOT_S                                     8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCFG
    Offset name:         WSOC_OCLA_O_CLKCFG
    Relative address:    0x40
    Description:         OCLA Clk Configuration.
    Default Value:       0x00000000

        Field:           MOD
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clock Mode:

                         0. No CLK
                         1. CLK40
                         2. RF CLK
                         3. Illegal

                         NOTE: move between CLK should be through zero (No CLK)

*/
#define WSOC_OCLA_CLKCFG_MOD_W                                       2U
#define WSOC_OCLA_CLKCFG_MOD_M                                       0x00000003U
#define WSOC_OCLA_CLKCFG_MOD_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TRIGS
    Offset name:         WSOC_OCLA_O_TRIGS
    Relative address:    0x44
    Description:         Triggers.

                        configure the two triggers
    Default Value:       0x00000000

        Field:           AND
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which of the sub triggers will make the trigger1
                         The sub_triggers order is {W,Z,Y,X}
                         to make ~X & Y use 4'h3.

*/
#define WSOC_OCLA_TRIGS_AND_W                                        4U
#define WSOC_OCLA_TRIGS_AND_M                                        0x0000000FU
#define WSOC_OCLA_TRIGS_AND_S                                        0U
/*

        Field:           INV
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which of the sub triggers will be invert for trigger1.
                         The sub_triggers order is {W,Z,Y,X}
                         to make ~X & Y use 4'h1

*/
#define WSOC_OCLA_TRIGS_INV_W                                        4U
#define WSOC_OCLA_TRIGS_INV_M                                        0x000000F0U
#define WSOC_OCLA_TRIGS_INV_S                                        4U
/*

        Field:           TAND
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which of the sub triggers will make the trigger2
                         The sub_triggers order is {W,Z,Y,X}
                         to make ~X & Y use 4'h3.

*/
#define WSOC_OCLA_TRIGS_TAND_W                                       4U
#define WSOC_OCLA_TRIGS_TAND_M                                       0x00000F00U
#define WSOC_OCLA_TRIGS_TAND_S                                       8U
/*

        Field:           TINV
        From..to bits:   12...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     which of the sub triggers will be invert for trigger1.
                         The sub_triggers order is {W,Z,Y,X}
                         to make ~X & Y use 4'h1

*/
#define WSOC_OCLA_TRIGS_TINV_W                                       4U
#define WSOC_OCLA_TRIGS_TINV_M                                       0x0000F000U
#define WSOC_OCLA_TRIGS_TINV_S                                       12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TIME
    Offset name:         WSOC_OCLA_O_TIME
    Relative address:    0x48
    Description:         OCLA Time.
    Default Value:       0x00000000

        Field:           TIME
        From..to bits:   0...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     use for:
                         1. For time between events for mode which check time between two events.
                         2. Number of event for modes that check number of event.

*/
#define WSOC_OCLA_TIME_TIME_W                                        26U
#define WSOC_OCLA_TIME_TIME_M                                        0x03FFFFFFU
#define WSOC_OCLA_TIME_TIME_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MODE
    Offset name:         WSOC_OCLA_O_MODE
    Relative address:    0x4C
    Description:         main mode configurations, memory params, and output params.
    Default Value:       0x00000000

        Field:           IQMOD
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     // 0: event1 happened
                         //  1: check time between last event_a to first event_b if it's bigger then mem_time event
                         //  2: check time between last event_a high to first event_b high if it's smaller then mem_time event
                         //  3: check the time from first event a to first event b if it's bigger then mem_time event
                         //  4: check the time from first event a to first event b if it's smaller then mem_time event
                         //  5: event1 happened T times
                         //  6: timestamp mode save events and timestamp
                         //  7: event1 happened but event2 didn't happened for T cycles
                         //  8: trigger A happened and next cycle trigger B happened sample monitor after timestamp once (as timestamp mode)
                         //  9: SW event when the mem_sw_info == 16'hffff
                         //  10: Save monitor bus and time stamp when monitor change masking from F trigger
                         //  11: Save T amount of samples when event1 happened
                         //  12: Save each time one of the trigger (A-F) happened
                         //  13: IQ Save 64 bit every cycle - 32LSB monitor bus,
                         //	             32 MSB bits are 32 LSB from IQ bus
                         //  14: IQ save
                         // 			32/64/128 bits IQ save mode
                         //     If  (mem_data_save_mode = 0)
                         //        case (mem_data_to_save)
                         //		   0:  ocla_dout[63:0] <= #1 ocla_iq_save_in[63:0];
                         //           1:  ocla_dout[63:0] <= #1 ocla_iq_save_in[127:64];
                         //		   2:  ocla_dout[127:0] <= #1 ocla_iq_save_in[127:0]; // save each cycle
                         //   If  (mem_data_save_mode = 1)
                         //     case (mem_data_to_save)
                         //      0: ocla_dout[31:0] <= #1 ocla_iq_save_in[31:0];
                         //      1: ocla_dout[31:0] <= #1 ocla_iq_save_in[63:32];
                         //	  2: ocla_dout[31:0] <= #1 ocla_iq_save_in[95:64];
                         //	  3: ocla_dout[31:0] <= #1 ocla_iq_save_in[127:96];
                         //  15: IQ inject
                         // 16: ocla debug write to the RAM {14'h3333, ocla_addr[17:0], 14'h2222, ocla_addr[17:0],
                         				      14'h1111, ocla_addr[17:0], 14'h0000, ocla_addr[17:0]}

*/
#define WSOC_OCLA_MODE_IQMOD_W                                       5U
#define WSOC_OCLA_MODE_IQMOD_M                                       0x0000001FU
#define WSOC_OCLA_MODE_IQMOD_S                                       0U
/*

        Field:           EN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable the OCLA should be the last write

*/
#define WSOC_OCLA_MODE_EN                                            0x00000020U
#define WSOC_OCLA_MODE_EN_M                                          0x00000020U
#define WSOC_OCLA_MODE_EN_S                                          5U
/*

        Field:           DATAMOD
        From..to bits:   8...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     // 0: save 64bits each cycle
                         // 1: save 32bits each cycle (write to memory every two cycles)
                         // 2: save 16LSB each cycle (write to the ram every 4 cycles)
                         // 3: save 8LSB  each cycle (write to the ram every 8 cycles)

                         // for IQ save/inject modes
                         // look at mode description.

*/
#define WSOC_OCLA_MODE_DATAMOD_W                                     2U
#define WSOC_OCLA_MODE_DATAMOD_M                                     0x00000300U
#define WSOC_OCLA_MODE_DATAMOD_S                                     8U
/*

        Field:           PARAMMOD
        From..to bits:   10...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     not in use.

*/
#define WSOC_OCLA_MODE_PARAMMOD_W                                    3U
#define WSOC_OCLA_MODE_PARAMMOD_M                                    0x00001C00U
#define WSOC_OCLA_MODE_PARAMMOD_S                                    10U
/*

        Field:           SWTCHIGH
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     At mode which switch iq with din (bit 15) take bits from 127 to 32 when this bit is one otherwise take 97:0.

*/
#define WSOC_OCLA_MODE_SWTCHIGH                                      0x00004000U
#define WSOC_OCLA_MODE_SWTCHIGH_M                                    0x00004000U
#define WSOC_OCLA_MODE_SWTCHIGH_S                                    14U
/*

        Field:           SWTCIQDIN
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Switch between IQ_SAVE data in and debug bus in.
                         This enable to do all triggers and save data on iq_in.

*/
#define WSOC_OCLA_MODE_SWTCIQDIN                                     0x00008000U
#define WSOC_OCLA_MODE_SWTCIQDIN_M                                   0x00008000U
#define WSOC_OCLA_MODE_SWTCIQDIN_S                                   15U
/*

        Field:           D2SAVE
        From..to bits:   16...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This do shift down to the monitor which saved (not the triggers)

                         0: monitor as it is.
                         1: Shift right 16 bits
                             for mode of 32 bits monitor[47:16]
                             for mode of 16 bits monitor[31:16]
                             for mode of 8 bits monitor[24:16].
                         2: Shift right 32 bits
                             for mode of 32 bits monitor[63:32]
                             for mode of 16 bits monitor[47:32]
                             for mode of 8 bits monitor[39:32].
                         3: Shift right 64 bits
                             Don't use in 64bits  mode
                            for mode of 32 bits monitor[95:64]
                             for mode of 16 bits monitor[79:64]
                             for mode of 8 bits monitor[71:64].


                         for IQ save mode 14
                           0 : output is iq_save_in[63:0]
                           1: output is iq_save_in[127:64]
                           2: output is iq_save_in[127:0]

*/
#define WSOC_OCLA_MODE_D2SAVE_W                                      2U
#define WSOC_OCLA_MODE_D2SAVE_M                                      0x00030000U
#define WSOC_OCLA_MODE_D2SAVE_S                                      16U
/*

        Field:           ADDRSW2D
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Save the mem_sw on the bits [31:24]

*/
#define WSOC_OCLA_MODE_ADDRSW2D                                      0x00400000U
#define WSOC_OCLA_MODE_ADDRSW2D_M                                    0x00400000U
#define WSOC_OCLA_MODE_ADDRSW2D_S                                    22U
/*

        Field:           MAXMIN
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     For max_time function can change it to min time by:
                         max = 0, min = 1.

*/
#define WSOC_OCLA_MODE_MAXMIN                                        0x00800000U
#define WSOC_OCLA_MODE_MAXMIN_M                                      0x00800000U
#define WSOC_OCLA_MODE_MAXMIN_S                                      23U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMSIZE
    Offset name:         WSOC_OCLA_O_MEMSIZE
    Relative address:    0x50
    Description:         OCLA Memory Size.
    Default Value:       0x00000000

        Field:           SIZE
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The last address in the memory OCLA use.
                         this is the 8 MSB out of 18 bits of 128bit wide lines.
                         (concatenated with 0x3FF to form the last address).

*/
#define WSOC_OCLA_MEMSIZE_SIZE_W                                     8U
#define WSOC_OCLA_MEMSIZE_SIZE_M                                     0x000000FFU
#define WSOC_OCLA_MEMSIZE_SIZE_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMSIZEEVT
    Offset name:         WSOC_OCLA_O_MEMSIZEEVT
    Relative address:    0x54
    Description:         Memory Size After Event.
    Default Value:       0x00000000

        Field:           SIZE
        From..to bits:   0...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of writes (128bit wide each) to the memory after the event

*/
#define WSOC_OCLA_MEMSIZEEVT_SIZE_W                                  18U
#define WSOC_OCLA_MEMSIZEEVT_SIZE_M                                  0x0003FFFFU
#define WSOC_OCLA_MEMSIZEEVT_SIZE_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMSWINF
    Offset name:         WSOC_OCLA_O_MEMSWINF
    Relative address:    0x58
    Description:         Memory SW Info.
                        Register which write to the memory as part of the data for SW HW alignment.
                        can also trigger an event to start OCLA recording.
    Default Value:       0x00000000

        Field:           SWINFO
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data save in memory .
                         not in mode : 6 , 10.
                         At mode of 64bits save it as MSB when en is high.

*/
#define WSOC_OCLA_MEMSWINF_SWINFO_W                                  16U
#define WSOC_OCLA_MEMSWINF_SWINFO_M                                  0x0000FFFFU
#define WSOC_OCLA_MEMSWINF_SWINFO_S                                  0U
/*

        Field:           EN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     When this bit is one and at ocla mode of not 6, 10 save the data.

*/
#define WSOC_OCLA_MEMSWINF_EN                                        0x00010000U
#define WSOC_OCLA_MEMSWINF_EN_M                                      0x00010000U
#define WSOC_OCLA_MEMSWINF_EN_S                                      16U
/*

        Field:           TRIG
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     raise bit to issue sw trigger.

*/
#define WSOC_OCLA_MEMSWINF_TRIG                                      0x00020000U
#define WSOC_OCLA_MEMSWINF_TRIG_M                                    0x00020000U
#define WSOC_OCLA_MEMSWINF_TRIG_S                                    17U
/*

        Field:           SAMP
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     signal to force re-sampling of the sw_info data into the recorded bus,

*/
#define WSOC_OCLA_MEMSWINF_SAMP                                      0x00040000U
#define WSOC_OCLA_MEMSWINF_SAMP_M                                    0x00040000U
#define WSOC_OCLA_MEMSWINF_SAMP_S                                    18U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STATESTA
    Offset name:         WSOC_OCLA_O_STATESTA
    Relative address:    0x5C
    Description:         Hold the pointer to the place in memory which event happened
    Default Value:       0x00000008

        Field:           INTRS
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     To read the OCLA state

                         ocla_mem_phase[1] - before or after the event
                         event_t_reg,
                         event_reg

*/
#define WSOC_OCLA_STATESTA_INTRS_W                                   3U
#define WSOC_OCLA_STATESTA_INTRS_M                                   0x00000007U
#define WSOC_OCLA_STATESTA_INTRS_S                                   0U
/*

        Field:           FIRSTFILL
        From..to bits:   3...3
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Indicates if this is the first time that the RAM is fill and therefore part of the RAM is unknown.
                         This value should be read when OCLA is finished working, before disabling the OCLA, because it is reset when OCLA is disabled.

*/
#define WSOC_OCLA_STATESTA_FIRSTFILL                                 0x00000008U
#define WSOC_OCLA_STATESTA_FIRSTFILL_M                               0x00000008U
#define WSOC_OCLA_STATESTA_FIRSTFILL_S                               3U
/*

        Field:           DATEVT
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This is as LSB of the event_ptr when use mode other then 64bits
                         0 event happened when the building of the 64bits was full.
                         1 event happened when the building of the 64 bits was on 8 bits.
                         2 event happened when the building of the 64 bits was on 16 bits.
                         ...

*/
#define WSOC_OCLA_STATESTA_DATEVT_W                                  4U
#define WSOC_OCLA_STATESTA_DATEVT_M                                  0x000000F0U
#define WSOC_OCLA_STATESTA_DATEVT_S                                  4U
/*

        Field:           EVTPTR
        From..to bits:   8...25
        DefaultValue:    0x0
        Access type:     read-only
        Description:     the address of the memory when event happened.

*/
#define WSOC_OCLA_STATESTA_EVTPTR_W                                  18U
#define WSOC_OCLA_STATESTA_EVTPTR_M                                  0x03FFFF00U
#define WSOC_OCLA_STATESTA_EVTPTR_S                                  8U
/*

        Field:           STATE
        From..to bits:   26...27
        DefaultValue:    0x0
        Access type:     read-only
        Description:     State machine:
                         0: looking for the event.
                         1: event found.
                         2: finish.

*/
#define WSOC_OCLA_STATESTA_STATE_W                                   2U
#define WSOC_OCLA_STATESTA_STATE_M                                   0x0C000000U
#define WSOC_OCLA_STATESTA_STATE_S                                   26U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RDDBG0
    Offset name:         WSOC_OCLA_O_RDDBG0
    Relative address:    0x60
    Description:         Read Debug 0.

                        Read the debug bus enter to OCLA 32 LSB
    Default Value:       0x00000000

        Field:           31TO0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     32 LSBs

*/
#define WSOC_OCLA_RDDBG0_31TO0_W                                     32U
#define WSOC_OCLA_RDDBG0_31TO0_M                                     0xFFFFFFFFU
#define WSOC_OCLA_RDDBG0_31TO0_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RDDBG1
    Offset name:         WSOC_OCLA_O_RDDBG1
    Relative address:    0x64
    Description:         Read Debug 1.

                        Read the debug bus enter to OCLA 63-32
    Default Value:       0x00000000

        Field:           63TO32
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     63 to 32 Bits.

*/
#define WSOC_OCLA_RDDBG1_63TO32_W                                    32U
#define WSOC_OCLA_RDDBG1_63TO32_M                                    0xFFFFFFFFU
#define WSOC_OCLA_RDDBG1_63TO32_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RDMAXTIME
    Offset name:         WSOC_OCLA_O_RDMAXTIME
    Relative address:    0x6C
    Description:         Read Max Time.
    Default Value:       0x00000000

        Field:           MAXTIME
        From..to bits:   0...25
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Value of the counter of max/min read

*/
#define WSOC_OCLA_RDMAXTIME_MAXTIME_W                                26U
#define WSOC_OCLA_RDMAXTIME_MAXTIME_M                                0x03FFFFFFU
#define WSOC_OCLA_RDMAXTIME_MAXTIME_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMCTL
    Offset name:         WSOC_OCLA_O_MEMCTL
    Relative address:    0x70
    Description:         Memory Start Address.
    Default Value:       0x00000000

        Field:           STARTADDR
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Which address the RAM start, change only for the 8 MSB, the 10 LSB is always 0.

*/
#define WSOC_OCLA_MEMCTL_STARTADDR_W                                 8U
#define WSOC_OCLA_MEMCTL_STARTADDR_M                                 0x000000FFU
#define WSOC_OCLA_MEMCTL_STARTADDR_S                                 0U
/*

        Field:           SAMPRATE
        From..to bits:   8...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Sample to the RAM once each X times

*/
#define WSOC_OCLA_MEMCTL_SAMPRATE_W                                  5U
#define WSOC_OCLA_MEMCTL_SAMPRATE_M                                  0x00001F00U
#define WSOC_OCLA_MEMCTL_SAMPRATE_S                                  8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INJECTCTL
    Offset name:         WSOC_OCLA_O_INJECTCTL
    Relative address:    0x74
    Description:         OCLA Inject Control.
    Default Value:       0x00000000

        Field:           START
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Start INJECT

*/
#define WSOC_OCLA_INJECTCTL_START                                    0x00000001U
#define WSOC_OCLA_INJECTCTL_START_M                                  0x00000001U
#define WSOC_OCLA_INJECTCTL_START_S                                  0U
/*

        Field:           STOP
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Which address the RAM start, change only for the 8 MSB, the 10 LSB is always 0.

*/
#define WSOC_OCLA_INJECTCTL_STOP                                     0x00000002U
#define WSOC_OCLA_INJECTCTL_STOP_M                                   0x00000002U
#define WSOC_OCLA_INJECTCTL_STOP_S                                   1U
/*

        Field:           MODE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Inject Mode:

                         0. Single INJECT mode (Stop when Address=Max address)
                         1. Multi   INJECT mode (stop when Wr to "stop" field)

*/
#define WSOC_OCLA_INJECTCTL_MODE                                     0x00010000U
#define WSOC_OCLA_INJECTCTL_MODE_M                                   0x00010000U
#define WSOC_OCLA_INJECTCTL_MODE_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PORTCFG0
    Offset name:         WSOC_OCLA_O_PORTCFG0
    Relative address:    0x78
    Description:         Debug Port CFG 0.
    Default Value:       0xAAAAAAAA

        Field:           BIT0SEL
        From..to bits:   0...31
        DefaultValue:    0xAAAAAAAA
        Access type:     read-write
        Description:     Bit 0.

*/
#define WSOC_OCLA_PORTCFG0_BIT0SEL_W                                 32U
#define WSOC_OCLA_PORTCFG0_BIT0SEL_M                                 0xFFFFFFFFU
#define WSOC_OCLA_PORTCFG0_BIT0SEL_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PORTCFG1
    Offset name:         WSOC_OCLA_O_PORTCFG1
    Relative address:    0x7C
    Description:         Debug Port CFG 1.
    Default Value:       0xCCCCCCCC

        Field:           BIT1SEL
        From..to bits:   0...31
        DefaultValue:    0xCCCCCCCC
        Access type:     read-write
        Description:     Bit 1.

*/
#define WSOC_OCLA_PORTCFG1_BIT1SEL_W                                 32U
#define WSOC_OCLA_PORTCFG1_BIT1SEL_M                                 0xFFFFFFFFU
#define WSOC_OCLA_PORTCFG1_BIT1SEL_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PORTCFG2
    Offset name:         WSOC_OCLA_O_PORTCFG2
    Relative address:    0x80
    Description:         Debug Port CFG 2.
    Default Value:       0xF0F0F0F0

        Field:           BIT2SEL
        From..to bits:   0...31
        DefaultValue:    0xF0F0F0F0
        Access type:     read-write
        Description:     Bit 2.

*/
#define WSOC_OCLA_PORTCFG2_BIT2SEL_W                                 32U
#define WSOC_OCLA_PORTCFG2_BIT2SEL_M                                 0xFFFFFFFFU
#define WSOC_OCLA_PORTCFG2_BIT2SEL_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PORTCFG3
    Offset name:         WSOC_OCLA_O_PORTCFG3
    Relative address:    0x84
    Description:         Debug Port CFG 3.
    Default Value:       0xFF00FF00

        Field:           BIT3SEL
        From..to bits:   0...31
        DefaultValue:    0xFF00FF00
        Access type:     read-write
        Description:     Bit 3.

*/
#define WSOC_OCLA_PORTCFG3_BIT3SEL_W                                 32U
#define WSOC_OCLA_PORTCFG3_BIT3SEL_M                                 0xFFFFFFFFU
#define WSOC_OCLA_PORTCFG3_BIT3SEL_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PORTCFG4
    Offset name:         WSOC_OCLA_O_PORTCFG4
    Relative address:    0x88
    Description:         Debug Port CFG 4.
    Default Value:       0xFFFF0000

        Field:           BIT4SEL
        From..to bits:   0...31
        DefaultValue:    0xFFFF0000
        Access type:     read-write
        Description:     Bit 4.

*/
#define WSOC_OCLA_PORTCFG4_BIT4SEL_W                                 32U
#define WSOC_OCLA_PORTCFG4_BIT4SEL_M                                 0xFFFFFFFFU
#define WSOC_OCLA_PORTCFG4_BIT4SEL_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TPSEL
    Offset name:         WSOC_OCLA_O_TPSEL
    Relative address:    0x8C
    Description:         Debug Port TP1 or TP2.
    Default Value:       0x00000000

        Field:           SEL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Each bit select which TP1 or TP2 would connect to OCLA bus bits[63:32]

                         0. select TP2
                         1. select TP1

                         Note: OCLA bus [31:0] is TP1

*/
#define WSOC_OCLA_TPSEL_SEL_W                                        32U
#define WSOC_OCLA_TPSEL_SEL_M                                        0xFFFFFFFFU
#define WSOC_OCLA_TPSEL_SEL_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PORTSEL
    Offset name:         WSOC_OCLA_O_PORTSEL
    Relative address:    0x90
    Description:         Debug Port Selector.
    Default Value:       0x00000000

        Field:           TP1SEL
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Select which debug port used by OCLA for TP1 --> [31:0]

                         0x0. select PHY Debug Port
                         0x1. select WSOC Debug Port
                         0x2. select TOP Debug Port
                         0x3. select BLE Debug Port
                         0x4. select Peripheral Debug Port

*/
#define WSOC_OCLA_PORTSEL_TP1SEL_W                                   3U
#define WSOC_OCLA_PORTSEL_TP1SEL_M                                   0x00000007U
#define WSOC_OCLA_PORTSEL_TP1SEL_S                                   0U
/*

        Field:           TP2SEL
        From..to bits:   8...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Select which debug port used by OCLA for TP2 --> [63:32]

                         0x0. select PHY Debug Port
                         0x1. select WSOC Debug Port
                         0x2. select TOP Debug Port
                         0x3. select BLE Debug Port
                         0x4. select Peripheral Debug Port

*/
#define WSOC_OCLA_PORTSEL_TP2SEL_W                                   3U
#define WSOC_OCLA_PORTSEL_TP2SEL_M                                   0x00000700U
#define WSOC_OCLA_PORTSEL_TP2SEL_S                                   8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OUTSEL
    Offset name:         WSOC_OCLA_O_OUTSEL
    Relative address:    0x94
    Description:         Debug Out Selector.

                        select if debug port output is connected to GPIO values (OCP mapped register) or to debug port.
    Default Value:       NA

        Field:           SEL
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     per bit selection

                         0. GPIO
                         1. debug port

*/
#define WSOC_OCLA_OUTSEL_SEL_W                                       32U
#define WSOC_OCLA_OUTSEL_SEL_M                                       0xFFFFFFFFU
#define WSOC_OCLA_OUTSEL_SEL_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OUTVAL
    Offset name:         WSOC_OCLA_O_OUTVAL
    Relative address:    0x98
    Description:         GPIO Out Value.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     GPIO out read/write value.

*/
#define WSOC_OCLA_OUTVAL_VAL_W                                       32U
#define WSOC_OCLA_OUTVAL_VAL_M                                       0xFFFFFFFFU
#define WSOC_OCLA_OUTVAL_VAL_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OUTVALSET
    Offset name:         WSOC_OCLA_O_OUTVALSET
    Relative address:    0x9C
    Description:         GPIO Out Value Set.
    Default Value:       NA

        Field:           SET
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     writing 1 to a bit will set the [OUTVAL.VAL]. writing 0 is ignored

*/
#define WSOC_OCLA_OUTVALSET_SET_W                                    32U
#define WSOC_OCLA_OUTVALSET_SET_M                                    0xFFFFFFFFU
#define WSOC_OCLA_OUTVALSET_SET_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OUTVALCLR
    Offset name:         WSOC_OCLA_O_OUTVALCLR
    Relative address:    0xA0
    Description:         GPIO Out Value Clear.
    Default Value:       NA

        Field:           CLR
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     writing 1 to a bit will clr a bit [OUTVAL.VAL]

*/
#define WSOC_OCLA_OUTVALCLR_CLR_W                                    32U
#define WSOC_OCLA_OUTVALCLR_CLR_M                                    0xFFFFFFFFU
#define WSOC_OCLA_OUTVALCLR_CLR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OUTVALTGL
    Offset name:         WSOC_OCLA_O_OUTVALTGL
    Relative address:    0xA4
    Description:         GPIO Out Value Toggle.
    Default Value:       NA

        Field:           TOGGLE
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     writing 1 to a bit will toggle a bit at [OUTVAL.VAL].

*/
#define WSOC_OCLA_OUTVALTGL_TOGGLE_W                                 32U
#define WSOC_OCLA_OUTVALTGL_TOGGLE_M                                 0xFFFFFFFFU
#define WSOC_OCLA_OUTVALTGL_TOGGLE_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OUTVALPLS
    Offset name:         WSOC_OCLA_O_OUTVALPLS
    Relative address:    0xA8
    Description:         GPIO Out Value Pulse.
    Default Value:       NA

        Field:           PULSE
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     writing 1 to a bit will create a pulse for the same bit at [OUTVAL.VAL]
                         ( Pulse is equal to toggle twice )

*/
#define WSOC_OCLA_OUTVALPLS_PULSE_W                                  32U
#define WSOC_OCLA_OUTVALPLS_PULSE_M                                  0xFFFFFFFFU
#define WSOC_OCLA_OUTVALPLS_PULSE_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TFSONTRG
    Offset name:         WSOC_OCLA_O_TFSONTRG
    Relative address:    0xB0
    Description:         TSF on Trigger.

                        this is the 32 lower bits of the tsf latched on final trigger event
    Default Value:       0x00000000

        Field:           TIMESTAMP
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TSF time stamp samled on trigger.

*/
#define WSOC_OCLA_TFSONTRG_TIMESTAMP_W                               32U
#define WSOC_OCLA_TFSONTRG_TIMESTAMP_M                               0xFFFFFFFFU
#define WSOC_OCLA_TFSONTRG_TIMESTAMP_S                               0U

#endif /* __HW_WSOC_OCLA_H__*/
