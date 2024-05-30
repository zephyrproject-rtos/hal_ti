/******************************************************************************
*  Filename:       hw_sys0_h
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

#ifndef __HW_SYS0_H__
#define __HW_SYS0_H__

//*****************************************************************************
//
// This section defines the register offsets of
// SYS0 component
//
//*****************************************************************************
// Description Register
#define SYS0_O_DESC                                                 0x00000000U

// Mutable section Unlock
#define SYS0_O_MUNLOCK                                              0x0000000CU

// ATEST Configuration
#define SYS0_O_ATESTCFG                                             0x00000100U

// TSENSE Configuration
#define SYS0_O_TSENSCFG                                             0x00000108U

// LPCMP configuration
#define SYS0_O_LPCMPCFG                                             0x0000010CU

// Device ID
#define SYS0_O_DEVICEID                                             0x000003FCU

// Part ID
#define SYS0_O_PARTID                                               0x000007F8U

// Internal. Only to be used through TI provided API.
#define SYS0_O_TMUTE0                                               0x00000800U

// Internal. Only to be used through TI provided API.
#define SYS0_O_TMUTE1                                               0x00000804U

// TMUTE2 trim Register
#define SYS0_O_TMUTE2                                               0x00000808U

// Internal. Only to be used through TI provided API.
#define SYS0_O_TMUTE3                                               0x0000080CU

// TMUTE4 trim Register
#define SYS0_O_TMUTE4                                               0x00000810U

// Internal. Only to be used through TI provided API.
#define SYS0_O_TMUTE5                                               0x00000814U

//*****************************************************************************
//
// Register: SYS0_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module Identifier is used to uniquely identify this IP
#define SYS0_DESC_MODID_W                                                   16U
#define SYS0_DESC_MODID_M                                           0xFFFF0000U
#define SYS0_DESC_MODID_S                                                   16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set from aggregated
// IRQ registers till DTB.
//
// 0: Standard IP MMRs do not exist
//
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
#define SYS0_DESC_STDIPOFF_W                                                 4U
#define SYS0_DESC_STDIPOFF_M                                        0x0000F000U
#define SYS0_DESC_STDIPOFF_S                                                12U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number. If multiple instances of IP exist in the device, this
// field can identify the instance number (0-15).
#define SYS0_DESC_INSTIDX_W                                                  4U
#define SYS0_DESC_INSTIDX_M                                         0x00000F00U
#define SYS0_DESC_INSTIDX_S                                                  8U

// Field:   [7:4] MAJREV
//
// Major revision of IP (0-15).
#define SYS0_DESC_MAJREV_W                                                   4U
#define SYS0_DESC_MAJREV_M                                          0x000000F0U
#define SYS0_DESC_MAJREV_S                                                   4U

// Field:   [3:0] MINREV
//
// Minor revision of IP (0-15).
#define SYS0_DESC_MINREV_W                                                   4U
#define SYS0_DESC_MINREV_M                                          0x0000000FU
#define SYS0_DESC_MINREV_S                                                   0U

//*****************************************************************************
//
// Register: SYS0_O_MUNLOCK
//
//*****************************************************************************
// Field:  [31:0] KEY
//
// Write the unlock key 0xC5AF_6927 to temporarily unlock registers in mutable
// section. The lock is set automatically if no write accesses, to the mutable
// section, are detected for consecutive 32 CLKULL (24MHz) clock cycles.
// Writing any value other that the unlock key will immediately lock the
// mutable register space for write access.
// ENUMs:
// UNLOCK                   Unlock registers in the mutable section
// LOCK                     Lock registers in the mutable section
#define SYS0_MUNLOCK_KEY_W                                                  32U
#define SYS0_MUNLOCK_KEY_M                                          0xFFFFFFFFU
#define SYS0_MUNLOCK_KEY_S                                                   0U
#define SYS0_MUNLOCK_KEY_UNLOCK                                     0xC5AF6927U
#define SYS0_MUNLOCK_KEY_LOCK                                       0x00000000U

//*****************************************************************************
//
// Register: SYS0_O_ATESTCFG
//
//*****************************************************************************
// Field: [31:24] KEY
//
// Key must be written with value 0x5A for successful write to ATESTCFG and to
// unlock register state.
// Write with any value other than 0x5A to KEY will be ignored and register
// content is not updated.
// It is recommended to write this register with incorrect KEY to lock back
// register state after necessary ATESTCFG updates are done.
// Read value of KEY is 0x0.
#define SYS0_ATESTCFG_KEY_W                                                  8U
#define SYS0_ATESTCFG_KEY_M                                         0xFF000000U
#define SYS0_ATESTCFG_KEY_S                                                 24U

// Field:     [8] VSEL
//
// Selects supply for ATEST switches.
// ENUMs:
// VDDA                     Selects VDDA
// VDDBST                   Selects VDDBOOST
#define SYS0_ATESTCFG_VSEL                                          0x00000100U
#define SYS0_ATESTCFG_VSEL_M                                        0x00000100U
#define SYS0_ATESTCFG_VSEL_S                                                 8U
#define SYS0_ATESTCFG_VSEL_VDDA                                     0x00000100U
#define SYS0_ATESTCFG_VSEL_VDDBST                                   0x00000000U

// Field:     [7] VA2VA1
//
// Enables isolation switch between VA_ATEST_A1 and VA_PAD_A1.
// ENUMs:
// CLOSE                    Switch is closed
// OPEN                     Switch is open
#define SYS0_ATESTCFG_VA2VA1                                        0x00000080U
#define SYS0_ATESTCFG_VA2VA1_M                                      0x00000080U
#define SYS0_ATESTCFG_VA2VA1_S                                               7U
#define SYS0_ATESTCFG_VA2VA1_CLOSE                                  0x00000080U
#define SYS0_ATESTCFG_VA2VA1_OPEN                                   0x00000000U

// Field:     [6] VA2VA0
//
// Enables isolation switch between VA_ATEST_A0 and VA_PAD_A0.
// ENUMs:
// CLOSE                    Switch is closed
// OPEN                     Switch is open
#define SYS0_ATESTCFG_VA2VA0                                        0x00000040U
#define SYS0_ATESTCFG_VA2VA0_M                                      0x00000040U
#define SYS0_ATESTCFG_VA2VA0_S                                               6U
#define SYS0_ATESTCFG_VA2VA0_CLOSE                                  0x00000040U
#define SYS0_ATESTCFG_VA2VA0_OPEN                                   0x00000000U

// Field:     [5] VR2VA1
//
// Enables isolation switch between VR_ATEST_A1 and VA_ATEST_A1.
// ENUMs:
// CLOSE                    Switch is closed
// OPEN                     Switch is open
#define SYS0_ATESTCFG_VR2VA1                                        0x00000020U
#define SYS0_ATESTCFG_VR2VA1_M                                      0x00000020U
#define SYS0_ATESTCFG_VR2VA1_S                                               5U
#define SYS0_ATESTCFG_VR2VA1_CLOSE                                  0x00000020U
#define SYS0_ATESTCFG_VR2VA1_OPEN                                   0x00000000U

// Field:     [4] VR2VA0
//
// Enables isolation switch between VR_ATEST_A0 and VA_ATEST_A0.
// ENUMs:
// CLOSE                    Switch is closed
// OPEN                     Switch is open
#define SYS0_ATESTCFG_VR2VA0                                        0x00000010U
#define SYS0_ATESTCFG_VR2VA0_M                                      0x00000010U
#define SYS0_ATESTCFG_VR2VA0_S                                               4U
#define SYS0_ATESTCFG_VR2VA0_CLOSE                                  0x00000010U
#define SYS0_ATESTCFG_VR2VA0_OPEN                                   0x00000000U

// Field:     [3] SHTVA1
//
// Shorts VA_ATEST_A1 to ground.
// ENUMs:
// CLOSE                    Switch is closed
// OPEN                     Switch is open
#define SYS0_ATESTCFG_SHTVA1                                        0x00000008U
#define SYS0_ATESTCFG_SHTVA1_M                                      0x00000008U
#define SYS0_ATESTCFG_SHTVA1_S                                               3U
#define SYS0_ATESTCFG_SHTVA1_CLOSE                                  0x00000008U
#define SYS0_ATESTCFG_SHTVA1_OPEN                                   0x00000000U

// Field:     [2] SHTVA0
//
// Shorts VA_ATEST_A0 to ground.
// ENUMs:
// CLOSE                    Switch is closed
// OPEN                     Switch is open
#define SYS0_ATESTCFG_SHTVA0                                        0x00000004U
#define SYS0_ATESTCFG_SHTVA0_M                                      0x00000004U
#define SYS0_ATESTCFG_SHTVA0_S                                               2U
#define SYS0_ATESTCFG_SHTVA0_CLOSE                                  0x00000004U
#define SYS0_ATESTCFG_SHTVA0_OPEN                                   0x00000000U

// Field:     [1] SHTVR1
//
// Shorts VR_ATEST_A1 to ground.
// ENUMs:
// CLOSE                    Switch is closed
// OPEN                     Switch is open
#define SYS0_ATESTCFG_SHTVR1                                        0x00000002U
#define SYS0_ATESTCFG_SHTVR1_M                                      0x00000002U
#define SYS0_ATESTCFG_SHTVR1_S                                               1U
#define SYS0_ATESTCFG_SHTVR1_CLOSE                                  0x00000002U
#define SYS0_ATESTCFG_SHTVR1_OPEN                                   0x00000000U

// Field:     [0] SHTVR0
//
// Shorts VR_ATEST_A0 to ground.
// ENUMs:
// CLOSE                    Switch is closed
// OPEN                     Switch is open
#define SYS0_ATESTCFG_SHTVR0                                        0x00000001U
#define SYS0_ATESTCFG_SHTVR0_M                                      0x00000001U
#define SYS0_ATESTCFG_SHTVR0_S                                               0U
#define SYS0_ATESTCFG_SHTVR0_CLOSE                                  0x00000001U
#define SYS0_ATESTCFG_SHTVR0_OPEN                                   0x00000000U

//*****************************************************************************
//
// Register: SYS0_O_TSENSCFG
//
//*****************************************************************************
// Field:  [11:8] SPARE
//
// Spare bits
#define SYS0_TSENSCFG_SPARE_W                                                4U
#define SYS0_TSENSCFG_SPARE_M                                       0x00000F00U
#define SYS0_TSENSCFG_SPARE_S                                                8U

// Field:   [1:0] SEL
//
// Used to enable and configure temperature sensor module. Setting the value to
// 0x3 will disable the temperature sensor.
// ENUMs:
// GND                      20uA current is injected on VR_ATEST_A0 and ground
//                          measured on VR_ATEST_A1
// VALUE                    20uA current is injected on VR_ATEST_A0 and
//                          voltage measured on VR_ATEST_A1
// DISABLE                  Temperature sensor is disabled
#define SYS0_TSENSCFG_SEL_W                                                  2U
#define SYS0_TSENSCFG_SEL_M                                         0x00000003U
#define SYS0_TSENSCFG_SEL_S                                                  0U
#define SYS0_TSENSCFG_SEL_GND                                       0x00000002U
#define SYS0_TSENSCFG_SEL_VALUE                                     0x00000001U
#define SYS0_TSENSCFG_SEL_DISABLE                                   0x00000000U

//*****************************************************************************
//
// Register: SYS0_O_LPCMPCFG
//
//*****************************************************************************
// Field:    [30] HYSPOL
//
// Spare bit for LPCOMP
#define SYS0_LPCMPCFG_HYSPOL                                        0x40000000U
#define SYS0_LPCMPCFG_HYSPOL_M                                      0x40000000U
#define SYS0_LPCMPCFG_HYSPOL_S                                              30U

// Field: [29:28] ATESTMUX
//
// Used to configure ATEST mux in comparator module and provides chosen output
// on VA_ATEST_A0.
// Note: This bit field is write-protected using global lock indicator on
// production device.
// ENUMs:
// IBIASOUT                 Selects bias current output
// COMP_VIN_NEG             Selects voltage divider output
// COMPOUT                  Selects comparator output
// OFF                      ATEST mux is off
#define SYS0_LPCMPCFG_ATESTMUX_W                                             2U
#define SYS0_LPCMPCFG_ATESTMUX_M                                    0x30000000U
#define SYS0_LPCMPCFG_ATESTMUX_S                                            28U
#define SYS0_LPCMPCFG_ATESTMUX_IBIASOUT                             0x30000000U
#define SYS0_LPCMPCFG_ATESTMUX_COMP_VIN_NEG                         0x20000000U
#define SYS0_LPCMPCFG_ATESTMUX_COMPOUT                              0x10000000U
#define SYS0_LPCMPCFG_ATESTMUX_OFF                                  0x00000000U

// Field:    [24] EVTIFG
//
// Event flag
//
// The event flag is set when the comparator output transition is qualified
// based on the edge polarity configuration in EDGCFG.
// ENUMs:
// SET
// CLR                      Clear
#define SYS0_LPCMPCFG_EVTIFG                                        0x01000000U
#define SYS0_LPCMPCFG_EVTIFG_M                                      0x01000000U
#define SYS0_LPCMPCFG_EVTIFG_S                                              24U
#define SYS0_LPCMPCFG_EVTIFG_SET                                    0x01000000U
#define SYS0_LPCMPCFG_EVTIFG_CLR                                    0x00000000U

// Field:    [21] COUTEN
//
// Enables LPCOMP output on device pin.
// ENUMs:
// EN                       Enabled
// DIS                      Disabled
#define SYS0_LPCMPCFG_COUTEN                                        0x00200000U
#define SYS0_LPCMPCFG_COUTEN_M                                      0x00200000U
#define SYS0_LPCMPCFG_COUTEN_S                                              21U
#define SYS0_LPCMPCFG_COUTEN_EN                                     0x00200000U
#define SYS0_LPCMPCFG_COUTEN_DIS                                    0x00000000U

// Field:    [20] COUT
//
// LPCOMP output status. This bit captures the value LPCOMP raw output.
// ENUMs:
// HIGH                     Output is high
// LOW                      Output is low
#define SYS0_LPCMPCFG_COUT                                          0x00100000U
#define SYS0_LPCMPCFG_COUT_M                                        0x00100000U
#define SYS0_LPCMPCFG_COUT_S                                                20U
#define SYS0_LPCMPCFG_COUT_HIGH                                     0x00100000U
#define SYS0_LPCMPCFG_COUT_LOW                                      0x00000000U

// Field:    [18] WUENSB
//
// Enables lpcmpcfg output to wake device from standby.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define SYS0_LPCMPCFG_WUENSB                                        0x00040000U
#define SYS0_LPCMPCFG_WUENSB_M                                      0x00040000U
#define SYS0_LPCMPCFG_WUENSB_S                                              18U
#define SYS0_LPCMPCFG_WUENSB_EN                                     0x00040000U
#define SYS0_LPCMPCFG_WUENSB_DIS                                    0x00000000U

// Field:    [17] EVTEN
//
// Enables event generation. Comparator module will produce event on ULL event
// fabric when EVTIFG is set.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define SYS0_LPCMPCFG_EVTEN                                         0x00020000U
#define SYS0_LPCMPCFG_EVTEN_M                                       0x00020000U
#define SYS0_LPCMPCFG_EVTEN_S                                               17U
#define SYS0_LPCMPCFG_EVTEN_EN                                      0x00020000U
#define SYS0_LPCMPCFG_EVTEN_DIS                                     0x00000000U

// Field:    [16] EDGCFG
//
// Selects positive edge or negative edge detection on comparator output to set
// the event flag
// ENUMs:
// FALL                     Fall edge detection
// RISE                     Rise edge detection
#define SYS0_LPCMPCFG_EDGCFG                                        0x00010000U
#define SYS0_LPCMPCFG_EDGCFG_M                                      0x00010000U
#define SYS0_LPCMPCFG_EDGCFG_S                                              16U
#define SYS0_LPCMPCFG_EDGCFG_FALL                                   0x00010000U
#define SYS0_LPCMPCFG_EDGCFG_RISE                                   0x00000000U

// Field: [14:12] NSEL
//
// Negative input selection. Setting values 0x5-0x7 will open all the switches.
// ENUMs:
// VDDD                     Selects VDDD
// VDDA                     Selects VDDA
// VA_PAD_A3                Selects VA_PAD_A3
// VA_PAD_A2                Selects VA_PAD_A2
// OPEN                     All switches are open
#define SYS0_LPCMPCFG_NSEL_W                                                 3U
#define SYS0_LPCMPCFG_NSEL_M                                        0x00007000U
#define SYS0_LPCMPCFG_NSEL_S                                                12U
#define SYS0_LPCMPCFG_NSEL_VDDD                                     0x00004000U
#define SYS0_LPCMPCFG_NSEL_VDDA                                     0x00003000U
#define SYS0_LPCMPCFG_NSEL_VA_PAD_A3                                0x00002000U
#define SYS0_LPCMPCFG_NSEL_VA_PAD_A2                                0x00001000U
#define SYS0_LPCMPCFG_NSEL_OPEN                                     0x00000000U

// Field:  [11:8] PSEL
//
// Positive input selection. Setting values 0x9-0xF will open all the switches.
// ENUMs:
// VDDA                     Selects VDDA
// VA_ATEST_A1              Selects VA_ATEST_A1
// VA_ATEST_A0              Selects VA_ATEST_A0
// VR_ATEST_A1              Selects VR_ATEST_A1
// VR_ATEST_A0              Selects VR_ATEST_A0
// VA_PAD_A3                Selects VA_PAD_A3
// VA_PAD_A2                Selects VA_PAD_A2
// VA_PAD_A1                Selects VA_PAD_A1
// OPEN                     All switches are open
#define SYS0_LPCMPCFG_PSEL_W                                                 4U
#define SYS0_LPCMPCFG_PSEL_M                                        0x00000F00U
#define SYS0_LPCMPCFG_PSEL_S                                                 8U
#define SYS0_LPCMPCFG_PSEL_VDDA                                     0x00000800U
#define SYS0_LPCMPCFG_PSEL_VA_ATEST_A1                              0x00000700U
#define SYS0_LPCMPCFG_PSEL_VA_ATEST_A0                              0x00000600U
#define SYS0_LPCMPCFG_PSEL_VR_ATEST_A1                              0x00000500U
#define SYS0_LPCMPCFG_PSEL_VR_ATEST_A0                              0x00000400U
#define SYS0_LPCMPCFG_PSEL_VA_PAD_A3                                0x00000300U
#define SYS0_LPCMPCFG_PSEL_VA_PAD_A2                                0x00000200U
#define SYS0_LPCMPCFG_PSEL_VA_PAD_A1                                0x00000100U
#define SYS0_LPCMPCFG_PSEL_OPEN                                     0x00000000U

// Field:   [7:5] HYSSEL
//
// Used to enable and select hysteresis level
//
// Hysteresis is disabled when HYSSEL = 0 and enabled for other values of
// HYSSEL from 1 to 7. Refer to device specific datasheet for individual
// hysteresis values.
// ENUMs:
// VAL7                     Hysteresis value: TBD
// VAL6                     Hysteresis value: TBD
// VAL5                     Hysteresis value: TBD
// VAL4                     Hysteresis value: TBD
// VAL3                     Hysteresis value: TBD
// VAL2                     Hysteresis value: TBD
// VAL1                     Hysteresis value: TBD
// VAL0                     Hysteresis is disabled
#define SYS0_LPCMPCFG_HYSSEL_W                                               3U
#define SYS0_LPCMPCFG_HYSSEL_M                                      0x000000E0U
#define SYS0_LPCMPCFG_HYSSEL_S                                               5U
#define SYS0_LPCMPCFG_HYSSEL_VAL7                                   0x000000E0U
#define SYS0_LPCMPCFG_HYSSEL_VAL6                                   0x000000C0U
#define SYS0_LPCMPCFG_HYSSEL_VAL5                                   0x000000A0U
#define SYS0_LPCMPCFG_HYSSEL_VAL4                                   0x00000080U
#define SYS0_LPCMPCFG_HYSSEL_VAL3                                   0x00000060U
#define SYS0_LPCMPCFG_HYSSEL_VAL2                                   0x00000040U
#define SYS0_LPCMPCFG_HYSSEL_VAL1                                   0x00000020U
#define SYS0_LPCMPCFG_HYSSEL_VAL0                                   0x00000000U

// Field:     [4] DIVPATH
//
// Used to select the path on which voltage divider is applied
// ENUMs:
// PSIDE                    Divider is applied on P-side
// NSIDE                    Divider is applied on N-side
#define SYS0_LPCMPCFG_DIVPATH                                       0x00000010U
#define SYS0_LPCMPCFG_DIVPATH_M                                     0x00000010U
#define SYS0_LPCMPCFG_DIVPATH_S                                              4U
#define SYS0_LPCMPCFG_DIVPATH_PSIDE                                 0x00000010U
#define SYS0_LPCMPCFG_DIVPATH_NSIDE                                 0x00000000U

// Field:   [3:1] DIV
//
// Used to configure reference divider. Setting values 0x5-0x7 will set the
// divide value to 1.
// ENUMs:
// VAL4                     Divide value is 1/4
// VAL3                     Divide value is 1/3
// VAL2                     Divide value is 1/2
// VAL1                     Divide value is 3/4
// VAL0                     Divide value is 1
#define SYS0_LPCMPCFG_DIV_W                                                  3U
#define SYS0_LPCMPCFG_DIV_M                                         0x0000000EU
#define SYS0_LPCMPCFG_DIV_S                                                  1U
#define SYS0_LPCMPCFG_DIV_VAL4                                      0x00000008U
#define SYS0_LPCMPCFG_DIV_VAL3                                      0x00000006U
#define SYS0_LPCMPCFG_DIV_VAL2                                      0x00000004U
#define SYS0_LPCMPCFG_DIV_VAL1                                      0x00000002U
#define SYS0_LPCMPCFG_DIV_VAL0                                      0x00000000U

// Field:     [0] EN
//
// Used to enable comparator module.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define SYS0_LPCMPCFG_EN                                            0x00000001U
#define SYS0_LPCMPCFG_EN_M                                          0x00000001U
#define SYS0_LPCMPCFG_EN_S                                                   0U
#define SYS0_LPCMPCFG_EN_EN                                         0x00000001U
#define SYS0_LPCMPCFG_EN_DIS                                        0x00000000U

//*****************************************************************************
//
// Register: SYS0_O_DEVICEID
//
//*****************************************************************************
// Field: [31:28] VERSION
//
// Monotonic increasing value indicating new hardware revision. A newer
// hardware revision shall never have a lower version than an older revision of
// hardware.
#define SYS0_DEVICEID_VERSION_W                                              4U
#define SYS0_DEVICEID_VERSION_M                                     0xF0000000U
#define SYS0_DEVICEID_VERSION_S                                             28U

// Field: [27:12] DEVICE
//
// Value generated by RAMP for the SOC. This value uniquely identifies the die
// from any other TI device.
#define SYS0_DEVICEID_DEVICE_W                                              16U
#define SYS0_DEVICEID_DEVICE_M                                      0x0FFFF000U
#define SYS0_DEVICEID_DEVICE_S                                              12U

// Field:  [11:1] MANFACTURER
//
// JEP 106 assigned manufacturer ID. This field identifies the device as a
// Texas Instruments device.
#define SYS0_DEVICEID_MANFACTURER_W                                         11U
#define SYS0_DEVICEID_MANFACTURER_M                                 0x00000FFEU
#define SYS0_DEVICEID_MANFACTURER_S                                          1U

// Field:     [0] ALWAYSONE
//
// Value 1 in this bit field means that a 32-bit scan register exists.
#define SYS0_DEVICEID_ALWAYSONE                                     0x00000001U
#define SYS0_DEVICEID_ALWAYSONE_M                                   0x00000001U
#define SYS0_DEVICEID_ALWAYSONE_S                                            0U

//*****************************************************************************
//
// Register: SYS0_O_PARTID
//
//*****************************************************************************
// Field:    [31] START
//
// Start bit
// ENUMs:
// SET
// CLR                      Clear
#define SYS0_PARTID_START                                           0x80000000U
#define SYS0_PARTID_START_M                                         0x80000000U
#define SYS0_PARTID_START_S                                                 31U
#define SYS0_PARTID_START_SET                                       0x80000000U
#define SYS0_PARTID_START_CLR                                       0x00000000U

// Field: [30:28] MAJORREV
//
// Monotonic increasing value indicating a new revision of the SKU significant
// enough that users of the device may have to revise PCB or software design
#define SYS0_PARTID_MAJORREV_W                                               3U
#define SYS0_PARTID_MAJORREV_M                                      0x70000000U
#define SYS0_PARTID_MAJORREV_S                                              28U

// Field: [27:24] MINORREV
//
// Monotonic increasing value indicating a new revision of the SKU that
// preserves compatibility with lesser MINORREV values
#define SYS0_PARTID_MINORREV_W                                               4U
#define SYS0_PARTID_MINORREV_M                                      0x0F000000U
#define SYS0_PARTID_MINORREV_S                                              24U

// Field: [23:16] VARIANT
//
// Bit pattern uniquely identifying a variant of a part
#define SYS0_PARTID_VARIANT_W                                                8U
#define SYS0_PARTID_VARIANT_M                                       0x00FF0000U
#define SYS0_PARTID_VARIANT_S                                               16U

// Field:  [15:0] PART
//
// Bit pattern uniquely identifying a part
#define SYS0_PARTID_PART_W                                                  16U
#define SYS0_PARTID_PART_M                                          0x0000FFFFU
#define SYS0_PARTID_PART_S                                                   0U

//*****************************************************************************
//
// Register: SYS0_O_TMUTE0
//
//*****************************************************************************
// Field:  [31:0] CDACL
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE0_CDACL_W                                                 32U
#define SYS0_TMUTE0_CDACL_M                                         0xFFFFFFFFU
#define SYS0_TMUTE0_CDACL_S                                                  0U

//*****************************************************************************
//
// Register: SYS0_O_TMUTE1
//
//*****************************************************************************
// Field:  [31:0] CDACM
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE1_CDACM_W                                                 32U
#define SYS0_TMUTE1_CDACM_M                                         0xFFFFFFFFU
#define SYS0_TMUTE1_CDACM_S                                                  0U

//*****************************************************************************
//
// Register: SYS0_O_TMUTE2
//
//*****************************************************************************
// Field: [30:26] IBTRIM
//
// LPCOMP: Bias current trim, 250nA to be terminated across I2V, 1M ohm
// setting.  Resulting target trim voltage 250mV.
#define SYS0_TMUTE2_IBTRIM_W                                                 5U
#define SYS0_TMUTE2_IBTRIM_M                                        0x7C000000U
#define SYS0_TMUTE2_IBTRIM_S                                                26U

// Field: [25:23] TRIM
//
// ADC REFBUF trim bits.
#define SYS0_TMUTE2_TRIM_W                                                   3U
#define SYS0_TMUTE2_TRIM_M                                          0x03800000U
#define SYS0_TMUTE2_TRIM_S                                                  23U

// Field: [22:16] LATCH
//
// SOC ADC: Latch trim bits. These bits are used in the analog IP.
#define SYS0_TMUTE2_LATCH_W                                                  7U
#define SYS0_TMUTE2_LATCH_M                                         0x007F0000U
#define SYS0_TMUTE2_LATCH_S                                                 16U

// Field:  [15:4] OFFSET
//
// SOCADC: Offset trim bits. These bits are used in DTC.
#define SYS0_TMUTE2_OFFSET_W                                                12U
#define SYS0_TMUTE2_OFFSET_M                                        0x0000FFF0U
#define SYS0_TMUTE2_OFFSET_S                                                 4U

// Field:   [3:2] RES
//
// SOCADC: Resistor trim bits. These bits are used in the analog IP.
#define SYS0_TMUTE2_RES_W                                                    2U
#define SYS0_TMUTE2_RES_M                                           0x0000000CU
#define SYS0_TMUTE2_RES_S                                                    2U

// Field:   [1:0] CDACU
//
// SOCADC: Upper 2 bits of CDAC trim. These bits are used in DTC.
#define SYS0_TMUTE2_CDACU_W                                                  2U
#define SYS0_TMUTE2_CDACU_M                                         0x00000003U
#define SYS0_TMUTE2_CDACU_S                                                  0U

//*****************************************************************************
//
// Register: SYS0_O_TMUTE3
//
//*****************************************************************************
// Field: [31:26] BATC1
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE3_BATC1_W                                                  6U
#define SYS0_TMUTE3_BATC1_M                                         0xFC000000U
#define SYS0_TMUTE3_BATC1_S                                                 26U

// Field: [25:19] BATC0
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE3_BATC0_W                                                  7U
#define SYS0_TMUTE3_BATC0_M                                         0x03F80000U
#define SYS0_TMUTE3_BATC0_S                                                 19U

// Field: [18:14] TEMPC2
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE3_TEMPC2_W                                                 5U
#define SYS0_TMUTE3_TEMPC2_M                                        0x0007C000U
#define SYS0_TMUTE3_TEMPC2_S                                                14U

// Field:  [13:8] TEMPC1
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE3_TEMPC1_W                                                 6U
#define SYS0_TMUTE3_TEMPC1_M                                        0x00003F00U
#define SYS0_TMUTE3_TEMPC1_S                                                 8U

// Field:   [7:0] TEMPC0
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE3_TEMPC0_W                                                 8U
#define SYS0_TMUTE3_TEMPC0_M                                        0x000000FFU
#define SYS0_TMUTE3_TEMPC0_S                                                 0U

//*****************************************************************************
//
// Register: SYS0_O_TMUTE4
//
//*****************************************************************************
// Field: [31:28] RECHCOMPREFLVL
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE4_RECHCOMPREFLVL_W                                         4U
#define SYS0_TMUTE4_RECHCOMPREFLVL_M                                0xF0000000U
#define SYS0_TMUTE4_RECHCOMPREFLVL_S                                        28U

// Field: [27:26] IOSTRCFG2
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE4_IOSTRCFG2_W                                              2U
#define SYS0_TMUTE4_IOSTRCFG2_M                                     0x0C000000U
#define SYS0_TMUTE4_IOSTRCFG2_S                                             26U

// Field: [25:22] IOSTRCFG1
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE4_IOSTRCFG1_W                                              4U
#define SYS0_TMUTE4_IOSTRCFG1_M                                     0x03C00000U
#define SYS0_TMUTE4_IOSTRCFG1_S                                             22U

// Field: [21:19] MAX
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE4_MAX_W                                                    3U
#define SYS0_TMUTE4_MAX_M                                           0x00380000U
#define SYS0_TMUTE4_MAX_S                                                   19U

// Field: [18:16] MED
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE4_MED_W                                                    3U
#define SYS0_TMUTE4_MED_M                                           0x00070000U
#define SYS0_TMUTE4_MED_S                                                   16U

// Field: [15:13] MIN
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE4_MIN_W                                                    3U
#define SYS0_TMUTE4_MIN_M                                           0x0000E000U
#define SYS0_TMUTE4_MIN_S                                                   13U

// Field: [12:11] DCDCLOAD
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE4_DCDCLOAD_W                                               2U
#define SYS0_TMUTE4_DCDCLOAD_M                                      0x00001800U
#define SYS0_TMUTE4_DCDCLOAD_S                                              11U

// Field:  [10:8] IPEAK
//
// DCDC: Set inductor peak current
// Min = 0x0
// Max = 0x7
// DCDC load support increases from 0x0 to 0x7
#define SYS0_TMUTE4_IPEAK_W                                                  3U
#define SYS0_TMUTE4_IPEAK_M                                         0x00000700U
#define SYS0_TMUTE4_IPEAK_S                                                  8U

// Field:   [7:6] DTIME
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE4_DTIME_W                                                  2U
#define SYS0_TMUTE4_DTIME_M                                         0x000000C0U
#define SYS0_TMUTE4_DTIME_S                                                  6U

// Field:   [5:3] LENSEL
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE4_LENSEL_W                                                 3U
#define SYS0_TMUTE4_LENSEL_M                                        0x00000038U
#define SYS0_TMUTE4_LENSEL_S                                                 3U

// Field:   [2:0] HENSEL
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE4_HENSEL_W                                                 3U
#define SYS0_TMUTE4_HENSEL_M                                        0x00000007U
#define SYS0_TMUTE4_HENSEL_S                                                 0U

//*****************************************************************************
//
// Register: SYS0_O_TMUTE5
//
//*****************************************************************************
// Field: [12:10] DCDCDRVDS
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE5_DCDCDRVDS_W                                              3U
#define SYS0_TMUTE5_DCDCDRVDS_M                                     0x00001C00U
#define SYS0_TMUTE5_DCDCDRVDS_S                                             10U

// Field:   [9:5] GLDOISCLR
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE5_GLDOISCLR_W                                              5U
#define SYS0_TMUTE5_GLDOISCLR_M                                     0x000003E0U
#define SYS0_TMUTE5_GLDOISCLR_S                                              5U

// Field:   [4:0] GLDOISSET
//
// Internal. Only to be used through TI provided API.
#define SYS0_TMUTE5_GLDOISSET_W                                              5U
#define SYS0_TMUTE5_GLDOISSET_M                                     0x0000001FU
#define SYS0_TMUTE5_GLDOISSET_S                                              0U


#endif // __SYS0__
