/******************************************************************************
*  Filename:       hw_scscs_h
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

#ifndef __HW_SCSCS_H__
#define __HW_SCSCS_H__

//*****************************************************************************
//
// This section defines the register offsets of
// SCSCS component
//
//*****************************************************************************
// Peripheral ID Register 4
#define SCSCS_O_PIDR4                                               0x00000010U

// Peripheral ID Register 5
#define SCSCS_O_PIDR5                                               0x00000014U

// Peripheral ID Register 6
#define SCSCS_O_PIDR6                                               0x00000018U

// Peripheral ID Register 7
#define SCSCS_O_PIDR7                                               0x0000001CU

// Peripheral ID Register 0
#define SCSCS_O_PIDR0                                               0x00000020U

// Peripheral ID Register 1
#define SCSCS_O_PIDR1                                               0x00000024U

// Peripheral ID Register 2
#define SCSCS_O_PIDR2                                               0x00000028U

// Peripheral ID Register 3
#define SCSCS_O_PIDR3                                               0x0000002CU

// Component ID Register 0
#define SCSCS_O_CIDR0                                               0x00000030U

// Component ID Register 1
#define SCSCS_O_CIDR1                                               0x00000034U

// Component ID Register 2
#define SCSCS_O_CIDR2                                               0x00000038U

// Component ID Register 3
#define SCSCS_O_CIDR3                                               0x0000003CU

//*****************************************************************************
//
// Register: SCSCS_O_PIDR4
//
//*****************************************************************************
// Field:   [7:4] SIZE
//
// This is a 4-bit value that indicates the total contiguous size of the memory
// window used by this component in powers of 2 from the standard 4KB. If a
// component only requires the standard 4KB then this should read as 0x0, 4KB
// only, for 8KB set to 0x1, 16KB == 0x2, 32KB == 0x3, and so on.
#define SCSCS_PIDR4_SIZE_W                                                   4U
#define SCSCS_PIDR4_SIZE_M                                          0x000000F0U
#define SCSCS_PIDR4_SIZE_S                                                   4U

// Field:   [3:0] DES_2
//
// Number of JEDEC continuation codes. Indicates the designer of the component
// (along with the identity code)
#define SCSCS_PIDR4_DES_2_W                                                  4U
#define SCSCS_PIDR4_DES_2_M                                         0x0000000FU
#define SCSCS_PIDR4_DES_2_S                                                  0U

//*****************************************************************************
//
// Register: SCSCS_O_PIDR5
//
//*****************************************************************************
//*****************************************************************************
//
// Register: SCSCS_O_PIDR6
//
//*****************************************************************************
//*****************************************************************************
//
// Register: SCSCS_O_PIDR7
//
//*****************************************************************************
//*****************************************************************************
//
// Register: SCSCS_O_PIDR0
//
//*****************************************************************************
// Field:   [7:0] PART_0
//
// Bits [7:0] of the component's part number. This is selected by the designer
// of the component.
#define SCSCS_PIDR0_PART_0_W                                                 8U
#define SCSCS_PIDR0_PART_0_M                                        0x000000FFU
#define SCSCS_PIDR0_PART_0_S                                                 0U

//*****************************************************************************
//
// Register: SCSCS_O_PIDR1
//
//*****************************************************************************
// Field:   [7:4] DES_0
//
// Bits [3:0] of the JEDEC identity code indicating the designer of the
// component (along with the continuation code)
#define SCSCS_PIDR1_DES_0_W                                                  4U
#define SCSCS_PIDR1_DES_0_M                                         0x000000F0U
#define SCSCS_PIDR1_DES_0_S                                                  4U

// Field:   [3:0] PART_1
//
// Bits [11:8] of the component's part number. This is selected by the designer
// of the component.
#define SCSCS_PIDR1_PART_1_W                                                 4U
#define SCSCS_PIDR1_PART_1_M                                        0x0000000FU
#define SCSCS_PIDR1_PART_1_S                                                 0U

//*****************************************************************************
//
// Register: SCSCS_O_PIDR2
//
//*****************************************************************************
// Field:   [7:4] REVISION
//
// The Revision field is an incremental value starting at 0x0 for the first
// design of this component. This only increases by 1 for both major and minor
// revisions and is simply used as a look-up to establish the exact major/minor
// revision.
#define SCSCS_PIDR2_REVISION_W                                               4U
#define SCSCS_PIDR2_REVISION_M                                      0x000000F0U
#define SCSCS_PIDR2_REVISION_S                                               4U

// Field:     [3] JEDEC
//
// Always set. Indicates that a JEDEC assigned value is used
#define SCSCS_PIDR2_JEDEC                                           0x00000008U
#define SCSCS_PIDR2_JEDEC_M                                         0x00000008U
#define SCSCS_PIDR2_JEDEC_S                                                  3U

// Field:   [2:0] DES_1
//
// Bits [6:4] of the JEDEC identity code indicating the designer of the
// component (along with the continuation code)
#define SCSCS_PIDR2_DES_1_W                                                  3U
#define SCSCS_PIDR2_DES_1_M                                         0x00000007U
#define SCSCS_PIDR2_DES_1_S                                                  0U

//*****************************************************************************
//
// Register: SCSCS_O_PIDR3
//
//*****************************************************************************
// Field:   [7:4] REVAND
//
// This field indicates minor errata fixes specific to this design, for example
// metal fixes after implementation. In most cases this field is zero. It is
// recommended that component designers ensure this field can be changed by a
// metal fix if required, for example by driving it from registers that reset
// to zero.
#define SCSCS_PIDR3_REVAND_W                                                 4U
#define SCSCS_PIDR3_REVAND_M                                        0x000000F0U
#define SCSCS_PIDR3_REVAND_S                                                 4U

// Field:   [3:0] CMOD
//
// Where the component is reusable IP, this value indicates if the customer has
// modified the behavior of the component. In most cases this field is zero.
#define SCSCS_PIDR3_CMOD_W                                                   4U
#define SCSCS_PIDR3_CMOD_M                                          0x0000000FU
#define SCSCS_PIDR3_CMOD_S                                                   0U

//*****************************************************************************
//
// Register: SCSCS_O_CIDR0
//
//*****************************************************************************
// Field:   [7:0] PRMBL_0
//
// Contains bits [7:0] of the component identification
#define SCSCS_CIDR0_PRMBL_0_W                                                8U
#define SCSCS_CIDR0_PRMBL_0_M                                       0x000000FFU
#define SCSCS_CIDR0_PRMBL_0_S                                                0U

//*****************************************************************************
//
// Register: SCSCS_O_CIDR1
//
//*****************************************************************************
// Field:   [7:4] CLASS
//
// Class of the component. E.g. ROM table, CoreSight component etc. Constitutes
// bits [15:12] of the component identification.
#define SCSCS_CIDR1_CLASS_W                                                  4U
#define SCSCS_CIDR1_CLASS_M                                         0x000000F0U
#define SCSCS_CIDR1_CLASS_S                                                  4U

// Field:   [3:0] PRMBL_1
//
// Contains bits [11:8] of the component identification
#define SCSCS_CIDR1_PRMBL_1_W                                                4U
#define SCSCS_CIDR1_PRMBL_1_M                                       0x0000000FU
#define SCSCS_CIDR1_PRMBL_1_S                                                0U

//*****************************************************************************
//
// Register: SCSCS_O_CIDR2
//
//*****************************************************************************
// Field:   [7:0] PRMBL_2
//
// Contains bits [23:16] of the component identification
#define SCSCS_CIDR2_PRMBL_2_W                                                8U
#define SCSCS_CIDR2_PRMBL_2_M                                       0x000000FFU
#define SCSCS_CIDR2_PRMBL_2_S                                                0U

//*****************************************************************************
//
// Register: SCSCS_O_CIDR3
//
//*****************************************************************************
// Field:   [7:0] PRMBL_3
//
// Contains bits [31:24] of the component identification
#define SCSCS_CIDR3_PRMBL_3_W                                                8U
#define SCSCS_CIDR3_PRMBL_3_M                                       0x000000FFU
#define SCSCS_CIDR3_PRMBL_3_S                                                0U


#endif // __SCSCS__
