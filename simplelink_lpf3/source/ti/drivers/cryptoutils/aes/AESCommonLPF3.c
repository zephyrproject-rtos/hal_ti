/*
 * Copyright (c) 2021-2023, Texas Instruments Incorporated
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
#include <stdint.h>
#include <string.h>

#include <ti/drivers/AESCommon.h>
#include <ti/drivers/cryptoutils/aes/AESCommonLPF3.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceLPF3.h>
#include <ti/drivers/dma/UDMALPF3.h>
#include <ti/drivers/Power.h>

#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/aes.h)
#include DeviceFamily_constructPath(driverlib/udma.h)
#include DeviceFamily_constructPath(inc/hw_dma.h)
#include DeviceFamily_constructPath(inc/hw_evtsvt.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_types.h)

/* Static globals */
static bool AESCommon_isInitialized = false;

/* DMA Control Table Entries */
ALLOCATE_CONTROL_TABLE_ENTRY(dmaChannel4ControlTableEntry, DMA_CH4);
ALLOCATE_CONTROL_TABLE_ENTRY(dmaChannel5ControlTableEntry, DMA_CH5);

static volatile uDMAControlTableEntry *dmaPriControlTableEntryChA = &dmaChannel4ControlTableEntry;
static volatile uDMAControlTableEntry *dmaPriControlTableEntryChB = &dmaChannel5ControlTableEntry;

/* Forward declarations */
void AESCommonLPF3_setPowerConstraint(AESCommonLPF3_Object *object);
void AESCommonLPF3_releasePowerConstraint(AESCommonLPF3_Object *object);

/*
 *  ======== AESCommonLPF3_init ========
 */
void AESCommonLPF3_init(void)
{
    CryptoResourceLPF3_constructRTOSObjects();

    UDMALPF3_init();

    AESCommon_isInitialized = true;
}

/*
 *  ======== AESCommonLPF3_construct ========
 */
int_fast16_t AESCommonLPF3_construct(AESCommonLPF3_Object *object, AES_ReturnBehavior returnBehavior, uint32_t timeout)
{
    DebugP_assert(object);

    uintptr_t interruptKey = HwiP_disable();

    if (!AESCommon_isInitialized || object->isOpen)
    {
        HwiP_restore(interruptKey);

        return AES_STATUS_ERROR;
    }

    object->isOpen = true;

    HwiP_restore(interruptKey);

    object->returnBehavior = returnBehavior;

    if (returnBehavior == AES_RETURN_BEHAVIOR_BLOCKING)
    {
        object->semaphoreTimeout = timeout;
    }
    else
    {
        object->semaphoreTimeout = SemaphoreP_NO_WAIT;
    }

    if (returnBehavior != AES_RETURN_BEHAVIOR_POLLING)
    {
        /*
         * Configure DMA channels 4 & 5 for LAES TRG A & B respectively.
         * Channels 4 & 5 are the only channels which can be used with LAES
         * because channels 6 & 7 do not support the DMA Done signal.
         *
         * AES Channel A is used for input and Channel B is used for output.
         *
         * CMAC and CBC-MAC AES modes use input DMA only.
         */
        HWREG(EVTSVT_BASE + EVTSVT_O_DMACH4SEL) = EVTSVT_DMACH4SEL_IPID_LAESTRGA;
        HWREG(EVTSVT_BASE + EVTSVT_O_DMACH5SEL) = EVTSVT_DMACH5SEL_IPID_LAESTRGB;
    }

    object->cryptoResourceLocked = false;
    object->operationInProgress  = false;
    object->powerConstraintSet   = false;

    /* Set power dependency. Power up and enable clock for DMA peripheral */
    Power_setDependency(PowerLPF3_PERIPH_DMA);

    /* Set power dependency. Power up and enable clock for LAES peripheral */
    Power_setDependency(PowerLPF3_PERIPH_AES);

    return AES_STATUS_SUCCESS;
}

/*
 *  ======== AESCommonLPF3_close ========
 */
void AESCommonLPF3_close(AESCommonLPF3_Object *object)
{
    DebugP_assert(object);

    /* Mark the module as available */
    object->isOpen = false;

    /* Release power dependency on DMA module */
    Power_releaseDependency(PowerLPF3_PERIPH_DMA);

    /* Release power dependency on LAES module */
    Power_releaseDependency(PowerLPF3_PERIPH_AES);
}

/*
 *  ======== AESCommonLPF3_setOperationInProgress ========
 */
int_fast16_t AESCommonLPF3_setOperationInProgress(AESCommonLPF3_Object *object)
{
    uintptr_t interruptKey = HwiP_disable();

    if (object->operationInProgress)
    {
        HwiP_restore(interruptKey);

        return AES_STATUS_ERROR;
    }

    object->operationInProgress = true;

    HwiP_restore(interruptKey);

    return AES_STATUS_SUCCESS;
}

/*
 *  ======== AESCommonLPF3_setupOperation ========
 */
void AESCommonLPF3_setupOperation(CryptoKey *key, uint32_t autoCfgVal)
{
    /* Load Key */
    AESCommonLPF3_loadKey(key);

    /* Set AUTOCFG */
    AESSetAUTOCFG(autoCfgVal);
}

/*
 *  ======== AESCommonLPF3_loadKey ========
 */
void AESCommonLPF3_loadKey(const CryptoKey *key)
{
    const uint8_t *keyMaterial;

    /* Only plaintext CryptoKeys are supported currently */
    DebugP_assert((key->encoding == CryptoKey_PLAINTEXT) || (key->encoding == CryptoKey_BLANK_PLAINTEXT));

    keyMaterial = key->u.plaintext.keyMaterial;

    DebugP_assert(keyMaterial);

    /* AES engine supports only 128-bit (16-byte) keys. */
    DebugP_assert(key->u.plaintext.keyLength == AES_128_KEY_LENGTH_BYTES);

    /* Write keyMaterial to the AES engine */
    AESWriteKEY(keyMaterial);
}
/*
 *  ======== AESAESCommonLPF3_cleanup ========
 */
void AESCommonLPF3_cleanup(AESCommonLPF3_Object *object)
{
    if (object->returnBehavior != AES_RETURN_BEHAVIOR_POLLING)
    {
        AESSetIMASK((uint32_t)0U);
        AESDisableDMA();

        IntDisable(INT_AES_COMB);

        /*
         * Disable DMA channels A & B.  Assuming DMA channels are statically
         * mapped, this should always be safe to do. This must be done before
         * calling AESAbort.
         */
        UDMALPF3_channelDisable(AESCommonLPF3_DMA_CHA_BITMASK | AESCommonLPF3_DMA_CHB_BITMASK);
    }

    /*
     * Abort any spurious encryption and clear TXT, BUF, DMA, AUTOCFG registers.
     */
    AESAbort();

    /* Clear all AES interrupts */
    AESClearInterrupt(AES_ICLR_ALL);

    if (object->cryptoResourceLocked)
    {
        object->cryptoResourceLocked = false;
        /*
         * Grant access for other threads to use the crypto module.
         * The semaphore must be posted before the callbackFxn to allow
         * the chaining of operations.
         */
        CryptoResourceLPF3_releaseLock();
    }

    AESCommonLPF3_releasePowerConstraint(object);
}

/*
 *  ======== AESCommonLPF3_setupSegmentedOperation ========
 */
int_fast16_t AESCommonLPF3_setupSegmentedOperation(AESCommonLPF3_Object *object, const CryptoKey *key)
{
    int_fast16_t status;

    /* Check that there is no operation in progress for this driver instance */
    status = AESCommonLPF3_setOperationInProgress(object);

    if (status == AES_STATUS_SUCCESS)
    {
        /* Make internal copy of crypto key */
        object->key = *key;

        /* returnStatus is only changed in the case of an error or cancellation */
        object->returnStatus = AES_STATUS_SUCCESS;
    }

    return status;
}

/*
 *  ======== AESCommonLPF3_configInputDMA ========
 */
void AESCommonLPF3_configInputDMA(const void *input, size_t inputLength)
{
    uint32_t control;
    uint32_t numTransfers;

    /*
     * Set the source data width and address increment based upon the address
     * alignment. Arbitrate after 16-bytes (AES block size). No destination
     * address increment.
     */
#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 1)
    if (((uintptr_t)input & 0x1U) != 0U)
    {
        control      = UDMA_DST_INC_NONE | UDMA_SIZE_8 | UDMA_SRC_INC_8 | UDMA_ARB_16;
        numTransfers = (uint32_t)inputLength;
    }
    else if (((uintptr_t)input & 0x2U) != 0U)
    {
        control      = UDMA_DST_INC_NONE | UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_ARB_8;
        numTransfers = (uint32_t)inputLength >> 1;
    }
    else
#endif
    {
        control      = UDMA_DST_INC_NONE | UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_ARB_4;
        numTransfers = (uint32_t)inputLength >> 2;
    }

    /*
     * Setup DMA channel A Primary Control Struct:
     *  -
     */
    uDMASetChannelControl(dmaPriControlTableEntryChA, control);

    /*
     * Setup DMA channel A Primary Control Struct:
     *  - Mode = Basic
     *  - Input & Output end pointers
     *  - Set n-1, where n = number DMA transfers that the DMA cycle contains.
     */
    uDMASetChannelTransfer(dmaPriControlTableEntryChA,
                           UDMA_MODE_BASIC,
                           (void *)input,
                           (void *)(AES_BASE + AES_O_DMACHA),
                           numTransfers);

    /* Enable the channel for AES input */
    UDMALPF3_channelEnable(AESCommonLPF3_DMA_CHA_BITMASK);
}

/*
 *  ======== AESCommonLPF3_isDMALengthValid ========
 */
bool AESCommonLPF3_isDMALengthValid(const void *input, const void *output, size_t length)
{
    size_t maxLength = 4096;

#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 1)
    uintptr_t alignment = (uintptr_t)input | (uintptr_t)output;

    if (alignment & 0x1U)
    {
        maxLength = 1024;
    }
    else if (alignment & 0x2U)
    {
        maxLength = 2048;
    }
#endif
    return (length <= maxLength);
}

/*
 *  ======== AESCommonLPF3_configOutputDMA ========
 */
void AESCommonLPF3_configOutputDMA(void *output, size_t outputLength)
{
    uint32_t control;
    uint32_t numTransfers;

    /*
     * Set the source data width and address increment based upon the address
     * alignment. Arbitrate after 16-bytes (AES block size). No source address
     * increment.
     */
#if (AESCommonLPF3_UNALIGNED_IO_SUPPORT_ENABLE == 1)
    if (((uintptr_t)output & 0x1U) != 0U)
    {
        control      = UDMA_SRC_INC_NONE | UDMA_SIZE_8 | UDMA_DST_INC_8 | UDMA_ARB_16;
        numTransfers = outputLength;
    }
    else if (((uintptr_t)output & 0x2U) != 0U)
    {
        control      = UDMA_SRC_INC_NONE | UDMA_SIZE_16 | UDMA_DST_INC_16 | UDMA_ARB_8;
        numTransfers = outputLength >> 1;
    }
    else
#endif
    {
        control      = UDMA_SRC_INC_NONE | UDMA_SIZE_32 | UDMA_DST_INC_32 | UDMA_ARB_4;
        numTransfers = outputLength >> 2;
    }

    /*
     * Setup DMA channel B Primary Control struct control params:
     *  -
     */
    uDMASetChannelControl(dmaPriControlTableEntryChB, control);

    /*
     * Setup DMA channel B Primary Control struct transfer params:
     *  - Mode = Basic
     *  - Input & Output end pointers
     *  - Set n-1, where n = number DMA transfers that the DMA cycle contains.
     */
    uDMASetChannelTransfer(dmaPriControlTableEntryChB,
                           UDMA_MODE_BASIC,
                           (void *)(AES_BASE + AES_O_DMACHB),
                           output,
                           numTransfers);

    /* Enable the channel for AES input */
    UDMALPF3_channelEnable(AESCommonLPF3_DMA_CHB_BITMASK);
}

/*
 *  ======== AESCommonLPF3_cancelDMA ========
 */
void AESCommonLPF3_cancelDMA(bool cancelChannelB)
{
    IntDisable(INT_AES_COMB);
    AESSetIMASK((uint32_t)0U);
    AESDisableDMA();

    uint32_t channelBitMask = AESCommonLPF3_DMA_CHA_BITMASK;
    if (cancelChannelB)
    {
        channelBitMask |= AESCommonLPF3_DMA_CHB_BITMASK;
    }

    /* Disable DMA channel(s) */
    UDMALPF3_channelDisable(channelBitMask);

    /* Set DMA channels to STOP */
    uDMASetChannelTransfer(dmaPriControlTableEntryChA, UDMA_MODE_STOP, 0, 0, 0);

    if (cancelChannelB)
    {
        uDMASetChannelTransfer(dmaPriControlTableEntryChB, UDMA_MODE_STOP, 0, 0, 0);
    }

    /* Abort must be done after disabling DMA channels according to LAES spec */
    AESAbort();

    /* Clear all AES interrupts */
    AESClearInterrupt(AES_ICLR_ALL);
}

/*
 *  ======== AESCommonLPF3_cancelOperation ========
 */
void AESCommonLPF3_cancelOperation(AESCommonLPF3_Object *object, bool cancelDMAChannelB)
{
    if (object->returnBehavior != AES_RETURN_BEHAVIOR_POLLING)
    {
        AESCommonLPF3_cancelDMA(cancelDMAChannelB);
    }

    AESCommonLPF3_releasePowerConstraint(object);

    object->returnStatus = AES_STATUS_CANCELED;

    AESCommonLPF3_clearOperationInProgress(object);

    if (object->cryptoResourceLocked)
    {
        object->cryptoResourceLocked = false;
        /*
         * Grant access for other threads to use the crypto module.
         * The semaphore must be posted before the callbackFxn to allow
         * the chaining of operations.
         */
        CryptoResourceLPF3_releaseLock();
    }
}

/*
 *  ======== AESCommonLPF3_setupHwi ========
 */
void AESCommonLPF3_setupHwi(HwiP_Fxn hwiFxn, uintptr_t hwiFxnArg, uint8_t intPriority)
{
    HwiP_setFunc(&CryptoResourceLPF3_hwi, hwiFxn, hwiFxnArg);
    HwiP_setPriority(INT_AES_COMB, (uint32_t)intPriority);
    IntEnable((uint32_t)INT_AES_COMB);
}

/*
 *  ======== AESCommonLPF3_setPowerConstraint ========
 */
void AESCommonLPF3_setPowerConstraint(AESCommonLPF3_Object *object)
{
    /* Ignore return value since it always returns Power_SOK */
    (void)Power_setConstraint(PowerLPF3_DISALLOW_STANDBY);
    object->powerConstraintSet = true;
}

/*
 *  ======== AESCommonLPF3_releasePowerConstraint ========
 */
void AESCommonLPF3_releasePowerConstraint(AESCommonLPF3_Object *object)
{
    if (object->powerConstraintSet)
    {
        object->powerConstraintSet = false;
        /* Ignore return value since it always returns Power_SOK */
        (void)Power_releaseConstraint(PowerLPF3_DISALLOW_STANDBY);
    }
}

/*
 *  ======== AESCommonLPF3_setupDMA ========
 */
void AESCommonLPF3_setupDMA(AESCommonLPF3_Object *object, uint32_t dmaConfig)
{
    AESSetupDMA(dmaConfig);

    AESCommonLPF3_setPowerConstraint(object);
}

/*
 *  ======== AESCommonLPF3_cleanupHwi ========
 */
void AESCommonLPF3_cleanupHwi(AESCommonLPF3_Object *object)
{
    AESDisableDMA();
    AESSetIMASK((uint32_t)0U);
    /* Clear all AES interrupts */
    AESClearInterrupt(AES_ICLR_ALL);

    AESCommonLPF3_releasePowerConstraint(object);
}
