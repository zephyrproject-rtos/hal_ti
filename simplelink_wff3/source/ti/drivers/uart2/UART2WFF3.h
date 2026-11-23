/*
 * Copyright (c) 2023-2026 Texas Instruments Incorporated
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
 *  @file       UART2WFF3.h
 *
 *  @brief      UART driver implementation for a Low Power F3 device UART
 *              controller
 *
 *  The UART header file should be included in an application as follows:
 *  @code
 *  #include <ti/drivers/UART2.h> #include <ti/drivers/uart2/UART2WFF3.h>
 *  @endcode
 *
 *  @warning Due to hardware constraints, the UART2 driver for WFF3 devices
 *  has limitations if the source or destination buffers reside in external
 *  memory. For read and write operations, UART2_Mode_CALLBACK is not supported
 *  for buffers in external memory (Flash or PSRAM).
 *
 *  Refer to @ref UART2.h for a complete description of APIs and examples of
 *  use.
 *
 *  ============================================================================
 */

#ifndef ti_drivers_uart2_UART2WFF3__include
#define ti_drivers_uart2_UART2WFF3__include

#include <stddef.h>
#include <stdint.h>

#include <stdint.h>
#include <stdbool.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(driverlib/dma.h)

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/UART2.h>
#include <ti/drivers/xmem/XMEMWFF3.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @brief  UART TXD/RXD encoding/decoding scheme
 *
 *  Encoding scheme for data transmitted/received on TXD/RXD pins.
 *  The data can either be encoded as standard UART, or as an IrDA-compliant
 *  Serial Infrared stream, where the width of each pulse is 3/16th of the bit period.
 *  A low-power SIR encoding is also available, where the pulse width can be configured.
 */
typedef enum
{
    UART2WFF3_CODING_UART   = 0, /*!< TXD/RXD coded as UART */
    UART2WFF3_CODING_SIR    = 1, /*!< TXD/RXD coded as Serial Infrared */
    UART2WFF3_CODING_SIR_LP = 2, /*!< TXD/RXD coded as Low-Power Serial Infrared */
} UART2WFF3_CodingScheme;

/*!
 *  @brief  Bounce buffer descriptor for UART2 external-memory staging.
 *
 *  The DMA used by the UART2 driver on CC35xx cannot access external memory
 *  (PSRAM or external flash) directly. The UART2 driver will stage data through
 *  internal RAM buffers described by this type before transmitting data.
 *
 *  `size` should be set to the largest transaction expected to/from external
 *  memory. `buffer` must point to internal RAM aligned to 4 bytes and placed in
 *  the `.internalRAM.bss` section.
 */
typedef struct
{
    size_t size;           /*!< Capacity of the buffer in bytes; 0 disables the buffer */
    unsigned char *buffer; /*!< Pointer to the internal-RAM backing array */
} UART2WFF3_BounceBuffer;

/*!
 *  @brief  UART2WFF3 Hardware attributes
 *
 *  The baseAddr and intNum fields are used by driverlib
 *  APIs and therefore must be populated by
 *  driverlib macro definitions. These definitions are found under the
 *  device family in:
 *      - inc/hw_memmap.h
 *      - inc/hw_ints.h
 *      - driverlib/uart.h
 *
 *  intPriority is the UART peripheral's interrupt priority. This value is passed
 *  unmodified to HwiP_construct().
 *
 *  The WiFi F3 devices use three priority bits. That means ~0 has the same
 *  effect as (7 << 5).
 *
 *  Setting the priority to 0 is not supported by this driver.  HWI's with
 *  priority 0 ignore the HWI dispatcher to support zero-latency interrupts,
 *  thus invalidating the critical sections in this driver.
 *
 *  A sample structure is shown below:
 *  @code
 *  const UART2WFF3_HWAttrs UART2WFF3_hwAttrs[] = {
 *      {
 *           .baseAddr           = UARTLIN0_BASE,
 *           .intNum             = INT_SP_UART_0,
 *           .intPriority        = (~0),
 *           .rxPin              = CONFIG_GPIO_UART2_0_RX,
 *           .txPin              = CONFIG_GPIO_UART2_0_TX,
 *           .ctsPin             = GPIO_INVALID_INDEX,
 *           .rtsPin             = GPIO_INVALID_INDEX,
 *           .flowControl        = UART2_FLOWCTRL_NONE,
 *           .txPinMux           = 5,
 *           .rxPinMux           = 3,
 *           .ctsPinMux          = GPIO_MUX_GPIO_INTERNAL,
 *           .rtsPinMux          = GPIO_MUX_GPIO_INTERNAL,
 *           .rxDmaChannel       = 0,
 *           .txDmaChannel       = 1,
 *           .codingScheme       = UART2WFF3_CODING_UART,
 *           .concatenateFIFO    = false,
 *      },
 *  };
 *  @endcode
 *
 *  To enable flow control, the .ctsPin and/or .rtsPin must be assigned.
 *  In addition, .flowControl must be set to UART2_FLOWCTRL_HARDWARE.
 */
typedef struct
{
    UART2_BASE_HWATTRS
    uint32_t txDmaChannel;                 /*!< DMA TX channel number */
    uint32_t rxDmaChannel;                 /*!< DMA RX channel number */
    int32_t txPinMux;                      /*!< TX PIN mux value */
    int32_t rxPinMux;                      /*!< RX PIN mux value */
    int32_t ctsPinMux;                     /*!< CTS PIN mux value for flow control */
    int32_t rtsPinMux;                     /*!< RTS PIN mux value for flow control */
    UART2WFF3_CodingScheme codingScheme;   /*!< UART TXD/RXD encoding/decoding scheme */
    uint8_t irLPClkDivider;                /*!< Clock divider for IR Low-Power mode */
    uint8_t powerID;                       /*!< Power driver ID for this UART instance */
    bool concatenateFIFO;                  /*!< Concatenate RX and TX FIFO if write-only */
    UART2WFF3_BounceBuffer TXBounceBuffer; /*!< Bounce buffer for TX transactions */
    UART2WFF3_BounceBuffer RXBounceBuffer; /*!< Bounce buffer for RX transactions */
    bool usePsram;                         /*!< Will the driver need to transact to/from PSRAM */
    bool useFlash;                         /*!< Will the driver need to transcat from Flash */
} UART2WFF3_HWAttrs;

/*!
 *  @brief      UART2WFF3 Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    UART2_BASE_OBJECT
    Power_NotifyObj preNotify;  /*!< For configuring IO pins before entering sleep */
    Power_NotifyObj postNotify; /*!< For configuring IO pins after returning from sleep */
    uint32_t *dmaTxDestAddr;
    uint32_t *dmaRxSrcAddr;
    XMEM_Handle psramHandleTX;
    XMEM_Handle psramHandleRX;
    XMEM_Handle flashHandleTX;
} UART2WFF3_Object, *UART2WFF3_Handle;

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_uart2_UART2WFF3__include */
