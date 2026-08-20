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

#include <stddef.h>
#include "dl_flashctl.h"
#include "dl_flash.h"

static uint32_t DL_Flash_getRegion(uint32_t addr);

uint32_t DL_Flash_eraseBank(uint32_t flashAddr)
{
    DL_FLASHCTL_COMMAND_STATUS cmdStatus  = DL_FLASHCTL_COMMAND_STATUS_FAILED;
    uint32_t                   failStatus = DL_FLASH_SUCCESS;
    uint32_t                   relStatus  = DL_FLASH_SUCCESS;
    uint32_t                   region     = DL_Flash_getRegion(flashAddr);

    /* Validate region */
    if (region == DL_FLASH_ADDR_INVALID)
    {
        failStatus = DL_FLASH_ADDR_INVALID;
    }
    else if (region == DL_FLASH_ADDR_NONMAIN)
    {
        failStatus = DL_FLASH_ADDR_NONMAIN;
    }

    /* Validate flash address is valid */
    if (failStatus == DL_FLASH_SUCCESS)
    {
        if ((flashAddr % DL_FLASH_BANK_SIZE) != 0U)
        {
            failStatus = DL_FLASH_ADDR_INVALID_BANK;
        }
    }

    /* Acquire flash semaphore before performing erase */
    if (failStatus == DL_FLASH_SUCCESS)
    {
        failStatus = DL_FlashCTL_acquireFlashSemaphore();
    }

    if (failStatus == DL_FLASH_SUCCESS)
    {
        /* Clear status */
        DL_FlashCTL_executeClearStatus(NVMNW);

        /* Unprotect the memory for erase operation */
        DL_FlashCTL_protectAllMemory(NVMNW);
        DL_FlashCTL_unprotectMainMemory(NVMNW);

        /* Issue bank erase command */
        cmdStatus = DL_FlashCTL_eraseMemory(NVMNW, flashAddr, DL_FLASHCTL_COMMAND_SIZE_BANK);

        if (cmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED)
        {
            failStatus = DL_FLASH_COMMAND_FAIL_ERASE;
        }
        else
        {
            /* Perform blank verify on the entire bank in 128-bit (16-byte) chunks */
            uint32_t currentAddr = flashAddr;
            uint32_t endAddr     = flashAddr + DL_FLASH_BANK_SIZE;

            while ((currentAddr < endAddr) && (failStatus == DL_FLASH_SUCCESS))
            {
                cmdStatus = DL_FlashCTL_blankVerify(NVMNW, currentAddr, (DL_FLASHCTL_REGION_SELECT)region);
                if (cmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED)
                {
                    failStatus = DL_FLASH_COMMAND_FAIL_BLANK_VERIFY;
                    break;
                }
                /* Move to next 128-bit (16-byte) flash word */
                currentAddr += 0x10U;
            }
        }

        relStatus = DL_FlashCTL_releaseFlashSemaphore();
        if ((failStatus == DL_FLASH_SUCCESS) && (relStatus != DL_FLASH_SUCCESS))
        {
            failStatus = relStatus;
        }
    }

    return failStatus;
}

uint32_t DL_Flash_eraseSector(uint32_t flashAddr)
{
    DL_FLASHCTL_COMMAND_STATUS cmdStatus  = DL_FLASHCTL_COMMAND_STATUS_FAILED;
    uint32_t                   failStatus = DL_FLASH_SUCCESS;
    uint32_t                   relStatus  = DL_FLASH_SUCCESS;
    uint32_t                   region     = DL_Flash_getRegion(flashAddr);

    /* Validate region */
    if (region == DL_FLASH_ADDR_INVALID)
    {
        failStatus = DL_FLASH_ADDR_INVALID;
    }
    else if (region == DL_FLASH_ADDR_NONMAIN)
    {
        failStatus = DL_FLASH_ADDR_NONMAIN;
    }

    /* Validate flash address for sector erase */
    if (failStatus == DL_FLASH_SUCCESS)
    {
        if ((flashAddr % DL_FLASH_SECTOR_SIZE) != 0U)
        {
            failStatus = DL_FLASH_ADDR_INVALID_SECTOR;
        }
    }

    /* Acquire flash semaphore before performing erase */
    if (failStatus == DL_FLASH_SUCCESS)
    {
        failStatus = DL_FlashCTL_acquireFlashSemaphore();
    }

    if (failStatus == DL_FLASH_SUCCESS)
    {
        /* Clear status */
        DL_FlashCTL_executeClearStatus(NVMNW);

        /* Disable protection masks */
        DL_FlashCTL_unprotectSector(NVMNW, flashAddr, (DL_FLASHCTL_REGION_SELECT)region);

        /* Issue sector erase command */
        cmdStatus = DL_FlashCTL_eraseMemory(NVMNW, flashAddr, DL_FLASHCTL_COMMAND_SIZE_SECTOR);

        if (cmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED)
        {
            failStatus = DL_FLASH_COMMAND_FAIL_ERASE;
        }
        else
        {
            /* Perform blank verify on the entire sector in 128-bit (16-byte) chunks */
            uint32_t currentAddr = flashAddr;
            uint32_t endAddr     = flashAddr + DL_FLASH_SECTOR_SIZE;

            while ((currentAddr < endAddr) && (failStatus == DL_FLASH_SUCCESS))
            {
                cmdStatus = DL_FlashCTL_blankVerify(NVMNW, currentAddr, (DL_FLASHCTL_REGION_SELECT)region);
                if (cmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED)
                {
                    failStatus = DL_FLASH_COMMAND_FAIL_BLANK_VERIFY;
                    break;
                }
                /* Move to next 128-bit (16-byte) flash word */
                currentAddr += 0x10U;
            }
        }

        relStatus = DL_FlashCTL_releaseFlashSemaphore();
        if ((failStatus == DL_FLASH_SUCCESS) && (relStatus != DL_FLASH_SUCCESS))
        {
            failStatus = relStatus;
        }
    }

    return failStatus;
}

uint32_t DL_Flash_program(uint32_t flashAddr, uint8_t *buffer, uint32_t sizeInBytes)
{
    uint32_t bytesRemaining = sizeInBytes;
    uint32_t byteOffset     = 0U;
    uint32_t paddedBuffer[2]; /* 8 bytes (2 words) for 64-bit write */

    DL_FLASHCTL_COMMAND_STATUS cmdStatus  = DL_FLASHCTL_COMMAND_STATUS_FAILED;
    uint32_t                   failStatus = DL_FLASH_SUCCESS;
    uint32_t                   relStatus  = DL_FLASH_SUCCESS;
    uint32_t                   region;

    /* Validate flash address (64-bit alignment for ECC generation) */
    if (failStatus == DL_FLASH_SUCCESS)
    {
        if ((flashAddr % 8U) != 0U)
        {
            failStatus = DL_FLASH_ADDR_INVALID_ALIGN;
        }
    }

    /* Validate input buffer */
    if (failStatus == DL_FLASH_SUCCESS)
    {
        if (buffer == NULL)
        {
            failStatus = DL_FLASH_INVALID_BUFFER;
        }
    }

    /* Validate number of bytes to program */
    if (failStatus == DL_FLASH_SUCCESS)
    {
        if ((sizeInBytes == 0U) || (flashAddr + sizeInBytes > NVMNW_BANK1_MAIN_ADDRESS + DL_FLASH_BANK_SIZE))
        {
            failStatus = DL_FLASH_INVALID_NUMBYTES;
        }
    }

    region = DL_Flash_getRegion(flashAddr);

    /* Validate region */
    if (region == DL_FLASH_ADDR_INVALID)
    {
        failStatus = DL_FLASH_ADDR_INVALID;
    }
    else if (region == DL_FLASH_ADDR_NONMAIN)
    {
        failStatus = DL_FLASH_ADDR_NONMAIN;
    }

    /* Acquire flash semaphore before performing program */
    if (failStatus == DL_FLASH_SUCCESS)
    {
        failStatus = DL_FlashCTL_acquireFlashSemaphore();
    }

    if (failStatus == DL_FLASH_SUCCESS)
    {
        /* Program 128-bit chunks (16 bytes at a time) while possible */
        while (bytesRemaining >= 16U)
        {
            /* Clear status */
            DL_FlashCTL_executeClearStatus(NVMNW);

            /* Disable protection masks */
            DL_FlashCTL_unprotectSector(NVMNW, flashAddr, (DL_FLASHCTL_REGION_SELECT)region);

            /* Program 16 bytes using 128-bit API */
            cmdStatus =
                DL_FlashCTL_programMemory128WithECCGenerated(NVMNW, flashAddr, (const uint32_t *)&buffer[byteOffset]);

            if (cmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED)
            {
                failStatus = DL_FLASH_COMMAND_FAIL_PROGRAM;
            }
            if (failStatus == DL_FLASH_SUCCESS)
            {
                /* Verify the programmed values */
                cmdStatus =
                    DL_FlashCTL_readVerify128WithECCGenerated(NVMNW, flashAddr, (const uint32_t *)&buffer[byteOffset]);

                if (cmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED)
                {
                    failStatus = DL_FLASH_COMMAND_FAIL_READ_VERIFY;
                    break;
                }
            }

            flashAddr      += 16U;
            byteOffset     += 16U;
            bytesRemaining -= 16U;

            if (failStatus != DL_FLASH_SUCCESS)
            {
                break;
            }
        }

        /* Handle remaining bytes (< 16 bytes) using 64-bit API */
        if (failStatus == DL_FLASH_SUCCESS)
        {
            if (bytesRemaining >= 8U)
            {
                /* Clear status */
                DL_FlashCTL_executeClearStatus(NVMNW);

                /* Disable protection masks */
                DL_FlashCTL_unprotectSector(NVMNW, flashAddr, (DL_FLASHCTL_REGION_SELECT)region);

                /* Program 8 bytes using 64-bit API */
                cmdStatus = DL_FlashCTL_programMemory64WithECCGenerated(NVMNW, flashAddr,
                                                                        (const uint32_t *)&buffer[byteOffset]);

                if (cmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED)
                {
                    failStatus = DL_FLASH_COMMAND_FAIL_PROGRAM;
                }

                if (failStatus == DL_FLASH_SUCCESS)
                {
                    /* Verify the programmed values */
                    cmdStatus = DL_FlashCTL_readVerify64WithECCGenerated(NVMNW, flashAddr,
                                                                         (const uint32_t *)&buffer[byteOffset]);

                    if (cmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED)
                    {
                        failStatus = DL_FLASH_COMMAND_FAIL_READ_VERIFY;
                    }
                }

                flashAddr      += 8U;
                byteOffset     += 8U;
                bytesRemaining -= 8U;
            }
        }

        /* Handle remaining bytes (< 8 bytes) with padding */
        if (failStatus == DL_FLASH_SUCCESS)
        {
            if (bytesRemaining > 0U)
            {
                uint32_t j;
                uint8_t *dstBytes = (uint8_t *)paddedBuffer;

                /* Initialize padded buffer with 0xFF at byte level */
                for (j = 0U; j < 8U; j++)
                {
                    dstBytes[j] = 0xFFU;
                }

                /* Copy remaining bytes from source buffer */
                for (j = 0U; j < bytesRemaining; j++)
                {
                    dstBytes[j] = buffer[byteOffset + j];
                }

                /* Clear status */
                DL_FlashCTL_executeClearStatus(NVMNW);

                /* Disable protection masks */
                DL_FlashCTL_unprotectSector(NVMNW, flashAddr, (DL_FLASHCTL_REGION_SELECT)region);

                /* Program padded data using 64-bit API */
                cmdStatus = DL_FlashCTL_programMemory64WithECCGenerated(NVMNW, flashAddr, paddedBuffer);

                if (cmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED)
                {
                    failStatus = DL_FLASH_COMMAND_FAIL_PROGRAM;
                }

                if (failStatus == DL_FLASH_SUCCESS)
                {
                    /* Verify the programmed values */
                    cmdStatus = DL_FlashCTL_readVerify64WithECCGenerated(NVMNW, flashAddr, paddedBuffer);

                    if (cmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED)
                    {
                        failStatus = DL_FLASH_COMMAND_FAIL_READ_VERIFY;
                    }
                }
            }
        }

        relStatus = DL_FlashCTL_releaseFlashSemaphore();
        if ((failStatus == DL_FLASH_SUCCESS) && (relStatus != DL_FLASH_SUCCESS))
        {
            failStatus = relStatus;
        }
    }

    return failStatus;
}

static uint32_t DL_Flash_getRegion(uint32_t addr)
{
    uint32_t retVal;

    if ((addr < (NVMNW_BANK1_MAIN_ADDRESS + DL_FLASH_BANK_SIZE)))
    {
        retVal = (uint32_t)DL_FLASHCTL_REGION_SELECT_MAIN;
    }
    else if ((addr >= NVMNW_BANK0_NONMAIN_ADDRESS) &&
             (addr < (NVMNW_BANK1_NONMAIN_ADDRESS + DL_FLASH_NONMAIN_BANK_SIZE)))
    {
        retVal = DL_FLASH_ADDR_NONMAIN;
    }
    else
    {
        retVal = DL_FLASH_ADDR_INVALID;
    }

    return retVal;
}
