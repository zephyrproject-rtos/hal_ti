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
#ifndef SHA2SW_COMMON_H_
#define SHA2SW_COMMON_H_

/*! ============================================================================
 *  @file       sha2sw_common.h
 *
 *  @brief      Definitions common across all SHA2 SW modules.
 *
 *  # Overview #
 *  Provides top-level general purpose SHA2 SW definitions such as
 *  error return codes and enumerations.
 *
 */

#include <stddef.h>
#include <stdint.h>

#include "sha2sw_config.h"

/*!
 *  @brief  Enum for the hash types supported by the library.
 */
typedef enum
{
    SHA2SW_HASH_TYPE_256 = 0,
#if SHA2SW_SUPPORT_SHA2_224 == 1
    SHA2SW_HASH_TYPE_224 = 1,
#endif
#if SHA2SW_SUPPORT_SHA2_384 == 1
    SHA2SW_HASH_TYPE_384 = 2,
#endif
    SHA2SW_HASH_TYPE_512 = 3
} SHA2SW_HashType;

/*!
 *  @brief  Number of rounds used in the SHA2 224 and 256 algorithms.
 */
#define SHA2SW_224_OR_256_ROUNDS ((uint8_t)64u)

/*!
 *  @brief  Number of rounds used in the SHA2 384 and 512 algorithms.
 */
#define SHA2SW_384_OR_512_ROUNDS ((uint8_t)80u)

/*!
 *  @brief  Number of bytes in the block of the SHA2 224 and 256 algorithms.
 */
#define SHA2SW_224_OR_256_BLOCK_SIZE ((uint8_t)64u)

/*!
 *  @brief  Number of bytes in the block of the SHA2 384 and 512 algorithms.
 */
#define SHA2SW_384_OR_512_BLOCK_SIZE ((uint8_t)128u)

/*!
 *  @brief  The maximum number of bits this implementation
 *          supports in the input message/data.
 */
#define SHA2SW_MAX_MESSAGE_BIT_LENGTH ((uint32_t)0x20000000u)

/*!
 *  @addtogroup sw_libraries_group
 *  @{
 *  @addtogroup sha2sw_status_codes
 *  @{
 *  @brief Status codes returned by the SHA2 SW module.
 */

/*!
 * @brief   Successful status code.
 *
 * Functions return SHA2SW_STATUS_SUCCESS if the function was executed
 * successfully.
 */
#define SHA2SW_STATUS_SUCCESS ((int_fast16_t)0)

/*!
 * @brief   Generic error status code.
 *
 * Functions return SHA2SW_STATUS_ERROR if the function was not executed
 * successfully and no more specific error is applicable.
 */
#define SHA2SW_STATUS_ERROR ((int_fast16_t)-100)

/*!
 * @brief   Requested operation is not supported.
 *
 * The library (as built) does not support a requested feature.
 */
#define SHA2SW_STATUS_UNSUPPORTED ((int_fast16_t)-102)

/*!
 * @brief   Too many data bytes have been requested to be hashed.
 *
 * The library supports a maximum length of 512MiB to be hashed.
 */
#define SHA2SW_STATUS_LENGTH_TOO_LARGE ((int_fast16_t)-103)

/*!
 * @brief   Input value was NULL.
 *
 * An input pointer was NULL. Operation not performed.
 */
#define SHA2SW_STATUS_NULL_INPUT ((int_fast16_t)-104)

/*! @}*/
/*! @}*/

#endif /* SHA2SW_COMMON_H_ */
