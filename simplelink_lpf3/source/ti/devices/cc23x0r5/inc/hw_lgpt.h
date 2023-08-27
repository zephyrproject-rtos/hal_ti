/******************************************************************************
*  Filename:       hw_lgpt_h
******************************************************************************
*  Copyright (c) 2021 Texas Instruments Incorporated. All rights reserved.
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
*  3) Neither the name of the copyright holder nor the names of its contributors
*     may be used to endorse or promote products derived from this software
*     without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
******************************************************************************/

#ifndef __HW_LGPT_H__
#define __HW_LGPT_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LGPT component
//
//*****************************************************************************
// Description Register.
#define LGPT_O_DESC                                                0x00000000U

// Description Extended
#define LGPT_O_DESCEX                                              0x00000004U

// Start Configuration
#define LGPT_O_STARTCFG                                            0x00000008U

// Timer Control
#define LGPT_O_CTL                                                 0x0000000CU

// Output Control
#define LGPT_O_OUTCTL                                              0x00000010U

// Counter
#define LGPT_O_CNTR                                                0x00000014U

// Clock Prescaler Configuration
#define LGPT_O_PRECFG                                              0x00000018U

// Prescaler Event
#define LGPT_O_PREEVENT                                            0x0000001CU

// Channel Input Filter
#define LGPT_O_CHFILT                                              0x00000020U

// Quadrature Decoder Status
#define LGPT_O_QDECSTAT                                            0x00000034U

// IR Generation
#define LGPT_O_IRGEN                                               0x00000038U

// Direct Memory Accsess
#define LGPT_O_DMA                                                 0x0000003CU

// Direct Memory Access
#define LGPT_O_DMARW                                               0x00000040U

// ADC Trigger
#define LGPT_O_ADCTRG                                              0x00000044U

// IO Controller
#define LGPT_O_IOCTL                                               0x00000048U

// Interrupt mask.
#define LGPT_O_IMASK                                               0x00000068U

// Raw interrupt status.
#define LGPT_O_RIS                                                 0x0000006CU

// Masked interrupt status.
#define LGPT_O_MIS                                                 0x00000070U

// Interrupt set register.
#define LGPT_O_ISET                                                0x00000074U

// Interrupt clear register.
#define LGPT_O_ICLR                                                0x00000078U

// Interrupt mask set register.
#define LGPT_O_IMSET                                               0x0000007CU

// Interrupt mask clear register.
#define LGPT_O_IMCLR                                               0x00000080U

// Debug control
#define LGPT_O_EMU                                                 0x00000084U

// Channel 0 Configuration
#define LGPT_O_C0CFG                                               0x000000C0U

// Channel 1 Configuration
#define LGPT_O_C1CFG                                               0x000000C4U

// Channel 2 Configuration
#define LGPT_O_C2CFG                                               0x000000C8U

// Pipeline Target
#define LGPT_O_PTGT                                                0x000000FCU

// Pipeline Channel 0 Capture Compare
#define LGPT_O_PC0CC                                               0x00000100U

// Pipeline Channel 1 Capture Compare
#define LGPT_O_PC1CC                                               0x00000104U

// Pipeline Channel 2 Capture Compare
#define LGPT_O_PC2CC                                               0x00000108U

// Target
#define LGPT_O_TGT                                                 0x0000013CU

// Channel 0 Capture Compare
#define LGPT_O_C0CC                                                0x00000140U

// Channel 1 Capture Compare
#define LGPT_O_C1CC                                                0x00000144U

// Channel 2 Capture Compare
#define LGPT_O_C2CC                                                0x00000148U

// Pipeline Target No Clear
#define LGPT_O_PTGTNC                                              0x0000017CU

// Pipeline Channel 0 Capture Compare No Clear
#define LGPT_O_PC0CCNC                                             0x00000180U

// Pipeline Channel 1 Capture Compare No Clear
#define LGPT_O_PC1CCNC                                             0x00000184U

// Pipeline Channel 2 Capture Compare No Clear
#define LGPT_O_PC2CCNC                                             0x00000188U

// Target No Clear
#define LGPT_O_TGTNC                                               0x000001BCU

// Channel 0 Capture Compare No Clear
#define LGPT_O_C0CCNC                                              0x000001C0U

// Channel 1 Capture Compare No Clear
#define LGPT_O_C1CCNC                                              0x000001C4U

// Channel 2 Capture Compare No Clear
#define LGPT_O_C2CCNC                                              0x000001C8U

//*****************************************************************************
//
// Register: LGPT_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module identifier used to uniquely identify this IP.
#define LGPT_DESC_MODID_W                                                  16U
#define LGPT_DESC_MODID_M                                          0xFFFF0000U
#define LGPT_DESC_MODID_S                                                  16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set of from
// aggregated IRQ registers till DTB.
//
// 0: Standard IP MMRs do not exist
//
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
#define LGPT_DESC_STDIPOFF_W                                                4U
#define LGPT_DESC_STDIPOFF_M                                       0x0000F000U
#define LGPT_DESC_STDIPOFF_S                                               12U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number. If multiple instances of IP exist in the device, this
// field can identify the instance number.
#define LGPT_DESC_INSTIDX_W                                                 4U
#define LGPT_DESC_INSTIDX_M                                        0x00000F00U
#define LGPT_DESC_INSTIDX_S                                                 8U

// Field:   [7:4] MAJREV
//
// Major revision of IP.
#define LGPT_DESC_MAJREV_W                                                  4U
#define LGPT_DESC_MAJREV_M                                         0x000000F0U
#define LGPT_DESC_MAJREV_S                                                  4U

// Field:   [3:0] MINREV
//
// Minor revision of IP.
#define LGPT_DESC_MINREV_W                                                  4U
#define LGPT_DESC_MINREV_M                                         0x0000000FU
#define LGPT_DESC_MINREV_S                                                  0U

//*****************************************************************************
//
// Register: LGPT_O_DESCEX
//
//*****************************************************************************
// Field:    [19] HIR
//
// Has IR logic.
#define LGPT_DESCEX_HIR                                            0x00080000U
#define LGPT_DESCEX_HIR_M                                          0x00080000U
#define LGPT_DESCEX_HIR_S                                                  19U

// Field:    [18] HDBF
//
// Has Dead-Band, Fault, and Park logic.
#define LGPT_DESCEX_HDBF                                           0x00040000U
#define LGPT_DESCEX_HDBF_M                                         0x00040000U
#define LGPT_DESCEX_HDBF_S                                                 18U

// Field: [17:14] PREW
//
// Prescale width. The prescaler can maximum be configured to 2^PREW-1.
#define LGPT_DESCEX_PREW_W                                                  4U
#define LGPT_DESCEX_PREW_M                                         0x0003C000U
#define LGPT_DESCEX_PREW_S                                                 14U

// Field:    [13] HQDEC
//
// Has Quadrature Decoder.
#define LGPT_DESCEX_HQDEC                                          0x00002000U
#define LGPT_DESCEX_HQDEC_M                                        0x00002000U
#define LGPT_DESCEX_HQDEC_S                                                13U

// Field:    [12] HCIF
//
// Has channel input filter.
#define LGPT_DESCEX_HCIF                                           0x00001000U
#define LGPT_DESCEX_HCIF_M                                         0x00001000U
#define LGPT_DESCEX_HCIF_S                                                 12U

// Field:  [11:8] CIFS
//
// Channel input filter size. The prevailing state filter can maximum be
// configured to 2^CIFS-1.
#define LGPT_DESCEX_CIFS_W                                                  4U
#define LGPT_DESCEX_CIFS_M                                         0x00000F00U
#define LGPT_DESCEX_CIFS_S                                                  8U

// Field:     [7] HDMA
//
// Has uDMA output and logic.
#define LGPT_DESCEX_HDMA                                           0x00000080U
#define LGPT_DESCEX_HDMA_M                                         0x00000080U
#define LGPT_DESCEX_HDMA_S                                                  7U

// Field:     [6] HINT
//
// Has interrupt output and logic.
#define LGPT_DESCEX_HINT                                           0x00000040U
#define LGPT_DESCEX_HINT_M                                         0x00000040U
#define LGPT_DESCEX_HINT_S                                                  6U

// Field:   [5:4] CNTRW
//
// Counter bit-width.
// The maximum counter value is equal to 2^CNTRW-1.
// ENUMs:
// RESERVED                 RESERVED
// CNTR32                   32-bit counter.
// CNTR24                   24-bit counter.
// CNTR16                   16-bit counter.
#define LGPT_DESCEX_CNTRW_W                                                 2U
#define LGPT_DESCEX_CNTRW_M                                        0x00000030U
#define LGPT_DESCEX_CNTRW_S                                                 4U
#define LGPT_DESCEX_CNTRW_RESERVED                                 0x00000030U
#define LGPT_DESCEX_CNTRW_CNTR32                                   0x00000020U
#define LGPT_DESCEX_CNTRW_CNTR24                                   0x00000010U
#define LGPT_DESCEX_CNTRW_CNTR16                                   0x00000000U

// Field:   [3:0] NCH
//
// Number of channels.
#define LGPT_DESCEX_NCH_W                                                   4U
#define LGPT_DESCEX_NCH_M                                          0x0000000FU
#define LGPT_DESCEX_NCH_S                                                   0U

//*****************************************************************************
//
// Register: LGPT_O_STARTCFG
//
//*****************************************************************************
// Field:   [1:0] LGPT
//
// LGPT start
// ENUMs:
// EV_SYNC                  LGPT starts when synchronized event input is high.
//                          Configured here EVTSVT.LGPTSYNCSEL.
#define LGPT_STARTCFG_LGPT_W                                               2U
#define LGPT_STARTCFG_LGPT_M                                      0x00000003U
#define LGPT_STARTCFG_LGPT_S                                               0U
#define LGPT_STARTCFG_LGPT_EV_SYNC                                0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_CTL
//
//*****************************************************************************
// Field:    [10] C2RST
//
// Channel 2 reset.
// ENUMs:
// RST                      Reset C2CC, PC2CC, and C2CFG.
// NOEFF                    No effect.
#define LGPT_CTL_C2RST                                             0x00000400U
#define LGPT_CTL_C2RST_M                                           0x00000400U
#define LGPT_CTL_C2RST_S                                                   10U
#define LGPT_CTL_C2RST_RST                                         0x00000400U
#define LGPT_CTL_C2RST_NOEFF                                       0x00000000U

// Field:     [9] C1RST
//
// Channel 1 reset.
// ENUMs:
// RST                      Reset C1CC, PC1CC, and C1CFG.
// NOEFF                    No effect.
#define LGPT_CTL_C1RST                                             0x00000200U
#define LGPT_CTL_C1RST_M                                           0x00000200U
#define LGPT_CTL_C1RST_S                                                    9U
#define LGPT_CTL_C1RST_RST                                         0x00000200U
#define LGPT_CTL_C1RST_NOEFF                                       0x00000000U

// Field:     [8] C0RST
//
// Channel 0 reset.
// ENUMs:
// RST                      Reset C0CC, PC0CC, and C0CFG.
// NOEFF                    No effect.
#define LGPT_CTL_C0RST                                             0x00000100U
#define LGPT_CTL_C0RST_M                                           0x00000100U
#define LGPT_CTL_C0RST_S                                                    8U
#define LGPT_CTL_C0RST_RST                                         0x00000100U
#define LGPT_CTL_C0RST_NOEFF                                       0x00000000U

// Field:     [5] INTP
//
// Interrupt Phase.
// This bit field controls when the RIS.TGT and RIS.ZERO interrupts are set.
// ENUMs:
// LATE                     RIS.TGT and RIS.ZERO are set one timer clock cycle
//                          after CNTR = TARGET/ZERO.
// EARLY                    RIS.TGT and RIS.ZERO are set one system clock
//                          cycle after CNTR = TARGET/ZERO.
#define LGPT_CTL_INTP                                              0x00000020U
#define LGPT_CTL_INTP_M                                            0x00000020U
#define LGPT_CTL_INTP_S                                                     5U
#define LGPT_CTL_INTP_LATE                                         0x00000020U
#define LGPT_CTL_INTP_EARLY                                        0x00000000U

// Field:   [4:3] CMPDIR
//
// Compare direction.
//
// This bit field controls the direction the counter must have in order to set
// the [RIS.CnCC] channel interrupts. This bitfield is only relevant if
// [CnCFG.CCACT] is configured to a compare action.
// ENUMs:
// RESERVED                 RESERVED
// DOWN                     Compare RIS fields are only set on down count.
// UP                       Compare RIS fields are only set on up count.
// BOTH                     Compare RIS fields are set on up count and down
//                          count.
#define LGPT_CTL_CMPDIR_W                                                   2U
#define LGPT_CTL_CMPDIR_M                                          0x00000018U
#define LGPT_CTL_CMPDIR_S                                                   3U
#define LGPT_CTL_CMPDIR_RESERVED                                   0x00000018U
#define LGPT_CTL_CMPDIR_DOWN                                       0x00000010U
#define LGPT_CTL_CMPDIR_UP                                         0x00000008U
#define LGPT_CTL_CMPDIR_BOTH                                       0x00000000U

// Field:   [2:0] MODE
//
// Timer mode control
//
// The CNTR restarts from 0 when MODE is written to UP_ONCE, UP_PER, UPDWN_PER,
// QDEC, SYNC_UP_ONCE, SYNC_UP_PER or SYNC_UPDWN_PER.
//
// When writing MODE all internally queued updates to the channels and TGT is
// cleared.
//
// When configuring the timer, MODE should be the last thing to configure. If
// changing timer configuration after MODE has been set is necessary,
// instructions, if any, given in the configuration registers should be
// followed. See for example C0CFG.
// ENUMs:
// SYNC_UPDWN_PER           Start counting up and down periodically
//                          synchronous to another LGPT,  selected within
//                          STARTCFG. The timer is started by setting
//                          CTL.MODE = UPDWN_PER automatically.
//                          It then operates as a
//                          normal timer in CTL.MODE = UPDWN_PER, counting
//                          from 0 to target value and back to 0,
//                          repeatedly.
//
//                          Period =  (target value *
//                          2) * timer clock period
// SYNC_UP_PER              Start counting up periodically synchronous to
//                          another LGPT,  selected within STARTCFG. The
//                          timer is started by setting CTL.MODE = UP_PER
//                          automatically.
//                          It then operates as a
//                          normal timer in CTL.MODE = UP_PER, incrementing
//                          from 0 to target value, repeatedly.
//
//                          Period =  (target value *
//                          2) * timer clock period
// SYNC_UP_ONCE             Start counting up once synchronous to another
//                          LGPT, selected within STARTCFG. The timer is
//                          started by setting CTL.MODE = UP_ONCE
//                          automatically.
//                          It then functions as a
//                          normal timer in CTL.MODE = UP_ONCE,
//                          incrementing from 0 to target value,  then
//                          stops and sets MODE to DIS.
// QDEC                     The timer functions as a quadrature decoder. IOC
//                          input 0, IOC input 1 and IOC input 2 are used
//                          respectivly as PHA, PHB and IDX inputs. IDX can
//                          be turned off by setting C2CFG.EDGE = NONE.
//                          The timer clock frequency
//                          sets the sample rate of the QDEC logic. This
//                          frequency can be configured in PRECFG.
// UPDWN_PER                Count up and down periodically. The timer counts
//                          from 0 to target value and back to 0,
//                          repeatedly.
//
//                          Period =  (target value *
//                          2) * timer clock period
// UP_PER                   Count up periodically. The timer increments from 0
//                          to target value, repeatedly.
//
//                          Period = (target value +
//                          1) * timer clock period
// UP_ONCE                  Count up once. The timer increments from 0 to
//                          target value,  then stops and sets MODE to DIS.
// DIS                      Disable timer. Updates to counter, channels, and
//                          events stop.
#define LGPT_CTL_MODE_W                                                     3U
#define LGPT_CTL_MODE_M                                            0x00000007U
#define LGPT_CTL_MODE_S                                                     0U
#define LGPT_CTL_MODE_SYNC_UPDWN_PER                               0x00000007U
#define LGPT_CTL_MODE_SYNC_UP_PER                                  0x00000006U
#define LGPT_CTL_MODE_SYNC_UP_ONCE                                 0x00000005U
#define LGPT_CTL_MODE_QDEC                                         0x00000004U
#define LGPT_CTL_MODE_UPDWN_PER                                    0x00000003U
#define LGPT_CTL_MODE_UP_PER                                       0x00000002U
#define LGPT_CTL_MODE_UP_ONCE                                      0x00000001U
#define LGPT_CTL_MODE_DIS                                          0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_OUTCTL
//
//*****************************************************************************
// Field:     [5] SETOUT2
//
// Set output 2.
//
// Write 1 to set output 2.
#define LGPT_OUTCTL_SETOUT2                                        0x00000020U
#define LGPT_OUTCTL_SETOUT2_M                                      0x00000020U
#define LGPT_OUTCTL_SETOUT2_S                                               5U

// Field:     [4] CLROUT2
//
// Clear output 2.
//
// Write 1 to clear output 2.
#define LGPT_OUTCTL_CLROUT2                                        0x00000010U
#define LGPT_OUTCTL_CLROUT2_M                                      0x00000010U
#define LGPT_OUTCTL_CLROUT2_S                                               4U

// Field:     [3] SETOUT1
//
// Set output 1.
//
// Write 1 to set output 1.
#define LGPT_OUTCTL_SETOUT1                                        0x00000008U
#define LGPT_OUTCTL_SETOUT1_M                                      0x00000008U
#define LGPT_OUTCTL_SETOUT1_S                                               3U

// Field:     [2] CLROUT1
//
// Clear output 1.
//
// Write 1 to clear output 1.
#define LGPT_OUTCTL_CLROUT1                                        0x00000004U
#define LGPT_OUTCTL_CLROUT1_M                                      0x00000004U
#define LGPT_OUTCTL_CLROUT1_S                                               2U

// Field:     [1] SETOUT0
//
// Set output 0.
//
// Write 1 to set output 0.
#define LGPT_OUTCTL_SETOUT0                                        0x00000002U
#define LGPT_OUTCTL_SETOUT0_M                                      0x00000002U
#define LGPT_OUTCTL_SETOUT0_S                                               1U

// Field:     [0] CLROUT0
//
// Clear output 0.
//
// Write 1 to clear output 0.
#define LGPT_OUTCTL_CLROUT0                                        0x00000001U
#define LGPT_OUTCTL_CLROUT0_M                                      0x00000001U
#define LGPT_OUTCTL_CLROUT0_S                                               0U

//*****************************************************************************
//
// Register: LGPT_O_CNTR
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Current counter value.
// If CTL.MODE = QDEC this can be used to set the initial counter value during
// QDEC.  Writing to CNTR in other modes than QDEC is possible, but may result
// in unpredictable behavior.
#define LGPT_CNTR_VAL_W                                                    16U
#define LGPT_CNTR_VAL_M                                            0x0000FFFFU
#define LGPT_CNTR_VAL_S                                                     0U

//*****************************************************************************
//
// Register: LGPT_O_PRECFG
//
//*****************************************************************************
// Field:  [15:8] TICKDIV
//
// Tick division.
//
// TICKDIV determines the timer clock frequency for the counter, and timer
// output updates. The timer clock frequency is the clock selected by TICKSRC
// divided by (TICKDIV + 1). This inverse is the timer clock period.
//
// 0x00: Divide by 1.
// 0x01: Divide by 2.
// ...
// 0xFF: Divide by 256.
#define LGPT_PRECFG_TICKDIV_W                                               8U
#define LGPT_PRECFG_TICKDIV_M                                      0x0000FF00U
#define LGPT_PRECFG_TICKDIV_S                                               8U

// Field:   [1:0] TICKSRC
//
// Prescaler tick source.
//
// TICKSRC determines the source which decrements the prescaler.
// ENUMs:
// BOTH_TICK                Prescaler is updated at both edges of TICKEN.
// FALL_TICK                Prescaler is updated at the falling edge of
//                          TICKEN.
// RISE_TICK                Prescaler is updated at the rising edge of TICKEN.
// CLK                      Prescaler is updated at the system clock.
#define LGPT_PRECFG_TICKSRC_W                                               2U
#define LGPT_PRECFG_TICKSRC_M                                      0x00000003U
#define LGPT_PRECFG_TICKSRC_S                                               0U
#define LGPT_PRECFG_TICKSRC_BOTH_TICK                              0x00000003U
#define LGPT_PRECFG_TICKSRC_FALL_TICK                              0x00000002U
#define LGPT_PRECFG_TICKSRC_RISE_TICK                              0x00000001U
#define LGPT_PRECFG_TICKSRC_CLK                                    0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_PREEVENT
//
//*****************************************************************************
// Field:   [7:0] VAL
//
// Sets the HIGH time of the prescaler event output.
//
// Event goes high when the prescaler counter equals VAL. Event goes low when
// prescaler counter is 0.
//
// Note:
// - Can be used to precharge or turn an external component on for a short time
// before sampling, like in QDEC.
// - If there is a requirement to create such events that have very short
// periods compared to timer clock period, use two timers. One timer acts as
// prescaler and event generator for another timer.
#define LGPT_PREEVENT_VAL_W                                                 8U
#define LGPT_PREEVENT_VAL_M                                        0x000000FFU
#define LGPT_PREEVENT_VAL_S                                                 0U

//*****************************************************************************
//
// Register: LGPT_O_CHFILT
//
//*****************************************************************************
// Field:  [15:8] LOAD
//
// The input of the channel filter is passed to the edge detection logic after
// LOAD + 1 consecutive equal samples.
#define LGPT_CHFILT_LOAD_W                                                  8U
#define LGPT_CHFILT_LOAD_M                                         0x0000FF00U
#define LGPT_CHFILT_LOAD_S                                                  8U

// Field:   [1:0] MODE
//
// Channel filter mode
// ENUMs:
// TIMERCLK                 Filter is clocked by timer clock.
// TICKSRC                  Filter is clocked by PRECFG.TICKSRC.
// CLK                      Filter is clocked by system clock.
// BYPASS                   Filter is bypassed. No Filter is used.
#define LGPT_CHFILT_MODE_W                                                  2U
#define LGPT_CHFILT_MODE_M                                         0x00000003U
#define LGPT_CHFILT_MODE_S                                                  0U
#define LGPT_CHFILT_MODE_TIMERCLK                                  0x00000003U
#define LGPT_CHFILT_MODE_TICKSRC                                   0x00000002U
#define LGPT_CHFILT_MODE_CLK                                       0x00000001U
#define LGPT_CHFILT_MODE_BYPASS                                    0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_QDECSTAT
//
//*****************************************************************************
// Field:     [1] DBLTRANS
//
// Double transition
// ENUMs:
// DBL                      Double transition on phase inputs.
// NONE                     Single or no transition on phase inputs.
#define LGPT_QDECSTAT_DBLTRANS                                     0x00000002U
#define LGPT_QDECSTAT_DBLTRANS_M                                   0x00000002U
#define LGPT_QDECSTAT_DBLTRANS_S                                            1U
#define LGPT_QDECSTAT_DBLTRANS_DBL                                 0x00000002U
#define LGPT_QDECSTAT_DBLTRANS_NONE                                0x00000000U

// Field:     [0] QDIR
//
// Direction of count during QDEC mode.
// ENUMs:
// DOWN                     Down (PHB leads PHA)
// UP                       Up (PHA leads PHB)
#define LGPT_QDECSTAT_QDIR                                         0x00000001U
#define LGPT_QDECSTAT_QDIR_M                                       0x00000001U
#define LGPT_QDECSTAT_QDIR_S                                                0U
#define LGPT_QDECSTAT_QDIR_DOWN                                    0x00000001U
#define LGPT_QDECSTAT_QDIR_UP                                      0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_IRGEN
//
//*****************************************************************************
// Field:     [0] CTL
//
// Control
// ENUMs:
// EN                       Enable.
// DIS                      Disable.
#define LGPT_IRGEN_CTL                                             0x00000001U
#define LGPT_IRGEN_CTL_M                                           0x00000001U
#define LGPT_IRGEN_CTL_S                                                    0U
#define LGPT_IRGEN_CTL_EN                                          0x00000001U
#define LGPT_IRGEN_CTL_DIS                                         0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_DMA
//
//*****************************************************************************
// Field: [19:16] RWCNTR
//
// The read/write counter. RWCNTR+1 is the number of times the DMA can access
// (read/write) the DMARW register. For each DMA access to DMARW an internal
// counter is incremented, writing to the next address field. RWADDR + 4*RWCNTR
// is the final register address which can be accessed by the DMA.
#define LGPT_DMA_RWCNTR_W                                                   4U
#define LGPT_DMA_RWCNTR_M                                          0x000F0000U
#define LGPT_DMA_RWCNTR_S                                                  16U

// Field:  [14:8] RWADDR
//
// The base address which the DMA access when reading/writing DMARW.  The base
// address is set by taking the 9 LSB of the physical address and divide by 4.
// For example, if you wanted the RWADDR to point to the PTGT register you
// should set RWADDR = 0x0FC/4.
#define LGPT_DMA_RWADDR_W                                                   7U
#define LGPT_DMA_RWADDR_M                                          0x00007F00U
#define LGPT_DMA_RWADDR_S                                                   8U

// Field:   [3:0] REQ
//
// ENUMs:
// C11CC                    Setting of RIS.C11CC generates a DMA request.
// C10CC                    Setting of RIS.C10CC generates a DMA request.
// C9CC                     Setting of RIS.C9CC generates a DMA request.
// C8CC                     Setting of RIS.C8CC generates a DMA request.
// C7CC                     Setting of RIS.C7CC generates a DMA request.
// C6CC                     Setting of RIS.C6CC generates a DMA request.
// C5CC                     Setting of RIS.C5CC generates a DMA request.
// C4CC                     Setting of RIS.C4CC generates a DMA request.
// C3CC                     Setting of RIS.C3CC generates a DMA request.
// C2CC                     Setting of RIS.C2CC generates a DMA request.
// C1CC                     Setting of RIS.C1CC generates a DMA request.
// C0CC                     Setting of RIS.C0CC generates a DMA request.
// FAULT                    Setting of RIS.FAULT generates a DMA request.
// ZERO                     Setting of RIS.ZERO generates a DMA request.
// TGT                      Setting of RIS.TGT generates a DMA request.
// DIS                      Disabled
#define LGPT_DMA_REQ_W                                                      4U
#define LGPT_DMA_REQ_M                                             0x0000000FU
#define LGPT_DMA_REQ_S                                                      0U
#define LGPT_DMA_REQ_C11CC                                         0x0000000FU
#define LGPT_DMA_REQ_C10CC                                         0x0000000EU
#define LGPT_DMA_REQ_C9CC                                          0x0000000DU
#define LGPT_DMA_REQ_C8CC                                          0x0000000CU
#define LGPT_DMA_REQ_C7CC                                          0x0000000BU
#define LGPT_DMA_REQ_C6CC                                          0x0000000AU
#define LGPT_DMA_REQ_C5CC                                          0x00000009U
#define LGPT_DMA_REQ_C4CC                                          0x00000008U
#define LGPT_DMA_REQ_C3CC                                          0x00000007U
#define LGPT_DMA_REQ_C2CC                                          0x00000006U
#define LGPT_DMA_REQ_C1CC                                          0x00000005U
#define LGPT_DMA_REQ_C0CC                                          0x00000004U
#define LGPT_DMA_REQ_FAULT                                         0x00000003U
#define LGPT_DMA_REQ_ZERO                                          0x00000002U
#define LGPT_DMA_REQ_TGT                                           0x00000001U
#define LGPT_DMA_REQ_DIS                                           0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_DMARW
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// DMA read write value.
//
// The value that is read/written from/to the registers.
#define LGPT_DMARW_VAL_W                                                   16U
#define LGPT_DMARW_VAL_M                                           0x0000FFFFU
#define LGPT_DMARW_VAL_S                                                    0U

//*****************************************************************************
//
// Register: LGPT_O_ADCTRG
//
//*****************************************************************************
// Field:   [3:0] SRC
//
// ENUMs:
// C11CC                    Setting of RIS.C11CC generates an ADC trigger.
// C10CC                    Setting of RIS.C10CC generates an ADC trigger.
// C9CC                     Setting of RIS.C9CC generates an ADC trigger.
// C8CC                     Setting of RIS.C8CC generates an ADC trigger.
// C7CC                     Setting of RIS.C7CC generates an ADC trigger.
// C6CC                     Setting of RIS.C6CC generates an ADC trigger.
// C5CC                     Setting of RIS.C5CC generates an ADC trigger.
// C4CC                     Setting of RIS.C4CC generates an ADC trigger.
// C3CC                     Setting of RIS.C3CC generates an ADC trigger.
// C2CC                     Setting of RIS.C2CC generates an ADC trigger.
// C1CC                     Setting of RIS.C1CC generates an ADC trigger.
// C0CC                     Setting of RIS.C0CC generates an ADC trigger.
// FAULT                    Setting of RIS.FAULT generates an ADC trigger.
// ZERO                     Setting of RIS.ZERO generates an ADC trigger.
// TGT                      Setting of RIS.TGT generates an ADC trigger.
// DIS                      Disabled
#define LGPT_ADCTRG_SRC_W                                                   4U
#define LGPT_ADCTRG_SRC_M                                          0x0000000FU
#define LGPT_ADCTRG_SRC_S                                                   0U
#define LGPT_ADCTRG_SRC_C11CC                                      0x0000000FU
#define LGPT_ADCTRG_SRC_C10CC                                      0x0000000EU
#define LGPT_ADCTRG_SRC_C9CC                                       0x0000000DU
#define LGPT_ADCTRG_SRC_C8CC                                       0x0000000CU
#define LGPT_ADCTRG_SRC_C7CC                                       0x0000000BU
#define LGPT_ADCTRG_SRC_C6CC                                       0x0000000AU
#define LGPT_ADCTRG_SRC_C5CC                                       0x00000009U
#define LGPT_ADCTRG_SRC_C4CC                                       0x00000008U
#define LGPT_ADCTRG_SRC_C3CC                                       0x00000007U
#define LGPT_ADCTRG_SRC_C2CC                                       0x00000006U
#define LGPT_ADCTRG_SRC_C1CC                                       0x00000005U
#define LGPT_ADCTRG_SRC_C0CC                                       0x00000004U
#define LGPT_ADCTRG_SRC_FAULT                                      0x00000003U
#define LGPT_ADCTRG_SRC_ZERO                                       0x00000002U
#define LGPT_ADCTRG_SRC_TGT                                        0x00000001U
#define LGPT_ADCTRG_SRC_DIS                                        0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_IOCTL
//
//*****************************************************************************
// Field: [11:10] COUT2
//
// IO complementary output 2 control
//
// This bit field controls IO complementary output 2.
// ENUMs:
// INV                      Inverted value. The IO complementary output is
//                          inverted.
// HIGH                     Driven high. The IO complementary output is driven
//                          high.
// LOW                      Driven low. The IO complementary output is driven
//                          low.
// NRM                      Normal output. The IO complementary output is not
//                          changed.
#define LGPT_IOCTL_COUT2_W                                                  2U
#define LGPT_IOCTL_COUT2_M                                         0x00000C00U
#define LGPT_IOCTL_COUT2_S                                                 10U
#define LGPT_IOCTL_COUT2_INV                                       0x00000C00U
#define LGPT_IOCTL_COUT2_HIGH                                      0x00000800U
#define LGPT_IOCTL_COUT2_LOW                                       0x00000400U
#define LGPT_IOCTL_COUT2_NRM                                       0x00000000U

// Field:   [9:8] OUT2
//
// IO output 2 control
//
// This bit field controls IO output 2.
// ENUMs:
// INV                      Inverted value. The IO output is inverted.
// HIGH                     Driven high. The IO output is driven high.
// LOW                      Driven low. The IO output is driven low.
// NRM                      Normal output. The IO output is not changed.
#define LGPT_IOCTL_OUT2_W                                                   2U
#define LGPT_IOCTL_OUT2_M                                          0x00000300U
#define LGPT_IOCTL_OUT2_S                                                   8U
#define LGPT_IOCTL_OUT2_INV                                        0x00000300U
#define LGPT_IOCTL_OUT2_HIGH                                       0x00000200U
#define LGPT_IOCTL_OUT2_LOW                                        0x00000100U
#define LGPT_IOCTL_OUT2_NRM                                        0x00000000U

// Field:   [7:6] COUT1
//
// IO complementary output 1 control
//
// This bit field controls IO complementary output 1.
// ENUMs:
// INV                      Inverted value. The IO complementary output is
//                          inverted.
// HIGH                     Driven high. The IO complementary output is driven
//                          high.
// LOW                      Driven low. The IO complementary output is driven
//                          low.
// NRM                      Normal output. The IO complementary output is not
//                          changed.
#define LGPT_IOCTL_COUT1_W                                                  2U
#define LGPT_IOCTL_COUT1_M                                         0x000000C0U
#define LGPT_IOCTL_COUT1_S                                                  6U
#define LGPT_IOCTL_COUT1_INV                                       0x000000C0U
#define LGPT_IOCTL_COUT1_HIGH                                      0x00000080U
#define LGPT_IOCTL_COUT1_LOW                                       0x00000040U
#define LGPT_IOCTL_COUT1_NRM                                       0x00000000U

// Field:   [5:4] OUT1
//
// IO output 1 control
//
// This bit field controls IO output 1.
// ENUMs:
// INV                      Inverted value. The IO output is inverted.
// HIGH                     Driven high. The IO output is driven high.
// LOW                      Driven low. The IO output is driven low.
// NRM                      Normal output. The IO output is not changed.
#define LGPT_IOCTL_OUT1_W                                                   2U
#define LGPT_IOCTL_OUT1_M                                          0x00000030U
#define LGPT_IOCTL_OUT1_S                                                   4U
#define LGPT_IOCTL_OUT1_INV                                        0x00000030U
#define LGPT_IOCTL_OUT1_HIGH                                       0x00000020U
#define LGPT_IOCTL_OUT1_LOW                                        0x00000010U
#define LGPT_IOCTL_OUT1_NRM                                        0x00000000U

// Field:   [3:2] COUT0
//
// IO complementary output 0 control
//
// This bit field controls IO complementary output 0.
// ENUMs:
// INV                      Inverted value. The IO complementary output is
//                          inverted.
// HIGH                     Driven high. The IO complementary output is driven
//                          high.
// LOW                      Driven low. The IO complementary output is driven
//                          low.
// NRM                      Normal output. The IO complementary output is not
//                          changed.
#define LGPT_IOCTL_COUT0_W                                                  2U
#define LGPT_IOCTL_COUT0_M                                         0x0000000CU
#define LGPT_IOCTL_COUT0_S                                                  2U
#define LGPT_IOCTL_COUT0_INV                                       0x0000000CU
#define LGPT_IOCTL_COUT0_HIGH                                      0x00000008U
#define LGPT_IOCTL_COUT0_LOW                                       0x00000004U
#define LGPT_IOCTL_COUT0_NRM                                       0x00000000U

// Field:   [1:0] OUT0
//
// IO output 0 control
//
// This bit field controls IO output 0.
// ENUMs:
// INV                      Inverted value. The IO output is inverted.
// HIGH                     Driven high. The IO output is driven high.
// LOW                      Driven low. The IO output is driven low.
// NRM                      Normal output. The IO output is not changed.
#define LGPT_IOCTL_OUT0_W                                                   2U
#define LGPT_IOCTL_OUT0_M                                          0x00000003U
#define LGPT_IOCTL_OUT0_S                                                   0U
#define LGPT_IOCTL_OUT0_INV                                        0x00000003U
#define LGPT_IOCTL_OUT0_HIGH                                       0x00000002U
#define LGPT_IOCTL_OUT0_LOW                                        0x00000001U
#define LGPT_IOCTL_OUT0_NRM                                        0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_IMASK
//
//*****************************************************************************
// Field:    [10] C2CC
//
// Enable RIS.C2CC interrupt.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define LGPT_IMASK_C2CC                                            0x00000400U
#define LGPT_IMASK_C2CC_M                                          0x00000400U
#define LGPT_IMASK_C2CC_S                                                  10U
#define LGPT_IMASK_C2CC_EN                                         0x00000400U
#define LGPT_IMASK_C2CC_DIS                                        0x00000000U

// Field:     [9] C1CC
//
// Enable RIS.C1CC interrupt.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define LGPT_IMASK_C1CC                                            0x00000200U
#define LGPT_IMASK_C1CC_M                                          0x00000200U
#define LGPT_IMASK_C1CC_S                                                   9U
#define LGPT_IMASK_C1CC_EN                                         0x00000200U
#define LGPT_IMASK_C1CC_DIS                                        0x00000000U

// Field:     [8] C0CC
//
// Enable RIS.C0CC interrupt.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define LGPT_IMASK_C0CC                                            0x00000100U
#define LGPT_IMASK_C0CC_M                                          0x00000100U
#define LGPT_IMASK_C0CC_S                                                   8U
#define LGPT_IMASK_C0CC_EN                                         0x00000100U
#define LGPT_IMASK_C0CC_DIS                                        0x00000000U

// Field:     [6] FAULT
//
// Enable RIS.FAULT interrupt.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define LGPT_IMASK_FAULT                                           0x00000040U
#define LGPT_IMASK_FAULT_M                                         0x00000040U
#define LGPT_IMASK_FAULT_S                                                  6U
#define LGPT_IMASK_FAULT_EN                                        0x00000040U
#define LGPT_IMASK_FAULT_DIS                                       0x00000000U

// Field:     [5] IDX
//
// Enable RIS.IDX interrupt.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define LGPT_IMASK_IDX                                             0x00000020U
#define LGPT_IMASK_IDX_M                                           0x00000020U
#define LGPT_IMASK_IDX_S                                                    5U
#define LGPT_IMASK_IDX_EN                                          0x00000020U
#define LGPT_IMASK_IDX_DIS                                         0x00000000U

// Field:     [4] DIRCHNG
//
// Enable RIS.DIRCHNG interrupt.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define LGPT_IMASK_DIRCHNG                                         0x00000010U
#define LGPT_IMASK_DIRCHNG_M                                       0x00000010U
#define LGPT_IMASK_DIRCHNG_S                                                4U
#define LGPT_IMASK_DIRCHNG_EN                                      0x00000010U
#define LGPT_IMASK_DIRCHNG_DIS                                     0x00000000U

// Field:     [3] CNTRCHNG
//
// Enable RIS.CNTRCHNG interrupt.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define LGPT_IMASK_CNTRCHNG                                        0x00000008U
#define LGPT_IMASK_CNTRCHNG_M                                      0x00000008U
#define LGPT_IMASK_CNTRCHNG_S                                               3U
#define LGPT_IMASK_CNTRCHNG_EN                                     0x00000008U
#define LGPT_IMASK_CNTRCHNG_DIS                                    0x00000000U

// Field:     [2] DBLTRANS
//
// Enable RIS.DBLTRANS interrupt.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define LGPT_IMASK_DBLTRANS                                        0x00000004U
#define LGPT_IMASK_DBLTRANS_M                                      0x00000004U
#define LGPT_IMASK_DBLTRANS_S                                               2U
#define LGPT_IMASK_DBLTRANS_EN                                     0x00000004U
#define LGPT_IMASK_DBLTRANS_DIS                                    0x00000000U

// Field:     [1] ZERO
//
// Enable RIS.ZERO interrupt.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define LGPT_IMASK_ZERO                                            0x00000002U
#define LGPT_IMASK_ZERO_M                                          0x00000002U
#define LGPT_IMASK_ZERO_S                                                   1U
#define LGPT_IMASK_ZERO_EN                                         0x00000002U
#define LGPT_IMASK_ZERO_DIS                                        0x00000000U

// Field:     [0] TGT
//
// Enable RIS.TGT interrupt.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define LGPT_IMASK_TGT                                             0x00000001U
#define LGPT_IMASK_TGT_M                                           0x00000001U
#define LGPT_IMASK_TGT_S                                                    0U
#define LGPT_IMASK_TGT_EN                                          0x00000001U
#define LGPT_IMASK_TGT_DIS                                         0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_RIS
//
//*****************************************************************************
// Field:    [10] C2CC
//
// Status of the C2CC interrupt. The interrupt is set when C2CC has capture or
// compare event.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_RIS_C2CC                                              0x00000400U
#define LGPT_RIS_C2CC_M                                            0x00000400U
#define LGPT_RIS_C2CC_S                                                    10U
#define LGPT_RIS_C2CC_SET                                          0x00000400U
#define LGPT_RIS_C2CC_CLR                                          0x00000000U

// Field:     [9] C1CC
//
// Status of the C1CC interrupt. The interrupt is set when C1CC has capture or
// compare event.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_RIS_C1CC                                              0x00000200U
#define LGPT_RIS_C1CC_M                                            0x00000200U
#define LGPT_RIS_C1CC_S                                                     9U
#define LGPT_RIS_C1CC_SET                                          0x00000200U
#define LGPT_RIS_C1CC_CLR                                          0x00000000U

// Field:     [8] C0CC
//
// Status of the C0CC interrupt. The interrupt is set when C0CC has capture or
// compare event.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_RIS_C0CC                                              0x00000100U
#define LGPT_RIS_C0CC_M                                            0x00000100U
#define LGPT_RIS_C0CC_S                                                     8U
#define LGPT_RIS_C0CC_SET                                          0x00000100U
#define LGPT_RIS_C0CC_CLR                                          0x00000000U

// Field:     [6] FAULT
//
// Status of the FAULT interrupt. The interrupt is set immediately on active
// fault input.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_RIS_FAULT                                             0x00000040U
#define LGPT_RIS_FAULT_M                                           0x00000040U
#define LGPT_RIS_FAULT_S                                                    6U
#define LGPT_RIS_FAULT_SET                                         0x00000040U
#define LGPT_RIS_FAULT_CLR                                         0x00000000U

// Field:     [5] IDX
//
// Status of the IDX interrupt. The interrupt is set when IDX is active.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_RIS_IDX                                               0x00000020U
#define LGPT_RIS_IDX_M                                             0x00000020U
#define LGPT_RIS_IDX_S                                                      5U
#define LGPT_RIS_IDX_SET                                           0x00000020U
#define LGPT_RIS_IDX_CLR                                           0x00000000U

// Field:     [4] DIRCHNG
//
// Status of the DIRCHNG interrupt. The interrupt is set when the direction of
// the counter changes.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_RIS_DIRCHNG                                           0x00000010U
#define LGPT_RIS_DIRCHNG_M                                         0x00000010U
#define LGPT_RIS_DIRCHNG_S                                                  4U
#define LGPT_RIS_DIRCHNG_SET                                       0x00000010U
#define LGPT_RIS_DIRCHNG_CLR                                       0x00000000U

// Field:     [3] CNTRCHNG
//
// Status of the CNTRCHNG interrupt. The interrupt is set when the counter
// increments or decrements.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_RIS_CNTRCHNG                                          0x00000008U
#define LGPT_RIS_CNTRCHNG_M                                        0x00000008U
#define LGPT_RIS_CNTRCHNG_S                                                 3U
#define LGPT_RIS_CNTRCHNG_SET                                      0x00000008U
#define LGPT_RIS_CNTRCHNG_CLR                                      0x00000000U

// Field:     [2] DBLTRANS
//
// Status of the DBLTRANS interrupt. The interrupt is set when a double
// transition has happened during QDEC mode.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_RIS_DBLTRANS                                          0x00000004U
#define LGPT_RIS_DBLTRANS_M                                        0x00000004U
#define LGPT_RIS_DBLTRANS_S                                                 2U
#define LGPT_RIS_DBLTRANS_SET                                      0x00000004U
#define LGPT_RIS_DBLTRANS_CLR                                      0x00000000U

// Field:     [1] ZERO
//
// Status of the ZERO interrupt. The interrupt is set when CNTR = 0.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_RIS_ZERO                                              0x00000002U
#define LGPT_RIS_ZERO_M                                            0x00000002U
#define LGPT_RIS_ZERO_S                                                     1U
#define LGPT_RIS_ZERO_SET                                          0x00000002U
#define LGPT_RIS_ZERO_CLR                                          0x00000000U

// Field:     [0] TGT
//
// Status of the TGT interrupt. The interrupt is set when CNTR = TGT.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_RIS_TGT                                               0x00000001U
#define LGPT_RIS_TGT_M                                             0x00000001U
#define LGPT_RIS_TGT_S                                                      0U
#define LGPT_RIS_TGT_SET                                           0x00000001U
#define LGPT_RIS_TGT_CLR                                           0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_MIS
//
//*****************************************************************************
// Field:    [10] C2CC
//
// Masked status of the RIS.C2CC interrupt.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_MIS_C2CC                                              0x00000400U
#define LGPT_MIS_C2CC_M                                            0x00000400U
#define LGPT_MIS_C2CC_S                                                    10U
#define LGPT_MIS_C2CC_SET                                          0x00000400U
#define LGPT_MIS_C2CC_CLR                                          0x00000000U

// Field:     [9] C1CC
//
// Masked status of the RIS.C1CC interrupt.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_MIS_C1CC                                              0x00000200U
#define LGPT_MIS_C1CC_M                                            0x00000200U
#define LGPT_MIS_C1CC_S                                                     9U
#define LGPT_MIS_C1CC_SET                                          0x00000200U
#define LGPT_MIS_C1CC_CLR                                          0x00000000U

// Field:     [8] C0CC
//
// Masked status of the RIS.C0CC interrupt.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_MIS_C0CC                                              0x00000100U
#define LGPT_MIS_C0CC_M                                            0x00000100U
#define LGPT_MIS_C0CC_S                                                     8U
#define LGPT_MIS_C0CC_SET                                          0x00000100U
#define LGPT_MIS_C0CC_CLR                                          0x00000000U

// Field:     [6] FAULT
//
// Masked status of the RIS.FAULT interrupt.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_MIS_FAULT                                             0x00000040U
#define LGPT_MIS_FAULT_M                                           0x00000040U
#define LGPT_MIS_FAULT_S                                                    6U
#define LGPT_MIS_FAULT_SET                                         0x00000040U
#define LGPT_MIS_FAULT_CLR                                         0x00000000U

// Field:     [5] IDX
//
// Masked status of the RIS.IDX interrupt.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_MIS_IDX                                               0x00000020U
#define LGPT_MIS_IDX_M                                             0x00000020U
#define LGPT_MIS_IDX_S                                                      5U
#define LGPT_MIS_IDX_SET                                           0x00000020U
#define LGPT_MIS_IDX_CLR                                           0x00000000U

// Field:     [4] DIRCHNG
//
// Masked status of the RIS.DIRCHNG interrupt.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_MIS_DIRCHNG                                           0x00000010U
#define LGPT_MIS_DIRCHNG_M                                         0x00000010U
#define LGPT_MIS_DIRCHNG_S                                                  4U
#define LGPT_MIS_DIRCHNG_SET                                       0x00000010U
#define LGPT_MIS_DIRCHNG_CLR                                       0x00000000U

// Field:     [3] CNTRCHNG
//
// Masked status of the RIS.CNTRCHNG interrupt.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_MIS_CNTRCHNG                                          0x00000008U
#define LGPT_MIS_CNTRCHNG_M                                        0x00000008U
#define LGPT_MIS_CNTRCHNG_S                                                 3U
#define LGPT_MIS_CNTRCHNG_SET                                      0x00000008U
#define LGPT_MIS_CNTRCHNG_CLR                                      0x00000000U

// Field:     [2] DBLTRANS
//
// Masked status of the RIS.DBLTRANS interrupt.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_MIS_DBLTRANS                                          0x00000004U
#define LGPT_MIS_DBLTRANS_M                                        0x00000004U
#define LGPT_MIS_DBLTRANS_S                                                 2U
#define LGPT_MIS_DBLTRANS_SET                                      0x00000004U
#define LGPT_MIS_DBLTRANS_CLR                                      0x00000000U

// Field:     [1] ZERO
//
// Masked status of the RIS.ZERO interrupt.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_MIS_ZERO                                              0x00000002U
#define LGPT_MIS_ZERO_M                                            0x00000002U
#define LGPT_MIS_ZERO_S                                                     1U
#define LGPT_MIS_ZERO_SET                                          0x00000002U
#define LGPT_MIS_ZERO_CLR                                          0x00000000U

// Field:     [0] TGT
//
// Masked status of the RIS.TGT interrupt.
// ENUMs:
// SET
// CLR                      Cleared
#define LGPT_MIS_TGT                                               0x00000001U
#define LGPT_MIS_TGT_M                                             0x00000001U
#define LGPT_MIS_TGT_S                                                      0U
#define LGPT_MIS_TGT_SET                                           0x00000001U
#define LGPT_MIS_TGT_CLR                                           0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_ISET
//
//*****************************************************************************
// Field:    [10] C2CC
//
// Set the RIS.C2CC interrupt.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_ISET_C2CC                                             0x00000400U
#define LGPT_ISET_C2CC_M                                           0x00000400U
#define LGPT_ISET_C2CC_S                                                   10U
#define LGPT_ISET_C2CC_SET                                         0x00000400U
#define LGPT_ISET_C2CC_NO_EFFECT                                   0x00000000U

// Field:     [9] C1CC
//
// Set the RIS.C1CC interrupt.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_ISET_C1CC                                             0x00000200U
#define LGPT_ISET_C1CC_M                                           0x00000200U
#define LGPT_ISET_C1CC_S                                                    9U
#define LGPT_ISET_C1CC_SET                                         0x00000200U
#define LGPT_ISET_C1CC_NO_EFFECT                                   0x00000000U

// Field:     [8] C0CC
//
// Set the RIS.C0CC interrupt.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_ISET_C0CC                                             0x00000100U
#define LGPT_ISET_C0CC_M                                           0x00000100U
#define LGPT_ISET_C0CC_S                                                    8U
#define LGPT_ISET_C0CC_SET                                         0x00000100U
#define LGPT_ISET_C0CC_NO_EFFECT                                   0x00000000U

// Field:     [6] FAULT
//
// Set the RIS.FAULT interrupt.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_ISET_FAULT                                            0x00000040U
#define LGPT_ISET_FAULT_M                                          0x00000040U
#define LGPT_ISET_FAULT_S                                                   6U
#define LGPT_ISET_FAULT_SET                                        0x00000040U
#define LGPT_ISET_FAULT_NO_EFFECT                                  0x00000000U

// Field:     [5] IDX
//
// Set the RIS.IDX interrupt.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_ISET_IDX                                              0x00000020U
#define LGPT_ISET_IDX_M                                            0x00000020U
#define LGPT_ISET_IDX_S                                                     5U
#define LGPT_ISET_IDX_SET                                          0x00000020U
#define LGPT_ISET_IDX_NO_EFFECT                                    0x00000000U

// Field:     [4] DIRCHNG
//
// Set the RIS.DIRCHNG interrupt.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_ISET_DIRCHNG                                          0x00000010U
#define LGPT_ISET_DIRCHNG_M                                        0x00000010U
#define LGPT_ISET_DIRCHNG_S                                                 4U
#define LGPT_ISET_DIRCHNG_SET                                      0x00000010U
#define LGPT_ISET_DIRCHNG_NO_EFFECT                                0x00000000U

// Field:     [3] CNTRCHNG
//
// Set the RIS.CNTRCHNG interrupt.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_ISET_CNTRCHNG                                         0x00000008U
#define LGPT_ISET_CNTRCHNG_M                                       0x00000008U
#define LGPT_ISET_CNTRCHNG_S                                                3U
#define LGPT_ISET_CNTRCHNG_SET                                     0x00000008U
#define LGPT_ISET_CNTRCHNG_NO_EFFECT                               0x00000000U

// Field:     [2] DBLTRANS
//
// Set the RIS.DBLTRANS interrupt.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_ISET_DBLTRANS                                         0x00000004U
#define LGPT_ISET_DBLTRANS_M                                       0x00000004U
#define LGPT_ISET_DBLTRANS_S                                                2U
#define LGPT_ISET_DBLTRANS_SET                                     0x00000004U
#define LGPT_ISET_DBLTRANS_NO_EFFECT                               0x00000000U

// Field:     [1] ZERO
//
// Set the RIS.ZERO interrupt.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_ISET_ZERO                                             0x00000002U
#define LGPT_ISET_ZERO_M                                           0x00000002U
#define LGPT_ISET_ZERO_S                                                    1U
#define LGPT_ISET_ZERO_SET                                         0x00000002U
#define LGPT_ISET_ZERO_NO_EFFECT                                   0x00000000U

// Field:     [0] TGT
//
// Set the RIS.TGT interrupt.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_ISET_TGT                                              0x00000001U
#define LGPT_ISET_TGT_M                                            0x00000001U
#define LGPT_ISET_TGT_S                                                     0U
#define LGPT_ISET_TGT_SET                                          0x00000001U
#define LGPT_ISET_TGT_NO_EFFECT                                    0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_ICLR
//
//*****************************************************************************
// Field:    [10] C2CC
//
// Clear the RIS.C2CC interrupt.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_ICLR_C2CC                                             0x00000400U
#define LGPT_ICLR_C2CC_M                                           0x00000400U
#define LGPT_ICLR_C2CC_S                                                   10U
#define LGPT_ICLR_C2CC_CLR                                         0x00000400U
#define LGPT_ICLR_C2CC_NO_EFFECT                                   0x00000000U

// Field:     [9] C1CC
//
// Clear the RIS.C1CC interrupt.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_ICLR_C1CC                                             0x00000200U
#define LGPT_ICLR_C1CC_M                                           0x00000200U
#define LGPT_ICLR_C1CC_S                                                    9U
#define LGPT_ICLR_C1CC_CLR                                         0x00000200U
#define LGPT_ICLR_C1CC_NO_EFFECT                                   0x00000000U

// Field:     [8] C0CC
//
// Clear the RIS.C0CC interrupt.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_ICLR_C0CC                                             0x00000100U
#define LGPT_ICLR_C0CC_M                                           0x00000100U
#define LGPT_ICLR_C0CC_S                                                    8U
#define LGPT_ICLR_C0CC_CLR                                         0x00000100U
#define LGPT_ICLR_C0CC_NO_EFFECT                                   0x00000000U

// Field:     [6] FAULT
//
// Clear the RIS.FAULT interrupt.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_ICLR_FAULT                                            0x00000040U
#define LGPT_ICLR_FAULT_M                                          0x00000040U
#define LGPT_ICLR_FAULT_S                                                   6U
#define LGPT_ICLR_FAULT_CLR                                        0x00000040U
#define LGPT_ICLR_FAULT_NO_EFFECT                                  0x00000000U

// Field:     [5] IDX
//
// Clear the RIS.IDX interrupt.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_ICLR_IDX                                              0x00000020U
#define LGPT_ICLR_IDX_M                                            0x00000020U
#define LGPT_ICLR_IDX_S                                                     5U
#define LGPT_ICLR_IDX_CLR                                          0x00000020U
#define LGPT_ICLR_IDX_NO_EFFECT                                    0x00000000U

// Field:     [4] DIRCHNG
//
// Clear the RIS.DIRCHNG interrupt.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_ICLR_DIRCHNG                                          0x00000010U
#define LGPT_ICLR_DIRCHNG_M                                        0x00000010U
#define LGPT_ICLR_DIRCHNG_S                                                 4U
#define LGPT_ICLR_DIRCHNG_CLR                                      0x00000010U
#define LGPT_ICLR_DIRCHNG_NO_EFFECT                                0x00000000U

// Field:     [3] CNTRCHNG
//
// Clear the RIS.CNTRCHNG interrupt.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_ICLR_CNTRCHNG                                         0x00000008U
#define LGPT_ICLR_CNTRCHNG_M                                       0x00000008U
#define LGPT_ICLR_CNTRCHNG_S                                                3U
#define LGPT_ICLR_CNTRCHNG_CLR                                     0x00000008U
#define LGPT_ICLR_CNTRCHNG_NO_EFFECT                               0x00000000U

// Field:     [2] DBLTRANS
//
// Clear the RIS.DBLTRANS interrupt.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_ICLR_DBLTRANS                                         0x00000004U
#define LGPT_ICLR_DBLTRANS_M                                       0x00000004U
#define LGPT_ICLR_DBLTRANS_S                                                2U
#define LGPT_ICLR_DBLTRANS_CLR                                     0x00000004U
#define LGPT_ICLR_DBLTRANS_NO_EFFECT                               0x00000000U

// Field:     [1] ZERO
//
// Clear the RIS.ZERO interrupt.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_ICLR_ZERO                                             0x00000002U
#define LGPT_ICLR_ZERO_M                                           0x00000002U
#define LGPT_ICLR_ZERO_S                                                    1U
#define LGPT_ICLR_ZERO_CLR                                         0x00000002U
#define LGPT_ICLR_ZERO_NO_EFFECT                                   0x00000000U

// Field:     [0] TGT
//
// Clear the RIS.TGT interrupt.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_ICLR_TGT                                              0x00000001U
#define LGPT_ICLR_TGT_M                                            0x00000001U
#define LGPT_ICLR_TGT_S                                                     0U
#define LGPT_ICLR_TGT_CLR                                          0x00000001U
#define LGPT_ICLR_TGT_NO_EFFECT                                    0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_IMSET
//
//*****************************************************************************
// Field:    [10] C2CC
//
// Set the MIS.C2CC mask.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_IMSET_C2CC                                            0x00000400U
#define LGPT_IMSET_C2CC_M                                          0x00000400U
#define LGPT_IMSET_C2CC_S                                                  10U
#define LGPT_IMSET_C2CC_SET                                        0x00000400U
#define LGPT_IMSET_C2CC_NO_EFFECT                                  0x00000000U

// Field:     [9] C1CC
//
// Set the MIS.C1CC mask.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_IMSET_C1CC                                            0x00000200U
#define LGPT_IMSET_C1CC_M                                          0x00000200U
#define LGPT_IMSET_C1CC_S                                                   9U
#define LGPT_IMSET_C1CC_SET                                        0x00000200U
#define LGPT_IMSET_C1CC_NO_EFFECT                                  0x00000000U

// Field:     [8] C0CC
//
// Set the MIS.C0CC mask.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_IMSET_C0CC                                            0x00000100U
#define LGPT_IMSET_C0CC_M                                          0x00000100U
#define LGPT_IMSET_C0CC_S                                                   8U
#define LGPT_IMSET_C0CC_SET                                        0x00000100U
#define LGPT_IMSET_C0CC_NO_EFFECT                                  0x00000000U

// Field:     [6] FAULT
//
// Set the MIS.FAULT mask.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_IMSET_FAULT                                           0x00000040U
#define LGPT_IMSET_FAULT_M                                         0x00000040U
#define LGPT_IMSET_FAULT_S                                                  6U
#define LGPT_IMSET_FAULT_SET                                       0x00000040U
#define LGPT_IMSET_FAULT_NO_EFFECT                                 0x00000000U

// Field:     [5] IDX
//
// Set the MIS.IDX mask.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_IMSET_IDX                                             0x00000020U
#define LGPT_IMSET_IDX_M                                           0x00000020U
#define LGPT_IMSET_IDX_S                                                    5U
#define LGPT_IMSET_IDX_SET                                         0x00000020U
#define LGPT_IMSET_IDX_NO_EFFECT                                   0x00000000U

// Field:     [4] DIRCHNG
//
// Set the MIS.DIRCHNG mask.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_IMSET_DIRCHNG                                         0x00000010U
#define LGPT_IMSET_DIRCHNG_M                                       0x00000010U
#define LGPT_IMSET_DIRCHNG_S                                                4U
#define LGPT_IMSET_DIRCHNG_SET                                     0x00000010U
#define LGPT_IMSET_DIRCHNG_NO_EFFECT                               0x00000000U

// Field:     [3] CNTRCHNG
//
// Set the MIS.CNTRCHNG mask.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_IMSET_CNTRCHNG                                        0x00000008U
#define LGPT_IMSET_CNTRCHNG_M                                      0x00000008U
#define LGPT_IMSET_CNTRCHNG_S                                               3U
#define LGPT_IMSET_CNTRCHNG_SET                                    0x00000008U
#define LGPT_IMSET_CNTRCHNG_NO_EFFECT                              0x00000000U

// Field:     [2] DBLTRANS
//
// Set the MIS.DBLTRANS mask.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_IMSET_DBLTRANS                                        0x00000004U
#define LGPT_IMSET_DBLTRANS_M                                      0x00000004U
#define LGPT_IMSET_DBLTRANS_S                                               2U
#define LGPT_IMSET_DBLTRANS_SET                                    0x00000004U
#define LGPT_IMSET_DBLTRANS_NO_EFFECT                              0x00000000U

// Field:     [1] ZERO
//
// Set the MIS.ZERO mask.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_IMSET_ZERO                                            0x00000002U
#define LGPT_IMSET_ZERO_M                                          0x00000002U
#define LGPT_IMSET_ZERO_S                                                   1U
#define LGPT_IMSET_ZERO_SET                                        0x00000002U
#define LGPT_IMSET_ZERO_NO_EFFECT                                  0x00000000U

// Field:     [0] TGT
//
// Set the MIS.TGT mask.
// ENUMs:
// SET
// NO_EFFECT                No effect
#define LGPT_IMSET_TGT                                             0x00000001U
#define LGPT_IMSET_TGT_M                                           0x00000001U
#define LGPT_IMSET_TGT_S                                                    0U
#define LGPT_IMSET_TGT_SET                                         0x00000001U
#define LGPT_IMSET_TGT_NO_EFFECT                                   0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_IMCLR
//
//*****************************************************************************
// Field:    [10] C2CC
//
// Clear the MIS.C2CC mask.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_IMCLR_C2CC                                            0x00000400U
#define LGPT_IMCLR_C2CC_M                                          0x00000400U
#define LGPT_IMCLR_C2CC_S                                                  10U
#define LGPT_IMCLR_C2CC_CLR                                        0x00000400U
#define LGPT_IMCLR_C2CC_NO_EFFECT                                  0x00000000U

// Field:     [9] C1CC
//
// Clear the MIS.C1CC mask.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_IMCLR_C1CC                                            0x00000200U
#define LGPT_IMCLR_C1CC_M                                          0x00000200U
#define LGPT_IMCLR_C1CC_S                                                   9U
#define LGPT_IMCLR_C1CC_CLR                                        0x00000200U
#define LGPT_IMCLR_C1CC_NO_EFFECT                                  0x00000000U

// Field:     [8] C0CC
//
// Clear the MIS.C0CC mask.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_IMCLR_C0CC                                            0x00000100U
#define LGPT_IMCLR_C0CC_M                                          0x00000100U
#define LGPT_IMCLR_C0CC_S                                                   8U
#define LGPT_IMCLR_C0CC_CLR                                        0x00000100U
#define LGPT_IMCLR_C0CC_NO_EFFECT                                  0x00000000U

// Field:     [6] FAULT
//
// Clear the MIS.FAULT mask.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_IMCLR_FAULT                                           0x00000040U
#define LGPT_IMCLR_FAULT_M                                         0x00000040U
#define LGPT_IMCLR_FAULT_S                                                  6U
#define LGPT_IMCLR_FAULT_CLR                                       0x00000040U
#define LGPT_IMCLR_FAULT_NO_EFFECT                                 0x00000000U

// Field:     [5] IDX
//
// Clear the MIS.IDX mask.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_IMCLR_IDX                                             0x00000020U
#define LGPT_IMCLR_IDX_M                                           0x00000020U
#define LGPT_IMCLR_IDX_S                                                    5U
#define LGPT_IMCLR_IDX_CLR                                         0x00000020U
#define LGPT_IMCLR_IDX_NO_EFFECT                                   0x00000000U

// Field:     [4] DIRCHNG
//
// Clear the MIS.DIRCHNG mask.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_IMCLR_DIRCHNG                                         0x00000010U
#define LGPT_IMCLR_DIRCHNG_M                                       0x00000010U
#define LGPT_IMCLR_DIRCHNG_S                                                4U
#define LGPT_IMCLR_DIRCHNG_CLR                                     0x00000010U
#define LGPT_IMCLR_DIRCHNG_NO_EFFECT                               0x00000000U

// Field:     [3] CNTRCHNG
//
// Clear the MIS.CNTRCHNG mask.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_IMCLR_CNTRCHNG                                        0x00000008U
#define LGPT_IMCLR_CNTRCHNG_M                                      0x00000008U
#define LGPT_IMCLR_CNTRCHNG_S                                               3U
#define LGPT_IMCLR_CNTRCHNG_CLR                                    0x00000008U
#define LGPT_IMCLR_CNTRCHNG_NO_EFFECT                              0x00000000U

// Field:     [2] DBLTRANS
//
// Clear the MIS.DBLTRANS mask.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_IMCLR_DBLTRANS                                        0x00000004U
#define LGPT_IMCLR_DBLTRANS_M                                      0x00000004U
#define LGPT_IMCLR_DBLTRANS_S                                               2U
#define LGPT_IMCLR_DBLTRANS_CLR                                    0x00000004U
#define LGPT_IMCLR_DBLTRANS_NO_EFFECT                              0x00000000U

// Field:     [1] ZERO
//
// Clear the MIS.ZERO mask.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_IMCLR_ZERO                                            0x00000002U
#define LGPT_IMCLR_ZERO_M                                          0x00000002U
#define LGPT_IMCLR_ZERO_S                                                   1U
#define LGPT_IMCLR_ZERO_CLR                                        0x00000002U
#define LGPT_IMCLR_ZERO_NO_EFFECT                                  0x00000000U

// Field:     [0] TGT
//
// Clear the MIS.TGT mask.
// ENUMs:
// CLR                      Clear
// NO_EFFECT                No effect
#define LGPT_IMCLR_TGT                                             0x00000001U
#define LGPT_IMCLR_TGT_M                                           0x00000001U
#define LGPT_IMCLR_TGT_S                                                    0U
#define LGPT_IMCLR_TGT_CLR                                         0x00000001U
#define LGPT_IMCLR_TGT_NO_EFFECT                                   0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_EMU
//
//*****************************************************************************
// Field:     [1] CTL
//
// Halt control.
//
// Configure when the counter shall stop upon CPU halt. This bitfield only
// applies if HALT = 1.
// ENUMs:
// ZERCOND                  Zero condition. The counter stops when CNTR = 0.
// IMMEDIATE                Immediate reaction. The counter stops immediately
//                          on debug halt.
#define LGPT_EMU_CTL                                               0x00000002U
#define LGPT_EMU_CTL_M                                             0x00000002U
#define LGPT_EMU_CTL_S                                                      1U
#define LGPT_EMU_CTL_ZERCOND                                       0x00000002U
#define LGPT_EMU_CTL_IMMEDIATE                                     0x00000000U

// Field:     [0] HALT
//
// Halt LGPT when CPU is halted in debug.
// ENUMs:
// EN                       Enable.
// DIS                      Disable.
#define LGPT_EMU_HALT                                              0x00000001U
#define LGPT_EMU_HALT_M                                            0x00000001U
#define LGPT_EMU_HALT_S                                                     0U
#define LGPT_EMU_HALT_EN                                           0x00000001U
#define LGPT_EMU_HALT_DIS                                          0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_C0CFG
//
//*****************************************************************************
// Field:    [10] OUT2
//
// Output 2 enable.
//
// When 0 < CCACT < 8, OUT2 becomes zero after a capture or compare event.
// ENUMs:
// EN                       Channel 0 controls output 2.
// DIS                      Channel 0 does not control output 2.
#define LGPT_C0CFG_OUT2                                            0x00000400U
#define LGPT_C0CFG_OUT2_M                                          0x00000400U
#define LGPT_C0CFG_OUT2_S                                                  10U
#define LGPT_C0CFG_OUT2_EN                                         0x00000400U
#define LGPT_C0CFG_OUT2_DIS                                        0x00000000U

// Field:     [9] OUT1
//
// Output 1 enable.
//
// When 0 < CCACT < 8, OUT1 becomes zero after a capture or compare event.
// ENUMs:
// EN                       Channel 0 controls output 1.
// DIS                      Channel 0 does not control output 1.
#define LGPT_C0CFG_OUT1                                            0x00000200U
#define LGPT_C0CFG_OUT1_M                                          0x00000200U
#define LGPT_C0CFG_OUT1_S                                                   9U
#define LGPT_C0CFG_OUT1_EN                                         0x00000200U
#define LGPT_C0CFG_OUT1_DIS                                        0x00000000U

// Field:     [8] OUT0
//
// Output 0 enable.
//
// When 0 < CCACT < 8, OUT0 becomes zero after a capture or compare event.
// ENUMs:
// EN                       Channel 0 controls output 0.
// DIS                      Channel 0 does not control output 0.
#define LGPT_C0CFG_OUT0                                            0x00000100U
#define LGPT_C0CFG_OUT0_M                                          0x00000100U
#define LGPT_C0CFG_OUT0_S                                                   8U
#define LGPT_C0CFG_OUT0_EN                                         0x00000100U
#define LGPT_C0CFG_OUT0_DIS                                        0x00000000U

// Field:     [6] INPUT
//
// Select channel input.
// ENUMs:
// IO                       IO controller
// EV                       Event fabric
#define LGPT_C0CFG_INPUT                                           0x00000040U
#define LGPT_C0CFG_INPUT_M                                         0x00000040U
#define LGPT_C0CFG_INPUT_S                                                  6U
#define LGPT_C0CFG_INPUT_IO                                        0x00000040U
#define LGPT_C0CFG_INPUT_EV                                        0x00000000U

// Field:   [5:4] EDGE
//
// Determines the edge that triggers the channel input event. This happens post
// filter.
// ENUMs:
// BOTH                     Input event is triggered at both edges.
// FALL                     Input event is triggered at falling edge.
// RISE                     Input event is triggered at rising edge.
// NONE                     Input is turned off.
#define LGPT_C0CFG_EDGE_W                                                   2U
#define LGPT_C0CFG_EDGE_M                                          0x00000030U
#define LGPT_C0CFG_EDGE_S                                                   4U
#define LGPT_C0CFG_EDGE_BOTH                                       0x00000030U
#define LGPT_C0CFG_EDGE_FALL                                       0x00000020U
#define LGPT_C0CFG_EDGE_RISE                                       0x00000010U
#define LGPT_C0CFG_EDGE_NONE                                       0x00000000U

// Field:   [3:0] CCACT
//
// Capture-Compare action.
//
// Capture-Compare action defines 15 different channel functions that utilize
// capture, compare, and zero events. In every compare event the timer looks at
// the current value of CNTR. The corresponding output event will be set 1
// timer period after CNTR = C0CC.
// ENUMs:
// PULSE_ON_CMP             Pulse on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Pulse enabled outputs
//                          when C0CC.VAL = CNTR.VAL.
//
//                           The output is high for
//                          two timer clock periods.
// TGL_ON_CMP               Toggle on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Toggle enabled outputs
//                          when C0CC.VAL = CNTR.VAL.
// SET_ON_CMP               Set on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs
//                          when C0CC.VAL = CNTR.VAL.
// CLR_ON_CMP               Clear on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Clear enabled outputs
//                          when C0CC.VAL = CNTR.VAL.
// SET_ON_0_TGL_ON_CMP      Set on zero, toggle on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs
//                          when CNTR.VAL = 0.
//                          - Toggle enabled outputs
//                          when C0CC.VAL = CNTR.VAL.
//
//                          Set CTL.MODE to UP_PER
//                          for edge-aligned PWM generation. Duty cycle is
//                          given by:
//
//                          When C0CC.VAL <= TGT.VAL:
//                             Duty cycle = C0CC.VAL
//                          / ( TGT.VAL + 1 ).
//
//                          When C0CC.VAL > TGT.VAL:
//                             Duty cycle = 1.
//
//                          Enabled outputs are
//                          cleared when C0CC.VAL = 0 and CNTR.VAL = 0.
// CLR_ON_0_TGL_ON_CMP      Clear on zero, toggle on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Clear enabled outputs
//                          when CNTR.VAL = 0.
//                          - Toggle enabled outputs
//                          when C0CC.VAL = CNTR.VAL.
//
//                          Set CTL.MODE to UPDWN_PER
//                          for center-aligned PWM generation. Duty cycle
//                          is given by:
//
//                          When C0CC.VAL <= TGT.VAL:
//                             Duty cycle = 1 - (
//                          C0CC.VAL / TGT.VAL ).
//
//                          When C0CC.VAL > TGT.VAL:
//                             Duty cycle = 0.
//
//                          Enabled outputs are set
//                          when C0CC.VAL = 0 and CNTR.VAL = 0.
// SET_ON_CAPT              Set on capture repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs on
//                          capture event and copy CNTR.VAL to C0CC.VAL.
// PER_PULSE_WIDTH_MEAS     Period and pulse width measurement.
//
//                          Continuously capture
//                          period and pulse width of the signal selected
//                          by INPUT relative to the signal edge given by
//                          EDGE.
//
//                          Set enabled outputs and
//                          RIS.C0CC when C0CC.VAL contains signal period
//                          and PC0CC.VAL contains signal pulse width.
//
//                          Notes:
//                          - Make sure to configure
//                          INPUT and CCACT when CTL.MODE equals DIS, then
//                          set CTL.MODE to UP_ONCE or UP_PER.
//                          - The counter restarts in
//                          the selected timer mode when C0CC.VAL contains
//                          the signal period.
//                          - If more than one
//                          channel uses this function, the channels will
//                          perform this function one at a time. The
//                          channel with lowest number has priority and
//                          performs the function first. Next measurement
//                          starts when current measurement completes
//                          successfully or times out. A timeout occurs
//                          when counter equals target.
//                          - To observe a timeout
//                          event the RIS.TGT interrupt can be used, or
//                          another channel can be configured to SET_ON_CMP
//                          with compare value equal TGT.
//
//                          Signal property
//                          requirements:
//                          - Signal Period >= 2 * (
//                          1 + PRECFG.TICKDIV ) * timer clock period.
//                          - Signal Period <=
//                          MAX(CNTR) * (1 + PRECFG.TICKDIV ) * timer clock
//                          period.
//                          - Signal low and high
//                          phase >= (1 + PRECFG.TICKDIV ) * timer clock
//                          period.
// PULSE_ON_CMP_DIS         Pulse on compare, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Pulse enabled outputs
//                          when C0CC.VAL = CNTR.VAL.
//                          - Disable channel.
//
//                           The output is high for
//                          two timer clock periods.
// TGL_ON_CMP_DIS           Toggle on compare, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Toggle enabled outputs
//                          when C0CC.VAL = CNTR.VAL.
//                          - Disable channel.
// SET_ON_CMP_DIS           Set on compare, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs
//                          when C0CC.VAL = CNTR.VAL.
//                          - Disable channel.
// CLR_ON_CMP_DIS           Clear on compare, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Clear enabled outputs
//                          when C0CC.VAL = CNTR.VAL.
//                          - Disable channel.
// SET_ON_0_TGL_ON_CMP_DIS  Set on zero, toggle on compare, and then disable
//                          channel.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs
//                          when CNTR.VAL = 0.
//                          - Toggle enabled outputs
//                          when C0CC.VAL = CNTR.VAL.
//                          - Disable channel.
//
//                          Enabled outputs are
//                          cleared when C0CC.VAL = 0 and CNTR.VAL = 0.
// CLR_ON_0_TGL_ON_CMP_DIS  Clear on zero, toggle on compare, and then disable
//                          channel.
//
//                          Channel function
//                          sequence:
//                          - Clear enabled outputs
//                          when CNTR.VAL = 0.
//                          - Toggle enabled outputs
//                          when C0CC.VAL = CNTR.VAL.
//                          - Disable channel.
//
//                          Enabled outputs are set
//                          when C0CC.VAL = 0 and CNTR.VAL = 0.
// SET_ON_CAPT_DIS          Set on capture, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs on
//                          capture event and copy CNTR.VAL to C0CC.VAL.
//                          - Disable channel.
//
//                          Primary use scenario is
//                          to select this function before starting the
//                          timer.
//                          Follow these steps to
//                          select this function while CTL.MODE is
//                          different from DIS:
//                           - Set CCACT to
//                          SET_ON_CAPT with no output enable.
//                           - Configure INPUT
//                          (optional).
//                           - Wait for three timer
//                          clock periods as defined in PRECFG before
//                          setting CCACT to SET_ON_CAPT_DIS. Output enable
//                          is optional.
//
//                          These steps prevent
//                          capture events caused by expired signal values
//                          in edge-detection circuit.
// DIS                      Disable channel.
#define LGPT_C0CFG_CCACT_W                                                  4U
#define LGPT_C0CFG_CCACT_M                                         0x0000000FU
#define LGPT_C0CFG_CCACT_S                                                  0U
#define LGPT_C0CFG_CCACT_PULSE_ON_CMP                              0x0000000FU
#define LGPT_C0CFG_CCACT_TGL_ON_CMP                                0x0000000EU
#define LGPT_C0CFG_CCACT_SET_ON_CMP                                0x0000000DU
#define LGPT_C0CFG_CCACT_CLR_ON_CMP                                0x0000000CU
#define LGPT_C0CFG_CCACT_SET_ON_0_TGL_ON_CMP                       0x0000000BU
#define LGPT_C0CFG_CCACT_CLR_ON_0_TGL_ON_CMP                       0x0000000AU
#define LGPT_C0CFG_CCACT_SET_ON_CAPT                               0x00000009U
#define LGPT_C0CFG_CCACT_PER_PULSE_WIDTH_MEAS                      0x00000008U
#define LGPT_C0CFG_CCACT_PULSE_ON_CMP_DIS                          0x00000007U
#define LGPT_C0CFG_CCACT_TGL_ON_CMP_DIS                            0x00000006U
#define LGPT_C0CFG_CCACT_SET_ON_CMP_DIS                            0x00000005U
#define LGPT_C0CFG_CCACT_CLR_ON_CMP_DIS                            0x00000004U
#define LGPT_C0CFG_CCACT_SET_ON_0_TGL_ON_CMP_DIS                   0x00000003U
#define LGPT_C0CFG_CCACT_CLR_ON_0_TGL_ON_CMP_DIS                   0x00000002U
#define LGPT_C0CFG_CCACT_SET_ON_CAPT_DIS                           0x00000001U
#define LGPT_C0CFG_CCACT_DIS                                       0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_C1CFG
//
//*****************************************************************************
// Field:    [10] OUT2
//
// Output 2 enable.
//
// When 0 < CCACT < 8, OUT2 becomes zero after a capture or compare event.
// ENUMs:
// EN                       Channel 1 controls output 2.
// DIS                      Channel 1 does not control output 2.
#define LGPT_C1CFG_OUT2                                            0x00000400U
#define LGPT_C1CFG_OUT2_M                                          0x00000400U
#define LGPT_C1CFG_OUT2_S                                                  10U
#define LGPT_C1CFG_OUT2_EN                                         0x00000400U
#define LGPT_C1CFG_OUT2_DIS                                        0x00000000U

// Field:     [9] OUT1
//
// Output 1 enable.
//
// When 0 < CCACT < 8, OUT1 becomes zero after a capture or compare event.
// ENUMs:
// EN                       Channel 1 controls output 1.
// DIS                      Channel 1 does not control output 1.
#define LGPT_C1CFG_OUT1                                            0x00000200U
#define LGPT_C1CFG_OUT1_M                                          0x00000200U
#define LGPT_C1CFG_OUT1_S                                                   9U
#define LGPT_C1CFG_OUT1_EN                                         0x00000200U
#define LGPT_C1CFG_OUT1_DIS                                        0x00000000U

// Field:     [8] OUT0
//
// Output 0 enable.
// When 0 < CCACT < 8, OUT0 becomes zero after a capture or compare event.
// ENUMs:
// EN                       Channel 1 controls output 0.
// DIS                      Channel 1 does not control output 0.
#define LGPT_C1CFG_OUT0                                            0x00000100U
#define LGPT_C1CFG_OUT0_M                                          0x00000100U
#define LGPT_C1CFG_OUT0_S                                                   8U
#define LGPT_C1CFG_OUT0_EN                                         0x00000100U
#define LGPT_C1CFG_OUT0_DIS                                        0x00000000U

// Field:     [6] INPUT
//
// Select channel input.
// ENUMs:
// IO                       IO controller
// EV                       Event fabric
#define LGPT_C1CFG_INPUT                                           0x00000040U
#define LGPT_C1CFG_INPUT_M                                         0x00000040U
#define LGPT_C1CFG_INPUT_S                                                  6U
#define LGPT_C1CFG_INPUT_IO                                        0x00000040U
#define LGPT_C1CFG_INPUT_EV                                        0x00000000U

// Field:   [5:4] EDGE
//
// Determines the edge that triggers the channel input event. This happens post
// filter.
// ENUMs:
// BOTH                     Input event is triggered at both edges.
// FALL                     Input event is triggered at falling edge.
// RISE                     Input event is triggered at rising edge.
// NONE                     Input is turned off.
#define LGPT_C1CFG_EDGE_W                                                   2U
#define LGPT_C1CFG_EDGE_M                                          0x00000030U
#define LGPT_C1CFG_EDGE_S                                                   4U
#define LGPT_C1CFG_EDGE_BOTH                                       0x00000030U
#define LGPT_C1CFG_EDGE_FALL                                       0x00000020U
#define LGPT_C1CFG_EDGE_RISE                                       0x00000010U
#define LGPT_C1CFG_EDGE_NONE                                       0x00000000U

// Field:   [3:0] CCACT
//
// Capture-Compare action.
//
// Capture-Compare action defines 15 different channel functions that utilize
// capture, compare, and zero events. In every compare event the timer looks at
// the current value of CNTR. The corresponding output event will be set 1
// timer period after CNTR = C1CC.
// ENUMs:
// PULSE_ON_CMP             Pulse on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Pulse enabled outputs
//                          when C1CC.VAL = CNTR.VAL.
//
//                           The output is high for
//                          two timer clock periods.
// TGL_ON_CMP               Toggle on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Toggle enabled outputs
//                          when C1CC.VAL = CNTR.VAL.
// SET_ON_CMP               Set on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs
//                          when C1CC.VAL = CNTR.VAL.
// CLR_ON_CMP               Clear on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Clear enabled outputs
//                          when C1CC.VAL = CNTR.VAL.
// SET_ON_0_TGL_ON_CMP      Set on zero, toggle on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs
//                          when CNTR.VAL = 0.
//                          - Toggle enabled outputs
//                          when C1CC.VAL = CNTR.VAL.
//
//                          Set CTL.MODE to UP_PER
//                          for edge-aligned PWM generation. Duty cycle is
//                          given by:
//
//                          When C1CC.VAL <= TGT.VAL:
//                             Duty cycle = C1CC.VAL
//                          / ( TGT.VAL + 1 ).
//
//                          When C1CC.VAL > TGT.VAL:
//                             Duty cycle = 1.
//
//                          Enabled outputs are
//                          cleared when C1CC.VAL = 0 and CNTR.VAL = 0.
// CLR_ON_0_TGL_ON_CMP      Clear on zero, toggle on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Clear enabled outputs
//                          when CNTR.VAL = 0.
//                          - Toggle enabled outputs
//                          when C1CC.VAL = CNTR.VAL.
//
//                          Set CTL.MODE to UPDWN_PER
//                          for center-aligned PWM generation. Duty cycle
//                          is given by:
//
//                          When C1CC.VAL <= TGT.VAL:
//                             Duty cycle = 1 - (
//                          C1CC.VAL / TGT.VAL ).
//
//                          When C1CC.VAL > TGT.VAL:
//                             Duty cycle = 0.
//
//                          Enabled outputs are set
//                          when C1CC.VAL = 0 and CNTR.VAL = 0.
// SET_ON_CAPT              Set on capture repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs on
//                          capture event and copy CNTR.VAL to C1CC.VAL.
// PER_PULSE_WIDTH_MEAS     Period and pulse width measurement.
//
//                          Continuously capture
//                          period and pulse width of the signal selected
//                          by INPUT relative to the signal edge given by
//                          EDGE.
//
//                          Set enabled outputs and
//                          RIS.C1CC when C1CC.VAL contains signal period
//                          and PC1CC.VAL contains signal pulse width.
//
//                          Notes:
//                          - Make sure to configure
//                          INPUT and CCACT when CTL.MODE equals DIS, then
//                          set CTL.MODE to UP_ONCE or UP_PER.
//                          - The counter restarts in
//                          the selected timer mode when C1CC.VAL contains
//                          the signal period.
//                          - If more than one
//                          channel uses this function, the channels will
//                          perform this function one at a time. The
//                          channel with lowest number has priority and
//                          performs the function first. Next measurement
//                          starts when current measurement completes
//                          successfully or times out. A timeout occurs
//                          when counter equals target.
//                          - To observe a timeout
//                          event the RIS.TGT interrupt can be used, or
//                          another channel can be configured to SET_ON_CMP
//                          with compare value equal TGT.
//
//                          Signal property
//                          requirements:
//                          - Signal Period >= 2 * (
//                          1 + PRECFG.TICKDIV ) * timer clock period.
//                          - Signal Period <=
//                          MAX(CNTR) * (1 + PRECFG.TICKDIV ) * timer clock
//                          period.
//                          - Signal low and high
//                          phase >= (1 + PRECFG.TICKDIV ) * timer clock
//                          period.
// PULSE_ON_CMP_DIS         Pulse on compare, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Pulse enabled outputs
//                          when C1CC.VAL = CNTR.VAL.
//                          - Disable channel.
//
//                           The output is high for
//                          two timer clock periods.
// TGL_ON_CMP_DIS           Toggle on compare, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Toggle enabled outputs
//                          when C1CC.VAL = CNTR.VAL.
//                          - Disable channel.
// SET_ON_CMP_DIS           Set on compare, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs
//                          when C1CC.VAL = CNTR.VAL.
//                          - Disable channel.
// CLR_ON_CMP_DIS           Clear on compare, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Clear enabled outputs
//                          when C1CC.VAL = CNTR.VAL.
//                          - Disable channel.
// SET_ON_0_TGL_ON_CMP_DIS  Set on zero, toggle on compare, and then disable
//                          channel.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs
//                          when CNTR.VAL = 0.
//                          - Toggle enabled outputs
//                          when C1CC.VAL = CNTR.VAL.
//                          - Disable channel.
//
//                          Enabled outputs are
//                          cleared when C1CC.VAL = 0 and CNTR.VAL = 0.
// CLR_ON_0_TGL_ON_CMP_DIS  Clear on zero, toggle on compare, and then disable
//                          channel.
//
//                          Channel function
//                          sequence:
//                          - Clear enabled outputs
//                          when CNTR.VAL = 0.
//                          - Toggle enabled outputs
//                          when C1CC.VAL = CNTR.VAL.
//                          - Disable channel.
//
//                          Enabled outputs are set
//                          when C1CC.VAL = 0 and CNTR.VAL = 0.
// SET_ON_CAPT_DIS          Set on capture, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs on
//                          capture event and copy CNTR.VAL to C1CC.VAL.
//                          - Disable channel.
//
//                          Primary use scenario is
//                          to select this function before starting the
//                          timer.
//                          Follow these steps to
//                          select this function while CTL.MODE is
//                          different from DIS:
//                           - Set CCACT to
//                          SET_ON_CAPT with no output enable.
//                           - Configure INPUT
//                          (optional).
//                           - Wait for three timer
//                          clock periods as defined in PRECFG before
//                          setting CCACT to SET_ON_CAPT_DIS. Output enable
//                          is optional.
//
//                          These steps prevent
//                          capture events caused by expired signal values
//                          in edge-detection circuit.
// DIS                      Disable channel.
#define LGPT_C1CFG_CCACT_W                                                  4U
#define LGPT_C1CFG_CCACT_M                                         0x0000000FU
#define LGPT_C1CFG_CCACT_S                                                  0U
#define LGPT_C1CFG_CCACT_PULSE_ON_CMP                              0x0000000FU
#define LGPT_C1CFG_CCACT_TGL_ON_CMP                                0x0000000EU
#define LGPT_C1CFG_CCACT_SET_ON_CMP                                0x0000000DU
#define LGPT_C1CFG_CCACT_CLR_ON_CMP                                0x0000000CU
#define LGPT_C1CFG_CCACT_SET_ON_0_TGL_ON_CMP                       0x0000000BU
#define LGPT_C1CFG_CCACT_CLR_ON_0_TGL_ON_CMP                       0x0000000AU
#define LGPT_C1CFG_CCACT_SET_ON_CAPT                               0x00000009U
#define LGPT_C1CFG_CCACT_PER_PULSE_WIDTH_MEAS                      0x00000008U
#define LGPT_C1CFG_CCACT_PULSE_ON_CMP_DIS                          0x00000007U
#define LGPT_C1CFG_CCACT_TGL_ON_CMP_DIS                            0x00000006U
#define LGPT_C1CFG_CCACT_SET_ON_CMP_DIS                            0x00000005U
#define LGPT_C1CFG_CCACT_CLR_ON_CMP_DIS                            0x00000004U
#define LGPT_C1CFG_CCACT_SET_ON_0_TGL_ON_CMP_DIS                   0x00000003U
#define LGPT_C1CFG_CCACT_CLR_ON_0_TGL_ON_CMP_DIS                   0x00000002U
#define LGPT_C1CFG_CCACT_SET_ON_CAPT_DIS                           0x00000001U
#define LGPT_C1CFG_CCACT_DIS                                       0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_C2CFG
//
//*****************************************************************************
// Field:    [10] OUT2
//
// Output 2 enable.
//
// When 0 < CCACT < 8, OUT2 becomes zero after a capture or compare event.
// ENUMs:
// EN                       Channel 2 controls output 2.
// DIS                      Channel 2 does not control output 2.
#define LGPT_C2CFG_OUT2                                            0x00000400U
#define LGPT_C2CFG_OUT2_M                                          0x00000400U
#define LGPT_C2CFG_OUT2_S                                                  10U
#define LGPT_C2CFG_OUT2_EN                                         0x00000400U
#define LGPT_C2CFG_OUT2_DIS                                        0x00000000U

// Field:     [9] OUT1
//
// Output 1 enable.
//
// When 0 < CCACT < 8, OUT1 becomes zero after a capture or compare event.
// ENUMs:
// EN                       Channel 2 controls output 1.
// DIS                      Channel 2 does not control output 1.
#define LGPT_C2CFG_OUT1                                            0x00000200U
#define LGPT_C2CFG_OUT1_M                                          0x00000200U
#define LGPT_C2CFG_OUT1_S                                                   9U
#define LGPT_C2CFG_OUT1_EN                                         0x00000200U
#define LGPT_C2CFG_OUT1_DIS                                        0x00000000U

// Field:     [8] OUT0
//
// Output 0 enable.
//
// When 0 < CCACT < 8, OUT0 becomes zero after a capture or compare event.
// ENUMs:
// EN                       Channel 2 controls output 0.
// DIS                      Channel 2 does not control output 0.
#define LGPT_C2CFG_OUT0                                            0x00000100U
#define LGPT_C2CFG_OUT0_M                                          0x00000100U
#define LGPT_C2CFG_OUT0_S                                                   8U
#define LGPT_C2CFG_OUT0_EN                                         0x00000100U
#define LGPT_C2CFG_OUT0_DIS                                        0x00000000U

// Field:     [6] INPUT
//
// Select channel input.
// ENUMs:
// IO                       IO controller
// EV                       Event fabric
#define LGPT_C2CFG_INPUT                                           0x00000040U
#define LGPT_C2CFG_INPUT_M                                         0x00000040U
#define LGPT_C2CFG_INPUT_S                                                  6U
#define LGPT_C2CFG_INPUT_IO                                        0x00000040U
#define LGPT_C2CFG_INPUT_EV                                        0x00000000U

// Field:   [5:4] EDGE
//
// Determines the edge that triggers the channel input event. This happens post
// filter.
// ENUMs:
// BOTH                     Input event is triggered at both edges.
// FALL                     Input event is triggered at falling edge.
// RISE                     Input event is triggered at rising edge.
// NONE                     Input is turned off.
#define LGPT_C2CFG_EDGE_W                                                   2U
#define LGPT_C2CFG_EDGE_M                                          0x00000030U
#define LGPT_C2CFG_EDGE_S                                                   4U
#define LGPT_C2CFG_EDGE_BOTH                                       0x00000030U
#define LGPT_C2CFG_EDGE_FALL                                       0x00000020U
#define LGPT_C2CFG_EDGE_RISE                                       0x00000010U
#define LGPT_C2CFG_EDGE_NONE                                       0x00000000U

// Field:   [3:0] CCACT
//
// Capture-Compare action.
//
// Capture-Compare action defines 15 different channel functions that utilize
// capture, compare, and zero events. In every compare event the timer looks at
// the current value of CNTR. The corresponding output event will be set 1
// timer period after CNTR = C2CC.
// ENUMs:
// PULSE_ON_CMP             Pulse on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Pulse enabled outputs
//                          when C2CC.VAL = CNTR.VAL.
//
//                           The output is high for
//                          two timer clock periods.
// TGL_ON_CMP               Toggle on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Toggle enabled outputs
//                          when C2CC.VAL = CNTR.VAL.
// SET_ON_CMP               Set on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs
//                          when C2CC.VAL = CNTR.VAL.
// CLR_ON_CMP               Clear on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Clear enabled outputs
//                          when C2CC.VAL = CNTR.VAL.
// SET_ON_0_TGL_ON_CMP      Set on zero, toggle on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs
//                          when CNTR.VAL = 0.
//                          - Toggle enabled outputs
//                          when C2CC.VAL = CNTR.VAL.
//
//                          Set CTL.MODE to UP_PER
//                          for edge-aligned PWM generation. Duty cycle is
//                          given by:
//
//                          When C2CC.VAL <= TGT.VAL:
//                             Duty cycle = C2CC.VAL
//                          / ( TGT.VAL + 1 ).
//
//                          When C2CC.VAL > TGT.VAL:
//                             Duty cycle = 1.
//
//                          Enabled outputs are
//                          cleared when C2CC.VAL = 0 and CNTR.VAL = 0.
// CLR_ON_0_TGL_ON_CMP      Clear on zero, toggle on compare repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Clear enabled outputs
//                          when CNTR.VAL = 0.
//                          - Toggle enabled outputs
//                          when C2CC.VAL = CNTR.VAL.
//
//                          Set CTL.MODE to UPDWN_PER
//                          for center-aligned PWM generation. Duty cycle
//                          is given by:
//
//                          When C2CC.VAL <= TGT.VAL:
//                             Duty cycle = 1 - (
//                          C2CC.VAL / TGT.VAL ).
//
//                          When C2CC.VAL > TGT.VAL:
//                             Duty cycle = 0.
//
//                          Enabled outputs are set
//                          when C2CC.VAL = 0 and CNTR.VAL = 0.
// SET_ON_CAPT              Set on capture repeatedly.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs on
//                          capture event and copy CNTR.VAL to C2CC.VAL.
// PER_PULSE_WIDTH_MEAS     Period and pulse width measurement.
//
//                          Continuously capture
//                          period and pulse width of the signal selected
//                          by INPUT relative to the signal edge given by
//                          EDGE.
//
//                          Set enabled outputs and
//                          RIS.C2CC when C2CC.VAL contains signal period
//                          and PC2CC.VAL contains signal pulse width.
//
//                          Notes:
//                          - Make sure to configure
//                          INPUT and CCACT when CTL.MODE equals DIS, then
//                          set CTL.MODE to UP_ONCE or UP_PER.
//                          - The counter restarts in
//                          the selected timer mode when C2CC.VAL contains
//                          the signal period.
//                          - If more than one
//                          channel uses this function, the channels will
//                          perform this function one at a time. The
//                          channel with lowest number has priority and
//                          performs the function first. Next measurement
//                          starts when current measurement completes
//                          successfully or times out. A timeout occurs
//                          when counter equals target.
//                          - To observe a timeout
//                          event the RIS.TGT interrupt can be used, or
//                          another channel can be configured to SET_ON_CMP
//                          with compare value equal TGT.
//
//                          Signal property
//                          requirements:
//                          - Signal Period >= 2 * (
//                          1 + PRECFG.TICKDIV ) * timer clock period.
//                          - Signal Period <=
//                          MAX(CNTR) * (1 + PRECFG.TICKDIV ) * timer clock
//                          period.
//                          - Signal low and high
//                          phase >= (1 + PRECFG.TICKDIV ) * timer clock
//                          period.
// PULSE_ON_CMP_DIS         Pulse on compare, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Pulse enabled outputs
//                          when C2CC.VAL = CNTR.VAL.
//                          - Disable channel.
//
//                           The output is high for
//                          two timer clock periods.
// TGL_ON_CMP_DIS           Toggle on compare, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Toggle enabled outputs
//                          when C2CC.VAL = CNTR.VAL.
//                          - Disable channel.
// SET_ON_CMP_DIS           Set on compare, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs
//                          when C2CC.VAL = CNTR.VAL.
//                          - Disable channel.
// CLR_ON_CMP_DIS           Clear on compare, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Clear enabled outputs
//                          when C2CC.VAL = CNTR.VAL.
//                          - Disable channel.
// SET_ON_0_TGL_ON_CMP_DIS  Set on zero, toggle on compare, and then disable
//                          channel.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs
//                          when CNTR.VAL = 0.
//                          - Toggle enabled outputs
//                          when C2CC.VAL = CNTR.VAL.
//                          - Disable channel.
//
//                          Enabled outputs are
//                          cleared when C2CC.VAL = 0 and CNTR.VAL = 0.
// CLR_ON_0_TGL_ON_CMP_DIS  Clear on zero, toggle on compare, and then disable
//                          channel.
//
//                          Channel function
//                          sequence:
//                          - Clear enabled outputs
//                          when CNTR.VAL = 0.
//                          - Toggle enabled outputs
//                          when C2CC.VAL = CNTR.VAL.
//                          - Disable channel.
//
//                          Enabled outputs are set
//                          when C2CC.VAL = 0 and CNTR.VAL = 0.
// SET_ON_CAPT_DIS          Set on capture, and then disable channel.
//
//                          Channel function
//                          sequence:
//                          - Set enabled outputs on
//                          capture event and copy CNTR.VAL to C2CC.VAL.
//                          - Disable channel.
//
//                          Primary use scenario is
//                          to select this function before starting the
//                          timer.
//                          Follow these steps to
//                          select this function while CTL.MODE is
//                          different from DIS:
//                           - Set CCACT to
//                          SET_ON_CAPT with no output enable.
//                           - Configure INPUT
//                          (optional).
//                           - Wait for three timer
//                          clock periods as defined in PRECFG before
//                          setting CCACT to SET_ON_CAPT_DIS. Output enable
//                          is optional.
//
//                          These steps prevent
//                          capture events caused by expired signal values
//                          in edge-detection circuit.
// DIS                      Disable channel.
#define LGPT_C2CFG_CCACT_W                                                  4U
#define LGPT_C2CFG_CCACT_M                                         0x0000000FU
#define LGPT_C2CFG_CCACT_S                                                  0U
#define LGPT_C2CFG_CCACT_PULSE_ON_CMP                              0x0000000FU
#define LGPT_C2CFG_CCACT_TGL_ON_CMP                                0x0000000EU
#define LGPT_C2CFG_CCACT_SET_ON_CMP                                0x0000000DU
#define LGPT_C2CFG_CCACT_CLR_ON_CMP                                0x0000000CU
#define LGPT_C2CFG_CCACT_SET_ON_0_TGL_ON_CMP                       0x0000000BU
#define LGPT_C2CFG_CCACT_CLR_ON_0_TGL_ON_CMP                       0x0000000AU
#define LGPT_C2CFG_CCACT_SET_ON_CAPT                               0x00000009U
#define LGPT_C2CFG_CCACT_PER_PULSE_WIDTH_MEAS                      0x00000008U
#define LGPT_C2CFG_CCACT_PULSE_ON_CMP_DIS                          0x00000007U
#define LGPT_C2CFG_CCACT_TGL_ON_CMP_DIS                            0x00000006U
#define LGPT_C2CFG_CCACT_SET_ON_CMP_DIS                            0x00000005U
#define LGPT_C2CFG_CCACT_CLR_ON_CMP_DIS                            0x00000004U
#define LGPT_C2CFG_CCACT_SET_ON_0_TGL_ON_CMP_DIS                   0x00000003U
#define LGPT_C2CFG_CCACT_CLR_ON_0_TGL_ON_CMP_DIS                   0x00000002U
#define LGPT_C2CFG_CCACT_SET_ON_CAPT_DIS                           0x00000001U
#define LGPT_C2CFG_CCACT_DIS                                       0x00000000U

//*****************************************************************************
//
// Register: LGPT_O_PTGT
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// The pipleline target value.
#define LGPT_PTGT_VAL_W                                                    16U
#define LGPT_PTGT_VAL_M                                            0x0000FFFFU
#define LGPT_PTGT_VAL_S                                                     0U

//*****************************************************************************
//
// Register: LGPT_O_PC0CC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Pipeline Capture Compare value.
//
// User defined pipeline compare value or channel-updated capture value.
//
// A read or write to this register will clear the RIS.C0CC interrupt.
//
// Compare mode:
// An update of VAL will be transferred to C0CC.VAL when the next CNTR.VAL is
// zero and CTL.MODE is different from DIS. This is useful for PWM generation
// and prevents jitter on the edges of the generated signal.
//
// Capture mode:
// When C0CFG.CCACT equals PER_PULSE_WIDTH_MEAS then VAL contains the width of
// the low or high phase of the selected signal. This is specified by
// C0CFG.EDGE.
#define LGPT_PC0CC_VAL_W                                                   16U
#define LGPT_PC0CC_VAL_M                                           0x0000FFFFU
#define LGPT_PC0CC_VAL_S                                                    0U

//*****************************************************************************
//
// Register: LGPT_O_PC1CC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Pipeline Capture Compare value.
//
// User defined pipeline compare value or channel-updated capture value.
//
// A read or write to this register will clear the RIS.C1CC interrupt.
//
// Compare mode:
// An update of VAL will be transferred to C1CC.VAL when the next CNTR.VAL is
// zero and CTL.MODE is different from DIS. This is useful for PWM generation
// and prevents jitter on the edges of the generated signal.
//
// Capture mode:
// When C1CFG.CCACT equals PER_PULSE_WIDTH_MEAS then VAL contains the width of
// the low or high phase of the selected signal. This is specified by
// C1CFG.EDGE.
#define LGPT_PC1CC_VAL_W                                                   16U
#define LGPT_PC1CC_VAL_M                                           0x0000FFFFU
#define LGPT_PC1CC_VAL_S                                                    0U

//*****************************************************************************
//
// Register: LGPT_O_PC2CC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Pipeline Capture Compare value.
//
// User defined pipeline compare value or channel-updated capture value.
//
// A read or write to this register will clear the RIS.C2CC interrupt.
//
// Compare mode:
// An update of VAL will be transferred to C2CC.VAL when the next CNTR.VAL is
// zero and CTL.MODE is different from DIS. This is useful for PWM generation
// and prevents jitter on the edges of the generated signal.
//
// Capture mode:
// When C2CFG.CCACT equals PER_PULSE_WIDTH_MEAS then VAL contains the width of
// the low or high phase of the selected signal. This is specified by
// C2CFG.EDGE.
#define LGPT_PC2CC_VAL_W                                                   16U
#define LGPT_PC2CC_VAL_M                                           0x0000FFFFU
#define LGPT_PC2CC_VAL_S                                                    0U

//*****************************************************************************
//
// Register: LGPT_O_TGT
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// User defined counter target value.
#define LGPT_TGT_VAL_W                                                     16U
#define LGPT_TGT_VAL_M                                             0x0000FFFFU
#define LGPT_TGT_VAL_S                                                      0U

//*****************************************************************************
//
// Register: LGPT_O_C0CC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Capture Compare value.
//
// User defined compare value or channel-updated capture value.
//
// A read or write to this register will clear the RIS.C0CC interrupt.
//
// Compare mode:
// VAL is compared against CNTR.VAL and an event is generated as specified by
// C0CFG.CCACT when these are equal.
//
// Capture mode:
// The current counter value is stored in VAL when a capture event occurs.
// C0CFG.CCACT determines if VAL is a signal period or a regular capture value.
#define LGPT_C0CC_VAL_W                                                    16U
#define LGPT_C0CC_VAL_M                                            0x0000FFFFU
#define LGPT_C0CC_VAL_S                                                     0U

//*****************************************************************************
//
// Register: LGPT_O_C1CC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Capture Compare value.
//
// User defined compare value or channel-updated capture value.
//
// A read or write to this register will clear the RIS.C1CC interrupt.
//
// Compare mode:
// VAL is compared against CNTR.VAL and an event is generated as specified by
// C1CFG.CCACT when these are equal.
//
// Capture mode:
// The current counter value is stored in VAL when a capture event occurs.
// C1CFG.CCACT determines if VAL is a signal period or a regular capture value.
#define LGPT_C1CC_VAL_W                                                    16U
#define LGPT_C1CC_VAL_M                                            0x0000FFFFU
#define LGPT_C1CC_VAL_S                                                     0U

//*****************************************************************************
//
// Register: LGPT_O_C2CC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Capture Compare value.
//
// User defined compare value or channel-updated capture value.
//
// A read or write to this register will clear the RIS.C2CC interrupt.
//
// Compare mode:
// VAL is compared against CNTR.VAL and an event is generated as specified by
// C2CFG.CCACT when these are equal.
//
// Capture mode:
// The current counter value is stored in VAL when a capture event occurs.
// C2CFG.CCACT determines if VAL is a signal period or a regular capture value.
#define LGPT_C2CC_VAL_W                                                    16U
#define LGPT_C2CC_VAL_M                                            0x0000FFFFU
#define LGPT_C2CC_VAL_S                                                     0U

//*****************************************************************************
//
// Register: LGPT_O_PTGTNC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// A read or write to this register will not clear the RIS.TGT interrupt.
//
// If CTL.MODE != QDEC.
// Target value for next counter period.
// The timer copies VAL to TGT.VAL when CNTR.VAL becomes 0. The copy does not
// happen when restarting the timer.
// This is useful to avoid period jitter in PWM applications with time-varying
// period, sometimes referenced as phase corrected PWM.
//
// If CTL.MODE = QDEC.
// The CNTR.VAL is updated with VAL on IDX. VAL is not loaded into TGT.VAL when
// CNTR.VAL becomes 0.
#define LGPT_PTGTNC_VAL_W                                                  16U
#define LGPT_PTGTNC_VAL_M                                          0x0000FFFFU
#define LGPT_PTGTNC_VAL_S                                                   0U

//*****************************************************************************
//
// Register: LGPT_O_PC0CCNC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Pipeline Capture Compare value.
//
// User defined pipeline compare value or channel-updated capture value.
//
// A read or write to this register will not clear the RIS.C0CC interrupt.
//
// Compare mode:
// An update of VAL will be transferred to C0CC.VAL when the next CNTR.VAL is
// zero and CTL.MODE is different from DIS. This is useful for PWM generation
// and prevents jitter on the edges of the generated signal.
//
// Capture mode:
// When C0CFG.CCACT equals PER_PULSE_WIDTH_MEAS then VAL contains the width of
// the low or high phase of the selected signal. This is specified by
// C0CFG.EDGE.
#define LGPT_PC0CCNC_VAL_W                                                 16U
#define LGPT_PC0CCNC_VAL_M                                         0x0000FFFFU
#define LGPT_PC0CCNC_VAL_S                                                  0U

//*****************************************************************************
//
// Register: LGPT_O_PC1CCNC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Pipeline Capture Compare value.
//
// User defined pipeline compare value or channel-updated capture value.
//
// A read or write to this register will not clear the RIS.C1CC interrupt.
//
// Compare mode:
// An update of VAL will be transferred to C1CC.VAL when the next CNTR.VAL is
// zero and CTL.MODE is different from DIS. This is useful for PWM generation
// and prevents jitter on the edges of the generated signal.
//
// Capture mode:
// When C1CFG.CCACT equals PER_PULSE_WIDTH_MEAS then VAL contains the width of
// the low or high phase of the selected signal. This is specified by
// C1CFG.EDGE.
#define LGPT_PC1CCNC_VAL_W                                                 16U
#define LGPT_PC1CCNC_VAL_M                                         0x0000FFFFU
#define LGPT_PC1CCNC_VAL_S                                                  0U

//*****************************************************************************
//
// Register: LGPT_O_PC2CCNC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Pipeline Capture Compare value.
//
// User defined pipeline compare value or channel-updated capture value.
//
// A read or write to this register will not clear the RIS.C2CC interrupt.
//
// Compare mode:
// An update of VAL will be transferred to C2CC.VAL when the next CNTR.VAL is
// zero and CTL.MODE is different from DIS. This is useful for PWM generation
// and prevents jitter on the edges of the generated signal.
//
// Capture mode:
// When C2CFG.CCACT equals PER_PULSE_WIDTH_MEAS then VAL contains the width of
// the low or high phase of the selected signal. This is specified by
// C2CFG.EDGE.
#define LGPT_PC2CCNC_VAL_W                                                 16U
#define LGPT_PC2CCNC_VAL_M                                         0x0000FFFFU
#define LGPT_PC2CCNC_VAL_S                                                  0U

//*****************************************************************************
//
// Register: LGPT_O_TGTNC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// User defined counter target value.
#define LGPT_TGTNC_VAL_W                                                   16U
#define LGPT_TGTNC_VAL_M                                           0x0000FFFFU
#define LGPT_TGTNC_VAL_S                                                    0U

//*****************************************************************************
//
// Register: LGPT_O_C0CCNC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Capture Compare value.
//
// User defined compare value or channel-updated capture value.
//
// A read or write to this register will not clear the RIS.C0CC interrupt.
//
// Compare mode:
// VAL is compared against CNTR.VAL and an event is generated as specified by
// C0CFG.CCACT when these are equal.
//
// Capture mode:
// The current counter value is stored in VAL when a capture event occurs.
// C0CFG.CCACT determines if VAL is a signal period or a regular capture value.
#define LGPT_C0CCNC_VAL_W                                                  16U
#define LGPT_C0CCNC_VAL_M                                          0x0000FFFFU
#define LGPT_C0CCNC_VAL_S                                                   0U

//*****************************************************************************
//
// Register: LGPT_O_C1CCNC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Capture Compare value.
//
// User defined compare value or channel-updated capture value.
//
// A read or write to this register will not clear the RIS.C1CC interrupt.
//
// Compare mode:
// VAL is compared against CNTR.VAL and an event is generated as specified by
// C1CFG.CCACT when these are equal.
//
// Capture mode:
// The current counter value is stored in VAL when a capture event occurs.
// C1CFG.CCACT determines if VAL is a signal period or a regular capture value.
#define LGPT_C1CCNC_VAL_W                                                  16U
#define LGPT_C1CCNC_VAL_M                                          0x0000FFFFU
#define LGPT_C1CCNC_VAL_S                                                   0U

//*****************************************************************************
//
// Register: LGPT_O_C2CCNC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Capture Compare value.
//
// User defined compare value or channel-updated capture value.
//
// A read or write to this register will not clear the RIS.C2CC interrupt.
//
// Compare mode:
// VAL is compared against CNTR.VAL and an event is generated as specified by
// C2CFG.CCACT when these are equal.
//
// Capture mode:
// The current counter value is stored in VAL when a capture event occurs.
// C2CFG.CCACT determines if VAL is a signal period or a regular capture value.
#define LGPT_C2CCNC_VAL_W                                                  16U
#define LGPT_C2CCNC_VAL_M                                          0x0000FFFFU
#define LGPT_C2CCNC_VAL_S                                                   0U


#endif // __LGPT__
