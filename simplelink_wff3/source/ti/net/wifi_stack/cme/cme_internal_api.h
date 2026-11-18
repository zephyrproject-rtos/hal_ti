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

  FILENAME:       cme_internal_api.h

  DESCRIPTION:    This files defines the APIs between CME and its internal modules.

  HISTORY:
                 04/15 - Creation

  ----------------------------------------------------------------------------- */
#ifndef _CME_INTERNAL_API_H_
#define _CME_INTERNAL_API_H_

#include "osi_type.h"
#include "cme_common.h"
#include "cme_scan_api.h"
#include "wpa_supplicant_i.h"   // for wpa_supplicant structure
#include "wps/wps_i.h"

// ============================================================================
//		Modules private definitions
// ============================================================================

/* connect specific flags */
#define CME_GENERAL_DATA_CONNECT_IS_PROFILES  (BIT_0) /* indicates profiles connection */
#define CME_GENERAL_DATA_CONNECT_IS_USER_REQ (BIT_1)

typedef struct
{
	// Point to site survey scan results in GLX.
	// Memory is allocated on first site survey request; it is not expected to survive
	// transition to/from Sleep mode.
	uint8_t *pSiteNetworks;//see WlanNetworkEntry_t cmeNetworkEntryResult_t

	// NUmber of valid networks
	uint32_t CMEWlanAddGetProfile_t;

	// Time elapsed from last site survey scan, used to decide whether a new site
	// survey is required
//	uint32_t lastSiteNetworksUpdate;

	//async event response parameters
	uint8_t responseStartIndex;
	uint8_t responseCount;
	uint8_t responseInternalEvent;

} cmeSiteSurveyResults_t;

typedef struct
{
	cmeScanCandidateDesc_t   *pCandidateScanResults;
	uint8_t                    numCandidates;
	uint8_t                    numAllocatedResults;
} cmeConnectionCandidates_t;

// Notify CME of scan completion.
// it carries scan type, scan status and detected networks information.
typedef struct
{
    uint8_t /*EScanRequestType*/   scanType;       // completed scan type
    cmeScanStatus_e     status;         // scan completion result/cause
    uint8_t               padding[2];
    cmeScanSharedInfo_t *pSharedInfo;   // contains the scan results
    Bool_e              fromTimeout;    // set if triggered by timeout
} CmeScanDoneInfo_t;

// Notify CME of scan completion.
// it carries scan type, scan status and detected networks information.
typedef struct
{
    cmeScanProfilesParams_t *pProfiles;   // pointer to profiles info, memory should be released from CME context
} CmeScanPeriodDoneInfo_t;



typedef struct
{
    void    *address;          /* pointer to header+payload data */
    uint32_t status;           /* the Tx result - 1 (success) or 0 (failure) */
    uint32_t uHeaderLen;       /* number of bytes in @header */
    uint32_t uPayloadLen;      /* number of bytes in @payload */
    uint32_t link;             /* link to send packet in */

}CmeTxDesc_t;

typedef struct
{
	Bool_e                    p2pFindStopping;
	Bool_e                    p2pConnectPending;
} cmeP2pSearchInfo_t;

//STA BSS transition flow
typedef enum
{
     NO_TRANSITION,
     BTM_RECEIVED,
     TRANSITION_IN_PROGRESS
} Bss_transition_states_e;

// =============================================================================
//	CME global variables
// =============================================================================

extern cmeSiteSurveyResults_t 	   gSiteSurveyInfo;
extern cmeConnectionCandidates_t   gCandidatesInfo;
extern OsiSyncObj_t gCmeCommandBlockingSyncObject;
extern int8_t gCmeLastWlanProfileIdx;
extern uint8_t gCurrentSSID[MAXIMAL_SSID_LENGTH];
extern size_t gCurrentSSIDLen;
extern Bool_e  gWPSfirstDisconnect_ull;
extern Bool_e  gWPSkickDisconnect_ull;
extern cmeP2pSearchInfo_t  gCmeP2pInfo;
extern Bool_e gSupplicantInitiatedScanInProgress;
extern Bss_transition_states_e gBssTransitionState;
extern Bool_e gSaveCurrentSupplicantProfile;
extern Bool_e gConnectionScanEarlyTerminationEnabled;

// =============================================================================
// CME FLOWS SM definitions
// =============================================================================
// STA flow:
typedef enum
{
    CME_STA_INIT_EVENT,
    CME_STA_DEINIT_EVENT,
    CME_STA_NETWORK_SEARCH_EVENT,
    CME_STA_FAST_CONNECT_REQ_EVENT,
    CME_STA_WPA_COMPLETED_EVENT,
    CME_STA_SCAN_DONE,
    CME_STA_WLAN_ROLE_UP_EVENT,
    CME_STA_WLAN_DISCONNECT_REQ_EVENT,
    CME_STA_WLAN_PEER_DISCONNECT_REQ,
    CME_STA_WLAN_BSS_LOSS_EVENT,
    CME_STA_WLAN_DHCP_RELEASED_EVENT,
    CME_STA_WLAN_DISCONNECT_COMPLETE_EVENT,
    CME_STA_P2P_CLIENT_INIT_EVENT,
    CME_STA_P2P_CLIENT_DEINIT_EVENT,
    CME_STA_NUM_OF_EVENTS
} Cme_STA_events_e;

//AP flow
typedef enum
{
    CME_AP_INIT_EVENT,
    CME_AP_STOP_ROLE_EVENT,
    CME_AP_NUM_OF_EVENTS
} Cme_AP_events_e;


typedef enum
{
    CME_STA_NONE_USER,
    CME_STA_WLAN_CONNECT_USER,
    CME_STA_PROFILE_MANAGER_USER,
    CME_STA_FAST_CONNECT_USER,
    CME_STA_PROVISIONING_CONFIRM_USER,
    CME_DEVICE_ROC_TIMEOUT,
    CME_P2P_CLIENT_USER,
} Cme_Users_e;

typedef enum
{
    CME_STA_DISABLED_STATE,
    CME_STA_IDLE_STATE,
    CME_STA_SUPPLICANT_MANAGED_STATE,
    CME_STA_CONNECTED_STATE,
    CME_STA_CONFIGURED_STATE,
    CME_STA_DISCONNECT_PEND_DHCP_REL_STATE,
    CME_STA_DISCONNECTING_STATE,
    CME_STA_NUM_OF_STATES
} Cme_STA_states_e;

typedef enum {
    WLAN_STATUS_DISCONNECTED = 0,
    WLAN_STATUS_SCANNING = 1,
    WLAN_STATUS_CONNECTING = 2,
    WLAN_STATUS_CONNECTED = 3,
    WLAN_STATUS_DISCONNECTING = 4
} CME_WlanStatus_e;

typedef enum
{
    CME_DEVICE_INIT_EVENT,
    CME_DEVICE_DEINIT_EVENT,
    CME_DEVICE_ROC,
    CME_DEVICE_CROC,
    CME_DEVICE_NUM_OF_EVENTS
} Cme_DEVICE_events_e;

typedef enum
{
    CME_DEVICE_DISABLED_STATE,
    CME_DEVICE_IDLE_STATE,
    CME_DEVICE_ROC_STATE,
    CME_DEVICE_DEINIT_IN_PROCESS_STATE,
    CME_DEVICE_NUM_OF_STATES
} Cme_DEVICE_states_e;

//Callers for Debug used by CME_ReleaseScanResults
typedef enum
{
                    /* Profile manager Callers */
    CALLER1 = 1,    /* role switch */
    CALLER2,        /* role switch CME Thread*/
    CALLER3,        /* connection policy change */
    CALLER4,        /* added profile */
    CALLER5,        /* removed profile */
    CALLER6,        /* wlan_connect */
    CALLER7,        /* disconnection */
    CALLER8,        /* cme scan completed */
    CALLER9         /* wlan disconnect command */
} Cme_callers_e;

typedef void (SmEventHandler)(Cme_Users_e __user);

// =============================================================================
//	Exported Type Definitions
// =============================================================================

#ifdef CC33XX_CME_DEBUG

typedef struct
{
    uint32_t numEloopTimeouts;
    uint32_t numStaConnection;
    uint32_t numStaDisconnection;
    uint32_t numSTAInterfaceUp;
    uint32_t numSTAInterfaceDown;
    uint32_t numAPInterfaceUp;
    uint32_t numAPInterfaceDown;
} cmeDebugInfo_t;

// Debug info
extern cmeDebugInfo_t gCmeDebugInfo;

// Debug info
#define NOTIFY_STA_CONNECTED()     \
    {                              \
        ++gCmeDebugInfo.numStaConnection; \
        GTRACE(GRP_CME, "gNumStaConnection %d", gCmeDebugInfo.numStaConnection); \
    }
#define NOTIFY_STA_DISCONNECTED()  \
    {                              \
        ++gCmeDebugInfo.numStaDisconnection; \
        GTRACE(GRP_CME, "gNumStaDisconnection %d", gCmeDebugInfo.numStaDisconnection); \
    }
#endif

// ============================================================================
//	Exported Functions 
// ============================================================================

// ----------------------------------------------------------------------------
void CME_FreeTxDesc(void *desc);
// ----------------------------------------------------------------------------

CmeTxDesc_t *CME_CopyTxDesc(void *srcDesc, uint32_t status);

// ----------------------------------------------------------------------------

/* ----------------------------------------------------------------------------
 cmeScan_InitAfterSleep()
 cmeMng_InitAfterSleep()
      Sleep Wake Up Initialization function, activated as part of Sleep wakeup sequence

 Parameters:    none
 Return code:   none
---------------------------------------------------------------------------- */
void cmeScan_InitAfterSleep();
void cmeMng_InitAfterSleep();


/* ----------------------------------------------------------------------------
 cmeScanInit()
      Initialization function, activated as part of out of reset sequence.

 Parameters: 	none
 Return code:	none
---------------------------------------------------------------------------- */
void cmeScanInit();

/* ----------------------------------------------------------------------------
 cmeMngInit()
      Initialization function, activated as part of out of reset sequence.

 Parameters: 	none
 Return code:	none
---------------------------------------------------------------------------- */
void cmeMngInit();

/* ----------------------------------------------------------------------------
 cmeMngInitStaDB()
      Initialization function, activated as part of STA role up process

 Parameters: 	none
 Return code:	none
---------------------------------------------------------------------------- */
void cmeMngInitStaDB();

/* ----------------------------------------------------------------------------
 cmeMngDeInitStaDB()
      De-initialization function, activated as part STA role down process.

 Parameters: 	none
 Return code:	none
---------------------------------------------------------------------------- */
void cmeMngDeInitStaDB();

/* ----------------------------------------------------------------------------
 cmeGetScanResults
      This function retrives scan results (if exist).
      If no valid results, host is expected to retry fetching the results ater
      a timeout.

 Parameters: 	aIndex - index of the first result to fetch
 	 	 	    aCount - number of results to fetch
 	 	 	    aExtraBytes - offset from buffer header, shall be filled with dispatcher info
 	 	 	    apNumNetworks - number of detected networks
 	 	 	    apNumBytes - number of bytes to send (including the dispatcher extra info bytes)
 Return code:	pointer to results buffer.
---------------------------------------------------------------------------- */
uint8_t* cmeGetScanResults(uint32_t aIndex, uint32_t aCount, uint32_t aExtraBytes, uint32_t *apNumNetworks, uint32_t *apNumBytes);

/* ----------------------------------------------------------------------------
 cmeWlanConnect
	Handle ad-hoc connection command

 Parameters: 	aRoleId - role index
                apCmd - pointer to profile params as received from user app.
                aKeyMgmt - management type, WPA_KEY_MGMT_xxx
 Return code:   none
---------------------------------------------------------------------------- */
void cmeWlanConnect(uint32_t aRoleId, CMEWlanConnectCommon_t *apCmd, CMEEapWlanConnect_t *apEapCmd, uint32_t aKeyMgmt, uint8_t profiles_connection);

/* ----------------------------------------------------------------------------
 cmeWlanDisconnect
	Handle disconnection command

 Parameters: 	none
 Return code:   0 - if disconnect completely served (was in < AUTHENTICATED state)
                1 - if deauth sent and wpa disconnect event is pending (was in AUTHENTICATED state)
---------------------------------------------------------------------------- */
uint8_t cmeWlanDisconnect(int reason_code);

/* ----------------------------------------------------------------------------
 prepareProfileInfo
      Allocate memory for profiles information and fill it with valid profiles
		(i.e. profiles which are not in black list).

 Parameters:
      apSharedInfo - IN/OUT information to be filled here
      aScanType    - IN scan type (one shot/periodic)
      apParams     - IN scan params set by the supplicant
 return 0 on success, -1 on failure
---------------------------------------------------------------------------- */
int32_t prepareProfileInfo(cmeScanSharedInfo_t *apSharedInfo, EScanRequestType aScanType, struct wpa_driver_scan_params *apParams);

/* ----------------------------------------------------------------------------
 addProfileIdToSupplicant
      Add a profile to supplicant's DB.
      Profile is identified by a unique profile ID assigned to every new added
      profile. Profile ID is selected by scan module based on the match found
      between scan results and existing profiles.

 Parameters:
      apCandidate - Pointer to candidate info
 Callers: CME context events: CME_MESSAGE_ID_SCAN_PERIOD_COMPLETE
                              CME_MESSAGE_ID_SCAN_COMPLETE 
 return 0 on success, -1 on failure
---------------------------------------------------------------------------- */
int32_t addProfileIdToSupplicant(cmeScanCandidateDesc_t *apCandidate);

//
// cmeProfileIndexSearchByUniqueId
//
// given supplicant unique profile id, search for matching profile
// if exis return the wlan profile index
// else - return -1
//
//int cmeProfileIndexSearchByUniqueId(int8_t profile_id);

/* ----------------------------------------------------------------------------
 addScanResProfile2Supplicant
      Build a profile based on scan result and add it to supplicant.
      This serves only for OPEN policy in order to connect to a detected network
      whcih has no profile.

 Parameters:
      apScanResult - profile to be added to supplicant

 return: none
---------------------------------------------------------------------------- */
void addScanResProfile2Supplicant(struct wpa_scan_res *apScanResult);

//*******************************************************************************************************************
// BLACK LIST METHODS
//*******************************************************************************************************************
//
// cmeClearCurrentConnectionAttemptCtr
//
// successful connection notifier - clear connection attempt for not black-listing this network
// and clear the connecting index as it is not
//
void cmeClearCurrentConnectionAttemptCtr();


//
// cmeConsequtiveScanCompletesNoCandidate
//
// allow X amounts of consequtive scan completes with no candidate found
// before clearing black list that might preventing from black listed profiles
// to enter the scan list
//
void cmeConsequtiveScanCompletesNoCandidate();

void cmeZeroConnectionIndex();
//
// cmeBlackListConnectionAttempt
//
// increment connection attempt counter for network
// then evaluate if all networks are blacklisted then we should clear all counters
//
void cmeBlackListConnectionAttempt(uint32_t index);
//*******************************************************************************************************************

//
// cmeMngSetConnectionPolicy
//
// connection policy settings from user / http server configuration
// handle fast connect storage in case connection is active, or invalidate already stored fast connection
// evantually, call profile manager re-evaluation to see if the new policies might affect the current connection method
//
void cmeMngSetConnectionPolicy(uint8_t should_connect_to_any_p2p_device,
                               uint8_t should_connect_to_open_ap,
                               uint8_t should_use_fast_connect,
                               uint8_t auto_start,
                               uint8_t fast_persistant);

int cmeMngConnectionPolicyUpdated(uint8_t should_use_fast_connect);

// cmeApRemovePeer
// Disconnect and remove a peer from the AP
void    cmeApRemovePeer(uint8_t *macAddr, BOOLEAN isUserReq);
void    cmeApRemoveAllPeers(struct hostapd_data *hapd, BOOLEAN isUserReq);
BOOLEAN cmeAPIsPeerConnected(u8 *macAddr);

int16_t cmeGetNumStaConnected(u8 *numStaConnected);

//int cmeApNetCfgStaInfo(int sta_index, SlNetCfgStaInfo_t *pApStaInfo);

//
// CME_GetConnectionPolicy
//
void CME_GetConnectionPolicy(uint8_t* pConnectOpenAp,
                         uint8_t* pUseFastConnect,
                         uint8_t* pAutoStart,
                         uint8_t* pConnectAnyP2P,
                         uint8_t* pFastPersistant);

//
// cmeMarkInvalidFastConnectionData
//
// invalidate fast connection frame to be used in future system bringup
//
int cmeMarkInvalidFastConnectionData();
//
// cmeFastConnectionTimerReleaseResources
//
// cme fast connect release resources
// called from CME context
//
void cmeFastConnectionTimerReleaseResources();

//
// cmeFastConnectionDeAuthHandler
//
// fast connect wpa_disconnected event handler, according to the fast connect state do the following:
// if was already connected, then just invalidate the entry
// if was during authentication attempt then:
// 1. if it was the first attempt, issue a second auth attempt (iop issue)
// 2. if it was the second attempt. invalidate the entry and release fast connection timer resources
//
// return 0 if fast connect handling is done
// return 1 if fast connect is continueing to second chance
//
int cmeFastConnectionDeAuthHandler(struct wpa_supplicant *wpa_s);

//
// cmeSaveFastConnectionData
//
// read fast connect files from FS and check if need to be re-written according
// to new parameters learned at last successful connection
//
int cmeSaveFastConnectionData();



//
// cmeUpdateCacheFastConnectionData
//
// store connection parameters in fast connect (regardless if policy is set or not- could be changed later)
// for future RESET fast connection attempt
//
void cmeUpdateCacheFastConnectionApScanData(cmeScanCandidateDesc_t* apScanInfo);

/* ----------------------------------------------------------------------------
 cmeStartSiteSurvey
      This function kicks a one shot site survey scan.

 Parameters: 	none
 Return code:	none
---------------------------------------------------------------------------- */
//void cmeStartSiteSurvey();

/* ----------------------------------------------------------------------------
 cmeScanDone
      This function is activated in response to scan completion notification.
      If completed scan is a site survey scan results are kept, waiting for host
      retrive command.
      Otherwise, it forwards the results to supplicant.

 Parameters: 	aRoleId
                apScanInfo - completed scan information

 Return code:	1 - in case connection scan was stopped and not completed
                0 - all other cases.
---------------------------------------------------------------------------- */
int cmeScanComplete(uint32_t aRoleId, CmeScanDoneInfo_t *apScanInfo);

/* ----------------------------------------------------------------------------
 cmePushFast2ScanResult
      This function duplicates FAST candidate to scan results DB.
      Once pushed, FAST candidate is used in the system in the same manner as
      regular candidate deteceted during scan sequence.

 Parameters:    apFastResult - pointer to the FAST candidate to duplicate
 Return code:   none
---------------------------------------------------------------------------- */
void cmePushFast2ScanResult(cmeScanCandidateDesc_t *apFastResult);

/* ----------------------------------------------------------------------------
 cmeProfileManagerConfigChange
      This function is activated in from several inputs, and is actually the fallback
      for most cases.
      The main goal of the function is to connect to one of the preferred networks stored in the FS, in case
      at least one profile exist and auto start is enabled (under STA/P2P role)

 Parameters:    none
 Return code:   none
---------------------------------------------------------------------------- */
void cmeProfileManagerConfigChange(int force_one_shot_profile_search, uint8_t caller);
//
void cmeStartSiteSurvey(uint8_t aRoleId, CMEWlanScanCommon_t* pScanCommon);

/* ----------------------------------------------------------------------------
 cmeWlanConnectDigest
                handles WLAN_CONNECT Message in CME
 Parameters:    pConnectCmd
                keyMgmtType
                connectReq
                bReconnect
 Return code:   none
---------------------------------------------------------------------------- */
void cmeWlanConnectDigest(CMEWlanConnectCommon_t *pConnectCmd,CMEEapWlanConnect_t* pEapConnectCmd, uint32_t keyMgmtType, uint16_t connectReq, Bool_e bReconnect);

/* ----------------------------------------------------------------------------
    cmeReassociationParamsStore
        Stores current connection parameters for potential future use during reassociation.

    Parameters:    None

    Return code:   None
---------------------------------------------------------------------------- */
void cmeReassociationParamsStore();

/* ----------------------------------------------------------------------------
    cmeReassociationParamsRestore
        Restores previously stored connection parameters for reassociation.

    Parameters:    None

    Return code:   None
---------------------------------------------------------------------------- */
void cmeReassociationParamsRestore();

/* ----------------------------------------------------------------------------
    cmeReassociationParamsClear
        Clears the connection parameters previously stored for reassociation.

    Parameters:    None

    Return code:   None
---------------------------------------------------------------------------- */
void cmeReassociationParamsClear();

/* ----------------------------------------------------------------------------
    cmeAreReassociationParamsValid
        Checks if stored connection parameters exist and are valid for 
        reassociation purposes.

    Parameters:    const _cme_minimized_wpa_ssid_t *apInputApSsid

    Return code:   TRUE if valid params for reassociation, FALSE otherwise
---------------------------------------------------------------------------- */
Bool_e cmeAreReassociationParamsValid(const _cme_minimized_wpa_ssid_t *apInputApSsid);

/* ----------------------------------------------------------------------------
 CME P2P exported Functions
---------------------------------------------------------------------------- */
void cmeP2pConnect(void *apPriv);
Bool_e CME_IsP2PConnectionRequired(uint8_t secType);
void cmeHandleP2pConnection(CMEWlanConnectCommon_t *apCmd, uint32_t aKeyMgmt);
void cmeStartP2pFind(struct wpa_supplicant *wpa_s, uint8_t *peer_addr, uint32_t timeout, Bool_e reportResult);
void CME_P2pDevFound(uint32_t aRoleId);
void CME_P2pNegConfirmation(uint32_t aRoleId, Bool_e isGO);
void cmeP2pGroupRemove(void);
void cmeP2pCancel(void);
void cmeStopP2pFind(struct wpa_supplicant *wpa_s);
void cmeP2pClearAll();
void cmeP2pGroupAdd(const char *ssidPostfix, int32_t freq);

/* ----------------------------------------------------------------------------
 cmeRemoveAllProfilesFromSupplicant
      This function removes all networks from supplicant DB

 Parameters:    none
 Return code:   none
---------------------------------------------------------------------------- */
void cmeRemoveAllProfilesFromSupplicant(struct wpa_supplicant *wpa_s, int reason_code);

// ----------------------------------------------------------------------------
// Nov 7 2016 - scan early termination threshold configuration
// ----------------------------------------------------------------------------
void cmeScanEarlyTermThresholdSet(cmeScanSharedInfo_t *apSharedInfo, int shouldUseFastConnect, int profile_priority/*-1 means ad-hoc*/,int secured_profile);

/* ----------------------------------------------------------------------------
 cmeSetScanCmeInfo
      This function is responsible to do all pre-scan preparartions.
      This includes:
        - memory allocation for scan results
        - building preferred networks list (to be used for selecting connection candidate)
        - notifying scan module information is ready

 Parameters: 	apSharedInfo - pointer to memory allocated by scan module, to
 	 	 	 				   be filled in this function
 	 	 	 	aScanType    - Scan type (survey/connection)
 	 	 	 	apSyncObj    - Scan sync object, shall be given to preempt the
 	 	 	 	               scan context when done.
                    apParams     - scan params set by the supplicant.
 Return code:	0 on success, -1 on failure (memory allocation)
---------------------------------------------------------------------------- */
int32_t cmeSetScanCmeInfo(cmeScanSharedInfo_t          *apSharedInfo,
                         EScanRequestType              aScanType,
					OsiSyncObj_t 		          *apSyncObj,
                         struct wpa_driver_scan_params *apParams);


//preferred network related API's
int16_t cmeAddPreferredNetwork(
                             //legacy profile parameters
                             CMEWlanAddGetProfile_t *pProfile,
                             int16_t *index_profile_ptr,
                             //ent profile parameters
                             void *pEapProfile,
                             int16_t *index_eap_profile_ptr);

int16_t cmeDeletePreferredNetwork(int index);
void    cmeIsCurrentlyConnectedProfileDeleted(int index);
int16_t cmeGetPreferredNetwork(uint8_t Index, CMEWlanAddGetEapProfile_t *Args);
int16_t cmeAddWpsCredentials2PreferredNetworks(struct wpa_supplicant *wpa_s, const struct wps_credential *cred);

/* ----------------------------------------------------------------------------
 cmeClearAdHocProfile
      This function is activated on disconnection event. If the connection was
      ad-hoc one, it clears ad-hoc profile ID.
      If connection was WPS based ...

 Parameters:    pointer to wpa_s object
 Return code:   none
---------------------------------------------------------------------------- */
void  cmeClearAdHocProfile(struct wpa_supplicant *wpa_s);

void  cmeSendConnectionStatusAsyncEvent(int connect_status, uint32_t Reason_Code, uint8_t roleId, uint8_t *bssidAddr);
//void  cmeFillProcessTimeoutData (SlWlanEventProcessTimeout_t *pMsg, uint8_t id);
BOOLEAN cmeCompareLastAdHocConnParams(CMEWlanConnectCommon_t *pCmdbuffer);
BOOLEAN cmeIsThisPeerInRemovalProgress(uint8_t *pMacAddr);
BOOLEAN cmeIsLastPeerRemovedValid();
void    cmeInvalidateLastPeerRemoved();

void  cmePendingWlanConnectStor(CMEWlanConnectCommon_t *pConnectCmd,CMEEapWlanConnect_t *pConnectEapCmd,uint16_t keyMgmtType, uint8_t profiles_connection);
void  cmeFreePendingWlanConnectResources();
//
//role activation module
//

#define CME_IS_ACTIVE_ROLE(role_bitmap,roletype) (role_bitmap & BIT_x(roletype))

uint8_t cme_is_activated_role_from_type(uint8_t role_type);
uint8_t cme_is_started_role_from_type(uint8_t role_type);
int cme_role_switch_manager(Cme_Users_e _deactivating_user, uint32_t deactivation_action_role_bitmap, uint8_t signal_event_when_done);
int cme_activate_sta_role();
int cme_activate_device_role();
int cme_deactivate_device_role(Cme_Users_e _deactivating_user);
void cme_set_unset_started_role(uint8_t set, uint8_t role_type);
int cme_deactivate_sta_role(Cme_Users_e _deactivating_user);
int cme_deactivate_sta_role_complete(Cme_Users_e _deactivating_user);
int cme_is_ap_role_like_activated();
int cme_is_sta_role_like_activated();
int cme_is_device_role_like_activated();
int cme_is_p2p_role_configured();


//void cme_manager_set_idle_mode();

//AP supplicant methods
int32_t supplicantRunAP();
void CmeApDeInit();

//AP peer management
void CmeApPeerConnectedNotify(uint8_t *connected_peer_addr, uint8_t AID, uint8_t isExtWPSInProgress);
void CmeApPeerDisConnectedNotify(uint8_t *disconnected_peer_addr);

//AP ip configuration api's
void cme_role_ap_ip_netapps_bringup();
void cme_role_ap_ip_netapps_bringdown();

int cme_deactivate_p2p_role(Cme_Users_e _deactivating_user);
int cme_deactivate_p2p_role_complete(Cme_Users_e _deactivating_user);

int cme_activate_ap_role();
int cme_deactivate_ap_role();

//Transceiver peer management
int cme_activate_transceiver_role();
int cme_deactivate_transceiver_role();

int CME_ReadWlanFlashParams(cmeWlanConfigFlashElement_t* pWlanConfig, BOOLEAN calledFromHost);
int CME_WriteWlanFlashParams(cmeWlanConfigFlashElement_t* pWlanConfig, BOOLEAN calledFromHost);

void CME_GetScanParamsFromFlash(uint32_t* pScanChannelGbandMask,
                               uint32_t* pScanChannelAbandMask,
                               uint8_t*  pScanChannelJbandMask,
                               int8_t*   pScanRssiThreshold
                              );

void CME_PrivateIeAndBwListCreate(void);
void CME_PrivateIeAndBwListDestroy(void);
void CME_generalSemaphoreCreate(void);
void CME_generalSemaphoreDestroy(void);
int32_t CME_generalSemaphoreTake(void);
void CME_generalSemaphoreRelease(void);
BOOLEAN CME_IsMacAllowed(uint8_t* pMacAddress);
int32_t ReadPieAndMacListFromFlash(cmeBwListCB_t* pBwListCB,
                                 cmePrivateIeCB_t* pPrivateIeCB,
                                 BOOLEAN calledFromHost);
int32_t WritePieAndMacListToFlash(cmeBwListCB_t* pBwListCB,
                                cmePrivateIeCB_t* pPrivateIeCB,
                                BOOLEAN calledFromHost);


void convertAsciiString2Hex(int8_t *dest, int8_t *pString, uint32_t aLength);

//
// CME station flow state machine core API
//
int CmeStationFlowSM(Cme_STA_events_e event, Cme_Users_e user);
int CmeStationFlowIsSMIdle();
int CmeStationFlowIsConnected();
int CmeStationFlowIsDisconnecting();
int16_t CmeStationFlowHostStatusGet();
Cme_Users_e CmeStationFlow_GetCurrentUser();
Cme_STA_states_e CmeStationFlow_GetCurrentState();

int CmeDeviceFlowSM(Cme_DEVICE_events_e event, Cme_Users_e user);
int CmeDeviceFlowIsSMIdle();
Cme_Users_e CmeDeviceFlow_GetCurrentUser();


int CmeAPFlowSM(Cme_AP_events_e event);
int CmeSetApParams(void *apParams);
int CmeApFlowIsUp();
int CmeApFlowIsDisconnecting();
int CmeApAnyConnectedLinks();
int8_t CmeGetConfiguredApTxPower(void);

uint8_t CME_GetLastDisconnectReason();

void cmeDeviceFlow();

//Start supplicant periodic timer
void CME_startSupplicantPeriodicTimer(void);

extern int16_t LoadConnectionPolicy_GetFromFlash(BOOLEAN isInternal, BOOLEAN runFromInit);



Bool_e CMEisSameConnectParams(CMEWlanConnectCommon_t *pCmdbuffer, int8_t* ssidName, Bool_e checkBssid);
Bool_e CMEIsWPA3TransitionModeDisabled(uint32_t keyMgmt,int32_t profileId);
int cmeCheckCurrentIsTransitionMode();

void cmeAddWpaPmkCache(struct wpa_supplicant *wpa_s, const uint8_t *pmkid, uint8_t *pmk, uint8_t pmk_len, uint8_t *bssid, int key_mgmt);
void cmeRemoveWpaPmkCache(void);

extern uint8_t gCmeRoleSwitchActive;
extern uint8_t gCmeConnectedLinksCount;


const char *cmeWlanGetKeyMgmt();

void CmeSetStaParams(void *staParams);
void CmeApExtWpsFailureNotify(int8_t wpsFailCode);

/* P2P Group Notifications */

void CmeP2pGroupStartedNotify(struct wpa_supplicant *wpa_s, uint8_t *groupPeerAddr, Bool_e isGroupTypeGo);
void CmeP2pGroupRemovedNotify(RoleType_e roleType);
p2pGroupRoleType_e CmeGetP2pGroupRoleType(void); 

#endif // _CME_INTERNAL_API_H_
