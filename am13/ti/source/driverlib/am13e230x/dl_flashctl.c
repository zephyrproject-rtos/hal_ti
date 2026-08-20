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

#include "dl_flashctl.h"

static void DL_FlashCTL_programMemoryConfig(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd);

static DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_executeCommand(NVMNW_Regs *flashctl);
static void DL_FlashCTL_programMemory8Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint8_t *data);

static void DL_FlashCTL_programMemory16Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd,
                                              const uint16_t *data);

static void DL_FlashCTL_programMemory32Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd,
                                              const uint32_t *data);

static void DL_FlashCTL_programMemory64Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd,
                                              const uint32_t *data);

static void DL_FlashCTL_programMemory96Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd,
                                              const uint32_t *data);

static void DL_FlashCTL_programMemory128Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd,
                                               const uint32_t *data);

static void DL_FlashCTL_readVerifyConfig(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd);

static void DL_FlashCTL_readVerify8Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint8_t *data);

static void DL_FlashCTL_readVerify16Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint16_t *data);

static void DL_FlashCTL_readVerify32Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint32_t *data);

static void DL_FlashCTL_readVerify64Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint32_t *data);

static void DL_FlashCTL_readVerify96Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint32_t *data);

static void DL_FlashCTL_readVerify128Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint32_t *data);

RAMFUNC static DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_executeCommand(NVMNW_Regs *flashctl)
{
    volatile uint32_t status;

    // Ensure that all flash command config registers have been written to
    __DSB();
    __ISB();

    /* Set bit to execute command */
    flashctl->GEN.CMDEXEC = NVMNW_CMDEXEC_VAL_EXECUTE;

    // Ensure the execute bit was set before polling for command status
    __DSB();
    __ISB();

    /*
     * After executing a flash operation, we will enter a do-while and read the
     * STATCMD register using the status variable. Within the loop it will
     * poll until DL_FLASHCTL_COMMAND_STATUS_PASSED or DL_FLASHCTL_COMMAND_STATUS_FAILED
     * is read from the STATCMD register. This is to ensure that it will properly poll
     * even when the CPU is running at maximum speeds.
     */
    do
    {
        status = flashctl->GEN.STATCMD & (NVMNW_STATCMD_CMDDONE_MASK | NVMNW_STATCMD_CMDPASS_MASK |
                                          NVMNW_STATCMD_CMDINPROGRESS_MASK | NVMNW_STATCMD_CMDPASS_STATFAIL);
    } while ((DL_FLASHCTL_COMMAND_STATUS)status == DL_FLASHCTL_COMMAND_STATUS_IN_PROGRESS);

    return (DL_FLASHCTL_COMMAND_STATUS)(status);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_eraseMemory(NVMNW_Regs *flashctl, uint32_t address,
                                                   DL_FLASHCTL_COMMAND_SIZE memorySize)
{
    /* Set command type and size */
    flashctl->GEN.CMDTYPE = (uint32_t)memorySize | DL_FLASHCTL_COMMAND_TYPE_ERASE;

    /* Set address, address should be in the desired bank or sector to erase */
    DL_FlashCTL_setCommandAddress(flashctl, address);

    // Execute the command and wait for completion
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_massErase(NVMNW_Regs *flashctl)
{
    DL_FLASHCTL_COMMAND_STATUS status;

    DL_FlashCTL_protectAllMemory(flashctl);
    DL_FlashCTL_unprotectMainMemory(flashctl);

    status = DL_FlashCTL_eraseMemory(flashctl, NVMNW_BANK0_MAIN_ADDRESS, DL_FLASHCTL_COMMAND_SIZE_BANK);

    return (status);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_massEraseMultiBank(NVMNW_Regs *flashctl)
{
    DL_FLASHCTL_COMMAND_STATUS status;

    DL_FlashCTL_protectAllMemory(flashctl);
    DL_FlashCTL_unprotectMainMemory(flashctl);

    status = DL_FlashCTL_eraseMemory(flashctl, NVMNW_BANK0_MAIN_ADDRESS, DL_FLASHCTL_COMMAND_SIZE_BANK);

    if (status != DL_FLASHCTL_COMMAND_STATUS_FAILED)
    {
        DL_FlashCTL_protectAllMemory(flashctl);
        DL_FlashCTL_unprotectMainMemory(flashctl);
        status = DL_FlashCTL_eraseMemory(flashctl, NVMNW_BANK1_MAIN_ADDRESS, DL_FLASHCTL_COMMAND_SIZE_BANK);
    }

    return (status);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_factoryReset(NVMNW_Regs *flashctl)
{
    DL_FLASHCTL_COMMAND_STATUS status;

    /* Erase Main Memory */
    status = DL_FlashCTL_massErase(flashctl);

    /* Erase BANK0 NM3 Sector*/
    if (status == DL_FLASHCTL_COMMAND_STATUS_PASSED)
    {
        DL_FlashCTL_unprotectNonMainMemory(flashctl);
        status = DL_FlashCTL_eraseMemory(flashctl, NVMNW_BANK0_NONMAIN_ADDRESS + (1U * DL_FLASHCTL_SECTOR_SIZE),
                                         DL_FLASHCTL_COMMAND_SIZE_SECTOR);
    }

    return (status);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_factoryResetMultiBank(NVMNW_Regs *flashctl)
{
    DL_FLASHCTL_COMMAND_STATUS status;

    /* Erase Main Memory */
    status = DL_FlashCTL_massEraseMultiBank(flashctl);

    /* Erase specific NON-MAIN Sectors */
    if (status == DL_FLASHCTL_COMMAND_STATUS_PASSED)
    {
        /* Erase BANK0 NM3 Sector*/
        if (status != DL_FLASHCTL_COMMAND_STATUS_FAILED)
        {
            DL_FlashCTL_unprotectNonMainMemory(flashctl);
            status = DL_FlashCTL_eraseMemory(flashctl, NVMNW_BANK0_NONMAIN_ADDRESS + (1U * DL_FLASHCTL_SECTOR_SIZE),
                                             DL_FLASHCTL_COMMAND_SIZE_SECTOR);
        }

        /* Erase BANK1 NM3 Sector*/
        if (status != DL_FLASHCTL_COMMAND_STATUS_FAILED)
        {
            DL_FlashCTL_unprotectNonMainMemory(flashctl);
            status = DL_FlashCTL_eraseMemory(flashctl, NVMNW_BANK1_NONMAIN_ADDRESS + (1U * DL_FLASHCTL_SECTOR_SIZE),
                                             DL_FLASHCTL_COMMAND_SIZE_SECTOR);
        }
    }

    return (status);
}

static void DL_FlashCTL_programMemoryConfig(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd)
{
    flashctl->GEN.CMDTYPE = (uint32_t)DL_FLASHCTL_COMMAND_SIZE_ONE_WORD | DL_FLASHCTL_COMMAND_TYPE_PROGRAM;

    uint32_t cmd_data_en = cmd & 0x0000FFFF;
    uint32_t cmd_ecc_en  = cmd & 0xFFFF0000;

    cmd_data_en = cmd_data_en << (address % 0x10);

    // If programming to the second 64 bits in a flash word,
    // write the second ECC byte
    if ((address % 0x10) >= 0x8)
    {
        cmd_ecc_en = cmd_ecc_en << 1;
    }

    flashctl->GEN.CMDBYTEN = cmd_ecc_en | cmd_data_en;

    /* Set address, address should be in the sector that we want to erase */
    DL_FlashCTL_setCommandAddress(flashctl, address);
}

static void DL_FlashCTL_programMemory8Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint8_t *data)
{
    DL_FlashCTL_programMemoryConfig(flashctl, address, cmd);

    // Create a 32-bit word from our data
    uint32_t data_shifted = ((uint32_t)*data) << ((address % 4U) * 8U);

    // Set which flash word we are writing to
    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;

    // Select the CMDDATA register for our address within the flash word,
    // then load it with our data
    uint32_t cmddata_select = (address / 4U) % 4U;
    if (cmddata_select == 0x0U)
    {
        flashctl->GEN.CMDDATA0 = data_shifted;
    }
    else if (cmddata_select == 0x1U)
    {
        flashctl->GEN.CMDDATA1 = data_shifted;
    }
    else if (cmddata_select == 0x2U)
    {
        flashctl->GEN.CMDDATA2 = data_shifted;
    }
    else
    {
        flashctl->GEN.CMDDATA3 = data_shifted;
    }
}

static void DL_FlashCTL_programMemory16Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd,
                                              const uint16_t *data)
{
    DL_FlashCTL_programMemoryConfig(flashctl, address, cmd);

    // Create a 32-bit word from our data
    uint32_t data_shifted = ((uint32_t)*data) << ((address % 4U) * 8U);

    // Set which flash word we are writing to
    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;

    // Select the CMDDATA register for our address within the flash word,
    // then load it with our data
    uint32_t cmddata_select = (address / 4U) % 4U;
    if (cmddata_select == 0x0U)
    {
        flashctl->GEN.CMDDATA0 = data_shifted;
    }
    else if (cmddata_select == 0x1U)
    {
        flashctl->GEN.CMDDATA1 = data_shifted;
    }
    else if (cmddata_select == 0x2U)
    {
        flashctl->GEN.CMDDATA2 = data_shifted;
    }
    else
    {
        flashctl->GEN.CMDDATA3 = data_shifted;
    }
}

static void DL_FlashCTL_programMemory32Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd,
                                              const uint32_t *data)
{
    DL_FlashCTL_programMemoryConfig(flashctl, address, cmd);

    // Create a 32-bit word from our data
    uint32_t data_shifted = ((uint32_t)*data) << ((address % 4U) * 8U);

    // Set which flash word we are writing to
    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;

    // Select the CMDDATA register for our address within the flash word,
    // then load it with our data
    uint32_t cmddata_select = (address / 4U) % 4U;
    if (cmddata_select == 0x0U)
    {
        flashctl->GEN.CMDDATA0 = data_shifted;
    }
    else if (cmddata_select == 0x1U)
    {
        flashctl->GEN.CMDDATA1 = data_shifted;
    }
    else if (cmddata_select == 0x2U)
    {
        flashctl->GEN.CMDDATA2 = data_shifted;
    }
    else
    {
        flashctl->GEN.CMDDATA3 = data_shifted;
    }
}

static void DL_FlashCTL_programMemory64Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd,
                                              const uint32_t *data)
{
    DL_FlashCTL_programMemoryConfig(flashctl, address, cmd);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    if ((address % 0x10U) == 0x8U)
    {
        flashctl->GEN.CMDDATA2 = *data;
        flashctl->GEN.CMDDATA3 = *(data + 1U);
    }
    else
    {
        flashctl->GEN.CMDDATA0 = *data;
        flashctl->GEN.CMDDATA1 = *(data + 1U);
    }
}

static void DL_FlashCTL_programMemory96Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd,
                                              const uint32_t *data)
{
    DL_FlashCTL_programMemoryConfig(flashctl, address, cmd);

    /* Set data registers */
    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    flashctl->GEN.CMDDATA0     = *data;
    flashctl->GEN.CMDDATA1     = *(data + 1);
    flashctl->GEN.CMDDATA2     = *(data + 2);
}

static void DL_FlashCTL_programMemory128Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd,
                                               const uint32_t *data)
{
    DL_FlashCTL_programMemoryConfig(flashctl, address, cmd);

    /* Set data registers */
    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    flashctl->GEN.CMDDATA0     = *data;
    flashctl->GEN.CMDDATA1     = *(data + 1);
    flashctl->GEN.CMDDATA2     = *(data + 2);
    flashctl->GEN.CMDDATA3     = *(data + 3);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory8(NVMNW_Regs *flashctl, uint32_t address, const uint8_t *data)
{
    /* Only enable the bottom 8 bits for programming*/
    DL_FlashCTL_programMemory8Config(flashctl, address, DL_FLASHCTL_PROGRAM_8_WITHOUT_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory16(NVMNW_Regs *flashctl, uint32_t address, const uint16_t *data)
{
    /* Enable 16 bits per data register for programming*/
    DL_FlashCTL_programMemory16Config(flashctl, address, DL_FLASHCTL_PROGRAM_16_WITHOUT_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory32(NVMNW_Regs *flashctl, uint32_t address, const uint32_t *data)
{
    /* Enable 32 bits per data register for programming*/
    DL_FlashCTL_programMemory32Config(flashctl, address, DL_FLASHCTL_PROGRAM_32_WITHOUT_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory64(NVMNW_Regs *flashctl, uint32_t address, const uint32_t *data)
{
    /* Enable 64 bits per data register for programming*/
    DL_FlashCTL_programMemory64Config(flashctl, address, DL_FLASHCTL_PROGRAM_64_WITHOUT_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory96(NVMNW_Regs *flashctl, uint32_t address, const uint32_t *data)
{
    /* Enable 96 bits per data register for programming*/
    DL_FlashCTL_programMemory96Config(flashctl, address, DL_FLASHCTL_PROGRAM_96_WITHOUT_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory128(NVMNW_Regs *flashctl, uint32_t address, const uint32_t *data)
{
    /* Enable 128 bits per data register for programming*/
    DL_FlashCTL_programMemory128Config(flashctl, address, DL_FLASHCTL_PROGRAM_128_WITHOUT_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory8WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                      const uint8_t *data)
{
    /* Only enable the bottom 8 bits for programming*/
    DL_FlashCTL_programMemory8Config(flashctl, address, DL_FLASHCTL_PROGRAM_8_WITH_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory16WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                       const uint16_t *data)
{
    /* Enable 16 bits per data register for programming*/
    DL_FlashCTL_programMemory16Config(flashctl, address, DL_FLASHCTL_PROGRAM_16_WITH_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory32WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                       const uint32_t *data)
{
    /* Enable 32 bits per data register for programming*/
    DL_FlashCTL_programMemory32Config(flashctl, address, DL_FLASHCTL_PROGRAM_32_WITH_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory64WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                       const uint32_t *data)
{
    /* Enable 64 bits per data register for programming, with ECC enabled */
    DL_FlashCTL_programMemory64Config(flashctl, address, DL_FLASHCTL_PROGRAM_64_WITH_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory96WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                       const uint32_t *data)
{
    /* Enable 96 bits per data register for programming, with ECC enabled */
    DL_FlashCTL_programMemory96Config(flashctl, address, DL_FLASHCTL_PROGRAM_96_WITH_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory128WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                        const uint32_t *data)
{
    /* Enable 128 bits per data register for programming, with ECC enabled */
    DL_FlashCTL_programMemory128Config(flashctl, address, DL_FLASHCTL_PROGRAM_128_WITH_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory8WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                   const uint8_t *data, const uint8_t *eccCode)
{
    /* Enable 8 bits per data register for programming, with ECC enabled */
    DL_FlashCTL_programMemory8Config(flashctl, address, DL_FLASHCTL_PROGRAM_8_WITH_ECC, data);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    if ((address % 0x10U) >= 0x8U)
    {
        flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL1_MASK);
        flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL1_OFS;
    }
    else
    {
        flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL0_MASK);
        flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL0_OFS;
    }

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory16WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                    const uint16_t *data, const uint8_t *eccCode)
{
    /* Enable 16 bits per data register for programming, with ECC enabled */
    DL_FlashCTL_programMemory16Config(flashctl, address, DL_FLASHCTL_PROGRAM_16_WITH_ECC, data);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    if ((address % 0x10U) >= 0x8U)
    {
        flashctl->GEN.CMDDATAECC0 = (*eccCode) << NVMNW_CMDDATAECC0_VAL1_OFS;
    }
    else
    {
        flashctl->GEN.CMDDATAECC0 = *eccCode;
    }

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory32WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                    const uint32_t *data, const uint8_t *eccCode)
{
    /* Enable 32 bits per data register for programming, with ECC enabled */
    DL_FlashCTL_programMemory32Config(flashctl, address, DL_FLASHCTL_PROGRAM_32_WITH_ECC, data);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    if ((address % 0x10U) >= 0x8U)
    {
        flashctl->GEN.CMDDATAECC0 = (*eccCode) << NVMNW_CMDDATAECC0_VAL1_OFS;
    }
    else
    {
        flashctl->GEN.CMDDATAECC0 = *eccCode;
    }

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory64WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                    const uint32_t *data, const uint8_t *eccCode)
{
    /* Enable 64 bits per data register for programming, with ECC enabled */
    DL_FlashCTL_programMemory64Config(flashctl, address, DL_FLASHCTL_PROGRAM_64_WITH_ECC, data);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    if ((address % 0x10U) >= 0x8U)
    {
        flashctl->GEN.CMDDATAECC0 = (*eccCode) << NVMNW_CMDDATAECC0_VAL1_OFS;
    }
    else
    {
        flashctl->GEN.CMDDATAECC0 = *eccCode;
    }

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory96WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                    const uint32_t *data, const uint8_t *eccCode)
{
    /* Enable 96 bits per data register for programming, with ECC enabled */
    DL_FlashCTL_programMemory96Config(flashctl, address, DL_FLASHCTL_PROGRAM_96_WITH_ECC, data);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;

    // Set the first ECC byte
    flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL0_MASK);
    flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL0_OFS;

    // Set the second ECC byte
    flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL1_MASK);
    flashctl->GEN.CMDDATAECC0 |= (*(eccCode + 1)) << NVMNW_CMDDATAECC0_VAL1_OFS;

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemory128WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                     const uint32_t *data, const uint8_t *eccCode)
{
    /* Enable 128 bits per data register for programming, with ECC enabled */
    DL_FlashCTL_programMemory128Config(flashctl, address, DL_FLASHCTL_PROGRAM_128_WITH_ECC, data);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;

    // Set the first ECC byte
    flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL0_MASK);
    flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL0_OFS;

    // Set the second ECC byte
    flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL1_MASK);
    flashctl->GEN.CMDDATAECC0 |= (*(eccCode + 1)) << NVMNW_CMDDATAECC0_VAL1_OFS;

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemoryBlocking64WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                               uint32_t *data, uint32_t dataSize,
                                                                               DL_FLASHCTL_REGION_SELECT regionSelect)
{
    DL_FLASHCTL_COMMAND_STATUS status = DL_FLASHCTL_COMMAND_STATUS_IN_PROGRESS;
    uint32_t                   size   = dataSize;
    uint32_t                  *d      = data;
    uint32_t                   addr   = address;

    /* Check for valid data size */
    if ((size == (uint32_t)0) || ((size & (uint32_t)1) == (uint32_t)1))
    {
        status = DL_FLASHCTL_COMMAND_STATUS_FAILED;
    }

    while ((size != (uint32_t)0) && (status != DL_FLASHCTL_COMMAND_STATUS_FAILED))
    {
        /* Clear STATCMD register before executing a flash operation */
        DL_FlashCTL_executeClearStatus(flashctl);

        /* Unprotect sector before every write */
        DL_FlashCTL_unprotectSector(flashctl, addr, regionSelect);

        status = DL_FlashCTL_programMemory64WithECCGenerated(flashctl, addr, d);
        size   = size - (uint32_t)2;
        d      = d + 2;
        addr   = addr + (uint32_t)8;
    }

    return (status);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemoryBlocking64WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                            uint32_t *data, uint8_t *eccCode,
                                                                            uint32_t                  dataSize,
                                                                            DL_FLASHCTL_REGION_SELECT regionSelect)
{
    DL_FLASHCTL_COMMAND_STATUS status = DL_FLASHCTL_COMMAND_STATUS_IN_PROGRESS;
    uint32_t                   size   = dataSize;
    uint32_t                  *d      = data;
    uint32_t                   addr   = address;
    uint8_t                   *ecc    = eccCode;
    /* Check for valid data size */
    if ((size == (uint32_t)0) || ((size & (uint32_t)1) == (uint32_t)1))
    {
        status = DL_FLASHCTL_COMMAND_STATUS_FAILED;
    }

    while ((size != (uint32_t)0) && (status != DL_FLASHCTL_COMMAND_STATUS_FAILED))
    {
        /* Clear STATCMD register before executing a flash operation */
        DL_FlashCTL_executeClearStatus(flashctl);

        /* Unprotect sector before every write */
        DL_FlashCTL_unprotectSector(flashctl, addr, regionSelect);

        status = DL_FlashCTL_programMemory64WithECCManual(flashctl, addr, d, ecc);
        size   = size - (uint32_t)2;
        d      = d + 2;
        ecc    = ecc + 1;
        addr   = addr + (uint32_t)8;
    }

    return (status);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemoryBlocking128WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                                uint32_t *data, uint32_t dataSize,
                                                                                DL_FLASHCTL_REGION_SELECT regionSelect)
{
    DL_FLASHCTL_COMMAND_STATUS status = DL_FLASHCTL_COMMAND_STATUS_IN_PROGRESS;
    uint32_t                   size   = dataSize;
    uint32_t                  *d      = data;
    uint32_t                   addr   = address;

    /* Check for valid data size */
    if ((size == (uint32_t)0) || ((size % (uint32_t)0x4) != (uint32_t)0))
    {
        status = DL_FLASHCTL_COMMAND_STATUS_FAILED;
    }

    while ((size != (uint32_t)0) && (status != DL_FLASHCTL_COMMAND_STATUS_FAILED))
    {
        /* Clear STATCMD register before executing a flash operation */
        DL_FlashCTL_executeClearStatus(flashctl);

        /* Unprotect sector before every write */
        DL_FlashCTL_unprotectSector(flashctl, addr, regionSelect);

        status = DL_FlashCTL_programMemory128WithECCGenerated(flashctl, addr, d);
        size   = size - (uint32_t)4;
        d      = d + 4;
        addr   = addr + (uint32_t)16;
    }

    return (status);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemoryBlocking128WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                             uint32_t *data, uint8_t *eccCode,
                                                                             uint32_t                  dataSize,
                                                                             DL_FLASHCTL_REGION_SELECT regionSelect)
{
    DL_FLASHCTL_COMMAND_STATUS status = DL_FLASHCTL_COMMAND_STATUS_IN_PROGRESS;
    uint32_t                   size   = dataSize;
    uint32_t                  *d      = data;
    uint32_t                   addr   = address;
    uint8_t                   *ecc    = eccCode;

    /* Check for valid data size */
    if ((size == (uint32_t)0) || ((size % (uint32_t)0x4) != (uint32_t)0))
    {
        status = DL_FLASHCTL_COMMAND_STATUS_FAILED;
    }

    while ((size != (uint32_t)0) && (status != DL_FLASHCTL_COMMAND_STATUS_FAILED))
    {
        /* Clear STATCMD register before executing a flash operation */
        DL_FlashCTL_executeClearStatus(flashctl);

        /* Unprotect sector before every write */
        DL_FlashCTL_unprotectSector(flashctl, addr, regionSelect);

        status = DL_FlashCTL_programMemory128WithECCManual(flashctl, addr, d, ecc);
        size   = size - (uint32_t)4;
        d      = d + 4;
        ecc    = ecc + 2;
        addr   = addr + (uint32_t)16;
    }

    return (status);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_programMemoryBlocking(NVMNW_Regs *flashctl, uint32_t address, uint32_t *data,
                                                             uint32_t dataSize, DL_FLASHCTL_REGION_SELECT regionSelect)
{
    DL_FLASHCTL_COMMAND_STATUS status = DL_FLASHCTL_COMMAND_STATUS_IN_PROGRESS;
    uint32_t                   size   = dataSize;
    uint32_t                  *d      = data;
    uint32_t                   addr   = address;

    /* Check for valid data size */
    if (size == (uint32_t)0)
    {
        status = DL_FLASHCTL_COMMAND_STATUS_FAILED;
    }

    while ((size != (uint32_t)0) && (status != DL_FLASHCTL_COMMAND_STATUS_FAILED))
    {
        /* Clear STATCMD register before executing a flash operation */
        DL_FlashCTL_executeClearStatus(flashctl);

        /* Unprotect sector before every write */
        DL_FlashCTL_unprotectSector(flashctl, addr, regionSelect);

        /* 32-bit case */
        if (size == (uint32_t)1)
        {
            status = DL_FlashCTL_programMemory32(flashctl, addr, d);

            size = size - (uint32_t)1;
            d    = d + 1;
            addr = addr + (uint32_t)8;
        }
        else if (size == (uint32_t)2)
        {
            /* 64-bit case */
            status = DL_FlashCTL_programMemory64(flashctl, addr, d);

            size = size - (uint32_t)2;
            d    = d + 2;
            addr = addr + (uint32_t)8;
        }
        else if (size == (uint32_t)3)
        {
            /* 96-bit case */
            status = DL_FlashCTL_programMemory96(flashctl, addr, d);

            size = size - (uint32_t)3;
            d    = d + 3;
            addr = addr + (uint32_t)16;
        }
        else
        {
            /* 128-bit case */
            status = DL_FlashCTL_programMemory128(flashctl, addr, d);
            size   = size - (uint32_t)4;
            d      = d + 4;
            addr   = addr + (uint32_t)16;
        }
    }

    return (status);
}

void DL_FlashCTL_unprotectMainMemory(NVMNW_Regs *flashctl)
{
    flashctl->GEN.CMDWEPROTA = 0;
    flashctl->GEN.CMDWEPROTB = 0;
}

void DL_FlashCTL_protectMainMemory(NVMNW_Regs *flashctl)
{
    flashctl->GEN.CMDWEPROTA = NVMNW_CMDWEPROTA_VAL_MAXIMUM;
    flashctl->GEN.CMDWEPROTB = NVMNW_CMDWEPROTB_VAL_MAXIMUM;
}

void DL_FlashCTL_unprotectNonMainMemory(NVMNW_Regs *flashctl)
{
    flashctl->GEN.CMDWEPROTNM = 0;
}

void DL_FlashCTL_protectNonMainMemory(NVMNW_Regs *flashctl)
{
    flashctl->GEN.CMDWEPROTNM = NVMNW_CMDWEPROTNM_VAL_MAXIMUM;
}

void DL_FlashCTL_unprotectAllMemory(NVMNW_Regs *flashctl)
{
    flashctl->GEN.CMDWEPROTA  = 0;
    flashctl->GEN.CMDWEPROTB  = 0;
    flashctl->GEN.CMDWEPROTNM = 0;
}

void DL_FlashCTL_protectAllMemory(NVMNW_Regs *flashctl)
{
    flashctl->GEN.CMDWEPROTA  = NVMNW_CMDWEPROTA_VAL_MAXIMUM;
    flashctl->GEN.CMDWEPROTB  = NVMNW_CMDWEPROTB_VAL_MAXIMUM;
    flashctl->GEN.CMDWEPROTNM = NVMNW_CMDWEPROTNM_VAL_MAXIMUM;
}

void DL_FlashCTL_unprotectSector(NVMNW_Regs *flashctl, uint32_t addr, DL_FLASHCTL_REGION_SELECT regionSelect)
{
    uint32_t sectorNumber = DL_FlashCTL_getFlashSectorNumber(flashctl, addr);
    uint32_t sectorInBank = DL_FlashCTL_getFlashSectorNumberInBank(flashctl, addr);
    uint32_t sectorMask;

    if ((uint32_t)regionSelect == NVMNW_CMDCTL_REGIONSEL_MAIN)
    {
        if (sectorInBank < (uint32_t)32)
        {
            /* Use CMDWEPROTA */
            sectorMask                = (uint32_t)1 << sectorInBank;
            flashctl->GEN.CMDWEPROTA &= ~sectorMask;
        }
        else
        {
            /* Use CMDWEPROTB */
            sectorMask                = (uint32_t)1 << ((sectorInBank / (uint32_t)8) - (uint32_t)4);
            flashctl->GEN.CMDWEPROTB &= ~sectorMask;
        }
    }
    else if ((uint32_t)regionSelect == NVMNW_CMDCTL_REGIONSEL_NONMAIN)
    {
        sectorMask                 = (uint32_t)1 << (sectorNumber % (uint32_t)4);
        flashctl->GEN.CMDWEPROTNM &= ~sectorMask;
    }
    else
    {
        // not expected to come here.
    }
}

void DL_FlashCTL_protectSector(NVMNW_Regs *flashctl, uint32_t addr, DL_FLASHCTL_REGION_SELECT regionSelect)
{
    uint32_t sectorNumber = DL_FlashCTL_getFlashSectorNumber(flashctl, addr);
    uint32_t sectorInBank = DL_FlashCTL_getFlashSectorNumberInBank(flashctl, addr);
    uint32_t sectorMask;

    if ((uint32_t)regionSelect == NVMNW_CMDCTL_REGIONSEL_MAIN)
    {
        if (sectorInBank < (uint32_t)32)
        {
            /* Use CMDWEPROTA */
            sectorMask                = (uint32_t)1 << sectorInBank;
            flashctl->GEN.CMDWEPROTA |= sectorMask;
        }
        else
        {
            /* Use CMDWEPROTB */
            sectorMask                = (uint32_t)1 << ((sectorInBank / (uint32_t)8) - (uint32_t)4);
            flashctl->GEN.CMDWEPROTB |= sectorMask;
        }
    }
    else if ((uint32_t)regionSelect == NVMNW_CMDCTL_REGIONSEL_NONMAIN)
    {
        sectorMask                 = (uint32_t)1 << (sectorNumber % (uint32_t)4);
        flashctl->GEN.CMDWEPROTNM |= sectorMask;
    }
    else
    {
        // not expected to come here.
    }
}

static void DL_FlashCTL_readVerifyConfig(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd)
{
    flashctl->GEN.CMDTYPE = (uint32_t)DL_FLASHCTL_COMMAND_SIZE_ONE_WORD | DL_FLASHCTL_COMMAND_TYPE_READ_VERIFY;

    uint32_t cmd_data_en = cmd & 0x0000FFFF;
    uint32_t cmd_ecc_en  = cmd & 0xFFFF0000;

    cmd_data_en = cmd_data_en << (address % 0x10);

    // If programming to the second 64 bits in a flash word,
    // write the second ECC byte
    if ((address % 0x10) >= 0x8)
    {
        cmd_ecc_en = cmd_ecc_en << 1;
    }

    flashctl->GEN.CMDBYTEN = cmd_ecc_en | cmd_data_en;

    /* Set address, address should be in the sector that we want to erase */
    DL_FlashCTL_setCommandAddress(flashctl, address);
}

static void DL_FlashCTL_readVerify8Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint8_t *data)
{
    DL_FlashCTL_readVerifyConfig(flashctl, address, cmd);

    // Create a 32-bit word from our data
    uint32_t data_shifted = ((uint32_t)*data) << ((address % 4U) * 8U);

    // Set which flash word we are writing to
    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;

    // Select the CMDDATA register for our address within the flash word,
    // then load it with our data
    uint32_t cmddata_select = (address / 4U) % 4U;
    if (cmddata_select == 0x0U)
    {
        flashctl->GEN.CMDDATA0 = data_shifted;
    }
    else if (cmddata_select == 0x1U)
    {
        flashctl->GEN.CMDDATA1 = data_shifted;
    }
    else if (cmddata_select == 0x2U)
    {
        flashctl->GEN.CMDDATA2 = data_shifted;
    }
    else
    {
        flashctl->GEN.CMDDATA3 = data_shifted;
    }
}

static void DL_FlashCTL_readVerify16Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint16_t *data)
{
    DL_FlashCTL_readVerifyConfig(flashctl, address, cmd);

    // Create a 32-bit word from our data
    uint32_t data_shifted = ((uint32_t)*data) << ((address % 4U) * 8U);

    // Set which flash word we are writing to
    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;

    // Select the CMDDATA register for our address within the flash word,
    // then load it with our data
    uint32_t cmddata_select = (address / 4U) % 4U;
    if (cmddata_select == 0x0U)
    {
        flashctl->GEN.CMDDATA0 = data_shifted;
    }
    else if (cmddata_select == 0x1U)
    {
        flashctl->GEN.CMDDATA1 = data_shifted;
    }
    else if (cmddata_select == 0x2U)
    {
        flashctl->GEN.CMDDATA2 = data_shifted;
    }
    else
    {
        flashctl->GEN.CMDDATA3 = data_shifted;
    }
}

static void DL_FlashCTL_readVerify32Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint32_t *data)
{
    DL_FlashCTL_readVerifyConfig(flashctl, address, cmd);

    // Create a 32-bit word from our data
    uint32_t data_shifted = ((uint32_t)*data) << ((address % 4U) * 8U);

    // Set which flash word we are writing to
    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;

    // Select the CMDDATA register for our address within the flash word,
    // then load it with our data
    uint32_t cmddata_select = (address / 4U) % 4U;
    if (cmddata_select == 0x0U)
    {
        flashctl->GEN.CMDDATA0 = data_shifted;
    }
    else if (cmddata_select == 0x1U)
    {
        flashctl->GEN.CMDDATA1 = data_shifted;
    }
    else if (cmddata_select == 0x2U)
    {
        flashctl->GEN.CMDDATA2 = data_shifted;
    }
    else
    {
        flashctl->GEN.CMDDATA3 = data_shifted;
    }
}

static void DL_FlashCTL_readVerify64Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint32_t *data)
{
    DL_FlashCTL_readVerifyConfig(flashctl, address, cmd);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    if ((address % 0x10U) == 0x8U)
    {
        flashctl->GEN.CMDDATA2 = *data;
        flashctl->GEN.CMDDATA3 = *(data + 1U);
    }
    else
    {
        flashctl->GEN.CMDDATA0 = *data;
        flashctl->GEN.CMDDATA1 = *(data + 1U);
    }
}

static void DL_FlashCTL_readVerify96Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint32_t *data)
{
    DL_FlashCTL_readVerifyConfig(flashctl, address, cmd);

    /* Set data registers */
    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    flashctl->GEN.CMDDATA0     = *data;
    flashctl->GEN.CMDDATA1     = *(data + 1);
    flashctl->GEN.CMDDATA2     = *(data + 2);
}

static void DL_FlashCTL_readVerify128Config(NVMNW_Regs *flashctl, uint32_t address, uint32_t cmd, const uint32_t *data)
{
    DL_FlashCTL_readVerifyConfig(flashctl, address, cmd);

    /* Set data registers */
    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    flashctl->GEN.CMDDATA0     = *data;
    flashctl->GEN.CMDDATA1     = *(data + 1);
    flashctl->GEN.CMDDATA2     = *(data + 2);
    flashctl->GEN.CMDDATA3     = *(data + 3);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify8(NVMNW_Regs *flashctl, uint32_t address, const uint8_t *data)
{
    DL_FlashCTL_readVerify8Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_8_WITHOUT_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify16(NVMNW_Regs *flashctl, uint32_t address, const uint16_t *data)
{
    DL_FlashCTL_readVerify16Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_16_WITHOUT_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify32(NVMNW_Regs *flashctl, uint32_t address, const uint32_t *data)
{
    DL_FlashCTL_readVerify32Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_32_WITHOUT_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify64(NVMNW_Regs *flashctl, uint32_t address, const uint32_t *data)
{
    DL_FlashCTL_readVerify64Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_64_WITHOUT_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify96(NVMNW_Regs *flashctl, uint32_t address, const uint32_t *data)
{
    DL_FlashCTL_readVerify96Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_96_WITHOUT_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify128(NVMNW_Regs *flashctl, uint32_t address, const uint32_t *data)
{
    DL_FlashCTL_readVerify128Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_128_WITHOUT_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify8WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                   const uint8_t *data)
{
    DL_FlashCTL_readVerify8Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_8_WITH_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify16WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                    const uint16_t *data)
{
    DL_FlashCTL_readVerify16Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_16_WITH_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify32WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                    const uint32_t *data)
{
    DL_FlashCTL_readVerify32Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_32_WITH_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify64WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                    const uint32_t *data)
{
    DL_FlashCTL_readVerify64Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_64_WITH_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify96WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                    const uint32_t *data)
{
    DL_FlashCTL_readVerify96Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_96_WITH_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify128WithECCGenerated(NVMNW_Regs *flashctl, uint32_t address,
                                                                     const uint32_t *data)
{
    DL_FlashCTL_readVerify128Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_128_WITH_ECC, data);

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify8WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                const uint8_t *data, const uint8_t *eccCode)
{
    DL_FlashCTL_readVerify8Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_8_WITH_ECC, data);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    if ((address % 0x10U) >= 0x8U)
    {
        flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL1_MASK);
        flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL1_OFS;
    }
    else
    {
        flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL0_MASK);
        flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL0_OFS;
    }

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify16WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                 const uint16_t *data, const uint8_t *eccCode)
{
    DL_FlashCTL_readVerify16Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_16_WITH_ECC, data);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    if ((address % 0x10U) >= 0x8U)
    {
        flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL1_MASK);
        flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL1_OFS;
    }
    else
    {
        flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL0_MASK);
        flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL0_OFS;
    }

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify32WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                 const uint32_t *data, const uint8_t *eccCode)
{
    DL_FlashCTL_readVerify32Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_32_WITH_ECC, data);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    if ((address % 0x10U) >= 0x8U)
    {
        flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL1_MASK);
        flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL1_OFS;
    }
    else
    {
        flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL0_MASK);
        flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL0_OFS;
    }

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify64WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                 const uint32_t *data, const uint8_t *eccCode)
{
    DL_FlashCTL_readVerify64Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_64_WITH_ECC, data);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;
    if ((address % 0x10U) >= 0x8U)
    {
        flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL1_MASK);
        flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL1_OFS;
    }
    else
    {
        flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL0_MASK);
        flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL0_OFS;
    }

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify96WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                 const uint32_t *data, const uint8_t *eccCode)
{
    DL_FlashCTL_readVerify96Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_96_WITH_ECC, data);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;

    // Set the first ECC byte
    flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL0_MASK);
    flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL0_OFS;

    // Set the second ECC byte
    flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL1_MASK);
    flashctl->GEN.CMDDATAECC0 |= (*(eccCode + 1)) << NVMNW_CMDDATAECC0_VAL1_OFS;

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_readVerify128WithECCManual(NVMNW_Regs *flashctl, uint32_t address,
                                                                  const uint32_t *data, const uint8_t *eccCode)
{
    DL_FlashCTL_readVerify128Config(flashctl, address, DL_FLASHCTL_READ_VERIFY_128_WITH_ECC, data);

    flashctl->GEN.CMDDATAINDEX = (address >> 4U) & 3U;

    // Set the first ECC byte
    flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL0_MASK);
    flashctl->GEN.CMDDATAECC0 |= (*eccCode) << NVMNW_CMDDATAECC0_VAL0_OFS;

    // Set the second ECC byte
    flashctl->GEN.CMDDATAECC0 &= ~((uint32_t)NVMNW_CMDDATAECC0_VAL1_MASK);
    flashctl->GEN.CMDDATAECC0 |= (*(eccCode + 1)) << NVMNW_CMDDATAECC0_VAL1_OFS;

    /* Execute command and wait for completion */
    return DL_FlashCTL_executeCommand(flashctl);
}

DL_FLASHCTL_COMMAND_STATUS DL_FlashCTL_blankVerify(NVMNW_Regs *flashctl, uint32_t address,
                                                   DL_FLASHCTL_REGION_SELECT region)
{
    // Blank verify 128 main array bits and 16 ECC bits.
    // Flash words are always 128-bit aligned.
    uint32_t u32AlignedAddress = address & 0xFFFFFFF0;

    DL_FLASHCTL_COMMAND_STATUS result = DL_FLASHCTL_COMMAND_STATUS_FAILED;

    // Blank verify 128 main/nonmain array bits.
    uint32_t u32CurrAddress = u32AlignedAddress;
    uint32_t u32EndAddress  = u32AlignedAddress + 0x10U;

    while (u32CurrAddress < u32EndAddress)
    {
        // If main/nonmain array flash not blank, return a failure
        if (HWREG(u32CurrAddress) != 0xFFFFFFFFU)
        {
            return result;
        }

        // Increment to next 32-bit segment
        u32CurrAddress += 0x4U;
    }

    // Blank verify 16 ECC bits
    uint32_t u32ECCAddress = 0x0U;

    if (region == DL_FLASHCTL_REGION_SELECT_MAIN)
    {  // Main array ECC
        u32ECCAddress = NVMNW_MAIN_ECC_ADDRESS + ((u32AlignedAddress - NVMNW_BANK0_MAIN_ADDRESS) / 16U);
    }
    else
    {  // Nonmain array ECC
        u32ECCAddress = NVMNW_NONMAIN_ECC_ADDRESS + ((u32AlignedAddress - NVMNW_BANK0_NONMAIN_ADDRESS) / 16U);
    }

    // If the ECC region is not blank, then return a failure
    if (HWREGH(u32ECCAddress) != 0xFFFFU)
    {
        return result;
    }

    result = DL_FLASHCTL_COMMAND_STATUS_PASSED;

    return result;
}

uint8_t DL_FlashCTL_calculateECC(uint32_t u32Address, uint64_t u64Data)
{
    const uint32_t addrSyndrome[8] = {0x554eaU, 0x0bad1U, 0x2a9b5U, 0x6a78dU, 0x19f83U, 0x07f80U, 0x7ff80U, 0x0007fU};
    const uint64_t dataSyndrome[8] = {0xb4d1b4d14b2e4b2eU, 0x1557155715571557U, 0xa699a699a699a699U,
                                      0x38e338e338e338e3U, 0xc0fcc0fcc0fcc0fcU, 0xff00ff00ff00ff00U,
                                      0xff0000ffff0000ffU, 0x00ffff00ff0000ffU};

    const uint16_t parity  = 0xfc;
    uint64_t       xorData = 0;
    uint32_t       xorAddr = 0;
    uint16_t       bit = 0, eccBit = 0, eccVal = 0;
    uint32_t       u32CurrentAddress = u32Address;

    //
    // Extract bits "20:2" of the address
    //
    u32CurrentAddress = (u32CurrentAddress & 0x3fff8U) >> 3U;

    //
    // Compute the ECC one bit at a time.
    //
    eccVal = 0;
    for (bit = 0; bit < 8U; bit++)
    {
        //
        // Apply the encoding masks to the address and data
        //
        xorAddr  = u32CurrentAddress & addrSyndrome[bit];
        xorData  = u64Data & dataSyndrome[bit];
        //
        // Fold the masked address into a single bit for parity calculation.
        // The result will be in the LSB.
        //
        xorAddr  = xorAddr ^ (xorAddr >> 16);
        xorAddr  = xorAddr ^ (xorAddr >> 8);
        xorAddr  = xorAddr ^ (xorAddr >> 4);
        xorAddr  = xorAddr ^ (xorAddr >> 2);
        xorAddr  = xorAddr ^ (xorAddr >> 1);
        //
        // Fold the masked data into a single bit for parity calculation.
        // The result will be in the LSB.
        //
        xorData  = xorData ^ (xorData >> 32);
        xorData  = xorData ^ (xorData >> 16);
        xorData  = xorData ^ (xorData >> 8);
        xorData  = xorData ^ (xorData >> 4);
        xorData  = xorData ^ (xorData >> 2);
        xorData  = xorData ^ (xorData >> 1);
        //
        // Merge the address and data, extract the ECC bit, and add it in
        //
        eccBit   = ((uint16_t)xorData ^ (uint16_t)xorAddr) & 0x0001U;
        eccVal  |= eccBit << bit;
    }
    //
    // Handle the bit parity. For odd parity, XOR the bit with 1
    //
    eccVal ^= parity;

    return eccVal;
}
