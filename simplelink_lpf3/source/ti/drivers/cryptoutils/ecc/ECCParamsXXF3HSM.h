/*
 * Copyright (c) 2024-2025, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== ECCParamsXXF3HSM.h ========
 *
 *  This file contains structure declarations for various ECC curves for use
 *  on CC27XX devices.
 */

/* For curves with parameter lengths that are not divisible by 4 (which
 * is only the case on NISTP521 curves), 2 bytes of 0s must be added to
 * the parameter buffers
 */
#define HSM_PADDED_PARAM_BYTES 2

/* The HSM requires base points of ECC multiplications to have padding bytes
 * between the X and Y components, depending on the number of words that are
 * required per component.
 */
#define PADDING_BYTES_EVEN 8
#define PADDING_BYTES_ODD  12

/*!
 *  @defgroup nistp192_params NIST P192 curve params
 *  @{
 */

/*!
 *  @brief Length of NIST P192 curve parameters in bytes
 */
#define ECCParams_NISTP192_LENGTH 24

/*!
 *  @brief Union to access ECC_NISTP192 curve params in bytes or words.
 */
typedef union
{
    uint8_t byte[ECCParams_NISTP192_LENGTH];
    uint32_t word[ECCParams_NISTP192_LENGTH / sizeof(uint32_t)];
} ECC_NISTP192_Param;

/*!
 *  @brief X coordinate of the generator point of the ECC_NISTP192 curve.
 */
extern const ECC_NISTP192_Param ECC_NISTP192_generatorX;

/*!
 *  @brief Y coordinate of the generator point of the ECC_NISTP192 curve.
 */
extern const ECC_NISTP192_Param ECC_NISTP192_generatorY;

/*!
 *  @brief Prime of the generator point of the ECC_NISTP192 curve.
 */
extern const ECC_NISTP192_Param ECC_NISTP192_prime;

/*!
 *  @brief 'a' constant of the ECC_NISTP192 curve when expressed in short
 *  Weierstrass form (y^2 = x^3 + a*x + b).
 */
extern const ECC_NISTP192_Param ECC_NISTP192_a;

/*!
 *  @brief 'b' constant of the ECC_NISTP192 curve when expressed in short
 *  Weierstrass form (y^2 = x^3 + a*x + b).
 */
extern const ECC_NISTP192_Param ECC_NISTP192_b;

/*!
 *  @brief Order of the generator point of the ECC_NISTP192 curve.
 */
extern const ECC_NISTP192_Param ECC_NISTP192_order;

/*!
 *  @brief 'k' in Montgomery domain of the ECC_NISTP192 curve.
 */
extern const ECC_NISTP192_Param ECC_NISTP192_k_mont;

/*!
 *  @brief 'a' in Montgomery domain of the ECC_NISTP192 curve.
 */
extern const ECC_NISTP192_Param ECC_NISTP192_a_mont;

/*!
 *  @brief 'b' in Montgomery domain of the ECC_NISTP192 curve.
 */
extern const ECC_NISTP192_Param ECC_NISTP192_b_mont;

/*! @} */ /* end of nistp192_params */

/*!
 *  @defgroup nistp384_params NIST P384 curve params
 *  @{
 */

/*!
 *  @brief Length of NIST P384 curve parameters in bytes
 */
#define ECCParams_NISTP384_LENGTH 48

/*!
 *  @brief Union to access ECC_NISTP384 curve params in bytes or words.
 */
typedef union
{
    uint8_t byte[ECCParams_NISTP384_LENGTH];
    uint32_t word[ECCParams_NISTP384_LENGTH / sizeof(uint32_t)];
} ECC_NISTP384_Param;

/*!
 *  @brief X coordinate of the generator point of the ECC_NISTP384 curve.
 */
extern const ECC_NISTP384_Param ECC_NISTP384_generatorX;

/*!
 *  @brief Y coordinate of the generator point of the ECC_NISTP384 curve.
 */
extern const ECC_NISTP384_Param ECC_NISTP384_generatorY;

/*!
 *  @brief Prime of the generator point of the ECC_NISTP384 curve.
 */
extern const ECC_NISTP384_Param ECC_NISTP384_prime;

/*!
 *  @brief 'a' constant of the ECC_NISTP384 curve when expressed in short
 *  Weierstrass form (y^2 = x^3 + a*x + b).
 */
extern const ECC_NISTP384_Param ECC_NISTP384_a;

/*!
 *  @brief 'b' constant of the ECC_NISTP384 curve when expressed in short
 *  Weierstrass form (y^2 = x^3 + a*x + b).
 */
extern const ECC_NISTP384_Param ECC_NISTP384_b;

/*!
 *  @brief Order of the generator point of the ECC_NISTP384 curve.
 */
extern const ECC_NISTP384_Param ECC_NISTP384_order;

/*!
 *  @brief 'k' in Montgomery domain of the ECC_NISTP384 curve.
 */
extern const ECC_NISTP384_Param ECC_NISTP384_k_mont;

/*!
 *  @brief 'a' in Montgomery domain of the ECC_NISTP384 curve.
 */
extern const ECC_NISTP384_Param ECC_NISTP384_a_mont;

/*!
 *  @brief 'b' in Montgomery domain of the ECC_NISTP384 curve.
 */
extern const ECC_NISTP384_Param ECC_NISTP384_b_mont;

/*! @} */ /* end of nistp384_params */

/*!
 *  @defgroup nistp521_params NIST P521 curve params
 *  @{
 */

/*!
 *  @brief Length of NIST P521 curve parameters in bytes
 */
#define ECCParams_NISTP521_LENGTH 66

/*!
 *  @brief Length in bytes of NISTP521 curve parameters including the padded
 *  0s so that the HSM is provided curve parameters with length that is divisible
 *  by 4, per its requirements.
 */
#define ECC_NISTP521_PARAM_LENGTH_WITH_PADDED_BYTES (ECCParams_NISTP521_LENGTH + HSM_PADDED_PARAM_BYTES)

/*!
 *  @brief Union to access ECC_NISTP521 curve params in bytes or words.
 */
typedef union
{
    uint8_t byte[ECC_NISTP521_PARAM_LENGTH_WITH_PADDED_BYTES];
    uint32_t word[ECC_NISTP521_PARAM_LENGTH_WITH_PADDED_BYTES / sizeof(uint32_t)];
} ECC_NISTP521_Param;

/*!
 *  @brief X coordinate of the generator point of the ECC_NISTP521 curve.
 */
extern const ECC_NISTP521_Param ECC_NISTP521_generatorX;

/*!
 *  @brief Y coordinate of the generator point of the ECC_NISTP521 curve.
 */
extern const ECC_NISTP521_Param ECC_NISTP521_generatorY;

/*!
 *  @brief Prime of the generator point of the ECC_NISTP521 curve.
 */
extern const ECC_NISTP521_Param ECC_NISTP521_prime;

/*!
 *  @brief 'a' constant of the ECC_NISTP521 curve when expressed in short
 *  Weierstrass form (y^2 = x^3 + a*x + b).
 */
extern const ECC_NISTP521_Param ECC_NISTP521_a;

/*!
 *  @brief 'b' constant of the ECC_NISTP521 curve when expressed in short
 *  Weierstrass form (y^2 = x^3 + a*x + b).
 */
extern const ECC_NISTP521_Param ECC_NISTP521_b;

/*!
 *  @brief Order of the generator point of the ECC_NISTP521 curve.
 */
extern const ECC_NISTP521_Param ECC_NISTP521_order;

/*!
 *  @brief 'k' in Montgomery domain of the ECC_NISTP521 curve.
 */
extern const ECC_NISTP521_Param ECC_NISTP521_k_mont;

/*!
 *  @brief 'a' in Montgomery domain of the ECC_NISTP521 curve.
 */
extern const ECC_NISTP521_Param ECC_NISTP521_a_mont;

/*!
 *  @brief 'b' in Montgomery domain of the ECC_NISTP521 curve.
 */
extern const ECC_NISTP521_Param ECC_NISTP521_b_mont;

/*! @} */ /* end of nistp521_params */

/*!
 *  @defgroup BrainpoolP256R1_params BrainpoolP256R1 curve params
 *  @{
 */

/*!
 *  @brief Length of BrainpoolP256R1 curve parameters in bytes
 */
#define ECCParams_BrainpoolP256R1_LENGTH 32

/*!
 *  @brief Union to access ECC_BrainpoolP256R1 curve params in bytes or words.
 */
typedef union
{
    uint8_t byte[ECCParams_BrainpoolP256R1_LENGTH];
    uint32_t word[ECCParams_BrainpoolP256R1_LENGTH / sizeof(uint32_t)];
} ECC_BrainpoolP256R1_Param;

/*!
 *  @brief X coordinate of the generator point of the ECC_BrainpoolP256R1 curve.
 */
extern const ECC_BrainpoolP256R1_Param ECC_BrainpoolP256R1_generatorX;

/*!
 *  @brief Y coordinate of the generator point of the ECC_BrainpoolP256R1 curve.
 */
extern const ECC_BrainpoolP256R1_Param ECC_BrainpoolP256R1_generatorY;

/*!
 *  @brief Prime of the generator point of the ECC_BrainpoolP256R1 curve.
 */
extern const ECC_BrainpoolP256R1_Param ECC_BrainpoolP256R1_prime;

/*!
 *  @brief 'a' constant of the ECC_BrainpoolP256R1 curve when expressed in short
 *  Weierstrass form (y^2 = x^3 + a*x + b).
 */
extern const ECC_BrainpoolP256R1_Param ECC_BrainpoolP256R1_a;

/*!
 *  @brief 'b' constant of the ECC_BrainpoolP256R1 curve when expressed in short
 *  Weierstrass form (y^2 = x^3 + a*x + b).
 */
extern const ECC_BrainpoolP256R1_Param ECC_BrainpoolP256R1_b;

/*!
 *  @brief Order of the generator point of the ECC_BrainpoolP256R1 curve.
 */
extern const ECC_BrainpoolP256R1_Param ECC_BrainpoolP256R1_order;

/*!
 *  @brief 'k' in Montgomery domain of the ECC_BrainpoolP256R1 curve.
 */
extern const ECC_BrainpoolP256R1_Param ECC_BrainpoolP256R1_k_mont;

/*!
 *  @brief 'a' in Montgomery domain of the ECC_BrainpoolP256R1 curve.
 */
extern const ECC_BrainpoolP256R1_Param ECC_BrainpoolP256R1_a_mont;

/*!
 *  @brief 'b' in Montgomery domain of the ECC_BrainpoolP256R1 curve.
 */
extern const ECC_BrainpoolP256R1_Param ECC_BrainpoolP256R1_b_mont;

/*! @} */ /* end of BrainpoolP256R1_params */

/*!
 *  @defgroup BrainpoolP384R1_params BrainpoolP384R1 curve params
 *  @{
 */

/*!
 *  @brief Length of BrainpoolP384R1 curve parameters in bytes
 */
#define ECCParams_BrainpoolP384R1_LENGTH 48

/*!
 *  @brief Union to access ECC_BrainpoolP384R1 curve params in bytes or words.
 */
typedef union
{
    uint8_t byte[ECCParams_BrainpoolP384R1_LENGTH];
    uint32_t word[ECCParams_BrainpoolP384R1_LENGTH / sizeof(uint32_t)];
} ECC_BrainpoolP384R1_Param;

/*!
 *  @brief X coordinate of the generator point of the ECC_BrainpoolP384R1 curve.
 */
extern const ECC_BrainpoolP384R1_Param ECC_BrainpoolP384R1_generatorX;

/*!
 *  @brief Y coordinate of the generator point of the ECC_BrainpoolP384R1 curve.
 */
extern const ECC_BrainpoolP384R1_Param ECC_BrainpoolP384R1_generatorY;

/*!
 *  @brief Prime of the generator point of the ECC_BrainpoolP384R1 curve.
 */
extern const ECC_BrainpoolP384R1_Param ECC_BrainpoolP384R1_prime;

/*!
 *  @brief 'a' constant of the ECC_BrainpoolP384R1 curve when expressed in short
 *  Weierstrass form (y^2 = x^3 + a*x + b).
 */
extern const ECC_BrainpoolP384R1_Param ECC_BrainpoolP384R1_a;

/*!
 *  @brief 'b' constant of the ECC_BrainpoolP384R1 curve when expressed in short
 *  Weierstrass form (y^2 = x^3 + a*x + b).
 */
extern const ECC_BrainpoolP384R1_Param ECC_BrainpoolP384R1_b;

/*!
 *  @brief Order of the generator point of the ECC_BrainpoolP384R1 curve.
 */
extern const ECC_BrainpoolP384R1_Param ECC_BrainpoolP384R1_order;

/*!
 *  @brief 'k' in Montgomery domain of the ECC_BrainpoolP384R1 curve.
 */
extern const ECC_BrainpoolP384R1_Param ECC_BrainpoolP384R1_k_mont;

/*!
 *  @brief 'a' in Montgomery domain of the ECC_BrainpoolP384R1 curve.
 */
extern const ECC_BrainpoolP384R1_Param ECC_BrainpoolP384R1_a_mont;

/*!
 *  @brief 'b' in Montgomery domain of the ECC_BrainpoolP384R1 curve.
 */
extern const ECC_BrainpoolP384R1_Param ECC_BrainpoolP384R1_b_mont;

/*! @} */ /* end of BrainpoolP384R1_params */

/*!
 *  @defgroup BrainpoolP512R1_params BrainpoolP512R1 curve params
 *  @{
 */

/*!
 *  @brief Length of BrainpoolP512R1 curve parameters in bytes
 */
#define ECCParams_BrainpoolP512R1_LENGTH 64

/*!
 *  @brief Union to access ECC_BrainpoolP512R1 curve params in bytes or words.
 */
typedef union
{
    uint8_t byte[ECCParams_BrainpoolP512R1_LENGTH];
    uint32_t word[ECCParams_BrainpoolP512R1_LENGTH / sizeof(uint32_t)];
} ECC_BrainpoolP512R1_Param;

/*!
 *  @brief X coordinate of the generator point of the ECC_BrainpoolP512R1 curve.
 */
extern const ECC_BrainpoolP512R1_Param ECC_BrainpoolP512R1_generatorX;

/*!
 *  @brief Y coordinate of the generator point of the ECC_BrainpoolP512R1 curve.
 */
extern const ECC_BrainpoolP512R1_Param ECC_BrainpoolP512R1_generatorY;

/*!
 *  @brief Prime of the generator point of the ECC_BrainpoolP512R1 curve.
 */
extern const ECC_BrainpoolP512R1_Param ECC_BrainpoolP512R1_prime;

/*!
 *  @brief 'a' constant of the ECC_BrainpoolP512R1 curve when expressed in short
 *  Weierstrass form (y^2 = x^3 + a*x + b).
 */
extern const ECC_BrainpoolP512R1_Param ECC_BrainpoolP512R1_a;

/*!
 *  @brief 'b' constant of the ECC_BrainpoolP512R1 curve when expressed in short
 *  Weierstrass form (y^2 = x^3 + a*x + b).
 */
extern const ECC_BrainpoolP512R1_Param ECC_BrainpoolP512R1_b;

/*!
 *  @brief Order of the generator point of the ECC_BrainpoolP512R1 curve.
 */
extern const ECC_BrainpoolP512R1_Param ECC_BrainpoolP512R1_order;

/*!
 *  @brief 'k' in Montgomery domain of the ECC_BrainpoolP512R1 curve.
 */
extern const ECC_BrainpoolP512R1_Param ECC_BrainpoolP512R1_k_mont;

/*!
 *  @brief 'a' in Montgomery domain of the ECC_BrainpoolP512R1 curve.
 */
extern const ECC_BrainpoolP512R1_Param ECC_BrainpoolP512R1_a_mont;

/*!
 *  @brief 'b' in Montgomery domain of the ECC_BrainpoolP512R1 curve.
 */
extern const ECC_BrainpoolP512R1_Param ECC_BrainpoolP512R1_b_mont;

/*! @} */ /* end of BrainpoolP512R1_params */
