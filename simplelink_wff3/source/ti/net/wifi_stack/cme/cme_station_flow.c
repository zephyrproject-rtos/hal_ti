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
  FILENAME:       cme_station_flow.c

  DESCRIPTION:    Handle Station flow state machine for one of the following users:
                  1. ad hoc connection
                  2. profile manager
                  3. fast connection
                  4. provisioning confirmation stage
  ----------------------------------------------------------------------------- */


#include "osi_kernel.h"



#include "common.h"
#include "wpa_supplicant_i.h"
#include "config.h"


#include "cme_scan_api.h"
#include "cme_fw_api.h"
#include "cme_internal_api.h"
#include "cme_supplicant_api.h"
#include "cme_defs.h"
#include "cme_internal_api.h"
#include "gtrace.h"
#include "l2_cfg.h"
#include "drv_ext_app.h"

extern bool open_at_cc35xx_debug(const char *text);

static void sta_debug(const char *text)
{
    (void)open_at_cc35xx_debug(text);
}

//
//Station Flow SM hanlders definition
//
void CmeStationInit             (Cme_Users_e __user);
void CmeStationDeInit           (Cme_Users_e __user);
void CmeStationSupplicantMng    (Cme_Users_e __user);
void CmeStationFastConnect      (Cme_Users_e __user);
void CmeStationConnected        (Cme_Users_e __user);
void CmeScanDone                (Cme_Users_e __user);
void CmeStationConfigured       (Cme_Users_e __user);
void CmeStationDisconnectReq    (Cme_Users_e __user);
void CmeStationPeerDisconnectReq(Cme_Users_e __user);
void CmeStationBssLossDiss      (Cme_Users_e __user);

void CmeStationDisconnectKick   (Cme_Users_e __user);

void CmeStaP2pClientInit        (Cme_Users_e __user);
void CmeStaP2pClientDeinit      (Cme_Users_e __user);

extern BOOLEAN isDhcpReleaseEnabled(int is_for_ap_role);
extern int ipConfigSendDhcpRelease(int is_for_ap_role);
extern int16_t CME_DhcpReleaseComplete();
extern void DhcpReleaseDestroyFlow();
extern int32_t CME_WlanDisconnect(BOOLEAN requestByHost);
extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t * args, uint16_t argsLen);

uint8_t cfgGetP2pOperChannel();
uint8_t cfgGetP2pOperRegClass();


void CmeStationDeauthReceived   (Cme_Users_e __user);


//supplicant methods
static int32_t supplicantRunSta();
void cmeStaSendDisConnectedEventToApp(int16_t reason_code);
extern signal_role_change_state_done_t g_signal_role_change_state_done;


typedef struct
{
    SmEventHandler* pSmEventHandler;
    uint8_t           ValidState;
} CmeStationSmEntry_t;


//
// CME Station Flow state machine core
// Function handler per event, according to the current valid states
//
const CmeStationSmEntry_t gCmeStationFlowSM[CME_STA_NUM_OF_EVENTS] =
{
    /* CME_STA_INIT_EVENT                   */  {CmeStationInit,                (1<<CME_STA_DISABLED_STATE)},
    /* CME_STA_DEINIT_EVENT                 */  {CmeStationDeInit,              (1<<CME_STA_IDLE_STATE)},
    /* CME_STA_NETWORK_SEARCH_EVENT         */  {CmeStationSupplicantMng,       (1<<CME_STA_IDLE_STATE)},
    /* CME_STA_FAST_CONNECT_REQ_EVENT       */  {CmeStationFastConnect,         (1<<CME_STA_IDLE_STATE)},
    /* CME_STA_WPA_COMPLETED_EVENT          */  {CmeStationConnected,           (1<<CME_STA_SUPPLICANT_MANAGED_STATE) | (1<<CME_STA_CONFIGURED_STATE)},
    /* CME_STA_SCAN_DONE                    */  {CmeScanDone,                   (1<<CME_STA_SUPPLICANT_MANAGED_STATE) | (1<<CME_STA_DISCONNECTING_STATE) | (1<<CME_STA_IDLE_STATE)},
    /* CME_STA_WLAN_ROLE_UP_EVENT           */  {CmeStationConfigured,          (1<<CME_STA_CONNECTED_STATE)},
    /* CME_STA_WLAN_DISCONNECT_REQ_EVENT    */  {CmeStationDisconnectReq,       (1<<CME_STA_DISCONNECTING_STATE) | (1<<CME_STA_DISCONNECT_PEND_DHCP_REL_STATE) | (1<<CME_STA_SUPPLICANT_MANAGED_STATE) |(1<<CME_STA_CONNECTED_STATE) |(1<<CME_STA_CONFIGURED_STATE) },
    /* CME_STA_WLAN_PEER_DISCONNECT_REQ     */  {CmeStationPeerDisconnectReq,   (1<<CME_STA_DISCONNECTING_STATE) | (1<<CME_STA_DISCONNECT_PEND_DHCP_REL_STATE) |(1<<CME_STA_CONNECTED_STATE) |(1<<CME_STA_CONFIGURED_STATE) |(1<<CME_STA_SUPPLICANT_MANAGED_STATE) },
    /* CME_STA_WLAN_BSS_LOSS_EVENT          */  {CmeStationBssLossDiss,         (1<<CME_STA_DISCONNECTING_STATE) | (1<<CME_STA_DISCONNECT_PEND_DHCP_REL_STATE) | (1<<CME_STA_SUPPLICANT_MANAGED_STATE) |(1<<CME_STA_CONNECTED_STATE) |(1<<CME_STA_CONFIGURED_STATE) },
    /* CME_STA_WLAN_DHCP_RELEASED_EVENT     */  {CmeStationDisconnectKick,      (1<<CME_STA_DISCONNECT_PEND_DHCP_REL_STATE)},
    /* CME_STA_WLAN_DISCONNECT_COMPLETE_EVENT*/ {CmeStationDeauthReceived,      (1<<CME_STA_DISCONNECTING_STATE) | (1<<CME_STA_SUPPLICANT_MANAGED_STATE) |(1<<CME_STA_CONNECTED_STATE) |(1<<CME_STA_CONFIGURED_STATE) | (1<<CME_STA_IDLE_STATE)},
    /* CME_STA_P2P_CLIENT_INIT_EVENT         */ {CmeStaP2pClientInit,           (1<<CME_STA_DISABLED_STATE) | (1<<CME_STA_IDLE_STATE)},
    /* CME_STA_P2P_CLIENT_DEINIT_EVENT       */ {CmeStaP2pClientDeinit,         (1<<CME_STA_IDLE_STATE) | (1<<CME_STA_SUPPLICANT_MANAGED_STATE) | (1<<CME_STA_CONNECTED_STATE) | (1<<CME_STA_CONFIGURED_STATE) | (1<<CME_STA_DISCONNECT_PEND_DHCP_REL_STATE) | (1<<CME_STA_DISCONNECTING_STATE)}
};


//
//valid states for SM user ownder change - DISABLED and IDLE
//any other state should be first terminated and then handed over to next user
//
#define CME_STATION_FLOW_SM_VALID_USER_TRANSITION ( (1<<CME_STA_DISABLED_STATE) | (1<<CME_STA_IDLE_STATE) )


Cme_STA_states_e gCmeStationFlowState_ull  = CME_STA_DISABLED_STATE;
Cme_Users_e  gCmeStationSmUser_ull     = CME_STA_NONE_USER;

//
// CmeStationFlow_GetCurrentUser
//      get current station flow SM user
//
Cme_Users_e CmeStationFlow_GetCurrentUser()
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    return gCmeStationSmUser_ull;
}

Cme_STA_states_e CmeStationFlow_GetCurrentState()
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    return gCmeStationFlowState_ull;
}
//
// CmeStationFlowSmValidateTransitionUserEvent:
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
static uint8_t CmeStationFlowSmValidateTransitionUserEvent(Cme_STA_events_e event,Cme_Users_e user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    uint8_t validTransition=FALSE;
    if (event < CME_STA_NUM_OF_EVENTS)
    {
        validTransition = ( (gCmeStationFlowSM[event].ValidState) & (1 << gCmeStationFlowState_ull) );
        CME_PRINT_REPORT("\n\rCME :CmeStationFlowSmValidateTransitionUserEvent: Valid state !! , New User owner request (current user ENUM(Cme_Users_e, %d) new user ENUM(Cme_Users_e, %d)), event:%d current state ENUM(Cme_STA_states_e, %d)\n\r",
                gCmeStationSmUser_ull,
                user,
                event,
                gCmeStationFlowState_ull);

        if(!validTransition)
        {
        	CME_PRINT_REPORT_ERROR("\n\rCME :Error first ! CmeStationFlowSmValidateTransitionUserEvent: Valid state:%d , New User owner request (current user ENUM(Cme_Users_e, %d) new user ENUM(Cme_Users_e, %d)), event:%d current state ENUM(Cme_STA_states_e, %d)\n\r",
                    validTransition,gCmeStationSmUser_ull,
                    user,
                    event,
                    gCmeStationFlowState_ull);

        }

    }
    else
    {
        GTRACE(GRP_CME_STA_FLOW,"CmeStationFlowSmValidateTransitionUserEvent: ERROR! state transition is not valid (event  ENUM(Cme_STA_events_e, %d) with state ENUM(Cme_STA_states_e, %d))\n\r",event,gCmeStationFlowState_ull);
    	CME_PRINT_REPORT_ERROR("\n\rCME :Error CmeStationFlowSmValidateTransitionUserEvent: ERROR! state transition is not valid (event  ENUM(Cme_STA_events_e, %d) with state ENUM(Cme_STA_states_e, %d))\n\r",event,gCmeStationFlowState_ull);

    }

    if ((validTransition) && (user != gCmeStationSmUser_ull))
    {
        //
        //state is valid + SM user change requested - check if valid state for user change
        //
        validTransition = ( CME_STATION_FLOW_SM_VALID_USER_TRANSITION & (1 << gCmeStationFlowState_ull) );

        GTRACE(GRP_CME_STA_FLOW,"CME :CmeStationFlowSmValidateTransitionUserEvent: Valid state:%d , New User owner request (current user ENUM(Cme_Users_e, %d) new user ENUM(Cme_Users_e, %d)), event:%d current state ENUM(Cme_STA_states_e, %d)\n\r",
                validTransition,gCmeStationSmUser_ull,
                user,
                event,
                gCmeStationFlowState_ull);
        /*CME_PRINT_REPORT("\n\rCME :CmeStationFlowSmValidateTransitionUserEvent: Valid state:%d , New User owner request (current user ENUM(Cme_Users_e, %d) new user ENUM(Cme_Users_e, %d)), event:%d current state ENUM(Cme_STA_states_e, %d)",
                validTransition,gCmeStationSmUser_ull,
                user,
                event,
                gCmeStationFlowState_ull);*/


        if (validTransition)
        {
            //valid state for user change
            //update new user
            gCmeStationSmUser_ull = user;

            GTRACE(GRP_CME_STA_FLOW,"CmeStationFlowSmValidateTransitionUserEvent: Successful user handover, new Station Flow SM user is ENUM(Cme_Users_e, %d)\n\r",
                            gCmeStationSmUser_ull        );

        }
        else//error
        {
        	CME_PRINT_REPORT_ERROR("\n\rCME :Error second! CmeStationFlowSmValidateTransitionUserEvent: Valid state:%d , New User owner request (current user ENUM(Cme_Users_e, %d) new user ENUM(Cme_Users_e, %d)), event:%d current state ENUM(Cme_STA_states_e, %d)\n\r",
                    validTransition,gCmeStationSmUser_ull,
                    user,
                    event,
                    gCmeStationFlowState_ull);

        }

    }

    HOOK(HOOK_IN_CME_STATION_FLOW);

    return validTransition;
}

//
// CmeStationFlowSM
//
// Station Machine core - any SM event should come through here
//
// inputs:
//      SM event
//      user requesting this event (CME manager action)
//
// returns:
//  0  - if event and user are validated
//  -1 - if event or user were not valid
//
int CmeStationFlowSM(Cme_STA_events_e event, Cme_Users_e user)
{
    int rc = 0;
    if (CmeStationFlowSmValidateTransitionUserEvent(event,user))
    {
        sta_debug("\r\nDBG_STA:FlowSM:valid enter\r\n");
        GTRACE(GRP_CME_STA_FLOW, "CmeStationFlowSM: currentState=ENUM(Cme_STA_states_e, %d), Event=ENUM(Cme_STA_events_e, %d), User: ENUM(Cme_Users_e, %d)",
                                   gCmeStationFlowState_ull, event, gCmeStationSmUser_ull);

        // call callback function
        if (NULL != gCmeStationFlowSM[event].pSmEventHandler)
        {
            sta_debug("\r\nDBG_STA:FlowSM:handler enter\r\n");
            gCmeStationFlowSM[event].pSmEventHandler(user);
            sta_debug("\r\nDBG_STA:FlowSM:handler done\r\n");
        }

    }
    else
    {
        GTRACE(GRP_CME_STA_FLOW, "CmeStationFlowSM: ERROR! UnExpected event currentState=ENUM(Cme_STA_states_e, %d), Event=ENUM(Cme_STA_events_e, %d), User: ENUM(Cme_Users_e, %d)",
                                   gCmeStationFlowState_ull, event, gCmeStationSmUser_ull);
        CME_PRINT_REPORT_ERROR("\n\rCME :CmeStationFlowSM: ERROR! UnExpected event currentState=ENUM(Cme_STA_states_e, %d), Event=ENUM(Cme_STA_events_e, %d), User: ENUM(Cme_Users_e, %d)",
                                   gCmeStationFlowState_ull, event, gCmeStationSmUser_ull);
        rc = -1;
    }

    return rc;
}

//
// CmeStationFlowIsSMIdle
//
// verify if STA flow SM is idle and ready for new user request
//
int CmeStationFlowIsSMIdle()
{
    return (gCmeStationFlowState_ull == CME_STA_IDLE_STATE ? 1: 0);
}


//
// CmeStationFlowIsSMIdle
//
// verify if STA flow SM is in connected state
//
int CmeStationFlowIsConnected()
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    if((gCmeStationFlowState_ull == CME_STA_CONNECTED_STATE) || (gCmeStationFlowState_ull == CME_STA_CONFIGURED_STATE))
    {
        GTRACE(GRP_CME,"CmeStationFlowIsConnected - connected, state = %d", gCmeStationFlowState_ull);
        return 1;
    }

    GTRACE(GRP_CME,"CmeStationFlowIsConnected - Not connected, state = %d", gCmeStationFlowState_ull);
    return 0;
}


//
// CmeStationFlowIsDisconnecting
//
// verify if STA flow SM is during disconnection
//
int CmeStationFlowIsDisconnecting()
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    return ((gCmeStationFlowState_ull == CME_STA_DISCONNECTING_STATE) ? 1: 0);
}

//
// CmeStationFlowHostStatusGet
//
// get station wlan status
//
int16_t CmeStationFlowHostStatusGet()
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    CME_WlanStatus_e state;
    switch (gCmeStationFlowState_ull)
    {
        case CME_STA_SUPPLICANT_MANAGED_STATE:
            state = WLAN_STATUS_SCANNING;
            break;
        case CME_STA_CONNECTED_STATE:
        case CME_STA_CONFIGURED_STATE:
            state = WLAN_STATUS_CONNECTED;
            break;
        case CME_STA_DISCONNECT_PEND_DHCP_REL_STATE:
        case CME_STA_DISCONNECTING_STATE:
            state = WLAN_STATUS_DISCONNECTING;
            break;
        case CME_STA_DISABLED_STATE:
        case CME_STA_IDLE_STATE:
        default:
            state = WLAN_STATUS_DISCONNECTED;
            break;
    }

    return (int16_t)state;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  STATION FLOW STATE MACHINE HANDLERS
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CmeStationInit             (Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    sta_debug("\r\nDBG_STA:CmeStationInit enter\r\n");
    if(supplicantRunSta()< 0)
    {
        sta_debug("\r\nDBG_STA:CmeStationInit supplicant fail\r\n");
        g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status= CME_SIGNAL_ROLE_CHNGE_STATUS_FAILED;
        CME_PRINT_REPORT("\n\rCME ERROR! CmeStationInit failed");
    }
    else
    {
        sta_debug("\r\nDBG_STA:CmeStationInit supplicant done\r\n");
        cmeMngInitStaDB();
        CME_PRINT_REPORT("\n\rCME Cme STA Init");
        //update state to idle
        gCmeStationFlowState_ull = CME_STA_IDLE_STATE;
    }
}

void CmeStaP2pClientInit(Cme_Users_e __user)
{
    //update state to idle
    GTRACE(GRP_CME,"STA interface gCmeStationFlowState_ull = CME_STA_IDLE_STATE");
    gCmeStationFlowState_ull = CME_STA_IDLE_STATE; // CmeStaP2pClientInit
}

void CmeStaP2pClientDeinit(Cme_Users_e __user)
{
    // Supplicant manages P2P client interface lifetime, not the role manager.
    // If STA role is still activated it keeps ownership of the SM at IDLE.
    // Only move to DISABLED when STA itself is not active.
    gCmeStationFlowState_ull = cme_is_sta_role_like_activated()
                               ? CME_STA_IDLE_STATE
                               : CME_STA_DISABLED_STATE;
}

void CmeStationDeInit(Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    struct wpa_supplicant *wpa_s;

    drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    CME_ReleaseScanResults(CALLER7);

    GTRACE(GRP_CME,"Removing STA interface");
    CME_PRINT_REPORT("\n\rRemoving STA interface ifname=%s", wpa_s->ifname);

    wpa_supplicant_remove_iface(gpSupplicantGlobals,
                                wpa_s,
                                1 /* enable print */);

    //update state to disableing
    gCmeStationFlowState_ull = CME_STA_DISABLED_STATE;

    extAppDeinit();

    cmeMngDeInitStaDB();
}


void CmeStationDisconnectReq(Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    int RetVal;
// TODO need to implement
    if ((gCmeStationFlowState_ull == CME_STA_DISCONNECTING_STATE) || (gCmeStationFlowState_ull == CME_STA_DISCONNECT_PEND_DHCP_REL_STATE))
    {
        CME_PRINT_REPORT("\n\rCmeStationDisconnectReq: already in disconnecting phase (state %d), wait for previous disconnect to complete");

        //already disconnecting
        GTRACE(GRP_CME,"CmeStationDisconnectReq: already in disconnecting phase (state %d), wait for previous disconnect to complete",gCmeStationFlowState_ull);
        //do nothing
        return;
    }
#if 0
    // send DHCP release if needed!

    if (isDhcpReleaseEnabled(NX_IFC_STA))
    {
        GTRACE(GRP_CME,"DHCP RELEASE: DHCP release config is on, send dhcp release and go to dhcp pending state");
        gCmeStationFlowState_ull = CME_STA_DISCONNECT_PEND_DHCP_REL_STATE;

        RetVal = ipConfigSendDhcpRelease(NX_IFC_STA);

        if (NX_SUCCESS != RetVal)
        {
            GTRACE(GRP_CME,"DHCP RELEASE: SendDhcpRelease Failed - cont the disconnect phase, no need to stop the dhcp release timer");

            DhcpReleaseDestroyFlow();
        }
        else
        {
            GTRACE(GRP_CME,"DHCP RELEASE: SendDhcpRelease Pass - wait for frame complete or timeout");
        }
    }
    else
#endif
    {
        //dhcp release is off - kick off wlan disconnect immediately
        CME_PRINT_REPORT("\n\rPerform CME station disconnect kick");
        CmeStationDisconnectKick(__user);
    }
}

void CmeStationPeerDisconnectReq(Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    gCmeStationFlowState_ull = CME_STA_DISCONNECTING_STATE;

    cmeReassociationParamsClear();
}

void CmeStationBssLossDiss(Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    if ((gCmeStationFlowState_ull == CME_STA_DISCONNECTING_STATE) || (gCmeStationFlowState_ull == CME_STA_DISCONNECT_PEND_DHCP_REL_STATE))
    {
        //already disconnecting
        GTRACE(GRP_CME,"CmeStationDisconnectReq: already in disconnecting phase (state %d), wait for previous disconnect to complete",gCmeStationFlowState_ull);
        //do nothing
        return;
    }

    CME_PRINT_REPORT("\n\rcmeWlanDisconnect(WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY)");
    GTRACE(GRP_CME,"CmeStationBssLossDiss -> cmeWlanDisconnect(WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY)");

    //disconnect current network + stop any running scan
    if (cmeWlanDisconnect(WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY) > 0)
    {
        //
        //deauth request sent
        //waiting for wpa state disconnected
        //
        gCmeStationFlowState_ull = CME_STA_DISCONNECTING_STATE;

        //now we wait for wpa disconnected state
    }
    else
    {
        //disconnect completed (wasnt > authenticating)
        CME_PRINT_REPORT("\n\rCME CmeStationBssLossDiss");

        //update state to idle
        gCmeStationFlowState_ull = CME_STA_IDLE_STATE;

        cmeStaSendDisConnectedEventToApp(WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY);

    }
}

void CmeStationDisconnectKick(Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    //CME_PRINT_REPORT("\n\CmeStationDisconnectKick,cmeWlanDisconnect(WLAN_REASON_DEAUTH_LEAVING)");

    gWPSkickDisconnect_ull = TRUE;

    //disconnect current network + stop any running scan
    if (cmeWlanDisconnect(WLAN_REASON_DEAUTH_LEAVING) > 0)
    {
        //
        //deauth request sent
        //waiting for wpa state disconnected
        //
        gCmeStationFlowState_ull = CME_STA_DISCONNECTING_STATE;

        //now we wait for wpa disconnected state
    }
    else
    {
        //disconnect completed (wasnt > authenticating)

        //update state to idle
        CME_PRINT_REPORT("\n\rCME CmeStationDisconnectKick");
        gCmeStationFlowState_ull = CME_STA_IDLE_STATE;

       cmeStaSendDisConnectedEventToApp(WLAN_REASON_DEAUTH_LEAVING);

    }

}

void CmeStationDeauthReceived(Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    uint16_t DeauthReason;

    //deauth recieved - wpa supplicant is ready for new connection requests

    gCmeStationFlowState_ull = CME_STA_IDLE_STATE;

    DeauthReason = (uint16_t)CME_GetLastDisconnectReason();

    GTRACE(GRP_CME,"CME: CmeStationDeauthReceived:  DeauthReason=%d (user=%d)", DeauthReason, __user);
    CME_PRINT_REPORT("\n\rCME: CmeStationDeauthReceived:  DeauthReason=%d", DeauthReason);

    //disconnect current network + stop any running scan
    if (cmeWlanDisconnect(DeauthReason) > 0)
    {
        //
        //deauth request sent
        //waiting for wpa state disconnected
        //
        gCmeStationFlowState_ull = CME_STA_DISCONNECTING_STATE;

        //now we wait for wpa disconnected state
    }
    else
    {
        //disconnect completed (wasnt > authenticating)

        //update state to idle
        gCmeStationFlowState_ull = CME_STA_IDLE_STATE;

        cmeStaSendDisConnectedEventToApp(DeauthReason);

    }

// TODO need to implement
#if 0

    /* Lior - send connect process timeout here if one is running in bg */
    if ((DeauthReason != WLAN_REASON_DEAUTH_LEAVING)  && (sl_host_timeout_is_process_running(HOST_API_TIMEOUT_ID_WLAN_CONNECT)) )
    {
        GTRACE(GRP_CME,"CME: CmeStationDeauthReceived!!!!! stopping wlan process timeout");

        /* force expiry in the incoming period */
        sl_host_timeout_force_process_timeout(HOST_API_TIMEOUT_ID_WLAN_CONNECT);
    }

#if 0
    /* stop also the process timeout for the disconnect if running.. */
    if (sl_host_timeout_is_process_running(HOST_API_TIMEOUT_ID_WLAN_DISCONNECT))
    {
        SlWlanAsyncResponse_t AsyncEventResp;
        AsyncEventResp.Status = SL_STATUS_OK;

        /* STA is not connected so stop the process timeout if running.. */
        sl_host_timeout_notify_process_completed(HOST_API_TIMEOUT_ID_WLAN_DISCONNECT,
                                                 (uint8_t*)&AsyncEventResp,
                                                 sizeof(SlWlanAsyncResponse_t));
    }
#endif
#endif
}


void CmeStationSupplicantMng      (Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    //
    //update STA flow SM triggered user
    //
    gCmeStationSmUser_ull = __user;

    //update state to scanning
    gCmeStationFlowState_ull = CME_STA_SUPPLICANT_MANAGED_STATE;


}
void CmeStationFastConnect      (Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    //
    //update STA flow SM triggered user
    //
    gCmeStationSmUser_ull = __user;

    //update state to scanning
    gCmeStationFlowState_ull = CME_STA_SUPPLICANT_MANAGED_STATE;


}

void CmeStationConnected        (Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    //update state to connected
    gCmeStationFlowState_ull = CME_STA_CONNECTED_STATE;

    //call wlanRoleUp method

}

void CmeScanDone                (Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    if(gCmeStationFlowState_ull != CME_STA_DISCONNECTING_STATE)
    {
        if(gCmeStationFlowState_ull == CME_STA_SUPPLICANT_MANAGED_STATE)
        {
            WlanEventConnect_t*  pArgs;

            CME_PRINT_REPORT_ERROR("\n\rCME CmeScanDone, connection failed, probably timeout\n\r");
            pArgs = os_zalloc(sizeof(WlanEventConnect_t));
            pArgs->Status = -1;

            wlanDispatcherSendEvent(WLAN_EVENT_CONNECT, (void*)pArgs, sizeof(WlanEventConnect_t));

            os_free(pArgs);
        }
        else
        {

            CME_PRINT_REPORT("\n\rCME CmeScanDone, scan stopped ,state :%d change to CME_STA_IDLE_STATE", gCmeStationFlowState_ull);
            gCmeStationFlowState_ull = CME_STA_IDLE_STATE;
        }

    }
    else
    {
        CME_PRINT_REPORT("\n\rCME: CmeScanDone, state :%d perform disconnect", gCmeStationFlowState_ull);
        gCmeStationFlowState_ull = CME_STA_IDLE_STATE;
        CME_WlanDisconnect(TRUE);
   }

}

void CmeStationConfigured       (Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    //update state to connected-configured
    gCmeStationFlowState_ull = CME_STA_CONFIGURED_STATE;
}

void CmeSetStaParams(void *staParams)
{
    RoleUpStaCmd_t *pParams = (RoleUpStaCmd_t *)staParams;

    // Set WPS parameters (WPS IE fields) if WPS is enabled
    cfgSetWpsMode(pParams->wpsDisabled);
    if (pParams->wpsDisabled == FALSE)
    {
        cfgSetWpsParameters(&(pParams->wpsParams));
    }

    if (pParams->p2pDeviceEnabled)
    {
        // enable
        cfgSetP2pDevice(FALSE);
        //set p2p params
        cfgSetP2pParameters(&(pParams->P2pParams));
    }
    else
    {
        // disable
        cfgSetP2pDevice(TRUE);
    }
}

// WPA supplicant methods

/* ----------------------------------------------------------------------------
 supplicantRunSta
    Initialize supplciant interface.
    It is assumed the cc33xx isn't activated unless some role needs to be active.
    Hence a role is enabled as result of wpa_supplicant_add_iface activation.

 Parameters:    none
 Return code:   none
---------------------------------------------------------------------------- */
static int32_t supplicantRunSta()
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    struct wpa_params params;
    struct wpa_global *pGlobal;
    struct wpa_supplicant *wpa_s;
    struct wpa_interface iface;

    sta_debug("\r\nDBG_STA:supplicantRunSta enter\r\n");

#ifdef CME_MEM_ESTIMATION
    GTRACE(GRP_CME, "before wpa_interface alloc");
    mem_PrintStat();
#endif

    memset(&iface, 0, sizeof(struct wpa_interface));

    // Initialize the interface & set role type

#ifdef CME_MEM_ESTIMATION
    GTRACE(GRP_CME, "after wpa_interface alloc");
    mem_PrintStat();
#endif
    
    iface.ifname = NETIF_NAME(TIWLAN_DEV_NAME_STA);
    iface.confname = NETIF_CONF_NAME(TIWLAN_DEV_NAME_STA); //Configuration name (configuration is done in config_cc33xx.c)

    // Disable P2P for this interface.
    // In order for this configuration to take place WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE
    // must be set on driver capabilities flags, see driver_cc33.c, setDriverCapabilities.
    iface.p2p_mgmt = 0;

    // only the first role that is started initializes supplicant
    if (NULL == gpSupplicantGlobals)
    {
        // Init global variables (were originally initialized in declaration)
        sta_debug("\r\nDBG_STA:wpa_mem_init enter\r\n");
        wpa_mem_init();
        sta_debug("\r\nDBG_STA:wpa_mem_init done\r\n");

        //
        // Init supplicant
        //
        os_memset(&params, 0, sizeof(params));

        // Set supplicant debug level
#ifndef HOSTAP_AND_CME_ENABLE_DEBUG
        params.wpa_debug_level = MSG_INFO;
#else
        params.wpa_debug_level = WPA_DEBUG_LEVEL;
        params.wpa_debug_syslog = 1;
#endif
		params.wpa_debug_show_keys = 0;
        sta_debug("\r\nDBG_STA:wpa_supplicant_init enter\r\n");
        pGlobal = wpa_supplicant_init(&params);
        sta_debug("\r\nDBG_STA:wpa_supplicant_init done\r\n");
#if 0 
    // TODO : no need any more use the cme periodioc timer
    CME_startSupplicantPeriodicTimer(); //Start Supplicant periodic timer (used for maintenance and cleanup)
#endif
#ifdef CME_MEM_ESTIMATION
        GTRACE(GRP_CME, "after wpa_supplicant_init");
        mem_PrintStat();
#endif

        sta_debug("\r\nDBG_STA:p2p_disabled set enter\r\n");
        pGlobal->p2p_disabled = 0;
        sta_debug("\r\nDBG_STA:p2p_disabled set done\r\n");
    }
    else
    {
        sta_debug("\r\nDBG_STA:reuse supplicant globals\r\n");
        pGlobal = gpSupplicantGlobals;
    }

    sta_debug("\r\nDBG_STA:wpa_supplicant_add_iface enter\r\n");
    wpa_s = wpa_supplicant_add_iface(pGlobal, &iface, NULL);
    sta_debug("\r\nDBG_STA:wpa_supplicant_add_iface done\r\n");
    if (NULL == wpa_s)
    {
      //TODO need implementation

        CME_PRINT_REPORT_ERROR("\n\rwpa_supplicant_add_iface failed %s",iface.ifname);
        return -1;
    }

    // Set scan interval for normal scan to 1 sec (3 first scans before moving to sched scan).
    // For now; there is no field in wpa_config.
    wpa_supplicant_set_scan_interval(wpa_s, 1);

    // Disable auto reconnection option. In case of disconnetion supplicant shall
    // not trigger scan. Instead, CME shall inspect current state & configuration
    // and behave accordingly.
    wpa_s->auto_reconnect_disabled = 1;

    if (NULL == gpSupplicantGlobals)
    {
        sta_debug("\r\nDBG_STA:wpa_supplicant_run enter\r\n");
        wpa_supplicant_run(pGlobal);
        sta_debug("\r\nDBG_STA:wpa_supplicant_run done\r\n");

#ifdef CME_MEM_ESTIMATION
        GTRACE(GRP_CME, "after wpa_supplicant_run");
        mem_PrintStat();
#endif

        // Store a pointer to the supplicant interface, to be used for every
        // activation of supplicant API.
        sta_debug("\r\nDBG_STA:store globals enter\r\n");
        gpSupplicantGlobals = pGlobal;
        sta_debug("\r\nDBG_STA:store globals done\r\n");
    }

    GTRACE(GRP_CME,"supplicantRunSta: done");
    CME_ROLE_PRINT_REPORT("\n\rsupplicantRunSta: done");

    HOOK(HOOK_IN_CME_STATION_FLOW);
    return 0;
}

// Debug only for cme tested
Bool_e cmeIsStaSMIdle()
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    return (CME_STA_IDLE_STATE == gCmeStationFlowState_ull);
}

Bool_e cmeIsStaSMSuppManaged()
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    return (CME_STA_SUPPLICANT_MANAGED_STATE == gCmeStationFlowState_ull);
}

Bool_e cmeIsStaConnected()
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    return (CME_STA_CONFIGURED_STATE == gCmeStationFlowState_ull);
}

void cmeStaSendDisConnectedEventToApp(int16_t reason_code)
{
    WlanEventDisconnect_t*  pArgs;

    pArgs = os_zalloc(sizeof(WlanEventDisconnect_t));
    pArgs->ReasonCode = reason_code; /* save last disconect reason */

    GTRACE(GRP_CME,"CME: Send disconnect event to app, reason=%d", reason_code);
    pArgs->IsStaIsDiscnctInitiator = 0;
    wlanDispatcherSendEvent(WLAN_EVENT_DISCONNECT, (void*)pArgs, sizeof(WlanEventDisconnect_t));

    os_free(pArgs);
}
