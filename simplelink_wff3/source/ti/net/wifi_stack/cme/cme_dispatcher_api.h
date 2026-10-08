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

  FILENAME:       cme_dispatcher_api.h

  DESCRIPTION:    This files defines the API between CME and SL dispatcher

  HISTORY:
                 04/15 Creation

  ----------------------------------------------------------------------------- */
#ifndef _CME_API_H_
#define _CME_API_H_

#include "cme_common.h"

/*=============================================================================
	Exported Type Definitions
=============================================================================*/
#define ID_AND_OPTION(ID, OPTION) (((0xFFFF & (OPTION)) <<16) | (0xFFFF & (ID)))
// ============================================================================
//	Exported Functions
// ============================================================================

/* ----------------------------------------------------------------------------
 CME_fastConnectTimerRelease
      This function pushes a message with fast connection timeout notifier to the
      queue.
      this command is asking the CME to release the timer resources as it is called from timer context.
 Parameters:
 Return code:
---------------------------------------------------------------------------- */
void CME_fastConnectTimerRelease();
/* ----------------------------------------------------------------------------
 CME_SuppDeinit
      this command is asking the CME to deinit the wpa_supplicant.

 Parameters:
 Return code:
---------------------------------------------------------------------------- */
void CME_SuppDeinit(uint32_t timeout);
/* ----------------------------------------------------------------------------
 CME_GetScanResults
      This function pushes a message with site survey request into CME message
      queue.
      As this command may trigger scan, results are sent to host asynchronously.
 Parameters: 	aIndex - index of the first result to fetch
 	 	 	    aCount - number of results to fetch
 	 	 	    aGetInternalEvent - if set, send event as internal event to host. Otherwise,
 	 	 	    send asynchronous user event.
 	 	 	    aExtraBytes - offset from buffer header, shall be filled with dispatcher info
 	 	 	    apNumNetworks - number of detected networks
 	 	 	    apNumBytes - number of bytes to send (including the dispatcher extra info bytes)
 	 	 	    scanCommon - parameters for the scan like ssid
 Return code:	pointer to results buffer.
---------------------------------------------------------------------------- */
int32_t CME_GetScanResults(uint32_t aIndex, uint32_t aCount, uint8_t aGetInternalEvent, CMEWlanScanCommon_t* pScanCommon);

/* ----------------------------------------------------------------------------
 CME_WlanSetMode
      This function pushes a message with new role set bitmap into
      CME message queue.
      early exit point without pushing a message to the queue in case requested
      role bitamp is already configured.
 Parameters:    bitmask reflecting new roles state, see role definitions in
                sl_protocol_internal.h
                boolean to determine if new roles state bitmap should be updated
                in flash
 Return code:   0 (success indication)
---------------------------------------------------------------------------- */
int32_t CME_WlanSetMode(uint8_t calledFromCmeThread,uint32_t role_bitmap, uint32_t timeout, BOOLEAN updateSetModeFlash);

/* ----------------------------------------------------------------------------
 CME_WlanSetPSMode
      This function set new power save mode

 Parameters:    aMode - power save mode

 Return code:   0 - memory allocation succeeded, -1 failed.
---------------------------------------------------------------------------- */
int16_t CME_WlanSetPSMode(uint8_t aMode);

/* ----------------------------------------------------------------------------
 CME_StartApWpsSession
      This function pushes a message with start ap wps session request parameters 
      into CME message queue.

 Parameters: Pointer to command parameters.

 Return code: 0 - push succeeded, -1 failed.
---------------------------------------------------------------------------- */
int16_t CME_StartApWpsSession(wlanWpsSession_t *wpsSession);

/* ----------------------------------------------------------------------------
 CME_SetExtWpsSession


 Parameters: None.

 Return code: 0 if pushing to CME queue succeeded, negative otherwise
---------------------------------------------------------------------------- */
int16_t CME_SetExtWpsSession(wlanSetExtWpsSession_t *wpsParams);


/* ----------------------------------------------------------------------------
 CME_SetWpsApPin
      This function sets WPS AP PIN (for ER)

 Parameters:    WlanSetWpsApPinParam_t
                
 Return code:   0 -  succeeded, -1 failed.
---------------------------------------------------------------------------- */
int16_t CME_SetWpsApPin(WlanSetWpsApPinParam_t *pWpsApPinParams);

/* ----------------------------------------------------------------------------
 CME_GetMacAddress
      This function return the current MAC address

 Parameters:    roleType
                Pointer to MAC address

 Return code:   0 - memory allocation succeeded, -1 failed.
---------------------------------------------------------------------------- */
int16_t CME_GetMacAddress(uint32_t roleType, uint8_t *pMacAddress);

/* ----------------------------------------------------------------------------
 CME_SetMacAddress
      This function set new MAC address

 Parameters:    roleType
                Pointer to MAC address

 Return code:   0 - memory allocation succeeded, -1 failed.
 ---------------------------------------------------------------------------- */
int16_t CME_GetDeviceInfo(device_info_t *pDeviceInfo);
/* ----------------------------------------------------------------------------
 CME_GetDeviceInfo
      This function get device information

 Parameters:    Pointer to pDeviceInfo

 Return code:   0 - memory allocation succeeded, -1 failed.
---------------------------------------------------------------------------- */
int16_t CME_SetMacAddress(uint32_t roleType, uint8_t *pMacAddress);

/* ----------------------------------------------------------------------------
 CME_WlanConnect
      This function pushes a message with WLAN connect request parameters into
      CME message queue.
      As this command may trigger scan, results are sent to host asynchronously.
 Parameters: 	Pointer to command parameters, which are copied to a local
 	 	 	 	buffer. This buffer should be release from CME context.
 Return code:	0 - memory allocation succeeded, -1 failed.
---------------------------------------------------------------------------- */
int32_t CME_WlanConnect(CMEWlanConnectCommon_t *apCmd, CMEEapWlanConnect_t* apEapCmd, BOOLEAN requestByHost);

/* ----------------------------------------------------------------------------
 CME_WlanConnectEap
      This function pushes a message with WLAN EAP connect request parameters into
      CME message queue.
      As this command may trigger scan, results are sent to host asynchronously.
 Parameters:    Pointer to command parameters, which are copied to a local
                buffer. This buffer should be release from CME context.
 Return code:   0 - memory allocation succeeded, -1 failed.
---------------------------------------------------------------------------- */
//int32_t CME_WlanConnectEap(SlWlanConnectEapCommand_t *apCmd);

/* ----------------------------------------------------------------------------
 CME_AddProfile
      This function pushes a message with Add profile request parameters into
      CME message queue.

 Parameters:    Pointer to command parameters, which are copied to a local
                buffer. This buffer should be release from CME context.
 Return code:   0 - memory allocation succeeded, -1 failed.
---------------------------------------------------------------------------- */
int32_t CME_AddProfile(CMEWlanAddGetProfile_t* new_profile);

//same just for EAP type profile
int32_t CME_AddEapProfile(CMEWlanAddGetEapProfile_t *new_profile);
//same but with profile removal
int16_t CME_RemoveProfile(uint8_t delete_profile_index);
int16_t CME_DhcpReleaseComplete();
int16_t CME_GetProfile(uint8_t profileIndex, CMEWlanAddGetEapProfile_t *fillOutArgs);


/* ----------------------------------------------------------------------------
 CME_GetStartedRoleBitmap
      This function get role bit map 
 Return code: bitmask reflecting new roles state 
---------------------------------------------------------------------------- */
uint32_t CME_GetStartedRoleBitmap();

/* ----------------------------------------------------------------------------
 CME_SetStartedRoleBitmap
      This function set the role bit map
 Parameters: bitmask reflecting new roles state
 Return code:
---------------------------------------------------------------------------- */
void CME_SetStartedRoleBitmap(uint32_t role_bitmap);

/* ----------------------------------------------------------------------------
 CME_SetTxPower
      This function sets the TX power
 Parameters: params - pointer to WlanTxPowerSet_t containing role and tx_power_dbm
 Return code:
---------------------------------------------------------------------------- */
int32_t CME_SetTxPower(WlanTxPowerSet_t *params);

/* ----------------------------------------------------------------------------
 CME_GetTxPower
      This function gets the TX power
 Parameters: params - pointer to WlanTxPowerGet_t; tx_power_dbm is filled on return
 Return code: 0 on success, negative error code on failure
---------------------------------------------------------------------------- */
int32_t CME_GetTxPower(WlanTxPowerGet_t *params);

/* ----------------------------------------------------------------------------
 CME_SetStartedRoleBitmap
      This function set the device power save mode
 Return device ps mode:
---------------------------------------------------------------------------- */
uint8_t CME_GetPowerSaveMode(void);

/* ----------------------------------------------------------------------------
 CME_SetPowerSaveMode
      This function set the device power save mode
 Parameters: mode the device ps mode
 Return code:
---------------------------------------------------------------------------- */
void CME_SetPowerSaveMode(uint8_t mode);
/* ----------------------------------------------------------------------------
 CME_SetApParams
      Dispatcher command for set ap parameters
 Parameters: ap Params - see   RoleUpApCmd_t
 Return code:
---------------------------------------------------------------------------- */
int CME_SetApParams(void *apParams);
/* ----------------------------------------------------------------------------
 CME_SetStaParams
      Dispatcher command for set sta parameters
 Parameters: sta Params - see   RoleUpApCmd_t
 Return code:
---------------------------------------------------------------------------- */
void CME_SetStaParams(void *staParams);
/* ----------------------------------------------------------------------------
 CME_SetConnPolicy
      This function pushes a message with new policy settings request parameters into
      CME message queue.

 Parameters:    Pointer to command parameters, which are copied to a local
                buffer. This buffer should be release from CME context.
 Return code:   0 - memory allocation succeeded, -1 failed.
---------------------------------------------------------------------------- */
int16_t CME_SetConnPolicy(WlanPolicySetGet_t *new_policy);

/* ----------------------------------------------------------------------------
 CME_GetConnPolicy
      This function returns current policy settings

 Parameters:    Pointer to command parameters, which are copied to a local
                buffer. runs on WLAN_IF context
 Return code:   0  - success, -1 failed
---------------------------------------------------------------------------- */
int16_t CME_GetConnPolicy(WlanPolicySetGet_t *policy);

/* ----------------------------------------------------------------------------
 CME_WlanDisconnect
      This function pushes a message with WLAN disconnect command into
      CME message queue.

 Parameters: 	none
 Return code:	ERROR_WIFI_ALREADY_DISCONNECTED - already disconnected
 	 	 	    SL_ERROR_INVALID_ROLE - no active role of type STA or P2P_CL
 	 	 	    STATUS_OK - STA/P2P_CL is active, starting disconnection

---------------------------------------------------------------------------- */
int32_t CME_WlanDisconnect(BOOLEAN requestByHost);

int16_t CME_WlanApRemovePeer(CMEWlanApRemovePeer_t *pCmdRemovePeer);

/*---------------------------------------------------------------------------- */
//int16_t CME_SetBLE_Enable()
/* ----------------------------------------------------------------------------
 * send enable BLE
---------------------------------------------------------------------------- */
int16_t CME_SetBLE_Enable();

/*------------------------------------------------------------------------------
// CME_SetP2pCmd - p2p group related commads
-------------------------------------------------------------------------------*/
int16_t CME_SetP2pCmd(WlanP2pCmd_t *p2pCmdParams);

/* ----------------------------------------------------------------------------
 CME_SetNonPrefferedChannels
      This function pushes a message with new non-preffered channels configuration into
      CME message queue.
      Needed for MBO feature.

 Parameters:    Pointer to the non-preffered channel list

 Return code:   0 - push succeeded, -1 failed.
---------------------------------------------------------------------------- */
int16_t CME_SetNonPrefferedChannels(WlanNonPrefChannels_t *pNonPrefChannels);

/* ----------------------------------------------------------------------------
 CME_GetConnectionScanEarlyTermination
      This function returns whether early termination is enabled for connection scans.

 Parameters:    None

 Return code:   1 for enabled, 0 for disabled.
---------------------------------------------------------------------------- */
int16_t CME_GetConnectionScanEarlyTermination();

/* ----------------------------------------------------------------------------
 CME_SetConnectionScanEarlyTermination
      This function enables/disables early termination for connection scans.

 Parameters:    enable

 Return code:   0
---------------------------------------------------------------------------- */
int16_t CME_SetConnectionScanEarlyTermination(uint8_t enable);



/* ----------------------------------------------------------------------------
 CME_SetScanDwellTime
      This function sets the scan dwell time

 Parameters:    enable

 Return code:   0
---------------------------------------------------------------------------- */
int16_t CME_SetScanDwellTime(WlanScanDwellTime_t* dwellTimes);




/* ----------------------------------------------------------------------------
 CME_SetSchedScanPlans
      This function pushes a message with new scheduled scan plans configuration into
      CME message queue.

 Parameters:    Pointer to the scheduled scan plans

 Return code:   0 - push succeeded, -1 failed.
---------------------------------------------------------------------------- */
int16_t CME_SetSchedScanPlans(char *sched_scan_plans);

/* ----------------------------------------------------------------------------
 CME_WlanExtP2pProcessProvDiscActionMsg
      This function send P2P prov-disc-reaponse message from external app
       it pushes the command to the message queue
 Parameters:    the response configuration
 Return code:   WLAN_ERROR_NO_FAILURE - when extp2P is not enabled
                STATUS_OK - msg was set into CME queue

---------------------------------------------------------------------------- */
int32_t CME_WlanExtP2pProcessProvDiscActionMsg(WlanActionParam_t* actionBuff, uint8_t requestByHost);

int32_t CME_WlanConnectValidateReq (CMEWlanConnectCommon_t *apCmd, BOOLEAN  *pIsProfileConnection);
int32_t CME_WlanGetKeyMngtBySecType (uint8_t secType, uint32_t *pKeyMgmtType);
void  CME_WlanGetStatus (void* pResp);

int32_t CME_WlanSetParameter(BOOLEAN CalledFromHost, uint32_t IdAndOption, uint16_t Length, void* pNewValue);
int32_t CME_WlanGetParameter(BOOLEAN CalledFromHost, uint32_t IdAndOption, uint16_t* pLength, void* pCurrentValue);
int32_t CME_BwListSetParameter(BOOLEAN CalledFromHost, uint32_t IdAndOption, uint16_t Length, void* pNewValue);
int32_t CME_BwListGetParameter(BOOLEAN CalledFromHost, uint32_t IdAndOption, uint16_t* pLength, void* pCurrentValue);
int32_t CME_PrivateIeSet(BOOLEAN CalledFromHost, uint32_t IdAndOption, uint16_t Length, void* pNewValue);

int16_t CME_WlanProfileConnectionValidateReq(CMEWlanConnectCommon_t *apCmd);
//void cme_InternalEventHandler(CmeInternalMsgsIds_e _event, void *data);

#endif // _CME_API_H_
