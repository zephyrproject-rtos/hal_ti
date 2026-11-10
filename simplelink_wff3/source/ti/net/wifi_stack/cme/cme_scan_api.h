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

  FILENAME:       cme_scan_api.h

  DESCRIPTION:    This files defines the API between CME and scan concentrator,

  HISTORY:
                 03/154 - Creation

  ----------------------------------------------------------------------------- */
#ifndef _CME_SCAN_API_H_
#define _CME_SCAN_API_H_

#include <cc3xxx_public_types.h>
#include "802_11defs.h"
#include <osi_kernel.h>
#include "common.h"
#include "drivers/driver.h"
#include "cme_defs.h"
#include "wlan_if.h"

/*=============================================================================
	Type Definitions
=============================================================================*/

#define SCAN_MAX_CHANNELS_BG  14
#define SCAN_MAX_CHANNELS_J    4
#define SCAN_MAX_CHANNELS_A   32
#define SCAN_MAX_CHANNELS_ALL_BANDS        ((SCAN_MAX_CHANNELS_BG) + (SCAN_MAX_CHANNELS_A) + (SCAN_MAX_CHANNELS_J))

#define SCAN_MAX_CHANNELS_NUM 60


#define PERIODIC_SCAN_MAX_NUM_OF_CYCLES_INTERVALS   (16)        /* Maximum number of configured inter-cycle intervals */

// Note that there is a difference between number of channels for one shot and
// periodic scan. This behavior is inherited from WL8 as its reason is unknown.
#define PERIODIC_SCAN_MAX_CHANNEL_NUM                       (37) /* G-14 + A-24 */

//TODO:  - to remove...
#define INFINITE_PERIODIC_SCAN_NUM_CYCLES                   (0)

// List of BG & A channels, to be used for scan in case supplicant hasn't set scan channels.
// Scan always starts from social channels.
#define PERIODIC_SCAN_CHANNELS_ARRAY_B_G_BAND               {1,6,11,2,3,4,5,7,8,9,10,12,13}
#define PERIODIC_SCAN_CHANNELS_ARRAY_A_BAND                 {36,40,44,48,52,56,60,64,100,104,\
                                                             108,112,116,120,124,128,132,136,\
                                                             140,144,149,153,157,161,165}
#define PERIODIC_SCAN_CHANNELS_ARRAY_B_G_A_BAND             {1,6,11,2,3,4,5,7,8,9,10,12,13,14,36,40,44,48,\
                                                             52,56,60,64,100,104,108,112,116,120,124,128,\
                                                             132,136,140,144,149,153,157,161,165}

#define CME_P2P_CONNECTION_FIND_TIMEOUT      (60)
#define CME_P2P_DISCOVERY_FIND_TIMEOUT       (60)

typedef enum
{
    CME_SCAN_STATUS_COMPLETE,     // Scan ended either due to early termination condition or since all channels/cycles were exhausted
    CME_SCAN_STATUS_STOPPED,      // Relevant only for periodic scan, acknowledge a stop periodic scan command
    CME_SCAN_STATUS_FAILED        // In case scan wasn't even started; should never occur
} cmeScanStatus_e;


// forward declaration
struct wpa_scan_res;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP

//typedef struct {
//    uint32_t flags;
//    uint8_t bssid[MAC_ADDR_LEN];
//    int32_t freq;
//    uint16_t beacon_int;
//    uint16_t caps;
//    int32_t qual;
//    int32_t noise;
//    int32_t level;
//    uint64 tsf;
//    uint32_t age;
//    uint32_t/*size_t*/ ie_len;
//    uint32_t/*size_t*/ beacon_ie_len;
//    /*
//     * Followed by ie_len octets of IEs from Probe Response frame (or if
//     * the driver does not indicate source of IEs, these may also be from
//     * Beacon frame). After the first set of IEs, another set of IEs may
//     * follow (with beacon_ie_len octets of data) if the driver provides
//     * both IE sets.
//     */
//} wpa_scan_res;

//  TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//profiles to search during scan. this list consider profiles which are in blacklist
//and they will not be at the profiles list)
typedef struct
{
    uint8_t       mSSID[DOT11_SSID_MAX_LEN];
    struct
    {
        uint32_t        mPriority   : 8  ;     // bits[7  :  0]
        uint32_t        mSsidLen    : 7  ;     // bits[14 :  7]
        uint32_t        mHidden     : 1  ;     // bit [15 : 14] = "1" ==> hidden profile
    } ssid;
    uint8_t       secType;
    uint8_t       mBssid[MAC_ADDR_LEN];
    int8_t        mProfileId;
} cmeScanProfiles_t;

typedef struct
{
    //WlanNetworkEntry_t
    uint8_t       mSSID[DOT11_SSID_MAX_LEN];
    uint8_t       mBssid[MAC_ADDR_LEN];
    uint8_t       mSsidLen;
    int8_t        mRSSI;
    uint32_t      mSecurityType;
    uint8_t       mChannel;
}cmeNetworkEntryResult_t;




typedef struct
{
    //WlanNetworkEntry_t
    uint8_t       mSSID[DOT11_SSID_MAX_LEN];
    uint8_t       mBssid[MAC_ADDR_LEN];
    uint8_t       mSsidLen;
    int8_t        mRSSI;
    uint32_t      mSecurityType;
    uint8_t       mChannel;

    uint16_t       mRatesLen;//Rates
    uint8_t        mRates[DOT11_MAX_SUPPORTED_RATES + WLAN_LEN_OF_IE_HEADER];

    uint16_t      HtCapabilitiesLen;     // HT capabilities IE were received
    uint8_t       HtCapabilitiesIe[DOT11_HT_CAPABILITIES_ELE_LEN + WLAN_LEN_OF_IE_HEADER];   /* HT capabilities IE unparsed */

    uint16_t      erpIeLen;     // HT capabilities IE were received
    uint8_t       erpIe[WLAN_DOT11_ERP_ELE_LEN + WLAN_LEN_OF_IE_HEADER];
    Bool_e        mErpPresent;
    uint8_t       mUseProtection; //erp capabilities
    uint8_t/*EPreamble*/    mBarkerPreambleMode; //erp capabilities

    uint8_t       rsnIeLen;//the len includes the header
    uint8_t       rsnIeData[DOT11_MAX_RSNE_SIZE + WLAN_LEN_OF_IE_HEADER];

    uint8_t       wpaIeLen;
    uint8_t       wpaIe[DOT11_MAX_RSNE_SIZE + WLAN_LEN_OF_IE_HEADER];

    uint16_t      wpsLen;
    uint8_t       wpsIeData[DOT11_MAX_WPSIE_SIZE + WLAN_LEN_OF_IE_HEADER];
    Bool_e        wpsPresent;

    uint16_t       beaconInterval;
    uint16_t       capabilities;

}cmeNetworkExtendedEntryResult_t;

typedef struct
{
    cmeNetworkEntryResult_t result;
    uint32_t      mScore;
} cmeScanDigestResult_t;

typedef struct
{
    cmeNetworkExtendedEntryResult_t result;
    uint32_t      mScore;
} cmeExtendedScanDigestResult_t;



// Candidate information, include a pointer to processed scan result, IEs and score.
// The information is filled from scan context when a new detected network is
// selected as candidate. It is handed to supplicant from get_scan_results2.
// The score field is added only for convinience; it is used during scan results
// handling for candidates selection.
typedef struct
{
    struct wpa_scan_res     mScanResult;
    uint8_t                 mInfoElements[MAX_BEACON_BODY_LENGTH];
    int8_t                  mProfileId;
    uint32_t                mScore;
    Bool_e                  mHtCapabilitiesPresent;     // HT capabilities IE were received
    Bool_e                  mHtInformationPresent;      // HT information IE was received

    Bool_e                  mVhtCapabilitesPresent;

    Bool_e                  pbacApEnabled;              // PBAC (protected block ack agreement capable). A STA sets the PBAC subfield of RSN
                                                        // Capabilities field to 1 to indicate it is PBAC. Otherwise, this subfield is set to 0.

    Bool_e                  mHeCapabilitiesPresent;     // HE capabilities IE were received
    Bool_e                  mHeOperationPresent;      // HE information IE was received

    Bool_e                  wmmIePresent;           // Wmm IE

    Bool_e                  mbssidIndicator; 
    Bool_e                  mbssidIndex; 
    Bool_e                  nonTransmittingBssid; 
    uint8_t                 transmittingBssid[MAC_ADDR_LEN];
} cmeScanCandidateDesc_t;

typedef struct
{
    uint8_t                   mNumProfiles;
    cmeScanProfiles_t       *mpProfiles;
} cmeScanProfilesParams_t;

typedef struct
{
    // Pointer to memory allocated for scan results in digest format.
    // Scan results are stored directly on this memory when a new probe
    // response packet is received.

    cmeScanDigestResult_t           *mpDigestScanResults;//relevant for survey scan only

    cmeExtendedScanDigestResult_t   *mpDigestExtendedScanResults;//relevant for survey scan only

    // Pointer to memory allocated for candidates scan results.
    // Candidates information is stored directly on this memory.
    cmeScanCandidateDesc_t  *mpCandidateScanResults;//connection scan only (one shot and periodic)

    // Extra IEs as received from suppicant, used to construct probe request
    ProbeRequestInfo_t      *mpExtraIesInfo;//shared for all scan types

    // Set from CME context to maximal number of scan results (CME_SCAN_MAX_DIGEST_RESULTS)
    uint16_t                  mNumDigestResultsMax;//relevant for survey scan only

    // Set from CME context to 0
    // Set from scan context to actual number of digest scan results (<= CME_SCAN_MAX_DIGEST_RESULTS)
    uint16_t                  mNumDigestResultsFound;//relevant for survey scan only

    // Set from CME context to maximal number of candidates (CME_SCAN_MAX_CANDIDATES)
    uint16_t                  mNumCandidatesMax;//for connection scan types (one shot and periodic)

    // Set from CME context to 0
    // Set from scan context to actual number of candidates (<= CME_SCAN_MAX_CANDIDATES)
    uint16_t                  mNumCandidatesFound;//for connection scan types (one shot and periodic)

    // Preferred networks (i.e. profiles) - list & number.
    // Filled by CME before starting a new scan cycle.
    // Used by scan SW for candidates selection.
    // As one shot and periodic scans may run concurrently, two lists are managed.
    cmeScanProfilesParams_t mOneShotProfiles;//relevant for all one shot - survey + connection
    cmeScanProfilesParams_t mPeriodicProfiles;//relevant for periodic scan only (connection scan)

    uint16_t                  mIsOpenProfileSupported;    //1 = supported
    uint8_t                   mIsProfileListExist;        //1 = profile list exist

    //CC33XX - add rssi/score thresholds
    int32_t mRssiEarlyTermThreshold; //if RSSI  value is >= this threshold, early terminate scan. 0 means dont care
    int32_t mScoreEarlyTermThreshold;//if Score value is >= this threshold, early terminate scan. 0 means dont care

    Bool_e ETexceeded;         /* indicates that report because of ET sent by the host */

    uint8_t   roleId;            /* role id */

    uint8_t wifi_band_cfg; /* supported band for specific roleId,  DOT11_BAND_ONLY_2_4GHZ = 0 , DOT11_BAND_ONLY_5GHZ = 1, DOT11_BAND_BOTH = 2,*/

    Bool_e extendedScanResults;
    //
} cmeScanSharedInfo_t;

/** \struct scanParams_t
 * \brief scan operation parameters
 *
 * \par Description
 * This structure defines parameters for a one shot scan operation
 *
 * \sa
 */
typedef struct
{
    uint8_t    numOfGChannels;       /**< Number of channels to scan                                                     */
    uint8_t    numOfAChannels;       /**< Number of channels to scan                                                     */
    uint8_t    channels_BG[ SCAN_MAX_CHANNELS_BG ];   /**< Channel data array, actual size according to the above field. */
    uint8_t    channels_A[ SCAN_MAX_CHANNELS_A ];     /**< Channel data array, actual size according to the above field. */
    uint8_t/*scanResultsFilterCfg_e*/   scanResultsFilterCfg;
} oneShotScanParams_t;



/** \struct periodicScanParams_t
 * \brief Periodic Scan Parameters
 *
 * \par Description
 * This structure defines all the parameters of Periodic scan
 *
 * \sa
 */
typedef struct
{
    struct sched_scan_plan *sched_scan_plans;   //Scan plans for scheduled scan (defined in supplicant's driver.h)
    uint16_t sched_scan_plans_num;                //Number of scan plans in sched_scan_plans array


    uint8_t                numOfGChannels;       /**< Number of channels to scan                                                      */
    uint8_t                numOfAChannels;       /**< Number of channels to scan                                                      */
    uint8_t                channels_BG[ SCAN_MAX_CHANNELS_BG ];    /**< Channel data array, actual size according to the above field. */
    uint8_t                channels_A[ SCAN_MAX_CHANNELS_A ];    /**< Channel data array, actual size according to the above field.   */
} periodicScanParams_t;


typedef struct
{
    union
    {
        oneShotScanParams_t     tScanInfo;
        periodicScanParams_t    tConnScanInfo;
    } u;
} scanRequestParams_t;



/* ----------------------------------------------------------------------------
    CmeScan_SetProfilesAndResultsMem
    This function pushes a message with request to fill the shared information
    structure into CME message queue.

 Parameters:
      IN apSharedInfo - pointer to a structure allocatrd by scan concentrator;
                        filled by CME to be used for handling scan results.
      IN apSyncObj    - pointer to sync obect that should be signaled once
                        request is processed.
      IN aScanReqType - scan type request
 Return code:	0 - in success, -1 - memory allocation failed

 ---------------------------------------------------------------------------- */
int32_t CmeScan_SetProfilesAndResultsMem(cmeScanSharedInfo_t *apSharedInfo,
									   OsiSyncObj_t		   *apSyncObj,
									   EScanRequestType     aScanReqType);

/* ----------------------------------------------------------------------------
    CmeScan_ScanDone
    This function pushes a message indicating scan completion into CME message
    queue. The message includes scan tag, pointer to shared information.
    Once this API is called, scan concentrator must not access the pointer.

 Parameters:
 	  IN aScanReqType - type of completed scan, describes scan type and reason
 	                    to send the event
 	  IN aNetIf       - Network interface indentifier
      IN apSharedInfo - pointer to a structure allocatrd by scan concentrator;
                        filled by CME to be used for handling scan results.
      IN aStatus      - indicate how scan was ended (normally, stopped, by error)
      IN fromIntr     - indicates if called from interrupt context
      IN fromTimeout  - indicates if the scan ended due to a timeout
 Return code:	0 - in success, -1 - memory allocation failed

 ---------------------------------------------------------------------------- */
int32_t CmeScan_ScanDone(EScanRequestType aScanReqType,
                       uint32_t           aNetIf,
                       cmeScanSharedInfo_t *apSharedInfo,
                       cmeScanStatus_e  aStatus,
                       uint8_t   fromIntr,
                       uint8_t   fromTimeout);

/* ----------------------------------------------------------------------------
    CmeScan_ScanPeriodDone
    This function pushes a message indicating scan period completion into CME message
    queue. The message includes scan type, role ID and scan period number.

 Parameters:
      IN aRoleId      - Role ID
      IN apSharedInfo - pointer to a structure allocatrd by scan concentrator;
                        filled by CME to be used for handling scan results.
      IN aStatus      - indicate how scan was ended (normally, stopped, by error)
 Return code:   0 - in success, -1 - failure in pushing the message to CME message queue

 ---------------------------------------------------------------------------- */
int32_t CmeScan_ScanPeriodDone(uint32_t  aRoleId,
                             cmeScanSharedInfo_t *apSharedInfo,
                             cmeScanStatus_e  aStatus);

/* ----------------------------------------------------------------------------
    CmeScan_GetExtraIes
    This function is used to retrieve the Extra IE's for scan procedure /
    out of scan procedure. the Extra IE's are attached to the probe request
    sent by the device.
    Note: the operation is done in the caller context.

 Parameters:
      IN aRoleId            - Role ID, used to access the right wpa_supplicant instance
      IN aInputBufferLength - length of the attached buffer to fill. used to make
                              sure that the IE's are not larger than the buffer.

      OUT apExtraIesLength  - The actual length of the Extra IE's written into
                                 the buffer.
      IN/OUT apExtraIes     - buffer to fill the Extra IE's.
 Return code:   none

 ---------------------------------------------------------------------------- */
void CmeScan_GetExtraIes(uint32_t aRoleId,
                         uint16_t aInputBufferLength,
                         uint16_t *apExtraIesLength,
                         uint8_t  *apExtraIes);


/* ---------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------- */


/* ----------------------------------------------------------------------------
    cmeScan_store_scan_dwell_times
    This function is used to store the scan dwell times in the cme_scan module 

 Parameters:
      IN WlanScanDwellTime_t            - dwellTimeParams , scan dwell times
 Return code:   none

 ---------------------------------------------------------------------------- */
void cmeScan_store_scan_dwell_times(WlanScanDwellTime_t dwellTimeParams);

#endif // _CME_SCAN_API_H_
