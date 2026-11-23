/*
 * Copyright (c) 2024, Texas Instruments Incorporated
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
/*-----------------------------------------------------------------------------

  FILENAME:       cme_fw_api.h

  DESCRIPTION:    This files defines the APIs between CME and FW (wlan services)
                  In general, according to the invoked API, CME pushes a message
                  to its queue in order to preempt CME context so events are
                  handled from CME context.

  HISTORY:
                 07/15 - Creation

  ----------------------------------------------------------------------------- */
#ifndef _CME_FW_API_H_
#define _CME_FW_API_H_

#include <osi_kernel.h>

// ============================================================================
//	Exported Type Definitions
// ============================================================================

// ============================================================================
//	CME exported Functions
// ============================================================================

// ----------------------------------------------------------------------------
int32_t CME_NotifyRxMngPack(void *aDesc);

// ----------------------------------------------------------------------------
int32_t CME_ChannelSwitchAnnounceNotify(uint32_t aRoleId, uint8_t channel, uint8_t count, Bool32 block_tx);

// ----------------------------------------------------------------------------
int32_t CME_ChannelSwitchDone(uint32_t aRoleId);

// ----------------------------------------------------------------------------
int32_t CME_RxEapol(void *aDesc);

//-----------------------------------------------------------------------------
int32_t CME_RxFromUnknown(void *aDesc, uint32_t aRoleId);

//-----------------------------------------------------------------------------
int32_t CME_RxFromUnknownData(void *aDesc);

//-----------------------------------------------------------------------------
int32_t CME_RemainOnChannelTimeoutNotify(uint32_t aRoleId);

// ----------------------------------------------------------------------------
int32_t CME_NotifyMicFailure(void *aDesc);

// ----------------------------------------------------------------------------
int32_t CME_PnReplayDetected(void *aDesc);

// ----------------------------------------------------------------------------
int32_t CME_unprotDeAuthAssocDetected(void *aDesc, uint32_t aRoleId);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
int32_t CME_AesSwDecryptionNeeded(uint32_t aDescriptorId);

// ----------------------------------------------------------------------------
int32_t CME_BssLoss(uint32_t aRoleId);

// ----------------------------------------------------------------------------
int32_t CME_StaDisconnect(uint32_t aRoleId);

// ----------------------------------------------------------------------------
int32_t CME_EapolTxResult(void *desc);

// ----------------------------------------------------------------------------
int32_t CME_TxResult(void *desc);

// ----------------------------------------------------------------------------
int32_t CME_MaxTxFailure(uint32_t aRoleId, uint16_t aInactiveLinksBits);

// ----------------------------------------------------------------------------
int32_t CME_SetInactiveSta(uint32_t aRoleId, uint16_t aInactiveLinksBits);

// ------------------------------
// TODO remove due to compilattion----------------------------------------------
//void CME_supplicantPeriodicTimeoutCB(TimerEventInfo_t   * timerElement);

// ----------------------------------------------------------------------------

int32_t cme_init();

int32_t cme_deinit();


#endif // _CME_FW_API_H_
