/******************************************************************************
*  Filename:       hw_i2c_h
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

#ifndef __HW_I2C_H__
#define __HW_I2C_H__

//*****************************************************************************
//
// This section defines the register offsets of
// I2C component
//
//*****************************************************************************
// Target Own Address
#define I2C_O_TOAR                                                  0x00000000U

// Target Control and Status
#define I2C_O_TSTA                                                  0x00000004U

// Target control
#define I2C_O_TCTL                                                  0x00000004U

// Target Data
#define I2C_O_TDR                                                   0x00000008U

// Target Interrupt Mask
#define I2C_O_TIMR                                                  0x0000000CU

// Target Raw Interrupt Status
#define I2C_O_TRIS                                                  0x00000010U

// Target Masked Interrupt Status
#define I2C_O_TMIS                                                  0x00000014U

// Target Interrupt Clear
#define I2C_O_TICR                                                  0x00000018U

// Controller Target Address
#define I2C_O_CTA                                                   0x00000800U

// Controller Control and Status
#define I2C_O_CSTA                                                  0x00000804U

// Controller control
#define I2C_O_CCTL                                                  0x00000804U

// Controller Data
#define I2C_O_CDR                                                   0x00000808U

// Controller Timer Period
#define I2C_O_CTPR                                                  0x0000080CU

// Controller Interrupt Mask
#define I2C_O_CIMR                                                  0x00000810U

// Controller Raw Interrupt Status
#define I2C_O_CRIS                                                  0x00000814U

// Controller Masked Interrupt Status
#define I2C_O_CMIS                                                  0x00000818U

// Controller Interrupt Clear
#define I2C_O_CICR                                                  0x0000081CU

// Controller Configuration
#define I2C_O_CCR                                                   0x00000820U

//*****************************************************************************
//
// Register: I2C_O_TOAR
//
//*****************************************************************************
// Field:   [6:0] OAR
//
// Target own address. This field specifies bits a6 through a0 of the target
// address.
#define I2C_TOAR_OAR_W                                                       7U
#define I2C_TOAR_OAR_M                                              0x0000007FU
#define I2C_TOAR_OAR_S                                                       0U

//*****************************************************************************
//
// Register: I2C_O_TSTA
//
//*****************************************************************************
// Field:     [2] FBR
//
// First byte received.
// This bit is only applicable when the TSTA.RREQ bit is set and is
// automatically cleared when data has been read from the TDR register.
// Note: This bit is not used for target transmit operations.
// ENUMs:
// SET                      The first byte following the target's own address
//                          has been received.
// CLR                      The first byte following the target's own address
//                          has not been received
#define I2C_TSTA_FBR                                                0x00000004U
#define I2C_TSTA_FBR_M                                              0x00000004U
#define I2C_TSTA_FBR_S                                                       2U
#define I2C_TSTA_FBR_SET                                            0x00000004U
#define I2C_TSTA_FBR_CLR                                            0x00000000U

// Field:     [1] TREQ
//
// This field reflects the transmit request status
// ENUMs:
// SET                      The I2C has been addressed as a target transmitter
//                          and is using clock stretching to delay the
//                          controller until data has been written to the
//                          TDR register
// CLR                      No outstanding transmit request
#define I2C_TSTA_TREQ                                               0x00000002U
#define I2C_TSTA_TREQ_M                                             0x00000002U
#define I2C_TSTA_TREQ_S                                                      1U
#define I2C_TSTA_TREQ_SET                                           0x00000002U
#define I2C_TSTA_TREQ_CLR                                           0x00000000U

// Field:     [0] RREQ
//
// This field reflects the receive request status.
// ENUMs:
// SET                      The target has outstanding receive data from the
//                          external controller and is using clock
//                          stretching to delay the controller until data
//                          has been read from the TDR register
// CLR                      No outstanding receive data
#define I2C_TSTA_RREQ                                               0x00000001U
#define I2C_TSTA_RREQ_M                                             0x00000001U
#define I2C_TSTA_RREQ_S                                                      0U
#define I2C_TSTA_RREQ_SET                                           0x00000001U
#define I2C_TSTA_RREQ_CLR                                           0x00000000U

//*****************************************************************************
//
// Register: I2C_O_TCTL
//
//*****************************************************************************
// Field:     [0] DA
//
// This field sets the device active control
// ENUMs:
// EN                       Enable the target operation
// DIS                      Disable the target operation
#define I2C_TCTL_DA                                                 0x00000001U
#define I2C_TCTL_DA_M                                               0x00000001U
#define I2C_TCTL_DA_S                                                        0U
#define I2C_TCTL_DA_EN                                              0x00000001U
#define I2C_TCTL_DA_DIS                                             0x00000000U

//*****************************************************************************
//
// Register: I2C_O_TDR
//
//*****************************************************************************
// Field:   [7:0] DATA
//
// Data for transfer. This field contains the data for transfer during a target
// receive or a transmit operation. When written, the register data is used as
// transmit data. When read, this register returns the last data received. Data
// is stored until next update, either by a system write to the controller for
// transmit or by an external controller to the target for receive.
#define I2C_TDR_DATA_W                                                       8U
#define I2C_TDR_DATA_M                                              0x000000FFU
#define I2C_TDR_DATA_S                                                       0U

//*****************************************************************************
//
// Register: I2C_O_TIMR
//
//*****************************************************************************
// Field:     [2] STOPIM
//
// Stop condition interrupt mask
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define I2C_TIMR_STOPIM                                             0x00000004U
#define I2C_TIMR_STOPIM_M                                           0x00000004U
#define I2C_TIMR_STOPIM_S                                                    2U
#define I2C_TIMR_STOPIM_EN                                          0x00000004U
#define I2C_TIMR_STOPIM_DIS                                         0x00000000U

// Field:     [1] STARTIM
//
// Start condition interrupt mask
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define I2C_TIMR_STARTIM                                            0x00000002U
#define I2C_TIMR_STARTIM_M                                          0x00000002U
#define I2C_TIMR_STARTIM_S                                                   1U
#define I2C_TIMR_STARTIM_EN                                         0x00000002U
#define I2C_TIMR_STARTIM_DIS                                        0x00000000U

// Field:     [0] DATAIM
//
// Data interrupt mask
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define I2C_TIMR_DATAIM                                             0x00000001U
#define I2C_TIMR_DATAIM_M                                           0x00000001U
#define I2C_TIMR_DATAIM_S                                                    0U
#define I2C_TIMR_DATAIM_EN                                          0x00000001U
#define I2C_TIMR_DATAIM_DIS                                         0x00000000U

//*****************************************************************************
//
// Register: I2C_O_TRIS
//
//*****************************************************************************
// Field:     [2] STOPRIS
//
// Stop condition raw interrupt status
// This bit is cleared by writing a 1 to TICR.STOPIC.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define I2C_TRIS_STOPRIS                                            0x00000004U
#define I2C_TRIS_STOPRIS_M                                          0x00000004U
#define I2C_TRIS_STOPRIS_S                                                   2U
#define I2C_TRIS_STOPRIS_SET                                        0x00000004U
#define I2C_TRIS_STOPRIS_CLR                                        0x00000000U

// Field:     [1] STARTRIS
//
// Start condition raw interrupt status
// This bit is cleared by writing a 1 to TICR.STARTIC.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define I2C_TRIS_STARTRIS                                           0x00000002U
#define I2C_TRIS_STARTRIS_M                                         0x00000002U
#define I2C_TRIS_STARTRIS_S                                                  1U
#define I2C_TRIS_STARTRIS_SET                                       0x00000002U
#define I2C_TRIS_STARTRIS_CLR                                       0x00000000U

// Field:     [0] DATARIS
//
// Data raw interrupt status
// This bit is cleared by writing a 1 to TICR.DATAIC.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define I2C_TRIS_DATARIS                                            0x00000001U
#define I2C_TRIS_DATARIS_M                                          0x00000001U
#define I2C_TRIS_DATARIS_S                                                   0U
#define I2C_TRIS_DATARIS_SET                                        0x00000001U
#define I2C_TRIS_DATARIS_CLR                                        0x00000000U

//*****************************************************************************
//
// Register: I2C_O_TMIS
//
//*****************************************************************************
// Field:     [2] STOPMIS
//
// Stop condition masked interrupt status
// This bit is cleared by writing a 1 to TICR.STOPIC.
// ENUMs:
// SET                      Masked interrupt occured
// CLR                      Masked interrupt did not occur
#define I2C_TMIS_STOPMIS                                            0x00000004U
#define I2C_TMIS_STOPMIS_M                                          0x00000004U
#define I2C_TMIS_STOPMIS_S                                                   2U
#define I2C_TMIS_STOPMIS_SET                                        0x00000004U
#define I2C_TMIS_STOPMIS_CLR                                        0x00000000U

// Field:     [1] STARTMIS
//
// Start condition masked interrupt status
// This bit is cleared by writing a 1 to TICR.STARTIC.
// ENUMs:
// SET                      Masked interrput occured
// CLR                      Masked interrupt did not occur
#define I2C_TMIS_STARTMIS                                           0x00000002U
#define I2C_TMIS_STARTMIS_M                                         0x00000002U
#define I2C_TMIS_STARTMIS_S                                                  1U
#define I2C_TMIS_STARTMIS_SET                                       0x00000002U
#define I2C_TMIS_STARTMIS_CLR                                       0x00000000U

// Field:     [0] DATAMIS
//
// Start condition masked interrupt status
// This bit is cleared by writing a 1 to TICR.DATAIC.
// ENUMs:
// SET                      Masked interrupt occured
// CLR                      Masked interrupt did not occur
#define I2C_TMIS_DATAMIS                                            0x00000001U
#define I2C_TMIS_DATAMIS_M                                          0x00000001U
#define I2C_TMIS_DATAMIS_S                                                   0U
#define I2C_TMIS_DATAMIS_SET                                        0x00000001U
#define I2C_TMIS_DATAMIS_CLR                                        0x00000000U

//*****************************************************************************
//
// Register: I2C_O_TICR
//
//*****************************************************************************
// Field:     [2] STOPIC
//
// Stop condition interrupt clear
// ENUMs:
// EN                       Clear interrupt
//                          Writing 1 to this bit
//                          clears TRIS.STOPRIS and TMIS.STOPMIS
// DIS                      No effect
#define I2C_TICR_STOPIC                                             0x00000004U
#define I2C_TICR_STOPIC_M                                           0x00000004U
#define I2C_TICR_STOPIC_S                                                    2U
#define I2C_TICR_STOPIC_EN                                          0x00000004U
#define I2C_TICR_STOPIC_DIS                                         0x00000000U

// Field:     [1] STARTIC
//
// Start condition interrupt clear
// ENUMs:
// EN                       Clear interrupt
//                          Writing 1 to this bit
//                          clears TRIS.STARTRIS and TMIS.STARTMIS
// DIS                      No effect
#define I2C_TICR_STARTIC                                            0x00000002U
#define I2C_TICR_STARTIC_M                                          0x00000002U
#define I2C_TICR_STARTIC_S                                                   1U
#define I2C_TICR_STARTIC_EN                                         0x00000002U
#define I2C_TICR_STARTIC_DIS                                        0x00000000U

// Field:     [0] DATAIC
//
// Data interrupt clear
// ENUMs:
// EN                       Clear interrupt
//                          Writing 1 to this bit
//                          clears TRIS.DATARIS and TMIS.DATAMIS
// DIS                      No effect
#define I2C_TICR_DATAIC                                             0x00000001U
#define I2C_TICR_DATAIC_M                                           0x00000001U
#define I2C_TICR_DATAIC_S                                                    0U
#define I2C_TICR_DATAIC_EN                                          0x00000001U
#define I2C_TICR_DATAIC_DIS                                         0x00000000U

//*****************************************************************************
//
// Register: I2C_O_CTA
//
//*****************************************************************************
// Field:   [7:1] SA
//
// Controller target address
// Defines which target is addressed for the transaction in controller mode
#define I2C_CTA_SA_W                                                         7U
#define I2C_CTA_SA_M                                                0x000000FEU
#define I2C_CTA_SA_S                                                         1U

// Field:     [0] RS
//
// Receive or Send
// This bit-field specifies the next operation with addressed target CTA.SA.
// ENUMs:
// EN                       Receive data from target
// DIS                      Transmit/send data to target
#define I2C_CTA_RS                                                  0x00000001U
#define I2C_CTA_RS_M                                                0x00000001U
#define I2C_CTA_RS_S                                                         0U
#define I2C_CTA_RS_EN                                               0x00000001U
#define I2C_CTA_RS_DIS                                              0x00000000U

//*****************************************************************************
//
// Register: I2C_O_CSTA
//
//*****************************************************************************
// Field:     [6] BUSBSY
//
// Bus busy
// Note:The bit changes based on the CCTRL.START and CCTRL.STOP conditions.
// ENUMs:
// SET                      The bus is busy.
// CLR                      The bus is idle.
#define I2C_CSTA_BUSBSY                                             0x00000040U
#define I2C_CSTA_BUSBSY_M                                           0x00000040U
#define I2C_CSTA_BUSBSY_S                                                    6U
#define I2C_CSTA_BUSBSY_SET                                         0x00000040U
#define I2C_CSTA_BUSBSY_CLR                                         0x00000000U

// Field:     [5] IDLE
//
// This field specifies whether I2C is idle or not
// ENUMs:
// SET                      The controller is idle.
// CLR                      The controller is not idle.
#define I2C_CSTA_IDLE                                               0x00000020U
#define I2C_CSTA_IDLE_M                                             0x00000020U
#define I2C_CSTA_IDLE_S                                                      5U
#define I2C_CSTA_IDLE_SET                                           0x00000020U
#define I2C_CSTA_IDLE_CLR                                           0x00000000U

// Field:     [4] ARBLST
//
// The filed specifies the arbitration status
// ENUMs:
// SET                      The controller lost arbitration.
// CLR                      The controller won arbitration.
#define I2C_CSTA_ARBLST                                             0x00000010U
#define I2C_CSTA_ARBLST_M                                           0x00000010U
#define I2C_CSTA_ARBLST_S                                                    4U
#define I2C_CSTA_ARBLST_SET                                         0x00000010U
#define I2C_CSTA_ARBLST_CLR                                         0x00000000U

// Field:     [3] DATACKN
//
// This field contains Data acknowledge status
// ENUMs:
// SET                      The transmitted data was not acknowledged
// CLR                      The transmitted data was acknowledged
#define I2C_CSTA_DATACKN                                            0x00000008U
#define I2C_CSTA_DATACKN_M                                          0x00000008U
#define I2C_CSTA_DATACKN_S                                                   3U
#define I2C_CSTA_DATACKN_SET                                        0x00000008U
#define I2C_CSTA_DATACKN_CLR                                        0x00000000U

// Field:     [2] ADRACKN
//
// This field reflects the address acknowledge status
// ENUMs:
// SET                      The transmitted address was not acknowledged
// CLR                      The transmitted address was acknowledged
#define I2C_CSTA_ADRACKN                                            0x00000004U
#define I2C_CSTA_ADRACKN_M                                          0x00000004U
#define I2C_CSTA_ADRACKN_S                                                   2U
#define I2C_CSTA_ADRACKN_SET                                        0x00000004U
#define I2C_CSTA_ADRACKN_CLR                                        0x00000000U

// Field:     [1] ERR
//
// This field reflects the error status
// ENUMs:
// SET                      An error occurred with the last operation
// CLR                      No error was detected on the last operation
#define I2C_CSTA_ERR                                                0x00000002U
#define I2C_CSTA_ERR_M                                              0x00000002U
#define I2C_CSTA_ERR_S                                                       1U
#define I2C_CSTA_ERR_SET                                            0x00000002U
#define I2C_CSTA_ERR_CLR                                            0x00000000U

// Field:     [0] BUSY
//
// This field reflects the I2C busy status
// Note: The I2C controller requires four CLKSVT clock cycles to assert the
// BUSY status after I2C controller operation has been initiated through a
// write into CCTL register.
// Hence after programming CCTL register, application is requested to wait for
// four CLKSVT clock cycles before issuing a controller status inquiry through
// a read from CSTA register. Any prior inquiry would result in wrong status
// being reported.
// ENUMs:
// SET                      The controller is busy
// CLR                      The controller is idle
#define I2C_CSTA_BUSY                                               0x00000001U
#define I2C_CSTA_BUSY_M                                             0x00000001U
#define I2C_CSTA_BUSY_S                                                      0U
#define I2C_CSTA_BUSY_SET                                           0x00000001U
#define I2C_CSTA_BUSY_CLR                                           0x00000000U

//*****************************************************************************
//
// Register: I2C_O_CCTL
//
//*****************************************************************************
// Field:     [3] ACK
//
// This field is to enable the data acknowledge.
// Note:This bit-field must be cleared when the I2C bus controller requires no
// further data to be transmitted from the target transmitter.
// ENUMs:
// EN                       The received data byte is acknowledged
//                          automatically by the controller
// DIS                      The received data byte is not acknowledged
//                          automatically by the controller
#define I2C_CCTL_ACK                                                0x00000008U
#define I2C_CCTL_ACK_M                                              0x00000008U
#define I2C_CCTL_ACK_S                                                       3U
#define I2C_CCTL_ACK_EN                                             0x00000008U
#define I2C_CCTL_ACK_DIS                                            0x00000000U

// Field:     [2] STOP
//
// This field is to set stop condition .
// Note: This bit-field determines if the cycle stops at the end of the data
// cycle or continues on to a repeated start condition.
// ENUMs:
// EN                       The controller generates the stop condition
// DIS                      The controller does not generate the stop
//                          condition
#define I2C_CCTL_STOP                                               0x00000004U
#define I2C_CCTL_STOP_M                                             0x00000004U
#define I2C_CCTL_STOP_S                                                      2U
#define I2C_CCTL_STOP_EN                                            0x00000004U
#define I2C_CCTL_STOP_DIS                                           0x00000000U

// Field:     [1] START
//
// This field is to set start or repeated start condition.
// ENUMs:
// EN                       The controller generates the start condition.
// DIS                      The controller does not generate the start
//                          condition
#define I2C_CCTL_START                                              0x00000002U
#define I2C_CCTL_START_M                                            0x00000002U
#define I2C_CCTL_START_S                                                     1U
#define I2C_CCTL_START_EN                                           0x00000002U
#define I2C_CCTL_START_DIS                                          0x00000000U

// Field:     [0] RUN
//
// This field is to set the controller enable.
// ENUMs:
// EN                       The controller is enabled to transmit or receive
//                          data
// DIS                      The controller is disabled.
#define I2C_CCTL_RUN                                                0x00000001U
#define I2C_CCTL_RUN_M                                              0x00000001U
#define I2C_CCTL_RUN_S                                                       0U
#define I2C_CCTL_RUN_EN                                             0x00000001U
#define I2C_CCTL_RUN_DIS                                            0x00000000U

//*****************************************************************************
//
// Register: I2C_O_CDR
//
//*****************************************************************************
// Field:   [7:0] DATA
//
// When Read: Last RX Data is returned
// When Written: Data is transferred during TX transaction
#define I2C_CDR_DATA_W                                                       8U
#define I2C_CDR_DATA_M                                              0x000000FFU
#define I2C_CDR_DATA_S                                                       0U

//*****************************************************************************
//
// Register: I2C_O_CTPR
//
//*****************************************************************************
// Field:     [7] TPR_7
//
// Must be set to 0 to set CTPR.TPR. If set to 1, a write to CTPR.TPR will be
// ignored.
#define I2C_CTPR_TPR_7                                              0x00000080U
#define I2C_CTPR_TPR_7_M                                            0x00000080U
#define I2C_CTPR_TPR_7_S                                                     7U

// Field:   [6:0] TPR
//
// SCL clock period
// This field specifies the period of the SCL clock.
// SCL_PRD = 2*(1+TPR)*(SCL_LP + SCL_HP)*CLK_PRD, where:
// SCL_PRD is the SCL line period (I2C clock).
// TPR is the timer period register value (range of 1 to 127)
// SCL_LP is the SCL low period (fixed at 6).
// SCL_HP is the SCL high period (fixed at 4).
// CLK_PRD is the CLKSVT period in ns.
#define I2C_CTPR_TPR_W                                                       7U
#define I2C_CTPR_TPR_M                                              0x0000007FU
#define I2C_CTPR_TPR_S                                                       0U

//*****************************************************************************
//
// Register: I2C_O_CIMR
//
//*****************************************************************************
// Field:     [0] IM
//
// Interrupt mask
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define I2C_CIMR_IM                                                 0x00000001U
#define I2C_CIMR_IM_M                                               0x00000001U
#define I2C_CIMR_IM_S                                                        0U
#define I2C_CIMR_IM_EN                                              0x00000001U
#define I2C_CIMR_IM_DIS                                             0x00000000U

//*****************************************************************************
//
// Register: I2C_O_CRIS
//
//*****************************************************************************
// Field:     [0] RIS
//
// Raw interrupt status
// This bit is cleared by writing 1 to CICR.IC bit.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define I2C_CRIS_RIS                                                0x00000001U
#define I2C_CRIS_RIS_M                                              0x00000001U
#define I2C_CRIS_RIS_S                                                       0U
#define I2C_CRIS_RIS_SET                                            0x00000001U
#define I2C_CRIS_RIS_CLR                                            0x00000000U

//*****************************************************************************
//
// Register: I2C_O_CMIS
//
//*****************************************************************************
// Field:     [0] MIS
//
// Masked interrupt status
// This bit is cleared by writing 1 to CICR.IC bit.
// ENUMs:
// SET                      Masked interrupt occured
// CLR                      Masked interrupt did not occur
#define I2C_CMIS_MIS                                                0x00000001U
#define I2C_CMIS_MIS_M                                              0x00000001U
#define I2C_CMIS_MIS_S                                                       0U
#define I2C_CMIS_MIS_SET                                            0x00000001U
#define I2C_CMIS_MIS_CLR                                            0x00000000U

//*****************************************************************************
//
// Register: I2C_O_CICR
//
//*****************************************************************************
// Field:     [0] IC
//
// Interrupt clear
// ENUMs:
// EN                       Clear Interrupt
//                          Writing 1 to this bit
//                          clears CRIS.RIS and CMIS.MIS.
// DIS                      No effect
#define I2C_CICR_IC                                                 0x00000001U
#define I2C_CICR_IC_M                                               0x00000001U
#define I2C_CICR_IC_S                                                        0U
#define I2C_CICR_IC_EN                                              0x00000001U
#define I2C_CICR_IC_DIS                                             0x00000000U

//*****************************************************************************
//
// Register: I2C_O_CCR
//
//*****************************************************************************
// Field:     [5] TFE
//
// I2C target function enable
//
// ENUMs:
// EN                       Target mode enabled
// DIS                      Target mode disabled
#define I2C_CCR_TFE                                                 0x00000020U
#define I2C_CCR_TFE_M                                               0x00000020U
#define I2C_CCR_TFE_S                                                        5U
#define I2C_CCR_TFE_EN                                              0x00000020U
#define I2C_CCR_TFE_DIS                                             0x00000000U

// Field:     [4] CFE
//
// I2C controller function enable
// ENUMs:
// EN                       Controller mode enabled
// DIS                      Controller mode disabled
#define I2C_CCR_CFE                                                 0x00000010U
#define I2C_CCR_CFE_M                                               0x00000010U
#define I2C_CCR_CFE_S                                                        4U
#define I2C_CCR_CFE_EN                                              0x00000010U
#define I2C_CCR_CFE_DIS                                             0x00000000U

// Field:     [0] LPBK
//
// I2C loopback
// ENUMs:
// EN                       Test mode (Loopback operation) enabled
// DIS                      Test mode (Loopback operation) disabled
#define I2C_CCR_LPBK                                                0x00000001U
#define I2C_CCR_LPBK_M                                              0x00000001U
#define I2C_CCR_LPBK_S                                                       0U
#define I2C_CCR_LPBK_EN                                             0x00000001U
#define I2C_CCR_LPBK_DIS                                            0x00000000U


#endif // __I2C__
