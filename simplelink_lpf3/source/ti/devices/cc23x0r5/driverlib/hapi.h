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

#ifndef __HAPI_H__
#define __HAPI_H__

#include <stdint.h>
#include "sha256sw.h"

/*! Magic value used to protect against inadvertent flash erasures/programming.
 *  (prevents corruption due to random jumps into the flash API, for example
 *  due to stack overflow or errant function pointers)
 *  Must be passed in key argument to all flash functions
 */
#define FLASH_API_KEY 0xB7E3A08F

/*! Define HAPI table and the functions it points to */
typedef struct
{
    //  0: Enter standby power state (from privileged thread mode with MSP as call stack)
    void (*enterStandby)(const uint32_t *copyList);
    //  1: [Utility] Calculate CRC32 over nBytes bytes at data
    uint32_t (*crc32)(const uint8_t *data, uint32_t nBytes);
    //  2: Apply copy list
    void (*applyCopyList)(const uint32_t *list);
    //  3: Erase (main) flash sector
    uint32_t (*flashSectorErase)(uint32_t key, uint32_t sectorAddress);
    //  4: Erase (main) flash bank
    uint32_t (*flashBankErase)(uint32_t key);
    //  5: Program (main) flash sector
    uint32_t (*flashProgram)(uint32_t key, const uint8_t *dataBuffer, uint32_t address, uint32_t nBytes);
    //  6: [Utility] Hamming weight of 32b word (number of bits set)
    uint32_t (*countBits)(uint32_t word);
    //  7: [Utility] Perform SECDED encoding on array of 64b words
    void (*secdedEncode)(uint8_t *parity, const uint64_t *data, uint32_t nWords64);
    //  8: [Utility] Perform SECDED detection/correction on array of 64b words and parity bytes
    int32_t (*secdedDecode)(uint64_t *data, const uint8_t *parity, uint32_t nWords64);
    // 9: Function to be called from boot code or bootloader to enter application properly
    void (*enterApplication)();
    // 10: SHA256: hash single block of data and produce digest
    int_fast16_t (*sha256SwHashData)(SHA256SW_Handle handle,
                                     SHA2SW_HashType hashType, // Only SHA2SW_HASH_TYPE_256 supported
                                     const void *data,
                                     size_t length,
                                     uint32_t digest[8]);
    // 11: SHA256: initialize hash state
    int_fast16_t (*sha256SwStart)(SHA256SW_Handle handle,
                                  SHA2SW_HashType hashType // Only SHA2SW_HASH_TYPE_256 supported
    );
    // 12: SHA256: update hash with data
    int_fast16_t (*sha256SwAddData)(SHA256SW_Handle handle, const void *data, size_t length);
    // 13: SHA256: finalize and produce digest
    int_fast16_t (*sha256SwFinalize)(SHA256SW_Handle handle, uint32_t digest[8]);
    // 14: [Utility] Reset device
    void (*resetDevice)(void);
    // 15: SHA256: Process Block
    void (*sha256SwProcessBlock)(uint32_t digest[8], uint32_t Ws[16]);
    // 16: SHA256: Round constants
    const uint32_t (*sha256SW_K256)[64];
    // 17: SHA256: Initial constants
    const uint32_t (*sha256SW_initialDigest256)[8];
    // 18: Busy loop that waits for nUs microseconds
    void (*waitUs)(uint32_t nUs);
    // 19: Count leading zeros
    uint32_t (*clz)(uint32_t x);
} HARD_API_T;

// Define address of HAPI table in ROM and macro for pointer to it
#define HAPI_TABLE_BASE_ADDR 0x0F00004C
#define HAPI_TABLE_POINTER   ((const HARD_API_T *)HAPI_TABLE_BASE_ADDR)

// ------------------------------------------------------------
// Macros used in applications to actually call HAPI functions
// ------------------------------------------------------------

// void HapiEnterStandby(const uint32_t *copyList)
/*****************************************************************************
 * \brief Enter standby power state
 * Stores the full state of the CPU to MSP call stack so that it can get
 * restored once we come back out of standby (at which point CPU is reset).
 * When exiting standby the CPU will appear to return from this function.
 *
 * \param[in] copyList
 *     If non-null, the copy list to apply through ApplyCopyList() in the
 *     AsmExitStandby function while waiting for flash to become ready.
 *
 * \pre
 *   - Execution state is privileged and call stack being used is MSP
 *   - MSP call stack must reside in retained SRAM (obviously)
 *   - Interrupts have been turned off with CPSID but interrupts enabled in NVIC
 *   - Wakeup event(s) have been configured in AON event fabric
 *   - SCB.SCR.DSLP_EN=0 (if not, in debug standby exit will enter standby again)
 * \warning
 *     The preconditions must be followed to the letter or bad things will happen
 * \note
 *     Clobbers r0-r3 (normal per AAPCS)
 *****************************************************************************/
#define HapiEnterStandby(p) HAPI_TABLE_POINTER->enterStandby((p))

// uint32_t HapiCrc32(const uint8_t *data, uint32_t nBytes)
/*****************************************************************************
 * \brief Calculate CRC32 over a data image
 * CRC32 implementation that uses a 256-entry LUT
 *
 * \param[in] data
 *     Pointer to the image data
 * \param[in] nBytes
 *     Size of image in bytes
 *
 * \return
 *      CRC-32 checksum of the image
 *****************************************************************************/
#define HapiCrc32(p, n) HAPI_TABLE_POINTER->crc32((p), (n))

// void HapiApplyCopyList(const uint32_t *list)
/*****************************************************************************
 * \brief Process copy list
 * Processes a copy list in a flexible CopyList format. Used by trims
 * in FCFG, for user-defined initialization in CCFG and may be used by
 * peripheral drivers to do HW reinitialization during wakeup from standby.
 * The copy list is processed as a sequence of 32b command words, followed by
 * zero or more literal words (LW):
 *
 * Command      |31:28|27:20    |19:2                  |1:0|LW|Description
 * -------------|-----|---------|----------------------|---|--|-------------------
 * EOL          |0000 |0000_0000|0000_0000_0000_0000_00|00 |0 |End-of-list
 * WAIT(N)      |0001 |0000_0000|nnnn_nnnn_nnnn_nnnn_nn|00 |0 |Wait N/12 us
 * NOP = WAIT(0)|0001 |0000_0000|0000_0000_0000_0000_00|00 |0 |No operation
 * CPY(A*,N)    |aaaa |nnnn_nnnn|aaaa_aaaa_aaaa_aaaa_aa|00 |N |Copy N literal words to address A*
 * CPY(A,1)     |aaaa |aaaa_aaaa|aaaa_aaaa_aaaa_aaaa_aa|01 |1 |Copy single literal word to full address A
 * JMP(A)       |aaaa |aaaa_aaaa|aaaa_aaaa_aaaa_aaaa_aa|10 |0 |Jump to new list at full address A
 * CALL(A)      |aaaa |aaaa_aaaa|aaaa_aaaa_aaaa_aaaa_aa|11 |0 |Recurse to list at full address A
 *
 * A* is a reduced address space that covers all SRAM and peripheral space.
 * Bits 27:20 of this address will be assumed to be all zero. Full addresses
 * must have 32b alignment
 *
 * \param[in] list
 *     Pointer to the copy list
 *****************************************************************************/
#define HapiApplyCopyList(p) HAPI_TABLE_POINTER->applyCopyList((p))

// uint32_t HapiFlashSectorErase(uint32_t key, uint32_t addr);
/*****************************************************************************
 * \brief Erase a flash sector.
 *
 * Erase the flash sector that begins at address addr. Function will not return
 * before erase operation completes or error occurs. Only main sectors and the
 * CCFG sector is supported and are subject to flash write/erase restrictions.
 * No default data is written back to CCFG after an erase.
 *
 * \warning No accesses to flash may occur during an erase operation. Interrupts
 * must be disabled prior to calling or care taken that no reads to flash occur.
 * DMA operations targeting flash must be suspended.
 *
 * \param key
 *     Magic number \ref FLASH_API_KEY (0xB7E3A08F) to protect against inadvertent
 *     flash erasures
 * \param addr
 *     First address of a main sector or the CCFG sector
 *
 * \return
 *     Return code
 *     - \ref FAPI_STATUS_SUCCESS (0)
 *     - \ref FAPI_STATUS_ADDRESS_ERROR
 *     - \ref FAPI_STATUS_INVALID_KEY
 *     - \ref FAPI_STATUS_FSM_ERROR
 *****************************************************************************/
#define HapiFlashSectorErase(k, p) HAPI_TABLE_POINTER->flashSectorErase((k), (p))

// uint32_t HapiFlashBankErase(uint32_t key);
/******************************************************************************
 * \brief Erase all unprotected sectors in the flash main bank.
 *
 * Function will not return before mass erase operation completes or error occurs.
 *
 * \warning No accesses to flash may occur during an erase operation. Interrupts
 * must be disabled prior to calling or care taken that no reads to flash occur.
 * DMA operations targeting flash must be suspended.
 *
 * \param key
 *     Magic number \ref FLASH_API_KEY (0xB7E3A08F) to protect against inadvertent
 *     flash erasures
 *
 * \return
 *     Return code
 *     - \ref FAPI_STATUS_SUCCESS (0)
 *     - \ref FAPI_STATUS_INVALID_KEY
 *     - \ref FAPI_STATUS_FSM_ERROR
 *****************************************************************************/
#define HapiFlashBankErase(k) HAPI_TABLE_POINTER->flashBankErase((k))

// uint32_t HapiFlashProgram(uint32_t key, const uint8_t *data, uint32_t addr, uint32_t nBytes)
/******************************************************************************
 * \brief Program to flash (MAIN or CCFG)
 *
 * This function programs a sequence of bytes into the on-chip flash.
 * Programming each location consists of the result of an AND operation
 * of the new data and the existing data; in other words bits that contain
 * 1 can remain 1 or be changed to 0, but bits that are 0 cannot be changed
 * to 1. Therefore, a byte can be programmed multiple times as long as these
 * rules are followed; if a program operation attempts to change a 0 bit to
 * a 1 bit, that bit will not have its value changed.
 *
 * Programming may cross main sector boundaries. This function does not
 * return until the data has been programmed or a programming error occurs.
 *
 * \note It is recommended to disable cache and line buffer before
 * programming the flash and re-enable/clear cache and line buffer when the
 * program operation completes.
 *
 * \warning Please note that code can not execute in flash while any part of
 * the flash is being programmed or erased. The application must disable
 * interrupts that have interrupt routines in flash.
 *
 * \warning The \c data pointer can not point to flash.
 *
 * \param key
 *     Magic number that must be \ref FLASH_API_KEY. The key protects against
 *     random jumps into the flash API
 * \param data
 *     Pointer to the byte array of new data to be programmed
 * \param addr
 *     First byte address in flash to be programmed
 * \param nBytes
 *     Number of bytes to be programmed
 *
 * \return
 *     Return code
 *     - \ref FAPI_STATUS_SUCCESS (0)
 *     - \ref FAPI_STATUS_ADDRESS_ERROR
 *     - \ref FAPI_STATUS_INVALID_KEY
 *     - \ref FAPI_STATUS_INCORRECT_DATABUFFER_LENGTH
 *     - \ref FAPI_STATUS_FSM_ERROR
 *****************************************************************************/
#define HapiFlashProgram(k, s, d, n) HAPI_TABLE_POINTER->flashProgram((k), (s), (d), (n))

// uint32_t HapiCountBits(uint32_t word)
/*****************************************************************************
 * \brief Return Hamming weight (# bits that are set) of word
 *
 * \param[in] word
 *     32-bit word to count bits for
 *
 * \return
 *     Number of bits set in word (0-32)
 *****************************************************************************/
#define HapiCountBits(w) HAPI_TABLE_POINTER->countBits((w))

// void HapiSecdedEncode(uint8_t *parity, const uint64_t *data, uint32_t nWords64)
/*****************************************************************************
 * \brief Perform SECDED encoding over data array and produce parity array
 * Uses the usual (72,64) SECDED generator matrix:
 *     DDDDDDDD DDDDDDDD DDDDDDDD DDDDDDDD DDDDDDDD DDDDDDDD DDDDDDDD DDDDDDDD  PPPPPPPP
 *     66665555 55555544 44444444 33333333 33222222 22221111 11111100 00000000  00000000
 *     32109876 54321098 76543210 98765432 10987654 32109876 54321098 76543210  76543210
 * -------------------------------------------------------------------------------------
 * P7: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111  01111111
 * P6: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111110  00000000
 * P5: 11111111 11111111 11111111 11111111 00000000 00000000 00000000 00000001  00000000
 * P4: 11111111 11111111 00000000 00000000 11111111 11111111 00000000 00000001  00000000
 * P3: 11111111 00000000 11111111 00000000 11111111 00000000 11111111 00000001  00000000
 * P2: 11110000 11110000 11110000 11110000 11110000 11110000 11110000 11110001  00000000
 * P1: 11001100 11001100 11001100 11001100 11001100 11001100 11001100 11001101  00000000
 * P0: 10101010 10101010 10101010 10101010 10101010 10101010 10101010 10101011  00000000
 *
 * \param[out] parity
 *     Pointer to where to store parity bytes (one byte per 64b word of data)
 * \param[in]  data
 *     Pointer to the data (4B aligned)
 * \param[in]  nWords64
 *     Number of 64b words of data / bytes of parity
 *****************************************************************************/
#define HapiSecdedEncode(p, d, n) HAPI_TABLE_POINTER->secdedEncode((p), (d), (n))

// int32_t HapiSecdedDecode(uint64_t *data, const uint8_t *parity, uint32_t nWords64)
/*****************************************************************************
 * \brief Perform SECDED correction/detection over data array using parity array
 * Uses the usual (72,64) SECDED generator matrix.
 *
 * \param[inout] data
 *     Pointer to the data (4B aligned)
 * \param[in]    parity
 *     Pointer to the parity bytes (one byte per 64b word of data)
 * \param[in]    nWords64
 *     Number of 64b words of data / bytes of parity
 *
 * \return
 *     <0:  uncorrectable error detected
 *     >=0: number of bits corrected
 *****************************************************************************/
#define HapiSecdedDecode(d, p, n) HAPI_TABLE_POINTER->secdedDecode((d), (p), (n))

// void BootEnterApplication(void)
/*****************************************************************************
 * \brief Called from bootloader to transfer into application
 * When called from a bootloader this function will apply application security
 * restrictions and transfer to application (set up VTOR register, setup SP and
 * jump to entry point as defined by application vector table in CCFG). The
 * function will never return.
 *
 * When called from an application the function will return without doing
 * anything.
 *****************************************************************************/
#define HapiEnterApplication() HAPI_TABLE_POINTER->enterApplication()

// int_fast16_t HapiSha256SwHashData(
//     SHA256SW_Handle handle,
//     const void *data,
//     size_t length,
//     uint32_t digest[8]
// )
/*****************************************************************************
 *  \brief  Performs a complete SHA256 hash operation, producing a final
 *          digest for the data.
 *
 *  This function wraps #HapiSha256SwStart(), #HapiSha256SwAddData(), and
 *  #HapiSha256SwFinalize().
 *
 *  There is no need to call #HapiSha256SwStart() prior to calling this function.
 *
 *  The total length of data that can be hashed by this implementation
 *  is 512MiB (0x20000000 bytes.)
 *
 *  \param[in]   handle    A #SHA256SW_Handle.
 *
 *  \param[in]   data      Data (message) to hash. May point to zero.
 *
 *  \param[in]   length    The number of bytes (pointed to by \c data parameter)
 *                         to add to the hash.
 *
 *  \param[out]  digest    Output location for the final digest. Must be
 *                         able to hold 32 bytes of output and be 32-bit aligned.
 *
 *  \retval #SHA2SW_STATUS_SUCCESS (0)         The hash operation succeeded.
 *  \retval #SHA2SW_STATUS_ERROR               The hash operation failed.
 *  \retval #SHA2SW_STATUS_UNSUPPORTED         Requested Hash Type is unsupported.
 *  \retval #SHA2SW_STATUS_LENGTH_TOO_LARGE    The requested length of data to hash
 *                                             is more than the implementation
 *                                             supports.
 *  \retval #SHA2SW_STATUS_NULL_INPUT          One or more of the pointer inputs is
 *                                             NULL.
 *****************************************************************************/
#define HapiSha256SwHashData(h, d, l, g) HAPI_TABLE_POINTER->sha256SwHashData((h), SHA2SW_HASH_TYPE_256, (d), (l), (g))

// int_fast16_t HapiSha256SwStart(SHA256SW_Handle handle)
/*****************************************************************************
 *  \brief  Initialize a SHA256SW_Handle, preparing for hashing data.
 *
 *  \param[in]  handle    A #SHA256SW_Handle.
 *
 *  \retval #SHA2SW_STATUS_SUCCESS (0)         The hash operation succeeded.
 *  \retval #SHA2SW_STATUS_UNSUPPORTED         Requested Hash Type is unsupported.
 *  \retval #SHA2SW_STATUS_NULL_INPUT          One or more of the pointer inputs is
 *                                             NULL.
 *
 *  \sa     #HapiSha256SwAddData()
 *  \sa     #HapiSha256SwFinalize()
 *****************************************************************************/
#define HapiSha256SwStart(h) HAPI_TABLE_POINTER->sha256SwStart((h), SHA2SW_HASH_TYPE_256)

// int_fast16_t HapiSha256SwAddData(SHA256SW_Handle handle, const void *data, size_t length)
/*****************************************************************************
 *  \brief  Add data to a SHA256 operation.
 *
 *  Adds data to a hash operation. The \c handle must have been
 *  initialized by a call to HapiSha256SwStart first.
 *
 *  The total length of data that can be hashed by this implementation
 *  is 512MiB (0x20000000 bytes.)
 *
 *  After passing in all data to be hashed, call #HapiSha256SwFinalize()
 *  to obtain the final digest.
 *
 *  \pre    handle was previously passed to #HapiSha256SwStart().
 *
 *  \param[in]  handle   A #SHA256SW_Handle.
 *
 *  \param[in]  data     Data (message) to add to the hash. May point to zero.
 *
 *  \param[in]  length   The number of bytes (pointed to by \c data parameter)
 *                       to add to the hash.
 *
 *  \retval #SHA2SW_STATUS_SUCCESS (0)         The hash operation succeeded.
 *  \retval #SHA2SW_STATUS_LENGTH_TOO_LARGE    The requested length of data to hash
 *                                             is more than the implementation
 *                                             supports.
 *  \retval #SHA2SW_STATUS_NULL_INPUT          One or more of the pointer inputs is
 *                                             NULL.
 *
 *  \sa     #HapiSha256SwStart()
 *  \sa     #HapiSha256SwFinalize()
 *****************************************************************************/
#define HapiSha256SwAddData(h, d, l) HAPI_TABLE_POINTER->sha256SwAddData((h), (d), (l))

// int_fast16_t HapiSha256SwFinalize(SHA256SW_Handle handle, uint32_t digest[8]);
/*****************************************************************************
 *  \brief  Finalize a SHA256 operation, creating the final digest.
 *
 *  After calling this function, \c handle should not be used again
 *  until it has been reinitialized via a call to #HapiSha256SwStart().
 *
 *  \pre    handle was previously passed to #HapiSha256SwStart() and data to
 *          be hashed was passed to #HapiSha256SwAddData()
 *
 *  \param[in]  handle  A #SHA256SW_Handle.
 *
 *  \param[out] digest  Output location for the final digest. Must be
 *                      able to hold 32 bytes of output and be 32-bit aligned.
 *
 *  \retval #SHA2SW_STATUS_SUCCESS (0)         The hash operation succeeded.
 *  \retval #SHA2SW_STATUS_NULL_INPUT          One or more of the pointer inputs is
 *                                             NULL.
 *
 *  \sa     #HapiSha256SwStart()
 *  \sa     #HapiSha256SwAddData()
 *****************************************************************************/
#define HapiSha256SwFinalize(h, g) HAPI_TABLE_POINTER->sha256SwFinalize((h), (g))

// __noreturn void HapiResetDevice(void)
/*****************************************************************************
 * \brief Perform system reset of the device
 *
 * This function will perform a system reset of the device equal to a pin
 * reset. Software can determine that this was the cause of reset once
 * rebooted. The function will never return.
 *****************************************************************************/
#define HapiResetDevice() HAPI_TABLE_POINTER->resetDevice()

// HAPI entry used for internal purposes
#define HapiSha256SWProcessBlock(d, w) HAPI_TABLE_POINTER->pSHA256SWProcessBlock((d), (w))

// HAPI entry used for internal purposes
#define HapiSha256SW_K256 (*HAPI_TABLE_POINTER->sha256SW_K256)

// HAPI entry used for internal purposes
#define HapiSha256SW_initialDigest256 (*HAPI_TABLE_POINTER->sha256SW_initialDigest256)

// void HapiWaitUs(uint32_t nUs)
/*****************************************************************************
 * \brief Wait function
 *
 * \param[in] nUs
 *     Number of microseconds to wait (min: 1 us, max: 2^24 us)
 *****************************************************************************/
#define HapiWaitUs(n) HAPI_TABLE_POINTER->waitUs((n))

// uint32_t HapiClz(uint32_t x)
/*****************************************************************************
 * \brief Count leading zeros
 *
 * \param[in] x
 *     Value to count leading zeros for
 * \return
 *     Number of leading zeroes (0 to 32)
 *****************************************************************************/
#define HapiClz(x) HAPI_TABLE_POINTER->clz((x))

#endif //__HAPI_H__
