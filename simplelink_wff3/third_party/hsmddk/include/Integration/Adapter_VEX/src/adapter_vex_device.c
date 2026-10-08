/* adapter_vex_device.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the device related functionality.
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

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/c_adapter_vex.h>          // configuration

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_internal.h>   // API implementation
#ifdef VEX_ENABLE_FIRMWARE_LOAD
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_firmware.h>       // Adapter_Firmware_*
#endif
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_sleep.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_mgmt.h>
#include <third_party/hsmddk/include/Kit/EIP130/MailboxControl/incl/eip130.h>
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_system.h>

#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_interrupts.h>


#define VEX_DEVICE_MAX_MAILBOXES    8U
#define VEX_DEVICE_MAX_CLEANUPS     8

static Device_Handle_t gl_VexDevice = NULL;
static int32_t gl_VexDeviceRefCnt = 0;          // vex_DeviceInit call reference counter
static int32_t gl_VexDevicePWRState = VEX_DEVICE_POWER_UNKNOWN;
static uint8_t gl_VexDeviceMyHostID = 0;        // My Host ID
static uint8_t gl_VexDeviceMyProt = 0;          // My Protection bit setting
static uint8_t gl_VexDeviceMasterID = 0;        // Host ID of master
static uint8_t gl_VexDeviceProtAvailable = 0;   // Protection functionality available
static uint8_t gl_VexDeviceNrOfMailboxes = 0;   // Number of mailboxes
static uint16_t gl_VexDeviceMailboxSize = 256;  // Mailbox size (256 bytes)
static uint16_t gl_VexDeviceTokenID = 0;        // TokenID reference counter

// Mailbox linking state
// 0x0000   = Not Linked
// 0xFFFF   = Linked for the sequence ->
//                link - one operation - unlink
// identity = Linked by a calling process for the sequence ->
//                link - multiple operations - unlink
static uint32_t gl_VexDeviceMailboxLinked[VEX_DEVICE_MAX_MAILBOXES];


static int32_t
vexLocal_DeviceInit(
        int32_t FirmwareCheckInfo)
{
    int32_t funcres = 0;

#ifdef VEX_ENABLE_FIRMWARE_LOAD
    // FirmwareCheckInfo == 1 for HW3, HW2 does not specify an action when fwcheck info = 1
    if ((FirmwareCheckInfo == 0) || (FirmwareCheckInfo == 1))
    {
        Adapter_Firmware_t FirmwareHandle;
        const uint32_t * Firmware_p;
        uint32_t Firmware_Word32Count;

        // Get the firmware image
        FirmwareHandle = Adapter_Firmware_Acquire(VEX_FIRMWARE_FILE,
                                                  &Firmware_p, &Firmware_Word32Count);
        if (FirmwareHandle == NULL)
        {
            funcres = -3;
        }
        else
        {
            // Load the firmware image
            rc = EIP130_FirmwareLoad(gl_VexDevice, VEX_MAILBOX_NR,
                                     Firmware_p, Firmware_Word32Count);
            Adapter_Firmware_Release(FirmwareHandle);
            if (rc < 0)
            {
                LOG_CRIT(VEX_LOG_PREFIX "FAILED Firmware load (%d)\n", rc);
                vex_DeviceStateIssue();
                funcres = -4;
            }
        }
    }
    else if(FirmwareCheckInfo == 3)
    {
        LOG_INFO(VEX_LOG_PREFIX "ROM-Only detected - skipping FWRAM load\n");
    }
    else
    {
        LOG_CRIT(VEX_LOG_PREFIX "FAILED Firmware Check (%d)\n", FirmwareCheckInfo);
    }
#else
    IDENTIFIER_NOT_USED(FirmwareCheckInfo);
#endif

    if (funcres == 0)
    {
        gl_VexDevicePWRState = VEX_DEVICE_POWER_ACTIVE;

        // Get exclusive access to the requested mailbox
        if (EIP130_MailboxLink(gl_VexDevice, VEX_MAILBOX_NR) != 0)
        {
            funcres = -6;
        }
        else
        {
            int32_t i = 0;

            // Check if OUT mailbox is unexpectedly FULL?
            // -> Remove result tokens
            while (EIP130_MailboxCanReadToken(gl_VexDevice, VEX_MAILBOX_NR))
            {
                Eip130Token_Result_t ResultToken;

                if (EIP130_MailboxReadToken(gl_VexDevice, VEX_MAILBOX_NR, &ResultToken) != 0)
                {
                    funcres = -7;
                    break;
                }

                i++;
                if (i > 3)
                {
                    funcres = -7;
                    break;
                }
            }

            if (funcres == 0)
            {
                // Check if IN mailbox is unexpectedly FULL?
                if (!EIP130_MailboxCanWriteToken(gl_VexDevice, VEX_MAILBOX_NR, NULL))
                {
                    funcres = -8;
                }
                else
                {
                    // TI Modification: Removing Firmware Login token as it may only be required for FIPS compliance
                    // TI Modification: HSM_DDK-8 to track.
                    #if DRIVER_TI_MODIFICATIONS_EXCLUDES
                    LOG_CRIT(VEX_LOG_PREFIX "Submit Firmware login\n");
                    /* Perform a firmware login to unlock full firmware potential */
                    rc = EIP130_FirmwareLogin(gl_VexDevice, VEX_MAILBOX_NR,
                                              VEX_CRYPTO_OFFICER_ID,
#ifndef VEX_MAILBOX_LINK_ONLY_ONCE
                                              true
#else
                                              false
#endif
                                              );
                    if (rc < 0)
                    {
                        /* Login token supported, but access or verify error occured */
                        LOG_CRIT(VEX_LOG_PREFIX "FAILED Firmware login (%d)\n", rc);
                        funcres = -9;
                    }
                    #endif
                }
            }
        }
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vex_DeviceInit
 */
int32_t
vex_DeviceInit(void)
{
    int32_t rc = 0;

    if (gl_VexDevice == NULL)
    {
        uint32_t i;

        // Get the EIP-130 device reference
        gl_VexDevice = Device_Find(VEX_DEVICE_NAME);
        if (gl_VexDevice == NULL)
        {
            rc = -1;
        }
        else
        {
            gl_VexDeviceRefCnt++;
            vex_DeviceStateIssue();

            // Reset mailbox linked indications
            for (i = 0U; i < VEX_DEVICE_MAX_MAILBOXES; i++)
            {
                gl_VexDeviceMailboxLinked[i] = 0;
            }

            // Check device and firmware state
            rc = EIP130_FirmwareCheck(gl_VexDevice);
            if (rc == -1)
            {
                // Not supported hardware
                rc = -2;
            }
            else
            {
                // Get mailbox related information and check given mailbox
                EIP130_MailboxGetOptions(gl_VexDevice,
                                            &gl_VexDeviceMyHostID,
                                            &gl_VexDeviceMasterID,
                                            &gl_VexDeviceMyProt,
                                            &gl_VexDeviceProtAvailable,
                                            &gl_VexDeviceNrOfMailboxes,
                                            &gl_VexDeviceMailboxSize,
                                            NULL, NULL);
                if (VEX_MAILBOX_NR <= vex_DeviceMailboxes())
                {
                    rc = vexLocal_DeviceInit(rc);
                }
                else
                {
                    rc = -2;
                }
            }
        }
    }
    else
    {
        gl_VexDeviceRefCnt++;
    }

    return rc;
}


/*----------------------------------------------------------------------------
 * vex_DeviceExit
 */
void
vex_DeviceExit(void)
{
    if (gl_VexDevice != NULL)
    {
        gl_VexDeviceRefCnt--;
        if (gl_VexDeviceRefCnt <= 0)
        {
            uint32_t i;

            for (i = 0U; i < VEX_DEVICE_MAX_MAILBOXES; ++i)
            {
                if (gl_VexDeviceMailboxLinked[i] != 0U)
                {
                    (void)EIP130_MailboxUnlink(gl_VexDevice, (uint8_t)(i + 1U));
                    gl_VexDeviceMailboxLinked[i] = 0U;
                }
            }

            gl_VexDevice = NULL;
            gl_VexDeviceRefCnt = 0;
            gl_VexDeviceMyProt = 0; // Protection bit setting reset
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    if (gl_VexDevice != NULL)
    {
        LOG_CRIT(VEX_LOG_PREFIX "FAILED to un-initialize device\n");
    }
    else
    {
        /* MISRA - Intentially empty */
    }
}


/*----------------------------------------------------------------------------
 * vex_DeviceGetHandle
 */
Device_Handle_t
vex_DeviceGetHandle(void)
{
    Device_Handle_t DeviceHandle = gl_VexDevice;
    if ((DeviceHandle != NULL) &&
        (gl_VexDevicePWRState == VEX_DEVICE_POWER_UNKNOWN))
    {
        // Check device and firmware state
        int32_t rc = EIP130_FirmwareCheck(DeviceHandle);
        switch (rc)
        {
        case 3:
            // Firmware ready for use (firmware is accepted)
            break;
        case 2:
            // Firmware checks busy - assume all will go OK
            break;

        case 1:
        case 0:
            // Firmware needs to loaded
            if (vexLocal_DeviceInit(rc) != 0)
            {
                // - Device initialization failed
                DeviceHandle = NULL;
            }
            break;

        default:
            // Possible return situations:
            // - No device connection
            // - Device initialization failed
            // - Device initialization busy (other host)
            // - Host not allowed to do the image load
            DeviceHandle = NULL;
            break;
        }
    }

    return DeviceHandle;
}


/*----------------------------------------------------------------------------
 * vex_DeviceIsSecureConnected
 */
bool
vex_DeviceIsSecureConnected(void)
{
    bool funcres = false;

    // Device connection available and protection bit set
    if (gl_VexDeviceMyProt != 0U)
    {
        funcres = true;
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vex_DeviceStateIssue
 */
void
vex_DeviceStateIssue(void)
{
    gl_VexDevicePWRState = VEX_DEVICE_POWER_UNKNOWN;
}

/*----------------------------------------------------------------------------
 * vex_DeviceLinkMailbox
 */
uint8_t
vex_DeviceMailboxes(void)
{
    return gl_VexDeviceNrOfMailboxes;
}

/*----------------------------------------------------------------------------
 * vex_DeviceLinkMailbox
 */
int32_t
vex_DeviceLinkMailbox(
           const uint8_t MailboxNr,
           uint32_t Identity)
{
    int32_t funcres = 0;

    // Device connection available
    if (gl_VexDevice == NULL)
    {
        funcres = -1;
    }
    else
    {
        // Valid mailbox
        if ((MailboxNr == 0U) || (MailboxNr > gl_VexDeviceNrOfMailboxes))
        {
            funcres = -2;
        }
        else
        {
            if (gl_VexDeviceMailboxLinked[MailboxNr - 1U] == 0U)
            {
#ifndef VEX_MAILBOX_LINK_ONLY_ONCE
                // Get exclusive access to the requested mailbox
                if (EIP130_MailboxLink(gl_VexDevice, MailboxNr) != 0)
                {
                    // Mailbox could be locked by another host
                    funcres = -3;
                }
                else
#endif
                {
                    gl_VexDeviceMailboxLinked[MailboxNr - 1U] = Identity;
                }
            }
            else if (gl_VexDeviceMailboxLinked[MailboxNr - 1U] != Identity)
            {
                // Mailbox lock for another process
                funcres = -4;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vex_DeviceLinkMailboxOverrule
 */
int32_t
vex_DeviceLinkMailboxOverrule(
           const uint8_t MailboxNr,
           uint32_t Identity)
{
    int32_t funcres = 0;

    // Device connection available
    if (gl_VexDevice == NULL)
    {
        funcres = -1;
    }
    else
    {
        // Valid mailbox
        if ((MailboxNr == 0U) || (MailboxNr > vex_DeviceMailboxes()))
        {
            funcres = -2;
        }
        else
        {
#ifndef VEX_MAILBOX_LINK_ONLY_ONCE
            // Get exclusive access to the requested mailbox
            if (EIP130_MailboxLink(gl_VexDevice, MailboxNr) != 0)
            {
                // Mailbox could be locked by another host
                funcres = -3;
            }
            else
#endif
            {
                gl_VexDeviceMailboxLinked[MailboxNr - 1U] = Identity;
            }
        }
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vex_DeviceUnlinkMailbox
 */
int32_t
vex_DeviceUnlinkMailbox(
           const uint8_t MailboxNr,
           uint32_t Identity)
{
    int32_t funcres = 0;

    // Device connection available
    if (gl_VexDevice == NULL)
    {
        funcres = -1;
    }
    else
    {
        // Valid mailbox
        if ((MailboxNr == 0U) || (MailboxNr > gl_VexDeviceNrOfMailboxes))
        {
            funcres = -2;
        }
        else
        {
            if (gl_VexDeviceMailboxLinked[MailboxNr - 1U] == Identity)
            {
                gl_VexDeviceMailboxLinked[MailboxNr - 1U] = 0U;

#ifndef VEX_MAILBOX_LINK_ONLY_ONCE
                // Release exclusive access to the requested mailbox
                if (EIP130_MailboxUnlink(gl_VexDevice, MailboxNr) != 0U)
                {
                    // Probably forced link by another host
                    funcres = -3;
                }
#endif
            }
            else if (gl_VexDeviceMailboxLinked[MailboxNr - 1U] != 0U)
            {
                // Not allowed to unlink the mailbox that is locked by another process
                funcres = -4;
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vex_DeviceGetTokenID
 */
uint16_t
vex_DeviceGetTokenID(void)
{
    // Generate a TokenID
    gl_VexDeviceTokenID++;
    if (gl_VexDeviceTokenID == 0U)
    {
        gl_VexDeviceTokenID++;
    }

    return gl_VexDeviceTokenID;
}

/*----------------------------------------------------------------------------
 * vex_DeviceSleep
 */
#ifdef VEX_ENABLE_FIRMWARE_SLEEP
VexStatus_t
vex_DeviceSleep(void)
{
    VexStatus_t rc = VEX_SUCCESS;

    // Device connection available
    if (gl_VexDevice == NULL)
    {
        rc = VEX_NOT_CONNECTED;
    }
    else
    {
        if (gl_VexDevicePWRState == VEX_DEVICE_POWER_ACTIVE)
        {
            Eip130Token_Command_t CommandResult;
            int32_t nRetries;
            uint32_t Identity;
            uint16_t TokenId;
            uint8_t MailboxNumber;

            // Check if firmware needs to be loaded
            rc = EIP130_FirmwareCheck(gl_VexDevice);
            switch (rc)
            {
            case 3:
                // Firmware ready for use (firmware is accepted)
                break;
            case -1:
                vex_DeviceStateIssue();
                rc = VEX_NOT_CONNECTED;
                break;
            case -2:
                rc = VEX_OPERATION_NOT_ALLOWED;
                break;
            default:
                // The firmware is not in accepted state
                vex_DeviceStateIssue();
                rc = VEX_POWER_STATE_ERROR;
                break;
            }

            if (rc >= 0)
            {
                // Get and set identity of calling process
                Identity = vex_IdentityGet();
                if (Identity == 0U)
                {
                    rc = VEX_NO_IDENTITY;
                }
                else
                {
                    // Get mailbox number to use
                    MailboxNumber = vex_MailboxGet(Identity);
                    if (MailboxNumber == 0U)
                    {
                        rc = VEX_NO_MAILBOX;
                    }
                    else
                    {
                        // Make sure the mailbox is linked for use
                        rc = VEX_MAILBOX_IN_USE;    // Assume link error
                        for (nRetries = 0; nRetries < 2; nRetries++)
                        {
                            rc = EIP130_MailboxLink(gl_VexDevice, MailboxNumber);
                            if (rc == 0)
                            {
                                rc = VEX_SUCCESS;
                                break;
                            }
                            if (nRetries == 0)
                            {
                                // Reset link assume that mailbox is in use by another Host.
                                rc = EIP130_MailboxLinkReset(gl_VexDevice, MailboxNumber);
                            }
                        }

                        if (rc == VEX_SUCCESS)
                        {
                            gl_VexDeviceMailboxLinked[MailboxNumber - 1U] = Identity;

                            // Check if mailbox is ready for the token
                            if (!EIP130_MailboxCanWriteToken(gl_VexDevice, MailboxNumber, NULL))
                            {
                                rc = VEX_MAILBOX_IN_USE;    // General error
                            }
                            else
                            {
                                // Write Sleep token
                                Eip130Token_Command_SystemSleep(&CommandResult);
                                Eip130Token_Command_Identity(&CommandResult, Identity);
                                TokenId = vex_DeviceGetTokenID();
                                CommandResult.W[0] |= TokenId;
                                rc = EIP130_MailboxWriteAndSubmitToken(gl_VexDevice, MailboxNumber,
                                                                       &CommandResult, false);
                                switch (rc)
                                {
                                case 0:
                                    break;
                                case -3:
                                    rc = VEX_MAILBOX_IN_USE;
                                    break;
                                case -4:
                                    vex_DeviceStateIssue(); // Report device state issue detected
                                    rc = VEX_POWER_STATE_ERROR;
                                    break;
                                default:
                                    rc = VEX_INTERNAL_ERROR;
                                    break;
                                }

                                if (rc == 0)
                                {
                                    // Wait and read output token
                                    do
                                    {
                                        for (nRetries = 0x00FFFFFF; nRetries != 0; nRetries--)
                                        {
                                            if (EIP130_MailboxCanReadToken(gl_VexDevice, MailboxNumber))
                                            {
                                                break;
                                            }
                                        }

                                        rc = EIP130_MailboxReadToken(gl_VexDevice, MailboxNumber,
                                                                     (Eip130Token_Result_t *)&CommandResult);
                                        if (rc < 0)
                                        {
                                            rc = VEX_INTERNAL_ERROR;
                                            break;
                                        }
                                    } while ((CommandResult.W[0] & MASK_16_BITS) != TokenId);

                                    if (rc == 0)
                                    {
                                        rc = Eip130Token_Result_Code((Eip130Token_Result_t *)&CommandResult);
                                        if (rc < 0)
                                        {
                                            rc -= 256;
                                        }
                                        else
                                        {
                                            gl_VexDevicePWRState = VEX_DEVICE_POWER_SLEEP;
                                        }
                                    }
                                }
                            }
                            // Unlink the mailbox
                            (void)vex_DeviceUnlinkMailbox(MailboxNumber, Identity);
                        }
                    }
                }
            }
        }
        else
        {
            rc = VEX_POWER_STATE_ERROR; // Invalid state
        }
    }

    return rc;
}
#endif

/*----------------------------------------------------------------------------
 * vex_DeviceResumeFromSleep
 */
#ifdef VEX_ENABLE_FIRMWARE_SLEEP
VexStatus_t
vex_DeviceResumeFromSleep(void)
{
    Eip130Token_Command_t CommandResult;
    VexStatus_t rc;
    uint32_t nRetries;
    uint32_t Identity;
    uint16_t TokenId;
    uint8_t MailboxNumber;
    uint8_t fReady = 0U;
    uint8_t fFWRam;

    // Device connection available
    if (gl_VexDevice == NULL)
    {
        rc = VEX_NOT_CONNECTED;
        fReady = 255U;
    }
    else
    {
        if (gl_VexDeviceMyHostID != gl_VexDeviceMasterID)
        {
            // This Host is NOT allowed to do the Sleep operation
            rc = VEX_OPERATION_NOT_ALLOWED;
            fReady = 255U;
        }
        else
        {
            // Check if firmware needs to be loaded
            rc = (VexStatus_t)EIP130_FirmwareCheck(gl_VexDevice);
            switch (rc)
            {
            case 3:
            case 2:
                // Firmware ready for use (firmware is accepted) or
                // the firmware is loaded and the firmware checks are busy
                rc = 0;
                fReady = 255U;
                break;
            case 1:
            case 0:
                // Assume Firmware is loaded already (in sleep state)
                break;

            default:
                // General error
                fReady = 255U;
                break;
            }
        }
    }
    if (fReady == 0U)
    {
        // Get and set identity of calling process
        Identity = vex_IdentityGet();
        if (Identity == 0U)
        {
            rc = VEX_NO_IDENTITY;
            fReady = 255U;
        }
        else
        {
            // Get mailbox number to use
            MailboxNumber = vex_MailboxGet(Identity);
            if (MailboxNumber == 0U)
            {
                rc = VEX_NO_MAILBOX;
                fReady = 255U;
            }
            else
            {
                // Link mailbox
                // Note: The HW is expected to come out of sleep state, so mailbox
                //       linking should be possible!
                rc = VEX_MAILBOX_IN_USE;    // Assume link error
                for (nRetries = 0U; nRetries < 2U; nRetries++)
                {
                    rc = EIP130_MailboxLink(gl_VexDevice, MailboxNumber);
                    if (rc == 0)
                    {
                        rc = VEX_SUCCESS;
                        break;
                    }
                    if (nRetries == 0U)
                    {
                        // Reset link assume that mailbox is in use by another Host
                        rc = EIP130_MailboxLinkReset(gl_VexDevice, MailboxNumber);
                    }
                }
                if (rc != VEX_SUCCESS)
                {
                    fReady = 255U;
                }
            }
        }
    }
    if (fReady == 0U)
    {
        // Reset mailbox linked indications
        for (nRetries = 0U; nRetries < VEX_DEVICE_MAX_MAILBOXES; ++nRetries)
        {
            gl_VexDeviceMailboxLinked[nRetries] = 0;
        }

        // Check if mailbox is ready for the token
        // Note: The HW is expected to come out of HW reset state, so direct
        //       mailbox use should be possible!
        if (!EIP130_MailboxCanWriteToken(gl_VexDevice, MailboxNumber, NULL))
        {
            rc = VEX_MAILBOX_IN_USE;
            fReady = 255U;
        }
        else
        {
            // Write Resume From Sleep token
            Eip130Token_Command_SystemResumeFromSleep(&CommandResult);
            Eip130Token_Command_Identity(&CommandResult, Identity);
            TokenId = vex_DeviceGetTokenID();
            Eip130Token_Command_SetTokenID(&CommandResult, TokenId, false);
            rc = EIP130_MailboxWriteAndSubmitToken(gl_VexDevice, MailboxNumber,
                                                   &CommandResult, false);
            if (rc >= 0)
            {
                // Check firmware configuration
                EIP130_ModuleGetOptions(gl_VexDevice, &fFWRam, NULL, NULL, NULL);
                if (fFWRam != 0U)
                {
                    uint8_t fFirmwareAccepted;

                    // Indicate that the firmware is written
                    EIP130_ModuleFirmwareWritten(gl_VexDevice);

                    // Check Resume from Sleep sequence
                    // Note: The firmware check indication sequence can be missed due to
                    //       environment behavior, thus only check the firmware accecpted
                    //       indication.
                    nRetries = 0x7FFFFFFF;
                    while (true)
                    {
                        EIP130_ModuleGetStatus(gl_VexDevice, NULL, NULL,
                                               NULL, NULL, NULL, NULL,
                                               NULL, NULL, &fFirmwareAccepted);
                        if (fFirmwareAccepted != 0U)
                        {
                            /* Firmware accepted and ready for use */
                            break;
                        }

                        if (EIP130_MailboxCanWriteToken(gl_VexDevice, MailboxNumber, NULL))
                        {
                            if (!EIP130_MailboxCanReadToken(gl_VexDevice, MailboxNumber))
                            {
                                /* Assume the Resume from Sleep has failed due to FWRAM or DataRAM
                                 * corruption. Try to recover with a System Boot (cold boot) */
                                LOG_CRIT(VEX_LOG_PREFIX "Resume from Sleep has failed, trying System Boot...\n");
                                rc = vexLocal_DeviceInit(1);
                                break;
                            }

                            /* Expected that the Firmware was accepted */
                            if (fFWRam != 0U)
                            {
                                /* Retry once */
                                fFWRam = 0U;
                            }
                            else
                            {
                                /* Safeguard */
                                break;
                            }
                        }

                        /* Handle retries */
                        nRetries--;
                        if (nRetries <= 0U)
                        {
                            /* Timeout (Is HW active?) */
                            rc = -4;
                        }
                    }
                }

                if (rc == 0)
                {
                    /* Wait for the Resume from Sleep result */
                    do
                    {
                        for (nRetries = (10000/VEX_POLLING_DELAY_MS); nRetries != 0U; nRetries--)
                        {
                            if (EIP130_MailboxCanReadToken(gl_VexDevice, MailboxNumber))
                            {
                                break;
                            }

                            /* Wait a bit for the next token available check */
                            Adapter_SleepMS(VEX_POLLING_DELAY_MS);
                        }

                        rc = EIP130_MailboxReadToken(gl_VexDevice, MailboxNumber,
                                                     (Eip130Token_Result_t *)&CommandResult);
                        if (rc < 0)
                        {
                            break;            // Unlink mailbox and return error
                        }

                    } while ((CommandResult.W[0] & MASK_16_BITS) != TokenId);

                    if (rc == 0)
                    {
                        /* Check the result */
                        rc = Eip130Token_Result_Code((Eip130Token_Result_t *)&CommandResult);

                        if (rc < 0)
                        {
                            rc -= 256;
                        }
                        else
                        {
                            gl_VexDevicePWRState = VEX_DEVICE_POWER_ACTIVE;

                            /* Perform a firmware login to unlock full firmware potential */
                            rc = EIP130_FirmwareLogin(gl_VexDevice, MailboxNumber,
                                                      VEX_CRYPTO_OFFICER_ID,
#ifndef VEX_MAILBOX_LINK_ONLY_ONCE
                                                      true
#else
                                                      false
#endif
                                                      );
                        }
                    }
                }
            }
        }
    }

    if (rc < 0)
    {
        LOG_CRIT(VEX_LOG_PREFIX "Resume from Sleep failed. (%d)\n", rc);

#ifndef VEX_MAILBOX_LINK_ONLY_ONCE
        // Unlink mailbox
        (void)EIP130_MailboxUnlink(gl_VexDevice, MailboxNumber);
#endif
    }
    else
    {
        // Reinitialize the interrupt registers to restore interrupt functionality
        rc = Adapter_Interrupts_ReInit();
    }

    return rc;
}
#endif

/* end of file adapter_vex_device.c */
