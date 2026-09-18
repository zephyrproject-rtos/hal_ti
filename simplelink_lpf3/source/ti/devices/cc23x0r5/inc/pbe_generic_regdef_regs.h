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
 *  ======== pbe_generic_regdef_regs.h ========
*/

#ifndef __PBE_GENERIC_REGDEF_REGS_H
#define __PBE_GENERIC_REGDEF_REGS_H

//******************************************************************************
// REGISTER OFFSETS
//******************************************************************************
// Packet Building Engine (PBE) interrupt generation register
#define PBE_GENERIC_REGDEF_O_IRQ                                     0x00000010U

// PBE API Operation Register
#define PBE_GENERIC_REGDEF_O_API                                     0x00000030U

//******************************************************************************
// Register: IRQ
//******************************************************************************
// Field: [15:15] operror
//
// Software defined interrupt
#define PBE_GENERIC_REGDEF_IRQ_OPERROR                               0x00008000U
#define PBE_GENERIC_REGDEF_IRQ_OPERROR_M                             0x00008000U
#define PBE_GENERIC_REGDEF_IRQ_OPERROR_S                                     15U
#define PBE_GENERIC_REGDEF_IRQ_OPERROR_OFF                           0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_OPERROR_ACTIVE                        0x00008000U

// Field: [14:14] unused14
//
// Software defined interrupt
#define PBE_GENERIC_REGDEF_IRQ_UNUSED14                              0x00004000U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED14_M                            0x00004000U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED14_S                                    14U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED14_OFF                          0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED14_ACTIVE                       0x00004000U

// Field: [13:13] txdone
//
// Packet transmitted. MCU shall deallocate or retry.
#define PBE_GENERIC_REGDEF_IRQ_TXDONE                                0x00002000U
#define PBE_GENERIC_REGDEF_IRQ_TXDONE_M                              0x00002000U
#define PBE_GENERIC_REGDEF_IRQ_TXDONE_S                                      13U
#define PBE_GENERIC_REGDEF_IRQ_TXDONE_OFF                            0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_TXDONE_ACTIVE                         0x00002000U

// Field: [12:12] unused12
//
// Software defined interrupt
#define PBE_GENERIC_REGDEF_IRQ_UNUSED12                              0x00001000U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED12_M                            0x00001000U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED12_S                                    12U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED12_OFF                          0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED12_ACTIVE                       0x00001000U

// Field: [11:11] unused11
//
// Software defined interrupt
#define PBE_GENERIC_REGDEF_IRQ_UNUSED11                              0x00000800U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED11_M                            0x00000800U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED11_S                                    11U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED11_OFF                          0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED11_ACTIVE                       0x00000800U

// Field: [10:10] unused10
//
// Software defined interrupt
#define PBE_GENERIC_REGDEF_IRQ_UNUSED10                              0x00000400U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED10_M                            0x00000400U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED10_S                                    10U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED10_OFF                          0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED10_ACTIVE                       0x00000400U

// Field: [9:9] unused9
//
// Software defined interrupt
#define PBE_GENERIC_REGDEF_IRQ_UNUSED9                               0x00000200U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED9_M                             0x00000200U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED9_S                                      9U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED9_OFF                           0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED9_ACTIVE                        0x00000200U

// Field: [8:8] rxok
//
// Packet received with CRC OK and not to be ignored by the MCU
#define PBE_GENERIC_REGDEF_IRQ_RXOK                                  0x00000100U
#define PBE_GENERIC_REGDEF_IRQ_RXOK_M                                0x00000100U
#define PBE_GENERIC_REGDEF_IRQ_RXOK_S                                         8U
#define PBE_GENERIC_REGDEF_IRQ_RXOK_OFF                              0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_RXOK_ACTIVE                           0x00000100U

// Field: [7:7] rxfovfl
//
// Packet received which did not fit in the RX FIFO and was not to be discarded. 
#define PBE_GENERIC_REGDEF_IRQ_RXFOVFL                               0x00000080U
#define PBE_GENERIC_REGDEF_IRQ_RXFOVFL_M                             0x00000080U
#define PBE_GENERIC_REGDEF_IRQ_RXFOVFL_S                                      7U
#define PBE_GENERIC_REGDEF_IRQ_RXFOVFL_OFF                           0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_RXFOVFL_ACTIVE                        0x00000080U

// Field: [6:6] unused6
//
// Software defined interrupt
#define PBE_GENERIC_REGDEF_IRQ_UNUSED6                               0x00000040U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED6_M                             0x00000040U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED6_S                                      6U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED6_OFF                           0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED6_ACTIVE                        0x00000040U

// Field: [5:5] rxign
//
// Packet received with correct CRC, but may be ignored by MCU
#define PBE_GENERIC_REGDEF_IRQ_RXIGN                                 0x00000020U
#define PBE_GENERIC_REGDEF_IRQ_RXIGN_M                               0x00000020U
#define PBE_GENERIC_REGDEF_IRQ_RXIGN_S                                        5U
#define PBE_GENERIC_REGDEF_IRQ_RXIGN_OFF                             0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_RXIGN_ACTIVE                          0x00000020U

// Field: [4:4] rxnok
//
// Packet received with CRC error, no data may be trusted
#define PBE_GENERIC_REGDEF_IRQ_RXNOK                                 0x00000010U
#define PBE_GENERIC_REGDEF_IRQ_RXNOK_M                               0x00000010U
#define PBE_GENERIC_REGDEF_IRQ_RXNOK_S                                        4U
#define PBE_GENERIC_REGDEF_IRQ_RXNOK_OFF                             0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_RXNOK_ACTIVE                          0x00000010U

// Field: [3:3] unused3
//
// Software defined interrupt
#define PBE_GENERIC_REGDEF_IRQ_UNUSED3                               0x00000008U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED3_M                             0x00000008U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED3_S                                      3U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED3_OFF                           0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED3_ACTIVE                        0x00000008U

// Field: [2:2] unused2
//
// Software defined interrupt
#define PBE_GENERIC_REGDEF_IRQ_UNUSED2                               0x00000004U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED2_M                             0x00000004U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED2_S                                      2U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED2_OFF                           0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_UNUSED2_ACTIVE                        0x00000004U

// Field: [1:1] pingrsp
//
// PBE responds to PBEOP_PING, basic test to see if the battery is connected.
#define PBE_GENERIC_REGDEF_IRQ_PINGRSP                               0x00000002U
#define PBE_GENERIC_REGDEF_IRQ_PINGRSP_M                             0x00000002U
#define PBE_GENERIC_REGDEF_IRQ_PINGRSP_S                                      1U
#define PBE_GENERIC_REGDEF_IRQ_PINGRSP_OFF                           0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_PINGRSP_ACTIVE                        0x00000002U

// Field: [0:0] opdone
//
// The operation commanded on PBEAPI has completed succesfully.
#define PBE_GENERIC_REGDEF_IRQ_OPDONE                                0x00000001U
#define PBE_GENERIC_REGDEF_IRQ_OPDONE_M                              0x00000001U
#define PBE_GENERIC_REGDEF_IRQ_OPDONE_S                                       0U
#define PBE_GENERIC_REGDEF_IRQ_OPDONE_OFF                            0x00000000U
#define PBE_GENERIC_REGDEF_IRQ_OPDONE_ACTIVE                         0x00000001U

//******************************************************************************
// Register: API
//******************************************************************************
// Field: [4:0] op
//
// PBE Operation
#define PBE_GENERIC_REGDEF_API_OP_W                                           5U
#define PBE_GENERIC_REGDEF_API_OP_M                                  0x0000001FU
#define PBE_GENERIC_REGDEF_API_OP_S                                           0U
#define PBE_GENERIC_REGDEF_API_OP_PING                               0x00000000U
#define PBE_GENERIC_REGDEF_API_OP_STOP                               0x00000001U
#define PBE_GENERIC_REGDEF_API_OP_EOPSTOP                            0x00000002U
#define PBE_GENERIC_REGDEF_API_OP_TX                                 0x00000010U
#define PBE_GENERIC_REGDEF_API_OP_RX                                 0x00000011U
#define PBE_GENERIC_REGDEF_API_OP_FS                                 0x00000012U
#define PBE_GENERIC_REGDEF_API_OP_STOPFS                             0x00000013U


#endif // __PBE_GENERIC_REGDEF_REGS_H
