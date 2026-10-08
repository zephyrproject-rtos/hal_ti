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
  FILENAME:       cme_user_if.c

  DESCRIPTION:    Handle internal requests and notifications.
                  
  HISTORY:
                  04/15 Creation
  ----------------------------------------------------------------------------- */

// the below should be included by wpa_supplicant_i.h, added here in order to
// avoid changes in wpa_supplicant_i.h
#include <stdio.h>
#include "common.h"

#include "wpa_supplicant_i.h"
#include "p2p_supplicant.h" 
#include "p2p/p2p.h" 
#include "drv_ti_internal.h"
#include "drivers/driver.h"
#include "scan.h"
#include "cme_scan_api.h"
#include "cme_internal_api.h"
#include "cme_supplicant_api.h"
#include "cme_defs.h"
#include "osi_kernel.h"
#include "802_11defs.h"
#include "wlan_if.h"
#include <driver/drv_core.h>
#include "gtrace.h"
#include "scan_result_table.h"
#include "cme_defs.h"
#include "p2p_i.h"
#include "drv_ext_app.h"

// ============================================================================
//      Modules data base
// ============================================================================

// TODO - move all module globals to one structure !!!

// Contains site survey scan results.
// Used to supply host & HTTP server a list of neighbor networks.
cmeSiteSurveyResults_t      gSiteSurveyInfo; //MEM_REGION_GLX, In site survey we don't go to power save.

// Serves as temporary container for candidates scan results.
// Filled by scan context,  retrieved (via driver_cc33) by suplicant from
// CME context. After results are retrieved allocated memory is released and all
// information is reset.
cmeConnectionCandidates_t   gCandidatesInfo ;

// Mark whether last triggered scan was site survey; used for setting scan
// parameters for scan module
cmeSiteSurveyState_t gSetSiteSurvey; //MEM_REGION_GLX, site survey does not go to sleep

// Timer which waits for survey scan complete
OsiTimer_t gTimerSiteSurveyComplete = {0};
#define CME_SURVEY_SCAN_TIMEOUT    (20000) //Mili, 20 sec

// Timer which waits for one shot scan complete
OsiTimer_t gTimerOneShotScanComplete = {0};
#define CME_ONE_SHOT_SCAN_TIMEOUT    (30000) //Mili, 30 sec

// Timer which waits for periodic scan complete
OsiTimer_t gTimerPeriodicScanComplete = {0};
#define CME_PERIODIC_SCAN_TIMEOUT    (40000) //Mili, 40 sec


//P2P Info related flags
cmeP2pSearchInfo_t  gCmeP2pInfo;

#define SCAN_MAX_DWELL_TIME_PASSIVE_MSEC            (110)
#define SCAN_MIN_DWELL_TIME_PASSIVE_MSEC            (110)
#define SCAN_MAX_DWELL_TIME_ACTIVE_MSEC             (60)
#define SCAN_MIN_DWELL_TIME_ACTIVE_MSEC             (25)

#define SCAN_DFS_DWELL_TIME_PASSIVE_MSEC            (150)

WlanScanDwellTime_t scanDwellTimeParams = {
    .max_dwell_time_passive_msec = SCAN_MAX_DWELL_TIME_PASSIVE_MSEC,
    .min_dwell_time_passive_msec = SCAN_MIN_DWELL_TIME_PASSIVE_MSEC,
    .max_dwell_time_active_msec  = SCAN_MAX_DWELL_TIME_ACTIVE_MSEC,
    .min_dwell_time_active_msec  = SCAN_MIN_DWELL_TIME_ACTIVE_MSEC,
    .dwell_time_dfs_passive_msec = SCAN_DFS_DWELL_TIME_PASSIVE_MSEC
};

// Points to wpa_supplicant interfaces
extern struct wpa_global *gpSupplicantGlobals;

// Probe request extra IEs
// Received from supplicant as part of connection scan command parameters.
// Stored in ULL, to be handed to scan module before every new scan cycle.
// The buffer itsels gProbeRequestExtraIes_ull->pExtraIesBuffer is allocated in glx when one shot connection is kicked,
// and is freed in cmeScanDone.
// !!! Must be stored in ULL memory !!!
ProbeRequestInfo_t gProbeRequestExtraIes_ull ;


// ============================================================================
//      External Functions
// ============================================================================
/* WLAN event dispatcher to host */
extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t * args, uint16_t argsLen);
extern void set_finish_wlan_periodic_scan();
extern void set_finish_wlan_one_shot_scan();


// ============================================================================
//      Local Functions declarations
// ============================================================================
void CME_start_survey_scan_timer();
void CME_survey_scan_timeout();
void CME_survey_scan_timer_stop();

void CME_start_one_shot_scan_timer();
void CME_one_shot_scan_timeout();
void CME_one_shot_scan_timer_stop();

void CME_start_periodic_scan_timer();
void CME_periodic_scan_timeout();
void CME_periodic_scan_timer_stop();


void cmeScan_store_scan_dwell_times(WlanScanDwellTime_t dwellTimeParams)
{
    os_memcpy(&scanDwellTimeParams,&dwellTimeParams,sizeof(WlanScanDwellTime_t));
}
// ============================================================================
//      Exported Functions Code section
// ============================================================================
void cmeScan_InitAfterSleep()
{
    HOOK(HOOK_IN_CME_SCAN);

    gSetSiteSurvey = CME_SITE_SURVEY_IDLE;
}

// ----------------------------------------------------------------------------
void cmeScanInit()
{
    HOOK(HOOK_IN_CME_SCAN);

    cmeScan_InitAfterSleep();
    // Note: this part should be activated only after reset and must not be
    // activated after a transition from low to full power mode,
    gProbeRequestExtraIes_ull.extraIesLength = 0;
    gProbeRequestExtraIes_ull.pExtraIesBuffer = NULL;

    //initialize site survey buffers:
    os_memset(&gSiteSurveyInfo, 0, sizeof(gSiteSurveyInfo));
    gSiteSurveyInfo.pSiteNetworks = NULL;
    gSiteSurveyInfo.responseCount = 0;
    gSiteSurveyInfo.responseInternalEvent = 0;
    gSiteSurveyInfo.responseStartIndex = 0;
}

// ----------------------------------------------------------------------------
// For SL R2 reference see performSingleScan

uint8_t* cmeGetScanResults(uint32_t aIndex, uint32_t NumOfResultsFound, uint32_t aExtraBytes, uint32_t *apNumNetworks, uint32_t *apNumBytes)

{
    HOOK(HOOK_IN_CME_SCAN);

    uint8_t  *pBuff = NULL;
    uint32_t numResults = 0;
    uint32_t resultsLen = 0;
    uint8_t *pSrc;
    uint8_t *pDst;
    uint8_t i;
    size_t scanEntrySize;

    if ( (NULL != gSiteSurveyInfo.pSiteNetworks) && (gSiteSurveyInfo.responseCount))
    {
//      uint32_t currTimeMs = osi_GetTimeMS();

        GTRACE(GRP_CME, "Site survey results exist, curr time %d ", osi_GetTimeMS());
        //CME_PRINT_REPORT("\n\rSite survey results exist, curr time %d ", osi_GetTimeMS());

        // No need to scan, send response to host immediately.
        // TODO enable the line below !!!!!!
        // if ( (currTimeMs - gSiteSurveyInfo.lastSiteNetworksUpdate) < CME_SITE_SURVEY_SCAN_RESULTS_AGING_MS )
        {


            numResults = MIN( NumOfResultsFound, (gSiteSurveyInfo.responseCount - aIndex) );
            GTRACE(GRP_CME, "Site survey results are valid, results to send(requested) %d, starting from %d (# NumOfResultsFound %d)", numResults, aIndex, NumOfResultsFound);
            CME_PRINT_REPORT("\n\rSite survey results are valid,results to send(requested) %d, starting from %d (# NumOfResultsFound %d)", numResults, aIndex, NumOfResultsFound);
            if(numResults == 0)
            {
                GTRACE(GRP_CME, "cmeGetScanResults No scan result");
                numResults = 1;
                if(gSiteSurveyInfo.pSiteNetworks == NULL)
                {
                    return NULL;
                }
            }

            scanEntrySize = scanResultTable_GetCmeScanDbPointer()->extendedScanResults ? sizeof(WlanNetworkEntryExtended_t) : sizeof(WlanNetworkEntry_t);
            resultsLen = numResults * scanEntrySize;

            pBuff = os_zalloc(resultsLen+aExtraBytes);
            if (NULL == pBuff)
            {
                GTRACE(GRP_CME,"failed to allocate %d bytes for sending scan results to host %d", resultsLen+aExtraBytes);
                CME_PRINT_REPORT("\n\rfailed to allocate %d bytes for sending scan results to host %d", resultsLen+aExtraBytes);
            }
            else
            {
                // Copy the results to the response buffer, leaving aExtraBytes for dispatcher usage
                // Can't use the original buffer:
                //       buffer is released after being transmitted by host if.
                //       host may retrieve results in chunks.

                //Need to copy each result separately since cmeScanDigestResult_t contains also mScore, which does not exists in SlWlanNetworkEntry_t
                pSrc = &gSiteSurveyInfo.pSiteNetworks[aIndex];
                pDst = &pBuff[aExtraBytes];
                if (TRUE == scanResultTable_GetCmeScanDbPointer()->extendedScanResults)
                {
                    for (i=0; i < numResults; i++)
                    {
                        memcpy((void *)pDst, (void *)pSrc, MIN(sizeof(WlanNetworkEntryExtended_t), sizeof(cmeNetworkExtendedEntryResult_t)));
                        pSrc+= sizeof (cmeExtendedScanDigestResult_t);
                        pDst+=sizeof (WlanNetworkEntryExtended_t);

                    }
                    resultsLen += aExtraBytes;

                }
                else
                {
                    for (i=0; i < numResults; i++)
                    {
                        memcpy((void *)pDst, (void *)pSrc, MIN(sizeof(WlanNetworkEntry_t), sizeof(cmeNetworkEntryResult_t)));
                        pSrc+= sizeof (cmeScanDigestResult_t);
                        pDst+=sizeof (WlanNetworkEntry_t);

                    }
                    resultsLen += aExtraBytes;
                }


            }
        }
        // else results need to be refreshed
    }
    else
    {
        //only allocate the extra bytes (no results)
            pBuff = os_zalloc(aExtraBytes);
            if (NULL == pBuff)
            {
                GTRACE(GRP_CME,"failed to allocate %d bytes for sending scan results to host", resultsLen+aExtraBytes);
                CME_PRINT_REPORT("\n\rfailed to allocate %d bytes for sending scan results to host", resultsLen+aExtraBytes);
            }                
        resultsLen = aExtraBytes;

    }

    *apNumNetworks = numResults;
    *apNumBytes = resultsLen;

    return pBuff;

}

// ----------------------------------------------------------------------------
// Nov 7 2016 - scan early termination threshold handling
// ----------------------------------------------------------------------------
void cmeScanEarlyTermThresholdSet(cmeScanSharedInfo_t *apSharedInfo, int shouldUseFastConnect, int profile_priority/*-1 means ad-hoc*/, int secured_profile)
{
    HOOK(HOOK_IN_CME_SCAN);

    if (shouldUseFastConnect != 0)
    {
       //
       //if fast connect policy is set, and scan frame didnt succeed
       //then we wish to connect to the first reasonable RSSI candidate we encounter
       //
        apSharedInfo->mRssiEarlyTermThreshold    = scan_result_get_good_rssi();
    }
    else
    {

        //if fast connect policy is not set, we can early terminate the scan
        if (profile_priority != -1)
        {
           //PROFILE CONNECTION case
           //only if we see one of the results in the best score available, then there is no use on continuing the scan
            apSharedInfo->mScoreEarlyTermThreshold = scan_result_calc_highest_score_for_profile_priority(profile_priority,secured_profile);
        }
        else
        {
           //AD HOC CONNECTION case
           //only if we see the result in the best RSSI, then there is no use on continuing the scan
            apSharedInfo->mRssiEarlyTermThreshold = scan_result_get_best_rssi();
        }
    }

    GTRACE(GRP_CME,"cmeScanEarlyTermThresholdSet: secured_profile %d, profile_priority %d, mScoreEarlyTermThreshol=%d, mRssiEarlyTermThreshol=%d",
        secured_profile,profile_priority,apSharedInfo->mScoreEarlyTermThreshold,apSharedInfo->mRssiEarlyTermThreshold);

   CME_CON_PRINT("\n\rcmeScanEarlyTermThresholdSet: secured_profile %d, profile_priority %d, mScoreEarlyTermThreshol=%d, mRssiEarlyTermThreshol=%d",
        secured_profile,profile_priority,apSharedInfo->mScoreEarlyTermThreshold,apSharedInfo->mRssiEarlyTermThreshold);

    HOOK(HOOK_IN_CME_SCAN);
}

// ----------------------------------------------------------------------------
int32_t cmeSetScanCmeInfo(cmeScanSharedInfo_t *apSharedInfo,
                        EScanRequestType    aScanType,
                        OsiSyncObj_t        *apSyncObj,
                        struct wpa_driver_scan_params   *apParams)
{
    HOOK(HOOK_IN_CME_SCAN);

    int32_t rc = 0;
    uint8_t maxNumOfCandidates;
    uint16_t ScanMemSize;
    size_t scanEntrySize;

    ASSERT_GENERAL(NULL != apSharedInfo);


    //
    // Nov 7 2016 - zero early termination conditions by default. will be set if relevant in prepareProfileInfo
    apSharedInfo->mRssiEarlyTermThreshold = 0;
    apSharedInfo->mScoreEarlyTermThreshold = 0;
    apSharedInfo->ETexceeded = FALSE;
    //

    // ------------------------------------------------------------------------
    //  Notes:
    //    (1) The same cmeScanSharedInfo_t stucture may be used for concurrent
    //        scans (one shot & periodic). Hence some fields may have already
    //        been set. Only updated fields should be touched here.
    //    (2) Only one scan type at a time is allowed by design. So if site survey
    //        scan is running, connection scan can't be started (and vice versa).
    // ------------------------------------------------------------------------
    // Prepare connection scan info
    if (aScanType != SCAN_REQUEST_SURVEY_SCAN)
    {
        apSharedInfo->mNumCandidatesFound = 0;

        // Candidates memory may be allocated or not allocated depending on system state:
        //      - out of reset/Sleep - not allocated
        //      - if connection candidate was found in previous cycle - not allocated
        //        (release by driver_cc currently after constructing assoc request,
        //         may be moved to successful connection)
        //      - between one shot/periodic scan cycles if no candidates were found
        //        and device remained in active mode - allocated
        //

        // NOTE: gCandidatesInfo.pCandidateScanResults must be used for testing DB state
        // since CME updates this one and not apSharedInfo.
        if (NULL != gCandidatesInfo.pCandidateScanResults)
        {
            CME_ReleaseScanResults(CALLER4); //Make sure we don't have any leftovers from previous scan.
        }

        // For WPS we have to allocate more entries (to pass supplicant all WPS available networks in the vicinity)
        // Also in scan requests triggered by the supplicant, we often look for more than one network
        if (CME_IsOngoingWPSAdHocConnection() || gSupplicantInitiatedScanInProgress)
        {
            maxNumOfCandidates = CME_SCAN_WPS_P2P_MBO_MAX_CANDIDATES;
        }
        else
        {
            maxNumOfCandidates = CME_SCAN_MAX_CANDIDATES;
        }

        //ull needs to be used here since the candidate info is kept for the connection phase,(authentication and association),
        //but supplicant can decide to go back to scans, and not connection, in case id does not find what it wants in the candidate table.
        //(i.e. in WPS or P2P)
        //Memory should be free when connection completes successfully or on errorneous cases (i.e. WPS timeout)
        apSharedInfo->mpCandidateScanResults = os_malloc(maxNumOfCandidates * sizeof(cmeScanCandidateDesc_t));

        if (NULL != apSharedInfo->mpCandidateScanResults)
        {

            // Note: candidate memory is allocated for wpa_scan_res structure + some
            //       IEs taken from beacon/probe response. Supplicant expects these
            //       IEs to follow wpa_scan_res.

            GTRACE(GRP_CME, "CME-SCAN Successful Allocated %d bytes for connection scan results", maxNumOfCandidates * sizeof(cmeScanCandidateDesc_t));
            CME_CON_PRINT( "\n\rCME-SCAN Successful Allocated %d bytes for connection scan results", maxNumOfCandidates * sizeof(cmeScanCandidateDesc_t));

            apSharedInfo->mNumCandidatesMax = maxNumOfCandidates;

            // Allocation succeeded, copy candidates info to gCandidatesInfo
            // and prepare the profiles information.
            // Note: prepareProfileInfo is responsible to free candidates memory in case of failure.
            gCandidatesInfo.pCandidateScanResults = apSharedInfo->mpCandidateScanResults;
            gCandidatesInfo.numAllocatedResults = maxNumOfCandidates;

            // When num_ssids=0 in a supplicant scan request, we don't use profiles
            if (!(gSupplicantInitiatedScanInProgress && (apParams->num_ssids == 0)))
            {
                rc = prepareProfileInfo(apSharedInfo, aScanType, apParams);
            }

            // Set extra probe request IE pointer (used for connection scan only)
            apSharedInfo->mpExtraIesInfo = &gProbeRequestExtraIes_ull;
        }
        else
        {
            GTRACE(GRP_GENERAL_ERROR, "CME-SCAN ERROR, failed to allocated %d bytes for connection scan results", maxNumOfCandidates*sizeof(cmeScanCandidateDesc_t));
            CME_CON_PRINT_ERROR( "\n\rCME-SCAN ERROR, failed to allocated %d bytes for connection scan results", maxNumOfCandidates*sizeof(cmeScanCandidateDesc_t));
            apSharedInfo->mNumCandidatesMax = 0;
            rc = -1;
        }

    }
    // Prepare site survey scan info only for site survey.
    // There's no point to collect scan results if user application isn't going
    // to fetch them.
    else
    {
        scanEntrySize = scanResultTable_GetCmeScanDbPointer()->extendedScanResults ? sizeof(cmeExtendedScanDigestResult_t) : sizeof(cmeScanDigestResult_t);
        ScanMemSize = apSharedInfo->mNumDigestResultsMax * scanEntrySize;

        gSiteSurveyInfo.pSiteNetworks = os_zalloc(ScanMemSize);

        if (NULL == gSiteSurveyInfo.pSiteNetworks)
        {
            GTRACE(GRP_CME, "ERROR, failed to allocate %d bytes for digest scan results", ScanMemSize);
            CME_CON_PRINT_ERROR("\n\rERROR, failed to allocate %d bytes for digest scan results", ScanMemSize);
            apSharedInfo->mNumDigestResultsMax = 0;
            rc = -1;
        }
        else
        {
            CME_CON_PRINT("\n\rCME_SITE_SURVEY_RUNNING, malloc storage for site survey candidate extended results ?:%d",
                    (int32_t)scanResultTable_GetCmeScanDbPointer()->extendedScanResults);
            GTRACE(GRP_CME, "CME_SITE_SURVEY_RUNNING, malloc storage for site survey candidate");

            // Fill shared scan information
            if (FALSE == scanResultTable_GetCmeScanDbPointer()->extendedScanResults)
            {
                apSharedInfo->mpDigestScanResults = (cmeScanDigestResult_t *)gSiteSurveyInfo.pSiteNetworks;
            }
            else
            {
                apSharedInfo->mpDigestExtendedScanResults = (cmeExtendedScanDigestResult_t *)gSiteSurveyInfo.pSiteNetworks;
            }

// TODO need implementation
#if 0
            gSiteSurveyInfo.numValidNetworks = 0;
#endif
            apSharedInfo->mNumDigestResultsFound = 0;

            //zero digest so there wont be mix up with scan types
            apSharedInfo->mOneShotProfiles.mNumProfiles = 0;

            //mark site survey as running
            gSetSiteSurvey = CME_SITE_SURVEY_RUNNING;
        }
    }

    if (0 == rc)
    {
        GTRACE(GRP_CME, "Scan information allocation ready for ENUM(EScanRequestType, %d)", aScanType);
        CME_CON_PRINT("\n\rcmeSetScanCmeInfo:Scan alloc ready for scan type :ENUM(EScanRequestType, %d)\n\r", aScanType);
    }
    else
    {
        GTRACE(GRP_CME, "Scan information could not be fully allocated, scan should not start");
        CME_CON_PRINT("\n\rScan information could not be fully allocated, scan should not start\n\r");
    }

    // Give the sync object to scan module anyway, otherwise system remains stuck for good.
    //osi_SyncObjSignal(apSyncObj);


    return rc;
}

static void cmeScanDoneSendScanDigest(uint32_t aRoleId, CmeScanDoneInfo_t *apScanInfo)
{
    struct wpa_supplicant *wpa_s = NULL;

    {
        // Mark site survey has stopped
        gSetSiteSurvey = CME_SITE_SURVEY_IDLE;

        CME_PRINT_REPORT("\n\rSite survey detected %d networks", apScanInfo->pSharedInfo->mNumDigestResultsFound);
        GTRACE(GRP_CME, "Site survey detected %d networks", apScanInfo->pSharedInfo->mNumDigestResultsFound);
        if(apScanInfo->pSharedInfo->mNumDigestResultsFound == 0)
        {
            //even if nothing found send the scan results,so the app will receive scan complete event
            if (FALSE == apScanInfo->pSharedInfo->extendedScanResults)
            {
                wlanDispatcherSendEvent(WLAN_EVENT_SCAN_RESULT, (void*)NULL, 0);
            }
            else
            {
                wlanDispatcherSendEvent(WLAN_EVENT_EXTENDED_SCAN_RESULT, (void*)NULL, 0);

            }
            goto free;
        }
        uint32_t numNetworks;
        uint32_t bytes2send;
        WlanNetworkEntry_t *pBuff2Send;
        WlanNetworkEntryExtended_t *pBuff2SendExtended;


        if (FALSE == apScanInfo->pSharedInfo->extendedScanResults)
        {
            pBuff2Send = (WlanNetworkEntry_t*) cmeGetScanResults(
                    gSiteSurveyInfo.responseStartIndex,
                    apScanInfo->pSharedInfo->mNumDigestResultsFound, 0,
                    &numNetworks, &bytes2send);

            if(NULL == pBuff2Send)
            {
                ASSERT_GENERAL(0);
            }


            //send internal async event if responseInternalEvent is set
            GTRACE(GRP_CME, "Site survey send internal async event");
            CME_PRINT_REPORT("\n\rSite survey send internal async event");
            wlanDispatcherSendEvent(WLAN_EVENT_SCAN_RESULT, (void*)pBuff2Send, numNetworks);
            os_free(pBuff2Send);
        }
        else
        {
            pBuff2SendExtended = (WlanNetworkEntryExtended_t*) cmeGetScanResults(
                    gSiteSurveyInfo.responseStartIndex,
                    apScanInfo->pSharedInfo->mNumDigestResultsFound, 0,
                    &numNetworks, &bytes2send);



            if(NULL == pBuff2SendExtended)
            {
                ASSERT_GENERAL(0);
            }

            //send internal async event if responseInternalEvent is set
            GTRACE(GRP_CME, "Extended site survey send internal async event");
            CME_PRINT_REPORT("\n\rExtended site survey send internal async event");
            wlanDispatcherSendEvent(WLAN_EVENT_EXTENDED_SCAN_RESULT, (void*)pBuff2SendExtended, numNetworks);
            os_free(pBuff2SendExtended);
        }
    }
free:
    if (gSiteSurveyInfo.pSiteNetworks != NULL)
    {
        os_free(gSiteSurveyInfo.pSiteNetworks);
        gSiteSurveyInfo.pSiteNetworks = NULL;
    }
}

// ----------------------------------------------------------------------------
int cmeScanComplete(uint32_t aRoleId, CmeScanDoneInfo_t *apScanInfo)
{
    HOOK(HOOK_IN_CME_SCAN);

    int rc = 0;
    struct wpa_supplicant *wpa_s = NULL;
    Cme_STA_states_e curretnState;
    cmeScanSharedInfo_t*    pCmeScanDB = scanResultTable_GetCmeScanDbPointer();

    GTRACE(GRP_CME, "CME_SCAN_STATUS_COMPLETE, (roleid=%d) type ENUM(EScanRequestType,%d) status ENUM(cmeScanStatus_e,%d)",
                     aRoleId, apScanInfo->scanType, apScanInfo->status);
    CME_PRINT_REPORT("\n\rCME_SCAN_STATUS_COMPLETE, (roleid=%d) type ENUM(EScanRequestType,%d) status ENUM(cmeScanStatus_e,%d)",
                    aRoleId,apScanInfo->scanType, apScanInfo->status);
    
    if (SCAN_REQUEST_SURVEY_SCAN == apScanInfo->scanType )
    {

        // If scan succeeded (this should always be the case):
        //      o Update supplicant state.
        //        Note that we don't invoke supplicant event handler since this
        //        triggeres a search for better connection candidate.
        //      o Update number of valid networks & scan timestamp
        //        (No need to copy results, they are directly written to CME
        //         allocated memory)
        CME_PRINT_SCAN_REPORT("\r\nCME_MESSAGE_ID_SCAN_COMPLETE, stopping survey scan timer");
        CME_survey_scan_timer_stop();
        cmeScanDoneSendScanDigest(aRoleId, apScanInfo);
    }
    else if ( SCAN_REQUEST_CONNECT_PERIODIC_SCAN == apScanInfo->scanType
            || SCAN_REQUEST_ONE_SHOT == apScanInfo->scanType)
    {
        RoleType_e roleType = drv_getRoleTypeFromRoleId(gpSupplicantGlobals, aRoleId);
        wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, aRoleId);

        GTRACE(GRP_CME, "CME: ScanType=%d, Roletype=%d", apScanInfo->scanType, roleType);
        CME_PRINT_SCAN_REPORT("\n\rcmeScanComplete: ScanType=%d, Roletype=%d", apScanInfo->scanType, roleType);

        curretnState = CmeStationFlow_GetCurrentState();

        if (SCAN_REQUEST_CONNECT_PERIODIC_SCAN == apScanInfo->scanType)
        {
            // clear scan indication on supplicant DB.
            // wpa_supplicant code clears this indication only upon receiving EVENT_SCHED_SCAN_STOPPED,
            // which does not seem to be raised in current implementation.
            wpa_s->sched_scanning = 0;
            CME_periodic_scan_timer_stop();
            set_finish_wlan_periodic_scan();
        }
        else
        {
            CME_PRINT_SCAN_REPORT("\r\nCME_MESSAGE_ID_SCAN_COMPLETE, stopping one shot scan timer");
            CME_one_shot_scan_timer_stop();
            set_finish_wlan_one_shot_scan();
        }

        // When scan complete arrive in stop scan flow
        // In P2P Scenario - scan complete can arrive as part of stop scan (i.e client negotiation failure).
        // In some cases supplicant also removes interface and the scan complete
        // can arrive after the interface is removed.
        // In this case we don't want to handle the scan results 
        if ((wpa_s == NULL) || (roleType == ROLE_TYPE_NONE))
        {
            CME_PRINT_SCAN_REPORT_ERROR("\r\nCME_MESSAGE_ID_SCAN_COMPLETE: driver interface doesn't exist!");
            return -1;
        }

        // External WPS: Perform a different state validation.
        // since ONE SHOT SCAN is usually started with the regular WLAN connect flow.
        //In case role type is Device (P2P) we don't verify the STA state machine,
        //device role managed by supplicant
        // The CME does not handle scans triggered by the supplicant, so no point
        // to check its state in thses cases.
        if (ROLE_IS_TYPE_STA_BASED(roleType))
        {
            if (isextWPS() && isExtWpsScanning())
            {
                if ((curretnState != CME_STA_IDLE_STATE) &&
                        (curretnState !=CME_STA_CONFIGURED_STATE))
                {
                    CME_PRINT_REPORT_ERROR("\n\rcmeScanDone: ERROR! UnExpected event, current state=ENUM(Cme_STA_states_e, %d)",curretnState);
                    GTRACE(GRP_CME_STA_FLOW, "cmeScanDone: ERROR! UnExpected event, current state=ENUM(Cme_STA_states_e, %d)",curretnState);
                    return rc;
                }
            }
            else
            {
                if ((curretnState != CME_STA_SUPPLICANT_MANAGED_STATE) &&
                    (curretnState != CME_STA_DISCONNECTING_STATE) && 
                    (gSupplicantInitiatedScanInProgress != TRUE))
                {
                	CME_PRINT_REPORT("\n\rcmeScanDone: skip on handling scan results due to disconnect or managed state, current state=ENUM(Cme_STA_states_e, %d)",curretnState);
                    GTRACE(GRP_CME_STA_FLOW, "meScanDone: skip on handling scan results , current state=ENUM(Cme_STA_states_e, %d)",curretnState);
                    return rc;
                }
            }
        }

        if (CME_SCAN_STATUS_COMPLETE == apScanInfo->status)
        {
            uint32_t i;

            GTRACE(GRP_CME, "Completed ENUM(EScanRequestType, %d) # candidates %d",
                            apScanInfo->scanType,
                            apScanInfo->pSharedInfo->mNumCandidatesFound);
            CME_PRINT_REPORT("\n\rCompleted ENUM(EScanRequestType, %d) # candidates %d",
                            apScanInfo->scanType,
                            apScanInfo->pSharedInfo->mNumCandidatesFound);

            // Store candidates information here, to be used by driver_cc33 when
            // supplicant retrieves the result
            gCandidatesInfo.numCandidates = apScanInfo->pSharedInfo->mNumCandidatesFound;

            if (0 == gCandidatesInfo.numCandidates)
            {
                //
                // allow X amounts of consequtive scan completes with no candidate found
                // before clearing black list that might preventing from black listed profiles
                // to enter the scan list
                //
                cmeConsequtiveScanCompletesNoCandidate();
            }
            else
            {
                // For STA connection scan, the profile should be set in supplicant DB
                // before scan result is forwarded.
                // One candidate is expected for non-WPS connection, but the implementation
                // is generaic and allows more candidates.
                // For WPS, Don't add any profile to supplicant DB. Let the supllicant to choose by itself from the scan results.
                if (ROLE_IS_TYPE_STA_BASED(roleType))
                {
                    if (!CME_IsOngoingWPSAdHocConnection() && !gSupplicantInitiatedScanInProgress)
                    {
                        for (i=0 ; i<gCandidatesInfo.numCandidates ; ++i)
                        {
                            addProfileIdToSupplicant(&apScanInfo->pSharedInfo->mpCandidateScanResults[i]);

                            // Temp ===================================================
                            // Just for testing the open profile - TODO - have to check if open policy ...
                        // addScanResProfile2Supplicant(&apScanInfo->pSharedInfo->mpCandidateScanResults[i].mScanResult);
                            // Temp ===================================================
                        }
                    }
                } 
            }
            // for p2p device role scan which was initiated by wlan_scan()
            // in that case we want to send results to SCAN RESULTS handler
            if (ROLE_IS_TYPE_DEVICE(roleType))
            {
                ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
                GTRACE(GRP_CME, "Completed p2pFindReportScanResults=%d gP2pSearchStopping=%d,p2pConnectionStarted=%d p2pConnectPending=%d", 
                    pDrv->p2pFindReportScanResults, gCmeP2pInfo.p2pFindStopping,
                    pDrv->p2pConnectionStarted, gCmeP2pInfo.p2pConnectPending);

                CME_PRINT_SCAN_REPORT("\n\rCompleted p2pFindReportScanResults=%d gP2pSearchStopping=%d,p2pConnectionStarted=%d p2pConnectPending=%d",
                    pDrv->p2pFindReportScanResults, gCmeP2pInfo.p2pFindStopping,
                    pDrv->p2pConnectionStarted, gCmeP2pInfo.p2pConnectPending);

                //handle report to host on scan results               
                if ((pDrv->p2pFindReportScanResults)
                    && (gSetSiteSurvey != CME_SITE_SURVEY_IDLE))        
                {
                    cmeScanDoneSendScanDigest(aRoleId, apScanInfo);
                }     
                //if p2p connetion is pending
                if (gCmeP2pInfo.p2pConnectPending != FALSE)
                {
                    rc = 1;
                    gCmeP2pInfo.p2pConnectPending = FALSE;
                }
                //as part of stop find - we report last complete scan 
                //and mark that no more reports are pending
                if ((gCmeP2pInfo.p2pFindStopping != FALSE) 
                    && (pDrv->p2pConnectionStarted == FALSE)
                    && (pDrv->p2pFindReportScanResults != FALSE))
                {
                    pDrv->p2pFindReportScanResults = FALSE;

                    //When stopping p2p find we are expecting for scan complete
                    //to send SCAN_COMPLETE handle event to host
                    //and release sync obj
                    GTRACE(GRP_CME, "Notify host that scan completed for device role");
                    CME_PRINT_SCAN_REPORT("\n\rNotify host that scan completed for device role");
                    wlanDispatcherSendEvent(WLAN_EVENT_P2P_SCAN_COMPLETED, (void*)NULL, 0);
                }
            }

            // scan is completed - clear indication of supplicant scan if set.
            gSupplicantInitiatedScanInProgress = FALSE;
            
            // Notify driver_cc33(supplicant) of scan completion
            drv_handleScanCompleteEvent(wpa_s->drv_priv,
                                        apScanInfo->scanType,
                                        gCandidatesInfo.numCandidates);
            

            // During external WPS scanning the site survery digest table is also populated
            // Send the digest table results to the SCAN RESULTS handler
            if (isextWPS() && isExtWpsScanning())
            {
                cmeScanDoneSendScanDigest(aRoleId, apScanInfo);
            }
 
        } // (CME_SCAN_STATUS_COMPLETE == apScanInfo->status)
        else if ((CME_SCAN_STATUS_STOPPED == apScanInfo->status) || (CME_SCAN_STATUS_FAILED == apScanInfo->status))
        {

            CME_PRINT_REPORT("\r\nStopping scan due to failure, status:%d",apScanInfo->status);

            // scan is completed - clear indication of supplicant scan if set.
            gSupplicantInitiatedScanInProgress = FALSE;

            if(SCAN_REQUEST_CONNECT_PERIODIC_SCAN == apScanInfo->scanType)
            {
                drv_handleScanStoppedEvent(wpa_s->drv_priv);
            }
            else
            {
                //notify wpa supplicant upon stop scan
                drv_handleOneShotScanStoppedEvent(wpa_s,apScanInfo->scanType);

            }
            /* rc must be >0 here, in order to gracefully stop the scan in supplicant and CME */
            rc = 1;
        }

        // Clear external WPS scanning
        if (isextWPS() && isExtWpsScanning())
        {
            extWpsClearScanning();
        }
    }

    return rc;
}

// ----------------------------------------------------------------------------
void cmePushFast2ScanResult(cmeScanCandidateDesc_t *apFastResult)
{
    HOOK(HOOK_IN_CME_SCAN);

    // gCandidatesInfo.pCandidateScanResults is expected to be NULL when
    // starting a new wlan connect
    ASSERT_GENERAL(NULL == gCandidatesInfo.pCandidateScanResults);

    gCandidatesInfo.pCandidateScanResults = os_malloc(sizeof(cmeScanCandidateDesc_t));
    if (NULL == gCandidatesInfo.pCandidateScanResults)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR, failed to allocated memory for duplicating fast candidate");
        CME_PRINT_REPORT_ERROR("\n\rCME: failed to allocated memory for duplicating fast candidate");
        return;
    }

    os_memcpy(gCandidatesInfo.pCandidateScanResults, apFastResult, sizeof(cmeScanCandidateDesc_t));
    gCandidatesInfo.numCandidates = 1;
    gCandidatesInfo.numAllocatedResults = 1;

    GTRACE(GRP_CME, "Fast candidated was successfully duplicated");
    //CME_PRINT_PROFILE_REPORT("\r\nFast candidated was successfully duplicated");

    HOOK(HOOK_IN_CME_SCAN);
}

// ----------------------------------------------------------------------------
void cmeStartSiteSurvey(uint8_t aRoleId, CMEWlanScanCommon_t* pScanCommon)
{
    HOOK(HOOK_IN_CME_SCAN);
    cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();

    if (CME_SITE_SURVEY_IDLE != gSetSiteSurvey)
    {
        GTRACE(GRP_CME,"cmeStartSiteSurvey: ongoing survey scan already running, wait for results");
        return;
    }
    // TODO - when we support getting site survey policy bit from host we have
    // to check it before starting the scan.

    gSetSiteSurvey = CME_SITE_SURVEY_TRIGGERED;
    GTRACE(GRP_CME,"cmeStartSiteSurvey: CME_SITE_SURVEY_TRIGGERED");

    //direct device driver survey scan call, supplicant independent
    if(device_cmd_ops[0]->site_survey(aRoleId, pScanCommon) == 0)
    {
        CME_start_survey_scan_timer();
    }
    else
    {
        //make sure the scan is stopped
        CmeScan_ScanDone(SCAN_REQUEST_SURVEY_SCAN, aRoleId, pCmeScanDB, CME_SCAN_STATUS_FAILED, 0, 0);
    }


    HOOK(HOOK_IN_CME_SCAN);
}

/* ----------------------------------------------------------------------------
// Notes for p2p_find()
// PARAMETERS:   timeout - Timeout for find operation in seconds or 0 for no timeout
//               enum p2p_discovery_type      - Device Discovery Type    
//                             P2P_FIND_START_WITH_FULL, - all channels
//                             P2P_FIND_ONLY_SOCIAL,     - only social channels to be scanned ( 1, 6, 11)
//                             P2P_FIND_PROGRESSIVE      - request a scan of a single channel that the frequency is known
//               num_req_dev_types - Number of requested device types  
//               req_dev_types - Requested device types array, must be an array
//                               containing num_req_dev_types * WPS_DEV_TYPE_LEN bytes; 
//                               %NULL if norequested device types.
//               dev_id - Device ID to search for or %NULL to find all devices
//               search_delay - Extra delay in milliseconds between search iterations
//               seek_count: Number of ASP Service Strings in the seek_string array
//               seek_string: ASP Service Strings to query for in Probe Requests
//               freq: Requested first scan frequency (in MHz) to modify type ==
//               P2P_FIND_START_WITH_FULL behavior. 0 = Use normal full scan.
//               If p2p_find is already in progress, this parameter is ignored and full
//               scan will be executed.
//               include_6ghz: Include 6 GHz channels in P2P find
//----------------------------------------------------------------------------
 cmeStartP2pFind
 
 Description: build a p2p_find() request for supplicant

 Parameters:    wpa_s - driver if
                peer_addr - requested device address to search or NULL to find all
                timeout - Timeout for find operation in seconds or 0 for no timeout
                        if 0 is set - need to stop manually by calling p2p_stop_find()
                reportResult - request to report result to host
 Return code:   none
---------------------------------------------------------------------------- */
#ifndef TI_STA_ONLY_BUILD
void cmeStartP2pFind(struct wpa_supplicant *wpa_s, uint8_t *peer_addr, uint32_t timeout, Bool_e reportResult)
{
    int freq = 0;
    enum p2p_discovery_type p2pScanType = P2P_FIND_START_WITH_FULL;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

    pDrv->p2pFindReportScanResults = reportResult;
    GTRACE(GRP_CME, "CME: call wpas_p2p_find(). reportResult = %d timeout=%d", 
        reportResult, timeout);
    wpas_p2p_find(wpa_s, timeout, p2pScanType, false, NULL, 
                    peer_addr, 0, 0, NULL, freq, false);
}

/* ----------------------------------------------------------------------------
 cmeStopP2pFind
 
 Description: sends p2p_stop_find request to supplicant

 Parameters:    wpa_s - driver if

 Return code:   none
---------------------------------------------------------------------------- */
#endif
#ifndef TI_STA_ONLY_BUILD
void cmeStopP2pFind(struct wpa_supplicant *wpa_s)
{
    struct p2p_data *p2p = NULL;
    uint8_t p2pState = 0xF;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;

    p2p = wpa_s->global->p2p;
    p2pState = p2p->state;
    GTRACE(GRP_CME, "CME: call wpas_p2p_stop_find() wpa_s = %s, p2pState=%d,  wpa_s->state=%d, scanning = %d", 
        wpa_s->ifname, p2pState, wpa_s->wpa_state, wpa_s->scanning);

    //if scan is running 
    if (p2pState == P2P_SEARCH) 
    {
        //send abort p2p find in supplicant
        wpas_p2p_stop_find(wpa_s);

        //stop scan in FW (before complete Event)
        pDrv->ops->send_scan_stop(pDrv->roleId, SCAN_REQUEST_ONE_SHOT, TRUE);
        
        //cancel scan work if pending
        if (radio_work_pending(wpa_s, "p2p-scan"))
        {
            GTRACE(GRP_DRIVER_CC33_DEBUG, "Pending p2p-scan work - Remove it...");

            radio_remove_works(wpa_s, "p2p-scan", 0);
        }
    }
    else
    {
        //not in scanning
        //signal host that scan completed
        GTRACE(GRP_CME, "Notify host that scan completed for device role");
        wlanDispatcherSendEvent(WLAN_EVENT_P2P_SCAN_COMPLETED, (void*)NULL, 0);
    }
}
#endif


#if 0

call issueOneShotScan in R2
---------------------
wpa_supplicant_restart_application_scan:
ApplyScanPolicy
setAppScanPolicy
setUserAppScanPolicy
wpa_supplicant_event_scan_complete

host command -> performSingleScan -> wpa_supplicant_perform_single_application_scan
EVENT_SCAN_PERIODIC_COMPLETE -> wpa_supplicant_event_scan_periodic_cycle_complete -> wpa_supplicant_restart_application_scan/ApplyScanPolicy

#endif

// ----------------------------------------------------------------------------
void CME_SetProbeRequestIes(uint32_t aLen, uint8_t *apBuff)
{
    HOOK(HOOK_IN_CME_SCAN);

    if (aLen<=MAX_EXTRA_IES_LEN)
    {
        gProbeRequestExtraIes_ull.pExtraIesBuffer = os_malloc (aLen); //retention in scan process
        if (gProbeRequestExtraIes_ull.pExtraIesBuffer)
        {
            gProbeRequestExtraIes_ull.extraIesLength = aLen;
            memcpy(gProbeRequestExtraIes_ull.pExtraIesBuffer, apBuff, aLen);
        }
        else
        {
            gProbeRequestExtraIes_ull.extraIesLength = 0;
        }
    }
    else
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR, probe request extraIEs is too long");
        gProbeRequestExtraIes_ull.extraIesLength = 0;
    }

    HOOK(HOOK_IN_CME_SCAN);
}

// ----------------------------------------------------------------------------
//ProbeRequestInfo_t * CME_GetProbeRequestIes(uint32_t aBufferLenegth)
//{
//    uint8_t *pExtraIesBuff;
//
//    if (0 == aBufferLenegth)
//        return NULL;
//
//    if (gProbeRequestExtraIes_ull.extraIesLength < aBufferLenegth)
//    {
//        mem_Free_ull(gProbeRequestExtraIes_ull.pExtraIesBuffer);
//        gProbeRequestExtraIes_ull.pExtraIesBuffer = NULL;
//        gProbeRequestExtraIes_ull.extraIesLength = 0;
//    }
//
//    if (NULL == gProbeRequestExtraIes_ull.pExtraIesBuffer)
//    {
//        pExtraIesBuff = mem_Zalloc_ull(aBufferLenegth);
//        if (NULL != pExtraIesBuff)
//        {
//            gProbeRequestExtraIes_ull.extraIesLength = aBufferLenegth;
//            gProbeRequestExtraIes_ull.pExtraIesBuffer = pExtraIesBuff;
//        }
//        else
//        {
//            GTRACE(GRP_GENERAL_ERROR, "ERROR: failed to allocate memory for extra IEs");
//        }
//    }
//
//    return &gProbeRequestExtraIes_ull;
//}

// ----------------------------------------------------------------------------
void CME_ReleaseScanResults(uint32_t aCaller)
{
    HOOK(HOOK_IN_CME_SCAN);

    GTRACE(GRP_CME_DEBUG,"CME_ReleaseScanResults, gCandidatesInfo.pCandidateScanResults=0x%x (caller=%d)",
                            (uint32_t)gCandidatesInfo.pCandidateScanResults, aCaller);
//    Report("\n\r CME_ReleaseScanResults, gCandidatesInfo.pCandidateScanResults=0x%x (caller=%d)",
//                           (uint32_t)gCandidatesInfo.pCandidateScanResults, aCaller);
    if (gCandidatesInfo.pCandidateScanResults != NULL)
    {
        os_free(gCandidatesInfo.pCandidateScanResults);
        gCandidatesInfo.pCandidateScanResults = NULL;
    }

    gCandidatesInfo.numCandidates = 0;
    gCandidatesInfo.numAllocatedResults = 0;
}

cmeScanCandidateDesc_t * CME_FindBssidInCandidatesScanTable (const uint8_t *bssid)
{
    HOOK(HOOK_IN_CME_SCAN);

    cmeScanCandidateDesc_t *pCandidateDesc = NULL;
    uint8_t  i;
    volatile uint8_t   numOfCandidates;
    char    macStr[MAC_STR_LEN] = {0};

    numOfCandidates = gCandidatesInfo.numCandidates;

    GET_MAC_STR(bssid, macStr);

    //Find the target network in the candidates table
    for (i=0 ; i<numOfCandidates ; i++)
    {
        if (IRQ_UtilCompareMacAddress(gCandidatesInfo.pCandidateScanResults[i].mScanResult.bssid, bssid))
        {
            pCandidateDesc = &gCandidatesInfo.pCandidateScanResults[i];
            GTRACE(GRP_DRIVER_CC33, "Search scan candidates - Candidate found in scan table: BSSID %s, table entry %d", macStr, i);
            break;
        }
    }

    HOOK(HOOK_IN_CME_SCAN);

    if (NULL == pCandidateDesc)
    {
        GTRACE(GRP_GENERAL_ERROR, "WARNING: can't find candidate in scan table: BSSID %s",  macStr);
        CME_PRINT_REPORT("\r\nWARNING: can't find candidate in scan table: BSSID %s",  macStr);
    }

    return (pCandidateDesc);
}

////   Survey  scan

void CME_start_survey_scan_timer()
{
    int32_t ret;
    if( gTimerSiteSurveyComplete.osTimerHandler == NULL)
    {
        osi_TimerCreate(&gTimerSiteSurveyComplete, "Survey scan complete timeout", CME_survey_scan_timeout, NULL);
        ret = osi_TimerStart(&gTimerSiteSurveyComplete, CME_SURVEY_SCAN_TIMEOUT  , FALSE);
        if(ret < 0)
        {
            CME_PRINT_REPORT_ERROR("\n\rCME: survey scan timer started failed");
        }
    }
    else
    {
        CME_PRINT_REPORT_ERROR("\n\rCME: error survey scan timer already started !!!");
    }

}

void CME_survey_scan_timeout()
{
    cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();
    //CME_PRINT_REPORT_ERROR("\n\rCME: timeout for survey scan !!");
    CmeScan_ScanDone(SCAN_REQUEST_SURVEY_SCAN, pCmeScanDB->roleId, pCmeScanDB, CME_SCAN_STATUS_FAILED, 1, 1);
}

void CME_survey_scan_timer_stop()
{
    int32_t ret;
    if(gTimerSiteSurveyComplete.osTimerHandler != NULL)
    {
        ret = osi_TimerStop(&gTimerSiteSurveyComplete);
        if(ret < 0)
        {
            CME_PRINT_REPORT_ERROR("\n\rCME: survey scan timer stop failed");
        }
        osi_TimerDelete(&gTimerSiteSurveyComplete);
    }
    else
    {
        CME_PRINT_REPORT_ERROR("\n\rCME: survey scan timer was not started");
    }
    gTimerSiteSurveyComplete.osTimerHandler = NULL;

}

////////////////////////////////////////////////////////////////////////////////////
////   one shot connection  scan
/////////////////////////////////////////////////////////////////////////////////
void CME_start_one_shot_scan_timer()
{
    int32_t ret;
    if( gTimerOneShotScanComplete.osTimerHandler == NULL)
    {
        osi_TimerCreate(&gTimerOneShotScanComplete, "One shot scan complete timeout", CME_one_shot_scan_timeout, NULL);
        ret = osi_TimerStart(&gTimerOneShotScanComplete, CME_ONE_SHOT_SCAN_TIMEOUT  , FALSE);
        if(ret < 0)
        {
            CME_PRINT_REPORT_ERROR("\n\rCME: one shot scan timer started failed");
        }
    }
    else
    {
        CME_PRINT_REPORT_ERROR("\n\rCME: error one shot scan timer already started !!!");
    }

}

void CME_one_shot_scan_timeout()
{
    cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();
    //CME_PRINT_REPORT_ERROR("\n\rCME: timeout for one shot scan !!");
    CmeScan_ScanDone(SCAN_REQUEST_ONE_SHOT, pCmeScanDB->roleId, pCmeScanDB, CME_SCAN_STATUS_FAILED, 1, 1);
}

void CME_one_shot_scan_timer_stop()
{
    int32_t ret;
    if(gTimerOneShotScanComplete.osTimerHandler != NULL)
    {
        ret = osi_TimerStop(&gTimerOneShotScanComplete);
        if(ret < 0)
        {
            CME_PRINT_REPORT_ERROR("\n\rCME: one shot scan timer stop failed");
        }
        osi_TimerDelete(&gTimerOneShotScanComplete);
    }
    else
    {
        CME_PRINT_REPORT_ERROR("\n\rCME: one shot scan timer was not started");
    }
    gTimerOneShotScanComplete.osTimerHandler = NULL;

}

////////////////////////////////////////////////////////////////////////////////////
////   periodic connection  scan
/////////////////////////////////////////////////////////////////////////////////
void CME_start_periodic_scan_timer()
{
    int32_t ret;
    if( gTimerPeriodicScanComplete.osTimerHandler == NULL)
    {
        osi_TimerCreate(&gTimerPeriodicScanComplete, "Periodic scan complete timeout", CME_periodic_scan_timeout, NULL);
        ret = osi_TimerStart(&gTimerPeriodicScanComplete, CME_PERIODIC_SCAN_TIMEOUT  , FALSE);
        if(ret < 0)
        {
            CME_PRINT_REPORT_ERROR("\n\rCME: periodic scan timer started failed");
        }
    }
    else
    {
        CME_PRINT_REPORT_ERROR("\n\rCME: error periodic scan timer already started !!!");
    }

}

void CME_periodic_scan_timeout()
{
    cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();
    //CME_PRINT_REPORT_ERROR("\n\rCME: timeout for periodic scan !!");
    CmeScan_ScanDone(SCAN_REQUEST_CONNECT_PERIODIC_SCAN, pCmeScanDB->roleId, pCmeScanDB, CME_SCAN_STATUS_FAILED, 1, 1);
}

void CME_periodic_scan_timer_stop()
{
    int32_t ret;
    if(gTimerPeriodicScanComplete.osTimerHandler != NULL)
    {
        ret = osi_TimerStop(&gTimerPeriodicScanComplete);
        if(ret < 0)
        {
            CME_PRINT_REPORT_ERROR("\n\rCME: periodic scan timer stop failed");
        }
        osi_TimerDelete(&gTimerPeriodicScanComplete);
    }
    else
    {
        CME_PRINT_REPORT_ERROR("\n\rCME: periodic scan timer was not stated");
    }
    gTimerPeriodicScanComplete.osTimerHandler = NULL;

}

