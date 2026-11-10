/* adapter_interrupts.c
 *
 * Freertos implementation EIP201 (AIC) functionality of the
 * Adapter_Interrupt API.  Spawns a thread using the UMDevXSProxy
 * interrupt reads, which call into the single interrupt handler
 * routine gl_InterruptHandler from within that thread.
 *
 * The interrupt handler thread can be slept ("disabled".)  All
 * communication happens through the flags member of
 * gl_InterruptContext.  It is only ever written by external thread:
 * there is no protection, and only read from the interrupt thread
 * (this works from a memory visibility point as
 * Adapter_Event_Signal() will take and release the mutex.
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

#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_interrupts.h>
#include <stdlib.h>
#include <string.h>
#include <third_party/hsmddk/include/Kit/EIP201/incl/eip201.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_mgmt.h>

#include <third_party/hsmddk/include/Kit/Log/incl/log.h>                        /* LOG_* */

static Device_Handle_t gl_Aic = NULL;

/* There is a problem with EIP201_SOURCE_ALL being set as -1, which
 * will cause assertion failures in the calls!
 */
#undef EIP201_SOURCE_ALL
#define EIP201_SOURCE_ALL 0xff

int32_t
Adapter_Interrupts_Init(const int32_t nIRQ)
{
    int32_t rval = -1;

    gl_Aic = Device_Find("EIP130_AIC");
    if (gl_Aic != NULL)
    {
        /* Configure them all for an edge detect.  We should probably
         * only have the interrupts we need.  We could also use
         * EIP201_Config_Change(), but there's no adapter function(!)
         */
        EIP201_SourceSettings_t settings = {
            .Source = EIP201_SOURCE_ALL,
            .Config = EIP201_CONFIG_RISING_EDGE,
            .fEnable = false /* enable source only when active */
        };
        if (EIP201_Initialize(gl_Aic, &settings, 1) == 0)
        {
            rval = 0;
        }
        else
        {
            rval = -3;
        }
    }

    LOG_WARN("%s(%d) [%p] = %d\n", __func__, nIRQ, gl_Aic, rval);

    return rval;
}


int32_t
Adapter_Interrupts_ReInit(void)
{
    int32_t rval = -1;

    /* Configure them all for an edge detect.  We should probably
     * only have the interrupts we need.  We could also use
     * EIP201_Config_Change(), but there's no adapter function(!)
     */
    EIP201_SourceSettings_t settings = {
        .Source = EIP201_SOURCE_ALL,
        .Config = EIP201_CONFIG_RISING_EDGE,
        .fEnable = false /* enable source only when active */
    };

    /* ReInitialize the interrupt registers */
    if (EIP201_Initialize(gl_Aic, &settings, 1) == 0)
    {
        rval = 0;
    }

    return rval;
}


int32_t
Adapter_Interrupts_UnInit(const int32_t nIRQ)
{

    if (gl_Aic != NULL)
    {
        (void)EIP201_SourceMask_DisableSource(gl_Aic, EIP201_SOURCE_ALL);
        gl_Aic = NULL;
    }

    return nIRQ;
}

int32_t
Adapter_Interrupt_Clear(const int32_t nIRQ,
                        const uint32_t Flags)
{
    int32_t funcres;
    (void)Flags;

    if (gl_Aic != NULL)
    {
        funcres = EIP201_Acknowledge(gl_Aic, 1u << nIRQ);
    }
    else
    {
        funcres = -1;
    }

    return funcres;
}


int32_t
Adapter_Interrupt_ClearAndEnable(const int32_t nIRQ,
                                 const uint32_t Flags)
{
    EIP201_SourceBitmap_t mask = (1U << nIRQ);
    int32_t rc;

    (void)EIP201_Acknowledge(gl_Aic, mask);
    rc = EIP201_SourceMask_EnableSource(gl_Aic, mask);
    return rc;
}

int32_t
Adapter_Interrupt_Disable(const int32_t nIRQ,
                          const uint32_t Flags)
{
    EIP201_SourceBitmap_t mask = (1U << nIRQ);
    int32_t rc;

    rc = EIP201_SourceMask_DisableSource(gl_Aic, mask);
    return rc;
}

int32_t
Adapter_Interrupt_Ext_RawStatus(void)
{
    int32_t funcres;
    EIP201_SourceBitmap_t sources = 0;
    EIP201_Status_t status = EIP201_SourceStatus_ReadAllRawCheck(gl_Aic, &sources);
    if (status > 0)
    {
        funcres = -(abs(status));
    }
    else
    {
        funcres = (int32_t)sources;
    }

    return funcres;
}


int32_t
Adapter_Interrupt_Ext_Status(void)
{
    int32_t funcres;
    EIP201_SourceBitmap_t sources = 0;
    EIP201_Status_t status = EIP201_SourceStatus_ReadAllEnabledCheck(gl_Aic, &sources);
    if (status > 0)
    {
        funcres = -(abs(status));
    }
    else
    {
        funcres = (int32_t)sources;
    }

    return funcres;
}


/* end of file adapter_interrupts.c */
