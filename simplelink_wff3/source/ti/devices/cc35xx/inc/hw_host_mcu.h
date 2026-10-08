/******************************************************************************
*  Filename:       hw_host_mcu.h
*
*  Description:    Defines and prototypes for the HOST_MCU peripheral.
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
#ifndef __HW_HOST_MCU_H__
#define __HW_HOST_MCU_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the HOST_MCU component

--------------------------------------------------------------------------------- */

//Trace Configuration
#define HOST_MCU_O_TRACECFG                                          0x00000000U

//Spare
#define HOST_MCU_O_SPARE                                             0x00000004U

//WRR Arbiter Enable Register
#define HOST_MCU_O_WRRARB                                            0x00000008U

//WRR Arbiter - Agent 0 Configuration
#define HOST_MCU_O_AGENT0CFG                                         0x00000010U

//WRR Arbiter - Agent 1 Configuration
#define HOST_MCU_O_AGENT1CFG                                         0x00000014U

//Software Timestamp Interrupt Register
#define HOST_MCU_O_SWIRQ                                             0x00000018U

//Non Secure Software Interrupt
#define HOST_MCU_O_NSSWIRQ                                           0x0000001CU

//Software Interrupt to CM3
#define HOST_MCU_O_SWIRQCM3                                          0x00000020U

//Arbiter Policy
#define HOST_MCU_O_ARBPOL                                            0x00000024U

//DEBUGSS Control Register
#define HOST_MCU_O_DBGSS                                             0x00000028U

//DEBUGSS Interface Lock
#define HOST_MCU_O_DBGSSLCK                                          0x0000002CU

//DEBUGSS Interface Lock Condition Mask
#define HOST_MCU_O_DBGSSLM                                           0x00000030U

//DEBUGSS Interface Lock Condition Status
#define HOST_MCU_O_DBGSSLS                                           0x00000034U



/*-----------------------------------REGISTER------------------------------------
    Register name:       TRACECFG
    Offset name:         HOST_MCU_O_TRACECFG
    Relative address:    0x0
    Description:         Trace Configuration.

                        Configuration register for CortexM3-TPIU (TRACE ports i/o unit)
    Default Value:       0x00000002

        Field:           CLKDIVVAL
        From..to bits:   0...1
        DefaultValue:    0x2
        Access type:     read-write
        Description:     Configure TRACE-CLOCK divider value, for (TPIU - input clock)
                         [1]    - Divide by 2 - 'tpiu_trace_clk_in' = 40MHz
                         [2]    - Divide by 4 - 'tpiu_trace_clk_in' = 20MHz (Default)
                         [0,3] - are not supported (do not use)

                         AFTER setting this value - set [CLKDIVEN] to active this value

        ENUMs:
            DIV_2:                       Divide by 2
            DIV_4:                       Divide by 4
*/
#define HOST_MCU_TRACECFG_CLKDIVVAL_W                                2U
#define HOST_MCU_TRACECFG_CLKDIVVAL_M                                0x00000003U
#define HOST_MCU_TRACECFG_CLKDIVVAL_S                                0U
#define HOST_MCU_TRACECFG_CLKDIVVAL_DIV_2                            0x00000000U
#define HOST_MCU_TRACECFG_CLKDIVVAL_DIV_4                            0x00000001U
/*

        Field:           CLKDIVEN
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set this register to load [CLKDIVVAL]

        ENUMs:
            DIS:
            EN:                          Disable
*/
#define HOST_MCU_TRACECFG_CLKDIVEN                                   0x00000100U
#define HOST_MCU_TRACECFG_CLKDIVEN_M                                 0x00000100U
#define HOST_MCU_TRACECFG_CLKDIVEN_S                                 8U
#define HOST_MCU_TRACECFG_CLKDIVEN_DIS                               0x00000000U
#define HOST_MCU_TRACECFG_CLKDIVEN_EN                                0x00000100U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SPARE
    Offset name:         HOST_MCU_O_SPARE
    Relative address:    0x4
    Description:         Spare
    Default Value:       0x00000000

        Field:           SBITS
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Spare

*/
#define HOST_MCU_SPARE_SBITS_W                                       32U
#define HOST_MCU_SPARE_SBITS_M                                       0xFFFFFFFFU
#define HOST_MCU_SPARE_SBITS_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WRRARB
    Offset name:         HOST_MCU_O_WRRARB
    Relative address:    0x8
    Description:         WRR Arbiter Enable Register
    Default Value:       0x00000002

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Field to enable/select the arbitration logic
                         0 - Disabled, use SIE-200 arbitration logic.
                         1 - Enable, use wrapper arbitration logic.

        ENUMs:
            DIS:                         Use SIE-200 arbitration logic
            EN:                          Use wrapper arbitration logic
*/
#define HOST_MCU_WRRARB_EN                                           0x00000001U
#define HOST_MCU_WRRARB_EN_M                                         0x00000001U
#define HOST_MCU_WRRARB_EN_S                                         0U
#define HOST_MCU_WRRARB_EN_DIS                                       0x00000000U
#define HOST_MCU_WRRARB_EN_EN                                        0x00000001U
/*

        Field:           POLICY
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Field to configure the priority policy
                         0 - Fixed Priority
                         1 - Round Robin (Default)

        ENUMs:
            FIXED:                       Fixed priority
            ROUNDROBIN:                  Round Robin (Default)
*/
#define HOST_MCU_WRRARB_POLICY                                       0x00000002U
#define HOST_MCU_WRRARB_POLICY_M                                     0x00000002U
#define HOST_MCU_WRRARB_POLICY_S                                     1U
#define HOST_MCU_WRRARB_POLICY_FIXED                                 0x00000000U
#define HOST_MCU_WRRARB_POLICY_ROUNDROBIN                            0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AGENT0CFG
    Offset name:         HOST_MCU_O_AGENT0CFG
    Relative address:    0x10
    Description:         WRR Arbiter - Agent 0 Configuration
    Default Value:       0x00010004

        Field:           NUMOFBLK
        From..to bits:   0...12
        DefaultValue:    0x4
        Access type:     read-write
        Description:     Number of words to be served in each arbitration grant.
                         Up to 8,192 words (32KB).
                         Value must be greater then 0.

*/
#define HOST_MCU_AGENT0CFG_NUMOFBLK_W                                13U
#define HOST_MCU_AGENT0CFG_NUMOFBLK_M                                0x00001FFFU
#define HOST_MCU_AGENT0CFG_NUMOFBLK_S                                0U
/*

        Field:           FIXPRI
        From..to bits:   16...17
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Field to select the fixed priority level
                         0 - Highest
                         1 - Medium
                         2 - Lowest (default)
                         3 - Not in Use

        ENUMs:
            SEL_0:                       Highest Priority
            SEL_2:                       Lowest priority (default)
            SEL_1:                       Medium Priority
*/
#define HOST_MCU_AGENT0CFG_FIXPRI_W                                  2U
#define HOST_MCU_AGENT0CFG_FIXPRI_M                                  0x00030000U
#define HOST_MCU_AGENT0CFG_FIXPRI_S                                  16U
#define HOST_MCU_AGENT0CFG_FIXPRI_SEL_0                              0x00000000U
#define HOST_MCU_AGENT0CFG_FIXPRI_SEL_2                              0x00020000U
#define HOST_MCU_AGENT0CFG_FIXPRI_SEL_1                              0x00010000U
/*

        Field:           TRANSDLY
        From..to bits:   24...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of cycle before starting to serve next agent in line.
                         Up to 32 cycles.

*/
#define HOST_MCU_AGENT0CFG_TRANSDLY_W                                5U
#define HOST_MCU_AGENT0CFG_TRANSDLY_M                                0x1F000000U
#define HOST_MCU_AGENT0CFG_TRANSDLY_S                                24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AGENT1CFG
    Offset name:         HOST_MCU_O_AGENT1CFG
    Relative address:    0x14
    Description:         WRR Arbiter - Agent 1 Configuration
    Default Value:       0x00000004

        Field:           NUMOFBLK
        From..to bits:   0...12
        DefaultValue:    0x4
        Access type:     read-write
        Description:     Number of words to be served in each arbitration grant.
                         Up to 8,192 words (32KB).
                         Value must be greater then 0.

*/
#define HOST_MCU_AGENT1CFG_NUMOFBLK_W                                13U
#define HOST_MCU_AGENT1CFG_NUMOFBLK_M                                0x00001FFFU
#define HOST_MCU_AGENT1CFG_NUMOFBLK_S                                0U
/*

        Field:           FIXPRI
        From..to bits:   16...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Field to select the fixed priority level
                         0 - Highest
                         1 - Medium
                         2 - Lowest (default)
                         3 - Not in Use

        ENUMs:
            SEL_0:                       Highest priority
            SEL_1:                       Medium priority
            SEL_2:                       Lowest priority (default)
*/
#define HOST_MCU_AGENT1CFG_FIXPRI_W                                  2U
#define HOST_MCU_AGENT1CFG_FIXPRI_M                                  0x00030000U
#define HOST_MCU_AGENT1CFG_FIXPRI_S                                  16U
#define HOST_MCU_AGENT1CFG_FIXPRI_SEL_0                              0x00000000U
#define HOST_MCU_AGENT1CFG_FIXPRI_SEL_1                              0x00010000U
#define HOST_MCU_AGENT1CFG_FIXPRI_SEL_2                              0x00020000U
/*

        Field:           TRANSDLY
        From..to bits:   24...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of cycle before starting to serve next agent in line.
                         Up to 32 cycles.

*/
#define HOST_MCU_AGENT1CFG_TRANSDLY_W                                5U
#define HOST_MCU_AGENT1CFG_TRANSDLY_M                                0x1F000000U
#define HOST_MCU_AGENT1CFG_TRANSDLY_S                                24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWIRQ
    Offset name:         HOST_MCU_O_SWIRQ
    Relative address:    0x18
    Description:         Software Timestamp Interrupt Register
    Default Value:       0x00000000

        Field:           TIMESTAMP
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Field to write timestamp for ET bus.

*/
#define HOST_MCU_SWIRQ_TIMESTAMP_W                                   16U
#define HOST_MCU_SWIRQ_TIMESTAMP_M                                   0x0000FFFFU
#define HOST_MCU_SWIRQ_TIMESTAMP_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       NSSWIRQ
    Offset name:         HOST_MCU_O_NSSWIRQ
    Relative address:    0x1C
    Description:         Non Secure Software Interrupt
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Non Secure context of CM33 can use this register to interrupt secure context of CM33.

*/
#define HOST_MCU_NSSWIRQ_EN_W                                        4U
#define HOST_MCU_NSSWIRQ_EN_M                                        0x0000000FU
#define HOST_MCU_NSSWIRQ_EN_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWIRQCM3
    Offset name:         HOST_MCU_O_SWIRQCM3
    Relative address:    0x20
    Description:         Software Interrupt to CM3
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Non Secure context of CM33 can use this register to interrupt CM3.

*/
#define HOST_MCU_SWIRQCM3_EN                                         0x00000001U
#define HOST_MCU_SWIRQCM3_EN_M                                       0x00000001U
#define HOST_MCU_SWIRQCM3_EN_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ARBPOL
    Offset name:         HOST_MCU_O_ARBPOL
    Relative address:    0x24
    Description:         Arbiter Policy.

                        Arbiter Policy for the arbiters(x2) located just before MEMSS Portion A and Portion B
    Default Value:       0x00000000

        Field:           RNDRBNS0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Field to select the arbitration policy of second arbiter (MEMSS Portion A)
                         1 -> Round Robin is enabled
                          0 -> Fixed priority is enabled

        ENUMs:
            FIXED:                       Fixed priority
            ROUNDROBIN:                  Round Robin priority
*/
#define HOST_MCU_ARBPOL_RNDRBNS0                                     0x00000001U
#define HOST_MCU_ARBPOL_RNDRBNS0_M                                   0x00000001U
#define HOST_MCU_ARBPOL_RNDRBNS0_S                                   0U
#define HOST_MCU_ARBPOL_RNDRBNS0_FIXED                               0x00000000U
#define HOST_MCU_ARBPOL_RNDRBNS0_ROUNDROBIN                          0x00000001U
/*

        Field:           RNDRBNS1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Field to select the arbitration policy of second arbiter (MEMSS Portion )
                         1 -> Round Robin is enabled
                         0 -> Fixed priority is enabled

        ENUMs:
            FIXED:                       Fixed priority
            ROUNDROBIN:                  Round Robin priority
*/
#define HOST_MCU_ARBPOL_RNDRBNS1                                     0x00000002U
#define HOST_MCU_ARBPOL_RNDRBNS1_M                                   0x00000002U
#define HOST_MCU_ARBPOL_RNDRBNS1_S                                   1U
#define HOST_MCU_ARBPOL_RNDRBNS1_FIXED                               0x00000000U
#define HOST_MCU_ARBPOL_RNDRBNS1_ROUNDROBIN                          0x00000002U
/*

        Field:           S0PRIM0
        From..to bits:   2...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit field takes affect when Fixed Priority is selected for the arbiter before MEMSS Portion A. This field is used to configure the priority of udma/sahb.

*/
#define HOST_MCU_ARBPOL_S0PRIM0_W                                    2U
#define HOST_MCU_ARBPOL_S0PRIM0_M                                    0x0000000CU
#define HOST_MCU_ARBPOL_S0PRIM0_S                                    2U
/*

        Field:           S0PRIM1
        From..to bits:   4...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit field takes affect when Fixed Priority is selected for the arbiter before MEMSS Portion A. This field is used to configure the priority of ocp.

*/
#define HOST_MCU_ARBPOL_S0PRIM1_W                                    2U
#define HOST_MCU_ARBPOL_S0PRIM1_M                                    0x00000030U
#define HOST_MCU_ARBPOL_S0PRIM1_S                                    4U
/*

        Field:           S1PRIM0
        From..to bits:   6...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit field takes affect when Fixed Priority is selected for the arbiter before MEMSS Portion B. This field is used to configure the priority of udma/sahb.

*/
#define HOST_MCU_ARBPOL_S1PRIM0_W                                    2U
#define HOST_MCU_ARBPOL_S1PRIM0_M                                    0x000000C0U
#define HOST_MCU_ARBPOL_S1PRIM0_S                                    6U
/*

        Field:           S1PRIM1
        From..to bits:   8...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit field takes affect when Fixed Priority is selected for the arbiter before MEMSS Portion B. This field is used to configure the priority of ocp.

*/
#define HOST_MCU_ARBPOL_S1PRIM1_W                                    2U
#define HOST_MCU_ARBPOL_S1PRIM1_M                                    0x00000300U
#define HOST_MCU_ARBPOL_S1PRIM1_S                                    8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGSS
    Offset name:         HOST_MCU_O_DBGSS
    Relative address:    0x28
    Description:         DEBUGSS Control Register.
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Non Secure context of CM33 can use this register to interrupt CM3.

*/
#define HOST_MCU_DBGSS_EN                                            0x00000001U
#define HOST_MCU_DBGSS_EN_M                                          0x00000001U
#define HOST_MCU_DBGSS_EN_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGSSLCK
    Offset name:         HOST_MCU_O_DBGSSLCK
    Relative address:    0x2C
    Description:         DEBUGSS Interface Lock.
    Default Value:       0x00000000

        Field:           LOCK
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The method: Obtain lock by Read. Following are all s/w operation possibilities:
                         When reading '1'  - lock is obtained. (i.e. no debugss request was active during the rd transaction).
                         When reading '0'  - lock is not obtained. Try to read again. (i.e. at least debugss request event was active during the rd transaction).
                         when writing '1'  - lock will be obtained regardless to debugss request status
                         when writing '0'  - lock will be released.

                         Type: Write/Read-Clear

*/
#define HOST_MCU_DBGSSLCK_LOCK                                       0x00000001U
#define HOST_MCU_DBGSSLCK_LOCK_M                                     0x00000001U
#define HOST_MCU_DBGSSLCK_LOCK_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGSSLM
    Offset name:         HOST_MCU_O_DBGSSLM
    Relative address:    0x30
    Description:         DEBUGSS Interface Lock Condition Mask
    Default Value:       0x00000000

        Field:           MASK
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Masks Debugss Force-active

                         Set 1 - Mask request during lock check.
                         Set 0 - O.W.

        ENUMs:
            SET_0:                       O.W
            SET_1:                       Mask request during lock check
*/
#define HOST_MCU_DBGSSLM_MASK                                        0x00000002U
#define HOST_MCU_DBGSSLM_MASK_M                                      0x00000002U
#define HOST_MCU_DBGSSLM_MASK_S                                      1U
#define HOST_MCU_DBGSSLM_MASK_SET_0                                  0x00000000U
#define HOST_MCU_DBGSSLM_MASK_SET_1                                  0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGSSLS
    Offset name:         HOST_MCU_O_DBGSSLS
    Relative address:    0x34
    Description:         DEBUGSS Interface Lock Condition Status
    Default Value:       0x00000000

        Field:           CSYSPWRREQ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEBUGSS HOST C SYS Power Request

        ENUMs:
            CLR:                         Not in use
            SET:                         Debugss host c sys power requested
*/
#define HOST_MCU_DBGSSLS_CSYSPWRREQ                                  0x00000001U
#define HOST_MCU_DBGSSLS_CSYSPWRREQ_M                                0x00000001U
#define HOST_MCU_DBGSSLS_CSYSPWRREQ_S                                0U
#define HOST_MCU_DBGSSLS_CSYSPWRREQ_CLR                              0x00000000U
#define HOST_MCU_DBGSSLS_CSYSPWRREQ_SET                              0x00000001U
/*

        Field:           FRCACT
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DEBUGSS HOST Force Active

        ENUMs:
            CLR:                         Not in use
            SET:                         Debugss host force active is set
*/
#define HOST_MCU_DBGSSLS_FRCACT                                      0x00000002U
#define HOST_MCU_DBGSSLS_FRCACT_M                                    0x00000002U
#define HOST_MCU_DBGSSLS_FRCACT_S                                    1U
#define HOST_MCU_DBGSSLS_FRCACT_CLR                                  0x00000000U
#define HOST_MCU_DBGSSLS_FRCACT_SET                                  0x00000002U

#endif /* __HW_HOST_MCU_H__*/
