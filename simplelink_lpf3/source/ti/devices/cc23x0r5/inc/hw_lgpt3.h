/******************************************************************************
*  Filename:       hw_lgpt3_h
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

#ifndef __HW_LGPT3_H__
#define __HW_LGPT3_H__

//*****************************************************************************
//
// Register: LGPT3_O_CNTR
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Current counter value.
// If CTL.MODE = QDEC this can be used to set the initial counter value during
// QDEC.  Writing to CNTR in other modes than QDEC is possible, but may result
// in unpredictable behavior.
#define LGPT3_CNTR_VAL_W                                                    24U
#define LGPT3_CNTR_VAL_M                                            0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_DMARW
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// DMA read write value.
//
// The value that is read/written from/to the registers.
#define LGPT3_DMARW_VAL_W                                                   24U
#define LGPT3_DMARW_VAL_M                                           0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_PTGT
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// The pipleline target value.
#define LGPT3_PTGT_VAL_W                                                    24U
#define LGPT3_PTGT_VAL_M                                            0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_PC0CC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Pipeline Capture Compare value.
//
// User defined pipeline compare value or channel-updated capture value.
//
// A read or write to this register will clear the RIS.C0CC interrupt.
//
// Compare mode:
// An update of VAL will be transferred to C0CC.VAL when the next CNTR.VAL is
// zero and CTL.MODE is different from DIS. This is useful for PWM generation
// and prevents jitter on the edges of the generated signal.
//
// Capture mode:
// When C0CFG.CCACT equals PER_PULSE_WIDTH_MEAS then VAL contains the width of
// the low or high phase of the selected signal. This is specified by
// C0CFG.EDGE.
#define LGPT3_PC0CC_VAL_W                                                   24U
#define LGPT3_PC0CC_VAL_M                                           0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_PC1CC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Pipeline Capture Compare value.
//
// User defined pipeline compare value or channel-updated capture value.
//
// A read or write to this register will clear the RIS.C1CC interrupt.
//
// Compare mode:
// An update of VAL will be transferred to C1CC.VAL when the next CNTR.VAL is
// zero and CTL.MODE is different from DIS. This is useful for PWM generation
// and prevents jitter on the edges of the generated signal.
//
// Capture mode:
// When C1CFG.CCACT equals PER_PULSE_WIDTH_MEAS then VAL contains the width of
// the low or high phase of the selected signal. This is specified by
// C1CFG.EDGE.
#define LGPT3_PC1CC_VAL_W                                                   24U
#define LGPT3_PC1CC_VAL_M                                           0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_PC2CC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Pipeline Capture Compare value.
//
// User defined pipeline compare value or channel-updated capture value.
//
// A read or write to this register will clear the RIS.C2CC interrupt.
//
// Compare mode:
// An update of VAL will be transferred to C2CC.VAL when the next CNTR.VAL is
// zero and CTL.MODE is different from DIS. This is useful for PWM generation
// and prevents jitter on the edges of the generated signal.
//
// Capture mode:
// When C2CFG.CCACT equals PER_PULSE_WIDTH_MEAS then VAL contains the width of
// the low or high phase of the selected signal. This is specified by
// C2CFG.EDGE.
#define LGPT3_PC2CC_VAL_W                                                   24U
#define LGPT3_PC2CC_VAL_M                                           0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_TGT
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// User defined counter target value.
#define LGPT3_TGT_VAL_W                                                     24U
#define LGPT3_TGT_VAL_M                                             0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_C0CC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Capture Compare value.
//
// User defined compare value or channel-updated capture value.
//
// A read or write to this register will clear the RIS.C0CC interrupt.
//
// Compare mode:
// VAL is compared against CNTR.VAL and an event is generated as specified by
// C0CFG.CCACT when these are equal.
//
// Capture mode:
// The current counter value is stored in VAL when a capture event occurs.
// C0CFG.CCACT determines if VAL is a signal period or a regular capture value.
#define LGPT3_C0CC_VAL_W                                                    24U
#define LGPT3_C0CC_VAL_M                                            0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_C1CC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Capture Compare value.
//
// User defined compare value or channel-updated capture value.
//
// A read or write to this register will clear the RIS.C1CC interrupt.
//
// Compare mode:
// VAL is compared against CNTR.VAL and an event is generated as specified by
// C1CFG.CCACT when these are equal.
//
// Capture mode:
// The current counter value is stored in VAL when a capture event occurs.
// C1CFG.CCACT determines if VAL is a signal period or a regular capture value.
#define LGPT3_C1CC_VAL_W                                                    24U
#define LGPT3_C1CC_VAL_M                                            0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_C2CC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Capture Compare value.
//
// User defined compare value or channel-updated capture value.
//
// A read or write to this register will clear the RIS.C2CC interrupt.
//
// Compare mode:
// VAL is compared against CNTR.VAL and an event is generated as specified by
// C2CFG.CCACT when these are equal.
//
// Capture mode:
// The current counter value is stored in VAL when a capture event occurs.
// C2CFG.CCACT determines if VAL is a signal period or a regular capture value.
#define LGPT3_C2CC_VAL_W                                                    24U
#define LGPT3_C2CC_VAL_M                                            0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_PTGTNC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// A read or write to this register will not clear the RIS.TGT interrupt.
//
// If CTL.MODE != QDEC.
// Target value for next counter period.
// The timer copies VAL to TGT.VAL when CNTR.VAL becomes 0. The copy does not
// happen when restarting the timer.
// This is useful to avoid period jitter in PWM applications with time-varying
// period, sometimes referenced as phase corrected PWM.
//
// If CTL.MODE = QDEC.
// The CNTR.VAL is updated with VAL on IDX. VAL is not loaded into TGT.VAL when
// CNTR.VAL becomes 0.
#define LGPT3_PTGTNC_VAL_W                                                  24U
#define LGPT3_PTGTNC_VAL_M                                          0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_PC0CCNC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Pipeline Capture Compare value.
//
// User defined pipeline compare value or channel-updated capture value.
//
// A read or write to this register will not clear the RIS.C0CC interrupt.
//
// Compare mode:
// An update of VAL will be transferred to C0CC.VAL when the next CNTR.VAL is
// zero and CTL.MODE is different from DIS. This is useful for PWM generation
// and prevents jitter on the edges of the generated signal.
//
// Capture mode:
// When C0CFG.CCACT equals PER_PULSE_WIDTH_MEAS then VAL contains the width of
// the low or high phase of the selected signal. This is specified by
// C0CFG.EDGE.
#define LGPT3_PC0CCNC_VAL_W                                                 24U
#define LGPT3_PC0CCNC_VAL_M                                         0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_PC1CCNC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Pipeline Capture Compare value.
//
// User defined pipeline compare value or channel-updated capture value.
//
// A read or write to this register will not clear the RIS.C1CC interrupt.
//
// Compare mode:
// An update of VAL will be transferred to C1CC.VAL when the next CNTR.VAL is
// zero and CTL.MODE is different from DIS. This is useful for PWM generation
// and prevents jitter on the edges of the generated signal.
//
// Capture mode:
// When C1CFG.CCACT equals PER_PULSE_WIDTH_MEAS then VAL contains the width of
// the low or high phase of the selected signal. This is specified by
// C1CFG.EDGE.
#define LGPT3_PC1CCNC_VAL_W                                                 24U
#define LGPT3_PC1CCNC_VAL_M                                         0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_PC2CCNC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Pipeline Capture Compare value.
//
// User defined pipeline compare value or channel-updated capture value.
//
// A read or write to this register will not clear the RIS.C2CC interrupt.
//
// Compare mode:
// An update of VAL will be transferred to C2CC.VAL when the next CNTR.VAL is
// zero and CTL.MODE is different from DIS. This is useful for PWM generation
// and prevents jitter on the edges of the generated signal.
//
// Capture mode:
// When C2CFG.CCACT equals PER_PULSE_WIDTH_MEAS then VAL contains the width of
// the low or high phase of the selected signal. This is specified by
// C2CFG.EDGE.
#define LGPT3_PC2CCNC_VAL_W                                                 24U
#define LGPT3_PC2CCNC_VAL_M                                         0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_TGTNC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// User defined counter target value.
#define LGPT3_TGTNC_VAL_W                                                   24U
#define LGPT3_TGTNC_VAL_M                                           0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_C0CCNC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Capture Compare value.
//
// User defined compare value or channel-updated capture value.
//
// A read or write to this register will not clear the RIS.C0CC interrupt.
//
// Compare mode:
// VAL is compared against CNTR.VAL and an event is generated as specified by
// C0CFG.CCACT when these are equal.
//
// Capture mode:
// The current counter value is stored in VAL when a capture event occurs.
// C0CFG.CCACT determines if VAL is a signal period or a regular capture value.
#define LGPT3_C0CCNC_VAL_W                                                  24U
#define LGPT3_C0CCNC_VAL_M                                          0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_C1CCNC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Capture Compare value.
//
// User defined compare value or channel-updated capture value.
//
// A read or write to this register will not clear the RIS.C1CC interrupt.
//
// Compare mode:
// VAL is compared against CNTR.VAL and an event is generated as specified by
// C1CFG.CCACT when these are equal.
//
// Capture mode:
// The current counter value is stored in VAL when a capture event occurs.
// C1CFG.CCACT determines if VAL is a signal period or a regular capture value.
#define LGPT3_C1CCNC_VAL_W                                                  24U
#define LGPT3_C1CCNC_VAL_M                                          0x00FFFFFFU

//*****************************************************************************
//
// Register: LGPT3_O_C2CCNC
//
//*****************************************************************************
// Field:  [23:0] VAL
//
// Capture Compare value.
//
// User defined compare value or channel-updated capture value.
//
// A read or write to this register will not clear the RIS.C2CC interrupt.
//
// Compare mode:
// VAL is compared against CNTR.VAL and an event is generated as specified by
// C2CFG.CCACT when these are equal.
//
// Capture mode:
// The current counter value is stored in VAL when a capture event occurs.
// C2CFG.CCACT determines if VAL is a signal period or a regular capture value.
#define LGPT3_C2CCNC_VAL_W                                                  24U
#define LGPT3_C2CCNC_VAL_M                                          0x00FFFFFFU


#endif // __LGPT3__
