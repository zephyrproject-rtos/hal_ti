/* adapter_global_control_init.c
 *
 * Adapter module responsible for adapter global control initialization tasks.
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

#include <third_party/hsmddk/include/Integration/Adapter_DriverInit/src/adapter_global_control_init.h>


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Top-level Adapter configuration
#include <third_party/hsmddk/include/Integration/Adapter_GlobalControl/src/c_adapter_global.h>

// Driver Framework Basic Definitions API
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>         // bool, true, false

#ifdef ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE
#include "adapter_pciconfig.h"  // PCICONFIG_*
#endif

// Logging API
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>                // LOG_*

// Driver Framework Device API
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_mgmt.h>        // Device_Initialize, Device_UnInitialize
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_rw.h>          // Device_Read32, Device_Write32


/*----------------------------------------------------------------------------
 * Local variables
 */

static bool gl_Adapter_IsInitialized = false;

#ifdef ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
static Device_Handle_t Adapter_Device_BOARDCTRL;
#endif

#ifdef ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE
static Device_Handle_t Adapter_Device_PCIConfigSpace;
#endif


/*----------------------------------------------------------------------------
 * Adapter_Global_Control_Init
 *
 * Return Value
 *     true   Success
 *     false  Failure (fatal!)
 */
bool
Adapter_Global_Control_Init(void)
{
    if (gl_Adapter_IsInitialized != false)
    {
        LOG_WARN("%s: Already initialized\n", __func__);
    }
    else
    {
        int nIRQ = -1;

        // trigger first-time initialization of the adapter
        if (Device_Initialize(&nIRQ) >= 0)
        {
            gl_Adapter_IsInitialized = true;
        }

#ifdef ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE
        if (gl_Adapter_IsInitialized)
        {
            Adapter_Device_PCIConfigSpace = Device_Find("PCI_CONFIG_SPACE");
            if (Adapter_Device_PCIConfigSpace == NULL)
            {
                LOG_CRIT("%s: Failed to locate PCI_CONFIG_SPACE\n", __func__);
                gl_Adapter_IsInitialized = false;
            }
        }
#endif // ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE

#ifdef ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
        if (gl_Adapter_IsInitialized)
        {
            Adapter_Device_BOARDCTRL = Device_Find("BOARD_CTRL");
            if (Adapter_Device_BOARDCTRL == NULL)
            {
                LOG_CRIT("%s: Failed to locate BOARD_CTRL\n", __func__);
                gl_Adapter_IsInitialized = false;
            }
        }
#endif // ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE

#ifdef ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE
#ifdef LOG_INFO_ENABLED
        if (gl_Adapter_IsInitialized)
        {
            uint32_t Value;
            int VendorID, DeviceID;

            Value = Device_Read32(Adapter_Device_PCIConfigSpace,
                                  PCICONFIG_REG_ID);

            VendorID = PCICONFIG_ID_EXTRACT_VENDOR(Value);
            DeviceID = PCICONFIG_ID_EXTRACT_DEVICE(Value);

            (void)(VendorID);
            (void)(DeviceID);

            LOG_INFO("%s: PCI device: Vendor=0x%X, Device=0x%X\n",
                     __func__, VendorID, DeviceID);
        }
#endif // LOG_INFO_ENABLED

        if (gl_Adapter_IsInitialized)
        {
            uint32_t Value;

            // initialize the PCI device
            // command and status register - Writing value 0x146 to this register
            // is recommended before accessing the FPGA

            Value = PCICONFIG_STATCMD_MEMORYACCESS_ENABLE +
                    PCICONFIG_STATCMD_BUSMASTER_ENABLE +
                    PCICONFIG_STATCMD_PARITYERR_ENABLE +
                    PCICONFIG_STATCMD_SYSTEMERR_ENABLE;

            Device_Write32(Adapter_Device_PCIConfigSpace,
                           PCICONFIG_REG_STATCMD,
                           Value);
        }

        if (gl_Adapter_IsInitialized)
        {
            uint32_t Value;
#ifdef LOG_INFO_ENABLED
            uint32_t OldValue;
#endif

            // Setting cache line size
            // maintain all other bits (set by BIOS or OS)
            Value = Device_Read32(Adapter_Device_PCIConfigSpace,
                                  PCICONFIG_REG_CONFIG);
#ifdef LOG_INFO_ENABLED
            OldValue = Value;
#endif

            Value = PCICONFIG_CONFIG_UPDATE_CACHELINESIZE(
                        Value,
                        ADAPTER_PCICONFIG_CACHELINESIZE);

#ifdef ADAPTER_PCICONFIG_MASTERLATENCYTIMER
            Value = PCICONFIG_CONFIG_UPDATE_MASTERLATENCYTIMER(
                        Value,
                        ADAPTER_PCICONFIG_MASTERLATENCYTIMER);
#endif

            Device_Write32(Adapter_Device_PCIConfigSpace,
                           PCICONFIG_REG_CONFIG,
                           Value);

#ifdef LOG_INFO_ENABLED
            LOG_INFO("%s: Changed PCI_Config[0x0c] from 0x%08x to 0x%08x\n",
                     __func__, OldValue, Value);
#endif
        }
#endif // ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE

        // FPGA board specific functionality
#ifdef ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
        if (gl_Adapter_IsInitialized)
        {
            // Enable PLB access on the board
            Device_Write32(Adapter_Device_BOARDCTRL, 0x8, 0x00400000);

#ifdef ADAPTER_GLOBAL_FPGA_HW_RESET_ENABLE
            // Perform HW Reset for the FPGA board
            Device_Write32(Adapter_Device_BOARDCTRL, 0x2000, 0);
            Device_Write32(Adapter_Device_BOARDCTRL, 0x2000, 0xFFFFFFFF);
            Device_Write32(Adapter_Device_BOARDCTRL, 0x2000, 0);
#endif // ADAPTER_GLOBAL_FPGA_HW_RESET_ENABLE
        }
#endif // ADAPTER_GLOBAL_BOARDCTRL_SUPPORT_ENABLE
    }

    return gl_Adapter_IsInitialized;
}


/*----------------------------------------------------------------------------
 * Adapter_Global_Control_UnInit
 */
void
Adapter_Global_Control_UnInit(void)
{
    if (gl_Adapter_IsInitialized)
    {
        gl_Adapter_IsInitialized = false;

        Device_UnInitialize();
    }
    else
    {
        LOG_WARN("%s: Adapter is uninitialized\n", __func__);
    }
}


/*----------------------------------------------------------------------------
 * Adapter_Global_Control_Report_Build_Params
 */
void
Adapter_Global_Control_Report_Build_Params(void)
{
#ifdef LOG_INFO_ENABLED
    int dummy;

    // This function is dependent on config file cs_adapter.h.
    // Please update this when Config file for Adapter is changed.
    Log_FormattedMessage("Adapter Global Control build configuration:\n");

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

#ifdef ADAPTER_64BIT_HOST
    REPORT_EXPL(ADAPTER_64BIT_HOST,
                " is SET => addresses are 64-bit");
#else
    REPORT_EXPL(ADAPTER_64BIT_HOST,
                " is NOT set => addresses are 32-bit");
#endif

    // PCI configuration
#ifdef ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE
#ifdef ADAPTER_PCICONFIG_CACHELINESIZE
    REPORT_INT(ADAPTER_PCICONFIG_CACHELINESIZE);
#endif

#ifdef ADAPTER_PCICONFIG_MASTERLATENCYTIMER
    REPORT_INT(ADAPTER_PCICONFIG_MASTERLATENCYTIMER);
#endif
#endif // ADAPTER_GLOBAL_PCI_SUPPORT_ENABLE

    // Global interrupts
#ifdef ADAPTER_GLOBAL_INTERRUPTS_TRACEFILTER
    REPORT_INT(ADAPTER_GLOBAL_INTERRUPTS_TRACEFILTER);
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

    IDENTIFIER_NOT_USED(dummy);

    // Adapter other
    Log_FormattedMessage("Other:\n");
    REPORT_STR(ADAPTER_GLOBAL_DRIVER_NAME);
    REPORT_STR("Dual BSD/GPL");

#endif //LOG_INFO_ENABLED
}


/* end of file adapter_global_control_init.c */
