/*
 * Copyright (c) 2018-2026, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 /*
 *  ======== pbe_ble_cs_ram_regs.h ========
*/

#ifndef __PBE_BLE_CS_RAM_REGS_H
#define __PBE_BLE_CS_RAM_REGS_H

//******************************************************************************
// REGISTER OFFSETS
//******************************************************************************
// 
#define PBE_BLE_CS_RAM_O_MODE                                        0x00000020U

// 
#define PBE_BLE_CS_RAM_O_ANTMSK                                      0x00000022U

// 
#define PBE_BLE_CS_RAM_O_ANT0                                        0x00000024U

// 
#define PBE_BLE_CS_RAM_O_ANT1                                        0x00000026U

// 
#define PBE_BLE_CS_RAM_O_ANT2                                        0x00000028U

// 
#define PBE_BLE_CS_RAM_O_ANT3                                        0x0000002AU

// 
#define PBE_BLE_CS_RAM_O_ANTN                                        0x0000002CU

// 
#define PBE_BLE_CS_RAM_O_TFCS                                        0x0000002EU

// 
#define PBE_BLE_CS_RAM_O_TFM                                         0x00000030U

// 
#define PBE_BLE_CS_RAM_O_TPM                                         0x00000032U

// 
#define PBE_BLE_CS_RAM_O_TIP1                                        0x00000034U

// 
#define PBE_BLE_CS_RAM_O_TIP2                                        0x00000036U

// 
#define PBE_BLE_CS_RAM_O_TRXTIMEOUTR013                              0x00000038U

// 
#define PBE_BLE_CS_RAM_O_TRXTIMEOUTI0                                0x0000003AU

// 
#define PBE_BLE_CS_RAM_O_TRXTIMEOUTI3                                0x0000003CU

// 
#define PBE_BLE_CS_RAM_O_TPILOTADJ                                   0x0000003EU

// 
#define PBE_BLE_CS_RAM_O_TSW                                         0x00000040U

// 
#define PBE_BLE_CS_RAM_O_DEMMISC3                                    0x00000042U

// 
#define PBE_BLE_CS_RAM_O_TRXWIDENINGR0                               0x00000044U

// 
#define PBE_BLE_CS_RAM_O_TSTEPREMAININGR0                            0x00000046U

// 
#define PBE_BLE_CS_RAM_O_TSWADJA                                     0x00000048U

// 
#define PBE_BLE_CS_RAM_O_TSWADJB                                     0x0000004AU

// 
#define PBE_BLE_CS_RAM_O_S2ROUTIDX                                   0x0000004CU

// 
#define PBE_BLE_CS_RAM_O_S2ROUTCHIDX                                 0x0000004EU

// 
#define PBE_BLE_CS_RAM_O_S2ROUTWORDSIZE                              0x00000050U

// 
#define PBE_BLE_CS_RAM_O_S2ROUTPAYLOADLEN                            0x00000052U

// 
#define PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD0L                             0x00000054U

// 
#define PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD0H                             0x00000056U

// 
#define PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD1L                             0x00000058U

// 
#define PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD1H                             0x0000005AU

// 
#define PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD2L                             0x0000005CU

// 
#define PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD2H                             0x0000005EU

// 
#define PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD3L                             0x00000060U

// 
#define PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD3H                             0x00000062U

// 
#define PBE_BLE_CS_RAM_O_FOFFSUM                                     0x00000064U

// 
#define PBE_BLE_CS_RAM_O_FOFFNUM                                     0x00000066U

// 
#define PBE_BLE_CS_RAM_O_FOFFLAST                                    0x00000068U

// 
#define PBE_BLE_CS_RAM_O_FOFFCOMP                                    0x0000006AU

// 
#define PBE_BLE_CS_RAM_O_RSSILAST                                    0x0000006CU

// 
#define PBE_BLE_CS_RAM_O_RSSISUM0                                    0x0000006EU

// 
#define PBE_BLE_CS_RAM_O_RSSINUM0                                    0x00000070U

// 
#define PBE_BLE_CS_RAM_O_NSTEPSDONE                                  0x00000072U

// 
#define PBE_BLE_CS_RAM_O_TSTEPACCL                                   0x00000074U

// 
#define PBE_BLE_CS_RAM_O_TSTEPACCH                                   0x00000076U

// 
#define PBE_BLE_CS_RAM_O_TSTEPACCTHRL                                0x00000078U

// 
#define PBE_BLE_CS_RAM_O_TSTEPACCTHRH                                0x0000007AU

// 
#define PBE_BLE_CS_RAM_O_TSTEPCOMP                                   0x0000007CU

// 
#define PBE_BLE_CS_RAM_O_TPOSTPROCESS                                0x0000007EU

// 
#define PBE_BLE_CS_RAM_O_TPOSTPROCESSDIV                             0x00000080U

//******************************************************************************
// Register: MODE
//******************************************************************************
// Field: [15:8] num_steps
//
// 
#define PBE_BLE_CS_RAM_MODE_NUM_STEPS_W                                       8U
#define PBE_BLE_CS_RAM_MODE_NUM_STEPS_M                                  0xFF00U
#define PBE_BLE_CS_RAM_MODE_NUM_STEPS_S                                       8U

// Field: [7:7] coherent_phase
//
// 
#define PBE_BLE_CS_RAM_MODE_COHERENT_PHASE                               0x0080U
#define PBE_BLE_CS_RAM_MODE_COHERENT_PHASE_M                             0x0080U
#define PBE_BLE_CS_RAM_MODE_COHERENT_PHASE_S                                  7U

// Field: [6:6] inline_phase
//
// 
#define PBE_BLE_CS_RAM_MODE_INLINE_PHASE                                 0x0040U
#define PBE_BLE_CS_RAM_MODE_INLINE_PHASE_M                               0x0040U
#define PBE_BLE_CS_RAM_MODE_INLINE_PHASE_S                                    6U

// Field: [5:5] report_format
//
// 
#define PBE_BLE_CS_RAM_MODE_REPORT_FORMAT                                0x0020U
#define PBE_BLE_CS_RAM_MODE_REPORT_FORMAT_M                              0x0020U
#define PBE_BLE_CS_RAM_MODE_REPORT_FORMAT_S                                   5U

// Field: [4:4] repeat_steps
//
// 
#define PBE_BLE_CS_RAM_MODE_REPEAT_STEPS                                 0x0010U
#define PBE_BLE_CS_RAM_MODE_REPEAT_STEPS_M                               0x0010U
#define PBE_BLE_CS_RAM_MODE_REPEAT_STEPS_S                                    4U

// Field: [3:2] phy
//
// Select the physical layer
#define PBE_BLE_CS_RAM_MODE_PHY_W                                             2U
#define PBE_BLE_CS_RAM_MODE_PHY_M                                        0x000CU
#define PBE_BLE_CS_RAM_MODE_PHY_S                                             2U
#define PBE_BLE_CS_RAM_MODE_PHY_1M_BT05                                  0x0000U
#define PBE_BLE_CS_RAM_MODE_PHY_2M_BT05                                  0x0004U
#define PBE_BLE_CS_RAM_MODE_PHY_2M_BT20                                  0x0008U

// Field: [1:0] role
//
// Select the role
#define PBE_BLE_CS_RAM_MODE_ROLE_W                                            2U
#define PBE_BLE_CS_RAM_MODE_ROLE_M                                       0x0003U
#define PBE_BLE_CS_RAM_MODE_ROLE_S                                            0U
#define PBE_BLE_CS_RAM_MODE_ROLE_INITIATOR                               0x0000U
#define PBE_BLE_CS_RAM_MODE_ROLE_REFLECTOR                               0x0001U

//******************************************************************************
// Register: ANTMSK
//******************************************************************************
// Field: [7:0] val
//
// 
#define PBE_BLE_CS_RAM_ANTMSK_VAL_W                                           8U
#define PBE_BLE_CS_RAM_ANTMSK_VAL_M                                      0x00FFU
#define PBE_BLE_CS_RAM_ANTMSK_VAL_S                                           0U

//******************************************************************************
// Register: ANT0
//******************************************************************************
// Field: [7:0] val
//
// 
#define PBE_BLE_CS_RAM_ANT0_VAL_W                                             8U
#define PBE_BLE_CS_RAM_ANT0_VAL_M                                        0x00FFU
#define PBE_BLE_CS_RAM_ANT0_VAL_S                                             0U

//******************************************************************************
// Register: ANT1
//******************************************************************************
// Field: [7:0] val
//
// 
#define PBE_BLE_CS_RAM_ANT1_VAL_W                                             8U
#define PBE_BLE_CS_RAM_ANT1_VAL_M                                        0x00FFU
#define PBE_BLE_CS_RAM_ANT1_VAL_S                                             0U

//******************************************************************************
// Register: ANT2
//******************************************************************************
// Field: [7:0] val
//
// 
#define PBE_BLE_CS_RAM_ANT2_VAL_W                                             8U
#define PBE_BLE_CS_RAM_ANT2_VAL_M                                        0x00FFU
#define PBE_BLE_CS_RAM_ANT2_VAL_S                                             0U

//******************************************************************************
// Register: ANT3
//******************************************************************************
// Field: [7:0] val
//
// 
#define PBE_BLE_CS_RAM_ANT3_VAL_W                                             8U
#define PBE_BLE_CS_RAM_ANT3_VAL_M                                        0x00FFU
#define PBE_BLE_CS_RAM_ANT3_VAL_S                                             0U

//******************************************************************************
// Register: ANTN
//******************************************************************************
// Field: [7:0] val
//
// 
#define PBE_BLE_CS_RAM_ANTN_VAL_W                                             8U
#define PBE_BLE_CS_RAM_ANTN_VAL_M                                        0x00FFU
#define PBE_BLE_CS_RAM_ANTN_VAL_S                                             0U

//******************************************************************************
// Register: TFCS
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TFCS_VAL_W                                            16U
#define PBE_BLE_CS_RAM_TFCS_VAL_M                                        0xFFFFU
#define PBE_BLE_CS_RAM_TFCS_VAL_S                                             0U

//******************************************************************************
// Register: TFM
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TFM_VAL_W                                             16U
#define PBE_BLE_CS_RAM_TFM_VAL_M                                         0xFFFFU
#define PBE_BLE_CS_RAM_TFM_VAL_S                                              0U

//******************************************************************************
// Register: TPM
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TPM_VAL_W                                             16U
#define PBE_BLE_CS_RAM_TPM_VAL_M                                         0xFFFFU
#define PBE_BLE_CS_RAM_TPM_VAL_S                                              0U

//******************************************************************************
// Register: TIP1
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TIP1_VAL_W                                            16U
#define PBE_BLE_CS_RAM_TIP1_VAL_M                                        0xFFFFU
#define PBE_BLE_CS_RAM_TIP1_VAL_S                                             0U

//******************************************************************************
// Register: TIP2
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TIP2_VAL_W                                            16U
#define PBE_BLE_CS_RAM_TIP2_VAL_M                                        0xFFFFU
#define PBE_BLE_CS_RAM_TIP2_VAL_S                                             0U

//******************************************************************************
// Register: TRXTIMEOUTR013
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TRXTIMEOUTR013_VAL_W                                  16U
#define PBE_BLE_CS_RAM_TRXTIMEOUTR013_VAL_M                              0xFFFFU
#define PBE_BLE_CS_RAM_TRXTIMEOUTR013_VAL_S                                   0U

//******************************************************************************
// Register: TRXTIMEOUTI0
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TRXTIMEOUTI0_VAL_W                                    16U
#define PBE_BLE_CS_RAM_TRXTIMEOUTI0_VAL_M                                0xFFFFU
#define PBE_BLE_CS_RAM_TRXTIMEOUTI0_VAL_S                                     0U

//******************************************************************************
// Register: TRXTIMEOUTI3
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TRXTIMEOUTI3_VAL_W                                    16U
#define PBE_BLE_CS_RAM_TRXTIMEOUTI3_VAL_M                                0xFFFFU
#define PBE_BLE_CS_RAM_TRXTIMEOUTI3_VAL_S                                     0U

//******************************************************************************
// Register: TPILOTADJ
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TPILOTADJ_VAL_W                                       16U
#define PBE_BLE_CS_RAM_TPILOTADJ_VAL_M                                   0xFFFFU
#define PBE_BLE_CS_RAM_TPILOTADJ_VAL_S                                        0U

//******************************************************************************
// Register: TSW
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TSW_VAL_W                                             16U
#define PBE_BLE_CS_RAM_TSW_VAL_M                                         0xFFFFU
#define PBE_BLE_CS_RAM_TSW_VAL_S                                              0U

//******************************************************************************
// Register: DEMMISC3
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_DEMMISC3_VAL_W                                        16U
#define PBE_BLE_CS_RAM_DEMMISC3_VAL_M                                    0xFFFFU
#define PBE_BLE_CS_RAM_DEMMISC3_VAL_S                                         0U

//******************************************************************************
// Register: TRXWIDENINGR0
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TRXWIDENINGR0_VAL_W                                   16U
#define PBE_BLE_CS_RAM_TRXWIDENINGR0_VAL_M                               0xFFFFU
#define PBE_BLE_CS_RAM_TRXWIDENINGR0_VAL_S                                    0U

//******************************************************************************
// Register: TSTEPREMAININGR0
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TSTEPREMAININGR0_VAL_W                                16U
#define PBE_BLE_CS_RAM_TSTEPREMAININGR0_VAL_M                            0xFFFFU
#define PBE_BLE_CS_RAM_TSTEPREMAININGR0_VAL_S                                 0U

//******************************************************************************
// Register: TSWADJA
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TSWADJA_VAL_W                                         16U
#define PBE_BLE_CS_RAM_TSWADJA_VAL_M                                     0xFFFFU
#define PBE_BLE_CS_RAM_TSWADJA_VAL_S                                          0U

//******************************************************************************
// Register: TSWADJB
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TSWADJB_VAL_W                                         16U
#define PBE_BLE_CS_RAM_TSWADJB_VAL_M                                     0xFFFFU
#define PBE_BLE_CS_RAM_TSWADJB_VAL_S                                          0U

//******************************************************************************
// Register: S2ROUTIDX
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_S2ROUTIDX_VAL_W                                       16U
#define PBE_BLE_CS_RAM_S2ROUTIDX_VAL_M                                   0xFFFFU
#define PBE_BLE_CS_RAM_S2ROUTIDX_VAL_S                                        0U

//******************************************************************************
// Register: S2ROUTCHIDX
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_S2ROUTCHIDX_VAL_W                                     16U
#define PBE_BLE_CS_RAM_S2ROUTCHIDX_VAL_M                                 0xFFFFU
#define PBE_BLE_CS_RAM_S2ROUTCHIDX_VAL_S                                      0U

//******************************************************************************
// Register: S2ROUTWORDSIZE
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_S2ROUTWORDSIZE_VAL_W                                  16U
#define PBE_BLE_CS_RAM_S2ROUTWORDSIZE_VAL_M                              0xFFFFU
#define PBE_BLE_CS_RAM_S2ROUTWORDSIZE_VAL_S                                   0U

//******************************************************************************
// Register: S2ROUTPAYLOADLEN
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_S2ROUTPAYLOADLEN_VAL_W                                16U
#define PBE_BLE_CS_RAM_S2ROUTPAYLOADLEN_VAL_M                            0xFFFFU
#define PBE_BLE_CS_RAM_S2ROUTPAYLOADLEN_VAL_S                                 0U

//******************************************************************************
// Register: S2ROUTPAYLOAD0L
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD0L_VAL_W                                 16U
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD0L_VAL_M                             0xFFFFU
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD0L_VAL_S                                  0U

//******************************************************************************
// Register: S2ROUTPAYLOAD0H
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD0H_VAL_W                                 16U
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD0H_VAL_M                             0xFFFFU
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD0H_VAL_S                                  0U

//******************************************************************************
// Register: S2ROUTPAYLOAD1L
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD1L_VAL_W                                 16U
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD1L_VAL_M                             0xFFFFU
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD1L_VAL_S                                  0U

//******************************************************************************
// Register: S2ROUTPAYLOAD1H
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD1H_VAL_W                                 16U
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD1H_VAL_M                             0xFFFFU
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD1H_VAL_S                                  0U

//******************************************************************************
// Register: S2ROUTPAYLOAD2L
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD2L_VAL_W                                 16U
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD2L_VAL_M                             0xFFFFU
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD2L_VAL_S                                  0U

//******************************************************************************
// Register: S2ROUTPAYLOAD2H
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD2H_VAL_W                                 16U
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD2H_VAL_M                             0xFFFFU
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD2H_VAL_S                                  0U

//******************************************************************************
// Register: S2ROUTPAYLOAD3L
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD3L_VAL_W                                 16U
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD3L_VAL_M                             0xFFFFU
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD3L_VAL_S                                  0U

//******************************************************************************
// Register: S2ROUTPAYLOAD3H
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD3H_VAL_W                                 16U
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD3H_VAL_M                             0xFFFFU
#define PBE_BLE_CS_RAM_S2ROUTPAYLOAD3H_VAL_S                                  0U

//******************************************************************************
// Register: FOFFSUM
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_FOFFSUM_VAL_W                                         16U
#define PBE_BLE_CS_RAM_FOFFSUM_VAL_M                                     0xFFFFU
#define PBE_BLE_CS_RAM_FOFFSUM_VAL_S                                          0U

//******************************************************************************
// Register: FOFFNUM
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_FOFFNUM_VAL_W                                         16U
#define PBE_BLE_CS_RAM_FOFFNUM_VAL_M                                     0xFFFFU
#define PBE_BLE_CS_RAM_FOFFNUM_VAL_S                                          0U

//******************************************************************************
// Register: FOFFLAST
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_FOFFLAST_VAL_W                                        16U
#define PBE_BLE_CS_RAM_FOFFLAST_VAL_M                                    0xFFFFU
#define PBE_BLE_CS_RAM_FOFFLAST_VAL_S                                         0U

//******************************************************************************
// Register: FOFFCOMP
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_FOFFCOMP_VAL_W                                        16U
#define PBE_BLE_CS_RAM_FOFFCOMP_VAL_M                                    0xFFFFU
#define PBE_BLE_CS_RAM_FOFFCOMP_VAL_S                                         0U

//******************************************************************************
// Register: RSSILAST
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_RSSILAST_VAL_W                                        16U
#define PBE_BLE_CS_RAM_RSSILAST_VAL_M                                    0xFFFFU
#define PBE_BLE_CS_RAM_RSSILAST_VAL_S                                         0U

//******************************************************************************
// Register: RSSISUM0
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_RSSISUM0_VAL_W                                        16U
#define PBE_BLE_CS_RAM_RSSISUM0_VAL_M                                    0xFFFFU
#define PBE_BLE_CS_RAM_RSSISUM0_VAL_S                                         0U

//******************************************************************************
// Register: RSSINUM0
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_RSSINUM0_VAL_W                                        16U
#define PBE_BLE_CS_RAM_RSSINUM0_VAL_M                                    0xFFFFU
#define PBE_BLE_CS_RAM_RSSINUM0_VAL_S                                         0U

//******************************************************************************
// Register: NSTEPSDONE
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_NSTEPSDONE_VAL_W                                      16U
#define PBE_BLE_CS_RAM_NSTEPSDONE_VAL_M                                  0xFFFFU
#define PBE_BLE_CS_RAM_NSTEPSDONE_VAL_S                                       0U

//******************************************************************************
// Register: TSTEPACCL
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TSTEPACCL_VAL_W                                       16U
#define PBE_BLE_CS_RAM_TSTEPACCL_VAL_M                                   0xFFFFU
#define PBE_BLE_CS_RAM_TSTEPACCL_VAL_S                                        0U

//******************************************************************************
// Register: TSTEPACCH
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TSTEPACCH_VAL_W                                       16U
#define PBE_BLE_CS_RAM_TSTEPACCH_VAL_M                                   0xFFFFU
#define PBE_BLE_CS_RAM_TSTEPACCH_VAL_S                                        0U

//******************************************************************************
// Register: TSTEPACCTHRL
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TSTEPACCTHRL_VAL_W                                    16U
#define PBE_BLE_CS_RAM_TSTEPACCTHRL_VAL_M                                0xFFFFU
#define PBE_BLE_CS_RAM_TSTEPACCTHRL_VAL_S                                     0U

//******************************************************************************
// Register: TSTEPACCTHRH
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TSTEPACCTHRH_VAL_W                                    16U
#define PBE_BLE_CS_RAM_TSTEPACCTHRH_VAL_M                                0xFFFFU
#define PBE_BLE_CS_RAM_TSTEPACCTHRH_VAL_S                                     0U

//******************************************************************************
// Register: TSTEPCOMP
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TSTEPCOMP_VAL_W                                       16U
#define PBE_BLE_CS_RAM_TSTEPCOMP_VAL_M                                   0xFFFFU
#define PBE_BLE_CS_RAM_TSTEPCOMP_VAL_S                                        0U

//******************************************************************************
// Register: TPOSTPROCESS
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TPOSTPROCESS_VAL_W                                    16U
#define PBE_BLE_CS_RAM_TPOSTPROCESS_VAL_M                                0xFFFFU
#define PBE_BLE_CS_RAM_TPOSTPROCESS_VAL_S                                     0U

//******************************************************************************
// Register: TPOSTPROCESSDIV
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_BLE_CS_RAM_TPOSTPROCESSDIV_VAL_W                                 16U
#define PBE_BLE_CS_RAM_TPOSTPROCESSDIV_VAL_M                             0xFFFFU
#define PBE_BLE_CS_RAM_TPOSTPROCESSDIV_VAL_S                                  0U


#endif // __PBE_BLE_CS_RAM_REGS_H
