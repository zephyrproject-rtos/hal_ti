/* adapter_init.c
 *
 * Adapter module responsible for adapter initialization tasks.
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

#include <third_party/hsmddk/include/Integration/Adapter_DriverInit/incl/adapter_init.h>


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

/*----------------------------------------------------------------------------
 * Local variables
 */

static bool gl_Adapter_IsInitialized = false;

#ifdef ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
static Device_Handle_t gl_Adapter_Device_BOARDCTRL;
#endif

static int32_t gl_Device_IRQ = -1;

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
    if (gl_Adapter_IsInitialized)
    {
        LOG_WARN("%s: Already initialized\n", __func__);
    }
    else
    {
        // trigger first-time initialization of the adapter
        if (Device_Initialize(&gl_Device_IRQ) >= 0)
        {
            gl_Adapter_IsInitialized = true;

#ifdef ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
            gl_Adapter_Device_BOARDCTRL = Device_Find("BOARD_CTRL");
            if (gl_Adapter_Device_BOARDCTRL == NULL)
            {
                LOG_CRIT("%s: Failed to locate BOARD_CTRL\n", __func__);
                gl_Adapter_IsInitialized = false;
            }
            else
            {
                // FPGA board specific functionality
                // Enable PLB access on the board
                Device_Write32(gl_Adapter_Device_BOARDCTRL, 0x8, 0x00400000);

#ifdef ADAPTER_GLOBAL_FPGA_HW_RESET_ENABLE
                // Perform HW Reset for the EIP-130 FPGA board
                Device_Write32(gl_Adapter_Device_BOARDCTRL, 0x2000, 0);
                Device_Write32(gl_Adapter_Device_BOARDCTRL, 0x2000, 0xFFFFFFFF);
                Device_Write32(gl_Adapter_Device_BOARDCTRL, 0x2000, 0);
#endif // ADAPTER_GLOBAL_FPGA_HW_RESET_ENABLE
                }
#endif // ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE

            if (gl_Adapter_IsInitialized)
            {
                if (Adapter_Interrupts_Init(gl_Device_IRQ) < 0)
                {
                    LOG_CRIT("%s: Adapter_Interrupts_Init failed\n", __func__);

                    Device_UnInitialize();

                    gl_Adapter_IsInitialized = false;
                }
                else
                {
                    LOG_WARN("Adapter_Init: Adapter_Interrupts enabled\n");
                }
            }
        }

        if (!gl_Adapter_IsInitialized)
        {
            gl_Device_IRQ = -1;
        }
    }

    return gl_Adapter_IsInitialized;
}


/*----------------------------------------------------------------------------
 * Adapter_UnInit
 */
void
Adapter_UnInit(void)
{
    if (gl_Adapter_IsInitialized)
    {
        (void)Adapter_Interrupts_UnInit(gl_Device_IRQ);

        Device_UnInitialize();

        gl_Adapter_IsInitialized = false;
        gl_Device_IRQ = -1;
    }
    else
    {
        LOG_WARN("%s: Adapter is not initialized\n", __func__);
    }
}


/*----------------------------------------------------------------------------
 * Adapter_Report_Build_Params
 */
void
Adapter_Report_Build_Params(void)
{
#ifdef LOG_INFO_ENABLED
    int32_t dummy;

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

    // Adapter VAL
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

#ifdef ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE
    REPORT_SET(ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE);
#endif

#ifdef ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
    REPORT_SET(ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE);
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


/* end of file adapter_init.c */
