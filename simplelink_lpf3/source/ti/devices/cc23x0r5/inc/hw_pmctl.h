/******************************************************************************
*  Filename:       hw_pmctl_h
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

#ifndef __HW_PMCTL_H__
#define __HW_PMCTL_H__

//*****************************************************************************
//
// This section defines the register offsets of
// PMCTL component
//
//*****************************************************************************
// Description Register.
#define PMCTL_O_DESC                                                0x00000000U

// Extended Description Register.
#define PMCTL_O_DESCEX                                              0x00000004U

// Shutdown Register.
#define PMCTL_O_SHTDWN                                              0x00000008U

// Sleep Control Register.
#define PMCTL_O_SLPCTL                                              0x0000000CU

// Wakeup Status Register
#define PMCTL_O_WUSTA                                               0x00000010U

// VDDR Control Register.
#define PMCTL_O_VDDRCTL                                             0x00000014U

// Internal. Only to be used through TI provided API.
#define PMCTL_O_SYSFSET                                             0x00000020U

// Internal. Only to be used through TI provided API.
#define PMCTL_O_SYSFCLR                                             0x00000024U

// Internal. Only to be used through TI provided API.
#define PMCTL_O_SYSFSTA                                             0x00000028U

// Reset Control Register.
#define PMCTL_O_RSTCTL                                              0x0000002CU

// Reset Status.
#define PMCTL_O_RSTSTA                                              0x00000030U

// Internal. Only to be used through TI provided API.
#define PMCTL_O_BOOTSTA                                             0x00000034U

// AON Register Status 1.
#define PMCTL_O_AONRSTA1                                            0x0000003CU

// AON Register Set 1.
#define PMCTL_O_AONRSET1                                            0x00000040U

// AON Register Clear 1.
#define PMCTL_O_AONRCLR1                                            0x00000044U

// Internal. Only to be used through TI provided API.
#define PMCTL_O_ETPP                                                0x00000064U

// Internal. Only to be used through TI provided API.
#define PMCTL_O_RETCFG0                                             0x0000007CU

// Internal. Only to be used through TI provided API.
#define PMCTL_O_RETCFG1                                             0x00000080U

// Internal. Only to be used through TI provided API.
#define PMCTL_O_RETCFG2                                             0x00000084U

// Internal. Only to be used through TI provided API.
#define PMCTL_O_RETCFG3                                             0x00000088U

// Internal. Only to be used through TI provided API.
#define PMCTL_O_RETCFG4                                             0x0000008CU

// Internal. Only to be used through TI provided API.
#define PMCTL_O_RETCFG5                                             0x00000090U

// Internal. Only to be used through TI provided API.
#define PMCTL_O_RETCFG6                                             0x00000094U

// Internal. Only to be used through TI provided API.
#define PMCTL_O_RETCFG7                                             0x00000098U

//*****************************************************************************
//
// Register: PMCTL_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module identifier used to uniquely identify this IP.
#define PMCTL_DESC_MODID_W                                                  16U
#define PMCTL_DESC_MODID_M                                          0xFFFF0000U
#define PMCTL_DESC_MODID_S                                                  16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set of from
// aggregated IRQ registers till DTB.
//
// 0: Standard IP MMRs do not exist
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
#define PMCTL_DESC_STDIPOFF_W                                                4U
#define PMCTL_DESC_STDIPOFF_M                                       0x0000F000U
#define PMCTL_DESC_STDIPOFF_S                                               12U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number. If multiple instances of IP exist in the device, this
// field can identify the instance number (0-15).
#define PMCTL_DESC_INSTIDX_W                                                 4U
#define PMCTL_DESC_INSTIDX_M                                        0x00000F00U
#define PMCTL_DESC_INSTIDX_S                                                 8U

// Field:   [7:4] MAJREV
//
// Major revision of IP (0-15).
#define PMCTL_DESC_MAJREV_W                                                  4U
#define PMCTL_DESC_MAJREV_M                                         0x000000F0U
#define PMCTL_DESC_MAJREV_S                                                  4U

// Field:   [3:0] MINREV
//
// Minor revision of IP (0-15).
#define PMCTL_DESC_MINREV_W                                                  4U
#define PMCTL_DESC_MINREV_M                                         0x0000000FU
#define PMCTL_DESC_MINREV_S                                                  0U

//*****************************************************************************
//
// Register: PMCTL_O_DESCEX
//
//*****************************************************************************
// Field: [31:30] FLASHSZ
//
// System flash availability
// ENUMs:
// SZ3                      Flash size set to level 3 (Max size)
// SZ2                      Flash size set to level 2
// SZ1                      Flash size set to level 1
// SZ0                      Flash size set to level 0 (Min size)
#define PMCTL_DESCEX_FLASHSZ_W                                               2U
#define PMCTL_DESCEX_FLASHSZ_M                                      0xC0000000U
#define PMCTL_DESCEX_FLASHSZ_S                                              30U
#define PMCTL_DESCEX_FLASHSZ_SZ3                                    0xC0000000U
#define PMCTL_DESCEX_FLASHSZ_SZ2                                    0x80000000U
#define PMCTL_DESCEX_FLASHSZ_SZ1                                    0x40000000U
#define PMCTL_DESCEX_FLASHSZ_SZ0                                    0x00000000U

// Field: [29:28] SRAMSZ
//
// System SRAM availability
// ENUMs:
// SZ3                      SRAM size set to level 3 (Max size)
// SZ2                      SRAM size set to level 2
// SZ1                      SRAM size set to level 1
// SZ0                      SRAM size set to level 0 (Min size)
#define PMCTL_DESCEX_SRAMSZ_W                                                2U
#define PMCTL_DESCEX_SRAMSZ_M                                       0x30000000U
#define PMCTL_DESCEX_SRAMSZ_S                                               28U
#define PMCTL_DESCEX_SRAMSZ_SZ3                                     0x30000000U
#define PMCTL_DESCEX_SRAMSZ_SZ2                                     0x20000000U
#define PMCTL_DESCEX_SRAMSZ_SZ1                                     0x10000000U
#define PMCTL_DESCEX_SRAMSZ_SZ0                                     0x00000000U

// Field:    [27] TSD
//
//  TSD (thermal shutdown) IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define PMCTL_DESCEX_TSD                                            0x08000000U
#define PMCTL_DESCEX_TSD_M                                          0x08000000U
#define PMCTL_DESCEX_TSD_S                                                  27U
#define PMCTL_DESCEX_TSD_IP_AVAIL                                   0x08000000U
#define PMCTL_DESCEX_TSD_IP_UNAVAIL                                 0x00000000U

// Field:    [26] LPCMP
//
// LPCMP (low power comparator) IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define PMCTL_DESCEX_LPCMP                                          0x04000000U
#define PMCTL_DESCEX_LPCMP_M                                        0x04000000U
#define PMCTL_DESCEX_LPCMP_S                                                26U
#define PMCTL_DESCEX_LPCMP_IP_AVAIL                                 0x04000000U
#define PMCTL_DESCEX_LPCMP_IP_UNAVAIL                               0x00000000U

//*****************************************************************************
//
// Register: PMCTL_O_SHTDWN
//
//*****************************************************************************
// Field:  [15:0] KEY
//
// Setting a valid key will trigger the device to enter SHUTDOWN mode.
// ENUMs:
// VALID                    This is the only valid key value that will trigger
//                          SHUTDOWN mode.
//                          All other values are
//                          invalid and will have no effect.
#define PMCTL_SHTDWN_KEY_W                                                  16U
#define PMCTL_SHTDWN_KEY_M                                          0x0000FFFFU
#define PMCTL_SHTDWN_KEY_S                                                   0U
#define PMCTL_SHTDWN_KEY_VALID                                      0x0000A5A5U

//*****************************************************************************
//
// Register: PMCTL_O_SLPCTL
//
//*****************************************************************************
// Field:     [0] SLPN
//
// The boot code will set this bit field and disable sleep mode, automatically
// unless waking up from a SHUTDOWN RSTSTA.SDDET is set.
// Application software must reconfigure the state for all IO's before setting
// this bit field upon waking up from a SHUTDOWN to avoid glitches on pins.
// ENUMs:
// DIS                      I/O pad sleep mode is disabled
// EN                       I/O pad sleep mode is enabled
#define PMCTL_SLPCTL_SLPN                                           0x00000001U
#define PMCTL_SLPCTL_SLPN_M                                         0x00000001U
#define PMCTL_SLPCTL_SLPN_S                                                  0U
#define PMCTL_SLPCTL_SLPN_DIS                                       0x00000001U
#define PMCTL_SLPCTL_SLPN_EN                                        0x00000000U

//*****************************************************************************
//
// Register: PMCTL_O_WUSTA
//
//*****************************************************************************
// Field:   [1:0] SRC
//
// This field shows the device wakeup source.
// ENUMs:
// STBY                     Wakeup from STANDBY mode.
// RST_SHTDWN               Wakeup from system reset / SHUTDOWN mode.
//                          See RSTSTA for more
//                          status information.
#define PMCTL_WUSTA_SRC_W                                                    2U
#define PMCTL_WUSTA_SRC_M                                           0x00000003U
#define PMCTL_WUSTA_SRC_S                                                    0U
#define PMCTL_WUSTA_SRC_STBY                                        0x00000002U
#define PMCTL_WUSTA_SRC_RST_SHTDWN                                  0x00000001U

//*****************************************************************************
//
// Register: PMCTL_O_VDDRCTL
//
//*****************************************************************************
// Field:     [1] STBY
//
// Select between continuous or duty-cycled VDDR regulation in STANDBY mode.
// ENUMs:
// PSUEDO                   Continuous VDDR regulation in STANDBY mode.
// NORMAL                   Duty-cycled VDDR regulation in STANDBY mode.
#define PMCTL_VDDRCTL_STBY                                          0x00000002U
#define PMCTL_VDDRCTL_STBY_M                                        0x00000002U
#define PMCTL_VDDRCTL_STBY_S                                                 1U
#define PMCTL_VDDRCTL_STBY_PSUEDO                                   0x00000002U
#define PMCTL_VDDRCTL_STBY_NORMAL                                   0x00000000U

// Field:     [0] SELECT
//
// Select between GLDO and DCDC as VDDR regulator (in ACTIVE, IDLE and STANDBY
// mode).
// ENUMs:
// DCDC                     DCDC enabled for regulation of VDDR voltage
// GLDO                     GLDO enabled for regulation of VDDR voltage
#define PMCTL_VDDRCTL_SELECT                                        0x00000001U
#define PMCTL_VDDRCTL_SELECT_M                                      0x00000001U
#define PMCTL_VDDRCTL_SELECT_S                                               0U
#define PMCTL_VDDRCTL_SELECT_DCDC                                   0x00000001U
#define PMCTL_VDDRCTL_SELECT_GLDO                                   0x00000000U

//*****************************************************************************
//
// Register: PMCTL_O_SYSFSET
//
//*****************************************************************************
// Field:     [2] FLAG2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// NOEFF                    Internal. Only to be used through TI provided API.
#define PMCTL_SYSFSET_FLAG2                                         0x00000004U
#define PMCTL_SYSFSET_FLAG2_M                                       0x00000004U
#define PMCTL_SYSFSET_FLAG2_S                                                2U
#define PMCTL_SYSFSET_FLAG2_SET                                     0x00000004U
#define PMCTL_SYSFSET_FLAG2_NOEFF                                   0x00000000U

// Field:     [1] FLAG1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// NOEFF                    Internal. Only to be used through TI provided API.
#define PMCTL_SYSFSET_FLAG1                                         0x00000002U
#define PMCTL_SYSFSET_FLAG1_M                                       0x00000002U
#define PMCTL_SYSFSET_FLAG1_S                                                1U
#define PMCTL_SYSFSET_FLAG1_SET                                     0x00000002U
#define PMCTL_SYSFSET_FLAG1_NOEFF                                   0x00000000U

// Field:     [0] FLAG0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// NOEFF                    Internal. Only to be used through TI provided API.
#define PMCTL_SYSFSET_FLAG0                                         0x00000001U
#define PMCTL_SYSFSET_FLAG0_M                                       0x00000001U
#define PMCTL_SYSFSET_FLAG0_S                                                0U
#define PMCTL_SYSFSET_FLAG0_SET                                     0x00000001U
#define PMCTL_SYSFSET_FLAG0_NOEFF                                   0x00000000U

//*****************************************************************************
//
// Register: PMCTL_O_SYSFCLR
//
//*****************************************************************************
// Field:     [2] FLAG2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLR                      Internal. Only to be used through TI provided API.
// NOEFF                    Internal. Only to be used through TI provided API.
#define PMCTL_SYSFCLR_FLAG2                                         0x00000004U
#define PMCTL_SYSFCLR_FLAG2_M                                       0x00000004U
#define PMCTL_SYSFCLR_FLAG2_S                                                2U
#define PMCTL_SYSFCLR_FLAG2_CLR                                     0x00000004U
#define PMCTL_SYSFCLR_FLAG2_NOEFF                                   0x00000000U

// Field:     [1] FLAG1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLR                      Internal. Only to be used through TI provided API.
// NOEFF                    Internal. Only to be used through TI provided API.
#define PMCTL_SYSFCLR_FLAG1                                         0x00000002U
#define PMCTL_SYSFCLR_FLAG1_M                                       0x00000002U
#define PMCTL_SYSFCLR_FLAG1_S                                                1U
#define PMCTL_SYSFCLR_FLAG1_CLR                                     0x00000002U
#define PMCTL_SYSFCLR_FLAG1_NOEFF                                   0x00000000U

// Field:     [0] FLAG0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLR                      Internal. Only to be used through TI provided API.
// NOEFF                    Internal. Only to be used through TI provided API.
#define PMCTL_SYSFCLR_FLAG0                                         0x00000001U
#define PMCTL_SYSFCLR_FLAG0_M                                       0x00000001U
#define PMCTL_SYSFCLR_FLAG0_S                                                0U
#define PMCTL_SYSFCLR_FLAG0_CLR                                     0x00000001U
#define PMCTL_SYSFCLR_FLAG0_NOEFF                                   0x00000000U

//*****************************************************************************
//
// Register: PMCTL_O_SYSFSTA
//
//*****************************************************************************
// Field:     [2] FLAG2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VAL1                     Internal. Only to be used through TI provided API.
// VAL0                     Internal. Only to be used through TI provided API.
#define PMCTL_SYSFSTA_FLAG2                                         0x00000004U
#define PMCTL_SYSFSTA_FLAG2_M                                       0x00000004U
#define PMCTL_SYSFSTA_FLAG2_S                                                2U
#define PMCTL_SYSFSTA_FLAG2_VAL1                                    0x00000004U
#define PMCTL_SYSFSTA_FLAG2_VAL0                                    0x00000000U

// Field:     [1] FLAG1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VAL1                     Internal. Only to be used through TI provided API.
#define PMCTL_SYSFSTA_FLAG1                                         0x00000002U
#define PMCTL_SYSFSTA_FLAG1_M                                       0x00000002U
#define PMCTL_SYSFSTA_FLAG1_S                                                1U
#define PMCTL_SYSFSTA_FLAG1_VAL1                                    0x00000002U

// Field:     [0] FLAG0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VAL1                     Internal. Only to be used through TI provided API.
// VAL0                     Internal. Only to be used through TI provided API.
#define PMCTL_SYSFSTA_FLAG0                                         0x00000001U
#define PMCTL_SYSFSTA_FLAG0_M                                       0x00000001U
#define PMCTL_SYSFSTA_FLAG0_S                                                0U
#define PMCTL_SYSFSTA_FLAG0_VAL1                                    0x00000001U
#define PMCTL_SYSFSTA_FLAG0_VAL0                                    0x00000000U

//*****************************************************************************
//
// Register: PMCTL_O_RSTCTL
//
//*****************************************************************************
// Field:     [2] LFLOSS
//
// LF clock loss reset enable.
// Trigger system reset when LF clock loss is detected, which reset the entire
// device and causes a reboot of the system.
// The system reset event is captured as RSTSTA.RESETSRC set to SYSRESET and
// RSTSTA.SYSSRC set to LFLOSSEV.
// ENUMs:
// ARMED                    LF clock loss detection will trigger a system
//                          reset.
// DISARMED                 LF clock loss detection will not trigger a system
//                          reset.
#define PMCTL_RSTCTL_LFLOSS                                         0x00000004U
#define PMCTL_RSTCTL_LFLOSS_M                                       0x00000004U
#define PMCTL_RSTCTL_LFLOSS_S                                                2U
#define PMCTL_RSTCTL_LFLOSS_ARMED                                   0x00000004U
#define PMCTL_RSTCTL_LFLOSS_DISARMED                                0x00000000U

// Field:     [1] TSDEN
//
// TSD (Thermal Shutdown) enable.
// TSD will trigger an immediate system reset, which reset the entire device
// and causes a reboot of the system.
// The device will be in reset until released by the TSD IP.
// The system reset event is captured as RSTSTA.TSDEV flag set.
// ENUMs:
// EN                       Temperature shutdown comparator enable.
//                          Note: If TSD IP not
//                          present, see DESCEX.TSD, enable will have no
//                          effect.
// NOEFF                    No effect
#define PMCTL_RSTCTL_TSDEN                                          0x00000002U
#define PMCTL_RSTCTL_TSDEN_M                                        0x00000002U
#define PMCTL_RSTCTL_TSDEN_S                                                 1U
#define PMCTL_RSTCTL_TSDEN_EN                                       0x00000002U
#define PMCTL_RSTCTL_TSDEN_NOEFF                                    0x00000000U

// Field:     [0] SYSRST
//
// Trigger system reset, which will reset the entire device and causes a reboot
// of the system.
// The system reset event is captured as RSTSTA.RESETSRC set to SYSRESET and
// RSTSTA.SYSSRC set to SYSRSTEV.
// ENUMs:
// SET                      Trigger a system reset.
// NOEFF                    No effect
#define PMCTL_RSTCTL_SYSRST                                         0x00000001U
#define PMCTL_RSTCTL_SYSRST_M                                       0x00000001U
#define PMCTL_RSTCTL_SYSRST_S                                                0U
#define PMCTL_RSTCTL_SYSRST_SET                                     0x00000001U
#define PMCTL_RSTCTL_SYSRST_NOEFF                                   0x00000000U

//*****************************************************************************
//
// Register: PMCTL_O_RSTSTA
//
//*****************************************************************************
// Field:    [17] SDDET
//
// Wakeup from SHUTDOWN flag.
// Note: This flag will be cleared when SLPCTL.SLPN is asserted.
// ENUMs:
// TRIG                     Wakeup from SHUTDOWN mode
// NO_TRIG                  Wakeup from SHUTDOWN mode not triggered
#define PMCTL_RSTSTA_SDDET                                          0x00020000U
#define PMCTL_RSTSTA_SDDET_M                                        0x00020000U
#define PMCTL_RSTSTA_SDDET_S                                                17U
#define PMCTL_RSTSTA_SDDET_TRIG                                     0x00020000U
#define PMCTL_RSTSTA_SDDET_NO_TRIG                                  0x00000000U

// Field:    [16] IOWUSD
//
// Wakeup from SHUTDOWN on an I/O event flag.
// Note: This flag will be cleared when SLPCTL.SLPN is asserted.
// ENUMs:
// TRIG                     Wakeup from SHUTDOWN triggered by an I/O event.
// NO_TRIG                  Wakeup from SHUTDOWN not triggered by an I/O
//                          event.
#define PMCTL_RSTSTA_IOWUSD                                         0x00010000U
#define PMCTL_RSTSTA_IOWUSD_M                                       0x00010000U
#define PMCTL_RSTSTA_IOWUSD_S                                               16U
#define PMCTL_RSTSTA_IOWUSD_TRIG                                    0x00010000U
#define PMCTL_RSTSTA_IOWUSD_NO_TRIG                                 0x00000000U

// Field:   [7:4] SYSSRC
//
// Shows which reset event that triggered SYSRESET in RESETSRC
// ENUMs:
// DERREV                   Digital Error reset event
// AERREV                   Analog Error reset event
// AFSMEV                   Analog FSM timeout event
// SWDRSTEV                 Serial Wire Debug reset event
// SYSRSTEV                 System reset event
// WDTEV                    Watchdog timeout event
// LOCKUPEV                 CPU LOCKUP event
// CPURSTEV                 CPU reset event
// LFLOSSEV                 LF clock loss event
#define PMCTL_RSTSTA_SYSSRC_W                                                4U
#define PMCTL_RSTSTA_SYSSRC_M                                       0x000000F0U
#define PMCTL_RSTSTA_SYSSRC_S                                                4U
#define PMCTL_RSTSTA_SYSSRC_DERREV                                  0x000000F0U
#define PMCTL_RSTSTA_SYSSRC_AERREV                                  0x000000E0U
#define PMCTL_RSTSTA_SYSSRC_AFSMEV                                  0x00000060U
#define PMCTL_RSTSTA_SYSSRC_SWDRSTEV                                0x00000050U
#define PMCTL_RSTSTA_SYSSRC_SYSRSTEV                                0x00000040U
#define PMCTL_RSTSTA_SYSSRC_WDTEV                                   0x00000030U
#define PMCTL_RSTSTA_SYSSRC_LOCKUPEV                                0x00000020U
#define PMCTL_RSTSTA_SYSSRC_CPURSTEV                                0x00000010U
#define PMCTL_RSTSTA_SYSSRC_LFLOSSEV                                0x00000000U

// Field:     [3] TSDEV
//
// System reset triggered by TSD event
// ENUMs:
// TRIG                     System reset triggered by TSD event
// NO_TRIG                  TSD event not triggered
#define PMCTL_RSTSTA_TSDEV                                          0x00000008U
#define PMCTL_RSTSTA_TSDEV_M                                        0x00000008U
#define PMCTL_RSTSTA_TSDEV_S                                                 3U
#define PMCTL_RSTSTA_TSDEV_TRIG                                     0x00000008U
#define PMCTL_RSTSTA_TSDEV_NO_TRIG                                  0x00000000U

// Field:   [2:0] RESETSRC
//
// Shows the root cause of the last system reset. More than one reported reset
// source can have been active during the last system reset, but only the root
// cause is reported.
// If reset cause is SYSRESET or PINRESET, the other reset flags must be read
// to determine actual root cause.
// ENUMs:
// SYSRESET                 Digital system reset. Actual root cause is given
//                          by SYSSRC.
// VDDRLOSS                 Brown out detect on VDDR
// VDDSLOSS                 Brown out detect on VDDS
// PINRESET                 Reset pin. TSD will also trigger a pin reset, so
//                          actual root cause is given by TSDEV reset flag
//                          status.
// PWRON                    Power on reset
#define PMCTL_RSTSTA_RESETSRC_W                                              3U
#define PMCTL_RSTSTA_RESETSRC_M                                     0x00000007U
#define PMCTL_RSTSTA_RESETSRC_S                                              0U
#define PMCTL_RSTSTA_RESETSRC_SYSRESET                              0x00000006U
#define PMCTL_RSTSTA_RESETSRC_VDDRLOSS                              0x00000004U
#define PMCTL_RSTSTA_RESETSRC_VDDSLOSS                              0x00000002U
#define PMCTL_RSTSTA_RESETSRC_PINRESET                              0x00000001U
#define PMCTL_RSTSTA_RESETSRC_PWRON                                 0x00000000U

//*****************************************************************************
//
// Register: PMCTL_O_BOOTSTA
//
//*****************************************************************************
// Field:   [7:0] FLAG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// APP_FAULT_HANDLER        Internal. Only to be used through TI provided API.
// APP_FAIL_APPTRANSFER     Internal. Only to be used through TI provided API.
// APP_FAIL_NOAPP           Internal. Only to be used through TI provided API.
// APP_WAITLOOP_DBGPROBE    Internal. Only to be used through TI provided API.
// MODE_APP                 Internal. Only to be used through TI provided API.
// BLDR_FAULT_HANDLER       Internal. Only to be used through TI provided API.
// BLDR_FAIL_APPTRANSFER    Internal. Only to be used through TI provided API.
// BLDR_FAIL_EXECUTION_CONTEXTInternal. Only to be used through TI provided
// API.
// BLDR_CMD_PROCESSING      Internal. Only to be used through TI provided API.
// BLDR_CMD_IDLE            Internal. Only to be used through TI provided API.
// BLDR_STARTED             Internal. Only to be used through TI provided API.
// BLDR_WAITLOOP_DBGPROBE   Internal. Only to be used through TI provided API.
// MODE_BLDR                Internal. Only to be used through TI provided API.
// BOOT_FAULT_HANDLER       Internal. Only to be used through TI provided API.
// BOOT_FAIL_SRAM_REPAIR    Internal. Only to be used through TI provided API.
// BOOT_WAITLOOP_DBGPROBE   Internal. Only to be used through TI provided API.
// BOOT_EXITED_SACI         Internal. Only to be used through TI provided API.
// BOOT_WAIT_SWD_DISCONNECT Internal. Only to be used through TI provided API.
// BOOT_ENTERED_SACI        Internal. Only to be used through TI provided API.
// BOOT_GENERAL_TRIMS       Internal. Only to be used through TI provided API.
// BOOT_SRAM_REP_DONE       Internal. Only to be used through TI provided API.
// BOOT_COLD_BOOT           Internal. Only to be used through TI provided API.
// BOOT_RESET               Internal. Only to be used through TI provided API.
#define PMCTL_BOOTSTA_FLAG_W                                                 8U
#define PMCTL_BOOTSTA_FLAG_M                                        0x000000FFU
#define PMCTL_BOOTSTA_FLAG_S                                                 0U
#define PMCTL_BOOTSTA_FLAG_APP_FAULT_HANDLER                        0x000000FFU
#define PMCTL_BOOTSTA_FLAG_APP_FAIL_APPTRANSFER                     0x000000FEU
#define PMCTL_BOOTSTA_FLAG_APP_FAIL_NOAPP                           0x000000FDU
#define PMCTL_BOOTSTA_FLAG_APP_WAITLOOP_DBGPROBE                    0x000000C1U
#define PMCTL_BOOTSTA_FLAG_MODE_APP                                 0x000000C0U
#define PMCTL_BOOTSTA_FLAG_BLDR_FAULT_HANDLER                       0x000000BFU
#define PMCTL_BOOTSTA_FLAG_BLDR_FAIL_APPTRANSFER                    0x000000BEU
#define PMCTL_BOOTSTA_FLAG_BLDR_FAIL_EXECUTION_CONTEXT              0x000000BDU
#define PMCTL_BOOTSTA_FLAG_BLDR_CMD_PROCESSING                      0x000000BCU
#define PMCTL_BOOTSTA_FLAG_BLDR_CMD_IDLE                            0x000000BBU
#define PMCTL_BOOTSTA_FLAG_BLDR_STARTED                             0x000000BAU
#define PMCTL_BOOTSTA_FLAG_BLDR_WAITLOOP_DBGPROBE                   0x00000081U
#define PMCTL_BOOTSTA_FLAG_MODE_BLDR                                0x00000080U
#define PMCTL_BOOTSTA_FLAG_BOOT_FAULT_HANDLER                       0x0000003FU
#define PMCTL_BOOTSTA_FLAG_BOOT_FAIL_SRAM_REPAIR                    0x0000003EU
#define PMCTL_BOOTSTA_FLAG_BOOT_WAITLOOP_DBGPROBE                   0x00000038U
#define PMCTL_BOOTSTA_FLAG_BOOT_EXITED_SACI                         0x00000037U
#define PMCTL_BOOTSTA_FLAG_BOOT_WAIT_SWD_DISCONNECT                 0x00000036U
#define PMCTL_BOOTSTA_FLAG_BOOT_ENTERED_SACI                        0x00000020U
#define PMCTL_BOOTSTA_FLAG_BOOT_GENERAL_TRIMS                       0x00000003U
#define PMCTL_BOOTSTA_FLAG_BOOT_SRAM_REP_DONE                       0x00000002U
#define PMCTL_BOOTSTA_FLAG_BOOT_COLD_BOOT                           0x00000001U
#define PMCTL_BOOTSTA_FLAG_BOOT_RESET                               0x00000000U

//*****************************************************************************
//
// Register: PMCTL_O_AONRSTA1
//
//*****************************************************************************
// Field:  [17:0] FLAG
//
// State of the AON register flags
#define PMCTL_AONRSTA1_FLAG_W                                               18U
#define PMCTL_AONRSTA1_FLAG_M                                       0x0003FFFFU
#define PMCTL_AONRSTA1_FLAG_S                                                0U

//*****************************************************************************
//
// Register: PMCTL_O_AONRSET1
//
//*****************************************************************************
// Field:  [17:0] FLAG
//
// Write 1 to set AONRSTA1.FLAG
// ENUMs:
// ALL_SET                  Set all flags
// NOEFF                    No flags changed status
#define PMCTL_AONRSET1_FLAG_W                                               18U
#define PMCTL_AONRSET1_FLAG_M                                       0x0003FFFFU
#define PMCTL_AONRSET1_FLAG_S                                                0U
#define PMCTL_AONRSET1_FLAG_ALL_SET                                 0x0003FFFFU
#define PMCTL_AONRSET1_FLAG_NOEFF                                   0x00000000U

//*****************************************************************************
//
// Register: PMCTL_O_AONRCLR1
//
//*****************************************************************************
// Field:  [17:0] FLAG
//
// Write 1 to clear AONRSTA1.FLAG
// ENUMs:
// ALL_CLR                  Clear all flags
// NOEFF                    No flags changed status
#define PMCTL_AONRCLR1_FLAG_W                                               18U
#define PMCTL_AONRCLR1_FLAG_M                                       0x0003FFFFU
#define PMCTL_AONRCLR1_FLAG_S                                                0U
#define PMCTL_AONRCLR1_FLAG_ALL_CLR                                 0x0003FFFFU
#define PMCTL_AONRCLR1_FLAG_NOEFF                                   0x00000000U

//*****************************************************************************
//
// Register: PMCTL_O_ETPP
//
//*****************************************************************************
//*****************************************************************************
//
// Register: PMCTL_O_RETCFG0
//
//*****************************************************************************
// Field:     [0] VAL
//
// Internal. Only to be used through TI provided API.
#define PMCTL_RETCFG0_VAL                                           0x00000001U
#define PMCTL_RETCFG0_VAL_M                                         0x00000001U
#define PMCTL_RETCFG0_VAL_S                                                  0U

//*****************************************************************************
//
// Register: PMCTL_O_RETCFG1
//
//*****************************************************************************
// Field:     [0] VAL
//
// Internal. Only to be used through TI provided API.
#define PMCTL_RETCFG1_VAL                                           0x00000001U
#define PMCTL_RETCFG1_VAL_M                                         0x00000001U
#define PMCTL_RETCFG1_VAL_S                                                  0U

//*****************************************************************************
//
// Register: PMCTL_O_RETCFG2
//
//*****************************************************************************
// Field:   [2:0] VAL
//
// Internal. Only to be used through TI provided API.
#define PMCTL_RETCFG2_VAL_W                                                  3U
#define PMCTL_RETCFG2_VAL_M                                         0x00000007U
#define PMCTL_RETCFG2_VAL_S                                                  0U

//*****************************************************************************
//
// Register: PMCTL_O_RETCFG3
//
//*****************************************************************************
//*****************************************************************************
//
// Register: PMCTL_O_RETCFG4
//
//*****************************************************************************
//*****************************************************************************
//
// Register: PMCTL_O_RETCFG5
//
//*****************************************************************************
//*****************************************************************************
//
// Register: PMCTL_O_RETCFG6
//
//*****************************************************************************
//*****************************************************************************
//
// Register: PMCTL_O_RETCFG7
//
//*****************************************************************************

#endif // __PMCTL__
