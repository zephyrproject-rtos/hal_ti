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
  FILENAME:       cme.c

  DESCRIPTION:    This file handles CME management.
                  It is responsible for:
                      - CME APIs both for host SW and on chip SW modules
                      - running the CME thread
                      - handling CME and wpa supplicant eloop events

  HISTORY:
                  04/15 Creation
  ----------------------------------------------------------------------------- */

#include <data_path/udata/export_inc/udata_api.h>
#include <stdio.h>

#include "osi_kernel.h"

#include "common.h"
#include "wpa_supplicant_i.h"
#include "wpabuf.h"        // for getting extra IEs
#include "hostapd.h"

#include "cme_scan_api.h"
#include "cme_fw_api.h"
#include "cme_internal_api.h"
#include "cme_supplicant_api.h"
#include "cme_dispatcher_api.h"
#include "cme_defs.h"
#include "cme_tester.h"

#include "gtrace.h"
#include "macro_utils.h"


#include "wlan_if.h"
#include "ble_if.h"

#include "errors.h"
#include "drv_ti_internal.h"
#include "80211_utils.h"
#include "lower_mac_if.h"
#include "cme_defs.h"
#include "rx.h"
#include "rx_defs.h"

#include "drv_ext_app.h"
#include "wpa_supplicant/ap.h"
#include "wpa_supplicant/bss.h"
#include "wlan_links.h"
#include "control_cmd_fw.h"
#include "wpa_supplicant_i.h"
#include "driver_i.h"
#include "cme_internal_api.h"
#include "l2_cfg.h"
#include "regulatory_domain_api.h"
#include "wps_hostapd.h"
// ============================================================================
//      Debug only - CME tester
// ============================================================================

extern void cmeTestInit();
extern bool mx_driver_scan_is_scan_tagged_frame(void *pDesc);
extern void set_finish_wlan_supplicant_operation();
#ifndef TI_STA_ONLY_BUILD
extern void cmeP2pListen();
#endif
extern void cfgBuildP2pParameters(struct wpa_config *conf);
extern  cmeScanSharedInfo_t*    scanResultTable_GetCmeScanDbPointer();
extern int32_t is_wlan_periodic_scan_in_progress();
extern ti_driver_ifData_t * getDriverForRoleId(uint32_t aRoleId, struct wpa_global *apGlobal);
extern void CME_periodic_scan_timer_stop();
extern void CME_start_periodic_scan_timer();
extern TUdata *gUdataCB;
#ifndef TI_STA_ONLY_BUILD
extern int ti_driver_inact_mili(void *priv, const u8 *addr);

void CME_start_peer_aging_timer(OsiTimer_t* osTimer, uint32_t timeout);
void CME_peer_aging_timer_stop(OsiTimer_t* osTimer);
#endif

extern void wlanLinks_getPeerList(int32_t* numOfPeers, uint8_t** mac_addr_peer_list);


void *XMALLOC(size_t n, void* heap, int type)
{
    return os_malloc(n);
}
void *XREALLOC(void *p, size_t n, void* heap, int type)
{
    return os_realloc(p,n);
}
void XFREE(void *p, void* heap, int type)
{
    os_free(p);
}



// Debug ----------------------------------------------------------------------
#define CC35XX_ADD_SUPPORT_ENT_PROFILE (0)

#define IS_PROFILE_CONNECT(Flags) ((Flags & WLAN_CONNECT_FLAG_PROFILE_CONNECT) == WLAN_CONNECT_FLAG_PROFILE_CONNECT)


// Supplicant & driver_cc33 APIs
extern int eloop_get_timeout(void);
extern void eloop_handle_timeout();
extern void _recvNetworkPacket(uint32_t netifid,uint8_t *inbuf, uint32_t inbuf_len);
extern int WLSendFW_Command(uint16_t opcode, uint32_t id, void *cmd, uint32_t len, void *out, uint32_t outLen);
extern void ti_driver_cancel_remain_on_channel_timer_callback_handle();

//Profile Managers
extern uint8_t     gPreferredReadFromFS;

// ============================================================================
//      Modules private definitions
// ============================================================================
// Messages sent from caller context via CME API to CME thread
typedef enum
{
    // -------------------------------
    //  System wakeup
    // -------------------------------
    CME_MESSAGE_ID_RESET,
    // -------------------------------
    //  Host commands
    // -------------------------------
    CME_MESSAGE_ID_GET_SCAN_RESULTS,        // Site survey request.
                                            // Scan results are forwarded to host w/o being stored,
                                            // hence CME triggers a one shot scan.
    CME_MESSAGE_ID_WLAN_CONNECT,            // WLAN connect commands, the message carries all
                                            // connection information.
    CME_MESSAGE_ID_WLAN_EAP_CONNECT,
    CME_MESSAGE_ID_WLAN_DISCONNECT,         // WLAN disconnect command, in case more than one role
                                            // is active, disconnect the P2P or STA base role.

    CME_MESSAGE_ID_PROFILE_ADDED,           // WLAN profile list new settings (STA or P2P profile)

    CME_MESSAGE_ID_PROFILE_EAP_ADDED,       // EAP profile add
    CME_MESSAGE_ID_PROFILE_REMOVED,         // WLAN profile list new settings (STA or P2P profile)

    CME_MESSAGE_ID_NEW_ROLE_SET,            // WLAN Role set configuration (STA/P2P/AP or STA/AP combination)

    CME_MESSAGE_ID_POLICY_SET,              // WLAN Connection policy new settings

    CME_MESSAGE_ID_PS_SET,                  // WLAN Set power save mode

    CME_MESSAGE_ID_AP_REMOVE_PEER,          // WLAN AP remove connected peer

//    CME_MESSAGE_ID_ROLE_START_COMPLETE,      // FW role start indication
//
//    CME_MESSAGE_ID_ROLE_STOP_COMPLETE,      // FW role stop complete indication

    CME_MESSAGE_ID_P2P_CMD,                 // Wlan Set P2P commads 

    CME_MESSAGE_ID_SET_WPS_AP_PIN,          // Wlan Set WPS AP PIN for ER 

    // -------------------------------
    //  Internal events
    // -------------------------------
    CME_MESSAGE_ID_ROLE_UP,                 // following role activation, FW indication upon successful role enablement
    CME_MESSAGE_ID_ROLE_DOWN,               // following role de-activation, FW indication upon successful role removal

    CME_MESSAGE_ID_SCAN_PERIOD_COMPLETE,    // Scan period complete notification

    CME_MESSAGE_ID_SCAN_COMPLETE,           // Scan complete notification
    CME_MESSAGE_ID_SET_SCAN_CME_INFO,       // Request for preparing the scan/CME shared information.
                                            // CME allocates the memory and fills relevant information,
                                            // it may free the memory after handling scan results
                                            // (or use it for anothehr scan).
    CME_MESSAGE_ID_RX_MNG_PACK,             // Forward received packets to driver_cc33
                                            // (and from there maybe to supplicant)
    CME_MESSAGE_ID_CSA_NOTIFY,              // Notification on a new Channel Switch Announcement element
    CME_MESSAGE_ID_CS_FINISH,               // Channel Switch finish notification
    CME_MESSAGE_ID_RX_EAPOL_PACK,           // Forward received EAPOL packet to supplicant
    CME_MESSAGE_ID_RX_FROM_UNKNOWN,         // Notify supplicant that rx from unknown was received
    CME_MESSAGE_ID_MIC_FAILURE,             // Forward mic failure indication to supplicant
    CME_MESSAGE_ID_PN_REPLAY_DETECTED,      // PN replay attack was detected (AES/TKIP)
    CME_MESSAGE_ID_AES_SW_DECRYPTION_NEEDED, // HW AES decryption failed, SW decryption is needed.
    CME_MESSAGE_ID_TX_DONE,                 // Notify TX result to supplicant
    CME_MESSAGE_ID_ROC_TIMER_TIMEOUT,              // Notify supplicant if ROC or CROC was handled
    CME_MESSAGE_ID_EXT_ROC,                      // Notify CME to start ROC
    CME_MESSAGE_ID_EXT_CROC,                     // Notify CME to CROC
    CME_MESSAGE_ID_EXT_SEND_ACTION,         // Notify CME to send action frame


    CME_MESSAGE_ID_BSS_LOSS,                // Notify CME SM & supplicant
    CME_MESSAGE_ID_EXT_ROC_EVENT,               // Notify CME and supplicant ROC has started/completed
    CME_MESSAGE_ID_INACTIVITY,
    CME_MESSAGE_ID_MAX_RETRY,


    CME_MESSAGE_ID_WPA_SUPP_COMPLETED,      // STA / P2P supplicant operational link completion notification
    CME_MESSAGE_ID_WPA_SUPP_CONNECTING,     // STA / P2P supplicant connecting of link notification
    CME_MESSAGE_ID_WPA_SUPP_DISCONNECTED,   // STA / P2P supplicant disconnection of link notification
    CME_MESSAGE_ID_P2P_DEV_FOUND,           // P2P Device found notification
    CME_MESSAGE_ID_P2P_NEG_RECIEVED,        // P2P Negotiation request recieved from remote peer
    CME_MESSAGE_ID_P2P_NEG_CONFIRMATION,    // P2P Negotiation Confirmation notification - now we can tell which side is the GO and which side is the CLIENT
    CME_MESSAGE_ID_AUTH_SENT,               // STA/P2P_CL authentication request sent notification
    CME_MESSAGE_ID_WPS_HANDSHAKE_SUCCESS,   // STA WPS credentials handshake completed successfully
    CME_MESSAGE_ID_AUTH_TIMEOUT,            // STA/P2P_CL authentication/association timeout notification
    CME_MESSAGE_ID_ROLE_STOPPED,            // A role stop sequence was stopped in all L2 layers.
                                            // Must be received before a role can be disabled
    CME_MESSAGE_ID_START_AP_WPS_SESSION,    // Start AP WPS session according to parameters
    CME_MESSAGE_ID_SET_EXT_WPS_SESSION,     // Set external WPS session according to parameters

    // -------------------------------
    //  Supplicant events
    // -------------------------------
    CME_MESSAGE_ID_NEW_ELOOP_TIMEOUT,           // Used to update the timeout CME context waits for
                                                // messages; allows handling eloop events on time.
    CME_MESSAGE_ID_SUPPLICANT_PERIODIC,         // Periodic timer used for supplicant's maintenance and cleanup

    CME_MESSAGE_ID_UNPROTECTED_DEAUTH_DEASSOC,  //Used to inform supplicant of an unprotected deauth or disassoc frame
                                                //in a protected connection, pushed by lrxp
    // -------------------------------
    //  Supplicant notifiers
    // -------------------------------

        // Modify the original dbus notifiers in order to inform CME of supplicant events.
        // This includes p2p negotiation completion and selected role.

    // -------------------------------
    //  Timer notifiers
    // -------------------------------
    CME_MESSAGE_ID_FAST_CONNECTION_TIMEOUT,

    // -------------------------------
    //  DEINIT
    // -------------------------------
    CME_MESSAGE_ID_SUPP_DEINIT,
    CME_MESSAGE_ID_DEINIT,

    // -------------------------------
    //  external app events
    // -------------------------------
    CME_MESSAGE_EXT_APP_PROCESS_PROV_DISC_REQ,


    CME_MESSAGE_ID_ASSOCIATED,

    CME_MESSAGE_ID_BLE_ENABLED,

    CME_MESSAGE_ID_SCAN_DONE,  //scan stopped , can happen when user initiate disconnect

    CME_MESSAGE_ID_SET_NON_PREFFERED_CHANNELS,

    CME_MESSAGE_ID_SET_VENDOR_ELEMETS,

    CME_MESSAGE_ID_CONFIGURE_PEER_AGING_TIMEOUT,

    CME_MESSAGE_ID_PEER_AGING_SAMPLE_TIME,

    CME_MESSAGE_ID_SET_SCAN_DWELL_TIME,

    CME_MESSAGE_ID_SET_SCHED_SCAN_PLANS

} CmeMsgsIds_e;

// Scan module request for filling scan information
typedef struct
{
    cmeScanSharedInfo_t *pSharedInfo;   // pointer to information that should be set
    OsiSyncObj_t        *pSyncObj;      // sync object to be given when information is ready
    uint8_t /*EScanRequestType*/     aScanReqType;  // scan request type
} CmeScanSetInfo_t;

// Host site survey request
typedef struct
{
    uint8_t index;                        // index of the first network to report
    uint8_t count;                        // number of networks to report
    uint8_t getInternalEvent;             // if set, send an internal async event
    uint8_t padding[1];
    CMEWlanScanCommon_t ScanCommon;      //params for the scan like ssid list
} CmeGetNetworks_t;

// Host WLAN connect command
typedef struct
{
    CMEWlanConnectCommon_t *pConnectCmd;        // pointer to to received command
    CMEEapWlanConnect_t *pConnectEapCmd;  // pointer for eap connect command - relevant in EAP case only
    uint32_t                 keyMgmtType;         // parsed management key, bit msk defined
                                                // in supplicant code, WPA_KEY_MGMT_xxx
    uint8_t                  profiles_connection;
    uint8_t                  padding[2];
} CmeWlanConnect_t;

// Host WLAN set mode command
typedef struct
{
    uint32_t               role_bitmap;   // new role bitmap configuration
                                        //ROLE_STA/ROLE_AP/ROLE_P2P
    uint32_t               calledFromCmeThread;
} CmeWlanMode_t;

// RX packets
typedef struct
{
    void* pDesc;

} CmeTxRxPack_t;

//preferred network profile command (add/remove)
typedef struct
{
    CMEWlanAddGetProfile_t *Profile;
    int16_t                *pNewProfileIndex;
} CmeWlanProfile_t;

typedef struct
{
    WlanPolicySetGet_t policy;
}CmeWlanPolicy_t;


#define CHANNEL_SWITCH_ELEM_LEN         3
typedef uint8_t CmeChannelSwitchIE_t [CHANNEL_SWITCH_ELEM_LEN];

typedef union
{
    WlanProvDiscResp_t WlanProvDiscResp;
}CmeExtAppAction_t;

typedef struct
{
  uint8_t    macAddr[MAC_ADDR_LEN];
} CmeWlanApRemovePeer_t;

typedef struct
{
    uint32_t  duration;
    int32_t   freq;
    struct wpa_supplicant *wpa_s;
    uint32_t  is_croc_performed_due_to_timeout;
}CmeWlanRocParam_t;


typedef struct
{
    ti_driver_ifData_t     *pDrv;
    uint8_t                apDst[MAC_ADDRESS_LEN];            // Destination address
    uint8_t                *actionBuff;
    uint32_t                actionBuffLen;
}CmeWlanSendActionParam_t;

typedef struct
{
    RoleType_e roleType;
    uint16_t vendorElements_length;
    uint8_t* pVendorElements;
} CMEWlanSetVendorElements_t;


/* disconnect specific flags */
#define CME_GENERAL_DATA_DISCONNECT_IS_BSS_LOSS  (BIT_0)
#define CME_GENERAL_DATA_DISCONNECT_IS_USER_REQ  (BIT_1)



/* AP remove specific flags */
#define CME_GENERAL_DATA_AP_REMOVE_PEER_IS_USER_REQ (BIT_0)


/* Timeout to deinit supplicant */
#define CME_DEINIT_SUPP (OSI_WAIT_FOREVER)
// Structure of CME messages
typedef struct
{
    CmeMsgsIds_e   msgId;
    uint32_t       roleId;                // Optional, set only when relevant
    uint16_t       generalData;           // Serves for 2 byte data commands
    union
    {
        CmeScanDoneInfo_t       postScanInfo;
        CmeScanPeriodDoneInfo_t scanPeriodDoneInfo;
        CmeScanSetInfo_t        preScanInfo;
        CmeGetNetworks_t        getNetworks;
        CmeWlanConnect_t        wlanConnect;
        CmeTxRxPack_t           txRxPacket;
        CmeWlanMode_t           wlanMode;
        CmeWlanProfile_t        profile;
#if 0
        CmeWlanEapProfile_t     eapProfile;
#endif
        uint8_t                 deletedProfileIdx;

        CmeWlanPolicy_t         policy;

        CmeWlanApRemovePeer_t         apRemovePeer;
        CmeChannelSwitchIE_t          channelSwitchIe;
        CmeExtAppAction_t             extAppAction;
        wlanWpsSession_t              wpsSession;
        wlanSetExtWpsSession_t        wpsParams;
        CmeWlanRocParam_t             rocParam;
        CmeWlanSendActionParam_t      sendActionParam;
        WlanP2pConfigChannelParam_t   p2pConfigParams;
        WlanP2pGroupAddParam_t        p2pGroupAddParams; 
        WlanNonPrefChannels_t         nonPrefChannels;
        CMEWlanSetVendorElements_t    vendorElements;
        uint32_t                      peerAgingTimeout;
        WlanScanDwellTime_t            dwellTimes;

        WlanSetWpsApPinParam_t          wpsApPin;
        char *                   sched_scan_plans;

    } un;

} cmeMsg_t;

// Message queue configuration
#define MSGQ_MSG_SIZE        (sizeof(cmeMsg_t)) // size of messages
#define MSGQ_MAX_NUM_MSGS    (80)               // maximal number of messages the queue can hold
#define MSGQ_MAX_THRESHOLD   (MSGQ_MAX_NUM_MSGS-10) //Above this threshold, don't allow new messages to enter queue
                                                   //This is not checked for every message but it is relevant only to messages that can fill
                                                   //quickly the queue like management packets from peer devices
                                                   //(in AP role all management packets are going to Supplicant)

#define VALID_COUNTRY_CODE(pParam) ((pParam[0] == 'U' && pParam[1] == 'S') || (pParam[0] == 'E' && pParam[1] == 'U') || (pParam[0] == 'J' && pParam[1] == 'P'))

//#define CME_MSG_QUEUE_DEBUG

// ============================================================================
//      Modules data base
// ============================================================================

// Point to supplicant interface; to be used whenever activating supplicant APIs.
// If more than one interface is running, struct wpa_supplicant are connected
// in a link list (using their next field)
// !!! Must be stored in ULL memory !!!
struct wpa_global *gpSupplicantGlobals  = NULL;

//Timer for supplicant periodic tasks (cleanup)
//Using FW timer instead of eloop (osi timer) in order to not wake from sleep
// TODO: need to implement
#if 0
TimerEventInfo_t gSupplicantPeriodic_timerEvent ;
#endif
// Context TCB
// !!! Must be stored in ULL memory !!!
OsiThread_t gCmeThreadTcb= NULL ;

// Context message queue CB
// !!! Must be stored in ULL memory !!!
OsiMsgQ_t gCmeMessageQueue = NULL;

//
//hold last bssid connected in order to tell if ARP entries should be flushed
uint8_t               gCmeLastConnectedBssId[MAC_ADDR_LEN]  = {0,0,0,0,0,0};

//holds the last (and possibly existing) profile index connected, or CME_SCAN_MAX_PROFILES value in case ad-hoc is connected
int8_t                gCmeLastWlanProfileIdx  = -1;

// Message queue memory
// Statically allocated in GLX as it assumed transition to low power is allowed
// only if all queues are empty
uint8_t gEloopMessagegQueueMem[MSGQ_MSG_SIZE * MSGQ_MAX_NUM_MSGS]; //MEM_REGION_GLX, Make sure to request GLX retention in the cme main loop
                                                                 // before handling the commands

// CME  - Command blocking sync object
// users: Role activation sync object
//        add profile return index
//
OsiSyncObj_t gCmeCommandBlockingSyncObject = NULL;
OsiSyncObj_t gCmeThreadStarted = NULL;

OsiSyncObj_t gCmeCommandStopBlockingSyncObject = NULL;

OsiSyncObj_t gCmeThrdRunStopSyncObject = NULL;

uint8_t      gContRunThrdLoopCme = TRUE;
OsiSyncObj_t gThrdLoopStoppedCmeSync = NULL;
OsiSyncObj_t gCmeThrdDummySleep = NULL;
OsiSyncObj_t gCmeEapolsStaSyncObject = NULL;
OsiSyncObj_t gtxCompleteSyncObj = NULL;

extern volatile uint8_t gFwCrashOccurred;

/* save last disconnect info */
CMEWlanEventDisconnect_t  gLastDisconnectInfo ;


//Pending WLAN connect command
CmeWlanConnect_t gCme_PendingWlanConnect;


//CME manager role switch indicator
uint8_t gCmeRoleSwitchActive;

signal_role_change_state_done_t g_signal_role_change_state_done = { .cme_signalWhenRoleStateChanged =0,
                                                .cme_signalWhenRoleStateChanged_status= CME_SIGNAL_ROLE_CHNGE_STATUS_OK };

//os objects
// TODO need to implement
#if 0
//AP access list (see cme_ap_access_list.c)
extern cmeBwListCB_t*      gBwListCB ;
#endif
// Control block for the Private Info Elements.
cmePrivateIeCB_t*   gPrivateIeCB ; //Should be ULL since we use this to check if white list exists, even in STA role
                                                 //(user can set the private IE also when AP role is disabled. It is just
                                                 //written to the flash).
// Semaphore for atomic access to B/W list and Private IE.
OsiSyncObj_t*  gGeneralAccessSemaphore; //MEM_REGION_GLX relvant for AP only

StartRoleApps_t gRoleAppsParams;

// Control block for channel switch
cmd_channel_switch_t gCmdChannelSwitchStart;
// ============================================================================
//      Local Functions declarations
// ============================================================================
void cme_Thread(void* apParam);


static int32_t pushMsg2Queue(cmeMsg_t *apMsg);
static int32_t pushMsg2Queue_fromIntr(cmeMsg_t *apMsg);
static BOOLEAN isMsgQueueAboveThreshold();
static Bool32 isTxResultSafeToFilter (void *descriptor);
static Bool32 isRxMgmtFrameSafeToFilter (void *descriptor);
int32_t cmeMsgQueueCleanup (void);
int32_t cmeMsgQueueCleanupAll (void);
static int32_t validateWlanConnectParams(CMEWlanConnectCommon_t *apCmd);
#if CC35XX_ADD_SUPPORT_ENT_PROFILE
static int32_t cme_validate_eap_connection_params(uint8_t  SsidLen,
                                                  uint8_t  PasswordLen,
                                                  uint8_t  UserLen,
                                                  uint8_t  AnonUserLen,
                                                  uint8_t  CertIndex,
                                                  uint32_t EapBitmask,
                                                  uint8_t  do_validate_role);
#endif

static BOOLEAN isSameConnectParamsInProgress(CMEWlanConnectCommon_t *pCmdbuffer, CMEEapWlanConnect_t *pConnectEapCmd);


void CME_supplicantPeriodicTimerKick(void);
void CME_supplicantPeriodicActivities(void);
void CME_MsgFree(cmeMsg_t *apMsg);
#ifdef CME_MSG_QUEUE_DEBUG
static void cme_debug_print_cME_queue_content(cmeMsg_t *apMsg);
static void debug_print_msg_type_subtype(cmeMsg_t* msg);
#endif /* CME_MSG_QUEUE_DEBUG */
int32_t cme_update_ap_beacon_tx_power(ti_driver_ifData_t *pDrv, uint32_t roleId, int8_t tx_power);
int32_t cme_get_role_channel(WlanRole_e role, uint16_t *channelNum, uint32_t *roleId);

// ============================================================================
//      External Functions
// ============================================================================
/* WLAN event dispatcher to host */
extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t * args, uint16_t argsLen);

// ============================================================================
//      Exported Functions
// ============================================================================
// ----------------------------------------------------------------------------

void CME_SetStartedRoleBitmap(uint32_t role_bitmap)
{
    gRoleAppsParams.hostConfiguredRolesBitmap = role_bitmap;

    HOOK(HOOK_IN_CME);
}
// ----------------------------------------------------------------------------
uint32_t CME_GetStartedRoleBitmap()
{
    HOOK(HOOK_IN_CME);

    return gRoleAppsParams.hostConfiguredRolesBitmap ;
}
// ----------------------------------------------------------------------------

int32_t CME_SetTxPower(WlanTxPowerSet_t *params)
{
    int32_t ret = 0;
    WlanTxPowerSet_t *txPowerParams = params;
    uint16_t channelNum;
    uint32_t roleId;
    int8_t regulatory_max;
    int8_t actual_tx_power;
    ti_driver_ifData_t *pDrv;
    uint32_t role_bitmap = CME_GetStartedRoleBitmap();

    /* Check if role is up */
    if((ROLE_IS_TYPE_STA(txPowerParams->role) && (0 == (role_bitmap & BIT_x(ROLE_STA)))) ||
       (ROLE_IS_TYPE_AP(txPowerParams->role) && (0 == (role_bitmap & BIT_x(ROLE_AP)))))
    {
        CME_PRINT_REPORT_ERROR("\n\rThe specified role is not active.\n\r");
        ret = WlanError(WLAN_ERROR_SEVERITY__LOW,
                       WLAN_ERROR_MODULE__COMMANDS,
                       WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
        return ret;
    }

    /* Get current channel for the role */
    ret = cme_get_role_channel(txPowerParams->role, &channelNum, &roleId);
    if (ret != 0)
    {
        return ret;
    }

    /* Get driver instance now that roleId is known */
    pDrv = getDriverForRoleId(roleId, gpSupplicantGlobals);

    /* Get regulatory max power for this channel */
    if (!regulatoryDomain_getChMaxPower(channelNum, &regulatory_max))
    {
        CME_PRINT_REPORT_ERROR("\n\rFailed to get regulatory maximum TX power.\n\r");
        if (ret != 0)
        {
            return ret;
        }
    }

    /* Determine actual TX power to apply - cap to min(WLAN_MAX_TX_POWER_DBM, regulatory_max) */
    if (txPowerParams->tx_power_dbm > MIN(WLAN_MAX_TX_POWER_DBM, regulatory_max) || txPowerParams->tx_power_dbm < WLAN_MIN_TX_POWER_DBM)
    {
        actual_tx_power = MIN(WLAN_MAX_TX_POWER_DBM, regulatory_max);
        GTRACE(GRP_SL_DISPATCH, "CME_SetTxPower: invalid tx_power=%d dBm (valid range [%d, %d] dBm), using %d dBm",
               txPowerParams->tx_power_dbm, WLAN_MIN_TX_POWER_DBM, actual_tx_power, actual_tx_power);
    }
    else /* Use requested value*/
    {
        actual_tx_power = txPowerParams->tx_power_dbm;
    }

    /* Apply TX power to firmware*/
    if (pDrv)
    {
        regulatoryDomain_setRoleMaxTxPower(pDrv, actual_tx_power);
        if (pDrv->fwMaxTxPower == actual_tx_power)
        {
            CME_PRINT_REPORT_ERROR("\n\rTX power set to %d dBm for role %d (channel %d).\n\r",
                   actual_tx_power, roleId, channelNum);
            /* Update beacon for AP role to advertise new TX power */
#ifndef TI_STA_ONLY_BUILD
            if (ROLE_IS_TYPE_AP(txPowerParams->role))
            {
                ret = cme_update_ap_beacon_tx_power(pDrv, roleId, actual_tx_power);
            }
#endif
        }
        else
        {
            CME_PRINT_REPORT_ERROR("\n\rFailed to set TX power");
            ret = -1;
        }
    }
    else
    {
        CME_PRINT_REPORT_ERROR("\n\rFailed to get driver instance for role %d.\n\r", roleId);
        ret = -1;
    }
    return ret;
}
// ----------------------------------------------------------------------------
#ifndef TI_STA_ONLY_BUILD
int32_t cme_update_ap_beacon_tx_power(ti_driver_ifData_t *pDrv, uint32_t roleId, int8_t tx_power)
{
    struct hostapd_hw_modes *mode;
    struct hostapd_data *hapd;
    struct wpa_supplicant *wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);
    int current_channel;

    if (!wpa_s || !wpa_s->ap_iface || !wpa_s->ap_iface->bss[0])
    {
        CME_PRINT_REPORT_ERROR("\n\rWarning: AP iface not available for beacon update.\n\r");
        return -1;
    }

    hapd = wpa_s->ap_iface->bss[0];

    pDrv->configuredApTxPower = tx_power;

    if (hapd->iface && hapd->iface->current_mode && hapd->iconf)
    {
        mode = hapd->iface->current_mode;
        current_channel = hapd->iconf->channel;
        for (int i = 0; i < mode->num_channels; i++)
        {
            if (mode->channels[i].chan == current_channel)
            {
                mode->channels[i].max_tx_power = tx_power;
                break;
            }
        }
    }

    if (wpa_supplicant_ap_update_beacon(wpa_s) < 0)
    {
        CME_PRINT_REPORT_ERROR("\n\rWarning: Failed to update beacon with new TX power.\n\r");
        return -1;
    }
    return 0;
}
#endif
// ----------------------------------------------------------------------------
int32_t cme_get_role_channel(WlanRole_e role, uint16_t *channelNum, uint32_t *roleId)
{
    int32_t freq;
    uint8_t band;
    Channel_e channel;
    ti_driver_ifData_t *pDrv;
    if (ROLE_IS_TYPE_STA(role))
    {
        if (!CmeStationFlowIsConnected())
        {
            CME_PRINT_REPORT_ERROR("\n\rSTA must be connected to get channel for role.\n\r");
            return -1;
        }
        *roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_STA);
    }
    else if (ROLE_IS_TYPE_AP(role))
    {
        *roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_AP);
    }
    else
    {
        CME_PRINT_REPORT_ERROR("\n\rInvalid role %d.\n\r", role);
        return -1;
    }
    pDrv = getDriverForRoleId(*roleId, gpSupplicantGlobals);
    freq = pDrv->freq;
    if (freq_to_chan(freq, &channel, &band) < 0)
    {
        CME_PRINT_REPORT_ERROR("\n\rFailed to get channel for role.\n\r");
        return -1;
    }
    *channelNum = (uint8_t)channel;
    return 0;
}
// ----------------------------------------------------------------------------

int32_t CME_GetTxPower(WlanTxPowerGet_t *params)
{
    WlanTxPowerGet_t *txPowerGet = params;
    ti_driver_ifData_t *pDrv;
    uint32_t roleId;
    int32_t ret;
    uint32_t role_bitmap = CME_GetStartedRoleBitmap();

    /* Check if role is up */
    if((ROLE_IS_TYPE_STA(txPowerGet->role) && (0 == (role_bitmap & BIT_x(ROLE_STA)))) ||
       (ROLE_IS_TYPE_AP(txPowerGet->role) && (0 == (role_bitmap & BIT_x(ROLE_AP)))))
    {
        CME_PRINT_REPORT_ERROR("\n\rThe specified role is not active.\n\r");
        ret = WlanError(WLAN_ERROR_SEVERITY__LOW,
                       WLAN_ERROR_MODULE__COMMANDS,
                       WLAN_ERROR_TYPE__INVALID_PARAM_GET_TYPE);
        return ret;
    }

    /* Determine role type */
    if (ROLE_IS_TYPE_STA(txPowerGet->role))
    {
        if (!CmeStationFlowIsConnected())
        {
            CME_PRINT_REPORT_ERROR("\n\rTX power is available only when station is connected.\n\r");
            ret = WlanError(WLAN_ERROR_SEVERITY__LOW,
                           WLAN_ERROR_MODULE__COMMANDS,
                           WLAN_ERROR_TYPE__INVALID_PARAM_GET_TYPE);
            return ret;
        }
        roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_STA);
    }
    else if (ROLE_IS_TYPE_AP(txPowerGet->role))
    {
        roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_AP);
    }
    else
    {
        CME_PRINT_REPORT_ERROR("\n\rCME_GetTxPower: invalid role %d\n\r", txPowerGet->role);
        ret = WlanError(WLAN_ERROR_SEVERITY__LOW,
                         WLAN_ERROR_MODULE__COMMANDS,
                         WLAN_ERROR_TYPE__INVALID_ROLE);
        return ret;
    }
    /* Get driver instance and read fwMaxTxPower */
    pDrv = getDriverForRoleId(roleId, gpSupplicantGlobals);
    if (pDrv)
    {
        txPowerGet->tx_power_dbm = pDrv->fwMaxTxPower;
    }
    else
    {
        CME_PRINT_REPORT_ERROR("\n\rFailed to get driver instance for role.\n\r");
        ret = WlanError(WLAN_ERROR_SEVERITY__LOW,
                       WLAN_ERROR_MODULE__COMMANDS,
                       WLAN_ERROR_TYPE__INVALID_PARAM_GET_TYPE);
        return ret;
    }
    return 0;
}

void CME_SetPowerSaveMode(uint8_t power_save)
{
    gRoleAppsParams.devicePowerSaveMode = power_save;

    HOOK(HOOK_IN_CME);
}
uint8_t CME_GetPowerSaveMode()
{
    HOOK(HOOK_IN_CME);

    return gRoleAppsParams.devicePowerSaveMode;
}
// ----------------------------------------------------------------------------
#ifndef TI_STA_ONLY_BUILD
int CME_SetApParams(void *apParams)
{
    return CmeSetApParams(apParams);
}
#endif
// ----------------------------------------------------------------------------
void CME_SetStaParams(void *staParams)
{
    CmeSetStaParams(staParams);
}
// ----------------------------------------------------------------------------
void CME_NotifyStaConnectionState(uint32_t aRoleId, LinkConnectionState_e aConnectionState, uint16_t aReasonCode)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    switch (aConnectionState)
    {
    case LINK_CONNECTION_STATE_CONNECTED:

#ifdef CC33XX_CME_DEBUG
        NOTIFY_STA_CONNECTED();
#endif
        msg.msgId = CME_MESSAGE_ID_WPA_SUPP_COMPLETED;

    break;

    case LINK_CONNECTION_STATE_CONNECTING:
        msg.msgId = CME_MESSAGE_ID_WPA_SUPP_CONNECTING;
        break;

    case LINK_CONNECTION_STATE_DISCONNECTED:

#ifdef CC33XX_CME_DEBUG
        NOTIFY_STA_DISCONNECTED();
#endif
        /* save last disconnect info..*/

        /* fetch data from last ssid connected */
        if (gpSupplicantGlobals->ifaces != NULL)
        {
           if (gpSupplicantGlobals->ifaces->last_ssid != NULL)
           {
               gLastDisconnectInfo.SsidLen = gpSupplicantGlobals->ifaces->last_ssid->ssid_len;


               if (gpSupplicantGlobals->ifaces->last_ssid->ssid != NULL)
               {
                   os_memcpy(gLastDisconnectInfo.SsidName,
                             gpSupplicantGlobals->ifaces->last_ssid->ssid,
                             gLastDisconnectInfo.SsidLen);
               }
               else
               {
                   GTRACE(GRP_GENERAL_ERROR, "gpSupplicantGlobals->ifaces->last_ssid->ssid is NULL");
               }

               /* copy the mac address */
               os_memcpy(gLastDisconnectInfo.Bssid, gpSupplicantGlobals->ifaces->bssid, ETH_ALEN);
           }
           else
           {
               GTRACE(GRP_GENERAL_ERROR, "gpSupplicantGlobals->ifaces->last_ssid is NULL");
           }
        }
        GTRACE(GRP_CME,"LINK_CONNECTION_STATE_DISCONNECTED ,send CME_MESSAGE_ID_WPA_SUPP_DISCONNECTED ");
        CME_PRINT_REPORT("\n\rLINK_CONNECTION_STATE_DISCONNECTED send CME_MESSAGE_ID_WPA_SUPP_DISCONNECTED ");

        msg.msgId = CME_MESSAGE_ID_WPA_SUPP_DISCONNECTED;
        break;
    case LINK_CONNECTION_STATE_DISCONNECTING:
        break;

    case LINK_CONNECTION_STATE_ASSOCIATED:
        msg.msgId = CME_MESSAGE_ID_ASSOCIATED;
        break;

    default:
        break;
    }

    msg.roleId = aRoleId;
    msg.generalData = aReasonCode;

    HOOK(HOOK_IN_CME);

    pushMsg2Queue(&msg);

}

/* ----------------------------------------------------------------------------
 CME_notifyScanDone
      This function pushes a message to the cME queue to notify about scan done
Parameters:    aRoleId - ID of the reporting role
Return code:
---------------------------------------------------------------------------- */
void CME_notifyScanDone(uint32_t aRoleId)
{
    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_SCAN_DONE;
    msg.roleId = aRoleId;
    msg.generalData = 0;

    pushMsg2Queue(&msg);

}


/* ----------------------------------------------------------------------------
 CME_fastConnectTimerRelease
      This function pushes a message with fast connection timeout notifier to the
      queue.
      this command is asking the CME to release the timer resources as it is called from timer context.
 Parameters:
 Return code:
---------------------------------------------------------------------------- */
void CME_fastConnectTimerRelease()
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;
    msg.msgId = CME_MESSAGE_ID_FAST_CONNECTION_TIMEOUT;

    pushMsg2Queue(&msg);
}

void CME_SuppDeinit(uint32_t timeout)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;
    msg.msgId = CME_MESSAGE_ID_SUPP_DEINIT;

    //clear previous blocking sync object (this command is blocking)

    if (OSI_INVALID_PARAMS == osi_SyncObjClear(&gCmeCommandStopBlockingSyncObject))

    {
        ASSERT_GENERAL(0);
    }

    pushMsg2Queue(&msg);

    if (OSI_OK!=osi_SyncObjWait(&gCmeCommandStopBlockingSyncObject, timeout))

    {
        ASSERT_GENERAL(timeout!=OSI_WAIT_FOREVER);//ASSERT_GENERAL only if timeout is set to FOREVER, otherwise it is legal
        GTRACE(GRP_SL_DISPATCH, "CME_SuppDeinit : Got CME role switch TIMEOUT! carry on");
    }
}

// ----------------------------------------------------------------------------
int32_t CME_GetScanResults(uint32_t aIndex, uint32_t aCount, uint8_t aGetInternalEvent, CMEWlanScanCommon_t* pScanCommon)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;
    int32_t status  = 0;


    if (
        (gCmeRoleSwitchActive != FALSE)// active role switch
            ||
        (CME_SITE_SURVEY_IDLE != gSetSiteSurvey) //site survey running
            ||
        (!cme_is_sta_role_like_activated() && !cme_is_ap_role_like_activated() && !cme_is_device_role_like_activated())//no AP or STA role active or DEVICE
       )
    {
        GTRACE(GRP_SL_DISPATCH,"ERROR! blocking CME_GetScanResults: RoleSwitchActive=%d, SiteSurveyRunning=%d, sta_role_active=%d, ap_role_active=%d, device_role_active=%d",
               gCmeRoleSwitchActive,
               gSetSiteSurvey,
               cme_is_sta_role_like_activated(),
               cme_is_ap_role_like_activated(),
               cme_is_device_role_like_activated()
               );
        if (!cme_is_sta_role_like_activated() && !cme_is_ap_role_like_activated() && !cme_is_device_role_like_activated()) //no AP or STA role active
        {
            status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_NO_ROLE_ACTIVE);
        }
        else if (gCmeRoleSwitchActive != FALSE) // active role switch
        {
            status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_ACTIVE_ROLE_SWITCH);
        }
        else //site survey running
        {
            status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_SITE_SURVEY_RUNNING);
        }

    }
    // We can only indicate up to 31 results because in the driver side, we only have bits 0-4
    // of the AdditionalData field which is used to return the number of results.
    else if((aCount - aIndex) > (32 - 1))
    {
        CME_PRINT_REPORT_ERROR("\n\rWlan_Scan failed request results can be up to 31: aCount: %d aIndex:%d",aCount,aIndex);
        status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_INVALID_PARAM);
    }
    else
    {
        //  scan shall be triggered from CME context
        msg.msgId = CME_MESSAGE_ID_GET_SCAN_RESULTS;
        msg.un.getNetworks.index = aIndex;
        msg.un.getNetworks.count = aCount;
        msg.un.getNetworks.getInternalEvent = aGetInternalEvent;
        os_memset((void *) &msg.un.getNetworks.ScanCommon, 0, sizeof(CMEWlanScanCommon_t));
        if(pScanCommon != NULL)
        {
            os_memcpy((void *) &msg.un.getNetworks.ScanCommon, (void *)pScanCommon, sizeof(CMEWlanScanCommon_t));
        }

        pushMsg2Queue(&msg);
    }

    return status;
}

//call cme to handle TX of action message from ext application
int32_t CME_WlanExtP2pProcessProvDiscActionMsg(WlanActionParam_t* actionBuff, uint8_t requestByHost)
{
    cmeMsg_t msg;
    int32_t status = WLAN_RET_CODE_OK;

    if(!isextP2P())
    {
        CME_PRINT_REPORT("\n\rERROR!! ext APP is not enabled");
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__EXT_APP_NOT_ENABLED);
    }

    msg.un.extAppAction.WlanProvDiscResp.provDiscReqData = os_malloc(actionBuff->ProvDiscResp.provDiscReqLen);
    // In case of allocation failure send error indication to host
    if (NULL == msg.un.extAppAction.WlanProvDiscResp.provDiscReqData)
    {
        status = WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__MALLOC);
        CME_PRINT_REPORT("\n\rERROR!! CME:allocation of pCmd failed");
    }
    else
    {
        msg.un.extAppAction.WlanProvDiscResp.msgType =  actionBuff->ProvDiscResp.msgType;
        msg.un.extAppAction.WlanProvDiscResp.roleId =   actionBuff->ProvDiscResp.roleId;

        msg.un.extAppAction.WlanProvDiscResp.status = actionBuff->ProvDiscResp.status;
        os_memcpy(msg.un.extAppAction.WlanProvDiscResp.provDiscReqSa,actionBuff->ProvDiscResp.provDiscReqSa,6);

        os_memcpy(msg.un.extAppAction.WlanProvDiscResp.provDiscReqData ,actionBuff->ProvDiscResp.provDiscReqData,actionBuff->ProvDiscResp.provDiscReqLen);
        msg.un.extAppAction.WlanProvDiscResp.provDiscReqLen = actionBuff->ProvDiscResp.provDiscReqLen;
        msg.un.extAppAction.WlanProvDiscResp.provDiscReqRxFreq = actionBuff->ProvDiscResp.provDiscReqRxFreq;

        msg.msgId = CME_MESSAGE_EXT_APP_PROCESS_PROV_DISC_REQ;


        msg.generalData = 0;
        msg.roleId = actionBuff->ProvDiscResp.roleId;
        if (requestByHost)
        {
            //indicates if this request has been asked by host/user
            msg.generalData |= CME_GENERAL_DATA_CONNECT_IS_USER_REQ;
        }

        pushMsg2Queue(&msg);
    }
    return status;
}

// ----------------------------------------------------------------------------
TMacAddr     g_fuse_mac_addr[6]= {
                        {0},//STA mac
                        {0},//BLE role
                        {0},//P2P Devicr
                        {0},//AP/P2PGO mac
                        {0},
                        {0}};

int16_t CME_GetMacAddress(uint32_t roleType, uint8_t *pMacAddress)
{
    /*get mac address from  g_fuse_mac_addr */
    switch (roleType)
    {
        case WLAN_ROLE_STA:
            os_memcpy(pMacAddress, g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_STA], MAC_ADDR_LEN);
            break;

        case WLAN_ROLE_AP:
        case WLAN_ROLE_P2P_GO:
            os_memcpy(pMacAddress, g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_AP], MAC_ADDR_LEN);
            break;

        case WLAN_ROLE_DEVICE:
            os_memcpy(pMacAddress, g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_DEVICE], MAC_ADDR_LEN);
            break;

        case WLAN_ROLE_P2P_CL:
            os_memcpy(pMacAddress, g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_AP], MAC_ADDR_LEN);
            break;

        default:
            return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_RET_CODE_DEV_NOT_STARTED);
            break;
    }

    return 0;
}

// ----------------------------------------------------------------------------

int16_t CME_SetMacAddress(uint32_t roleType, uint8_t *pMacAddress)
{
    HOOK(HOOK_IN_CME);

    if(IRQ_UtilIsZeroMacAddress(pMacAddress))
    {
        GTRACE(GRP_GENERAL_ERROR, "CME_SetMacAddress zero is not supported !");
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_INVALID_MAC_ADDR);
    }

    /*Set mac address from  g_fuse_mac_addr */
    if (WLAN_ROLE_STA == roleType)
    {
        IRQ_UtilCopyMacAddress(pMacAddress, g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_STA]);
        return 0;
    }
    else if (WLAN_ROLE_AP == roleType)
    {
        IRQ_UtilCopyMacAddress(pMacAddress, g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_AP]);
        return 0;
    }
    else if (WLAN_ROLE_P2P_GO == roleType)
    {
        //WLAN_MAC_OFFSET_ROLE_P2P_GO is same mac as the WLAN_MAC_OFFSET_ROLE_AP
        IRQ_UtilCopyMacAddress(pMacAddress, g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_P2P_GO]);
        return 0;

    }
    else if (WLAN_ROLE_DEVICE == roleType)
    {
        IRQ_UtilCopyMacAddress(pMacAddress, g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_DEVICE]);
        return 0;
    }
    else
    {
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_RET_CODE_DEV_NOT_STARTED);
    }

    GTRACE(GRP_GENERAL_ERROR, "CME_SetMacAddress is changed for %s to apply the change role down - role up!", roleType?"ROLE_AP":"ROLE_STA");


    return 0;
}

// ----------------------------------------------------------------------------
extern device_info_t gDevice_info;
int16_t CME_GetDeviceInfo(device_info_t *pDeviceInfo)
{

    /*only if gDevice_info is available*/
    if (gDevice_info.struct_is_updateed)
    {
        os_memcpy(pDeviceInfo ,&gDevice_info, sizeof(device_info_t));
    }

    return 0;

}

// ----------------------------------------------------------------------------
int32_t CME_WlanSetMode(uint8_t calledFromCmeThread,uint32_t role_bitmap, uint32_t timeout, BOOLEAN updateSetModeFlash)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;
    int32_t ret = 0;
    uint32_t originalStartedRoleBitmap = CME_GetStartedRoleBitmap();

    if (role_bitmap == 0xFF)
    {
        GTRACE(GRP_SL_DISPATCH, "CME_WlanSetMode : ERROR - invalid role %d",role_bitmap);
        CME_PRINT_REPORT("\r\nCME_WlanSetMode : ERROR - invalid role %d",role_bitmap);
        return WlanError(WLAN_ERROR_SEVERITY__LOW,
                         WLAN_ERROR_MODULE__CME,
                         WLAN_ERROR_TYPE__INVALID_ROLE);
    }

    // CME manager sanity check
    if (CME_GetStartedRoleBitmap() == role_bitmap)
    {
        GTRACE(GRP_SL_DISPATCH, "CME_WlanSetMode: nothing to do, role "
                                "bitmap 0x%x is already set, exit func",
                                role_bitmap);
        CME_PRINT_REPORT("\r\nCME_WlanSetMode: nothing to do, role bitmap "
                         "0x%x is already set, exit func\n\r", role_bitmap);
        /************************************************************
         *  EARLY EXIT POINT - requested role bitmap is already set!
         ***********************************************************/
        return 0;
    }

    if (gCmeRoleSwitchActive != FALSE)
    {
        // Impossible - role switch should hold the command mailbox until its done
    	CME_PRINT_REPORT_ERROR("\r\nCME_WlanSetMode: ERROR! " 
                               "rgCmeRoleSwitchActive != FALSE, "
                               "gCmeRoleSwitchActive:%d\n\r",
                               gCmeRoleSwitchActive);
        return WlanError(WLAN_ERROR_SEVERITY__LOW,
                         WLAN_ERROR_MODULE__CME,
                         WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);
    }

    GTRACE(GRP_SL_DISPATCH, "CME_WlanSetMode : CME mode set role bitmap 0x%x",
                            role_bitmap);

    CME_SetStartedRoleBitmap(role_bitmap);

    GTRACE(GRP_SL_DISPATCH, "CME_WlanSetMode cont ---");
    CME_PRINT_REPORT("\r\nCME_WlanSetMode cont ---");

    // Must be set here, just before sending "CME_MESSAGE_ID_NEW_ROLE_SET" command,
    // since this function releases the context and CME context also looks at this
    // global and starts role switch internally, before we wait here on the sync object.
    gCmeRoleSwitchActive = TRUE;

    g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status = CME_SIGNAL_ROLE_CHNGE_STATUS_OK;

    if (!calledFromCmeThread)
    {
        // Prepare role set command
        msg.msgId                   = CME_MESSAGE_ID_NEW_ROLE_SET;
        msg.un.wlanMode.role_bitmap = role_bitmap;
        msg.un.wlanMode.calledFromCmeThread = calledFromCmeThread;

        HOOK(HOOK_IN_CME);

        pushMsg2Queue(&msg);

		GTRACE(GRP_SL_DISPATCH, "CME_WlanSetMode: triggered CME with role "
                                "switch request, wait for completion, timeout:"
                                " %lu\r\n", timeout);
        CME_PRINT_REPORT("\n\rCME_WlanSetMode: send to CME with role switch "
                         "request, wait for completion, timeout: %lu \r\n",
                         timeout);
        
        // Wait on sync object - new role set operation must block command mailbox!
		ret = osi_SyncObjWait(&gCmeCommandBlockingSyncObject, timeout);
	    if (OSI_OK != ret)
	    {
	        ASSERT_GENERAL(timeout != OSI_WAIT_FOREVER);
	        GTRACE(GRP_SL_DISPATCH, "CME_WlanSetMode : Got CME role switch TIMEOUT! carry on");
            CME_PRINT_REPORT_ERROR("\n\rCME_WlanSetMode : Got CME role switch TIMEOUT! carry on\n\r");

			return WlanError(WLAN_ERROR_SEVERITY__LOW,
                             WLAN_ERROR_MODULE__CME,
                             WLAN_ERROR_TYPE__HOST_RESPONSE_TIMEOUT_IN_PRGRESS);
	    }
	    // If role up has timed out, it means that it failed during the supplicant_run_ap/sta
	    else if (g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status != CME_SIGNAL_ROLE_CHNGE_STATUS_OK)
	    {
            CME_PRINT_REPORT_ERROR("\n\rCME_WlanSetMode : Got role switch error\r\n");
            CME_SetStartedRoleBitmap(originalStartedRoleBitmap);

			return WlanError(WLAN_ERROR_SEVERITY__LOW,
                             WLAN_ERROR_MODULE__CME,
                             WLAN_ERROR_TYPE__HOST_RESPONSE_STATUS_ERROR);
	    }
	    else
	    {
	        GTRACE(GRP_SL_DISPATCH, "CME_WlanSetMode : Got CME role switch acknowledgments, role switch completed");
	        CME_PRINT_REPORT("\n\rCME_WlanSetMode : Got CME role switch acknowledgments, role switch completed\r\n");
	    }

	    HOOK(HOOK_IN_CME);
    }
    else
    {
        int role_switch_rc;

        GTRACE(GRP_CME, "CME_WlanSetMode, calledFromCmeThread");
        CME_PRINT_REPORT("\r\nCME_WlanSetMode: deactivate and activate roles");

        // New role set request - must be set in command
        gCme_PendingWlanConnect.pConnectCmd = NULL;

        // gCmeRoleSwitchActive can be false in case the role switch was
        // initiated internally by CME
        if (gCmeRoleSwitchActive == TRUE)
        {
        	uint8_t signalEvent  = !calledFromCmeThread;
            uint32_t activationBitmap = BIT_x(ROLE_STA) | BIT_x(ROLE_AP) | BIT_x(ROLE_DEVICE);

            role_switch_rc = cme_role_switch_manager(CmeStationFlow_GetCurrentUser(),
                                                     activationBitmap,
                                                     signalEvent /*if role switch done signal event*/);
            if (role_switch_rc == 0)
            {
                // In case role activation completed - try profile search
                cmeProfileManagerConfigChange(0, CALLER2);
            }

            // Use this global flag to find out if role state change was successful.
            // In case of error, restore original started roles bitmap.
            if (g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status != CME_SIGNAL_ROLE_CHNGE_STATUS_OK)
            {
                CME_SetStartedRoleBitmap(originalStartedRoleBitmap);
            }
        }

		GTRACE(GRP_SL_DISPATCH, "CME_WlanSetMode :  role_switch_rc:%d",role_switch_rc);
		CME_PRINT_REPORT_ERROR("\n\rCME_WlanSetMode : role_switch_rc:%d\r\n", role_switch_rc);
    }

    return WLAN_RET_CODE_OK;
}

// ----------------------------------------------------------------------------
int16_t CME_WlanSetPSMode(uint8_t aMode)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    if(NULL == gpSupplicantGlobals)
    {
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_RET_CODE_DEV_NOT_STARTED);
    }

    if(CME_GetPowerSaveMode() == aMode)
    {
        GTRACE(GRP_GENERAL_ERROR, "CME_WlanSetPSMode: Power save %d already set", aMode);
        CME_PRINT_REPORT_ERROR("\n\rCME_WlanSetMode : Power save %d already set\n\r", aMode);
        return 0;
    }

    // set new power save mode
    CME_SetPowerSaveMode(aMode);

    // prepare PS command
    msg.msgId                   = CME_MESSAGE_ID_PS_SET;


    return pushMsg2Queue(&msg);
}
// ----------------------------------------------------------------------------
int16_t CME_StartApWpsSession(wlanWpsSession_t *wpsSession)
{
    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_START_AP_WPS_SESSION;
    os_memcpy(&(msg.un.wpsSession), wpsSession, sizeof(wlanWpsSession_t));

    return pushMsg2Queue(&msg);
}

int16_t CME_SetExtWpsSession(wlanSetExtWpsSession_t *wpsParams)
{
    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_SET_EXT_WPS_SESSION;
    os_memcpy(&(msg.un.wpsParams), wpsParams, sizeof(wlanSetExtWpsSession_t));

    return pushMsg2Queue(&msg);
}

int16_t CME_SetBLE_Enable()
{
    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_BLE_ENABLED;

    return pushMsg2Queue(&msg);
}

int16_t CME_SetScanDwellTime(WlanScanDwellTime_t* dwellTimes)
{
    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_SET_SCAN_DWELL_TIME;
    os_memcpy(&(msg.un.dwellTimes), dwellTimes, sizeof(WlanScanDwellTime_t));
    
    return pushMsg2Queue(&msg);
}

int16_t CME_SetP2pCmd(WlanP2pCmd_t *p2pCmdParams)
{
    cmeMsg_t msg;

    int16_t ret = 0;

    msg.msgId = CME_MESSAGE_ID_P2P_CMD;
    msg.generalData = p2pCmdParams->Id;
    if (p2pCmdParams->Id == P2P_CMD_ID_CONFIG_CHANNELS)
    {
        Bool32 isDfsChannel = FALSE;

        msg.un.p2pConfigParams.operChannel   = p2pCmdParams->Data.cfgParams.operChannel;
        msg.un.p2pConfigParams.operClass     = p2pCmdParams->Data.cfgParams.operClass;
        msg.un.p2pConfigParams.listenChannel = p2pCmdParams->Data.cfgParams.listenChannel;
        msg.un.p2pConfigParams.listenClass   = p2pCmdParams->Data.cfgParams.listenClass;
        msg.un.p2pConfigParams.goIntent      = p2pCmdParams->Data.cfgParams.goIntent;

       //Check validity of operating channel
        if (p2pCmdParams->Data.cfgParams.operChannel != 0)
		{
			ret = regulatoryDomain_IsChannelSupported(p2pCmdParams->Data.cfgParams.operChannel, &isDfsChannel);
			if (ret == 0)
			{
				CME_PRINT_REPORT_ERROR("\r\nP2P device set channel failed: "
									   "operating channel not "
									   "supported");
				return WlanError(WLAN_ERROR_SEVERITY__LOW,
								 WLAN_ERROR_MODULE__COMMANDS,
								 WLAN_ERROR_TYPE__INVALID_PARAM_CHANNEL);
			}
	
			if (isDfsChannel)
			{
				CME_PRINT_REPORT_ERROR("\r\nP2P device set chennel failed: "
									   "Operating channel must "
									   "not be a DFS channel");
				return WlanError(WLAN_ERROR_SEVERITY__LOW,
								 WLAN_ERROR_MODULE__COMMANDS,
								 WLAN_ERROR_TYPE__INVALID_PARAM_CHANNEL);
			}
		}
    }
    else if (p2pCmdParams->Id == P2P_CMD_ID_GROUP_ADD)
    {
        uint32_t postfixLen = strlen(p2pCmdParams->Data.groupAddParams.ssidPostfix);

        if (postfixLen >= sizeof(msg.un.p2pGroupAddParams.ssidPostfix))
        {
            CME_PRINT_REPORT_ERROR("\r\np2p_group_add: SSID postfix exceeds maximum length");
            return WlanError(WLAN_ERROR_SEVERITY__LOW,
                           WLAN_ERROR_MODULE__COMMANDS,
                           WLAN_ERROR_TYPE__INVALID_PARAM_NAME);
        }
        
        if (CME_GetStartedRoleBitmap() & BIT_x(ROLE_AP))
        {
            CME_PRINT_REPORT_ERROR("\r\nCME_SetP2pCmd: p2p_group_add rejected - AP role is active");

              return WlanError(WLAN_ERROR_SEVERITY__LOW,
                               WLAN_ERROR_MODULE__COMMANDS,
                               WLAN_ERROR_TYPE__ROLE_NOT_SUPPORTED);
        }
        msg.un.p2pGroupAddParams.freq    = p2pCmdParams->Data.groupAddParams.freq;
        os_memcpy(msg.un.p2pGroupAddParams.ssidPostfix,
                p2pCmdParams->Data.groupAddParams.ssidPostfix,
                postfixLen + 1);
    }
    
    return pushMsg2Queue(&msg);
}


int16_t CME_SetNonPrefferedChannels(WlanNonPrefChannels_t *pNonPrefChannels)
{
    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_SET_NON_PREFFERED_CHANNELS;

    if (NULL != pNonPrefChannels->channel_list)
    {
        uint8 listLen = strlen(pNonPrefChannels->channel_list);
        msg.un.nonPrefChannels.channel_list = os_zalloc(listLen + 1);

        if (NULL == msg.un.nonPrefChannels.channel_list)
        {
            return -1;
        }

        os_memcpy(msg.un.nonPrefChannels.channel_list, pNonPrefChannels->channel_list, listLen);
    }
    else
    {
        msg.un.nonPrefChannels.channel_list = NULL;
    }
    
    return pushMsg2Queue(&msg);
}

// ----------------------------------------------------------------------------
int16_t CME_GetConnectionScanEarlyTermination()
{
    return gConnectionScanEarlyTerminationEnabled;
}

// ----------------------------------------------------------------------------
int16_t CME_SetConnectionScanEarlyTermination(uint8_t enable)
{
    gConnectionScanEarlyTerminationEnabled = enable;
    return 0;
}

// ----------------------------------------------------------------------------
int16_t CME_SetConnPolicy(WlanPolicySetGet_t *new_policy)
{
    cmeMsg_t msg;


    cmeMngSetConnectionPolicy( 0 , //any p2p - not suported
                               0 , //open policy - not suported 
                                new_policy->fastPolicy,
                                new_policy->autoPolicy,
                                new_policy->fastPersistant);

    msg.msgId = CME_MESSAGE_ID_POLICY_SET;
    msg.un.policy.policy.fastPolicy = new_policy->fastPolicy;
    msg.un.policy.policy.autoPolicy = new_policy->autoPolicy;
    msg.un.policy.policy.fastPersistant = new_policy->fastPersistant;

    return pushMsg2Queue(&msg);

}

int16_t CME_GetConnPolicy(WlanPolicySetGet_t *policy)
{
    CME_GetConnectionPolicy(NULL, &policy->fastPolicy, &policy->autoPolicy, NULL, &policy->fastPersistant);
    return 0;
}


int16_t CME_SetWpsApPin(WlanSetWpsApPinParam_t *pWpsApPinParams)
{
    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_SET_WPS_AP_PIN;
    
    os_memcpy(&(msg.un.wpsApPin), pWpsApPinParams, sizeof(WlanSetWpsApPinParam_t));

    return pushMsg2Queue(&msg);
}

// ----------------------------------------------------------------------------

int16_t CME_SetSchedScanPlans(char *sched_scan_plans)
{
    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_SET_SCHED_SCAN_PLANS;

    if (NULL == sched_scan_plans)
    {
        return -1;
    }

    uint8 len = strlen(sched_scan_plans);
    msg.un.sched_scan_plans = os_zalloc(len + 1);

    if (NULL == msg.un.sched_scan_plans)
    {
        return -1;
    }

    os_memcpy(msg.un.sched_scan_plans, sched_scan_plans, len);
    
    return pushMsg2Queue(&msg);
}

// ----------------------------------------------------------------------------

/* Sec type to key management type LUT */
static const uint32_t SecTypeToWPAkey_lut[] = {
/* (0)  WLAN_SEC_TYPE_OPEN  */            WPA_KEY_MGMT_NONE,
/* (1)  WLAN_SEC_TYPE_WEP  */             WPA_KEY_MGMT_NONE,
/* (2)  WLAN_SEC_TYPE_WPA_WPA2  */        WPA_KEY_MGMT_PSK,
/* (3)  WLAN_SEC_TYPE_WPS_PBC  */         WPA_KEY_MGMT_WPS,
/* (4)  WLAN_SEC_TYPE_WPS_PIN  */         WPA_KEY_MGMT_WPS,
/* (5)  CME_SEC_TYPE_WPA_ENT  */          WPA_KEY_MGMT_UNEXPECTED,
/* (6)  WLAN_SEC_TYPE_P2P_PBC  */         WPA_KEY_MGMT_NONE,
/* (7)  WLAN_SEC_TYPE_P2P_PIN_KEYPAD */   WPA_KEY_MGMT_NONE,
/* (8)  WLAN_SEC_TYPE_P2P_PIN_DISPLAY */  WPA_KEY_MGMT_NONE,
/* (9)  WLAN_SEC_TYPE_P2P_PIN_AUTO */     WPA_KEY_MGMT_UNEXPECTED,
/* (10) WLAN_SEC_TYPE_WEP_SHARED */       WPA_KEY_MGMT_NONE,
/* (11) CME_SEC_TYPE_WPA2_PLUS */         WPA_KEY_MGMT_PSK_SHA256,
/* (12) CME_SEC_TYPE_WPA3 */              WPA_KEY_MGMT_SAE,
/* (13) WLAN_SEC_TYPE_WPA2_AES_ONLY_PMF */     WPA_KEY_MGMT_PSK,
/* (14) WLAN_SEC_TYPE_WPA2_AES_ONLY_NO_PMF */  WPA_KEY_MGMT_PSK,
/* (15) UNEXPECTED */                     WPA_KEY_MGMT_UNEXPECTED,
/* (16) WLAN_SEC_TYPE_WPA2_WPA3 */        WPA_KEY_MGMT_PSK | WPA_KEY_MGMT_PSK_SHA256 | WPA_KEY_MGMT_SAE,
/* (17) CME_SEC_TYPE_WPA_ENT */           WPA_KEY_MGMT_UNEXPECTED,
/* (18) CME_SEC_TYPE_WPA */               WPA_KEY_MGMT_UNEXPECTED,
/* (19) CME_SEC_TYPE_WEP_SHARED */        WPA_KEY_MGMT_UNEXPECTED,
/* (20) WLAN_SEC_TYPE_WPA2_FT */          WPA_KEY_MGMT_PSK | WPA_KEY_MGMT_FT_PSK,
/* (21) WLAN_SEC_TYPE_WPA2_PLUS_FT */     WPA_KEY_MGMT_PSK_SHA256 | WPA_KEY_MGMT_FT_PSK,
/* (22) WLAN_SEC_TYPE_WPA3_FT */          WPA_KEY_MGMT_SAE | WPA_KEY_MGMT_FT_SAE,
/* (23) WLAN_SEC_TYPE_WPA2_WPA3_FT */     WPA_KEY_MGMT_PSK | WPA_KEY_MGMT_PSK_SHA256 | WPA_KEY_MGMT_SAE | WPA_KEY_MGMT_FT_PSK | WPA_KEY_MGMT_FT_SAE,
};


/*-------------------------------------*/
/* Get the managment key by sec type   */
/*-------------------------------------*/
int32_t CME_WlanGetKeyMngtBySecType(uint8_t secType, uint32_t *pKeyMgmtType)
{
    HOOK(HOOK_IN_CME);

    int32_t status = 0;
    uint32_t size = sizeof(SecTypeToWPAkey_lut) / sizeof(uint32_t);

    /* get the sec type from the LUT */
    if (secType >= size)
    {
        *pKeyMgmtType = WPA_KEY_MGMT_UNEXPECTED;
    }
    else
    {
        *pKeyMgmtType = SecTypeToWPAkey_lut[secType];
    }

    if(*pKeyMgmtType == WPA_KEY_MGMT_UNEXPECTED)
    {
        GTRACE(GRP_CME, "Invalid security type %d", secType);
        status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_INVALID_SECURITY_TYPE);
    }

    GTRACE(GRP_CME, "CME_WlanGetKeyMngtBySecType %d, keyMngType=%d", secType, *pKeyMgmtType);


    return status;
}

UINT8 CME_GetLastDisconnectReason()
{
    HOOK(HOOK_IN_CME);

    return gLastDisconnectInfo.ReasonCode;
}



/*-----------------------------------------------------------------------------*/
/* Check the validity and readiness of the device/STA to connect to the        */
/* desired AP. It also checks the command connection parameters sent by host.  */
/*-----------------------------------------------------------------------------*/
int32_t CME_WlanConnectValidateReq (CMEWlanConnectCommon_t *apCmd, BOOLEAN  *pIsProfileConnection)
{
    int32_t status;
    RoleType_e roleType;
    struct wpa_supplicant *wpa_s;

    HOOK(HOOK_IN_CME);

    /*  Get STA/P2P CL role is valid and select the correct iface */
    roleType = drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    if (ROLE_TYPE_NONE == roleType)
    {
        GTRACE(GRP_CME, "CME_WlanConnectValidateReq: Role sta type is NONE!!!");
        roleType = drv_getDeviceIface(gpSupplicantGlobals, &wpa_s);
        if (ROLE_TYPE_NONE == roleType)
        {
            GTRACE(GRP_CME, "CME_WlanConnectValidateReq: Role device type is NONE!!!");
            return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__INVALID_ROLE);
        }
    }

    //PROFILES connection case (command all zeros)- new
    if ((TRUE == IRQ_UtilIsZeroMacAddress((const uint8_t *)apCmd->Bssid)) &&
        (0 == apCmd->SsidLen) &&
        (IS_PROFILE_CONNECT(apCmd->Flags)) &&
        (apCmd->PasswordLen==0))
    {
        CME_PRINT_PROFILE_REPORT("\n\r [PROFILE] CME_WlanConnectValidateReq: Profile connection\n\r");
        status = CME_WlanProfileConnectionValidateReq(apCmd);
        *pIsProfileConnection = 1;
        
        return status;
    }
    else
    {
        status = validateWlanConnectParams(apCmd);
    }

    if (0 != status)
    {
        return status;
    }


    // More sanity checks for STA role are derived from requested security type.
    // If command parameters are valid, a message is pushed to CME queue.
    // Code below is based on R2 (V61)
    switch (apCmd->SecType)
    {
        case CME_SEC_TYPE_WEP:
        case CME_SEC_TYPE_WEP_SHARED:

            //July 2020 WEP is being dissabled
#if 0
    //  cc3100 code - WepKeyId is not supported yet in the shared host structure - TODO
    //  if (NUM_WEP_KEYS <= apCmd->WepKeyId)
    //  {
    //      GTRACE(GRP_CME, "Invalid WEP key %d", apCmd->WepKeyId);
    //      status = SL_ERROR_WLAN_ILLEGAL_WEP_KEY_INDEX;
    //  }
    //  else
        {
            if ( (WEP40_ASCII_KEY_LENGTH != apCmd->PasswordLen) &&
             (WEP40_HEX_KEY_LENGTH != apCmd->PasswordLen) &&
             (WEP104_ASCII_KEY_LENGTH != apCmd->PasswordLen) &&
             (WEP104_HEX_KEY_LENGTH != apCmd->PasswordLen) )
            {
                GTRACE(GRP_CME, "Invalid WEP password length %d", apCmd->PasswordLen);
                status = SL_ERROR_WLAN_KEY_ERROR;
            }

        }
#endif
        status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_INVALID_SECURITY_TYPE);

        break;

        case CME_SEC_TYPE_WPA_WPA2:

            if (WPA_MAX_PASSPHRASE_LEN < apCmd->PasswordLen)
            {
                GTRACE(GRP_CME, "Invalid WPA password length %d", apCmd->PasswordLen);
                status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_PASSPHRASE_TOO_LONG);
            }
            break;

        default:
            break;
    } // switch (sec_type)

    //
    //cme manager sanity check
    //
    if (gCmeRoleSwitchActive != FALSE)
    {

        ASSERT_GENERAL(0);//impossible - !!role switch should hold the command mailbox until its done
        return -1;
    }


    //if role switch is pending or ongoing operation is blocked

   GTRACE(GRP_SL_DISPATCH, "CME_WlanConnect : SecType %d , CME manager status check result = %d , gCmeRoleSwitchActive=%d! ",
                             apCmd->SecType, status, gCmeRoleSwitchActive);

   HOOK(HOOK_IN_CME);

   return status;
}


// ----------------------------------------------------------------------------
static int32_t cmeWlanConnectValidateCommon(CMEWlanConnectCommon_t *pCommon,
                                            uint32_t *pKeyMgmtType,
                                            BOOLEAN  *pIsProfileConnection)
{
    int32_t status;

    if (((pCommon->SecType == CME_SEC_TYPE_WPA2_WPA3) ||
         (pCommon->SecType == CME_SEC_TYPE_WPA2_WPA3_FT)) &&
        (l2_cfg_isMixedModeSupported() == FALSE))
    {
        CME_PRINT_REPORT("\n\rCan't connect to AP since WPA2/WPA3 "
                         "mixed mode isn't supported");
        return WlanError(WLAN_ERROR_SEVERITY__LOW,
                         WLAN_ERROR_MODULE__CME,
                         WLAN_ERROR_TYPE__INVALID_PARAM_SEC_TYPE);
    }

    status  = CME_WlanGetKeyMngtBySecType(pCommon->SecType, pKeyMgmtType);
    if (status != 0)
    {
        return status;
    }

    status = CME_WlanConnectValidateReq(pCommon, pIsProfileConnection);

    return status;
}

// Validate connect params, allocate, and copy cmd buffer.
// pSrc may be larger than pCommon (EAP case); baseSize = sizeof the full struct.
// ppCmd is set to the allocated buffer on success; untouched on failure.
static int32_t cmeWlanConnectPrepareCmd(CMEWlanConnectCommon_t *pCommon,
                                        const void             *pSrc,
                                        uint32_t                baseSize,
                                        uint32_t               *pKeyMgmtType,
                                        BOOLEAN                *pIsProfileConnection,
                                        void                  **ppCmd)
{
    int32_t  status;
    uint32_t cmdLen;

    status = cmeWlanConnectValidateCommon(pCommon, pKeyMgmtType, pIsProfileConnection);
    if (0 != status)
    {
        return status;
    }

    // Allocate and copy — dispatcher frees cmd memory after CME_WlanConnect returns.
    cmdLen = baseSize + 1 + pCommon->SsidLen + pCommon->PasswordLen;
    *ppCmd = os_malloc(cmdLen);
    if (NULL == *ppCmd)
    {
        CME_PRINT_REPORT("\n\rERROR!! CME:allocation of pCmd failed");
        return WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__MALLOC);
    }

    os_memcpy(*ppCmd, pSrc, cmdLen);
    return 0;
}

// ----------------------------------------------------------------------------
int32_t CME_WlanConnect(CMEWlanConnectCommon_t *apCmd, CMEEapWlanConnect_t* apEapCmd, BOOLEAN requestByHost)
{
    cmeMsg_t msg;
    int32_t    status;
    BOOLEAN  isProfileConnection = FALSE;
    CMEWlanConnectCommon_t *pCmd = NULL;
    CMEEapWlanConnect_t *pEapCmd = NULL;

    if (apCmd)
    {
        status = cmeWlanConnectPrepareCmd(apCmd,
                                          apCmd,
                                          sizeof(CMEWlanConnectCommon_t),
                                          &msg.un.wlanConnect.keyMgmtType,
                                          &isProfileConnection,
                                          (void **)&pCmd);
    }
    else if (apEapCmd)
    {
        status = cmeWlanConnectPrepareCmd(&apEapCmd->EapCommonConnect,
                                          apEapCmd,
                                          sizeof(CMEEapWlanConnect_t),
                                          &msg.un.wlanConnect.keyMgmtType,
                                          &isProfileConnection,
                                          (void **)&pEapCmd);
    }
    else
    {
        status = WlanError(WLAN_ERROR_SEVERITY__MID,
                           WLAN_ERROR_MODULE__CME,
                           WLAN_ERROR_TYPE__NULL_BUF);
    }

    if (0 != status)
    {
        return status;
    }

    msg.msgId = CME_MESSAGE_ID_WLAN_CONNECT;
    msg.un.wlanConnect.pConnectCmd = pCmd;
    msg.un.wlanConnect.pConnectEapCmd = pEapCmd;

    msg.generalData = 0;

    if (isProfileConnection)
    {
        //indicates if this is profiles connection case
        msg.generalData |= CME_GENERAL_DATA_CONNECT_IS_PROFILES;
    }

    if (requestByHost)
    {
        //indicates if this request has been asked by host/user
        msg.generalData |= CME_GENERAL_DATA_CONNECT_IS_USER_REQ;
    }

    pushMsg2Queue(&msg);

    HOOK(HOOK_IN_CME);

    return status;
}
// ----------------------------------------------------------------------------
int32_t CME_WlanDisconnect(BOOLEAN requestByHost)
{
	int32_t    status = WLAN_RET_CODE_OK;
    RoleType_e roleType;
    ti_driver_ifData_t *pDrv;
    cmeMsg_t   msg;
    struct wpa_supplicant *wpa_s;

    HOOK(HOOK_IN_CME);

    // Get STA/P2P CL role is valid and select the correct iface
    roleType = drv_getStaIface(gpSupplicantGlobals, &wpa_s);
  
    if (ROLE_TYPE_NONE == roleType)
    {
        CME_PRINT_REPORT_ERROR("\n\rCME  roleType sta or p2p client doesn't exists");

        roleType = drv_getDeviceIface(gpSupplicantGlobals, &wpa_s);
        if(ROLE_TYPE_NONE == roleType)
        {
            CME_PRINT_REPORT_ERROR("\n\rCME  roleType device doesn't exists");
           return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__INVALID_ROLE);
        }
    }

    pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    if (pDrv == NULL)
    {
        CME_PRINT_REPORT_ERROR("\n\rCME pDrv is NULL");
       return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__INVALID_ROLE);
    }

    //
    //cme manager sanity check
    //

    if (gCmeRoleSwitchActive != FALSE)
    {
        CME_PRINT_REPORT_ERROR("\n\rNOTE: gCmeRoleSwitchActive TRUE - role switch already in progress");
        int ret;
        ret = cme_role_switch_manager(CmeStationFlow_GetCurrentUser(),(BIT_x(ROLE_STA)),1/*if role switch done signal event*/);
        return ret;
    }

    GTRACE(GRP_SL_DISPATCH, "CME_WlanDisconnect gCmeRoleSwitchActive=%d! ", gCmeRoleSwitchActive);
    CME_PRINT_REPORT("\n\rCME_WlanDisconnect gCmeRoleSwitchActive=%d! roleType:%d", gCmeRoleSwitchActive, roleType);

    if (ROLE_IS_TYPE_STA_BASED_OR_DEVICE(roleType)) // STA or p2p client/device
    {
        msg.generalData = 0;

        if (WPA_DISCONNECTED == wpa_s->wpa_state)
        {
//            status = WLAN_ERROR_WIFI_ALREADY_DISCONNECTED;
            GTRACE(GRP_CME, "WARNING: supplicant is already in disconnected state");
            CME_PRINT_REPORT("\n\rWARNING: supplicant is already in disconnected state");
        }
        // else, result is already OK

        //TODO - send DHCP release

        // push disconnect message to CME queue in any case
        // if already disconnected, this stops any active scan
        msg.msgId = CME_MESSAGE_ID_WLAN_DISCONNECT;

        msg.roleId = pDrv->roleId;

        if (requestByHost)
        {
            msg.generalData |= CME_GENERAL_DATA_DISCONNECT_IS_USER_REQ;
        }


        pushMsg2Queue(&msg);
    }
    else
    {
        GTRACE(GRP_CME, "ERROR: CME_WlanDisconnect not Supported in AP Mode and/or if CME is in provisioning or role switch");
        CME_PRINT_REPORT("\n\rERROR: CME_WlanDisconnect not Supported in AP Mode and/or if CME is in provisioning or role switch");

        status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__INVALID_ROLE);
    }

    return status;
}

//
// CONNECTION PROFILES API's
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ----------------------------------------------------------------------------
int16_t CME_GetProfile(uint8 profileIndex, CMEWlanAddGetEapProfile_t *fillOutArgs)
{
    int16_t RetVal = WLAN_RET_CODE_OK;

    if (profileIndex >= CME_SCAN_MAX_PROFILES)
    {
        GTRACE(GRP_CME, "Error - Profile Index does not exist - %d", profileIndex);
        // When error code is returned, it is transfered in the SecType field.
        fillOutArgs->CommonAddProf.SecType = WLAN_ERROR_TYPE__HOST_RESPONSE_GET_PROFILE_INVALID_INDEX; //SL_ERROR_WLAN_GET_PROFILE_INVALID_INDEX;
        fillOutArgs->CommonAddProf.SsidLen = 0;

        RetVal = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_GET_PROFILE_INVALID_INDEX);
        
    }
    else
    {
        //
        //prevent preemption of this thread (host interface) so that preferred networks structure wont be changed during reading
        //
        //uint32 old_preempt = osi_DisablePreemption();

        RetVal = cmeGetPreferredNetwork(profileIndex, fillOutArgs);

        //restore original preemption
        //osi_RestorePreemption(old_preempt);

        if(RetVal < 0)
        {
            fillOutArgs->CommonAddProf.SecType = RetVal;
            fillOutArgs->CommonAddProf.SsidLen = 0; // add info to Host that this ID has no entry
        }
    }
    
    return RetVal;
}

// ----------------------------------------------------------------------------
int16_t CME_RemoveProfile(uint8_t delete_profile_index)
{
    cmeMsg_t  msg;
    int16_t   status = WLAN_RET_CODE_OK;

    //validity check
    if (
               (WLAN_DEL_ALL_PROFILES != delete_profile_index)  //delete all profiles request
            && (delete_profile_index >= CME_SCAN_MAX_PROFILES)  //profile index is in range
        )
    {
        status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_GET_PROFILE_INVALID_INDEX);
    }
    else if(CME_IsOngoingWPSAdHocConnection())
    {

        status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_ADD_REMOVE_PROFILE_FAILED_WPS_IN_PROGRESS);
    }

    if (status == WLAN_RET_CODE_OK)
    {
        // Now instead of doing the whole flow from the CME context we will call cmeDeletePreferredNetwork from
        // the dispatcher context and write the profile to flash BUT NOT TO GLOBAL.
        // We want to prevent the possibility of race condition so we disable profile remove durring WPS, and
        // only when we are done writing to flash, we will send a message to the CME to update the global GLX and to do
        // cmeProfileManagerConfigChange
        status = cmeDeletePreferredNetwork(delete_profile_index);
        GTRACE(GRP_SL_DISPATCH, "CME_RemoveProfile: Profile index %d is removed", delete_profile_index);
        CME_PRINT_REPORT("\n\rCME_RemoveProfile: Profile index %d is removed", delete_profile_index);

        if(status == WLAN_RET_CODE_OK)
        {
            msg.msgId = CME_MESSAGE_ID_PROFILE_REMOVED;
            msg.un.deletedProfileIdx = delete_profile_index;

            pushMsg2Queue(&msg);
        }
    }

    return status;
}

// ----------------------------------------------------------------------------
#if CC35XX_ADD_SUPPORT_ENT_PROFILE
int32_t CME_AddEapProfile(CMEWlanAddGetEapProfile_t *new_profile)
{
    cmeMsg_t msg;

    int16 index;
    CMEWlanAddGetEapProfile_t *sl_wlan_add_profile_args = new_profile;

    if ((new_profile->CommonAddProf.SecType == WLAN_SEC_TYPE_WPA2_WPA3) &&
        (l2_cfg_isMixedModeSupported() == FALSE))
    {
        return WlanError(WLAN_ERROR_SEVERITY__LOW,
                         WLAN_ERROR_MODULE__CME,
                         WLAN_ERROR_TYPE__INVALID_PARAM_SEC_TYPE);
    }

    int32_t  status = cme_validate_eap_connection_params(sl_wlan_add_profile_args->Common.SsidLen,
                                                       sl_wlan_add_profile_args->Common.PasswordLen,
                                                       sl_wlan_add_profile_args->UserLen,
                                                       sl_wlan_add_profile_args->AnonUserLen,
                                                       sl_wlan_add_profile_args->CertIndex,
                                                       sl_wlan_add_profile_args->EapBitmask,
                                                       0/*do not validate role*/);


    GTRACE(GRP_SL_DISPATCH, "CME_AddEapProfile : CME manager status check result = %d ", status);

    if (WLAN_RET_CODE_OK == status)
    {

        // Now instead of doing the whole flow from the CME context we will call cmeAddPreferredNetwork from
        // the dispatcher context and write the profile to flash BUT NOT TO GLOBAL.
        // Only when we are done we will send a message to the CME to update the global GLX and to do
        // cmeProfileManagerConfigChange
        cmeAddPreferredNetwork(NULL,NULL,sl_wlan_add_profile_args,&index);

        if ( index >= 0) //meaning successful profile index allocation
        {
            msg.msgId = CME_MESSAGE_ID_PROFILE_EAP_ADDED;
            pushMsg2Queue(&msg);
        }

        status = index;

        GTRACE(GRP_SL_DISPATCH, "CME_AddEapProfile: Profile written to flash, index returned is %d", index);

    }
    return status;
}
#endif
// ----------------------------------------------------------------------------
static int32_t cmeValidateProfileSecType(uint8_t secType, uint8_t passwordLen)
{
    switch ((CMESecType_e)secType)
    {
        case CME_SEC_TYPE_OPEN:
            break;
        case CME_SEC_TYPE_WPA_WPA2:
        case CME_SEC_TYPE_WPA3:
        case CME_SEC_TYPE_WPA2_PLUS:
        case CME_SEC_TYPE_WPA2_FT:
        case CME_SEC_TYPE_WPA2_PLUS_FT:
        case CME_SEC_TYPE_WPA3_FT:
            if (passwordLen > WPA_MAX_PASSPHRASE_LEN)
            {
                return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_PASSPHRASE_TOO_LONG);
            }
            break;
        case CME_SEC_TYPE_WPA2_WPA3:
        case CME_SEC_TYPE_WPA2_WPA3_FT:
            if (l2_cfg_isMixedModeSupported() == FALSE)
            {
                return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__INVALID_PARAM_SEC_TYPE);
            }
            if (passwordLen > WPA_MAX_PASSPHRASE_LEN)
            {
                return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_PASSPHRASE_TOO_LONG);
            }
            break;
        default:
            return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_INVALID_SECURITY_TYPE);
    }
    return WLAN_RET_CODE_OK;
}

// ----------------------------------------------------------------------------
int32_t CME_AddProfile(CMEWlanAddGetProfile_t* new_profile)
{
    cmeMsg_t   msg;
    int32_t    status;
    int16_t    index;
    const CMEWlanAddGetProfile_t *cme_wlan_add_profile_args = new_profile;
    uint32_t keyMgmtType;    

    //
    //validity check
    //
    /* extract the corresponding key managment */
    status = CME_WlanGetKeyMngtBySecType (new_profile->SecType, &keyMgmtType);

    /* Profile Add cmd is invalid/wrong secType - just return the error */
    if (WLAN_RET_CODE_OK != status)
    {
        return status;
    }

    if ((0 == cme_wlan_add_profile_args->SsidLen) || (cme_wlan_add_profile_args->SsidLen > SSID_MAX_LEN))
    {
        status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_SSID_LEN);
    }
    else if(CME_IsOngoingWPSAdHocConnection())
    {
        status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_ADD_REMOVE_PROFILE_FAILED_WPS_IN_PROGRESS);
    }
    else
    {
        status = cmeValidateProfileSecType(cme_wlan_add_profile_args->SecType,
                                           cme_wlan_add_profile_args->PasswordLen);
    }

    /* Profile Add cmd param is invalid/wrong secType - just return the error */
    if (WLAN_RET_CODE_OK == status)
    {
    
        // Now instead of doing the whole flow from the CME context we will call cmeAddPreferredNetwork from
        // the dispatcher context and write the profile to flash BUT NOT TO GLOBAL.
        // We want to prevent the possibility of race condition so we disable profile add durring WPS, and
        // only when we are done writing to flash, we will send a message to the CME to update the global GLX and to do
        // cmeProfileManagerConfigChange
        cmeAddPreferredNetwork(new_profile,&index,NULL,NULL);

        if ( index >= 0) //meaning successful profile index allocation
        {
            msg.msgId = CME_MESSAGE_ID_PROFILE_ADDED;

            pushMsg2Queue(&msg);
        }

        status = index;
        GTRACE(GRP_SL_DISPATCH, "CME_AddProfile: Profile written to flash, index returned is %d", index);
    }
    return status;
}

int16_t CME_WlanProfileConnectionValidateReq(CMEWlanConnectCommon_t *apCmd)
{
    int16_t status = WLAN_RET_CODE_OK;
    CMEWlanAddGetEapProfile_t *fillOutArgs;
    uint8_t index = apCmd->SecType;

    fillOutArgs = os_malloc(sizeof(CMEWlanAddGetEapProfile_t) + MAX_SSID_LEN);

    if (fillOutArgs == NULL)
    {
        CME_PRINT_REPORT_ERROR("\n\rERROR: allocation failed");
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_GET_PROFILE_INVALID_INDEX);
    }

    if(CME_GetProfile(index, fillOutArgs) == WLAN_RET_CODE_OK)
    {
        status = WLAN_RET_CODE_OK;
    }
    else
    {
        CME_PRINT_REPORT_ERROR("\n\rProfile Index does not exist - %d", index);
        status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_GET_PROFILE_INVALID_INDEX);
    }
    
    os_free(fillOutArgs);
    return status;
}

// ----------------------------------------------------------------------------
#if CC35XX_ADD_SUPPORT_ENT_PROFILE
static int32_t cme_validate_eap_connection_params(uint8_t  SsidLen,
                                                  uint8_t  PasswordLen,
                                                  uint8_t  UserLen,
                                                  uint8_t  AnonUserLen,
                                                  uint8_t  CertIndex,
                                                  unit32_t EapBitmask,
                                                  uint8_t  do_validate_role)
{
    int32_t status = WLAN_RET_CODE_OK;
    //
    //EAP is relevant for STA role only
    //
    if (do_validate_role && (!cme_is_activated_role_from_type(ROLE_STA)))
    {
        GTRACE(GRP_CME, "WLAN Dispatcher ERROR! CME_WlanConnectEap: Command Not Supported in non-STA Mode - parse cmdCME_WlanConnectEap");
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__INVALID_ROLE);
    }


    if((0 == SsidLen) || (SsidLen > SSID_MAX_LEN))
    {
        GTRACE(GRP_CME, "WLAN Dispatcher: Parameter Error");
        status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_SSID_LEN);//SL_ERROR_WLAN_SSID_LEN_ERROR;
    }
    else
    {
        //now supporting 2 sets of ENT certificate files, user must state if it is the first one (0) or the second set (1)
        //TODO - 1 ENT is allowed!!
        if (CertIndex != 0 && CertIndex != 1)
        {
            GTRACE(GRP_CME, "WLAN Dispatcher: certificate index out of range");
            status = -1;//SL_ERROR_WLAN_EAP_WRONG_CERT_INDEX;

        }
        else if ((0 == UserLen) || (UserLen > MAX_USER_LEN))
        {
            GTRACE(GRP_CME, "WLAN Dispatcher: Parameter Error");
            status = -1; //SL_ERROR_WLAN_USER_ID_LEN_ERROR;
        }
        else
        {

            switch (EAPBITMASK_GET_PHASE1_VAL(EapBitmask))
            {
                case TLS: // TLS
                    break; //TLS
                case TTLS: // TTLS
                case PEAP0: // PEAP
                case PEAP1: // PEAP
                    if (EAPBITMASK_GET_PHASE2_VAL(EapBitmask) > 2) // Should be MSCHAPV2 or TLS or PSK
                    {
                        status = SL_ERROR_WLAN_EAP_WRONG_METHOD;
                    }

                    else
                    {
                        if (((0 == PasswordLen) || ( PasswordLen > MAX_PASS_LEN)) &&
                                ((EAPBITMASK_GET_PHASE2_VAL(EapBitmask) == 0)||( EAPBITMASK_GET_PHASE2_VAL(EapBitmask) == 2 ))  ) //MSCHAPV2 or PSK
                        {
                            status = SL_ERROR_WLAN_PASSWORD_ERROR;
                        }
                        else if (AnonUserLen > MAX_ANON_LEN)
                        {
                            status = SL_ERROR_WLAN_EAP_ANONYMOUS_LEN_ERROR;
                        }
                    }
                    break;
                case FAST: // FAST
                    if ((0 == PasswordLen) || ( PasswordLen > MAX_PASS_LEN))
                    {
                        status = SL_ERROR_WLAN_PASSWORD_ERROR;
                    }
                    else if (AnonUserLen > MAX_ANON_LEN)
                    {
                        status = SL_ERROR_WLAN_EAP_ANONYMOUS_LEN_ERROR;
                    }

                    break;
                default:
                    status = SL_ERROR_WLAN_EAP_WRONG_METHOD;
                    GTRACE(GRP_CME, "ERROR!parse cmd EAP connect, unsupported eap bitmask!!! %d",  EAPBITMASK_GET_PHASE1_VAL(EapBitmask));
                    break;
            }
        }
    }

    return status;

}
#endif
//
//   END OF PROFILES APIs
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ----------------------------------------------------------------------------
void CME_ChannelSwitchSetTxPower(uint8_t channel)
{
    ti_driver_ifData_t *pDrv;
    pDrv = drv_getDriverData(NETIF_NAME(TIWLAN_DEV_NAME_STA));
    if(NULL != pDrv)
    {
        int8_t maxTxPower;
        if(TRUE == regulatoryDomain_getChMaxPower(channel, &maxTxPower))
        {
            regulatoryDomain_setRoleMaxTxPower(pDrv, maxTxPower);
        }
        else
        {
            GTRACE(GRP_CME, "\n\rFailed setting TX power after channel switch. valid channel TX power did not found!");   
        }
    }
    else
    {
        GTRACE(GRP_CME, "\n\rFailed setting TX power after channel switch. Driver data did not found!");   
    }
}

// ----------------------------------------------------------------------------
int32_t CME_ChannelSwitchAnnounceNotify(uint32_t aRoleId, uint8_t channel, uint8_t count, Bool32 block_tx)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_CSA_NOTIFY;
    msg.roleId = aRoleId;
    msg.un.channelSwitchIe[0] = block_tx;
    msg.un.channelSwitchIe[1] = channel;
    msg.un.channelSwitchIe[2] = count;

    return pushMsg2Queue(&msg);
}

// ----------------------------------------------------------------------------
int32_t CME_ChannelSwitchDone(uint32_t aRoleId)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_CS_FINISH;
    msg.roleId = aRoleId;

    return pushMsg2Queue(&msg);
}

int32_t CME_RemainOnChannelTimeoutNotify(uint32_t aRoleId)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_ROC_TIMER_TIMEOUT;
    msg.roleId = aRoleId;

    return pushMsg2Queue_fromIntr(&msg);
}

// ----------------------------------------------------------------------------
int32_t CME_RemainOnChannelNotify(struct wpa_supplicant *wpa_s,
                                  int32_t aRoleId,
                                  int32_t freq,
                                  uint32_t duration)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_EXT_ROC ;
    msg.roleId = aRoleId;
    msg.un.rocParam.duration = duration;
    msg.un.rocParam.freq = freq;
    msg.un.rocParam.wpa_s = wpa_s;

    return pushMsg2Queue(&msg);
}

int32_t CME_CancelRemainOnChannelNotify(struct wpa_supplicant *wpa_s, uint32_t is_croc_performed_due_to_timeout)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_EXT_CROC ;
    msg.un.rocParam.wpa_s = wpa_s;
    msg.un.rocParam.is_croc_performed_due_to_timeout = is_croc_performed_due_to_timeout;
    return pushMsg2Queue(&msg);
}


int32_t CME_sendActionFrameNotify( ti_driver_ifData_t     *pDrv,
                                   const uint8_t          *apDst,         // Destination address
                                   const uint8_t          *actionBuff,
                                   uint32_t                actionBuffLen)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    uint8_t *actionBuffToSend = os_malloc(actionBuffLen);//free of the buffer after the action is send
    os_memcpy(actionBuffToSend,actionBuff,actionBuffLen);

    msg.msgId = CME_MESSAGE_ID_EXT_SEND_ACTION ;
    msg.un.sendActionParam.pDrv = pDrv;
    os_memcpy(msg.un.sendActionParam.apDst, apDst, MAC_ADDRESS_LEN);
    msg.un.sendActionParam.actionBuff = actionBuffToSend;
    msg.un.sendActionParam.actionBuffLen =actionBuffLen;

    return pushMsg2Queue(&msg);
}


int32_t CME_updateVendorElementsNotify(RoleType_e roleType,  uint16_t vendorElements_length, uint8_t* pVendorElements)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;
    uint8_t* pVendorIE = NULL;
    int32 ret;

    if(vendorElements_length)
    {
        pVendorIE = os_malloc(vendorElements_length);
        if(pVendorIE == NULL)
        {
            GTRACE(GRP_DRIVER_CC33, "WLAN_SET_VENDOR_IE:failed to allocate memory, size :%d",vendorElements_length);
            CME_PRINT_REPORT_ERROR("\n\rWLAN_SET_VENDOR_IE:failed to allocate memory size :%d", vendorElements_length);
            ret = WLAN_RET_COMMAND_ERROR_MID_TYPE__CMD_GENERAL;
            return ret;
        }

        os_memcpy(pVendorIE,pVendorElements,vendorElements_length);
    }

    msg.msgId = CME_MESSAGE_ID_SET_VENDOR_ELEMETS ;
    msg.un.vendorElements.roleType = roleType;
    msg.un.vendorElements.vendorElements_length = vendorElements_length;
    msg.un.vendorElements.pVendorElements = pVendorIE;

    return pushMsg2Queue(&msg);
}


#ifndef TI_STA_ONLY_BUILD
int32_t CME_setPeerAgingTimeout(uint32_t agingTimeOut)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_CONFIGURE_PEER_AGING_TIMEOUT ;
    msg.un.peerAgingTimeout = agingTimeOut;

    return pushMsg2Queue(&msg);
}
#endif

#ifndef TI_STA_ONLY_BUILD
int32_t CME_peerAgingSampleTime()
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_PEER_AGING_SAMPLE_TIME ;

    return pushMsg2Queue(&msg);
}
#endif


// ----------------------------------------------------------------------------
CmeTxDesc_t *CME_CopyTxDesc(void *srcDesc, uint32_t status)
{
    uint32_t allocSize;
    struct MgmtPktDesc *pDesc = (struct MgmtPktDesc *)srcDesc;
    CmeTxDesc_t *pDstDesc;
    if(!pDesc)
    {
        CME_PRINT_REPORT("\n\rCME_TxResult,pDesc is NULL");
        ASSERT_GENERAL(0);
        return NULL;
    }
    pDstDesc = os_malloc(sizeof(CmeTxDesc_t));
    if(!pDstDesc)
    {
        CME_PRINT_REPORT_ERROR("\n\rERROR !!! CME failed to malloc desc \n\r");
        return NULL;
    }

    // malloc for payload + header
    allocSize = pDesc->uHeaderLen + pDesc->uPayloadLen;
    pDstDesc->address = os_malloc(allocSize);
    if(!pDstDesc->address)
    {
        os_free(pDstDesc);
        CME_PRINT_REPORT_ERROR("CME failed to malloc address desc \n\r");
        return NULL;
    }

    // Copy the descriptor
    pDstDesc->link = pDesc->link;
    pDstDesc->status = status;
    pDstDesc->uHeaderLen = pDesc->uHeaderLen;
    pDstDesc->uPayloadLen = pDesc->uPayloadLen;

    // First copy the header
    os_memcpy((uint8_t*)pDstDesc->address, pDesc->header, pDesc->uHeaderLen);
    // Copy the payload
    //CME_PRINT_REPORT("\n\rCME_TxResult,descriptor copied uHeaderLen:%d uPayloadLen:%d",pDstDesc->uHeaderLen,pDesc->uPayloadLen);

    os_memcpy((((uint8_t*)pDstDesc->address) + pDstDesc->uHeaderLen), pDesc->payload, pDesc->uPayloadLen);


    return pDstDesc;
}


void CME_FreeTxDesc(void *desc)
{
    CmeTxDesc_t *pDesc = (CmeTxDesc_t *)desc;
    if(pDesc && pDesc->address)
    {
        os_free(pDesc->address);
        pDesc->address = NULL;
    }

    os_free(pDesc);
    pDesc = NULL;

    return;
}

// ----------------------------------------------------------------------------
int32_t CME_EapolTxResult(void *desc)
{
    GTRACE(GRP_CME, "EAPOL TX complete received");
    if (OSI_OK != osi_SyncObjSignal(&gCmeEapolsStaSyncObject))
    {
        GTRACE(GRP_CME, "ERROR: Signaling gCmeEapolsStaSyncObject sync object failed");
    }

    return 0;
}

// ----------------------------------------------------------------------------
int32_t CME_TxResult(void *desc)
{
    cmeMsg_t msg;
    volatile CmeTxDesc_t *pDesc = NULL;
    struct MgmtPktDesc* pRecDesc;
    TMgmtPktReport* pMgmDesc =  (TMgmtPktReport*)desc;
    struct ieee80211_mgmt *pMngPack;
    tiwdrv_if_mode_e netifMode;
    uint8_t netif;

    pRecDesc = pMgmDesc->desc;

    if(OK != wlanLinks_GetNetifInfo(pMgmDesc->desc->link, &netif, &netifMode))
    {
       CME_PRINT_REPORT_ERROR("\r\n CME_TxResult: wlanLinks_GetNetifInfo failed");
       return -1;
    }

    if((netifMode == TIWDRV_IF_MODE_SAP) || (netifMode == TIWDRV_IF_MODE_STA))
    {
        uint16 fc, type, stype;
        pMngPack = (struct ieee80211_mgmt *)(uint8_t*)RX_BUF_DATA(desc);

        fc = le_to_host16(pMngPack->frame_control);
        type = WLAN_FC_GET_TYPE(fc);
        stype = WLAN_FC_GET_STYPE(fc);

        if(netifMode == TIWDRV_IF_MODE_SAP)
        {
            //optimization :for AP there is no need to send the tx result
            // of beacon and of probe response to the supplicant.
            if ((type == WLAN_FC_TYPE_MGMT) &&
                        ((stype == WLAN_FC_STYPE_BEACON)||(stype == WLAN_FC_STYPE_PROBE_RESP)))

            {
                return -1;
            }
            
        }

    }
   //Check if messages queue is above threshold. if yes, and in case supplicant does not anything with the frame, disregard it.
   //(i.e. TX done on probe responses and action frames can be disregarded safely since supplicant ignores them as well)
   if (isMsgQueueAboveThreshold())
   {
       if (isTxResultSafeToFilter (desc))
       {
           //For now drop only TX done on probe responses or action frames (assuming these fill the queue, and it is anyway safe
           //to clean them since supplicant disregards them as well)
           CME_PRINT_REPORT("\n\rCME_TxResult:CME queue above threshold, drop frame\n\r");
           GTRACE(GRP_CME, "CME_TxResult: CME queue above threshold, drop frame");
           return -1;
       }
   }
   // Copy the descriptor
   if(pMgmDesc->desc)
   {
       //CME_PRINT_REPORT("\n\rCME_TxResult,copy descriptor");
       pDesc = CME_CopyTxDesc(pMgmDesc->desc, pMgmDesc->status);
   }
   if(!pDesc)
   {
       CME_PRINT_REPORT_ERROR("\n\rERROR CME_TxResult,CME failed to copy desc ");
       return -1;
   }

    msg.msgId = CME_MESSAGE_ID_TX_DONE;
    msg.un.txRxPacket.pDesc = (void*)pDesc;

    // Note that some TX packets may not be released, as their content is used
    // by supplicant or driver_cc;  in this case, they shall be released after
    // handled.

    //Report("\n\rsend msg :CME_MESSAGE_ID_TX_DONE");

    return pushMsg2Queue(&msg);
}

// ----------------------------------------------------------------------------
int32_t CME_MaxTxFailure(uint32_t aRoleId, uint16_t aInactiveLinksBits)
{
    cmeMsg_t msg;

    HOOK(HOOK_IN_CME);

    msg.msgId = CME_MESSAGE_ID_MAX_RETRY;
    msg.roleId = aRoleId;
    msg.generalData = aInactiveLinksBits;

    return pushMsg2Queue(&msg);
}
// ----------------------------------------------------------------------------
int32_t CME_SetInactiveSta(uint32_t aRoleId, uint16_t aInactiveLinksBits)
{
    cmeMsg_t msg;

    HOOK(HOOK_IN_CME);

    msg.msgId = CME_MESSAGE_ID_INACTIVITY;
    msg.roleId = aRoleId;
    msg.generalData = aInactiveLinksBits;

    return pushMsg2Queue(&msg);
}

// ----------------------------------------------------------------------------
int32_t CmeScan_SetProfilesAndResultsMem(cmeScanSharedInfo_t *apSharedInfo,
                                       OsiSyncObj_t        *apSyncObj,
                                       EScanRequestType     aScanReqType)
{
    cmeMsg_t msg;

    HOOK(HOOK_IN_CME);

    msg.msgId = CME_MESSAGE_ID_SET_SCAN_CME_INFO;
    msg.un.preScanInfo.pSharedInfo  = apSharedInfo;
    msg.un.preScanInfo.pSyncObj     = apSyncObj;
    msg.un.preScanInfo.aScanReqType = aScanReqType;

    return pushMsg2Queue(&msg);
}

// ----------------------------------------------------------------------------
int32_t CmeScan_ScanDone(EScanRequestType    aScanReqType,
                       uint32_t              aRoleId,
                       cmeScanSharedInfo_t *apSharedInfo,
                       cmeScanStatus_e     aStatus,
                       uint8_t             fromIntr,
                       uint8_t             fromTimeout)
{
    cmeMsg_t msg;

    HOOK(HOOK_IN_CME);

    msg.msgId = CME_MESSAGE_ID_SCAN_COMPLETE;
    msg.roleId = aRoleId;
    msg.un.postScanInfo.scanType = aScanReqType;
    msg.un.postScanInfo.status = aStatus;
    msg.un.postScanInfo.pSharedInfo = apSharedInfo;

    if (fromTimeout)
    {
        msg.un.postScanInfo.fromTimeout = TRUE;
    }
    else
    {
        msg.un.postScanInfo.fromTimeout = FALSE;
    }

    if(!fromIntr)
    {
        return pushMsg2Queue(&msg);
    }
    else
    {
        return pushMsg2Queue_fromIntr(&msg);
    }
}

// ----------------------------------------------------------------------------
int32_t CmeScan_ScanPeriodDone(uint32_t  aRoleId,
                             cmeScanSharedInfo_t *apSharedInfo,
                             cmeScanStatus_e  aStatus)
{
    cmeMsg_t msg;

    HOOK(HOOK_IN_CME);

    msg.msgId = CME_MESSAGE_ID_SCAN_PERIOD_COMPLETE;
    msg.roleId = aRoleId;
    msg.un.scanPeriodDoneInfo.pProfiles = &apSharedInfo->mPeriodicProfiles;
    msg.un.postScanInfo.scanType = SCAN_REQUEST_CONNECT_PERIODIC_SCAN;
    msg.un.postScanInfo.status = aStatus;
    msg.un.postScanInfo.pSharedInfo = apSharedInfo;

    return pushMsg2Queue(&msg);
}


// ----------------------------------------------------------------------------
int32_t CME_NotifyRxMngPack(void *aDesc)
{
    cmeMsg_t msg;
    Bool32 filterRxMngFrame;

    //Check if messages queue is above threshold. if yes, disregard the management frame  
    if (isMsgQueueAboveThreshold())
    {
        filterRxMngFrame = isRxMgmtFrameSafeToFilter(aDesc);
        if (filterRxMngFrame)
        {
            GTRACE(GRP_GENERAL_ERROR, "CME_NotifyRxMngPack: CME queue above threshold, drop Mng frame");

            RxBufFree(aDesc);

            return -1;
        }
    }

    RX_MGMT_PRINT("\n\rCME_NotifyRxMngPack send MSG");

    msg.msgId = CME_MESSAGE_ID_RX_MNG_PACK;
    msg.un.txRxPacket.pDesc = aDesc;

    return pushMsg2Queue(&msg);
}

#if 0
int32_t CME_unprotDeAuthAssocDetected(void *aDesc, uint32_t aRoleId)
{
    cmeMsg_t msg;

    //Check if messages queue is above threshold. if yes, disregard the frame
    if (isMsgQueueAboveThreshold())
    {
        GTRACE(GRP_CME, "CME queue above threshold, drop frame");
        Report("\n\rCME_unprotDeAuthAssocDetected,CME queue above threshold, drop frame");

        RxBufFree(aDesc);

        return -1;
    }


    msg.msgId = CME_MESSAGE_ID_UNPROTECTED_DEAUTH_DEASSOC;
    msg.roleId = aRoleId;
    msg.un.txRxPacket.pDesc = aDesc;

    return pushMsg2Queue(&msg);
}
#endif

// ----------------------------------------------------------------------------
int32_t CME_RxFromUnknown(void *aDesc, uint32_t aRoleId)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    //Check if messages queue is above threshold. if yes, disregard the rx frame
    if (isMsgQueueAboveThreshold())
    {
        GTRACE(GRP_CME, "CME queue above threshold, drop rx frame");
        Report("\n\rCME_RxFromUnknown:CME queue above threshold, drop rx frame");

        RxBufFree(aDesc);

        return -1;
    }

    msg.msgId = CME_MESSAGE_ID_RX_FROM_UNKNOWN;
    msg.roleId = aRoleId;
    msg.un.txRxPacket.pDesc = aDesc;

    return pushMsg2Queue(&msg);
}

// ----------------------------------------------------------------------------
int32_t CME_RxFromUnknownData(void *aDesc)
{
    HOOK(HOOK_IN_CME);

    RxIfDescriptor_t *pRxParams = (RxIfDescriptor_t *)aDesc;
    uint8_t uHlid = pRxParams->hlid;
    TUdata *pUdata = gUdataCB;
    RoleType_e eRoleType;
    uint32_t roleId;

    /* Validate HLID bounds */
    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        RxBufFree(aDesc);
        return -1;
    }
    /* Get role type from link info */
    eRoleType = pUdata->aLinkInfo[uHlid].eRoleType;
    roleId = drv_getRoleIdFromType(gpSupplicantGlobals, eRoleType);

    return CME_RxFromUnknown(aDesc, roleId);
}
#if 0
int32_t CME_NotifyMicFailure(void *aDesc)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    //Check if messages queue is above threshold. if yes, disregard the rx frame
    if (isMsgQueueAboveThreshold())
    {
        GTRACE(GRP_CME, "CME queue above threshold, drop rx frame");
        Report("\n\rCME_NotifyMicFailure:CME queue above threshold, drop rx frame");

        RxBufFree(aDesc);

        return -1;
    }


        RxBufFree(aDesc);


    return 0;
#if 0 // For now no handle for mic failure - just release the frame
    msg.msgId = CME_MESSAGE_ID_MIC_FAILURE;
    msg.un.txRxPacket.pDesc = aDesc;

    return pushMsg2Queue(&msg);
#endif
}
#endif
#if 0
// ----------------------------------------------------------------------------
int32_t CME_PnReplayDetected(void *aDesc)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    //Check if messages queue is above threshold. if yes, disregard the frame
    if (isMsgQueueAboveThreshold())
    {
        GTRACE(GRP_CME, "CME queue above threshold, drop frame");
        Report("\n\rCME_PnReplayDetected:ME queue above threshold, drop frame");

        RxBufFree(aDesc);

        return -1;
    }


        RxBufFree(aDesc);

    return 0;
#if 0 // For now no handle for mic failure - just release the frame
    msg.msgId = CME_MESSAGE_ID_PN_REPLAY_DETECTED;
    msg.un.txRxPacket.descriptorId = aDescriptorId;
    msg.generalData = cipherType;

    return pushMsg2Queue(&msg);
#endif
}
#endif
// ----------------------------------------------------------------------------
int32_t CME_RxEapol(void *aDesc)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;
    
    // Allow external WPS handling to forward EAPOLs to the application
    uint8_t netifId = 0;
    if (isextWPS() && extWpsIsLinkWps(((RxIfDescriptor_t *) aDesc)->hlid, &netifId))
    {
        GTRACE(0, "Forward EAPOL Rx to External WPS, netifId: %u", netifId);
        _recvNetworkPacket(netifId, (uint8*)((TEthernetHeader *)RX_ETH_PKT_DATA((uint8_t *)aDesc)), RX_ETH_PKT_LEN((uint8_t *)aDesc));
        RxBufFree(aDesc);
        return 0;
    }

    //Check if messages queue is above threshold. if yes, disregard the eapol frame
    if (isMsgQueueAboveThreshold())
    {
        GTRACE(GRP_GENERAL_ERROR, "CME_RxEapol:CME queue above threshold, drop eapol frame ");

        RxBufFree(aDesc);

        return -1;                
    }
    
    msg.msgId = CME_MESSAGE_ID_RX_EAPOL_PACK;
    //msg.roleId = aRoleId;
    msg.un.txRxPacket.pDesc = aDesc;

    return pushMsg2Queue(&msg);
}
//
// cmePendingWlanConnectTrigger -
//                                      trigger wlan connect with the original command buffered in pending block
//
int cmePendingWlanConnectTrigger()
{
    HOOK(HOOK_IN_CME);

    struct wpa_supplicant *wpa_s;
    ti_driver_ifData_t *pDrv = NULL;

    GTRACE(GRP_CME,"cme_PendingWlanConnect.pConnectCmd value 0x%x",(uint32_t)gCme_PendingWlanConnect.pConnectCmd);
    CME_PRINT_REPORT("\n\rCME:cme_PendingWlanConnect.pConnectCmd value 0x%x",(uint32_t)gCme_PendingWlanConnect.pConnectCmd);
    if ((gCme_PendingWlanConnect.pConnectCmd == NULL) && (gCme_PendingWlanConnect.pConnectEapCmd == NULL))
    {
        CME_PRINT_REPORT("\n\rCME:cme_PendingWlanConnect.connect cmd is not waiting");
        return 0;
    }

    drv_getStaIface(gpSupplicantGlobals, &wpa_s);
    pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

	CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: cmePendingWlanConnectTrigger, change state to :CME_STA_NETWORK_SEARCH_EVENT !!");
    //set state in STA flow SM with wlanConnect User
     if (0 != CmeStationFlowSM(CME_STA_NETWORK_SEARCH_EVENT,CME_STA_WLAN_CONNECT_USER))
     {
         GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set scan in STA flow SM and failed!! ");
         CME_PRINT_REPORT_ERROR("\n\rCME: ERROR!CmeStationFlowSM tried to set scan in STA flow SM and failed!! ");
         ASSERT_GENERAL(0);
         return 0;
     }

    GTRACE(GRP_CME,"cme_InternalEventHandler: WlanConnect event trigger following previous network DISCONNECTEd event");
    CME_PRINT_REPORT("\n\rcme_InternalEventHandler: WlanConnect event trigger following previous network DISCONNECTEd event");

    cmeWlanConnect(pDrv->roleId, gCme_PendingWlanConnect.pConnectCmd, gCme_PendingWlanConnect.pConnectEapCmd,
                   gCme_PendingWlanConnect.keyMgmtType,gCme_PendingWlanConnect.profiles_connection);

    //clear wlanconnect, releasing the buffer performed inside wlanConnect
    GTRACE(GRP_CME_CONN_ON_CONN,"gCme_PendingWlanConnect.pConnectCmd nullify");
    CME_PRINT_REPORT("\n\rgCme_PendingWlanConnect.pConnectCmd nullify");


    gCme_PendingWlanConnect.pConnectCmd = NULL;
    gCme_PendingWlanConnect.pConnectEapCmd = NULL;

    return 1;


}
// ----------------------------------------------------------------------------
int32_t CME_BssLoss(uint32_t aRoleId)
{
    HOOK(HOOK_IN_CME);

#if defined(SL_WOLFSSL_BRINGUP_TESTS) || defined(DISABLE_BSS_LOSS_EVENT)
    // during the bring up tests, the long run of the
    // crypto operations cause a disconnection
    // due to beacon loss (no entry to ip thread)
#warning "TODO: undef by properly integrating wolfssl long key operations (TLS)"//TODO what is the requirement
    //Don't disconnect on BSS loss for now (tls takes too much time, stucking the lrxp thread).
    return 0;
#else

    //TODO "TODO: BSS loss event should be called also in WPS, once moving from Supplicant SW crypto calculations to crypto subsystem"
    if ((!CME_IsOngoingWPSAdHocConnection())) /* TODO:  TLS handshack && (!isOnGoingTLSHandshake()))*/
    {
        cmeMsg_t msg;

        GTRACE(GRP_CME, "Got BSS loss event, replacing with internal disconnect command. ");

        // This handles the BSS loss event by simulating a regular disconnect command, initiated locally.
        // The cme module will then try to reconnect according to its profiles database.
        // A more generic implementation should involve kind of roaming manager - will not be implemented for now.
        msg.msgId = CME_MESSAGE_ID_WLAN_DISCONNECT;
        msg.roleId = aRoleId;
        msg.generalData = CME_GENERAL_DATA_DISCONNECT_IS_BSS_LOSS ;//indicate if its bssloss

        return pushMsg2Queue(&msg);
    }
    else
    {
        GTRACE(GRP_CME, "Got BSS loss event, disregard in WPS/TLS handshake - temp!!! ");

        return 0;
    }
#endif
}

//
// cmeFreePendingWlanConnectResources -
//                                      free the original command resource block
//
void cmeFreePendingWlanConnectResources()
{
    HOOK(HOOK_IN_CME);

#if 0
    if (gCme_PendingWlanConnect.pConnectEapCmd)
    {
        os_free(gCme_PendingWlanConnect.pConnectEapCmd);
        gCme_PendingWlanConnect.pConnectEapCmd = NULL;
    }
#endif
    if (gCme_PendingWlanConnect.pConnectCmd)
    {
        os_free(gCme_PendingWlanConnect.pConnectCmd);

    }

    gCme_PendingWlanConnect.pConnectCmd = NULL;

    GTRACE(GRP_CME,"cmeFreePendingWlanConnectResources");
}

void cme_Thread(void* apParam)
{
    HOOK(HOOK_IN_CME);

    int32_t            eloopTimeout;
    uint32_t           timeoutMs = 0xFFFFFFFF;
    cmeMsg_t           msg;
    OsiReturnVal_e     rc;
    int role_switch_rc;
    volatile BOOLEAN running;

    BOOLEAN sendInternalEvent = FALSE;
    BOOLEAN bRemovePeerNeeded = FALSE;

    // Simulations code -------------------------------------------------------
#ifndef CC33XX_NO_CME_TEST //TODO do we need CC33XX_NO_CME_TEST
    Bool32 simGetScanResults = FALSE;

    //-------------------------------------------------------------------------
    // Simulations code
    // set simScanResult to TRUE in order to simulate scan results.
    Bool32 simScanResult = FALSE;
    //-------------------------------------------------------------------------
#endif
    // Simulations code -------------------------------------------------------

    running = TRUE;

    while(gContRunThrdLoopCme)
    {

    if(running)
    {
        CME_PRINT_REPORT("\n\rcme_Thread: thrd is up and running");
    }

    cmeMngInit();

    gCmeRoleSwitchActive = FALSE;


    //signal that thread is up and running
    osi_SyncObjSignal(&gCmeThreadStarted);


    while(running)
    {
        //Access eloop only if supplicant is initialized
        if (gpSupplicantGlobals)
        {
           eloopTimeout = eloop_get_timeout();
        }
        else
        {
           eloopTimeout = -1;
        }

        if (eloopTimeout < 0)
        {
           // if no timer event was detected, wait forever
           timeoutMs = OSI_WAIT_FOREVER;
        }
        else
        {
           // if eloop is expecting a timer event, waiting on message queue for timeoutMS
           timeoutMs = eloopTimeout;
           //GTRACE(GRP_CME_DEBUG, "CME is waiting on message queue for %d msecs", timeoutMs);
        }

        rc = osi_MsgQRead(&gCmeMessageQueue, &msg, timeoutMs);

        if(OSI_OK == rc)
        {
            //CME_PRINT_REPORT("\n\rCME osi_MsgQRead rc:%d msg.msgId:%d", rc, msg.msgId);
            //GTRACE(GRP_CME, "CME: handle msgN0=%d", msg.msgId);

            switch (msg.msgId)
            {
                case CME_MESSAGE_ID_CSA_NOTIFY:
                {
                    int ret = 0;
                    Bool32 isDfsChannel;

                    gCmdChannelSwitchStart.channelSwitchParams.RoleID = msg.roleId;
                    gCmdChannelSwitchStart.channelSwitchParams.stopTx = msg.un.channelSwitchIe[0];
                    gCmdChannelSwitchStart.channelSwitchParams.channel = msg.un.channelSwitchIe[1];
                    gCmdChannelSwitchStart.channelSwitchParams.switchTime = msg.un.channelSwitchIe[2];
                    //gCmdChannelSwitchStart.channelSwitchParams.band = ;

                    // set isDfsChannel if needed
                    regulatoryDomain_IsChannelSupported(gCmdChannelSwitchStart.channelSwitchParams.channel,
                                                        &isDfsChannel);

                    gCmdChannelSwitchStart.channelSwitchParams.isDfsChannel = (uint8_t )isDfsChannel;

                    ret = WLSendFW_Command(CMD_CHANNEL_SWITCH, CMD_CHANNEL_SWITCH, 
                                           (void *)&gCmdChannelSwitchStart,
                                           sizeof(cmd_channel_switch_t), NULL, 0);
                }
                break; // CME_MESSAGE_ID_CSA_NOTIFY
                case CME_MESSAGE_ID_CS_FINISH:
                {
                    uint8_t channel;
                    
                    channel = gCmdChannelSwitchStart.channelSwitchParams.channel;

                    // Set TX power after channel switch
                    CME_ChannelSwitchSetTxPower(channel);
                    
                    wlanDispatcherSendEvent(WLAN_EVENT_CS_FINISH, (void*)&channel, sizeof(uint8));
                }
                break; //CME_MESSAGE_ID_CS_FINISH:

                case CME_MESSAGE_ID_SCAN_DONE:
                {
                    struct wpa_supplicant *wpa_s = NULL;
                    wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, msg.roleId);
                    GTRACE(GRP_CME, "CME: CME_MESSAGE_ID_SCAN_DONE");
                    CME_PRINT_REPORT("\n\rCME: CME_MESSAGE_ID_SCAN_DONE");
                	CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: CME_MESSAGE_ID_SCAN_DONE, change state to :CME_STA_SCAN_DONE !!");
                    if (wpa_s != NULL)
                    {
                        //msg for scan done received from transport layer
                        //due to user request to stop scan or disconnect
                        CmeStationFlowSM(CME_STA_SCAN_DONE, CmeStationFlow_GetCurrentUser());
                    }
                }
                break;
                case CME_MESSAGE_ID_GET_SCAN_RESULTS:
                {
                    // Start site survey scan only if no survey scan is active
                    if ((gCmeRoleSwitchActive == FALSE)//no active role switch
                         &&(CME_SITE_SURVEY_IDLE == gSetSiteSurvey))
                    {
                        uint8_t role_id = 0;

                        gSiteSurveyInfo.responseStartIndex      = msg.un.getNetworks.index;
                        gSiteSurveyInfo.responseCount           = msg.un.getNetworks.count;
                        gSiteSurveyInfo.responseInternalEvent   = msg.un.getNetworks.getInternalEvent;      

                        if (msg.un.getNetworks.ScanCommon.roleType == WLAN_ROLE_DEVICE)
                        {
                            ti_driver_ifData_t *pDrv = drv_getDriverData(NETIF_NAME(TIWLAN_DEV_NAME_P2PDEV));

                            role_id = (uint8_t) drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_DEVICE);
                            
                            GTRACE(GRP_CME, "CME: CME_MESSAGE_ID_GET_SCAN_RESULTS: roleid=%d, roletype=%d",
                                             pDrv->roleId, pDrv->roleType);

#ifndef TI_STA_ONLY_BUILD
                            cmeStartP2pFind(pDrv->wpa_s, NULL, CME_P2P_DISCOVERY_FIND_TIMEOUT, TRUE);
#endif
                            
                        }
                        else
                        {//AP or STA

                            if (cme_is_sta_role_like_activated())
                            {
                                // Get STA/P2P CL role id from iface
                                role_id = (uint8_t) drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_STA);
                            }
                            else if (cme_is_ap_role_like_activated())
                            {
                                // Get STA/P2P CL role id from iface
                                role_id = (uint8_t) drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_AP);

                            }
                            else
                            {
                                //there shouldnt be a case that no role is active (and not during role switch)
                                ASSERT_GENERAL(0);
                            }

                            ASSERT_GENERAL(role_id != ROLE_ID_NONE);

                            // Start external WPS scan
                            if (isextWPS() && 
                                ((msg.un.getNetworks.ScanCommon.extWpsMode == WLAN_SEC_TYPE_WPS_PBC) || 
                                (msg.un.getNetworks.ScanCommon.extWpsMode == WLAN_SEC_TYPE_WPS_PIN)))
                                
                            {
                                extWpsScan(msg.un.getNetworks.ScanCommon.extWpsMode == CME_SEC_TYPE_WPS_PIN);
                            }
                            else
                            {
                                cmeStartSiteSurvey(role_id, &msg.un.getNetworks.ScanCommon);
                            }

                        }
                    }
                    else
                    {
                        GTRACE(GRP_CME, "CME: site survey is already running");

                    }
                }break; // CME_MESSAGE_ID_GET_SCAN_RESULTS//

                case CME_MESSAGE_ID_NEW_ROLE_SET:
                {
                    GTRACE(GRP_CME, "CME: handle CME_MESSAGE_ID_NEW_ROLE_SET, "
                                    "calledFromCmeThread:%d", 
                                    msg.un.wlanMode.calledFromCmeThread);
                    CME_PRINT_REPORT("\n\rCME: handle CME_MESSAGE_ID_NEW_ROLE_SET: "
                                     "deactivate and activate roles, calledFromCmeThread:%d, "
                                     "gCmeRoleSwitchActive=%d",
                                     msg.un.wlanMode.calledFromCmeThread, gCmeRoleSwitchActive);

                    // New role set request - must be set in command
                    gCme_PendingWlanConnect.pConnectCmd = NULL;

                    // It can be false in case the role switch was initiated internally by CME
                    if (gCmeRoleSwitchActive == TRUE)
                    {
                    	uint8_t signalEvent = !msg.un.wlanMode.calledFromCmeThread;
                        uint32_t actionBitmap = BIT_x(ROLE_STA) | BIT_x(ROLE_AP) | BIT_x(ROLE_DEVICE);

                        role_switch_rc = cme_role_switch_manager(CmeStationFlow_GetCurrentUser(),
                                                                 actionBitmap,
                                                                 signalEvent /* if role switch done signal event */);
                        if (role_switch_rc == 0)
                        {
                            //in case role activation completed - try profile search
                            cmeProfileManagerConfigChange(0, CALLER1);
                        }
                    }
                }break; // CME_MESSAGE_ID_NEW_ROLE_SET //

                case CME_MESSAGE_ID_PS_SET:
                {
                    struct wpa_supplicant *wpa_s = NULL;
                    RoleType_e role_type     = drv_getStaIface(gpSupplicantGlobals, &wpa_s);
                    if((role_type == ROLE_TYPE_NONE) || (wpa_s == NULL))
                    {
                        CME_PRINT_REPORT_ERROR("\r\nCME: CME_MESSAGE_ID_PS_SET ,STA Role is not up");
                        break;
                    }
                    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t*)wpa_s->drv_priv;

                    WlanPowerSave_e aPowerSave = CME_GetPowerSaveMode();

                    if(pDrv->ops->set_ps)
                    {
                        pDrv->ops->set_ps(pDrv->roleId, (uint8_t)aPowerSave);
                    }

                }break; //CME_MESSAGE_ID_PS_SET
#ifndef TI_STA_ONLY_BUILD
                case CME_MESSAGE_ID_START_AP_WPS_SESSION:
                {
                    int8_t ret = 0;
                    wlanWpsSession_t *wpsSession = &(msg.un.wpsSession);
                    uint32_t roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_AP);
                    struct wpa_supplicant *wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);
                    char *endptr;
                    unsigned long pin_val;
                    size_t pin_len = 0;

                    if (NULL == wpa_s)
                    {
                        GTRACE(GRP_CME, "Can't start a WPS session if AP is not activated!");
                        wlanDispatcherSendEvent(WLAN_EVENT_AP_WPS_START_FAILED, (void*)(&ret), sizeof(int8_t));
                        break;
                    }

                    if (wpsSession->wpsMethod == WPS_METHOD_PBC)
                    {
                        ret = wpa_supplicant_ap_wps_pbc(wpa_s, NULL, NULL);
                        if (ret < 0)
                        {
                            GTRACE(GRP_CME, "Failed starting AP WPS PBC session, error code %d", ret);
                            wlanDispatcherSendEvent(WLAN_EVENT_AP_WPS_START_FAILED, (void*)(&ret), sizeof(int8_t));
                            break;
                        }
                    }
                    else
                    {
                        pin_len = strlen(wpsSession->pin);
                        // Validate PIN length: must be 4 or 8 digits
                        if (pin_len != 4 && pin_len != 8) 
                        {
                            GTRACE(GRP_CME, "AP WPS session: invalid PIN length %d (expected 4 or 8)", pin_len);
                            CME_PRINT_REPORT_ERROR("\n\rAP WPS session: invalid PIN length %d (expected 4 or 8)", pin_len);
                            wlanDispatcherSendEvent(WLAN_EVENT_WPS_INVALID_PIN, NULL, 0);
                            break;
                        }

                        pin_val = strtoul(wpsSession->pin, &endptr, 10);
                        if (*endptr != '\0')
                        {
                            GTRACE(GRP_CME, "AP WPS session: invalid PIN - contains non-numeric characters");
                            CME_PRINT_REPORT_ERROR("\n\rAP WPS session: invalid PIN - contains non-numeric characters");
                            wlanDispatcherSendEvent(WLAN_EVENT_WPS_INVALID_PIN, NULL, 0);
                            break;
                        }
                        
                        if (pin_len == 8) 
                        {
                            if (wps_pin_valid(pin_val) == FALSE) 
                            {
                                GTRACE(GRP_CME, "AP WPS session: invalid 8-digit PIN checksum");
                                CME_PRINT_REPORT_ERROR("\n\rAP WPS session: invalid 8-digit PIN checksum");
                                wlanDispatcherSendEvent(WLAN_EVENT_WPS_INVALID_PIN, NULL, 0);
                                break;
                            }
                        }

                        ret = wpa_supplicant_ap_wps_pin(wpa_s, NULL, (const char*)wpsSession->pin, NULL, 0, 0);
                        if (ret < 0)
                        {
                            GTRACE(GRP_CME, "Failed starting AP WPS PIN session, error code %d", ret);
                            wlanDispatcherSendEvent(WLAN_EVENT_AP_WPS_START_FAILED, (void*)(&ret), sizeof(int8_t));
                            break;
                        }
                    }
                }break; //CME_MESSAGE_ID_START_AP_WPS_SESSION

                case CME_MESSAGE_ID_SET_WPS_AP_PIN:
                {
                    int8_t ret = 0;
                    WlanSetWpsApPinParam_t *wpsApPin = &(msg.un.wpsApPin);
                    uint32_t roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_AP);
                    struct wpa_supplicant *wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);
                    char *endptr;
                    unsigned long pin_val;

                    if (NULL == wpa_s)
                    {
                        GTRACE(GRP_CME, "Cannot set WPS AP PIN if AP is not activated!");
                        CME_PRINT_REPORT_ERROR("\r\nCME: CME_MESSAGE_ID_SET_WPS_AP_PIN ,AP Role is not up");
                        ret = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__ROLE_IS_NOT_UP);
                        break;
                    }
                    
                    pin_val = strtoul(wpsApPin->pin, &endptr, 10);
                    if ((*endptr != '\0') || (wps_pin_valid(pin_val) == FALSE)) 
                    {
                        GTRACE(GRP_CME, "AP WPS PIN Set: invalid PIN code received");
                        CME_PRINT_REPORT_ERROR("\r\nCME: CME_MESSAGE_ID_SET_WPS_AP_PIN ,invalid PIN code received");
                        wlanDispatcherSendEvent(WLAN_EVENT_WPS_INVALID_PIN, NULL, 0);
                        break;
                    }

                    ret = hostapd_wps_ap_pin_set(wpa_s->ap_iface->bss[0], (const char*)wpsApPin->pin, wpsApPin->timeout);
                    if (ret < 0)
                    {
                        GTRACE(GRP_CME, "Failed - to set AP WPS PIN, error code %d", ret);
                        CME_PRINT_REPORT_ERROR("\r\nCME: CME_MESSAGE_ID_SET_WPS_AP_PIN ,Failed - to set AP WPS PIN, error code %d", ret);
                        ret = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
                        break;
                    }

                    
                }break; //CME_MESSAGE_ID_SET_WPS_AP_PIN

                case CME_MESSAGE_ID_SET_EXT_WPS_SESSION:
                {
                    int8_t ret = 0;
                    struct wpa_supplicant *pApInterface;
                    wlanSetExtWpsSession_t *wpsParams = &(msg.un.wpsParams);
                    uint32_t roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_AP);
                    pApInterface = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);

                    if (NULL == pApInterface)
                    {
                        GTRACE(GRP_CME, "Can't start a WPS session if AP is not activated!");
                        ASSERT_GENERAL(0);
                    }
                    if (wpsParams->enable)
                    {
                        if (wpsParams->wpsMethod == 0)
                        {
                            ret = ext_wps_registrar_button_pushed(pApInterface, wpsParams->peerMac);
                            if (ret < 0)
                            {
                                GTRACE(GRP_CME, "Failed starting AP WPS PBC session, error code %d", ret);
                                CmeApExtWpsFailureNotify(ret);
                            }
                        }
                        else
                        {
                            ret = ext_wps_registrar_add_pin(pApInterface,
                                                            pApInterface->own_addr,
                                                            NULL, // NULL is used for indicating "any" UUID
                                                            wpsParams->pin,
                                                            os_strlen((char*)wpsParams->pin),
                                                            0);
                            if (ret < 0)
                            {
                                GTRACE(GRP_CME, "Failed starting AP WPS pin session, error code %d", ret);
                                CmeApExtWpsFailureNotify(ret);
                            }
                        }
                    }
                    else
                    {
                        ret = wpa_supplicant_ap_wps_cancel(pApInterface);
                        if (ret < 0)
                        {
                            GTRACE(GRP_CME, "Failed stopping AP WPS session, error code %d", ret);
                            CmeApExtWpsFailureNotify(ret);
                        }
                    }
                }break; //CME_MESSAGE_ID_SET_EXT_WPS_SESSION
#endif // TI_STA_ONLY_BUILD
                case CME_MESSAGE_ID_WLAN_CONNECT:
                {
                    GTRACE(GRP_CME, "CME: CME_MESSAGE_ID_WLAN_CONNECT called. CmeStationFlowIsSMIdle=%d, generalData=0x%x (roleid=%d)",
                           CmeStationFlowIsSMIdle(), 
                           msg.generalData,
                           msg.roleId);
                    CME_PRINT_REPORT("\n\rCME: CME_MESSAGE_ID_WLAN_CONNECT called. generalData=0x%x",msg.generalData);

                    CMEWlanConnectCommon_t *pConnectCmd = msg.un.wlanConnect.pConnectCmd;
                    CMEEapWlanConnect_t *pConnectEapCmd = msg.un.wlanConnect.pConnectEapCmd;
                    BOOLEAN bReconnect = FALSE;

                    /* specifiy this cmd requested by the user */
                    if (msg.generalData & CME_GENERAL_DATA_CONNECT_IS_USER_REQ)
                    {
                        bReconnect = isSameConnectParamsInProgress(pConnectCmd,pConnectEapCmd);

                        if(pConnectCmd)
                        {
                            gSaveCurrentSupplicantProfile = CMEisSameConnectParams(pConnectCmd, SSID_STRING(pConnectCmd), TRUE);
                        }
                        else
                        {
                            gSaveCurrentSupplicantProfile = CMEisSameConnectParams(&pConnectEapCmd->EapCommonConnect, EAP_SSID_STRING(pConnectEapCmd), TRUE);
                        }
                        GTRACE(GRP_CME, "CME: CMEisSameConnectParams = %d", gSaveCurrentSupplicantProfile);
                        CME_PRINT_REPORT("\n\rCME: CMEisSameConnectParams = %d", gSaveCurrentSupplicantProfile);

    
                    }
                   
                    cmeWlanConnectDigest(pConnectCmd, pConnectEapCmd, msg.un.wlanConnect.keyMgmtType, msg.generalData, bReconnect);

                }break; // CME_MESSAGE_ID_WLAN_CONNECT // 
                case CME_MESSAGE_ID_WLAN_DISCONNECT:
                {
                    struct wpa_supplicant *wpa_s;
                    ti_driver_ifData_t *pDrv = NULL;

                    wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, msg.roleId);

                    if(wpa_s != NULL)
                    {
                        pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
                        if(pDrv != NULL && pDrv->pAuthInfo != NULL)
                        {
                            destroyAuthData(pDrv,TRUE);
                        }
                    }

                    GTRACE(GRP_CME, "CME: CME_MESSAGE_ID_WLAN_DISCONNECT request");
                    CME_CON_PRINT("\n\rCME: CME_MESSAGE_ID_WLAN_DISCONNECT request");

                    gSaveCurrentSupplicantProfile = FALSE;

                    if (ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
                    {

                        if (msg.generalData & CME_GENERAL_DATA_DISCONNECT_IS_USER_REQ)
                        {
                            //disconnection initiated by user - we remove pmk cache
                            cmeRemoveWpaPmkCache();
                            cmeReassociationParamsClear();
                        }

                        //check if disconnection needed:
                        if (! CmeStationFlowIsSMIdle() )
                        {
                            Cme_STA_events_e disconnectEvent = ((msg.generalData & CME_GENERAL_DATA_DISCONNECT_IS_BSS_LOSS) ? CME_STA_WLAN_BSS_LOSS_EVENT : CME_STA_WLAN_DISCONNECT_REQ_EVENT);

                            GTRACE(GRP_CME,"Got disconnect command, event ENUM(Cme_STA_events_e, %d)",disconnectEvent);
                            CME_CON_PRINT("\n\rGot disconnect command, event ENUM(Cme_STA_events_e, %d)",disconnectEvent);
                            CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: CME_MESSAGE_ID_WLAN_DISCONNECT, change state to :%d !!", disconnectEvent);


                            if (0 != CmeStationFlowSM(disconnectEvent,CmeStationFlow_GetCurrentUser()))
                            {
                                GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set disconnect in STA flow SM and failed!! ");
                                CME_CON_PRINT("\n\rCME: ERROR!CmeStationFlowSM tried to set disconnect in STA flow SM and failed!! ");
                                ASSERT_GENERAL(0);
                                //exit point
                                break;
                            }
                        }
                        else
                        {
                            GTRACE(GRP_SL_DISPATCH,"CME_MESSAGE_ID_WLAN_DISCONNECT: send disconnect event ");
                            CME_CON_PRINT("\n\rCME_MESSAGE_ID_WLAN_DISCONNECT: send disconnect event ");

                            /* specifiy this cmd iniated by the user */
                            if (msg.generalData & CME_GENERAL_DATA_DISCONNECT_IS_USER_REQ)
                            {
                                //send notification to host on role up
                                WlanEventDisconnect_t*  pArgs;

                                pArgs = os_zalloc(sizeof(WlanEventDisconnect_t));
                                pArgs->ReasonCode = WLAN_DISCONNECT_USER_INITIATED; /* save last disconect reason */

                                if (isextWPS() && isExtWpsInProgress())
                                {
                                    // External WPS, clear state
                                    extWpsClear();
                                }

                                //remove gAdHocProfile_ull profiles
                                cmeClearAdHocProfile(wpa_s);
                                
                                //clear supplicant profiles if exist
                                cmeRemoveAllProfilesFromSupplicant(wpa_s, WLAN_REASON_DEAUTH_LEAVING);
                                pArgs->IsStaIsDiscnctInitiator = 1;
                                
                                wlanDispatcherSendEvent(WLAN_EVENT_DISCONNECT, (void*)pArgs, sizeof(WlanEventDisconnect_t));

                                os_free(pArgs);
                            }

                            cmeProfileManagerConfigChange(0, CALLER9);
                        }
                    }
                    else if (ROLE_IS_TYPE_DEVICE(pDrv->roleType))
                    {
#ifndef TI_STA_ONLY_BUILD
                        cmeStopP2pFind(wpa_s);
#endif

                        GTRACE(GRP_SL_DISPATCH,"CME_MESSAGE_ID_WLAN_DISCONNECT: send disconnect event ");
                        CME_CON_PRINT("\n\rCME_MESSAGE_ID_WLAN_DISCONNECT: send disconnect event ");

                        /* specifiy this cmd iniated by the user */
                        if (msg.generalData & CME_GENERAL_DATA_DISCONNECT_IS_USER_REQ)
                        {
                            //send notification to host on role up
                            WlanEventDisconnect_t*  pArgs;

                            pArgs = os_zalloc(sizeof(WlanEventDisconnect_t));
                            pArgs->ReasonCode = WLAN_DISCONNECT_USER_INITIATED; /* save last disconect reason */

                            pArgs->IsStaIsDiscnctInitiator = 1;

                            wlanDispatcherSendEvent(WLAN_EVENT_DISCONNECT, (void*)pArgs, sizeof(WlanEventDisconnect_t));

                            os_free(pArgs);
                        }
                    }
// TODO: need to implement
#if 0
                            /* ---------------------------------------------------------------------*/
                            /* cmd initaited by the host and we are already disconnected, just do:  */
                            /*    >> stop process timeout monitoring if any                         */
                            /*    >> send internal async event with data (reason)                   */
                            /*       if we are in the middle of API timeout                         */
                            /* ---------------------------------------------------------------------*/

                            GTRACE(GRP_SL_DISPATCH,"CME_MESSAGE_ID_WLAN_DISCONNECT: Stopping process timeout!!! ");

                             sl_host_timeout_process_stop(HOST_API_TIMEOUT_ID_WLAN_DISCONNECT);

                             if (sl_host_timeout_is_api_running(HOST_API_TIMEOUT_ID_WLAN_DISCONNECT))
                             {
                                 CmdParserRetVal_e RetVal;

                                 /* stop the API timeout as well as we send its related event */
                                 sl_host_timeout_api_stop(HOST_API_TIMEOUT_ID_WLAN_DISCONNECT);

                                 /* allocate async the internal event */
                                 SlWlanAsyncResponse_t* pDissEvent = (SlWlanAsyncResponse_t*)AllocateEvent(sizeof(SlWlanAsyncResponse_t), __LINE__);
                                 ASSERT_GENERAL(NULL != pDissEvent);


                                 /* specify disconenct has completed */
                                 pDissEvent->Status = SL_STATUS_OK;
                                 pDissEvent->Data = CME_GetLastDisconnectReason(); /* save last disconect reason */


                                 GTRACE(GRP_SL_DISPATCH,"CME_MESSAGE_ID_WLAN_DISCONNECT: Last reason code=%d",pDissEvent->Data);


                                 /* send the async event to host */
                                 RetVal = sl_dispatcher_sendEvent(SL_OPCODE_WLAN_STAP2PCL_ASYNCDISCONNECTEDRESPONSE,
                                                                  (uint8_t*) pDissEvent,
                                                                  sizeof(SlWlanAsyncResponse_t));

                                 if (RetVal != CMD_PARSER_OK)
                                 {
                                     GTRACE(GRP_SL_DISPATCH,"TLV_2: FAILED TO SEND INTERNAL DISCONNECT EVENT  ");
                                 }
                           }

#endif           

                }break; // CME_MESSAGE_ID_WLAN_DISCONNECT

                case CME_MESSAGE_ID_PROFILE_EAP_ADDED:
                case CME_MESSAGE_ID_PROFILE_ADDED:
                {
                    // Instead of touching this global from the dispatcher context,
                    // we assume that the global is not updated
                    GTRACE(GRP_CME, "CME: CCME_MESSAGE_ID_PROFILE_EAP_ADDED ||CME_MESSAGE_ID_PROFILE_ADDED  request");
				    gPreferredReadFromFS = FALSE;
                    cmeProfileManagerConfigChange(0, CALLER4);
                }break;

                case CME_MESSAGE_ID_PROFILE_REMOVED:
                {
                    // Instead of touching this global from the dispatcher context, we assume that the global is not updated
				    gPreferredReadFromFS = FALSE;
				    cmeIsCurrentlyConnectedProfileDeleted(msg.un.deletedProfileIdx);
                }break; //CME_MESSAGE_ID_PROFILE_REMOVED

#ifndef TI_STA_ONLY_BUILD
                case CME_MESSAGE_ID_AP_REMOVE_PEER:
                {
                    sendInternalEvent = FALSE;
                    bRemovePeerNeeded = FALSE;

                    if (is_broadcast_ether_addr(msg.un.apRemovePeer.macAddr))
                    {
                        GTRACE(GRP_CME, "CME_MESSAGE_ID_AP_REMOVE_PEER: BROADCAST MAC DETECTED.\n");
                        bRemovePeerNeeded = TRUE;
                    }
                    else
                    {
                        if (!cmeAPIsPeerConnected(msg.un.apRemovePeer.macAddr)) 
                        {
                            // The current peer is disconnected (as the last record).
                            GTRACE(GRP_CME, "CME_MESSAGE_ID_AP_REMOVE_PEER: the requested peer is not connected.\n");
                        }
                        else 
                        {
                            // The requested peer is connected.
                            GTRACE(GRP_CME, "CME_MESSAGE_ID_AP_REMOVE_PEER: requested peer is connected - consider remove.\n");

                            if (cmeIsLastPeerRemovedValid())
                            {
                                // There is a peer that is being removed
                                GTRACE(GRP_CME, "CME_MESSAGE_ID_AP_REMOVE_PEER: Last peer removed entry is valid\n");

                                if (cmeIsThisPeerInRemovalProgress(msg.un.apRemovePeer.macAddr))
                                {
                                    // If the desired peer is already being removed,
                                    // then simply ensure that no internal asynchronous events are triggered.
                                    GTRACE(GRP_CME, "CME_MESSAGE_ID_AP_REMOVE_PEER: Do nothing - Same Peer is currently in remove phase\n");
                                }
                                else
                                {
                                    // Other peer is being removed, rejecting the current request to disconnect.
                                    GTRACE(GRP_CME, "CME_MESSAGE_ID_AP_REMOVE_PEER: other peer is currently in remove process - reject this one.\n");
                                    sendInternalEvent = TRUE;
                                }
                            }
                            else
                            {
                                // If the desired peer is connected and not already being removed,
                                // proceed with initiating the disconnection sequence. 
                                bRemovePeerNeeded = TRUE;
                                GTRACE(GRP_CME, "CME_MESSAGE_ID_AP_REMOVE_PEER: Last peer removed entry is invalid\n");
                            }
                        }
                    } // end of is not a broadcast

                    if (TRUE == bRemovePeerNeeded)
                    {
                        // Initiate AP remove peer
                        GTRACE(GRP_SL_DISPATCH, "CME_MESSAGE_ID_AP_REMOVE_PEER: User Initiated: call the actual AP remove peer!\n");
                        cmeApRemovePeer(msg.un.apRemovePeer.macAddr, TRUE);
                    }
                    
                    // Signal to release the lock
                    GTRACE(GRP_CME_DEBUG, "cme_Thread : signaling gCmeCommandBlockingSyncObject.\r\n");
                    if (OSI_OK != osi_SyncObjSignal(&gCmeCommandBlockingSyncObject))
                    {
                        ASSERT_GENERAL(0);
                    }
                }
                break; // CME_MESSAGE_ID_AP_REMOVE_PEER
#endif
                case CME_MESSAGE_ID_RX_MNG_PACK:
                {
                    GTRACE(GRP_CME_DEBUG, "CME is sending a management packet to driver ");
                    RX_MGMT_PRINT("\n\rCME received management packet from FW");
                    drv_handleRxMngPacket(msg.un.txRxPacket.pDesc);
                }break; // CME_MESSAGE_ID_RX_MNG_PACK
                case CME_MESSAGE_ID_UNPROTECTED_DEAUTH_DEASSOC:
                {
                    RX_MGMT_PRINT("\n\rCME received CME_MESSAGE_ID_UNPROTECTED_DEAUTH_DEASSOC from FW");
                    GTRACE(GRP_MGMT_PROTECTION_IMP,"MPF: received deauth/deassoc, passing to supplicant");
                    drv_handleUnprotRxDeauth(msg.un.txRxPacket.pDesc, msg.roleId);
                }break; //CME_MESSAGE_ID_UNPROTECTED_DEAUTH_DEASSOC
                case CME_MESSAGE_ID_RX_FROM_UNKNOWN:
                {
                    drv_handleRxFromUnknown(msg.un.txRxPacket.pDesc, msg.roleId);
                }break; //CME_MESSAGE_ID_UNPROTECTED_DEAUTH_DEASSOC
                case CME_MESSAGE_ID_RX_EAPOL_PACK:
                {
                    RX_MGMT_PRINT("\n\rCME received msg CME_MESSAGE_ID_RX_EAPOL_PACK FW");
                    drv_handleRxEapol(msg.un.txRxPacket.pDesc);
                }break; //CME_MESSAGE_ID_RX_EAPOL_PACK
                case CME_MESSAGE_ID_NEW_ELOOP_TIMEOUT:
                {
                    // nothing to do here, this message was sent only in order to
                    // update the wait on msgQ timeout
                }break; // CME_MESSAGE_ID_NEW_ELOOP_TIMEOUT //

                case CME_MESSAGE_ID_POLICY_SET:
                {
                    cmeMngConnectionPolicyUpdated(msg.un.policy.policy.fastPolicy);
                }break;

                case CME_MESSAGE_ID_SCAN_COMPLETE:
                {
                    uint8_t                 numOfSSID;
#ifndef CC33XX_NO_CME_TEST
                    // Simulate a valid scan result when scan complete indication is received.
                    // For the moment it should be received due to scan timeout.
                    if (TRUE == simScanResult)
                    {
                        cmeTestBuildScanResult(msg.un.postScanInfo.pSharedInfo, msg.un.postScanInfo.scanType);
                        msg.un.postScanInfo.status = CME_SCAN_STATUS_COMPLETE;
                    }
#endif // CC33XX_NO_CME_TEST

                    // If a connection scan was completed ,free profiles memory.
                    // If periodic scan should start,memory shall be re-allocated.
                    // Note:
                    // Scan completed event may be received in some cases when
                    // there's no active scan (for example when interface is removed).
                    // That's the reason for verifying profiles memory is valid before
                    // releasing the memory.

                    CME_PRINT_REPORT("\n\rCME received CME_MESSAGE_ID_SCAN_COMPLETE FW scantype=%d", msg.un.postScanInfo.scanType);
                    GTRACE(GRP_CME,"CME received CME_MESSAGE_ID_SCAN_COMPLETE FW. roleid(%d) SiteSurvgeyState=%d P2pFindStopping=%d", 
                        msg.roleId, gSetSiteSurvey, gCmeP2pInfo.p2pFindStopping);

                    if (SCAN_REQUEST_CONNECT_PERIODIC_SCAN == msg.un.postScanInfo.scanType)
                    {
                        if (NULL != msg.un.postScanInfo.pSharedInfo->mPeriodicProfiles.mpProfiles)
                        {
                            os_free(msg.un.postScanInfo.pSharedInfo->mPeriodicProfiles.mpProfiles);
                            msg.un.postScanInfo.pSharedInfo->mPeriodicProfiles.mpProfiles = NULL;
                            msg.un.postScanInfo.pSharedInfo->mPeriodicProfiles.mNumProfiles = 0;
                        }
                    }
                    else
                    {
                        //here we must decide if one_shot or site survey scan completed

                        //new: sometimes p2p_stop calls for scan_stop while 
                        //     no one_shot scan was triggered
                        //     and we will get mNumProfiles = 0
                        //     in this case: we want to be sure the complete event
                        //     if for stopping one_shot of p2p_stop_find
                        //     Notes
                        //     gSetSiteSurvey == CME_SITE_SURVEY_IDLE
                        //     gCmeP2pInfo.p2pFindStopping == TRUE
                        //     regarding supplicant scans:
                        //     in one shot scans initiated by the supplicant mNumProfiles might be equal to zero,
                        //     so in case we get here when supplicant initiated scan is in progress - 
                        //     check if this is the current scan or a periodic scan that runs in parallel.
                        numOfSSID = msg.un.postScanInfo.pSharedInfo->mOneShotProfiles.mNumProfiles;
                        if ((numOfSSID == 0)
                            && (msg.un.postScanInfo.scanType == SCAN_REQUEST_ONE_SHOT)
                            && (gCmeP2pInfo.p2pFindStopping == FALSE)
                            && ((!gSupplicantInitiatedScanInProgress) || (gSupplicantInitiatedScanInProgress && is_wlan_periodic_scan_in_progress()))
                        )
                        {
                            if(gSetSiteSurvey == CME_SITE_SURVEY_RUNNING)
                            {
                                //Survey scan and one shot has the same scan tag
                                msg.un.postScanInfo.scanType = SCAN_REQUEST_SURVEY_SCAN;
                            }
                            else
                            {
                                GTRACE(GRP_CME,"CME_MESSAGE_ID_SCAN_COMPLETE, Warning! no connection scan in process");
                                CME_PRINT_SCAN_REPORT("\r\nCME_MESSAGE_ID_SCAN_COMPLETE, Warning! no connection scan in process, ignore the SCAN_COMPLETE\r\n");
                                // connection scan should always have profiles
                                //this can happen if scan_complete send from the FW twice ,
                                break;//don't process this scan complete
                            }
                        }
                        else if (NULL != msg.un.postScanInfo.pSharedInfo->mOneShotProfiles.mpProfiles)
                        {

                            os_free(msg.un.postScanInfo.pSharedInfo->mOneShotProfiles.mpProfiles);
                            msg.un.postScanInfo.pSharedInfo->mOneShotProfiles.mpProfiles = NULL;
                            msg.un.postScanInfo.pSharedInfo->mOneShotProfiles.mNumProfiles = 0;
                        }
                    }


                    if (cmeScanComplete(msg.roleId, &msg.un.postScanInfo) > 0)
                    {
                        RoleType_e roleType = drv_getRoleTypeFromRoleId(gpSupplicantGlobals, msg.roleId);

                        if (ROLE_IS_TYPE_STA_BASED(roleType))
                        {
                            //connection SCAN type WAS STOPPED
                            //therefore, we should carry on with operations that were pending
                            //on the scan stop indication

                            //
                            //notify STA flow SM upon disconnection complete event (move to idle)
                            //
                            GTRACE(GRP_CME,"CME: CME_MESSAGE_ID_SCAN_COMPLETE cmeScanComplete ");
                            CME_PRINT_REPORT("\n\rCME: CME_MESSAGE_ID_SCAN_COMPLETE cmeScanComplete ");
                            CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: CME_MESSAGE_ID_SCAN_COMPLETE, change state to CME_STA_WLAN_DISCONNECT_COMPLETE_EVENT !!");

                            if (0 != CmeStationFlowSM(CME_STA_WLAN_DISCONNECT_COMPLETE_EVENT,CmeStationFlow_GetCurrentUser()))
                            {
                                GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set scan in STA flow SM and failed!! ");
                                ASSERT_GENERAL(0); 
                                //exit point
                                break;
                            }

                            //
                            //handle wlanConnect on wlanConnect (waiting for the first one to disconnect)
                            //
                            GTRACE(GRP_CME_CONN_ON_CONN,"gCme_PendingWlanConnect.pConnectCmd value 0x%x",(uint32_t)gCme_PendingWlanConnect.pConnectCmd);
                            CME_CON_PRINT("\n\rgCme_PendingWlanConnect.pConnectCmd value 0x%x",(uint32_t)gCme_PendingWlanConnect.pConnectCmd);
                            if (gCme_PendingWlanConnect.pConnectCmd != NULL)
                            {
                                CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: CME_MESSAGE_ID_SCAN_COMPLETE, change state to CME_STA_NETWORK_SEARCH_EVENT !!");

                                //set state in STA flow SM with wlanConnect User
                                if (0 != CmeStationFlowSM(CME_STA_NETWORK_SEARCH_EVENT,CME_STA_WLAN_CONNECT_USER))
                                {
                                    GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set scan in STA flow SM and failed!! ");
                                    ASSERT_GENERAL(0);
                                    //exit point
                                    break;
                                }

                                GTRACE(GRP_CME,"cme_InternalEventHandler: WlanConnect event trigger following previous network DISCONNECTEd event");
                                CME_CON_PRINT("\n\rcme_InternalEventHandler: WlanConnect event trigger following previous network DISCONNECTEd event");
                                //send the actual connect command with the relevant ssid
                                // gCme_PendingWlanConnect.pConnectEapCmd?
                                cmeWlanConnect(msg.roleId, gCme_PendingWlanConnect.pConnectCmd, gCme_PendingWlanConnect.pConnectEapCmd,
                                            gCme_PendingWlanConnect.keyMgmtType,gCme_PendingWlanConnect.profiles_connection);

                                //clear wlanconnect, releasing the buffer performed inside wlanConnect
                                GTRACE(GRP_CME_CONN_ON_CONN,"gCme_PendingWlanConnect.pConnectCmd nullify");

                                gCme_PendingWlanConnect.pConnectCmd = NULL;
                            }
                            else
                            {
                                if (gCmeRoleSwitchActive == TRUE)
                                {
                                    // maybe ROLE_P2P?
                                    cme_role_switch_manager(CmeStationFlow_GetCurrentUser(),(BIT_x(ROLE_STA) | BIT_x(ROLE_AP)),1/*if role switch done signal event*/);
                                }

                                //In any case (with or without role switch) trigger profile manager to evaluate if profile search should be triggered
                                cmeProfileManagerConfigChange(0,CALLER8);
                            }
                        }
                        else if (ROLE_IS_TYPE_DEVICE(roleType))
                        {
                            GTRACE(GRP_CME_CONN_ON_CONN,"gCme_PendingWlanConnect.pConnectCmd value 0x%x",(uint32_t)gCme_PendingWlanConnect.pConnectCmd);
                            CME_CON_PRINT("\n\rgCme_PendingWlanConnect.pConnectCmd value 0x%x",(uint32_t)gCme_PendingWlanConnect.pConnectCmd);
                            if (gCme_PendingWlanConnect.pConnectCmd != NULL)
                            {
                                //CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: CME_MESSAGE_ID_SCAN_COMPLETE, change state to CME_STA_NETWORK_SEARCH_EVENT !!");
                                //p2p connectio command is pending  due to the stop find
                                cmeWlanConnect(msg.roleId, gCme_PendingWlanConnect.pConnectCmd, NULL,
                                            gCme_PendingWlanConnect.keyMgmtType,gCme_PendingWlanConnect.profiles_connection);

                                //clear wlanconnect, releasing the buffer performed inside wlanConnect 
                                gCme_PendingWlanConnect.pConnectCmd = NULL;
                            }
                        }
                    }

                    if (msg.un.postScanInfo.fromTimeout == TRUE)
                    {
                        wlanDispatcherSendEvent(WLAN_EVENT_GENERAL_ERROR, NULL, 0);
                    }

                }break; // CME_MESSAGE_ID_SCAN_COMPLETE
                case CME_MESSAGE_ID_SCAN_PERIOD_COMPLETE:
                {
                    GTRACE(GRP_CME, "CME: scan period ended, role id %d profiles memory 0x%x",
                           msg.roleId,
                           (uint32_t)msg.un.scanPeriodDoneInfo.pProfiles->mpProfiles);
                    CME_PRINT_REPORT("\n\rCME: CME_MESSAGE_ID_SCAN_PERIOD_COMPLETE Periodic scan in progress ");

                    RoleType_e roleType = drv_getRoleTypeFromRoleId(gpSupplicantGlobals, msg.roleId);
                    struct wpa_supplicant *wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, msg.roleId);

                    // Store candidates information here, to be used when supplicant retrieves the result
                    gCandidatesInfo.numCandidates = msg.un.postScanInfo.pSharedInfo->mNumCandidatesFound;

                    // For STA connection scan, the profile should be set in supplicant DB
                    // before scan result is forwarded.
                    // One candidate is expected for non-WPS connection, but the implementation
                    // is generaic and allows more candidates.
                    // For WPS, Don't add any profile to supplicant DB. Let the supllicant to choose by itself from the scan results.
                    if (ROLE_IS_TYPE_STA_BASED(roleType))
                    {
                        if (!CME_IsOngoingWPSAdHocConnection() && !gSupplicantInitiatedScanInProgress)
                        {
                            for (int i = 0; i < gCandidatesInfo.numCandidates; i++)
                            {
                                addProfileIdToSupplicant(&msg.un.postScanInfo.pSharedInfo->mpCandidateScanResults[i]);
                            }
                        }
                    }

                    CME_periodic_scan_timer_stop();
                    CME_start_periodic_scan_timer();

                    // Notify supplicant of scan period completion
                    drv_handleScanCompleteEvent(wpa_s->drv_priv,
                                                msg.un.postScanInfo.scanType,
                                                gCandidatesInfo.numCandidates);
                    
                    //send msg that periodic scan complete
                    wlanDispatcherSendEvent(WLAN_EVENT_CONNECT_PERIODIC_SCAN_COMPLETE, NULL, 0);
                    //When Periodic scan is in progress, we can't delete the profile
                    //When the profile will be found, it will be proccessed and deleted in CME_MESSAGE_ID_SCAN_COMPLETE
#if 0
                    // Free profiles memory, shall be allocated in the next scan cycle
                    if (NULL != msg.un.scanPeriodDoneInfo.pProfiles)
                    {
                        os_free(msg.un.scanPeriodDoneInfo.pProfiles->mpProfiles);
                        msg.un.scanPeriodDoneInfo.pProfiles->mpProfiles = NULL;
                        msg.un.scanPeriodDoneInfo.pProfiles->mNumProfiles = 0;
                    }
                    if (cmeScanComplete(msg.roleId, &msg.un.postScanInfo) > 0)
                    {
                        //connection SCAN type WAS STOPPED
                        //therefore, we should carry on with operations that were pending
                        //on the scan stop indication

                        //
                        //notify STA flow SM upon disconnection complete event (move to idle)
                        //
                        GTRACE(GRP_CME,"CME: CME_MESSAGE_ID_SCAN_PERIOD_COMPLETE cmeScanComplete ");
                        CME_PRINT_REPORT("\n\rCME: CME_MESSAGE_ID_SCAN_PERIOD_COMPLETE cmeScanComplete ");
                    	CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: CME_MESSAGE_ID_SCAN_PERIOD_COMPLETE, change state to CME_STA_WLAN_DISCONNECT_COMPLETE_EVENT !!");

                        if (0 != CmeStationFlowSM(CME_STA_WLAN_DISCONNECT_COMPLETE_EVENT,CmeStationFlow_GetCurrentUser()))
                        {
                            GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set sta result found in STA flow SM and failed!! ");
                            ASSERT_GENERAL(0);

                        }

                        //
                        //handle wlanConnect on wlanConnect (waiting for the first one to disconnect)
                        //
                        GTRACE(GRP_CME_CONN_ON_CONN,"gCme_PendingWlanConnect.pConnectCmd value 0x%x",(uint32_t)gCme_PendingWlanConnect.pConnectCmd);
                        if (gCme_PendingWlanConnect.pConnectCmd != NULL)
                        {
                        	CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: CME_MESSAGE_ID_SCAN_PERIOD_COMPLETE, change state to CME_STA_WLAN_CONNECT_USER !!");

                            //set state in STA flow SM with wlanConnect User
                            if (0 != CmeStationFlowSM(CME_STA_NETWORK_SEARCH_EVENT,CME_STA_WLAN_CONNECT_USER))
                            {
                                GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set scan in STA flow SM and failed!! ");
                                ASSERT_GENERAL(0); //TODO: , Happened - Need to debug (log exists)
                                //exit point
                                break;
                            }



                            GTRACE(GRP_CME,"cme_InternalEventHandler: WlanConnect event trigger following previous network DISCONNECTEd event");
                            //send the actual connect command with the relevant ssid
                            // gCme_PendingWlanConnect.pConnectEapCmd?
                            cmeWlanConnect(msg.roleId, gCme_PendingWlanConnect.pConnectCmd, NULL,
                                           gCme_PendingWlanConnect.keyMgmtType,gCme_PendingWlanConnect.profiles_connection);

                            //clear wlanconnect, releasing the buffer performed inside wlanConnect
                            GTRACE(GRP_CME_CONN_ON_CONN,"gCme_PendingWlanConnect.pConnectCmd nullify");

                            gCme_PendingWlanConnect.pConnectCmd = NULL;
                        }
                        else
                        {
                            if (gCmeRoleSwitchActive == TRUE)
                            {
                                // maybe ROLE_P2P?
                                cme_role_switch_manager(CmeStationFlow_GetCurrentUser(),(BIT_x(ROLE_STA) | BIT_x(ROLE_AP)),1/*if role switch done signal event*/);
                            }

                            //In any case (with or without role switch) trigger profile manager to evaluate if profile search should be triggered
                            cmeProfileManagerConfigChange(0);
                        }
                    }
#endif                    
                    cmeConsequtiveScanCompletesNoCandidate();

                }break; // CME_MESSAGE_ID_SCAN_PERIOD_COMPLETE

                case CME_MESSAGE_ID_FAST_CONNECTION_TIMEOUT:
                {
				    GTRACE(GRP_CME,"CME_MESSAGE_ID_FAST_CONNECTION_TIMEOUT event");
                    CME_PRINT_PROFILE_REPORT("\r\nCME_MESSAGE_ID_FAST_CONNECTION_TIMEOUT event");
				    cmeFastConnectionTimerReleaseResources();

				    if (0 != CmeStationFlowSM(CME_STA_WLAN_DISCONNECT_REQ_EVENT,CME_STA_FAST_CONNECT_USER))
				    {
				       GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set disconnect in STA flow SM and failed!! ");
				       ASSERT_GENERAL(0);
				    }

				    //if was immediately disconnected - invalidate the connection
				    if (CmeStationFlowIsSMIdle() )
				    {
				        cmeMarkInvalidFastConnectionData();

				        //now, as the SM is idle, fallback to regular WlanConnect
				        cmePendingWlanConnectTrigger();

				    }

                } break; // CME_MESSAGE_ID_FAST_CONNECTION_TIMEOUT

                case CME_MESSAGE_ID_TX_DONE:
                {
                    drv_handleTxResult(msg.un.txRxPacket.pDesc);
                } break; // CME_MESSAGE_ID_TX_DONE


                case CME_MESSAGE_ID_ROC_TIMER_TIMEOUT:
                {
                	uint32_t is_croc_performed_due_to_timeout =0;
                    if(isextDPP())
                    {
                    	CME_CON_PRINT("\n\rCME : WFD ,got msg CME_MESSAGE_ID_ROC_TIMER_TIMEOUT\n\r");

                        //call cancel remain on channel
                        //and deinit the device role
                    	is_croc_performed_due_to_timeout = 1;
                        ti_driver_ext_set_CROC(1,is_croc_performed_due_to_timeout);
                    }
                    else
                    {
                    	CME_CON_PRINT("\n\rCME : got msg CME_MESSAGE_ID_ROC_TIMER_TIMEOUT\n\r");
                        ti_driver_cancel_remain_on_channel_timer_callback_handle();
                    }
                } break;

                case CME_MESSAGE_ID_EXT_ROC:
                {
                    CME_PRINT_ROC_REPORT("\n\rCME : got msg CME_MESSAGE_ID_EXT_ROC\n\r");
                    wpa_drv_remain_on_channel(msg.un.rocParam.wpa_s,
                                              msg.un.rocParam.freq,
                                              msg.un.rocParam.duration);
                    rc = CmeDeviceFlowSM(CME_DEVICE_ROC, CmeDeviceFlow_GetCurrentUser());

                }
                break;
                case CME_MESSAGE_ID_EXT_CROC:
                {
                	Cme_Users_e deviceFlow_GetCurrentUser= CmeDeviceFlow_GetCurrentUser();
                    CME_CON_PRINT("\n\rCME :got msg CME_MESSAGE_ID_EXT_CROC : is_croc_performed_due_to_timeout :%d",
                    		msg.un.rocParam.is_croc_performed_due_to_timeout);
                	if(msg.un.rocParam.is_croc_performed_due_to_timeout)
                	{
                		deviceFlow_GetCurrentUser = CME_DEVICE_ROC_TIMEOUT;
                	}

                    rc = CmeDeviceFlowSM(CME_DEVICE_CROC, deviceFlow_GetCurrentUser);

                }
                break;
                case CME_MESSAGE_ID_EXT_SEND_ACTION:
                {
                    uint8_t *apSrc;
                    int32_t freq;
                    uint32_t aWaitTime ;//ms
                    uint8_t* apBssid;
                    ti_driver_ifData_t  *pDrv;

                    CME_CON_PRINT("\n\rCME :got msg CME_MESSAGE_ID_EXT_SEND_ACTION");
                    pDrv = msg.un.sendActionParam.pDrv;
                    //for take the freq from the driver
                    freq = pDrv->freq;
                    apBssid = pDrv->macAddr;

                    //take the mac addr from the driver
                    apSrc = pDrv->macAddr;
                    aWaitTime = 0; //not used for this scenario
                    rc = ti_driver_send_action(pDrv,
                                              freq,
                                              aWaitTime,
                                              msg.un.sendActionParam.apDst,            // Destination address
                                              apSrc,            //role mac address
                                              apBssid,
                                              msg.un.sendActionParam.actionBuff,
                                              msg.un.sendActionParam.actionBuffLen,
                                              0);
                    os_free(msg.un.sendActionParam.actionBuff);
                    if(rc < 0)
                    {
                        CME_CON_PRINT_ERROR("\n\rERROR ! CME_MESSAGE_ID_EXT_SEND_ACTION failed");
                    }
                    wlanDispatcherSendEvent(WLAN_EVENT_SEND_ACTION_DONE, NULL, 0);

                }
                break;
                case CME_MESSAGE_ID_MAX_RETRY:
                case CME_MESSAGE_ID_INACTIVITY:
                {
                    RX_MGMT_PRINT("\n\rCME received CME_MESSAGE_ID_MAX_RETRY|CME_MESSAGE_ID_INACTIVITY from FW");
                    drv_lowAck(gpSupplicantGlobals, msg.roleId, msg.generalData, (CME_MESSAGE_ID_MAX_RETRY == msg.msgId));
                }break; //  CME_MESSAGE_ID_MAX_RETRY | CME_MESSAGE_ID_INACTIVITY
                case CME_MESSAGE_ID_WPA_SUPP_COMPLETED:
                {
                    struct wpa_supplicant *wpa_s;
                    // Get STA/P2P CL role is valid and select the correct iface
                    RoleType_e role_type = drv_getRoleTypeFromRoleId(gpSupplicantGlobals, msg.roleId);
                    wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, msg.roleId);

                    ASSERT_GENERAL(wpa_s!=NULL);

                   //notify CME manager to update state machine
                   GTRACE(GRP_GENERAL_ERROR, "cme_InternalEventHandler: got event CME_MESSAGE_ID_WPA_SUPP_COMPLETED, role ID %d RoleType=%d",
                             msg.roleId, role_type);

                   //
                   //verify we are on a valid cme mode - connection in progress
                   //

                   if (ROLE_IS_TYPE_STA_BASED(role_type))
                   {
                        //
                        //       in case disconnect arrived during connection sequence we
                        //       should drop this event as it is no longer relevant.
                        //       This check must run even during BTM to handle race conditions
                        //       where DISASSOC arrives while COMPLETED message is queued.
                        //
                        if (CmeStationFlowIsDisconnecting() || wpa_s->wpa_state == WPA_DISCONNECTED)
                        {
                            GTRACE(GRP_CME,"cme_InternalEventHandler: got event CME_MESSAGE_ID_WPA_SUPP_COMPLETED for role ID %d, but SM is in DISCONNECTING state, drop this event (do nothing), supp state %d", msg.roleId,wpa_s->wpa_state);
                            //verify we are indeed not supplicant complete
                            ASSERT_GENERAL(wpa_s->wpa_state < WPA_COMPLETED);
                            if (gBssTransitionState == TRANSITION_IN_PROGRESS)
                            {
                                set_finish_wlan_supplicant_operation();
                                gBssTransitionState = NO_TRANSITION;
                            }
                            break;
                        }

                        // since BSS transition is initiated by the supplicant and not handled by the CME,
                        // we avoid CME internal actions like mode verification and station flow SM update during the reconnection process.
                        if (gBssTransitionState != TRANSITION_IN_PROGRESS)
                        {
                            //
                            //update station flow SM upon wpa suppilcant completed
                            //
                            CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: CME_MESSAGE_ID_WPA_SUPP_COMPLETED, change state to CME_STA_WPA_COMPLETED_EVENT !!");

                            if (0 != CmeStationFlowSM(CME_STA_WPA_COMPLETED_EVENT,CmeStationFlow_GetCurrentUser()))
                            {
                                GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set sta result found in STA flow SM and failed!! ");
                                ASSERT_GENERAL(0);
                            }
                        }

                       //
                       //set started role bitmap indication
                       //
                       cme_set_unset_started_role(TRUE/*set role*/,role_type);


                       //
                       //CC33XX Sep 5 2016 - flush arp cache only if connecting to previous bssid then the last one
                       //
                       //
                       //get bssid address here
                       //
                       ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
                       uint8_t *bssidAddr  = pDrv->currBssid;
                       uint8_t is_first_connect = IRQ_UtilIsZeroMacAddress(gCmeLastConnectedBssId) ;

                       if (!is_first_connect
                               &&
                            (os_memcmp(gCmeLastConnectedBssId, bssidAddr,MAC_ADDR_LEN) !=0 ))
                       {
                           GTRACE(GRP_CME,"CME: cme_InternalEventHandler: currently connected bssid is different then the previously connected one (0x%x:%x:%x:%x:%x:%x), flushing all previous ARP entries",
                                  gCmeLastConnectedBssId[5],gCmeLastConnectedBssId[4],gCmeLastConnectedBssId[3],gCmeLastConnectedBssId[2],gCmeLastConnectedBssId[1],gCmeLastConnectedBssId[0]);
                           CME_PRINT_REPORT("\n\rCME: cme_InternalEventHandler: currently connected bssid is different then the previously connected one (0x%x:%x:%x:%x:%x:%x), flushing all previous ARP entries",
                                  gCmeLastConnectedBssId[5],gCmeLastConnectedBssId[4],gCmeLastConnectedBssId[3],gCmeLastConnectedBssId[2],gCmeLastConnectedBssId[1],gCmeLastConnectedBssId[0]);

                           //if connected to a different bssid than the last one then previous ARP entries should be flushed
                           //otherwise - let it be
                          // _nx_arp_dynamic_entries_invalidate(&ip_0);

                       }
                       else
                       {
                           GTRACE(GRP_CME,"CME: cme_InternalEventHandler:is_first_connect=%d OR currently connected bssid is EQUAL to the previously connected one (0x%x:%x:%x:%x:%x:%x), keep the ARP entries as is",
                                  is_first_connect,gCmeLastConnectedBssId[5],gCmeLastConnectedBssId[4],gCmeLastConnectedBssId[3],gCmeLastConnectedBssId[2],gCmeLastConnectedBssId[1],gCmeLastConnectedBssId[0]);
                           CME_PRINT_REPORT("\n\rCME: cme_InternalEventHandler:is_first_connect=%d OR currently connected bssid is EQUAL to the previously connected one (0x%x:%x:%x:%x:%x:%x), keep the ARP entries as is",
                                  is_first_connect,gCmeLastConnectedBssId[5],gCmeLastConnectedBssId[4],gCmeLastConnectedBssId[3],gCmeLastConnectedBssId[2],gCmeLastConnectedBssId[1],gCmeLastConnectedBssId[0]);
                       }

                       //update the newly connected bssid
                       os_memcpy(gCmeLastConnectedBssId, bssidAddr, MAC_ADDR_LEN);

                        if (ROLE_IS_TYPE_P2P_CLIENT(role_type))
                        {
                            WlanEventFormationComplete_t*  pArgs;
                            uint8_t band;

                            pArgs = os_zalloc(sizeof(WlanEventFormationComplete_t));

                            os_memcpy(pArgs->Bssid, bssidAddr, MAC_ADDR_LEN);
                            os_memcpy(pArgs->SsidName, pDrv->ssid, pDrv->ssid_len);
                            pArgs->SsidLen =  pDrv->ssid_len;

                            if(freq_to_chan(pDrv->freq, &pArgs->Channel, &band) < 0)
                            {
                               ASSERT_GENERAL(0);
                            }

                            pArgs->P2pRoleGo = FALSE;

                            wlanDispatcherSendEvent(WLAN_EVENT_P2P_GROUP_STARTED, (void*)pArgs, sizeof(WlanEventFormationComplete_t));
                             
                            os_free(pArgs);
                        }
                        else
                        {
                            WlanEventConnect_t*  pArgs;
                            uint8_t band;

                            pArgs = os_zalloc(sizeof(WlanEventConnect_t));

                            os_memcpy(pArgs->Bssid, bssidAddr, MAC_ADDR_LEN);
                            os_memcpy(pArgs->SsidName, pDrv->ssid, pDrv->ssid_len);
                            pArgs->SsidLen =  pDrv->ssid_len;
                            pArgs->Status = 0;

                            if(freq_to_chan(pDrv->freq, &pArgs->Channel, &band) < 0)
                            {
                               ASSERT_GENERAL(0);
                            }

                            wlanDispatcherSendEvent(WLAN_EVENT_CONNECT, (void*)pArgs, sizeof(WlanEventConnect_t));

                            os_free(pArgs);
                        }

                       

                       //send notification to host on role up
                       //cmeSendConnectionStatusAsyncEvent(1/*connected*/,0,msg.roleId, bssidAddr);

                       //search for wlan profile (preffered) network match, to be inputted to netcfg bringup method (different configuration per profile)
                       //otherwise, return CME_SCAN_MAX_PROFILES
                       //int wlan_profile_idx = cmeProfileIndexSearchByUniqueId(wpa_s->current_ssid->id);

#if 0 // Lwip handler, done  by the appplication
                        if(wpa_s->current_ssid->ssid_len == 0)
                        {
                            /* fill the correct ssid*/
                            RoleSsid_t*  pRoleSsid = Roles_GetSsId(msg.roleId);

                            //wlan netapp role up sequence
                            cme_role_station_ip_netapps_bringup(msg.roleId, pRoleSsid->ssid, pRoleSsid->ssidLength);
                        }
                        else
                        {
                            cme_role_station_ip_netapps_bringup(msg.roleId, wpa_s->current_ssid->ssid, wpa_s->current_ssid->ssid_len);
                        }
#endif
                        if (gBssTransitionState == TRANSITION_IN_PROGRESS)
                        {
                            // in case of bss transition, the reconnection is now completed.
                            // clear the protection bit and reset transition state. the CME is now in control. 
                            set_finish_wlan_supplicant_operation();
                            gBssTransitionState = NO_TRANSITION;
                        }
                        else
                        {
                            //
                            //update station flow SM upon wpa suppilcant completed
                            //
                            CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: CME_MESSAGE_ID_WPA_SUPP_COMPLETED, change state to CME_STA_WLAN_ROLE_UP_EVENT !!");

                            if (0 != CmeStationFlowSM(CME_STA_WLAN_ROLE_UP_EVENT,CmeStationFlow_GetCurrentUser()))
                            {
                                GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set sta result found in STA flow SM and failed!! ");
                                ASSERT_GENERAL(0);

                            }

                            //clear black list connection attempt counter
                            //relevant for profile search connection only (checked according to global index)
                            cmeClearCurrentConnectionAttemptCtr();

                            //*********************
                            //fast connection handler
                            //*********************
                            //cancel fast connect and fast connect timer
                            cmeFastConnectionTimerReleaseResources();

                            cmeFreePendingWlanConnectResources();
                            //validate the fast connection now that it is official success
                            cmeSaveFastConnectionData();

                            //store reassociation related params taken from supplicant
                            cmeReassociationParamsStore();

                            if (ROLE_IS_TYPE_STA(role_type))
                            {
                                //Check if the transition mode is disabled during the connection with Transition mode
                                cmeCheckCurrentIsTransitionMode();
                            }

                        }
                    }
                }break; // CME_MESSAGE_ID_WPA_SUPP_COMPLETED
                case CME_MESSAGE_ID_WPA_SUPP_CONNECTING:
                {
                    struct wpa_supplicant *wpa_s;
                    // Get STA/P2P CL role is valid and select the correct iface
                    RoleType_e role_type = drv_getRoleTypeFromRoleId(gpSupplicantGlobals, msg.roleId);
                    wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, msg.roleId);

                    GTRACE(GRP_CME,"CME: CME_MESSAGE_ID_WPA_SUPP_CONNECTING roletype=%d roleid=%d", role_type, msg.roleId);

                    ASSERT_GENERAL(wpa_s!=NULL);

                    if (ROLE_IS_TYPE_STA_BASED(role_type))
                    {

                        //get bssid address here
                        //
                        ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
                        uint8_t *bssidAddr  = pDrv->currBssid;

                        WlanEventConnecting_t*  pArgs;

                        //update the newly connected bssid
                        os_memcpy(gCmeLastConnectedBssId, bssidAddr, MAC_ADDR_LEN);
                        pArgs = os_zalloc(sizeof(WlanEventConnecting_t));

                        os_memcpy(pArgs->Bssid, bssidAddr, MAC_ADDR_LEN);
                        os_memcpy(pArgs->SsidName, pDrv->ssid, pDrv->ssid_len);
                        pArgs->SsidLen =  pDrv->ssid_len;



                        wlanDispatcherSendEvent(WLAN_EVENT_CONNECTING, (void*)pArgs, sizeof(WlanEventConnecting_t));
                        os_free(pArgs);

                    }
                }break; // CME_MESSAGE_ID_WPA_SUPP_CONNECTING
                case CME_MESSAGE_ID_WPA_SUPP_DISCONNECTED:
                {
                    struct wpa_supplicant *wpa_s;
                    wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, msg.roleId);
                    ti_driver_ifData_t *pDrv = NULL; 
                    RoleType_e role_type = ROLE_ID_NONE;
                    uint16_t disconnect_reason = msg.generalData;
                    int rc = 0;
                    uint8_t isStopping = FALSE;

                    /* save last disconnect reason */
                    gLastDisconnectInfo.ReasonCode = disconnect_reason;

                    if (wpa_s != NULL)
                    {
                        // Get STA/P2P CL role is valid and select the correct iface
                        pDrv = (ti_driver_ifData_t*)wpa_s->drv_priv;
                        role_type = pDrv->roleType;
                    }
                    else
                    {
                        // we are getting here in case of p2p client teardown
                        // and client role was deactivated
                        // and wpa_s is NULL 
                        
                        CME_PRINT_REPORT("\r\n CME: CME_MESSAGE_ID_WPA_SUPP_DISCONNECTED, wpa_s is NULL!! (roleid=%d) gCmeRoleSwitchActive =%d",
                               msg.roleId, gCmeRoleSwitchActive);
                        // unset p2p_client role       
                        set_finish_wlan_supplicant_operation();
                        cme_set_unset_started_role(FALSE, ROLE_P2P_CL);


                        break;
                        ASSERT_GENERAL(0);
                    }


                    if ((pDrv != NULL) && (pDrv->pAuthInfo != NULL))
                    {
                        destroyAuthData(pDrv, TRUE);
                    }

                    int is_sta_connected = cme_is_started_role_from_type(role_type);
                    

                    ASSERT_GENERAL(wpa_s!=NULL);

                    int is_fast_connection = (CmeStationFlow_GetCurrentUser() ==  CME_STA_FAST_CONNECT_USER ? 1 : 0);

                    GTRACE(GRP_CME,"cme_InternalEventHandler: got event CME_MESSAGE_ID_WPA_SUPP_DISCONNECTED role ID %d (roleType=%d) reason %d",
                                   msg.roleId, pDrv->roleType, msg.generalData);
                    CME_PRINT_REPORT("\r\nCME: got event CME_MESSAGE_ID_WPA_SUPP_DISCONNECTED role ID %d (roleType=%d) reason %d is_fast_connection=%d",
                                   msg.roleId, pDrv->roleType, msg.generalData, is_fast_connection);

                    //invalidate connecting index in case it was profile search
                    cmeZeroConnectionIndex();


                    if (ROLE_IS_TYPE_STA_BASED(role_type))
                    {
                        //
                        //unset started role bitmap indication
                        //
                        cme_set_unset_started_role(FALSE/*set role*/,role_type);

                    }

                    set_finish_wlan_supplicant_operation();
                    gBssTransitionState = NO_TRANSITION;

                    //
                    //notify STA flow SM upon disconnection event (move to idle)
                    //

                    //remove gAdHocProfile_ull profiles
                    cmeClearAdHocProfile(wpa_s);

                    //
                    //remove profiles from supplicant, not relevant anymore (if it is a result of wlan disconnect it is done already) - check it?
                    //
                    cmeRemoveAllProfilesFromSupplicant(wpa_s, disconnect_reason);

                    
                    if (isextWPS() && isExtWpsInProgress())
                    {
                        // External WPS, clear state
                        extWpsClear();
                    }

                    CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: CME_MESSAGE_ID_WPA_SUPP_DISCONNECTED, change state to CME_STA_WLAN_DISCONNECT_COMPLETE_EVENT !!");
                    if (0 != CmeStationFlowSM(CME_STA_WLAN_DISCONNECT_COMPLETE_EVENT,CmeStationFlow_GetCurrentUser()))
                    {
                        GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set sta result found in STA flow SM and failed!! ");
                        ASSERT_GENERAL(0);
                    }
                    
                    //
                    //CME was success to disconnect, now lets check if also need to  perform role_down
                    //
                    if (gCmeRoleSwitchActive != FALSE)
                    {
                        CME_PRINT_REPORT("\n\rCME: continue cme_role_switch_manager");

                        //notify STA/P2P deactivation
                        rc = cme_role_switch_manager(CmeStationFlow_GetCurrentUser(),(BIT_x(ROLE_STA)),1/*if role switch done signal event*/);
                        isStopping = TRUE;

                    }
                    //handle fast connect deauth receive (while not yet connected)
                    else if
                    (
                            is_fast_connection
#ifndef CC33XX_NO_CME_TEST
                            || cmeIsFastTest()
#endif
                    )
                    {
#ifndef CC33XX_NO_CME_TEST
                        // Simulate init with fast connection
                        if (cmeIsFastTest())
                        {
//                            cmeClearFastTest();
                            // fast is activated only after reset, clear
                            // disconnected indication as it should be 0 after reset
                            wpa_s->disconnected = 0;

                            cmeProfileManagerConfigChange(TRUE);
                            rc = 1; // avoid profile manager operation
                        }
                        else
#endif
                        {
                            //fast connect handling

                            //
                            //if station was not connected then call deauth handler which makes second attempt or release fast connect resources
                            //   (if it was once connected then it was all released during WPA_COMPLETED)
                            //
                            if ( !is_sta_connected )/*handle case where fast connection failed for some reason (before timeout)*/
                            {
                                rc = cmeFastConnectionDeAuthHandler(wpa_s);
                            }

                        }
                    }

                    GTRACE(GRP_CME,"fast connect disconnection: is_sta_connected=%d, disconnect_reason=%d, rc=%d",
                                is_sta_connected, disconnect_reason, rc);
                    CME_PRINT_PROFILE_REPORT("\r\nfast connect disconnection: is_sta_connected=%d, disconnect_reason=%d, rc=%d gCmeRoleSwitchActive=%d",
                                is_sta_connected, disconnect_reason, rc, gCmeRoleSwitchActive);
                    //            
                    //   In case station was connected before, but the disconnection arrives from the AP (and not local disconnect request)
                    //   then we should invalidate the fast connection data, in case it was valid
                    //
        #if 0 // Save old algorithm for now
                    if (is_sta_connected && (WLAN_REASON_DEAUTH_LEAVING != disconnect_reason))/*in case*/
                    {
                        cmeMarkInvalidFastConnectionData();
                    }
        #else
                    // Invalidate fast connection data if:
                    // station was connected before disconnection
                    // AND ( the disconnection arrives from a local disconnect request
                    //      OR the disconnection arrives from the AP) <- NEW!!
                    // AND not from the role down
                    // And not part of connect process ( disconnect before connection ?)
                    if (is_sta_connected && 
                        /*(WLAN_REASON_DEAUTH_LEAVING == disconnect_reason) && */
                        (isStopping == FALSE) && 
                        (gCme_PendingWlanConnect.pConnectCmd == NULL))
                    {
                        cmeMarkInvalidFastConnectionData();
                    }
        #endif

                    if (rc == 0)//CME no longer in role switch, and no fast connect second chance
                    {
                        //now, see if wlanConnect command was pending

                        if (cmePendingWlanConnectTrigger()==0)
                        {
                            //trigger profile manager to evaluate if profile search should be triggered
                            cmeProfileManagerConfigChange(0, CALLER7);
                        }
                    }

                    //notify role activation module in case it de-activates a role and waits for disconnect notification
                }break; //CME_MESSAGE_ID_WPA_SUPP_DISCONNECTED
#ifndef TI_STA_ONLY_BUILD
                case CME_MESSAGE_ID_P2P_DEV_FOUND:
                {
                    struct wpa_supplicant *wpa_s;
                    wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, msg.roleId);
                    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t*)wpa_s->drv_priv;

                    GTRACE(GRP_CME, "CME: CME_MESSAGE_ID_P2P_DEV_FOUND call p2p connect roleID=%d", pDrv->roleId);
                    CME_CON_PRINT("\n\rCME: CME_MESSAGE_ID_P2P_DEV_FOUND call p2p connect");
                    
                    cmeP2pConnect(pDrv);
                }
                break;
                case CME_MESSAGE_ID_P2P_NEG_CONFIRMATION:
                {
                    GTRACE(GRP_CME, "CME: (Roleid=%d) CME_MESSAGE_ID_P2P_NEG_CONFIRMATION. Will be %s",
                                    msg.roleId, (msg.generalData == TRUE)?"GO":"CLIENT");
                    if ((msg.generalData == FALSE) && (CmeStationFlowIsSMIdle())) // Client
                    {
                        //We are going to be a P2P Client
                        //only if STA is in idle state we set managed state
                        //set state in STA flow SM with relevant User
                    	CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: CME_MESSAGE_ID_P2P_NEG_CONFIRMATION, change state to CME_STA_NETWORK_SEARCH_EVENT !!");

                        if (0 != CmeStationFlowSM(CME_STA_NETWORK_SEARCH_EVENT, CmeStationFlow_GetCurrentUser()))
                        {
                            GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set scan in STA flow SM and failed!! ");
                            CME_PRINT_REPORT_ERROR("\r\nCME: ERROR!CmeStationFlowSM tried to set scan in STA flow SM and failed!! ");
                            ASSERT_GENERAL(0);
                        }
                    }
                    else
                    {
                        //we are going to be GO
                        //at this point we have enabled role AP
                        //do nothing
                        //supplicant will configure  the rest
                    }

                }break;
#endif
                case CME_MESSAGE_EXT_APP_PROCESS_PROV_DISC_REQ :
                {
#ifndef TI_STA_ONLY_BUILD
                    ext_p2p_process_prov_disc_req( &msg.un.extAppAction.WlanProvDiscResp);
#endif
                    os_free(msg.un.extAppAction.WlanProvDiscResp.provDiscReqData);
                }
                break;
                case CME_MESSAGE_ID_SUPP_DEINIT:
                {
                    GTRACE(GRP_CME, "CME_MESSAGE_ID_SUPP_DEINIT");
                    CME_PRINT_REPORT("\n\r receive event to deinit supplicant");

                    // Deinit supplicant
                    wpa_supplicant_deinit(gpSupplicantGlobals);

                    // Signal the sync object - command blocking

                    if (OSI_OK!=osi_SyncObjSignal(&gCmeCommandStopBlockingSyncObject))

                    {
                        ASSERT_GENERAL(0);
                    }

                }break; //CME_MESSAGE_ID_SUPP_DEINIT
                case CME_MESSAGE_ID_DEINIT:
                {
                    CME_PRINT_REPORT("\n\r receive event to deinit CME thread");
                    if (OSI_OK!=osi_SyncObjSignal(&gCmeThrdRunStopSyncObject))
                    {
                        ASSERT_GENERAL(0);
                    }
                    //CME thread is still running after supplicant deinit
                    running = FALSE;

                }//CME_MESSAGE_ID_DEINIT
                break;
                case CME_MESSAGE_ID_ASSOCIATED:
                {
                    struct wpa_supplicant *wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, msg.roleId);
                    ti_driver_ifData_t *pDrv = ( ti_driver_ifData_t *)wpa_s->drv_priv;
                    CME_PRINT_REPORT("\n\rCME: CME_MESSAGE_ID_ASSOCIATED role ID %d", msg.roleId);
                    if (pDrv->roleStarted == FALSE)
                    {
                        break;
                    }

                    uint8_t *bssidAddr  = pDrv->currBssid;
                    WlanEventAssociated_t*  pArgs;
                    uint8_t band;

                    //update the newly connected bssid
                    os_memcpy(gCmeLastConnectedBssId, bssidAddr, MAC_ADDR_LEN);
                    pArgs = os_zalloc(sizeof(WlanEventAssociated_t));

                    os_memcpy(pArgs->Bssid, bssidAddr, MAC_ADDR_LEN);
                    os_memcpy(pArgs->SsidName, pDrv->ssid, pDrv->ssid_len);
                    pArgs->SsidLen =  pDrv->ssid_len;

                    if(freq_to_chan(pDrv->freq, &pArgs->Channel, &band) < 0)
                    {
                        ASSERT_GENERAL(0);
                        os_free(pArgs);
                        break;
                    }

                    // If external WPS is in progress, cancel the wpa_supplicant "Auth" timeout
                    // This timeout triggers when the WPS registration doesn't start
                    // Currently we let the external WPS user handle this externally
                    if (isextWPS() && isExtWpsInProgress())
                    {
                        pArgs->isExtWPSInProgress = 1;
                        extWpsCancelAuthTimeout();
                    }

                    wlanDispatcherSendEvent(WLAN_EVENT_ASSOCIATED, (void*)pArgs, sizeof(WlanEventAssociated_t));
                    os_free(pArgs);
                }   
                break;
                case CME_MESSAGE_ID_SET_SCAN_DWELL_TIME:
                {
                    WlanScanDwellTime_t  dwellTimes = msg.un.dwellTimes;
                    cmeScan_store_scan_dwell_times(dwellTimes);
                }
                break;
                case CME_MESSAGE_ID_BLE_ENABLED:

                    BleIf_EnableBLE();
                    break;
                case CME_MESSAGE_ID_P2P_CMD:
                {
                    struct wpa_supplicant *wpa_s;
                    
                    //CME_PRINT_REPORT("\n\r CME: P2P CMD #%d", msg.generalData);
                    switch (msg.generalData)
                    {
                        case P2P_CMD_ID_SCAN_STOP:
                        {
                            //we can stop p2p_find on role device only
                            //role device role, if exist stop scan

                            wpa_s = drv_getP2pDeviceSupplicant();

                            if (wpa_s != NULL)
                            {
#ifndef TI_STA_ONLY_BUILD
                                cmeStopP2pFind(wpa_s);
#endif
                            }
                            else
                            {
                                GTRACE(GRP_CME, "CME: ERROR! Stop p2p find failed - no device roleId!!!");
                                CME_PRINT_REPORT("\n\r CME: ERROR! Stop p2p find failed - no device roleId!!!");
                            }
                        }
                        break;

#ifndef TI_STA_ONLY_BUILD
                        case P2P_CMD_ID_GROUP_REMOVE:
                        {
                            cmeP2pGroupRemove();
                        }
                        break;
#endif

                        case P2P_CMD_ID_CONFIG_CHANNELS:
                        {
                            P2pParams_t params;
                            params.operChannel = msg.un.p2pConfigParams.operChannel;
                            params.operReg = msg.un.p2pConfigParams.operClass;
                            params.listenChannel = msg.un.p2pConfigParams.listenChannel;
                            params.listenReg = msg.un.p2pConfigParams.listenClass;
                            params.goIntent = msg.un.p2pConfigParams.goIntent;

                            GTRACE(GRP_CME, "CME: P2P_CMD_ID_CONFIG_CHANNELS setting oper:%d %d listen:%d %d go_intent=%d", 
                            params.operChannel, params.operReg, params.listenChannel, params.listenReg, params.goIntent);

                            cfgSetP2pParameters(&params);

                            //apply changed params on the wpa_supplicant config struct
                            wpa_s = drv_getP2pDeviceSupplicant();

                            if (wpa_s != NULL)
                            {
                                cfgBuildP2pParameters(wpa_s->conf);

                                /* Mark changed fields so wpas_p2p_update_config pushes them
                                * into the running p2p_data module via p2p_set_listen_channel()
                                * and p2p_set_oper_channel().
                                */
                                wpa_s->conf->changed_parameters |= CFG_CHANGED_P2P_LISTEN_CHANNEL |
                                                                    CFG_CHANGED_P2P_OPER_CHANNEL;
                                wpa_supplicant_update_config(wpa_s);

                            }
                            else
                            {
                                /* Device not yet up — channels will be applied at startup via
                                * cfgBuildP2pParameters() in wpa_config_read(). No action needed.
                                */
                                GTRACE(GRP_CME, "CME: ERROR! P2P_CMD_ID_CONFIG_CHANNELS failed - no device roleId!!!");
                                CME_PRINT_REPORT("\n\r CME: ERROR! P2P_CMD_ID_CONFIG_CHANNELS failed - no device roleId!!!");
                            }
   
                        }
                        break;

#ifndef TI_STA_ONLY_BUILD
                        case P2P_CMD_ID_LISTEN:
                        {
                            cmeP2pListen();
                        }
                        break;

                        case P2P_CMD_ID_CANCEL:
                        {
                            cmeP2pCancel();
                        }
                        break;
#endif

#ifndef TI_STA_ONLY_BUILD
                        case P2P_CMD_ID_GROUP_ADD:
                        {
                            cmeP2pGroupAdd(msg.un.p2pGroupAddParams.ssidPostfix,
                                            msg.un.p2pGroupAddParams.freq);
                        }
                        break;
#endif
                        default:

                            break;

                    }

                }
                break;
                case CME_MESSAGE_ID_SET_NON_PREFFERED_CHANNELS:
                {
                    struct wpa_supplicant *wpa_s;
                    uint32_t roleId;

                    roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_STA);
                    if (roleId != INVALID_ROLE_ID)
                    {
                        wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);

                        wpas_mbo_update_non_pref_chan(wpa_s, msg.un.nonPrefChannels.channel_list);
                    }
                    else
                    {
                        GTRACE(GRP_CME, "CME: ERROR! Set non preffered channels failed - no sta roleId!!!");
                        CME_PRINT_REPORT("\n\r CME: ERROR! Set non preffered channels failed - no sta roleId!!!");
                    }

                    os_free(msg.un.nonPrefChannels.channel_list);
                }
                break;
                
                case CME_MESSAGE_ID_SET_SCHED_SCAN_PLANS:
                {
                    struct wpa_supplicant *wpa_s;
                    uint32_t roleId;

                    roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_STA);
                    if (roleId != INVALID_ROLE_ID)
                    {
                        wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);

                        if (!((wpa_s == NULL) || (wpa_s->conf == NULL)))
                        {
                            wpa_s->conf->sched_scan_plans = msg.un.sched_scan_plans;
                            wpa_s->conf->changed_parameters |= CFG_CHANGED_SCHED_SCAN_PLANS;
                            wpa_supplicant_update_config(wpa_s);
                        }
                    }
                    else
                    {
                        GTRACE(GRP_CME, "CME: ERROR! Set sched scan plans failed - no sta roleId!!!");
                        CME_PRINT_REPORT("\n\r CME: ERROR! Set sched scan plans failed - no sta roleId!!!");
                    }

                    os_free(msg.un.sched_scan_plans);
                }
                break;

#ifndef TI_STA_ONLY_BUILD
                case CME_MESSAGE_ID_CONFIGURE_PEER_AGING_TIMEOUT:
                {
                    uint32_t peerAgingTimeout = msg.un.peerAgingTimeout;
                    RoleType_e RoleType = ROLE_AP;
                    int32_t roleId;
                    ti_driver_ifData_t * pDrv = NULL;

                    CME_PRINT_REPORT("\n\rCME_MESSAGE_ID_CONFIGURE_PEER_AGING_TIMEOUT, peerAgingTimeoutEvent:%d", peerAgingTimeout);
                    GTRACE(GRP_CME, "CME_MESSAGE_ID_SET__VENDOR_ELEMETS peerAgingTimeoutEvent:%d",peerAgingTimeout);

                    roleId = drv_getRoleIdFromType(gpSupplicantGlobals,RoleType);
                    if(roleId == ROLE_ID_NONE)
                    {
                        GTRACE(GRP_DRIVER_CC33, "CME:CME_MESSAGE_ID_CONFIGURE_PEER_AGING_TIMEOUT:Role is not up");
                        CME_PRINT_REPORT_ERROR("\n\rCME:CME_MESSAGE_ID_CONFIGURE_PEER_AGING_TIMEOUT:Role is not up");
                        break;
                    }
                    pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);
                    if(pDrv == NULL)
                    {
                        GTRACE(GRP_DRIVER_CC33, "CME :CME_MESSAGE_ID_CONFIGURE_PEER_AGING_TIMEOUT:Role is not up, pDrv is null");
                        CME_PRINT_REPORT_ERROR("\n\rCME:CME_MESSAGE_ID_CONFIGURE_PEER_AGING_TIMEOUT:Role is not up, pDrv is null");
                        break;
                    }

                    pDrv->peerAgingTimeout = peerAgingTimeout;
                    if(pDrv->timerPeerAgingSample.osTimerHandler != NULL)
                    {
                        CME_peer_aging_timer_stop(&pDrv->timerPeerAgingSample);
                    }

                    if(peerAgingTimeout)
                    {
                        CME_start_peer_aging_timer(&pDrv->timerPeerAgingSample, peerAgingTimeout);
                    }
                }
                break;
#endif

#ifndef TI_STA_ONLY_BUILD
                case CME_MESSAGE_ID_PEER_AGING_SAMPLE_TIME:
                {
                    RoleType_e RoleType = ROLE_AP;
                    int32_t roleId;
                    ti_driver_ifData_t * pDrv = NULL;
                    int32_t inActTime;
                    uint8_t *addr;
                    int32_t NumPeer;
                    int i;
                    uint8_t *p_mac_addr_peer_list;//[MAX_NUM_OF_AP_UNICAST_LINKS][6];
                    WlanEventPeerAging_t*  pArgs;

                    roleId = drv_getRoleIdFromType(gpSupplicantGlobals,RoleType);
                    if(roleId == ROLE_ID_NONE)
                    {
                        GTRACE(GRP_DRIVER_CC33, "CME:CME_MESSAGE_ID_PEER_AGING_SAMPLE_TIME:Role is not up");
                        CME_PRINT_REPORT_ERROR("\n\rCME:CME_MESSAGE_ID_PEER_AGING_SAMPLE_TIME:Role is not up");
                        break;
                    }
                    pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);
                    if(pDrv == NULL)
                    {
                        GTRACE(GRP_DRIVER_CC33, "CME :CME_MESSAGE_ID_PEER_AGING_SAMPLE_TIME:Role is not up, pDrv is null");
                        CME_PRINT_REPORT_ERROR("\n\rCME:CME_MESSAGE_ID_PEER_AGING_SAMPLE_TIME:Role is not up, pDrv is null");
                        break;
                    }


                    wlanLinks_getPeerList(&NumPeer, &p_mac_addr_peer_list);

                    for(i=0;i<(NumPeer*MAC_ADDR_LEN);i+= MAC_ADDR_LEN)
                    {
                        addr = (uint8_t*)&p_mac_addr_peer_list[i];

                        inActTime = ti_driver_inact_mili(pDrv, addr);

                        if(inActTime > 0)
                        {
                            //CME_PRINT_REPORT("\n\rCME:Aging of Peer=" MACSTR ", inActime: %d",MAC2STR(addr), inActTime);
                            if((pDrv->peerAgingTimeout) && (inActTime > pDrv->peerAgingTimeout))
                            {
                                pArgs = os_zalloc(sizeof(WlanEventPeerAging_t));
                                if(pArgs == NULL)
                                {
                                    CME_PRINT_REPORT_ERROR("\n\rCME:CME_MESSAGE_ID_PEER_AGING_SAMPLE_TIME: allocation for pargs failed");
                                }
                                else
                                {
                                    pArgs->inactiveTime = inActTime;
                                    MAC_COPY(pArgs->peer_mac, addr);
                                    wlanDispatcherSendEvent(WLAN_EVENT_PEER_AGING, (void*)pArgs, sizeof(WlanEventPeerAging_t));
                                    os_free(pArgs);
                                }
                            }
                        }
                    }

                    if(p_mac_addr_peer_list != NULL)
                    {
                        os_free(p_mac_addr_peer_list);
                    }

                    if(pDrv->peerAgingTimeout> 0)
                    {
                        //CME_PRINT_REPORT("\n\rCME_MESSAGE_ID_PEER_AGING_SAMPLE_TIMECME_start_peer_aging_timer");

                        CME_start_peer_aging_timer(&pDrv->timerPeerAgingSample, pDrv->peerAgingTimeout);
                    }
                }
                break;
#endif
                case CME_MESSAGE_ID_SET_VENDOR_ELEMETS:
                {
                    int32_t roleId;
                    ti_driver_ifData_t * pDrv;
                    uint16_t length= msg.un.vendorElements.vendorElements_length;
                    uint8_t* pData = msg.un.vendorElements.pVendorElements;

                    CME_PRINT_REPORT("\n\rCME_MESSAGE_ID_SET__VENDOR_ELEMETS, length:%d", length);
                    GTRACE(GRP_CME, "CME_MESSAGE_ID_SET__VENDOR_ELEMETS");

                    roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)msg.un.vendorElements.roleType);
                    if(roleId == ROLE_ID_NONE)
                    {
                        GTRACE(GRP_DRIVER_CC33, "CME:WLAN_SET_VENDOR_IE:Role is not up");
                        CME_PRINT_REPORT_ERROR("\n\rCME:WLAN_SET_VENDOR_IE:Role is not up");
                        if(pData)
                        {
                            os_free(pData);
                        }
                        break;
                    }
                    pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);
                    if(pDrv == NULL)
                    {
                        GTRACE(GRP_DRIVER_CC33, "CME :WLAN_SET_VENDOR_IE:Role is not up, pDrv is null");
                        CME_PRINT_REPORT_ERROR("\n\rCME:WLAN_SET_VENDOR_IE:Role is not up, pDrv is null");
                        if(pData)
                        {
                            os_free(pData);
                        }
                        break;
                    }

                    ////////// AP role
#ifndef TI_STA_ONLY_BUILD
                    if(msg.un.vendorElements.roleType == ROLE_AP)
                    {
                        struct wpa_supplicant *wpa_s = pDrv->ctx;
                        struct hostapd_data *hapd = wpa_s->ap_iface->bss[0];
                        struct wpabuf *  buf = NULL;

                        if(hapd == NULL)
                        {
                            GTRACE(GRP_DRIVER_CC33, "CME :WLAN_SET_VENDOR_IE: hapd is null");
                            CME_PRINT_REPORT_ERROR("\n\rCME:WLAN_SET_VENDOR_IE:hapd is null ");
                            if(pData)
                            {
                                os_free(pData);
                            }
                            break;
                        }

                        //free the buf that already exists
                        if(hapd->conf->assocresp_elements != NULL)
                        {
                            wpabuf_free(hapd->conf->assocresp_elements);
                            hapd->conf->assocresp_elements = NULL;
                        }

                        if(length > 0)
                        {
                            buf = wpabuf_alloc_ext_data(pData, length);
                            if (buf == NULL)
                            {
                                GTRACE(GRP_DRIVER_CC33, "CME :WLAN_SET_VENDOR_IE:failed to allocated mem:%d",length);
                                CME_PRINT_REPORT_ERROR("\n\rCME:WLAN_SET_VENDOR_IE:failed to allocate mem :%d ",length);
                                if(pData)
                                {
                                    os_free(pData);
                                }
                                break;
                            }
                        }
                        hapd->conf->assocresp_elements = buf;//will be freed by the supplicant
                    }
#endif
                    ////////// STA role
                    else//STA
                    {
                        pDrv->vendorIEInfo.vendor_elements_length = length;

                        if(pDrv->vendorIEInfo.vendor_elements)
                        {
                            //free the old vendor iE
                            os_free(pDrv->vendorIEInfo.vendor_elements);
                            pDrv->vendorIEInfo.vendor_elements = NULL;
                        }
                        if(length != 0)
                        {
                            pDrv->vendorIEInfo.vendor_elements = pData;//will be released when the Pdrv is released
                        }

                    }
                }
                break;

                default:
                {

                    HOOK(HOOK_IN_CME);
                    CME_PRINT_REPORT_ERROR("\n\r Not handle message msg.msgId %d", msg.msgId);

                    GTRACE(GRP_GENERAL_ERROR, "Not handle message msg.msgId %d", msg.msgId);
                    ASSERT_GENERAL(0);
                }
            }
        }

        //Access eloop only if supplicant is initialized
        //This is the eloop of the supplicant, it was located in here to reduce adding additional thread,
        if (gpSupplicantGlobals)
        {
             eloop_handle_timeout();
        }
    } // end while(running)
    //wait forever until the thread is deleted
    //or  when thread implementation is disconnect and not delete, this will be signaled
    //CME_PRINT_REPORT("\n\r CME thread , thread on wait loop to be deleted or disconnected !!!");
    if (OSI_OK!=osi_SyncObjWait(&gCmeThrdDummySleep,OSI_WAIT_FOREVER))
    {
        CME_PRINT_REPORT_ERROR("\n\rerror!!! failed to wait   gCmeThrdDummySleep");
    }

    } //while(gContRunThrdLoopCme)
    CME_PRINT_REPORT("\n\r cme_Thread: exit from thread loop !!");
    if (OSI_OK!=osi_SyncObjSignal(&gThrdLoopStoppedCmeSync))
    {
        ASSERT_GENERAL(0);
    }

}


int32_t cme_deinit()
{
    HOOK(HOOK_IN_CME);

    int32_t ret = OSI_OK;
    CME_SuppDeinit(CME_DEINIT_SUPP);

    //if the thread is created by external app gCmeThreadTcb may not use
    if (NULL != gCmeThreadTcb)
    {
        //send CME deinit
        cmeMsg_t msg;
        msg.msgId = CME_MESSAGE_ID_DEINIT;

        //clear previous blocking sync object (this command is blocking)

        if (OSI_INVALID_PARAMS == osi_SyncObjClear(&gCmeCommandStopBlockingSyncObject))

        {
            ASSERT_GENERAL(0);
        }

        pushMsg2Queue(&msg);
        //Stop the CME thread
        //CME_PRINT_REPORT("\n\rSend Request to stop CME thread\n");

        //Wait for the thread stop
        osi_SyncObjWait(&gCmeThrdRunStopSyncObject, OSI_WAIT_FOREVER);

        // ============== Destroy thread ======================== //
        ret = osi_ThreadDelete(&gCmeThreadTcb);
        if(OSI_OK != ret)
        {
            CME_PRINT_REPORT_ERROR("cme_deinit: FAILED to delete thread \n\r");
            ASSERT_GENERAL(0);
            return ret;
        }

        // ============== Delete message queue ======================== //

        ret = osi_MsgQDelete(&gCmeMessageQueue);
        if(OSI_OK != ret)
        {
            CME_PRINT_REPORT_ERROR("cme_deinit: FAILED to delete msgQ \n\r");
            ASSERT_GENERAL(0);
            return ret;
        }
        // ============== Delete sync object ======================== //
        ret = osi_SyncObjDelete(&gCmeCommandBlockingSyncObject);
        if(OSI_OK != ret)
        {
            CME_PRINT_REPORT_ERROR("cme_deinit: FAILED to delete sync object \n\r");
            ASSERT_GENERAL(0);
            return ret;
        }
        ret = osi_SyncObjDelete(&gCmeThreadStarted);
        if(OSI_OK != ret)
        {
            CME_PRINT_REPORT_ERROR("cme_deinit: FAILED to delete sync object \n\r");
            ASSERT_GENERAL(0);
            return ret;
        }


        // ============== Delete sync object ======================== //
        ret = osi_SyncObjDelete(&gCmeCommandStopBlockingSyncObject);
        if(OSI_OK != ret)
        {
            CME_PRINT_REPORT_ERROR("cme_deinit: FAILED to delete sync object \n\r");
            ASSERT_GENERAL(0);
            return ret;
        }
        ret = osi_SyncObjDelete(&gThrdLoopStoppedCmeSync);
        if(OSI_OK != ret)
        {
            CME_PRINT_REPORT_ERROR("cme_deinit: FAILED to delete sync object \n\r");
            ASSERT_GENERAL(0);
            return ret;
        }
        ret = osi_SyncObjDelete(&gCmeThrdRunStopSyncObject);
        if(OSI_OK != ret)
        {
            CME_PRINT_REPORT_ERROR("cme_deinit: FAILED to delete gCmeThrdRunStopSyncObject sync object \n\r");
            ASSERT_GENERAL(0);
            return ret;
        }
        ret = osi_SyncObjDelete(&gCmeThrdDummySleep);
        if(OSI_OK != ret)
        {
            CME_PRINT_REPORT_ERROR("cme_deinit: FAILED to delete gCmeThrdDummySleep sync object \n\r");
            ASSERT_GENERAL(0);
            return ret;
        }
        ret = osi_SyncObjDelete(&gCmeEapolsStaSyncObject);
        if(OSI_OK != ret)
        {
            CME_PRINT_REPORT_ERROR("cme_deinit: FAILED to delete gCmeEapolsStaSyncObject sync object \n\r");
            ASSERT_GENERAL(0);
            return ret;
        }
        ret = osi_SyncObjDelete(&gtxCompleteSyncObj);
        if(OSI_OK != ret)
        {
            CME_PRINT_REPORT_ERROR("cme_deinit: FAILED to delete gtxCompleteSyncObj sync object \n\r");
            ASSERT_GENERAL(0);
            return ret;
        }

        // ============== Free internal WPS configurations ======================== //
        cfgSetWpsParametersCleanUp();
    }
    HOOK(HOOK_IN_CME);

    return OSI_OK;

}

int32_t cme_init()
{
    HOOK(HOOK_IN_CME);

    int32_t rc = OSI_OK;


    gpSupplicantGlobals = NULL;
    os_memset(&gCandidatesInfo, 0, sizeof(gCandidatesInfo));
    gCandidatesInfo.pCandidateScanResults = NULL;
    gCandidatesInfo.numAllocatedResults = 0;
    gCandidatesInfo.numCandidates = 0;

    os_memset(&gLastDisconnectInfo, 0, sizeof(gLastDisconnectInfo));
    // TODO : need to implement Timer
#if 0
    os_memset(&gSupplicantPeriodic_timerEvent, 0, sizeof(gSupplicantPeriodic_timerEvent));
#endif

    GTRACE(GRP_CME_CONN_ON_CONN,"gCme_PendingWlanConnect.pConnectCmd nullify");

    // Debug

    cmeScanInit();


    //cme_InitAfterSleep();
    gCmeRoleSwitchActive = FALSE;
    gCme_PendingWlanConnect.pConnectCmd = NULL;

    /* Clear FW crash flag on init */
    gFwCrashOccurred = 0;
#if 0
    gCme_PendingWlanConnect.pConnectEapCmd = NULL;

    //Init global pointers for access list and private ie (the lists will be read on AP init)
    gBwListCB = NULL;
#endif
    gPrivateIeCB = NULL;

    //initialize p2p info
    gCmeP2pInfo.p2pFindStopping = FALSE;
    gCmeP2pInfo.p2pConnectPending = FALSE;

    /* Connection Policy load */
    LoadConnectionPolicy_GetFromFlash(TRUE, 0);

    // CME role switch is blocking the command mailbox from receiving any other commands
     rc = osi_SyncObjCreate(&gCmeCommandBlockingSyncObject);
     if(rc != OSI_OK)
     {
         GTRACE_NVIC(GRP_CME, "cme_init: Sync object Create failed");
         ASSERT_GENERAL(0);
         return rc;
     }
     rc = osi_SyncObjCreate(&gCmeThreadStarted);
     if(rc != OSI_OK)
     {
         GTRACE_NVIC(GRP_CME, "cme_init: Sync object Create failed");
         ASSERT_GENERAL(0);
         return rc;
     }


     rc = osi_SyncObjCreate(&gCmeThrdRunStopSyncObject);
     if(rc != OSI_OK)
     {
         GTRACE_NVIC(GRP_CME, "cme_init: gCmeThrdRunStopSyncObject object Create failed");
         ASSERT_GENERAL(0);
         return rc;
     }


     rc = osi_SyncObjCreate(&gCmeCommandStopBlockingSyncObject);
     if(rc != OSI_OK)
     {
         GTRACE_NVIC(GRP_CME, "cme_init: Sync object Create failed");
         ASSERT_GENERAL(0);
         return rc;
     }

     rc = osi_SyncObjCreate(&gThrdLoopStoppedCmeSync);
     if(rc != OSI_OK)
     {
         GTRACE_NVIC(GRP_CME, "cme_init: Sync object gThrdLoopStoppedCmeSync Create failed");
         ASSERT_GENERAL(0);
         return rc;
     }

     rc = osi_SyncObjCreate(&gCmeThrdDummySleep);
     if(rc != OSI_OK)
     {
         GTRACE_NVIC(GRP_CME, "cme_init: Sync object gCmeThrdDummySleep Create failed");
         CME_PRINT_REPORT_ERROR("\n\rcme_init: Sync object gCmeThrdDummySleep Create failed");
         ASSERT_GENERAL(0);
         return rc;
     }

     rc = osi_SyncObjCreate(&gCmeEapolsStaSyncObject);
     if(rc != OSI_OK)
     {
         GTRACE_NVIC(GRP_CME, "cme_init: Sync object gCmeEapolsStaSyncObject Create failed");
         ASSERT_GENERAL(0);
         return rc;
     }

     rc = osi_SyncObjCreate(&gtxCompleteSyncObj);
     if(rc != OSI_OK)
     {
         GTRACE_NVIC(GRP_CME, "cme_init: Sync object gtxCompleteSyncObj Create failed");
         ASSERT_GENERAL(0);
         return rc;
     }

    rc = osi_MsgQCreate(&gCmeMessageQueue,
                        "eloopQueue",
                        MSGQ_MSG_SIZE,
                        MSGQ_MAX_NUM_MSGS
                        );

    if(rc != OSI_OK)
    {
        GTRACE_NVIC(GRP_CME, "cme_init: Queue Create failed");
        return rc;
    }

    CME_PRINT_REPORT_ERROR("\n\rcme: osi_ThreadCreate");

    rc = osi_ThreadCreate(&gCmeThreadTcb,                   // Thread control block
                         "cme",                            // Thread name
                          CME_THR_STACK_SIZE,               // Stack size
                          CME_THREAD_PRIORITY,                 // Thread priority
                          cme_Thread,                       // Thread entry function
                          NULL);                             // Thread init parameters

    if (OSI_OK != rc)
    {
        GTRACE_NVIC(GRP_CME,"cme_init: osi_ThreadCreate failed, rc = %d", rc);
       // ASSERT_GENERAL(0);
    }
    else
    {
        GTRACE_NVIC(GRP_CME,"cme_init: osi_ThreadCreate created successfully");
    }
    //wait for CME thread start running
    osi_SyncObjWait(&gCmeThreadStarted, OSI_WAIT_FOREVER);

    HOOK(HOOK_IN_CME);

    return OSI_OK;
}


// ----------------------------------------------------------------------------
// pushMsg2Queue
//      Push a message to CME message queue. Message is popped and handled from
//      CME context
// Parameters:
//      apMsg
// return 0 on success, -1 on failure
// ----------------------------------------------------------------------------
static int32_t pushMsg2Queue(cmeMsg_t *apMsg)
{
    HOOK(HOOK_IN_CME);

    int32_t ret = 0;
    OsiReturnVal_e rc;

    //GTRACE(GRP_CME_DEBUG,"CME add message ENUM(CmeMsgsIds_e, %d)", apMsg->msgId);
    //CME_PRINT_REPORT("\n\r CME add message ENUM(CmeMsgsIds_e, %d)", apMsg->msgId);


    rc = osi_MsgQWrite(&gCmeMessageQueue, apMsg, OSI_NO_WAIT, OSI_FLAG_NOT_FROM_INTR);

    if (OSI_OK != rc)
    {
        CME_PRINT_REPORT_ERROR("\n\rWARNING !!!!!! CME osi_MsgQWrite overflow");
#ifdef CME_MSG_QUEUE_DEBUG
        //for debug purpose, this is left open, will be undef later on
        //the code shouldn't come into this place, we need to drop packet that are not relevant
        //before
        GTRACE(GRP_CME,"CME: current msgID=%d", apMsg->msgId);
        CME_PRINT_REPORT_ERROR("\r\nCME: current msgID=%d roleId:%d", apMsg->msgId, apMsg->roleId);
        debug_print_msg_type_subtype(apMsg);
        cme_debug_print_cME_queue_content(apMsg);
        ASSERT_GENERAL(0);
#endif //CME_MSG_QUEUE_DEBUG
        CME_MsgFree(apMsg);
    }

    return ret;
}


// ----------------------------------------------------------------------------
// pushMsg2Queue_fromIntr
//      Push a message to CME message queue. Message is popped and handled from
//      CME context, this will not use lock, so memory will not be allocated from heap
// Parameters:
//      apMsg
// return 0 on success, -1 on failure
// ----------------------------------------------------------------------------
static int32_t pushMsg2Queue_fromIntr(cmeMsg_t *apMsg)
{
    HOOK(HOOK_IN_CME);

    int32_t ret = 0;
    OsiReturnVal_e rc;

    if(apMsg->msgId != CME_MESSAGE_ID_NEW_ELOOP_TIMEOUT)
    {
        GTRACE(GRP_CME_DEBUG,"CME add message ENUM(CmeMsgsIds_e, %d)", apMsg->msgId);
        //CME_PRINT_REPORT("\n\r CME add message ENUM(CmeMsgsIds_e, %d)", apMsg->msgId);
    }


    rc = osi_MsgQWrite(&gCmeMessageQueue, apMsg , OSI_NO_WAIT,OSI_FLAG_FROM_INTR);

    if (OSI_OK != rc)
    {
        CME_PRINT_REPORT_ERROR("\n\rWARNING !!!!!! CME pushMsg2Queue_fromIntr: osi_MsgQWrite overflow");
#ifdef CME_MSG_QUEUE_DEBUG
        //for debug purpose, this is left open, will be undef later on
        //the code shouldn't come into this place, we need to drop packet that are not relevant
        //before
        GTRACE(GRP_CME,"CME: current msgID=%d", apMsg->msgId);
        CME_PRINT_REPORT_ERROR("\r\nCME: current msgID=%d", apMsg->msgId);
        cme_debug_print_cME_queue_content(apMsg);
        ASSERT_GENERAL(0);
#endif //CME_MSG_QUEUE_DEBUG
        CME_MsgFree(apMsg);

    }

    return ret;
}

// ----------------------------------------------------------------------------
// CME_MsgFree
//      frees msg send to cME queue
// Parameters:
//      apMsg
// return
// ----------------------------------------------------------------------------
void CME_MsgFree(cmeMsg_t *apMsg)
{
    if(apMsg->msgId == CME_MESSAGE_ID_TX_DONE)
    {
        CME_FreeTxDesc(apMsg->un.txRxPacket.pDesc);
    }
    else
    {
        RxBufFree(apMsg->un.txRxPacket.pDesc);
    }

}
#if 0
// ----------------------------------------------------------------------------
// cmeMsgQueueCleanup
//      Try to clean the CME message queue by removing 'unimportant' messages
//      such as
// Parameters:
//      None
// return 0 on success, -1 on failure
// ----------------------------------------------------------------------------
int32_t cmeMsgQueueCleanup (void)
{
    HOOK(HOOK_IN_CME);

    OsiReturnVal_e rc;
    uint32_t numOfMsgs;
    uint8_t cleanedMsgs = 0;
    int i;
    cmeMsg_t msg;

    GTRACE(GRP_CME,"CME message queue cleanup");

    // Protect CME queue since this is called from various thread contexts
    //DISABLE_MED_PRIORITY_INTERRUPTS_NO_RT

    numOfMsgs = osi_MsgQCount(&gCmeMessageQueue);


    //Read messages from CME queue and save only the important ones
    for (i=0; i < numOfMsgs; i++)
    {

        rc = osi_MsgQRead(&gCmeMessageQueue, &msg, OSI_NO_WAIT); //No need to wait, messages should be already in the queue

        if (rc == OSI_OK)
         {
            //before we filter CME_MESSAGE_ID_RX_MNG_PACK
            // check if Rx Frames are safe to drop
            // if Frame BEACON, PROBE REQ or ACTION -> drop
            if (msg.msgId == CME_MESSAGE_ID_RX_MNG_PACK)
            {
                if (isRxMgmtFrameSafeToFilter(msg.un.txRxPacket.pDesc))
                {
                    RxBufFree(msg.un.txRxPacket.pDesc);
                    cleanedMsgs++;
                }
                else
                {
                    //return to queue
                    rc = osi_MsgQWrite(&gCmeMessageQueue, &msg , OSI_NO_WAIT,OSI_FLAG_NOT_FROM_INTR);

                    if (rc != OSI_OK)
                    {
                        GTRACE(GRP_CME,"CME queue write error");
                    }
                }
            }
            //Filter the following messages
            else if ((msg.msgId == CME_MESSAGE_ID_RX_EAPOL_PACK) ||
                (msg.msgId == CME_MESSAGE_ID_RX_FROM_UNKNOWN) ||
                (msg.msgId == CME_MESSAGE_ID_PN_REPLAY_DETECTED) ||
                (msg.msgId == CME_MESSAGE_ID_AES_SW_DECRYPTION_NEEDED) ||
                (msg.msgId == CME_MESSAGE_ID_TX_DONE)) //In case the queue is full, we filter every TX complete (not just the 'safe' ones, see isTxResultSafeToFilter())
            {
                //All the filtered messages that we dump, have a descriptor ID on the same location in the struct,
                //that should be released.
                CME_MsgFree(&msg);
                cleanedMsgs++;

                GTRACE(GRP_CME_DEBUG,"CME Dump message ENUM(CmeMsgsIds_e, %d)", msg.msgId);
            }
            else
            {
                //return to queue
                rc = osi_MsgQWrite(&gCmeMessageQueue, &msg , OSI_NO_WAIT,OSI_FLAG_NOT_FROM_INTR);

                if (rc != OSI_OK)
                {
                    GTRACE(GRP_CME,"CME queue write error");
                }
            }
        }
    }

    // TODO: need to implement critical section
    //ENABLE_MED_PRIORITY_INTERRUPTS_NO_RT  //end critical section

    GTRACE(GRP_CME,"CME %d messages cleaned", cleanedMsgs);

    return (0);
}
#endif
#if 0
// ----------------------------------------------------------------------------
// cmeMsgQueueCleanup
//      Try to clean the CME message queue by removing 'unimportant' messages
//      such as
// Parameters:
//      None
// return 0 on success, -1 on failure
// ----------------------------------------------------------------------------
int32_t cmeMsgQueueCleanupAll (void)
{
    HOOK(HOOK_IN_CME);

    OsiReturnVal_e rc;
    uint32_t numOfMsgs;
    uint8_t cleanedMsgs = 0;
    int i;
    cmeMsg_t msg;

    GTRACE(GRP_CME,"CME message queue cleanup");

    // Protect CME queue since this is called from various thread contexts
    // TODO: need to implement critical section
    //DISABLE_MED_PRIORITY_INTERRUPTS_NO_RT

    numOfMsgs = osi_MsgQCount(&gCmeMessageQueue);


    //Read messages from CME queue and save only the important ones
    for (i=0; i < numOfMsgs; i++)
    {

        rc = osi_MsgQRead(&gCmeMessageQueue, &msg, OSI_NO_WAIT); //No need to wait, messages should be already in the queue


        if (rc == OSI_OK)
        {
            //Filter the following messages
            if ((msg.msgId == CME_MESSAGE_ID_RX_MNG_PACK) ||
                (msg.msgId == CME_MESSAGE_ID_RX_EAPOL_PACK) ||
                (msg.msgId == CME_MESSAGE_ID_RX_FROM_UNKNOWN) ||
                (msg.msgId == CME_MESSAGE_ID_PN_REPLAY_DETECTED) ||
                (msg.msgId == CME_MESSAGE_ID_AES_SW_DECRYPTION_NEEDED) ||
                (msg.msgId == CME_MESSAGE_ID_TX_DONE)) //In case the queue is full, we filter every TX complete (not just the 'safe' ones, see isTxResultSafeToFilter())
            {
                //All the filtered messages that we dump, have a descriptor ID on the same location in the struct,
                //that should be released.
                if(msg.msgId == CME_MESSAGE_ID_TX_DONE)
                {
                    CME_FreeTxDesc(msg.un.txRxPacket.pDesc);
                }
                else
                {
                    RxBufFree(msg.un.txRxPacket.pDesc);
                }
                cleanedMsgs++;

                GTRACE_NVIC(GRP_CME_DEBUG,"CME Dump message ENUM(CmeMsgsIds_e, %d)", msg.msgId);
            }
        }
    }

    // TODO: need to implement critical section
    //ENABLE_MED_PRIORITY_INTERRUPTS_NO_RT  //end critical section

    GTRACE(GRP_CME,"CME %d messages cleaned", cleanedMsgs);

    return (0);
}
#endif

static BOOLEAN isMsgQueueAboveThreshold()
{
    HOOK(HOOK_IN_CME);

    uint32_t numOfMsgs;

    numOfMsgs = osi_MsgQCount(&gCmeMessageQueue);


    if (numOfMsgs >= MSGQ_MAX_THRESHOLD)
    {
        GTRACE(GRP_CME,"CME: Msg queue above threshold, numOfMsgs:%d", numOfMsgs);
        //CME_PRINT_REPORT("\n\rCME: Msg queue above threshold, numOfMsgs:%d", numOfMsgs);

#ifdef CME_QUEUE_DEBUG

        int i = 0;
        OsiReturnVal_e rc; 
        cmeMsg_t msg;

        for (i = 0; i < numOfMsgs; i++)
        {
            rc = osi_MsgQRead(&gCmeMessageQueue, &msg, OSI_NO_WAIT);
            if (rc == OSI_OK)
            {
                GTRACE(GRP_CME,"CME: Queue=%d, msgID=%d", i, msg.msgId);
                Report("\r\nCME: Queue=%d, msgID=%d", i, msg.msgId);
            }
        
        }
        ASSERT_GENERAL(0);
        
#endif //CME_QUEUE_DEBUG
        return TRUE;
    }
    return FALSE;
}

int32_t CME_EloopTimeoutUpdated()
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_NEW_ELOOP_TIMEOUT;
#ifdef CC33XX_CME_DEBUG
    ++gCmeDebugInfo.numEloopTimeouts;
#endif

    return pushMsg2Queue(&msg);
}

//Check which Rx Mgmt messages are safe to filter, in case the CME queue fill up.
//For now drop only: Beacon and Probe Requests (in AP role)

static Bool32 isRxMgmtFrameSafeToFilter (void *descriptor)
{
    uint16 fc, type, stype;
    RxIfDescriptor_t *desc = (RxIfDescriptor_t *)descriptor;
    struct ieee80211_mgmt *pMngPack;
    Bool32 retVal = FALSE;

    // Extract transmitted packet type and verify it was a management packet
    pMngPack = (struct ieee80211_mgmt *)(uint8_t*)RX_BUF_DATA(desc);

    fc = le_to_host16(pMngPack->frame_control);
    type = WLAN_FC_GET_TYPE(fc);
    stype = WLAN_FC_GET_STYPE(fc);

    GTRACE(GRP_CME,"CME: Rx frame type=%d, stype=%d", type, stype);
    //Report("\r\n CME:Current msg, Rx frame type=%d, stype=%d", type, stype);

    // Check if frames belong to AP role?

    if (type == WLAN_FC_TYPE_MGMT)
    {   
        if ((stype == WLAN_FC_STYPE_PROBE_REQ)  || (stype == WLAN_FC_STYPE_ACTION) ||(stype == WLAN_FC_STYPE_DEAUTH)
         || (stype == WLAN_FC_STYPE_BEACON) || (stype == WLAN_FC_STYPE_PROBE_RESP))
        {
            retVal = TRUE;
        }

    }

/*
    if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
        if ((type == WLAN_FC_TYPE_MGMT) &&
            ((stype == WLAN_FC_STYPE_PROBE_RESP)  || (stype == WLAN_FC_STYPE_ACTION)))
        {
            retVal = TRUE;
        }
    }
*/
    return retVal;
}

//Check which TX result messages are safe to filter, in case the CME queue fill up.
//For now drop only TX done on probe responses or action frames (assuming these fill the queue, and it is anyway safe
//to clean them since supplicant disregards them as well)
static Bool32 isTxResultSafeToFilter (void *descriptor)
{
    uint16 fc, type, stype;
    TxIfDescriptor_t *desc = (TxIfDescriptor_t *)descriptor;
    struct ieee80211_mgmt *pMngPack;
    tiwdrv_netif_id_e netIfId = TIWDRV_NETIF_ID_NONE;
    Bool32 retVal = FALSE;

    // Extract transmitted packet type and verify it was a management packet
    pMngPack = (struct ieee80211_mgmt *)(uint8_t*)RX_BUF_DATA(desc);

    fc = le_to_host16(pMngPack->frame_control);
    type = WLAN_FC_GET_TYPE(fc);
    stype = WLAN_FC_GET_STYPE(fc);

    //convert link desc->hlid to role Type 
    netIfId = wlanLinks_GetNetIfId(desc->hlid);
    //for AP role -> drop Probe resp and actions
    if (netIfId == TIWDRV_NETIF_ID_SAP)
    //if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
        if ((type == WLAN_FC_TYPE_MGMT) &&
            ((stype == WLAN_FC_STYPE_PROBE_RESP)  || (stype == WLAN_FC_STYPE_ACTION)))
        {
            retVal = TRUE;
        }
    }

    return retVal;
}


/* check if there is identical connect cmd already running */
// Function checks if reconnection is needed - i.e. in case both SSID & BSSID are equal, 
// reconnect is not needed and function returns NULL
// in case of WPS connection, if prev connection was WPS and scanning, reconnect is not needed and function returns NULL
static BOOLEAN isSameConnectParamsInProgress(CMEWlanConnectCommon_t *pConnect, CMEEapWlanConnect_t *pConnectEapCmd)
{
    BOOLEAN bReconnect = FALSE;

    int8_t* ssidName;

    CME_WlanStatus_e state = (CME_WlanStatus_e)CmeStationFlowHostStatusGet();

    CMEWlanConnectCommon_t *pConCmd;

    if(pConnectEapCmd)
    {
        pConCmd = &pConnectEapCmd->EapCommonConnect;
        ssidName = EAP_SSID_STRING(pConnectEapCmd);
    }
    else
    {
        pConCmd = pConnect;
        ssidName = SSID_STRING(pConnect);
    }

    GTRACE(GRP_CME, "CME: isSameConnectParamsInProgress: WLAN_STATUS: %d", state);

    if ((state == WLAN_STATUS_SCANNING) || (state == WLAN_STATUS_CONNECTED))
    {
        struct wpa_supplicant *wpa_s;
        BOOLEAN noCheck = TRUE; // Neither SSID nor BSSID where check;

        /* Get STA/P2P CL role is valid and select the correct iface */
        drv_getStaIface(gpSupplicantGlobals, &wpa_s);

        //not WPS
        if ( (pConCmd->SecType != WLAN_SEC_TYPE_WPS_PBC) && (pConCmd->SecType != WLAN_SEC_TYPE_WPS_PIN))
        {
            GTRACE(GRP_CME, "CME: isSameConnectParamsInProgress: Now compare ssid/bssid...");
            if (wpa_s->current_ssid != NULL)
            {
                /* compare the conn params */
                if ((pConCmd->SsidLen > 0) && (wpa_s->current_ssid->ssid_len))
                {
                    bReconnect |= (pConCmd->SsidLen != wpa_s->current_ssid->ssid_len);
                    bReconnect |= !!(memcmp(ssidName, wpa_s->current_ssid->ssid, pConCmd->SsidLen));

                    noCheck = FALSE;
                }

                /* if bssid is not fully null compare it as well */
                if ( pConCmd->Bssid[0] ||
                        pConCmd->Bssid[1] ||
                        pConCmd->Bssid[2] ||
                        pConCmd->Bssid[3] ||
                        pConCmd->Bssid[4] ||
                        pConCmd->Bssid[5] )
                {

                    if (state == WLAN_STATUS_CONNECTED)
                    {
                        /* compare the BSSID */
                        bReconnect |= !!(memcmp(pConCmd->Bssid, wpa_s->bssid, MAC_ADDR_LEN));

                    }
                    else
                    {
                        /* compare the BSSID */
                        bReconnect |= !!(memcmp(pConCmd->Bssid, wpa_s->current_ssid->bssid, MAC_ADDR_LEN));
                    }
                    noCheck = FALSE;
                }

                if (noCheck)
                {
                    //In case neither SSID nor BSSID where compared - it is a reconnect anyway
                    bReconnect = TRUE;
                }

                GTRACE(GRP_CME, "CME: isSameConnectParamsInProgress: bReconnect=%d", bReconnect);
            }
            else
            {
                /* compare with last AdHoc connection */
                BOOLEAN IsDifferent = cmeCompareLastAdHocConnParams(pConCmd);

                GTRACE(GRP_CME, "CME: isSameConnectParamsInProgress: Comparing last AdHoc conn params");

                bReconnect |= IsDifferent;
            }
        }
        //WPS
        else
        {
            GTRACE(GRP_CME, "CME: isSameWPSConnectInProgress: Now check if allready in scanning or change to WPS");
            //check old connection, if WPS step in
            if (CME_IsOngoingWPSAdHocConnection())
            {
                //check if WLAN in scanning or already connected
                if (state == WLAN_STATUS_SCANNING)
                {
                    GTRACE(GRP_CME, "connection was WPS and WLAN scanning, do nothing");
                }
                else
                {
                    GTRACE(GRP_CME, "connection was WPS and WLAN connected, start new connection");
                    bReconnect = TRUE;
                }
            }
            // sectype change to WPS
            else
            {
                GTRACE(GRP_CME, "connection change to WPS, new connection on the way");
                bReconnect = TRUE;
            }
        }

    }
    else
    {
        GTRACE(GRP_CME, "CME: isSameConnectParamsInProgress: not connected & no connect in background.. ");
    }

    HOOK(HOOK_IN_CME);

    return bReconnect;
}

// ----------------------------------------------------------------------------
// validateWlanConnectParams
//      Validate the parameters received in WLAN connect command:
//          role is either STA or P2P
//          security type fits with role type
//          password length fits security type
// Parameters:
//      apCmd - WLAN connect command
// return
// ----------------------------------------------------------------------------
static int32_t validateWlanConnectParams(CMEWlanConnectCommon_t *apCmd)
{
    int32_t      status = 0;

    // Verify STA based role or Device exists
    if (!cme_is_sta_role_like_activated() && !cme_is_device_role_like_activated())
    {
        GTRACE(GRP_SL_DISPATCH, "ERROR: connect command is not supported in AP Mode");
        status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__INVALID_ROLE);
    }
    // verify security type matches role type
#if 0 // no P2P supported
    else if ( (IS_P2P_SEC_TYPE(apCmd->SecType) && !cme_is_p2p_role_configured()) ||
            ( !IS_P2P_SEC_TYPE(apCmd->SecType) &&  cme_is_p2p_role_configured()))
    {
        GTRACE(GRP_SL_DISPATCH, "ERROR: requested security type %d doesn't fit role type  (is p2p %d)",
                apCmd->SecType, cme_is_p2p_role_configured());
        status = WLAN_ERROR_INVALID_ROLE;
    }
#endif
	// If security is needed, verify password is valid
	else if ( (!(apCmd->Flags & WLAN_CONNECT_FLAG_ENTERPRISE_CONNECT)) && (0 == apCmd->PasswordLen) && (
			(( CME_SEC_TYPE_WEP == apCmd->SecType ) || ( CME_SEC_TYPE_WPA_WPA2 == apCmd->SecType ) 
            || ( CME_SEC_TYPE_WPA3 == apCmd->SecType ) || (CME_SEC_TYPE_WPA2_PLUS == apCmd->SecType)) 
            || ( CME_SEC_TYPE_WPA2_WPA3 == apCmd->SecType ) ) )
		// from cc3100 R2 -  ( SL_SEC_TYPE_WEP_SHARED == apCmd->SecType )
	{
		GTRACE(GRP_SL_DISPATCH, "ERROR: password length is 0 while security %d is requested", apCmd->SecType);
		status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_PASSWORD);
	}
	// perform sanity check on received parameters
	else
	{
	    /* ssid length constraint has been removed as we support connection of bssid only */
		if ( (/* (0 == apCmd->SsidLen) ||  */ (SSID_MAX_LEN < apCmd->SsidLen)) && (
				(( CME_SEC_TYPE_WEP == apCmd->SecType ) || ( CME_SEC_TYPE_WPA_WPA2 == apCmd->SecType ))
                || ( CME_SEC_TYPE_WPA3 == apCmd->SecType ) || (CME_SEC_TYPE_WPA2_PLUS == apCmd->SecType)
                || (CME_SEC_TYPE_WPA2_WPA3 == apCmd->SecType) || (CME_SEC_TYPE_WPA_ENT == apCmd->SecType) ) )
		{
			GTRACE(GRP_CME,"Illegal SSID length %d security type %d", apCmd->SsidLen, apCmd->SecType);
			status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_SSID_LEN);
		}
	}
    HOOK(HOOK_IN_CME);

    return status;
}

//
// cmePendingWlanConnectStore
//                          - store the pending connection command block (point at the original buffers)
//
void cmePendingWlanConnectStor(CMEWlanConnectCommon_t *pConnectCmd,CMEEapWlanConnect_t *pConnectEapCmd,uint16_t keyMgmtType, uint8_t profiles_connection)
{
    HOOK(HOOK_IN_CME);

    gCme_PendingWlanConnect.pConnectCmd = pConnectCmd;
    gCme_PendingWlanConnect.pConnectEapCmd = pConnectEapCmd;

    //gCme_PendingWlanConnect.pConnectEapCmd = pConnectEapCmd;

    gCme_PendingWlanConnect.keyMgmtType = keyMgmtType;

    gCme_PendingWlanConnect.profiles_connection = profiles_connection;

    GTRACE(GRP_CME,"gCme_PendingWlanConnect.pConnectCmd copy 0x%x, profiles_connection=%d",(uint32_t)pConnectCmd,profiles_connection);
}


//================================================================
// P2P Related
//================================================================
/******************************************************************************
  Function          : CME_P2pDevFound

  Description       : Prepare p2p connect command and send to CME thread
    
  Input parameters  : roleId
  Output parameters : None

  Return value      : none.
******************************************************************************/
void CME_P2pDevFound(uint32_t aRoleId)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_P2P_DEV_FOUND;
    msg.roleId = aRoleId;

    HOOK(HOOK_IN_CME);
    
    pushMsg2Queue(&msg);
}
/******************************************************************************
  Function          : CME_P2pNegConfirmation

  Description       : Forward to CME the neg confirmation results
    
  Input parameters  : roleId - role index
                      isGO - TRUE (GO) / FALSE (CL)
  Output parameters : None

  Return value      : none.
******************************************************************************/
void CME_P2pNegConfirmation(uint32_t aRoleId, Bool_e isGO)
{
    HOOK(HOOK_IN_CME);

    cmeMsg_t msg;

    msg.msgId = CME_MESSAGE_ID_P2P_NEG_CONFIRMATION;
    msg.roleId = aRoleId;
    msg.generalData = isGO;

    HOOK(HOOK_IN_CME);
    
    pushMsg2Queue(&msg);
}
//================================================================

/******************************************************************************
  Function          : CME_generalSemaphoreCreate

  Description       : Allocates and registers the semaphore protecting access
                      to the B/W list and Private IE.

  Input parameters  : None

  Output parameters : None

  Return value      : none.
******************************************************************************/
void CME_generalSemaphoreCreate(void)
{
    OsiSyncObj_t* pSemaphore;
    OsiReturnVal_e     status;

    HOOK(HOOK_IN_CME);

    pSemaphore = os_malloc(sizeof(OsiSyncObj_t));
    ASSERT_GENERAL(NULL != pSemaphore);

    status = osi_SyncObjCreate(pSemaphore);
    ASSERT_GENERAL(OSI_OK == status);

    gGeneralAccessSemaphore = pSemaphore;
}


/******************************************************************************
  Function          : CME_generalSemaphoreDestroy

  Description       : Free and un-registers the semaphore protecting access
                      to the B/W list and Private IE.

  Input parameters  : None

  Output parameters : None

  Return value      : none.
******************************************************************************/
void CME_generalSemaphoreDestroy(void)
{
    OsiSyncObj_t*      pSemaphore;
    OsiReturnVal_e     status;

    HOOK(HOOK_IN_CME);

#ifdef BWLIST_UNITEST
    TestingThreadStatus =1;
    while(TestingThreadStatus != 0)
    {
        GTRACE(GRP_CME, "Waiting for testing thread exit");
        osi_Sleep(20);
    }
#endif

    pSemaphore = gGeneralAccessSemaphore;
    gGeneralAccessSemaphore = NULL;

    status = osi_SyncObjDelete(pSemaphore);
    ASSERT_GENERAL(OSI_OK == status);

    os_free(pSemaphore);
}

/******************************************************************************
  Function          : CME_generalSemaphoreTake

  Description       : Takes the semaphore protecting access
                      to the B/W list and Private IE.

  Input parameters  : None

  Output parameters : None

  Return value      : 0 if Semaphore successfuly taken, -1 otherwise.
******************************************************************************/
int32_t CME_generalSemaphoreTake(void)
{
    HOOK(HOOK_IN_CME);

    OsiReturnVal_e     status;

    status = osi_SyncObjWait(gGeneralAccessSemaphore, OSI_WAIT_FOREVER);
    ASSERT_GENERAL(OSI_OK == status);

    return 0;
}

/******************************************************************************
  Function          : CME_generalSemaphoreRelease

  Description       : Frees the semaphore protecting access
                      to the B/W list and Private IE.

  Input parameters  : None

  Output parameters : None

  Return value      : none.
******************************************************************************/
void CME_generalSemaphoreRelease(void)
{
    HOOK(HOOK_IN_CME);

    OsiReturnVal_e     status;

    status = osi_SyncObjClear(gGeneralAccessSemaphore);
    ASSERT_GENERAL(OSI_OK == status);
}

int16 CME_WlanApRemovePeer(CMEWlanApRemovePeer_t *pCmdRemovePeer)
{
    cmeMsg_t msg;
    int16  status = OSI_OK;

    if (cme_is_ap_role_like_activated())
    {
        msg.msgId = CME_MESSAGE_ID_AP_REMOVE_PEER;
        IRQ_UtilCopyMacAddress (pCmdRemovePeer->MacAddress, msg.un.apRemovePeer.macAddr);
        msg.generalData = CME_GENERAL_DATA_AP_REMOVE_PEER_IS_USER_REQ;

        if (pushMsg2Queue(&msg) < 0)
        {
            status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__HOST_RESPONSE_STATUS_ERROR);
        }
        else
        {
            if(OSI_OK != osi_SyncObjWait(&gCmeCommandBlockingSyncObject, OSI_WAIT_FOREVER))
            {
                CME_PRINT_REPORT("\n\rError! Failed to wait to gCmeCommandBlockingSyncObject.\n\r");
            }
        }
    }
    else
    {
        status = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CME, WLAN_ERROR_TYPE__INVALID_ROLE);
    }

    return status;
}

#ifdef CME_MSG_QUEUE_DEBUG
static void debug_print_msg_type_subtype(cmeMsg_t* msg)
{
    if(msg->msgId == CME_MESSAGE_ID_RX_MNG_PACK)
    {
        uint16 fc, type, stype;
        RxIfDescriptor_t *desc = (RxIfDescriptor_t *) msg->un.txRxPacket.pDesc;
        struct ieee80211_mgmt *pMngPack;


        // Extract transmitted packet type and verify it was a management packet
        pMngPack = (struct ieee80211_mgmt *)(uint8_t*)RX_BUF_DATA(desc);

        fc = le_to_host16(pMngPack->frame_control);
        type = WLAN_FC_GET_TYPE(fc);
        stype = WLAN_FC_GET_STYPE(fc);

        GTRACE(GRP_CME,"CME: Rx frame type=%d, stype=%d", type, stype);
        CME_PRINT_REPORT_ERROR("\r\nCME: Rx frame type=%d, stype=%d", type, stype);
    }
}

static void cme_debug_print_cME_queue_content(cmeMsg_t *apMsg)
{
    (void)apMsg;
    //for debug purpose, this is left open, will be undef later on
    //the code shouldn't come into this place, we need to drop packet that are not relevant
    //before
    int i = 0;
    OsiReturnVal_e rc;
    cmeMsg_t msg;
    uint32_t numOfMsgs;


    numOfMsgs = osi_MsgQCount(&gCmeMessageQueue);

    for (i = 0; i < numOfMsgs; i++)
    {
        rc = osi_MsgQRead(&gCmeMessageQueue, &msg, OSI_NO_WAIT);
        if (rc == OSI_OK)
        {
            GTRACE(GRP_CME,"CME: msgInqueu=%d, msgID=%d", i, msg.msgId);
            CME_PRINT_REPORT_ERROR("\r\nCME: QueueId=%d, msgID=%d roleId:%d", i, msg.msgId,msg.roleId);
            if(msg.msgId == CME_MESSAGE_ID_RX_MNG_PACK)
            {
                debug_print_msg_type_subtype(&msg);
            }
            if(msg.msgId == CME_MESSAGE_ID_TX_DONE)
            {

                uint16 fc, type, stype;
                TxIfDescriptor_t *desc = (TxIfDescriptor_t *)msg.un.txRxPacket.pDesc;
                struct ieee80211_mgmt *pMngPack;
                tiwdrv_netif_id_e netIfId = TIWDRV_NETIF_ID_NONE;
                Bool32 retVal = FALSE;

                // Extract transmitted packet type and verify it was a management packet
                pMngPack = (struct ieee80211_mgmt *)(uint8_t*)RX_BUF_DATA(desc);

                fc = le_to_host16(pMngPack->frame_control);
                type = WLAN_FC_GET_TYPE(fc);
                stype = WLAN_FC_GET_STYPE(fc);

                //convert link desc->hlid to role Type
                netIfId = wlanLinks_GetNetIfId(desc->hlid);
                //for AP role -> drop Probe resp and actions
                GTRACE(GRP_CME,"CME: TX done frame netIfId=%d type=%d, stype=%d", netIfId, type, stype);
                CME_PRINT_REPORT_ERROR("\r\nCME: TX done frame netIfId=%d, type=%d, stype=%d", netIfId, type, stype);

            }
        }
    }//for
}
#endif /* CME_MSG_QUEUE_DEBUG */
