/*
 * Copyright (c) 2024-2026 Texas Instruments Incorporated
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
 * ========== XMEMWFF3.h ==========
 */
#ifndef ti_drivers_xmem_XMEMWFF3__include
#define ti_drivers_xmem_XMEMWFF3__include

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 *  @brief  Memory type
 *
 *  This enumeration defines a type of memory. Flash and PSRAM are considered
 *  external, and differentiated from any internal memory
 */
typedef enum
{
    XMEM_MEM_FLASH    = 0, /*<! External Flash Memory */
    XMEM_MEM_PSRAM    = 1, /*<! External PSRAM Memory */
    XMEM_MEM_INTERNAL = 2, /*<! Internal Memory */
} XMEM_MemType;

/*
 *  @deprecated  Device enumeration.
 *
 *  These macros are defined for backwards compatibility. See #XMEM_MemType
 */
#define XMEM_FLASH 0
#define XMEM_PSRAM 1

/*!
 *  @brief  size of one word which can be read by STIG command and used in:
 *  #XMEMWFF3_read()
 */
#define XMEM_WORD_SIZE 4

/*!
 *  @brief  Number of max available XMEM Configuration.
 */
#define CONFIG_XMEM_COUNT 1

/*!
 *  @brief  Number of max available XMEM handlers.
 */
#define XMEM_NUM_HANDLER 16

/*!
 *  @brief   Successful status code returned by:
 *  #XMEMWFF3_read(), #XMEMWFF3_write(), #XMEMWFF3_erase(), or
 *  #XMEMWFF3_lock().
 *
 *  APIs returns #XMEM_STATUS_SUCCESS if the API was executed
 *  successfully.
 */
#define XMEM_STATUS_SUCCESS (0)

/*!
 *  @brief   Generic error status code returned by:
 *  #XMEMWFF3_erase(), or #XMEMWFF3_write(),
 *
 *  APIs return #XMEM_STATUS_ERROR if the API was not executed
 *  successfully.
 */
#define XMEM_STATUS_ERROR (-1)

/*!
 *  @brief An error status code returned by #XMEMWFF3_lock()
 *
 *  #XMEMWFF3_lock() will return this value if the @p timeout has expired.
 *  This is currently not supported, and is reserved for future functionality.
 */
#define XMEM_STATUS_TIMEOUT (-3)

/*!
 *  @brief An error status code returned by #XMEMWFF3_read(), #XMEMWFF3_write(), or
 *  #XMEMWFF3_erase()
 *
 *  Error status code returned if the @p offset argument is invalid
 *  (e.g., when offset + bufferSize exceeds the size of the region).
 */
#define XMEM_STATUS_INV_OFFSET (-4)

/*!
 *  @brief An error status code
 *
 *  Error status code returned by #XMEMWFF3_erase() if the @p offset argument is
 *  not aligned on a flash sector address.
 */
#define XMEM_STATUS_INV_ALIGNMENT (-5)

/*!
 *  @brief An error status code returned by #XMEMWFF3_erase() and #XMEMWFF3_write()
 *
 *  Error status code returned by #XMEMWFF3_erase() if the @p size argument is
 *  not a multiple of the flash sector size, or if @p offset + @p size
 *  extends past the end of the region.
 */
#define XMEM_STATUS_INV_SIZE (-6)

/*!
 *  @brief An error status code returned by #XMEMWFF3_write()
 *
 *  #XMEMWFF3_write() will return this value if #XMEM_WRITE_PRE_VERIFY is
 *  requested and a flash location can not be changed to the value
 *  desired.
 */
#define XMEM_STATUS_INV_WRITE (-7)

/*!
 *  @brief   An error status code returned by #XMEMWFF3_write()
 *
 *  XMEMWFF3_write() will return this value if #XMEM_WRITE_PRE_VERIFY
 *  or #XMEM_WRITE_POST_VERIFY is requested but the verification buffer has not been configured.
 */
#define XMEM_STATUS_VERIFYBUFFER (-8)

/*!
 *  @brief   An error status code returned by various XMEM functions
 *
 *  APIs return #XMEM_STATUS_INVALID_PARAMS if one or more of the
 *  input parameters are invalid (e.g., invalid flag combinations,
 *  NULL pointers, or out-of-range values).
 */
#define XMEM_STATUS_INVALID_PARAMS (-9)

/*!
 *
 *   @brief read flag.
 *
 *  If #XMEM_READ_STIG is set in the flags passed to #XMEMWFF3_read(), the
 *  read operation is done using udma.
 */
#define XMEM_READ (0x0)

/*!
 *
 *   @brief read STIG flag.
 *
 *  If #XMEM_READ_STIG is set in the flags passed to #XMEMWFF3_read(), the
 *  read operation is done using STIG command.
 */
#define XMEM_READ_STIG (0x1)

/*!
 *  @brief XMEM write flags
 *
 *  The following flags can be or'd together and passed as a bit mask
 *  to #XMEMWFF3_write().
 *  @{
 */

/*!
 *  @brief write flag.
 *
 *  If #XMEM_WRITE is used in #XMEMWFF3_write(), the write operation will be
 *  performed directly without any validation or erasing of the destination
 *  sectors. Operation is done using udma.
 *
 */
#define XMEM_WRITE (0x0)

/*!
 *  @brief Erase write flag.
 *
 *  If #XMEM_WRITE_ERASE is set in the flags passed to #XMEMWFF3_write(), the
 *  affected destination flash sectors will be erased prior to the
 *  start of the write operation.
 */
#define XMEM_WRITE_ERASE (0x1)

/*!
 *  @brief Validate write flag.
 *
 *  If #XMEM_WRITE_PRE_VERIFY is set in the flags passed to #XMEMWFF3_write(), the
 *  destination address range will be pre-tested to guarantee that the source
 *  data can be successfully written. If #XMEM_WRITE_ERASE is also requested in
 *  the write flags, then the #XMEM_WRITE_PRE_VERIFY modifier is ignored.
 */
#define XMEM_WRITE_PRE_VERIFY (0x2)

/*!
 *  @brief Validate write flag.
 *
 *  If #XMEM_WRITE_POST_VERIFY is set in the flags passed to #XMEMWFF3_write(), the
 *  destination address range will be tested after the write is finished to
 *  verify that the write operation was completed successfully.
 */
#define XMEM_WRITE_POST_VERIFY (0x4)

/*!
 *  @brief Write STIG write flag.
 *
 *  If #XMEM_WRITE_STIG is set in the flags passed to #XMEMWFF3_write(), the
 *  write operation is done using STIG command.
 */
#define XMEM_WRITE_STIG (0x8)
/** @} */

/*!
 *  @brief The maximum Flash size supported by the driver/device
 *
 *  @note The actual flash size will in most cases be smaller than this value,
 *  but this defines the upper limit of flash size that the driver can support.
 */
#define XMEM_MAX_FLASH_SIZE 0x04000000U

/*!
 *  @brief The maximum PSRAM size supported by the driver/device
 *
 *  @note The actual PSRAM size will in most cases be smaller than this value,
 *  but this defines the upper limit of PSRAM size that the driver can support.
 */
#define XMEM_MAX_PSRAM_SIZE 0x04000000U

/*!
 *  @brief  Flash register structure for address-data pairs
 *
 *  Structure used to define register address and data value pairs for
 *  STIG operations in flash memory.
 */
typedef struct
{
    uint32_t address; /*!< Register address for flash operation */
    uint32_t data;    /*!< Data value to write to or read from the register */
} FlashRegister;

/*!
 *  @brief  Flash STIG erase configuration structure
 *
 *  Structure containing configuration parameters and register operations
 *  for STIG-based flash erase operations.
 */
typedef struct
{
    uint32_t preStigCfg;                /*!< Is pre STIG configuration needed */
    uint32_t StigCfg;                   /*!< Is erase operation needed */
    uint32_t postStigCfg;               /*!< Is post STIG configuration needed */
    FlashRegister preStigOperation[1];  /*!< Register operations to perform before STIG erase */
    FlashRegister stigOperation[1];     /*!< Register operations for STIG erase command */
    FlashRegister postStigOperation[1]; /*!< Register operations to perform after STIG erase */
} FlashStigEraseCfg;

/*!
 *  @brief  Flash STIG write configuration structure
 *
 *  Structure containing configuration parameters and register operations
 *  for STIG-based flash write operations.
 */
typedef struct
{
    uint32_t preStigCfg;                /*!< Is pre STIG configuration needed */
    uint32_t postStigCfg;               /*!< Is post STIG configuration needed */
    FlashRegister preStigOperation[1];  /*!< Register operations to perform before STIG write */
    FlashRegister stigOperation[1];     /*!< Register operations for STIG write command */
    FlashRegister postStigOperation[1]; /*!< Register operations to perform after STIG write */
} FlashStigWriteCfg;

/*!
 *  @brief  Flash STIG read configuration structure
 *
 *  Structure containing configuration parameters and register operations
 *  for STIG-based flash read operations.
 */
typedef struct
{
    uint32_t preStigCfg;                /*!< Is pre STIG configuration needed */
    uint32_t postStigCfg;               /*!< Is post STIG configuration needed */
    FlashRegister preStigOperation[1];  /*!< Register operations to perform before STIG read */
    FlashRegister stigOperation[1];     /*!< Register operations for STIG read command */
    FlashRegister postStigOperation[1]; /*!< Register operations to perform after STIG read */
} FlashStigReadCfg;

/*!
 *  @brief  Flash polling configuration structure
 *
 *  Structure containing parameters for polling flash status
 *  during operations.
 */
typedef struct
{
    uint32_t NumOfIteration; /*!< Maximum number of polling iterations */
    uint32_t command;        /*!< Command to execute for polling */
    uint32_t timeOut;        /*!< Timeout value for polling operation */
    uint32_t polarity;       /*!< Expected polarity of status bit */
    uint32_t mask;           /*!< Bit mask for status checking */
} FlashPollingCfg;

/*!
 *  @brief  Flash type configuration structure
 *
 *  Structure containing all configurations and parameters
 *  for a specific flash memory type.
 */
typedef struct
{
    FlashRegister enterStigCfg[3];  /*!< Register operations to enter STIG mode */
    FlashStigReadCfg readStigCfg;   /*!< Configuration for STIG read operations */
    FlashStigWriteCfg writeStigCfg; /*!< Configuration for STIG write operations */
    FlashStigEraseCfg eraseStigCfg; /*!< Configuration for STIG erase operations */
    FlashRegister exitStigCfg[3];   /*!< Register operations to exit STIG mode */
    FlashPollingCfg pollingCfg;     /*!< Configuration for status polling */
    size_t sectorSize;              /*!< Size of a flash sector in bytes */
    size_t verifyBufSize;           /*!< Size of verification buffer in bytes */
} FlashType;

/*!
 *  @brief Hardware attributes structure for the XMEMWFF3 driver
 *
 *  Contains hardware-specific configuration for the XMEMWFF3 driver
 *  that doesn't change during runtime.
 */

typedef struct
{
    FlashType flashType; /*!< Configuration for the specific flash memory hardware */
} XMEMWFF3_HWAttrs;

/*!
 *  @brief Runtime state object for the XMEMWFF3 driver instance
 *
 *  Maintains state information for a XMEMWFF3 driver instance
 *  including memory region parameters and access control.
 */
typedef struct
{
    bool opened;            /*!< Has this region been opened */
    uintptr_t mutexKey;     /*!< Store the mutex key */
    size_t regionBase;      /*!< Offset from base of Ext flash - fetched during init() */
    size_t regionStartAddr; /*!< The regionBase translated to logical address - fetched during init() */
    size_t regionSize;      /*!< The size of the region in bytes - fetched during init() */
    XMEM_MemType deviceNum; /*!< XMEM_MEM_FLASH / XMEM_MEM_PSRAM. XMEM_MEM_INTERNAL is not supported. */
} XMEMWFF3_Object;

/*!
 *  @brief      XMEM attributes
 *
 *  The address of an XMEM_Attrs structure is passed to #XMEMWFF3_getAttrs().
 *
 *  @sa     #XMEMWFF3_getAttrs()
 */
typedef struct
{
    FlashType flashType; /*!< Configuration for the specific flash memory hardware */
} XMEM_Attrs;

/*!
 *  @brief      A handle that is returned from the #XMEMWFF3_open() call.
 */
typedef struct XMEM_Config_ *XMEM_Handle;

/*!
 *  @brief  XMEM Global configuration
 *
 *  The XMEM_Config structure contains a set of pointers used to characterize
 *  the XMEM driver implementation.
 *
 *  This structure needs to be defined before calling #XMEMWFF3_init() and it must
 *  not be changed thereafter.
 *
 *  @sa     #XMEMWFF3_init()
 */
typedef struct XMEM_Config_
{
    /*! Pointer to a driver specific data object */
    void *object;

    /*! Pointer to a driver specific hardware attributes structure */
    const void *hwAttrs;
} XMEM_Config;

/*!
 *  @brief  Parameters for opening an XMEM region
 *
 *  This structure defines the parameters used when opening an XMEM region
 *  with #XMEMWFF3_open(). It specifies the region's location, size, and
 *  the associated hardware device.
 */
typedef struct
{
    size_t regionBase;      /*!< physical Offset from base of Ext flash*/
    size_t regionStartAddr; /*!< The regionBase translated to logical address*/
    size_t regionSize;      /*!< The size of the region in bytes*/
    XMEM_MemType deviceNum; /*!< XMEM_MEM_FLASH / XMEM_MEM_PSRAM. XMEM_MEM_INTERNAL is not supported. */
} XMEM_Params;

/*!
 *  @brief  External flash device type identifiers
 *
 *  This enumeration defines identifiers for supported external flash memory devices.
 *  These values are used to select the appropriate flash device configuration and
 *  command sequences for memory operations.
 */
typedef enum
{
    IS25WJ032F  = 0x00, /* SUPPORTED */
    IS25WJ064F  = 0x01, /* SUPPORTED */
    W25Q32JW    = 0x02, /* SUPPORTED */
    W25Q64JW    = 0x03, /* SUPPORTED */
    GD25LF32E   = 0x04, /* SUPPORTED */
    GD25LF64E   = 0x05, /* SUPPORTED */
    PY25Q32LB   = 0x06, /* SUPPORTED */
    PY25Q64LB   = 0x07, /* SUPPORTED */
    PY25Q128LA  = 0x08, /* SUPPORTED */
    PY25Q256LC  = 0x09, /* SUPPORTED */
    MX25U3235F  = 0x0A, /* SUPPORTED */
    MX25U6435F  = 0x0B, /* SUPPORTED */
    IS25WJ128F  = 0x0C, /* SUPPORTED */
    W25Q12PW    = 0x0D, /* SUPPORTED */
    W25Q33PW    = 0x0E, /* SUPPORTED */
    W25Q64PW    = 0x0F, /* SUPPORTED */
    W25Q25PW    = 0x10,
    IS25WP256D  = 0x11,
    GD25LE32E   = 0x12,
    GD25LE64E   = 0x13,
    MX25U3232F  = 0x14,
    MX25U6432F  = 0x15,
    MX25U12843G = 0x16, /* SUPPORTED */
    BY25FQ256EL = 0x17,
    XM25LU32C   = 0x18,
    XM25LU64C   = 0x19,

    CUSTOM1 = 0xF0,
    CUSTOM2 = 0xF1,
    CUSTOM3 = 0xF2,
    CUSTOM4 = 0xF3,

    FLASH_NOT_DETECTED = 0xFF
} XMEM_Flash_Idx;

/*!
 *  @brief  Function to close an #XMEM_Handle.
 *
 *  @param  handle      A handle returned from #XMEMWFF3_open()
 *
 *  @retval  #XMEM_STATUS_SUCCESS         Success.
 *  @retval  #XMEM_STATUS_INVALID_PARAMS  If handle is NULL.
 *
 *  @sa     #XMEMWFF3_open()
 */
int_fast16_t XMEMWFF3_close(XMEM_Handle handle);

/*!
 *  @brief  Erase @p size bytes of the region beginning at @p offset bytes
 *  from the base of the region referenced by the #XMEM_Handle.
 *
 *  @pre    Calling context: Task only. This function can not be called from a
 *          critical section - interrupts must be enabled.
 *
 *  @param   handle     A handle returned from #XMEMWFF3_open()
 *
 *  @param   offset     The byte offset into the XMEM region to start
 *                      erasing from (must be erase sector aligned)
 *
 *  @param   size       The number of bytes to erase (must be integer
 *                      multiple of sector size)
 *
 *  @retval  #XMEM_STATUS_SUCCESS         Success.
 *  @retval  #XMEM_STATUS_INV_ALIGNMENT   If @p offset is not aligned on
 *                                       a sector boundary
 *  @retval  #XMEM_STATUS_INV_OFFSET      If @p offset exceeds region size
 *  @retval  #XMEM_STATUS_INV_SIZE        If @p size or @p offset + @p size
 *                                       exceeds region size, or if @p size
 *                                       is not an integer multiple of
 *                                       the flash sector size.
 *  @retval  #XMEM_STATUS_ERROR           If an internal error occurred
 *                                       erasing the flash.
 *
 *  @note   This API is blocking, and will block indefinitely until a shared
 *          mutex is acquired.
 *
 *  @warning Erasing internal flash on most devices can introduce
 *  significant interrupt latencies while the erase operation is in
 *  in progress. The user may want to surround certain real-time
 *  critical code sections with #XMEMWFF3_lock() and #XMEMWFF3_unlock() calls in order
 *  to prevent uncoordinated flash erase operations from negatively
 *  impacting performance.
 */
int_fast16_t XMEMWFF3_erase(XMEM_Handle handle, size_t offset, size_t size);

/*!
 *  @brief  Function to get the XMEM attributes
 *
 *  This function will populate a #XMEM_Attrs structure with attributes
 *  specific to the memory region associated with the #XMEM_Handle.
 *
 *  @param  handle      A handle returned from #XMEMWFF3_open()
 *
 *  @param  attrs       Location to store attributes.
 */
void XMEMWFF3_getAttrs(XMEM_Handle handle, XMEM_Attrs *attrs);

/*!
*  @brief  Function to get the XMEM object

*  This function will populate an #XMEMWFF3_Object structure with the object
*  data specific to the memory region associated with the #XMEM_Handle.
*
*  @param  handle      A handle returned from #XMEMWFF3_open()
*
*  @param  object      Location to store the XMEMWFF3 object.
*/
void XMEMWFF3_getObject(XMEM_Handle handle, XMEMWFF3_Object *object);

/*!
 *  @brief  Function to get the number of active XMEM handlers
 *
 *  This function will return the count of active handlers that have been
 *  opened using the #XMEMWFF3_open() function and not yet closed.
 *
 *  @return  The number of currently active XMEM handlers.
 */
uint8_t XMEMWFF3_getActiveHandlers(void);

/*!
 *  @brief  Function to initialize the XMEM module
 *
 *  @pre    The XMEM_config structure must exist and be persistent before this
 *          function can be called. This function must also be called before
 *          any other XMEM APIs.
 */
void XMEMWFF3_init(void);

/*!
 *  @brief  Function to lock the XMEM driver
 *
 *  This function is provided in the event that the user needs to
 *  perform some flash related operation not provided by the XMEM
 *  driver API set or if the user simply needs to block flash operations
 *  for a period of time.
 *
 *  For example, the interrupt latency introduced
 *  by an uncoordinated flash write operation could interfere with some
 *  critical operation being performed by the application.
 *
 *  #XMEMWFF3_lock() prevents any other thread from initiating
 *  read, write, or erase operations while the user is performing an
 *  operation which is incompatible with those functions.
 *
 *  When the application no longer needs to block flash operations by
 *  other threads, #XMEMWFF3_unlock() must be called to allow XMEM write or erase
 *  APIs to complete.
 *
 *  @pre    Calling context: Task only. This function can not be called from a
 *          critical section - interrupts must be enabled.
 *
 *  @param  handle      A handle returned from #XMEMWFF3_open()
 *
 *  @param  timeout     Not used.
 *
 *
 *  @retval  #XMEM_STATUS_SUCCESS         Success.
 *
 *  @note   This API is blocking, and will block indefinitely until a shared
 *          mutex is acquired.
 */
int_fast16_t XMEMWFF3_lock(XMEM_Handle handle, uint32_t timeout);

/*!
 *  @brief  Open an XMEM region for reading and writing.
 *
 *  @pre    Calling context: Task only. This function can not be called from a
 *          critical section - interrupts must be enabled.
 *          #XMEMWFF3_init() must have been called first.
 *
 *  @param  params   Pointer to a parameter block.
 *                   Parameters muse be initialized before
 *                   calling #XMEMWFF3_open()
 *
 *  @note   This API is blocking, and will block indefinitely until a shared
 *          mutex is acquired.
 *
 *  @return  A non-zero handle on success, else NULL.
 */
XMEM_Handle XMEMWFF3_open(XMEM_Params *params);

/*!
 *  @brief   Read data from the XMEM region associated with the #XMEM_Handle.
 *
 *  @pre    Calling context: Task only. This function can not be called from a
 *          critical section - interrupts must be enabled.
 *
 *  @param   handle     A handle returned from #XMEMWFF3_open()
 *
 *  @param   offset     The byte offset into the XMEM region to start
 *                      reading from.
 *                      Note: When using STIG mode, the offset + word size
 *                      must not cross page boundaries (256 bytes). Operations
 *                      that would exceed the current page will return an error.
 *
 *  @param   buffer     A buffer to copy the data to.
 *                      For flash reads, the buffer may reside in internal RAM
 *                      (TCM_DRAM or DRAM) or external PSRAM. Flash data is always
 *                      read into an internal 256-byte intermediate buffer first,
 *                      then copied to @p buffer in 256-byte chunks with alignment
 *                      handling, so PSRAM destinations are supported.
 *
 *  @param   bufferSize The size of the buffer (number of bytes to read).
 *           If #XMEM_READ_STIG flash is on, and bufferSize is higher than 4 (one word),
 *           only the first 4 bytes will be read.
 *           If #XMEM_READ_STIG flash is on, bufferSize is not allowed to be lower than 4 (one word).
 *
 *  @param   flags      Read flags (#XMEM_READ_STIG)
 *
 *  @retval  #XMEM_STATUS_SUCCESS     Success.
 *  @retval  #XMEM_STATUS_INV_OFFSET  If @p offset + @p size exceed the size
 *                                    of the region.
 *  @retval  #XMEM_STATUS_ERROR       If #XMEM_READ_STIG flash is on and bufferSize is lower than 4 (one word).
 *                                    If the internal read STIG operation is failed.
 *  @retval  #XMEM_STATUS_INVALID_PARAMS  If flags contain disallowed bits.
 *
 *  @note   This API is blocking, and will block indefinitely until a shared
 *          mutex is acquired.
 */
int_fast16_t XMEMWFF3_read(XMEM_Handle handle, size_t offset, void *buffer, size_t bufferSize, uint_fast16_t flags);

/*!
 *  @brief  Function to unlock the XMEM driver
 *
 *  This function allows XMEM write and erase operations to proceed after being
 *  temporarily inhibited by a call to #XMEMWFF3_lock().
 *
 *  @pre    Calling context: Task only. This function can not be called from a
 *          critical section - interrupts must be enabled.
 *
 *  @param  handle      A handle returned from #XMEMWFF3_open()
 */
void XMEMWFF3_unlock(XMEM_Handle handle);

/*!
 *  @brief   Write data to the XMEM region associated with the #XMEM_Handle.
 *
 *  @pre    Calling context: Task only. This function can not be called from a
 *          critical section - interrupts must be enabled.
 *
 *  @param   handle     A handle returned from #XMEMWFF3_open()
 *
 *  @param   offset     The byte offset into the XMEM region to start
 *                      writing.
 *                      Note: When using STIG mode, the offset + word size
 *                      must not cross page boundaries (256 bytes). Operations
 *                      that would exceed the current page will return an error.
 *
 *  @param   buffer     A buffer containing data to write to the XMEM region.
 *                      The buffer may reside in internal RAM (TCM_DRAM or DRAM) or
 *                      external PSRAM. For flash writes, data is always copied from
 *                      @p buffer into an internal 256-byte intermediate buffer first,
 *                      then written to flash, so PSRAM source buffers are supported.
 *
 *  @param   bufferSize The size of the buffer (number of bytes to write).
 *           If #XMEM_WRITE_STIG flash is on, and bufferSize is higher than 4 (one word),
 *           only the first 4 bytes will be write.
 *           If #XMEM_WRITE_STIG flash is on, bufferSize is not allowed to be lower than 4 (one word).
 *
 *  @param   flags      Write flags (#XMEM_WRITE_ERASE, #XMEM_WRITE_PRE_VERIFY,
 *                      #XMEM_WRITE_POST_VERIFY, #XMEM_WRITE_STIG).
 *
 *  @retval  #XMEM_STATUS_SUCCESS       Success.
 *  @retval  #XMEM_STATUS_ERROR         If the internal flash write operation
 *                                      failed, or if #XMEM_WRITE_POST_VERIFY
 *                                      was requested and the destination flash
 *                                      range does not match the source
 *                                      @p buffer data.
 *  @retval  #XMEM_STATUS_INV_OFFSET     If @p offset + @p size exceed the size
 *                                      of the region.
 *  @retval  #XMEM_STATUS_INV_WRITE      If #XMEM_WRITE_PRE_VERIFY is requested
 *                                      and the destination flash address range
 *                                      cannot be change to the values desired.
 *  @retval  #XMEM_STATUS_INV_ALIGNMENT  If #XMEM_WRITE_ERASE is requested
 *                                      and @p offset is not aligned on
 *                                      a sector boundary
 *  @retval  #XMEM_STATUS_VERIFYBUFFER   If #XMEM_WRITE_PRE_VERIFY or #XMEM_WRITE_POST_VERIFY
 *                                      is requested but the verification buffer has not
 *                                      been configured.
 *
 *  @retval  #XMEM_STATUS_INVALID_PARAMS  If flags contain disallowed bits.
 *
 *  @note   This API is blocking, and will block indefinitely until a shared
 *          mutex is acquired. This call may lock a region to ensure atomic access to the region.
 *
 *  @warning Writing to internal flash on most devices can introduce
 *  significant interrupt latencies while the write operation is in
 *  in progress. The user may want to surround certain real-time
 *  critical code sections with #XMEMWFF3_lock() and #XMEMWFF3_unlock() calls in order
 *  to prevent uncoordinated flash write operations from negatively
 *  impacting performance.
 */
int_fast16_t XMEMWFF3_write(XMEM_Handle handle, size_t offset, void *buffer, size_t bufferSize, uint_fast16_t flags);

/*!
 *  @brief  Determine the memory type of a given address.
 *
 *  This function maps an address to an #XMEM_MemType value by checking
 *  whether the address falls within the external PSRAM, external flash,
 *  or internal memory address ranges.
 *
 *  @param  addr  The address to classify.
 *
 *  @return  #XMEM_MEM_PSRAM    If @p addr is in the external PSRAM range.
 *  @return  #XMEM_MEM_FLASH    If @p addr is in the external flash range.
 *  @return  #XMEM_MEM_INTERNAL If @p addr is not in any external memory range.
 */
XMEM_MemType XMEMWFF3_addrToType(uintptr_t addr);

/*!
 *  @brief  Check whether an address resides in external memory.
 *
 *  This function returns @p true if @p addr maps to external PSRAM or
 *  external flash, and @p false if it maps to internal memory.
 *
 *  @param  addr  The address to check.
 *
 *  @return  @p true   If @p addr is in external memory.
 *  @return  @p false  If @p addr is in internal memory.
 *
 *  @sa  #XMEMWFF3_addrToType()
 */
bool XMEMWFF3_isAddrExternal(uintptr_t addr);

/*!
 *  @brief  Convert an address to a byte offset within its memory region.
 *
 *  Given an address, this function computes the byte offset from the base of
 *  that region.
 *
 *  @param  addr  The address to convert.
 *
 *  @return  The byte offset of @p addr from the base of the specified
 *           memory region.
 */
size_t XMEMWFF3_addrToOffset(uintptr_t addr);

#if defined(__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ti_drivers_xmem_XMEMWFF3__include */
