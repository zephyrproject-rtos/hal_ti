/* adapter_init_psa.c
 *
 * Adapter module responsible for Adapter PSA initialization tasks.
 *
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include <third_party/hsmddk/include/Integration/Adapter_DriverInit/src/adapter_init.h>


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Top-level Adapter configuration
#include <third_party/hsmddk/include/Config/cs_adapter.h>

// Driver Framework Basic Definitions API
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>                 // bool, true, false

#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_interrupts.h>         // Adapter_Interrupts_Init/UnInit

// Logging API
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>                        // LOG_*

// Driver Framework Device API
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_mgmt.h>                // Device_Initialize/UnInitialize
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_rw.h>                  // Device_Read32, Device_Write32

// Driver Framework DMAResource API
#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_mgmt.h>                // DMAResource_Init/UnInit


/*----------------------------------------------------------------------------
 * Local variables
 */

static bool AIV_Adapter_IsInitialized = false;
static int32_t AIV_Device_IRQ;

/*----------------------------------------------------------------------------
 * Adapter_Init
 *
 * Return Value
 *     true   Success
 *     false  Failure (fatal!)
 */
bool
Adapter_Init(void)
{
    bool funcres = true;
    AIV_Device_IRQ = -1;

    if (AIV_Adapter_IsInitialized != false)
    {
        LOG_WARN("%s: Already initialized\n", __func__);
        funcres = true;
    }
    else
    {
        // trigger first-time initialization of the adapter
        if (Device_Initialize(&AIV_Device_IRQ) < 0)
        {
            funcres = false;
        }
        else
        {
            if (!DMAResource_Init())
            {
                Device_UnInitialize();
                funcres = false;
            }
            else
            {
                LOG_WARN("%s: Adapter_Interrupts enabled\n", __func__);
                if (Adapter_Interrupts_Init(AIV_Device_IRQ) < 0)
                {
                    LOG_CRIT("%s: Adapter_Interrupts_Init failed\n", __func__);

                    DMAResource_UnInit();

                    Device_UnInitialize();

                    funcres = false;
                }
                else
                {
                    AIV_Adapter_IsInitialized = true;
                }
            }
        }
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * Adapter_UnInit
 */
void
Adapter_UnInit(void)
{
    if (!AIV_Adapter_IsInitialized)
    {
        LOG_WARN("%s: Adapter is not initialized\n", __func__);
    }
    else
    {
        AIV_Adapter_IsInitialized = false;

        DMAResource_UnInit();

        (void)Adapter_Interrupts_UnInit(AIV_Device_IRQ);

        Device_UnInitialize();
    }
    return;
}


/*----------------------------------------------------------------------------
 * Adapter_Report_Build_Params
 */
void
Adapter_Report_Build_Params(void)
{
#ifdef LOG_INFO_ENABLED
    int dummy;

    // This function is dependent on config file cs_adapter.h.
    // Please update this when Config file for Adapter is changed.
    Log_FormattedMessage("Adapter build configuration:\n");

#define REPORT_SET(_X) \
    Log_FormattedMessage("\t" #_X "\n")

#define REPORT_STR(_X) \
    Log_FormattedMessage("\t" #_X ": %s\n", _X)

#define REPORT_INT(_X) \
    dummy = _X; Log_FormattedMessage("\t" #_X ": %d\n", _X)

#define REPORT_HEX32(_X) \
    dummy = _X; Log_FormattedMessage("\t" #_X ": 0x%08X\n", _X)

#define REPORT_EQ(_X, _Y) \
    dummy = (_X + _Y); Log_FormattedMessage("\t" #_X " == " #_Y "\n")

#define REPORT_EXPL(_X, _Y) \
    Log_FormattedMessage("\t" #_X _Y "\n")

    // Adapter PSA
#ifdef ADAPTER_STRICT_ARGS
    REPORT_SET(ADAPTER_STRICT_ARGS);
#endif

#ifdef ADAPTER_REMOVE_BOUNCEBUFFERS
    REPORT_EXPL(ADAPTER_REMOVE_BOUNCEBUFFERS, " is SET => Bounce DISABLED");
#else
    REPORT_EXPL(ADAPTER_REMOVE_BOUNCEBUFFERS, " is NOT set => Bounce ENABLED");
#endif

#ifdef ADAPTER_ENABLE_SWAP
    REPORT_EXPL(ADAPTER_ENABLE_SWAP, " is SET => Byte swap in words ENABLED");
#else
    REPORT_EXPL(ADAPTER_ENABLE_SWAP, " is NOT set => Byte swap in words DISABLED");
#endif

#ifdef ADAPTER_64BIT_HOST
    REPORT_EXPL(ADAPTER_64BIT_HOST,
                " is SET => addresses are 64-bit");
#else
    REPORT_EXPL(ADAPTER_64BIT_HOST,
                " is NOT set => addresses are 32-bit");
#endif

#ifdef ADAPTER_64BIT_DEVICE
    REPORT_EXPL(ADAPTER_64BIT_DEVICE,
                " is SET => full 64-bit DMA addresses usable");
#else
    REPORT_EXPL(ADAPTER_64BIT_DEVICE,
                " is NOT set => DMA addresses must be below 4GB");
#endif

    // Log
    Log_FormattedMessage("Logging:\n");

#if (LOG_SEVERITY_MAX == LOG_SEVERITY_INFO)
    REPORT_EQ(LOG_SEVERITY_MAX, LOG_SEVERITY_INFO);
#elif (LOG_SEVERITY_MAX == LOG_SEVERITY_WARNING)
    REPORT_EQ(LOG_SEVERITY_MAX, LOG_SEVERITY_WARNING);
#elif (LOG_SEVERITY_MAX == LOG_SEVERITY_CRITICAL)
    REPORT_EQ(LOG_SEVERITY_MAX, LOG_SEVERITY_CRITICAL);
#else
    REPORT_EXPL(LOG_SEVERITY_MAX, " - Unknown (not info/warn/crit)");
#endif

    // Adapter other
    Log_FormattedMessage("Other:\n");
    REPORT_STR(ADAPTER_DRIVER_NAME);

    IDENTIFIER_NOT_USED(dummy);

#endif //LOG_INFO_ENABLED
}


/* end of file adapter_init_psa.c */
