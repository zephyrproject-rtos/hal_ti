/*
 * Copyright (c) 2023-2026 Texas Instruments Incorporated
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
 *  @file       HSMXXF3.h
 *
 *  @brief      Interface to for all HSM-related operations
 *
 *  This module provides functions for use of the Hardware Security Module.
 *
 *  The HSM initialization procedure must first enable the clock, then
 *  initialize the mailbox, and finally boot the device.
 *
 *  APIs are provided to synchronize access to the HSM and submit command tokens,
 *  constructed by TI crypto drivers.
 *
 *  Additional APIs to construct command tokens, interpret result token data as
 *  well as additional key/asset management operations.
 *
 *  @anchor HSMXXF3_BounceBuffers
 *  ## Bounce Buffers (CC35xx only)
 *
 *  On CC35xx, the HSM cannot access external memory directly. When data
 *  resides in external memory, crypto drivers stage it through internal-RAM
 *  bounce buffers before submitting tokens to the HSM, and copy results back
 *  out afterwards:
 *
 *  | Variable                  | Used for            |
 *  |---------------------------|---------------------|
 *  | `HSMXXF3_inputBounce`     | PSRAM + flash input |
 *  | `HSMXXF3_outputBounce`    | PSRAM output only   |
 *  | `HSMXXF3_auxBounce`       | PSRAM + flash aux   |
 *
 *  Flash output is not supported; setting `HSMXXF3_outputBounce.size` to zero
 *  is valid when PSRAM is not used with crypto drivers.
 *
 *  Setting a buffer's `size` field to zero disables it. Any operation that
 *  requires the disabled buffer will return
 *  #HSMXXF3_STATUS_BOUNCE_UNAVAILABLE. The SysConfig HSM module configures
 *  buffers based on which external memory types are used with crypto drivers.
 *
 *  When defining buffers manually, each array must be aligned to 4 bytes and
 *  placed in `.internalRAM.bss`. For example:
 *
 *  @code
 *  static uint8_t myInputBuf[4096] __attribute__((aligned(4), section(".internalRAM.bss")));
 *  HSMXXF3_BounceBuffer HSMXXF3_inputBounce = {
 *     .size = sizeof(myInputBuf),
 *     .buffer = myInputBuf
 *  };
 *  @endcode
 *
 *  ### Size constraints
 *
 *  The following constraints apply when a buffer is enabled (size > 0).
 *
 *  **Input buffer** (`HSMXXF3_inputBounce.size`):
 *  - At least 16 bytes (one AES block).
 *  - At least 128 bytes if any SHA2 driver object may be in external memory
 *    (SHA2 maximum block size).
 *  - At least 144 bytes if any SHA3 driver object may be in external memory
 *    (SHA3 maximum block size: SHA3-224 rate).
 *  - At least 96 bytes if EdDSA sign or verify operations are used with a
 *    driver object in external memory (EdDSA sign-initial maximum length).
 *  - At least 384 bytes if EdDSA sign or verify operations are used with the
 *    message in external memory (SHA-512 intermediate hash chunking:
 *    2 × 128-byte blocks reserved for finalization + up to 127-byte SHA-512
 *    alignment remainder).
 *
 *  **Output buffer** (`HSMXXF3_outputBounce.size`):
 *  - At least 16 bytes (one AES block) when enabled.
 *  - At least 144 bytes if ECDSA, EdDSA sign, or ECDH operations are used
 *    with a driver object in external memory (ECDSA/ECDH component vector
 *    length for P-521).
 *
 *  **Auxiliary buffer** (`HSMXXF3_auxBounce.size`):
 *  - At least 16 bytes (one AES block).
 *  - At least 72 bytes if EdDSA verify is used with a driver object in
 *    external memory (EdDSA component vector length).
 *  - At least 144 bytes if ECDSA verify is used with a driver object in
 *    external memory (ECDSA component vector length).
 *
 */

/*! @cond NODOC */

#include <stdint.h>
#include <stdbool.h>

#include <ti/devices/DeviceFamily.h>
#include <ti/drivers/SHA2.h>
#include <ti/drivers/sha2/SHA2XXF3HSM.h>

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* SHA3 only supported for CC35XX */
    #include <ti/drivers/SHA3.h>
    #include <ti/drivers/sha3/SHA3XXF3HSM.h>
#endif

#include <ti/drivers/AESGCM.h>
#include <ti/drivers/aesgcm/AESGCMXXF3HSM.h>

#include <ti/drivers/AESECB.h>
#include <ti/drivers/aesecb/AESECBXXF3.h>

#include <ti/drivers/AESCTR.h>
#include <ti/drivers/aesctr/AESCTRXXF3.h>

#include <ti/drivers/AESCBC.h>
#include <ti/drivers/aescbc/AESCBCXXF3.h>

#include <ti/drivers/AESCMAC.h>
#include <ti/drivers/aescmac/AESCMACXXF3.h>

#include <ti/drivers/AESCCM.h>
#include <ti/drivers/aesccm/AESCCMXXF3.h>

#include <ti/drivers/ECDH.h>
#include <ti/drivers/ecdh/ECDHXXF3HSM.h>

#include <ti/drivers/ECDSA.h>
#include <ti/drivers/ecdsa/ECDSAXXF3HSM.h>

#include <ti/drivers/EDDSA.h>
#include <ti/drivers/eddsa/EDDSAXXF3HSM.h>

#include <ti/drivers/TRNG.h>
#include <ti/drivers/trng/TRNGXXF3HSM.h>

#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>

/*!
 *  @brief   Successful status code.
 *
 *  Functions return #HSMXXF3_STATUS_SUCCESS if the function was executed
 *  successfully.
 */
#define HSMXXF3_STATUS_SUCCESS ((int_fast16_t)0)

/*!
 *  @brief   Generic error status code.
 *
 *  Functions return #HSMXXF3_STATUS_ERROR if the function was not executed
 *  successfully and no more specific error is applicable.
 */
#define HSMXXF3_STATUS_ERROR ((int_fast16_t)-1)

/*!
 *  @brief   Timeout for polling mode response.
 *
 *  Functions return #HSMXXF3_STATUS_TIMEOUT if the #HSMXXF3_ReturnBehavior is
 *  set to #HSMXXF3_RETURN_BEHAVIOR_POLLING and the HSM does not provide an output
 *  token in sufficient time.
 */
#define HSMXXF3_STATUS_TIMEOUT ((int_fast16_t)-2)

/*!
 *  @brief   HSM is in Sleep Mode
 *
 *  Functions return #HSMXXF3_STATUS_TIMEOUT if the #HSMXXF3_ReturnBehavior is
 *  set to #HSMXXF3_RETURN_BEHAVIOR_POLLING and the HSM does not provide an output
 *  token in sufficient time.
 */
#define HSMXXF3_STATUS_IN_SLEEP_MODE ((int_fast16_t)-3)

/*!
 *  @brief  Acquiring a semaphore failed
 *
 *  Functions return #HSMXXF3_STATUS_RESOURCE_UNAVAILABLE if acquiring a
 *  semaphore failed.
 */
#define HSMXXF3_STATUS_RESOURCE_UNAVAILABLE ((int_fast16_t)-4)

/*!
 *  @brief  A required bounce buffer is not configured.
 *
 *  Returned when an operation targets external memory but the corresponding
 *  bounce buffer has `size` zero. Configure the buffer via SysConfig by
 *  enabling the relevant external memory type. If not using SysConfig, define
 *  an #HSMXXF3_BounceBuffer directly. See #HSMXXF3_BounceBuffers.
 */
#define HSMXXF3_STATUS_BOUNCE_UNAVAILABLE ((int_fast16_t)-5)

/* Co-processor ID for LAES */
#define HSMXXF3_LAES_COPROCESSOR_ID 0x1

/* The following defines are the default RNG configuration parameters */

/* Default TRNG parameters */
#define HSMXXF3_RNG_CONFG_TRNG_DEFAULT_AUTOSEED           0xFF
#define HSMXXF3_RNG_CONFG_TRNG_DEFAULT_SAMPLE_CYCLE       0x4BBE
#define HSMXXF3_RNG_CONFG_TRNG_MAX_SAMPLE_CYCLE           0x00
#define HSMXXF3_RNG_CONFG_DEFAULT_NOISEBLOCKS             0x01
#define HSMXXF3_RNG_CONFG_TRNG_DEFAULT_SCALE              0x01
#define HSMXXF3_RNG_CONFG_TRNG_DEFAULT_SAMPLEDIV          0x00
#define HSMXXF3_RNG_CONFG_TRNG_DEFAULT_REPCNTCUTOFF       0x09
#define HSMXXF3_RNG_CONFG_TRNG_DEFAULT_ADAPTPROP64CUTOFF  0x15
#define HSMXXF3_RNG_CONFG_TRNG_DEFAULT_ADAPTPROP512CUTOFF 0x47

/* Default CRNG parameters */
#define HSMXXF3_RNG_CONFG_CRNG_DEFAULT_AUTOSEED 0x1
#define HSMXXF3_RNG_CONFG_CRNG_DEFAULT_MIXCYCLE 0x2

#define HSMXXF3_RETVAL_MASK MASK_8_BITS

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* Power state defines from LPF3 to WFF3 mapping. */
    #define PowerLPF3_ENTERING_STANDBY PowerWFF3_ENTERING_SLEEP
    #define PowerLPF3_AWAKE_STANDBY    PowerWFF3_AWAKE_SLEEP
    #define PowerLPF3_DISALLOW_STANDBY PowerWFF3_DISALLOW_SLEEP

#endif

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
/*!
 *  @brief  Bounce buffer descriptor for HSM external-memory staging (CC35xx only).
 *
 *  The HSM on CC35xx cannot access external memory (PSRAM or external flash)
 *  directly. Crypto drivers stage data through internal-RAM buffers described
 *  by this type before submitting tokens to the HSM.
 *
 *  Setting `size` to zero disables the buffer; any operation that requires it
 *  returns #HSMXXF3_STATUS_BOUNCE_UNAVAILABLE. `buffer` must point to
 *  internal RAM aligned to 4 bytes and placed in `.internalRAM.bss` whenever
 *  `size` is non-zero.
 *
 *  See #HSMXXF3_BounceBuffers for size constraints and a usage example.
 */
typedef struct
{
    size_t size;     /*!< Capacity of the buffer in bytes; 0 disables the buffer */
    uint8_t *buffer; /*!< Pointer to the internal-RAM backing array */
} HSMXXF3_BounceBuffer;
#endif

/*!
 *  @brief  HSM firmware version
 *
 *  Used to represent the three-component version number of the HSM firmware.
 *  An instance of this struct is populated by #HSMXXF3_getFwVersion().
 */
typedef struct
{
    uint8_t patch; /*!< Patch version number */
    uint8_t minor; /*!< Minor version number */
    uint8_t major; /*!< Major version number */
} HSMXXF3_SystemInfoVersion;

/*!
 *  @brief  Enum for the NRBG engine type
 */
typedef enum
{
    HSMXXF3_MODE_CRNG = 1,
    HSMXXF3_MODE_TRNG = 2,
} HSMXXF3_NRBGMode;

/*!
 * @brief   The way in which #HSMXXF3_waitForResult() function calls return after performing an
 * calling #HSMXXF3_submitToken().
 *
 *
 * #HSMXXF3_waitForResult() has restrictions on the context from
 * which it may be called, depending on the return behavior.
 *
 * |                                   | Task  | Hwi   | Swi   |
 * |-----------------------------------|-------|-------|-------|
 * |HSMXXF3_RETURN_BEHAVIOR_CALLBACK   | X     | X     | X     |
 * |HSMXXF3_RETURN_BEHAVIOR_BLOCKING   | X     |       |       |
 * |HSMXXF3_RETURN_BEHAVIOR_POLLING    | X     | X     | X     |
 *
 */
typedef enum
{
    HSMXXF3_RETURN_BEHAVIOR_CALLBACK = 1, /*!< The #HSMXXF3_waitForResult() call will return immediately while
                                           *   the HSM operation goes on in the background. The registered
                                           *   callback function is called after the operation completes.
                                           *   The callback function is a driver-specific post-processing
                                           *   function that will be called from the common HWI.
                                           */

    HSMXXF3_RETURN_BEHAVIOR_BLOCKING = 2, /*!< The #HSMXXF3_waitForResult() call will block while the HSM
                                           *   operation goes on in the background. The HWI will post the
                                           *   semaphore. HSM operation results are available after the
                                           *   function returns.
                                           */

    HSMXXF3_RETURN_BEHAVIOR_POLLING = 4, /*!< The #HSMXXF3_waitForResult() call will continuously poll a flag
                                          *   while the HSM operation goes on in the background. The HWI will
                                          *   set the flag. SHA2 operation results are available after the
                                          *   function returns.
                                          */

} HSMXXF3_ReturnBehavior;

/*!
 *  @brief  Pointer to crypto driver post-processing functions.
 *
 *  Crypto drivers pass an #HSMXXF3_CallbackFxn as a parameter to #HSMXXF3_submitToken().
 *  In callback mode, the HSMXXF3 HWI will call the drivers' post-processing functions, as
 *  stored in the #HSMXXF3_Operation struct.
 */
typedef void (*HSMXXF3_CallbackFxn)(uintptr_t arg0);

/*!
 *  @brief  Struct to hold metadata for a crypto driver's operation.
 *
 *  #HSMXXF3_acquireLock() populates the #HSMXXF3_Operation.driverHandle while
 *  the rest of the metadata is populated by #HSMXXF3_submitToken(). The HWI
 *  accesses this stored information to respond to the calling driver.
 */
typedef struct
{
    Eip130Token_Command_t commandToken;
    Eip130Token_Result_t resultToken;
    HSMXXF3_ReturnBehavior returnBehavior;
    HSMXXF3_CallbackFxn callbackFxn;
    uintptr_t driverHandle;
} HSMXXF3_Operation;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
/*!
 *  @brief  Input bounce buffer; `size` 0 disables it.
 *
 *  When `size` is non-zero: at least 16 bytes, at least 128 if any SHA2
 *  driver object may reside in external memory, at least 96 if EdDSA
 *  operations are used with a driver object in external memory, and at least
 *  384 if EdDSA sign/verify is used with messages in external memory.
 *  See #HSMXXF3_BounceBuffers for full constraints and an example.
 */
extern HSMXXF3_BounceBuffer HSMXXF3_inputBounce;

/*!
 *  @brief  Output bounce buffer; `size` 0 disables it.
 *
 *  Only used for PSRAM output; may have `size` 0 when PSRAM is not used with
 *  crypto drivers. When `size` is non-zero: at least 16 bytes, at least 144
 *  if ECDSA or EdDSA sign operations are used with a driver object in external
 *  memory. See #HSMXXF3_BounceBuffers for full constraints and an example.
 */
extern HSMXXF3_BounceBuffer HSMXXF3_outputBounce;

/*!
 *  @brief  Auxiliary bounce buffer; `size` 0 disables it.
 *
 *  When `size` is non-zero: at least 16 bytes, at least 144 if ECDSA verify
 *  is used with a driver object in external memory, or at least 72 for EdDSA
 *  verify only. See #HSMXXF3_BounceBuffers for full constraints and an
 *  example.
 */
extern HSMXXF3_BounceBuffer HSMXXF3_auxBounce;
#endif

/*!
 *  @brief  Initializes the HWI and semaphores for HSMXXF3.
 *
 *  This function registers a hardware interrupt for result tokens
 *  from the HSM, and constructs the HSMXXF3_accessSemaphore and
 *  HSMXXF3_operationSemaphore.
 *
 *  This function should be called from driver init() functions.
 *
 *  @post   #HSMXXF3_init()
 */
void HSMXXF3_constructRTOSObjects(void);

/*!
 *  @brief  Disables clock for HSM, effectively powering it off.
 *
 *  This function provides an alternative to putting the HSM to sleep
 *  when it no longer needs to be used.
 */
void HSMXXF3_disableClock(void);

/*!
 *  @brief  Puts the HSM to sleep, lowering its power consumption.
 *
 *  This function submits a sleep token to the HSM, and waits for a
 *  successful token result.
 *
 *  Calling this function when the HSM is in sleep mode will
 *  return a HSMXXF3_STATUS_IN_SLEEP_MODE status code indicating
 *  that the HSM is already asleep.
 *
 *  @pre    #HSMXXF3_init() has to be called first.
 *
 *  @retval #HSMXXF3_STATUS_SUCCESS               HSM put to sleep successfully.
 *  @retval #HSMXXF3_STATUS_ERROR                 Error. Error output token, or HSM in bad state.
 */
int_fast16_t HSMXXF3_sleep(void);

/*!
 *  @brief  Revives the HSM from sleep mode.
 *
 *  This function submits a resume token to the HSM, and waits for a
 *  successful token result.
 *
 *  Calling this function when the HSM is not in sleep mode will do nothing.
 *
 *  @pre    #HSMXXF3_sleep() has to be called first.
 *
 *  @retval #HSMXXF3_STATUS_SUCCESS               HSM woke up from sleep successfully.
 *  @retval #HSMXXF3_STATUS_ERROR                 Error. Error output token, or HSM in bad state.
 */
int_fast16_t HSMXXF3_wakeUp(void);

/*!
 *  @brief  Initializes the HSM and HSMXXF3 driver for token submissions.
 *
 *  This function enables the HSM clock, initializes the HSM mailbox,
 *  boots the HSM, and performs extra initialization for the token submission
 *  process. The return value reflects if any of these operations fail.
 *
 *  This function should be called in driver construct() functions.
 *
 *  @pre    #HSMXXF3_constructRTOSObjects()
 *  @post   #HSMXXF3_acquireLock()
 *
 *  @retval #HSMXXF3_STATUS_SUCCESS               HSM booted and initialized successfully.
 *  @retval #HSMXXF3_STATUS_ERROR                 Error. Failed boot or mailbox initiailization.
 */
int_fast16_t HSMXXF3_init(void);

/*!
 *  @brief  Is HSM capable of decoupling DMA operations from ECC operations.
 *
 *  Checks the HSM FW version to arrive at that conclusion.
 *
 *  @pre    #HSMXXF3_init()
 *
 *  @retval true                                  ECDH and ECDSA DMA operations can happen on their own.
 *  @retval false                                 ECDH and ECDSA DMA operations have to happen within the ECC operation.
 */
bool HSMXXF3_isStandaloneDMASupportEnabled(void);

/*!
 *  @brief  Returns the HSM custom FW version.
 *
 *  The FW version is determined during #HSMXXF3_init(). Calling this
 *  function does not directly communicate with the HSM.
 *
 *  @param  [out] version   Pointer to struct to receive the FW version.
 *
 *  @pre    #HSMXXF3_init()
 *
 *  @retval #HSMXXF3_STATUS_SUCCESS   FW version returned successfully.
 *  @retval #HSMXXF3_STATUS_ERROR     HSM not yet initialized.
 */
int_fast16_t HSMXXF3_getFwVersion(HSMXXF3_SystemInfoVersion *version);

/*!
 *  @brief  Provisions the HUK to the HSM
 *
 *  @pre    #HSMXXF3_init() to initialize and boot up the HSM.
 *
 *  @retval #HSMXXF3_STATUS_SUCCESS                       Provisioning the HUK into the HSM was successful
 *  @retval #HSMXXF3_STATUS_ERROR                         Provisioning the HUK failed
 *  @retval #HSMXXF3_STATUS_RESOURCE_UNAVAILABLE          Error when acquiring a semaphore
 */
int_fast16_t HSMXXF3_provisionHUK(void);

/*!
 *  @brief  Acquires the HSMXXF3_accessSemaphore.
 *
 *  This function will attempt to take the HSMXXF3_accessSemaphore.
 *  The calling driver must decide whether timeout is
 *  SemaphoreP_NO_WAIT or another value.
 *
 *  @param  [in] timeout         Amount of time to wait for semaphore
 *                               to be posted.
 *
 *  @param  [in] driverHandle   The driver's handle.
 *
 *  @pre    #HSMXXF3_init() has to be called first.
 *  @post   #HSMXXF3_submitToken()
 *
 *  @retval Returns True on success, False on timeout
 */
bool HSMXXF3_acquireLock(uint32_t timeout, uintptr_t driverHandle);

/*!
 *  @brief  Releases the HSMXXF3_accessSemaphore.
 *
 *  This function will release the HSMXXF3_accessSemaphore.
 *  It will also clear the #HSMXXF3_Operation.driverHandle member.
 *
 *  @pre    #HSMXXF3_init() has to be called first.
 */
void HSMXXF3_releaseLock(void);

/*!
 *  @brief  Submits a token to the HSM mailbox.
 *
 *  This function will submit the operation.commandToken to the HSM mailbox
 *  and kick-off the HSM operation. It will also save the operation metadata
 *  to the HSMXXF3 driver, for use in #HSMXXF3_waitForResult().
 *
 *  @param  [in] retBehavior    Driver's return behavior for use in
 *                              #HSMXXF3_waitForResult().
 *
 *  @param  [in] callbackFxn    Pointer to driver's result post-processing
 *                              function. This post-processing function will
 *                              call the user-provided callback function, if
 *                              the driver is in callback mode.
 *
 *  @param  [in] driverHandle   The driver's handle.
 *
 *  @pre    #HSMXXF3_acquireLock() has to be successfully called first.
 *  @post   #HSMXXF3_waitForResult()
 *
 *  @retval #HSMXXF3_STATUS_SUCCESS               Token successfully written to HSM mailbox.
 *  @retval #HSMXXF3_STATUS_ERROR                 Error. Invalid token or unsuccessful write to mailbox.
 */
int_fast16_t HSMXXF3_submitToken(HSMXXF3_ReturnBehavior retBehavior,
                                 HSMXXF3_CallbackFxn callbackFxn,
                                 uintptr_t driverHandle);

/*!
 *  @brief  Waits for HSM response to previously submitted token.
 *
 *  This function is responsible for reporting the result back to the
 *  driver that submitted an operation request. Depending on the
 *  return behavior provided in #HSMXXF3_submitToken(), this function
 *  will poll a flag, block on an operation semaphore, or return
 *  immediately.
 *
 *  @pre    #HSMXXF3_submitToken() has to be called first.
 *
 *  @retval #HSMXXF3_STATUS_SUCCESS               Successfully waited for the result.
 *  @retval #HSMXXF3_STATUS_ERROR                 Error. Provided return behavior invalid.
 */
int_fast16_t HSMXXF3_waitForResult(void);

/*!
 *  @brief Cancels the operation currently in progress.
 *
 *  This API checks to see if there is an operation currently running.
 *  If so, wait on the HSM to finish in polling mode and clear the appropriate interrupts.
 *
 *  @retval #HSMXXF3_STATUS_SUCCESS               Successfully canceled operation in progress.
 *  @retval #HSMXXF3_STATUS_ERROR                 Error.
 */
int_fast16_t HSMXXF3_cancelOperation(void);

/*!
 *  @brief returns the value of HSMXXF3_operationInProgress
 *
 *  @retval true                        Operation in progress
 *  @retval false                       No operation in progress
 */
bool HSMXXF3_isOperationInProgress(void);

/*!
 *  @brief returns the value of HSMXXF3_operationInProgress
 *
 *  @retval HSMXXF3_NRBGMode            The current NRBG state
 */
HSMXXF3_NRBGMode HSMXXF3_getCurrentNRBGMode(void);

/*!
 *  @brief switch NRBG Mode CRNG -> TRNG or vice-versa
 *
 *  @pre Call TRNGXXF3HSM_switchNrbgMode() API with the newNrbgMode
 *
 */
void HSMXXF3_updateInternalNRBGMode();

/*
 *  ================ APIs to handle result token data ================
 */

/*!
 *  @brief  Get operation result code
 *
 *  This API should be called during a driver's post processing sequence after a call
 *  to #HSMXXF3_submitToken() that submits an asset creation token.
 *
 *  @retval Result token return code.
 */
int32_t HSMXXF3_getResultCode(void);

/*!
 *  @brief  Fetches the asset ID from the HSM's result token
 *
 *  This API should be called during a driver's post processing sequence after a call
 *  to #HSMXXF3_submitToken() that submits an asset creation token.
 *
 *  @retval Asset Identification Number
 */
uint32_t HSMXXF3_getResultAssetID(void);

/*!
 *  @brief  Copies a hash operation's final digest to user space
 *
 *  @deprecated Use #HSMXXF3_getResultHashState() for intermediate state
 *              retrieval. This function remains valid for final digest output.
 *
 *  @param  [out] digest        User specified destination address
 *  @param  [in]  digestLength  Digest length in bytes
 */
void HSMXXF3_getResultDigest(uint8_t *digest, size_t digestLength);

/*!
 *  @brief  Copies hash state from a result token
 *
 *  Extracts the intermediate hash state or final digest from the HSM result
 *  token into user-provided memory.
 *
 *  @param  [out] state        Destination buffer
 *  @param  [in]  stateLength  Number of bytes to copy
 */
void HSMXXF3_getResultHashState(uint8_t *state, size_t stateLength);

/*!
 *  @brief  Fetches the AES tag
 *
 *  @param  [in] mac                Pointer to copy tag to
 *  @param  [in] macLength          Length of mac to get
 */
void HSMXXF3_getAESEncryptTag(void *mac, size_t macLength);

/*!
 *  @brief  Fetches the AES IV
 *
 *  @param  [in] object             Pointer to copy iv to
 */
void HSMXXF3_getAESIV(uint8_t *iv);

/*!
 *  @brief  Fetches the Final mac from result token
 *
 *  @param  [in] mac                Buffer to copy mac to
 *  @param  [in] macLength          Length of the mac
 */
void HSMXXF3_getAESCMACSignMac(uint8_t *mac, uint8_t macLength);

/*!
 *  @brief  Fetches the content of a public data asset
 *
 *  @param  [in] assetId            Asset Identification Number
 *  @param  [in] data               Location to copy the data to
 *  @param  [in] dataLength         Data length
 */
void HSMXXF3_getPublicDataRead(uint32_t assetId, const uint8_t *data, uint8_t dataLength);

/*
 *  ================ APIs to construct key/asset management-related command tokens ================
 */

/*!
 *  @brief  Constructs an asset create command token
 *
 *  @param  [in] assetPolicy        User's asset policy to create an asset
 *
 *  @param  [in] assetLength        User's asset length to allocate in HSM RAM
 */
void HSMXXF3_constructCreateAssetToken(uint64_t assetPolicy, uint32_t assetLength);

/*!
 *  @brief  Constructs an asset load plaintext command token
 *
 *  @pre    A successfully conducted asset creation operation that returned an assetID.
 *
 *  @param  [in] input_p            User's asset policy to create an asset
 *
 *  @param  [in] inputLength        User's key material length which should be consistent
 *                                  with the key length passed during an asset create operation
 *
 *  @param  [in] assetId            Asset ID to load the key material to HSM RAM
 */
void HSMXXF3_constructLoadPlaintextAssetToken(const uint8_t *input_p, const uint32_t inputLength, uint32_t assetId);

/*!
 *  @brief  Constructs an asset delete command token
 *
 *  @param  [in] assetId            Asset ID of asset to delete in HSM RAM
 *
 *  @pre    A successfully conducted asset creation operation that returned an assetID.
 */
void HSMXXF3_constructDeleteAssetToken(uint32_t assetId);

/*!
 *  @brief  Constructs an export asset to coprocessor command token
 *
 *  @param  [in] assetId            Asset ID to export to coprocessor
 *
 *  @param  [in] copID              Coprocessor ID to export the asset to.
 *                                  Only HSMXXF3_LAES_COPROCESSOR_ID is supported currently.
 *
 *  @param  [in] copOffset          Coprocessor offset to export the asset to. For LAES coprocessor,
 *                                  this must be set to 0 to export to LAES key registers.
 *
 *  @pre    A successfully conducted asset creation operation that returned an assetID.
 *
 *  @retval #HSMXXF3_STATUS_SUCCESS  Token constructed successfully.
 *  @retval #HSMXXF3_STATUS_ERROR    Token construction failed due to unsupported coprocessor or offset.
 */
int_fast16_t HSMXXF3_constructExportAssetCopToken(uint32_t assetId, uint16_t copID, uint16_t copOffset);

/*
 *  ================ APIs to construct driver-specific command tokens ================
 */
/*!
 *  @brief  Constructs a SHA2 onestep/segmented command token
 *
 *  @param  [in] object             SHA2XXF3HSM object
 *
 */
void HSMXXF3_constructSHA2PhysicalToken(SHA2XXF3HSM_Object *object);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
/*!
 *  @brief  Constructs a SHA3 onestep/segmented command token
 *
 *  @param  [in] object             SHA3XXF3HSM object
 *
 */
void HSMXXF3_constructSHA3PhysicalToken(SHA3XXF3HSM_Object *object);
#endif

/*!
 *  @brief  Constructs a ECDH gen pub key command token
 *
 *  @param  [in] object             ECDHXXF3HSM_Object object
 */
void HSMXXF3_constructECDHGenPubPhysicalToken(ECDHXXF3HSM_Object *object);

/*!
 *  @brief  Constructs a ECDH gen shared secret command token
 *
 *  @param  [in] object             ECDHXXF3HSM_Object object
 */
void HSMXXF3_constructECDHGenShrdSecPhysicalToken(ECDHXXF3HSM_Object *object);

/*!
 *  @brief  Constructs a ECDH ECC key check command token
 *
 *  @param  [in] object             ECDHXXF3HSM_Object object
 */
void HSMXXF3_constructECDHVerifyKeysPhysicalToken(ECDHXXF3HSM_Object *object);

/*!
 *  @brief  Constructs a ECDSA sign/verify command token
 *
 *  @param  [in] object             ECDSAXXF3HSM object
 */
void HSMXXF3_constructECDSAPhysicalToken(ECDSAXXF3HSM_Object *object);

/*!
 *  @brief  Constructs a EDDSA gen pub key command token
 *
 *  @param  [in] object             ECDSAXXF3HSM object
 */
void HSMXXF3_constructEDDSAGenPubKeyPhysicalToken(EDDSAXXF3HSM_Object *object);

/*!
 *  @brief  Constructs an EDDSA sign initial command token
 *
 *  @param  [in] object             EDDSAXXF3HSM object
 */
void HSMXXF3_constructEDDSASignInitialPhysicalToken(EDDSAXXF3HSM_Object *object);

/*!
 *  @brief  Constructs an EDDSA intermediate hash command token
 *
 *  @param  [in] input              Data buffer input address.
 *  @param  [in] inputLength        Data buffer input length.
 *  @param  [in] tempAssetID        Asset ID holding the intermediate digest.
 */
void HSMXXF3_constructEDDSAIntermediateHashPhysicalToken(const uint8_t *input,
                                                         size_t inputLength,
                                                         uint32_t tempAssetID);

/*!
 *  @brief  Constructs an EDDSA sign update command token
 *
 *  @param  [in] object             EDDSAXXF3HSM object
 */
void HSMXXF3_constructEDDSASignUpdatePhysicalToken(EDDSAXXF3HSM_Object *object);

/*!
 *  @brief  Constructs an EDDSA sign finalize command token
 *
 *  @param  [in] object             EDDSAXXF3HSM object
 */
void HSMXXF3_constructEDDSASignFinalizePhysicalToken(EDDSAXXF3HSM_Object *object);

/*!
 *  @brief  Constructs an EDDSA verify initial command token
 *
 *  @param  [in] object             EDDSAXXF3HSM object
 */
void HSMXXF3_constructEDDSAVerifyInitialPhysicalToken(EDDSAXXF3HSM_Object *object);

/*!
 *  @brief  Constructs an EDDSA verify final command token
 *
 *  @param  [in] object             EDDSAXXF3HSM object
 */
void HSMXXF3_constructEDDSAVerifyFinalizePhysicalToken(EDDSAXXF3HSM_Object *object);

/*!
 *  @brief  Constructs an AES-GCM Token
 *
 *  @param  [in] object             The AESGCMXXF3HSM object that contains necessary data.
 *  @param  [in] saveIV             Should the IV be saved to temporary state asset.
 *  @param  [in] loadIV             Should the IV be loaded from a temporary state asset.
 */
void HSMXXF3_constructGCMToken(const AESGCMXXF3HSM_Object *object, bool saveIV, bool loadIV);

/*!
 *  @brief  Constructs an AES-CCM Token
 *
 *  @param  [in] object             The AESCCMXXF3 object that contains necessary data.
 *  @param  [in] saveIV             Should the IV be saved to temporary state asset.
 *  @param  [in] loadIV             Should the IV be loaded from a temporary state asset.
 */
void HSMXXF3_constructCCMToken(const AESCCMXXF3_Object *object, bool saveIV, bool loadIV);

/*!
 *  @brief  Constructs an AES-ECB one-step command token
 *
 *  @param  [in] object             The AESECBXXF3 object that contains necessary data
 *  @param  [in] key                Pointer to key material if it has been retrieved in plaintext
 */
void HSMXXF3_constructAESECBOneStepPhysicalToken(AESECBXXF3_Object *object, uint8_t *key);

/*!
 *  @brief  Constructs an AES-CTR one-step command token
 *
 *  @param  [in] object             The AESCTRXXF3 object that contains necessary data
 *  @param  [in] key                Pointer to key material if it has been retrieved in plaintext
 */
void HSMXXF3_constructAESCTROneStepPhysicalToken(AESCTRXXF3_Object *object, uint8_t *key);

/*
 *  @brief  Constructs an AES-CBC one-step command token
 *
 *  @param  [in] object             The AESCBCXXF3 object that contains necessary data
 *  @param  [in] key                Pointer to key material if it has been retrieved in plaintext
 */
void HSMXXF3_constructAESCBCOneStepPhysicalToken(AESCBCXXF3_Object *object, uint8_t *key);

/*!
 *  @brief  Constructs an AES-CMAC Token
 *
 *  @param  [in] object             The AESCMACXXF3 object that contains necessary data
 *  @param  [in] isFirst            Is the operation a new to continue or new to final.
 *  @param  [in] isFinal            Is the operation continue to final or new to final.
 */
void HSMXXF3_constructCMACToken(AESCMACXXF3_Object *object, bool isFirst, bool isFinal);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1)
/*!
 *  @brief  Constructs an RNG configure token for CRNG/TRNG operations command token
 *
 *  @warning Submitting tokens constructed by this function is currently not
 *           supported. The #HSMXXF3_submitToken() function will unconditionally
 *           return #HSMXXF3_STATUS_ERROR if using tokens constructed by this
 *           function.
 *
 *  @param  [in] object             The TRNGXXF3HSM_Object object that contains necessary data
 */
void HSMXXF3_constructRNGSwitchNRBGWithDefaultsPhysicalToken(HSMXXF3_NRBGMode HSMXXF3_nrbgMode);

/*!
 *  @brief  Constructs an RNG configure token tailored to reseed the DRBG engine command token
 *
 *  @warning Submitting tokens constructed by this function is currently not
 *           supported. The #HSMXXF3_submitToken() function will unconditionally
 *           return #HSMXXF3_STATUS_ERROR if using tokens constructed by this
 *           function.
 *
 */
void HSMXXF3_constructRNGReseedDRBGPhysicalToken(void);
#endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1) \
        */

/*!
 *  @brief  Constructs an RNG get random number command token
 *
 *  @param  [in] entropyBuffer      The buffer to deposit the entropy into.
 *  @param  [in] entropyRequested   The size of the entropy requested.
 */
void HSMXXF3_constructRNGGetRandomNumberPhysicalToken(uintptr_t entropyBuffer, size_t entropyRequested);

/*!
 *  @brief  Constructs an RNG get raw random number command token
 *
 *  @param  [in] entropyBuffer      The buffer to deposit the entropy into.
 *  @param  [in] entropyRequested   The size of the entropy requested.
 */
void HSMXXF3_constructRNGGetRawRandomNumberPhysicalToken(uintptr_t entropyBuffer, size_t entropyRequested);

/*! @endcond */
