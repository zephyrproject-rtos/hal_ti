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
/** \file  scan_result_table.h
 *  \brief declarations for a table holding scan results, by BSSID
 *
 *  \see   scan_result_table.c
 */


#ifndef __SCAN_RESULT_TABLE_H__
#define __SCAN_RESULT_TABLE_H__

#include "cme_defs.h"
#include "rates.h"
#include "mlme_parser.h"
#include "802_11defs.h"
#include "cme_scan_api.h"

// scan_result defines for weights
#define SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG1         ( -30 ) // above this value is a good link first degredation - full score
#define SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG2         ( -35 ) // above this value is a good link second degredation
#define SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG3         ( -40 ) // above this value is a good link third degradation
#define SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG4         ( -45 ) // above this value is a good link fourth degradation
#define SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG5         ( -50 ) // above this value is a good link fifth degradation
#define SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG6         ( -55 ) // above this value is a good link sixth degradation
#define SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG7         ( -60 ) // above this value is a good link seven degradation
#define SCAN_RESULT_RSSI_THRESHOLD_DEG1              ( -65 ) // first degredation
#define SCAN_RESULT_RSSI_THRESHOLD_DEG2              ( -70 ) // second degredation
#define SCAN_RESULT_RSSI_THRESHOLD_DEG3              ( -75 ) // third degradation
#define SCAN_RESULT_RSSI_THRESHOLD_DEG4              ( -80 ) // fourth degradation
#define SCAN_RESULT_RSSI_THRESHOLD_DEG5              ( -85 ) // fifth degradation
#define SCAN_RESULT_RSSI_THRESHOLD_WORST_DEG1        ( -90 ) // worst threshold first degredation
#define SCAN_RESULT_RSSI_THRESHOLD_WORST_DEG2        ( -95 ) // worst threshold second degredation
#define SCAN_RESULT_RSSI_THRESHOLD_WORST_DEG3        ( -100) // worst threshold third degradation
#define SCAN_RESULT_RSSI_THRESHOLD_NOT_VALID         ( -127) // more degradation

// rssi extracting from frame
#define RSSI_LEVEL_BITMASK	0x7F
#define EXTRACT_RSSI(rssi) ((rssi & RSSI_LEVEL_BITMASK) | BIT(7))


typedef uint8_t ScanTag_t;
/* site types */
typedef enum
{
    SITE_PRIMARY        = 0,
    SITE_SELF           = 1,
    SITE_REGULAR        = 2,
    SITE_NULL           = 3
} siteType_e;

/** \struct TScanFrameInfo
 * \brief Scan Fram Information
 *
 * \par Description
 * This structure contains a single frame information, returned by the result CB when a frame is available.
 * It is used to pass scan results (beacons and probe responses).
 *
 * \sa
 */
typedef struct
{
    uint8_t*                    pBssId;              /* BSSID (MAC address) of the AP from which the frame was received */
    uint64_t                    uTtsfOffset;         /* TSF offset between device free running and AP TSF */
    scanIEParsingParams_t*      pParsedIEs;          /* Information elements in the frame, which is parsed */
    uint8_t/*RadioBand_e*/      eBand;               /* Band on which the frame was received */
    uint8_t                     uChannel;            /* Channel on which the frame was received */
    int8_t                      iRssi;               /* RSSI level at which frame was received */
    int8_t                      iSnr;                /* SNR level at which frame was received */
    uint8_t/*RateIndex_e*/      eRate;               /* Bitrate at which frame was received */
    uint8_t                     *pBuffer;            /* Frame information elements, unparsed */
    uint16_t                    uBufferLength;       /* Length of the frame unparsed information elements */
} TScanFrameInfo;

//typedef enum
//{
//    BEACONS_POOL_LARGE           = 0,
//    BEACONS_POOL_STANDARD        = 1,
//    BEACONS_POOL_NULL            = 2
//
//}EBeaconPoolType;


//typedef struct
//{
//    /* The following fields are used for entry management at the SiteMng */
//    uint8_t                   index;
//    siteType_e                 siteType;
//    uint32_t                  localTimeStamp;
//    /* end of fields  are used for entry management at the SiteMng */
//
////    TI_BOOL                    bConsideredForSelect;
////    ERadioBand                 eBand;
//    uint8_t                   tsfTimeStamp[ TIME_STAMP_LEN ];
//
//    /* The following fields are used for the selection */
//    TI_BOOL                    probeRecv;
//    TI_BOOL                    beaconRecv;
//    TMacAddr                   bssid;
//    TSsid                      ssid;
//    ScanBssType_e              bssType;
////    TRateSets	               rateMask;
////    tiwdrv_rate_e              maxBasicRate;
////    tiwdrv_rate_e              maxActiveRate;
////    EModulationType            beaconModulation;
////    EModulationType            probeModulation;
////    EPreamble                  currentPreambleType;
////    EPreamble                  preambleAssRspCap;
////    EPreamble                  barkerPreambleType;
////    ESlotTime                  currentSlotTime;
////    ESlotTime                  newSlotTime;
//    TI_BOOL                    useProtection;
//    TI_BOOL                    NonErpPresent;
//    uint8_t                   channel;
//	/* 40MHz support - add channel type */
////    BandWidthSettings_e        channelType;
//    TI_BOOL                    privacy;
//    TI_BOOL                    agility;
//    uint16_t                  capabilities;
//    uint16_t                  beaconInterval;
//    uint8_t                   dtimPeriod;
//    TI_INT8                    snr;
////    tiwdrv_rate_e              rxRate;
//    TI_INT32                   rssi;
//
//    /* HT capabilites */
//	Tdot11HtCapabilitiesUnparse tHtCapabilities;
//	/* HT information */
//    TI_BOOL                     bHtInfoUpdate;
//	Tdot11HtInformationUnparse  tHtInformation;
//
//    /* QOS */
//    TI_BOOL                    WMESupported;
//    dot11_ACParameters_t       WMEParameters;
//    uint8_t                   lastWMEParameterCnt;
//
//    /* Power Constraint */
//    uint8_t                   powerConstraint;
//
//    /* AP Tx Power obtained from TPC Report */
//    uint8_t                   APTxPower;
//
//    /* UPSD */
//    TI_BOOL                    APSDSupport;
//
//    /* WiFi Simple Config */
////    TIWLN_SIMPLE_CONFIG_MODE   WSCSiteMode; /* indicates the current WiFi Simple Config mode of the specific site*/
//
//    uint16_t                  atimWindow;
//    dot11_RSN_t                pRsnIe[MAX_RSN_IE];
//    uint8_t                   rsnIeLen;
//    /* 80211h beacon  - Switch Channel IE included */
//    TI_BOOL                    bChannelSwitchAnnoncIEFound;
//    TI_BOOL                    bP2PDEviceMgmtPresent;
//    uint8_t                   *pBuf;          /* pointer to buffer to hold beacon */
//    uint16_t                  frameLength;    /* frame length */
//    uint8_t                   elmntIdxInPool; /* index of element inside pool, holding the buf */
////    EBeaconPoolType            poolTypeInUse;  /* indicates type of pool used for specific site */
//
//    mgmtStatus_e               failStatus;
//    TI_BOOL                    prioritySite;
//
//
//    uint8_t                   RRMEnabledCapabilities[5];
//
//    /* 802.11r - mobility domain information */
////    mobilityDomain_t mobilityDomain;
//
//} TSiteEntry;

typedef struct
{
    cmeScanSharedInfo_t     cmeScanDb;

    uint32_t                   digestLowestScore;           /**<  lowest score in the digest table */
    uint32_t                   digestLowestScoreIndex;      /**<  index of lowest score in the digest table */

    uint32_t                   candidateLowestScore;        /**<  lowest score in the candidate table */
    uint32_t                   candidateLowestScoreIndex;   /**<  index of lowest score in the candidate table */

} ScanResultTable_t;


//void *   scanResultTable_Create();
//void *   scanResultTable_Init ();
//void        scanResultTable_Destroy (void * hScanResultTable);
//TSiteEntry  *scanResultTable_GetFirst (void * hScanResultTable);
//TSiteEntry  *scanResultTable_GetNext (void * hScanResultTable);
//TSiteEntry  *scanResultTable_GetBySsidBssidPair (void * hScanResultTable, TSsid *pSsid, TMacAddr *pBssid);
//uint32_t   scanResultTable_CalculateBssidListSize (void * hScanResultTable, TI_BOOL bAllVarIes);
//uint32_t   scanResultTable_GetNumOfBSSIDInTheList (void * hScanResultTable);
//TI_STATUS   scanResultTable_GetBssidList (void * hScanResultTable, OS_802_11_BSSID_LIST_EX *pBssidList,
//                                          uint32_t *pLength, TI_BOOL bAllVarIes);
//TI_STATUS scanResultTable_GetBssidSupportedRatesList (void * hScanResultTable, OS_802_11_N_RATES *pRateList, uint32_t *pLength);

//void        scanResultTable_PerformAging(void * hScanResultTable);
//void        scanResultTable_SetSraThreshold(void * hScanResultTable, uint32_t uSraThreshold);
//void        scanResultTable_RemoveBySsidBssidPair(void * hScanResultTable, TSsid *pSsid, TMacAddr *pBssid);



void            scan_result_table_init();


Bool_e                  scanResultTable_NotifyScanPriodStart(ScanTag_t  scanTag);
cmeScanSharedInfo_t*    scanResultTable_GetCmeScanDbPointer();
#ifdef COMPILE_DEAD_FUNC
void    scan_result_get_probe_req_extra_ie(uint16_t*  extraIeLen, uint8_t** pExtraIe);
#endif
uint32_t  scan_result_calc_weighted_score(TScanFrameInfo* scanInfo, EScanRequestType  eScanReqType);

void    scanCandidateTable_HandleResult(TScanFrameInfo*     pFrame,
                                        uint32_t              score,
                                        int8_t                profileId);

void    scanDigestTable_HandleResult(TScanFrameInfo*        pFrame,
                                     uint32_t                 score);

void    scanDigestTable_HandleExtendedResult(TScanFrameInfo*      pFrame,
                                             uint32_t             score);

int32_t   scan_result_get_worst_rssi();

Bool_e scan_result_check_early_termination(cmeScanSharedInfo_t*    pCmeScanDB,
                                              int32_t                   res_rssi,
                                              uint32_t                  score);

Bool_e scan_result_ssid_match(dot11_SSID_t*      apSsidIe,
                          uint8_t*             apBssid,
                          uint8_t              securityType,
                          uint8_t              numOfSSID,
                          cmeScanProfiles_t* pList,
                          int8_t*              profileId);    

uint32_t scan_result_calc_highest_score_for_profile_priority(int profile_priority,int secured_profile);

int32_t scan_result_get_best_rssi();

int32_t scan_result_get_good_rssi();

cmeScanSharedInfo_t*    scanResultTable_GetCmeScanDbPointer();

#endif /* __SCAN_RESULT_TABLE_H__ */


