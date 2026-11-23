/*
 * Copyright (c) 2021-2026 Texas Instruments Incorporated
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
#include <ti/drivers/cryptoutils/aes/AESCommonXXF3.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceXXF3.h>
#include <ti/drivers/dma/UDMALPF3.h>
#include <ti/drivers/Power.h>

#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/aes.h)
#include DeviceFamily_constructPath(driverlib/udma.h)
#include DeviceFamily_constructPath(inc/hw_aes.h)
#include DeviceFamily_constructPath(inc/hw_dma.h)
#include DeviceFamily_constructPath(inc/hw_evtsvt.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_types.h)

#if ((DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) && (ENABLE_KEY_STORAGE == 1))
    #error "Key storage is not supported for CC23X0"
#endif

#if (ENABLE_KEY_STORAGE == 1)
    #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA.h>
    #include <ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_helpers.h>
    #include <ti/drivers/cryptoutils/hsm/HSMXXF3.h>
    #include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>
#endif

/* Static globals */
static bool AESCommon_isInitialized = false;

#ifndef TFM_BUILD
/* DMA Control Table Entries and channel masks from SysConfig. */
extern volatile uDMAControlTableEntry *AESCommonXXF3_dmaPriControlTableEntryChA;
extern volatile uDMAControlTableEntry *AESCommonXXF3_dmaPriControlTableEntryChB;
extern uint32_t AESCommonXXF3_dmaChannelMaskChA;
extern uint32_t AESCommonXXF3_dmaChannelMaskChB;
#endif

/* Forward declarations */
void AESCommonXXF3_setPowerConstraint(AESCommonXXF3_Object *object);
void AESCommonXXF3_releasePowerConstraint(AESCommonXXF3_Object *object);

/*
 *  ======== AESCommonXXF3_init ========
 */
void AESCommonXXF3_init(void)
{
    CryptoResourceXXF3_constructRTOSObjects();

#ifndef TFM_BUILD
    UDMALPF3_init();
#endif

    AESCommon_isInitialized = true;
}

/*
 *  ======== AESCommonXXF3_construct ========
 */
int_fast16_t AESCommonXXF3_construct(AESCommonXXF3_Object *object, AES_ReturnBehavior returnBehavior, uint32_t timeout)
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

#ifndef TFM_BUILD
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
#endif

    object->cryptoResourceLocked = false;
    object->operationInProgress  = false;
    object->powerConstraintSet   = false;

#ifndef TFM_BUILD
    /* Set power dependency. Power up and enable clock for DMA peripheral */
    Power_setDependency(PowerLPF3_PERIPH_DMA);
#endif

    /* Set power dependency. Power up and enable clock for LAES peripheral */
    Power_setDependency(PowerLPF3_PERIPH_AES);

    return AES_STATUS_SUCCESS;
}

/*
 *  ======== AESCommonXXF3_close ========
 */
void AESCommonXXF3_close(AESCommonXXF3_Object *object)
{
    DebugP_assert(object);

    /* Mark the module as available */
    object->isOpen = false;

#ifndef TFM_BUILD
    /* Release power dependency on DMA module */
    Power_releaseDependency(PowerLPF3_PERIPH_DMA);
#endif

    /* Release power dependency on LAES module */
    Power_releaseDependency(PowerLPF3_PERIPH_AES);
}

/*
 *  ======== AESCommonXXF3_setOperationInProgress ========
 */
int_fast16_t AESCommonXXF3_setOperationInProgress(AESCommonXXF3_Object *object)
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
 *  ======== AESCommonXXF3_setupOperation ========
 */
void AESCommonXXF3_setupOperation(CryptoKey *key, uint32_t autoCfgVal)
{
    /* Load Key */
    AESCommonXXF3_loadKey(key);

    /* Set AUTOCFG */
    AESSetAUTOCFG(autoCfgVal);
}

/*
 *  ======== AESCommonXXF3_loadKey ========
 */
void AESCommonXXF3_loadKey(const CryptoKey *key)
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

#if (ENABLE_KEY_STORAGE == 1)

/*
 *  ======== AESCommonXXF3_isHsmKeyStateValid ========
 */
bool AESCommonXXF3_isHsmKeyStateValid(void)
{
    uint32_t mask = AES_STA_KEYINTID_M | AES_STA_KEYSTATE_M;

    /* Return true if key registers were properly written by HSM */
    return ((HWREG(AES_BASE + AES_O_STA) & mask) == (AES_STA_KEYINTID_HSM | AES_STA_KEYSTATE_VALID));
}

/*
 *  ======== AESCommonXXF3_loadKeyFromKeyStore ========
 */
int_fast16_t AESCommonXXF3_loadKeyFromKeyStore(const CryptoKey *key,
                                               uint32_t *keyAssetID,
                                               KeyStore_PSA_Algorithm targetAlg,
                                               KeyStore_PSA_KeyUsage targetUsage)
{
    int_fast16_t status = AES_STATUS_KEYSTORE_GENERIC_ERROR;
    int_fast16_t keyStoreStatus;
    int_fast16_t hsmStatus;
    uint8_t keyMaterial[AESCommonXXF3_256_KEY_LENGTH_BYTES];
    KeyStore_PSA_KeyAttributes attributes = KEYSTORE_PSA_KEY_ATTRIBUTES_INIT;
    KeyStore_PSA_KeyLifetime lifetime;
    KeyStore_PSA_KeyLocation location;
    KeyStore_PSA_KeyFileId keyID;

    *keyAssetID = PSA_ASSETID_INVALID;

    GET_KEY_ID(keyID, key->u.keyStore.keyID);

    keyStoreStatus = KeyStore_PSA_getKeyAttributes(keyID, &attributes);

    if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
    {
        lifetime = KeyStore_PSA_getKeyLifetime(&attributes);
        location = KEYSTORE_PSA_KEY_LIFETIME_GET_LOCATION(lifetime);

        if (location == KEYSTORE_PSA_KEY_LOCATION_HSM_ASSET_STORE)
        {
            /* HSM is needed to unwrap the key so try to obtain access to the HSM module */
            if (!HSMXXF3_acquireLock(SemaphoreP_NO_WAIT, (uintptr_t)0U))
            {
                /* Acquiring the lock failed so we return immediately */
                return AES_STATUS_RESOURCE_UNAVAILABLE;
            }
        }

        keyStoreStatus = KeyStore_PSA_retrieveFromKeyStore(key,
                                                           &keyMaterial[0],
                                                           sizeof(keyMaterial),
                                                           keyAssetID,
                                                           targetAlg,
                                                           targetUsage);

        /* KeyStore_PSA_retrieveFromKeyStore internally validates that the retrieved
         * key material has a length matching that of the CryptoKey.
         */
        if (keyStoreStatus == KEYSTORE_PSA_STATUS_SUCCESS)
        {
            if (PSA_ASSETID_INVALID == *keyAssetID)
            {
                AESWriteKEY(keyMaterial);
                status = AES_STATUS_SUCCESS;
            }
            else
            {
                /* Export the asset to LAES key registers via the coprocessor interface. The LAES
                 * coprocessor interface can only access the LAES key registers so the coprocessor
                 * offset is 0.
                 */
                hsmStatus = HSMXXF3_constructExportAssetCopToken(*keyAssetID, HSMXXF3_LAES_COPROCESSOR_ID, 0);

                if (hsmStatus == HSMXXF3_STATUS_SUCCESS)
                {
                    hsmStatus = HSMXXF3_submitToken(HSMXXF3_RETURN_BEHAVIOR_POLLING, NULL, (uintptr_t)0U);
                }

                if (hsmStatus == HSMXXF3_STATUS_SUCCESS)
                {
                    hsmStatus = HSMXXF3_waitForResult();
                }

                if (hsmStatus == HSMXXF3_STATUS_SUCCESS)
                {
                    /* Check the key registers were properly written */
                    if (AESCommonXXF3_isHsmKeyStateValid())
                    {
                        status = AES_STATUS_SUCCESS;
                    }
                }
            }
        }
        else if (keyStoreStatus == KEYSTORE_PSA_STATUS_INVALID_KEY_ID)
        {
            status = AES_STATUS_KEYSTORE_INVALID_ID;
        }
        else
        {
            status = AES_STATUS_KEYSTORE_GENERIC_ERROR;
        }

        if (location == KEYSTORE_PSA_KEY_LOCATION_HSM_ASSET_STORE)
        {
            HSMXXF3_releaseLock();
        }
    }

    return status;
}
#endif /* ENABLE_KEY_STORAGE */

/*
 *  ======== AESAESCommonXXF3_cleanup ========
 */
void AESCommonXXF3_cleanup(AESCommonXXF3_Object *object)
{
#ifndef TFM_BUILD
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
        UDMALPF3_channelDisable(AESCommonXXF3_dmaChannelMaskChA | AESCommonXXF3_dmaChannelMaskChB);
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
        CryptoResourceXXF3_releaseLock();
    }

    AESCommonXXF3_releasePowerConstraint(object);
#endif
}

/*
 *  ======== AESCommonXXF3_setupSegmentedOperation ========
 */
int_fast16_t AESCommonXXF3_setupSegmentedOperation(AESCommonXXF3_Object *object, const CryptoKey *key)
{
    int_fast16_t status;

    /* Check that there is no operation in progress for this driver instance */
    status = AESCommonXXF3_setOperationInProgress(object);

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
 *  ======== AESCommonXXF3_configInputDMA ========
 */
void AESCommonXXF3_configInputDMA(const void *input, size_t inputLength)
{
#ifndef TFM_BUILD
    uint32_t control;
    uint32_t numTransfers;

    /*
     * Set the source data width and address increment based upon the address
     * alignment. Arbitrate after 16-bytes (AES block size). No destination
     * address increment.
     */
    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 1)
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
    uDMASetChannelControl(AESCommonXXF3_dmaPriControlTableEntryChA, control);

    /*
     * Setup DMA channel A Primary Control Struct:
     *  - Mode = Basic
     *  - Input & Output end pointers
     *  - Set n-1, where n = number DMA transfers that the DMA cycle contains.
     */
    uDMASetChannelTransfer(AESCommonXXF3_dmaPriControlTableEntryChA,
                           UDMA_MODE_BASIC,
                           (void *)input,
                           (void *)(AES_BASE + AES_O_DMACHA),
                           numTransfers);

    /* Enable the channel for AES input */
    UDMALPF3_channelEnable(AESCommonXXF3_dmaChannelMaskChA);
#endif
}

/*
 *  ======== AESCommonXXF3_isDMALengthValid ========
 */
bool AESCommonXXF3_isDMALengthValid(const void *input, const void *output, size_t length)
{
    size_t maxLength = 4096;

#if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 1)
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
 *  ======== AESCommonXXF3_configOutputDMA ========
 */
void AESCommonXXF3_configOutputDMA(void *output, size_t outputLength)
{
#ifndef TFM_BUILD
    uint32_t control;
    uint32_t numTransfers;

    /*
     * Set the source data width and address increment based upon the address
     * alignment. Arbitrate after 16-bytes (AES block size). No source address
     * increment.
     */
    #if (AESCommonXXF3_UNALIGNED_IO_SUPPORT_ENABLE == 1)
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
    uDMASetChannelControl(AESCommonXXF3_dmaPriControlTableEntryChB, control);

    /*
     * Setup DMA channel B Primary Control struct transfer params:
     *  - Mode = Basic
     *  - Input & Output end pointers
     *  - Set n-1, where n = number DMA transfers that the DMA cycle contains.
     */
    uDMASetChannelTransfer(AESCommonXXF3_dmaPriControlTableEntryChB,
                           UDMA_MODE_BASIC,
                           (void *)(AES_BASE + AES_O_DMACHB),
                           output,
                           numTransfers);

    /* Enable the channel for AES input */
    UDMALPF3_channelEnable(AESCommonXXF3_dmaChannelMaskChB);
#endif
}

/*
 *  ======== AESCommonXXF3_cancelDMA ========
 */
void AESCommonXXF3_cancelDMA(bool cancelChannelB)
{
#ifndef TFM_BUILD
    IntDisable(INT_AES_COMB);
    AESSetIMASK((uint32_t)0U);
    AESDisableDMA();

    uint32_t channelBitMask = AESCommonXXF3_dmaChannelMaskChA;

    if (cancelChannelB)
    {
        channelBitMask |= AESCommonXXF3_dmaChannelMaskChB;
    }

    /* Disable DMA channel(s) */
    UDMALPF3_channelDisable(channelBitMask);

    /* Set DMA channels to STOP */
    uDMASetChannelTransfer(AESCommonXXF3_dmaPriControlTableEntryChA, UDMA_MODE_STOP, 0, 0, 0);

    if (cancelChannelB)
    {
        uDMASetChannelTransfer(AESCommonXXF3_dmaPriControlTableEntryChB, UDMA_MODE_STOP, 0, 0, 0);
    }

    /* Abort must be done after disabling DMA channels according to LAES spec */
    AESAbort();

    /* Clear all AES interrupts */
    AESClearInterrupt(AES_ICLR_ALL);
#endif
}

/*
 *  ======== AESCommonXXF3_cancelOperation ========
 */
void AESCommonXXF3_cancelOperation(AESCommonXXF3_Object *object, bool cancelDMAChannelB)
{
    if (object->returnBehavior != AES_RETURN_BEHAVIOR_POLLING)
    {
        AESCommonXXF3_cancelDMA(cancelDMAChannelB);
    }

    AESCommonXXF3_releasePowerConstraint(object);

    object->returnStatus = AES_STATUS_CANCELED;

    AESCommonXXF3_clearOperationInProgress(object);

    if (object->cryptoResourceLocked)
    {
        object->cryptoResourceLocked = false;
        /*
         * Grant access for other threads to use the crypto module.
         * The semaphore must be posted before the callbackFxn to allow
         * the chaining of operations.
         */
        CryptoResourceXXF3_releaseLock();
    }
}

/*
 *  ======== AESCommonXXF3_setupHwi ========
 */
void AESCommonXXF3_setupHwi(HwiP_Fxn hwiFxn, uintptr_t hwiFxnArg, uint8_t intPriority)
{
    HwiP_setFunc(&CryptoResourceXXF3_hwi, hwiFxn, hwiFxnArg);
    HwiP_setPriority(INT_AES_COMB, (uint32_t)intPriority);
    IntEnable((uint32_t)INT_AES_COMB);
}

/*
 *  ======== AESCommonXXF3_setPowerConstraint ========
 */
void AESCommonXXF3_setPowerConstraint(AESCommonXXF3_Object *object)
{
    /* Ignore return value since it always returns Power_SOK */
    (void)Power_setConstraint(PowerLPF3_DISALLOW_STANDBY);
    object->powerConstraintSet = true;
}

/*
 *  ======== AESCommonXXF3_releasePowerConstraint ========
 */
void AESCommonXXF3_releasePowerConstraint(AESCommonXXF3_Object *object)
{
    if (object->powerConstraintSet)
    {
        object->powerConstraintSet = false;
        /* Ignore return value since it always returns Power_SOK */
        (void)Power_releaseConstraint(PowerLPF3_DISALLOW_STANDBY);
    }
}

/*
 *  ======== AESCommonXXF3_setupDMA ========
 */
void AESCommonXXF3_setupDMA(AESCommonXXF3_Object *object, uint32_t dmaConfig)
{
    AESSetupDMA(dmaConfig);

    AESCommonXXF3_setPowerConstraint(object);
}

/*
 *  ======== AESCommonXXF3_cleanupHwi ========
 */
void AESCommonXXF3_cleanupHwi(AESCommonXXF3_Object *object)
{
    AESDisableDMA();
    AESSetIMASK((uint32_t)0U);
    /* Clear all AES interrupts */
    AESClearInterrupt(AES_ICLR_ALL);

    AESCommonXXF3_releasePowerConstraint(object);
}
