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
 * @file       SDWFF3.h
 * @brief      SDWFF3 driver implementation for a Wi-Fi F3 device.
 *             SDWFF3 controller using the DMA controller or Core.
 *
 * # Driver include #
 * The SDWFF3 header file should be included in an application as follows:
 * @code
 * #include <ti/drivers/SD.h>
 * #include <ti/drivers/sd/SDWFF3.h>
 * #include <ti/drivers/dma/DMAWFF3.h>
 * @endcode
 *
 * Refer to @ref SD.h for a complete description of APIs.
 *
 * Note that the user also needs to include the DMAWFF3.h driver since the SDWFF3
 * uses DMA in order to improve throughput.
 *
 * # Overview #
 * The general SD API should be used in application code, i.e. #SD_open()
 * should be used instead of #SDWFF3_open(). The board file will define the
 * device specific config, and casting in the general API will ensure that the
 * correct device specific functions are called.
 *
 * # General Behavior #
 * Before using SDWFF3 on Wi-Fi F3 devices:
 *   - The SDWFF3 driver is initialized by calling #SD_init().
 *   - The SDWFF3 HW is configured and flags system dependencies (e.g. IOs, power,
 *     etc.) by calling #SD_open().
 *   - The SDWFF3 driver makes use of DMA in order to optimize throughput. This is
 *     handled directly by the SDWFF3 driver, so the application should never make
 *     any calls directly to the DMAWFF3.h driver.
 *   - After SDWFF3 HW IP initialized, card must be initialized too.
 *     The application must make sure that the card is connected.
 *     It is recommended to check with #SD_control() with command SDWFF3_CMD_IS_CARD_CONNECTED
 *     before using #SD_initialize().
 *     note: The driver will indicate to the application if the card is connected or not,
 *           using call-back function that define in the Parameters of #SD_open().
 *   - #SD_read() and #SD_write() can be called only after the HW IP and the card are initiated.
 *
 * After SDWFF3 operation has ended:
 *   - Release system dependencies for SD by calling #SD_close().
 *
 * The SDWFF3.h driver is setting a power constraint during transfers to
 * keep the device out of sleep. When the transfer has finished, the power
 * constraint is released.
 *
 * ## Power voltage #
 * This driver supports a card voltage of 3.3V only.
 * In case the pins of the SD card are defined as 1.8V, the user must use external
 * level-shifter and supply 3.3V to the card.
 *
 * ## Data Frames #
 * SDWFF3 data frames is fixed on 32-bits (4-bytes)
 *
 * ## Bit Rate ##
 * When the connected card is UHS-1 then the maximum bit rate is 40MHz.
 * Else the maximum bit rate is 20MHz.
 *
 * ### Transfer Size Limit #
 * The DMA controller only supports data transfers of up to 16383 bytes.
 * A transfer with more than 16383 bytes will be transmitted/received in
 * multiple 16383 sized portions until all data has been transmitted/received.
 *
 * ## Polling SDWFF3 transfers #
 * When using #SD_read() or #SD_write() with small number of sectors the transmit can be done by polling
 * the peripheral & sending data sector-by-sector. A controller device can
 * perform the transfer immediately and return, but a peripheral will block
 * until it receives the number of sectors specified in the #SD_read() or #SD_write() call.
 * The minDmaTransferSize field in the hardware attributes is the threshold; if
 * the transaction count is below the threshold a polling transfer is
 * performed; otherwise a DMA transfer is done.  This is intended to reduce the
 * overhead of setting up a DMA transfer to only send a few data sectors.
 *
 * # Supported Functions #
 * Generic API function   | WFF3 API function       | Description
 * -----------------------|----------------------- -|------------------------------------------------------------
 * #SD_init()             | #SDWFF3_init()          | Initializes the SD driver
 * #SD_open()             | #SDWFF3_open()          | Open the SD peripheral with the parameters specified
 * #SD_close()            | #SDWFF3_close()         | Close a SD peripheral
 * #SD_initialize()       | #SDWFF3_initialize()    | Initialize the SD card
 * #SD_control()          | #SDWFF3_control()       | Performs implementation specific features
 * #SD_write()            | #SDWFF3_write()         | Writes data to the specified sectors of the SD card
 * #SD_read()             | #SDWFF3_read()          | Reads the specified sectors from the SD card
 * #SD_getNumSectors()    | #SDWFF3_getNumSectors() | Obtain the total number of sectors on the SD card
 * #SD_getSectorSize()    | #SDWFF3_getSectorSize() | Obtain the sector size used to access the SD card
 *
 * @note All calls should go through the generic API
 *
 * # SysConfig #
 * The output of SysConfig will supply #SD_Config, #SDWFF3_Object and #SDWFF3_HwAttrs
 * for the driver usage.
 * A sample #SDWFF3_HwAttrs structure is shown below:
 *
 * SDWFF3_HwAttrs SDWFF3_hwAttrs[CONFIG_SD_COUNT] = {
 *  {
 *    .baseAddr           = SDMMC_BASE,
 *    .intNum             = INT_EVT_SDMMC_PUB_REQ,
 *    .intPriority        = (~0),
 *    .powerID            = PowerWFF3_PERIPH_SDMMC,
 *    .DmaChannel         = 5,
 *    .clkPin             = 14,
 *    .clkPinMux          = 3,
 *    .cmdPin             = 15,
 *    .cmdPinMux          = 3,
 *    .data0Pin           = 13,
 *    .data0PinMux        = 3,
 *    .data1Pin           = 12,
 *    .data1PinMux        = 3,
 *    .data2Pin           = 11,
 *    .data2PinMux        = 3,
 *    .data3Pin           = 10,
 *    .data3PinMux        = 3,
 *    .cdPin              = GPIO_INVALID_INDEX,
 *    .cdPinMux           = GPIO_MUX_GPIO_INTERNAL,
 *    .wpPin              = GPIO_INVALID_INDEX,
 *    .wpPinMux           = GPIO_MUX_GPIO_INTERNAL,
 *    .powPin             = GPIO_INVALID_INDEX,
 *    .powPinMux          = GPIO_MUX_GPIO_INTERNAL,
 *    .numData            = 4,
 *    .divClk             = 0,
 *    .cdEnable           = false,
 *    .cdPolHigh          = false,
 *    .wpEnable           = false,
 *    .wpPolHigh          = false,
 *    .powEnable          = false,
 *    .powerOffInSleep    = false
 *  },
 *  };
 *---------------------------------------------------------------------*
 * An example for using SDWFF3 driver correctly on Wi-Fi F3 devices
 *---------------------------------------------------------------------*
 *
 *  @code
 *  Customer should provide a callback function by #SDWFF3_Param that is sent to #SD_open().
 *  SDWFF3 will indicate the application for any event in Event_Type enum
 *  //function scratch
 *  void SDWFF3_callBack(uint8_t event){
 *      if (event == SD_CARD_INSERTED){
 *          // do something
 *      }
 *      .
 *      .
 *      .
 *  }
 *
 *  //Variable declaration for driver usage - can be declare with any name
 *  SDWFF3_Param SDWFF3_param;
 *
 *  //Initiate #SDWFF3_Param - for more details about the params, please review #SDWFF3_open description
 *  SDWFF3_param.SDWFF3CallbackFxn = SDWFF3_callBack;
 *  SDWFF3_param.minDmaTransferSize = (uint32_t)num;
 *
 *  //To start using SD driver, the driver must be initialized
 *  SD_init();
 *
 *  //Then the SD host controller peripheral must be open using #SDWFF3_param
 *  SD_handle = SD_open(0, (SD_Params *)&SDWFF3_param);
 *
 *  //The last initialization is for the card - IF CONNECTED!!
 *  SD_initialize(SD_handle);
 *
 *  if the return from #SD_initialize() is SD_STATUS_SUCCESS, read and write to the card is allowed
 *
 *
 */

#ifndef ti_drivers_sd_SDWFF3__include
#define ti_drivers_sd_SDWFF3__include

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(driverlib/dma.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_iomux.h)
#include DeviceFamily_constructPath(inc/hw_sdmmc.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)

#include <ti/drivers/SD.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/Power.h>

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------//

/*!
 * @brief Callback function supplied by the application
 */
typedef void (*SDWFF3_EventCB)(uint8_t event);

/*!
 * @brief Command used by #SD_control()
 *
 * Review #SDWFF3_control() for more details
 */
#define SDWFF3_CMD_IS_CARD_CONNECTED       (SD_CMD_RESERVED + 0)
#define SDWFF3_CMD_IS_CARD_WRITE_PROTECTED (SD_CMD_RESERVED + 1)

/**
 *  \brief SDWFF3 driver object
 */
typedef struct
{
    /*! True if the controller is opened */
    bool isOpen;

    /*! True if the card is initiated */
    bool cardInitiated;

    /*! Type of card */
    SD_CardType cardType;

    /*! define if the card is connected */
    bool card_inserted;

    /*! define if the card is write protected */
    bool write_protected;

    /*! Card identification register */
    uint32_t cid[4];

    /*! Relative card address */
    uint32_t rca;

    /*! Card specific data */
    uint32_t csd[4];

    /*! SD configuration register */
    uint32_t scr[2];

    /*! Transfer speed */
    uint8_t tranSpeed;

    /*! Number of bytes to be transferred per block */
    uint32_t curBlockSize;

    /*! Max Number of bytes to be transferred per block that can be configured */
    uint32_t maxBlockSize;

    /*! Number of sectors - sector = 512B */
    uint32_t numSectors;

    /*! Data dec. block counter */
    uint32_t dataBlockCount;

    /*! Define if block length can be changed */
    bool partialBlock;

    /*! Num of data line that the card supported */
    uint32_t maxBusWidth;

    /*! Variable to divide card clock, based on 40MHz */
    uint32_t clockDiv;

    /*! DMA transaction threshold */
    uint32_t SDminDmaTransferSize;

    /*! Application call-back function */
    SDWFF3_EventCB SDWFF3_CB_function;

    /*! HWI interrupt params */
    HwiP_Params SDhwiPrms;

    /*! HWI interrupt struct */
    HwiP_Struct SDhwiStruct;

} SDWFF3_Object;

typedef struct
{
    /*! SD HW register base address */
    uint32_t baseAddr;

    /*! Interrupt number for HWip driver */
    uint32_t intNum;

    /*! Interrupt priority for HWip driver */
    uint32_t intPriority;

    /*! Peripheral ID for power driver */
    PowerWFF3_Resource powerID;

    /*! DMA channel for SD */
    uint32_t DmaChannel;

    /*! GPIO number for clock I/F */
    uint8_t clkPin;

    /*! GPIO mode number for clock I/F */
    uint8_t clkPinMux;

    /*! GPIO number for command I/F */
    uint8_t cmdPin;

    /*! GPIO mode number for command I/F */
    uint8_t cmdPinMux;

    /*! GPIO number for data 0 I/F */
    uint8_t data0Pin;

    /*! GPIO mode number for data 0 I/F */
    uint8_t data0PinMux;

    /*! GPIO number for data 1 I/F */
    uint8_t data1Pin;

    /*! GPIO mode number for data 1 I/F */
    uint8_t data1PinMux;

    /*! GPIO number for data 2 I/F */
    uint8_t data2Pin;

    /*! GPIO mode number for data 2 I/F */
    uint8_t data2PinMux;

    /*! GPIO number for data 3 I/F */
    uint8_t data3Pin;

    /*! GPIO mode number for data 3 I/F */
    uint8_t data3PinMux;

    /*! GPIO number for card detect I/F */
    uint8_t cdPin;

    /*! GPIO mode number for card detect I/F */
    uint8_t cdPinMux;

    /*! GPIO number for write protect I/F */
    uint8_t wpPin;

    /*! GPIO mode number write protect I/F */
    uint8_t wpPinMux;

    /*! GPIO number for HW power supply I/F */
    uint8_t powPin;

    /*! GPIO mode number for HW power supply I/F */
    uint8_t powPinMux;

    /*! Number of data lines */
    uint32_t numData;

    /*! Card clock divider */
    uint32_t divClk;

    /*! Card detect enable */
    bool cdEnable;

    /*! Is Card detect polarity high */
    bool cdPolHigh;

    /*! Write protect enable */
    bool wpEnable;

    /*! Is Write protect polarity high */
    bool wpPolHigh;

    /*! HW power supply enable */
    bool powEnable;

    /*! Card power off when host sleep */
    bool powerOffInSleep;

} SDWFF3_HwAttrs;

typedef struct
{
    /*! Application call-back function */
    void *SDWFF3CallbackFxn;

    /*! Minimum transfer size for DMA based transfer */
    uint32_t minDmaTransferSize;

} SDWFF3_Param;

typedef enum
{
    SDWFF3_NULL                 = 0,
    SDWFF3_CARD_INSERTED        = 1,
    SDWFF3_CARD_REMOVED         = 2,
    SDWFF3_CARD_WRITE_PROTECTED = 3,
    SDWFF3_STATUS_ERR           = 4
} Event_Type;

/* ========================================================================== */
/*                       Function Declarations                                */
/* ========================================================================== */

/*!
 *  The functions are based on SD.h
 *  Descriptions will appear there, and expanded here where relevant for WFF3.
 */

/*!
 *  ======== SDWFF3_close ========
 *  @brief Function to close a SD peripheral specified by the SD handle.
 *
 *  When closing the peripheral, IOs will be reset to what is configured by SysConfig.
 *  If power-off while sleep defined in Sys-Config then card must be initialized too.
 *
 *  @pre #SD_open() had to be called first.
 *
 *  @param[in] handle A #SD_Handle returned from #SD_open()
 *
 *  @sa #SD_open()
 */
void SDWFF3_close(SD_Handle handle);

/*!
 *  ======== SDWFF3_control ========
 *  @brief  Function for setting control parameters of the SDWFF3 driver
 *          after it has been opened.
 *
 *  @pre    #SDWFF3_open() has to be called first.
 *
 *  @param  handle A SDWFF3 handle returned from #SDWFF3_open()
 *
 *  @param  cmd  The command to execute, supported commands are:
 *  | Command                           | SD_STATUS_SUCCESS      | SD_STATUS_ERROR        |
 *  |-----------------------------------|------------------------|------------------------|
 *  | SDWFF3_CMD_IS_CARD_CONNECTED      | Card is connected      | Card is NOT connected  |
 *  | SDWFF3_CMD_IS_CARD_WRITE_PROTECTED| Card is write protected| Card is write protected|
 *
 *  @param  arg  Not used in SDWFF3.
 *
 *  @return Status code
 *  @retval #SD_STATUS_SUCCESS    The call was successful.
 *  @retval #SD_STATUS_ERROR      The call was unsuccessful.
 */
int_fast16_t SDWFF3_control(SD_Handle handle, uint_fast16_t cmd, void *arg);

/*!
 *  @brief Function to obtain the total number of sectors on the SD card.
 *         Note: Total Card capacity is the (NumberOfSectors * SectorSize).
 *
 *  @pre SD Card has been initialized using #SD_initialize().
 *
 *  @param  handle A #SD_Handle returned from #SD_open().
 *
 *  @return The total number of sectors on the SD card,
 *          or 0 if an error occurred.
 *
 *  @sa #SD_initialize()
 */
uint_fast32_t SDWFF3_getNumSectors(SD_Handle handle);

/*!
 *  The sector size of SD card is always 512 bytes
 */
uint_fast32_t SDWFF3_getSectorSize(SD_Handle handle);

/*!
 *  @brief This function initializes the SD driver.
 *
 *  @pre The #SD_config[] array must exist and be persistent before this
 *       function can be called. This function must also be called before
 *       any other SD driver APIs. This function call does not modify any
 *       peripheral registers.
 *
 *  @note For initializing the driver correctly, review the example for using the driver above.
 */
void SDWFF3_init(SD_Handle handle);

/*!
 *  @brief  Function to initialize the SD card.
 *
 *  @pre    SD controller has been opened by calling #SD_open().
 *
 *  @param  handle A #SD_Handle returned from #SD_open().
 *
 *  @return #SD_STATUS_SUCCESS if no errors occurred during the initialization,
 *          #SD_STATUS_ERROR otherwise.
 */
int_fast16_t SDWFF3_initialize(SD_Handle handle);

/*!
 *  @brief Function to open the SD peripheral with the index and parameters
 *         specified.
 *
 *  @pre SD controller has been initialized using #SD_init().
 *
 *  @param index  There is one SDWFF3 so index = 0.
 *
 *  @param params Pointer to a #SDWFF3_Param block.
 *                SDWFF3CallbackFxn   - call-back function for the application.
 *                                     The function must be SDWFF3EventCB type.
 *                                     See example above for template.
 *                minDmaTransferSize - Define the threshold for using DMA in transaction.
 *                                     If the number of sector is bigger than minDmaTransferSize, DMA will be used.
 *
 *  @return A #SD_Handle on success or a NULL on an error or if it has been
 *          opened already.
 *
 *  @sa #SD_init()
 *  @sa #SD_close()
 */
SD_Handle SDWFF3_open(SD_Handle handle, SD_Params *params);

/*!
 *  @brief Function that reads the specified sectors from the SD card.
 *         The destination is specified by \a buf. The starting sector
 *         is specified by \a sector and the total number of sectors to
 *         read is provided by \a secCount.
 *
 *  @pre SD controller has been opened and initialized by calling #SD_open()
 *       followed by #SD_initialize().
 *
 *  @param handle A #SD_Handle returned from #SD_open().
 *
 *  @param buf Pointer to a buffer to read data into.
 *
 *  @param sector Starting sector on the disk to read from.
 *
 *  @param secCount Number of sectors to be read.
 *
 *  @return #SD_STATUS_SUCCESS if no errors occurred during the write,
 *          #SD_STATUS_ERROR otherwise.
 *
 *  @sa #SD_initialize()
 */
int_fast16_t SDWFF3_read(SD_Handle handle, void *buf, int_fast32_t sector, uint_fast32_t secCount);

/*!
 *  @brief Function that writes data to the specified sectors of the SD card.
 *         The source is specified by \a buf. The starting sector to write
 *         is specified by \a sector and the total number of sectors to write
 *         is provided by \a secCount.
 *
 *  @pre SD controller has been opened and initialized by calling #SD_open()
 *       followed by #SD_initialize().
 *
 *  @param  handle A #SD_Handle returned from #SD_open().
 *
 *  @param  buf Pointer to a buffer containing data to write to disk.
 *
 *  @param  sector Starting sector on the disk to write to.
 *
 *  @param  secCount Number of sectors to be written.
 *
 *  @return #SD_STATUS_SUCCESS if no errors occurred during the write,
 *          #SD_STATUS_ERROR otherwise.
 *
 *  @sa     #SD_initialize()
 */
int_fast16_t SDWFF3_write(SD_Handle handle, const void *buf, int_fast32_t sector, uint_fast32_t secCount);

/* SDWFF3 function table */
extern const SD_FxnTable SDWFF3_fxnTable;

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_sd_SDWFF3__include */
