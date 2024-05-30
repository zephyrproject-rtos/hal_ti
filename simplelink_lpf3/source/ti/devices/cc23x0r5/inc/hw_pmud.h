/******************************************************************************
*  Filename:       hw_pmud_h
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

#ifndef __HW_PMUD_H__
#define __HW_PMUD_H__

//*****************************************************************************
//
// This section defines the register offsets of
// PMUD component
//
//*****************************************************************************
// Control
#define PMUD_O_CTL                                                  0x00000000U

// Internal. Only to be used through TI provided API.
#define PMUD_O_MEASCFG                                              0x00000004U

// Last Measured Battery Voltage
#define PMUD_O_BAT                                                  0x00000028U

// Battery Update
#define PMUD_O_BATUPD                                               0x0000002CU

// Last measured Temperature in Degree Celsius
#define PMUD_O_TEMP                                                 0x00000030U

// Temperature Update
#define PMUD_O_TEMPUPD                                              0x00000034U

// Event Mask
#define PMUD_O_EVENTMASK                                            0x00000048U

// Event
#define PMUD_O_EVENT                                                0x0000004CU

// Battery Upper Limit
#define PMUD_O_BATTUL                                               0x00000050U

// Battery Lower Limit
#define PMUD_O_BATTLL                                               0x00000054U

// Temperature Upper Limit
#define PMUD_O_TEMPUL                                               0x00000058U

// Temperature Lower Limit
#define PMUD_O_TEMPLL                                               0x0000005CU

// Internal. Only to be used through TI provided API.
#define PMUD_O_PREFSYS                                              0x00000080U

// Internal. Only to be used through TI provided API.
#define PMUD_O_PREG0                                                0x00000090U

// Internal. Only to be used through TI provided API.
#define PMUD_O_PREG1                                                0x00000094U

// Internal. Only to be used through TI provided API.
#define PMUD_O_PREG2                                                0x00000098U

// DCDC configuration
#define PMUD_O_DCDCCFG                                              0x0000009CU

// DCDC status
#define PMUD_O_DCDCSTAT                                             0x000000A0U

//*****************************************************************************
//
// Register: PMUD_O_CTL
//
//*****************************************************************************
// Field:     [2] HYST_EN
//
// Enables hysteresis on both battery and temperature measurements.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define PMUD_CTL_HYST_EN                                            0x00000004U
#define PMUD_CTL_HYST_EN_M                                          0x00000004U
#define PMUD_CTL_HYST_EN_S                                                   2U
#define PMUD_CTL_HYST_EN_EN                                         0x00000004U
#define PMUD_CTL_HYST_EN_DIS                                        0x00000000U

// Field:     [1] CALC_EN
//
// Configuration of the calculation block that converts the digital
// battery/temperature level to a Volt/Celsius value.
// ENUMs:
// EN                       Calculation enabled
// DIS                      Calculation disabled
#define PMUD_CTL_CALC_EN                                            0x00000002U
#define PMUD_CTL_CALC_EN_M                                          0x00000002U
#define PMUD_CTL_CALC_EN_S                                                   1U
#define PMUD_CTL_CALC_EN_EN                                         0x00000002U
#define PMUD_CTL_CALC_EN_DIS                                        0x00000000U

// Field:     [0] MEAS_EN
//
// Configuration of the measurement block that interfaces with the analog
// domain.
// ENUMs:
// EN                       Measurements enabled (battery voltage and
//                          temperature)
// DIS                      Measurements disabled
#define PMUD_CTL_MEAS_EN                                            0x00000001U
#define PMUD_CTL_MEAS_EN_M                                          0x00000001U
#define PMUD_CTL_MEAS_EN_S                                                   0U
#define PMUD_CTL_MEAS_EN_EN                                         0x00000001U
#define PMUD_CTL_MEAS_EN_DIS                                        0x00000000U

//*****************************************************************************
//
// Register: PMUD_O_MEASCFG
//
//*****************************************************************************
// Field:   [1:0] PER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// _32CYC                   Internal. Only to be used through TI provided API.
// _16CYC                   Internal. Only to be used through TI provided API.
// _8CYC                    Internal. Only to be used through TI provided API.
// CONT                     Internal. Only to be used through TI provided API.
#define PMUD_MEASCFG_PER_W                                                   2U
#define PMUD_MEASCFG_PER_M                                          0x00000003U
#define PMUD_MEASCFG_PER_S                                                   0U
#define PMUD_MEASCFG_PER__32CYC                                     0x00000003U
#define PMUD_MEASCFG_PER__16CYC                                     0x00000002U
#define PMUD_MEASCFG_PER__8CYC                                      0x00000001U
#define PMUD_MEASCFG_PER_CONT                                       0x00000000U

//*****************************************************************************
//
// Register: PMUD_O_BAT
//
//*****************************************************************************
// Field:  [10:8] INT
//
// Integer part:
//
// 0x0: Battery voltage = 0V + fractional part
// ...
// 0x3: Battery voltage = 3V + fractional part
// 0x4: Battery voltage = 4V + fractional part
#define PMUD_BAT_INT_W                                                       3U
#define PMUD_BAT_INT_M                                              0x00000700U
#define PMUD_BAT_INT_S                                                       8U

// Field:   [7:0] FRAC
//
// Fractional part, standard binary fractional encoding.
//
// 0x00: .0V
// ...
// 0x20: 1/8 = .125V
// 0x40: 1/4 = .25V
// 0x80: 1/2 = .5V
// ...
// 0xA0: 1/2 + 1/8 = .625V
// ...
// 0xFF: 1/2 + 1/4 + 1/8 + ... + 1/256 = 0.99V
#define PMUD_BAT_FRAC_W                                                      8U
#define PMUD_BAT_FRAC_M                                             0x000000FFU
#define PMUD_BAT_FRAC_S                                                      0U

//*****************************************************************************
//
// Register: PMUD_O_BATUPD
//
//*****************************************************************************
// Field:     [0] STA
//
// Battery update status. Write 1 to clear the status.
// ENUMs:
// UPD                      New battery voltage present
// NOUPD                    No update since last clear
#define PMUD_BATUPD_STA                                             0x00000001U
#define PMUD_BATUPD_STA_M                                           0x00000001U
#define PMUD_BATUPD_STA_S                                                    0U
#define PMUD_BATUPD_STA_UPD                                         0x00000001U
#define PMUD_BATUPD_STA_NOUPD                                       0x00000000U

//*****************************************************************************
//
// Register: PMUD_O_TEMP
//
//*****************************************************************************
// Field:  [16:8] INT
//
// Integer part of temperature value  (signed)
// Total value = INT + FRAC
// 2's complement encoding
//
// 0x100: Min value (-256°C)
// 0x1D8: -40°C
// 0x1FF: -1°C
// 0x00: 0°C
// 0x1B: 27°C
// 0x55: 85°C
// 0xFF: Max value (255°C)
#define PMUD_TEMP_INT_W                                                      9U
#define PMUD_TEMP_INT_M                                             0x0001FF00U
#define PMUD_TEMP_INT_S                                                      8U

// Field:   [7:6] FRAC
//
// Fractional part of temperature value.
// Total value = INT + FRAC
// The encoding is an extension of the 2's complement encoding.
//
// 00: 0.0°C
// 01: 0.25°C
// 10: 0.5°C
// 11: 0.75°C
//
// For example:
// 000000001,00 = ( 1+0,00) =  1,00
// 000000000,11 = ( 0+0,75) =  0,75
// 000000000,10 = ( 0+0,50) =  0,50
// 000000000,01 = ( 0+0,25) =  0,25
// 000000000,00 = ( 0+0,00) =  0,00
// 111111111,11 = (-1+0,75) = -0,25
// 111111111,10 = (-1+0,50) = -0,50
// 111111111,01 = (-1+0,25) = -0,75
// 111111111,00 = (-1+0,00) = -1,00
// 111111110,11 = (-2+0,75) = -1,25
#define PMUD_TEMP_FRAC_W                                                     2U
#define PMUD_TEMP_FRAC_M                                            0x000000C0U
#define PMUD_TEMP_FRAC_S                                                     6U

//*****************************************************************************
//
// Register: PMUD_O_TEMPUPD
//
//*****************************************************************************
// Field:     [0] STA
//
// Temperature update status. Write 1 to clear the status.
// ENUMs:
// UPD                      New temperature value present
// NOUPD                    No temperature update since last clear
#define PMUD_TEMPUPD_STA                                            0x00000001U
#define PMUD_TEMPUPD_STA_M                                          0x00000001U
#define PMUD_TEMPUPD_STA_S                                                   0U
#define PMUD_TEMPUPD_STA_UPD                                        0x00000001U
#define PMUD_TEMPUPD_STA_NOUPD                                      0x00000000U

//*****************************************************************************
//
// Register: PMUD_O_EVENTMASK
//
//*****************************************************************************
// Field:     [5] TEMP_UPDATE_MASK
//
// 1: EVENT.TEMP_UPDATE contributes to combined event from BATMON
// 0: EVENT.TEMP_UPDATE does not contribute to combined event from BATMON
#define PMUD_EVENTMASK_TEMP_UPDATE_MASK                             0x00000020U
#define PMUD_EVENTMASK_TEMP_UPDATE_MASK_M                           0x00000020U
#define PMUD_EVENTMASK_TEMP_UPDATE_MASK_S                                    5U

// Field:     [4] BATT_UPDATE_MASK
//
// 1: EVENT.BATT_UPDATE contributes to combined event from BATMON
// 0: EVENT.BATT_UPDATE does not contribute to combined event from BATMON
#define PMUD_EVENTMASK_BATT_UPDATE_MASK                             0x00000010U
#define PMUD_EVENTMASK_BATT_UPDATE_MASK_M                           0x00000010U
#define PMUD_EVENTMASK_BATT_UPDATE_MASK_S                                    4U

// Field:     [3] TEMP_BELOW_LL_MASK
//
// 1: EVENT.TEMP_BELOW_LL contributes to combined event from BATMON
// 0: EVENT.TEMP_BELOW_LL does not contribute to combined event from BATMON
#define PMUD_EVENTMASK_TEMP_BELOW_LL_MASK                           0x00000008U
#define PMUD_EVENTMASK_TEMP_BELOW_LL_MASK_M                         0x00000008U
#define PMUD_EVENTMASK_TEMP_BELOW_LL_MASK_S                                  3U

// Field:     [2] TEMP_OVER_UL_MASK
//
// 1: EVENT.TEMP_OVER_UL contributes to combined event from BATMON
// 0: EVENT.TEMP_OVER_UL does not contribute to combined event from BATMON
#define PMUD_EVENTMASK_TEMP_OVER_UL_MASK                            0x00000004U
#define PMUD_EVENTMASK_TEMP_OVER_UL_MASK_M                          0x00000004U
#define PMUD_EVENTMASK_TEMP_OVER_UL_MASK_S                                   2U

// Field:     [1] BATT_BELOW_LL_MASK
//
// 1: EVENT.BATT_BELOW_LL contributes to combined event from BATMON
// 0: EVENT.BATT_BELOW_LL does not contribute to combined event from BATMON
#define PMUD_EVENTMASK_BATT_BELOW_LL_MASK                           0x00000002U
#define PMUD_EVENTMASK_BATT_BELOW_LL_MASK_M                         0x00000002U
#define PMUD_EVENTMASK_BATT_BELOW_LL_MASK_S                                  1U

// Field:     [0] BATT_OVER_UL_MASK
//
// 1: EVENT.BATT_OVER_UL contributes to combined event from BATMON
// 0: EVENT.BATT_OVER_UL does not contribute to combined event from BATMON
#define PMUD_EVENTMASK_BATT_OVER_UL_MASK                            0x00000001U
#define PMUD_EVENTMASK_BATT_OVER_UL_MASK_M                          0x00000001U
#define PMUD_EVENTMASK_BATT_OVER_UL_MASK_S                                   0U

//*****************************************************************************
//
// Register: PMUD_O_EVENT
//
//*****************************************************************************
// Field:     [5] TEMP_UPDATE
//
// Alias to TEMPUPD.STA
#define PMUD_EVENT_TEMP_UPDATE                                      0x00000020U
#define PMUD_EVENT_TEMP_UPDATE_M                                    0x00000020U
#define PMUD_EVENT_TEMP_UPDATE_S                                             5U

// Field:     [4] BATT_UPDATE
//
// Alias to BATUPD.STA
#define PMUD_EVENT_BATT_UPDATE                                      0x00000010U
#define PMUD_EVENT_BATT_UPDATE_M                                    0x00000010U
#define PMUD_EVENT_BATT_UPDATE_S                                             4U

// Field:     [3] TEMP_BELOW_LL
//
// Read:
// 1: Temperature level is below the lower limit set by TEMPLL.
// 0: Temperature level is not below the lower limit set by TEMPLL.
// Write:
// 1: Clears the flag
// 0: No change in the flag
#define PMUD_EVENT_TEMP_BELOW_LL                                    0x00000008U
#define PMUD_EVENT_TEMP_BELOW_LL_M                                  0x00000008U
#define PMUD_EVENT_TEMP_BELOW_LL_S                                           3U

// Field:     [2] TEMP_OVER_UL
//
// Read:
// 1: Temperature level is above the upper limit set by TEMPUL.
// 0: Temperature level is not above the upper limit set by TEMPUL.
// Write:
// 1: Clears the flag
// 0: No change in the flag
#define PMUD_EVENT_TEMP_OVER_UL                                     0x00000004U
#define PMUD_EVENT_TEMP_OVER_UL_M                                   0x00000004U
#define PMUD_EVENT_TEMP_OVER_UL_S                                            2U

// Field:     [1] BATT_BELOW_LL
//
// Read:
// 1: Battery level is below the lower limit set by BATTLL.
// 0: Battery level is not below the lower limit set by BATTLL.
// Write:
// 1: Clears the flag
// 0: No change in the flag
#define PMUD_EVENT_BATT_BELOW_LL                                    0x00000002U
#define PMUD_EVENT_BATT_BELOW_LL_M                                  0x00000002U
#define PMUD_EVENT_BATT_BELOW_LL_S                                           1U

// Field:     [0] BATT_OVER_UL
//
// Read:
// 1: Battery level is above the upper limit set by BATTUL.
// 0: Battery level is not above the upper limit set by BATTUL.
// Write:
// 1: Clears the flag
// 0: No change in the flag
#define PMUD_EVENT_BATT_OVER_UL                                     0x00000001U
#define PMUD_EVENT_BATT_OVER_UL_M                                   0x00000001U
#define PMUD_EVENT_BATT_OVER_UL_S                                            0U

//*****************************************************************************
//
// Register: PMUD_O_BATTUL
//
//*****************************************************************************
// Field:  [10:8] INT
//
// Integer part:
// Total battery voltage = INT + FRAC (integer and fractional part)
//
// 0x0: Battery voltage = 0V + fractional part
// ...
// 0x3: Battery voltage =  3V + fractional part
// 0x4: Battery voltage =  4V + fractional part
#define PMUD_BATTUL_INT_W                                                    3U
#define PMUD_BATTUL_INT_M                                           0x00000700U
#define PMUD_BATTUL_INT_S                                                    8U

// Field:   [7:0] FRAC
//
// Fractional part, standard binary fractional encoding.
//
// 0x00: .0V
// ...
// 0x20: 1/8 = .125V
// 0x40: 1/4 = .25V
// 0x80: 1/2 = .5V
// ...
// 0xA0: 1/2 + 1/8 = .625V
// ...
// 0xFF: 1/2 + 1/4 + 1/8 + ... + 1/256 = 0.99V
#define PMUD_BATTUL_FRAC_W                                                   8U
#define PMUD_BATTUL_FRAC_M                                          0x000000FFU
#define PMUD_BATTUL_FRAC_S                                                   0U

//*****************************************************************************
//
// Register: PMUD_O_BATTLL
//
//*****************************************************************************
// Field:  [10:8] INT
//
// Integer part:
// Total battery voltage = INT + FRAC (integer and fractional part)
//
// 0x0: Battery voltage = 0V + fractional part
// ...
// 0x3: Battery voltage =  3V + fractional part
// 0x4: Battery voltage =  4V + fractional part
#define PMUD_BATTLL_INT_W                                                    3U
#define PMUD_BATTLL_INT_M                                           0x00000700U
#define PMUD_BATTLL_INT_S                                                    8U

// Field:   [7:0] FRAC
//
// Fractional part, standard binary fractional encoding.
//
// 0x00: .0V
// ...
// 0x20: 1/8 = .125V
// 0x40: 1/4 = .25V
// 0x80: 1/2 = .5V
// ...
// 0xA0: 1/2 + 1/8 = .625V
// ...
// 0xFF: 1/2 + 1/4 + 1/8 + ... + 1/256 = 0.99V
#define PMUD_BATTLL_FRAC_W                                                   8U
#define PMUD_BATTLL_FRAC_M                                          0x000000FFU
#define PMUD_BATTLL_FRAC_S                                                   0U

//*****************************************************************************
//
// Register: PMUD_O_TEMPUL
//
//*****************************************************************************
// Field:  [16:8] INT
//
// Integer part (signed) of temperature upper limit.
// Total value = INT + FRAC
// 2's complement encoding
//
// 0x100: Min value (-256°C)
// 0x1D8: -40°C
// 0x1FF: -1°C
// 0x00: 0°C
// 0x1B: 27°C
// 0x55: 85°C
// 0xFF: Max value (255°C)
#define PMUD_TEMPUL_INT_W                                                    9U
#define PMUD_TEMPUL_INT_M                                           0x0001FF00U
#define PMUD_TEMPUL_INT_S                                                    8U

// Field:   [7:6] FRAC
//
// Fractional part of temperature upper limit.
// Total value = INT + FRAC
// The encoding is an extension of the 2's complement encoding.
//
// 00: 0.0°C
// 01: 0.25°C
// 10: 0.5°C
// 11: 0.75°C
//
// For example:
// 000000001,00 = ( 1+0,00) =  1,00
// 000000000,11 = ( 0+0,75) =  0,75
// 000000000,10 = ( 0+0,50) =  0,50
// 000000000,01 = ( 0+0,25) =  0,25
// 000000000,00 = ( 0+0,00) =  0,00
// 111111111,11 = (-1+0,75) = -0,25
// 111111111,10 = (-1+0,50) = -0,50
// 111111111,01 = (-1+0,25) = -0,75
// 111111111,00 = (-1+0,00) = -1,00
// 111111110,11 = (-2+0,75) = -1,25
#define PMUD_TEMPUL_FRAC_W                                                   2U
#define PMUD_TEMPUL_FRAC_M                                          0x000000C0U
#define PMUD_TEMPUL_FRAC_S                                                   6U

//*****************************************************************************
//
// Register: PMUD_O_TEMPLL
//
//*****************************************************************************
// Field:  [16:8] INT
//
// Integer part (signed) of temperature lower limit.
// Total value = INT + FRAC
// 2's complement encoding
//
// 0x100: Min value (-256°C)
// 0x1D8: -40°C
// 0x1FF: -1°C
// 0x00: 0°C
// 0x1B: 27°C
// 0x55: 85°C
// 0xFF: Max value (255°C)
#define PMUD_TEMPLL_INT_W                                                    9U
#define PMUD_TEMPLL_INT_M                                           0x0001FF00U
#define PMUD_TEMPLL_INT_S                                                    8U

// Field:   [7:6] FRAC
//
// Fractional part of temperature lower limit.
// Total value = INT + FRAC
// The encoding is an extension of the 2's complement encoding.
//
// 00: 0.0°C
// 01: 0.25°C
// 10: 0.5°C
// 11: 0.75°C
//
// For example:
// 000000001,00 = ( 1+0,00) =  1,00
// 000000000,11 = ( 0+0,75) =  0,75
// 000000000,10 = ( 0+0,50) =  0,50
// 000000000,01 = ( 0+0,25) =  0,25
// 000000000,00 = ( 0+0,00) =  0,00
// 111111111,11 = (-1+0,75) = -0,25
// 111111111,10 = (-1+0,50) = -0,50
// 111111111,01 = (-1+0,25) = -0,75
// 111111111,00 = (-1+0,00) = -1,00
// 111111110,11 = (-2+0,75) = -1,25
#define PMUD_TEMPLL_FRAC_W                                                   2U
#define PMUD_TEMPLL_FRAC_M                                          0x000000C0U
#define PMUD_TEMPLL_FRAC_S                                                   6U

//*****************************************************************************
//
// Register: PMUD_O_PREFSYS
//
//*****************************************************************************
// Field: [15:11] SPARE
//
// Internal. Only to be used through TI provided API.
#define PMUD_PREFSYS_SPARE_W                                                 5U
#define PMUD_PREFSYS_SPARE_M                                        0x0000F800U
#define PMUD_PREFSYS_SPARE_S                                                11U

// Field:    [10] TEST10
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// CLR                      Internal. Only to be used through TI provided API.
#define PMUD_PREFSYS_TEST10                                         0x00000400U
#define PMUD_PREFSYS_TEST10_M                                       0x00000400U
#define PMUD_PREFSYS_TEST10_S                                               10U
#define PMUD_PREFSYS_TEST10_SET                                     0x00000400U
#define PMUD_PREFSYS_TEST10_CLR                                     0x00000000U

// Field:     [9] TEST9
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// CLR                      Internal. Only to be used through TI provided API.
#define PMUD_PREFSYS_TEST9                                          0x00000200U
#define PMUD_PREFSYS_TEST9_M                                        0x00000200U
#define PMUD_PREFSYS_TEST9_S                                                 9U
#define PMUD_PREFSYS_TEST9_SET                                      0x00000200U
#define PMUD_PREFSYS_TEST9_CLR                                      0x00000000U

// Field:     [8] TEST8
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// CLR                      Internal. Only to be used through TI provided API.
#define PMUD_PREFSYS_TEST8                                          0x00000100U
#define PMUD_PREFSYS_TEST8_M                                        0x00000100U
#define PMUD_PREFSYS_TEST8_S                                                 8U
#define PMUD_PREFSYS_TEST8_SET                                      0x00000100U
#define PMUD_PREFSYS_TEST8_CLR                                      0x00000000U

// Field:     [7] TEST7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// CLR                      Internal. Only to be used through TI provided API.
#define PMUD_PREFSYS_TEST7                                          0x00000080U
#define PMUD_PREFSYS_TEST7_M                                        0x00000080U
#define PMUD_PREFSYS_TEST7_S                                                 7U
#define PMUD_PREFSYS_TEST7_SET                                      0x00000080U
#define PMUD_PREFSYS_TEST7_CLR                                      0x00000000U

// Field:     [6] TEST6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// CLR                      Internal. Only to be used through TI provided API.
#define PMUD_PREFSYS_TEST6                                          0x00000040U
#define PMUD_PREFSYS_TEST6_M                                        0x00000040U
#define PMUD_PREFSYS_TEST6_S                                                 6U
#define PMUD_PREFSYS_TEST6_SET                                      0x00000040U
#define PMUD_PREFSYS_TEST6_CLR                                      0x00000000U

// Field:     [5] TEST5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// CLR                      Internal. Only to be used through TI provided API.
#define PMUD_PREFSYS_TEST5                                          0x00000020U
#define PMUD_PREFSYS_TEST5_M                                        0x00000020U
#define PMUD_PREFSYS_TEST5_S                                                 5U
#define PMUD_PREFSYS_TEST5_SET                                      0x00000020U
#define PMUD_PREFSYS_TEST5_CLR                                      0x00000000U

// Field:     [4] TEST4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// CLR                      Internal. Only to be used through TI provided API.
#define PMUD_PREFSYS_TEST4                                          0x00000010U
#define PMUD_PREFSYS_TEST4_M                                        0x00000010U
#define PMUD_PREFSYS_TEST4_S                                                 4U
#define PMUD_PREFSYS_TEST4_SET                                      0x00000010U
#define PMUD_PREFSYS_TEST4_CLR                                      0x00000000U

// Field:     [3] TEST3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// CLR                      Internal. Only to be used through TI provided API.
#define PMUD_PREFSYS_TEST3                                          0x00000008U
#define PMUD_PREFSYS_TEST3_M                                        0x00000008U
#define PMUD_PREFSYS_TEST3_S                                                 3U
#define PMUD_PREFSYS_TEST3_SET                                      0x00000008U
#define PMUD_PREFSYS_TEST3_CLR                                      0x00000000U

// Field:     [2] TEST2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// CLR                      Internal. Only to be used through TI provided API.
#define PMUD_PREFSYS_TEST2                                          0x00000004U
#define PMUD_PREFSYS_TEST2_M                                        0x00000004U
#define PMUD_PREFSYS_TEST2_S                                                 2U
#define PMUD_PREFSYS_TEST2_SET                                      0x00000004U
#define PMUD_PREFSYS_TEST2_CLR                                      0x00000000U

// Field:     [1] TEST1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// CLR                      Internal. Only to be used through TI provided API.
#define PMUD_PREFSYS_TEST1                                          0x00000002U
#define PMUD_PREFSYS_TEST1_M                                        0x00000002U
#define PMUD_PREFSYS_TEST1_S                                                 1U
#define PMUD_PREFSYS_TEST1_SET                                      0x00000002U
#define PMUD_PREFSYS_TEST1_CLR                                      0x00000000U

// Field:     [0] TEST0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// CLR                      Internal. Only to be used through TI provided API.
#define PMUD_PREFSYS_TEST0                                          0x00000001U
#define PMUD_PREFSYS_TEST0_M                                        0x00000001U
#define PMUD_PREFSYS_TEST0_S                                                 0U
#define PMUD_PREFSYS_TEST0_SET                                      0x00000001U
#define PMUD_PREFSYS_TEST0_CLR                                      0x00000000U

//*****************************************************************************
//
// Register: PMUD_O_PREG0
//
//*****************************************************************************
// Field:    [11] LOW_IPEAK_DIS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SET                      Internal. Only to be used through TI provided API.
// CLR                      Internal. Only to be used through TI provided API.
#define PMUD_PREG0_LOW_IPEAK_DIS                                    0x00000800U
#define PMUD_PREG0_LOW_IPEAK_DIS_M                                  0x00000800U
#define PMUD_PREG0_LOW_IPEAK_DIS_S                                          11U
#define PMUD_PREG0_LOW_IPEAK_DIS_SET                                0x00000800U
#define PMUD_PREG0_LOW_IPEAK_DIS_CLR                                0x00000000U

// Field:    [10] SOCLDO_ITESTEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define PMUD_PREG0_SOCLDO_ITESTEN                                   0x00000400U
#define PMUD_PREG0_SOCLDO_ITESTEN_M                                 0x00000400U
#define PMUD_PREG0_SOCLDO_ITESTEN_S                                         10U
#define PMUD_PREG0_SOCLDO_ITESTEN_EN                                0x00000400U
#define PMUD_PREG0_SOCLDO_ITESTEN_DIS                               0x00000000U

// Field:   [9:7] SOCLDO_ATBSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VDD_AON                  Internal. Only to be used through TI provided API.
// SOCLDO_VREF_AMP_OUT      Internal. Only to be used through TI provided API.
// SOCLDO_ITEST             Internal. Only to be used through TI provided API.
// NC                       Internal. Only to be used through TI provided API.
#define PMUD_PREG0_SOCLDO_ATBSEL_W                                           3U
#define PMUD_PREG0_SOCLDO_ATBSEL_M                                  0x00000380U
#define PMUD_PREG0_SOCLDO_ATBSEL_S                                           7U
#define PMUD_PREG0_SOCLDO_ATBSEL_VDD_AON                            0x00000200U
#define PMUD_PREG0_SOCLDO_ATBSEL_SOCLDO_VREF_AMP_OUT                0x00000100U
#define PMUD_PREG0_SOCLDO_ATBSEL_SOCLDO_ITEST                       0x00000080U
#define PMUD_PREG0_SOCLDO_ATBSEL_NC                                 0x00000000U

// Field:   [6:5] UDIGLDO_ATBSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VAL3                     Internal. Only to be used through TI provided API.
// VAL2                     Internal. Only to be used through TI provided API.
// VAL1                     Internal. Only to be used through TI provided API.
// VAL0                     Internal. Only to be used through TI provided API.
#define PMUD_PREG0_UDIGLDO_ATBSEL_W                                          2U
#define PMUD_PREG0_UDIGLDO_ATBSEL_M                                 0x00000060U
#define PMUD_PREG0_UDIGLDO_ATBSEL_S                                          5U
#define PMUD_PREG0_UDIGLDO_ATBSEL_VAL3                              0x00000060U
#define PMUD_PREG0_UDIGLDO_ATBSEL_VAL2                              0x00000040U
#define PMUD_PREG0_UDIGLDO_ATBSEL_VAL1                              0x00000020U
#define PMUD_PREG0_UDIGLDO_ATBSEL_VAL0                              0x00000000U

// Field:   [4:2] DIGLDO_ATBSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VAL4                     Internal. Only to be used through TI provided API.
// VAL2                     Internal. Only to be used through TI provided API.
// VAL1                     Internal. Only to be used through TI provided API.
// VAL0                     Internal. Only to be used through TI provided API.
#define PMUD_PREG0_DIGLDO_ATBSEL_W                                           3U
#define PMUD_PREG0_DIGLDO_ATBSEL_M                                  0x0000001CU
#define PMUD_PREG0_DIGLDO_ATBSEL_S                                           2U
#define PMUD_PREG0_DIGLDO_ATBSEL_VAL4                               0x00000010U
#define PMUD_PREG0_DIGLDO_ATBSEL_VAL2                               0x00000008U
#define PMUD_PREG0_DIGLDO_ATBSEL_VAL1                               0x00000004U
#define PMUD_PREG0_DIGLDO_ATBSEL_VAL0                               0x00000000U

// Field:     [1] SPARE
//
// Internal. Only to be used through TI provided API.
#define PMUD_PREG0_SPARE                                            0x00000002U
#define PMUD_PREG0_SPARE_M                                          0x00000002U
#define PMUD_PREG0_SPARE_S                                                   1U

// Field:     [0] UDIGLDO_EN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define PMUD_PREG0_UDIGLDO_EN                                       0x00000001U
#define PMUD_PREG0_UDIGLDO_EN_M                                     0x00000001U
#define PMUD_PREG0_UDIGLDO_EN_S                                              0U
#define PMUD_PREG0_UDIGLDO_EN_EN                                    0x00000001U
#define PMUD_PREG0_UDIGLDO_EN_DIS                                   0x00000000U

//*****************************************************************************
//
// Register: PMUD_O_PREG1
//
//*****************************************************************************
// Field:    [19] TEST_DCDC_NMOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define PMUD_PREG1_TEST_DCDC_NMOS                                   0x00080000U
#define PMUD_PREG1_TEST_DCDC_NMOS_M                                 0x00080000U
#define PMUD_PREG1_TEST_DCDC_NMOS_S                                         19U
#define PMUD_PREG1_TEST_DCDC_NMOS_EN                                0x00080000U
#define PMUD_PREG1_TEST_DCDC_NMOS_DIS                               0x00000000U

// Field:    [18] TEST_DCDC_PMOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define PMUD_PREG1_TEST_DCDC_PMOS                                   0x00040000U
#define PMUD_PREG1_TEST_DCDC_PMOS_M                                 0x00040000U
#define PMUD_PREG1_TEST_DCDC_PMOS_S                                         18U
#define PMUD_PREG1_TEST_DCDC_PMOS_EN                                0x00040000U
#define PMUD_PREG1_TEST_DCDC_PMOS_DIS                               0x00000000U

// Field:    [17] DITHER_EN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define PMUD_PREG1_DITHER_EN                                        0x00020000U
#define PMUD_PREG1_DITHER_EN_M                                      0x00020000U
#define PMUD_PREG1_DITHER_EN_S                                              17U
#define PMUD_PREG1_DITHER_EN_EN                                     0x00020000U
#define PMUD_PREG1_DITHER_EN_DIS                                    0x00000000U

// Field:    [16] GLDO_AON
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define PMUD_PREG1_GLDO_AON                                         0x00010000U
#define PMUD_PREG1_GLDO_AON_M                                       0x00010000U
#define PMUD_PREG1_GLDO_AON_S                                               16U
#define PMUD_PREG1_GLDO_AON_EN                                      0x00010000U
#define PMUD_PREG1_GLDO_AON_DIS                                     0x00000000U

// Field:    [15] RCHG_BLK_VTRIG_EN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define PMUD_PREG1_RCHG_BLK_VTRIG_EN                                0x00008000U
#define PMUD_PREG1_RCHG_BLK_VTRIG_EN_M                              0x00008000U
#define PMUD_PREG1_RCHG_BLK_VTRIG_EN_S                                      15U
#define PMUD_PREG1_RCHG_BLK_VTRIG_EN_EN                             0x00008000U
#define PMUD_PREG1_RCHG_BLK_VTRIG_EN_DIS                            0x00000000U

// Field:    [14] RCHG_BLK_ATEST_EN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define PMUD_PREG1_RCHG_BLK_ATEST_EN                                0x00004000U
#define PMUD_PREG1_RCHG_BLK_ATEST_EN_M                              0x00004000U
#define PMUD_PREG1_RCHG_BLK_ATEST_EN_S                                      14U
#define PMUD_PREG1_RCHG_BLK_ATEST_EN_EN                             0x00004000U
#define PMUD_PREG1_RCHG_BLK_ATEST_EN_DIS                            0x00000000U

// Field:    [13] RCHG_FORCE_SAMP_VREF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define PMUD_PREG1_RCHG_FORCE_SAMP_VREF                             0x00002000U
#define PMUD_PREG1_RCHG_FORCE_SAMP_VREF_M                           0x00002000U
#define PMUD_PREG1_RCHG_FORCE_SAMP_VREF_S                                   13U
#define PMUD_PREG1_RCHG_FORCE_SAMP_VREF_EN                          0x00002000U
#define PMUD_PREG1_RCHG_FORCE_SAMP_VREF_DIS                         0x00000000U

// Field:    [12] RCHG_COMP_CLK_DIS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIS                      Internal. Only to be used through TI provided API.
// EN                       Internal. Only to be used through TI provided API.
#define PMUD_PREG1_RCHG_COMP_CLK_DIS                                0x00001000U
#define PMUD_PREG1_RCHG_COMP_CLK_DIS_M                              0x00001000U
#define PMUD_PREG1_RCHG_COMP_CLK_DIS_S                                      12U
#define PMUD_PREG1_RCHG_COMP_CLK_DIS_DIS                            0x00001000U
#define PMUD_PREG1_RCHG_COMP_CLK_DIS_EN                             0x00000000U

// Field:     [7] SPARE
//
// Internal. Only to be used through TI provided API.
#define PMUD_PREG1_SPARE                                            0x00000080U
#define PMUD_PREG1_SPARE_M                                          0x00000080U
#define PMUD_PREG1_SPARE_S                                                   7U

// Field:     [6] VDDR_ATBSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define PMUD_PREG1_VDDR_ATBSEL                                      0x00000040U
#define PMUD_PREG1_VDDR_ATBSEL_M                                    0x00000040U
#define PMUD_PREG1_VDDR_ATBSEL_S                                             6U
#define PMUD_PREG1_VDDR_ATBSEL_EN                                   0x00000040U
#define PMUD_PREG1_VDDR_ATBSEL_DIS                                  0x00000000U

// Field:     [5] GLDO_EA_BIAS_DIS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// OFF                      Internal. Only to be used through TI provided API.
// ON                       Internal. Only to be used through TI provided API.
#define PMUD_PREG1_GLDO_EA_BIAS_DIS                                 0x00000020U
#define PMUD_PREG1_GLDO_EA_BIAS_DIS_M                               0x00000020U
#define PMUD_PREG1_GLDO_EA_BIAS_DIS_S                                        5U
#define PMUD_PREG1_GLDO_EA_BIAS_DIS_OFF                             0x00000020U
#define PMUD_PREG1_GLDO_EA_BIAS_DIS_ON                              0x00000000U

// Field:   [4:1] GLDO_ATBSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VDDROK                   Internal. Only to be used through TI provided API.
// IB1U                     Internal. Only to be used through TI provided API.
// PASSGATE                 Internal. Only to be used through TI provided API.
// ERRAMP_OUT               Internal. Only to be used through TI provided API.
// NC                       Internal. Only to be used through TI provided API.
#define PMUD_PREG1_GLDO_ATBSEL_W                                             4U
#define PMUD_PREG1_GLDO_ATBSEL_M                                    0x0000001EU
#define PMUD_PREG1_GLDO_ATBSEL_S                                             1U
#define PMUD_PREG1_GLDO_ATBSEL_VDDROK                               0x00000010U
#define PMUD_PREG1_GLDO_ATBSEL_IB1U                                 0x00000008U
#define PMUD_PREG1_GLDO_ATBSEL_PASSGATE                             0x00000004U
#define PMUD_PREG1_GLDO_ATBSEL_ERRAMP_OUT                           0x00000002U
#define PMUD_PREG1_GLDO_ATBSEL_NC                                   0x00000000U

//*****************************************************************************
//
// Register: PMUD_O_PREG2
//
//*****************************************************************************
// Field:     [5] RSTNMASK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BM                       Internal. Only to be used through TI provided API.
// BNM                      Internal. Only to be used through TI provided API.
#define PMUD_PREG2_RSTNMASK                                         0x00000020U
#define PMUD_PREG2_RSTNMASK_M                                       0x00000020U
#define PMUD_PREG2_RSTNMASK_S                                                5U
#define PMUD_PREG2_RSTNMASK_BM                                      0x00000020U
#define PMUD_PREG2_RSTNMASK_BNM                                     0x00000000U

// Field:     [4] DCDC_RCHG_ATBSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RCHG_BLK                 Internal. Only to be used through TI provided API.
// DCDC_GLDO                Internal. Only to be used through TI provided API.
#define PMUD_PREG2_DCDC_RCHG_ATBSEL                                 0x00000010U
#define PMUD_PREG2_DCDC_RCHG_ATBSEL_M                               0x00000010U
#define PMUD_PREG2_DCDC_RCHG_ATBSEL_S                                        4U
#define PMUD_PREG2_DCDC_RCHG_ATBSEL_RCHG_BLK                        0x00000010U
#define PMUD_PREG2_DCDC_RCHG_ATBSEL_DCDC_GLDO                       0x00000000U

// Field:   [3:0] PMUREG_ATBSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DCDC_ATEST0_RCHG_ATEST1  Internal. Only to be used through TI provided API.
// SOCLDOI_A0               Internal. Only to be used through TI provided API.
// RESERVED                 Internal. Only to be used through TI provided API.
// SOCLDOV_A1               Internal. Only to be used through TI provided API.
// NC                       Internal. Only to be used through TI provided API.
#define PMUD_PREG2_PMUREG_ATBSEL_W                                           4U
#define PMUD_PREG2_PMUREG_ATBSEL_M                                  0x0000000FU
#define PMUD_PREG2_PMUREG_ATBSEL_S                                           0U
#define PMUD_PREG2_PMUREG_ATBSEL_DCDC_ATEST0_RCHG_ATEST1            0x00000008U
#define PMUD_PREG2_PMUREG_ATBSEL_SOCLDOI_A0                         0x00000004U
#define PMUD_PREG2_PMUREG_ATBSEL_RESERVED                           0x00000002U
#define PMUD_PREG2_PMUREG_ATBSEL_SOCLDOV_A1                         0x00000001U
#define PMUD_PREG2_PMUREG_ATBSEL_NC                                 0x00000000U

//*****************************************************************************
//
// Register: PMUD_O_DCDCCFG
//
//*****************************************************************************
// Field: [22:16] LM_HIGHTH
//
// DCDC load meter high threshold value for adaptive IPEAK adjustment. DCDC
// load meter output is in percentage scale so the applicable values are 'd1 to
// 'd100. Values from 'd101 to 'd127 are invalid and not to be used.
#define PMUD_DCDCCFG_LM_HIGHTH_W                                             7U
#define PMUD_DCDCCFG_LM_HIGHTH_M                                    0x007F0000U
#define PMUD_DCDCCFG_LM_HIGHTH_S                                            16U

// Field:  [14:8] LM_LOWTH
//
// DCDC load meter low threshold value for adaptive IPEAK adjustment. DCDC load
// meter output is in percentage scale so the applicable values are 'd1 to
// 'd100. Values from 'd101 to 'd127 are invalid and not to be used.
#define PMUD_DCDCCFG_LM_LOWTH_W                                              7U
#define PMUD_DCDCCFG_LM_LOWTH_M                                     0x00007F00U
#define PMUD_DCDCCFG_LM_LOWTH_S                                              8U

// Field:     [4] ADP_IPEAK_EN
//
// This bit is used to enable adaptive IPEAK adjustment scheme in hardware.
// When this bit is set, DCDC IPEAK value is automatically adjusted to suitable
// value by sensing the DCDC load meter output for better DCDC operational
// efficiency.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define PMUD_DCDCCFG_ADP_IPEAK_EN                                   0x00000010U
#define PMUD_DCDCCFG_ADP_IPEAK_EN_M                                 0x00000010U
#define PMUD_DCDCCFG_ADP_IPEAK_EN_S                                          4U
#define PMUD_DCDCCFG_ADP_IPEAK_EN_EN                                0x00000010U
#define PMUD_DCDCCFG_ADP_IPEAK_EN_DIS                               0x00000000U

// Field:     [0] LMEN
//
// This bit is used to enable DCDC load meter. Software can obtain DCDC load
// meter value from DCDCSTAT regiser and adjust IPEAK setting in SYS0.TDCDC
// register accordingly.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define PMUD_DCDCCFG_LMEN                                           0x00000001U
#define PMUD_DCDCCFG_LMEN_M                                         0x00000001U
#define PMUD_DCDCCFG_LMEN_S                                                  0U
#define PMUD_DCDCCFG_LMEN_EN                                        0x00000001U
#define PMUD_DCDCCFG_LMEN_DIS                                       0x00000000U

//*****************************************************************************
//
// Register: PMUD_O_DCDCSTAT
//
//*****************************************************************************
// Field:  [10:8] IPEAK
//
// DCDC IPEAK value. This value is same as what is programmed in
// SYS0:TMUTE4.IPEAK when adaptive IPEAK adjustment scheme is not enabled, and
// it shows current IPEAK value applied by hardware when adaptive IPEAK
// adjustment scheme is enabled.
// Note: Software can only support IPEAK = 1
#define PMUD_DCDCSTAT_IPEAK_W                                                3U
#define PMUD_DCDCSTAT_IPEAK_M                                       0x00000700U
#define PMUD_DCDCSTAT_IPEAK_S                                                8U

// Field:   [6:0] LOAD
//
// This indicates DCDC load meter output value in percentage scale.
// Applicable range is 'd1 to 'd100.
#define PMUD_DCDCSTAT_LOAD_W                                                 7U
#define PMUD_DCDCSTAT_LOAD_M                                        0x0000007FU
#define PMUD_DCDCSTAT_LOAD_S                                                 0U


#endif // __PMUD__
