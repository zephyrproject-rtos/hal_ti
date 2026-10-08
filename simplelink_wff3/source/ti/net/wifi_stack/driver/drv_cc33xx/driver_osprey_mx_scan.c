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
/*
 * driver_osprey_mx_scan.c
 *
 *  Created on: Jun 24, 2020
 *      Author: user
 */
#include "tw_driver.h"
#include "udata_api.h"
#include "osi_kernel.h"

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
#include "scan.h"
#include "bss.h"
#include "cme_supplicant_api.h"
#include "cme_dispatcher_api.h"
#include "cme_internal_api.h"
#include "cme_fw_api.h"
#include "cme_defs.h"
#include "802_11defs.h"


#include "drv_ti_internal.h"

#include "mpdu.h"
#include "80211_utils.h"

#include "drv_ext_app.h"
#include "driver_osprey_mx_scan.h"
#include "regulatory_domain.h"

#include "cme_internal_api.h"
#include "mlme_parser.h"
#include "scan_result_table.h"
#include "ie_parser_util.h"
#include "lower_mac_if.h"
#include "public_share.h"
#include "rx.h"
#include "rx_defs.h"
#include "l2_cfg.h"
#include "errors.h"

#define CC33XX_MAX_TXPWR (21)

// ============================================================================
//      Modules extern globals
// ============================================================================
extern  cmeScanSharedInfo_t*    scanResultTable_GetCmeScanDbPointer();

extern  uint32_t  scan_result_calc_weighted_score(TScanFrameInfo* scanInfo,
                                                EScanRequestType  eScanReqType);

extern int cc3xxx_trnspt_cmd_if_send_stop_scan (uint8_t roleID,
                              EScanRequestType scanRequestType,
                              Bool_e isET);

extern  void scanCandidateTable_HandleResult(TScanFrameInfo*     pFrame,
                                             uint32_t              score,
                                             int8_t                profileId);

extern  void scanDigestTable_HandleResult(TScanFrameInfo*        pFrame,
                                          uint32_t                 score);

extern  void scanDigestTable_HandleExtendedResult(TScanFrameInfo*      pFrame,
                                                  uint32_t             score);

extern  int32_t is_wlan_periodic_scan_in_progress();


// ============================================================================
//      Local services APIs
// ============================================================================

/******************************************************************************

    FUNCTION:		mx_driver_scan_check_early_termination

    PROTOTYPE:		driver_osprey_mx_scan

    DESCRIPTION:    Check if we can do early termination to scan

    CALLER:         mx_driver_scan_results_process

    PARAMETERS:     pCmeScanDB - pointer to Scan Data block
                    res_rssi - result frame RSSI
                    score  - result calculated score

    RETURNS:        TRUE - needed ET
                    FALSE - no needed ET

******************************************************************************/
Bool_e mx_driver_scan_check_early_termination(cmeScanSharedInfo_t*    pCmeScanDB,
                                              int32_t                   res_rssi,
                                              uint32_t                  score)
{
    HOOK(HOOK_IN_DRIVER_OSPREY_MX_SCAN);

    Bool_e early_terminate = FALSE;
    if(FALSE == pCmeScanDB->ETexceeded)
    {
        if ( /* both thresholds are enabled */
                (pCmeScanDB->mRssiEarlyTermThreshold  != 0)
             && (pCmeScanDB->mScoreEarlyTermThreshold != 0))
        {
            if (    ((int32_t)(pCmeScanDB->mRssiEarlyTermThreshold)  <= (int32_t)res_rssi)
                    && (pCmeScanDB->mScoreEarlyTermThreshold <= score))
            {
                early_terminate = TRUE;
            }
        }
        else if (    /* only RSSI threshold is enabled */
                   (pCmeScanDB->mRssiEarlyTermThreshold != 0)
                && ((int32_t)(pCmeScanDB->mRssiEarlyTermThreshold) <= (int32_t)res_rssi))
        {
            early_terminate = TRUE;
        }
        else if (    /* only SCORE threshold is enabled */
                   (pCmeScanDB->mScoreEarlyTermThreshold != 0)
                && (pCmeScanDB->mScoreEarlyTermThreshold <= score)
              )
        {
          early_terminate = TRUE;
        }
    }
    else
    {
        early_terminate = FALSE;
        GTRACE(GRP_DRIVER_MX," Early termination already exceeded");
    }

    HOOK(HOOK_IN_DRIVER_OSPREY_MX_SCAN);

    return early_terminate;

}

/******************************************************************************

    FUNCTION:		mx_driver_ssid_match

    PROTOTYPE:		driver_osprey_mx_scan

    DESCRIPTION:    Check SSID + BSSID and security type

    CALLER:         mx_driver_scan_results_process

    PARAMETERS:     apSsidIe - pointer to SSID IE in frame
                    apBssid  - pointer to the BSSID in the frame
                    securityType - security type
                    numOfSSID - number of SSID in the list
                    pList - List of the SSID
                    OUT profileId - matching profile ID

    RETURNS:        TRUE  - found match
                    FALSE - SSID and security type unmatched

******************************************************************************/
int8_t mx_driver_ssid_match(dot11_SSID_t*      apSsidIe,
                          uint8_t*             apBssid,
                          uint8_t              securityType,
                          uint8_t              numOfSSID,
                          cmeScanProfiles_t* pList,
                          int8_t*              profileId)
{
    HOOK(HOOK_IN_DRIVER_OSPREY_MX_SCAN);

    int     ssidIndex;
    int     foundMatch = FALSE;
    uint8_t   macZero[6] = {0,0,0,0,0,0};

    //go over ssid list and check if input ssid is found inside the list
    for (ssidIndex = 0; ssidIndex < numOfSSID; ssidIndex++)
    {
        Bool_e isWep; //Match in WEP security
        GTRACE(GRP_DRIVER_MX," filter scan results: index %d, rcv SSID len %d, list ssid len %d, security type ENUM(CMESecType_e, %d)",
                                ssidIndex,
                                apSsidIe->hdr.eleLen,
                                (uint32_t)pList[ssidIndex].ssid.mSsidLen,
                                (CMESecType_e) pList[ssidIndex].secType);

        //In case of wep - since can not know at this stage if the remote AP uses open or shared, we pass in either case.
        isWep = (((securityType == CME_SEC_TYPE_WEP) || (securityType == CME_SEC_TYPE_WEP_SHARED)) &&
                ((pList[ssidIndex].secType == CME_SEC_TYPE_WEP) || (pList[ssidIndex].secType == CME_SEC_TYPE_WEP_SHARED))); //We have a match in WEP

        // compare security type
        // Should be enhanced with key management compare as in wpa_supplicant_ssid_bss_match

        //Filter the result in case the security does not match and we also don't have a match in wep type.
        //In any other case, we have a match and we don't filter the result, we go on and check the ssid or bssid.
        if ((securityType != pList[ssidIndex].secType) && (!isWep))
        {
            GTRACE(GRP_DRIVER_MX," filter scan results: AP security type: ENUM(CMESecType_e, %d), profile security type: ENUM(CMESecType_e, %d), dropping this one",
                                    (CMESecType_e) securityType, (CMESecType_e) pList[ssidIndex].secType);
            continue;
        }

        //if ssid length is the same
        if (apSsidIe->hdr.eleLen == pList[ssidIndex].ssid.mSsidLen)
        {
            //if SSID is the same AND BSSID is the same or should be ignored
            if (    (memcmp(apSsidIe->serviceSetId, &(pList[ssidIndex].mSSID[0]), apSsidIe->hdr.eleLen) == 0)
                 && (    (IRQ_UtilCompareMacAddress (apBssid, pList[ssidIndex].mBssid) ) //MAC is equal
                      || (IRQ_UtilCompareMacAddress (macZero,pList[ssidIndex].mBssid) ) //MAC is not relevant
                    )
               )
            {
                foundMatch = TRUE;
                *profileId = pList[ssidIndex].mProfileId;
                break;
            }
        }
        // For WPS / connect to BSSID
        else if (    (0 == pList[ssidIndex].ssid.mSsidLen)
                  && (    (IRQ_UtilCompareMacAddress (apBssid, pList[ssidIndex].mBssid) ) //MAC is equal
                       || (IRQ_UtilCompareMacAddress (macZero,pList[ssidIndex].mBssid) ) //MAC is not relevant
                     )
                )
        {
            foundMatch = TRUE;
            *profileId = pList[ssidIndex].mProfileId;
            break;
        }
    }

    HOOK(HOOK_IN_DRIVER_OSPREY_MX_SCAN);

    return foundMatch;
}

/******************************************************************************

    mx_driver_FilterWpsP2p

    DESCRIPTION:    check if need to filter received results due to wps and / or p2p
                    IE's. if wps and / or p2p filter is set, pass only frames
                    who contain these IE's

    CALLER:         ScanModule_processRxFrame()

    PARAMETERS:     aRoleId - role index
                    pScanCB - pointer to scan module control block
                    desc - pointer to frame descriptor

    RETURNS:        TRUE - if frame should be dropped.

******************************************************************************/
Bool_e  mx_driver_FilterWpsP2p(uint32_t aRoleId, uint8_t* payloadStart, uint16_t payloadLength)
{
    Bool_e  findWps = FALSE, findP2p = FALSE;
    Bool_e  toDrop = FALSE;
    uint8*  pDot11Wps;
    uint8*  pDot11P2p;
    uint8   wpsOui[] = DOT11_WPS_OUI; //OUI_TYPE for WPS is 0x00, 0x50, 0xf2, 4
    uint8   p2pOui[] = DOT11_P2P_OUI; //OUI_TYPE for P2P is 0x50, 0x6F, 0x9A, 0x09
    RoleType_e roleType = drv_getRoleTypeFromRoleId(gpSupplicantGlobals, aRoleId);

    if (CME_IsOngoingWPSAdHocConnection())
    {
        //look for WPS IE in the frame
        findWps = IEParser_FindVendorSpecificIe_forBeaconProbeRsp(payloadStart,        /* payload start */
                                                payloadLength,     /* payload length */
                                                (uint8 *) &wpsOui,            /* OUI to search for */
                                                (uint8**)&pDot11Wps);         /* returned pointer to the info element */

        if (findWps)
        {
            GTRACE(GRP_SCAN_MODULE, "scan: WPS IE match");
        }
    }

    if (ROLE_IS_TYPE_DEVICE(roleType))
    {
        //look for P2P IE in the frame
        findP2p = IEParser_FindVendorSpecificIe_forBeaconProbeRsp(payloadStart,        /* payload start */
                                                payloadLength,     /* payload length */
                                                (uint8 *) &p2pOui,            /* OUI to search for */
                                                (uint8**)&pDot11P2p);         /* returned pointer to the info element */

        if (findP2p)
        {
            GTRACE(GRP_SCAN_MODULE, "scan: P2P IE match");
        }
    }

    //if needed to pass wps and p2p
    if (    CME_IsOngoingWPSAdHocConnection()
         && ROLE_IS_TYPE_DEVICE(roleType)
       )
    {
        //but didnt found non of them --> drop frame
        if (!findWps && !findP2p)
        {
            GTRACE(GRP_SCAN_MODULE, "scan RX drop: WPS IE + P2P IE not found in frame");
            toDrop = TRUE;
        }
    }
    else    //if needed to pass wps
    if (CME_IsOngoingWPSAdHocConnection())
    {
        //but didnt found wps --> drop frame
        if (!findWps)
        {
            GTRACE(GRP_SCAN_MODULE, "scan RX drop: WPS IE not found in frame");
            toDrop = TRUE;
        }
    }
    else    //if needed to pass p2p
    if (ROLE_IS_TYPE_DEVICE(roleType))
    {
        //but didnt found p2p --> drop frame
        if (!findP2p)
        {
            GTRACE(GRP_SCAN_MODULE, "scan RX drop: P2P IE not found in frame");
            toDrop = TRUE;
        }
    }

    return toDrop;
}

void rsn_findSecurityIEs(uint8_t *payload, uint16_t payloadLen, dot11_RSN_t **pDotRsn, dot11_RSN_t **pDotWpa, dot11_RSN_t **pDotRsnOverride, dot11_RSN_t **pDotRsnOverride2)
{
    const uint8_t wpaOui[] = DOT11_WPA_OUI; //OUI_TYPE for WPA is 0x00, 0x50, 0xf2, 1
    const uint8_t rsnOverrideOui[] = DOT11_RSN_OVERRIDE_OUI;
    const uint8_t rsnOverride2Oui[] = DOT11_RSN_OVERRIDE_2_OUI;
    *pDotRsn = NULL;
    *pDotWpa = NULL;
    *pDotRsnOverride = NULL;
    *pDotRsnOverride2 = NULL;

    GTRACE(GRP_DRIVER_CC33, "RSN: Check Security type, IE payload len: %d", payloadLen);

    //Search for RSN IE
        IEParser_FindIe( payload,        /* payload start */
                         payloadLen,     /* payload length */
                         RSN_IE_ID,           /* look for RSN IE */
                         (uint8_t**)pDotRsn);  /* returned pointer to the info element */

        // Search for WPA IE
        IEParser_FindVendorSpecificIe(payload,        /* payload start */
                                      payloadLen,     /* payload length */
                                      (uint8_t *)&wpaOui, /* OUI to search for*/
                                      (uint8_t**)pDotWpa);    /* returned pointer to the info element */

        // Search for RSN OVERRIDE IE
        IEParser_FindVendorSpecificIe(payload,        /* payload start */
                                      payloadLen,     /* payload length */
                                      (uint8_t *)&rsnOverrideOui, /* OUI to search for*/
                                      (uint8_t**)pDotRsnOverride);    /* returned pointer to the info element */

        // Search for RSN OVERRIDE 2 IE
        IEParser_FindVendorSpecificIe(payload,        /* payload start */
                                      payloadLen,     /* payload length */
                                      (uint8_t *)&rsnOverride2Oui, /* OUI to search for*/
                                      (uint8_t**)pDotRsnOverride2);    /* returned pointer to the info element */
}

static int getSecurities(scanIEParsingParams_t *params, uint8_t *securityType, uint8_t *securityTypeOverride, uint8_t *securityTypeOverride2)
{
    dot11_RSN_t *pDotRsn = NULL;
    dot11_RSN_t *pDotWpa = NULL;
    dot11_RSN_t *pDotRsnOverride = NULL;
    dot11_RSN_t *pDotRsnOverride2 = NULL;

    if(params->rsnIeLen != 0)
    {
        pDotRsn = &params->rsnIe;
    }

    if(params->wpaIeLen != 0)
    {
        pDotWpa = &params->wpaIe;
    }

    if(params->rsnOverrideIeLen != 0)
    {
        pDotRsnOverride = &params->rsnOverrideIe;
    }

    if(params->rsnOverride2IeLen != 0)
    {
        pDotRsnOverride2 = &params->rsnOverride2Ie;
    }

    return rsn_getSecurityTypes(params->capabilities, pDotRsn, pDotWpa, pDotRsnOverride, pDotRsnOverride2, securityType, securityTypeOverride, securityTypeOverride2);
}


/******************************************************************************

    FUNCTION:		mx_driver_scan_results_process

    PROTOTYPE:		driver_osprey_mx_scan

    DESCRIPTION:    Process the scan result frame
                    For site_survey - update the scan result table
                    For one_shot/periodic - verify SSID, Security match
                    if result is good, we can do early termination

    CALLER:         cc3xxx_trnspt_cmd_if_check_scan_tagged_frame

    PARAMETERS:     frame - pointer to RX descriptor
                    scanType - scan type

    RETURNS:         OK - updated scan table
                    -1

******************************************************************************/
int32_t mx_driver_scan_results_process(uint32_t aRoleId, RxIfDescriptor_t *desc, EScanRequestType scanType)
{
    HOOK(HOOK_IN_DRIVER_OSPREY_MX_SCAN);

    cmeScanSharedInfo_t*    pCmeScanDB = scanResultTable_GetCmeScanDbPointer();
    cmeScanProfiles_t*      pList;
    uint8_t                 numOfSSID;
    int8_t                  profileId = -1;
    int8_t                  res_rssi = EXTRACT_RSSI(desc->rx_level);
    uint32_t                score;
    Bool_e                  status =-1;
    Bool32                  foundMatch = FALSE;
    dot11_SSID_t*           pDot11Ssid;
    MGMT_Header_t          *pMacHdr = (MGMT_Header_t *)(uint8_t*)RX_BUF_DATA(desc);
    uint8_t*                pFrame;
    uint16_t                pLen;
    Bool32                  continue2check;
    uint8_t                 securityType = 0xff, securityTypeOverride = 0xff, securityTypeOverride2 = 0xff;
    BeaconFrame_t*          pBeaconFrame;
    struct wpa_supplicant   *wpa_s;
    ti_driver_ifData_t      *pDrv = NULL;
    Bool_e                  mbssid_support;


    int32_t    frameLengthWithoutDescr;


    frameLengthWithoutDescr = desc->length - sizeof(RxIfDescriptor_t);

    wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, aRoleId);
    pDrv = (ti_driver_ifData_t*)wpa_s->drv_priv;


    switch(scanType)
    {
        case SCAN_REQUEST_ONE_SHOT:
            pList = pCmeScanDB->mOneShotProfiles.mpProfiles;
            numOfSSID = pCmeScanDB->mOneShotProfiles.mNumProfiles;
            if ((numOfSSID == 0) && 
                ((!gSupplicantInitiatedScanInProgress) || (gSupplicantInitiatedScanInProgress && is_wlan_periodic_scan_in_progress())))
            {
                //one shot and survey scan has the same TAG, the difference is the existence of the ssid list
                if(gSetSiteSurvey == CME_SITE_SURVEY_RUNNING)
                {
                    scanType = SCAN_REQUEST_SURVEY_SCAN;
                }
                else
                {
                    CME_PRINT_SCAN_REPORT("\r\nscan_results_process ,Warning ! Got Rx scan TAG SCAN_REQUEST_ONE_SHOT with no SSId on the list\r\n");
                    goto out;//frame will be dropped
                }
            }
            break;
        case SCAN_REQUEST_SURVEY_SCAN:
        {
            pList = pCmeScanDB->mOneShotProfiles.mpProfiles;
            numOfSSID = pCmeScanDB->mOneShotProfiles.mNumProfiles;
        }break; // SCAN_REQUEST_ONE_SHOT | SCAN_REQUEST_SURVEY_SCAN
        case SCAN_REQUEST_CONNECT_PERIODIC_SCAN:
        {
            pList = pCmeScanDB->mPeriodicProfiles.mpProfiles;
            numOfSSID = pCmeScanDB->mPeriodicProfiles.mNumProfiles;
        }break; // SCAN_REQUEST_CONNECT_PERIODIC_SCAN
        default:
        {
            return -1;// frame has no scan tagged so it will not be dropped
        }
    }

    //if we got into here we definitely have scan tag on the RX
    if(pCmeScanDB->ETexceeded)// early termination already found a match
        goto out;//the frame will be dropped, it is scan tag frame which is not required

    /* Helpful pointer */
    pFrame  = (uint8_t*)pMacHdr + sizeof(MGMT_Header_t) + BEACON_PROBRESP_FIXED_LENGTH_FIELDS;
    pLen    = RX_BUF_LEN(desc) - sizeof(MGMT_Header_t) - BEACON_PROBRESP_FIXED_LENGTH_FIELDS;

    mbssid_support = scanParser_CheckMbssidSupport(pFrame, pLen);

    if(scanType != SCAN_REQUEST_SURVEY_SCAN 
        && !CME_IsOngoingWPSAdHocConnection()
        && (pDrv->p2pConnectionStarted == FALSE)
        && !gSupplicantInitiatedScanInProgress
        && !mbssid_support)
    {
        pBeaconFrame = (BeaconFrame_t *)(pMacHdr);
        GTRACE(GRP_SCAN_MODULE, "mx_driver_scan_results_process: parse SSID IE");
        //get SSID Element
        continue2check = IEParser_FindIe(pFrame, pLen, SSID_IE_ID, (uint8_t**)&pDot11Ssid);

         //if ssid is found in this result - check ssid match (if not - drop the result)
        if ((TRUE == continue2check) && (pDot11Ssid->hdr.eleLen <= DOT11_SSID_MAX_LEN))
        {
            dot11_RSN_t *pDotRsn = NULL, *pDotWpa = NULL, *pDotRsnOverride = NULL, *pDotRsnOverride2 = NULL;
            rsn_findSecurityIEs((uint8_t*)pFrame, pLen, &pDotRsn, &pDotWpa, &pDotRsnOverride, &pDotRsnOverride2);
            // This is a beacon or a probe response so adjust the address to be at the beginning of the IE.
            // Extract the security type
            if ((rsn_getSecurityTypes(pBeaconFrame->capabilityInfo,
                                     pDotRsn,
                                     pDotWpa,
                                     pDotRsnOverride,
                                     pDotRsnOverride2,
                                     &securityType,
                                     &securityTypeOverride,
                                     &securityTypeOverride2)) < 0) /* returned security type */
            {
                /*GTRACE(GRP_DRIVER_MX, "Error: Security type not extracted");
                CME_PRINT_SCAN_REPORT_ERROR("\r\nscan_results, Security type not extracted:channel: %d da : "MACSTR" sa: "MACSTR" bssid: "MACSTR"",
                        desc->channel,
                        MAC2STR(pMacHdr->da),
                        MAC2STR(pMacHdr->sa),
                        MAC2STR(pMacHdr->bssid));*/
                //rsn will be failed for enterprise AP
                continue2check = FALSE; //security type not found
                status =-1;
                goto out;
            }
            // Security type extracted - continue to check for a match
            if (TRUE == continue2check)
            {
                if (securityType == CME_SEC_TYPE_OPEN && pCmeScanDB->mIsOpenProfileSupported)
                {
                    // A match is found if we can find a none secure AP and open AP is supported
                    foundMatch = TRUE;
                    GTRACE(GRP_DRIVER_MX, "ENUM(EScanRequestType,%d): foundMatch %d, Open AP",
                                           scanType,
                                           foundMatch);
                }
                else if(numOfSSID > 0)
                {
                    if (securityTypeOverride2 != 0xff)
                    {
                        foundMatch = scan_result_ssid_match(pDot11Ssid,
                                                        pBeaconFrame->h.bssid,
                                                        securityTypeOverride2,
                                                        numOfSSID,
                                                        pList,
                                                        &profileId);
                    }
                    if ((foundMatch == FALSE) && (securityTypeOverride != 0xff))
                    {
                        foundMatch = scan_result_ssid_match(pDot11Ssid,
                                                        pBeaconFrame->h.bssid,
                                                        securityTypeOverride,
                                                        numOfSSID,
                                                        pList,
                                                        &profileId);
                    }
                    if (foundMatch == FALSE)
                    {
                        foundMatch = scan_result_ssid_match(pDot11Ssid,
                                                        pBeaconFrame->h.bssid,
                                                        securityType,
                                                        numOfSSID,
                                                        pList,
                                                        &profileId);
                    }

                    GTRACE(GRP_DRIVER_MX, "ENUM(EScanRequestType,%d): foundMatch %d, profile ID 0x%X, capabilities 0x%X",
                                                     scanType, foundMatch, profileId, pBeaconFrame->capabilityInfo);
                }
                else
                {
                    foundMatch = FALSE;
                }
            }
        }
        else
        {
            status =-1;
            goto out;
        }
    }
    else
    {
        //SCAN_WL18XX_PRINT("No SSID list - site_survey just update the scan table \n\r");
        foundMatch = TRUE;
    }

    if(foundMatch != FALSE &&
            !mx_driver_FilterWpsP2p(aRoleId, pFrame - BEACON_PROBRESP_FIXED_LENGTH_FIELDS, pLen + BEACON_PROBRESP_FIXED_LENGTH_FIELDS))
    {
        scanIEParsingParams_t   pParsedFrame;
        TScanFrameInfo          tScanFrameInfo;

        scanIEMultiBSSIDParams_t multiBSSIDParsingParams = {0};

        Bool_e isPeriodicScan = (scanType == SCAN_REQUEST_CONNECT_PERIODIC_SCAN);        


        do
        {
            profileId = -1;
            if (scanParser_parseFrame((dot11_mgmtFrame_t *)pMacHdr, &pParsedFrame, frameLengthWithoutDescr, &multiBSSIDParsingParams) == OK)
            {
                /* patch if DS element doesn't exist */
                if (pParsedFrame.dsParams.hdr.eleLen == 0)
                {
                    pParsedFrame.dsParams.hdr.eleId   = DS_PARAMETER_SET_IE_ID;
                    pParsedFrame.dsParams.hdr.eleLen  = 1;
                    pParsedFrame.dsParams.currChannel = desc->channel;
                }

                /* Update the regDomain that there is transmission on the channel */
                if (RXFLAGS_TO_BAND(desc->flags)== RADIO_BAND_2_4GHZ)
                {
                    regulatoryDomain_UpdateChannelValidity(pParsedFrame.rxChannel, isPeriodicScan);
                }

                /* Build the scan frame info object*/
                os_memset(&tScanFrameInfo, 0 , sizeof(TScanFrameInfo)); 
                tScanFrameInfo.pBssId           = &(pParsedFrame.bssid[0]);
                tScanFrameInfo.eBand            = (uint8_t)(RadioBand_e)RXFLAGS_TO_BAND(desc->flags);
                tScanFrameInfo.uChannel         = desc->channel;
                tScanFrameInfo.pParsedIEs       = &pParsedFrame;
                tScanFrameInfo.eRate            = desc->rate;
                tScanFrameInfo.iRssi            = EXTRACT_RSSI(desc->rx_level);
                tScanFrameInfo.uTtsfOffset      = desc->timestamp;
                tScanFrameInfo.pBuffer          = pParsedFrame.pData;
                tScanFrameInfo.uBufferLength    = pParsedFrame.uDatalen;   
            }
            else
            {
                status =-1;
                goto out;
            }

            /* It looks like it never happens. Anyway decided to check */
            if ( tScanFrameInfo.uBufferLength > MAX_BEACON_BODY_LENGTH )
            {
                Report("ERROR: frameLength=%d exceeds the limit %d \n\r",
                        tScanFrameInfo.uBufferLength, MAX_BEACON_BODY_LENGTH);
                status =-1;
                goto out;
            }

            if (getSecurities(&pParsedFrame, &securityType, &securityTypeOverride, &securityTypeOverride2) < 0 )
            {
                status =-1;
                goto out;
            }  

            if(numOfSSID > 0)
            {
                Bool_e ret = FALSE;
                if (securityTypeOverride2 != 0xff)
                {
                    ret = scan_result_ssid_match(&pParsedFrame.ssid,
                                            pParsedFrame.bssid,
                                            securityTypeOverride2,
                                            numOfSSID,
                                            pList,
                                            &profileId);

                }
                if ((ret == FALSE) && (securityTypeOverride != 0xff))
                {
                    ret = scan_result_ssid_match(&pParsedFrame.ssid,
                                            pParsedFrame.bssid,
                                            securityTypeOverride,
                                            numOfSSID,
                                            pList,
                                            &profileId);
                }
                if (ret == FALSE)
                {
                    ret = scan_result_ssid_match(&pParsedFrame.ssid,
                                            pParsedFrame.bssid,
                                            securityType,
                                            numOfSSID,
                                            pList,
                                            &profileId);
                }
            }

            /* Compare BSSID of the scan result and make sure it does not apear in the Deny List */
            /* When the Deny List is searched, expired entries are removed as well */
            if (DenyList_elementExists(&(pDrv->denyList), pParsedFrame.bssid, NULL))
            {
                Report("Scan results: BSSID %02x:%02x:%02x:%02x:%02x:%02x is in Deny List. Remove it from scan results",
                       pParsedFrame.bssid[0], pParsedFrame.bssid[1], pParsedFrame.bssid[2], pParsedFrame.bssid[3], 
                       pParsedFrame.bssid[4], pParsedFrame.bssid[5]);
                status =-1;
                goto out;
            }

            /* Update entry in result table */
            score = scan_result_calc_weighted_score(&tScanFrameInfo, scanType);

            /* If score is zero - exit */
            /* Unless its a supplicant one shot scan, where the score doesn't always matter */
            if (score == 0 && !gSupplicantInitiatedScanInProgress)
            {
                //SCAN_WL18XX_PRINT("drop scan result, score is 0. ssid = %s \n\r", tScanFrameInfo.pParsedIEs->ssid.serviceSetId);
                CME_PRINT_SCAN_REPORT("\n\rdrop scan result, score is 0, . ssid.. = %c%c%c%c%c \n\r",
                        tScanFrameInfo.pParsedIEs->ssid.serviceSetId[0],
                        tScanFrameInfo.pParsedIEs->ssid.serviceSetId[1],
                        tScanFrameInfo.pParsedIEs->ssid.serviceSetId[2],
                        tScanFrameInfo.pParsedIEs->ssid.serviceSetId[3],
                        tScanFrameInfo.pParsedIEs->ssid.serviceSetId[4]);
                status =-1;
            }
            else
            {
                CME_PRINT_SCAN_DEBUG_REPORT("\n\rScan result, score is %d. ssid = %s \n\r", score ,tScanFrameInfo.pParsedIEs->ssid.serviceSetId);
                /* According to scan type, decide which scan result table to update (or send the frame info to the caller) */
                if(scanType != SCAN_REQUEST_SURVEY_SCAN)
                {
                    scanCandidateTable_HandleResult(&tScanFrameInfo, score, profileId);

                    // Allow candidate scan to populate the survey digest table when external WPS is required
                    if (isextWPS() && isExtWpsScanning())
                    {
                        if (TRUE == scanResultTable_GetCmeScanDbPointer()->extendedScanResults)
                        {
                            scanDigestTable_HandleExtendedResult(&tScanFrameInfo, score);
                        }
                        else
                        {
                            scanDigestTable_HandleResult(&tScanFrameInfo, score);
                        }
                    }

                    if (ROLE_IS_TYPE_DEVICE(pDrv->roleType) && // relevant for p2p device scan
                        (pDrv->p2pConnectionStarted == FALSE) &&
                        (pDrv->p2pFindReportScanResults != FALSE))
                    {
                        if (TRUE == scanResultTable_GetCmeScanDbPointer()->extendedScanResults)
                        {
                            scanDigestTable_HandleExtendedResult(&tScanFrameInfo, score);
                        }
                        else
                        {
                            scanDigestTable_HandleResult(&tScanFrameInfo, score);
                        }
                    }

                }
                else
                {
                    if (TRUE == scanResultTable_GetCmeScanDbPointer()->extendedScanResults)
                    {
                        // site_survey
                        scanDigestTable_HandleExtendedResult(&tScanFrameInfo, score);
                    }
                    else
                    {
                        // site_survey
                        scanDigestTable_HandleResult(&tScanFrameInfo, score);
                    }
                }
                status = OK;
            }

            if (gConnectionScanEarlyTerminationEnabled)
            {
                // supplicant scan is not a connection scan. we want to pass the supplicant all networks
                // that meet the request requirements.
                if(OK == status && scanType != SCAN_REQUEST_SURVEY_SCAN && !gSupplicantInitiatedScanInProgress)
                {
                    Bool_e early_termination = scan_result_check_early_termination(pCmeScanDB,
                                                                    (int32_t)res_rssi,
                                                                    score);
                    if (early_termination != FALSE)
                    {
                        // need to stop scan ?
                        pCmeScanDB->ETexceeded = TRUE;
                        if(cc3xxx_trnspt_cmd_if_send_stop_scan(aRoleId , scanType, early_termination) < 0)
                        {
                            status =-1;
                            ASSERT_GENERAL(0);
                        }

                        break;
                    }
                }
            }
        }
        while( mlmeParser_getMoreSubelementsLeft(&multiBSSIDParsingParams) != 0 );
        
    }
    else
    {
        status =-1;
    }

out:

    HOOK(HOOK_IN_DRIVER_OSPREY_MX_SCAN);

    return OK;//packet will be dropped by higher layer , search for this :: if(pDrv->ops->scan_tag(roleId, (void*)desc) == OK)
}
#if 0
int8_t mx_driver_scan_results_process(CC33_FrameRxDesc_t *frame, EScanRequestType scanType)
{
    cmeScanSharedInfo_t*    pCmeScanDB = scanResultTable_GetCmeScanDbPointer();
    cmeScanProfiles_t*      pList;
    uint8_t                   numOfSSID;
    int8_t                    profileId = -1;
    int32_t                   res_rssi = GET_RSSI_VAL_FROM_DESC(frame);
    uint32_t                  score;
    Bool_e                  status =-1;
    Bool32                  foundMatch = FALSE;
    dot11_SSID_t*           pDot11Ssid;

    /* Fixing the starting address and the payload len to point after the MAC header */
    frame->address +=  sizeof(MPDUHeader_t);
    frame->length_type.length -= sizeof(MPDUHeader_t);

    if(scanType == SCAN_REQUEST_CONNECT_PERIODIC_SCAN)
    {
        pList = pCmeScanDB->mPeriodicProfiles.mpProfiles;
        numOfSSID = pCmeScanDB->mPeriodicProfiles.mNumProfiles;
    }
    else if (scanType == SCAN_REQUEST_ONE_SHOT)
    {
        pList = pCmeScanDB->mOneShotProfiles.mpProfiles;
        numOfSSID = pCmeScanDB->mOneShotProfiles.mNumProfiles;
        if(numOfSSID == 0)
        {
            scanType = SCAN_REQUEST_SURVEY_SCAN;
        }
    }
    else
    {
        GTRACE(GRP_DRIVER_MX, "mx_driver_scan_results_process: Scan type is not valid %d", scanType);
        status =-1;
        goto out;

    }

    GTRACE(GRP_DRIVER_MX, "mx_driver_scan_results_process: number of SSIDs list %d", numOfSSID);


    if(scanType != SCAN_REQUEST_SURVEY_SCAN)
    {
        Bool32          continue2check;
        uint8_t           securityType;

        /* Helpful pointer */
        uint8_t*                  pFrame  = (uint8_t*)frame->address + BEACON_PROBRESP_FIXED_LENGTH_FIELDS;
        uint16_t                  pLen    = frame->length_type.length - BEACON_PROBRESP_FIXED_LENGTH_FIELDS;
        BeaconFrame_t*          pBeaconFrame = (BeaconFrame_t *)(GET_WLAN_HEADER_START_FROM_RX_DESC(frame));

        //get SSID Element
        continue2check = IEParser_FindIe(
                              (uint8_t*)pFrame,        /* payload start */
                              pLen ,                 /* payload length */
                              SSID_IE_ID,            /* look for SSID IE */
                              (uint8_t**)&pDot11Ssid); /* returned pointer to the info element */

        //if ssid is found in this result - check ssid match (if not - drop the result)
       if ((TRUE == continue2check) && (pDot11Ssid->hdr.eleLen <= DOT11_SSID_MAX_LEN))
       {

           // This is a beacon or a probe response so adjust the address to be at the beginning of the IE.
           // Extract the security type
           if ((rsn_getSecurityType(pBeaconFrame->capabilityInfo,
                                    (uint8_t*)pFrame,      /* payload start */
                                    pLen,                /* payload length */
                                    &securityType)) < 0) /* returned security type */
           {
               GTRACE(GRP_DRIVER_MX, "Error: Security type not extracted");
               continue2check = FALSE; //security type not found
               status =-1;
               goto out;
           }
           // Security type extracted - continue to check for a match
           if (TRUE == continue2check)
           {
               if (securityType == SL_SEC_TYPE_OPEN && pCmeScanDB->mIsOpenProfileSupported)
               {
                   // A match is found if we can find a none secure AP and open AP is supported
                   foundMatch = TRUE;
                   GTRACE(GRP_DRIVER_MX, "ENUM(EScanRequestType,%d): foundMatch %d, Open AP",
                                          scanType,
                                          foundMatch);
               }
               else if(numOfSSID > 0)
               {
                   foundMatch = mx_driver_ssid_match(pDot11Ssid,
                                                     pBeaconFrame->h.bssid,
                                                     securityType,
                                                     numOfSSID,
                                                     pList,
                                                     &profileId);

                   GTRACE(GRP_DRIVER_MX, "ENUM(EScanRequestType,%d): foundMatch %d, profile ID 0x%X, Security type ENUM(CMESecType_e, %d), capabilities 0x%X",
                                                    scanType, foundMatch, profileId, (CMESecType_e) securityType, pBeaconFrame->capabilityInfo);
               }
               else
               {
                   foundMatch = FALSE;
               }
           }
       }
       else
       {
           status =-1;
           goto out;
       }
    }
    else
    {
        GTRACE(GRP_DRIVER_MX, "No SSID list - site_survey just update the scan table");
        foundMatch = TRUE;
    }

    if(foundMatch != FALSE)
    {
        scanIEParsingParams_t   *pParsedFrame;
        TScanFrameInfo          tScanFrameInfo;

        Bool_e isPeriodicScan = (scanType == SCAN_REQUEST_CONNECT_PERIODIC_SCAN);

        /* Parse received frame*/
        pParsedFrame = os_zalloc(sizeof(scanIEParsingParams_t));

        if (pParsedFrame == NULL)
        {
            GTRACE(GRP_GENERAL_ERROR, "ERROR: fail to allocate memory for scan result");
            ASSERT_GENERAL(0);
        }

        if (scanParser_parseFrame(frame, pParsedFrame) == OK)
        {
            /* patch if DS element doesn't exist */
            if (pParsedFrame->dsParams.hdr.eleLen == 0)
            {
                pParsedFrame->dsParams.hdr.eleId   = DS_PARAMETER_SET_IE_ID;
                pParsedFrame->dsParams.hdr.eleLen  = 1;
                pParsedFrame->dsParams.currChannel = frame->sw_tagging.channel;
            }

            /* Update the regDomain that there is transmission on the channel */
            if (frame->sw_tagging.band != RADIO_BAND_2_4GHZ)
            {
                regulatoryDomain_UpdateChannelValidity(pParsedFrame->rxChannel, isPeriodicScan);
            }
            /* Save the Country IE - If periodic scan set new country in reg domain */
            if ((pParsedFrame->country.hdr.eleId != 0) && (pParsedFrame->country.hdr.eleLen != 0))
            {
                if (frame->sw_tagging.band == RADIO_BAND_2_4GHZ)
                {
                    if (isPeriodicScan)
                    {
                        regulatoryDomain_setSupportedChannelsAccording2CountryIe(&pParsedFrame->country,
                                                                                 TRUE,
                                                                                 TRUE);
                    }
                }
                else // RADIO_BAND_5GHZ
                {
                    if (isPeriodicScan)
                    {
                        regulatoryDomain_setSupportedChannelsAccording2CountryIe(&pParsedFrame->country,
                                                                                 FALSE,
                                                                                 TRUE);
                    }
                }
            }

            /* Build the scan frame info object*/
            tScanFrameInfo.pBssId           = &(pParsedFrame->bssid[0]);
            tScanFrameInfo.eBand            = (RadioBand_e)frame->sw_tagging.band;
            tScanFrameInfo.uChannel         = frame->sw_tagging.channel;
            tScanFrameInfo.pParsedIEs       = pParsedFrame;
            tScanFrameInfo.eRate            = (RateIndex_e)frame->phy_information1.rate;
            tScanFrameInfo.iRssi            = GET_RSSI_VAL_FROM_DESC(frame);
            tScanFrameInfo.uTtsfOffset      = RxBeacon_CalculateNewRoleOffset( frame );
            tScanFrameInfo.pBuffer          = pParsedFrame->pData;
            tScanFrameInfo.uBufferLength    = pParsedFrame->uDatalen;
        }

        /* It looks like it never happens. Anyway decided to check */
        if ( tScanFrameInfo.uBufferLength > MAX_BEACON_BODY_LENGTH )
        {
            GTRACE( GRP_GENERAL_ERROR, "ERROR: frameLength=%d exceeds the limit %d",
                    tScanFrameInfo.uBufferLength, MAX_BEACON_BODY_LENGTH);
            status =-1;
            goto out;
        }

        /* Update entry in result table */
        score = scan_result_calc_weighted_score(&tScanFrameInfo, scanType);

        /* If score is zero - exit */
        if (score == 0)
        {
            GTRACE(GRP_DRIVER_MX, "drop scan result, score is 0. ssid = %s", tScanFrameInfo.pParsedIEs->ssid.serviceSetId);
            status =-1;
        }
        else
        {
            GTRACE(GRP_DRIVER_MX, "Scan result, score is %d. ssid = %s", score ,tScanFrameInfo.pParsedIEs->ssid.serviceSetId);
            /* According to scan type, decide which scan result table to update (or send the frame info to the caller) */
            if(scanType != SCAN_REQUEST_SURVEY_SCAN)
            {
                scanCandidateTable_HandleResult(&tScanFrameInfo, score, profileId);
            }
            else
            {
                // site_survey
                scanDigestTable_HandleResult(&tScanFrameInfo, score);
            }
            status = OK;
        }
        os_free(pParsedFrame);
    }
    else
    {
        status =-1;
    }

    if(OK == status && scanType != SCAN_REQUEST_SURVEY_SCAN)
    {

        Bool_e early_termination = mx_driver_scan_check_early_termination(pCmeScanDB,
                                                        (int32_t)res_rssi,
                                                        score);
        if (early_termination != FALSE)
        {
          GTRACE(GRP_DRIVER_MX, "scan Early Terminate: rssi ET TH = -%d, rssi = -%d, score TH = %d, score = %d",
                 CONVERT_SIGN(pCmeScanDB->mRssiEarlyTermThreshold),
                 CONVERT_SIGN(res_rssi),
                 pCmeScanDB->mScoreEarlyTermThreshold,
                 score);

          pCmeScanDB->ETexceeded = TRUE;
          mx_driver_send_scan_stop_cmd(frame->link_role.role_id, scanType, early_termination);
        }
    }
out:
    return status;
}
#endif

/******************************************************************************

    FUNCTION:		mx_driver_scan_is_scan_tagged_frame

    PROTOTYPE:		driver_osprey_mx_scan

    DESCRIPTION:    Check if the frame is scan tagged frame

    CALLER:         isRxMgmtFrameSafeToFilter

    PARAMETERS:     pDesc - pointer to RX descriptor

    RETURNS:        true / false

******************************************************************************/
bool mx_driver_scan_is_scan_tagged_frame(void *pDesc)
{
    HOOK(HOOK_IN_DRIVER_OSPREY_MX_SCAN);

    RxIfDescriptor_t *pFrame = (RxIfDescriptor_t *)pDesc;

    EScanRequestType scanTag = ((pFrame->status) & 0x38) >> 3; // scan tag bit 3:5

    return ((scanTag != SCAN_REQUEST_NONE) && (scanTag < SCAN_NUM_OF_REQUEST_TYPE));
}

/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_check_scan_tagged_frame

    PROTOTYPE:		driver_osprey_mx_scan

    DESCRIPTION:    Check if Frame is scan related, if not continue
                    regular flow processing.

    CALLER:         handler RX management frame

    PARAMETERS:     pDesc - pointer to RX descriptor

    RETURNS:        0 - scan tagged and updated scan table
                    other - untagged frame

******************************************************************************/
int cc3xxx_trnspt_cmd_if_check_scan_tagged_frame(uint32_t aRoleId, void *desc)
{
    HOOK(HOOK_IN_DRIVER_OSPREY_MX_SCAN);

    int status =-1;

    RxIfDescriptor_t *frame = (RxIfDescriptor_t *)desc;

    EScanRequestType scanTag = ((frame->status) & 0x38) >> 3; // scan tag bit 3:5
    

    if( scanTag != SCAN_REQUEST_NONE && scanTag < SCAN_NUM_OF_REQUEST_TYPE)
    {
        RX_MGMT_PRINT("\n\rcheck_scan_tagged_frame: rx MGMT frame is of SCAN : scanTag:%d", scanTag);
        GTRACE(GRP_SCAN_MODULE, "check_scan_tagged_frame: rx MGMT frame is of SCAN : scanTag:%d", scanTag);
        status = mx_driver_scan_results_process(aRoleId, (RxIfDescriptor_t*)frame, (EScanRequestType)scanTag);
        if(status < 0){
            GTRACE(GRP_DRIVER_CC33, "Unable to update table");
            RX_MGMT_PRINT_ERROR("\n\rERROR parse scan results ,Unable to update table");
        }

        status = OK;
    }
    else
    {
        /* not scan tag */
        status =-1;
    }

#if 0
    uint8_t frameType;
    uint8_t scanTag = frame->sw_tagging.scan_tag;

    GTRACE(GRP_DRIVER_MX_DEBUG, "cc3xxx_trnspt_cmd_if_check_scan_tagged_frame: check tagged frame %d", frame->sw_tagging.scan_tag);
    if (WLAN_ROLE_RX_TAG != frame->sw_tagging.scan_tag)
    {
        // There is scan resumed
        if (INVALID_RX_TAG != frame->sw_tagging.scan_tag)
        {

            // Frame is tagged
            // Verify that it is scan material - beacon or probe response
            frameType = frame->length_type.frame_type;
            if ((frameType == FRAME_TYPE_BEACON) || (frameType == FRAME_TYPE_PROBE_RESPONSE))
            {
                GTRACE(GRP_DRIVER_MX, "Frame is scan tagged and frame type is 0x%x, scan type ENUM(EScanRequestType,%d)",
                       frameType,
                       (EScanRequestType)scanTag);

                status = mx_driver_scan_results_process(frame, (EScanRequestType)scanTag);
            }
        }
    }
#endif

    return status;

}
/******************************************************************************

    FUNCTION:		trnspt_cmd_build_scan_channel_list

    PROTOTYPE:		driver_osprey_mx_scan

    DESCRIPTION:    Build channel list for ONE_SHOT/Periodic scan
                    If the supplicant not given the channel list we
                    build the list manually.
                    For periodic scan we also prepare the scan scheduler
                    plan.
                    The channel list build according to the RegDomain

    CALLER:         mx_driver_one_shot_scan | mx_driver_sched_scan

    PARAMETERS:     scanParam - Pointer to driver object
                    scanType - Pointer to scan configuration
                    apSuppParams - Pointer to supplicant parameters

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t trnspt_cmd_build_scan_channel_list(ScanParams_t *scanParam,
                                        EScanRequestType scanType,
                                        struct wpa_driver_scan_params *apSuppParams,
                                        uint8_t max_sched_scan_plans,WlanBandCfg_e Band)
{

    ChannelInfo_t       *pChannelList;
    uint8_t             *pNumOfPassive;
    uint8_t             *pNumOfDfs;
    uint8_t             *pNumOfActive;
    channelCapability_t channelCapability;
    int32_t             status;
    uint8_t             sizeOfBG = 0;
    uint8_t             sizeOfA = 0;
    uint16_t            localChannel[SCAN_MAX_CHANNELS_NUM] = PERIODIC_SCAN_CHANNELS_ARRAY_B_G_A_BAND;
    uint8_t             passiveIdx = 0;
    uint8_t             numOfActiveChannels = 0;
    ChannelInfo_t       activeScanChanInfo[SCAN_MAX_CHANNELS_A];
    volatile uint8_t    index = 0;
    uint8_t             index24 = 0;
    uint8_t             index5 = SCAN_MAX_CHANNELS_BG;
    uint8_t             is5GhzSupported = 0;

    // Check if there is channel list comes from supplicant
    if (NULL != apSuppParams)
    {
        if (NULL != apSuppParams->freqs)
        {
            // When receiving a channels list from the supplicant,
            // we are interested only in these channels, so reset the local channel list.
            os_memset(localChannel, 0, sizeof(uint16_t) * SCAN_MAX_CHANNELS_NUM);

            // Supplicant-supplied frequencies array is guaranteed to be zero-terminated
            for (index = 0; apSuppParams->freqs[index]; ++index)
            {
                // Check for overflow when accessing localChannel array
                if (index24 >= SCAN_MAX_CHANNELS_BG)
                {
                    GTRACE(GRP_DRIVER_MX, "build_channel_list: 2.4G index "
                                          "out of range. index24 = %d, max = %d",
                                          index24, SCAN_MAX_CHANNELS_BG);
                    return -1;
                }

                if (index5 >= SCAN_MAX_CHANNELS_NUM)
                {
                    GTRACE(GRP_DRIVER_MX, "build_channel_list: 5G index "
                                          "out of range. index5 = %d, max = %d",
                                          index5, SCAN_MAX_CHANNELS_NUM);
                    return -1;
                }


                if (BASE_FREQ_5_0 <= apSuppParams->freqs[index])
                {
                    localChannel[index5] = (apSuppParams->freqs[index] - BASE_FREQ_5_0)/5;
                    GTRACE(GRP_DRIVER_MX, "[%d] channel2scan %d", index, localChannel[index5]);
                    index5++;
                }
                else if (BASE_FREQ_2_4 <= apSuppParams->freqs[index])
                {
                    localChannel[index24] = (apSuppParams->freqs[index] - BASE_FREQ_2_4)/5;
                    GTRACE(GRP_DRIVER_MX, "[%d] channel2scan %d", index, localChannel[index24]);
                    index24++;
                }

            }
        }
    }

    if (scanType == SCAN_REQUEST_CONNECT_PERIODIC_SCAN)
    {
        periodicParams_t *pPeriodicScanParams = &scanParam->u.tConnScanInfo;

        pChannelList     = scanParam->u.tConnScanInfo.channelList;
        pNumOfActive     = (uint8_t*)&scanParam->u.tConnScanInfo.numOfActive;
        pNumOfPassive    = (uint8_t*)&scanParam->u.tConnScanInfo.numOfPassive;
        pNumOfDfs        = (uint8_t*)&scanParam->u.tConnScanInfo.numOfDfs;

        // Set scan plan
        if ((apSuppParams->sched_scan_plans_num == 0) || (!apSuppParams->sched_scan_plans))
        {
            return -1;
        }

        //Check if number of plans exceeds driver support
        if (apSuppParams->sched_scan_plans_num > max_sched_scan_plans)
        {
            GTRACE(GRP_GENERAL_ERROR, "ERROR: Sched scan: Num of plans exceeds the driver support");
            return -1;
        }

        os_memcpy(pPeriodicScanParams->sched_scan_plans, apSuppParams->sched_scan_plans,
                  (sizeof(struct sched_scan_plan) * apSuppParams->sched_scan_plans_num));
        scanParam->u.tConnScanInfo.sched_scan_plans_num = apSuppParams->sched_scan_plans_num;
    }
    else
    {
        pChannelList     = scanParam->u.tScanInfo.channelList;
        pNumOfActive     = (uint8_t*)&scanParam->u.tScanInfo.numOfActive;
        pNumOfPassive    = (uint8_t*)&scanParam->u.tScanInfo.numOfPassive;
        pNumOfDfs        = (uint8_t*)&scanParam->u.tScanInfo.numOfDfs;
    }

    /*************************/
    /* Build G band channels */
    /*************************/
    if ((Band == BAND_SEL_ONLY_2_4GHZ) || (Band == BAND_SEL_BOTH))
    {
        for (index = 0 ; (localChannel[index] > 0) && (index < SCAN_MAX_CHANNELS_BG); index++)
        {
            status = regulatoryDomain_GetCapability(RADIO_BAND_2_4GHZ,
                                                    localChannel[index],
                                                    &channelCapability);
            //channel is not valid - ignore it
            if (status == OK)
            {
                //if channel is valid for active - put it in temporary buffer. active channels will be
                //copied after all passive channels in this band.
                if (TRUE == channelCapability.channelValidityActive)
                {
                    activeScanChanInfo[numOfActiveChannels].channel = localChannel[index];
                    activeScanChanInfo[numOfActiveChannels].txPowerLevelDbm = channelCapability.uMaxTxPowerDomain;
                    activeScanChanInfo[numOfActiveChannels].channelFlags = 0;
                    numOfActiveChannels++;
                    pNumOfActive[RADIO_BAND_2_4GHZ]++;

                }
                else if (TRUE == channelCapability.channelValidityPassive)
                {
                    pChannelList[passiveIdx].channel = localChannel[index];
                    pChannelList[passiveIdx].txPowerLevelDbm = channelCapability.uMaxTxPowerDomain;
                    pChannelList[passiveIdx].channelFlags = 0;
                    passiveIdx++;
                    pNumOfPassive[RADIO_BAND_2_4GHZ]++;
                }
            }
        }

#ifdef CME_CC3XX_PORT_LOG_REPORT
        CME_CC3XX_PORT_PRINT("Active 2.4G ch list: ");
        for (int i = 0; i < numOfActiveChannels; i++)
        {
            CME_CC3XX_PORT_PRINT("%d,", activeScanChanInfo[i].channel);
        }
        CME_CC3XX_PORT_PRINT("\n");
        CME_CC3XX_PORT_PRINT("Passive 2.4G ch list: ");
        for (int i = 0; i < passiveIdx; i++)
        {
            CME_CC3XX_PORT_PRINT("%d,", pChannelList[i].channel);
        }
        CME_CC3XX_PORT_PRINT("\n");
        CME_CC3XX_PORT_PRINT("Total of 2.4G: Active  = %d , num of 2.4G passive= %d \n", numOfActiveChannels, passiveIdx);
#endif//CME_CC3XX_PORT_LOG_REPORT

        // Copy active channels right after passive channels
        os_memcpy((void*)(&pChannelList[passiveIdx]),
                  (void*)activeScanChanInfo,
                  sizeof(ChannelInfo_t)*numOfActiveChannels);

        sizeOfBG = numOfActiveChannels + passiveIdx;
    }
    /*************************/
    /* Build A band channels */
    /*************************/
    is5GhzSupported = (uint8_t)l2_cfg_is5GhzSupported();

    numOfActiveChannels = 0;
    if (((Band == BAND_SEL_ONLY_5GHZ) || (Band == BAND_SEL_BOTH)) &&
        (is5GhzSupported))
    {
        /* Build A band channels*/
        os_memset(activeScanChanInfo, 0x00, sizeof(ChannelInfo_t)*SCAN_MAX_CHANNELS_A);

        passiveIdx = SCAN_MAX_CHANNELS_BG;

        for (index = SCAN_MAX_CHANNELS_BG;
             (localChannel[index] < A_5G_BAND_MAX_CHANNEL) &&
             (localChannel[index] >= A_5G_BAND_MIN_CHANNEL) &&
             (index < SCAN_MAX_CHANNELS_NUM);
             index++)
        {
            status = regulatoryDomain_GetCapability(RADIO_BAND_5GHZ,
                                                    localChannel[index],
                                                    &channelCapability);
            // Channel is not valid - ignore it
            if (OK == status)
            {
                /********************************************/
                /* A band: construct passive channels first */
                /********************************************/
                if ((FALSE == channelCapability.channelValidityActive) &&
                    (TRUE  == channelCapability.channelValidityPassive) &&
                    ((channelCapability.uFlags & TIW_REG_DOMAIN_DFS) == 0))
                {
                    pChannelList[passiveIdx].channelFlags = 0;
                    pChannelList[passiveIdx].channel = localChannel[index];
                    pChannelList[passiveIdx].txPowerLevelDbm = channelCapability.uMaxTxPowerDomain;
                    passiveIdx++;
                    pNumOfPassive[RADIO_BAND_5GHZ]++;
                }
                /****************************************************************************/
                /* A Band: construct DFS channels next. they are put after passive channels */
                /****************************************************************************/
                else if ((FALSE == channelCapability.channelValidityActive) &&
                         (TRUE  == channelCapability.channelValidityPassive) &&
                         (channelCapability.uFlags & TIW_REG_DOMAIN_DFS))
                {
                    pChannelList[passiveIdx].channelFlags = TIW_REG_DOMAIN_DFS;
                    pChannelList[passiveIdx].channel = localChannel[index];
                    pChannelList[passiveIdx].txPowerLevelDbm = channelCapability.uMaxTxPowerDomain;
                    passiveIdx++;
                    pNumOfDfs[0]++;

                }
                /******************************************/
                /* A Band: construct active channels last */
                /******************************************/
                else if ((TRUE == channelCapability.channelValidityActive) &&
                         ((channelCapability.uFlags & TIW_REG_DOMAIN_DFS) == 0))
                {
                    activeScanChanInfo[numOfActiveChannels].channelFlags = 0;
                    activeScanChanInfo[numOfActiveChannels].channel = localChannel[index];
                    activeScanChanInfo[numOfActiveChannels].txPowerLevelDbm = channelCapability.uMaxTxPowerDomain;
                    numOfActiveChannels++;
                    pNumOfActive[RADIO_BAND_5GHZ]++;
                }
            }
        }

#ifdef CME_CC3XX_PORT_LOG_REPORT
        CME_CC3XX_PORT_PRINT("Passive/dfs 5G ch list:");
        for (int i = SCAN_MAX_CHANNELS_BG; i < passiveIdx; i++)
        {
            CME_CC3XX_PORT_PRINT("%d,", pChannelList[i].channel);
        }
        CME_CC3XX_PORT_PRINT("\n");
        CME_CC3XX_PORT_PRINT("Active 5G ch list:");
        for (int i = 0; i < numOfActiveChannels; i++)
        {
            CME_CC3XX_PORT_PRINT("%d,", activeScanChanInfo[i].channel);
        }
        CME_CC3XX_PORT_PRINT("\n");

        CME_CC3XX_PORT_PRINT("Total num of 5G Active  = %d,num of 5G passive/dfs  = %d \n", numOfActiveChannels, pNumOfDfs[0]);
#endif //CME_CC3XX_PORT_LOG_REPORT

        // Copy active channels right after passive channels
        if (passiveIdx + numOfActiveChannels >= CONN_SCAN_MAX_CHANNELS_ALL_BANDS)
        {
            return WlanError(WLAN_ERROR_SEVERITY__HIGH,
                            WLAN_ERROR_MODULE__COMMANDS,
                            WLAN_ERROR_TYPE__CMD_GENERAL);
        }
        else
        {
            os_memcpy((void*)(&pChannelList[passiveIdx]),
                      (void*)activeScanChanInfo,
                      sizeof(ChannelInfo_t) * numOfActiveChannels);
        }
    }

    if (numOfActiveChannels + passiveIdx > SCAN_MAX_CHANNELS_BG)
    {
        sizeOfA = numOfActiveChannels + passiveIdx - SCAN_MAX_CHANNELS_BG;
    }

    if ((sizeOfBG + sizeOfA) == 0)
    {
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR: No valid channels found for scan!!\n\r");
        return -1;
    }

    GTRACE(GRP_DRIVER_MX, "Finish build channel list: num of BG channel %d, num of A channel %d",
           sizeOfBG,
           sizeOfA);
    CME_CC3XX_PORT_PRINT("Finish build channel list: num of BG channel %d, num of A channel %d\n",
           sizeOfBG,
           sizeOfA);
    CME_CC3XX_PORT_PRINT("Finish build channel list: numOf5G_ActiveChannels=%d , Total Passive (2.4+5G)= %d , num_of_dfs = %d\n",numOfActiveChannels,passiveIdx,pNumOfDfs[0]);

    HOOK(HOOK_IN_DRIVER_OSPREY_MX_SCAN);

    return 0;
}
