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
/** \file  scan_result_table.c
 *  \brief implements a table holding scan results, by BSSID
 *
 *  \see   scanResultTable.h
 */


//#define __FILE_ID__  FILE_ID_52
#include "scan_result_table.h"
#include "osDot11.h"
#include "80211_utils.h"
#include "cme_scan_api.h"
#include "rsn.h"
#include "gtrace.h"
#include "cme_common.h"
#include "cme_internal_api.h"
#include "ie_parser_util.h"

//#define MILISECONDS(seconds)                            (seconds * 1000)
//#define UPDATE_LOCAL_TIMESTAMP(pSite)                   pSite->localTimeStamp = osi_GetTimeMS();
//
//#define UPDATE_BSSID(pSite, pFrame)                     MAC_COPY((pSite)->bssid, *((pFrame)->tBssId))
////#define UPDATE_BAND(pSite, pFrame)                      (pSite)->eBand = (pFrame)->eBand
//#define UPDATE_BEACON_INTERVAL(pSite, pFrame)           pSite->beaconInterval = (pFrame)->pParsedIEs->beaconInterval
//#define UPDATE_CAPABILITIES(pSite, pFrame)              pSite->capabilities = (pFrame)->pParsedIEs->capabilities
//#define UPDATE_PRIVACY(pSite, pFrame)                   pSite->privacy = (((pFrame)->pParsedIEs->capabilities >> CAP_PRIVACY_SHIFT) & CAP_PRIVACY_MASK) ? TI_TRUE : TI_FALSE
//#define UPDATE_AGILITY(pSite, pFrame)                   pSite->agility = (((pFrame)->pParsedIEs->capabilities >> CAP_AGILE_SHIFT) & CAP_AGILE_MASK) ? TI_TRUE : TI_FALSE
////#define UPDATE_SLOT_TIME(pSite, pFrame)                 pSite->newSlotTime = (((pFrame)->pParsedIEs->capabilities >> CAP_SLOT_TIME_SHIFT) & CAP_SLOT_TIME_MASK) ? PHY_SLOT_TIME_SHORT : PHY_SLOT_TIME_LONG
//#define UPDATE_PROTECTION(pSite, pFrame)                pSite->useProtection = ((pFrame)->pParsedIEs->useProtection)
//#define UPDATE_CHANNEL(pSite, pFrame, rxChannel)        if ((pFrame)->pParsedIEs->dsParams.hdr.eleLen == 0) \
//                                                            pSite->channel = rxChannel; \
//                                                        else \
//                                                            pSite->channel = (pFrame)->pParsedIEs->dsParams.currChannel;
//#define UPDATE_DTIM_PERIOD(pSite, pFrame)               if ((pFrame)->pParsedIEs->tim.hdr.eleLen != 0) \
//                                                            pSite->dtimPeriod = (pFrame)->pParsedIEs->tim.dtimPeriod
//#define UPDATE_ATIM_WINDOW(pSite, pFrame)               if ((pFrame)->pParsedIEs->ibssParams.hdr.eleLen != 0) \
//                                                            pSite->atimWindow = (pFrame)->pParsedIEs->ibssParams.atimWindow
//#define UPDATE_AP_TX_POWER(pSite, pFrame)               if ((pFrame)->pParsedIEs->TPCReport.hdr.eleLen != 0) \
//                                                            pSite->APTxPower = (pFrame)->pParsedIEs->TPCReport.transmitPower
//#define UPDATE_BSS_TYPE(pSite, pFrame)                  pSite->bssType = (((pFrame)->pParsedIEs->capabilities >> CAP_ESS_SHIFT) & CAP_ESS_MASK) ? BSS_INFRASTRUCTURE : BSS_INDEPENDENT
//
///* Updated from beacons */
////#define UPDATE_BEACON_MODULATION(pSite, pFrame)         pSite->beaconModulation = (((pFrame)->pParsedIEs->capabilities >> CAP_PBCC_SHIFT) & CAP_PBCC_MASK) ? DRV_MODULATION_PBCC : DRV_MODULATION_CCK
//#define UPDATE_BEACON_RECV(pSite)                       pSite->beaconRecv = TI_TRUE
//
///* Updated from probes */
////#define UPDATE_PROBE_MODULATION(pSite, pFrame)          pSite->probeModulation = (((pFrame)->pParsedIEs->capabilities >> CAP_PBCC_SHIFT) & CAP_PBCC_MASK) ? DRV_MODULATION_PBCC : DRV_MODULATION_CCK
//#define UPDATE_PROBE_RECV(pSite)                        pSite->probeRecv = TI_TRUE
//#define UPDATE_APSD(pSite, pFrame)                      if ((pFrame)->pParsedIEs->WMEParams.hdr.eleLen == 0) \
//                                                                (pSite)->APSDSupport = ((((pFrame)->pParsedIEs->capabilities >> CAP_APSD_SHIFT) & CAP_APSD_MASK) ? TI_TRUE : TI_FALSE); \
//                                                        else \
//                                                            pSite->APSDSupport = (((((pFrame)->pParsedIEs->capabilities >> CAP_APSD_SHIFT) & CAP_APSD_MASK) ? TI_TRUE : TI_FALSE) || \
//                                                                                  ((((pFrame)->pParsedIEs->WMEParams.ACInfoField >> AP_QOS_INFO_UAPSD_SHIFT) & AP_QOS_INFO_UAPSD_MASK) ? TI_TRUE : TI_FALSE));
//
////#define UPDATE_PREAMBLE(pSite, pFrame)                  { (pSite)->currentPreambleType = (((pFrame)->pParsedIEs->capabilities >> CAP_PREAMBLE_SHIFT) & CAP_PREAMBLE_MASK) ? PREAMBLE_SHORT : PREAMBLE_LONG; \
////                                                          (pSite)->barkerPreambleType = (pFrame)->pParsedIEs->barkerPreambleMode; }
////
//#define UPDATE_QOS(pSite, pFrame)                       if ( ((pFrame)->pParsedIEs->WMEParams.hdr.eleLen != 0) && \
//                                                             (((((pFrame)->pParsedIEs->WMEParams.ACInfoField) & dot11_WME_ACINFO_MASK) != pSite->lastWMEParameterCnt) || (!pSite->WMESupported)) ) \
//                                                            pSite->WMESupported = TI_TRUE; \
//                                                        else \
//                                                            pSite->WMESupported = TI_FALSE;
//
//#define UPDATE_RSSI(pSite, pFrame)                      (pSite)->rssi = (pFrame)->iRssi;
//#define UPDATE_SNR(pSite, pFrame)                       (pSite)->snr = (pFrame)->iSnr;
////#define UPDATE_RATE(pSite, pFrame)                      if ((TIW_DRV_RATE_1M <= (pFrame)->eRate) && (TIW_DRV_RATE_54M >= (pFrame)->eRate)) \
////                                                            (pSite)->rxRate = (pFrame)->eRate;
////#define UPDATE_MOBILITY_DOMAIN(pSite, pFrame)           if (pFrame->pParsedIEs->tMobilityDomain.hdr.eleLen > 0) { \
////                                                            pSite->mobilityDomain.bMdValid = TI_TRUE; \
////                                                            pSite->mobilityDomain.mdId = pFrame->pParsedIEs->tMobilityDomain.mdId; \
////                                                            pSite->mobilityDomain.ftCapaAndPolicy = pFrame->pParsedIEs->tMobilityDomain.ftCapaAndPolicy; } \
////                                                        else pSite->mobilityDomain.bMdValid = TI_FALSE;


// scan_result weights indexes
#define SCAN_RESULT_WEIGHT_RSSI_INDEX                            ( 0 )
#define SCAN_RESULT_WEIGHT_PROFILE_PRIORITY_INDEX                ( 1 )
#define SCAN_RESULT_WEIGHT_SECURE_PROFILE_INDEX                  ( 2 )
#define NUM_OF_SCAN_RESULT_WEIGHTS                               ( 3 )

// scan_result weights
#define SCAN_RESULT_WEIGHT_SECURE             (   1 )
#define SCAN_RESULT_WEIGHT_RSSI               (   1 )
#define SCAN_RESULT_WEIGHT_PROFILE_PRIORITY   ( 100 )


#define SCORE_BOOST_5G (12)


typedef uint32_t (*P_SCAN_RESULT_CALC_PARAMETER_SCORE_VAL_FUNC)(TScanFrameInfo* scanInfo, EScanRequestType  eScanReqType);

uint32_t scan_result_get_score_rssi(TScanFrameInfo* scanInfo, EScanRequestType  eScanReqType);
uint32_t scan_result_get_score_security(TScanFrameInfo* scanInfo, EScanRequestType  eScanReqType);
uint32_t scan_result_get_score_profile_priority(TScanFrameInfo* scanInfo, EScanRequestType  eScanReqType);


P_SCAN_RESULT_CALC_PARAMETER_SCORE_VAL_FUNC g_scan_result_par_score_calc[NUM_OF_SCAN_RESULT_WEIGHTS];

uint16_t  scan_result_weights[NUM_OF_SCAN_RESULT_WEIGHTS];

ScanResultTable_t    ScanResultTable = {
    .cmeScanDb.mNumDigestResultsMax = CME_SCAN_MAX_DIGEST_RESULTS,
    .cmeScanDb.extendedScanResults = FALSE
    };

OsiSyncObj_t         ScanResultTableSyncObj_ull = NULL; //1 byte


extern cmeProfileInfo_t gAdHocProfile_ull;


//void    scanCandidateTable_UpdateLowestScore();
//void    scanCandidateTable_SaveResult(TScanFrameInfo*           pFrame,
//                                      int8_t                      score,
//                                      cmeScanCandidateDesc_t*   pScanResultDesc);


void            scan_result_init_weighted_score();

//static int32_t    scanResultTable_UpdateSiteData (void * hScanResultTable, TSiteEntry *pSite, TScanFrameInfo *pFrame, int8_t  score);
//static void         scanResultTable_updateRates(void * hScanResultTable, TSiteEntry *pSite, TScanFrameInfo *pFrame);
//static void         scanResultTable_UpdateWSCParams (TSiteEntry *pSite, TScanFrameInfo *pFrame);
//static int32_t     scanResultTable_CheckRxSignalValidity(ScanResultTable_t *pScanResultTable, TSiteEntry *pSite, int8_t rxLevel, uint8_t channel);
//static void         scanResultTable_RemoveEntry(void * hScanResultTable, uint8_t uIndex);
//static void         scanResultTable_UpdatHtParams (ScanResultTable_t *pScanResultTable, TSiteEntry *pSite, mlmeIEParsingParams_t *pFrameInfo);
//static void         scanResultTable_UpdateRsnIe(ScanResultTable_t *pScanResultTable, TSiteEntry *pSite, dot11_RSN_t *pNewRsnIe, uint8_t newRsnIeLen);
//static int32_t    scanResultTable_UpdateFrameBuffer(ScanResultTable_t *pScanResultTable, TSiteEntry *pSite, TScanFrameInfo *pFrame);
//static void         scanResultTable_UpdateBeaconTimestamp(ScanResultTable_t *pScanResultTable, TSiteEntry *pSite, TScanFrameInfo *pFrame);


/**
 * \fn     scan_result_table_init
 * \brief  Create scan result sync object.
 *
 *         called from initThreadEntry()
 *
 * \note
 * \return
 * \sa
 */
void   scan_result_table_init()
{
    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    // create sync object to wait until CME process the request in its own context
    if (osi_SyncObjCreate(&ScanResultTableSyncObj_ull) != OSI_OK)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: fail to allocate sync object !!!");
        ASSERT_GENERAL(0);
    }
}



//static int32_t  scanResultTable_createBeaconBuffer(ScanResultTable_t *pScanResultTable, TSiteEntry *pSite,TScanFrameInfo *pFrame)
//{
//    uint8_t elementIdx = 0;

//    if(pFrame->uBufferLength >= STANDART_BEACON_BODY_LENGTH)
//    {
//        pSite->pBuf = pool_GetElement(pScanResultTable->pLargeBeaconsPool, &elementIdx);
//        pSite->poolTypeInUse = BEACONS_POOL_LARGE;
//    }
//    else
//    {
//        pSite->pBuf = pool_GetElement(pScanResultTable->pStndtBeaconsPool, &elementIdx);
//        pSite->poolTypeInUse = BEACONS_POOL_STANDARD;
//    }
//
//    pSite->pBuf = mem_Malloc_glx(pFrame->uBufferLength);
//
//    pSite->elmntIdxInPool = elementIdx;
//
//    if(pSite->pBuf)
//    {
//       memcpy (pSite->pBuf, pFrame->pBuffer, pFrame->uBufferLength);
//       pSite->frameLength = pFrame->uBufferLength;
//
//       return OK;
//    }
//
//    GTRACE(GRP_GENERAL_ERROR, "scanResultTable_createBeaconBuffer: pSite->pBuf is NULL");
//
//    return-1;
//}






/** 
 * \fn     scanResultTable_Create
 * \brief  Create a scan result table object.
 * 
 * Create a scan result table object. Allocate system resources.
 * 
 * \note   
 * \return Handle to the newly created scan result table object, NULL if an error occured.
 * \sa     scanResultTable_Init, scanResultTable_Destroy
 */ 
//void * scanResultTable_Create ()
//{
//    ScanResultTable_t    *pScanResultTable = NULL;
//
//    /* Allocate object storage */
//    pScanResultTable = (ScanResultTable_t*)mem_Malloc_glx(sizeof(ScanResultTable_t));
//    if (NULL == pScanResultTable)
//    {
//        /* because the malloc failure here the TRACEx can not be used (no pointer for the 1st parameter to TRACEx) */
//        GTRACE(GRP_GENERAL_ERROR, "scanResultTable_Create: ERROR - Unable to allocate memory for pScanResultTable of %d bytes", sizeof (ScanResultTable_t));
//        ASSERT_GENERAL(0);
//        return NULL;  /* this is done similarly to the next error case */
//    }
//
//    return (void *)pScanResultTable;
//}


/**
 * \fn     scanResultTable_Init
 * \brief  Create a scan result table object + initialize all parameters.
 *
 * Create a scan result table object. Allocate system resources.
 *
 * \note
 * \return Handle to the newly created scan result table object, NULL if an error occured.
 * \sa
 */
//void * scanResultTable_Init ()
//{
//}



/** 
 * \fn     scanResultTable_Destroy 
 * \brief  Destroys the scan result table object
 * 
 * Destroys the scan result table object. Release system resources
 * 
 * \param  hScanResultTable - handle to the scan result table object
 * \return None
 * \sa     scanResultTable_Create 
 */ 
//void        scanResultTable_Destroy (void * hScanResultTable)
//{
//    ScanResultTable_t    *pScanResultTable = (ScanResultTable_t*)hScanResultTable;
//
//    if (NULL != pScanResultTable)
//    {
//        /* if the pool memory has already been allocated */
//        if (NULL != pScanResultTable->pStndtBeaconsPool)
//        {
//            pool_Destroy(pScanResultTable->pStndtBeaconsPool);
//        }
//
//        /* if the pool memory has already been allocated */
//        if (NULL != pScanResultTable->pLargeBeaconsPool)
//        {
//            pool_Destroy(pScanResultTable->pLargeBeaconsPool);
//        }
//
//        /* if the table memory has already been allocated */
//        if (NULL != pScanResultTable->pTable)
//        {
//            /* free table memory */
//            os_memoryFree (pScanResultTable->hOS, (void*)pScanResultTable->pTable,
//                           sizeof (TSiteEntry) * pScanResultTable->uEntriesNumber);
//        }
//
//        /* free scan result table object memeory */
//        os_memoryFree (pScanResultTable->hOS, (void*)hScanResultTable, sizeof (ScanResultTable_t));
//    }
//}



/******************************************************************************

    scanResultTable_NotifyScanPriodStart

    DESCRIPTION:    Initializes the scan result table object. Set handles to other objects.

    Caller:         ScanModule_NewCycle()

    CONTEXT:        Scan Module Thread

    PARAMETERS:     ScanTag - holds scan request type.

    RETURNS:        TRUE - if shared data based was received. FALSE - otherwise (i.e.
                    fail to allocate memory).

******************************************************************************/
Bool_e   scanResultTable_NotifyScanPriodStart(ScanTag_t  scanTag)
{
    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    /* initialize lower score parameters */
    switch (scanTag)
    {
        case    SCAN_REQUEST_CONNECT_PERIODIC_SCAN:
        case    SCAN_REQUEST_ONE_SHOT:
            ScanResultTable.candidateLowestScore      = 0;
            ScanResultTable.candidateLowestScoreIndex = 0;
            break;

        case    SCAN_REQUEST_SURVEY_SCAN:
            ScanResultTable.digestLowestScore      = 0;
            ScanResultTable.digestLowestScoreIndex = 0;
            break;
    }


    //init scan results weights
    scan_result_init_weighted_score();

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    return TRUE;
}


/** 
 * \fn     scanResultTable_GetFirst 
 * \brief  Retrieves the first entry in the table 
 * 
 * Retrieves the first entry in the table
 * 
 * \param  hScanResultTable - handle to the scan result table object
 * \return A pointer to the first entry in the table, NULL if the table is empty
 * \sa     scanResultTable_GetNext
 */ 
//TSiteEntry  *scanResultTable_GetFirst (void * hScanResultTable)
//{
//    ScanResultTable_t    *pScanResultTable = (ScanResultTable_t*)hScanResultTable;
//
//    /* initialize the iterator to point at the first site */
//    pScanResultTable->uIterator = 0;
//
//    /* and return the next entry... */
//    return scanResultTable_GetNext (hScanResultTable);
//}

/** 
 * \fn     scanResultTable_GetNext
 * \brief  Retreives the next entry in the table
 * 
 * Retreives the next entry in the table, until table is exhusted. A call to scanResultTable_GetFirst
 * must preceed a sequence of calls to this function.
 * 
 * \param  hScanResultTable - handle to the scan result table object
 * \return A pointer to the next entry in the table, NULL if the table is exhsuted
 * \sa     scanResultTable_GetFirst
 */ 
//TSiteEntry  *scanResultTable_GetNext (void * hScanResultTable)
//{
//    ScanResultTable_t    *pScanResultTable = (ScanResultTable_t*)hScanResultTable;
//
//    /* if the iterator points to a site behind current table storage, return error */
//    if (pScanResultTable->uCurrentSiteNumber <= pScanResultTable->uIterator)
//    {
//        return NULL;
//    }
//
//    return &(pScanResultTable->pTable[ pScanResultTable->uIterator++ ]);
//}


/******************************************************************************

    scanCandidateTable_GetBySsidBssidPair

    DESCRIPTION:    retreives Candidate entry according to its SSID and BSSID

    Caller:         scanCandidateTable_HandleResult()
                    txAssocReqPacket()

    Context:        Scan Module Therad

    PARAMETERS:     pSsid - SSID to search for
                    ssidLen - SSID Length
                    pBssid - BSSID to search for

    RETURNS:        pointer to Candidate entry with macthing BSSID, NULL if no such entry was found.

******************************************************************************/
cmeScanCandidateDesc_t* scanCandidateTable_GetBySsidBssidPair (char *pSsid, uint32_t ssidLen, const uint8_t *pBssid)
{
    uint32_t                  uIndex;
    uint16_t  ScanMemSize;
    cmeScanCandidateDesc_t  *pScanCandDesc;
    cmeScanSharedInfo_t *pCmeScanDb = scanResultTable_GetCmeScanDbPointer();
    size_t scanEntrySize;

    // TODO - use get mac string utility
    // GTRACE(GRP_SCAN_RESULT, "scanCandidateTable_GetBySsidBssidPair: Searching for SSID  BSSID %02x:%02x:%02x:%02x:%02x:%02x", (*pBssid)[ 0 ], (*pBssid)[ 1 ], (*pBssid)[ 2 ], (*pBssid)[ 3 ], (*pBssid)[ 4 ], (*pBssid)[ 5 ]);
    
//TODO: to add ssid comparation. need to know where the ssid ie starts in each saved result

    pScanCandDesc = pCmeScanDb->mpCandidateScanResults;

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    scanEntrySize = pCmeScanDb->extendedScanResults ? sizeof(cmeExtendedScanDigestResult_t) : sizeof(cmeScanDigestResult_t);
    ScanMemSize = pCmeScanDb->mNumDigestResultsMax * scanEntrySize;

    /* check all entries in the table */
    for (uIndex = 0; (uIndex < pCmeScanDb->mNumCandidatesFound) && (uIndex < ScanMemSize); uIndex++)
    {
        /* if the BSSID and SSID match */
        // In order to find ssid we need to parse the frame. I think it is enough to compare only bssid
        if (IRQ_UtilCompareMacAddress (pBssid, pScanCandDesc[ uIndex ].mScanResult.bssid) /*&&
            (
             ((pSsid->len == pScanResultTable->pScanResDescList[ uIndex ].result.infoElements[]) &&
             (0 == memcmp ((uint8_t *)(&(pSsid->str[ 0 ])),
                                     (uint8_t *)(&(pScanResultTable->pScanResDescList[ uIndex ].result.pSsidIe.serviceSetId[0])),
                                     pSsid->len)))
           )*/)

        {
            //GTRACE(1, "Entry found at index %d \n\r", uIndex);
            return &(pScanCandDesc[ uIndex ]);
        }
    }

    /* site wasn't found: return NULL */
    return NULL;
}







/******************************************************************************

    scanDigestTable_GetBySsidBssidPair

    DESCRIPTION:    retreives digest entry according to its SSID and BSSID

    Caller:         scanDigestTable_HandleResult()

    Context:        Scan Module Therad

    PARAMETERS:     pSsid - SSID to search for
                    ssidLen - SSID Length
                    pBssid - BSSID to search for

    RETURNS:        pointer to the digest entry with macthing BSSID, NULL if no such entry was found.

******************************************************************************/
void*  scanDigestTable_GetBySsidBssidPair (char *pSsid, uint32_t ssidLen, const uint8_t *pBssid)
{
    uint32_t                  uIndex;
    uint16_t  ScanMemSize;
    cmeScanSharedInfo_t *pCmeScanDb = scanResultTable_GetCmeScanDbPointer();

    if (TRUE == pCmeScanDb->extendedScanResults)
    {
        cmeExtendedScanDigestResult_t *pScanDigestDesc;
        pScanDigestDesc = pCmeScanDb->mpDigestExtendedScanResults;
        HOOK(HOOK_IN_SCAN_RESULT_TABLE)

        /* check all entries in the table */
        for (uIndex = 0; (uIndex <pCmeScanDb->mNumDigestResultsFound) && (uIndex < pCmeScanDb->mNumDigestResultsMax); uIndex++)
        {
            /* if the BSSID and SSID match */
            if (    IRQ_UtilCompareMacAddress (pBssid, pScanDigestDesc[ uIndex ].result.mBssid))
                    /*&& (ssidLen == pScanDigestDesc[ uIndex ].mSsidLen)
                    && (0 == memcmp (pSsid, pScanDigestDesc[ uIndex ].mSSID, ssidLen))
               )*/
            {
                //GTRACE(1, "Digest Entry found at index %d \n\r", uIndex);
                return &(pScanDigestDesc[ uIndex ]);
            }
        }
    }
    else
    {
        cmeScanDigestResult_t *pScanDigestDesc;
        pScanDigestDesc = pCmeScanDb->mpDigestScanResults;
        HOOK(HOOK_IN_SCAN_RESULT_TABLE);

        /* check all entries in the table */
        for (uIndex = 0; (uIndex < pCmeScanDb->mNumDigestResultsFound) && (uIndex < pCmeScanDb->mNumDigestResultsMax); uIndex++)
        {
            /* if the BSSID and SSID match */
            if (    IRQ_UtilCompareMacAddress (pBssid, pScanDigestDesc[ uIndex ].result.mBssid))
                    /*&& (ssidLen == pScanDigestDesc[ uIndex ].mSsidLen)
                    && (0 == memcmp (pSsid, pScanDigestDesc[ uIndex ].mSSID, ssidLen))
               )*/
            {
                //GTRACE(1, "Digest Entry found at index %d \n\r", uIndex);
                return &(pScanDigestDesc[ uIndex ]);
            }
        }
    }

    /* site wasn't found: return NULL */
    return NULL;
}


/** 
 * \fn     scanResultTable_FindHidden
 * \brief  find entry with hidden SSID anfd return it's index
 * 
 * \param  hScanResultTable - handle to the scan result table object
 * \param  uHiddenSsidIndex - entry index to return
 * \return OK if found, TI_NOT if not.
 */ 
//static int32_t scanResultTable_FindHidden (ScanResultTable_t *pScanResultTable, uint32_t *uHiddenSsidIndex)
//{
//    uint32_t uIndex;
//
//    GTRACE(GRP_SCAN_RESULT, "scanResultTable_FindHidden: Searching for hidden SSID");
//
//    /* check all entries in the table */
//    for (uIndex = 0; uIndex < pScanResultTable->uCurrentSiteNumber; uIndex++)
//    {
//        /* check if entry is with hidden SSID */
//        if ( (pScanResultTable->pTable[ uIndex ].result.ssid.len == 0) ||
//            ((pScanResultTable->pTable[ uIndex ].result.ssid.len == 1) && (pScanResultTable->pTable[ uIndex ].result.ssid.str[0] == 0)))
//        {
//            GTRACE(GRP_SCAN_RESULT, "scanResultTable_FindHidden: Entry found at index %d", uIndex);
//            *uHiddenSsidIndex = uIndex;
//            return OK;
//        }
//    }
//
//    /* site wasn't found: return NULL */
//    GTRACE(GRP_SCAN_RESULT, "scanResultTable_FindHidden: Entry was not found");
//    return-1;
//}

/** 
 * \fn     scanResultTable_performAging 
 * \brief  Deletes from table all entries which are older than the Sra threshold
 * 
 * \param  hScanResultTable - handle to the scan result table object
 * \return None
 * \sa     scanResultTable_SetSraThreshold
 */ 
//void   scanResultTable_PerformAging(void * hScanResultTable)
//{
//    ScanResultTable_t    *pScanResultTable = (ScanResultTable_t*)hScanResultTable;
//    uint8_t            uIndex = 0;
//
//    /* check all entries in the table */
//    while (uIndex < pScanResultTable->uCurrentSiteNumber)
//    {
//        /* check if the entry's age is old if it remove it */
//        if (pScanResultTable->pTable[uIndex].localTimeStamp <
//                osi_GetTimeMS() - MILISECONDS(pScanResultTable->uSraThreshold))
//        {
//            /* The removeEntry places the last entry instead of the deleted entry
//             * in order to preserve the table's continuity. For this reason the
//             * uIndex is not incremented because we want to check the entry that
//             * was placed instead of the entry deleted */
//            scanResultTable_RemoveEntry(hScanResultTable, uIndex);
//        }
//        else
//        {
//            /* If the entry was not deleted check the next entry */
//            uIndex++;
//        }
//    }
//}

/** 
 * \fn     scanResultTable_removeEntry 
 * \brief  Deletes entry from table
 *         the function keeps a continuty in the table by copying the last
 *         entry in the table to the place the entry was deleted from
 * 
 * \param  hScanResultTable - handle to the scan result table object
 * \param  uIndex           - index of the entry to be deleted
 * \return OK if entry deleted successfully-1 otherwise
 */ 
//void   scanResultTable_RemoveEntry(void * hScanResultTable, uint8_t uIndex)
//{
//    ScanResultTable_t    *pScanResultTable = (ScanResultTable_t*)hScanResultTable;
//
//    if (uIndex >= pScanResultTable->uCurrentSiteNumber)
//    {
//        GTRACE(GRP_GENERAL_ERROR , "scanResultTable_removeEntry: %d out of bound entry index", uIndex);
//        return;
//    }
//
//    /* if uIndex is not the last entry, then copy the last entry in the table to the uIndex entry */
//    if (uIndex < (pScanResultTable->uCurrentSiteNumber - 1))
//    {
//        memcpy(       &(pScanResultTable->pTable[uIndex]),
//                      &(pScanResultTable->pTable[pScanResultTable->uCurrentSiteNumber - 1]),
//                      sizeof(cmeScanDigestResult_t));
//    }
//
//    /* clear the last entry */
//    ZeroMem(&(pScanResultTable->pTable[pScanResultTable->uCurrentSiteNumber - 1]), sizeof(cmeScanDigestResult_t));
//    /* decrease the current table size */
//    pScanResultTable->uCurrentSiteNumber--;
//}


/** 
 * \fn     scanResultTable_UpdateSiteData 
 * \brief  Update a site entry data from a received frame (beacon or probe response)
 * 
 * Update a site entry data from a received frame (beacon or probe response)
 * 
 * \param  hScanResultTable - handle to the scan result table object
 * \param  pSite - the site entry to update
 * \param  pFrame - the received frame information
 * \param  score  - score of the received result
 * \return NONE */
//static int32_t scanResultTable_UpdateSiteData(void * hScanResultTable, TSiteEntry *pSite, TScanFrameInfo *pFrame, int8_t  score)
//{
//    ScanResultTable_t    *pScanResultTable = (ScanResultTable_t*)hScanResultTable;
//
//    dot11MgmtSubType_e  eSubType = pFrame->pParsedIEs->frame.subType;
//
//    if ((eSubType != BEACON) && (eSubType != PROBE_RESPONSE))
//    {
//        GTRACE(GRP_GENERAL_ERROR, "scanResultTable_UpdateSiteData: unknown frame sub type %d", eSubType);
//        return-1;
//    }
//
//    if (scanResultTable_UpdateFrameBuffer(pScanResultTable, pSite, pFrame) != OK)
//    {
//        GTRACE(GRP_GENERAL_ERROR, "scanResultTable_UpdateSiteData: frame buffer length is too big, sub-type = %d, length = %d", eSubType, pFrame->uBufferLength);
//        return-1;
//    }
//
//    /* Update SSID */
//    if (pFrame->pParsedIEs->ssidIePresent != TI_FALSE)
//    {
//        pSite->ssid.len = pFrame->pParsedIEs->ssid.hdr.eleLen;
//        if (pSite->ssid.len > DOT11_SSID_MAX_LEN)
//        {
//           GTRACE( GRP_GENERAL_ERROR, "scanResultTable_UpdateSiteData: pSite->ssid.len=%d exceeds the limit. Set to limit value %d", pSite->ssid.len, DOT11_SSID_MAX_LEN);
//           pSite->ssid.len = DOT11_SSID_MAX_LEN;
//        }
//
//        if (pSite->ssid.len > 0)
//        {
//            memcpy(
//                (void *)pSite->ssid.str,
//                (void *)pFrame->pParsedIEs->ssid.serviceSetId,
//                pSite->ssid.len);
//        }
//        if (pSite->ssid.len < DOT11_SSID_MAX_LEN)
//        {
//            pSite->ssid.str[pSite->ssid.len] = '\0';
//        }
//    }
//
//    /* Since a new scan was initiated the entry can be selected again */
////    pSite->bConsideredForSelect = TI_FALSE;
//    UPDATE_LOCAL_TIMESTAMP(pSite);
//
//
//    UPDATE_BSSID (pSite, pFrame);
////    UPDATE_BAND (pSite, pFrame);
//    UPDATE_BEACON_INTERVAL (pSite, pFrame);
//    UPDATE_CAPABILITIES (pSite, pFrame);
//    UPDATE_PRIVACY (pSite, pFrame);
//    scanResultTable_UpdateRsnIe(pScanResultTable, pSite, pFrame->pParsedIEs->rsnIe, pFrame->pParsedIEs->rsnIeLen);
//    UPDATE_APSD (pSite, pFrame);
////    UPDATE_PREAMBLE (pSite, pFrame);
//    UPDATE_AGILITY (pSite, pFrame);
//    UPDATE_RSSI (pSite, pFrame);
//    UPDATE_SNR (pSite, pFrame);
////    UPDATE_RATE (pSite, pFrame);
////    UPDATE_MOBILITY_DOMAIN(pSite, pFrame);
//
////    UPDATE_SLOT_TIME (pSite, pFrame);
//    UPDATE_PROTECTION (pSite, pFrame);
//
////    scanResultTable_updateRates (hScanResultTable, pSite, pFrame);
//
//    if ((pFrame->pParsedIEs->dsParams.hdr.eleLen != 0)  &&
//        (pFrame->pParsedIEs->dsParams.currChannel != pFrame->uChannel))
//    {
//        GTRACE(GRP_GENERAL_ERROR , "scanResultTable_UpdateSiteData: wrong channels, radio channel=%d, frame channel=%d", pFrame->uChannel, pFrame->pParsedIEs->dsParams.currChannel);
//    }
//    else
//        UPDATE_CHANNEL (pSite, pFrame , pFrame->uChannel);
//
//
//    UPDATE_BSS_TYPE (pSite, pFrame);
//    UPDATE_ATIM_WINDOW (pSite, pFrame);
//    UPDATE_AP_TX_POWER (pSite, pFrame);
//    UPDATE_QOS (pSite, pFrame);
//    scanResultTable_UpdateBeaconTimestamp(pScanResultTable, pSite, pFrame);
////    scanResultTable_UpdateWSCParams(pSite, pFrame);
//    scanResultTable_UpdatHtParams(pScanResultTable, pSite, pFrame->pParsedIEs);
//
//    /* if possible make same solution for probe resp and beacon */
//    if (BEACON == eSubType)
//    {
//        /* DTIM is only available in beacons */
//        if (pSite->bssType == BSS_INFRASTRUCTURE)
//        {
//            UPDATE_DTIM_PERIOD (pSite, pFrame);
//        }
//
////        UPDATE_BEACON_MODULATION (pSite, pFrame);
//
//        /* If the BSS type is independent, the beacon & probe modulation are equal,
//            It is important to update this field here for dynamic PBCC algorithm compatibility */
//        if (pSite->bssType == BSS_INDEPENDENT)
//        {
////            UPDATE_PROBE_MODULATION (pSite, pFrame);
//        }
//
//        pSite->bChannelSwitchAnnoncIEFound = (pFrame->pParsedIEs->channelSwitch.hdr.eleLen != 0)?TI_TRUE:TI_FALSE;
//        pSite->bP2PDEviceMgmtPresent = (pFrame->pParsedIEs->P2PDEviceMgmtPresent)?TI_TRUE:TI_FALSE;
//
//        UPDATE_BEACON_RECV(pSite);
//    }
//    else
//    {
////        UPDATE_PROBE_MODULATION (pSite, pFrame);
//
//        /* If the BSS type is independent, the beacon & probe modulation are equal,
//            It is important to update this field here for dynamic PBCC algorithm compatibility */
////        if (pSite->bssType == BSS_INDEPENDENT)
////            UPDATE_BEACON_MODULATION (pSite, pFrame);
//
//        UPDATE_PROBE_RECV (pSite);
//
//        pSite->bChannelSwitchAnnoncIEFound = TI_FALSE;
//    }
//
//    return OK;
//}





/**
 * \fn     scanDigestTable_UpdateLowestScore
 * \brief  update lowest digest scan result score and the index of this entry
 *
 * update lowest digest scan result score and the index of this entry
 *
 * \note
 * \param  none
 * \return score of this result. the highest result will is the best candidate
 * \sa
 */
void     scanDigestTable_UpdateLowestScore()
{
    uint8_t                       i;
    cmeScanSharedInfo_t *pCmeScanDb = scanResultTable_GetCmeScanDbPointer();

    //take a pointer to the digest table

    if (TRUE == pCmeScanDb->extendedScanResults)
    {
        cmeExtendedScanDigestResult_t*      pEntry;
        pEntry = pCmeScanDb->mpDigestExtendedScanResults;
        HOOK(HOOK_IN_SCAN_RESULT_TABLE);

        // Set the initial lowest score to the first score in the table
        ScanResultTable.digestLowestScoreIndex   = 0;
        ScanResultTable.digestLowestScore        = pEntry[0].mScore;

        //go over all results and update lowest scan result score and the index of this entry
        for (i = 0; i < pCmeScanDb->mNumDigestResultsFound; i++)
        {
            if (ScanResultTable.digestLowestScore > pEntry[i].mScore)
            {
                ScanResultTable.digestLowestScore        = pEntry[i].mScore;
                ScanResultTable.digestLowestScoreIndex   = i;
            }
        }
    }
    else
    {
        cmeScanDigestResult_t*      pEntry;
        pEntry = pCmeScanDb->mpDigestScanResults;

        // Set the initial lowest score to the first score in the table
        ScanResultTable.digestLowestScoreIndex   = 0;
        ScanResultTable.digestLowestScore        = pEntry[0].mScore;

        //go over all results and update lowest scan result score and the index of this entry
        for (i = 0; i < pCmeScanDb->mNumDigestResultsFound; i++)
        {
            if (ScanResultTable.digestLowestScore > pEntry[i].mScore)
            {
                ScanResultTable.digestLowestScore        = pEntry[i].mScore;
                ScanResultTable.digestLowestScoreIndex   = i;
            }
        }
    }
}



/** 
 * \fn     scanDigestTable_HandleResult
 * \brief  Update a digest entry data from a received frame (beacon or probe response)
 *
 * Update a digest entry data from a received frame (beacon or probe response)
 *
 * \param  pFrame - the received frame information
 *         score  - score of this enrty
 * \return NONE */
void scanDigestTable_SaveResult(TScanFrameInfo*            pFrame,
                                 uint32_t                     score,
                                 cmeScanDigestResult_t*     pEntry)

{
    uint32_t secType;
    uint16_t ieLen;
    //update channel;
    pEntry->result.mChannel = pFrame->pParsedIEs->dsParams.currChannel;

    //update SSID
    pEntry->result.mSsidLen = pFrame->pParsedIEs->ssid.hdr.eleLen;

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    if (pEntry->result.mSsidLen > 0)
    {
        memset(pEntry->result.mSSID, 0, sizeof(pEntry->result.mSSID));
        memcpy(
            (void *)pEntry->result.mSSID,
            (void *)pFrame->pParsedIEs->ssid.serviceSetId,
            pEntry->result.mSsidLen);

        DRV_PRINT_REPORT("\n\r\n\r ssid :%s", pEntry->result.mSSID);
    }

    //update score
    pEntry->mScore = score;

    //update rssi (and extracted from frame)
    pEntry->result.mRSSI = pFrame->iRssi;

    //update BSSID
    // MAC_COPY(pEntry->result.mBssid, pFrame->tBssId);
    IRQ_UtilCopyMacAddress(pFrame->pBssId, (uint8_t *)pEntry->result.mBssid);


    //update sec_type
    secType = 0;

    if ((pFrame->pParsedIEs->capabilities & DOT11_CAPABILITY_PRIVACY) == 0)
    {
        //OPEN
        secType |= ((RSN_WLAN_SECURITY_TYPE_BITMAP_OPEN & RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK) << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION);
    }
    else  if ((pFrame->pParsedIEs->rsnIeLen == 0) && (pFrame->pParsedIEs->wpaIeLen == 0))
    {
        //WEP
        secType |= ((RSN_WLAN_SECURITY_TYPE_BITMAP_WEP & RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK) << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION);

    }
    else
    {
        // WPA / WPA2 /WPA3

        //rsn_rsnWpaIe2SecurityInfo() function just or's bits on secType according to the information in the info element.
        //It is called first on the RSN IE (if exists), then on the WPA IE (if exists), and finally on the RSN override IEs (if exists).
        if (pFrame->pParsedIEs->rsnIeLen > 0)
        {
            DRV_PRINT_REPORT("\n\r RSN analyze");
            rsn_rsnWpaIe2SecurityInfo(&pFrame->pParsedIEs->rsnIe, pFrame->pParsedIEs->rsnIeLen, &secType);
        }

        if (pFrame->pParsedIEs->wpaIeLen > 0)
        {
            DRV_PRINT_REPORT("\n\r WPA analyze");
            rsn_rsnWpaIe2SecurityInfo(&pFrame->pParsedIEs->wpaIe, pFrame->pParsedIEs->wpaIeLen, &secType);
        }

        if (pFrame->pParsedIEs->rsnOverrideIeLen > 0)
        {
            DRV_PRINT_REPORT("\n\r RSN override analyze");
            rsn_rsnWpaIe2SecurityInfo(&pFrame->pParsedIEs->rsnOverrideIe, pFrame->pParsedIEs->rsnOverrideIeLen, &secType);
        }

        if (pFrame->pParsedIEs->rsnOverride2IeLen > 0)
        {
            DRV_PRINT_REPORT("\n\r RSN override 2 analyze");
            rsn_rsnWpaIe2SecurityInfo(&pFrame->pParsedIEs->rsnOverride2Ie, pFrame->pParsedIEs->rsnOverride2IeLen, &secType);
        }
    }

    pEntry->result.mSecurityType = secType;
}

void scanDigestTable_SaveExtendedResult(TScanFrameInfo*            pFrame,
                                 uint32_t                     score,
                                 cmeExtendedScanDigestResult_t*     pEntry)
{
    uint32_t secType;
       uint16_t ieLen;

       //update channel;
       pEntry->result.mChannel = pFrame->pParsedIEs->dsParams.currChannel;

       //update SSID
       pEntry->result.mSsidLen = pFrame->pParsedIEs->ssid.hdr.eleLen;

       HOOK(HOOK_IN_SCAN_RESULT_TABLE);

       if (pEntry->result.mSsidLen > 0)
       {
           memset(pEntry->result.mSSID, 0, sizeof(pEntry->result.mSSID));
           memcpy(
               (void *)pEntry->result.mSSID,
               (void *)pFrame->pParsedIEs->ssid.serviceSetId,
               pEntry->result.mSsidLen);

           DRV_PRINT_REPORT("\n\r\n\r ssid :%s", pEntry->result.mSSID);
       }

       //update score
       pEntry->mScore = score;

       //update rssi
       pEntry->result.mRSSI = pFrame->iRssi;


       //update BSSID
       // MAC_COPY(pEntry->result.mBssid, pFrame->tBssId);
       IRQ_UtilCopyMacAddress(pFrame->pBssId, (uint8_t *)pEntry->result.mBssid);


       //update sec_type
       secType = 0;

       if ((pFrame->pParsedIEs->capabilities & DOT11_CAPABILITY_PRIVACY) == 0)
       {
           //OPEN
           secType |= ((RSN_WLAN_SECURITY_TYPE_BITMAP_OPEN & RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK) << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION);
       }
       else  if ((pFrame->pParsedIEs->rsnIeLen == 0) && (pFrame->pParsedIEs->wpaIeLen == 0))
       {
           //WEP
           secType |= ((RSN_WLAN_SECURITY_TYPE_BITMAP_WEP & RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK) << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION);

       }
       else
       {
           // WPA / WPA2 /WPA3

           //rsn_rsnWpaIe2SecurityInfo() function just or's bits on secType according to the information in the info element.
           //It is called first on the RSN IE (if exists), then on the WPA IE (if exists), and finally on the RSN override IEs (if exists).
           if (pFrame->pParsedIEs->rsnIeLen > 0)
           {
               DRV_PRINT_REPORT("\n\r RSN analyze");
               rsn_rsnWpaIe2SecurityInfo(&pFrame->pParsedIEs->rsnIe, pFrame->pParsedIEs->rsnIeLen, &secType);
           }

           if (pFrame->pParsedIEs->wpaIeLen > 0)
           {
               DRV_PRINT_REPORT("\n\r WPA analyze");
               rsn_rsnWpaIe2SecurityInfo(&pFrame->pParsedIEs->wpaIe, pFrame->pParsedIEs->wpaIeLen, &secType);
           }

           if (pFrame->pParsedIEs->rsnOverrideIeLen > 0)
           {
               DRV_PRINT_REPORT("\n\r RSN override analyze");
               rsn_rsnWpaIe2SecurityInfo(&pFrame->pParsedIEs->rsnOverrideIe, pFrame->pParsedIEs->rsnOverrideIeLen, &secType);
           }

           if (pFrame->pParsedIEs->rsnOverride2IeLen > 0)
           {
               DRV_PRINT_REPORT("\n\r RSN override 2 analyze");
               rsn_rsnWpaIe2SecurityInfo(&pFrame->pParsedIEs->rsnOverride2Ie, pFrame->pParsedIEs->rsnOverride2IeLen, &secType);
           }
       }

       pEntry->result.mSecurityType = secType;


       // Add rates IE
       pEntry->result.mRatesLen = 0;
       memset(&pEntry->result.mRates, 0, sizeof(pEntry->result.mRates));
       if (TRUE == pFrame->pParsedIEs->ratesIePresent)
       {
            ieLen = (uint16_t)pFrame->pParsedIEs->rates.hdr.eleLen + WLAN_LEN_OF_IE_HEADER;
            pEntry->result.mRatesLen = ieLen;
            os_memcpy(pEntry->result.mRates,
                    (void *)&pFrame->pParsedIEs->rates,
                    ieLen);
       }

    //HT capabilities
    pEntry->result.HtCapabilitiesLen = 0;
    memset(&pEntry->result.HtCapabilitiesIe, 0, sizeof(pEntry->result.HtCapabilitiesIe));
    if (TRUE == pFrame->pParsedIEs->htCapabilitiesPresent)
    {
         ieLen = (uint16_t)pFrame->pParsedIEs->htCapabilities.eleHdr.eleLen + WLAN_LEN_OF_IE_HEADER;
         pEntry->result.HtCapabilitiesLen = ieLen;
         os_memcpy(pEntry->result.HtCapabilitiesIe,
                 (void *)&pFrame->pParsedIEs->htCapabilities,
                 ieLen);
    }

    pEntry->result.mErpPresent = 0;
    pEntry->result.erpIeLen = 0;
    if (TRUE == pFrame->pParsedIEs->erpPresent)
    {
         pEntry->result.mUseProtection = pFrame->pParsedIEs->useProtection;
         pEntry->result.mBarkerPreambleMode = pFrame->pParsedIEs->barkerPreambleMode;
         pEntry->result.mErpPresent = 1;

         ieLen = (uint16_t)pFrame->pParsedIEs->erpIe.hdr.eleLen + WLAN_LEN_OF_IE_HEADER;
         pEntry->result.erpIeLen = ieLen;
         os_memcpy(pEntry->result.erpIe,
                 (void *)&pFrame->pParsedIEs->erpIe,
                 ieLen);

    }

    pEntry->result.rsnIeLen = 0;
    if (pFrame->pParsedIEs->rsnIeLen > 0)
    {
        ieLen = (uint16_t)pFrame->pParsedIEs->rsnIe.hdr.eleLen + WLAN_LEN_OF_IE_HEADER;
        pEntry->result.rsnIeLen = ieLen;
        os_memcpy(pEntry->result.rsnIeData,
                (void *)&pFrame->pParsedIEs->rsnIe,
                ieLen);
    }

    pEntry->result.wpaIeLen = 0;
    if (pFrame->pParsedIEs->wpaIeLen > 0)
    {
        ieLen = (uint16_t)pFrame->pParsedIEs->wpaIe.hdr.eleLen + WLAN_LEN_OF_IE_HEADER;
        pEntry->result.wpaIeLen = ieLen;
        os_memcpy(pEntry->result.wpaIe,
                (void *)&pFrame->pParsedIEs->wpaIe,
                ieLen);
    }

    pEntry->result.wpsLen = 0;
    if (TRUE == pFrame->pParsedIEs->wpsPresent)
    {
        ieLen = (uint16_t)pFrame->pParsedIEs->wpsIe.hdr.eleLen + WLAN_LEN_OF_IE_HEADER;
        pEntry->result.wpsLen = ieLen;
        os_memcpy(pEntry->result.wpsIeData,
                (void *)&pFrame->pParsedIEs->wpsIe,
                MIN(ieLen,sizeof(pEntry->result.wpsIeData)+WLAN_LEN_OF_IE_HEADER));
    }

       pEntry->result.beaconInterval= pFrame->pParsedIEs->beaconInterval;
       pEntry->result.capabilities = pFrame->pParsedIEs->capabilities;


   }

/******************************************************************************

    scanDigestTable_HandleResult

    DESCRIPTION:    Update a digest entry data from a received frame (beacon or probe response)

    Caller:         scanResultTable_UpdateEntry()

    Context:        Scan Module Therad

    PARAMETERS:     pFrame - Scan Frame information
                    score - score of this scan result

    RETURNS:        none

******************************************************************************/
void scanDigestTable_HandleResult(TScanFrameInfo*      pFrame,
                                  uint32_t               score)
{
    cmeScanDigestResult_t   *pEntry;
    Bool_e                  resultSaved = FALSE;
    cmeScanSharedInfo_t *pCmeScanDb = scanResultTable_GetCmeScanDbPointer();

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    //if table does not exist - exit
    if (pCmeScanDb->mpDigestScanResults == NULL)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Scan Digest Table not available !!!");
        ASSERT_GENERAL(0);
        return;
    }


    //Logic:
    // 1) if entry with same ssid:bssid is found - update rssi and score if score is better
    // 1) if table is full - replace entry with lowest score if new score is higher
    // 3) if table is not full - add to new entry and advance counter of entries
    // 4) find entry with lowest score

    pEntry = (cmeScanDigestResult_t *) scanDigestTable_GetBySsidBssidPair(pFrame->pParsedIEs->ssid.serviceSetId,
                                                pFrame->pParsedIEs->ssid.hdr.eleLen,
                                                pFrame->pBssId);

    //this result already exist. update it if current result have better score
    if (pEntry != NULL)
    {
        if (score >= pEntry->mScore)
        {
            GTRACE(GRP_SCAN_RESULT, "Update Digest Result - old score %d, new score %d",
                    pEntry->mScore, score);

            //save the result
            scanDigestTable_SaveResult(pFrame, score, pEntry);

            resultSaved = TRUE;
        }
    }
    else    //new result
    {
        //save the result at free entry
        if (pCmeScanDb->mNumDigestResultsFound < pCmeScanDb->mNumDigestResultsMax)
        {
            //take free entry
            pEntry = &pCmeScanDb->mpDigestScanResults[pCmeScanDb->mNumDigestResultsFound];

            GTRACE(GRP_SCAN_RESULT, "digest table: save result to entry %d with score %d", pCmeScanDb->mNumDigestResultsFound, score);

            //save the result
            scanDigestTable_SaveResult(pFrame, score, pEntry);

            //advance for next result
            pCmeScanDb->mNumDigestResultsFound++;

            resultSaved = TRUE;
        }
        else    //table is full
        {
            GTRACE(GRP_SCAN_RESULT, "digest table is full %d entries", pCmeScanDb->mNumDigestResultsFound);


            if (score > ScanResultTable.digestLowestScore)
            {
                GTRACE(GRP_SCAN_RESULT, "Digest Result: replace entry %d with lowest score old score %d with new score %d",
                        ScanResultTable.digestLowestScoreIndex,
                        ScanResultTable.digestLowestScore,
                        score);

                //override entry with lowest score
                scanDigestTable_SaveResult(pFrame,
                                           score,
                                           & (pCmeScanDb->mpDigestScanResults[ScanResultTable.digestLowestScoreIndex]));

                resultSaved = TRUE;
            }
        }
    }

    //if result was save - update the entry with the lowest score
    if (resultSaved)
    {
        scanDigestTable_UpdateLowestScore();
    }
}

void scanDigestTable_HandleExtendedResult(TScanFrameInfo*      pFrame,
                                          uint32_t             score)
{
    cmeExtendedScanDigestResult_t   *pEntry;
    Bool_e                  resultSaved = FALSE;
    cmeScanSharedInfo_t *pCmeScanDb = scanResultTable_GetCmeScanDbPointer();

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    //if table does not exist - exit
    if(ScanResultTable.cmeScanDb.mNumDigestResultsMax == 0)
    {
        GTRACE(GRP_GENERAL_ERROR, "no scan results");

        CME_PRINT_REPORT_ERROR("\n\rno scan results");
        return;

    }
    else if (pCmeScanDb->mpDigestExtendedScanResults == NULL)
    {
        GTRACE(GRP_GENERAL_ERROR, "mpDigestExtendedScanResults was not allocated !!!");
        CME_PRINT_REPORT_ERROR("\n\rmpDigestExtendedScanResults was not allocated !!!");

        ASSERT_GENERAL(0);
        return;
    }


    //Logic:
    // 1) if entry with same ssid:bssid is found - update rssi and score if score is better
    // 1) if table is full - replace entry with lowest score if new score is higher
    // 3) if table is not full - add to new entry and advance counter of entries
    // 4) find entry with lowest score


    pEntry =(cmeExtendedScanDigestResult_t *) scanDigestTable_GetBySsidBssidPair(pFrame->pParsedIEs->ssid.serviceSetId,
                                                pFrame->pParsedIEs->ssid.hdr.eleLen,
                                                pFrame->pBssId);

    //this result already exist. update it if current result have better score
    if (pEntry != NULL)
    {
        if (score >= pEntry->mScore)
        {
            GTRACE(GRP_SCAN_RESULT, "Update Digest Result - old score %d, new score %d",
                    pEntry->mScore, score);

            //save the result
            scanDigestTable_SaveExtendedResult(pFrame, score, pEntry);

            resultSaved = TRUE;
        }
    }
    else    //new result
    {
        //save the result at free entry
        if (pCmeScanDb->mNumDigestResultsFound < pCmeScanDb->mNumDigestResultsMax)
        {
            //take free entry
            pEntry = &pCmeScanDb->mpDigestExtendedScanResults[pCmeScanDb->mNumDigestResultsFound];

            GTRACE(GRP_SCAN_RESULT, "digest table: save result to entry %d with score %d", pCmeScanDb->mNumDigestResultsFound, score);

            //save the result
            scanDigestTable_SaveExtendedResult(pFrame, score, pEntry);

            //advance for next result
            pCmeScanDb->mNumDigestResultsFound++;

            resultSaved = TRUE;
        }
        else    //table is full
        {
            GTRACE(GRP_SCAN_RESULT, "digest table is full %d entries", pCmeScanDb->mNumDigestResultsFound);


            if (score > ScanResultTable.digestLowestScore)
            {
                GTRACE(GRP_SCAN_RESULT, "Digest Result: replace entry %d with lowest score old score %d with new score %d",
                        ScanResultTable.digestLowestScoreIndex,
                        ScanResultTable.digestLowestScore,
                        score);

                //override entry with lowest score
                scanDigestTable_SaveExtendedResult(pFrame,
                                           score,
                                           & (pCmeScanDb->mpDigestExtendedScanResults[ScanResultTable.digestLowestScoreIndex]));

                resultSaved = TRUE;
            }
        }
    }

    //if result was save - update the entry with the lowest score
    if (resultSaved)
    {
        scanDigestTable_UpdateLowestScore();
    }
}

/**
 * \fn     scanCandidateTable_UpdateLowestScore
 * \brief  update lowest scan result score and the index of this entry
 *
 * update lowest scan result score and the index of this entry
 *
 * \note
 * \param  pScanResultTable - pointer to the scan result table
 * \return score of this result. the highest result will is the best candidate
 * \sa     scanResultTable_UpdateEntry
 */
void     scanCandidateTable_UpdateLowestScore()
{
    uint8_t                   i;
    cmeScanCandidateDesc_t  *pScanCandDesc;

    //take a pointer to the candidate table
    pScanCandDesc = ScanResultTable.cmeScanDb.mpCandidateScanResults;

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);
    
    // Set the initial lowest score to the first score in the table
    ScanResultTable.candidateLowestScoreIndex   = 0;
    ScanResultTable.candidateLowestScore        = pScanCandDesc[0].mScore;

    //update lowest scan result score and the index of this entry
    for (i = 0; i < ScanResultTable.cmeScanDb.mNumCandidatesFound; i++)
    {
        if (ScanResultTable.candidateLowestScore > pScanCandDesc[i].mScore)
        {
            ScanResultTable.candidateLowestScore        = pScanCandDesc[i].mScore;
            ScanResultTable.candidateLowestScoreIndex   = i;
        }
    }

    GTRACE(GRP_SCAN_RESULT, "Candidate table: lowest score is %d, index %d",
           ScanResultTable.candidateLowestScore,
           ScanResultTable.candidateLowestScoreIndex);
}



/**
 * \fn     scanCandidateTable_SaveResult
 * \brief  Update a full result entry data from a received frame (beacon or probe response)
 *
 * Update a full result entry data from a received frame (beacon or probe response)
 *
 * \param  pFrame - the received frame information
 * \param  score  - score of the received result
 * \param  pScanResultDesc - entry to save
 * \return NONE */
void scanCandidateTable_SaveResult(TScanFrameInfo*          pFrame,
                                   uint32_t                   score,
                                   int8_t                     profileId,
                                   cmeScanCandidateDesc_t*  pScanResultDesc)
{
    pScanResultDesc->mScore = score;
    pScanResultDesc->mProfileId = profileId;

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    IRQ_UtilCopyMacAddress(pFrame->pBssId, (uint8_t *)pScanResultDesc->mScanResult.bssid);

    pScanResultDesc->mScanResult.beacon_int = pFrame->pParsedIEs->beaconInterval;

    pScanResultDesc->mScanResult.qual = 0;
    pScanResultDesc->mScanResult.noise = 0;
    pScanResultDesc->mScanResult.level = pFrame->iRssi;
    pScanResultDesc->mScanResult.age = 0;

    pScanResultDesc->mScanResult.caps = pFrame->pParsedIEs->capabilities;

    pScanResultDesc->mScanResult.tsf = pFrame->uTtsfOffset;

    pScanResultDesc->mHtCapabilitiesPresent = pFrame->pParsedIEs->htCapabilitiesPresent;
    pScanResultDesc->mHtInformationPresent = pFrame->pParsedIEs->htInformationPresent;

    pScanResultDesc->mVhtCapabilitesPresent = pFrame->pParsedIEs->vhtCapabilitesPresent;

    pScanResultDesc->mHeCapabilitiesPresent = pFrame->pParsedIEs->heCapabilitiesPresent;
    pScanResultDesc->mHeOperationPresent = pFrame->pParsedIEs->heOperationPresent;

    GTRACE(GRP_SCAN_RESULT, "scan_result:  pScanResultDesc->mHeCapabilitiesPresent: %d,  pScanResultDesc->mHeOperationPresent: %d",  pScanResultDesc->mHeCapabilitiesPresent,  pScanResultDesc->mHeOperationPresent);
    // Copy the HT IEs
//    if (pScanResultDesc->mHtCapabilitiesPresent)
//    {
//        len = pFrame->pParsedIEs->htCapabilities.tHdr.eleLen + sizeof(dot11_eleHdr_t);
//        memcpy(&pScanResultDesc->mHtCapabilities, &pFrame->pParsedIEs->htCapabilities, len);
//    }

//    if (pScanResultDesc->mHtInformationPresent)
//    {
//        len = pFrame->pParsedIEs->htInformation.tHdr.eleLen + sizeof(dot11_eleHdr_t);
//        memcpy(&pScanResultDesc->mHtInformation, &pFrame->pParsedIEs->htInformation, len);
//    }

//    pScanResultDesc->mIsNewOpenProfile = ???

    pScanResultDesc->mScanResult.freq = channel_to_freq(pFrame->pParsedIEs->dsParams.currChannel);

    //these fields are not used in the upper layers
//    pScanResultDesc->mpScanResult->tsf =
//    pScanResultDesc->mpScanResult->flags =
//    pScanResultDesc->mpScanResult->age =


    if (pFrame->pParsedIEs->nonTransmittingBssid)
    {
        uint16_t MergedBufferLength = sizeof pScanResultDesc->mInfoElements;
        Bool_e MergeSuccess;

        pScanResultDesc->mbssidIndex = pFrame->pParsedIEs->mbssidIndex;
        pScanResultDesc->mbssidIndicator = pFrame->pParsedIEs->mbssidIndicator;
        IRQ_UtilCopyMacAddress(pFrame->pParsedIEs->transmittingBssid, pScanResultDesc->transmittingBssid);

        MergeSuccess = IEParser_MergeIeBuffers( 
            pFrame->pParsedIEs->nonTransmittingBssidIeBuffer, pFrame->pParsedIEs->nonTransmittingBssidIeBufferLength,
            pFrame->pBuffer, pFrame->uBufferLength,
            pScanResultDesc->mInfoElements, &MergedBufferLength);

        if (MergeSuccess)
        {
            pScanResultDesc->mScanResult.ie_len = MergedBufferLength;
        }
        else 
        {
            pScanResultDesc->mScanResult.ie_len = 0;
            DRV_PRINT_REPORT_ERROR("\n\n Error merging MBSSID IEs with transmitting parent");
        }
    }
    else 
    {
        memcpy (pScanResultDesc->mInfoElements,
                pFrame->pBuffer,
                pFrame->uBufferLength);
        pScanResultDesc->mScanResult.ie_len = pFrame->uBufferLength;
    }

    pScanResultDesc->mScanResult.beacon_ie_len = 0;

    //configure pbac for pmf
    pScanResultDesc->pbacApEnabled = pFrame->pParsedIEs->pbacApEnabled;

    pScanResultDesc->wmmIePresent = pFrame->pParsedIEs->wmmPresent;

    pScanResultDesc->nonTransmittingBssid = pFrame->pParsedIEs->nonTransmittingBssid;


}



/******************************************************************************

    scanCandidateTable_HandleResult

    DESCRIPTION:    Update a Candidate entry data from a received frame (beacon or probe response)

    Caller:         scanResultTable_UpdateEntry()

    Context:        Scan Module Therad

    PARAMETERS:     pFrame - Scan Frame information
                    score - score of this scan result

    RETURNS:        none

******************************************************************************/
void scanCandidateTable_HandleResult(TScanFrameInfo*      pFrame,
                                     uint32_t               score,
                                     int8_t                 profileId)
{
    cmeScanCandidateDesc_t*     pEntry;
    Bool_e                      resultSaved = FALSE;
    cmeScanSharedInfo_t *pCmeScanDb = scanResultTable_GetCmeScanDbPointer();

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    //if table does not exist - exit
    if (pCmeScanDb->mpCandidateScanResults == NULL)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Scan Candidate Table not available !!!");
        ASSERT_GENERAL(0);
        return;
    }


    /* check if the SSID:BSSID pair already exists in the table */
    pEntry = scanCandidateTable_GetBySsidBssidPair(pFrame->pParsedIEs->ssid.serviceSetId,
                                                   pFrame->pParsedIEs->ssid.hdr.eleLen ,
                                                   pFrame->pBssId);

    /* this SSID:BSSID pair already exists in the table */
    if (pEntry != NULL)
    {
        if (score >= pEntry->mScore)
        {
            //update score as new score is better
            GTRACE(GRP_SCAN_RESULT, "Update Candidate Result - old score %d, new score %d, profile ID %d, IEs length %d",
                    pEntry->mScore, score, profileId, pFrame->uBufferLength);

            //save the result
            scanCandidateTable_SaveResult(pFrame, score, profileId, pEntry);

            resultSaved = TRUE;
        }
        else
        {
            //do not update score as new score is not better
            GTRACE(GRP_SCAN_RESULT, "Candidate table: do not update old score %d as new score %d is not better",
                  pEntry->mScore,
                  score);
        }
    }
    else    //new result
    {
        //save the result at free entry
        if (pCmeScanDb->mNumCandidatesFound < pCmeScanDb->mNumCandidatesMax)
        {
            //take free entry
            pEntry = &pCmeScanDb->mpCandidateScanResults[pCmeScanDb->mNumCandidatesFound];

            GTRACE(GRP_SCAN_RESULT, "Candidate table: save result to entry %d with score %d, profile ID %d",
                   pCmeScanDb->mNumCandidatesFound, score, profileId);

            //save the result
            scanCandidateTable_SaveResult(pFrame, score, profileId, pEntry);

            //advance for next result
            pCmeScanDb->mNumCandidatesFound++;

            resultSaved = TRUE;
        }
        else    //table is full
        {
            GTRACE(GRP_SCAN_RESULT, "Candidate table is full %d entries", pCmeScanDb->mNumCandidatesFound);

            if (score > ScanResultTable.candidateLowestScore)
            {
                GTRACE(GRP_SCAN_RESULT, "Candidate Result: replace entry %d with lowest score old score %d with new score %d, profile ID %d",
                        ScanResultTable.candidateLowestScoreIndex,
                        ScanResultTable.candidateLowestScore,
                        score,
                        profileId);

                //override entry with lowest score
                scanCandidateTable_SaveResult(pFrame,
                                              score,
                                              profileId,
                                              & (pCmeScanDb->mpCandidateScanResults[ScanResultTable.candidateLowestScoreIndex]));

                resultSaved = TRUE;
            }
        }
    }

    //if result was save - update the entry with the lowest score
    if (resultSaved)
    {
        scanCandidateTable_UpdateLowestScore();
    }
}



/**
 * \fn     scanResultTable_updateRates 
 * \brief  Update a scan result table entry with rates information 
 * 
 * Called by the function 'updateSiteInfo()' in order to translate the rates received
 * in the beacon or probe response to rate used by the driver. Perfoms the following:
 *    -   Check the rates. validity. If rates are invalid, return
 *    -   Get the max active rate & max basic rate, if invalid, return
 *    -   Translate the max active rate and max basic rate from network rates to host rates.
 *        The max active & max basic rate are used by the driver from now on in all the processes:
 *        (selection, join, transmission, etc....)
 * 
 * \param  hScanResultTable - handle to the scan result table object
 * \param  pSite - a pointer to the site entry to update 
 * \param  pFrame - a pointer to the received frame
 * \return None
 * \sa     scanResultTable_UpdateSiteData 
 */ 
//void scanResultTable_updateRates(void * hScanResultTable, TSiteEntry *pSite, TScanFrameInfo *pFrame)
//{
////    ScanResultTable_t    *pScanResultTable = (ScanResultTable_t*)hScanResultTable;
//    ScanResultTable_t    *pScanResultTable = &ScanResultDigestTable;
//    uint8_t            maxBasicRate = 0, maxActiveRate = 0;
//    uint32_t           bitMapExtSupp = 0;
//    uint32_t           uMcsSupportedRateMask = 0, uMcsbasicRateMask = 0;
//
//    if (pFrame->pParsedIEs->rates.hdr[1] == 0)
//    {
//        TRACE(pScanResultTable->hReport, REPORT_SEVERITY_ERROR, "scanResultTable_updateRates, pRates=NULL, beacon & probeResp are:\n");
//        TRACE_INFO_HEX(pScanResultTable->hReport, (uint8_t*)&pFrame->pParsedIEs->rates, pFrame->pParsedIEs->rates.hdr[1]+2);
//        TRACE_INFO_HEX(pScanResultTable->hReport, (uint8_t*)&pFrame->pParsedIEs->rates, pFrame->pParsedIEs->rates.hdr[1]+2);
//        return;
//    }
//
//    /* Update the rate elements */
//    maxBasicRate = (uint8_t)rate_GetMaxBasicFromStr ((uint8_t *)pFrame->pParsedIEs->rates.rates,
//                                            pFrame->pParsedIEs->rates.hdr[1], (ENetRate)maxBasicRate);
//    maxActiveRate = (uint8_t)rate_GetMaxActiveFromStr ((uint8_t *)pFrame->pParsedIEs->rates.rates,
//                                              pFrame->pParsedIEs->rates.hdr[1], (ENetRate)maxActiveRate);
//
//    if (pFrame->pParsedIEs->extRates.hdr[1])
//    {
//        maxBasicRate = (uint8_t)rate_GetMaxBasicFromStr ((uint8_t *)pFrame->pParsedIEs->extRates.rates,
//                                                pFrame->pParsedIEs->extRates.hdr[1], (ENetRate)maxBasicRate);
//        maxActiveRate = (uint8_t)rate_GetMaxActiveFromStr ((uint8_t *)pFrame->pParsedIEs->extRates.rates,
//                                                  pFrame->pParsedIEs->extRates.hdr[1], (ENetRate)maxActiveRate);
//    }
//
//    if (maxActiveRate == 0)
//    {
//        maxActiveRate = maxBasicRate;
//    }
//
//    /* Now update it from network to host rates */
//    pSite->maxBasicRate = rate_NetToDrv(maxBasicRate);
//    pSite->maxActiveRate = rate_NetToDrv(maxActiveRate);
//
//    if (pSite->maxActiveRate == TIW_DRV_RATE_INVALID)
//            TRACE(pScanResultTable->hReport, REPORT_SEVERITY_ERROR, "scanResultTable_updateRates: Network To Host Rate failure, no active network rate\n");
//
//    if (pSite->maxBasicRate != TIW_DRV_RATE_INVALID)
//    {
//        if (pSite->maxActiveRate != TIW_DRV_RATE_INVALID)
//        {
//            pSite->maxActiveRate = TI_MAX (pSite->maxActiveRate, pSite->maxBasicRate);
//        }
//    }
//    else /* in case some vendors don't specify basic rates */
//    {
//        TRACE(pScanResultTable->hReport, REPORT_SEVERITY_WARNING, "scanResultTable_updateRates: Network To Host Rate failure, no basic network rate");
//        pSite->maxBasicRate = pSite->maxActiveRate;
//    }
//
//    /* build rates bit map */
//    rate_NetStrToDrvBitmap (&pSite->rateMask.uSuppRatesBitMap,
//                            pFrame->pParsedIEs->rates.rates,
//                            pFrame->pParsedIEs->rates.hdr[1]);
//    rate_NetBasicStrToDrvBitmap (&pSite->rateMask.uBasicRatesBitMap,
//                                 pFrame->pParsedIEs->rates.rates,
//                                 pFrame->pParsedIEs->rates.hdr[1]);
//
//    if (pFrame->pParsedIEs->extRates.hdr[1])
//    {
//        rate_NetStrToDrvBitmap (&bitMapExtSupp,
//                                pFrame->pParsedIEs->extRates.rates,
//                                pFrame->pParsedIEs->extRates.hdr[1]);
//
//        pSite->rateMask.uSuppRatesBitMap |= bitMapExtSupp;
//
//        rate_NetBasicStrToDrvBitmap (&bitMapExtSupp,
//                                     pFrame->pParsedIEs->extRates.rates,
//                                     pFrame->pParsedIEs->extRates.hdr[1]);
//
//        pSite->rateMask.uBasicRatesBitMap |= bitMapExtSupp;
//    }
//
//    if (pFrame->pParsedIEs->tHtCapabilities.tHdr[1] != 0)
//    {
//        /* MCS build rates bit map */
//        rate_McsNetStrToDrvBitmap (&uMcsSupportedRateMask,
//                                   (pFrame->pParsedIEs->tHtCapabilities.aHtCapabilitiesIe + DOT11_HT_CAPABILITIES_MCS_RATE_OFFSET));
//
//        pSite->rateMask.uSuppRatesBitMap |= uMcsSupportedRateMask;
//    }
//
//    if (pFrame->pParsedIEs->tHtInformation.tHdr[1] != 0)
//    {
//        /* MCS build rates bit map */
//        rate_McsNetStrToDrvBitmap (&uMcsbasicRateMask,
//                                   (pFrame->pParsedIEs->tHtInformation.aHtInformationIe + DOT11_HT_INFORMATION_MCS_RATE_OFFSET));
//
//        pSite->rateMask.uBasicRatesBitMap |= uMcsbasicRateMask;
//    }
//}

/** 
 * \fn     scanResultTable_UpdateWSCParams 
 * \brief  Update a scan result table entry with WSC information 
 * 
 * Update a scan result table entry with WSC information
 * 
 * \param  pSite - a pointer to the site entry to update 
 * \param  pFrame - a pointer to the received frame
 * \return None
 * \sa     scanResultTable_UpdateSiteData 
 */ 
//void scanResultTable_UpdateWSCParams (TSiteEntry *pSite, TScanFrameInfo *pFrame)
//{
//    /* if the IE is not null => the WSC is on - check which method is supported */
//    if (pFrame->pParsedIEs->WSCParams.hdr.eleLen != 0)
//    {
//        uint8_t    *tlvPtr,*endPtr;
//        uint16_t   tlvPtrType,tlvPtrLen,selectedMethod=0;
//
//        tlvPtr = (uint8_t*)pFrame->pParsedIEs->WSCParams.WSCBeaconOrProbIE;
//        endPtr = tlvPtr + pFrame->pParsedIEs->WSCParams.hdr.eleLen - DOT11_OUI_LEN;
//
//        do
//        {
//            COPY_BIG_END_WORD(&tlvPtrType, tlvPtr);
//
//            if (tlvPtrType == DOT11_WSC_DEVICE_PASSWORD_ID)
//            {
//                tlvPtr+=2;
//                tlvPtr+=2;
//                COPY_BIG_END_WORD(&selectedMethod, tlvPtr);
//                break;
//            }
//            else
//            {
//                tlvPtr+=2;
//                COPY_BIG_END_WORD(&tlvPtrLen, tlvPtr);
//                tlvPtr+=tlvPtrLen+2;
//            }
//        } while ((tlvPtr < endPtr) && (selectedMethod == 0));
//
//        if (tlvPtr > endPtr)
//        {
//            pSite->WSCSiteMode = TIWLN_SIMPLE_CONFIG_OFF;
//            return;
//        }
//
//        if (selectedMethod == DOT11_WSC_DEVICE_PASSWORD_ID_PIN)
//            pSite->WSCSiteMode = TIWLN_SIMPLE_CONFIG_PIN_METHOD;
//        else if (selectedMethod == DOT11_WSC_DEVICE_PASSWORD_ID_PBC)
//            pSite->WSCSiteMode = TIWLN_SIMPLE_CONFIG_PBC_METHOD;
//        else
//            pSite->WSCSiteMode = TIWLN_SIMPLE_CONFIG_OFF;
//    }
//    else
//    {
//        pSite->WSCSiteMode = TIWLN_SIMPLE_CONFIG_OFF;
//    }
//}

/** 
 * \fn     scanResultTable_GetNumOfBSSIDInTheList
 * \brief  Returns the number of BSSID's in the scan result list
 * 
 * \param  hScanResultTable - handle to the scan result table
 * \return The number of BSSID's in the list
 * \sa scanResultTable_GetBssidSupportedRatesList
 */ 
//uint32_t scanResultTable_GetNumOfBSSIDInTheList (void * hScanResultTable)
//{
//    ScanResultTable_t    *pScanResultTable = &ScanResultDigestTable;
//    return (pScanResultTable->uCurrentSiteNumber);
//}

/** 
 * \fn     scanResultTable_CalculateBssidListSize
 * \brief  Calculates the size required for BSSID list storage
 * 
 * Calculates the size required for BSSID list storage
 * 
 * \param  hScanResultTable - handle to the scan result table object
 * \param  bAllVarIes - whether to include all variable size IEs
 * \return The total length required
 * \sa     scanResultTable_GetBssidList
 */ 
//uint32_t scanResultTable_CalculateBssidListSize (void * hScanResultTable, TI_BOOL bAllVarIes)
//{
//    ScanResultTable_t    *pScanResultTable = (ScanResultTable_t*)hScanResultTable;
//    uint32_t           uSiteIndex, uSiteLength, uLength = 0;
//    TSiteEntry          *pSiteEntry;
//    uint8_t            rsnIeLen = 0;
//
//
//
//    /* set the length of the list header (sites count) */
//    uLength = sizeof(OS_802_11_BSSID_LIST_EX) - sizeof(OS_802_11_BSSID_EX);
//
//    /* check lengthes of all sites in the table */
//    for (uSiteIndex = 0; uSiteIndex < pScanResultTable->uCurrentSiteNumber; uSiteIndex++)
//    {
//
//        pSiteEntry = &(pScanResultTable->pTable[ uSiteIndex ]);
//
////#ifdef CCX_MODULE_INCLUDED
//            rsnIeLen = pSiteEntry->rsnIeLen;
////#endif
//
//        /* if full list is requested */
//        if (bAllVarIes)
//        {
//            /* set length of all IEs for this site */
//            uSiteLength = sizeof(OS_802_11_BSSID_EX) + sizeof(OS_802_11_FIXED_IEs);
//            /* and add beacon or probe response length */
//
//            uSiteLength += pSiteEntry->frameLength;
//
//
//        }
//        /* partial list is requested */
//        else
//        {
//            uSiteLength = (sizeof(OS_802_11_BSSID_EX) + sizeof(OS_802_11_FIXED_IEs) +
//                           (pSiteEntry->ssid.len + 2) + (DOT11_MAX_SUPPORTED_RATES + 2) +
//                           + (DOT11_DS_PARAMS_ELE_LEN +2) + rsnIeLen + pSiteEntry->frameLength);
//
//            /* QOS_WME information element */
//            if (pSiteEntry->WMESupported)
//            {
//                /* length of element + header */
//                uSiteLength += (DOT11_WME_PARAM_ELE_LEN + 2);
//            }
//        }
//
//        /* make sure length is 4 bytes aligned */
//        if (uSiteLength % 4)
//        {
//            uSiteLength += (4 - (uSiteLength % 4));
//        }
//
//        /* add this site length to the total length */
//        uLength += uSiteLength;
//
//        TRACE(pScanResultTable->hReport, REPORT_SEVERITY_INFORMATION , "scanResultTable_calculateBssidListSize: BSSID length=%d on site index %d\n", uSiteLength, uSiteIndex);
//    }
//
//    TRACE(pScanResultTable->hReport, REPORT_SEVERITY_INFORMATION , "scanResultTable_calculateBssidListSize: total length=%d \n", uLength);
//
//    return uLength;
//}

/** 
 * \fn     scanResultTable_GetBssidList
 * \brief  Retrieves the site table content
 * 
 * Retrieves the site table content
 * 
 * \param  hScanResultTable - handle to the scan result table object
 * \param  pBssidList - pointer to a buffer large enough to hols the BSSID list
 * \param  plength - length of the supplied buffer, will be overwritten with the actual list length
 * \param  bAllVarIes - whether to include all variable size IEs
 * \return None
 * \sa     scanResultTable_CalculateBssidListSize
 */ 
//int32_t scanResultTable_GetBssidList (void * hScanResultTable,
//                                        OS_802_11_BSSID_LIST_EX *pBssidList,
//                                        uint32_t *pLength,
//                                        TI_BOOL bAllVarIes)
//{
//    ScanResultTable_t        *pScanResultTable = (ScanResultTable_t*)hScanResultTable;
//    uint32_t                uLength, uSiteIndex, len, firstOFDMloc = 0;
//    TSiteEntry              *pSiteEntry;
//    OS_802_11_BSSID_EX      *pBssid;
//    OS_802_11_FIXED_IEs     *pFixedIes;
//    OS_802_11_VARIABLE_IEs  *pVarIes;
//    uint8_t                *pData;
////#ifdef CCX_MODULE_INCLUDED
//    uint32_t                rsnIndex, rsnIeLength;
////#endif
//
//    TRACE(pScanResultTable->hReport, REPORT_SEVERITY_INFORMATION , "scanResultTable_GetBssidList called, pBssidList= 0x%p, pLength=%d\n", pBssidList, *pLength);
//
//    /* verify the supplied length is enough */
//    uLength = scanResultTable_CalculateBssidListSize (hScanResultTable, bAllVarIes);
//    if (uLength > *pLength)
//    {
//        TRACE(pScanResultTable->hReport, REPORT_SEVERITY_ERROR , "scanResultTable_GetBssidList: received length %d, insufficient to hold list of size %d\n", *pLength, uLength);
//        *pLength = uLength;
//        return-1;
//    }
//#ifdef TI_DBG
//    else
//    {
//        TRACE(pScanResultTable->hReport, REPORT_SEVERITY_INFORMATION , "scanResultTable_GetBssidList: supplied length: %d, required length: %d\n", *pLength, uLength);
//    }
//#endif
//
//    /* Nullify number of items in the BSSID list */
//    pBssidList->NumberOfItems = 0;
//
//    /* set length to list header size (only list count) */
//    uLength = sizeof(OS_802_11_BSSID_LIST_EX) - sizeof(OS_802_11_BSSID_EX);
//
//    /* set data pointer to first item in list */
//    pData = (uint8_t*)&(pBssidList->Bssid[0]);
//
//
//    for (uSiteIndex = 0; uSiteIndex < pScanResultTable->uCurrentSiteNumber; uSiteIndex++)
//    {
//        /* set BSSID entry pointer to current location in buffer */
//        pBssid = (OS_802_11_BSSID_EX*)pData;
//
//        /* set pointer to site entry */
//        pSiteEntry = &(pScanResultTable->pTable[ uSiteIndex ]);
//
//
//        TRACE(pScanResultTable->hReport, REPORT_SEVERITY_INFORMATION , "scanResultTable_GetBssidList: copying entry at index %d, BSSID %02x:%02x:%02x:%02x:%02x:%02x\n", uSiteIndex, pSiteEntry->bssid[ 0 ], pSiteEntry->bssid[ 1 ], pSiteEntry->bssid[ 2 ], pSiteEntry->bssid[ 3 ], pSiteEntry->bssid[ 4 ], pSiteEntry->bssid[ 5 ]);
//
//        /* start copy stuff: */
//        /* MacAddress */
//        MAC_COPY (pBssid->MacAddress, pSiteEntry->bssid);
//
//        /* Capabilities */
//        pBssid->Capabilities = pSiteEntry->capabilities;
//
//        /* SSID */
//        os_memoryZero (pScanResultTable->hOS, &(pBssid->Ssid.Ssid), DOT11_SSID_MAX_LEN);
//        if (pSiteEntry->ssid.len > DOT11_SSID_MAX_LEN)
//        {
//            pSiteEntry->ssid.len = DOT11_SSID_MAX_LEN;
//        }
//        os_memoryCopy (pScanResultTable->hOS,
//                       (void *)pBssid->Ssid.Ssid,
//                       (void *)pSiteEntry->ssid.str,
//                       pSiteEntry->ssid.len);
//        pBssid->Ssid.SsidLength = pSiteEntry->ssid.len;
//
//        /* privacy */
//        pBssid->Privacy = pSiteEntry->privacy;
//
//        /* RSSI */
//        pBssid->Rssi = pSiteEntry->rssi;
//
//        pBssid->Configuration.Length = sizeof(OS_802_11_CONFIGURATION);
//        pBssid->Configuration.BeaconPeriod = pSiteEntry->beaconInterval;
//        pBssid->Configuration.ATIMWindow = pSiteEntry->atimWindow;
//        pBssid->Configuration.Union.channel = Chan2Freq(pSiteEntry->channel);
//
//        if  (pSiteEntry->bssType == BSS_INDEPENDENT)
//            pBssid->InfrastructureMode = os802_11IBSS;
//        else
//            pBssid->InfrastructureMode = os802_11Infrastructure;
//        /* Supported Rates */
//        os_memoryZero (pScanResultTable->hOS, (void *)pBssid->SupportedRates, sizeof(OS_802_11_RATES_EX));
//        rate_DrvBitmapToNetStr (pSiteEntry->rateMask.uSuppRatesBitMap,
//                                pSiteEntry->rateMask.uBasicRatesBitMap,
//                                (uint8_t*)pBssid->SupportedRates,
//                                &len,
//                                &firstOFDMloc);
//
//        /* set network type acording to band and rates */
//        if (RADIO_BAND_2_4_GHZ == pSiteEntry->eBand)
//        {
//            if (firstOFDMloc == len)
//            {
//                pBssid->NetworkTypeInUse = os802_11DS;
//            } else {
//                pBssid->NetworkTypeInUse = os802_11OFDM24;
//            }
//        }
//        else
//        {
//            pBssid->NetworkTypeInUse = os802_11OFDM5;
//        }
//
//        /* start copy IE's: first nullify length */
//        pBssid->IELength = 0;
//
//        /* copy fixed IEs from site entry */
//        pFixedIes = (OS_802_11_FIXED_IEs*)&(pBssid->IEs[ pBssid->IELength ]);
//        os_memoryCopy (pScanResultTable->hOS, (void*)pFixedIes->TimeStamp,
//                       &(pSiteEntry->tsfTimeStamp[ 0 ]), TIME_STAMP_LEN);
//        pFixedIes->BeaconInterval = pSiteEntry->beaconInterval;
//        pFixedIes->Capabilities = pSiteEntry->capabilities;
//        pBssid->IELength += sizeof(OS_802_11_FIXED_IEs);
//
//        /* set pointer for variable length IE's */
//        pVarIes = (OS_802_11_VARIABLE_IEs*)&(pBssid->IEs[ pBssid->IELength ]);
//
//        if (!bAllVarIes)
//        {   /* copy only some variable IEs */
//
//            /* copy SSID */
//            pVarIes->ElementID = SSID_IE_ID;
//            pVarIes->Length = pSiteEntry->ssid.len;
//            os_memoryCopy (pScanResultTable->hOS,
//                           (void *)pVarIes->data,
//                           (void *)pSiteEntry->ssid.str,
//                           pSiteEntry->ssid.len);
//            pBssid->IELength += (pVarIes->Length + 2);
//
//            /* copy RATES */
//            pVarIes = (OS_802_11_VARIABLE_IEs*)&(pBssid->IEs[ pBssid->IELength ]);
//            pVarIes->ElementID = SUPPORTED_RATES_IE_ID;
//            rate_DrvBitmapToNetStr (pSiteEntry->rateMask.uSuppRatesBitMap,
//                                    pSiteEntry->rateMask.uBasicRatesBitMap,
//                                    (uint8_t *)pVarIes->data,
//                                    &len,
//                                    &firstOFDMloc);
//            pVarIes->Length = len;
//            pBssid->IELength += (pVarIes->Length + 2);
//
//            /* copy DS */
//            pVarIes = (OS_802_11_VARIABLE_IEs*)&(pBssid->IEs[ pBssid->IELength ]);
//            pVarIes->ElementID = DS_PARAMETER_SET_IE_ID;
//            pVarIes->Length = DOT11_DS_PARAMS_ELE_LEN;
//            os_memoryCopy (pScanResultTable->hOS, (void *)pVarIes->data,
//                           &(pSiteEntry->channel), DOT11_DS_PARAMS_ELE_LEN);
//            pBssid->IELength += (pVarIes->Length + 2);
////#ifdef CCX_MODULE_INCLUDED
//            /* copy RSN information elements */
//            if (0 < pSiteEntry->rsnIeLen)
//            {
//                rsnIeLength = 0;
//                for (rsnIndex=0; rsnIndex < MAX_RSN_IE && pSiteEntry->pRsnIe[ rsnIndex ].hdr[1] > 0; rsnIndex++)
//                {
//                    pVarIes = (OS_802_11_VARIABLE_IEs*)&(pBssid->IEs[ pBssid->IELength + rsnIeLength ]);
//                    pVarIes->ElementID = pSiteEntry->pRsnIe[ rsnIndex ].hdr[0];
//                    pVarIes->Length = pSiteEntry->pRsnIe[ rsnIndex ].hdr[1];
//                    os_memoryCopy (pScanResultTable->hOS, (void *)pVarIes->data,
//                                   (void *)pSiteEntry->pRsnIe[ rsnIndex ].rsnIeData,
//                                   pSiteEntry->pRsnIe[ rsnIndex ].hdr[1]);
//                    rsnIeLength += pSiteEntry->pRsnIe[ rsnIndex ].hdr[1] + 2;
//                }
//                pBssid->IELength += pSiteEntry->rsnIeLen;
//            }
////#endif
//            /* QOS_WME/CCX */
//            if (TI_TRUE == pSiteEntry->WMESupported)
//            {
//                /* oui */
//                uint8_t            ouiWME[3] = {0x50, 0xf2, 0x01};
//                dot11_WME_PARAM_t   *pWMEParams;
//
//                /* fill in the general element  parameters */
//                pVarIes =  (OS_802_11_VARIABLE_IEs*)&(pBssid->IEs[ pBssid->IELength ]);
//                pVarIes->ElementID = DOT11_WME_ELE_ID;
//                pVarIes->Length = DOT11_WME_PARAM_ELE_LEN;
//
//                /* fill in the specific element  parameters */
//                pWMEParams = (dot11_WME_PARAM_t*)pVarIes;
//                os_memoryCopy (pScanResultTable->hOS, (void *)pWMEParams->OUI, ouiWME, 3);
//                pWMEParams->OUIType = dot11_WME_OUI_TYPE;
//                pWMEParams->OUISubType = dot11_WME_OUI_SUB_TYPE_PARAMS_IE;
//                pWMEParams->version = dot11_WME_VERSION;
//                pWMEParams->ACInfoField = dot11_WME_ACINFO_MASK & pSiteEntry->lastWMEParameterCnt;
//
//                /* fill in the data  */
//                os_memoryCopy (pScanResultTable->hOS, &(pWMEParams->WME_ACParameteres),
//                               &(pSiteEntry->WMEParameters), sizeof(dot11_ACParameters_t));
//
//
//                /* update the general length */
//                pBssid->IELength += (pVarIes->Length + 2);
//            }
//
//            /* Copy the unknown IEs */
//            if ( 0 < pSiteEntry->frameLength  ) {
//
//                    os_memoryCopy (pScanResultTable->hOS, (void *)(&pBssid->IEs[ pBssid->IELength ]),
//                                   (void*)(pSiteEntry->pBuf), pSiteEntry->frameLength);
//                    pBssid->IELength += pSiteEntry->frameLength;
//            }
//
//        }
//        else
//        {   /* Copy all variable IEs */
//            if (pSiteEntry->probeRecv)
//            {
//                /* It looks like it never happens. Anyway decided to check */
//                if ( pSiteEntry->frameLength > MAX_BEACON_BODY_LENGTH )
//                   /* it may have sense to check the Len here for 0 or MIN_BEACON_BODY_LENGTH also */
//                {
//                    TRACE( pScanResultTable->hReport, REPORT_SEVERITY_ERROR,
//                         "scanResultTable_GetBssidList. pSiteEntry->frameLength=%d exceeds the limit %d\n",
//                         pSiteEntry->frameLength, MAX_BEACON_BODY_LENGTH);
//                    handleRunProblem(PROBLEM_BUF_SIZE_VIOLATION);
//                    return-1;
//                }
//                if(pSiteEntry->pBuf != NULL)
//                {
//
//                    os_memoryCopy (pScanResultTable->hOS, (void*)pVarIes,
//                                   (void*)(pSiteEntry->pBuf), pSiteEntry->frameLength);
//                    pBssid->IELength += pSiteEntry->frameLength;
//                }
//            }
//            else
//            {
//                /* It looks like it never happens. Anyway decided to check */
//                if ( pSiteEntry->frameLength > MAX_BEACON_BODY_LENGTH )
//                   /* it may have sense to check the Len here for 0 or MIN_BEACON_BODY_LENGTH also */
//                {
//                    TRACE( pScanResultTable->hReport, REPORT_SEVERITY_ERROR,
//                         "scanResultTable_GetBssidList. pSiteEntry->frameLength=%d exceeds the limit %d\n",
//                         pSiteEntry->frameLength, MAX_BEACON_BODY_LENGTH);
//                    handleRunProblem(PROBLEM_BUF_SIZE_VIOLATION);
//                    return-1;
//                }
//
//
//                if(pSiteEntry->pBuf)
//                {
//                    os_memoryCopy (pScanResultTable->hOS, (void*)pVarIes,
//                            (void*)(pSiteEntry->pBuf), pSiteEntry->frameLength);
//                    pBssid->IELength += pSiteEntry->frameLength;
//                }
//            }
//        }
//
//        /* -1 to remove the IEs[1] placeholder in OS_802_11_BSSID_EX which is taken into account in pBssid->IELength */
//        pBssid->Length = sizeof(OS_802_11_BSSID_EX) + pBssid->IELength - 1;
//
//        TRACE(pScanResultTable->hReport, REPORT_SEVERITY_INFORMATION , "scanResultTable_GetBssidList: before alignment fix, IEs length: %d, BSSID length %d\n", pBssid->IELength, pBssid->Length);
//
//        /* make sure length is 4 bytes aligned */
//        if (pBssid->Length % 4)
//        {
//            pBssid->Length += (4 - (pBssid->Length % 4));
//        }
//
//        TRACE(pScanResultTable->hReport, REPORT_SEVERITY_INFORMATION , "scanResultTable_GetBssidList: after alignment fix, IEs length: %d, BSSID length %d\n", pBssid->IELength, pBssid->Length);
//
//        pData += pBssid->Length;
//        uLength += pBssid->Length;
//
//        TRACE(pScanResultTable->hReport, REPORT_SEVERITY_INFORMATION , "scanResultTable_GetBssidList: current length: %d\n", uLength);
//    }
//
//    pBssidList->NumberOfItems = pScanResultTable->uCurrentSiteNumber;
//    *pLength = uLength;
//
//    TRACE(pScanResultTable->hReport, REPORT_SEVERITY_INFORMATION , "scanResultTable_GetBssidList: total length: %d, number of items: %d\n", uLength, pBssidList->NumberOfItems);
//
//    return OK;
//}


/** 
 * \fn     scanResultTable_GetBssidSupportedRatesList
 * \brief  Retrieves the Rate table corresponding with the site
 * table
 * 
 * 
 * \param  hScanResultTable - handle to the scan result table object
 * \param  pRateList - pointer to a buffer large enough to hols
 * the rate list
 * \param  pLength - length of the supplied buffer,
 * \return int32_t
 * \sa scanResultTable_GetBssidSupportedRatesList
 */ 
//int32_t scanResultTable_GetBssidSupportedRatesList (void * hScanResultTable,
//                                                      OS_802_11_N_RATES *pRateList,
//                                                      uint32_t *pLength)
//{
//    ScanResultTable_t        *pScanResultTable = (ScanResultTable_t*)hScanResultTable;
//    TSiteEntry              *pSiteEntry;
//    uint32_t                uSiteIndex;
//    uint32_t                requiredLength;
//    OS_802_11_N_RATES         *pCurrRateString;
//    TI_BOOL                  b11nEnable;
//    TI_BOOL                  bMimoEnable;
//
//    TRACE(pScanResultTable->hReport, REPORT_SEVERITY_INFORMATION , "scanResultTable_GetBssidSupportedRatesList called");
//
//    TWD_DevCap_IsHtEnable(pScanResultTable->hTWD, &b11nEnable);
//    TWD_DevCap_IsMimoEnable(pScanResultTable->hTWD, &bMimoEnable);
//
//    /* Verify the supplied length is enough*/
//    requiredLength = pScanResultTable->uCurrentSiteNumber*sizeof(OS_802_11_N_RATES);
//    if (requiredLength > *pLength)
//    {
//        TRACE(pScanResultTable->hReport, REPORT_SEVERITY_ERROR , "scanResultTable_GetBssidSupportedRatesList: received length %d, insufficient to hold list of size %d\n", *pLength, requiredLength);
//        *pLength = requiredLength;
//        return-1;
//    }
//
//    /* Create the rate list*/
//    for (uSiteIndex = 0; uSiteIndex < pScanResultTable->uCurrentSiteNumber; uSiteIndex++)
//    {
//        pCurrRateString = &(pRateList[uSiteIndex]);
//        pSiteEntry = &(pScanResultTable->pTable[ uSiteIndex ]);
//
//        /* Supported Rates */
//        os_memoryZero (pScanResultTable->hOS, (void *)pCurrRateString, sizeof(OS_802_11_N_RATES));
//
//        rate_DrvBitmapToDrvRates (pSiteEntry->rateMask.uSuppRatesBitMap,
//                                  (uint8_t*)pCurrRateString,
//                                  b11nEnable,
//                                  bMimoEnable);
//    }
//
//    return OK;
//}


/***********************************************************************
 *                        scanResultTable_CheckRxSignalValidity
 ***********************************************************************
DESCRIPTION: Called by the scanResultTable_UpdateEntry when receiving managment frame 
                Find the ste in the site table and validate that the 
                RSSI of that site signal is not lower then -80DB + not lower
                then the exising site RSSI


INPUT:      rxLevel     -   Rx level the frame received in
            bssid       -   BSSID of the frame

OUTPUT:

RETURN:     OK /-1

************************************************************************/
/** 
 * \fn     scanResultTable_CheckRxSignalValidity
 * \brief  return the state of the table to its state after scan
 * 
 * Called by the scanResultTable_UpdateEntry when receiving managment frame   
 * validate that the RSSI of that site signal is not lower then then the exising site RSSI.
 * validate that the channel in correct.                                             
 * 
 * \param  pScanResultTable - scan result table object
 * \param  pSite - entry from the table
 * \param  rssi - RSSI level at which frame was received 
 * \param  channel - channel on which the frame was received 
 * \return None
 * \sa
 */ 
//static int32_t scanResultTable_CheckRxSignalValidity(ScanResultTable_t *pScanResultTable, TSiteEntry *pSite, int8_t rxLevel, uint8_t channel)
//{
//     if ((channel != pSite->channel) &&
//         (rxLevel < pSite->rssi))
//     {   /* Ignore wrong packets with lower RSSI that were detect as
//         ripples from different channels */
//         TRACE(pScanResultTable->hReport, REPORT_SEVERITY_WARNING, "scanResultTable_CheckRxSignalValidity:Rx RSSI =%d, on channel=%d, is lower then given RSSI =%d on channel=%d, dropping it.\n", rxLevel, channel, pSite->rssi, pSite->channel);
//         return-1;
//     }
//
//     return OK;
//}


//static void scanResultTable_UpdatHtParams (ScanResultTable_t *pScanResultTable, TSiteEntry *pSite,
//                                           mlmeIEParsingParams_t *pFrameInfo)
//{
//    /* Updating HT capabilites IE params */
//    if (pFrameInfo->tHtCapabilities.tHdr.eleLen != 0)
//    {
//        /* updating the HT capabilities unparse format into the site table. */
//        memcpy (&pSite->tHtCapabilities,
//                (uint8_t *)(&pFrameInfo->tHtCapabilities),
//                sizeof(Tdot11HtCapabilitiesUnparse));
//
//        GTRACE(GRP_SCAN_RESULT, "$$$$$$ HT capabilites parameters were updates.");
//    }
//    else
//    {
//        pSite->tHtCapabilities.tHdr.eleId = TI_FALSE;
//    }
//
//    /* Updating HT Information IE params */
//    if (pFrameInfo->tHtInformation.tHdr.eleLen != 0)
//    {
//        /* update in case different setting vlaue from the last one */
//        if (memcmp (          (uint8_t *)&pSite->tHtInformation,
//                (uint8_t *)&pFrameInfo->tHtInformation,
//                sizeof(Tdot11HtInformationUnparse)) != 0)
//        {
//            pSite->bHtInfoUpdate = TI_TRUE;
//            /* updating the HT Information unparse pormat into the site table. */
//            memcpy (&pSite->tHtInformation, &pFrameInfo->tHtInformation, sizeof(Tdot11HtInformationUnparse));
//            GTRACE(GRP_SCAN_RESULT, "$$$$$$ HT Information parameters were updates.");
//        }
//        else
//        {
//            pSite->bHtInfoUpdate = TI_FALSE;
//        }
//    }
//    else
//    {
//        pSite->tHtInformation.tHdr.eleId = TI_FALSE;
//    }
//}

//void scanResultTable_RemoveBySsidBssidPair(void * hScanResultTable, TSsid *pSsid, TMacAddr *pBssid)
//{
//    ScanResultTable_t *pScanResultTable = (ScanResultTable_t*)hScanResultTable;
//    TSiteEntry *pSite;
//
//    pSite = scanCandidateTable_GetBySsidBssidPair(hScanResultTable, pSsid ,pBssid);
//
//    if (NULL != pSite)
//    {
//        TRACE(pScanResultTable->hReport, REPORT_SEVERITY_INFORMATION , "scanResultTable_RemoveBySsidBssidPair: found entry, removing it\n");
//
//        scanResultTable_RemoveEntry(hScanResultTable, pSite->index);
//    }
//    else
//    {
//        TRACE(pScanResultTable->hReport, REPORT_SEVERITY_WARNING , "scanResultTable_RemoveBySsidBssidPair: entry doesn't exist!!\n");
//    }
//
//
//}


//static void  scanResultTable_UpdateRsnIe(ScanResultTable_t *pScanResultTable, TSiteEntry *pSite, dot11_RSN_t *pNewRsnIe, uint8_t newRsnIeLen)
//{
//    if ((pNewRsnIe) != NULL)
//    {
//        uint8_t length = 0;
//        uint8_t index = 0;
//        dot11_RSN_t *pTempRsnIe = pNewRsnIe;
//
//        pSite->rsnIeLen = newRsnIeLen;
//
//        while ((length < (pSite)->rsnIeLen) && (index < MAX_RSN_IE))
//        {
//            (pSite)->pRsnIe[index].hdr.eleId = pTempRsnIe->hdr.eleId;
//            (pSite)->pRsnIe[index].hdr.eleLen = pTempRsnIe->hdr.eleLen;
//
//            memcpy((void *)(pSite)->pRsnIe[index].rsnIeData, (void *)pTempRsnIe->rsnIeData, pTempRsnIe->hdr.eleLen);
//
//            length += pTempRsnIe->hdr.eleLen + 2;
//            pTempRsnIe += 1;
//            index++;
//        }
//    }
//    else
//    {
//        pSite->rsnIeLen = 0;
//    }
//}


//static int32_t  scanResultTable_UpdateFrameBuffer(ScanResultTable_t *pScanResultTable, TSiteEntry *pSite, TScanFrameInfo *pFrame)
//{
//    if (pFrame->uBufferLength > MAX_BEACON_BODY_LENGTH)
//    {
//        GTRACE(GRP_SCAN_ERROR, "scanResultTable_UpdateFrameBuffer: frame is too long, length %d", pFrame->uBufferLength);
//        return-1;
//    }
//
//    //free curernt buffer
//   mem_Free_glx(pSite->pBuf);
//
//    //allocate new buffer
//    pSite->pBuf = mem_Malloc_glx(pFrame->uBufferLength);
//
//    /* Copy the frame buffer to the site buffer (raw frame data) */
//    if(pSite->pBuf)
//    {
//        memcpy (pSite->pBuf, pFrame->pBuffer, pFrame->uBufferLength);
//        pSite->frameLength = pFrame->uBufferLength;
//
//        return OK;
//    }
//
//    GTRACE(GRP_GENERAL_ERROR, "scanResultTable_UpdateFrameBuffer: fail to allocate new frame buffer, length %d", pFrame->uBufferLength);
//
//    return-1;
//}


//static void  scanResultTable_UpdateBeaconTimestamp(ScanResultTable_t *pScanResultTable, TSiteEntry *pSite, TScanFrameInfo *pFrame)
//{
//    memcpy(pSite->tsfTimeStamp, (void *)pFrame->pParsedIEs->timeStamp, TIME_STAMP_LEN);
//}






/**
 * \fn     scanResultTable_GetCmeScanDbPointer
 * \brief  get pointer to CME shared data base
 *
 * update get pointer to CME shared data base
 *
 * \note
 * \param
 * \return pointer to CME shared data base
 * \sa     scanCncn_SendCompleteIndication
 */
cmeScanSharedInfo_t*    scanResultTable_GetCmeScanDbPointer()
{
    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    return &(ScanResultTable.cmeScanDb);
}


/*************************************************************************/
// Name:        scan_result_init_weighted_score
//
// Description: initialize the scan result weights. done at every scan cycle
//              (this is done instead of putting it in ULL)
//
// Callers:     scanResultTable_NotifyScanPriodStart
//
// Inputs:      none
//
// Outputs:     none
//
// Return values:   none
/*************************************************************************/
void scan_result_init_weighted_score()
{
    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    //init weights
    scan_result_weights[SCAN_RESULT_WEIGHT_RSSI_INDEX]             = SCAN_RESULT_WEIGHT_RSSI;
    scan_result_weights[SCAN_RESULT_WEIGHT_PROFILE_PRIORITY_INDEX] = SCAN_RESULT_WEIGHT_PROFILE_PRIORITY;
    scan_result_weights[SCAN_RESULT_WEIGHT_SECURE_PROFILE_INDEX]   = SCAN_RESULT_WEIGHT_SECURE;

    //init functions pointers of weight calculation functions
    g_scan_result_par_score_calc[SCAN_RESULT_WEIGHT_RSSI_INDEX]               = scan_result_get_score_rssi;
    g_scan_result_par_score_calc[SCAN_RESULT_WEIGHT_PROFILE_PRIORITY_INDEX]   = scan_result_get_score_profile_priority;
    g_scan_result_par_score_calc[SCAN_RESULT_WEIGHT_SECURE_PROFILE_INDEX]     = scan_result_get_score_security;
}




/*************************************************************************/
// Name:        scan_result_get_score_rssi
//
// Description: calculate the score of this scan result according to its rssi
//
//
// Callers:     scan_result_calc_weighted_score
//
// Inputs:      scanInfo - scan result information
//              eScanReqType - scan type
//
// Outputs:     none
//
// Return values:   score
/*************************************************************************/
typedef struct
{
    int16_t    rssi_step;
    uint16_t   rssi_score;
} rssi_score_element_t;

const rssi_score_element_t  rssi_steps[] =
{
    /*------------------------------------------------+-------------------------------------*/
    /*    RSSI STEP                             |        RSSI SCORE                         */
    {SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG1   /* -30 */  , 2055               },
    {SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG2   /* -35 */  , 2050               },
    {SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG3   /* -40 */  , 2045               },
    {SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG4   /* -45 */  , 2040               },
    {SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG5   /* -50 */  , 2035               },
    {SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG6   /* -55 */  , 2030               },
    {SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG7   /* -60 */  , 2025               },
    {SCAN_RESULT_RSSI_THRESHOLD_DEG1        /* -65 */  , 2020               },
    {SCAN_RESULT_RSSI_THRESHOLD_DEG2        /* -70 */  , 2015               },
    {SCAN_RESULT_RSSI_THRESHOLD_DEG3        /* -75 */  , 2010               },
    {SCAN_RESULT_RSSI_THRESHOLD_DEG4        /* -80 */  , 2005               },
    {SCAN_RESULT_RSSI_THRESHOLD_DEG5        /* -85 */  , 2000               },
    {SCAN_RESULT_RSSI_THRESHOLD_WORST_DEG1  /* -90 */  , 1500               },
    {SCAN_RESULT_RSSI_THRESHOLD_WORST_DEG2  /* -95 */  , 1000               },
    {SCAN_RESULT_RSSI_THRESHOLD_WORST_DEG3  /* -100 */ ,  500               },
    {SCAN_RESULT_RSSI_THRESHOLD_NOT_VALID   /* -127 */ ,    0               },
};

uint32_t scan_result_get_score_rssi(TScanFrameInfo* scanInfo, EScanRequestType  eScanReqType)
{
    int8_t    rssi;
    uint32_t   i, score = 0;

    uint8_t   num_of_scan_steps = sizeof(rssi_steps) / sizeof(rssi_score_element_t);

    //take the rssi from the scan result
    rssi = scanInfo->iRssi;

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    //find rssi step that represent the scan result and get the score from this step
    for (i = 0; i < num_of_scan_steps; i++)
    {
        if (rssi >= rssi_steps[i].rssi_step)
        {
            score = rssi_steps[i].rssi_score;
            break;
        }
    }

    if ((eScanReqType != SCAN_REQUEST_SURVEY_SCAN ) && (scanInfo->uChannel > A_5G_BAND_MIN_CHANNEL))
    {
        score += SCORE_BOOST_5G;
    }

    GTRACE(GRP_SCAN_RESULT, "rssi = -%d, score = %d", CONVERT_SIGN(rssi), score);

    return  score;
}

/*************************************************************************/
// Name:        scan_result_get_score_profile_priority
//
// Description: calculate the score of this scan result according to the
//              priority of this device in the profile list. if the device
//              does not exist in the profile list - score is 0.
//
// Callers:     scan_result_calc_weighted_score
//
// Inputs:      scanInfo - scan result information
//              eScanReqType - scan type
//
// Outputs:     none
//
// Return values:   score
/*************************************************************************/
const uint8_t score_per_profile_priority[] =
{
//there are 16 prorities [0:15] + open profile
//----------------------------
//  score  |  priority
     1     ,  //  OPEN security: open security is supported and Profile not in the list
     2     ,  //  0         low priority
     3     ,  //  1
     4     ,  //  2
     5     ,  //  3
     6     ,  //  4
     7     ,  //  5
     8     ,  //  6
     9     ,  //  7
    10     ,  //  8
    11     ,  //  9
    12     ,  //  10
    13     ,  //  11
    14     ,  //  12
    15     ,  //  13
    16     ,  //  14
    17     ,  //  15        high priority
//----------------------------
};

uint32_t scan_result_get_score_profile_priority(TScanFrameInfo* scanInfo, EScanRequestType  eScanReqType)
{
    int     i;
    uint8_t   openProfileFound= 0;
    uint8_t   profilePriority = 0;
    uint32_t  score           = 0;
    uint8_t   macZero[6] = {0,0,0,0,0,0};
    uint16_t  isOpenSupported = 0;

    cmeScanProfilesParams_t*    ptrProfilesParam;
    cmeScanSharedInfo_t *pCmeScanDb = scanResultTable_GetCmeScanDbPointer();

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    if (IS_SITE_SRUVEY_SCAN(eScanReqType) == FALSE)
    {
        isOpenSupported = pCmeScanDb->mIsOpenProfileSupported;
    }

    if (eScanReqType == SCAN_REQUEST_CONNECT_PERIODIC_SCAN)
    {
        ptrProfilesParam = &(pCmeScanDb->mPeriodicProfiles);
    }
    else
    {
        ptrProfilesParam = &(pCmeScanDb->mOneShotProfiles);
    }

    //first of all see if result is open security
    //AND open security is allowed
    //AND it is not in the list
    if (    (isOpenSupported)
         && ( (scanInfo->pParsedIEs->capabilities & DOT11_CAPABILITY_PRIVACY) == 0)
       )
    {
        //open profile is allowed and current result has open security!
        //now we need to check if current result is not in the profile list

        uint8_t       profileFound = 0;

        GTRACE(GRP_SCAN_RESULT, "open profile supported and result is open security");

        //check ssid:bssid of the frame is found at the profiles list
        for (i = 0 ; i < ptrProfilesParam->mNumProfiles ; i++)
        {
            //check if ssid is in the list
            if (  (ptrProfilesParam->mpProfiles[i].ssid.mSsidLen > 0) &&
                  (memcmp(ptrProfilesParam->mpProfiles[i].mSSID,
                          scanInfo->pParsedIEs->ssid.serviceSetId,
                          ptrProfilesParam->mpProfiles[i].ssid.mSsidLen) == 0)
               )
            {
                //ssid is in the list. check if the profile has this bssid is in the list or broadcast ssid
                if (    (IRQ_UtilCompareMacAddress (scanInfo->pBssId, ptrProfilesParam->mpProfiles[i].mBssid) ) //MAC is equal
                     || (IRQ_UtilCompareMacAddress (macZero,          ptrProfilesParam->mpProfiles[i].mBssid) ) //MAC is not relevant
                   )
                {
                    //profile exist therefore open profile is not relevant
                    profileFound = 1;
                    break;
                }
            }
        }

        //only if this open profile is not found in the profile list we give him a score of open profile
        if (!profileFound)
        {
            openProfileFound = 1;
            score = score_per_profile_priority[0];
            GTRACE(GRP_SCAN_RESULT, "open profile, score = %d", score);
        }
    }

    //if result is not open security OR open profiles is not supported OR is found in the Profile list
    //use regular logic - if it is in the profile list - give score according to its priority
    if (!openProfileFound)
    {
        //check ssid:bssid of the frame is found at the profiles list
        for (i = 0 ; i < ptrProfilesParam->mNumProfiles; i++)
        {
            //first compare ssid
            if (    memcmp(ptrProfilesParam->mpProfiles[i].mSSID,
                           scanInfo->pParsedIEs->ssid.serviceSetId,
                           ptrProfilesParam->mpProfiles[i].ssid.mSsidLen) == 0
               )
            {
                //ssid is in the list.
                //check if the profile has same bssid or it is broadcast bssid
                if (    (IRQ_UtilCompareMacAddress (scanInfo->pBssId, ptrProfilesParam->mpProfiles[i].mBssid) ) //MAC is equal
                     || (IRQ_UtilCompareMacAddress (macZero,          ptrProfilesParam->mpProfiles[i].mBssid) ) //MAC is not relevant
                   )
                {
                    profilePriority = ptrProfilesParam->mpProfiles[i].ssid.mPriority;

                    //TBD: replace 15 with #define once it will be added
                    ASSERT_GENERAL(profilePriority <= 15);

                    score = score_per_profile_priority[profilePriority + 1];

                    GTRACE(GRP_SCAN_RESULT, "profile found, priority = %d, score = %d", profilePriority, score);
                    break;
                }
                else
                {
                    GTRACE(GRP_SCAN_RESULT, "ssid is matched but bssid is not matching. profile bssid = %8.8X:%4.4X, in bssid = %8.8X:%4.4X",
                           *(uint32_t*)&(ptrProfilesParam->mpProfiles[i].mBssid[0]),
                           *(uint16_t*)&(ptrProfilesParam->mpProfiles[i].mBssid[4]),//mbssid is on aligned address
                           *(uint32_t*)&(scanInfo->pBssId[0]),
                           *(uint16_t*)&(scanInfo->pBssId[4]) );//pBssId is on aligned address
                }
            }
        }
    }

    return score;
}


/*************************************************************************/
// Name:        scan_result_get_score_security
//
// Description: calculate the score of this scan result according to the
//              its security
//
// Callers:     scan_result_calc_weighted_score
//
// Inputs:      scanInfo - scan result information
//              eScanReqType - scan type
//
// Outputs:     none
//
// Return values:   score
/*************************************************************************/
const uint8_t score_per_security_type[] =
{
        0,      /* OPEN SECURITY */
        1       /* SECURED       */
};

uint32_t scan_result_get_score_security(TScanFrameInfo* scanInfo, EScanRequestType  eScanReqType)
{
    uint32_t   score;

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    if ( (scanInfo->pParsedIEs->capabilities & DOT11_CAPABILITY_PRIVACY) != 0)
    {
        //security exist for this device
        score = score_per_security_type[1];
    }
    else
    {
        //security does not exist for this device
        score = score_per_security_type[0];
    }

    GTRACE(GRP_SCAN_RESULT, "capabilities = 0x%X, secure = %d, score = %d",
             scanInfo->pParsedIEs->capabilities,
            (scanInfo->pParsedIEs->capabilities & DOT11_CAPABILITY_PRIVACY),
             score);

    return score;
}



/*************************************************************************/
// Name:        scan_result_calc_weighted_score
//
// Description: calculate the score of this scan result according relevant
//              parameters: rssi, its security proirity and whether open profile is allowed.
//              it is used to prioretize results.
//
// Callers:     scan_result_calc_weighted_score
//
// Inputs:      scanInfo     - scan result information
//              eScanReqType - scan type
//
// Outputs:     none
//
// Return values:   score
/*************************************************************************/
uint32_t scan_result_calc_weighted_score(TScanFrameInfo* scanInfo, EScanRequestType  eScanReqType)
{
    uint32_t      total_score  = 0;
    uint32_t      par_id = 0;
    uint16_t      priority_score, par_score;

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    for(par_id = 0; par_id < NUM_OF_SCAN_RESULT_WEIGHTS; par_id++)
    {
        par_score = g_scan_result_par_score_calc[par_id](scanInfo, eScanReqType);

        if (par_id == SCAN_RESULT_WEIGHT_PROFILE_PRIORITY_INDEX)
        {
            priority_score = par_score;
        }
        total_score  += ( par_score * scan_result_weights[par_id] );
    }

    //for connection scan - score should be zero if device is not in the candidate list
    //for survey scan   - score is relevant even if device is not in the candidate list
    if (eScanReqType != SCAN_REQUEST_SURVEY_SCAN)
    {
        //NOT survey scan --> connection scan

        //if priority score is zero - total score should be zero as well
        //(device is not in the list and therefore is irelevant for connection)
        total_score = total_score * (priority_score > 0);
    }

    GTRACE(GRP_SCAN_RESULT, "ENUM(EScanRequestType,%d), weighted score = %d", eScanReqType, total_score);

    return total_score;
}

// Nov 7 2016 -
//scan early termination threhold routines
//
uint32_t scan_result_calc_highest_score_for_profile_priority(int profile_priority,int secured_profile)
{
    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    ASSERT_GENERAL((secured_profile == 0 || secured_profile == 1) && (profile_priority>=0 && profile_priority<=15));
    uint32_t max_result = SCAN_RESULT_WEIGHT_PROFILE_PRIORITY * score_per_profile_priority[profile_priority+1];//take score for this profile priority
    max_result+= rssi_steps[0].rssi_score;//best rssi score
    max_result+= score_per_security_type[secured_profile];//security

    return max_result;
}

int32_t scan_result_get_best_rssi()
{
    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    return SCAN_RESULT_RSSI_THRESHOLD_GOOD_DEG7;
}

int32_t scan_result_get_good_rssi()
{
    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    return SCAN_RESULT_RSSI_THRESHOLD_DEG1;
}

int32_t scan_result_get_worst_rssi()
{
    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    return SCAN_RESULT_RSSI_THRESHOLD_WORST_DEG3;
}

/******************************************************************************

    FUNCTION:       mx_driver_scan_check_early_termination


    DESCRIPTION:    Check if we can do early termination to scan

    CALLER:         scan_results_process

    PARAMETERS:     pCmeScanDB - pointer to Scan Data block
                    res_rssi - result frame RSSI
                    score  - result calculated score

    RETURNS:        TRUE - needed ET
                    FALSE - no needed ET

******************************************************************************/
Bool_e scan_result_check_early_termination(cmeScanSharedInfo_t*    pCmeScanDB,
                                              int32_t                   res_rssi,
                                              uint32_t                  score)
{
    Bool_e early_terminate = FALSE;

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

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
    return early_terminate;

}
/******************************************************************************

    FUNCTION:       mx_driver_ssid_match


    DESCRIPTION:    Check SSID + BSSID and security type

    CALLER:         scan_results_process

    PARAMETERS:     apSsidIe - pointer to SSID IE in frame
                    apBssid  - pointer to the BSSID in the frame
                    securityType - security type
                    numOfSSID - number of SSID in the list
                    pList - List of the SSID
                    OUT profileId - matching profile ID

    RETURNS:        TRUE  - found match
                    FALSE - SSID and security type unmatched

******************************************************************************/
Bool_e scan_result_ssid_match(dot11_SSID_t*        apSsidIe,
                              uint8_t*             apBssid,
                              uint8_t              securityType,
                              uint8_t              numOfSSID,
                              cmeScanProfiles_t*   pList,
                              int8_t*              profileId)    
{
    int     ssidIndex;
    int     foundMatch = FALSE;
    uint8_t   macZero[6] = {0,0,0,0,0,0};
    char    p2pSSIDPattern[] = "DIRECT-";

    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

   //go over ssid list and check if input ssid is found inside the list
   for (ssidIndex = 0; ssidIndex < numOfSSID; ssidIndex++)
   {
       Bool_e isWep = FALSE; //Match in WEP security
       Bool_e isWPA = FALSE; //Match WPA-only AP with WPA_WPA2
       Bool_e isWPA2 = FALSE; // Match in WPA2 and WPA2 PLUS
       Bool_e isENT = FALSE;
       Bool_e isWPA2_PMF_REQ = FALSE; // Match in WPA2 and WPA2 PLUS WITH PMF REQ
       Bool_e isWPA2_NO_PMF = FALSE; // Match in WPA2 and WPA2 PLUS WITHOUT PMF
       Bool_e isWPA2AESOnly = FALSE; // Match in WPA2 AES only with PMF
       Bool_e isWPA2AESOnly_NO_PMF = FALSE; // Match in WPA2 AES only without PMF
       Bool_e isWPA2WPA3 = FALSE; // Match in WPA2 WPA3
       GTRACE(GRP_DRIVER_MX, "verify scan_result_ssid_match : index (%d) rcv ssid_len %d, list ssid len %d, security type ENUM(CMESecType_e, %d) ssid:" MACSTR " Bssid:" MACSTR ,
                                ssidIndex,
                                //apSsidIe->serviceSetId,
                                apSsidIe->hdr.eleLen,
                                (uint32_t)pList[ssidIndex].ssid.mSsidLen,
                                (CMESecType_e) pList[ssidIndex].secType,
                                MAC2STR(pList[ssidIndex].mSSID),
                                MAC2STR(pList[ssidIndex].mBssid));

        //In case of wep - since can not know at this stage if the remote AP uses open or shared, we pass in either case.
        isWep = (((securityType == CME_SEC_TYPE_WEP) || (securityType == CME_SEC_TYPE_WEP_SHARED)) &&
               ((pList[ssidIndex].secType == CME_SEC_TYPE_WEP) || (pList[ssidIndex].secType == CME_SEC_TYPE_WEP_SHARED))); //We have a match in WEP

       HOOK(HOOK_IN_SCAN_RESULT_TABLE);

       isWPA = ((securityType == CME_SEC_TYPE_WPA) && (pList[ssidIndex].secType == CME_SEC_TYPE_WPA_WPA2));

        //In case the AP is support PMF and we try to connect with WPA2 it is a match
       isWPA2 = (((securityType == CME_SEC_TYPE_WPA_WPA2) || (securityType == CME_SEC_TYPE_WPA2_PLUS) || (securityType == CME_SEC_TYPE_WPA2_WPA3) ||
                  (securityType == CME_SEC_TYPE_WPA2_AES_ONLY_PMF) || (securityType == CME_SEC_TYPE_WPA2_AES_ONLY_NO_PMF)) &&
                 ((pList[ssidIndex].secType == CME_SEC_TYPE_WPA_WPA2) || (pList[ssidIndex].secType == CME_SEC_TYPE_WPA2_PLUS) || (pList[ssidIndex].secType == CME_SEC_TYPE_WPA2_WPA3)));

       isWPA2_PMF_REQ = (((securityType == CME_SEC_TYPE_WPA2_PLUS) || (securityType == CME_SEC_TYPE_WPA2_WPA3) || (securityType == CME_SEC_TYPE_WPA2_AES_ONLY_PMF)) &&
                         ((pList[ssidIndex].secType == CME_SEC_TYPE_WPA2_PLUS) || (pList[ssidIndex].secType == CME_SEC_TYPE_WPA2_WPA3)));

       isWPA2_NO_PMF = (((securityType == CME_SEC_TYPE_WPA_WPA2) || (securityType == CME_SEC_TYPE_WPA2_WPA3) || (securityType == CME_SEC_TYPE_WPA2_AES_ONLY_NO_PMF)) &&
                        ((pList[ssidIndex].secType == CME_SEC_TYPE_WPA_WPA2) || (pList[ssidIndex].secType == CME_SEC_TYPE_WPA2_PLUS) || (pList[ssidIndex].secType == CME_SEC_TYPE_WPA2_WPA3)));

       isWPA2AESOnly = (((securityType == CME_SEC_TYPE_WPA2_AES_ONLY_PMF) || (securityType == CME_SEC_TYPE_WPA2_AES_ONLY_NO_PMF) || (securityType == CME_SEC_TYPE_WPA2_WPA3)) &&
                        ((pList[ssidIndex].secType == CME_SEC_TYPE_WPA2_AES_ONLY_PMF)));

       isWPA2AESOnly_NO_PMF = (((securityType == CME_SEC_TYPE_WPA2_WPA3)) &&
                               ((pList[ssidIndex].secType == CME_SEC_TYPE_WPA2_AES_ONLY_NO_PMF)));

       isWPA2WPA3 = (((securityType == CME_SEC_TYPE_WPA2_WPA3) || (securityType == CME_SEC_TYPE_WPA3)) &&
                     ((pList[ssidIndex].secType == CME_SEC_TYPE_WPA2_WPA3 || pList[ssidIndex].secType == CME_SEC_TYPE_WPA3)));

       // If profile security type is WPA2WPA3 but SAE is not supported then it should not be considered WPA2WPA3.
       // This is to cover the case where the chosen profile security type is WPA2WPA3 but a 64 length psk was used which is valid only for WPA2.
       if ((pList[ssidIndex].secType == CME_SEC_TYPE_WPA2_WPA3) &&
           (gAdHocProfile_ull.uniqueProfileId != CME_INVALID_PROFILE_ID) &&
           ((gAdHocProfile_ull.profile.key_mgmt & WPA_KEY_MGMT_SAE) == 0) &&
           ((gAdHocProfile_ull.profile.key_mgmt & WPA_KEY_MGMT_FT_SAE) == 0))
       {
           isWPA2WPA3 = FALSE;
       }

       // if scan is part of p2p_find() we check that ssid starts with "DIREDT-"
       if (strncmp(apSsidIe->serviceSetId, p2pSSIDPattern, strlen(p2pSSIDPattern)) == 0)
       {
           GTRACE(GRP_DRIVER_MX, "scan_result_ssid_match: Found \"DIRECT-\" ");
           //CME_PRINT_REPORT("scan_result_ssid_match: Found \"DIRECT-\" ");
           foundMatch = TRUE;
           *profileId = pList[ssidIndex].mProfileId;
           break;
       }

        isENT = (securityType == CME_SEC_TYPE_WPA_ENT);
       // compare security type
       // Should be enhanced with key management compare as in wpa_supplicant_ssid_bss_match

       //Filter the result in case the security does not match and we also don't have a match in wep type.
       //In any other case, we have a match and we don't filter the result, we go on and check the ssid or bssid.
      if ((pList[ssidIndex].secType == CME_SEC_TYPE_OPEN) && (securityType != CME_SEC_TYPE_OPEN))
      {
          GTRACE(GRP_DRIVER_MX, "filter scan results:security OPEN  AP security type: ENUM(CMESecType_e, %d), profile security type: ENUM(CMESecType_e, %d), dropping this one",
                                   (CMESecType_e) securityType, (CMESecType_e) pList[ssidIndex].secType);

          continue;
      }
      if ((securityType != pList[ssidIndex].secType) && (!isWep) && (!isWPA) && (!isWPA2) && (!isWPA2WPA3) && (!isENT) && (!isWPA2_PMF_REQ) && (!isWPA2_NO_PMF) && (!isWPA2AESOnly) && (!isWPA2AESOnly_NO_PMF))
      {
          GTRACE(GRP_DRIVER_MX, "Drop filter scan results: AP security type: ENUM(CMESecType_e, %d), profile security type: ENUM(CMESecType_e, %d), dropping this one",
                                    (CMESecType_e) securityType, (CMESecType_e) pList[ssidIndex].secType);

           continue;
      }

       //if ssid length is the same
       if (apSsidIe->hdr.eleLen == pList[ssidIndex].ssid.mSsidLen)
       {
           //if SSID is the same AND BSSID is the same or should be ignored
           if (    (os_memcmp(apSsidIe->serviceSetId, &(pList[ssidIndex].mSSID[0]), apSsidIe->hdr.eleLen) == 0)
                 && (  (IRQ_UtilCompareMacAddress (macZero,pList[ssidIndex].mBssid) ) ||//MAC is not relevant
                         (IRQ_UtilCompareMacAddress (apBssid, pList[ssidIndex].mBssid) ) //MAC is equal
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
                 && (  (IRQ_UtilCompareMacAddress (macZero,pList[ssidIndex].mBssid) ) ||//MAC is not relevant
                         (IRQ_UtilCompareMacAddress (apBssid, pList[ssidIndex].mBssid) ) //MAC is equal
                    )
               )
       {
           foundMatch = TRUE;
           *profileId = pList[ssidIndex].mProfileId;
           break;
       }
   }
   return foundMatch;
}
/*************************************************************************/
// Name:        scan_result_get_probe_req_extra_ie
//
// Description: get extra IE to add to probe request of one shot / periodic scan
//
// Callers:
//
// Inputs:      none
//
// Outputs:     extraIeLen      - extra IE length
//              pExtraIe        - extra IE Buffer
//
// Return values:   score
/*************************************************************************/
#ifdef COMPILE_DEAD_FUNC
void    scan_result_get_probe_req_extra_ie(uint16_t*  extraIeLen, uint8_t** pExtraIe)
{
    HOOK(HOOK_IN_SCAN_RESULT_TABLE);

    //get extra IE information
    *extraIeLen = (uint16_t)ScanResultTable.cmeScanDb.mpExtraIesInfo->extraIesLength;
    *pExtraIe   =         ScanResultTable.cmeScanDb.mpExtraIesInfo->pExtraIesBuffer;
}
#endif
