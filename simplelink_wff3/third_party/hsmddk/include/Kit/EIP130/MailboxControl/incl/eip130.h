/* eip130.h
 *
 * EIP-130 Root of Trust / Security Module Driver Library API
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

#ifndef INCLUDE_GUARD_EIP130_H
#define INCLUDE_GUARD_EIP130_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_types.h>           /* Device_Handle_t */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */


/*----------------------------------------------------------------------------
 * EIP130_ModuleGetOptions
 *
 * This function can be used to retrieve specific module hardware related
 * information of this EIP-130. The pointer arguments define the information
 * that can be retrieved.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * fFWRam_p (optional)
 *     Pointer to the memory location where the Firmware RAM indication of this
 *     EIP-130 will be written. (0=No FWRAM, 1=FWRAM available)
 *
 * BusIfc_p (optional)
 *     Pointer to the memory location where the bus interface type of the
 *     EIP-130 will be written. (1=AXI, 0=AHB)
 *
 * Engines_p (optional)
 *     Pointer to the memory location where engine information of this EIP-130
 *     will be written.
 *
 * CustomEngines_p (optional)
 *     Pointer to the memory location where custom engine information of this
 *     EIP-130 will be written.
 */
void
EIP130_ModuleGetOptions(
        Device_Handle_t Device,
        uint8_t * const fFWRam_p,
        uint8_t * const BusIfc_p,
        uint16_t * const Engines_p,
        uint16_t * const CustomEngines_p);


/*----------------------------------------------------------------------------
 * EIP130_ModuleGetStatus
 *
 * This function can be used to retrieve module status information of this
 * EIP-130. The pointer arguments define the information that can be retrieved.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * fBit0_p (optional)
 *     Pointer to the memory location where the Bit 0 indication of this
 *     EIP-130 will be written. (0=not set, 1=set)
 *
 * fBit1_p (optional)
 *     Pointer to the memory location where the Bit 1 indication of this
 *     EIP-130 will be written. (0=not set, 1=set)
 *
 * fFatalError_p (optional)
 *     Pointer to the memory location where the fatal indication of this
 *     EIP-130 will be written. (0=no error, 1=fatal error)
 *
 * fCRC24Ok_p (optional)
 *     Pointer to the memory location where the CRC24 OK indication of this
 *     EIP-130 will be written. (0=busy/error, 1=OK)
 *
 * fCRC24Busy_p (optional)
 *     Pointer to the memory location where the CRC24 Busy indication of this
 *     EIP-130 will be written. (0=not busy, 1=Busy)
 *
 * fCRC24Error_p (optional)
 *     Pointer to the memory location where the CRC24 Error indication of this
 *     EIP-130 will be written. (0=no error, 1=error)
 *
 * fFirmwareWritten_p (optional)
 *     Pointer to the memory location where the firmware written indication of
 *     this EIP-130 will be written when FWRAM is available.
 *     (0=not written, 1=written)
 *
 * fFirmwareChecks_p (optional)
 *     Pointer to the memory location where the firmware checks indication
 *     of this EIP-130 will be written when FWRAM is available.
 *     (EIP-130 HW2: 0=not busy, 1=busy)
 *     (EIP-130 HW3: 0=not done/busy, 1=done)
 *
 * fFirmwareAccepted_p (optional)
 *     Pointer to the memory location where the firmware accepted indication of
 *     this EIP-130 will be written when FWRAM is available.
 *     (0=not accepted, 1=accepted)
 */
void
EIP130_ModuleGetStatus(
        Device_Handle_t Device,
        uint8_t * const fBit0_p,
        uint8_t * const fBit1_p,
        uint8_t * const fFatalError_p,
        uint8_t * const fCRC24Ok_p,
        uint8_t * const fCRC24Busy_p,
        uint8_t * const fCRC24Error_p,
        uint8_t * const fFirmwareWritten_p,
        uint8_t * const fFirmwareChecks_p,
        uint8_t * const fFirmwareAccepted_p);


/*----------------------------------------------------------------------------
 * EIP130_ModuleGetVersion
 *
 * This function can be used to retrieve module version information of this
 * EIP-130. The pointer arguments define the information that can be retrieved.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * EipNumber_p (optional)
 *     Pointer to the memory location where the EIP number of this EIP-130
 *     will be written.
 *
 * MajorVersion_p (optional)
 *     Pointer to the memory location where the major version of this EIP-130
 *     will be written.
 *
 * MinorVersion_p (optional)
 *     Pointer to the memory location where the minor version of this EIP-130
 *     will be written.
 *
 * PatchLevel_p (optional)
 *     Pointer to the memory location where the patch level of this EIP-130
 *     will be written.
 */
void
EIP130_ModuleGetVersion(
        Device_Handle_t Device,
        uint8_t * const EipNumber_p,
        uint8_t * const MajorVersion_p,
        uint8_t * const MinorVersion_p,
        uint8_t * const PatchLevel_p);


/*----------------------------------------------------------------------------
 * EIP130_ModuleFirmwareWritten
 *
 * This function can be used to indicate that the firmware is written in FWRAM.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 */
void
EIP130_ModuleFirmwareWritten(
        Device_Handle_t Device);


#ifndef EIP130_REMOVE_MAILBOXACCESSVERIFY
/*----------------------------------------------------------------------------
 * EIP130_MailboxAccessVerify
 *
 * This function can be used to verify that the Device Handle really provides
 * communication to an EIP-130 hardware device.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * MailboxNr
 *     The mailbox number to write this token to (1..4).
 *     The mailbox must be linked to this host.
 *
 * Return Value:
 *     0    Success
 *     <0   Error code:
 *     -1   Not supported - Check if HW is active
 *     -2   Invalid mailbox number
 */
Eip130FunctionStatus_t
EIP130_MailboxAccessVerify(
        Device_Handle_t Device,
        const uint8_t MailboxNr);
#endif


/*----------------------------------------------------------------------------
 * EIP130_MailboxGetOptions
 *
 * This function can be used to retrieve specific mailbox related information
 * of this EIP-130. The pointer arguments define the information that can be
 * retrieved.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * MyHostID_p (optional)
 *     Pointer to the memory location where the HostID for this CPU will be
 *     written.
 *
 * MasterID_p (optional)
 *     Pointer to the memory location where the HostID of the Master CPU will
 *     be written. The Master CPU can use the EIP130_Mailbox_ControlAccess
 *     function.
 *
 * MyProt_p (optional)
 *     Pointer to the memory location where the protection setting for this CPU
 *     will be  written.
 *
 * ProtAvailable_p (optional)
 *     Pointer to the memory location where the protection available
 *     information will be written.
 *
 * NrOfMailboxes_p (optional)
 *     Pointer to the memory location where the number of mailboxes available
 *     on this EIP-130 will be written.
 *
 * MailboxSize_p (optional)
 *     Pointer to the memory location where the size of a mailbox of this
 *     EIP-130 will be written.
 *
 * HostIds_p (optional)
 *     Pointer to the memory location where the EIP-130 host IDs information
 *     will be written.
 *
 * SecureHostId_p (optional)
 *     Pointer to the memory location where the EIP-130 secure host IDs
 *     information will be written.
 */
void
EIP130_MailboxGetOptions(
        Device_Handle_t Device,
        uint8_t * const MyHostID_p,
        uint8_t * const MasterID_p,
        uint8_t * const MyProt_p,
        uint8_t * const ProtAvailable_p,
        uint8_t * const NrOfMailboxes_p,
        uint16_t * const MailboxSize_p,
        uint8_t * const HostId_p,
        uint8_t * const SecureHostId_p);


#ifndef EIP130_REMOVE_MAILBOXLINKID
/*----------------------------------------------------------------------------
 * EIP130_MailboxGetLinkID
 *
 * This function can be used to retrieve information about the host that
 * linked the mailbox.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * MailboxNr
 *     The mailbox number to retrieve the LinkID from (1..4).
 *
 * HostID_p
 *     Pointer to the memory location where the HostID will be written.
 *
 * Secure_p
 *     Pointer to the memory location where the indication will be written
 *     that the host is secure.
 *
 * Return Value:
 *     0    Success
 *     <0   Error code:
 *     -1   Invalid mailbox number
 *     -2   Not linked
 */
Eip130FunctionStatus_t
EIP130_MailboxGetLinkID(
        Device_Handle_t Device,
        const uint8_t MailboxNr,
        uint8_t * const HostID_p,
        uint8_t * const Secure_p);
#endif


#ifndef EIP130_REMOVE_MAILBOXACCESSCONTROL
/*----------------------------------------------------------------------------
 * EIP130_MailboxAccessControl
 *
 * This function is only available to the Master CPU and allows it to control
 * the maibox sharing by allowing only selected hosts to use selected
 * mailboxes. After reset, no host is allowed to access any mailbox.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * MailboxNr
 *     The number of the mailbox (1..M) for which to control the access.
 *
 * HostNr
 *     The number of the host (0..H) for which to control the access to
 *     MailboxNr.
 *
 * fAccessAllowed
 *     true   Allow HostNr to link and use MailboxNr.
 *     false  Do not allow HostNr to link and use MailboxNr.
 *
 * Return Value:
 *     0    Success
 *     <0   Error code:
 *     -1   Invalid mailbox number
 *     -2   Invalid host number
 */
Eip130FunctionStatus_t
EIP130_MailboxAccessControl(
        Device_Handle_t Device,
        uint8_t MailboxNr,
        uint8_t HostNr,
        bool fAccessAllowed);
#endif


/*----------------------------------------------------------------------------
 * EIP130_MailboxLink
 *
 * This function tries to link the requested mailbox. Upon success the mailbox
 * can be used until unlinked. A mailbox can only be linked by this host when
 * access has been granted by the Master CPU.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * MailboxNr
 *     The mailbox number to write this token to (1..4).
 *     The mailbox must be linked to this host.
 *
 * Return Value:
 *     0    Success
 *     <0   Error code:
 *     -1   Invalid mailbox number
 *     -2   Not link (linking failed)
 */
Eip130FunctionStatus_t
EIP130_MailboxLink(
        Device_Handle_t Device,
        const uint8_t MailboxNr);


/*----------------------------------------------------------------------------
 * EIP130_MailboxUnlink
 *
 * This function unlinks a previously linked mailbox.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * MailboxNr
 *     The mailbox number to write this token to (1..4).
 *     The mailbox must be linked to this host.
 *
 * Return Value:
 *     0    Success
 *     <0   Error code:
 *     -1   Invalid mailbox number
 *     -2   Still linked (unlinking failed)
 */
Eip130FunctionStatus_t
EIP130_MailboxUnlink(
        Device_Handle_t Device,
        const uint8_t MailboxNr);


/*----------------------------------------------------------------------------
 * EIP130_MailboxLinkReset
 *
 * This function resets a linked mailbox (forced unlinking).
 * Note: This function can only be called by the master host.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * MailboxNr
 *     The mailbox number to write this token to (1..4).
 *     The mailbox must be linked to this host.
 *
 * Return Value:
 *     0    Success
 *     <0   Error code:
 *     -1   Invalid mailbox number
 *     -2   Still linked (link reset failed)
 */
Eip130FunctionStatus_t
EIP130_MailboxLinkReset(
        Device_Handle_t Device,
        const uint8_t MailboxNr);


/*----------------------------------------------------------------------------
 * EIP130_MailboxCanReadToken/WriteToken
 *
 * CanWriteToken returns 'true' when a new command token may be written to the
 * mailbox of the EIP130 Security Module using one of the WriteToken functions.
 * CanReadToken returns 'true' when a result token can be read from the
 * mailbox of the EIP130 Security Module using one of the ReadToken functions.
 * This functions are fully re-entrant and thread-safe.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * MailboxNr
 *     The mailbox number to write this token to (1..4).
 *     The mailbox must be linked to this host.
 *
 * ModuleStatus
 *     A optional pointer to a variable that holds the ModuleStatus on return.
 *     This ModuleStatus can be used to detect EIP-130 fatal error situations.
 *
 * Return Value
 *     true   Token can be written/read
 *     false  Token canNOT be written/read
 */
bool
EIP130_MailboxCanWriteToken(
        Device_Handle_t Device,
        const uint8_t MailboxNr,
        Eip130RegisterWord_t * const ModuleStatus);

bool
EIP130_MailboxCanReadToken(
        Device_Handle_t Device,
        const uint8_t MailboxNr);


/*----------------------------------------------------------------------------
 * EIP130_MailboxWriteAndSubmitToken
 *
 * This function writes the token to the IN mailbox and then hands off the
 * mailbox to the SM to start processing the token. The request fails when the
 * mailbox is full or not linked to this host.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * MailboxNr
 *     The mailbox number to write this token to (1..4).
 *     The mailbox must be linked to this host.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * fDoCanWriteCheck
 *     Indication to do the can write token check (EIP130_MailboxCanWriteToken).
 *
 * Return Value
 *     0    Success
 *     <0   Error code:
 *     -1   Invalid mailbox number
 *     -2   Invalid CommandToken buffer specified
 *     -3   Token cannot be written
 *     -4   Token handover failed - Check if HW is active
 */
Eip130FunctionStatus_t
EIP130_MailboxWriteAndSubmitToken(
        Device_Handle_t Device,
        const uint8_t MailboxNr,
        const Eip130Token_Command_t * const CommandToken_p,
        const bool fDoCanWriteCheck);


/*----------------------------------------------------------------------------
 * EIP130_MailboxReadToken
 *
 * This function reads the token from the OUT mailbox and then frees the
 * mailbox, allowing the SM to write another result in it.
 * The request fails when the mailbox is empty or the token is not for this
 * host.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * MailboxNr
 *     The mailbox number to write this token to (1..4).
 *     The mailbox must be linked to this host.
 *
 * ResultToken_p
 *     Pointer to the result token buffer this function will write to.
 *
 * Return Value
 *     0    Success
 *     <0   Error code:
 *     -1   Invalid mailbox number
 *     -2   Invalid ResultToken buffer specified
 *     -3   Token cannot be read
 */
Eip130FunctionStatus_t
EIP130_MailboxReadToken(
        Device_Handle_t Device,
        const uint8_t MailboxNr,
        Eip130Token_Result_t * const ResultToken_p);


/*----------------------------------------------------------------------------
 * EIP130_FirmwareCheck
 *
 * This function checks if firmware needs to be loaded.
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * Return Value
 *     3    Firmware is ready for use
 *     2    Firmware checks are still busy
 *     1    Firmware image load required
 *     0    Firmware (token & image) needs to be loaded
 *     <0   Error code:
 *     -1   Not supported - Check if HW is active
 *     -2   This Host is NOT allowed to do the download
 *     -3   Hardware error
 *     -4   Hardware/Firmware state error
 */
Eip130FunctionStatus_t
EIP130_FirmwareCheck(
        Device_Handle_t Device);


/*----------------------------------------------------------------------------
 * EIP130_FirmwareLoad
 *
 * This function first checks if the firmware needs to be loaded. If that is
 * the case it writes the appropriate firmware image parts to the mailbox and
 * FWRAM and waits till the firmware has been accepted (and thus started).
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * MailboxNr
 *     The mailbox number to use for the RAM-based Firmware Code Validation
 *     and Boot token. Note mailbox will be unlink after function return.
 *
 * Firmware_p
 *     Pointer to the buffer that holds the firmware image.
 *
 * FirmwareWord32Size
 *     The size of the firmware image in 32-bit words.
 *
 * Return Value
 *     0    Firmware load and accepted (started)
 *     <0   Error code:
 *     -1   Not supported - Check if HW is active
 *     -2   This Host is NOT allowed to do the download
 *     -3   Firmware checks done timeout - Check if HW is active
 *     -4   Firmware load failed (multiple times)
 *     -5   Hardware error
 */
Eip130FunctionStatus_t
EIP130_FirmwareLoad(
        Device_Handle_t Device,
        const uint8_t MailboxNr,
        const uint32_t * const Firmware_p,
        const uint32_t FirmwareWord32Size);


/*----------------------------------------------------------------------------
 * EIP130_FirmwareLogin
 *
 * This function performs a firmware login. The objective of the firmware
 * login to be compliant with the FIPS140-3 requirement that operations in
 * �FIPS-Approved mode� can only be invoked by an authenticated user (or role).
 * The firmware login must be performed after each reset (hardware or firmware)
 * or power-cycle before another Token can be used. However, the following
 * Tokens can be used without a prior firmware login:
 * - SystemInfo
 * - Reset
 * - Static Asset Search
 * - Public Data Read
 * - Monotonic Counter Read
 * - Register Read / Write
 * - Resume from Sleep
 *
 * Device
 *     The Driver Framework Device Handle for the EIP-130.
 *
 * MailboxNr
 *     The mailbox number to use for the firmware login token. Note mailbox
 *     will be unlink after function return.
 *
 * Identity
 *      A 32-bit value to identify the user.
 *
 * fUnlinkMailbox
 *     true   Unlink the mailbox after the firmware login command.
 *     false  Keep the mailbox in the linked state.
 *
 * Return Value
 *     0    Successful firmware login
 *     <0   Error code:
 *     -1   Invalid mailbox number
 *     -2   Not link (linking failed)
 *     -3   Token cannot be written
 *     -4   Token handover failed - Check if HW is active
 *     -5   Result token timeout
 *     -7   Access error
 *     -18  Verify error
 */
Eip130FunctionStatus_t
EIP130_FirmwareLogin(
        Device_Handle_t Device,
        const uint8_t MailboxNr,
        const uint32_t Identity,
        const bool fUnlinkMailbox);


#endif /* INCLUDE_GUARD_EIP130_H */

/* end of file eip130.h */
