/*This file is AUTO GENERATED, DO NOT EDIT manually*/

/*
 * Copyright (c) 2024, Texas Instruments Incorporated
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

/**
 * @defgroup DL_FLASH_AM13E230X  Driverlib FLASH API
 * @ingroup DL_AM13E230X
 *
 * The module gives APIs to erase and program flash banks and sectors in
 * the AM13E230X Non-Volatile memory system.
 *
 *  Recommend users to use this API vs \ref  DL_FLASHCTL_AM13E230X
 *
 *
 *
 * @{
 */

#ifndef DL_FLASH_H
#define DL_FLASH_H

#include <stdbool.h>
#include <stdint.h>

#include <soc.h>
#include <dl_common.h>
#include <dl_factoryregion.h>
#include <dl_sysctl.h>
#include <dl_flashctl.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Size of Flash Bank in bytes
 */
#define DL_FLASH_BANK_SIZE (0x40000U)

/*!
 * @brief Size of Flash Sector in bytes
 */
#define DL_FLASH_SECTOR_SIZE (0x800U)

/*!
 * @brief Size of Non-Main Flash Bank in bytes
 */
#define DL_FLASH_NONMAIN_BANK_SIZE (0x1000U)

/*!
 * @brief The Flash API operation completed successfully
 */
#define DL_FLASH_SUCCESS (0x0U)

/*!
 * @brief The Flash address is not 64-bit aligned
 */
#define DL_FLASH_ADDR_INVALID_ALIGN (0x1U)

/*!
 * @brief The Flash address is not sector aligned
 */
#define DL_FLASH_ADDR_INVALID_SECTOR (0x2U)

/*!
 * @brief The Flash address is not bank aligned
 */
#define DL_FLASH_ADDR_INVALID_BANK    (0x3U)
/*!
 * @brief Failure in execution of Flash Program command
 */
#define DL_FLASH_COMMAND_FAIL_PROGRAM (0x4U)

/*!
 * @brief Failure in execution of Flash Erase command
 */
#define DL_FLASH_COMMAND_FAIL_ERASE (0x5U)

/*!
 * @brief Failure in execution of Flash Read Verify command
 */
#define DL_FLASH_COMMAND_FAIL_READ_VERIFY (0x6U)

/*!
 * @brief Failure in execution of Blank Verify command
 */
#define DL_FLASH_COMMAND_FAIL_BLANK_VERIFY (0x7U)

/*!
 * @brief The programming buffer is a NULL pointer
 */
#define DL_FLASH_INVALID_BUFFER (0x8U)

/*!
 * @brief The number of bytes to be programmed is either zero or exceeds bank boundaries
 */
#define DL_FLASH_INVALID_NUMBYTES (0x9U)

/*!
 * @brief The Flash address is not in Flash memory region
 */
#define DL_FLASH_ADDR_INVALID (0xAU)
/*!
 * @brief The Flash address is in non main Flash memory region
 */
#define DL_FLASH_ADDR_NONMAIN (0xBU)
/*!
 * @brief The acquire flash semaphore failed
 */
#define DL_FLASH_SEM_ACQ_FAIL (0xCU)
/*!
 * @brief The release flash semaphore failed
 */
#define DL_FLASH_SEM_REL_FAIL (0xDU)

/**
 *  @brief      Performs bank erase of the given bank address
 *
 *  This function erases an entire flash bank at the specified address. The function validates
 *  the address to ensure it is bank-aligned and not in the active bank . It acquires
 *  the flash semaphore, unprotects the memory, performs the erase operation, and releases
 *  the semaphore before returning.
 *
 *  @param[in]  flashAddr  The flash bank memory address (must be bank-aligned)
 *
 *  @return     uint32_t indicating the operation status:
 *              - DL_FLASH_SUCCESS: Operation completed successfully
 *              - DL_FLASH_ADDR_INVALID: Address is not in Flash
 *              - DL_FLASH_ADDR_INVALID_BANK: Address is not bank-aligned
 *              - DL_FLASH_COMMAND_FAIL_ERASE: Erase command failed
 *              - DL_FLASH_COMMAND_FAIL_BLANK_VERIFY: Blank verify failed after erase
 *
 *  @note       This API should not be called for active flash banks (Bank 0 is protected)
 *  @note       This API sets all main memory of the given bank to unprotected from erase/program
 */
uint32_t DL_Flash_eraseBank(uint32_t flashAddr);

/**
 *  @brief      Performs sector erase of the given sector address
 *
 *  This function erases a single flash sector at the specified address. The function validates
 *  the address to ensure it is sector-aligned and not in the active bank . It acquires
 *  the flash semaphore, unprotects the sector, performs the erase operation, and releases
 *  the semaphore before returning.
 *
 *  @param[in]  flashAddr  The flash sector memory address (must be sector-aligned)
 *
 *  @return     uint32_t indicating the operation status:
 *              - DL_FLASH_SUCCESS: Operation completed successfully
 *              - DL_FLASH_ADDR_INVALID: Address is not in Flash
 *              - DL_FLASH_ADDR_INVALID_SECTOR: Address is not sector-aligned
 *              - DL_FLASH_COMMAND_FAIL_ERASE: Erase command failed
 *              - DL_FLASH_COMMAND_FAIL_BLANK_VERIFY: Blank verify failed after erase
 *
 *  @note       This API should not be called for active flash banks (Bank 0 is protected)
 *  @note       This API unprotects the specified sector for erase operation
 */
uint32_t DL_Flash_eraseSector(uint32_t flashAddr);

/**
 *  @brief      Programs the given buffer at the supplied address with automatic ECC generation
 *
 *  This function programs flash memory starting from the specified address with the provided data.
 *  It automatically handles 128-bit (16-byte), 64-bit (8-byte), and smaller writes with padding.
 *  ECC codes are automatically generated for all writes. The function validates all input parameters,
 *  acquires the flash semaphore, performs the programming and verification operations, and releases
 *  the semaphore before returning.
 *
 *  @param[in]  flashAddr    The starting flash address for the program operation (must be 8-byte aligned)
 *  @param[in]  buffer       Pointer to the data buffer to be programmed
 *  @param[in]  sizeInBytes  The number of bytes to be programmed
 *
 *  @return     uint32_t indicating the operation status:
 *              - DL_FLASH_SUCCESS: Operation completed successfully
 *              - DL_FLASH_ADDR_INVALID: Address is not in Flash
 *              - DL_FLASH_ADDR_INVALID_ALIGN: Address is not 8-byte aligned
 *              - DL_FLASH_INVALID_BUFFER: Buffer pointer is NULL
 *              - DL_FLASH_INVALID_NUMBYTES: Invalid byte count (zero or exceeds bank boundary)
 *              - DL_FLASH_COMMAND_FAIL_PROGRAM: Program command failed
 *              - DL_FLASH_COMMAND_FAIL_READ_VERIFY: Read verify command failed
 *
 *  @note       This API should not be called for active flash banks
 *  @note       The address must be 8-byte aligned for ECC generation
 *  @note       Data less than 8 bytes will be padded with 0xFF to complete the 8-byte write
 *  @note       The function uses 128-bit writes when possible, then 64-bit writes for remaining data
 */
uint32_t DL_Flash_program(uint32_t flashAddr, uint8_t *buffer, uint32_t sizeInBytes);

#ifdef __cplusplus
}
#endif

#endif /* DL_FLASH_H */

/** @}*/
