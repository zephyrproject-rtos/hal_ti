/******************************************************************************
 *  Filename:       ospi.c
 *
 *  Description:    Driver for the peripheral OSPI controller
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

#include "ospi.h"

// should be 100% margin from the real time the polling takes
#define OSPI_IDLE_XSPI_COUNTER_BEFORE_TIMEOUT 100

//*****************************************************************************
//
// Functions
//
//*****************************************************************************

//*****************************************************************************
//
// Get Read Data or Status Register
//
//*****************************************************************************
uint32_t __attribute__((noinline, section(".TI.ramfunc"))) OSPIGetSTIGDataRegister(uint32_t regSelect)
{
    return HWREG(OSPI_REGS_BASE + regSelect);
}

//*****************************************************************************
//
// Set Write Data or Status Register
//
//*****************************************************************************
void OSPISetSTIGDataRegister(uint32_t regSelect, uint32_t regData)
{
    HWREG(OSPI_REGS_BASE + regSelect) = regData;
}

//*****************************************************************************
//
// Set STIG command
//
//*****************************************************************************
void __attribute__((noinline, section(".TI.ramfunc"))) OSPIExecuteSTIGWriteCommand(OSPISTIGConfig_t OspiStigCommand)
{
    uint32_t configReg = 0;

    uint8_t opCode = OspiStigCommand.stigOpcode;
    configReg |= (opCode << OSPI_FLASH_CMD_CTRL_CMD_OPCODE_S) & OSPI_FLASH_CMD_CTRL_CMD_OPCODE_M;

    uint8_t addrEN = OspiStigCommand.stigAddrEn;
    if (addrEN == 1)
    {
        configReg |= (addrEN << OSPI_FLASH_CMD_CTRL_ENB_COMD_ADDR_S) & OSPI_FLASH_CMD_CTRL_ENB_COMD_ADDR_M;

        uint8_t addrNumBytes = OspiStigCommand.stigAddrNumBytes;
        configReg |= (addrNumBytes << OSPI_FLASH_CMD_CTRL_NUM_ADDR_BYTES_S) & OSPI_FLASH_CMD_CTRL_NUM_ADDR_BYTES_M;
    }

    uint8_t modeBitEN = OspiStigCommand.stigModeBitEN;
    if (modeBitEN == 1)
    {
        configReg |= (modeBitEN << OSPI_FLASH_CMD_CTRL_ENB_MODE_BIT_S) & OSPI_FLASH_CMD_CTRL_ENB_MODE_BIT_M;
    }

    uint8_t readEN = OspiStigCommand.stigRdEn;
    if (readEN == 1)
    {
        configReg |= (readEN << OSPI_FLASH_CMD_CTRL_ENB_READ_DATA_S) & OSPI_FLASH_CMD_CTRL_ENB_READ_DATA_M;

        uint8_t readNumBytes = OspiStigCommand.stigRDNumBytes;
        configReg |= (readNumBytes << OSPI_FLASH_CMD_CTRL_NUM_RD_DATA_BYTES_S) &
                     OSPI_FLASH_CMD_CTRL_NUM_RD_DATA_BYTES_M;
    }

    uint8_t writeEN = OspiStigCommand.stigWrEn;
    if (writeEN == 1)
    {
        configReg |= (writeEN << OSPI_FLASH_CMD_CTRL_ENB_WRITE_DATA_S) & OSPI_FLASH_CMD_CTRL_ENB_WRITE_DATA_M;

        uint8_t writeNumBytes = OspiStigCommand.stigWrNumBytes;
        configReg |= (writeNumBytes << OSPI_FLASH_CMD_CTRL_NUM_WR_DATA_BYTES_S) &
                     OSPI_FLASH_CMD_CTRL_NUM_WR_DATA_BYTES_M;
    }

    uint8_t dummyCycles = OspiStigCommand.stigNumDummyCycles;
    configReg |= (dummyCycles << OSPI_FLASH_CMD_CTRL_NUM_DUMMY_CYCLES_S) & OSPI_FLASH_CMD_CTRL_NUM_DUMMY_CYCLES_M;

    OSPIStartSTIGCommand(configReg);
}

//*****************************************************************************
//
// Execute STIG Command
//
//*****************************************************************************
void __attribute__((noinline, section(".TI.ramfunc"))) OSPIStartSTIGCommand(uint32_t configReg)
{

    uint32_t idleXSPICounterBefore = 0;
    uint32_t idleSTIGCounterBefore = 0;
    uint32_t idleXSPICounterAfter  = 0;
    uint32_t idleSTIGCounterAfter  = 0;

    uint32_t regValue = 0;

    while ((HWREG(OSPI_REGS_BASE + OSPI_O_CONFIG) & OSPI_CONFIG_IDLE_M) == OSPI_CONFIG_IDLE_DISABLE &&
            (idleXSPICounterBefore < OSPI_IDLE_XSPI_COUNTER_BEFORE_TIMEOUT))
    {
        idleXSPICounterBefore++;
    }

    // STIG accessible check before STIG execution
    while ((HWREG(OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL) & OSPI_FLASH_CMD_CTRL_CMD_EXEC_STATUS_M) ==
            OSPI_FLASH_CMD_CTRL_CMD_EXEC_STATUS_ENABLE &&
            (idleSTIGCounterBefore < OSPI_IDLE_XSPI_COUNTER_BEFORE_TIMEOUT))
    {
        idleSTIGCounterBefore++;
    }

    // Execute command
    HWREG(OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL) = (configReg | OSPI_FLASH_CMD_CTRL_CMD_EXEC);

    // Wait for xSPI to complete the STIG execution.
    while ((HWREG(OSPI_REGS_BASE + OSPI_O_CONFIG) & OSPI_CONFIG_IDLE_M) == OSPI_CONFIG_IDLE_DISABLE &&
            (idleXSPICounterAfter < OSPI_IDLE_XSPI_COUNTER_BEFORE_TIMEOUT))
    {
        idleXSPICounterAfter++;
    }

    // STIG accessible check after STIG execution AND stig fix flag
    do
    {
        regValue = HWREG(OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL);
        idleSTIGCounterAfter++;
    } while ((((regValue & OSPI_FLASH_CMD_CTRL_CMD_EXEC_STATUS_M) == OSPI_FLASH_CMD_CTRL_CMD_EXEC_STATUS_ENABLE) ||
              ((regValue & OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_M) != 0)) &&
             (idleSTIGCounterAfter < OSPI_IDLE_XSPI_COUNTER_BEFORE_TIMEOUT));
}

//*****************************************************************************
//
// Set address for command execution by STIG
//
//*****************************************************************************
void __attribute__((noinline, section(".TI.ramfunc"))) OSPISetCommandAddress(uint32_t address)
{
    // This register should be setup while the controller is idle.
    HWREG(OSPI_REGS_BASE + OSPI_O_FLASH_CMD_ADDR) = address;
}
