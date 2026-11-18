/*
 * Copyright (c) 2023-2025, Texas Instruments Incorporated
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
/** ============================================================================
 *  @file       DMAWFF3.h
 *
 *  @brief      DMAWFF3 driver implementation.
 *
 * # Driver include #
 *  The DMAWFF3 header file should be included in an application as follows:
 *  @code
 *  #include <ti/drivers/dma/DMAWFF3.h>
 *  @endcode
 *
 * # Overview #
 * The DMAWFF3 driver currently only supports internal use by the drivers
 * that use the DMA peripheral (for example, UART2WFF3).
 * In other words, the application should never call any of the functions in this
 * file.
 *
 * # General Behavior #
 * This driver is used implicitly by other drivers (e.g., the UART2WFF3
 * driver) so users should not have to interface to this driver from the
 * application.
 *
 * # Error handling #
 * Error handling is handled by the overlying driver which uses the DMA.
 *
 * # Power management #
 * Power management is handled by the overlying driver which uses the DMA.
 *
 * # Supported functions #
 * Note that these functions should never be called from the application, they
 * are only called from other drivers. They are however included here for completeness:
 *
 * | API function                | Description                              |
 * |---------------------------  |------------------------------------------|
 * | DMAWFF3_clearInterrupt()    | Clear DMA interrupts.                    |
 * | DMAWFF3_configureChannel()  | Configure DMA channel transaction.       |
 * | DMAWFF3_connectChannel()    | Connect DMA channel to peripheral.       |
 * | DMAWFF3_disableChannel()    | Abort DMA channel operation.             |
 * | DMAWFF3_getRemainingBytes() | Get remaining bytes of DMA transaction.  |
 * | DMAWFF3_init()              | Initialize the DMA driver.               |
 * | DMAWFF3_initChannel()       | Initialize DMA channel HW functionality. |
 * | DMAWFF3_startTransaction()  | Start DMA channel transaction.           |
 *
 * @note These functions should not be called by code. These functions are called
 *       by drivers using the DMA.
 *
 * # Unsupported Functionality #
 * - DMA transaction from flash is not supported due to HW limitations.
 * - Use of DMA interrupts are not supported by this driver. It only supports
 *   clearing the interrupts for initialization purpose.
 *   Higher level drivers for peripherals that makes use of the DMA should handle
 *   the DMA related interrupts of the peripheral itself.
 *
 * ============================================================================
 */

#ifndef ti_drivers_DMAWFF3__include
#define ti_drivers_DMAWFF3__include

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/Power.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(driverlib/dma.h)

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @brief  Definitions for the config argument of the #DMAWFF3_configureChannel()
 *  function. The argument value must be a bitwise OR the supported
 *  defines.
 */
typedef enum
{
    /*! Source pointer wraps around */
    DMAWFF3_CONFIG_SRC_PTR_WRAP       = DMA_CONFIG_SRC_PTR_WRAP,
    /*! Destination pointer wraps around */
    DMAWFF3_CONFIG_DST_PTR_WRAP       = DMA_CONFIG_DST_PTR_WRAP,
    /*! Tie DMA request signal high. Set this bit when doing memory-to-memory transactions. */
    DMAWFF3_CONFIG_FORCE_REQ          = DMA_CONFIG_FORCE_REQ,
    /*! Source pointer (FIFO mode) */
    DMAWFF3_CONFIG_SRC_PTR_FIFO       = DMA_CONFIG_SRC_PTR_FIFO,
    /*! Destination pointer (FIFO mode) */
    DMAWFF3_CONFIG_DST_PTR_FIFO       = DMA_CONFIG_DST_PTR_FIFO,
    /*! Link DMA channel to RX port of peripheral */
    DMAWFF3_CONFIG_RX                 = DMA_CONFIG_RX,
    /*! Link DMA channel to TX port of peripheral */
    DMAWFF3_CONFIG_TX                 = DMA_CONFIG_TX,
    /*! Enable DMA to set a read/write clear pulse at the beginning of a job (one cycle after run cmd) */
    DMAWFF3_CONFIG_CLEAR_AT_JOB_START = DMA_CONFIG_CLEAR_AT_JOB_START,
} DMAWFF3_ChConfig;

/*!
 *  @brief  Definitions for the wordSize argument of the #DMAWFF3_configureChannel()
 *  function.
 */
typedef enum
{
    /*! Word size is 1 byte */
    DMAWFF3_WORD_SIZE_1B = DMA_WORD_SIZE_1B,
    /*! Word size is 2 bytes */
    DMAWFF3_WORD_SIZE_2B = DMA_WORD_SIZE_2B,
    /*! Word size is 4 bytes */
    DMAWFF3_WORD_SIZE_4B = DMA_WORD_SIZE_4B,
} DMAWFF3_WordSize;

/*!
 *  @brief  Definitions for the blockSize argument of the #DMAWFF3_configureChannel()
 *  function.
 */
typedef enum
{
    /*! Block size is 1 byte */
    DMAWFF3_BLOCK_SIZE_1B = DMA_WORD_SIZE_1B,
    /*! Block size is 2 bytes */
    DMAWFF3_BLOCK_SIZE_2B = DMA_WORD_SIZE_2B,
    /*! Block size is 4 bytes */
    DMAWFF3_BLOCK_SIZE_4B = DMA_WORD_SIZE_4B,
} DMAWFF3_BlockSize;

/*!
 *  @brief  Definitions for the peripheral argument of the #DMAWFF3_connectChannel()
 *  function.
 */
typedef enum
{
    DMAWFF3_PERIPH_UARTLIN_0 = DMA_PERIPH_UARTLIN_0,
    DMAWFF3_PERIPH_UARTLIN_1 = DMA_PERIPH_UARTLIN_1,
    DMAWFF3_PERIPH_SPI_0     = DMA_PERIPH_SPI_0,
    DMAWFF3_PERIPH_SPI_1     = DMA_PERIPH_SPI_1,
    DMAWFF3_PERIPH_I2C_0     = DMA_PERIPH_I2C_0,
    DMAWFF3_PERIPH_I2C_1     = DMA_PERIPH_I2C_1,
    DMAWFF3_PERIPH_SDMMC     = DMA_PERIPH_SDMMC,
    DMAWFF3_PERIPH_SDIO      = DMA_PERIPH_SDIO,
    DMAWFF3_PERIPH_MCAN      = DMA_PERIPH_MCAN,
    DMAWFF3_PERIPH_ADC       = DMA_PERIPH_ADC,
    DMAWFF3_PERIPH_PDM       = DMA_PERIPH_PDM,
    DMAWFF3_PERIPH_HIF       = DMA_PERIPH_HIF,
    DMAWFF3_PERIPH_UARTLIN_2 = DMA_PERIPH_UARTLIN_2,
} DMAWFF3_Peripheral;

/*!
 *  @brief  Function to disable a DMA channel
 *
 *  The function will abort any operation in the selected DMA channel.
 *  Function returns when abort operation is finished. The abort operation
 *  might last for a maximum of eight clock cycles.
 *
 *  @pre    Calling context: Hwi, Swi, Task
 *
 *  @post   DMAWFF3_initChannel() must be called before any new transaction
 *          can be started on the channel.
 *
 */
extern void DMAWFF3_disableChannel(uint32_t channel);

/*!
 *  @brief  Function to get the number of remaining bytes of a DMA transaction
 *
 *  The function will return the number of remaining of bytes of a DMA transaction.
 *  An aborted DMA transaction may cause bytes to remain.
 *
 *  @pre    Calling context: Hwi, Swi, Task
 *
 *  @return Number of remaining bytes in last DMA transaction
 *
 */
extern uint16_t DMAWFF3_getRemainingBytes(uint32_t channel);

/*!
 *  @brief  Function to initialize the WFF3 DMA driver and peripheral
 *
 *  The function will initialize the DMA peripheral by disabling
 *  all DMA interrupts.
 *
 *  @pre    Calling context: Hwi, Swi, Task
 *
 */
extern void DMAWFF3_init(void);

/*!
 *  @brief  Function to initialize a DMA channel
 *
 *  The function will initialize the selected DMA channel by
 *  issuing an INIT command to the channel.
 *
 *  @pre    Calling context: Hwi, Swi, Task
 *
 */
extern void DMAWFF3_initChannel(uint32_t channel);

/*!
 *  @brief  Function to configure the given DMA channel
 *
 *  The function will configure the given DMA channel.
 *  The block size of the channel determines the arbitration
 *  rate of the DMA channels.
 *
 *  @pre    Calling context: Hwi, Swi, Task
 *
 *  @param  channel    Channel number to be configured.
 *
 *  @param  blockSize  Number of words in a block (1-63 words, inclusive).
 *
 *  @param  wordSize   Size of a word which is one of the
 *                     following defines:
 *                         - \ref DMAWFF3_WORD_SIZE_1B
 *                         - \ref DMAWFF3_WORD_SIZE_2B
 *                         - \ref DMAWFF3_WORD_SIZE_4B
 *
 *  @param  config     Channel configuration which is a bitwise OR of
 *                     the following defines:
 *                         - \ref DMAWFF3_CONFIG_SRC_PTR_WRAP
 *                         - \ref DMAWFF3_CONFIG_DST_PTR_WRAP
 *                         - \ref DMAWFF3_CONFIG_FORCE_REQ
 *                         - \ref DMAWFF3_CONFIG_SRC_PTR_FIFO
 *                         - \ref DMAWFF3_CONFIG_DST_PTR_FIFO
 *                         - \ref DMAWFF3_CONFIG_RX
 *                         - \ref DMAWFF3_CONFIG_TX
 *                         - \ref DMAWFF3_CONFIG_CLEAR_AT_JOB_START
 *
 */
__STATIC_INLINE void DMAWFF3_configureChannel(uint32_t channel,
                                              uint8_t blockSize,
                                              DMAWFF3_WordSize wordSize,
                                              DMAWFF3_ChConfig config)
{
    /* Configure DMA channel */
    DMAConfigureChannel(channel, blockSize, wordSize, config);
}

/*!
 *  @internal
 *  @brief  Function to connect the given DMA channel to given peripheral
 *
 *  @pre    DMAWFF3_init() has to be called first.
 *          Calling context: Hwi, Swi, Task
 *
 *  @param  channelNo  Channel number to be connected.
 *
 *  @param peripheral  Peripheral to be connected.
 *
 */
__STATIC_INLINE void DMAWFF3_connectChannel(uint32_t channel, DMAWFF3_Peripheral peripheral)
{
    /* Connect DMA channel to peripheral */
    DMAInitChannel(channel, (DMAPeripheral)peripheral);
}

/*!
 *  @internal
 *  @brief  Function to clear a given DMA channel interrupt.
 *
 *  Will clear the DMA interrupt(s) for the given channel bitmask.
 *
 *  @pre    Calling context: Hwi, Swi, Task
 *
 *  @param  channelBitmask  A bitmask of the channels to clear interrupts for.
 *
 */
__STATIC_INLINE void DMAWFF3_clearInterrupt(uint32_t channelBitmask)
{
    /* Clear DMA interrupts */
    DMAClearInt(channelBitmask);
}

/*!
 *  @brief  Function to start a DMA transaction
 *
 *  The function will start a transaction on the given DMA channel
 *
 *  @pre    Calling context: Hwi, Swi, Task
 *
 *  @param  channel  Channel number of the DMA transaction
 *
 *  @param  srcStartAddr  Pointer to the start address of the source data.
 *                        The pointer cannot point to flash memory.
 *
 *  @param  dstStartAddr  Pointer to the destination start address
 *
 *  @param  transLenByte  Number of bytes in the DMA transaction
 *
 *  @param  remainingBytesBurst  True if burst mode shall be used
 *
 */
__STATIC_INLINE void DMAWFF3_startTransaction(uint32_t channel,
                                              const uint32_t *srcStartAddr,
                                              uint32_t *dstStartAddr,
                                              uint16_t transLenByte,
                                              bool remainingBytesBurst)
{
    /* Start DMA transaction */
    DMAStartTransaction(channel, srcStartAddr, dstStartAddr, transLenByte, remainingBytesBurst);
}

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_DMAWFF3__include */
