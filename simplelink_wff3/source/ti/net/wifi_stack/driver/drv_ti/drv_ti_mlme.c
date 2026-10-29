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
  FILENAME:       drv_ti_mlme.c

  DESCRIPTION:	  This file handles construction/parsing of sent/received packets
  ----------------------------------------------------------------------------- */

#include "udata_api.h"
#include "udata_net_api.h"
#include "tx_ctrl_api.h"
#include "wlan_links.h"
#include "drv_ti_internal.h"
#include "common.h"
#include "common/ieee802_11_defs.h"
#include "common/ieee802_11_common.h"		// For parsing IEs of received packets

#include "eloop.h"
#include "mpdu.h"

#include "cme_fw_api.h"
#include "cme_internal_api.h"
#include "cme_supplicant_api.h"

#include "scan_result_table.h"      // For getting candidate parameters
#include "regulatory_domain_api.h"  // for powerCapability_t
#include "gtrace.h"
#include "l2_cfg.h"
#include "fw_utils.h"
#include "lower_mac_if.h"
#include "mlme_parser.h"
#include "80211_utils.h"


// ============================================================================
//		Modules private definitions
// ============================================================================

// The below affect connection sequence behavior
#define AUTH_MAX_TRIES			  (3)
#define ASSOC_MAX_TRIES           (3)
#define ASSOC_TIMEOUT_MSECS	 	(200)
#define AUTH_TIMEOUT_MSECS	 	(200)
#define RX_AUTH_TIMEOUT_MSECS   (200)   // Time to wait for auth response after successful transmission
#define DEAUTH_DEASSOC_TX_EXPIRY_TIME_USEC (8000)

// Device capabilities for building association request
// #define CC33_SUPOPORT_B_ONLY         // for supporting only B band
#define CC33_SUPPORT_IMMEDIATE_BA
#define CC33_SUPPORT_SUPPORT_HT
//#define CC33_SUPPORT_SUPPORT_WME
// #define CC33_SUPPORT_DELAYED_BA      // not supported also in WL8
// #define CC33_SUPPORT_PBCC            // not supported also in WL8

// Define how often the STA wakes to listen to Beacon management frames when
// in power save mode.
#define LISTEN_INTERVAL_DEF     (3)

// Association response sizes
#define AUTH_MSG_HEADER_LEN     (6)
#define MAX_CHALLANGE_LEN       (256)
#define MD_IE_LEN               (5)
#define MAX_RSN_IE_LEN          (258)
#define FT_IE_LEN               (258)
#define TSPEC_IE_LEN            (55)
#define RIC_REQUEST_LEN         (6 + TSPEC_IE_LEN*2) /* support upto 2 tspec renegotiation in reassociation */
#define MAX_ASSOC_MSG_LENGTH    (512 + MAX_EXTRA_IES_LEN)
#define MAX_AUTH_MSG_LEN        (MAX_EXTRA_IES_LEN + AUTH_MSG_HEADER_LEN)


#define TX_COMPLETE_TIMEOUT     (1000)


// ============================================================================
// 	Type definitions
// ============================================================================

// ============================================================================
//		Modules data base
// ============================================================================
// sync object deauth flow
extern OsiSyncObj_t gtxCompleteSyncObj;
extern volatile uint8_t gFwCrashOccurred;

// ============================================================================
//      External Functions
// ============================================================================
/* WLAN event dispatcher to host */
extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t * args, uint16_t argsLen);

// ============================================================================
//		Local Functions declarations
// ============================================================================

static uint16_t assocCapBuild(uint32_t aRoleId,
                              RoleType_e    aRoleType,
                              struct wpa_driver_associate_params *apParams,
                              cmeScanCandidateDesc_t *apCandidateScanRes);
static uint32_t assocQosBuild(uint32_t aRoleId, uint8_t *apWmeIeDest, uint8_t isHeConnection );
void deauthDisassocTxResultCb(void *apDesc);
static void wep_shared_auth_challenge(ti_driver_ifData_t  *apDrv,
                                     struct ieee80211_mgmt *mgmt,
                                     size_t len);


// ============================================================================
//		TX management packets
// ============================================================================

// ----------------------------------------------------------------------------
extern TMacAddr     g_fuse_mac_addr[];



int32_t ti_drv_txAuthReqPacket(ti_driver_ifData_t *apDrv, uint16_t aAuthType)
{

    TMgmtPktDesc        *pkt;
    uint32_t            payloadSize,total_len,extra =0;
    uint16_t            fc;

    dot11_mgmtHeader_t  *pDot11Header;
    uint8_t             authMsg[MAX_AUTH_MSG_LEN] = {0};

    authMsg_t           *pAuthMsg;

    pAuthMsg = (authMsg_t*)authMsg;

    payloadSize = sizeof(pAuthMsg->authAlgo) + apDrv->pAuthInfo->ie_len;

    /* SAE alg flow includes seqnum and status in the payload */
    if(aAuthType != AUTH_ALG_TYPE_SAE)
    {
        payloadSize += sizeof(pAuthMsg->seqNum) + sizeof(pAuthMsg->status);
    }

#ifdef CONFIG_SAE
    payloadSize += apDrv->pAuthInfo->auth_data_len;
#endif   

    /* allocate descriptor and payload */
    extra = IEEE80211_HT_CTL_LEN; // Add 4 bytes gap, may be filled later on by the PMAC
    total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + sizeof(dot11_mgmtHeader_t) + extra + payloadSize;

    pkt = udata_AllocTxMgmtPacket(sizeof(dot11_mgmtHeader_t) + extra,payloadSize,NULL );

    if(!pkt)
    {
        MLME_REPORT_PRINT_ERROR("\n\rdrv_ti_mlme:ti_drv_txAuthReqPacket: ERROR cannot allocate packet %d \n\r", payloadSize);
        return NOK;
    }
    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_txAuthReqPacket payloadSize:%d",payloadSize);

    pkt->ePktType = UDATA_TX_PKT_TYPE_WLAN_MGMT;

    
    //link was inserted by the command sta role start: see @cc3xxx_trnspt_cmd_if_start_role
    pkt->link     = wlanLinks_LinkMacFind(TIWDRV_NETIF_ID_STA, (uint8_t *)apDrv->pAuthInfo->peerInfo.bssid);

    if(INVALID_LINK == pkt->link)
    {
        MLME_REPORT_PRINT_ERROR("\n\rdrv_ti_mlme:ti_drv_txAuthReqPacket: ERROR unsupported link id %d \n\r", pkt->link);
        os_free(pkt);
        return NOK;
    }

    set_nab_tx_header(pkt->nabHeader, total_len);

    /* prepare WLAN header */
    pDot11Header = (dot11_mgmtHeader_t *) pkt->header;

    fc = DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_AUTH;
    if (aAuthType)
    {
        fc |= DOT11_FC_WEP;
        pkt->flags |= PKTF_ENCRYPT;
    }
    COPY_WLAN_WORD(&pDot11Header->fc, &fc);

    MAC_COPY (pDot11Header->DA, (uint8_t *)apDrv->pAuthInfo->peerInfo.bssid);
    MAC_COPY (pDot11Header->SA, (uint8_t *)apDrv->macAddr);
    MAC_COPY (pDot11Header->BSSID, (uint8_t *)apDrv->pAuthInfo->peerInfo.bssid);

    /* insert algorithm */
    pAuthMsg->authAlgo = aAuthType;

    /* insert sequense */
    pAuthMsg->seqNum = 1;

    /* insert status code */
    pAuthMsg->status = 0;

    apDrv->pAuthInfo->expectedTransaction = 2;

#ifdef CONFIG_SAE
    if(apDrv->pAuthInfo->auth_data_len > 0 && apDrv->pAuthInfo->auth_data != NULL)
    {
        uint8_t *ie_ptr = (uint8_t *)&pAuthMsg->seqNum + apDrv->pAuthInfo->auth_data_len;
        // Copy commit to auth packet
        os_memcpy(&pAuthMsg->seqNum, apDrv->pAuthInfo->auth_data, apDrv->pAuthInfo->auth_data_len);
        apDrv->pAuthInfo->expectedTransaction = pAuthMsg->seqNum; // U16 to U8?

        os_memcpy(ie_ptr, apDrv->pAuthInfo->ie, apDrv->pAuthInfo->ie_len);
    }
    else
    {
        uint8_t *ie_ptr = (uint8_t *)&pAuthMsg->status + sizeof pAuthMsg->status;
        if (apDrv->pAuthInfo->ie_len)
        {
            os_memcpy(ie_ptr, apDrv->pAuthInfo->ie, apDrv->pAuthInfo->ie_len);
        }
    }
#endif

    pkt->flags |= PKTF_EXTERNAL_CONTEXT;

    /* copy payload */

    os_memcpy(pkt->payload, authMsg, payloadSize);


    pkt->fTxCompleteCb = (TMgmtPacketCb)CME_TxResult;

    MLME_REPORT_PRINT("\n\rsend txAuthReqPacket, linkId:%d",pkt->link);

    /* submit for tx */
    udata_SendTxMgmtPacket(pkt);

    return OK;

}

//Send TX auth response packet
int32_t ti_drv_txAuthResPacket(ti_driver_ifData_t *apDrv, uint8_t* destAddr, uint16_t authType, uint16_t auth_transaction, uint16_t statusCode,
                             const u8 *extra, size_t extra_len, int encrypt)
{
    TMgmtPktDesc    *pkt;
    uint32_t          payloadSize,total_len=0,extraHThdr;
    uint16_t        fc;

    dot11_mgmtHeader_t  *pDot11Header;
    uint8_t             authMsg[MAX_AUTH_MSG_LEN] = {0};

    authMsg_t           *pAuthMsg;

    pAuthMsg            = (authMsg_t*)authMsg;

    payloadSize = sizeof(pAuthMsg->authAlgo) + sizeof(pAuthMsg->seqNum) + sizeof(pAuthMsg->status);
    payloadSize += extra_len;

    extraHThdr = IEEE80211_HT_CTL_LEN; // Add 4 bytes gap, may be filled later on by the PMAC
    total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + sizeof(dot11_mgmtHeader_t) + extraHThdr + payloadSize;

    pkt = udata_AllocTxMgmtPacket(sizeof(dot11_mgmtHeader_t) + extraHThdr,payloadSize ,NULL);

    if(!pkt)
    {
        MLME_REPORT_PRINT_ERROR("\n\rdrv_ti_mlme:ti_drv_txAuthResPacket: ERROR cannot allocate packet \n\r");
        return NOK;
    }
    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_txAuthResPacket\n\r ");

    set_nab_tx_header(pkt->nabHeader, total_len );//TODO check if it can be moved to lower layers

    if(extra)
    {
        /* This is the address of the payload. */
        os_memcpy(((uint8_t*)(pAuthMsg)) + (payloadSize - extra_len), extra, extra_len);
    }

    pkt->ePktType = UDATA_TX_PKT_TYPE_WLAN_MGMT;
    pkt->link = udataNet_GetTxMgmtLink(
                apDrv->roleType ? TIWDRV_NETIF_ID_SAP : TIWDRV_NETIF_ID_STA,
                (uint8_t*) destAddr);

    if(INVALID_LINK == pkt->link )
    {
        Report("\n\r ti_drv_txAuthResPacket: ERROR unsupported link id %d \n\r", pkt->link);
        os_free(pkt);
        return NOK;
    }

    /* prepare WLAN header */
    pDot11Header = (dot11_mgmtHeader_t *) (pkt->header);

    fc = DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_AUTH;
    if (encrypt)
    {
        fc |= FCTL_PROTECTED;
        pkt->flags |= PKTF_ENCRYPT;
    }
    COPY_WLAN_WORD(&pDot11Header->fc, &fc);

    MAC_COPY (pDot11Header->DA, (uint8_t *)destAddr);
    MAC_COPY (pDot11Header->SA, (uint8_t *)apDrv->macAddr);
    MAC_COPY (pDot11Header->BSSID, (uint8_t *)destAddr);


    /* insert algorithm */
    pAuthMsg->authAlgo = authType;

    /* insert sequense */
    pAuthMsg->seqNum = auth_transaction;

    /* insert status code */
    pAuthMsg->status = statusCode;


    pkt->flags |= PKTF_EXTERNAL_CONTEXT;

    /* copy payload */
    os_memcpy(pkt->payload, authMsg, payloadSize);

    /* submit for tx */
    udata_SendTxMgmtPacket(pkt);

    return OK;

}


// ----------------------------------------------------------------------------
// Code is based on MCP mlme_assocRequestMsgBuild
// ----------------------------------------------------------------------------
int32_t ti_drv_txAssocReqPacket(ti_driver_ifData_t *apDrv,
                      struct wpa_driver_associate_params *apParams)
{
    TMgmtPktDesc    *pkt;
    int32_t          status =  OK;


    dot11_SSID_t          *pDot11Ssid;
    dot11_RATES_t         *pDot11Rates;
    struct ieee80211_mgmt  *pMngPack;
    uint8_t  ratesBuf[DOT11_MAX_SUPPORTED_RATES];
    uint8_t   *pPack;
    uint32_t  len,total_len;
    uint32_t  actualSize = 0, extraHThdr;
    uint8_t   fixedFieldsLen = 0;
    uint32_t  taggedFieldsLen = 0;
    uint32_t  packType = FRAME_TYPE_ASSOCIATION_REQ;
    uint16_t  capabilities;
    uint32_t  supportedRatesBM = 0, basicRatesBM = 0;
    cmeScanCandidateDesc_t *pCandidateDesc;
    uint16_t           fc;
    CipherSuite_e cipherSuite = rsn_getPairwiseSuite();
    uint8_t   isHeConnection;
    dot11_mgmtHeader_t  *pDot11Header;


    // Added for correct rates configuration
    Channel_e apChannel;
    uint8_t apBand_temp;

    uint8_t band_cfg = l2_GetPhyConfig();

    // In case of association timeout, request is originated by internally,
    // so apParams is NULL. The already transmitted association request packet
    // is retransmitted.
    if (NULL == apParams)
    {
        // we not released yet the packet just transmit again and increase the retries counter
        if(NULL == apDrv->pAssocInfo->pDescriptor)
        {
            // should not get here
            ASSERT_GENERAL(0);
        }
        // If packet is not waiting in TX queue, revert pointer & size (which
        // were updated by PMAC) and resend
        if ( (ASSOC_REQ_DESC_SENT_TO_PMAC != apDrv->pAssocInfo->descriptorState) &&
             (ASSOC_REQ_DESC_PENDING_TX != apDrv->pAssocInfo->descriptorState) )
        {

            MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_txAssocReqPacket resend");

            // Prepare the packet
            CmeTxDesc_t *pDesc = (CmeTxDesc_t *)apDrv->pAssocInfo->pDescriptor;

            /* allocate descriptor and payload */
            extraHThdr = IEEE80211_HT_CTL_LEN; // Add 4 bytes gap, may be filled later on by the PMAC
            total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + sizeof(dot11_mgmtHeader_t) + extraHThdr + pDesc->uPayloadLen;

            pkt = udata_AllocTxMgmtPacket(sizeof(dot11_mgmtHeader_t) + extraHThdr,pDesc->uPayloadLen,NULL );

            if(!pkt)
            {
                MLME_REPORT_PRINT_ERROR("\n\rti_drv_txAssocReqPacket: ERROR resend cannot allocate packet \n\r");
                return NOK;
            }

            set_nab_tx_header(pkt->nabHeader, total_len );//TODO check if it can be moved to lower layers

            pkt->ePktType    = UDATA_TX_PKT_TYPE_WLAN_MGMT;
            pkt->link        = pDesc->link;

            /* copy header */
            os_memcpy(pkt->header, (void*)(pDesc->address), pDesc->uHeaderLen-extraHThdr);
            /* copy payload */
            os_memcpy(pkt->payload, (uint8_t *)pDesc->address + pDesc->uHeaderLen, pDesc->uPayloadLen);

            pkt->flags |= PKTF_EXTERNAL_CONTEXT;
            pkt->fTxCompleteCb = (TMgmtPacketCb)CME_TxResult;


            /* submit for tx */
            udata_SendTxMgmtPacket(pkt);

        }
        else
        {
            // we're still waiting for PMAC to send the previous assoc request
            GTRACE(GRP_DRIVER_CC33, "Association request retry, waiting for PMAC to send previous assoc ");
            MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_txAssocReqPacket Association request retry, waiting for FW to send previous assoc");

        }
        // Timer for timeout should be armed anyway
        // Arm a timer limiting the time we're waiting for association response
        apDrv->pAssocInfo->timeoutMS = ASSOC_TIMEOUT_MSECS;
        eloop_register_timeout(0,                        // seconds
                               ASSOC_TIMEOUT_MSECS*1000, // useconds, TODO - review this number
                               ti_drv_AssocTimeout,     // Timeout callback
                               apDrv,                    // eloop data
                               NULL);                   // pointer to packet

        ++apDrv->pAssocInfo->tries;

        HOOK(HOOK_DRV_TI_MLME);

        return OK;

    }
    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_txAssocReqPacket");

    // In WPS, several scan results may exists. So, anyway, search the appropriate candidate in the scan results table.
    //Find the target network in the candidates table
    pCandidateDesc = CME_FindBssidInCandidatesScanTable (apParams->bssid);

    if (NULL == pCandidateDesc)
    {
        HOOK(HOOK_DRV_TI_MLME);

        //TODO: cannot happen...(?)
        ASSERT_GENERAL(FALSE);
        return NOK;
    }


    pMngPack = os_zalloc(MAX_ASSOC_MSG_LENGTH);
    
    if (FALSE == IRQ_UtilIsZeroMacAddress(apDrv->pAssocInfo->prev_bssid))
    {
        packType = FRAME_TYPE_REASSOCIATION_REQ;
    }


    // Set destination address & callback parameters
    //      o All other paramateres are set in the allocating function
    //      o By default, no callbakc function is set.
    apDrv->pAssocInfo->descriptorState = ASSOC_REQ_DESC_SENT_TO_PMAC;

    pPack = (uint8_t*)&pMngPack->u.assoc_req;

    //
    // Capabilities
    //
    capabilities = assocCapBuild(apDrv->roleId, apDrv->roleType ,apParams, pCandidateDesc);
    GTRACE(GRP_DRIVER_CC33, "Set capabilities field 0x%x", capabilities);

    pMngPack->u.assoc_req.capab_info = capabilities;
    pPack += sizeof(uint16_t);
    actualSize += sizeof(uint16_t);
    fixedFieldsLen += sizeof(uint16_t);
    GTRACE(GRP_DRIVER_CC33, "added capa actual size %d", actualSize);

    //
    // Listen interval
    //
    pMngPack->u.assoc_req.listen_interval = host_to_le16(LISTEN_INTERVAL_DEF);
    pPack += sizeof(uint16_t);
    actualSize += sizeof(uint16_t);
    fixedFieldsLen += sizeof(uint16_t);
    GTRACE(GRP_DRIVER_CC33, "added listen int actual size %d", actualSize);


    //
    // For re-association only insert current AP MAC address
    //
    if (FRAME_TYPE_REASSOCIATION_REQ == packType)
    {
        IRQ_UtilCopyMacAddress(apDrv->pAssocInfo->prev_bssid, pPack);
        GTRACE(GRP_DRIVER_CC33, "Prev AP MAC address: %x:%x:%x:%x:%x:%x",
            pPack[0], pPack[1], pPack[2], pPack[3], pPack[4], pPack [5]);

        pPack += MAC_ADDR_LEN;
        actualSize += MAC_ADDR_LEN;
        fixedFieldsLen += MAC_ADDR_LEN;

        GTRACE(GRP_DRIVER_CC33, "added MAC address actual size %d", actualSize);
    }

    //
    // SSID
    //
    pDot11Ssid = (dot11_SSID_t *)pPack;
    pDot11Ssid->hdr.eleId = SSID_IE_ID;
    pDot11Ssid->hdr.eleLen = apParams->ssid_len;
    os_memcpy((uint8_t *)pDot11Ssid->serviceSetId, apParams->ssid, apParams->ssid_len);
    pPack += apParams->ssid_len + sizeof(dot11_eleHdr_t);
    actualSize += apParams->ssid_len + sizeof(dot11_eleHdr_t);
    GTRACE(GRP_DRIVER_CC33, "added SSID len %d actual size %d", apParams->ssid_len, actualSize);

    //
    // Rates element
    //
    // A unified bit field of local and peer supported rates was set on role DB
    // when role was started. Published rates contain only peer supported rates.


    cfgGetRates(apDrv->roleType, &basicRatesBM, &supportedRatesBM);
    basicRatesBM = 0; // association request should not publish basic rates, so removing the default initialization 

    // Remove 11b rates when connecting to 5Ghz AP
    if (freq_to_chan(apDrv->freq, &apChannel, &apBand_temp))
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: failed to get channel from freq %d for role %d",
                                       apDrv->freq, apDrv->roleType);
        return -1;
    }
    if (!(is_bg_channel(apChannel)))
    {
        supportedRatesBM = supportedRatesBM & ~ANY_B_RATE;
    }

    os_memset(ratesBuf, 0, DOT11_MAX_SUPPORTED_RATES);
    len = convertBitmapToRatesIe(supportedRatesBM, basicRatesBM, ratesBuf);

    // Supported rates IE
    pDot11Rates = (dot11_RATES_t *)pPack;
    pDot11Rates->hdr.eleId = SUPPORTED_RATES_IE_ID;

    if (len <= SUPPORTED_RATES_MAX_IE_LEN)
        pDot11Rates->hdr.eleLen = len;
    else
        pDot11Rates->hdr.eleLen = SUPPORTED_RATES_MAX_IE_LEN;

    os_memcpy((void *)pDot11Rates->rates, ratesBuf, pDot11Rates->hdr.eleLen);
    pPack += pDot11Rates->hdr.eleLen + sizeof(dot11_eleHdr_t);
    actualSize += pDot11Rates->hdr.eleLen + sizeof(dot11_eleHdr_t);



    // Extended supported rates IE
    if (SUPPORTED_RATES_MAX_IE_LEN < len)
    {
        pDot11Rates = (dot11_RATES_t *)pPack;
        pDot11Rates->hdr.eleId  = EXT_SUPPORTED_RATES_IE_ID;
        pDot11Rates->hdr.eleLen = len - SUPPORTED_RATES_MAX_IE_LEN;
        os_memcpy((void *)pDot11Rates->rates, &ratesBuf[SUPPORTED_RATES_MAX_IE_LEN], pDot11Rates->hdr.eleLen);
        pPack += pDot11Rates->hdr.eleLen + sizeof(dot11_eleHdr_t);
        actualSize += pDot11Rates->hdr.eleLen + sizeof(dot11_eleHdr_t);
    }

    GTRACE(GRP_DRIVER_CC33, "added supported rates actual size %d supported rates BM 0x%x",
                             actualSize, supportedRatesBM);

    //
    // Spectrum management
    //
    if (pCandidateDesc->mScanResult.caps & DOT11_SPECTRUM_MANAGEMENT)
    {
        powerCapability_t powerCapability;
        dot11_CAPABILITY_t *pDot11PowerCapability = (dot11_CAPABILITY_t *)pPack;
        int8_t maxTxPower;

        regulatoryDomain_GetPowerCapability(&powerCapability, apChannel);

        pDot11PowerCapability->hdr.eleId = DOT11_CAPABILITY_ELE_ID;
        pDot11PowerCapability->hdr.eleLen = DOT11_CAPABILITY_ELE_LEN;
        pDot11PowerCapability->minTxPower = WLAN_MIN_TX_POWER_DBM;
        if (TRUE == regulatoryDomain_getChMaxPower(apChannel, &maxTxPower))
        {
            pDot11PowerCapability->maxTxPower = maxTxPower;
        }
        else
        {
            pDot11PowerCapability->maxTxPower = WLAN_MAX_TX_POWER_DBM;
        }

        pPack += DOT11_CAPABILITY_ELE_LEN + sizeof(dot11_eleHdr_t);
        actualSize += DOT11_CAPABILITY_ELE_LEN + sizeof(dot11_eleHdr_t);

        GTRACE(GRP_DRIVER_CC33, "added capability ELE actual size %d", actualSize);
    }

    //
    // Security info
    //

    GTRACE(GRP_DRIVER_CC33, "wpa_ie_len %d wps %d", apParams->wpa_ie_len, apParams->wps);

    os_memcpy(pPack, apParams->wpa_ie, apParams->wpa_ie_len);

    utilsDumpHex((uint8_t *)pPack, apParams->wpa_ie_len);

    pPack += apParams->wpa_ie_len;
    actualSize += apParams->wpa_ie_len;
    GTRACE(GRP_DRIVER_CC33, "added wpa_ie actual size %d", actualSize);
    //
   // HT capabilities
   //
   // If peer has published HT capabilities & HT information, discard HT rates
   // from Association Request for TKIP and WEP

    if ( (FALSE != cfgIsStaWmeEnabled()) &&
         (FALSE != pCandidateDesc->mHtInformationPresent) &&
         (FALSE != pCandidateDesc->mHtCapabilitiesPresent) )
    {
        if ( (CIPHER_SUITE_TKIP != cipherSuite) && (CIPHER_SUITE_WEP != cipherSuite) )
        {
            len = l2_cfgBuildHtCapabilitiesIe(apDrv->roleId, pPack);
            pPack += len;
            actualSize += len;
            GTRACE(GRP_DRIVER_CC33, "added HT capabilities size %d", actualSize);
        }
    }
 

#ifndef DISABLE_WIFI6
    /* VHT (WiFi5) and HE (WiFi6) are not yet separated - both guarded by DISABLE_WIFI6.
     * WiFi5 certification is mandatory for WiFi6 certification.
     * When Wifi5 will need to be implemented a separate guard for VHT (WiFi5) is needed. */
    //if channel is 5GHZ, then add VHT Support
    if(!(is_bg_channel(apChannel)))
    {
        if((band_cfg == L2_CFG_BAND_ONLY_5GHZ) || (band_cfg == L2_CFG_BAND_BOTH))    
        {
            if(FALSE != (pCandidateDesc->mVhtCapabilitesPresent && l2_cfg_isStaHeEnabled() && !(l2_GetWirelessProto()) ))
            {
        
                if ( (CIPHER_SUITE_TKIP != cipherSuite) && (CIPHER_SUITE_WEP != cipherSuite) )
                {
                    len = l2_cfgBuildVhtCapabilitiesIe(apDrv->roleId, pPack);
                    pPack += len;
                    actualSize += len;
                    GTRACE(GRP_DRIVER_CC33, "added VHT capabilities Size %d", actualSize);
        
                    len = l2_cfgBuildOperatingModeNotifcationIe(apDrv->roleId, pPack);
                    pPack += len;
                    actualSize += len;
                    GTRACE(GRP_DRIVER_CC33, "added Operating Mode Notification Size %d", actualSize);
                }
            }
        }
    }
    isHeConnection = l2_cfg_isStaHeEnabled() && !(l2_GetWirelessProto()) &&
                    (FALSE != pCandidateDesc->mHeCapabilitiesPresent) &&
                    (FALSE != pCandidateDesc->mHeOperationPresent);
    //HE
    if  (isHeConnection)
    {
        if ( (CIPHER_SUITE_TKIP != cipherSuite) && (CIPHER_SUITE_WEP != cipherSuite) )
        {
            len = l2_cfgBuildHeCapabilitiesIe(apDrv->roleId, pPack);
            pPack += len;
            actualSize += len;
            GTRACE(GRP_DRIVER_CC33, "added HE capabilities size %d", actualSize);
        }
        else // in case of TKIP\WEP connection remove HE
        {
            GTRACE(GRP_DRIVER_CC33, "TKIP/WEP connection - doesn't support HE");
            isHeConnection = FALSE;
        }
    }
    else
    {
        GTRACE(GRP_DRIVER_CC33, "Device doesn't support 11ax, no HE capabilities IE");
    }
#endif

    //
    // WMM IE
    //
    if (FALSE != cfgIsStaWmeEnabled() && FALSE != pCandidateDesc->wmmIePresent)
    {
        len = assocQosBuild(apDrv->roleId, pPack,isHeConnection);
        pPack += len;
        actualSize += len;
        GTRACE(GRP_DRIVER_CC33, "added QOS actual size %d", actualSize);
    }

    //add Vendor elements to Assoc request
    if(apDrv->vendorIEInfo.vendor_elements_length > 0)
    {
        len = apDrv->vendorIEInfo.vendor_elements_length;
        if((actualSize +len) > MAX_ASSOC_MSG_LENGTH)
        {
            GTRACE(GRP_DRIVER_CC33, "Error!vendor elements actual size %d is bigger than max size", actualSize);
            MLME_REPORT_PRINT_ERROR( "\n\rERROR!vendor elements actual size %d is bigger than max size", actualSize);
        }
        else
        {
            os_memcpy(pPack, apDrv->vendorIEInfo.vendor_elements,len);
            pPack += len;
            actualSize += len;
            GTRACE(GRP_DRIVER_CC33, "added vendor iE size %d", actualSize);
            MLME_REPORT_PRINT( "\n\radded vendor iE size %d", actualSize);
        }
    }

    //
    // Extended capabilities
    //
    /* allocate descriptor and payload */
    extraHThdr = IEEE80211_HT_CTL_LEN; // Add 4 bytes gap, may be filled later on by the PMAC
    total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + sizeof(dot11_mgmtHeader_t) + extraHThdr + actualSize;

    pkt = udata_AllocTxMgmtPacket(sizeof(dot11_mgmtHeader_t) + extraHThdr,actualSize,NULL);

    if(!pkt)
    {
        MLME_REPORT_PRINT_ERROR("\n\r ti_drv_txAssocReqPacket: ERROR cannot allocate packet \n\r");
        status = NOK;
        goto free;
    }

    set_nab_tx_header(pkt->nabHeader, total_len );//TODO check if it can be moved to lower layers

    pkt->ePktType = UDATA_TX_PKT_TYPE_WLAN_MGMT;
    pkt->link     = udataNet_GetTxMgmtLink(TIWDRV_NETIF_ID_STA, (uint8_t *)apDrv->pAssocInfo->peerInfo.bssid);


    if(INVALID_LINK == pkt->link)
    {
        Report("\n\rti_drv_txAssocReqPacket: ERROR unsupported link id %d \n\r", pkt->link);
        status = NOK;
        goto free;
    }

    /* prepare WLAN header */
    pDot11Header = (dot11_mgmtHeader_t *) (pkt->header);

    fc = DOT11_FC_TYPE_MGMT;

    if (FRAME_TYPE_REASSOCIATION_REQ == packType)
    {
        fc |= DOT11_FC_SUB_REASSOC_REQ;
    }
    else
    {
        fc |= DOT11_FC_SUB_ASSOC_REQ;
    }

    COPY_WLAN_WORD(&pDot11Header->fc, &fc);

    MAC_COPY (pDot11Header->DA, (uint8_t *)apDrv->pAssocInfo->peerInfo.bssid);
    MAC_COPY (pDot11Header->SA, (uint8_t *)apDrv->macAddr);
    MAC_COPY (pDot11Header->BSSID, (uint8_t *)apDrv->pAssocInfo->peerInfo.bssid);

    /* copy payload */
    os_memcpy(pkt->payload, (void*)(pPack - actualSize), actualSize);

    pkt->flags |= PKTF_EXTERNAL_CONTEXT;

    pkt->fTxCompleteCb = (TMgmtPacketCb)CME_TxResult;

    /* submit for tx */
    udata_SendTxMgmtPacket(pkt);

    /* copy for re-assocation if needed */
    CmeTxDesc_t *cme_pkt = CME_CopyTxDesc((void *)pkt, 0);
    apDrv->pAssocInfo->pDescriptor = (void *)cme_pkt;

    taggedFieldsLen = actualSize - fixedFieldsLen;
    apDrv->assoc_req_ies = os_zalloc(taggedFieldsLen);
    if (apDrv->assoc_req_ies == NULL)
    {
        apDrv->assoc_req_ies_len = 0;
    }
    else
    {
        os_memcpy(apDrv->assoc_req_ies, (uint8_t *)&(pMngPack->u.assoc_req.capab_info) + fixedFieldsLen, taggedFieldsLen);
        apDrv->assoc_req_ies_len = taggedFieldsLen;
    }

    // Arm a timer limiting the time we're waiting for association response
    apDrv->pAssocInfo->timeoutMS = ASSOC_TIMEOUT_MSECS;
    eloop_register_timeout(0,                        // seconds
                           ASSOC_TIMEOUT_MSECS*1000, // useconds, TODO - review this number
                           ti_drv_AssocTimeout,     // Timeout callback
                           apDrv,                    // eloop data
                           NULL);                    // user data

free:
    os_free(pMngPack);
    GTRACE(GRP_DRIVER_CC33, "Association request was successfully sent to L2");
    return status;
}

// ----------------------------------------------------------------------------
Bool32 ti_drv_AuthReqCB(void *aDesc, void *apDrv)
{

    CmeTxDesc_t        *pDesc = (CmeTxDesc_t *)aDesc;
    ti_driver_ifData_t    *pDrv = (ti_driver_ifData_t *)apDrv;
    Bool_e                 txStatus;

    txStatus = pDesc->status;

    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_AuthReqCB ");

    // If auth request was received in the mean time, there's nothing to do here
    if ( (NULL == pDrv->pAuthInfo) || (TRUE == pDrv->pAuthInfo->done) )
    {
        GTRACE(GRP_DRIVER_CC33, "Auth response was received before handling auth request exchange");
        return TRUE;
    }

    //
    // If we got here, behavior depends on TX status
    //

    // If peer got our request, we wait for auth response for a limited time
    if (1 == txStatus)
    {
        GTRACE(GRP_DRIVER_CC33, "TX auth request was successfully completed, waiting for response, num retries %d", pDrv->pAuthInfo->tries);

        // Set timeout event for the reception of auth response.
        // In case of timeout, try again.
        pDrv->pAuthInfo->timeoutMS = RX_AUTH_TIMEOUT_MSECS;
    }
    // else, expiry or peer hasn't got the packet, try again
    else
    {
        GTRACE(GRP_DRIVER_CC33, "TX auth request failed, status = %d num retries %d",
                                 txStatus, pDrv->pAuthInfo->tries);

        pDrv->pAuthInfo->timeoutMS = AUTH_TIMEOUT_MSECS;

        // If we got maximal number of retries there's no point in waiting for
        // another timeout, activate the CB immediately
        if (AUTH_MAX_TRIES == pDrv->pAuthInfo->tries)
        {
            pDrv->pAuthInfo->timeoutMS = 0;
        }
    }

    HOOK(HOOK_DRV_TI_MLME);

    eloop_register_timeout(0,                       // seconds
                   pDrv->pAuthInfo->timeoutMS*1000, // useconds
                   ti_drv_AuthTimeout,             // Timeout callback
                   pDrv,                            // eloop data
                   NULL);                           // user data

    return TRUE;
}

// ----------------------------------------------------------------------------
Bool32 ti_drv_AssocReqCB(void *aDesc, void *apDrv)
{
    CmeTxDesc_t           *pDesc = (CmeTxDesc_t *)aDesc;
    ti_driver_ifData_t    *pDrv = (ti_driver_ifData_t *)apDrv;
    Bool_e                txStatus;
    Bool32                releaseDesc = TRUE;

    txStatus = pDesc->status;

    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_AssocReqCB");

    // If assoc DB is still valid, and the descriptor ID matches the one we are waiting on, mark that packet was handed by PMAC to SW, and
    // descriptor may be released after association response was received or TX max
    // retries was reached.
    if ((NULL != pDrv->pAssocInfo) && txStatus == 1)
    {
        GTRACE(GRP_DRIVER_CC33, "Association request completed. result = %d, waiting for assoc response", pDesc->status);
        MLME_REPORT_PRINT("\n\rAssociation request completed. result = %d, waiting for assoc response", pDesc->status);
        pDrv->pAssocInfo->descriptorState = ASSOC_REQ_DESC_PENDING_ASSOC_RESP;

        releaseDesc = TRUE;
    }
    // else, association phase was already completed, descriptor should be released
    else
    {
        GTRACE(GRP_DRIVER_CC33, "Association request completed, releasing the packet");
        MLME_REPORT_PRINT("\n\rAssociation request completed, releasing the packet");
    }

    return releaseDesc;
}

//Not needed anymore (using managed sequence for sending deauth/disassoc...

// ----------------------------------------------------------------------------
/*!
    \brief      Send deauthentication / disassociation packet

    Send Deauth / disassoc packet via the ltxp.
    This is a blocking function. Waits on a sync object till tx complete.

    \param

    \return     0 on success, -1 otherwise
*/
int32_t ti_drv_txDeauthDisassocPacket(ti_driver_ifData_t *apDrv,
                                    uint8_t  *apBssid,
                                    uint32_t aType,
                                    uint16_t aReason)
{
    TMgmtPktDesc        *pkt;
    uint32_t            payloadSize,total_len,extraHThdr;
    uint16_t            fc;
    dot11_mgmtHeader_t  *pDot11Header;
    OsiReturnVal_e      osiRetVal;
    char macStrSA[MAC_STR_LEN], macStrDA[MAC_STR_LEN];
    uint8_t             SecureHdrLength = 0;
    uint32_t            link = INVALID_LINK;
    int32_t             ret = OK;

    payloadSize = sizeof(deAuth_t); //for disconnect send 2 bytes with reason
    extraHThdr = IEEE80211_HT_CTL_LEN; // Add 4 bytes gap, may be filled later on by the PMAC

    if (ROLE_IS_TYPE_STA_BASED(apDrv->roleType))
    {
        link = udataNet_GetTxMgmtLink(TIWDRV_NETIF_ID_STA, (uint8_t *)apBssid);
    }
    else
    {
        link = udataNet_GetTxMgmtLink(TIWDRV_NETIF_ID_SAP, (uint8_t *)apBssid);
    }

    if (INVALID_LINK == link)
    {
        MLME_REPORT_PRINT_ERROR("\n\rERROR ti_drv_txDeauthDisassocPacket: ERROR unsupported link id %d \n\r", link);
        GTRACE(GRP_DRIVER_CC33, "ti_drv_txDeauthDisassocPacket: ERROR No valid hlid was found!  NetifId = %d", link);
        return NOK;
    }
    //identify if encripted mgmt frame only if not broadcast
    if (txCtrlParams_GetMgmtEncryptMode(link) && !MAC_MULTICAST((uint8_t *)apBssid))
    {
        SecureHdrLength = RSN_SEC_LEN;
        extraHThdr += SecureHdrLength;
        GTRACE(GRP_DRIVER_CC33, "ti_drv_txDeauthDisassocPacket:SecureHdrLength!! ");
    }
        
    
    total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + sizeof(dot11_mgmtHeader_t) + extraHThdr + payloadSize;

    pkt = udata_AllocTxMgmtPacket(sizeof(dot11_mgmtHeader_t) + extraHThdr,payloadSize,NULL );

    if(!pkt)
    {
        MLME_REPORT_PRINT_ERROR("\n\rERROR ti_drv_txDeauthDisassocPacket: ERROR cannot allocate packet");
        return NOK;
    }

    set_nab_tx_header(pkt->nabHeader, total_len );//TODO check if it can be moved to lower layers

    pkt->ePktType = UDATA_TX_PKT_TYPE_WLAN_MGMT;

    pkt->link = link;
    
    GET_MAC_STR(apDrv->macAddr, macStrSA);
    GET_MAC_STR(apBssid,macStrDA);

    MLME_REPORT_PRINT("\n\rti_drv_txDeauthDisassocPacket: roleType:%d aReason:%d link id:%d SA:%s DA:%s",
        apDrv->roleType, aReason, pkt->link, macStrSA, macStrDA);
    GTRACE(GRP_DRIVER_CC33, "ti_drv_txDeauthDisassocPacket: roleType:%d aReason:%d link id:%d SA:%s DA:%s aType=%d",
        apDrv->roleType, aReason, pkt->link, macStrSA, macStrDA, aType);


    /* prepare WLAN header */
    pDot11Header = (dot11_mgmtHeader_t *) (pkt->header);

    fc = aType;

    if (SecureHdrLength)
    {
        fc |= DOT11_FC_WEP;
        pkt->flags |= PKTF_ENCRYPT;
    } 

    COPY_WLAN_WORD(&pDot11Header->fc, &fc);
    MAC_COPY (pDot11Header->DA, (uint8_t *)apBssid); 
    MAC_COPY (pDot11Header->SA, (uint8_t *)apDrv->macAddr);

    // WLAN_DISCONNECT_AP_REMOVE_PEER is only on unicast deauth    
    if(WLAN_DISCONNECT_AP_REMOVE_PEER == aReason)
    {
        aReason = WLAN_DISCONNECT_DEAUTH_SENDING_STA_LEAVING;
    }

    if(ROLE_IS_TYPE_AP_BASED(apDrv->roleType))
    {
        MAC_COPY (pDot11Header->BSSID, (uint8_t *)apDrv->macAddr);
    }
    else
    {
        MAC_COPY (pDot11Header->BSSID, (uint8_t *)apBssid);
    }

    pkt->flags |= PKTF_EXTERNAL_CONTEXT;

    /* copy payload */
    os_memcpy(&(((deAuth_t*)pkt->payload)->reason), &aReason, payloadSize);

    pkt->fTxCompleteCb = (TMgmtPacketCb)deauthDisassocTxResultCb;

    /* submit for tx */
    osiRetVal = udata_SendTxMgmtPacket(pkt);
   
    if (osiRetVal != OSI_OK)
    {
        MLME_REPORT_PRINT("\n\rti_drv_txDeauthDisassocPacket: udata_SendTxMgmtPacket was failed to send");
        GTRACE(GRP_DRIVER_CC33, "ERROR!: ti_drv_txDeauthDisassocPacket: udata_SendTxMgmtPacket ret %d ", osiRetVal);
        ret = NOK;
        goto fail;
    }

    //Wait for tx complete
    // Check for FW crash before waiting to avoid unnecessary timeout
    if (gFwCrashOccurred)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: FW crash detected before TX complete wait");
        MLME_REPORT_PRINT_ERROR("\n\rERROR: FW crash detected, skipping TX complete wait");
        if (pkt != NULL)
        {
            TTxCtrlBlk *pPktCtrlBlk = udataNet_ExtractTxCtrlBlkFromDesc(pkt);
            if (pPktCtrlBlk != NULL && pPktCtrlBlk->tTxPktParams.pInputPkt != NULL)
            {
                txCtrl_FreePacket(pPktCtrlBlk, STATUS_XMIT_ERROR);
            }
        }
        ret = NOK;
        goto fail;
    }

    osiRetVal = osi_SyncObjWait(&gtxCompleteSyncObj, TX_COMPLETE_TIMEOUT);
    if (OSI_OK != osiRetVal)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: osi_SyncObjectWait failed, rc = %d", osiRetVal);
        MLME_REPORT_PRINT_ERROR("\n\rERROR: osi_SyncObjectWait failed, rc = %d", osiRetVal);
        if (gFwCrashOccurred && pkt != NULL)
        {
            TTxCtrlBlk *pPktCtrlBlk = udataNet_ExtractTxCtrlBlkFromDesc(pkt);
            if (pPktCtrlBlk != NULL && pPktCtrlBlk->tTxPktParams.pInputPkt != NULL)
            {
                txCtrl_FreePacket(pPktCtrlBlk, STATUS_XMIT_ERROR);
            }
        }

        ret = NOK;
        goto fail;
    }

 fail:
    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_txDeauthDisassocPacket send done ret:%d ",ret);


    return ret;
}


/*!
    \brief      Callback for deauth / disassoc tx result

    \param      uint32_t aDescriptorId - packet descriptor id

    \return     none
*/
void deauthDisassocTxResultCb(void *apDesc)
{
    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:deauthDisassocTxResultCb");
    GTRACE(GRP_DRIVER_CC33, "drv_ti_mlme:deauthDisassocTxResultCb");

    /* Signal to the waiting thread */
    //GTRACE(GRP_DRIVER_CC33, "\n\rdeauthDisassocTxResultCb: Signal to the waiting thread");
    osi_SyncObjSignal(&gtxCompleteSyncObj);
}

static void wep_shared_auth_challenge(ti_driver_ifData_t  *apDrv,
                     struct ieee80211_mgmt *mgmt,
                     size_t len)
{

    u8 *pos;
    struct ieee802_11_elems elems;

    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:wep_shared_auth_challenge ");

    GTRACE(GRP_DRIVER_CC33, "MLME: replying to auth challenge");

    pos = mgmt->u.auth.variable;
    /* Parse the authentication response (packet 2 of 4). We already checked that the status is SUCCESS. */
    if (ieee802_11_parse_elems(pos, len - (pos - (u8 *) mgmt), &elems, 0) == ParseFailed)
    {
        GTRACE(GRP_DRIVER_CC33, "MLME: failed to parse Auth(challenge)");
        return;
    }
    if (elems.challenge == NULL)
    {
        GTRACE(GRP_DRIVER_CC33, "MLME: no challenge IE in shared key auth frame");
        return;
    }

    /* Update the expected transaction field */
    apDrv->pAuthInfo->expectedTransaction = 4;

    /* Send packet 3 of 4 with the encrypted challenge. */
    ti_drv_txAuthResPacket(apDrv, mgmt->sa,
                            AUTH_ALG_TYPE_SHARED_KEY,
                            (mgmt->u.auth.auth_transaction + 1),
                            WLAN_STATUS_SUCCESS,
                            elems.challenge - CC33_DRV_MNG_AUTH_CHALLENGE_HEADER_SIZE,
                            elems.challenge_len + CC33_DRV_MNG_AUTH_CHALLENGE_HEADER_SIZE,
                            1);

}


// ----------------------------------------------------------------------------
rxMngPackNextOperation_e ti_drv_rxAuthResponsePacket(
						   ti_driver_ifData_t  *apDrv,
						   struct ieee80211_mgmt *apMngPack,
						   uint32_t                aPackLen)
{
	char macSender[MAC_STR_LEN];
	uint32_t minLen = WLAN_HDR_LEN + sizeof(apMngPack->u.auth);

    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_rxAuthResponsePacket ");

	// Sanity check on packet parameters and authentication state
	if (aPackLen < minLen)
		return RX_MGMT_NONE;

	if ( (NULL == apDrv->pAuthInfo) || (TRUE == apDrv->pAuthInfo->done) )
		return RX_MGMT_NONE;

	GET_MAC_STR(apMngPack->sa, macSender);

	if (FALSE == IRQ_UtilCompareMacAddress(apMngPack->sa, apDrv->pAuthInfo->peerInfo.bssid))
	{
		char macExpected[MAC_STR_LEN];

		GET_MAC_STR(apMngPack->sa, macSender);
		GET_MAC_STR(apDrv->pAuthInfo->peerInfo.bssid, macExpected);
		GTRACE(GRP_DRIVER_CC33, "RX auth response, BSSID mismatch expected %s sender %s",
								 macExpected, macSender);
	    MLME_REPORT_PRINT("\n\rRX auth response, BSSID mismatch expected %s sender %s",
                                 macExpected, macSender);

		return RX_MGMT_NONE;
	}

	if (    (apMngPack->u.auth.auth_alg != apDrv->pAuthInfo->authType
			 && WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG == le_to_host16(apMngPack->u.auth.status_code))
		 || apMngPack->u.auth.auth_transaction != apDrv->pAuthInfo->expectedTransaction )
	{
		GTRACE(GRP_DRIVER_CC33, "Auth response mismatch from peer %s", macSender);
		GTRACE(GRP_DRIVER_CC33, "Auth response RX type %d expected %d", apMngPack->u.auth.auth_alg, apDrv->pAuthInfo->authType);
		GTRACE(GRP_DRIVER_CC33, "Auth response RX transaction %d expected %d", apMngPack->u.auth.auth_transaction, apDrv->pAuthInfo->expectedTransaction);
		return RX_MGMT_NONE;
	}

	// Handle optional error indication on peer side
	if (WLAN_STATUS_SUCCESS != apMngPack->u.auth.status_code)
	{
		GTRACE(GRP_DRIVER_CC33, "Auth response from peer %s status code %d",
								macSender,
								apMngPack->u.auth.status_code);
        MLME_REPORT_PRINT("\n\rAuth response from peer %s status code %d",
                                macSender,
                                apMngPack->u.auth.status_code);

        wlanDispatcherSendEvent(WLAN_EVENT_AUTHENTICATION_REJECTED, (void *)&apMngPack->u.auth.status_code, sizeof(uint16_t));

		if (WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA == apMngPack->u.auth.status_code ||
            WLAN_STATUS_ASSOC_REJECTED_TEMPORARILY == apMngPack->u.auth.status_code ||
            WLAN_STATUS_DENIED_INSUFFICIENT_BANDWIDTH == apMngPack->u.auth.status_code ||
            WLAN_STATUS_REQUEST_DECLINED == apMngPack->u.auth.status_code)
		{
			if (DENY_LIST_EN) 
            {
                GTRACE(GRP_DRIVER_CC33, "Authentication rejected, adding this MAC to Deny List");
                DenyList_addElement(&(apDrv->denyList), apMngPack->sa, DENY_LIST_DEFAULT_EXPIRY_TIME + osi_GetTimeMS());
                
                MLME_REPORT_PRINT("\n\rti_drv_rxAuthResponsePacket:destroyAuthData");
                destroyAuthData(apDrv, TRUE);
                return RX_MGMT_NONE;
            }
		}

		// For any other failure indication, let supplicant decide how to continue.
		// (For WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG supplicant starts again.)
        MLME_REPORT_PRINT("\n\rti_drv_rxAuthResponsePacket:destroyAuthData");
		destroyAuthData(apDrv, TRUE);
		return RX_MGMT_AUTH;
	}

	// Handle shared key
	switch (apDrv->pAuthInfo->authType)
	{
		case AUTH_ALG_TYPE_OPEN_SYSTEM:
		case AUTH_ALG_TYPE_LEAP:
		case AUTH_ALG_TYPE_FT:
			break;
		case AUTH_ALG_TYPE_SHARED_KEY:
			if (4 != apDrv->pAuthInfo->expectedTransaction)
			{
			    wep_shared_auth_challenge(apDrv, apMngPack, aPackLen);
				return RX_MGMT_NONE;
			}
			break;
		case AUTH_ALG_TYPE_SAE:
		    break;
		default:
		    GTRACE(GRP_DRIVER_CC33, "WARNING: Auth response from peer %s invalid type %d",
		                            macSender, apDrv->pAuthInfo->authType);
			return RX_MGMT_NONE;
	}

	apDrv->pAuthInfo->done = TRUE;

	// pAuthInfo is released when it is understood we don't have to resend an
	// authentication request:
	//	- error indication in status of auth response
	//  - authentication timeout callback in case
	//		o done=TRUE
	//		o failure in sending another auth request
	//	- when a new auth request is started and auth_data is valid
	//	- send assoc request
	//	- RX deauth
	//	- interface stop request


	return RX_MGMT_AUTH;
}



// ----------------------------------------------------------------------------
rxMngPackNextOperation_e ti_drv_rxAssocResponsePacket(
									ti_driver_ifData_t  *apDrv,
                           	   	    struct ieee80211_mgmt *apMngPack,
                           	   	    uint32_t 				  aPackLen,
                           	   	    Bool32                aIsReassoc,
                           	   	    void *                desc)
{
    char macSender[MAC_STR_LEN];
    uint8_t   *pIes;
#if 0
    uint8_t   secType = 0;
#endif
    uint16_t  status_code;
    uint32_t  minLen = WLAN_HDR_LEN + sizeof(apMngPack->u.assoc_resp);
    struct ieee802_11_elems parsedElems;

    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_rxAssocResponsePacket ");

    // Sanity check on packet parameters and authentication state
    if (aPackLen < minLen)
        return RX_MGMT_NONE;

    if (NULL == apDrv->pAssocInfo)
    {
        GTRACE(GRP_DRIVER_CC33, "RX an unexpected asssoc response, dropping the packet");
        MLME_REPORT_PRINT("\r\nRX an unexpected asssoc response, dropping the packet");
        return RX_MGMT_NONE;
    }

    GET_MAC_STR(apMngPack->sa, macSender);

    if (!IRQ_UtilCompareMacAddress(apDrv->pAssocInfo->peerInfo.bssid, apMngPack->sa))
    {
        GTRACE(GRP_DRIVER_CC33, "RX %sssoc response from wrong peer %s",
                                 (aIsReassoc ? "Rea" :"A"), macSender);
        return RX_MGMT_NONE;
    }

    status_code = le_to_host16(apMngPack->u.assoc_resp.status_code);

    GTRACE(GRP_DRIVER_CC33, "RX %ssoc response for %s status %d ", (aIsReassoc ? "Rea" :"A" ), macSender, status_code);
    MLME_REPORT_PRINT("\r\nRX %ssoc response for %s status %d ", (aIsReassoc ? "Rea" :"A" ), macSender, status_code);

    if (WLAN_STATUS_SUCCESS != status_code)
    {
        wlanDispatcherSendEvent(WLAN_EVENT_ASSOCIATION_REJECTED, (void *)&status_code, sizeof(uint16_t));
    }

    pIes = apMngPack->u.assoc_resp.variable;
    ieee802_11_parse_elems(pIes, aPackLen - minLen, &parsedElems, 1 /* show errors in log */);

    if (   WLAN_STATUS_ASSOC_REJECTED_TEMPORARILY == status_code
        && parsedElems.timeout_int
        && WLAN_TIMEOUT_ASSOC_COMEBACK == parsedElems.timeout_int[0])
    {
        uint32_t tu, msecs;

//TODO according to the SPEC STA is not allowed to try to associate again before end
//            of timeout interval !!! if profile is added and interval is long we will try to
//            associate before. we might decide to move to next profile instead of setting
//            timer


        COPY_WLAN_32BIT(&tu,parsedElems.timeout_int + 1);
        msecs = tu * 1024 / 1000;
        GTRACE(GRP_DRIVER_CC33,
               "%s rejected association temporarily; comeback duration %d TU (%d ms). Adding this MAC to Deny List ",
               macSender, tu, msecs);
        CME_PRINT_REPORT("\n\r%s rejected association temporarily; comeback duration %d TU (%d ms). Adding this MAC to Deny List",
                macSender, tu, msecs);

        if (DENY_LIST_EN) 
        {
            DenyList_addElement(&(apDrv->denyList), apMngPack->sa, msecs + osi_GetTimeMS());
        }
        eloop_cancel_timeout(ti_drv_AssocTimeout, apDrv, NULL);

        eloop_register_timeout(0,                       // seconds
                               msecs*1000,              // useconds
                               ti_drv_AssocTimeout,    // Timeout callback
                               apDrv,                   // eloop data
                               NULL);                   // user data

        // TODO - cancel the remain on channel
        return RX_MGMT_NONE;
    }

    if (WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA == status_code)
    {
        /* can't assoc us right now, try again in 200 ms */
        uint32_t msecs = 200;

        GTRACE(GRP_DRIVER_CC33,
                    "%s rejected association; try again in %d ms",
                    macSender, msecs);
        eloop_cancel_timeout(ti_drv_AssocTimeout, apDrv, NULL);

        if (ASSOC_TIMEOUT_MSECS < msecs)
        {
            eloop_register_timeout(0,                       // seconds
                                   msecs*1000,              // useconds
                                   ti_drv_AssocTimeout,    // Timeout callback
                                   apDrv,                   // eloop data
                                   NULL);                   // user data
        }
        // TODO - cancel the remain on channel

        return RX_MGMT_NONE;
    }
    // If descriptor was handed back to SW, mark that assoc request packet can be released
    if (ASSOC_REQ_DESC_PENDING_ASSOC_RESP == apDrv->pAssocInfo->descriptorState)
    {
        GTRACE(GRP_DRIVER_CC33, "Association request can be released (got assoc response after TX exchange)");
        MLME_REPORT_PRINT("\n\rAssociation request can be released (got assoc response after TX exchange)");
        apDrv->pAssocInfo->descriptorState = ASSOC_REQ_DESC_OK2RELEASE;
    }
    // Otherwise mark packet can be released once PMAC hands it back
    else
    {
        MLME_REPORT_PRINT("\n\rAssociation request waits for TX exchange (got assoc response before TX exchange)");
        GTRACE(GRP_DRIVER_CC33, "Association request waits for TX exchange (got assoc response before TX exchange)");
        apDrv->pAssocInfo->descriptorState = ASSOC_REQ_DESC_PENDING_TX;
    }

    if (WLAN_STATUS_SUCCESS != status_code)
    {
        GTRACE(GRP_DRIVER_CC33, "%s denied association, status = %d",
                    macSender, status_code);
        MLME_REPORT_PRINT("\n\rti_drv_rxAssocResponsePacket destroyAssocData, status = %d",
                            status_code);
        destroyAssocData(apDrv, TRUE);
    }
    else
    {
        // Set AP parameters in L2 data bases
        ti_drv_setApInfo(apDrv, &parsedElems, apMngPack, aPackLen);

        GTRACE(GRP_DRIVER_CC33, "associated with %s", macSender);

        //if privacy is enabled (but cipher is not WEP), request to be in active mode shorten the RX time
        //of the expected EAPOL
        if (apMngPack->u.assoc_resp.capab_info & BIT_x(CAP_PRIVACY_SHIFT))
        {
#if 0 // TODO: need to implement
            pDesc = (struct CC33_FrameRxDesc_s *)MMU_GET_VIRTUAL_ADDR_FROM_DESC(frameId);

            // This is an association response so adjust the address to be at the beginning of the IE.

            if((rsn_getSecurityType(apMngPack->u.assoc_resp.capab_info,
                                (uint8_t*)(pDesc->address + ASSOC_RESP_FIXED_DATA_LEN),     /* payload start */
                                pDesc->length_type.length - ASSOC_RESP_FIXED_DATA_LEN , /* payload length */
                                &secType) == 0) &&
                    (SL_SEC_TYPE_WEP != secType))
            {
                //cc33_driver_start_security_mgmt_seq(apDrv->roleId);
            }
#endif
        }

        /* Copy association info before destroy */
        apDrv->ssid_len = apDrv->pAssocInfo->ssid_len;
        os_memcpy(apDrv->ssid, apDrv->pAssocInfo->ssid, apDrv->pAssocInfo->ssid_len);
        apDrv->freq = apDrv->assocFreq;

        /*
         * destroy assoc_data afterwards, as otherwise an idle
         * recalc after assoc_data is NULL but before associated
         * is set can cause the interface to go idle
         */
        MLME_REPORT_PRINT("\n\rti_drv_rxAssocResponsePacket destroyAssocData, status_code OK,descriptorState:%d",apDrv->pAssocInfo->descriptorState);
        destroyAssocData(apDrv, FALSE);
    }

    HOOK(HOOK_DRV_TI_MLME);

    return RX_MGMT_RX_ASSOC;

}

// ----------------------------------------------------------------------------
Bool_e ti_drv_checkUnprotectedDeauthDisassocEventCriteria(
                                        ti_driver_ifData_t  *apDrv,
						                struct ieee80211_mgmt *apMngPack)
{
    TWlanLinkInfo pLinkInfo;
    wlanLinks_ReadLinkInfo(&pLinkInfo, apDrv->link);
    if (IRQ_UtilCompareMacAddress(apDrv->macAddr, apMngPack->da) &&
        pLinkInfo.bPMFEncription && 
        (IS_PROTECTED_FRAME(le_to_host16(apMngPack->frame_control)) == FALSE) &&
        ((apMngPack->u.deauth.reason_code == WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA) || 
         (apMngPack->u.deauth.reason_code == WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA)))
    {
        return TRUE;
    }

    return FALSE;
}

// ----------------------------------------------------------------------------
rxMngPackNextOperation_e ti_drv_rxDeauthPacket(
						   ti_driver_ifData_t  *apDrv,
						   struct ieee80211_mgmt *apMngPack,
						   uint32_t                aPackLen)
{

    char macSender[MAC_STR_LEN];
    char macBssid[MAC_STR_LEN];
    char macDest[MAC_STR_LEN];
	uint32_t  minLen = WLAN_HDR_LEN + sizeof(apMngPack->u.deauth);
	uint16_t  reasonCode;

    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_rxDeauthPacket ");

	// Sanity check on packet parameters and authentication state
	if (aPackLen < minLen)
		return RX_MGMT_NONE;

    GET_MAC_STR(apMngPack->da,    macDest);
    GET_MAC_STR(apMngPack->sa,    macSender);
    GET_MAC_STR(apDrv->currBssid, macBssid);
    reasonCode = le_to_host16(apMngPack->u.deauth.reason_code);

    GTRACE(GRP_DRIVER_CC33, "RX deauth packet, associated %d, from %s, bssid %s, reason %d",
           apDrv->associated,
           macSender,
           macBssid,
           reasonCode);
    MLME_REPORT_PRINT("\n\rdrv_ti_mlme: deauth packet, associated %d, from %s, bssid %s, macDest:%s, reason %d",
           apDrv->associated,
           macSender,
           macBssid,
           macDest,
           reasonCode);

    apDrv->deauthReason = reasonCode;

	if ( FALSE == apDrv->associated ||
	     !IRQ_UtilCompareMacAddress(apDrv->currBssid, apMngPack->sa))
	{
		return RX_MGMT_NONE;
	}

    if (ti_drv_checkUnprotectedDeauthDisassocEventCriteria(apDrv, apMngPack))
    {
        return RX_MGMT_UNPROT_DEAUTH;
    }

	finalizeStaDisconnect(apDrv, 1097);

	// at this point the mac80211, mlme.c marks interface is idle,
	// in cc33xx idle state should be notified by roles management.

    HOOK(HOOK_DRV_TI_MLME);

	return RX_MGMT_DEAUTH;

}

// ----------------------------------------------------------------------------
rxMngPackNextOperation_e ti_drv_rxDisassocPacket(
						   ti_driver_ifData_t  *apDrv,
						   struct ieee80211_mgmt *apMngPack,
						   uint32_t                aPackLen)
{
	char macSender[MAC_STR_LEN];
	uint32_t  minLen = WLAN_HDR_LEN + sizeof(apMngPack->u.disassoc);
	uint16_t  reasonCode;

    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_rxDisassocPacket ");

	// Sanity check on packet parameters and authentication state
	if (aPackLen < minLen)
		return RX_MGMT_NONE;

	reasonCode = le_to_host16(apMngPack->u.deauth.reason_code);

	GET_MAC_STR(apMngPack->sa, macSender);
	GTRACE(GRP_DRIVER_CC33, "RX disassoc packet from %s reason %d",macSender, reasonCode);

    apDrv->deauthReason = reasonCode;

    if (FALSE == apDrv->associated ||
	    !IRQ_UtilCompareMacAddress(apDrv->currBssid, apMngPack->sa))
		return RX_MGMT_NONE;

    if (ti_drv_checkUnprotectedDeauthDisassocEventCriteria(apDrv, apMngPack))
    {
        return RX_MGMT_UNPROT_DISASSOC;
    }

	finalizeStaDisconnect(apDrv, 1135);

	// TODO
	// At this point the mac80211, mlme.c marks interface is idle,
	// in cc33xx idle state should be notified by roles management.

    HOOK(HOOK_DRV_TI_MLME);

	return RX_MGMT_DISASSOC;
}

// ----------------------------------------------------------------------------
/*static*/ rxMngPackNextOperation_e ti_drv_rxSaQueryPacket(
                                        ti_driver_ifData_t  *apDrv,
                                        struct ieee80211_mgmt *apMngPack,
                                        uint32_t                aPackLen)
{
//
//    GTRACE(GRP_MGMT_PROTECTION_IMP, "receive sa query %d, trans_id 0x%X, associated %d",
//           apMngPack->u.action.u.sa_query_req.action,
//           *(uint16_t*)apMngPack->u.action.u.sa_query_req.trans_id,
//           apDrv->associated);
    MLME_REPORT_PRINT("\n\rdrv_ti_mlme:ti_drv_rxSaQueryPacket ");

    if (apMngPack->u.action.u.sa_query_req.action == WLAN_SA_QUERY_REQUEST)
    {
        struct ieee80211_mgmt  mgmt;

        //answer this frame only if the source of this query is assiciated with us
        if ( FALSE == apDrv->associated ||
             !IRQ_UtilCompareMacAddress(apDrv->currBssid, apMngPack->sa))
        {
            return RX_MGMT_NONE;
        }

        mgmt.u.action.category               = WLAN_ACTION_SA_QUERY;
        mgmt.u.action.u.sa_query_resp.action = WLAN_SA_QUERY_RESPONSE;
        mgmt.u.action.u.sa_query_resp.trans_id[0] = apMngPack->u.action.u.sa_query_req.trans_id[0];
        mgmt.u.action.u.sa_query_resp.trans_id[1] = apMngPack->u.action.u.sa_query_req.trans_id[1];

        //send sa query response
        ti_driver_send_action(apDrv,
                              apDrv->freq,              //aFreq,                        // ignored
                              0,              //aWaitTime,                    // ignored
                              apMngPack->sa,  // Destination address (which is the source of this frame)
                              apDrv->macAddr,           //Source address:               // ignored - deduced from role id
                              apMngPack->bssid,           // BSSID:                       // ignored - deduced from role id
                              (u8*)&(mgmt.u.action),//const u8 *apData,
                              4,              //size_t aDataLen,
                              0               /*int    aNoCck*/);            // ignored

        return RX_MGMT_NONE;
    }
    else if (apMngPack->u.action.u.sa_query_req.action == WLAN_SA_QUERY_RESPONSE)
    {
        //sa query response is delivered to the supplicant
        return RX_MGMT_SEND_RX_MGMT_EVENT;
    }
    else
    {
        return RX_MGMT_NONE;
    }
}



/* ----------------------------------------------------------------------------
 assocCapBuild
      This function builds capabilities field for association request.
      Beahvior is based on WL8 MCP; bits that were not set in MCP are not set
      in cc33xx as well.

 Parameters:    aRoleId
                aRoleType
                apParams - pointer to association parameters
                apCandidateScanRes - pointer to candidate scan result
 Return code:   constructed capabilities field
---------------------------------------------------------------------------- */
static uint16_t assocCapBuild(uint32_t      aRoleId,
                              RoleType_e    aRoleType,
                              struct wpa_driver_associate_params *apParams,
                              cmeScanCandidateDesc_t *apCandidateScanRes)
{
	uint16_t           cap = DOT11_CAPS_ESS;

	Bool32           shortSlotSupported = cfgIsStaShortSlotEnabled();
	Bool32           shortSlotPreambleSupported = cfgIsStaShortPreambleEnabled();

	CipherSuite_e    cipherSuite = rsn_getPairwiseSuite();

    //MLME_REPORT_PRINT("\n\rdrv_ti_mlme:drv_ti_mlme:assocCapBuild ");

    /* Privacy */
    if (CIPHER_SUITE_NONE != cipherSuite)
    {
        cap |= DOT11_CAPS_PRIVACY;
    }

    /* Preamble */
    // In MCP preamble type is set once, at init time to a hard coded value.
    if (FALSE != shortSlotPreambleSupported)
    {
        cap |= DOT11_CAPS_SHORT_PREAMBLE;
    }

    /* Pbcc */
    // Packet Binary Convolutional Code is not supported in WL8 and won't
    // be aslo in CC33xx, no need to check capabilities for this one
#ifdef CC33_SUPPORT_PBCC
    cap |= DOT11_CAPS_PBCC;
#endif

    /* Checking if peer AP supports Spectrum Management (802.11h)*/
    if (apCandidateScanRes->mScanResult.caps & DOT11_SPECTRUM_MANAGEMENT)
	{
        cap |= DOT11_SPECTRUM_MANAGEMENT;
    }

    /* slot time */
    // For BG band, have to verify the peer supports OFDM
    // TODO: is this check sufficient?
	if ( (apParams->freq.freq <= FREQ_CH_14) && (TRUE == shortSlotSupported) )
    {
	    uint32_t supportedRates;
	    uint32_t apBasicRatesBM;

	    cfgGetRates(aRoleType, &apBasicRatesBM, &supportedRates);// TODO: need to implemnt roles_StaBasedGetPeerSupportedRates(aRoleId);


	    // If peer doesn't support PFDM, force long slot time
	    if (0 == (supportedRates & ANY_AG_OFDM_RATE))
	    {
	        shortSlotSupported = FALSE;
	    }

    }
	if (TRUE == shortSlotSupported)
	{
        cap |= DOT11_CAPS_SHORT_SLOT_TIME;
    }

    /* if chiper = TKIP/WEP then 11n is not used */
	// TODO - do we want to configure one of the below:
	//  CC33_SUPPORT_IMMEDIATE_BA, CC33_SUPPORT_SUPPORT_HT, CC33_SUPPORT_SUPPORT_WME
    if ( (CIPHER_SUITE_TKIP != cipherSuite) && (CIPHER_SUITE_WEP != cipherSuite) )
    {
        // TODO MCP publishes BA support only if peer supports HT.
        // In 802.11 spec (8.4.1.4 Capability Information field) BA bits depend on dot11DelayedBlockAckOptionImplemented
        // Follow MCP behavior, which may be caused by interop issues.

        if ( (TRUE == apCandidateScanRes->mHtCapabilitiesPresent) && (TRUE == apCandidateScanRes->mHtInformationPresent) )
        {
#ifdef AX_DEBUG_FIXES
      // remove this line to disabe support in immediate BA
	        cap |= DOT11_CAPS_IMMEDIATE_BA;
#endif
        }
	}

    // part of MBO inplementation.
    // check whether this association should include support for RRM (Radio Resource Measurements),
    // and if so set the rrm enabled capability.
    if (apParams->rrm_used)
    {
        cap |= DOT11_CAPS_RRM_ENABLED;
    }

    HOOK(HOOK_DRV_TI_MLME);

    return cap;
}

/* ----------------------------------------------------------------------------
 assocQosBuild
      This function builds
      Beahvior is based on WL8 MCP

 Parameters:    aRoleId - STA role ID
                apPack - pointer to association request packet to be updated
 Return code:   number of added bytes
---------------------------------------------------------------------------- */
static uint32_t assocQosBuild(uint32_t aRoleId, uint8_t *apWmeIeDest,uint8_t isHeConnection )
{

    dot11_WME_IE_t *pDot11_WME_IE = (dot11_WME_IE_t *)apWmeIeDest;

    //MLME_REPORT_PRINT("\n\rdrv_ti_mlme:assocQosBuild ");

    pDot11_WME_IE->hdr.eleId = DOT11_WME_ELE_ID;
    pDot11_WME_IE->hdr.eleLen = DOT11_WME_ELE_LEN;
    pDot11_WME_IE->OUI[0] = 0x0;
    pDot11_WME_IE->OUI[1] = 0x50;
    pDot11_WME_IE->OUI[2] = 0xf2;
    pDot11_WME_IE->OUIType = dot11_WME_OUI_TYPE;
    pDot11_WME_IE->OUISubType = dot11_WME_OUI_SUB_TYPE_IE;
    pDot11_WME_IE->version = dot11_WME_VERSION;
    pDot11_WME_IE->ACInfoField = 0;
   

    if(gL2DynamicCfg.acPsMode.wmeAcPsMode[AC_VO] == PS_SCHEME_UPSD_TRIGGER)
    {
        pDot11_WME_IE->ACInfoField |= (1 << AC_VO_APSD_FLAGS_SHIFT);
    }
    if(gL2DynamicCfg.acPsMode.wmeAcPsMode[AC_VI] == PS_SCHEME_UPSD_TRIGGER)
    {
        pDot11_WME_IE->ACInfoField |= (1 << AC_VI_APSD_FLAGS_SHIFT);
    }

    if(gL2DynamicCfg.acPsMode.wmeAcPsMode[AC_BK] == PS_SCHEME_UPSD_TRIGGER)
    {
        pDot11_WME_IE->ACInfoField |= (1 << AC_BK_APSD_FLAGS_SHIFT);
    }

    if(gL2DynamicCfg.acPsMode.wmeAcPsMode[AC_BE] == PS_SCHEME_UPSD_TRIGGER)
    {
        pDot11_WME_IE->ACInfoField |= (1 << AC_BE_APSD_FLAGS_SHIFT);
    }

    if (pDot11_WME_IE->ACInfoField)  //if at least 1 AC is in trigger mode, set the max SP len
    {
        pDot11_WME_IE->ACInfoField |= (((gL2DynamicCfg.maxSpLen) & MAX_SP_LENGTH_MASK) << MAX_SP_LENGTH_SHIFT);
    }

#ifndef DISABLE_WIFI6
    if(gpL2CommonCfg->heParams.moreDataBit && isHeConnection)
    {
        pDot11_WME_IE->ACInfoField |= (1 << MORE_DATA_ACK_SHIFT);
    }
#endif


    return (pDot11_WME_IE->hdr.eleLen + sizeof(dot11_eleHdr_t));

}

/*
   Association response received, update FW in MCP & NLCP

NLCP - mac80211
=============
aid
capabilities
HT capabilities (if we have 11n and AP doesn't disable 11n)
40MHz support
rate control init ?
MFP
WMM

call ieee80211_set_associated:
keep peer info in mgd.associated
keep dtim
keep peer BSSID on peer info

enable ARP filtering

notify driver in case parameters were changed (ieee80211_bss_info_change_notify):
wl1271_bss_info_changed_sta - checks type of change
for every changed parameter - set new value using info elements mechanism


start AP connection monitor timer
start beacon loss timer

enabled TX queues


MCP - configureApBeforeRoc
=============
build ARP template
aid - ACX_AID
burst mode enabled - ACX_BURST_MODE
set RSN keys
HT capabilities - ACX_PEER_CAP, ACX_HT_BSS_OPERATION
supported rates


From NLCP FW log:

ACX_AC_CFG  v
ACX_TID_CFG redundant for legacy PS delivery
ACX_SLOT    v
ACX_PREAMBLE_TYPE   v
ACX_CONN_MONIT_PARAMS
ACX_KEEP_ALIVE_MODE
ACX_AID     v
ACX_BET_ENABLE
CMD_SET_PS_MODE
ACX_RATE_POLICY
ACX_PEER_CAP
ACX_HT_BSS_OPERATION
ACX_ARP_IP_FILTER
CMD_SET_PEER_STATE
ACX_BA_SESSION_RX_SETUP
ACX_BET_ENABLE
ACX_BEACON_FILTER_OPT
ACX_PEER_CAP
ACX_HT_BSS_OPERATION

*/


// ------------------------------------------------------------------------
void readErpFlag(struct ieee802_11_elems *apParsedElems,    // IN  - points to parsed received packet
                 Bool32 *apUseProtection,                   // OUT - whether protection is required
                 Bool32 *apShortBarkerPreamble)             // OUT - whether short barker is required
{
    *apShortBarkerPreamble = TRUE;
    *apUseProtection = FALSE;

    HOOK(HOOK_DRV_TI_MLME);

    if (NULL != apParsedElems->erp_info)
    {
        uint8_t erpFlags = *apParsedElems->erp_info;

        *apUseProtection = (erpFlags & 0x2) >> 1;
        *apShortBarkerPreamble = ((erpFlags & 0x4) >> 2) ? FALSE : TRUE;
    }
}

// ------------------------------------------------------------------------
int32_t getWmmConfig(struct ieee802_11_elems *apParsedElems,    // IN  - points to parsed received packet
                  dot11_WME_PARAM_t *apWMEParamIE,            // OUT - QOS parsed params
                  dot11_WSC_t       *apWSCIE)                 // OUT - QOS parsed params
{
    uint8_t wpaIeOuiIe[4] = {0x00, 0x50, 0xf2, 0x01};
    int32_t rc = -1;
    const uint8_t *pWmmData = apParsedElems->wmm;
    // Only one of the QOS IEs is present, so start by setting length to 0.
    // The length of the existing one shall be updated below
    apWMEParamIE->hdr.eleLen = 0;
    apWSCIE->hdr.eleLen = 0;

    HOOK(HOOK_DRV_TI_MLME);

    if (0 == memcmp(pWmmData, wpaIeOuiIe, 3))
    {
        /* Note : WSC, WPA and WME use the same OUI */
        /*  Its assumes that:
                            WPA uses OUI Type with value  - 1
                            WME uses OUI Type with value  - 2
                            WSC uses OUI Type with value  - 4
         */

        GTRACE(GRP_DRIVER_CC33, "WMM IE OUI is OK, checking WME params");

        if( ( (*(uint8_t *)(pWmmData+3)) == dot11_WME_OUI_TYPE ) &&
            ( ( (*(uint8_t *)(pWmmData+4)) == dot11_WME_OUI_SUB_TYPE_PARAMS_IE ) ||
              ( (*(uint8_t *)(pWmmData+4)) == dot11_WME_OUI_SUB_TYPE_IE  ) ) )
        {

            GTRACE(GRP_DRIVER_CC33, "WME OUI type & sub type are OK, checking WME params");

            /* If we are here - the following is WME-Params IE, WME-Info IE or TSPEC IE. */
            /* Note that we are using the WMEParams struct also to hold the WME-Info IE
               which is a subset of WMEParams, and only one of them is sent in a frame. */
            rc = mlmeParser_readWMEParams(pWmmData-2, apWMEParamIE);
        }
        if((*(pWmmData+3)) == dot11_WSC_OUI_TYPE )
        {
            /* If we are here - the following is WSC IE */
            /*
             * This IE is not supposed to be found in beacons accroding to the standard
             * definition. However, some APs do add it to beacons. It is read from beacons
             * accroding to a registry key (which is false by default). Even if it is not
             * read, the readLen must be set for the pointer to advance, which is done
             * above.
             */
//            if ((BEACON != params->frame.subType) || (TI_TRUE == pHandle->bParseBeaconWSC))
            {
                GTRACE(GRP_DRIVER_CC33, "WSC IE OUI is OK, checking WME params");

                rc = mlmeParser_readWSCParams(pWmmData-2, apWSCIE);
            }
        }
    }

    return rc;
}


// ----------------------------------------------------------------------------
void finalizeStaDisconnect(ti_driver_ifData_t *apDrv, uint32_t aCaller)
{
//    - stopping TX queues
//   - resetting HT capabilities
//   - stopping ARP filtering
//   - deleting related timers
	// TODO - notify FW it should clear peer info and reset 802.11 to our own defaults
	// update power state

    GTRACE(GRP_DRIVER_CC33, "finalizeStaDisconnect activated from %d", aCaller);
    MLME_REPORT_PRINT("\n\rfinalize StaDisconnect ");


    if(FALSE == apDrv->roleStarted)
    {
        GTRACE(GRP_DRIVER_CC33, "WARNING: Role %d wasn't started yet or already stopped, can't stop it", apDrv->roleId);
        MLME_ERROR_PRINT("\n\rWARNING: Role %d wasn't started yet or already stopped, can't stop it", apDrv->roleId);
        return;
    }
    // If role is stopped before association was completed ROC is still on.
    // In this case we should ask for CROC before we can stop the role.
    if (TRUE == apDrv->rocActive)
    {
        // This call is blocking; when it returns CROC handling is completed

        apDrv->ops->cancel_remain_on_channel(apDrv);
    }
    apDrv->ops->stop_role(apDrv);
    markDisconnected(apDrv, 1528);
}

// ----------------------------------------------------------------------------
void markDisconnected(ti_driver_ifData_t *apDrv, uint32_t aCaller)
{
    GTRACE(GRP_DRIVER_CC33, "markDisconnected: apDrv->associated %d caller %d", apDrv->associated, aCaller);

	apDrv->associated = FALSE;
	IRQ_UtilZeroMacAddress(apDrv->currBssid);
}
