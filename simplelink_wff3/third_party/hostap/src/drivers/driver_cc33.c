/*
 * hostapd / Driver interaction with TI CC3300 driver
 * Copyright (c) 2010, Texas Instruments, Inc. - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name(s) of the above-listed copyright holder(s) nor the
 *  names of its contributors may be used to endorse or promote products
 *  derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "os.h"

#include "utils/eloop.h"
#include "utils/common.h"
#include "common/ieee802_11_defs.h"
#include "common/defs.h"

#include "driver.h"

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
#include "scan.h"


#include "scan_result_table.h"
#include "l2_cfg.h"
#include "drv_ti_internal.h"
#include "fw_utils.h"

#include "bss.h"
#include "cme_supplicant_api.h"
#include "cme_dispatcher_api.h"
#include "cme_internal_api.h"
#include "cme_fw_api.h"
#include "cme_defs.h"
#include "802_11defs.h"


#include "debug_assert.h"

#include "mpdu.h"
#include "80211_utils.h"
#include "regulatory_domain_api.h"
#include "common.h"

#include "driver/drv_core.h"
#include "cc3xxx_public_commands.h"
#include "rx.h"
// ============================================================================
//      Modules private definitions
// ============================================================================

// ----------------------------------------------------------------------------
// start if debug info section


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

// end of ebug info section
// ----------------------------------------------------------------------------

// Device capabilities - ToDo - should be replaced with regulatory domain API
#define CC33_NUM_SUPPORTED_BANDS    (2)

// Supported channels, currently this is hard coded in the macros below
// ToDo - should be taken from regulatory domain module
const uint8_t gHwConfigChannlesBG[] = PERIODIC_SCAN_CHANNELS_ARRAY_B_G_BAND;
const uint8_t gHwConfigChannlesA[] = PERIODIC_SCAN_CHANNELS_ARRAY_A_BAND;


// ============================================================================
//      Modules globals
// ============================================================================

// Globals holding the pointer to the driver data for the specific interface.
// Needed only to l2_packet interface implementation since this module does not have any access to the supplicant
// internal data. It only gets interface name.
// TODO: if needed in future, it can be implemented as a translation table between interface name and the pointer.

ti_driver_ifData_t *gpCc33xxDriverIfDataSta  = NULL; //TIWLAN_DEV_NAME_STA
ti_driver_ifData_t *gpCc33xxDriverIfDataAp   = NULL; //TIWLAN_DEV_NAME_SAP


// ----------------------------------------------------------------------------
// Debug code
#ifdef CC33XX_DRIVER_DEBUG
cc33drv_debugInfo_t gSuppDrvDebugInfo_ull ;
#endif
// Debug code
// ----------------------------------------------------------------------------

extern int mx_driver_send_scan_stop_cmd (uint32_t roleID, EScanRequestType scanRequestType, Bool_e isET);

// ============================================================================
//		Local Functions declarations
// ============================================================================

static int32_t buildSingleModeCapability(RoleType_e aRoleType,
                                       Bool32 aUseUll,
                                       struct hostapd_hw_modes *apHwMode);

static int  setDriverCapabilities(ti_driver_ifData_t *apDrv);
static int 	enableRole(ti_driver_ifData_t *apDrv, RoleType_e role_type);

static int initPeriodicScanParams(ti_driver_ifData_t 	 		 *apDrv,
								  scanRequestParams_t 		 	 *apScanParams,
								  struct wpa_driver_scan_params  *apSuppParams);

static int kickOneshotConnectionScan(ti_driver_ifData_t *apDrv,
                                 struct wpa_driver_scan_params *apParams);

static int p2pSearch(ti_driver_ifData_t *apDrv,
				     struct wpa_driver_scan_params *apParams);



static void sendRxAuthEvent(ti_driver_ifData_t  *apDrv,
                            struct ieee80211_mgmt *apMngPack,
                            uint32_t                aPackLen);
static void sendRxAssocEvent(ti_driver_ifData_t *apDrv,
                             struct ieee80211_mgmt *apMngPack,
                             uint32_t                aPackLen);

int cc33_driver_send_scan_stop_cmd (ti_driver_ifData_t *apDrv, EScanRequestType scanRequestType);

// ============================================================================
//      Local services APIs
// ============================================================================

// ----------------------------------------------------------------------------
#if 0
ti_driver_ifData_t * getDriverForRoleId(uint32_t aRoleId, struct wpa_global *apGlobal)
{
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

    // cc33xx supports 2 roles at most. If first role doesn't match role ID
    // check for a second role.
    if (NULL != wpa_s->next)
    {
        wpa_s = wpa_s->next;
        pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

        if (NULL == pDrv)
            return NULL;

        if (pDrv->roleId == aRoleId)
            return pDrv;
    }

    ASSERT_GENERAL(0);
    return NULL;
}
#endif
// ============================================================================
//      Supplicant APIs
// ============================================================================
extern int mx_driver_enable_role (ti_driver_ifData_t *apDrv, RoleType_e aRoleType);
extern int mx_driver_disable_role (ti_driver_ifData_t *apDrv);
extern int8_t mx_driver_set_link_connection_state (uint8_t lid, LinkState_e linkConnectionState);
/* ----------------------------------------------------------------------------
 cc33_driver_if_init
      This function initializes a new interface when a new role is activated.

 Parameters:    ctx - pointer to wpa_s
                ifname - interface name, indicates role type
                global_private - used to keep driver info on wpa_s, unused

 Return code:   0 - on success, -1 - failure in sanity tests
---------------------------------------------------------------------------- */
#ifdef TI_DEPRICATED
void *cc33_driver_if_init(void *ctx, const char *ifname, void *global_priv)
{
    ti_driver_ifData_t *pDrv;

    GTRACE(GRP_DRIVER_CC33, "Init supplicant driver: ifname = %s", ifname);

#ifdef CC33XX_DRIVER_DEBUG
    memset(&gSuppDrvDebugInfo_ull, 0, sizeof(cc33drv_debugInfo_t));
#endif

    pDrv = os_zalloc(sizeof(ti_driver_ifData_t));
    if (0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_STA)))
    {
        gpCc33xxDriverIfDataSta = pDrv; //saved just for l2_packet interface implementation
    }
    else if(0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_SAP)))
    {
        gpCc33xxDriverIfDataAp = pDrv; //saved just for l2_packet interface implementation
    }
    // ToDo - handle the P2P option, ASSERT_GENERAL for the meantime
    else
    {
        ASSERT_GENERAL(FALSE);
    }

    if (NULL == pDrv)
    {
        GTRACE(GRP_GENERAL_ERROR, "Init supplicant driver: Could not allocate memory for cc3300 driver interface data");
        return NULL;
    }

    GTRACE(GRP_DRIVER_CC33, "Init supplicant driver: allocated %d bytes (GLX %d) for cc3300 driver interface data",
                                  sizeof(ti_driver_ifData_t), pDrv->isGlx);

    pDrv->ops = device_cmd_ops[0];

    // Keep received parameters
    pDrv->wpa_s = ctx;
    pDrv->ctx = ctx;
    os_memcpy(pDrv->iface, ifname, sizeof(pDrv->iface));

    // Extract role type from interface name
    pDrv->roleType = drv_getDrvRoleType(pDrv);

    // Mark role wasn't enabled nor started yet
    // need to implement
    pDrv->roleId = ROLE_ID_NONE;
    pDrv->roleStarted = FALSE;
    pDrv->roleEnabled = FALSE;

    // Set default capabilites on driver data base
    setDriverCapabilities(pDrv);

    if (ROLE_TYPE_NONE != pDrv->roleType)
    {
        GTRACE(GRP_DRIVER_CC33, "Assigned driver role ENUM(RoleType_e, %d) to the interface", pDrv->roleType);

        //if (mx_driver_enable_role(pDrv, pDrv->roleType))
        if(pDrv->ops->enable_role(pDrv, pDrv->roleType))
        {
            GTRACE(GRP_GENERAL_ERROR, "ERROR: Init supplicant driver: enable role failed");
            os_free(pDrv);
        }
    }

    // Reset RSN DB
    rsn_init();
    scan_result_table_init();
    regulatoryDomain_init();

    return pDrv;
}
#endif
/* ----------------------------------------------------------------------------
 cc33_driver_deinit
      This function de-initializes an interface when a role is terminated.

 Parameters:    apPriv - pointer to private driver DB

 Return code:   0 - on success, -1 - failure in sanity tests
---------------------------------------------------------------------------- */
extern  OsiSyncObj_t            ScanResultTableSyncObj_ull;

void cc33_driver_deinit(void *apPriv)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    if (NULL == pDrv)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: NULL driver pointer");
        ASSERT_GENERAL(0);
        return;
    }

    GTRACE(GRP_DRIVER_CC33, "Deinit driver_cc33 role ID %d type ENUM(RoleType_e,%d)",
                             pDrv->roleId, pDrv->roleType);


    // Now that role is down, it is the time for memory cleanup
    //   STA role: free driver's ULL DB
    //   AP role:  release beacon descriptor & probe response memory
    //             free driver's GLC DB
    if (FALSE != ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
    {
        // Note: STA role is already stopped at this point. Once disabled scan
        // requets can't be served anymore.

        // Role disable blocks until role is disabled in all SW modules, including
        // WLAN services & data path.
        // When it returns, it is safe now to free driver memory.
        // Note that activating context may by blocked for few msecs until closure
        // confirmation is received from all modules.
        //mx_driver_disable_role(pDrv);
        pDrv->ops->disable_role(pDrv);

        // Verify the dynamically allocated members were released; if not, this
        // is the last chance ...
        // This is needed for the use case of enabled but not started role where
        // allocated memory wasn't set yet to
        os_free(pDrv);
        gpCc33xxDriverIfDataSta = NULL;
    }
    else // AP based role
    {
        // Removing AP interface flow:
        //      o CME initiates remove interface sequence upon host commnad
        //      o supplicant flushes all STAs by sending a multicast deauth packet
        //      o supplicant cancels any active scan
        //      o supplicant activates the driver_deinit API
        // Implementation limitations:
        //      o Stopping AP role is allowed only after transmission of deauth packet
        //      o Due to the above, sending deauth is blocking, till tx complete.


        //TODO: role should already be stoped. Should it be checked here, and if not perform stop?
//        // Note: AP role is still active, have to stop it before disabling the role
//        drv_cc33_StopApRole(pDrv->roleId);

        // Role disable blocks until role is disabled in all SW modules, including
        // WLAN services & data path.
        // When it returns, it is safe now to free driver memory.
        // Note that activating context may by blocked for few msecs until closure
        // confirmation is received from all modules.
        //mx_driver_disable_role(pDrv);
        pDrv->ops->disable_role(pDrv);

        os_free(pDrv);
        gpCc33xxDriverIfDataAp = NULL;

        // ============== Delete sync object ======================== //
        if(OSI_OK != osi_SyncObjDelete(&ScanResultTableSyncObj_ull))
        {
            GTRACE(GRP_GENERAL_ERROR, "cc33_driver_deinit: FAILED to delete sync object ");
            ASSERT_GENERAL(0);
        }
        ScanResultTableSyncObj_ull = NULL;
    }
}

/* ----------------------------------------------------------------------------
 cc33_driver_get_capa
      This function retruns driver capabilities to supplicant

 Parameters:    IN  apPriv - pointer to private driver DB
                OUT apCaba - pointer to driver capabilities

 Return code:   0 - on success, -1 - driver wasn't initialized yet
---------------------------------------------------------------------------- */
int cc33_driver_get_capa(void *apPriv, struct wpa_driver_capa *apCapa)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    if (NULL == pDrv)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: NULL driver pointer");
        return -1;
    }

    os_memcpy(apCapa, &pDrv->capa, sizeof(*apCapa));
    return 0;
}

/* ----------------------------------------------------------------------------
 cc33_driver_set_key
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

 ToDo - complete functionality
---------------------------------------------------------------------------- */
int cc33_driver_set_key(const char *ifname, void *apPriv, enum wpa_alg alg,
                               const u8 *addr, int key_idx, int set_tx,
                               const u8 *seq, size_t seq_len,
                               const u8 *key, size_t key_len)
{

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    securityKeys_t secKey;

    if ( (ROLE_TYPE_NONE == pDrv->roleType) || ROLE_IS_TYPE_DEVICE(pDrv->roleType) )
        return 0;

/* **************************
 * Important:
 *      The code below this point should be optimized and short as possible till we perform the actual set key in FW.
 *      This is to minimize the time between the transmission of the last eapol of the 4 way handshake, in STA role,
 *      (performed by the supplicant before the call to cc33_driver_set_key()); and the actual set key,
 *      in order to prevent a race condition where the AP sends us an encripted packet, before we set the encription key.
 * **************************/
    //No debug messages here, for speed optimization (set key ASAP after last eapol was send).
    //Enable Only for debug!!
    GTRACE(GRP_DRIVER_CC33_DEBUG, "Set keys: alg %d, key index %d, seq len %d, key len %d, set TX %d",
                                   alg, key_idx, seq_len, key_len, set_tx);

    if (MAX_KEYS_NUM <= key_idx)
    {
        // Should not happen; start w/ ASSERT_GENERAL, if happens try to understand the scenario - ToDo
        ASSERT_GENERAL(FALSE);
        return -1;
    }

    memset(&secKey, 0, sizeof(secKey));

    if (NULL != addr)
    {
        IRQ_UtilCopyMacAddress(addr, secKey.macAddress);
    }
    // else, macAddress is zeroed by the memset above

    if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
        uint8_t lid;

        if (MAC_BROADCAST(secKey.macAddress)) //AP Broadcast
        {
            // need to implement peer ID
            //lid = Roles_GetBroadcastFlid(pDrv->roleId);
            secKey.lidKeyType = KEY_TYPE_BROADCAST;
        }
        else //Peer linkId
        {
            // need to implement peer ID
            //lid = MAT_SearchPeerId(secKey.macAddress);
            secKey.lidKeyType = KEY_TYPE_UNICAST;
        }

        if (lid == 0xFF)
        {
            //TODO: temp - address 0 with default key (set both broadcast and unicast?)
            //TODO: temp - remove when scenario is understood.
            if ((!MAC_EQUAL (secKey.macAddress, "\x0\x0\x0\x0\x0\x0")) &&
                (alg != WPA_ALG_NONE) &&
                (key_len > 0))
            {
                ASSERT_GENERAL (FALSE);
            }
            return -1;

        }

        secKey.lid = lid;
        secKey.keyType  = alg;
        secKey.keyIndex = key_idx;
        secKey.encLen = key_len;

        if ((alg == WPA_ALG_NONE) || (0 == key_len) )
        {
            rsn_removeKey(&secKey);
        }
        else
        {

            if (WPA_ALG_IGTK == alg)
            {
                // ToDo- same as in driver_wilink
                return -1;
            }


            if ((WPA_ALG_WEP == alg) && (set_tx))
            {
                /* WEP not supported */
                return -1;

//                GenParams.lValue = secKey.keyIndex;
//                wilink_send_ti_private_cmd(drv,TI_PARAM_AP_SET_DEFAULT_KEY, TIWDRV_CMD_SET_FLAG,
//                                          TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenParams,sizeof(GenParams));
            }

            if (WPA_ALG_TKIP == alg)
            {
                /* TKIP not supported */
                return -1;

//                os_memcpy((secKey.encKey+24),(key+16),8);
//                os_memcpy(secKey.micTxKey,(key+16),8);
//                os_memcpy(secKey.micRxKey,(key+24),8);
//                os_memcpy((secKey.encKey+16),(key+24),8);
//                os_memcpy(&secKey.encKey,key,16);
            }
            else
            {
                os_memcpy(secKey.encKey, key, key_len);
            }

            rsn_addKey(&secKey);
        }
    }
    else /* Role station or P2P client*/
    {
        // need to implement roles
        uint8_t lid = 0;//Roles_GetMainLinkId(pDrv->roleId);

        // --------------------------------------------------------------------
        // The code below was imported from wilink_driver
        secKey.keyType  = alg;
        secKey.encLen = key_len;
        os_memcpy(secKey.encKey, key, key_len);

        if (seq && seq_len && (seq_len <= KEY_RSC_LEN))
        {
        
#ifdef CC33XX_DRIVER_DO_NOT_TAKE_KEY_RSC_IN_BROADCAST_SET_KEY
            if (!MAC_BROADCAST(secKey.macAddress)) //not broadcast (unicast) so take the RSC
            {
                os_memcpy(secKey.keyRsc, seq, seq_len);
            }//in case of broadcast do not take the RSC. (RSC set to zero in the begining of the function)

#else
            os_memcpy(secKey.keyRsc, seq, seq_len);
#endif
        }
        secKey.keyIndex = key_idx;
        secKey.lid = lid;

        if (MAC_BROADCAST(secKey.macAddress))
        {
            secKey.lidKeyType = KEY_TYPE_BROADCAST;
        }
        else
        {
            secKey.lidKeyType = KEY_TYPE_UNICAST;
        }

        // --------------------------------------------------------------------
        // The code below was imported from rsn.c, rsn_setParam, TI_PARAM_ADD_KEY

        /* Reset the security sequence number only for unicat re-key */
//        if (!MAC_BROADCAST(secKey.macAddress))
//        {
            // ToDo
//            wlanLinks_ResetLinkSecuritySeqNum(pRsn->hWlanLinks, hlid);
//        }

        // Remove the key when the length is 0, or the type is not set
        if ( (WPA_ALG_NONE == alg) || (0 == key_len) )
        {
            rsn_removeKey(&secKey);
        }
        // Otherwise set the key
        else
        {
            rsn_addKey(&secKey);
        }
        // The code above was imported from rsn.c, rsn_setParam, TI_PARAM_ADD_KEY
        // --------------------------------------------------------------------
        }
//For debug...
#if 0
    if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
        GTRACE(GRP_DRIVER_CC33, "RoleAP");
    }
    else
    {
        GTRACE(GRP_DRIVER_CC33, "RoleSTA");
    }

    wpa_hexdump(MSG_DEBUG, "Addr", addr, MAC_ADDR_LEN);
    wpa_hexdump(MSG_DEBUG, "PN number", seq, seq_len);
    wpa_hexdump(MSG_DEBUG, "AES Key", key, key_len);
#endif


    return 0;


} // cc33_driver_set_key

/* ----------------------------------------------------------------------------
 cc33_driver_get_hw_feature_data
      This function reprots driver capabilities to supplicant.
      This includes supported bands and channels, HT capabilities.

 Parameters:    IN  apDrv - Pointer to driver object
                OUT apNumModes - Pointer to number of supported modes
                OUT apFlags - Pointer to flags, set to 0 as in MCP
 Return code:   On success - pointer to driver parameters
                On failure - NULL
---------------------------------------------------------------------------- */
struct hostapd_hw_modes * cc33_driver_get_hw_feature_data(void *apPriv,
                                                          u16  *apNumModes,
                                                          u16  *apFlags, u8 *apDfs)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    uint32_t m, numModes = 0;
    uint32_t supportedBandsBM = 0xFF;// need to implemnt cfgGetSupportedBands();
    struct hostapd_hw_modes *pHwModes;

    // Calculate number of supported bands
    while (supportedBandsBM)
    {
        if (supportedBandsBM & 1)
        {
            ++numModes;
        }
        supportedBandsBM = supportedBandsBM >> 1;
    }

    pHwModes = os_zalloc(numModes * sizeof(struct hostapd_hw_modes));

    if (NULL == pHwModes)
    {
        GTRACE(MSG_ERROR, "ERROR: failed to allocate memory for HW modes");
        return NULL;
    }

    // ToDo - have to use regulatory domain results in order to select mode

    // Configure the supported rates
    supportedBandsBM = 0xff; // need to implement cfgGetSupportedBands();
    for (m=0; m<numModes ; ++m)
    {
        switch (m)
        {
            case RADIO_BAND_2_4GHZ:
                pHwModes[m].mode = HOSTAPD_MODE_IEEE80211G;
                break;

            case RADIO_BAND_5GHZ:
                pHwModes[m].mode = HOSTAPD_MODE_IEEE80211A;
                break;

            // Note that RADIO_BAND_JAPAN_4_9_GHZ is also defined but not handled yet
            default:
                ASSERT_GENERAL(FALSE);
        }

        // need to implement
#if 0
        buildSingleModeCapability(pDrv->roleType, pDrv->wpa_s->use_ull_memory, &pHwModes[m]);
#endif
        // ToDo - do we need to take special care for channel 14 as in MCP? check w/ Maital
    }

    *apNumModes = numModes;
    *apFlags = 0;
    return pHwModes;
}

/* ----------------------------------------------------------------------------
 cc33_driver_get_mac_addr
      Supply role's MAC address to supplicant

 Parameters:    apPriv - pointer to private driver DB
 Return code:   pointer to locak MAC address
---------------------------------------------------------------------------- */
const u8 * cc33_driver_get_mac_addr(void *apPriv)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    return pDrv->macAddr;
}

#if 0
/* ----------------------------------------------------------------------------
 cc33_driver_state_changed
     This function is used to notify L2 driver connection state changes.
     CME is notified when L2 connection is established or when L2 disconnects.

 Parameters:    apDrv - pointer to drive instance
                new_state - new L2 state
                old_state - old L2 state

 Return code:   0
---------------------------------------------------------------------------- */
void cc33_driver_state_changed(struct wpa_supplicant *wpa_s,
                   enum wpa_states new_state,
                   enum wpa_states old_state)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

    // This API serves the CME STA connection manager, for AP role there's
    // nothing to do here.
    if (ROLE_IS_TYPE_AP(pDrv->roleType))
    {
        return;
    }

    GTRACE(GRP_DRIVER_CC33,"wpa_s->wpa_state=%d, new_state=%d, old_state=%d, pDrv->roleStarted=%d",wpa_s->wpa_state,new_state,old_state,pDrv->roleStarted);

    //If we are out of scanning, and we are after 'wpa_select_network (called by cme connection manager)', we should zero this flag.
    //if we are out of scanning in other cases (i.e. WPS), it does not matter and we can zero this flag anyway.
    if (old_state == WPA_SCANNING)
    {
        wpa_s->cc33xx_initiated_select_network = 0;
    }

    // Filter disconnect (or other?) events while in WPS, or the first disconnect after a successful WPS for 'fast connect' via supplicant
    if ((CME_IsOngoingWPSAdHocConnection()) || (gWPSfirstDisconnect_ull==TRUE))
    {
        if (WPA_DISCONNECTED == new_state)
        {
            //Filter WPS first disconnect
            //TODO: - Do we want to send a different disconnect event to the CME and it will filter it?
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
            return;
        }
    }

#ifdef CC33XX_DRIVER_DEBUG
    // This is just for forcing disconnect during different connection stages
    // ToDo - remove once CME SM is defined as fully tested
    if ( (WPA_COMPLETED != wpa_s->wpa_state) && (wpa_s->wpa_state == gSuppDrvDebugInfo_ull.sta.gForceDisconnectState) )
    {
        GTRACE(GRP_DRIVER_CC33, "Forcing disconnect for state %d", gSuppDrvDebugInfo_ull.sta.gForceDisconnectState);
        CME_WlanDisconnect(FALSE);

        // Clear the disconnection constraint
        gSuppDrvDebugInfo_ull.sta.gForceDisconnectState = 100;
    }
#endif



    if (WPA_COMPLETED == new_state)
    {
        // In case of 4 way handshake, ignore the second WPA_COMPLETED event
        if (FALSE == pDrv->connected)
        {
            uint32_t apLink;

            pDrv->connected = TRUE;

            // need to implement roles
            apLink = 0;//Roles_GetMainLinkId(pDrv->roleId);

            // activate SetLinkState which sets WMM and calls the below.
            // In cc33xx FW manages WMM state so setting WMM is irrelevant.
            mx_driver_set_link_connection_state(apLink, LINK_STATE_CONNECTED);

            // Notify RSN module
            rsn_setPortStatus(pDrv->roleId, 1);

            cc33_driver_cancel_remain_on_channel(pDrv);


            GTRACE(GRP_DRIVER_CC33, "Calling  CME_NotifyStaConnectionState. - new state WPA_COMPLETED ");

            CME_NotifyStaConnectionState(pDrv->roleId, TRUE, 0);

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
            cc33_driver_stop_security_mgmt_seq(pDrv->roleId);
        }
    }
    // Transition from connected to disconnected (may be reconnecting or scanning)
    else if ( (WPA_ASSOCIATED <= old_state) && (new_state < WPA_ASSOCIATED) )
    {
        pDrv->connected = FALSE;
        pDrv->connectTimeout = FALSE;

        // Notify RSN module, it will forward the new state to data path
        rsn_setPortStatus(pDrv->roleId, 0);

        //If we reached here, role should already be stopped
        ASSERT_GENERAL (FALSE == pDrv->roleStarted);

//        if (FALSE == pDrv->roleStarted)
        {
            GTRACE(GRP_DRIVER_CC33, "Calling  CME_NotifyStaConnectionState. - new state < WPA_ASSOCIATED ");

            CME_NotifyStaConnectionState(pDrv->roleId, FALSE, pDrv->deauthReason);
        }

    }
    // Disconnection during connection sequence
    else if (  (WPA_DISCONNECTED == new_state) &&
               ((WPA_ASSOCIATING == old_state) || (WPA_AUTHENTICATING == old_state)) /*&&
               (TRUE == pDrv->roleStarted)*/
            )
    {
        // Error, CME can release its memory
        CME_ReleaseScanResults();

        finalizeStaDisconnect(pDrv, __LINE__);
        GTRACE(GRP_DRIVER_CC33, "Calling  CME_NotifyStaConnectionState. - Disconnection during connection ");
        CME_NotifyStaConnectionState(pDrv->roleId, FALSE, pDrv->deauthReason);
    }
    //sta is associated
    else if (WPA_ASSOCIATED == new_state)
    {

        // Done using scan results, CME can release its memory
        CME_ReleaseScanResults();
    }
    else if (    (new_state == WPA_4WAY_HANDSHAKE)
              && (old_state == WPA_COMPLETED)
            )
    {
        //this transition means Rekey starts and therefore start mgmt sequence for it
        //and request to be in active mode
        cc33_driver_start_security_mgmt_seq(pDrv->roleId);
    }
    else if (new_state <= WPA_INACTIVE)
    {
        CME_ReleaseScanResults(); // Clean any leftovers anyway

        if (old_state == WPA_SCANNING)
        {
            CmeStationFlowSM(CME_STA_SCAN_DONE, CmeStationFlow_GetCurrentUser());
        }
    }
}

#endif

/* ----------------------------------------------------------------------------
 cc33_driver_wps_success
     This function notifies that WPS was successfull

 Parameters:    struct wpa_supplicant *wpa_s

 Return code:   0
---------------------------------------------------------------------------- */
void cc33_driver_wps_success(struct wpa_supplicant *wpa_s)
{
    GTRACE(GRP_DRIVER_CC33, "CC33 Driver - WPS event Success");
    CME_ClearWPSAdHocConnection();
    gWPSfirstDisconnect_ull = TRUE; //Disregard the next supplicant disconnect event since it is genarated internaly by the supplicant which is about to perform fast connect with the new credentials.
}

/* ----------------------------------------------------------------------------
 cc33_driver_wps_fail
     This function notifies that WPS process failed

 Parameters:    struct wpa_supplicant *wpa_s

 Return code:   0
---------------------------------------------------------------------------- */
void cc33_driver_wps_fail(struct wpa_supplicant *wpa_s)
{
    GTRACE(GRP_DRIVER_CC33, "CC33 Driver - WPS event Fail");
    //CME_ClearWPSAdHocConnection();
}

/* ----------------------------------------------------------------------------
 cc33_driver_wps_cleared
     This function notifies that WPS process was cleared, either due tue timeout or cancelletion

 Parameters:    struct wpa_supplicant *wpa_s

 Return code:   0
---------------------------------------------------------------------------- */
void cc33_driver_wps_cleared(struct wpa_supplicant *wpa_s)
{
    GTRACE(GRP_DRIVER_CC33, "CC33 Driver - WPS Cleared");

    CME_WlanDisconnect(FALSE);

    CME_ReleaseScanResults(); //Make sure we don't have any leftovers from previous scan.

    CME_ClearWPSAdHocConnection();

    //gil - potential bug fix
   // wpa_supplicant_set_state(wpa_s, WPA_INACTIVE);


}

/* ----------------------------------------------------------------------------
 cc33_driver_wps_credential
     This function pass the credentials of the new network after a successfull WPS negotiation.
     Assumption: This function is called after the supplicant processed internally the credentials so we have the parameters
                 available in wpa_s->current_ssid (used in cmeAddWpsCredentials2PreferredNetworks).

 Parameters:    struct wpa_supplicant *wpa_s
                const struct wps_credential *cred

 Return code:   0
---------------------------------------------------------------------------- */
void cc33_driver_wps_credential(struct wpa_supplicant *wpa_s, const struct wps_credential *cred)
{
    int16_t status;

    GTRACE(GRP_DRIVER_CC33, "CC33 Driver - WPS Credentials received, auth type: %d, enc type: %d", cred->auth_type, cred->encr_type);

    status = cmeAddWpsCredentials2PreferredNetworks(wpa_s, cred);

    if (status >=0 )
    {
        GTRACE(GRP_DRIVER_CC33, "CC33 Driver - WPS Credentials, Add profile success, index = %d", status);
        gCmeLastWlanProfileIdx = status;
    }
    else
    {
        GTRACE(GRP_DRIVER_CC33, "CC33 Driver - WPS Credentials, Add profile failed, status = %d", status);
    }
}

/* ----------------------------------------------------------------------------
 cc33_driver_set_country
      Set country to regulatory domain

 Parameters:    apPriv - pointer to private driver DB
                apCountry - pointer to country to be set
 Return code:   0 - success indication
---------------------------------------------------------------------------- */
int cc33_driver_set_country(void *apPriv, const char *apCountry)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    GTRACE(GRP_DRIVER_CC33, "Set country to %s", apCountry);

    pDrv->countryUpdated = TRUE;

    ASSERT_GENERAL(FALSE);

    // ToDo:
    //   - how do we get the country in CC? didn't find any reference in cc3100
    //   - do we have to define a new API for the regulatory domain module which is equivalent to regulatoryDomain_setParam
    //     in cc3100 the MCP driver doesn't support setting the regulatory domain from supplicant.

    return 0;
}

/* ----------------------------------------------------------------------------
 cc33_driver_send_action
      This function sends an action frame to LTXP.

 Parameters:    apPriv - pointer to private driver DB

 Return code:   0 - OK, -1 - failure
---------------------------------------------------------------------------- */
//Todo: this function was not tested yet.
int cc33_driver_send_action(void *apPriv,
                            unsigned int aFreq,         // ignored
                            unsigned int aWaitTime,     // ignored
                            const u8 *apDst,            // Destination address
                            const u8 *apSrc,            // Source address: ignored - deduced from role id
                            const u8 *apBssid,          // BSSID:          ignored - deduced from role id
                            const u8 *apData,
                            size_t aDataLen,
                            int    aNoCck)              // ignored
{
    return -1;
    // need to implement
#if 0
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    CC33_FrameTxDesc_t      *pDescriptor;
    struct  ieee80211_mgmt  *pMngPack;
    char   macStr[MAC_STR_LEN];
    uint8_t descId;
    int32_t rc;
    ltxpSendFrameRequest_t sendReq;

    GTRACE(GRP_DRIVER_CC33, "Sending %d byte action frame to %s", aDataLen, GET_MAC_STR(apDst, macStr));

    rc = cc33drv_AllocAndConfigMngPack(pDrv->roleId, aDataLen, FRAME_TYPE_ACTION, FALSE, &descId, &pMngPack, &pDescriptor, &sendReq);
    if (rc < 0)
    {
        return -1;
    }

    // Copy payload & fill MAC address
    os_memcpy((void *)sendReq.address, apData, aDataLen);

    sendReq.pDestAddr = apDst;

    LtxpSend_SwGenerated(&sendReq);

    return 0;
#endif
}

// The below serves for verifying EAPOL packets were actually transmitted
#ifdef ENABLE_EAPOL_TX_EXCHANGE
void cc33_driver_eapol_tx_result(const uint8_t aDescId)
{
    struct CC33_FrameTxDesc_s *pDesc = (struct CC33_FrameTxDesc_s *) MMU_GET_VIRTUAL_ADDR_FROM_DESC(aDescId);

    GTRACE(GRP_DRIVER_CC33, "EAPOL TX done: status ENUM(TX_status_e, %d)", pDesc->tx_state_status.tx_status);
}
#endif

/* ----------------------------------------------------------------------------
 cc33_driver_send_l2_data
      This function sends an l2 data frame to LTXP.
      802.11 is constructed here, LXTP should not change the packet.

 Parameters:    pDrv - pointer to private driver DB
                dst_addr - destination address
                proto - l2 protocol used
                *pData - data
                dataLen
                Bool_e forceUnsecure - Send the packet with no encryption

 Return code:   0 - OK, -1 - failure
---------------------------------------------------------------------------- */
int cc33_driver_send_l2_data(ti_driver_ifData_t *pDrv,
                           const u8 *dst_addr,
                           u16 proto,
                           const u8 *pData,
                           size_t dataLen)
{
    return -1;
    // need to implement
#if 0
    uint32_t rc;
    ltxpSendFrameRequest_t sendReq;

    GTRACE(GRP_DRIVER_CC33, "Sending L2 data packet; role ID %d packet size %d ether type 0x%x",
                           pDrv->roleId, dataLen, proto);

    rc = cc33drv_AllocAndConfigTXDataPack(pDrv->roleId,
                                          pData,
                                          dataLen,
                                          &sendReq);
    if (TXC_RETURN_CODE_SUCCESS != rc)
        return -1;

    sendReq.etherType = proto;
    sendReq.pDestAddr = dst_addr;

    LtxpSend_SwGenerated(&sendReq);

    return 0;

#endif
}



#if 0
/* ----------------------------------------------------------------------------
 cc33_driver_send_eapol
      This function sends an action frame to LTXP.
      802.11 is constructed here, LXTP should not change the packet.

 Parameters:    apPriv - pointer to private driver DB

 Return code:   0 - OK, -1 - failure
---------------------------------------------------------------------------- */
int cc33_driver_send_eapol(void *apPriv,
                           const u8 *apDst,
                           u16 aProto,
                           const u8 *apData,
                           size_t aDataLen)
{
    uint32_t rc;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    ltxpSendFrameRequest_t sendReq;

    GTRACE(GRP_DRIVER_CC33, "Sending EAPOL packet; role ID %d packet size %d ether type 0x%x",
                           pDrv->roleId, aDataLen, aProto);

    rc = cc33drv_AllocAndConfigTXDataPack(pDrv->roleId,
                                          apData,
                                          aDataLen,
                                          &sendReq);
    if (TXC_RETURN_CODE_SUCCESS != rc)
        return -1;

    sendReq.etherType = aProto;
    sendReq.pDestAddr = apDst;

#ifdef ENABLE_EAPOL_TX_EXCHANGE
    // Just to make sure EAPOL was acknowledge
    sendReq.callback = (uint32_t)cc33_driver_eapol_tx_result;
    sendReq.callback_msi = 0;
    sendReq.release_frame = TRUE;
#endif

    LtxpSend_CcDriver(&sendReq);

    return 0;
}
#endif


/* ----------------------------------------------------------------------------
 cc33_driver_get_scan_results
      This API is used by supplicant to get last scan detected networks.

Parameters:  apPriv - pointer to private driver DB
 Return:     pointer to networks list; memory is allocated here and released
             by supplicant after results are taken.
---------------------------------------------------------------------------- */
struct wpa_scan_results * cc33_driver_get_scan_results(void *apPriv)
{
    Bool_e is_fast_connect = (CME_STA_FAST_CONNECT_USER == CmeStationFlow_GetCurrentUser());
    uint32_t i;
    uint32_t numCandidates = gCandidatesInfo.numCandidates;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    struct wpa_scan_results *pSupplicantResults = NULL;

    GTRACE(GRP_DRIVER_CC33, "Num connection candidates %d, is fast connection %d, num BSS in priority list %d",
                            numCandidates, is_fast_connect, pDrv->wpa_s->num_bss);

    // New cc33xx functionality: clear previous scan results from supplicant DB
    // in order to force supplicant to select a new result for the new connection.
    wpa_bss_flush(pDrv->wpa_s);

    // Note: this API must allocate memory and return a valid wpa_scan_results
    // to supplicant even if scan results list is empty. Otherwise, a periodic
    // scan shall not be triggered !!!
    pSupplicantResults = (struct wpa_scan_results *)os_zalloc(sizeof(struct wpa_scan_results));
    if (!pSupplicantResults)
    {
        _ASSERT(NULL != pSupplicantResults); //TODO: Debug
        return (NULL);
    }

    if (numCandidates)
    {
        pSupplicantResults->res = (struct wpa_scan_res **)os_zalloc(numCandidates * sizeof(struct wpa_scan_res *));
        if (!pSupplicantResults->res)
        {
            os_free (pSupplicantResults);
            _ASSERT(NULL != pSupplicantResults->res); //TODO: Debug
            return (NULL);
        }
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
        // TODO: Debug code, remove after integarting scan full path
        uint8_t* pIe;
        char ssid[SSID_MAX_LEN];
        char macStr[MAC_STR_LEN];

        memset(ssid, 0, SSID_MAX_LEN);
        // Debug code, remove after integarting scan full path
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

    return pSupplicantResults;
}





/* ----------------------------------------------------------------------------
 cc33_driver_if_add
      This API adds a new interface either by application (i.e. CME) or
      internally for example for P2P when negotiation ends.

 Parameters:
 Return code:   0 - parameters OK, -1 - error indication
---------------------------------------------------------------------------- */
int cc33_driver_if_add(void *apPriv, enum wpa_driver_if_type type,
                              const char *ifname, const u8 *addr, void *bss_ctx,
                              void **drv_priv, char *force_ifname, u8 *if_addr,
                              const char *bridge, int use_existing, int setup_ap)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    GTRACE(GRP_DRIVER_CC33, "Add new interface: type = %d, ifname=%s",type, ifname);

    switch(type)
    {
        case WPA_IF_AP_BSS:
        case WPA_IF_AP_VLAN:
            os_strlcpy(force_ifname, NETIF_NAME(TIWLAN_DEV_NAME_SAP), IFNAMSIZ);
            break;
        case WPA_IF_P2P_CLIENT:
        case WPA_IF_P2P_GO:
        case WPA_IF_P2P_GROUP:
            /* we need the p2p-group interface up to get its mac addr */
//            (void)linux_set_iface_flags(drv->drv_global->cmd_sock, NETIF_NAME(TIWLAN_DEV_NAME_P2PGROUP), 1);
            os_strlcpy(force_ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2P), IFNAMSIZ);
            break;
        case WPA_IF_STATION:
            os_strlcpy(force_ifname, NETIF_NAME(TIWLAN_DEV_NAME_STA), IFNAMSIZ);
            break;
        default:
            GTRACE(GRP_GENERAL_ERROR, "ERROR inadding an unknown if type: %d, ifname=%s", type, ifname);
            return -1;
    }

    if (addr)
    {
        IRQ_UtilCopyMacAddress(addr, if_addr);
    }
    else
    {
        // need to implement roles
        //uint8_t *pAddress = Roles_GetLocalMacFromRoleId(pDrv->roleId);
        uint8_t pAddress[6] = {0xFF, 0xFF, 0xFF,0xFF,0xFF,0xFF};
        IRQ_UtilCopyMacAddress(pAddress, if_addr);
    }

    return 0;
}

/* ----------------------------------------------------------------------------
 cc33_send_mgmt_frame
      This function sends a management packet directly to data path
      The wlan header will be constructed by the ltxp layer. The payload is taken as is from the supplicant.

 Parameters:    apPriv - pointer to private driver DB
                apData - pointer to 802.11 header of the packet
                aDataLen - packet length including 802.11 header
                aNoAck - if TRUE - no 802.11 ack is expected for this packet
                         hence excessive retries may be avoided
                freq -  Frequency (in MHz) to send the frame on, or 0 to let the driver decide
                csa_offs - Array of CSA offsets or %NULL
                csa_offs_len - Number of elements in csa_offs

 Return code:   0 on success, -1 on failure (illegal parameters)
---------------------------------------------------------------------------- */
//TODO: - handle freq and csa_offs parameters?
int cc33_send_mgmt_frame(void *apPriv,
                         const u8 *apData,
                         size_t aDataLen,
                         int aNoack,
                         unsigned int freq,
                         const u16 *csa_offs,
                         size_t csa_offs_len)
{

    return -1;
    // need to implement
#if 0
    char   macStr[MAC_STR_LEN];
    uint8_t  descId;
    uint32_t allocSize;
    int32_t  rc;
    CC33_FrameTxDesc_t    *pDescriptor;
    ti_driver_ifData_t  *pDrv = (ti_driver_ifData_t *)apPriv;
    struct ieee80211_mgmt *pMngPack;
    ltxpSendFrameRequest_t sendReq;

    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: NULL driver pointer");
        ASSERT_GENERAL(0);
        return -1;
    }

    if (aDataLen < WLAN_HDR_LEN)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: Bad len");
        ASSERT_GENERAL(0);
        return -1;
    }

    //TODO:: Add some spare bytes (for encrypted header)
    allocSize = CC33_DRV_PAYLOAD_START_OFFSET + CC33_DRV_PACKET_FOOTER_SIZE + (aDataLen - WLAN_HDR_LEN); //aDataLen already includes the header len
    rc = TxcAllocateNoWaitRequest(CC33_DRIVER_MMU_ALLOC_MASTER_TYPE,    // [in ] CC33xx master ID
                                  allocSize,                            // [in ] Allocation size, in bytes, for the entire thing
                                  MMU_ALLOC_OPCODE_ALLOCATE,            // [in ] Opcode = ALLOC (as opposed to REALLOC or DEALLOC)
                                  MMU_POOL_TYPE_MNGMT,                  // [in ] Pool ID from which to allocate (TX/RX/MNG)
                                  &descId,                              // [out] -> CC33xx virtual descriptor index
                                  0);                                   // [in ] Reallocated descriptor index - irrelevant for ALLOCATE
    if (rc != TXC_RETURN_CODE_SUCCESS)
    {
        GTRACE(GRP_GENERAL_ERROR,
               "ERROR: failed to allocate %d bytes for management packet",
               allocSize);
        return -1;
    }

    pMngPack = (struct ieee80211_mgmt *)apData;

    // ------------------------------------------------------------------------
    // Allocation succeeded
    //  o Set packet information on the send request structure
    //  o Construct payload
    // ------------------------------------------------------------------------

    pDescriptor = (struct CC33_FrameTxDesc_s *) MMU_GET_VIRTUAL_ADDR_FROM_DESC(descId);

    sendReq.address = (uint32_t) ((uint8_t *) pDescriptor + CC33_DRV_PAYLOAD_START_OFFSET);
    sendReq.frame = pDescriptor;
    sendReq.frame_type = (uint8_t) pMngPack->frame_control;
    sendReq.payload_length = aDataLen - WLAN_HDR_LEN;
    sendReq.release_frame = FALSE;
    sendReq.role_id = pDrv->roleId;
    sendReq.callback = (uint32_t)CME_TxResult;
    sendReq.callback_msi = (uint32_t)pDrv;
    sendReq.etherType = ETHER_TYPE_INVALID;
    sendReq.expiry_duration_us = TX_NO_EXPIRY;
    sendReq.pDestAddr = (uint8_t *)pMngPack->da;
    sendReq.retriesLimit    = LTXP_TX_RETRIES_DEFAULT_LIMIT;
    sendReq.rate_ovr = RATE_OVR_DISABLED;

    // Copy the supplicant packet payload to the allocated buffer
    os_memcpy((void *)sendReq.address, apData + WLAN_HDR_LEN, aDataLen - WLAN_HDR_LEN);

    GET_MAC_STR(pMngPack->da, macStr);
    GTRACE(GRP_DRIVER_CC33, " Sending management frame: desc ID 0x%x payload address 0x%x fc 0x%x # bytes %d dest %s aNoack %d",
                              descId, sendReq.address, pMngPack->frame_control, (aDataLen - WLAN_HDR_LEN), macStr, aNoack);

    LtxpSend_SwGenerated(&sendReq);

    return 0;
#endif
}

/* ----------------------------------------------------------------------------
 cc33_driver_remain_on_channel
      This function sends a ROC request to WLAN services and blocks until
      command handling is completed.

 Parameters:    apPriv - pointer to private driver DB
                aFreq - indicates the channel to remain on
                aDuration - time to remain on channel, unused. See note below.

 ToDo - the duration parameter is redundant (not used in WL8 FW).
 It is kept in MCP P2P DB and sent to supplicant in the remain on channel event.
 Supplicant doesn't use this parameter. Currently it is not saved. Can we ommit it?

 Return code:   0 - OK, role found -1 - else
---------------------------------------------------------------------------- */
int cc33_driver_remain_on_channel(void *apPriv, unsigned int aFreq, unsigned int aDuration)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    ROCParameters_t cmdParams;
    CommandParam_t cmd;

    cmd.cmdID = CMD_REMAIN_ON_CHANNEL;




    if (freq_to_chan(aFreq, &cmdParams.Channel, &cmdParams.Band))
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: failed to get channel from freq %d for role %d",
                                       aFreq, pDrv->roleId);
        return -1;
    }

#ifdef CC33XX_DRIVER_DEBUG
    ++gSuppDrvDebugInfo_ull.sta.numRoc;
#endif
    cmdParams.roleID = pDrv->roleId;
#ifdef CC33XX_DRIVER_DEBUG
    GTRACE(GRP_DRIVER_CC33, "Remain on channel %d for role %d num so far %d",
                             cmdParams.Channel, pDrv->roleId, gSuppDrvDebugInfo_ull.sta.numRoc);
#else
    GTRACE(GRP_DRIVER_CC33, "Remain on channel %d for role %d",
                             cmdParams.Channel, pDrv->roleId);
#endif

    os_memcpy(cmd.param, (void *)&cmdParams, sizeof(cmdParams));
    // Send the command and wait blocking for response.
    // When the below returns, ROC sequence is completed.
    // TODO: send command
    //CME_SendCmd2WlanServices(&cmd);

    // Mark ROC was activated by driver
    pDrv->rocActive = TRUE;

    return 0;
}

/* ----------------------------------------------------------------------------
 cc33_driver_cancel_remain_on_channel
      This function sends a CROC request to WLAN services, we don't wait for
      command completion. When function returns CROC command wasn't actually
      handled.

 Parameters:    apPriv - pointer to private driver DB

 Return code:   0
---------------------------------------------------------------------------- */
int cc33_driver_cancel_remain_on_channel(void *apPriv)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    ROCParameters_t cmdParams;
    CommandParam_t cmd;

    cmd.cmdID = CMD_CANCEL_REMAIN_ON_CHANNEL;
    cmdParams.roleID = pDrv->roleId;



#ifdef CC33XX_DRIVER_DEBUG
    ++gSuppDrvDebugInfo_ull.sta.numCroc;
    GTRACE(GRP_DRIVER_CC33, "Cancel remain on channel for role %d, num so far %d",
                             pDrv->roleId, gSuppDrvDebugInfo_ull.sta.numCroc);
#else
    GTRACE(GRP_DRIVER_CC33, "Cancel remain on channel for role %d",
                             pDrv->roleId);
#endif
    os_memcpy(cmd.param, (void *)&cmdParams, sizeof(cmdParams));
    // TODO: Send command
    //CME_SendCmd2WlanServices(&cmd);

    // Mark ROC was deactivated by driver
    pDrv->rocActive = FALSE;

    return 0;
}


/* ----------------------------------------------------------------------------
 cc33_driver_start_security_mgmt_seq
      This function sends a Start Security Mgmt Sequence request to WLAN services
      and blocks until command handling is completed.

 Parameters:    aRoleId - Role ID

  Return code:   0 - OK, role found -1 - else
---------------------------------------------------------------------------- */
int cc33_driver_start_security_mgmt_seq(RoleID_t    aRoleId)
{
    StartMgmtSeqParameters_t cmdParams;
    CommandParam_t cmd;

    cmd.cmdID = CMD_START_SECURITY_MGMT_SEQ;
    cmdParams.roleID = aRoleId;

    os_memcpy(cmd.param, (void *)&cmdParams, sizeof(cmdParams));
    GTRACE(GRP_DRIVER_CC33, "start security mgmt sequence for role %d",
           aRoleId);

    // Send the command and wait blocking for response.
    // When the below returns, MGMT Sequence is started.
    // TODO: need to implement send command
    //CME_SendCmd2WlanServices(&cmd);

    return 0;
}

/* ----------------------------------------------------------------------------
 cc33_driver_stop_security_mgmt_seq
      This function sends a Stop Security Mgmt Sequence request to WLAN services
      and blocks until command handling is completed.

 Parameters:    aRoleId - Role ID

  Return code:   0 - OK, role found -1 - else
---------------------------------------------------------------------------- */
int cc33_driver_stop_security_mgmt_seq(RoleID_t     aRoleId)
{
    StartMgmtSeqParameters_t cmdParams;
    CommandParam_t cmd;

    cmd.cmdID = CMD_STOP_SECURITY_MGMT_SEQ;
    cmdParams.roleID = aRoleId;

    os_memcpy(cmd.param, (void *)&cmdParams, sizeof(cmdParams));
    GTRACE(GRP_DRIVER_CC33, "stop security mgmt sequence for role %d",
           aRoleId);

    // Send the command and wait blocking for response.
    // When the below returns, MGMT Sequence is stopped.
    // TODO: need to implement send command
    //CME_SendCmd2WlanServices(&cmd);

    return 0;
}


// ----------------------------------------------------------------------------
static int32_t buildSingleModeCapability(RoleType_e aRoleType,
                                       Bool32 aUseUll,
                                       struct hostapd_hw_modes *apHwMode)
{
    return -1;
    // need to implement
#if 0
    uint8_t  *pChanList;
    uint32_t basicRatesBM, supportedRatesBM;
    uint32_t i, freqBase;
    Bool32 htSupported;
    int    rates[DOT11_MAX_SUPPORTED_RATES];
    const htCapabilities_t *pHtCap = NULL;

    switch (apHwMode->mode)
    {
        case HOSTAPD_MODE_IEEE80211A:
            // Get supported rates & remove B rates
            cfgGetRates(aRoleType, &basicRatesBM, &supportedRatesBM);
            supportedRatesBM = supportedRatesBM & ~ANY_B_RATE;

            apHwMode->num_rates = convertBitmapToSupplicantRates(supportedRatesBM, rates);

            // ToDo - channels should be taken from regulatory domain module
            apHwMode->num_channels = sizeof(gHwConfigChannlesA);
            pChanList = (uint8_t *)&gHwConfigChannlesA;
            freqBase = BASE_FREQ_5_0;
            break;

        case HOSTAPD_MODE_IEEE80211G:
            cfgGetRates(aRoleType, &basicRatesBM, &supportedRatesBM);

            apHwMode->num_rates = convertBitmapToSupplicantRates(supportedRatesBM, rates);

            // ToDo - channels should be taken from regulatory domain module
            apHwMode->num_channels = sizeof(gHwConfigChannlesBG);
            pChanList = (uint8_t *)&gHwConfigChannlesBG;
            freqBase = BASE_FREQ_2_4;
            break;

        case HOSTAPD_MODE_IEEE80211B:
            // Get supported rates & remove OFDM rates
            cfgGetRates(aRoleType, &basicRatesBM, &supportedRatesBM);
            supportedRatesBM = supportedRatesBM & ~ANY_AG_OFDM_RATE;

            apHwMode->num_rates = convertBitmapToSupplicantRates(supportedRatesBM, rates);

            // ToDo - channels should be taken from regulatory domain module
            apHwMode->num_channels = sizeof(gHwConfigChannlesBG);
            pChanList = (uint8_t *)&gHwConfigChannlesBG;
            freqBase = BASE_FREQ_2_4;
            break;

        default:
            return -1;
    }

    htSupported = cfgGetHtCapabilities(&pHtCap);
    if (htSupported)
    {
        os_memset(apHwMode->mcs_set, 0, 16);
        os_memcpy(apHwMode->mcs_set, pHtCap->suppMcsSet.rxMscBitmask, RX_MCS_BITMASK_SIZE);
        os_memcpy(&apHwMode->mcs_set[RX_MCS_BITMASK_SIZE], &(pHtCap->suppMcsSet.highestSupportedDataRate), RX_HIGHEST_SUPP_DATA_RATE_BM_SIZE);
        os_memcpy(&apHwMode->mcs_set[RX_MCS_BITMASK_SIZE+RX_HIGHEST_SUPP_DATA_RATE_BM_SIZE], &(pHtCap->suppMcsSet.txSettingBM), sizeof(pHtCap->suppMcsSet.txSettingBM));

        apHwMode->ht_capab = pHtCap->htCapabBM;
        apHwMode->a_mpdu_params = *((uint8_t *)&pHtCap->ampduCfg);
    }

    apHwMode->channels = os_zalloc(sizeof(struct hostapd_channel_data) * (apHwMode->num_channels)) ;

    if (NULL == apHwMode->channels)
    {
        GTRACE(MSG_ERROR, "ERROR: failed to allocate memory for channels info");
        return -1;
    }

    for (i=0; i<apHwMode->num_channels; ++i)
    {
        apHwMode->channels[i].chan = pChanList[i];
        apHwMode->channels[i].freq = apHwMode->channels[i].chan*5 + freqBase;
        apHwMode->channels[i].max_tx_power = 0;  // ToDo - needed for AP role,
                                                 // have to take this one from regulatory domain (?)

        // the below is imported from MCP for 40MHz channel, as it is not
        // supported code is commented out
//        if (apHwMode->ht_capab & HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET)
//        {
//            apHwMode->channels[i].flag |= HOSTAPD_CHAN_HT40;
//            if (pChanList[i].flags & TIW_REG_DOMAIN_HT40PLUS)
//                apHwMode->channels[i].flag |= HOSTAPD_CHAN_HT40PLUS;
//            if (pChanList[i].flags & TIW_REG_DOMAIN_HT40MINUS)
//                apHwMode->channels[i].flag |= HOSTAPD_CHAN_HT40MINUS;
//        }

        if (apHwMode->channels[i].chan == 14)
            apHwMode->channels[i].freq = FREQ_CH_14;
    }

    apHwMode->rates = os_zalloc(sizeof(struct hostapd_rate_data) * (apHwMode->num_rates));

    if (NULL == apHwMode->rates)
    {
        GTRACE(MSG_ERROR, "ERROR: failed to allocate memory for rates info");
        return -1;
    }

    for (i=0; i<apHwMode->num_rates; ++i)
    {
        apHwMode->rates[i] = rates[i];
    }

    return 0;
#endif
}

// ----------------------------------------------------------------------------
static int p2pSearch(ti_driver_ifData_t *apDrv,
		  		     struct wpa_driver_scan_params *apParams)
{

    // ToDo - when implementing don't forget to update scan type using SET_ONE_SHOT_OS_SCAN macros
    ASSERT_GENERAL(FALSE);

	return 0;
}



// ============================================================================
// 	API for CME commands & notifications
// ============================================================================

// ----------------------------------------------------------------------------
RoleType_e cc33drv_getStaIface(struct wpa_global *apGlobal, struct wpa_supplicant **apIface)
{
    RoleType_e roleType = ROLE_TYPE_NONE;
    struct wpa_supplicant *wpa_s;
    ti_driver_ifData_t *pDrv;

    // API may be called when there's no active supplicant interface.
    // Expected mainly for irrelevant driver commands, still we shouldn't crush.
    //
    // Dec 29 2016 - supoort no role transition
    //
    if (apGlobal==NULL || NULL == apGlobal->ifaces)
        return ROLE_TYPE_NONE;

    wpa_s = apGlobal->ifaces;
    pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

    if (ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
    {
        roleType = pDrv->roleType;
    }
    else
    // cc33xx supports 2 roles at most. If first role isn't a STA based role,
    // check if there's another role.
    {
        if (NULL != wpa_s->next)
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
    return roleType;
}

// ----------------------------------------------------------------------------
struct wpa_supplicant * cc33drv_getIfaceFromRoleID(struct wpa_global *apGlobal,
                                                  uint32_t aRoleID)
{
    struct wpa_supplicant *wpa_s;
    ti_driver_ifData_t *pDrv;

    // Go over all valid interfaces and verify netIf is related to a valid one
    wpa_s = apGlobal->ifaces;
    while (NULL != wpa_s)
    {
        pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
        if (aRoleID == pDrv->roleId)
            return wpa_s;

        wpa_s = wpa_s->next;
    }

    ASSERT_GENERAL(0);
    return NULL;
}

// ----------------------------------------------------------------------------
int cc33drv_getRoleIdFromType(struct wpa_global *apGlobal,RoleType_e roleType)
{
    int roleid= ROLE_ID_NONE;
    struct wpa_supplicant *wpa_s;
    ti_driver_ifData_t *pDrv;

    wpa_s = apGlobal->ifaces;
    pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

    if (roleType == ROLE_STA)
    {
        if (ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
        {
            roleid = pDrv->roleId;
        }
        else
        // cc33xx supports 2 roles at most. If first role isn't a STA based role,
        // check if there's another role.
        {
            if (NULL != wpa_s->next)
            {
                wpa_s = wpa_s->next;
                pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

                if (ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
                {
                    roleid = pDrv->roleId;
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
        // cc33xx supports 2 roles at most. If first role isn't a AP based role,
        // check if there's another role.
        {
            if (NULL != wpa_s->next)
            {
                wpa_s = wpa_s->next;
                pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

                if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
                {
                    roleid = pDrv->roleId;
                }
            }
        }
    }
    else
    {
        ASSERT_GENERAL(0);
    }

    return roleid;
}

// ----------------------------------------------------------------------------
#if 0
ti_driver_ifData_t * cc33_driver_bss_loss(uint32_t aRoleId, struct wpa_global *apGlobal)
{
    struct wpa_supplicant *wpa_s;
    ti_driver_ifData_t *pDrv;

    wpa_s = apGlobal->ifaces;
    pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

    // NLCP behavior:
    // Register a 4.5 seconds delayed disconnect from peer & notify supplicant
    // finalizeStaDisconnect(pDrv, WLAN_FC_STYPE_DEAUTH, WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY, TRUE);

    // Notify driver_nl80211, nl80211_cqm_event, NL80211_CQM_RSSI_BEACON_LOSS_EVENT
    // A start_roaming event is sent to supplican, this starts a one shot scan for roaming purpose.

    return pDrv;
}
#endif

// ----------------------------------------------------------------------------
void cc33drv_handleScanCompleteEvent(void *apDrv, EScanRequestType aScanType, uint32_t aNumResults)
{
	ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apDrv;
	union wpa_event_data eventData;

	ASSERT_GENERAL(ROLE_TYPE_NONE != pDrv->roleType);

	os_memset(&eventData, 0, sizeof(eventData.scan_info));

	// If periodic scan, clear scan indication on supplicant DB.
    // wpa_supplicant code clears this indication only for stop scan command.
	if (SCAN_REQUEST_CONNECT_PERIODIC_SCAN == aScanType)
	{
	    pDrv->wpa_s->sched_scanning = 0;
	}
	else
	{
	    // For one shot scan, clear the completed scan indication on driver DB
	    if (SCAN_REQUEST_ONE_SHOT == aScanType)
	    {
	        CLEAR_ONE_SHOT_OS_SCAN(pDrv);
	    }
	    else
	    {
	        CLEAR_ONE_SHOT_APP_SCAN(pDrv);
	    }
	}

	// Event is sent for both
	eventData.scan_info.nl_scan_event = 1; //Normal scan
	wpa_supplicant_event(pDrv->ctx, EVENT_SCAN_RESULTS, &eventData);
}

// ----------------------------------------------------------------------------
void cc33drv_handleOneShotScanStoppedEvent(struct wpa_supplicant *wpa_s,EScanRequestType    scanType)
{
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
void cc33drv_handleScanStoppedEvent(void *apDrv)
{
	ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apDrv;

	GTRACE(GRP_DRIVER_CC33, "Scheduled scan was stopped");
	wpa_supplicant_event(pDrv->ctx, EVENT_SCHED_SCAN_STOPPED, NULL);

	// Nov 23 2015 - force supplicant inactive state as state machine will not be invoked anymore
	wpa_supplicant_set_state(pDrv->wpa_s, WPA_INACTIVE);
}

void cc33drv_handleUnprotRxDeauth (uint32_t aDescriptorId)
{
    return;
    // need to implement
#if 0
    uint32_t                  roleId = 0;
    uint16_t                  fc, stype;
    CC33_FrameRxDesc_t      *pDesc;
    union wpa_event_data    eventData;
    struct ieee80211_mgmt   *pMngPack;
    ti_driver_ifData_t    *pDrv;

    pDesc = (struct CC33_FrameRxDesc_s *)MMU_GET_VIRTUAL_ADDR_FROM_DESC(aDescriptorId);

    // Check if packet is from the current session
    if (!cc33_RxFrame_CheckSessionIsValid(pDesc))
    {
        GTRACE(GRP_DRIVER_CC33, "NOTIFY: Received mng packet is from previous session, dropping packet");
        TxcReleaseDeAllocRequestPush(aDescriptorId);
        return;
    }
    // First extact basic information from descriptor
    roleId = pDesc->link_role.role_id;
    pDrv = getDriverForRoleId(roleId, gpSupplicantGlobals);
    pMngPack = (struct ieee80211_mgmt *)pDesc->address;

    // Handle management packet
    fc = le_to_host16(pMngPack->frame_control);
    stype = WLAN_FC_GET_STYPE(fc);

    eventData.unprot_disassoc.reason_code = pMngPack->u.deauth.reason_code;

    eventData.unprot_disassoc.sa = pMngPack->sa;
    eventData.unprot_disassoc.da = pMngPack->da;

    GTRACE(GRP_MGMT_PROTECTION_IMP, "MPF: unprotected deauth/deassoc %d, send EVENT to supplicant", stype);

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

    TxcReleaseDeAllocRequestPush(aDescriptorId); //relase frane after supplicant event is sent
#endif
}

#if 0
extern int cc3xxx_trnspt_cmd_if_check_scan_tagged_frame(CC33_FrameRxDesc_t *frame);
#endif
// ----------------------------------------------------------------------------
#if 0

void cc33drv_handleRxMngPacket(uint32_t aDescriptorId)
{
	uint16_t fc, type, stype;
	uint32_t packLen;
	uint32_t roleId = 0;
	rxMngPackNextOperation_e rc;
	CC33_FrameRxDesc_t       *pDesc;
    ti_driver_ifData_t     *pDrv;
	struct ieee80211_mgmt    *pMngPack;

    pDesc = (struct CC33_FrameRxDesc_s *)MMU_GET_VIRTUAL_ADDR_FROM_DESC(aDescriptorId);


    int status = cc3xxx_trnspt_cmd_if_check_scan_tagged_frame(pDesc);
    if(OK == status)
    {
        GTRACE(GRP_DRIVER_CC33, "NOTIFY: scan tagged, dropping packet");
        TxcReleaseDeAllocRequestPush(aDescriptorId);
        return;
    }

    // Check if packet is from the current session
    if (!cc33_RxFrame_CheckSessionIsValid(pDesc))
    {
        GTRACE(GRP_DRIVER_CC33, "NOTIFY: Received mng packet is from previous session, dropping packet");
        TxcReleaseDeAllocRequestPush(aDescriptorId);
        return;
    }

    roleId = pDesc->link_role.role_id;
    pDrv = getDriverForRoleId(roleId, gpSupplicantGlobals);

	// PMAC updates descriptor fields before transmission:
    //      address points to first byte of 802.11 header
    pMngPack = (struct ieee80211_mgmt *)pDesc->address;
    packLen = pDesc->length_type.length;

	// Handle management packets
	fc = le_to_host16(pMngPack->frame_control);
	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);

	// Data path is expected to forward only management packets
	ASSERT_GENERAL(WLAN_FC_TYPE_MGMT == type);

	GTRACE(GRP_DRIVER_CC33, "Received mng packet role id %d, desc id 0x%X, frame type 0x%X, fc 0x%x, SN %d",
	                         roleId, aDescriptorId, GET_MPDU_TYPE_SUBTYPE(fc), fc, GET_SEQ_NUM(le_to_host16(pMngPack->seq_ctrl)));

	// Management packets may be received after interface is removed (at least until
    // role removal is properly handled). Protect against this situation and drop
    // the packet if driver instance is invalid
	if (NULL == pDrv)
	{
	    GTRACE(GRP_DRIVER_CC33, "NOTIFY: driver instance is invalid, dropping RX packet");
	    TxcReleaseDeAllocRequestPush(aDescriptorId);
	    return;
	}

    //if management frame is protected - remove security header. copy payload backward
    if (TEST_PROTECTED_BIT(pDesc->mpdu_control.wlan_frame_control) != 0)
    {
        uint8_t*  ptr1 = (uint8_t*)pMngPack + sizeof(MPDUHeader_t);
        uint8_t*  ptr2 = (uint8_t*)pMngPack + pDesc->mpdu_control.mac_header_length; //include security header

        packLen -=  (pDesc->mpdu_control.mac_header_length - sizeof(MPDUHeader_t));

        uint16_t  payloadLen = pDesc->length_type.length - pDesc->mpdu_control.mac_header_length;

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

	    if (WLAN_FC_STYPE_AUTH == stype)
	    {
	        //Check if address is in whitelist or blacklist
	        if (!CME_IsMacAllowed(pMngPack->sa))
	        {
	            //mac is not allowed. Send proper auth response to the STA
	            cc33drv_txAuthResPacket(pDrv, pMngPack->sa,
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
	        uint32_t linkId = MAT_SearchPeerId(pMngPack->sa);

//            notifySupp = (INVALID_LINK == linkId);

            GTRACE(GRP_DRIVER_CC33, "Assoc request from 0x%x 0x%x, notify supplicant %d link ID %d",
                                     (uint32_t *)pMngPack->sa, (uint16_t *)&pMngPack->sa[4], notifySupp, linkId);
	    }

	    if (notifySupp)
	    {
	        union wpa_event_data eventData;

	        eventData.rx_mgmt.frame = (u8 *)pMngPack;
	        eventData.rx_mgmt.frame_len = pDesc->length_type.length;
	        eventData.rx_mgmt.datarate = pDesc->phy_information1.rate;
	        eventData.rx_mgmt.ssi_signal = GET_RSSI_VAL_FROM_DESC(pDesc);

	        GTRACE(GRP_DRIVER_CC33, "Sending RX mng packet event to supplicant; type: 0x%X, header length %d, length %d, header at 0x%x, payload at 0x%x",
	               GET_MPDU_TYPE_SUBTYPE(fc),
	               pDesc->mpdu_control.mac_header_length,
	               eventData.rx_mgmt.frame_len,
	               (uint32_t)pDesc->address,
	               (uint32_t)(pDesc->address + pDesc->mpdu_control.mac_header_length));

	        if (WLAN_FC_STYPE_PROBE_REQ == stype)
	        {
	            //TODO: to remove? 
	            GTRACE(GRP_DRIVER_CC33, "Probe request: received");
	        }

	        wpa_supplicant_event(pDrv->ctx, EVENT_RX_MGMT, &eventData);
	    }

	    // Either supplicant has completed handling the received packet or no
        // no supplicant handling is needed, in any case memory should be returned to MMU
        TxcReleaseDeAllocRequestPush(aDescriptorId);

	    return;
	}

	switch (stype)
	{
		 case WLAN_FC_STYPE_BEACON:
	        // NLCP beacon handling is all performed in WLAN services layer.
	        // This includes parsing beacon and updating RSSI statistics, WMM,
	        // rates. Handling of TIM in PS mode.

	        // NLCP reference code at:
			// rc = rxBeaconPacket(apPack, packLen);
		     rc = RX_MGMT_NONE;
			 break;
		case WLAN_FC_STYPE_PROBE_RESP:
//			rc = rxProbeResponsePacket(pMngPack, packLen);
			break;

		case WLAN_FC_STYPE_AUTH:
			rc = cc33drv_rxAuthResponsePacket(pDrv, pMngPack, packLen);
			break;

		case WLAN_FC_STYPE_DEAUTH:
			rc = cc33drv_rxDeauthPacket(pDrv, pMngPack, packLen);
			break;

		case WLAN_FC_STYPE_DISASSOC:
		    rc = cc33drv_rxDisassocPacket(pDrv, pMngPack, packLen);
			// NLCP reference code at:
			// rma = ieee80211_rx_mgmt_disassoc(sdata, mgmt, skb->len);
			break;

		case WLAN_FC_STYPE_ASSOC_RESP:
		case WLAN_FC_STYPE_REASSOC_RESP:
			rc = cc33drv_rxAssocResponsePacket(pDrv, pMngPack, packLen, (WLAN_FC_STYPE_REASSOC_RESP == stype), aDescriptorId);
			// NLCP reference code at:
			// rma = ieee80211_rx_mgmt_assoc_resp(sdata, mgmt, skb->len, &bss);
			break;

		case WLAN_FC_STYPE_ACTION:
		{
		    GTRACE(GRP_DRIVER_CC33, "Received action frame. category %d, action %d",
		           pMngPack->u.action.category,
		           pMngPack->u.action.u.sa_query_req.action);


			switch (pMngPack->u.action.category)
			{
			    case WLAN_ACTION_SA_QUERY:
			    {
                    rc = cc33drv_rxSaQueryPacket(pDrv,
                                                 pMngPack,
                                                 packLen);
                }
			        break;

				case WLAN_ACTION_SPECTRUM_MGMT:
				{
				    uint8_t* pChannelSwitchIEstart;


				    if ((pMngPack->u.action.u.chan_switch.action_code != WLAN_CHANNEL_SWITCH_ACTION_CODE) ||
				        (pMngPack->u.action.u.chan_switch.element_id != WLAN_EID_CHANNEL_SWITCH))
				    {
				        GTRACE(GRP_DRIVER_CC33,
				               "Unknown action code / element ID (%d/%d) for SPECTRUM_MGMT action frame, ignore it.",
				               pMngPack->u.action.u.chan_switch.action_code,
				               pMngPack->u.action.u.chan_switch.element_id);

				        break;
				    }

				    pChannelSwitchIEstart = &pMngPack->u.action.u.chan_switch.switch_mode;

				    WlanLpThread_ChannelSwithcHandler(pChannelSwitchIEstart, roleId);
                    break;
				}
			}
		}
		break;

		default:
			GTRACE(GRP_DRIVER_CC33, "Received unknown mng type %d, frame control 0x%x", stype, pMngPack->frame_control);
			break;
	}


	GTRACE(GRP_DRIVER_CC33, "rc = ENUM(rxMngPackNextOperation_e,%d)", rc);

	// depending on the result of received packet handling, notify the supplicant
	switch (rc)
	{
		case RX_MGMT_NONE:
			/* no action */
			break;
		case RX_MGMT_DEAUTH:
			sendEventDeauthDisassoc(pDrv, FRAME_TYPE_DEAUTHENTICATION, pMngPack, packLen);
            CmeStationFlowSM(CME_STA_WLAN_PEER_DISCONNECT_REQ, CME_STA_NONE_USER);
			break;
		case RX_MGMT_DISASSOC:
			sendEventDeauthDisassoc(pDrv, FRAME_TYPE_DISASSOCIATION, pMngPack, packLen);
            CmeStationFlowSM(CME_STA_WLAN_PEER_DISCONNECT_REQ, CME_STA_NONE_USER);
			break;
		case RX_MGMT_AUTH:
			// NLCP code, mac80211\mlme.c
			// cfg80211_send_rx_auth(sdata->dev, (u8 *)mgmt, skb->len);
			sendRxAuthEvent(pDrv, pMngPack, packLen);
			break;
		case RX_MGMT_RX_ASSOC:
			// NLCP code, mac80211\mlme.c
			// cfg80211_send_rx_assoc(sdata->dev, bss, (u8 *)mgmt, skb->len);
			sendRxAssocEvent(pDrv, pMngPack, packLen);
			break;
		case RX_MGMT_ASSOC_TIMEOUT:
			// NLCP code, mac80211\mlme.c
			// cfg80211_send_assoc_timeout(sdata->dev, mgmt->bssid);
		    cc33drv_sendConnectTimeoutEvent(pDrv, EVENT_ASSOC_TIMED_OUT, pMngPack->bssid);
			break;

		case RX_MGMT_SEND_RX_MGMT_EVENT:
		{
            union wpa_event_data eventData;

            eventData.rx_mgmt.frame = (u8 *)pMngPack;
            eventData.rx_mgmt.frame_len = packLen;//after security header is reduced
            eventData.rx_mgmt.datarate = pDesc->phy_information1.rate;
            eventData.rx_mgmt.ssi_signal = GET_RSSI_VAL_FROM_DESC(pDesc);

            wpa_supplicant_event(pDrv->ctx, EVENT_RX_MGMT, &eventData);
		}
		    break;

		default:
			GTRACE(GRP_DRIVER_CC33, "Unknown return code %d", rc);
			break;
	}

	// Free the received packet memory
	TxcReleaseDeAllocRequestPush(aDescriptorId);
}
#endif

#if 0
// ----------------------------------------------------------------------------
void cc33drv_handleRemainOnChannelEvent(void *apDrv, Bool32 aIsRoc, uint32_t aDurationMS, uint32_t aChannel)
{
	ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apDrv;
	union wpa_event_data eventData;
	enum wpa_event_type  eventType = (TRUE == aIsRoc) ? EVENT_REMAIN_ON_CHANNEL : EVENT_CANCEL_REMAIN_ON_CHANNEL;

	eventData.remain_on_channel.duration = aDurationMS;
	eventData.remain_on_channel.freq = channel_to_freq(aChannel);

	wpa_supplicant_event(pDrv->ctx, eventType, &eventData);
}
#endif
#if 0

// ----------------------------------------------------------------------------
void cc33drv_handleTxResult(uint32_t aDescriptorId)
{

    return;
// need to implement
    uint16_t fc, type, stype;
    Bool32 releaseDesc = TRUE;
	CC33_FrameTxDesc_t    *pDesc;
	ti_driver_ifData_t  *pDrv;
	struct ieee80211_mgmt *pMngPack;
	union wpa_event_data eventData;
	uint8_t localHeader [32];

	pDesc = (CC33_FrameTxDesc_t *)MMU_GET_VIRTUAL_ADDR_FROM_DESC(aDescriptorId);

    // Check if packet is from the current or a valid session
    if (!cc33_TxResult_CheckSessionIsValid(pDesc))
    {
        GTRACE(GRP_DRIVER_CC33, "NOTIFY: Received tx result is from previous session, dropping packet");
        TxcReleaseDeAllocRequestPush(aDescriptorId);
        return;
    }


	pDrv = (ti_driver_ifData_t *)pDesc->txexch_callback_msi;

#ifdef PMAC_AX
	// Since packet is sent to supplicant we must make sure that frame is placed as expected - header & payload
	// We to be located just before the payload
	memcpy(localHeader,(void *)pDesc->hdr_addr,sizeof(MGMT_Header_t));
	// close the gap originaly saved for HT header	
	memcpy((void *)(pDesc->address-sizeof(MGMT_Header_t)),localHeader,sizeof(MGMT_Header_t)); 
	pMngPack = (struct ieee80211_mgmt *)(pDesc->address-sizeof(MGMT_Header_t));
#else
	// After transmission address points to 802.11 header
	pMngPack = (struct ieee80211_mgmt *)pDesc->address;
#endif


	// Extract transmitted packet type and verify it was a management packet
	fc = le_to_host16(pMngPack->frame_control);
	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);

	// Supplicant handles TX results only for AP based roles
	if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
	    GTRACE(GRP_DRIVER_CC33, "Forward TX result (desc id 0x%x) to supplicant; TX status ENUM(TX_status_e,%d) fc 0x%x",
                                 aDescriptorId, (TX_status_e)pDesc->tx_state_status.tx_status, fc);

	    // Notify supplicant of TX result
        memset(&eventData, 0, sizeof(eventData));
        eventData.tx_status.type = type;
        eventData.tx_status.stype = stype;
        eventData.tx_status.ack = (STATUS_EXPLICIT_SUCCESS == pDesc->tx_state_status.tx_status);
        eventData.tx_status.data = (uint8_t *)pMngPack;
        eventData.tx_status.data_len = pDesc->length_type.length + sizeof(MGMT_Header_t);
        eventData.tx_status.dst = pMngPack->da;
        wpa_supplicant_event(pDrv->ctx, EVENT_TX_STATUS, &eventData);

        // Supplicant has completed using the packet, if PMAC hasn't done it
        // already, free the packet
        if (TRUE == pDesc->tx_exchange.sw_no_release_request)
        {
            TxcReleaseDeAllocRequestPush(aDescriptorId);
        }


        return;
    }

	// For STA based role, distribute the result to expecting CB
	switch (stype)
	{
	    case WLAN_FC_STYPE_AUTH:
	        releaseDesc = cc33drv_AuthReqCB(aDescriptorId);
	        break;

	    case WLAN_FC_STYPE_ASSOC_REQ:
	    case WLAN_FC_STYPE_REASSOC_REQ:
	        releaseDesc = cc33drv_AssocReqCB(aDescriptorId);
	        break;

	    case WLAN_FC_STYPE_DEAUTH:
	        GTRACE(GRP_DRIVER_CC33, "TX deauth packet was completed with result ENUM(TX_status_e,%d)",
	                                (TX_status_e)pDesc->tx_state_status.tx_status);

	        //TX complete of a Deauth packet is handled separately (in a blocking manner) and we should not arrive here.
	        ASSERT_GENERAL(FALSE);

	        break;

	    default:
	        ASSERT_GENERAL(FALSE);
	}

	if (TRUE == releaseDesc)
	{
	    TxcReleaseDeAllocRequestPush(aDescriptorId);
	}
}
#endif

// ----------------------------------------------------------------------------
void cc33drv_handleRxEapol(uint32_t aDescriptorId)
{
    return;
// need to implement
#if 0
    uint8_t                *pEapolBuff;
    uint32_t               eapolOffset;
    CC33_FrameRxDesc_t   *pDesc;
    ti_driver_ifData_t *pDrv;
    struct ieee80211_hdr *pHdr;
    union wpa_event_data eventData;

    pDesc = (struct CC33_FrameRxDesc_s *)MMU_GET_VIRTUAL_ADDR_FROM_DESC(aDescriptorId);

    // Check if packet is from the current session
    if (!cc33_RxFrame_CheckSessionIsValid(pDesc))
    {
        GTRACE(GRP_DRIVER_CC33, "NOTIFY: Received eapol packet is from previous session, dropping packet");
        TxcReleaseDeAllocRequestPush(aDescriptorId);
        return;
    }

    pDrv = getDriverForRoleId(pDesc->link_role.role_id, gpSupplicantGlobals);

    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33_DEBUG, "NOTIFY: driver instance is invalid, dropping packet");
        TxcReleaseDeAllocRequestPush(aDescriptorId);
        return;
    }

    // PMAC updates descriptor fields before forwarding:
    //      address points to first byte of 802.11 header
    //      pDesc->length_type.length reflects total number of received bytes
    //      For EAPOL data we have to skip 802.11 header and snap header
    pHdr = (struct ieee80211_hdr *)pDesc->address;
    eapolOffset = pDesc->mpdu_control.mac_header_length + WLAN_SNAP_HDR_LEN;
    pEapolBuff = (uint8_t *)(pDesc->address + eapolOffset);

    GTRACE(GRP_DRIVER_CC33, "Forward RX EAPOL to supplicant; RX len %d EAPOL offset %d header size %d desc id 0x%x",
                             pDesc->length_type.length,
                             eapolOffset,
                             pDesc->mpdu_control.mac_header_length,
                             aDescriptorId);

    memset(&eventData, 0, sizeof(eventData));
    eventData.eapol_rx.data = pEapolBuff;
    eventData.eapol_rx.data_len = pDesc->length_type.length - eapolOffset;
    eventData.eapol_rx.src = pHdr->addr2;
    wpa_supplicant_event(pDrv->ctx, EVENT_EAPOL_RX, &eventData);

    // Supplicant doesn't free the EAPOL, so we do it after handling is completed
    TxcReleaseDeAllocRequestPush(aDescriptorId);
#endif
}

// ----------------------------------------------------------------------------
void cc33drv_handleRxFromUnknown(uint32_t aDescriptorId)
{
    return;
// need to implement
#if 0
    CC33_FrameRxDesc_t   *pDesc;
    ti_driver_ifData_t *pDrv;
    struct ieee80211_hdr *pHdr;
    uint16_t fc;
    union wpa_event_data eventData;

    pDesc = (struct CC33_FrameRxDesc_s *)MMU_GET_VIRTUAL_ADDR_FROM_DESC(aDescriptorId);

    // Check if packet is from the current session
    if (!cc33_RxFrame_CheckSessionIsValid(pDesc))
    {
        GTRACE(GRP_DRIVER_CC33, "NOTIFY: Received packet from Unknown is from previous session, dropping packet");
        TxcReleaseDeAllocRequestPush(aDescriptorId);
        return;
    }

    // Frame from unknown  is (by definition) from unknown link at some level.
    // We shouldn't check session validity

#ifdef CC33XX_DRIVER_DEBUG
    ++gSuppDrvDebugInfo_ull.common.numRxFromUnknown;
#endif

    pDrv = getDriverForRoleId(pDesc->link_role.role_id, gpSupplicantGlobals);

    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33_DEBUG, "NOTIFY: driver instance is invalid, dropping packet");
        TxcReleaseDeAllocRequestPush(aDescriptorId);
        return;
    }

    memset(&eventData, 0, sizeof(eventData));

    //Start of packet
    pHdr = (struct ieee80211_hdr *)pDesc->address;

    fc = le_to_host16(pHdr->frame_control); //frame control

    //Code taken from driver nl80211
    eventData.rx_from_unknown.bssid = get_hdr_bssid(pHdr, pDesc->length_type.length); //Set the bss
    eventData.rx_from_unknown.addr = pHdr->addr2; //Set the source address
    eventData.rx_from_unknown.wds = (fc & (WLAN_FC_FROMDS | WLAN_FC_TODS)) == (WLAN_FC_FROMDS | WLAN_FC_TODS); //Set wds

    wpa_supplicant_event(pDrv->ctx, EVENT_RX_FROM_UNKNOWN, &eventData);

    //Free the frame
    TxcReleaseDeAllocRequestPush(aDescriptorId);
#endif
}
// ----------------------------------------------------------------------------

void cc33drv_pnReplayDetected(uint32_t aDescriptorId, uint16_t cipherType)
{
    return;
// need to implement
#if 0
    CC33_FrameRxDesc_t    *pDesc;

    pDesc = (struct CC33_FrameRxDesc_s *)MMU_GET_VIRTUAL_ADDR_FROM_DESC(aDescriptorId);

    // Check if packet is from the current session
    if (!cc33_RxFrame_CheckSessionIsValid(pDesc))
    {
        GTRACE(GRP_DRIVER_CC33_DEBUG, "NOTIFY: Replay detection is from previous session, dropping packet");
        TxcReleaseDeAllocRequestPush(aDescriptorId);
        return;
    }

    GTRACE(GRP_DRIVER_CC33, "cc33drv: PN Replay Detected, cipher suite ENUM(CipherSuite_e,%d)", cipherType);

    //TODO:, Implement replay detection
#ifdef CC33XX_DRIVER_DEBUG
    ++gSuppDrvDebugInfo_ull.common.numPnReplayDetected;
#endif

    TxcReleaseDeAllocRequestPush(aDescriptorId);
#endif
}


// ----------------------------------------------------------------------------
void cc33drv_aesSwDecryptionNeeded(uint32_t aDescriptorId)
{
    return;
// need to implement
#if 0
    CC33_FrameRxDesc_t    *pDesc;

    pDesc = (struct CC33_FrameRxDesc_s *)MMU_GET_VIRTUAL_ADDR_FROM_DESC(aDescriptorId);

    // Check if packet is from the current session
    if (!cc33_RxFrame_CheckSessionIsValid(pDesc))
    {
        GTRACE(GRP_DRIVER_CC33_DEBUG, "NOTIFY: AES SW decryption needed is from previous session, dropping packet");
        TxcReleaseDeAllocRequestPush(aDescriptorId);
        return;
    }

    GTRACE(GRP_DRIVER_CC33_DEBUG, "cc33drv: AES SW decryption needed");

    //TODO:, What to do here?
#ifdef CC33XX_DRIVER_DEBUG
    ++gSuppDrvDebugInfo_ull.common.numAesSwDecryptionNeeded;
#endif

    TxcReleaseDeAllocRequestPush(aDescriptorId);
#endif
}

// ----------------------------------------------------------------------------
void cc33drv_lowAck(struct wpa_global *apGlobal, uint32_t aRoleId,
                    uint16_t aInactiveLinksBits, Bool32 aMaxRetries)
{
    return;
// need to implement
#if 0
    char macStr[MAC_STR_LEN];
    const uint8_t  *pPeerAdd;
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

    for (i=0 ; i<MAX_LINK_NUM; ++i)
    {
        if (staBitsMask & aInactiveLinksBits)
        {
            pPeerAdd = Links_GetPeerAddress(i);
            IRQ_UtilCopyMacAddress(pPeerAdd, eventData.low_ack.addr);

            GET_MAC_STR(pPeerAdd, macStr);
            GTRACE(GRP_DRIVER_CC33, "Low ack/max retries (%d) detected for link %d address %s", aMaxRetries,i, macStr);

            wpa_supplicant_event(pDrv->ctx, EVENT_STATION_LOW_ACK, &eventData);
        }

        staBitsMask <<= 1;
    }
#endif
}

// ----------------------------------------------------------------------------
Bool32 cc33drv_stopConnectionScans(struct wpa_supplicant *wpa_s)
{
    Bool32 waiting4stop = FALSE;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    EScanRequestType   scanType = SCAN_REQUEST_NONE; // Relevant only for one shot scan

    GTRACE(GRP_DRIVER_CC33_DEBUG, "Scan stop, State = %d, Scaning = %d, Sched Scaning = %d", wpa_s->wpa_state, wpa_s->scanning, wpa_s->sched_scanning);

    // Cancel scheduled one shot scan, if pending
    wpa_supplicant_cancel_scan(wpa_s);

    if (wpa_s->wpa_state == WPA_SCANNING)
    {
        if (0 == wpa_s->sched_scanning)
        {
            // One shot connection scan - get the scan type

            // Only one type of connection scan is allowed, ASSERT_GENERAL otherwise
            //ASSERT_GENERAL(FALSE == (ONE_SHOT_OS_SCAN_ACTIVE(pDrv) & ONE_SHOT_APP_SCAN_ACTIVE(pDrv)));
            scanType = SCAN_REQUEST_ONE_SHOT;
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
        if ( wpa_s->scanning )
        {
            // sched_scanning is cleared when stopped event is received
            if (0 != wpa_s->sched_scanning)
            {
                //Periodic scan is running
                mx_driver_send_scan_stop_cmd (pDrv->roleId, SCAN_REQUEST_CONNECT_PERIODIC_SCAN, FALSE);
            }
            else
            {
                // One shot connection scan is running

                mx_driver_send_scan_stop_cmd (pDrv->roleId, scanType, FALSE);
            }

            waiting4stop = TRUE;
        }
        else
        {
            // If we are here, Supplicant is in between one shot connection scans, it's state is scanning,
            // but currently there is no actual scan running in the FW
            cc33drv_handleOneShotScanStoppedEvent(wpa_s, scanType);

        }
    }

    // Cancel the scan work in supplicant
    if (radio_work_pending(wpa_s, "scan"))
    {
        GTRACE(GRP_DRIVER_CC33_DEBUG, "Pending scan work - Remove it...");

        radio_remove_works(wpa_s, "scan", 0);
    }


    return waiting4stop;
}

// ----------------------------------------------------------------------------

// ============================================================================
// 	Internal service functions
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
	// Use the sames configuration as in MCP & NLCP (driver_nl80211) drivers
	apDrv->capa.key_mgmt = WPA_DRIVER_CAPA_KEY_MGMT_WPA
					     | WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK
					     | WPA_DRIVER_CAPA_KEY_MGMT_WPA2
					     | WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK
					     | WPA_DRIVER_CAPA_KEY_MGMT_FT
					     | WPA_DRIVER_CAPA_KEY_MGMT_FT_PSK;

	apDrv->capa.enc = WPA_DRIVER_CAPA_ENC_CCMP
#ifdef CONFIG_IEEE80211W
				    | WPA_DRIVER_CAPA_ENC_BIP
//				    | WPA_DRIVER_CAPA_ENC_BIP_GMAC_128
//				    | WPA_DRIVER_CAPA_ENC_BIP_GMAC_256
//				    | WPA_DRIVER_CAPA_ENC_BIP_CMAC_256
#endif
				    ;

	apDrv->capa.auth = WPA_DRIVER_AUTH_OPEN | WPA_DRIVER_AUTH_SHARED | WPA_DRIVER_AUTH_LEAP;


	// we support probe response offload (MCP & NLCP
	apDrv->capa.flags = WPA_DRIVER_FLAGS_PROBE_RESP_OFFLOAD;
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
	apDrv->capa.flags |= WPA_DRIVER_FLAGS_P2P_CAPABLE;
	// The below is supported by MCP driver but not by NLCP driver
	//  | WPA_DRIVER_FLAGS_P2P_CONCURRENT | WPA_DRIVER_FLAGS_P2P_MGMT_AND_NON_P2P;

	// The below indicates supplicant to enable/disable p2p according to user configuration.
	// When adding a new interface if WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE is set
	//     wpa_s->p2p_mgmt = iface->p2p_mgmt, otherwise wpa_s->p2p_mgmt = 1.
	// wpas_p2p_init is activated only if p2p_mgmt = 1.
	// see wpa_supplicant_init_iface
	apDrv->capa.flags |= WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE;

	apDrv->capa.max_remain_on_chan = 5000;

	// Tx status reporting support (supported by MCP & NLCP drivers)
	// Supplicant is block till deauth / disassoc are sent. No need to wait for status
//	apDrv->capa.flags |= WPA_DRIVER_FLAGS_DEAUTH_TX_STATUS;

	// Trust driver association errors (supported by MCP & NLCP drivers)
	apDrv->capa.flags |= WPA_DRIVER_FLAGS_SANE_ERROR_CODES;

	// AP related settings
	apDrv->capa.max_stations =   1;  // need to imlement  cfgGetApMaxNumStations();
	apDrv->capa.flags |= WPA_DRIVER_FLAGS_AP | WPA_DRIVER_FLAGS_AP_UAPSD;

	// Finally set the flag indicating supplicant internal SME should be used (NLCP like)
	apDrv->capa.flags |= WPA_DRIVER_FLAGS_SME;

	//Needed for setting wep static keys
	apDrv->capa.flags |= WPA_DRIVER_FLAGS_SET_KEYS_AFTER_ASSOC_DONE;

	// ToDo - the below are supported by driver_nl80211 but not by MCP driver - check why
//	drv->capa.flags |= WPA_DRIVER_FLAGS_EAPOL_TX_STATUS;

	// The below is not referenced in MCP and it looks like also in NLCP
	//	max_acl_mac_addrs, num_multichan_concurrent, extended_capa, extended_capa_mask, extended_capa_len

	GTRACE(GRP_DRIVER_CC33, "driver capabilities: key_mgmt 0x%x enc 0x%x flags MSB 0x%x flags LSB 0x%x", apDrv->capa.key_mgmt, apDrv->capa.enc, (uint32_t) (apDrv->capa.flags >> 32),   (uint32_t) (apDrv->capa.flags));

	return 0;
}

// ----------------------------------------------------------------------------
// enableRole
//      Send enable role command to FW, wait for FW to allocate a role and set
//      role ID on driver DB. This role ID shall be used for any further access
//      to this role.
//      Roles module is also responsible for allocating MAC address.
//
// Parameters:
//      apDrv - IN/OUT pointer to the driver DB
//      aRoleType - type of role that should be allocated & enabled
// return 0 on success, -1 on failure
//
// Note: ENABLE_USER_DEFAULTS is used in wilink products to get role parameters
//       from ini file. In cc33xx it is currently assumed that role parameters
//       are initialized in legay FW to the desired values.
// ----------------------------------------------------------------------------
#if 0

static int enableRole (ti_driver_ifData_t *apDrv, RoleType_e aRoleType)
{
    return 0;
    Command_t cmd;
	RoleEnableParameters_t cmdParams;

    cmd.cmdID = CMD_ROLE_ENABLE;
    cmd.pCmdParams = (void *)&cmdParams;

	GTRACE(GRP_WPA_SUPPLICANT, "Enable role ENUM(RoleType_e, %d) ", aRoleType);

#ifdef CC33XX_DRIVER_DEBUG
	// Reset debug info
	if (ROLE_IS_TYPE_STA_BASED(aRoleType))
	{
	    memset(&gSuppDrvDebugInfo_ull.sta, 0, sizeof(cc33drv_staDebugInfo_t));
	    gSuppDrvDebugInfo_ull.sta.gForceDisconnectState = 100;
	}
	else if (ROLE_IS_TYPE_AP_BASED(aRoleType))
    {
        memset(&gSuppDrvDebugInfo_ull.ap, 0, sizeof(cc33drv_apDebugInfo_t));
    }
#endif

	cmdParams.roleID = INVALID_ROLE_ID;
	cmdParams.roleType = aRoleType;
	// Clear MAC address, this indicates the roles module address needs to be allocated.
	// ToDo - may be removed if we always allocate address for a new role.
	IRQ_UtilZeroMacAddress(cmdParams.macAddress);

    // Send the command and wait for response
	CME_SendCmd2WlanServices(&cmd);

	// Mark role wasn't started yet
	apDrv->roleStarted = FALSE;

	// Set received parameters on role DB
	apDrv->roleId = cmdParams.roleID;
	IRQ_UtilCopyMacAddress(cmdParams.macAddress, apDrv->macAddr);

	return 0;
}
#endif


// ----------------------------------------------------------------------------
/*!
    \brief      Send deauthentication / disassociation command to FW

    Send Deauth / disassoc command to wlan lp thread, starting a managed sequence
    of sending a deauth / disassoc frame.
    This is a blocking function. Waits till sequence is completed.

    \param      apDrv - IN/OUT pointer to the driver DB
                pDestAddr - destination address
                frameType - FRAME_TYPE_AUTHENTICATION / FRAME_TYPE_DEAUTHENTICATION
                reason - deauth / disassoc reason

    \return     0 on success, -1 otherwise
*/
int32_t cc33drv_sendDeauthDisassoc(ti_driver_ifData_t *pDrv,
                                 uint8_t  *pDestAddr,
                                 uint32_t frameType,
                                 uint16_t reason)
{
    CommandParam_t cmd;
    SendDeauthDisassocParameters_t cmdParams;

    cmd.cmdID = CMD_SEND_DEAUTH_DISASSOC;
    cmdParams.roleID = pDrv->roleId;
    cmdParams.reason = reason;
    cmdParams.frameType = frameType;

    IRQ_UtilCopyMacAddress (pDestAddr, cmdParams.destAddr);

    os_memcpy(cmd.param, (void *)&cmdParams, sizeof(cmdParams));
    // Command blocks until WLAN services completes the disable operation
    // TODO: need to implement send command
    //CME_SendCmd2WlanServices(&cmd);

    return 0;
}


//struct wpa_driver_auth_params {
//	int freq;
//	const u8 *bssid;
//	const u8 *ssid;
//	size_t ssid_len;
//	int auth_alg;
//	const u8 *ie;
//	size_t ie_len;
//	const u8 *wep_key[4];
//	size_t wep_key_len[4];
//	int wep_tx_keyidx;
//	int local_state_change;
//
//	/**
//	 * p2p - Whether this connection is a P2P group
//	 */
//	int p2p;
//
//	const u8 *sae_data;
//	size_t sae_data_len;
//
//};

// ----------------------------------------------------------------------------
static int initPeriodicScanParams(ti_driver_ifData_t 	     *apDrv,
		  						   scanRequestParams_t		     *apScanParams,
		  						   struct wpa_driver_scan_params *apSuppParams)
{
	unsigned int i, j;
	int local_chans[] = PERIODIC_SCAN_CHANNELS_ARRAY_B_G_A_BAND;    // if supplicant doesn't set any channel,
	                                                                // all channels shall be scanned, starting
	                                                                // from social channels.
	periodicScanParams_t * pPeriodicScanParams = &apScanParams->u.tConnScanInfo;

	//---------------------------
	// Set scan plan
	//---------------------------
	if ((apSuppParams->sched_scan_plans_num == 0) || (!apSuppParams->sched_scan_plans))
	{
	    return -1;
	}

	//Check if number of plans exceeds driver support
	if (apSuppParams->sched_scan_plans_num > apDrv->capa.max_sched_scan_plans)
	{
	    GTRACE(GRP_GENERAL_ERROR, "ERROR: Sched scan: Num of plans exceeds the driver support");
	    return -1;
	}

	// Allocate buffer for scheduled scan plans. Will be copied by the scan module so glx memory can be used.
	// Will be freed by the scan module.
	pPeriodicScanParams->sched_scan_plans = os_malloc(sizeof(struct sched_scan_plan) * apSuppParams->sched_scan_plans_num);
	if (!pPeriodicScanParams->sched_scan_plans)
	{
	    return -1;
	}

	os_memcpy(pPeriodicScanParams->sched_scan_plans, apSuppParams->sched_scan_plans, (sizeof (struct sched_scan_plan)) * apSuppParams->sched_scan_plans_num);
	pPeriodicScanParams->sched_scan_plans_num = apSuppParams->sched_scan_plans_num;

	// --------------------------
	// set channels
	// --------------------------

	// If freqs are set by supplicant, translate frequencies to channels and
	// use them.
	if (NULL != apSuppParams->freqs)
	{
		int *pCurrFreq = apSuppParams->freqs;
		RadioBand_e band;

		i = 0;
		while ( (0 != *pCurrFreq) && (i < PERIODIC_SCAN_MAX_CHANNEL_NUM) )
		{
		    freq_to_chan(pCurrFreq[i], (Channel_e *)&local_chans[i], &band);
		    ++i;
		}
	}

	// ToDo - use regulatory domain for setting channels

	//
	// 2.4GHz channels
	//
	j = 0;
	if (FALSE != cfgIsBGbandSupported())
	{
        for (i=0 ; i<PERIODIC_SCAN_MAX_CHANNEL_NUM ; ++i)
        {
            if (1 != is_bg_channel(local_chans[i]))
                continue;

            pPeriodicScanParams->channels_BG[j] = local_chans[i];
            j++;

            // All BG channels are configure, no need to loop anymore
            if (SCAN_MAX_CHANNELS_BG == j)
                break;
        }
	}
	pPeriodicScanParams->numOfGChannels = j;

	//
	// 5GHz channels
	//
	j = 0;
	if (FALSE != cfgIsAbandSupported())
	{
        for (i=0 ; i<PERIODIC_SCAN_MAX_CHANNEL_NUM ; ++i)
        {
            if (0 != is_bg_channel(local_chans[i]))
                continue;

            pPeriodicScanParams->channels_A[j] = local_chans[i];
            j++;
        }
	}
	pPeriodicScanParams->numOfAChannels = j;

	// Notes:
	//      - Probe request TX rate is selected by scan module
	//      - Extra IEs are handed to scan module from CME upon scan module request

	return 0;
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

    wpa_supplicant_event(apDrv->ctx, EVENT_ASSOC, &event);
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
// need to implement
#if 0
static void sendEventDeauthDisassoc(ti_driver_ifData_t  *apDrv,
                                    uint32_t                aType,
                                    struct ieee80211_mgmt *apMngPack,
                                    uint32_t                aPackLen)
{
    char macStr[MAC_STR_LEN];
    union wpa_event_data event;
    uint32_t  minLen = WLAN_HDR_LEN + sizeof(apMngPack->u.deauth);
    uint16_t reason_code;
    wpaEventType_e type;

    GET_MAC_STR(apMngPack->bssid, macStr);

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
        return;
    }

    markDisconnected(apDrv, __LINE__);
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
}
#endif

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
}

// ----------------------------------------------------------------------------
// based on net\wireless\mlme.c,

//          ieee80211_set_disassoc
//          ieee80211_mgd_deauth (when sending deauth, if already associated)
//
//              __ieee80211_connection_loss
//              ieee80211_rx_mgmt_deauth
//              ieee80211_rx_mgmt_disassoc
//              ieee80211_sta_connection_lost
//              ieee80211_mgd_auth (if already associated)
//              ieee80211_mgd_assoc (if already associated)
//              ieee80211_mgd_disassoc

//              ieee80211_sta_rx_queued_mgmt with result = IEEE80211_STYPE_DISASSOC


// ----------------------------------------------------------------------------
// based on net\wireless\mlme.c, cfg80211_send_disassoc
//       originated from mac80211\mlme.c:
//          ieee80211_sta_rx_queued_mgmt with processing reult of RX_MGMT_DISASSOC
//              cc33xx - done
//          ieee80211_mgd_disassoc after calling ieee80211_set_disassoc
//              cc33xx - looks like ieee80211_mgd_disassoc is not activated.
//              supplicant command for disassociation is sent dirrectly from
//              driver_nl80211.c to driver layer

/* ----------------------------------------------------------------------------
 cc33drv_sendConnectTimeoutEvent
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
void cc33drv_sendConnectTimeoutEvent(ti_driver_ifData_t  *apDrv,
                                     wpaEventType_e        aType,
                                     uint8_t                 *apBssid)
{
    char macStr[MAC_STR_LEN];
    union wpa_event_data event;

    GET_MAC_STR(apBssid, macStr);
    GTRACE(GRP_DRIVER_CC33,  "Connection timeout for %s, sending ENUM(wpaEventType_e, %d) to supplicant",
                              macStr, aType);

    cc33_driver_cancel_remain_on_channel(apDrv);

    if (FALSE != apDrv->roleStarted)
    {
        mx_driver_stop_role(apDrv);
    }


    // Notify CME (for black list update)
//  CME_InternalEventHandler(CME_MESSAGE_ID_AUTH_TIMEOUT, &apDrv->roleId);
    apDrv->connectTimeout = TRUE;

    // Notify supplicant connection attempt has timed out
    os_memset(&event, 0, sizeof(event));
    IRQ_UtilCopyMacAddress(apBssid, event.timeout_event.addr);

    wpa_supplicant_event(apDrv->ctx, aType, &event);
}


/* ----------------------------------------------------------------------------
 store_peer_info
	Store peer information as received in association or authentication commands

 Parameters: 	none
 	 	 	 	 aAssoc -
 Return code:   none
---------------------------------------------------------------------------- */
#if 0
static int store_peer_info(struct ieee80211_sub_if_data *sdata,
				struct cfg80211_bss *cbss, int aAssoc)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct ieee80211_bss *bss = (void *)cbss->priv;
	struct sta_info *new_sta = NULL;
	bool have_sta = false;
	int err;

	if (WARN_ON(!ifmgd->auth_data && !ifmgd->assoc_data))
		return -EINVAL;

	if (assoc) {
		rcu_read_lock();
		have_sta = sta_info_get(sdata, cbss->bssid);
		rcu_read_unlock();
	}

	if (!have_sta) {
		new_sta = sta_info_alloc(sdata, cbss->bssid, GFP_KERNEL);
		if (!new_sta)
			return -ENOMEM;
	}

	if (new_sta) {
		u32 rates = 0, basic_rates = 0;
		bool have_higher_than_11mbit;
		int min_rate = INT_MAX, min_rate_index = -1;
		struct ieee80211_supported_band *sband;
		const struct cfg80211_bss_ies *ies;

		sband = local->hw.wiphy->bands[cbss->channel->band];

		err = ieee80211_prep_channel(sdata, cbss);
		if (err) {
			sta_info_free(local, new_sta);
			return err;
		}

		ieee80211_get_rates(sband, bss->supp_rates,
				    bss->supp_rates_len,
				    &rates, &basic_rates,
				    &have_higher_than_11mbit,
				    &min_rate, &min_rate_index);

		/*
		 * This used to be a workaround for basic rates missing
		 * in the association response frame. Now that we no
		 * longer use the basic rates from there, it probably
		 * doesn't happen any more, but keep the workaround so
		 * in case some *other* APs are buggy in different ways
		 * we can connect -- with a warning.
		 */
		if (!basic_rates && min_rate_index >= 0) {
			sdata_info(sdata,
				   "No basic rates, using min rate instead\n");
			basic_rates = BIT(min_rate_index);
		}

		new_sta->sta.supp_rates[cbss->channel->band] = rates;
		sdata->vif.bss_conf.basic_rates = basic_rates;

		/* cf. IEEE 802.11 9.2.12 */
		if (cbss->channel->band == IEEE80211_BAND_2GHZ &&
		    have_higher_than_11mbit)
			sdata->flags |= IEEE80211_SDATA_OPERATING_GMODE;
		else
			sdata->flags &= ~IEEE80211_SDATA_OPERATING_GMODE;

		memcpy(ifmgd->bssid, cbss->bssid, ETH_ALEN);

		/* set timing information */
		sdata->vif.bss_conf.beacon_int = cbss->beacon_interval;
		rcu_read_lock();
		ies = rcu_dereference(cbss->beacon_ies);
		if (ies) {
			const u8 *tim_ie;

			sdata->vif.bss_conf.sync_tsf = ies->tsf;
			sdata->vif.bss_conf.sync_device_ts =
				bss->device_ts_beacon;
			tim_ie = cfg80211_find_ie(WLAN_EID_TIM,
						  ies->data, ies->len);
			if (tim_ie && tim_ie[1] >= 2)
				sdata->vif.bss_conf.sync_dtim_count = tim_ie[2];
			else
				sdata->vif.bss_conf.sync_dtim_count = 0;
		} else if (!(local->hw.flags &
					IEEE80211_HW_TIMING_BEACON_ONLY)) {
			ies = rcu_dereference(cbss->proberesp_ies);
			/* must be non-NULL since beacon IEs were NULL */
			sdata->vif.bss_conf.sync_tsf = ies->tsf;
			sdata->vif.bss_conf.sync_device_ts =
				bss->device_ts_presp;
			sdata->vif.bss_conf.sync_dtim_count = 0;
		} else {
			sdata->vif.bss_conf.sync_tsf = 0;
			sdata->vif.bss_conf.sync_device_ts = 0;
			sdata->vif.bss_conf.sync_dtim_count = 0;
		}
		rcu_read_unlock();

		/* tell driver about BSSID, basic rates and timing */
		ieee80211_bss_info_change_notify(sdata,
			BSS_CHANGED_BSSID | BSS_CHANGED_BASIC_RATES |
			BSS_CHANGED_BEACON_INT);

		if (assoc)
			sta_info_pre_move_state(new_sta, IEEE80211_STA_AUTH);

		err = sta_info_insert(new_sta);
		new_sta = NULL;
		if (err) {
			sdata_info(sdata,
				   "failed to insert STA entry for the AP (error %d)\n",
				   err);
			return err;
		}
	} else
		WARN_ON_ONCE(!ether_addr_equal(ifmgd->bssid, cbss->bssid));

	return 0;
}
#endif


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
extern int mx_driver_one_shot_scan(void *apPriv,
                                   struct wpa_driver_scan_params *apParams);

extern int wl18xx_one_shot_scan(void *apPriv, struct wpa_driver_scan_params *apParams);
extern int mx_driver_sched_scan(void *apPriv,
                                struct wpa_driver_scan_params *apParams);

extern int mx_driver_stop_sched_scan(void *apPriv);

const struct wpa_driver_ops wpa_driver_cc33_ops =
{
	.name = "cc3300",

	// Roles shared APIs
	.init2 = cc33_driver_if_init,
	.deinit = cc33_driver_deinit,

	.get_capa = cc33_driver_get_capa,
	.set_key = cc33_driver_set_key,
	.get_hw_feature_data = cc33_driver_get_hw_feature_data,
	.get_mac_addr = cc33_driver_get_mac_addr,

	.set_country = cc33_driver_set_country,
	.send_action = cc33_driver_send_action,

	// Scan related APIs
	.scan2 = wl18xx_one_shot_scan/*cc33_driver_oneshot_scan*/,
    .get_scan_results2 = cc33_driver_get_scan_results,
    .sched_scan = mx_driver_sched_scan/*cc33_driver_sched_scan*/,
    .stop_sched_scan = mx_driver_stop_sched_scan/*cc33_driver_stop_sched_scan*/,

	// STA based only section
	.authenticate = cc33_driver_authenticate,
    .deauthenticate = cc33_driver_deauthenticate,
    .associate = cc33_driver_associate,
    .get_bssid = cc33_driver_get_bssid,
    .get_ssid = cc33_driver_get_ssid,

	// AP only section (code resides in drv_cc33_ap_specific.c)
//    .set_ap = cc33_driver_set_ap,
//	.set_freq = cc33_driver_set_channel,
//	.set_tx_queue_params = cc33_driver_set_tx_queue_params,
//	.set_rts = cc33_driver_set_rts,
//	.deinit_ap = cc33_driver_deinit_ap,
////	.hapd_set_ssid = cc33_driver_hapd_set_ssid, // This is redundant since SSID is set also in set_ap API
//	.sta_add = cc33_driver_sta_add,
//	.sta_set_flags = cc33_driver_sta_set_flags,
//    .sta_remove = cc33_driver_sta_remove,
//    .sta_deauth = cc33_driver_sta_deauth,
//    .sta_disassoc = cc33_driver_sta_disassoc,
//    .hapd_send_eapol = cc33_driver_hpad_send_eapol,
//    .get_inact_sec = cc33_driver_inact_sec,
//    .poll_client = cc33_driver_poll_client,

	// P2P only section
	.if_add = cc33_driver_if_add,
	.send_mlme = cc33_send_mgmt_frame,

	// P2P & STA based
	.remain_on_channel = cc33_driver_remain_on_channel,
    .cancel_remain_on_channel = cc33_driver_cancel_remain_on_channel,

//
//#ifndef HOSTAPD

//#endif
//	.update_ft_ies = wilink_update_ft_ies,


//  .global_init = cc33_driver_global_init,     // For MCP it allocates sockets, initializes regulatory domain,
                                                // HT capabilities & P2P scan configuration.
                                                // cc33xx - not implemented.
                                                // For P2P, scan parameters are constructed in run time
//  .global_deinit = wilink_global_deinit,      // For MCP, allocated objects are released.
                                                // cc33xx - not implemented.
//  .set_privacy = wilink_set_privacy,          // MCP sets an unused flag on AP DB, not supprted by NLCP
//  .probe_req_report = cc33_driver_probe_req_report,   // Note: this API is needed for supporting EVENT_RX_PROBE_REQ
                                                        // which isn't supported both in NLCP and MCP.

};


