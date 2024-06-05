/******************************************************************************
*  Filename:       hw_lrfds2r_h
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

#ifndef __HW_LRFDS2R_H__
#define __HW_LRFDS2R_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LRFDS2R component
//
//*****************************************************************************
// Sample2RAM Config Register 
#define LRFDS2R_O_CFG                                               0x00000000U

// Sample2RAM Start Address Register 
#define LRFDS2R_O_START                                             0x00000004U

// Sample2RAM Stop Address Register 
#define LRFDS2R_O_STOP                                              0x00000008U

// Sample2RAM Status Register 
#define LRFDS2R_O_STAT                                              0x0000000CU

// Sample2RAM Trigger Register 
#define LRFDS2R_O_TRIG                                              0x00000010U

//*****************************************************************************
//
// Register: LRFDS2R_O_CFG
//
//*****************************************************************************
// Field:     [5] LAST0 
//
// When this bit is enabled, then the S2R will write all zeros, whenever it 
// tries to write the stop address (instead of the regular value) 
// ENUMs: 
// EN                       Writing all zeros to stop address is enabled 
// DIS                      Writing all zeros to stop address is disabled 
#define LRFDS2R_CFG_LAST0                                           0x00000020U
#define LRFDS2R_CFG_LAST0_M                                         0x00000020U
#define LRFDS2R_CFG_LAST0_S                                                  5U
#define LRFDS2R_CFG_LAST0_EN                                        0x00000020U
#define LRFDS2R_CFG_LAST0_DIS                                       0x00000000U

// Field:   [4:3] TRIGMODE 
//
// Trigger mode 
// ENUMs: 
// ONEVENT                  Trigger on event, i.e. fill memory area once, but 
//                          wait for an event from the selected sample 
//                          source. 
// PERIODIC                 Periodic mode, i.e. fill memory area periodically, 
//                          continuing at the start address after reaching 
//                          the stop address, upon a manual trigger. 
// ONESHOT                  One shot mode, i.e. fill memory area once, from 
//                          start to stop address, upon a manual trigger. 
#define LRFDS2R_CFG_TRIGMODE_W                                               2U
#define LRFDS2R_CFG_TRIGMODE_M                                      0x00000018U
#define LRFDS2R_CFG_TRIGMODE_S                                               3U
#define LRFDS2R_CFG_TRIGMODE_ONEVENT                                0x00000010U
#define LRFDS2R_CFG_TRIGMODE_PERIODIC                               0x00000008U
#define LRFDS2R_CFG_TRIGMODE_ONESHOT                                0x00000000U

// Field:   [2:1] SEL 
//
// Select sample source 
// ENUMs: 
// DECSTAGE                 Samples from decode stage mux. The sample source 
//                          is selected in LRFDMDM:DEMDEBUG.DECSTAGEDEBUG 
//                          register. 
// FRONTEND                 Samples from frontend mux. The sample source is 
//                          selected in LRFDMDM:DEMDEBUG.FRONTENDDEBUG 
//                          register. 
// ADCDIG                   Samples from ADCDIG. 
// SYNTH                    Samples from frequency synthesizer's DTST 
//                          interface. 
#define LRFDS2R_CFG_SEL_W                                                    2U
#define LRFDS2R_CFG_SEL_M                                           0x00000006U
#define LRFDS2R_CFG_SEL_S                                                    1U
#define LRFDS2R_CFG_SEL_DECSTAGE                                    0x00000006U
#define LRFDS2R_CFG_SEL_FRONTEND                                    0x00000004U
#define LRFDS2R_CFG_SEL_ADCDIG                                      0x00000002U
#define LRFDS2R_CFG_SEL_SYNTH                                       0x00000000U

// Field:     [0] CTL 
//
// Sample2RAM module enable 
// ENUMs: 
// EN                       Enabled 
// DIS                      Not enabled 
#define LRFDS2R_CFG_CTL                                             0x00000001U
#define LRFDS2R_CFG_CTL_M                                           0x00000001U
#define LRFDS2R_CFG_CTL_S                                                    0U
#define LRFDS2R_CFG_CTL_EN                                          0x00000001U
#define LRFDS2R_CFG_CTL_DIS                                         0x00000000U

//*****************************************************************************
//
// Register: LRFDS2R_O_START
//
//*****************************************************************************
// Field:  [12:0] ADDR 
//
// Memory start address for where to dump the samples. The address is word 
// oriented starting from the start of the MCERAM, then RFERAM, then PBERAM, 
// then S2RRAM and then BUFRAM. Also note that S2R has write priority to the 
// RAMs, so any attempt at simultaneously accessing the RAMs used by S2R while 
// it is running may be unreliable (no arbitration/stall implemented), and 
// should be avoided. 
//
// 0 -> 1023 : MCERAM 
// 1024 -> 2047 : RFERAM 
// 2048 -> 3071 : PBERAM 
// 3072 -> 4095 : S2RRAM 
// 4096 -> 4479 : BUFRAM 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDS2R_START_ADDR_W                                                13U
#define LRFDS2R_START_ADDR_M                                        0x00001FFFU
#define LRFDS2R_START_ADDR_S                                                 0U
#define LRFDS2R_START_ADDR_ALLONES                                  0x00001FFFU
#define LRFDS2R_START_ADDR_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDS2R_O_STOP
//
//*****************************************************************************
// Field:  [12:0] ADDR 
//
// Memory start address for where to dump the samples. The address is word 
// oriented starting from the start of the MCERAM, then RFERAM, then PBERAM, 
// then S2RRAM and then BUFRAM. Also note that S2R has write priority to the 
// RAMs, so any attempt at simultaneously accessing the RAMs used by S2R while 
// it is running may be unreliable (no arbitration/stall implemented), and 
// should be avoided. 
//
// 0 -> 1023 : MCERAM 
// 1024 -> 2047 : RFERAM 
// 2048 -> 3071 : PBERAM 
// 3072 -> 4095 : S2RRAM 
// 4096 -> 4479 : BUFRAM 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDS2R_STOP_ADDR_W                                                 13U
#define LRFDS2R_STOP_ADDR_M                                         0x00001FFFU
#define LRFDS2R_STOP_ADDR_S                                                  0U
#define LRFDS2R_STOP_ADDR_ALLONES                                   0x00001FFFU
#define LRFDS2R_STOP_ADDR_ALLZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDS2R_O_STAT
//
//*****************************************************************************
// Field: [27:16] ADDRCNT 
//
// Current address counter value 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDS2R_STAT_ADDRCNT_W                                              12U
#define LRFDS2R_STAT_ADDRCNT_M                                      0x0FFF0000U
#define LRFDS2R_STAT_ADDRCNT_S                                              16U
#define LRFDS2R_STAT_ADDRCNT_ALLONES                                0x0FFF0000U
#define LRFDS2R_STAT_ADDRCNT_ALLZEROS                               0x00000000U

// Field:     [0] RUNNING 
//
// S2R running status 
// ENUMs: 
// TRUE                     Running 
// FALSE                    Not running 
#define LRFDS2R_STAT_RUNNING                                        0x00000001U
#define LRFDS2R_STAT_RUNNING_M                                      0x00000001U
#define LRFDS2R_STAT_RUNNING_S                                               0U
#define LRFDS2R_STAT_RUNNING_TRUE                                   0x00000001U
#define LRFDS2R_STAT_RUNNING_FALSE                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDS2R_O_TRIG
//
//*****************************************************************************
// Field:     [0] TRIG 
//
// Trigger a new sample capture (or arm it if the trigger mode is trigger on 
// event) 
// ENUMs: 
// ARM                      Trigger capture or arm module 
// NO_EFFECT                No effect 
#define LRFDS2R_TRIG_TRIG                                           0x00000001U
#define LRFDS2R_TRIG_TRIG_M                                         0x00000001U
#define LRFDS2R_TRIG_TRIG_S                                                  0U
#define LRFDS2R_TRIG_TRIG_ARM                                       0x00000001U
#define LRFDS2R_TRIG_TRIG_NO_EFFECT                                 0x00000000U


#endif // __LRFDS2R__
