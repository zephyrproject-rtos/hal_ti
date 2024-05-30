/*
 * Copyright (c) 2022-2023, Texas Instruments Incorporated
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
 *  @file       UDMALPF3.h
 *
 *  @brief      UDMALPF3 driver implementation.
 *
 * # Driver include #
 *  The UDMALPF3 header file should be included in an application as follows:
 *  @code
 *  #include <ti/drivers/dma/UDMALPF3.h>
 *  @endcode
 *
 * # Overview #
 * The UDMALPF3 driver currently only supports internal use by the drivers
 * that use the uDMA peripheral (e.g., SPILPF3DMA).
 * In other words, the application should never call any of the functions in this
 * file.
 *
 * # General Behavior #
 * This driver is used implicitly by other drivers (e.g., the SPILPF3DMA
 * driver) so users should not have to interface to this driver from the
 * application.
 * The uDMA hardware makes use of a control table in RAM which must be 1024 bytes
 * aligned. The default base address of this control table is 0x20000400, however
 * this can be changed simply by defining UDMALPF3_CONFIG_BASE.
 * The SPILPF3DMA.h supports SPI0, and uses both TX and RX DMA channels.
 * Each control table entry is 16 bytes, so if an application uses SPI0
 * the total RAM usage will be 2*16=32 bytes. Please see [Use cases] (@ref
 * UDMA_23XX_USE_CASES) for example.
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
 * | API function             | Description                                    |
 * |------------------------- |------------------------------------------------|
 * | UDMALPF3_init()        | Initialize the uDMA HW.                        |
 *
 * @note These functions should not be called by code. These functions are called
 *       by drivers using the DMA.
 *
 * # Unsupported Functionality #
 * No known limitations
 *
 * # Use Cases @anchor UDMA_23XX_USE_CASES #
 * In a system that has available SPI and UART peripherals, the following
 * scenarios are possible:
 * @code
 * #define UDMALPF3_CONFIG_BASE 0x20000400
 * @endcode
 * - If only SPI0 is used (with TX mapped on channel 0 and RX mapped on channel
 * 1), this will allocate 2*16=32 RAM bytes at address:\n
 * [0x20000400-0x2000041F] = SPI0 RX/TX DMA channels
 * - If only UART0 (with TX mapped on channel 2 and RX mapped on channel 3) is
 * used, this will allocate 2*16=32 RAM bytes at address:\n
 * [0x20000420-0x2000043F] = UART0 RX/TX DMA channels
 * - If both SPI0 and UART0 are used, this will allocate 4*16=64 RAM bytes at addresses:\n
 * [0x20000400-0x2000041F] = SPI0 RX/TX DMA channels\n
 * [0x20000420-0x2000043F] = UART0 RX/TX DMA channels
 *
 * ============================================================================
 */

#ifndef ti_drivers_UDMALPF3__include
#define ti_drivers_UDMALPF3__include

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/Power.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(driverlib/udma.h)

#ifdef __cplusplus
extern "C" {
#endif

/*! Base address for the DMA control table, must be 1024 bytes aligned */
#if !defined(UDMALPF3_CONFIG_BASE)
    #define UDMALPF3_CONFIG_BASE 0x20000400
#endif

/*! Make sure DMA control table base address is 1024 bytes aligned */
#if (UDMALPF3_CONFIG_BASE & 0x3FF)
    #error "Base address for DMA control table 'UDMALPF3_CONFIG_BASE' must be 1024 bytes aligned."
#endif

/*! Compiler specific macros to allocate DMA control table entries */
#if defined(__IAR_SYSTEMS_ICC__)
    #define ALLOCATE_CONTROL_TABLE_ENTRY(ENTRY_NAME, CHANNEL_INDEX)                               \
        __no_init __root static volatile uDMAControlTableEntry ENTRY_NAME @UDMALPF3_CONFIG_BASE + \
            (CHANNEL_INDEX) * sizeof(uDMAControlTableEntry)
#elif defined(__TI_COMPILER_VERSION__) || defined(__clang__)
    #define ALLOCATE_CONTROL_TABLE_ENTRY(ENTRY_NAME, CHANNEL_INDEX) \
        static volatile uDMAControlTableEntry ENTRY_NAME            \
            __attribute__((retain,                                  \
                           location((UDMALPF3_CONFIG_BASE) + (CHANNEL_INDEX) * sizeof(uDMAControlTableEntry))))
#elif defined(__GNUC__)
    #define ALLOCATE_CONTROL_TABLE_ENTRY(ENTRY_NAME, CHANNEL_INDEX)                                          \
        extern int UDMALPF3_##ENTRY_NAME##_is_placed;                                                        \
        __attribute__((section("." #ENTRY_NAME), used)) static volatile uDMAControlTableEntry ENTRY_NAME = { \
            &UDMALPF3_##ENTRY_NAME##_is_placed}
#else
    #error "don't know how to define ALLOCATE_CONTROL_TABLE_ENTRY for this toolchain"
#endif

/*! Sets the DMA transfer size in number of items */
#define UDMALPF3_SET_TRANSFER_SIZE(SIZE)    (((SIZE - 1) << UDMA_XFER_SIZE_S) & UDMA_XFER_SIZE_M)
/*! Gets the DMA transfer size in number of items*/
#define UDMALPF3_GET_TRANSFER_SIZE(CONTROL) (((CONTROL & UDMA_XFER_SIZE_M) >> UDMA_XFER_SIZE_S) + 1)

/*!
 *  @brief      UDMALPF3 Global configuration
 */
typedef struct
{
    uint32_t CtrlBaseAddr; /*!< Base address for UDMALPF3 control table */
} UDMALPF3_Config;

/* Externs from ti_drivers_config.c */
extern const UDMALPF3_Config UDMALPF3_config;

/*!
 *  @brief  Function to initialize the LPF3 DMA driver and peripheral
 *
 *  The function will initialize the DMA peripheral and set the Control table
 *  base address. The call powers up and clocks the DMA module only during
 *  initialization. Each driver using DMA must set a power dependency
 *  on the module before starting to use it (e.g. when opening the driver) and
 *  release that dependency when DMA is no longer needed (e.g. when closing the
 *  driver).
 *
 *  @pre    Calling context: Hwi, Swi, Task
 *
 *  @return none
 *
 *  @sa
 */
extern void UDMALPF3_init(void);

/*!
 *  @internal
 *  @brief  Function to enable the given DMA channel(s)
 *
 *  @pre    UDMALPF3_init() has to be called first.
 *          Calling context: Hwi, Swi, Task
 *
 *  @param  channelBitMask  A bitmask of the channels to be enabled.
 *
 *  @sa     UDMALPF3_channelDisable
 */
__STATIC_INLINE void UDMALPF3_channelEnable(uint32_t channelBitMask)
{
    /* Enable DMA channel */
    uDMAEnableChannel(channelBitMask);
}

/*!
 *  @internal
 *  @brief  Function to check if a given DMA channel is done.
 *
 *  Will read the request done signal for the given channels
 *  and return true if all channels are done, otherwise false.
 *
 *  @pre    UDMALPF3_init() has to be called first.
 *          Calling context: Hwi, Swi, Task
 *
 *  @param  channelBitMask  A bitmask of the channels to be checked.
 *
 *  @return True if the channels are done, false otherwise.
 *
 *  @sa     UDMALPF3_channelDisable
 */
__STATIC_INLINE bool UDMALPF3_channelDone(uint32_t channelBitMask)
{
    /* Check if REQDONE is set for the specified channels */
    return (uDMAIntStatus() & channelBitMask) ? true : false;
}

/*!
 *  @internal
 *  @brief  Function to clear a given DMA channel interrupt.
 *
 *  Will clear the DMA interrupt(s) for the given bitmask provided.
 *
 *  @pre    Calling context: Hwi, Swi, Task
 *
 *  @param  channelBitMask  A bitmask of the channels to clear interrupts for.
 *
 *  @return none
 */
__STATIC_INLINE void UDMALPF3_clearInterrupt(uint32_t channelBitMask)
{
    /* Clear UDMA done interrupt */
    uDMAClearInt(channelBitMask);
}

/*!
 *  @internal
 *  @brief  Function to disable one or more DMA channels.
 *
 *  Will disable the channel(s) for the given bitmask provided.
 *
 *  @pre    Calling context: Hwi, Swi, Task
 *
 *  @param  channelBitMask  A bitmask of the channels to be disabled.
 *
 *  @return none
 *
 *  @sa     UDMALPF3_channelEnable
 */
__STATIC_INLINE void UDMALPF3_channelDisable(uint32_t channelBitMask)
{
    /* Disable provided channels(s) */
    uDMADisableChannel(channelBitMask);
}

/*!
 *  @internal
 *  @brief  Function to disable a DMA channel's attributes.
 *
 *  Will disable a channel's attributes.
 *
 *  @pre    Calling context: Hwi, Swi, Task
 *
 *  @param  channelBitMask  A bitmask of the channels to configure.
 *
 *  @param  attr  Channel attribute to disable.
 *
 *
 *  @return none
 *
 *  @sa     UDMALPF3_channelEnable
 */
__STATIC_INLINE void UDMALPF3_disableAttribute(uint32_t channelBitMask, uint32_t attr)
{
    /* disable provided attribute for the given channel */
    uDMADisableChannelAttribute(channelBitMask, attr);
}

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_UDMALPF3__include */
