/*
 * Copyright (c) 2020, Texas Instruments Incorporated
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
 *  ======== UART2CC32XX.c ========
 */

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC32XX.h>
#include <ti/drivers/dma/UDMACC32XX.h>

#include <ti/drivers/uart2/UART2CC32XX.h>

/* driverlib header files */
#include <ti/devices/cc32xx/inc/hw_memmap.h>
#include <ti/devices/cc32xx/inc/hw_ocp_shared.h>
#include <ti/devices/cc32xx/inc/hw_ints.h>
#include <ti/devices/cc32xx/inc/hw_types.h>
#include <ti/devices/cc32xx/inc/hw_uart.h>
#include <ti/devices/cc32xx/driverlib/rom.h>
#include <ti/devices/cc32xx/driverlib/rom_map.h>
#include <ti/devices/cc32xx/driverlib/uart.h>
#include <ti/devices/cc32xx/driverlib/pin.h>
#include <ti/devices/cc32xx/driverlib/udma.h>

/* Pad configuration defines */
#define PAD_CONFIG_BASE (OCP_SHARED_BASE + OCP_SHARED_O_GPIO_PAD_CONFIG_0)
#define PAD_RESET_STATE 0xC61

#if defined(__IAR_SYSTEMS_ICC__)
#include <intrinsics.h>
#endif

#define MIN(a,b) (((a)<(b))?(a):(b))

/* Mazimum number of bytes that DMA can transfer */
#define MAX_SIZE 1024

/* Options for DMA write and read */
#define TX_CONTROL_OPTS  (UDMA_SIZE_8 | UDMA_SRC_INC_8 | UDMA_DST_INC_NONE | \
                          UDMA_ARB_4)
#define RX_CONTROL_OPTS  (UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 | \
                          UDMA_ARB_4)

/* Static functions */
static void configDmaRx(UART2_Handle handle);
static void configDmaTx(UART2_Handle handle);
static void UART2CC32XX_hwiIntFxn(uintptr_t arg);
static uint_fast16_t getPowerMgrId(uint32_t baseAddr);
static void initHw(UART2_Handle handle);
static int  postNotifyFxn(unsigned int eventType, uintptr_t eventArg,
        uintptr_t clientArg);
static void cancelDmaRx(UART2_Handle handle);
static int32_t readData(UART2_Handle handle, int32_t size);
static void readSemCallback(UART2_Handle handle, void *buffer, size_t count,
        void *userArg, int_fast16_t status);
static void readDone(UART2_Handle handle);
static void writeSemCallback(UART2_Handle handle, void *buffer, size_t count,
        void *userArg, int_fast16_t status);

/* UART function table for UART2CC32XX implementation */
const UART2_FxnTable UART2CC32XX_fxnTable = {
    UART2CC32XX_close,
    UART2CC32XX_open,
    UART2CC32XX_read,
    UART2CC32XX_readCancel,
    UART2CC32XX_write,
    UART2CC32XX_writeCancel,
    UART2CC32XX_flushRx,
};

/* Map UART2 data length to driverlib data length */
static const uint32_t dataLength[] = {
    UART_CONFIG_WLEN_5,     /* UART2_DataLen_5 */
    UART_CONFIG_WLEN_6,     /* UART2_DataLen_6 */
    UART_CONFIG_WLEN_7,     /* UART2_DataLen_7 */
    UART_CONFIG_WLEN_8      /* UART2_DataLen_8 */
};

/* Map UART2 stop bits to driverlib stop bits */
static const uint32_t stopBits[] = {
    UART_CONFIG_STOP_ONE,   /* UART2_StopBits_1 */
    UART_CONFIG_STOP_TWO    /* UART2_StopBits_2 */
};

/* Map UART2 parity type to driverlib parity type */
static const uint32_t parityType[] = {
    UART_CONFIG_PAR_NONE,   /* UART2_Parity_NONE */
    UART_CONFIG_PAR_EVEN,   /* UART2_Parity_EVEN */
    UART_CONFIG_PAR_ODD,    /* UART2_Parity_ODD */
    UART_CONFIG_PAR_ZERO,   /* UART2_Parity_ZERO */
    UART_CONFIG_PAR_ONE     /* UART2_Parity_ONE */
};

/*
 *  Map UART2CC32XX FIFO threshold types to driverlib TX FIFO threshold
 *  defines.
 */
static const uint8_t txFifoThreshold[5] = {
    UART_FIFO_TX1_8, /* UART2CC32XX_FIFO_THRESHOLD_1_8     */
    UART_FIFO_TX2_8, /* UART2CC32XX_FIFO_THRESHOLD_2_8     */
    UART_FIFO_TX4_8, /* UART2CC32XX_FIFO_THRESHOLD_4_8     */
    UART_FIFO_TX6_8, /* UART2CC32XX_FIFO_THRESHOLD_6_8     */
    UART_FIFO_TX7_8  /* UART2CC32XX_FIFO_THRESHOLD_7_8     */
};

/*
 *  Map UART2CC32XXFIFO threshold types to driverlib RX FIFO threshold
 *  defines.
 */
static const uint8_t rxFifoThreshold[5] = {
    UART_FIFO_RX1_8, /* UART2CC32XX_FIFO_THRESHOLD_1_8     */
    UART_FIFO_RX2_8, /* UART2CC32XX_FIFO_THRESHOLD_2_8     */
    UART_FIFO_RX4_8, /* UART2CC32XX_FIFO_THRESHOLD_4_8     */
    UART_FIFO_RX6_8, /* UART2CC32XX_FIFO_THRESHOLD_6_8     */
    UART_FIFO_RX7_8  /* UART2CC32XX_FIFO_THRESHOLD_7_8     */
};

/* Number of bytes in the RX FIFO at the corresponding FIFO threshold level */
static const uint8_t rxFifoBytes[6] = {
     2,   /* UART2CC26X2_FIFO_THRESHOLD_1_8     */
     4,   /* UART2CC26X2_FIFO_THRESHOLD_2_8     */
     8,   /* UART2CC26X2_FIFO_THRESHOLD_4_8     */
    12,   /* UART2CC26X2_FIFO_THRESHOLD_6_8     */
    14    /* UART2CC26X2_FIFO_THRESHOLD_7_8     */
};

/*
 *  ======== uartDmaEnable ========
 *  Atomic version of DriverLib UARTDMAEnable()
 */
static inline void uartDmaEnable(uint32_t ui32Base, uint32_t ui32DMAFlags)
{
    uintptr_t key;

    key = HwiP_disable();
    /* Set the requested bits in the UART DMA control register. */
    HWREG(ui32Base + UART_O_DMACTL) |= ui32DMAFlags;

    HwiP_restore(key);
}

/*
 *  ======== uartDmaDisable ========
 *  Atomic version of DriverLib UARTDMADisable()
 */
static inline void uartDmaDisable(uint32_t ui32Base, uint32_t ui32DMAFlags)
{
    uintptr_t key;

    key = HwiP_disable();
    /* Clear the requested bits in the UART DMA control register. */
    HWREG(ui32Base + UART_O_DMACTL) &= ~ui32DMAFlags;

    HwiP_restore(key);
}

/*
 *  ======== getRxStatus ========
 *  Get the left-most bit set in the RX error status (OE, BE, PE, FE)
 *  read from the RSR register:
 *      bit#   3   2   1   0
 *             OE  BE  PE  FE
 *  e.g., if OE and FE are both set, OE wins.  This will make it easier
 *  to convert an RX error status to a UART2 error code.
 */
static inline uint32_t getRxStatus(uint32_t x)
{
#if defined(__TI_COMPILER_VERSION__)
    return ((uint32_t) (x & (0x80000000 >> __clz(x))));
#elif defined(__GNUC__)
    return ((uint32_t) (x & (0x80000000 >> __builtin_clz(x))));
#elif defined(__IAR_SYSTEMS_ICC__)
    return ((uint32_t) (x & (0x80000000 >>  __CLZ(x))));
#else
    #error "Unsupported compiler"
#endif
}

/*
 *  ======== rxStatus2ErrorCode ========
 *  Convert RX status (OE, BE, PE, FE) to a UART2 error code.
 */
static inline int_fast16_t rxStatus2ErrorCode(uint32_t x)
{
    uint32_t status;

    status = getRxStatus(x);
    return (-((int_fast16_t)status));
}

/*
 * Function for checking whether flow control is enabled.
 */
static inline bool isFlowControlEnabled(UART2CC32XX_HWAttrs const *hwAttrs) {
    return (hwAttrs->flowControl == UART2CC32XX_FLOWCTRL_HARDWARE);
}

/*
 *  ======== UART2CC32XX_close ========
 */
void UART2CC32XX_close(UART2_Handle handle)
{
    UART2CC32XX_Object        *object = handle->object;
    UART2CC32XX_HWAttrs const *hwAttrs = handle->hwAttrs;
    uint32_t                   padRegister;

    /* Disable UART and interrupts. */
    UARTIntDisable(hwAttrs->baseAddr, UART_INT_RX | UART_INT_RT | UART_INT_OE |
                   UART_INT_BE | UART_INT_PE | UART_INT_FE | UART_INT_EOT);
 
    /* Disable UART and interrupts. */
    uartDmaDisable(hwAttrs->baseAddr, UART_DMA_TX | UART_DMA_RX);
    MAP_UARTDisable(hwAttrs->baseAddr);

    if (object->hwi) {
        HwiP_delete(object->hwi);
    }
    if (object->writeSem) {
        SemaphoreP_delete(object->writeSem);
    }
    if (object->readSem) {
        SemaphoreP_delete(object->readSem);
    }
    if (object->udmaHandle) {
        UDMACC32XX_close(object->udmaHandle);
    }

    Power_unregisterNotify(&object->postNotify);
    Power_releaseDependency(object->powerMgrId);

    if (object->txPin != (uint16_t)-1) {
        PowerCC32XX_restoreParkState((PowerCC32XX_Pin)object->txPin,
                                     object->prevParkTX);
        object->txPin = (uint16_t)-1;
    }

    if (object->rtsPin != (uint16_t)-1) {
        PowerCC32XX_restoreParkState((PowerCC32XX_Pin)object->rtsPin,
                                     object->prevParkRTS);
        object->rtsPin = (uint16_t)-1;
    }

    /* Restore pin pads to their reset states */
    padRegister = (PinToPadGet((hwAttrs->rxPin) & 0xff)<<2) + PAD_CONFIG_BASE;
    HWREG(padRegister) = PAD_RESET_STATE;
    padRegister = (PinToPadGet((hwAttrs->txPin) & 0xff)<<2) + PAD_CONFIG_BASE;
    HWREG(padRegister) = PAD_RESET_STATE;
    if (isFlowControlEnabled(hwAttrs)) {
        if (hwAttrs->ctsPin != UART2CC32XX_PIN_UNASSIGNED) {
            padRegister = (PinToPadGet((hwAttrs->ctsPin) & 0xff)<<2)
                                       + PAD_CONFIG_BASE;
            HWREG(padRegister) = PAD_RESET_STATE;
        }

        if (hwAttrs->rtsPin != UART2CC32XX_PIN_UNASSIGNED) {
            padRegister = (PinToPadGet((hwAttrs->rtsPin) & 0xff)<<2)
                                       + PAD_CONFIG_BASE;
            HWREG(padRegister) = PAD_RESET_STATE;
        }
    }

    object->state.opened = false;
}

/*
 *  ======== UART2CC32XX_flushRx ========
 */
void UART2CC32XX_flushRx(UART2_Handle handle)
{
    UART2CC32XX_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Clear any read errors */
    MAP_UARTRxErrorClear(hwAttrs->baseAddr);

    /* Read RX FIFO until empty */
    while (((int32_t)MAP_UARTCharGetNonBlocking(hwAttrs->baseAddr)) != -1);
}

/*
 *  ======== UART2CC32XX_hwiIntFxn ========
 *  Hwi function that processes UART interrupts.
 */
static void UART2CC32XX_hwiIntFxn(uintptr_t arg)
{
    uint32_t                   status;
    uint32_t                   errStatus = 0;
    uint32_t                   bytesToRead;
    uint32_t                   fifoThresholdBytes;
    UART2_Handle               handle = (UART2_Handle)arg;
    UART2CC32XX_HWAttrs const *hwAttrs = handle->hwAttrs;
    UART2CC32XX_Object        *object = handle->object;

    /* Clear interrupts */
    status = MAP_UARTIntStatus(hwAttrs->baseAddr, true);
    MAP_UARTIntClear(hwAttrs->baseAddr, status);

    if (status & (UART_INT_OE | UART_INT_BE | UART_INT_PE | UART_INT_FE)) {
        /* Handle the error */
        if (object->state.readReturnMode != UART2_ReadReturnMode_PARTIAL) {
            UARTDMADisable(hwAttrs->baseAddr, UART_DMA_RX);

            /* Number of bytes not yet transferred by the DMA */
            bytesToRead = uDMAChannelSizeGet(hwAttrs->rxDmaChannel);
            object->bytesRead += (object->readCount - bytesToRead);
        }

        errStatus = UARTRxErrorGet(hwAttrs->baseAddr);
        object->rxStatus = rxStatus2ErrorCode(errStatus);

        readDone(handle);
    }
    else if (status & UART_INT_RT) {
        if ((object->state.readReturnMode == UART2_ReadReturnMode_PARTIAL) &&
                object->readCount > 0) {
            readData(handle, object->readCount);

            readDone(handle);
        }
    }
    else if ((status & UART_INT_RX) &&
             (object->state.readReturnMode == UART2_ReadReturnMode_PARTIAL)) {
        /* Must leave at least one byte in the fifo to get read timeout */
        fifoThresholdBytes = rxFifoBytes[hwAttrs->rxIntFifoThr];
        bytesToRead = MIN(fifoThresholdBytes - 1, object->readCount);
        readData(handle, bytesToRead);

        if (object->readCount == 0) {
            readDone(handle);
        }
    }

    /* Read data if characters are available. */
    if ((object->state.readReturnMode != UART2_ReadReturnMode_PARTIAL) &&
        object->readSize && !uDMAChannelIsEnabled(hwAttrs->rxDmaChannel)) {
        UARTDMADisable(hwAttrs->baseAddr, UART_DMA_RX);

        errStatus = MAP_UARTRxErrorGet(hwAttrs->baseAddr);
        object->rxStatus = rxStatus2ErrorCode(errStatus);
        MAP_UARTRxErrorClear(hwAttrs->baseAddr);

        UARTIntDisable(hwAttrs->baseAddr, UART_INT_DMARX);
        UARTIntClear(hwAttrs->baseAddr, UART_INT_DMARX);

        if (object->readCount != 0) {
            object->bytesRead += object->rxSize;
            object->readCount -= object->rxSize;

            if (--object->nReadTransfers == 0) {
                readDone(handle);
            }
            else {
                /* Start a new DMA transfer */
                configDmaRx(handle);
            }
        }
    }

    /* Write completed. */
    if (object->writeCount && !MAP_uDMAChannelIsEnabled(hwAttrs->txDmaChannel)) {
        /*
         * Cannot clear DMATXRIS in the UART_RIS register without disabling
         * DMA
         */
        UARTDMADisable(hwAttrs->baseAddr, UART_DMA_TX);

        UARTIntDisable(hwAttrs->baseAddr, UART_INT_DMATX);
        UARTIntClear(hwAttrs->baseAddr, UART_INT_DMATX);

        object->bytesWritten += object->txSize;
        object->writeCount -= object->txSize;

        if ((object->writeCount) && (--object->nWriteTransfers > 0)) {
            configDmaTx(handle);
        }
    }

    /* EOT interrupt received */
    if (status & (UART_INT_EOT)) {
        /* Check txEnabled in case writeCancel was called */
        if ((object->writeCount == 0) && object->state.txEnabled) {
            Power_releaseConstraint(PowerCC32XX_DISALLOW_LPDS);

            object->state.txEnabled = false;
            object->writeSize = 0;
            object->writeCallback(handle, (void *)object->writeBuf,
                    object->bytesWritten, object->userArg, object->txStatus);
        }
    }
}

/*
 *  ======== UART2CC32XX_open ========
 */
UART2_Handle UART2CC32XX_open(uint_least8_t index, UART2_Params *params)
{
    UART2_Handle               handle = NULL;
    UART2CC32XX_Object        *object;
    UART2CC32XX_HWAttrs const *hwAttrs;
    HwiP_Params                hwiParams;
    uintptr_t                  key;
    uint16_t                   pin;
    uint16_t                   mode;

    if (index < UART2_count) {
        handle = (UART2_Handle)&(UART2_config[index]);
        hwAttrs = handle->hwAttrs;
        object = handle->object;
    }
    else {
        return (NULL);
    }
    
    /* Check for callback when in UART2_Mode_CALLBACK */
    if (((params->readMode == UART2_Mode_CALLBACK) &&
        (params->readCallback == NULL)) ||
         ((params->writeMode == UART2_Mode_CALLBACK) &&
          (params->writeCallback == NULL))) {
        return (NULL);
    }

    key = HwiP_disable();

    if (object->state.opened) {
        HwiP_restore(key);
        return (NULL);
    }
    object->state.opened = true;

    HwiP_restore(key);

    object->state.txEnabled      = false;
    object->state.readMode       = params->readMode;
    object->state.writeMode      = params->writeMode;
    object->state.readReturnMode = params->readReturnMode;
    object->readCallback         = params->readCallback;
    object->writeCallback        = params->writeCallback;
    object->baudRate             = params->baudRate;
    object->stopBits             = params->stopBits;
    object->dataLength           = params->dataLength;
    object->parityType           = params->parityType;
    object->userArg              = params->userArg;

    /* Set UART transaction variables to defaults. */
    object->writeBuf             = NULL;
    object->readBuf              = NULL;
    object->writeCount           = 0;
    object->readCount            = 0;
    object->writeSize            = 0;
    object->readSize             = 0;
    object->nWriteTransfers      = 0;
    object->nReadTransfers       = 0;
    object->rxStatus             = 0;
    object->txStatus             = 0;
    object->state.txEnabled      = false;
    object->txPin                = (uint16_t)-1;
    object->rtsPin               = (uint16_t)-1;

    object->readSem = NULL;
    object->writeSem = NULL;
    object->hwi = NULL;

    /* Determine the Power resource Id from the UART base address */
    object->powerMgrId = getPowerMgrId(hwAttrs->baseAddr);
    if (object->powerMgrId >= PowerCC32XX_NUMRESOURCES) {
        object->state.opened = false;
        return (NULL);
    }

    /*
     *  Register power dependency. Keeps the clock running in SLP
     *  and DSLP modes.
     */
    Power_setDependency(object->powerMgrId);

    /* Do a software reset of the peripheral */
    PowerCC32XX_reset(object->powerMgrId);

    pin = (hwAttrs->rxPin) & 0xff;
    mode = (hwAttrs->rxPin >> 8) & 0xff;

    MAP_PinTypeUART((unsigned long)pin, (unsigned long)mode);

    pin = (hwAttrs->txPin) & 0xff;
    mode = (hwAttrs->txPin >> 8) & 0xff;

    MAP_PinTypeUART((unsigned long)pin, (unsigned long)mode);

    /*
     * Read and save TX pin park state; set to "don't park" while UART is
     * open as device default is logic '1' during LPDS
     */
    object->prevParkTX =
        (PowerCC32XX_ParkState) PowerCC32XX_getParkState((PowerCC32XX_Pin)pin);
    PowerCC32XX_setParkState((PowerCC32XX_Pin)pin, ~1);
    object->txPin = pin;

    if (isFlowControlEnabled(hwAttrs)) {
        if (hwAttrs->ctsPin != UART2CC32XX_PIN_UNASSIGNED) {
            pin = (hwAttrs->ctsPin) & 0xff;
            mode = (hwAttrs->ctsPin >> 8) & 0xff;
            MAP_PinTypeUART((unsigned long)pin, (unsigned long)mode);
        }

        if (hwAttrs->rtsPin != UART2CC32XX_PIN_UNASSIGNED) {
            pin = (hwAttrs->rtsPin) & 0xff;
            mode = (hwAttrs->rtsPin >> 8) & 0xff;
            MAP_PinTypeUART((unsigned long)pin, (unsigned long)mode);

            /*
             * Read and save RTS pin park state; set to "don't park" while UART is
             * open as device default is logic '1' during LPDS
             */
            object->prevParkRTS = (PowerCC32XX_ParkState)PowerCC32XX_getParkState(
                (PowerCC32XX_Pin)pin);
            PowerCC32XX_setParkState((PowerCC32XX_Pin)pin, ~1);
            object->rtsPin = pin;
        }

        /* Flow control will be enabled in initHw() */
    }

    Power_registerNotify(&object->postNotify, PowerCC32XX_AWAKE_LPDS,
                         postNotifyFxn, (uintptr_t)handle);

    /* DMA first */
    UDMACC32XX_init();
    object->udmaHandle = UDMACC32XX_open();
    if (object->udmaHandle == NULL) {
        UART2CC32XX_close(handle);
        return (NULL);
    }

    /* Initialize the hardware */
    initHw(handle);

    HwiP_clearInterrupt(hwAttrs->intNum);

    HwiP_Params_init(&hwiParams);
    hwiParams.arg = (uintptr_t)handle;
    hwiParams.priority = hwAttrs->intPriority;
    
    object->hwi = HwiP_create(hwAttrs->intNum, UART2CC32XX_hwiIntFxn,
                              &hwiParams);

    if (object->hwi == NULL) {
        UART2CC32XX_close(handle);
        return (NULL);
    }

    /* If write mode is blocking create a semaphore and set callback. */
    if (object->state.writeMode == UART2_Mode_BLOCKING) {
        object->writeSem = SemaphoreP_createBinary(0);
        if (object->writeSem == NULL) {
            UART2CC32XX_close(handle);
            return (NULL);
        }
        object->writeCallback = &writeSemCallback;
    }

    /* If read mode is blocking create a semaphore and set callback. */
    if (object->state.readMode == UART2_Mode_BLOCKING) {
        object->readSem = SemaphoreP_createBinary(0);
        if (object->readSem == NULL) {
            UART2CC32XX_close(handle);
            return (NULL);
        }
        object->readCallback = &readSemCallback;
    }
    
    return (handle);
}

/*
 *  ======== UART2CC32XX_read ========
 */
int_fast16_t UART2CC32XX_read(UART2_Handle handle, void *buffer,
        size_t size, size_t *bytesRead, uint32_t timeout)
{
    UART2CC32XX_Object        *object = handle->object;
    UART2CC32XX_HWAttrs const *hwAttrs = handle->hwAttrs;
    int                        status = UART2_STATUS_SUCCESS;
    unsigned char             *buf = (unsigned char *)buffer;
    int32_t                    data;
    uintptr_t                  key;
    size_t                     nBytesRead;
    size_t                    *pNBytesRead;
    uint32_t                   errStatus;

    pNBytesRead = (bytesRead == NULL) ? &nBytesRead : bytesRead;
    *pNBytesRead = 0;

    /* Check for Rx error since the last read */
    errStatus = UARTRxErrorGet(hwAttrs->baseAddr);
    status = rxStatus2ErrorCode(errStatus);
    UARTRxErrorClear(hwAttrs->baseAddr);

    if (status != UART2_STATUS_SUCCESS) {
        object->readSize = 0;
        return (status);
    }
	
	key = HwiP_disable();
	
    if (object->readSize) {
        HwiP_restore(key);
        return (UART2_STATUS_EINUSE);
    }

    /* Save the data to be read and restore interrupts. */
    object->readBuf = (unsigned char *)buffer;
    object->readSize = size;
    object->readCount = size; /* Number remaining to be read */
    object->bytesRead = 0;    /* Number of bytes read */
    object->rxStatus = 0;     /* Clear receive errors */

    HwiP_restore(key);

    if (object->state.readMode == UART2_Mode_POLLING) {
        while (size) {
            data = UARTCharGetNonBlocking(hwAttrs->baseAddr);
            if (data == -1) {
                break;
            }
            /* Convert error code in upper bytes of data to a UART2 status */
            status = rxStatus2ErrorCode((data >> 8) & 0xF);
            if (status < 0) {
                break;
            }
            *buf++ = data & 0xFF;
            size--;
        }
        *pNBytesRead = object->readSize - size;

        /* Set readSize to 0 to allow another read */
        object->readCount = 0;
        object->readSize = 0;

        return (status);
    }

    /* Set constraints to guarantee transaction */
    Power_setConstraint(PowerCC32XX_DISALLOW_LPDS);

    /*
     *  Don't use DMA for return partial mode, since we have to leave
     *  one byte in the FIFO to get the read timeout.
     */
    if (object->state.readReturnMode != UART2_ReadReturnMode_PARTIAL) {
        /* Can transfer maximum of 1024 bytes in one DMA transfer */
        object->nReadTransfers = (object->readSize + MAX_SIZE - 1) / MAX_SIZE;
        configDmaRx(handle);
    }

    if (object->state.readMode == UART2_Mode_BLOCKING) {
        if (SemaphoreP_OK != SemaphoreP_pend(object->readSem, timeout)) {
            key = HwiP_disable();
            if (object->readSize == 0) {
                /* Interrupt occurred just after SemaphoreP_pend() timeout */
                status = object->rxStatus;
                SemaphoreP_pend(object->readSem, SemaphoreP_NO_WAIT);
                HwiP_restore(key);
            }
            else {
                status = UART2_STATUS_ETIMEOUT;

                /* Set readCount to 0 to prevent ISR from doing more work */
                object->readCount = 0;
                HwiP_restore(key);

                cancelDmaRx(handle);

                /* Release the power constraint */
                Power_releaseConstraint(PowerCC32XX_DISALLOW_LPDS);
            }
        }
        else {
            status = object->rxStatus;
        }

        *pNBytesRead = object->bytesRead;
        object->readSize = 0;  /* Allow the next read */
    }
    else {
        /* ISR will do the work */
    }

    return (status);
}

/*
 *  ======== UART2CC32XX_readCancel ========
 */
void UART2CC32XX_readCancel(UART2_Handle handle)
{
    UART2CC32XX_Object *object = handle->object;
    uintptr_t           key;

    if (object->state.readMode == UART2_Mode_POLLING) {
        return;
    }

    key = HwiP_disable();

    if (object->readSize == 0) {
        HwiP_restore(key);
        return;
    }

    cancelDmaRx(handle);

    object->readSize = 0;
    object->rxStatus = UART2_STATUS_ECANCELLED;

    HwiP_restore(key);

    object->readCallback(handle, object->readBuf, object->bytesRead,
                         object->userArg, UART2_STATUS_ECANCELLED);
}

/*
 *  ======== UART2CC32XX_write ========
 */
int_fast16_t UART2CC32XX_write(UART2_Handle handle, const void *buffer,
        size_t size, size_t *bytesWritten, uint32_t timeout)
{
    UART2CC32XX_Object        *object = handle->object;
    UART2CC32XX_HWAttrs const *hwAttrs = handle->hwAttrs;
    uintptr_t                  key;
    int                        status = UART2_STATUS_SUCCESS;
    uint32_t                   writeCount;
    unsigned char             *buf = (unsigned char *)buffer;
    size_t                     nBytesWritten;
    size_t                    *pNBytesWritten;

    if (size == 0) {
        return (UART2_STATUS_EINVALID);
    }

    pNBytesWritten = (bytesWritten == NULL) ? &nBytesWritten : bytesWritten;

    key = HwiP_disable();

    if (!object->state.opened) {
        HwiP_restore(key);
        return (UART2_STATUS_EINVALID);
    }

    /*
     *  Make sure any previous write has finished.
     *  In blocking mode, UART2_cancel() may have posted the semaphore,
     *  so we use writeSize to ensure that there are no on-going writes.
     *  This ensures that we can return the txStatus to the caller without
     *  it having been reset to 0 by a pre-empting thread.
     */
    if (object->state.txEnabled ||
        (object->writeSize &&
         (object->state.writeMode == UART2_Mode_BLOCKING))) {
        HwiP_restore(key);
        return (UART2_STATUS_EINUSE);
    }

    /* Save the data to be written and restore interrupts. */
    object->writeBuf = buffer;
    object->writeSize = size;
    object->writeCount = size;
    object->bytesWritten = 0;
    object->state.txEnabled = true;

    object->txStatus = UART2_STATUS_SUCCESS;

    HwiP_restore(key);

    if (object->state.writeMode == UART2_Mode_POLLING) {
        writeCount = 0;
        while (size) {
            if (!UARTCharPutNonBlocking(hwAttrs->baseAddr, *buf)) {
                break;
            }
            buf++;
            writeCount++;
            size--;
        }
        *pNBytesWritten = writeCount;
        object->state.txEnabled = false;
        return (status);
    }

    Power_setConstraint(PowerCC32XX_DISALLOW_LPDS);

    object->nWriteTransfers = (object->writeSize + MAX_SIZE - 1) / MAX_SIZE;
    configDmaTx(handle);

    /* If writeMode is blocking, block and get the state. */
    if (object->state.writeMode == UART2_Mode_BLOCKING) {
        /* Pend on semaphore and wait for Hwi to finish. */
        if (SemaphoreP_OK != SemaphoreP_pend(object->writeSem, timeout)) {
            /* Disable the TX interrupt and clear in case it's pending */
            key = HwiP_disable();
            
            UARTIntDisable(hwAttrs->baseAddr, UART_INT_TX);
            UARTIntClear(hwAttrs->baseAddr, UART_INT_TX);

            object->state.txEnabled = false;
            object->txStatus = UART2_STATUS_ETIMEOUT;

            HwiP_restore(key);
        }
        status = object->txStatus; /* UART2_cancel() may have posted semaphore */
        *pNBytesWritten = object->bytesWritten;
        object->writeSize = 0;  /* Allow the next UART2_write */
        object->state.txEnabled = false;
    }

    return (status);
}

/*
 *  ======== UART2CC32XX_writeCancel ========
 */
void UART2CC32XX_writeCancel(UART2_Handle handle)
{
    UART2CC32XX_Object        *object = handle->object;
    UART2CC32XX_HWAttrs const *hwAttrs = handle->hwAttrs;
    uint32_t                   bytesRemaining;
    uintptr_t                  key;

    key = HwiP_disable();

    MAP_uDMAChannelDisable(hwAttrs->txDmaChannel);
    uartDmaDisable(hwAttrs->baseAddr, UART_DMA_TX);

    UARTIntDisable(hwAttrs->baseAddr, UART_INT_DMATX);
    UARTIntClear(hwAttrs->baseAddr, UART_INT_DMATX);

    /* Return if there is no write */
    if ((object->writeSize == 0) && !object->state.txEnabled) {
        HwiP_restore(key);
        return;
    }

    object->state.txEnabled = false;

    bytesRemaining = MAP_uDMAChannelSizeGet(hwAttrs->txDmaChannel);
    object->bytesWritten += object->writeCount - bytesRemaining;

    /*
     *  If the transfer didn't complete, the ISR will not run to
     *  release the Power constraint, so do it here.
     */
    if (object->bytesWritten < object->writeCount) {
        Power_releaseConstraint(PowerCC32XX_DISALLOW_LPDS);
    }

    object->writeSize = 0;
    object->txStatus = UART2_STATUS_ECANCELLED;

    HwiP_restore(key);

    object->writeCallback(handle, (void *)object->writeBuf,
                          object->bytesWritten, object->userArg,
                          UART2_STATUS_ECANCELLED);
}

/*
 *  ======== configDmaRx ========
 *  Call with interrupts disabled.
 */
static void configDmaRx(UART2_Handle handle)
{
    UART2CC32XX_Object        *object = handle->object;
    UART2CC32XX_HWAttrs const *hwAttrs = handle->hwAttrs;
    unsigned int               key;
    uint32_t                   rxSize;

    rxSize = MIN(object->readCount, MAX_SIZE);
    object->rxSize = rxSize;

    /* A lock is needed because we are accessing shared uDMA registers.*/
    key = HwiP_disable();

    MAP_uDMAChannelControlSet(hwAttrs->rxDmaChannel, RX_CONTROL_OPTS);
    MAP_uDMAChannelTransferSet(hwAttrs->rxDmaChannel, UDMA_MODE_BASIC, 
                               (void *)(hwAttrs->baseAddr + UART_O_DR),
                               (void *)(object->readBuf + object->bytesRead), 
                               rxSize);

    uartDmaEnable(hwAttrs->baseAddr, UART_DMA_RX);

    MAP_UARTIntEnable(hwAttrs->baseAddr, UART_INT_DMARX);

    MAP_uDMAChannelEnable(hwAttrs->rxDmaChannel);

    HwiP_restore(key);
}

/*
 *  ======== configDmaTx ========
 *  Call with interrupts disabled.
 */
static void configDmaTx(UART2_Handle handle)
{
    UART2CC32XX_Object        *object = handle->object;
    UART2CC32XX_HWAttrs const *hwAttrs = handle->hwAttrs;
    unsigned int               key;
    uint32_t                   txSize;

    /* TransferSize must be <= 1024 */
    txSize = MIN(object->writeCount, MAX_SIZE);
    object->txSize = txSize;

    /* A lock is needed because we are accessing shared uDMA registers.*/
    key = HwiP_disable();

    MAP_uDMAChannelControlSet(hwAttrs->txDmaChannel, TX_CONTROL_OPTS);
    MAP_uDMAChannelTransferSet(hwAttrs->txDmaChannel, UDMA_MODE_BASIC, 
                               (void *)(object->writeBuf + object->bytesWritten),
                               (void *)(hwAttrs->baseAddr + UART_O_DR), txSize);

    uartDmaEnable(hwAttrs->baseAddr, UART_DMA_TX);

    MAP_UARTIntEnable(hwAttrs->baseAddr, UART_INT_DMATX);

    MAP_uDMAChannelEnable(hwAttrs->txDmaChannel);

    HwiP_restore(key);
}

/*
 *  ======== getPowerMgrId ========
 */
static uint_fast16_t getPowerMgrId(uint32_t baseAddr)
{
    switch (baseAddr) {
        case UARTA0_BASE:
            return (PowerCC32XX_PERIPH_UARTA0);
        case UARTA1_BASE:
            return (PowerCC32XX_PERIPH_UARTA1);
        default:
            return ((uint_fast16_t)(~0U));
    }
}

/*
 *  ======== initHw ========
 */
static void initHw(UART2_Handle handle)
{
    UART2CC32XX_Object        *object = handle->object;
    UART2CC32XX_HWAttrs const *hwAttrs = handle->hwAttrs;
    ClockP_FreqHz              freq;
    unsigned long              mode = UART_FLOWCONTROL_NONE;

    ClockP_getCpuFreq(&freq);
    MAP_UARTConfigSetExpClk(hwAttrs->baseAddr, freq.lo, object->baudRate,
                            dataLength[object->dataLength] |
                            stopBits[object->stopBits] |
                            parityType[object->parityType]);

    /* Clear all UART interrupts */
    UARTIntClear(hwAttrs->baseAddr, UART_INT_OE | UART_INT_BE | UART_INT_PE |
                                    UART_INT_FE | UART_INT_RT | UART_INT_TX |
                                    UART_INT_RX | UART_INT_CTS | UART_INT_EOT);

    UARTEnable(hwAttrs->baseAddr);

    UARTIntEnable(hwAttrs->baseAddr, UART_INT_RX | UART_INT_RT | UART_INT_OE |
                  UART_INT_BE | UART_INT_PE | UART_INT_FE | UART_INT_EOT);

    MAP_UARTFIFOLevelSet(hwAttrs->baseAddr, txFifoThreshold[hwAttrs->txIntFifoThr],
                         rxFifoThreshold[hwAttrs->rxIntFifoThr]);

    if (isFlowControlEnabled(hwAttrs)) {
        /* Set flow control */
        if (hwAttrs->ctsPin != UART2CC32XX_PIN_UNASSIGNED) {
            mode = UART_FLOWCONTROL_TX;
        }

        if (hwAttrs->rtsPin != UART2CC32XX_PIN_UNASSIGNED) {
            mode |= UART_FLOWCONTROL_RX;
        }
    }
    MAP_UARTFlowControlSet(hwAttrs->baseAddr, mode);

    if (hwAttrs->rxPin != UART2CC32XX_PIN_UNASSIGNED) {
        MAP_uDMAChannelAssign(hwAttrs->rxDmaChannel);

        uDMAChannelAttributeDisable(hwAttrs->rxDmaChannel, (UDMA_ATTR_ALTSELECT |
                                                            UDMA_ATTR_USEBURST |
                                                            UDMA_ATTR_REQMASK));
    }

    if (hwAttrs->txPin != UART2CC32XX_PIN_UNASSIGNED) {
        MAP_uDMAChannelAssign(hwAttrs->txDmaChannel);

        uDMAChannelAttributeDisable(hwAttrs->txDmaChannel, (UDMA_ATTR_ALTSELECT |
                                                            UDMA_ATTR_USEBURST |
                                                            UDMA_ATTR_REQMASK));
    }
}

/*
 *  ======== postNotifyFxn ========
 *  Called by Power module when waking up from LPDS.
 */
static int postNotifyFxn(unsigned int eventType, uintptr_t eventArg,
        uintptr_t clientArg)
{
    /* Reconfigure the hardware if returning from sleep */
    initHw((UART2_Handle) clientArg);

    return (Power_NOTIFYDONE);
}

/*
 *  ======== cancelDmaRx ========
 *  Stop the current DMA receive transfer.
 */
static void cancelDmaRx(UART2_Handle handle)
{
    UART2CC32XX_Object        *object = handle->object;
    UART2CC32XX_HWAttrs const *hwAttrs = handle->hwAttrs;
    uint32_t                   bytesRemaining;
    uintptr_t                  key;

    if ((object->state.readReturnMode == UART2_ReadReturnMode_PARTIAL) ||
        (object->state.readMode == UART2_Mode_POLLING)) {
        return;
    }

    /* Disable interrupts to avoid reading data while changing state. */
    key = HwiP_disable();

    MAP_uDMAChannelDisable(hwAttrs->rxDmaChannel);
    uartDmaDisable(hwAttrs->baseAddr, UART_DMA_RX);
    
    UARTIntDisable(hwAttrs->baseAddr, UART_INT_DMARX);
    UARTIntClear(hwAttrs->baseAddr, UART_INT_DMARX);

    /* Return if there is no read. */
    if (object->readSize == 0) {
        HwiP_restore(key);
        return;
    }

    bytesRemaining = MAP_uDMAChannelSizeGet(hwAttrs->rxDmaChannel);
    object->bytesRead += object->readCount - bytesRemaining;

    /*
     *  Since object->readSize != 0, the ISR has not run and released
     *  the Power constraint.  Release the constraint here.  Setting
     *  object->readSize to 0 will prevent the ISR from releasing the
     *  constraint in case it is pending.
     */
    Power_releaseConstraint(PowerCC32XX_DISALLOW_LPDS);

    HwiP_restore(key);
}

/*
 *  ======== readData ========
 */
static int32_t readData(UART2_Handle handle, int32_t size)
{
    UART2CC32XX_Object        *object = handle->object;
    UART2CC32XX_HWAttrs const *hwAttrs = handle->hwAttrs;
    int32_t                    data;

    if (size > object->readCount) {
        size = object->readCount;
    }

    while (size) {
        data = UARTCharGetNonBlocking(hwAttrs->baseAddr);
        if (data == -1) {
            break;
        }
        *(object->readBuf + object->bytesRead) = (uint8_t)(data & 0xFF);
        object->bytesRead++;
        object->readCount--;
        size--;
    }

    return (size);
}

/*
 *  ======== readDone ========
 *  Called from the ISR only.
 */
static void readDone(UART2_Handle handle)
{
    UART2CC32XX_Object *object = handle->object;
    size_t              count;

    /* Return if no ongoing read */
    if (object->readSize == 0) {
        return;
    }

    count = object->bytesRead;

    Power_releaseConstraint(PowerCC32XX_DISALLOW_LPDS);

    /* Set readSize to 0 to allow UART2_read() to be called */
    object->readSize = 0;
    
    object->readCallback(handle, object->readBuf, count, object->userArg,
                         object->rxStatus);
}

/*
 *  ======== readSemCallback ========
 *  Simple callback to post a semaphore for the blocking mode.
 */
static void readSemCallback(UART2_Handle handle, void *buffer, size_t count,
        void *userArg, int_fast16_t status)
{
    UART2CC32XX_Object *object = handle->object;

    SemaphoreP_post(object->readSem);
}

/*
 *  ======== writeSemCallback ========
 *  Simple callback to post a semaphore for the blocking mode.
 */
static void writeSemCallback(UART2_Handle handle, void *buffer, size_t count,
        void *userArg, int_fast16_t status)
{
    UART2CC32XX_Object *object = handle->object;

    SemaphoreP_post(object->writeSem);
}
