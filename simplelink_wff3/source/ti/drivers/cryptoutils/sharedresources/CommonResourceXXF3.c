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

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/cryptoutils/sharedresources/CommonResourceXXF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_ints.h)

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
    /* HSM Register names for CC35XX are different compared to CC27XX
     * Below mapping helps to keep the source code same between
     * both devices.
     */
    #define INT_HSM_SEC_IRQ INT_OSPR_HSM_HOST_0_SEC_IRQ
#endif /* (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX) */

/* The CommonResource access semaphore is tasked with regulating access to the DMA bus. The main modules leveraging this
 * semaphore are:
 * - CAN
 * - APU
 * - HSM crypto drivers (ECDH, ECDSA, AES-CCM, RNG, etc...)
 */
static SemaphoreP_Struct CommonResourceXXF3_accessSemaphore;

/* Module metadata to ensure this CommonResourceXXF3_constructRTOSObjects was called before any _acquireLock API. */
static bool CommonResourceXXF3_isInitialized         = false;
static volatile bool CommonResourceXXF3_HSMIRQNeeded = false;

/*
 *  ======== CommonResourceXXF3_constructRTOSObjects ========
 */
void CommonResourceXXF3_constructRTOSObjects(void)
{
    uintptr_t key;

    key = HwiP_disable();

    if (!CommonResourceXXF3_isInitialized)
    {
        (void)SemaphoreP_constructBinary(&CommonResourceXXF3_accessSemaphore, 1U);

        /* Update global variable. */
        CommonResourceXXF3_isInitialized = true;
        CommonResourceXXF3_HSMIRQNeeded  = false;
    }

    HwiP_restore(key);
}

/*
 *  ======== CommonResourceXXF3_acquireLock ========
 */
bool CommonResourceXXF3_acquireLock(uint32_t timeout)
{
    SemaphoreP_Status resourceAcquired;

    /* Try and obtain the CommonResource access semaphore */
    resourceAcquired = SemaphoreP_pend(&CommonResourceXXF3_accessSemaphore, timeout);

    return (resourceAcquired == SemaphoreP_OK);
}

/*
 *  ======== CommonResourceXXF3_releaseLock ========
 */
void CommonResourceXXF3_releaseLock(void)
{
    uintptr_t key;

    SemaphoreP_post(&CommonResourceXXF3_accessSemaphore);

    key = HwiP_disable();

    if (CommonResourceXXF3_HSMIRQNeeded)
    {
        /* In the case where HSM drivers (mainly ECDH and ECDSA) attempt to acquire a semaphore in a non-blocking
         * fashion from an ISR and fail, _acquireLockWithDelay registers this statically and fires up the IRQ as the
         * last entity to hold the semaphore releases it.
         */
        HwiP_post(INT_HSM_SEC_IRQ);

        CommonResourceXXF3_HSMIRQNeeded = false;
    }

    HwiP_restore(key);
}

/*
 *  ======== CommonResourceXXF3_acquireLockWithDelay ========
 */
bool CommonResourceXXF3_acquireLockWithDelay(void)
{
    SemaphoreP_Status resourceAcquired;

    /* Try and obtain the CommonResource access semaphore */
    resourceAcquired = SemaphoreP_pend(&CommonResourceXXF3_accessSemaphore, SemaphoreP_NO_WAIT);

    if (resourceAcquired != SemaphoreP_OK)
    {
        CommonResourceXXF3_HSMIRQNeeded = true;
    }

    return (resourceAcquired == SemaphoreP_OK);
}
