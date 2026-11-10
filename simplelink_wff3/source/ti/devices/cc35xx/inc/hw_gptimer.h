/******************************************************************************
*  Filename:       hw_gptimer.h
*
*  Description:    Defines and prototypes for the GPTIMER peripheral.
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
#ifndef __HW_GPTIMER_H__
#define __HW_GPTIMER_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the GPTIMER component

--------------------------------------------------------------------------------- */

//Description Register
#define GPTIMER_O_DESC                                               0x00000000U

//Description Extended
#define GPTIMER_O_DESCEX                                             0x00000004U

//Start Configuration
#define GPTIMER_O_STARTCFG                                           0x00000008U

//Timer Control
#define GPTIMER_O_CTL                                                0x0000000CU

//Output Control
#define GPTIMER_O_OUTCTL                                             0x00000010U

//Counter
#define GPTIMER_O_CNTR                                               0x00000014U

//Clock Prescaler Configuration
#define GPTIMER_O_PRECFG                                             0x00000018U

//Prescaler Event
#define GPTIMER_O_PREEVENT                                           0x0000001CU

//Channel Input Filter
#define GPTIMER_O_CHFILT                                             0x00000020U

//Fault
#define GPTIMER_O_FAULT                                              0x00000024U

//Park
#define GPTIMER_O_PARK                                               0x00000028U

//Dead Band Delay
#define GPTIMER_O_DBDLY                                              0x0000002CU

//Dead Band Control
#define GPTIMER_O_DBCTL                                              0x00000030U

//Quadrature Decoder Status
#define GPTIMER_O_QDECSTAT                                           0x00000034U

//IR Generation
#define GPTIMER_O_IRGEN                                              0x00000038U

//Direct Memory Access
#define GPTIMER_O_DMA                                                0x0000003CU

//Direct Memory Access
#define GPTIMER_O_DMARW                                              0x00000040U

//ADC Trigger
#define GPTIMER_O_ADCTRG                                             0x00000044U

//IO Controller
#define GPTIMER_O_IOCTL                                              0x00000048U

//Interrupt mask
#define GPTIMER_O_IMASK                                              0x00000068U

//Raw interrupt status
#define GPTIMER_O_RIS                                                0x0000006CU

//Masked interrupt status
#define GPTIMER_O_MIS                                                0x00000070U

//Interrupt set register
#define GPTIMER_O_ISET                                               0x00000074U

//Interrupt clear register
#define GPTIMER_O_ICLR                                               0x00000078U

//Interrupt mask set register
#define GPTIMER_O_IMSET                                              0x0000007CU

//Interrupt mask clear register
#define GPTIMER_O_IMCLR                                              0x00000080U

//Debug control
#define GPTIMER_O_EMU                                                0x00000084U

//Channel 0 Configuration
#define GPTIMER_O_C0CFG                                              0x000000C0U

//Channel 1 Configuration
#define GPTIMER_O_C1CFG                                              0x000000C4U

//Channel 2 Configuration
#define GPTIMER_O_C2CFG                                              0x000000C8U

//Channel 3 Configuration
#define GPTIMER_O_C3CFG                                              0x000000CCU

//Pipeline Target
#define GPTIMER_O_PTGT                                               0x000000FCU

//Pipeline Channel 0 Capture Compare
#define GPTIMER_O_PC0CC                                              0x00000100U

//Pipeline Channel 1 Capture Compare
#define GPTIMER_O_PC1CC                                              0x00000104U

//Pipeline Channel 2 Capture Compare
#define GPTIMER_O_PC2CC                                              0x00000108U

//Pipeline Channel 3 Capture Compare
#define GPTIMER_O_PC3CC                                              0x0000010CU

//Target
#define GPTIMER_O_TGT                                                0x0000013CU

//Channel 0 Capture Compare
#define GPTIMER_O_C0CC                                               0x00000140U

//Channel 1 Capture Compare
#define GPTIMER_O_C1CC                                               0x00000144U

//Channel 2 Capture Compare
#define GPTIMER_O_C2CC                                               0x00000148U

//Channel 3 Capture Compare
#define GPTIMER_O_C3CC                                               0x0000014CU

//Pipeline Target No Clear
#define GPTIMER_O_PTGTNC                                             0x0000017CU

//Pipeline Channel 0 Capture Compare No Clear
#define GPTIMER_O_PC0CCNC                                            0x00000180U

//Pipeline Channel 1 Capture Compare No Clear
#define GPTIMER_O_PC1CCNC                                            0x00000184U

//Pipeline Channel 2 Capture Compare No Clear
#define GPTIMER_O_PC2CCNC                                            0x00000188U

//Pipeline Channel 3 Capture Compare No Clear
#define GPTIMER_O_PC3CCNC                                            0x0000018CU

//Target No Clear
#define GPTIMER_O_TGTNC                                              0x000001BCU

//Channel 0 Capture Compare No Clear
#define GPTIMER_O_C0CCNC                                             0x000001C0U

//Channel 1 Capture Compare No Clear
#define GPTIMER_O_C1CCNC                                             0x000001C4U

//Channel 2 Capture Compare No Clear
#define GPTIMER_O_C2CCNC                                             0x000001C8U

//Channel 3 Capture Compare No Clear
#define GPTIMER_O_C3CCNC                                             0x000001CCU

//Clock Enable Register
#define GPTIMER_O_CLKCFG                                             0x00001000U



/*-----------------------------------REGISTER------------------------------------
    Register name:       DESC
    Offset name:         GPTIMER_O_DESC
    Relative address:    0x0
    Description:         Description Register. This register provides IP module ID, revision information, instance index and standard MMR registers offset.
    Default Value:       0xDE491000

        Field:           MINREV
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Minor revision of IP.

*/
#define GPTIMER_DESC_MINREV_W                                        4U
#define GPTIMER_DESC_MINREV_M                                        0x0000000FU
#define GPTIMER_DESC_MINREV_S                                        0U
/*

        Field:           MAJREV
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Major revision of IP.

*/
#define GPTIMER_DESC_MAJREV_W                                        4U
#define GPTIMER_DESC_MAJREV_M                                        0x000000F0U
#define GPTIMER_DESC_MAJREV_S                                        4U
/*

        Field:           INSTIDX
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     IP Instance ID number. If multiple instances of IP exist in the device, this field can identify the instance number.

*/
#define GPTIMER_DESC_INSTIDX_W                                       4U
#define GPTIMER_DESC_INSTIDX_M                                       0x00000F00U
#define GPTIMER_DESC_INSTIDX_S                                       8U
/*

        Field:           STDIPOFF
        From..to bits:   12...15
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Standard IP MMR block offset. Standard IP MMRs are the set of from aggregated IRQ registers till DTB.

                         0: Standard IP MMRs do not exist

                         0x1-0xF: Standard IP MMRs begin at offset of (64*[STDIPOFF] from the base IP address)

*/
#define GPTIMER_DESC_STDIPOFF_W                                      4U
#define GPTIMER_DESC_STDIPOFF_M                                      0x0000F000U
#define GPTIMER_DESC_STDIPOFF_S                                      12U
/*

        Field:           MODID
        From..to bits:   16...31
        DefaultValue:    0xDE49
        Access type:     read-only
        Description:     Module identifier used to uniquely identify this IP.

*/
#define GPTIMER_DESC_MODID_W                                         16U
#define GPTIMER_DESC_MODID_M                                         0xFFFF0000U
#define GPTIMER_DESC_MODID_S                                         16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DESCEX
    Offset name:         GPTIMER_O_DESCEX
    Relative address:    0x4
    Description:         Description Extended

                        This register describes the parameters of the LGPT.
    Default Value:       0x00000000

        Field:           NCH
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of channels.

*/
#define GPTIMER_DESCEX_NCH_W                                         4U
#define GPTIMER_DESCEX_NCH_M                                         0x0000000FU
#define GPTIMER_DESCEX_NCH_S                                         0U
/*

        Field:           CNTRW
        From..to bits:   4...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Counter bit-width.
                         The maximum counter value is equal to 2^[CNTRW]-1.

        ENUMs:
            CNTR16:                      16-bit counter.
            CNTR24:                      24-bit counter.
            CNTR32:                      32-bit counter.
            RESERVED:                    RESERVED
*/
#define GPTIMER_DESCEX_CNTRW_W                                       2U
#define GPTIMER_DESCEX_CNTRW_M                                       0x00000030U
#define GPTIMER_DESCEX_CNTRW_S                                       4U
#define GPTIMER_DESCEX_CNTRW_CNTR16                                  0x00000000U
#define GPTIMER_DESCEX_CNTRW_CNTR24                                  0x00000010U
#define GPTIMER_DESCEX_CNTRW_CNTR32                                  0x00000020U
#define GPTIMER_DESCEX_CNTRW_RESERVED                                0x00000030U
/*

        Field:           HINT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Has interrupt output and logic.

*/
#define GPTIMER_DESCEX_HINT                                          0x00000040U
#define GPTIMER_DESCEX_HINT_M                                        0x00000040U
#define GPTIMER_DESCEX_HINT_S                                        6U
/*

        Field:           HDMA
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Has uDMA output and logic.

*/
#define GPTIMER_DESCEX_HDMA                                          0x00000080U
#define GPTIMER_DESCEX_HDMA_M                                        0x00000080U
#define GPTIMER_DESCEX_HDMA_S                                        7U
/*

        Field:           CIFS
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Channel input filter size. The prevailing state filter can maximum be configured to 2^[CIFS]-1.

*/
#define GPTIMER_DESCEX_CIFS_W                                        4U
#define GPTIMER_DESCEX_CIFS_M                                        0x00000F00U
#define GPTIMER_DESCEX_CIFS_S                                        8U
/*

        Field:           HCIF
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Has channel input filter.

*/
#define GPTIMER_DESCEX_HCIF                                          0x00001000U
#define GPTIMER_DESCEX_HCIF_M                                        0x00001000U
#define GPTIMER_DESCEX_HCIF_S                                        12U
/*

        Field:           HQDEC
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Has Quadrature Decoder.

*/
#define GPTIMER_DESCEX_HQDEC                                         0x00002000U
#define GPTIMER_DESCEX_HQDEC_M                                       0x00002000U
#define GPTIMER_DESCEX_HQDEC_S                                       13U
/*

        Field:           PREW
        From..to bits:   14...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Prescaler width. The prescaler can maximum be configured to 2^[PREW]-1.

*/
#define GPTIMER_DESCEX_PREW_W                                        4U
#define GPTIMER_DESCEX_PREW_M                                        0x0003C000U
#define GPTIMER_DESCEX_PREW_S                                        14U
/*

        Field:           HDBF
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Has Dead-Band, Fault, and Park logic.

*/
#define GPTIMER_DESCEX_HDBF                                          0x00040000U
#define GPTIMER_DESCEX_HDBF_M                                        0x00040000U
#define GPTIMER_DESCEX_HDBF_S                                        18U
/*

        Field:           HIR
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Has IR logic.

*/
#define GPTIMER_DESCEX_HIR                                           0x00080000U
#define GPTIMER_DESCEX_HIR_M                                         0x00080000U
#define GPTIMER_DESCEX_HIR_S                                         19U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STARTCFG
    Offset name:         GPTIMER_O_STARTCFG
    Relative address:    0x8
    Description:         Start Configuration

                        This register is only for when [CTL.MODE] is configured to one of the SYNC modes.
                        This register defines when this LGPT starts.
    Default Value:       0x00000000

        Field:           LGPT0
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     LGPT start

        ENUMs:
            EV_SYNC:                     LGPT starts when synchronized event input is high. Configured here [EVTSVT:LGPTSYNCSEL].
*/
#define GPTIMER_STARTCFG_LGPT0_W                                     2U
#define GPTIMER_STARTCFG_LGPT0_M                                     0x00000003U
#define GPTIMER_STARTCFG_LGPT0_S                                     0U
#define GPTIMER_STARTCFG_LGPT0_EV_SYNC                               0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTL
    Offset name:         GPTIMER_O_CTL
    Relative address:    0xC
    Description:         Timer Control
    Default Value:       0x00000000

        Field:           MODE
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Timer mode control

                         The [CNTR.*] restarts from 0 when MODE is written to UP_ONCE, UP_PER, UPDWN_PER, QDEC, SYNC_UP_ONCE, SYNC_UP_PER or SYNC_UPDWN_PER.

                         When writing MODE all internally queued updates to the channels and [TGT.*] is cleared.

                         When configuring the timer, MODE should be the last thing to configure. If changing timer configuration after MODE has been set is necessary, instructions, if any, given in the configuration registers should be followed. See for example [C0CFG.*].

        ENUMs:
            DIS:                         Disable timer. Updates to counter, channels, and events stop.
            UP_ONCE:                     Count up once. The timer increments from 0 to target value,  then stops and sets MODE to DIS.
            UP_PER:                      Count up periodically. The timer increments from 0 to target value, repeatedly.

                         Period = (target value + 1) * timer clock period
            UPDWN_PER:                   Count up and down periodically. The timer counts from 0 to target value and back to 0, repeatedly.

                         Period =  (target value * 2) * timer clock period
            QDEC:                        The timer functions as a quadrature decoder. IOC input 0, IOC input 1 and IOC input 2 are used respectively as PHA, PHB and IDX inputs. IDX can be turned off by setting [C2CFG.EDGE] = NONE.
                         The timer clock frequency sets the sample rate of the QDEC logic. This frequency can be configured in [PRECFG.*].
            SYNC_UP_ONCE:                Start counting up once synchronous to another LGPT, selected within [STARTCFG.*]. The timer is started by setting [CTL.MODE] = UP_ONCE automatically.
                         It then functions as a normal timer in [CTL.MODE] = UP_ONCE, incrementing from 0 to target value,  then stops and sets MODE to DIS.
            SYNC_UP_PER:                 Start counting up periodically synchronous to another LGPT,  selected within [STARTCFG.*]. The timer is started by setting [CTL.MODE] = UP_PER automatically.
                         It then operates as a normal timer in [CTL.MODE] = UP_PER, incrementing from 0 to target value, repeatedly.

                         Period =  (target value * 2) * timer clock period
            SYNC_UPDWN_PER:              Start counting up and down periodically synchronous to another LGPT,  selected within [STARTCFG.*]. The timer is started by setting [CTL.MODE] = UPDWN_PER automatically.
                         It then operates as a normal timer in [CTL.MODE] = UPDWN_PER, counting from 0 to target value and back to 0, repeatedly.

                         Period =  (target value * 2) * timer clock period
*/
#define GPTIMER_CTL_MODE_W                                           3U
#define GPTIMER_CTL_MODE_M                                           0x00000007U
#define GPTIMER_CTL_MODE_S                                           0U
#define GPTIMER_CTL_MODE_DIS                                         0x00000000U
#define GPTIMER_CTL_MODE_UP_ONCE                                     0x00000001U
#define GPTIMER_CTL_MODE_UP_PER                                      0x00000002U
#define GPTIMER_CTL_MODE_UPDWN_PER                                   0x00000003U
#define GPTIMER_CTL_MODE_QDEC                                        0x00000004U
#define GPTIMER_CTL_MODE_SYNC_UP_ONCE                                0x00000005U
#define GPTIMER_CTL_MODE_SYNC_UP_PER                                 0x00000006U
#define GPTIMER_CTL_MODE_SYNC_UPDWN_PER                              0x00000007U
/*

        Field:           CMPDIR
        From..to bits:   3...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Compare direction.

                         This bit field controls the direction the counter must have in order to set the [RIS.*] compare interrupts.

        ENUMs:
            BOTH:                        Compare [RIS.*] fields are set on up count and down count.
            UP:                          Compare [RIS.*] fields are only set on up count.
            DOWN:                        Compare [RIS.*] fields are only set on down count.
            RESERVED:                    RESERVED
*/
#define GPTIMER_CTL_CMPDIR_W                                         2U
#define GPTIMER_CTL_CMPDIR_M                                         0x00000018U
#define GPTIMER_CTL_CMPDIR_S                                         3U
#define GPTIMER_CTL_CMPDIR_BOTH                                      0x00000000U
#define GPTIMER_CTL_CMPDIR_UP                                        0x00000008U
#define GPTIMER_CTL_CMPDIR_DOWN                                      0x00000010U
#define GPTIMER_CTL_CMPDIR_RESERVED                                  0x00000018U
/*

        Field:           INTP
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Interrupt Phase.
                         This bit field controls when the [RIS.TGT] and [RIS.ZERO] interrupts are set.

        ENUMs:
            EARLY:                       [RIS.TGT] and [RIS.ZERO] are set one system clock cycle after [CNTR.*] = TARGET/ZERO.
            LATE:                        [RIS.TGT] and [RIS.ZERO] are set one timer clock cycle after [CNTR.*] = TARGET/ZERO.
*/
#define GPTIMER_CTL_INTP                                             0x00000020U
#define GPTIMER_CTL_INTP_M                                           0x00000020U
#define GPTIMER_CTL_INTP_S                                           5U
#define GPTIMER_CTL_INTP_EARLY                                       0x00000000U
#define GPTIMER_CTL_INTP_LATE                                        0x00000020U
/*

        Field:           C0RST
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Channel 0 reset.

        ENUMs:
            NOEFF:                       No effect.
            RST:                         Reset [C0CC], [PC0CC], and [C0CFG].
*/
#define GPTIMER_CTL_C0RST                                            0x00000100U
#define GPTIMER_CTL_C0RST_M                                          0x00000100U
#define GPTIMER_CTL_C0RST_S                                          8U
#define GPTIMER_CTL_C0RST_NOEFF                                      0x00000000U
#define GPTIMER_CTL_C0RST_RST                                        0x00000100U
/*

        Field:           C1RST
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Channel 1 reset.

        ENUMs:
            NOEFF:                       No effect.
            RST:                         Reset [C1CC.*], [PC1CC.*], and [C1CFG.*].
*/
#define GPTIMER_CTL_C1RST                                            0x00000200U
#define GPTIMER_CTL_C1RST_M                                          0x00000200U
#define GPTIMER_CTL_C1RST_S                                          9U
#define GPTIMER_CTL_C1RST_NOEFF                                      0x00000000U
#define GPTIMER_CTL_C1RST_RST                                        0x00000200U
/*

        Field:           C2RST
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Channel 2 reset.

        ENUMs:
            NOEFF:                       No effect.
            RST:                         Reset [C2CC.*], [PC2CC.*], and [C2CFG.*].
*/
#define GPTIMER_CTL_C2RST                                            0x00000400U
#define GPTIMER_CTL_C2RST_M                                          0x00000400U
#define GPTIMER_CTL_C2RST_S                                          10U
#define GPTIMER_CTL_C2RST_NOEFF                                      0x00000000U
#define GPTIMER_CTL_C2RST_RST                                        0x00000400U
/*

        Field:           C3RST
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Channel 3 reset.

        ENUMs:
            NOEFF:                       No effect.
            RST:                         Reset [C3CC.*], [PC3CC.*], and [C3CFG.*].
*/
#define GPTIMER_CTL_C3RST                                            0x00000800U
#define GPTIMER_CTL_C3RST_M                                          0x00000800U
#define GPTIMER_CTL_C3RST_S                                          11U
#define GPTIMER_CTL_C3RST_NOEFF                                      0x00000000U
#define GPTIMER_CTL_C3RST_RST                                        0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OUTCTL
    Offset name:         GPTIMER_O_OUTCTL
    Relative address:    0x10
    Description:         Output Control

                        Set and clear individual outputs manually. Manual update of an output takes priority over automatic channel updates to the same output. It is not possible to set and clear an output at the same time, such requests will be neglected.

                        An output can be automatically cleared, set, toggled, or pulsed by each channel, listed in decreasing order of priority. The action with highest priority happens when multiple channels want to update an output at the same time.

                        All outputs are connected to the event fabric and the IO controller. The outputs going to the IO controller have an additional complementary output, this output is the inverted IO output. Both the IO and the IO complementary outputs are passed through an IO Controller, see [IOCTL.*].
    Default Value:       0x00000000

        Field:           CLROUT0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear output 0.

                         Write 1 to clear output 0.

*/
#define GPTIMER_OUTCTL_CLROUT0                                       0x00000001U
#define GPTIMER_OUTCTL_CLROUT0_M                                     0x00000001U
#define GPTIMER_OUTCTL_CLROUT0_S                                     0U
/*

        Field:           SETOUT0
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set output 0.

                         Write 1 to set output 0.

*/
#define GPTIMER_OUTCTL_SETOUT0                                       0x00000002U
#define GPTIMER_OUTCTL_SETOUT0_M                                     0x00000002U
#define GPTIMER_OUTCTL_SETOUT0_S                                     1U
/*

        Field:           CLROUT1
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear output 1.

                         Write 1 to clear output 1.

*/
#define GPTIMER_OUTCTL_CLROUT1                                       0x00000004U
#define GPTIMER_OUTCTL_CLROUT1_M                                     0x00000004U
#define GPTIMER_OUTCTL_CLROUT1_S                                     2U
/*

        Field:           SETOUT1
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set output 1.

                         Write 1 to set output 1.

*/
#define GPTIMER_OUTCTL_SETOUT1                                       0x00000008U
#define GPTIMER_OUTCTL_SETOUT1_M                                     0x00000008U
#define GPTIMER_OUTCTL_SETOUT1_S                                     3U
/*

        Field:           CLROUT2
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear output 2.

                         Write 1 to clear output 2.

*/
#define GPTIMER_OUTCTL_CLROUT2                                       0x00000010U
#define GPTIMER_OUTCTL_CLROUT2_M                                     0x00000010U
#define GPTIMER_OUTCTL_CLROUT2_S                                     4U
/*

        Field:           SETOUT2
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set output 2.

                         Write 1 to set output 2.

*/
#define GPTIMER_OUTCTL_SETOUT2                                       0x00000020U
#define GPTIMER_OUTCTL_SETOUT2_M                                     0x00000020U
#define GPTIMER_OUTCTL_SETOUT2_S                                     5U
/*

        Field:           CLROUT3
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear output 3.

                         Write 1 to clear output 3.

*/
#define GPTIMER_OUTCTL_CLROUT3                                       0x00000040U
#define GPTIMER_OUTCTL_CLROUT3_M                                     0x00000040U
#define GPTIMER_OUTCTL_CLROUT3_S                                     6U
/*

        Field:           SETOUT3
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set output 3.

                         Write 1 to set output 3.

*/
#define GPTIMER_OUTCTL_SETOUT3                                       0x00000080U
#define GPTIMER_OUTCTL_SETOUT3_M                                     0x00000080U
#define GPTIMER_OUTCTL_SETOUT3_S                                     7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CNTR
    Offset name:         GPTIMER_O_CNTR
    Relative address:    0x14
    Description:         Counter
                        The counter of this timer. After [CTL.MODE] is set the counter updates at the rate specified in [PRECFG.*].
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Current counter value.
                         If [CTL.MODE] = QDEC this can be used to set the initial counter value during QDEC.

*/
#define GPTIMER_CNTR_VAL_W                                           32U
#define GPTIMER_CNTR_VAL_M                                           0xFFFFFFFFU
#define GPTIMER_CNTR_VAL_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRECFG
    Offset name:         GPTIMER_O_PRECFG
    Relative address:    0x18
    Description:         Clock Prescaler Configuration

                        This register is used to set the timer clock period. The prescaler is a counter which counts down from the value [TICKDIV]. When the prescaler counter reaches zero, [CNTR.*] is updated. The field [TICKDIV] effectively divides the prescaler tick source. The timer clock frequency can be calculated as [TICKSRC]/([TICKDIV]+1).
    Default Value:       0x00000000

        Field:           TICKSRC
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Prescaler tick source.

                         [TICKSRC] determines the source which decrements the prescaler.

        ENUMs:
            CLK:                         Prescaler is updated at the system clock.
            RISE_TICK:                   Prescaler is updated at the rising edge of TICKEN.
            FALL_TICK:                   Prescaler is updated at the falling edge of TICKEN.
            BOTH_TICK:                   Prescaler is updated at both edges of TICKEN.
*/
#define GPTIMER_PRECFG_TICKSRC_W                                     2U
#define GPTIMER_PRECFG_TICKSRC_M                                     0x00000003U
#define GPTIMER_PRECFG_TICKSRC_S                                     0U
#define GPTIMER_PRECFG_TICKSRC_CLK                                   0x00000000U
#define GPTIMER_PRECFG_TICKSRC_RISE_TICK                             0x00000001U
#define GPTIMER_PRECFG_TICKSRC_FALL_TICK                             0x00000002U
#define GPTIMER_PRECFG_TICKSRC_BOTH_TICK                             0x00000003U
/*

        Field:           TICKDIV
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tick division.

                         [TICKDIV] determines the timer clock frequency for the counter, and timer output updates. The timer clock frequency is the clock selected by [TICKSRC] divided by ([TICKDIV] + 1). This inverse is the timer clock period.

                         0x00: Divide by 1.
                         0x01: Divide by 2.
                         ...
                         0xFF: Divide by 256.

*/
#define GPTIMER_PRECFG_TICKDIV_W                                     8U
#define GPTIMER_PRECFG_TICKDIV_M                                     0x0000FF00U
#define GPTIMER_PRECFG_TICKDIV_S                                     8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PREEVENT
    Offset name:         GPTIMER_O_PREEVENT
    Relative address:    0x1C
    Description:         Prescaler Event

                        This register is used to output a logic high signal before the zero crossing of the prescaler counter. The output is routed to the IOC.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Sets the HIGH time of the prescaler event output.

                         Event goes high when the prescaler counter equals [VAL]. Event goes low when prescaler counter is 0.

                         Note:
                         - Can be used to precharge or turn an external component on for a short time before sampling, like in QDEC.
                         - If there is a requirement to create such events that have very short periods compared to timer clock period, use two timers. One timer acts as prescaler and event generator for another timer.

*/
#define GPTIMER_PREEVENT_VAL_W                                       8U
#define GPTIMER_PREEVENT_VAL_M                                       0x000000FFU
#define GPTIMER_PREEVENT_VAL_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CHFILT
    Offset name:         GPTIMER_O_CHFILT
    Relative address:    0x20
    Description:         Channel Input Filter

                        This register is used to configure the filter on the channel inputs. The configuration is for all inputs.
                        The filter is enabled when a channel is in capture mode.

                        The input to the filter is passed to the edge detection logic if [LOAD] + 1 consecutive input samples are equal. The filter functions as a down counter, counting down every input sample.
                        If two consecutive samples are unequal, the filter counter restarts from [LOAD].
                        If the filter counter reaches zero, the input signal is valid and passed to the edge detection logic.

                        The channel filter should only be configured while the [CTL.MODE] = DIS. Configuring the filter while the timer is running can result in unexpected behavior.
    Default Value:       0x00000000

        Field:           MODE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel filter mode

        ENUMs:
            BYPASS:                      Filter is bypassed. No Filter is used.
            CLK:                         Filter is clocked by system clock.
            TICKSRC:                     Filter is clocked by [PRECFG.TICKSRC].
            TIMERCLK:                    Filter is clocked by timer clock.
*/
#define GPTIMER_CHFILT_MODE_W                                        2U
#define GPTIMER_CHFILT_MODE_M                                        0x00000003U
#define GPTIMER_CHFILT_MODE_S                                        0U
#define GPTIMER_CHFILT_MODE_BYPASS                                   0x00000000U
#define GPTIMER_CHFILT_MODE_CLK                                      0x00000001U
#define GPTIMER_CHFILT_MODE_TICKSRC                                  0x00000002U
#define GPTIMER_CHFILT_MODE_TIMERCLK                                 0x00000003U
/*

        Field:           LOAD
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The input of the channel filter is passed to the edge detection logic after [LOAD] + 1 consecutive equal samples.

*/
#define GPTIMER_CHFILT_LOAD_W                                        8U
#define GPTIMER_CHFILT_LOAD_M                                        0x0000FF00U
#define GPTIMER_CHFILT_LOAD_S                                        8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FAULT
    Offset name:         GPTIMER_O_FAULT
    Relative address:    0x24
    Description:         Fault

                        This register is used to configure the fault input logic.

                        Primary use scenario is to select [CTL] before starting the timer. Follow these steps to configure [CTL] while [CTL.MODE] is different from DIS:
                        - Set [C0CFG.EDGE] to NONE.
                        - Configure [CTL].
                        - Wait for three system clock periods before setting [C0CFG.EDGE] different from NONE.
                        These steps prevent fault detection caused by expired signal values in synchronize and edge-detection circuit.
    Default Value:       0x00000000

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Fault control

                         On active fault input the counter can optionally stop. If the counter stops this is done by hardware, software must then restart the timer if wanted. The fault input overrides channel 0 IOC input when [CTL] != DIS.
                         This means that channel 0 receives fault as input signal when [C0CFG.INPUT] = IO and [CTL] != DIS.

                         [CHFILT.*] can be used to avoid glitching on the fault input. Fault is level triggered, the polarity is set by the [C0CFG.EDGE] field. Here  [C0CFG.EDGE] = RISE gives active high and [C0CFG.EDGE] = FALL gives active low polarity.

                         Fault is typically used together with [PARK.*] to stop the PWM signal to an external motor control circuit safely. Configure [PARK.*] to ensure predefined values of the PWM outputs.

                         If [CTL] != DIS the [RIS.FAULT] interrupt is set immediately when the fault input is active while [CTL.MODE] != DIS.

                         The three modes of fault is described below:

                         [CTL] = IMMEDIATE
                         In this mode the counter stops immediately on an active fault input. This is done by hardware by setting [CTL.MODE] = DIS. To start the counter software must set [CTL.MODE] != DIS.
                         When the counter has stopped, the input synchronizers and the channel filter is not running. This means that if [RIS.FAULT] is cleared it will not be set again while [CTL.MODE] = DIS.

                         [CTL] = ZEROCOND
                         In this mode the counter stops when [CNTR.*] = 0 after an active fault input. If the [RIS.FAULT] interrupt has been cleared by software before [CNTR.*] = 0, and the fault input is inactive, the counter will continue as normal.
                         When the counter stops on zero, it can be started again by clearing the [RIS.FAULT] interrupt if the fault input is inactive. To change the counter mode set [CTL.MODE] = DIS, clear the [RIS.FAULT] interrupt, then start timer in wanted mode.

                         [CTL] = IRQ
                         In this mode only the [RIS.FAULT] flag is set on an active fault input.


        ENUMs:
            DIS:                         Disable. The timer ignores fault.
            IMMEDIATE:                   Immediate reaction. The counter stops immediately on fault.
            ZERCOND:                     Zero condition. The counter stops when [CNTR.*] = 0.
            IRQ:                         Interrupt request. Only set [RIS.FAULT] on active fault.
*/
#define GPTIMER_FAULT_CTL_W                                          2U
#define GPTIMER_FAULT_CTL_M                                          0x00000003U
#define GPTIMER_FAULT_CTL_S                                          0U
#define GPTIMER_FAULT_CTL_DIS                                        0x00000000U
#define GPTIMER_FAULT_CTL_IMMEDIATE                                  0x00000001U
#define GPTIMER_FAULT_CTL_ZERCOND                                    0x00000002U
#define GPTIMER_FAULT_CTL_IRQ                                        0x00000003U
/*

        Field:           RES
        From..to bits:   2...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Software should not rely on the value of a reserved. Writing any other value than the reset value may result in undefined behavior.

*/
#define GPTIMER_FAULT_RES_W                                          30U
#define GPTIMER_FAULT_RES_M                                          0xFFFFFFFCU
#define GPTIMER_FAULT_RES_S                                          2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PARK
    Offset name:         GPTIMER_O_PARK
    Relative address:    0x28
    Description:         Park

                        This register configures how the outputs should be set in Park mode. Park mode is either entered by debug halt or fault. Park mode is activated when the counter stops. Park mode is inactive when the counter starts. When park mode is active all outputs are set to their predefined states.

                        For IO output signals which have enabled dead band, a dead band insertion will be done before switching to the predefined state.
    Default Value:       0x00000000

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Park Control.

        ENUMs:
            DIS:                         Disable park mode.
            FAULT:                       Enter park mode on fault.
            DEBUG:                       Enter park mode on debug.
            BOTH:                        Enter parkmode on fault or debug.
*/
#define GPTIMER_PARK_CTL_W                                           2U
#define GPTIMER_PARK_CTL_M                                           0x00000003U
#define GPTIMER_PARK_CTL_S                                           0U
#define GPTIMER_PARK_CTL_DIS                                         0x00000000U
#define GPTIMER_PARK_CTL_FAULT                                       0x00000001U
#define GPTIMER_PARK_CTL_DEBUG                                       0x00000002U
#define GPTIMER_PARK_CTL_BOTH                                        0x00000003U
/*

        Field:           IOPS0
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO Park State 0

                         Park state for IO output 0.

        ENUMs:
            HIGH:                        Output is set high in park mode.
            LOW:                         Output is set low in park mode.
*/
#define GPTIMER_PARK_IOPS0                                           0x00000004U
#define GPTIMER_PARK_IOPS0_M                                         0x00000004U
#define GPTIMER_PARK_IOPS0_S                                         2U
#define GPTIMER_PARK_IOPS0_HIGH                                      0x00000004U
#define GPTIMER_PARK_IOPS0_LOW                                       0x00000000U
/*

        Field:           IOCPS0
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO Complementary Park State 0

                         Park state for IO Complementary output 0.

        ENUMs:
            LOW:                         Output is set low in park mode.
            HIGH:                        Output is set high in park mode.
*/
#define GPTIMER_PARK_IOCPS0                                          0x00000008U
#define GPTIMER_PARK_IOCPS0_M                                        0x00000008U
#define GPTIMER_PARK_IOCPS0_S                                        3U
#define GPTIMER_PARK_IOCPS0_LOW                                      0x00000000U
#define GPTIMER_PARK_IOCPS0_HIGH                                     0x00000008U
/*

        Field:           IOPS1
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO Park State 1

                         Park state for IO output 1.

        ENUMs:
            LOW:                         Output is set low in park mode.
            HIGH:                        Output is set high in park mode.
*/
#define GPTIMER_PARK_IOPS1                                           0x00000010U
#define GPTIMER_PARK_IOPS1_M                                         0x00000010U
#define GPTIMER_PARK_IOPS1_S                                         4U
#define GPTIMER_PARK_IOPS1_LOW                                       0x00000000U
#define GPTIMER_PARK_IOPS1_HIGH                                      0x00000010U
/*

        Field:           IOCPS1
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO Complementary Park State 1

                         Park state for IO Complementary output 1.

        ENUMs:
            LOW:                         Output is set low in park mode.
            HIGH:                        Output is set high in park mode.
*/
#define GPTIMER_PARK_IOCPS1                                          0x00000020U
#define GPTIMER_PARK_IOCPS1_M                                        0x00000020U
#define GPTIMER_PARK_IOCPS1_S                                        5U
#define GPTIMER_PARK_IOCPS1_LOW                                      0x00000000U
#define GPTIMER_PARK_IOCPS1_HIGH                                     0x00000020U
/*

        Field:           IOPS2
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO Park State 2

                         Park state for IO output 2.

        ENUMs:
            LOW:                         Output is set low in park mode.
            HIGH:                        Output is set high in park mode.
*/
#define GPTIMER_PARK_IOPS2                                           0x00000040U
#define GPTIMER_PARK_IOPS2_M                                         0x00000040U
#define GPTIMER_PARK_IOPS2_S                                         6U
#define GPTIMER_PARK_IOPS2_LOW                                       0x00000000U
#define GPTIMER_PARK_IOPS2_HIGH                                      0x00000040U
/*

        Field:           IOCPS2
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO Complementary Park State 2

                         Park state for IO Complementary output 2.

        ENUMs:
            LOW:                         Output is set low in park mode.
            HIGH:                        Output is set high in park mode.
*/
#define GPTIMER_PARK_IOCPS2                                          0x00000080U
#define GPTIMER_PARK_IOCPS2_M                                        0x00000080U
#define GPTIMER_PARK_IOCPS2_S                                        7U
#define GPTIMER_PARK_IOCPS2_LOW                                      0x00000000U
#define GPTIMER_PARK_IOCPS2_HIGH                                     0x00000080U
/*

        Field:           IOPS3
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO Park State 3

                         Park state for IO output 3.

        ENUMs:
            LOW:                         Output is set low in park mode.
            HIGH:                        Output is set high in park mode.
*/
#define GPTIMER_PARK_IOPS3                                           0x00000100U
#define GPTIMER_PARK_IOPS3_M                                         0x00000100U
#define GPTIMER_PARK_IOPS3_S                                         8U
#define GPTIMER_PARK_IOPS3_LOW                                       0x00000000U
#define GPTIMER_PARK_IOPS3_HIGH                                      0x00000100U
/*

        Field:           IOCPS3
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO Complementary Park State 3

                         Park state for IO Complementary output 3.

        ENUMs:
            LOW:                         Output is set low in park mode.
            HIGH:                        Output is set high in park mode.
*/
#define GPTIMER_PARK_IOCPS3                                          0x00000200U
#define GPTIMER_PARK_IOCPS3_M                                        0x00000200U
#define GPTIMER_PARK_IOCPS3_S                                        9U
#define GPTIMER_PARK_IOCPS3_LOW                                      0x00000000U
#define GPTIMER_PARK_IOCPS3_HIGH                                     0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBDLY
    Offset name:         GPTIMER_O_DBDLY
    Relative address:    0x2C
    Description:         Dead Band Delay

                        This register is used to insert a dead band delay when generating complementary PWM signals. To enable dead band, on for example IO output 0, create a reference PWM signal on Output 0, then set  [DBCTL.IOC0] = EN.

                        TBD: 12-bit width fall delay and rise delay may be excessive, if 8-bits are enough we can join DBDLY and DBCTL.
    Default Value:       0x00000000

        Field:           RISEDLY
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Rise delay.

                         The number of system clock periods inserted between the rise of the dead band reference signal and the rise of the output signal.

*/
#define GPTIMER_DBDLY_RISEDLY_W                                      12U
#define GPTIMER_DBDLY_RISEDLY_M                                      0x00000FFFU
#define GPTIMER_DBDLY_RISEDLY_S                                      0U
/*

        Field:           FALLDLY
        From..to bits:   16...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Fall delay.

                         The number of system clock periods inserted between the fall of the dead band reference signal and the rise of the inverted output signal.

*/
#define GPTIMER_DBDLY_FALLDLY_W                                      12U
#define GPTIMER_DBDLY_FALLDLY_M                                      0x0FFF0000U
#define GPTIMER_DBDLY_FALLDLY_S                                      16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBCTL
    Offset name:         GPTIMER_O_DBCTL
    Relative address:    0x30
    Description:         Dead Band Control

                        This register is used to enable dead band for IOC outputs.
    Default Value:       0x00000000

        Field:           IO0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable dead band on IO and IO complementary output 0.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_DBCTL_IO0                                            0x00000001U
#define GPTIMER_DBCTL_IO0_M                                          0x00000001U
#define GPTIMER_DBCTL_IO0_S                                          0U
#define GPTIMER_DBCTL_IO0_DIS                                        0x00000000U
#define GPTIMER_DBCTL_IO0_EN                                         0x00000001U
/*

        Field:           IO1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable dead band on IO and IO complementary output 1.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_DBCTL_IO1                                            0x00000002U
#define GPTIMER_DBCTL_IO1_M                                          0x00000002U
#define GPTIMER_DBCTL_IO1_S                                          1U
#define GPTIMER_DBCTL_IO1_DIS                                        0x00000000U
#define GPTIMER_DBCTL_IO1_EN                                         0x00000002U
/*

        Field:           IO2
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable dead band on IO and IO complementary output 2.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_DBCTL_IO2                                            0x00000004U
#define GPTIMER_DBCTL_IO2_M                                          0x00000004U
#define GPTIMER_DBCTL_IO2_S                                          2U
#define GPTIMER_DBCTL_IO2_DIS                                        0x00000000U
#define GPTIMER_DBCTL_IO2_EN                                         0x00000004U
/*

        Field:           IO3
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable dead band on IO and IO complementary output 3.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_DBCTL_IO3                                            0x00000008U
#define GPTIMER_DBCTL_IO3_M                                          0x00000008U
#define GPTIMER_DBCTL_IO3_S                                          3U
#define GPTIMER_DBCTL_IO3_DIS                                        0x00000000U
#define GPTIMER_DBCTL_IO3_EN                                         0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       QDECSTAT
    Offset name:         GPTIMER_O_QDECSTAT
    Relative address:    0x34
    Description:         Quadrature Decoder Status

                        This register can be used during QDEC mode to check the status of the quadrature decoder.
    Default Value:       0x00000000

        Field:           QDIR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Direction of count during QDEC mode.

        ENUMs:
            UP:                          Up (PHA leads PHB)
            DOWN:                        Down (PHB leads PHA)
*/
#define GPTIMER_QDECSTAT_QDIR                                        0x00000001U
#define GPTIMER_QDECSTAT_QDIR_M                                      0x00000001U
#define GPTIMER_QDECSTAT_QDIR_S                                      0U
#define GPTIMER_QDECSTAT_QDIR_UP                                     0x00000000U
#define GPTIMER_QDECSTAT_QDIR_DOWN                                   0x00000001U
/*

        Field:           DBLTRANS
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Double transition

        ENUMs:
            NONE:                        Single or no transition on phase inputs.
            DBL:                         Double transition on phase inputs.
*/
#define GPTIMER_QDECSTAT_DBLTRANS                                    0x00000002U
#define GPTIMER_QDECSTAT_DBLTRANS_M                                  0x00000002U
#define GPTIMER_QDECSTAT_DBLTRANS_S                                  1U
#define GPTIMER_QDECSTAT_DBLTRANS_NONE                               0x00000000U
#define GPTIMER_QDECSTAT_DBLTRANS_DBL                                0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRGEN
    Offset name:         GPTIMER_O_IRGEN
    Relative address:    0x38
    Description:         IR Generation

                        Use this register to generate IR codes. When [CTL] = 1, an AND gate is enabled between IO output 0 in LGPT0 and IC output 0 in LGPT1. The output of the gate overrides IO output 0 in LGPT0. See [OUTCTL.*] for explanation of outputs.

                        To generate IR codes let LGPT0 generate the carrier wave on output 0. Set this output as tick input of LGPT1, with [PRECFG.TICKSRC] = FALL_TICK.
                        Generate wanted IR codes by adjusting LGPT1 [PTGT.*] and [PC0CC.*].
    Default Value:       0x00000000

        Field:           CTL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Control


        ENUMs:
            DIS:                         Disable.
            EN:                          Enable.
*/
#define GPTIMER_IRGEN_CTL                                            0x00000001U
#define GPTIMER_IRGEN_CTL_M                                          0x00000001U
#define GPTIMER_IRGEN_CTL_S                                          0U
#define GPTIMER_IRGEN_CTL_DIS                                        0x00000000U
#define GPTIMER_IRGEN_CTL_EN                                         0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMA
    Offset name:         GPTIMER_O_DMA
    Relative address:    0x3C
    Description:         Direct Memory Access

                        This register is used to enable DMA requests from the timer and set the register addresses which the DMA will access (read/write).
                        Choose DMA request source by setting the [REQ] field. The setting of the corresponding interrupt in the [RIS.*] registers also sets the DMA request.
                        Upon a DMA request defined by [REQ] an internal address pointer is set to [RWADDR]*4. Every access to [DMARW.*] will increment the internal pointer by 4 such that the next DMA access will be to the next register.
                        The internal pointer will stop after [RWCNTR] increments. Further access will be ignored.
    Default Value:       0x00000000

        Field:           REQ
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA request trigger

        ENUMs:
            DIS:                         Disabled
            FAULT:                       Setting of [RIS.FAULT] generates a DMA request.
            TGT:                         Setting of [RIS.TGT] generates a DMA request.
            ZERO:                        Setting of [RIS.ZERO] generates a DMA request.
            C0CC:                        Setting of [RIS.C0CC] generates a DMA request.
            C1CC:                        Setting of [RIS.C1CC] generates a DMA request.
            C2CC:                        Setting of [RIS.C2CC] generates a DMA request.
            C3CC:                        Setting of [RIS.C3CC] generates a DMA request.
*/
#define GPTIMER_DMA_REQ_W                                            3U
#define GPTIMER_DMA_REQ_M                                            0x00000007U
#define GPTIMER_DMA_REQ_S                                            0U
#define GPTIMER_DMA_REQ_DIS                                          0x00000000U
#define GPTIMER_DMA_REQ_FAULT                                        0x00000003U
#define GPTIMER_DMA_REQ_TGT                                          0x00000001U
#define GPTIMER_DMA_REQ_ZERO                                         0x00000002U
#define GPTIMER_DMA_REQ_C0CC                                         0x00000004U
#define GPTIMER_DMA_REQ_C1CC                                         0x00000005U
#define GPTIMER_DMA_REQ_C2CC                                         0x00000006U
#define GPTIMER_DMA_REQ_C3CC                                         0x00000007U
/*

        Field:           ADDRESS
        From..to bits:   8...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The base address which the DMA access when reading/writing [DMARW].  The base address is set by taking the 9 LSB of the physical address and divide by 4.
                         For example, if you wanted the [RWADDR] to point to the [PTGT] register you should set [RWADDR] = 0x0FC/4.

*/
#define GPTIMER_DMA_ADDRESS_W                                        7U
#define GPTIMER_DMA_ADDRESS_M                                        0x00007F00U
#define GPTIMER_DMA_ADDRESS_S                                        8U
/*

        Field:           RWC
        From..to bits:   16...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The read/write counter. RWCNTR+1 is the number of times the DMA can access (read/write) the [DMARW] register. For each DMA access to [DMARW] an internal counter is incremented, writing to the next address field. [RWADDR] + 4*[RWCNTR] is the final register address which can be accessed by the DMA.

*/
#define GPTIMER_DMA_RWC_W                                            4U
#define GPTIMER_DMA_RWC_M                                            0x000F0000U
#define GPTIMER_DMA_RWC_S                                            16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMARW
    Offset name:         GPTIMER_O_DMARW
    Relative address:    0x40
    Description:         Direct Memory Access

                        This register is used by the DMA to access (read/write) register inside this LGPT module.
                        Each access to this register will increment the internal DMA address counter. See [DMA.*] for description.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA read write value.

                         The value that is read/written from/to the registers.

*/
#define GPTIMER_DMARW_VAL_W                                          32U
#define GPTIMER_DMARW_VAL_M                                          0xFFFFFFFFU
#define GPTIMER_DMARW_VAL_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ADCTRG
    Offset name:         GPTIMER_O_ADCTRG
    Relative address:    0x44
    Description:         ADC Trigger

                        This register is used to enable ADC trigger from the timer.
                        Choose ADC trigger source by setting the [SRC] field. The setting of the corresponding interrupt in the [RIS.*] registers also sets the ADC trigger.
    Default Value:       0x00000000

        Field:           SRC
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ADC request trigger

        ENUMs:
            DIS:                         Disabled
            FAULT:                       Setting of [RIS.FAULT] generates an ADC trigger.
            TGT:                         Setting of [RIS.TGT] generates an ADC trigger.

            ZERO:                        Setting of [RIS.ZERO] generates an ADC trigger.
            C0CC:                        Setting of [RIS.C0CC] generates an ADC trigger.
            C1CC:                        Setting of [RIS.C1CC] generates an ADC trigger.
            C2CC:                        Setting of [RIS.C2CC] generates an ADC trigger.
            C3CC:                        Setting of [RIS.C3CC] generates an ADC trigger.
*/
#define GPTIMER_ADCTRG_SRC_W                                         3U
#define GPTIMER_ADCTRG_SRC_M                                         0x00000007U
#define GPTIMER_ADCTRG_SRC_S                                         0U
#define GPTIMER_ADCTRG_SRC_DIS                                       0x00000000U
#define GPTIMER_ADCTRG_SRC_FAULT                                     0x00000003U
#define GPTIMER_ADCTRG_SRC_TGT                                       0x00000001U
#define GPTIMER_ADCTRG_SRC_ZERO                                      0x00000002U
#define GPTIMER_ADCTRG_SRC_C0CC                                      0x00000004U
#define GPTIMER_ADCTRG_SRC_C1CC                                      0x00000005U
#define GPTIMER_ADCTRG_SRC_C2CC                                      0x00000006U
#define GPTIMER_ADCTRG_SRC_C3CC                                      0x00000007U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IOCTL
    Offset name:         GPTIMER_O_IOCTL
    Relative address:    0x48
    Description:         IO Controller

                        This register controls the IO outputs.
    Default Value:       0x00000000

        Field:           OUT0
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO output 0 control

                         This bit field controls IO output 0.

        ENUMs:
            NRM:                         Normal output. The IO output is not changed.
            LOW:                         Driven low. The IO output is driven low.
            HIGH:                        Driven high. The IO output is driven high.
            INV:                         Inverted value. The IO output is inverted.
*/
#define GPTIMER_IOCTL_OUT0_W                                         2U
#define GPTIMER_IOCTL_OUT0_M                                         0x00000003U
#define GPTIMER_IOCTL_OUT0_S                                         0U
#define GPTIMER_IOCTL_OUT0_NRM                                       0x00000000U
#define GPTIMER_IOCTL_OUT0_LOW                                       0x00000001U
#define GPTIMER_IOCTL_OUT0_HIGH                                      0x00000002U
#define GPTIMER_IOCTL_OUT0_INV                                       0x00000003U
/*

        Field:           COUT0
        From..to bits:   2...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO complementary output 0 control

                         This bit field controls IO complementary output 0.

        ENUMs:
            NRM:                         Normal output. The IO complementary output is not changed.
            LOW:                         Driven low. The IO complementary output is driven low.
            HIGH:                        Driven high. The IO complementary output is driven high.
            INV:                         Inverted value. The IO complementary output is inverted.
*/
#define GPTIMER_IOCTL_COUT0_W                                        2U
#define GPTIMER_IOCTL_COUT0_M                                        0x0000000CU
#define GPTIMER_IOCTL_COUT0_S                                        2U
#define GPTIMER_IOCTL_COUT0_NRM                                      0x00000000U
#define GPTIMER_IOCTL_COUT0_LOW                                      0x00000004U
#define GPTIMER_IOCTL_COUT0_HIGH                                     0x00000008U
#define GPTIMER_IOCTL_COUT0_INV                                      0x0000000CU
/*

        Field:           OUT1
        From..to bits:   4...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO output 1 control

                         This bit field controls IO output 1.

        ENUMs:
            NRM:                         Normal output. The IO output is not changed.
            LOW:                         Driven low. The IO output is driven low.
            HIGH:                        Driven high. The IO output is driven high.
            INV:                         Inverted value. The IO output is inverted.
*/
#define GPTIMER_IOCTL_OUT1_W                                         2U
#define GPTIMER_IOCTL_OUT1_M                                         0x00000030U
#define GPTIMER_IOCTL_OUT1_S                                         4U
#define GPTIMER_IOCTL_OUT1_NRM                                       0x00000000U
#define GPTIMER_IOCTL_OUT1_LOW                                       0x00000010U
#define GPTIMER_IOCTL_OUT1_HIGH                                      0x00000020U
#define GPTIMER_IOCTL_OUT1_INV                                       0x00000030U
/*

        Field:           COUT1
        From..to bits:   6...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO complementary output 1 control

                         This bit field controls IO complementary output 1.

        ENUMs:
            NRM:                         Normal output. The IO complementary output is not changed.
            LOW:                         Driven low. The IO complementary output is driven low.
            HIGH:                        Driven high. The IO complementary output is driven high.
            INV:                         Inverted value. The IO complementary output is inverted.
*/
#define GPTIMER_IOCTL_COUT1_W                                        2U
#define GPTIMER_IOCTL_COUT1_M                                        0x000000C0U
#define GPTIMER_IOCTL_COUT1_S                                        6U
#define GPTIMER_IOCTL_COUT1_NRM                                      0x00000000U
#define GPTIMER_IOCTL_COUT1_LOW                                      0x00000040U
#define GPTIMER_IOCTL_COUT1_HIGH                                     0x00000080U
#define GPTIMER_IOCTL_COUT1_INV                                      0x000000C0U
/*

        Field:           OUT2
        From..to bits:   8...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO output 2 control

                         This bit field controls IO output 2.

        ENUMs:
            NRM:                         Normal output. The IO output is not changed.
            LOW:                         Driven low. The IO output is driven low.
            HIGH:                        Driven high. The IO output is driven high.
            INV:                         Inverted value. The IO output is inverted.
*/
#define GPTIMER_IOCTL_OUT2_W                                         2U
#define GPTIMER_IOCTL_OUT2_M                                         0x00000300U
#define GPTIMER_IOCTL_OUT2_S                                         8U
#define GPTIMER_IOCTL_OUT2_NRM                                       0x00000000U
#define GPTIMER_IOCTL_OUT2_LOW                                       0x00000100U
#define GPTIMER_IOCTL_OUT2_HIGH                                      0x00000200U
#define GPTIMER_IOCTL_OUT2_INV                                       0x00000300U
/*

        Field:           COUT2
        From..to bits:   10...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO complementary output 2 control

                         This bit field controls IO complementary output 2.

        ENUMs:
            NRM:                         Normal output. The IO complementary output is not changed.
            LOW:                         Driven low. The IO complementary output is driven low.
            HIGH:                        Driven high. The IO complementary output is driven high.
            INV:                         Inverted value. The IO complementary output is inverted.
*/
#define GPTIMER_IOCTL_COUT2_W                                        2U
#define GPTIMER_IOCTL_COUT2_M                                        0x00000C00U
#define GPTIMER_IOCTL_COUT2_S                                        10U
#define GPTIMER_IOCTL_COUT2_NRM                                      0x00000000U
#define GPTIMER_IOCTL_COUT2_LOW                                      0x00000400U
#define GPTIMER_IOCTL_COUT2_HIGH                                     0x00000800U
#define GPTIMER_IOCTL_COUT2_INV                                      0x00000C00U
/*

        Field:           OUT3
        From..to bits:   12...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO output 3 control

                         This bit field controls IO output 3.

        ENUMs:
            NRM:                         Normal output. The IO output is not changed.
            LOW:                         Driven low. The IO output is driven low.
            HIGH:                        Driven high. The IO output is driven high.
            INV:                         Inverted value. The IO output is inverted.
*/
#define GPTIMER_IOCTL_OUT3_W                                         2U
#define GPTIMER_IOCTL_OUT3_M                                         0x00003000U
#define GPTIMER_IOCTL_OUT3_S                                         12U
#define GPTIMER_IOCTL_OUT3_NRM                                       0x00000000U
#define GPTIMER_IOCTL_OUT3_LOW                                       0x00001000U
#define GPTIMER_IOCTL_OUT3_HIGH                                      0x00002000U
#define GPTIMER_IOCTL_OUT3_INV                                       0x00003000U
/*

        Field:           COUT3
        From..to bits:   14...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     IO complementary output 3 control

                         This bit field controls IO complementary output 3.

        ENUMs:
            NRM:                         Normal output. The IO complementary output is not changed.
            LOW:                         Driven low. The IO complementary output is driven low.
            HIGH:                        Driven high. The IO complementary output is driven high.
            INV:                         Inverted value. The IO complementary output is inverted.
*/
#define GPTIMER_IOCTL_COUT3_W                                        2U
#define GPTIMER_IOCTL_COUT3_M                                        0x0000C000U
#define GPTIMER_IOCTL_COUT3_S                                        14U
#define GPTIMER_IOCTL_COUT3_NRM                                      0x00000000U
#define GPTIMER_IOCTL_COUT3_LOW                                      0x00004000U
#define GPTIMER_IOCTL_COUT3_HIGH                                     0x00008000U
#define GPTIMER_IOCTL_COUT3_INV                                      0x0000C000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMASK
    Offset name:         GPTIMER_O_IMASK
    Relative address:    0x68
    Description:         Interrupt mask. This register selects interrupt sources which are allowed to pass from [RIS.*] to [MIS.*] when the corresponding bit-fields are set to 1.
    Default Value:       0x00000000

        Field:           TGT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable [RIS.TGT] interrupt.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_IMASK_TGT                                            0x00000001U
#define GPTIMER_IMASK_TGT_M                                          0x00000001U
#define GPTIMER_IMASK_TGT_S                                          0U
#define GPTIMER_IMASK_TGT_DIS                                        0x00000000U
#define GPTIMER_IMASK_TGT_EN                                         0x00000001U
/*

        Field:           ZERO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable [RIS.ZERO] interrupt.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_IMASK_ZERO                                           0x00000002U
#define GPTIMER_IMASK_ZERO_M                                         0x00000002U
#define GPTIMER_IMASK_ZERO_S                                         1U
#define GPTIMER_IMASK_ZERO_DIS                                       0x00000000U
#define GPTIMER_IMASK_ZERO_EN                                        0x00000002U
/*

        Field:           DBLTRANS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable [RIS.DBLTRANS] interrupt.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_IMASK_DBLTRANS                                       0x00000004U
#define GPTIMER_IMASK_DBLTRANS_M                                     0x00000004U
#define GPTIMER_IMASK_DBLTRANS_S                                     2U
#define GPTIMER_IMASK_DBLTRANS_DIS                                   0x00000000U
#define GPTIMER_IMASK_DBLTRANS_EN                                    0x00000004U
/*

        Field:           CNTRCHNG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable [RIS.CNTRCHNG] interrupt.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_IMASK_CNTRCHNG                                       0x00000008U
#define GPTIMER_IMASK_CNTRCHNG_M                                     0x00000008U
#define GPTIMER_IMASK_CNTRCHNG_S                                     3U
#define GPTIMER_IMASK_CNTRCHNG_DIS                                   0x00000000U
#define GPTIMER_IMASK_CNTRCHNG_EN                                    0x00000008U
/*

        Field:           DIRCHNG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable [RIS.DIRCHNG] interrupt.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_IMASK_DIRCHNG                                        0x00000010U
#define GPTIMER_IMASK_DIRCHNG_M                                      0x00000010U
#define GPTIMER_IMASK_DIRCHNG_S                                      4U
#define GPTIMER_IMASK_DIRCHNG_DIS                                    0x00000000U
#define GPTIMER_IMASK_DIRCHNG_EN                                     0x00000010U
/*

        Field:           IDX
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable [RIS.IDX] interrupt.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_IMASK_IDX                                            0x00000020U
#define GPTIMER_IMASK_IDX_M                                          0x00000020U
#define GPTIMER_IMASK_IDX_S                                          5U
#define GPTIMER_IMASK_IDX_DIS                                        0x00000000U
#define GPTIMER_IMASK_IDX_EN                                         0x00000020U
/*

        Field:           FAULT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable [RIS.FAULT] interrupt.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_IMASK_FAULT                                          0x00000040U
#define GPTIMER_IMASK_FAULT_M                                        0x00000040U
#define GPTIMER_IMASK_FAULT_S                                        6U
#define GPTIMER_IMASK_FAULT_DIS                                      0x00000000U
#define GPTIMER_IMASK_FAULT_EN                                       0x00000040U
/*

        Field:           C0CC
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable [RIS.C0CC] interrupt.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_IMASK_C0CC                                           0x00000100U
#define GPTIMER_IMASK_C0CC_M                                         0x00000100U
#define GPTIMER_IMASK_C0CC_S                                         8U
#define GPTIMER_IMASK_C0CC_DIS                                       0x00000000U
#define GPTIMER_IMASK_C0CC_EN                                        0x00000100U
/*

        Field:           C1CC
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable [RIS.C1CC] interrupt.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_IMASK_C1CC                                           0x00000200U
#define GPTIMER_IMASK_C1CC_M                                         0x00000200U
#define GPTIMER_IMASK_C1CC_S                                         9U
#define GPTIMER_IMASK_C1CC_DIS                                       0x00000000U
#define GPTIMER_IMASK_C1CC_EN                                        0x00000200U
/*

        Field:           C2CC
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable [RIS.C2CC] interrupt.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_IMASK_C2CC                                           0x00000400U
#define GPTIMER_IMASK_C2CC_M                                         0x00000400U
#define GPTIMER_IMASK_C2CC_S                                         10U
#define GPTIMER_IMASK_C2CC_DIS                                       0x00000000U
#define GPTIMER_IMASK_C2CC_EN                                        0x00000400U
/*

        Field:           C3CC
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable [RIS.C3CC] interrupt.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_IMASK_C3CC                                           0x00000800U
#define GPTIMER_IMASK_C3CC_M                                         0x00000800U
#define GPTIMER_IMASK_C3CC_S                                         11U
#define GPTIMER_IMASK_C3CC_DIS                                       0x00000000U
#define GPTIMER_IMASK_C3CC_EN                                        0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RIS
    Offset name:         GPTIMER_O_RIS
    Relative address:    0x6C
    Description:         Raw interrupt status. This register reflects the state of all pending interrupts, regardless of masking. This register allows the user to implement a poll scheme. A flag set in this register can be cleared by writing 1 to the corresponding [ICLR.*] register bit.
    Default Value:       0x00000000

        Field:           TGT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status of the [TGT] interrupt. The interrupt is set when [CNTR.*] = [TGT.*].

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_RIS_TGT                                              0x00000001U
#define GPTIMER_RIS_TGT_M                                            0x00000001U
#define GPTIMER_RIS_TGT_S                                            0U
#define GPTIMER_RIS_TGT_CLR                                          0x00000000U
#define GPTIMER_RIS_TGT_SET                                          0x00000001U
/*

        Field:           ZERO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status of the [ZERO] interrupt. The interrupt is set when [CNTR.*] = 0.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_RIS_ZERO                                             0x00000002U
#define GPTIMER_RIS_ZERO_M                                           0x00000002U
#define GPTIMER_RIS_ZERO_S                                           1U
#define GPTIMER_RIS_ZERO_CLR                                         0x00000000U
#define GPTIMER_RIS_ZERO_SET                                         0x00000002U
/*

        Field:           DBLTRANS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status of the [DBLTRANS] interrupt. The interrupt is set when a double transition has happened during QDEC mode.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_RIS_DBLTRANS                                         0x00000004U
#define GPTIMER_RIS_DBLTRANS_M                                       0x00000004U
#define GPTIMER_RIS_DBLTRANS_S                                       2U
#define GPTIMER_RIS_DBLTRANS_CLR                                     0x00000000U
#define GPTIMER_RIS_DBLTRANS_SET                                     0x00000004U
/*

        Field:           CNTRCHNG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status of the [CNTRCHNG] interrupt. The interrupt is set when the counter increments or decrements.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_RIS_CNTRCHNG                                         0x00000008U
#define GPTIMER_RIS_CNTRCHNG_M                                       0x00000008U
#define GPTIMER_RIS_CNTRCHNG_S                                       3U
#define GPTIMER_RIS_CNTRCHNG_CLR                                     0x00000000U
#define GPTIMER_RIS_CNTRCHNG_SET                                     0x00000008U
/*

        Field:           DIRCHNG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status of the [DIRCHNG] interrupt. The interrupt is set when the direction of the counter changes.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_RIS_DIRCHNG                                          0x00000010U
#define GPTIMER_RIS_DIRCHNG_M                                        0x00000010U
#define GPTIMER_RIS_DIRCHNG_S                                        4U
#define GPTIMER_RIS_DIRCHNG_CLR                                      0x00000000U
#define GPTIMER_RIS_DIRCHNG_SET                                      0x00000010U
/*

        Field:           IDX
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status of the [IDX] interrupt. The interrupt is set when [IDX] is active.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_RIS_IDX                                              0x00000020U
#define GPTIMER_RIS_IDX_M                                            0x00000020U
#define GPTIMER_RIS_IDX_S                                            5U
#define GPTIMER_RIS_IDX_CLR                                          0x00000000U
#define GPTIMER_RIS_IDX_SET                                          0x00000020U
/*

        Field:           FAULT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status of the [FAULT] interrupt. The interrupt is set immediately on active fault input.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_RIS_FAULT                                            0x00000040U
#define GPTIMER_RIS_FAULT_M                                          0x00000040U
#define GPTIMER_RIS_FAULT_S                                          6U
#define GPTIMER_RIS_FAULT_CLR                                        0x00000000U
#define GPTIMER_RIS_FAULT_SET                                        0x00000040U
/*

        Field:           C0CC
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status of the [C0CC] interrupt. The interrupt is set when [C0CC] has capture or compare event.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_RIS_C0CC                                             0x00000100U
#define GPTIMER_RIS_C0CC_M                                           0x00000100U
#define GPTIMER_RIS_C0CC_S                                           8U
#define GPTIMER_RIS_C0CC_CLR                                         0x00000000U
#define GPTIMER_RIS_C0CC_SET                                         0x00000100U
/*

        Field:           C1CC
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status of the [C1CC] interrupt. The interrupt is set when [C1CC] has capture or compare event.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_RIS_C1CC                                             0x00000200U
#define GPTIMER_RIS_C1CC_M                                           0x00000200U
#define GPTIMER_RIS_C1CC_S                                           9U
#define GPTIMER_RIS_C1CC_CLR                                         0x00000000U
#define GPTIMER_RIS_C1CC_SET                                         0x00000200U
/*

        Field:           C2CC
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status of the [C2CC] interrupt. The interrupt is set when [C2CC] has capture or compare event.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_RIS_C2CC                                             0x00000400U
#define GPTIMER_RIS_C2CC_M                                           0x00000400U
#define GPTIMER_RIS_C2CC_S                                           10U
#define GPTIMER_RIS_C2CC_CLR                                         0x00000000U
#define GPTIMER_RIS_C2CC_SET                                         0x00000400U
/*

        Field:           C3CC
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status of the [C3CC] interrupt. The interrupt is set when [C3CC] has capture or compare event.

        ENUMs:
            DIS:                         Disable
            EN:                          Enable
*/
#define GPTIMER_RIS_C3CC                                             0x00000800U
#define GPTIMER_RIS_C3CC_M                                           0x00000800U
#define GPTIMER_RIS_C3CC_S                                           11U
#define GPTIMER_RIS_C3CC_DIS                                         0x00000000U
#define GPTIMER_RIS_C3CC_EN                                          0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MIS
    Offset name:         GPTIMER_O_MIS
    Relative address:    0x70
    Description:         Masked interrupt status. This register is simply a bit-wise AND of the contents of [IMASK.*] and RIS.*] registers. A flag set in this register can be cleared by writing 1 to the corresponding [ICLR.*] register bit.
    Default Value:       0x00000000

        Field:           TGT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked status of the [RIS.TGT] interrupt.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_MIS_TGT                                              0x00000001U
#define GPTIMER_MIS_TGT_M                                            0x00000001U
#define GPTIMER_MIS_TGT_S                                            0U
#define GPTIMER_MIS_TGT_CLR                                          0x00000000U
#define GPTIMER_MIS_TGT_SET                                          0x00000001U
/*

        Field:           ZERO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked status of the [RIS.ZERO] interrupt.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_MIS_ZERO                                             0x00000002U
#define GPTIMER_MIS_ZERO_M                                           0x00000002U
#define GPTIMER_MIS_ZERO_S                                           1U
#define GPTIMER_MIS_ZERO_CLR                                         0x00000000U
#define GPTIMER_MIS_ZERO_SET                                         0x00000002U
/*

        Field:           DBLTRANS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked status of the [RIS.DBLTRANS] interrupt.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_MIS_DBLTRANS                                         0x00000004U
#define GPTIMER_MIS_DBLTRANS_M                                       0x00000004U
#define GPTIMER_MIS_DBLTRANS_S                                       2U
#define GPTIMER_MIS_DBLTRANS_CLR                                     0x00000000U
#define GPTIMER_MIS_DBLTRANS_SET                                     0x00000004U
/*

        Field:           CNTRCHNG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked status of the [RIS.CNTRCHNG] interrupt.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_MIS_CNTRCHNG                                         0x00000008U
#define GPTIMER_MIS_CNTRCHNG_M                                       0x00000008U
#define GPTIMER_MIS_CNTRCHNG_S                                       3U
#define GPTIMER_MIS_CNTRCHNG_CLR                                     0x00000000U
#define GPTIMER_MIS_CNTRCHNG_SET                                     0x00000008U
/*

        Field:           DIRCHNG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked status of the [RIS.DIRCHNG] interrupt.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_MIS_DIRCHNG                                          0x00000010U
#define GPTIMER_MIS_DIRCHNG_M                                        0x00000010U
#define GPTIMER_MIS_DIRCHNG_S                                        4U
#define GPTIMER_MIS_DIRCHNG_CLR                                      0x00000000U
#define GPTIMER_MIS_DIRCHNG_SET                                      0x00000010U
/*

        Field:           IDX
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked status of the [RIS.IDX] interrupt.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_MIS_IDX                                              0x00000020U
#define GPTIMER_MIS_IDX_M                                            0x00000020U
#define GPTIMER_MIS_IDX_S                                            5U
#define GPTIMER_MIS_IDX_CLR                                          0x00000000U
#define GPTIMER_MIS_IDX_SET                                          0x00000020U
/*

        Field:           FAULT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked status of the [RIS.FAULT] interrupt.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_MIS_FAULT                                            0x00000040U
#define GPTIMER_MIS_FAULT_M                                          0x00000040U
#define GPTIMER_MIS_FAULT_S                                          6U
#define GPTIMER_MIS_FAULT_CLR                                        0x00000000U
#define GPTIMER_MIS_FAULT_SET                                        0x00000040U
/*

        Field:           C0CC
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked status of the [RIS.C0CC] interrupt.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_MIS_C0CC                                             0x00000100U
#define GPTIMER_MIS_C0CC_M                                           0x00000100U
#define GPTIMER_MIS_C0CC_S                                           8U
#define GPTIMER_MIS_C0CC_CLR                                         0x00000000U
#define GPTIMER_MIS_C0CC_SET                                         0x00000100U
/*

        Field:           C1CC
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked status of the [RIS.C1CC] interrupt.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_MIS_C1CC                                             0x00000200U
#define GPTIMER_MIS_C1CC_M                                           0x00000200U
#define GPTIMER_MIS_C1CC_S                                           9U
#define GPTIMER_MIS_C1CC_CLR                                         0x00000000U
#define GPTIMER_MIS_C1CC_SET                                         0x00000200U
/*

        Field:           C2CC
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked status of the [RIS.C2CC] interrupt.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_MIS_C2CC                                             0x00000400U
#define GPTIMER_MIS_C2CC_M                                           0x00000400U
#define GPTIMER_MIS_C2CC_S                                           10U
#define GPTIMER_MIS_C2CC_CLR                                         0x00000000U
#define GPTIMER_MIS_C2CC_SET                                         0x00000400U
/*

        Field:           C3CC
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked status of the [RIS.C3CC] interrupt.

        ENUMs:
            CLR:                         Cleared
            SET:                         Set
*/
#define GPTIMER_MIS_C3CC                                             0x00000800U
#define GPTIMER_MIS_C3CC_M                                           0x00000800U
#define GPTIMER_MIS_C3CC_S                                           11U
#define GPTIMER_MIS_C3CC_CLR                                         0x00000000U
#define GPTIMER_MIS_C3CC_SET                                         0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ISET
    Offset name:         GPTIMER_O_ISET
    Relative address:    0x74
    Description:         Interrupt set register. This register can used by software for diagnostics and safety checking purposes. Writing a 1 to a bit in this register will set the event and the corresponding [RIS.*] bit also gets set. If the corresponding [IMASK.*] bit is set, then the corresponding [MIS.*] register bit also gets set.
    Default Value:       0x00000000

        Field:           TGT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [RIS.TGT] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_ISET_TGT                                             0x00000001U
#define GPTIMER_ISET_TGT_M                                           0x00000001U
#define GPTIMER_ISET_TGT_S                                           0U
#define GPTIMER_ISET_TGT_NO_EFFECT                                   0x00000000U
#define GPTIMER_ISET_TGT_SET                                         0x00000001U
/*

        Field:           ZERO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [RIS.ZERO] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_ISET_ZERO                                            0x00000002U
#define GPTIMER_ISET_ZERO_M                                          0x00000002U
#define GPTIMER_ISET_ZERO_S                                          1U
#define GPTIMER_ISET_ZERO_NO_EFFECT                                  0x00000000U
#define GPTIMER_ISET_ZERO_SET                                        0x00000002U
/*

        Field:           DBLTRANS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [RIS.DBLTRANS] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_ISET_DBLTRANS                                        0x00000004U
#define GPTIMER_ISET_DBLTRANS_M                                      0x00000004U
#define GPTIMER_ISET_DBLTRANS_S                                      2U
#define GPTIMER_ISET_DBLTRANS_NO_EFFECT                              0x00000000U
#define GPTIMER_ISET_DBLTRANS_SET                                    0x00000004U
/*

        Field:           CNTRCHNG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [RIS.CNTRCHNG] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_ISET_CNTRCHNG                                        0x00000008U
#define GPTIMER_ISET_CNTRCHNG_M                                      0x00000008U
#define GPTIMER_ISET_CNTRCHNG_S                                      3U
#define GPTIMER_ISET_CNTRCHNG_NO_EFFECT                              0x00000000U
#define GPTIMER_ISET_CNTRCHNG_SET                                    0x00000008U
/*

        Field:           DIRCHNG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [RIS.DIRCHNG] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_ISET_DIRCHNG                                         0x00000010U
#define GPTIMER_ISET_DIRCHNG_M                                       0x00000010U
#define GPTIMER_ISET_DIRCHNG_S                                       4U
#define GPTIMER_ISET_DIRCHNG_NO_EFFECT                               0x00000000U
#define GPTIMER_ISET_DIRCHNG_SET                                     0x00000010U
/*

        Field:           IDX
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [RIS.IDX] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_ISET_IDX                                             0x00000020U
#define GPTIMER_ISET_IDX_M                                           0x00000020U
#define GPTIMER_ISET_IDX_S                                           5U
#define GPTIMER_ISET_IDX_NO_EFFECT                                   0x00000000U
#define GPTIMER_ISET_IDX_SET                                         0x00000020U
/*

        Field:           FAULT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [RIS.FAULT] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_ISET_FAULT                                           0x00000040U
#define GPTIMER_ISET_FAULT_M                                         0x00000040U
#define GPTIMER_ISET_FAULT_S                                         6U
#define GPTIMER_ISET_FAULT_NO_EFFECT                                 0x00000000U
#define GPTIMER_ISET_FAULT_SET                                       0x00000040U
/*

        Field:           C0CC
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [RIS.C0CC] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_ISET_C0CC                                            0x00000100U
#define GPTIMER_ISET_C0CC_M                                          0x00000100U
#define GPTIMER_ISET_C0CC_S                                          8U
#define GPTIMER_ISET_C0CC_NO_EFFECT                                  0x00000000U
#define GPTIMER_ISET_C0CC_SET                                        0x00000100U
/*

        Field:           C1CC
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [RIS.C1CC] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_ISET_C1CC                                            0x00000200U
#define GPTIMER_ISET_C1CC_M                                          0x00000200U
#define GPTIMER_ISET_C1CC_S                                          9U
#define GPTIMER_ISET_C1CC_NO_EFFECT                                  0x00000000U
#define GPTIMER_ISET_C1CC_SET                                        0x00000200U
/*

        Field:           C2CC
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [RIS.C2CC] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_ISET_C2CC                                            0x00000400U
#define GPTIMER_ISET_C2CC_M                                          0x00000400U
#define GPTIMER_ISET_C2CC_S                                          10U
#define GPTIMER_ISET_C2CC_NO_EFFECT                                  0x00000000U
#define GPTIMER_ISET_C2CC_SET                                        0x00000400U
/*

        Field:           C3CC
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [RIS.C3CC] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_ISET_C3CC                                            0x00000800U
#define GPTIMER_ISET_C3CC_M                                          0x00000800U
#define GPTIMER_ISET_C3CC_S                                          11U
#define GPTIMER_ISET_C3CC_NO_EFFECT                                  0x00000000U
#define GPTIMER_ISET_C3CC_SET                                        0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ICLR
    Offset name:         GPTIMER_O_ICLR
    Relative address:    0x78
    Description:         Interrupt clear register. This register allows software to clear interrupts. Writing a 1 to a bit in this register will clear the event and the corresponding [RIS.*] bit also gets cleared. If the corresponding [IMASK.*] bit is set, then the corresponding [MIS.*] register bit also gets cleared.
    Default Value:       0x00000000

        Field:           TGT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [RIS.TGT] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_ICLR_TGT                                             0x00000001U
#define GPTIMER_ICLR_TGT_M                                           0x00000001U
#define GPTIMER_ICLR_TGT_S                                           0U
#define GPTIMER_ICLR_TGT_NO_EFFECT                                   0x00000000U
#define GPTIMER_ICLR_TGT_CLR                                         0x00000001U
/*

        Field:           ZERO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [RIS.ZERO] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_ICLR_ZERO                                            0x00000002U
#define GPTIMER_ICLR_ZERO_M                                          0x00000002U
#define GPTIMER_ICLR_ZERO_S                                          1U
#define GPTIMER_ICLR_ZERO_NO_EFFECT                                  0x00000000U
#define GPTIMER_ICLR_ZERO_CLR                                        0x00000002U
/*

        Field:           DBLTRANS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [RIS.DBLTRANS] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_ICLR_DBLTRANS                                        0x00000004U
#define GPTIMER_ICLR_DBLTRANS_M                                      0x00000004U
#define GPTIMER_ICLR_DBLTRANS_S                                      2U
#define GPTIMER_ICLR_DBLTRANS_NO_EFFECT                              0x00000000U
#define GPTIMER_ICLR_DBLTRANS_CLR                                    0x00000004U
/*

        Field:           CNTRCHNG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [RIS.CNTRCHNG] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_ICLR_CNTRCHNG                                        0x00000008U
#define GPTIMER_ICLR_CNTRCHNG_M                                      0x00000008U
#define GPTIMER_ICLR_CNTRCHNG_S                                      3U
#define GPTIMER_ICLR_CNTRCHNG_NO_EFFECT                              0x00000000U
#define GPTIMER_ICLR_CNTRCHNG_CLR                                    0x00000008U
/*

        Field:           DIRCHNG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [RIS.DIRCHNG] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_ICLR_DIRCHNG                                         0x00000010U
#define GPTIMER_ICLR_DIRCHNG_M                                       0x00000010U
#define GPTIMER_ICLR_DIRCHNG_S                                       4U
#define GPTIMER_ICLR_DIRCHNG_NO_EFFECT                               0x00000000U
#define GPTIMER_ICLR_DIRCHNG_CLR                                     0x00000010U
/*

        Field:           IDX
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [RIS.IDX] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_ICLR_IDX                                             0x00000020U
#define GPTIMER_ICLR_IDX_M                                           0x00000020U
#define GPTIMER_ICLR_IDX_S                                           5U
#define GPTIMER_ICLR_IDX_NO_EFFECT                                   0x00000000U
#define GPTIMER_ICLR_IDX_CLR                                         0x00000020U
/*

        Field:           FAULT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [RIS.FAULT] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_ICLR_FAULT                                           0x00000040U
#define GPTIMER_ICLR_FAULT_M                                         0x00000040U
#define GPTIMER_ICLR_FAULT_S                                         6U
#define GPTIMER_ICLR_FAULT_NO_EFFECT                                 0x00000000U
#define GPTIMER_ICLR_FAULT_CLR                                       0x00000040U
/*

        Field:           C0CC
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [RIS.C0CC] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_ICLR_C0CC                                            0x00000100U
#define GPTIMER_ICLR_C0CC_M                                          0x00000100U
#define GPTIMER_ICLR_C0CC_S                                          8U
#define GPTIMER_ICLR_C0CC_NO_EFFECT                                  0x00000000U
#define GPTIMER_ICLR_C0CC_CLR                                        0x00000100U
/*

        Field:           C1CC
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [RIS.C1CC] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_ICLR_C1CC                                            0x00000200U
#define GPTIMER_ICLR_C1CC_M                                          0x00000200U
#define GPTIMER_ICLR_C1CC_S                                          9U
#define GPTIMER_ICLR_C1CC_NO_EFFECT                                  0x00000000U
#define GPTIMER_ICLR_C1CC_CLR                                        0x00000200U
/*

        Field:           C2CC
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [RIS.C2CC] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_ICLR_C2CC                                            0x00000400U
#define GPTIMER_ICLR_C2CC_M                                          0x00000400U
#define GPTIMER_ICLR_C2CC_S                                          10U
#define GPTIMER_ICLR_C2CC_NO_EFFECT                                  0x00000000U
#define GPTIMER_ICLR_C2CC_CLR                                        0x00000400U
/*

        Field:           C3CC
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [RIS.C3CC] interrupt.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_ICLR_C3CC                                            0x00000800U
#define GPTIMER_ICLR_C3CC_M                                          0x00000800U
#define GPTIMER_ICLR_C3CC_S                                          11U
#define GPTIMER_ICLR_C3CC_NO_EFFECT                                  0x00000000U
#define GPTIMER_ICLR_C3CC_CLR                                        0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMSET
    Offset name:         GPTIMER_O_IMSET
    Relative address:    0x7C
    Description:         Interrupt mask set register. Writing a 1 to a bit in this register will set the corresponding [IMASK.*] bit.
    Default Value:       0x00000000

        Field:           TGT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [MIS.TGT] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_IMSET_TGT                                            0x00000001U
#define GPTIMER_IMSET_TGT_M                                          0x00000001U
#define GPTIMER_IMSET_TGT_S                                          0U
#define GPTIMER_IMSET_TGT_NO_EFFECT                                  0x00000000U
#define GPTIMER_IMSET_TGT_SET                                        0x00000001U
/*

        Field:           ZERO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [MIS.ZERO] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_IMSET_ZERO                                           0x00000002U
#define GPTIMER_IMSET_ZERO_M                                         0x00000002U
#define GPTIMER_IMSET_ZERO_S                                         1U
#define GPTIMER_IMSET_ZERO_NO_EFFECT                                 0x00000000U
#define GPTIMER_IMSET_ZERO_SET                                       0x00000002U
/*

        Field:           DBLTRANS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [MIS.DBLTRANS] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_IMSET_DBLTRANS                                       0x00000004U
#define GPTIMER_IMSET_DBLTRANS_M                                     0x00000004U
#define GPTIMER_IMSET_DBLTRANS_S                                     2U
#define GPTIMER_IMSET_DBLTRANS_NO_EFFECT                             0x00000000U
#define GPTIMER_IMSET_DBLTRANS_SET                                   0x00000004U
/*

        Field:           CNTRCHNG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [MIS.CNTRCHNG] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_IMSET_CNTRCHNG                                       0x00000008U
#define GPTIMER_IMSET_CNTRCHNG_M                                     0x00000008U
#define GPTIMER_IMSET_CNTRCHNG_S                                     3U
#define GPTIMER_IMSET_CNTRCHNG_NO_EFFECT                             0x00000000U
#define GPTIMER_IMSET_CNTRCHNG_SET                                   0x00000008U
/*

        Field:           DIRCHNG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [MIS.DIRCHNG] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_IMSET_DIRCHNG                                        0x00000010U
#define GPTIMER_IMSET_DIRCHNG_M                                      0x00000010U
#define GPTIMER_IMSET_DIRCHNG_S                                      4U
#define GPTIMER_IMSET_DIRCHNG_NO_EFFECT                              0x00000000U
#define GPTIMER_IMSET_DIRCHNG_SET                                    0x00000010U
/*

        Field:           IDX
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [MIS.IDX] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_IMSET_IDX                                            0x00000020U
#define GPTIMER_IMSET_IDX_M                                          0x00000020U
#define GPTIMER_IMSET_IDX_S                                          5U
#define GPTIMER_IMSET_IDX_NO_EFFECT                                  0x00000000U
#define GPTIMER_IMSET_IDX_SET                                        0x00000020U
/*

        Field:           FAULT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [MIS.FAULT] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_IMSET_FAULT                                          0x00000040U
#define GPTIMER_IMSET_FAULT_M                                        0x00000040U
#define GPTIMER_IMSET_FAULT_S                                        6U
#define GPTIMER_IMSET_FAULT_NO_EFFECT                                0x00000000U
#define GPTIMER_IMSET_FAULT_SET                                      0x00000040U
/*

        Field:           C0CC
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [MIS.C0CC] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_IMSET_C0CC                                           0x00000100U
#define GPTIMER_IMSET_C0CC_M                                         0x00000100U
#define GPTIMER_IMSET_C0CC_S                                         8U
#define GPTIMER_IMSET_C0CC_NO_EFFECT                                 0x00000000U
#define GPTIMER_IMSET_C0CC_SET                                       0x00000100U
/*

        Field:           C1CC
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [MIS.C1CC] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_IMSET_C1CC                                           0x00000200U
#define GPTIMER_IMSET_C1CC_M                                         0x00000200U
#define GPTIMER_IMSET_C1CC_S                                         9U
#define GPTIMER_IMSET_C1CC_NO_EFFECT                                 0x00000000U
#define GPTIMER_IMSET_C1CC_SET                                       0x00000200U
/*

        Field:           C2CC
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [MIS.C2CC] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_IMSET_C2CC                                           0x00000400U
#define GPTIMER_IMSET_C2CC_M                                         0x00000400U
#define GPTIMER_IMSET_C2CC_S                                         10U
#define GPTIMER_IMSET_C2CC_NO_EFFECT                                 0x00000000U
#define GPTIMER_IMSET_C2CC_SET                                       0x00000400U
/*

        Field:           C3CC
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set the [MIS.C3CC] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            SET:                         Set
*/
#define GPTIMER_IMSET_C3CC                                           0x00000800U
#define GPTIMER_IMSET_C3CC_M                                         0x00000800U
#define GPTIMER_IMSET_C3CC_S                                         11U
#define GPTIMER_IMSET_C3CC_NO_EFFECT                                 0x00000000U
#define GPTIMER_IMSET_C3CC_SET                                       0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMCLR
    Offset name:         GPTIMER_O_IMCLR
    Relative address:    0x80
    Description:         Interrupt mask clear register. Writing a 1 to a bit in this register will clear the corresponding [IMASK.*] bit.
    Default Value:       0x00000000

        Field:           TGT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [MIS.TGT] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_IMCLR_TGT                                            0x00000001U
#define GPTIMER_IMCLR_TGT_M                                          0x00000001U
#define GPTIMER_IMCLR_TGT_S                                          0U
#define GPTIMER_IMCLR_TGT_NO_EFFECT                                  0x00000000U
#define GPTIMER_IMCLR_TGT_CLR                                        0x00000001U
/*

        Field:           ZERO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [MIS.ZERO] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_IMCLR_ZERO                                           0x00000002U
#define GPTIMER_IMCLR_ZERO_M                                         0x00000002U
#define GPTIMER_IMCLR_ZERO_S                                         1U
#define GPTIMER_IMCLR_ZERO_NO_EFFECT                                 0x00000000U
#define GPTIMER_IMCLR_ZERO_CLR                                       0x00000002U
/*

        Field:           DBLTRANS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [MIS.DBLTRANS] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_IMCLR_DBLTRANS                                       0x00000004U
#define GPTIMER_IMCLR_DBLTRANS_M                                     0x00000004U
#define GPTIMER_IMCLR_DBLTRANS_S                                     2U
#define GPTIMER_IMCLR_DBLTRANS_NO_EFFECT                             0x00000000U
#define GPTIMER_IMCLR_DBLTRANS_CLR                                   0x00000004U
/*

        Field:           CNTRCHNG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [MIS.CNTRCHNG] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_IMCLR_CNTRCHNG                                       0x00000008U
#define GPTIMER_IMCLR_CNTRCHNG_M                                     0x00000008U
#define GPTIMER_IMCLR_CNTRCHNG_S                                     3U
#define GPTIMER_IMCLR_CNTRCHNG_NO_EFFECT                             0x00000000U
#define GPTIMER_IMCLR_CNTRCHNG_CLR                                   0x00000008U
/*

        Field:           DIRCHNG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [MIS.DIRCHNG] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_IMCLR_DIRCHNG                                        0x00000010U
#define GPTIMER_IMCLR_DIRCHNG_M                                      0x00000010U
#define GPTIMER_IMCLR_DIRCHNG_S                                      4U
#define GPTIMER_IMCLR_DIRCHNG_NO_EFFECT                              0x00000000U
#define GPTIMER_IMCLR_DIRCHNG_CLR                                    0x00000010U
/*

        Field:           IDX
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [MIS.IDX] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_IMCLR_IDX                                            0x00000020U
#define GPTIMER_IMCLR_IDX_M                                          0x00000020U
#define GPTIMER_IMCLR_IDX_S                                          5U
#define GPTIMER_IMCLR_IDX_NO_EFFECT                                  0x00000000U
#define GPTIMER_IMCLR_IDX_CLR                                        0x00000020U
/*

        Field:           FAULT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [MIS.FAULT] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_IMCLR_FAULT                                          0x00000040U
#define GPTIMER_IMCLR_FAULT_M                                        0x00000040U
#define GPTIMER_IMCLR_FAULT_S                                        6U
#define GPTIMER_IMCLR_FAULT_NO_EFFECT                                0x00000000U
#define GPTIMER_IMCLR_FAULT_CLR                                      0x00000040U
/*

        Field:           C0CC
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [MIS.C0CC] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_IMCLR_C0CC                                           0x00000100U
#define GPTIMER_IMCLR_C0CC_M                                         0x00000100U
#define GPTIMER_IMCLR_C0CC_S                                         8U
#define GPTIMER_IMCLR_C0CC_NO_EFFECT                                 0x00000000U
#define GPTIMER_IMCLR_C0CC_CLR                                       0x00000100U
/*

        Field:           C1CC
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [MIS.C1CC] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_IMCLR_C1CC                                           0x00000200U
#define GPTIMER_IMCLR_C1CC_M                                         0x00000200U
#define GPTIMER_IMCLR_C1CC_S                                         9U
#define GPTIMER_IMCLR_C1CC_NO_EFFECT                                 0x00000000U
#define GPTIMER_IMCLR_C1CC_CLR                                       0x00000200U
/*

        Field:           C2CC
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [MIS.C2CC] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_IMCLR_C2CC                                           0x00000400U
#define GPTIMER_IMCLR_C2CC_M                                         0x00000400U
#define GPTIMER_IMCLR_C2CC_S                                         10U
#define GPTIMER_IMCLR_C2CC_NO_EFFECT                                 0x00000000U
#define GPTIMER_IMCLR_C2CC_CLR                                       0x00000400U
/*

        Field:           C3CC
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear the [MIS.C3CC] mask.

        ENUMs:
            NO_EFFECT:                   No effect
            CLR:                         Clear
*/
#define GPTIMER_IMCLR_C3CC                                           0x00000800U
#define GPTIMER_IMCLR_C3CC_M                                         0x00000800U
#define GPTIMER_IMCLR_C3CC_S                                         11U
#define GPTIMER_IMCLR_C3CC_NO_EFFECT                                 0x00000000U
#define GPTIMER_IMCLR_C3CC_CLR                                       0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EMU
    Offset name:         GPTIMER_O_EMU
    Relative address:    0x84
    Description:         Debug control

                        This register can be used to freeze the timer when CPU halts when [HALT] is set to 1. When [HALT] is set to 0, or when the CPU releases debug halt, the filters and edge detection logic is flushed and the timer starts. For setting a predefined output value during a CPU debug halt, [PARK.*], if the timer has this register, should be configured additionally. If this timer does not have the [PARK.*] register a predefined output value during CPU halt is not possible.
    Default Value:       0x00000000

        Field:           HALT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Halt LGPT when CPU is halted in debug.

        ENUMs:
            DIS:                         Disable.
            EN:                          Enable.
*/
#define GPTIMER_EMU_HALT                                             0x00000001U
#define GPTIMER_EMU_HALT_M                                           0x00000001U
#define GPTIMER_EMU_HALT_S                                           0U
#define GPTIMER_EMU_HALT_DIS                                         0x00000000U
#define GPTIMER_EMU_HALT_EN                                          0x00000001U
/*

        Field:           CTL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Halt control.

                         Configure when the counter shall stop upon CPU halt. This bitfield only applies if [HALT] = 1.

        ENUMs:
            IMMEDIATE:                   Immediate reaction. The counter stops immediately on debug halt.
            ZERCOND:                     Zero condition. The counter stops when [CNTR.*] = 0.
*/
#define GPTIMER_EMU_CTL                                              0x00000002U
#define GPTIMER_EMU_CTL_M                                            0x00000002U
#define GPTIMER_EMU_CTL_S                                            1U
#define GPTIMER_EMU_CTL_IMMEDIATE                                    0x00000000U
#define GPTIMER_EMU_CTL_ZERCOND                                      0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C0CFG
    Offset name:         GPTIMER_O_C0CFG
    Relative address:    0xC0
    Description:         Channel 0 Configuration

                        This register configures channel function and enables outputs.

                        Each channel has an edge-detection circuit. The the edge-detection circuit is:
                         - enabled while [CCACT] selects a capture function and [CTL.MODE] is different from DIS.
                         - flushed while [CCACT] selects a capture function and [CTL.MODE] is changed from DIS to another mode.

                        The flush action uses two system clock periods. It prevents capture events caused by expired signal values stored in the edge-detection circuit.

                        The channel input signal enters the edge-detection circuit. False capture events can occur when:
                        - the edge-detection circuit contains expired signal samples and the circuit is enabled without flush as described above.
                        - the [CCACT] field is reconfigured while CTL.MODE is different from DIS.

                        Primary use scenario is to select [CCACT] before starting the timer. Follow these steps to configure [CCACT] to a capture action while [CTL.MODE] is different from DIS:
                        - Set [EDGE] to NONE.
                        - Configure [CCACT].
                        - Wait for three system clock periods before setting [EDGE] different from NONE.
                        These steps prevent capture events caused by expired signal values in edge-detection circuit.
    Default Value:       0x00000000

        Field:           CCACT
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture-Compare action.

                         Capture-Compare action defines 15 different channel functions that utilize capture, compare, and zero events. In every compare event the timer looks at the current value of [CNTR.*]. The corresponding output event will be set 1 timer period after [CNTR.*] = [C0CC.*].

        ENUMs:
            DIS:                         Disable channel.
            SET_ON_CAPT_DIS:             Set on capture, and then disable channel.

                         Channel function sequence:
                         - Set enabled outputs on capture event and copy [CNTR.VAL] to [C0CC.VAL].
                         - Disable channel.

                         Primary use scenario is to select this function before starting the timer.
                         Follow these steps to select this function while [CTL.MODE] is different from DIS:
                          - Set CCACT to SET_ON_CAPT with no output enable.
                          - Configure [INPUT] (optional).
                          - Wait for three timer clock periods as defined in [PRECFG.*] before setting CCACT to SET_ON_CAPT_DIS. Output enable is optional.

                         These steps prevent capture events caused by expired signal values in edge-detection circuit.
            CLR_ON_0_TGL_ON_CMP:         Clear on zero, toggle on compare repeatedly.

                         Channel function sequence:
                         - Clear enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C0CC.VAL] = [CNTR.VAL].

                         Set [CTL.MODE] to UPDWN_PER for center-aligned PWM generation. Duty cycle is given by:

                         When [C0CC.VAL] <= [TGT.VAL]:
                            Duty cycle = 1 - ( [C0CC.VAL] / [TGT.VAL] ).

                         When [C0CC.VAL] > [TGT.VAL]:
                            Duty cycle = 0.

                         Enabled outputs are set when [C0CC.VAL] = 0 and [CNTR.VAL] = 0.
            SET_ON_0_TGL_ON_CMP:         Set on zero, toggle on compare repeatedly.

                         Channel function sequence:
                         - Set enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C0CC.VAL] = [CNTR.VAL].

                         Set [CTL.MODE] to UP_PER for edge-aligned PWM generation. Duty cycle is given by:

                         When [C0CC.VAL] <= [TGT.VAL]:
                            Duty cycle = [C0CC.VAL] / ( [TGT.VAL] + 1 ).

                         When [C0CC.VAL] > [TGT.VAL]:
                            Duty cycle = 1.

                         Enabled outputs are cleared when [C0CC.VAL] = 0 and [CNTR.VAL] = 0.
            CLR_ON_CMP:                  Clear on compare repeatedly.

                         Channel function sequence:
                         - Clear enabled outputs  when [C0CC.VAL] = [CNTR.VAL].
            SET_ON_CMP:                  Set on compare repeatedly.

                         Channel function sequence:
                         - Set enabled outputs  when [C0CC.VAL] = [CNTR.VAL].
            TGL_ON_CMP:                  Toggle on compare repeatedly.

                         Channel function sequence:
                         - Toggle enabled outputs  when [C0CC.VAL] = [CNTR.VAL].
            PULSE_ON_CMP:                Pulse on compare repeatedly.

                         Channel function sequence:
                         - Pulse enabled outputs when [C0CC.VAL] = [CNTR.VAL].

                          The output is high for two timer clock periods.
            CLR_ON_0_TGL_ON_CMP_DIS:     Clear on zero, toggle on compare, and then disable channel.

                         Channel function sequence:
                         - Clear enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C0CC.VAL] = [CNTR.VAL].
                         - Disable channel.

                         Enabled outputs are set when [C0CC.VAL] = 0 and [CNTR.VAL] = 0.
            SET_ON_0_TGL_ON_CMP_DIS:     Set on zero, toggle on compare, and then disable channel.

                         Channel function sequence:
                         - Set enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C0CC.VAL] = [CNTR.VAL].
                         - Disable channel.

                         Enabled outputs are cleared when [C0CC.VAL] = 0 and [CNTR.VAL] = 0.
            CLR_ON_CMP_DIS:              Clear on compare, and then disable channel.

                         Channel function sequence:
                         - Clear enabled outputs when [C0CC.VAL] = [CNTR.VAL].
                         - Disable channel.
            SET_ON_CMP_DIS:              Set on compare, and then disable channel.

                         Channel function sequence:
                         - Set enabled outputs when [C0CC.VAL] = [CNTR.VAL].
                         - Disable channel.
            TGL_ON_CMP_DIS:              Toggle on compare, and then disable channel.

                         Channel function sequence:
                         - Toggle enabled outputs when [C0CC.VAL] = [CNTR.VAL].
                         - Disable channel.
            PULSE_ON_CMP_DIS:            Pulse on compare, and then disable channel.

                         Channel function sequence:
                         - Pulse enabled outputs when [C0CC.VAL] = [CNTR.VAL].
                         - Disable channel.

                          The output is high for two timer clock periods.
            PER_PULSE_WIDTH_MEAS:        Period and pulse width measurement.

                         Continuously capture period and pulse width of the signal selected by [INPUT] relative to the signal edge given by [EDGE].

                         Set enabled outputs and [RIS.C0CC] when [C0CC.VAL] contains signal period and [PC0CC.VAL] contains signal pulse width.

                         Notes:
                         - Make sure to configure [INPUT] and CCACT when [CTL.MODE] equals DIS, then set [CTL.MODE] to UP_ONCE or UP_PER.
                         - The counter restarts in the selected timer mode when [C0CC.VAL] contains the signal period.
                         - If more than one channel uses this function, the channels will perform this function one at a time. The channel with lowest number has priority and performs the function first. Next measurement starts when current measurement completes successfully or times out. A timeout occurs when counter equals target.
                         - To observe a timeout event the [RIS.TGT] interrupt can be used, or another channel can be configured to SET_ON_CMP with compare value equal [TGT].

                         Signal property requirements:
                         - Signal Period >= 2 * ( 1 + [PRECFG.TICKDIV] ) * timer clock period.
                         - Signal Period <= MAX([CNTR.*]) * (1 + [PRECFG.TICKDIV] ) * timer clock period.
                         - Signal low and high phase >= (1 + [PRECFG.TICKDIV] ) * timer clock period.
            SET_ON_CAPT:                 Set on capture repeatedly.

                         Channel function sequence:
                         - Set enabled outputs on capture event and copy [CNTR.VAL] to [C0CC.VAL].
*/
#define GPTIMER_C0CFG_CCACT_W                                        4U
#define GPTIMER_C0CFG_CCACT_M                                        0x0000000FU
#define GPTIMER_C0CFG_CCACT_S                                        0U
#define GPTIMER_C0CFG_CCACT_DIS                                      0x00000000U
#define GPTIMER_C0CFG_CCACT_SET_ON_CAPT_DIS                          0x00000001U
#define GPTIMER_C0CFG_CCACT_CLR_ON_0_TGL_ON_CMP                      0x0000000AU
#define GPTIMER_C0CFG_CCACT_SET_ON_0_TGL_ON_CMP                      0x0000000BU
#define GPTIMER_C0CFG_CCACT_CLR_ON_CMP                               0x0000000CU
#define GPTIMER_C0CFG_CCACT_SET_ON_CMP                               0x0000000DU
#define GPTIMER_C0CFG_CCACT_TGL_ON_CMP                               0x0000000EU
#define GPTIMER_C0CFG_CCACT_PULSE_ON_CMP                             0x0000000FU
#define GPTIMER_C0CFG_CCACT_CLR_ON_0_TGL_ON_CMP_DIS                  0x00000002U
#define GPTIMER_C0CFG_CCACT_SET_ON_0_TGL_ON_CMP_DIS                  0x00000003U
#define GPTIMER_C0CFG_CCACT_CLR_ON_CMP_DIS                           0x00000004U
#define GPTIMER_C0CFG_CCACT_SET_ON_CMP_DIS                           0x00000005U
#define GPTIMER_C0CFG_CCACT_TGL_ON_CMP_DIS                           0x00000006U
#define GPTIMER_C0CFG_CCACT_PULSE_ON_CMP_DIS                         0x00000007U
#define GPTIMER_C0CFG_CCACT_PER_PULSE_WIDTH_MEAS                     0x00000008U
#define GPTIMER_C0CFG_CCACT_SET_ON_CAPT                              0x00000009U
/*

        Field:           EDGE
        From..to bits:   4...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Determines the edge that triggers the channel input event. This happens post filter.

        ENUMs:
            NONE:                        Input is turned off.
            RISE:                        Input event is triggered at rising edge.
            FALL:                        Input event is triggered at falling edge.
            BOTH:                        Input event is triggered at both edges.
*/
#define GPTIMER_C0CFG_EDGE_W                                         2U
#define GPTIMER_C0CFG_EDGE_M                                         0x00000030U
#define GPTIMER_C0CFG_EDGE_S                                         4U
#define GPTIMER_C0CFG_EDGE_NONE                                      0x00000000U
#define GPTIMER_C0CFG_EDGE_RISE                                      0x00000010U
#define GPTIMER_C0CFG_EDGE_FALL                                      0x00000020U
#define GPTIMER_C0CFG_EDGE_BOTH                                      0x00000030U
/*

        Field:           INPUT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Select channel input.

        ENUMs:
            EV:                          Event fabric
            IO:                          IO controller
*/
#define GPTIMER_C0CFG_INPUT                                          0x00000040U
#define GPTIMER_C0CFG_INPUT_M                                        0x00000040U
#define GPTIMER_C0CFG_INPUT_S                                        6U
#define GPTIMER_C0CFG_INPUT_EV                                       0x00000000U
#define GPTIMER_C0CFG_INPUT_IO                                       0x00000040U
/*

        Field:           OUT0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 0 enable.

                         When 0 < [CCACT] < 8, OUT0 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 0 does not control output 0.
            EN:                          Channel 0 controls output 0.
*/
#define GPTIMER_C0CFG_OUT0                                           0x00000100U
#define GPTIMER_C0CFG_OUT0_M                                         0x00000100U
#define GPTIMER_C0CFG_OUT0_S                                         8U
#define GPTIMER_C0CFG_OUT0_DIS                                       0x00000000U
#define GPTIMER_C0CFG_OUT0_EN                                        0x00000100U
/*

        Field:           OUT1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 1 enable.

                         When 0 < [CCACT] < 8, OUT1 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 0 does not control output 1.
            EN:                          Channel 0 controls output 1.
*/
#define GPTIMER_C0CFG_OUT1                                           0x00000200U
#define GPTIMER_C0CFG_OUT1_M                                         0x00000200U
#define GPTIMER_C0CFG_OUT1_S                                         9U
#define GPTIMER_C0CFG_OUT1_DIS                                       0x00000000U
#define GPTIMER_C0CFG_OUT1_EN                                        0x00000200U
/*

        Field:           OUT2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 2 enable.

                         When 0 < [CCACT] < 8, OUT2 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 0 does not control output 2.
            EN:                          Channel 0 controls output 2.
*/
#define GPTIMER_C0CFG_OUT2                                           0x00000400U
#define GPTIMER_C0CFG_OUT2_M                                         0x00000400U
#define GPTIMER_C0CFG_OUT2_S                                         10U
#define GPTIMER_C0CFG_OUT2_DIS                                       0x00000000U
#define GPTIMER_C0CFG_OUT2_EN                                        0x00000400U
/*

        Field:           OUT3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 3 enable.

                         When 0 < [CCACT] < 8, OUT3 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 0 does not control output 3.
            EN:                          Channel 0 controls output 3.
*/
#define GPTIMER_C0CFG_OUT3                                           0x00000800U
#define GPTIMER_C0CFG_OUT3_M                                         0x00000800U
#define GPTIMER_C0CFG_OUT3_S                                         11U
#define GPTIMER_C0CFG_OUT3_DIS                                       0x00000000U
#define GPTIMER_C0CFG_OUT3_EN                                        0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C1CFG
    Offset name:         GPTIMER_O_C1CFG
    Relative address:    0xC4
    Description:         Channel 1 Configuration

                        This register configures channel function and enables outputs.

                        Each channel has an edge-detection circuit. The the edge-detection circuit is:
                         - enabled while [CCACT] selects a capture function and [CTL.MODE] is different from DIS.
                         - flushed while [CCACT] selects a capture function and [CTL.MODE] is changed from DIS to another mode.

                        The flush action uses two system clock periods. It prevents capture events caused by expired signal values stored in the edge-detection circuit.

                        The channel input signal enters the edge-detection circuit. False capture events can occur when:
                        - the edge-detection circuit contains expired signal samples and the circuit is enabled without flush as described above.
                        - the [CCACT] field is reconfigured while CTL.MODE is different from DIS.

                        Primary use scenario is to select [CCACT] before starting the timer. Follow these steps to configure [CCACT] to a capture action while [CTL.MODE] is different from DIS:
                        - Set [EDGE] to NONE.
                        - Configure [CCACT].
                        - Wait for three system clock periods before setting [EDGE] different from NONE.
                        These steps prevent capture events caused by expired signal values in edge-detection circuit.
    Default Value:       0x00000000

        Field:           CCACT
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture-Compare action.

                         Capture-Compare action defines 15 different channel functions that utilize capture, compare, and zero events. In every compare event the timer looks at the current value of [CNTR.*]. The corresponding output event will be set 1 timer period after [CNTR.*] = [C1CC.*].

        ENUMs:
            DIS:                         Disable channel.
            SET_ON_CAPT_DIS:             Set on capture, and then disable channel.

                         Channel function sequence:
                         - Set enabled outputs on capture event and copy [CNTR.VAL] to [C1CC.VAL].
                         - Disable channel.

                         Primary use scenario is to select this function before starting the timer.
                         Follow these steps to select this function while [CTL.MODE] is different from DIS:
                          - Set CCACT to SET_ON_CAPT with no output enable.
                          - Configure [INPUT] (optional).
                          - Wait for three timer clock periods as defined in [PRECFG.*] before setting CCACT to SET_ON_CAPT_DIS. Output enable is optional.

                         These steps prevent capture events caused by expired signal values in edge-detection circuit.
            CLR_ON_0_TGL_ON_CMP:         Clear on zero, toggle on compare repeatedly.

                         Channel function sequence:
                         - Clear enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C1CC.VAL] = [CNTR.VAL].

                         Set [CTL.MODE] to UPDWN_PER for center-aligned PWM generation. Duty cycle is given by:

                         When [C1CC.VAL] <= [TGT.VAL]:
                            Duty cycle = 1 - ( [C1CC.VAL] / [TGT.VAL] ).

                         When [C1CC.VAL] > [TGT.VAL]:
                            Duty cycle = 0.

                         Enabled outputs are set when [C1CC.VAL] = 0 and [CNTR.VAL] = 0.
            SET_ON_0_TGL_ON_CMP:         Set on zero, toggle on compare repeatedly.

                         Channel function sequence:
                         - Set enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C1CC.VAL] = [CNTR.VAL].

                         Set [CTL.MODE] to UP_PER for edge-aligned PWM generation. Duty cycle is given by:

                         When [C1CC.VAL] <= [TGT.VAL]:
                            Duty cycle = [C1CC.VAL] / ( [TGT.VAL] + 1 ).

                         When [C1CC.VAL] > [TGT.VAL]:
                            Duty cycle = 1.

                         Enabled outputs are cleared when [C1CC.VAL] = 0 and [CNTR.VAL] = 0.
            CLR_ON_CMP:                  Clear on compare repeatedly.

                         Channel function sequence:
                         - Clear enabled outputs  when [C1CC.VAL] = [CNTR.VAL].
            SET_ON_CMP:                  Set on compare repeatedly.

                         Channel function sequence:
                         - Set enabled outputs  when [C1CC.VAL] = [CNTR.VAL].
            TGL_ON_CMP:                  Toggle on compare repeatedly.

                         Channel function sequence:
                         - Toggle enabled outputs  when [C1CC.VAL] = [CNTR.VAL].
            PULSE_ON_CMP:                Pulse on compare repeatedly.

                         Channel function sequence:
                         - Pulse enabled outputs when [C1CC.VAL] = [CNTR.VAL].

                          The output is high for two timer clock periods.
            CLR_ON_0_TGL_ON_CMP_DIS:     Clear on zero, toggle on compare, and then disable channel.

                         Channel function sequence:
                         - Clear enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C1CC.VAL] = [CNTR.VAL].
                         - Disable channel.

                         Enabled outputs are set when [C1CC.VAL] = 0 and [CNTR.VAL] = 0.
            SET_ON_0_TGL_ON_CMP_DIS:     Set on zero, toggle on compare, and then disable channel.

                         Channel function sequence:
                         - Set enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C1CC.VAL] = [CNTR.VAL].
                         - Disable channel.

                         Enabled outputs are cleared when [C1CC.VAL] = 0 and [CNTR.VAL] = 0.
            CLR_ON_CMP_DIS:              Clear on compare, and then disable channel.

                         Channel function sequence:
                         - Clear enabled outputs when [C1CC.VAL] = [CNTR.VAL].
                         - Disable channel.
            SET_ON_CMP_DIS:              Set on compare, and then disable channel.

                         Channel function sequence:
                         - Set enabled outputs when [C1CC.VAL] = [CNTR.VAL].
                         - Disable channel.
            TGL_ON_CMP_DIS:              Toggle on compare, and then disable channel.

                         Channel function sequence:
                         - Toggle enabled outputs when [C1CC.VAL] = [CNTR.VAL].
                         - Disable channel.
            PULSE_ON_CMP_DIS:            Pulse on compare, and then disable channel.

                         Channel function sequence:
                         - Pulse enabled outputs when [C1CC.VAL] = [CNTR.VAL].
                         - Disable channel.

                          The output is high for two timer clock periods.
            PER_PULSE_WIDTH_MEAS:        Period and pulse width measurement.

                         Continuously capture period and pulse width of the signal selected by [INPUT] relative to the signal edge given by [EDGE].

                         Set enabled outputs and [RIS.C1CC] when [C1CC.VAL] contains signal period and [PC1CC.VAL] contains signal pulse width.

                         Notes:
                         - Make sure to configure [INPUT] and CCACT when [CTL.MODE] equals DIS, then set [CTL.MODE] to UP_ONCE or UP_PER.
                         - The counter restarts in the selected timer mode when [C1CC.VAL] contains the signal period.
                         - If more than one channel uses this function, the channels will perform this function one at a time. The channel with lowest number has priority and performs the function first. Next measurement starts when current measurement completes successfully or times out. A timeout occurs when counter equals target.
                         - To observe a timeout event the [RIS.TGT] interrupt can be used, or another channel can be configured to SET_ON_CMP with compare value equal [TGT].

                         Signal property requirements:
                         - Signal Period >= 2 * ( 1 + [PRECFG.TICKDIV] ) * timer clock period.
                         - Signal Period <= MAX([CNTR.*]) * (1 + [PRECFG.TICKDIV] ) * timer clock period.
                         - Signal low and high phase >= (1 + [PRECFG.TICKDIV] ) * timer clock period.
            SET_ON_CAPT:                 Set on capture repeatedly.

                         Channel function sequence:
                         - Set enabled outputs on capture event and copy [CNTR.VAL] to [C1CC.VAL].


*/
#define GPTIMER_C1CFG_CCACT_W                                        4U
#define GPTIMER_C1CFG_CCACT_M                                        0x0000000FU
#define GPTIMER_C1CFG_CCACT_S                                        0U
#define GPTIMER_C1CFG_CCACT_DIS                                      0x00000000U
#define GPTIMER_C1CFG_CCACT_SET_ON_CAPT_DIS                          0x00000001U
#define GPTIMER_C1CFG_CCACT_CLR_ON_0_TGL_ON_CMP                      0x0000000AU
#define GPTIMER_C1CFG_CCACT_SET_ON_0_TGL_ON_CMP                      0x0000000BU
#define GPTIMER_C1CFG_CCACT_CLR_ON_CMP                               0x0000000CU
#define GPTIMER_C1CFG_CCACT_SET_ON_CMP                               0x0000000DU
#define GPTIMER_C1CFG_CCACT_TGL_ON_CMP                               0x0000000EU
#define GPTIMER_C1CFG_CCACT_PULSE_ON_CMP                             0x0000000FU
#define GPTIMER_C1CFG_CCACT_CLR_ON_0_TGL_ON_CMP_DIS                  0x00000002U
#define GPTIMER_C1CFG_CCACT_SET_ON_0_TGL_ON_CMP_DIS                  0x00000003U
#define GPTIMER_C1CFG_CCACT_CLR_ON_CMP_DIS                           0x00000004U
#define GPTIMER_C1CFG_CCACT_SET_ON_CMP_DIS                           0x00000005U
#define GPTIMER_C1CFG_CCACT_TGL_ON_CMP_DIS                           0x00000006U
#define GPTIMER_C1CFG_CCACT_PULSE_ON_CMP_DIS                         0x00000007U
#define GPTIMER_C1CFG_CCACT_PER_PULSE_WIDTH_MEAS                     0x00000008U
#define GPTIMER_C1CFG_CCACT_SET_ON_CAPT                              0x00000009U
/*

        Field:           EDGE
        From..to bits:   4...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Determines the edge that triggers the channel input event. This happens post filter.

        ENUMs:
            NONE:                        Input is turned off.
            RISE:                        Input event is triggered at rising edge.
            FALL:                        Input event is triggered at falling edge.
            BOTH:                        Input event is triggered at both edges.
*/
#define GPTIMER_C1CFG_EDGE_W                                         2U
#define GPTIMER_C1CFG_EDGE_M                                         0x00000030U
#define GPTIMER_C1CFG_EDGE_S                                         4U
#define GPTIMER_C1CFG_EDGE_NONE                                      0x00000000U
#define GPTIMER_C1CFG_EDGE_RISE                                      0x00000010U
#define GPTIMER_C1CFG_EDGE_FALL                                      0x00000020U
#define GPTIMER_C1CFG_EDGE_BOTH                                      0x00000030U
/*

        Field:           INPUT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Select channel input.

        ENUMs:
            EV:                          Event fabric
            IO:                          IO controller
*/
#define GPTIMER_C1CFG_INPUT                                          0x00000040U
#define GPTIMER_C1CFG_INPUT_M                                        0x00000040U
#define GPTIMER_C1CFG_INPUT_S                                        6U
#define GPTIMER_C1CFG_INPUT_EV                                       0x00000000U
#define GPTIMER_C1CFG_INPUT_IO                                       0x00000040U
/*

        Field:           OUT0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 0 enable.
                         When 0 < [CCACT] < 8, OUT0 becomes zero after a capture or compare event.


        ENUMs:
            DIS:                         Channel 1 does not control output 0.
            EN:                          Channel 1 controls output 0.
*/
#define GPTIMER_C1CFG_OUT0                                           0x00000100U
#define GPTIMER_C1CFG_OUT0_M                                         0x00000100U
#define GPTIMER_C1CFG_OUT0_S                                         8U
#define GPTIMER_C1CFG_OUT0_DIS                                       0x00000000U
#define GPTIMER_C1CFG_OUT0_EN                                        0x00000100U
/*

        Field:           OUT1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 1 enable.

                         When 0 < [CCACT] < 8, OUT1 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 1 does not control output 1.
            EN:                          Channel 1 controls output 1.
*/
#define GPTIMER_C1CFG_OUT1                                           0x00000200U
#define GPTIMER_C1CFG_OUT1_M                                         0x00000200U
#define GPTIMER_C1CFG_OUT1_S                                         9U
#define GPTIMER_C1CFG_OUT1_DIS                                       0x00000000U
#define GPTIMER_C1CFG_OUT1_EN                                        0x00000200U
/*

        Field:           OUT2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 2 enable.

                         When 0 < [CCACT] < 8, OUT2 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 1 does not control output 2.
            EN:                          Channel 1 controls output 2.
*/
#define GPTIMER_C1CFG_OUT2                                           0x00000400U
#define GPTIMER_C1CFG_OUT2_M                                         0x00000400U
#define GPTIMER_C1CFG_OUT2_S                                         10U
#define GPTIMER_C1CFG_OUT2_DIS                                       0x00000000U
#define GPTIMER_C1CFG_OUT2_EN                                        0x00000400U
/*

        Field:           OUT3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 3 enable.

                         When 0 < [CCACT] < 8, OUT3 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 1 does not control output 3.
            EN:                          Channel 1 controls output 3.
*/
#define GPTIMER_C1CFG_OUT3                                           0x00000800U
#define GPTIMER_C1CFG_OUT3_M                                         0x00000800U
#define GPTIMER_C1CFG_OUT3_S                                         11U
#define GPTIMER_C1CFG_OUT3_DIS                                       0x00000000U
#define GPTIMER_C1CFG_OUT3_EN                                        0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C2CFG
    Offset name:         GPTIMER_O_C2CFG
    Relative address:    0xC8
    Description:         Channel 2 Configuration

                        This register configures channel function and enables outputs.

                        Each channel has an edge-detection circuit. The the edge-detection circuit is:
                         - enabled while [CCACT] selects a capture function and [CTL.MODE] is different from DIS.
                         - flushed while [CCACT] selects a capture function and [CTL.MODE] is changed from DIS to another mode.

                        The flush action uses two system clock periods. It prevents capture events caused by expired signal values stored in the edge-detection circuit.

                        The channel input signal enters the edge-detection circuit. False capture events can occur when:
                        - the edge-detection circuit contains expired signal samples and the circuit is enabled without flush as described above.
                        - the [CCACT] field is reconfigured while CTL.MODE is different from DIS.

                        Primary use scenario is to select [CCACT] before starting the timer. Follow these steps to configure [CCACT] to a capture action while [CTL.MODE] is different from DIS:
                        - Set [EDGE] to NONE.
                        - Configure [CCACT].
                        - Wait for three system clock periods before setting [EDGE] different from NONE.
                        These steps prevent capture events caused by expired signal values in edge-detection circuit.
    Default Value:       0x00000000

        Field:           CCACT
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture-Compare action.

                         Capture-Compare action defines 15 different channel functions that utilize capture, compare, and zero events. In every compare event the timer looks at the current value of [CNTR.*]. The corresponding output event will be set 1 timer period after [CNTR.*] = [C2CC.*].

        ENUMs:
            DIS:                         Disable channel.
            SET_ON_CAPT_DIS:             Set on capture, and then disable channel.

                         Channel function sequence:
                         - Set enabled outputs on capture event and copy [CNTR.VAL] to [C2CC.VAL].
                         - Disable channel.

                         Primary use scenario is to select this function before starting the timer.
                         Follow these steps to select this function while [CTL.MODE] is different from DIS:
                          - Set CCACT to SET_ON_CAPT with no output enable.
                          - Configure [INPUT] (optional).
                          - Wait for three timer clock periods as defined in [PRECFG.*] before setting CCACT to SET_ON_CAPT_DIS. Output enable is optional.

                         These steps prevent capture events caused by expired signal values in edge-detection circuit.
            CLR_ON_0_TGL_ON_CMP:         Clear on zero, toggle on compare repeatedly.

                         Channel function sequence:
                         - Clear enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C2CC.VAL] = [CNTR.VAL].

                         Set [CTL.MODE] to UPDWN_PER for center-aligned PWM generation. Duty cycle is given by:

                         When [C2CC.VAL] <= [TGT.VAL]:
                            Duty cycle = 1 - ( [C2CC.VAL] / [TGT.VAL] ).

                         When [C2CC.VAL] > [TGT.VAL]:
                            Duty cycle = 0.

                         Enabled outputs are set when [C2CC.VAL] = 0 and [CNTR.VAL] = 0.
            SET_ON_0_TGL_ON_CMP:         Set on zero, toggle on compare repeatedly.

                         Channel function sequence:
                         - Set enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C2CC.VAL] = [CNTR.VAL].

                         Set [CTL.MODE] to UP_PER for edge-aligned PWM generation. Duty cycle is given by:

                         When [C2CC.VAL] <= [TGT.VAL]:
                            Duty cycle = [C2CC.VAL] / ( [TGT.VAL] + 1 ).

                         When [C2CC.VAL] > [TGT.VAL]:
                            Duty cycle = 1.

                         Enabled outputs are cleared when [C2CC.VAL] = 0 and [CNTR.VAL] = 0.
            CLR_ON_CMP:                  Clear on compare repeatedly.

                         Channel function sequence:
                         - Clear enabled outputs  when [C2CC.VAL] = [CNTR.VAL].
            SET_ON_CMP:                  Set on compare repeatedly.

                         Channel function sequence:
                         - Set enabled outputs  when [C2CC.VAL] = [CNTR.VAL].
            TGL_ON_CMP:                  Toggle on compare repeatedly.

                         Channel function sequence:
                         - Toggle enabled outputs  when [C2CC.VAL] = [CNTR.VAL].
            PULSE_ON_CMP:                Pulse on compare repeatedly.

                         Channel function sequence:
                         - Pulse enabled outputs when [C2CC.VAL] = [CNTR.VAL].

                          The output is high for two timer clock periods.
            CLR_ON_0_TGL_ON_CMP_DIS:     Clear on zero, toggle on compare, and then disable channel.

                         Channel function sequence:
                         - Clear enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C2CC.VAL] = [CNTR.VAL].
                         - Disable channel.

                         Enabled outputs are set when [C2CC.VAL] = 0 and [CNTR.VAL] = 0.
            SET_ON_0_TGL_ON_CMP_DIS:     Set on zero, toggle on compare, and then disable channel.

                         Channel function sequence:
                         - Set enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C2CC.VAL] = [CNTR.VAL].
                         - Disable channel.

                         Enabled outputs are cleared when [C2CC.VAL] = 0 and [CNTR.VAL] = 0.
            CLR_ON_CMP_DIS:              Clear on compare, and then disable channel.

                         Channel function sequence:
                         - Clear enabled outputs when [C2CC.VAL] = [CNTR.VAL].
                         - Disable channel.
            SET_ON_CMP_DIS:              Set on compare, and then disable channel.

                         Channel function sequence:
                         - Set enabled outputs when [C2CC.VAL] = [CNTR.VAL].
                         - Disable channel.
            TGL_ON_CMP_DIS:              Toggle on compare, and then disable channel.

                         Channel function sequence:
                         - Toggle enabled outputs when [C2CC.VAL] = [CNTR.VAL].
                         - Disable channel.
            PULSE_ON_CMP_DIS:            Pulse on compare, and then disable channel.

                         Channel function sequence:
                         - Pulse enabled outputs when [C2CC.VAL] = [CNTR.VAL].
                         - Disable channel.

                          The output is high for two timer clock periods.
            PER_PULSE_WIDTH_MEAS:        Period and pulse width measurement.

                         Continuously capture period and pulse width of the signal selected by [INPUT] relative to the signal edge given by [EDGE].

                         Set enabled outputs and [RIS.C2CC] when [C2CC.VAL] contains signal period and [PC2CC.VAL] contains signal pulse width.

                         Notes:
                         - Make sure to configure [INPUT] and CCACT when [CTL.MODE] equals DIS, then set [CTL.MODE] to UP_ONCE or UP_PER.
                         - The counter restarts in the selected timer mode when [C2CC.VAL] contains the signal period.
                         - If more than one channel uses this function, the channels will perform this function one at a time. The channel with lowest number has priority and performs the function first. Next measurement starts when current measurement completes successfully or times out. A timeout occurs when counter equals target.
                         - To observe a timeout event the [RIS.TGT] interrupt can be used, or another channel can be configured to SET_ON_CMP with compare value equal [TGT].

                         Signal property requirements:
                         - Signal Period >= 2 * ( 1 + [PRECFG.TICKDIV] ) * timer clock period.
                         - Signal Period <= MAX([CNTR.*]) * (1 + [PRECFG.TICKDIV] ) * timer clock period.
                         - Signal low and high phase >= (1 + [PRECFG.TICKDIV] ) * timer clock period.
            SET_ON_CAPT:                 Set on capture repeatedly.

                         Channel function sequence:
                         - Set enabled outputs on capture event and copy [CNTR.VAL] to [C2CC.VAL].


*/
#define GPTIMER_C2CFG_CCACT_W                                        4U
#define GPTIMER_C2CFG_CCACT_M                                        0x0000000FU
#define GPTIMER_C2CFG_CCACT_S                                        0U
#define GPTIMER_C2CFG_CCACT_DIS                                      0x00000000U
#define GPTIMER_C2CFG_CCACT_SET_ON_CAPT_DIS                          0x00000001U
#define GPTIMER_C2CFG_CCACT_CLR_ON_0_TGL_ON_CMP                      0x0000000AU
#define GPTIMER_C2CFG_CCACT_SET_ON_0_TGL_ON_CMP                      0x0000000BU
#define GPTIMER_C2CFG_CCACT_CLR_ON_CMP                               0x0000000CU
#define GPTIMER_C2CFG_CCACT_SET_ON_CMP                               0x0000000DU
#define GPTIMER_C2CFG_CCACT_TGL_ON_CMP                               0x0000000EU
#define GPTIMER_C2CFG_CCACT_PULSE_ON_CMP                             0x0000000FU
#define GPTIMER_C2CFG_CCACT_CLR_ON_0_TGL_ON_CMP_DIS                  0x00000002U
#define GPTIMER_C2CFG_CCACT_SET_ON_0_TGL_ON_CMP_DIS                  0x00000003U
#define GPTIMER_C2CFG_CCACT_CLR_ON_CMP_DIS                           0x00000004U
#define GPTIMER_C2CFG_CCACT_SET_ON_CMP_DIS                           0x00000005U
#define GPTIMER_C2CFG_CCACT_TGL_ON_CMP_DIS                           0x00000006U
#define GPTIMER_C2CFG_CCACT_PULSE_ON_CMP_DIS                         0x00000007U
#define GPTIMER_C2CFG_CCACT_PER_PULSE_WIDTH_MEAS                     0x00000008U
#define GPTIMER_C2CFG_CCACT_SET_ON_CAPT                              0x00000009U
/*

        Field:           EDGE
        From..to bits:   4...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Determines the edge that triggers the channel input event. This happens post filter.

        ENUMs:
            NONE:                        Input is turned off.
            RISE:                        Input event is triggered at rising edge.
            FALL:                        Input event is triggered at falling edge.
            BOTH:                        Input event is triggered at both edges.
*/
#define GPTIMER_C2CFG_EDGE_W                                         2U
#define GPTIMER_C2CFG_EDGE_M                                         0x00000030U
#define GPTIMER_C2CFG_EDGE_S                                         4U
#define GPTIMER_C2CFG_EDGE_NONE                                      0x00000000U
#define GPTIMER_C2CFG_EDGE_RISE                                      0x00000010U
#define GPTIMER_C2CFG_EDGE_FALL                                      0x00000020U
#define GPTIMER_C2CFG_EDGE_BOTH                                      0x00000030U
/*

        Field:           INPUT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Select channel input.

        ENUMs:
            EV:                          Event fabric
            IO:                          IO controller
*/
#define GPTIMER_C2CFG_INPUT                                          0x00000040U
#define GPTIMER_C2CFG_INPUT_M                                        0x00000040U
#define GPTIMER_C2CFG_INPUT_S                                        6U
#define GPTIMER_C2CFG_INPUT_EV                                       0x00000000U
#define GPTIMER_C2CFG_INPUT_IO                                       0x00000040U
/*

        Field:           OUT0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 0 enable.

                         When 0 < [CCACT] < 8, OUT0 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 2 does not control output 0.
            EN:                          Channel 2 controls output 0.
*/
#define GPTIMER_C2CFG_OUT0                                           0x00000100U
#define GPTIMER_C2CFG_OUT0_M                                         0x00000100U
#define GPTIMER_C2CFG_OUT0_S                                         8U
#define GPTIMER_C2CFG_OUT0_DIS                                       0x00000000U
#define GPTIMER_C2CFG_OUT0_EN                                        0x00000100U
/*

        Field:           OUT1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 1 enable.

                         When 0 < [CCACT] < 8, OUT1 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 2 does not control output 1.
            EN:                          Channel 2 controls output 1.
*/
#define GPTIMER_C2CFG_OUT1                                           0x00000200U
#define GPTIMER_C2CFG_OUT1_M                                         0x00000200U
#define GPTIMER_C2CFG_OUT1_S                                         9U
#define GPTIMER_C2CFG_OUT1_DIS                                       0x00000000U
#define GPTIMER_C2CFG_OUT1_EN                                        0x00000200U
/*

        Field:           OUT2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 2 enable.

                         When 0 < [CCACT] < 8, OUT2 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 2 does not control output 2.
            EN:                          Channel 2 controls output 2.
*/
#define GPTIMER_C2CFG_OUT2                                           0x00000400U
#define GPTIMER_C2CFG_OUT2_M                                         0x00000400U
#define GPTIMER_C2CFG_OUT2_S                                         10U
#define GPTIMER_C2CFG_OUT2_DIS                                       0x00000000U
#define GPTIMER_C2CFG_OUT2_EN                                        0x00000400U
/*

        Field:           OUT3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 3 enable.

                         When 0 < [CCACT] < 8, OUT3 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 2 does not control output 3.
            EN:                          Channel 2 controls output 3.
*/
#define GPTIMER_C2CFG_OUT3                                           0x00000800U
#define GPTIMER_C2CFG_OUT3_M                                         0x00000800U
#define GPTIMER_C2CFG_OUT3_S                                         11U
#define GPTIMER_C2CFG_OUT3_DIS                                       0x00000000U
#define GPTIMER_C2CFG_OUT3_EN                                        0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C3CFG
    Offset name:         GPTIMER_O_C3CFG
    Relative address:    0xCC
    Description:         Channel 3 Configuration

                        This register configures channel function and enables outputs.

                        Each channel has an edge-detection circuit. The the edge-detection circuit is:
                         - enabled while [CCACT] selects a capture function and [CTL.MODE] is different from DIS.
                         - flushed while [CCACT] selects a capture function and [CTL.MODE] is changed from DIS to another mode.

                        The flush action uses two system clock periods. It prevents capture events caused by expired signal values stored in the edge-detection circuit.

                        The channel input signal enters the edge-detection circuit. False capture events can occur when:
                        - the edge-detection circuit contains expired signal samples and the circuit is enabled without flush as described above.
                        - the [CCACT] field is reconfigured while CTL.MODE is different from DIS.

                        Primary use scenario is to select [CCACT] before starting the timer. Follow these steps to configure [CCACT] to a capture action while [CTL.MODE] is different from DIS:
                        - Set [EDGE] to NONE.
                        - Configure [CCACT].
                        - Wait for three system clock periods before setting [EDGE] different from NONE.
                        These steps prevent capture events caused by expired signal values in edge-detection circuit.
    Default Value:       0x00000000

        Field:           CCACT
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture-Compare action.

                         Capture-Compare action defines 15 different channel functions that utilize capture, compare, and zero events. In every compare event the timer looks at the current value of [CNTR.*]. The corresponding output event will be set 1 timer period after [CNTR.*] = [C3CC.*].

        ENUMs:
            DIS:                         Disable channel.
            SET_ON_CAPT_DIS:             Set on capture, and then disable channel.

                         Channel function sequence:
                         - Set enabled outputs on capture event and copy [CNTR.VAL] to [C3CC.VAL].
                         - Disable channel.

                         Primary use scenario is to select this function before starting the timer.
                         Follow these steps to select this function while [CTL.MODE] is different from DIS:
                          - Set CCACT to SET_ON_CAPT with no output enable.
                          - Configure [INPUT] (optional).
                          - Wait for three timer clock periods as defined in [PRECFG.*] before setting CCACT to SET_ON_CAPT_DIS. Output enable is optional.

                         These steps prevent capture events caused by expired signal values in edge-detection circuit.
            CLR_ON_0_TGL_ON_CMP:         Clear on zero, toggle on compare repeatedly.

                         Channel function sequence:
                         - Clear enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C3CC.VAL] = [CNTR.VAL].

                         Set [CTL.MODE] to UPDWN_PER for center-aligned PWM generation. Duty cycle is given by:

                         When [C3CC.VAL] <= [TGT.VAL]:
                            Duty cycle = 1 - ( [C3CC.VAL] / [TGT.VAL] ).

                         When [C3CC.VAL] > [TGT.VAL]:
                            Duty cycle = 0.

                         Enabled outputs are set when [C3CC.VAL] = 0 and [CNTR.VAL] = 0.
            SET_ON_0_TGL_ON_CMP:         Set on zero, toggle on compare repeatedly.

                         Channel function sequence:
                         - Set enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C3CC.VAL] = [CNTR.VAL].

                         Set [CTL.MODE] to UP_PER for edge-aligned PWM generation. Duty cycle is given by:

                         When [C3CC.VAL] <= [TGT.VAL]:
                            Duty cycle = [C3CC.VAL] / ( [TGT.VAL] + 1 ).

                         When [C3CC.VAL] > [TGT.VAL]:
                            Duty cycle = 1.

                         Enabled outputs are cleared when [C3CC.VAL] = 0 and [CNTR.VAL] = 0.
            CLR_ON_CMP:                  Clear on compare repeatedly.

                         Channel function sequence:
                         - Clear enabled outputs  when [C3CC.VAL] = [CNTR.VAL].
            SET_ON_CMP:                  Set on compare repeatedly.

                         Channel function sequence:
                         - Set enabled outputs  when [C3CC.VAL] = [CNTR.VAL].
            TGL_ON_CMP:                  Toggle on compare repeatedly.

                         Channel function sequence:
                         - Toggle enabled outputs  when [C3CC.VAL] = [CNTR.VAL].
            PULSE_ON_CMP:                Pulse on compare repeatedly.

                         Channel function sequence:
                         - Pulse enabled outputs when [C3CC.VAL] = [CNTR.VAL].

                          The output is high for two timer clock periods.
            CLR_ON_0_TGL_ON_CMP_DIS:     Clear on zero, toggle on compare, and then disable channel.

                         Channel function sequence:
                         - Clear enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C3CC.VAL] = [CNTR.VAL].
                         - Disable channel.

                         Enabled outputs are set when [C3CC.VAL] = 0 and [CNTR.VAL] = 0.
            SET_ON_0_TGL_ON_CMP_DIS:     Set on zero, toggle on compare, and then disable channel.

                         Channel function sequence:
                         - Set enabled outputs when [CNTR.VAL] = 0.
                         - Toggle enabled outputs when [C3CC.VAL] = [CNTR.VAL].
                         - Disable channel.

                         Enabled outputs are cleared when [C3CC.VAL] = 0 and [CNTR.VAL] = 0.
            CLR_ON_CMP_DIS:              Clear on compare, and then disable channel.

                         Channel function sequence:
                         - Clear enabled outputs when [C3CC.VAL] = [CNTR.VAL].
                         - Disable channel.
            SET_ON_CMP_DIS:              Set on compare, and then disable channel.

                         Channel function sequence:
                         - Set enabled outputs when [C3CC.VAL] = [CNTR.VAL].
                         - Disable channel.
            TGL_ON_CMP_DIS:              Toggle on compare, and then disable channel.

                         Channel function sequence:
                         - Toggle enabled outputs when [C3CC.VAL] = [CNTR.VAL].
                         - Disable channel.
            PULSE_ON_CMP_DIS:            Pulse on compare, and then disable channel.

                         Channel function sequence:
                         - Pulse enabled outputs when [C3CC.VAL] = [CNTR.VAL].
                         - Disable channel.

                          The output is high for two timer clock periods.
            PER_PULSE_WIDTH_MEAS:        Period and pulse width measurement.

                         Continuously capture period and pulse width of the signal selected by [INPUT] relative to the signal edge given by [EDGE].

                         Set enabled outputs and [RIS.C3CC] when [C3CC.VAL] contains signal period and [PC3CC.VAL] contains signal pulse width.

                         Notes:
                         - Make sure to configure [INPUT] and CCACT when [CTL.MODE] equals DIS, then set [CTL.MODE] to UP_ONCE or UP_PER.
                         - The counter restarts in the selected timer mode when [C3CC.VAL] contains the signal period.
                         - If more than one channel uses this function, the channels will perform this function one at a time. The channel with lowest number has priority and performs the function first. Next measurement starts when current measurement completes successfully or times out. A timeout occurs when counter equals target.
                         - To observe a timeout event the [RIS.TGT] interrupt can be used, or another channel can be configured to SET_ON_CMP with compare value equal [TGT].

                         Signal property requirements:
                         - Signal Period >= 2 * ( 1 + [PRECFG.TICKDIV] ) * timer clock period.
                         - Signal Period <= MAX([CNTR.*]) * (1 + [PRECFG.TICKDIV] ) * timer clock period.
                         - Signal low and high phase >= (1 + [PRECFG.TICKDIV] ) * timer clock period.
            SET_ON_CAPT:                 Set on capture repeatedly.

                         Channel function sequence:
                         - Set enabled outputs on capture event and copy [CNTR.VAL] to [C3CC.VAL].


*/
#define GPTIMER_C3CFG_CCACT_W                                        4U
#define GPTIMER_C3CFG_CCACT_M                                        0x0000000FU
#define GPTIMER_C3CFG_CCACT_S                                        0U
#define GPTIMER_C3CFG_CCACT_DIS                                      0x00000000U
#define GPTIMER_C3CFG_CCACT_SET_ON_CAPT_DIS                          0x00000001U
#define GPTIMER_C3CFG_CCACT_CLR_ON_0_TGL_ON_CMP                      0x0000000AU
#define GPTIMER_C3CFG_CCACT_SET_ON_0_TGL_ON_CMP                      0x0000000BU
#define GPTIMER_C3CFG_CCACT_CLR_ON_CMP                               0x0000000CU
#define GPTIMER_C3CFG_CCACT_SET_ON_CMP                               0x0000000DU
#define GPTIMER_C3CFG_CCACT_TGL_ON_CMP                               0x0000000EU
#define GPTIMER_C3CFG_CCACT_PULSE_ON_CMP                             0x0000000FU
#define GPTIMER_C3CFG_CCACT_CLR_ON_0_TGL_ON_CMP_DIS                  0x00000002U
#define GPTIMER_C3CFG_CCACT_SET_ON_0_TGL_ON_CMP_DIS                  0x00000003U
#define GPTIMER_C3CFG_CCACT_CLR_ON_CMP_DIS                           0x00000004U
#define GPTIMER_C3CFG_CCACT_SET_ON_CMP_DIS                           0x00000005U
#define GPTIMER_C3CFG_CCACT_TGL_ON_CMP_DIS                           0x00000006U
#define GPTIMER_C3CFG_CCACT_PULSE_ON_CMP_DIS                         0x00000007U
#define GPTIMER_C3CFG_CCACT_PER_PULSE_WIDTH_MEAS                     0x00000008U
#define GPTIMER_C3CFG_CCACT_SET_ON_CAPT                              0x00000009U
/*

        Field:           EDGE
        From..to bits:   4...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Determines the edge that triggers the channel input event. This happens post filter.

        ENUMs:
            NONE:                        Input is turned off.
            RISE:                        Input event is triggered at rising edge.
            FALL:                        Input event is triggered at falling edge.
            BOTH:                        Input event is triggered at both edges.
*/
#define GPTIMER_C3CFG_EDGE_W                                         2U
#define GPTIMER_C3CFG_EDGE_M                                         0x00000030U
#define GPTIMER_C3CFG_EDGE_S                                         4U
#define GPTIMER_C3CFG_EDGE_NONE                                      0x00000000U
#define GPTIMER_C3CFG_EDGE_RISE                                      0x00000010U
#define GPTIMER_C3CFG_EDGE_FALL                                      0x00000020U
#define GPTIMER_C3CFG_EDGE_BOTH                                      0x00000030U
/*

        Field:           INPUT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Select channel input.

        ENUMs:
            EV:                          Event fabric
            IO:                          IO controller
*/
#define GPTIMER_C3CFG_INPUT                                          0x00000040U
#define GPTIMER_C3CFG_INPUT_M                                        0x00000040U
#define GPTIMER_C3CFG_INPUT_S                                        6U
#define GPTIMER_C3CFG_INPUT_EV                                       0x00000000U
#define GPTIMER_C3CFG_INPUT_IO                                       0x00000040U
/*

        Field:           OUT0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 0 enable.

                         When 0 < [CCACT] < 8, OUT0 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 3 does not control output 0.
            EN:                          Channel 3 controls output 0.
*/
#define GPTIMER_C3CFG_OUT0                                           0x00000100U
#define GPTIMER_C3CFG_OUT0_M                                         0x00000100U
#define GPTIMER_C3CFG_OUT0_S                                         8U
#define GPTIMER_C3CFG_OUT0_DIS                                       0x00000000U
#define GPTIMER_C3CFG_OUT0_EN                                        0x00000100U
/*

        Field:           OUT1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 1 enable.

                         When 0 < [CCACT] < 8, OUT1 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 3 does not control output 1.
            EN:                          Channel 3 controls output 1.
*/
#define GPTIMER_C3CFG_OUT1                                           0x00000200U
#define GPTIMER_C3CFG_OUT1_M                                         0x00000200U
#define GPTIMER_C3CFG_OUT1_S                                         9U
#define GPTIMER_C3CFG_OUT1_DIS                                       0x00000000U
#define GPTIMER_C3CFG_OUT1_EN                                        0x00000200U
/*

        Field:           OUT2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 2 enable.

                         When 0 < [CCACT] < 8, OUT2 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 3 does not control output 2.
            EN:                          Channel 3 controls output 2.
*/
#define GPTIMER_C3CFG_OUT2                                           0x00000400U
#define GPTIMER_C3CFG_OUT2_M                                         0x00000400U
#define GPTIMER_C3CFG_OUT2_S                                         10U
#define GPTIMER_C3CFG_OUT2_DIS                                       0x00000000U
#define GPTIMER_C3CFG_OUT2_EN                                        0x00000400U
/*

        Field:           OUT3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Output 3 enable.

                         When 0 < [CCACT] < 8, OUT3 becomes zero after a capture or compare event.

        ENUMs:
            DIS:                         Channel 3 does not control output 3.
            EN:                          Channel 3 controls output 3.
*/
#define GPTIMER_C3CFG_OUT3                                           0x00000800U
#define GPTIMER_C3CFG_OUT3_M                                         0x00000800U
#define GPTIMER_C3CFG_OUT3_S                                         11U
#define GPTIMER_C3CFG_OUT3_DIS                                       0x00000000U
#define GPTIMER_C3CFG_OUT3_EN                                        0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PTGT
    Offset name:         GPTIMER_O_PTGT
    Relative address:    0xFC
    Description:         Pipeline Target
                        A read or write to this register will clear the [RIS.ZERO] and [RIS.TGT] interrupt.


                        If [CTL.MODE] != QDEC.
                        Target value for next counter period.
                        The timer will copy [PTGT.VAL] to [TGT.VAL] on the upcoming [CNTR.*] zero crossing only if [PTGT.VAL] has been written. The copy does not happen when restarting the timer.
                        This is useful to avoid period jitter in PWM applications with time-varying period, sometimes referenced as phase corrected PWM.

                        If [CTL.MODE] = QDEC
                        The [CNTR.*] value is updated with VALUE on IDX if the counter is counting down. If the counter is counting up, [CNTR.*] is loaded with zero on IDX.
                        In this mode the VALUE is not loaded into [TGT] on zero crossing.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The pipleline target value.

*/
#define GPTIMER_PTGT_VAL_W                                           32U
#define GPTIMER_PTGT_VAL_M                                           0xFFFFFFFFU
#define GPTIMER_PTGT_VAL_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PC0CC
    Offset name:         GPTIMER_O_PC0CC
    Relative address:    0x100
    Description:         Pipeline Channel 0 Capture Compare
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Pipeline Capture Compare value.

                         User defined pipeline compare value or channel-updated capture value.

                         A read or write to this register will clear the [RIS.C0CC] interrupt.

                         Compare mode:
                         An update of VAL will be transferred to [C0CC.VAL] when the next [CNTR.VAL] is zero and [CTL.MODE] is different from DIS. This is useful for PWM generation and prevents jitter on the edges of the generated signal.

                         Capture mode:
                         When [C0CFG.CCACT] equals PER_PULSE_WIDTH_MEAS then VAL contains the width of the low or high phase of the selected signal. This is specified by [C0CFG.EDGE].

*/
#define GPTIMER_PC0CC_VAL_W                                          32U
#define GPTIMER_PC0CC_VAL_M                                          0xFFFFFFFFU
#define GPTIMER_PC0CC_VAL_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PC1CC
    Offset name:         GPTIMER_O_PC1CC
    Relative address:    0x104
    Description:         Pipeline Channel 1 Capture Compare
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Pipeline Capture Compare value.

                         User defined pipeline compare value or channel-updated capture value.

                         A read or write to this register will clear the [RIS.C1CC] interrupt.

                         Compare mode:
                         An update of VAL will be transferred to [C1CC.VAL] when the next [CNTR.VAL] is zero and [CTL.MODE] is different from DIS. This is useful for PWM generation and prevents jitter on the edges of the generated signal.

                         Capture mode:
                         When [C1CFG.CCACT] equals PER_PULSE_WIDTH_MEAS then VAL contains the width of the low or high phase of the selected signal. This is specified by [C1CFG.EDGE].

*/
#define GPTIMER_PC1CC_VAL_W                                          32U
#define GPTIMER_PC1CC_VAL_M                                          0xFFFFFFFFU
#define GPTIMER_PC1CC_VAL_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PC2CC
    Offset name:         GPTIMER_O_PC2CC
    Relative address:    0x108
    Description:         Pipeline Channel 2 Capture Compare
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Pipeline Capture Compare value.

                         User defined pipeline compare value or channel-updated capture value.

                         A read or write to this register will clear the [RIS.C2CC] interrupt.

                         Compare mode:
                         An update of VAL will be transferred to [C2CC.VAL] when the next [CNTR.VAL] is zero and [CTL.MODE] is different from DIS. This is useful for PWM generation and prevents jitter on the edges of the generated signal.

                         Capture mode:
                         When [C2CFG.CCACT] equals PER_PULSE_WIDTH_MEAS then VAL contains the width of the low or high phase of the selected signal. This is specified by [C2CFG.EDGE].

*/
#define GPTIMER_PC2CC_VAL_W                                          32U
#define GPTIMER_PC2CC_VAL_M                                          0xFFFFFFFFU
#define GPTIMER_PC2CC_VAL_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PC3CC
    Offset name:         GPTIMER_O_PC3CC
    Relative address:    0x10C
    Description:         Pipeline Channel 3 Capture Compare
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Pipeline Capture Compare value.

                         User defined pipeline compare value or channel-updated capture value.

                         A read or write to this register will clear the [RIS.C3CC] interrupt.

                         Compare mode:
                         An update of VAL will be transferred to [C3CC.VAL] when the next [CNTR.VAL] is zero and [CTL.MODE] is different from DIS. This is useful for PWM generation and prevents jitter on the edges of the generated signal.

                         Capture mode:
                         When [C3CFG.CCACT] equals PER_PULSE_WIDTH_MEAS then VAL contains the width of the low or high phase of the selected signal. This is specified by [C3CFG.EDGE].

*/
#define GPTIMER_PC3CC_VAL_W                                          32U
#define GPTIMER_PC3CC_VAL_M                                          0xFFFFFFFFU
#define GPTIMER_PC3CC_VAL_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TGT
    Offset name:         GPTIMER_O_TGT
    Relative address:    0x13C
    Description:         Target

                        User defined counter target.
                        A read or write to this register will clear the [RIS.ZERO] and [RIS.TGT] interrupt.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     User defined counter target value.

*/
#define GPTIMER_TGT_VAL_W                                            32U
#define GPTIMER_TGT_VAL_M                                            0xFFFFFFFFU
#define GPTIMER_TGT_VAL_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C0CC
    Offset name:         GPTIMER_O_C0CC
    Relative address:    0x140
    Description:         Channel 0 Capture Compare
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture Compare value.

                         User defined compare value or channel-updated capture value.

                         A read or write to this register will clear the [RIS.C0CC] interrupt.

                         Compare mode:
                         VAL is compared against [CNTR.VAL] and an event is generated as specified by [C0CFG.CCACT] when these are equal.

                         Capture mode:
                         The current counter value is stored in VAL when a capture event occurs. [C0CFG.CCACT] determines if VAL is a signal period or a regular capture value.

*/
#define GPTIMER_C0CC_VAL_W                                           32U
#define GPTIMER_C0CC_VAL_M                                           0xFFFFFFFFU
#define GPTIMER_C0CC_VAL_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C1CC
    Offset name:         GPTIMER_O_C1CC
    Relative address:    0x144
    Description:         Channel 1 Capture Compare
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture Compare value.

                         User defined compare value or channel-updated capture value.

                         A read or write to this register will clear the [RIS.C1CC] interrupt.

                         Compare mode:
                         VAL is compared against [CNTR.VAL] and an event is generated as specified by [C1CFG.CCACT] when these are equal.

                         Capture mode:
                         The current counter value is stored in VAL when a capture event occurs. [C1CFG.CCACT] determines if VAL is a signal period or a regular capture value.

*/
#define GPTIMER_C1CC_VAL_W                                           32U
#define GPTIMER_C1CC_VAL_M                                           0xFFFFFFFFU
#define GPTIMER_C1CC_VAL_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C2CC
    Offset name:         GPTIMER_O_C2CC
    Relative address:    0x148
    Description:         Channel 2 Capture Compare
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture Compare value.

                         User defined compare value or channel-updated capture value.

                         A read or write to this register will clear the [RIS.C2CC] interrupt.

                         Compare mode:
                         VAL is compared against [CNTR.VAL] and an event is generated as specified by [C2CFG.CCACT] when these are equal.

                         Capture mode:
                         The current counter value is stored in VAL when a capture event occurs. [C2CFG.CCACT] determines if VAL is a signal period or a regular capture value.

*/
#define GPTIMER_C2CC_VAL_W                                           32U
#define GPTIMER_C2CC_VAL_M                                           0xFFFFFFFFU
#define GPTIMER_C2CC_VAL_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C3CC
    Offset name:         GPTIMER_O_C3CC
    Relative address:    0x14C
    Description:         Channel 3 Capture Compare
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture Compare value.

                         User defined compare value or channel-updated capture value.

                         A read or write to this register will clear the [RIS.C3CC] interrupt.

                         Compare mode:
                         VAL is compared against [CNTR.VAL] and an event is generated as specified by [C3CFG.CCACT] when these are equal.

                         Capture mode:
                         The current counter value is stored in VAL when a capture event occurs. [C3CFG.CCACT] determines if VAL is a signal period or a regular capture value.

*/
#define GPTIMER_C3CC_VAL_W                                           32U
#define GPTIMER_C3CC_VAL_M                                           0xFFFFFFFFU
#define GPTIMER_C3CC_VAL_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PTGTNC
    Offset name:         GPTIMER_O_PTGTNC
    Relative address:    0x17C
    Description:         Pipeline Target No Clear

                        Use this register to read or write to [PTGT.*] without clearing the [RIS.ZERO] and [RIS.TGT] interrupt.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     A read or write to this register will not clear the [RIS.TGT] interrupt.

                         If [CTL.MODE] != QDEC.
                         Target value for next counter period.
                         The timer copies VAL to [TGT.VAL] when [CNTR.VAL] becomes 0. The copy does not happen when restarting the timer.
                         This is useful to avoid period jitter in **PWM** applications with time-varying period, sometimes referenced as phase corrected PWM.

                         If [CTL.MODE] = QDEC.
                         The [CNTR.VAL] is updated with VAL on IDX. VAL is not loaded into [TGT.VAL] when [CNTR.VAL] becomes 0.

*/
#define GPTIMER_PTGTNC_VAL_W                                         32U
#define GPTIMER_PTGTNC_VAL_M                                         0xFFFFFFFFU
#define GPTIMER_PTGTNC_VAL_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PC0CCNC
    Offset name:         GPTIMER_O_PC0CCNC
    Relative address:    0x180
    Description:         Pipeline Channel 0 Capture Compare No Clear
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Pipeline Capture Compare value.

                         User defined pipeline compare value or channel-updated capture value.

                         A read or write to this register will not clear the [RIS.C0CC] interrupt.

                         Compare mode:
                         An update of VAL will be transferred to [C0CC.VAL] when the next [CNTR.VAL] is zero and [CTL.MODE] is different from DIS. This is useful for **PWM** generation and prevents jitter on the edges of the generated signal.

                         Capture mode:
                         When [C0CFG.CCACT] equals PER_PULSE_WIDTH_MEAS then VAL contains the width of the low or high phase of the selected signal. This is specified by [C0CFG.EDGE].

*/
#define GPTIMER_PC0CCNC_VAL_W                                        32U
#define GPTIMER_PC0CCNC_VAL_M                                        0xFFFFFFFFU
#define GPTIMER_PC0CCNC_VAL_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PC1CCNC
    Offset name:         GPTIMER_O_PC1CCNC
    Relative address:    0x184
    Description:         Pipeline Channel 1 Capture Compare No Clear
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Pipeline Capture Compare value.

                         User defined pipeline compare value or channel-updated capture value.

                         A read or write to this register will not clear the [RIS.C1CC] interrupt.

                         Compare mode:
                         An update of VAL will be transferred to [C1CC.VAL] when the next [CNTR.VAL] is zero and [CTL.MODE] is different from DIS. This is useful for **PWM** generation and prevents jitter on the edges of the generated signal.

                         Capture mode:
                         When [C1CFG.CCACT] equals PER_PULSE_WIDTH_MEAS then VAL contains the width of the low or high phase of the selected signal. This is specified by [C1CFG.EDGE].

*/
#define GPTIMER_PC1CCNC_VAL_W                                        32U
#define GPTIMER_PC1CCNC_VAL_M                                        0xFFFFFFFFU
#define GPTIMER_PC1CCNC_VAL_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PC2CCNC
    Offset name:         GPTIMER_O_PC2CCNC
    Relative address:    0x188
    Description:         Pipeline Channel 2 Capture Compare No Clear
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Pipeline Capture Compare value.

                         User defined pipeline compare value or channel-updated capture value.

                         A read or write to this register will not clear the [RIS.C2CC] interrupt.

                         Compare mode:
                         An update of VAL will be transferred to [C2CC.VAL] when the next [CNTR.VAL] is zero and [CTL.MODE] is different from DIS. This is useful for **PWM** generation and prevents jitter on the edges of the generated signal.

                         Capture mode:
                         When [C2CFG.CCACT] equals PER_PULSE_WIDTH_MEAS then VAL contains the width of the low or high phase of the selected signal. This is specified by [C2CFG.EDGE].

*/
#define GPTIMER_PC2CCNC_VAL_W                                        32U
#define GPTIMER_PC2CCNC_VAL_M                                        0xFFFFFFFFU
#define GPTIMER_PC2CCNC_VAL_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PC3CCNC
    Offset name:         GPTIMER_O_PC3CCNC
    Relative address:    0x18C
    Description:         Pipeline Channel 3 Capture Compare No Clear
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Pipeline Capture Compare value.

                         User defined pipeline compare value or channel-updated capture value.

                         A read or write to this register will not clear the [RIS.C3CC] interrupt.

                         Compare mode:
                         An update of VAL will be transferred to [C3CC.VAL] when the next [CNTR.VAL] is zero and [CTL.MODE] is different from DIS. This is useful for **PWM** generation and prevents jitter on the edges of the generated signal.

                         Capture mode:
                         When [C3CFG.CCACT] equals PER_PULSE_WIDTH_MEAS then VAL contains the width of the low or high phase of the selected signal. This is specified by [C3CFG.EDGE].

*/
#define GPTIMER_PC3CCNC_VAL_W                                        32U
#define GPTIMER_PC3CCNC_VAL_M                                        0xFFFFFFFFU
#define GPTIMER_PC3CCNC_VAL_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TGTNC
    Offset name:         GPTIMER_O_TGTNC
    Relative address:    0x1BC
    Description:         Target No Clear

                        Use this register to read or write to [TGT.*] without clearing the [RIS.ZERO] and [RIS.TGT] interrupt.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     User defined counter target value.

*/
#define GPTIMER_TGTNC_VAL_W                                          32U
#define GPTIMER_TGTNC_VAL_M                                          0xFFFFFFFFU
#define GPTIMER_TGTNC_VAL_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C0CCNC
    Offset name:         GPTIMER_O_C0CCNC
    Relative address:    0x1C0
    Description:         Channel 0 Capture Compare No Clear
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture Compare value.

                         User defined compare value or channel-updated capture value.

                         A read or write to this register will not clear the [RIS.C0CC] interrupt.

                         Compare mode:
                         VAL is compared against [CNTR.VAL] and an event is generated as specified by [C0CFG.CCACT] when these are equal.

                         Capture mode:
                         The current counter value is stored in VAL when a capture event occurs. [C0CFG.CCACT] determines if VAL is a signal period or a regular capture value.

*/
#define GPTIMER_C0CCNC_VAL_W                                         32U
#define GPTIMER_C0CCNC_VAL_M                                         0xFFFFFFFFU
#define GPTIMER_C0CCNC_VAL_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C1CCNC
    Offset name:         GPTIMER_O_C1CCNC
    Relative address:    0x1C4
    Description:         Channel 1 Capture Compare No Clear
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture Compare value.

                         User defined compare value or channel-updated capture value.

                         A read or write to this register will not clear the [RIS.C1CC] interrupt.

                         Compare mode:
                         VAL is compared against [CNTR.VAL] and an event is generated as specified by [C1CFG.CCACT] when these are equal.

                         Capture mode:
                         The current counter value is stored in VAL when a capture event occurs. [C1CFG.CCACT] determines if VAL is a signal period or a regular capture value.

*/
#define GPTIMER_C1CCNC_VAL_W                                         32U
#define GPTIMER_C1CCNC_VAL_M                                         0xFFFFFFFFU
#define GPTIMER_C1CCNC_VAL_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C2CCNC
    Offset name:         GPTIMER_O_C2CCNC
    Relative address:    0x1C8
    Description:         Channel 2 Capture Compare No Clear
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture Compare value.

                         User defined compare value or channel-updated capture value.

                         A read or write to this register will not clear the [RIS.C2CC] interrupt.

                         Compare mode:
                         VAL is compared against [CNTR.VAL] and an event is generated as specified by [C2CFG.CCACT] when these are equal.

                         Capture mode:
                         The current counter value is stored in VAL when a capture event occurs. [C2CFG.CCACT] determines if VAL is a signal period or a regular capture value.

*/
#define GPTIMER_C2CCNC_VAL_W                                         32U
#define GPTIMER_C2CCNC_VAL_M                                         0xFFFFFFFFU
#define GPTIMER_C2CCNC_VAL_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C3CCNC
    Offset name:         GPTIMER_O_C3CCNC
    Relative address:    0x1CC
    Description:         Channel 3 Capture Compare No Clear
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Capture Compare value.

                         User defined compare value or channel-updated capture value.

                         A read or write to this register will not clear the [RIS.C3CC] interrupt.

                         Compare mode:
                         VAL is compared against [CNTR.VAL] and an event is generated as specified by [C3CFG.CCACT] when these are equal.

                         Capture mode:
                         The current counter value is stored in VAL when a capture event occurs. [C3CFG.CCACT] determines if VAL is a signal period or a regular capture value.

*/
#define GPTIMER_C3CCNC_VAL_W                                         32U
#define GPTIMER_C3CCNC_VAL_M                                         0xFFFFFFFFU
#define GPTIMER_C3CCNC_VAL_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCFG
    Offset name:         GPTIMER_O_CLKCFG
    Relative address:    0x1000
    Description:         Clock Enable Register
    Default Value:       0x00000000

        Field:           ENABLE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     GPTimer main clock Enable

*/
#define GPTIMER_CLKCFG_ENABLE                                        0x00000001U
#define GPTIMER_CLKCFG_ENABLE_M                                      0x00000001U
#define GPTIMER_CLKCFG_ENABLE_S                                      0U

#endif /* __HW_GPTIMER_H__*/
