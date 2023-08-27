/******************************************************************************
*  Filename:       hw_bpu_h
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

#ifndef __HW_BPU_H__
#define __HW_BPU_H__

//*****************************************************************************
//
// This section defines the register offsets of
// BPU component
//
//*****************************************************************************
// Breakpoint Control Register
#define BPU_O_BP_CTRL                                               0x00000000U

// Breakpoint Comparator Register 0
#define BPU_O_BP_COMP0                                              0x00000008U

// Breakpoint Comparator Register 1
#define BPU_O_BP_COMP1                                              0x0000000CU

// Breakpoint Comparator Register 2
#define BPU_O_BP_COMP2                                              0x00000010U

// Breakpoint Comparator Register 3
#define BPU_O_BP_COMP3                                              0x00000014U

// Peripheral ID Register 4
#define BPU_O_PIDR4                                                 0x00000FD0U

// Peripheral ID Register 5
#define BPU_O_PIDR5                                                 0x00000FD4U

// Peripheral ID Register 6
#define BPU_O_PIDR6                                                 0x00000FD8U

// Peripheral ID Register 7
#define BPU_O_PIDR7                                                 0x00000FDCU

// Peripheral ID Register 0
#define BPU_O_PIDR0                                                 0x00000FE0U

// Peripheral ID Register 1
#define BPU_O_PIDR1                                                 0x00000FE4U

// Peripheral ID Register 2
#define BPU_O_PIDR2                                                 0x00000FE8U

// Peripheral ID Register 3
#define BPU_O_PIDR3                                                 0x00000FECU

// Component ID Register 0
#define BPU_O_CIDR0                                                 0x00000FF0U

// Component ID Register 1
#define BPU_O_CIDR1                                                 0x00000FF4U

// Component ID Register 2
#define BPU_O_CIDR2                                                 0x00000FF8U

// Component ID Register 3
#define BPU_O_CIDR3                                                 0x00000FFCU

//*****************************************************************************
//
// Register: BPU_O_BP_CTRL
//
//*****************************************************************************
// Field:   [7:4] NUM_CODE
//
// Number of comparators.
#define BPU_BP_CTRL_NUM_CODE_W                                               4U
#define BPU_BP_CTRL_NUM_CODE_M                                      0x000000F0U
#define BPU_BP_CTRL_NUM_CODE_S                                               4U

// Field:     [1] KEY
//
// Key field. To write to the Breakpoint Control Register, you must write a 1
// to this write-only bit. This bit reads as zero.
#define BPU_BP_CTRL_KEY                                             0x00000002U
#define BPU_BP_CTRL_KEY_M                                           0x00000002U
#define BPU_BP_CTRL_KEY_S                                                    1U

// Field:     [0] ENABLE
//
// Breakpoint unit enable bit. DBGRESETn clears the ENABLE bit.
// ENUMs:
// BKPT_EN                  Breakpoint unit enabled
// BKPT_DIS                 Breakpoint unit disabled
#define BPU_BP_CTRL_ENABLE                                          0x00000001U
#define BPU_BP_CTRL_ENABLE_M                                        0x00000001U
#define BPU_BP_CTRL_ENABLE_S                                                 0U
#define BPU_BP_CTRL_ENABLE_BKPT_EN                                  0x00000001U
#define BPU_BP_CTRL_ENABLE_BKPT_DIS                                 0x00000000U

//*****************************************************************************
//
// Register: BPU_O_BP_COMP0
//
//*****************************************************************************
// Field: [31:30] BP_MATCH
//
// This selects what happens when the COMP address is matched
// ENUMs:
// BKPT_COMP_BOTH           set breakpoint on both lower and upper halfwords
// BKPT_COMP_HI             set breakpoint on upper halfword, lower is
//                          unaffected
// BKPT_COMP_LOW            set breakpoint on lower halfword, upper is
//                          unaffected
// BKPT_COMP_NONE           no breakpoint generated
#define BPU_BP_COMP0_BP_MATCH_W                                              2U
#define BPU_BP_COMP0_BP_MATCH_M                                     0xC0000000U
#define BPU_BP_COMP0_BP_MATCH_S                                             30U
#define BPU_BP_COMP0_BP_MATCH_BKPT_COMP_BOTH                        0xC0000000U
#define BPU_BP_COMP0_BP_MATCH_BKPT_COMP_HI                          0x80000000U
#define BPU_BP_COMP0_BP_MATCH_BKPT_COMP_LOW                         0x40000000U
#define BPU_BP_COMP0_BP_MATCH_BKPT_COMP_NONE                        0x00000000U

// Field:  [28:2] COMP
//
// Comparison address, UNKNOWN on reset.
#define BPU_BP_COMP0_COMP_W                                                 27U
#define BPU_BP_COMP0_COMP_M                                         0x1FFFFFFCU
#define BPU_BP_COMP0_COMP_S                                                  2U

// Field:     [0] ENABLE
//
// Compare enable for Breakpoint Comparator Register 0. The ENABLE bit of
// BP_CTRL must also be set to enable comparisons. DBGRESETn clears the ENABLE
// bit.
// ENUMs:
// BKPT_COMP_DIS            Breakpoint Comparator Register 0 compare enabled
// BKPT_COMP_EN             Breakpoint Comparator Register 0 compare disabled
#define BPU_BP_COMP0_ENABLE                                         0x00000001U
#define BPU_BP_COMP0_ENABLE_M                                       0x00000001U
#define BPU_BP_COMP0_ENABLE_S                                                0U
#define BPU_BP_COMP0_ENABLE_BKPT_COMP_DIS                           0x00000001U
#define BPU_BP_COMP0_ENABLE_BKPT_COMP_EN                            0x00000000U

//*****************************************************************************
//
// Register: BPU_O_BP_COMP1
//
//*****************************************************************************
// Field: [31:30] BP_MATCH
//
// This selects what happens when the COMP address is matched
// ENUMs:
// BKPT_COMP_BOTH           Set breakpoint on both lower and upper halfwords
// BKPT_COMP_HI             Set breakpoint on upper halfword, lower is
//                          unaffected
// BKPT_COMP_LOW            Set breakpoint on lower halfword, upper is
//                          unaffected
// BKPT_COMP_NONE           No breakpoint generated
#define BPU_BP_COMP1_BP_MATCH_W                                              2U
#define BPU_BP_COMP1_BP_MATCH_M                                     0xC0000000U
#define BPU_BP_COMP1_BP_MATCH_S                                             30U
#define BPU_BP_COMP1_BP_MATCH_BKPT_COMP_BOTH                        0xC0000000U
#define BPU_BP_COMP1_BP_MATCH_BKPT_COMP_HI                          0x80000000U
#define BPU_BP_COMP1_BP_MATCH_BKPT_COMP_LOW                         0x40000000U
#define BPU_BP_COMP1_BP_MATCH_BKPT_COMP_NONE                        0x00000000U

// Field:  [28:2] COMP
//
// Comparison address. Although it is architecturally Unpredictable whether
// breakpoint matches on the address of the second halfword of a 32-bit
// instruction to generates a debug event, in this processor it is predictable
// and a debug event is generated.
#define BPU_BP_COMP1_COMP_W                                                 27U
#define BPU_BP_COMP1_COMP_M                                         0x1FFFFFFCU
#define BPU_BP_COMP1_COMP_S                                                  2U

// Field:     [0] ENABLE
//
// Comparison address, UNKNOWN on reset.
// ENUMs:
// BKPT_COMP_DIS            Breakpoint Comparator Register 1 compare enabled
// BKPT_COMP_EN             Breakpoint Comparator Register 1 compare disabled
#define BPU_BP_COMP1_ENABLE                                         0x00000001U
#define BPU_BP_COMP1_ENABLE_M                                       0x00000001U
#define BPU_BP_COMP1_ENABLE_S                                                0U
#define BPU_BP_COMP1_ENABLE_BKPT_COMP_DIS                           0x00000001U
#define BPU_BP_COMP1_ENABLE_BKPT_COMP_EN                            0x00000000U

//*****************************************************************************
//
// Register: BPU_O_BP_COMP2
//
//*****************************************************************************
// Field: [31:30] BP_MATCH
//
// This selects what happens when the COMP address is matched
// ENUMs:
// BKPT_COMP_BOTH           Set breakpoint on both lower and upper halfwords
// BKPT_COMP_HI             Set breakpoint on upper halfword, lower is
//                          unaffected
// BKPT_COMP_LOW            Set breakpoint on lower halfword, upper is
//                          unaffected
// BKPT_COMP_NONE           No breakpoint matching
#define BPU_BP_COMP2_BP_MATCH_W                                              2U
#define BPU_BP_COMP2_BP_MATCH_M                                     0xC0000000U
#define BPU_BP_COMP2_BP_MATCH_S                                             30U
#define BPU_BP_COMP2_BP_MATCH_BKPT_COMP_BOTH                        0xC0000000U
#define BPU_BP_COMP2_BP_MATCH_BKPT_COMP_HI                          0x80000000U
#define BPU_BP_COMP2_BP_MATCH_BKPT_COMP_LOW                         0x40000000U
#define BPU_BP_COMP2_BP_MATCH_BKPT_COMP_NONE                        0x00000000U

// Field:  [28:2] COMP
//
// Comparison address, UNKNOWN on reset.
#define BPU_BP_COMP2_COMP_W                                                 27U
#define BPU_BP_COMP2_COMP_M                                         0x1FFFFFFCU
#define BPU_BP_COMP2_COMP_S                                                  2U

// Field:     [0] ENABLE
//
// Compare enable for Breakpoint Comparator Register 2. The ENABLE bit of
// BP_CTRL must also be set to enable comparisons. DBGRESETn clears the ENABLE
// bit.
// ENUMs:
// BKPT_COMP_DIS            Breakpoint Comparator Register 2 compare enabled
// BKPT_COMP_EN             Breakpoint Comparator Register 2 compare disabled
#define BPU_BP_COMP2_ENABLE                                         0x00000001U
#define BPU_BP_COMP2_ENABLE_M                                       0x00000001U
#define BPU_BP_COMP2_ENABLE_S                                                0U
#define BPU_BP_COMP2_ENABLE_BKPT_COMP_DIS                           0x00000001U
#define BPU_BP_COMP2_ENABLE_BKPT_COMP_EN                            0x00000000U

//*****************************************************************************
//
// Register: BPU_O_BP_COMP3
//
//*****************************************************************************
// Field: [31:30] BP_MATCH
//
// This selects what happens when the COMP address is matched
// ENUMs:
// BKPT_COMP_BOTH           Set breakpoint on both lower and upper halfwords
// BKPT_COMP_HI             Set breakpoint on upper halfword, lower is
//                          unaffected
// BKPT_COMP_LOW            Set breakpoint on lower halfword, upper is
//                          unaffected
// BKPT_COMP_NONE           No breakpoint generated
#define BPU_BP_COMP3_BP_MATCH_W                                              2U
#define BPU_BP_COMP3_BP_MATCH_M                                     0xC0000000U
#define BPU_BP_COMP3_BP_MATCH_S                                             30U
#define BPU_BP_COMP3_BP_MATCH_BKPT_COMP_BOTH                        0xC0000000U
#define BPU_BP_COMP3_BP_MATCH_BKPT_COMP_HI                          0x80000000U
#define BPU_BP_COMP3_BP_MATCH_BKPT_COMP_LOW                         0x40000000U
#define BPU_BP_COMP3_BP_MATCH_BKPT_COMP_NONE                        0x00000000U

// Field:  [28:2] COMP
//
// Comparison address, UNKNOWN on reset.
#define BPU_BP_COMP3_COMP_W                                                 27U
#define BPU_BP_COMP3_COMP_M                                         0x1FFFFFFCU
#define BPU_BP_COMP3_COMP_S                                                  2U

// Field:     [0] ENABLE
//
// Compare enable for Breakpoint Comparator Register 3. The ENABLE bit of
// BP_CTRL must also be set to enable comparisons. DBGRESETn clears the ENABLE
// bit.
// ENUMs:
// BKPT_COMP_DIS            Breakpoint Comparator Register 3 compare enabled
// BKPT_COMP_EN             Breakpoint Comparator Register 3 compare disabled
#define BPU_BP_COMP3_ENABLE                                         0x00000001U
#define BPU_BP_COMP3_ENABLE_M                                       0x00000001U
#define BPU_BP_COMP3_ENABLE_S                                                0U
#define BPU_BP_COMP3_ENABLE_BKPT_COMP_DIS                           0x00000001U
#define BPU_BP_COMP3_ENABLE_BKPT_COMP_EN                            0x00000000U

//*****************************************************************************
//
// Register: BPU_O_PIDR4
//
//*****************************************************************************
// Field:   [7:4] SIZE
//
// This is a 4-bit value that indicates the total contiguous size of the memory
// window used by this component in powers of 2 from the standard 4KB. If a
// component only requires the standard 4KB then this should read as 0x0, 4KB
// only, for 8KB set to 0x1, 16KB == 0x2, 32KB == 0x3, and so on.
#define BPU_PIDR4_SIZE_W                                                     4U
#define BPU_PIDR4_SIZE_M                                            0x000000F0U
#define BPU_PIDR4_SIZE_S                                                     4U

// Field:   [3:0] DES_2
//
// Number of JEDEC continuation codes. Indicates the designer of the component
// (along with the identity code)
#define BPU_PIDR4_DES_2_W                                                    4U
#define BPU_PIDR4_DES_2_M                                           0x0000000FU
#define BPU_PIDR4_DES_2_S                                                    0U

//*****************************************************************************
//
// Register: BPU_O_PIDR5
//
//*****************************************************************************
//*****************************************************************************
//
// Register: BPU_O_PIDR6
//
//*****************************************************************************
//*****************************************************************************
//
// Register: BPU_O_PIDR7
//
//*****************************************************************************
//*****************************************************************************
//
// Register: BPU_O_PIDR0
//
//*****************************************************************************
// Field:   [7:0] PART_0
//
// Bits [7:0] of the component's part number. This is selected by the designer
// of the component.
#define BPU_PIDR0_PART_0_W                                                   8U
#define BPU_PIDR0_PART_0_M                                          0x000000FFU
#define BPU_PIDR0_PART_0_S                                                   0U

//*****************************************************************************
//
// Register: BPU_O_PIDR1
//
//*****************************************************************************
// Field:   [7:4] DES_0
//
// Bits [3:0] of the JEDEC identity code indicating the designer of the
// component (along with the continuation code)
#define BPU_PIDR1_DES_0_W                                                    4U
#define BPU_PIDR1_DES_0_M                                           0x000000F0U
#define BPU_PIDR1_DES_0_S                                                    4U

// Field:   [3:0] PART_1
//
// Bits [11:8] of the component's part number. This is selected by the designer
// of the component.
#define BPU_PIDR1_PART_1_W                                                   4U
#define BPU_PIDR1_PART_1_M                                          0x0000000FU
#define BPU_PIDR1_PART_1_S                                                   0U

//*****************************************************************************
//
// Register: BPU_O_PIDR2
//
//*****************************************************************************
// Field:   [7:4] REVISION
//
// The Revision field is an incremental value starting at 0x0 for the first
// design of this component. This only increases by 1 for both major and minor
// revisions and is simply used as a look-up to establish the exact major/minor
// revision.
#define BPU_PIDR2_REVISION_W                                                 4U
#define BPU_PIDR2_REVISION_M                                        0x000000F0U
#define BPU_PIDR2_REVISION_S                                                 4U

// Field:     [3] JEDEC
//
// Always set. Indicates that a JEDEC assigned value is used
#define BPU_PIDR2_JEDEC                                             0x00000008U
#define BPU_PIDR2_JEDEC_M                                           0x00000008U
#define BPU_PIDR2_JEDEC_S                                                    3U

// Field:   [2:0] DES_1
//
// Bits [6:4] of the JEDEC identity code indicating the designer of the
// component (along with the continuation code)
#define BPU_PIDR2_DES_1_W                                                    3U
#define BPU_PIDR2_DES_1_M                                           0x00000007U
#define BPU_PIDR2_DES_1_S                                                    0U

//*****************************************************************************
//
// Register: BPU_O_PIDR3
//
//*****************************************************************************
// Field:   [7:4] REVAND
//
// This field indicates minor errata fixes specific to this design, for example
// metal fixes after implementation. In most cases this field is zero. It is
// recommended that component designers ensure this field can be changed by a
// metal fix if required, for example by driving it from registers that reset
// to zero.
#define BPU_PIDR3_REVAND_W                                                   4U
#define BPU_PIDR3_REVAND_M                                          0x000000F0U
#define BPU_PIDR3_REVAND_S                                                   4U

// Field:   [3:0] CMOD
//
// Where the component is reusable IP, this value indicates if the customer has
// modified the behavior of the component. In most cases this field is zero.
#define BPU_PIDR3_CMOD_W                                                     4U
#define BPU_PIDR3_CMOD_M                                            0x0000000FU
#define BPU_PIDR3_CMOD_S                                                     0U

//*****************************************************************************
//
// Register: BPU_O_CIDR0
//
//*****************************************************************************
// Field:   [7:0] PRMBL_0
//
// Contains bits [7:0] of the component identification
#define BPU_CIDR0_PRMBL_0_W                                                  8U
#define BPU_CIDR0_PRMBL_0_M                                         0x000000FFU
#define BPU_CIDR0_PRMBL_0_S                                                  0U

//*****************************************************************************
//
// Register: BPU_O_CIDR1
//
//*****************************************************************************
// Field:   [7:4] CLASS
//
// Class of the component. E.g. ROM table, CoreSight component etc. Constitutes
// bits [15:12] of the component identification.
#define BPU_CIDR1_CLASS_W                                                    4U
#define BPU_CIDR1_CLASS_M                                           0x000000F0U
#define BPU_CIDR1_CLASS_S                                                    4U

// Field:   [3:0] PRMBL_1
//
// Contains bits [11:8] of the component identification
#define BPU_CIDR1_PRMBL_1_W                                                  4U
#define BPU_CIDR1_PRMBL_1_M                                         0x0000000FU
#define BPU_CIDR1_PRMBL_1_S                                                  0U

//*****************************************************************************
//
// Register: BPU_O_CIDR2
//
//*****************************************************************************
// Field:   [7:0] PRMBL_2
//
// Contains bits [23:16] of the component identification
#define BPU_CIDR2_PRMBL_2_W                                                  8U
#define BPU_CIDR2_PRMBL_2_M                                         0x000000FFU
#define BPU_CIDR2_PRMBL_2_S                                                  0U

//*****************************************************************************
//
// Register: BPU_O_CIDR3
//
//*****************************************************************************
// Field:   [7:0] PRMBL_3
//
// Contains bits [31:24] of the component identification
#define BPU_CIDR3_PRMBL_3_W                                                  8U
#define BPU_CIDR3_PRMBL_3_M                                         0x000000FFU
#define BPU_CIDR3_PRMBL_3_S                                                  0U


#endif // __BPU__
