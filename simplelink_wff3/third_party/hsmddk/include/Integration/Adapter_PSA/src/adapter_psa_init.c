/* adapter_psa_init.c
 *
 * Implementation of the PSA API.
 *
 * This file implements the initializaton function.
 */

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Module        : DDK-130_bsd                                              */
/*   Version       : 4.1.1                                                    */
/*   Configuration : DDK_EIP130_BSD                                           */
/*                                                                            */
/*   Date          : 2023-Mar-10                                              */
/*                                                                            */
/* Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.           */
/*                                                                            */
/* Redistribution and use in source and binary forms, with or without         */
/* modification, are permitted provided that the following conditions are     */
/* met:                                                                       */
/*                                                                            */
/* 1. Redistributions of source code must retain the above copyright          */
/* notice, this list of conditions and the following disclaimer.              */
/*                                                                            */
/* 2. Redistributions in binary form must reproduce the above copyright       */
/* notice, this list of conditions and the following disclaimer in the        */
/* documentation and/or other materials provided with the distribution.       */
/*                                                                            */
/* 3. Neither the name of the copyright holder nor the names of its           */
/* contributors may be used to endorse or promote products derived from       */
/* this software without specific prior written permission.                   */
/*                                                                            */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        */
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          */
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR      */
/* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT       */
/* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT           */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,      */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY      */
/* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT        */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE      */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.       */
/* -------------------------------------------------------------------------- */

#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/c_adapter_psa.h>              // configuration
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/incl/platform.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_system.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_preprovisioned_keys.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>
#include <third_party/hsmddk/include/Config/cs_mbedtls.h>

#include <DeviceFamily.h>

static bool KeyMgmt_isInitialized = false;

extern uint8_t volatileAllocBuffer[];
extern size_t volatileAllocBufferSizeBytes;
/*----------------------------------------------------------------------------
 * psa_crypto_init
 */
psa_status_t
psa_crypto_init(void)
{
    /* Subsequent calls to this API are guaranteed to succeed - thus the default condition of success */
    psa_status_t funcres = PSA_SUCCESS;
    uint32_t Identity = 0U;
    uint16_t OtpErrorLocation = 0U;
    uint8_t OtpErrorCode = 0U;
    uint8_t Mode = 0xFFU;
    uint8_t SelfTestError = 0U;
    uint8_t CryptoOfficer = 0U;
    uint8_t HostID = 0U;
    uint8_t NonSecure = 0U;

    if (!KeyMgmt_isInitialized)
    {
        /* Check if HW is available and accessable */
        funcres = psaInt_SystemGetState(&OtpErrorCode, &OtpErrorLocation,
                                        &Mode, &SelfTestError, &CryptoOfficer,
                                        &HostID, &NonSecure, &Identity);
        if (PSA_SUCCESS == funcres)
        {
            switch (Mode)
            {
            case 0:                         /* Active Mode */
            case 15:                        /* Active Mode - Login successful */
                break;
            case 3:                         /* Fatal Error - Login Failed */
            case 4:                         /* Fatal Error - Self-test */
            case 5:                         /* Fatal Error - DMA */
            case 6:                         /* Fatal Error - NRBG or DRBG */
            case 7:                         /* Fatal Error - Key generation */
            default:                        /* Unexpected value */
    #ifdef PSA_LOG_LOWLEVEL_ERROR
                LOG_WARN("Abort - %s()=%d\n", __func__, funcres);
    #endif
                funcres = PSA_ERROR_CORRUPTION_DETECTED;
                break;
            }
        }
        else
        {
            /* MISRA - Intentially empty */
        }

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC35XX)
        if (PSA_SUCCESS == funcres)
        {
            funcres = KeyMgmt_initPreProvisionedKeys();
        }
#endif

        if (PSA_SUCCESS == funcres)
        {
            psaInt_mbedtls_memory_buffer_alloc_init(volatileAllocBuffer, volatileAllocBufferSizeBytes);

            KeyMgmt_isInitialized = true;
        }
    }

    return funcres;
}


/* end of file adapter_psa_init.c */