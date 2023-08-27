/******************************************************************************
*  Filename:       hw_lgpt1_h
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

#ifndef __HW_LGPT1_H__
#define __HW_LGPT1_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LGPT1 component
//
//*****************************************************************************
// Description Register.
// Description Extended
// Start Configuration
// Timer Control
// Output Control
// Counter
// Clock Prescaler Configuration
// Prescaler Event
// Channel Input Filter
// Fault
// Park
// Dead Band Delay
// Dead Band Control
// Direct Memory Accsess
// Direct Memory Access
// ADC Trigger
// IO Controller
// Interrupt mask.
// Raw interrupt status.
// Masked interrupt status.
// Interrupt set register.
// Interrupt clear register.
// Interrupt mask set register.
// Interrupt mask clear register.
// Debug control
// Channel 0 Configuration
// Channel 1 Configuration
// Channel 2 Configuration
// Pipeline Target
// Pipeline Channel 0 Capture Compare
// Pipeline Channel 1 Capture Compare
// Pipeline Channel 2 Capture Compare
// Target
// Channel 0 Capture Compare
// Channel 1 Capture Compare
// Channel 2 Capture Compare
// Pipeline Target No Clear
// Pipeline Channel 0 Capture Compare No Clear
// Pipeline Channel 1 Capture Compare No Clear
// Pipeline Channel 2 Capture Compare No Clear
// Target No Clear
// Channel 0 Capture Compare No Clear
// Channel 1 Capture Compare No Clear
// Channel 2 Capture Compare No Clear
#define LGPT1_O_FAULT                                               0x00000024U
#define LGPT1_O_PARK                                                0x00000028U
#define LGPT1_O_DBDLY                                               0x0000002CU
#define LGPT1_O_DBCTL                                               0x00000030U

//*****************************************************************************
//
// Register: LGPT1_O_FAULT
//
//*****************************************************************************
// Field:   [1:0] CTL
//
// Fault control
//
// On active fault input the counter can optionally stop. If the counter stops
// this is done by hardware, software must then restart the timer if wanted.
// The fault input overrides channel 0 IOC input when CTL != DIS.
// This means that channel 0 receives fault as input signal when C0CFG.INPUT =
// IO and CTL != DIS.
//
// CHFILT can be used to avoid glitching on the fault input. Fault is level
// triggered, the polarity is set by the C0CFG.EDGE field. Here  C0CFG.EDGE =
// RISE gives active high and C0CFG.EDGE = FALL gives active low polarity.
//
// Fault is typically used together with PARK to stop the PWM signal to an
// external motor control circuit safely. Configure PARK to ensure predefined
// values of the PWM outputs.
//
// If CTL != DIS the RIS.FAULT interrupt is set immediately when the fault
// input is active while CTL.MODE != DIS.
//
// The three modes of fault is described below:
//
// CTL = IMMEDIATE
// In this mode the counter stops immediately on an active fault input. This is
// done by hardware by setting CTL.MODE = DIS. To start the counter software
// must set CTL.MODE != DIS.
// When the counter has stopped, the input synchronizers and the channel filter
// is not running. This means that if RIS.FAULT is cleared it will not be set
// again while CTL.MODE = DIS.
//
// CTL = ZEROCOND
// In this mode the counter stops when CNTR = 0 after an active fault input. If
// the RIS.FAULT interrupt has been cleared by software before CNTR = 0, and
// the fault input is inactive, the counter will continue as normal.
// When the counter stops on zero, it can be started again by clearing the
// RIS.FAULT interrupt if the fault input is inactive. To change the counter
// mode set CTL.MODE = DIS, clear the RIS.FAULT interrupt, then start timer in
// wanted mode.
//
// CTL = IRQ
// In this mode only the RIS.FAULT flag is set on an active fault input.
// ENUMs:
// IRQ                      Interrupt request. Only set RIS.FAULT on active
//                          fault.
// ZERCOND                  Zero condition. The counter stops when CNTR = 0.
// IMMEDIATE                Immediate reaction. The counter stops immediately
//                          on fault.
// DIS                      Disable. The timer ignores fault.
#define LGPT1_FAULT_CTL_W                                                    2U
#define LGPT1_FAULT_CTL_M                                           0x00000003U
#define LGPT1_FAULT_CTL_S                                                    0U
#define LGPT1_FAULT_CTL_IRQ                                         0x00000003U
#define LGPT1_FAULT_CTL_ZERCOND                                     0x00000002U
#define LGPT1_FAULT_CTL_IMMEDIATE                                   0x00000001U
#define LGPT1_FAULT_CTL_DIS                                         0x00000000U

//*****************************************************************************
//
// Register: LGPT1_O_PARK
//
//*****************************************************************************
// Field:     [7] IOCPS2
//
// IO Complementary Park State 2
//
// Park state for IO Complementary output 2.
// ENUMs:
// HIGH                     Output is set high in park mode.
// LOW                      Output is set low in park mode.
// Field:     [6] IOPS2
//
// IO Park State 2
//
// Park state for IO output 2.
// ENUMs:
// HIGH                     Output is set high in park mode.
// LOW                      Output is set low in park mode.
// Field:     [5] IOCPS1
//
// IO Complementary Park State 1
//
// Park state for IO Complementary output 1.
// ENUMs:
// HIGH                     Output is set high in park mode.
// LOW                      Output is set low in park mode.
// Field:     [4] IOPS1
//
// IO Park State 1
//
// Park state for IO output 1.
// ENUMs:
// HIGH                     Output is set high in park mode.
// LOW                      Output is set low in park mode.
// Field:     [3] IOCPS0
//
// IO Complementary Park State 0
//
// Park state for IO Complementary output 0.
// ENUMs:
// HIGH                     Output is set high in park mode.
// LOW                      Output is set low in park mode.
// Field:     [2] IOPS0
//
// IO Park State 0
//
// Park state for IO output 0.
// ENUMs:
// HIGH                     Output is set high in park mode.
// LOW                      Output is set low in park mode.
// Field:   [1:0] CTL
//
// Park Control.
// ENUMs:
// BOTH                     Enter parkmode on fault or debug.
// DEBUG                    Enter park mode on debug.
// FAULT                    Enter park mode on fault.
// DIS                      Disable park mode.
#define LGPT1_PARK_IOCPS2                                           0x00000080U
#define LGPT1_PARK_IOCPS2_M                                         0x00000080U
#define LGPT1_PARK_IOCPS2_S                                                  7U
#define LGPT1_PARK_IOCPS2_HIGH                                      0x00000080U
#define LGPT1_PARK_IOCPS2_LOW                                       0x00000000U
#define LGPT1_PARK_IOPS2                                            0x00000040U
#define LGPT1_PARK_IOPS2_M                                          0x00000040U
#define LGPT1_PARK_IOPS2_S                                                   6U
#define LGPT1_PARK_IOPS2_HIGH                                       0x00000040U
#define LGPT1_PARK_IOPS2_LOW                                        0x00000000U
#define LGPT1_PARK_IOCPS1                                           0x00000020U
#define LGPT1_PARK_IOCPS1_M                                         0x00000020U
#define LGPT1_PARK_IOCPS1_S                                                  5U
#define LGPT1_PARK_IOCPS1_HIGH                                      0x00000020U
#define LGPT1_PARK_IOCPS1_LOW                                       0x00000000U
#define LGPT1_PARK_IOPS1                                            0x00000010U
#define LGPT1_PARK_IOPS1_M                                          0x00000010U
#define LGPT1_PARK_IOPS1_S                                                   4U
#define LGPT1_PARK_IOPS1_HIGH                                       0x00000010U
#define LGPT1_PARK_IOPS1_LOW                                        0x00000000U
#define LGPT1_PARK_IOCPS0                                           0x00000008U
#define LGPT1_PARK_IOCPS0_M                                         0x00000008U
#define LGPT1_PARK_IOCPS0_S                                                  3U
#define LGPT1_PARK_IOCPS0_HIGH                                      0x00000008U
#define LGPT1_PARK_IOCPS0_LOW                                       0x00000000U
#define LGPT1_PARK_IOPS0                                            0x00000004U
#define LGPT1_PARK_IOPS0_M                                          0x00000004U
#define LGPT1_PARK_IOPS0_S                                                   2U
#define LGPT1_PARK_IOPS0_HIGH                                       0x00000004U
#define LGPT1_PARK_IOPS0_LOW                                        0x00000000U
#define LGPT1_PARK_CTL_W                                                     2U
#define LGPT1_PARK_CTL_M                                            0x00000003U
#define LGPT1_PARK_CTL_S                                                     0U
#define LGPT1_PARK_CTL_BOTH                                         0x00000003U
#define LGPT1_PARK_CTL_DEBUG                                        0x00000002U
#define LGPT1_PARK_CTL_FAULT                                        0x00000001U
#define LGPT1_PARK_CTL_DIS                                          0x00000000U

//*****************************************************************************
//
// Register: LGPT1_O_DBDLY
//
//*****************************************************************************
// Field: [27:16] FALLDLY
//
// Fall delay.
//
// The number of system clock periods inserted between the fall of the dead
// band reference signal and the rise of the inverted output signal.
// Field:  [11:0] RISEDLY
//
// Rise delay.
//
// The number of system clock periods inserted between the rise of the dead
// band reference signal and the rise of the output signal.
#define LGPT1_DBDLY_FALLDLY_W                                               12U
#define LGPT1_DBDLY_FALLDLY_M                                       0x0FFF0000U
#define LGPT1_DBDLY_FALLDLY_S                                               16U
#define LGPT1_DBDLY_RISEDLY_W                                               12U
#define LGPT1_DBDLY_RISEDLY_M                                       0x00000FFFU
#define LGPT1_DBDLY_RISEDLY_S                                                0U

//*****************************************************************************
//
// Register: LGPT1_O_DBCTL
//
//*****************************************************************************
// Field:     [2] IO2
//
// Enable dead band on IO and IO complementary output 2.
// ENUMs:
// EN                       Enable
// DIS                      Disable
// Field:     [1] IO1
//
// Enable dead band on IO and IO complementary output 1.
// ENUMs:
// EN                       Enable
// DIS                      Disable
// Field:     [0] IO0
//
// Enable dead band on IO and IO complementary output 0.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define LGPT1_DBCTL_IO2                                             0x00000004U
#define LGPT1_DBCTL_IO2_M                                           0x00000004U
#define LGPT1_DBCTL_IO2_S                                                    2U
#define LGPT1_DBCTL_IO2_EN                                          0x00000004U
#define LGPT1_DBCTL_IO2_DIS                                         0x00000000U
#define LGPT1_DBCTL_IO1                                             0x00000002U
#define LGPT1_DBCTL_IO1_M                                           0x00000002U
#define LGPT1_DBCTL_IO1_S                                                    1U
#define LGPT1_DBCTL_IO1_EN                                          0x00000002U
#define LGPT1_DBCTL_IO1_DIS                                         0x00000000U
#define LGPT1_DBCTL_IO0                                             0x00000001U
#define LGPT1_DBCTL_IO0_M                                           0x00000001U
#define LGPT1_DBCTL_IO0_S                                                    0U
#define LGPT1_DBCTL_IO0_EN                                          0x00000001U
#define LGPT1_DBCTL_IO0_DIS                                         0x00000000U


#endif // __LGPT1__
