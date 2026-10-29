/* adapter_vex_internal.h
 *
 * VEX API: Internal interfaces and definitions.
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

#ifndef INCLUDE_GUARD_ADAPTER_VEX_INTERNAL_H
#define INCLUDE_GUARD_ADAPTER_VEX_INTERNAL_H

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>            // VexTokenCmd_*_t, VexToken_*_t
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    // Eip130Token_Command/Result_t
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_types.h>           // Device_Handle_t

// Device power states
#define VEX_DEVICE_POWER_UNKNOWN        0
#define VEX_DEVICE_POWER_ACTIVE         1
#define VEX_DEVICE_POWER_SLEEP          2


#ifdef VEX_ENABLE_SF_MILENAGE
/*----------------------------------------------------------------------------
 * vex_ConvertFromUint8ToBool
 */
bool
vex_ConvertFromUint8ToBool(const uint8_t input);
#endif


/*----------------------------------------------------------------------------
 * vex_ConvertFromUint32ToBool
 */
bool
vex_ConvertFromUint32ToBool(const uint32_t input);


/*----------------------------------------------------------------------------
 * vex_InitBufManager
 *
 * This function installs the callback functions for the BufManager.
 *
 * Return Value:
 *     Not applicable.
 */
void
vex_InitBufManager(void);

/*----------------------------------------------------------------------------
 * vex_Nop
 *
 * This function handles the NOP based token.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_Nop(
        const VexTokenCmd_Nop_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * vex_SymCipher
 *
 * This function handles the Symmetric Crypto Cipher based token.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_SymCipher(
        const VexTokenCmd_Cipher_t * const CommandToken_p,
        VexTokenRslt_Cipher_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * vex_SymCipher_PostProcessing
 *
 * This function handles the interpreting the physical token and populating the logical token accordingly
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * ResultTokenP_p
 *     Pointer to the buffer where the physical result token
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_SymCipher_PostProcessing(
        const VexTokenCmd_Cipher_t * const CommandToken_p,
        VexTokenRslt_Cipher_t * const ResultToken_p,
        const Eip130Token_Result_t * const ResultTokenP_p);

/*----------------------------------------------------------------------------
 * vex_SymCipherAE
 *
 * This function handles the Authenticated Symmetric Crypto Cipher based token.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_SymCipherAE(
        const VexTokenCmd_CipherAE_t * const CommandToken_p,
        VexTokenRslt_CipherAE_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * vex_SymCipherAE_PostProcessing
 *
 * This function handles the interpreting the physical token and populating the logical token accordingly
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * ResultTokenP_p
 *     Pointer to the buffer where the physical result token
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_SymCipherAE_PostProcessing(const VexTokenCmd_CipherAE_t * const CommandToken_p,
                               VexTokenRslt_CipherAE_t * const ResultToken_p,
                               const Eip130Token_Result_t * const ResultTokenP_p);

/*----------------------------------------------------------------------------
 * vex_SymHash
 *
 * This function handles the Symmetric Crypto Hash based token.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_SymHash(
        const VexTokenCmd_Hash_t * const CommandToken_p,
        VexTokenRslt_Hash_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * vex_SymHash
 */
VexStatus_t
vex_SymHash_PostProcessing(
        const VexTokenCmd_Hash_t * const CommandToken_p,
        VexTokenRslt_Hash_t * const ResultToken_p,
        const Eip130Token_Result_t * const ResultTokenP);

/*----------------------------------------------------------------------------
 * vex_SymMac
 *
 * This function handles the Symmetric Crypto MAC based token.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_SymMac(
        const VexTokenCmd_Mac_t * const CommandToken_p,
        VexTokenRslt_Mac_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * vex_SymMac_PostProcessing
 *
 * This function handles the Symmetric Crypto MAC based token.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_SymMac_PostProcessing(const VexTokenCmd_Mac_t * const CommandToken_p,
                          VexTokenRslt_Mac_t * const ResultToken_p,
                          const Eip130Token_Result_t * const ResultTokenP_p);

/*----------------------------------------------------------------------------
 * vex_SymKeyWrap
 *
 * This function handles the Symmetric Crypto key wrap token.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_SymKeyWrap(
        const VexTokenCmd_KeyWrap_t * const CommandToken_p,
        VexTokenRslt_KeyWrap_t * const ResultToken_p);


/*----------------------------------------------------------------------------
 * vex_Trng
 *
 * This function handles the TRNG based token.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_Trng(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * vex_Trng_PostProcessing
 *
 * This function handles the interpreting the physical token and populating the logical token accordingly
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * ResultTokenP_p
 *     Pointer to the buffer where the physical result token
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_Trng_PostProcessing(const VexTokenCmd_Generic_t * const CommandToken_p,
                          VexTokenRslt_Generic_t * const ResultToken_p,
                          const Eip130Token_Result_t * const ResultTokenP_p);

/*----------------------------------------------------------------------------
 * vex_Asset
 *
 * This function handles the Asset Management based tokens.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_Asset(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * vex_Asset_PostProcessing
 *
 * This function handles the interpreting the physical token and populating the logical token accordingly
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * ResultTokenP_p
 *     Pointer to the buffer where the physical result token
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_Asset_PostProcessing(const VexTokenCmd_Generic_t * const CommandToken_p,
                         VexTokenRslt_Generic_t * const ResultToken_p,
                         const Eip130Token_Result_t * const ResultTokenP_p);

/*----------------------------------------------------------------------------
 * vex_Asym
 *
 * This function handles the Asymmetric Crypto based tokens.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_Asym(const VexTokenCmd_Generic_t * const CommandToken_p,
         VexTokenRslt_Generic_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * vex_Asym_PostProcessing
 *
 * This function handles the Asymmetric Crypto based tokens.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * ResultTokenP_p
 *     Pointer to the buffer where the physical result token
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_Asym_PostProcessing(const VexTokenCmd_Generic_t * const CommandToken_p,
                        VexTokenRslt_Generic_t * const ResultToken_p,
                        const Eip130Token_Result_t * const ResultTokenP_p);

/*----------------------------------------------------------------------------
 * vex_AUnlock
 *
 * This function handles the Authenticated Unlock based tokens.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_AUnlock(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p);

#ifdef VEX_ENABLE_SF
/*----------------------------------------------------------------------------
 * vex_SpecialFunctions
 *
 * This function handles the Special Functions based tokens.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_SpecialFunctions(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p);
#endif

/*----------------------------------------------------------------------------
 * vex_Service
 *
 * This function handles the Service based tokens.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_Service(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * vex_System
 *
 * This function handles the System based tokens.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_System(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * vex_Hardware
 *
 * This function handles the services that are hardware related.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_Hardware(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * vex_Claim
 *
 * This function handles the services with which the exclusive mailbox locking
 * can be controlled.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_Claim(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p);


/*----------------------------------------------------------------------------
 * vex_PhysicalTokenExchange
 *
 * This function exchanges the physical tokens with the EIP-130 hardware.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result needs to be returned.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_PhysicalTokenExchange(
        Eip130Token_Command_t * const CommandToken_p,
        Eip130Token_Result_t * const ResultToken_p);


/*----------------------------------------------------------------------------
 * vex_DeviceInit
 *
 * This function initializes the connection to the device hardware.
 *
 * Return Value:
 *      0 : Successful.
 *     -1 : Could not find device.
 *     -2 : Could not retrieve device information.
 *     -3 : Firmware acquiring failed.
 *     -4 : Firmware load failed.
 *     -5 : Firmware use issue.
 *     -6 : Mailbox linking failed.
 *     -7 : OUT mailbox is unexpectedly FULL.
 *     -8 : IN mailbox is unexpectedly FULL.
 *     -9 : Access or verify error occured of firmware login.
 *   -100 : Lock acquire failed.
 */
int32_t
vex_DeviceInit(void);

/*----------------------------------------------------------------------------
 * vex_DeviceExit
 *
 * This function releases the connection with the device hardware.
 *
 * Return Value:
 *      Not applicable.
 */
void
vex_DeviceExit(void);

/*----------------------------------------------------------------------------
 * vex_DeviceGetHandle
 *
 * This function provides the device handle, if available.
 *
 * Return Value:
 *      The device handle.
 *      Note that NULL means not available.
 */
Device_Handle_t
vex_DeviceGetHandle(void);

/*----------------------------------------------------------------------------
 * vex_DeviceIsSecureConnected
 *
 * This function returns the secure connection state.
 * Note this means that the host has its protection set when accessing the
 * device registers and mailboxes.
 *
 * Return Value:
 *      true  : Device handle is available and protection set when accessing
 *              the device.
 *      false : Not connected (or device handle not available).
 */
bool
vex_DeviceIsSecureConnected(void);

/*----------------------------------------------------------------------------
 * vex_DeviceStateIssue
 *
 * This function must be called when a device connection/state issue is
 * detected. The device/firmware will be re-initialized automatically if a
 * service is requested and the device connection/state issue is solved.
 *
 * Return Value:
 *      N/A
 */
void
vex_DeviceStateIssue(void);

/*----------------------------------------------------------------------------
 * vex_DeviceMailboxes
 *
 * This function returns the number of mailboxes.
 *
 * Return Value: Number of mailboxes
 */
uint8_t
vex_DeviceMailboxes(void);

/*----------------------------------------------------------------------------
 * vex_DeviceLinkMailbox
 *
 * This function links a mailbox.
 *
 * MailboxNr
 *     Number of the mailbox to link.
 *
 * Identity
 *     Identity of calling process to claim mailbox.
 *
 * Return Value:
 *      0 : Successful.
 *     -1 : No device connection.
 *     -2 : Invalid mailbox number.
 *     -3 : Mailbox linking failed.
 *     -4 : Mailbox already linked by another process.
 */
int32_t
vex_DeviceLinkMailbox(
           const uint8_t MailboxNr,
           uint32_t Identity);

/*----------------------------------------------------------------------------
 * vex_DeviceLinkMailboxOverrule
 *
 * This function overrules a mailbox identity link.
 *
 * MailboxNr
 *     Number of the mailbox to link.
 *
 * Identity
 *     Identity of calling process to claim mailbox.
 *
 * Return Value:
 *      0 : Successful.
 *     -1 : No device connection.
 *     -2 : Invalid mailbox number.
 *     -3 : Mailbox linking failed.
 *     -4 : Mailbox already linked by another process.
 */
int32_t
vex_DeviceLinkMailboxOverrule(
           const uint8_t MailboxNr,
           uint32_t Identity);

/*----------------------------------------------------------------------------
 * vex_DeviceUnlinkMailbox
 *
 * This function unlinks a mailbox.
 *
 * MailboxNr
 *     Number of the mailbox to link.
 *
 * Identity
 *     Identity of calling process to release mailbox.
 *
 * Return Value:
 *      0 : Successful.
 *     -1 : No device connection.
 *     -2 : Invalid mailbox number.
 *     -3 : Mailbox unlinking failed.
 *     -4 : Not allowed to unlink the mailbox that is locked by another process
 */
int32_t
vex_DeviceUnlinkMailbox(
           const uint8_t MailboxNr,
           uint32_t Identity);

/*----------------------------------------------------------------------------
 * vex_DeviceGetTokenID
 *
 * This function return a unique token id since startup.
 *
 * Return Value:
 *     A unique token id.
 */
uint16_t
vex_DeviceGetTokenID(void);

/*----------------------------------------------------------------------------
 * vex_DeviceSleep
 *
 * This function puts the device in Sleep mode after first checking that the
 * firmware is accepted and the calling process is on the master host. If that
 * is the case it writes the Sleep token and waits for the result token.
 *
 * Return Value
 *     0      Firmware is set in Sleep mode
 *     <0     VEX eError code:
 *     <-256  Firmware error from token
 */
VexStatus_t
vex_DeviceSleep(void);

/*----------------------------------------------------------------------------
 * vex_DeviceResumeFromSleep
 *
 * This function resumes the device that is Sleep mode to active state after
 * checking that the firmware is in the correct state and the calling process
 * is on the master host. If that is the case it writes the Resume from Sleep
 * token and waits for the result token.
 *
 * Return Value
 *     0      Firmware is in active (usable) state
 *     <0     VEX eError code:
 *     <-256  Firmware error from token
 */
VexStatus_t
vex_DeviceResumeFromSleep(void);


/*----------------------------------------------------------------------------
 * vex_MailboxGet
 *
 * This function returns the mailbox number to use after verifying/linking
 * the mailbox first.
 *
 * Identity
 *     Identity of calling process.
 *
 * Return Value:
 *     1..8 : Mailbox to use.
 *        0 : Invalid mailbox or mailbox linking failed.
 */
uint8_t
vex_MailboxGet(
        uint32_t Identity);

/*----------------------------------------------------------------------------
 * vex_IdentityCryptoOfficer
 *
 * This function sets the identity of the Crypto Officer
 * Officer.
 *
 * CryptoOfficerId
 *     Identity of the Crypto Officer.
 *
 * Return Value:
 *     -
 */
void
vex_IdentityCryptoOfficer(
        uint32_t CryptoOfficerId);

/*----------------------------------------------------------------------------
 * vex_IdentityGet
 *
 * This function returns identity to use.
 *
 * Return Value:
 *     The identity to use.
 */
uint32_t
vex_IdentityGet(void);


/*----------------------------------------------------------------------------
 * VexCleanup_t
 */
typedef void (*VexCleanup_t)(void * pContext);


#endif /* INCLUDE_GUARD_ADAPTER_VEX_INTERNAL_H */

/* end of file adapter_vex_internal.h */
