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

/*!***************************************************************************
 *  @file       SDIO.h
 *  @brief      Secure Digital Input Output (SDIO) Driver
 *
 *  @anchor ti_drivers_SDIO_Overview
 *  # Overview
 *
 *  The SDIO driver is designed to serve as an interface to perform basic
 *  transfers directly between Hosts.
 *
 *  <hr>
 *  @anchor ti_drivers_SDIO_Usage
 *  # Usage
 *  SDIO (Secure Digital Input Output) provides a reliable and efficient method for
 *  connecting peripheral devices to a host system.
 *  It allows the host device, such as a microcontroller or processor, to communicate with various
 *  SDIO-compatible modules, including Wi-Fi, Bluetooth, GPS, and other external peripherals.
 *  The host can use standard SDIO commands to initialize and control the connected device.
 *
 *  @anchor ti_drivers_SDIO_Synopsis
 *  ## Synopsis
 *  @anchor ti_drivers_SDIO_Synopsis_Code
 *
 *  <hr>
 *  @anchor ti_drivers_SDIO_Configuration
 *  # Configuration
 *  Refer to the @ref driver_configuration "Driver's Configuration"
 *  section for driver configuration information.
 *
 *  <hr>
 ******************************************************************************
 */

#ifndef ti_drivers_SDIO__include
#define ti_drivers_SDIO__include

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @defgroup SDIO_STATUS Status Codes
 *  SDIO_STATUS_* macros are general status codes returned by SDIO driver
 *  @{
 *  @ingroup SDIO_CONTROL
 */

/*!
 * @brief Successful status code returned by SDIO driver
 */
#define SDIO_STATUS_SUCCESS (0)

/*!
 * @brief Generic error status code returned by SDIO driver
 */
#define SDIO_STATUS_ERROR (-1)
/** @}*/

/*!
 *  @brief      A handle that is returned from a #SDIO_open() call.
 */
typedef struct SDIO_Config_ *SDIO_Handle;

/*!
 *  @brief SDIO Parameters
 *
 *  SDIO Parameters are used to with the #SDIO_open() call.
 *  Default values for these parameters are set using #SDIO_Params_init().
 *
 *  @sa #SDIO_Params_init()
 */

/* SDIO Parameters */
typedef struct
{
    void *custom; /*!< Custom argument used by driver implementation */
} SDIO_Params;

/*!
 *  @brief SDIO Global configuration
 *
 *  The #SDIO_Config structure contains a set of pointers used
 *  to characterize the SDIO driver implementation.
 *
 *  This structure needs to be defined before calling #SDIO_init() and it must
 *  not be changed thereafter.
 *
 *  @sa #SDIO_init()
 */
typedef struct SDIO_Config_
{

    /*! Pointer to a driver specific data object */
    void *object;

    /*! Pointer to a driver specific hardware attributes structure */
    void const *hwAttrs;
} SDIO_Config;

/*!
 *  @brief Function to close a SDIO peripheral specified by the SDIO handle.
 *
 *  @pre #SDIO_open() had to be called first.
 *
 *  @param handle An #SDIO_Handle returned from #SDIO_open()
 *
 *  @sa #SDIO_open()
 */
extern void SDIO_close(SDIO_Handle handle);

/*!
 *  @brief This function initializes the SDIO driver.
 *
 *  @pre The #SDIO_Config[] array must exist and be persistent before this
 *       function can be called. This function must also be called before
 *       any other SDIO driver APIs. This function call does not modify any
 *       peripheral registers.
 */
extern void SDIO_init(void);

/*!
 *  @brief Function to initialize the #SDIO_Params struct to its defaults.
 *
 *  @param params A pointer to #SDIO_Params structure for initialization.
 */
extern void SDIO_Params_init(SDIO_Params *params);

/*!
 *  @brief Function to open the SDIO peripheral with the index and parameters
 *         specified.
 *
 *  @pre SDIO driver has been initialized using #SDIO_init().
 *
 *  @param index  Logical peripheral number for the SDIO indexed into
 *                the #SDIO_Config[] table.
 *
 *  @param params Pointer to a parameter block, if NULL it will use
 *                default values. All the fields in this structure are
 *                RO (read-only).
 *
 *  @return An #SDIO_Handle on success or a NULL on an error or if it has been
 *          opened already.
 *
 *  @sa #SDIO_init()
 *  @sa #SDIO_close()
 */
extern SDIO_Handle SDIO_open(uint_least8_t index, SDIO_Params *params);

/*!
 *  @brief Function that reads the data from SDIO host.
 *         The destination is specified by \a buf. And the total number of
 *         bytes to read is provided by \a numByte.
 *
 *  @pre SDIO driver has been opened and initialized by calling #SDIO_open()
 *
 *  @param handle An #SDIO_Handle returned from #SDIO_open().
 *
 *  @param buf Pointer to a buffer to read data into.
 *
 *  @param numByte Number of bytes to be read.
 *
 *  @return #SDIO_STATUS_SUCCESS if no errors occurred during the write,
 *          #SDIO_STATUS_ERROR otherwise.
 *
 *  @sa SDIO host initialized the SDIO peripheral
 */
extern int_fast16_t SDIO_read(SDIO_Handle handle, void *buf, int_fast32_t numByte);

/*!
 *  @brief Function that writes data to SDIO host.
 *         The source is specified by \a buf. And the total number of
 *         bytes to read is provided by \a numByte
 *
 *  @pre SDIO driver has been opened and initialized by calling #SDIO_open()
 *
 *  @param  handle An #SDIO_Handle returned from #SDIO_open().
 *
 *  @param  buf Pointer to a buffer containing data to write to disk.
 *
 *  @param  numByte Number of bytes to be written.
 *
 *  @return #SDIO_STATUS_SUCCESS if no errors occurred during the write,
 *          #SDIO_STATUS_ERROR otherwise.
 *
 *  @sa SDIO host initialized the SDIO peripheral
 */
extern int_fast16_t SDIO_write(SDIO_Handle handle, void *buf, int_fast32_t numByte);

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_SDIO__include */
