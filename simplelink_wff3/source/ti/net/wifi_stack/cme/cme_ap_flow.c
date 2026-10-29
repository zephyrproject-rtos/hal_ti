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

#ifndef TI_STA_ONLY_BUILD

#include <inc_common_fw/cc3xxx_public_types.h>
#include "osi_kernel.h"
#include "common.h"
#include "wpa_supplicant_i.h"
#include "config.h"
#include "ap/ap_config.h"
#include "ap/hostapd.h"
#include "cme_scan_api.h"
#include "cme_fw_api.h"
#include "cme_internal_api.h"
#include "cme_supplicant_api.h"
#include "cme_defs.h"
#include "cc3xxx_public_types.h"
//#include "errors.h"
#include "l2_cfg.h"
#include "ap.h"
#include "common/ieee802_11_defs.h"
#include "80211_utils.h"
#include "gtrace.h"
#include "wlan_if.h"
#include "p2p_supplicant.h"
#include "wpa_supplicant/config.h"
#include "p2p/p2p_i.h"
#include "drv_ti_internal.h"
#include "errors.h"

// ============================================================================
//      External Functions
// ============================================================================
/* WLAN event dispatcher to host */
extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t * args, uint16_t argsLen);

//
//AP Flow SM hanlders definition
//
void CmeApInit             (Cme_Users_e __user);
void CmeApDeactivateReq    (Cme_Users_e __user);
void CmeApStopRole         (Cme_Users_e __user);
extern int32_t CME_peerAgingSampleTime();
static void CME_peer_aging_timeout();


extern void drv_ti_ap_init(void);


typedef enum
{
    CME_AP_DISABLED_STATE,
    CME_AP_UP_STATE,
    CME_AP_DISCONNECTING_STATE,
    CME_AP_NUM_OF_STATES
} Cme_AP_states_e;

typedef struct
{
    SmEventHandler* pSmEventHandler;
    uint8_t           ValidState;
} CmeApSmEntry_t;


//
// CME AP Flow state machine core
// Function handler per event, according to the current valid states
//
const CmeApSmEntry_t gCmeApFlowSM[CME_AP_NUM_OF_STATES] =
{
    /* CME_AP_INIT_EVENT                   */  {CmeApInit,            (1<<CME_AP_DISABLED_STATE)},
    /* CME_AP_STOP_ROLE_EVENT              */  {CmeApStopRole,        (1<<CME_AP_DISCONNECTING_STATE) | (1<<CME_AP_UP_STATE)}
};


Cme_AP_states_e gCmeApFlowState_ull  = CME_AP_DISABLED_STATE;

// SSID structure for the AP role
// Handed to supplicant in wpa_supplicant_create_ap, must remain vaild as long
// as the AP interface is up as supplicant points to this memory.
struct wpa_ssid gCmeSsid;

// Store configured AP TX power for Country IE 
int8_t gCmeConfiguredApTxPower = WLAN_MAX_TX_POWER_DBM;

// counter of connected peers in case of AP role
uint8_t gCmeConnectedLinksCount; //MEM_REGION_GLX

extern signal_role_change_state_done_t g_signal_role_change_state_done;

//
// CmeApFlowSMValidateTransitionUserEvent:
//
// State Machine transition validator and user updater
//
// inputs: event and user
//
// validates:
//  1. event is valid for the current SM state
//  2. user transition in a valid SM state
//  in case of user transition, update the global user parameter with the new user parameter
//
// return:
//  - TRUE if all transitions are valid
//  - FALSE if any transition is invalid
//
static uint8_t CmeApFlowSmValidateTransitionUserEvent(Cme_AP_events_e event)
{
    HOOK(HOOK_IN_CME_AP_FLOW);

    uint8_t validTransition=FALSE;
    if (event < CME_AP_NUM_OF_EVENTS)
    {
        validTransition = ( (gCmeApFlowSM[event].ValidState) & (1 << gCmeApFlowState_ull) );
    }
    else
    {
        GTRACE(GRP_CME_AP_FLOW,"CmeApFlowSmValidateTransitionUserEvent: ERROR! state transition is not valid (event  ENUM(Cme_AP_events_e, %d) with state ENUM(Cme_AP_states_e, %d))",
               event,gCmeApFlowState_ull);
    }



    return validTransition;
}

//
// CmeApFlowSM
//
// AP Machine core - any SM event should come through here
//
// inputs:
//      SM event
//      user requesting this event (CME manager action)
//
// returns:
//  0  - if event is validated
//  -1 - if event is not valid
//
int CmeAPFlowSM(Cme_AP_events_e event)
{
    HOOK(HOOK_IN_CME_AP_FLOW);

    int rc = 0;
    if (CmeApFlowSmValidateTransitionUserEvent(event))
    {
        GTRACE(GRP_CME_AP_FLOW, "CmeApFlowSM: currentState=ENUM(Cme_AP_states_e, %d), Event=ENUM(Cme_AP_events_e, %d)",
                                   gCmeApFlowState_ull, event);

        // call callback function
        if (NULL != gCmeApFlowSM[event].pSmEventHandler)
        {
            gCmeApFlowSM[event].pSmEventHandler(CME_STA_NONE_USER);
        }
    }
    else
    {
        GTRACE(GRP_CME_AP_FLOW, "CmeApFlowSM: ERROR! UnExpected event currentState=ENUM(Cme_AP_states_e, %d), Event=ENUM(Cme_AP_events_e, %d)",
                                   gCmeApFlowState_ull, event);
        rc = -1;
    }

    return rc;
}



//
// CmeApFlowIsUp
//
// verify if AP flow SM is up and ready for new request
//
int CmeApFlowIsUp()
{
    HOOK(HOOK_IN_CME_AP_FLOW);

    return ((gCmeApFlowState_ull == CME_AP_UP_STATE) ? 1: 0);
}


//
// CmeApFlowIsDisconnecting
//
// verify if AP flow SM is during disconnection
//
int CmeApFlowIsDisconnecting()
{
    HOOK(HOOK_IN_CME_AP_FLOW);

    return ((gCmeApFlowState_ull == CME_AP_DISCONNECTING_STATE) ? 1: 0);
}

int CmeApAnyConnectedLinks()
{
    HOOK(HOOK_IN_CME_AP_FLOW);

    return gCmeConnectedLinksCount;
}

int8_t CmeGetConfiguredApTxPower(void)
{
    return gCmeConfiguredApTxPower;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  AP FLOW STATE MACHINE HANDLERS
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CmeApInit(Cme_Users_e __user)
{
    int32_t ret = 0;
#if 0 //RazB: need to implement
    CME_PrivateIeAndBwListCreate();
#endif
    /* Reject AP start if a P2P group is already active.
    * AP role shares driver globals and MAC slots with P2P GO and CL
    * and cannot coexist with either.
    */
    if (CmeGetP2pGroupRoleType() != NOT_IN_GROUP)
    {
        CME_PRINT_REPORT_ERROR("\n\rCME ERROR! CmeApInit rejected - P2P group is active (group role=%d)",
                                CmeGetP2pGroupRoleType());
        g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status = CME_SIGNAL_ROLE_CHNGE_STATUS_FAILED;

        return;
    }

    CME_generalSemaphoreCreate();

    ret = supplicantRunAP();
    if (ret < 0)
    {
        g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status = CME_SIGNAL_ROLE_CHNGE_STATUS_FAILED;
        CME_PRINT_REPORT("\n\rCME ERROR! CmeApInit failed");
    }
    else
    {
        // Update state to up
        gCmeApFlowState_ull = CME_AP_UP_STATE;

        // Clear connections bit mask
        gCmeConnectedLinksCount = 0;
    }
}

void CmeApStopRole(Cme_Users_e __user)
{
    GTRACE(GRP_CME,"CmeApStopRole: now deiniting AP");
    CmeApDeInit();
    //update state to disconnecting
    gCmeApFlowState_ull = CME_AP_DISABLED_STATE;
}

int32_t setApSecurityParams (WlanSecParams_t*  pWlanSecConfig, int saePwe, struct wpa_ssid *pCmeSsid)
{
    HOOK(HOOK_IN_CME_AP_FLOW);

    int32_t rc = 0;

    switch (pWlanSecConfig->Type)
    {
        case CME_SEC_TYPE_OPEN:
            pCmeSsid->key_mgmt = WPA_KEY_MGMT_NONE;
            pCmeSsid->auth_alg = WPA_AUTH_ALG_OPEN;
            pCmeSsid->pairwise_cipher = WPA_CIPHER_NONE;
            pCmeSsid->group_cipher = WPA_CIPHER_NONE;
            break;

        case CME_SEC_TYPE_WPA_WPA2:

            if (pWlanSecConfig->KeyLen == WPA_HEX_PASSPHRASE_LENGTH)
            {
                //PMK received
                // string contains Hex password, convert it to Hex format
                convertAsciiString2Hex((int8_t *)&pCmeSsid->psk[0], (int8_t *)&pWlanSecConfig->Key[0], pWlanSecConfig->KeyLen);
                pCmeSsid->psk_set = 1;
            }
            else if ((pWlanSecConfig->KeyLen < WPA_HEX_PASSPHRASE_LENGTH )  && (pWlanSecConfig->KeyLen >= WPA_HEX_MIN_PASSPHRASE_LENGTH ))
            {
                //Valid Passphrase received
                pCmeSsid->passphrase = os_zalloc (pWlanSecConfig->KeyLen + 1);
                os_memcpy(pCmeSsid->passphrase, pWlanSecConfig->Key, pWlanSecConfig->KeyLen);
            }
            else
            {
                rc = -1;
            }

            if (rc == 0)
            {
                pCmeSsid->key_mgmt = WPA_KEY_MGMT_PSK;
                pCmeSsid->auth_alg = WPA_AUTH_ALG_OPEN;
                pCmeSsid->pairwise_cipher = CME_AP_WPA_DEFAULT_CIPHER;
                pCmeSsid->group_cipher = CME_AP_WPA_DEFAULT_CIPHER;
                pCmeSsid->proto = DEFAULT_PROTO;
            }

            break;

        case CME_SEC_TYPE_WPA2_PLUS:

            if ((pWlanSecConfig->KeyLen < WPA_HEX_PASSPHRASE_LENGTH ) 
                && (pWlanSecConfig->KeyLen >= WPA_HEX_MIN_PASSPHRASE_LENGTH ))
            {
                //Valid Passphrase received
                pCmeSsid->passphrase = os_zalloc (pWlanSecConfig->KeyLen + 1);
                os_memcpy(pCmeSsid->passphrase, pWlanSecConfig->Key, pWlanSecConfig->KeyLen);
            }

            pCmeSsid->key_mgmt = WPA_KEY_MGMT_PSK;
            pCmeSsid->pairwise_cipher = CME_AP_WPA_DEFAULT_CIPHER;
            pCmeSsid->group_cipher = CME_AP_WPA_DEFAULT_CIPHER;
            pCmeSsid->ieee80211w = MGMT_FRAME_PROTECTION_OPTIONAL; 
            pCmeSsid->proto = DEFAULT_PROTO;
            pCmeSsid->auth_alg = WPA_AUTH_ALG_OPEN;
            break;  
      
        case CME_SEC_TYPE_WPA3:

            if ((pWlanSecConfig->KeyLen < WPA_HEX_PASSPHRASE_LENGTH ) 
                && (pWlanSecConfig->KeyLen >= WPA_HEX_MIN_PASSPHRASE_LENGTH ))
            {
                //Valid Passphrase received
                pCmeSsid->passphrase = os_zalloc (pWlanSecConfig->KeyLen + 1);
                os_memcpy(pCmeSsid->passphrase, pWlanSecConfig->Key, pWlanSecConfig->KeyLen);
            }
            pCmeSsid->key_mgmt = WPA_KEY_MGMT_SAE;
            //pCmeSsid->auth_alg = WPA_AUTH_ALG_SAE;
            pCmeSsid->auth_alg = WPA_AUTH_ALG_OPEN;
            pCmeSsid->pairwise_cipher = CME_AP_WPA_DEFAULT_CIPHER;
            pCmeSsid->group_cipher = CME_AP_WPA_DEFAULT_CIPHER;
            //pCmeSsid->sae_pwe = CME_AP_WPA_SAE_PWE_H2E_AND_HUNTING_AND_PECKING;
            pCmeSsid->sae_pwe = saePwe;
            pCmeSsid->ieee80211w = MGMT_FRAME_PROTECTION_REQUIRED;
            pCmeSsid->proto = WPA_PROTO_RSN;
            pCmeSsid->group_mgmt_cipher = WPA_CIPHER_AES_128_CMAC;
            break;
        case CME_SEC_TYPE_WPA2_WPA3:

            if (l2_cfg_isMixedModeSupported() == FALSE)
            {
                CME_PRINT_REPORT("\n\rCan't start AP role with WPA2/WPA3 mixed "
                                 "mode security since it's not supported");
                rc = -1;
                break;
            }

            if ((pWlanSecConfig->KeyLen < WPA_HEX_PASSPHRASE_LENGTH ) 
                && (pWlanSecConfig->KeyLen >= WPA_HEX_MIN_PASSPHRASE_LENGTH ))
            {
                //Valid Passphrase received
                pCmeSsid->passphrase = os_zalloc (pWlanSecConfig->KeyLen + 1);
                os_memcpy(pCmeSsid->passphrase, pWlanSecConfig->Key, pWlanSecConfig->KeyLen);
            }

            pCmeSsid->key_mgmt = WPA_KEY_MGMT_SAE | WPA_KEY_MGMT_PSK;
            pCmeSsid->auth_alg = WPA_AUTH_ALG_OPEN;
            pCmeSsid->pairwise_cipher = CME_AP_WPA_DEFAULT_CIPHER;
            pCmeSsid->group_cipher = CME_AP_WPA_DEFAULT_CIPHER;
            pCmeSsid->sae_pwe = CME_AP_WPA_SAE_PWE_H2E_AND_HUNTING_AND_PECKING;
            pCmeSsid->ieee80211w = MGMT_FRAME_PROTECTION_OPTIONAL;
            pCmeSsid->proto = WPA_PROTO_RSN;
            pCmeSsid->group_mgmt_cipher = WPA_CIPHER_AES_128_CMAC;

            break;
        default:
            HOOK(HOOK_IN_CME_AP_FLOW);
            rc = -1;
            break;
    }

    HOOK(HOOK_IN_CME_AP_FLOW);

    return rc;
}

int CmeSetApParams(void *apParams)
{
    RoleUpApCmd_t *pParams = (RoleUpApCmd_t *)apParams;
    int freq;
    int sae_pwe;

    const cfgAp_t *apCfg = cfgGetApCfg();

    os_memset((void *)&gCmeSsid, 0, sizeof(struct wpa_ssid));

    gCmeSsid.ssid_len = os_strlen((const char*)pParams->ssid);
    gCmeSsid.ssid = os_zalloc(gCmeSsid.ssid_len + 1);
    memcpy(gCmeSsid.ssid, pParams->ssid, gCmeSsid.ssid_len + 1);
    gCmeSsid.ssid[gCmeSsid.ssid_len] = 0;
    gCmeSsid.ignore_broadcast_ssid = pParams->hidden;
    
    if (pParams->p2p_aGO)
    {
        gCmeSsid.mode = WPAS_MODE_P2P_GO;
        gCmeSsid.p2p_group = 1;
        gCmeSsid.p2p_persistent_group = 0;
    }
	else
	{
		gCmeSsid.mode = WPAS_MODE_AP;
	}

    //Set channel number
    freq = channel_to_freq(pParams->channel);
    if (freq == -1)
    {
        //Bad channel - use default
        freq = channel_to_freq(AP_DEFAULT_CHANNEL_NUMBER);
        GTRACE(GRP_CME, "Using default channel %d", AP_DEFAULT_CHANNEL_NUMBER);
    }

    gCmeSsid.frequency = freq;
    gCmeConfiguredApTxPower = pParams->tx_pow;

    gCmeSsid.beacon_int = apCfg->beaconIntervalTU;
    gCmeSsid.dtim_period = apCfg->dtimInterval;
    /* Set AP station inactivity timeout */
    if (pParams->apMaxInactivity != 0)
    {
        gCmeSsid.ap_max_inactivity = pParams->apMaxInactivity;
    }
    else
    {
        gCmeSsid.ap_max_inactivity = 300;  /* Default: 300 seconds (5 minutes) */
    }
    //indicates ht is enabled for supplicant

    gCmeSsid.ht = cfgIs11nEnabled();

    // Set AP SAE related configurations
    if ((pParams->sae_pwe != 0) && (pParams->sae_pwe != 1) && (pParams->sae_pwe != 2))
    {
        sae_pwe = CME_AP_WPA_SAE_PWE_H2E_AND_HUNTING_AND_PECKING;
    }
    else
    {
        sae_pwe = pParams->sae_pwe;
    }

    // Set security Params
    if (setApSecurityParams(&pParams->secParams, sae_pwe, &gCmeSsid) < 0)
    {
        CME_PRINT_REPORT_ERROR("\n\rFailed setting AP security");
        os_free(gCmeSsid.ssid);
        os_memset((void *)&gCmeSsid, 0, sizeof(struct wpa_ssid));
        gCmeConfiguredApTxPower = WLAN_MAX_TX_POWER_DBM;

        return WlanError(WLAN_ERROR_SEVERITY__LOW,
                         WLAN_ERROR_MODULE__CME,
                         WLAN_ERROR_TYPE__INVALID_PARAM_SEC_TYPE);
    }

    if(cfgGetApMaxNumStationsFromConfIni() < pParams->sta_limit)
    {
        pParams->sta_limit = cfgGetApMaxNumStationsFromConfIni();
        CME_PRINT_REPORT_ERROR("\n\rWARNING! sta_limit is higher than the limit configure by the conf.ini , setting it to :%d",pParams->sta_limit);
    }
    
    //Set AP max number of stations
    cfgSetApMaxNumStations(pParams->sta_limit);
    CME_PRINT_REPORT("\n\r sta_limit is set to :%d max inactivity timeout %d (sec)",pParams->sta_limit, gCmeSsid.ap_max_inactivity);

    cfgSetWpsMode(pParams->wpsDisabled);
    if (pParams->wpsDisabled)
    {
        gCmeSsid.wps_disabled = 1;
    }
    else
    {
        gCmeSsid.wps_disabled = 0;
        cfgSetWpsParameters(&(pParams->wpsParams));
    }

    gCmeSsid.transition_disable = !!pParams->transitionDisable;

    CME_PRINT_REPORT("\n\r Transition_disable=%d sae_anticlogging_threshold=%d\n\r",
                        gCmeSsid.transition_disable, 
                        pParams->sae_anticlogging_threshold);

    cfgSetApSaeAntiCloggingThreshold(pParams->sae_anticlogging_threshold);

    HOOK(HOOK_IN_CME_AP_FLOW);

    return 0;
}

void freeApParams()
{
    // Now that AP is completely down, free SSID string memory and passphrase, if exists
    if (gCmeSsid.ssid != NULL)
    {
        os_free(gCmeSsid.ssid);
        gCmeSsid.ssid = NULL;
    }
    if (gCmeSsid.passphrase != NULL)
    {
        os_free(gCmeSsid.passphrase);
        gCmeSsid.passphrase = NULL;
    }

    CME_generalSemaphoreDestroy();
}

void supplicantDeinitAP(struct wpa_global *pGlobal, struct wpa_supplicant *wpa_s, uint8_t destroyGlobal)
{
    if (wpa_supplicant_remove_iface(pGlobal, wpa_s, 0) < 0)
    {
        CME_PRINT_REPORT_ERROR("\n\rAP interface, "
                                "wpa_supplicant_remove_iface failed");
    }
    else
    {
        CME_PRINT_REPORT("\n\rAP interface, "
                            "wpa_supplicant_remove_iface success");
    }

    if (destroyGlobal)
    {
        wpa_supplicant_deinit(pGlobal);
    }
    freeApParams();
}

int32_t supplicantRunAP()
{
    int32_t ret = 0;
    HOOK(HOOK_IN_CME_AP_FLOW);

#ifdef CONFIG_AP
    struct wpa_params params;
    struct wpa_global *pGlobal;
    struct wpa_interface  iface;
    struct wpa_supplicant *wpa_s;


    if (NULL == gCmeSsid.ssid)
    {
        ASSERT_GENERAL(0);
    }

        // other 802.11 parameters are set taken from conf file, in add interface API;
        // if file doesn't exist supplicant gives default values.
        // As supplicant constructs the beacon/probe response packets we should set
        // our defualts before supplicant configures the AP.


        // get AP configuration and set it for the supplicant
    GTRACE(GRP_CME, "AP cfg: Key management type: %d, Frequency %d beacon int. %d dtim %d ",
            gCmeSsid.key_mgmt, gCmeSsid.frequency, gCmeSsid.beacon_int, gCmeSsid.dtim_period);
    

    // only the first role that is started initializes supplicant
    if (NULL == gpSupplicantGlobals)
    {
        // Init global variables (were originally initialized in declaration)
        wpa_mem_init();

        // Init supplicant
        os_memset(&params, 0, sizeof(params));

#ifndef HOSTAP_AND_CME_ENABLE_DEBUG
        params.wpa_debug_level = MSG_INFO;
#else
        params.wpa_debug_level = WPA_DEBUG_LEVEL;
        params.wpa_debug_syslog = 1;
#endif
        params.wpa_debug_show_keys = 0;
        pGlobal = wpa_supplicant_init(&params);
        if (pGlobal == NULL)
        {
            CME_PRINT_REPORT_ERROR("\n\rwpa_supplicant_init() failed");
            freeApParams();
            return -1;
        }

        pGlobal->p2p = 0;
    }
    else
    {
        pGlobal = gpSupplicantGlobals;
    }

    pGlobal->p2p_disabled = gCmeSsid.mode == WPAS_MODE_AP;

    memset(&iface, 0, sizeof(struct wpa_interface));
    
    if (gCmeSsid.mode == WPAS_MODE_P2P_GO)
    {
        //we are here since it's an AP aGO
        //leaving this to support the old approach for different project
        GTRACE(GRP_CME, "AP: enable p2p_mgmt=1");
        iface.ifname = NETIF_NAME(TIWLAN_DEV_NAME_P2P_GO);
        iface.confname = NETIF_CONF_NAME(TIWLAN_DEV_NAME_P2P_GO);
        iface.p2p_mgmt = 1;
    }
    else
    {
        iface.ifname = NETIF_NAME(TIWLAN_DEV_NAME_SAP);
        iface.confname = NETIF_CONF_NAME(TIWLAN_DEV_NAME_SAP); //Configuration name (configuration is done in config_cc33xx.c)
        iface.p2p_mgmt = 0;
    }

    // TODO - supplicant must get AP configuration from a file or control interface
    wpa_s = wpa_supplicant_add_iface(pGlobal, &iface, NULL);
    if (NULL == wpa_s)
    {
        freeApParams();
        return -1;
    }

    // Set scan interval for normal scan to 1 sec (3 first scans before moving to sched scan).
    // For now; there is no field in wpa_config.
    wpa_supplicant_set_scan_interval(wpa_s, 1);

    drv_ti_ap_init();

    ret = wpa_supplicant_create_ap(wpa_s, &gCmeSsid);
    if (ret < 0)
    {
        CME_PRINT_REPORT_ERROR("\n\rwpa_supplicant_create_ap() failed");
        supplicantDeinitAP(pGlobal, wpa_s,
                               gpSupplicantGlobals == NULL ? 1 : 0);
        return ret;
    }

    if (NULL == gpSupplicantGlobals)
    {
        ret = wpa_supplicant_run(pGlobal);
        // In case wpa_supplicant_run() fails something is
        // wrong with the global. It's the first try to run
        // supplicant so we wish to destroy the global context
        if (ret < 0)
        {
            CME_PRINT_REPORT_ERROR("\n\rwpa_supplicant_run() failed");
            supplicantDeinitAP(pGlobal, wpa_s, 1);
            return ret;
        }

        // In case of success, store a pointer to the
        // supplicant interface, activation of supplicant API.
        gpSupplicantGlobals = pGlobal;
    }

    GTRACE(GRP_CME,"supplicantRunAP: done");
    CME_PRINT_REPORT("\n\rsupplicantRunAP: done");

    HOOK(HOOK_IN_CME_AP_FLOW);

#endif
    return 0;
}

// Temp, till CME SM supports AP
void CmeApDeInit()
{
    int32 ret;
    HOOK(HOOK_IN_CME_AP_FLOW);

    struct wpa_supplicant *pApInterface;

    GTRACE(GRP_CME,"Removing AP interface");
    CME_PRINT_REPORT("\n\r Removing AP interface");

    uint32_t roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_AP);
    pApInterface = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);

    if (pApInterface!=NULL)
    {
        ret = wpa_supplicant_remove_iface(gpSupplicantGlobals,
                                    pApInterface,
                                    1 /* enable print */);
        if(ret<0)
        {
            CME_PRINT_REPORT_ERROR("\n\r AP interface ,wpa_supplicant_remove_iface failed");

        }
        else
        {
            CME_PRINT_REPORT_ERROR("\n\r AP interface ,wpa_supplicant_remove_iface success");
        }
    }

    freeApParams();

    HOOK(HOOK_IN_CME_AP_FLOW);

#if 0 //RazB: need to implement
    CME_PrivateIeAndBwListDestroy();
#endif
}

void CmeApExtWpsFailureNotify(int8_t wpsFailCode)
{
    wlanDispatcherSendEvent(WLAN_EVENT_AP_EXT_WPS_SETTING_FAILED, (void*)(&wpsFailCode), sizeof(int8_t));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  AP PEER Management
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// CmeApPeerConnectedNotify
//
// Description:
//              Notification from supplicant that a peer (STA/P2P_CL) connected to this AP role
//
// input:
//
// output: None
//
void CmeApPeerConnectedNotify(uint8_t *connected_peer_addr, uint8_t AID, uint8_t isExtWPSInProgress)
{
    HOOK(HOOK_IN_CME_AP_FLOW);

    ++gCmeConnectedLinksCount;

    //send notification to host on role up
    WlanEventSTAAdded_t*  pArgs;

    pArgs = os_zalloc(sizeof(WlanEventSTAAdded_t));

        /* copy the mac address */
    os_memcpy(pArgs->Mac, connected_peer_addr, MAC_ADDR_LEN);

    GTRACE(GRP_CME, "AP: Sta MAC %x:%x:%x:%x:%x:%x is Connected. AID=%d",
                   pArgs->Mac[0],
                   pArgs->Mac[1],
                   pArgs->Mac[2],
                   pArgs->Mac[3],
                   pArgs->Mac[4],
                   pArgs->Mac[5],
                   AID);

    pArgs->isExtWPSInProgress = isExtWPSInProgress;

    wlanDispatcherSendEvent(WLAN_EVENT_ADD_PEER, (void*)pArgs, sizeof(WlanEventSTAAdded_t));

    os_free(pArgs);

    HOOK(HOOK_IN_CME_AP_FLOW);
}

//
// CmeApPeerDisConnectedNotify
//
// Description:
//              Notification from supplicant that a peer (STA/P2P_CL) disconnected from this AP role
//
// input:
//
// output: None
//
void CmeApPeerDisConnectedNotify(uint8 *disconnected_peer_addr)
{
    HOOK(HOOK_IN_CME_AP_FLOW);

    ASSERT_GENERAL(0 < gCmeConnectedLinksCount);
    --gCmeConnectedLinksCount;

    //send notification to host on role up
    WlanEventSTARemoved_t*  pArgs;

    pArgs = os_zalloc(sizeof(WlanEventSTARemoved_t));

        /* copy the mac address */
    os_memcpy(pArgs->Mac, disconnected_peer_addr, MAC_ADDR_LEN);

        GTRACE(GRP_CME, "AP: Sta MAC %x:%x:%x:%x:%x:%x is DisConnected.",
                   pArgs->Mac[0],
                   pArgs->Mac[1],
                   pArgs->Mac[2],
                   pArgs->Mac[3],
                   pArgs->Mac[4],
                   pArgs->Mac[5]);

        // the peer which is removal in progress has just
        // finished, so clear the entry
        cmeInvalidateLastPeerRemoved();

    wlanDispatcherSendEvent(WLAN_EVENT_REMOVE_PEER, (void*)pArgs, sizeof(WlanEventSTARemoved_t));

    os_free(pArgs);

    HOOK(HOOK_IN_CME_AP_FLOW);
}


///////////////////////////////////////////////////////////////////////////////////
//    P2P Group Management
///////////////////////////////////////////////////////////////////////////////////
//
// CmeP2pGroupStartedNotify
//
// Description:
//              Notification host that a p2p group formated and we P2P GO/P2P_CL role
//
// input:    if driver - supplicant priv if
//           group peer address
//           isGroupTypeGo - True - for GO, False - for Client 
//
// output: None
//
void CmeP2pGroupStartedNotify(struct wpa_supplicant *wpa_s, uint8_t *groupPeerAddr, Bool_e isGroupTypeGo)
{
    WlanEventFormationComplete_t*  pArgs;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    uint8_t band;

    pArgs = os_zalloc(sizeof(WlanEventFormationComplete_t));

    os_memcpy(pArgs->Bssid, groupPeerAddr, MAC_ADDR_LEN);
    os_memcpy(pArgs->SsidName, pDrv->ssid, pDrv->ssid_len);
    pArgs->SsidLen =  pDrv->ssid_len;

    if(freq_to_chan(pDrv->freq, &pArgs->Channel, &band) < 0)
    {
        ASSERT_GENERAL(0);
    }

    pArgs->P2pRoleGo = isGroupTypeGo;

    wlanDispatcherSendEvent(WLAN_EVENT_P2P_GROUP_STARTED, (void*)pArgs, sizeof(WlanEventFormationComplete_t));
                             
    os_free(pArgs);
}

//
// CmeP2pGroupRemovedNotify
//
// Description:
//             Notify Host that p2p group was removed
//
// input:      RoleType
//
// output: None
//
void CmeP2pGroupRemovedNotify(RoleType_e roleType)
{
    WlanEventGroupRemoved_t*  pArgs;

    pArgs = os_zalloc(sizeof(WlanEventGroupRemoved_t));

    switch(roleType)
    {
        case ROLE_P2P_GO:
            pArgs->RoleType = WLAN_ROLE_P2P_GO;
            break;
        case ROLE_DEVICE:
            pArgs->RoleType = WLAN_ROLE_DEVICE;
            break;
        default:
            pArgs->RoleType = WLAN_ROLE_P2P_CL;
            break;

    }

    wlanDispatcherSendEvent(WLAN_EVENT_P2P_GROUP_REMOVED, (void*)pArgs, sizeof(WlanEventGroupRemoved_t));
                             
    os_free(pArgs);

}
////////////////////////////////////////////////////////////////////////////////////
////   aging timer
/////////////////////////////////////////////////////////////////////////////////
void CME_start_peer_aging_timer(OsiTimer_t* osTimer, uint32_t timeout)
{
    int32_t ret;
    if( osTimer->osTimerHandler == NULL)
    {
        osi_TimerCreate(osTimer, "peerAgingTimer", CME_peer_aging_timeout, NULL);
    }
    ret = osi_TimerStart(osTimer, timeout  , FALSE);
    if(ret < 0)
    {
        CME_PRINT_REPORT_ERROR("\n\rCME: Aging timer start failed");
    }
    else
    {
        //CME_PRINT_REPORT("\n\rCME: Aging timer started !!!");
    }

}

void CME_peer_aging_timeout()
{
    //CME_PRINT_REPORT("\n\rCME: CME_peer_aging_timeout function !!");
    //push event to CME to verify aging
    CME_peerAgingSampleTime();
}

void CME_peer_aging_timer_stop(OsiTimer_t* osTimer)
{
    int32_t ret;
    if(osTimer->osTimerHandler != NULL)
    {
        ret = osi_TimerStop(osTimer);
        if(ret < 0)
        {
            CME_PRINT_REPORT_ERROR("\n\rCME: aging timer stop failed");
        }
        osi_TimerDelete(osTimer);
    }
    else
    {
        CME_PRINT_REPORT("\n\rCME: aging timer was not stated");
    }
    osTimer->osTimerHandler = NULL;

}

#endif
