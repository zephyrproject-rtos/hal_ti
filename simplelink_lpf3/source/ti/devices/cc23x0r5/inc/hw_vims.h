/******************************************************************************
*  Filename:       hw_vims_h
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

#ifndef __HW_VIMS_H__
#define __HW_VIMS_H__

//*****************************************************************************
//
// This section defines the register offsets of
// VIMS component
//
//*****************************************************************************
// Module Description
#define VIMS_O_DESC                                                 0x00000000U

// Extended Module Description
#define VIMS_O_DESCEX                                               0x00000004U

// Internal. Only to be used through TI provided API.
#define VIMS_O_FLWS1T                                               0x00000008U

// Internal. Only to be used through TI provided API.
#define VIMS_O_FLWS2T                                               0x0000000CU

// Internal. Only to be used through TI provided API.
#define VIMS_O_PTRMC0                                               0x00000018U

// Internal. Only to be used through TI provided API.
#define VIMS_O_B0TRMC1                                              0x0000001CU

// Internal. Only to be used through TI provided API.
#define VIMS_O_B0TRMC0                                              0x00000020U

// Internal. Only to be used through TI provided API.
#define VIMS_O_FLBLCK                                               0x00000100U

// Internal. Only to be used through TI provided API.
#define VIMS_O_CFG                                                  0x000003FCU

// Flash main region write/erase protection configuration 1
#define VIMS_O_WEPRA                                                0x00000410U

// Flash main region write/erase protection configuration 2
#define VIMS_O_WEPRB                                                0x00000414U

// Flash write/erase protection configuration for other regions
#define VIMS_O_WEPRAUX                                              0x0000041CU

// Flash status
#define VIMS_O_FLBSTAT                                              0x00000420U

// Cache control
#define VIMS_O_CCHCTRL                                              0x00000424U

//*****************************************************************************
//
// Register: VIMS_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module identifier used to uniquely identify this IP.
#define VIMS_DESC_MODID_W                                                   16U
#define VIMS_DESC_MODID_M                                           0xFFFF0000U
#define VIMS_DESC_MODID_S                                                   16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set of from
// aggregated IRQ registers till DTB.
//
// 0: Standard IP MMRs do not exist
//
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
#define VIMS_DESC_STDIPOFF_W                                                 4U
#define VIMS_DESC_STDIPOFF_M                                        0x0000F000U
#define VIMS_DESC_STDIPOFF_S                                                12U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number. If multiple instances of IP exist in the device, this
// field can identify the instance number (0-15).
#define VIMS_DESC_INSTIDX_W                                                  4U
#define VIMS_DESC_INSTIDX_M                                         0x00000F00U
#define VIMS_DESC_INSTIDX_S                                                  8U

// Field:   [7:4] MAJREV
//
// Major revision of IP (0-15).
#define VIMS_DESC_MAJREV_W                                                   4U
#define VIMS_DESC_MAJREV_M                                          0x000000F0U
#define VIMS_DESC_MAJREV_S                                                   4U

// Field:   [3:0] MINREV
//
// Minor revision of IP (0-15).
#define VIMS_DESC_MINREV_W                                                   4U
#define VIMS_DESC_MINREV_M                                          0x0000000FU
#define VIMS_DESC_MINREV_S                                                   0U

//*****************************************************************************
//
// Register: VIMS_O_DESCEX
//
//*****************************************************************************
// Field:    [27] NBANK
//
// Provides the FLASH Bank count
#define VIMS_DESCEX_NBANK                                           0x08000000U
#define VIMS_DESCEX_NBANK_M                                         0x08000000U
#define VIMS_DESCEX_NBANK_S                                                 27U

// Field: [26:15] FLSZ
//
// This provides the total FLASH size in Kilo Bytes. The total FLASH size is
// (FLSZ + 1)KB
#define VIMS_DESCEX_FLSZ_W                                                  12U
#define VIMS_DESCEX_FLSZ_M                                          0x07FF8000U
#define VIMS_DESCEX_FLSZ_S                                                  15U

// Field:  [14:0] ROMSZ
//
// Provides the size of ROM in Bytes.
#define VIMS_DESCEX_ROMSZ_W                                                 15U
#define VIMS_DESCEX_ROMSZ_M                                         0x00007FFFU
#define VIMS_DESCEX_ROMSZ_S                                                  0U

//*****************************************************************************
//
// Register: VIMS_O_FLWS1T
//
//*****************************************************************************
// Field:   [2:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// WS7                      Internal. Only to be used through TI provided API.
// WS6                      Internal. Only to be used through TI provided API.
// WS5                      Internal. Only to be used through TI provided API.
// WS4                      Internal. Only to be used through TI provided API.
// WS3                      Internal. Only to be used through TI provided API.
// WS2                      Internal. Only to be used through TI provided API.
// WS1                      Internal. Only to be used through TI provided API.
// WS0                      Internal. Only to be used through TI provided API.
#define VIMS_FLWS1T_VAL_W                                                    3U
#define VIMS_FLWS1T_VAL_M                                           0x00000007U
#define VIMS_FLWS1T_VAL_S                                                    0U
#define VIMS_FLWS1T_VAL_WS7                                         0x00000007U
#define VIMS_FLWS1T_VAL_WS6                                         0x00000006U
#define VIMS_FLWS1T_VAL_WS5                                         0x00000005U
#define VIMS_FLWS1T_VAL_WS4                                         0x00000004U
#define VIMS_FLWS1T_VAL_WS3                                         0x00000003U
#define VIMS_FLWS1T_VAL_WS2                                         0x00000002U
#define VIMS_FLWS1T_VAL_WS1                                         0x00000001U
#define VIMS_FLWS1T_VAL_WS0                                         0x00000000U

//*****************************************************************************
//
// Register: VIMS_O_FLWS2T
//
//*****************************************************************************
// Field:   [2:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// WS7                      Internal. Only to be used through TI provided API.
// WS6                      Internal. Only to be used through TI provided API.
// WS5                      Internal. Only to be used through TI provided API.
// WS4                      Internal. Only to be used through TI provided API.
// WS3                      Internal. Only to be used through TI provided API.
// WS2                      Internal. Only to be used through TI provided API.
// WS1                      Internal. Only to be used through TI provided API.
// WS0                      Internal. Only to be used through TI provided API.
#define VIMS_FLWS2T_VAL_W                                                    3U
#define VIMS_FLWS2T_VAL_M                                           0x00000007U
#define VIMS_FLWS2T_VAL_S                                                    0U
#define VIMS_FLWS2T_VAL_WS7                                         0x00000007U
#define VIMS_FLWS2T_VAL_WS6                                         0x00000006U
#define VIMS_FLWS2T_VAL_WS5                                         0x00000005U
#define VIMS_FLWS2T_VAL_WS4                                         0x00000004U
#define VIMS_FLWS2T_VAL_WS3                                         0x00000003U
#define VIMS_FLWS2T_VAL_WS2                                         0x00000002U
#define VIMS_FLWS2T_VAL_WS1                                         0x00000001U
#define VIMS_FLWS2T_VAL_WS0                                         0x00000000U

//*****************************************************************************
//
// Register: VIMS_O_PTRMC0
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
#define VIMS_PTRMC0_VAL_W                                                   32U
#define VIMS_PTRMC0_VAL_M                                           0xFFFFFFFFU
#define VIMS_PTRMC0_VAL_S                                                    0U

//*****************************************************************************
//
// Register: VIMS_O_B0TRMC1
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
#define VIMS_B0TRMC1_VAL_W                                                  32U
#define VIMS_B0TRMC1_VAL_M                                          0xFFFFFFFFU
#define VIMS_B0TRMC1_VAL_S                                                   0U

//*****************************************************************************
//
// Register: VIMS_O_B0TRMC0
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
#define VIMS_B0TRMC0_VAL_W                                                  32U
#define VIMS_B0TRMC0_VAL_M                                          0xFFFFFFFFU
#define VIMS_B0TRMC0_VAL_S                                                   0U

//*****************************************************************************
//
// Register: VIMS_O_FLBLCK
//
//*****************************************************************************
// Field:     [0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BLOCK                    Internal. Only to be used through TI provided API.
// ALLOW                    Internal. Only to be used through TI provided API.
#define VIMS_FLBLCK_VAL                                             0x00000001U
#define VIMS_FLBLCK_VAL_M                                           0x00000001U
#define VIMS_FLBLCK_VAL_S                                                    0U
#define VIMS_FLBLCK_VAL_BLOCK                                       0x00000001U
#define VIMS_FLBLCK_VAL_ALLOW                                       0x00000000U

//*****************************************************************************
//
// Register: VIMS_O_CFG
//
//*****************************************************************************
// Field:     [1] TRMVLID
//
// Internal. Only to be used through TI provided API.
#define VIMS_CFG_TRMVLID                                            0x00000002U
#define VIMS_CFG_TRMVLID_M                                          0x00000002U
#define VIMS_CFG_TRMVLID_S                                                   1U

// Field:     [0] WEPRTRM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLOW                    Internal. Only to be used through TI provided API.
// RESTRICT                 Internal. Only to be used through TI provided API.
#define VIMS_CFG_WEPRTRM                                            0x00000001U
#define VIMS_CFG_WEPRTRM_M                                          0x00000001U
#define VIMS_CFG_WEPRTRM_S                                                   0U
#define VIMS_CFG_WEPRTRM_ALLOW                                      0x00000001U
#define VIMS_CFG_WEPRTRM_RESTRICT                                   0x00000000U

//*****************************************************************************
//
// Register: VIMS_O_WEPRA
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Flash write/erase protection configuration value.
#define VIMS_WEPRA_VAL_W                                                    32U
#define VIMS_WEPRA_VAL_M                                            0xFFFFFFFFU
#define VIMS_WEPRA_VAL_S                                                     0U

//*****************************************************************************
//
// Register: VIMS_O_WEPRB
//
//*****************************************************************************
// Field:  [27:0] VAL
//
// Flash write/erase protection configuration value.
#define VIMS_WEPRB_VAL_W                                                    28U
#define VIMS_WEPRB_VAL_M                                            0x0FFFFFFFU
#define VIMS_WEPRB_VAL_S                                                     0U

//*****************************************************************************
//
// Register: VIMS_O_WEPRAUX
//
//*****************************************************************************
// Field:     [2] WEPREGR
//
// Flash engr region write/erase protection configuration value.
#define VIMS_WEPRAUX_WEPREGR                                        0x00000004U
#define VIMS_WEPRAUX_WEPREGR_M                                      0x00000004U
#define VIMS_WEPRAUX_WEPREGR_S                                               2U

// Field:     [1] WEPRTRM
//
// Flash trim region write/erase protection configuration value.
#define VIMS_WEPRAUX_WEPRTRM                                        0x00000002U
#define VIMS_WEPRAUX_WEPRTRM_M                                      0x00000002U
#define VIMS_WEPRAUX_WEPRTRM_S                                               1U

// Field:     [0] WEPRNMN
//
// Flash non main region write/erase protection configuration value.
#define VIMS_WEPRAUX_WEPRNMN                                        0x00000001U
#define VIMS_WEPRAUX_WEPRNMN_M                                      0x00000001U
#define VIMS_WEPRAUX_WEPRNMN_S                                               0U

//*****************************************************************************
//
// Register: VIMS_O_FLBSTAT
//
//*****************************************************************************
// Field:     [3] PARERR
//
// This bit indicates parity error on write/erase and read protection MMRs.
// This bit is sticky when set to 1 by hardware.
// ENUMs:
// ERROR                    Error
// NOERROR                  No Error
#define VIMS_FLBSTAT_PARERR                                         0x00000008U
#define VIMS_FLBSTAT_PARERR_M                                       0x00000008U
#define VIMS_FLBSTAT_PARERR_S                                                3U
#define VIMS_FLBSTAT_PARERR_ERROR                                   0x00000008U
#define VIMS_FLBSTAT_PARERR_NOERROR                                 0x00000000U

// Field:     [2] B0BSY
//
// This bit indicates if flash is busy.
// ENUMs:
// BUSY                     Busy
// IDLE                     Idle
#define VIMS_FLBSTAT_B0BSY                                          0x00000004U
#define VIMS_FLBSTAT_B0BSY_M                                        0x00000004U
#define VIMS_FLBSTAT_B0BSY_S                                                 2U
#define VIMS_FLBSTAT_B0BSY_BUSY                                     0x00000004U
#define VIMS_FLBSTAT_B0BSY_IDLE                                     0x00000000U

// Field:     [1] B2TRDY
//
// This bit indicates if flash is ready in 2T mode.
// ENUMs:
// READY                    Ready
// NOTREADY                 Not Ready
#define VIMS_FLBSTAT_B2TRDY                                         0x00000002U
#define VIMS_FLBSTAT_B2TRDY_M                                       0x00000002U
#define VIMS_FLBSTAT_B2TRDY_S                                                1U
#define VIMS_FLBSTAT_B2TRDY_READY                                   0x00000002U
#define VIMS_FLBSTAT_B2TRDY_NOTREADY                                0x00000000U

// Field:     [0] B1TRDY
//
// This bit indicates if flash is ready in 1T mode.
// ENUMs:
// READY                    Ready
// NOTREADY                 Not Ready
#define VIMS_FLBSTAT_B1TRDY                                         0x00000001U
#define VIMS_FLBSTAT_B1TRDY_M                                       0x00000001U
#define VIMS_FLBSTAT_B1TRDY_S                                                0U
#define VIMS_FLBSTAT_B1TRDY_READY                                   0x00000001U
#define VIMS_FLBSTAT_B1TRDY_NOTREADY                                0x00000000U

//*****************************************************************************
//
// Register: VIMS_O_CCHCTRL
//
//*****************************************************************************
// Field:     [2] CCHMPEN
//
// This bit is used to enable the micropredictor unit.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define VIMS_CCHCTRL_CCHMPEN                                        0x00000004U
#define VIMS_CCHCTRL_CCHMPEN_M                                      0x00000004U
#define VIMS_CCHCTRL_CCHMPEN_S                                               2U
#define VIMS_CCHCTRL_CCHMPEN_EN                                     0x00000004U
#define VIMS_CCHCTRL_CCHMPEN_DIS                                    0x00000000U

// Field:     [1] CCHPFEN
//
// This bit is used to enable the prefetch unit.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define VIMS_CCHCTRL_CCHPFEN                                        0x00000002U
#define VIMS_CCHCTRL_CCHPFEN_M                                      0x00000002U
#define VIMS_CCHCTRL_CCHPFEN_S                                               1U
#define VIMS_CCHCTRL_CCHPFEN_EN                                     0x00000002U
#define VIMS_CCHCTRL_CCHPFEN_DIS                                    0x00000000U

// Field:     [0] CCHEN
//
// This bit is used to enable the cache.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define VIMS_CCHCTRL_CCHEN                                          0x00000001U
#define VIMS_CCHCTRL_CCHEN_M                                        0x00000001U
#define VIMS_CCHCTRL_CCHEN_S                                                 0U
#define VIMS_CCHCTRL_CCHEN_EN                                       0x00000001U
#define VIMS_CCHCTRL_CCHEN_DIS                                      0x00000000U


//*****************************************************************************
//
// This section defines the register offsets of
// VIMS component
//
//*****************************************************************************
// Status
#define VIMS_O_STAT                                                 0x00000000

// Control
#define VIMS_O_CTL                                                  0x00000004

//*****************************************************************************
//
// Register: VIMS_O_STAT
//
//*****************************************************************************
// Field:     [5] IDCODE_LB_DIS
//
// Icode/Dcode flash line buffer status
//
// 0: Enabled or in transition to disabled
// 1: Disabled and flushed
#define VIMS_STAT_IDCODE_LB_DIS                                     0x00000020
#define VIMS_STAT_IDCODE_LB_DIS_BITN                                         5
#define VIMS_STAT_IDCODE_LB_DIS_M                                   0x00000020
#define VIMS_STAT_IDCODE_LB_DIS_S                                            5

// Field:     [4] SYSBUS_LB_DIS
//
// Sysbus flash line buffer control
//
// 0: Enabled or in transition to disabled
// 1: Disabled and flushed
#define VIMS_STAT_SYSBUS_LB_DIS                                     0x00000010
#define VIMS_STAT_SYSBUS_LB_DIS_BITN                                         4
#define VIMS_STAT_SYSBUS_LB_DIS_M                                   0x00000010
#define VIMS_STAT_SYSBUS_LB_DIS_S                                            4

// Field:     [3] MODE_CHANGING
//
// VIMS mode change status
//
// 0: VIMS is in the mode defined by MODE
// 1: VIMS is in the process of changing to the mode given in CTL.MODE
#define VIMS_STAT_MODE_CHANGING                                     0x00000008
#define VIMS_STAT_MODE_CHANGING_BITN                                         3
#define VIMS_STAT_MODE_CHANGING_M                                   0x00000008
#define VIMS_STAT_MODE_CHANGING_S                                            3

// Field:     [2] INV
//
// This bit is set when invalidation of the cache memory is active / ongoing
#define VIMS_STAT_INV                                               0x00000004
#define VIMS_STAT_INV_BITN                                                   2
#define VIMS_STAT_INV_M                                             0x00000004
#define VIMS_STAT_INV_S                                                      2

// Field:   [1:0] MODE
//
// Current VIMS mode
// ENUMs:
// OFF                      VIMS Off mode
// CACHE                    VIMS Cache mode
// GPRAM                    VIMS GPRAM mode
#define VIMS_STAT_MODE_W                                                     2
#define VIMS_STAT_MODE_M                                            0x00000003
#define VIMS_STAT_MODE_S                                                     0
#define VIMS_STAT_MODE_OFF                                          0x00000003
#define VIMS_STAT_MODE_CACHE                                        0x00000001
#define VIMS_STAT_MODE_GPRAM                                        0x00000000

//*****************************************************************************
//
// Register: VIMS_O_CTL
//
//*****************************************************************************
// Field:    [31] STATS_CLR
//
// Set this bit to clear statistic counters.
#define VIMS_CTL_STATS_CLR                                          0x80000000
#define VIMS_CTL_STATS_CLR_BITN                                             31
#define VIMS_CTL_STATS_CLR_M                                        0x80000000
#define VIMS_CTL_STATS_CLR_S                                                31

// Field:    [30] STATS_EN
//
// Set this bit to enable statistic counters.
#define VIMS_CTL_STATS_EN                                           0x40000000
#define VIMS_CTL_STATS_EN_BITN                                              30
#define VIMS_CTL_STATS_EN_M                                         0x40000000
#define VIMS_CTL_STATS_EN_S                                                 30

// Field:    [29] DYN_CG_EN
//
// 0: The in-built clock gate functionality is bypassed.
// 1: The in-built clock gate functionality is enabled, automatically gating
// the clock when not needed.
#define VIMS_CTL_DYN_CG_EN                                          0x20000000
#define VIMS_CTL_DYN_CG_EN_BITN                                             29
#define VIMS_CTL_DYN_CG_EN_M                                        0x20000000
#define VIMS_CTL_DYN_CG_EN_S                                                29

// Field:     [5] IDCODE_LB_DIS
//
// Icode/Dcode flash line buffer control
//
// 0: Enable
// 1: Disable
#define VIMS_CTL_IDCODE_LB_DIS                                      0x00000020
#define VIMS_CTL_IDCODE_LB_DIS_BITN                                          5
#define VIMS_CTL_IDCODE_LB_DIS_M                                    0x00000020
#define VIMS_CTL_IDCODE_LB_DIS_S                                             5

// Field:     [4] SYSBUS_LB_DIS
//
// Sysbus flash line buffer control
//
// 0: Enable
// 1: Disable
#define VIMS_CTL_SYSBUS_LB_DIS                                      0x00000010
#define VIMS_CTL_SYSBUS_LB_DIS_BITN                                          4
#define VIMS_CTL_SYSBUS_LB_DIS_M                                    0x00000010
#define VIMS_CTL_SYSBUS_LB_DIS_S                                             4

// Field:     [3] ARB_CFG
//
// Icode/Dcode and sysbus arbitation scheme
//
// 0: Static arbitration  (icode/docde > sysbus)
// 1: Round-robin arbitration
#define VIMS_CTL_ARB_CFG                                            0x00000008
#define VIMS_CTL_ARB_CFG_BITN                                                3
#define VIMS_CTL_ARB_CFG_M                                          0x00000008
#define VIMS_CTL_ARB_CFG_S                                                   3

// Field:     [2] PREF_EN
//
// Tag prefetch control
//
// 0: Disabled
// 1: Enabled
#define VIMS_CTL_PREF_EN                                            0x00000004
#define VIMS_CTL_PREF_EN_BITN                                                2
#define VIMS_CTL_PREF_EN_M                                          0x00000004
#define VIMS_CTL_PREF_EN_S                                                   2

// Field:   [1:0] MODE
//
// VIMS mode request.
// Write accesses to this field will be blocked while STAT.MODE_CHANGING is set
// to 1.
// ENUMs:
// OFF                      VIMS Off mode
// CACHE                    VIMS Cache mode
// GPRAM                    VIMS GPRAM mode
#define VIMS_CTL_MODE_W                                                      2
#define VIMS_CTL_MODE_M                                             0x00000003
#define VIMS_CTL_MODE_S                                                      0
#define VIMS_CTL_MODE_OFF                                           0x00000003
#define VIMS_CTL_MODE_CACHE                                         0x00000001
#define VIMS_CTL_MODE_GPRAM                                         0x00000000



#endif // __VIMS__
