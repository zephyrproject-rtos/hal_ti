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
  FILENAME:       cme_device_flow.c

  DESCRIPTION:    Handle device  flow state machine for one of the following users:
                  1. roc and send action frames
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


static void CmeDeviceInit(Cme_Users_e __user);
static void CmeDeviceDeInit(Cme_Users_e __user);
void CmeDeviceROC (Cme_Users_e __user);
void CmeDeviceCROC (Cme_Users_e __user);
static void supplicantRunDevice();
static uint8_t CmeDeviceFlowSmValidateTransitionUserEvent(Cme_DEVICE_events_e event,Cme_Users_e user);
extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t *args, uint16_t argsLen);

extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t * args, uint16_t argsLen);
extern void ti_driver_cancel_remain_on_channel_timer_callback_handle();

Cme_DEVICE_states_e gCmeDeviceFlowState_ull  = CME_DEVICE_DISABLED_STATE;
Cme_Users_e  gCmeDeviceSmUser_ull     = CME_STA_NONE_USER;


#define CME_DEVICE_FLOW_SM_VALID_USER_TRANSITION ( (1<<CME_DEVICE_DISABLED_STATE) | (1<<CME_DEVICE_IDLE_STATE) | (1<<CME_DEVICE_ROC_STATE) )

typedef struct
{
    SmEventHandler* pSmEventHandler;
    uint8_t           ValidState;
} CmeDeviceSmEntry_t;

const CmeDeviceSmEntry_t gCmeDeviceFlowSM[CME_DEVICE_NUM_OF_EVENTS] =
{
    /*CME_DEVICE_INIT_EVENT*/               {CmeDeviceInit,                (1<<CME_DEVICE_DISABLED_STATE)},
    /*CME_DEVICE_DEINIT_EVENT*/             {CmeDeviceDeInit,              (1<<CME_DEVICE_IDLE_STATE)},
    /*CME_DEVICE_ROC*/                      {CmeDeviceROC,                 (1<<CME_DEVICE_IDLE_STATE)},
    /*CME_DEVICE_CROC*/                     {CmeDeviceCROC,                (1<<CME_DEVICE_ROC_STATE)|(1<<CME_DEVICE_IDLE_STATE)},
};



//
// CmeStationFlowIsSMIdle
//
// verify if DEVICE flow SM is idle and ready for new user request
//
int CmeDeviceFlowIsSMIdle()
{
    return (gCmeDeviceFlowState_ull == CME_DEVICE_IDLE_STATE ? 1: 0);
}

int CmeDeviceFlowSM(Cme_DEVICE_events_e event, Cme_Users_e user)
{
    int rc = 0;
    if (CmeDeviceFlowSmValidateTransitionUserEvent(event,user))
    {
        GTRACE(GRP_CME_STA_FLOW, "CME :CmeDeviceFlowSM: currentState=ENUM(Cme_DEVICE_states_e, %d), Event=ENUM(Cme_DEVICE_events_e, %d)",
                                   gCmeDeviceFlowState_ull, event);

        // call callback function
        if (NULL != gCmeDeviceFlowSM[event].pSmEventHandler)
        {
            gCmeDeviceFlowSM[event].pSmEventHandler(user);
        }

    }
    else
    {
        GTRACE(GRP_CME_STA_FLOW, "CME :CmeStationFlowSM: ERROR! UnExpected event currentState=ENUM(Cme_DEVICE_states_e, %d), Event=ENUM(Cme_DEVICE_events_e, %d)",
                                   gCmeDeviceFlowState_ull, event);

        CME_PRINT_REPORT_ERROR("\n\rCME :CmeStationFlowSM: ERROR! UnExpected event currentState=ENUM(Cme_DEVICE_states_e, %d), Event=ENUM(Cme_DEVICE_events_e, %d)\n\r",
                                   gCmeDeviceFlowState_ull, event);

        rc = -1;
    }

    return rc;
}


static uint8_t CmeDeviceFlowSmValidateTransitionUserEvent(Cme_DEVICE_events_e event,Cme_Users_e user)
{

    uint8_t validTransition=FALSE;
    if (event < CME_DEVICE_NUM_OF_EVENTS)
    {
        validTransition = ( (gCmeDeviceFlowSM[event].ValidState) & (1 << gCmeDeviceFlowState_ull) );
    }
    else
    {
        GTRACE(GRP_CME_STA_FLOW,"CME : CmeDeviceFlowSmValidateTransitionUserEvent:ERROR! state transition is not valid"
                    "event  ENUM(Cme_STA_events_e, %d) with state ENUM(Cme_DEVICE_states_e, %d)",
                    event,gCmeDeviceFlowState_ull);
        CME_PRINT_REPORT_ERROR("\n\rCME :CmeDeviceFlowSmValidateTransitionUserEvent: ERROR! state transition is not valid "
                    "event ENUM(Cme_STA_events_e, %d) with state ENUM(Cme_DEVICE_states_e, %d)\n",
                    event,gCmeDeviceFlowState_ull);

    }

    if (validTransition)
    {
        //
        //state is valid + SM user change requested - check if valid state for user change
        //
        validTransition = ( CME_DEVICE_FLOW_SM_VALID_USER_TRANSITION & (1 << gCmeDeviceFlowState_ull) );

        GTRACE(GRP_CME_STA_FLOW,"CME :CmeDeviceFlowSmValidateTransitionUserEvent: Valid state :%d , ENUM(Cme_STA_events_e, %d) current state ENUM(Cme_DEVICE_states_e, %d)",
                validTransition,event,gCmeDeviceFlowState_ull);
        CME_PRINT_REPORT_ERROR("\n\rCME :CmeDeviceFlowSmValidateTransitionUserEvent: Valid state :%d, ENUM(Cme_STA_events_e, %d) current state ENUM(Cme_DEVICE_states_e, %d)",
                validTransition,event,gCmeDeviceFlowState_ull);


    }

    return validTransition;
}



void CmeDeviceInit             (Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    supplicantRunDevice();
    CME_PRINT_REPORT("\n\rDevice SM: CmeDeviceInit\n\r");

    //update state to idle
    gCmeDeviceFlowState_ull = CME_DEVICE_IDLE_STATE;

}

void CmeDeviceDeInit(Cme_Users_e __user)
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    struct wpa_supplicant *wpa_s;
    RoleType_e roleType;

    CME_PRINT_REPORT("\n\rCME :Device SM: CmeDeviceDeInit, move to :CME_DEVICE_DISABLED_STATE\n\r");

    roleType = drv_getDeviceIface(gpSupplicantGlobals, &wpa_s);
    if (roleType == ROLE_TYPE_NONE)
    {
        CME_PRINT_REPORT("\n\rdevice role doesn't exist");
        return;
    }
    
    wpa_supplicant_remove_iface(gpSupplicantGlobals,
                                wpa_s,
                                1 /* enable print */);

    //update state to disableing
    gCmeDeviceFlowState_ull = CME_DEVICE_DISABLED_STATE;

}

void CmeDeviceROC (Cme_Users_e __user)
{

    CME_PRINT_REPORT("\n\rCME :Device SM: CmeDeviceROCStarted\n");
    set_extDPP(1);
    wlanDispatcherSendEvent(WLAN_EVENT_ROC_DONE, NULL, 0);

    gCmeDeviceFlowState_ull = CME_DEVICE_ROC_STATE;
    //wpa_drv_remain_on_channel is performed by CME
}


void CmeDeviceCROC (Cme_Users_e __user)
{
    int32_t ret;
    struct wpa_supplicant *wpa_s;
    uint32_t*   pArgs;

    CME_PRINT_REPORT("\n\rCME :Device SM: CmeDeviceCROC \n");

    wpa_s = drv_getP2pDeviceSupplicant();

    if(wpa_s == NULL )
    {
        GTRACE(GRP_CME,"CME :ERROR ! DEVICE role doesn't exists");
        CME_PRINT_REPORT_ERROR("\r\nCME :ERROR ! DEVICE role doesn't exists");
    }
    ti_driver_cancel_remain_on_channel_timer_callback_handle();
    set_extDPP(0);
    gCmeDeviceFlowState_ull = CME_DEVICE_IDLE_STATE;

    pArgs = os_zalloc(sizeof(uint32_t));
    *pArgs = 0;
    if(__user == CME_DEVICE_ROC_TIMEOUT)
    {
    	*pArgs = 1;
    }
    wlanDispatcherSendEvent(WLAN_EVENT_CROC_DONE, (void*)pArgs, 0);
    os_free(pArgs);
}


Cme_Users_e CmeDeviceFlow_GetCurrentUser()
{
    return gCmeDeviceSmUser_ull;
}


static void supplicantRunDevice()
{
    HOOK(HOOK_IN_CME_STATION_FLOW);

    struct wpa_params params;
    struct wpa_global *pGlobal;
    struct wpa_supplicant *wpa_s;
    struct wpa_interface iface;


    memset(&iface, 0, sizeof(struct wpa_interface));

    // Initialize the interface & set role type

    iface.ifname = NETIF_NAME(TIWLAN_DEV_NAME_P2PDEV);
    iface.confname = NETIF_CONF_NAME(TIWLAN_DEV_NAME_P2PDEV); //Configuration name (configuration is done in config_cc33xx.c)

    // Disable P2P for this interface.
    // In order for this configuration to take place WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE
    // must be set on driver capabilities flags, see driver_cc33.c, setDriverCapabilities.
    iface.p2p_mgmt = 0;
    CME_PRINT_REPORT("\r\nCME : supplicantRunDevice: cfgGetP2pDeviceEnable = %d", cfgGetP2pDeviceEnable());

    if (cfgGetP2pDeviceEnable())
    {
        iface.p2p_mgmt = 1;
    }


    // only the first role that is started initializes supplicant
    if (NULL == gpSupplicantGlobals)
    {
        // Init global variables (were originally initialized in declaration)
        wpa_mem_init();

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
        pGlobal = wpa_supplicant_init(&params);
        pGlobal->p2p_disabled = 0;
    }
    else
    {
        pGlobal = gpSupplicantGlobals;
    }

#ifndef TI_STA_ONLY_BUILD
    if (TRUE == cfgGetP2pDeviceEnable())
    {
        pGlobal->params.conf_p2p_dev = os_strdup(NETIF_CONF_NAME(TIWLAN_DEV_NAME_P2PDEV));
    }
#endif

    wpa_s = wpa_supplicant_add_iface(pGlobal, &iface, NULL);
    if (NULL == wpa_s)
    {
        return;
    }

    wpa_s->auto_reconnect_disabled = 1;

    if (cfgGetP2pDeviceEnable())
    {
        wpa_s->drv_flags |= WPA_DRIVER_FLAGS_P2P_DEDICATED_INTERFACE;
    }     

    if (NULL == gpSupplicantGlobals)
    {
        wpa_supplicant_run(pGlobal);

        // Store a pointer to the supplicant interface, to be used for every
        // activation of supplicant API.
        gpSupplicantGlobals = pGlobal;
    }

    GTRACE(GRP_CME,"CME :supplicantRunDevice: done");
    CME_ROLE_PRINT_REPORT("\n\rCME :supplicantRunDevice: done");

    HOOK(HOOK_IN_CME_STATION_FLOW);
}

