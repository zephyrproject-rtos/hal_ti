/* HSMSAL.c
 *
 * Implementation of the HSMSAL API.
 *
 * This file contains the logical token exchange implementation between the
 * HSMLPF3 and VEX API.
 */

/*
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <third_party/hsmddk/include/Integration/HSMSAL/HSMSAL.h>            // API to implement

#include <third_party/hsmddk/include/Kit/EIP130/MailboxControl/incl/eip130.h>
#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_internal.h>
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_interrupts.h>
#include <third_party/hsmddk/include/Integration/Adapter_DriverInit/incl/api_driver_init.h>

/*----------------------------------------------------------------------------
 * HSMSAL_Init
 *      Makes call to Driver130_init() mainly to unify all calls under the HSMSAL umbrella
 */
HSMSALStatus_t
HSMSAL_Init(void)
{
    return (HSMSALStatus_t)Driver130_Init();
}

/*----------------------------------------------------------------------------
 * HSMSAL_setCryptoOfficerID
 */
void
HSMSAL_setCryptoOfficerID(uint32_t crypto_officer_id)
{
    vex_IdentityCryptoOfficer(crypto_officer_id);
}

/*----------------------------------------------------------------------------
 * HSMSAL_getCryptoOfficerID
 */
uint32_t
HSMSAL_getCryptoOfficerID()
{
    return vex_IdentityGet();
}

/*----------------------------------------------------------------------------
 * HSMSAL_ConvertVexCodeToSAL
 *      Converts VexStatus_t return code type to HSMSALStatus_t code type
 */
static HSMSALStatus_t
HSMSAL_ConvertVexCodeToSAL(VexStatus_t VexStatus)
{
    return (HSMSALStatus_t)VexStatus;
}

/*----------------------------------------------------------------------------
 * HSMSAL_SubmitPhysicalToken
 *      Accepts an EIP130 Command Token, and deposits it to the HW directly
 */
HSMSALStatus_t
HSMSAL_SubmitPhysicalToken(const Eip130Token_Command_t * const CommandToken_p)
{
    return HSMSAL_ConvertVexCodeToSAL(vex_PhysicalTokenExchange((Eip130Token_Command_t *)CommandToken_p, NULL));
}

/*----------------------------------------------------------------------------
 * HSMSAL_ScanAndReadMailbox
 */
HSMSALStatus_t
HSMSAL_ScanAndReadMailbox(Eip130Token_Result_t * const ResultToken_p, const uint8_t MailboxNumber)
{
    HSMSALStatus_t funcres = HSMSAL_INTERNAL_ERROR;
    Device_Handle_t Device = vex_DeviceGetHandle();
    int32_t sourcesEnabled;
    int32_t mailboxIRQOffset;

    if (EIP130_MailboxCanReadToken(Device, MailboxNumber))
    {
        /* Check which AIC interrupts have been triggered. */
        sourcesEnabled = HSMSAL_GetEIP201InterruptStatus();
        mailboxIRQOffset = ((MailboxNumber * 2U) - 1U);

        if (sourcesEnabled & (1 << mailboxIRQOffset))
        {
            /* Clear and disable the mailbox-specific interrupt */
            HSMSAL_ClearAndDisableEIP201Interrupt(mailboxIRQOffset);

            /* Read the Mailbox's out buffer into the result token */
            (void)EIP130_MailboxReadToken(Device, MailboxNumber, ResultToken_p);

            funcres = HSMSAL_SUCCESS;
        }
        else
        {
            funcres = HSMSAL_BAD_ARGUMENT;
        }
    }
    else
    {
        funcres = HSMSAL_MAILBOX_IN_USE;
    }
    return funcres;
}

/*----------------------------------------------------------------------------
 * HSMSAL_GetMailBoxNumber
 *
 * This function looks into the available mailboxes and the identity of the process
 *     called and returns the appropriate mailbox to use for token deposits
 */
uint8_t
HSMSAL_GetMailBoxNumber()
{
    return vex_MailboxGet(vex_IdentityGet());
}

/*----------------------------------------------------------------------------
 * HSMSAL_WaitForResultPolling
 *     Populates the result token in polling mode
 */
HSMSALStatus_t
HSMSAL_WaitForResultPolling(Eip130Token_Result_t * const ResultToken_p)
{
    HSMSALStatus_t funcres = HSMSAL_RESPONSE_TIMEOUT;
    uint8_t MailboxNumber  = HSMSAL_GetMailBoxNumber();
    int32_t LoopsLeft      = HSMSAL_POLLING_LOOPS;

    /* Poll for output token available without sleep */
    while (LoopsLeft > 0)
    {
        if(HSMSAL_ScanAndReadMailbox(ResultToken_p, MailboxNumber) == HSMSAL_SUCCESS)
        {
            break;
        }
        LoopsLeft--;
    }

    if (LoopsLeft > 0)
    {
        funcres = HSMSAL_SUCCESS;
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * HSMSAL_GetEIP201InterruptStatus
 *     Returns the AIC Enabled Status Register
 */
int32_t
HSMSAL_GetEIP201InterruptStatus()
{
    return Adapter_Interrupt_Ext_Status();
}

/*----------------------------------------------------------------------------
 * HSMSAL_ClearEIP201Interrupt
 *     This function handles clearing a specific IRQ raised by the EIP201 engine
 */
HSMSALStatus_t
HSMSAL_ClearEIP201Interrupt(const int32_t nIRQ)
{
    return HSMSAL_ConvertVexCodeToSAL(Adapter_Interrupt_Clear(nIRQ, 0U));
}

/*----------------------------------------------------------------------------
 * HSMSAL_ClearAndDisableEIP201Interrupt
 *     This function handles clearing and disabling specific IRQ raised by the EIP201 engine
 */
HSMSALStatus_t
HSMSAL_ClearAndDisableEIP201Interrupt(const int32_t nIRQ)
{
    HSMSALStatus_t funcres = HSMSAL_INTERNAL_ERROR;

    /* First, try to clear the interrupt */
    funcres = HSMSAL_ConvertVexCodeToSAL(Adapter_Interrupt_Clear(nIRQ, 0U));

    if (funcres == HSMSAL_SUCCESS)
    {
        /* Second, try to disable the interrupt */
        funcres = HSMSAL_ConvertVexCodeToSAL(Adapter_Interrupt_Disable(nIRQ, 0U));
    }

    return funcres;
}