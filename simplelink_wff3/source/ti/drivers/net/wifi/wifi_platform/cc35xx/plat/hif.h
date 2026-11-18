/*****************************************************************************
 *  Filename:       hif.h
 *
 *  Description:    Defines and prototypes for the HIF peripheral.
 *
 *  Copyright (c) 2023 Texas Instruments Incorporated
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

#ifndef __HIF_H__
#define __HIF_H__

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup hif_api
//! @{
//
//*****************************************************************************
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "ti/devices/cc35xx/inc/hw_hif.h"
#include "ti/devices/cc35xx//driverlib/debug.h"
#include "ti/devices/cc35xx//driverlib/dma.h"

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
// Return values that can be returned from HIFRead() and HIFWrite()
//
//*****************************************************************************
#define HIF_STATUS_SUCCESS       (0)  //!< Success
#define HIF_ERR_NOT_ALIGN        (-1) //!< Error code for unaligned data
#define HIF_ERR_DMA_READ_FAIL    (-2) //!< Error code for failure of read operation using DMA
#define HIF_ERR_DMA_WRITE_FAIL   (-3) //!< Error code for failure of write operation using DMA
#define HIF_ERR_BUFFER_OVERFLOW  (-4) //!< Error code for length which is less than required
#define HIF_ERR_INVALID_SRC_ADDR (-5) //!< Error code for unsupported source address (read operation)
#define HIF_ERR_WRITE_FAIL       (-6) //!< Error code for failure of direct write operation
#define HIF_ERR_PSRAM_READ_FAIL  (-7) //!< Error code for failure to copy data from PSRAM using XMEM
#define HIF_ERR_BUFFER_TOO_LARGE (-8) //!< Error code for transfer size exceeding staging buffer
#define HIF_ERR_INIT_FAIL        (-9) //!< Error code for initialization failure
#define HIF_ERR_PSRAM_WRITE_FAIL (-10) //!< Error code for failure to copy data to PSRAM using XMEM

//*****************************************************************************
//
// Configuration values that can be passed to HIFRead() as part of srcAddr
//
//*****************************************************************************
//! Read data for packets FIFO
#define HIF_NAB_DATA_ADDR    0x0000BFF0
//! Read control from mailbox
#define HIF_NAB_CONTROL_ADDR 0x0000BFF8

//remove the delay before read operation
//#define REMOVE_HIF_READ_DELAY

#ifndef HWREG
#define HWREG(x)                                                              \
        (*((volatile unsigned long *)(x)))
#endif

#ifndef HWREG32
#define HWREG32(x)                                                            \
        (*((volatile unsigned long *)(x)))
#endif




//*****************************************************************************
//
// Enumerations
//
//*****************************************************************************

//*****************************************************************************
//
// Functions
//
//*****************************************************************************
//*****************************************************************************
//
//! \brief Initialize HIF and DMA channel.
//!
//! \param dmaChannel the DMA channel that will be used, can be 1 to 11.
//! \return
//! - \ref HIF_STATUS_SUCCESS
//! - \ref HIF_ERR_INIT_FAIL
//
//*****************************************************************************
extern int32_t HIFInit(uint32_t dmaChannel);

//*****************************************************************************
//
//! \brief Deinitialize HIF and unregister power notification.
//!
//! Must be called symmetrically with \ref HIFInit() to prevent double
//! registration of the power notify object on the next \ref HIFInit() call.
//!
//! \return
//! - \ref HIF_STATUS_SUCCESS
//
//*****************************************************************************
extern int32_t HIFDeinit(void);

//*****************************************************************************
//
//! \brief Read data from HIF module.
//!
//! This function must be called after \ref HIFInit().
//! The function first sets write mode to start read operation from the NAB
//! and then starts the read operation.
//!
//! **PSRAM Support**: If destStartAddr is in PSRAM range (0x60000000-0x60800000),
//! the function automatically uses a 2-stage transfer:
//!   1. HIF->RAM via SYSDMA
//!   2. RAM->PSRAM via XMEM/UDMA
//!
//! \param dmaChannel the DMA channel that will be used, can be 1 to 11.
//! \param srcAddr the address of the NAB to read from.
//! - \ref HIF_NAB_DATA_ADDR
//! - \ref HIF_NAB_CONTROL_ADDR
//!
//! \param destStartAddr is the destination address of the read (supports both RAM and PSRAM).
//! \param length is size of the data to read in bytes. Must be a multiple of 4,
//!         and greater than 16 bytes (if srcAddr == HIF_NAB_DATA_ADDR).
//!         Maximum 2048 bytes for PSRAM destinations.
//! \param actualLengthRead pointer to the actual length that was read, received by reading the NAB header.
//! \return
//! - \ref HIF_STATUS_SUCCESS
//! - \ref HIF_ERR_DMA_READ_FAIL
//! - \ref HIF_ERR_WRITE_FAIL
//! - \ref HIF_ERR_BUFFER_OVERFLOW
//! - \ref HIF_ERR_INVALID_SRC_ADDR
//! - \ref HIF_ERR_PSRAM_WRITE_FAIL
//! - \ref HIF_ERR_BUFFER_TOO_LARGE
//!
//
//*****************************************************************************
extern int32_t HIFRead(uint32_t dmaChannel,
                       uint32_t srcAddr,
                       uint8_t *destStartAddr,
                       uint16_t length,
                       uint32_t *actualLengthRead);

//*****************************************************************************
//
//! \brief Write data to HIF module.
//!
//! This function must be called after \ref HIFInit().
//!
//! **PSRAM Support**: If srcAddr is in PSRAM range (0x60000000-0x60800000),
//! the function automatically uses a 2-stage transfer:
//!   1. PSRAM->RAM via XMEM/UDMA
//!   2. RAM->HIF via SYSDMA
//!
//! \param dmaChannel the DMA channel that will be used, can be 1 to 11.
//! \param srcAddr is the address to write from (supports both RAM and PSRAM).
//! \param length is size of the data to write in bytes. Must be multiple of 4.
//!        Maximum 2048 bytes for PSRAM sources.
//
//! \return
//! - \ref HIF_STATUS_SUCCESS
//! - \ref HIF_ERR_NOT_ALIGN
//! - \ref HIF_ERR_DMA_WRITE_FAIL
//! - \ref HIF_ERR_PSRAM_READ_FAIL
//! - \ref HIF_ERR_BUFFER_TOO_LARGE
//
//*****************************************************************************
extern int32_t HIFWrite(uint32_t dmaChannel, uint8_t *srcAddr, uint16_t length);

//*****************************************************************************
//
//! \brief Wait for fifo to be empty and Switch HIF to idle mode 0
//!
//!
//!
//! \return
//!
//*****************************************************************************
extern void HIFSetIdle(void);

//*****************************************************************************
//
//! \brief Collect debug information in case of an error
//!
//!
//!
//! \return
//!
//*****************************************************************************
extern void HIFCollectDebugInfo(void);

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

#endif // __HIF_H__
