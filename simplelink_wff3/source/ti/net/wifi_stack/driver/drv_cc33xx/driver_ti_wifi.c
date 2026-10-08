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
#include "drv_ti_internal.h"

#include "ethernet.h"
#include "tw_driver.h"
#include "udata_api.h"
#include "udata_net_api.h"
#include "rx_defs.h"
//#include "rx.h"
#include "tx_data_queue_api.h"
#include "wlan_links.h"
#include "public_types.h"

#include "utils/eloop.h"
#include "utils/common.h"
#include "common/ieee802_11_defs.h"
#include "common/defs.h"

#include "drivers/driver.h"

#include "ap/hostapd.h"
#include "ap/ap_config.h"
#include "ap/ieee802_1x.h"
#include "ap/ieee802_11.h"
#include "ap/sta_info.h"
#include "ap/hw_features.h"
#include "ap/beacon.h"
#include "ap/tkip_countermeasures.h"
#include "../../wpa_supplicant/config.h"
#include "../../wpa_supplicant/wpa_supplicant_i.h"
#include "wps/wps_i.h"
#include "p2p/p2p_i.h"
#include "p2p/p2p.h"
#include "scan.h"
#include "scan_result_table.h"


#include "bss.h"
#include "cme_supplicant_api.h"
#include "cme_dispatcher_api.h"
#include "cme_internal_api.h"
#include "cme_fw_api.h"
#include "cme_defs.h"
#include "802_11defs.h"

#include "gtrace.h"

#include "mpdu.h"

#include "80211_utils.h"
#include "regulatory_domain_api.h"
#include "common.h"
#include "driver/drv_core.h"
#include "rsn.h"
#include "public_share.h"
#include "l2_cfg.h"
#include "lower_mac_if.h"
#include "drv_ti_internal.h"
#include "drv_ext_app.h"
#include "rx.h"
#include "wlan_if.h"
#include "errors.h"
#include "tx_ctrl.h"
#include "control_cmd_fw.h"
// ============================================================================
//      Modules private definitions
// ============================================================================
// Scan states
// The macros below are used for keeping one shot scan type & state on driver DB.
// Used for building stop one shot scan command since scan module expects to receive
// scan type in stop command.
#define SET_ONE_SHOT_OS_SCAN(pDrv)     (pDrv->activeOneShotScanBM |= 1)
#define SET_ONE_SHOT_APP_SCAN(pDrv)    (pDrv->activeOneShotScanBM |= 2)

#define CLEAR_ONE_SHOT_OS_SCAN(pDrv)   (pDrv->activeOneShotScanBM &= ~1)
#define CLEAR_ONE_SHOT_APP_SCAN(pDrv)  (pDrv->activeOneShotScanBM &= ~2)

#define ONE_SHOT_OS_SCAN_ACTIVE(pDrv)  (pDrv->activeOneShotScanBM & 1)
#define ONE_SHOT_APP_SCAN_ACTIVE(pDrv) (pDrv->activeOneShotScanBM & 2)
#define WPA_DRIVER_FLAGS_SANE_ERROR_CODES       0x00004000

#define DEVICE_CMD_OPS      (0)

#define SCHED_MAX_W_SIZE (0x3FFFFFFF) //microSec  63x16M ~ 1000sec ~ 16 min.-- this is the FW limit
#define SCHED_MAX_W_SIZE_HOST (900000) //15 mintes taking gap form FW:SCHED_MAX_W_SIZE

// for MBO:
// if a related packet is received while the action it requires cannot be started due to other ongoing operation,
// we reinsert it into the CME queue. To prevent endless retries, we drop the packet once this threshold is reached.
#define RX_PACKET_REINSERTION_THRESHOLD (8000)


#define EAPOLS_TX_TIMEOUT (200)


// ============================================================================
//      Modules globals
// ============================================================================

// Globals holding the pointer to the driver data for the specific interface.
// Needed only to l2_packet interface implementation since this module does not have any access to the supplicant
// internal data. It only gets interface name.

ti_driver_ifData_t *gpDriverIfDataSta  = NULL; //TIWLAN_DEV_NAME_STA
ti_driver_ifData_t *gpDriverIfDataAp   = NULL; //TIWLAN_DEV_NAME_SAP
ti_driver_ifData_t *gpDriverIfDataDev  = NULL; //TIWLAN_DEV_NAME_P2PDEV

off_channel_t g_offChannelDev = {0};
void* g_remain_on_channel_apPriv = NULL;

p2pGroupRoleType_e gP2pGroupRoleType = NOT_IN_GROUP; // used when p2p group is formed

p2pGroupRole_e gP2pGroupRole = P2P_GROUP_ROLE_NONE; // used when p2p negotiation completes and the future role is defined, but not yet connected to the group

const uint8_t gTIHwConfigChannelsBG[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
const uint8_t gTIHwConfigChannelsA[] = PERIODIC_SCAN_CHANNELS_ARRAY_A_BAND;

//Extended capabilities for STA role
const uint8_t gTIStaExtendedCapabilities[] = {
    [WLAN_EXT_CAPAB_BYTE(WLAN_EXT_CAPAB_EXT_CHAN_SWITCH)] = 
        BIT(WLAN_EXT_CAPAB_EXT_CHAN_SWITCH % 8),

    [WLAN_EXT_CAPAB_BYTE(WLAN_EXT_CAPAB_MULTIPLE_BSSID)] = 
        BIT(WLAN_EXT_CAPAB_MULTIPLE_BSSID % 8),
};

const uint8_t gTIStaExtendedCapabilitiesMask[sizeof gTIStaExtendedCapabilities] = {0};

//Extended capabilities for AP role
const uint8_t gTIApExtendedCapabilities[] = {0};

const uint8_t gTIApExtendedCapabilitiesMask[sizeof gTIApExtendedCapabilities] = {0};

extern TMacAddr g_fuse_mac_addr[];

extern uint32_t isextP2P();
extern uint32_t isextWPS();
extern uint32_t isextDPP();

extern int32_t set_cond_in_process_wlan_supplicant_operation();
extern int32_t set_cond_in_process_wlan_one_shot_scan();
extern int32_t set_cond_in_process_wlan_periodic_scan();
#ifndef TI_STA_ONLY_BUILD
extern int32_t set_cond_in_process_wlan_ap_roledown();
#endif
extern int32_t set_cond_in_process_wlan_sta_roledown();
extern void set_finish_wlan_one_shot_scan();
extern void set_finish_wlan_periodic_scan();
#ifndef TI_STA_ONLY_BUILD
extern void set_finish_wlan_ap_roledown();
#endif
extern void set_finish_wlan_sta_roledown();
extern void set_finish_wlan_supplicant_operation();
extern void CME_start_one_shot_scan_timer();
extern void CME_start_periodic_scan_timer();
extern void CME_peer_aging_timer_stop(OsiTimer_t *osTimer);

OsiLockObj_t    extAppLockObj;
extern txCtrl_t *gTxCtrlCB;

// for MBO: count the conscutive reinsartions of BTM request packets to the queue.
uint32_t gBtmCtr = 0;

extern OsiSyncObj_t gCmeEapolsStaSyncObject;

extern void trnspt_cmd_get_mac_addr(uint8 *macAddr, RoleType_e aRoleType);

// ============================================================================
//      Local Functions declarations
// ============================================================================
static int  setDriverCapabilities(ti_driver_ifData_t *apDrv);
void ti_driver_cancel_remain_on_channel_timer_callback();
extern int ti_send_mgmt_frame(void *apPriv,
                       const uint8_t *apData,
                       size_t aDataLen);
extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t *args, uint16_t argsLen);
extern int32_t CME_RemainOnChannelNotify(struct wpa_supplicant *wpa_s,
                                  int32_t aRoleId,
                                  int32_t freq,
                                  uint32_t duration);
extern int32_t CME_CancelRemainOnChannelNotify(struct wpa_supplicant *wpa_s,
		uint32_t is_croc_performed_due_to_timeout);

extern int32_t CME_sendActionFrameNotify( ti_driver_ifData_t     *pDrv,
                                          const uint8_t          *apDst,         // Destination address
                                          const uint8_t          *actionBuff,
                                          uint32_t                actionBuffLen);

extern int roleUp_Inter(WlanRole_e roleType, void *params, unsigned long int timeout);
extern int roleDown_inter(WlanRole_e roleType, unsigned long int timeout);
extern int32_t is_wlan_supplicant_operation_in_progress();


int CME_CancelRemainOn_from_CME_thread(uint8_t is_croc_performed_due_to_timeout );
int Wlan_RoleDown_from_CME_thread(WlanRole_e roleType, unsigned long int timeout);

// ============================================================================
//      Local services APIs
// ============================================================================
// ----------------------------------------------------------------------------
// parse_ie,
// create index buffer containing all IE addresses
// ----------------------------------------------------------------------------
int32_t parse_ie(uint32_t *pIE_addr_table, uint32_t *pIE_extension_addr_table, uint32_t *pIE_vendorSpecific_addr_table ,const u8 *ies, size_t len)
{
    const struct element *elem;

    for_each_element(elem, ies, len)
    {
        if(elem->id == EID_EXTENSION)
        {
            pIE_extension_addr_table[*((uint8 *) (elem->data))] = (uint32_t)elem;
        }
        else if(elem->id == VENDOR_SPECIFIC_IE_ID)
        {
            uint8 *vendor_specifi_oui_type = ((uint8 *) (elem->data));
            vendor_specifi_oui_type = vendor_specifi_oui_type + 3;
            pIE_vendorSpecific_addr_table[*((uint8 *) (vendor_specifi_oui_type))] = (uint32_t)elem;
        }
        else
        {
            pIE_addr_table[elem->id] = (uint32_t)elem;
        }

    }
    return 0;
}

// ----------------------------------------------------------------------------
ti_driver_ifData_t * getDriverForRoleId(uint32_t aRoleId, struct wpa_global *apGlobal)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    struct wpa_supplicant *wpa_s;
    ti_driver_ifData_t *pDrv;


    // Make sure ifaces is valid. It may be NULL in case of a race where interface
    // is down before a received packet is handled
    if (NULL == apGlobal->ifaces)
        return NULL;

    wpa_s = apGlobal->ifaces;
    if (NULL == wpa_s)
        return NULL;

    pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    if (NULL == pDrv)
        return NULL;

    if (pDrv->roleId == aRoleId)
        return pDrv;

    while (NULL != wpa_s->next)
    {
        wpa_s = wpa_s->next;
        pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

        if (NULL == pDrv)
            return NULL;

        if (pDrv->roleId == aRoleId)
            return pDrv;
    }

    ASSERT_GENERAL(0);//no interface found for the role
    return NULL;
}

// ============================================================================
//      Supplicant APIs
// ============================================================================
/* ----------------------------------------------------------------------------
 ti_driver_if_init
      This function initializes a new interface when a new role is activated.

 Parameters:    ctx - pointer to wpa_s
                ifname - interface name, indicates role type
                global_private - used to keep driver info on wpa_s, unused

 Return code:   0 - on success, -1 - failure in sanity tests
---------------------------------------------------------------------------- */
void *ti_driver_if_init(void *ctx, const char *ifname, void *global_priv)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    ti_driver_ifData_t *pDrv;

    GTRACE(GRP_DRIVER_CC33, "Init supplicant driver: ifname = %s", ifname);

    pDrv = os_zalloc(sizeof(ti_driver_ifData_t));
    if (0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_STA)))
    {
        gpDriverIfDataSta = pDrv; //saved just for l2_packet interface implementation
    }
    else if(0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_SAP)))
    {
        gpDriverIfDataAp = pDrv; //saved just for l2_packet interface implementation
    }
    else if(0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2PDEV)))
    {
        gpDriverIfDataDev = pDrv;
    }
    else if(0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2P_GO)))
    {
        gpDriverIfDataAp = pDrv; 
        gP2pGroupRole = P2P_GROUP_ROLE_GO;
    }
    else if(0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2P_CL)))
    {
        gpDriverIfDataSta = pDrv;
        gP2pGroupRole = P2P_GROUP_ROLE_CLIENT;
    }
    else if(0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2P))) //group
    {
        if (gP2pGroupRole == P2P_GROUP_ROLE_CLIENT)
        {
            gpDriverIfDataSta = pDrv; //saved just for l2_packet interface implementation
        }
        else if (gP2pGroupRole == P2P_GROUP_ROLE_GO)
        {
            gpDriverIfDataAp = pDrv; //saved just for l2_packet interface implementation
        }
        else
        {
            CME_PRINT_REPORT_ERROR("\n\r probably should not get here.... gP2pGroupRole=%d", gP2pGroupRole);
            ASSERT_GENERAL(0);
        }
    }
    else
    {
        /* ASSERT_GENERAL */
    }

    if (NULL == pDrv)
    {
        GTRACE(GRP_GENERAL_ERROR, "Init supplicant driver: Could not allocate memory for ti driver interface data");
        return NULL;
    }

    GTRACE(GRP_DRIVER_CC33, "Init supplicant driver: allocated %d bytes for ti driver interface data", sizeof(ti_driver_ifData_t));
    CME_PRINT_REPORT("\r\nInit supplicant driver:ifname:%s allocated %d bytes for ti driver interface data\n", ifname, sizeof(ti_driver_ifData_t));

    pDrv->ops = device_cmd_ops[DEVICE_CMD_OPS];

    // Keep received parameters
    pDrv->wpa_s = ctx;
    pDrv->ctx = ctx;
    os_memcpy(pDrv->iface, ifname, sizeof(pDrv->iface));

    // Extract role type from interface name
    pDrv->roleType = drv_getDrvRoleType(pDrv);

    // Mark role wasn't enabled ,not started yet
    pDrv->roleId = ROLE_ID_NONE;
    pDrv->roleEnabled = FALSE;
    pDrv->roleStarted = FALSE;

    // Set default capabilities on driver data base
    setDriverCapabilities(pDrv);

    if (ROLE_TYPE_NONE != pDrv->roleType)
    {
        GTRACE(GRP_DRIVER_CC33, "Assigned driver role ENUM(RoleType_e, %d) to the interface", pDrv->roleType);

        if (pDrv->ops->enable_role(pDrv, pDrv->roleType))
        {
            GTRACE(GRP_GENERAL_ERROR, "ERROR: Init supplicant driver: enable role failed");
            CME_PRINT_REPORT_ERROR("\r\nERROR ! couldn't enable role roleType : %d", pDrv->roleType);
            os_free(pDrv);
            pDrv = NULL;
            goto fail;
        }
    }

    if (pDrv &&  ROLE_IS_TYPE_STA(pDrv->roleType))
    {
        // Reset RSN DB
        rsn_init();
        scan_result_table_init();
        pDrv->apPowerLevel = WLAN_MAX_TX_POWER_DBM;

        pDrv->security_key_idx_mc1 = 0xFF;
        pDrv->security_key_idx_mc2 = 0xFF;
        pDrv->broadcastNextKeyArrEntry = 0;
    }

#ifndef TI_STA_ONLY_BUILD
    if (pDrv && ROLE_IS_TYPE_AP(pDrv->roleType))
    {
        pDrv->configuredApTxPower = CmeGetConfiguredApTxPower();
        GTRACE(GRP_DRIVER_CC33, "Stored configured AP TX power: %d dBm in driver structure", pDrv->configuredApTxPower);
    }
#endif

    if (pDrv && ROLE_IS_TYPE_P2P(pDrv->roleType))
    {
        GTRACE(GRP_DRIVER_CC33, "The P2P Role interface is initialized: %d", pDrv->roleType);
        CME_PRINT_REPORT("\r\nThe P2P Role interface is initialized: %d", pDrv->roleType);
        if (ROLE_IS_TYPE_P2P_CLIENT(pDrv->roleType))
        {
            CmeStationFlowSM(CME_STA_P2P_CLIENT_INIT_EVENT, CME_P2P_CLIENT_USER);
        }
    }
    //p2p device just initialized -  yet no role group
    if (pDrv && ROLE_IS_TYPE_DEVICE(pDrv->roleType))
    {
        gP2pGroupRole = P2P_GROUP_ROLE_NONE;
    }

    pDrv->fwMaxTxPower = WLAN_MAX_TX_POWER_DBM;

    if(g_offChannelDev.p_remain_channel_mutex == NULL)
    {
        if(osi_LockObjCreate(&(g_offChannelDev.p_remain_channel_mutex))< 0)
        {
            os_free(pDrv);
            pDrv = NULL;
            goto fail;
        }
    }
    if(g_offChannelDev.p_off_channel_mutex == NULL)
    {
        if(osi_LockObjCreate(&(g_offChannelDev.p_off_channel_mutex))<0)
        {
            os_free(pDrv);
            osi_LockObjDelete(&(g_offChannelDev.p_remain_channel_mutex));
            pDrv = NULL;
            goto fail;
        }
    }
fail:
    return pDrv;
} // ti_driver_if_init

/* ----------------------------------------------------------------------------
 ti_driver_deinit
      This function de-initializes an interface when a role is terminated.

 Parameters:    apPriv - pointer to private driver DB

 Return code:   0 - on success, -1 - failure in sanity tests
---------------------------------------------------------------------------- */
extern  OsiSyncObj_t            ScanResultTableSyncObj_ull;

void ti_driver_deinit(void *apPriv)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    if (NULL == pDrv)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: NULL driver pointer");
        ASSERT_GENERAL(0);
        return;
    }

    GTRACE(GRP_DRIVER_CC33, "Deinit driver role ID %d type ENUM(RoleType_e,%d)",
                             pDrv->roleId, pDrv->roleType);
    CME_PRINT_REPORT("\r\nDeinit driver role ID %d type ENUM(RoleType_e,%d)",
                             pDrv->roleId, pDrv->roleType);

    if(ROLE_IS_TYPE_P2P(pDrv->roleType))
    {
        gP2pGroupRole = P2P_GROUP_ROLE_NONE;
    }

    // Now that role is down, it is the time for memory cleanup
    if (FALSE != ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
    {
        GTRACE(GRP_DRIVER_CC33, "Driver role ID %d type ENUM(RoleType_e,%d)",
                                 pDrv->roleId, pDrv->roleType);
        CME_PRINT_REPORT("\r\nSTA Based Driver role ID %d type ENUM(RoleType_e,%d)",
                                 pDrv->roleId, pDrv->roleType);
        

        // Note: STA role is already stopped at this point. Once disabled scan
        // requets can't be served anymore.

        // Role disable blocks until role is disabled in all SW modules, including
        // WLAN services & data path.
        // When it returns, it is safe now to free driver memory.
        // Note that activating context may by blocked for few msecs until closure
        // confirmation is received from all modules.
        if( pDrv->ops->disable_role(pDrv) != 0 )
        {
            CME_PRINT_REPORT_ERROR("\r\nDisable STA role failed");
        }

        // supplicant is responsible to deactivate a p2p client role
        // we are about to free the driver data, so we need to
        // move STA SM Flow to deactivated state
        if (ROLE_IS_TYPE_P2P_CLIENT(pDrv->roleType))
        {
            CmeStationFlowSM(CME_STA_P2P_CLIENT_DEINIT_EVENT, CME_P2P_CLIENT_USER);
            gP2pGroupRoleType = NOT_IN_GROUP;
        }
        // Verify the dynamically allocated members were released; if not, this
        // is the last chance ...
        // This is needed for the use case of enabled but not started role where
        // allocated memory wasn't set yet to
        if(pDrv->vendorIEInfo.vendor_elements_length != 0)
        {
            os_free(pDrv->vendorIEInfo.vendor_elements);
            pDrv->vendorIEInfo.vendor_elements = NULL;
            pDrv->vendorIEInfo.vendor_elements_length = 0;
        }

        os_free(pDrv);
        gpDriverIfDataSta = NULL;
    }
    else if (FALSE != ROLE_IS_TYPE_AP_BASED(pDrv->roleType))// AP based role
    {
        GTRACE(GRP_DRIVER_CC33, "Driver role ID %d type ENUM(RoleType_e,%d)",
                                 pDrv->roleId, pDrv->roleType);
        CME_PRINT_REPORT("\n\rAP Based Driver role ID %d type ENUM(RoleType_e,%d)",
                                 pDrv->roleId, pDrv->roleType);

        // Removing AP interface flow:
        //      o CME initiates remove interface sequence upon host commnad
        //      o supplicant flushes all STAs by sending a multicast deauth packet
        //      o supplicant cancels any active scan
        //      o supplicant activates the driver_deinit API
        // Implementation limitations:
        //      o Stopping AP role is allowed only after transmission of deauth packet
        //      o Due to the above, sending deauth is blocking, till tx complete.


        //TODO: role should already be stoped. Should it be checked here, and if not perform stop?
        // Note: AP role is still active, have to stop it before disabling the role
        if( pDrv->ops->stop_role(pDrv) <0 )
        {
            CME_PRINT_REPORT_ERROR("\n\rStop AP role failed");
        }

        // Role disable blocks until role is disabled in all SW modules, including
        // WLAN services & data path.
        // When it returns, it is safe now to free driver memory.
        // Note that activating context may by blocked for few msecs until closure
        // confirmation is received from all modules.
        if(  pDrv->ops->disable_role(pDrv) != 0 )
        {
            CME_PRINT_REPORT_ERROR("\n\rDisable AP role failed");
        }

        //if aging timer and thread are up release them
#ifndef TI_STA_ONLY_BUILD
        CME_peer_aging_timer_stop(&pDrv->timerPeerAgingSample);
        pDrv->peerAgingTimeout = 0;
#endif

        os_free(pDrv);
        gpDriverIfDataAp = NULL;
    }
    else if(FALSE != ROLE_IS_TYPE_DEVICE(pDrv->roleType))
    {
        GTRACE(GRP_DRIVER_CC33, "Driver role ID %d type ENUM(RoleType_e,%d)",
                                 pDrv->roleId, pDrv->roleType);
        // Removing AP interface flow:
        //      o CME initiates remove interface sequence upon host commnad
        //      o supplicant flushes all STAs by sending a multicast deauth packet
        //      o supplicant cancels any active scan
        //      o supplicant activates the driver_deinit API
        // Implementation limitations:
        //      o Stopping AP role is allowed only after transmission of deauth packet
        //      o Due to the above, sending deauth is blocking, till tx complete.


        //TODO: role should already be stoped. Should it be checked here, and if not perform stop?
        // Note: AP role is still active, have to stop it before disabling the role
        pDrv->ops->stop_role(pDrv);

        // Role disable blocks until role is disabled in all SW modules, including
        // WLAN services & data path.
        // When it returns, it is safe now to free driver memory.
        // Note that activating context may by blocked for few msecs until closure
        // confirmation is received from all modules.
        pDrv->ops->disable_role(pDrv);

        os_free(pDrv);
        gpDriverIfDataDev = NULL;
    }

    // ============== Delete sync object ======================== //
    if ((NULL == gpDriverIfDataSta) && (NULL == gpDriverIfDataAp) && (NULL == gpDriverIfDataDev))
    {
        if((ScanResultTableSyncObj_ull != NULL) && (OSI_OK != osi_SyncObjDelete(&ScanResultTableSyncObj_ull)))
        {
            GTRACE(GRP_GENERAL_ERROR, "ti_driver_deinit: FAILED to delete sync object ");
            ASSERT_GENERAL(0);
        }
        ScanResultTableSyncObj_ull = NULL;
        if(g_offChannelDev.p_remain_channel_mutex != NULL)
        {
            if(OSI_OK != osi_LockObjDelete(&(g_offChannelDev.p_remain_channel_mutex)))
            {
                GTRACE(GRP_GENERAL_ERROR, "ERROR ! ti_driver_deinit: FAILED to delete sync object p_remain_channel_mutex ");
                ASSERT_GENERAL(0);
            }
            g_offChannelDev.p_remain_channel_mutex = NULL;
        }
        if(g_offChannelDev.p_off_channel_mutex != NULL)
        {
            if(OSI_OK != osi_LockObjDelete(&(g_offChannelDev.p_off_channel_mutex)))
            {
                GTRACE(GRP_GENERAL_ERROR, "ERROR ! ti_driver_deinit: FAILED to delete sync object p_off_channel_mutex ");
                ASSERT_GENERAL(0);
            }
            g_offChannelDev.p_off_channel_mutex = NULL;
        }

    }

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

} // ti_driver_deinit

/* ----------------------------------------------------------------------------
 ti_driver_off_channel_device_init
      This function initializes a new device .

 Parameters:    ifname - interface name, indicates role type

 Return code:   0 - on success, -1 - failure in sanity tests
---------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------
 ti_driver_get_capa
      This function returns driver capabilities to supplicant

 Parameters:    IN  apPriv - pointer to private driver DB
                OUT apCaba - pointer to driver capabilities

 Return code:   0 - on success, -1 - driver wasn't initialized yet
---------------------------------------------------------------------------- */
int ti_driver_get_capa(void *apPriv, struct wpa_driver_capa *apCapa)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    if (NULL == pDrv)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: NULL driver pointer");
        return -1;
    }

    os_memcpy(apCapa, &pDrv->capa, sizeof(*apCapa));
    return 0;
} // ti_driver_get_capa


/* ----------------------------------------------------------------------------
 ti_driver_get_ext_capa
      This function returns the extended driver capabilities to supplicant

 Parameters:    IN  apPriv - pointer to private driver DB
                IN  type - Iterface type 
                OUT ext_capab - pointer to driver ext capabilities are witten to
                OUT ext_capab_mask - pointer to driver ext capabilities mask (what bits must be clear from the IE)
                OUT ext_capab_len - pointer to the size of ext_capab and ext_capab_mask

 Return code:   0
---------------------------------------------------------------------------- */
int ti_driver_get_ext_capa(void *priv, enum wpa_driver_if_type type,
			     const u8 **ext_capab, const u8 **ext_capab_mask,
			     unsigned int *ext_capab_len)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)priv;
    uint8_t roleType;
    if(NULL == pDrv)
    {
        GTRACE(GRP_GENERAL_ERROR, "Error: NULL driver pointer");
        return -1;
    } 

    roleType = (uint8_t)pDrv->roleType;
    
    if (roleType == ROLE_AP)
    {
        *ext_capab = gTIApExtendedCapabilities;
        *ext_capab_mask = gTIApExtendedCapabilitiesMask;
        *ext_capab_len = sizeof gTIApExtendedCapabilities;
    }

    if (roleType == ROLE_STA)
    {
        *ext_capab = gTIStaExtendedCapabilities;
        *ext_capab_mask = gTIStaExtendedCapabilitiesMask;
        *ext_capab_len = sizeof gTIStaExtendedCapabilities;
    }

    return 0;
}// ti_driver_get_ext_capa

/* ----------------------------------------------------------------------------
 ti_driver_set_key
      This API serves for STA & AP based roles.
      It configures security keys and mode.

 Parameters:    IN ifname - pointer to interface name, unused
                IN apPriv - Pointer to driver object
                IN alg - security key type (none, WEP, TKIP, PMK ...)
                IN addr - peer address or NULL
                IN key_idx
                IN set_tx
                IN seq
                IN seq_len
                IN key
                IN key_len
 Return code:   0 - parameters OK, -1 - error indication

 TODO - complete functionality
---------------------------------------------------------------------------- */
//int ti_driver_set_key(const char *ifname, void *apPriv, enum wpa_alg alg,
//                               const u8 *addr, int key_idx, int set_tx,
//                               const u8 *seq, size_t seq_len,
//                               const u8 *key, size_t key_len)
int ti_driver_set_key(void *apPriv, struct wpa_driver_set_key_params *params)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    securityKeys_t secKey;
    char macStr[MAC_STR_LEN];

    if ( (ROLE_TYPE_NONE == pDrv->roleType) || ROLE_IS_TYPE_DEVICE(pDrv->roleType) )
        return 0;

/* **************************
 * Important:
 *      The code below this point should be optimized and short as possible till we perform the actual set key in FW.
 *      This is to minimize the time between the transmission of the last eapol of the 4 way handshake, in STA role,
 *      (performed by the supplicant before the call to ti_driver_set_key()); and the actual set key,
 *      in order to prevent a race condition where the AP sends us an encripted packet, before we set the encription key.
 * **************************/
    //No debug messages here, for speed optimization (set key ASAP after last eapol was send).
    //Enable Only for debug!!
    GTRACE(GRP_DRIVER_CC33_DEBUG, "Set keys: alg %d, key index %d, seq len %d, key len %d, set TX %d",
           params->alg, params->key_idx, params->seq_len, params->key_len, params->set_tx);
    //CME_CC3XX_PORT_PRINT("\n\rSet/Remove keys: alg %d, key index %d, seq len %d, key len %d, set TX %d",
    //       params->alg, params->key_idx, params->seq_len, params->key_len, params->set_tx);

    os_memset(&secKey, 0, sizeof(secKey));

    if (NULL != params->addr)
    {
        IRQ_UtilCopyMacAddress(params->addr, secKey.macAddress);
    }
    // else, macAddress is zeroed by the memset above

    if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
        uint8_t lid = INVALID_LINK;

        if (MAC_BROADCAST(secKey.macAddress)) //AP Broadcast
        {
            lid = wlanLinks_GetBroadcastLink();
            secKey.lidKeyType = KEY_TYPE_BROADCAST;
        }
        else //Peer linkId
        {

            lid = wlanLinks_LinkMacFind(TIWDRV_NETIF_ID_SAP, (uint8_t *)secKey.macAddress);
            secKey.lidKeyType = KEY_TYPE_UNICAST;
        }


        if (lid == INVALID_LINK)
        {
            //if this is not for remove key
            if ((!MAC_EQUAL (secKey.macAddress, "\x0\x0\x0\x0\x0\x0")) &&
                (params->alg != WPA_ALG_NONE) &&
                (params->key_len > 0))
            {
                //if it is for remove key and linkId doesn't exists it is not error
                GET_MAC_STR(secKey.macAddress, macStr);
                TX_PRINT_ERROR("\n\rti_driver_set_key : link id doesn't exist yet for mac :%s", macStr);

                ASSERT_GENERAL (FALSE);
                return -1;

            }
            else//key is to be removed and linkId not exist
            {
                return 0;

            }
        }

        secKey.lid = lid;
        secKey.keyType  = params->alg;
        secKey.keyIndex = params->key_idx;
        secKey.encLen = params->key_len;

        if ((params->alg == WPA_ALG_NONE) || (0 == params->key_len) )
        {
            rsn_removeKey(&secKey, params->ifname);
        }
        else
        {
            #if 0

            if (WPA_ALG_IGTK == params->alg)
            {
                // TODO- same as in driver_wilink
                return -1;
            }


            if ((WPA_ALG_WEP == params->alg) && (params->set_tx))
            {
                /* WEP not supported */
                return -1;
            }

            if (WPA_ALG_TKIP == params->alg)
            {
                /* TKIP not supported */
                return -1;
            }
            else
            #endif
            {
                os_memcpy(secKey.encKey, params->key, params->key_len);
            }

            rsn_addKey(&secKey, params->ifname);
        }
    }
    else /* Role station or P2P client*/
    {
        uint8_t lid = udataNet_GetTxMgmtLink(TIWDRV_NETIF_ID_STA, pDrv->currBssid);
        if (lid == INVALID_LINK)
        {
            //TODO: temp - address 0 with default key (set both broadcast and unicast?)
            //TODO: temp - remove when scenario is understood.
            if ((!MAC_EQUAL (secKey.macAddress, "\x0\x0\x0\x0\x0\x0")) &&
                (params->alg != WPA_ALG_NONE) &&
                (params->key_len > 0))
            {
                TX_PRINT_ERROR("\n\rti_driver_set_key : STA invalid interface alg:%d key_len:%d", params->alg, params->key_len);
                ASSERT_GENERAL (FALSE);
            }
            TX_PRINT_ERROR("\n\rti_driver_set_key : STA invalid interface");
            return -1;

        }

        if (MAC_BROADCAST(secKey.macAddress))
        {
            secKey.lidKeyType = KEY_TYPE_BROADCAST;
            TX_DATA_SEND_PRINT("\n\r+++KEY_TYPE_BROADCAST: lid = %d", lid);
        }
        else
        {
            secKey.lidKeyType = KEY_TYPE_UNICAST;
            TX_DATA_SEND_PRINT("\n\r+++KEY_TYPE_UNICAST: lid = %d", lid);
        }
        // --------------------------------------------------------------------
        // The code below was imported from wilink_driver
        secKey.keyType  = params->alg;
        secKey.encLen = params->key_len;
        os_memcpy(secKey.encKey, params->key, params->key_len);

        if (params->seq && params->seq_len && (params->seq_len <= KEY_RSC_LEN))
        {
            os_memcpy(secKey.keyRsc, params->seq, params->seq_len);
        }

        if (WPA_ALG_TKIP == params->alg)
        {
            os_memcpy(secKey.micRxKey, params->key + 24, TKIP_MIC_LEN);
            os_memcpy(secKey.micTxKey, params->key + 16, TKIP_MIC_LEN);
        }
        secKey.keyIndex = params->key_idx;
        secKey.lid = lid;


        // --------------------------------------------------------------------
        // The code below was imported from rsn.c, rsn_setParam, TI_PARAM_ADD_KEY

        // Remove the key when the length is 0, or the type is not set
        if ( (WPA_ALG_NONE == params->alg) || (0 == params->key_len) )
        {
            TX_DATA_SEND_PRINT("\n\rrsn_removeKey");
            rsn_removeKey(&secKey, params->ifname);
        }
        // Otherwise set the key
        else
        {
            TX_DATA_SEND_PRINT("\n\rrsn_addKey");
            rsn_addKey(&secKey, params->ifname);
        }
        // The code above was imported from rsn.c, rsn_setParam, TI_PARAM_ADD_KEY
        // --------------------------------------------------------------------

    }

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    return 0;
} // ti_driver_set_key

static int8_t countSupportedChannels(uint8_t band, uint8_t *pChanList,
                                     uint8_t chanListLen, uint8_t *numSupported,
                                     uint8_t roleType)
{
    uint8_t i = 0;
    channelCapability_t channelCapability = {0};
    int32_t ret = 0;

    for (i = 0; i < chanListLen; i++)
    {
        ret = regulatoryDomain_GetCapability(band, pChanList[i],
                                             &channelCapability);
        if (ret < 0)
        {
            GTRACE(MSG_ERROR, "ERROR: failed getting channel capability");
            CME_PRINT_REPORT_ERROR("\n\rFailed getting channel %d capability, "
                                   "band %d\n\r",pChanList[i], band);
            return ret;
        }

        if (ROLE_IS_TYPE_AP(roleType) ||
            ROLE_IS_TYPE_P2P_GO(roleType))
        {
            /* Not DFS - DFS isn't supported for AP role */
            if (((channelCapability.uFlags & TIW_REG_DOMAIN_DFS) == 0) &&
                ((channelCapability.channelValidityActive != 0) ||
                 (channelCapability.channelValidityPassive != 0)))
            {
                *numSupported += 1;
            }
        }
        else
        {
            /* For other roles DFS channels are supported */
            if ((channelCapability.channelValidityActive != 0) ||
                (channelCapability.channelValidityPassive != 0))
            {
                *numSupported += 1;
            }
        }
    }

    return 0;
}

// ----------------------------------------------------------------------------
static int32_t buildApChannelsCapability(RoleType_e roleType,
                                         struct hostapd_hw_modes *hwMode,
                                         uint8_t band)
{
    uint8_t *pChanList = NULL;
    uint32_t freqBase = 0;
    uint8_t chanListLen = 0, j = 0;
    int8_t  maxTxPower = 0;
    uint8_t numSupported = 0, i = 0;
    channelCapability_t channelCapability = {0};
    int32_t ret = 0;

    if (band == RADIO_BAND_2_4GHZ)
    {
        pChanList = (uint8_t *)&gTIHwConfigChannelsBG;
        chanListLen = sizeof(gTIHwConfigChannelsBG);
        freqBase = BASE_FREQ_2_4;
    }
    else if (band == RADIO_BAND_5GHZ)
    {
        pChanList = (uint8_t *)&gTIHwConfigChannelsA;
        chanListLen = sizeof(gTIHwConfigChannelsA);
        freqBase = BASE_FREQ_5_0;
    }
    else
    {
        return -1;
    }

    /* Count only non-DFS channels for AP. We don't support CAC and 
    * hence can't operate AP mode in non-DFS channels.
    * First we count and then we know how much channels to allocate
    */
    ret = countSupportedChannels(band, pChanList, chanListLen,
                                 &numSupported, roleType);
    if (ret < 0)
    {
        return ret;
    }

    if (numSupported == 0)
    {
        hwMode->num_channels = 0;
        CME_PRINT_REPORT_ERROR("\n\rWARNING: failed to build channels list - 0 channels");
        return -1;
    }
    hwMode->num_channels = numSupported;

    hwMode->channels = os_zalloc(sizeof(struct hostapd_channel_data) * (hwMode->num_channels));
    if (NULL == hwMode->channels)
    {
        CME_PRINT_REPORT_ERROR("\n\rERROR: failed to allocate memory for channels info");
        return -1;
    }

    /* After counting the channels in order to allocate tight memory
     * size, fill out channels in input buffer.
     */
    for (i = 0; i < chanListLen; i++)
    {
        ret = regulatoryDomain_GetCapability(band, pChanList[i],
                                             &channelCapability);
        if (ret < 0)
        {
            return ret;
        }

        if (ROLE_IS_TYPE_AP(roleType) ||
            ROLE_IS_TYPE_P2P_GO(roleType))
        {
            /* DFS channel or non-supported channel, skip it */
            if (((channelCapability.uFlags & TIW_REG_DOMAIN_DFS) != 0) ||
                ((channelCapability.channelValidityActive == 0) &&
                 (channelCapability.channelValidityPassive == 0)))
            {
                continue;
            }
        }
        else
        {
            /* Channel not supported, skip it */
            if ((channelCapability.channelValidityActive == 0) &&
                (channelCapability.channelValidityPassive == 0))
            {
                continue;
            }
        }

        ASSERT_GENERAL(j < hwMode->num_channels);

        hwMode->channels[j].chan = pChanList[i];
        hwMode->channels[j].freq = (hwMode->channels[j].chan * 5) + freqBase;

        ret = regulatoryDomain_getChMaxPower(hwMode->channels[j].chan, &maxTxPower);
        if (ret)
        {
            if (maxTxPower < 0)
            {
                GTRACE(GRP_GENERAL_ERROR, "channel %d: negative max_tx_power %d dBm, clamping to 0",
                       hwMode->channels[j].chan, maxTxPower);
            }
            hwMode->channels[j].max_tx_power = (u8)MAX((int8_t)0, maxTxPower);
        }

        /* Channel 14 frequency breaks frequency offset calculation */
        if (hwMode->channels[j].chan == CHANNEL_14)
        {
            hwMode->channels[j].freq = FREQ_CH_14;
        }

        hwMode->channels[j].allowed_bw = HOSTAPD_CHAN_WIDTH_20;
        j++;
    }

    return 0;
}

// ----------------------------------------------------------------------------
static void buildApHtCapability(struct hostapd_hw_modes *hwMode, const htCapabilities_t *pHtCap)
{
    os_memset(hwMode->mcs_set, 0, 16);

    os_memcpy(hwMode->mcs_set,
              pHtCap->suppMcsSet.rxMscBitmask,
              RX_MCS_BITMASK_SIZE);

    os_memcpy(&hwMode->mcs_set[RX_MCS_BITMASK_SIZE],
              &(pHtCap->suppMcsSet.highestSupportedDataRate),
              RX_HIGHEST_SUPP_DATA_RATE_BM_SIZE);

    os_memcpy(&hwMode->mcs_set[RX_MCS_BITMASK_SIZE +
                               RX_HIGHEST_SUPP_DATA_RATE_BM_SIZE],
              &(pHtCap->suppMcsSet.txSettingBM),
              sizeof(pHtCap->suppMcsSet.txSettingBM));

    hwMode->ht_capab = pHtCap->htCapabBM;

    //we want to disable AMSDU Support for AP Role always
    hwMode->ht_capab &= ~BIT_11;



    
    hwMode->a_mpdu_params = *((uint8_t *)&pHtCap->ampduCfg);
}

// ----------------------------------------------------------------------------
static int32_t ti_drv_buildSingleModeCapability(RoleType_e roleType,
                                                struct hostapd_hw_modes *hwMode)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    uint32_t basicRatesBM, supportedRatesBM;
    uint32_t i;
    Bool32 htSupported;
    int rates[DOT11_MAX_SUPPORTED_RATES];
    const htCapabilities_t *pHtCap = NULL;
    uint8_t band = 0;
    int32_t ret = 0;

    if (hwMode->mode == HOSTAPD_MODE_IEEE80211A)
    {
        // Get supported rates & remove B rates
        cfgGetRates(roleType, &basicRatesBM, &supportedRatesBM);

        // Remove MCS rates
        EXCLUDE_MCS_RATES(supportedRatesBM);

        supportedRatesBM = supportedRatesBM & ~ANY_B_RATE;
        hwMode->num_rates = convertBitmapToSupplicantRates(supportedRatesBM, rates);

        band = RADIO_BAND_5GHZ;
    }
    else if ((hwMode->mode == HOSTAPD_MODE_IEEE80211B) ||
             (hwMode->mode == HOSTAPD_MODE_IEEE80211G))
    {
        // Get supported rates & remove OFDM rates
        cfgGetRates(roleType, &basicRatesBM, &supportedRatesBM);

        // Remove MCS rates
        EXCLUDE_MCS_RATES(supportedRatesBM);

        if (hwMode->mode == HOSTAPD_MODE_IEEE80211B)
        {
            supportedRatesBM = supportedRatesBM & ~ANY_AG_OFDM_RATE;
        }

        hwMode->num_rates = convertBitmapToSupplicantRates(supportedRatesBM, rates);

        band = RADIO_BAND_2_4GHZ;
    }
    else
    {
        return -1;
    }

    ret = buildApChannelsCapability(roleType, hwMode, band);
    if (ret < 0)
    {
        GTRACE(MSG_ERROR, "WARNING: No channels found for HW mode");
        return -1;
    }

    htSupported = l2_cfgGetHtCapabilities(&pHtCap);

    if (htSupported)
    {
        buildApHtCapability(hwMode, pHtCap);
    }

    hwMode->rates = os_zalloc(sizeof(struct hostapd_rate_data) * (hwMode->num_rates));
    if (NULL == hwMode->rates)
    {
        os_free(hwMode->channels);
        GTRACE(MSG_ERROR, "ERROR: failed to allocate memory for rates info");
        return -1;
    }

    for (i = 0; i < hwMode->num_rates; i++)
    {
        hwMode->rates[i] = rates[i];
    }

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    return 0;
}

static int32_t getHwNumModes(uint16_t *numModes,
                             uint8_t *is2_4GHzBandSupported,
                             uint8_t *is5GHzBandSupported)
{
    uint8_t phyConfig = l2_GetPhyConfig();
    Bool_e regDomain_5GHzSupport;

    ASSERT_GENERAL(phyConfig <= 2);

    *numModes = 0;

    *is2_4GHzBandSupported = regulatoryDomain_isBandSupported(RADIO_BAND_2_4GHZ);

    regDomain_5GHzSupport = regulatoryDomain_isBandSupported(RADIO_BAND_5GHZ);
    *is5GHzBandSupported = (regDomain_5GHzSupport && l2_cfg_is5GhzSupported());

    if (phyConfig == L2_CFG_BAND_ONLY_2_4GHZ)
    {
        if (*is2_4GHzBandSupported == FALSE)
        {
            return -1;
        }
        *numModes = 1;
    }
    else if (phyConfig == L2_CFG_BAND_ONLY_5GHZ)
    {
        if (*is5GHzBandSupported == FALSE)
        {
            return -1;
        }
        *numModes = 1;
    }
    else if (phyConfig == L2_CFG_BAND_BOTH)
    {
        // It might happen that phyCfg and regulatory domain rules
        // aren't aligned. In this case we try to adjust the
        // phy configuration to the regulatory domain
        if ((*is2_4GHzBandSupported))
        {
            *numModes += 1;
        }

        if ((*is5GHzBandSupported))
        {
            *numModes += 1;
        }
    }

    return 0;
}

/* ----------------------------------------------------------------------------
 ti_driver_get_hw_feature_data
      This function reprots driver capabilities to supplicant.
      This includes supported bands and channels, HT capabilities.

 Parameters:    IN  priv     - Pointer to driver object
                OUT numModes - Pointer to number of supported modes
                OUT flags    - Pointer to flags, set to 0 as in MCP
 Return code:   On success - pointer to driver parameters
                On failure - NULL
---------------------------------------------------------------------------- */
struct hostapd_hw_modes *ti_driver_get_hw_feature_data(void *priv,
                                                       u16 *numModes,
                                                       u16 *flags, u8 *apDfs)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    struct hostapd_hw_modes *pHwModes = NULL;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)priv;
    uint8_t phyConfig = l2_GetPhyConfig();
    uint8_t is2_4GHzBandSupported = 0, is5GHzBandSupported = 0;
    uint8_t mode = 0;
    int32_t ret = 0;

    ret = getHwNumModes(numModes,
                        &is2_4GHzBandSupported,
                        &is5GHzBandSupported);
    if (ret < 0)
    {
        GTRACE(MSG_ERROR, "ERROR: Failed getting number "
                          "of supported HW modes");
        return NULL;
    }

    if (*numModes == 0)
    {
        GTRACE(MSG_ERROR, "ERROR: No HW mode is supported");
        return NULL;
    }

    pHwModes = os_zalloc((*numModes) * sizeof(struct hostapd_hw_modes));
    if (NULL == pHwModes)
    {
        GTRACE(MSG_ERROR, "ERROR: failed to allocate memory for HW modes");
        *numModes = 0;
        return NULL;
    }

    switch (phyConfig)
    {
        case L2_CFG_BAND_ONLY_2_4GHZ:
            pHwModes[0].mode = HOSTAPD_MODE_IEEE80211G;

            ret = ti_drv_buildSingleModeCapability(pDrv->roleType, &pHwModes[0]);
            if (ret < 0)
            {
                *numModes = 0;
                os_free(pHwModes);
                return NULL;
            }
            break;

        case L2_CFG_BAND_ONLY_5GHZ:
            pHwModes[0].mode = HOSTAPD_MODE_IEEE80211A;

            ret = ti_drv_buildSingleModeCapability(pDrv->roleType, &pHwModes[0]);
            if (ret < 0)
            {
                *numModes = 0;
                os_free(pHwModes);
                return NULL;
            }
            break;

        case L2_CFG_BAND_BOTH:

            if (is2_4GHzBandSupported)
            {
                pHwModes[mode].mode = HOSTAPD_MODE_IEEE80211G;
                ret = ti_drv_buildSingleModeCapability(pDrv->roleType, &pHwModes[mode]);
                if (ret < 0)
                {
                    *numModes = 0;
                    os_free(pHwModes);
                    return NULL;
                }
                mode++;
            }

            if (is5GHzBandSupported)
            {
                pHwModes[mode].mode = HOSTAPD_MODE_IEEE80211A;
                ret = ti_drv_buildSingleModeCapability(pDrv->roleType, &pHwModes[mode]);
                if (ret < 0)
                {
                    *numModes = 0;
                    os_free(pHwModes);
                    return NULL;
                }
            }

            break;

        default:
            ASSERT_GENERAL(0);
    }

    *flags = 0;

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    return pHwModes;
} // ti_driver_get_hw_feature_data

/* ----------------------------------------------------------------------------
 ti_driver_get_mac_addr
      Supply role's MAC address to supplicant

 Parameters:    apPriv - pointer to private driver DB
 Return code:   pointer to locak MAC address
---------------------------------------------------------------------------- */
const u8 * ti_driver_get_mac_addr(void *apPriv)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    return pDrv->macAddr;
} // ti_driver_get_mac_addr
/* ----------------------------------------------------------------------------
 ti_driver_state_changed
     This function is used to notify L2 driver connection state changes.
     CME is notified when L2 connection is established or when L2 disconnects.

 Parameters:    apDrv - pointer to drive instance
                new_state - new L2 state
                old_state - old L2 state

 Return code:   0
---------------------------------------------------------------------------- */
void ti_driver_state_changed(struct wpa_supplicant *wpa_s,
                             enum wpa_states new_state,
                             enum wpa_states old_state)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

    // This API serves the CME STA connection manager, for AP role there's
    // nothing to do here.
    if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
        return;
    }

    GTRACE(GRP_DRIVER_CC33, "ti_driver: state wpa_s->wpa_state=%d, new_state=%d, old_state=%d, pDrv->roleStarted=%d, CmeStationFlow_GetCurrentState()=%d",
                            wpa_s->wpa_state, new_state, old_state, pDrv->roleStarted, CmeStationFlow_GetCurrentState());

    CME_PRINT_REPORT("\n\rti_driver: state wpa_s->wpa_state=%d, new_state=%d, old_state=%d, pDrv->roleStarted=%d, CmeStationFlow_GetCurrentState()=%d roleType=%d",
                            wpa_s->wpa_state, new_state, old_state, pDrv->roleStarted, CmeStationFlow_GetCurrentState(), pDrv->roleType);

    if (ROLE_IS_TYPE_STA(pDrv->roleType))
    {
    // During BSS transition flow, the CME state is different from CME_STA_SUPPLICANT_MANAGED_STATE. 
    // If we reach this point when gBssTransitionState is BTM_RECEIVED and the CME state is CME_STA_SUPPLICANT_MANAGED_STATE, 
    // it means that a BTM request was received but the transition was rejected. Set gBssTransitionState back to NO_TRANSITION.
    if ((gBssTransitionState == BTM_RECEIVED) && (CmeStationFlow_GetCurrentState() == CME_STA_SUPPLICANT_MANAGED_STATE))
    {
        gBssTransitionState = NO_TRANSITION;
    }

    // Since the BSS transition is triggered by the supplicant and not by the CME, we want to avoid
    // the CME state change handling during the transition to the new AP. Once connected, we must update the 
    // new AP details and send the required notifications.
    if (gBssTransitionState != NO_TRANSITION)
    {
        GTRACE(GRP_DRIVER_CC33, "ti_driver_state_changed: bss transition flow, gBssTransitionState=%d", gBssTransitionState);
        CME_PRINT_REPORT("\n\rti_driver_state_changed: bss transition flow, gBssTransitionState=%d", gBssTransitionState);
    }
    }
    //If we are out of scanning, and we are after 'wpa_select_network (called by cme connection manager)', we should zero this flag.
    //if we are out of scanning in other cases (i.e. WPS), it does not matter and we can zero this flag anyway.
    if (old_state == WPA_SCANNING)
    {
        wpa_s->cc33xx_initiated_select_network = 0;
    }

    // Filter disconnect (or other?) events while in WPS, or the first disconnect after a successful WPS for 'fast connect' via supplicant
    // Don't filter if external WPS is in progress because this allows the supplicant to keep trying to reconnect if the AP deauthenticats the STA
    if (((CME_IsOngoingWPSAdHocConnection()) || (gWPSfirstDisconnect_ull==TRUE))
        && !(isextWPS() && isExtWpsInProgress()))
    {
        if (gWPSkickDisconnect_ull)
        {
            gWPSkickDisconnect_ull = FALSE;
            gWPSfirstDisconnect_ull = FALSE; 
        }
        else if (WPA_DISCONNECTED == new_state)
        {
            //Filter WPS first disconnect
            //TODO: Do we want to send a different disconnect event to the CME and it will filter it?
            if (gWPSfirstDisconnect_ull)
            {
                GTRACE(GRP_DRIVER_CC33, "WPS: filter first disconnect after WPS");
            }
            else
            {
                GTRACE(GRP_DRIVER_CC33, "WPS: filter disconnect event");
            }

            gWPSfirstDisconnect_ull = FALSE;

            return;

        }
        else if (WPA_ASSOCIATED == new_state)
        {
            //Disregard the first associated event in WPS since we are about to disconnect and connect again.
            //The scan results table is still needed.
            CME_NotifyStaConnectionState(pDrv->roleId, LINK_CONNECTION_STATE_ASSOCIATED, 0);
            return;
        }
    }

#ifdef CC33XX_DRIVER_DEBUG
    // This is just for forcing disconnect during different connection stages
    // TODO - remove once CME SM is defined as fully tested
    if ( (WPA_COMPLETED != wpa_s->wpa_state) && (wpa_s->wpa_state == gSuppDrvDebugInfo_ull.sta.gForceDisconnectState) )
    {
        GTRACE(GRP_DRIVER_CC33, "Forcing disconnect for state %d", gSuppDrvDebugInfo_ull.sta.gForceDisconnectState);
        CME_WlanDisconnect(FALSE);

        // Clear the disconnection constraint
        gSuppDrvDebugInfo_ull.sta.gForceDisconnectState = 100;
    }
#endif

    if (((WPA_AUTHENTICATING == old_state) || (WPA_ASSOCIATING == new_state)) && 
        (gBssTransitionState == NO_TRANSITION))
    {
        GTRACE(GRP_DRIVER_CC33, "Calling  CME_NotifyStaConnectionState. - new state SUPP_CONNECTING ");

        CME_NotifyStaConnectionState(pDrv->roleId, LINK_CONNECTION_STATE_CONNECTING, 0);
    }

    if (WPA_COMPLETED == new_state)
    {
        // In case of 4 way handshake, ignore the second WPA_COMPLETED event
        // In case of BSS transition, pDrv->connected is already true
        if ((FALSE == pDrv->connected) || (gBssTransitionState == TRANSITION_IN_PROGRESS))
        {
            uint32_t apLink;

            pDrv->connected = TRUE;
            Bool_e wmm;

            //this is made after the 4 phase handshake to prevent configuration to the FW during the 4 phase handshake
            ti_drv_setApAssocInfo(pDrv);

            if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
            {

                apLink = udataNet_GetTxMgmtLink(TIWDRV_NETIF_ID_SAP, pDrv->currBssid);
                wmm = cfgIsApWmeEnabled();

            }
            else
            {

                apLink = udataNet_GetTxMgmtLink(TIWDRV_NETIF_ID_STA, pDrv->currBssid);
                wmm = cfgIsStaWmeEnabled();

            }

            if(INVALID_LINK == apLink )
            {
                GTRACE(GRP_DRIVER_CC33, "ti_driver_state_changed: ERROR unsupported link id %d",apLink);
                TX_DATA_SEND_PRINT_ERROR("\n\rERROR!!ti_driver_state_changed: ERROR unsupported link id %d",apLink);
                return;
            }



            // activate SetLinkState which sets WMM and calls the below.
            // In cc33xx FW manages WMM state so setting WMM is irrelevant.
            pDrv->ops->set_peer_state(apLink, /* LINK_STATE_CONNECTED */1, wmm );

            // Notify RSN module
            rsn_setPortStatus(pDrv->roleId, 1);
            
            Bool_e encrypted = wlanLinks_GetLinkDataEncryption(apLink);
            udata_SetEapolEncryption(apLink, encrypted);

            pDrv->ops->cancel_remain_on_channel(pDrv);


            GTRACE(GRP_DRIVER_CC33, "Calling  CME_NotifyStaConnectionState. - new state WPA_COMPLETED ");

            CME_NotifyStaConnectionState(pDrv->roleId, LINK_CONNECTION_STATE_CONNECTED, 0);

        }
        // A transition to WPA_COMPLETED state while connected may happen in case
        // of rekey, just make sure this is the case.
        else if ((WPA_GROUP_HANDSHAKE != old_state) && (WPA_4WAY_HANDSHAKE != old_state))
        {
            GTRACE(GRP_GENERAL_ERROR, "ERROR: Invalid state transition from %d to WPA_COMPLETED",
                                      old_state);
            ASSERT_GENERAL(FALSE);
        }

        if ((WPA_GROUP_HANDSHAKE == old_state) || (WPA_4WAY_HANDSHAKE == old_state))
        {
            //this transition means Security/Rekey ended and therefore stop mgmt sequence for it
            //ti_driver_start_security_mgmt_seq(pDrv->roleId);
        }
    }
    else if ((gBssTransitionState != NO_TRANSITION) && 
             ((WPA_ASSOCIATING == old_state) && (new_state == WPA_DISCONNECTED)))
    {
        //we are during BSS transition but association was rejected
        //clean up association attempt and prepate for potential retry
        //do not disconnect
        CME_PRINT_REPORT("\n\rAssoc rejected during btm.");
        if (ROLE_IS_TYPE_STA(pDrv->roleType))
        {
            cmeRemoveWpaPmkCache();
        }
        //notify associating failure?
    }
    // Transition from connected to disconnected (may be reconnecting or scanning)
    else if (((WPA_ASSOCIATED <= old_state) && (new_state < WPA_ASSOCIATED) && (gBssTransitionState == NO_TRANSITION)) ||
             ((WPA_DISCONNECTED == new_state) && (gBssTransitionState != NO_TRANSITION)))
    {
        pDrv->connected = FALSE;
        pDrv->connectTimeout = FALSE;

        // Notify RSN module, it will forward the new state to data path
        rsn_setPortStatus(pDrv->roleId, 0);
        int apLink = udataNet_GetTxMgmtLink(TIWDRV_NETIF_ID_STA, pDrv->currBssid);
        udata_SetEapolEncryption(apLink, 0);

        //If we reached here, role should already be stopped
        //ASSERT_GENERAL (FALSE == pDrv->roleStarted);

        if (FALSE == pDrv->roleStarted)
        {
            GTRACE(GRP_DRIVER_CC33, "Calling  CME_NotifyStaConnectionState. - LINK_CONNECTION_STATE_DISCONNECTED ");

            CME_NotifyStaConnectionState(pDrv->roleId, LINK_CONNECTION_STATE_DISCONNECTED, pDrv->deauthReason);
        }

    }
    // Disconnection during connection sequence
    else if (  (WPA_DISCONNECTED == new_state) &&
               ((WPA_ASSOCIATING == old_state) || (WPA_AUTHENTICATING == old_state)) /*&&
               (TRUE == pDrv->roleStarted)*/
            )
    {
        // Error, CME can release its memory
        CME_ReleaseScanResults(CALLER5);

        finalizeStaDisconnect(pDrv, 975);
        GTRACE(GRP_DRIVER_CC33, "Calling  CME_NotifyStaConnectionState. - Disconnection during connection ");
        CME_NotifyStaConnectionState(pDrv->roleId, LINK_CONNECTION_STATE_DISCONNECTED, pDrv->deauthReason);
    }
    //sta is associated
    else if (WPA_ASSOCIATED == new_state)
    {
        CME_NotifyStaConnectionState(pDrv->roleId, LINK_CONNECTION_STATE_ASSOCIATED, 0);
    }
    else if (    (new_state == WPA_4WAY_HANDSHAKE)
              && (old_state == WPA_COMPLETED)
            )
    {
        //this transition means Rekey starts and therefore start mgmt sequence for it
        //and request to be in active mode
        //cc33_driver_start_security_mgmt_seq(pDrv->roleId);
    }
    else if (new_state <= WPA_INACTIVE)
    {
        CME_ReleaseScanResults(CALLER6); // Clean any leftovers anyway

        if (old_state == WPA_SCANNING)
        {
            CME_PRINT_REPORT("\n\rCME_notifyScanDone");
            CME_notifyScanDone(pDrv->roleId);
            
            // Disconnection during scan while in WPS
            if (CME_IsOngoingWPSAdHocConnection())
            {
                CME_NotifyStaConnectionState(pDrv->roleId, LINK_CONNECTION_STATE_DISCONNECTED, pDrv->deauthReason);
            }
        }
    }

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

} // ti_driver_state_changed



/* ----------------------------------------------------------------------------
 ti_driver_send_l2_data
      This function sends an l2 data frame.

 Parameters:    pDrv - pointer to private driver DB
                dst_addr - destination address
                proto - l2 protocol used
                *pData - data
                dataLen
                Bool_e forceUnsecure - Send the packet with no encryption

 Return code:   0 - OK, -1 - failure
---------------------------------------------------------------------------- */
/*Private ethertype for TI Wilink driver management packets*/
#define TIWDRV_MGMT_ETH_TYPE            0x889A

int ti_driver_send_l2_data(ti_driver_ifData_t *pDrv,
                           const u8 *dst_addr,
                           u16 proto,
                           const u8 *pData,
                           size_t dataLen)
{

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    int status = 0, syncObjResult = 0;
    TMgmtPktDesc *pMgmtPkt;
    TEthernetHeader *pEthHead= NULL;
    uint8_t link = 0;
    uint32_t uNetIfId = 0, extraHThdr,total_len;
    dot11_mgmtHeader_t *pDot11Header = NULL;
    TTxCtrlBlk *pPktCtrlBlk = NULL;
    uint16_t fc=0;

    extraHThdr = IEEE80211_HT_CTL_LEN; // Add 4 bytes gap, may be filled later on by the PMAC

    if(ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
    {
        uNetIfId = TIWDRV_NETIF_ID_STA;
    }
    else if(ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
        uNetIfId = TIWDRV_NETIF_ID_SAP;
    }
    else if(ROLE_IS_TYPE_DEVICE(pDrv->roleType))
    {
        uNetIfId = TIWDRV_NETIF_ID_P2PDEV;
    }
    else
    {
        ASSERT_GENERAL(0);
    }

    txDataQ_LinkMacFind((uint8_t *)&link, (uint8_t *)dst_addr);

    if (INVALID_LINK == link)
    {
        GTRACE(GRP_DRIVER_CC33, "ti_driver_send_l2_data: No valid hlid was found!  NetifId = %d\n\r", link);
        status = -1;
        goto fail;
    }

    ///////////////////////////////////////////////////////
    /* Insert Tx MGMT packet from hostap to the driver without the Ethernet header (having WLAN header under it) */
    if (TIWDRV_MGMT_ETH_TYPE == proto)
    {

        CME_PRINT_REPORT("\n\rSend L2 packet of type TIWDRV_MGMT_ETH_TYPE");


        total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + sizeof(dot11_mgmtHeader_t) + extraHThdr + dataLen;
        /* allocate mgmt packet descriptor and buffers */
        pMgmtPkt = udata_AllocTxMgmtPacket( sizeof(dot11_mgmtHeader_t) + extraHThdr, dataLen, NULL);
        if (!pMgmtPkt)
        {
            GTRACE(GRP_DRIVER_CC33, "ti_driver_send_l2_data: Failed to allocate TMgmtPktDesc for Tx MGMT packet\n\r");
            CME_PRINT_REPORT_ERROR ("\r\nti_driver_send_l2_data: Failed to allocate TMgmtPktDesc for Tx MGMT packet\n\r");
            status = -1;
            goto fail;
        }
        set_nab_tx_header(pMgmtPkt->nabHeader, total_len );


        pMgmtPkt->link = link;
        pMgmtPkt->ePktType = UDATA_TX_PKT_TYPE_WLAN_MGMT;
        pMgmtPkt->flags = PKTF_EXTERNAL_CONTEXT;


        /* Set Tx-complete callback for sending back the packet upon completion */
        pMgmtPkt->fTxCompleteCb = (TMgmtPacketCb)CME_TxResult;

        /* copy header and payload to new buffers - the Ethernet header on top of the WLAN header is dropped */
        pDot11Header = (dot11_mgmtHeader_t *) pMgmtPkt->header;

        fc = DOT11_FC_TYPE_MGMT ;
        if (pDrv->pAuthInfo->authType)
        {
            fc |= DOT11_FC_WEP;
            pMgmtPkt->flags |= PKTF_ENCRYPT;
        }
        COPY_WLAN_WORD(&pDot11Header->fc, &fc);

        MAC_COPY (pDot11Header->DA, (uint8_t *)dst_addr);
        MAC_COPY (pDot11Header->SA, (uint8_t *)pDrv->macAddr);
        MAC_COPY (pDot11Header->BSSID, (uint8_t *)pDrv->currBssid);

        os_memcpy(pMgmtPkt->payload, pData, dataLen);

        /* submit for tx */
        status = udata_SendTxMgmtPacket(pMgmtPkt);
    }
    ///////////////////////////////////////////////////////
    /* Insert EAPOL packet to the driver Tx Mgmt path (Ethernet format) */
    else if(ETHERTYPE_EAPOL == proto)
    {
        CME_PRINT_REPORT("\n\rSend L2 packet of type ETHERTYPE_EAPOL dataLen:%d link=%d",
            dataLen, link);

        pEthHead  = os_malloc(sizeof(TEthernetHeader));
        if (!pEthHead)
        {
            TX_DATA_SEND_PRINT_ERROR("\n\rERROR ti_driver_send_l2_data: Failed to allocate TEthernetHeader for Tx EAPOL packet\n\r", __FUNCTION__);
            status = -1;
            goto fail;
        }
        os_memcpy(pEthHead->dst, dst_addr, MAC_ADDR_LEN);
        MAC_COPY(pEthHead->src, (uint8_t *)pDrv->macAddr);
        pEthHead->type = BYTE_SWAP_WORD(proto);

        total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + ETHERNET_HDR_LEN + dataLen;
        /* allocate mgmt packet descriptor and buffers */
        pMgmtPkt = udata_AllocTxMgmtPacket(ETHERNET_HDR_LEN, dataLen, pEthHead);
        if (!pMgmtPkt)
        {
            TX_DATA_SEND_PRINT_ERROR("\n\rERROR ti_driver_send_l2_data: Failed to allocate TMgmtPktDesc for Tx EAPOL packet:%s\n\r", __FUNCTION__);
            status = -1;
            os_free(pEthHead);
            goto fail;
        }
        set_nab_tx_header(pMgmtPkt->nabHeader, total_len );

        /* Set Tx-complete callback for sending back the packet upon completion */
        pMgmtPkt->fTxCompleteCb = (TMgmtPacketCb)CME_EapolTxResult;

        //
        /* prepare WLAN header */
        pDot11Header = (dot11_mgmtHeader_t *) pMgmtPkt->header;

        COPY_WLAN_WORD(&pDot11Header->fc, &fc);

        pMgmtPkt->link = link;
        pMgmtPkt->ePktType = UDATA_TX_PKT_TYPE_ETHER_EAPOL;
        pMgmtPkt->flags = PKTF_EXTERNAL_CONTEXT;


        /* copy payload to new buffers - the Ethernet header on top of the WLAN header is dropped */
        os_memcpy(pMgmtPkt->payload, pData, dataLen);

        GTRACE(GRP_DRIVER_CC33, "Ether type is ETHERTYPE_EAPOL 0x%x \n\r", proto);


        /* submit for tx */
        status = udata_SendTxMgmtPacket(pMgmtPkt);

        /* Wait for TX complete on EAPOLs */
        if (uNetIfId == TIWDRV_NETIF_ID_STA)
        {
            syncObjResult = osi_SyncObjWait(&gCmeEapolsStaSyncObject, EAPOLS_TX_TIMEOUT);
            if (OSI_OK != syncObjResult)
            {
                GTRACE(GRP_DRIVER_CC33, "ERROR: Waiting for gCmeEapolsStaSyncObject failed with result %d", syncObjResult);
            }
        }
    }
    ////////////////////////////  DATA  ///////////////////////////
    /* Insert data packet to the driver Tx Data path (Ethernet format) */
    else
    {
        GTRACE(GRP_DRIVER_CC33, "Ether type is Data type 0x%x \n\r", proto);
        TX_DATA_SEND_PRINT("\n\rsend Ether Data 0x%x datalen %d", proto, dataLen);

        if (((proto != FRAME_TYPE_NO_DATA_FRAME) && (proto != FRAME_TYPE_QOS_NO_DATA_FRAME)) && dataLen == 0)
        {
            TX_DATA_SEND_PRINT_ERROR("\n\r Error: Data frame with no data (datalen 0)");
            status = -1;
            goto fail;
        }

        pEthHead  = os_malloc(sizeof(TEthernetHeader));
        if (!pEthHead)
        {
            TX_DATA_SEND_PRINT("ti_driver_send_l2_data: Failed to allocate TEthernetHeader for Tx data packet:%s\n\r", __FUNCTION__);
            status = -1;
            goto fail;
        }
        os_memcpy(pEthHead->dst, dst_addr, MAC_ADDR_LEN);
        os_memcpy(pEthHead->src, pDrv->macAddr, MAC_ADDR_LEN);
        pEthHead->type = BYTE_SWAP_WORD(proto);

        total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + ETHERNET_HDR_LEN + dataLen;

        /* allocate data packet descriptor and buffers */
        pPktCtrlBlk = udata_AllocTxDataPacket(dataLen,ETHERNET_HDR_LEN,pEthHead);

        if (!pPktCtrlBlk)
        {
            GTRACE(GRP_DRIVER_CC33, "ti_driver_send_l2_data: Failed to allocate TxCtrlBlk\n\r");
            TX_DATA_SEND_PRINT_ERROR("\n\rERROR ti_driver_send_l2_data: Failed to allocate TxCtrlBlk");
            status = -1;
            os_free(pEthHead);
            goto fail;
        }
        set_nab_tx_header(&pPktCtrlBlk->aPktNabHdr, total_len );

        /* copy payload to new buffers - the Ethernet header is dropped later on and replaced with wlan header*/
        if(pData != NULL)//for NULL data packets Pdata = NULL
            os_memcpy(pPktCtrlBlk->tTxPktParams.pInputPkt, pData, dataLen);

        /* if ip_summed is set to PARTIAL by NS,
         * it means the NS agrees & expects the HW to do
         * the checksum for tcp/udp packets only. */
        /*if TCP/UDP and Checksum offload enabled*/

#if 0 // TODO: Need to implement
        if (skb->ip_summed == CHECKSUM_PARTIAL)
        {
            pPktCtrlBlk->tTxDescriptor.csumData = *((TI_UINT8*)(skb_network_header(skb) + IP_PROTOCOL_OFFSET));
        }
        else
#endif
        {
            pPktCtrlBlk->tTxDescriptor.csumData = 0;
        }

        if ((proto == FRAME_TYPE_NO_DATA_FRAME) || (proto == FRAME_TYPE_QOS_NO_DATA_FRAME))
        {
            pPktCtrlBlk->tTxPktParams.isNullDataFrame = 1;
        }

        /* Send the packet to the driver for transmission. */
        status = udataNet_InsertDataPacket(pPktCtrlBlk, uNetIfId, D_TAG_CLSFR /* TODO: need to implement */);
		return status; // no need to free pEthHead, it will be free by lower layers
    }


fail:
    return status;
} // ti_driver_send_l2_data

/* ----------------------------------------------------------------------------
 ti_driver_set_country
      Set country to regulatory domain

 Parameters:    apPriv - pointer to private driver DB
                apCountry - pointer to country to be set
 Return code:   0 - success indication
---------------------------------------------------------------------------- */
int ti_driver_set_country(void *apPriv, const char *apCountry)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    GTRACE(GRP_DRIVER_CC33, "Set country to %s", apCountry);

    pDrv->countryUpdated = TRUE;

    return 0;
} // ti_driver_set_country

/* ----------------------------------------------------------------------------
 ti_driver_get_country
      This function returns the current country code to supplicant

 Parameters:    IN  apPriv - pointer to private driver DB
                OUT apCountry - pointer to current country code
 Return code:   0 - success indication, -1 - failure
---------------------------------------------------------------------------- */
int ti_driver_get_country(void *apPriv, char *apCountry)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    return regulatoryDomain_getCountryString((uint8_t*)apCountry);
} // ti_driver_set_country


/* ----------------------------------------------------------------------------
 ti_driver_send_mgmt_frame
      This function sends managment frame

---------------------------------------------------------------------------- */
int ti_driver_send_mgmt_frame(void *apPriv,
                              const uint8_t *apData,
                              size_t aDataLen,
                              int aNoack,
                              unsigned int freq,
                              const uint16_t *csa_offs,
                              size_t csa_offs_len,
                              int no_encrypt,
                              unsigned int wait)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    int32_t ret = 0;

    GTRACE(GRP_DRIVER_CC33, "ti_driver_send_mgmt_frame: roletype=%d", 
                            pDrv->roleType);

    if(ROLE_IS_TYPE_AP_BASED_OR_DEVICE(pDrv->roleType))
    {
        //for AP or P2P_GO or P2P Device
        //if freq = 0 means Use bss->freq and wait_time =0
        if (((freq == pDrv->freq) || (freq == 0)))
        {
            wpa_printf(MSG_DEBUG, "ti_driver: P2P send mgmt frame on bss-freq :%d",pDrv->freq);
            ret = ti_send_mgmt_frame(pDrv, apData, aDataLen);
            if(ret < 0)
            {
                wpa_printf(MSG_ERROR, "ti_driver: ti_driver_remain_on_channel failed !");
            }
        }
        else if(pDrv->capa.flags & WPA_DRIVER_FLAGS_OFFCHANNEL_TX)
        {
            wpa_printf(MSG_INFO, "ti_driver: P2P off channel freq:%d pDrv->freq:%d",freq, pDrv->freq);
            //wpa_printf(MSG_ERROR, "ti_driver: lock1");
            osi_LockObjLock(&g_offChannelDev.p_off_channel_mutex , OSI_WAIT_FOREVER);
            //it will be delivered by the remain on channel
            g_offChannelDev.p_off_channel_mgmt_data = apData;
            g_offChannelDev.off_channel_mgmt_datalen = aDataLen;
            
            ret = ti_driver_remain_on_channel(pDrv, freq, wait); 
            if(ret < 0)
            {
                wpa_printf(MSG_ERROR, "ti_driver: ti_driver_remain_on_channel failed !");
            }
            //wpa_printf(MSG_ERROR, "ti_driver: unlock1");
            osi_LockObjUnlock(&g_offChannelDev.p_off_channel_mutex);
        }
        else
        {
            wpa_printf(MSG_ERROR, "ti_driver: 0ff channel is not allowed! freq:%d pDrv->freq:%d",freq,pDrv->freq);
            return -1;
        }
    }
    else
    {
        //for STA and for P2P_DEVICE : WLAN_FC_STYPE_PROBE_RESP
        //if freq =0 the last mgmt freq need to be used
        //wait-time is always 0
        //off-channel is OK.
        ti_send_mgmt_frame(pDrv, apData, aDataLen);
    }
    return(ret);

}
/* start dev role and roc on its channel */
int ti_driver_start_dev(void *apPriv,
            dot11_band band, int channel)
{
    int ret = 0;
#if 0
    if (WARN_ON(!(wlvif->bss_type == BSS_TYPE_STA_BSS ||
              wlvif->bss_type == BSS_TYPE_IBSS)))
        return -EINVAL;

    /* the dev role is already started for p2p mgmt interfaces */

    if (!wlcore_is_p2p_mgmt(wlvif)) {
        ret = cc33xx_cmd_role_enable(wl,
                         cc33xx_wlvif_to_vif(wlvif)->addr,
                         CC33XX_ROLE_DEVICE,
                         &wlvif->dev_role_id);
        if (ret < 0)
            goto out;
    }

    cc33xx_debug(DEBUG_CMD, "cmd role start dev");
    ret = cc33xx_cmd_role_start_dev(wl, wlvif, band, channel);
    if (ret < 0)
        goto out_disable;

    cc33xx_debug(DEBUG_CMD, "cmd roc");
    ret = cc33xx_roc(wl, wlvif, wlvif->dev_role_id, band, channel);
    if (ret < 0)
        goto out_stop;

    return 0;

out_stop:
    cc333xx_cmd_role_stop_dev(wl, wlvif);
out_disable:
    if (!wlcore_is_p2p_mgmt(wlvif))
        cc33xx_cmd_role_disable(wl, &wlvif->dev_role_id);
out:
#endif
    return ret;
}


/* ----------------------------------------------------------------------------
 ti_driver_send_action
      This function sends an action frame to LTXP.

 Parameters:    apPriv - pointer to private driver DB

 Return code:   0 - OK, -1 - failure
---------------------------------------------------------------------------- */
int ti_driver_send_action(void *apPriv,
                            unsigned int aFreq,
                            unsigned int aWaitTime,
                            const u8 *apDst,            // Destination address
                            const u8 *apSrc,
                            const u8 *apBssid,
                            const u8 *apData,
                            size_t aDataLen,
                            int    aNoCck)
{
    ti_driver_ifData_t* pDrv = apPriv;
    int32_t ret = -1;
    uint8_t *buf;
    struct ieee80211_hdr *hdr;
    int32_t offchanok = 1;
    int32_t hdr_len = WLAN_HDR_LEN;
    struct ieee80211_mgmt *pMgmt;

    if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType) && (int) (aFreq == pDrv->freq) &&
            pDrv->beacon_set)
        offchanok = 0;

    wpa_printf(MSG_DEBUG, "ti_driver: Send Action frame ( "
           "freq=%u MHz wait=%d ms no_cck=%d offchanok=%d)",
           aFreq, aWaitTime, aNoCck, offchanok);

    wpa_printf(MSG_DEBUG,
            "ti_driver: apBssid: " MACSTR " apSrc: " MACSTR "apDst: " MACSTR ,
            MAC2STR(apBssid),MAC2STR(apSrc), MAC2STR(apDst));

    buf = os_zalloc(hdr_len + aDataLen);
    if (buf == NULL)
        return ret;
    os_memcpy(buf + hdr_len, apData, aDataLen);
    hdr = (struct ieee80211_hdr *) buf;
    hdr->frame_control =
        IEEE80211_FC(WLAN_FC_TYPE_MGMT, WLAN_FC_STYPE_ACTION);
    os_memcpy(hdr->addr1, apDst, ETH_ALEN);
    os_memcpy(hdr->addr2, apSrc, ETH_ALEN);
    os_memcpy(hdr->addr3, apBssid, ETH_ALEN);

    // in case of BTM response, clear the supplicant operation protection bit
    // that was set upon receiving the BTM request.
    pMgmt = (struct ieee80211_mgmt *)buf;
    if ((pMgmt->u.action.category == WLAN_ACTION_WNM) &&
        (pMgmt->u.action.u.bss_tm_req.action == WNM_BSS_TRANS_MGMT_RESP))
    {
        set_finish_wlan_supplicant_operation();
    }

    //enter the message to the queue with the sync object
    ret =  ti_driver_send_mgmt_frame(pDrv, buf, hdr_len + aDataLen, 0, aFreq, 0, 0, 0, aWaitTime);

    os_free(buf);
    return ret;


}  // ti_driver_send_action

/* ----------------------------------------------------------------------------
ti_driver_send_action_cancel_wait

            This command cancels the wait time associated with sending an action
	        frame. It is only available when %WPA_DRIVER_FLAGS_OFFCHANNEL_TX is
	        set in the driver flags.

Parameters:    apPriv - pointer to private driver DB
       
Return code:   0 - parameters OK, -1 - error indication
---------------------------------------------------------------------------- */

void ti_driver_send_action_cancel_wait(void *apPriv)
{
    ti_driver_ifData_t* pDrv = apPriv;
    int ret;

    wpa_printf(MSG_DEBUG, "ti_driver: ti_driver_send_action_cancel_wait roleid=%d, RocInitiateExplicitly=%d", 
                        pDrv->roleId, g_offChannelDev.RocInitiateExplicitly);

    //if roc was set - cancel it
    if((pDrv->offChannel_roc_started) 
        && (g_offChannelDev.RocInitiateExplicitly == FALSE))
    {
        wpa_printf(MSG_INFO, "ti_driver: ti_driver_cancel_remain_on_channel from ti_driver_send_action_cancel_wait");
       // wpa_printf(MSG_ERROR, "ti_driver: lock4");
       // osi_LockObjLock(&g_offChannelDev.p_off_channel_mutex , OSI_WAIT_FOREVER);
        ret = ti_driver_cancel_remain_on_channel(g_remain_on_channel_apPriv);
        if(ret < 0)
        {
            wpa_printf(MSG_ERROR, "ti_driver: ti_driver_remain_on_channel failed !");
        }
        //wpa_printf(MSG_ERROR, "ti_driver: unlock4");
       // osi_LockObjUnlock(&g_offChannelDev.p_off_channel_mutex);


        //g_remain_on_channel_apPriv = NULL;//not needed anymore?
    }


}//ti_driver_send_action_cancel_wait

/* ----------------------------------------------------------------------------
 ti_driver_ext_set_ROC
      This function create device role enable it and  role start.
      In  it sets ROC on the channel

 Return code:   0 - OK, -1 - failure
---------------------------------------------------------------------------- */
int ti_driver_ext_set_ROC( uint32_t    channel,
                           uint8_t* countryDomain)

{
    int32_t roleId, ret = 0;
    struct wpa_supplicant *wpa_s;
    RoleUpApCmd_t RoleUpStaParams;
    int32_t duration;

    osi_LockObjLock(&extAppLockObj, OSI_WAIT_FOREVER);

    os_memset(&RoleUpStaParams, 0x0, sizeof(RoleUpApCmd_t));
    RoleUpStaParams.channel = channel;
    os_memcpy(&RoleUpStaParams.countryDomain[0], countryDomain, 3);


    GTRACE(GRP_CME,"ti_driver_ext_set_ROC: Send ROC from external channel :%d",channel);
    CME_PRINT_REPORT("\n\rti_driver: Send ROC from external channel :%d",channel);


    roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_DEVICE);
    if(roleId == ROLE_ID_NONE)
    {
        GTRACE(GRP_CME,"ti_driver_ext_set_ROC, create device role");
        CME_PRINT_REPORT_ERROR("\n\rti_driver_ext_set_ROC, create device role");

        ret = roleUp_Inter(WLAN_ROLE_DEVICE, &RoleUpStaParams, WLAN_WAIT_TIME_ROLE_SWITCH);
        if(ret < 0)
        {
            GTRACE(GRP_CME,"ti_driver_ext_set_ROC, Wlan_RoleUp failed");
            CME_PRINT_REPORT_ERROR("\n\rtti_driver_ext_set_ROC, Wlan_RoleUp failed");
            ret = -1;
            goto out;

        }
    }
    else
    {
        GTRACE(GRP_CME,"ti_driver_ext_set_ROC, DEVICE role already exists");
        CME_PRINT_REPORT_ERROR("\r\nti_driver_ext_set_ROC, DEVICE role already exists");
        ret = -1;
        goto out;
    }

    wpa_s = drv_getP2pDeviceSupplicant(); 

    //role was not enabled
    if(wpa_s == NULL )
    {
        GTRACE(GRP_CME,"ERROR ! ti_driver: Send ROC from external, DEVICE role doesn't exists");
        CME_PRINT_REPORT("\r\nERROR ! ti_driver: Send ROC from external, DEVICE role doesn't exists");
        ret = -1;
        goto out;
    }

    duration = CC33_ROC_ENDLESS_TIMOUT;

    //call ROC
    CME_RemainOnChannelNotify(wpa_s, roleId, channel_to_freq(channel), duration);

out:
    osi_LockObjUnlock(&extAppLockObj);
    return ret;
}

/* ----------------------------------------------------------------------------
 ti_driver_ext_set_CROC()
 this function Cancel the ROC
 Return code:   0 - OK, -1 - failure
---------------------------------------------------------------------------- */
int ti_driver_ext_set_CROC(uint8_t calledFromCmeThread,uint32_t is_croc_performed_due_to_timeout)
{
    int32_t roleId, ret= 0;
    struct wpa_supplicant *wpa_s;
    uint8_t roleid = ROLE_DEVICE;

    CME_PRINT_REPORT("\r\nti_driver_ext_set_CROC , calledFromCmeThread :%d\r\n",calledFromCmeThread);

    if(!calledFromCmeThread)
    {
    	ret = osi_LockObjLock(&extAppLockObj, OSI_WAIT_FOREVER);
        if(ret != 0)
        {
            GTRACE(GRP_CME,"ERROR ! ti_driver_ext_set_CROC, failed to take extAppLockObj \r\n ");
            CME_PRINT_REPORT_ERROR("\r\nERROR ! ti_driver_ext_set_CROC, failed to take extAppLockObj \r\n");
            return ret;
        }

    }
    else
    {
    	ret = osi_LockObjLock(&extAppLockObj, OSI_NO_WAIT);
        if(ret != 0)
        {
            GTRACE(GRP_CME,"NOTICE ! ti_driver_ext_set_CROC, called due to cROC timeout ,failed to take extAppLockObj , no need to hanle");
            CME_PRINT_REPORT("\r\nNOTICE ! ti_driver_ext_set_CROC, called due to cROC timeout ,failed to take extAppLockObj , no need to hanle \r\n");
            //free the CME thread so the other work can be perform.
            return ret;
        }
    }

    roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_DEVICE);
    if(roleId == ROLE_ID_NONE)
    {
        GTRACE(GRP_CME,"ERROR ! ti_driver_ext_set_CROC, DEVICE role already exists");
        CME_PRINT_REPORT("\r\nERROR ! ti_driver_ext_set_CROC, DEVICE role not exists");
        ret = -1;
        goto out;
    }
    wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);

    //role was not enabled
    if(wpa_s == NULL )
    {
        GTRACE(GRP_CME,"ERROR ! ti_driver_ext_set_CROC, DEVICE role doesn't exists");
        CME_PRINT_REPORT("\r\nERROR ! ti_driver_ext_set_CROC, DEVICE role doesn't exists\r\n");
        ret = -1;
        goto out;
    }

    if(calledFromCmeThread)
    {

    	ret =  CME_CancelRemainOn_from_CME_thread(is_croc_performed_due_to_timeout);
    	ret = Wlan_RoleDown_from_CME_thread(WLAN_ROLE_DEVICE, WLAN_WAIT_FOREVER);
    }
    else
    {
        ret = CME_CancelRemainOnChannelNotify(wpa_s,is_croc_performed_due_to_timeout);

        if(ret < 0)
        {
            GTRACE(GRP_CME,"ERROR ! ti_driver:  CME_CancelRemainOnChannelNotify failed");
            CME_PRINT_REPORT("\r\nERROR ! ti_driver: CME_CancelRemainOnChannelNotify failed\r\n");
            ret = -1;
            goto out;
        }

    	ret = roleDown_inter(WLAN_ROLE_DEVICE, WLAN_WAIT_TIME_ROLE_SWITCH);
    }
    if(ret < 0)
    {
        GTRACE(GRP_CME,"ti_driver_ext_set_CROC, WARNING ! device role down exit with error, calledFromCmeThread:%d", calledFromCmeThread);
        CME_PRINT_REPORT("\r\nti_driver_ext_set_CROC ,WARNING ! device role down , exit with error, calledFromCmeThread:%d\r\n", calledFromCmeThread);
        ret = -1;
        goto out;
    }
out:
    osi_LockObjUnlock(&extAppLockObj);
    return ret;
}

int Wlan_RoleDown_from_CME_thread(WlanRole_e roleType, unsigned long int timeout)
{
    uint32_t role_bitmap;
    int32_t ret = 0;
    uint8_t calledFromCmeThread = 1;

    HOOK(HOOK_WLAN_IF);

#ifndef TI_STA_ONLY_BUILD
    if(roleType == WLAN_ROLE_AP)
    {
        ret = set_cond_in_process_wlan_ap_roledown();
    }
    else
#endif
    {
        ret = set_cond_in_process_wlan_sta_roledown();
    }
    if(ret != OSI_OK)
    {
        CME_PRINT_REPORT("\n\r ---device roleDown_from_CME_thread - retry---");
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);//not call to fail in purpose
    }

    CME_PRINT_REPORT("\n\r ---device roleDown_from_CME_thread---");

    role_bitmap = CME_GetStartedRoleBitmap();


    if (ROLE_IS_TYPE_STA(roleType))
    {
        role_bitmap &= ~(uint32_t)BIT_x(ROLE_STA);

        ret = CME_WlanSetMode(calledFromCmeThread,role_bitmap, timeout, 0);
    }
    else if (ROLE_IS_TYPE_AP(roleType))
    {
        role_bitmap &= ~(uint32_t)BIT_x(ROLE_AP);

        ret = CME_WlanSetMode(calledFromCmeThread,role_bitmap, timeout, 0);
    }
    else if (ROLE_IS_TYPE_TRANSCEIVER(roleType))
    {
        if (0 == (role_bitmap & BIT_x(ROLE_TRANSCEIVER)))
        {
            ret = -1;
            goto fail;
        }

        ret = ctrlCmdFw_pltStop();
        if (ret < 0)
        {
            goto fail;
        }

        role_bitmap &= ~(uint32_t)BIT_x(ROLE_TRANSCEIVER);

        CME_SetStartedRoleBitmap(role_bitmap);
        role_bitmap = CME_GetStartedRoleBitmap();

    }
    else if (ROLE_IS_TYPE_DEVICE(roleType))
    {
        role_bitmap &= ~(uint32_t)BIT_x(ROLE_DEVICE);

        ret = CME_WlanSetMode(calledFromCmeThread,role_bitmap, timeout, 0);
        if (ret < 0)
        {
            goto fail;
        }
    }
    HOOK(HOOK_WLAN_IF);
#ifndef TI_STA_ONLY_BUILD
    if(roleType == WLAN_ROLE_AP)
    {
        set_finish_wlan_ap_roledown();
    }
    else
#endif
    {
        set_finish_wlan_sta_roledown();
    }
    return ret;

    fail:
#ifndef TI_STA_ONLY_BUILD
        if(roleType == WLAN_ROLE_AP)
        {
            set_finish_wlan_ap_roledown();
        }
        else
#endif
        {
            set_finish_wlan_sta_roledown();
        }
        return ret;
}

int CME_CancelRemainOn_from_CME_thread(uint8_t is_croc_performed_due_to_timeout )
{
	int32_t rc;
	Cme_Users_e deviceFlow_GetCurrentUser= CmeDeviceFlow_GetCurrentUser();
	CME_CON_PRINT("\n\rCME :got msg CME_MESSAGE_ID_EXT_CROC : is_croc_performed_due_to_timeout :%d",
			is_croc_performed_due_to_timeout);
	if(is_croc_performed_due_to_timeout)
	{
		deviceFlow_GetCurrentUser = CME_DEVICE_ROC_TIMEOUT;
	}

	rc = CmeDeviceFlowSM(CME_DEVICE_CROC, deviceFlow_GetCurrentUser);
	return rc;
}
/* ----------------------------------------------------------------------------
 ti_driver_ext_tx_send_action
      This function sends an action frame to LTXP  direct from the application.
      It is for applications that want to make the P2P provision by themselves

 Parameters:    apPriv - pointer to private driver DB

 Return code:   0 - OK, -1 - failure
---------------------------------------------------------------------------- */
int ti_driver_ext_tx_send_action(
                            const uint8_t  *apDst,            // Destination address
                            const uint8_t *actionBuff,
                            uint32_t       actionBuffLen)
{

    ti_driver_ifData_t     *pDrv;
    struct wpa_supplicant *wpa_s = NULL;
    uint32_t roleId;
    struct ieee80211_mgmt  mgmt;
    uint8_t *apSrc;
    int32_t freq;
    uint32_t aWaitTime ;//ms
    int32_t ret = 0;
    uint8_t* apBssid;


    osi_LockObjLock(&extAppLockObj, OSI_WAIT_FOREVER);

    if(!isextDPP())
    {
        GTRACE(GRP_CME,"ERROR ! ti_driver:  ti_driver_ext_tx_send_action ,ext is not enabled");
        CME_PRINT_REPORT("\r\nERROR ! ti_driver:  ti_driver_ext_tx_send_action ext is not enabled");
        ret = -1;
        goto out;
    }
    roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_DEVICE);

    if(roleId == ROLE_ID_NONE)
    {
        GTRACE(GRP_CME,"ERROR ! ti_driver:  ti_driver_ext_tx_send_action role device doesn't exists");
        CME_PRINT_REPORT("\r\nERROR ! ti_driver:  ti_driver_ext_tx_send_action role device doesn't exists");
        ret = -1;
        goto out;
    }

    GTRACE(GRP_CME,"ti_driver: Send action from  external  to role id :%d",roleId);
    CME_PRINT_REPORT("\n\rti_driver: Send action from  external  to role id :%d",roleId);


    wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);

    //role was not enabled
    if(wpa_s == NULL )
    {
        GTRACE(GRP_CME,"ERROR ! Send ext action frame to role id :%d which is not enabled",roleId);
        CME_PRINT_REPORT("\r\n ERROR ! Send ext action frame to role id :%d which is not enabled",roleId);
        ret = -1;
        goto out;
    }

    pDrv = wpa_s->drv_priv;
    if(pDrv == NULL )
    {
        GTRACE(GRP_CME,"ERROR ! Send action frame to role id :%d pDrv is NULL",roleId);
        CME_PRINT_REPORT("\r\n ERROR ! Send action frame to role id :%d pDrv is NULL",roleId);
        ASSERT_GENERAL(0);// this scenario not suppose to happen
        ret = -1;
        goto out;
    }

    if(!pDrv->roleStarted)
    {
        GTRACE(GRP_CME,"ERROR ! role was not started, role id :%d pDrv is NULL",roleId);
        CME_PRINT_REPORT("\r\n ERROR ! role was not started,  role id :%d pDrv is NULL",roleId);
        ASSERT_GENERAL(0);// this scenario not suppose to happen
        ret = -1;
        goto out;
    }

    ret = CME_sendActionFrameNotify( pDrv,
                                     apDst,         // Destination address
                                     actionBuff,
                                     actionBuffLen);

    out:
        osi_LockObjUnlock(&extAppLockObj);
        return ret;
}

/* ----------------------------------------------------------------------------
ti_driver_one_shot_scan
                    This function is prepares and sends a scan command
                    to the scan module via the transport bus
                    This function also build the info elements for probe
                    request, fill the channel list (reg domain), and
                    the SSID list. this function is handler for ONE_SHOT
                    scan.


Parameters:    apPriv - pointer to private driver DB
               apParams - Pointer to scan configuration
                                    (set by supplicant)
Return code:   0 - parameters OK, -1 - error indication
---------------------------------------------------------------------------- */
int ti_driver_one_shot_scan(void *apPriv, struct wpa_driver_scan_params *apParams)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();
    int32_t ret = set_cond_in_process_wlan_one_shot_scan();

    if (ret == OSI_OK)
    {
        ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

        if (pDrv->ops->one_shot(apPriv, apParams) == OSI_OK)
        {
            CME_PRINT_REPORT("\n\rti_driver: start one shot timer");
            CME_start_one_shot_scan_timer();
        }
        else
        {
            CME_PRINT_REPORT("\n\rti_driver: starting one shot scan failed");
            CmeScan_ScanDone(SCAN_REQUEST_ONE_SHOT, pCmeScanDB->roleId, pCmeScanDB, CME_SCAN_STATUS_FAILED, 0, 0);
            return -1;
        }
    }
    else
    {
        GTRACE(GRP_DRIVER_CC33_DEBUG, "ti_driver: one shot scan failed to start");
        CME_PRINT_REPORT("\n\rti_driver: one shot scan failed to start");
        return -1;
    }
    return ret;
} // ti_driver_one_shot_scan


/* ----------------------------------------------------------------------------
 ti_driver_get_scan_results
      This API is used by supplicant to get last scan detected networks.

 Parameters:  apPriv - pointer to private driver DB
 Return:      pointer to networks list; memory is allocated here and released
              by supplicant after results are taken.
---------------------------------------------------------------------------- */
struct wpa_scan_results * ti_driver_get_scan_results(void *apPriv)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    Bool_e is_fast_connect = (CME_STA_FAST_CONNECT_USER == CmeStationFlow_GetCurrentUser());
    uint32_t i;
    uint32_t numCandidates = gCandidatesInfo.numCandidates;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    struct wpa_scan_results *pSupplicantResults = NULL;

    GTRACE(GRP_DRIVER_CC33, "Num connection candidates %d, is fast connection %d, num BSS in priority list %d",
                            numCandidates, is_fast_connect, pDrv->wpa_s->num_bss);

    // clear previous scan results from supplicant DB
    // in order to force supplicant to select a new result for the new connection.
    wpa_bss_flush(pDrv->wpa_s);

    // Note: this API must allocate memory and return a valid wpa_scan_results
    // to supplicant even if scan results list is empty. Otherwise, a periodic
    // scan shall not be triggered !!!
    pSupplicantResults = (struct wpa_scan_results *)os_zalloc(sizeof(struct wpa_scan_results));
    if (!pSupplicantResults)
    {
        //ASSERT_GENERAL(NULL != pSupplicantResults); //TODO: Debug
        GTRACE(GRP_DRIVER_CC33, "Failed to allocate wpa_scan_results");
        return (NULL);
    }

    if (numCandidates)
    {
        pSupplicantResults->res = (struct wpa_scan_res **)os_zalloc(numCandidates * sizeof(struct wpa_scan_res *));
        if (!pSupplicantResults->res)
        {
            os_free (pSupplicantResults);
            //ASSERT_GENERAL(NULL != pSupplicantResults->res); //TODO: Debug
            GTRACE(GRP_DRIVER_CC33, "Failed to allocate wpa_scan_res");
            return (NULL);
        }
    }

    if(gCandidatesInfo.pCandidateScanResults == NULL)
    {
        GTRACE(GRP_DRIVER_CC33, "gCandidatesInfo.pCandidateScanResults is NULL");
        os_free (pSupplicantResults->res);
        os_free (pSupplicantResults);
        return NULL;
    }

    // Scan results are stored in supplicant format. Still they need to be
    // copied to a new allocated buffer since supplicant frees the scan results
    // after handling.
    // Note: supplciant code could be changed to avoid this free operation.
    for (i=0 ; i<numCandidates ; ++i)
    {
        uint32_t allocSize;
        struct wpa_scan_res *pRes;

        // --------------------------------------------------------------------
        // TODO: Debug code, remove after integrating scan full path
        uint8_t* pIe;
        char ssid[SSID_MAX_LEN];
        char macStr[MAC_STR_LEN];

        memset(ssid, 0, SSID_MAX_LEN);
        // Debug code, remove after integrating scan full path
        // --------------------------------------------------------------------

        // Scan result needs to be copied here since supplicant frees scan result
        // memory after using it for selecting his candidate
        allocSize = sizeof(struct wpa_scan_res);
        allocSize += gCandidatesInfo.pCandidateScanResults[i].mScanResult.ie_len;
        allocSize += gCandidatesInfo.pCandidateScanResults[i].mScanResult.beacon_ie_len;
        pRes = os_zalloc(allocSize);

        if (!pRes)
        {
            ASSERT_GENERAL(NULL != pRes); //TODO: Debug
            break; //The following allocations will probably also fail so no need to continue (in case we will remove the ASSERT_GENERAL)
        }

        // Copy the basic scan result stucture
        memcpy(pRes, &gCandidatesInfo.pCandidateScanResults[i].mScanResult, sizeof(struct wpa_scan_res));

        // Copy extra IEs
        pIe = (uint8_t *)(pRes + 1);
        memcpy(pIe, gCandidatesInfo.pCandidateScanResults[i].mInfoElements, allocSize - sizeof(struct wpa_scan_res));
        pSupplicantResults->res[i] = pRes;

        // --------------------------------------------------------------------
        // TODO: Debug code, remove after integarting scan full path
        pIe = (uint8_t *)(pSupplicantResults->res[i] + 1);
        memcpy(ssid, &pIe[2], pIe[1]);
        GET_MAC_STR(pSupplicantResults->res[i]->bssid, macStr);
        GTRACE(GRP_DRIVER_CC33, "ssid %s bssid %s ie len %d beacon ie len %d", ssid, macStr,
                                 pSupplicantResults->res[i]->ie_len,
                                 pSupplicantResults->res[i]->beacon_ie_len);

        utilsDumpScanResult(pSupplicantResults->res[i]);

        // Debug code, remove after integarting scan full path
        // --------------------------------------------------------------------

        ++pSupplicantResults->num;

    } // for all available candidates

    //fast connect store in global buffers for possible file system storage in successful connection
    //we are expecting only one result on profile search that is fast-connect candidate
    if ((FALSE == is_fast_connect) && (gCandidatesInfo.numCandidates > 0) && (!CME_IsOngoingWPSAdHocConnection())) //In WPS, the candidate is also not relevant for fast connect
    {
        cmeUpdateCacheFastConnectionApScanData(&gCandidatesInfo.pCandidateScanResults[0]); //In case we are here we are supposed to have only 1 candidate and it is the first one.
    }

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    return pSupplicantResults;
} // ti_driver_get_scan_results

/* ----------------------------------------------------------------------------
ti_driver_sched_scan
                    Configure and start periodic scan.
                    This function is prepares and sends a scan command
                    to the scan module via the transport bus
                    This function also build the info elements for probe
                    request, fill the channel list (reg domain), and
                    the SSID list. this function is handler for
                    PERIODIC_SCAN


Parameters:    apPriv - pointer to private driver DB
               apParams - Pointer to scan configuration
                                    (set by supplicant)
Return code:   0 - parameters OK, -1 - error indication
---------------------------------------------------------------------------- */
int ti_driver_sched_scan(void *apPriv, struct wpa_driver_scan_params *apParams)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();
    int32_t ret = set_cond_in_process_wlan_periodic_scan();

    if (ret == OSI_OK)
    {
        ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

        if (pDrv->ops->sched_scan(apPriv, apParams) == OSI_OK)
        {
            CME_start_periodic_scan_timer();
            return 0;
        }
        else
        {
            CME_PRINT_REPORT("\n\rti_driver: starting periodic scan failed");
            CmeScan_ScanDone(SCAN_REQUEST_CONNECT_PERIODIC_SCAN, pCmeScanDB->roleId, pCmeScanDB, CME_SCAN_STATUS_FAILED, 0, 0);
            return -1;
        }
    }
    else
    {
        GTRACE(GRP_DRIVER_CC33_DEBUG, "scheduled scan failed to start");
        CME_PRINT_REPORT("\n\rscheduled scan failed to start");
        return -1;
    }
} // ti_driver_one_shot_scan


/* ----------------------------------------------------------------------------
ti_driver_stop_sched_scan
                    Stop a periodic scan; command is handled in WLAN
                    services context, when completed a
                    CME_MESSAGE_ID_SCAN_COMPLETE message is pushed
                    to CME queue.

Parameters:    apPriv - pointer to private driver DB

Return code:   0 - parameters OK, -1 - error indication
---------------------------------------------------------------------------- */
int ti_driver_stop_sched_scan(void *apPriv)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    GTRACE(GRP_DRIVER_CC33_DEBUG, "Scan stop cmd: scanning %d, sched_scanning %d", pDrv->wpa_s->scanning, pDrv->wpa_s->sched_scanning);

    return (pDrv->ops->send_scan_stop(pDrv->roleId, SCAN_REQUEST_CONNECT_PERIODIC_SCAN, FALSE));
} // ti_driver_stop_sched_scan


int ti_driver_abort_scan(void *apPriv, uint64_t scan_cookie)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    //not implemented
    GTRACE(GRP_DRIVER_CC33_DEBUG, "ti_driver: abort scan");

    // fix - issue OSPREY_LDB-2587
    if (ROLE_IS_TYPE_DEVICE(pDrv->roleType))
    {
        //cancel scan work if pending
        if (radio_work_pending(pDrv->wpa_s, "p2p-scan"))
        {
            GTRACE(GRP_DRIVER_CC33_DEBUG, "Pending p2p-scan work - Remove it...");

            radio_remove_works(pDrv->wpa_s, "p2p-scan", 0);
        }
    }

    return(0);
}

/* ----------------------------------------------------------------------------
 ti_driver_start_remain_on_channel
        This function sends a ti_driver_remain_on_channel() request to WLAN services
        and blocks until command handling is completed.
        Only called by supplicant.

 Parameters:    apPriv - pointer to private driver DB
                aFreq - indicates the channel to remain on
                aDuration - time to remain on channel.


 Return code:   0 - OK, role found -1 - else
---------------------------------------------------------------------------- */
int ti_driver_start_remain_on_channel(void *apPriv, unsigned int aFreq, unsigned int aDuration)
{
    int32_t ret = 0;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    g_offChannelDev.RocInitiateExplicitly = TRUE;
    wpa_printf(MSG_INFO, "ti_driver: remain_on_channel called by supplicant");
    ret = ti_driver_remain_on_channel(pDrv, aFreq, aDuration);
    return(ret);
}


/* ----------------------------------------------------------------------------
 ti_driver_remain_on_channel
      This function sends a ROC request to WLAN services and blocks until
      command handling is completed.

 Parameters:    apPriv - pointer to private driver DB
                aFreq - indicates the channel to remain on
                aDuration - time to remain on channel, unused. See note below.
                aDuration = 0xFFFFFFFF(CC33_ROC_ENDLESS_TIMOUT) means endless ROC with no timer

 Return code:   0 - OK, role found -1 - else
---------------------------------------------------------------------------- */

int ti_driver_remain_on_channel(void *apPriv, uint32_t aFreq, uint32_t aDuration)
{
    int32_t ret = 0;
    uint8_t notifySupp = 0;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    wpa_printf(MSG_DEBUG, "ti_driver: Remain on channel Freq %d duration = %d (roleid %d) RocInitiateExplicitly = %d",
            aFreq, aDuration, pDrv->roleId, g_offChannelDev.RocInitiateExplicitly);

    CME_CON_PRINT("\n\rti_driver: Remain on channel Freq %d duration = %d (roleid %d) RocInitiateExplicitly = %d",
            aFreq, aDuration, pDrv->roleId, g_offChannelDev.RocInitiateExplicitly);

    //wpa_printf(MSG_ERROR, "ti_driver: lock2");
    osi_LockObjLock(&g_offChannelDev.p_remain_channel_mutex , OSI_WAIT_FOREVER);
    g_offChannelDev.off_channel_duration = aDuration;
    g_offChannelDev.off_channel_freq = aFreq;

    if(ROLE_IS_TYPE_AP_BASED_OR_DEVICE(pDrv->roleType) &&
           (pDrv->capa.flags & WPA_DRIVER_FLAGS_OFFCHANNEL_TX))// &&
               /* ((int) aFreq != pDrv->freq))*/
    {
       //if there is already device active -- use it
       if(pDrv->roleStarted == 0) // role device is not started
       {
           //start device and perform remain on channel
            if(startDevOffchannelRole(pDrv, aFreq) < 0)
            {
                wpa_printf(MSG_ERROR, "ti_driver: Remain on channel, start_dev failed! (Freq %d)", aFreq);
                CME_CON_PRINT_ERROR("\n\rERROR:ti_driver: Remain on channel, start_dev failed! (Freq %d)", aFreq);
                ASSERT_GENERAL(0);
                ret = -1;
                goto out;

            }
            CME_CON_PRINT("\n\rti_driver: Remain on channel, start_dev role (Freq %d)", aFreq);
       }
       
       if(g_offChannelDev.off_channel_mgmt_datalen > 0)//there is mgmt packet to send
       {
           //event TX_STATUS back to the suppplicant for the mgmt packet is send from the function
           //drv_handleTxResult
           wpa_printf(MSG_DEBUG, "ti_driver ti_send_mgmt_frame for the device!");
           ret = ti_send_mgmt_frame((void *)pDrv,
                   g_offChannelDev.p_off_channel_mgmt_data,(size_t)g_offChannelDev.off_channel_mgmt_datalen);
           if(ret < 0)
           {
               wpa_printf(MSG_ERROR, "ti_driver ti_send_mgmt_frame for DEVICE role failed!");
               ASSERT_GENERAL(0);
               ret = -1;
               goto error_off_channel;
           }
           g_offChannelDev.off_channel_mgmt_datalen = 0;
       }

    }
    else
    {
       if(pDrv->ops->remain_on_channel(apPriv, aFreq) < 0)
       {
           ASSERT_GENERAL(0);
           ret = -1;
           goto out;
       }

    }

    g_remain_on_channel_apPriv = apPriv;

    pDrv->pRemainOnChannelDuration = aDuration;

    notifySupp = 1;

   if((aDuration > 0) && (aDuration!= CC33_ROC_ENDLESS_TIMOUT))//aDuration = CC33_ROC_ENDLESS_TIMOUT means endless ROC with no timer
   {
       if(!g_offChannelDev.off_channel_dev_timer_was_set)
       {
           //set timer to cancel roc
           g_offChannelDev.off_channel_dev_timer_was_set = 1;
           wpa_printf(MSG_ERROR, "ti_driver: start timer Remain on channel! (Freq %d)", aFreq);
           osi_TimerCreate(&(pDrv->pRemainOnChannelTimer), "remain_on_channel timeout", ti_driver_cancel_remain_on_channel_timer_callback, NULL);
           ret = osi_TimerStart(&(pDrv->pRemainOnChannelTimer), pDrv->pRemainOnChannelDuration, FALSE);
           if(ret < 0)
           {
               CME_CON_PRINT_ERROR("\n\rti_driver: roc timer started failed");
           }
       }
       else
       {
           wpa_printf(MSG_WARNING, "timer for cancel remain on channel was already set!");

       }
   }

   if(ret == 0)
   {
       goto out;
   }
   error_off_channel:
      wpa_printf(MSG_ERROR, "ti_send_mgmt_frame error ! error_off_channel!");
      stopDevOffchannelRole(pDrv);
   out:
     g_offChannelDev.off_channel_mgmt_datalen = 0; //no packet is waiting to be send
     //wpa_printf(MSG_ERROR, "ti_driver: unlock2");
     osi_LockObjUnlock(&g_offChannelDev.p_remain_channel_mutex);

    //to send event to supplicant if roc initiated by supplicant
    if ((notifySupp) && (g_offChannelDev.RocInitiateExplicitly == TRUE))
    {
        if(!isextDPP())
        {
            drv_handleRemainOnChannelEvent(pDrv, 1, pDrv->pRemainOnChannelDuration, aFreq);
        }
    }

    if ((g_offChannelDev.off_channel_dev_timer_was_set == FALSE) && ((aDuration!= CC33_ROC_ENDLESS_TIMOUT)))
    {
        wpa_printf(MSG_DEBUG, "the duration is 0 -> we want to cancel roc, since we didn't set timer");
        ret = ti_driver_cancel_remain_on_channel(apPriv);
        wpa_printf(MSG_DEBUG, "ti_driver_cancel_remain_on_channel = %d", ret);
    }

   return ret;
}

void ti_driver_cancel_remain_on_channel_timer_callback()
{
    //send message to CME to cancel timer and CROC
    //from CME we calling to ti_driver_cancel_remain_on_channel_timer_callback_handle()
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)g_remain_on_channel_apPriv;
    CME_PRINT_ROC_REPORT("\n\rti_driver, cancel_remain_on_channel_timer_callback");
    CME_RemainOnChannelTimeoutNotify(pDrv->roleId);
  
}

/* ----------------------------------------------------------------------------
 ti_driver_cancel_remain_on_channel_timer_callback_handle
      This function handles a callback timer of remain_of_channel
      Called from CME

 Parameters:    0

 Return code:   0
---------------------------------------------------------------------------- */

void ti_driver_cancel_remain_on_channel_timer_callback_handle()
{

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)g_remain_on_channel_apPriv;
    if (g_remain_on_channel_apPriv == NULL)
    {
        wpa_printf(MSG_INFO, "timer event - ti_driver_cancel_remain_on_channel : g_remain_on_channel_apPriv is NULL");
        return;
    }
    wpa_printf(MSG_INFO, "timer - ti_driver_cancel_remain_on_channel : timeout, roleid=%d, roc_started=%d, RocInitiateExplicitly=%d", 
                        pDrv->roleId, pDrv->offChannel_roc_started, g_offChannelDev.RocInitiateExplicitly);

    CME_PRINT_ROC_REPORT("\r\ntimer - ti_driver_cancel_remain_on_channel : timeout, roleid=%d, roc_started=%d, RocInitiateExplicitly=%d",
                        pDrv->roleId, pDrv->offChannel_roc_started, g_offChannelDev.RocInitiateExplicitly);

    //if roc is started, we need to cancel roc (FW CROC) and stop device role
    if (pDrv->offChannel_roc_started)
    {
        ti_driver_cancel_remain_on_channel(g_remain_on_channel_apPriv);
    }

    //and if roc was started by supplicant send croc event
    if (g_offChannelDev.RocInitiateExplicitly == TRUE)
    {
        if(!isextDPP()) //notify to supplicant
        {
            //roc initiated by supplicant
            drv_handleRemainOnChannelEvent(pDrv, 0, g_offChannelDev.off_channel_duration, g_offChannelDev.off_channel_freq);
        }
        g_offChannelDev.RocInitiateExplicitly = FALSE;
    }

    g_remain_on_channel_apPriv = NULL;//not needed anymore
}


/* ----------------------------------------------------------------------------
 ti_driver_stop_remain_on_channel
      This function sends a ti_driver_cancel_remain_on_channel to WLAN services
      Called by supplicant

 Parameters:    apPriv - pointer to private driver DB

 Return code:   0
---------------------------------------------------------------------------- */
int ti_driver_stop_remain_on_channel(void *apPriv)
{
    g_offChannelDev.RocInitiateExplicitly = FALSE;
    wpa_printf(MSG_INFO, "ti_driver: cancel_remain_on_channel called by supplicant");
    return(ti_driver_cancel_remain_on_channel(apPriv));

}

/* ----------------------------------------------------------------------------
 ti_driver_cancel_remain_on_channel
      This function sends a CROC request to WLAN services, we don't wait for
      command completion. When function returns CROC command wasn't actually
      handled.

 Parameters:    apPriv - pointer to private driver DB

 Return code:   0
---------------------------------------------------------------------------- */
int ti_driver_cancel_remain_on_channel(void *apPriv)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    Channel_e chan;
    uint8_t/*RadioBand_e*/ band;

    //wpa_printf(MSG_ERROR, "ti_driver: lock3");
    osi_LockObjLock(&g_offChannelDev.p_remain_channel_mutex , OSI_WAIT_FOREVER);

    wpa_printf(MSG_INFO, "ti_driver: cancel_remain_on_channel (roc started=%d, roleid=%d, drvFreq=%d, RocInitiateExplicitly=%d)",
                        pDrv->offChannel_roc_started,
                        pDrv->roleId,
                        pDrv->freq,
                        g_offChannelDev.RocInitiateExplicitly
                        );

    //if the call to cancel remain initate by timer
    if((pDrv->pRemainOnChannelTimer.osTimerHandler != NULL) 
        && ( g_offChannelDev.off_channel_dev_timer_was_set))
    {
        CME_PRINT_ROC_REPORT("\n\rti_driver, cancel_remain_on_channel,osi_TimerStop");
        osi_TimerStop(&pDrv->pRemainOnChannelTimer);
        osi_TimerDelete(&pDrv->pRemainOnChannelTimer);
        g_offChannelDev.off_channel_dev_timer_was_set = 0;
        pDrv->pRemainOnChannelTimer.osTimerHandler = NULL;
        wpa_printf(MSG_INFO, "ti_driver_cancel_remain_on_channel: cancel timer");
       
    }
    // if roc was started - send croc to FW
    if (pDrv->offChannel_roc_started)
    {
        if(pDrv->ops->cancel_remain_on_channel(pDrv) < 0)
        {
            ASSERT_GENERAL(0);
            return -1;
        }
        pDrv->offChannel_roc_started = 0;
    }

    //if the cancel is for off-channel device
    if(ROLE_IS_TYPE_AP_BASED_OR_DEVICE(pDrv->roleType) &&
            (pDrv->capa.flags & WPA_DRIVER_FLAGS_OFFCHANNEL_TX) && pDrv)
    {
       wpa_printf(MSG_INFO, "ti_driver_cancel_remain_on_channel stopDevOffchannelRole");
       stopDevOffchannelRole(pDrv);
    }
    osi_LockObjUnlock(&g_offChannelDev.p_remain_channel_mutex);

    return 0;
} // ti_driver_cancel_remain_on_channel


/* ----------------------------------------------------------------------------
 ti_driver_probe_req_report
    This command can be used to request the driver to indicate when     
    Probe Request frames are received with EVENT_RX_PROBE_REQ events
    But driver may disable Probe Request reporting at least in station mode

 Parameters:    apPriv - pointer to private driver DB
                aReport - Whether to report on received Probe Requests Frames

 Return code:   0 - OK, role found -1 - else
---------------------------------------------------------------------------- */
int ti_driver_probe_req_report(void *apPriv, int aReport)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    CME_PRINT_ROC_REPORT("\n\rMsg from supplicant wait or stop-wait for probe_req. IsToWait %d (role %d)",
            aReport, pDrv->roleId);

    pDrv->p2pReportProbeRequestRx = aReport;
    
    return 0;
}

/* ----------------------------------------------------------------------------
 ti_driver_if_add


 Parameters:    apPriv - pointer to private driver DB
                

 Return code:   0 - OK, role found -1 - else
---------------------------------------------------------------------------- */
int ti_driver_if_add(void *apPriv, enum wpa_driver_if_type type,
                    const char *ifname, const u8 *addr, void *bss_ctx,
                    void **drv_priv, char *force_ifname, u8 *if_addr,
                    const char *bridge, int use_existing, int setup_ap)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    uint8_t pAddress[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    CME_PRINT_REPORT("\n\rti_driver: Add new interface: type = %d, ifname=%s, force_ifname: %s, drvRoleid=%d",
                type, ifname, force_ifname, pDrv->roleId);
    switch(type)
    {
        case WPA_IF_AP_BSS:
        case WPA_IF_AP_VLAN:
            os_strlcpy(force_ifname, NETIF_NAME(TIWLAN_DEV_NAME_SAP), IFNAMSIZ);
            break;

        case WPA_IF_P2P_GO:
        {
            /* p2p Autonomous GO will take AP MAC Address */
            trnspt_cmd_get_mac_addr(pAddress, ROLE_AP);
            IRQ_UtilCopyMacAddress(pAddress, if_addr);
            os_strlcpy(force_ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2P_GO), IFNAMSIZ);
        }
        break;
        case WPA_IF_P2P_CLIENT:
        {
            trnspt_cmd_get_mac_addr(pAddress, ROLE_AP);
            IRQ_UtilCopyMacAddress(pAddress, if_addr);
            os_strlcpy(force_ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2P_CL), IFNAMSIZ);
        }
        break;
        case WPA_IF_P2P_GROUP:
        {
            /* we need the p2p-group interface up to get its mac addr */
            trnspt_cmd_get_mac_addr(pAddress, ROLE_AP);
            IRQ_UtilCopyMacAddress(pAddress, if_addr);
            os_strlcpy(force_ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2P), IFNAMSIZ);
        }
            break;
        case WPA_IF_P2P_DEVICE:
            os_strlcpy(force_ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2PDEV), IFNAMSIZ);
            CME_PRINT_REPORT("\n\rti_driver: force_ifname to use: %s", force_ifname);
            break;
        case WPA_IF_STATION:
            os_strlcpy(force_ifname, NETIF_NAME(TIWLAN_DEV_NAME_STA), IFNAMSIZ);
            break;
        default:
            GTRACE(GRP_GENERAL_ERROR, "ERROR in adding an unknown if type: %d, ifname=%s", type, ifname);
            return -1;
    }

    return 0;
}
/* ----------------------------------------------------------------------------
 ti_send_mgmt_frame
      This function sends a management packet directly to data path
      The wlan header will be constructed by the ltxp layer. The payload is taken as is from the supplicant.

 Parameters:    apPriv - pointer to private driver DB
                apData - pointer to 802.11 header of the packet
                aDataLen - packet length including 802.11 header

 Return code:   0 on success, -1 on failure (illegal parameters)
---------------------------------------------------------------------------- */
int ti_send_mgmt_frame(void *apPriv,
                       const uint8_t *apData,
                       size_t aDataLen)
{

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    TMgmtPktDesc        *pMgmtPkt;
    uint32_t            dataLen,total_len, total_len_aligned,extraHThdr;
    dot11_mgmtHeader_t* pDot11Header;
    uint8_t*            dst_addr;
    uint32_t            uNetIfId = 0;
    uint16_t            fc;
    int32_t             status = 0;
    uint32_t            link;
    uint8_t             SecureHdrLength = 0;
    txCtrl_t           *pTxCtrl = gTxCtrlCB;

    struct ieee80211_mgmt* pPayload = (struct ieee80211_mgmt *) apData;
    uint16_t stype = (pPayload->frame_control >> 4) & 0xF;

    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: NULL driver pointer");
        ASSERT_GENERAL(0);
        status = -1;
        goto fail;
    }

    {//logs

        //reduce number of log msgs
        if((pPayload->frame_control != IEEE80211_FC(WLAN_FC_TYPE_MGMT, WLAN_FC_STYPE_PROBE_REQ))
                &&(pPayload->frame_control != IEEE80211_FC(WLAN_FC_TYPE_MGMT, WLAN_FC_STYPE_PROBE_RESP)))
        {
            if(stype == WLAN_FC_STYPE_ASSOC_RESP)
            {
                CME_PRINT_REPORT("\n\rti_send_mgmt_frame, send_mlme WLAN_FC_STYPE_ASSOC_RESP");
            }
            if(stype == WLAN_FC_STYPE_ACTION)
            {
                CME_PRINT_REPORT("\n\rti_send_mgmt_frame, send_mlme WLAN_FC_STYPE_ACTION roleType:%d aDataLen:%d category:%d action :%d",
                        pDrv->roleType,
                        (uint32_t)aDataLen,
                        pPayload->u.action.category,
                        pPayload->u.action.u.public_action.action);
            }
            else
            {
                CME_PRINT_REPORT("\n\rti_send_mgmt_frame, send_mlme fc:0x%x roleType:%d aDataLen:%d ",
                        pPayload->frame_control>>4,pDrv->roleType, (uint32_t)aDataLen);
                //frame_control see : IEEE80211_FC(WLAN_FC_TYPE_MGMT, WLAN_FC_STYPE_AUTH);
            }
        }
    }

    if (aDataLen < WLAN_HDR_LEN)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: Bad len");
        CME_PRINT_REPORT_ERROR("\n\rERROR: Bad len");
        ASSERT_GENERAL(0);
        status = -1;
        goto fail;
    }

    extraHThdr = IEEE80211_HT_CTL_LEN;
    dst_addr = ((struct ieee80211_mgmt *) apData)->da;

    if(ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
    {
        uNetIfId = TIWDRV_NETIF_ID_STA;
    }
    else if(ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
        uNetIfId = TIWDRV_NETIF_ID_SAP;
    }
    else if(ROLE_IS_TYPE_DEVICE(pDrv->roleType))
    {
        uNetIfId = TIWDRV_NETIF_ID_P2PDEV;
    }
    else
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR:unvalid role type : %d", pDrv->roleType);
        ASSERT_GENERAL(0);
    }

    link = udataNet_GetTxMgmtLink(uNetIfId, (uint8_t *)dst_addr);

    if (INVALID_LINK == link)
    {
        GTRACE(GRP_DRIVER_CC33, "ti_driver_send_l2_data: No valid hlid was found!  NetifId = %d", link);
        CME_PRINT_REPORT_ERROR("\n\rERROR !!!rti_driver_send_l2_data: No valid hlid was found!  NetifId = %d\n\r", link);
        status = -1;
        goto fail;
    }
     //CME_PRINT_REPORT("\n\rti_driver:  roleType:%d hlid:%d  NetifId:%d\n\r", pDrv->roleType,link,uNetIfId);

    if( (pTxCtrl->aEncryptMgmt[link]) &&
        ((stype == WLAN_FC_STYPE_DISASSOC) ||
         (stype == WLAN_FC_STYPE_DEAUTH) ||
         ((stype == WLAN_FC_STYPE_ACTION || stype == WLAN_FC_STYPE_ACTION_NO_ACK) &&
          pPayload->u.action.category != WLAN_ACTION_PUBLIC)) )
    {
        SecureHdrLength = RSN_SEC_LEN;
        CME_PRINT_REPORT_ERROR("\n\rti_send_mgmt_frame stype %d encrypted for link %d", stype, link);
    }

    extraHThdr += SecureHdrLength;
    /* allocate descriptor and payload */
    dataLen = aDataLen - WLAN_HDR_LEN;
    total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + sizeof(dot11_mgmtHeader_t) + extraHThdr + ALIGNN_TO_4(dataLen);
    pMgmtPkt = udata_AllocTxMgmtPacket( sizeof(dot11_mgmtHeader_t) + extraHThdr, dataLen, NULL);

    if(!pMgmtPkt)
    {
//        ASSERT_GENERAL(0);
        GTRACE(GRP_DRIVER_CC33, "error !! ti_driver_send_l2_data: allocate MgmtPkt fails");
        CME_PRINT_REPORT_ERROR("\n\rterror !! ti_driver_send_l2_data: allocate MgmtPkt fails");
        status = -1;
        goto fail;
    }
    set_nab_tx_header(pMgmtPkt->nabHeader, total_len );

    pMgmtPkt->link = link;
    pMgmtPkt->ePktType = UDATA_TX_PKT_TYPE_WLAN_MGMT;
    pMgmtPkt->flags |= PKTF_EXTERNAL_CONTEXT;


    /* Set Tx-complete callback for sending back the packet upon completion */
    pMgmtPkt->fTxCompleteCb = (TMgmtPacketCb)CME_TxResult;

    /* copy header and payload to new buffers - the Ethernet header on top of the WLAN header is dropped */
    pDot11Header = (dot11_mgmtHeader_t *) pMgmtPkt->header;

    //copy dot11_mgmtHeader_t from the received packet
    os_memcpy((uint8_t*)pDot11Header, (uint8_t*)apData, WLAN_HDR_LEN);

    fc = pDot11Header->fc ;
    if (pDrv->pAuthInfo) //else it means that auth was not allocate yet
    {
        if (pDrv->pAuthInfo->authType)//if authentication is not open
        {
            fc |= DOT11_FC_WEP;
            pMgmtPkt->flags |= PKTF_ENCRYPT;
        }
    }
    else if (SecureHdrLength)
    {
        fc |= DOT11_FC_WEP;
        pMgmtPkt->flags |= PKTF_ENCRYPT;
    } 

    COPY_WLAN_WORD(&pDot11Header->fc, &fc);

    //copy packet data to the payload
    os_memcpy((uint8_t*)pMgmtPkt->payload, (uint8_t*)apData + WLAN_HDR_LEN, aDataLen - WLAN_HDR_LEN);

    /* submit for tx */
    //GTRACE(GRP_DRIVER_CC33, "udata_SendTxMgmtPacket");
    status = udata_SendTxMgmtPacket(pMgmtPkt);

    return status;//pMgmtPkt is freed by lower layers

 fail:
        return status;
} // ti_send_mgmt_frame

// ============================================================================
//  API for CME commands & notifications
// ============================================================================

// ----------------------------------------------------------------------------
RoleType_e drv_getStaIface(struct wpa_global *apGlobal, struct wpa_supplicant **apIface)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    RoleType_e roleType = ROLE_TYPE_NONE;
    struct wpa_supplicant *wpa_s;
    ti_driver_ifData_t *pDrv;
    // API may be called when there's no active supplicant interface.
    // Expected mainly for irrelevant driver commands, still we shouldn't crush.
    //
    //
    if ((apGlobal==NULL) || (NULL == apGlobal->ifaces))
    {
        CME_PRINT_REPORT_ERROR("\r\nERROR ! apGlobal or apGlobal->ifaces is NULL");
        return ROLE_TYPE_NONE;
    }

    wpa_s = apGlobal->ifaces;
    pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

    if (ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
    {
        roleType = pDrv->roleType;
    }
    else
    // supports 2 roles at most. If first role isn't a STA based role,
    // check if there's another role.
    {
        while (NULL != wpa_s->next)
        {
            wpa_s = wpa_s->next;
            pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

            if (ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
            {
                roleType = pDrv->roleType;
            }
        }
    }

    if (NULL != apIface)
    {
        *apIface = wpa_s;
    }

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    return roleType;
}


RoleType_e drv_getDeviceIface(struct wpa_global *apGlobal, struct wpa_supplicant **apIface)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    RoleType_e roleType = ROLE_TYPE_NONE;
    struct wpa_supplicant *wpa_s;
    ti_driver_ifData_t *pDrv;
    // API may be called when there's no active supplicant interface.
    // Expected mainly for irrelevant driver commands, still we shouldn't crush.
    //
    //
    if ((apGlobal==NULL) || (NULL == apGlobal->ifaces))
    {
        CME_PRINT_REPORT_ERROR("\r\nERROR ! apGlobal or apGlobal->ifaces is NULL");
        return ROLE_TYPE_NONE;
    }
    wpa_s = apGlobal->ifaces;
    pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

    if (ROLE_IS_TYPE_DEVICE(pDrv->roleType))
    {
        roleType = pDrv->roleType;
    }
    else
    // supports 2 roles at most. If first role isn't a STA based role,
    // check if there's another role.
    {
        while (NULL != wpa_s->next)
        {
            wpa_s = wpa_s->next;
            pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

            if (ROLE_IS_TYPE_DEVICE(pDrv->roleType))
            {
                roleType = pDrv->roleType;
            }
        }
    }

    if (NULL != apIface)
    {
        *apIface = wpa_s;
    }

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    return roleType;
}

// ----------------------------------------------------------------------------
struct wpa_supplicant * drv_getIfaceFromRoleID(struct wpa_global *apGlobal, uint32_t aRoleID)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    struct wpa_supplicant *wpa_s;
    ti_driver_ifData_t *pDrv;

    if ((NULL == apGlobal) || (NULL == apGlobal->ifaces))
    {
        return NULL;
    }

    // Go over all valid interfaces and verify netIf is related to a valid one
    wpa_s = apGlobal->ifaces;
    while (NULL != wpa_s)
    {
        pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
        if ((NULL != pDrv) && (aRoleID == pDrv->roleId))
            return wpa_s;

        wpa_s = wpa_s->next;
    }

    return NULL;
}

// ----------------------------------------------------------------------------
int drv_getRoleIdFromType(struct wpa_global *apGlobal,RoleType_e roleType)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    int roleid= ROLE_ID_NONE;
    struct wpa_supplicant *wpa_s;
    ti_driver_ifData_t *pDrv;

    if ((NULL == apGlobal) || (NULL == apGlobal->ifaces))
    {
        return roleid;
    }

    wpa_s = apGlobal->ifaces;
    pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    if (NULL == pDrv)
    {
        return roleid;
    }
    if (roleType == ROLE_STA)
    {
        if (ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
        {
            roleid = pDrv->roleId;
        }
        else
        {
            while (NULL != wpa_s->next)
            {
                wpa_s = wpa_s->next;
                pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
                if (NULL == pDrv)
                {
                    continue;
                }

                if (ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
                {
                    roleid = pDrv->roleId;
                    break;
                }
            }
        }
    }
    else if (roleType == ROLE_AP)
    {
        if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
        {
            roleid = pDrv->roleId;
        }
        else
        {
            while (NULL != wpa_s->next)
            {
                wpa_s = wpa_s->next;
                pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
                if (NULL == pDrv)
                {
                    continue;
                }

                if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
                {
                    roleid = pDrv->roleId;
                    break;
                }
            }
        }
    }
    else if (roleType == ROLE_DEVICE)
    {
        if (ROLE_IS_TYPE_DEVICE(pDrv->roleType))
        {
            roleid = pDrv->roleId;
        }
        else
        {
            while (NULL != wpa_s->next)
            {
                wpa_s = wpa_s->next;
                pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
                if (NULL == pDrv)
                {
                    continue;
                }

                if (ROLE_IS_TYPE_DEVICE(pDrv->roleType))
                {
                    roleid = pDrv->roleId;
                    break;
                }
            }
        }
    }
    else if (roleType == ROLE_P2P_CL)
    {
        if (ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
        {
            roleid = pDrv->roleId;
        }
        else
        {
            while (NULL != wpa_s->next)
            {
                wpa_s = wpa_s->next;
                pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
                if (NULL == pDrv)
                {
                    continue;
                }

                if (ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
                {
                    roleid = pDrv->roleId;
                    break;
                }
            }
        }
    }
    else if (roleType == ROLE_P2P_GO)
    {
        if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
        {
            roleid = pDrv->roleId;
        }
        else
        {
            while (NULL != wpa_s->next)
            {
                wpa_s = wpa_s->next;
                pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
                if (NULL == pDrv)
                {
                    continue;
                }

                if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
                {
                    roleid = pDrv->roleId;
                    break;
                }
            }
        }
    }

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    return roleid;
}

//-----------------------------------------------------------------------------
RoleType_e drv_getRoleTypeFromRoleId(struct wpa_global *apGlobal, uint32_t aRoleID)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);
    struct wpa_supplicant *wpa_s;
    ti_driver_ifData_t *pDrv;

    // Go over all valid interfaces and verify netIf is related to a valid one
    wpa_s = apGlobal->ifaces;
    while (NULL != wpa_s)
    {
        pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
        if (aRoleID == pDrv->roleId)
        {
            return pDrv->roleType;
        }

        wpa_s = wpa_s->next;
    }

    return ROLE_TYPE_NONE;
}

 struct wpa_supplicant* drv_getP2pDeviceSupplicant(void)
{
    uint32_t roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_DEVICE);
    if (roleId == INVALID_ROLE_ID) 
    {
        GTRACE(GRP_CME, "CME: ERROR! No P2P device role");
        return NULL;
    }
    return drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);
}

// ----------------------------------------------------------------------------

void drv_handleScanCompleteEvent(void *apDrv, EScanRequestType aScanType, uint32_t aNumResults)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apDrv;
    union wpa_event_data eventData;

    ASSERT_GENERAL(ROLE_TYPE_NONE != pDrv->roleType);

    os_memset(&eventData, 0, sizeof(eventData.scan_info));

    GTRACE(GRP_DRIVER_CC33, "drv_handleScanCompleteEvent: ScanType=%d, aNumResults=%d", aScanType, aNumResults);

    // For one shot scan, clear the completed scan indication on driver DB
    if (SCAN_REQUEST_ONE_SHOT == aScanType)
    {
        CLEAR_ONE_SHOT_OS_SCAN(pDrv);
    }
    else if (SCAN_REQUEST_CONNECT_PERIODIC_SCAN != aScanType)
    {
        CLEAR_ONE_SHOT_APP_SCAN(pDrv);
    }

    // Event is sent for both
    GTRACE(GRP_DRIVER_CC33, "Report to wpa_supplicant: EVENT_SCAN_RESULTS");
    eventData.scan_info.nl_scan_event = 1; //Normal scan
    wpa_supplicant_event(pDrv->ctx, EVENT_SCAN_RESULTS, &eventData);

    HOOK(HOOK_IN_DRIVER_TI_WIFI);
}

// ----------------------------------------------------------------------------

void drv_handleScanStoppedEvent(void *apDrv)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apDrv;

    GTRACE(GRP_DRIVER_CC33, "Scheduled scan was stopped");
    wpa_supplicant_event(pDrv->ctx, EVENT_SCHED_SCAN_STOPPED, NULL);

    // Nov 23 2015 - force supplicant inactive state as state machine will not be invoked anymore
    wpa_supplicant_set_state(pDrv->wpa_s, WPA_INACTIVE);
}

// ----------------------------------------------------------------------------
void drv_handleOneShotScanStoppedEvent(struct wpa_supplicant *wpa_s,EScanRequestType    scanType)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    if ((wpa_s == NULL) || (wpa_s->drv_priv == NULL))
    {
        return;
    }

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

    // For one shot scan, clear the completed scan indication on driver DB
   if (SCAN_REQUEST_ONE_SHOT == scanType)
   {
       CLEAR_ONE_SHOT_OS_SCAN(pDrv);
   }
   else
   {
       CLEAR_ONE_SHOT_APP_SCAN(pDrv);
   }

   wpa_supplicant_set_state(wpa_s, WPA_INACTIVE);
}
// ----------------------------------------------------------------------------
Bool32 drv_stopConnectionScans(struct wpa_supplicant *wpa_s)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    Bool32 waiting4stop = FALSE;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    EScanRequestType   scanType = SCAN_REQUEST_NONE; // Relevant only for one shot scan

    GTRACE(GRP_DRIVER_CC33_DEBUG, "Scan stop, wpa_state = %d, Scaning = %d, Sched Scaning = %d, gBssTransitionState = %d", 
        wpa_s->wpa_state, wpa_s->scanning, wpa_s->sched_scanning, gBssTransitionState);

    CME_PRINT_SCAN_REPORT("\r\n drv_stopConnectionScans: wpa_state = %d, Scaning = %d, Sched Scaning = %d, gBssTransitionState = %d", 
        wpa_s->wpa_state, wpa_s->scanning, wpa_s->sched_scanning, gBssTransitionState);
    // If wpa State is already WPA_SCANNING
    // the change state will move to State = WPA_INACTIVE
    // and CME_MESSAGE_ID_SCAN_DONE send to CME thread
    // we check the WPA state before calling scan cancel
    // and if is WPA_SCANNING we do not want to move to STA 
    // IDLE SM, but to DISCONNECTING. Since it will be changed in ScanDone
    // During a BSS transition, the WPA state remains WPA_COMPLETED while scanning, so check gBssTransitionState.
    // If a scan is in progress, we move the STA state to DISCONNECTING, 
    // and it will change to IDLE in CmeStationDeauthReceived once disconnection is complete.
    if ((wpa_s->wpa_state == WPA_SCANNING) || (gBssTransitionState == BTM_RECEIVED))
    {
        waiting4stop = TRUE;
        CME_PRINT_REPORT("\r\ndrv_stopConnectionScans: waiting4stop wpa_state:%d", wpa_s->wpa_state);
    }
    else
    {
        CME_PRINT_REPORT("\r\ndrv_stopConnectionScans: wpa_state :%d", wpa_s->wpa_state);
    }

    // Cancel scheduled one shot scan, if pending
    wpa_supplicant_cancel_scan(wpa_s);

    if ((wpa_s->wpa_state == WPA_SCANNING) || (gBssTransitionState == BTM_RECEIVED))
    {
        if (0 == wpa_s->sched_scanning)
        {
            // One shot connection scan - get the scan type

            // Only one type of connection scan is allowed, ASSERT_GENERAL otherwise
            //ASSERT_GENERAL(FALSE == (ONE_SHOT_OS_SCAN_ACTIVE(pDrv) & ONE_SHOT_APP_SCAN_ACTIVE(pDrv)));
            scanType = SCAN_REQUEST_ONE_SHOT;
            CME_PRINT_REPORT("\r\ndrv_stopConnectionScans: scanType = SCAN_REQUEST_ONE_SHOT");
//
//            if (ONE_SHOT_OS_SCAN_ACTIVE(pDrv))
//            {
//                scanType = SCAN_REQUEST_CONNECT_ONE_SHOT_OS_SCAN;
//            }
//            else if (ONE_SHOT_APP_SCAN_ACTIVE(pDrv))
//            {
//                scanType = SCAN_REQUEST_CONNECT_ONE_SHOT_APP_SCAN;
//            }
        }

        // If scan is running, stop it.
        if (wpa_s->scanning || wpa_s->sched_scanning)
        {
            CME_PRINT_REPORT("\r\nwaiting4stop send stop scan to FW:wpa_s->scanning: %d wpa_s->sched_scanning: %d", wpa_s->scanning,wpa_s->sched_scanning);
            waiting4stop = TRUE;
            // sched_scanning is cleared when stopped event is received
            if (0 != wpa_s->sched_scanning)
            {
                //Periodic scan is running
                pDrv->ops->send_scan_stop(pDrv->roleId, SCAN_REQUEST_CONNECT_PERIODIC_SCAN, FALSE);
            }
            else
            {
                // One shot connection scan is running
                pDrv->ops->send_scan_stop(pDrv->roleId, scanType, FALSE);
            }

        }
        else
        {
            CME_PRINT_REPORT("\r\ndrv_handleOneShotScanStoppedEvent");
            // If we are here, Supplicant is in between one shot connection scans, it's state is scanning,
            // but currently there is no actual scan running in the FW
            drv_handleOneShotScanStoppedEvent(wpa_s, scanType);

        }
    }

    // Cancel the scan work in supplicant
    if (radio_work_pending(wpa_s, "scan"))
    {
        GTRACE(GRP_DRIVER_CC33_DEBUG, "Pending scan work - Remove it...");

        radio_remove_works(wpa_s, "scan", 0);
    }

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    return waiting4stop;
}


// ----------------------------------------------------------------------------

void drv_handleRemainOnChannelEvent(void *apDrv, Bool32 aIsRoc, uint32_t aDurationMS, uint32_t freq)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apDrv;
    union wpa_event_data eventData;
    enum wpa_event_type  eventType = (TRUE == aIsRoc) ? EVENT_REMAIN_ON_CHANNEL : EVENT_CANCEL_REMAIN_ON_CHANNEL;

    eventData.remain_on_channel.duration = aDurationMS;
    eventData.remain_on_channel.freq = freq;

    if(eventType == EVENT_REMAIN_ON_CHANNEL)
    {
        GTRACE(GRP_DRIVER_CC33_DEBUG, "ti_driver send EVENT_REMAIN_ON_CHANNEL to the supplicant aDurationMS:%d freq:%d",
                aDurationMS,freq);
    }
    else
    {
        GTRACE(GRP_DRIVER_CC33_DEBUG, "ti_driver send EVENT_CANCEL_REMAIN_ON_CHANNEL to the supplicant aDurationMS:%d freq:%d",
                aDurationMS,freq);
    }

    wpa_supplicant_event(pDrv->ctx, eventType, &eventData);
}

// ----------------------------------------------------------------------------

p2pGroupRoleType_e CmeGetP2pGroupRoleType(void)
{
    return gP2pGroupRoleType;
}
// ============================================================================
//  Internal service functions
// ============================================================================


/* ----------------------------------------------------------------------------
 setDriverCapabilities
      This function configures driver capabilities on driver DB.
      This information is fetached by supplicant using get_capa API.

 Parameters:    OUT apDrv - pointer to driver instance
 Return code:   0 - API always succeeds
---------------------------------------------------------------------------- */
static int setDriverCapabilities(ti_driver_ifData_t *apDrv)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    // Use the sames configuration as in MCP & NLCP (driver_nl80211) drivers
    apDrv->capa.key_mgmt = WPA_DRIVER_CAPA_KEY_MGMT_WPA
                         | WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK
                         | WPA_DRIVER_CAPA_KEY_MGMT_WPA2
                         | WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK
#ifdef  CONFIG_SAE                
                         | WPA_DRIVER_CAPA_KEY_MGMT_SAE
#endif                         
                         | WPA_DRIVER_CAPA_KEY_MGMT_FT
                         | WPA_DRIVER_CAPA_KEY_MGMT_FT_PSK;

    apDrv->capa.enc = WPA_DRIVER_CAPA_ENC_CCMP
#ifdef CONFIG_IEEE80211W
                    | WPA_DRIVER_CAPA_ENC_BIP
                    | WPA_DRIVER_CAPA_ENC_BIP_GMAC_128
//                  | WPA_DRIVER_CAPA_ENC_BIP_GMAC_256
//                  | WPA_DRIVER_CAPA_ENC_BIP_CMAC_256
#endif
                    ;

    apDrv->capa.auth = WPA_DRIVER_AUTH_OPEN 
                     | WPA_DRIVER_AUTH_SHARED 
                     | WPA_DRIVER_AUTH_LEAP;


    // we support probe response offload (MCP & NLCP
    apDrv->capa.flags = WPA_DRIVER_FLAGS_PROBE_RESP_OFFLOAD 
#ifdef  CONFIG_SAE   
                        | WPA_DRIVER_FLAGS_SAE
#endif                        
                        ;
    apDrv->capa.probe_resp_offloads = WPA_DRIVER_PROBE_RESP_OFFLOAD_WPS
                                    | WPA_DRIVER_PROBE_RESP_OFFLOAD_WPS2
                                    | WPA_DRIVER_PROBE_RESP_OFFLOAD_P2P;

    /* scan related settings */
    apDrv->capa.max_scan_ssids = 1;
    apDrv->capa.max_sched_scan_ssids = CME_SCAN_MAX_PROFILES;
    apDrv->capa.max_match_sets = CME_SCAN_MAX_PROFILES;
    apDrv->capa.sched_scan_supported = 1;
    apDrv->capa.max_sched_scan_plans = CME_SCAN_MAX_SCHED_SCAN_PLANS;
    apDrv->capa.max_sched_scan_plan_interval = CME_SCAN_MAX_SCHED_SCAN_PLAN_INTERVAL;
    apDrv->capa.max_sched_scan_plan_iterations = CME_MAX_SCHED_SCAN_PLAN_ITERATION;


    /* p2p related settings */
    apDrv->capa.num_multichan_concurrent = 2;
    apDrv->capa.flags |= WPA_DRIVER_FLAGS_P2P_CAPABLE;
    // The below is supported by MCP driver but not by NLCP driver
    //  | WPA_DRIVER_FLAGS_P2P_CONCURRENT | WPA_DRIVER_FLAGS_P2P_MGMT_AND_NON_P2P;
     //apDrv->capa.flags |= WPA_DRIVER_FLAGS_P2P_MGMT_AND_NON_P2P;
     //apDrv->capa.flags |= WPA_DRIVER_FLAGS_P2P_CONCURRENT;

    // The below indicates supplicant to enable/disable p2p according to user configuration.
    // When adding a new interface if WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE is set
    //     wpa_s->p2p_mgmt = iface->p2p_mgmt, otherwise wpa_s->p2p_mgmt = 1.
    // wpas_p2p_init is activated only if p2p_mgmt = 1.
    // see wpa_supplicant_init_iface
    if (ROLE_IS_TYPE_STA_BASED_OR_DEVICE(apDrv->roleType))
    {
        apDrv->capa.flags |= WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE;
    }
    //apDrv->capa.flags |= WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE;
    // support for offchannel
    apDrv->capa.flags |= WPA_DRIVER_FLAGS_OFFCHANNEL_TX;


    apDrv->capa.max_remain_on_chan = 5000;

    // Tx status reporting support (supported by MCP & NLCP drivers)
    // Supplicant is block till deauth / disassoc are sent. No need to wait for status
//  apDrv->capa.flags |= WPA_DRIVER_FLAGS_DEAUTH_TX_STATUS;

    // Trust driver association errors (supported by MCP & NLCP drivers)
    apDrv->capa.flags |= WPA_DRIVER_FLAGS_SANE_ERROR_CODES;

    // AP related settings
    //TODO:AP max station get the number
    //apDrv->capa.max_stations =   g_stub_func.l2_cfgGetApMaxNumStations();
    apDrv->capa.flags |= WPA_DRIVER_FLAGS_AP | WPA_DRIVER_FLAGS_AP_UAPSD;

    // Finally set the flag indicating supplicant internal SME should be used (NLCP like)
    apDrv->capa.flags |= WPA_DRIVER_FLAGS_SME;

    //Needed for setting wep static keys
    apDrv->capa.flags |= WPA_DRIVER_FLAGS_SET_KEYS_AFTER_ASSOC_DONE;

    // Needed for MBO
    apDrv->capa.rrm_flags |= WPA_DRIVER_FLAGS_SUPPORT_RRM;

    // TODO - the below are supported by driver_nl80211 but not by MCP driver - check why
//  drv->capa.flags |= WPA_DRIVER_FLAGS_EAPOL_TX_STATUS;

    // The below is not referenced in MCP and it looks like also in NLCP
    //  max_acl_mac_addrs, num_multichan_concurrent, extended_capa, extended_capa_mask, extended_capa_len

    GTRACE(GRP_DRIVER_CC33, "driver capabilities: key_mgmt 0x%x enc 0x%x flags MSB 0x%x flags LSB 0x%x", apDrv->capa.key_mgmt, apDrv->capa.enc, (uint32_t) (apDrv->capa.flags >> 32),   (uint32_t) (apDrv->capa.flags));

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    return 0;
}
// ============================================================================
//  Supplicant notifications
// ============================================================================

/* ----------------------------------------------------------------------------
 sendRxAuthEvent
    Send authentication event to supplicant; this should take supplicant to the
    next step (association)

 Parameters:    apDrv - pointer to driver instance
                apMngPack - pointer to received packet header
                aPackLen - number of bytes in packet, including 80211 header

 based on net\wireless\mlme.c cfg80211_send_rx_auth & driver_nl80211.c, mlme_event_auth

 Return code:   none
---------------------------------------------------------------------------- */
void sendRxAuthEvent(ti_driver_ifData_t  *apDrv,
                     struct ieee80211_mgmt *apMngPack,
                     uint32_t                 aPackLen)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    uint32_t minLen = WLAN_HDR_LEN + sizeof(apMngPack->u.auth);
    union wpa_event_data event;

    os_memset(&event, 0, sizeof(event));

    IRQ_UtilCopyMacAddress(apMngPack->sa, event.auth.peer);
    event.auth.auth_type = le_to_host16(apMngPack->u.auth.auth_alg);
    event.auth.auth_transaction = le_to_host16(apMngPack->u.auth.auth_transaction);
    event.auth.status_code = le_to_host16(apMngPack->u.auth.status_code);

    // Copy any IEs, if exist
    if (minLen < aPackLen)
    {
        event.auth.ies = apMngPack->u.auth.variable;
        event.auth.ies_len = aPackLen - minLen;
    }
    // Authentication confirmed, update peer BSSID
    IRQ_UtilCopyMacAddress(apMngPack->sa, apDrv->authBssid);

    GTRACE(GRP_DRIVER_CC33, "Sending EVENT_AUTH to supplicant");
    wpa_supplicant_event(apDrv->ctx, EVENT_AUTH, &event);

    HOOK(HOOK_IN_DRIVER_TI_WIFI);
}
/* ----------------------------------------------------------------------------
 sendRxAssocEvent
    Send association event to supplicant; this should take supplicant to the
    next step

 Parameters:    apDrv - pointer to driver instance
                apMngPack - pointer to received packet header
                aPackLen - number of bytes in packet, including 80211 header

 based on net\wireless\mlme.c cfg80211_send_rx_assoc which goes to
 driver_nl80211.c, mlme_event_assoc

 Return code:   none
---------------------------------------------------------------------------- */
static void sendRxAssocEvent(ti_driver_ifData_t  *apDrv,
                             struct ieee80211_mgmt *apMngPack,
                             uint32_t                 aPackLen)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    char macStr[MAC_STR_LEN];
    union wpa_event_data event;
    uint16_t status_code;
    uint32_t minLen = WLAN_HDR_LEN + sizeof(apMngPack->u.assoc_resp);

    GET_MAC_STR(apMngPack->sa, macStr);
    GTRACE(GRP_DRIVER_CC33, "Received assoc response from %s sending EVENT_ASSOC to supplicant", macStr);

    os_memset(&event, 0, sizeof(event));

    status_code = le_to_host16(apMngPack->u.assoc_resp.status_code);
    if (WLAN_STATUS_SUCCESS != status_code)
    {
        event.assoc_reject.bssid = apMngPack->bssid;
        if (minLen < aPackLen)
        {
            event.assoc_reject.resp_ies = (u8 *) apMngPack->u.assoc_resp.variable;
            event.assoc_reject.resp_ies_len = minLen;
        }
        event.assoc_reject.status_code = status_code;

        wpa_supplicant_event(apDrv->ctx, EVENT_ASSOC_REJECT, &event);
        return;
    }

    // Copy any IEs, if exist
    if (minLen < aPackLen)
    {
        event.assoc_info.resp_ies = apMngPack->u.assoc_resp.variable;
        event.assoc_info.resp_ies_len = aPackLen - minLen;
    }

    event.assoc_info.freq = apDrv->assocFreq;

    event.assoc_info.req_ies = apDrv->assoc_req_ies;
    event.assoc_info.req_ies_len = apDrv->assoc_req_ies_len;

    wpa_supplicant_event(apDrv->ctx, EVENT_ASSOC, &event);

    clear_assoc_req_ies(apDrv);

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

}

/* ----------------------------------------------------------------------------
 sendEventDeauthDisassoc
    Send deauthentication event to supplicant (based on driver_nl80211.c, mlme_event_deauth_disassoc)
    This API may be activated in response to reception of disconnection packet
    or when we're sending a disconnection packet.
    Packet originator (local/remote) is detected using BSSID comparison, set
    on locally_generated field in the event sturcture.

 Parameters:    apDrv - pointer to driver instance
                aType - deauth/disassoc
                apMngPack - pointer to received/transmitted packet header
                aPackLen - number of bytes in packet, including 80211 header

 Return code:   none
---------------------------------------------------------------------------- */
static void sendEventDeauthDisassoc(ti_driver_ifData_t *apDrv, uint32_t aType,
                                    struct ieee80211_mgmt *apMngPack,
                                    uint32_t aPackLen)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    char macStr[MAC_STR_LEN];
    union wpa_event_data event;
    uint32  minLen = WLAN_HDR_LEN + sizeof(apMngPack->u.deauth);
    uint16 reason_code;
    enum wpa_event_type   type;

    GET_MAC_STR(apMngPack->bssid, macStr);

    CME_PRINT_REPORT("\r\n sendEventDeauthDisassoc: apMngPack->bssid:" MACSTR "\r\n",MAC2STR(apMngPack->bssid) );
    GTRACE(GRP_DRIVER_CC33, "sendEventDeauthDisassoc: apMngPack->bssid:" MACSTR "\r\n",MAC2STR(apMngPack->bssid) );

    // If we're associated but not to the sending device, just drop the packet
    if (FALSE != apDrv->associated &&
        0 == IRQ_UtilCompareMacAddress(apMngPack->bssid, apDrv->authBssid) &&
        0 == IRQ_UtilCompareMacAddress(apMngPack->bssid, apDrv->currBssid))
    {
        /*
         * We have presumably received this deauth as a
         * response to a clear_state_mismatch() outgoing
         * deauth.  Don't let it take us offline!
         */
        GTRACE(GRP_DRIVER_CC33, "RX deauth from unknown BSSID %s, ignoring ...", macStr);

        CME_PRINT_REPORT("\r\n sendEventDeauthDisassoc :apDrv->associated:%d apMngPack->bssid: " MACSTR
                    " apDrv->authBssid:" MACSTR "apDrv->currBssid:" MACSTR "\r\n",
                    apDrv->associated,MAC2STR(apMngPack->bssid),  MAC2STR(apDrv->authBssid), MAC2STR(apDrv->currBssid));

        return;
    }

    markDisconnected(apDrv, 2238);
    os_memset(&event, 0, sizeof(event));

    /* Note: Same offset for Reason Code in both frame subtypes */
    if (minLen <= aPackLen)
    {
        reason_code = le_to_host16(apMngPack->u.deauth.reason_code);
    }

    if (FRAME_TYPE_DISASSOCIATION == aType)
    {
        event.disassoc_info.locally_generated = IRQ_UtilCompareMacAddress(apMngPack->sa, apDrv->macAddr);
        event.disassoc_info.addr = apMngPack->bssid;
        event.disassoc_info.reason_code = reason_code;
        if (minLen < aPackLen)
        {
            event.disassoc_info.ie = apMngPack->u.disassoc.variable;
            event.disassoc_info.ie_len = aPackLen - minLen;
        }
        type = EVENT_DISASSOC;
    }
    else if (FRAME_TYPE_DEAUTHENTICATION == aType)
    {
        event.deauth_info.locally_generated = IRQ_UtilCompareMacAddress(apMngPack->sa, apDrv->macAddr);
        event.deauth_info.addr = apMngPack->bssid;
        event.deauth_info.reason_code = reason_code;
        if (minLen < aPackLen)
        {
            event.deauth_info.ie = apMngPack->u.deauth.variable;
            event.deauth_info.ie_len = aPackLen - minLen;
        }
        type = EVENT_DEAUTH;
    }
    else
    {
        ASSERT_GENERAL(0);
    }

    wpa_supplicant_event(apDrv->ctx, type, &event);

    HOOK(HOOK_IN_DRIVER_TI_WIFI);
}

/* ----------------------------------------------------------------------------
 sendEventUnprotDeauthDisassoc
    Send unprotected deauthentication/disassociation event to supplicant (based on driver_nl80211.c, mlme_event_deauth_disassoc)
    This API may be activated in response to reception of disconnection packet
    or when we're sending a disconnection packet.
    Packet originator (local/remote) is detected using BSSID comparison, set
    on locally_generated field in the event sturcture.

 Parameters:    apDrv - pointer to driver instance
                aType - deauth/disassoc
                apMngPack - pointer to received/transmitted packet header
                aPackLen - number of bytes in packet, including 80211 header

 Return code:   none
---------------------------------------------------------------------------- */
static void sendEventUnprotDeauthDisassoc(ti_driver_ifData_t *apDrv, uint32_t aType,
                                          struct ieee80211_mgmt *apMngPack,
                                          uint32_t aPackLen)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    char macStr[MAC_STR_LEN];
    union wpa_event_data event;
    uint32  minLen = WLAN_HDR_LEN + sizeof(apMngPack->u.deauth);
    uint16 reason_code;
    enum wpa_event_type  type;

    GET_MAC_STR(apMngPack->bssid, macStr);

    CME_PRINT_REPORT("\r\n sendEventUnprotDeauthDisassoc: apMngPack->bssid:" MACSTR "\r\n",MAC2STR(apMngPack->bssid) );
    GTRACE(GRP_DRIVER_CC33, "sendEventUnprotDeauthDisassoc: apMngPack->bssid:" MACSTR "\r\n",MAC2STR(apMngPack->bssid) );

    // If we're associated but not to the sending device, just drop the packet
    if (FALSE != apDrv->associated &&
        0 == IRQ_UtilCompareMacAddress(apMngPack->bssid, apDrv->authBssid) &&
        0 == IRQ_UtilCompareMacAddress(apMngPack->bssid, apDrv->currBssid))
    {
        /*
         * We have presumably received this deauth as a
         * response to a clear_state_mismatch() outgoing
         * deauth.  Don't let it take us offline!
         */
        GTRACE(GRP_DRIVER_CC33, "RX deauth from unknown BSSID %s, ignoring ...", macStr);

        CME_PRINT_REPORT("\r\n sendEventDeauthDisassoc :apDrv->associated:%d apMngPack->bssid: " MACSTR
                    " apDrv->authBssid:" MACSTR "apDrv->currBssid:" MACSTR "\r\n",
                    apDrv->associated,MAC2STR(apMngPack->bssid),  MAC2STR(apDrv->authBssid), MAC2STR(apDrv->currBssid));

        return;
    }

    os_memset(&event, 0, sizeof(event));

    /* Note: Same offset for Reason Code in both frame subtypes */
    if (minLen <= aPackLen)
    {
        reason_code = le_to_host16(apMngPack->u.deauth.reason_code);
    }

    if (FRAME_TYPE_DISASSOCIATION == aType)
    {
        event.unprot_disassoc.sa = apMngPack->sa;
        event.unprot_disassoc.da = apMngPack->da;
        event.unprot_disassoc.reason_code = reason_code;
        type = EVENT_UNPROT_DISASSOC;
    }
    else if (FRAME_TYPE_DEAUTHENTICATION == aType)
    {
        event.unprot_deauth.sa = apMngPack->sa;
        event.unprot_deauth.da = apMngPack->da;
        event.unprot_deauth.reason_code = reason_code;
        type = EVENT_UNPROT_DEAUTH;
    }
    else
    {
        return;
    }

    wpa_supplicant_event(apDrv->ctx, type, &event);

    HOOK(HOOK_IN_DRIVER_TI_WIFI);
}

#ifndef TI_STA_ONLY_BUILD
/* ----------------------------------------------------------------------------
 rx_send_ap_p2p_action_to_ext_app
    Send P2P action frame  event to the application


 Return code:   zero for success , 1 for error
---------------------------------------------------------------------------- */
int32 rx_send_ap_p2p_action_to_ext_app(RxIfDescriptor_t *desc,
        ti_driver_ifData_t *pDrv,
        struct ieee80211_mgmt * pMngPack,
        uint32_t packLen)
{
    struct wpa_supplicant *wpa_s = pDrv->ctx;
    struct hostapd_data *hapd = wpa_s->ap_iface->bss[0];
    if (is_multicast_ether_addr(pMngPack->sa) ||
        is_zero_ether_addr(pMngPack->sa) ||
        os_memcmp(pMngPack->sa, hapd->own_addr, ETH_ALEN) == 0) {

        CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket:: Error ! wrong sa address");
        wpa_printf(MSG_ERROR, "drv_handleRxMngPacket:: Error ! wrong sa address");

        return 1;
    }

    if (!is_broadcast_ether_addr(pMngPack->bssid) &&
        /* Invitation responses can be sent with the peer MAC as BSSID */
        !(hapd->conf->p2p & P2P_GROUP_OWNER) &&
        os_memcmp(pMngPack->bssid, hapd->own_addr, ETH_ALEN) != 0) {
            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket:: Error ! wrong bssid");
            wpa_printf(MSG_ERROR, "drv_handleRxMngPacket:: Error ! wrong bssid");
        return 1;
    }
    if (hapd->iface->state != HAPD_IFACE_ENABLED)
    {
        CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket:: Error ! interface not enabled");
        wpa_printf(MSG_ERROR, "drv_handleRxMngPacket:: Error ! interface not enabled");

        return 1;
    }
    {
        struct sta_info *sta;

        sta = ap_get_sta(hapd, pMngPack->sa);
        if (sta) {
            u16 fc = le_to_host16(pMngPack->frame_control);
            u16 seq_ctrl = le_to_host16(pMngPack->seq_ctrl);

            if ((fc & WLAN_FC_RETRY) &&
                sta->last_seq_ctrl != WLAN_INVALID_MGMT_SEQ &&
                sta->last_seq_ctrl == seq_ctrl &&
                sta->last_subtype == WLAN_FC_STYPE_ACTION) {
                CME_PRINT_REPORT( "\r\ndrv_handleRxMngPacket:ERROR! repeated action frame");
                wpa_printf(MSG_ERROR, "drv_handleRxMngPacket:: Error ! repeated action frame");
                return 1;

            }

            sta->last_seq_ctrl = seq_ctrl;
            sta->last_subtype = WLAN_FC_STYPE_ACTION;
        }
    }
    if (wpa_s->global->p2p_disabled){
        CME_PRINT_REPORT( "\r\ndrv_handleRxMngPacket :ERROR! p2p_disabled");
        wpa_printf(MSG_ERROR, "drv_handleRxMngPacket:: Error ! p2p_disabled");
        return 1;
    }
    if (wpa_s->global->p2p == NULL){
        CME_PRINT_REPORT( "\r\ndrv_handleRxMngPacket :p2p not allocated");
        wpa_printf(MSG_ERROR, "drv_handleRxMngPacket:: p2p not allocated");
        return 1;
    }

    WlanEvenWfdMgmtFrame_t* actionFrame;
    actionFrame = os_malloc(sizeof(WlanEvenWfdMgmtFrame_t));

    memset(actionFrame, 0, sizeof(WlanEvenWfdMgmtFrame_t));
    actionFrame->frame = (uint8_t*)pMngPack;
    actionFrame->frame_len = packLen;
    actionFrame->dataRate = desc->rate;
    actionFrame->rssi_signal = desc->rx_level;
    actionFrame->rx_freq = pDrv->freq;

    CME_CC3XX_PORT_PRINT("\n\rRX: send frame to ext app : P2P_PROV_DISC_REQ");
    wpa_printf(MSG_INFO,"dRX: send frame to ext app : P2P_PROV_DISC_REQ" );

    wlanDispatcherSendEvent(WLAN_EVENT_ACTION_FRAME_RX, (void*)actionFrame, sizeof(WlanEvenWfdMgmtFrame_t));

    os_free(actionFrame);

    return 0;
}
#endif
/* ----------------------------------------------------------------------------
 rx_send_device_dpp_action_to_ext_app
    Send P2P action frame  event to the application


 Return code:   zero for success , 1 for error
---------------------------------------------------------------------------- */
int32 rx_send_device_dpp_action_to_ext_app(RxIfDescriptor_t *desc,
        ti_driver_ifData_t *pDrv,
        struct ieee80211_mgmt * pMngPack,
        uint32_t packLen)
{
    WlanEvenWfdMgmtFrame_t* actionFrame;
    actionFrame = os_malloc(sizeof(WlanEvenWfdMgmtFrame_t));

    memset(actionFrame, 0, sizeof(WlanEvenWfdMgmtFrame_t));
    actionFrame->frame = (uint8_t*)pMngPack;
    actionFrame->frame_len = packLen;
    actionFrame->dataRate = desc->rate;
    actionFrame->rssi_signal = desc->rx_level;
    actionFrame->rx_freq = pDrv->freq;

    CME_PRINT_REPORT("\n\rRX: send DPP frame to ext app");
    wpa_printf(MSG_INFO,"dRX: send DPP frame to ext app" );

    wlanDispatcherSendEvent(WLAN_EVENT_ACTION_FRAME_RX, (void*)actionFrame, sizeof(WlanEvenWfdMgmtFrame_t));

    os_free(actionFrame);

    return 0;
}


ti_driver_ifData_t * drv_getDriverFromDescriptor (void *descriptor)
{
    RxIfDescriptor_t *desc = (RxIfDescriptor_t *)descriptor;
    uint32_t roleId;
    uint8_t netif = TIWDRV_NETIF_NUM;
    tiwdrv_if_mode_e netifMode = TIWDRV_IF_MODE_UNKNOWN;
    ti_driver_ifData_t     *pDrv = NULL;

    //scan results coming on the system hlid
    if (desc->hlid == WLANLINKS_SYSTEM_HLID)
    {
        /* we are not have any link id yet ROLE_STA */
        roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_STA);
        if(roleId == ROLE_ID_NONE)
        {
        	//can happen right after role is down if some frames are still in queue
            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket :ROLE_STA was deactivate, drop frame");
            CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxMngPacket :ROLE_STA was deactivate, drop frame");
        	goto fail;
        }
        pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);
    }
    else if (desc->hlid == DEVICE_GLOBAL_LINK) // device global link
    {
        roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_DEVICE);
        if(roleId == ROLE_ID_NONE)
        {
        	//can happen right after role is down if some frames are still in queue
        	GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket :ROLE_STA was deactivate, drop frame");
        	CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxMngPacket :ROLE_DEVICE was deactivate, drop frame");
        	goto fail;
        }
        pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);
    }
    else if (desc->hlid == AP_GLOBAL_LINK)
    {
        roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_AP);
        if(roleId == ROLE_ID_NONE)
        {
        	//can happen right after role is down if some frames are still in queue
        	GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket :AP_GLOBAL_LINK, ROLE_AP was deactivate, drop frame");
        	CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxMngPacket :AP_GLOBAL_LINK, ROLE_AP was deactivate, drop frame");
        	goto fail;
        }
        pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);

    }
    else
    {
        if(OK != wlanLinks_GetNetifInfo(desc->hlid, &netif, &netifMode))
           goto fail;

        switch(netifMode)
        {
            case TIWDRV_IF_MODE_STA:
            {
                roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_STA);
            }break;
            case TIWDRV_IF_MODE_SAP:
            {
                roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_AP);

            }break;
            case TIWDRV_IF_MODE_P2PDEV:
            {
                roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_DEVICE);

            }break;

            default:
            {
                /* failed unsupported role type */
                GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : No link id. Free the rx buffer");
                CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxMngPacket : netifMode doesn't exists!!! hlid:%d netifMode:%d Free the rx buffer", desc->hlid,netifMode);
                goto fail;
            }
        }
        pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);
    }   
fail:

    return pDrv;
}

void drv_handleRxMngPacket(void *descriptor)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    RxIfDescriptor_t *desc = (RxIfDescriptor_t *)descriptor;
    uint16_t fc, stype;
    uint16_t type;
    uint32_t packLen;
    rxMngPackNextOperation_e rc = RX_MGMT_NONE;
    ti_driver_ifData_t     *pDrv;
    struct ieee80211_mgmt    *pMngPack;
    uint8_t netif = TIWDRV_NETIF_NUM;
    tiwdrv_if_mode_e netifMode = TIWDRV_IF_MODE_UNKNOWN;
    uint32_t roleId;
    uint32_t extraHdr = 0;


    /* Get the mac header location in the packet Buffer */
    pMngPack = (struct ieee80211_mgmt *)(uint8_t*)RX_BUF_DATA(desc);

    packLen = RX_BUF_LEN(desc);

    GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : recv frame packLen=%d desc->hlid=%d", packLen, desc->hlid);

    if (desc->hlid >= WLANLINKS_MAX_LINKS)
    {
        GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : HLID exceeds limits, PktType = %d, Hlid = %d", -1 /*desc->packet_class_tag*/, desc->hlid);
        CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxMngPacket : HLID exceeds limits, Hlid = %d", desc->hlid);
        RxBufFree(desc);
        return;
    }

    if(NULL == gpSupplicantGlobals->ifaces)
    {
        GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : supplicant already stopped drop the packets");
        CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxMngPacket : supplicant already stopped drop the packets\n\r");
        RxBufFree(desc);

        return;
    }

    //scan results coming on the system hlid
    if (desc->hlid == WLANLINKS_SYSTEM_HLID)
    {
        /* we are not have any link id yet ROLE_STA */
        roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_STA);
        if(roleId == ROLE_ID_NONE)
        {
        	//can happen right after role is down if some frames are still in queue
            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket :ROLE_STA was deactivate, drop frame");
            CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxMngPacket :ROLE_STA was deactivate, drop frame");
        	goto fail;
        }
        pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);
    }
    else if (desc->hlid == DEVICE_GLOBAL_LINK) // device global link
    {
        roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_DEVICE);
        if(roleId == ROLE_ID_NONE)
        {
        	//can happen right after role is down if some frames are still in queue
        	GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket :ROLE_STA was deactivate, drop frame");
        	CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxMngPacket :ROLE_DEVICE was deactivate, drop frame");
        	goto fail;
        }
        pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);
    }
    else if (desc->hlid == AP_GLOBAL_LINK)
    {
        roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_AP);
        if(roleId == ROLE_ID_NONE)
        {
        	//can happen right after role is down if some frames are still in queue
        	GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket :AP_GLOBAL_LINK, ROLE_AP was deactivate, drop frame");
        	CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxMngPacket :AP_GLOBAL_LINK, ROLE_AP was deactivate, drop frame");
        	goto fail;
        }
        pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);

    }
    else
    {
        if(OK != wlanLinks_GetNetifInfo(desc->hlid, &netif, &netifMode))
           goto fail;

        switch(netifMode)
        {
            case TIWDRV_IF_MODE_STA:
            {
                roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_STA);
            }break;
            case TIWDRV_IF_MODE_SAP:
            {
                roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_AP);

            }break;
            case TIWDRV_IF_MODE_P2PDEV:
            {
                roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_DEVICE);

            }break;

            default:
            {
                /* failed unsupported role type */
                GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : No link id. Free the rx buffer");
                CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxMngPacket : netifMode doesn't exists!!! hlid:%d netifMode:%d Free the rx buffer", desc->hlid,netifMode);
                RxBufFree(desc);
                return;
            }
        }
        pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);

    }

    if(pDrv)
    {
        if(pDrv->ops->scan_tag(roleId, (void*)desc) == OK)
        {
            GTRACE(GRP_DRIVER_CC33, "rdrv_handleRxMngPacket : mgmt packet, finish process,drop Rx MGMT SCAN packet");

            RxBufFree(desc);//OSPREY_MX-15
            return;

        }
    }

    //GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket Handle Mgmt packets");
    // Handle management packets
    fc = le_to_host16(pMngPack->frame_control);
    type =  WLAN_FC_GET_TYPE(fc); // Frame Type - MGMT(0), CTRL (1), DATA (2)
    stype = WLAN_FC_GET_STYPE(fc);

    if((stype != WLAN_FC_STYPE_PROBE_REQ) && (stype != WLAN_FC_STYPE_REASSOC_RESP)//reduce amount of log prints
       && (stype != WLAN_FC_STYPE_BEACON))
    {
        uint32_t linkId = udataNet_GetTxMgmtLink(TIWDRV_NETIF_ID_SAP, pMngPack->sa);

        //CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket: Packet is of type:%d stype:%d linkId:%d", type, stype,linkId );
        wpa_printf(MSG_INFO, "drv_handleRxMngPacket : Packet is of type:%d stype:%d linkId:%d", type, stype, linkId);
        //wpa_printf(MSG_INFO, "ti_driver: 0ff channel is not allowed! pDrv->freq:%d",pDrv->freq);

    }
    if (IS_WEP_ON(fc) != 0)
    {
        extraHdr = RSN_SEC_LEN;
    }
    if (IS_HT_ON(fc))
    {
        extraHdr += IEEE80211_HT_CTL_LEN;
    }
    //if management frame is protected - remove security header. copy payload backward
    if (extraHdr)
    {
        if ((int32_t)(packLen - extraHdr) < (int32_t)sizeof(MPDUHeader_t))
        {
            //packet is too short, drop it
            goto fail;
        }

        uint8_t*  ptr1 = (uint8_t*)pMngPack + sizeof(MPDUHeader_t);
        uint8_t*  ptr2 = (uint8_t*)pMngPack + sizeof(MPDUHeader_t) + extraHdr; //include security header

        packLen -=  (extraHdr);

        uint16_t  payloadLen = packLen - sizeof(MPDUHeader_t);

        memcpy(ptr1, ptr2, payloadLen);
    }

    // For AP role, just forward the packet to supplicant
    if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
        Bool32 notifySupp = ( (WLAN_FC_STYPE_AUTH == stype)         ||
                              (WLAN_FC_STYPE_ASSOC_REQ == stype)    ||
                              (WLAN_FC_STYPE_REASSOC_REQ == stype)  ||
                              (WLAN_FC_STYPE_DISASSOC == stype)     ||
                              (WLAN_FC_STYPE_DEAUTH == stype)       ||
                              (WLAN_FC_STYPE_ACTION == stype)       ||
                              (WLAN_FC_STYPE_BEACON == stype)       ||
                              (WLAN_FC_STYPE_PROBE_REQ == stype) );

#ifdef CONFIG_P2P
        if(isextP2P()) //if P2P action frames are managed by external app
        {
            if (WLAN_FC_STYPE_ACTION == stype)
            {
                if(pMngPack->u.action.category == WLAN_ACTION_PUBLIC)
                {
                    uint32_t actionVariable;
                    COPY_WLAN_32BIT(&actionVariable, &pMngPack->u.action.u.public_action.variable);
                    CME_CC3XX_PORT_PRINT("\n\rdrv_handleRxMngPacket : Rx Packet is of type:WLAN_ACTION_PUBLIC ,action:%d  vendor type: 0x%x",
                            pMngPack->u.action.u.public_action.action,actionVariable  );
                    wpa_printf(MSG_INFO,"drv_handleRxMngPacket : Rx Packet is of type:WLAN_ACTION_PUBLIC ,action:%d  vendor type: 0x%x",
                            pMngPack->u.action.u.public_action.action,actionVariable  );
                    if(packLen >= IEEE80211_HDRLEN + 9)//size of public action frame is at least 9
                    {
                        if(pMngPack->u.action.u.public_action.action == WLAN_PA_VENDOR_SPECIFIC)
                        {
                            if (WPA_GET_BE32(pMngPack->u.action.u.public_action.variable) == P2P_IE_VENDOR_TYPE)
                            {
                                //the switch is for future where we may handle more types by app.
                                switch ((uint8_t)pMngPack->u.action.u.public_action.variable[4] ) {
                                    case P2P_PROV_DISC_REQ:
                                    {
#ifndef TI_STA_ONLY_BUILD
                                        if(rx_send_ap_p2p_action_to_ext_app(desc, pDrv, pMngPack, packLen) == 0)
                                        {
                                            notifySupp = FALSE;//frame was send to external app
                                        }
#endif
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        CME_PRINT_REPORT("\n\rERROR! drv_handleRxMngPacket : wrong packet len %d",packLen);
                        wpa_printf(MSG_ERROR,"ERROR! drv_handleRxMngPacket : wrong packet len %d",packLen);
                    }
                }
            }
        }
#endif /* CONFIG_P2P */
        if (WLAN_FC_STYPE_AUTH == stype)
        {
            //Check if address is in whitelist or blacklist
            if (0) // (!CME_IsMacAllowed(pMngPack->sa)) //TODO: need to implement whitelist
            {
                CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : ti_drv_txAuthResPacket WLAN_FC_STYPE_AUTH");

                //mac is not allowed. Send proper auth response to the STA
                ti_drv_txAuthResPacket(pDrv, pMngPack->sa,
                                        AUTH_ALG_TYPE_OPEN_SYSTEM,
                                        (pMngPack->u.auth.auth_transaction + 1),
                                        WLAN_STATUS_UNSPECIFIED_FAILURE,
                                        NULL,
                                        0,
                                        0);

                notifySupp = FALSE;
            }
        }

        if (WLAN_FC_STYPE_ASSOC_REQ == stype)
        {

            uint32_t linkId = udataNet_GetTxMgmtLink(TIWDRV_NETIF_ID_SAP, pMngPack->sa);
            uint16_t saLast2bytes;
            uint32_t saFirstBytes;

            notifySupp = (INVALID_LINK != linkId);
            //CME_PRINT_REPORT("\n\rWLAN_FC_STYPE_ASSOC_REQ from " MACSTR " notify supplicant %d link ID %d",
            //                MAC2STR(pMngPack->sa), notifySupp, desc->hlid);
            COPY_WLAN_32BIT(&saFirstBytes,pMngPack->sa);
            COPY_WLAN_WORD(&saLast2bytes,pMngPack->sa+4);

            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : Assoc request from 0x%x 0x%x, notify supplicant %d link ID %d",
                       saFirstBytes, saLast2bytes, notifySupp, desc->hlid);
        }

        if (notifySupp)
        {
            union wpa_event_data eventData;

            eventData.rx_mgmt.frame = (u8 *)pMngPack;
            eventData.rx_mgmt.frame_len = packLen;
            eventData.rx_mgmt.datarate = desc->rate;
            eventData.rx_mgmt.ssi_signal = desc->rx_level;


            if (WLAN_FC_STYPE_PROBE_REQ == stype)
            {
                GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : Probe request: received");
            }

            wpa_supplicant_event(pDrv->ctx, EVENT_RX_MGMT, &eventData);
        }

        // Either supplicant has completed handling the received packet or no
        // no supplicant handling is needed, in any case memory should be returned to MMU
        RxBufFree(desc);

        return;
    }

    switch (stype)
    {
        case WLAN_FC_STYPE_BEACON:
        {
            uint32_t beaconElementsLen;
            const uint8_t *pIE, *pos;
            uint16_t apCapabilities = le_to_host16(pMngPack->u.beacon.capab_info);
            dot11_COUNTRY_t *pCountryIE;
            dot11_POWER_CONSTRAINT_t *pPowerConstraintIE;
            dot11_CELL_TP_t *pDtpcIE;
            dot11HeMuEdcaAcParams_t *pHeMuEdcaParamsIE = NULL;
            dot11_ACParameters_t *pAcParameters = NULL;
            dot11_WME_PARAM_t *pWmmParamIE = NULL;
            uint32_t* pIE_addr_table = NULL;
            uint32_t* pIE_extension_addr_table = NULL;
            uint32_t* pIE_vendorSpecific_addr_table = NULL;

            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : BEACON received");

            pIE_addr_table                = os_zalloc(0xFF * sizeof(uint32_t));
            pIE_extension_addr_table      = os_zalloc(DOT11_MAX_WPSIE_SIZE * sizeof(uint32_t));
            pIE_vendorSpecific_addr_table = os_zalloc(DOT11_MAX_WPSIE_SIZE * sizeof(uint32_t));
            
            if((pIE_addr_table == NULL) || (pIE_extension_addr_table == NULL) || (pIE_vendorSpecific_addr_table == NULL))
            {
                if(pIE_addr_table)
                    os_free(pIE_addr_table);

                if(pIE_extension_addr_table)
                    os_free(pIE_extension_addr_table);
                
                if(pIE_vendorSpecific_addr_table)
                    os_free(pIE_vendorSpecific_addr_table);


                GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : allocation of pIE_addr_table failed");
                CME_PRINT_REPORT_ERROR("\r\nERROR! drv_handleRxMngPacket : allocation of pIE_addr_table failed");
                break;//don't analyze the beacon
            }


            pos = pMngPack->u.beacon.variable;
            beaconElementsLen = packLen - (uint32_t )(pos - (uint8_t *)pMngPack);

            
            

            if( parse_ie(pIE_addr_table , pIE_extension_addr_table, pIE_vendorSpecific_addr_table, pos, beaconElementsLen) != 0)
            {
                os_free(pIE_addr_table);
                os_free(pIE_extension_addr_table);
                os_free(pIE_vendorSpecific_addr_table);
                GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : parsing of IE table failed");
                CME_PRINT_REPORT_ERROR("\r\nERROR drv_handleRxMngPacket : parsing of IE table failed");
                break;
            }

#ifndef DISABLE_WIFI6
            pHeMuEdcaParamsIE =  (void *)pIE_extension_addr_table[MU_EDCA_PARAMETER_SET_IE_ID];

            if(pHeMuEdcaParamsIE && (pDrv->connected))
            {
                int ac;
                int changed = 0 ;
                for(ac = 0; ac < NUM_ACCESS_CATEGORIES; ac++)
                {
                    if (os_memcmp(pDrv->apHeMuEdcaAcParams[ac]._byte, pHeMuEdcaParamsIE->heMuEdcaAcParamsIe[ac]._byte,HE_MU_EDCA_FIELD_BYTES) != 0)
                    {

                        os_memcpy(pDrv->apHeMuEdcaAcParams[ac]._byte, pHeMuEdcaParamsIE->heMuEdcaAcParamsIe[ac]._byte,HE_MU_EDCA_FIELD_BYTES);
                        
                        pDrv->ops->tx_param(pDrv, &pDrv->assocParams.acParameters[ac], pDrv->assocParams.psScheme, TRUE, (uint8_t *)&pHeMuEdcaParamsIE->heMuEdcaAcParamsIe[ac], ac);

                    }

                }
   
            }
#endif

            pWmmParamIE = (void *)pIE_vendorSpecific_addr_table[dot11_WME_OUI_TYPE];
                    
            if(pWmmParamIE && (pDrv->connected))
            {
                int ac;
                int changed = 0 ;
                if(os_memcmp(&(pDrv->apAcParameters), &(pWmmParamIE->WME_ACParameteres), sizeof(dot11_ACParameters_t)) != 0)
                {
                    setWmeSiteParams(pWmmParamIE, &pDrv->assocParams);

                    os_memcpy(&(pDrv->apAcParameters), &(pWmmParamIE->WME_ACParameteres), sizeof(dot11_ACParameters_t));

                    for(ac = 0; ac < NUM_ACCESS_CATEGORIES; ac++)
                    {
#ifndef DISABLE_WIFI6
                        if(pHeMuEdcaParamsIE)
                        {
                            pDrv->ops->tx_param(pDrv, &pDrv->assocParams.acParameters[ac], pDrv->assocParams.psScheme, TRUE, (uint8_t *)&pHeMuEdcaParamsIE->heMuEdcaAcParamsIe[ac], ac);
                        }
                        else
                        {
                            pDrv->ops->tx_param(pDrv, &pDrv->assocParams.acParameters[ac], pDrv->assocParams.psScheme, TRUE, (uint8_t *)&pDrv->assocParams.muEdca[ac], ac);
                        }
#else
                        pDrv->ops->tx_param(pDrv, &pDrv->assocParams.acParameters[ac], pDrv->assocParams.psScheme, FALSE, NULL, ac);
#endif
                    }
                }

            }


            pIE =  (void *)pIE_addr_table[DOT11_EXT_CHANNEL_SWITCH_ELE_ID];

            if (pIE)
            {
                dot11_EXT_CHANNEL_SWITCH_IE_t *pExtChannelSwitchIE = (dot11_EXT_CHANNEL_SWITCH_IE_t *)pIE;

                CME_PRINT_REPORT("\r\ndrv_handleRxMngPacket :cmd extended channel switch role_id=%d,"
                                 "new channel=%d, count=%d, block tx=%d, new operating class=%d\n\r",
                                 roleId,
                                 pExtChannelSwitchIE->channelNumber,
                                 pExtChannelSwitchIE->channelSwitchCount,
                                 pExtChannelSwitchIE->channelSwitchMode,
                                 pExtChannelSwitchIE->newOperatingClass);

                CME_ChannelSwitchAnnounceNotify(roleId,
                                                pExtChannelSwitchIE->channelNumber,
                                                pExtChannelSwitchIE->channelSwitchCount,
                                                pExtChannelSwitchIE->channelSwitchMode);

            }
            else
            {
                pIE =  (void *)pIE_addr_table[DOT11_CHANNEL_SWITCH_ELE_ID];
                if (pIE)
                {
                    dot11_CHANNEL_SWITCH_IE_t *pChannelSwitchIE = (dot11_CHANNEL_SWITCH_IE_t *)pIE;

                    CME_PRINT_REPORT("drv_handleRxMngPacket :cmd channel switch role_id=%d, " 
                                     "new channel=%d, count=%d, block tx=%d\n\r",
                                     roleId,
                                     pChannelSwitchIE->channelNumber,
                                     pChannelSwitchIE->channelSwitchCount,
                                     pChannelSwitchIE->channelSwitchMode);

                    CME_ChannelSwitchAnnounceNotify(roleId,
                                                    pChannelSwitchIE->channelNumber,
                                                    pChannelSwitchIE->channelSwitchCount,
                                                    pChannelSwitchIE->channelSwitchMode);
                }
            }
            
            pCountryIE =  (dot11_COUNTRY_t *)pIE_addr_table[DOT11_COUNTRY_ELE_ID];

            pPowerConstraintIE =  (dot11_POWER_CONSTRAINT_t *)pIE_addr_table[DOT11_POWER_CONSTRAINT_ELE_ID];

            pDtpcIE =  (dot11_CELL_TP_t *)pIE_addr_table[DOT11_CELL_TP_ELE_ID];

            regulatoryDomain_handlePowerConstraint(pDrv, apCapabilities,
                                                   pCountryIE, pPowerConstraintIE,
                                                   pDtpcIE);

            os_free(pIE_addr_table);
            os_free(pIE_extension_addr_table);
            os_free(pIE_vendorSpecific_addr_table);
            //Beacons are received into here only on device role -during p2p listen
            rc = RX_MGMT_NONE;
            break;
        }
        case WLAN_FC_STYPE_PROBE_REQ:
            //CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : PROBE_REQ roleId:%d" ,roleId);
            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : STA Probe request: received roleId:%d", roleId);

            //Probe-req are received into here only on device role -during p2p listen
            if (ROLE_IS_TYPE_DEVICE(pDrv->roleType))
            {
                if (pDrv->p2pReportProbeRequestRx != 0)
                {
                    rc = RX_SEND_RX_PROBE_REQ;
                }
                else
                {
                    rc = RX_MGMT_NONE;
                }
            }
            else
            {
                rc = RX_MGMT_NONE;
            }
            break;
        case WLAN_FC_STYPE_PROBE_RESP:
            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : PROBE_RESP received. Drop. rc=%d roleId:%d", rc, roleId);
//          rc = rxProbeResponsePacket(pMngPack, packLen);
            break;

        case WLAN_FC_STYPE_AUTH:
            //CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket(): WLAN_FC_STYPE_AUTH");
            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : WLAN_FC_STYPE_AUTH. roleId:%d", roleId);
            rc = ti_drv_rxAuthResponsePacket(pDrv, pMngPack, packLen);
            break;

        case WLAN_FC_STYPE_DEAUTH:
            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket(): WLAN_FC_STYPE_DEAUTH");
            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : WLAN_FC_STYPE_DEAUTH. roleId:%d", roleId);
            rc = ti_drv_rxDeauthPacket(pDrv, pMngPack, packLen);
            break;

        case WLAN_FC_STYPE_DISASSOC:
            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : WLAN_FC_STYPE_DISASSOC");
            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : WLAN_FC_STYPE_DISASSOC. roleId:%d", roleId);
            rc = ti_drv_rxDisassocPacket(pDrv, pMngPack, packLen);
            break;

        case WLAN_FC_STYPE_ASSOC_RESP:
            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : WLAN_FC_STYPE_ASSOC_RESP");
            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : WLAN_FC_STYPE_ASSOC_RESP. roleId:%d", roleId);
            rc = ti_drv_rxAssocResponsePacket(pDrv, pMngPack, packLen, (WLAN_FC_STYPE_REASSOC_RESP == stype), desc);
            break;

        case WLAN_FC_STYPE_REASSOC_RESP:
            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : WLAN_FC_STYPE_REASSOC_RESP. roleId:%d", roleId);
            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : WLAN_FC_STYPE_REASSOC_RESP");
            //RX_MGMT_PRINT("\n\rdrv_handleRxMngPacket: WLAN_FC_STYPE_ASSOC_RESP|WLAN_FC_STYPE_REASSOC_RESP");

            rc = ti_drv_rxAssocResponsePacket(pDrv, pMngPack, packLen, (WLAN_FC_STYPE_REASSOC_RESP == stype), desc);
            break;

        case WLAN_FC_STYPE_ACTION:
        {
            CME_CC3XX_PORT_PRINT("\n\rdrv_handleRxMngPacket: WLAN_FC_STYPE_ACTION category %d, action %d roleId:%d",
                   pMngPack->u.action.category,
                   pMngPack->u.action.u.sa_query_req.action, roleId);
            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : Received action frame. category %d, action %d roleId:%d",
                   pMngPack->u.action.category,
                   pMngPack->u.action.u.sa_query_req.action, roleId);


            switch (pMngPack->u.action.category)
            {
                case WLAN_ACTION_SA_QUERY:
                {
                    rc = ti_drv_rxSaQueryPacket(pDrv,
                                                 pMngPack,
                                                 packLen);
                }
                    break;

                case WLAN_ACTION_SPECTRUM_MGMT:
                {
                    uint8_t* pChannelSwitchIEstart;
                    if (pMngPack->u.action.u.chan_switch.action_code != DOT11_CHANNEL_SWITCH_ACTION_CODE)
                    {
                        GTRACE(GRP_DRIVER_CC33,
                               "drv_handleRxMngPacket : Unknown action code / element ID (%d/%d) for SPECTRUM_MGMT action frame, ignore it.",
                               pMngPack->u.action.u.chan_switch.action_code,
                               pMngPack->u.action.u.chan_switch.element_id);

                        break;
                    }
                    dot11_CHANNEL_SWITCH_ACTION_FRAME_t* pChannelSwitchstart = (dot11_CHANNEL_SWITCH_ACTION_FRAME_t*)&pMngPack->u.action.u.chan_switch.switch_mode;
                    CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : action code cmd channel switch role_id=%d, new channel=%d, count=%d, block tx=%d hlid:%d",
                    roleId, pChannelSwitchstart->channelNumber, pChannelSwitchstart->channelSwitchCount, pChannelSwitchstart->channelSwitchMode,desc->hlid);
                    if(roleId == 1)//AP role id doesn't make sense ,OSPREY_LDB-2851
                    {
                        CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : action code cmd channel switch ! drop packet, current channel:%d",desc->channel);
                        break;
                    }
                    CME_ChannelSwitchAnnounceNotify(roleId, pChannelSwitchstart->channelNumber, pChannelSwitchstart->channelSwitchCount, pChannelSwitchstart->channelSwitchMode);
                    break;
                }
                    break;

                case WLAN_ACTION_PUBLIC:
                {
                        if (pMngPack->u.action.u.chan_switch.action_code == DOT11_EXT_CHANNEL_SWITCH_ACTION_CODE) 
                        {
                            dot11_EXT_CHANNEL_SWITCH_ACTION_FRAME_t* pExtChannelSwitchIEstart = (dot11_EXT_CHANNEL_SWITCH_ACTION_FRAME_t*)&pMngPack->u.action.u;
                            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : action code cmd extended channel switch role_id=%d, new channel=%d, count=%d, block tx=%d, new operating class=%d",
                            roleId, pExtChannelSwitchIEstart->channelNumber, pExtChannelSwitchIEstart->channelSwitchCount, pExtChannelSwitchIEstart->channelSwitchMode, pExtChannelSwitchIEstart->newOperatingClass);
                            CME_ChannelSwitchAnnounceNotify(roleId, pExtChannelSwitchIEstart->channelNumber, pExtChannelSwitchIEstart->channelSwitchCount, pExtChannelSwitchIEstart->channelSwitchMode);
                            break;
                        }
                		uint32_t actionVariable;
            			COPY_WLAN_32BIT(&actionVariable, &pMngPack->u.action.u.public_action.variable);
            			CME_CC3XX_PORT_PRINT("\n\rdrv_handleRxMngPacket : Rx Packet is of type:WLAN_ACTION_PUBLIC ,action:%d, vendor type: 0x%x",
            						pMngPack->u.action.u.public_action.action,actionVariable  );
            			wpa_printf(MSG_INFO,"drv_handleRxMngPacket : Rx Packet is of type:WLAN_ACTION_PUBLIC ,action:%d, vendor type: 0x%x",
            							pMngPack->u.action.u.public_action.action,actionVariable  );
            			if(packLen >= IEEE80211_HDRLEN + 9)//size of public action frame is at least 9
            			{
            				if(pMngPack->u.action.u.public_action.action == WLAN_PA_VENDOR_SPECIFIC)
            				{
            					//DPP packet
            					if (isextDPP() && (WPA_GET_BE32(pMngPack->u.action.u.public_action.variable) == QM_ACTION_VENDOR_TYPE))
            					{
            						if(rx_send_device_dpp_action_to_ext_app(desc, pDrv, pMngPack, packLen) == 0)
            						{
            							rc = RX_MGMT_NONE;
            						}
            					}
                            	else //if (pMngPack->u.action.u.sa_query_req.action == WLAN_PA_VENDOR_SPECIFIC)
                                {
                                    GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : Received Public WLAN_ACTION_PUBLIC frame VENDOR_SPECIFIC, roleId:%d", roleId );
                                    rc = RX_MGMT_SEND_RX_MGMT_EVENT;
                                }
            				}
            				if(isextDPP() && ((pMngPack->u.action.u.public_action.action == WLAN_PA_GAS_INITIAL_REQ)||
            						(pMngPack->u.action.u.public_action.action == WLAN_PA_GAS_INITIAL_RESP) ||
            						(pMngPack->u.action.u.public_action.action == WLAN_PA_GAS_COMEBACK_REQ) ||
            						(pMngPack->u.action.u.public_action.action == WLAN_PA_GAS_COMEBACK_RESP)) )
            				{
            					//DPP packet
            				    if ((packLen >= IEEE80211_HDRLEN + 17) &&
            					   (WPA_GET_BE32((uint8_t *)(&(pMngPack->u.action.u.public_action.variable[10]))) == QM_ACTION_VENDOR_TYPE))
            					{
            				        if(rx_send_device_dpp_action_to_ext_app(desc, pDrv, pMngPack, packLen) == 0)
            						{
            				            rc = RX_MGMT_NONE;
            						}
            					}
            				}
            			}
            			else
            			{
            				CME_PRINT_REPORT("\n\rERROR! drv_handleRxMngPacket : wrong packet len %d",packLen);
            				wpa_printf(MSG_ERROR,"ERROR! drv_handleRxMngPacket : wrong packet len %d",packLen);
            			}
                    
                }
                break;

                case WLAN_ACTION_RADIO_MEASUREMENT:
                {
                    // part of MBO implementation
                    if (pMngPack->u.action.u.rrm.action == WLAN_RRM_RADIO_MEASUREMENT_REQUEST)
                    {
                        // looks like the rrm struct should contain an additional field (u8 repetitions[2]) before the variable field, so start with variable[2]
                        struct rrm_measurement_request_element *rrm_measurement_request = (struct rrm_measurement_request_element *)&pMngPack->u.action.u.rrm.variable[2];
                        if (rrm_measurement_request->type == MEASURE_TYPE_BEACON)
                        {
                            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket: WLAN_ACTION_RADIO_MEASUREMENT : Measurement Request element : Beacon request");
                            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket: WLAN_ACTION_RADIO_MEASUREMENT : Measurement Request element : Beacon request");
                            rc = RX_MGMT_SEND_RX_MGMT_EVENT;
                        }
                    }
                }
                break;

                case WLAN_ACTION_WNM:
                {
                    // part of MBO implementation
                    if (pMngPack->u.action.u.bss_tm_req.action == WNM_BSS_TRANS_MGMT_REQ)
                    {
                        // ignore packets received after disconnection (due to a race condition/reinsertion)
                        if (pDrv->wpa_s->wpa_state < WPA_ASSOCIATED)
                        {
                            rc = RX_MGMT_NONE;
                            break;
                        }

                        // check validity interval not set to zero - IOP issue
                        if (pMngPack->u.action.u.bss_tm_req.validity_interval == 0)
                        {
                            pMngPack->u.action.u.bss_tm_req.validity_interval = 15;
                        }
                        
                        // if another BTM preceded this one - pass frame to supplicant
                        if (gBssTransitionState != NO_TRANSITION)
                        {
                            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket: WLAN_ACTION_WNM : BSS Transition Management Request");
                            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket: WLAN_ACTION_WNM : BSS Transition Management Request");
                            rc = RX_MGMT_SEND_RX_MGMT_EVENT;
                            break;
                        }

                        int ret = set_cond_in_process_wlan_supplicant_operation();
                        if (ret == OSI_OK)
                        {
                            gBtmCtr = 0;
                            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket: WLAN_ACTION_WNM : BSS Transition Management Request, setting protection");
                            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket: WLAN_ACTION_WNM : BSS Transition Management Request, setting protection");

                            // gBssTransitionState is currently NO_TRANSITION. update the transition status and notify the user.
                            gBssTransitionState = BTM_RECEIVED;
                            wlanDispatcherSendEvent(WLAN_EVENT_BSS_TRANSITION_INITIATED, (void*)NULL, 0);
                            rc = RX_MGMT_SEND_RX_MGMT_EVENT;
                        }
                        else
                        {
                            gBtmCtr++;
                            if (gBtmCtr >= RX_PACKET_REINSERTION_THRESHOLD)
                            {
                                // retries threshold exceeded, drop the frame
                                rc = RX_MGMT_NONE;
                                gBtmCtr = 0;
                                GTRACE(GRP_DRIVER_CC33, "BTM: retries threshold exceeded, dropping the frame");
                                gBssTransitionState = NO_TRANSITION;
                                break;
                            }
                            
                            // In case of protected frames, the security header is removed during processing.
                            // Since we are resending the frame to the function, we must clear the protection bit the first
                            // time to prevent attemting to remove the security header again.
                            if (IS_WEP_ON(fc))
                            {
                                pMngPack->frame_control &= ~(1 << DOT11_FC_WEP_SHIFT);
                            }

                            GTRACE(GRP_DRIVER_CC33, "BTM: starting wlan_supplicant_operation failed, reinserting packet to queue, gBtmCtr: %d", gBtmCtr);
                            CME_NotifyRxMngPack(descriptor);
                            rc = RX_DONT_FREE;
                        }
                    }
                }
                break;
            }
        }
        break;

        default:
            HOOK(HOOK_IN_DRIVER_TI_WIFI);

            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : Received unknown mng type %d, frame control 0x%x roleId:%d", stype, pMngPack->frame_control, roleId);
            CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxMngPacket ERROR Received unknown mng type %d, frame control 0x%x roleId:%d", stype, pMngPack->frame_control, roleId);
            break;
    }

    // depending on the result of received packet handling, notify the supplicant
    switch (rc)
    {
        case RX_MGMT_NONE:
        case RX_DONT_FREE:
            /* no action */
            break;
        case RX_MGMT_DEAUTH:
            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : sendEventDeauthDisassoc hange state to :CME_STA_WLAN_PEER_DISCONNECT_REQ");
            sendEventDeauthDisassoc(pDrv, FRAME_TYPE_DEAUTHENTICATION, pMngPack, packLen);
        	CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: RX_MGMT_DEAUTH, change state to CME_STA_WLAN_PEER_DISCONNECT_REQ !!");
            CmeStationFlowSM(CME_STA_WLAN_PEER_DISCONNECT_REQ, CmeStationFlow_GetCurrentUser());
            break;
        case RX_MGMT_DISASSOC:
            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : sendEventDeauthDisassoc state to :CME_STA_WLAN_PEER_DISCONNECT_REQ");
            sendEventDeauthDisassoc(pDrv, FRAME_TYPE_DISASSOCIATION, pMngPack, packLen);
        	CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: RX_MGMT_DISASSOC, change state to CME_STA_WLAN_PEER_DISCONNECT_REQ !!");
            CmeStationFlowSM(CME_STA_WLAN_PEER_DISCONNECT_REQ, CmeStationFlow_GetCurrentUser());
            break;
        case RX_MGMT_UNPROT_DEAUTH:
            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : sendEventUnprotDeauthDisassoc");
            sendEventUnprotDeauthDisassoc(pDrv, FRAME_TYPE_DEAUTHENTICATION, pMngPack, packLen);
            break;
        case RX_MGMT_UNPROT_DISASSOC:
            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : sendEventUnprotDeauthDisassoc");
            sendEventUnprotDeauthDisassoc(pDrv, FRAME_TYPE_DISASSOCIATION, pMngPack, packLen);
            break;
        case RX_MGMT_AUTH:
            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : sendRxAuthEvent\n");
            sendRxAuthEvent(pDrv, pMngPack, packLen);
            break;
        case RX_MGMT_RX_ASSOC:
            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : sendRxAssocEvent\n");
            sendRxAssocEvent(pDrv, pMngPack, packLen);
            break;
        case RX_MGMT_ASSOC_TIMEOUT:
            CME_PRINT_REPORT("\n\rdrv_handleRxMngPacket : drv_sendConnectTimeoutEvent\n");
            drv_sendConnectTimeoutEvent(pDrv, EVENT_ASSOC_TIMED_OUT, pMngPack->bssid);
            break;

        case RX_MGMT_SEND_RX_MGMT_EVENT:
        {
            union wpa_event_data eventData;

            eventData.rx_mgmt.frame = (u8 *)pMngPack;
            eventData.rx_mgmt.frame_len = packLen;//after security header is reduced
            eventData.rx_mgmt.datarate = desc->rate;
            eventData.rx_mgmt.ssi_signal = desc->rx_level; 
            eventData.rx_mgmt.freq = channel_to_freq(desc->channel);
            GTRACE(GRP_DRIVER_CC33, "Send EVENT_RX_MGMT to wpa_supplicant, channel=%d", desc->channel);
            wpa_supplicant_event(pDrv->ctx, EVENT_RX_MGMT, &eventData);
        }
        break;
        case RX_SEND_RX_PROBE_REQ:
        {
            union wpa_event_data eventData;

            eventData.rx_probe_req.sa = (u8 *)pMngPack->sa;
            eventData.rx_probe_req.da = (u8 *)pMngPack->da;
            eventData.rx_probe_req.bssid = (u8 *)pMngPack->bssid;
            eventData.rx_probe_req.ssi_signal = desc->rx_level;
            eventData.rx_probe_req.ie = (u8 *)pMngPack + IEEE80211_HDRLEN;
            eventData.rx_probe_req.ie_len = packLen - IEEE80211_HDRLEN;

            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : Send EVENT_RX_PROBE_REQ to wpa_supplicant");
            wpa_supplicant_event(pDrv->ctx, EVENT_RX_PROBE_REQ, &eventData);
        }

        break;

        default:
            GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket : Unknown return code %d", rc);
            CME_PRINT_REPORT_ERROR("\n\rERROR Unknown return code %d", rc);
            break;
    }
fail:
    if (rc != RX_DONT_FREE)
    {
        /* not dispatched yet? error! */
        GTRACE(GRP_DRIVER_CC33, "drv_handleRxMngPacket: FREE Rx Buffer");
        RxBufFree(desc);
    }

    return ;
}

void drv_handleUnprotRxDeauth (void *descriptor, uint32 roleId)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    RxIfDescriptor_t *desc = (RxIfDescriptor_t *)descriptor;

    uint16                  fc, stype;
    union wpa_event_data    eventData;
    struct ieee80211_mgmt   *pMngPack;
    ti_driver_ifData_t      *pDrv;

    pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);
    /* Get the mac header location in the packet Buffer */
    pMngPack = (struct ieee80211_mgmt *)(uint8_t*)RX_BUF_DATA(desc);

    // Handle management packet
    fc = le_to_host16(pMngPack->frame_control);
    stype = WLAN_FC_GET_STYPE(fc);

    eventData.unprot_disassoc.reason_code = pMngPack->u.deauth.reason_code;

    eventData.unprot_disassoc.sa = pMngPack->sa;
    eventData.unprot_disassoc.da = pMngPack->da;

    GTRACE(GRP_MGMT_PROTECTION_IMP, "MPF: unprotected deauth/deassoc %d, send EVENT to supplicant", stype);
    RX_MGMT_PRINT("\n\rMPF: unprotected deauth/deassoc %d, send EVENT to supplicant", stype);


    if (stype == WLAN_FC_STYPE_DEAUTH)
    {
        GTRACE(GRP_MGMT_PROTECTION,"MPF: Deauth to Supplicant");
        wpa_supplicant_event(pDrv->ctx, EVENT_UNPROT_DEAUTH, &eventData);
    }
    else
    {
        GTRACE(GRP_MGMT_PROTECTION,"MPF: Deassoc to Supplicant");
        wpa_supplicant_event(pDrv->ctx, EVENT_UNPROT_DISASSOC, &eventData);
    }
fail:
    RxBufFree(desc);
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

}

void drv_handleRxFromUnknown(void *descriptor, uint32 roleId)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    RxIfDescriptor_t *desc = (RxIfDescriptor_t *)descriptor;
    ti_driver_ifData_t *pDrv = NULL;
    RoleType_e eRoleType;
    TEthernetHeader *pHdr;
    union wpa_event_data eventData;

    GTRACE(GRP_DRIVER_CC33, "drv_handleRxFromUnknown: roleId=%d, hlid=%d", roleId, desc->hlid);
    CME_PRINT_REPORT("\n\rdrv_handleRxFromUnknown: roleId=%d, hlid=%d", roleId, desc->hlid);

    if (NULL == gpSupplicantGlobals || NULL == gpSupplicantGlobals->ifaces)
    {
        GTRACE(GRP_DRIVER_CC33, "drv_handleRxFromUnknown: supplicant stopped");
        CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxFromUnknown: supplicant stopped");
        goto done;
    }

    /* Get role type from role ID */
    eRoleType = drv_getRoleTypeFromRoleId(gpSupplicantGlobals, roleId);

    /* Only notify supplicant for AP or P2P GO role */
    if (ROLE_IS_TYPE_AP_BASED(eRoleType) == FALSE)
    {
        GTRACE(GRP_DRIVER_CC33, "drv_handleRxFromUnknown: non-AP role %d, drop frame", eRoleType);
        CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxFromUnknown: non-AP role %d, drop frame", eRoleType);
        goto done;
    }

    pDrv = getDriverForRoleId(roleId, gpSupplicantGlobals);
    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33, "drv_handleRxFromUnknown: driver instance is NULL");
        CME_PRINT_REPORT_ERROR("\n\rdrv_handleRxFromUnknown: driver instance is NULL");
        goto done;
    }

    /* Get source MAC from ethernet header */
    pHdr = (TEthernetHeader *)RX_ETH_PKT_DATA((uint8_t *)descriptor);

    GTRACE(GRP_DRIVER_CC33, "drv_handleRxFromUnknown: notify supplicant, src=" MACSTR,
           MAC2STR(pHdr->src));

    CME_PRINT_REPORT("\n\rdrv_handleRxFromUnknown: notify supplicant, src=" MACSTR,
           MAC2STR(pHdr->src));

    /* Notify supplicant about frame from unknown station */
    os_memset(&eventData, 0, sizeof(eventData));
    eventData.rx_from_unknown.bssid = pDrv->macAddr;
    eventData.rx_from_unknown.addr = pHdr->src;
    eventData.rx_from_unknown.wds = 0;

    wpa_supplicant_event(pDrv->ctx, EVENT_RX_FROM_UNKNOWN, &eventData);

done:
    RxBufFree(desc);

    HOOK(HOOK_IN_DRIVER_TI_WIFI);
}
// ----------------------------------------------------------------------------
void drv_handleRxEapol(void *aDesc)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    RxIfDescriptor_t *desc = (RxIfDescriptor_t *)aDesc;
    ti_driver_ifData_t     *pDrv;
    uint8_t netif = TIWDRV_NETIF_NUM;
    tiwdrv_if_mode_e netifMode = TIWDRV_IF_MODE_UNKNOWN;
    uint32_t roleId = 0;
    uint32_t packLen;
    uint8_t                *pEapolBuff;
    uint32_t               eapolOffset;
    union wpa_event_data eventData;
	TEthernetHeader *pHdr;
    uint32_t headerSize = 0;
    uint8_t  headerAlignment = 0;


    /* Get the mac header location in the packet Buffer */
    pHdr = (TEthernetHeader *)RX_ETH_PKT_DATA((uint8_t *)aDesc);
    packLen = RX_ETH_PKT_LEN((uint8_t *)aDesc);



    headerSize += sizeof(TEthernetHeader);
    packLen -= ETHERNET_HDR_LEN;

    RX_MGMT_PRINT("\n\r drv_handleRxEapol");

    if (desc->hlid >= WLANLINKS_MAX_LINKS)
    {
        GTRACE(GRP_DRIVER_CC33, "rolesMngr_ForwardMgmtPacket(): HLID exceeds limits Hlid = %d", desc->hlid);
        RX_MGMT_PRINT_ERROR("\n\r drv_handleRxEapol():  HLID exceeds limits Hlid = %d", desc->hlid);
        RxBufFree(desc);

        return;
    }

    if(NULL == gpSupplicantGlobals->ifaces)
    {
        RX_MGMT_PRINT("\n\r rv_handleRxEapol(): supplicant already stopped drop the packets");

        GTRACE(GRP_DRIVER_CC33, "drv_handleRxEapol(): supplicant already stopped drop the packets");
        RxBufFree(desc);

        return;
    }

    if (desc->hlid == WLANLINKS_SYSTEM_HLID)
    {
        /* we are not have any link id yet ROLE_STA */
        roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_STA);
        if (roleId != ROLE_ID_NONE)
        {
            pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);
        }
        else
        {
            /* maybe we have p2p client role started */
            roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_P2P_CL);
            if (roleId != ROLE_ID_NONE)
            {
                pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);
            }
        }
    }
    else
    {
        if(OK != wlanLinks_GetNetifInfo(desc->hlid, &netif, &netifMode))
           goto fail;

        switch(netifMode)
        {
            case TIWDRV_IF_MODE_STA:
            {
                roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_STA);
            }break;
            case TIWDRV_IF_MODE_SAP:
            {
                roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_AP);

            }break;
            case TIWDRV_IF_MODE_P2PDEV:
            {
                roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_DEVICE);

            }break;

            default:
            {
                HOOK(HOOK_IN_DRIVER_TI_WIFI);

                /* failed unsupported role type */
                GTRACE(GRP_DRIVER_CC33_DEBUG, "NOTIFY: netifMode (%d) is invalid, dropping packet", netifMode);
                RX_MGMT_PRINT_ERROR("\n\rNOTIFY: netifMode (%d) is invalid, dropping packet", netifMode);
                goto fail;
            }
        }
        pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);

    }

    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33_DEBUG, "NOTIFY: driver instance is invalid, dropping packet");
        RxBufFree(desc);

        return;
    }

    // PMAC updates descriptor fields before forwarding:
    //      address points to first byte of 802.11 header
    //      pDesc->length_type.length reflects total number of received bytes
    //      For EAPOL data we have to skip 802.11 header and snap header

	eapolOffset = headerSize;
    pEapolBuff = (uint8_t *)((uint8_t *)pHdr + eapolOffset);

    GTRACE(GRP_DRIVER_CC33, "Forward RX EAPOL to supplicant; RX len %d EAPOL offset %d header size %d ", packLen, eapolOffset, sizeof(TEthernetHeader));

    os_memset(&eventData, 0, sizeof(eventData));
    eventData.eapol_rx.data = pEapolBuff;
    eventData.eapol_rx.data_len = packLen;
    eventData.eapol_rx.src = pHdr->src;
    wpa_supplicant_event(pDrv->ctx, EVENT_EAPOL_RX, &eventData);

fail:
    // Supplicant doesn't free the EAPOL, so we do it after handling is completed
    RxBufFree(desc);

    HOOK(HOOK_IN_DRIVER_TI_WIFI);
    return;

}

// ----------------------------------------------------------------------------
void drv_lowAck(struct wpa_global *apGlobal, uint32_t aRoleId,
                uint16_t aInactiveLinksBits, Bool32 aMaxRetries)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    char macStr[MAC_STR_LEN];
    TMacAddr        pPeerAdd;
    uint32_t i, staBitsMask=1;
    ti_driver_ifData_t *pDrv;
    union wpa_event_data eventData;

    pDrv = getDriverForRoleId(aRoleId, apGlobal);
    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33, "NOTIFY: driver instance is invalid, ignoring low ack notification");
        return;
    }

    memset(&eventData, 0, sizeof(eventData));

    for (i=0 ; i < WLANLINKS_MAX_LINKS; ++i)
    {
        if (staBitsMask & aInactiveLinksBits)
        {
            //#TODO
            //txDataQ_GetMacFromLink(i, pPeerAdd);
            IRQ_UtilCopyMacAddress(pPeerAdd, eventData.low_ack.addr);

            GET_MAC_STR(pPeerAdd, macStr);
            GTRACE(GRP_DRIVER_CC33, "Low ack/max retries (%d) detected for link %d address %s", aMaxRetries,i, macStr);

            wpa_supplicant_event(pDrv->ctx, EVENT_STATION_LOW_ACK, &eventData);
        }

        staBitsMask <<= 1;
    }

    HOOK(HOOK_IN_DRIVER_TI_WIFI);
}


void drv_handleTxResult(void *desc)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    CmeTxDesc_t *pDesc = (CmeTxDesc_t *)desc;
    struct ieee80211_mgmt *pMngPack;
    uint16_t fc, type, stype;
    tiwdrv_if_mode_e netifMode;
    uint8_t netif;
    uint8_t roleId = ROLE_ID_NONE;
    Bool32 releaseDesc = TRUE;
    ti_driver_ifData_t     *pDrv;
    union wpa_event_data eventData;

    // After transmission address points to 802.11 header
    pMngPack = (struct ieee80211_mgmt *)pDesc->address;
    if(OK != wlanLinks_GetNetifInfo(pDesc->link, &netif, &netifMode))
       goto fail;

    switch(netifMode)
    {
        case TIWDRV_IF_MODE_STA:
        {
            roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_STA);
        }break;
        case TIWDRV_IF_MODE_SAP:
        {
            roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_AP);

        }break;
        case TIWDRV_IF_MODE_P2PDEV:
        {
            roleId = drv_getRoleIdFromType(gpSupplicantGlobals,(RoleType_e)ROLE_DEVICE);

        }break;

        default:
        {
            //TODO validate that on this scenario the txctrl packet is freef
            HOOK(HOOK_IN_DRIVER_TI_WIFI);

            /* it can be when response was recieved but the link was disconnected */
            TX_DATA_SEND_PRINT("\n\rdrv_handleTxResult : netif doesn't exists, means that role was stopped link:%d",pDesc->link);
            goto fail;
        }
    }
    if(roleId == ROLE_ID_NONE)
    {
        TX_PRINT_ERROR("\n\rWarning!drv_handleTxResult, role was already closed for netifMode:%d", netifMode);
    	goto fail;
    }

    // Extract transmitted packet type and verify it was a management packet
    fc = le_to_host16(pMngPack->frame_control);
    type = WLAN_FC_GET_TYPE(fc);
    stype = WLAN_FC_GET_STYPE(fc);

    pDrv   = getDriverForRoleId(roleId, gpSupplicantGlobals);

    if(pDrv == NULL)
    {
        TX_PRINT_ERROR("\n\rError!!drv_handleTxResult,no drive found roleId:%d type:%d stype:%d ",roleId,type,stype);
        goto fail;
    }

    // Supplicant handles TX results only for AP based roles
    // or DEVICE ROLE for off-channel
    if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType) || ROLE_IS_TYPE_DEVICE(pDrv->roleType))
    {

        //Since we add 4 bytes after the header before payload
        // for HT, we need to remove these when sending to supplicant
        // IEEE80211_HT_CTL_LEN = 4
        // WLAN_HDR_LEN = 24
        uint8_t *newPayload;
        uint32_t payloadLen = (pDesc->uHeaderLen + pDesc->uPayloadLen - IEEE80211_HT_CTL_LEN);
        newPayload = os_malloc(payloadLen);
        os_memcpy(newPayload, (uint8_t *)pDesc->address, WLAN_HDR_LEN);
        os_memcpy(newPayload + WLAN_HDR_LEN,
                  (uint8_t *)pDesc->address + WLAN_HDR_LEN + IEEE80211_HT_CTL_LEN,
                   payloadLen - WLAN_HDR_LEN );

        // Notify supplicant of TX result
        memset(&eventData, 0, sizeof(eventData));
        eventData.tx_status.type = type;
        eventData.tx_status.stype = stype;
        eventData.tx_status.ack = (1 == pDesc->status);
        eventData.tx_status.data = newPayload;
        eventData.tx_status.data_len = payloadLen;
        eventData.tx_status.dst = pMngPack->da;
        wpa_supplicant_event(pDrv->ctx, EVENT_TX_STATUS, &eventData);

        CME_FreeTxDesc(desc);

        os_free(newPayload);

        return;
    }


    // For STA based role, distribute the result to expecting CB
    switch (stype)
    {
        case WLAN_FC_STYPE_AUTH:
            releaseDesc = ti_drv_AuthReqCB(pDesc, pDrv);
            break;

        case WLAN_FC_STYPE_ASSOC_REQ:
        case WLAN_FC_STYPE_REASSOC_REQ:
            releaseDesc = ti_drv_AssocReqCB(pDesc, pDrv);
            break;

        case WLAN_FC_STYPE_DEAUTH:
            GTRACE(GRP_DRIVER_CC33, "TX deauth packet was completed with result %d", pDesc->status);

            //TX complete of a Deauth packet is handled separately (in a blocking manner) and we should not arrive here.
            ASSERT_GENERAL(FALSE);

            break;

        case WLAN_FC_STYPE_ACTION:
            GTRACE(GRP_DRIVER_CC33, "Action packet completed, releasing the packet");
            // in case we will need to hanle tx complete CB, right now we just release the packet
            releaseDesc = TRUE;
            break;

        default:
            HOOK(HOOK_IN_DRIVER_TI_WIFI);

            ASSERT_GENERAL(FALSE);
    }


    udata_SetRxState(pDesc->link, LINK_STATE_OPEN);
fail:
    if (TRUE == releaseDesc)
    {
        TX_PRINT_COMPLETE("\n\rdrv_handleTxResult CME_FreeTxDesc : 0x%x", (uint32_t)desc);
        CME_FreeTxDesc(desc);
    }

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    return ;
}

/* ----------------------------------------------------------------------------
 drv_sendConnectTimeoutEvent
    Send association/authentication timeout event to supplicant.
    Association timeout:
        activated when association timer expires or if received response is not
        complete (no rates IE).
    Authentication timeout:
        activated when authentication timer expires and number of auth retries
        exceeds maximal reties

 Parameters:    apDrv - pointer to driver instance
                aType - event type (association/authentication)
                apBssid - peer BSSID

 Return code:   none
---------------------------------------------------------------------------- */
void drv_sendConnectTimeoutEvent(ti_driver_ifData_t  *apDrv,
                                 enum wpa_event_type  aType,
                                     uint8_t         *apBssid)
{
    HOOK(HOOK_IN_DRIVER_TI_WIFI);

    char macStr[MAC_STR_LEN];
    union wpa_event_data event;

    GET_MAC_STR(apBssid, macStr);
    GTRACE(GRP_DRIVER_CC33,  "Connection timeout for %s, sending ENUM(wpaEventType_e, %d) to supplicant",
                              macStr, aType);

    CME_ROLE_PRINT_REPORT("\n\r drv_sendConnectTimeoutEvent, Send command CMD_ROLE_STOP %d wpaEventType_e: %d", 
        apDrv->roleId, aType);

    apDrv->ops->cancel_remain_on_channel(apDrv);

    if (FALSE != apDrv->roleStarted)
    {
        apDrv->ops->stop_role(apDrv);
    }


    // Notify CME (for black list update)
//  CME_InternalEventHandler(CME_MESSAGE_ID_AUTH_TIMEOUT, &apDrv->roleId);
    apDrv->connectTimeout = TRUE;

    // Notify supplicant connection attempt has timed out
    os_memset(&event, 0, sizeof(event));
    IRQ_UtilCopyMacAddress(apBssid, event.timeout_event.addr);

    wpa_supplicant_event(apDrv->ctx, aType, &event);

    HOOK(HOOK_IN_DRIVER_TI_WIFI);

} // drv_sendConnectTimeoutEvent




//============================================================================
//   P2P Related Driver API
//============================================================================

/* ----------------------------------------------------------------------------
 drv_handleGroupRole

 Parameters:    apDrv - pointer to driver instance of device type

 Return code:   none
---------------------------------------------------------------------------- */
void drv_handleGroupRole(struct wpa_supplicant *wpa_s, Bool_e isGroupRoleGo)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

    // wait for group started or group failure events
    gP2pGroupRoleType = NOT_IN_GROUP; 
  
    //send event to CME
    //in case we become Client -> need to change STA SM State
    CME_P2pNegConfirmation(pDrv->roleId, isGroupRoleGo);
}


//============================================================================
//   Notifications from supplicant
//============================================================================

#ifndef TI_STA_ONLY_BUILD
/* ----------------------------------------------------------------------------
 ti_driver_p2p_dev_found

 Parameters:


 Return code:   npne
---------------------------------------------------------------------------- */
void ti_driver_p2p_dev_found(struct wpa_supplicant *wpa_s, const uint8_t *peer_addr)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    const struct p2p_peer_info *info = p2p_get_peer_found(wpa_s->global->p2p, peer_addr, 0);
    GTRACE(GRP_DRIVER_CC33, "ti_driver: roleid=%d p2p_dev_found name=%s, group_capab=0x%x", 
                            pDrv->roleId, info->device_name, info->group_capab);

	uint8_t p2pCapabGroupOwnerBit = info->group_capab & 1; //bit0 in group capab info

    struct wpa_bss *bss = NULL;
    if (p2pCapabGroupOwnerBit)
    {
        bss = wpa_bss_get_p2p_dev_addr(wpa_s, info->p2p_device_addr);
    }

    if (pDrv->p2pConnectionStarted &&
        (IRQ_UtilCompareMacAddress(peer_addr, pDrv->p2pPeerAddr) ||
        (p2pCapabGroupOwnerBit && bss && IRQ_UtilCompareMacAddress(bss->bssid, pDrv->p2pPeerAddr))))
    {
        CME_PRINT_REPORT("\n\rdriver p2p_dev_found !");
        GTRACE(GRP_DRIVER_CC33, "ti_driver: desired peer found!");

        pDrv->p2pPeerCandidateIsFound = 1;
        //pDrv->p2pCapabGroupOwnerBit = IS_BIT_SET(info->group_capab, BIT_x(0)); // is set bit not working
        pDrv->p2pCapabGroupOwnerBit = p2pCapabGroupOwnerBit;
        GTRACE(GRP_DRIVER_CC33, "ti_driver: p2pCapabGroupOwnerBit=%d", pDrv->p2pCapabGroupOwnerBit);

        //When we about to Join an existing GO
        //we change interface type of device's parent
        if (pDrv->p2pCapabGroupOwnerBit == 1)
        {
            if (cme_is_sta_role_like_activated())
            {
                // Joining an existing GO would make us P2P Client.
                // STA + P2P Client is not a supported concurrent combination.
                // Stop the find immediately and notify the app - no need to wait for find timeout.
                GTRACE(GRP_DRIVER_CC33, "ti_driver: peer is existing GO but STA is active - aborting connect");
                CME_PRINT_REPORT_ERROR("\r\nti_driver: P2P client join rejected: STA role is active");
                cmeStopP2pFind(wpa_s);
                cmeP2pClearAll();
                wlanDispatcherSendEvent(WLAN_EVENT_P2P_GROUP_FORMATION_FAILED, NULL, 0);
                return;
            }
            drv_handleGroupRole(wpa_s, FALSE);
        }
        //Send message to CME that a desired peer found - to trigger connect command
        CME_P2pDevFound(pDrv->roleId);
    }
}
#endif // TI_STA_ONLY_BUILD

#ifndef TI_STA_ONLY_BUILD
/* ----------------------------------------------------------------------------
 ti_driver_go_neg_completed

 Parameters:


 Return code:   none
---------------------------------------------------------------------------- */
void ti_driver_go_neg_completed(struct wpa_supplicant *wpa_s,
                                struct p2p_go_neg_results *res)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    uint32_t roleId;

    CME_PRINT_REPORT("\n\rP2P neg completed status=%d  isGO=%d peer=" MACSTR, res->status, res->role_go, MAC2STR(res->peer_device_addr));
    GTRACE(GRP_DRIVER_CC33, "ti_driver_go_neg_completed: res.ssid=%s status:%d  isGO=%d peer=" MACSTR, 
            res->ssid, res->status, res->role_go, MAC2STR(res->peer_device_addr));

    if (res->status != 0)
    {
        GTRACE(GRP_DRIVER_CC33, "Negotiation Failed! status=%d", res->status);
        CME_PRINT_REPORT_ERROR("\r\nti_driver_go_neg_completed: GO negotiation failed, status=%d", res->status);
        cmeP2pClearAll();
        wlanDispatcherSendEvent(WLAN_EVENT_P2P_GROUP_FORMATION_FAILED, NULL, 0);
        return;
    }
    //Negotiation was successful 
    if (res->role_go == TRUE)
    {
        gP2pGroupRole = P2P_GROUP_ROLE_GO;
    }
    else
    {
        gP2pGroupRole = P2P_GROUP_ROLE_CLIENT;
    }

    drv_handleGroupRole(wpa_s, res->role_go);
}
#endif

#ifndef TI_STA_ONLY_BUILD
/* ----------------------------------------------------------------------------
 ti_driver_p2p_find_stopped

 Parameters:


 Return code:   none
---------------------------------------------------------------------------- */
void ti_driver_p2p_find_stopped(struct wpa_supplicant *wpa_s)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

    GTRACE(GRP_DRIVER_CC33, "ti_driver: p2p_find_stopped! gP2pSearchStopping=%d", gCmeP2pInfo.p2pFindStopping);
    CME_PRINT_REPORT("\n\rp2p find stopped. gP2pSearchStopping=%d", gCmeP2pInfo.p2pFindStopping);
    gCmeP2pInfo.p2pFindStopping = TRUE;
 
    if (pDrv->p2pPeerCandidateIsFound == 0)
    {
        // we didn't find any peer candidate and search is timeout
        // mark that connection is stopped
        if (pDrv->p2pConnectionStarted == TRUE)
        {
            // Notify application that P2P peer was not found during find timeout
            GTRACE(GRP_CME, "P2P find timed out - peer not found, notify host");
            CME_PRINT_REPORT("\n\rP2P find timed out - peer not found, notify host");
            wlanDispatcherSendEvent(WLAN_EVENT_P2P_PEER_NOT_FOUND, (void*)NULL, 0);
            gCmeP2pInfo.p2pConnectPending = FALSE;
        }
        pDrv->p2pConnectionStarted = FALSE;
    }

}
#endif
#ifndef TI_STA_ONLY_BUILD
/* ----------------------------------------------------------------------------
 ti_driver_p2p_group_formation_failure

 Parameters:

 Return code:   none
---------------------------------------------------------------------------- */
void ti_driver_p2p_group_formation_failure(struct wpa_supplicant *wpa_s)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    uint32_t roleId;

    //clean bit. connection stopped with failure
    CME_PRINT_REPORT("\n\r ti_driver : P2P Group Formation FAILED roleid=%d, roleType = %d, if_name = %s",
        pDrv->roleId, pDrv->roleType, wpa_s->ifname);
    GTRACE(GRP_DRIVER_CC33, "ti_driver: P2P Group Formation FAILED roleid=%d, roleType = %d, if_name = %s",
        pDrv->roleId, pDrv->roleType, wpa_s->ifname);

    // need to stop all running p2p related processes
    // in case when P2P CL role is up and scanning - stop scan
    if (ROLE_IS_TYPE_P2P_CLIENT(pDrv->roleType))
    {
        drv_stopConnectionScans(wpa_s);
    }
    //event to app that group formation failed
    wlanDispatcherSendEvent(WLAN_EVENT_P2P_GROUP_FORMATION_FAILED, NULL, 0);
}
#endif // TI_STA_ONLY_BUILD

#ifndef TI_STA_ONLY_BUILD
/* ----------------------------------------------------------------------------
 ti_driver_p2p_group_started

 Parameters:

 Return code:   none
---------------------------------------------------------------------------- */
void ti_driver_p2p_group_started(struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid, uint8_t client)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    
    gP2pGroupRoleType = (client == 0)?GO_IN_GROUP:CLIENT_IN_GROUP;

    CME_PRINT_REPORT("\n\r ti_driver: P2P Group Started roleid=%d is %s, group ssid %s, wpaState=%d gP2pGroupRoleType=%d", 
        pDrv->roleId, (client == 0)?"GO":"Client", ssid->ssid, wpa_s->wpa_state, gP2pGroupRoleType);
    if (wpa_s->go_params != NULL) 
    {   
        GTRACE(GRP_DRIVER_CC33, "ti_driver: P2P Group Started freq=%d status=%d peer if_addr=%02x:%02x:%02x:%02x:%02x:%02x", 
            wpa_s->go_params->freq, wpa_s->go_params->status,
            wpa_s->go_params->peer_interface_addr[0], wpa_s->go_params->peer_interface_addr[1], wpa_s->go_params->peer_interface_addr[2],
            wpa_s->go_params->peer_interface_addr[3], wpa_s->go_params->peer_interface_addr[4], wpa_s->go_params->peer_interface_addr[5]);
    }

    if (client == 0) //GO Role
    {
        GTRACE(GRP_DRIVER_CC33, "ti_driver: P2P Group Started roleid=%d is GO, ssid=%s, ssid->mode=%d p=%s, >> notify host>> ",
            pDrv->roleId, ssid->ssid, ssid->mode, ssid->passphrase);

        pDrv->ssid_len = ssid->ssid_len;
        os_memcpy(pDrv->ssid, ssid->ssid, ssid->ssid_len);

        CmeP2pGroupStartedNotify(wpa_s, pDrv->macAddr, TRUE);
    }
    else
    {
        GTRACE(GRP_DRIVER_CC33, "ti_driver: P2P Group Started roleid=%d is Client",
            pDrv->roleId);
        if (CmeStationFlowIsSMIdle())
        {
            if (0 != CmeStationFlowSM(CME_STA_NETWORK_SEARCH_EVENT, CmeStationFlow_GetCurrentUser()))
            {
                GTRACE(GRP_CME,"CME: ERROR: CmeStationFlowSM tried to set state managed in STA flow SM and failed!! ");
                CME_PRINT_REPORT_ERROR("\r\nCME: ERROR: CmeStationFlowSM tried to set state managed in STA flow SM and failed!! ");
                ASSERT_GENERAL(0);
            }
        }
        
    }
}
#endif

#ifndef TI_STA_ONLY_BUILD
/* ----------------------------------------------------------------------------
 ti_driver_p2p_group_removed

 Parameters:

 Return code:   none
---------------------------------------------------------------------------- */
void ti_driver_p2p_group_removed(struct wpa_supplicant *wpa_s)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    RoleType_e roleType = pDrv->roleType;

    CME_PRINT_REPORT("\n\r P2P Group REMOVED roleType:%d gP2pGroupRoleType=%d gP2pGroupRole=%d",roleType, gP2pGroupRoleType, gP2pGroupRole);
    GTRACE(GRP_DRIVER_CC33, "ti_driver: P2P Group REMOVED roleid=%d roleType=%d, wpa_s=%p",
            pDrv->roleId, roleType, wpa_s);

    gP2pGroupRoleType = NOT_IN_GROUP;
    gP2pGroupRole = P2P_GROUP_ROLE_NONE;

    //init p2p module globals
    gCmeP2pInfo.p2pFindStopping = FALSE;
    gCmeP2pInfo.p2pConnectPending = FALSE;

    // release connection related flags on device role
    cmeP2pClearAll();
        
    //notify host that group was removed
    CmeP2pGroupRemovedNotify(roleType);
}
#endif

//-----------------------------------------------------------------------------------------//


const struct wpa_driver_ops wpa_driver_ti_ops =
{
	.name = "ti_wifi",

    // Roles shared APIs
	.init2  = ti_driver_if_init,
    .deinit = ti_driver_deinit,

    .get_capa   = ti_driver_get_capa,
    .get_ext_capab   = ti_driver_get_ext_capa,
	.set_key    = ti_driver_set_key,

	.get_hw_feature_data = ti_driver_get_hw_feature_data,
	.get_mac_addr = ti_driver_get_mac_addr,

    .set_country = ti_driver_set_country,
    .get_country = ti_driver_get_country,
    .send_action = ti_driver_send_action,
    .send_action_cancel_wait = ti_driver_send_action_cancel_wait,

    // Scan related APIs
	.scan2 = ti_driver_one_shot_scan,
    .get_scan_results2 = ti_driver_get_scan_results,
    .sched_scan = ti_driver_sched_scan,
    .stop_sched_scan = ti_driver_stop_sched_scan,
    .abort_scan = ti_driver_abort_scan,

    // STA based only section
    .authenticate = ti_driver_authenticate,
    .deauthenticate = ti_driver_deauthenticate,
    .associate = ti_driver_associate,
    .get_bssid = ti_driver_get_bssid,
    .get_ssid = ti_driver_get_ssid,
    .add_pmkid = ti_driver_add_pmkid,


    // P2P & STA based
    .remain_on_channel = ti_driver_start_remain_on_channel,
    .cancel_remain_on_channel = ti_driver_stop_remain_on_channel,
    .if_add = ti_driver_if_add,
    .probe_req_report = ti_driver_probe_req_report,

    // AP only section (code resides in drv_cc33_ap_specific.c)
#ifdef CONFIG_AP
    .set_ap = ti_driver_set_ap,
    .set_freq = ti_driver_set_channel,
    .set_tx_queue_params = ti_driver_set_tx_queue_params,
    .set_rts = ti_driver_set_rts,
    .deinit_ap = ti_driver_deinit_ap,
    //.hapd_set_ssid = ti_driver_hapd_set_ssid, // This is redundant since SSID is set also in set_ap API
    .sta_add = ti_driver_sta_add,
    .sta_set_flags = ti_driver_sta_set_flags,
    .sta_remove = ti_driver_sta_remove,
    .sta_deauth = ti_driver_sta_deauth,
    .sta_disassoc = ti_driver_sta_disassoc,
    .hapd_send_eapol = ti_driver_hpad_send_eapol,
    .get_inact_sec = ti_driver_inact_sec,
    .poll_client = ti_driver_poll_client,
#endif
    .send_mlme = ti_driver_send_mgmt_frame,
};
