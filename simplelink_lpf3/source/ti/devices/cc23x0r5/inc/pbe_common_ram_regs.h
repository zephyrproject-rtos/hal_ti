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
 *  ======== pbe_common_ram_regs.h ========
*/

#ifndef __PBE_COMMON_RAM_REGS_H
#define __PBE_COMMON_RAM_REGS_H

//******************************************************************************
// REGISTER OFFSETS
//******************************************************************************
// 
#define PBE_COMMON_RAM_O_CMDPAR0                                     0x00000000U

// 
#define PBE_COMMON_RAM_O_CMDPAR1                                     0x00000002U

// 
#define PBE_COMMON_RAM_O_MSGBOX                                      0x00000004U

// Reason why PBE ended operation.
#define PBE_COMMON_RAM_O_ENDCAUSE                                    0x00000006U

// 
#define PBE_COMMON_RAM_O_FIFOCMDADD                                  0x00000008U

//******************************************************************************
// Register: CMDPAR0
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_COMMON_RAM_CMDPAR0_VAL_W                                         16U
#define PBE_COMMON_RAM_CMDPAR0_VAL_M                                     0xFFFFU
#define PBE_COMMON_RAM_CMDPAR0_VAL_S                                          0U

//******************************************************************************
// Register: CMDPAR1
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_COMMON_RAM_CMDPAR1_VAL_W                                         16U
#define PBE_COMMON_RAM_CMDPAR1_VAL_M                                     0xFFFFU
#define PBE_COMMON_RAM_CMDPAR1_VAL_S                                          0U

//******************************************************************************
// Register: MSGBOX
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_COMMON_RAM_MSGBOX_VAL_W                                          16U
#define PBE_COMMON_RAM_MSGBOX_VAL_M                                      0xFFFFU
#define PBE_COMMON_RAM_MSGBOX_VAL_S                                           0U

//******************************************************************************
// Register: ENDCAUSE
//******************************************************************************
// Field: [7:0] stat
//
// 
#define PBE_COMMON_RAM_ENDCAUSE_STAT_W                                        8U
#define PBE_COMMON_RAM_ENDCAUSE_STAT_M                                   0x00FFU
#define PBE_COMMON_RAM_ENDCAUSE_STAT_S                                        0U
#define PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK                               0x0000U
#define PBE_COMMON_RAM_ENDCAUSE_STAT_RXTIMEOUT                           0x0001U
#define PBE_COMMON_RAM_ENDCAUSE_STAT_NOSYNC                              0x0002U
#define PBE_COMMON_RAM_ENDCAUSE_STAT_RXERR                               0x0003U
#define PBE_COMMON_RAM_ENDCAUSE_STAT_CONNECT                             0x0004U
#define PBE_COMMON_RAM_ENDCAUSE_STAT_MAXNAK                              0x0006U
#define PBE_COMMON_RAM_ENDCAUSE_STAT_SCANRSP                             0x0006U
#define PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP                             0x0007U
#define PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_RXF                             0x00F9U
#define PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_TXF                             0x00FAU
#define PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_SYNTH                           0x00FBU
#define PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_STOP                            0x00FCU
#define PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_PAR                             0x00FDU
#define PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_BADOP                           0x00FEU
#define PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_INTERNAL                        0x00FFU

//******************************************************************************
// Register: FIFOCMDADD
//******************************************************************************
// Field: [15:0] val
//
// 
#define PBE_COMMON_RAM_FIFOCMDADD_VAL_W                                      16U
#define PBE_COMMON_RAM_FIFOCMDADD_VAL_M                                  0xFFFFU
#define PBE_COMMON_RAM_FIFOCMDADD_VAL_S                                       0U


#endif // __PBE_COMMON_RAM_REGS_H
