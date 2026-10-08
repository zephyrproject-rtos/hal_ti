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
  FILENAME:       drv_ti_sta_specific.c

  DESCRIPTION:	  This file handles STA role specific functionality
  ----------------------------------------------------------------------------- */

#include "tw_driver.h"
#include "udata_net_api.h"
#include "wlan_links.h"
#include "drv_ti_internal.h"
#include "ieee802_11_defs.h"
#include "80211_utils.h"
#include "mlme_parser.h"
#include "mpdu.h"
#include "cme_internal_api.h"
#include "cme_supplicant_api.h"
#include "eloop.h"
#include "gtrace.h"
#include "802_11defs.h"
#include "common.h"
#include "l2_cfg.h"
#include "fw_utils.h"
#include "lower_mac_if.h"
#include "mlme_parser.h"
#include "regulatory_domain_api.h"


// ============================================================================
//      Modules private definitions
// ============================================================================

// AC parameters extraction
#define AC_PARAMS_AIFSN_MASK               (0x0f)
#define AC_PARAMS_ACID_MASK                (0x60)
#define AC_PARAMS_CWMIN_MASK               (0x0f)
#define AC_PARAMS_CWMAX_MASK               (0xf0)
#define AC_PARAMS_ACM_MASK                 (0x10)

#define AC_PARAMS_ACID_SHIFT                  (5)

#define AC_INFO_FIELD_UAPSD_MASK            (0x80)

// QOS max allowed values
#define QOS_CWMAX_MAX                        (15)
#define QOS_CWMIN_MAX                        (15)
#define QOS_TX_OP_LIMIT_MAX                (32000)


// Maximal allowed value of AID
#define IEEE80211_MAX_AID      (2007)

// The below affect connection sequence behavior
#define AUTH_MAX_TRIES            (3)
#define ASSOC_MAX_TRIES           (3)

#define SPECIAL_BG_CHANNEL      (14)

// Debug info
#ifdef CC33XX_DRIVER_DEBUG
#define CC33_DRIVER_INC_NUM_STA_AUTH()      (++gSuppDrvDebugInfo_ull.sta.numAuthAttempts)
#endif

// ============================================================================
//      Local APIs
// ============================================================================

static void setRates(ti_driver_ifData_t   *apDrv,
                     RoleCommonParam_t       *apRates,
                     cmeScanCandidateDesc_t *apCandidateDesc);

static int32_t startStaRole(ti_driver_ifData_t          *apDrv,
                          struct wpa_driver_auth_params *apParams,
                          cmeScanCandidateDesc_t        *apCandidateDesc);



// ============================================================================
//      Structure
// ============================================================================

// ============================================================================
//      Exported APIs
// ============================================================================
/* ----------------------------------------------------------------------------
 ti_driver_authenticate
      This function handles authentication request from wpa_supplicant.
      Flow is based on NLCP driver.

 Parameters:    apPriv - pointer to drive instance
                apParams - peer parameters
 Return code:   0 - on success, -1 - failure in sanity tests

 MCP note:
      There's no equivalent code in driver_wilink since connection is managed by
      MCP internal SME.
      The auth packet is constructed in mlme_authMsgBuild.
      All management packets are sent using mlmeBuilder_sendFrame which allocates
      a management packet and builds the 802.11 header (sets mng type, MAC addresses, flags ...)
---------------------------------------------------------------------------- */
int ti_driver_authenticate(void *apPriv, struct wpa_driver_auth_params *apParams)
{
    int rc;
    ti_driver_ifData_t  *pDrv = (ti_driver_ifData_t *)apPriv;
    authInfo_t           *pAuthInfo;
    RadioBand_e          band;
    Channel_e            channel;
    cmeScanCandidateDesc_t *pCandidateDesc = NULL;
    int8_t max_tx_power;

    GTRACE(GRP_DRIVER_CC33, "Authenticate: role ID %d, auth alg 0x%x", pDrv->roleId, apParams->auth_alg);
    MLME_REPORT_PRINT("\n\rAuthenticate: role ID %d, auth alg 0x%x", pDrv->roleId, apParams->auth_alg);
#ifdef CC33XX_DRIVER_DEBUG
    CC33_DRIVER_INC_NUM_STA_AUTH();
#endif

    // --------------------------
    //  Role preparations
    // --------------------------
    // Sanity checks, STA based role should be enabled at this point
    if (INVALID_ROLE_ID == pDrv->roleId)
    {
        GTRACE(GRP_DRIVER_CC33, "Authenticate: invalid role ID");
        MLME_REPORT_PRINT_ERROR("\n\rAuthenticate: invalid role ID ");
        ASSERT_GENERAL(0);
    }
    if (FALSE == ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
    {
        GTRACE(GRP_DRIVER_CC33, "Authenticate: invalid role ID");
        MLME_REPORT_PRINT_ERROR("\n\rAuthenticate: invalid role ,roleType %d", pDrv->roleType);
    }

    ASSERT_GENERAL(ROLE_IS_TYPE_STA_BASED(pDrv->roleType));

    if (ROLE_IS_TYPE_STA(pDrv->roleType))
    {
        // when trying to authenticate during the regular CME connection flow the CME state is CME_STA_SUPPLICANT_MANAGED_STATE.
        // if thats not the case, it means we were already connected and we are roaming now.
        if (CmeStationFlow_GetCurrentState() != CME_STA_SUPPLICANT_MANAGED_STATE)
        {
            gBssTransitionState = TRANSITION_IN_PROGRESS;
        }
    }
    
    // Reset DB for the new connection (as in driver_80211.c, nl80211_mark_disconnected)
    markDisconnected(pDrv, __LINE__);

    // Keep candidate BSSID for sanity checks on potential RX deauth/disassoc
    IRQ_UtilZeroMacAddress(pDrv->authBssid);

    // ------------------------------------------
    // Keep AP parameters on private driver DB
    // ------------------------------------------
    //pAuthInfo is used only for the authentication process, in which we are not going to power save. GLX should be used.
    pAuthInfo = os_zalloc(sizeof(authInfo_t) + apParams->ie_len);
    ASSERT_GENERAL(NULL != pAuthInfo);

#ifdef CONFIG_SAE
    if(apParams->auth_data_len > 0)
    {
        // Copy auth_data to pAuthInfo
        GTRACE(GRP_DRIVER_CC33, "ti_driver_authenticate: SAE auth commit, auth_data_len = %d", apParams->auth_data_len);
        pAuthInfo->auth_data_len = apParams->auth_data_len;
        pAuthInfo->auth_data = os_zalloc(apParams->auth_data_len);
        os_memcpy(pAuthInfo->auth_data, apParams->auth_data, apParams->auth_data_len);
    }
#endif

    // TODO- Parse keys, and perform sanity checks
    // see nl80211.c, nl80211_authenticate

    // For shared key verify keys - taken from wireless\mlme.c, __cfg80211_mlme_auth
//  if (auth_type == NL80211_AUTHTYPE_SHARED_KEY)
//      if (!key || !key_len || key_idx < 0 || key_idx > 4)
//          return -EINVAL;

    // Translate supplicant authentication type to 802.11 types
    if (apParams->auth_alg & WPA_AUTH_ALG_OPEN)
        pAuthInfo->authType = AUTH_ALG_TYPE_OPEN_SYSTEM;
    else if (apParams->auth_alg & WPA_AUTH_ALG_SHARED)
        pAuthInfo->authType = AUTH_ALG_TYPE_SHARED_KEY;
    else if (apParams->auth_alg & WPA_AUTH_ALG_LEAP)
        pAuthInfo->authType = AUTH_ALG_TYPE_LEAP;
    else if (apParams->auth_alg & WPA_AUTH_ALG_FT)
        pAuthInfo->authType = AUTH_ALG_TYPE_FT;
    else if (apParams->auth_alg & WPA_AUTH_ALG_SAE)
        pAuthInfo->authType = AUTH_ALG_TYPE_SAE;
    // note: apParams->sae_data is ignored fron \net\wireless\mlme.c and down
    else
        ASSERT_GENERAL(0);

    // BSSID
    if (NULL != apParams->bssid)
    {
        IRQ_UtilCopyMacAddress(apParams->bssid, pAuthInfo->peerInfo.bssid);
    }

    // AP channel
    rc = freq_to_chan(apParams->freq, &channel, (uint8_t *)&band);
    if (rc < 0)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: can't find channel/band for frequencey %d",  apParams->freq);
        os_free(pAuthInfo);
        return -1;
    }
    pDrv->assocFreq = apParams->freq;

    // Extra IEs - TODO - this is imported from NLCP, does it ever happen?
    // if not, pAuthInfo->ie can be removed
    if (apParams->ie && apParams->ie_len)
    {
        os_memcpy(pAuthInfo->ie, apParams->ie, apParams->ie_len);
        pAuthInfo->ie_len = apParams->ie_len;
    }

    // Supplicant information doesn't contain all needed information.
    // In MCP missing data is set by STA engine when candidate is selected.
    // In NLCP missing data is taken from scan results DB.
    // For the mean time we follow NLCP behavior.

    // In WPS, several scan results may exists. So, anyway, search the appropriate candidate in the scan results table.

    //Find the target network in the candidates table
    pCandidateDesc = CME_FindBssidInCandidatesScanTable (apParams->bssid);
    if (NULL == pCandidateDesc)
    {
        os_free(pAuthInfo);
        return -1;
    }

    if (pCandidateDesc->nonTransmittingBssid)
    {
        IRQ_UtilCopyMacAddress(apParams->bssid, pDrv->mbssidData.TransmittingBssid);
        pDrv->mbssidData.mbssidIndex = pCandidateDesc->mbssidIndex;
        pDrv->mbssidData.mbssidIndicator = pCandidateDesc->mbssidIndicator;
    }
    else 
    {
        memset(&pDrv->mbssidData, 0, sizeof pDrv->mbssidData);
    }

    pAuthInfo->peerInfo.beacon_interval = pCandidateDesc->mScanResult.beacon_int;
    pAuthInfo->peerInfo.tsfOffset = pCandidateDesc->mScanResult.tsf;

#ifdef CONFIG_SAE
    if(pAuthInfo->authType == AUTH_ALG_TYPE_SAE && ((NULL != pDrv->pAuthInfo) && (TRUE == pDrv->pAuthInfo->done)))
    {
        // we already send commit, now we are going to send confirm
        destroyAuthData(pDrv, TRUE);
        pDrv->pAuthInfo = pAuthInfo;
        
        goto auth;
    }
#endif
    // Sanity check on command parameters has passed
    // Now check auth state, if we're  already authenticated disconnect and clear DB
    if ( ((NULL != pDrv->pAuthInfo) && (TRUE == pDrv->pAuthInfo->done)) ||
          (NULL != pDrv->pAssocInfo) )
    {
        GTRACE(GRP_DRIVER_CC33, "Warning, got authentication request while we're already authenticated; pAuthInfo 0x%x pAssocInfo 0x%x",
                                pDrv->pAuthInfo, pDrv->pAssocInfo);
        os_free(pAuthInfo);
        return -1;
    }

    if (apParams->auth_alg & WPA_AUTH_ALG_SHARED)
    {
        // WEP not supported

//        // In this case we need the WEP key before authentication, so we can encrypt the challenge.
//        int keyId = apParams->wep_tx_keyidx;
//
////        SecurityWepTkipUnion_u * auxM0SecKeys = (SecurityWepTkipUnion_u*)(M0_WEP_TKIP_PTRS);
//        SecurityWepTkipUnion_u * auxM0SecKeys = &wepTkipKeysShared;
//        WEPKey_t * pWEPKey = &(auxM0SecKeys->wep);
//        pWEPKey->keySize = apParams->wep_key_len[keyId];
//        pWEPKey->keyId = keyId;
//        //--------------------------------------------------------
//        // Init the WEP key
//        //--------------------------------------------------------
//        os_memcpy(pWEPKey->wepKey, apParams->wep_key[keyId], apParams->wep_key_len[keyId]);
//
//        // Now we will set the link security type although we are not yet connected
//        CC33_LinkDb_t *linkEntry;
//        uint8_t linkId = Roles_GetMainLinkId(pDrv->roleId);
//        linkEntry = Links_getLinkHwEntry(linkId);
//        linkEntry->encryption_uc.encryption_type_uc = CIPHER_SUITE_WEP;
    }

    // If for any reason there are auth leftovers on driver DB, clean them

    if (NULL != pDrv->pAuthInfo)
    {
        MLME_REPORT_PRINT("\n\rti_driver_authenticate:destroyAuthData , destroy old auth data");
        destroyAuthData(pDrv, TRUE);
    }
    pDrv->pAuthInfo = pAuthInfo;

    if (TRUE == pDrv->associated)
    {
        ASSERT_GENERAL(0);
        finalizeStaDisconnect(pDrv, __LINE__);
    }

	//Send max_tx_power to firmware
    regulatoryDomain_getChMaxPower(channel, &max_tx_power);
    regulatoryDomain_setRoleMaxTxPower(pDrv, max_tx_power);

    // in case of roaming, we need to stop the current role before starting a new one
    if (TRANSITION_IN_PROGRESS == gBssTransitionState)
    {
        // to resolve an IOP issue we had, we disassociate from the first ap before transitioning to the new one.
        // although not required by the spec, this action is allowed.
        ti_drv_txDeauthDisassocPacket(pDrv, (uint8_t *)pDrv->wpa_s->sme.prev_bssid, FRAME_TYPE_DISASSOCIATION, WLAN_REASON_BSS_TRANSITION_DISASSOC);

        stopStaRole(pDrv);
    }

    // Send start role command to FW and wait blocking for response
    startStaRole(pDrv, apParams, pCandidateDesc);

    // Copy the security info to link DB and free memory
//    for (i=0 ; i<4 ; ++i)
//    {
//        if (NULL != pDrv->pSecKey[i])
//        {
//            rsn_addKey(pDrv->roleId, pDrv->pSecKey[i]);
//            mem_Free_glx(pDrv->pSecKey[i]);
//            pDrv->pSecKey[i] = NULL;
//            break;
//        }
//    }

auth:
    try2authenticate(pDrv);

    return 0;
}

/* ----------------------------------------------------------------------------
 ti_driver_deauthenticate
      This function handles a deauthentication request from wpa_supplicant.
      Flow is based on NLCP driver.

 Parameters:    apPriv - pointer to drive instance
                apBssid - BSSID to connect from
                aReasonCode - reason to be sent to peer
 Return code:   0 - on success, -1 - failure in sanity tests
---------------------------------------------------------------------------- */
int ti_driver_deauthenticate(void *apPriv, const u8 *apBssid, u16 aReasonCode)
{
    char  macStr[MAC_STR_LEN];
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    int status = 0;
    GET_MAC_STR(apBssid, macStr);
    GTRACE(GRP_DRIVER_CC33, "Deauthenticate: BSSID %s, reason %d", macStr, aReasonCode);
    MLME_REPORT_PRINT("\n\rti_driver_deauthenticate: roleType:%d BSSID %s, reason %d\n",
            pDrv->roleType,macStr, aReasonCode);


    if (FALSE == ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
    {
        GTRACE(GRP_DRIVER_CC33, "No need to handle deauthenticate request for AP based role:%d", pDrv->roleType);
        MLME_REPORT_PRINT_ERROR("\n\rNo need to handle deauthenticate for AP based role:%d\n", pDrv->roleType);
        return -1;
    }

    // Keep disconnection reason; to be reported to CME when supplicant sets
    // state to disconnected.
    pDrv->deauthReason = aReasonCode;

    //
    // the code below was imported from mac80211, mlme.c, ieee80211_mgd_deauth
    //

    // If we're still in authentication phase, clear info.
    if (NULL != pDrv->pAuthInfo)
    {
        // associated flag is set when receiving assoc response packet, at this
        // stage pDrv->pAuthInfo is cleared.
        // So if we got here associated must be FALSE, double check.
        ASSERT_GENERAL(FALSE == pDrv->associated);

        MLME_REPORT_PRINT("\n\rti_driver_deauthenticate:destroyAuthData");
        destroyAuthData(pDrv, TRUE);
    }

    // If we're still in association phase, clear info.
    if (NULL != pDrv->pAssocInfo)
    {
        // associated flag is set when receiving assoc response packet, at this
        // stage pDrv->pAssocInfo is cleared.
        // So if we got here associated must be FALSE, double check.
        MLME_REPORT_PRINT_ERROR("\n\rti_driver_deauthenticate:destroyAssocData");
        ASSERT_GENERAL(FALSE == pDrv->associated);
        destroyAssocData(pDrv, FALSE);
    }
    if (NULL != pDrv->assoc_req_ies)
    {
        clear_assoc_req_ies(pDrv);
    }

    // If we're already associated, tear down BA session (if exists) and send a
    // deauth packet
    if (pDrv->associated &&
        IRQ_UtilCompareMacAddress(pDrv->currBssid, apBssid))
    {
        // TODO - tear down BA session

        //Send deauth packet (blocking till sequence is completed)
        status = ti_drv_txDeauthDisassocPacket(pDrv, (uint8_t *)apBssid, FRAME_TYPE_DEAUTHENTICATION, aReasonCode);//for possible reasons search :WLAN_REASON_*
    }

    // Complete the stop role sequence
    finalizeStaDisconnect(pDrv, __LINE__);

    return status;
}

// ----------------------------------------------------------------------------
// NLCP - role_id, band, channel, basic_rate_set, beacon_interval,ssid_type, ssid_len, ssid, bssid, local_rates, channel_type, remote_rates
// MCP-  ssid_len, ssid, bssid
// missing in MCP - roleID, band, channel, basicRateSet, beaconInterval, localSupportedRates, remotePeerSupportedRates
// MCP builds the packet in mlme_assocRequestMsgBuild,  activated from mlme_sendAssocRequest

/* ----------------------------------------------------------------------------
 ti_driver_associate
      This function sends association request packet based on supplciant parameters

 Parameters:    apPriv - pointer to drive instance
                apParams - peer parameters
 Return code:   0 - on success, -1 - failure in sanity tests
---------------------------------------------------------------------------- */
int ti_driver_associate(void *apPriv,struct wpa_driver_associate_params *apParams)
{
    int    rc = 0;
    assocInfo_t          *pAssocInfo;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    GTRACE(GRP_DRIVER_CC33, "ti_driver_associate: Associate: mode:%d roleType: %d", apParams->mode, pDrv->roleType);
    MLME_REPORT_PRINT("\n\rti_driver_associate: Associate: mode:%d roleType: %d", apParams->mode, pDrv->roleType);


    // Role should be enabled at this point
    if (INVALID_ROLE_ID == pDrv->roleId)
    {
        GTRACE(GRP_DRIVER_CC33, "Associate: invalid role ID");
        ASSERT_GENERAL(0);
    }
    else if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
        // There's nothing to do here for AP role ...
        MLME_REPORT_PRINT("\n\rti_driver_associate: exit Associate:for AP role");
        return 0;
    }

    // Sanity checks on parameters and state
    if (0 == apParams->ssid_len)
    {
        return -1;
    }

    // We should be authenticated by now, if not this is an error
    if ( (NULL != pDrv->pAuthInfo) && (TRUE != pDrv->pAuthInfo->done) )
    {
        GTRACE(GRP_DRIVER_CC33, "Warning, got association command while not authenticated");
        ASSERT_GENERAL(FALSE);
        return -1;
    }

    if (NULL != pDrv->pAssocInfo)
    {
        GTRACE(GRP_DRIVER_CC33, "Warning, got association command before previous attempt ended");
        ASSERT_GENERAL(FALSE);
        return -1;
    }

    // Handle auth & security
    rsn_setAuthParams(pDrv->roleId, apParams->auth_alg, apParams->key_mgmt_suite, apParams->wpa_ie, apParams->wpa_ie_len);
    rsn_setCryptoParams(pDrv->roleId, apParams->pairwise_suite, apParams->group_suite);

    // configure WPS
//    wps_enabled = (KEY_MGMT_WPS == apParams->key_mgmt_suite);       // TODO

    // ------------------------------------------
    // Keep AP parameters on private driver DB
    // ------------------------------------------
    // (based on mac80211\mlme.c ieee80211_mgd_assoc
    //pAssocInfo is used only for the association process, in which we are not going to power save. GLX should be used.
    pAssocInfo = os_zalloc(sizeof(assocInfo_t) + apParams->wpa_ie_len);
    if (pAssocInfo == NULL)
    {
        CME_PRINT_REPORT_ERROR("\n\rti_driver_associate:allocate pAssocInfo failed: sizeof(assocInfo_t):%d + wpa_ie_len:%d", sizeof(assocInfo_t),apParams->wpa_ie_len);
        ASSERT_GENERAL(FALSE);
        return -1;

    }
    // Init descriptor & descriptor state state
    pAssocInfo->descriptorState = ASSOC_REQ_DESC_INVALID;
// TODO: need to implmenet
#if 0
    pAssocInfo->descriptorId = TXC_NO_VIRT_DESC;
#endif
	if (NULL != pDrv->pAuthInfo)
	{
		// TODO - NLCP sets the flag to TRUE in case BSSID doesn't match
		// how is it possible to associate with another BSSID?
        MLME_REPORT_PRINT("\n\rti_driver_associate:destroyAuthData");
		destroyAuthData(pDrv, FALSE);
	}

    // BSSID
    if (NULL != apParams->bssid)
    {
        IRQ_UtilCopyMacAddress(apParams->bssid, pAssocInfo->peerInfo.bssid);
    }

    // Check the prev_bssid param.
    // When not set to null, this is a request to use reassociation instead of association.
    // prev_bssid is the bssid of the AP we are leaving.
    // keep it for building the reassociation request packet.
    if (NULL != apParams->prev_bssid)
    {
        IRQ_UtilCopyMacAddress(apParams->prev_bssid, pAssocInfo->prev_bssid);
    }

    // Keep SSID
    memcpy(pAssocInfo->ssid, apParams->ssid, apParams->ssid_len);
    pAssocInfo->ssid_len = apParams->ssid_len;

    pDrv->pAssocInfo = pAssocInfo;

    // All other capabilities are adde to the association request in the function below
    rc = try2associate(pDrv, apParams);
    return rc;
}

/* ----------------------------------------------------------------------------
 ti_driver_get_bssid
      This API serves for STA role only.
      If STA is connected, it returns the BSSID of currently connected AP.
      Else it returns 00:00:00:00:00:00

 Parameters:    IN  apPriv - Pointer to driver object
                OUT apBssid - Pointer to current BSSID
 Return code:   0 - BSSID is valid; -1 - else
---------------------------------------------------------------------------- */
int ti_driver_get_bssid(void *apPriv, u8 *apBssid)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    char macStr[MAC_STR_LEN];

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    if (FALSE == pDrv->associated)
    {
        IRQ_UtilZeroMacAddress(apBssid);
        return -1;
    }

    IRQ_UtilCopyMacAddress(pDrv->currBssid, apBssid);

    GET_MAC_STR(apBssid, macStr);
    GTRACE(GRP_DRIVER_CC33, "Return BSSID %s to supplicant", macStr);

    return 0;
}

/* ----------------------------------------------------------------------------
 ti_driver_get_ssid
      This API serves for STA role only.
      If STA is connected, it returns the SSID of currently connected AP.
      Else it returns NULL

 Parameters:    IN  apPriv - Pointer to driver object
                OUT apSsid - Pointer to current SSID string
 Return code:   SSID length - if STA is associated; 0 - else
---------------------------------------------------------------------------- */
int ti_driver_get_ssid(void *apPriv, u8 *apSsid)
{
    uint32_t ssidLen = 0;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    if (FALSE == pDrv->associated)
        return ssidLen;

    ssidLen = pDrv->ssid_len;
    if ( 0 < ssidLen)
    {
        os_memcpy(apSsid, pDrv->ssid, pDrv->ssid_len);
    }

    GTRACE(GRP_DRIVER_CC33, "Return SSID %s of len %d to supplicant", apSsid, ssidLen);

    return ssidLen;
}

/* ----------------------------------------------------------------------------
 ti_driver_add_pmkid
    This API serves for STA role only.
    If STA is connected with WPA3 to the AP, it returns the PMKID.
    Else it returns NULL

 Parameters:    IN  apPriv - Pointer to driver object
                OUT pmkid  - Pointer to current PMKID cache
 Return code:   
---------------------------------------------------------------------------- */

int ti_driver_add_pmkid(void *apPriv, struct wpa_pmkid_params *pmkid)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    struct wpa_supplicant *wpa_s = pDrv->wpa_s;

    if ((wpa_s != NULL) && (pmkid != NULL))
    {
        CME_PRINT_REPORT("\n\rti_driver_add_pmkid: role id=%d, PMK len=%d reauth_threshhold=%d p_fils_cache_id:%p selected keymgmt=%d peer BSSID: " MACSTR, 
            pDrv->roleId, pmkid->pmk_len, pmkid->pmk_reauth_threshold, pmkid->fils_cache_id, wpa_s->key_mgmt, MAC2STR(pmkid->bssid));

        cmeAddWpaPmkCache(wpa_s, (uint8_t*)pmkid->pmkid, (uint8_t*)pmkid->pmk, pmkid->pmk_len, (uint8_t*)pmkid->bssid, wpa_s->key_mgmt);
    }

    return 0;
}

// ============================================================================
//      APIs shared between drv_cc33_xxx modules
// ============================================================================

// ----------------------------------------------------------------------------
void ti_drv_AuthTimeout(void *apDrv, void *apData2)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apDrv;

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    // If be any chance auth response was received before timeout was cancelled
    // there's nothing to do here
    if ( (NULL == pDrv->pAuthInfo) || (TRUE == pDrv->pAuthInfo->done) )
    {
        return;
    }

    GTRACE(GRP_DRIVER_CC33, "Authentication timed out, trial # %d", pDrv->pAuthInfo->tries);
    MLME_REPORT_PRINT("\n\rAuthentication timed out, trial # %d", pDrv->pAuthInfo->tries);


    // mac80211\mlme.c, ieee80211_probe_auth checks number of trials + existence of probe response.
    // it is assumed, at least for a start that we won't try to authenticate w/o probe response
    // so only part of the code is imported.
    // Note: tries is cleared when probe response is received + pDrv->pAuthInfo is valid
    //      TODO - does it mean we always have to receive probe response before really starting the
    //             authentication sequenc?
    if (AUTH_MAX_TRIES <= pDrv->pAuthInfo->tries)
    {
        uint8_t  bssid[ETH_ALEN];

        // Most likely AP is not in the range. NLCP removes the bss struct for that AP from cfg DB
        // Supplicant adds the AP to black list, so for the meantime do nothing more.

        // Clear authentication info before notifying the supplicant
        IRQ_UtilCopyMacAddress(pDrv->pAuthInfo->peerInfo.bssid, bssid);
        MLME_REPORT_PRINT("\n\rti_drv_AuthTimeout:destroyAuthData");
        ti_drv_txDeauthDisassocPacket(pDrv,
                                   (uint8_t *)pDrv->pAuthInfo->peerInfo.bssid,
                                   FRAME_TYPE_DEAUTHENTICATION,
                                   WLAN_REASON_PREV_AUTH_NOT_VALID); //for possible reasons search :WLAN_REASON_*
        destroyAuthData(apDrv, TRUE);

        drv_sendConnectTimeoutEvent(pDrv, EVENT_AUTH_TIMED_OUT, bssid);
        return;
    }

    // else, try one more time
    try2authenticate(pDrv);
}

// ----------------------------------------------------------------------------
void ti_drv_AssocTimeout(void *apDrv, void *apData2)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apDrv;

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    if (NULL == pDrv->pAssocInfo)
        return;

    GTRACE(GRP_DRIVER_CC33, "Association timed out, trial # %d", pDrv->pAssocInfo->tries);
    MLME_REPORT_PRINT("\n\rAssociation timed out, trial # %d", pDrv->pAssocInfo->tries);

    if (ASSOC_MAX_TRIES <= pDrv->pAssocInfo->tries)
    {
        uint8_t  bssid[ETH_ALEN];

        // Clear association info before notifiying the supplicant
        IRQ_UtilCopyMacAddress(pDrv->pAssocInfo->peerInfo.bssid, bssid);
        MLME_REPORT_PRINT("\n\rti_drv_AssocTimeout:destroyAssocData");
        destroyAssocData(apDrv, TRUE);
        clear_assoc_req_ies(pDrv);

        drv_sendConnectTimeoutEvent(pDrv, EVENT_ASSOC_TIMED_OUT, bssid);
        return;
    }

    // else, try one more time
    ti_drv_txAssocReqPacket(pDrv, NULL);
}



// ============================================================================
//      Local APIs
// ============================================================================

/* ----------------------------------------------------------------------------
 setRates
     Select rates for this link, based on local and peer rates; peer rates are
     extracted from received beacon/probe response.

 Parameters:    IN apDrv - pointer to drive instance
                OUT apCmdParams - pointer to the role start command where rates
                                  should be set
                IN apCandidateDesc - peer info, for getting peer rates
 Return code:   none
---------------------------------------------------------------------------- */
static void setRates(ti_driver_ifData_t   *apDrv,
                     RoleCommonParam_t       *apRates,
                     cmeScanCandidateDesc_t *apCandidateDesc)
{
    uint32_t basicRatesBM, supportedRatesBM;
    uint32_t locatSupportedRatesBM;
    CipherSuite_e cipherSuite;
    rateSets_t linkRates;

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    getPeerRates(apCandidateDesc, &linkRates);

    //
    // Set peer rates
    //
    apRates->basicRateSetBM = linkRates.basicRatesBM;
    apRates->remotePeerSupportedRatesBM = linkRates.supportedRatesBM;
    apRates->WMM = apCandidateDesc->wmmIePresent;

    //
    // Set local rates
    //

    cfgGetRates(ROLE_STA, &basicRatesBM, &supportedRatesBM);

    locatSupportedRatesBM = basicRatesBM | supportedRatesBM;

    // 11n rates are not allowed when security mode is TKIP or WEP
    cipherSuite = rsn_getPairwiseSuite();
    if ( (CIPHER_SUITE_TKIP == cipherSuite) || (CIPHER_SUITE_WEP == cipherSuite) )
    {
        EXCLUDE_MCS_RATES(locatSupportedRatesBM);
    }

    apRates->localSupportedRatesBM = locatSupportedRatesBM;

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);
}

/* ----------------------------------------------------------------------------
 startStaRole
    Prepare and send the start role command.
    The code is based on WL8 NLCP driver code which sends the command just before
    sending the authentication command.
    (For MCP start role is started by the internal SME, role parameters are taken
     from selected AP parameters).

 Parameters:    apDrv
 Return code:   0 - on success, -1 - error in memory allocation
---------------------------------------------------------------------------- */
static int32_t startStaRole(ti_driver_ifData_t          *apDrv,
                          struct wpa_driver_auth_params *apParams,
                          cmeScanCandidateDesc_t        *apCandidateDesc)
{
    RoleCommonParam_t              aRates;
    dot11Mode_e dot11mode = cfgGetStadot11Mode();
    SlotTime_e  slotTime;
    RadioBand_e band;
    Channel_e   channel;


    int ret = 0;

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    // TODO:
    // AC parameters
    // HT capabilities
    // ERP protection
    // Preamble type
    // are currently set when assoc response is received
    // we may set them here based on probe response.

    //
    // Set RF related parameters
    //
    freq_to_chan(apParams->freq, &channel, (uint8_t *)&band);

    //
    // STA specific parameters
    //

    // Select peer & local rates based on peer supported rates, selected channel
    // and encryption type and set them on role DB.
    setRates(apDrv, &aRates, apCandidateDesc);

    // Set slot time
    if (RADIO_BAND_2_4GHZ == band)
    {
        if (DOT11_B_MODE == dot11mode)
        {
            slotTime = SLOT_TIME_LONG;
        }
        else
        {
            ASSERT_GENERAL( (DOT11_G_MODE == dot11mode) || (DOT11_DUAL_MODE == dot11mode) );

            // If peer supports short slot, use own slot time
            if ( (apCandidateDesc->mScanResult.caps >> CAP_SLOT_TIME_SHIFT) & CAP_SLOT_TIME_MASK )
            {
                slotTime =  (cfgIsStaShortSlotEnabled()) ? SLOT_TIME_SHORT : SLOT_TIME_LONG;
            }
            // else, we have to use long slot
            else
            {
                slotTime = SLOT_TIME_LONG;
            }
        }
    }
    else
    {
        ASSERT_GENERAL( (DOT11_A_MODE == dot11mode) || (DOT11_DUAL_MODE == dot11mode) );

        slotTime = SLOT_TIME_SHORT;
    }

    ret = apDrv->ops->start_role((void*)apDrv, (void*)apParams, &aRates, slotTime);

    if(ret < 0)
    {
        GTRACE(GRP_DRIVER_CC33, " Role not Started rc id %d", ret);

        ASSERT_GENERAL(0);
    }

    rsn_SetDefaults(apDrv->roleId, FALSE /* default cipher suite is none */);

    // Mark role was started (should be used to avoid restarting an active role)
    apDrv->roleStarted = TRUE;

    os_memcpy(&apDrv->apRate, &aRates, sizeof (apDrv->apRate) );

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    return 0;
}

/* ----------------------------------------------------------------------------
 stopStaRole
    Send stop STA role to WLAN services and wait blocking till operation is
    fully completed and all role resources are released

 Parameters:    apDrv
 Return code:   0 - success
---------------------------------------------------------------------------- */
int32_t stopStaRole(ti_driver_ifData_t *apDrv)
{
    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    if (FALSE == apDrv->roleStarted)
    {
        GTRACE(GRP_DRIVER_CC33, "WARNING: Role %d wasn't started yet or already stopped, can't stop it", apDrv->roleId);
        return 0;
    }

    // If role is stopped before association was completed ROC is still on.
    // In this case we should ask for CROC before we can stop the role.
    if (TRUE == apDrv->rocActive)
    {
        // This call is blocking; when it returns CROC handling is completed
        apDrv->ops->cancel_remain_on_channel(apDrv);
    }

    apDrv->ops->stop_role(apDrv);

    // Mark role was stopped (should be used to avoid restarting an active role)
    apDrv->roleStarted = FALSE;

    return 0;
}

/* ----------------------------------------------------------------------------
 startDevOffchannelRole
    Prepare and send the start role command.

 Parameters:    apDrv -- the driver of the main channel role
 Return code:   0 - on success, -1 - error in memory allocation
---------------------------------------------------------------------------- */

/* start dev role and roc on its channel */
int32_t startDevOffchannelRole(void *apPriv, uint32_t aFreq)
{
    int32_t ret = 0;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    struct wpa_driver_ap_params input_params;

    os_memset(&input_params, 0, sizeof(input_params));
    input_params.freq = os_malloc(sizeof(struct hostapd_freq_params));

    GTRACE(GRP_DRIVER_CC33, "Start device role for freq :%d",aFreq);

    if (pDrv == NULL)
    {
        wpa_printf(MSG_ERROR, "Off-channel device doesn't exists! freq :%d", aFreq);
        CME_CON_PRINT_ERROR("\n\rti_driver: Off-channel device doesn't exists! freq :%d", aFreq);

        ret = -1;
        goto out_stop;

    }
    else
    {
        //otherwise role device already exists so use it
        if (pDrv->roleStarted == FALSE) 
        {
            pDrv->offChannel_role_enabled = 1;
            input_params.freq->freq = aFreq;

            ret = pDrv->ops->start_role(pDrv, &input_params, NULL, 0);
            if (ret < 0)
            {
                CME_CON_PRINT_ERROR("\n\rti_driver: enable device role ! freq :%d", aFreq);
                goto out_stop;
            }
            // Mark role was started (should be used to avoid restarting an active role)
            wpa_printf(MSG_INFO, "Off-channel device started freq :%d", pDrv->freq);

        }

        if (pDrv->freq != aFreq )
        {
            wpa_printf(MSG_ERROR, "role device exists with different freq: %d  required freq:%d",
                    pDrv->freq, aFreq);
            CME_CON_PRINT_ERROR("\n\rrole device exists with different freq: %d  required freq:%d",
                    pDrv->freq, aFreq);

            ASSERT_GENERAL(0);
            ret = -1;
            goto out_stop;
        }
    }

    if(pDrv->ops->remain_on_channel(pDrv, aFreq) < 0)
    {
        wpa_printf(MSG_ERROR, "ERROR: cmd remain_on_channel! (Freq %d)", aFreq);
        CME_CON_PRINT_ERROR("\n\rERROR: cmd remain_on_channel! (Freq %d)", aFreq);
        pDrv->offChannel_roc_started = 0;
        ASSERT_GENERAL(0);
        ret = -1;
        goto out_stop;
    }

    pDrv->offChannel_roc_started = 1; 
    CME_PRINT_ROC_REPORT("\n\rti_driver: ROC started");

    os_free(input_params.freq);

    return 0;

out_stop:
    stopDevOffchannelRole(pDrv);
    os_free(input_params.freq);
    return ret;
}

/* ----------------------------------------------------------------------------
 stopDevOffchannelRole
    Send stop DEV role to WLAN services and wait blocking till operation is
    fully completed and all role resources are released

 Parameters:    apDevDrv -- the device driver
 Return code:   0 - success
---------------------------------------------------------------------------- */
int32_t stopDevOffchannelRole(void *apDevPriv)
{
    int ret = 0;
    ti_driver_ifData_t *pDevDrv = (ti_driver_ifData_t *)apDevPriv;

    if(apDevPriv == NULL)
    {
        wpa_printf(MSG_WARNING, "stopDevOffchannelRole : no device role exists!!");
        return -1;
    }
    
    if(pDevDrv->roleStarted)
    {
        ret = pDevDrv->ops->stop_role(pDevDrv);
        if (ret < 0)
        {
            wpa_printf(MSG_ERROR, "stop_DEVICE role failed!!");
            goto out;
        }

    }

out:
    return ret;
}
/* ----------------------------------------------------------------------------
 startDeviceRole
    Device start role command.

 Parameters:    apDrv - pointer to device driver
                aFreq - frequency channel of listen/operational channel 
 Return code:   0 - on success, -1 - error in memory allocation
---------------------------------------------------------------------------- */
int32_t startDeviceRole(void *apPriv, uint32_t aFreq)
{
    int32_t ret = 0;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    struct wpa_driver_ap_params input_params;

    os_memset(&input_params, 0, sizeof(input_params));
    input_params.freq = os_malloc(sizeof(struct hostapd_freq_params));

    GTRACE(GRP_DRIVER_CC33, "Start device role for freq :%d",aFreq);

    input_params.freq->freq = aFreq;
    ret = pDrv->ops->start_role(pDrv, &input_params, NULL, 0);
    if (ret < 0)
    {
        wpa_printf(MSG_ERROR, "START DEVICE role failed!!");
        goto out;
    }
    pDrv->roleStarted = TRUE;
out:
    os_free(input_params.freq);
    return ret;
}
/* ----------------------------------------------------------------------------
 stopDeviceRole
    Send stop Device role to WLAN services and wait blocking till operation is
    fully completed and all role resources are released

 Parameters:    apDrv
 Return code:   0 - success
---------------------------------------------------------------------------- */
int32_t stopDeviceRole(ti_driver_ifData_t *apDrv)
{
    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    if (FALSE == apDrv->roleStarted)
    {
        GTRACE(GRP_DRIVER_CC33, "WARNING: Role %d wasn't started yet or already stopped, can't stop it", apDrv->roleId);
        return 0;
    }

    // If role is stopped before association was completed ROC is still on.
    // In this case we should ask for CROC before we can stop the role.
    if (TRUE == apDrv->rocActive)
    {
        // This call is blocking; when it returns CROC handling is completed
        apDrv->ops->cancel_remain_on_channel(apDrv);
    }

    apDrv->ops->stop_role(apDrv);

    // Mark role was stopped (should be used to avoid restarting an active role)
    apDrv->roleStarted = FALSE;

    return 0;
}

// ----------------------------------------------------------------------------
void destroyAuthData(ti_driver_ifData_t *apDrv, Bool32 aClearBssid)
{
    GTRACE(GRP_DRIVER_CC33, "Destroy auth info");
    MLME_REPORT_PRINT("\n\rDestroy auth info");


    if (TRUE == aClearBssid)
    {
        IRQ_UtilZeroMacAddress(apDrv->currBssid);
    }

    // Clear any timeout (if exists)
    eloop_cancel_timeout(ti_drv_AuthTimeout, apDrv, NULL);

#ifdef CONFIG_SAE
    if(apDrv->pAuthInfo->auth_data != NULL)
    {
        os_free(apDrv->pAuthInfo->auth_data);
        apDrv->pAuthInfo->auth_data = NULL;
    }
#endif
    if(apDrv->pAuthInfo != NULL)
    {
        os_free(apDrv->pAuthInfo);
        apDrv->pAuthInfo = NULL;
    }
}

// ----------------------------------------------------------------------------
void destroyAssocData(ti_driver_ifData_t *apDrv, Bool32 aDisassoc)
{
    GTRACE(GRP_DRIVER_CC33, "Destroy info : %d", (uint32_t)apDrv->pAssocInfo);
    //if((apDrv->pAssocInfo)  && (apDrv->pAssocInfo->pDescriptor != NULL))
    //{
    //    MLME_REPORT_PRINT("\n\rdestroyAssocData : %d", (uint32_t)apDrv->pAssocInfo->pDescriptor);
    //}

    // Free the association request packet, no retransmission is
    // expected at this point.
    CME_FreeTxDesc(apDrv->pAssocInfo->pDescriptor);
    apDrv->pAssocInfo->pDescriptor = NULL;

    if (aDisassoc)
    {
        IRQ_UtilZeroMacAddress(apDrv->currBssid);
    }

    // Clear any timeout (if exists)
    eloop_cancel_timeout(ti_drv_AssocTimeout, apDrv, NULL);

    os_free(apDrv->pAssocInfo);
    apDrv->pAssocInfo = NULL;

}

// ----------------------------------------------------------------------------
void clear_assoc_req_ies(ti_driver_ifData_t *apDrv)
{
    os_free(apDrv->assoc_req_ies);
    apDrv->assoc_req_ies = NULL;
    apDrv->assoc_req_ies_len = 0;
}

// ----------------------------------------------------------------------------
int32_t try2authenticate(ti_driver_ifData_t *apDrv)
{
    char macStr[MAC_STR_LEN];
    int32_t status = OK;

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    // Peer info should exit at this point, double check
    ASSERT_GENERAL((NULL != apDrv->pAuthInfo));

    // Increment number of retries; it is tested in ti_drv_AuthTimeout and if
    // maximal allowed number is reached we give up this connection.
    ++apDrv->pAuthInfo->tries;

    GET_MAC_STR(apDrv->pAuthInfo->peerInfo.bssid, macStr);

    // Build authentication packet and push it forward to data path
    if (NULL != apDrv->pAuthInfo)
    {
        // Activate ROC only if not already activated.
        // If auth was timed out we may get here while ROC is already active
        if (FALSE == apDrv->rocActive)
        {
            // Remain on channel until authentication sequence ends
            apDrv->ops->remain_on_channel(apDrv, apDrv->assocFreq);
        }
        MLME_REPORT_PRINT("\n\rSending auth request packet to %s (auth type ENUM(authType_e, %d) # tries %d)",
                                macStr, apDrv->pAuthInfo->authType, apDrv->pAuthInfo->tries);

        GTRACE(GRP_DRIVER_CC33, "Sending auth request packet to %s (auth type ENUM(authType_e, %d) # tries %d)",
                                macStr, apDrv->pAuthInfo->authType, apDrv->pAuthInfo->tries);
        status = ti_drv_txAuthReqPacket(apDrv, apDrv->pAuthInfo->authType);
    }

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    return status;
}

// ----------------------------------------------------------------------------
int32_t try2associate(ti_driver_ifData_t *apDrv, struct wpa_driver_associate_params *apParams)
{
    char macStr[MAC_STR_LEN];

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    ++apDrv->pAssocInfo->tries;

    GET_MAC_STR(apDrv->pAssocInfo->peerInfo.bssid, macStr);

    if (ASSOC_MAX_TRIES < apDrv->pAssocInfo->tries)
    {
        GTRACE(GRP_DRIVER_CC33, "association with %s timed out", macStr);
        finalizeStaDisconnect(apDrv, 916);
        return -1;
    }

    GTRACE(GRP_DRIVER_CC33, "Sending assoc request packet to %s # tries %d ", macStr, apDrv->pAssocInfo->tries);

    // The API below construct an association request packet (if needed)
    // and sends the packet to LTXP. It also arms a timer limiting the time
    // we can wait for peer response.
    ti_drv_txAssocReqPacket(apDrv, apParams);

    return 0;
}


// ----------------------------------------------------------------------------
// WL8 sets AC parameters using ACX_AC_CFG based on association response packet
// This structure contains the parameters that might be changed after association.
// Relevant only for STA & client.
void updateACParams(dot11_ACParameters_t *apAcParams, RolePostAssocParameters_t *apParams)
{
    uint32_t acId, ac;
    uint8_t  cwMin; 
    uint16_t cwMax;
    dot11_QOS_AC_IE_Params_t *pACParameteresRecord;
    uint16_t txOpLimit;

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    pACParameteresRecord = (dot11_QOS_AC_IE_Params_t *)apAcParams;

    for (ac=0 ;  ac<NUM_ACCESS_CATEGORIES ; ac++, pACParameteresRecord++)
    {
        acId = (pACParameteresRecord->ACI_AIFSN & AC_PARAMS_ACID_MASK) >> AC_PARAMS_ACID_SHIFT;

        // michal - ac is no longer part of the structure
        //acQosParams.ac = acId;
        apParams->acParameters[ac].aifsn = pACParameteresRecord->ACI_AIFSN & AC_PARAMS_AIFSN_MASK;
        apParams->acParameters[ac].acm   = pACParameteresRecord->ACI_AIFSN & AC_PARAMS_ACM_MASK;

        //txoplimit is only uint16_t, make sure we don't exceed.
        if (pACParameteresRecord->TXOPLimit > 0x7ff)
        {
            txOpLimit = 0xffff;
        }
        else
        {
            txOpLimit = pACParameteresRecord->TXOPLimit << 5;
        }
        apParams->acParameters[ac].txopLimit = txOpLimit;

        cwMin = pACParameteresRecord->ECWmin_ECWmax & AC_PARAMS_CWMIN_MASK;
        apParams->acParameters[ac].cwMin = ((1 << cwMin) - 1);   /* CwMin = 2^CwMin - 1*/

        cwMax = (pACParameteresRecord->ECWmin_ECWmax & AC_PARAMS_CWMAX_MASK) >> 4;
        apParams->acParameters[ac].cwMax =  ((1 << cwMax) - 1);   /* CwMax = 2^CwMax - 1*/

        GTRACE(GRP_DRIVER_CC33, "Setting AC cfg: ac %d cwMin %d cwMax %d AIFSN from IE: 0X%x, AIFSN %d TXOP limit %d",
                                 ac, cwMin, cwMax,
                                 pACParameteresRecord->ACI_AIFSN, apParams->acParameters[ac].aifsn, apParams->acParameters[ac].txopLimit);

        // Sanity check on the received parameters
        if ( (QOS_CWMIN_MAX < cwMin) || (QOS_CWMAX_MAX < cwMax) ||
             (QOS_TX_OP_LIMIT_MAX < apParams->acParameters[ac].txopLimit) ||
             (NUM_ACCESS_CATEGORIES <= acId) )
        {
            GTRACE(GRP_GENERAL_ERROR, "ERROR in AC parameters: ac %d cwMin %d cwMax %d TXOP limit %d",
                                       acId, cwMin, cwMax, apParams->acParameters[ac].txopLimit);
        }
    }
}

//-----------------------------------------------------------------------------
void updateUAPSDConfiguration(dot11_WME_PARAM_t *apWmeParamIE, RolePostAssocParameters_t *apParams)
{
    int i;
    Bool_e isAPSD = TRUE;
    Bool_e isMixedMode = FALSE;

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    apParams->psScheme = PS_SCHEME_LEGACY; //Default value

    //Check first if AP supports UPSD

    //Make sure this is the correct WMM
    if ((apWmeParamIE->OUIType == dot11_WME_OUI_TYPE) &&
        (apWmeParamIE->OUISubType == dot11_WME_OUI_SUB_TYPE_PARAMS_IE))
    {
        //qos_info field (same as AcInfoField) bit 7 is UAPSD configuration of AP
        if (apWmeParamIE->ACInfoField & AC_INFO_FIELD_UAPSD_MASK) //AP supports UAPSD
        {
            //Check per AC power save configuration
            for (i=0; i< NUM_ACCESS_CATEGORIES; i++)
            {
                // TODO: need to implement
                isMixedMode |= (gL2DynamicCfg.acPsMode.wmeAcPsMode[i] == PS_SCHEME_UPSD_TRIGGER); //TRUE if at least one AC is UPSD
                isAPSD &= (gL2DynamicCfg.acPsMode.wmeAcPsMode[i] == PS_SCHEME_UPSD_TRIGGER); //FALSE if at least one AC is not UPSD
            }

            if (isAPSD)
            {
                apParams->psScheme = PS_SCHEME_UPSD_TRIGGER;
            }
            else if (isMixedMode)
            {
                apParams->psScheme = PS_SCHEME_MIXED_MODE;
            }
        }
    }
}

/* setPeerHtCapabilities - set ap peer Cap and BSS cap based on HT CAP IE and HT INFO IE
 *
 *Input Parameters:    apHtCapabilitiesPos  - pointer to the HT CAP info element Date (not includes the id and len)
 *                     apHtInformationPos   - pointer to the HT Operation info element Date (not includes the id and len)
 *Output Parameters:   apHtCfg              - pointer to the ht BSS cap from the AP, to be stored in RolePostAssocParameters_t  struct
 *                     apPeerCapParams      - pointer to the ht Peer cap from the AP, to be stored in RolePostAssocParameters_t struct
 *Return code:   void
 *
 */
void setPeerHtCapabilities(uint8_t            *apHtCapabilitiesPos,
                           uint8_t            *apHtInformationPos,
                           htBssCap_t       *apHtCfg,            // OUT - HT parameters structure (part of role start parameters)
                           htPeerCap_t      *apPeerCapParams)    // OUT - Peer capabilities structure (part of role start parameters)
{
    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    // If both local & peer support 11n & HT, set peer capabilities
    if ( (FALSE != cfgIs11nEnabled()) && (FALSE != cfgIsStaWmeEnabled()) &&
         (NULL != apHtCapabilitiesPos) && (NULL != apHtInformationPos) )
    {

        uint16_t htCapabilitiesField;
        uint32_t ampduParams;


        /* get data from HT capabilities field (and handle endian) */
        COPY_WLAN_WORD(&htCapabilitiesField,apHtCapabilitiesPos);

        /* get date from A-MPDU parameters field */
        ampduParams = apHtCapabilitiesPos[HT_CAP_AMPDU_PARAMETERS_FIELD_OFFSET];

        /* set the ht cap params*/
        apPeerCapParams->uAmpduMaxLength = (ampduParams & HT_CAP_AMPDU_MAX_SIZE_BITMASK);
        apPeerCapParams->uAmpduMinSpacing = ((ampduParams & HT_CAP_AMPDU_SPACING_BITMASK) >> HT_CAP_AMPDU_SPACING_OFFSET);
        apPeerCapParams->htCapabilites = htCapabilitiesField;
        apPeerCapParams->htCapabilites |= htCapabilitiesField ? HT_CAP_HT_OPERRATION : 0;

        // ACX_HT_BSS_OPERATION
        apHtCfg->rifsMode          = ((apHtInformationPos[1] & HT_INF_RIFS_MOD_BITMASK) >> 3);              // HT_RIFS_MODE , in second bite
        apHtCfg->htProtection      = (apHtInformationPos[2] & HT_INF_PROTECTION_MOD_BITMASK);               // HT_PROT
        apHtCfg->gfProtection      = ((apHtInformationPos[2] & HT_INF_NON_GF_PRES_BITMASK) >> 2);           //HT_GF_PROT
        apHtCfg->dualCtsProtection = ((apHtInformationPos[4] & HT_INF_DUAL_CTS_PROTECTION_BITMASK) >> 7);   //HT_DUAL_CTS_PROT(apHtInformation);

        GTRACE(GRP_HE, "setPeerHtCapabilities: HT peer capabilities are set succefully.uAmpduMinSpacing: %d, uAmpduMaxLength: %d, htCapabilites :0x%x"
               ,apPeerCapParams->uAmpduMinSpacing, apPeerCapParams->uAmpduMaxLength, apPeerCapParams->htCapabilites);

        // TODO set htInfoParamas
    }
    else
    {
        apPeerCapParams->uAmpduMaxLength = 0;
        apPeerCapParams->uAmpduMinSpacing = 0;
        apPeerCapParams->htCapabilites = 0;
    }
}

#ifndef DISABLE_WIFI6
/******************************************************************************
  Function          : setPeerHeCapabilities

  Description       : Set ap peer Cap and BSS cap based on HE CAP IE and HE OPER IE,
                      will be later used for post association params

  Input parameters  : apHeCapabilitiesPos -  pointer to the HE CAP info element Date (not includes the id and len)
                      apHeOperationPos    -  pointer to the HE OPERATION info element Date (not includes the id and len)

  Output parameters : apHeBssCfg          -  pointer to the he BSS cap from the AP, to be stored in RolePostAssocParameters_t  struct
                      apPeerCapParams     -  pointer to the he Peer cap from the AP, to be stored in RolePostAssocParameters_t  struct

  Return value      : None (void)
******************************************************************************/
//TODO: handle MU EDCA
// MCS Set field structure acording 802.11n SPEC

void setPeerHeCapabilities(uint8_t                        *pHeCapabilitiesPos,
                           uint8_t                        *pHeOperationPos,
                           uint8_t                        *pHeMuEdcaPos,
                           heBssCap_t                   *pHeBssCfg,            // OUT - HE parameters structure
                           hePeerCap_t                  *pPeerCapParams,       // OUT - Peer capabilities structure
                           heMuEdcaAcParams_t           *pMuEdca,
                           uint8_t currBssid[ETH_ALEN])              // OUT - MU EDCA

{

       int currAc;
       uint8_t * pCurrtAcPos;

    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

        // If local supports HE, set peer capabilities
       if ( (FALSE != l2_cfg_isStaHeEnabled()) && (!(l2_GetWirelessProto())) &&
            (NULL != pHeCapabilitiesPos) && (NULL != pHeOperationPos))
       {
           pPeerCapParams->peerHeSupport = 1;

           /* init */
           os_memset(pPeerCapParams->heMacCap,0,sizeof(pPeerCapParams->heMacCap));

           /* get first field */
           os_memcpy(pPeerCapParams->heMacCap, pHeCapabilitiesPos, HE_MAC_CAP_LEN_IN_BYTES);

           pPeerCapParams->nominalPacketPadding = ((heCapabilities_t *)pHeCapabilitiesPos)->hePhyCapabilities.nominalPacketPadding;
#if 0
        GTRACE(GRP_HE_DBG, "GRP_HE_DBG: pPeerCapParams->_w32[0]: 0x%x",(uint32_t)pPeerCapParams->heMacCap._w32[0]);
           GTRACE(GRP_HE_DBG, "GRP_HE_DBG: pPeerCapParams->_w32[1]: 0x%x",pPeerCapParams->heMacCap._w32[1]);


           GTRACE(GRP_HE_DBG, "GRP_HE_DBG: HTC_HE_Support: %d. twtRequesterSupport: %d. twtResponderSupport: %d ",
              (uint32_t)pPeerCapParams->heMacCap.HTC_HE_Support,
              (uint32_t)pPeerCapParams->heMacCap.twtRequesterSupport,
              (uint32_t)pPeerCapParams->heMacCap.twtResponderSupport);

           GTRACE(GRP_HE_DBG, "GRP_HE_DBG: DynamicFragSupport: %d. maxFragMsduAmsduExp: %d. minFragSize: %d ",
              (uint32_t)pPeerCapParams->heMacCap.DynamicFragSupport,
              (uint32_t)pPeerCapParams->heMacCap.maxFragMsduAmsduExp,
              (uint32_t)pPeerCapParams->heMacCap.minFragSize);

#endif

           COPY_WLAN_32BIT(&pHeBssCfg->heOperationCfg,pHeOperationPos);//TODO to check if it is ok
           os_memcpy(&(pHeBssCfg->bssBasicMcsSet), &(pHeOperationPos[HE_OPERATION_MCS_OFFSET]), sizeof(pHeBssCfg->bssBasicMcsSet));
#if  0
           GTRACE(GRP_HE_DBG, "GRP_HE_DBG: heOperationCfg: defaultPeDuration: %d, heOperationCfg: twtRequired: %d,heOperationCfg: txopDurRtsThresh: %d",
                  pHeBssCfg->heOperationCfg.defaultPeDuration,
                  pHeBssCfg->heOperationCfg.twtRequired,
                  pHeBssCfg->heOperationCfg.txopDurRtsThresh);
           GTRACE(GRP_HE_DBG, "GRP_HE_DBG: heOperationCfg: vhtOperInfoPresent: %d,heOperationCfg: coHostedBSS: %d,heOperationCfg: erSUDisable: %d ",
                  pHeBssCfg->heOperationCfg.vhtOperInfoPresent,
                  pHeBssCfg->heOperationCfg.coHostedBSS,
                  pHeBssCfg->heOperationCfg.erSUDisable);
           GTRACE(GRP_HE_DBG, "GRP_HE_DBG: heOperationCfg: gHz6OperInfoPresent: %d . bssColorInfo: 0x%x . bssBasicMcsSet: 0x%x",
                  pHeBssCfg->heOperationCfg.gHz6OperInfoPresent, pHeBssCfg->bssColorInfo._byte, pHeBssCfg->bssBasicMcsSet);
#endif

            //Find the target network in the candidates table
            cmeScanCandidateDesc_t* pCandidateDesc = CME_FindBssidInCandidatesScanTable (currBssid);
            dot11HeMuEdcaAcParams_t* pHeMuEdcaAcParams = NULL;
            if (NULL != pCandidateDesc)
            {
               pHeMuEdcaAcParams = (dot11HeMuEdcaAcParams_t*)get_ie_ext( (const u8 *) pCandidateDesc->mInfoElements, pCandidateDesc->mScanResult.ie_len, WLAN_EID_EXT_HE_MU_EDCA_PARAMS);
            }

           if (NULL != pHeMuEdcaAcParams)
           {
                //extract more data ack bit from qos info
               pHeBssCfg->qosInfo_moreDataAckBit = pHeMuEdcaAcParams->qos_information;

               for (currAc =0; currAc < NUM_ACCESS_CATEGORIES;currAc++ )
               {
                   memcpy(pMuEdca[currAc]._byte, pHeMuEdcaAcParams->heMuEdcaAcParamsIe[currAc]._byte, HE_MU_EDCA_FIELD_BYTES);
                   GTRACE(GRP_HE_DBG, "GRP_HE_DBG: muEdca[%d]._byte:0x%x%x%x",currAc,pMuEdca[currAc]._byte[0],pMuEdca[currAc]._byte[1],pMuEdca[currAc]._byte[2]);

               }
           }
       }
       else
       {
           pPeerCapParams->heMacCap[0] = 0;
           pPeerCapParams->heMacCap[1] = 0;
       }

}
#endif


// ------------------------------------------------------------------------
int32_t setWmeSiteParams(dot11_WME_PARAM_t *apWmeParamIE, RolePostAssocParameters_t *apParams)
{
    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    if (0 == apWmeParamIE->hdr.eleLen)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: empty WMM params");
        return -1;
    }

    updateACParams(&(apWmeParamIE->WME_ACParameteres), apParams);
    updateUAPSDConfiguration(apWmeParamIE, apParams);

    return 0;
}

// When assoc response is received, in MCP it is handled in mlme_assocRecv
// ------------------------------------------------------------------------


void ti_drv_setApInfo(ti_driver_ifData_t    *apDrv,
                       struct ieee802_11_elems *apParsedElems,
                       struct ieee80211_mgmt   *apMngPack,
                       uint32_t                  aPackLen)
{
    uint16_t aid;
    uint16_t capabilities = 0;
    Bool32 shortBarkerPreamble = FALSE;
    Bool_e shortBPreambleSupported;
    uint32_t  minLen = WLAN_HDR_LEN + sizeof(apMngPack->u.assoc_resp);

    dot11_WME_PARAM_t wmeParamIE;
    dot11_WSC_t       wscIE;

    int32_t rc;

    // Post association configuration param
    uint32_t   basicRatesBM, supportedRatesBM;
    uint32_t   localSupportedRates;
    uint8_t *pIes = apMngPack->u.assoc_resp.variable;
    uint8_t *muEcdaPos;
    heBssCap_t heBssCap = {0};

    apDrv->link = 0;


    HOOK(HOOK_DRV_TI_STA_SPECIFIC);

    // Note:
    // Associated indication is set on driver DB before the association event is
    // sent to supplicant. This complies with mac802.11 mlme.c behavior.
    // There is no appropriate API to do it later in supplicant event handler.
    apDrv->associated = TRUE;
    IRQ_UtilCopyMacAddress(apMngPack->sa, apDrv->currBssid);

    os_memset(&apDrv->assocParams, 0, sizeof (RolePostAssocParameters_t));
    os_memset(&apDrv->apHeMuEdcaAcParams, 0, sizeof(apDrv->apHeMuEdcaAcParams));
    os_memset(&apDrv->apAcParameters, 0, sizeof(dot11_ACParameters_t));
    os_memset(&apDrv->peerCap, 0, sizeof(PeerCap_t));
    os_memset(&apDrv->bssCap, 0, sizeof(BssCap_t));
    apDrv->link = udataNet_GetTxMgmtLink(TIWDRV_NETIF_ID_STA, apDrv->currBssid);

    if(INVALID_LINK == apDrv->link)
    {
        GTRACE(1,"\n\r ti_drv_setApInfo: ERROR unsupported link id %d ", apDrv->link);
        return;
    }


    // Configure B preamble - based on peer capabilities & ERP info if exists
    readErpFlag(apParsedElems, &apDrv->useProtection, &shortBarkerPreamble);
    shortBPreambleSupported = FALSE;
    if (FALSE != cfgIsStaShortPreambleEnabled())
    {
        capabilities = le_to_host16(apMngPack->u.assoc_resp.capab_info);
        if ( ((capabilities >> CAP_PREAMBLE_SHIFT) & CAP_PREAMBLE_MASK) &&
             (TRUE == shortBarkerPreamble) )
        {
            shortBPreambleSupported = TRUE;
        }
    }


    GTRACE(GRP_DRIVER_CC33, "Setting short preamble support to %d; peer capabilities 0x%x, peer barker preamble %d CTS protection %d",
                             shortBPreambleSupported, capabilities, shortBarkerPreamble, apDrv->useProtection);

    // Configure QOS
    apDrv->wmeEnabled = cfgIsStaWmeEnabled();

    if (TRUE == apDrv->wmeEnabled)
    {
        rc = -1;

        if (apParsedElems->wmm_len)
        {
            // Parse the received packet
            rc = getWmmConfig(apParsedElems, &wmeParamIE, &wscIE);

            // if WMM wasn't successfully detected, don't update
            if (0 == rc)
            {
                os_memcpy(&(apDrv->apAcParameters), &(wmeParamIE.WME_ACParameteres), sizeof(dot11_ACParameters_t));
                rc = setWmeSiteParams(&wmeParamIE, &apDrv->assocParams);
            }
        }

        if (rc < 0)
        {
            apDrv->wmeEnabled = FALSE;
            GTRACE(GRP_DRIVER_CC33, "Warning: failed to set AC QOS_WME parameters!!! disabling WME");
        }
    }


    // Configure Aid
    aid = le_to_host16(apMngPack->u.assoc_resp.aid);
    aid &= ~(BIT(15) | BIT(14));

    if (0 == aid || IEEE80211_MAX_AID < aid)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: invalid AID %d", aid);
        // TODO - how should we handle this?
        // MCP - no sanity test, NLCP aid is set to 0, legacy FW asserts on aid=0.
    }
    else    // aid OK
    {
       GTRACE(GRP_DRIVER_CC33, "Setting AID to %d origin 0x%x ", aid, apMngPack->u.assoc_resp.aid);
    }

    wlanLinks_SetLinkAid(aid, apDrv->link);

    setPeerHtCapabilities((uint8_t *)apParsedElems->ht_capabilities,
                          (uint8_t *)apParsedElems->ht_operation,
                          &apDrv->bssCap.htCfgInBss, &apDrv->peerCap.htPeerCap);

    os_memcpy(&heBssCap, &apDrv->bssCap.heCfgInBss, sizeof(heBssCap_t));
#ifndef DISABLE_WIFI6
    setPeerHeCapabilities((uint8_t *)apParsedElems->he_capabilities,
                          (uint8_t *)apParsedElems->he_operation, muEcdaPos,
                          &heBssCap, &apDrv->peerCap.hePeerCap,
                          apDrv->assocParams.muEdca, apDrv->currBssid);
#endif
}

//after associate and connect
void ti_drv_setApAssocInfo(ti_driver_ifData_t    *apDrv)
{
    uint32_t   basicRatesBM, supportedRatesBM;
    uint32_t   supportedRates;

    supportedRates = apDrv->apRate.remotePeerSupportedRatesBM;

    //calls cc3xxx_trnspt_cmd_if_config_assoc_peer function
    apDrv->ops->assoc_peer(apDrv, &apDrv->peerCap, &apDrv->bssCap,  supportedRates, apDrv->link, apDrv->wmeEnabled, apDrv->useProtection);

    uint8_t ac = 0;
    for(ac = 0; ac < NUM_ACCESS_CATEGORIES; ac++)
    {
#ifndef DISABLE_WIFI6
        os_memcpy(apDrv->apHeMuEdcaAcParams[ac]._byte, apDrv->assocParams.muEdca[ac]._byte,HE_MU_EDCA_FIELD_BYTES);
        apDrv->ops->tx_param(apDrv, &apDrv->assocParams.acParameters[ac], apDrv->assocParams.psScheme, TRUE, (uint8_t *)&apDrv->assocParams.muEdca[ac], ac);
#else
        apDrv->ops->tx_param(apDrv, &apDrv->assocParams.acParameters[ac], apDrv->assocParams.psScheme, FALSE, NULL, ac);
#endif
    }

}


// ============================================================================
//      AP Deny List
// ============================================================================

/******************************************************************************
  Function          : DenyList_initList

  Description       : Function to zero list structure when role is enabled

  Input parameters  : Pointer to the DenyList_LinkedList_t structure

  Output parameters : None (void)
  
  Return value      : 0 if successful, -1 if list is NULL

  Coder             : Dana
******************************************************************************/
int DenyList_initList(DenyList_LinkedList_t* list) 
{
    if (!list) 
    {
        return -1;
    }
        list->head = NULL;
        list->size = 0;
        GTRACE(GRP_DRIVER_CC33, "DenyList_initList");

        return 0;
}

/******************************************************************************
  Function          : DenyList_timerExpiry

  Description       : Callback function that is called when the timer expires.
                      It verifies and removes expired elements from the deny list.
                      The assumption is that this function is called from the same 
                      context where the timer was registered. This is the context 
                      of the CME and supplicant.

  Input parameters  : list - pointer to the DenyList_LinkedList_t structure

  Output parameters : None (void)
  
  Return value      : None (void)

  Coder             : Dana
******************************************************************************/
static void DenyList_timerExpiry(void *list, void *timeout_ctx) 
{
    DenyList_LinkedList_t* plist = list;

    GTRACE(GRP_DRIVER_CC33, "DenyList_timerExpiry: Timer expired, verifying and removing expired elements");

    DenyList_verifyAndRemoveExpiredElements(plist);

    // If the list is not empty, re-register the timer
    if (plist->size > 0) 
    {
       if (eloop_is_timeout_registered(DenyList_timerExpiry, list, NULL)) 
        {   
            eloop_cancel_timeout(DenyList_timerExpiry, list, NULL);
        }
        eloop_register_timeout(DENY_LIST_TIMER_TIMEOUT_SECONDS,         // seconds
                               0,                                       // useconds
                               DenyList_timerExpiry,                    // Timeout callback
                               list,                                    // eloop data
                               NULL);                                   // pointer to packet	
    } 
    else 
    {
        GTRACE(GRP_DRIVER_CC33, "DenyList_timerExpiry: List is empty, timer will not be re-registered");
    }
}

/******************************************************************************
  Function          : DenyList_clearList

  Description       : Function to clear the entire list and remove the timer 
                      if it exists. This function will free all the nodes in the list.

  Input parameters  : Pointer to the DenyList_LinkedList_t structure

  Output parameters : None (void)
  
  Return value      : None

  Coder             : Dana
******************************************************************************/
void DenyList_clearList(DenyList_LinkedList_t* list) 
{
    if (!list || !DENY_LIST_EN)
    {
        return;
    } 
    GTRACE(GRP_DRIVER_CC33, "DenyList_clearList: Clearing list");

    // Remove timer if exists
    if (eloop_is_timeout_registered(DenyList_timerExpiry, (void *) list, NULL))
    {
        eloop_cancel_timeout(DenyList_timerExpiry, (void *) list, NULL);
    }

    DenyList_Node_t* current = list->head;
    while (current) 
    {
        DenyList_Node_t* temp = current;
        current = current->next;
        os_free(temp);
    }

    list->head = NULL;
    list->size = 0;
}

/******************************************************************************
  Function          : DenyList_elementExists

  Description       : Helper function to check if a MAC address exists in the list

  Input parameters  : list - pointer to the DenyList_LinkedList_t structure
                      macAddr - MAC Address to search for in the list

  Output parameters : node - pointer to the DenyList_Node_t structure where the found node will be stored
  
  Return value      : 1 if MAC Address exists in the list, 0 if it does not exist

  Coder             : Dana
******************************************************************************/
int DenyList_elementExists(DenyList_LinkedList_t* list, uint8_t macAddr[6], DenyList_Node_t** node) 
{
    if (!list || !list->head)
    {
        return 0;
    } 

    DenyList_Node_t* current = list->head;
    uint32_t nowTime = osi_GetTimeMS(); // Get the current time
    DenyList_Node_t* prev = NULL;

    while (current) 
    {
        // While we traverse the list, we will verify expiry before comparing the MAC address
        if ((current->expiryTime - nowTime) > UINT32_MAX/2)
        {
            // Expiry time has passed, remove the element
            if (prev) 
            {
                prev->next = current->next;
            } else 
            {
                list->head = current->next;
            }
            DenyList_Node_t* temp = current;
            current = current->next;
            
            GTRACE(GRP_DRIVER_CC33, "DenyList_elementExists: Mac address %02x:%02x:%02x:%02x:%02x:%02x expiry %d removed from list",  
            temp->macAddr[0], temp->macAddr[1], temp->macAddr[2], temp->macAddr[3], temp->macAddr[4], temp->macAddr[5], temp->expiryTime);
            CME_PRINT_REPORT("\n\rDenyList_elementExists: Mac address %02x:%02x:%02x:%02x:%02x:%02x expiry %d removed from list\n\r",  
            temp->macAddr[0], temp->macAddr[1], temp->macAddr[2], temp->macAddr[3], temp->macAddr[4], temp->macAddr[5], temp->expiryTime);

            os_free(temp);
            list->size--;
        } 
        else
        {
            // Now we actually compare the MAC address
            if (memcmp(current->macAddr, macAddr, 6) == 0)
            {
                GTRACE(GRP_DRIVER_CC33, "DenyList_elementExists: Mac address already exists");
                if (node != NULL)
                {
                    *node = current;
                }
                return 1; // MAC address found
            }
            // Move to the next node
            prev = current;
            current = current->next;
        }
    }
    return 0; // MAC address not found
}

/******************************************************************************
  Function          : DenyList_findAndRemoveSoonestExpiry

  Description       : Function to find and remove the node with the soonest expiry time in the list.
                      This function is useful for managing the deny list and ensuring that
                      we can efficiently find the node that should be removed next when the 
                      list is full. 

  Input parameters  : list - pointer to the DenyList_LinkedList_t structure

  Output parameters : None (void)
  
  Return value      : None (void)

  Coder             : Dana
******************************************************************************/
void DenyList_findAndRemoveSoonestExpiry(DenyList_LinkedList_t* list) 
{
    if (!list || !list->head) 
    {
        return; // List is empty or invalid
    }

    DenyList_Node_t* current = list->head;
    DenyList_Node_t* soonestNode = current;
    DenyList_Node_t* prev = NULL;
    DenyList_Node_t* prevSoonest = NULL;
    uint32_t nowTime = osi_GetTimeMS();

    // Traverse the list to find the soonest expiry node
    while (current) 
    {
        if ((nowTime - current->expiryTime) < (nowTime - soonestNode->expiryTime)) 
        {
            soonestNode = current; // Update the node with the soonest expiry time
            prevSoonest = prev; // Track the previous node of the soonest node
        }
        prev = current;
        current = current->next;
    }

    // Remove the soonest expiry node from the list
    if (soonestNode == list->head) 
    {
        list->head = soonestNode->next; // Update head if the soonest node is the first node
    } else if (prevSoonest) 
    {
        prevSoonest->next = soonestNode->next; // Bypass the soonest node
    }

    list->size--; // Decrement the size of the list

    GTRACE(GRP_DRIVER_CC33, "DenyList_findAndRemoveSoonestExpiry:  MAC address=%02x:%02x:%02x:%02x:%02x:%02x expiry Time %d",
    soonestNode->macAddr[0], soonestNode->macAddr[1], soonestNode->macAddr[2], soonestNode->macAddr[3], soonestNode->macAddr[4], soonestNode->macAddr[5], soonestNode->expiryTime);
    CME_PRINT_REPORT("\n\rDenyList_findAndRemoveSoonestExpiry:  MAC address=%02x:%02x:%02x:%02x:%02x:%02x expiry Time %d\n\r", 
    soonestNode->macAddr[0], soonestNode->macAddr[1], soonestNode->macAddr[2], soonestNode->macAddr[3], soonestNode->macAddr[4], soonestNode->macAddr[5], soonestNode->expiryTime);

    // Free the memory of the removed node
    os_free(soonestNode);
}

/******************************************************************************
  Function          : DenyList_addElement

  Description       : Function to add an element to the list

  Input parameters  : list - pointer to the DenyList_LinkedList_t structure
                      macAddr - NAC Address to add to the list
                      expiryTime - expiry time in MS of the new list Entry

  Output parameters : None (void)
  
  Return value      : 0 if the MAC address was successfully added,
                      -1 if the list is empty or invalid,
                      -2 if the MAC address already exists in the list (expiry time updated),
                      -3 if memory allocation failed

  Coder             : Dana
******************************************************************************/
int DenyList_addElement(DenyList_LinkedList_t* list, uint8_t macAddr[6], uint32_t expiryTime) 
{
     DenyList_Node_t* node = NULL; 

    if (list == NULL) 
    {
        return -1;
    }

    // Begin by clearing old entries from the list
    DenyList_verifyAndRemoveExpiredElements(list);

    if (DenyList_elementExists(list, macAddr, &node)) 
    {
        node->expiryTime = expiryTime; // Update the expiry time of the existing node

        GTRACE(GRP_DRIVER_CC33, "DenyList_addElement:  updated node MAC address=%02x:%02x:%02x:%02x:%02x:%02x expiry Time %d",
        (node)->macAddr[0], (node)->macAddr[1], (node)->macAddr[2], (node)->macAddr[3], (node)->macAddr[4], (node)->macAddr[5], (node)->expiryTime);

        return -2; // MAC address already exists in the list, update the expiry time
    }

    if (list->size >= DENY_LIST_MAX_ENTRIES) 
    {
        // List is full - Need to remove the entry that is closest to its expiry
        GTRACE(GRP_DRIVER_CC33, "DenyList_addElement: List full - remove soonest expiry");
        DenyList_findAndRemoveSoonestExpiry(list);
    }

    // Create a new node
    DenyList_Node_t* newNode = (DenyList_Node_t*)os_malloc(sizeof(DenyList_Node_t));
    if (newNode == NULL) 
    {
        return -3; // Memory allocation failed
    }

    memcpy(newNode->macAddr, macAddr, 6);
    newNode->expiryTime = expiryTime;
    newNode->next = list->head;

    // Add the new node to the head of the list
    list->head = newNode;
    list->size++;
    GTRACE(GRP_DRIVER_CC33, "DenyList_addElement:  added MAC address=%02x:%02x:%02x:%02x:%02x:%02x expiry Time %d list size %d", 
        macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5], expiryTime, list->size);
    CME_PRINT_REPORT("\n\rDenyList_addElement:  added MAC address=%02x:%02x:%02x:%02x:%02x:%02x expiry Time %d list size %d\n\r", 
        macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5], expiryTime, list->size);

    // ONLY if this is the first element in the list, create a timer for clearing the list
    if (list->size == 1)
    {
        eloop_register_timeout(DENY_LIST_TIMER_TIMEOUT_SECONDS,         // seconds
                               0,                                       // useconds
                               DenyList_timerExpiry,                    // Timeout callback
                               list,                                   // eloop data
                               NULL);                                   // pointer to packet
    }

    return 0; // Success
}

/******************************************************************************
  Function          : DenyList_removeElement

  Description       : Function to remove an element from the list

  Input parameters  : list - pointer to the DenyList_LinkedList_t structure
                      macAddr - MAC Address to remove from the list

  Output parameters : None (void)
  
  Return value      : -1 if the list is empty or invalid,
                      -2 if the MAC address was not found in the list,
                      0 if the MAC address was successfully removed

  Coder             : Dana
******************************************************************************/
int DenyList_removeElement(DenyList_LinkedList_t* list, uint8_t macAddr[6]) 
{
    if (!list || !list->head) 
    {
        return -1; // List is empty or invalid
    }

    DenyList_Node_t* current = list->head;
    DenyList_Node_t* prev = NULL;

    while (current) 
    {
        if (memcmp(current->macAddr, macAddr, 6) == 0) 
        {
            // MAC address found, remove the node
            if (prev) 
            {
                prev->next = current->next;
            } else 
            {
                list->head = current->next;
            }
            GTRACE(GRP_DRIVER_CC33, "DenyList_removeElement: Mac address %02x:%02x:%02x:%02x:%02x:%02x removed from list", 
            macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);

            os_free(current);
            list->size--;
            return 0; // Success
        }
        prev = current;
        current = current->next;
    }
    return -2; // MAC address not found
}

/******************************************************************************
  Function          : DenyList_verifyAndRemoveExpiredElements

  Description       : Function that iterates through the linked list, checks the expiry time of each
                      element against the current time, and removes expired elements.
                      This function should be called when trying to connect.

  Input parameters  : list - pointer to the DenyList_LinkedList_t structure

  Output parameters : None (void)
  
  Return value      : None (void)

  Coder             : Dana
******************************************************************************/
void DenyList_verifyAndRemoveExpiredElements(DenyList_LinkedList_t* list) 
{
    if (!list || !list->head) 
    {
        return; // List is empty or invalid
    }

    GTRACE(GRP_DRIVER_CC33, "DenyList_verifyAndRemoveExpiredElements");

    uint32_t nowTime = osi_GetTimeMS(); // Get the current time
    DenyList_Node_t* current = list->head;
    DenyList_Node_t* prev = NULL;

    while (current) 
    {
        if ((current->expiryTime - nowTime) > UINT32_MAX/2)
        {
            // Expiry time has passed, remove the element
            if (prev) 
            {
                prev->next = current->next;
            } else 
            {
                list->head = current->next;
            }
            DenyList_Node_t* temp = current;
            current = current->next;

            GTRACE(GRP_DRIVER_CC33, "DenyList_verifyAndRemoveExpiredElements: Mac address %02x:%02x:%02x:%02x:%02x:%02x expiry %d removed from list",  
            temp->macAddr[0], temp->macAddr[1], temp->macAddr[2], temp->macAddr[3], temp->macAddr[4], temp->macAddr[5], temp->expiryTime);
            CME_PRINT_REPORT("\n\rDenyList_verifyAndRemoveExpiredElements: Mac address %02x:%02x:%02x:%02x:%02x:%02x expiry %d removed from list\n\r",  
            temp->macAddr[0], temp->macAddr[1], temp->macAddr[2], temp->macAddr[3], temp->macAddr[4], temp->macAddr[5], temp->expiryTime);

            os_free(temp);
            list->size--;

            if (list->size == 0)
            {
                // If the list is empty, cancel the timer
                if (eloop_is_timeout_registered(DenyList_timerExpiry, (void *) list, NULL)) 
                {
                    eloop_cancel_timeout(DenyList_timerExpiry, (void *) list, NULL);
                }
            }

        } else 
        {
            // Move to the next node
            prev = current;
            current = current->next;
        }
    }
}
