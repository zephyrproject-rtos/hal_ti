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

  FILENAME:       cme_supplicant_api.h

  DESCRIPTION:    This files defines the APIs between CME and supplicant or
  	  	  	  	  cc3300 driver (ex driver_wilink)

  HISTORY:
                 04/15 - Creation

  ----------------------------------------------------------------------------- */
#ifndef _CME_SUPPLICANT_API_H_
#define _CME_SUPPLICANT_API_H_

#include "cme_defs.h"
#include "cme_scan_api.h"

// ============================================================================
//	Exported Type Definitions
// ============================================================================


// TI cc3300 supplicant driver interface names; used by cc3300 supplicant driver
// to get interface type.
#define TIWLAN_DEV_NAME_STA		"ti_sta"
#define TIWLAN_DEV_NAME_SAP		"ti_sap"
#define TIWLAN_DEV_NAME_P2PDEV 	"ti_p2pdev" //p2p-dev-ti_sta
#define TIWLAN_DEV_NAME_P2P 	"ti_p2p"	// either P2P CL or P2P GO
#define TIWLAN_DEV_NAME_P2P_GO 	"ti_p2p_go"
#define TIWLAN_DEV_NAME_P2P_CL 	"ti_p2p_cl"		

#define NETIF_NAME(DEVNAME) 	DEVNAME"0"
#define NETIF_CONF_NAME(DEVNAME)    (NETIF_NAME(DEVNAME)"_conf")

// forward declaration, struct is defined in  drv_ti_internal.h
//struct ti_driver_ifData_t;

// forward declaration, struct is defined in cc33_public_commands.h
//struct ROCParameters_t;

// forward declaration, structs are defined in wpa_supplicant_i.h
struct wpa_global;
struct wpa_supplicant;

typedef enum
{
    CME_SITE_SURVEY_IDLE,       // site survey scan isn't pending/running
                                // set in CME init and when site survey scan complete event
                                // is received
    CME_SITE_SURVEY_TRIGGERED,  // site survey scan was triggered but not configured yet
                                // (CME_MESSAGE_ID_SET_SCAN_CME_INFO wasn't activated yet)
    CME_SITE_SURVEY_RUNNING     // site survey scan is running
} cmeSiteSurveyState_t;

// ============================================================================
//  CME - supplicant shared globals
// ============================================================================

extern struct wpa_global *gpSupplicantGlobals;


// Site survey scan state
extern cmeSiteSurveyState_t gSetSiteSurvey;


// ============================================================================
//	CME exported Functions
// ============================================================================

/* ----------------------------------------------------------------------------
 CME_EloopTimeoutUpdated
      This function preempts the CME context. The timeout for blocking on message
      queue is updated based on this new event.

 Parameters: 	none
 Return code:	none
---------------------------------------------------------------------------- */
int32_t CME_EloopTimeoutUpdated();

/* ----------------------------------------------------------------------------
 CME_SendCmd2WlanServices
      This function forwards a command via CME to WLAN LP serivces.
      Before forwarding, CME checks if command contains relevant CME information.
      If so, it uses it before forwarding. This happens for:
           - AP role - STA connected - update AP connections state
           - AP role - STA disconnected  - update AP connections state
      CME blocks on a sync object until WLAN services completes command handling.
      This way CME messages order is kept as is.
 Parameters:    apCmd - pointer to the command
 Return code:   none
---------------------------------------------------------------------------- */
void CME_SendCmd2WlanServices(void *apCmd);

/* ----------------------------------------------------------------------------
 CME_NotifyStaConnectionState
      This function notifies CME of a change in L2 connection state for STA role.
      CME shall forward the information to relevant modules.
 Parameters:    aRoleId - ID of the reporting role
                aConnectionState - State of connection
                aReasonCode - disconnection reason code; irrelevant in case of
                connection notification
 Return code:   none
---------------------------------------------------------------------------- */
void CME_NotifyStaConnectionState(uint32_t aRoleId, LinkConnectionState_e aConnectionState, uint16_t aReasonCode);

/* ----------------------------------------------------------------------------
 CME_notifyScanDone
      This function pushes a message to the cME queue to notify about scan done
Parameters:    aRoleId - ID of the reporting role
Return code:
---------------------------------------------------------------------------- */
void CME_notifyScanDone(uint32_t aRoleId);

/* ----------------------------------------------------------------------------
 CME_GetProbeRequestIes
      This function gives driver_cc a buffer for filling extra probe request IEs.
      IF the ULL buffer was already allocated and its size is sufficient, memory
      shall not be allocated and the new IEs shall override the existing buffer.
      It is retrieved by scan module before every periodic scan cycle.
 Parameters:    aBufferLenegth - number of bytes to copy
 Return code:   Pointer to CME extra IEs object
---------------------------------------------------------------------------- */
//ProbeRequestInfo_t * CME_GetProbeRequestIes(uint32_t aBufferLenegth);

/* ----------------------------------------------------------------------------
 CME_ReleaseScanResults
      This function indicates the CME driver_cc has completed using scan results.
      The CME shall release scan results and clear number of scan results.
 Parameters:    none
 Return code:   none
---------------------------------------------------------------------------- */
void CME_ReleaseScanResults(uint32_t aCaller);

/* ----------------------------------------------------------------------------
 CME_FindBssidInCandidatesScanTable
      This search the candidates results in the scan table for the requested bssid.

 Parameters:    bssid
 Return code:   pointer to the matching candidate entry
---------------------------------------------------------------------------- */
cmeScanCandidateDesc_t * CME_FindBssidInCandidatesScanTable (const uint8_t *bssid);

/* ----------------------------------------------------------------------------
 CME_InternalEventHandler
      This function notifies the CME of WLAN events.
 Parameters:    event - newly occured event
         `      data - event related data, should always carry role ID
 Return code:   none
---------------------------------------------------------------------------- */
//void CME_InternalEventHandler(CmeInternalMsgsIds_e _event, void *data);

/* ----------------------------------------------------------------------------
 CME_GetScanResultsFilterCfg
      This API set scan results filtering configuration based on connection
      type (WPS/P2P/legacy).

 Return code:   TRUE - if WPS connection is pending
---------------------------------------------------------------------------- */
scanResultsFilterCfg_e CME_GetScanResultsFilterCfg();

/* ----------------------------------------------------------------------------
 CME_IsOngoingWPSAdHocConnection
      Returns TRUE if wps ad hoc connection is ongoing.

 Return code:   TRUE / FALSE
---------------------------------------------------------------------------- */
Bool_e CME_IsOngoingWPSAdHocConnection();

/* ----------------------------------------------------------------------------
 CME_ClearWPSAdHocConnection
      Clear ongoing wps ad hoc connection

 Return code:   TRUE / FALSE
---------------------------------------------------------------------------- */
void CME_ClearWPSAdHocConnection();

/* ----------------------------------------------------------------------------
 CME_SetWPSAdHocConnection
      Set WPS AdHoc Connection

 Return code:   TRUE / FALSE
---------------------------------------------------------------------------- */
void CME_SetWPSAdHocConnection();

/* ----------------------------------------------------------------------------
 CME_SetProbeRequestIes
      This function stores extra IEs in CME.
      This is temporary, may be removed when CME produces extra IEs per new
      scan cycle.

 Return code:   supplicant originated extra IEs info
---------------------------------------------------------------------------- */
void CME_SetProbeRequestIes(uint32_t alen, uint8_t *apBuff);

/* ----------------------------------------------------------------------------
 CME_GetConnectionCandidates
      This function supplies a pointer to connection candidate/candidates; this
      may be scan results based in case of ad-hoc or profile connection OR fast
      connection information based, in case of fast connection.
      It is CME responsibilty to point to the correct DB according to its state.

 Return code:   supplicant originated extra IEs info
---------------------------------------------------------------------------- */
void CME_GetConnectionCandidates(uint32_t alen, uint8_t *apBuff);


// ============================================================================
//	cc33xx driver exported Functions
// ============================================================================
/* ----------------------------------------------------------------------------
 drv_getDeviceIface
      Search for Device interface

 Parameters: IN  apGlobal - pointer to global supplicant info
             OUT apIface  - pointer to the detected Device iface (if found)
 Return:  detected role type
---------------------------------------------------------------------------- */

RoleType_e drv_getDeviceIface(struct wpa_global *apGlobal, struct wpa_supplicant **apIface);

/* ----------------------------------------------------------------------------
 drv_getStaIface
      Search for STA based interface

 Parameters: IN  apGlobal - pointer to global supplicant info
             OUT apIface  - pointer to the detected STA based iface (if found)
 Retrun:  detected role type
---------------------------------------------------------------------------- */
RoleType_e drv_getStaIface(struct wpa_global *apGlobal, struct wpa_supplicant **apIface);

/* ----------------------------------------------------------------------------
 drv_getRoleIdFromType
      Search for role-type based interface and get its role id

 Parameters: IN  apGlobal - pointer to global supplicant info
 Retrun:  detected role id
---------------------------------------------------------------------------- */
int drv_getRoleIdFromType(struct wpa_global *apGlobal,RoleType_e roleType);

/* ----------------------------------------------------------------------------
 drv_getRoleTypeFromRoleId
      Search for roletype from its role id

 Parameters: IN  apGlobal - pointer to global supplicant info
             OUT apIface  - pointer to the detected STA based iface (if found)
 Retrun:  detected role type
---------------------------------------------------------------------------- */
RoleType_e drv_getRoleTypeFromRoleId(struct wpa_global *apGlobal, uint32_t aRoleID);

/* ----------------------------------------------------------------------------
 drv_getIfaceFromRoleID
      Translate netIf received from  interface

 Parameters: IN  apGlobal - pointer to global supplicant info
             IN  aRoleID   - network IF handle received from scan module CB
 Retrun:  pointer to wpa supplicant instance
---------------------------------------------------------------------------- */
struct wpa_supplicant * drv_getIfaceFromRoleID(struct wpa_global *apGlobal, uint32_t aRoleID);


/* ----------------------------------------------------------------------------
 drv_getP2pDeviceSupplicant
      Search for p2p device interface

 Parameters: IN None

 Retrun:  pointer to wpa supplicant instance
---------------------------------------------------------------------------- */
 struct wpa_supplicant* drv_getP2pDeviceSupplicant(void);
/* ----------------------------------------------------------------------------
 drv_handleScanCompleteEvent
      This function forwards the notification of connection scan completion to
      supplicant.

 Parameters: 	apDrv - pointer to drive instance
 	 	 	 	aScanType - type of compelted scan
 	 	 	 	aNumResults - number of detected networks.
 Return code:	none
---------------------------------------------------------------------------- */
void drv_handleScanCompleteEvent(void *apDrv, EScanRequestType aScanType, uint32_t aNumResults);

/* ----------------------------------------------------------------------------
 drv_handleScanStoppedEvent
      This function forwards the notification that periodic scan has stopped to
      supplicant.

 Parameters: 	apDrv - pointer to drive instance
 Return code:	none
---------------------------------------------------------------------------- */
void drv_handleScanStoppedEvent(void *apDrv);

/* ----------------------------------------------------------------------------
 drv_handleUnprotRxDeauth
      This function forwards the notification that an unprotectedt deauth/deassoc
      frame was recived on a protected link, to supplicant.

 Parameters:    aDescriptorId - Descriptor Id
 Return code:   none
---------------------------------------------------------------------------- */
void drv_handleUnprotRxDeauth (void *descriptor, uint32 roleId);

/* ----------------------------------------------------------------------------
 drv_handleOneShotScanStoppedEvent
      This function forwards the notification that one-shot scan has stopped to
      supplicant.

 Parameters:    wpa_s
 Return code:   scan type that was stopped
---------------------------------------------------------------------------- */
void drv_handleOneShotScanStoppedEvent(struct wpa_supplicant *wpa_s,EScanRequestType    scanType);


/* ----------------------------------------------------------------------------
 cc33drv_handleRxMngPacket
      This function notifies a management/EAPOL packet was receivet.
      Packet is first handled by the cc33 driver, then if necessary supplicant
      is also notified.

 Parameters: 	aDescriptorId - received packet descriptor
 Return code:	none
---------------------------------------------------------------------------- */
void drv_handleRxMngPacket(void *descriptor);
/* ----------------------------------------------------------------------------
 drv_handleRemainOnChannelEvent
      This function forwards the notification that ROC/CROC command was handled
      to supplicant.

 Parameters: 	apDrv - pointer to drive instance
 	 	 	 	aIsRoc - TRUE - ROC has started, FALSE - CROC was completed
 	 	 	 	aDuratioMS - time to ROC
 	 	 	 	aChannel - channel to ROC on
 Return code:	none
---------------------------------------------------------------------------- */
void drv_handleRemainOnChannelEvent(void *apDrv, Bool32 aIsRoc, uint32_t aDurationMS, uint32_t freq);

/* ----------------------------------------------------------------------------
 drv_handleTxResult
      This function reports of TX result of management packets & EAPOLs

 Parameters: 	results - transmitted packet results
 Return code:	none
---------------------------------------------------------------------------- */
void drv_handleTxResult(void *results);

/* ----------------------------------------------------------------------------
 drv_handleRxEapol
      This function reports of received EAPOL packet

 Parameters:    aDescriptorId - received packet descriptor ID
 Return code:   none
---------------------------------------------------------------------------- */
void drv_handleRxEapol(void *aDescs);

/* ----------------------------------------------------------------------------
 drv_handleRxFromUnknown
      This function reports the supplicant about a packet received from an unknonw peer

 Parameters:    aDescriptorId - received packet descriptor ID
 Return code:   none
---------------------------------------------------------------------------- */
void drv_handleRxFromUnknown (void *descriptor, uint32 roleId);

/* ----------------------------------------------------------------------------
 cc33drv_pnReplayDetected
      This function notifies PN replay detected
 Parameters:    aDescriptorId - descriptor ID of the failed packet
                cipherType    - cipher suite used
 Return code:   none
---------------------------------------------------------------------------- */
void cc33drv_pnReplayDetected(uint32_t aDescriptorId, uint16_t cipherType);

/* ----------------------------------------------------------------------------
 cc33drv_aesSwDecryptionNeeded
      This function notifies AES HW decryption of this specific packet was failed and
      SW decryption might be needed.
 Parameters:    aDescriptorId - descriptor ID of the failed packet

 Return code:   none
---------------------------------------------------------------------------- */
void cc33drv_aesSwDecryptionNeeded(uint32_t aDescriptorId);

/* ----------------------------------------------------------------------------
 drv_lowAck
      This function serves only AP based role.
      It notifies a bad connection was deteced. This can be either due to
      MAX_TX_FAILURE_EVENT_ID or INACTIVE_STA_EVENT_ID produced in legacy FW code.

 Parameters:    apGlobal - pointer to global drivers DB
                aRoleId - ID of the reporting role
                aInactiveLinksBits - a bit mask of all inactive links
                aMaxRetries - indicates activation reason. T
                              TRUE - max retries, FALSE - STA aging
 Return code:   none

 TODO - we may add actual number of links or report of one link at a time
        in order to avoid looping on all possible links every time.
---------------------------------------------------------------------------- */
void drv_lowAck(struct wpa_global *apGlobal, uint32_t aRoleId,
                    uint16_t aInactiveLinksBits, Bool32 aMaxRetries);

/* ----------------------------------------------------------------------------
 drv_stopConnectionScans
      This function stops any connection active scans (one shot/periodic) and
      cancels any scheduled scans.

 Parameters:    wpa_s - pointer to supplicant instance
 Return code:   TRUE - if connection scan is active, FALSE - else.
                When TRUE is returned, scan sends CME_MESSAGE_ID_SCAN_COMPLETE
                message with CME_SCAN_STATUS_STOPPED result to notify scan
                was stopped.
---------------------------------------------------------------------------- */
Bool32 drv_stopConnectionScans(struct wpa_supplicant *wpa_s);

/* ----------------------------------------------------------------------------
 cc33drv_startSiteSurvey
      This function kicks the site survey scan
 Parameters:    aRoleId
 Return code:   none
---------------------------------------------------------------------------- */
void cc33drv_startSiteSurvey(uint8_t aRoleId);
int8_t mx_driver_site_survey_scan(uint8_t roleID);

#endif // _CME_SUPPLICANT_API_H_
