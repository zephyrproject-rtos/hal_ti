/* HSMSAL.h
 *
 * The HSMSAL API.
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

#ifndef INCLUDE_GUARD_HSMSAL_H
#define INCLUDE_GUARD_HSMSAL_H

#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>
#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_internal.h>

#define HSMSAL_MAILBOX_NR VEX_MAILBOX_NR

#define HSMSAL_POLLING_LOOPS VEX_POLLING_MAXLOOPS*VEX_POLLING_MAXLOOPS*VEX_POLLING_SKIP_FIRST_DELAYS

/*----------------------------------------------------------------------------
 * HSMSALStatus_t
 */
typedef int32_t HSMSALStatus_t;

/* Retuned Status codes */
#define HSMSAL_SUCCESS                 (0)     /* Operation success */
#define HSMSAL_UNSUPPORTED             (-1)    /* Not supported */
#define HSMSAL_NOT_CONNECTED           (-2)    /* No connection with HW available */
#define HSMSAL_POWER_STATE_ERROR       (-3)    /* Device writes (unexpectly) did not work */
#define HSMSAL_OPERATION_NOT_ALLOWED   (-4)    /* The host is not allowed to do this operation */
#define HSMSAL_OPERATION_FAILED        (-5)    /* Operation failed */
#define HSMSAL_INVALID_OPCODE          (-6)    /* Invalid parameter */
#define HSMSAL_INVALID_SUBCODE         (-7)    /* Invalid parameter */
#define HSMSAL_INVALID_LENGTH          (-8)    /* Invalid length */
#define HSMSAL_BAD_ARGUMENT            (-9)    /* Wrong use; not depending on configuration */
#define HSMSAL_NO_MEMORY               (-10)   /* No memory */
#define HSMSAL_NO_IDENTITY             (-11)   /* No identity */
#define HSMSAL_NO_MAILBOX              (-12)   /* No mailbox */
#define HSMSAL_MAILBOX_IN_USE          (-13)   /* Mailbox is in use */
#define HSMSAL_RESPONSE_TIMEOUT        (-14)   /* Output token response timeout */
#define HSMSAL_DATA_TIMEOUT            (-15)   /* Data ready check timeout */
#define HSMSAL_DATA_MAPPING_ERROR      (-16)   /* Data mapping error */
#define HSMSAL_LOCK_TIMEOUT            (-17)   /* Output token response timeout */
#define HSMSAL_TOKEN_TIMEOUT           (-18)   /* Input token processing timeout */
#define HSMSAL_INTERNAL_ERROR          (-19)   /* Internal error */

/*----------------------------------------------------------------------------
 * HSMSAL_Init
 *
 * An HSMSAL wrapper around Driver130_init()
 *
 * Return Value:
 *     One of the HSMSALStatus_t values.
 */
HSMSALStatus_t
HSMSAL_Init(void);

/*----------------------------------------------------------------------------
 * HSMSAL_setCryptoOfficerID
 *
 * This function sets the crypto officer ID.
 *
 * crypto_officer_id
 *     The crypto officer ID that was set during HUK provisioning
 */
void
HSMSAL_setCryptoOfficerID(uint32_t crypto_officer_id);

/*----------------------------------------------------------------------------
 * HSMSAL_getCryptoOfficerID
 *
 * This function gets the crypto officer ID.
 *
 * Return Value:
 *     The Crypto Officer ID.
 */
uint32_t
HSMSAL_getCryptoOfficerID();

/*----------------------------------------------------------------------------
 * HSMSAL_SubmitPhysicalToken
 *
 * This function handles EIP130 command tokens coming from the HSMLPF3 Utility Driver and
 *     passes them to the physical exchange layer and eventually the EIP130 engine.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request (CommandToken).
 *
 * Return Value:
 *     One of the HSMSALStatus_t values.
 */
HSMSALStatus_t
HSMSAL_SubmitPhysicalToken(const Eip130Token_Command_t * const CommandToken_p);

/*----------------------------------------------------------------------------
 * HSMSAL_GetMailBoxNumber
 *
 * This function looks into the available mailboxes and the identity of the process
 *     called and returns the appropriate mailbox to use for token deposits
 *
 * Return Value:
 *     The Mailbox number a process should use.
 */
uint8_t
HSMSAL_GetMailBoxNumber();

/*----------------------------------------------------------------------------
 * HSMSAL_ScanAndReadMailbox
 *
 * This function scans a specific mailbox and reads its content to populate
 *      a result token if said mailbox can be read from.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result (ResultToken) needs
 *     to be returned.
 *
 * mailbox_num
 *     Mailbox number to scan and read results from.
 *
 * Return Value:
 *     One of the HSMSALStatus_t values.
 */
HSMSALStatus_t
HSMSAL_ScanAndReadMailbox(Eip130Token_Result_t * const ResultToken_p, const uint8_t MailboxNumber);

/*----------------------------------------------------------------------------
 * HSMSAL_WaitForResultPolling
 *
 * This function populates the result token in polling mode.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result (ResultToken) needs
 *     to be returned.
 *
 * Return Value:
 *     One of the HSMSALStatus_t values.
 */
HSMSALStatus_t
HSMSAL_WaitForResultPolling(Eip130Token_Result_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * HSMSAL_GetEIP201InterruptStatus
 *
 * This function returns returns the AIC Enabled Status Register
 *
 * Return Value:
 *     a 32-bit interrupts register status value.
 */
int32_t
HSMSAL_GetEIP201InterruptStatus();

/*----------------------------------------------------------------------------
 * HSMSAL_ClearEIP201Interrupt
 *
 * This function handles clearing a specific IRQ raised by the EIP201 engine
 *
 * nIRQ number
 *     irq number
 *
 * Return Value:
 *     One of the HSMSALStatus_t values.
 */
HSMSALStatus_t
HSMSAL_ClearEIP201Interrupt(const int32_t nIRQ);

/*----------------------------------------------------------------------------
 * HSMSAL_ClearAndDisableEIP201Interrupt
 *
 * This function handles clearing and disabling specific IRQ raised by the EIP201 engine
 *
 * nIRQ number
 *     irq number
 *
 * Return Value:
 *     One of the HSMSALStatus_t values.
 */
HSMSALStatus_t
HSMSAL_ClearAndDisableEIP201Interrupt(const int32_t nIRQ);

#endif /* INCLUDE_GUARD_HSMSAL_H */

/* end of file HSMSAL.h */