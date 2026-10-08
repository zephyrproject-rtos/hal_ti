/*
 * Copyright (c) 2025 Texas Instruments Incorporated
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
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/i2s.h)
#include DeviceFamily_constructPath(inc/hw_i2s.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)

#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2S.h>
#include <ti/drivers/i2s/I2SWFF3.h>
#include <ti/drivers/Power.h>

#define I2S_CLOCK_DIVIDER_MAX 1024U
#define I2S_CLOCK_DIVIDER_MIN 2U
#define I2S_NB_CHANNELS_MAX   8U

/* Forward declarations */
static bool configObject(I2S_Handle handle, I2S_Params *params);
static void initIO(I2S_Handle handle);
static void finalizeIO(I2S_Handle handle);
static void initHw(I2S_Handle handle);
static void I2S_hwiIntFxn(uintptr_t arg);
static int i2sPostNotify(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg);

static void configSerialFormat(I2S_Handle handle);
static void configChannels(I2S_Handle handle);
static void configClocks(I2S_Handle handle);
static void enableClocks(I2S_Handle handle);

static bool computeSCKDivider(I2S_Handle handle, const I2S_Params *params, uint16_t *result);
static bool computeWSDivider(I2S_Handle handle, const I2S_Params *params, uint16_t *result);
static uint8_t getNumberOfChannels(const uint8_t channelsList);
static uint32_t getBitRate(I2S_Handle handle, const I2S_Params *params);
static uint16_t computeMemoryStep(I2S_Handle handle,
                                  I2S_DataInterfaceUse expectedUseSD0,
                                  I2S_DataInterfaceUse expectedUseSD1);
static void updatePointer(I2S_Handle handle, I2SWFF3_Interface *interface);

/* Extern globals */
extern const I2S_Config I2S_config[];
extern const uint_least8_t I2S_count;

/* Static globals */
static bool isInitialized = false;

/*
 *  ======== I2S_init ========
 */
void I2S_init(void)
{
    if (!isInitialized)
    {
        isInitialized = true;
    }
}

/*
 *  ======== I2S_open ========
 */
I2S_Handle I2S_open(uint_least8_t index, I2S_Params *params)
{
    I2S_Handle handle;
    uintptr_t key;
    I2SWFF3_Object *object;
    I2SWFF3_HWAttrs const *hwAttrs;

    handle  = (I2S_Handle) & (I2S_config[index]);
    object  = handle->object;
    hwAttrs = handle->hwAttrs;

    DebugP_assert(index < I2S_count);

    key = HwiP_disable();

    /* Return early if module is not initialized or if the object is already
     * open.
     */
    if (!isInitialized || object->isOpen)
    {
        HwiP_restore(key);
        return NULL;
    }

    /* Configure the I2S object attributes and verify the parameters.
     * Return early if parameters are invalid.
     */
    if (!configObject(handle, params))
    {
        /* The parameters provided are not valid. */
        HwiP_restore(key);
        return NULL;
    }

    /* Configure IOs, always succeeds */
    initIO(handle);

    object->isOpen = true;

    HwiP_restore(key);

    /* Register power dependency - i.e. power up and enable clock for I2S. */
    Power_setDependency(PowerWFF3_PERIPH_I2S);

    /* Register notification functions */
    Power_registerNotify(&object->i2sPostObj, PowerWFF3_AWAKE_SLEEP, (Power_NotifyFxn)i2sPostNotify, (uintptr_t)handle);

    HwiP_Params hwiParams;

    /* Register HW interrupt */
    HwiP_Params_init(&hwiParams);
    hwiParams.arg      = (uintptr_t)handle;
    hwiParams.priority = hwAttrs->intPriority;
    HwiP_construct(&(object->hwi), INT_I2S_IRQ_REQ, (HwiP_Fxn)I2S_hwiIntFxn, &hwiParams);

    HwiP_clearInterrupt(INT_I2S_IRQ_REQ);

    return handle;
}

/*
 *  ======== I2S_close ========
 */
void I2S_close(I2S_Handle handle)
{
    I2SWFF3_Object *object = handle->object;

    /* Disable I2S interrupts. */
    I2SDisableInt(I2S_BASE, I2S_INT_ALL);
    HwiP_destruct(&(object->hwi));

    /* Wait for end of started transactions */
    while ((I2SGetInPointerNext(I2S_BASE) != 0U) || (I2SGetOutPointerNext(I2S_BASE) != 0U)) {}

    while ((I2SGetInPointer(I2S_BASE) != 0U) || (I2SGetOutPointer(I2S_BASE) != 0U)) {}

    I2SSetInPointer(I2S_BASE, 0U);
    I2SSetOutPointer(I2S_BASE, 0U);

    I2SConfigureInSampleStampTrigger(I2S_BASE, I2S_STMP_SATURATION);
    I2SConfigureOutSampleStampTrigger(I2S_BASE, I2S_STMP_SATURATION);

    /* Disable I2S module */
    I2SStop(I2S_BASE);
    I2SDisableSampleStamp(I2S_BASE);

    /* Disable controller generated clocks (if they were previously enabled) */
    I2SDisableControllerClocks(I2S_BASE);

    /* Disable the audio clock */
    I2SDisableAdfs(I2S_BASE);

    /* Deallocate pins */
    finalizeIO(handle);

    /* Unregister power notification objects */
    Power_unregisterNotify(&object->i2sPostObj);

    /* Release power dependency - i.e. potentially power down serial domain. */
    Power_releaseDependency(PowerWFF3_PERIPH_I2S);

    /* Mark the module as available */
    object->isOpen = false;
}

/*
 *  ======== I2S_setReadQueueHead ========
 */
void I2S_setReadQueueHead(I2S_Handle handle, I2S_Transaction *transaction)
{

    DebugP_assert(&transaction != 0x0);

    I2SWFF3_Object *object       = handle->object;
    I2SWFF3_Interface *interface = &object->read;

    interface->activeTransfer = transaction;
}

/*
 *  ======== I2S_setWriteQueueHead ========
 */
void I2S_setWriteQueueHead(I2S_Handle handle, I2S_Transaction *transaction)
{

    DebugP_assert(&transaction != 0x0);

    I2SWFF3_Object *object       = handle->object;
    I2SWFF3_Interface *interface = &object->write;

    interface->activeTransfer = transaction;
}

/*
 *  ======== I2S_startClocks ========
 */
void I2S_startClocks(I2S_Handle handle)
{

    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    initHw(handle);
    enableClocks(handle);
}

/*
 *  ======== I2S_stopClocks ========
 */
void I2S_stopClocks(I2S_Handle handle)
{

    I2SClearInt(I2S_BASE, I2S_INT_ALL);

    I2SDisableInt(I2S_BASE,
                  (uint32_t)I2S_INT_TIMEOUT | (uint32_t)I2S_INT_BUS_ERR | (uint32_t)I2S_INT_WCLK_ERR |
                      (uint32_t)I2S_INT_PTR_ERR);

    I2SStop(I2S_BASE);
    I2SDisableSampleStamp(I2S_BASE);

    /* Disable controller generated clocks (if they were previously enabled) */
    I2SDisableControllerClocks(I2S_BASE);

    /* Disable the audio clock (if it was previously enabled) */
    I2SDisableAdfs(I2S_BASE);

    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);
}

/*
 *  ======== I2S_startRead ========
 */
void I2S_startRead(I2S_Handle handle)
{
    I2SWFF3_Object *object = handle->object;

    /* If a read interface is activated */
    if (object->read.memoryStep != 0)
    {

        /* Enable I2S Hardware Interrupts */
        I2SEnableInt(I2S_BASE,
                     (uint32_t)I2S_INT_DMA_IN | (uint32_t)I2S_INT_TIMEOUT | (uint32_t)I2S_INT_BUS_ERR |
                         (uint32_t)I2S_INT_WCLK_ERR | (uint32_t)I2S_INT_PTR_ERR);

        /* At startup, INPTRNEXT must be written twice. The first value will be
         * directly copy to INPTR.
         */
        object->ptrUpdateFxn(handle, &object->read);
        object->ptrUpdateFxn(handle, &object->read);

        /* Configuring sample stamp generator will trigger the audio stream to
         * start.
         */
        I2SConfigureInSampleStampTrigger(I2S_BASE, (HWREGH(I2S_BASE + I2S_O_STMPWCNT) + object->startUpDelay));
    }
}

/*
 *  ======== I2S_startWrite ========
 */
void I2S_startWrite(I2S_Handle handle)
{

    I2SWFF3_Object *object = handle->object;

    /* If a write interface is activated */
    if (object->write.memoryStep != 0)
    {

        /* Enable I2S Hardware Interrupts */
        I2SEnableInt(I2S_BASE,
                     (uint32_t)I2S_INT_DMA_OUT | (uint32_t)I2S_INT_TIMEOUT | (uint32_t)I2S_INT_BUS_ERR |
                         (uint32_t)I2S_INT_WCLK_ERR | (uint32_t)I2S_INT_PTR_ERR);

        /* At startup, OUTPTRNEXT must be written twice. The first value will be
         * directly copy to OUTPTR.
         */
        object->ptrUpdateFxn(handle, &object->write);
        object->ptrUpdateFxn(handle, &object->write);

        /* Configuring sample stamp generator will trigger the audio stream to
         * start.
         */
        I2SConfigureOutSampleStampTrigger(I2S_BASE, (HWREGH(I2S_BASE + I2S_O_STMPWCNT) + object->startUpDelay));
    }
}

/*
 *  ======== I2S_stopRead ========
 */
void I2S_stopRead(I2S_Handle handle)
{

    I2SWFF3_Object *object = handle->object;

    /* If a read interface is activated */
    if (object->read.memoryStep != 0)
    {

        /* Disable DMA_IN interrupts: we do not need anymore to refresh IN_PTR */
        I2SDisableInt(I2S_BASE, I2S_INT_DMA_IN);

        /* Wait for end of started transfers */
        while (I2SGetInPointerNext(I2S_BASE) != 0U) {}
        while (I2SGetInPointer(I2S_BASE) != 0U) {}

        I2SClearInt(I2S_BASE, I2S_INT_DMA_IN);
        I2SClearInt(I2S_BASE, I2S_INT_PTR_ERR);

        I2SConfigureInSampleStampTrigger(I2S_BASE, I2S_STMP_SATURATION);

        I2SSetInPointer(I2S_BASE, 0U);
    }
}

/*
 *  ======== I2S_stopWrite ========
 */
void I2S_stopWrite(I2S_Handle handle)
{

    I2SWFF3_Object *object = handle->object;

    /* If a write interface is activated */
    if (object->write.memoryStep != 0)
    {

        /* Disable DMA_OUT interrupts: we do not need anymore to refresh OUT_PTR */
        I2SDisableInt(I2S_BASE, I2S_INT_DMA_OUT);

        /* Wait for end of started transactions */
        while (I2SGetOutPointerNext(I2S_BASE) != 0U) {}
        while (I2SGetOutPointer(I2S_BASE) != 0U) {}

        I2SClearInt(I2S_BASE, I2S_INT_DMA_OUT);
        I2SClearInt(I2S_BASE, I2S_INT_PTR_ERR);

        I2SConfigureOutSampleStampTrigger(I2S_BASE, I2S_STMP_SATURATION);

        I2SSetOutPointer(I2S_BASE, 0U);
    }
}

/*
 *  ======== I2S_hwiIntFxn ========
 *  Hwi function that processes I2S interrupts.
 */
static void I2S_hwiIntFxn(uintptr_t arg)
{

    I2S_Handle handle      = (I2S_Handle)arg;
    I2SWFF3_Object *object = handle->object;
    uint16_t errStatus     = 0U;

    uint32_t interruptStatus = I2SIntStatus(I2S_BASE, true);

    /* I2S_INT_PTR_ERR flag should be consider if and only if I2S_INT_DMA_IN or
     * I2S_INT_DMA_OUT is raised at the same time.
     */
    if ((((interruptStatus & (uint32_t)I2S_INT_PTR_ERR) != 0U) &&
         ((((interruptStatus & (uint32_t)I2S_INT_DMA_IN) != 0U)) ||
          ((interruptStatus & (uint32_t)I2S_INT_DMA_OUT) != 0U))))
    {

        if ((interruptStatus & (uint32_t)I2S_INT_DMA_IN) != 0U)
        {
            /* Try to update IN_PTR */
            object->ptrUpdateFxn(handle, &object->read);
            /* Check if we could clear I2S_INT_DMA_IN flag */
            interruptStatus = I2SIntStatus(I2S_BASE, true);
            /* I2S_INT_PTR_ERR is confirmed if we could not clear I2S_INT_DMA_IN
             * flag.
             */
            if (((interruptStatus & (uint32_t)I2S_INT_PTR_ERR) != 0U) &&
                ((interruptStatus & (uint32_t)I2S_INT_DMA_IN) != 0U))
            {
                I2SClearInt(I2S_BASE, I2S_INT_PTR_ERR);
                errStatus = errStatus | I2S_PTR_READ_ERROR;
            }
        }

        if ((interruptStatus & (uint32_t)I2S_INT_DMA_OUT) != 0U)
        {
            /* Try to update OUT_PTR */
            object->ptrUpdateFxn(handle, &object->write);
            /* Check if we could clear I2S_INT_DMA_OUT flag */
            interruptStatus = I2SIntStatus(I2S_BASE, true);
            /* I2S_INT_PTR_ERR is confirmed if we could not clear
             * I2S_INT_DMA_OUT flag.
             */
            if (((interruptStatus & (uint32_t)I2S_INT_PTR_ERR) != 0U) &&
                ((interruptStatus & (uint32_t)I2S_INT_DMA_OUT) != 0U))
            {
                I2SClearInt(I2S_BASE, I2S_INT_PTR_ERR);
                errStatus = errStatus | I2S_PTR_WRITE_ERROR;
            }
        }
    }
    else if ((interruptStatus & (uint32_t)I2S_INT_PTR_ERR) != 0U)
    {
        /* I2S_INT_PTR_ERR must not be considered as no I2S_INT_DMA_xxx flag is
         * set.
         */
        I2SClearInt(I2S_BASE, I2S_INT_PTR_ERR);
    }

    if ((interruptStatus & (uint32_t)I2S_INT_DMA_IN) != 0U)
    {
        object->ptrUpdateFxn(handle, &object->read);
    }

    if ((interruptStatus & (uint32_t)I2S_INT_DMA_OUT) != 0U)
    {
        object->ptrUpdateFxn(handle, &object->write);
    }

    if ((interruptStatus & (uint32_t)I2S_INT_TIMEOUT) != 0U)
    {
        I2SClearInt(I2S_BASE, I2S_INT_TIMEOUT);
        errStatus = errStatus | I2S_TIMEOUT_ERROR;
    }

    if ((interruptStatus & (uint32_t)I2S_INT_BUS_ERR) != 0U)
    {
        I2SClearInt(I2S_BASE, I2S_INT_BUS_ERR);
        errStatus = errStatus | I2S_BUS_ERROR;
    }

    if ((interruptStatus & (uint32_t)I2S_INT_WCLK_ERR) != 0U)
    {
        I2SClearInt(I2S_BASE, I2S_INT_WCLK_ERR);
        errStatus = errStatus | I2S_WS_ERROR;
    }

    if (errStatus != 0U)
    {
        object->errorCallback(handle, errStatus, NULL);
    }
}

/*
 *  ======== initHw ========
 *  This functions initializes the I2S hardware module.
 *
 *  @pre    Function assumes that the I2S handle is pointing to a hardware
 *          module which has already been opened.
 */
static void initHw(I2S_Handle handle)
{
    /* Configure serial format. */
    configSerialFormat(handle);
    /* Configure the channels used on each data interface. */
    configChannels(handle);
    /* Configure the clocks for the CCLK, SCK and WS signals. */
    configClocks(handle);
}

/*
 *  ======== updatePointer ========
 */
static void updatePointer(I2S_Handle handle, I2SWFF3_Interface *interface)
{

    I2S_Transaction *transaction = interface->activeTransfer;

    if (transaction != NULL)
    {

        /* Critical section to prevent any modification or deletion of the
         * current transaction.
         */
        uintptr_t key;
        key = HwiP_disable();

        /* Transaction */
        if ((transaction->bytesTransferred + interface->memoryStep) > transaction->bufSize)
        {
            /* The current transaction is over */
            I2S_Transaction *transactionFinished = transaction;
            transaction                          = (I2S_Transaction *)List_next(&transactionFinished->queueElement);
            interface->activeTransfer            = transaction;

            transactionFinished->numberOfCompletions++;
            transactionFinished->untransferredBytes = transactionFinished->bufSize -
                                                      transactionFinished->bytesTransferred;
            transactionFinished->bytesTransferred = 0;

            if (transaction != NULL)
            {
                interface->pointerSet(I2S_BASE, ((uint32_t)transaction->bufPtr + transaction->bytesTransferred));
                transaction->bytesTransferred += interface->memoryStep;
                interface->callback(handle, I2S_TRANSACTION_SUCCESS, transactionFinished);
            }
            else
            {
                /* Not anymore transaction */
                interface->callback(handle, I2S_ALL_TRANSACTIONS_SUCCESS, transactionFinished);

                /* If needed the interface must be stopped */
                if (interface->activeTransfer != NULL)
                {
                    /* Application called I2S_setXxxxQueueHead() -> new
                     * transfers can be executed next time.
                     */
                }
                else if ((I2S_Transaction *)List_next(&transactionFinished->queueElement) != NULL)
                {
                    /* Application queued transactions after the transaction
                     * finished -> activeTransfer must be modified and transfers
                     * can be executed next time.
                     */
                    interface->activeTransfer = (I2S_Transaction *)List_next(&transactionFinished->queueElement);
                }
                else
                {
                    /* Application did nothing, we need to stop the interface to
                     * avoid errors. However, we cannot spin here while the
                     * hardware stops, this is an ISR context!
                     */
                    if (interface->stopInterface == I2S_stopRead)
                    {
                        I2SDisableInt(I2S_BASE, I2S_INT_DMA_IN);

                        I2SClearInt(I2S_BASE, I2S_INT_DMA_IN);
                        I2SClearInt(I2S_BASE, I2S_INT_PTR_ERR);

                        I2SConfigureInSampleStampTrigger(I2S_BASE, I2S_STMP_SATURATION);

                        I2SSetInPointer(I2S_BASE, 0U);
                    }

                    if (interface->stopInterface == I2S_stopWrite)
                    {
                        I2SDisableInt(I2S_BASE, I2S_INT_DMA_OUT);

                        I2SClearInt(I2S_BASE, I2S_INT_DMA_OUT);
                        I2SClearInt(I2S_BASE, I2S_INT_PTR_ERR);

                        I2SConfigureOutSampleStampTrigger(I2S_BASE, I2S_STMP_SATURATION);

                        I2SSetOutPointer(I2S_BASE, 0U);
                    }
                }
            }
        }
        else
        {
            interface->pointerSet(I2S_BASE, ((uint32_t)transaction->bufPtr + transaction->bytesTransferred));
            transaction->bytesTransferred += interface->memoryStep;
        }

        HwiP_restore(key);
    }
    else
    {
        /* No element in the queue: do nothing */
    }
}

/*
 *  ======== configObject ========
 */
static bool configObject(I2S_Handle handle, I2S_Params *params)
{

    I2SWFF3_Object *object = handle->object;
    I2SWFF3_DataInterface *SD0;
    I2SWFF3_DataInterface *SD1;

    bool retVal = true;

    /* Get the pointer to the SD0 and SD1 interfaces*/
    SD0 = &object->dataInterfaceSD0;
    SD1 = &object->dataInterfaceSD1;

    if (params == NULL)
    {
        /* This module cannot be open if the user does not provide the expected
         * pointers callback. So it is no point to try to load the default value
         * here.
         */
        retVal = false;
    }
    else
    {
        object->moduleRole        = params->moduleRole;
        object->invertWS          = params->invertWS;
        object->samplingEdge      = params->samplingEdge;
        object->beforeWordPadding = params->beforeWordPadding;
        object->afterWordPadding  = params->afterWordPadding;
        object->phaseType         = params->phaseType;
        object->bitsPerWord       = params->bitsPerWord;
        object->startUpDelay      = params->startUpDelay;

        object->dataShift = (params->trueI2sFormat) ? 1 : 0;

        if (params->memorySlotLength == I2S_MEMORY_LENGTH_16BITS)
        {
            object->memorySlotLength = I2S_MEM_LENGTH_16;
        }
        else if (params->memorySlotLength == I2S_MEMORY_LENGTH_32BITS)
        {
            object->memorySlotLength = I2S_MEM_LENGTH_32;
        }
        else
        {
            retVal = false;
        }
        object->read.pointerSet     = I2SSetInPointer;
        object->read.stopInterface  = I2S_stopRead;
        object->write.pointerSet    = I2SSetOutPointer;
        object->write.stopInterface = I2S_stopWrite;
        object->ptrUpdateFxn        = updatePointer;

        SD0->interfaceConfig      = params->SD0Use;
        SD0->channelsUsed         = params->SD0Channels;
        SD0->numberOfChannelsUsed = getNumberOfChannels((uint8_t)SD0->channelsUsed);
        SD1->interfaceConfig      = params->SD1Use;
        SD1->channelsUsed         = params->SD1Channels;
        SD1->numberOfChannelsUsed = getNumberOfChannels((uint8_t)SD1->channelsUsed);

        if (params->CCLKDivider == 1U)
        {
            retVal = false;
        }
        object->CCLKDivider = params->CCLKDivider;
        uint16_t SCKDivider = 0U;
        if (!computeSCKDivider(handle, params, &SCKDivider))
        {
            retVal = false;
        }
        object->SCKDivider = SCKDivider;
        uint16_t WSDivider = 0U;
        if (!computeWSDivider(handle, params, &WSDivider))
        {
            retVal = false;
        }
        object->WSDivider = WSDivider;

        object->read.memoryStep  = computeMemoryStep(handle, I2S_SD0_INPUT, I2S_SD1_INPUT);
        object->write.memoryStep = computeMemoryStep(handle, I2S_SD0_OUTPUT, I2S_SD1_OUTPUT);

        /* If the user set a fixed length of the buffers, we can optimize the
         * runtime by setting the DMA buffer length.
         */
        if (params->fixedBufferLength == 0U)
        {
            retVal = false;
        }
        else
        {
            if (params->fixedBufferLength != 1U)
            {
                uint16_t memoryStep = ((object->read.memoryStep > object->write.memoryStep) ? object->read.memoryStep
                                                                                            : object->write.memoryStep);
                if (memoryStep != 0U)
                {
                    uint8_t dmaBuffSizeDivider = 1U;
                    uint16_t dmaBuffSizeConfig = (uint16_t)(((((params->fixedBufferLength) / memoryStep) * 2U)) /
                                                            dmaBuffSizeDivider);

                    /* The value of the DMA buffer size is limited to 256 */
                    while (dmaBuffSizeConfig > 256U)
                    {
                        dmaBuffSizeDivider = dmaBuffSizeDivider * 2;
                        dmaBuffSizeConfig  = (uint16_t)(((((params->fixedBufferLength) / memoryStep) * 2U)) /
                                                       dmaBuffSizeDivider);
                    }

                    /* dmaBuffSizeConfig <= 256 */
                    object->dmaBuffSizeConfig = (uint8_t)dmaBuffSizeConfig;

                    object->read.memoryStep  = (object->read.memoryStep != 0U)
                                                   ? (uint16_t)(params->fixedBufferLength / dmaBuffSizeDivider)
                                                   : 0U;
                    object->write.memoryStep = (object->write.memoryStep != 0U)
                                                   ? (uint16_t)(params->fixedBufferLength / dmaBuffSizeDivider)
                                                   : 0U;
                }
            }
            else
            {
                object->dmaBuffSizeConfig = 2U;
            }
        }

        object->read.callback = params->readCallback;
        if ((object->read.callback == NULL) && (object->read.memoryStep != 0U))
        {
            retVal = false;
        }
        object->write.callback = params->writeCallback;
        if ((object->write.callback == NULL) && (object->write.memoryStep != 0U))
        {
            retVal = false;
        }
        object->errorCallback = params->errorCallback;
        if (object->errorCallback == NULL)
        {
            retVal = false;
        }

        object->read.activeTransfer  = NULL;
        object->write.activeTransfer = NULL;
    }

    return retVal;
}

/*
 *  ======== initIO ========
 */
static void initIO(I2S_Handle handle)
{
    I2SWFF3_HWAttrs const *hwAttrs;

    /* Get the pointer to the object and hwAttrs */
    hwAttrs = handle->hwAttrs;

    /* Make sure all pins have their input buffers enabled */
    GPIO_setConfigAndMux(hwAttrs->wsPin, GPIO_CFG_INPUT, hwAttrs->wsPinMux);
    GPIO_setConfigAndMux(hwAttrs->sckPin, GPIO_CFG_INPUT, hwAttrs->sckPinMux);
    GPIO_setConfigAndMux(hwAttrs->cclkPin, GPIO_CFG_INPUT, hwAttrs->cclkPinMux);
    GPIO_setConfigAndMux(hwAttrs->sd0Pin, GPIO_CFG_INPUT, hwAttrs->sd0PinMux);
    GPIO_setConfigAndMux(hwAttrs->sd1Pin, GPIO_CFG_INPUT, hwAttrs->sd1PinMux);
}

/*
 *  ======== finalizeIO ========
 */
static void finalizeIO(I2S_Handle handle)
{
    I2SWFF3_HWAttrs const *hwAttrs;

    /* Get the pointer to the object and hwAttrs */
    hwAttrs = handle->hwAttrs;

    GPIO_resetConfig(hwAttrs->wsPin);
    GPIO_resetConfig(hwAttrs->sckPin);
    GPIO_resetConfig(hwAttrs->cclkPin);
    GPIO_resetConfig(hwAttrs->sd0Pin);
    GPIO_resetConfig(hwAttrs->sd1Pin);
}

/*
 *  ======== getNumberOfChannels ========
 */
static uint8_t getNumberOfChannels(const uint8_t channelsList)
{

    uint8_t i              = 0;
    uint8_t nbChannelsUsed = 0;
    for (i = 0; i <= (I2S_NB_CHANNELS_MAX - 1U); i++)
    {
        if (((channelsList >> i) & 1U) == 1U)
        {
            nbChannelsUsed++;
        }
    }
    return nbChannelsUsed;
}

/*
 *  ======== computeSCKDivider ========
 */
static bool computeSCKDivider(I2S_Handle handle, const I2S_Params *params, uint16_t *result)
{
    I2SWFF3_HWAttrs const *hwAttrs;
    hwAttrs = handle->hwAttrs;

    uint32_t expectedBitRate = getBitRate(handle, params);
    uint32_t freqDividerSCK  = 0U;

    bool retVal = true;

    *result = 0;

    if (expectedBitRate == 0U)
    {
        retVal = false;
    }
    else
    {

        /* We want to round the integer division: ROUND(a/b)=(a+b/2)/b */
        freqDividerSCK = ((hwAttrs->audioClkFreq + expectedBitRate / 2) / expectedBitRate);

        if ((freqDividerSCK < I2S_CLOCK_DIVIDER_MIN) || (freqDividerSCK > I2S_CLOCK_DIVIDER_MAX))
        {
            retVal = false;
        }
        else
        {
            /* If we reach this code it means we have freqDividerSCK <= 1024 */
            uint16_t u16FreqDividerSCK = (uint16_t)freqDividerSCK;
            *result                    = u16FreqDividerSCK;
        }
    }
    return retVal;
}

/*
 *  ======== computeWSDivider ========
 */
static bool computeWSDivider(I2S_Handle handle, const I2S_Params *params, uint16_t *result)
{

    I2SWFF3_Object const *object;
    I2SWFF3_DataInterface const *SD0;
    I2SWFF3_DataInterface const *SD1;

    bool retVal            = true;
    uint8_t numbOfChannels = 0U;

    /* Get the pointer to the SD0 and SD1 interfaces*/
    object = handle->object;
    SD0    = &object->dataInterfaceSD0;
    SD1    = &object->dataInterfaceSD1;

    *result = 0x0000;

    if (SD0->interfaceConfig)
    {
        numbOfChannels = (numbOfChannels > SD0->numberOfChannelsUsed) ? numbOfChannels : SD0->numberOfChannelsUsed;
    }
    if (SD1->interfaceConfig)
    {
        numbOfChannels = (numbOfChannels > SD1->numberOfChannelsUsed) ? numbOfChannels : SD1->numberOfChannelsUsed;
    }

    uint16_t sampleLength = 0U;

    switch (object->phaseType)
    {

        case (I2S_PHASE_TYPE_DUAL):

            /* In dual-phase format, each phase represents a channel and is
             * divided into the three intervals:
             *
             * Data delay (optional): BCLK periods between the first WCLK edge
             * and MSB of the audio channel data transfered during the phase.
             *
             * Word: BCLK periods during which one sample word (a single
             * channel) is transfered.
             *
             * Idle (optional): BCLK periods between the word interval and the
             * next phase.
             */
            sampleLength += object->beforeWordPadding;
            sampleLength += object->bitsPerWord;
            sampleLength += object->afterWordPadding;

            /* WS is high for WDIV[9:0] (1 to 1023) SCK periods and low for
             * WDIV[9:0] (1 to 1023) SCK periods.
             * WS frequency = SCK frequency / (2 x WDIV[9:0])
             * Dual phase protocols don't accept more than two channels.
             */
            if (numbOfChannels <= 2U)
            {
                *result = sampleLength;
            }
            else
            {
                retVal = false;
            }
            break;

        case (I2S_PHASE_TYPE_SINGLE):

            /* In single phase format, from 1 to 8 sample words (channels) are
             * transfered back-to-back using a single phase. The phase is
             * divided into the three intervals:
             *
             * Data delay (optional) : BCLK periods between the first WCLK edge
             * and MSB of the FIRST audio channel
             * data transfered.
             *
             * Word: BCLK periods during which from 1 to 8 channels are
             * transfered back-to-back.
             *
             * Idle (optional): BCLK periods between the word interval and the
             * next phase.
             */
            sampleLength += object->beforeWordPadding;
            sampleLength += (object->bitsPerWord * numbOfChannels);
            sampleLength += object->afterWordPadding;

            /* WS is high for 1 SCK period and low for WDIV[9:0] (1 to 1023) SCK
             * periods.
             * WS frequency = SCK frequency / (1 + I2S:I2SWCLKDIV.WDIV[9:0])
             * Single phase protocols don't accept more than 8 channels
             */
            if (numbOfChannels <= 8U)
            {
                *result = sampleLength;
            }
            else
            {
                retVal = false;
            }
            break;

        default:
            retVal = false;
    }
    return retVal;
}

/*
 *  ======== getBitRate ========
 */
static uint32_t getBitRate(I2S_Handle handle, const I2S_Params *params)
{

    I2SWFF3_Object const *object;
    I2SWFF3_DataInterface const *SD0;
    I2SWFF3_DataInterface const *SD1;
    uint32_t dataLength = 0U;

    /* Get the pointer to the SD0 and SD1 interfaces*/
    object = handle->object;
    SD0    = &object->dataInterfaceSD0;
    SD1    = &object->dataInterfaceSD1;

    uint16_t sampleLength = 0U;
    sampleLength += object->beforeWordPadding;
    sampleLength += object->bitsPerWord;
    sampleLength += object->afterWordPadding;

    uint32_t samplePerChannelPerSecond = params->samplingFrequency;
    uint8_t numbOfChannels             = 0U;
    if (SD0->interfaceConfig)
    {
        uint8_t numbOfChannelsSD0 = (object->phaseType == I2S_PHASE_TYPE_DUAL) ? 2U : SD0->numberOfChannelsUsed;
        numbOfChannels            = (numbOfChannelsSD0 > numbOfChannels) ? numbOfChannelsSD0 : numbOfChannels;
    }
    if (SD1->interfaceConfig)
    {
        uint8_t numbOfChannelsSD1 = (object->phaseType == I2S_PHASE_TYPE_DUAL) ? 2U : SD1->numberOfChannelsUsed;
        numbOfChannels            = (numbOfChannelsSD1 > numbOfChannels) ? numbOfChannelsSD1 : numbOfChannels;
    }

    /* No risk of overflow: highest possible value is 24 000 000 (any higher
     * value has no sense).
     */
    dataLength = (uint32_t)((uint32_t)numbOfChannels * (uint32_t)sampleLength);
    return (dataLength * samplePerChannelPerSecond);
}

/*
 *  ======== configSerialFormat ========
 */
static void configSerialFormat(I2S_Handle handle)
{

    I2SWFF3_Object const *object;

    /* Get the pointer to the object*/
    object = handle->object;

    /*
     * Word length depends on the phase type:
     * For dual-phase format (I2S, LJF, RJF) this is the maximum number of bits
     * per word (object->bitsPerWord + object->afterWordPadding).
     * For single-phase format (DSP) this is the exact number of bits per word
     * (object->bitsPerWord).
     */
    I2SConfigureFormat(I2S_BASE,
                       (object->beforeWordPadding + object->dataShift),
                       object->memorySlotLength,
                       ((object->samplingEdge == I2S_SAMPLING_EDGE_RISING) ? I2S_POS_EDGE : I2S_NEG_EDGE),
                       (object->phaseType == I2S_PHASE_TYPE_DUAL),
                       ((object->phaseType == I2S_PHASE_TYPE_DUAL) ? (object->bitsPerWord + object->afterWordPadding)
                                                                   : object->bitsPerWord));

    /* Set the WCLK counter period */
    I2SConfigureWclkCounterPeriod(I2S_BASE, object->dmaBuffSizeConfig);

    /* To avoid false start-up triggers, the input and output triggers must
     * initially be equal to or higher than the WCLK counter period, which is
     * set as above. Since, I2S_STMP_SATURATION > 256 this should prevent false
     * triggers. 256 is used above because it is the maximum allowed value of
     * dmaBuffSizeConfig, guaranteed by configObject().
     */
    I2SConfigureInSampleStampTrigger(I2S_BASE, I2S_STMP_SATURATION);
    I2SConfigureOutSampleStampTrigger(I2S_BASE, I2S_STMP_SATURATION);
}

/*
 *  ======== configChannels ========
 */
static void configChannels(I2S_Handle handle)
{

    I2SWFF3_Object const *object;
    I2SWFF3_DataInterface const *SD0;
    I2SWFF3_DataInterface const *SD1;

    /* Get the pointer to the SD0 and SD1 interfaces*/
    object = handle->object;
    SD0    = &object->dataInterfaceSD0;
    SD1    = &object->dataInterfaceSD1;

    I2SConfigureFrame(I2S_BASE,
                      (uint8_t)SD0->interfaceConfig,
                      (uint8_t)SD0->channelsUsed,
                      (uint8_t)SD1->interfaceConfig,
                      (uint8_t)SD1->channelsUsed);
}

/*
 *  ======== configClocks ========
 */
static void configClocks(I2S_Handle handle)
{

    I2SWFF3_Object const *object;

    /* Get the pointer to the object*/
    object = handle->object;

    I2SConfigureClocks(I2S_BASE,
                       (bool)object->moduleRole,
                       object->invertWS,
                       (object->phaseType == I2S_PHASE_TYPE_DUAL),
                       object->CCLKDivider,
                       object->WSDivider,
                       object->SCKDivider);
}

/*
 *  ======== enableClocks ========
 */
static void enableClocks(I2S_Handle handle)
{

    I2SWFF3_Object const *object;
    I2SWFF3_HWAttrs const *hwAttrs;
    I2SWFF3_ADFS adfs;

    /* Get the pointer to the object and hwAttrs */
    object  = handle->object;
    hwAttrs = handle->hwAttrs;

    I2SStart(I2S_BASE, object->dmaBuffSizeConfig);

    /* Enable sample stamps */
    I2SEnableSampleStamp(I2S_BASE);

    /* Reset WCLK counter */
    I2SResetWclkCounter(I2S_BASE);

    if (object->moduleRole == I2S_CONTROLLER)
    {
        adfs = hwAttrs->adfs;

        /* To select the ADFS input and to configure the ADFS it is necessary to
         * disable the I2S module clock.
         */
        I2SDisableClk(I2S_BASE);

        /* Select the source clock source and configure the ADFS. The
         * selected clock source is used by the ADFS to generate the audio
         * clock, which is used to generate the I2S clocks.
         */
        I2SSelectAdfsInputClk(I2S_BASE, hwAttrs->clkSrc);
        I2SConfigureAdfs(I2S_BASE, adfs.tref, adfs.delta, adfs.deltaSign, adfs.div);

        /* Enable the ADFS module and re-enable the I2S module clock */
        I2SEnableAdfs(I2S_BASE);
        I2SEnableClk(I2S_BASE);

        /* Enable controller generated clocks */
        I2SEnableControllerClocks(I2S_BASE);
    }
}

/*
 *  ======== computeMemoryStep ========
 */
static uint16_t computeMemoryStep(I2S_Handle handle,
                                  I2S_DataInterfaceUse expectedUseSD0,
                                  I2S_DataInterfaceUse expectedUseSD1)
{

    I2SWFF3_Object const *object;
    uint8_t numbOfChannels     = 0;
    uint8_t sampleMemoryLength = 16;
    uint16_t memoryNeeded      = 0;
    I2SWFF3_DataInterface const *SD0;
    I2SWFF3_DataInterface const *SD1;

    const uint8_t byteLength = 8U;

    /* Get the pointer to the object*/
    object = handle->object;
    SD0    = &object->dataInterfaceSD0;
    SD1    = &object->dataInterfaceSD1;

    if (SD0->interfaceConfig == expectedUseSD0)
    {
        numbOfChannels += SD0->numberOfChannelsUsed;
    }

    if (SD1->interfaceConfig == expectedUseSD1)
    {
        numbOfChannels += SD1->numberOfChannelsUsed;
    }

    if (object->memorySlotLength == I2S_MEM_LENGTH_32)
    {
        sampleMemoryLength = 32;
    }

    /* In the worst case we have 16x32x2=1024 < 2^16 */
    memoryNeeded = (uint16_t)((uint16_t)numbOfChannels * (uint16_t)sampleMemoryLength * (uint16_t)2U);

    /* Bits to byte conversion: we manage to have full bytes */
    if ((memoryNeeded % byteLength) != 0U)
    {
        memoryNeeded += (byteLength - (memoryNeeded % byteLength));
    }
    memoryNeeded = memoryNeeded / byteLength;

    return memoryNeeded;
}

/*
 *  ======== i2sPostNotify ========
 *  This functions is called to notify the I2S driver of an ongoing transition
 *  out of sleep mode.
 *
 *  @pre    Function assumes that the I2S handle (clientArg) is pointing to a
 *          hardware module which has already been opened.
 */
static int i2sPostNotify(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg)
{

    /* Reconfigure the hardware if returning from sleep */
    if (eventType == (uint32_t)PowerWFF3_AWAKE_SLEEP)
    {
        initHw((I2S_Handle)clientArg);
    }

    return Power_NOTIFYDONE;
}
