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
#ifndef SHA256SW_H_
#define SHA256SW_H_

/** ============================================================================
 *  @file       sha256sw.h
 */
/*!
 *  @addtogroup sw_libraries_group
 *  @{
 *
 *  @addtogroup sha2sw_api
 *  @{
 *  @brief      SHA2 256/224 SW APIs.
 *
 *
 *  @anchor ti_SHA256_SW_LIBRARY_Overview
 *  # Overview #
 *  Provides top-level general purpose SHA2 256/224 APIs. SHA2 algorithm is
 *  implemented in SW with no HW acceleration. The implementation is highly
 *  optimized for speed and code size. These functions reside in ROM, and are
 *  exposed through HAPI, and also through the function prototypes and macros below.
 *
 *
 *  Availability of SHA2 224 depends on build configuration.
 *  See file @ref sha2sw_config.h.
 *
 *  ## Limitations ##
 *  @li A maximum of 512MiB may be hashed by this implementation. (SHA2
 *      standard supports 2 million Terabytes for 224/256)
 *  @li Input data may be 8-bit aligned. However, output digest must be
 *      32-bit aligned.
 *  @li Intermediate values, input data, and final digest value may be
 *      left behind on the stack.
 *
 *  <hr>
 *  @anchor ti_SHA256_SW_LIBRARY_Usage
 *  # Usage #
 *
 *  There are two general ways to execute a SHA2 operation:
 *
 *  - one-step, using #SHA256SWHashData()
 *  - multi-step, using #SHA256SWStart(), #SHA256SWAddData(), and
 *    #SHA256SWFinalize()
 *
 *  The multi-step approach allows the hash to be extended by adding
 *  more data.
 *
 *  All input data is to be in little-endian (LE) format and the resulting
 *  hash values produced by these APIs are in LE format.
 *
 *  @anchor ti_SHA256_SW_LIBRARY_Synopsis
 *  ## Synopsis
 *
 *  The following is a quick overview of one-step hashing.
 *
 *  @anchor ti_SHA256_SW_LIBRARY_Synopsis_Code
 *  @code
 *  // Import SHA2 SW Driver definitions
 *  #include <sha256sw.h>
 *
 *  // Create an object and handle
 *  SHA256SW_Object sha256SWObject;
 *  SHA256SW_Handle sha256SWHandle = &sha256SWObject;
 *
 *  // Allocate space for digest output
 *  uint32_t actualDigest[8];
 *
 *  result = SHA256SWHashData(sha256SWHandle, SHA2SW_HASH_TYPE_256,
 *                             message, strlen(message), actualDigest);
 *  @endcode
 *
 *  <hr>
 *  @anchor ti_SHA256_SW_LIBRARY_Examples
 *  # Examples
 *  @li @ref ti_SHA256_SW_LIBRARY_Example_hashData "Hashing data in one call"
 *  @li @ref ti_SHA256_SW_LIBRARY_Example_addData "Hashing data in multiple calls"
 *
 *  @anchor ti_SHA256_SW_LIBRARY_Example_hashData
 *  ## Hashing data in one call
 *
 *  @code
 *  SHA256SW_Object sha256SWObject;
 *  SHA256SW_Handle sha256SWHandle = &sha256SWObject;
 *  int_fast16_t sha2SWresult;
 *  uint32_t finalDigest[8];
 *  int notsame;
 *
 *  char message[] =
 *          "abcdefghijklmnabcdefghijklmnabcdefghijklmnabcdefghijklmn1234";
 *  uint8_t expectedDigest[] =
 *          { 0x60, 0x06, 0x00, 0x24, 0x13, 0xe4, 0x27, 0x0d,
 *            0x4d, 0xdb, 0x66, 0x93, 0x42, 0xa9, 0xe2, 0xdb,
 *            0x66, 0x5e, 0xc8, 0x70, 0x73, 0xc4, 0x2e, 0xb5,
 *            0x44, 0x99, 0x62, 0xf1, 0x2a, 0xb2, 0xe8, 0x60 };
 *
 *  sha2SWresult = SHA256SWHashData(sha256SWHandle, SHA2SW_HASH_TYPE_256,
 *                                   message, strlen(message), finalDigest);
 *
 *  if (sha2SWresult != SHA2SW_STATUS_SUCCESS)
 *  {
 *      while(1);
 *  }
 *
 *  // NOTE: If expectedDigest is a secret value, a timing constant comparison
 *  // routine shall be used instead of memcmp.
 *  notsame = memcmp(finalDigest, expectedDigest, sizeof(finalDigest));
 *
 *  if (notsame)
 *  {
 *      while(1);
 *  }
 *  @endcode
 *
 *
 *  @anchor ti_SHA256_SW_LIBRARY_Example_addData
 *  ## Hashing data in multiple calls
 *
 *  @code
 *  SHA256SW_Object sha256SWObject;
 *  SHA256SW_Handle sha256SWHandle = &sha256SWObject;
 *  int_fast16_t sha2SWresult;
 *  uint32_t finalDigest[8];
 *  int notsame;
 *
 *  char message[] =
 *          "abcdefghijklmnabcdefghijklmnabcdefghijklmnabcdefghijklmn1234";
 *  uint8_t expectedDigest[] =
 *          { 0x60, 0x06, 0x00, 0x24, 0x13, 0xe4, 0x27, 0x0d,
 *            0x4d, 0xdb, 0x66, 0x93, 0x42, 0xa9, 0xe2, 0xdb,
 *            0x66, 0x5e, 0xc8, 0x70, 0x73, 0xc4, 0x2e, 0xb5,
 *            0x44, 0x99, 0x62, 0xf1, 0x2a, 0xb2, 0xe8, 0x60, };
 *
 *
 *  sha2SWresult = SHA256SWStart(sha256SWHandle, SHA2SW_HASH_TYPE_256);
 *
 *  if (sha2SWresult == SHA2SW_STATUS_SUCCESS) {
 *      sha2SWresult = SHA256SWAddData(sha256SWHandle, message, 20);
 *  }
 *
 *  if (sha2SWresult == SHA2SW_STATUS_SUCCESS) {
 *      sha2SWresult = SHA256SWAddData(sha256SWHandle, &message[20], strlen(message) - 20);
 *  }
 *
 *  if (sha2SWresult == SHA2SW_STATUS_SUCCESS) {
 *      sha2SWresult = SHA256SWFinalize(sha256SWHandle, finalDigest);
 *  }
 *
 *  if (sha2SWresult != SHA2SW_STATUS_SUCCESS)
 *  {
 *      while(1);
 *  }
 *
 *  // NOTE: If expectedDigest is a secret value, a timing constant comparison
 *  // routine shall be used instead of memcmp.
 *  notsame = memcmp(finalDigest, expectedDigest, sizeof(finalDigest));
 *
 *  if (notsame)
 *  {
 *      while(1);
 *  }
 *  @endcode
 *
 *
 *  <hr>
 *  @anchor ti_SHA256_SW_LIBRARY_configuration
 *  # Configuration
 *
 *  See file @ref sha2sw_config.h for full configuration information.
 *
 *  If #SHA2SW_VALIDATE_INPUTS is not defined then:
 *  @li the caller is responsible for ensuring all inputs are valid, and
 *  @li the module's functions will only return #SHA2SW_STATUS_SUCCESS
 *
 */

#include <stddef.h>
#include <stdint.h>

#include "sha2sw_common.h"
#include "sha2sw_config.h"

/*!
 *  @brief SHA256SW Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    uint32_t bitsProcessed; // Only 2^32 bits (512 MiBytes) are supported
    int8_t offsetWb;        // Byte offset into Ws, used to load message
    uint8_t reserved1;
    uint8_t reserved2;
    uint8_t reserved3;
    uint32_t digest32[8]; // Holds intermediate/final digest
    uint32_t Ws32[16];    // Message schedule, indexed by (s & 0xF),
                          // where s = 63 - t, and t is NIST 180-4's
                          // message schedule index
} SHA256SW_Object;

/*!
 *  @brief  A handle to a SHA256SW_Object.
 */
typedef SHA256SW_Object *SHA256SW_Handle;

/* Include this file after the type definitions above, to break cyclic dependency between hapi.h and sha256sw.h */
#include "hapi.h"

/*!
 *  @brief  Performs a complete hash operation, producing a final digest
 *          for the data.
 *
 *  This function wraps #SHA256SWStart(), #SHA256SWAddData(), and
 *  #SHA256SWFinalize().
 *
 *  There is no need to call #SHA256SWStart() prior to calling this function.
 *
 *  The total length of data that can be hashed by this implementation
 *  is 512MiB (0x20000000 bytes.)
 *
 *  @param[in]  handle A #SHA256SW_Handle.
 *
 *  @param[in]  hashType The type of hash (256 or 224) to perform.
 *
 *  @param[in]  data data (message) to hash. May point to zero.
 *
 *  @param[in]  length the number of bytes (pointed to by @c data parameter)
 *              to add to the hash.
 *
 *  @param[out]  digest Output location for the final digest. Must be
 *               able to hold 32 bytes of output and be 32-bit aligned.
 *
 *  @retval #SHA2SW_STATUS_SUCCESS             The hash operation succeeded.
 *  @retval #SHA2SW_STATUS_ERROR               The hash operation failed.
 *  @retval #SHA2SW_STATUS_UNSUPPORTED         Requested Hash Type is unsupported.
 *  @retval #SHA2SW_STATUS_LENGTH_TOO_LARGE    The requested length of data to hash
 *                                             is more than the implementation
 *                                             supports.
 *  @retval #SHA2SW_STATUS_NULL_INPUT          One or more of the pointer inputs is
 *                                             NULL.
 *
 */
extern int_fast16_t SHA256SWHashData(SHA256SW_Handle handle,
                                     SHA2SW_HashType hashType,
                                     const void *data,
                                     size_t length,
                                     uint32_t digest[8]);

#define SHA256SWHashData HAPI_TABLE_POINTER->sha256SwHashData

/*!
 *  @brief  Initialize a SHA256SW_Handle, preparing for hashing data.
 *
 *  @param[in] handle A #SHA256SW_Handle.
 *
 *  @param[in] hashType The type of hash (256 or 224) to perform.
 *
 *  @retval #SHA2SW_STATUS_SUCCESS             The hash operation succeeded.
 *  @retval #SHA2SW_STATUS_UNSUPPORTED         Requested Hash Type is unsupported.
 *  @retval #SHA2SW_STATUS_NULL_INPUT          One or more of the pointer inputs is
 *                                             NULL.
 *
 *  @sa     #SHA256SWAddData()
 *  @sa     #SHA256SWFinalize()
 */
extern int_fast16_t SHA256SWStart(SHA256SW_Handle handle, SHA2SW_HashType hashType);

#define SHA256SWStart HAPI_TABLE_POINTER->sha256SwStart

/*!
 *  @brief  Add data to a SHA256/224 operation.
 *
 *  Adds data to a hash operation. The @c handle must have been
 *  initialized by a call to SHA256SWStart first.
 *
 *  The total length of data that can be hashed by this implementation
 *  is 512MiB (0x20000000 bytes.)
 *
 *  After passing in all data to be hashed, call #SHA256SWFinalize()
 *  to obtain the final digest.
 *
 *  @pre    handle was previously passed to #SHA256SWStart().
 *
 *  @param[in]  handle A #SHA256SW_Handle.
 *
 *  @param[in]  data data (message) to add to the hash. May point to zero.
 *
 *  @param[in]  length the number of bytes (pointed to by @c data parameter)
 *              to add to the hash.
 *
 *  @retval #SHA2SW_STATUS_SUCCESS             The hash operation succeeded.
 *  @retval #SHA2SW_STATUS_LENGTH_TOO_LARGE    The requested length of data to hash
 *                                             is more than the implementation
 *                                             supports.
 *  @retval #SHA2SW_STATUS_NULL_INPUT          One or more of the pointer inputs is
 *                                             NULL.
 *
 *  @sa     #SHA256SWStart()
 *  @sa     #SHA256SWFinalize()
 */
extern int_fast16_t SHA256SWAddData(SHA256SW_Handle handle, const void *data, size_t length);

#define SHA256SWAddData HAPI_TABLE_POINTER->sha256SwAddData

/*!
 *  @brief  Finalize a SHA256/224 operation, creating the final digest.
 *
 *  After calling this function, @c handle should not be used again
 *  until it has been reinitialized via a call to #SHA256SWStart().
 *
 *  @pre    handle was previously passed to #SHA256SWStart() and data to
 *          be hashed was passed to #SHA256SWAddData()
 *
 *  @param[in]  handle A #SHA256SW_Handle.
 *
 *  @param[out]  digest Output location for the final digest. Must be
 *               able to hold 32 bytes of output and be 32-bit aligned.
 *
 *  @retval #SHA2SW_STATUS_SUCCESS             The hash operation succeeded.
 *  @retval #SHA2SW_STATUS_NULL_INPUT          One or more of the pointer inputs is
 *                                             NULL.
 *
 *  @sa     #SHA256SWStart()
 *  @sa     #SHA256SWAddData()
 */
extern int_fast16_t SHA256SWFinalize(SHA256SW_Handle handle, uint32_t digest[8]);

#define SHA256SWFinalize HAPI_TABLE_POINTER->sha256SwFinalize

/*! @}*/
/*! @}*/

#endif /* SHA256SW_H_ */
