/******************************************************************************
 *  Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
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
 *
 ******************************************************************************/
#ifndef SHA2SW_CONFIG_H_
#define SHA2SW_CONFIG_H_

/** ============================================================================
 *  @file       sha2sw_config.h
 */
/*!
 *  @addtogroup sw_libraries_group
 *  @{
 *  @addtogroup sha2sw_config_options
 *  @{
 *  @brief Build-time configuration options for the SHA2 SW module
 */
/*!
 * @brief   Include support for SHA2 224.
 *
 */
#if !defined(SHA2SW_SUPPORT_SHA2_224)
// #define SHA2SW_SUPPORT_SHA2_224 (1)
#endif

/*!
 * @brief   Include support for SHA2 384.
 *
 */
#if !defined(SHA2SW_SUPPORT_SHA2_384)
// #define SHA2SW_SUPPORT_SHA2_384 (1)
#endif

/*!
 * @brief   If defined, SHA2SW library will check inputs for invalid
 *          conditions. Otherwise, parameters will not be checked.
 *
 *  If #SHA2SW_VALIDATE_INPUTS is not defined then:
 *  @li the caller is responsible for ensuring all inputs are valid, and
 *  @li the module's functions will only return #SHA2SW_STATUS_SUCCESS
 *
 *
 *  Not defining this value will reduce code size.
 */
#if !defined(SHA2SW_VALIDATE_INPUTS)
    #define SHA2SW_VALIDATE_INPUTS (1)
#endif

/*!
 * @brief   Use a faster implementation of the message schedule which is
 *          slightly larger in code size.
 *
 * Expected time savings of 2,600 cycles or more per input block. Code
 * size cost for enabling may be as little as 8 bytes.
 */
#if !defined(SHA2SW_FAST_MESSAGE_SCHEDULE)
    #define SHA2SW_FAST_MESSAGE_SCHEDULE (1)
#endif

/*!
 * @brief   Use a faster implementation of the working variables a-h which is
 *          slightly larger in code size.
 *
 * Expected time savings of 750 cycles or more per input block. Code
 * size cost for enabling may be as little as 24 bytes.
 */
#if !defined(SHA2SW_FAST_WORKING_VARS)
    #define SHA2SW_FAST_WORKING_VARS (1)
#endif

/*!
 * @brief   Use portions of the constants of the 512 algorithm to
 *          support the 256 and 224 algorithms.
 *
 * The initial hash values as well as the round constants (K) of
 * 512/384 are extensions of the values used for 256/224. Thus,
 * const data space can be saved by using the 512/384 constants
 * for the 256/224 algorithm. However, the 256/224 algorithm must
 * spend extra cycles to skip over unneeded constants.
 *
 * Expected savings of at least 288 bytes of const data at the cost
 * of a few bytes of code space and small change in performance.
 */
#if !defined(SHA2SW_USE_512_CONST_FOR_256)
// #define SHA2SW_USE_512_CONST_FOR_256 (1)
#endif

/*!
 * @brief   Use Arm(R) C Language Extensions
 *
 * Use ARM(R) CLE to directly access op codes which can improve
 * code size and/or performance.
 */
#if !defined(SHA2SW_USE_ARMCLE)
    #define SHA2SW_USE_ARMCLE (1)
#endif

/*! @}*/
/*! @}*/

#endif /* SHA2SW_CONFIG_H_ */
