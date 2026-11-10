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
/** \file mlmeParser.h
 *  \brief 802.11 MLME Parser
 *
 *  \see mlmeParser.c
 */

#include <public_types.h>


/***************************************************************************/
/*																		   */
/*		MODULE:	mlmeParser.h											   */
/*    PURPOSE:	802.11 MLME Parser										   */
/*																	 	   */
/***************************************************************************/

#ifndef _MLME_PARSER_H
#define _MLME_PARSER_H

#include "802_11defs.h"
#include "paramOut.h"
#include "osi_kernel.h"

/* Constants */
/*
#define FRAME_CTRL_PROTOCOL_VERSION_MASK	0x03
#define FRAME_CTRL_TYPE_MASK				0x0C
#define FRAME_CTRL_SUB_TYPE_MASK			0xF0
*/
//#define MLME_LOG
#ifdef MLME_LOG
#define MLME_REPORT_PRINT  Report
#define MLME_ERROR_PRINT   Report
#define MLME_REPORT_PRINT_ERROR Report
#else
#define MLME_REPORT_PRINT(...)
#define MLME_REPORT_PRINT_ERROR Report
#endif

//#define MLME_LOG_PARSER
#ifdef MLME_LOG_PARSER
#define MLME_REPORT_PRINT_PARSER  Report
#define MLME_ERROR_PRINT_PARSER   Report
#else
#define MLME_REPORT_PRINT_PARSER(...)
#endif


#define MLME_ERROR_PRINT_LOG
#ifdef MLME_ERROR_PRINT_LOG
#define MLME_ERROR_PRINT  Report
#else
#define MLME_ERROR_PRINT(...)
#endif


#define MAX_MGMT_FRAME_BODY_LEN 2032
/* Enumerations */
#define MAX_IES_NUMBER               32
#define MAX_MULTIPLE_BSSID_IE_NUMBER 1024  //bytes
#define NONTRANSMITTED_BSSID_PROFILE 0x0


typedef enum
{
    MSG_BROADCAST,
    MSG_MULTICAST,
    MSG_UNICAST
} mlmeMsgDestType_t;

/* state machine states */

/* Typedefs */
/* This struct is used for ROAMING_TRIGGER_AP_DISCONNECT */
typedef struct
{
    uint16_t uStatusCode;      /* status code of deauth/disassoc packet                   */
    Bool32   bDeAuthenticate;  /* Whether this packet is DeAuth ( if DisAssoc than TI_FALSE) */
} APDisconnect_t;

typedef union
{
    APDisconnect_t APDisconnect;
//    tiwdrv_rate_e  rate;
} roamingEventData_u;
/* Disassociation frame structure */
typedef struct
{
    uint16_t                   reason;
    //roamingEventData_u          eventData;/**/
}  disAssoc_t;

/* Authentication message frame structure */
typedef struct
{
    uint16_t                   authAlgo;//auth_alg
    uint16_t                   seqNum;  //auth_transaction
    uint16_t                   status;  //status_code
    dot11_CHALLENGE_t        *pChallenge;//variable[0]
}  authMsg_t;


/* DeAuthentication message frame structure */
typedef struct
{
    uint16_t                   reason;
    //roamingEventData_u          eventData;
}  deAuth_t;

/* Action message frame structure */
typedef struct
{
    uint8_t                    frameType;
    uint8_t                    category;
    uint8_t                    action;
    uint8_t                    *pData;
    uint32_t                   uDataLen;
} action_t;


typedef struct
{
    dot11MgmtSubType_e subType;

    union
    {
 /*       beacon_probeRsp_t iePacket;*/
        disAssoc_t  disAssoc;
/*        assocRsp_t  assocRsp;*/
        authMsg_t   auth;
        deAuth_t    deAuth;
        action_t    action;
    } content;

    union
    {
        mlmeMsgDestType_t   destType;
    } extesion;

} mlmeFrameInfo_t;

typedef struct
{
    dot11_SSID_t            ssid;
    Bool32                 ssidIePresent;
    macAddress_t            bssid;
    macAddress_t            dest;
    macAddress_t            src;
    dot11_CHALLENGE_t       challenge;
    dot11_RATES_t           rates;
    dot11_RATES_t           extRates;
    dot11_FH_PARAMS_t       fhParams;
    dot11_CF_PARAMS_t       cfParams;
    dot11_DS_PARAMS_t       dsParams;
    dot11_IBSS_PARAMS_t     ibssParams;
    dot11_COUNTRY_t         country;
    dot11_WME_PARAM_t       WMEParams;
    dot11_WSC_t             WSCParams;
    dot11_POWER_CONSTRAINT_t powerConstraint;
    dot11_CHANNEL_SWITCH_IE_t  channelSwitch;
    dot11_QUIET_t           quiet;
    dot11_TPC_REPORT_t      TPCReport;
#ifdef CCX_MODULE_INCLUDED
    dot11_CELL_TP_t         cellTP;
    CCXv4IEs_t                ccxIEs[MAX_NUM_OF_AC];
#endif /* CCX_MODULE_INCLUDED */
    dot11_RSN_t             rsnIe[3];
    dot11_TIM_t             tim;
    dot11_QOS_CAPABILITY_IE_t   QosCapParams;
    dot11HtCapabilitiesUnparse_t tHtCapabilities;
    dot11HtInformationUnparse_t  tHtInformation;

    dot11_RM_ENABLED_CAPABILITIES_IE_t  tRRMEnabledCap;
    dot11_MOBILITY_DOMAIN_IE_t          tMobilityDomain;
    dot11_FAST_TRANSITION_IE_t          tFastTransition;
    dot11_NEIGHBOR_REPORT_IE_t          tNeighborReport;

    uint8_t                rxChannel;
    uint8_t                band;

    Bool32                 recvChannelSwitchAnnoncIE;

    uint8_t                unknownIe[MAX_BEACON_BODY_LENGTH];
    uint16_t               unknownIeLen;


    uint16_t capabilities;
    uint16_t useProtection;
    Bool32   ciscoIePresent;
    EPreamble barkerPreambleMode;
    uint8_t  nonErpPresent;
    uint8_t  rsnIeLen;

    uint16_t status;
    uint16_t aid;
    uint8_t  *tspecVoiceParameters;
    uint8_t  *tspecVideoParameters;

    char      timeStamp[TIME_STAMP_LEN];
    uint16_t beaconInterval;

    uint8_t                    *pData;
    uint32_t                   uDatalen;
    Bool32                 P2PDEviceMgmtPresent;

    mlmeFrameInfo_t         frame;
}mlmeIEParsingParams_t;


typedef struct
{
    uint8_t                   *pData;
    uint32_t                  uDatalen;

    uint16_t                  beaconInterval;
    uint16_t                  capabilities;

    uint8_t                   bssid[MAC_ADDR_LEN];

    // If this is a non-transmitting bssid then its info (beacon / probe reposnse) 
    // are transmitted by transmittingBssid
    Bool_e                    nonTransmittingBssid; 
    uint8_t                   transmittingBssid[MAC_ADDR_LEN];
    uint8_t                   *nonTransmittingBssidIeBuffer;
    uint8_t                   nonTransmittingBssidIeBufferLength; 
    uint8_t                   mbssidIndex;
    uint8_t                   mbssidIndicator; 

    uint8_t                   rxChannel;      //taken from the descriptor
    Bool_e                    ssidIePresent;
    Bool_e                    ratesIePresent;
    Bool_e                    extRatesIePresent;
    Bool_e                    htCapabilitiesPresent;
    Bool_e                    htInformationPresent;
    Bool_e                    vhtCapabilitesPresent;
    Bool_e                    pbacApEnabled;
    uint8_t                   rsnIeLen;//the len includes the header
    uint8_t                   wpaIeLen;
    uint8_t                   rsnOverrideIeLen;
    uint8_t                   rsnOverride2IeLen;
    uint16_t                  wpsLen;

    dot11_COUNTRY_t         country;
    dot11_SSID_t            ssid;
    dot11_RATES_t           rates;
    dot11_RATES_t           extRates;
    dot11_DS_PARAMS_t       dsParams;
    dot11_RSN_t             rsnIe;
    dot11_RSN_t             wpaIe; //It is wrong to use dot11_WPA_IE_t since it assumes only one pairwaise suite and one auth key suite
    dot11_RSN_t             rsnOverrideIe;
    dot11_RSN_t             rsnOverride2Ie;
    dot11_wps_t             wpsIe;
    dot11HtCapabilitiesUnparse_t htCapabilities;
    dot11HtInformationUnparse_t  htInformation;
    dot11HeCapabilitiesUnparse_t heCapabilities;
    dot11HeOperationUnparse_t    heOperation;
    dot11HeMuEdcaAcParams_t      heMuEdcaAcParams;

    Bool_e                  heCapabilitiesPresent;
    Bool_e                  heOperationPresent;
    Bool_e                  heMuEdcaAcParamsPresent;
    Bool_e                  wmmPresent;
    Bool_e                  wpsPresent;
    dot11_erp_t             erpIe;
    Bool_e                  erpPresent;
    uint8_t                 useProtection; //erp capabilities
    uint8_t/*EPreamble*/    barkerPreambleMode; //erp capabilities
} scanIEParsingParams_t;



typedef struct
{
    uint8_t MaxBSSIDIndicator;      //Max BSSID Indicator - from the IE data.
    uint8_t SubElementIndex;        //Index of multiple BSSID sub elements
    uint8_t *pSubElementData;       //Pointer to the next subelements to parse 
    Bool_e  moreSubElementsLeft;    //Indication if we have more sub elements to find
    uint8_t subElementLength;       //length of the sub element that we found
}scanIEMultiBSSIDParams_t;

/* Structures */

/* External data definitions */

/* External functions definitions */

/* Function prototypes */
/**
 * \fn     mlmeParser_create
 * \brief  create mlmeParser module
 */
//void * mlmeParser_Create(void * hOs);
//
///**
// * \fn     mlmeParser_destroy
// * \brief  destroy mlmeParser module
// */
//int32_t mlmeParser_Destroy(void * hMlmeParser);
//
///**
// * \fn     mlmeParser_Init
// * \brief  init mlmeParser module
// */
//void mlmeParser_Init (TModuleHandleTable *pUwdHandles);
//
///**
// * \fn     mlmeParser_SetDefaults
// * \brief  set defaults mlmeParser module
// */
//void mlmeParser_SetDefaults (void * hMlmeParser, TMlmeParserInitParams *pMlmeParserInitParams);
//
/**
 * \fn     mlmeParser_parseFrame
 * \brief  parse an entire received frame. The frame must start with a
 *         RxIfDescriptor_t describing it (length, flags etc.). The parsed
 *         frame will be output into params. The caller is responsible for
 *         allocating params.
 */
int32_t mlmeParser_parseFrame(void * hMlmeParser, void *pFrame,
                                mlmeIEParsingParams_t *params);

/**
 * \fn     mlmeParser_parseIEs
 * \brief  parse IE data into IEs. The parsed data will be output into params.
 *         The caller is responsible for allocating params.
 */
int32_t mlmeParser_parseIEs(void * hMlmeParser,
                              uint8_t *pData,
                              int32_t bodyDataLen,
                              mlmeIEParsingParams_t *params);


uint8_t mlmeParser_calcBssidNonTx(uint8_t *bssid, uint8_t subElementIndex, uint8_t maxBssidIndicator);
int32_t scanParser_parseFrame(dot11_mgmtFrame_t *pMgmtFrame, scanIEParsingParams_t *params, uint16_t length, scanIEMultiBSSIDParams_t *multiBSSIDParsingParams);
int32_t scanParser_parseIEs(uint8_t *pData, scanIEParsingParams_t *params, uint8_t *pDataEnd, uint16_t leftDataLen, scanIEMultiBSSIDParams_t *multiBSSIDParsingParams);
uint8_t* scanParser_findMbssidSubElement(uint8_t *pData, uint16_t len, uint8_t mbssidIndex);
int32_t scanParser_findNextMbssidSubElement(uint8_t *pData, uint16_t len, scanIEMultiBSSIDParams_t *multiBSSIDParsingParams);

int32_t mlmeParser_readWMEParams(const uint8_t *apWmmData, dot11_WME_PARAM_t *apWMEParamIE);
int32_t mlmeParser_readWSCParams(const uint8_t *apWmmData, dot11_WSC_t *apWSC_IE);

uint32_t mlmeParser_MbssidSubEleBufferPrep(dot11_mgmtFrame_t *frame_msg_buff, int32_t frameLengthWithoutDescr , scanIEMultiBSSIDParams_t *multiBSSIDParsingParams);
Bool_e mlmeParser_getMoreSubelementsLeft(scanIEMultiBSSIDParams_t *pMBSSID);
void mlmeParser_SetMoreSubelementsLeft(scanIEMultiBSSIDParams_t *pMBSSID, Bool_e SubEleLeft);
Bool_e scanParser_CheckMbssidSupport(uint8_t *pData, uint16_t len);

///**
// * \fn     mlmeParser_ParseIEBuffer
// * \brief  find a desired IE in an IE buffer. The match buffer can
// *         optionally be returned via pMatchBuffer.
// */
//Bool32 mlmeParser_ParseIeBuffer(void * hOs,
//                                 uint8_t *pIeBuffer,
//                                 uint32_t length,
//                                 uint8_t desiredIeId,
//                                 uint8_t **pDesiredIe,
//                                 uint8_t *pMatchBuffer,
//                                 uint32_t matchBufferLen);
//
//#ifdef CCX_MODULE_INCLUDED
///**
// * \fn     mlmeParser_readCcxOui
// * \brief  parse the CCX OUI inside an IE buffer. Return result
// *         in a CCXv4IEs_t struct
// */
//void mlmeParser_readCcxOui (uint8_t *pData,
//                            uint32_t dataLen,
//                            uint32_t *pReadLen,
//                            CCXv4IEs_t *ccxIEs);
//#endif /* CCX_MODULE_INCLUDED */
#endif


