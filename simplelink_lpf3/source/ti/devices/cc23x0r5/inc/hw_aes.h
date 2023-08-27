/******************************************************************************
*  Filename:       hw_aes_h
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

#ifndef __HW_AES_H__
#define __HW_AES_H__

//*****************************************************************************
//
// This section defines the register offsets of
// AES component
//
//*****************************************************************************
// Description Register.
#define AES_O_DESC                                                  0x00000000U

// Trigger
#define AES_O_TRG                                                   0x00000010U

// Abort
#define AES_O_ABORT                                                 0x00000014U

// Clear
#define AES_O_CLR                                                   0x00000018U

// Status
#define AES_O_STA                                                   0x0000001CU

// Direct Memory Access
#define AES_O_DMA                                                   0x00000020U

// DMA Channel A data transfer
#define AES_O_DMACHA                                                0x00000024U

// DMA Channel B data transfer
#define AES_O_DMACHB                                                0x00000028U

// Automatic Configuration
#define AES_O_AUTOCFG                                               0x0000002CU

// Key Word 0
#define AES_O_KEY0                                                  0x00000050U

// Key Word 1
#define AES_O_KEY1                                                  0x00000054U

// Key Word 2
#define AES_O_KEY2                                                  0x00000058U

// Key Word 3
#define AES_O_KEY3                                                  0x0000005CU

// Text Word 0
#define AES_O_TXT0                                                  0x00000070U

// Text Word 1
#define AES_O_TXT1                                                  0x00000074U

// Text Word 2
#define AES_O_TXT2                                                  0x00000078U

// Text Word 3
#define AES_O_TXT3                                                  0x0000007CU

// Text Word 0 XOR
#define AES_O_TXTX0                                                 0x00000080U

// Text Word 1 XOR
#define AES_O_TXTX1                                                 0x00000084U

// Text Word 2 XOR
#define AES_O_TXTX2                                                 0x00000088U

// Text Word 3 XOR
#define AES_O_TXTX3                                                 0x0000008CU

// Buffer Word 0
#define AES_O_BUF0                                                  0x00000090U

// Buffer Word 1
#define AES_O_BUF1                                                  0x00000094U

// Buffer Word 2
#define AES_O_BUF2                                                  0x00000098U

// Buffer Word 3
#define AES_O_BUF3                                                  0x0000009CU

// Text Word 0 XOR Buffer Word 0
#define AES_O_TXTXBUF0                                              0x000000A0U

// Text Word 1 XOR Buffer Word 1
#define AES_O_TXTXBUF1                                              0x000000A4U

// Text Word 2 XOR Buffer Word 2
#define AES_O_TXTXBUF2                                              0x000000A8U

// Text Word 3 XOR Buffer Word3
#define AES_O_TXTXBUF3                                              0x000000ACU

// Interrupt Mask register
#define AES_O_IMASK                                                 0x00000104U

// Raw Interrupt Status register
#define AES_O_RIS                                                   0x00000108U

// Masked Interrupt Status register
#define AES_O_MIS                                                   0x0000010CU

// Interrupt Set register
#define AES_O_ISET                                                  0x00000110U

// Interrupt Clear register
#define AES_O_ICLR                                                  0x00000114U

// Interrupt Mask Set register
#define AES_O_IMSET                                                 0x00000118U

// Interrupt Mask Clear register
#define AES_O_IMCLR                                                 0x0000011CU

//*****************************************************************************
//
// Register: AES_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module Identifier
// 	    This register is used to uniquely identify this IP.
#define AES_DESC_MODID_W                                                    16U
#define AES_DESC_MODID_M                                            0xFFFF0000U
#define AES_DESC_MODID_S                                                    16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset
// 	    Standard IP MMRs are the set from aggregated IRQ registers till DTB.
//
// 0: Standard IP MMRs do not exist.
//
// 0x1-0xF: Standard IP MMRs begin at offset of 64*STDIPOFF from the base IP
// address.
#define AES_DESC_STDIPOFF_W                                                  4U
#define AES_DESC_STDIPOFF_M                                         0x0000F000U
#define AES_DESC_STDIPOFF_S                                                 12U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number
// 	    If multiple instances of IP exist in the device, this field can
// identify the instance number (0-15).
#define AES_DESC_INSTIDX_W                                                   4U
#define AES_DESC_INSTIDX_M                                          0x00000F00U
#define AES_DESC_INSTIDX_S                                                   8U

// Field:   [7:4] MAJREV
//
// Major revision of IP (0-15)
#define AES_DESC_MAJREV_W                                                    4U
#define AES_DESC_MAJREV_M                                           0x000000F0U
#define AES_DESC_MAJREV_S                                                    4U

// Field:   [3:0] MINREV
//
// Minor Revision of IP(0-15)
#define AES_DESC_MINREV_W                                                    4U
#define AES_DESC_MINREV_M                                           0x0000000FU
#define AES_DESC_MINREV_S                                                    0U

//*****************************************************************************
//
// Register: AES_O_TRG
//
//*****************************************************************************
// Field:     [3] DMACHA
//
// Manually trigger channel A request
// ENUMs:
// SET                      Triggers channel A request
// NOEFF                    Writing 0 has no effect
#define AES_TRG_DMACHA                                              0x00000008U
#define AES_TRG_DMACHA_M                                            0x00000008U
#define AES_TRG_DMACHA_S                                                     3U
#define AES_TRG_DMACHA_SET                                          0x00000008U
#define AES_TRG_DMACHA_NOEFF                                        0x00000000U

// Field:     [2] DMACHB
//
// Manually trigger channel B request
// ENUMs:
// SET                      Triggers channel B request
// NOEFF                    Writing 0 has no effect
#define AES_TRG_DMACHB                                              0x00000004U
#define AES_TRG_DMACHB_M                                            0x00000004U
#define AES_TRG_DMACHB_S                                                     2U
#define AES_TRG_DMACHB_SET                                          0x00000004U
#define AES_TRG_DMACHB_NOEFF                                        0x00000000U

// Field:   [1:0] AESOP
//
// AES Operation
//
// Write an enumerated value to this field when STA.STATE = IDLE to manually
// trigger an AES operation. If condition is not met, the trigger is ignored.
// Non-enumerated values are ignored.
// Enumerated value indicates source of AES operation
// ENUMs:
// TXTXBUF                  TXT = AES(KEY, TXT XOR BUF)
// BUF                      TXT = AES(KEY,BUF)
// TXT                      TXT = AES(KEY,TXT)
#define AES_TRG_AESOP_W                                                      2U
#define AES_TRG_AESOP_M                                             0x00000003U
#define AES_TRG_AESOP_S                                                      0U
#define AES_TRG_AESOP_TXTXBUF                                       0x00000003U
#define AES_TRG_AESOP_BUF                                           0x00000002U
#define AES_TRG_AESOP_TXT                                           0x00000001U

//*****************************************************************************
//
// Register: AES_O_ABORT
//
//*****************************************************************************
// Field:     [0] ABORTAES
//
// Abort AES operation
//
// Abort an ongoing AES operation. An abort will clear TXT, BUF, DMA, AUTOCFG
// registers
// ENUMs:
// SET                      Aborts an ongoing AES operation
// NOEFF                    Writing 0 has no effect
#define AES_ABORT_ABORTAES                                          0x00000001U
#define AES_ABORT_ABORTAES_M                                        0x00000001U
#define AES_ABORT_ABORTAES_S                                                 0U
#define AES_ABORT_ABORTAES_SET                                      0x00000001U
#define AES_ABORT_ABORTAES_NOEFF                                    0x00000000U

//*****************************************************************************
//
// Register: AES_O_CLR
//
//*****************************************************************************
// Field:     [1] TXT
//
// Clear TXT
// ENUMs:
// CLR                      Clears TXT
// NOEFF                    Writing 0 has no effect
#define AES_CLR_TXT                                                 0x00000002U
#define AES_CLR_TXT_M                                               0x00000002U
#define AES_CLR_TXT_S                                                        1U
#define AES_CLR_TXT_CLR                                             0x00000002U
#define AES_CLR_TXT_NOEFF                                           0x00000000U

// Field:     [0] BUF
//
// Clear BUF
// ENUMs:
// CLR                      Clears BUF
// NOEFF                    Writing 0 has no effect
#define AES_CLR_BUF                                                 0x00000001U
#define AES_CLR_BUF_M                                               0x00000001U
#define AES_CLR_BUF_S                                                        0U
#define AES_CLR_BUF_CLR                                             0x00000001U
#define AES_CLR_BUF_NOEFF                                           0x00000000U

//*****************************************************************************
//
// Register: AES_O_STA
//
//*****************************************************************************
// Field:     [1] BUFSTA
//
//  BUF Status
//
// Field gives the status of BUF, indicating EMPTY or FULL, when AUTOCFG.TRGAES
// = WRBUF3.
// If AUTOCFG.TRGAES != WRBUF3, then STA.BUFSTA will hold the value 0.
// Note : Useful for CBC-MAC
// ENUMs:
// FULL                     Data stored in BUF is not yet consumed by the AES
//                          engine. Next block of data cannot be written
//                          into BUF until STA.STATE = IDLE.
// EMPTY                    Data stored in BUF is already consumed by the AES
//                          engine and next block of data can be written in
//                          BUF.
#define AES_STA_BUFSTA                                              0x00000002U
#define AES_STA_BUFSTA_M                                            0x00000002U
#define AES_STA_BUFSTA_S                                                     1U
#define AES_STA_BUFSTA_FULL                                         0x00000002U
#define AES_STA_BUFSTA_EMPTY                                        0x00000000U

// Field:     [0] STATE
//
// State
//
// Field gives the state of the AES engine.
// ENUMs:
// BUSY                     AES operation active
// IDLE                     AES engine is IDLE
#define AES_STA_STATE                                               0x00000001U
#define AES_STA_STATE_M                                             0x00000001U
#define AES_STA_STATE_S                                                      0U
#define AES_STA_STATE_BUSY                                          0x00000001U
#define AES_STA_STATE_IDLE                                          0x00000000U

//*****************************************************************************
//
// Register: AES_O_DMA
//
//*****************************************************************************
// Field: [19:16] DONEACT
//
// Done Action
//
// This field determines the side effects of DMA done. It is allowed to
// configure this field with an OR-combination of supported enums, with the
// exception that GATE_TRGAES_ON_CHA and GATE_TRGAES_ON_CHA_DEL must be
// mutually exclusive
// ENUMs:
// CLR_TXT_ON_CHB           DMA channel B done event clears TXT0 thru TXT3 if
//                          STA.STATE = IDLE. Event is ignored if condition
//                          is not met.
// CLR_TXT_ON_CHA           DMA channel A done event clears TXT0 thru TXT3 if
//                          STA.STATE = IDLE. Event is ignored if condition
//                          is not met.
// GATE_TRGAES_ON_CHA_DEL   Delayed gating of triggers defined in
//                          AUTOCFG.TRGAES
//                          		Due to the pipelining
//                          of BUF writes, in certain modes, DMA CHA Done
//                          appears before the last but one AES operation
//                          has completed. Setting this bit, will gate the
//                          triggers defined in AUTOCFG.TRGAES  only after
//                          the last write by CHA is consumed by AES FSM.
//                          Used in ECB,CBC,CBC-MAC modes (having multiple
//                          blocks encryption/decryption) to avoid spurious
//                          AES operation triggered on last read by CHB.
//                          For single mode operation,
//                          DMA.GATE_TRGAES_ON_CHA must be used.
// GATE_TRGAES_ON_CHA       Triggers defined in AUTOCFG.TRGAES are gated when
//                          RIS.CHADONE  = SET
// DIS                      DMA done has no side effect
#define AES_DMA_DONEACT_W                                                    4U
#define AES_DMA_DONEACT_M                                           0x000F0000U
#define AES_DMA_DONEACT_S                                                   16U
#define AES_DMA_DONEACT_CLR_TXT_ON_CHB                              0x00080000U
#define AES_DMA_DONEACT_CLR_TXT_ON_CHA                              0x00040000U
#define AES_DMA_DONEACT_GATE_TRGAES_ON_CHA_DEL                      0x00020000U
#define AES_DMA_DONEACT_GATE_TRGAES_ON_CHA                          0x00010000U
#define AES_DMA_DONEACT_DIS                                         0x00000000U

// Field: [13:12] ADRCHB
//
// Channel B Read Write Address
//
// The DMA accesses DMACHB to read or write contents of TXT and BUF as a
// response to a burst request. This field specifes the start address of the
// first DMA transfer that follows the burst request. The internal address gets
// incremented automatically for subsequent accesses. The DMA can transfer
// 8-bit, 16-bit, or 32-bit words, and must always complete a 16-byte transfer
// before re-arbitration.
// ENUMs:
// TXTXBUF0                 Start address is TXTXBUF0
// BUF0                     Start address is BUF0
// TXTX0                    Start address is TXTX0
// TXT0                     Start address is TXT0
#define AES_DMA_ADRCHB_W                                                     2U
#define AES_DMA_ADRCHB_M                                            0x00003000U
#define AES_DMA_ADRCHB_S                                                    12U
#define AES_DMA_ADRCHB_TXTXBUF0                                     0x00003000U
#define AES_DMA_ADRCHB_BUF0                                         0x00002000U
#define AES_DMA_ADRCHB_TXTX0                                        0x00001000U
#define AES_DMA_ADRCHB_TXT0                                         0x00000000U

// Field:  [10:8] TRGCHB
//
// Channel B Trigger
//
// Select the condition that triggers DMA channel B request. Non-enumerated
// values are not supported and ignored.
// ENUMs:
// RDTXT3                   Reads of TXT3, or TXTXBUF3 trigger request
// WRTXT3                   Writes to TXT3, TXTX3, or TXTXBUF3 trigger request
// AESDONE                  Completion of AES operation triggers request
// AESSTART                 Start of AES operation triggers request
// DIS                      DMA requests are disabled
#define AES_DMA_TRGCHB_W                                                     3U
#define AES_DMA_TRGCHB_M                                            0x00000700U
#define AES_DMA_TRGCHB_S                                                     8U
#define AES_DMA_TRGCHB_RDTXT3                                       0x00000400U
#define AES_DMA_TRGCHB_WRTXT3                                       0x00000300U
#define AES_DMA_TRGCHB_AESDONE                                      0x00000200U
#define AES_DMA_TRGCHB_AESSTART                                     0x00000100U
#define AES_DMA_TRGCHB_DIS                                          0x00000000U

// Field:   [5:4] ADRCHA
//
// Channel A Read Write Address
//
// The DMA accesses DMACHA to read or write contents of TXT and BUF as a
// response to a burst request. This field specifes the start address of the
// first DMA transfer that follows the burst request. The internal address gets
// incremented automatically for subsequent accesses. The DMA can transfer
// 8-bit, 16-bit, or 32-bit words, and must always complete a 16-byte transfer
// before re-arbitration.
// ENUMs:
// TXTXBUF0                 Start address is TXTXBUF0
// BUF0                     Start address is BUF0
// TXTX0                    Start address is TXTX0
// TXT0                     Start address is TXT0
#define AES_DMA_ADRCHA_W                                                     2U
#define AES_DMA_ADRCHA_M                                            0x00000030U
#define AES_DMA_ADRCHA_S                                                     4U
#define AES_DMA_ADRCHA_TXTXBUF0                                     0x00000030U
#define AES_DMA_ADRCHA_BUF0                                         0x00000020U
#define AES_DMA_ADRCHA_TXTX0                                        0x00000010U
#define AES_DMA_ADRCHA_TXT0                                         0x00000000U

// Field:   [2:0] TRGCHA
//
// Channel A Trigger
//
// Select the condition that triggers DMA channel A request. Non-enumerated
// values are not supported and ignored.
// ENUMs:
// RDTXT3                   Reads of TXT3 or TXTXBUF3 trigger request
// WRTXT3                   Writes to TXT3 or TXTX3 trigger request
// AESDONE                  Completion of AES operation triggers request
// AESSTART                 Start of AES operation triggers request
// DIS                      DMA requests are disabled
#define AES_DMA_TRGCHA_W                                                     3U
#define AES_DMA_TRGCHA_M                                            0x00000007U
#define AES_DMA_TRGCHA_S                                                     0U
#define AES_DMA_TRGCHA_RDTXT3                                       0x00000004U
#define AES_DMA_TRGCHA_WRTXT3                                       0x00000003U
#define AES_DMA_TRGCHA_AESDONE                                      0x00000002U
#define AES_DMA_TRGCHA_AESSTART                                     0x00000001U
#define AES_DMA_TRGCHA_DIS                                          0x00000000U

//*****************************************************************************
//
// Register: AES_O_DMACHA
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value transferred through DMA Channel A
#define AES_DMACHA_VAL_W                                                    32U
#define AES_DMACHA_VAL_M                                            0xFFFFFFFFU
#define AES_DMACHA_VAL_S                                                     0U

//*****************************************************************************
//
// Register: AES_O_DMACHB
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value transferred through DMA Channel B
#define AES_DMACHB_VAL_W                                                    32U
#define AES_DMACHB_VAL_M                                            0xFFFFFFFFU
#define AES_DMACHB_VAL_S                                                     0U

//*****************************************************************************
//
// Register: AES_O_AUTOCFG
//
//*****************************************************************************
// Field:    [28] CHBDNCLR
//
// This field enable auto-clear of RIS.CHBDONE interrupt on read/write of
// TXT3/BUF3/TXTX3/TXTXBUF3 .
//
// ENUMs:
// EN                       Enable auto-clear of  RIS.CHBDONE interrupt
// DIS                      Disable auto-clear of  RIS.CHBDONE interrupt
#define AES_AUTOCFG_CHBDNCLR                                        0x10000000U
#define AES_AUTOCFG_CHBDNCLR_M                                      0x10000000U
#define AES_AUTOCFG_CHBDNCLR_S                                              28U
#define AES_AUTOCFG_CHBDNCLR_EN                                     0x10000000U
#define AES_AUTOCFG_CHBDNCLR_DIS                                    0x00000000U

// Field:    [27] CHADNCLR
//
// This field enables auto-clear of RIS.CHADONE interrupt on read/write of
// TXT3/BUF3/TXTX3/TXTXBUF3 .
//
// ENUMs:
// EN                       Enable auto-clear of  RIS.CHADONE interrupt
// DIS                      Disable auto-clear of  RIS.CHADONE interrupt
#define AES_AUTOCFG_CHADNCLR                                        0x08000000U
#define AES_AUTOCFG_CHADNCLR_M                                      0x08000000U
#define AES_AUTOCFG_CHADNCLR_S                                              27U
#define AES_AUTOCFG_CHADNCLR_EN                                     0x08000000U
#define AES_AUTOCFG_CHADNCLR_DIS                                    0x00000000U

// Field:    [26] CLRAESST
//
// Clear AES Start
//
// This field enables auto-clear of RIS.AESSTART interrupt on read/write of
// TXT3/BUF3/TXTX3/TXTXBUF3 .
// ENUMs:
// EN                       Enable auto-clear of  RIS.AESSTART interrupt
// DIS                      Disable auto-clear of  RIS.AESSTART interrupt
#define AES_AUTOCFG_CLRAESST                                        0x04000000U
#define AES_AUTOCFG_CLRAESST_M                                      0x04000000U
#define AES_AUTOCFG_CLRAESST_S                                              26U
#define AES_AUTOCFG_CLRAESST_EN                                     0x04000000U
#define AES_AUTOCFG_CLRAESST_DIS                                    0x00000000U

// Field:    [25] CLRAESDN
//
// Clear AES Done
//
// This field enables auto-clear of RIS.AESDONE interrupt on read/write of
// TXT3/BUF3/TXTX3/TXTXBUF3 .
//
// ENUMs:
// EN                       Enable auto-clear of  RIS.AESDONE interrupt
// DIS                      Disable auto-clear of RIS.AESDONE interrupt
#define AES_AUTOCFG_CLRAESDN                                        0x02000000U
#define AES_AUTOCFG_CLRAESDN_M                                      0x02000000U
#define AES_AUTOCFG_CLRAESDN_S                                              25U
#define AES_AUTOCFG_CLRAESDN_EN                                     0x02000000U
#define AES_AUTOCFG_CLRAESDN_DIS                                    0x00000000U

// Field:    [24] BUSHALT
//
// Bus Halt
//
// This field decides if bus halts on access to KEY, TXT, BUF, TXTX and TXTXBUF
// when STA.STATE = BUSY.
// ENUMs:
// EN                       Enable bus halt
//
//                          When STA.STATE = BUSY,
//                          access to KEY, TXT, TXTX, TXTXBUF halt the bus
//                          until STA.STATE = IDLE.
//                          When STA.STATE = BUSY and
//                          if either STA.BUFSTA = FULL or AUTOCFG.CTRSIZE
//                          != DISABLE, access to BUF halts the bus until
//                          STA.STATE = IDLE.
// DIS                      Disable bus halt
//
//                          When STA.STATE = BUSY,
//                          writes to KEY, TXT, TXTX are ignored, reads
//                          from  TXT, TXTXBUF return zero.
//                          When STA.STATE = BUSY and
//                          if either STA.BUFSTA = FULL or AUTOCFG.CTRSIZE
//                          != DISABLE, writes to BUF are ignored, reads
//                          return zero.
#define AES_AUTOCFG_BUSHALT                                         0x01000000U
#define AES_AUTOCFG_BUSHALT_M                                       0x01000000U
#define AES_AUTOCFG_BUSHALT_S                                               24U
#define AES_AUTOCFG_BUSHALT_EN                                      0x01000000U
#define AES_AUTOCFG_BUSHALT_DIS                                     0x00000000U

// Field: [21:19] CTRSIZE
//
// Counter Size
//
// Configures  size of counter as either 8,16,32,64 or 128
// Non-enumerated values are not supported and ignored
// ENUMs:
// CTR128                   Configures counter size as 128-bit
// CTR64                    Configures counter size as 64-bit
// CTR32                    Configures counter size as 32-bit
// CTR16                    Configures counter size as 16-bit
// CTR8                     Configures counter size as 8-bit
// DIS                      Disable CTR operation
#define AES_AUTOCFG_CTRSIZE_W                                                3U
#define AES_AUTOCFG_CTRSIZE_M                                       0x00380000U
#define AES_AUTOCFG_CTRSIZE_S                                               19U
#define AES_AUTOCFG_CTRSIZE_CTR128                                  0x00280000U
#define AES_AUTOCFG_CTRSIZE_CTR64                                   0x00200000U
#define AES_AUTOCFG_CTRSIZE_CTR32                                   0x00180000U
#define AES_AUTOCFG_CTRSIZE_CTR16                                   0x00100000U
#define AES_AUTOCFG_CTRSIZE_CTR8                                    0x00080000U
#define AES_AUTOCFG_CTRSIZE_DIS                                     0x00000000U

// Field:    [18] CTRALIGN
//
// Counter Alignment
//
// Specifies alignment of counter
// ENUMs:
// RIGHTALIGN               Indicates right aligned counter
//                          Not applicable when
//                          counter size is 128-bit
//                          For 128-bit counter, all
//                          octets will be considered
//
//                          If right aligned, octet
//                          8-15 will be considered based on endianness and
//                          counter size
// LEFTALIGN                Indicates Left Aligned Counter
//                          Not applicable for
//                          128-bit counter size.
//                          For 128-bit counter, all
//                          octets will be considered
//
//                          When left aligned,,octet
//                          0-7 will be considered , based on counter size
//                          and endianness
#define AES_AUTOCFG_CTRALIGN                                        0x00040000U
#define AES_AUTOCFG_CTRALIGN_M                                      0x00040000U
#define AES_AUTOCFG_CTRALIGN_S                                              18U
#define AES_AUTOCFG_CTRALIGN_RIGHTALIGN                             0x00040000U
#define AES_AUTOCFG_CTRALIGN_LEFTALIGN                              0x00000000U

// Field:    [17] CTRENDN
//
// Counter Endianness
//
// Specifies Endianness of counter
// ENUMs:
// BIGENDIAN                Specifies Big Endian Counter
//                          Carry will flow from
//                          octet 'n' to octet 'n-1'
// LITTLEENDIAN             Specifies Little Endian Counter
//                          Carry will flow from
//                          octet 'n' to octet 'n+1'
#define AES_AUTOCFG_CTRENDN                                         0x00020000U
#define AES_AUTOCFG_CTRENDN_M                                       0x00020000U
#define AES_AUTOCFG_CTRENDN_S                                               17U
#define AES_AUTOCFG_CTRENDN_BIGENDIAN                               0x00020000U
#define AES_AUTOCFG_CTRENDN_LITTLEENDIAN                            0x00000000U

// Field:   [9:8] TRGTXT
//
// Trigger for TXT
//
// This field determines if and when hardware automatically XORs BUF into TXT.
// Non-enumerated values are not supported and ignored. It is allowed to
// configure this field with an OR-combination of supported enums.
// ENUMs:
// RDTXTXBUF3               Hardware XORs content of BUF into TXT upon read of
//                          TXTXBUF3
// RDTXT3                   Hardware XORs content of BUF into TXT upon read of
//                          TXT3
// DIS                      No hardware update of TXT
#define AES_AUTOCFG_TRGTXT_W                                                 2U
#define AES_AUTOCFG_TRGTXT_M                                        0x00000300U
#define AES_AUTOCFG_TRGTXT_S                                                 8U
#define AES_AUTOCFG_TRGTXT_RDTXTXBUF3                               0x00000200U
#define AES_AUTOCFG_TRGTXT_RDTXT3                                   0x00000100U
#define AES_AUTOCFG_TRGTXT_DIS                                      0x00000000U

// Field:   [5:4] AESSRC
//
// AES Source
//
// This field specifies the data source to hardware-triggered AES operations.
// Non-enumerated values are not supported and ignored.
// ENUMs:
// TXTXBUF                  TXT = AES(KEY, TXT XOR BUF)
// BUF                      TXT = AES(KEY,BUF)
// TXT                      TXT = AES(KEY,TXT)
#define AES_AUTOCFG_AESSRC_W                                                 2U
#define AES_AUTOCFG_AESSRC_M                                        0x00000030U
#define AES_AUTOCFG_AESSRC_S                                                 4U
#define AES_AUTOCFG_AESSRC_TXTXBUF                                  0x00000030U
#define AES_AUTOCFG_AESSRC_BUF                                      0x00000020U
#define AES_AUTOCFG_AESSRC_TXT                                      0x00000010U

// Field:   [3:0] TRGAES
//
// Trigger Electronic Codebook
//
// This field specifies one or more actions that indirectly trigger AES
// operation.
// It is allowed to configure this field with an OR-combination of supported
// enums.
// ENUMs:
// WRBUF3S                  Write to BUF3 will schedule to trigger single
//                          action once STA.STATE is or becomes IDLE.
//                          Subsequent writes do not trigger action unless
//                          this setting is written again to this field.
// WRBUF3                   All writes to BUF3 will schedule to trigger action
//                          once STA.STATE is or becomes IDLE, only when
//                          AUTOCFG.CTRSIZE = DIS
// RDTXT3                   All reads of TXT3 or TXTXBUF3 trigger action, only
//                          when STA.STATE = IDLE
// WRTXT3                   All writes to TXT3 or TXTX3 trigger action, only
//                          when STA.STATE = IDLE
// DIS                      No user action indirectly triggers AES operation
#define AES_AUTOCFG_TRGAES_W                                                 4U
#define AES_AUTOCFG_TRGAES_M                                        0x0000000FU
#define AES_AUTOCFG_TRGAES_S                                                 0U
#define AES_AUTOCFG_TRGAES_WRBUF3S                                  0x00000008U
#define AES_AUTOCFG_TRGAES_WRBUF3                                   0x00000004U
#define AES_AUTOCFG_TRGAES_RDTXT3                                   0x00000002U
#define AES_AUTOCFG_TRGAES_WRTXT3                                   0x00000001U
#define AES_AUTOCFG_TRGAES_DIS                                      0x00000000U

//*****************************************************************************
//
// Register: AES_O_KEY0
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value of KEY[31:0]
#define AES_KEY0_VAL_W                                                      32U
#define AES_KEY0_VAL_M                                              0xFFFFFFFFU
#define AES_KEY0_VAL_S                                                       0U

//*****************************************************************************
//
// Register: AES_O_KEY1
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value of KEY[63:32]
#define AES_KEY1_VAL_W                                                      32U
#define AES_KEY1_VAL_M                                              0xFFFFFFFFU
#define AES_KEY1_VAL_S                                                       0U

//*****************************************************************************
//
// Register: AES_O_KEY2
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value of KEY[95:64]
#define AES_KEY2_VAL_W                                                      32U
#define AES_KEY2_VAL_M                                              0xFFFFFFFFU
#define AES_KEY2_VAL_S                                                       0U

//*****************************************************************************
//
// Register: AES_O_KEY3
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value of KEY[127:96]
#define AES_KEY3_VAL_W                                                      32U
#define AES_KEY3_VAL_M                                              0xFFFFFFFFU
#define AES_KEY3_VAL_S                                                       0U

//*****************************************************************************
//
// Register: AES_O_TXT0
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value of TXT[31:0]
#define AES_TXT0_VAL_W                                                      32U
#define AES_TXT0_VAL_M                                              0xFFFFFFFFU
#define AES_TXT0_VAL_S                                                       0U

//*****************************************************************************
//
// Register: AES_O_TXT1
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value of TXT[63:32]
#define AES_TXT1_VAL_W                                                      32U
#define AES_TXT1_VAL_M                                              0xFFFFFFFFU
#define AES_TXT1_VAL_S                                                       0U

//*****************************************************************************
//
// Register: AES_O_TXT2
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value of TXT[95:64]
#define AES_TXT2_VAL_W                                                      32U
#define AES_TXT2_VAL_M                                              0xFFFFFFFFU
#define AES_TXT2_VAL_S                                                       0U

//*****************************************************************************
//
// Register: AES_O_TXT3
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value of TXT[127:96]
//
// AUTOCFG.TRGAES decides if a write to or a read of this field triggers an AES
// operation.
#define AES_TXT3_VAL_W                                                      32U
#define AES_TXT3_VAL_M                                              0xFFFFFFFFU
#define AES_TXT3_VAL_S                                                       0U

//*****************************************************************************
//
// Register: AES_O_TXTX0
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value in TXT0 will be TXT0.VAL = VAL XOR TXT0.VAL
#define AES_TXTX0_VAL_W                                                     32U
#define AES_TXTX0_VAL_M                                             0xFFFFFFFFU
#define AES_TXTX0_VAL_S                                                      0U

//*****************************************************************************
//
// Register: AES_O_TXTX1
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value in TXT1 will be TXT1.VAL = VAL XOR TXT1.VAL
#define AES_TXTX1_VAL_W                                                     32U
#define AES_TXTX1_VAL_M                                             0xFFFFFFFFU
#define AES_TXTX1_VAL_S                                                      0U

//*****************************************************************************
//
// Register: AES_O_TXTX2
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value in TXT2 will be TXT2.VAL = VAL XOR TXT2.VAL
#define AES_TXTX2_VAL_W                                                     32U
#define AES_TXTX2_VAL_M                                             0xFFFFFFFFU
#define AES_TXTX2_VAL_S                                                      0U

//*****************************************************************************
//
// Register: AES_O_TXTX3
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value in TXT3 will be TXT3.VAL = VAL XOR TXT3.VAL
#define AES_TXTX3_VAL_W                                                     32U
#define AES_TXTX3_VAL_M                                             0xFFFFFFFFU
#define AES_TXTX3_VAL_S                                                      0U

//*****************************************************************************
//
// Register: AES_O_BUF0
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value of BUF[31:0]
#define AES_BUF0_VAL_W                                                      32U
#define AES_BUF0_VAL_M                                              0xFFFFFFFFU
#define AES_BUF0_VAL_S                                                       0U

//*****************************************************************************
//
// Register: AES_O_BUF1
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value of BUF[63:32]
#define AES_BUF1_VAL_W                                                      32U
#define AES_BUF1_VAL_M                                              0xFFFFFFFFU
#define AES_BUF1_VAL_S                                                       0U

//*****************************************************************************
//
// Register: AES_O_BUF2
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value of BUF[95:64]
#define AES_BUF2_VAL_W                                                      32U
#define AES_BUF2_VAL_M                                              0xFFFFFFFFU
#define AES_BUF2_VAL_S                                                       0U

//*****************************************************************************
//
// Register: AES_O_BUF3
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value of BUF[127:96]
#define AES_BUF3_VAL_W                                                      32U
#define AES_BUF3_VAL_M                                              0xFFFFFFFFU
#define AES_BUF3_VAL_S                                                       0U

//*****************************************************************************
//
// Register: AES_O_TXTXBUF0
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value read will be  TXT0.VAL XOR BUF0.VAL
#define AES_TXTXBUF0_VAL_W                                                  32U
#define AES_TXTXBUF0_VAL_M                                          0xFFFFFFFFU
#define AES_TXTXBUF0_VAL_S                                                   0U

//*****************************************************************************
//
// Register: AES_O_TXTXBUF1
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value read will be  TXT1.VAL XOR BUF1.VAL
#define AES_TXTXBUF1_VAL_W                                                  32U
#define AES_TXTXBUF1_VAL_M                                          0xFFFFFFFFU
#define AES_TXTXBUF1_VAL_S                                                   0U

//*****************************************************************************
//
// Register: AES_O_TXTXBUF2
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value read will be TXT2.VAL XOR BUF2.VAL
#define AES_TXTXBUF2_VAL_W                                                  32U
#define AES_TXTXBUF2_VAL_M                                          0xFFFFFFFFU
#define AES_TXTXBUF2_VAL_S                                                   0U

//*****************************************************************************
//
// Register: AES_O_TXTXBUF3
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Value read will be  TXT3.VAL XOR BUF3.VAL
#define AES_TXTXBUF3_VAL_W                                                  32U
#define AES_TXTXBUF3_VAL_M                                          0xFFFFFFFFU
#define AES_TXTXBUF3_VAL_S                                                   0U

//*****************************************************************************
//
// Register: AES_O_IMASK
//
//*****************************************************************************
// Field:     [3] CHBDONE
//
// DMA Channel B Done interrupt mask
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define AES_IMASK_CHBDONE                                           0x00000008U
#define AES_IMASK_CHBDONE_M                                         0x00000008U
#define AES_IMASK_CHBDONE_S                                                  3U
#define AES_IMASK_CHBDONE_EN                                        0x00000008U
#define AES_IMASK_CHBDONE_DIS                                       0x00000000U

// Field:     [2] CHADONE
//
// DMA Channel A Done interrupt mask
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define AES_IMASK_CHADONE                                           0x00000004U
#define AES_IMASK_CHADONE_M                                         0x00000004U
#define AES_IMASK_CHADONE_S                                                  2U
#define AES_IMASK_CHADONE_EN                                        0x00000004U
#define AES_IMASK_CHADONE_DIS                                       0x00000000U

// Field:     [1] AESSTART
//
// AES Start interrupt mask
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define AES_IMASK_AESSTART                                          0x00000002U
#define AES_IMASK_AESSTART_M                                        0x00000002U
#define AES_IMASK_AESSTART_S                                                 1U
#define AES_IMASK_AESSTART_EN                                       0x00000002U
#define AES_IMASK_AESSTART_DIS                                      0x00000000U

// Field:     [0] AESDONE
//
// AES Done interrupt mask
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define AES_IMASK_AESDONE                                           0x00000001U
#define AES_IMASK_AESDONE_M                                         0x00000001U
#define AES_IMASK_AESDONE_S                                                  0U
#define AES_IMASK_AESDONE_EN                                        0x00000001U
#define AES_IMASK_AESDONE_DIS                                       0x00000000U

//*****************************************************************************
//
// Register: AES_O_RIS
//
//*****************************************************************************
// Field:     [3] CHBDONE
//
// Raw Interrupt Status for DMA Channel B Done
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define AES_RIS_CHBDONE                                             0x00000008U
#define AES_RIS_CHBDONE_M                                           0x00000008U
#define AES_RIS_CHBDONE_S                                                    3U
#define AES_RIS_CHBDONE_SET                                         0x00000008U
#define AES_RIS_CHBDONE_CLR                                         0x00000000U

// Field:     [2] CHADONE
//
// Raw Interrupt Status for DMA Channel A Done
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define AES_RIS_CHADONE                                             0x00000004U
#define AES_RIS_CHADONE_M                                           0x00000004U
#define AES_RIS_CHADONE_S                                                    2U
#define AES_RIS_CHADONE_SET                                         0x00000004U
#define AES_RIS_CHADONE_CLR                                         0x00000000U

// Field:     [1] AESSTART
//
// Raw Interrupt Status for AES Start
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define AES_RIS_AESSTART                                            0x00000002U
#define AES_RIS_AESSTART_M                                          0x00000002U
#define AES_RIS_AESSTART_S                                                   1U
#define AES_RIS_AESSTART_SET                                        0x00000002U
#define AES_RIS_AESSTART_CLR                                        0x00000000U

// Field:     [0] AESDONE
//
// Raw Interrupt Status for AES Done
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define AES_RIS_AESDONE                                             0x00000001U
#define AES_RIS_AESDONE_M                                           0x00000001U
#define AES_RIS_AESDONE_S                                                    0U
#define AES_RIS_AESDONE_SET                                         0x00000001U
#define AES_RIS_AESDONE_CLR                                         0x00000000U

//*****************************************************************************
//
// Register: AES_O_MIS
//
//*****************************************************************************
// Field:     [3] CHBDONE
//
// Masked Interrupt Status for DMA Channel B Done
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define AES_MIS_CHBDONE                                             0x00000008U
#define AES_MIS_CHBDONE_M                                           0x00000008U
#define AES_MIS_CHBDONE_S                                                    3U
#define AES_MIS_CHBDONE_SET                                         0x00000008U
#define AES_MIS_CHBDONE_CLR                                         0x00000000U

// Field:     [2] CHADONE
//
// Masked Interrupt Status for DMA Channel A Done
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define AES_MIS_CHADONE                                             0x00000004U
#define AES_MIS_CHADONE_M                                           0x00000004U
#define AES_MIS_CHADONE_S                                                    2U
#define AES_MIS_CHADONE_SET                                         0x00000004U
#define AES_MIS_CHADONE_CLR                                         0x00000000U

// Field:     [1] AESSTART
//
// Masked Interrupt Status for AES Start
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define AES_MIS_AESSTART                                            0x00000002U
#define AES_MIS_AESSTART_M                                          0x00000002U
#define AES_MIS_AESSTART_S                                                   1U
#define AES_MIS_AESSTART_SET                                        0x00000002U
#define AES_MIS_AESSTART_CLR                                        0x00000000U

// Field:     [0] AESDONE
//
// Masked Interrupt Status for AES Done
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define AES_MIS_AESDONE                                             0x00000001U
#define AES_MIS_AESDONE_M                                           0x00000001U
#define AES_MIS_AESDONE_S                                                    0U
#define AES_MIS_AESDONE_SET                                         0x00000001U
#define AES_MIS_AESDONE_CLR                                         0x00000000U

//*****************************************************************************
//
// Register: AES_O_ISET
//
//*****************************************************************************
// Field:     [3] CHBDONE
//
// Set DMA Channel B Done interrupt
// ENUMs:
// SET                      Set interrupt
// NOEFF                    Writing 0 has no effect
#define AES_ISET_CHBDONE                                            0x00000008U
#define AES_ISET_CHBDONE_M                                          0x00000008U
#define AES_ISET_CHBDONE_S                                                   3U
#define AES_ISET_CHBDONE_SET                                        0x00000008U
#define AES_ISET_CHBDONE_NOEFF                                      0x00000000U

// Field:     [2] CHADONE
//
// Set DMA Channel A Done interrupt
// ENUMs:
// SET                      Set interrupt
// NOEFF                    Writing 0 has no effect
#define AES_ISET_CHADONE                                            0x00000004U
#define AES_ISET_CHADONE_M                                          0x00000004U
#define AES_ISET_CHADONE_S                                                   2U
#define AES_ISET_CHADONE_SET                                        0x00000004U
#define AES_ISET_CHADONE_NOEFF                                      0x00000000U

// Field:     [1] AESSTART
//
// Set AES Start interrupt
// ENUMs:
// SET                      Set interrupt
// NOEFF                    Writing 0 has no effect
#define AES_ISET_AESSTART                                           0x00000002U
#define AES_ISET_AESSTART_M                                         0x00000002U
#define AES_ISET_AESSTART_S                                                  1U
#define AES_ISET_AESSTART_SET                                       0x00000002U
#define AES_ISET_AESSTART_NOEFF                                     0x00000000U

// Field:     [0] AESDONE
//
// Set AES Done interrupt
// ENUMs:
// SET                      Set interrupt
// NOEFF                    Writing 0 has no effect
#define AES_ISET_AESDONE                                            0x00000001U
#define AES_ISET_AESDONE_M                                          0x00000001U
#define AES_ISET_AESDONE_S                                                   0U
#define AES_ISET_AESDONE_SET                                        0x00000001U
#define AES_ISET_AESDONE_NOEFF                                      0x00000000U

//*****************************************************************************
//
// Register: AES_O_ICLR
//
//*****************************************************************************
// Field:     [3] CHBDONE
//
// Clear DMA Channel B Done interrupt
// ENUMs:
// CLR                      Clear interrupt
// NOEFF                    Writing 0 has no effect
#define AES_ICLR_CHBDONE                                            0x00000008U
#define AES_ICLR_CHBDONE_M                                          0x00000008U
#define AES_ICLR_CHBDONE_S                                                   3U
#define AES_ICLR_CHBDONE_CLR                                        0x00000008U
#define AES_ICLR_CHBDONE_NOEFF                                      0x00000000U

// Field:     [2] CHADONE
//
// Clear DMA Channel A Done interrupt
// ENUMs:
// CLR                      Clear interrupt
// NOEFF                    Writing 0 has no effect
#define AES_ICLR_CHADONE                                            0x00000004U
#define AES_ICLR_CHADONE_M                                          0x00000004U
#define AES_ICLR_CHADONE_S                                                   2U
#define AES_ICLR_CHADONE_CLR                                        0x00000004U
#define AES_ICLR_CHADONE_NOEFF                                      0x00000000U

// Field:     [1] AESSTART
//
// Clear AES Start interrupt
// ENUMs:
// CLR                      Clear interrupt
// NOEFF                    Writing 0 has no effect
#define AES_ICLR_AESSTART                                           0x00000002U
#define AES_ICLR_AESSTART_M                                         0x00000002U
#define AES_ICLR_AESSTART_S                                                  1U
#define AES_ICLR_AESSTART_CLR                                       0x00000002U
#define AES_ICLR_AESSTART_NOEFF                                     0x00000000U

// Field:     [0] AESDONE
//
// Clear AES Done interrupt
// ENUMs:
// CLR                      Clear interrupt
// NOEFF                    Writing 0 has no effect
#define AES_ICLR_AESDONE                                            0x00000001U
#define AES_ICLR_AESDONE_M                                          0x00000001U
#define AES_ICLR_AESDONE_S                                                   0U
#define AES_ICLR_AESDONE_CLR                                        0x00000001U
#define AES_ICLR_AESDONE_NOEFF                                      0x00000000U

//*****************************************************************************
//
// Register: AES_O_IMSET
//
//*****************************************************************************
// Field:     [3] CHBDONE
//
// Set DMA Channel B Done interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define AES_IMSET_CHBDONE                                           0x00000008U
#define AES_IMSET_CHBDONE_M                                         0x00000008U
#define AES_IMSET_CHBDONE_S                                                  3U
#define AES_IMSET_CHBDONE_SET                                       0x00000008U
#define AES_IMSET_CHBDONE_NOEFF                                     0x00000000U

// Field:     [2] CHADONE
//
// Set DMA Channel A Done interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define AES_IMSET_CHADONE                                           0x00000004U
#define AES_IMSET_CHADONE_M                                         0x00000004U
#define AES_IMSET_CHADONE_S                                                  2U
#define AES_IMSET_CHADONE_SET                                       0x00000004U
#define AES_IMSET_CHADONE_NOEFF                                     0x00000000U

// Field:     [1] AESSTART
//
// Set AES Start interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define AES_IMSET_AESSTART                                          0x00000002U
#define AES_IMSET_AESSTART_M                                        0x00000002U
#define AES_IMSET_AESSTART_S                                                 1U
#define AES_IMSET_AESSTART_SET                                      0x00000002U
#define AES_IMSET_AESSTART_NOEFF                                    0x00000000U

// Field:     [0] AESDONE
//
// Set AES Done interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define AES_IMSET_AESDONE                                           0x00000001U
#define AES_IMSET_AESDONE_M                                         0x00000001U
#define AES_IMSET_AESDONE_S                                                  0U
#define AES_IMSET_AESDONE_SET                                       0x00000001U
#define AES_IMSET_AESDONE_NOEFF                                     0x00000000U

//*****************************************************************************
//
// Register: AES_O_IMCLR
//
//*****************************************************************************
// Field:     [3] CHBDONE
//
// Clear DMA Channel B Done interrupt mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define AES_IMCLR_CHBDONE                                           0x00000008U
#define AES_IMCLR_CHBDONE_M                                         0x00000008U
#define AES_IMCLR_CHBDONE_S                                                  3U
#define AES_IMCLR_CHBDONE_CLR                                       0x00000008U
#define AES_IMCLR_CHBDONE_NOEFF                                     0x00000000U

// Field:     [2] CHADONE
//
// Clear DMA Channel A Done interrupt mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define AES_IMCLR_CHADONE                                           0x00000004U
#define AES_IMCLR_CHADONE_M                                         0x00000004U
#define AES_IMCLR_CHADONE_S                                                  2U
#define AES_IMCLR_CHADONE_CLR                                       0x00000004U
#define AES_IMCLR_CHADONE_NOEFF                                     0x00000000U

// Field:     [1] AESSTART
//
// Clear AES Start interrupt mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define AES_IMCLR_AESSTART                                          0x00000002U
#define AES_IMCLR_AESSTART_M                                        0x00000002U
#define AES_IMCLR_AESSTART_S                                                 1U
#define AES_IMCLR_AESSTART_CLR                                      0x00000002U
#define AES_IMCLR_AESSTART_NOEFF                                    0x00000000U

// Field:     [0] AESDONE
//
// Clear AES Done interrupt mask
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define AES_IMCLR_AESDONE                                           0x00000001U
#define AES_IMCLR_AESDONE_M                                         0x00000001U
#define AES_IMCLR_AESDONE_S                                                  0U
#define AES_IMCLR_AESDONE_CLR                                       0x00000001U
#define AES_IMCLR_AESDONE_NOEFF                                     0x00000000U


#endif // __AES__
