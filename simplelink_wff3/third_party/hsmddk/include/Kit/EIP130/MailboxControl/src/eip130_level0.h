/* eip130_level0.h
 *
 * This file contains all the macros and inline functions that allow
 * access to the EIP-130 Root of Trust / Security Module registers
 * and to build the values read or written to the registers as well
 * as the tokens.
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

#ifndef INCLUDE_GUARD_EIP130_LEVEL0_H
#define INCLUDE_GUARD_EIP130_LEVEL0_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, BIT_* etc. */
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_types.h>           /* Device_Handle_t */
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_rw.h>              /* Read32, Write32 */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* EIP-130 configuration and Eip130RegisterWord_t */


/* EIP130 mailbox memory locations as offset from a base address */
/* Note: IN-mailbox is write-only, OUT-mailbox is read-only */
#define EIP130_MAILBOX_IN_BASE                  0x0000U
#define EIP130_MAILBOX_OUT_BASE                 0x0000U
#define EIP130_MAILBOX_SPACING_BYTES            0x0400U /* Actual mailbox size independent */

/* EIP130 mailbox register locations as offset from a base address */
#define EIP130_REGISTEROFFSET_MAILBOX_STAT      0x3F00U
#define EIP130_REGISTEROFFSET_MAILBOX_CTRL      0x3F00U
#define EIP130_REGISTEROFFSET_MAILBOX_RAWSTAT   0x3F04U
#define EIP130_REGISTEROFFSET_MAILBOX_RESET     0x3F04U
#define EIP130_REGISTEROFFSET_MAILBOX_LINKID    0x3F08U
#define EIP130_REGISTEROFFSET_MAILBOX_OUTID     0x3F0CU
#define EIP130_REGISTEROFFSET_MAILBOX_LOCKOUT   0x3F10U

/* EIP130 module register locations as offset from a base address */
#define EIP130_REGISTEROFFSET_MODULE_STATUS     0x3FE0U
#define EIP130_REGISTEROFFSET_EIP_OPTIONS2      0x3FF4U
#define EIP130_REGISTEROFFSET_EIP_OPTIONS       0x3FF8U
#define EIP130_REGISTEROFFSET_EIP_VERSION       0x3FFCU

/* EIP130 Firmware RAM location as offset from a base address */
#define EIP130_FIRMWARE_RAM_BASE                0x4000U

/* EIP130 Firmware download related synchronisation defines */
#define EIP130_FIRMWARE_WRITTEN                 BIT_20
#define EIP130_FIRMWARE_CHECKS_BUSY             BIT_22
#define EIP130_FIRMWARE_ACCEPTED                BIT_23

/* EIP130 Hardware state/error indications */
#define EIP130_CRC24_BUSY                       BIT_8
#define EIP130_CRC24_OK                         BIT_9
#define EIP130_FATAL_ERROR                      BIT_31


#if !defined(EIP130_REMOVE_READMAILBOXSTATUS) || \
    !defined(EIP130_REMOVE_MAILBOXLINK) || \
    !defined(EIP130_REMOVE_MAILBOXLINKID) || \
    !defined(EIP130_REMOVE_MAILBOXLINKRESET) || \
    !defined(EIP130_REMOVE_MAILBOXUNLINK) || \
    !defined(EIP130_REMOVE_MAILBOXCANWRITETOKEN) || \
    !defined(EIP130_REMOVE_FIRMWAREDOWNLOAD) || \
    !defined(EIP130_REMOVE_FIRMWARELOGIN)
static Eip130RegisterWord_t
EIP130_RegisterReadMailboxStatus(
        Device_Handle_t Device)
{
    return (Eip130RegisterWord_t)Device_Read32(Device,
                                               EIP130_REGISTEROFFSET_MAILBOX_STAT);
}
#endif

#if !defined(EIP130_REMOVE_WRITEMAILBOXCONTROL) || \
    !defined(EIP130_REMOVE_MAILBOXLINK) || \
    !defined(EIP130_REMOVE_MAILBOXUNLINK)
static void
EIP130_RegisterWriteMailboxControl(
        Device_Handle_t Device,
        Eip130RegisterWord_t Value)
{
    (void)Device_Write32(Device, EIP130_REGISTEROFFSET_MAILBOX_CTRL,
                         (uint32_t)Value);
}
#endif

#ifndef EIP130_REMOVE_MAILBOXRAWSTATUS
static Eip130RegisterWord_t
EIP130_RegisterReadMailboxRawStatus(
        Device_Handle_t Device)
{
    return (Eip130RegisterWord_t)Device_Read32(Device,
                                               EIP130_REGISTEROFFSET_MAILBOX_RAWSTAT);
}
#endif

#if !defined(EIP130_REMOVE_MAILBOXRESET) || \
    !defined(EIP130_REMOVE_MAILBOXLINKRESET) || \
    !defined(EIP130_REMOVE_FIRMWAREDOWNLOAD)
static void
EIP130_RegisterWriteMailboxReset(
        Device_Handle_t Device,
        Eip130RegisterWord_t Value)
{
    (void)Device_Write32(Device, EIP130_REGISTEROFFSET_MAILBOX_RESET,
                         (uint32_t)Value);
}
#endif

#ifndef EIP130_REMOVE_MAILBOXLINKID
static Eip130RegisterWord_t
EIP130_RegisterReadMailboxLinkId(
        Device_Handle_t Device)
{
    return (Eip130RegisterWord_t)Device_Read32(Device,
                                               EIP130_REGISTEROFFSET_MAILBOX_LINKID);
}
#endif

#ifndef EIP130_REMOVE_MAILBOXOUTID
static Eip130RegisterWord_t
EIP130_RegisterReadMailboxOutId(
        Device_Handle_t Device)
{
    return (Eip130RegisterWord_t)Device_Read32(Device,
                                               EIP130_REGISTEROFFSET_MAILBOX_OUTID);
}
#endif

#ifndef EIP130_REMOVE_MAILBOXACCESSCONTROL
static Eip130RegisterWord_t
EIP130_RegisterReadMailboxLockout(
        Device_Handle_t Device)
{
    return (Eip130RegisterWord_t)Device_Read32(Device,
                                               EIP130_REGISTEROFFSET_MAILBOX_LOCKOUT);
}
#endif

#ifndef EIP130_REMOVE_MAILBOXACCESSCONTROL
static void
EIP130_RegisterWriteMailboxLockout(
        Device_Handle_t Device,
        Eip130RegisterWord_t Value)
{
    (void)Device_Write32(Device, EIP130_REGISTEROFFSET_MAILBOX_LOCKOUT,
                         (uint32_t)Value);
}
#endif

#if !defined(EIP130_REMOVE_MODULEGETVERSION) || \
    !defined(EIP130_REMOVE_VERSION_OPTION) || \
    !defined(EIP130_REMOVE_MAILBOXACCESSVERIFY) || \
    !defined(EIP130_REMOVE_FIRMWARECHECK)
static Eip130RegisterWord_t
EIP130_RegisterReadVersion(
        Device_Handle_t Device)
{
    return (Eip130RegisterWord_t)Device_Read32(Device,
                                               EIP130_REGISTEROFFSET_EIP_VERSION);
}
#endif

#if !defined(EIP130_REMOVE_MAILBOXGETOPTIONS) || \
    !defined(EIP130_REMOVE_MAILBOXACCESSVERIFY) || \
    !defined(EIP130_REMOVE_FIRMWAREDOWNLOAD)
static Eip130RegisterWord_t
EIP130_RegisterReadOptions(
        Device_Handle_t Device)
{
    return (Eip130RegisterWord_t)Device_Read32(Device,
                                               EIP130_REGISTEROFFSET_EIP_OPTIONS);
}
#endif

#if !defined(EIP130_REMOVE_MODULEGETOPTIONS) || \
    !defined(EIP130_REMOVE_MAILBOXCANWRITETOKEN) || \
    !defined(EIP130_REMOVE_FIRMWARECHECK) || \
    !defined(EIP130_REMOVE_FIRMWAREDOWNLOAD) || \
    !defined(EIP130_REMOVE_FIRMWARELOGIN)
static Eip130RegisterWord_t
EIP130_RegisterReadOptions2(
        Device_Handle_t Device)
{
    return (Eip130RegisterWord_t)Device_Read32(Device,
                                               EIP130_REGISTEROFFSET_EIP_OPTIONS2);
}
#endif

#if !defined(EIP130_REMOVE_MODULEGETSTATUS) || \
    !defined(EIP130_REMOVE_MAILBOXCANWRITETOKEN) || \
    !defined(EIP130_REMOVE_FIRMWARECHECK) || \
    !defined(EIP130_REMOVE_FIRMWAREDOWNLOAD) || \
    !defined(EIP130_REMOVE_FIRMWARELOGIN)
static Eip130RegisterWord_t
EIP130_RegisterReadModuleStatus(
        Device_Handle_t Device)
{
    return (Eip130RegisterWord_t)Device_Read32(Device,
                                               EIP130_REGISTEROFFSET_MODULE_STATUS);
}
#endif

#if !defined(EIP130_REMOVE_MODULEFIRMWAREWRITTEN) || \
    !defined(EIP130_REMOVE_FIRMWAREDOWNLOAD)
static void
EIP130_RegisterWriteModuleStatus(
        Device_Handle_t Device,
        Eip130RegisterWord_t Value)
{
    (void)Device_Write32(Device, EIP130_REGISTEROFFSET_MODULE_STATUS,
                         (uint32_t)Value);
}
#endif


#endif /* INCLUDE_GUARD_EIP130_LEVEL0_H */

/* end of file eip130_level0.h */
