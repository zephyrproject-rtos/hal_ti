/******************************************************************************
*  Filename:       hw_host_xip.h
*
*  Description:    Defines and prototypes for the HOST_XIP peripheral.
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
#ifndef __HW_HOST_XIP_H__
#define __HW_HOST_XIP_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the HOST_XIP component

--------------------------------------------------------------------------------- */

//WRR Arbiter Enable
#define HOST_XIP_O_ARBCTL                                            0x00000000U

//WRR ARBITER HALT
#define HOST_XIP_O_ARBHALT                                           0x00000004U

//WRR Arbiter - Agent 0 Configuration
#define HOST_XIP_O_ARBCFG0                                           0x00000008U

//WRR Arbiter - Agent 1 Configuration
#define HOST_XIP_O_ARBCFG1                                           0x0000000CU

//WRR Arbiter - Agent 2 Configuration
#define HOST_XIP_O_ARBCFG2                                           0x00000010U

//Register to configure the extra delay added before the device switch
#define HOST_XIP_O_SWCHDLY                                           0x00000014U

//Disable clocks using HOST_XIP_RCM Module
#define HOST_XIP_O_RCMCLKDIS                                         0x00000020U

//Force clocks using HOST_XIP_RCM Module
#define HOST_XIP_O_RCMCLKFRC                                         0x00000024U

//(ICG) Clock Status from HOST_XIP_RCM Module
#define HOST_XIP_O_RCMCLKSTA                                         0x00000028U

//OSPICFG
#define HOST_XIP_O_OSPICFG                                           0x00000040U

//uDMA source address for secured read master
#define HOST_XIP_O_UDSCFG0                                           0x00001000U

//uDMA destination address for secured write master
#define HOST_XIP_O_UDSCFG1                                           0x00001004U

//uDMA secured job Length
#define HOST_XIP_O_UDSCFG2                                           0x00001008U

//uDMA Direction
#define HOST_XIP_O_UDSCFG3                                           0x0000100CU

//uDMA secured job kick
#define HOST_XIP_O_UDSCTL0                                           0x00001010U

//uDMA secured job abort
#define HOST_XIP_O_UDSCTL1                                           0x00001014U

//uDMA secured Status bits
#define HOST_XIP_O_UDSSTA                                            0x00001020U

//uDMA secured IRQ Status bits
#define HOST_XIP_O_UDSIRQ                                            0x00001024U

//uDMA secured Status bits in addition to [UDMSSTA] register
#define HOST_XIP_O_UDSSTA1                                           0x0000102CU

//uDMA Secure channel peripheral config register
#define HOST_XIP_O_UDSPERCFG                                         0x00001040U

//Register to select the peripheral to be served on secured channel
#define HOST_XIP_O_UDSPERSEL                                         0x00001060U

//Register to select the peripheral to be served on non secured channel
#define HOST_XIP_O_UDNSPERSEL                                        0x00001064U

//uDMA source address for non-secured read master
#define HOST_XIP_O_UDNSCFG0                                          0x00002000U

//uDMA destination address for non-secured write master
#define HOST_XIP_O_UDNSCFG1                                          0x00002004U

//uDMA non-secured job Length
#define HOST_XIP_O_UDNSCFG2                                          0x00002008U

//uDMA Direction
#define HOST_XIP_O_UDNSCFG3                                          0x0000200CU

//uDMA non-secured job kick
#define HOST_XIP_O_UDNSCTL0                                          0x00002010U

//uDMA non-secured job abort
#define HOST_XIP_O_UDNSCTL1                                          0x00002014U

//uDMA non-secured Status bits
#define HOST_XIP_O_UDNSSTA                                           0x00002020U

//uDMA non-secured IRQ Status bits
#define HOST_XIP_O_UDNSIRQ                                           0x00002024U

//uDMA threshold configuration
#define HOST_XIP_O_UTHRCNF                                           0x00002028U

//uDMA non-secured Status bits in addition to [UDNSSTA] register
#define HOST_XIP_O_UDNSSTA1                                          0x0000202CU

//Non secure peirpheral job configuration
#define HOST_XIP_O_UDNSPERCFG                                        0x00002040U

//For Load/Read xSPI config job in OTFDE memory
#define HOST_XIP_O_OTOSMEM                                           0x00003000U

//SECGA OTFDE PROTECTION CONFIG:
#define HOST_XIP_O_OTPRTCFG                                          0x00004000U

//Region 0 key word 0
#define HOST_XIP_O_RGN0CFG0                                          0x00004004U

//Region 0 key word 1
#define HOST_XIP_O_RGN0CFG1                                          0x00004008U

//Region 0 key word 2
#define HOST_XIP_O_RGN0CFG2                                          0x0000400CU

//Region 0 key word 3
#define HOST_XIP_O_RGN0CFG3                                          0x00004010U

//Region 0 nonce word 0
#define HOST_XIP_O_RGN0CFG4                                          0x00004014U

//Region 0 nonce word 1
#define HOST_XIP_O_RGN0CFG5                                          0x00004018U

//Region 1 key word 0
#define HOST_XIP_O_RGN1CFG0                                          0x00004020U

//Region 1 key word 1
#define HOST_XIP_O_RGN1CFG1                                          0x00004024U

//Region 1 key word 2
#define HOST_XIP_O_RGN1CFG2                                          0x00004028U

//Region 1 key word 3
#define HOST_XIP_O_RGN1CFG3                                          0x0000402CU

//Region 1 nonce word 0
#define HOST_XIP_O_RGN1CFG4                                          0x00004030U

//Region 1 nonce word 1
#define HOST_XIP_O_RGN1CFG5                                          0x00004034U

//Region 2 key word 0
#define HOST_XIP_O_RGN2CFG0                                          0x00004040U

//Region 1 key word 1
#define HOST_XIP_O_RGN2CFG1                                          0x00004044U

//Region 1 key word 2
#define HOST_XIP_O_RGN2CFG2                                          0x00004048U

//Region 1 key word 3
#define HOST_XIP_O_RGN2CFG3                                          0x0000404CU

//Region 2 nonce word 0
#define HOST_XIP_O_RGN2CFG4                                          0x00004050U

//Region 2 nonce word 1
#define HOST_XIP_O_RGN2CFG5                                          0x00004054U

//Region 3 key word 0
#define HOST_XIP_O_RGN3CFG0                                          0x00004060U

//Region 3 key word 1
#define HOST_XIP_O_RGN3CFG1                                          0x00004064U

//Region 3 key word 2
#define HOST_XIP_O_RGN3CFG2                                          0x00004068U

//Region 3 key word 3
#define HOST_XIP_O_RGN3CFG3                                          0x0000406CU

//Region 3 nonce word 0
#define HOST_XIP_O_RGN3CFG4                                          0x00004070U

//Region 3 nonce word 1
#define HOST_XIP_O_RGN3CFG5                                          0x00004074U

//Pulse signaled by SW to enable OTFDE and start handling incoming tasks
#define HOST_XIP_O_OTSWCTL0                                          0x00005000U

//Pulse signaled by SW to disable OTFDE and stop handling incoming task
#define HOST_XIP_O_OTSWCTL1                                          0x00005004U

//Pulse signaled by SW to suspend OTFDE task and hold task related data
#define HOST_XIP_O_OTSWCTL2                                          0x00005008U

//Pulse signaled by SW to resume OTFDE suspended task
#define HOST_XIP_O_OTSWCTL3                                          0x0000500CU

//Pulse signaled by SW to soft reset OTFDE engine and fifo and move to active idle
#define HOST_XIP_O_OTSWCTL4                                          0x00005010U

//OTFDE status
#define HOST_XIP_O_OTSTA                                             0x00005020U

//Event indication
#define HOST_XIP_O_OTINDSTA                                          0x00005030U

//Event Masked
#define HOST_XIP_O_OTINDMASK                                         0x00005040U

//Event IRQ next state
#define HOST_XIP_O_OTINDNEXT                                         0x00005050U

//set of controller non STIG configurations
#define HOST_XIP_O_OTSTGSEL                                          0x00005060U

//Device 0 parameters
#define HOST_XIP_O_OTD0CFG                                           0x00005070U

//Device 0 polling timer parameters
#define HOST_XIP_O_OTD0PTMR                                          0x00005074U

//Device 0 wrap configuration
#define HOST_XIP_O_OTD0WRAP                                          0x00005078U

//Device 1 parameters
#define HOST_XIP_O_OTD1CFG                                           0x00005080U

//Device 1 wrap configuration
#define HOST_XIP_O_OTD1WRAP                                          0x00005084U

//Global watchdog timer
#define HOST_XIP_O_OTGLBTMR                                          0x00005090U

//region 0 parameters config 0
#define HOST_XIP_O_OTR0CFG0                                          0x00006000U

//region 0 parameters config 1
#define HOST_XIP_O_OTR0CFG1                                          0x00006004U

//region 0 parameters config 2
#define HOST_XIP_O_OTR0CFG2                                          0x00006008U

//region 0 parameters config 3
#define HOST_XIP_O_OTR0CFG3                                          0x0000600CU

//region 1 parameters config 0
#define HOST_XIP_O_OTR1CFG0                                          0x00007000U

//region 1 parameters config 1
#define HOST_XIP_O_OTR1CFG1                                          0x00007004U

//region 1 parameters config 2
#define HOST_XIP_O_OTR1CFG2                                          0x00007008U

//region 1 parameters config 3
#define HOST_XIP_O_OTR1CFG3                                          0x0000700CU

//region 2 parameters config 0
#define HOST_XIP_O_OTR2CFG0                                          0x00008000U

//region 2 parameters config 1
#define HOST_XIP_O_OTR2CFG1                                          0x00008004U

//region 2 parameters config 2
#define HOST_XIP_O_OTR2CFG2                                          0x00008008U

//region 2 parameters config 3
#define HOST_XIP_O_OTR2CFG3                                          0x0000800CU

//region 3 parameters config 0
#define HOST_XIP_O_OTR3CFG0                                          0x00009000U

//region 3 parameters config 1
#define HOST_XIP_O_OTR3CFG1                                          0x00009004U

//region 3 parameters config 2
#define HOST_XIP_O_OTR3CFG2                                          0x00009008U

//region 3 parameters config 3
#define HOST_XIP_O_OTR3CFG3                                          0x0000900CU



/*-----------------------------------REGISTER------------------------------------
    Register name:       ARBCTL
    Offset name:         HOST_XIP_O_ARBCTL
    Relative address:    0x0
    Description:         WRR Arbiter Enable
    Default Value:       0x00000003

        Field:           WRR
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     0 - Disabled, use SIE-200 arbitration logic.
                         1 - Enable, use wrapper arbitration logic.

*/
#define HOST_XIP_ARBCTL_WRR                                          0x00000001U
#define HOST_XIP_ARBCTL_WRR_M                                        0x00000001U
#define HOST_XIP_ARBCTL_WRR_S                                        0U
/*

        Field:           WRRCFG
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     WRR ARB POLICY RR:
                         0 - Fixed Priority
                         1 - Round Robin (Default)

*/
#define HOST_XIP_ARBCTL_WRRCFG                                       0x00000002U
#define HOST_XIP_ARBCTL_WRRCFG_M                                     0x00000002U
#define HOST_XIP_ARBCTL_WRRCFG_S                                     1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ARBHALT
    Offset name:         HOST_XIP_O_ARBHALT
    Relative address:    0x4
    Description:         WRR ARBITER HALT.
                        With sending halt request, Arbiter will finish current burst and then stop transmission of data.
                        Write ENABLE = 0 to stop halting
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MEM_ARBITER_HALT_EN ARBITER HALT.
                         0: Arbiter transmiting data/ disable halt
                         1: Arbiter will stop transmiting data

*/
#define HOST_XIP_ARBHALT_EN                                          0x00000001U
#define HOST_XIP_ARBHALT_EN_M                                        0x00000001U
#define HOST_XIP_ARBHALT_EN_S                                        0U
/*

        Field:           STS
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     1: Arbiter curently halted

*/
#define HOST_XIP_ARBHALT_STS                                         0x00000002U
#define HOST_XIP_ARBHALT_STS_M                                       0x00000002U
#define HOST_XIP_ARBHALT_STS_S                                       1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ARBCFG0
    Offset name:         HOST_XIP_O_ARBCFG0
    Relative address:    0x8
    Description:         WRR Arbiter - Agent 0 Configuration
    Default Value:       0x04010010

        Field:           NUMWORDS
        From..to bits:   0...12
        DefaultValue:    0x10
        Access type:     read-write
        Description:     Number of words to be served in each arbitration grant.
                         Up to 8,192 words (32KB).
                         Value must be > 0.

*/
#define HOST_XIP_ARBCFG0_NUMWORDS_W                                  13U
#define HOST_XIP_ARBCFG0_NUMWORDS_M                                  0x00001FFFU
#define HOST_XIP_ARBCFG0_NUMWORDS_S                                  0U
/*

        Field:           FIXPRI
        From..to bits:   16...17
        DefaultValue:    0x1
        Access type:     read-write
        Description:     For Fixed Priority:
                         0 - Highest.
                         1 - Medium.
                         2 - Lowest (default).

*/
#define HOST_XIP_ARBCFG0_FIXPRI_W                                    2U
#define HOST_XIP_ARBCFG0_FIXPRI_M                                    0x00030000U
#define HOST_XIP_ARBCFG0_FIXPRI_S                                    16U
/*

        Field:           TRANSDLY
        From..to bits:   24...28
        DefaultValue:    0x4
        Access type:     read-write
        Description:     Number of cycle before starting to serve next agent in line.
                         Up to 32 cycles.

*/
#define HOST_XIP_ARBCFG0_TRANSDLY_W                                  5U
#define HOST_XIP_ARBCFG0_TRANSDLY_M                                  0x1F000000U
#define HOST_XIP_ARBCFG0_TRANSDLY_S                                  24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ARBCFG1
    Offset name:         HOST_XIP_O_ARBCFG1
    Relative address:    0xC
    Description:         WRR Arbiter - Agent 1 Configuration
    Default Value:       0x00020001

        Field:           NUMWORDS
        From..to bits:   0...12
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Number of words to be served in each arbitration grant.
                         Up to 8,192 words (32KB).
                         Value must be atleast 1. 0(Zero) is not allowed.

*/
#define HOST_XIP_ARBCFG1_NUMWORDS_W                                  13U
#define HOST_XIP_ARBCFG1_NUMWORDS_M                                  0x00001FFFU
#define HOST_XIP_ARBCFG1_NUMWORDS_S                                  0U
/*

        Field:           FIXPRI
        From..to bits:   16...17
        DefaultValue:    0x2
        Access type:     read-write
        Description:     For Fixed Priority:
                         0 - Highest.
                         1 - Medium (default).
                         2 - Lowest.

*/
#define HOST_XIP_ARBCFG1_FIXPRI_W                                    2U
#define HOST_XIP_ARBCFG1_FIXPRI_M                                    0x00030000U
#define HOST_XIP_ARBCFG1_FIXPRI_S                                    16U
/*

        Field:           TRANSDLY
        From..to bits:   24...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of cycle before starting to serve next agent in line.
                         Up to 32 cycles.

*/
#define HOST_XIP_ARBCFG1_TRANSDLY_W                                  5U
#define HOST_XIP_ARBCFG1_TRANSDLY_M                                  0x1F000000U
#define HOST_XIP_ARBCFG1_TRANSDLY_S                                  24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ARBCFG2
    Offset name:         HOST_XIP_O_ARBCFG2
    Relative address:    0x10
    Description:         WRR Arbiter - Agent 2 Configuration
    Default Value:       0x04000004

        Field:           NUMWORDS
        From..to bits:   0...12
        DefaultValue:    0x4
        Access type:     read-write
        Description:     Number of words to be served in each arbitration grant.
                         Up to 8,192 words (32KB).
                         Value must be > 0.

*/
#define HOST_XIP_ARBCFG2_NUMWORDS_W                                  13U
#define HOST_XIP_ARBCFG2_NUMWORDS_M                                  0x00001FFFU
#define HOST_XIP_ARBCFG2_NUMWORDS_S                                  0U
/*

        Field:           FIXPRI
        From..to bits:   16...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     For Fixed Priority:
                         0 - Highest (default).
                         1 - Medium.
                         2 - Lowest.

*/
#define HOST_XIP_ARBCFG2_FIXPRI_W                                    2U
#define HOST_XIP_ARBCFG2_FIXPRI_M                                    0x00030000U
#define HOST_XIP_ARBCFG2_FIXPRI_S                                    16U
/*

        Field:           TRANSDLY
        From..to bits:   24...28
        DefaultValue:    0x4
        Access type:     read-write
        Description:     Number of cycle before starting to serve next agent in line.
                         Up to 32 cycles.

*/
#define HOST_XIP_ARBCFG2_TRANSDLY_W                                  5U
#define HOST_XIP_ARBCFG2_TRANSDLY_M                                  0x1F000000U
#define HOST_XIP_ARBCFG2_TRANSDLY_S                                  24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWCHDLY
    Offset name:         HOST_XIP_O_SWCHDLY
    Relative address:    0x14
    Description:         Register to configure the extra delay added before the device switch
    Default Value:       0x00000001

        Field:           DEVSWCHDLY
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     This field configures the extra delay added before the device switch

        ENUMs:
            SEL0:                        No extra delay
            SEL1:                        Extra delay of 16 cycles
            SEL2:                        Extra delay of 32 cycles
            SEL3:                        Extra delay of 64 cycles
*/
#define HOST_XIP_SWCHDLY_DEVSWCHDLY_W                                2U
#define HOST_XIP_SWCHDLY_DEVSWCHDLY_M                                0x00000003U
#define HOST_XIP_SWCHDLY_DEVSWCHDLY_S                                0U
#define HOST_XIP_SWCHDLY_DEVSWCHDLY_SEL0                             0x00000000U
#define HOST_XIP_SWCHDLY_DEVSWCHDLY_SEL1                             0x00000001U
#define HOST_XIP_SWCHDLY_DEVSWCHDLY_SEL2                             0x00000002U
#define HOST_XIP_SWCHDLY_DEVSWCHDLY_SEL3                             0x00000003U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RCMCLKDIS
    Offset name:         HOST_XIP_O_RCMCLKDIS
    Relative address:    0x20
    Description:         Disable clocks using HOST_XIP_RCM Module
    Default Value:       0x00000000

        Field:           HOSTXIP
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HOST_XIP CLK SW DISABLE:
                         1 - Clock is permanent blocked (not depended on clk_req input)
                         0 - (default) - Clock is not blocked, but gated with clk_req input port

*/
#define HOST_XIP_RCMCLKDIS_HOSTXIP                                   0x00000001U
#define HOST_XIP_RCMCLKDIS_HOSTXIP_M                                 0x00000001U
#define HOST_XIP_RCMCLKDIS_HOSTXIP_S                                 0U
/*

        Field:           SOC
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SOC CLK SW DISABLE:
                         1 - Clock is permanent blocked (not depended on clk_req input)
                         0 - (default) - Clock is not blocked, but gated with clk_req input port

*/
#define HOST_XIP_RCMCLKDIS_SOC                                       0x00000002U
#define HOST_XIP_RCMCLKDIS_SOC_M                                     0x00000002U
#define HOST_XIP_RCMCLKDIS_SOC_S                                     1U
/*

        Field:           OSPIREF
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OSPI REF CLK SW DISABLE:
                         1 - Clock is permanent blocked (not depended on clk_req input)
                         0 - (default) - Clock is not blocked, but gated with clk_req input port

*/
#define HOST_XIP_RCMCLKDIS_OSPIREF                                   0x00000004U
#define HOST_XIP_RCMCLKDIS_OSPIREF_M                                 0x00000004U
#define HOST_XIP_RCMCLKDIS_OSPIREF_S                                 2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RCMCLKFRC
    Offset name:         HOST_XIP_O_RCMCLKFRC
    Relative address:    0x24
    Description:         Force clocks using HOST_XIP_RCM Module
    Default Value:       0x00000000

        Field:           HOSTXIP
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HOST_XIP CLK SW FORCE:
                         1 - Force clk (even if sw_disable_clk is 1 or clk_req is 0)
                         0 - Clock is not forced, but gated with clk_req input port

*/
#define HOST_XIP_RCMCLKFRC_HOSTXIP                                   0x00000001U
#define HOST_XIP_RCMCLKFRC_HOSTXIP_M                                 0x00000001U
#define HOST_XIP_RCMCLKFRC_HOSTXIP_S                                 0U
/*

        Field:           SOC
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SOC CLK SW FORCE:
                         1 - Force clk (even if sw_disable_clk is 1 or clk_req is 0)
                         0 - Clock is not forced, but gated with clk_req input port

*/
#define HOST_XIP_RCMCLKFRC_SOC                                       0x00000002U
#define HOST_XIP_RCMCLKFRC_SOC_M                                     0x00000002U
#define HOST_XIP_RCMCLKFRC_SOC_S                                     1U
/*

        Field:           OSPIREF
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OSPI REF CLK SW FORCE:
                         1 - Force clk (even if sw_disable_clk is 1 or clk_req is 0)
                         0 - Clock is not forced, but gated with clk_req input port

*/
#define HOST_XIP_RCMCLKFRC_OSPIREF                                   0x00000004U
#define HOST_XIP_RCMCLKFRC_OSPIREF_M                                 0x00000004U
#define HOST_XIP_RCMCLKFRC_OSPIREF_S                                 2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RCMCLKSTA
    Offset name:         HOST_XIP_O_RCMCLKSTA
    Relative address:    0x28
    Description:         (ICG) Clock Status from HOST_XIP_RCM Module
    Default Value:       0x00000000

        Field:           HOSTXIP
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     1 - Force clk (even if sw_disable_clk is 1 or clk_req is 0)
                         0 - Clock is not forced, but gated with clk_req input port

*/
#define HOST_XIP_RCMCLKSTA_HOSTXIP                                   0x00000001U
#define HOST_XIP_RCMCLKSTA_HOSTXIP_M                                 0x00000001U
#define HOST_XIP_RCMCLKSTA_HOSTXIP_S                                 0U
/*

        Field:           SOC
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     1 - Force clk (even if sw_disable_clk is 1 or clk_req is 0)
                         0 - Clock is not forced, but gated with clk_req input port

*/
#define HOST_XIP_RCMCLKSTA_SOC                                       0x00000002U
#define HOST_XIP_RCMCLKSTA_SOC_M                                     0x00000002U
#define HOST_XIP_RCMCLKSTA_SOC_S                                     1U
/*

        Field:           OSPIREF
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     1 - Force clk (even if sw_disable_clk is 1 or clk_req is 0)
                         0 - Clock is not forced, but gated with clk_req input port

*/
#define HOST_XIP_RCMCLKSTA_OSPIREF                                   0x00000004U
#define HOST_XIP_RCMCLKSTA_OSPIREF_M                                 0x00000004U
#define HOST_XIP_RCMCLKSTA_OSPIREF_S                                 2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OSPICFG
    Offset name:         HOST_XIP_O_OSPICFG
    Relative address:    0x40
    Description:
    Default Value:       0x00000003

        Field:           HLDFIXEN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     HOLD FIX ENABLE

                         Field to enable the *OSPI* hold fix

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define HOST_XIP_OSPICFG_HLDFIXEN                                    0x00000001U
#define HOST_XIP_OSPICFG_HLDFIXEN_M                                  0x00000001U
#define HOST_XIP_OSPICFG_HLDFIXEN_S                                  0U
#define HOST_XIP_OSPICFG_HLDFIXEN_DIS                                0x00000000U
#define HOST_XIP_OSPICFG_HLDFIXEN_EN                                 0x00000001U
/*

        Field:           GLTFIXEN
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Field to enable the *OSPI* glitch fix

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define HOST_XIP_OSPICFG_GLTFIXEN                                    0x00000002U
#define HOST_XIP_OSPICFG_GLTFIXEN_M                                  0x00000002U
#define HOST_XIP_OSPICFG_GLTFIXEN_S                                  1U
#define HOST_XIP_OSPICFG_GLTFIXEN_DIS                                0x00000000U
#define HOST_XIP_OSPICFG_GLTFIXEN_EN                                 0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDSCFG0
    Offset name:         HOST_XIP_O_UDSCFG0
    Relative address:    0x1000
    Description:         uDMA source address for secured read master.
                        Must be Word aligned.
    Default Value:       0x00000000

        Field:           JSRCADDR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA SEC JOB SRC ADDR:
                         Specifies source address for secured read master.
                         Source address must comply with bit.26 to enable Sec/Non-Sec accesses, otherwise transactions will be blocked.

*/
#define HOST_XIP_UDSCFG0_JSRCADDR_W                                  32U
#define HOST_XIP_UDSCFG0_JSRCADDR_M                                  0xFFFFFFFFU
#define HOST_XIP_UDSCFG0_JSRCADDR_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDSCFG1
    Offset name:         HOST_XIP_O_UDSCFG1
    Relative address:    0x1004
    Description:         uDMA destination address for secured write master.
                        Must be Word aligned.
    Default Value:       0x00000000

        Field:           JDESTADDR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA SEC JOB DST ADDR:
                         Specifies destination address for secured write master.
                         Destination address must comply with bit.26 to enable Sec/Non-Sec accesses, otherwise transactions will be blocked.

*/
#define HOST_XIP_UDSCFG1_JDESTADDR_W                                 32U
#define HOST_XIP_UDSCFG1_JDESTADDR_M                                 0xFFFFFFFFU
#define HOST_XIP_UDSCFG1_JDESTADDR_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDSCFG2
    Offset name:         HOST_XIP_O_UDSCFG2
    Relative address:    0x1008
    Description:         uDMA secured job Length
    Default Value:       0x00000000

        Field:           JLEN
        From..to bits:   0...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA SEC JOB LENGTH:
                         Resolution - 32 bits/4 bytes
                         Maximum configurable job size - 1 Mega byte (256K Words).
                         (Maximum available size in MEMSS is 1MB).

*/
#define HOST_XIP_UDSCFG2_JLEN_W                                      18U
#define HOST_XIP_UDSCFG2_JLEN_M                                      0x0003FFFFU
#define HOST_XIP_UDSCFG2_JLEN_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDSCFG3
    Offset name:         HOST_XIP_O_UDSCFG3
    Relative address:    0x100C
    Description:         uDMA Direction
    Default Value:       0x00000000

        Field:           JDIR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA SEC JOB MODE:
                         0 - Data movement from External memory to Internal memory/Peripheral
                         1 - Data movement from Internal memory/Peripheral to External memory.

*/
#define HOST_XIP_UDSCFG3_JDIR                                        0x00000001U
#define HOST_XIP_UDSCFG3_JDIR_M                                      0x00000001U
#define HOST_XIP_UDSCFG3_JDIR_S                                      0U
/*

        Field:           SMODE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Secure channel mode
                         0: Memory Mode
                         1: Peripheral Mode

*/
#define HOST_XIP_UDSCFG3_SMODE                                       0x00000002U
#define HOST_XIP_UDSCFG3_SMODE_M                                     0x00000002U
#define HOST_XIP_UDSCFG3_SMODE_S                                     1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDSCTL0
    Offset name:         HOST_XIP_O_UDSCTL0
    Relative address:    0x1010
    Description:         uDMA secured job kick
    Default Value:       0x00000000

        Field:           JSTART
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     DMA SEC JOB START WRCL:
                         Start command for uDMA to start working on secured configured job.

*/
#define HOST_XIP_UDSCTL0_JSTART                                      0x00000001U
#define HOST_XIP_UDSCTL0_JSTART_M                                    0x00000001U
#define HOST_XIP_UDSCTL0_JSTART_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDSCTL1
    Offset name:         HOST_XIP_O_UDSCTL1
    Relative address:    0x1014
    Description:         uDMA secured job abort
    Default Value:       0x00000000

        Field:           JCLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     DMA SEC JOB CLEAR WRCL:
                         Clear command for uDMA to stop working and clear configuration.

*/
#define HOST_XIP_UDSCTL1_JCLR                                        0x00000001U
#define HOST_XIP_UDSCTL1_JCLR_M                                      0x00000001U
#define HOST_XIP_UDSCTL1_JCLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDSSTA
    Offset name:         HOST_XIP_O_UDSSTA
    Relative address:    0x1020
    Description:         uDMA secured Status bits
    Default Value:       0x00000000

        Field:           JSTA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DMA SEC JOB ACTIVE:
                         Status bit to indicate that DMA is processing a secured job.
                         When this bit is set, SW has written all the job parameters and also provided a start_pulse to HW,
                         and cannot change job parameters without clear_pulse.
                         Job will wait to be executed (indicated by job_in_progress)

*/
#define HOST_XIP_UDSSTA_JSTA                                         0x00000001U
#define HOST_XIP_UDSSTA_JSTA_M                                       0x00000001U
#define HOST_XIP_UDSSTA_JSTA_S                                       0U
/*

        Field:           JINPROG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DMA SEC JOB IN PROGRESS:
                         1- sec job is currently in progress and being executed by uDMA

*/
#define HOST_XIP_UDSSTA_JINPROG                                      0x00000010U
#define HOST_XIP_UDSSTA_JINPROG_M                                    0x00000010U
#define HOST_XIP_UDSSTA_JINPROG_S                                    4U
/*

        Field:           RDWRDSLFT
        From..to bits:   8...27
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DMA SEC JOB READ WORDS LEFT:
                         number of read words left in sec job.
                         Note: This value would be updated on a read to this register. [UDSSTA1.WRWRDSLFT] is updated on a read to this register
                         This register value shows number of words in 32 bit when field [UDSCFG3.JDIR] is configured '0' else shows number of words in 8/16/32 bit based on the configuration of [UDSCFG3.SMODE] and [UDPERCFG.SWORDSZ] fields

*/
#define HOST_XIP_UDSSTA_RDWRDSLFT_W                                  20U
#define HOST_XIP_UDSSTA_RDWRDSLFT_M                                  0x0FFFFF00U
#define HOST_XIP_UDSSTA_RDWRDSLFT_S                                  8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDSIRQ
    Offset name:         HOST_XIP_O_UDSIRQ
    Relative address:    0x1024
    Description:         uDMA secured IRQ Status bits
    Default Value:       0x00000000

        Field:           JIRQSTA
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status vector for IRQ indication for secured DMA IRQ:
                         2'd0 - DMA done.
                         2'd1 - DMA Internal bus error occurred. check SEC_STATUS in order to recovers

*/
#define HOST_XIP_UDSIRQ_JIRQSTA_W                                    2U
#define HOST_XIP_UDSIRQ_JIRQSTA_M                                    0x00000003U
#define HOST_XIP_UDSIRQ_JIRQSTA_S                                    0U
/*

        Field:           JIRQBEDIR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bus Error direction
                         0: Source bus
                         1: Destination bus
                         Note: Source and destination is determined based on [UDMA_SEC_MODE_CFG.MEM_DMA_SEC_JOB_MODE] configuration

*/
#define HOST_XIP_UDSIRQ_JIRQBEDIR                                    0x00000004U
#define HOST_XIP_UDSIRQ_JIRQBEDIR_M                                  0x00000004U
#define HOST_XIP_UDSIRQ_JIRQBEDIR_S                                  2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDSSTA1
    Offset name:         HOST_XIP_O_UDSSTA1
    Relative address:    0x102C
    Description:         uDMA secured Status bits in addition to [UDMSSTA] register
    Default Value:       NA

        Field:           WRDOFST
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     DMA SEC PERIPH WORD OFFSET:
                         Number of words left in a peripheral block.
                         Note: This value would be updated only on a read to [UDSSTA] register.
                         This register value shows number of words in 8/16/32 bit based on the configuration of [UDSCFG3.SMODE] and [UDPERCFG.SWORDSZ] fields

*/
#define HOST_XIP_UDSSTA1_WRDOFST_W                                   8U
#define HOST_XIP_UDSSTA1_WRDOFST_M                                   0x000000FFU
#define HOST_XIP_UDSSTA1_WRDOFST_S                                   0U
/*

        Field:           WRWRDSLFT
        From..to bits:   8...27
        DefaultValue:    NA
        Access type:     read-only
        Description:     DMA SEC JOB WRITE WORDS LEFT:
                         Number of write words left in sec job.
                         Note: This value would be updated only on a read to [UDSSTA] register.
                         This register value shows number of words in 32 bit when field [UDSCFG3.JDIR] is configured '1' else shows number of words in 8/16/32 bit based on the configuration of [UDSCFG3.SMODE] and [UDPERCFG.SWORDSZ] fields

*/
#define HOST_XIP_UDSSTA1_WRWRDSLFT_W                                 20U
#define HOST_XIP_UDSSTA1_WRWRDSLFT_M                                 0x0FFFFF00U
#define HOST_XIP_UDSSTA1_WRWRDSLFT_S                                 8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDSPERCFG
    Offset name:         HOST_XIP_O_UDSPERCFG
    Relative address:    0x1040
    Description:         uDMA Secure channel peripheral config register
    Default Value:       0x00000000

        Field:           SPERWDSZ
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Secure channel peripheral job word size
                         8/16/32 (Word Size of 1/2/4 bytes)
                         Sel_0 - 32 bit
                         Sel_1 -  16 bit
                         Sel_2 - 8 bit

*/
#define HOST_XIP_UDSPERCFG_SPERWDSZ_W                                2U
#define HOST_XIP_UDSPERCFG_SPERWDSZ_M                                0x00000003U
#define HOST_XIP_UDSPERCFG_SPERWDSZ_S                                0U
/*

        Field:           SPERBLKSZ
        From..to bits:   2...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Secure channel peripheral block size(in 32bits/4bytes)
                         Multiplication of Word size

                         Upto 64 words based on the word size selected

                         Block = block_size * word_size

*/
#define HOST_XIP_UDSPERCFG_SPERBLKSZ_W                               6U
#define HOST_XIP_UDSPERCFG_SPERBLKSZ_M                               0x000000FCU
#define HOST_XIP_UDSPERCFG_SPERBLKSZ_S                               2U
/*

        Field:           SENCLRSRT
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable uDMA to set a rd/wr clear pulse at the beginning of a job

*/
#define HOST_XIP_UDSPERCFG_SENCLRSRT                                 0x00000100U
#define HOST_XIP_UDSPERCFG_SENCLRSRT_M                               0x00000100U
#define HOST_XIP_UDSPERCFG_SENCLRSRT_S                               8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDSPERSEL
    Offset name:         HOST_XIP_O_UDSPERSEL
    Relative address:    0x1060
    Description:         Register to select the peripheral to be served on secured channel
    Default Value:       0x00000000

        Field:           SPERSEL
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Select the peripheral to serve job. This field along with [UDMA_SEC_MODE.MEM_SEC_MODE] selects the peripheral to the channel
                         0x0 UART0
                         0x1 UART1
                         0x2 SPI0
                         0x3 SPI1
                         0x4 I2C0
                         0x5 I2C1
                         0x6 SDMMC
                         0x7 SDIO
                         0x8 MCAN
                         0x9 ADC
                         0xA PDM
                         0xB HIF


*/
#define HOST_XIP_UDSPERSEL_SPERSEL_W                                 4U
#define HOST_XIP_UDSPERSEL_SPERSEL_M                                 0x0000000FU
#define HOST_XIP_UDSPERSEL_SPERSEL_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDNSPERSEL
    Offset name:         HOST_XIP_O_UDNSPERSEL
    Relative address:    0x1064
    Description:         Register to select the peripheral to be served on non secured channel
    Default Value:       0x00000000

        Field:           NSPERSEL
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Select the peripheral to serve job. This field along with [UDMA_NONSEC_MODE.MEM_NON_SEC_MODE] selects the peripheral to the channel
                         0x0 UART0
                         0x1 UART1
                         0x2 SPI0
                         0x3 SPI1
                         0x4 I2C0
                         0x5 I2C1
                         0x6 SDMMC
                         0x7 SDIO
                         0x8 MCAN
                         0x9 ADC
                         0xA PDM
                         0xB HIF

*/
#define HOST_XIP_UDNSPERSEL_NSPERSEL_W                               4U
#define HOST_XIP_UDNSPERSEL_NSPERSEL_M                               0x0000000FU
#define HOST_XIP_UDNSPERSEL_NSPERSEL_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDNSCFG0
    Offset name:         HOST_XIP_O_UDNSCFG0
    Relative address:    0x2000
    Description:         uDMA source address for non-secured read master.
                        Must be Word aligned.
    Default Value:       0x00000000

        Field:           JSRCADDR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA NONSEC JOB SRC ADDR:
                         Specifies source address for non-secured read master.
                         Source address must comply with bit.26 to enable Sec/Non-Sec accesses, otherwise transactions will be blocked.
                         In case using SAU to define secured memory region 'inside' the non-secured, this channel will allow this.

*/
#define HOST_XIP_UDNSCFG0_JSRCADDR_W                                 32U
#define HOST_XIP_UDNSCFG0_JSRCADDR_M                                 0xFFFFFFFFU
#define HOST_XIP_UDNSCFG0_JSRCADDR_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDNSCFG1
    Offset name:         HOST_XIP_O_UDNSCFG1
    Relative address:    0x2004
    Description:         uDMA destination address for non-secured write master.
                        Must be Word aligned.
    Default Value:       0x00000000

        Field:           JDESTADDR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA NONSEC JOB DST ADDR:
                         Specifies destination address for non-secured write master.
                         Destination address must comply with bit.26 to enable Sec/Non-Sec accesses, otherwise transactions will be blocked.
                         In case using SAU to define secured memory region 'inside' the non-secured, this channel will allow this.

*/
#define HOST_XIP_UDNSCFG1_JDESTADDR_W                                32U
#define HOST_XIP_UDNSCFG1_JDESTADDR_M                                0xFFFFFFFFU
#define HOST_XIP_UDNSCFG1_JDESTADDR_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDNSCFG2
    Offset name:         HOST_XIP_O_UDNSCFG2
    Relative address:    0x2008
    Description:         uDMA non-secured job Length
    Default Value:       0x00000000

        Field:           JLEN
        From..to bits:   0...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA NONSEC JOB LENGTH:
                         Resolution - 32 bits/4bytes
                         Maximum configurable job size - 1 Mega byte (256K Words).
                         (Maximum available size in MEMSS is 1MB).

*/
#define HOST_XIP_UDNSCFG2_JLEN_W                                     18U
#define HOST_XIP_UDNSCFG2_JLEN_M                                     0x0003FFFFU
#define HOST_XIP_UDNSCFG2_JLEN_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDNSCFG3
    Offset name:         HOST_XIP_O_UDNSCFG3
    Relative address:    0x200C
    Description:         uDMA Direction
    Default Value:       0x00000000

        Field:           JDIR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA NONSEC JOB MODE:
                         0 - Data movement from External memory to Internal memory.
                         1 - Data movement from Internal memory to External memory.

*/
#define HOST_XIP_UDNSCFG3_JDIR                                       0x00000001U
#define HOST_XIP_UDNSCFG3_JDIR_M                                     0x00000001U
#define HOST_XIP_UDNSCFG3_JDIR_S                                     0U
/*

        Field:           NSMODE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Non secure channel mode
                         0: Memory Mode
                         1: Peripheral Mode

*/
#define HOST_XIP_UDNSCFG3_NSMODE                                     0x00000002U
#define HOST_XIP_UDNSCFG3_NSMODE_M                                   0x00000002U
#define HOST_XIP_UDNSCFG3_NSMODE_S                                   1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDNSCTL0
    Offset name:         HOST_XIP_O_UDNSCTL0
    Relative address:    0x2010
    Description:         uDMA non-secured job kick
    Default Value:       0x00000000

        Field:           JSTART
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     DMA NONSEC JOB START WRCL:
                         Start command for uDMA to start working on non-secured configured job.

*/
#define HOST_XIP_UDNSCTL0_JSTART                                     0x00000001U
#define HOST_XIP_UDNSCTL0_JSTART_M                                   0x00000001U
#define HOST_XIP_UDNSCTL0_JSTART_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDNSCTL1
    Offset name:         HOST_XIP_O_UDNSCTL1
    Relative address:    0x2014
    Description:         uDMA non-secured job abort
    Default Value:       0x00000000

        Field:           JCLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     DMA NONSEC JOB CLEAR WRCL:
                         Clear command for uDMA to stop working and clear configuration.

*/
#define HOST_XIP_UDNSCTL1_JCLR                                       0x00000001U
#define HOST_XIP_UDNSCTL1_JCLR_M                                     0x00000001U
#define HOST_XIP_UDNSCTL1_JCLR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDNSSTA
    Offset name:         HOST_XIP_O_UDNSSTA
    Relative address:    0x2020
    Description:         uDMA non-secured Status bits
    Default Value:       0x00000000

        Field:           JSTA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DMA NONSEC JOB ACTIVE:
                         Status bit to indicate that DMA is processing a non-secured job.
                         When this bit is set, SW has written all the job parameters and also provided a start_pulse to HW,
                         and cannot change job parameters without clear_pulse.
                         Job will wait to be executed (indicated by job_in_progress)

*/
#define HOST_XIP_UDNSSTA_JSTA                                        0x00000001U
#define HOST_XIP_UDNSSTA_JSTA_M                                      0x00000001U
#define HOST_XIP_UDNSSTA_JSTA_S                                      0U
/*

        Field:           JINPROG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DMA NONSEC JOB IN PROGRESS:
                         1- nonsec job is currently in progress and being executed by uDMA

*/
#define HOST_XIP_UDNSSTA_JINPROG                                     0x00000010U
#define HOST_XIP_UDNSSTA_JINPROG_M                                   0x00000010U
#define HOST_XIP_UDNSSTA_JINPROG_S                                   4U
/*

        Field:           RDWRDSLFT
        From..to bits:   8...27
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DMA NONSEC JOB READ WORDS LEFT:
                         Number of read words left in nonsec job
                         Note: This value would be updated on a read to this register. [UDNSSTA1.WRWRDSLFT] is updated on a read to this register
                         This register value shows number of words in 32 bit when field [UDNSCFG3.JDIR] is configured '0' else shows number of words in 8/16/32 bit based on the configuration of [UDNSCFG3.NSMODE] and [UDPERCFG.NSWORDSZ] fields

*/
#define HOST_XIP_UDNSSTA_RDWRDSLFT_W                                 20U
#define HOST_XIP_UDNSSTA_RDWRDSLFT_M                                 0x0FFFFF00U
#define HOST_XIP_UDNSSTA_RDWRDSLFT_S                                 8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDNSIRQ
    Offset name:         HOST_XIP_O_UDNSIRQ
    Relative address:    0x2024
    Description:         uDMA non-secured IRQ Status bits
    Default Value:       0x00000000

        Field:           JIRQSTA
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status vector for IRQ indication for non-secured DMA IRQ:
                         2'd0 - DMA done.
                         2'd1 - DMA bus error occurred. check NONSEC_STATUS in order to recovers

*/
#define HOST_XIP_UDNSIRQ_JIRQSTA_W                                   2U
#define HOST_XIP_UDNSIRQ_JIRQSTA_M                                   0x00000003U
#define HOST_XIP_UDNSIRQ_JIRQSTA_S                                   0U
/*

        Field:           JIRQBEDIR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bus Error direction
                         0: Source bus
                         1: Destination bus
                         Note: Source and destination is determined based on [UDMA_NONSEC_MODE_CFG.MEM_DMA_NONSEC_JOB_MODE] configuration

*/
#define HOST_XIP_UDNSIRQ_JIRQBEDIR                                   0x00000004U
#define HOST_XIP_UDNSIRQ_JIRQBEDIR_M                                 0x00000004U
#define HOST_XIP_UDNSIRQ_JIRQBEDIR_S                                 2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UTHRCNF
    Offset name:         HOST_XIP_O_UTHRCNF
    Relative address:    0x2028
    Description:         uDMA threshold configuration
    Default Value:       0x00000090

        Field:           THRVAL
        From..to bits:   0...4
        DefaultValue:    0x10
        Access type:     read-write
        Description:     FIFO WRITE THRESHOLD:
                         In case of write to ext mem, uDMA will reach the threshold and after that will send the data to the ext mem
                         Note: 0(Zero) is not allowed

*/
#define HOST_XIP_UTHRCNF_THRVAL_W                                    5U
#define HOST_XIP_UTHRCNF_THRVAL_M                                    0x0000001FU
#define HOST_XIP_UTHRCNF_THRVAL_S                                    0U
/*

        Field:           BURSTVAL
        From..to bits:   5...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FIFO WRITE BURST LEN:
                         After uDMA will reached the threshold, uDMA will sent the data in blocks.
                         0x0 : block size = 4   word
                         0x1 : block size = 8   word
                         0x2 : block size = 16 word
                         0x3 : block size = 32 word

*/
#define HOST_XIP_UTHRCNF_BURSTVAL_W                                  2U
#define HOST_XIP_UTHRCNF_BURSTVAL_M                                  0x00000060U
#define HOST_XIP_UTHRCNF_BURSTVAL_S                                  5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDNSSTA1
    Offset name:         HOST_XIP_O_UDNSSTA1
    Relative address:    0x202C
    Description:         uDMA non-secured Status bits in addition to [UDNSSTA] register
    Default Value:       NA

        Field:           WRWRDSLFT
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     DMA NONSEC PERIPH WORD OFFSET:
                         Number of words left in a peripheral block.
                         Note: This value would be updated only on a read to [UDNSSTA] register.
                         This register value shows number of words in 8/16/32 bit based on the configuration of [UDNSCFG3.NSMODE] and [UDPERCFG.NSWORDSZ] fields

*/
#define HOST_XIP_UDNSSTA1_WRWRDSLFT_W                                8U
#define HOST_XIP_UDNSSTA1_WRWRDSLFT_M                                0x000000FFU
#define HOST_XIP_UDNSSTA1_WRWRDSLFT_S                                0U
/*

        Field:           WRDOFST
        From..to bits:   8...27
        DefaultValue:    NA
        Access type:     read-only
        Description:     DMA NONSEC JOB WRITE WORDS LEFT:
                         Number of write words left in nonsec job.
                         Note: This value would be updated only on a read to [UDNSSTA] register.
                         This register value shows number of words in 32 bit when field [UDNSCFG3.JDIR] is configured '1' else shows number of words in 8/16/32 bit based on the configuration of [UDNSCFG3.NSMODE] and [UDPERCFG.NSWORDSZ] fields

*/
#define HOST_XIP_UDNSSTA1_WRDOFST_W                                  20U
#define HOST_XIP_UDNSSTA1_WRDOFST_M                                  0x0FFFFF00U
#define HOST_XIP_UDNSSTA1_WRDOFST_S                                  8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDNSPERCFG
    Offset name:         HOST_XIP_O_UDNSPERCFG
    Relative address:    0x2040
    Description:         Non secure peirpheral job configuration
    Default Value:       0x00000000

        Field:           NSPERWDSZ
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Non-secure channel peripheral job word size
                         8/16/32 (Word Size of 1/2/4 bytes)

                         Sel_0 - 32 bit
                         Sel_1 -  16 bit
                         Sel_2 - 8 bit

*/
#define HOST_XIP_UDNSPERCFG_NSPERWDSZ_W                              2U
#define HOST_XIP_UDNSPERCFG_NSPERWDSZ_M                              0x00000003U
#define HOST_XIP_UDNSPERCFG_NSPERWDSZ_S                              0U
/*

        Field:           NSPERBLSZ
        From..to bits:   2...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Non-secure channel peripheral job block size(in 32bits/4bytes)
                         Multiplication of Word size.

                         Upto 64 words based on Word size

                         Block = block_size * word_size

*/
#define HOST_XIP_UDNSPERCFG_NSPERBLSZ_W                              6U
#define HOST_XIP_UDNSPERCFG_NSPERBLSZ_M                              0x000000FCU
#define HOST_XIP_UDNSPERCFG_NSPERBLSZ_S                              2U
/*

        Field:           NSENCLRSRT
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable uDMA to set a rd/wr clear pulse at the beginning of a job

*/
#define HOST_XIP_UDNSPERCFG_NSENCLRSRT                               0x00000100U
#define HOST_XIP_UDNSPERCFG_NSENCLRSRT_M                             0x00000100U
#define HOST_XIP_UDNSPERCFG_NSENCLRSRT_S                             8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTOSMEM
    Offset name:         HOST_XIP_O_OTOSMEM
    Relative address:    0x3000
    Description:         For Load/Read xSPI config job in OTFDE memory
    Default Value:       0x00000000

        Field:           WDATACFG
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE CFG OSPI 81FC WR MEM
                         xSPI config Memory wr/rd access (under OTFDE module)

*/
#define HOST_XIP_OTOSMEM_WDATACFG_W                                  32U
#define HOST_XIP_OTOSMEM_WDATACFG_M                                  0xFFFFFFFFU
#define HOST_XIP_OTOSMEM_WDATACFG_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTPRTCFG
    Offset name:         HOST_XIP_O_OTPRTCFG
    Relative address:    0x4000
    Description:         SECGA OTFDE PROTECTION CONFIG:
                        General OTFDE protection Configurations
    Default Value:       0x0000000A

        Field:           INITDLY
        From..to bits:   0...3
        DefaultValue:    0xA
        Access type:     read-write
        Description:     OTFDE INITIAL DELAY:
                         0-15 160MHz cycles of initial delay of the first transaction of a task
                         must configure value greater than 10 (0xa)

*/
#define HOST_XIP_OTPRTCFG_INITDLY_W                                  4U
#define HOST_XIP_OTPRTCFG_INITDLY_M                                  0x0000000FU
#define HOST_XIP_OTPRTCFG_INITDLY_S                                  0U
/*

        Field:           R0WRLOCK
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE REGION 0 WRITE LOCK EN:
                         Locks the ability to write into Region 0 registers
                         0- Lock Disabled
                         1- Lock Enabled

*/
#define HOST_XIP_OTPRTCFG_R0WRLOCK                                   0x00000010U
#define HOST_XIP_OTPRTCFG_R0WRLOCK_M                                 0x00000010U
#define HOST_XIP_OTPRTCFG_R0WRLOCK_S                                 4U
/*

        Field:           R0ENCBPASS
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE REGION 0 ENC DEC BYPASS:
                         Encrypt  Decrypt or Bypass transactions for region 0
                         0- Enable bypass and no enc dec
                         1- Disable bypass and use enc dec

*/
#define HOST_XIP_OTPRTCFG_R0ENCBPASS                                 0x00000020U
#define HOST_XIP_OTPRTCFG_R0ENCBPASS_M                               0x00000020U
#define HOST_XIP_OTPRTCFG_R0ENCBPASS_S                               5U
/*

        Field:           R1WRLOCK
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE REGION 1 WRITE LOCK EN:
                         Locks the ability to write into Region 1 registers
                         0- Lock Disabled
                         1- Lock Enabled

*/
#define HOST_XIP_OTPRTCFG_R1WRLOCK                                   0x00000100U
#define HOST_XIP_OTPRTCFG_R1WRLOCK_M                                 0x00000100U
#define HOST_XIP_OTPRTCFG_R1WRLOCK_S                                 8U
/*

        Field:           R1ENCBPASS
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE REGION 1 ENC DEC BYPASS:
                         Encrypt  Decrypt or Bypass transactions for region 1
                         0- Enable bypass and no enc dec
                         1- Disable bypass and use enc dec

*/
#define HOST_XIP_OTPRTCFG_R1ENCBPASS                                 0x00000200U
#define HOST_XIP_OTPRTCFG_R1ENCBPASS_M                               0x00000200U
#define HOST_XIP_OTPRTCFG_R1ENCBPASS_S                               9U
/*

        Field:           R2WRLOCK
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE REGION 2 WRITE LOCK EN:
                         Locks the ability to write into Region 2 registers
                         0- Lock Disabled
                         1- Lock Enabled

*/
#define HOST_XIP_OTPRTCFG_R2WRLOCK                                   0x00001000U
#define HOST_XIP_OTPRTCFG_R2WRLOCK_M                                 0x00001000U
#define HOST_XIP_OTPRTCFG_R2WRLOCK_S                                 12U
/*

        Field:           R2ENCBPASS
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE REGION 2 ENC DEC BYPASS:
                         Encrypt  Decrypt or Bypass transactions for region 2
                         0- Enable bypass and no enc dec
                         1- Disable bypass and use enc dec

*/
#define HOST_XIP_OTPRTCFG_R2ENCBPASS                                 0x00002000U
#define HOST_XIP_OTPRTCFG_R2ENCBPASS_M                               0x00002000U
#define HOST_XIP_OTPRTCFG_R2ENCBPASS_S                               13U
/*

        Field:           R3WRLOCK
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE REGION 3 WRITE LOCK EN:
                         Locks the ability to write into Region 3 registers
                         0- Lock Disabled
                         1- Lock Enabled

*/
#define HOST_XIP_OTPRTCFG_R3WRLOCK                                   0x00010000U
#define HOST_XIP_OTPRTCFG_R3WRLOCK_M                                 0x00010000U
#define HOST_XIP_OTPRTCFG_R3WRLOCK_S                                 16U
/*

        Field:           R3ENCBPASS
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE REGION 3 ENC DEC BYPASS:
                         Encrypt  Decrypt or Bypass transactions for region 3
                         0- Enable bypass and no enc dec
                         1- Disable bypass and use enc dec

*/
#define HOST_XIP_OTPRTCFG_R3ENCBPASS                                 0x00020000U
#define HOST_XIP_OTPRTCFG_R3ENCBPASS_M                               0x00020000U
#define HOST_XIP_OTPRTCFG_R3ENCBPASS_S                               17U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN0CFG0
    Offset name:         HOST_XIP_O_RGN0CFG0
    Relative address:    0x4004
    Description:         Region 0 key word 0
    Default Value:       0x00000000

        Field:           KEY0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key LSBs

*/
#define HOST_XIP_RGN0CFG0_KEY0_W                                     32U
#define HOST_XIP_RGN0CFG0_KEY0_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN0CFG0_KEY0_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN0CFG1
    Offset name:         HOST_XIP_O_RGN0CFG1
    Relative address:    0x4008
    Description:         Region 0 key word 1
    Default Value:       0x00000000

        Field:           KEY1
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key

*/
#define HOST_XIP_RGN0CFG1_KEY1_W                                     32U
#define HOST_XIP_RGN0CFG1_KEY1_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN0CFG1_KEY1_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN0CFG2
    Offset name:         HOST_XIP_O_RGN0CFG2
    Relative address:    0x400C
    Description:         Region 0 key word 2
    Default Value:       0x00000000

        Field:           KEY2
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key

*/
#define HOST_XIP_RGN0CFG2_KEY2_W                                     32U
#define HOST_XIP_RGN0CFG2_KEY2_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN0CFG2_KEY2_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN0CFG3
    Offset name:         HOST_XIP_O_RGN0CFG3
    Relative address:    0x4010
    Description:         Region 0 key word 3
    Default Value:       0x00000000

        Field:           KEY3
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key MSBs

*/
#define HOST_XIP_RGN0CFG3_KEY3_W                                     32U
#define HOST_XIP_RGN0CFG3_KEY3_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN0CFG3_KEY3_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN0CFG4
    Offset name:         HOST_XIP_O_RGN0CFG4
    Relative address:    0x4014
    Description:         Region 0 nonce word 0
    Default Value:       0x00000000

        Field:           NONCE0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Nonce (IV)

*/
#define HOST_XIP_RGN0CFG4_NONCE0_W                                   32U
#define HOST_XIP_RGN0CFG4_NONCE0_M                                   0xFFFFFFFFU
#define HOST_XIP_RGN0CFG4_NONCE0_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN0CFG5
    Offset name:         HOST_XIP_O_RGN0CFG5
    Relative address:    0x4018
    Description:         Region 0 nonce word 1
    Default Value:       0x00000000

        Field:           NONCE1
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Nonce (IV)

*/
#define HOST_XIP_RGN0CFG5_NONCE1_W                                   32U
#define HOST_XIP_RGN0CFG5_NONCE1_M                                   0xFFFFFFFFU
#define HOST_XIP_RGN0CFG5_NONCE1_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN1CFG0
    Offset name:         HOST_XIP_O_RGN1CFG0
    Relative address:    0x4020
    Description:         Region 1 key word 0
    Default Value:       0x00000000

        Field:           KEY0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key LSBs

*/
#define HOST_XIP_RGN1CFG0_KEY0_W                                     32U
#define HOST_XIP_RGN1CFG0_KEY0_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN1CFG0_KEY0_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN1CFG1
    Offset name:         HOST_XIP_O_RGN1CFG1
    Relative address:    0x4024
    Description:         Region 1 key word 1
    Default Value:       0x00000000

        Field:           KEY1
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key

*/
#define HOST_XIP_RGN1CFG1_KEY1_W                                     32U
#define HOST_XIP_RGN1CFG1_KEY1_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN1CFG1_KEY1_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN1CFG2
    Offset name:         HOST_XIP_O_RGN1CFG2
    Relative address:    0x4028
    Description:         Region 1 key word 2
    Default Value:       0x00000000

        Field:           KEY2
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key

*/
#define HOST_XIP_RGN1CFG2_KEY2_W                                     32U
#define HOST_XIP_RGN1CFG2_KEY2_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN1CFG2_KEY2_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN1CFG3
    Offset name:         HOST_XIP_O_RGN1CFG3
    Relative address:    0x402C
    Description:         Region 1 key word 3
    Default Value:       0x00000000

        Field:           KEY3
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key MSBs

*/
#define HOST_XIP_RGN1CFG3_KEY3_W                                     32U
#define HOST_XIP_RGN1CFG3_KEY3_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN1CFG3_KEY3_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN1CFG4
    Offset name:         HOST_XIP_O_RGN1CFG4
    Relative address:    0x4030
    Description:         Region 1 nonce word 0
    Default Value:       0x00000000

        Field:           NONCE0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Nonce (IV)

*/
#define HOST_XIP_RGN1CFG4_NONCE0_W                                   32U
#define HOST_XIP_RGN1CFG4_NONCE0_M                                   0xFFFFFFFFU
#define HOST_XIP_RGN1CFG4_NONCE0_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN1CFG5
    Offset name:         HOST_XIP_O_RGN1CFG5
    Relative address:    0x4034
    Description:         Region 1 nonce word 1
    Default Value:       0x00000000

        Field:           NONCE1
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Nonce (IV)

*/
#define HOST_XIP_RGN1CFG5_NONCE1_W                                   32U
#define HOST_XIP_RGN1CFG5_NONCE1_M                                   0xFFFFFFFFU
#define HOST_XIP_RGN1CFG5_NONCE1_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN2CFG0
    Offset name:         HOST_XIP_O_RGN2CFG0
    Relative address:    0x4040
    Description:         Region 2 key word 0
    Default Value:       0x00000000

        Field:           KEY0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key LSBs

*/
#define HOST_XIP_RGN2CFG0_KEY0_W                                     32U
#define HOST_XIP_RGN2CFG0_KEY0_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN2CFG0_KEY0_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN2CFG1
    Offset name:         HOST_XIP_O_RGN2CFG1
    Relative address:    0x4044
    Description:         Region 1 key word 1
    Default Value:       0x00000000

        Field:           KEY1
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key

*/
#define HOST_XIP_RGN2CFG1_KEY1_W                                     32U
#define HOST_XIP_RGN2CFG1_KEY1_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN2CFG1_KEY1_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN2CFG2
    Offset name:         HOST_XIP_O_RGN2CFG2
    Relative address:    0x4048
    Description:         Region 1 key word 2
    Default Value:       0x00000000

        Field:           KEY2
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key

*/
#define HOST_XIP_RGN2CFG2_KEY2_W                                     32U
#define HOST_XIP_RGN2CFG2_KEY2_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN2CFG2_KEY2_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN2CFG3
    Offset name:         HOST_XIP_O_RGN2CFG3
    Relative address:    0x404C
    Description:         Region 1 key word 3
    Default Value:       0x00000000

        Field:           KEY3
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key MSBs

*/
#define HOST_XIP_RGN2CFG3_KEY3_W                                     32U
#define HOST_XIP_RGN2CFG3_KEY3_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN2CFG3_KEY3_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN2CFG4
    Offset name:         HOST_XIP_O_RGN2CFG4
    Relative address:    0x4050
    Description:         Region 2 nonce word 0
    Default Value:       0x00000000

        Field:           NONCE0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Nonce (IV)

*/
#define HOST_XIP_RGN2CFG4_NONCE0_W                                   32U
#define HOST_XIP_RGN2CFG4_NONCE0_M                                   0xFFFFFFFFU
#define HOST_XIP_RGN2CFG4_NONCE0_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN2CFG5
    Offset name:         HOST_XIP_O_RGN2CFG5
    Relative address:    0x4054
    Description:         Region 2 nonce word 1
    Default Value:       0x00000000

        Field:           NONCE1
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Nonce (IV)

*/
#define HOST_XIP_RGN2CFG5_NONCE1_W                                   32U
#define HOST_XIP_RGN2CFG5_NONCE1_M                                   0xFFFFFFFFU
#define HOST_XIP_RGN2CFG5_NONCE1_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN3CFG0
    Offset name:         HOST_XIP_O_RGN3CFG0
    Relative address:    0x4060
    Description:         Region 3 key word 0
    Default Value:       0x00000000

        Field:           KEY0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key LSBs

*/
#define HOST_XIP_RGN3CFG0_KEY0_W                                     32U
#define HOST_XIP_RGN3CFG0_KEY0_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN3CFG0_KEY0_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN3CFG1
    Offset name:         HOST_XIP_O_RGN3CFG1
    Relative address:    0x4064
    Description:         Region 3 key word 1
    Default Value:       0x00000000

        Field:           KEY1
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key

*/
#define HOST_XIP_RGN3CFG1_KEY1_W                                     32U
#define HOST_XIP_RGN3CFG1_KEY1_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN3CFG1_KEY1_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN3CFG2
    Offset name:         HOST_XIP_O_RGN3CFG2
    Relative address:    0x4068
    Description:         Region 3 key word 2
    Default Value:       0x00000000

        Field:           KEY2
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key

*/
#define HOST_XIP_RGN3CFG2_KEY2_W                                     32U
#define HOST_XIP_RGN3CFG2_KEY2_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN3CFG2_KEY2_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN3CFG3
    Offset name:         HOST_XIP_O_RGN3CFG3
    Relative address:    0x406C
    Description:         Region 3 key word 3
    Default Value:       0x00000000

        Field:           KEY3
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AES encryption Key MSBs

*/
#define HOST_XIP_RGN3CFG3_KEY3_W                                     32U
#define HOST_XIP_RGN3CFG3_KEY3_M                                     0xFFFFFFFFU
#define HOST_XIP_RGN3CFG3_KEY3_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN3CFG4
    Offset name:         HOST_XIP_O_RGN3CFG4
    Relative address:    0x4070
    Description:         Region 3 nonce word 0
    Default Value:       0x00000000

        Field:           NONCE0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Nonce (IV)

*/
#define HOST_XIP_RGN3CFG4_NONCE0_W                                   32U
#define HOST_XIP_RGN3CFG4_NONCE0_M                                   0xFFFFFFFFU
#define HOST_XIP_RGN3CFG4_NONCE0_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RGN3CFG5
    Offset name:         HOST_XIP_O_RGN3CFG5
    Relative address:    0x4074
    Description:         Region 3 nonce word 1
    Default Value:       0x00000000

        Field:           NONCE1
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Nonce (IV)

*/
#define HOST_XIP_RGN3CFG5_NONCE1_W                                   32U
#define HOST_XIP_RGN3CFG5_NONCE1_M                                   0xFFFFFFFFU
#define HOST_XIP_RGN3CFG5_NONCE1_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTSWCTL0
    Offset name:         HOST_XIP_O_OTSWCTL0
    Relative address:    0x5000
    Description:         Pulse signaled by SW to enable OTFDE and start handling incoming tasks
    Default Value:       0x00000000

        Field:           ENREQ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     OTFDE SW ENABLE REQ WRCL:
                         Pulse signaled by SW to enable OTFDE and start handling incoming tasks

*/
#define HOST_XIP_OTSWCTL0_ENREQ                                      0x00000001U
#define HOST_XIP_OTSWCTL0_ENREQ_M                                    0x00000001U
#define HOST_XIP_OTSWCTL0_ENREQ_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTSWCTL1
    Offset name:         HOST_XIP_O_OTSWCTL1
    Relative address:    0x5004
    Description:         Pulse signaled by SW to disable OTFDE and stop handling incoming task
                        and erase all task related data
    Default Value:       0x00000000

        Field:           DISREQ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     OTFDE SW DISABLE REQ WRCL:
                         Pulse signaled by SW to disable OTFDE and stop handling incoming task
                         and erase all task related data

*/
#define HOST_XIP_OTSWCTL1_DISREQ                                     0x00000001U
#define HOST_XIP_OTSWCTL1_DISREQ_M                                   0x00000001U
#define HOST_XIP_OTSWCTL1_DISREQ_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTSWCTL2
    Offset name:         HOST_XIP_O_OTSWCTL2
    Relative address:    0x5008
    Description:         Pulse signaled by SW to suspend OTFDE task and hold task related data
    Default Value:       0x00000000

        Field:           SUSPENDREQ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     OTFDE SW SUSPEND TASK REQ WRCL:
                         Pulse signaled by SW to suspend OTFDE task and hold task related data

*/
#define HOST_XIP_OTSWCTL2_SUSPENDREQ                                 0x00000001U
#define HOST_XIP_OTSWCTL2_SUSPENDREQ_M                               0x00000001U
#define HOST_XIP_OTSWCTL2_SUSPENDREQ_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTSWCTL3
    Offset name:         HOST_XIP_O_OTSWCTL3
    Relative address:    0x500C
    Description:         Pulse signaled by SW to resume OTFDE suspended task
    Default Value:       0x00000000

        Field:           RESUMEREQ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     OTFDE SW RESUME TASK REQ WRCL:
                         Pulse signaled by SW to resume OTFDE suspended task

*/
#define HOST_XIP_OTSWCTL3_RESUMEREQ                                  0x00000001U
#define HOST_XIP_OTSWCTL3_RESUMEREQ_M                                0x00000001U
#define HOST_XIP_OTSWCTL3_RESUMEREQ_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTSWCTL4
    Offset name:         HOST_XIP_O_OTSWCTL4
    Relative address:    0x5010
    Description:         Pulse signaled by SW to soft reset OTFDE engine and fifo and move to active idle
    Default Value:       0x00000000

        Field:           RSTREQ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     OTFDE SW SOFT RESET REQ WRCL:
                         1- Soft Reset request pulse

*/
#define HOST_XIP_OTSWCTL4_RSTREQ                                     0x00000001U
#define HOST_XIP_OTSWCTL4_RSTREQ_M                                   0x00000001U
#define HOST_XIP_OTSWCTL4_RSTREQ_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTSTA
    Offset name:         HOST_XIP_O_OTSTA
    Relative address:    0x5020
    Description:         OTFDE status
    Default Value:       0x00000100

        Field:           ACTIVESTA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE ACTIVE:
                         0- OTFDE is disabled IF OTFDE_TASK_SUSPENDED is also de-asserted
                         1- OTFDE is active

*/
#define HOST_XIP_OTSTA_ACTIVESTA                                     0x00000001U
#define HOST_XIP_OTSTA_ACTIVESTA_M                                   0x00000001U
#define HOST_XIP_OTSTA_ACTIVESTA_S                                   0U
/*

        Field:           TASKSUS
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE TASK SUSPENDED
                         1- OTFDE is in task suspended mode
                         0- OTFDE is either active or disabled (IF OTFDE_ACTIVE is also de-asserted then OTFDE is disabled)

*/
#define HOST_XIP_OTSTA_TASKSUS                                       0x00000002U
#define HOST_XIP_OTSTA_TASKSUS_M                                     0x00000002U
#define HOST_XIP_OTSTA_TASKSUS_S                                     1U
/*

        Field:           EXTMUX
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE SELECT EXTERNAL MUX:
                         0- External Muxes bypassing OTFDE allowing System/ SW access to xspi
                         1- External Muxes are controlled by OTFDE which is Active and has access to xspi

*/
#define HOST_XIP_OTSTA_EXTMUX                                        0x00000004U
#define HOST_XIP_OTSTA_EXTMUX_M                                      0x00000004U
#define HOST_XIP_OTSTA_EXTMUX_S                                      2U
/*

        Field:           TASKACTIVE
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE ACTIVE TASK VALID:
                         0- No task is being handled,
                         1- A   task is being handled,
                         note: decide if OTFDE is active or suspended using OTFDE_ACTIVE and OTFDE_TASK_SUSPENDED

*/
#define HOST_XIP_OTSTA_TASKACTIVE                                    0x00000008U
#define HOST_XIP_OTSTA_TASKACTIVE_M                                  0x00000008U
#define HOST_XIP_OTSTA_TASKACTIVE_S                                  3U
/*

        Field:           TASKDIR
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE ACTIVE TASK TYPE:
                         0- Active read task
                         1- Active write task
                         value is valid only if OTFDE_ACTIVE or OTFDE_TASK_SUSPENDED are set

*/
#define HOST_XIP_OTSTA_TASKDIR                                       0x00000010U
#define HOST_XIP_OTSTA_TASKDIR_M                                     0x00000010U
#define HOST_XIP_OTSTA_TASKDIR_S                                     4U
/*

        Field:           TASKDEVICE
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE ACTIVE TASK DEVICE:
                         0- Device 0 active task
                         1- Device 1 active task
                         value is valid only if OTFDE_ACTIVE or OTFDE_TASK_SUSPENDED are set

*/
#define HOST_XIP_OTSTA_TASKDEVICE                                    0x00000020U
#define HOST_XIP_OTSTA_TASKDEVICE_M                                  0x00000020U
#define HOST_XIP_OTSTA_TASKDEVICE_S                                  5U
/*

        Field:           TASKREGION
        From..to bits:   6...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE ACTIVE TASK REGION:
                         0- Region 0 active task
                         1- Region 1 active task
                         2- Region 2 active task
                         3- Region 3 active task
                         value is valid only if OTFDE_ACTIVE or OTFDE_TASK_SUSPENDED are set

*/
#define HOST_XIP_OTSTA_TASKREGION_W                                  2U
#define HOST_XIP_OTSTA_TASKREGION_M                                  0x000000C0U
#define HOST_XIP_OTSTA_TASKREGION_S                                  6U
/*

        Field:           OTFDENBUSY
        From..to bits:   8...8
        DefaultValue:    0x1
        Access type:     read-only
        Description:     OTFDE IS NOT BUSY.
                         This bit set when OTFDE NOT in the middle of configuration or transmitting data.
                         OTFDE can be halted only when this bit is set.

*/
#define HOST_XIP_OTSTA_OTFDENBUSY                                    0x00000100U
#define HOST_XIP_OTSTA_OTFDENBUSY_M                                  0x00000100U
#define HOST_XIP_OTSTA_OTFDENBUSY_S                                  8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTINDSTA
    Offset name:         HOST_XIP_O_OTINDSTA
    Relative address:    0x5030
    Description:         Event indication
    Default Value:       0x00000000

        Field:           RSTEV
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE RESET EVENT RDCL:
                         0 - Disable
                         1- Set Indication
                         OTFDE Hard reset or Disable request completion event indication

*/
#define HOST_XIP_OTINDSTA_RSTEV                                      0x00000001U
#define HOST_XIP_OTINDSTA_RSTEV_M                                    0x00000001U
#define HOST_XIP_OTINDSTA_RSTEV_S                                    0U
/*

        Field:           SWRSTEV
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE SOFT RESET EVENT RDCL:
                         0 - Disable
                         1- Set Indication
                         OTFDE Soft reset completion event indication

*/
#define HOST_XIP_OTINDSTA_SWRSTEV                                    0x00000002U
#define HOST_XIP_OTINDSTA_SWRSTEV_M                                  0x00000002U
#define HOST_XIP_OTINDSTA_SWRSTEV_S                                  1U
/*

        Field:           BYPASSEV
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE BYPASS MODE CHANGE EVENT RDCL:
                         0 - Disable
                         1- Set Indication
                         OTFDE entered or exited bypass mode between suspend and resume states

*/
#define HOST_XIP_OTINDSTA_BYPASSEV                                   0x00000004U
#define HOST_XIP_OTINDSTA_BYPASSEV_M                                 0x00000004U
#define HOST_XIP_OTINDSTA_BYPASSEV_S                                 2U
/*

        Field:           GENERALERR
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE GENERAL ERROR RDCL:
                         0 - Disable
                         1- Set Indication
                         General error event indication

*/
#define HOST_XIP_OTINDSTA_GENERALERR                                 0x00000010U
#define HOST_XIP_OTINDSTA_GENERALERR_M                               0x00000010U
#define HOST_XIP_OTINDSTA_GENERALERR_S                               4U
/*

        Field:           DATPATHERR
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE XSPI DATA PATH ERROR_RDCL:
                         0 - Disable
                         1- Set Indication
                         xSPI error on the data path to OTFDE

*/
#define HOST_XIP_OTINDSTA_DATPATHERR                                 0x00000020U
#define HOST_XIP_OTINDSTA_DATPATHERR_M                               0x00000020U
#define HOST_XIP_OTINDSTA_DATPATHERR_S                               5U
/*

        Field:           XSPICFGERR
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE XSPI CNFG PATH ERROR RDCL:
                         0 - Disable
                         1- Set Indication
                         xSPI error on the config path to OTFDE

*/
#define HOST_XIP_OTINDSTA_XSPICFGERR                                 0x00000040U
#define HOST_XIP_OTINDSTA_XSPICFGERR_M                               0x00000040U
#define HOST_XIP_OTINDSTA_XSPICFGERR_S                               6U
/*

        Field:           XSPIINT
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE XSPI SERVICE INTERRUPT INDICATION RDCL:
                         0 - Disable
                         1- Set Indication
                         indication that service interruption criteria was triggered

*/
#define HOST_XIP_OTINDSTA_XSPIINT                                    0x00000080U
#define HOST_XIP_OTINDSTA_XSPIINT_M                                  0x00000080U
#define HOST_XIP_OTINDSTA_XSPIINT_S                                  7U
/*

        Field:           DEVDISERR
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE TRANS DEVICE DISABLED ERROR RDCL:
                         0 - Disable
                         1- Set Indication
                         indication that the current transaction is into a disabled device

*/
#define HOST_XIP_OTINDSTA_DEVDISERR                                  0x00000100U
#define HOST_XIP_OTINDSTA_DEVDISERR_M                                0x00000100U
#define HOST_XIP_OTINDSTA_DEVDISERR_S                                8U
/*

        Field:           REGDISERR
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE TRANS REGION DISABLED ERROR RDCL:
                         0 - Disable
                         1- Set Indication
                         indication that the current transaction is into a disabled region

*/
#define HOST_XIP_OTINDSTA_REGDISERR                                  0x00000200U
#define HOST_XIP_OTINDSTA_REGDISERR_M                                0x00000200U
#define HOST_XIP_OTINDSTA_REGDISERR_S                                9U
/*

        Field:           POLLITREXP
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE TRANS XSPI POLLING ITR EXPIRED RDCL:
                         0 - Disable
                         1- Set Indication
                         Polling Request iterations expired

*/
#define HOST_XIP_OTINDSTA_POLLITREXP                                 0x00000400U
#define HOST_XIP_OTINDSTA_POLLITREXP_M                               0x00000400U
#define HOST_XIP_OTINDSTA_POLLITREXP_S                               10U
/*

        Field:           REGMAPERR
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE TRANS MULTIPLE REGIONS MAPPED ERROR RDCL:
                         0 - Disable
                         1- Set Indication
                         Indication that a transaction was mapped into more than one region

*/
#define HOST_XIP_OTINDSTA_REGMAPERR                                  0x00000800U
#define HOST_XIP_OTINDSTA_REGMAPERR_M                                0x00000800U
#define HOST_XIP_OTINDSTA_REGMAPERR_S                                11U
/*

        Field:           ADDRNOALGN
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE TRANS ADDRESS NOT 32 BIT VIOLATION RDCL:
                         0 - Disable
                         1- Set Indication
                         Indication that a transaction address was not 32 bit aligned

*/
#define HOST_XIP_OTINDSTA_ADDRNOALGN                                 0x00001000U
#define HOST_XIP_OTINDSTA_ADDRNOALGN_M                               0x00001000U
#define HOST_XIP_OTINDSTA_ADDRNOALGN_S                               12U
/*

        Field:           SIZENOALGN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE TRANS SIZE NOT 32 BIT VIOLATION RDCL:
                         0 - Disable
                         1- Set Indication
                         Indication that a transaction size was not 32 bit

*/
#define HOST_XIP_OTINDSTA_SIZENOALGN                                 0x00002000U
#define HOST_XIP_OTINDSTA_SIZENOALGN_M                               0x00002000U
#define HOST_XIP_OTINDSTA_SIZENOALGN_S                               13U
/*

        Field:           BURNOALGN
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE TRANS BURST NOT 32 BIT VIOLATION RDCL:
                         0 - Disable
                         1- Set Indication
                         Indication that a transaction burst was not non-seq

*/
#define HOST_XIP_OTINDSTA_BURNOALGN                                  0x00004000U
#define HOST_XIP_OTINDSTA_BURNOALGN_M                                0x00004000U
#define HOST_XIP_OTINDSTA_BURNOALGN_S                                14U
/*

        Field:           REGDIRERR
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE REGION READ WRITE DEF VIOLATION RDCL:
                         0 - Disable
                         1- Set Indication
                         Indication that a transaction type was not allowed according to region definitions

*/
#define HOST_XIP_OTINDSTA_REGDIRERR                                  0x00008000U
#define HOST_XIP_OTINDSTA_REGDIRERR_M                                0x00008000U
#define HOST_XIP_OTINDSTA_REGDIRERR_S                                15U
/*

        Field:           SUSPENDDIS
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OTFDE SW SUSPEND REQ WHILE DISABLED RDCL:
                         0 - Disable
                         1- Set Indication
                         indication that SW requested suspend while OTFDE is disabled

*/
#define HOST_XIP_OTINDSTA_SUSPENDDIS                                 0x00010000U
#define HOST_XIP_OTINDSTA_SUSPENDDIS_M                               0x00010000U
#define HOST_XIP_OTINDSTA_SUSPENDDIS_S                               16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTINDMASK
    Offset name:         HOST_XIP_O_OTINDMASK
    Relative address:    0x5040
    Description:         Event Masked
    Default Value:       0x0001FFFF

        Field:           RSTEV
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE RESET MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask hard reset completion event

*/
#define HOST_XIP_OTINDMASK_RSTEV                                     0x00000001U
#define HOST_XIP_OTINDMASK_RSTEV_M                                   0x00000001U
#define HOST_XIP_OTINDMASK_RSTEV_S                                   0U
/*

        Field:           SWRSTEV
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE SOFT RESET MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask soft reset completion event

*/
#define HOST_XIP_OTINDMASK_SWRSTEV                                   0x00000002U
#define HOST_XIP_OTINDMASK_SWRSTEV_M                                 0x00000002U
#define HOST_XIP_OTINDMASK_SWRSTEV_S                                 1U
/*

        Field:           BYPASSEV
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE BYPASS MODE CHANGE MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask bypass mode change between suspend and resume completion event

*/
#define HOST_XIP_OTINDMASK_BYPASSEV                                  0x00000004U
#define HOST_XIP_OTINDMASK_BYPASSEV_M                                0x00000004U
#define HOST_XIP_OTINDMASK_BYPASSEV_S                                2U
/*

        Field:           GENERALERR
        From..to bits:   4...4
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE GENERAL MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask general error event

*/
#define HOST_XIP_OTINDMASK_GENERALERR                                0x00000010U
#define HOST_XIP_OTINDMASK_GENERALERR_M                              0x00000010U
#define HOST_XIP_OTINDMASK_GENERALERR_S                              4U
/*

        Field:           DATPATHERR
        From..to bits:   5...5
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE XSPI DATA PATH MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask xSPI data path related errors signaled to OTFDE

*/
#define HOST_XIP_OTINDMASK_DATPATHERR                                0x00000020U
#define HOST_XIP_OTINDMASK_DATPATHERR_M                              0x00000020U
#define HOST_XIP_OTINDMASK_DATPATHERR_S                              5U
/*

        Field:           XSPICFGERR
        From..to bits:   6...6
        DefaultValue:    0x1
        Access type:     read-write
        Description:     0- Masked
                         1- Enabled
                         Enable / Mask xSPI config path related errors signaled to OTFDE

*/
#define HOST_XIP_OTINDMASK_XSPICFGERR                                0x00000040U
#define HOST_XIP_OTINDMASK_XSPICFGERR_M                              0x00000040U
#define HOST_XIP_OTINDMASK_XSPICFGERR_S                              6U
/*

        Field:           XSPIINT
        From..to bits:   7...7
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE XSPI SERVICE INTERRUPT MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask xSPI service interrupt criteria event indication

*/
#define HOST_XIP_OTINDMASK_XSPIINT                                   0x00000080U
#define HOST_XIP_OTINDMASK_XSPIINT_M                                 0x00000080U
#define HOST_XIP_OTINDMASK_XSPIINT_S                                 7U
/*

        Field:           DEVDISERR
        From..to bits:   8...8
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE TRANS DEVICE DISABLED MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask transaction into a disabled device event indication

*/
#define HOST_XIP_OTINDMASK_DEVDISERR                                 0x00000100U
#define HOST_XIP_OTINDMASK_DEVDISERR_M                               0x00000100U
#define HOST_XIP_OTINDMASK_DEVDISERR_S                               8U
/*

        Field:           REGDISERR
        From..to bits:   9...9
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE TRANS REGION DISABLED MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask transaction into a disabled region event indication

*/
#define HOST_XIP_OTINDMASK_REGDISERR                                 0x00000200U
#define HOST_XIP_OTINDMASK_REGDISERR_M                               0x00000200U
#define HOST_XIP_OTINDMASK_REGDISERR_S                               9U
/*

        Field:           POLLITREXP
        From..to bits:   10...10
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE XSPI POLLING ITR EXPIRED MASK:
                         0- Masked
                         1- Enabled
                         Polling requests iterations expired

*/
#define HOST_XIP_OTINDMASK_POLLITREXP                                0x00000400U
#define HOST_XIP_OTINDMASK_POLLITREXP_M                              0x00000400U
#define HOST_XIP_OTINDMASK_POLLITREXP_S                              10U
/*

        Field:           REGMAPERR
        From..to bits:   11...11
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE TRANS MULTIPLE REGIONS MAPPED MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask transaction was mapped into more than one region indication

*/
#define HOST_XIP_OTINDMASK_REGMAPERR                                 0x00000800U
#define HOST_XIP_OTINDMASK_REGMAPERR_M                               0x00000800U
#define HOST_XIP_OTINDMASK_REGMAPERR_S                               11U
/*

        Field:           ADDRNOALGN
        From..to bits:   12...12
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE TRANS ADDRESS NOT 32 BIT MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask transaction address was not 32 bit aligned indication

*/
#define HOST_XIP_OTINDMASK_ADDRNOALGN                                0x00001000U
#define HOST_XIP_OTINDMASK_ADDRNOALGN_M                              0x00001000U
#define HOST_XIP_OTINDMASK_ADDRNOALGN_S                              12U
/*

        Field:           SIZENOALGN
        From..to bits:   13...13
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE TRANS SIZE NOT 32 BIT MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask transaction size was not 32 bit indication

*/
#define HOST_XIP_OTINDMASK_SIZENOALGN                                0x00002000U
#define HOST_XIP_OTINDMASK_SIZENOALGN_M                              0x00002000U
#define HOST_XIP_OTINDMASK_SIZENOALGN_S                              13U
/*

        Field:           BURNOALGN
        From..to bits:   14...14
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE TRANS BURST NOT 32 BIT MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask transaction burst was not non-seq indication

*/
#define HOST_XIP_OTINDMASK_BURNOALGN                                 0x00004000U
#define HOST_XIP_OTINDMASK_BURNOALGN_M                               0x00004000U
#define HOST_XIP_OTINDMASK_BURNOALGN_S                               14U
/*

        Field:           REGDIRERR
        From..to bits:   15...15
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE REGION READ WRITE DEF MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask transaction type was not allowed according to region definitions

*/
#define HOST_XIP_OTINDMASK_REGDIRERR                                 0x00008000U
#define HOST_XIP_OTINDMASK_REGDIRERR_M                               0x00008000U
#define HOST_XIP_OTINDMASK_REGDIRERR_S                               15U
/*

        Field:           SUSPENDDIS
        From..to bits:   16...16
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE SUSPEND WHILE DISABLED MASK:
                         0- Masked
                         1- Enabled
                         Enable / Mask SW requested suspend while OTFDE is disabled indication

*/
#define HOST_XIP_OTINDMASK_SUSPENDDIS                                0x00010000U
#define HOST_XIP_OTINDMASK_SUSPENDDIS_M                              0x00010000U
#define HOST_XIP_OTINDMASK_SUSPENDDIS_S                              16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTINDNEXT
    Offset name:         HOST_XIP_O_OTINDNEXT
    Relative address:    0x5050
    Description:         Event IRQ next state
    Default Value:       0x0000F3FA

        Field:           RSTNS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RESET NON SECURED

*/
#define HOST_XIP_OTINDNEXT_RSTNS                                     0x00000001U
#define HOST_XIP_OTINDNEXT_RSTNS_M                                   0x00000001U
#define HOST_XIP_OTINDNEXT_RSTNS_S                                   0U
/*

        Field:           SWRSTEV
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE SOFT RESET NS:
                         0- Disable
                         1- Active Idle
                         Decision of next state for  soft reset completion event

*/
#define HOST_XIP_OTINDNEXT_SWRSTEV                                   0x00000002U
#define HOST_XIP_OTINDNEXT_SWRSTEV_M                                 0x00000002U
#define HOST_XIP_OTINDNEXT_SWRSTEV_S                                 1U
/*

        Field:           BYPMDCH
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     BYPASS MODE CHANGE

                         Used in ECO for PG1.
                         Problem Statement
                         In DDR 80MHz mode RD cmd, Seen in QPI (Octal not yet checked) the xSPI IP stop driving the data to soon violating Ext Mem hold requirement (~0.5ns v. up to ~2-3ns requirement for most vendors)
                         Suggested Fix
                         extend IO data drive by additional logic at IP for read commands in the DDR 80MHz mode

*/
#define HOST_XIP_OTINDNEXT_BYPMDCH                                   0x00000004U
#define HOST_XIP_OTINDNEXT_BYPMDCH_M                                 0x00000004U
#define HOST_XIP_OTINDNEXT_BYPMDCH_S                                 2U
/*

        Field:           GENERALERR
        From..to bits:   4...4
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE GENERAL ERROR NS:
                         0- Disable
                         1- Active Idle
                         Decision of next state for  general error event

*/
#define HOST_XIP_OTINDNEXT_GENERALERR                                0x00000010U
#define HOST_XIP_OTINDNEXT_GENERALERR_M                              0x00000010U
#define HOST_XIP_OTINDNEXT_GENERALERR_S                              4U
/*

        Field:           DATPATHERR
        From..to bits:   5...5
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE XSPI DATA PATH ERROR NS:
                         0- Disable
                         1- Active Idle
                         Decision of next state for xSPI data path related errors signaled to OTFDE

*/
#define HOST_XIP_OTINDNEXT_DATPATHERR                                0x00000020U
#define HOST_XIP_OTINDNEXT_DATPATHERR_M                              0x00000020U
#define HOST_XIP_OTINDNEXT_DATPATHERR_S                              5U
/*

        Field:           XSPICFGERR
        From..to bits:   6...6
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE XSPI CNFG PATH ERROR NS:
                         0- Disable
                         1- Active Idle
                         Decision of next state for xSPI config path related errors signaled to OTFDE

*/
#define HOST_XIP_OTINDNEXT_XSPICFGERR                                0x00000040U
#define HOST_XIP_OTINDNEXT_XSPICFGERR_M                              0x00000040U
#define HOST_XIP_OTINDNEXT_XSPICFGERR_S                              6U
/*

        Field:           XSPISERINT
        From..to bits:   7...7
        DefaultValue:    0x1
        Access type:     read-write
        Description:     XSPI SERVICE INTERRUPT

*/
#define HOST_XIP_OTINDNEXT_XSPISERINT                                0x00000080U
#define HOST_XIP_OTINDNEXT_XSPISERINT_M                              0x00000080U
#define HOST_XIP_OTINDNEXT_XSPISERINT_S                              7U
/*

        Field:           DEVDISERR
        From..to bits:   8...8
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE TRANS DEVICE DISABLED NS:
                         0- Disable
                         1- Active Idle
                         Decision of next state for transaction into a disabled device event indication

*/
#define HOST_XIP_OTINDNEXT_DEVDISERR                                 0x00000100U
#define HOST_XIP_OTINDNEXT_DEVDISERR_M                               0x00000100U
#define HOST_XIP_OTINDNEXT_DEVDISERR_S                               8U
/*

        Field:           REGDISERR
        From..to bits:   9...9
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE TRANS REGION DISABLED NS:
                         0- Disable
                         1- Active Idle
                         Decision of next state for transaction into a disabled region event indication

*/
#define HOST_XIP_OTINDNEXT_REGDISERR                                 0x00000200U
#define HOST_XIP_OTINDNEXT_REGDISERR_M                               0x00000200U
#define HOST_XIP_OTINDNEXT_REGDISERR_S                               9U
/*

        Field:           REGMAPERR
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE TRANS MULTIPLE REGIONS MAPPED NS:
                         0- Disable
                         1- N/A
                         Decision of next state for transaction was mapped into more than one region

*/
#define HOST_XIP_OTINDNEXT_REGMAPERR                                 0x00000800U
#define HOST_XIP_OTINDNEXT_REGMAPERR_M                               0x00000800U
#define HOST_XIP_OTINDNEXT_REGMAPERR_S                               11U
/*

        Field:           ADDRNOALGN
        From..to bits:   12...12
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE TRANS ADDRESS NOT 32 BIT NS:
                         0- Disable
                         1- Active Idle
                         Decision of next state for transaction address was not 32 bit aligned indication

*/
#define HOST_XIP_OTINDNEXT_ADDRNOALGN                                0x00001000U
#define HOST_XIP_OTINDNEXT_ADDRNOALGN_M                              0x00001000U
#define HOST_XIP_OTINDNEXT_ADDRNOALGN_S                              12U
/*

        Field:           SIZENOALGN
        From..to bits:   13...13
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE TRANS SIZE NOT 32 BIT NS:
                         0- Disable
                         1- Active Idle
                         Decision of next state for transaction size was not 32 bit indication

*/
#define HOST_XIP_OTINDNEXT_SIZENOALGN                                0x00002000U
#define HOST_XIP_OTINDNEXT_SIZENOALGN_M                              0x00002000U
#define HOST_XIP_OTINDNEXT_SIZENOALGN_S                              13U
/*

        Field:           BURNOALGN
        From..to bits:   14...14
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE TRANS BURST NOT 32 BIT NS:
                         0- Disable
                         1- Active Idle
                         Decision of next state for transaction burst was not non-seq indication

*/
#define HOST_XIP_OTINDNEXT_BURNOALGN                                 0x00004000U
#define HOST_XIP_OTINDNEXT_BURNOALGN_M                               0x00004000U
#define HOST_XIP_OTINDNEXT_BURNOALGN_S                               14U
/*

        Field:           REGDIRERR
        From..to bits:   15...15
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE REGION READ WRITE VIOLATION NS:
                         0- Disable
                         1- Active Idle
                         Decision of next state for transaction type was not allowed according to region definitions

*/
#define HOST_XIP_OTINDNEXT_REGDIRERR                                 0x00008000U
#define HOST_XIP_OTINDNEXT_REGDIRERR_M                               0x00008000U
#define HOST_XIP_OTINDNEXT_REGDIRERR_S                               15U
/*

        Field:           SUSPENDDIS
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE SUSPEND WHILE DISABLED NS:
                         0- Disable
                         1- N/A
                         Decision of next state for SW requested suspend while OTFDE is disabled

*/
#define HOST_XIP_OTINDNEXT_SUSPENDDIS                                0x00010000U
#define HOST_XIP_OTINDNEXT_SUSPENDDIS_M                              0x00010000U
#define HOST_XIP_OTINDNEXT_SUSPENDDIS_S                              16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTSTGSEL
    Offset name:         HOST_XIP_O_OTSTGSEL
    Relative address:    0x5060
    Description:         set of controller non STIG configurations
    Default Value:       0x00000000

        Field:           DEV0JOB0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used when the access address does not match any region
                         0- Reject not mapped address access
                         1- Bypass not mapped address access (address is forwarded as is to xspi)

*/
#define HOST_XIP_OTSTGSEL_DEV0JOB0                                   0x00000001U
#define HOST_XIP_OTSTGSEL_DEV0JOB0_M                                 0x00000001U
#define HOST_XIP_OTSTGSEL_DEV0JOB0_S                                 0U
/*

        Field:           DEV0JOB4
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used when the access address does not match any region
                         0- Reject not mapped address access
                         1- Bypass not mapped address access (address is forwarded as is to xspi)

*/
#define HOST_XIP_OTSTGSEL_DEV0JOB4                                   0x00000010U
#define HOST_XIP_OTSTGSEL_DEV0JOB4_M                                 0x00000010U
#define HOST_XIP_OTSTGSEL_DEV0JOB4_S                                 4U
/*

        Field:           DEV0JOB5
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used when the access address does not match any region
                         0- Reject not mapped address access
                         1- Bypass not mapped address access (address is forwarded as is to xspi)

*/
#define HOST_XIP_OTSTGSEL_DEV0JOB5                                   0x00000020U
#define HOST_XIP_OTSTGSEL_DEV0JOB5_M                                 0x00000020U
#define HOST_XIP_OTSTGSEL_DEV0JOB5_S                                 5U
/*

        Field:           DEV0JOB6
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used when the access address does not match any region
                         0- Reject not mapped address access
                         1- Bypass not mapped address access (address is forwarded as is to xspi)

*/
#define HOST_XIP_OTSTGSEL_DEV0JOB6                                   0x00000040U
#define HOST_XIP_OTSTGSEL_DEV0JOB6_M                                 0x00000040U
#define HOST_XIP_OTSTGSEL_DEV0JOB6_S                                 6U
/*

        Field:           DEV0JOB7
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used when the access address does not match any region
                         0- Reject not mapped address access
                         1- Bypass not mapped address access (address is forwarded as is to xspi)

*/
#define HOST_XIP_OTSTGSEL_DEV0JOB7                                   0x00000080U
#define HOST_XIP_OTSTGSEL_DEV0JOB7_M                                 0x00000080U
#define HOST_XIP_OTSTGSEL_DEV0JOB7_S                                 7U
/*

        Field:           DEV1JOB0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used when the access address does not match any region
                         0- Reject not mapped address access
                         1- Bypass not mapped address access (address is forwarded as is to xspi)

*/
#define HOST_XIP_OTSTGSEL_DEV1JOB0                                   0x00000100U
#define HOST_XIP_OTSTGSEL_DEV1JOB0_M                                 0x00000100U
#define HOST_XIP_OTSTGSEL_DEV1JOB0_S                                 8U
/*

        Field:           DEV1JOB4
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used when the access address does not match any region
                         0- Reject not mapped address access
                         1- Bypass not mapped address access (address is forwarded as is to xspi)

*/
#define HOST_XIP_OTSTGSEL_DEV1JOB4                                   0x00001000U
#define HOST_XIP_OTSTGSEL_DEV1JOB4_M                                 0x00001000U
#define HOST_XIP_OTSTGSEL_DEV1JOB4_S                                 12U
/*

        Field:           DEV1JOB5
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used when the access address does not match any region
                         0- Reject not mapped address access
                         1- Bypass not mapped address access (address is forwarded as is to xspi)

*/
#define HOST_XIP_OTSTGSEL_DEV1JOB5                                   0x00002000U
#define HOST_XIP_OTSTGSEL_DEV1JOB5_M                                 0x00002000U
#define HOST_XIP_OTSTGSEL_DEV1JOB5_S                                 13U
/*

        Field:           DEV1JOB6
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used when the access address does not match any region
                         0- Reject not mapped address access
                         1- Bypass not mapped address access (address is forwarded as is to xspi)

*/
#define HOST_XIP_OTSTGSEL_DEV1JOB6                                   0x00004000U
#define HOST_XIP_OTSTGSEL_DEV1JOB6_M                                 0x00004000U
#define HOST_XIP_OTSTGSEL_DEV1JOB6_S                                 14U
/*

        Field:           DEV1JOB7
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used when the access address does not match any region
                         0- Reject not mapped address access
                         1- Bypass not mapped address access (address is forwarded as is to xspi)

*/
#define HOST_XIP_OTSTGSEL_DEV1JOB7                                   0x00008000U
#define HOST_XIP_OTSTGSEL_DEV1JOB7_M                                 0x00008000U
#define HOST_XIP_OTSTGSEL_DEV1JOB7_S                                 15U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTD0CFG
    Offset name:         HOST_XIP_O_OTD0CFG
    Relative address:    0x5070
    Description:         Device 0 parameters
    Default Value:       0x00500001

        Field:           DEVICE
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     OTFDE DEVICE 0 ENABLED:
                         Device enabled (and all the device parameters were checked in SW)
                         0- Device Disabled
                         1- Device Enabled

*/
#define HOST_XIP_OTD0CFG_DEVICE                                      0x00000001U
#define HOST_XIP_OTD0CFG_DEVICE_M                                    0x00000001U
#define HOST_XIP_OTD0CFG_DEVICE_S                                    0U
/*

        Field:           WRPROTTIME
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 0 WRITE PROTECTION TIMER EN:
                         Set the write protection timer after a write task
                         0- Write protection timer is disabled
                         1- Write protection timer is enabled

*/
#define HOST_XIP_OTD0CFG_WRPROTTIME                                  0x00000002U
#define HOST_XIP_OTD0CFG_WRPROTTIME_M                                0x00000002U
#define HOST_XIP_OTD0CFG_WRPROTTIME_S                                1U
/*

        Field:           PREWRCMD
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 0 ISSUE PRE WRITE CMD:
                         Issue a Pre Write command before the next write task
                         0- Do not issue PRE WR CMD
                         1- Issue PRE WR CMD before every write task

*/
#define HOST_XIP_OTD0CFG_PREWRCMD                                    0x00000004U
#define HOST_XIP_OTD0CFG_PREWRCMD_M                                  0x00000004U
#define HOST_XIP_OTD0CFG_PREWRCMD_S                                  2U
/*

        Field:           POSTWRCMD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 0 ISSUE POST WRITE CMD:
                         Issue a Post Write command after the write task ended
                         0- Do not issue POST WR CMD
                         1- Issue POST WR CMD after every write task

*/
#define HOST_XIP_OTD0CFG_POSTWRCMD                                   0x00000008U
#define HOST_XIP_OTD0CFG_POSTWRCMD_M                                 0x00000008U
#define HOST_XIP_OTD0CFG_POSTWRCMD_S                                 3U
/*

        Field:           WRBUFTMMOD
        From..to bits:   4...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 0 WRITE BUFFER TIMER MODE:
                         00- mode0 is   16usec resolution
                         01- mode1 is   32usec resolution
                         10- mode2 is   64usec resolution
                         11- mode3 is 256usec resolution

*/
#define HOST_XIP_OTD0CFG_WRBUFTMMOD_W                                2U
#define HOST_XIP_OTD0CFG_WRBUFTMMOD_M                                0x00000030U
#define HOST_XIP_OTD0CFG_WRBUFTMMOD_S                                4U
/*

        Field:           WRBUFTMRNG
        From..to bits:   8...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 0 WRITE BUFFER TIMER RANGE:
                         range is 0 - 63 multiplied by Mode resolution
                         mode0: timer res is   16usec, timer range is   16-1024usec
                         mode1: timer res is   32usec, timer range is   32-2048usec
                         mode2: timer res is   64usec, timer range is   64-4192usec
                         mode3: timer res is 256usec, timer range is 256-16384usec

*/
#define HOST_XIP_OTD0CFG_WRBUFTMRNG_W                                6U
#define HOST_XIP_OTD0CFG_WRBUFTMRNG_M                                0x00003F00U
#define HOST_XIP_OTD0CFG_WRBUFTMRNG_S                                8U
/*

        Field:           RWW
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 0 RWW EN:
                         0- Read while Write is disabled
                         1- Read while Write is Enabled

*/
#define HOST_XIP_OTD0CFG_RWW                                         0x00010000U
#define HOST_XIP_OTD0CFG_RWW_M                                       0x00010000U
#define HOST_XIP_OTD0CFG_RWW_S                                       16U
/*

        Field:           DEVICESIZE
        From..to bits:   20...22
        DefaultValue:    0x5
        Access type:     read-write
        Description:     OTFDE DEVICE 0 SIZE:
                         000 -   2 MByte
                         001 -   4 MByte
                         010 -   8 MByte
                         011 - 16 MByte
                         100 - 32 MByte
                         101 - 64 MByte

*/
#define HOST_XIP_OTD0CFG_DEVICESIZE_W                                3U
#define HOST_XIP_OTD0CFG_DEVICESIZE_M                                0x00700000U
#define HOST_XIP_OTD0CFG_DEVICESIZE_S                                20U
/*

        Field:           NUMBANKS
        From..to bits:   24...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 0 NUMBER OF BANKS:
                         000 -   1 Bank
                         001 -   2 Banks
                         010 -   4 Banks
                         011 -   8 Banks
                         100 - 16 Banks

*/
#define HOST_XIP_OTD0CFG_NUMBANKS_W                                  3U
#define HOST_XIP_OTD0CFG_NUMBANKS_M                                  0x07000000U
#define HOST_XIP_OTD0CFG_NUMBANKS_S                                  24U
/*

        Field:           INTCRT
        From..to bits:   28...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 0 SERVICE INTERRUPT CRITERIA:
                         0- No service interruption criteria.
                         any other value is in 160MHz cycles between two transactions towards xSPI

*/
#define HOST_XIP_OTD0CFG_INTCRT_W                                    4U
#define HOST_XIP_OTD0CFG_INTCRT_M                                    0xF0000000U
#define HOST_XIP_OTD0CFG_INTCRT_S                                    28U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTD0PTMR
    Offset name:         HOST_XIP_O_OTD0PTMR
    Relative address:    0x5074
    Description:         Device 0 polling timer parameters
    Default Value:       0x000103FF

        Field:           RESPCNT
        From..to bits:   0...9
        DefaultValue:    0x3FF
        Access type:     read-write
        Description:     This value holds the amount of time in us between each polling iteration sent to xspi control
                         range : 1us-1023us
                         value zero is NA

*/
#define HOST_XIP_OTD0PTMR_RESPCNT_W                                  10U
#define HOST_XIP_OTD0PTMR_RESPCNT_M                                  0x000003FFU
#define HOST_XIP_OTD0PTMR_RESPCNT_S                                  0U
/*

        Field:           POLLITERA
        From..to bits:   16...20
        DefaultValue:    0x1
        Access type:     read-write
        Description:     This value holds the number of additional iterations before polling process is considered complete
                         range : 0-31 iterations
                         Translating into total polling request iterations: min 1 and max 32

*/
#define HOST_XIP_OTD0PTMR_POLLITERA_W                                5U
#define HOST_XIP_OTD0PTMR_POLLITERA_M                                0x001F0000U
#define HOST_XIP_OTD0PTMR_POLLITERA_S                                16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTD0WRAP
    Offset name:         HOST_XIP_O_OTD0WRAP
    Relative address:    0x5078
    Description:         Device 0 wrap configuration
    Default Value:       0x000103FF

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Enable wrap feature for device 0

*/
#define HOST_XIP_OTD0WRAP_EN                                         0x00000001U
#define HOST_XIP_OTD0WRAP_EN_M                                       0x00000001U
#define HOST_XIP_OTD0WRAP_EN_S                                       0U
/*

        Field:           SIZE
        From..to bits:   1...4
        DefaultValue:    0xF
        Access type:     read-write
        Description:     Define the wrap size, this field is active only if [EN] is set.
                         0x0. 8 Bytes
                         0x1. 16 Bytes
                         0x2. 32 Bytes
                         0x3. 64 Bytes
                         0x4. 128 Bytes
                         0x5. 256 Bytes
                         0x6. 512 Bytes
                         0x7. 1024 Bytes
                         0x8. 2048 Bytes
                         0x9. 4096 Bytes


*/
#define HOST_XIP_OTD0WRAP_SIZE_W                                     4U
#define HOST_XIP_OTD0WRAP_SIZE_M                                     0x0000001EU
#define HOST_XIP_OTD0WRAP_SIZE_S                                     1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTD1CFG
    Offset name:         HOST_XIP_O_OTD1CFG
    Relative address:    0x5080
    Description:         Device 1 parameters
    Default Value:       0x00000000

        Field:           DEVICE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 1 ENABLED:
                         Device enabled (and all the device parameters were checked in SW)
                         0 - Device Disabled
                         1- Device Enabled

*/
#define HOST_XIP_OTD1CFG_DEVICE                                      0x00000001U
#define HOST_XIP_OTD1CFG_DEVICE_M                                    0x00000001U
#define HOST_XIP_OTD1CFG_DEVICE_S                                    0U
/*

        Field:           WRPROTTIME
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 1 WRITE PROTECTION TIMER EN:
                         Set the write protection timer after a write task
                         0- Write protection timer is disabled
                         1- Write protection timer is enabled

*/
#define HOST_XIP_OTD1CFG_WRPROTTIME                                  0x00000002U
#define HOST_XIP_OTD1CFG_WRPROTTIME_M                                0x00000002U
#define HOST_XIP_OTD1CFG_WRPROTTIME_S                                1U
/*

        Field:           PREWRCMD
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 1 ISSUE PRE WRITE CMD:
                         Issue a Pre Write command before the next write task
                         0- Do not issue PRE WR CMD
                         1- Issue PRE WR CMD before every write task

*/
#define HOST_XIP_OTD1CFG_PREWRCMD                                    0x00000004U
#define HOST_XIP_OTD1CFG_PREWRCMD_M                                  0x00000004U
#define HOST_XIP_OTD1CFG_PREWRCMD_S                                  2U
/*

        Field:           POSTWRCMD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 1 ISSUE POST WRITE CMD:
                         Issue a Post Write command after the write task ended
                         0- Do not issue POST WR CMD
                         1- Issue POST WR CMD after every write task

*/
#define HOST_XIP_OTD1CFG_POSTWRCMD                                   0x00000008U
#define HOST_XIP_OTD1CFG_POSTWRCMD_M                                 0x00000008U
#define HOST_XIP_OTD1CFG_POSTWRCMD_S                                 3U
/*

        Field:           WRBUFTMMOD
        From..to bits:   4...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 1 WRITE BUFFER TIMER MODE:
                         00- mode0 is   16usec resolution
                         01- mode1 is   32usec resolution
                         10- mode2 is   64usec resolution
                         11- mode3 is 256usec resolution

*/
#define HOST_XIP_OTD1CFG_WRBUFTMMOD_W                                2U
#define HOST_XIP_OTD1CFG_WRBUFTMMOD_M                                0x00000030U
#define HOST_XIP_OTD1CFG_WRBUFTMMOD_S                                4U
/*

        Field:           WRBUFTMRNG
        From..to bits:   8...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 1 WRITE BUFFER TIMER RANGE:
                         range is 0 - 63 multiplied by Mode resolution
                         mode0: timer res is   16usec, timer range is   16-1024usec
                         mode1: timer res is   32usec, timer range is   32-2048usec
                         mode2: timer res is   64usec, timer range is   64-4192usec
                         mode3: timer res is 256usec, timer range is 256-16384usec

*/
#define HOST_XIP_OTD1CFG_WRBUFTMRNG_W                                6U
#define HOST_XIP_OTD1CFG_WRBUFTMRNG_M                                0x00003F00U
#define HOST_XIP_OTD1CFG_WRBUFTMRNG_S                                8U
/*

        Field:           INTCRT
        From..to bits:   16...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTFDE DEVICE 1 SERVICE INTERRUPT CRITERIA:
                         0- No service interruption criteria.
                         any other value is in 160MHz cycles between two transactions towards xSPI

*/
#define HOST_XIP_OTD1CFG_INTCRT_W                                    4U
#define HOST_XIP_OTD1CFG_INTCRT_M                                    0x000F0000U
#define HOST_XIP_OTD1CFG_INTCRT_S                                    16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTD1WRAP
    Offset name:         HOST_XIP_O_OTD1WRAP
    Relative address:    0x5084
    Description:         Device 1 wrap configuration
    Default Value:       0x000103FF

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Enable wrap feature for device 1

*/
#define HOST_XIP_OTD1WRAP_EN                                         0x00000001U
#define HOST_XIP_OTD1WRAP_EN_M                                       0x00000001U
#define HOST_XIP_OTD1WRAP_EN_S                                       0U
/*

        Field:           SIZE
        From..to bits:   1...4
        DefaultValue:    0xF
        Access type:     read-write
        Description:     Define the wrap size, this field is active only if [EN] is set.
                         0x0. 8 Bytes
                         0x1. 16 Bytes
                         0x2. 32 Bytes
                         0x3. 64 Bytes
                         0x4. 128 Bytes
                         0x5. 256 Bytes
                         0x6. 512 Bytes
                         0x7. 1024 Bytes
                         0x8. 2048 Bytes
                         0x9. 4096 Bytes


*/
#define HOST_XIP_OTD1WRAP_SIZE_W                                     4U
#define HOST_XIP_OTD1WRAP_SIZE_M                                     0x0000001EU
#define HOST_XIP_OTD1WRAP_SIZE_S                                     1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTGLBTMR
    Offset name:         HOST_XIP_O_OTGLBTMR
    Relative address:    0x5090
    Description:         Global watchdog timer
                        counting before raising IRQ
    Default Value:       0x00000005

        Field:           VAL
        From..to bits:   0...2
        DefaultValue:    0x5
        Access type:     read-write
        Description:     Watchdog timer in ms
                         Timer pops watchdog IRQ in case a process within OTFDE crosses the required time
                         range 0-7
                         translated to up to 7ms
                         value 0 is NA

*/
#define HOST_XIP_OTGLBTMR_VAL_W                                      3U
#define HOST_XIP_OTGLBTMR_VAL_M                                      0x00000007U
#define HOST_XIP_OTGLBTMR_VAL_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR0CFG0
    Offset name:         HOST_XIP_O_OTR0CFG0
    Relative address:    0x6000
    Description:         region 0 parameters config 0
    Default Value:       0x0000000D

        Field:           REGION
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     REGION 0 ENABLED:
                         0- Disabled
                         1- Enabled
                         Region enabled for incoming transactions

*/
#define HOST_XIP_OTR0CFG0_REGION                                     0x00000001U
#define HOST_XIP_OTR0CFG0_REGION_M                                   0x00000001U
#define HOST_XIP_OTR0CFG0_REGION_S                                   0U
/*

        Field:           DEVICE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 0 DEVICE ID:
                         0- Device_0
                         1- Device_1

*/
#define HOST_XIP_OTR0CFG0_DEVICE                                     0x00000002U
#define HOST_XIP_OTR0CFG0_DEVICE_M                                   0x00000002U
#define HOST_XIP_OTR0CFG0_DEVICE_S                                   1U
/*

        Field:           SPIWR
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     REGION 0 SPI WRITE ENABLE:
                         0- Cannot issue a SPI Write to this  region
                         1- Can issue a SPI Write to this  region

*/
#define HOST_XIP_OTR0CFG0_SPIWR                                      0x00000004U
#define HOST_XIP_OTR0CFG0_SPIWR_M                                    0x00000004U
#define HOST_XIP_OTR0CFG0_SPIWR_S                                    2U
/*

        Field:           SPIRD
        From..to bits:   3...3
        DefaultValue:    0x1
        Access type:     read-write
        Description:     REGION 0 SPI READ ENABLE:
                         0- Cannot issue a SPI Read from this region
                         1- Can issue a SPI Read from this region

*/
#define HOST_XIP_OTR0CFG0_SPIRD                                      0x00000008U
#define HOST_XIP_OTR0CFG0_SPIRD_M                                    0x00000008U
#define HOST_XIP_OTR0CFG0_SPIRD_S                                    3U
/*

        Field:           OFFSET
        From..to bits:   4...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Device related address offset

*/
#define HOST_XIP_OTR0CFG0_OFFSET_W                                   14U
#define HOST_XIP_OTR0CFG0_OFFSET_M                                   0x0003FFF0U
#define HOST_XIP_OTR0CFG0_OFFSET_S                                   4U
/*

        Field:           SECID1
        From..to bits:   20...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     6 MSB bits of ID+COUNTER field (out of 38bits)

*/
#define HOST_XIP_OTR0CFG0_SECID1_W                                   6U
#define HOST_XIP_OTR0CFG0_SECID1_M                                   0x03F00000U
#define HOST_XIP_OTR0CFG0_SECID1_S                                   20U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR0CFG1
    Offset name:         HOST_XIP_O_OTR0CFG1
    Relative address:    0x6004
    Description:         region 0 parameters config 1
    Default Value:       0x00010000

        Field:           STARTADDR
        From..to bits:   0...19
        DefaultValue:    0x10000
        Access type:     read-write
        Description:     System start address

*/
#define HOST_XIP_OTR0CFG1_STARTADDR_W                                20U
#define HOST_XIP_OTR0CFG1_STARTADDR_M                                0x000FFFFFU
#define HOST_XIP_OTR0CFG1_STARTADDR_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR0CFG2
    Offset name:         HOST_XIP_O_OTR0CFG2
    Relative address:    0x6008
    Description:         region 0 parameters config 2
    Default Value:       0x00017FFF

        Field:           ENDADDR
        From..to bits:   0...19
        DefaultValue:    0x17FFF
        Access type:     read-write
        Description:     System end address

*/
#define HOST_XIP_OTR0CFG2_ENDADDR_W                                  20U
#define HOST_XIP_OTR0CFG2_ENDADDR_M                                  0x000FFFFFU
#define HOST_XIP_OTR0CFG2_ENDADDR_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR0CFG3
    Offset name:         HOST_XIP_O_OTR0CFG3
    Relative address:    0x600C
    Description:         region 0 parameters config 3
    Default Value:       0x00000000

        Field:           SECID0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 LSB bits of ID+COUNTER field (out of 38bits)

*/
#define HOST_XIP_OTR0CFG3_SECID0_W                                   32U
#define HOST_XIP_OTR0CFG3_SECID0_M                                   0xFFFFFFFFU
#define HOST_XIP_OTR0CFG3_SECID0_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR1CFG0
    Offset name:         HOST_XIP_O_OTR1CFG0
    Relative address:    0x7000
    Description:         region 1 parameters config 0
    Default Value:       0x00000000

        Field:           REGION
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 1 ENABLED:
                         0- Disabled
                         1- Enabled
                         Region enabled for incoming transactions

*/
#define HOST_XIP_OTR1CFG0_REGION                                     0x00000001U
#define HOST_XIP_OTR1CFG0_REGION_M                                   0x00000001U
#define HOST_XIP_OTR1CFG0_REGION_S                                   0U
/*

        Field:           DEVICE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 1 DEVICE ID:
                         0- Device_0
                         1- Device_1

*/
#define HOST_XIP_OTR1CFG0_DEVICE                                     0x00000002U
#define HOST_XIP_OTR1CFG0_DEVICE_M                                   0x00000002U
#define HOST_XIP_OTR1CFG0_DEVICE_S                                   1U
/*

        Field:           SPIWR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 1 SPI WRITE ENABLE:
                         0- Cannot issue a SPI Write to this  region
                         1- Can issue a SPI Write to this  region

*/
#define HOST_XIP_OTR1CFG0_SPIWR                                      0x00000004U
#define HOST_XIP_OTR1CFG0_SPIWR_M                                    0x00000004U
#define HOST_XIP_OTR1CFG0_SPIWR_S                                    2U
/*

        Field:           SPIRD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 1 SPI READ ENABLE:
                         0- Cannot issue a SPI Read from this region
                         1- Can issue a SPI Read from this region

*/
#define HOST_XIP_OTR1CFG0_SPIRD                                      0x00000008U
#define HOST_XIP_OTR1CFG0_SPIRD_M                                    0x00000008U
#define HOST_XIP_OTR1CFG0_SPIRD_S                                    3U
/*

        Field:           OFFSET
        From..to bits:   4...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Device related address offset

*/
#define HOST_XIP_OTR1CFG0_OFFSET_W                                   14U
#define HOST_XIP_OTR1CFG0_OFFSET_M                                   0x0003FFF0U
#define HOST_XIP_OTR1CFG0_OFFSET_S                                   4U
/*

        Field:           SECID1
        From..to bits:   20...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     6 MSB bits of ID+COUNTER field (out of 38bits)

*/
#define HOST_XIP_OTR1CFG0_SECID1_W                                   6U
#define HOST_XIP_OTR1CFG0_SECID1_M                                   0x03F00000U
#define HOST_XIP_OTR1CFG0_SECID1_S                                   20U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR1CFG1
    Offset name:         HOST_XIP_O_OTR1CFG1
    Relative address:    0x7004
    Description:         region 1 parameters config 1
    Default Value:       0x00000001

        Field:           STARTADDR
        From..to bits:   0...19
        DefaultValue:    0x1
        Access type:     read-write
        Description:     System start address

*/
#define HOST_XIP_OTR1CFG1_STARTADDR_W                                20U
#define HOST_XIP_OTR1CFG1_STARTADDR_M                                0x000FFFFFU
#define HOST_XIP_OTR1CFG1_STARTADDR_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR1CFG2
    Offset name:         HOST_XIP_O_OTR1CFG2
    Relative address:    0x7008
    Description:         region 1 parameters config 2
    Default Value:       0x00000000

        Field:           ENDADDR
        From..to bits:   0...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     System end address

*/
#define HOST_XIP_OTR1CFG2_ENDADDR_W                                  20U
#define HOST_XIP_OTR1CFG2_ENDADDR_M                                  0x000FFFFFU
#define HOST_XIP_OTR1CFG2_ENDADDR_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR1CFG3
    Offset name:         HOST_XIP_O_OTR1CFG3
    Relative address:    0x700C
    Description:         region 1 parameters config 3
    Default Value:       0x00000000

        Field:           SECID0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 LSB bits of ID+COUNTER field (out of 38bits)

*/
#define HOST_XIP_OTR1CFG3_SECID0_W                                   32U
#define HOST_XIP_OTR1CFG3_SECID0_M                                   0xFFFFFFFFU
#define HOST_XIP_OTR1CFG3_SECID0_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR2CFG0
    Offset name:         HOST_XIP_O_OTR2CFG0
    Relative address:    0x8000
    Description:         region 2 parameters config 0
    Default Value:       0x00000000

        Field:           REGION
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 2 ENABLED:
                         0- Disabled
                         1- Enabled
                         Region enabled for incoming transactions

*/
#define HOST_XIP_OTR2CFG0_REGION                                     0x00000001U
#define HOST_XIP_OTR2CFG0_REGION_M                                   0x00000001U
#define HOST_XIP_OTR2CFG0_REGION_S                                   0U
/*

        Field:           DEVICE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 2 DEVICE ID:
                         0- Device_0
                         1- Device_1

*/
#define HOST_XIP_OTR2CFG0_DEVICE                                     0x00000002U
#define HOST_XIP_OTR2CFG0_DEVICE_M                                   0x00000002U
#define HOST_XIP_OTR2CFG0_DEVICE_S                                   1U
/*

        Field:           SPIWR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 2 SPI WRITE ENABLE:
                         0- Cannot issue a SPI Write to this  region
                         1- Can issue a SPI Write to this  region

*/
#define HOST_XIP_OTR2CFG0_SPIWR                                      0x00000004U
#define HOST_XIP_OTR2CFG0_SPIWR_M                                    0x00000004U
#define HOST_XIP_OTR2CFG0_SPIWR_S                                    2U
/*

        Field:           SPIRD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 2 SPI READ ENABLE:
                         0- Cannot issue a SPI Read from this region
                         1- Can issue a SPI Read from this region

*/
#define HOST_XIP_OTR2CFG0_SPIRD                                      0x00000008U
#define HOST_XIP_OTR2CFG0_SPIRD_M                                    0x00000008U
#define HOST_XIP_OTR2CFG0_SPIRD_S                                    3U
/*

        Field:           OFFSET
        From..to bits:   4...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Device related address offset

*/
#define HOST_XIP_OTR2CFG0_OFFSET_W                                   14U
#define HOST_XIP_OTR2CFG0_OFFSET_M                                   0x0003FFF0U
#define HOST_XIP_OTR2CFG0_OFFSET_S                                   4U
/*

        Field:           SECID1
        From..to bits:   20...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     6 MSB bits of ID+COUNTER field (out of 38bits)

*/
#define HOST_XIP_OTR2CFG0_SECID1_W                                   6U
#define HOST_XIP_OTR2CFG0_SECID1_M                                   0x03F00000U
#define HOST_XIP_OTR2CFG0_SECID1_S                                   20U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR2CFG1
    Offset name:         HOST_XIP_O_OTR2CFG1
    Relative address:    0x8004
    Description:         region 2 parameters config 1
    Default Value:       0x00000001

        Field:           STARTADDR
        From..to bits:   0...19
        DefaultValue:    0x1
        Access type:     read-write
        Description:     System start address

*/
#define HOST_XIP_OTR2CFG1_STARTADDR_W                                20U
#define HOST_XIP_OTR2CFG1_STARTADDR_M                                0x000FFFFFU
#define HOST_XIP_OTR2CFG1_STARTADDR_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR2CFG2
    Offset name:         HOST_XIP_O_OTR2CFG2
    Relative address:    0x8008
    Description:         region 2 parameters config 2
    Default Value:       0x00000000

        Field:           ENDADDR
        From..to bits:   0...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     System end address

*/
#define HOST_XIP_OTR2CFG2_ENDADDR_W                                  20U
#define HOST_XIP_OTR2CFG2_ENDADDR_M                                  0x000FFFFFU
#define HOST_XIP_OTR2CFG2_ENDADDR_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR2CFG3
    Offset name:         HOST_XIP_O_OTR2CFG3
    Relative address:    0x800C
    Description:         region 2 parameters config 3
    Default Value:       0x00000000

        Field:           SECID0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 LSB bits of ID+COUNTER field (out of 38bits)

*/
#define HOST_XIP_OTR2CFG3_SECID0_W                                   32U
#define HOST_XIP_OTR2CFG3_SECID0_M                                   0xFFFFFFFFU
#define HOST_XIP_OTR2CFG3_SECID0_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR3CFG0
    Offset name:         HOST_XIP_O_OTR3CFG0
    Relative address:    0x9000
    Description:         region 3 parameters config 0
    Default Value:       0x00000000

        Field:           REGION
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 3 ENABLED:
                         0- Disabled
                         1- Enabled
                         Region enabled for incoming transactions

*/
#define HOST_XIP_OTR3CFG0_REGION                                     0x00000001U
#define HOST_XIP_OTR3CFG0_REGION_M                                   0x00000001U
#define HOST_XIP_OTR3CFG0_REGION_S                                   0U
/*

        Field:           DEVICE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 3 DEVICE ID:
                         0- Device_0
                         1- Device_1

*/
#define HOST_XIP_OTR3CFG0_DEVICE                                     0x00000002U
#define HOST_XIP_OTR3CFG0_DEVICE_M                                   0x00000002U
#define HOST_XIP_OTR3CFG0_DEVICE_S                                   1U
/*

        Field:           SPIWR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 3 SPI WRITE ENABLE:
                         0- Cannot issue a SPI Write to this  region
                         1- Can issue a SPI Write to this  region

*/
#define HOST_XIP_OTR3CFG0_SPIWR                                      0x00000004U
#define HOST_XIP_OTR3CFG0_SPIWR_M                                    0x00000004U
#define HOST_XIP_OTR3CFG0_SPIWR_S                                    2U
/*

        Field:           SPIRD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REGION 3 SPI READ ENABLE:
                         0- Cannot issue a SPI Read from this region
                         1- Can issue a SPI Read from this region

*/
#define HOST_XIP_OTR3CFG0_SPIRD                                      0x00000008U
#define HOST_XIP_OTR3CFG0_SPIRD_M                                    0x00000008U
#define HOST_XIP_OTR3CFG0_SPIRD_S                                    3U
/*

        Field:           OFFSET
        From..to bits:   4...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Device related address offset

*/
#define HOST_XIP_OTR3CFG0_OFFSET_W                                   14U
#define HOST_XIP_OTR3CFG0_OFFSET_M                                   0x0003FFF0U
#define HOST_XIP_OTR3CFG0_OFFSET_S                                   4U
/*

        Field:           SECID1
        From..to bits:   20...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     6 MSB bits of ID+COUNTER field (out of 38bits)

*/
#define HOST_XIP_OTR3CFG0_SECID1_W                                   6U
#define HOST_XIP_OTR3CFG0_SECID1_M                                   0x03F00000U
#define HOST_XIP_OTR3CFG0_SECID1_S                                   20U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR3CFG1
    Offset name:         HOST_XIP_O_OTR3CFG1
    Relative address:    0x9004
    Description:         region 3 parameters config 1
    Default Value:       0x00000001

        Field:           STARTADDR
        From..to bits:   0...19
        DefaultValue:    0x1
        Access type:     read-write
        Description:     System start address

*/
#define HOST_XIP_OTR3CFG1_STARTADDR_W                                20U
#define HOST_XIP_OTR3CFG1_STARTADDR_M                                0x000FFFFFU
#define HOST_XIP_OTR3CFG1_STARTADDR_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR3CFG2
    Offset name:         HOST_XIP_O_OTR3CFG2
    Relative address:    0x9008
    Description:         region 3 parameters config 2
    Default Value:       0x00000000

        Field:           ENDADDR
        From..to bits:   0...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     System end address

*/
#define HOST_XIP_OTR3CFG2_ENDADDR_W                                  20U
#define HOST_XIP_OTR3CFG2_ENDADDR_M                                  0x000FFFFFU
#define HOST_XIP_OTR3CFG2_ENDADDR_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OTR3CFG3
    Offset name:         HOST_XIP_O_OTR3CFG3
    Relative address:    0x900C
    Description:         region 3 parameters config 3
    Default Value:       0x00000000

        Field:           SECID0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 LSB bits of ID+COUNTER field (out of 38bits)

*/
#define HOST_XIP_OTR3CFG3_SECID0_W                                   32U
#define HOST_XIP_OTR3CFG3_SECID0_M                                   0xFFFFFFFFU
#define HOST_XIP_OTR3CFG3_SECID0_S                                   0U

#endif /* __HW_HOST_XIP_H__*/
