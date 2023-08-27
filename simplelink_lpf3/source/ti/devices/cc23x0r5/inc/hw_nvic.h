/******************************************************************************
*  Filename:       hw_nvic_h
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

#ifndef __HW_NVIC_H__
#define __HW_NVIC_H__

//*****************************************************************************
//
// This section defines the register offsets of
// NVIC component
//
//*****************************************************************************
// Interrupt Set-Enable Register
#define NVIC_O_ISER                                                 0x00000100U

// Interrupt Clear-Enable Register
#define NVIC_O_ICER                                                 0x00000180U

// Interrupt Set-Pending Register
#define NVIC_O_ISPR                                                 0x00000200U

// Interrupt Clear-Pending Register
#define NVIC_O_ICPR                                                 0x00000280U

// Interrupt Priority Register 0
#define NVIC_O_IPR0                                                 0x00000400U

// Interrupt Priority Register 1
#define NVIC_O_IPR1                                                 0x00000404U

// Interrupt Priority Register 2
#define NVIC_O_IPR2                                                 0x00000408U

// Interrupt Priority Register 3
#define NVIC_O_IPR3                                                 0x0000040CU

// Interrupt Priority Register 4
#define NVIC_O_IPR4                                                 0x00000410U

// Interrupt Priority Register 5
#define NVIC_O_IPR5                                                 0x00000414U

// Interrupt Priority Register 6
#define NVIC_O_IPR6                                                 0x00000418U

// Interrupt Priority Register 7
#define NVIC_O_IPR7                                                 0x0000041CU

//*****************************************************************************
//
// Register: NVIC_O_ISER
//
//*****************************************************************************
// Field:  [31:0] SETENA
//
// Writing 0 to a SETENA bit has no effect, writing 1 to a bit enables the
// corresponding interrupt. Reading the bit returns its current enable state.
// Reset clears the SETENA fields.
#define NVIC_ISER_SETENA_W                                                  32U
#define NVIC_ISER_SETENA_M                                          0xFFFFFFFFU
#define NVIC_ISER_SETENA_S                                                   0U

//*****************************************************************************
//
// Register: NVIC_O_ICER
//
//*****************************************************************************
// Field:  [31:0] CLRENA
//
// Writing 0 to a CLRENA bit has no effect, writing 1 to a bit disables the
// corresponding interrupt. Reading the bit returns its current enable state.
// Reset clears the CLRENA field.
#define NVIC_ICER_CLRENA_W                                                  32U
#define NVIC_ICER_CLRENA_M                                          0xFFFFFFFFU
#define NVIC_ICER_CLRENA_S                                                   0U

//*****************************************************************************
//
// Register: NVIC_O_ISPR
//
//*****************************************************************************
// Field:  [31:0] SETPEND
//
// Interrupt set-pending bits for a: Write: 1 = pend interrupt 0 = no effect;
// Read: 1 = interrupt is pending 0 = interrupt is not pending.
#define NVIC_ISPR_SETPEND_W                                                 32U
#define NVIC_ISPR_SETPEND_M                                         0xFFFFFFFFU
#define NVIC_ISPR_SETPEND_S                                                  0U

//*****************************************************************************
//
// Register: NVIC_O_ICPR
//
//*****************************************************************************
// Field:  [31:0] CLRPEND
//
// Interrupt clear-pending bits: Write: 1 = clear interrupt pending bit, 0 = no
// effect; Read: 1 = interrupt is pending 0 = interrupt is not pending.
#define NVIC_ICPR_CLRPEND_W                                                 32U
#define NVIC_ICPR_CLRPEND_M                                         0xFFFFFFFFU
#define NVIC_ICPR_CLRPEND_S                                                  0U

//*****************************************************************************
//
// Register: NVIC_O_IPR0
//
//*****************************************************************************
// Field: [31:30] IP_3
//
// Priority of interrupt 3
#define NVIC_IPR0_IP_3_W                                                     2U
#define NVIC_IPR0_IP_3_M                                            0xC0000000U
#define NVIC_IPR0_IP_3_S                                                    30U

// Field: [23:22] IP_2
//
// Priority of interrupt 2
#define NVIC_IPR0_IP_2_W                                                     2U
#define NVIC_IPR0_IP_2_M                                            0x00C00000U
#define NVIC_IPR0_IP_2_S                                                    22U

// Field: [15:14] IP_1
//
// Priority of interrupt 1
#define NVIC_IPR0_IP_1_W                                                     2U
#define NVIC_IPR0_IP_1_M                                            0x0000C000U
#define NVIC_IPR0_IP_1_S                                                    14U

// Field:   [7:6] IP_0
//
// Priority of interrupt 0
#define NVIC_IPR0_IP_0_W                                                     2U
#define NVIC_IPR0_IP_0_M                                            0x000000C0U
#define NVIC_IPR0_IP_0_S                                                     6U

//*****************************************************************************
//
// Register: NVIC_O_IPR1
//
//*****************************************************************************
// Field: [31:30] IP_7
//
// Priority of interrupt 7
#define NVIC_IPR1_IP_7_W                                                     2U
#define NVIC_IPR1_IP_7_M                                            0xC0000000U
#define NVIC_IPR1_IP_7_S                                                    30U

// Field: [23:22] IP_6
//
// Priority of interrupt 6
#define NVIC_IPR1_IP_6_W                                                     2U
#define NVIC_IPR1_IP_6_M                                            0x00C00000U
#define NVIC_IPR1_IP_6_S                                                    22U

// Field: [15:14] IP_5
//
// Priority of interrupt 5
#define NVIC_IPR1_IP_5_W                                                     2U
#define NVIC_IPR1_IP_5_M                                            0x0000C000U
#define NVIC_IPR1_IP_5_S                                                    14U

// Field:   [7:6] IP_4
//
// Priority of interrupt 4
#define NVIC_IPR1_IP_4_W                                                     2U
#define NVIC_IPR1_IP_4_M                                            0x000000C0U
#define NVIC_IPR1_IP_4_S                                                     6U

//*****************************************************************************
//
// Register: NVIC_O_IPR2
//
//*****************************************************************************
// Field: [31:30] IP_11
//
// Priority of interrupt 11
#define NVIC_IPR2_IP_11_W                                                    2U
#define NVIC_IPR2_IP_11_M                                           0xC0000000U
#define NVIC_IPR2_IP_11_S                                                   30U

// Field: [23:22] IP_10
//
// Priority of interrupt 10
#define NVIC_IPR2_IP_10_W                                                    2U
#define NVIC_IPR2_IP_10_M                                           0x00C00000U
#define NVIC_IPR2_IP_10_S                                                   22U

// Field: [15:14] IP_9
//
// Priority of interrupt 9
#define NVIC_IPR2_IP_9_W                                                     2U
#define NVIC_IPR2_IP_9_M                                            0x0000C000U
#define NVIC_IPR2_IP_9_S                                                    14U

// Field:   [7:6] IP_8
//
// Priority of interrupt 8
#define NVIC_IPR2_IP_8_W                                                     2U
#define NVIC_IPR2_IP_8_M                                            0x000000C0U
#define NVIC_IPR2_IP_8_S                                                     6U

//*****************************************************************************
//
// Register: NVIC_O_IPR3
//
//*****************************************************************************
// Field: [31:30] IP_15
//
// Priority of interrupt 15
#define NVIC_IPR3_IP_15_W                                                    2U
#define NVIC_IPR3_IP_15_M                                           0xC0000000U
#define NVIC_IPR3_IP_15_S                                                   30U

// Field: [23:22] IP_14
//
// Priority of interrupt 14
#define NVIC_IPR3_IP_14_W                                                    2U
#define NVIC_IPR3_IP_14_M                                           0x00C00000U
#define NVIC_IPR3_IP_14_S                                                   22U

// Field: [15:14] IP_13
//
// Priority of interrupt 13
#define NVIC_IPR3_IP_13_W                                                    2U
#define NVIC_IPR3_IP_13_M                                           0x0000C000U
#define NVIC_IPR3_IP_13_S                                                   14U

// Field:   [7:6] IP_12
//
// Priority of interrupt 12
#define NVIC_IPR3_IP_12_W                                                    2U
#define NVIC_IPR3_IP_12_M                                           0x000000C0U
#define NVIC_IPR3_IP_12_S                                                    6U

//*****************************************************************************
//
// Register: NVIC_O_IPR4
//
//*****************************************************************************
// Field: [31:30] IP_19
//
// Priority of interrupt 19
#define NVIC_IPR4_IP_19_W                                                    2U
#define NVIC_IPR4_IP_19_M                                           0xC0000000U
#define NVIC_IPR4_IP_19_S                                                   30U

// Field: [23:22] IP_18
//
// Priority of interrupt 18
#define NVIC_IPR4_IP_18_W                                                    2U
#define NVIC_IPR4_IP_18_M                                           0x00C00000U
#define NVIC_IPR4_IP_18_S                                                   22U

// Field: [15:14] IP_17
//
// Priority of interrupt 17
#define NVIC_IPR4_IP_17_W                                                    2U
#define NVIC_IPR4_IP_17_M                                           0x0000C000U
#define NVIC_IPR4_IP_17_S                                                   14U

// Field:   [7:6] IP_16
//
// Priority of interrupt 16
#define NVIC_IPR4_IP_16_W                                                    2U
#define NVIC_IPR4_IP_16_M                                           0x000000C0U
#define NVIC_IPR4_IP_16_S                                                    6U

//*****************************************************************************
//
// Register: NVIC_O_IPR5
//
//*****************************************************************************
// Field: [31:30] IP_23
//
// Priority of interrupt 23
#define NVIC_IPR5_IP_23_W                                                    2U
#define NVIC_IPR5_IP_23_M                                           0xC0000000U
#define NVIC_IPR5_IP_23_S                                                   30U

// Field: [23:22] IP_22
//
// Priority of interrupt 22
#define NVIC_IPR5_IP_22_W                                                    2U
#define NVIC_IPR5_IP_22_M                                           0x00C00000U
#define NVIC_IPR5_IP_22_S                                                   22U

// Field: [15:14] IP_21
//
// Priority of interrupt 21
#define NVIC_IPR5_IP_21_W                                                    2U
#define NVIC_IPR5_IP_21_M                                           0x0000C000U
#define NVIC_IPR5_IP_21_S                                                   14U

// Field:   [7:6] IP_20
//
// Priority of interrupt 20
#define NVIC_IPR5_IP_20_W                                                    2U
#define NVIC_IPR5_IP_20_M                                           0x000000C0U
#define NVIC_IPR5_IP_20_S                                                    6U

//*****************************************************************************
//
// Register: NVIC_O_IPR6
//
//*****************************************************************************
// Field: [31:30] IP_27
//
// Priority of interrupt 27
#define NVIC_IPR6_IP_27_W                                                    2U
#define NVIC_IPR6_IP_27_M                                           0xC0000000U
#define NVIC_IPR6_IP_27_S                                                   30U

// Field: [23:22] IP_26
//
// Priority of interrupt 26
#define NVIC_IPR6_IP_26_W                                                    2U
#define NVIC_IPR6_IP_26_M                                           0x00C00000U
#define NVIC_IPR6_IP_26_S                                                   22U

// Field: [15:14] IP_25
//
// Priority of interrupt 25
#define NVIC_IPR6_IP_25_W                                                    2U
#define NVIC_IPR6_IP_25_M                                           0x0000C000U
#define NVIC_IPR6_IP_25_S                                                   14U

// Field:   [7:6] IP_24
//
// Priority of interrupt 24
#define NVIC_IPR6_IP_24_W                                                    2U
#define NVIC_IPR6_IP_24_M                                           0x000000C0U
#define NVIC_IPR6_IP_24_S                                                    6U

//*****************************************************************************
//
// Register: NVIC_O_IPR7
//
//*****************************************************************************
// Field: [31:30] IP_31
//
// Priority of interrupt 31
#define NVIC_IPR7_IP_31_W                                                    2U
#define NVIC_IPR7_IP_31_M                                           0xC0000000U
#define NVIC_IPR7_IP_31_S                                                   30U

// Field: [23:22] IP_30
//
// Priority of interrupt 30
#define NVIC_IPR7_IP_30_W                                                    2U
#define NVIC_IPR7_IP_30_M                                           0x00C00000U
#define NVIC_IPR7_IP_30_S                                                   22U

// Field: [15:14] IP_29
//
// Priority of interrupt 29
#define NVIC_IPR7_IP_29_W                                                    2U
#define NVIC_IPR7_IP_29_M                                           0x0000C000U
#define NVIC_IPR7_IP_29_S                                                   14U

// Field:   [7:6] IP_28
//
// Priority of interrupt 28
#define NVIC_IPR7_IP_28_W                                                    2U
#define NVIC_IPR7_IP_28_M                                           0x000000C0U
#define NVIC_IPR7_IP_28_S                                                    6U


#endif // __NVIC__
