/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
/*!****************************************************************************
 *  @file       I2CWFF3.h
 *
 *  @brief      I2C driver implementation for a WiFi F3 device I2C
 *              controller.
 *
 *  # Driver Include #
 *  The I2C header file should be included in an application as follows:
 *  @code
 *  #include <ti/drivers/I2C.h>
 *  #include <ti/drivers/i2c/I2CWFPF3.h>
 *  @endcode
 *
 * # Overview #
 * Refer to @ref I2C.h for a complete description of APIs.
 *
 * ## General Behavior ##
 * Before using the I2C in WFF3:
 *   - The I2C driver is initialized by calling #I2C_init().
 *   - The I2C HW is configured and system dependencies are declared (e.g. IOs,
 *     power, etc.) by calling #I2C_open().
 *   .
 * The following is true for receive operation:
 *   - RX is enabled by calling #I2C_transfer().
 *     The readCount of the #I2C_Transaction must be set to a non-zero value.
 *   - If the #I2C_transfer() succeeds, the I2C remains enabled.
 *   - The application must check the return value from I2C_transfer()
 *     to verify that the transfer succeeded.
 *   .
 * The following apply for transmit operation:
 *   - TX is enabled by calling #I2C_transfer().
 *     The writeCount of the #I2C_Transaction must be set to a non-zero value.
 *   - If the #I2C_transfer() succeeds, the I2C remains enabled.
 *   - The application must check the return value from #I2C_transfer()
 *     to verify that the transfer succeeded.
 *   .
 * After I2C operation has ended:
 *   - Release system dependencies for I2C by calling I2C_close().
 *
 * ## Error handling ##
 * If an error occurs during operation:
 *   - The I2C Controller transmits a stop bit and remains enabled.
 *
 * ## Power Management ##
 *  The I2CWFF3 driver sets a power constraint during transactions to keep
 *  the device out of sleep; so when all tasks are blocked, the device will
 *  enter idle mode instead of sleep.  When the transactions have finished,
 *  the power constraint to prohibit sleep is released.
 *  The following statements are valid:
 *    - After I2C_open() call: I2C is enabled, there are no active I2C
 *      transactions, the device can enter sleep.
 *    - After I2C_transfer() call: active I2C transactions exist, the device
 *      might enter idle, but not sleep.
 *    - When I2C_transfer() completes, either after success or error, I2C
 *      remains enabled, and the device can enter sleep.
 *    - After I2C_close() call: I2C is disabled
 *
 * ## Supported Functions ##
 *  | Generic API Function         | Description                                       |
 *  |------------------------------|---------------------------------------------------|
 *  | #I2C_init()                  | Initialize I2C driver                             |
 *  | #I2C_Params_init()           | Initialize an #I2C_Params structure               |
 *  | #I2C_open()                  | Initialize I2C HW and set system dependencies     |
 *  | #I2C_close()                 | Disable I2C HW and release system dependencies    |
 *  | #I2C_setAddressMode()        | Set the address mode to be used in I2C transfers  |
 *  | #I2C_transfer()              | Start I2C transfer                                |
 *  | #I2C_transferTimeout()       | Start I2C transfer with a timeout                 |
 *  | #I2C_cancel()                | Cancels all I2C transfers                         |
 *
 * ## Supported Bit Rates ##
 *  - #I2C_100kHz
 *  - #I2C_400kHz
 *  - #I2C_1000kHz
 *
 * ## Supported Address Modes ##
 *  - #I2C_ADDRESS_MODE_7_BIT
 *  - #I2C_ADDRESS_MODE_10_BIT
 *
 * ## Unsupported Functionality ##
 * The WFF3 I2C driver currently does not support:
 *  - Multi-controller mode
 *  - I2C target mode
 *  - DMA operation
 *
 ******************************************************************************
 */

#ifndef ti_drivers_i2c_I2CWFF3__include
#define ti_drivers_i2c_I2CWFF3__include

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/I2C.h>
#include <ti/drivers/Power.h>

#include <ti/drivers/dpl/SwiP.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @brief  I2CWFF3 Hardware attributes
 *
 *  The baseAddr and intNum fields define the base address and the interrupt
 *  number of the I2C peripheral.  These values are passed to driverlib APIs
 *  and therefore must be populated by driverlib macro definitions.  These
 *  macros are found in the header files:
 *      - inc/hw_memmap.h
 *      - inc/hw_ints.h
 *
 *  The powerMngrId is the Power driver resource ID for the I2C peripheral.
 *  These macros are defined in the device specific Power include file.

 *  intPriority is the I2C peripheral's interrupt priority. This value is passed
 *  unmodified to HwiP_construct().
 *
 *  swiPriority is the priority of a SwiP that the I2C driver constructs to
 *  finalize I2C transfers. See the documentation for the SwiP module for a
 *  description of Swi priorities.
 *
 *
 *  sdaPin and sclPin define the SDA and SCL pin mapping, respectively. These
 *  are typically defined with a macro in a header file, which maps to a GPIO
 *  number. For example, when using sysconfig, ti_drivers_config.h defines
 *  CONFIG_GPIO_I2C_0_SDA to be 18 (for GPIO18).
 *
 *  sdaPinMux and sclPinMux are values drawn from the GPIO driver. They indicate
 *  the function for that specific DIO pin that select I2C mode.
 *
 *  A sample structure is shown below:
 *  @code
 *  const I2CWFF3_HWAttrs I2CWFF3_hwAttrs[CONFIG_I2C_COUNT] = {
 *      {
 *          .baseAddr    = I2C0_BASE,
 *          .powerMngrId = PowerWFF3_PERIPH_I2C0,
 *          .intNum      = INT_SP_I2C_0_INTREQ, // TODO: Update this when OSPREY_SILICON-1671 is fixed
 *          .intPriority = (~0),
 *          .swiPriority = 0,
 *          .sclPin      = 17,
 *          .sclPinMux   = 6,
 *          .sdaPin      = 18,
 *          .sdaPinMux   = 6
 *      },
 *  };
 *  @endcode
 */
typedef struct
{
    I2C_BASE_HWATTRS

    /* I2C peripheral's Power driver ID */
    unsigned long powerMngrId;

    /*
     *  I2C Swi priority.
     *  The higher the number, the higher the priority.
     */
    uint32_t swiPriority;
    /* SDA pin index and mux */
    uint8_t sdaPin;
    uint8_t sdaPinMux;
    /* SCL pin index and mux */
    uint8_t sclPin;
    uint8_t sclPinMux;
} I2CWFF3_HWAttrs;

/*!
 *  @brief      I2CWFF3 Object.
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    I2C_BASE_OBJECT

    /* Swi object */

    SwiP_Struct swi;
    /* Bitrate of the I2C module */
    I2C_BitRate bitRate;

    /* Address mode of the I2C module.
     * Note, this is the driverlib definition of address mode and not of the type
     * I2C_AddressMode.
     */
    uint32_t addressMode;

    /* I2C power notification */
    void *i2cPostFxn;
    Power_NotifyObj i2cPostObj;
} I2CWFF3_Object;

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_i2c_I2CWFF3__include */
