/******************************************************************************
 *  Copyright (c) 2022-2024 Texas Instruments Incorporated
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

#ifndef __FLASH_H__
#define __FLASH_H__

//*****************************************************************************
//
//! \addtogroup system_control_group
//! @{
//! \addtogroup flash_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "../inc/hw_types.h"
#include "../inc/hw_flash.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_ints.h"
#include "../inc/hw_vims.h"
#include "hapi.h"
#include "chipinfo.h"
#include "interrupt.h"
#include "debug.h"

//*****************************************************************************
// Values that can be returned from the API functions
//*****************************************************************************
#define FAPI_STATUS_SUCCESS                     0x00000000 ///< Function completed successfully
#define FAPI_STATUS_FSM_BUSY                    0x00000001 ///< FSM is Busy
#define FAPI_STATUS_FSM_READY                   0x00000002 ///< FSM is Ready
#define FAPI_STATUS_INCORRECT_DATABUFFER_LENGTH 0x00000003 ///< Incorrect parameter value
#define FAPI_STATUS_FSM_ERROR                   0x00000004 ///< Flash program/erase operation failed
#define FAPI_STATUS_ADDRESS_ERROR               0x00000005 ///< Address range or alignment error
#define FAPI_STATUS_INVALID_KEY                 0x00000010 ///< Invalid random jump protection key

//*****************************************************************************
//
//! \brief Get size of a flash sector in number of bytes.
//!
//! This function will return the size of a flash sector in number of bytes.
//!
//! \return Returns size of a flash sector in number of bytes.
//
//*****************************************************************************
__STATIC_INLINE uint32_t FlashGetSectorSize(void)
{
    return (FLASH_MAIN_SECTOR_SIZE);
}

//*****************************************************************************
//
//! \brief Get the size of the flash.
//!
//! This function returns the size of the flash main bank in number of bytes.
//!
//! \return Returns the flash size in number of bytes.
//
//*****************************************************************************
__STATIC_INLINE uint32_t FlashGetSize(void)
{
    // Return flash size in number of bytes
    return (FLASH_MAIN_SIZE);
}

//*****************************************************************************
//
//! \brief Checks if the Flash state machine has detected an error.
//!
//! This function returns the status of the Flash State Machine indicating if
//! an error is detected or not. Primary use is to check if an Erase or
//! Program operation has failed.
//!
//! \note Please note that code can not execute in flash while any part of the flash
//! is being programmed or erased. This function must be called from ROM or
//! SRAM while any part of the flash is being programmed or erased.
//!
//! \return Returns status of Flash state machine:
//! - \ref FAPI_STATUS_FSM_ERROR
//! - \ref FAPI_STATUS_SUCCESS
//
//*****************************************************************************
__STATIC_INLINE uint32_t FlashCheckFsmForError(void)
{
    if (HWREG(FLASH_BASE + FLASH_O_STATCMD) & FLASH_STATCMD_CMDPASS_M)
    {
        return (FAPI_STATUS_SUCCESS);
    }
    else
    {
        return (FAPI_STATUS_FSM_ERROR);
    }
}

//*****************************************************************************
//
//! \brief Checks if the Flash state machine is ready.
//!
//! This function returns the status of the Flash State Machine indicating if
//! it is ready to accept a new command or not. Primary use is to check if an
//! Erase or Program operation has finished.
//!
//! \note Please note that code can not execute in flash while any part of the flash
//! is being programmed or erased. This function must be called from ROM or
//! SRAMh while any part of the flash is being programmed or erased.
//!
//! \return Returns readiness status of Flash state machine:
//! - \ref FAPI_STATUS_FSM_READY
//! - \ref FAPI_STATUS_FSM_BUSY
//
//*****************************************************************************
__STATIC_INLINE uint32_t FlashCheckFsmForReady(void)
{
    if (HWREG(FLASH_BASE + FLASH_O_STATCMD) & FLASH_STATCMD_CMDDONE_M)
    {
        return (FAPI_STATUS_FSM_READY);
    }
    else
    {
        return (FAPI_STATUS_FSM_BUSY);
    }
}

//*****************************************************************************
//
//! \brief Erase a flash sector.
//!
//! This function will erase the specified flash sector. The function will
//! not return until the flash sector has been erased or an error condition
//! occurred. If flash top sector is erased the function will program the
//! the device security data bytes with default values. The device security
//! data located in the customer configuration area of the flash top sector,
//! must have valid values at all times. These values affect the configuration
//! of the device during boot.
//!
//! \warning Please note that code can not execute in flash while any part of the flash
//! is being programmed or erased. The application must disable interrupts that have
//! interrupt routines in flash. This function calls a ROM function which handles the
//! actual program operation.
//!
//! \param sectorAddress is the starting address in flash of the sector to be
//! erased.
//!
//! \return Returns the status of the sector erase:
//! - \ref FAPI_STATUS_SUCCESS                     : Success.
//! - \ref FAPI_STATUS_INCORRECT_DATABUFFER_LENGTH : Invalid argument.
//! - \ref FAPI_STATUS_FSM_ERROR                   : A programming error is encountered.
//
//*****************************************************************************
__STATIC_INLINE uint32_t FlashEraseSector(uint32_t sectorAddress)
{
    // Store current configuration
    uint32_t cchctrl                  = HWREG(VIMS_BASE + VIMS_O_CCHCTRL);
    // Clear instruction cache
    HWREG(VIMS_BASE + VIMS_O_CCHCTRL) = (VIMS_CCHCTRL_CCHMPEN_DIS | VIMS_CCHCTRL_CCHPFEN_DIS | VIMS_CCHCTRL_CCHEN_DIS);

    uint32_t retCode = HapiFlashSectorErase(FLASH_API_KEY, sectorAddress);

    // Restore configuration
    HWREG(VIMS_BASE + VIMS_O_CCHCTRL) = cchctrl;

    return (retCode);
}

/*****************************************************************************
 * \brief Erase all unprotected sectors in the flash main bank
 *
 * This function will erase all unprotected main bank flash sectors. It will
 * not return until the flash sectors has been erased or an error condition
 * occurs.
 *
 * \warning Please note that code can not execute in flash while any part of
 * the flash is being programmed or erased. The application must disable
 * interrupts that have interrupt routines in flash.
 *
 * \return Returns the status of the sector erase:
 * - \ref FAPI_STATUS_SUCCESS (0): Success
 * - \ref FAPI_STATUS_FSM_ERROR  : An erase error is encountered.
 *****************************************************************************/
__STATIC_INLINE uint32_t FlashEraseBank(void)
{
    // Store current configuration
    uint32_t cchctrl = HWREG(VIMS_BASE + VIMS_O_CCHCTRL);

    // Clear instruction cache
    HWREG(VIMS_BASE + VIMS_O_CCHCTRL) = (VIMS_CCHCTRL_CCHMPEN_DIS | VIMS_CCHCTRL_CCHPFEN_DIS | VIMS_CCHCTRL_CCHEN_DIS);

    uint32_t retCode = HapiFlashBankErase(FLASH_API_KEY);

    // Restore configuration
    HWREG(VIMS_BASE + VIMS_O_CCHCTRL) = cchctrl;

    return (retCode);
}

//*****************************************************************************
//
//! \brief Programs unprotected flash sectors in the main bank.
//!
//! This function programs a sequence of bytes into the on-chip flash.
//! Programming each location consists of the result of an AND operation
//! of the new data and the existing data; in other words bits that contain
//! 1 can remain 1 or be changed to 0, but bits that are 0 cannot be changed
//! to 1. Therefore, a byte can be programmed multiple times as long as these
//! rules are followed; if a program operation attempts to change a 0 bit to
//! a 1 bit, that bit will not have its value changed.
//!
//! This function does not return until the data has been programmed or a
//! programming error occurs.
//!
//!
//! \warning Please note that code can not execute in flash while any part of the flash
//! is being programmed or erased. The application must disable interrupts that have
//! interrupt routines in flash. This function calls a ROM function which handles the
//! actual program operation.
//!
//! The \c dataBuffer pointer can not point to flash.
//!
//! \param dataBuffer is a pointer to the data to be programmed.
//! \param address is the starting address in flash to be programmed.
//! \param count is the number of bytes to be programmed.
//!
//! \return Returns status of the flash programming:
//! - \ref FAPI_STATUS_SUCCESS                     : Success.
//! - \ref FAPI_STATUS_INCORRECT_DATABUFFER_LENGTH : Too many bytes were requested.
//! - \ref FAPI_STATUS_FSM_ERROR                   : A programming error is encountered.
//
//*****************************************************************************
__STATIC_INLINE uint32_t FlashProgram(uint8_t *dataBuffer, uint32_t address, uint32_t count)
{
    // Store current configuration
    uint32_t cchctrl = HWREG(VIMS_BASE + VIMS_O_CCHCTRL);

    // Clear instruction cache
    HWREG(VIMS_BASE + VIMS_O_CCHCTRL) = (VIMS_CCHCTRL_CCHMPEN_DIS | VIMS_CCHCTRL_CCHPFEN_DIS | VIMS_CCHCTRL_CCHEN_DIS);

    uint32_t retCode = HapiFlashProgram(FLASH_API_KEY, dataBuffer, address, count);

    // Restore configuration
    HWREG(VIMS_BASE + VIMS_O_CCHCTRL) = cchctrl;

    return (retCode);
}

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

#endif // __FLASH_H__
