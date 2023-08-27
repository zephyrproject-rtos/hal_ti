/******************************************************************************
*  Filename:       hw_dma_h
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

#ifndef __HW_DMA_H__
#define __HW_DMA_H__

//*****************************************************************************
//
// This section defines the register offsets of
// DMA component
//
//*****************************************************************************
// Status Register.
#define DMA_O_STATUS                                                0x00000000U

// Configuration Register.
#define DMA_O_CFG                                                   0x00000004U

// Channel Control Data Base Pointer Register.
#define DMA_O_CTRL                                                  0x00000008U

// Channel Alternate Control Data Base Pointer Register.
#define DMA_O_ALTCTRL                                               0x0000000CU

// Channel Wait On Request Status Register.
#define DMA_O_WAITONREQ                                             0x00000010U

// Channel Software Request Register.
#define DMA_O_SOFTREQ                                               0x00000014U

// Channel Set UseBurst Register.
#define DMA_O_SETBURST                                              0x00000018U

// Channel Clear UseBurst Register.
#define DMA_O_CLEARBURST                                            0x0000001CU

// Channel Set Request Mask Register.
#define DMA_O_SETREQMASK                                            0x00000020U

// Clear Channel Request Mask Register.
#define DMA_O_CLEARREQMASK                                          0x00000024U

// Set Channel Enable Register.
#define DMA_O_SETCHANNELEN                                          0x00000028U

// Clear Channel Enable Register.
#define DMA_O_CLEARCHANNELEN                                        0x0000002CU

// Channel Set Primary-Alternate Register.
#define DMA_O_SETCHNLPRIALT                                         0x00000030U

// Channel Clear Primary-Alternate Register.
#define DMA_O_CLEARCHNLPRIALT                                       0x00000034U

// Set Channel Priority Register.
#define DMA_O_SETCHNLPRIORITY                                       0x00000038U

// Clear Channel Priority Register.
#define DMA_O_CLEARCHNLPRIORITY                                     0x0000003CU

// Error Status and Clear Register.
#define DMA_O_ERROR                                                 0x0000004CU

// Channel Request Done Register.
#define DMA_O_REQDONE                                               0x00000504U

// Channel Request Done Mask Register.
#define DMA_O_DONEMASK                                              0x00000520U

//*****************************************************************************
//
// Register: DMA_O_STATUS
//
//*****************************************************************************
// Field: [31:28] TEST
//
//
// 0x0: Controller does not include the integration test logic
// 0x1: Controller includes the integration test logic
// 0x2: Undefined
// ...
// 0xF: Undefined
#define DMA_STATUS_TEST_W                                                    4U
#define DMA_STATUS_TEST_M                                           0xF0000000U
#define DMA_STATUS_TEST_S                                                   28U

// Field: [20:16] TOTALCHANNELS
//
// Register value returns number of available uDMA channels minus one. For
// example a read out value of:
//
// 0x00: Show that the controller is configured to use 1 uDMA channel
// 0x01: Shows that the controller is configured to use 2 uDMA channels
// ...
// 0x1F: Shows that the controller is configured to use 32 uDMA channels
// (32-1=31=0x1F)
#define DMA_STATUS_TOTALCHANNELS_W                                           5U
#define DMA_STATUS_TOTALCHANNELS_M                                  0x001F0000U
#define DMA_STATUS_TOTALCHANNELS_S                                          16U

// Field:   [7:4] STATE
//
// Current state of the control state machine. State can be one of the
// following:
//
// 0x0: Idle
// 0x1: Reading channel controller data
// 0x2: Reading source data end pointer
// 0x3: Reading destination data end pointer
// 0x4: Reading source data
// 0x5: Writing destination data
// 0x6: Waiting for uDMA request to clear
// 0x7: Writing channel controller data
// 0x8: Stalled
// 0x9: Done
// 0xA: Peripheral scatter-gather transition
// 0xB: Undefined
// ...
// 0xF: Undefined.
#define DMA_STATUS_STATE_W                                                   4U
#define DMA_STATUS_STATE_M                                          0x000000F0U
#define DMA_STATUS_STATE_S                                                   4U

// Field:     [0] MASTERENABLE
//
// Shows the enable status of the controller as configured by CFG.MASTERENABLE:
// ENUMs:
// EN                       Controller is enabled
// DIS                      Controller is disabled
#define DMA_STATUS_MASTERENABLE                                     0x00000001U
#define DMA_STATUS_MASTERENABLE_M                                   0x00000001U
#define DMA_STATUS_MASTERENABLE_S                                            0U
#define DMA_STATUS_MASTERENABLE_EN                                  0x00000001U
#define DMA_STATUS_MASTERENABLE_DIS                                 0x00000000U

//*****************************************************************************
//
// Register: DMA_O_CFG
//
//*****************************************************************************
// Field:   [7:5] PRTOCTRL
//
// Sets the AHB-Lite bus protocol protection state by controlling the AHB
// signal HProt[3:1] as follows:
//
// Bit [7] Controls HProt[3] to indicate if a cacheable access is occurring.
// Bit [6] Controls HProt[2] to indicate if a bufferable access is occurring.
// Bit [5] Controls HProt[1] to indicate if a privileged access is occurring.
//
// When bit [n] = 1 then the corresponding HProt bit is high.
// When bit [n] = 0 then the corresponding HProt bit is low.
//
// This field controls HProt[3:1] signal for all transactions initiated by uDMA
// except two transactions below:
// - the read from the address indicated by source address pointer
// - the write to the address indicated by destination address pointer
// HProt[3:1] for these two exceptions can be controlled by dedicated fields in
// the channel configutation descriptor.
#define DMA_CFG_PRTOCTRL_W                                                   3U
#define DMA_CFG_PRTOCTRL_M                                          0x000000E0U
#define DMA_CFG_PRTOCTRL_S                                                   5U

// Field:     [0] MASTERENABLE
//
// Enables the controller.
// ENUMs:
// EN                       Enables the controller
// DIS                      Disables the controller
#define DMA_CFG_MASTERENABLE                                        0x00000001U
#define DMA_CFG_MASTERENABLE_M                                      0x00000001U
#define DMA_CFG_MASTERENABLE_S                                               0U
#define DMA_CFG_MASTERENABLE_EN                                     0x00000001U
#define DMA_CFG_MASTERENABLE_DIS                                    0x00000000U

//*****************************************************************************
//
// Register: DMA_O_CTRL
//
//*****************************************************************************
// Field:  [31:8] BASEPTR
//
// This register point to the base address for the primary data structures of
// each uDMA channel. This is not stored in module, but in system memory, thus
// space must be allocated for this usage when uDMA is in usage
#define DMA_CTRL_BASEPTR_W                                                  24U
#define DMA_CTRL_BASEPTR_M                                          0xFFFFFF00U
#define DMA_CTRL_BASEPTR_S                                                   8U

//*****************************************************************************
//
// Register: DMA_O_ALTCTRL
//
//*****************************************************************************
// Field:  [31:0] BASEPTR
//
// This register shows the base address for the alternate data structures and
// is calculated by module, thus read only
#define DMA_ALTCTRL_BASEPTR_W                                               32U
#define DMA_ALTCTRL_BASEPTR_M                                       0xFFFFFFFFU
#define DMA_ALTCTRL_BASEPTR_S                                                0U

//*****************************************************************************
//
// Register: DMA_O_WAITONREQ
//
//*****************************************************************************
// Field:   [7:0] CHNLSTATUS
//
// Channel wait on request status:
//
// Bit [Ch] = 0: Once uDMA receives a single or burst request on channel Ch,
// this channel may come out of active state even if request is still present.
// Bit [Ch] = 1: Once uDMA receives a single or burst request on channel Ch, it
// keeps channel Ch in active state until the requests are deasserted. This
// handshake is necessary for channels where the requester is in an
// asynchronous domain or can run at slower clock speed than uDMA
#define DMA_WAITONREQ_CHNLSTATUS_W                                           8U
#define DMA_WAITONREQ_CHNLSTATUS_M                                  0x000000FFU
#define DMA_WAITONREQ_CHNLSTATUS_S                                           0U

//*****************************************************************************
//
// Register: DMA_O_SOFTREQ
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Set the appropriate bit to generate a software uDMA request on the
// corresponding uDMA channel
//
// Bit [Ch] = 0: Does not create a uDMA request for channel Ch
// Bit [Ch] = 1: Creates a uDMA request for channel Ch
//
// Writing to a bit where a uDMA channel is not implemented does not create a
// uDMA request for that channel
#define DMA_SOFTREQ_CHNLS_W                                                  8U
#define DMA_SOFTREQ_CHNLS_M                                         0x000000FFU
#define DMA_SOFTREQ_CHNLS_S                                                  0U

//*****************************************************************************
//
// Register: DMA_O_SETBURST
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Returns the useburst status, or disables individual channels from generating
// single uDMA requests. The value R is the arbitration rate and stored in the
// controller data structure.
//
// Read as:
//
// Bit [Ch] = 0: uDMA channel Ch responds to both burst and single requests on
// channel Ch. The controller performs 2^R, or single, bus transfers.
//
// Bit [Ch] = 1: uDMA channel Ch does not respond to single transfer requests.
// The controller only responds to burst transfer requests and performs 2^R
// transfers.
//
// Write as:
// Bit [Ch] = 0: No effect. Use the CLEARBURST.CHNLS to set bit [Ch] to 0.
// Bit [Ch] = 1: Disables single transfer requests on channel Ch. The
// controller performs 2^R transfers for burst requests.
//
// Writing to a bit where a uDMA channel is not implemented has no effect
#define DMA_SETBURST_CHNLS_W                                                 8U
#define DMA_SETBURST_CHNLS_M                                        0x000000FFU
#define DMA_SETBURST_CHNLS_S                                                 0U

//*****************************************************************************
//
// Register: DMA_O_CLEARBURST
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Set the appropriate bit to enable single transfer requests.
//
// Write as:
//
// Bit [Ch] = 0: No effect. Use the SETBURST.CHNLS to disable single transfer
// requests.
//
// Bit [Ch] = 1: Enables single transfer requests on channel Ch.
//
// Writing to a bit where a uDMA channel is not implemented has no effect.
#define DMA_CLEARBURST_CHNLS_W                                               8U
#define DMA_CLEARBURST_CHNLS_M                                      0x000000FFU
#define DMA_CLEARBURST_CHNLS_S                                               0U

//*****************************************************************************
//
// Register: DMA_O_SETREQMASK
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Returns the burst and single request mask status, or disables the
// corresponding channel from generating uDMA requests.
//
// Read as:
// Bit [Ch] = 0: External requests are enabled for channel Ch.
// Bit [Ch] = 1: External requests are disabled for channel Ch.
//
// Write as:
// Bit [Ch] = 0: No effect. Use the CLEARREQMASK.CHNLS to enable uDMA requests.
// Bit [Ch] = 1: Disables uDMA burst request channel [Ch] and uDMA single
// request channel [Ch] input from generating uDMA requests.
//
// Writing to a bit where a uDMA channel is not implemented has no effect
#define DMA_SETREQMASK_CHNLS_W                                               8U
#define DMA_SETREQMASK_CHNLS_M                                      0x000000FFU
#define DMA_SETREQMASK_CHNLS_S                                               0U

//*****************************************************************************
//
// Register: DMA_O_CLEARREQMASK
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Set the appropriate bit to enable uDMA request for the channel.
//
// Write as:
// Bit [Ch] = 0: No effect. Use the SETREQMASK.CHNLS to disable channel Ch from
// generating requests.
// Bit [Ch] = 1: Enables channel [Ch] to generate uDMA requests.
//
// Writing to a bit where a uDMA channel is not implemented has no effect.
#define DMA_CLEARREQMASK_CHNLS_W                                             8U
#define DMA_CLEARREQMASK_CHNLS_M                                    0x000000FFU
#define DMA_CLEARREQMASK_CHNLS_S                                             0U

//*****************************************************************************
//
// Register: DMA_O_SETCHANNELEN
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Returns the enable status of the channels, or enable the corresponding
// channels.
//
// Read as:
// Bit [Ch] = 0: Channel Ch is disabled.
// Bit [Ch] = 1: Channel Ch is enabled.
//
// Write as:
// Bit [Ch] = 0: No effect. Use the CLEARCHANNELEN.CHNLS to disable a channel
// Bit [Ch] = 1: Enables channel Ch
//
// Writing to a bit where a uDMA channel is not implemented has no effect
#define DMA_SETCHANNELEN_CHNLS_W                                             8U
#define DMA_SETCHANNELEN_CHNLS_M                                    0x000000FFU
#define DMA_SETCHANNELEN_CHNLS_S                                             0U

//*****************************************************************************
//
// Register: DMA_O_CLEARCHANNELEN
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Set the appropriate bit to disable the corresponding uDMA channel.
//
// Write as:
// Bit [Ch] = 0: No effect. Use the SETCHANNELEN.CHNLS to enable uDMA channels.
// Bit [Ch] = 1: Disables channel Ch
//
// Writing to a bit where a uDMA channel is not implemented has no effect
#define DMA_CLEARCHANNELEN_CHNLS_W                                           8U
#define DMA_CLEARCHANNELEN_CHNLS_M                                  0x000000FFU
#define DMA_CLEARCHANNELEN_CHNLS_S                                           0U

//*****************************************************************************
//
// Register: DMA_O_SETCHNLPRIALT
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Returns the channel control data structure status, or selects the alternate
// data structure for the corresponding uDMA channel.
//
// Read as:
// Bit [Ch] = 0: uDMA channel Ch is using the primary data structure.
// Bit [Ch] = 1: uDMA channel Ch is using the alternate data structure.
//
// Write as:
// Bit [Ch] = 0: No effect. Use the CLEARCHNLPRIALT.CHNLS to disable a channel
// Bit [Ch] = 1: Selects the alternate data structure for channel Ch
//
// Writing to a bit where a uDMA channel is not implemented has no effect
#define DMA_SETCHNLPRIALT_CHNLS_W                                            8U
#define DMA_SETCHNLPRIALT_CHNLS_M                                   0x000000FFU
#define DMA_SETCHNLPRIALT_CHNLS_S                                            0U

//*****************************************************************************
//
// Register: DMA_O_CLEARCHNLPRIALT
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Clears the appropriate bit to select the primary data structure for the
// corresponding uDMA channel.
//
// Write as:
// Bit [Ch] = 0: No effect. Use the SETCHNLPRIALT.CHNLS to select the alternate
// data structure.
// Bit [Ch] = 1: Selects the primary data structure for channel Ch.
//
// Writing to a bit where a uDMA channel is not implemented has no effect
#define DMA_CLEARCHNLPRIALT_CHNLS_W                                          8U
#define DMA_CLEARCHNLPRIALT_CHNLS_M                                 0x000000FFU
#define DMA_CLEARCHNLPRIALT_CHNLS_S                                          0U

//*****************************************************************************
//
// Register: DMA_O_SETCHNLPRIORITY
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Returns the channel priority mask status, or sets the channel priority to
// high.
//
// Read as:
// Bit [Ch] = 0: uDMA channel Ch is using the default priority level.
// Bit [Ch] = 1: uDMA channel Ch is using a high priority level.
//
// Write as:
// Bit [Ch] = 0: No effect. Use the CLEARCHNLPRIORITY.CHNLS to set channel Ch
// to the default priority level.
// Bit [Ch] = 1: Channel Ch uses the high priority level.
//
// Writing to a bit where a uDMA channel is not implemented has no effect
#define DMA_SETCHNLPRIORITY_CHNLS_W                                          8U
#define DMA_SETCHNLPRIORITY_CHNLS_M                                 0x000000FFU
#define DMA_SETCHNLPRIORITY_CHNLS_S                                          0U

//*****************************************************************************
//
// Register: DMA_O_CLEARCHNLPRIORITY
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Clear the appropriate bit to select the default priority level for the
// specified uDMA channel.
//
// Write as:
// Bit [Ch] = 0: No effect. Use the SETCHNLPRIORITY.CHNLS to set channel Ch to
// the high priority level.
// Bit [Ch] = 1: Channel Ch uses the default priority level.
//
// Writing to a bit where a uDMA channel is not implemented has no effect
#define DMA_CLEARCHNLPRIORITY_CHNLS_W                                        8U
#define DMA_CLEARCHNLPRIORITY_CHNLS_M                               0x000000FFU
#define DMA_CLEARCHNLPRIORITY_CHNLS_S                                        0U

//*****************************************************************************
//
// Register: DMA_O_ERROR
//
//*****************************************************************************
// Field:     [0] STATUS
//
// Returns the status of bus error flag in uDMA, or clears this bit
//
// Read as:
//
// 0: No bus error detected
// 1: Bus error detected
//
// Write as:
//
// 0: No effect, status of bus error flag is unchanged.
// 1: Clears the bus error flag.
#define DMA_ERROR_STATUS                                            0x00000001U
#define DMA_ERROR_STATUS_M                                          0x00000001U
#define DMA_ERROR_STATUS_S                                                   0U

//*****************************************************************************
//
// Register: DMA_O_REQDONE
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Reflects the uDMA done status for the given channel, channel [Ch]. It's a
// sticky done bit. Unless cleared by writing a 1, it holds the value of 1.
//
// Read as:
// Bit [Ch] = 0: Request has not completed for channel Ch
// Bit [Ch] = 1: Request has completed for the channel Ch
//
// Writing a 1 to individual bits would clear the corresponding bit.
//
// Write as:
// Bit [Ch] = 0: No effect.
// Bit [Ch] = 1: The corresponding [Ch] bit is cleared  and is set to 0
#define DMA_REQDONE_CHNLS_W                                                  8U
#define DMA_REQDONE_CHNLS_M                                         0x000000FFU
#define DMA_REQDONE_CHNLS_S                                                  0U

//*****************************************************************************
//
// Register: DMA_O_DONEMASK
//
//*****************************************************************************
// Field:   [7:0] CHNLS
//
// Controls the propagation of the uDMA done and active state to the assigned
// peripheral. Specifically used for software channels.
//
// Read as:
// Bit [Ch] = 0: uDMA done and active state for channel Ch is not blocked from
// reaching to the peripherals.
// Note that the uDMA done state for channel [Ch] is blocked from contributing
// to generation of combined uDMA done signal
//
// Bit [Ch] = 1: uDMA done and active state for channel Ch is blocked from
// reaching to the peripherals.
// Note that the uDMA done state for channel [Ch] is not blocked from
// contributing to generation of combined uDMA done signal
//
// Write as:
// Bit [Ch] = 0: Allows uDMA done and active state to propagate to the
// peripherals.
// Note that this disables uDMA done state for channel [Ch] from contributing
// to generation of combined uDMA done signal
//
// Bit [Ch] = 1: Blocks uDMA done and active state to propagate to the
// peripherals.
// Note that this enables uDMA done for  channel [Ch] to contribute to
// generation of combined uDMA done signal.
#define DMA_DONEMASK_CHNLS_W                                                 8U
#define DMA_DONEMASK_CHNLS_M                                        0x000000FFU
#define DMA_DONEMASK_CHNLS_S                                                 0U


#endif // __DMA__
