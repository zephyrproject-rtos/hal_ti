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
/** \file mlmeBuilder.c
 * MLME Stands for Media Access Control (MAC) Sublayer Management Entity
 *  \brief 802.11 MLME Parser
 *
 *  \see mlmeParser.h
 */


/***************************************************************************/
/*                                                                         */
/*      MODULE: mlmeParser.c                                              */
/*    PURPOSE:  802.11 MLME Parser                                        */
/*                                                                         */
/***************************************************************************/



//#define __FILE_ID__  FILE_ID_42
#include "mlme_parser.h"

#include "regulatory_domain_api.h"
#include "gtrace.h"
#include "ie_parser_util.h"

#include "common.h"
#include "wpa_common.h"   // for security definitions
#include "ieee802_11_defs.h"
#include "l2_cfg.h"
/* Constants */

#define CHECK_PARSING_ERROR_CONDITION_PRINT 0

/* Enumerations */

/* Typedefs */

/* Structures */
typedef struct
{

    /* Module's handles*/
    void *               hReport;
    void *               hOs;
    void *               hRegulatoryDomain;

    Bool32                  bParseBeaconWSC;
} TMlmeParser;
/* External data definitions */

//extern int WMEQosTagToACTable[MAX_NUM_OF_802_1d_TAGS];

/* External functions definitions */

/* Local function prototypes */

//static int32_t parseBeaconProbeRsp(TMlmeParser *pMlmeParser, void *pBuffer,
//                                     uint8_t *pData, dot11_mgmtFrame_t *pMgmtFrame,
//                                     mlmeIEParsingParams_t *params);
//static int32_t parseAssocRsp(TMlmeParser *pMlmeParser, void *pBuffer,
//                               uint8_t *pData, dot11_mgmtFrame_t *pMgmtFrame,
//                               uint32_t bodyDataLen,
//                               mlmeIEParsingParams_t *params);
//
//static int32_t mlmeParser_getFrameType(TMlmeParser *pMlme,
//                               uint16_t* pFrameCtrl,
//                               dot11MgmtSubType_e *pType);
//
static int32_t mlmeParser_readRates(uint8_t *pData,
                                  uint32_t dataLen,
                                  uint32_t *pReadLen,
                                  dot11_RATES_t *pRates);

static int32_t mlmeParser_readERP( uint8_t *pData,
                             uint32_t dataLen,
                             uint32_t *pReadLen,
                             dot11_erp_t *pErpIe,
                             uint8_t *useProtection,
                             uint8_t *barkerPreambleMode);
//
//static int32_t mlmeParser_readSsid(TMlmeParser *pMlmeParser,
//                           uint8_t *pData,
//                           uint32_t dataLen,
//                           uint32_t *pReadLen,
//                           dot11_SSID_t *pSsid);
//
//static int32_t mlmeParser_readFhParams(TMlmeParser *pMlmeParser,
//                               uint8_t *pData,
//                               uint32_t dataLen,
//                               uint32_t *pReadLen,
//                               dot11_FH_PARAMS_t *pFhParams);
//
//static int32_t mlmeParser_readDsParams(TMlmeParser *pMlmeParser,
//                               uint8_t *pData,
//                               uint32_t dataLen,
//                               uint32_t *pReadLen,
//                               dot11_DS_PARAMS_t *pDsParams);
//
//static int32_t mlmeParser_readCfParams(TMlmeParser *pMlmeParser,
//                               uint8_t *pData,
//                               uint32_t dataLen,
//                               uint32_t *pReadLen,
//                               dot11_CF_PARAMS_t *pCfParams);
//
//static int32_t mlmeParser_readIbssParams(TMlmeParser *pMlmeParser,
//                                 uint8_t *pData,
//                                 uint32_t dataLen,
//                                 uint32_t *pReadLen,
//                                 dot11_IBSS_PARAMS_t *pIbssParams);
//
//static int32_t mlmeParser_readTim(TMlmeParser *pMlmeParser,
//                          uint8_t *pData,
//                          uint32_t dataLen,
//                          uint32_t *pReadLen,
//                          dot11_TIM_t *pTim);
//
//static int32_t mlmeParser_readCountry(TMlmeParser *pMlmeParser,
//                                 uint8_t *pData,
//                                 uint32_t dataLen,
//                                 uint32_t *pReadLen,
//                                 dot11_COUNTRY_t *countryIE);
//
//static int32_t mlmeParser_readWMEParams(TMlmeParser *pMlmeParser,
//                                   uint8_t *pData,
//                                   uint32_t dataLen,
//                                   uint32_t *pReadLen,
//                                   dot11_WME_PARAM_t *pWMEParamIE,
//                                   mlmeIEParsingParams_t *assocRsp);
//
//static int32_t mlmeParser_readPowerConstraint(TMlmeParser *pMlmeParser,
//                                         uint8_t *pData,
//                                         uint32_t dataLen,
//                                         uint32_t *pReadLen,
//                                         dot11_POWER_CONSTRAINT_t *powerConstraintIE);
//
//static int32_t mlmeParser_readChannelSwitch(TMlmeParser *pMlmeParser,
//                                       uint8_t *pData,
//                                       uint32_t dataLen,
//                                       uint32_t *pReadLen,
//                                       dot11_CHANNEL_SWITCH_t *channelSwitch,
//                                       uint8_t channel);
//
//static int32_t mlmeParser_readTPCReport(TMlmeParser *pMlmeParser,
//                                   uint8_t *pData,
//                                   uint32_t dataLen,
//                                   uint32_t *pReadLen,
//                                   dot11_TPC_REPORT_t   *TPCReport);
//
//#ifdef CCX_MODULE_INCLUDED
//static int32_t mlmeParser_readCellTP(TMlmeParser *pMlmeParser,
//                                uint8_t *pData,
//                                uint32_t dataLen,
//                                uint32_t *pReadLen,
//                                dot11_CELL_TP_t *cellTP);
//#endif /* CCX_MODULE_INCLUDED */
//
//static int32_t mlmeParser_readQuiet(TMlmeParser *pMlmeParser,
//                               uint8_t *pData,
//                               uint32_t dataLen,
//                               uint32_t *pReadLen,
//                               dot11_QUIET_t *quiet);
//
//static int32_t mlmeParser_readChallange(TMlmeParser *pMlmeParser,
//                                uint8_t *pData,
//                                uint32_t dataLen,
//                                uint32_t *pReadLen,
//                                dot11_CHALLENGE_t *pChallange);
//
//
//static int32_t mlmeParser_readRsnIe(TMlmeParser *pMlmeParser,
//                               uint8_t *pData,
//                               uint32_t dataLen,
//                               uint32_t *pReadLen,
//                               dot11_RSN_t *pRsnIe);
//
//static int32_t mlmeParser_readQosCapabilityIE(TMlmeParser *pMlmeParser,
//                                         uint8_t *pData,
//                                         uint32_t dataLen,
//                                         uint32_t *pReadLen,
//                                         dot11_QOS_CAPABILITY_IE_t *QosCapParams);
//
static int32_t mlmeParser_readHtCapabilitiesIE (uint8_t *pData,
                                              uint32_t dataLen,
                                              uint32_t *pReadLen,
                                              dot11HtCapabilitiesUnparse_t *pHtCapabilities);

static int32_t mlmeParser_readHtInformationIE (uint8_t *pData,
                                             uint32_t dataLen,
                                             uint32_t *pReadLen,
                                             dot11HtInformationUnparse_t *pHtInformation);

static int32_t mlmeParser_parseExtension       (uint8_t *pData,
                                              uint16_t bodyDataLen,
                                              uint32_t *pReadLen,
                                              scanIEParsingParams_t *pParams);

#ifndef DISABLE_WIFI6
static int32_t mlmeParser_readHeCapabilitiesIE(uint8_t *pData,
                                             uint16_t dataLen,
                                             uint32_t *pReadLen,
                                             dot11HeCapabilitiesUnparse_t *pHtCapabilities);

static int32_t mlmeParser_readHeOperationIE   (uint8_t *pData,
                                             uint16_t dataLen,
                                             uint32_t *pReadLen,
                                             dot11HeOperationUnparse_t *pHtCapabilities);


static int32_t mlmeParser_readHeMuEdcaParamerterSetIE(uint8_t *pData, 
                                                    uint16_t dataLen,
                                                    uint32_t *pReadLen, 
                                                    dot11HeMuEdcaAcParams_t *pHeMuEdcaAcParams);
#endif

//static int32_t mlmeParser_readRMEnabledCapIE(TMlmeParser *pMlmeParser,
//                                        uint8_t *pData,
//                                        uint32_t dataLen,
//                                        uint32_t *pReadLen,
//                                        dot11_RM_ENABLED_CAPABILITIES_IE_t *pRMEnabledCap);
//
//
//static int32_t mlmeParser_readMobilityDomain(TMlmeParser *pMlme,
//                                        uint8_t *pData,
//                                        uint32_t dataLen,
//                                        uint32_t *pReadLen,
//                                        dot11_MOBILITY_DOMAIN_IE_t *pMobilityDomain);
//
//static int32_t mlmeParser_readFastTransition(TMlmeParser *pMlmeParser,
//                                        uint8_t *pData,
//                                        uint32_t dataLen,
//                                        uint32_t *pReadLen,
//                                        dot11_FAST_TRANSITION_IE_t *pFastTranstion);
//
//static int32_t mlmeParser_readP2PParams(TMlmeParser *pMlme,uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, TI_BOOL* mgmtBit);
//
//static uint32_t mlmeParser_getWSCReadLen(uint8_t *pData);
//
//static int32_t mlmeParser_readWSCParams(TMlmeParser *pMlme,
//                                          uint8_t *pData,
//                                          uint32_t dataLen,
//                                          uint32_t *pReadLen,
//                                          dot11_WSC_t *pWSC_IE);

/* Functions */

/**
 * \fn     mlmeParser_create
 * \brief  create mlmeParser module
 */
//void * mlmeParser_Create(void * hOs)
//{
//    TMlmeParser   *pMlmeParser;
//
//    if ((pMlmeParser = os_memoryAlloc(hOs, sizeof(TMlmeParser))) != NULL)
//    {
//        pMlmeParser->hOs = hOs;
//
//        return pMlmeParser;
//    }
//    else /* Failed to allocate control block */
//    {
//        WLAN_OS_REPORT(("FATAL ERROR: mlmeParser_create(): Error allocating cb - aborting"));
//        return NULL;
//    }
//}
///**
// * \fn     mlmeParser_destroy
// * \brief  destroy mlmeParser module
// */
//int32_t mlmeParser_Destroy(void * hMlmeParser)
//{
//    TMlmeParser   *pMlmeParser;
//
//    if (hMlmeParser != NULL)
//    {
//        pMlmeParser = (TMlmeParser *)hMlmeParser;
//
//        /* Free pre-allocated control block */
//        os_memoryFree(pMlmeParser->hOs, pMlmeParser, sizeof(TMlmeParser));
//    }
//    return OK;
//}
//
///**
// * \fn     mlmeParser_Init
// * \brief  init mlmeParser module
// */
//void mlmeParser_Init (TModuleHandleTable *pUwdHandles)
//{
//    TMlmeParser *pMlmeParser = (TMlmeParser *)(pUwdHandles->hMlmeParser);
//
//    os_memorySet(pMlmeParser->hOs, pMlmeParser, 0, sizeof(TMlmeParser));
//
//    pMlmeParser->hOs               = pUwdHandles->hOs;
//    pMlmeParser->hReport           = pUwdHandles->hReport;
//    pMlmeParser->hRegulatoryDomain = pUwdHandles->hRegulatoryDomain;
//
//
//}
//
///**
// * \fn     mlmeParser_SetDefaults
// * \brief  set defaults mlmeParser module
// */
//void mlmeParser_SetDefaults (void * hMlmeParser, TMlmeParserInitParams *pMlmeParserInitParams)
//{
//    TMlmeParser *pMlmeParser = (TMlmeParser*)hMlmeParser;
//
//    pMlmeParser->bParseBeaconWSC = pMlmeParserInitParams->parseWSCInBeacons;
//}

//int32_t mlmeParser_parseFrame(void * hMlmeParser, void *pBuffer,
//                                mlmeIEParsingParams_t *params)
//{
//    int32_t              status =-1;
//    TMlmeParser            *pHandle = (TMlmeParser *)hMlmeParser;
//    uint8_t               *pData;
//    int32_t               bodyDataLen;
//    uint32_t              readLen;
////    const RxIfDescriptor_t *desc = pBuffer;
//
//    dot11_mgmtFrame_t      *pMgmtFrame;
//    dot11MgmtSubType_e     msgType;
//
//    if ((hMlmeParser == NULL) || (pBuffer == NULL) || (params == NULL))
//    {
//        GTRACE(GRP_GENERAL_ERROR, "mlmeParser_parseFrame: hMlme == %x, buf = %x, params = %x",
//                        (uint32_t)hMlmeParser,
//                        (uint32_t)pBuffer, (uint32_t)params);
//		return-1;
//    }
//
//    /* zero frame content */
//	ZeroMem(params, sizeof(mlmeIEParsingParams_t));
//
////TODO: to set RX_BUF_DATA
////    pMgmtFrame = (dot11_mgmtFrame_t*)RX_BUF_DATA(pBuffer);
//
//    /* length of body (BUF without 802.11 header and FCS) */
////    if (RX_BUF_LEN(pBuffer) < WLAN_HDR_LEN)
////    {
////        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: Body length is too short (%d)!", RX_BUF_LEN(pBuffer));
////        return-1;
////    }
////    bodyDataLen = RX_BUF_LEN(pBuffer) - WLAN_HDR_LEN;
//
//    /* get frame type */
//    status = mlmeParser_getFrameType(pHandle, (uint16_t *)&pMgmtFrame->hdr.fc, &msgType);
//    if (status != OK)
//    {
//        return-1;
//    }
//
//    params->frame.subType = msgType;
//
//    /* check destination MAC address for broadcast */
//    if (MAC_BROADCAST (pMgmtFrame->hdr.DA))
//    {
//        params->frame.extesion.destType = MSG_BROADCAST;
//    }
//    else
//    {
//        if (MAC_MULTICAST (pMgmtFrame->hdr.DA))
//        {
//            params->frame.extesion.destType = MSG_MULTICAST;
//        }
//        else
//        {
//            params->frame.extesion.destType = MSG_UNICAST;
//        }
//    }
//
//    /* save addresses */
//    MAC_COPY(params->dest,  pMgmtFrame->hdr.DA);
//    MAC_COPY(params->src,   pMgmtFrame->hdr.SA);
//    MAC_COPY(params->bssid, pMgmtFrame->hdr.BSSID);
//
//    pData = (uint8_t *)(pMgmtFrame->body);
//
//    switch (msgType)
//    {
//    case ASSOC_REQUEST:
//        GTRACE(GRP_MLME, "MLME_PARSER: recieved ASSOC_REQ message");
//        break;
//    case RE_ASSOC_REQUEST:
//        GTRACE(GRP_MLME, "MLME_PARSER: recieved RE_ASSOC_REQ message");
//        break;
//    case RE_ASSOC_RESPONSE:
//        GTRACE(GRP_MLME, "MLME_PARSER: recieved RE_ASSOC_RSP message");
//
//    case ASSOC_RESPONSE:
//        status = parseAssocRsp(pHandle, pBuffer, pData, pMgmtFrame, bodyDataLen, params);
//        break;
//
//    case PROBE_REQUEST:
//        GTRACE(GRP_MLME, "MLME_PARSER: recieved PROBE_REQ message");
//        break;
//
//    case PROBE_RESPONSE:
//
//    case BEACON:
//    {
//        status = parseBeaconProbeRsp(pHandle, pBuffer, pData, pMgmtFrame, params);
//
//        break;
//    }
//
//    case ATIM:
//        GTRACE(GRP_MLME, "MLME_PARSER: recieved ATIM message");
//        break;
//    case DIS_ASSOC:
//        /* read Reason interval */
//	    COPY_WLAN_WORD(&params->frame.content.disAssoc.reason , pData);
//
//	    params->frame.content.disAssoc.eventData.APDisconnect.uStatusCode = params->frame.content.disAssoc.reason;
//	    params->frame.content.disAssoc.eventData.APDisconnect.bDeAuthenticate = TI_FALSE;
//
//	    status = OK;
//
//        break;
//
//    case AUTH:
//        /* read Algorithm interval */
//	    COPY_WLAN_WORD(&params->frame.content.auth.authAlgo , pData);
//        pData += 2;
//        /* read Sequence number */
//	    COPY_WLAN_WORD(&params->frame.content.auth.seqNum , pData);
//        pData += 2;
//        /* read status */
//	    COPY_WLAN_WORD(&params->frame.content.auth.status , pData);
//        pData += 2;
//
//        GTRACE(GRP_MLME, "MLME_PARSER: Read Auth: algo=%d, seq=%d, status=%d", params->frame.content.auth.authAlgo, params->frame.content.auth.seqNum, params->frame.content.auth.status);
//        bodyDataLen -= 6;
//        /* read Challenge */
//        params->frame.content.auth.pChallenge = &(params->challenge);
//
//        mlmeParser_parseIEs(pHandle, pData, bodyDataLen, params);
//
//
//        status = OK;
//
//        break;
//    case DE_AUTH:
//        /* read Reason */
//	    COPY_WLAN_WORD(&params->frame.content.deAuth.reason , pData);
//
//	    params->frame.content.deAuth.eventData.APDisconnect.uStatusCode = params->frame.content.disAssoc.reason;
//	    params->frame.content.deAuth.eventData.APDisconnect.bDeAuthenticate = TRUE;
//
//	    status = OK; /* dispatching outside of this function*/
//
//        break;
//
//    case ACTION:
//        /* Verify that the length includes all constant fields (category, action, token & status) */
//        if (bodyDataLen < 4)
//        {
//            break;
//        }
//
//        /* read Category field */
//        params->frame.content.action.category = *pData;
//        pData ++;
//        bodyDataLen --;
//
//		params->frame.content.action.action = *pData;
//		pData ++;
//		bodyDataLen --;
//
//        params->frame.content.action.pData =pData;
//        params->frame.content.action.uDataLen = bodyDataLen;
//
//		status = OK;
//
//		switch(params->frame.content.action.category)
//		{
//			case CATAGORY_QOS:
//			case WME_CATAGORY_QOS:
//			    break;
//
//			case CATAGORY_SPECTRUM_MANAGEMENT:
//				/* read action field */
//
//
//				switch(params->frame.content.action.action)
//				{
////					case MEASUREMENT_REQUEST:
////						/* Checking the frame type  */
////						if(params->frame.extesion.destType == MSG_BROADCAST)
////							params->frame.content.action.frameType = MSR_FRAME_TYPE_BROADCAST;
////						else
////							params->frame.content.action.frameType = MSR_FRAME_TYPE_UNICAST;
////
////						break;
//
//					case TPC_REQUEST:
//						break;
////TODO: to add desc
////					case CHANNEL_SWITCH_ANNOUNCEMENT:
////							mlmeParser_readChannelSwitch(pHandle,pData,bodyDataLen,&readLen,&(params->channelSwitch),
////								desc->channel);
////						break;
//
//					default:
//                        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: Error, category is invalid for action management frame %d",params->frame.content.action.category );
//						status =-1;
//                        break;
//				}
//
//				break;
//			case CATEGORY_RRM:
//
//
//                params->frame.content.action.pData -=2;
//                params->frame.content.action.uDataLen -=2;
//
//
//                switch(params->frame.content.action.action)
//                {
////                case RRM_MEASUREMENT_REQUEST:
//                /* case LINK_MEASUREMENT_REQUEST: */
//
////                    if(params->frame.extesion.destType == MSG_BROADCAST)
////							params->frame.content.action.frameType = MSR_FRAME_TYPE_BROADCAST;
////						else
////							params->frame.content.action.frameType = MSR_FRAME_TYPE_UNICAST;
////                     GTRACE(GRP_MLME, "mlmeParser_parseFrame: Radio Measurement Request Received - Beacon/TSM Measurement type");
////                     break;
//
//                case NEIGHBOR_MEASUREMENT_REPORT:
//                    GTRACE(GRP_MLME, "mlmeParser_parseFrame: Neighbor Measurement Report Received");
//                    break;
//
//                default:
//                    GTRACE(GRP_MLME, "mlmeParser_parseFrame: Measurement Request/Report type is not recognized!");
//                }
//
//                break;
//			default:
//				status =-1;
//				break;
//
//		}
//
//    }
//
//    return status;
//}

#if CHECK_PARSING_ERROR_CONDITION_PRINT
#define CHECK_PARSING_ERROR_CONDITION(x, msg, bDump)	   \
        if ((x)) \
        { \
            TRACE(pHandle->hReport, REPORT_SEVERITY_ERROR, msg);    \
            if (bDump) {\
                TRACE(pHandle->hReport, REPORT_SEVERITY_ERROR, "Buff len = %d ", packetLength);    \
                report_PrintDump (pPacketBody, packetLength); }\
                return-1; \
        }
#else
#define CHECK_PARSING_ERROR_CONDITION(x, msg, bDump) \
        if ((x)) return-1;
#endif

//int32_t mlmeParser_parseIEs(void * hMlmeParser,
//							  uint8_t *pData,
//							  int32_t bodyDataLen,
//							  mlmeIEParsingParams_t *params)
//{
//    dot11_eleHdr_t 		*pEleHdr;
//    uint32_t 			 readLen = 0;
//	int32_t			 status =-1;
//    uint8_t 			 rsnIeIdx = 0;
//    uint8_t 			 wpaIeOuiIe[4] = { 0x00, 0x50, 0xf2, 0x01};
//    mlmeIEParsingParams_t 	*frame = params;
//	TMlmeParser				*pHandle = (TMlmeParser *)hMlmeParser;
////#ifdef CCX_MODULE_INCLUDED
////	TI_BOOL				allowCellTP = TRUE;
////#endif /* CCX_MODULE_INCLUDED */
////#if CHECK_PARSING_ERROR_CONDITION_PRINT
////	int32_t				packetLength = bodyDataLen;
////	uint8_t				*pPacketBody = pData;
////#endif
//
//
//	params->recvChannelSwitchAnnoncIE = TI_FALSE;
//    params->P2PDEviceMgmtPresent = TI_FALSE;
//
//	while (bodyDataLen > 1)
//	{
//		pEleHdr = (dot11_eleHdr_t *)pData;
//
////#if CHECK_PARSING_ERROR_CONDITION_PRINT
////		/* CHECK_PARSING_ERROR_CONDITION(((*pEleHdr)[1] > (bodyDataLen - 2)), ("MLME_PARSER: IE %d with length %d out of bounds %d", (*pEleHdr)[0], (*pEleHdr)[1], (bodyDataLen - 2)), TRUE); */
////		if ((*pEleHdr)[1] > (bodyDataLen - 2))
////		{
////			TRACE(pHandle->hReport, REPORT_SEVERITY_ERROR, "MLME_PARSER: IE %d with length %d out of bounds %d", (*pEleHdr)[0], (*pEleHdr)[1], (bodyDataLen - 2));
////
////			TRACE(pHandle->hReport, REPORT_SEVERITY_ERROR, "Buff len = %d ", packetLength);
////			report_PrintDump (pPacketBody, packetLength);
////		}
////#endif
//        switch ((*pEleHdr).eleId)
//		{
//		/* read SSID */
//		case SSID_IE_ID:
//		    frame->ssidIePresent = TRUE;
//			status = mlmeParser_readSsid(pHandle, pData, bodyDataLen, &readLen, &frame->ssid);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading SSID"),TRUE);
//			break;
//		/* read rates */
//		case SUPPORTED_RATES_IE_ID:
//			status = mlmeParser_readRates(pHandle, pData, bodyDataLen, &readLen, &frame->rates);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading RATES"),TRUE);
//			break;
//		case EXT_SUPPORTED_RATES_IE_ID:
//			status = mlmeParser_readRates(pHandle, pData, bodyDataLen, &readLen, &frame->extRates);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading EXT RATES"),TRUE);
//			break;
//
//		case ERP_IE_ID:
//			status = mlmeParser_readERP(pHandle, pData, bodyDataLen, &readLen,
//										(TI_BOOL *)&frame->useProtection,
//										(EPreamble *)&frame->barkerPreambleMode);
//
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading ERP"),TRUE);
//			break;
//		/* read FH parameter set */
//		case FH_PARAMETER_SET_IE_ID:
//			status = mlmeParser_readFhParams(pHandle, pData, bodyDataLen, &readLen, &frame->fhParams);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading FH parameters"),TRUE);
//			break;
//		/* read DS parameter set */
//		case DS_PARAMETER_SET_IE_ID:
//			status = mlmeParser_readDsParams(pHandle, pData, bodyDataLen, &readLen, &frame->dsParams);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading DS parameters"),TRUE);
//			if (RADIO_BAND_2_4_GHZ == params->band )
//			{
//				if (frame->dsParams.currChannel != params->rxChannel)
//				{
//					GTRACE(GRP_GENERAL_ERROR, "Channel ERROR - incompatible channel source information: Frame=%d Vs Radio=%d.parser ABORTED!!!",
//						frame->dsParams.currChannel , params->rxChannel);
//
//                    return-1;
//				}
//			}
//			break;
//		/* read CF parameter set */
//		case CF_PARAMETER_SET_IE_ID:
//			status = mlmeParser_readCfParams(pHandle, pData, bodyDataLen, &readLen, &frame->cfParams);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading CF parameters"),TRUE);
//			break;
//		/* read IBSS parameter set */
//		case IBSS_PARAMETER_SET_IE_ID:
//			status = mlmeParser_readIbssParams(pHandle, pData, bodyDataLen, &readLen, &frame->ibssParams);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading IBSS parameters"),TRUE);
//			break;
//
//		/* read TIM */
//		case TIM_IE_ID:
//			status = mlmeParser_readTim(pHandle, pData, bodyDataLen, &readLen, &frame->tim);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading TIM"),TRUE);
//			break;
//
//		/* read Country */
//		case COUNTRY_IE_ID:
//			status = mlmeParser_readCountry(pHandle, pData, bodyDataLen, &readLen, &frame->country);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading country parameters"),TRUE);
//			break;
//
//        /* read challenge for shared auth */
//		case CHALLANGE_TEXT_IE_ID:
//		    status = mlmeParser_readChallange(pHandle, pData, bodyDataLen, &readLen, &frame->challenge);
//		    CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading challenge parameters"),TRUE);
//            break;
//
//		/* read Power Constraint */
//		case POWER_CONSTRAINT_IE_ID:
//#ifdef CCX_MODULE_INCLUDED
//			allowCellTP = TI_FALSE;
//#endif /* CCX_MODULE_INCLUDED */
//			status = mlmeParser_readPowerConstraint(pHandle, pData, bodyDataLen, &readLen, &frame->powerConstraint);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading Power Constraint parameters"),TRUE);
//			break;
//
//		/* read Channel Switch Mode */
//        case CHANNEL_SWITCH_ANNOUNCEMENT_IE_ID:
//
//				params->recvChannelSwitchAnnoncIE = TRUE;
//				status = mlmeParser_readChannelSwitch(pHandle, pData, bodyDataLen, &readLen, &frame->channelSwitch, params->rxChannel);
//				if (status != OK)
//				{
//					/*
//					 * PATCH for working with AP-DK 4.0.51 that use IE 37 (with length 20) for RSNE
//					 * Ignore the IE instead of rejecting the whole BUF (beacon or probe response)
//					 */
//                    GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: error reading Channel Switch announcement parameters - ignore IE");
//				}
//			break;
//
//		/* read Quiet IE */
//		case QUIET_IE_ID:
//			status = mlmeParser_readQuiet(pHandle, pData, bodyDataLen, &readLen, &frame->quiet);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading Quiet parameters"),TRUE);
//			break;
//
//		/* read TPC report IE */
//		case TPC_REPORT_IE_ID:
//			status = mlmeParser_readTPCReport(pHandle, pData, bodyDataLen, &readLen, &frame->TPCReport);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading TPC report parameters"),TRUE);
//			break;
//
//		case CCX_EXT_1_IE_ID:
//		case CCX_EXT_2_IE_ID:
//		    frame->ciscoIePresent = TRUE;
//			status = mlmeParser_readRsnIe(pHandle, pData, bodyDataLen, &readLen, &frame->rsnIe[rsnIeIdx]);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading RSN IE"),TRUE);
//
//			frame->rsnIeLen += readLen;
//			rsnIeIdx ++;
//			break;
//
//		case RSN_IE_ID:
//            if( rsnIeIdx >= 3 )
//            {
//                GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: Number of RSN IEs exeeds 3");
//                return-1;
//            }
//			status = mlmeParser_readRsnIe(pHandle, pData, bodyDataLen, &readLen, &frame->rsnIe[rsnIeIdx]);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading RSN IE"),TRUE);
//
//			frame->rsnIeLen += readLen;
//			rsnIeIdx ++;
//			break;
//
//		case QOS_CAPABILITY_IE_ID:
//			status = mlmeParser_readQosCapabilityIE(pHandle, pData, bodyDataLen, &readLen, &params->QosCapParams);
//			CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading QOS CapabilityIE"),TRUE);
//			break;
//
//	case HT_CAPABILITIES_IE_ID:
//		status = mlmeParser_readHtCapabilitiesIE(pHandle, pData, bodyDataLen, &readLen, &params->tHtCapabilities);
//		CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading HT Capabilitys IE"),TRUE);
//		break;
//
//	case HT_INFORMATION_IE_ID:
//		status = mlmeParser_readHtInformationIE(pHandle, pData, bodyDataLen, &readLen, &params->tHtInformation);
//		CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading HT Information IE"),TRUE);
//		break;
//
//    case RRM_ENABLED_CAPABILITIES_IE_ID:
//         status = mlmeParser_readRMEnabledCapIE(pHandle, pData, bodyDataLen, &readLen, &params->tRRMEnabledCap);
//         CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading RRM_ENABLED_CAPABILITIES IE"),TRUE);
//         break;
//
//    case MOBILITY_DOMAIN_IE_ID:
//        status = mlmeParser_readMobilityDomain(pHandle, pData, bodyDataLen, &readLen, &params->tMobilityDomain);
//        CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading MOBILITY_DOMAIN IE"), TRUE);
//        break;
//
//    case FAST_TRANSITION_IE_ID:
//        status = mlmeParser_readFastTransition(pHandle, pData, bodyDataLen, &readLen, &params->tFastTransition);
//        CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading FAST_TRANSTITION IE"), TRUE);
//        break;
//
//
//	case VENDOR_SPECIFIC_IE_ID:
//			if (!memcmp(pData+2, wpaIeOuiIe, 3))
//			{
//				/* Note : WSC, WPA and WME use the same OUI */
//				/*  Its assumes that:
//						WPA uses OUI Type with value  - 1
//						WME uses OUI Type with value  - 2
//						WSC uses OUI Type with value  - 4
//				*/
//
//				/* Check the OUI sub Type to verify whether this is a WSC IE, WME IE or WPA IE*/
//				if( (*(uint8_t*)(pData+5)) == dot11_WPA_OUI_TYPE)
//				{
//                    if( rsnIeIdx >= 3 )
//                    {
//                        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: Number of RSN IEs exeeds 3");
//                        return-1;
//                    }
//					/* If we are here - the following is WPA IE */
//					status = mlmeParser_readRsnIe(pHandle, pData, bodyDataLen,
//												  &readLen, &params->rsnIe[rsnIeIdx]);
//					frame->rsnIeLen += readLen;
//					rsnIeIdx ++;
//
//					CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading RSN IE"),TRUE);
//				}
//				if( ( (*(uint8_t*)(pData+5)) == dot11_WME_OUI_TYPE ) &&
//					( ( (*(uint8_t*)(pData+6)) == dot11_WME_OUI_SUB_TYPE_PARAMS_IE) ||
//					  ( (*(uint8_t*)(pData+6)) == dot11_WME_OUI_SUB_TYPE_IE) ) )
//				{
//					/* If we are here - the following is WME-Params IE, WME-Info IE or TSPEC IE. */
//					/* Note that we are using the WMEParams struct also to hold the WME-Info IE
//					     which is a subset of WMEParams, and only one of them is sent in a frame. */
//					status = mlmeParser_readWMEParams(pHandle, pData, bodyDataLen, &readLen, &frame->WMEParams, NULL);
//
//					CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading WME params"),TRUE);
//				}
//				if( ( (*(uint8_t*)(pData+5)) == dot11_WSC_OUI_TYPE ))
//				{
//					/* If we are here - the following is WSC IE */
//                    readLen = mlmeParser_getWSCReadLen (pData);
//                    /*
//                     * This IE is not supposed to be found in beacons accroding to the standard
//                     * definition. However, some APs do add it to beacons. It is read from beacons
//                     * accroding to a registry key (which is false by default). Even if it is not
//                     * read, the readLen must be set for the pointer to advance, which is done
//                     * above.
//                     */
//                    if ((BEACON != params->frame.subType) || (TRUE == pHandle->bParseBeaconWSC))
//                    {
//					status = mlmeParser_readWSCParams(pHandle, pData, bodyDataLen, &readLen, &frame->WSCParams);
//					CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading WSC params"),TRUE);
//				}
//                }
//				else
//				{
//					/* Unrecognized OUI type */
//					readLen = (*pEleHdr).eleLen + 2;
//				}
//			}
//            else
//            {
//               status = mlmeParser_readP2PParams(pHandle, pData, bodyDataLen, &readLen, &frame->P2PDEviceMgmtPresent);
//               CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading P2P params"),TRUE);
//            }
//           break;
//
//
//#ifdef CCX_MODULE_INCLUDED
//		case CELL_POWER_IE:
//			/* We mustn't take the Cell Transmit Power IE into account if */
//			/* there's a Power Constraint IE. Since the IEs must be in increasing */
//			/* order, it's enough to perform the check here, because if the Power */
//			/* Constraint IE is present it must have already been processed. */
//			if (allowCellTP)
//			{
//				status = mlmeParser_readCellTP(pHandle, pData, bodyDataLen, &readLen, &frame->cellTP);
//				CHECK_PARSING_ERROR_CONDITION((status != OK), ("MLME_PARSER: error reading Cell Transmit Power params."),TRUE);
//			}
//			break;
//#endif /* CCX_MODULE_INCLUDED */
//
//		default:
//			GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: unknown IE found (%d)", pData[0]);
//            {
//                uint32_t copyLen;
//                readLen = pData[1] + 2;
//                status = OK;
//                /* check buffer overflow */
//                if( sizeof(params->unknownIe) - params->unknownIeLen < readLen)
//                {
//                    copyLen =  sizeof(params->unknownIe) - params->unknownIeLen;
//                }
//                else
//                {
//                    copyLen = readLen;
//                }
//                memcpy(&params->unknownIe[params->unknownIeLen],
//				       pData, copyLen );
//			params->unknownIeLen += copyLen;
//			break;
//            }
//		}   // switch
//
//		pData += readLen;
//		bodyDataLen -= readLen;
//
//#if CHECK_PARSING_ERROR_CONDITION_PRINT
//		/* CHECK_PARSING_ERROR_CONDITION((bodyDataLen < 0), ("MLME_PARSER: negative bodyDataLen %d bytes", bodyDataLen),TRUE); */
//		if (bodyDataLen < 0)
//		{
//			TRACE(pHandle->hReport, REPORT_SEVERITY_ERROR, "MLME_PARSER: negative bodyDataLen %d bytes", bodyDataLen);
//			TRACE(pHandle->hReport, REPORT_SEVERITY_ERROR, "Buff len = %d ", packetLength);
//			report_PrintDump (pPacketBody, packetLength);
//		}
//#endif
//
//	}   // while
//
//
//	return OK;
//}

///**
//*
//* parseIeBuffer  - Parse a required information element.
//*
//* \b Description:
//*
//* Parse an required information element
//* and returns a pointer to the IE.
// * If given a matching buffer as well, returns a pointer to the first IE
// * that matches the IE ID and the given buffer.
//*
//* \b ARGS:
//*
//*  I   - hOs - pointer to OS context
//*  I   - pIeBuffer - pointer to the IE buffer
//*  I   - length - the length of the whole buffer
//*  I   - desiredIeId - the desired IE ID
//*  O   - pDesiredIe - a pointer to the desired IE
//*  I   - pMatchBuffer - a matching buffer in the IE buffer. Optional, if not required a NULL can be given.
//*  I   - matchBufferLen - the matching buffer length. Optional, if not required zero can be given.
//*
//*
//* \b RETURNS:
//*
//* TRUE if IE pointer was found, TI_FALSE on failure.
//*
//* \sa
//*/
//TI_BOOL mlmeParser_ParseIeBuffer (void * hOs, uint8_t *pIeBuffer, uint32_t length, uint8_t desiredIeId, uint8_t **pDesiredIe, uint8_t *pMatchBuffer, uint32_t matchBufferLen)
//{
//    dot11_eleHdr_t   *eleHdr;
//    uint8_t         *pCurIe;
//
//
//    if (pDesiredIe!=NULL)
//    {
//        *pDesiredIe = NULL;
//    }
//
//    if ((pIeBuffer == NULL) || (length==0))
//    {
//       return TI_FALSE;
//    }
//
//    pCurIe = pIeBuffer;
//
//    while (length>0)
//    {
//        eleHdr = (dot11_eleHdr_t*)pCurIe;
//
//        if (length < ((uint32_t)(*eleHdr)[1] + 2))
//        {
//            return TI_FALSE;
//        }
//
//        if ((*eleHdr)[0] == desiredIeId)
//        {
//            if ((matchBufferLen==0) || (pMatchBuffer == NULL) ||
//                (!os_memoryCompare(hOs, &pCurIe[2], pMatchBuffer, matchBufferLen)))
//            {
//                if (pDesiredIe!=NULL)
//                {
//                    *pDesiredIe = (uint8_t*)eleHdr;
//                }
//                return TRUE;
//            }
//
//        }
//        length -= (*eleHdr)[1] + 2;
//        pCurIe += (*eleHdr)[1] + 2;
//    }
//
//    return TI_FALSE;
//}
//
//int32_t mlmeParser_getFrameType(TMlmeParser *pMlme, uint16_t* pFrameCtrl, dot11MgmtSubType_e *pType)
//{
//    uint16_t fc;
//
//	COPY_WLAN_WORD(&fc, pFrameCtrl); /* copy with endianess handling. */
//
//	if ((fc & DOT11_FC_PROT_VERSION_MASK) != DOT11_FC_PROT_VERSION)
//    {
//        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: Error Wrong protocol version (not %d)", DOT11_FC_PROT_VERSION);
//        return-1;
//    }
//
//    if ((fc & DOT11_FC_TYPE_MASK) != DOT11_FC_TYPE_MGMT)
//    {
//        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: Error not MANAGEMENT frame");
//        return-1;
//    }
//
//    *pType = (dot11MgmtSubType_e)((fc & DOT11_FC_SUB_MASK) >> 4);
//
//    return OK;
//}


//#ifdef CCX_MODULE_INCLUDED
//void mlmeParser_readCcxOui (uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, CCXv4IEs_t *ccxIEs)
//{
//    uint8_t ieLen;
//	uint8_t ouiType;
//
//    ieLen = *(pData+1) + 2;
//
//    if (dataLen < ieLen)
//    {
//		/* Wrong length of info-element, skip to the end of the packet */
//		*pReadLen = dataLen;
//		return;
//    }
//
//    *pReadLen = ieLen;
//	ouiType = *(pData+5);
//
//	switch (ouiType)
//	{
//		case TS_METRIX_OUI_TYPE:
//			ccxIEs->tsMetrixParameter = (dot11_TS_METRICS_IE_t *)pData;
//			break;
//		case TS_RATE_SET_OUI_TYPE:
//			ccxIEs->trafficStreamParameter = (dot11_TSRS_IE_t *)pData;
//			break;
//		case EDCA_LIFETIME_OUI_TYPE:
//			ccxIEs->edcaLifetimeParameter = (dot11_MSDU_LIFE_TIME_IE_t *)pData;
//			break;
//	}
//    return;
//}
//#endif /* CCX_MODULE_INCLUDED */
//
//
static int32_t mlmeParser_readERP(uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen,
                                  dot11_erp_t *pErpIe, uint8_t *useProtection, uint8_t *barkerPreambleMode)
{

    uint32_t erpIElen;
    uint8_t ctrl;

    pErpIe->hdr.eleId = *pData;
    pErpIe->hdr.eleLen = *(pData+1);

    *pReadLen = pErpIe->hdr.eleLen + 2;

    if (dataLen < (uint32_t)(pErpIe->hdr.eleLen + 2))
    {
        return-1;
    }

    if (pErpIe->hdr.eleLen > DOT11_MAX_ERPIE_SIZE)
    {
        MLME_REPORT_PRINT_ERROR("\n\r pErpIe->hdr.eleLen(=%d) > DOT11_MAX_ERPIE_SIZE ",pErpIe->hdr.eleLen);
        return-1;
    }

    memcpy((void *)pErpIe->erpIeData, pData+sizeof(dot11_eleHdr_t), pErpIe->hdr.eleLen);

    ctrl = *(pData + 2);

    *useProtection = (uint8_t)(ctrl & 0x2) >>1;
    *barkerPreambleMode = (uint8_t)(((ctrl & 0x4) >>2) ? PREAMBLE_LONG : PREAMBLE_SHORT);

    return OK;
}


static int32_t mlmeParser_readRates(uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_RATES_t *pRates)
{
    HOOK(HOOK_IN_MLME_PARSER);

    pRates->hdr.eleId = *pData;
    pRates->hdr.eleLen = *(pData+1);

    *pReadLen = pRates->hdr.eleLen + 2;

    if (dataLen < (uint32_t)(pRates->hdr.eleLen + 2))
    {
        return-1;
    }

    if (pRates->hdr.eleLen > DOT11_MAX_SUPPORTED_RATES)
    {
        return-1;
    }

    memcpy((void *)pRates->rates, pData+2, pRates->hdr.eleLen);

    return OK;
}

static int32_t mlmeParser_readSsid(uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_SSID_t *pSsid)
{
    HOOK(HOOK_IN_MLME_PARSER);

    pSsid->hdr.eleId = ((dot11_SSID_t *)(pData))->hdr.eleId;
    pSsid->hdr.eleLen = ((dot11_SSID_t *)(pData))->hdr.eleLen;

    *pReadLen = pSsid->hdr.eleLen + sizeof(dot11_eleHdr_t);


    if ((dataLen < 2) || (dataLen < (uint32_t)(pSsid->hdr.eleLen + 2)) || (pSsid->hdr.eleLen > DOT11_SSID_MAX_LEN))
    {
        MLME_ERROR_PRINT("\n\r ERROR! mlmeParser_readSsid : %d \n\r ",pSsid->hdr.eleLen);
        return-1;
    }

    memcpy((void *)pSsid->serviceSetId, pData+sizeof(dot11_eleHdr_t), pSsid->hdr.eleLen);
#ifdef MLME_LOG_PARSER
    {
        char ssidNullTerm[DOT11_SSID_MAX_LEN+1];
        memcpy(ssidNullTerm ,pSsid->serviceSetId,DOT11_SSID_MAX_LEN  );
        ssidNullTerm[DOT11_SSID_MAX_LEN] = 0;
        MLME_REPORT_PRINT_PARSER("\n\rssid: %s \n\r",pSsid->serviceSetId);
    }
#endif
    return OK;
}


//static int32_t mlmeParser_readFhParams(TMlmeParser *pMlme, uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_FH_PARAMS_t *pFhParams)
//{
//    pFhParams->hdr.eleId = *pData;
//    pFhParams->hdr.eleLen = *(pData+1);
//    pData += 2;
//
//    if ((dataLen < DOT11_FH_PARAMS_ELE_LEN + 2) || (pFhParams->hdr.eleLen != DOT11_FH_PARAMS_ELE_LEN))
//    {
//        return-1;
//    }
//
//    COPY_WLAN_WORD(&pFhParams->dwellTime , pData);
//    pData += 2;
//
//    pFhParams->hopSet = *pData;
//    pFhParams->hopPattern = *(pData+1);
//    pFhParams->hopIndex = *(pData+2);
//
//    *pReadLen = pFhParams->hdr.eleLen + 2;
//
//    return OK;
//}


static int32_t mlmeParser_readDsParams(uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_DS_PARAMS_t *pDsParams)
{
    HOOK(HOOK_IN_MLME_PARSER);

    pDsParams->hdr.eleId = *pData;
    pDsParams->hdr.eleLen = *(pData+1);

    if ((dataLen < DOT11_DS_PARAMS_ELE_LEN + 2) || (pDsParams->hdr.eleLen != DOT11_DS_PARAMS_ELE_LEN))
    {
        return-1;
    }

    pDsParams->currChannel = *(pData+2);

    *pReadLen = pDsParams->hdr.eleLen + 2;

    return OK;
}


//static int32_t mlmeParser_readCfParams(TMlmeParser *pMlme, uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_CF_PARAMS_t *pCfParams)
//{
//    pCfParams->hdr.eleId = *pData;
//    pCfParams->hdr.eleLen = *(pData+1);
//    pData += 2;
//
//    if ((dataLen < DOT11_CF_PARAMS_ELE_LEN + 2) || (pCfParams->hdr.eleLen != DOT11_CF_PARAMS_ELE_LEN))
//    {
//        return-1;
//    }
//
//    pCfParams->cfpCount = *pData;
//    pCfParams->cfpPeriod = *(pData+1);
//    pData += 2;
//
//    COPY_WLAN_WORD(&pCfParams->cfpMaxDuration, pData);
//    pData += 2;
//
//    COPY_WLAN_WORD(&pCfParams->cfpDurRemain, pData);
//
//    *pReadLen = pCfParams->hdr.eleLen + 2;
//
//    return OK;
//}
//
//
//static int32_t mlmeParser_readIbssParams(TMlmeParser *pMlme, uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_IBSS_PARAMS_t *pIbssParams)
//{
//    pIbssParams->hdr.eleId = *pData;
//    pIbssParams->hdr.eleLen = *(pData+1);
//    pData += 2;
//
//    if ((dataLen < DOT11_IBSS_PARAMS_ELE_LEN + 2) || (pIbssParams->hdr.eleLen != DOT11_IBSS_PARAMS_ELE_LEN))
//    {
//        return-1;
//    }
//
//    COPY_WLAN_WORD(&pIbssParams->atimWindow, pData);
//
//    *pReadLen = pIbssParams->hdr.eleLen + 2;
//
//    return OK;
//}
//
//
//static int32_t mlmeParser_readTim(TMlmeParser *pMlme, uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_TIM_t *pTim)
//{
//    pTim->hdr.eleId = *pData;
//    pTim->hdr.eleLen = *(pData+1);
//
//    if ((dataLen < 2) || (dataLen < (uint32_t)(pTim->hdr.eleLen + 2)) || (pTim->hdr.eleLen < 3))
//    {
//        return-1;
//    }
//
//    pTim->dtimCount		= *(pData + 2);
//    pTim->dtimPeriod	= *(pData + 3);
//    pTim->bmapControl	= *(pData + 4);
//
//    memcpy((void *)pTim->partialVirtualBmap, pData + 5, pTim->hdr.eleLen - 3);
//
//    *pReadLen = pTim->hdr.eleLen + 2;
//
//    return OK;
//}


static int32_t mlmeParser_readCountry(uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_COUNTRY_t *countryIE)
{
    HOOK(HOOK_IN_MLME_PARSER);

    int32_t i, j;
    uint8_t uPadLen = 0;

    countryIE->hdr.eleId = *pData;
    countryIE->hdr.eleLen = *(pData+1);

    *pReadLen = countryIE->hdr.eleLen + 2;

    if ((dataLen < 8) || (dataLen < (uint32_t)(countryIE->hdr.eleLen + 2)))
    {
        return-1;
    }

    if ((countryIE->hdr.eleLen > DOT11_COUNTRY_ELE_LEN_MAX) || (countryIE->hdr.eleLen < DOT11_COUNTRY_STRING_LEN))
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: MLME_PARSER: country IE error: eleLen=%d, maxLen=%d, minLen=%d", countryIE->hdr.eleLen, DOT11_COUNTRY_ELE_LEN_MAX, DOT11_COUNTRY_STRING_LEN);
        return-1;
    }

    uPadLen = (countryIE->hdr.eleLen % 3);

    if((uPadLen != 0) && (uPadLen != 1))
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: MLME_PARSER: country IE error: uPadLen = %d. Must be 0 or 1.", uPadLen);
        return-1;
    }

    memcpy(&(countryIE->countryIE.CountryString), pData+2, DOT11_COUNTRY_STRING_LEN);

    /* Loop on all tripletChannels. Each item has three fields ('i' counts rows and 'j' counts bytes). */
    for (i = 0, j = 0;  j < (countryIE->hdr.eleLen - DOT11_COUNTRY_STRING_LEN - uPadLen);  i++, j+=3)
    {
        countryIE->countryIE.tripletChannels[i].firstChannelNumber	= *(pData + j + 5);
        countryIE->countryIE.tripletChannels[i].numberOfChannels	= *(pData + j + 6);
        countryIE->countryIE.tripletChannels[i].maxTxPowerLevel		= *(pData + j + 7);
    }

    return OK;
}

// this API is used by driver_cc when assoc response is received
int32_t mlmeParser_readWMEParams(const uint8_t *apWmmData, dot11_WME_PARAM_t *apWMEParamIE)
{
    HOOK(HOOK_IN_MLME_PARSER);

    uint8_t ieSubtype;

    /* Note:  This function actually reads either the WME-Params IE or the WME-Info IE! */

    apWMEParamIE->hdr.eleId = *apWmmData;
    apWMEParamIE->hdr.eleLen = *(apWmmData+1);

    if ((WME_TSPEC_IE_LEN < apWMEParamIE->hdr.eleLen) || (apWMEParamIE->hdr.eleLen < DOT11_WME_ELE_LEN))
    {
        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME Parameter IE error: eleLen=%d", apWMEParamIE->hdr.eleLen);
        return -1;
    }

    ieSubtype = *((uint8_t*)(apWmmData+6));
    switch (ieSubtype)
    {
        case dot11_WME_OUI_SUB_TYPE_IE:
            /* Read WMM IE */
            if (*((uint8_t*)(apWmmData+7)) != dot11_WME_VERSION)
            {
                GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME IE error: Version =%d is unsupported", *((uint8_t*)(apWmmData+7)) );
                return-1;
            }
            if (apWMEParamIE->hdr.eleLen != DOT11_WME_ELE_LEN)
            {
                GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME IE error: Length = %d", apWMEParamIE->hdr.eleLen);
                return-1;
            }
            memcpy (&(apWMEParamIE->OUI), apWmmData+2, DOT11_WME_ELE_LEN);
            break;

        case dot11_WME_OUI_SUB_TYPE_PARAMS_IE:
            /* Read WMM Params IE */
            if (*((uint8_t*)(apWmmData+7)) != dot11_WME_VERSION)
            {
                GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME PARAMS IE error: Version =%d is unsupported", *((uint8_t*)(apWmmData+7)) );
                return-1;
            }
            if (apWMEParamIE->hdr.eleLen != DOT11_WME_PARAM_ELE_LEN)
            {
                GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME PARAMS IE error: Length = %d", apWMEParamIE->hdr.eleLen);
                return-1;
            }
            memcpy (&(apWMEParamIE->OUI), apWmmData+2, DOT11_WME_PARAM_ELE_LEN);
            break;

        case WME_TSPEC_IE_OUI_SUB_TYPE:
        //24

            os_memcpy (&(apWMEParamIE->WME_ACParameteres), apWmmData+11, sizeof(dot11_ACParameters_t));
            break;

        default:
            HOOK(HOOK_IN_MLME_PARSER);

            /* Checking OUI Sub Type validity */
            GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME Parameter IE error: Sub Type =%d is invalid",ieSubtype);
            return-1;
    }

    HOOK(HOOK_IN_MLME_PARSER);

    return OK;
}

//static int32_t mlmeParser_readWMEParams(TMlmeParser *pMlme,uint8_t *pData, uint32_t dataLen,
//								   uint32_t *pReadLen, dot11_WME_PARAM_t *pWMEParamIE,
//								   mlmeIEParsingParams_t *assocRsp)
//{
//	uint8_t ieSubtype;
//	uint8_t ac;
//
//	/* Note:  This function actually reads either the WME-Params IE or the WME-Info IE! */
//
//    pWMEParamIE->hdr.eleId = *pData;
//    pWMEParamIE->hdr.eleLen = *(pData+1);
//
//    *pReadLen = pWMEParamIE->hdr.eleLen + 2;
//
//    if (dataLen < *pReadLen)
//    {
//        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME Parameter: eleLen=%d is too long (%d)", *pReadLen, dataLen);
//		*pReadLen = dataLen;
//		return-1;
//    }
//
//    if ((pWMEParamIE->hdr.eleLen> WME_TSPEC_IE_LEN) || (pWMEParamIE->hdr.eleLen< DOT11_WME_ELE_LEN))
//    {
//        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME Parameter IE error: eleLen=%d", pWMEParamIE->hdr.eleLen);
//        return-1;
//    }
//
//	ieSubtype = *((uint8_t*)(pData+6));
//    switch (ieSubtype)
//	{
//		case dot11_WME_OUI_SUB_TYPE_IE:
//			/* Read WMM IE */
//			if (*((uint8_t*)(pData+7)) != dot11_WME_VERSION)
//			{
//                GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME IE error: Version =%d is unsupported", *((uint8_t*)(pData+7)) );
//				return-1;
//			}
//			if (pWMEParamIE->hdr.eleLen != DOT11_WME_ELE_LEN)
//			{
//                GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME IE error: Length = %d", pWMEParamIE->hdr.eleLen);
//				return-1;
//			}
//			memcpy (&(pWMEParamIE->OUI), pData+2, DOT11_WME_ELE_LEN);
//			break;
//
//		case dot11_WME_OUI_SUB_TYPE_PARAMS_IE:
//			/* Read WMM Params IE */
//			if (*((uint8_t*)(pData+7)) != dot11_WME_VERSION)
//			{
//                GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME PARAMS IE error: Version =%d is unsupported", *((uint8_t*)(pData+7)) );
//				return-1;
//			}
//			if (pWMEParamIE->hdr.eleLen != DOT11_WME_PARAM_ELE_LEN)
//			{
//                GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME PARAMS IE error: Length = %d", pWMEParamIE->hdr.eleLen);
//				return-1;
//			}
//			memcpy (&(pWMEParamIE->OUI), pData+2, DOT11_WME_PARAM_ELE_LEN);
//			break;
//
//		case WME_TSPEC_IE_OUI_SUB_TYPE:
//			/* Read renegotiated TSPEC parameters */
//			if (assocRsp == NULL)
//			{
//                GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME TSPEC IE error: TSPEC Sub Type in beacon or probe resp");
//				return-1;
//			}
//
//            /* Verify that the TSPEC IE length is correct before saving it */
//            if ((dataLen < WME_TSPEC_IE_LEN + 2) || (pWMEParamIE->hdr.eleLen != WME_TSPEC_IE_LEN))
//            {
//                GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME TSPEC IE length error: dataLen = %d, IeLen = %d", dataLen, pWMEParamIE->hdr.eleLen);
//				return-1;
//            }
////TODO: to add WMEQosTagToACTable
////            ac = WMEQosTagToACTable [ GET_USER_PRIORITY_FROM_WME_TSPEC_IE(pData) ];
////
////			if (ac == QOS_AC_VO)
////			{
////				assocRsp->tspecVoiceParameters = pData;
////			}
////			else if (ac == QOS_AC_VI)
////			{
////				assocRsp->tspecVideoParameters = pData;
////			}
//			break;
//
//		default:
//			/* Checking OUI Sub Type validity */
//            GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WME Parameter IE error: Sub Type =%d is invalid",ieSubtype);
//			return-1;
//	}
//    return OK;
//}


//static uint32_t mlmeParser_getWSCReadLen(uint8_t *pData)
//{
//    return *(pData+1) + 2;
//}
//
//

// this API is used by driver_cc when assoc response is received
int32_t mlmeParser_readWSCParams(const uint8_t *apWmmData, dot11_WSC_t *apWSC_IE)
{
    HOOK(HOOK_IN_MLME_PARSER);

    apWSC_IE->hdr.eleId = *apWmmData;
    apWSC_IE->hdr.eleLen = *(apWmmData+1);

    /* Length Sanity check of the WSC IE */
    if (apWSC_IE->hdr.eleLen > ( sizeof(dot11_WSC_t) - sizeof(dot11_eleHdr_t) ))
    {
        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WSC Parameter IE error: eleLen=%d, maxLen=%d", apWSC_IE->hdr.eleLen, ( sizeof(dot11_WSC_t) - sizeof(dot11_eleHdr_t) ));
        return -1;
    }

    /* Copy the WSC Params IE */
    memcpy(&(apWSC_IE->OUI), apWmmData+2, apWSC_IE->hdr.eleLen);

    return 0;
}

//static int32_t mlmeParser_readWSCParams(TMlmeParser *pMlme,uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_WSC_t *pWSC_IE)
//{
//	pWSC_IE->hdr.eleId = *pData;
//	pWSC_IE->hdr.eleLen = *(pData+1);
//
//    *pReadLen = pWSC_IE->hdr.eleLen + 2;
//
//    /* Length Sanity check of the WSC IE */
//	if ((dataLen < 8) || (dataLen < (uint32_t)(pWSC_IE->hdr.eleLen + 2)))
//    {
//        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WSC Parameter IE error: dataLen=%d, pWSC_IE->hdr.eleLen=%d", dataLen, pWSC_IE->hdr.eleLen);
//		return-1;
//    }
//
//    /* Length Sanity check of the WSC IE */
//	if (pWSC_IE->hdr.eleLen > ( sizeof(dot11_WSC_t) - sizeof(dot11_eleHdr_t) ))
//    {
//        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: WSC Parameter IE error: eleLen=%d, maxLen=%d", pWSC_IE->hdr.eleLen, ( sizeof(dot11_WSC_t) - sizeof(dot11_eleHdr_t) ));
//        return-1;
//    }
//
//	/* Copy the WSC Params IE */
//	memcpy(&(pWSC_IE->OUI), pData+2, pWSC_IE->hdr.eleLen);
//
//    return OK;
//}
//
//
//static int32_t mlmeParser_readQosCapabilityIE(TMlmeParser *pMlme,uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_QOS_CAPABILITY_IE_t *QosCapParams)
//{
//    QosCapParams->hdr.eleId = *pData;
//    QosCapParams->hdr.eleLen = *(pData+1);
//
//    *pReadLen = QosCapParams->hdr.eleLen + 2;
//
//    if (dataLen < (uint32_t)(QosCapParams->hdr.eleLen + 2))
//    {
//        return-1;
//    }
//
//    if (QosCapParams->hdr.eleLen > DOT11_QOS_CAPABILITY_ELE_LEN)
//    {
//        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: QOS Capability  IE error: eleLen=%d, maxLen=%d", QosCapParams->hdr.eleLen, DOT11_QOS_CAPABILITY_ELE_LEN);
//        return-1;
//    }
//
//   QosCapParams->QosInfoField = (*(pData+1));
//    return OK;
//}
//

static int32_t mlmeParser_readHtCapabilitiesIE(uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11HtCapabilitiesUnparse_t *pHtCapabilities)
{
    HOOK(HOOK_IN_MLME_PARSER);

    pHtCapabilities->eleHdr.eleId = *pData;
    pHtCapabilities->eleHdr.eleLen = *(pData+1);

    *pReadLen = pHtCapabilities->eleHdr.eleLen + 2;

    if (dataLen < (uint32_t)(pHtCapabilities->eleHdr.eleLen + 2))
    {
        return-1;
    }

    if (pHtCapabilities->eleHdr.eleLen != DOT11_HT_CAPABILITIES_ELE_LEN)
    {
        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: HT Capability IE error: eleLen=%d, expectedLen=%d", pHtCapabilities->eleHdr.eleLen, DOT11_HT_CAPABILITIES_ELE_LEN);
        return-1;
    }

    memcpy((void*)pHtCapabilities->htCapabilitiesIe, pData + 2, pHtCapabilities->eleHdr.eleLen);

    return OK;
}

static int32_t mlmeParser_readHtInformationIE(uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11HtInformationUnparse_t *pHtInformation)
{
    HOOK(HOOK_IN_MLME_PARSER);

    pHtInformation->eleHdr.eleId = *pData;
    pHtInformation->eleHdr.eleLen = *(pData+1);

    *pReadLen = pHtInformation->eleHdr.eleLen + 2;

    if (dataLen < (uint32_t)(pHtInformation->eleHdr.eleLen + 2))
    {
        return-1;
    }

    if (pHtInformation->eleHdr.eleLen < DOT11_HT_INFORMATION_ELE_LEN)
    {
        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: HT Information IE error: eleLen=%d, ExpectedLen=%d", pHtInformation->eleHdr.eleLen, DOT11_HT_INFORMATION_ELE_LEN);
        return-1;
    }

    if (pHtInformation->eleHdr.eleLen != DOT11_HT_INFORMATION_ELE_LEN)
    {
        /*This IE can be extended more than 22 bytes. if so we are taking only first 22 bytes*/
        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: HT Information IE error: eleLen=%d, ExpectedLen=%d", pHtInformation->eleHdr.eleLen, DOT11_HT_INFORMATION_ELE_LEN);
    }

    memcpy((void*)pHtInformation->htInformationIe, pData + 2, DOT11_HT_INFORMATION_ELE_LEN);


    return OK;
}

//static int32_t mlmeParser_readRMEnabledCapIE(TMlmeParser *pMlme,uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_RM_ENABLED_CAPABILITIES_IE_t *pRMEnabledCap)
//{
//    pRMEnabledCap->hdr.eleId = *pData;
//    pRMEnabledCap->hdr.eleLen = *(pData+1);
//
//    *pReadLen = pRMEnabledCap->hdr.eleLen + 2;
//
//    if (dataLen < (uint32_t)(pRMEnabledCap->hdr.eleLen + 2))
//    {
//        return-1;
//    }
//
//    if (pRMEnabledCap->hdr.eleLen < RRM_ENABLED_CAPABILITIES_ELE_LEN)
//    {
//        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: RMEnabledCapabilities IE error: eleLen=%d, minimum Len=%d", pRMEnabledCap->hdr.eleLen, RRM_ENABLED_CAPABILITIES_ELE_LEN);
//        return-1;
//    }
//
//
//    memcpy((void*)pRMEnabledCap->capabilities, pData + 2, pRMEnabledCap->hdr.eleLen);
//
//    return OK;
//}
//
//
//static int32_t mlmeParser_readMobilityDomain(TMlmeParser *pMlme,uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_MOBILITY_DOMAIN_IE_t *pMobilityDomain)
//{
//    if (dataLen < 2)
//    {
//        return-1;
//    }
//
//    pMobilityDomain->hdr.eleId = *pData;
//    pMobilityDomain->hdr.eleLen = *(pData+1);
//
//    *pReadLen = pMobilityDomain->hdr.eleLen + 2;
//
//    if (dataLen < (uint32_t)(pMobilityDomain->hdr.eleLen + 2))
//    {
//        return-1;
//    }
//
//    if (pMobilityDomain->hdr.eleLen != DOT11_MOBILITY_DOMAIN_ELE_LEN)
//    {
//        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: Mobilit Domain IE error: eleLen=%d, expected=%d", pMobilityDomain->hdr.eleLen, DOT11_MOBILITY_DOMAIN_ELE_LEN);
//        return-1;
//    }
//
//    COPY_WLAN_WORD(&(pMobilityDomain->mdId),  pData + 2);
//
//    pMobilityDomain->ftCapaAndPolicy = *(pData + 4);
//
//    return OK;
//}
//
//static int32_t mlmeParser_readFastTransition(TMlmeParser *pMlmeParser, uint8_t *pData, uint32_t dataLen,
//                                        uint32_t *pReadLen, dot11_FAST_TRANSITION_IE_t *pFastTranstion)
//{
//    if (dataLen < 2)
//    {
//        return-1;
//    }
//
//    pFastTranstion->hdr.eleId = *pData;
//    pFastTranstion->hdr.eleLen = *(pData+1);
//
//    if (dataLen < (uint32_t)(pFastTranstion->hdr.eleLen + 2))
//    {
//        return-1;
//    }
//
//    memcpy(pFastTranstion->body, pData+2, pFastTranstion->hdr.eleLen);
//
//    *pReadLen = pFastTranstion->hdr.eleLen + 2;
//
//    return OK;
//}
//
//static int32_t mlmeParser_readChallange(TMlmeParser *pMlmeParser, uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_CHALLENGE_t *pChallange)
//{
//    if (dataLen < 2)
//    {
//        return-1;
//    }
//
//    pChallange->hdr.eleId = *pData;
//    pChallange->hdr.eleLen = *(pData+1);
//    pData += 2;
//
//    if ((dataLen < 2) || (dataLen < (uint32_t)(pChallange->hdr.eleLen + 2)))
//    {
//        return-1;
//    }
//
//    if (pChallange->hdr.eleLen > DOT11_CHALLENGE_TEXT_MAX)
//    {
//        return-1;
//    }
//
//    memcpy((void *)pChallange->text, pData, pChallange->hdr.eleLen);
//
//    *pReadLen = pChallange->hdr.eleLen + 2;
//
//    return OK;
//}

int32_t mlmeParser_readRsnIe(uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_RSN_t *pRsnIe)
{
    HOOK(HOOK_IN_MLME_PARSER);

    pRsnIe->hdr.eleId = *pData;
    pRsnIe->hdr.eleLen = *(pData+1);
    pData += 2;

    if ((dataLen < 2) || (dataLen < (uint32_t)(pRsnIe->hdr.eleLen + 2)))
    {
        return-1;
    }

    memcpy((void *)pRsnIe->rsnIeData, pData, pRsnIe->hdr.eleLen);

    *pReadLen = pRsnIe->hdr.eleLen + 2;

    GTRACE(GRP_MGMT_PROTECTION_IMP, "MPF: pRsnIe->hdr.eleId= %d, RSN_IE_ID= %d",pRsnIe->hdr.eleId ,RSN_IE_ID);

    HOOK(HOOK_IN_MLME_PARSER);

    return OK;
}

//static int32_t mlmeParser_readPowerConstraint(TMlmeParser *pMlme,uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_POWER_CONSTRAINT_t *powerConstraintIE)
//{
//    powerConstraintIE->hdr.eleId = *pData;
//    powerConstraintIE->hdr.eleLen = *(pData+1);
//
//    *pReadLen = powerConstraintIE->hdr.eleLen + 2;
//
//    if ((dataLen < 2) || (dataLen < (uint32_t)(powerConstraintIE->hdr.eleLen + 2)))
//    {
//        return-1;
//    }
//
//    if (powerConstraintIE->hdr.eleLen > DOT11_POWER_CONSTRAINT_ELE_LEN)
//    {
//        return-1;
//    }
//
//    memcpy((void *)&(powerConstraintIE->powerConstraint), pData+2, powerConstraintIE->hdr.eleLen);
//
//    return OK;
//}
//
//
//static int32_t mlmeParser_readChannelSwitch(TMlmeParser *pMlme,uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_CHANNEL_SWITCH_t *channelSwitch, uint8_t channel)
//{
//    channelSwitch->hdr.eleId  = *pData++;
//    channelSwitch->hdr.eleLen = *pData++;
//
//    *pReadLen = channelSwitch->hdr.eleLen + 2;
//
//
//    if ((dataLen < 2) || (dataLen < (uint32_t)(channelSwitch->hdr.eleLen + 2)))
//    {
//        return-1;
//    }
//
//    if (channelSwitch->hdr.eleLen > DOT11_CHANNEL_SWITCH_ELE_LEN)
//    {
//        return-1;
//    }
//
//
//    channelSwitch->channelSwitchMode = *pData++;
//    channelSwitch->channelNumber = *pData++;
//    channelSwitch->channelSwitchCount = *pData;
//
//
//	return OK;
//}
//
//static int32_t mlmeParser_readQuiet(TMlmeParser *pMlme,uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_QUIET_t *quiet)
//{
//    quiet->hdr.eleId = *pData++;
//    quiet->hdr.eleLen = *pData++;
//
//    *pReadLen = quiet->hdr.eleLen + 2;
//
//    if ((dataLen < 2) || (dataLen < (uint32_t)(DOT11_QUIET_ELE_LEN + 2)))
//    {
//        return-1;
//    }
//
//    if (quiet->hdr.eleLen > DOT11_QUIET_ELE_LEN)
//    {
//        return-1;
//    }
//
//    quiet->quietCount = *pData++;
//    quiet->quietPeriod = *pData++;
//    COPY_WLAN_WORD(&quiet->quietDuration , pData);
//    pData += sizeof(uint16_t);
//    COPY_WLAN_WORD(&quiet->quietOffset , pData);
//
//	return OK;
//}
//
//
//static int32_t mlmeParser_readTPCReport(TMlmeParser *pMlme,uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_TPC_REPORT_t *TPCReport)
//{
//    TPCReport->hdr.eleId = *pData;
//    TPCReport->hdr.eleLen = *(pData+1);
//
//    *pReadLen = TPCReport->hdr.eleLen + 2;
//
//    if ((dataLen < 2) || (dataLen < (uint32_t)(TPCReport->hdr.eleLen + 2)))
//    {
//        return-1;
//    }
//
//    if (TPCReport->hdr.eleLen > DOT11_TPC_REPORT_ELE_LEN)
//    {
//        return-1;
//    }
//
//    TPCReport->transmitPower = *(pData+2);
//
//    return OK;
//}
//
//
//#ifdef CCX_MODULE_INCLUDED
//static int32_t mlmeParser_readCellTP(TMlmeParser *pMlme, uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, dot11_CELL_TP_t *cellTP)
//{
//    uint8_t ccx_OUI[] = CCX_OUI;
//
//    cellTP->hdr.eleId = *pData++;
//    cellTP->hdr.eleLen = *pData++;
//
//    *pReadLen = cellTP->hdr.eleLen + 2;
//
//    if ((dataLen < 2) || (dataLen < (uint32_t)(cellTP->hdr.eleLen + 2)))
//    {
//        return-1;
//    }
//
//    if (cellTP->hdr.eleLen > DOT11_CELL_TP_ELE_LEN)
//    {
//        return-1;
//    }
//
//	os_memoryCopy(pMlme->hOs, (void*)cellTP->oui, pData, cellTP->hdr.eleLen);
//
//    if (os_memoryCompare(pMlme->hOs, (void*)cellTP->oui, ccx_OUI, 3) != 0)
//    {
//		return-1;
//    }
//
//    return OK;
//}
//#endif /* CCX_MODULE_INCLUDED */

/**
 *
 * mlmeParser_ParseBeaconProbeRsp  - Parse a beacon & probe response packets.
 *
 * \b Description:
 *
 * Parse the required packet and store the parsed outcome in params
 *
 * \b ARGS:
 *
 *  I   - pMlme - mlme object
 *  I   - pData - packets data buffer
 *  I   - pRxAttr - packet's attributes
 *  I   - bodyDataLen - data length
 *  I   - pMgmtFrame - a pointer to a dot11_mgmtFrame_t struct in order to save the association response
 *  I   - pBuffer - pointer to the packet's beginning
 *  O   - params - parsed output
 *
 *
 * \b RETURNS:
 *
 * OK if parsed successfully ,-1 on failure.
 *
 * \sa
 */
//static int32_t parseBeaconProbeRsp(TMlmeParser *pMlmeParser, void *pBuffer,
//                                     uint8_t *pData, dot11_mgmtFrame_t *pMgmtFrame,
//                                     mlmeIEParsingParams_t *params)
//{
//	uint32_t uDataLen;
//	int32_t eStatus = OK;
////	const RxIfDescriptor_t *desc = pBuffer;
//	ERadioBand band;
//
//	GTRACE(GRP_MLME, "MLME_PARSER: recieved PROBE_RESPONSE message");
//
//    /* If the frame length is too short (below headers size), notify and exit */
////TODO: to set RX_BUF_LEN
////    if (RX_BUF_LEN(pBuffer) < (WLAN_HDR_LEN + TIME_STAMP_LEN + 4))
////    {
////        GTRACE(GRP_GENERAL_ERROR, "mlmeParser_parseFrame: probe response total length too short. length=%d, channel=%d", RX_BUF_LEN(pBuffer), desc->channel);
////        eStatus =-1;
////        return eStatus;
////    }
//
////    uDataLen = RX_BUF_LEN(pBuffer) - WLAN_HDR_LEN - TIME_STAMP_LEN - 4;
//
//    if (uDataLen > MAX_BEACON_BODY_LENGTH)
//    {
////TODO: to add desc
////        GTRACE(GRP_GENERAL_ERROR, "mlmeParser_parseFrame: probe response data length out of range. length=%d, channel=%d", uDataLen, desc->channel);
//        eStatus =-1;
//        return eStatus;
//    }
//
//    /* init frame fields */
//    params->barkerPreambleMode = PREAMBLE_UNSPECIFIED;
//
//    /* feilds added for dispatching outside of parsing */
//    params->pData = (uint8_t *)(pMgmtFrame->body+TIME_STAMP_LEN+4);
//    params->uDatalen = uDataLen;
//
//    /* read time stamp */
//    memcpy((void *)params->timeStamp, pData, TIME_STAMP_LEN);
//    pData += TIME_STAMP_LEN;
//
//    /* read beacon interval */
//    COPY_WLAN_WORD(&params->beaconInterval , pData);
//    pData += 2;
//    /* read capabilities */
//    COPY_WLAN_WORD(&params->capabilities , pData);
//    pData += 2;
//
//    params->rsnIeLen = 0;
////TODO: to set RXFLAGS_TO_BAND + desc
////    band = RXFLAGS_TO_BAND(desc->flags);
//    params->band = band;
////    params->rxChannel = desc->channel;
//
////TODO: to add desc
////    if ((band == RADIO_BAND_2_4_GHZ) && (desc->channel > NUM_OF_CHANNELS_24))
////    {
////        GTRACE(GRP_GENERAL_ERROR, "mlmeParser_parseFrame, band=%d, channel=%d", band, desc->channel);
////        /* Error in parsing Probe response packet - exit */
////        eStatus =-1;
////        return eStatus;
////    }
////    else if ((band == RADIO_BAND_5_0_GHZ) && (desc->channel <= NUM_OF_CHANNELS_24))
////    {
////        GTRACE(GRP_GENERAL_ERROR, "mlmeParser_parseFrame, band=%d, channel=%d", band, desc->channel);
////        /* Error in parsing Probe response packet - exit */
////        eStatus =-1;
////        return eStatus;
////    }
//
//
//    if (mlmeParser_parseIEs(pMlmeParser, pData, uDataLen/*bodyDataLen*/, params) != OK)
//    {
//        GTRACE(GRP_GENERAL_ERROR, "mlmeParser_parseFrame: Error in parsing Probe response packet");
//
//        /* Error in parsing Probe response packet - exit */
//        eStatus =-1;
//        return eStatus;
//    }
//
//    return eStatus;
//
//}
/**
 *
 * mlmeParser_ParseAssocRsp  - Parse an association response packet.
 *
 * \b Description:
 *
 * Parse the required packet and store the parsed outcome in params
 *
 * \b ARGS:
 *
 *  I   - pMlme - mlme object
 *  I   - pData - packets data buffer
 *  I   - pRxAttr - packet's attributes
 *  I   - bodyDataLen - data length
 *  O   - pMgmtFrame - a pointer to a dot11_mgmtFrame_t struct in order to save the association response
 *  O   - params - structure containing the parsed buffer
 *
 *
 * \b RETURNS:
 *
 * OK if parsed successfully ,-1 on failure.
 *
 * \sa
 */
//static int32_t parseAssocRsp(TMlmeParser *pMlmeParser, void *pBuffer,
//                               uint8_t *pData, dot11_mgmtFrame_t *pMgmtFrame,
//                               uint32_t bodyDataLen,
//                               mlmeIEParsingParams_t *params)
//{
//
//	int32_t			eStatus = OK;
//
//    if (bodyDataLen < ASSOC_RESP_FIXED_DATA_LEN)
//    {
//        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: IE ASSOC_RESPONSE length is too short (%d)!", bodyDataLen);
//        eStatus =-1;
//        return eStatus;
//    }
//
//    params->pData = (uint8_t *)(pMgmtFrame->body);
//    params->uDatalen = bodyDataLen;
//
//    /* init frame fields */
//    params->barkerPreambleMode = PREAMBLE_UNSPECIFIED;
//
//    /* read capabilities */
//    COPY_WLAN_WORD(&params->capabilities , pData);
//    pData += 2;
//    /* read status */
//    COPY_WLAN_WORD(&params->status , pData);
//    pData += 2;
//    /* read AID */
//    COPY_WLAN_WORD(&params->aid , pData);
//    params->aid &= ASSOC_RESP_AID_MASK;
//    pData += 2;
//
//    bodyDataLen -= ASSOC_RESP_FIXED_DATA_LEN;
//
//    GTRACE(GRP_MLME, "MLME_PARSER: recieved ASSOC_RESPONSE message, status = %d", params->status);
//
//    params->rsnIeLen = 0;
//
//    /* parse the IE's in the assocRsp */
//    eStatus = mlmeParser_parseIEs(pMlmeParser,pData,bodyDataLen, params);
//
//    return eStatus;
//}

//static int32_t mlmeParser_readP2PParams(TMlmeParser *pMlme,uint8_t *pData, uint32_t dataLen, uint32_t *pReadLen, TI_BOOL* mgmtBit)
//{
// uint8_t             P2PIeOuiIe[4] = {0x50,0x6f,0x9a,0x09};
// #define P2P_ATTR_MANAGEABILITY 10
//
//  *pReadLen = *(pData+1) + 2;
//
//    if (!memcmp(pData+2, P2PIeOuiIe, 4))
//    {
//     /* looking for  p2p device managment bit */
//     const uint8_t *pos = pData+6;
//     const uint8_t *end = pData + 2 + (*(uint8_t*)(pData+1));
//     uint16_t attr_len;
//
//     while (pos < end)
//     {
//       if (pos + 2 >= end)
//       {
//         GTRACE(GRP_GENERAL_ERROR, "MLMEParser: Invalid P2P attribute");
//         return-1;
//       }
//       else
//       {
//        memcpy(&attr_len, (void *)(pos + 1), sizeof(uint16_t));
//        if (pos + 3 + attr_len > end)
//        {
//         GTRACE(GRP_GENERAL_ERROR, "P2P: Attribute underflow (len=%u left=%d)", attr_len, (int) (end - pos - 3));
//         return-1;
//        }
//        else
//        {
//         if (*(uint8_t*)(pos) == P2P_ATTR_MANAGEABILITY )
//         {
//          if (*(uint8_t*)(pos+ 3)& 0x01)
//           *mgmtBit = TRUE;
//          else
//           *mgmtBit = TI_FALSE;
//         return OK;
//         }
//        }
//        pos += 3 + attr_len;
//      }
//     }
//  }
// return OK;
//
//}

uint8_t mlmeParser_calcBssidNonTx(uint8_t *bssid, uint8_t subElementIndex, uint8_t maxBssidIndicator)
{
    uint8_t bssidLastByte = bssid[5];
    uint8_t B = bssidLastByte % maxBssidIndicator;
    uint8_t newLastByte = bssidLastByte - B + (B+subElementIndex)%maxBssidIndicator;

    return (newLastByte);
}


int32_t scanParser_parseFrame(dot11_mgmtFrame_t *pMgmtFrame, scanIEParsingParams_t *params, uint16_t length, scanIEMultiBSSIDParams_t *multiBSSIDParsingParams)
{
    HOOK(HOOK_IN_MLME_PARSER);

    uint8_t               *pData, *pData_StartOfIEs;
    uint8_t               *pDataEnd;
    uint16_t              leftDataLen = 0;
    uint8_t               *pSubElement;

    os_memset(params,0 ,sizeof(scanIEParsingParams_t));

    //extract bssid
    IRQ_UtilCopyMacAddress(pMgmtFrame->hdr.BSSID, params->bssid);
    leftDataLen = length ;
    leftDataLen -= sizeof(dot11_mgmtHeader_t);      //this is the payload=body length
    pData       = (uint8_t *)pMgmtFrame->body;      //here start the beacon/probe response data after mgmt header
    pDataEnd    = pData +  leftDataLen - 1;         //this is the last byte of the data

    //save the begining address of the info elements
    params->pData = (uint8_t *)(pMgmtFrame->body + TIME_STAMP_LEN + 2 /* beacon interval */ + 2 /* capabilities */);

    //save the length of the info elements
    //    params->uDatalen = pDesc->length_type.length - TIME_STAMP_LEN - 2 /* beacon interval */- 2 /* capabilities */ - 4 /* FCS */;
    //  06.12.15 - PMAC has already decremented FCS size, no need to do it here
    params->uDatalen = length - sizeof(dot11_mgmtHeader_t) - TIME_STAMP_LEN - 2 /* beacon interval */- 2 /* capabilities */;

    //advance timestamp
    pData       += TIME_STAMP_LEN;
    leftDataLen -= TIME_STAMP_LEN;

    /* read beacon interval */
    COPY_WLAN_WORD(&params->beaconInterval , pData);
    pData       += 2;
    leftDataLen -= 2;

    /* read capabilities */
    COPY_WLAN_WORD(&params->capabilities , pData);
    pData       += 2;
    leftDataLen -= 2;

    MLME_REPORT_PRINT_PARSER("\n\rstart analyzing scan packetlength :%d \n\r", length);
    //rest of the frame is info elements. go over them and save requirested info elements

    pData_StartOfIEs = pData;
    scanParser_parseIEs(pData, params, pDataEnd, leftDataLen, multiBSSIDParsingParams);  // Parse all IEs Except of MBSSID IE

    if( 0 != multiBSSIDParsingParams->SubElementIndex )
    {          
        uint8 * subElemDataEnd = multiBSSIDParsingParams->pSubElementData + multiBSSIDParsingParams->subElementLength;

        MLME_REPORT_PRINT_PARSER("\n\r start parsing subelement number :%d \n\r", multiBSSIDParsingParams->SubElementIndex);

        // Override parent IEs with those found in MBSSID sub elemnent
        scanParser_parseIEs(multiBSSIDParsingParams->pSubElementData, params, subElemDataEnd,
            multiBSSIDParsingParams->subElementLength, multiBSSIDParsingParams);  

        // The effective address of each non-transmitting bssid is derived from
        // the transmitting bssid which carries it.
        params->nonTransmittingBssidIeBuffer = multiBSSIDParsingParams->pSubElementData;
        params->nonTransmittingBssidIeBufferLength = multiBSSIDParsingParams->subElementLength;
        params->mbssidIndex = multiBSSIDParsingParams->SubElementIndex;
        params->mbssidIndicator = multiBSSIDParsingParams->MaxBSSIDIndicator;
        params->nonTransmittingBssid = TRUE;
        // params->bssid[5] += multiBSSIDParsingParams->SubElementIndex;
        params->bssid[5] = mlmeParser_calcBssidNonTx(params->bssid, multiBSSIDParsingParams->SubElementIndex, params->mbssidIndicator);
        IRQ_UtilCopyMacAddress(pMgmtFrame->hdr.BSSID, params->transmittingBssid);
    }
    
    multiBSSIDParsingParams->SubElementIndex++;

    //Sub elemets more then the max number
    if( (multiBSSIDParsingParams->SubElementIndex > multiBSSIDParsingParams->MaxBSSIDIndicator) && 
        (multiBSSIDParsingParams->MaxBSSIDIndicator > 0) )
    {
        MLME_ERROR_PRINT("\n\r Warning !! sub element %d is bigger then the max subelements %d", 
            multiBSSIDParsingParams->SubElementIndex, multiBSSIDParsingParams->MaxBSSIDIndicator);

        mlmeParser_SetMoreSubelementsLeft(multiBSSIDParsingParams, FALSE);
        return OK;
    }
    
    //Find sub element for the next iteration.
    pSubElement = scanParser_findMbssidSubElement(pData_StartOfIEs, leftDataLen, multiBSSIDParsingParams->SubElementIndex);
    if(NULL!=pSubElement)
    {
        mlmeParser_SetMoreSubelementsLeft(multiBSSIDParsingParams, TRUE);
        multiBSSIDParsingParams->subElementLength = *(pSubElement+1);
        multiBSSIDParsingParams->pSubElementData = (pSubElement + 2); 
        MLME_REPORT_PRINT_PARSER("\n\rSub Element found !!! \n\r index = %d   length = %d",
            multiBSSIDParsingParams->SubElementIndex, multiBSSIDParsingParams->subElementLength);
    }
    else
    {
        mlmeParser_SetMoreSubelementsLeft(multiBSSIDParsingParams, FALSE);
        multiBSSIDParsingParams->subElementLength = 0;
        multiBSSIDParsingParams->pSubElementData = NULL; 
    }

    return OK;
}




int32_t scanParser_parseIEs(uint8_t *pData, scanIEParsingParams_t *params, uint8_t *pDataEnd, uint16_t leftDataLen, scanIEMultiBSSIDParams_t *multiBSSIDParsingParams)
{

    dot11_eleHdr_t *pEleHdr;
    uint32_t        readLen;

    MLME_REPORT_PRINT_PARSER("\n\rStart parsing BSSID index = 0x%x\n\r", multiBSSIDParsingParams->SubElementIndex);

    while (pData < pDataEnd)
    {
        pEleHdr = (dot11_eleHdr_t *)pData;

        switch (pEleHdr->eleId)
        {
            case SSID_IE_ID:
            {
                MLME_REPORT_PRINT_PARSER("\n\r SSID_IE_ID, eleLen:%d leftDataLen:%d \n\r",pEleHdr->eleLen, leftDataLen);

                if (mlmeParser_readSsid(pData, leftDataLen, &readLen, &params->ssid) != OK)
                {
                    MLME_ERROR_PRINT("\n\rERROR! SSID_IE_ID failed");
                    return-1;
                }
                if(params->ssid.serviceSetId[0] != 0)
                {
                    params->ssidIePresent = TRUE;
                }
            }
            break;

            case SUPPORTED_RATES_IE_ID:
            {
                MLME_REPORT_PRINT_PARSER("\n\r SUPPORTED_RATES_IE_ID, eleLen:%d\n\r",pEleHdr->eleLen);

                if (mlmeParser_readRates(pData, leftDataLen, &readLen, &params->rates) != OK)
                {
                    MLME_ERROR_PRINT("\n\rERROR! SUPPORTED_RATES_IE_ID failed");
                    return-1;
                }
                params->ratesIePresent = TRUE;
            }
            break;

            case EXT_SUPPORTED_RATES_IE_ID:
            {
                MLME_REPORT_PRINT_PARSER("\n\r EXT_SUPPORTED_RATES_IE_ID, eleLen:%d\n\r",pEleHdr->eleLen);
                if (mlmeParser_readRates(pData, leftDataLen, &readLen, &params->extRates) != OK)
                {
                    MLME_ERROR_PRINT("\n\rERROR! EXT_SUPPORTED_RATES_IE_ID failed");
                    return-1;
                }
                params->extRatesIePresent = TRUE;
            }
            break;

            case COUNTRY_IE_ID:
            {
                MLME_REPORT_PRINT_PARSER("\n\r COUNTRY_IE_ID, eleLen:%d\n\r",pEleHdr->eleLen);

                if (mlmeParser_readCountry(pData, leftDataLen, &readLen, &params->country) != OK)
                {
                    MLME_ERROR_PRINT("\n\rERROR! COUNTRY_IE_ID failed");
                    return-1;
                }
            }
            break;

            case DS_PARAMETER_SET_IE_ID:
            {
                MLME_REPORT_PRINT_PARSER("\n\r DS_PARAMETER_SET_IE_ID, eleLen:%d\n\r",pEleHdr->eleLen);

                if (mlmeParser_readDsParams(pData, leftDataLen, &readLen, &params->dsParams) != OK)
                {
                    MLME_ERROR_PRINT("\n\rERROR! DS_PARAMETER_SET_IE_ID failed");
                    return-1;
                }
            }
            //TODO:  check the channel is the same as the channel at the descriptor and is ok with the band
            break;

            case RSN_IE_ID:
            {
                MLME_REPORT_PRINT_PARSER("\n\r RSN_IE_ID, eleLen:%d\n\r",pEleHdr->eleLen);

                if (mlmeParser_readRsnIe(pData, leftDataLen, &readLen, &params->rsnIe) != OK)
                {
                    MLME_ERROR_PRINT("\n\rERROR! RSN_IE_ID failed,leftDataLen:%d pEleHdr->eleLen:%d",leftDataLen,pEleHdr->eleLen);
                    return-1;
                }
                params->rsnIeLen = params->rsnIe.hdr.eleLen + 2; //data len + 1 byte header + 1 byte len
            }
            break;

            case VENDOR_SPECIFIC_IE_ID: // WPA_IE is Vendor ID with oui equal to 0x00, 0x50, 0xf2, 1
            {
                MLME_REPORT_PRINT_PARSER("\n\r VENDOR_SPECIFIC_IE_ID, eleLen:%d\n\r",pEleHdr->eleLen);

                //In order for this Info element to be WPA, the oui field should equal 0x00, 0x50, 0xf2, 1
                //else it is vendor specific ie
                if ((*(pData + 1) > WPA_SELECTOR_LEN) &&  (RSN_SELECTOR_GET((pData + 2)) == WPA_OUI_TYPE))
                {
                    if (mlmeParser_readRsnIe(pData, leftDataLen, &readLen, &params->wpaIe) != OK) //Structure of rsnIe and wpaIe is quite similar so use the same parser function
                    {
                        MLME_ERROR_PRINT("\n\rERROR! VENDOR_SPECIFIC_IE_ID: failed :%d", leftDataLen);
                        return-1;
                    }
                    params->wpaIeLen = params->wpaIe.hdr.eleLen + 2; //data len + 1 byte header + 1 byte len
                }
                else if (WPA_GET_BE32(pData + 2) == RSNE_OVERRIDE_IE_VENDOR_TYPE)
                {
                    if (mlmeParser_readRsnIe(pData, leftDataLen, &readLen, &params->rsnOverrideIe) != OK)
                    {
                        MLME_ERROR_PRINT("\n\rERROR! RSNE_OVERRIDE_IE_VENDOR_TYPE: failed");
                        return -1;
                    }
                    params->rsnOverrideIeLen = params->rsnOverrideIe.hdr.eleLen + 2; //data len + 1 byte header + 1 byte len
                }
                else if (WPA_GET_BE32(pData + 2) == RSNE_OVERRIDE_2_IE_VENDOR_TYPE)
                {
                    if (mlmeParser_readRsnIe(pData, leftDataLen, &readLen, &params->rsnOverride2Ie) != OK)
                    {
                        MLME_ERROR_PRINT("\n\rERROR! RSNE_OVERRIDE_2_IE_VENDOR_TYPE: failed");
                        return -1;
                    }
                    params->rsnOverride2IeLen = params->rsnOverride2Ie.hdr.eleLen + 2; //data len + 1 byte header + 1 byte len
                }
                // look for wmm IE
                else if ( RSN_SELECTOR_GET((pData + 2)) ==  RSN_SELECTOR(0x00, 0x50, 0xf2, 2))
                {
                    if  (pEleHdr->eleLen == DOT_11_WMM_LEN)
                    {
                        params->wmmPresent = TRUE;
                        GTRACE(GRP_HE, "MLME_PARSER: Found WMM IE");
                    }
                }
                else if (WPA_GET_BE32(pData+2) == WPS_IE_VENDOR_TYPE) {
                        /* WPS */
                        params->wpsPresent = TRUE;
                        params->wpsLen = pEleHdr->eleLen+2;
                        os_memcpy(&params->wpsIe,pEleHdr, params->wpsLen);
                }
                readLen = pEleHdr->eleLen + 2;
            }
            break;
#ifndef DISABLE_WIFI6
            case VHT_CAPABILITY_IE_ID:

                MLME_REPORT_PRINT_PARSER("\n\r VHT_CAPABILITIES_IE_ID, eleLen:%d\n\r",pEleHdr->eleLen);

                readLen = pEleHdr->eleLen + 2;
                
                params->vhtCapabilitesPresent = TRUE;
            break;
#endif
            case HT_CAPABILITIES_IE_ID:
                MLME_REPORT_PRINT_PARSER("\n\r HT_CAPABILITIES_IE_ID, eleLen:%d\n\r",pEleHdr->eleLen);

                if (mlmeParser_readHtCapabilitiesIE(pData, leftDataLen, &readLen, &params->htCapabilities) != OK)
                {
                    MLME_ERROR_PRINT("\n\rERROR! HT_CAPABILITIES_IE_ID: failed");
                    return-1;
                }
                params->htCapabilitiesPresent = TRUE;
                break;

            case HT_INFORMATION_IE_ID:
                MLME_REPORT_PRINT_PARSER("\n\r HT_INFORMATION_IE_ID, eleLen:%d\n\r",pEleHdr->eleLen);

                if (mlmeParser_readHtInformationIE(pData, leftDataLen, &readLen, &params->htInformation) != OK)
                {
                    MLME_ERROR_PRINT("\n\rERROR! HT_INFORMATION_IE_ID: failed");
                    return-1;
                }
                params->htInformationPresent = TRUE;
                break;

            case EID_EXTENSION:
                MLME_REPORT_PRINT_PARSER("\n\r EID_EXTENSION, eleLen:%d\n\r",pEleHdr->eleLen);

                GTRACE(GRP_HE, "MLME_PARSER: eid extension found. eleID: %d",pEleHdr->eleId);
                if (mlmeParser_parseExtension(pData, leftDataLen, &readLen, params))
                {
                    MLME_ERROR_PRINT("\n\rERROR! EID_EXTENSION: failed");
                    return-1;
                }
                break;
            case ERP_IE_ID:
                MLME_REPORT_PRINT_PARSER("\n\r ERP_IE_ID, eleLen:%d\n\r",pEleHdr->eleLen);

                if (mlmeParser_readERP(pData, leftDataLen, &readLen, &params->erpIe, (uint8_t *)&(params->useProtection),(uint8_t *)&(params->barkerPreambleMode)) != OK)
                {
                     return-1;
                }
                params->erpPresent = TRUE;
                break;

            case MULTIPLE_BSSID: //assumption that no MULTIPLE_BSSID IE in a subelement (means that we only get here in the "first call").
                pEleHdr->eleId = *pData;
                pEleHdr->eleLen = *(pData+1);
                multiBSSIDParsingParams->MaxBSSIDIndicator = (1 << (*(pData+2))); 

                readLen = ((pEleHdr->eleLen) +2);
                break;

            default:
            {
                MLME_REPORT_PRINT_PARSER("\n\rdefault, eleid:%d eleLen:%d\n\r",pEleHdr->eleId,pEleHdr->eleLen);
                readLen = pEleHdr->eleLen + 2;
            }
            break;
        }

        pData       += readLen;
        leftDataLen -= readLen;
    }

    return 1;
}



/*
This function finds the next multiple bssid sub element by index. if it doesn't found returns null pointer.
*/
uint8_t* scanParser_findMbssidSubElement(uint8_t *pData, uint16_t len, uint8_t mbssidIndex)
{
    uint8_t *pMbssidTag, *pSubElement, *pMbssidIndexTag;
    uint8_t curr_subelement_index;
    uint8_t mbssidTag_Len, mbssidSubElement_Len, readLenInTag = 0;
    const uint8_t *pDataEnd = pData + len;

    MLME_REPORT_PRINT_PARSER("\n\r Looking for index %d ",mbssidIndex);
    while(TRUE == IEParser_FindIe(pData, len, MULTIPLE_BSSID, &pMbssidTag))
    {
        readLenInTag = 0;
        mbssidTag_Len = *(pMbssidTag+1);

        pSubElement =  pMbssidTag + 3;
        readLenInTag += 3;
        
        //Iterate over all Sub elements in the tag
        while(readLenInTag < mbssidTag_Len)
        {
            mbssidSubElement_Len = *(pSubElement+1);
            readLenInTag += (mbssidSubElement_Len + 2);
            
            //Iterate over all IEs of a Sub elements
            while(IEParser_FindIe((pSubElement + 2), mbssidSubElement_Len , MULTIPLE_BSSID_INDEX, &pMbssidIndexTag))
            {
                curr_subelement_index = *(pMbssidIndexTag+2);
                MLME_REPORT_PRINT_PARSER("\n\r Subelement with index %x found. \n\r mbssidIndex to find %x ", curr_subelement_index, mbssidIndex);
                if(mbssidIndex == curr_subelement_index)
                {
                    return pSubElement;
                }
                else{
                    break;
                }
            }
            pSubElement += (mbssidSubElement_Len +2 );
            MLME_REPORT_PRINT_PARSER("\n\r After advancing : *pSubElement = 0x%X , *(pSubElement+1) = 0x%X", *(pSubElement), *(pSubElement+1));
        }

        //Continue to next tag:
        pData = pMbssidTag + (mbssidTag_Len + 2);
        if (pData >=  pDataEnd)
        {
            break;
        }
        len = pDataEnd - pData;
    }

    MLME_REPORT_PRINT_PARSER("\n\r sub element with index %d did not found. return NULL.", mbssidIndex);
    return NULL;
}


Bool_e mlmeParser_getMoreSubelementsLeft(scanIEMultiBSSIDParams_t *pMBSSID)
{
    // CME_PRINT_SCAN_REPORT("\n\r get more sub elements = %d , address = 0x%X  , size is %d", pMBSSID->moreSubElementsLeft, (uint32_t)&(pMBSSID->moreSubElementsLeft), sizeof(pMBSSID->moreSubElementsLeft));
    return pMBSSID->moreSubElementsLeft;
}

void mlmeParser_SetMoreSubelementsLeft(scanIEMultiBSSIDParams_t *pMBSSID, Bool_e SubEleLeft)
{
    // CME_PRINT_SCAN_REPORT("\n\r set more sub elements left to %d", SubEleLeft);
    pMBSSID->moreSubElementsLeft = SubEleLeft;
}


/*
This function checks if the curr prob response / beacon supports MBSSID or not.
*/
Bool_e scanParser_CheckMbssidSupport(uint8_t *pData, uint16_t len)
{
    uint8_t *pMbssidTag;
    Bool_e returnVal = FALSE;

    returnVal = IEParser_FindIe(pData, len, MULTIPLE_BSSID, &pMbssidTag);
    return returnVal;
}


/******************************************************************************
  Function          : mlmeParser_parseExtension

  Description       : Parsing IEs that are under the extension eid field (=255). in this case the element will have another subfield called 
  					  extended eid, that will indicate the id number. The element leangth in the Length subfield will include the extension id.

  Input parameters  : uint8_t *pData						- 	pointer to the address to read from in the frame 
  					  uint16_t bodyDataLen				- 	total size left to read

  Output parameters : uint32_t *readLen  					- 	address of the output paramter, will store how many bites read form the function
					  scanIEParsingParams_t *pParams	- 	pointer to the paramter that will store the parsed ie

  Return value      :	0		-	on success
  					  	-1 		- 	on failure
 ******************************************************************************/

int32_t mlmeParser_parseExtension(uint8_t *pData, uint16_t bodyDataLen, uint32_t *readLen, scanIEParsingParams_t *pParams)
{
    HOOK(HOOK_IN_MLME_PARSER);

    dot11_eleHdr_t      *pEleHdr;
    uint8_t               eleIdExt;

    pEleHdr  = (dot11_eleHdr_t *)pData;

    eleIdExt = *(pData+2);

    GTRACE(GRP_HE, "MLME_PARSER:mlmeParser_parseExtension eidext=%d",eleIdExt);
    *readLen = pEleHdr->eleLen + sizeof(dot11_eleHdr_t);


    switch (eleIdExt)
    {
#ifndef DISABLE_WIFI6
        case MU_EDCA_PARAMETER_SET_IE_ID:
        
            if (mlmeParser_readHeMuEdcaParamerterSetIE(pData, bodyDataLen, readLen, &pParams->heMuEdcaAcParams) != OK)
            {
                return-1;
            }
            pParams->heMuEdcaAcParamsPresent = TRUE;
            GTRACE(GRP_HE_DBG, "MLME_PARSER: pParams->heMuEdcaAcParamsPresent: %d",pParams->heMuEdcaAcParamsPresent);

            break;

        case HE_CAPABILITIES_IE_ID:
            GTRACE(GRP_HE_DBG, "MLME_PARSER: HE_CAPABILITIES_IE_ID found: %d",HE_CAPABILITIES_IE_ID);
            if (mlmeParser_readHeCapabilitiesIE(pData, bodyDataLen, readLen, &pParams->heCapabilities) != OK)
            {
                return-1;
            }
            pParams->heCapabilitiesPresent = TRUE;
            GTRACE(GRP_HE_DBG, "MLME_PARSER: pParams->heCapabilities: %d",pParams->heCapabilitiesPresent);

            break;

        case HE_OPERATION_IE_ID:
            if (mlmeParser_readHeOperationIE(pData, bodyDataLen, readLen, &pParams->heOperation) != OK)
            {
                return-1;
            }
            pParams->heOperationPresent = TRUE;
            GTRACE(GRP_HE_DBG, "MLME_PARSER: pParams->heOperation: %d", pParams->heOperationPresent);
            break;
            //TODO: should we parse MU EDCA, no.38 too?
#endif


        default:
        {
            MLME_REPORT_PRINT_PARSER("\n\r mlmeParser_parseExtension, EID_EXTENSION ,unhandled extension : eleIdExt:%d: eleLen:%d\n\r",eleIdExt,pEleHdr->eleLen);
        }
        break;
    }

    return OK;

}


#ifndef DISABLE_WIFI6
/******************************************************************************
  Function          : mlmeParser_readHeMuEdcaParamerterSetIE

  Description       : Parsing HE Capabilities IE

  Input parameters  : uint8_t *pData									- 	pointer to the address to read from in the frame 
  					  uint16_t dataLen								- 	total size left to read

  Output parameters : uint32_t *readLen  								- 	address of the output paramter, will store how many bites read form the function
					  dot11HeCapabilitiesUnparse_t *pHeCapabilities	- 	pointer to the HE Capabilities paramter that will store the parsed ie

  Return value      :	0		-	on success
  					  	-1 		- 	on failure

  Coder             : gilsho
 ******************************************************************************/

static int32_t mlmeParser_readHeMuEdcaParamerterSetIE(uint8_t *pData, uint16_t dataLen, uint32_t *pReadLen, dot11HeMuEdcaAcParams_t *pHeMuEdcaAcParams)
{
    HOOK(HOOK_IN_MLME_PARSER);

    pHeMuEdcaAcParams->eleHdr.eleId = *pData;
    pHeMuEdcaAcParams->eleHdr.eleLen = *(pData +1);
    pHeMuEdcaAcParams->eleIdExt = *(pData+2);

    GTRACE(GRP_MLME, "MLME_PARSER: pHeMuEdcaAcParams->eleHdr.eleIdExt =%d.  pHeMuEdcaAcParams->eleHdr.eleLen=%d",pHeMuEdcaAcParams->eleIdExt,  pHeMuEdcaAcParams->eleHdr.eleLen);

    *pReadLen = pHeMuEdcaAcParams->eleHdr.eleLen + sizeof(pHeMuEdcaAcParams->eleHdr);

    if (dataLen < (uint32_t)(pHeMuEdcaAcParams->eleHdr.eleLen + 2))
    {
        return-1;
    }

    if (pHeMuEdcaAcParams->eleHdr.eleLen < DOT11_HE_MU_EDCA_MIN_TOTAL_LEN)
    {
        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: HE MU EDCA Param Set IE error: element Len=%d, Minimum len expected=%d", pHeMuEdcaAcParams->eleHdr.eleLen, DOT11_HE_MU_EDCA_ELE_MIN_LEN);
        return-1;
    }

    if (pHeMuEdcaAcParams->eleHdr.eleLen != DOT11_HE_MU_EDCA_MIN_TOTAL_LEN)
    {
        /*This IE can be extended. if so we are taking only first 24 bytes*/
        GTRACE(GRP_HE, "MLME_PARSER: HE MU EDCA Param Set IE : element Len=%d, Minimum len expected=%d. Taking minimum len only.", pHeMuEdcaAcParams->eleHdr.eleLen, DOT11_HE_MU_EDCA_ELE_MIN_LEN);
    }

    memcpy((void*)pHeMuEdcaAcParams->heMuEdcaAcParamsIe, pData + 3, DOT11_HE_MU_EDCA_ELE_MIN_LEN); //elements only without the ext.id

    return OK;
}



/******************************************************************************
  Function          : mlmeParser_readHeCapabilitiesIE

  Description       : Parsing HE Capabilities IE

  Input parameters  : uint8_t *pData									- 	pointer to the address to read from in the frame 
  					  uint16_t dataLen								- 	total size left to read

  Output parameters : uint32_t *readLen  								- 	address of the output paramter, will store how many bites read form the function
					  dot11HeCapabilitiesUnparse_t *pHeCapabilities	- 	pointer to the HE Capabilities paramter that will store the parsed ie

  Return value      :	0		-	on success
  					  	-1 		- 	on failure
 ******************************************************************************/

static int32_t mlmeParser_readHeCapabilitiesIE(uint8_t *pData, uint16_t dataLen, uint32_t *pReadLen, dot11HeCapabilitiesUnparse_t *pHeCapabilities)
{
    HOOK(HOOK_IN_MLME_PARSER);

    pHeCapabilities->eleHdr.eleId = *pData;
    pHeCapabilities->eleHdr.eleLen = *(pData +1);
    pHeCapabilities->eleIdExt = *(pData+2);

    GTRACE(GRP_MLME, "MLME_PARSER: pHeCapabilities->eleHdr.eleIdExt =%d.  pHeCapabilities->eleHdr.eleLen=%d",pHeCapabilities->eleIdExt,  pHeCapabilities->eleHdr.eleLen);

    *pReadLen = pHeCapabilities->eleHdr.eleLen + sizeof(pHeCapabilities->eleHdr);

    if (dataLen < (uint32_t)(pHeCapabilities->eleHdr.eleLen + 2))
    {
        return-1;
    }

    if (pHeCapabilities->eleHdr.eleLen < DOT11_HE_CAPABILITIES_MIN_TOTAL_LEN)
    {
        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: HE Capability IE error: element Len=%d, Minimum len expected=%d", pHeCapabilities->eleHdr.eleLen, DOT11_HE_CAPABILITIES_ELE_MIN_LEN);
        return-1;
    }

    if (pHeCapabilities->eleHdr.eleLen != DOT11_HE_CAPABILITIES_MIN_TOTAL_LEN)
    {
        /*This IE can be extended. if so we are taking only first 24 bytes*/
        GTRACE(GRP_HE, "MLME_PARSER: HE Capability IE : element Len=%d, Minimum len expected=%d. Taking minimum len only.", pHeCapabilities->eleHdr.eleLen, DOT11_HE_CAPABILITIES_ELE_MIN_LEN);
    }

    memcpy((void*)pHeCapabilities->heCapabilitiesIe, pData + 3, DOT11_HE_CAPABILITIES_ELE_MIN_LEN); //elements only without the ext.id

    return OK;
}

/******************************************************************************
  Function          : mlmeParser_readHeOperationIE

  Description       : Parsing HE Operation IE

  Input parameters  : uint8_t *pData									- 	pointer to the address to read from in the frame 
  					  uint16_t dataLen								- 	total size left to read

  Output parameters : uint32_t *readLen  								- 	address of the output paramter, will store how many bites read form the function
					  dot11HeOperationUnparse_t *pHeOperation		- 	pointer to the HE Operation paramter that will store the parsed ie

  Return value      :	0		-	on success
  					  	-1 		- 	on failure
 ******************************************************************************/

static int32_t mlmeParser_readHeOperationIE(uint8_t *pData, uint16_t dataLen, uint32_t *pReadLen, dot11HeOperationUnparse_t *pHeOperation)
{
    HOOK(HOOK_IN_MLME_PARSER);

    pHeOperation->eleHdr.eleId = *pData;
    pHeOperation->eleHdr.eleLen = *(pData+1);
    pHeOperation->eleIdExt = *(pData+2);

    GTRACE(GRP_MLME, "MLME_PARSER: pHeOperation->eleHdr.eleIdExt =%d.  pHeOperation->eleHdr.eleLen=%d",pHeOperation->eleIdExt,  pHeOperation->eleHdr.eleLen);

    *pReadLen = pHeOperation->eleHdr.eleLen + sizeof(pHeOperation->eleHdr);

    if (dataLen < (uint32_t)(pHeOperation->eleHdr.eleLen + 2))
    {
        return-1;
    }

    if (pHeOperation->eleHdr.eleLen < DOT11_HE_OPERATION_MIN_TOTAL_LEN)
    {
        GTRACE(GRP_GENERAL_ERROR, "MLME_PARSER: HE Capability IE error: element Len=%d, Minimum len expected=%d", pHeOperation->eleHdr.eleLen, DOT11_HE_OPERATION_ELE_MIN_LEN);
        return-1;
    }

    if (pHeOperation->eleHdr.eleLen != DOT11_HE_OPERATION_MIN_TOTAL_LEN)
    {
        /*This IE can be extended. if so we are taking only first 6 bytes*/
        GTRACE(GRP_HE, "MLME_PARSER: HE Information IE: eleLen=%d, ExpectedLen=%d. Taking minimum len only.", pHeOperation->eleHdr.eleLen, DOT11_HE_OPERATION_ELE_MIN_LEN);
    }

    memcpy((void*)pHeOperation->heOperationIe, pData + 3, DOT11_HE_OPERATION_ELE_MIN_LEN); //elements only without the ext.id


    return OK;
}
#endif
