/******************************************************************************
 *  Filename:       xip.h
 *
 *  Description:    Defines and prototypes for the XIP peripheral.
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

#ifndef ti_devices_xip__include
#define ti_devices_xip__include

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup xip_api
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include "ospi.h"
#include "../inc/hw_types.h"
#include "../inc/hw_host_xip.h"

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

//! Address bit secure mask - identify secure/non-secure address based on bit 26 (External memory)
#define XIP_UDMA_BIT_SECURE_MASK 0x04000000

// UDMA peripheral processing status enumerations for use with #XIPGetUDMAChannelProgressingStatus().
#define XIP_UDMA_CHANNEL_STATUS_IDLE     0 //!< Channel is in IDLE state, there is no active job.
#define XIP_UDMA_CHANNEL_STATUS_PROGRESS 1 //!< Channel is in PROGRESS state, there is an active job.

// UDMA data movement direction
#define XIP_UDMA_DIRECTION_EXT_TO_INT 0 //!< UDMA Data movement from External memory to Internal memory.
#define XIP_UDMA_DIRECTION_INT_TO_EXT 1 //!< UDMA Data movement from Internal memory to External memory.

// UDMA job status
#define XIP_UDMA_JOB_STARTED   0    //!< UDMA job started
#define XIP_UDMA_JOB_NOT_START (-1) //!< UDMA job not started

//*****************************************************************************
//
// UDMA interrupt status values returned by XIPGetUDMAIrqStatus()
//
//*****************************************************************************
#define XIP_UDMA_JOB_IRQ_STATUS_DONE      0 //!< Transaction done
#define XIP_UDMA_JOB_IRQ_STATUS_BUS_ERROR 1 //!< Error, but able to recover (only in write)
#define XIP_UDMA_JOB_IRQ_STATUS_SEC_ERROR 2 //!< Error, unable to recover

#define XIP_UDMA_NON_SECURE_CHANNEL 0
#define XIP_UDMA_SECURE_CHANNEL     1

//*****************************************************************************
//
// Functions
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Configure the relevant channel and start a uDMA transaction.
//!
//! \param srcAddr is a pointer to the source data.
//! \param dstAddr is a pointer to the destination data.
//! \note if direction is \ref XIP_UDMA_DIRECTION_EXT_TO_INT
//!                        srcAddr: pointer to External memory
//!                        dstAddr: pointer to Internal memory
//!       if direction is \ref XIP_UDMA_DIRECTION_INT_TO_EXT
//!                        srcAddr: pointer to Internal memory
//!                        dstAddr: pointer to External memory
//!
//! \note For non-secured channel, external memory address must comply with bit 26
//!       to enable Secure/Non-Secure accesses, otherwise transactions will be blocked.
//!       In case using SAU to define secured memory region 'inside' the non-secured,
//!       non-secure channel will allow this.
//!
//! \param length is the number of words to transfer and should not be larger than \ref XIP_UDMA_MAX_JOB_SIZE.
//! \param directionMode specify the copy direction.
//! - Data movement from External memory to Internal memory
//!   - \ref XIP_UDMA_DIRECTION_EXT_TO_INT
//! - Data movement from Internal memory to External memory
//!   - \ref XIP_UDMA_DIRECTION_INT_TO_EXT
//! \param channelSelect specify which channel to use secure or non-secure (in current implementation only use SECURE
//! channel!)
//! - \ref XIP_UDMA_SECURE_CHANNEL
//! - \ref XIP_UDMA_NON_SECURE_CHANNEL
//!
//! \return Returns indication if job started or if job did not started because of an ongoing job.
//! - \ref XIP_UDMA_JOB_STARTED
//! - \ref XIP_UDMA_JOB_NOT_START
//!
//! \note Follow the transfer limitations: ONLY USE \ref XIP_UDMA_SECURE_CHANNEL
//
//*****************************************************************************
uint32_t XIPStartUDMATransaction(const uint32_t *srcAddr,
                                 uint32_t *dstAddr,
                                 uint32_t length,
                                 uint8_t directionMode,
                                 uint32_t channelSelect);

//*****************************************************************************
//
//! \brief Return the channel progressing status.
//!
//! \param channelSelect selects either secure or non-secure channel.
//! - \ref XIP_UDMA_SECURE_CHANNEL     : Return the secure channel progressing status.
//! - \ref XIP_UDMA_NON_SECURE_CHANNEL : Return the non-secure channel progressing status.
//!
//! \note This function does not return the transaction status, only the channel status.
//! \return Returns the channel progressing status, one of the following:
//! - \ref XIP_UDMA_CHANNEL_STATUS_IDLE
//! - \ref XIP_UDMA_CHANNEL_STATUS_PROGRESS
//!
//! @sa XIPGetUDMAIrqStatus()
//
//*****************************************************************************
uint32_t XIPGetUDMAChannelProgressingStatus(uint32_t channelSelect);

//*****************************************************************************
//
//! \brief Return the channel remaining words left to transmit.
//!
//! \param channelSelect selects either secure or non-secure channel.
//! - \ref XIP_UDMA_SECURE_CHANNEL     : Return the secure channel progressing status.
//! - \ref XIP_UDMA_NON_SECURE_CHANNEL : Return the non-secure channel progressing status.
//!
//! \note This function return the channel words left to transmit.
//
//*****************************************************************************
uint32_t XIPGetUDMAChannelWordsLeft(uint32_t channelSelect);

//*****************************************************************************
//
//! \brief Return the transactions status.
//!
//! This function can be called when interrupt raised or when channel is Idle.
//!
//! \param channelSelect selects either the secure or non-secure channel.
//! - \ref XIP_UDMA_SECURE_CHANNEL     : Return the secure channel transaction status.
//! - \ref XIP_UDMA_NON_SECURE_CHANNEL : Return the non-secure channel transaction status.
//!
//! \return Returns the current interrupt status, one of the following:
//! - \ref XIP_UDMA_JOB_IRQ_STATUS_DONE
//! - \ref XIP_UDMA_JOB_IRQ_STATUS_BUS_ERROR
//! - \ref XIP_UDMA_JOB_IRQ_STATUS_BUS_ERROR
//! - \ref XIP_UDMA_JOB_IRQ_STATUS_SEC_ERROR
//
//*****************************************************************************
uint32_t XIPGetUDMAIrqStatus(uint32_t channelSelect);

//*****************************************************************************
//
//! \brief Disable the OTFDE processing.
//!
//! \note It is the user's responsibility to check that there are no active/pending
//!       tasks before calling this function.
//!
//! \note this function must be placed in RAM by the linker (ref. TI.ramfunc),
//! as calling to this function will disable any access to flash, preventing execution for flash.
//!
//
//*****************************************************************************
void XIPDisableOTFDE(void);

//*****************************************************************************
//
//! \brief Enable the OTFDE processing.
//!
//! \note this function must be placed in RAM by the linker (ref. TI.ramfunc),
//! as only this function enables the access to the flash.
//!
//
//*****************************************************************************
void XIPEnableOTFDE(void);

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

#endif // ti_devices_xip__include
