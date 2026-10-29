/*
 * Copyright (c) 2023-2025, Texas Instruments Incorporated
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
 *  ======== I2CWFF3.c ========
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <ti/drivers/i2c/I2CWFF3.h>
#include <ti/drivers/i2c/I2CSupport.h>

#include <ti/drivers/GPIO.h>
#include <ti/drivers/Power.h>

#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/dpl/SwiP.h>

/* Driverlib header files */
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(driverlib/i2c.h)

/* Prototypes */
static void I2CWFF3_blockingCallback(I2C_Handle handle, I2C_Transaction *msg, bool transferStatus);
static inline void I2CWFF3_completeTransfer(I2C_Handle handle);
static uint16_t I2CWFF3_drainRxFifo(uint32_t baseAddr, uint8_t *buffer, uint16_t count);
static uint16_t I2CWFF3_fillTxFifo(uint32_t baseAddr, const uint8_t *buffer, uint16_t count);
static void I2CWFF3_hwiFxn(uintptr_t arg);
static void I2CWFF3_initHw(I2C_Handle handle);
static void I2CWFF3_initIO(I2C_Handle handle);
static int I2CWFF3_postNotify(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg);
static void I2CWFF3_swiFxn(uintptr_t arg0, uintptr_t arg1);

/* Default I2C parameters structure */
extern const I2C_Params I2C_defaultParams;

/*
 *  ======== I2C_close ========
 */
void I2C_close(I2C_Handle handle)
{
    I2CWFF3_Object *object;
    I2CWFF3_HWAttrs const *hwAttrs;

    /* Get the pointer to the object and hwAttrs */
    hwAttrs = handle->hwAttrs;
    object  = handle->object;

    /* Check to see if a I2C transaction is in progress */
    DebugP_assert(object->headPtr == NULL);

    /* Mask all I2C interrupts */
    I2CDisableInt(hwAttrs->baseAddr, I2C_INT_ALL);

    /* Disable the I2C Controller */
    I2CControllerDisable(hwAttrs->baseAddr);

    /* Deallocate pins */
    GPIO_resetConfig(hwAttrs->sclPin);
    GPIO_resetConfig(hwAttrs->sdaPin);

    /* Power off the I2C module */
    Power_releaseDependency(hwAttrs->powerMngrId);

    /* Destruct modules used in driver */
    HwiP_destruct(&(object->hwi));
    SwiP_destruct(&(object->swi));
    SemaphoreP_destruct(&(object->mutex));
    if (object->transferMode == I2C_MODE_BLOCKING)
    {
        SemaphoreP_destruct(&(object->transferComplete));
    }

    /* Unregister power post notification object */
    Power_unregisterNotify(&object->i2cPostObj);

    /* Mark the module as available */
    object->isOpen = false;

    return;
}

/*
 *  ======== I2C_control ========
 *  Currently not in use.
 */
int_fast16_t I2C_control(I2C_Handle handle, uint_fast16_t cmd, void *arg)
{
    /* No implementation */
    return I2C_STATUS_UNDEFINEDCMD;
}

/*
 *  ======== I2C_open ========
 */
I2C_Handle I2C_open(uint_least8_t index, I2C_Params *params)
{
    I2C_Handle handle = NULL;
    union
    {
        HwiP_Params hwiParams;
        SwiP_Params swiParams;
    } paramsUnion;
    uintptr_t key;
    I2CWFF3_Object *object;
    I2CWFF3_HWAttrs const *hwAttrs;

    if (index < I2C_count)
    {
        if (params == NULL)
        {
            params = (I2C_Params *)&I2C_defaultParams;
        }

        handle  = (I2C_Handle)&I2C_config[index];
        hwAttrs = handle->hwAttrs;
        object  = handle->object;
    }
    else
    {
        return NULL;
    }

    /* Check for callback when transfer mode is I2C_MODE_CALLBACK */
    if ((params->transferMode == I2C_MODE_CALLBACK) && (params->transferCallbackFxn == NULL))
    {
        return NULL;
    }

    /* Check for valid bit rate */
    DebugP_assert(params->bitRate <= I2C_1000kHz);

    /* Determine if the device index was already opened */
    key = HwiP_disable();
    if (object->isOpen == true)
    {
        HwiP_restore(key);
        return NULL;
    }

    /* Mark the handle as being used */
    object->isOpen = true;
    HwiP_restore(key);

    /* Power on the I2C module */
    Power_setDependency(hwAttrs->powerMngrId);

    /* Configure the IOs */
    I2CWFF3_initIO(handle);

    /* Save parameters */
    object->transferMode        = params->transferMode;
    object->transferCallbackFxn = params->transferCallbackFxn;
    object->bitRate             = params->bitRate;

    /* Set the address mode */
    I2C_setAddressMode(handle, params->addressMode);

    /* Disable and clear interrupts possible from soft resets */
    I2CDisableInt(hwAttrs->baseAddr, I2C_INT_ALL);
    I2CClearInt(hwAttrs->baseAddr, I2C_INT_ALL);

    /* Create Hwi object for this I2C peripheral */
    HwiP_Params_init(&paramsUnion.hwiParams);
    paramsUnion.hwiParams.arg      = (uintptr_t)handle;
    paramsUnion.hwiParams.priority = hwAttrs->intPriority;
    HwiP_construct(&(object->hwi), hwAttrs->intNum, I2CWFF3_hwiFxn, &paramsUnion.hwiParams);

    /* Create Swi object for this I2C peripheral */
    SwiP_Params_init(&(paramsUnion.swiParams));
    paramsUnion.swiParams.arg0     = (uintptr_t)handle;
    paramsUnion.swiParams.priority = hwAttrs->swiPriority;
    SwiP_construct(&(object->swi), I2CWFF3_swiFxn, &(paramsUnion.swiParams));

    /* Create thread safe handles for this I2C peripheral
     * Semaphore to provide exclusive access to the I2C peripheral
     */
    SemaphoreP_constructBinary(&(object->mutex), 1);

    /* Store a callback function that posts the transfer complete
     * semaphore for synchronous mode
     */
    if (object->transferMode == I2C_MODE_BLOCKING)
    {
        /* Semaphore to cause the waiting task to block for the I2C to finish */
        SemaphoreP_constructBinary(&(object->transferComplete), 0);

        /* Store internal callback function */
        object->transferCallbackFxn = I2CWFF3_blockingCallback;
    }

    /* Clear the head and tail pointers */
    object->headPtr = NULL;
    object->tailPtr = NULL;

    /* Initialize the I2C hardware module */
    I2CWFF3_initHw(handle);

    /* Register notification functions */
    Power_registerNotify(&object->i2cPostObj,
                         PowerWFF3_AWAKE_SLEEP,
                         (Power_NotifyFxn)I2CWFF3_postNotify,
                         (uint32_t)handle);

    /* Return the address of the handle */
    return handle;
}

/*
 *  ======== I2CWFF3_hwiFxn ========
 *  Hwi interrupt handler to service the I2C peripheral
 *
 *  The handler is a generic handler for a I2C object.
 */
static void I2CWFF3_hwiFxn(uintptr_t arg)
{
    I2C_Handle handle              = (I2C_Handle)arg;
    I2CWFF3_Object *object         = handle->object;
    I2CWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Get interrupt status */
    uint32_t intStatus = I2CIntStatus(hwAttrs->baseAddr, false);

    /* Clear all interrupt flags */
    I2CClearInt(hwAttrs->baseAddr, I2C_INT_ALL);

    /* Handle errors */
    if (intStatus & I2C_CONTROLLER_INT_ARB_LOST)
    {
        /* Arbitration lost
         * SW should:
         * - Flush TX FIFO
         * - Clear and mask the TX Empty interrupt by the TXEMPTY bit through
         *   the IMASK and ICLR register.
         * - Once the bus is IDLE, the TXFIFO can be filled and enabled, the
         *   TXEMPTY bit can be unmasked and a new transaction can be initiated.
         */
        /* Wait until stop condition, by disabling all interrupts but the
         * STOP condition interrupt */
        I2CDisableInt(hwAttrs->baseAddr, ~I2C_CONTROLLER_INT_STOP);
        I2CFlushTxFifo(hwAttrs->baseAddr);
        object->currentTransaction->status = I2C_STATUS_ARB_LOST;
    }
    else if (intStatus & I2C_CONTROLLER_INT_NACK)
    {
        /* Address/Data NACK
         * Get errors to determine NACK type
         */
        uint32_t error = I2CControllerGetError(hwAttrs->baseAddr);
        if (error & I2C_CONTROLLER_ERR_ADDR_ACK)
        {
            /* Address NACK */
            /* HW automatically generates STOP */
            object->currentTransaction->status = I2C_STATUS_ADDR_NACK;
        }
        else if (error & I2C_CONTROLLER_ERR_DATA_ACK)
        {
            /* HW automatically generates STOP */
            object->currentTransaction->status = I2C_STATUS_DATA_NACK;
        }
    }

    /* Complete transfer if STOP condition is detected */
    if (intStatus & I2C_CONTROLLER_INT_STOP)
    {
        I2CControllerSetCommand(hwAttrs->baseAddr, 0, I2C_CONTROLLER_TRANSACTION_LENGTH_NONE);
        I2CWFF3_completeTransfer(handle);
    }
    /* If the transaction has been cancelled and the current burst transaction
     * is done, then send stop condition. If the current burst transaction is
     * not done, then we need to wait until the burst transaction is done,
     * because the HW does not support cancelling a burst transaction.
     */
    else if ((object->currentTransaction->status == I2C_STATUS_CANCEL) &&
             (intStatus & (I2C_CONTROLLER_INT_TX_DONE | I2C_CONTROLLER_INT_RX_DONE)))
    {
        /* Generate a STOP condition.
         * This will cause the I2C_CONTROLLER_INT_STOP interrupt to trigger.
         */
        I2CControllerSetCommand(hwAttrs->baseAddr,
                                I2C_CONTROLLER_CMD_BURST_FINISH,
                                I2C_CONTROLLER_TRANSACTION_LENGTH_NONE);
    }
    /* Continue transaction if it is still in progress or if it is being
     * cancelled */
    else if ((object->currentTransaction->status == I2C_STATUS_INCOMPLETE) ||
             (object->currentTransaction->status == I2C_STATUS_CANCEL))
    {
        /* If any data (in FIFO or in I2C object) needs to be written */
        if (object->writeCount || !I2CIsTxFifoEmpty(hwAttrs->baseAddr))
        {
            /* Write data to TX FIFO, if there is any data to write */
            if (object->writeCount)
            {
                /* Fill TX FIFO */
                uint32_t fifoWriteCount = I2CWFF3_fillTxFifo(hwAttrs->baseAddr, object->writeBuf, object->writeCount);

                /* Update buffer pointer and write count based on number of
                 * bytes written to FIFO
                 */
                object->writeBuf += fifoWriteCount;
                object->writeCount -= fifoWriteCount;

                if (object->writeCount == 0)
                {
                    /* Disable the FIFO trigger threshold interrupt, since no
                     * additional data needs to be written to the FIFO
                     */
                    I2CDisableInt(hwAttrs->baseAddr, I2C_CONTROLLER_INT_TX_FIFO_TRIGGER);
                }
            }

            /* If the previous transaction is done, start new transaction */
            if (intStatus & I2C_CONTROLLER_INT_TX_DONE)
            {
                /* Determine the transaction length to write to the I2C module.
                 * The maximum transaction length supported by the I2C module is
                 * I2C_CONTROLLER_TRANSACTION_LENGTH_MAX, so if the write count
                 * (plus the number of bytes in the TX FIFO) is more than
                 * I2C_CONTROLLER_TRANSACTION_LENGTH_MAX, the data needs to be
                 * split up into multiple burst transactions. It will still only
                 * result in one I2C transaction. I.e. one start condition and
                 * one stop condition (or repeated start condition if read count
                 * is non-zero)
                 */
                uint32_t transactionLength = object->writeCount + I2CGetTxFifoCount(hwAttrs->baseAddr);
                if (transactionLength > I2C_CONTROLLER_TRANSACTION_LENGTH_MAX)
                {
                    transactionLength = I2C_CONTROLLER_TRANSACTION_LENGTH_MAX;
                }

                /* Continue burst transaction */
                I2CControllerSetCommand(hwAttrs->baseAddr, I2C_CONTROLLER_CMD_BURST_SEND_CONT, transactionLength);
            }
        }
        /* If any data needs to be read */
        else if (object->readCount)
        {
            /* Only read the RX FIFO if a TX transaction has NOT just finished.
             * If a TX transaction has just finished, then there is not yet any
             * data to read from the RX FIFO.
             */
            if (!(intStatus & I2C_CONTROLLER_INT_TX_DONE))
            {
                /* Drain RX FIFO */
                uint32_t fifoReadCount = I2CWFF3_drainRxFifo(hwAttrs->baseAddr, object->readBuf, object->readCount);

                /* Update buffer pointer and read count based on number of bytes
                 * read from FIFO
                 */
                object->readBuf += fifoReadCount;
                object->readCount -= fifoReadCount;
            }

            /* If still more data needs to be read */
            if (object->readCount)
            {
                if (object->readCount < (I2C_RX_FIFO_SIZE - I2CGetRxFifoCount(hwAttrs->baseAddr)))
                {
                    /* Disable the FIFO trigger threshold interrupt, since the
                     * rest of the data can fit in the FIFO
                     */
                    I2CDisableInt(hwAttrs->baseAddr, I2C_CONTROLLER_INT_RX_FIFO_TRIGGER);
                }

                /* If a transaction has just finished, start a new transaction */
                if (intStatus & (I2C_CONTROLLER_INT_TX_DONE | I2C_CONTROLLER_INT_RX_DONE))
                {
                    /* Determine the transaction length to write to the I2C
                     * module.
                     * The maximum transaction length supported by the I2C
                     * module is I2C_CONTROLLER_TRANSACTION_LENGTH_MAX, so if
                     * the read count is more than
                     * I2C_CONTROLLER_TRANSACTION_LENGTH_MAX, then the
                     * transaction needs to be split up into multiple burst
                     * transactions. It will still only result in one I2C
                     * transaction. I.e. one start condition and one stop
                     * condition.
                     */
                    uint32_t transactionLength = object->readCount;
                    if (transactionLength > I2C_CONTROLLER_TRANSACTION_LENGTH_MAX)
                    {
                        transactionLength = I2C_CONTROLLER_TRANSACTION_LENGTH_MAX;
                    }

                    /* If a TX transaction has just finished,
                     * start an RX transaction */
                    if (intStatus & I2C_CONTROLLER_INT_TX_DONE)
                    {
                        I2CDisableInt(hwAttrs->baseAddr, I2C_INT_ALL);
                        I2CEnableInt(hwAttrs->baseAddr,
                                     I2C_CONTROLLER_INT_RX_DONE | I2C_CONTROLLER_INT_RX_FIFO_TRIGGER |
                                         I2C_CONTROLLER_INT_NACK | I2C_CONTROLLER_INT_ARB_LOST |
                                         I2C_CONTROLLER_INT_STOP);

                        /* Specify target address, target address mode,
                         * and receive mode */
                        I2CControllerSetTargetAddr(hwAttrs->baseAddr,
                                                   object->addressMode,
                                                   object->currentTransaction->targetAddress,
                                                   I2C_CONTROLLER_DIR_RECEIVE);

                        /* Start burst operation */
                        I2CControllerSetCommand(hwAttrs->baseAddr,
                                                I2C_CONTROLLER_CMD_BURST_RECEIVE_START,
                                                transactionLength);
                    }
                    /* If an RX transaction has just finished, continue I2C
                     * transaction */
                    else if (intStatus & I2C_CONTROLLER_INT_RX_DONE)
                    {
                        /* Continue burst transaction */
                        I2CControllerSetCommand(hwAttrs->baseAddr,
                                                I2C_CONTROLLER_CMD_BURST_RECEIVE_CONT,
                                                transactionLength);
                    }
                }
            }
            /* No more data is needed */
            else
            {
                /* Generate a STOP condition.
                 * This will cause the I2C_CONTROLLER_INT_STOP interrupt to
                 * trigger.
                 */
                I2CControllerSetCommand(hwAttrs->baseAddr,
                                        I2C_CONTROLLER_CMD_BURST_FINISH,
                                        I2C_CONTROLLER_TRANSACTION_LENGTH_NONE);
                object->currentTransaction->status = I2C_STATUS_SUCCESS;
            }
        }
        else
        {
            /* Generate a STOP condition.
             * This will cause the I2C_CONTROLLER_INT_STOP interrupt to trigger.
             */
            I2CControllerSetCommand(hwAttrs->baseAddr,
                                    I2C_CONTROLLER_CMD_BURST_FINISH,
                                    I2C_CONTROLLER_TRANSACTION_LENGTH_NONE);
            object->currentTransaction->status = I2C_STATUS_SUCCESS;
        }
    }

    return;
}

/*
 *  ======== I2C_setAddressMode ========
 */
void I2C_setAddressMode(I2C_Handle handle, I2C_AddressMode addressMode)
{
    I2CWFF3_Object *object = handle->object;

    /* Convert address mode to driverlib format */
    if (addressMode == I2C_ADDRESS_MODE_10_BIT)
    {
        object->addressMode = I2C_CONTROLLER_ADDR_MODE_10_BIT;
    }
    else
    {
        object->addressMode = I2C_CONTROLLER_ADDR_MODE_7_BIT;
    }
}

/*
 *  ======== I2C_setClockTimeout ========
 */
int_fast16_t I2C_setClockTimeout(I2C_Handle handle, uint32_t timeout)
{
    return I2C_STATUS_ERROR;
}

/*
 *  ======== I2CWFF3_swiFxn ========
 *  SWI interrupt handler to service the I2C peripheral
 *
 *  Takes care of cleanup and the callback in SWI context after an I2C transfer
 */
static void I2CWFF3_swiFxn(uintptr_t arg0, uintptr_t arg1)
{
    I2C_Handle handle      = (I2C_Handle)arg0;
    I2CWFF3_Object *object = handle->object;
    int_fast16_t status;

    /* If this current transaction was canceled, we need to cancel
     * any queued transactions
     */
    if (object->currentTransaction->status == I2C_STATUS_CANCEL)
    {
        /* Allow callback to run. If in CALLBACK mode, the application
         * may initiate a transfer in the callback which will call
         * primeTransfer().
         */
        object->transferCallbackFxn(handle, object->currentTransaction, false);
        object->currentTransaction->status = I2C_STATUS_CANCEL;

        /* Release the constraint to disallow sleep */
        Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

        /* Also dequeue and call the transfer callbacks for any queued transfers */
        while (object->headPtr != object->tailPtr)
        {
            object->headPtr         = object->headPtr->nextPtr;
            object->headPtr->status = I2C_STATUS_CANCEL;
            object->transferCallbackFxn(handle, object->headPtr, false);
            object->headPtr->status = I2C_STATUS_CANCEL;
        }

        /* Clean up object */
        object->currentTransaction = NULL;
        object->headPtr            = NULL;
        object->tailPtr            = NULL;
    }
    else if (object->currentTransaction->status == I2C_STATUS_TIMEOUT)
    {
        /* This can only occur in BLOCKING mode. No need to call the blocking
         * callback as the semaphore has already timed out.
         */
        object->headPtr = NULL;
        object->tailPtr = NULL;

        /* Release sleep disallow constraint. */
        Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);
    }
    /* See if we need to process any other transactions */
    else if (object->headPtr == object->tailPtr)
    {

        /* No other transactions need to occur */
        object->headPtr = NULL;
        object->tailPtr = NULL;

        /* Allow callback to run. If in CALLBACK mode, the application
         * may initiate a transfer in the callback which will call
         * primeTransfer().
         */
        object->transferCallbackFxn(handle,
                                    object->currentTransaction,
                                    (object->currentTransaction->status == I2C_STATUS_SUCCESS));

        /* Release sleep disallow constraint */
        Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);
    }
    else
    {
        /* Another transfer needs to take place */
        object->headPtr = object->headPtr->nextPtr;

        /* Allow application callback to run. The application may
         * initiate a transfer in the callback which will add an
         * additional transfer to the queue.
         */
        object->transferCallbackFxn(handle,
                                    object->currentTransaction,
                                    (object->currentTransaction->status == I2C_STATUS_SUCCESS));

        status = I2CSupport_primeTransfer(handle, object->headPtr);

        /* If I2CSupport_primeTransfer() failed, post the SWI immediately to
         * trigger the callback function to be called.
         * There is no need to set the transaction status here, since it has
         * already been set in I2CSupport_primeTransfer()
         */
        if (status != I2C_STATUS_SUCCESS)
        {
            SwiP_post(&(object->swi));
        }
    }
}

/*
 *  ======== I2CSupport_controllerFinish ========
 */
void I2CSupport_controllerFinish(I2C_HWAttrs const *hwAttrs)
{
    /* The HW does not support stopping/cancelling a burst transaction,
     * instead we wait until the current burst transaction completes, and then
     * cancel any future burst transactions.
     * This is done in I2CWFF3_hwiFxn().
     */
}

/*
 *  ======== I2CSupport_powerRelConstraint =======
 */
void I2CSupport_powerRelConstraint(void)
{
    /* Release sleep disallow constraint. */
    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);
}

/*
 *  ======== I2CSupport_powerSetConstraint =======
 */
void I2CSupport_powerSetConstraint(void)
{
    /* Set sleep disallow constraint. */
    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);
}

/*
 *  ======== I2CSupport_primeTransfer =======
 */
int_fast16_t I2CSupport_primeTransfer(I2C_Handle handle, I2C_Transaction *transaction)
{
    I2CWFF3_Object *object         = handle->object;
    I2CWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;
    int_fast16_t status            = I2C_STATUS_SUCCESS;

    /* Store the new internal counters and pointers */
    object->currentTransaction = transaction;

    object->writeBuf   = transaction->writeBuf;
    object->writeCount = transaction->writeCount;
    object->readBuf    = transaction->readBuf;
    object->readCount  = transaction->readCount;

    /* Transaction is incomplete unless the stop condition occurs AND
     * all bytes have been sent and received. This condition is checked
     * in the hardware interrupt.
     */
    object->currentTransaction->status = I2C_STATUS_INCOMPLETE;

    /* Flush FIFOs if any is not empty */
    if (!I2CIsRxFifoEmpty(hwAttrs->baseAddr) || !I2CIsTxFifoEmpty(hwAttrs->baseAddr))
    {
        /* Flush FIFOs */
        I2CFlushFifos(hwAttrs->baseAddr);

        /* Clear interrupt flags */
        I2CClearInt(hwAttrs->baseAddr, I2C_INT_ALL);
    }

    /* Determine if the bus is in use by another I2C Controller */
    if (I2CControllerIsBusBusy(hwAttrs->baseAddr))
    {
        transaction->status = I2C_STATUS_BUS_BUSY;
        status              = I2C_STATUS_BUS_BUSY;
    }
    /* Start transfer in Transmit */
    else if (object->writeCount)
    {
        /* Enable interrupts */
        I2CEnableInt(hwAttrs->baseAddr,
                     I2C_CONTROLLER_INT_TX_DONE | I2C_CONTROLLER_INT_NACK | I2C_CONTROLLER_INT_ARB_LOST |
                         I2C_CONTROLLER_INT_STOP);

        /* Specify target address, target address mode, and transmit mode */
        I2CControllerSetTargetAddr(hwAttrs->baseAddr,
                                   object->addressMode,
                                   object->currentTransaction->targetAddress,
                                   I2C_CONTROLLER_DIR_TRANSMIT);

        /* Fill TX FIFO */
        uint32_t fifoWriteCount = I2CWFF3_fillTxFifo(hwAttrs->baseAddr, object->writeBuf, object->writeCount);

        /* Determine the transaction length to write to the I2C module.
         * The maximum transaction length supported by the I2C module is
         * I2C_CONTROLLER_TRANSACTION_LENGTH_MAX, so if the write count is more
         * than I2C_CONTROLLER_TRANSACTION_LENGTH_MAX, the data needs to be
         * split up into multiple burst transactions. It will still only result
         * in one I2C transaction. I.e. one start condition and one stop
         * condition (or repeated start condition if read count
         * is non-zero)
         */
        uint32_t transactionLength = object->writeCount > I2C_CONTROLLER_TRANSACTION_LENGTH_MAX
                                         ? I2C_CONTROLLER_TRANSACTION_LENGTH_MAX
                                         : object->writeCount;

        /* Update buffer pointer on write count based on number of bytes written
         * to FIFO
         */
        object->writeBuf += fifoWriteCount;
        object->writeCount -= fifoWriteCount;

        /* Enable TX FIFO trigger threshold interrupt, if there is additional
         * additional data to write to the fifo.
         */
        if (object->writeCount != 0)
        {
            I2CEnableInt(hwAttrs->baseAddr, I2C_CONTROLLER_INT_TX_FIFO_TRIGGER);
        }

        /* Start burst operation */
        I2CControllerSetCommand(hwAttrs->baseAddr, I2C_CONTROLLER_CMD_BURST_SEND_START, transactionLength);
    }
    else
    {
        /* Determine the transaction length to write to the I2C module.
         * The maximum transaction length supported by the I2C module is
         * I2C_CONTROLLER_TRANSACTION_LENGTH_MAX, so if the read count
         * is more than I2C_CONTROLLER_TRANSACTION_LENGTH_MAX, then the
         * transaction needs to be split up into multiple burst
         * transactions. It will still only result in one I2C
         * transaction. I.e. on start condition and one stop condition.
         */
        uint32_t transactionLength = object->readCount > I2C_CONTROLLER_TRANSACTION_LENGTH_MAX
                                         ? I2C_CONTROLLER_TRANSACTION_LENGTH_MAX
                                         : object->readCount;

        /* Enable interrupts */
        I2CEnableInt(hwAttrs->baseAddr,
                     I2C_CONTROLLER_INT_RX_DONE | I2C_CONTROLLER_INT_NACK | I2C_CONTROLLER_INT_ARB_LOST |
                         I2C_CONTROLLER_INT_STOP);

        /* Also enable RX FIFO trigger threshold interrupt, if all the data to
         * be read can't fit in the RX FIFO.
         */
        if (object->readCount > I2C_RX_FIFO_SIZE)
        {
            I2CEnableInt(hwAttrs->baseAddr, I2C_CONTROLLER_INT_RX_FIFO_TRIGGER);
        }

        /* Specify target address, target address mode, and receive mode */
        I2CControllerSetTargetAddr(hwAttrs->baseAddr,
                                   object->addressMode,
                                   object->currentTransaction->targetAddress,
                                   I2C_CONTROLLER_DIR_RECEIVE);

        /* Start the I2C transfer in controller receive mode */
        I2CControllerSetCommand(hwAttrs->baseAddr, I2C_CONTROLLER_CMD_BURST_RECEIVE_START, transactionLength);
    }

    return status;
}

/*
 *  ======== I2CWFF3_completeTransfer ========
 *  This function may be invoked in the context of the HWI.
 */
static inline void I2CWFF3_completeTransfer(I2C_Handle handle)
{
    I2CWFF3_Object *object         = handle->object;
    I2CWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Disable and clear any interrupts */
    I2CDisableInt(hwAttrs->baseAddr, I2C_INT_ALL);
    I2CClearInt(hwAttrs->baseAddr, I2C_INT_ALL);

    SwiP_post(&(object->swi));
}

/*
 *  ======== I2CWFF3_blockingCallback ========
 */
static void I2CWFF3_blockingCallback(I2C_Handle handle, I2C_Transaction *msg, bool transferStatus)
{
    I2CWFF3_Object *object = handle->object;

    SemaphoreP_post(&(object->transferComplete));
}

/*
 *  ======== I2CWFF3_initHw ========
 *  This functions initializes the I2C hardware module.
 *
 *  The function assumes that the I2C handle is pointing to a hardware module
 *  which has already been opened.
 */
static void I2CWFF3_initHw(I2C_Handle handle)
{
    I2CWFF3_Object *object         = handle->object;
    I2CWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Disable interrupts */
    I2CDisableInt(hwAttrs->baseAddr, I2C_INT_ALL);

    /* Flush FIFOs */
    I2CFlushFifos(hwAttrs->baseAddr);

    /* Set FIFO trigger thresholds
     * There is no risk of overflow or underflow of FIFOs since clock stretching
     * is utilized. If the RX FIFO is full or the TX FIFO is empty, the I2C
     * module will use clock stretching until data has been read from the RX
     * FIFO or written to the TX FIFO.
     * For this reason a low TX threshold (one byte from empty) and a high RX
     * threshold (one byte from full) is used to reduce interrupt processing
     * time.
     */
    I2CSetTxFifoTrigger(hwAttrs->baseAddr, 1);
    I2CSetRxFifoTrigger(hwAttrs->baseAddr, I2C_RX_FIFO_SIZE - 1);

    /* Clear interrupt flags */
    I2CClearInt(hwAttrs->baseAddr, I2C_INT_ALL);

    /* Make sure there is no current command */
    I2CControllerSetCommand(hwAttrs->baseAddr, 0, I2C_CONTROLLER_TRANSACTION_LENGTH_NONE);

    /* Set the I2C configuration
     * Enabled:
     *  - Clock stretching enabled
     * Disabled:
     *  - Multi-controller mode
     *  - Loopback mode
     *
     * The enumerated values of I2C_BitRate match the values expected by
     * I2CControllerInit, which is why object->bitRate is passed directly to
     * the function.
     */
    I2CControllerInit(hwAttrs->baseAddr, I2C_CONTROLLER_CONFIG_CLOCK_STRETCHING_DETECTION, object->bitRate);

    /* Enable the I2C Controller for operation */
    I2CControllerEnable(hwAttrs->baseAddr);
}

/*
 *  ======== I2CWFF3_initIO ========
 *  This functions initializes the I2C IOs.
 *
 *  The function assumes that the I2C handle is pointing to a hardware module
 *  which has already been opened.
 */
static void I2CWFF3_initIO(I2C_Handle handle)
{
    I2CWFF3_HWAttrs const *hwAttrs;

    /* Get the pointer to the hwAttrs */
    hwAttrs = handle->hwAttrs;

    /* Configure I2C pins SDA and SCL and set their muxes */
    GPIO_setConfigAndMux(hwAttrs->sdaPin, GPIO_CFG_IN_PU, hwAttrs->sdaPinMux);
    GPIO_setConfigAndMux(hwAttrs->sclPin, GPIO_CFG_IN_PU, hwAttrs->sclPinMux);
}

/*
 *  ======== I2CWFF3_postNotify ========
 *  This functions is called to notify the I2C driver of an ongoing transition
 *  out of sleep mode.
 *
 *  The function assumes that the I2C handle (clientArg) is pointing to a
 *  hardware module which has already been opened.
 */
static int I2CWFF3_postNotify(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg)
{
    /* reconfigure the hardware if returning from sleep*/
    if (eventType == PowerWFF3_AWAKE_SLEEP)
    {
        I2CWFF3_initHw((I2C_Handle)clientArg);
    }

    return Power_NOTIFYDONE;
}

/*
 *  ======== I2CWFF3_drainRxFifo ========
 *  Helper function to read up to count bytes from the I2C RX FIFO to buffer.
 *  Will return when either the RX FIFO is empty or when count bytes has been
 *  read.
 *  Returns the number of bytes actually read.
 */
static uint16_t I2CWFF3_drainRxFifo(uint32_t baseAddr, uint8_t *buffer, uint16_t count)
{
    uint16_t bytesRead = 0;

    /* Read from RX FIFO until count bytes has been read or RX FIFO is empty */
    while (bytesRead < count)
    {
        /* Read byte */
        if (I2CGetDataNonBlocking(baseAddr, &buffer[bytesRead]) == 1)
        {
            /* Successfully read byte from RX FIFO */
            bytesRead++;
        }
        else
        {
            /* No more data in RX FIFO */
            break;
        }
    }

    return bytesRead;
}

/*
 *  ======== I2CWFF3_fillTxFifo ========
 *  Helper function to write up to count bytes to the I2C TX FIFO from buffer.
 *  Will return when either the TX FIFO is full or when count bytes has been
 *  written.
 *  Returns the number of bytes actually written.
 */
static uint16_t I2CWFF3_fillTxFifo(uint32_t baseAddr, const uint8_t *buffer, uint16_t count)
{
    uint16_t bytesWritten = 0;

    /* Write to TX FIFO until count bytes has been written or TX FIFO is full */
    while (bytesWritten < count)
    {
        /* Write byte */
        if (I2CPutDataNonBlocking(baseAddr, buffer[bytesWritten]) == 1)
        {
            /* Successfully wrote byte to TX FIFO */
            bytesWritten++;
        }
        else
        {
            /* No more space in TX FIFO */
            break;
        }
    }

    return bytesWritten;
}
