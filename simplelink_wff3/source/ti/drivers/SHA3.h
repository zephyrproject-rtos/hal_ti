/*
 * Copyright (c) 2026 Texas Instruments Incorporated
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
/*!****************************************************************************
 *  @file       SHA3.h
 *
 *  @brief      SHA3 driver header
 *
 *  @anchor ti_drivers_SHA3_Overview
 *  # Overview #
 *
 *  SHA3 (Secure Hash Algorithm 3) is a cryptographic hashing algorithm
 *  standardized by NIST in FIPS 202. It maps an input of arbitrary length to a
 *  fixed-length output with negligible probability of collision.
 *
 *  SHA3 provides the same interface and digest sizes as SHA2 (224, 256, 384,
 *  and 512 bits), making it a drop-in alternative. However, the two algorithms
 *  are internally completely different. SHA2 uses a Merkle-Damgaard
 *  construction while SHA3 uses the Keccak sponge construction. This
 *  architectural diversity means that a cryptanalytic breakthrough against SHA2
 *  would not affect SHA3, and vice versa. SHA3 serves as a fallback option if
 *  SHA2 is ever found to be insecure.
 *
 *  Key internal differences:
 *
 *  - SHA3 uses a 1600-bit internal state (vs. 256/512-bit for SHA2)
 *  - SHA3 block sizes (called "rate") vary inversely with digest length:
 *    - SHA3-224: 144 bytes
 *    - SHA3-256: 136 bytes
 *    - SHA3-384: 104 bytes
 *    - SHA3-512: 72 bytes
 *  - SHA3 is immune to length-extension attacks (SHA2 is not)
 *
 *  Hashes are often used to ensure the integrity of messages. They are also
 *  used as constituent parts of more complicated cryptographic schemes. HMAC
 *  is a message authentication code that is based on hash functions such as
 *  SHA3 rather than a block cipher.
 *
 *  "Hash" may refer to either the process of hashing when used as a verb and
 *  the output digest when used as a noun.
 *
 *  @anchor ti_drivers_SHA3_Usage
 *  # Usage #
 *
 *  Before starting a SHA3 operation, the application must do the following:
 *      - Call #SHA3_init() to initialize the driver
 *      - Call #SHA3_Params_init() to initialize the SHA3_Params to default
 *        values
 *      - Modify the #SHA3_Params as desired
 *      - Call #SHA3_open() to open an instance of the driver
 *
 *  There are two general ways to execute a SHA3 operation:
 *
 *  - one-step (in one operation)
 *  - multi-step (multiple partial operations)

 *  @anchor ti_drivers_SHA3_Synopsis
 *  # Synopsis
 *
 *  @anchor ti_drivers_SHA3_Synopsis_Code
 *  @code
 *
 *  // Import SHA3 Driver definitions
 *  #include <ti/drivers/SHA3.h>
 *
 *  // Define name for SHA3 channel index
 *  #define SHA3_INSTANCE 0
 *
 *  SHA3_init();
 *
 *  handle = SHA3_open(SHA3_INSTANCE, NULL);
 *
 * // For CC35XX devices only,
 * // Since the SHA3 driver for CC35XX relies on one HW engine (the HSM) for
 * // all of its operations. If the HSM boot up sequence fails, SHA3_open() will
 * // return NULL.
 *  if (!handle) {
 *      // Handle error
 *  }
 *
 *  result = SHA3_hashData(handle, message, strlen(message), actualDigest);
 *
 *  SHA3_close(handle);
 *  @endcode
 *
 *  @anchor ti_drivers_SHA3_Examples
 *  # Examples #
 *
 *  ## One-step hash operation #
 *
 *  The #SHA3_hashData() function can perform a SHA3 operation in a single call.
 *  It will always use the most highly optimized routine with the least overhead
 *  and the fastest runtime. However, it requires that the entire input message
 *  is available to the function in a contiguous location at the start of the
 *  call. The single call operation is required when hashing a message with a
 *  length smaller than or equal to one hash-block length. All devices support
 *  single call operations.
 *
 *  After a SHA3 operation completes, the application may either start another
 *  operation or close the driver by calling #SHA3_close().
 *
 *  @code
 *  SHA3_Params params;
 *  SHA3_Handle handle;
 *  int_fast16_t result;
 *
 *  char message[] = "A Ferengi without profit is no Ferengi at all.";
 *
 *  uint8_t actualDigest[SHA3_DIGEST_LENGTH_BYTES_256];
 *  uint8_t expectedDigest[] = {
 *      0x9a, 0xe5, 0x62, 0x7b,
 *      0xdb, 0x5d, 0xc4, 0xa2,
 *      0x4a, 0x49, 0xe1, 0x9a,
 *      0xf6, 0x5d, 0xf9, 0xf2,
 *      0x41, 0x4f, 0xcd, 0xb2,
 *      0xbd, 0x62, 0x02, 0x01,
 *      0x03, 0x2f, 0x90, 0x36,
 *      0x79, 0xcf, 0xd6, 0x5c
 *  };
 *
 *  SHA3_init();
 *
 *  SHA3_Params_init(&params);
 *  params.returnBehavior = SHA3_RETURN_BEHAVIOR_BLOCKING;
 *  handle = SHA3_open(0, &params);
 *  assert(handle != NULL);
 *
 *  result = SHA3_hashData(handle, message, strlen(message), actualDigest);
 *  assert(result == SHA3_STATUS_SUCCESS);
 *
 *  result = memcmp(actualDigest, expectedDigest, SHA3_DIGEST_LENGTH_BYTES_256);
 *  assert(result == 0);
 *
 *  SHA3_close(handle);
 *  @endcode
 *
 *  ## Partial hash operation #
 *
 *  When trying to operate on data that is too large to fit into available
 *  memory, partial processing is more advisable. The segments are processed
 *  with #SHA3_addData() whereas the final digest is computed by
 *  #SHA3_finalize().
 *
 *  @code
 *  SHA3_Handle handle;
 *  int_fast16_t result;
 *  SHA3_Params params;
 *
 *  const char message[] =
 *      "Premature optimization is the root of all evil (or at least most of it) in programming.";
 *
 *  uint8_t actualDigest[SHA3_DIGEST_LENGTH_BYTES_256];
 *  uint8_t expectedDigest[] = {
 *      0x1b, 0x87, 0x43, 0x40,
 *      0x83, 0x04, 0x76, 0xab,
 *      0x22, 0x46, 0x6e, 0x94,
 *      0x62, 0x0d, 0x4d, 0xdf,
 *      0xc5, 0x4d, 0x73, 0xc5,
 *      0xfd, 0xf6, 0x1a, 0x38,
 *      0x91, 0x0c, 0x98, 0x87,
 *      0xa9, 0x1a, 0xf0, 0xbe
 *  };
 *
 *  SHA3_init();
 *
 *  SHA3_Params_init(&params);
 *  params.returnBehavior = SHA3_RETURN_BEHAVIOR_BLOCKING;
 *  handle = SHA3_open(0, &params);
 *  assert(handle != NULL);
 *
 *  // We can configure the driver even after SHA3_open()
 *  result = SHA3_setHashType(handle, SHA3_HASH_TYPE_256);
 *  assert(result == SHA3_STATUS_SUCCESS);
 *
 *  // Process data in chunks. The driver buffers incomplete blocks internally.
 *  result = SHA3_addData(handle, &message[0], 17);
 *  assert(result == SHA3_STATUS_SUCCESS);
 *
 *  result = SHA3_addData(handle, &message[17], strlen(message) - 17);
 *  assert(result == SHA3_STATUS_SUCCESS);
 *
 *  // Compute the resulting digest
 *  result = SHA3_finalize(handle, actualDigest);
 *  assert(result == SHA3_STATUS_SUCCESS);
 *
 *  // Verify
 *  result = memcmp(actualDigest, expectedDigest, SHA3_DIGEST_LENGTH_BYTES_256);
 *  assert(result == 0);
 *
 *  SHA3_close(handle);
 *  @endcode
 *
 * ## One-step HMAC operation #
 *
 *  The #SHA3_hmac() function can perform a SHA3 operation in a single call. It
 *  will always use the most highly optimized routine with the least overhead
 *  and the fastest runtime. It requires that the entire input message is
 *  available to the function in a contiguous location at the start of the call.
 *
 *  After a SHA3 operation completes, the application may either start another
 *  operation or close the driver by calling #SHA3_close().
 *
 *  @code
 *  SHA3_Params params;
 *  SHA3_Handle handle;
 *  int_fast16_t result;
 *  CryptoKey hmacKey;
 *
 *  uint8_t message[] = {
 *          0xb1, 0x68, 0x9c, 0x25, 0x91, 0xea, 0xf3, 0xc9,
 *          0xe6, 0x60, 0x70, 0xf8, 0xa7, 0x79, 0x54, 0xff,
 *          0xb8, 0x17, 0x49, 0xf1, 0xb0, 0x03, 0x46, 0xf9,
 *          0xdf, 0xe0, 0xb2, 0xee, 0x90, 0x5d, 0xcc, 0x28,
 *          0x8b, 0xaf, 0x4a, 0x92, 0xde, 0x3f, 0x40, 0x01,
 *          0xdd, 0x9f, 0x44, 0xc4, 0x68, 0xc3, 0xd0, 0x7d,
 *          0x6c, 0x6e, 0xe8, 0x2f, 0xac, 0xea, 0xfc, 0x97,
 *          0xc2, 0xfc, 0x0f, 0xc0, 0x60, 0x17, 0x19, 0xd2,
 *          0xdc, 0xd0, 0xaa, 0x2a, 0xec, 0x92, 0xd1, 0xb0,
 *          0xae, 0x93, 0x3c, 0x65, 0xeb, 0x06, 0xa0, 0x3c,
 *          0x9c, 0x93, 0x5c, 0x2b, 0xad, 0x04, 0x59, 0x81,
 *          0x02, 0x41, 0x34, 0x7a, 0xb8, 0x7e, 0x9f, 0x11,
 *          0xad, 0xb3, 0x04, 0x15, 0x42, 0x4c, 0x6c, 0x7f,
 *          0x5f, 0x22, 0xa0, 0x03, 0xb8, 0xab, 0x8d, 0xe5,
 *          0x4f, 0x6d, 0xed, 0x0e, 0x3a, 0xb9, 0x24, 0x5f,
 *          0xa7, 0x95, 0x68, 0x45, 0x1d, 0xfa, 0x25, 0x8e
 *  };
 *
 *  // In this case, keyingMaterial is 40 bytes long. It could also be
 *  // any other length.
 *  uint8_t keyingMaterial[] = {
 *          0x97, 0x79, 0xd9, 0x12, 0x06, 0x42, 0x79, 0x7f,
 *          0x17, 0x47, 0x02, 0x5d, 0x5b, 0x22, 0xb7, 0xac,
 *          0x60, 0x7c, 0xab, 0x08, 0xe1, 0x75, 0x8f, 0x2f,
 *          0x3a, 0x46, 0xc8, 0xbe, 0x1e, 0x25, 0xc5, 0x3b,
 *          0x8c, 0x6a, 0x8f, 0x58, 0xff, 0xef, 0xa1, 0x76
 *  };
 *
 *  uint8_t actualHmac[SHA3_DIGEST_LENGTH_BYTES_256];
 *  uint8_t expectedHmac[] = {
 *      0x11, 0x2a, 0x7f, 0x4b, 0x67, 0x2b, 0x8f, 0x0d,
 *      0xb2, 0xb8, 0x99, 0x7b, 0xbf, 0x28, 0xf7, 0x9d,
 *      0xf3, 0x5d, 0xd2, 0x68, 0xb6, 0x67, 0xb3, 0x76,
 *      0x1e, 0x4f, 0xb6, 0x4e, 0xcb, 0x6a, 0x94, 0x50
 *  };
 *
 *  SHA3_init();
 *
 *  SHA3_Params_init(&params);
 *  params.returnBehavior = SHA3_RETURN_BEHAVIOR_BLOCKING;
 *  handle = SHA3_open(0, &params);
 *
 * // For CC35XX devices only,
 * // Since the SHA3 driver for CC35XX relies on one HW engine (the HSM) for
 * // all of its operations. If the HSM boot up sequence fails, SHA3_open() will
 * // return NULL.
 *  assert(handle != NULL);
 *
 *  CryptoKeyPlaintextHSM_initKey(&hmacKey,
 *                             keyingMaterial,
 *                             sizeof(keyingMaterial));
 *
 *  result = SHA3_hmac(handle,
 *                     &hmacKey,
 *                     message,
 *                     sizeof(message),
 *                     actualHmac);
 *  assert(result == SHA3_STATUS_SUCCESS);
 *
 *  result = memcmp(actualHmac, expectedHmac, SHA3_DIGEST_LENGTH_BYTES_256);
 *  assert(result == 0);
 *
 *  SHA3_close(handle);
 *  @endcode
 */

#ifndef ti_drivers_SHA3__include
#define ti_drivers_SHA3__include

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Common SHA3 status code reservation offset.
 * SHA3 driver implementations should offset status codes with
 * SHA3_STATUS_RESERVED growing negatively.
 *
 * Example implementation specific status codes:
 * @code
 * #define SHA3XYZ_STATUS_ERROR0    SHA3_STATUS_RESERVED - 0
 * #define SHA3XYZ_STATUS_ERROR1    SHA3_STATUS_RESERVED - 1
 * #define SHA3XYZ_STATUS_ERROR2    SHA3_STATUS_RESERVED - 2
 * @endcode
 */
#define SHA3_STATUS_RESERVED (-32)

/*!
 * @brief   Successful status code.
 *
 * Functions return SHA3_STATUS_SUCCESS if the function was executed
 * successfully.
 */
#define SHA3_STATUS_SUCCESS ((int_fast16_t)0)

/*!
 * @brief   Generic error status code.
 *
 * Functions return SHA3_STATUS_ERROR if the function was not executed
 * successfully and no more specific error is applicable.
 */
#define SHA3_STATUS_ERROR ((int_fast16_t)-1)

/*!
 * @brief   An error status code returned if the hardware or software resource
 * is currently unavailable.
 *
 * SHA3 driver implementations may have hardware or software limitations on how
 * many clients can simultaneously perform operations. This status code is
 * returned if the mutual exclusion mechanism signals that an operation cannot
 * currently be performed.
 */
#define SHA3_STATUS_RESOURCE_UNAVAILABLE ((int_fast16_t)-2)

/*!
 *  @brief  The ongoing operation was canceled.
 */
#define SHA3_STATUS_CANCELED ((int_fast16_t)-3)

/*!
 *  @brief  The requested operation or configuration is not
 *  supported by the device specific implementation.
 */
#define SHA3_STATUS_UNSUPPORTED ((int_fast16_t)-4)

/*!
 * @brief   Importing generated key into KeyStore failed
 *
 * Functions return SHA3_STATUS_KEYSTORE_ERROR if the KeyStore_PSA_importKey()
 * did not return KEYSTORE_PSA_STATUS_SUCCESS
 */
#define SHA3_STATUS_KEYSTORE_ERROR ((int_fast16_t)-5)

/*!
 * @brief  The requested operation involves a DMA transfer larger than the
 * hardware's DMA controller can handle.
 *
 * Functions return SHA3_STATUS_DMA_ERROR only on CC27XX devices, as large DMA
 * transfers will not be automatically segmented into multiple token
 * transactions.
 */
#define SHA3_STATUS_DMA_ERROR ((int_fast16_t)-6)

/*!
 * @brief   The way in which SHA3 function calls return after performing an
 * operation.
 *
 * Not all SHA3 operations exhibit the specified return behavior. Functions that
 * do not require significant computation and cannot offload that computation to
 * a background thread behave like regular functions. Which functions exhibit
 * the specified return behavior is not implementation dependent. Specifically,
 * a software-backed implementation run on the same CPU as the application will
 * emulate the return behavior while not actually offloading the computation to
 * the background thread.
 *
 * SHA3 functions exhibiting the specified return behavior have restrictions on
 * the context from which they may be called.
 *
 * |                                | Task  | Hwi   | Swi   |
 * |--------------------------------|-------|-------|-------|
 * |SHA3_RETURN_BEHAVIOR_CALLBACK   | X     | X     | X     |
 * |SHA3_RETURN_BEHAVIOR_BLOCKING   | X     |       |       |
 * |SHA3_RETURN_BEHAVIOR_POLLING    | X     | X     | X     |
 *
 */
typedef enum
{
    SHA3_RETURN_BEHAVIOR_CALLBACK = 1, /*!< The function call will return
                                        *   immediately while the SHA3 operation
                                        *   goes on in the background. The
                                        *   registered callback function is
                                        *   called after the operation
                                        *   completes. The context the callback
                                        *   function is called (task, HWI, SWI)
                                        *   is implementation-dependent.
                                        */
    SHA3_RETURN_BEHAVIOR_BLOCKING = 2, /*!< The function call will block while
                                        *   the SHA3 operation goes on in the
                                        *   background. SHA3 operation results
                                        *   are available after the function
                                        *   returns.
                                        */
    SHA3_RETURN_BEHAVIOR_POLLING  = 4, /*!< The function call will continuously
                                        *   poll a flag while the SHA3 operation
                                        *   goes on in the background. SHA3
                                        *   operation results are available
                                        *   after the function returns.
                                        */
} SHA3_ReturnBehavior;

/*!
 *  @brief  Enum for the hash types supported by the driver.
 */
typedef enum
{
    SHA3_HASH_TYPE_224 = 0,
    SHA3_HASH_TYPE_256 = 1,
    SHA3_HASH_TYPE_384 = 2,
    SHA3_HASH_TYPE_512 = 3,
} SHA3_HashType;

/*!
 *  @brief  Enum for the hash digest lengths in bytes supported by the driver.
 */
typedef enum
{
    SHA3_DIGEST_LENGTH_BYTES_224 = 28,
    SHA3_DIGEST_LENGTH_BYTES_256 = 32,
    SHA3_DIGEST_LENGTH_BYTES_384 = 48,
    SHA3_DIGEST_LENGTH_BYTES_512 = 64,
} SHA3_DigestLengthBytes;

/*!
 *  @brief  Enum for the block sizes of the algorithms.
 *
 *  SHA3 iteratively consumes segments of the block size and updates its
 *  internal state. The state is carried forward together with the next segment
 *  until the final segment produces the output digest.
 *  The block sizes of the algorithms differ from their digest lengths. When
 *  performing partial hashes, the segment lengths for all but the last segment
 *  must be multiples of the relevant block size.
 */
typedef enum
{
    SHA3_BLOCK_SIZE_BYTES_224 = 144,
    SHA3_BLOCK_SIZE_BYTES_256 = 136,
    SHA3_BLOCK_SIZE_BYTES_384 = 104,
    SHA3_BLOCK_SIZE_BYTES_512 = 72,
} SHA3_BlockSizeBytes;

/*!
 *  @brief SHA3 Global configuration
 *
 *  The %SHA3_Config structure contains a set of pointers used to characterize
 *  the SHA3 driver implementation.
 *
 *  This structure needs to be defined before calling #SHA3_init() and it must
 *  not be changed thereafter.
 *
 *  @sa     SHA3_init()
 */
typedef struct
{
    /*! Pointer to a driver specific data object */
    void *object;

    /*! Pointer to a driver specific hardware attributes structure */
    void const *hwAttrs;
} SHA3_Config;

/*!
 *  @brief  A handle that is returned from an SHA3_open() call.
 */
typedef SHA3_Config *SHA3_Handle;

/*!
 *  @brief  The definition of a callback function used by the SHA3 driver when
 *          used in ::SHA3_RETURN_BEHAVIOR_CALLBACK
 *
 *  @param  handle Handle of the client that started the SHA3 operation.
 *
 *  @param  returnStatus The result of the SHA3 operation. May contain an error
 *                       code. Informs the application of why the callback
 *                       function was called.
 */
typedef void (*SHA3_CallbackFxn)(SHA3_Handle handle, int_fast16_t returnStatus);

/*!
 *  @brief  SHA3 Parameters
 *
 *  SHA3 Parameters are used to with the SHA3_open() call. Default values for
 *  these parameters are set using SHA3_Params_init().
 *
 *  @sa     SHA3_Params_init()
 */
typedef struct
{
    SHA3_HashType hashType;             /*!< SHA3 variant to use. This
                                         *   determines the output digest
                                         *   length.
                                         */
    SHA3_ReturnBehavior returnBehavior; /*!< Blocking, callback, or polling
                                         *   return behavior
                                         */
    SHA3_CallbackFxn callbackFxn;       /*!< Callback function pointer */
    uint32_t timeout;                   /*!< Timeout before the driver returns
                                         *   an error in
                                         *   ::SHA3_RETURN_BEHAVIOR_BLOCKING
                                         */
} SHA3_Params;

/*!
 * @brief Global SHA3 configuration struct.
 *
 * Specifies context objects and hardware attributes for every
 * driver instance.
 *
 * This variable is supposed to be defined in the board file.
 */
extern const SHA3_Config SHA3_config[];

/*!
 * @brief Global SHA3 configuration count.
 *
 * Specifies the amount of available SHA3 driver instances.
 *
 * This variable is supposed to be defined in the board file.
 */
extern const uint_least8_t SHA3_count;

/*!
 *  @brief  Default SHA3_Params structure
 *
 *  @sa     #SHA3_Params_init()
 */
extern const SHA3_Params SHA3_defaultParams;

/*!
 *  @brief  Initializes the SHA3 driver module.
 *
 *  @pre    The #SHA3_config structure must exist and be persistent before this
 *          function can be called. This function must also be called before any
 *          other SHA3 driver APIs. This function call does not modify any
 *          peripheral registers.
 */
void SHA3_init(void);

/*!
 *  @brief  Initializes \a params with default values.
 *
 *  @param  params      A pointer to #SHA3_Params structure for initialization
 *
 *  Defaults values are:
 *      returnBehavior              = SHA3_RETURN_BEHAVIOR_BLOCKING
 *      callbackFxn                 = NULL
 *      timeout                     = SemaphoreP_WAIT_FOREVER
 *      custom                      = NULL
 */
void SHA3_Params_init(SHA3_Params *params);

/*!
 *  @brief  Initializes a SHA3 driver instance and returns a handle.
 *
 *  @pre    SHA3 controller has been initialized using #SHA3_init()
 *
 *  @param  index         Logical peripheral number for the SHA3 indexed into
 *                        the #SHA3_config table
 *
 *  @param  params        Pointer to a parameter block, if NULL it will use
 *                        default values.
 *
 *  @return A #SHA3_Handle on success or a NULL on an error or if it has been
 *          opened already.
 *
 *  @sa     #SHA3_init(), #SHA3_close()
 */
SHA3_Handle SHA3_open(uint_least8_t index, const SHA3_Params *params);

/*!
 *  @brief  Closes a SHA3 peripheral specified by \a handle.
 *
 *  @pre    #SHA3_open() has to be called first.
 *
 *  @param  handle A #SHA3_Handle returned from SHA3_open()
 *
 *  @sa     #SHA3_open()
 */
void SHA3_close(SHA3_Handle handle);

/*!
 *  @brief  Starts an HMAC operation on segmented data
 *
 *  This function uses @c key to compute the all intermediate results involving
 *  @c key as specified in FIPS 198-1.
 *
 *  This function blocks until the final digest hash been computed.
 *  It returns immediately when ::SHA3_RETURN_BEHAVIOR_CALLBACK is set.
 *
 *  @pre    #SHA3_open() has to be called first.
 *
 *  @post   Call #SHA3_addData() and #SHA3_finalizeHmac()
 *
 *  @param  handle  A #SHA3_Handle returned from #SHA3_open()
 *
 *  @param  key     The key with which to sign the message with
 *
 *  @retval #SHA3_STATUS_SUCCESS               The hash operation succeeded.
 *  @retval #SHA3_STATUS_ERROR                 The hash operation failed.
 *  @retval #SHA3_STATUS_RESOURCE_UNAVAILABLE  The required hardware resource
 *                                             was not available. Try again
 *                                             later.
 *  @retval #SHA3_STATUS_CANCELED              The hash operation was canceled.
 *
 *  @sa     #SHA3_reset()
 */
int_fast16_t SHA3_setupHmac(SHA3_Handle handle, const CryptoKey *key);

/*!
 *  @brief  Adds a segment of @c data with a @c length in bytes to the
 *          cryptographic hash or HMAC.
 *
 *  %SHA3_addData() may be called arbitrary times before finishing the operation
 *  with #SHA3_finalize().
 *
 *  This function blocks until the final digest hash been computed.
 *  It returns immediately when ::SHA3_RETURN_BEHAVIOR_CALLBACK is set.
 *
 *
 *  @pre    #SHA3_open() has to be called first.
 *  @pre    If computing an HMAC, #SHA3_setupHmac() must be called first.
 *
 *  @param  handle   A #SHA3_Handle returned from #SHA3_open()
 *
 *  @param  data     Pointer to the location to read from.
 *                   There might be alignment restrictions on different
 *                   platforms.
 *
 *  @param  length   Length of the message segment to hash, in bytes.
 *
 *  @retval #SHA3_STATUS_SUCCESS               The hash operation succeeded.
 *  @retval #SHA3_STATUS_ERROR                 The hash operation failed.
 *  @retval #SHA3_STATUS_RESOURCE_UNAVAILABLE  The required hardware resource
 *                                             was not available. Try again
 *                                             later.
 *  @retval #SHA3_STATUS_DMA_ERROR             The requested transaction is too
 *                                             large for the HSM DMA controller
 *                                             to handle.
 *  @retval #SHA3_STATUS_CANCELED              The hash operation was canceled.
 *  @retval #SHA3_STATUS_UNSUPPORTED           The requested operation is not
 *                                             supported by this implementation.
 *
 *  @sa     #SHA3_open(), #SHA3_reset(), #SHA3_finalize()
 */
int_fast16_t SHA3_addData(SHA3_Handle handle, const void *data, size_t length);

/*!
 *  @brief  Finishes a hash operation and writes the result to \a digest.
 *
 *  This function finishes a hash operation that has been previously started
 *  by #SHA3_addData().
 *
 *  This function blocks until the final digest hash been computed.
 *  It returns immediately when ::SHA3_RETURN_BEHAVIOR_CALLBACK is set.
 *
 *  @pre    #SHA3_addData() has to be called first.
 *
 *  @param  handle      A #SHA3_Handle returned from #SHA3_open()
 *
 *  @param  digest      Pointer to the location to write the digest to.
 *
 *  @retval #SHA3_STATUS_SUCCESS               The hash operation succeeded.
 *  @retval #SHA3_STATUS_ERROR                 The hash operation failed.
 *  @retval #SHA3_STATUS_RESOURCE_UNAVAILABLE  The required hardware resource
 *                                             was not available. Try again
 *                                             later.
 *  @retval #SHA3_STATUS_CANCELED              The hash operation was canceled.
 *
 *  @sa     #SHA3_open(), #SHA3_addData()
 */
int_fast16_t SHA3_finalize(SHA3_Handle handle, void *digest);

/*!
 *  @brief  Finishes an HMAC operation and writes the result to @c hmac.
 *
 *  This function finishes a an HMAC operation that has been previously started
 *  by #SHA3_setupHmac() and #SHA3_addData().
 *
 *  This function blocks until the final digest hash been computed.
 *  It returns immediately when ::SHA3_RETURN_BEHAVIOR_CALLBACK is set.
 *
 *  @pre    #SHA3_setupHmac() must be called prior.
 *  @pre    #SHA3_addData() should be called after #SHA3_setupHmac().
 *
 *  @param  handle      A #SHA3_Handle returned from #SHA3_open()
 *
 *  @param  hmac        Pointer to the location to write the digest to.
 *
 *  @retval #SHA3_STATUS_SUCCESS               The hash operation succeeded.
 *  @retval #SHA3_STATUS_ERROR                 The hash operation failed.
 *  @retval #SHA3_STATUS_RESOURCE_UNAVAILABLE  The required hardware resource
 *                                             was not available. Try again
 *                                             later.
 *  @retval #SHA3_STATUS_CANCELED              The hash operation was canceled.
 *
 *  @sa     #SHA3_open(), #SHA3_setupHmac() #SHA3_addData()
 */
int_fast16_t SHA3_finalizeHmac(SHA3_Handle handle, void *hmac);

/*!
 *  @brief  Hashes a segment of \a data with a \a size in bytes and writes the
 *          resulting hash to \a digest.
 *
 *  The digest content is computed in one step. Intermediate data from a
 *  previous partial operation started with #SHA3_addData() is discarded.
 *
 *  This function blocks until the final digest hash been computed.
 *  It returns immediately when ::SHA3_RETURN_BEHAVIOR_CALLBACK is set.
 *
 *  @pre    #SHA3_open() has to be called first.
 *
 *  @param  handle   A #SHA3_Handle returned from #SHA3_open()
 *
 *  @param  data     Pointer to the location to read from.
 *                   There might be alignment restrictions on different
 *                   platforms.
 *
 *  @param  dataLength Length of the message @c data, in bytes.
 *
 *  @param  digest   Pointer to the location to write the digest to.
 *                   There might be alignment restrictions on different
 *                   platforms.
 *
 *  @retval #SHA3_STATUS_SUCCESS               The hash operation succeeded.
 *  @retval #SHA3_STATUS_ERROR                 The hash operation failed.
 *  @retval #SHA3_STATUS_RESOURCE_UNAVAILABLE  The required hardware resource
 *                                             was not available. Try again
 *                                             later.
 *  @retval #SHA3_STATUS_DMA_ERROR             The requested transaction is too
 *                                             large for the HSM DMA controller
 *                                             to handle.
 *  @retval #SHA3_STATUS_CANCELED              The hash operation was canceled.
 *  @retval #SHA3_STATUS_UNSUPPORTED           The requested operation is not
 *                                             supported by this implementation.
 *
 *  @sa     #SHA3_open()
 */
int_fast16_t SHA3_hashData(SHA3_Handle handle, const void *data, size_t dataLength, void *digest);

/*!
 *  @brief  Creates a keyed hash of @c data with @c key.
 *
 *  This function signs @c data using @c key using the keyed-hash message
 *  authentication code (HMAC) algorithm specified in FIPS 198-1.
 *
 *  This function expects all of @c data to be available in contiguous memory.
 *
 *  Intermediate data from a previous
 *  partial operation started with #SHA3_addData() is discarded.
 *
 *  This function blocks until the final digest hash been computed.
 *  It returns immediately when ::SHA3_RETURN_BEHAVIOR_CALLBACK is set.
 *
 *  @pre    #SHA3_open() has to be called first.
 *
 *  @param  handle  A #SHA3_Handle returned from #SHA3_open()
 *
 *  @param  key     The key with which @c data is signed
 *
 *  @param  data    Pointer to the location to read from.
 *                  There might be alignment restrictions on different
 *                  platforms.
 *
 *  @param  dataLength Length of the message @c data, in bytes.
 *
 *  @param  hmac    Pointer to the location to write the HMAC to.
 *                  There might be alignment restrictions on different
 *                  platforms.
 *
 *  @retval #SHA3_STATUS_SUCCESS               The hash operation succeeded.
 *  @retval #SHA3_STATUS_ERROR                 The hash operation failed.
 *  @retval #SHA3_STATUS_RESOURCE_UNAVAILABLE  The required hardware resource
 *                                             was not available. Try again
 *                                             later.
 *
 *  @sa     #SHA3_open()
 */
int_fast16_t SHA3_hmac(SHA3_Handle handle, const CryptoKey *key, const void *data, size_t dataLength, void *hmac);

/*!
 *  @brief Clears internal buffers and aborts an ongoing SHA3 operation.
 *
 *  Clears all internal buffers and the intermediate digest of this driver
 *  instance. If an asynchronous operation is ongoing, the behavior is the same
 *  as for #SHA3_cancelOperation().
 *
 *  @param  handle      A #SHA3_Handle returned from #SHA3_open()
 *
 *  @sa     #SHA3_cancelOperation()
 */
void SHA3_reset(SHA3_Handle handle);

/*!
 *  @brief Aborts an ongoing SHA3 operation and clears internal buffers.
 *
 *  Aborts an ongoing hash operation of this driver instance. The operation will
 *  terminate as though an error occurred and the status code of the operation
 *  will be #SHA3_STATUS_CANCELED in this case.
 *
 *  @param  handle      A #SHA3_Handle returned from #SHA3_open()
 *
 *  @retval #SHA3_STATUS_SUCCESS               The operation was canceled or
 *                                             there was no operation in
 *                                             progress to be canceled.
 */
int_fast16_t SHA3_cancelOperation(SHA3_Handle handle);

/*!
 *  @brief  Selects a new hash algorithm @a type.
 *
 *  This function changes the hash algorithm type of the hash digest at
 *  run-time. The hash type is usually specified during #SHA3_open().
 *
 *  Neither is it allowed to call this function during a running hash operation
 *  nor during an incomplete multi-step hash operation. In this case
 *  #SHA3_STATUS_ERROR would be returned.
 *
 *  @pre    #SHA3_open() has to be called first.
 *
 *  @param  handle      A #SHA3_Handle returned from #SHA3_open()
 *
 *  @param  type        New hash algorithm type
 *
 *  @retval #SHA3_STATUS_SUCCESS                Hash type set correctly.
 *  @retval #SHA3_STATUS_ERROR                  Error. Platform may not support
 *                                              this hash type.
 */
int_fast16_t SHA3_setHashType(SHA3_Handle handle, SHA3_HashType type);

/**
 *  @brief  Constructs a new SHA3 object
 *
 *  Unlike #SHA3_open(), #SHA3_construct() does not require the hwAttrs and
 *  object to be allocated in a #SHA3_Config array that is indexed into.
 *  Instead, the #SHA3_Config, hwAttrs, and object can be allocated at any
 *  location. This allows for relatively simple run-time allocation of temporary
 *  driver instances on the stack or the heap.
 *  The drawback is that this makes it more difficult to write device-agnostic
 *  code. If you use an ifdef with DeviceFamily, you can choose the correct
 *  object and hwAttrs to allocate. That compilation unit will be tied to the
 *  device it was compiled for at this point. To change devices, recompilation
 *  of the application with a different DeviceFamily setting is necessary.
 *
 *  @param  config  #SHA3_Config describing the location of the object and
 *                  hwAttrs.
 *
 *  @param  params  #SHA3_Params to configure the driver instance.
 *
 *  @return         Returns a #SHA3_Handle on success or NULL on failure.
 *
 *  @pre    The object struct @c config points to must be zeroed out prior to
 *          calling this function. Otherwise, unexpected behavior may ensue.
 */
SHA3_Handle SHA3_construct(SHA3_Config *config, const SHA3_Params *params);

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_SHA3__include */
