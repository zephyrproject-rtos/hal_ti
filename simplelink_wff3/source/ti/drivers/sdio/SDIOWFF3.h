/*
 * Copyright (c) 2025, Texas Instruments Incorporated
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
/*
 *  ======== SDIOWFF3.h ========
 */
/*
 * @file       SDIOWFF3.h
 * @brief      SDIO driver implementation for a Wi-Fi F3 device.
 *             SDIOWFF3 peripheral using the DMA controller or Core.
 *
 * # Driver include #
 *  The SDIOWFF3 header file should be included in an application as follows:
 *  @code
 *  #include <ti/drivers/SDIO.h>
 *  #include <ti/drivers/sdio/SDIOWFF3.h>
 *  @endcode
 *
 *  Refer to @ref SDIO.h for a complete description of APIs.
 *
 * # Overview #
 * The general SDIO API should be used in application code, i.e. #SDIO_open()
 * should be used instead of #SDIO_open(). The board file will define the
 * device specific config, and casting in the general API will ensure that the
 * correct device specific functions are called.
 *
 * # General Behavior #
 * Before using SDIOWFF3 on Wi-Fi F3 devices:
 *   - The SDIOWFF3 driver is initialized by calling #SDIO_init().
 *   - The SDIOWFF3 HW is configured and flags system dependencies (e.g. IOs, power,
 *     etc.) by calling #SDIO_open().
 *   - The SDWFF3 driver makes use of DMA in order to optimize throughput. This is
 *     handled directly by the SDIOWFF3 driver, so the application should never make
 *     any calls directly to the DMAWFF3.h driver.
 *   - After SDIOWFF3 HW IP initialized, SDIO peripheral must be initialized by SDIO
 *     controller before read and write.
 *     It is recommended to check with #SDIOWFF3_isSdioInitialized() if the host
 *     already initialized the peripheral.
 *     note: The driver will indicate to the application if the SDIO
 *           peripheral is initialized, using callback function that define
 *           in the Parameters of #SDIO_open().
 *
 * After SDIOWFF3 operation has ended:
 *   - Release system dependencies for SDIO by calling #SDIO_close().
 *
 * The SDIOWFF3.h driver is setting a power constraint during transfers to
 * keep the device out of sleep. When the transfer has finished, the power
 * constraint is released.
 *
 *  # Data Frames #
 *  SDIOWFF3 data frames is fixed on 32-bits (4-bytes)
 *
 *  # Transfer Size Limit #
 *  The DMA controller only supports data transfers of up to 16383 bytes.
 *  A transfer with more than 16383 bytes will be transmitted/received in
 *  multiple 16383 sized portions until all data has been transmitted/received.
 *
 * # Supported Functions #
 *
 * API function                   | Description
 * ------------------------------ |------------------------------------------------------------
 * #SDIO_init()                   | This function initializes the SDIO driver
 * #SDIO_open()                   | Function to open the SDIO peripheral with the parameters specified
 * #SDIO_close()                  | Function to close a SDIO peripheral
 * #SDIO_write()                  | Function that writes data to Tx FIFO
 * #SDIO_read()                   | Function that reads the transmitted data from Rx FIFO
 * #SDIOWFF3_isSdioInitialized()  | Check if SDIO host init SDIO peripheral
 *
 * #SDIO Header#
 * To provide transaction parameters (such as: Direction, number of bytes etc.)
 * Host SDIO must send header on the data line.
 * The header length must be divided by 4 bytes.
 * Threshold on the Rx FIFO inside SDIO peripheral, could generate an
 * IRQ to indicate that the host sent a header.
 * Once the threshold IRQ rose, application should read the header.
 * note: SDIOWFF3 doesn't familiar with the header protocol.
 *
 * **Important**
 * With getting a new header the driver mask the threshold IRQ.
 * The masking will be removed in the end of #SDIO_read().
 *   - If the header define writing from the host to peripheral then the masking
 *     will be removed by #SDIO_read()
 *
 * # SDIO callback Function #
 * With using #SDIO_open(), the application must provide a pointer to a
 * call-back function.
 * The driver will call the function from IRQ function, the implementation of
 * the function must be shortest as possible SDIOWFF3 can indicate the
 * application about various events:
 *
 *  Event enumeration          |IDX| Description
 *  -------------------------- |---|------------------------------------------------------------
 *  SDIOWFF3_DATA_IN_RX_FIFO   | 1 | Received new SDIO header
 *  SDIOWFF3_CARD_INIT         | 2 | SDIO host initialized SDIO peripheral
 *  SDIOWFF3_CARD_DEINIT       | 3 | SDIO host reset SDIO peripheral
 *  SDIOWFF3_RX_CRC_ERROR      | 4 | Received command or data from host with CRC error
 *  SDIOWFF3_RX_BUFF_OVERRUN   | 5 | Overrun error on Rx FIFO
 *  SDIOWFF3_RX_BUFF_UNDERRUN  | 6 | Underrun error on Rx FIFO
 *  SDIOWFF3_TX_BUFF_OVERRUN   | 7 | Overrun error on Tx FIFO
 *  SDIOWFF3_TX_BUFF_UNDERRUN  | 8 | Underrun error on Tx FIFO
 *  SDIOWFF3_HOST_WRONG_ACCESS | 9 | Host tried to access to wrong address
 *  SDIOWFF3_HOST_SENT_MSG  |10 | Host sent a new message
 *
 * # Sys-Config #
 * The output of the sysconfig will supply #SDIO_Config, #SDIOWFF3_Object and #SDIOWFF3_HwAttrs
 * for the driver usage.
 * A sample #SDIOWFF3_HwAttrs structure is shown below:
 *
 * SDIOWFF3_HwAttrs SDIOWFF3_hwAttrs[CONFIG_SDIO_COUNT] = {
 *    {
 *     .FN0baseAddr        = SDIO_CORE_BASE,
 *     .FN1baseAddr        = SDIO_CARD_FN1_BASE,
 *     .intNum             = INT_SDIO_CARD_IRQ_REQ,
 *     .intPriority        = (~0),
 *     .powerID            = PowerWFF3_PERIPH_SDIO,
 *     .rxDmaChannel       = 6,
 *     .txDmaChannel       = 5,
 *     .headerLen          = 4,
 *     .clkPin             = 12,
 *     .clkPinMux          = 19,
 *     .cmdPin             = 13,
 *     .cmdPinMux          = 19,
 *     .data0Pin           = 33,
 *     .data0PinMux        = 30,
 *     .data1Pin           = 32,
 *     .data1PinMux        = 30,
 *     .data2Pin           = 31,
 *     .data2PinMux        = 30,
 *     .data3Pin           = 10,
 *     .data3PinMux        = 19,
 *     .irqPin             = 17,
 *     .irqPinMux          = 17
 *    },
 *};
 *
 *  function scratch
 *  void SDIOWFF3_callBack(SDIO_Handle handle, uint8_t eventIDX, uint32_t *transHeader, uint32_t headerLen)
 *  {
 *     if(eventIDX == SSDIOWFF3_DATA_IN_RX_FIFO
 *     {
 *         ...
 *     }
 *     else if(eventIDX == SDIOWFF3_CARD_INIT)
 *     {
 *        ...
 *     }
 *     else if(eventIDX == SDIOWFF3_CRC_ERROR)
 *     {
 *        ...
 *     }
 *  }
 *
 *---------------------------------------------------------------------*
 * An example for using SDIOWFF3 driver correctly on Wi-Fi F3 devices
 *---------------------------------------------------------------------*
 *
 *  @code
 *  Firstly the application must generate a SDIOWFF3_Param struct and define the callback function.
 *
 *  //Variable declaration for driver usage - can be declare with any name
 *  SDIOWFF3_Param SDIOWFF3_param;
 *
 *  //Initiate SDWFF3_Param
 *  SDIOWFF3_param.SDIOWFF3_CallbackFxn = SDIOWFF3_callBack;
 *
 *  //To start using SDIO driver, the driver must be initialized
 *  //SDIO_config variable is generated as output by SysConfig
 *  SDIO_init(&SDIO_config);
 *
 *  //Then the SDIO peripheral must be open using *SDIOWFF3_param
 *  int_fast16_t ret = SDIO_open(0, (SDIO_Params *)&SDIOWFF3_param);
 *
 *
 */

#ifndef ti_drivers_sdio_SDIOWFF3__include
#define ti_drivers_sdio_SDIOWFF3__include

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_sdio_card_fn1.h)
#include DeviceFamily_constructPath(inc/hw_sdio_core.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_iomux.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/ClockP.h>

#include <ti/drivers/SDIO.h>

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------//

typedef void (*SDIOWFF3EventCB)(SDIO_Handle handle, uint8_t eventIDX);

typedef enum
{
    SDIOWFF3_DATA_IN_RX_FIFO   = 1,
    SDIOWFF3_CARD_INIT         = 2,
    SDIOWFF3_CARD_DEINIT       = 3,
    SDIOWFF3_RX_CRC_ERROR      = 4,
    SDIOWFF3_RX_BUFF_OVERRUN   = 5,
    SDIOWFF3_RX_BUFF_UNDERRUN  = 6,
    SDIOWFF3_TX_BUFF_OVERRUN   = 7,
    SDIOWFF3_TX_BUFF_UNDERRUN  = 8,
    SDIOWFF3_HOST_WRONG_ACCESS = 9,
    SDIOWFF3_HOST_SENT_MSG     = 10
} SDIOWFF_eventIDX;

/**
 *  \brief SDIOWFF3 driver object
 */
typedef struct
{
    /*! True if the driver is initiated */
    bool isInit;

    /*! True if the driver is opened */
    bool isOpen;

    /*! True if the card is initiated */
    bool cardInitiated;

} SDIOWFF3_Object;

typedef struct
{
    /*! FN0 HW register base address */
    uint32_t FN0baseAddr;

    /*! FN1 HW register base address */
    uint32_t FN1baseAddr;

    /*! Interrupt number for HWip driver */
    uint32_t intNum;

    /*! Interrupt priority for HWip driver */
    uint32_t intPriority;

    /*! Peripheral ID for power driver */
    uint32_t powerID;

    /*! DMA channel for SDIO Rx FIFO */
    uint32_t rxDmaChannel;

    /*! DMA channel for SDIO Tx FIFO */
    uint32_t txDmaChannel;

    /*! Rx Threshold value */
    uint32_t thresholdLen;

    /*! GPIO number for clock I/F */
    uint32_t clkPin;

    /*! GPIO mode number for clock I/F */
    uint32_t clkPinMux;

    /*! GPIO number for command I/F */
    uint32_t cmdPin;

    /*! GPIO mode number for command I/F */
    uint32_t cmdPinMux;

    /*! GPIO number for data 0 I/F */
    uint32_t data0Pin;

    /*! GPIO mode number for data 0 I/F */
    uint32_t data0PinMux;

    /*! GPIO number for data 1 I/F */
    uint32_t data1Pin;

    /*! GPIO mode number for data 1 I/F */
    uint32_t data1PinMux;

    /*! GPIO number for data 2 I/F */
    uint32_t data2Pin;

    /*! GPIO mode number for data 2 I/F */
    uint32_t data2PinMux;

    /*! GPIO number for data 3 I/F */
    uint32_t data3Pin;

    /*! GPIO mode number for data 3 I/F */
    uint32_t data3PinMux;

    /*! GPIO number for IRQ I/F */
    uint32_t irqPin;

    /*! GPIO mode number for IRQ I/F */
    uint32_t irqPinMux;

    /*! HWI interrupt params */
    HwiP_Params hwiPrms;

    /*! HWI interrupt struct */
    HwiP_Struct hwiStruct;

    /*! Application callback function */
    SDIOWFF3EventCB SDIOWFF3_CBFunction;

} SDIOWFF3_HwAttrs;

typedef struct
{
    /*! Application callback function */
    SDIOWFF3EventCB SDIOWFF3_CallbackFxn;

} SDIOWFF3_Param;

/*!
 *  @brief Function to check if SDIO host already initialize SDIO peripheral
 *         SDIO initialize definition is:
 *              TRUE - after SDIO host enable SDIO functions
 *              FALSE - after SDIO host reset SDIO peripheral
 *
 *  @pre SDIO driver has been opened and initialized by calling #SDIO_open()
 *
 *  @return True if the card is initialized
 */
bool SDIOWFF3_isSdioInitialized(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_sdio_SDIOWFF3__include */
