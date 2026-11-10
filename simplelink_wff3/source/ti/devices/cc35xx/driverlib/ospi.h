/******************************************************************************
 *  Filename:       ospi.h
 *
 *  Description:    Defines and prototypes for the OSPI peripheral.
 *
 *  Copyright (c) 2024-2026 Texas Instruments Incorporated
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

#ifndef ti_devices_ospi__include
#define ti_devices_ospi__include

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup ospi_api
//! @{
//
//*****************************************************************************

#include "../inc/hw_memmap.h"
#include "../inc/hw_ospi.h"
#include "../inc/hw_types.h"

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
// Configuration values that can be passed to \ref OSPIGetSTIGDataRegister() as the regSelect parameter
//
//*****************************************************************************
//! Flash Read Data Register (Lower)
#define OSPI_STIG_READ_DATA_LOWER OSPI_O_FLASH_RD_DATA_LOWER
//! Flash Read Data Register (Upper)
#define OSPI_STIG_READ_DATA_UPPER OSPI_O_FLASH_RD_DATA_UPPER

//*****************************************************************************
//
// Configuration values that can be passed to OSPIExecuteSTIGWriteCommand() as the OSPISTIGConfig_t parameter
//
//*****************************************************************************
//! Memory Bank should only be enabled when triggering Flash Rd/Wr commands with Memory Bank transfer.
#define OSPI_STIG_MEMORY_BANK_TRANSFER_ENABLE  OSPI_FLASH_CMD_CTRL_STIG_MEM_BANK_EN_ENABLE
//! Memory Bank should be disabled before triggering any operation that not use Memory Bank transfer.
#define OSPI_STIG_MEMORY_BANK_TRANSFER_DISABLE OSPI_FLASH_CMD_CTRL_STIG_MEM_BANK_EN_DISABLE

//! Enable write data transfer if flash command requires write data bytes to be sent to the device.
#define OSPI_STIG_WRITE_DATA_ENABLE  OSPI_FLASH_CMD_CTRL_ENB_WRITE_DATA_ENABLE
//! Disable write data transfer if flash command do not requires write data to the device.
#define OSPI_STIG_WRITE_DATA_DISABLE OSPI_FLASH_CMD_CTRL_ENB_MODE_BIT_DISABLE

//! Enable Mode bit if required by the flash command and Ensure the mode bits as defined
//! in the Mode Bit Configuration Register (OSPI_O_MODE_BIT_CONFIG[7:0]) are sent
//! following the address bytes.
#define OSPI_STIG_MODE_BIT_ENABLE  OSPI_FLASH_CMD_CTRL_ENB_MODE_BIT_ENABLE
//! Disable Mode bit if not required by the flash command.
#define OSPI_STIG_MODE_BIT_DISABLE OSPI_FLASH_CMD_CTRL_ENB_MODE_BIT_DISABLE

//! Enable Address if flash command requires an address.
#define OSPI_STIG_COMMAND_ADDRESS_ENABLE  OSPI_FLASH_CMD_CTRL_ENB_COMD_ADDR_ENABLE
//! Disable Address if flash command not requires an address. (e.g WEN command 0x6)
#define OSPI_STIG_COMMAND_ADDRESS_DISABLE OSPI_FLASH_CMD_CTRL_ENB_COMD_ADDR_DISABLE

//! Enable read data if flash command expect response data bytes received from the device.
#define OSPI_STIG_READ_DATA_ENABLE  OSPI_FLASH_CMD_CTRL_ENB_READ_DATA_ENABLE
//! Disable read data if flash command not expected data bytes received from the device.
#define OSPI_STIG_READ_DATA_DISABLE OSPI_FLASH_CMD_CTRL_ENB_READ_DATA_DISABLE

//*****************************************************************************
//
// Enumerations
//
//*****************************************************************************

//! OSPI flash status register bit indication
typedef enum
{
    OSPI_FLASH_STA_REG_WIP  = 0x01, //!< Write in progress bit
    OSPI_FLASH_STA_REG_WEL  = 0x02, //!< Write enable latch
    OSPI_FLASH_STA_REG_BP0  = 0x04, //!< Level of protected block
    OSPI_FLASH_STA_REG_BP1  = 0x08, //!< Level of protected block
    OSPI_FLASH_STA_REG_BP2  = 0x10, //!< Level of protected block
    OSPI_FLASH_STA_REG_BP3  = 0x20, //!< level of protected block
    OSPI_FLASH_STA_REG_QE   = 0x40, //!< Quad SPI mode Enable
    OSPI_FLASH_STA_REG_SRWD = 0x80  //!< Status register write protect
} OSPIFlashStatusRegister;

//! Sub group of used JEDEC commands
typedef enum
{
    OSPI_COMMAND_WRSR      = 0x01, //!< Write status/configuration register
    OSPI_COMMAND_WRITE     = 0x02, //!< Normal write
    OSPI_COMMAND_READ      = 0x03, //!< Normal read
    OSPI_COMMAND_FAST_READ = 0x0B, //!< Fast read
    OSPI_COMMAND_RDSR      = 0x05, //!< Read status register
    OSPI_COMMAND_WREN      = 0x06, //!< Write enable
    OSPI_COMMAND_SE        = 0x20, //!< Sector erase
    OSPI_COMMAND_CE        = 0x60, //!< Chip erase (60h or C7h)
    OSPI_COMMAND_QEN       = 0x35, //!< Quad SPI en (35h or 38h)
    OSPI_COMMAND_QDIS      = 0xF5, //!< Quad disable (0xf5 or ffh)
    OSPI_COMMAND_RSTEN     = 0x66, //!< Reset Enable
    OSPI_COMMAND_RST       = 0x99  //!< Reset Memory
} OSPISTIGCommand;

typedef enum
{
    OSPI_INSTR_TYPE_SPI          = 0, //!< Standard SPI mode (instruction always shifted into the device on DQ0 only)
    OSPI_INSTR_TYPE_DUAL_SPI     = 1, //!< DIO-SPI mode (Instruction sent on DQ0 and DQ1)
    OSPI_INSTR_TYPE_QUAD_IO_SPI  = 2, //!< QIO-SPI mode (Instruction sent on DQ0,DQ1,DQ2 and DQ3)
    OSPI_INSTR_TYPE_OCTAL_IO_SPI = 3  //!< OIO-SPI mode (Instruction sent on DQ[7:0]
} OSPIInstructionType;

typedef struct
{
    uint8_t stigOpcode;
    uint8_t stigRdEn;
    uint8_t stigRDNumBytes;
    uint8_t stigAddrEn;
    uint8_t stigAddrNumBytes;
    uint8_t stigModeBitEN;
    uint8_t stigWrEn;
    uint8_t stigWrNumBytes;
    uint8_t stigNumDummyCycles;
    uint8_t stigMemoryEn;
} OSPISTIGConfig_t;

//*****************************************************************************
//
//! \brief Returns the read data or status register value.
//!
//! This function called when using STIG for read data from specific address
//! or read status register.
//! This function called following the calls of \ref OSPISetSTIGDataRegister()
//! (together with \ref OSPISetCommandAddress()) and/or
//! - \ref OSPIExecuteSTIGWriteCommand().
//!
//! \param regSelect is the selected register for the return data.
//! The parameter can have one of these three values:
//! - \ref OSPI_STIG_READ_DATA_LOWER
//! - \ref OSPI_STIG_READ_DATA_UPPER
//!
//! \return Returns the value of the status register or required address.
//!
//! \note this function must be placed in RAM by the linker (ref. TI.ramfunc),
//! as execution for flash must be disabled in order to take control on OSPI IP.
//!
//
//*****************************************************************************
uint32_t OSPIGetSTIGDataRegister(uint32_t regSelect);

//*****************************************************************************
//
//! \brief Configure and execute the STIG command.
//!
//! This function configures the relevant parameters for the STIG command.
//!
//! \param OspiStigCommand is the selected STIG command struct.
//! - \ref OSPISTIGConfig_t struct is a combination of parameters to obtain STIG command.
//!
//! \note this function must be placed in RAM by the linker (ref. TI.ramfunc),
//! as execution for flash must be disabled in order to take control on OSPI IP.
//!
//
//*****************************************************************************
void OSPIExecuteSTIGWriteCommand(OSPISTIGConfig_t OspiStigCommand);

//*****************************************************************************
//
//! \brief Execute the STIG command.
//!
//! This function include protection check of the STIG and the xSPI
//! before and after the STIG command kick.
//!
//! \param configReg is the value of the configurations process from
//! \ref OSPIExecuteSTIGWriteCommand().
//!
//! \note this function must be placed in RAM by the linker (ref. TI.ramfunc),
//! as execution for flash must be disabled in order to take control on OSPI IP.
//!
//
//*****************************************************************************
void OSPIStartSTIGCommand(uint32_t configReg);

//*****************************************************************************
//
//! \brief Set the address for the STIG write/read command.
//!
//! \param address is the 32 bit address to be write/read.
//!
//! \note this function must be placed in RAM by the linker (ref. TI.ramfunc),
//! as execution for flash must be disabled in order to take control on OSPI IP.
//!
//
//*****************************************************************************
void OSPISetCommandAddress(uint32_t address);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
//! Close the Doxygen group.
//! @}
//! @}
//
//*****************************************************************************

#endif // ti_devices_ospi__include
