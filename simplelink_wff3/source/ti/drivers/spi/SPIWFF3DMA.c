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
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_spi.h)
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(driverlib/dma.h)
#include DeviceFamily_constructPath(driverlib/spi.h)

#include <ti/drivers/dma/DMAWFF3.h>
#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/dpl/SwiP.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/spi/SPIWFF3DMA.h>

/* Headers required for intrinsics */
#if defined(__TI_COMPILER_VERSION__)
    #include <arm_acle.h>
#elif defined(__GNUC__)
    #include <arm_acle.h>
#elif defined(__IAR_SYSTEMS_ICC__)
    #include <intrinsics.h>
#else
    #error "Unsupported compiler"
#endif

/* Options for DMA write and read */
#define SPI_TX_DMA_CONTROL_OPTS (DMAWFF3_CONFIG_DST_PTR_FIFO | DMAWFF3_CONFIG_CLEAR_AT_JOB_START | DMAWFF3_CONFIG_TX)
#define SPI_RX_DMA_CONTROL_OPTS (DMAWFF3_CONFIG_SRC_PTR_FIFO | DMAWFF3_CONFIG_CLEAR_AT_JOB_START | DMAWFF3_CONFIG_RX)

#define MAX_DMA_TRANSFER_AMOUNT 0x00003FFFU

#define SPI_TX_DMA_BLOCK_SIZE (1)
#define SPI_RX_DMA_BLOCK_SIZE (1)

#define SPI_DATASIZE_8      (8)
#define SPI_DATASIZE_16     (16)
#define PARAMS_DATASIZE_MIN SPI_DATASIZE_8
#define PARAMS_DATASIZE_MAX SPI_DATASIZE_16

/* API Function Prototypes */
void SPIWFF3DMA_close(SPI_Handle handle);
int_fast16_t SPIWFF3DMA_control(SPI_Handle handle, uint_fast16_t cmd, void *arg);
void SPIWFF3DMA_init(SPI_Handle handle);
SPI_Handle SPIWFF3DMA_open(SPI_Handle handle, SPI_Params *params);
static void SPIWFF3DMA_swiFxn(uintptr_t arg0, uintptr_t arg1);
bool SPIWFF3DMA_transfer(SPI_Handle handle, SPI_Transaction *transaction);
void SPIWFF3DMA_transferCancel(SPI_Handle handle);

/* Local Function Prototypes */
static void SPIWFF3DMA_blockingTransferCallback(SPI_Handle handle, SPI_Transaction *msg);
static void SPIWFF3DMA_configNextTransfer(SPIWFF3DMA_Object *object, SPIWFF3DMA_HWAttrs const *hwAttrs);
static void SPIWFF3DMA_startDmaTransaction(SPIWFF3DMA_Object *object, SPIWFF3DMA_HWAttrs const *hwAttrs);
static void SPIWFF3DMA_csnCallback(uint_least8_t);
static void SPIWFF3DMA_flushFifos(SPIWFF3DMA_HWAttrs const *hwAttrs);
static bool SPIWFF3DMA_initHw(SPI_Handle handle);
static void SPIWFF3DMA_initIO(SPI_Handle handle);
static void SPIWFF3DMA_finalizeIO(SPI_Handle handle);
static void SPIWFF3DMA_setIOSleepState(SPI_Handle handle);
static inline void SPIWFF3DMA_primeTransfer(SPI_Handle handle);
static inline void SPIWFF3DMA_releaseConstraint(uint32_t txBufAddr);
static inline void SPIWFF3DMA_setConstraint(uint32_t txBufAddr);
static inline void SPIWFF3DMA_spiPollingTransfer(SPI_Handle handle, SPI_Transaction *transaction);
static int SPIWFF3DMA_spiPostNotify(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg);
static inline bool SPIWFF3DMA_spiBusy(SPIWFF3DMA_Object *object, SPIWFF3DMA_HWAttrs const *hwAttrs);
static inline void SPIWFF3DMA_disableSPI(uint32_t baseAddr);
static inline void SPIWFF3DMA_enableSPI(SPI_Handle handle);
static inline bool SPIWFF3DMA_isSPIEnabled(SPI_Handle handle);
static inline void SPIWFF3DMA_enableInterrupt(uint32_t baseAddr, uint32_t irqs);
static inline void SPIWFF3DMA_disableInterrupt(uint32_t baseAddr, uint32_t irqs);
static inline void SPIWFF3DMA_clearInterrupt(uint32_t baseAddr, uint32_t irqs);
static void SPIWFF3DMA_initDMA(SPI_Handle handle);
static void SPIWFF3DMA_enableDMA(uint32_t baseAddr, uint32_t dmaFlags);
static void SPIWFF3DMA_disableDMA(uint32_t baseAddr, uint32_t dmaFlags);
static inline uint32_t SPIWFF3DMA_getInterruptStatus(uint32_t baseAddr, bool masked);
static bool SPIWFF3DMA_configSPI(uint32_t baseAddr,
                                 uint32_t freq,
                                 uint32_t format,
                                 uint32_t mode,
                                 uint32_t bitRate,
                                 uint32_t dataSize,
                                 uint32_t dsample);
static int32_t SPIWFF3DMA_dataPutNonBlocking(uint32_t baseAddr, uint32_t frame);
static void SPIWFF3DMA_dataGet(uint32_t baseAddr, uint32_t *frame);
static bool SPIWFF3DMA_isSPIBusy(uint32_t baseAddr);

/* RX FIFO over flowed, data was lost */
#define SPI_INT_RXOF   (SPI_MIS_RXOVF_SET)
/* RX FIFO trigger level was passed */
#define SPI_INT_RXFF   (SPI_MIS_RX_SET)
/* TX FIFO trigger level was passed */
#define SPI_INT_TXFF   (SPI_MIS_TX_SET)
/* Transfer complete, HW is idle */
#define SPI_INT_IDLE   (SPI_MIS_IDLE_SET)
/* Subset of SPI interrupts used by this driver */
#define SPI_INT_SUBSET (SPI_INT_TXFF | SPI_INT_RXFF | SPI_INT_RXOF | SPI_INT_IDLE)
/* All SPI interrupts */
#define SPI_INT_ALL \
    (SPI_INT_SUBSET | SPI_MIS_TXEMPTY_SET | SPI_MIS_PER_SET | SPI_MIS_RTOUT_SET | SPI_MIS_DMARX_SET | SPI_MIS_DMATX_SET)

/* DSAMPLE default value limits based bit rate */
#define DSAMPLE_MED_BITRATE  4000000
#define DSAMPLE_HIGH_BITRATE 8000000

/* Sampling delay value */
#define DSAMPLE_MAX_CYCLES 0xF0000U

/* Maximum serial clock divider value */
#define SERIAL_CLK_DIVIDER_MAX 0x3FFU

/* SPI function table for SPIWFF3DMA implementation */
const SPI_FxnTable SPIWFF3DMA_fxnTable = {SPIWFF3DMA_close,
                                          SPIWFF3DMA_control,
                                          SPIWFF3DMA_init,
                                          SPIWFF3DMA_open,
                                          SPIWFF3DMA_transfer,
                                          SPIWFF3DMA_transferCancel};

static const uint32_t mode[] = {
    /* SPI_CONTROLLER */
    SPI_MODE_CONTROLLER,
    /* SPI_PERIPHERAL */
    SPI_MODE_PERIPHERAL,
};

/* Mapping SPI frame format from generic driver to driverlib */
static const uint32_t frameFormat[] = {
    /* SPI_POL0_PHA0 */
    (SPI_CTL0_FRF_MOTOROLA_3WIRE | SPI_CTL0_SPO_LOW | SPI_CTL0_SPH_FIRST),
    /* SPI_POL0_PHA1 */
    (SPI_CTL0_FRF_MOTOROLA_3WIRE | SPI_CTL0_SPO_LOW | SPI_CTL0_SPH_SECOND),
    /* SPI_POL1_PHA0 */
    (SPI_CTL0_FRF_MOTOROLA_3WIRE | SPI_CTL0_SPO_HIGH | SPI_CTL0_SPH_FIRST),
    /* SPI_POL1_PHA1 */
    (SPI_CTL0_FRF_MOTOROLA_3WIRE | SPI_CTL0_SPO_HIGH | SPI_CTL0_SPH_SECOND),
    /* SPI_TI */
    (SPI_CTL0_FRF_TI_SYNC),
    /* SPI_MW */
    (SPI_CTL0_FRF_MICROWIRE),
};

/*
 *  ======== SPIWFF3DMA_close ========
 */
void SPIWFF3DMA_close(SPI_Handle handle)
{
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Disable the SPI */
    SPIWFF3DMA_disableSPI(hwAttrs->baseAddr);

    HwiP_destruct(&(object->hwi));

    SwiP_destruct(&(object->swi));

    if (object->transferMode == SPI_MODE_BLOCKING)
    {
        SemaphoreP_destruct(&(object->transferComplete));
    }

    SPIWFF3DMA_finalizeIO(handle);

    Power_releaseDependency(hwAttrs->powerID);

    Power_unregisterNotify(&object->spiPostObj);

    object->isOpen = false;
}

/*!
 *  ======== SPIWFF3DMA_control ========
 *  @brief  Function for setting control parameters of the SPI driver
 *          after it has been opened.
 *
 *  @pre    SPIWFF3DMA_open() has to be called first.
 *          Calling context: Hwi, Swi, Task
 *
 *  @param  handle A SPI handle returned from SPIWFF3DMA_open()
 *
 *  @param  cmd  The command to execute, supported commands are:
 *  | Command                                   | Description                  |
 *  |-------------------------------------------|------------------------------|
 *  | ::SPIWFF3DMA_CMD_RETURN_PARTIAL_ENABLE  | Enable RETURN_PARTIAL        |
 *  | ::SPIWFF3DMA_CMD_RETURN_PARTIAL_DISABLE | Disable RETURN_PARTIAL       |
 *  | ::SPIWFF3DMA_CMD_SET_CSN_PIN            | Re-configure chip select pin |
 *  | ::SPIWFF3DMA_CMD_SET_MANUAL             | Enable manual start mode     |
 *  | ::SPIWFF3DMA_CMD_CLR_MANUAL             | Disable manual start mode    |
 *  | ::SPIWFF3DMA_CMD_MANUAL_START           | Perform a manual start       |
 *  | ::SPIWFF3DMA_CMD_SET_SAMPLE_DELAY       | Set a custom DSAMPLE value   |
 *
 *  @param  *arg  Pointer to command arguments.
 *
 *  @return ::SPI_STATUS_SUCCESS if success, or error code if error.
 */
int_fast16_t SPIWFF3DMA_control(SPI_Handle handle, uint_fast16_t cmd, void *arg)
{
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;
    uint_least8_t pinIndex;
    uint_least8_t sampleDelay;

    /* Initialize return value */
    int ret = SPI_STATUS_ERROR;

    /* Perform command */
    switch (cmd)
    {
        case SPIWFF3DMA_CMD_RETURN_PARTIAL_ENABLE:
            /* Enable RETURN_PARTIAL if peripheral mode is enabled */

            if (object->mode == SPI_PERIPHERAL)
            {
                object->returnPartial = SPIWFF3DMA_retPartEnabledIntNotSet;
                ret                   = SPI_STATUS_SUCCESS;
            }
            else
            {
                /* Partial return not available in controller mode. */
                ret = SPI_STATUS_ERROR;
            }
            break;

        case SPIWFF3DMA_CMD_RETURN_PARTIAL_DISABLE:
            GPIO_setInterruptConfig(object->csnPin, GPIO_CFG_INT_DISABLE);
            object->returnPartial = SPIWFF3DMA_retPartDisabled;
            ret                   = SPI_STATUS_SUCCESS;
            break;

        case SPIWFF3DMA_CMD_SET_CSN_PIN:
            pinIndex = *((uint_least8_t *)arg);

            if (pinIndex == GPIO_INVALID_INDEX)
            {
                /* If trying to disable the CS pin, forward to the CLEAR_CS command and break */
                ret = SPIWFF3DMA_control(handle, SPIWFF3DMA_CMD_CLEAR_CSN_PIN, NULL);
                break;
            }

            /* Reset the previous CS pin and configure the new one */
            GPIO_resetConfig(object->csnPin);
            object->csnPin = pinIndex;
            GPIO_setConfigAndMux(object->csnPin, GPIO_CFG_INPUT, hwAttrs->csnPinMux);

            ret = SPI_STATUS_SUCCESS;
            break;

        case SPIWFF3DMA_CMD_CLEAR_CSN_PIN:
            /* If the CS pin is assigned, reset and unassign it */
            if (object->csnPin != GPIO_INVALID_INDEX)
            {
                GPIO_resetConfig(object->csnPin);
                object->csnPin = GPIO_INVALID_INDEX;
            }
            ret = SPI_STATUS_SUCCESS;
            break;

        case SPIWFF3DMA_CMD_SET_MANUAL:
            /* If a transaction is queued, do not modify */
            if (object->headPtr == NULL)
            {
                object->manualStart = true;
                ret                 = SPI_STATUS_SUCCESS;
            }
            break;

        case SPIWFF3DMA_CMD_CLR_MANUAL:
            /* If a transaction is queued, do not modify */
            if (object->headPtr == NULL)
            {
                object->manualStart = false;
                ret                 = SPI_STATUS_SUCCESS;
            }
            break;

        case SPIWFF3DMA_CMD_MANUAL_START:
            if (object->headPtr != NULL && object->manualStart)
            {
                SPIWFF3DMA_enableSPI(handle);
                SPIWFF3DMA_startDmaTransaction(object, hwAttrs);
                ret = SPI_STATUS_SUCCESS;
            }
            break;

        case SPIWFF3DMA_CMD_SET_SAMPLE_DELAY:
            sampleDelay = *((uint_least8_t *)arg);

            if (object->mode == SPI_CONTROLLER && sampleDelay <= (DSAMPLE_MAX_CYCLES >> SPI_CLKCFG1_DSAMPLE_S))
            {
                /* Cache the value so it is persistent across standby */
                object->dsample = sampleDelay << SPI_CLKCFG1_DSAMPLE_S;

                HWREG(hwAttrs->baseAddr + SPI_O_CLKCFG1) &= ~SPI_CLKCFG1_DSAMPLE_M;
                HWREG(hwAttrs->baseAddr + SPI_O_CLKCFG1) |= object->dsample;
                ret = SPI_STATUS_SUCCESS;
            }
            break;

        default:
            /* This command is not defined */
            ret = SPI_STATUS_UNDEFINEDCMD;
            break;
    }

    return (ret);
}

static void SPIWFF3DMA_startDmaTransaction(SPIWFF3DMA_Object *object, SPIWFF3DMA_HWAttrs const *hwAttrs)
{
    SPIWFF3DMA_enableDMA(hwAttrs->baseAddr, SPI_DMACR_TXEN | SPI_DMACR_RXEN);

    DMAWFF3_startTransaction(hwAttrs->rxDmaChannel,
                             object->dmaRxSrcAddr,
                             object->dmaRxDstAddr,
                             object->dmaRxTransferSize,
                             true);

    DMAWFF3_startTransaction(hwAttrs->txDmaChannel,
                             object->dmaTxSrcAddr,
                             object->dmaTxDstAddr,
                             object->dmaTxTransferSize,
                             true);
}

/*
 *  ======== SPIWFF3DMA_hwiFxn ========
 */
static void SPIWFF3DMA_hwiFxn(uintptr_t arg)
{
    uint32_t intStatus;
    SPI_Transaction *completedList;
    size_t *transferSize;
    SPIWFF3DMA_Object *object         = ((SPI_Handle)arg)->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = ((SPI_Handle)arg)->hwAttrs;
    uintptr_t key;

    intStatus = SPIWFF3DMA_getInterruptStatus(hwAttrs->baseAddr, true);
    SPIWFF3DMA_clearInterrupt(hwAttrs->baseAddr, intStatus);

    if (intStatus & SPI_MIS_RXOVF_SET)
    {
        if (object->headPtr != NULL)
        {
            /*
             * RX overrun during a transfer; mark the current transfer
             * as failed & cancel all remaining transfers.
             */
            object->headPtr->status = SPI_TRANSFER_FAILED;

            SPIWFF3DMA_transferCancel((SPI_Handle)arg);
        }
        else
        {
            SPIWFF3DMA_disableSPI(hwAttrs->baseAddr);

            /* Disable DMA and clear DMA interrupts */
            SPIWFF3DMA_disableDMA(hwAttrs->baseAddr, SPI_DMACR_TXEN | SPI_DMACR_RXEN);
            DMAWFF3_disableChannel(hwAttrs->rxDmaChannel);
            DMAWFF3_disableChannel(hwAttrs->txDmaChannel);
            DMAWFF3_clearInterrupt(1 << hwAttrs->txDmaChannel | 1 << hwAttrs->rxDmaChannel);

            SPIWFF3DMA_disableInterrupt(hwAttrs->baseAddr, SPI_INT_ALL);
            SPIWFF3DMA_clearInterrupt(hwAttrs->baseAddr, SPI_INT_ALL);

            /* Clear out the FIFO by resetting SPI module and re-initting */
            SPIWFF3DMA_flushFifos(hwAttrs);
        }
    }
    else
    {
        DMAWFF3_clearInterrupt(1 << hwAttrs->txDmaChannel | 1 << hwAttrs->rxDmaChannel);

        transferSize = &object->transferSize;

        if (DMAWFF3_getRemainingBytes(hwAttrs->txDmaChannel) == 0 &&
            DMAWFF3_getRemainingBytes(hwAttrs->rxDmaChannel) == 0 && object->framesQueued == object->headPtr->count &&
            object->headPtr->nextPtr == NULL)
        {
            SPIWFF3DMA_disableDMA(hwAttrs->baseAddr, SPI_DMACR_TXEN);
            DMAWFF3_clearInterrupt(1 << hwAttrs->txDmaChannel);
        }

        if (DMAWFF3_getRemainingBytes(hwAttrs->rxDmaChannel) == 0 && (intStatus & SPI_MIS_DMARX_SET) &&
            *transferSize != 0)
        {
            object->framesTransferred += *transferSize;
            *transferSize = 0;

            if ((object->framesQueued) < (object->headPtr->count) ||
                (object->framesTransferred) < (object->headPtr->count))
            {
                /*
                 * In this case we need to reconfigure the channel to
                 * continue transferring frames. SPIWFF3DMA_configNextTransfer() will
                 * continue queueing frames for the current transfer and
                 * start the next transaction.
                 */

                SPIWFF3DMA_configNextTransfer(object, hwAttrs);
                SPIWFF3DMA_startDmaTransaction(object, hwAttrs);
            }
            else
            {
                key                     = HwiP_disable();
                /*
                 * All data has been transferred for the current
                 * transaction. Set status & move the transaction to
                 * object->completedList. This is required because
                 * object->headPtr is moved to the following transaction.
                 * Also, transaction callbacks are executed in the driver
                 * SWI which will be posted later.
                 */
                object->headPtr->status = SPI_TRANSFER_COMPLETED;

                if (object->completedTransfers == NULL)
                {
                    /* List is empty; just add the transaction */
                    object->completedTransfers = object->headPtr;
                    completedList              = object->completedTransfers;
                }
                else
                {
                    /* Traverse to the last element */
                    completedList = object->completedTransfers;
                    while (completedList->nextPtr != NULL)
                    {
                        completedList = completedList->nextPtr;
                    }

                    /* Store the completed transaction at end of list */
                    completedList->nextPtr = object->headPtr;

                    /*
                     * Make sure we are pointing to the end of the list;
                     * we need to clear references in completed transfer
                     * after we move object->headPtr forward.
                     */
                    completedList = completedList->nextPtr;
                }

                /* Move the object->headPtr to the next transaction */
                object->headPtr = object->headPtr->nextPtr;

                /* Clear references in completed transfer */
                completedList->nextPtr = NULL;

                /* Update object variables for the following transfer. */
                object->framesQueued      = object->transferSize;
                object->framesTransferred = 0;

                HwiP_restore(key);

                if (object->headPtr != NULL)
                {
                    SPIWFF3DMA_configNextTransfer(object, hwAttrs);
                    SPIWFF3DMA_startDmaTransaction(object, hwAttrs);
                }
                else
                {
                    /* No more queued transfers; disable DMA & SPI */
                    SPIWFF3DMA_disableDMA(hwAttrs->baseAddr, SPI_DMACR_TXEN | SPI_DMACR_RXEN);

                    /*
                     * For this driver implementation the peripheral is kept
                     * active until either a FIFO-overrun occurs or
                     * SPI_transferCancel() is executed.
                     */
                }

                /* Post driver SWI to execute transaction callbacks */
                SwiP_post(&(object->swi));
            }
        }
    }
}

/*
 *  ======== SPIWFF3DMA_init ========
 */
void SPIWFF3DMA_init(SPI_Handle handle)
{
    ((SPIWFF3DMA_Object *)handle->object)->isOpen = false;
}

/*
 *  ======== SPIWFF3DMA_open ========
 */
SPI_Handle SPIWFF3DMA_open(SPI_Handle handle, SPI_Params *params)
{
    union
    {
        HwiP_Params hwiParams;
        SwiP_Params swiParams;
    } paramsUnion;
    uint32_t key;
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;

    key = HwiP_disable();

    /* Failure conditions */
    if (object->isOpen || params->dataSize > PARAMS_DATASIZE_MAX || params->dataSize < PARAMS_DATASIZE_MIN)
    {
        HwiP_restore(key);

        return (NULL);
    }
    object->isOpen = true;

    HwiP_restore(key);

    DebugP_assert((params->dataSize >= PARAMS_DATASIZE_MIN) && (params->dataSize <= PARAMS_DATASIZE_MAX));

    object->bitRate            = params->bitRate;
    object->dataSize           = params->dataSize;
    object->mode               = params->mode;
    object->transferMode       = params->transferMode;
    object->transferTimeout    = params->transferTimeout;
    object->returnPartial      = SPIWFF3DMA_retPartDisabled;
    object->headPtr            = NULL;
    object->tailPtr            = NULL;
    object->completedTransfers = NULL;
    object->format             = params->frameFormat;
    object->txScratchBuf       = hwAttrs->defaultTxBufValue;
    object->busyBit            = (params->mode == SPI_CONTROLLER ? SPI_STA_BUSY : SPI_STA_TFE);
    object->manualStart        = false;

    /*
     * Set a default dsample value based on the bitRate
     * DSAMPLE can be changed later by the user using the SPI_control() API with
     * the CMD_SET_SAMPLE_DELAY option.
     */
    object->dsample = 0;
    if (object->bitRate >= DSAMPLE_MED_BITRATE)
    {
        object->dsample = 1 << SPI_CLKCFG1_DSAMPLE_S;
    }
    else if (object->bitRate >= DSAMPLE_HIGH_BITRATE)
    {
        object->dsample = 2 << SPI_CLKCFG1_DSAMPLE_S;
    }

    SPIWFF3DMA_initDMA(handle);

    /* Register power dependency - i.e. power up and enable clock for SPI. */
    Power_setDependency(hwAttrs->powerID);

    /*
     * Configure IOs after hardware has been initialized so that IOs aren't
     * toggled unnecessary
     */
    if (!SPIWFF3DMA_initHw(handle))
    {
        /*
         * Trying to use SPI driver when some other driver or application
         * has already allocated these pins, error!
         */
        Power_releaseDependency(hwAttrs->powerID);

        object->isOpen = false;
        return (NULL);
    }

    /* CS is initialized using hwAttrs, but can be re-configured later */
    object->csnPin = hwAttrs->csnPin;

    /*
     * IO configuration must occur before SPI IP is enabled
     * for peripheral mode.
     * For controller mode see SPIWFF3DMA_enableSPI().
     */
    if (object->mode == SPI_PERIPHERAL)
    {
        SPIWFF3DMA_initIO(handle);
    }

    HwiP_Params_init(&paramsUnion.hwiParams);
    paramsUnion.hwiParams.arg      = (uintptr_t)handle;
    paramsUnion.hwiParams.priority = hwAttrs->intPriority;
    HwiP_construct(&(object->hwi), (int)hwAttrs->intNum, SPIWFF3DMA_hwiFxn, &paramsUnion.hwiParams);

    SwiP_Params_init(&paramsUnion.swiParams);
    paramsUnion.swiParams.arg0     = (uintptr_t)handle;
    paramsUnion.swiParams.priority = hwAttrs->swiPriority;
    SwiP_construct(&(object->swi), SPIWFF3DMA_swiFxn, &(paramsUnion.swiParams));

    Power_registerNotify(&object->spiPostObj,
                         PowerWFF3_AWAKE_SLEEP | PowerWFF3_ENTERING_SLEEP,
                         (Power_NotifyFxn)SPIWFF3DMA_spiPostNotify,
                         (uint32_t)handle);

    if (object->transferMode == SPI_MODE_BLOCKING)
    {
        /*
         * Create a semaphore to block task execution for the duration of the
         * SPI transfer
         */
        SemaphoreP_constructBinary(&(object->transferComplete), 0);
        object->transferCallbackFxn = SPIWFF3DMA_blockingTransferCallback;
    }
    else
    {
        DebugP_assert(params->transferCallbackFxn != NULL);
        object->transferCallbackFxn = params->transferCallbackFxn;
    }

    return (handle);
}

/*
 *  ======== SPIWFF3DMA_swiFxn ========
 */
static void SPIWFF3DMA_swiFxn(uintptr_t arg0, uintptr_t arg1)
{
    SPI_Transaction *transaction;
    SPIWFF3DMA_Object *object = ((SPI_Handle)arg0)->object;
    uintptr_t key;

    /* To protect against any Linked-List manipulation, we took ownership of the processor and disabled interrupts
     * This also includes the while loop check here, since another process might temporarily tamper with
     * object->copmoletedTransfers
     */
    key = HwiP_disable();

    while (object->completedTransfers != NULL)
    {
        transaction = object->completedTransfers;

        /* Move object->completedTransfers to the next transaction */
        object->completedTransfers = object->completedTransfers->nextPtr;

        transaction->nextPtr = NULL;

        /* Transaction complete; release power constraints */
        SPIWFF3DMA_releaseConstraint((uint32_t)transaction->txBuf);

        /* Inverted logic here to restore interrupts right before we jump to the callback function and disable them
         * after we return */
        HwiP_restore(key);

        /* Execute callback function for completed transfer */
        object->transferCallbackFxn((SPI_Handle)arg0, transaction);

        key = HwiP_disable();
    }

    /* Restore interrupts */
    HwiP_restore(key);
}

/*
 *  ======== SPIWFF3DMA_transfer ========
 */
bool SPIWFF3DMA_transfer(SPI_Handle handle, SPI_Transaction *transaction)
{
    uint8_t alignMask;
    bool buffersAligned;
    uintptr_t key;
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Queued transfers are not supported in peripheral mode */
    if (object->mode == SPI_PERIPHERAL && (object->headPtr || transaction->count > MAX_DMA_TRANSFER_AMOUNT))
    {
        return (false);
    }

    if (transaction->count == 0)
    {
        return (false);
    }

    key = HwiP_disable();

    /*
     * Make sure that the buffers are aligned properly.
     * alignMask is used to check if the RX/TX buffers addresses
     * are aligned to the frameSize.
     */
    if (object->dataSize <= SPI_DATASIZE_8)
    {
        alignMask = 0;
    }
    else
    {
        alignMask = 1;
    }

    buffersAligned = ((((uint32_t)transaction->rxBuf & alignMask) == 0) &&
                      (((uint32_t)transaction->txBuf & alignMask) == 0));

    if (!buffersAligned || (object->headPtr && object->transferMode == SPI_MODE_BLOCKING))
    {
        transaction->status = SPI_TRANSFER_FAILED;

        HwiP_restore(key);

        return (false);
    }
    else
    {
        if (object->headPtr)
        {
            object->tailPtr->nextPtr = transaction;
            object->tailPtr          = transaction;
            object->tailPtr->status  = SPI_TRANSFER_QUEUED;
        }
        else
        {
            object->headPtr = transaction;
            object->tailPtr = transaction;

            object->framesQueued      = 0;
            object->framesTransferred = 0;
            object->transferSize      = 0;
            object->tailPtr->status   = (object->returnPartial != SPIWFF3DMA_retPartDisabled)
                                            ? SPI_TRANSFER_PEND_CSN_ASSERT
                                            : SPI_TRANSFER_STARTED;
        }

        object->tailPtr->nextPtr = NULL;
    }

    /* In peripheral mode, optionally enable callback on CS de-assert */
    if (object->returnPartial == SPIWFF3DMA_retPartEnabledIntNotSet)
    {
        object->returnPartial = SPIWFF3DMA_retPartEnabledIntSet;
        GPIO_setInterruptConfig(object->csnPin, GPIO_CFG_IN_INT_RISING | GPIO_CFG_INT_ENABLE);
    }

    /* Set constraints to guarantee transaction */
    SPIWFF3DMA_setConstraint((uint32_t)transaction->txBuf);

    /*
     * Polling transfer if BLOCKING mode & transaction->count < threshold
     * Peripherals not allowed to use polling unless timeout is disabled
     * Polling not allowed with returnPartial mode
     */
    if (object->transferMode == SPI_MODE_BLOCKING && transaction->count < hwAttrs->minDmaTransferSize &&
        object->returnPartial == SPIWFF3DMA_retPartDisabled &&
        (object->mode == SPI_CONTROLLER || object->transferTimeout == SPI_WAIT_FOREVER))
    {
        HwiP_restore(key);

        SPIWFF3DMA_spiPollingTransfer(handle, transaction);

        /* Release constraint since transaction is done */
        SPIWFF3DMA_releaseConstraint((uint32_t)transaction->txBuf);

        /* Transaction completed; set status & mark SPI ready */
        object->headPtr->status = SPI_TRANSFER_COMPLETED;
        object->headPtr         = NULL;
        object->tailPtr         = NULL;
    }
    else
    {
        /*
         * Perform a DMA backed SPI transfer; we need exclusive access while
         * priming the transfer to prevent race conditions with
         * SPIWFF3DMA_transferCancel().
         */

        /* Enable DMA interrupts */
        SPIWFF3DMA_clearInterrupt(hwAttrs->baseAddr, SPI_INT_ALL);
        SPIWFF3DMA_enableInterrupt(hwAttrs->baseAddr, SPI_MIS_DMATX_SET | SPI_MIS_DMARX_SET);

        SPIWFF3DMA_primeTransfer(handle);

        /* Enable the RX overrun interrupt in the SPI module */
        SPIWFF3DMA_enableInterrupt(hwAttrs->baseAddr, SPI_MIS_RXOVF_SET);

        HwiP_restore(key);

        if (object->transferMode == SPI_MODE_BLOCKING)
        {
            if (SemaphoreP_OK != SemaphoreP_pend(&(object->transferComplete), object->transferTimeout))
            {
                /* Timeout occurred; cancel the transfer */
                object->headPtr->status = SPI_TRANSFER_FAILED;
                SPIWFF3DMA_transferCancel(handle);

                /*
                 * SPIWFF3DMA_transferCancel() performs callback which posts
                 * transferComplete semaphore. This call consumes this extra
                 * post.
                 */
                SemaphoreP_pend(&(object->transferComplete), SemaphoreP_NO_WAIT);

                return (false);
            }
        }
    }

    return (true);
}

/*
 *  ======== SPIWFF3DMA_transferCancel ========
 */
void SPIWFF3DMA_transferCancel(SPI_Handle handle)
{
    uintptr_t key;
    uint32_t temp;
    uint8_t dmaFrameSize;
    SPI_Transaction *tempPtr;
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;

    /*
     * Acquire exclusive access to the driver. Required to prevent race
     * conditions if preempted by code trying to configure another transfer.
     */
    key = HwiP_disable();

    if (object->headPtr == NULL)
    {

        /*
         * Disable the SPI peripheral in case the peripherals finite state
         * machine is in a bad state. Calling SPI_transfer() will re-enable
         * the peripheral.
         */
        SPIWFF3DMA_disableSPI(hwAttrs->baseAddr);
        HwiP_restore(key);

        return;
    }

    /*
     * There are 2 use cases in which to call transferCancel():
     *   1.  The driver is in CALLBACK mode.
     *   2.  The driver is in BLOCKING mode & there has been a transfer timeout.
     */
    if (object->transferMode != SPI_MODE_BLOCKING || object->headPtr->status == SPI_TRANSFER_FAILED ||
        object->headPtr->status == SPI_TRANSFER_CSN_DEASSERT)
    {

        /* Prevent interrupt while canceling the transfer */
        HwiP_disableInterrupt(hwAttrs->intNum);

        /*
         * Disable the TX DMA channel first to stop feeding more frames to
         * the FIFO.  Next, wait until the TX FIFO is empty (all frames in
         * FIFO have been sent).  RX DMA channel is disabled later to allow
         * the DMA to move all frames already in FIFO to memory.
         */
        DMAWFF3_disableChannel(hwAttrs->txDmaChannel);

        if (object->mode == SPI_CONTROLLER)
        {
            /*
             * Wait until the TX FIFO is empty; this is to make sure the
             * chip select is deasserted before disabling the SPI.
             */
            while (SPIWFF3DMA_isSPIBusy(hwAttrs->baseAddr)) {}
        }

        SPIWFF3DMA_disableSPI(hwAttrs->baseAddr);

        /* Now disable the RX, DMA & interrupts */
        DMAWFF3_disableChannel(hwAttrs->rxDmaChannel);
        SPIWFF3DMA_disableDMA(hwAttrs->baseAddr, SPI_DMACR_TXEN | SPI_DMACR_RXEN);
        DMAWFF3_clearInterrupt(1 << hwAttrs->txDmaChannel | 1 << hwAttrs->rxDmaChannel);
        SPIWFF3DMA_disableInterrupt(hwAttrs->baseAddr, SPI_INT_ALL);
        SPIWFF3DMA_clearInterrupt(hwAttrs->baseAddr, SPI_INT_ALL);

        /*
         * Update transaction->count with the amount of frames which have
         * been transferred.
         */
        object->headPtr->count = object->framesTransferred;
        if (object->transferSize)
        {
            dmaFrameSize = (object->dataSize <= SPI_DATASIZE_8 ? 1 : 2);
            temp = (object->dmaRxTransferSize - DMAWFF3_getRemainingBytes(hwAttrs->rxDmaChannel)) / dmaFrameSize;

            if (temp <= object->transferSize)
            {
                object->headPtr->count += (object->transferSize - temp);
            }
        }

        /*
         * Disables peripheral, clears all registers & reinitializes it to
         * parameters used in SPI_open()
         */
        SPIWFF3DMA_initHw(handle);

        HwiP_clearInterrupt(hwAttrs->intNum);

        /* Synchronize the instruction pipeline before enabling SPI interrupt
         * to ensure that interrupts are properly cleared.
         */
        __DMB();
        __DSB();
        __ISB();

        HwiP_enableInterrupt(hwAttrs->intNum);

        /* Synchronize the instruction pipeline after enabling SPI interrupt
         * to ensure that interrupts are properly enabled.
         * */
        __DMB();
        __DSB();
        __ISB();

        /*
         * Go through all queued transfers; set status CANCELED (if we did
         * not cancel due to timeout).  The object->headPtr->count is
         * stored/restored temporarily.
         */
        temp    = object->headPtr->count;
        tempPtr = object->headPtr;

        while (tempPtr != NULL)
        {
            if (tempPtr->status != SPI_TRANSFER_FAILED && tempPtr->status != SPI_TRANSFER_CSN_DEASSERT)
            {
                tempPtr->status = SPI_TRANSFER_CANCELED;
            }

            tempPtr->count = 0;
            tempPtr        = tempPtr->nextPtr;
        }
        object->headPtr->count = temp;

        /* Add all cancelled transactions to object->completedTransfers */
        tempPtr = object->completedTransfers;
        if (tempPtr == NULL)
        {
            /* Empty list; just add all of the cancelled transactions */
            object->completedTransfers = object->headPtr;
        }
        else
        {
            /* Move through the list until we reach the last element */
            while (tempPtr->nextPtr != NULL)
            {
                tempPtr = tempPtr->nextPtr;
            }

            /* Add all of the cancelled transactions */
            tempPtr->nextPtr = object->headPtr;
        }

        /* Clear all driver object variables*/
        object->headPtr           = NULL;
        object->tailPtr           = NULL;
        object->framesQueued      = 0;
        object->framesTransferred = 0;
        object->transferSize      = 0;

        HwiP_restore(key);

        /*
         * All transactions have been marked as cancelled & added to
         * object->completedTransfers.  Post the driver SWI to execute
         * callback functions.
         */
        SwiP_post(&(object->swi));

        /* Must return here; do not call HwiP_restore() twice */
        return;
    }

    HwiP_restore(key);
}

/*
 *  ======== SPIWFF3DMA_blockingTransferCallback ========
 */
static void SPIWFF3DMA_blockingTransferCallback(SPI_Handle handle, SPI_Transaction *msg)
{
    SPIWFF3DMA_Object *object = handle->object;
    SemaphoreP_post(&(object->transferComplete));
}

/*
 *  ======== SPIWFF3DMA_configNextTransfer ========
 *  This function must be executed with interrupts disabled.
 */
static void SPIWFF3DMA_configNextTransfer(SPIWFF3DMA_Object *object, SPIWFF3DMA_HWAttrs const *hwAttrs)
{
    size_t framesQueued;
    SPI_Transaction *transaction;
    uint8_t dmaFrameSize;

    /*
     * dmaFrameSize is the number of bytes required to fit a SPI frame.
     * It is used in determining value of dmaTxSrcAddr/dmaRxSrcAddr,
     * dmaTxTransferSize/dmaRxTransferSize, and the max number of SPI
     * frames that can transfer over DMA channel
     */
    dmaFrameSize = (object->dataSize <= SPI_DATASIZE_8 ? 1 : 2);

    /*
     * object->framesQueued keeps track of how many frames (of the current
     * transaction) have been configured for DMA transfer.  If
     * object->framesQueued == transaction->count; all frames have been queued
     * & we should configure the free DMA channel to send the next transaction.
     * When the current transaction has completed; object->framesQueued
     * will be updated (in the ISR) to reflect the amount of frames queued
     * of the following transaction.
     */
    transaction = object->headPtr;
    if (object->framesQueued < transaction->count)
    {
        framesQueued = object->framesQueued;
    }
    else
    {
        transaction = object->headPtr->nextPtr;
        if (transaction == NULL)
        {
            /* There are no queued transactions */
            return;
        }

        framesQueued        = 0;
        transaction->status = SPI_TRANSFER_STARTED;
    }

    /*
     * The DMA has a max transfer amount of 16383 bytes. If the transaction is
     * greater; we must transfer it in chunks.  framesQueued keeps track of
     * how much data has been queued for transfer.
     */
    if ((transaction->count - framesQueued) > (MAX_DMA_TRANSFER_AMOUNT / dmaFrameSize))
    {
        object->transferSize = (MAX_DMA_TRANSFER_AMOUNT / dmaFrameSize);
    }
    else
    {
        object->transferSize = transaction->count - framesQueued;
    }

    /* Setup the TX transfer buffers & characteristics */
    if (transaction->txBuf)
    {
        /*
         * Add an offset for the amount of data transferred.  The offset is
         * calculated by: object->framesQueued * (dmaFrameSize).  This
         * accounts for 8 or 16-bit sized transfers.
         */
        object->dmaTxSrcAddr = (void *)((uint32_t)transaction->txBuf + (uint32_t)(framesQueued * dmaFrameSize));
    }
    else
    {
        object->dmaTxSrcAddr = (void *)&(object->txScratchBuf);
    }
    object->dmaTxDstAddr      = (void *)(hwAttrs->baseAddr + SPI_O_TXDATA);
    object->dmaTxTransferSize = object->transferSize * dmaFrameSize;

    /* Setup the RX transfer buffers & characteristics */
    if (transaction->rxBuf)
    {
        /*
         * Add an offset for the amount of data transferred.  The offset is
         * calculated by: object->framesQueued * (dmaFrameSize).  This
         * accounts for 8 or 16-bit sized transfers.
         */
        object->dmaRxDstAddr = (void *)((uint32_t)transaction->rxBuf + (uint32_t)(framesQueued * dmaFrameSize));

        /* Make sure the RX DMA is incrementing the destination address. */
        DMADisableDestinationFifoMode(hwAttrs->rxDmaChannel);
    }
    else
    {
        /*
         * When the rxBuf pointer is NULL a scratch buffer (2 bytes) will be
         * used since the SPI transactions are always full-duplex. Configure the
         * DMA destination as FIFO to make sure it is not incrementing the
         * destination address.
         */
        DMAEnableDestinationFifoMode(hwAttrs->rxDmaChannel);

        object->dmaRxDstAddr = &object->rxScratchBuf;
    }
    object->dmaRxSrcAddr      = (void *)(hwAttrs->baseAddr + SPI_O_RXDATA);
    object->dmaRxTransferSize = object->transferSize * dmaFrameSize;

    if (transaction == object->headPtr)
    {
        /*
         * Only update object->framesQueued if we are configuring a DMA
         * channel for the current transaction.
         */
        object->framesQueued += object->transferSize;
    }
}

/*
 *  ======== SPIWFF3DMA_csnCallback ========
 *  Peripheral mode optional callback function for when the CS is asserted &
 *  deasserted.
 */
static void SPIWFF3DMA_csnCallback(uint_least8_t index)
{
    uintptr_t key;
    SPI_Handle spiHandle      = (SPI_Handle)GPIO_getUserArg(index);
    SPIWFF3DMA_Object *object = spiHandle->object;

    if (!GPIO_read(index))
    {
        /* Start transfer if CS goes low */
        key = HwiP_disable();
        if (object->headPtr != NULL)
        {
            /* We have data ready; indicate transaction started */
            object->headPtr->status = SPI_TRANSFER_STARTED;
        }
        else
        {
            /* We are not waiting to transfer; disable all interrupts */
            GPIO_setInterruptConfig(object->csnPin, GPIO_CFG_INT_DISABLE);
            object->returnPartial = SPIWFF3DMA_retPartEnabledIntNotSet;
        }
        HwiP_restore(key);
    }
    else
    {
        /* Cancel ongoing transfer if CS high */
        key = HwiP_disable();

        GPIO_setInterruptConfig(object->csnPin, GPIO_CFG_INT_DISABLE);
        object->returnPartial = SPIWFF3DMA_retPartEnabledIntNotSet;

        /* Indicate why the transaction completed */
        if (object->headPtr != NULL)
        {
            object->headPtr->status = SPI_TRANSFER_CSN_DEASSERT;
        }

        HwiP_restore(key);

        /* Cancel the current transaction */
        SPIWFF3DMA_transferCancel(spiHandle);
    }
}

/*
 *  ======== SPIWFF3DMA_flushFifos ========
 */
static void SPIWFF3DMA_flushFifos(SPIWFF3DMA_HWAttrs const *hwAttrs)
{
    /* Disable the SPI in case it isn't already */
    SPIWFF3DMA_disableSPI(hwAttrs->baseAddr);

    /* Trigger Fifo reset */
    HWREG(SPI0_BASE + SPI_O_CTL0) |= SPI_CTL0_FIFORST_RST_TRIG;

    while ((HWREG(SPI0_BASE + SPI_O_CTL0) & SPI_CTL0_FIFORST) == SPI_CTL0_FIFORST_RST_TRIG) {}
}

/*
 *  ======== SPIWFF3DMA_initHw ========
 */
static bool SPIWFF3DMA_initHw(SPI_Handle handle)
{
    ClockP_FreqHz freq                = {0, 0};
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;
    uint32_t format;

    SPIWFF3DMA_flushFifos(hwAttrs);

    /* Disable SSI operation */
    SPIWFF3DMA_disableSPI(hwAttrs->baseAddr);

    /* Disable SPI module interrupts */
    SPIWFF3DMA_disableInterrupt(hwAttrs->baseAddr, SPI_INT_ALL);
    SPIWFF3DMA_clearInterrupt(hwAttrs->baseAddr, SPI_INT_ALL);

    /* Get requested format */
    format = frameFormat[object->format];

    if ((hwAttrs->csnPin != GPIO_INVALID_INDEX) && (((format & SPI_CTL0_FRF_M) == SPI_CTL0_FRF_MOTOROLA_3WIRE) ||
                                                    (format & SPI_CTL0_FRF_M) == SPI_CTL0_FRF_MOTOROLA_4WIRE))
    {
        /*
         * A CS pin was specified, ensure SPI is in 4WIRE mode
         */
        format |= SPI_CTL0_FRF_MOTOROLA_4WIRE;
        SPISelectCSN(hwAttrs->baseAddr, hwAttrs->csnSel);
    }

    /* Set the SPI configuration */
    ClockP_getCpuFreq(&freq);

#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX
    /* On CC35XX, the SPI reference clock is half of CPU CLK (SOC CLK = 80 MHz) */
    freq.lo /= 2;
#endif

    if (freq.lo / 2 >= object->bitRate)
    {
        SPIWFF3DMA_configSPI(hwAttrs->baseAddr,
                             freq.lo,
                             format,
                             mode[object->mode],
                             object->bitRate,
                             object->dataSize,
                             object->dsample);
        return true;
    }
    return false;
}

/*
 *  ======== SPIWFF3DMA_initIO ========
 *  This functions initializes the SPI IOs.
 *
 *  @pre    Function assumes that the SPI handle is pointing to a hardware
 *          module which has already been opened.
 */
static void SPIWFF3DMA_initIO(SPI_Handle handle)
{
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;

    if (object->mode == SPI_PERIPHERAL)
    {
        GPIO_setConfigAndMux(hwAttrs->sclkPin, GPIO_CFG_INPUT, hwAttrs->sclkPinMux);
        GPIO_setConfigAndMux(hwAttrs->picoPin, GPIO_CFG_INPUT, hwAttrs->picoPinMux);
        GPIO_setConfigAndMux(hwAttrs->pociPin, GPIO_CFG_NO_DIR, hwAttrs->pociPinMux);
        GPIO_setConfigAndMux(object->csnPin, GPIO_CFG_INPUT, hwAttrs->csnPinMux);

        /* In peripheral mode, enable WU from STDBY on CSN */
        GPIO_setCallback(object->csnPin, SPIWFF3DMA_csnCallback);
        GPIO_setUserArg(object->csnPin, handle);
    }
    else
    {
        GPIO_setConfigAndMux(hwAttrs->sclkPin, GPIO_CFG_NO_DIR, hwAttrs->sclkPinMux);
        GPIO_setConfigAndMux(hwAttrs->picoPin, GPIO_CFG_NO_DIR, hwAttrs->picoPinMux);
        GPIO_setConfigAndMux(hwAttrs->pociPin, GPIO_CFG_INPUT, hwAttrs->pociPinMux);
        GPIO_setConfigAndMux(object->csnPin, GPIO_CFG_NO_DIR, hwAttrs->csnPinMux);
    }
}

/*
 *  ======== SPIWFF3DMA_finalizeIO ========
 *  This function releases the SPI IOs.
 */
static void SPIWFF3DMA_finalizeIO(SPI_Handle handle)
{
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;

    GPIO_resetConfig(hwAttrs->picoPin);
    GPIO_resetConfig(hwAttrs->pociPin);
    GPIO_resetConfig(hwAttrs->sclkPin);

    /* We always mux CS in peripheral mode, but as controller it can be SW-controlled (and therefore unmuxed) */
    if (object->mode == SPI_PERIPHERAL || object->csnPin != GPIO_INVALID_INDEX)
    {
        GPIO_resetConfig(object->csnPin);
    }
}

/*
 *  ======== SPIWFF3DMA_setIOSleepState ========
 *  This function releases the SPI IOs and resets pins back to initial user and GPIO Configurations.
 */
static void SPIWFF3DMA_setIOSleepState(SPI_Handle handle)
{
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;
    bool sclkIsActiveHigh             = (HWREG(hwAttrs->baseAddr + SPI_O_CTL0) & SPI_CTL0_SPO_M) != 0;

    /* CONFIG_GPIO_SPI_CONTROLLER_SCLK */
    GPIO_PinConfig sclkPinConfig = GPIO_CFG_OUTPUT_INTERNAL;

    /* CONFIG_GPIO_SPI_CONTROLLER_CSN */
    GPIO_PinConfig csnPinConfig = GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_HIGH;

    /* CONFIG_GPIO_SPI_CONTROLLER_POCI */
    GPIO_PinConfig picoPinConfig = GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_NONE_INTERNAL;

    /* CONFIG_GPIO_SPI_CONTROLLER_PICO */
    GPIO_PinConfig pociPinConfig = GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_LOW;

    if (object->mode == SPI_CONTROLLER)
    {
        GPIO_setConfig(object->csnPin, csnPinConfig);
        GPIO_setConfig(hwAttrs->picoPin, picoPinConfig);

        sclkPinConfig |= sclkIsActiveHigh ? GPIO_CFG_OUT_HIGH : GPIO_CFG_OUT_LOW;
        GPIO_setConfig(hwAttrs->sclkPin, sclkPinConfig);
    }
    else
    {
        GPIO_setConfig(hwAttrs->pociPin, pociPinConfig);
    }
}

/*
 *  ======== SPIWFF3DMA_primeTransfer ========
 *  Function must be executed with interrupts disabled.
 */
static inline void SPIWFF3DMA_primeTransfer(SPI_Handle handle)
{
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;

    if (object->transferSize == 0)
    {
        /* Mux RX DMA channel to SPI peripheral */
        DMAWFF3_connectChannel(hwAttrs->rxDmaChannel, hwAttrs->rxChannelEvtMux);

        /* Mux TX DMA channel to SPI peripheral */
        DMAWFF3_connectChannel(hwAttrs->txDmaChannel, hwAttrs->txChannelEvtMux);

        HwiP_clearInterrupt(hwAttrs->intNum);

        HwiP_enableInterrupt(hwAttrs->intNum);

        /* Configure RX & TX DMA transfers */
        SPIWFF3DMA_configNextTransfer(object, hwAttrs);

        if (!object->manualStart)
        {
            SPIWFF3DMA_enableSPI(handle);
            SPIWFF3DMA_startDmaTransaction(object, hwAttrs);
        }
    }
    else // (object->transferSize != 0)
    {
        /*
         * Channel is already configured for a transfer.
         * In this case no work is required; the Hwi will configure channel
         * as transfers continue & complete.
         */
    }
}

/*
 *  ======== SPIWFF3DMA_releaseConstraint ========
 */
static inline void SPIWFF3DMA_releaseConstraint(uint32_t txBufAddr)
{
    /* Release standby constraint since operation is done. */
    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);
}

/*
 *  ======== SPIWFF3DMA_setConstraint ========
 */
static inline void SPIWFF3DMA_setConstraint(uint32_t txBufAddr)
{
    /* Set constraints to guarantee operation */
    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);
}

/*
 *  ======== SPIWFF3DMA_spiPollingTransfer ========
 */
static inline void SPIWFF3DMA_spiPollingTransfer(SPI_Handle handle, SPI_Transaction *transaction)
{
    uint8_t txIncrement, rxIncrement;
    uint32_t dummyBuffer;
    size_t rxCount, txCount;
    void *rxBuf;
    void *txBuf;
    bool put;
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Only increment src/destination pointers if buffers were provided */
    if (transaction->rxBuf)
    {
        rxBuf = transaction->rxBuf;
        if (object->dataSize <= SPI_DATASIZE_8)
        {
            rxIncrement = sizeof(uint8_t);
        }
        else
        {
            rxIncrement = sizeof(uint16_t);
        }
    }
    else
    {
        rxBuf       = &(object->rxScratchBuf);
        rxIncrement = 0;
    }

    if (transaction->txBuf)
    {
        txBuf = transaction->txBuf;
        if (object->dataSize <= SPI_DATASIZE_8)
        {
            txIncrement = sizeof(uint8_t);
        }
        else
        {
            txIncrement = sizeof(uint16_t);
        }
    }
    else
    {
        txBuf       = (void *)&(object->txScratchBuf);
        txIncrement = 0;
    }

    rxCount = transaction->count;
    txCount = rxCount;

    SPIWFF3DMA_enableSPI(handle);

    /* Fill the TX FIFO as much as we can before reading */
    while (rxCount--)
    {
        if (object->dataSize <= SPI_DATASIZE_8)
        {
            put = true;
            while (txCount > 0 && put)
            {
                put = SPIWFF3DMA_dataPutNonBlocking(hwAttrs->baseAddr, *((uint8_t *)txBuf));
                if (put)
                {
                    txBuf = (void *)(((uint32_t)txBuf) + txIncrement);
                    txCount--;
                }
            }
            SPIWFF3DMA_dataGet(hwAttrs->baseAddr, &dummyBuffer);
            *((uint8_t *)rxBuf) = (uint8_t)dummyBuffer;
        }
        else
        {
            put = true;
            while (txCount > 0 && put)
            {
                put = SPIWFF3DMA_dataPutNonBlocking(hwAttrs->baseAddr, *((uint16_t *)txBuf));
                if (put)
                {
                    txBuf = (void *)(((uint32_t)txBuf) + txIncrement);
                    txCount--;
                }
            }
            SPIWFF3DMA_dataGet(hwAttrs->baseAddr, &dummyBuffer);
            *((uint16_t *)rxBuf) = (uint16_t)dummyBuffer;
        }

        /* Update rxBuf position */
        rxBuf = (void *)(((uint32_t)rxBuf) + rxIncrement);
    }

    while (SPIWFF3DMA_spiBusy(object, hwAttrs)) {}
}

/*
 *  ======== SPIWFF3DMA_spiPostNotify ========
 */
static int SPIWFF3DMA_spiPostNotify(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg)
{
    SPI_Handle handle                 = (SPI_Handle)clientArg;
    SPIWFF3DMA_Object *object         = handle->object;
    const SPIWFF3DMA_HWAttrs *hwAttrs = handle->hwAttrs;

    DMAWFF3_WordSize dmaWordSize = DMAWFF3_WORD_SIZE_1B;

    if (eventType == PowerWFF3_AWAKE_SLEEP)
    {
        if (object->dataSize <= SPI_DATASIZE_8)
        {
            dmaWordSize = DMAWFF3_WORD_SIZE_1B;
        }
        else
        {
            dmaWordSize = DMAWFF3_WORD_SIZE_2B;
        }

        /* Configure SPI DMA Rx channel. */
        DMAWFF3_configureChannel(hwAttrs->rxDmaChannel, SPI_RX_DMA_BLOCK_SIZE, dmaWordSize, SPI_RX_DMA_CONTROL_OPTS);

        /* Configure SPI DMA Tx channel. */
        DMAWFF3_configureChannel(hwAttrs->txDmaChannel, SPI_TX_DMA_BLOCK_SIZE, dmaWordSize, SPI_TX_DMA_CONTROL_OPTS);

        /* Initialize SPI hardware. */
        SPIWFF3DMA_initHw((SPI_Handle)clientArg);

        /* If SPI hardware in peripheral mode, initialize required GPIOs. */
        if (object->mode == SPI_PERIPHERAL)
        {
            SPIWFF3DMA_initIO(handle);
        }
    }
    else if (eventType == PowerWFF3_ENTERING_SLEEP)
    {
        /* Set the SPI IO back to default state before entering STDBY */
        SPIWFF3DMA_setIOSleepState(handle);
    }

    return (Power_NOTIFYDONE);
}

/*
 *  ======== SPIWFF3DMA_spiBusy ========
 *  HW is busy when in controller mode and BSY bit is set, or when in peripheral mode
 *  and TFE bit is not set.
 */
static inline bool SPIWFF3DMA_spiBusy(SPIWFF3DMA_Object *object, SPIWFF3DMA_HWAttrs const *hwAttrs)
{
    bool registerBit = (bool)(HWREG(hwAttrs->baseAddr + SPI_O_STA) & (object->busyBit));
    if (object->busyBit == SPI_STA_BUSY_ACTIVE)
    {
        return (registerBit);
    }
    else
    {
        return (!registerBit);
    }
}

/*
 *  ======== SPIWFF3DMA_disableSPI ========
 *  Disables the SPI peripheral
 */
static inline void SPIWFF3DMA_disableSPI(uint32_t baseAddr)
{
    HWREG(baseAddr + SPI_O_CTL1) &= ~SPI_CTL1_EN_ENABLE;
}

/*
 *  ======== SPIWFF3DMA_enableSPI ========
 *  Enables the SPI peripheral and performs IO muxing as necessary
 */
static inline void SPIWFF3DMA_enableSPI(SPI_Handle handle)
{
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;
    uint32_t baseAddr                 = hwAttrs->baseAddr;

    if (!SPIWFF3DMA_isSPIEnabled(handle))
    {
        HWREG(baseAddr + SPI_O_CTL1) |= SPI_CTL1_EN_ENABLE;
        if (object->mode == SPI_CONTROLLER)
        {
            /*
             * IO mux needs to occur after SPI IP is enabled
             * to produce correct signal state.
             */
            SPIWFF3DMA_initIO(handle);
        }
    }
}

/*
 *  ======== SPIWFF3DMA_isSPIEnabled ========
 *  Returns the SPI Peripheral State
 */
static inline bool SPIWFF3DMA_isSPIEnabled(SPI_Handle handle)
{
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;
    return (HWREG(hwAttrs->baseAddr + SPI_O_CTL1) & SPI_CTL1_EN_ENABLE) != 0;
}

/*
 *  ======== SPIWFF3DMA_getInterruptStatus ========
 *  Return the masked interrupt status
 */
static inline uint32_t SPIWFF3DMA_getInterruptStatus(uint32_t baseAddr, bool masked)
{
    /* Return either the interrupt status or the raw interrupt status as
    requested. */
    if (masked)
    {
        return (HWREG(baseAddr + SPI_O_MIS));
    }
    else
    {
        return (HWREG(baseAddr + SPI_O_RIS));
    }
}

/*
 *  ======== SPIWFF3DMA_enableInterrupt ========
 *  Enables the SPI peripheral interrupt
 */
static inline void SPIWFF3DMA_enableInterrupt(uint32_t baseAddr, uint32_t irqs)
{
    HWREG(baseAddr + SPI_O_IMASK) |= irqs;
}

/*
 *  ======== SPIWFF3DMA_disableInterrupt ========
 *  Disables the SPI peripheral interrupt
 */
static inline void SPIWFF3DMA_disableInterrupt(uint32_t baseAddr, uint32_t irqs)
{
    HWREG(baseAddr + SPI_O_IMASK) &= ~irqs;
}

/*
 *  ======== SPIWFF3DMA_clearInterrupt ========
 *  Clears the specified SPI peripheral interrupts
 */
static inline void SPIWFF3DMA_clearInterrupt(uint32_t baseAddr, uint32_t irqs)
{
    HWREG(baseAddr + SPI_O_ICLR) = irqs;
}

/*
 * ======== SPIWFF3DMA_initDMA ========
 * Intialize and configure the DMA peripheral
 */
static void SPIWFF3DMA_initDMA(SPI_Handle handle)
{
    SPIWFF3DMA_Object *object         = handle->object;
    SPIWFF3DMA_HWAttrs const *hwAttrs = handle->hwAttrs;
    DMAWFF3_WordSize dmaWordSize      = DMAWFF3_WORD_SIZE_1B;

    DMAWFF3_init();

    if (object->dataSize <= SPI_DATASIZE_8)
    {
        dmaWordSize = DMAWFF3_WORD_SIZE_1B;
    }
    else
    {
        dmaWordSize = DMAWFF3_WORD_SIZE_2B;
    }

    DMAWFF3_configureChannel(hwAttrs->rxDmaChannel, SPI_RX_DMA_BLOCK_SIZE, dmaWordSize, SPI_RX_DMA_CONTROL_OPTS);
    DMAWFF3_configureChannel(hwAttrs->txDmaChannel, SPI_TX_DMA_BLOCK_SIZE, dmaWordSize, SPI_TX_DMA_CONTROL_OPTS);
}

/*
 *  ======== SPIWFF3DMA_enableDMA ========
 *  Enable the SPI DMA peripheral
 */
static void SPIWFF3DMA_enableDMA(uint32_t baseAddr, uint32_t dmaFlags)
{
    /* Set the requested bits in the SPI DMA control register. */
    HWREG(baseAddr + SPI_O_DMACR) |= dmaFlags;
}

static void SPIWFF3DMA_disableDMA(uint32_t baseAddr, uint32_t dmaFlags)
{
    /* Clear the requested bits in the SPI DMA control register. */
    HWREG(baseAddr + SPI_O_DMACR) &= ~dmaFlags;
}

/*
 *  ======== SPIWFF3DMA_configSPI ========
 *  Configures the peripheral settings
 */
static bool SPIWFF3DMA_configSPI(uint32_t baseAddr,
                                 uint32_t freq,
                                 uint32_t format,
                                 uint32_t mode,
                                 uint32_t bitRate,
                                 uint32_t dataSize,
                                 uint32_t dsample)
{
    uint16_t scr;
    uint32_t ratio;

#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX
    /* CC35XX has a prescaler in CLKCFG0[2:0] which is by default set to
     * divide by 1. The SCR math below takes PRESC = DIV_BY_1.
     */
    HWREG(baseAddr + SPI_O_CLKCFG0) = (HWREG(baseAddr + SPI_O_CLKCFG0) & ~SPI_CLKCFG0_PRESC_M) |
                                       SPI_CLKCFG0_PRESC_DIV_BY_1;
#endif

    /* Get existing settings */
    uint32_t reg = HWREG(baseAddr + SPI_O_CLKCFG1);

    /* Create a mask for settings to modify */
    uint32_t mask = (SPI_CLKCFG1_DSAMPLE_M | SPI_CLKCFG1_SCR_M);

    /* Calculate scr variable such that actual clock is always <= bitRate */
    ratio = (freq + (2 * bitRate) - 1) / (2 * bitRate);

    if (ratio > 0 && ratio <= SERIAL_CLK_DIVIDER_MAX)
    {
        scr = (uint16_t)(ratio - 1);
    }
    else
    {
        scr = 0;
    }

    /* Set clock divider */
    HWREG(baseAddr + SPI_O_CLKCFG1) = (reg & ~mask) | dsample | scr;

    /* Get existing settings */
    reg  = HWREG(baseAddr + SPI_O_CTL0);
    /* Create mask for settings to modify */
    mask = (SPI_CTL0_DSS_M | SPI_CTL0_FRF_M | SPI_CTL0_SPO_M | SPI_CTL0_SPH_M);

    /* Convert and mask data size to HW register format */
    dataSize                     = (SPI_CTL0_DSS_M & (dataSize - 1));
    /* Apply updated register */
    HWREG(baseAddr + SPI_O_CTL0) = (reg & ~mask) | format | dataSize;

    /* Set controller/peripheral mode, MSB first */
    HWREG(baseAddr + SPI_O_CTL1) = mode | SPI_CTL1_MSB_MSB;

    /* Set IFLS to trigger interrupt when 1 byte or more is in the FIFO */
    HWREG(baseAddr + SPI_O_IFLS) &= ~(SPI_IFLS_TXSEL_M | SPI_IFLS_RXSEL_M);
    HWREG(baseAddr + SPI_O_IFLS) |= SPI_IFLS_TXSEL_LEVEL_1 | SPI_IFLS_RXSEL_M;

    return (true);
}

static int32_t SPIWFF3DMA_dataPutNonBlocking(uint32_t baseAddr, uint32_t frame)
{
    /* Check for space to write. */
    if (HWREG(baseAddr + SPI_O_STA) & SPI_STA_TNF_NOT_FULL)
    {
        /* Write the data to the SPI TX FIFO. */
        HWREG(baseAddr + SPI_O_TXDATA) = frame;
        return (1);
    }
    else
    {
        return (0);
    }
}

static void SPIWFF3DMA_dataGet(uint32_t baseAddr, uint32_t *frame)
{
    /* Wait until there is data to be read. */
    while (HWREG(baseAddr + SPI_O_STA) & SPI_STA_RFE_EMPTY) {}

    /* Read data from SPI RX FIFO. */
    *frame = HWREG(baseAddr + SPI_O_RXDATA);
}

static bool SPIWFF3DMA_isSPIBusy(uint32_t baseAddr)
{
    /* Determine if the SPI is busy. */
    return ((HWREG(baseAddr + SPI_O_STA) & SPI_STA_BUSY) ? true : false);
}