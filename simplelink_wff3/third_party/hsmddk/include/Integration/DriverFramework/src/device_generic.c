/* device_generic.c
 *
 * This is the generic Driver Framework v4 Device API implementation.
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

// Driver Framework Device API
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_mgmt.h>            // API to implement


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Defs API
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             // IDENTIFIER_NOT_USED, NULL

// Driver Framework C Run-time Library API
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>                   // strlen, strcpy

// Driver Framework Device Internal interface
#include <third_party/hsmddk/include/Integration/DriverFramework/incl/device_internal.h>        // Device_Internal_*


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Default configuration
#include <third_party/hsmddk/include/Integration/DriverFramework/incl/c_device_generic.h>

// Logging API
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>


/*----------------------------------------------------------------------------
 * Local variables
 */
static Device_Admin_t HWPALLib_Devices[HWPAL_DEVICE_COUNT];

/*-----------------------------------------------------------------------------
 * DeviceLib_Device_Exists
 *
 * Checks if a device with DeviceName_p is already present in the device list
 *
 */
static bool
DeviceLib_Device_Exists(
        const char * DeviceName_p)
{
    bool funcres = false;
    if (DeviceName_p != NULL)
    {
        uint32_t i = 0;
        Device_Admin_t ** DevAdmin_pp = Device_Internal_Admin_Get();

        while (DevAdmin_pp[i] != NULL)
        {
            if (strcmp(DevAdmin_pp[i]->DevName, DeviceName_p) == 0)
            {
                funcres = true;
                break;
            }
            i++;
        }
    }

    return funcres;
}


/*-----------------------------------------------------------------------------
 * device_mgmt API
 *
 * These functions support finding a device given its name.
 * A handle is returned that is needed in the device_rw API
 * to read or write the device
 */

/*-----------------------------------------------------------------------------
 * Device_Initialize
 */
int32_t
Device_Initialize(
        void * CustomInitData_p)
{
    int32_t funcres = 0;
    uint32_t res;
    uint32_t DevStatCount = Device_Internal_Static_Count_Get();
    uint32_t DevCount = Device_Internal_Count_Get();
    const Device_Admin_Static_t * DevStatAdmin_p =
                            Device_Internal_Admin_Static_Get();
    Device_Admin_t ** DevAdmin_pp = Device_Internal_Admin_Get();
    Device_Global_Admin_t * DevGlobalAdmin_p =
                            Device_Internal_Admin_Global_Get();

    if (DevGlobalAdmin_p->fInitialized)
    {
        funcres = 0; // already initialized, success
    }
    else
    {
        if (DevStatCount > DevCount)
        {
            LOG_CRIT("%s: Invalid number of static devices (%d), max %d\n",
                     __func__, (int32_t)DevStatCount, DevCount);
            funcres = -1; // failed
        }
        else
        {
            // Copy static devices
            for (res = 0; res < DevStatCount; res++)
            {
                if (DeviceLib_Device_Exists(DevStatAdmin_p[res].DevName))
                {
                    LOG_CRIT("%s: failed, device (index %d) with name %s exists\n",
                             __func__, res, DevStatAdmin_p[res].DevName);
                    funcres = -1;
                    break;
                }
                else
                {
                    // Allocate memory for device administration data
                    DevAdmin_pp[res] = &HWPALLib_Devices[res];
                    if (DevAdmin_pp[res] == NULL)
                    {
                        LOG_CRIT("%s: failed to allocate device (index %d, name %s)\n",
                                 __func__, res, DevStatAdmin_p[res].DevName);
                        funcres = -1;
                        break;
                    }
                    else
                    {
                        (void)strcpy(DevAdmin_pp[res]->DevName, DevStatAdmin_p[res].DevName);

                        // Copy the rest of device data
                        DevAdmin_pp[res]->DeviceNr = DevStatAdmin_p[res].DeviceNr;
                        DevAdmin_pp[res]->FirstOfs = DevStatAdmin_p[res].FirstOfs;
                        DevAdmin_pp[res]->LastOfs  = DevStatAdmin_p[res].LastOfs;
                        DevAdmin_pp[res]->Flags    = DevStatAdmin_p[res].Flags;

#ifdef HWPAL_DEVICE_MAGIC
                        DevAdmin_pp[res]->Magic    = HWPAL_DEVICE_MAGIC;
#endif
                        DevAdmin_pp[res]->DeviceId = res;
                    }
                }
            }

            if (funcres == 0)
            {
                funcres = Device_Internal_Initialize(CustomInitData_p);
                if (funcres != 0)
                {
                    LOG_CRIT("%s: failed, error %d\n", __func__, funcres);
                    funcres = -1;
                }
                else
                {
                    DevGlobalAdmin_p->fInitialized = true;
                }
            }

            if (funcres != 0)
            {
                for (res = 0; res < DevStatCount; res++)
                {
                    if (DevAdmin_pp[res] != NULL)
                    {
                        DevAdmin_pp[res] = NULL;
                    }
                }
            }
        }
    }

    return funcres;
}


/*-----------------------------------------------------------------------------
 * Device_UnInitialize
 */
void
Device_UnInitialize(void)
{
    uint32_t DevCount = Device_Internal_Count_Get();
    Device_Admin_t ** DevAdmin_pp = Device_Internal_Admin_Get();
    Device_Global_Admin_t * DevGlobalAdmin_p =
                        Device_Internal_Admin_Global_Get();

    LOG_INFO("%s: unregister driver\n", __func__);

    if (DevGlobalAdmin_p->fInitialized)
    {
        Device_Internal_UnInitialize();

        DevGlobalAdmin_p->fInitialized = false;
    }
}


/*-----------------------------------------------------------------------------
 * Device_Find
 */
Device_Handle_t
Device_Find(
        const char * DeviceName_p)
{
    uint32_t i;
    Device_Handle_t funcres = NULL;
    uint32_t DevCount = Device_Internal_Count_Get();
    Device_Admin_t ** DevAdmin_pp = Device_Internal_Admin_Get();
    const Device_Global_Admin_t * const DevGlobalAdmin_p =
                        Device_Internal_Admin_Global_Get();

    if (!DevGlobalAdmin_p->fInitialized)
    {
        LOG_CRIT("%s: failed, not initialized\n", __func__);
        funcres = NULL;
    }
    else
    {
#ifdef HWPAL_STRICT_ARGS_CHECK
        if (DeviceName_p == NULL)
        {
            LOG_CRIT("%s: failed, invalid name\n", __func__);
            funcres = NULL; // not supported, thus not found
        }
        else
        {
#endif
            // walk through the device list and compare the device name
            for (i = 0; i < DevCount; i++)
            {
                if ((DevAdmin_pp[i] != NULL) &&
                    (strcmp(DeviceName_p, DevAdmin_pp[i]->DevName) == 0))
                {
                    funcres = Device_Internal_Find(DeviceName_p, i);
                    break;
                }
            }

            if (funcres == NULL)
            {
                LOG_CRIT("%s: failed to find device '%s'\n", __func__, DeviceName_p);
            }
#ifdef HWPAL_STRICT_ARGS_CHECK
        }
#endif
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * Device_GetProperties
 */
int32_t
Device_GetProperties(
        const uint32_t Index,
        Device_Properties_t * const Props_p,
        bool * const fValid_p)
{
    int32_t funcres = 0;
    Device_Admin_t ** DevAdmin_pp = Device_Internal_Admin_Get();
    const Device_Global_Admin_t * const DevGlobalAdmin_p =
                        Device_Internal_Admin_Global_Get();

    if (!DevGlobalAdmin_p->fInitialized)
    {
        LOG_CRIT("%s: failed, not initialized\n", __func__);
        funcres = -1;
    }
    else
    {
#ifdef HWPAL_STRICT_ARGS_CHECK
        if (Index >= Device_Internal_Count_Get())
        {
            LOG_CRIT("%s: failed, invalid index %d, max device count %d\n",
                     __func__, Index, Device_Internal_Count_Get());
            funcres = -1;
        }
        else
        {
            if ((Props_p == NULL) || (fValid_p == NULL))
            {
                LOG_CRIT("%s: failed, invalid pointers for device index %d\n",
                         __func__, Index);
                funcres = -1;
            }
            else
            {
#endif
                if (DevAdmin_pp[Index] != NULL)
                {
                    LOG_INFO("%s: device with index %d not present\n", __func__, Index);
                    *fValid_p = false;
                }
                else
                {
                    Props_p->Name_p          = DevAdmin_pp[Index]->DevName;
                    Props_p->StartByteOffset = DevAdmin_pp[Index]->FirstOfs;
                    Props_p->LastByteOffset  = DevAdmin_pp[Index]->LastOfs;
                    Props_p->Flags           = (char)DevAdmin_pp[Index]->Flags;
                    *fValid_p = true;
                }
#ifdef HWPAL_STRICT_ARGS_CHECK
            }
        }
#endif
    }
    return funcres;
}


#if HWPAL_DEVICE_ALLOW_ADD_DEVICE
/*----------------------------------------------------------------------------
 * Device_Add
 */
int32_t
Device_Add(
        const uint32_t Index,
        const Device_Properties_t * const Props_p)
{
    int32_t funcres = 0;
    Device_Admin_t ** DevAdmin_pp = Device_Internal_Admin_Get();
    const Device_Global_Admin_t * const DevGlobalAdmin_p =
                        Device_Internal_Admin_Global_Get();

    if (!DevGlobalAdmin_p->fInitialized)
    {
        LOG_CRIT("%s: failed, not initialized\n", __func__);
        funcres = -1;
    }
    else
    {
#ifdef HWPAL_STRICT_ARGS_CHECK
        if (Index >= Device_Internal_Count_Get())
        {
            LOG_CRIT("%s: failed, invalid index %d, max device count %d\n",
                     __func__, Index, Device_Internal_Count_Get());
            funcres = -1;
        }
        else
        {
            if ((Props_p == NULL) || (Props_p->Name_p == NULL))
            {
                LOG_CRIT("%s: failed, invalid properties for device index %d\n",
                         __func__, Index);
                funcres = -1;
            }
            else
            {
#endif
                if (DevAdmin_pp[Index] != NULL)
                {
                    LOG_CRIT("%s: device with index %d already added\n", __func__, Index);
                    funcres = -1;
                }
                else
                {
                    if (DeviceLib_Device_Exists(Props_p->Name_p))
                    {
                        LOG_CRIT("%s: device with name %s already added\n",
                                 __func__, Props_p->Name_p);
                        funcres = -1;
                    }
                    else
                    {
                        // Allocate memory for device administration data
                        DevAdmin_pp[Index] = Device_Internal_Alloc(sizeof(Device_Admin_t));
                        if (DevAdmin_pp[Index] == NULL)
                        {
                            LOG_CRIT("%s: failed to allocate device (index %d, name %s)\n",
                                     __func__, Index, Props_p->Name_p);
                            funcres = -1;
                        }
                        else
                        {
                            (void)strcpy(DevAdmin_pp[Index]->DevName, Props_p->Name_p);

                            // Copy the rest
                            DevAdmin_pp[Index]->FirstOfs  = Props_p->StartByteOffset;
                            DevAdmin_pp[Index]->LastOfs   = Props_p->LastByteOffset;
                            DevAdmin_pp[Index]->Flags     = (uint32_t)Props_p->Flags;

                            // Set default values
                            DevAdmin_pp[Index]->DeviceNr  = 0;
#ifdef HWPAL_DEVICE_MAGIC
                            DevAdmin_pp[Index]->Magic     = HWPAL_DEVICE_MAGIC;
#endif

                            DevAdmin_pp[Index]->DeviceId  = Index;
                        }
                    }
                }
#ifdef HWPAL_STRICT_ARGS_CHECK
            }
        }
#endif
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * Device_Remove
 */
int32_t
Device_Remove(
        const uint32_t Index)
{
    int32_t funcres = 0;
    Device_Admin_t ** DevAdmin_pp = Device_Internal_Admin_Get();
    const Device_Global_Admin_t * const DevGlobalAdmin_p =
                        Device_Internal_Admin_Global_Get();

    if (!DevGlobalAdmin_p->fInitialized)
    {
        LOG_CRIT("%s: failed, not initialized\n", __func__);
        funcres = -1;
    }
    else
    {
#ifdef HWPAL_STRICT_ARGS_CHECK
        if (Index >= Device_Internal_Count_Get())
        {
            LOG_CRIT("%s: failed, invalid index %d, max device count %d\n",
                     __func__, Index, Device_Internal_Count_Get());
            funcres = -1;
        }
        else
        {
#endif
            if (DevAdmin_pp[Index] != NULL)
            {
                LOG_CRIT("%s: device with index %d already removed\n",
                         __func__, Index);
                funcres = -1;
            }
            else
            {
                DevAdmin_pp[Index] = NULL;
            }
#ifdef HWPAL_STRICT_ARGS_CHECK
        }
#endif
    }

    return funcres;
}
#endif


/*-----------------------------------------------------------------------------
 * Device_GetName
 */
char *
Device_GetName(
        const uint32_t Index)
{
    char *funcres;
    Device_Admin_t ** DevAdmin_pp = Device_Internal_Admin_Get();
    const Device_Global_Admin_t * const DevGlobalAdmin_p =
                        Device_Internal_Admin_Global_Get();

    if (!DevGlobalAdmin_p->fInitialized)
    {
        LOG_CRIT("%s: failed, not initialized\n", __func__);
        funcres = NULL;
    }
    else
    {
#ifdef HWPAL_STRICT_ARGS_CHECK
        if (Index >= Device_Internal_Count_Get())
        {
            LOG_CRIT("%s: failed, invalid index %d, max device count %d\n",
                     __func__, Index, Device_Internal_Count_Get());
            funcres = NULL;
        }
        else
        {
#endif
            if (DevAdmin_pp[Index] != NULL)
            {
                LOG_CRIT("%s: device with index %d already removed\n",
                         __func__, Index);
                funcres = NULL;
            }
            else
            {
                funcres = DevAdmin_pp[Index]->DevName; // success
            }
#ifdef HWPAL_STRICT_ARGS_CHECK
        }
#endif
    }
    return funcres;
}


/*-----------------------------------------------------------------------------
 * Device_GetIndex
 */
int32_t
Device_GetIndex(
        const Device_Handle_t Device)
{
    int32_t funcres;
    const Device_Global_Admin_t * const DevGlobalAdmin_p =
                        Device_Internal_Admin_Global_Get();

    if (!DevGlobalAdmin_p->fInitialized)
    {
        LOG_CRIT("%s: failed, not initialized\n", __func__);
        funcres = -1;
    }
    else
    {
        funcres = Device_Internal_GetIndex(Device);
    }

    return funcres;
}


/*-----------------------------------------------------------------------------
 * Device_GetCount
 */
uint32_t
Device_GetCount(void)
{
    return Device_Internal_Count_Get();
}


/* end of file device_generic.c */
