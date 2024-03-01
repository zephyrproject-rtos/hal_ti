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

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/cryptoutils/sharedresources/CryptoResourceLPF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_ints.h)

/* Crypto driver semaphore used to control access to the AES engine */
SemaphoreP_Struct CryptoResourceLPF3_accessSemaphore;
SemaphoreP_Struct CryptoResourceLPF3_operationSemaphore;

HwiP_Struct CryptoResourceLPF3_hwi;

static bool CryptoResourceLPF3_isInitialized = false;

static void errorSpin(uintptr_t arg)
{
    while (1) {}
}

void CryptoResourceLPF3_constructRTOSObjects(void)
{
    HwiP_Params hwiParams;
    uintptr_t key;

    key = HwiP_disable();

    if (!CryptoResourceLPF3_isInitialized)
    {
        /*
         * Construct the common Hwi with a dummy ISR function. This should not
         * matter as the function is set whenever we start an operation after
         * pending on CryptoResourceLPF3_accessSemaphore.
         */
        HwiP_Params_init(&hwiParams);
        hwiParams.priority  = (uint32_t)~0U;
        hwiParams.enableInt = false;
        (void)HwiP_construct(&CryptoResourceLPF3_hwi, INT_AES_COMB, errorSpin, &hwiParams);

        (void)SemaphoreP_constructBinary(&CryptoResourceLPF3_accessSemaphore, 1U);
        (void)SemaphoreP_constructBinary(&CryptoResourceLPF3_operationSemaphore, 0U);

        CryptoResourceLPF3_isInitialized = true;
    }

    HwiP_restore(key);
}

bool CryptoResourceLPF3_acquireLock(uint32_t timeout)
{
    SemaphoreP_Status resourceAcquired;

    /* Try and obtain access to the crypto module */
    resourceAcquired = SemaphoreP_pend(&CryptoResourceLPF3_accessSemaphore, timeout);

    return (resourceAcquired == SemaphoreP_OK);
}

void CryptoResourceLPF3_releaseLock(void)
{
    SemaphoreP_post(&CryptoResourceLPF3_accessSemaphore);
}
