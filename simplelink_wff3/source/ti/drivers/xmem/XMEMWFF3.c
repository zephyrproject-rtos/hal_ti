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
 *  ========== XSPIWFF3.c ==========
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/MutexP.h>
#include <ti/drivers/dpl/ClockP.h>

#include <ti/drivers/xmem/XMEMWFF3.h>
#include <ti/drivers/xmem/flash/FlashWFF3.h>
#include <ti/drivers/utils/Math.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/dcache.h)

#define PHY_OFFSET             12
#define PHYSICAL_ADDR          0
#define LOGIC_ADDR             1
#define VERIFBUF_SIZE_IN_BYTES 256
#define WRITE_SIZE_IN_BYTES    256
#define READ_SIZE_IN_BYTES     256
#define PAGE_SIZE              0x100

static int_fast16_t checkEraseRange(XMEM_Handle handle, size_t offset, size_t size);
static int_fast16_t doErase(XMEM_Handle handle, size_t offset, size_t size);
static uint32_t ConvertOffsetToAddr(XMEM_Handle handle, size_t offset, size_t AddrType);
static void flashTypeSelection(void);

const uint8_t XMEM_count = XMEM_NUM_HANDLER;
/* xmem_num, writeMutex, writeMutexStruct, isInitialized must be in TCM_DRAM:
 * they are accessed by XMEMWFF3_init/open/lock/unlock which can be called
 * from within the PS_RAM-inaccessible window (OTFDE disabled / OSPI in
 * flash mode).
 */
static uint8_t xmem_num __attribute__((section(".internalRAM.bss")));
static MutexP_Handle writeMutex __attribute__((section(".internalRAM.bss")));
static MutexP_Struct writeMutexStruct __attribute__((section(".internalRAM.bss")));

/* These variables are accessed inside the PS_RAM-inaccessible window
 * (between FlashStigPreConfigOp and FlashStigPostConfigOp).
 * Place them in .internalRAM (DRAM) so they remain reachable when PS_RAM
 * is offline (OTFDE disabled / OSPI in flash mode).
 */
static size_t sectorBaseMask __attribute__((section(".internalRAM.bss")));
static void *verifyBuf __attribute__((section(".internalRAM.bss")));
__attribute__((section(".internalRAM.bss"), aligned(4))) static uint8_t verifyBuffer[VERIFBUF_SIZE_IN_BYTES];
static void *xmemDataToWriteBuf __attribute__((section(".internalRAM.bss")));
__attribute__((section(".internalRAM.bss"),
               aligned(4))) static uint8_t xmemDataToWriteBuffer[WRITE_SIZE_IN_BYTES + 4]; /*!<
                                                                                            * handling
                                                                                            * unaligned
                                                                                            * write
                                                                                            */
static void *xmemDataToReadBuf __attribute__((section(".internalRAM.bss")));
__attribute__((section(".internalRAM.bss"),
               aligned(4))) static uint8_t xmemDataToReadBuffer[READ_SIZE_IN_BYTES + 4]; /*!< handling
                                                                                          * unaligned
                                                                                          * read
                                                                                          */

extern uint8_t _Boot_report_address[];
#define BOOT_REPORT_ADDR ((uint32_t)(_Boot_report_address))

static bool isInitialized __attribute__((section(".internalRAM.data"))) = false;

__attribute__((section(".internalRAM.bss"))) XMEMWFF3_HWAttrs XMEMWFF3_hwAttrs;

__attribute__((section(".internalRAM.bss"))) XMEMWFF3_Object XMEMWFF3_objects[XMEM_NUM_HANDLER];

XMEM_Config XMEM_config[CONFIG_XMEM_COUNT] = {{.object = &(XMEMWFF3_objects), .hwAttrs = &(XMEMWFF3_hwAttrs)}};

/* Flush D-Cache before FlashRead (PSRAM only).
 * Caller must wrap with HwiP_disable/HwiP_restore.
 */
#define XMEM_CACHE_FLUSH_IF_PSRAM(obj)          \
    do                                          \
    {                                           \
        if ((obj)->deviceNum == XMEM_MEM_PSRAM) \
        {                                       \
            DCacheFlush();                      \
        }                                       \
    } while (0)

/* Invalidate D-Cache after FlashWrite (PSRAM only).
 * Caller must wrap with HwiP_disable/HwiP_restore.
 */
#define XMEM_CACHE_INVALIDATE_IF_PSRAM(obj)     \
    do                                          \
    {                                           \
        if ((obj)->deviceNum == XMEM_MEM_PSRAM) \
        {                                       \
            DCacheInvalidate();                 \
        }                                       \
    } while (0)

/* Flush + Disable D-Cache before FlashWrite (PSRAM only).
 * Caller must wrap with HwiP_disable/HwiP_restore.
 */
#define XMEM_CACHE_FLUSH_DISABLE_FOR_WRITE_IF_PSRAM(obj) \
    do                                                   \
    {                                                    \
        if ((obj)->deviceNum == XMEM_MEM_PSRAM)          \
        {                                                \
            DCacheFlush();                               \
            DCacheDisable();                             \
        }                                                \
    } while (0)

/* Enable + Invalidate D-Cache after FlashWrite (PSRAM only).
 * Caller must wrap with HwiP_disable/HwiP_restore.
 */
#define XMEM_CACHE_INVALIDATE_ENABLE_IF_PSRAM(obj) \
    do                                             \
    {                                              \
        if ((obj)->deviceNum == XMEM_MEM_PSRAM)    \
        {                                          \
            DCacheEnable();                        \
            DCacheInvalidate();                    \
        }                                          \
    } while (0)

/*
 *  ======== XMEMWFF3_close ========
 */
int_fast16_t XMEMWFF3_close(XMEM_Handle handle)
{
    if (handle == NULL)
    {
        return XMEM_STATUS_INVALID_PARAMS;
    }

    XMEMWFF3_Object *object;

    uintptr_t key = MutexP_lock(writeMutex);

    object = handle->object;
    memset(object, 0, sizeof(XMEMWFF3_Object));

    free(handle);

    xmem_num--;

    MutexP_unlock(writeMutex, key);

    return XMEM_STATUS_SUCCESS;
}

/*
 *  ======== XMEMWFF3_erase ========
 */
int_fast16_t XMEMWFF3_erase(XMEM_Handle handle, size_t offset, size_t size)
{
    int_fast16_t status;

    if (handle == NULL)
    {
        return (XMEM_STATUS_ERROR);
    }

    XMEMWFF3_Object const *object;

    object = handle->object;

    /* STIG operation are not supported for PSRAM */
    if (object->deviceNum == XMEM_MEM_PSRAM)
    {
        return XMEM_STATUS_ERROR;
    }

    uintptr_t key = MutexP_lock(writeMutex);

    status = doErase(handle, offset, size);

    MutexP_unlock(writeMutex, key);

    return (status);
}

/*
 *  ======== XMEMWFF3_getAttrs ========
 */
void XMEMWFF3_getAttrs(XMEM_Handle handle, XMEM_Attrs *attrs)
{
    if (handle == NULL || attrs == NULL)
    {
        return;
    }

    XMEMWFF3_HWAttrs const *hwAttrs;

    hwAttrs = handle->hwAttrs;

    attrs->flashType = hwAttrs->flashType;
}

/*
 *  ======== XMEMWFF3_getObject ========
 */
void XMEMWFF3_getObject(XMEM_Handle handle, XMEMWFF3_Object *object)
{
    if (handle == NULL || object == NULL)
    {
        return;
    }

    XMEMWFF3_Object const *obj;

    obj = handle->object;

    memcpy(object, obj, sizeof(XMEMWFF3_Object));
}

/*
 *  ======== XMEMWFF3_getActiveHandlers ========
 */
uint8_t XMEMWFF3_getActiveHandlers(void)
{
    return xmem_num;
}

/*
 *  ======== XMEMWFF3_init ========
 */
void XMEMWFF3_init(void)
{
    uintptr_t key;
    MutexP_Params mutexParams;

    key = HwiP_disable();

    if (!isInitialized)
    {
        isInitialized = true;
        HwiP_restore(key);

        /* Initialize variables */
        verifyBuf = (void *)&verifyBuffer;

        /* Select flash type */
        flashTypeSelection();

        /* Create a mutex for thread safety */
        MutexP_Params_init(&mutexParams);
        writeMutex = MutexP_construct(&writeMutexStruct, &mutexParams);
    }
    else
    {
        /* Already initialized */
        HwiP_restore(key);
    }
}

/*
 *  ======== XMEMWFF3_lock =======
 */
int_fast16_t XMEMWFF3_lock(XMEM_Handle handle, uint32_t timeout)
{
    if (handle == NULL)
    {
        return (XMEM_STATUS_ERROR);
    }

    XMEMWFF3_Object *object = handle->object;
    object->mutexKey        = MutexP_lock(writeMutex);
    if (object->mutexKey == 0)
    {
        return (XMEM_STATUS_TIMEOUT);
    }

    return (XMEM_STATUS_SUCCESS);
}

/*
 *  ======== XMEMWFF3_open =======
 */
XMEM_Handle XMEMWFF3_open(XMEM_Params *params)
{
    XMEMWFF3_Object *object;
    const XMEMWFF3_HWAttrs *hwAttrs;
    XMEM_Handle handle = NULL;
    int i;

    if (params == NULL)
    {
        return (NULL);
    }

    XMEMWFF3_init();
    /* Confirm that 'init' has successfully completed */
    if (writeMutex == NULL)
    {
        return (NULL);
    }

    /* Verify max number of handlers */
    if (xmem_num >= XMEM_count)
    {
        return (NULL);
    }

    uintptr_t key = MutexP_lock(writeMutex);

    /* Allocate XMEM handle */
    handle = malloc(sizeof(XMEM_Config));
    if (handle == NULL)
    {
        MutexP_unlock(writeMutex, key);
        return (NULL);
    }

    /* Pointing to hwAttrs*/
    handle->hwAttrs = XMEM_config[0].hwAttrs;

    /* Pointing to the beginning of array of objects */
    object = (XMEMWFF3_Object *)(XMEM_config[0].object);

    /* Check for available slot */
    for (i = 0; i < XMEM_count; i++)
    {
        /* Check if current object slot is available (not opened) */
        if (false == object->opened)
        {
            break;
        }

        /* Ther is not available slot */
        if (i == XMEM_count - 1)
        {
            free(handle);
            MutexP_unlock(writeMutex, key);
            return (NULL);
        }

        /* Current object is opened, move to the next object in the array */
        object = object + 1;
    }

    hwAttrs = handle->hwAttrs;

    object->deviceNum       = params->deviceNum;
    object->regionBase      = params->regionBase;
    object->regionStartAddr = params->regionStartAddr;
    object->regionSize      = params->regionSize;

    sectorBaseMask = ~(hwAttrs->flashType.sectorSize - 1);

    /* The region cannot be smaller than a sector size */
    if (object->regionSize < hwAttrs->flashType.sectorSize)
    {
        memset(object, 0, sizeof(XMEMWFF3_Object));
        free(handle);
        MutexP_unlock(writeMutex, key);
        return (NULL);
    }

    /* The region size must be a multiple of sector size */
    if (object->regionSize != (object->regionSize & sectorBaseMask))
    {
        memset(object, 0, sizeof(XMEMWFF3_Object));
        free(handle);
        MutexP_unlock(writeMutex, key);
        return (NULL);
    }

    /* Validate target device */
    if (object->deviceNum != XMEM_MEM_FLASH && object->deviceNum != XMEM_MEM_PSRAM)
    {
        memset(object, 0, sizeof(XMEMWFF3_Object));
        free(handle);
        MutexP_unlock(writeMutex, key);
        return (NULL);
    }

    object->opened = true;

    /* object is ready, handle points to a found object */
    handle->object = object;

    xmem_num++;

    MutexP_unlock(writeMutex, key);

    return (handle);
}

/*
 *  ======== XMEMWFF3_read =======
 */
int_fast16_t XMEMWFF3_read(XMEM_Handle handle, size_t offset, void *buffer, size_t bufferSize, uint_fast16_t flags)
{
    uint32_t clockPTickPeriod;
    unsigned int key;

    if (handle == NULL || buffer == NULL || bufferSize == 0)
    {
        return (XMEM_STATUS_ERROR);
    }

    /* Validate that flags only contain allowed bits */
    if (flags & ~(XMEM_READ_STIG))
    {
        return (XMEM_STATUS_INVALID_PARAMS);
    }

    XMEMWFF3_Object const *object;

    object = handle->object;

    /* Prepare Read buffer */
    xmemDataToReadBuf = (void *)&xmemDataToReadBuffer;

    if (flags & XMEM_READ_STIG)
    {
        /* STIG operation are not supported for PSRAM */
        if (object->deviceNum == XMEM_MEM_PSRAM)
        {
            return XMEM_STATUS_ERROR;
        }

        /*  Check if offset + word size exceeds page boundary */
        if (((offset & 0xFF) + XMEM_WORD_SIZE) > PAGE_SIZE)
        {
            return XMEM_STATUS_ERROR;
        }

        uint32_t status = 0;

        uint32_t startAddrPhy = ConvertOffsetToAddr(handle, offset, PHYSICAL_ADDR);

        if (bufferSize < XMEM_WORD_SIZE)
        {
            return XMEM_STATUS_ERROR;
        }
        else
        {
            bufferSize = XMEM_WORD_SIZE; /* length of reading from STIG is always 1 word which is 4 Bytes */
        }

        if (offset + bufferSize > object->regionSize)
        {
            return (XMEM_STATUS_INV_OFFSET);
        }

        /*
         *  Get exclusive access to the region.  We don't want someone
         *  else to erase the region while we are reading it.
         */
        uintptr_t mutexKey = MutexP_lock(writeMutex);

        key = HwiP_disable();

        /*
         * Ensure SysTimer is enabled, to be able to read the SysTimer counter
         * value.
         */

        clockPTickPeriod = ClockP_getSystemTickPeriod();
        FlashSetTickPeriod(clockPTickPeriod);

        status = FlashReadSTIG(startAddrPhy, xmemDataToReadBuf, object->deviceNum);

        /* Copy data to buffer */
        memcpy(buffer, xmemDataToReadBuf, XMEM_WORD_SIZE);

        HwiP_restore(key);

        if (status != 0)
        {
            MutexP_unlock(writeMutex, mutexKey);
            return XMEM_STATUS_ERROR;
        }

        MutexP_unlock(writeMutex, mutexKey);
    }
    else
    {
        if (offset + bufferSize > object->regionSize)
        {
            return (XMEM_STATUS_INV_OFFSET);
        }

        /*
         *  Get exclusive access to the region.  We don't want someone
         *  else to erase the region while we are reading it.
         */
        uintptr_t mutexKey = MutexP_lock(writeMutex);

        /* PSRAM: Check if both src (RAM buffer) and dst (PSRAM) are 4-byte aligned */
        if (object->deviceNum == XMEM_MEM_PSRAM)
        {
            uint32_t psramAddr = ConvertOffsetToAddr(handle, offset, LOGIC_ADDR);

            /* PSRAM destination buffer: DMA cannot do PSRAM-to-PSRAM, use memcpy directly */
            if (XMEMWFF3_addrToType((uintptr_t)buffer) == XMEM_MEM_PSRAM)
            {
                memcpy(buffer, (void *)psramAddr, bufferSize);
                MutexP_unlock(writeMutex, mutexKey);
                return (XMEM_STATUS_SUCCESS);
            }

            uint32_t psramAlignment = psramAddr & 0x3;
            uint32_t bufAlignment   = (uint32_t)(uintptr_t)buffer & 0x3;

            /* If both are 4-byte aligned (or can be aligned together), use simple DMA approach */
            if (psramAlignment == bufAlignment)
            {
                int remainingBytes = bufferSize;

                /* Handle head: align to 4-byte boundary with memcpy */
                if (psramAlignment != 0)
                {
                    size_t headBytes = 4 - psramAlignment;
                    if (headBytes > remainingBytes)
                    {
                        headBytes = remainingBytes;
                    }
                    memcpy(buffer, (void *)psramAddr, headBytes);
                    buffer += headBytes;
                    psramAddr += headBytes;
                    remainingBytes -= headBytes;
                }

                /* Now both are 4-byte aligned - use DMA for the rest */
                if (remainingBytes >= 4)
                {
                    /* Round down to multiple of 4 for DMA */
                    size_t dmaBytes = remainingBytes & ~0x3;

                    uintptr_t readCacheKey = HwiP_disable();
                    XMEM_CACHE_FLUSH_IF_PSRAM(object);

                    /* Read from psram to the buffer */
                    FlashRead((uint32_t *)psramAddr, (uint32_t *)buffer, dmaBytes);

                    HwiP_restore(readCacheKey);

                    buffer += dmaBytes;
                    psramAddr += dmaBytes;
                    remainingBytes -= dmaBytes;
                }

                /* Handle tail with memcpy (0-3 bytes) */
                if (remainingBytes > 0)
                {
                    memcpy(buffer, (void *)psramAddr, remainingBytes);
                }

                MutexP_unlock(writeMutex, mutexKey);
                return (XMEM_STATUS_SUCCESS);
            }

            /* Alignments differ - use read-modify-write with 256-byte pages */
            int remainingBytes = bufferSize;
            uint32_t psramlogicAddr;
            uint32_t alignment;

            /* Handling the constraint of reading from 4 Bytes aligned address */
            alignment = offset % 4;

            /* Handle the constraint of reading multiples of 256 Bytes at a time. */
            while (remainingBytes >= READ_SIZE_IN_BYTES)
            {
                /* Set address to read from - align to 256-byte boundary */
                psramlogicAddr = ConvertOffsetToAddr(handle, offset, LOGIC_ADDR) - alignment;

                uintptr_t readCacheKey = HwiP_disable();
                XMEM_CACHE_FLUSH_IF_PSRAM(object);

                /* Read from PSRAM into intermediate buffer */
                FlashRead((uint32_t *)psramlogicAddr, (uint32_t *)xmemDataToReadBuf, READ_SIZE_IN_BYTES);

                HwiP_restore(readCacheKey);

                /* Copy data to user buffer */
                memcpy(buffer, xmemDataToReadBuf + alignment, READ_SIZE_IN_BYTES - alignment);

                buffer += READ_SIZE_IN_BYTES - alignment;
                remainingBytes -= (READ_SIZE_IN_BYTES - alignment);
                offset += READ_SIZE_IN_BYTES - alignment;
                alignment = 0;
            }

            /* Less than 256-bytes remaining */
            if (remainingBytes > 0)
            {
                if (offset + READ_SIZE_IN_BYTES > object->regionSize)
                {
                    alignment = offset & 0xFF;
                }

                psramlogicAddr = ConvertOffsetToAddr(handle, offset, LOGIC_ADDR) - alignment;

                uintptr_t readCacheKey = HwiP_disable();
                XMEM_CACHE_FLUSH_IF_PSRAM(object);

                if ((alignment + remainingBytes) > READ_SIZE_IN_BYTES)
                {
                    size_t firstReadSize = READ_SIZE_IN_BYTES - alignment;

                    FlashRead((uint32_t *)psramlogicAddr, (uint32_t *)xmemDataToReadBuf, READ_SIZE_IN_BYTES);
                    memcpy(buffer, xmemDataToReadBuf + alignment, firstReadSize);

                    uint8_t *nextBuffer = (uint8_t *)buffer + firstReadSize;
                    size_t nextSize     = remainingBytes - firstReadSize;
                    uint32_t nextAddr   = (uint32_t)psramlogicAddr + READ_SIZE_IN_BYTES;

                    FlashRead((uint32_t *)nextAddr, (uint32_t *)xmemDataToReadBuf, READ_SIZE_IN_BYTES);
                    memcpy((uint8_t *)nextBuffer, xmemDataToReadBuf, nextSize);
                }
                else
                {
                    FlashRead((uint32_t *)psramlogicAddr, (uint32_t *)xmemDataToReadBuf, READ_SIZE_IN_BYTES);
                    memcpy(buffer, xmemDataToReadBuf + alignment, remainingBytes);
                }
                HwiP_restore(readCacheKey);
            }

            MutexP_unlock(writeMutex, mutexKey);
            return (XMEM_STATUS_SUCCESS);
        }

        /* Flash: Original complex 256-byte aligned logic */
        int remainingBytes = bufferSize;
        uint32_t flashlogicAddr;
        uint32_t alignment;

        /* Handling the constraint of reading from 4 Bytes aligned address */
        alignment = offset % 4;

        /* Handle the constraint of reading multiples of 256 Bytes at a time. */
        while (remainingBytes >= READ_SIZE_IN_BYTES)
        {
            /* Set address to read from
             * If offset is not align, set the address to be align*/
            flashlogicAddr = ConvertOffsetToAddr(handle, offset, LOGIC_ADDR) - alignment;

            /* Read from flash
             * flashlogicAddr is align, read 256 bytes*/
            FlashRead((uint32_t *)flashlogicAddr, (uint32_t *)xmemDataToReadBuf, READ_SIZE_IN_BYTES);

            /* Copy data to buffer.
             * If offset is not aligned, we need to align the src address and read size*/
            memcpy(buffer, xmemDataToReadBuf + alignment, READ_SIZE_IN_BYTES - alignment);

            /* Advance buffer, subtract remain size, Advance offset */
            buffer += READ_SIZE_IN_BYTES - alignment;
            remainingBytes -= (READ_SIZE_IN_BYTES - alignment);
            offset += READ_SIZE_IN_BYTES - alignment;

            /* Now the offset is aligned, alignment should be 0 for the rest of the read loop*/
            alignment = 0;
        }

        /* Less than 256-bytes to read:
         * - Either after the loop for remaining bytes
         * - Or for first time read with less than 256-bytes length
         */
        if (remainingBytes > 0)
        {
            /* Handling the constraint of reading from addresses that exceed region size  */
            if (offset + READ_SIZE_IN_BYTES > object->regionSize)
            {
                alignment = offset & 0xFF;
            }

            /* Set address to read from
             * If offset is not align, set the address to be align*/
            flashlogicAddr = ConvertOffsetToAddr(handle, offset, LOGIC_ADDR) - alignment;

            /* Check if the true alignment + remainingBytes exceeds buffer size */
            if ((alignment + remainingBytes) > READ_SIZE_IN_BYTES)
            {
                /* Calculate how much we can read in first operation */
                size_t firstReadSize = READ_SIZE_IN_BYTES - alignment;

                /* First read operation */
                FlashRead((uint32_t *)flashlogicAddr, (uint32_t *)xmemDataToReadBuf, READ_SIZE_IN_BYTES);

                memcpy(buffer, xmemDataToReadBuf + alignment, firstReadSize);

                /* Second read operation for remaining bytes */
                uint8_t *nextBuffer = (uint8_t *)buffer + firstReadSize;
                size_t nextSize     = remainingBytes - firstReadSize;
                uint32_t nextAddr   = (uint32_t)flashlogicAddr + READ_SIZE_IN_BYTES;

                FlashRead((uint32_t *)nextAddr, (uint32_t *)xmemDataToReadBuf, READ_SIZE_IN_BYTES);

                memcpy((uint8_t *)nextBuffer, xmemDataToReadBuf, nextSize);
            }
            else
            {
                /* Read from flash
                 * flashlogicAddr is aligned, read 256 bytes.
                 */
                FlashRead((uint32_t *)flashlogicAddr, (uint32_t *)xmemDataToReadBuf, READ_SIZE_IN_BYTES);

                /* Copy data to buffer.
                 * If offset is not aligned, we need to align the src address and read size
                 */
                memcpy(buffer, xmemDataToReadBuf + alignment, remainingBytes);
            }
        }

        MutexP_unlock(writeMutex, mutexKey);
    }

    return (XMEM_STATUS_SUCCESS);
}

/*
 *  ======== XMEMWFF3_unlock =======
 */
void XMEMWFF3_unlock(XMEM_Handle handle)
{
    if (handle == NULL)
    {
        return;
    }

    XMEMWFF3_Object *object = handle->object;
    MutexP_unlock(writeMutex, object->mutexKey);
}

/*
 *  ======== XMEMWFF3_write =======
 */
int_fast16_t XMEMWFF3_write(XMEM_Handle handle, size_t offset, void *buffer, size_t bufferSize, uint_fast16_t flags)
{
    if (handle == NULL || buffer == NULL || bufferSize == 0)
    {
        return (XMEM_STATUS_ERROR);
    }

    /* Validate that flags only contain allowed bits */
    if (flags & ~(XMEM_WRITE_ERASE | XMEM_WRITE_PRE_VERIFY | XMEM_WRITE_POST_VERIFY | XMEM_WRITE_STIG))
    {
        return (XMEM_STATUS_INVALID_PARAMS);
    }

    XMEMWFF3_HWAttrs const *hwAttrs;
    XMEMWFF3_Object const *object;

    hwAttrs = handle->hwAttrs;
    object  = handle->object;

    unsigned int key;
    unsigned int size;
    uint32_t status              = 0;
    uint32_t flashlogicStartAddr = ConvertOffsetToAddr(handle, offset, LOGIC_ADDR);
    uint32_t flashlogicAddr      = flashlogicStartAddr;
    uint32_t startAddrPhy        = ConvertOffsetToAddr(handle, offset, PHYSICAL_ADDR);
    uint32_t *srcBuf, *dstBuf;
    uint8_t *_srcBuf, *_dstBuf;
    uint32_t totalSize;
    uint32_t clockPTickPeriod;
    size_t originalOffset = offset;
    void *originalBuffer  = buffer;
    int i, j;
    int retval = XMEM_STATUS_SUCCESS;

    /* Validate offset and bufferSize */
    if (offset + bufferSize > object->regionSize)
    {
        return (XMEM_STATUS_INV_OFFSET);
    }

    /* Validate buffer size for STIG write */
    if (flags & XMEM_WRITE_STIG)
    {
        /* STIG operation are not supported for PSRAM */
        if (object->deviceNum == XMEM_MEM_PSRAM)
        {
            return XMEM_STATUS_ERROR;
        }

        /*  Check if offset + word size exceeds page boundary */
        if (((offset & 0xFF) + XMEM_WORD_SIZE) > PAGE_SIZE)
        {
            return XMEM_STATUS_ERROR;
        }

        if (bufferSize < XMEM_WORD_SIZE)
        {
            return XMEM_STATUS_ERROR;
        }
        else
        {
            bufferSize = XMEM_WORD_SIZE;
        }
    }

    /* Get exclusive access to the Flash region */
    uintptr_t mutexKey = MutexP_lock(writeMutex);

    /* Prepare Write buffer */
    xmemDataToWriteBuf = (void *)&xmemDataToWriteBuffer;

    /* If erase is set, erase destination sector(s) first */
    if (flags & XMEM_WRITE_ERASE)
    {
        size = bufferSize & sectorBaseMask;
        if (bufferSize & (~sectorBaseMask))
        {
            size += hwAttrs->flashType.sectorSize;
        }

        /* Validate offset is not aligned on a sector boundary */
        if (offset != (offset & sectorBaseMask))
        {
            MutexP_unlock(writeMutex, mutexKey);
            return (XMEM_STATUS_INV_ALIGNMENT);
        }

        retval = doErase(handle, offset, size);
        if (retval != XMEM_STATUS_SUCCESS)
        {
            MutexP_unlock(writeMutex, mutexKey);
            return (retval);
        }
    }
    else if (flags & XMEM_WRITE_PRE_VERIFY)
    {
        /*
         *  If pre-verify, each destination byte must be able to be changed to the
         *  source byte (1s to 0s, not 0s to 1s).
         *  this is satisfied by the following test:
         *     src == (src & dst)
         */

        /* Validate that the verification buffer has been configured */
        if ((verifyBuf == NULL) || (hwAttrs->flashType.verifyBufSize == 0))
        {
            MutexP_unlock(writeMutex, mutexKey);
            return (XMEM_STATUS_VERIFYBUFFER);
        }

        /* Start reading from the requested start address */
        flashlogicAddr = offset;

        /* Set the number of bytes to read */
        totalSize = bufferSize;

        j = 0;
        while (totalSize > 0)
        {
            size = Math_MIN(hwAttrs->flashType.verifyBufSize, VERIFBUF_SIZE_IN_BYTES);
            size = Math_MIN(size, totalSize);

            /* Read destination before the change for pre-verify expected change */
            _dstBuf = (uint8_t *)verifyBuf;

            XMEMWFF3_read(handle, flashlogicAddr, _dstBuf, size, 0);

            _srcBuf = (uint8_t *)buffer;

            for (i = 0; i < size; i++, j++)
            {
                if (_srcBuf[j] != (_srcBuf[j] & _dstBuf[i]))
                {
                    MutexP_unlock(writeMutex, mutexKey);
                    return (XMEM_STATUS_INV_WRITE);
                }
            }

            flashlogicAddr = flashlogicAddr + size;
            totalSize      = totalSize - size;
        }
    }

    if (flags & XMEM_WRITE_STIG)
    {
        /* Copy to Write buffer */
        memcpy(xmemDataToWriteBuffer, buffer, bufferSize);

        srcBuf = (uint32_t *)xmemDataToWriteBuf;
        dstBuf = (uint32_t *)startAddrPhy;

        key = HwiP_disable();

        /*
         * Ensure SysTimer is enabled, to be able to read the SysTimer counter
         * value.
         */
        clockPTickPeriod = ClockP_getSystemTickPeriod();
        FlashSetTickPeriod(clockPTickPeriod);

        status = FlashWriteSTIG(srcBuf, dstBuf, object->deviceNum);
        HwiP_restore(key);
    }
    else
    {
        /* PSRAM: Check if both src (RAM buffer) and dst (PSRAM) are 4-byte aligned */
        if (object->deviceNum == XMEM_MEM_PSRAM)
        {
            uint32_t psramAddr = ConvertOffsetToAddr(handle, offset, LOGIC_ADDR);

            /* PSRAM source buffer: DMA cannot do PSRAM-to-PSRAM, use memcpy directly */
            if (XMEMWFF3_addrToType((uintptr_t)buffer) == XMEM_MEM_PSRAM)
            {
                memcpy((void *)psramAddr, buffer, bufferSize);
                MutexP_unlock(writeMutex, mutexKey);
                return (XMEM_STATUS_SUCCESS);
            }

            uint32_t psramAlignment = psramAddr & 0x3;
            uint32_t bufAlignment   = (uint32_t)(uintptr_t)buffer & 0x3;

            /* If both are 4-byte aligned (or can be aligned together), use simple DMA approach */
            if (psramAlignment == bufAlignment)
            {
                int remainingBytes = bufferSize;

                /* Handle head: align to 4-byte boundary with memcpy */
                if (psramAlignment != 0)
                {
                    size_t headBytes = 4 - psramAlignment;
                    if (headBytes > remainingBytes)
                    {
                        headBytes = remainingBytes;
                    }
                    /* memcpy can be used for small sizes */
                    memcpy((void *)psramAddr, buffer, headBytes);
                    buffer += headBytes;
                    psramAddr += headBytes;
                    remainingBytes -= headBytes;
                }

                /* Now both are 4-byte aligned - use DMA for the rest */
                if (remainingBytes >= 4)
                {
                    /* Round down to multiple of 4 for DMA */
                    size_t dmaBytes = remainingBytes & ~0x3;

                    uintptr_t cacheKey = HwiP_disable();
                    XMEM_CACHE_FLUSH_IF_PSRAM(object);

                    FlashWrite((uint32_t *)buffer, (uint32_t *)psramAddr, dmaBytes);

                    XMEM_CACHE_INVALIDATE_IF_PSRAM(object);
                    HwiP_restore(cacheKey);

                    buffer += dmaBytes;
                    psramAddr += dmaBytes;
                    remainingBytes -= dmaBytes;
                }

                /* Handle tail with memcpy (0-3 bytes) */
                if (remainingBytes > 0)
                {
                    memcpy((void *)psramAddr, buffer, remainingBytes);
                }

                MutexP_unlock(writeMutex, mutexKey);
                return (XMEM_STATUS_SUCCESS);
            }

            /* Alignments differ - use read-modify-write with 256-byte pages */
            srcBuf             = (uint32_t *)xmemDataToWriteBuf;
            size               = bufferSize;
            dstBuf             = (uint32_t *)flashlogicStartAddr;
            int remainingBytes = size;
            uint32_t alignment;

            alignment = offset % 4;

            /* Handle 256-byte chunks */
            while (remainingBytes >= WRITE_SIZE_IN_BYTES)
            {
                dstBuf = (uint32_t *)(ConvertOffsetToAddr(handle, offset, LOGIC_ADDR) - alignment);

                uintptr_t readCacheKey = HwiP_disable();
                XMEM_CACHE_FLUSH_IF_PSRAM(object);

                FlashRead((uint32_t *)dstBuf, (uint32_t *)srcBuf, READ_SIZE_IN_BYTES);
                memcpy((uint8_t *)srcBuf + alignment, buffer, READ_SIZE_IN_BYTES - alignment);

                FlashWrite((uint32_t *)srcBuf, (uint32_t *)dstBuf, WRITE_SIZE_IN_BYTES);

                XMEM_CACHE_INVALIDATE_IF_PSRAM(object);
                HwiP_restore(readCacheKey);

                buffer += READ_SIZE_IN_BYTES - alignment;
                remainingBytes -= (READ_SIZE_IN_BYTES - alignment);
                offset += READ_SIZE_IN_BYTES - alignment;
                alignment = 0;
            }

            /* Less than 256-bytes remaining */
            if (remainingBytes > 0)
            {
                if (offset + WRITE_SIZE_IN_BYTES > object->regionSize)
                {
                    alignment = offset & 0xFF;
                }

                dstBuf = (uint32_t *)(ConvertOffsetToAddr(handle, offset, LOGIC_ADDR) - alignment);

                uintptr_t readCacheKey = HwiP_disable();
                XMEM_CACHE_FLUSH_IF_PSRAM(object);

                if (alignment + remainingBytes > WRITE_SIZE_IN_BYTES)
                {
                    size_t firstWriteSize = WRITE_SIZE_IN_BYTES - alignment;

                    FlashRead((uint32_t *)dstBuf, (uint32_t *)srcBuf, READ_SIZE_IN_BYTES);
                    memcpy((uint8_t *)srcBuf + alignment, buffer, firstWriteSize);

                    FlashWrite((uint32_t *)srcBuf, (uint32_t *)dstBuf, WRITE_SIZE_IN_BYTES);

                    uint8_t *nextBuffer = (uint8_t *)buffer + firstWriteSize;
                    size_t nextSize     = remainingBytes - firstWriteSize;
                    uint32_t nextAddr   = (uint32_t)dstBuf + WRITE_SIZE_IN_BYTES;

                    FlashRead((uint32_t *)nextAddr, (uint32_t *)srcBuf, READ_SIZE_IN_BYTES);
                    memcpy((uint8_t *)srcBuf, nextBuffer, nextSize);

                    FlashWrite((uint32_t *)srcBuf, (uint32_t *)nextAddr, WRITE_SIZE_IN_BYTES);
                }
                else
                {
                    FlashRead((uint32_t *)dstBuf, (uint32_t *)srcBuf, READ_SIZE_IN_BYTES);
                    memcpy((uint8_t *)srcBuf + alignment, buffer, remainingBytes);

                    FlashWrite((uint32_t *)srcBuf, (uint32_t *)dstBuf, WRITE_SIZE_IN_BYTES);
                }
                XMEM_CACHE_INVALIDATE_IF_PSRAM(object);
                HwiP_restore(readCacheKey);
            }

            MutexP_unlock(writeMutex, mutexKey);
            return (XMEM_STATUS_SUCCESS);
        }

        /* Flash: Original complex 256-byte aligned logic */
        srcBuf             = (uint32_t *)xmemDataToWriteBuf;
        size               = bufferSize;
        dstBuf             = (uint32_t *)flashlogicStartAddr;
        int remainingBytes = size;
        uint32_t alignment;

        /* Handling the constraint of writing from 256-byte aligned address to prevent sector crossing */
        alignment = offset % WRITE_SIZE_IN_BYTES;

        /* Handle the constraint of writing multiples of 256 Bytes at a time. */
        while (remainingBytes >= WRITE_SIZE_IN_BYTES)
        {
            /* Set address to write
             * If offset is not align, set the address to be align*/
            dstBuf = (uint32_t *)(ConvertOffsetToAddr(handle, offset, LOGIC_ADDR) - alignment);

            /* Read from flash
             * dstBuf is align, read 256 bytes*/
            FlashRead((uint32_t *)dstBuf, (uint32_t *)srcBuf, READ_SIZE_IN_BYTES);

            /* Copy data to from read buffer to write buffer.
             * If offset is not aligned, copy data to correct place in write buffer*/
            memcpy((uint8_t *)srcBuf + alignment, buffer, READ_SIZE_IN_BYTES - alignment);

            /* Write to flash */
            FlashWrite((uint32_t *)srcBuf, (uint32_t *)dstBuf, WRITE_SIZE_IN_BYTES);

            /* Advance buffer, subtract remain size, Advance offset */
            buffer += READ_SIZE_IN_BYTES - alignment;
            remainingBytes -= (READ_SIZE_IN_BYTES - alignment);
            offset += READ_SIZE_IN_BYTES - alignment;

            /* Now the offset is aligned, alignment should be 0 for the rest of the read loop*/
            alignment = 0;
        }

        /* Less than 256-bytes to write:
         * - Either after the loop for remaining bytes
         * - Or for first time write with less than 256-bytes length
         */
        if (remainingBytes > 0)
        {
            /* Handling the constraint of writing to addresses that exceed region size  */
            if (offset + WRITE_SIZE_IN_BYTES > object->regionSize)
            {
                alignment = offset & 0xFF;
            }

            /* Set address to read from
             * If offset is not align, set the address to be align*/
            dstBuf = (uint32_t *)(ConvertOffsetToAddr(handle, offset, LOGIC_ADDR) - alignment);

            /* Check if the true alignment + remainingBytes exceeds buffer size */
            if (alignment + remainingBytes > WRITE_SIZE_IN_BYTES)
            {
                /* Calculate how much we can write in first operation */
                size_t firstWriteSize = WRITE_SIZE_IN_BYTES - alignment;

                /* First write operation */
                FlashRead((uint32_t *)dstBuf, (uint32_t *)srcBuf, READ_SIZE_IN_BYTES);
                memcpy((uint8_t *)srcBuf + alignment, buffer, firstWriteSize);

                FlashWrite((uint32_t *)srcBuf, (uint32_t *)dstBuf, WRITE_SIZE_IN_BYTES);

                /* Second write operation for remaining bytes */
                uint8_t *nextBuffer = (uint8_t *)buffer + firstWriteSize;
                size_t nextSize     = remainingBytes - firstWriteSize;
                uint32_t nextAddr   = (uint32_t)dstBuf + WRITE_SIZE_IN_BYTES;

                FlashRead((uint32_t *)nextAddr, (uint32_t *)srcBuf, READ_SIZE_IN_BYTES);
                memcpy((uint8_t *)srcBuf, nextBuffer, nextSize);

                FlashWrite((uint32_t *)srcBuf, (uint32_t *)nextAddr, WRITE_SIZE_IN_BYTES);
            }
            else
            {
                /* Read from flash
                 * dstBuf is aligned, read 256 bytes.
                 */
                FlashRead((uint32_t *)dstBuf, (uint32_t *)srcBuf, READ_SIZE_IN_BYTES);

                /* Copy data from read buffer to write buffer.
                 * If offset is not aligned, copy data to correct place in write buffer */
                memcpy((uint8_t *)srcBuf + alignment, buffer, remainingBytes);

                /* Write to flash */
                FlashWrite((uint32_t *)srcBuf, (uint32_t *)dstBuf, WRITE_SIZE_IN_BYTES);
            }
        }
    }

    if (status != 0)
    {
        retval = XMEM_STATUS_ERROR;
    }
    else if (flags & XMEM_WRITE_POST_VERIFY)
    {
        /*
         *  Note: This validates the entire bufferSize even on erase mode.
         */

        /* Validate that the verification buffer has been configured */
        if ((verifyBuf == NULL) || (hwAttrs->flashType.verifyBufSize == 0))
        {
            MutexP_unlock(writeMutex, mutexKey);
            return (XMEM_STATUS_VERIFYBUFFER);
        }

        /* Start reading from the requested start address */
        flashlogicAddr = originalOffset;

        /* Set the number of bytes to read */
        totalSize = bufferSize;

        j = 0;

        while (totalSize > 0)
        {
            if (totalSize > hwAttrs->flashType.verifyBufSize)
            {
                size = hwAttrs->flashType.verifyBufSize;
            }
            else
            {
                size = totalSize;
            }

            _srcBuf = (uint8_t *)originalBuffer;
            _dstBuf = (uint8_t *)verifyBuf;

            XMEMWFF3_read(handle, flashlogicAddr, _dstBuf, size, 0);

            for (i = 0; i < size; i++, j++)
            {
                if (_srcBuf[j] != _dstBuf[i])
                {
                    MutexP_unlock(writeMutex, mutexKey);
                    return (XMEM_STATUS_ERROR);
                }
            }

            flashlogicAddr = flashlogicAddr + size;
            totalSize      = totalSize - size;
        }
    }

    MutexP_unlock(writeMutex, mutexKey);

    return (retval);
}

/*
 *  ======== checkEraseRange ========
 */
static int_fast16_t checkEraseRange(XMEM_Handle handle, size_t offset, size_t size)
{
    if (handle == NULL)
    {
        return (XMEM_STATUS_ERROR);
    }

    XMEMWFF3_Object const *object;

    object = handle->object;

    if (offset != (offset & sectorBaseMask))
    {
        return (XMEM_STATUS_INV_ALIGNMENT); /* Start address is not aligned */
    }

    if (size != (size & sectorBaseMask))
    {
        return (XMEM_STATUS_INV_SIZE); /* Size is not a multiple of sector size */
    }

    if (offset >= object->regionSize)
    {
        return (XMEM_STATUS_INV_OFFSET); /* Offset is past end of region */
    }

    if (offset + size > object->regionSize)
    {
        return (XMEM_STATUS_INV_SIZE); /* Size is too big */
    }

    return (XMEM_STATUS_SUCCESS);
}

uint32_t ConvertOffsetToAddr(XMEM_Handle handle, size_t offset, size_t AddrType)
{
    if (handle == NULL)
    {
        return 0;
    }

    XMEMWFF3_Object const *object;

    object = handle->object;

    uint32_t calcAddr;

    /* Calculate logical address */
    if (AddrType == LOGIC_ADDR)
    {
        calcAddr = object->regionStartAddr + offset;
        return (calcAddr);
    }
    else
    {
        /* Calculate physical address */
        calcAddr = object->regionBase + offset;
        return (calcAddr);
    }
}

/*
 *  ======== doErase ========
 */
static int_fast16_t doErase(XMEM_Handle handle, size_t offset, size_t size)
{
    if (handle == NULL)
    {
        return (XMEM_STATUS_ERROR);
    }

    XMEMWFF3_HWAttrs const *hwAttrs;
    XMEMWFF3_Object const *object;

    hwAttrs = handle->hwAttrs;
    object  = handle->object;

    unsigned int key;
    uint32_t status = 0;
    uint32_t clockPTickPeriod;
    int_fast16_t rangeStatus;

    /* Sanity test the erase args */
    rangeStatus = checkEraseRange(handle, offset, size);

    if (rangeStatus != XMEM_STATUS_SUCCESS)
    {
        return (rangeStatus);
    }

    uint32_t startAddrPhy = ConvertOffsetToAddr(handle, offset, PHYSICAL_ADDR);

    while (size)
    {
        key = HwiP_disable();

        /*
         * Ensure SysTimer is enabled, to be able to read the SysTimer counter
         * value.
         */
        clockPTickPeriod = ClockP_getSystemTickPeriod();
        FlashSetTickPeriod(clockPTickPeriod);
        status = (uint32_t)FlashSectorErase(startAddrPhy, object->deviceNum);

        HwiP_restore(key);

        if (status != FLASH_STATUS_SUCCESS)
        {
            break;
        }

        startAddrPhy += hwAttrs->flashType.sectorSize;
        size -= hwAttrs->flashType.sectorSize;
    }

    if (status != FLASH_STATUS_SUCCESS)
    {
        return (XMEM_STATUS_ERROR);
    }

    return (XMEM_STATUS_SUCCESS);
}

/*
 *  ======== flashTypeSelection ========
 */
static void flashTypeSelection(void)
{
    const FlashType IS25WJ032F_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0402220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0402220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0200,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType IS25WJ064F_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0402220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0402220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0200,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType W25Q32JW_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0802220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0802220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0400,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType W25Q64JW_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0802220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0802220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0400,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType W25Q33PW_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0602220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0602220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0300,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType W25Q64PW_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0602220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0602220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0300,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType W25Q12PW_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0802220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0802220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0300,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType GD25LF32E_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0402220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0402220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0200,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType GD25LF64E_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0402220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0402220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0200,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType PY25Q32LB_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0a02220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0a02220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0500,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType PY25Q64LB_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0a02220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0a02220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0500,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType PY25Q128LA_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0a02220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0a02220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0500,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType PY25Q256LC_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0c02220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0c02220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bbb0600,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020bb000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200b0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType MX25U3235F_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0402220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0402220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0200,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType MX25U6435F_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0402220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0402220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0200,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType MX25U12843G_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x060222eb,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x060222eb,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0xebba0300,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    const FlashType IS25WJ128F_TYPE = {

        /* Operations */
        .writeStigCfg.preStigCfg  = 1,
        .writeStigCfg.postStigCfg = 0,
        .readStigCfg.preStigCfg   = 0,
        .readStigCfg.postStigCfg  = 0,
        .eraseStigCfg.preStigCfg  = 1,
        .eraseStigCfg.postStigCfg = 0,
        .eraseStigCfg.StigCfg     = 1,

        /* Enter STIG mode */
        .enterStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .enterStigCfg[0].data    = 0x82080089,
        .enterStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .enterStigCfg[1].data    = 0x0602220b,
        .enterStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .enterStigCfg[2].data    = 0x00022002,

        /* EXIT STIG mode */
        .exitStigCfg[0].address = OSPI_REGS_BASE + OSPI_O_CONFIG,
        .exitStigCfg[0].data    = 0x82080089,
        .exitStigCfg[1].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_RD_CONFIG,
        .exitStigCfg[1].data    = 0x0602220b,
        .exitStigCfg[2].address = OSPI_REGS_BASE + OSPI_O_DEV_INSTR_WR_CONFIG,
        .exitStigCfg[2].data    = 0x00022002,

        /* Pre STIG configuration */
        .writeStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.preStigOperation[0].data    = 0x06000001,
        .eraseStigCfg.preStigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.preStigOperation[0].data    = 0x06000001,

        /* Execute STIG operation */
        .readStigCfg.stigOperation[0].address  = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .readStigCfg.stigOperation[0].data     = 0x0bba0300,
        .writeStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .writeStigCfg.stigOperation[0].data    = 0x020ab000,
        .eraseStigCfg.stigOperation[0].address = OSPI_REGS_BASE + OSPI_O_FLASH_CMD_CTRL,
        .eraseStigCfg.stigOperation[0].data    = 0x200a0000,

        /* Polling operation */
        .pollingCfg.command        = 0x05900000,
        .pollingCfg.timeOut        = 200,
        .pollingCfg.NumOfIteration = 4,

        /* General */
        .sectorSize    = 0x1000,
        .verifyBufSize = 256};

    /* Read data from shared memory */
    if (BOOT_REPORT_ADDR != 0 && BOOT_REPORT_ADDR >= 0x28000000)
    {
        uint8_t *pSharedReport      = (uint8_t *)(BOOT_REPORT_ADDR);
        uint16_t flashTypeBitMap    = *((uint16_t *)(pSharedReport + 9)); /* Flash type offset is 9 bytes */
        XMEM_Flash_Idx flashTypeIdx = (XMEM_Flash_Idx)(flashTypeBitMap & 0xff);

        switch (flashTypeIdx)
        {
            case IS25WJ032F:
                {
                    XMEMWFF3_hwAttrs.flashType = IS25WJ032F_TYPE;
                }
                break;

            case IS25WJ064F:
                {
                    XMEMWFF3_hwAttrs.flashType = IS25WJ064F_TYPE;
                }
                break;

            case W25Q32JW:
                {
                    XMEMWFF3_hwAttrs.flashType = W25Q32JW_TYPE;
                }
                break;

            case W25Q64JW:
                {
                    XMEMWFF3_hwAttrs.flashType = W25Q64JW_TYPE;
                }
                break;

            case GD25LF32E:
                {
                    XMEMWFF3_hwAttrs.flashType = GD25LF32E_TYPE;
                }
                break;

            case GD25LF64E:
                {
                    XMEMWFF3_hwAttrs.flashType = GD25LF64E_TYPE;
                }
                break;

            case PY25Q32LB:
                {
                    XMEMWFF3_hwAttrs.flashType = PY25Q32LB_TYPE;
                }
                break;

            case PY25Q64LB:
                {
                    XMEMWFF3_hwAttrs.flashType = PY25Q64LB_TYPE;
                }
                break;
            case PY25Q128LA:
                {
                    XMEMWFF3_hwAttrs.flashType = PY25Q128LA_TYPE;
                }
                break;
            case PY25Q256LC:
                {
                    XMEMWFF3_hwAttrs.flashType = PY25Q256LC_TYPE;
                }
                break;
            case MX25U3235F:
                {
                    XMEMWFF3_hwAttrs.flashType = MX25U3235F_TYPE;
                }
                break;
            case MX25U6435F:
                {
                    XMEMWFF3_hwAttrs.flashType = MX25U6435F_TYPE;
                }
                break;
            case MX25U12843G:
                {
                    XMEMWFF3_hwAttrs.flashType = MX25U12843G_TYPE;
                }
                break;
            case IS25WJ128F:
                {
                    XMEMWFF3_hwAttrs.flashType = IS25WJ128F_TYPE;
                }
                break;
            case W25Q33PW:
                {
                    XMEMWFF3_hwAttrs.flashType = W25Q33PW_TYPE;
                }
                break;
            case W25Q64PW:
                {
                    XMEMWFF3_hwAttrs.flashType = W25Q64PW_TYPE;
                }
                break;
            case W25Q12PW:
                {
                    XMEMWFF3_hwAttrs.flashType = W25Q12PW_TYPE;
                }
                break;

            default:
                /* Default to a safe configuration */
                XMEMWFF3_hwAttrs.flashType = IS25WJ032F_TYPE;
                break;
        }
    }
}

/*
 *  ======== XMEMWFF3_addrToType ========
 */
XMEM_MemType XMEMWFF3_addrToType(uintptr_t addr)
{
    if (((addr >= EXT_PSRAM_BASE) && (addr < (EXT_PSRAM_BASE + XMEM_MAX_PSRAM_SIZE))) ||
        ((addr >= EXT_PSRAM_SEC_BASE) && (addr < (EXT_PSRAM_SEC_BASE + XMEM_MAX_PSRAM_SIZE))))
    {
        return XMEM_MEM_PSRAM;
    }

    if (((addr >= EXT_FLASH_BASE) && (addr < (EXT_FLASH_BASE + XMEM_MAX_FLASH_SIZE))) ||
        ((addr >= EXT_FLASH_SEC_BASE) && (addr < (EXT_FLASH_SEC_BASE + XMEM_MAX_FLASH_SIZE))))
    {
        return XMEM_MEM_FLASH;
    }

    return XMEM_MEM_INTERNAL;
}

/*
 *  ======== XMEMWFF3_isAddrExternal ========
 */
bool XMEMWFF3_isAddrExternal(uintptr_t addr)
{
    return XMEMWFF3_addrToType(addr) != XMEM_MEM_INTERNAL;
}

/*
 *  ======== XMEMWFF3_addrToOffset ========
 */
size_t XMEMWFF3_addrToOffset(uintptr_t addr)
{

    XMEM_MemType memType = XMEMWFF3_addrToType(addr);

    if (memType == XMEM_MEM_PSRAM)
    {
        return (addr >= EXT_PSRAM_SEC_BASE) ? (size_t)(addr - EXT_PSRAM_SEC_BASE) : (size_t)(addr - EXT_PSRAM_BASE);
    }

    return (addr >= EXT_FLASH_SEC_BASE) ? (size_t)(addr - EXT_FLASH_SEC_BASE) : (size_t)(addr - EXT_FLASH_BASE);
}
