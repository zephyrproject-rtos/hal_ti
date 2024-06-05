/******************************************************************************
*  Filename:       hw_lrfdtrc_h
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

#ifndef __HW_LRFDTRC_H__
#define __HW_LRFDTRC_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LRFDTRC component
//
//*****************************************************************************
// Tracer Configuration 
#define LRFDTRC_O_CFG                                               0x00000000U

// Channel 1 Command Register 
#define LRFDTRC_O_CH1CMD                                            0x00000004U

// Channel 2 Command Register 
#define LRFDTRC_O_CH2CMD                                            0x00000008U

// Channel 3 Command Register 
#define LRFDTRC_O_CH3CMD                                            0x0000000CU

// Channel 1 Parameter 0/1 Register 
#define LRFDTRC_O_CH1PAR01                                          0x00000014U

// Channel 2 Parameter 0/1 Register 
#define LRFDTRC_O_CH2PAR01                                          0x00000018U

// Channel 3 Parameter 0/1 Register 
#define LRFDTRC_O_CH3PAR01                                          0x0000001CU

// Channel 1 Parameter 2/3 Register 
#define LRFDTRC_O_CH1PAR23                                          0x00000024U

// Channel 2 Parameter 2/3 Register 
#define LRFDTRC_O_CH2PAR23                                          0x00000028U

// Channel 3 Parameter 2/3 Register 
#define LRFDTRC_O_CH3PAR23                                          0x0000002CU

//*****************************************************************************
//
// Register: LRFDTRC_O_CFG
//
//*****************************************************************************
// Field:   [8:7] PRESCAL 
//
// Data rate prescaler for bit clock of the serialized data 
// ENUMs: 
// DIV4                     Divide clock by 4 
// DIV3                     Divide clock by 3 
// DIV2                     Divide clock by 2 
// DIV1                     Divide clock by 1 
#define LRFDTRC_CFG_PRESCAL_W                                                2U
#define LRFDTRC_CFG_PRESCAL_M                                       0x00000180U
#define LRFDTRC_CFG_PRESCAL_S                                                7U
#define LRFDTRC_CFG_PRESCAL_DIV4                                    0x00000180U
#define LRFDTRC_CFG_PRESCAL_DIV3                                    0x00000100U
#define LRFDTRC_CFG_PRESCAL_DIV2                                    0x00000080U
#define LRFDTRC_CFG_PRESCAL_DIV1                                    0x00000000U

// Field:     [6] TSCLR 
//
// Writing  1 to this bit clears the TX timer 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDTRC_CFG_TSCLR                                           0x00000040U
#define LRFDTRC_CFG_TSCLR_M                                         0x00000040U
#define LRFDTRC_CFG_TSCLR_S                                                  6U
#define LRFDTRC_CFG_TSCLR_ONE                                       0x00000040U
#define LRFDTRC_CFG_TSCLR_ZERO                                      0x00000000U

// Field:     [5] TSEN 
//
// Enables the Timestamp 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDTRC_CFG_TSEN                                            0x00000020U
#define LRFDTRC_CFG_TSEN_M                                          0x00000020U
#define LRFDTRC_CFG_TSEN_S                                                   5U
#define LRFDTRC_CFG_TSEN_ON                                         0x00000020U
#define LRFDTRC_CFG_TSEN_OFF                                        0x00000000U

// Field:   [4:3] CH3EN 
//
// Enables CH3 traces 
// ENUMs: 
// TOPSM                    Enabled with MCE, MCO and CCE backdoor access 
//                          access 
// NORM                     Enabled in normal mode. Data from bus slave 
//                          interface. 
// OFF                      Disabled. No tracer transfer due to CH3 events 
#define LRFDTRC_CFG_CH3EN_W                                                  2U
#define LRFDTRC_CFG_CH3EN_M                                         0x00000018U
#define LRFDTRC_CFG_CH3EN_S                                                  3U
#define LRFDTRC_CFG_CH3EN_TOPSM                                     0x00000010U
#define LRFDTRC_CFG_CH3EN_NORM                                      0x00000008U
#define LRFDTRC_CFG_CH3EN_OFF                                       0x00000000U

// Field:   [2:1] CH2EN 
//
// Enables CH2 traces 
// ENUMs: 
// TOPSM                    Enabled with PBE and RFE backdoor access access 
// NORM                     Enabled in normal mode. Data from bus slave 
//                          interface. 
// OFF                      Disabled. No tracer transfer due to CH2 events 
#define LRFDTRC_CFG_CH2EN_W                                                  2U
#define LRFDTRC_CFG_CH2EN_M                                         0x00000006U
#define LRFDTRC_CFG_CH2EN_S                                                  1U
#define LRFDTRC_CFG_CH2EN_TOPSM                                     0x00000004U
#define LRFDTRC_CFG_CH2EN_NORM                                      0x00000002U
#define LRFDTRC_CFG_CH2EN_OFF                                       0x00000000U

// Field:     [0] CH1EN 
//
// Enables CH1 traces 
// ENUMs: 
// NORM                     Enabled in normal mode. Data from bus slave 
//                          interface. 
// OFF                      Disabled. No tracer transfer due to CH1 events 
#define LRFDTRC_CFG_CH1EN                                           0x00000001U
#define LRFDTRC_CFG_CH1EN_M                                         0x00000001U
#define LRFDTRC_CFG_CH1EN_S                                                  0U
#define LRFDTRC_CFG_CH1EN_NORM                                      0x00000001U
#define LRFDTRC_CFG_CH1EN_OFF                                       0x00000000U

//*****************************************************************************
//
// Register: LRFDTRC_O_CH1CMD
//
//*****************************************************************************
// Field:  [15:8] PKTHDR 
//
// Header Byte. Reverts back to 0 when ready to transmit. A Write starts a 
// transmission sequence. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH1CMD_PKTHDR_W                                              8U
#define LRFDTRC_CH1CMD_PKTHDR_M                                     0x0000FF00U
#define LRFDTRC_CH1CMD_PKTHDR_S                                              8U
#define LRFDTRC_CH1CMD_PKTHDR_ALLONES                               0x0000FF00U
#define LRFDTRC_CH1CMD_PKTHDR_ALLZEROS                              0x00000000U

// Field:   [2:0] PARCNT 
//
// Number of parameters to transmit. Reverts back to 0 when ready to transmit. 
// A Write starts a transmission sequence. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH1CMD_PARCNT_W                                              3U
#define LRFDTRC_CH1CMD_PARCNT_M                                     0x00000007U
#define LRFDTRC_CH1CMD_PARCNT_S                                              0U
#define LRFDTRC_CH1CMD_PARCNT_ALLONES                               0x00000007U
#define LRFDTRC_CH1CMD_PARCNT_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDTRC_O_CH2CMD
//
//*****************************************************************************
// Field:  [15:8] PKTHDR 
//
// Header Byte. Reverts back to 0 when ready to transmit. A Write starts a 
// transmission sequence. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH2CMD_PKTHDR_W                                              8U
#define LRFDTRC_CH2CMD_PKTHDR_M                                     0x0000FF00U
#define LRFDTRC_CH2CMD_PKTHDR_S                                              8U
#define LRFDTRC_CH2CMD_PKTHDR_ALLONES                               0x0000FF00U
#define LRFDTRC_CH2CMD_PKTHDR_ALLZEROS                              0x00000000U

// Field:   [2:0] PARCNT 
//
// Number of parameters to transmit. Reverts back to 0 when ready to transmit. 
// A Write starts a transmission sequence. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH2CMD_PARCNT_W                                              3U
#define LRFDTRC_CH2CMD_PARCNT_M                                     0x00000007U
#define LRFDTRC_CH2CMD_PARCNT_S                                              0U
#define LRFDTRC_CH2CMD_PARCNT_ALLONES                               0x00000007U
#define LRFDTRC_CH2CMD_PARCNT_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDTRC_O_CH3CMD
//
//*****************************************************************************
// Field:  [15:8] PKTHDR 
//
// Header Byte. Reverts back to 0 when ready to transmit. A Write starts a 
// transmission sequence. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH3CMD_PKTHDR_W                                              8U
#define LRFDTRC_CH3CMD_PKTHDR_M                                     0x0000FF00U
#define LRFDTRC_CH3CMD_PKTHDR_S                                              8U
#define LRFDTRC_CH3CMD_PKTHDR_ALLONES                               0x0000FF00U
#define LRFDTRC_CH3CMD_PKTHDR_ALLZEROS                              0x00000000U

// Field:   [2:0] PARCNT 
//
// Number of parameters to transmit. Reverts back to 0 when ready to transmit. 
// A Write starts a transmission sequence. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH3CMD_PARCNT_W                                              3U
#define LRFDTRC_CH3CMD_PARCNT_M                                     0x00000007U
#define LRFDTRC_CH3CMD_PARCNT_S                                              0U
#define LRFDTRC_CH3CMD_PARCNT_ALLONES                               0x00000007U
#define LRFDTRC_CH3CMD_PARCNT_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDTRC_O_CH1PAR01
//
//*****************************************************************************
// Field: [31:16] PAR1 
//
// Parameter 1 for Channel 1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH1PAR01_PAR1_W                                             16U
#define LRFDTRC_CH1PAR01_PAR1_M                                     0xFFFF0000U
#define LRFDTRC_CH1PAR01_PAR1_S                                             16U
#define LRFDTRC_CH1PAR01_PAR1_ALLONES                               0xFFFF0000U
#define LRFDTRC_CH1PAR01_PAR1_ALLZEROS                              0x00000000U

// Field:  [15:0] PAR0 
//
// Parameter 0 for Channel 1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH1PAR01_PAR0_W                                             16U
#define LRFDTRC_CH1PAR01_PAR0_M                                     0x0000FFFFU
#define LRFDTRC_CH1PAR01_PAR0_S                                              0U
#define LRFDTRC_CH1PAR01_PAR0_ALLONES                               0x0000FFFFU
#define LRFDTRC_CH1PAR01_PAR0_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDTRC_O_CH2PAR01
//
//*****************************************************************************
// Field: [31:16] PAR1 
//
// Parameter 1 for Channel 2 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH2PAR01_PAR1_W                                             16U
#define LRFDTRC_CH2PAR01_PAR1_M                                     0xFFFF0000U
#define LRFDTRC_CH2PAR01_PAR1_S                                             16U
#define LRFDTRC_CH2PAR01_PAR1_ALLONES                               0xFFFF0000U
#define LRFDTRC_CH2PAR01_PAR1_ALLZEROS                              0x00000000U

// Field:  [15:0] PAR0 
//
// Parameter 0 for Channel 2 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH2PAR01_PAR0_W                                             16U
#define LRFDTRC_CH2PAR01_PAR0_M                                     0x0000FFFFU
#define LRFDTRC_CH2PAR01_PAR0_S                                              0U
#define LRFDTRC_CH2PAR01_PAR0_ALLONES                               0x0000FFFFU
#define LRFDTRC_CH2PAR01_PAR0_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDTRC_O_CH3PAR01
//
//*****************************************************************************
// Field: [31:16] PAR1 
//
// Parameter 1 for Channel 3 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH3PAR01_PAR1_W                                             16U
#define LRFDTRC_CH3PAR01_PAR1_M                                     0xFFFF0000U
#define LRFDTRC_CH3PAR01_PAR1_S                                             16U
#define LRFDTRC_CH3PAR01_PAR1_ALLONES                               0xFFFF0000U
#define LRFDTRC_CH3PAR01_PAR1_ALLZEROS                              0x00000000U

// Field:  [15:0] PAR0 
//
// Parameter 0 for Channel 3 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH3PAR01_PAR0_W                                             16U
#define LRFDTRC_CH3PAR01_PAR0_M                                     0x0000FFFFU
#define LRFDTRC_CH3PAR01_PAR0_S                                              0U
#define LRFDTRC_CH3PAR01_PAR0_ALLONES                               0x0000FFFFU
#define LRFDTRC_CH3PAR01_PAR0_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDTRC_O_CH1PAR23
//
//*****************************************************************************
// Field: [31:16] PAR3 
//
// Parameter 3 for Channel 1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH1PAR23_PAR3_W                                             16U
#define LRFDTRC_CH1PAR23_PAR3_M                                     0xFFFF0000U
#define LRFDTRC_CH1PAR23_PAR3_S                                             16U
#define LRFDTRC_CH1PAR23_PAR3_ALLONES                               0xFFFF0000U
#define LRFDTRC_CH1PAR23_PAR3_ALLZEROS                              0x00000000U

// Field:  [15:0] PAR2 
//
// Parameter 2 for Channel 1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH1PAR23_PAR2_W                                             16U
#define LRFDTRC_CH1PAR23_PAR2_M                                     0x0000FFFFU
#define LRFDTRC_CH1PAR23_PAR2_S                                              0U
#define LRFDTRC_CH1PAR23_PAR2_ALLONES                               0x0000FFFFU
#define LRFDTRC_CH1PAR23_PAR2_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDTRC_O_CH2PAR23
//
//*****************************************************************************
// Field: [31:16] PAR3 
//
// Parameter 3 for Channel 2 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH2PAR23_PAR3_W                                             16U
#define LRFDTRC_CH2PAR23_PAR3_M                                     0xFFFF0000U
#define LRFDTRC_CH2PAR23_PAR3_S                                             16U
#define LRFDTRC_CH2PAR23_PAR3_ALLONES                               0xFFFF0000U
#define LRFDTRC_CH2PAR23_PAR3_ALLZEROS                              0x00000000U

// Field:  [15:0] PAR2 
//
// Parameter 2 for Channel 2 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH2PAR23_PAR2_W                                             16U
#define LRFDTRC_CH2PAR23_PAR2_M                                     0x0000FFFFU
#define LRFDTRC_CH2PAR23_PAR2_S                                              0U
#define LRFDTRC_CH2PAR23_PAR2_ALLONES                               0x0000FFFFU
#define LRFDTRC_CH2PAR23_PAR2_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDTRC_O_CH3PAR23
//
//*****************************************************************************
// Field: [31:16] PAR3 
//
// Parameter 3 for Channel 3 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH3PAR23_PAR3_W                                             16U
#define LRFDTRC_CH3PAR23_PAR3_M                                     0xFFFF0000U
#define LRFDTRC_CH3PAR23_PAR3_S                                             16U
#define LRFDTRC_CH3PAR23_PAR3_ALLONES                               0xFFFF0000U
#define LRFDTRC_CH3PAR23_PAR3_ALLZEROS                              0x00000000U

// Field:  [15:0] PAR2 
//
// Parameter 2 for Channel 3 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDTRC_CH3PAR23_PAR2_W                                             16U
#define LRFDTRC_CH3PAR23_PAR2_M                                     0x0000FFFFU
#define LRFDTRC_CH3PAR23_PAR2_S                                              0U
#define LRFDTRC_CH3PAR23_PAR2_ALLONES                               0x0000FFFFU
#define LRFDTRC_CH3PAR23_PAR2_ALLZEROS                              0x00000000U


#endif // __LRFDTRC__
