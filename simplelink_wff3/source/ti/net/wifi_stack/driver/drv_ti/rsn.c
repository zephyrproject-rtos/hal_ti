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
  FILENAME:       rsn.c

  DESCRIPTION:    This file handles STA RSN (Robust Security Network) keys.
                  It is based on WL8 MCP rsn.c code.

  HISTORY:
                  07/15 Creation
  ----------------------------------------------------------------------------- */

#include <data_path/udata/udata.h>
#include <inc_common/wlan_links.h>
#include "rsn.h"
#include <string.h>
#include "macro_utils.h"
#include "mpdu.h"                   // for TEST_BROADCAST_ADDRESS
#include "gtrace.h"
#include "cme_supplicant_api.h"     // for sending CROC
#include "ieee802_11_defs.h"        // for security definitions
#include "drivers/driver.h"                 // for security definitions
#include "wpa_common.h"        // for security definitions
#include "wpa.h"
#include "cme_common.h"
#include "drv_ti_internal.h"
#include "ie_parser_util.h"



// ============================================================================
//  Type definitions
// ============================================================================

typedef enum
{
   RSN_PRE_AUTH_START,
   RSN_PRE_AUTH_END
} preAuthStatusEvent_e;

// ============================================================================
//  Module's globals
// ============================================================================

// RSN data base
rsnCB_t gRsnDB ;

// ============================================================================
//  Local functions declarations
// ============================================================================

// Timeout events handlers
#if 0
static void pairwiseReKeyTimeout();
static void groupReKeyTimeout();
static void micFailureReportTimeout();
#endif
//static void preAuthTimeout();

static void setKey(KeyAction_e aAction, securityKeys_t *apSecurityKey, const char *ifname);
static void setDefaultKeyId(uint8_t aKeyId, uint32_t aBrcstLid, const char *ifname);
//static void notifyPreAuthStatus (preAuthStatusEvent_e aNewStatus);
void rsn_getSecurityTypeFrom_IE(dot11_RSN_t *pDotRsn, uint8_t *secType);


// The below is imported from MCP as reference
#if 0

/* Constants */
#define PREAUTH_CAND_LIST_MEMBUFF_SIZE  (2*sizeof(uint32_t) + (sizeof(OS_802_11_PMKID_CANDIDATE) * PREAUTH_CAND_LIST_MAX_SIZE))
#define MAX_WPA2_UNICAST_SUITES     (TWD_CIPHER_WEP104+1)
#define MAX_WPA2_KEY_MNG_SUITES     (RSN_KEY_MNG_CCX+1)


/* Cipher suites for group key sent in RSN IE are: WEP40, WEP104, TKIP, CCCMP */
#define GRP_CIPHER_MAXNO_IN_RSNIE         4

/* Cipher suites for unicast key sent in RSN IE are TKIP, CCMP, "use Group key"*/
#define UNICAST_CIPHER_MAXNO_IN_RSNIE     3


/* WPA2 key management suites */
#define WPA2_IE_KEY_MNG_NONE             0
#define WPA2_IE_KEY_MNG_801_1X           1
#define WPA2_IE_KEY_MNG_PSK_801_1X       2
#define WPA2_IE_KEY_MNG_CCKM             3
#define WPA2_IE_KEY_MNG_NA               4


#define WPA2_OUI_MAX_VERSION           0x1
#define WPA2_OUI_DEF_TYPE              0x1
#define WPA2_OUI_MAX_TYPE              0x2

#define WPA2_PREAUTH_CAPABILITY_MASK               0x0001   /* bit 0 */
#define WPA2_PREAUTH_CAPABILITY_SHIFT              0
#define WPA2_GROUP_4_UNICAST_CAPABILITY_MASK        0x0002   /* bit 1 No Pairwise */
#define WPA2_GROUP_4_UNICAST_CAPABILITY_SHIFT        1
#define WPA2_PTK_REPLAY_COUNTERS_CAPABILITY_MASK    0x000c   /* bit 2 and 3 */
#define WPA2_PTK_REPLAY_COUNTERS_CAPABILITY_SHIFT   2
#define WPA2_GTK_REPLAY_COUNTERS_CAPABILITY_MASK    0x0030   /* bit 4 and 5 */
#define WPA2_GTK_REPLAY_COUNTERS_CAPABILITY_SHIFT   4
                                                             /* bit 6 - 15 - reserved */
#define WPA2_IE_MIN_LENGTH                  4
#define WPA2_IE_GROUP_SUITE_LENGTH          8
#define WPA2_IE_MIN_PAIRWISE_SUITE_LENGTH   14
#define WPA2_IE_MIN_DEFAULT_LENGTH          24
#define WPA2_IE_MIN_KEY_MNG_SUITE_LENGTH(pairwiseCnt) (10+4*pairwiseCnt)


#define MAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"

static uint8_t wpa2IeOuiIe[3] = { 0x00, 0x0f, 0xac};

/* Enumerations */

/* Typedefs */

/* WPA2 data parsed from RSN info element */
typedef struct
{

    ECipherSuite        broadcastSuite;
    uint16_t           unicastSuiteCnt;
    ECipherSuite        unicastSuite[MAX_WPA2_UNICAST_SUITES];
    uint16_t           KeyMngSuiteCnt;
    uint8_t            KeyMngSuite[MAX_WPA2_KEY_MNG_SUITES];
    uint8_t            preAuthentication;
    uint8_t            bcastForUnicatst;
    uint8_t            ptkReplayCounters;
    uint8_t            gtkReplayCounters;
    uint16_t           pmkIdCnt;
    uint8_t            pmkId[PMKID_VALUE_SIZE];
    uint8_t            lengthWithoutPmkid;
} wpa2IeData_t;




/* Local function prototypes */
TI_STATUS rsn_sendKeysNotSet(rsn_t *pRsn);
void pairwiseReKeyTimeout(void * hRsn, TI_BOOL bTwdInitOccured);
void groupReKeyTimeout(void * hRsn, TI_BOOL bTwdInitOccured);
void micFailureReportTimeout (void * hRsn, TI_BOOL bTwdInitOccured);
static rsn_siteBanEntry_t * findEntryForInsert(void * hRsn);
static rsn_siteBanEntry_t * findBannedSiteAndCleanup(void * hRsn, TMacAddr siteBssid);
TI_STATUS rsn_resetPreAuthCache(rsn_t *pRsn);
TI_STATUS rsn_resetPreAuthList(void * hRsn);
TI_STATUS rsn_getPreAuthList (rsn_t * pRsn,OS_802_11_PMKID *preAuthList);


#endif

#define PAIRWISE_MIC_FAIL_FILTER_DEF       (1)
#define RSN_WEPMIXEDMODE_ENABLED_DEF       (0)
#define RSN_PREAUTH_TIMEOUT_DEF_MS      (2000)
#define RSN_WEP_STATUS_DEF                 (0)

#define WPA_ALG_IGTK (4)

// ----------------------------------------------------------------------------

void rsn_init()
{
    HOOK(HOOK_RSN);

   memset(&gRsnDB, 0, sizeof(rsnCB_t));
}


// ----------------------------------------------------------------------------
void rsn_setCryptoParams(uint32_t aRoleId, uint32_t aPairwiseSuite, uint32_t aGroupSuite)
{
    HOOK(HOOK_RSN);

    // Set the pairwise cipher suite
    switch (aPairwiseSuite)
    {
        case WPA_CIPHER_NONE:
            gRsnDB.unicastSuite = CIPHER_SUITE_NONE;
            break;

        case WPA_CIPHER_WEP104:
        case WPA_CIPHER_WEP40:
            gRsnDB.unicastSuite = CIPHER_SUITE_WEP;
            break;

       case WPA_CIPHER_TKIP:
           gRsnDB.unicastSuite = CIPHER_SUITE_TKIP;
           break;

        case WPA_CIPHER_CCMP:
            gRsnDB.unicastSuite = CIPHER_SUITE_AES;
            break;

        case WPA_CIPHER_GCMP:
            gRsnDB.unicastSuite = CIPHER_SUITE_GCMP128;
            break;

        case WPA_CIPHER_BIP_CMAC_256:
            gRsnDB.unicastSuite = CIPHER_BIP_CMAC_256;
            break;

        case WPA_CIPHER_BIP_GMAC_128:
            gRsnDB.unicastSuite = CIPHER_BIP_GMAC_128;
            break;

        case WPA_CIPHER_BIP_GMAC_256:
            gRsnDB.unicastSuite = CIPHER_BIP_GMAC_256;
            break;

        case WPA_CIPHER_GCMP_256:
            gRsnDB.unicastSuite = CIPHER_SUITE_GCMP256;
            break;

        case WPA_CIPHER_CCMP_256:
            gRsnDB.unicastSuite = CIPHER_SUITE_CCMP256;
            break;


        default:
            CME_PRINT_REPORT_ERROR("\n\rrsn_setCryptoParams unsupported PairwiseSuite %d",aPairwiseSuite) ;
            // TODO - not supported in MCP
            ASSERT_GENERAL(0);
            break;
    }

    GTRACE(GRP_DRIVER_CC33, "Set cipher pairwise to ENUM(CipherSuite_e, %d)", gRsnDB.unicastSuite);


    // Set the group cipher suite
    switch (aGroupSuite)
    {
        case WPA_CIPHER_NONE:
            gRsnDB.broadcastSuite = CIPHER_SUITE_NONE;
            break;

        case WPA_CIPHER_WEP104:
        case WPA_CIPHER_WEP40:
            gRsnDB.broadcastSuite = CIPHER_SUITE_WEP;
            break;

        case WPA_CIPHER_TKIP:
            gRsnDB.broadcastSuite = CIPHER_SUITE_TKIP;
            break;

        case WPA_CIPHER_CCMP:
            gRsnDB.broadcastSuite = CIPHER_SUITE_AES;
            break;

        case WPA_CIPHER_BIP_CMAC_256:
            gRsnDB.broadcastSuite = CIPHER_BIP_CMAC_256;
            break;
        case WPA_CIPHER_BIP_GMAC_128:
            gRsnDB.broadcastSuite = CIPHER_BIP_GMAC_128;
            break;
        case WPA_CIPHER_BIP_GMAC_256:
            gRsnDB.broadcastSuite = CIPHER_BIP_GMAC_256;
            break;
        case WPA_CIPHER_GCMP_256:
            gRsnDB.broadcastSuite = CIPHER_SUITE_GCMP256;
            break;
        case WPA_CIPHER_CCMP_256:
            gRsnDB.broadcastSuite = CIPHER_SUITE_CCMP256;
            break;
        case WPA_CIPHER_GCMP:
            gRsnDB.broadcastSuite = CIPHER_SUITE_GCMP128;
            break;
        default:

            CME_PRINT_REPORT_ERROR("\n\rrsn_setCryptoParams unsupported GroupSuite %d",aGroupSuite) ;

            ASSERT_GENERAL(0);
            break;
    }

    GTRACE(GRP_DRIVER_CC33, "Set cipher group to ENUM(CipherSuite_e, %d)", gRsnDB.broadcastSuite);
}

/*-----------------------------------------------------------------------------
Routine Name: notifyPreAuthStatus
Routine Description: This routine is used to notify higher level application
                     of the pre-authentication status
Arguments: newStatus - pre authentication status
Return Value: none
-----------------------------------------------------------------------------*/
// No one is registered on this event in WL8 so no implementation here
//static void notifyPreAuthStatus (preAuthStatusEvent_e aNewStatus)
//{
//    evHandler_HandleEvent(pRsn->hEvHandler, pRsn->pRoleDesc->uNetIfId, TIW_DRV_EV_WPA2_PREAUTHENTICATION,
//                            (uint8_t*)&memBuff, sizeof(uint32_t));

//}

/*
 * Parse and translate the rsnIE and return it in security information format, as described in wlan.h
 * (for survey scan results security information)
 * Just OR the security type bits so it can be run sequentially on WPA IE and RSN IE
 *
 * Params: dot11_RSN_t *rsnIe - pointer to the rsn ie
 *         uint8_t rsnIeLen - rsnIE len
 *         uint16_t *securityType [out] - returned security type
 *
 * Return - 0 on success, negative on error
 *
 */
int rsn_rsnWpaIe2SecurityInfo(dot11_RSN_t *rsnIe, uint8_t rsnIeLen, uint32_t *securityType)
{
    int result = 0;
    struct wpa_ie_data parsedSec;
    int i;
    bool checkPmf = false;

    GTRACE(GRP_DRIVER_CC33, "RSN; Parse RSN/WPA IE");
    DRV_PRINT_REPORT("\n\rRSN; Parse RSN/WPA IE ");
    DRV_PRINT_REPORT("\n\r RSN data");
    DRV_PRINT_REPORT("\n\r start RSN print eleId: %d eleLen:%d rsnIeLen:%d",rsnIe->hdr.eleId,rsnIe->hdr.eleLen,rsnIeLen);

    for (i=0;i<rsnIe->hdr.eleLen;i++ )
    {
        DRV_PRINT_REPORT(" %02x",(uint8_t)rsnIe->rsnIeData[i]);
    }
    DRV_PRINT_REPORT("\n\r");


    result = wpa_parse_wpa_ie( (u8 *) rsnIe, rsnIeLen, &parsedSec);

    if (result != 0)
    {
        GTRACE(GRP_DRIVER_CC33, "RSN: Parsed RSN IE error, result - %d", result);

        return  (-1);
    }

    //Construct security type

    if (parsedSec.proto & WPA_PROTO_WPA)
    {
        *securityType |= ((RSN_WLAN_SECURITY_TYPE_BITMAP_WPA & RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK) << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION);
        DRV_PRINT_REPORT("\n\r WPA_PROTO_WPA securityType:0x%x", *securityType);
    }
    else if ((parsedSec.proto & WPA_PROTO_RSN) && ((parsedSec.group_cipher == WPA_CIPHER_TKIP) && (parsedSec.pairwise_cipher == WPA_CIPHER_TKIP)))
    {
        *securityType |= ((RSN_WLAN_SECURITY_TYPE_BITMAP_WPA & RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK) << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION);
        DRV_PRINT_REPORT("\n\r TKIP - securityType:0x%x", *securityType);
    }
    else if ((parsedSec.proto & WPA_PROTO_RSN) && ((parsedSec.key_mgmt == (WPA_KEY_MGMT_SAE | WPA_KEY_MGMT_PSK)) || (parsedSec.key_mgmt == (WPA_KEY_MGMT_SAE | WPA_KEY_MGMT_PSK_SHA256))))
    {
        // WPA2/3
        checkPmf = true;
        *securityType |= (((RSN_WLAN_SECURITY_TYPE_BITMAP_WPA3) & RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK) << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION);
        *securityType |= ((RSN_WLAN_SECURITY_TYPE_BITMAP_WPA2 & RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK) << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION);
        DRV_PRINT_REPORT("\n\r WPA2/3 - securityType:0x%x", *securityType);
    }
    else if ((parsedSec.proto & WPA_PROTO_RSN) && (parsedSec.key_mgmt & (WPA_KEY_MGMT_SAE | WPA_KEY_MGMT_FT_SAE)))
    {
        // WPA3 - SAE
        checkPmf = true;
        *securityType |= ((RSN_WLAN_SECURITY_TYPE_BITMAP_WPA3 & RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK) << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION);
        DRV_PRINT_REPORT("\n\r WPA3 - SAE securityType:0x%x", *securityType);
    }
    else if (parsedSec.proto & WPA_PROTO_RSN)
    {
        // WPA2
        checkPmf = true;
        *securityType |= ((RSN_WLAN_SECURITY_TYPE_BITMAP_WPA2 & RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK) << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION);
        DRV_PRINT_REPORT("\n\r WPA_PROTO_RSN securityType:0x%x", *securityType);
    }

    if(checkPmf)
    {
        if(0 != (parsedSec.capabilities & BIT_6))
        {
            *securityType |= ((RSN_WLAN_SECURITY_TYPE_BITMAP_PMF_REQUIRED & RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK) << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION);
        }
        
        if(0 != (parsedSec.capabilities & BIT_7))
        {
            *securityType |= ((RSN_WLAN_SECURITY_TYPE_BITMAP_PMF_CAPABLE & RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK) << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION);
        }
    }

    //Key management (PSK=bit0, 802.1X=bit1 — from supplicant WPA_KEY_MGMT_PSK=BIT(1), WPA_KEY_MGMT_IEEE8021X=BIT(0))
    *securityType |= ((((uint32_t)parsedSec.key_mgmt) & RSN_WLAN_SCAN_RESULT_KEY_MGMT_MASK) << RSN_WLAN_SCAN_RESULT_KEY_MGMT_POSITION);
    DRV_PRINT_REPORT("\n\r adding key mgmt securityType:0x%x", *securityType);

    //SAE key management (WPA3-Personal) — supplicant WPA_KEY_MGMT_SAE=BIT(10), stored as bit2 of key_mgmt field
    if (parsedSec.key_mgmt & (WPA_KEY_MGMT_SAE | WPA_KEY_MGMT_FT_SAE))
    {
        *securityType |= (RSN_WLAN_KEY_MGMT_SUITE_SAE << RSN_WLAN_SCAN_RESULT_KEY_MGMT_POSITION);
        DRV_PRINT_REPORT("\n\r adding SAE key mgmt securityType:0x%x", *securityType);
    }


    //Group Cipher (bit map definitions in wlan.h is shifted by 1 compared to the bitmap definitions in supplicant)
    *securityType |= (((((uint32_t)parsedSec.group_cipher) >> 1) & RSN_WLAN_SCAN_RESULT_GROUP_CIPHER_MASK) << RSN_WLAN_SCAN_RESULT_GROUP_CIPHER_POSITION);
    DRV_PRINT_REPORT("\n\r adding Group Cipher securityType:0x%x", *securityType);

    //Pairwise Cipher (bit map definitions in wlan.h is shifted by 1 compared to the bitmap definitions in supplicant)
    *securityType |= (((((uint32_t)parsedSec.pairwise_cipher) >> 1) & RSN_WLAN_SCAN_RESULT_UNICAST_CIPHER_MASK) << RSN_WLAN_SCAN_RESULT_UNICAST_CIPHER_POSITION);
    DRV_PRINT_REPORT("\n\r adding Pairwise Cipher securityType:0x%x", *securityType);


    GTRACE(GRP_DRIVER_CC33, "RSN: key_mgmt 0x%x , group_cipher 0x%x, pairwise_cipher 0x%x, proto 0x%x,  securityType 0x%x" , parsedSec.key_mgmt,
           parsedSec.group_cipher,
           parsedSec.pairwise_cipher,
           parsedSec.proto,
           *securityType);

    DRV_PRINT_REPORT ("\n\rRSN: key_mgmt 0x%x , group_cipher 0x%x, pairwise_cipher 0x%x, proto 0x%x,  securityType 0x%x" , parsedSec.key_mgmt,
    parsedSec.group_cipher,
    parsedSec.pairwise_cipher,
    parsedSec.proto,
    *securityType);
    return (result);
}


/*
 * Parse the payload for RSN ie and WPA IE and return the security type (SL_SEC_TYPE_OPEN / SL_SEC_TYPE_WEP / SL_SEC_TYPE_WPA_WPA2 / CME_SEC_TYPE_WPA_ENT)
 * The payload should be at the beginning of the IE, regardless of the type of packet beacon/probe response/ association response.
 *
 * Params: uint16_t dot11CapabilityInfo
 *         uint8_t *payload - pointer to the beginning of the IE. Beacon or probe response payload
 *         uint8_t payloadLen
 *         uint8_t *securityType [out] - returned security type from WPA/RSN IE
 *         uint8_t *securityTypeOverride [out] - returned security type from RSN Override IE
 *         uint8_t *securityTypeOverride2 [out] - returned security type from RSN Override 2 IE
 *
 * Return - 0 on success, negative on error
 *
 */
int rsn_getSecurityTypes(uint16_t dot11CapabilityInfo, dot11_RSN_t *pDotRsn, dot11_RSN_t *pDotWpa, dot11_RSN_t *pDotRsnOverride, dot11_RSN_t *pDotRsnOverride2, uint8_t *securityType, uint8_t *securityTypeOverride, uint8_t *securityTypeOverride2)
{
    int result = 0;
    uint8_t secType = 0xff; //0xff - security type not found
    uint8_t secTypeOverride = 0xff; //0xff - security type not found
    uint8_t secTypeOverride2 = 0xff; //0xff - security type not found

    if (0 == (dot11CapabilityInfo & DOT11_CAPABILITY_PRIVACY))
    {
        secType = CME_SEC_TYPE_OPEN; //Security type open
    }
    else{        
        if ((pDotRsn == NULL) && (pDotWpa == NULL) && (pDotRsnOverride == NULL) && (pDotRsnOverride2 == NULL))
        {
            //Security type wep
            secType = CME_SEC_TYPE_WEP;
        }
        else
        {
            //Check key management & ciphers in WPA_IE and/or RSN_IE and set security type
            if (pDotRsn)
            {
                rsn_getSecurityTypeFrom_IE(pDotRsn, &secType);
            }
            else if (pDotWpa)
            {
                rsn_getSecurityTypeFrom_IE(pDotWpa, &secType);
            }
            
            //Check RSN Override IEs if present
            if (pDotRsnOverride)
            {
                rsn_getSecurityTypeFrom_IE(pDotRsnOverride, &secTypeOverride);
            }
            if (pDotRsnOverride2)
            {
                rsn_getSecurityTypeFrom_IE(pDotRsnOverride2, &secTypeOverride2);
            }
        }
    }

    if ((secType == 0xff) && (secTypeOverride == 0xff) && (secTypeOverride2 == 0xff))
    {
        result = -1;
    }

    GTRACE(GRP_DRIVER_CC33, "RSN: Security types are secType: ENUM(CMESecType_e,%d), secTypeOverride: ENUM(CMESecType_e,%d), secTypeOverride2: ENUM(CMESecType_e,%d)", (CMESecType_e) secType, (CMESecType_e) secTypeOverride, (CMESecType_e) secTypeOverride2);
    *securityType = secType;
    *securityTypeOverride = secTypeOverride;
    *securityTypeOverride2 = secTypeOverride2;

    return (result);
}

/*
 * Check key management & ciphers in WPA_IE or RSN_IE and return security type (SL_SEC_TYPE_OPEN / SL_SEC_TYPE_WEP / SL_SEC_TYPE_WPA_WPA2 / CME_SEC_TYPE_WPA_ENT)
 *
 * Params: dot11_RSN_t *pDotRsn
 *         uint8_t *secType [out] - returned security type
 *
 */
void rsn_getSecurityTypeFrom_IE(dot11_RSN_t *pDotRsn, uint8_t *secType)
{
    struct wpa_ie_data parsedSec;
    struct wpa_ie_data parsedSec_wpa;
    uint8_t parseDescRet = 0;


    //TODO: for now, Supplicant code (wpa_parse_wpa_ie) does not check for WEP ciphers in the RSN IE or WPA IE. Add in future.

    HOOK(HOOK_RSN);

    if ((wpa_parse_wpa_ie( (u8 *) pDotRsn, (pDotRsn->hdr.eleLen) + 2 , &parsedSec)) < 0)
    {
        return;
    }

    parseDescRet =wpa_parse_wpa_ie_wpa( (u8 *) pDotRsn, (pDotRsn->hdr.eleLen) + 2 , &parsedSec_wpa);

    if ( (wpa_key_mgmt_wpa_ieee8021x (parsedSec.key_mgmt)) ||
            ((parseDescRet>=0) && wpa_key_mgmt_wpa_ieee8021x(parsedSec_wpa.key_mgmt)))

    {
        //Security type Enterprise
        *secType = CME_SEC_TYPE_WPA_ENT;
    }
    else if (wpa_key_mgmt_wpa_psk(parsedSec.key_mgmt))
    {
        Bool_e sae_only = (parsedSec.key_mgmt & (WPA_KEY_MGMT_PSK |
                                                 WPA_KEY_MGMT_FT_PSK |
                                                 WPA_KEY_MGMT_PSK_SHA256)) == 0;
        if(sae_only)
        {
            *secType = CME_SEC_TYPE_WPA3;
        }
        else if ((parsedSec.key_mgmt & (WPA_KEY_MGMT_SAE | WPA_KEY_MGMT_FT_SAE)) == 0) 
        {
            if ((parsedSec.capabilities & (WPA_CAPABILITY_MFPC | WPA_CAPABILITY_MFPR)) == 0)
            {
                // Check if WPA-only
                if (parsedSec.proto == WPA_PROTO_WPA)
                {
                    *secType = CME_SEC_TYPE_WPA;
                }
                else
                {
                    // WPA2-only or WPA-WPA2 mixed mode
                    *secType = CME_SEC_TYPE_WPA_WPA2;
                    if (((parsedSec.pairwise_cipher & WPA_CIPHER_TKIP) == 0) && ((parsedSec.group_cipher & WPA_CIPHER_TKIP) == 0))
                    {
                        *secType = CME_SEC_TYPE_WPA2_AES_ONLY_NO_PMF;
                    }
                }
            }
            else
            {
                *secType = CME_SEC_TYPE_WPA2_PLUS;
                if (((parsedSec.pairwise_cipher & WPA_CIPHER_TKIP) == 0) && ((parsedSec.group_cipher & WPA_CIPHER_TKIP) == 0))
                {
                    *secType = CME_SEC_TYPE_WPA2_AES_ONLY_PMF;
                }  
            }
        }
        else
        {
            *secType = CME_SEC_TYPE_WPA2_WPA3;
        }

 
    }
    else if ((parsedSec.pairwise_cipher & (WPA_CIPHER_WEP40 | WPA_CIPHER_WEP104)) &&
             (parsedSec.group_cipher & (WPA_CIPHER_WEP40 | WPA_CIPHER_WEP104)))
    {
        //Security type wep
        *secType = CME_SEC_TYPE_WEP;
    }

    return;
}


#if 0
/**
*
* rsn_resetPreAuthList -
*
* \b Description:
*   Cleans up the PreAuth cache. Called when SSID is being
*   changed.
*
* \b ARGS:
*
*  I   - hRsn - RSN SM context  \n
*
* \b RETURNS:
*
*  TI_OK if successful, TI_NOK otherwise.
*/

TI_STATUS rsn_resetPreAuthList(void * hRsn)
{
    return rsn_resetPreAuthCache(pRsn);
}

/**
*
* rsn_findPreAuthBssid
*
* \b Description:
*
* Finds if AP is in the PreAuth List

* \b ARGS:
*
*  I   - pRsn     - pointer to rsn context
*  I   - pBSSID   - pointer to AP's BSSID address
*  O   - cacheIndex  - index of the cache table entry containing the
                       bssid
*
* \b RETURNS:
*
* TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_STATUS rsn_findPreAuthBssid (rsn_t * pRsn, TMacAddr *pBSSID, uint8_t  *cacheIndex)
{

    uint8_t           i     = 0;
    TMacAddr    entryMac;


    while((i < RSN_PREAUTH_CACHE_SIZE) && (i <= pRsn->preAuthCache.entriesNumber))
    {
        MAC_COPY (entryMac, pRsn->preAuthCache.preAuthTbl[i].bssId);
        if (MAC_EQUAL (entryMac, *pBSSID))
        {
            *cacheIndex = i;
            return TI_OK;
        }
        i++;
    }

    return TI_NOK;
}


/**
*
* rsn_getPreAuthList
*
* \b Description:
*
* Returns content of the Pre Auth List
*
* \b ARGS:
*
*  I   - pRsn            - pointer to rsn context
*  O   - preAuthList      memory buffer where the procedure
*  writes the preAuth BSSID's. Supplied by the caller
*  procedure.
*
* \b RETURNS:
*
* TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_STATUS rsn_getPreAuthList (rsn_t * pRsn, OS_802_11_PMKID *preAuthList)
{
    uint8_t   neededLength, i = 0;
    uint8_t   NumOfEntries = pRsn->preAuthCache.entriesNumber;
    uint8_t   *bssid;

    /* Check the buffer length */
    if(NumOfEntries > 1)
       neededLength = 30 + ((NumOfEntries - 1) * (MAC_ADDR_LEN));
    else
       neededLength = 30;

    if(neededLength > preAuthList->Length)
    {
        /* The buffer length is not enough */
        preAuthList->Length = neededLength;
        return TI_NOK;
    }

    /* The buffer is big enough. Fill the info */
    preAuthList->Length         = neededLength;
    preAuthList->BSSIDInfoCount = NumOfEntries;

    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN:  Get PreAuth cache.  Number of entries  = %d \n", NumOfEntries);

    for (i = 0; i < NumOfEntries; i++ )
    {
        bssid = (uint8_t *) pRsn->preAuthCache.preAuthTbl[i].bssId;

        MAC_COPY(preAuthList->osBSSIDInfo[i].BSSID, bssid);
        os_memoryZero(pRsn->hOs,
                      (void *)preAuthList->osBSSIDInfo[i].PMKID,
                      PMKID_VALUE_SIZE);

        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN:  BSSID:  %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
    }

    return TI_OK;
}

/**
*
* rsn_addPreAuthBssid
*
* \b Description:
*
* Add/Set an AP received from the Supplicant to pre auth list
*
* \b ARGS:
*
*  I   - pRsn     - pointer to rsn context
*  I   - pBSSID   - pointer to AP's BSSID address
*
* \b RETURNS:
*
* TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_STATUS rsn_addPreAuthBssid (rsn_t *pRsn, TMacAddr *pBSSID)
{
    uint8_t      cacheIndex;
    TI_STATUS     status = TI_NOK;

    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "rsn_addPreAuthBssid: received new BSSID " MACSTR "\n",
           (*pBSSID)[0],
           (*pBSSID)[1],
           (*pBSSID)[2],
           (*pBSSID)[3],
           (*pBSSID)[4],
           (*pBSSID)[5]);

    /* Try to find the pBSSId in the PreAuth cache */
    status = rsn_findPreAuthBssid (pRsn, pBSSID, &cacheIndex);

    if (status != TI_OK)
    {
        /* This is a new entry. Copy the new entry to the next free place.*/
        cacheIndex = pRsn->preAuthCache.nextFreeEntry;
        MAC_COPY (pRsn->preAuthCache.preAuthTbl[cacheIndex].bssId, *pBSSID);

        /* Update the next free entry index. (If the table is full, a new entry */
        /* will override the oldest entries from the beginning of the table)    */
        /* Update the number of entries. (it cannot be more than max cach size) */
        pRsn->preAuthCache.nextFreeEntry  = (cacheIndex + 1) % RSN_PREAUTH_CACHE_SIZE;

        if(pRsn->preAuthCache.entriesNumber < RSN_PREAUTH_CACHE_SIZE)
            pRsn->preAuthCache.entriesNumber ++;
    }

    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN:  Add BSSID: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X in index %d\n", (*pBSSID)[0], (*pBSSID)[1], (*pBSSID)[2], (*pBSSID)[3], (*pBSSID)[4], (*pBSSID)[5], cacheIndex);

    return TI_OK;
}

/**
*
* rsn_setPreAuthList
*
* \b Description:
*
* Set Pre Auth cache
*
* \b ARGS:
*
*  I   - pRsn            - pointer to rsn context
*  O   - pPreAuthList       - memory buffer where the procedure
*  reads the BSSID's from. Supplied by the caller procedure.
* \b RETURNS:
*
* TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_STATUS rsn_setPreAuthList (rsn_t *pRsn, OS_802_11_PMKID *pPreAuthList)
{
    uint8_t          neededLength, i = 0;
    uint8_t          NumOfEntries;
    TMacAddr          macAddr;

    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: rsn_setPreAuthList \n");

    TRACE_INFO_HEX(pRsn->hReport, (uint8_t*)pPreAuthList ,sizeof(OS_802_11_PMKID));

    /* Check the num of entries in the buffer: if 0 it means that */
    /* pre auth cache has to be cleaned                              */
    if(pPreAuthList->BSSIDInfoCount == 0)
    {
        rsn_resetPreAuthCache(pRsn);
        return TI_OK;
    }

    /* Check the minimal buffer length */
    if (pPreAuthList->Length < 2*sizeof(uint32_t))
    {
        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: Set Pre Auth list - Buffer size < min length (8 bytes). Supplied length is %d .\n", pPreAuthList->Length);
        return TI_NOK;
    }

    /* Check the buffer length */
    NumOfEntries = (uint8_t)pPreAuthList->BSSIDInfoCount;
    neededLength =  2*sizeof(uint32_t) + (NumOfEntries  *(MAC_ADDR_LEN + PMKID_VALUE_SIZE));

    if(pPreAuthList->Length < neededLength)
    {
        /* Something wrong with the buffer */
        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: Set Pre Auth list - no enough room for %d entries Needed length is %d. Supplied length is %d .\n", NumOfEntries, neededLength,pPreAuthList->Length);
        return TI_NOK;
    }

    /*  Fill the PreAuth cashe */
    pPreAuthList->BSSIDInfoCount = NumOfEntries;
    for (i = 0; i < NumOfEntries; i++ )
    {
         MAC_COPY (macAddr, pPreAuthList->osBSSIDInfo[i].BSSID);

         TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION , "rsn_setPreAuthList: Received new pre-auth AP\n");
         if (pRsn->numberOfPreAuthCandidates)
         {
            pRsn->numberOfPreAuthCandidates--;
            if (pRsn->numberOfPreAuthCandidates == 0)
            {
               TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION , "Stopping the Pre-Auth timer since Pre-auth is finished\n");
               tmr_StopTimer (pRsn->hPreAuthTimerWpa2);
               /* Send PRE-AUTH end event to External Application */
               notifyPreAuthStatus (pRsn, RSN_PRE_AUTH_END);
            }

            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION , "rsn_setPreAuthList: %d APs left in candidate list\n",pRsn->numberOfPreAuthCandidates);
         }
        else
        {
           TRACE(pRsn->hReport, REPORT_SEVERITY_WARNING , "rsn_setPreAuthList: number of candidates was already zero...\n");
        }
        rsn_addPreAuthBssid(pRsn,&macAddr);
    }

    return TI_OK;

}

/**
*
* rsn_resetPreAuthCache
*
* \b Description:
*
* Reset Pre Auth Table
*
* \b ARGS:
*
*  I   - pRsn - pointer to rsn context
*
* \b RETURNS:
*
* TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_STATUS rsn_resetPreAuthCache (rsn_t *pRsn)
{
    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN:  Reset PreAuth cache.  %d entries are deleted. \n", pRsn->preAuthCache.entriesNumber);
    os_memoryZero(pRsn->hOs, (void*)&pRsn->preAuthCache, sizeof(preAuthCache_t));
    return TI_OK;
}


/**
*
* rsn_getPreAuthStatus
*
* \b Description:
*
* Returns the status of the Pre Auth for the BSSID. If the authentictaion mode
 * is not WPA2, then TI_FALSE will be returned.
*  For WPA2 mode, if BSSID exists in the ptre auth table and its
*  liftime is valid TI_TRUE will be returned. Otherwise
*  TI_FALSE.
*
*
*
* \b ARGS:
*  I   - pRsn     - pointer to rsn context
 * I   - givenAP  - required BSSID
*
* \b RETURNS:
*
* TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_BOOL rsn_GetPreAuthStatus(void * hRsn, TMacAddr *givenAP, uint8_t  *cacheIndex)
{
    rsn_t           *pRsn = (rsn_t*)hRsn;

    if (rsn_findPreAuthBssid (pRsn, givenAP, cacheIndex)!=TI_OK)
    {
        return TI_FALSE;
    }
    return TI_TRUE;
}

#endif

// ----------------------------------------------------------------------------
int32_t rsn_SetDefaults(uint32_t aRoleID, Bool32 aPrivacyOn)
{
    HOOK(HOOK_RSN);

    gRsnDB.roleId = aRoleID;

    if (TRUE == aPrivacyOn)
    {
        gRsnDB.broadcastSuite = CIPHER_SUITE_WEP;
        gRsnDB.unicastSuite = CIPHER_SUITE_WEP;
    }
    else
    {
        gRsnDB.broadcastSuite = CIPHER_SUITE_NONE;
        gRsnDB.unicastSuite = CIPHER_SUITE_NONE;
    }

    // The below is set in MCP in rsn_SetDefaults when a STA is started.
    // All parameters are hard coded.
    // Actually all 3 fields can be removed as they are never changed, they're
    // kept for the meantime lest we need to dynamically change them in the future.
//    gRsnDB.pairwiseMicFailureFilter = PAIRWISE_MIC_FAIL_FILTER_DEF;
//    gRsnDB.mixedMode = RSN_WEPMIXEDMODE_ENABLED_DEF;
//    gRsnDB.preAuthTimeout = RSN_PREAUTH_TIMEOUT_DEF_MS;

//    gRsnDB.numberOfPreAuthCandidates = 0;
//    gRsnDB.waitRsnSuccess = FALSE;

#if 0

    /* Create preAuthTimerWpa2 timer */
    if (OSI_OK != osi_TimerCreate(&gRsnDB.preAuthTimerWpa2, "preAuthTimerWpa2", preAuthTimeout, NULL))
    {
        GTRACE(GRP_CME,  "ERROR RSN: Failed to create preAuthTimerWpa2");
        ASSERT_GENERAL(0);
        return -1;
    }


    /* Create the module's timers */
    if (OSI_OK != osi_TimerCreate(&gRsnDB.micFailureReportWaitTimer, "micFailureReportWaitTimer", micFailureReportTimeout))
    {
        GTRACE(GRP_CME,  "ERROR RSN: Failed to create micFailureReportWaitTimer");
        ASSERT_GENERAL(0);
        return -1;
    }

    if (OSI_OK != osi_TimerCreate(&gRsnDB.micFailureGroupReKeyTimer, "micFailureGroupReKeyTimer", groupReKeyTimeout))
    {
        GTRACE(GRP_CME,  "ERROR RSN: Failed to create micFailureGroupReKeyTimer");
        ASSERT_GENERAL(0);
        return -1;
    }

    if (OSI_OK != osi_TimerCreate(&gRsnDB.micFailurePairwiseReKeyTimer, "micFailurePairwiseReKeyTimer", pairwiseReKeyTimeout))
    {
        GTRACE(GRP_CME,  "ERROR RSN: Failed to create micFailurePairwiseReKeyTimer");
        ASSERT_GENERAL(0);
        return -1;
    }
#endif


#ifdef CCX_MODULE_INCLUDED
    pRsn->networkEapMode = OS_CCX_NETWORK_EAP_OFF;
#endif /* CCX_MODULE_INCLUDED */

    return 0;
}



#if 0


/**
*
* rsn_Start - Start event for the RSN SM
*
* \b Description:
*
* Start event for the RSN SM
*
* \b ARGS:
*
*  I   - hRsn - RSN SM context  \n
*
* \b RETURNS:
*
*  TI_OK if successful, TI_NOK otherwise.
*
* \sa rsn_Stop, rsn_Recv
*/
TI_STATUS rsn_start(void * hRsn)
{
    rsn_t               *pRsn;

    pRsn = (rsn_t*)hRsn;

    if (pRsn == NULL)
    {
        return TI_NOK;
    }

    pRsn->bWaitRsnSuccess = TI_TRUE;
    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "rsn_start ...\n");

    return TI_OK;
}



/**
*
* rsn_Stop - Stop event for the RSN SM
*
* \b Description:
*
* Stop event for the RSN SM
*
* \b ARGS:
*
*  I   - hRsn - RSN SM context  \n
*
* \b RETURNS:
*
*  TI_OK if successful, TI_NOK otherwise.
*
* \sa rsn_Start, rsn_Recv
*/
TI_STATUS rsn_stop (void * hRsn, TI_BOOL removeKeys)
{
    rsn_t           *pRsn;

    pRsn = (rsn_t*)hRsn;

    if (pRsn == NULL)
    {
        return TI_NOK;
    }

    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: calling STOP... removeKeys=%d\n", removeKeys);
    pRsn->bWaitRsnSuccess = TI_FALSE;

    pRsn->eGroupKeyUpdate = GROUP_KEY_UPDATE_FALSE;
    pRsn->ePairwiseKeyUpdate = PAIRWISE_KEY_UPDATE_FALSE;

    tmr_StopTimer (pRsn->hMicFailureReportWaitTimer);

    /* Stop the pre-authentication timer in case we are disconnecting */
    tmr_StopTimer (pRsn->hPreAuthTimerWpa2);

#ifdef CCX_MODULE_INCLUDED
    pRsn->networkEapMode = OS_CCX_NETWORK_EAP_OFF;
#endif /* CCX_MODULE_INCLUDED */

    if (removeKeys)
    {   /* reset Pre Auth list if exist */
        rsn_resetPreAuthList(pRsn);
    }


    return TI_OK;
}



/**
*
* rsn_getCipherSuite  - get current broadcast cipher suite support.
*
* \b Description:
*
* get current broadcast cipher suite support.
*
* \b ARGS:
*
*  I   - pRsn - context \n
*  O   - suite - cipher suite to work with \n
*
* \b RETURNS:
*
*  TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_STATUS rsn_getCipherSuite(rsn_t *pRsn, TrsnEncryptionStatus *pSuite)
{
    if (pRsn == NULL)
    {
        return TI_NOK;
    }

    //*pSuite = (pRsn->broadcastSuite > pRsn->unicastSuite) ? pRsn->broadcastSuite : pRsn->unicastSuite;

    pSuite->eRsnEncrGroup = pRsn->broadcastSuite;
    pSuite->eRsnEncrPairwise = pRsn->unicastSuite;
    return TI_OK;
}


TI_STATUS rsn_getParamEncryptionStatus(void * hRsn, TrsnEncryptionStatus *rsnStatus)
{ /* RSN_ENCRYPTION_STATUS_PARAM */
    rsn_t       *pRsn = (rsn_t *)hRsn;
    TI_STATUS   status = TI_NOK;

    if ( (NULL == pRsn) || (NULL == rsnStatus) )
    {
        return status;
    }
    status = rsn_getCipherSuite(pRsn, rsnStatus);
    return status;
}



/**
*
* rsn_getExtAuthMode  - Get current External authentication Mode Status.
*
* \b Description:
*
* Get current External Mode Status.
*
* \b ARGS:
*
*  I   - pRsn - context \n
*  I   - pExtAuthMode - CCX External Mode Status \n
*
* \b RETURNS:
*
*  TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_STATUS rsn_getExtAuthMode(rsn_t *pRsn, EExternalAuthMode *pExtAuthMode)
{
    *pExtAuthMode = pRsn->externalAuthMode;

    return TI_OK;
}



/**
*
* rsn_GetParam - Get a specific parameter from the RSN SM
*
* \b Description:
*
* Get a specific parameter from the RSN SM.
*
* \b ARGS:
*
*  I   - hRsn - RSN SM context  \n
*  I/O - pParam - Parameter \n
*
* \b RETURNS:
*
*  TI_OK if successful, TI_NOK otherwise.
*
* \sa rsn_Start, rsn_Stop
*/
TI_STATUS rsn_getParam(void * hRsn, void *param)
{
    rsn_t       *pRsn = (rsn_t *)hRsn;
    paramInfo_t *pParam = (paramInfo_t*)param;
    TI_STATUS   status = TI_OK;

    if ( (NULL == pRsn) || (NULL == pParam) )
    {
        return TI_NOK;
    }

 /*   if (!pRsn->pRoleDesc->bIsEnabled)
    {
        return STATION_IS_NOT_RUNNING;
    }*/

    switch (pParam->paramType)
    {
    case TI_PARAM_ENCRYPTION_STATUS:
        status = rsn_getCipherSuite (pRsn, &pParam->content.tRsnEncryptionStatus);
        break;

    case TI_PARAM_EXT_AUTHENTICATION_MODE:
        status = rsn_getExtAuthMode (pRsn, &pParam->content.rsnExtAuthneticationMode);
        break;

    case TI_PARAM_MIXED_MODE:
        pParam->content.rsnMixedMode = pRsn->bMixedMode;
        status = TI_OK;
        break;

    case TI_PARAM_PREAUTH_LIST:
         pParam->content.rsnPreAuthList.Length = pParam->paramLength;
         status = rsn_getPreAuthList (pRsn, &pParam->content.rsnPreAuthList);
         pParam->paramLength = pParam->content.rsnPreAuthList.Length + 2 * sizeof(uint32_t);
         break;

#ifdef CCX_MODULE_INCLUDED
    case TI_PARAM_CCX_NETWORK_EAP:
        status = rsn_getNetworkEap (pRsn, &pParam->content.networkEap);
        break;
#endif /* CCX_MODULE_INCLUDED */

    case TI_PARAM_PORT_STATUS:
        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: Get Port Status\n"  );
        pParam->content.rsnPortStatus = rsn_getPortStatus( pRsn );
        break;

    default:
        return TI_NOK;
    }

    return status;
}




/**
*
* rsn_setUcastSuite  - Set current unicast cipher suite support.
*
* \b Description:
*
* Set current unicast cipher suite support.
*
* \b ARGS:
*
*  I   - pRsn - context \n
*  I   - suite - cipher suite to work with \n
*
* \b RETURNS:
*
*  TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_STATUS rsn_setUcastSuite(rsn_t *pRsn, ECipherSuite suite)
{
    pRsn->unicastSuite = suite;

    return TI_OK;
}


/**
*
* rsn_setBcastSuite  - Set current broadcast cipher suite support.
*
* \b Description:
*
* Set current broadcast cipher suite support.
*
* \b ARGS:
*
*  I   - pRsn - context \n
*  I   - suite - cipher suite to work with \n
*
* \b RETURNS:
*
*  TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_STATUS rsn_setBcastSuite(rsn_t *pRsn, ECipherSuite suite)
{
    pRsn->broadcastSuite = suite;

    return TI_OK;
}


/**
*
* rsn_setExtAuthMode  - Set current External authentication Mode Status.
*
* \b Description:
*
* Set current External authentication Mode Status.
*
* \b ARGS:
*
*  I   - pRsn - context \n
*  I   - extAuthMode - External authentication Mode \n
*
* \b RETURNS:
*
*  TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_STATUS rsn_setExtAuthMode(rsn_t *pRsn, EExternalAuthMode extAuthMode)
{
    if (extAuthMode >= RSN_EXT_AUTH_MODEMAX)
    {
        return TI_NOK;
    }

    pRsn->externalAuthMode = extAuthMode;

    return TI_OK;
}

#endif

// ----------------------------------------------------------------------------
void rsn_addKey(securityKeys_t *apSecurityKey,const char *ifname)
{
    GTRACE(GRP_DRIVER_CC33_DEBUG, "RSN: add key KeyIndex 0x%x, keyLength=%d keyType %d",
                                   apSecurityKey->keyIndex, apSecurityKey->encLen, apSecurityKey->keyType);

    // Remove the key when the length is 0, or the type is not set
    if ( (WPA_ALG_NONE == apSecurityKey->keyType) || (0 == apSecurityKey->encLen) )
    {
        // Set the security type from RSN DB, to be used in the remove function below
        // (RSN DB is updated in rsn_setKey)

        rsn_removeKey(apSecurityKey, ifname);
    }
    else
    {
        // Set the key to FW
        rsn_setKey(apSecurityKey, ifname);
    }
}

// ----------------------------------------------------------------------------
uint32_t rsn_getGenericIe(uint32_t aRoleId, uint8_t *apGenericIE)
{
    os_memcpy(apGenericIE, &gRsnDB.genericIE.data, gRsnDB.genericIE.length);
    GTRACE(GRP_DRIVER_CC33, "RSN: IE length = %d", gRsnDB.genericIE.length);

    return gRsnDB.genericIE.length;
}

// ----------------------------------------------------------------------------
legacyAuthType_e rsn_setAuthParams(uint32_t aRoleId,
                                   int32_t  aAuthAlg,
                                   uint32_t aKeySuite,
                                   const uint8_t *apWpaIe,
                                   uint32_t      aWpaIeLen)
{
    legacyAuthType_e    legacyAuthType = AUTH_LEGACY_OPEN_SYSTEM;
    externalAuthMode_e  externalAuthMode;

    GTRACE(GRP_DRIVER_CC33, "RSN: auth alg 0x%x, key suite %d, WPA IE len %d",
                            aAuthAlg, aKeySuite, aWpaIeLen);

    // Set a default value, updated below if parameters are OK
    gRsnDB.externalAuthMode = RSN_EXT_AUTH_MODE_OPEN;

    // Store the WPA IE
    gRsnDB.genericIE.length = aWpaIeLen;
    if (255 < aWpaIeLen)
    {
        GTRACE(GRP_DRIVER_CC33, "WARNING RSN: length %d exceeds max length 255, truncating", aWpaIeLen);
        gRsnDB.genericIE.length = 255;
    }
    os_memcpy((void*)&gRsnDB.genericIE.data, apWpaIe, gRsnDB.genericIE.length);

    // Set the external auth mode
    if (NULL == apWpaIe || 0 == aWpaIeLen)
    {
        if (aAuthAlg & WPA_DRIVER_AUTH_SHARED)
        {
            if (aAuthAlg & WPA_DRIVER_AUTH_OPEN)
            {
                externalAuthMode = RSN_EXT_AUTH_MODE_AUTO_SWITCH;
            }
            else
            {
                externalAuthMode = RSN_EXT_AUTH_MODE_SHARED_KEY;
            }
        }
        else
        {
            externalAuthMode = RSN_EXT_AUTH_MODE_OPEN;
        }
    }
    else if (WLAN_EID_RSN == apWpaIe[0])
    {
        if (WPA_KEY_MGMT_PSK == aKeySuite)
        {
            externalAuthMode = RSN_EXT_AUTH_MODE_WPA2PSK;
        }
        else
        {
            externalAuthMode = RSN_EXT_AUTH_MODE_WPA2;
        }
    }
    else
    {
        if (WPA_KEY_MGMT_PSK == aKeySuite)
        {
            externalAuthMode = RSN_EXT_AUTH_MODE_WPAPSK;
        }
        else
        {
            externalAuthMode = RSN_EXT_AUTH_MODE_WPA;
        }
    }

    GTRACE(GRP_DRIVER_CC33, "RSN: setting external auth mode to ENUM(externalAuthMode_e,%d)", externalAuthMode);

    if (RSN_EXT_AUTH_MODEMAX <= externalAuthMode)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR RSN: illegal rsnExtAuthneticationMode %d", externalAuthMode);

        // If external auth mode is illegal, set the legacy one to a default
        // value of OPEN
        return AUTH_LEGACY_OPEN_SYSTEM;
    }

    gRsnDB.externalAuthMode = externalAuthMode;

    // Select the correct legacy autjentication mode
    if (RSN_EXT_AUTH_MODE_SHARED_KEY == externalAuthMode)
    {
        legacyAuthType = AUTH_LEGACY_SHARED_KEY;
    }

    return legacyAuthType;
}

#if 0
int32_t rsn_setParam(void *apParam)
{
    paramInfo_t         *pParam = (paramInfo_t*)param;
    TI_STATUS           status = TI_OK;

    pRsn = (rsn_t*)hRsn;

    if ( (NULL == pRsn) || (NULL == pParam) )
    {
        return TI_NOK;
    }

    /*if (!pRsn->pRoleDesc->bIsEnabled)
    {
        return STATION_IS_NOT_RUNNING;
    }*/

    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: Set rsn_setParam   %X \n", pParam->paramType);

    switch (pParam->paramType)
    {


    case TI_PARAM_ENCRYPTION_STATUS:
        {
            pRsn->unicastSuite   = pParam->content.tRsnEncryptionStatus.eRsnEncrPairwise;
            pRsn->broadcastSuite = pParam->content.tRsnEncryptionStatus.eRsnEncrGroup;
            status = TI_OK;
        }
        break;

    case TI_PARAM_EXT_AUTHENTICATION_MODE:
        {
            legacyAuthType_e eLegacyAuthType;

            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: Set TI_PARAM_EXT_AUTHENTICATION_MODE rsnExtAuthneticationMode  %d \n", pParam->content.rsnExtAuthneticationMode);

            status = rsn_setExtAuthMode (pRsn, pParam->content.rsnExtAuthneticationMode);

            if (status == TI_OK) {
                if (pParam->content.rsnExtAuthneticationMode == RSN_EXT_AUTH_MODE_SHARED_KEY)
                {
                    eLegacyAuthType = AUTH_LEGACY_SHARED_KEY;
                }
                else
                {
                    eLegacyAuthType = AUTH_LEGACY_OPEN_SYSTEM;
                }

                mlme_SetLegacyAuthType(pRsn->hMlme, eLegacyAuthType);
            }
            else
            {
                TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "error on rsn_setExtAuthMode ()");
            }

        }
        break;

#ifdef CCX_MODULE_INCLUDED
    case TI_PARAM_CCX_NETWORK_EAP:
        {
            OS_CCX_NETWORK_EAP      networkEap = 0;

            rsn_getNetworkEap (pRsn, &networkEap);
            if (networkEap != pParam->content.networkEap)
            {
                TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: Set TI_PARAM_CCX_NETWORK_EAP networkEap  %d \n", pParam->content.networkEap);

                status = rsn_setNetworkEap (pRsn, pParam->content.networkEap);
                if (status == TI_OK)
                {
                    /*status = RE_SCAN_NEEDED;*/
                }
            }
        }
        break;
#endif /* CCX_MODULE_INCLUDED */
    case TI_PARAM_MIXED_MODE:
        {
            status = TI_OK;
            pRsn->bMixedMode = pParam->content.rsnMixedMode;

            break;
        }

    case TI_PARAM_PREAUTH_LIST:
        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: Set TI_PARAM_PREAUTH_LIST \n");

        TRACE_INFO_HEX(pRsn->hReport, (uint8_t*)&pParam->content.rsnPreAuthList ,sizeof(OS_802_11_PMKID));
        status = rsn_setPreAuthList (pRsn, &pParam->content.rsnPreAuthList);

        if(status == TI_OK)
        {
            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: Set TI_PARAM_PREAUTH_LIST:   %d Pre Auth entries has been added to the cache.\n", pParam->content.rsnPreAuthList.BSSIDInfoCount);
        }
        else
        {
            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: Set TI_PARAM_PREAUTH_LIST failure");
        }
        break;

    case TI_PARAM_ADD_KEY:
        {
            TSecurityKeys *pSecurityKey = pParam->content.pRsnKey;
            uint32_t     keyIndex;
            uint8_t      hlid;

            TRACE(pRsn->hReport,REPORT_SEVERITY_INFORMATION,"RSN:Set TI_PARAM_ADD_KEY KeyIndex %x,keyLength=%d\n",pSecurityKey->keyIndex,pSecurityKey->encLen);
            keyIndex = (uint8_t)pSecurityKey->keyIndex;

            if(keyIndex >= MAX_KEYS_NUM)
            {
                return TI_NOK;
            }

            /* Reset the security sequence number only for unicat re-key */
            if (!MAC_BROADCAST(pSecurityKey->macAddress))
            {
                hlid = (uint8_t)roleSta_GetApLinkId(pRsn->pRoleDesc->hRoleHandle);
                wlanLinks_ResetLinkSecuritySeqNum(pRsn->hWlanLinks, hlid);
            }

            //report_PrintDump((void*)pSecurityKey,sizeof(*pSecurityKey));

            /* Remove the key when the length is 0, or the type is not set */
            if ( (pSecurityKey->keyType == KEY_NULL) ||
                    (pSecurityKey->encLen == 0))
            {
                /* Clearing a key */
                status = rsn_removeKey( pRsn, pSecurityKey );
            }
            else
            {
                status = rsn_setKey (pRsn, pSecurityKey);  /* send key to FW*/
            }
        }
        break;

    case TI_PARAM_PORT_STATUS:
        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: Set Port Status %d \n", pParam->content.rsnPortStatus);
        status = rsn_setPortStatus( hRsn, pParam->content.rsnPortStatus );
        break;

    case TI_PARAM_WPA_IE:
           TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: Set Generic IE: length=%d, IE=%02x%02x%02x... \n", pParam->content.rsnGenericIE.length, pParam->content.rsnGenericIE.data[0], pParam->content.rsnGenericIE.data[1],pParam->content.rsnGenericIE.data[2] );

        status = TI_OK;

        if (pParam->content.rsnGenericIE.length > 255)
        {
            TRACE(pRsn->hReport, REPORT_SEVERITY_WARNING, "RSN: Set Generic IE: length %d exceeds max length 255, truncating\n",
                   pParam->content.rsnGenericIE.length);
            pParam->content.rsnGenericIE.length = 255;
        }

        pRsn->genericIE.length = pParam->content.rsnGenericIE.length;
        os_memoryCopy(pRsn->hOs,(void*)pRsn->genericIE.data, (uint8_t*)pParam->content.rsnGenericIE.data, pParam->content.rsnGenericIE.length);
        break;

    default:
        return TI_NOK;
    }

    return status;
}

/**
*
* rsn_parseIe  - Parse a required information element.
*
* \b Description:
*
* Parse an Aironet information element.
* Builds a structure of all the capabilities described in the Aironet IE.
* We look at Flags field only to determine KP and MIC bits value
*
* \b ARGS:
*
*  I   - pRsn - pointer to admCtrl context
*  I   - pAironetIe - pointer to Aironet IE buffer  \n
*  O   - pAironetData - capabilities structure
*
*
* \b RETURNS:
*
* TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_STATUS rsn_parseIe(rsn_t *pRsn, TRsnData *pRsnData, uint8_t **pIe, uint8_t IeId)
{

    dot11_eleHdr_t      *eleHdr;
    TI_INT16             length;
    uint8_t            *pCurIe;


    *pIe = NULL;

    if ((pRsnData == NULL) || (pRsnData->ieLen==0))
    {
       return TI_OK;
    }

    pCurIe = pRsnData->pIe;

    length = pRsnData->ieLen;
    while (length>0)
    {
        eleHdr = (dot11_eleHdr_t*)pCurIe;

        if (length<((*eleHdr)[1] + 2))
        {
            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "admCtrl_parseIe ERROR: pRsnData->ieLen=%d, length=%d\n\n", pRsnData->ieLen,length);
            return TI_OK;
        }

        if ((*eleHdr)[0] == IeId)
        {
            *pIe = (uint8_t*)eleHdr;
            break;
        }
        length -= (*eleHdr)[1] + 2;
        pCurIe += (*eleHdr)[1] + 2;
    }
    return TI_OK;
}


/**
*
* rsn_eventRecv - Set a specific parameter to the RSN SM
*
* \b Description:
*
* Set a specific parameter to the RSN SM.
*
* \b ARGS:
*
*  I   - hRsn - RSN SM context  \n
*  I/O - pParam - Parameter \n
*
* \b RETURNS:
*
*  TI_OK if successful, TI_NOK otherwise.
*
* \sa rsn_Start, rsn_Stop
*/
TI_STATUS rsn_reportStatus (rsn_t *pRsn, TI_STATUS rsnStatus)
{
    TI_STATUS status = TI_OK;
    uint32_t uApLink;
    TI_BOOL bEncrypt, bDropBcast;

    if (pRsn == NULL)
    {
        return TI_NOK;
    }

    uApLink = roleSta_GetApLinkId(pRsn->pRoleDesc->hRoleHandle);

    pRsn->bWaitRsnSuccess = TI_FALSE;
    if (rsnStatus == TI_OK)
    {
        bEncrypt = (pRsn->unicastSuite != TWD_CIPHER_NONE);
        bDropBcast = (pRsn->bMixedMode) ? TI_FALSE : bEncrypt;

        udata_SetDataEncryption(pRsn->hUdata, uApLink, bEncrypt, bDropBcast, bEncrypt);
        wlanLinks_SetLinkDataEncryption(pRsn->hWlanLinks, uApLink, bEncrypt);
    }
    else
    {
        rsnStatus = (TI_STATUS)STATUS_SECURITY_FAILURE;
    }

    status = connInfra_reportRsnStatus(pRsn->hConn, (mgmtStatus_e)rsnStatus);

    if (status!=TI_OK)
    {
        return status;
    }

    if (rsnStatus == TI_OK)
    {
        evHandler_HandleEvent (pRsn->hEvHandler, pRsn->pRoleDesc->uNetIfId, TIW_DRV_EV_AUTH_SUCC, NULL, 0);
    }

    /* for wpa2, encrypt eapols after port is open */
    if (   (pRsn->externalAuthMode == RSN_EXT_AUTH_MODE_WPA2) ||
            (pRsn->externalAuthMode == RSN_EXT_AUTH_MODE_WPA2PSK))
    {
        udata_SetEapolEncryption(pRsn->hUdata, uApLink, TI_TRUE);
    }

    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: rsn_reportStatus \n");

    return TI_OK;
}

#ifdef CCX_MODULE_INCLUDED
/**
*
* rsn_getCcxExtendedInfoElement -
*
* \b Description:
*
* Get the Aironet information element.
*
* \b ARGS:
*
*  I   - hRsn - Rsn SM context  \n
*  I/O - pRsnIe - Pointer to the return information element \n
*  I/O - pRsnIeLen - Pointer to the returned IE's length \n
*
* \b RETURNS:
*
*  TI_OK if successful, TI_NOK otherwise.
*
* \sa
*/
TI_STATUS rsn_getCcxExtendedInfoElement(void * hRsn, uint8_t *pRsnIe, uint8_t *pRsnIeLen)
{
    rsn_t       *pRsn;
    TI_STATUS   status;

    if ( (NULL == hRsn) || (NULL == pRsnIe) || (NULL == pRsnIeLen) )
    {
        return TI_NOK;
    }

    pRsn = (rsn_t*)hRsn;

    status = admCtrlCcx_getInfoElement (pRsn, pRsnIe, pRsnIeLen);

    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "rsn_getCcxExtendedInfoElement pRsnIeLen= %d\n",*pRsnIeLen);

    return status;
}


void rsn_CcxSetSite(void * hRsn, TRsnData *pRsnData, uint8_t *pAssocIe)
{
    rsn_t        *pRsn = (rsn_t *)hRsn;
    paramInfo_t  *pParam;

    pParam = (paramInfo_t *)os_memoryAlloc(pRsn->hOs, sizeof(paramInfo_t));
    if (!pParam) {
        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "rsn_ccxSetSite: malloc failed!");
        return;
    }

    if ((pRsn->externalAuthMode != RSN_EXT_AUTH_MODE_WPA2) &&
            (pRsn->externalAuthMode != RSN_EXT_AUTH_MODE_WPA))
    {
        ccxMngr_SetCckmExists(pRsn->hCcxMngr, TI_FALSE);
    }
    else
    {
        admCtrlCcx_setExtendedParams(pRsn, pRsnData);

        ccxMngr_SetCckmExists(pRsn->hCcxMngr, TI_TRUE);
    }

    os_memoryFree(pRsn->hOs, pParam, sizeof(paramInfo_t));
}

#endif /* CCX_MODULE_INCLUDED */

#endif // if 0

// ----------------------------------------------------------------------------

#if 0
static void saveKey(securityKeys_t *apSecurityKey)
{
    uint8_t keyIndex = apSecurityKey->keyIndex; // & ~TIWLAN_KEY_FLAGS_TRANSMIT;
                                              // TODO in MCP the above is set in driver_wilink
                                              // we don't set it and don't forward the command to RSN

#ifdef GEM_SUPPORTED
    if (pKey->keyType == KEY_GEM)
    {
        keyIndex = (MAC_BROADCAST(pKey->macAddress)) ? 0 : 1;
    }
#endif

    if (MAX_KEYS_NUM <= keyIndex)
        return;

    os_memcpy(&gRsnDB.keys[keyIndex], apSecurityKey, sizeof(*apSecurityKey));
}
#endif

#if 0

void removeKey(rsn_t *pRsn, uint32_t uKeyIndex)
{
    if (uKeyIndex >= ARRAY_LEN(pRsn->aKeys))
        return;

    os_memoryZero(pRsn->hOs, &pRsn->aKeys[uKeyIndex], sizeof(TSecurityKeys));
}
#endif


////
#if 0
TI_STATUS rsn_setKey (rsn_t *pRsn, TSecurityKeys *pKey)
{
    TTwdParamInfo       tTwdParam;
    TI_STATUS           status = TI_OK;
    TI_BOOL             bDefaultKey = TI_FALSE;


    saveKey(pRsn, pKey);

    tTwdParam.paramType = TWD_RSN_KEY_ADD_PARAM_ID;
    tTwdParam.content.configureCmdCBParams.pCb = (uint8_t*) pKey;
    tTwdParam.content.configureCmdCBParams.fCb = NULL;
    tTwdParam.content.configureCmdCBParams.hCb = NULL;
    status = TWD_SetParam (pRsn->hTWD, &tTwdParam);
    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: rsn_setKey, KeyType=%d, KeyId = 0x%lx,encLen=0x%x\n", pKey->keyType,pKey->keyIndex, pKey->encLen);

    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "\nEncKey = ");

    TRACE_INFO_HEX(pRsn->hReport, (uint8_t *)pKey->encKey, pKey->encLen);

    if (pKey->keyType != KEY_WEP)
    {
        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "\nMac address = ");
        TRACE_INFO_HEX(pRsn->hReport, (uint8_t *)pKey->macAddress, MAC_ADDR_LEN);
        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "\nRSC = ");
        TRACE_INFO_HEX(pRsn->hReport, (uint8_t *)pKey->keyRsc, KEY_RSC_LEN);
        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "\nMic RX = ");
        TRACE_INFO_HEX(pRsn->hReport, (uint8_t *)pKey->micRxKey, MAX_KEY_LEN);
        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "\nMic TX = ");
        TRACE_INFO_HEX(pRsn->hReport, (uint8_t *)pKey->micTxKey, MAX_KEY_LEN);
    }

    if ((pKey->keyType == KEY_WEP) && (bDefaultKey))    {
        status = rsn_setDefaultKeyId(pRsn, pKey->keyIndex, pKey->hlid);
        if (status!=TI_OK)
        {
            return status;
        }
    }
#ifdef GEM_SUPPORTED
    /* Don't encrypt the eapol in WAPI */
    if (pKey->keyType != KEY_GEM)
#endif
    {
        /* for wpa, encrypt eapols after unicast key is set */
        if (   ((pRsn->externalAuthMode == RSN_EXT_AUTH_MODE_WPA) ||
                (pRsn->externalAuthMode == RSN_EXT_AUTH_MODE_WPAPSK)) && !MAC_BROADCAST(pKey->macAddress))
            udata_SetEapolEncryption(pRsn->hUdata, pKey->hlid, TI_TRUE);
    }

    return status;
}
#endif
////

// ----------------------------------------------------------------------------
void rsn_setKey(securityKeys_t *apSecurityKey, const char *ifname)
{
    Bool32              defaultKey = FALSE;

    HOOK(HOOK_RSN);

//    OsiReturnVal_e      osiRc;

    //saveKey(apSecurityKey); // TODO - code can be copied and activated here


    // Set key type for PMAC - this is done in setKey below directly on link DB
//    if ( (FALSE == MAC_BROADCAST(apSecurityKey->macAddress)) || (KEY_WEP == apSecurityKey->keyType)
//    {
//        TODO - udata_SetEncryptionType(pRsn->hUdata, apSecurityKey->hlid, apSecurityKey->keyType);
//
//    }

//TODO: implement filter of mic failue 3 sec (?) after set key
#if 0
    if (apSecurityKey->lidKeyType == KEY_TYPE_BROADCAST)
    {
        GTRACE(GRP_DRIVER_CC33, "RSN: Group ReKey timer started");

        osiRc = osi_TimerStop(&gRsnDB.micFailureGroupReKeyTimer);
        if (OSI_OK != osiRc)
        {
            GTRACE(GRP_DRIVER_CC33, "ERROR RSN: failed to stop group rekey timer, rc 0x%x", osiRc);
        }
        osiRc = osi_TimerStart(&gRsnDB.micFailureGroupReKeyTimer, RSN_MIC_FAILURE_RE_KEY_TIMEOUT_MS, 0 /* one shot */);
        if (OSI_OK != osiRc)
        {
            GTRACE(GRP_DRIVER_CC33, "ERROR RSN: failed to start group rekey timer, rc 0x%x", osiRc);
        }

        osi_TimerStop(&gRsnDB.micFailureGroupReKeyTimer);
        osi_TimerStart(&gRsnDB.micFailureGroupReKeyTimer, RSN_MIC_FAILURE_RE_KEY_TIMEOUT_MS, OSI_ONE_SHOT_TIMER);

        gRsnDB.groupKeyUpdate = TRUE;
    }
    else
    {
        if (gRsnDB.pairwiseMicFailureFilter)
        {
            GTRACE(GRP_DRIVER_CC33, "RSN: Pairwise ReKey timer started");

            osiRc = osi_TimerStop(&gRsnDB.micFailurePairwiseReKeyTimer);
            if (OSI_OK != osiRc)
            {
                GTRACE(GRP_DRIVER_CC33, "ERROR RSN: failed to stop pairwise rekey timer, rc 0x%x", osiRc);
            }
            osiRc = osi_TimerStart(&gRsnDB.micFailurePairwiseReKeyTimer, RSN_MIC_FAILURE_RE_KEY_TIMEOUT_MS, 0 /* one shot */);
            if (OSI_OK != osiRc)
            {
                GTRACE(GRP_DRIVER_CC33, "ERROR RSN: failed to strat pairwise rekey timer, rc 0x%x", osiRc);
            }

            osi_TimerStop(&gRsnDB.micFailurePairwiseReKeyTimer);
            osi_TimerStart(&gRsnDB.micFailurePairwiseReKeyTimer, RSN_MIC_FAILURE_RE_KEY_TIMEOUT_MS, OSI_ONE_SHOT_TIMER);

            gRsnDB.pairwiseKeyUpdate = TRUE;
        }
    }
#endif

//TODO: implement wep default key...
    if (WPA_ALG_WEP == apSecurityKey->keyType)
    {
        apSecurityKey->lidKeyType = KEY_TYPE_WEP_DEFAULT;
    }
    else
    {
        // TODO - is it needed?
//        wlanLinks_GetSecuritySeqNum(pRsn->hWlanLinks, apSecurityKey->hlid, &apSecurityKey->uSecuritySeqNumLow, &apSecurityKey->uSecuritySeqNumHigh);
    }

    // Send the key to WLAN services for link configuration - TODO - check where did I take the code in setKey
    setKey(KEY_ADD_OR_REPLACE, apSecurityKey, ifname);

    GTRACE(GRP_DRIVER_CC33, "RSN: link ID %d, type ENUM(LidKeyType_e, %d), KeyType = %d, KeyId = 0x%x, encLen=0x%x",
                            apSecurityKey->lid,
                            apSecurityKey->lidKeyType,
                            apSecurityKey->keyType,
                            apSecurityKey->keyIndex,
                            apSecurityKey->encLen);

//    GTRACE(GRP_DRIVER_CC33,  "EncKey = ");
//    TRACE_INFO_HEX(pRsn->hReport, (uint8_t *)apSecurityKey->encKey, apSecurityKey->encLen);

//    if (apSecurityKey->keyType != WPA_ALG_WEP)
//    {
//        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "\nMac address = ");
//        TRACE_INFO_HEX(pRsn->hReport, (uint8_t *)apSecurityKey->macAddress, MAC_ADDR_LEN);
//        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "\nRSC = ");
//        TRACE_INFO_HEX(pRsn->hReport, (uint8_t *)apSecurityKey->keyRsc, KEY_RSC_LEN);
//        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "\nMic RX = ");
//        TRACE_INFO_HEX(pRsn->hReport, (uint8_t *)apSecurityKey->micRxKey, MAX_KEY_LEN);
//        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "\nMic TX = ");
//        TRACE_INFO_HEX(pRsn->hReport, (uint8_t *)apSecurityKey->micTxKey, MAX_KEY_LEN);
//    }

    // 29.1.16 - compared till here

    if ((WPA_ALG_WEP == apSecurityKey->keyType) && defaultKey)
    {
        setDefaultKeyId(apSecurityKey->keyIndex, apSecurityKey->lid, ifname);
    }
#if 0
#ifdef GEM_SUPPORTED
    /* Don't encrypt the eapol in WAPI */
    if (apSecurityKey->keyType != KEY_GEM)
#endif
    {
        /* for wpa, encrypt eapols after unicast key is set */
        if (   ((RSN_EXT_AUTH_MODE_WPA == gRsnDB.externalAuthMode) ||
                (RSN_EXT_AUTH_MODE_WPAPSK == gRsnDB.externalAuthMode)) &&
                (FALSE == TEST_BROADCAST_ADDRESS(apSecurityKey->macAddress))  )
        {
//            udata_SetEapolEncryption(pRsn->hUdata, apSecurityKey->hlid, TI_TRUE);

            // TODO
            // Mark that EAPOLs need to be encrypted for this link.
            // This is used when sending EAPOLs to data path (driver_cc33 or data path API).
            // We also have to check EPAOL is for re-keying and make sure we're not connecting or roaming,
            // this is done in MCP by comparing link state to LINK_STATE_EAPOL || LINK_STATE_OPEN
//                typedef enum
//                {
//                    LINK_STATE_CLOSED,  /* closed for all packets. */
//                    LINK_STATE_MGMT,    /* open only for mgmt packets. */
//                    LINK_STATE_EAPOL,   /* open only for mgmt or EAPOL packets. */
//                    LINK_STATE_OPEN,   /* open for all packets. */
//                    LINK_STATE_NUM
//                } ELinkState;
        }
    }
#endif
}

#if 0
void rsn_SetKeys(void * hRsn)
{
    rsn_t        *pRsn = (rsn_t *)hRsn;
    uint8_t i;

    for (i = 0; i < ARRAY_LEN(pRsn->aKeys); i++)
    {
        TSecurityKeys *pKey = &pRsn->aKeys[i];

        if (pKey->keyType == KEY_NULL)
        {
            continue;
        }

        rsn_setKey(pRsn, pKey);
    }
}

#endif

// ----------------------------------------------------------------------------
// The below was imported from TWDriverCtrl.c
// ----------------------------------------------------------------------------
static void setKey(KeyAction_e aAction, securityKeys_t *apSecurityKey, const char *ifname)
{
    SetKey_t setKeyCfg;
    uint8_t  *pKeyData = apSecurityKey->encKey;
    uint8_t  keyLength = apSecurityKey->encLen;
    uint8_t  tkipKeyBuffer[KEY_SIZE_TKIP];
    Bool_e   isPmfEnable = FALSE;
    ti_driver_ifData_t * pDrv = drv_getDriverData(ifname);

    HOOK(HOOK_RSN);

    os_memset((void *)&setKeyCfg, 0, sizeof(setKeyCfg));

    setKeyCfg.lid = apSecurityKey->lid;
    setKeyCfg.lidKeyType = apSecurityKey->lidKeyType;
    setKeyCfg.action = aAction;
    setKeyCfg.keyId = (uint8_t)apSecurityKey->keyIndex;

    if ((KEY_REMOVE != aAction) &&
        ((apSecurityKey->keyType == WPA_ALG_TKIP) ||
         (apSecurityKey->keyType == WPA_ALG_CCMP) ||
         (apSecurityKey->keyType == WPA_ALG_IGTK) ||
         (apSecurityKey->keyType == WPA_ALG_BIP_CMAC_256) ||
         (apSecurityKey->keyType == WPA_ALG_BIP_GMAC_128) ||
         (apSecurityKey->keyType == WPA_ALG_BIP_GMAC_256)))
    {
        setKeyCfg.AcSeqNum16 = WPA_GET_LE16 (&(apSecurityKey->keyRsc[0]));
        setKeyCfg.AcSeqNum32 = WPA_GET_LE32 (&(apSecurityKey->keyRsc[2]));
    }

    switch (apSecurityKey->keyType)
    {
        case WPA_ALG_NONE:
            setKeyCfg.cipher_type = CIPHER_SUITE_NONE;
            break;
        case WPA_ALG_WEP:
            setKeyCfg.cipher_type = CIPHER_SUITE_WEP;
            break;

        case WPA_ALG_TKIP:
            setKeyCfg.cipher_type = CIPHER_SUITE_TKIP;

            /* Build the TKIP key*/
            if (KEY_REMOVE != aAction)
            {
                keyLength = KEY_SIZE_TKIP;
                os_memcpy((void*)(&tkipKeyBuffer[0]),  (void*)apSecurityKey->encKey,  16);
                os_memcpy((void*)(&tkipKeyBuffer[16]), (void*)apSecurityKey->micRxKey, 8);
                os_memcpy((void*)(&tkipKeyBuffer[24]), (void*)apSecurityKey->micTxKey, 8);
                pKeyData = tkipKeyBuffer;
            }
            break;

        case WPA_ALG_CCMP:
            setKeyCfg.cipher_type = CIPHER_SUITE_AES;
            break;

        case WPA_ALG_IGTK:
            setKeyCfg.cipher_type = CIPHER_BIP_CMAC_128;
            isPmfEnable = TRUE;
            break;

        case WPA_ALG_BIP_CMAC_256:
            setKeyCfg.cipher_type = CIPHER_BIP_CMAC_256;
            isPmfEnable = TRUE;
            break;

        case WPA_ALG_BIP_GMAC_128:
            setKeyCfg.cipher_type = CIPHER_BIP_GMAC_128;
            isPmfEnable = TRUE;
            break;

        case WPA_ALG_BIP_GMAC_256:
            setKeyCfg.cipher_type = CIPHER_BIP_GMAC_256;
            isPmfEnable = TRUE;
            break;

        case WPA_ALG_GCMP_256:
            setKeyCfg.cipher_type = CIPHER_SUITE_GCMP256;
            isPmfEnable = TRUE;
            break;

        default:
            CME_PRINT_REPORT_ERROR("\n\r setKey wrong cipher keyType:%d", apSecurityKey->keyType);
            ASSERT_GENERAL(0);
            return;
    }

    if (MAX_KEY_SIZE < keyLength)
    {
        os_memcpy((void *)setKeyCfg.key, (void *)pKeyData, MAX_KEY_SIZE);
        setKeyCfg.keySize = (uint8_t)(KeySize_e)MAX_KEY_SIZE;
    }
    else
    {
        os_memcpy((void *)setKeyCfg.key, (void *)pKeyData, keyLength);
        setKeyCfg.keySize = (uint8_t)(KeySize_e)keyLength;
    }
   
    /* Update the extra mem-blocks number per Tx packet according to the new security type */
   // updateLinkSecurityType(pTWD, eAction, apSecurityKey->hlid, apSecurityKey);
    {
        EKeyType keyType = KEY_NULL;
        Bool_e bEncrypt = FALSE, bDropBcast;


        if(apSecurityKey->keyType > WPA_ALG_BIP_CMAC_256)
        {
            ASSERT_GENERAL(0);
        }

        if(aAction != KEY_REMOVE)
        {
            keyType = (EKeyType)apSecurityKey->keyType;
            bEncrypt = TRUE;
        }
        else
        {
            isPmfEnable = FALSE;
        }

        //TODO need to see about mixed mode bDropBcast = (pRsn->bMixedMode) ? TI_FALSE : bEncrypt;
        bDropBcast = bEncrypt;

        // in case of aes encryption set rsn parameters per (key ID and PN numbers) link
        // rsn parameters used for detection replay attack (in function: wlanLinks_CheckLinkPn)
        if (apSecurityKey->keyType > WPA_ALG_TKIP)
        {
            if (apSecurityKey->lidKeyType == KEY_TYPE_UNICAST)
            {
                wlanLinks_SetLinkPn(apSecurityKey->lid, setKeyCfg.keyId, setKeyCfg.AcSeqNum16, setKeyCfg.AcSeqNum32);
            }
            else if (apSecurityKey->lidKeyType == KEY_TYPE_BROADCAST)
            {
                uint8 keyIndex = pDrv->broadcastNextKeyArrEntry;
                if ((AES_BROADCAST2_ENTRY == keyIndex) && (setKeyCfg.keyId == pDrv->security_key_idx_mc1))
                {
                    keyIndex = AES_BROADCAST1_ENTRY;
                }
                else if ((AES_BROADCAST1_ENTRY == keyIndex) && (setKeyCfg.keyId == pDrv->security_key_idx_mc2))
                {
                    keyIndex = AES_BROADCAST2_ENTRY;
                }
                wlanLinks_SetBroadcastPn((AESKey_rxPN_Tid_t *)&pDrv->broadcastPn[keyIndex],
                                         setKeyCfg.AcSeqNum16,
                                         setKeyCfg.AcSeqNum32);

                if (keyIndex == AES_BROADCAST1_ENTRY)
                {
                    pDrv->security_key_idx_mc1 = setKeyCfg.keyId;
                    pDrv->broadcastNextKeyArrEntry = AES_BROADCAST2_ENTRY;
                }
                else // AES_BROADCAST2_IDX
                {
                    pDrv->security_key_idx_mc2 = setKeyCfg.keyId;
                    pDrv->broadcastNextKeyArrEntry = AES_BROADCAST1_ENTRY;
                }
            }
        }
  
        wlanLinks_SetLinkDataEncryption(apSecurityKey->lid, bEncrypt);
        CME_CC3XX_PORT_PRINT("\n\r setting pmf for lid :%d pmf :%d", apSecurityKey->lid, isPmfEnable);
        GTRACE(GRP_DRIVER_CC33,"Setting pmf for lid :%d pmf :%d", apSecurityKey->lid, isPmfEnable);
        wlanLinks_UpdateLinkPMFEnabled(apSecurityKey->lid, isPmfEnable);
        udata_SetDataEncryption(apSecurityKey->lid, bEncrypt, bDropBcast, bEncrypt);

        // MGMT encryption for sta based role and ap role brodcast only
        // have ap based and lidkeytype is broadcast
        if ( ROLE_IS_TYPE_STA_BASED(pDrv->roleType) || ((apSecurityKey->lidKeyType == KEY_TYPE_BROADCAST) && ROLE_IS_TYPE_AP_BASED(pDrv->roleType)) )
        {
            udata_SetMgmtEncryption(apSecurityKey->lid, isPmfEnable);
        }
        
        if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType) && (apSecurityKey->lidKeyType == KEY_TYPE_UNICAST)) 
        {
            udata_SetEapolEncryption(apSecurityKey->lid, bEncrypt);
        }
        
        udata_SetEncryptionType(apSecurityKey->lid, keyType);
    }


    
    if(pDrv != NULL)
    {
        if(pDrv->roleEnabled)
        {
            pDrv->ops->set_key(&setKeyCfg);//cc3xxx_trnspt_cmd_if_set_key
        }
        else
        {
            GTRACE(GRP_DRIVER_CC33,"Role is disabled. Do not send set key command");
        }
    }
}

// ----------------------------------------------------------------------------
void rsn_removeKey(securityKeys_t *apSecurityKey, const char *ifname)
{
    enum wpa_alg keyType = apSecurityKey->keyType;

    GTRACE(GRP_DRIVER_CC33_DEBUG, "RSN: remove key link ID %d, keyType %d, keyIndex %d", apSecurityKey->lid, keyType, apSecurityKey->keyIndex);

    // If link ID is invalid, there's nothing to do here
    if (INVALID_LINK == apSecurityKey->lid)
        return;

    if ( (WPA_ALG_TKIP == keyType) || (WPA_ALG_CCMP == keyType) )
    {
        apSecurityKey->encLen = 16;
        if ( (0 == apSecurityKey->keyIndex) && (FALSE == TEST_BROADCAST_ADDRESS(apSecurityKey->macAddress)) )
            return;
    }


    // Update L2
    setKey(KEY_REMOVE, apSecurityKey, ifname);

    //os_memset(&gRsnDB.keys[keyIndex], 0, sizeof(securityKeys_t));
}

/* ----------------------------------------------------------------------------
 setDefaultKeyId
      set a default WEP key to FW

 Parameters:    default key ID
                Braodacst link ID
 Return code:   none
  ---------------------------------------------------------------------------- */
static void setDefaultKeyId(uint8_t aKeyId, uint32_t aBrcstLid, const char *ifname)
{
    SetKey_t  setKeyCfg;

    HOOK(HOOK_RSN);

    //
    // Original code
    //
//    TTwdParamInfo           tTwdParam;
//    TDefaultWepKeyIdRoleParams  tWepKeyIdParam;
//
//    tWepKeyIdParam.uBcastHlid = uBrcstHlid;
//    tWepKeyIdParam.uRsnDefaultKeyID = keyId;
//
//    /* Now we configure default key ID to the HAL */
//    tTwdParam.paramType = TWD_RSN_DEFAULT_KEY_ID_PARAM_ID;
//    tTwdParam.content.configureCmdCBParams.pCb = &tWepKeyIdParam;
//    tTwdParam.content.configureCmdCBParams.fCb = NULL;
//    tTwdParam.content.configureCmdCBParams.hCb = NULL;
//    status = TWD_SetParam (pRsn->hTWD, &tTwdParam);
//
//    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN: rsn_setDefaultKeyId, KeyId = 0x%lx\n", keyId);

    //
    // TWD handling for TWD_RSN_DEFAULT_KEY_ID_PARAM_ID
    //
    ASSERT_GENERAL(aKeyId <= MAX_DEFAULT_KEY_ID);

    os_memset(&setKeyCfg, 0, sizeof(setKeyCfg));
    setKeyCfg.lid  = aBrcstLid;
    setKeyCfg.lidKeyType = KEY_TYPE_WEP_DEFAULT;
    setKeyCfg.action = KEY_SET_ID;
    setKeyCfg.keySize = NO_KEY;
    setKeyCfg.cipher_type = CIPHER_SUITE_WEP;
    setKeyCfg.keyId = aKeyId;


    ti_driver_ifData_t * pDrv = drv_getDriverData(ifname);
    if(pDrv != NULL)
    {
        pDrv->ops->set_key(&setKeyCfg);
    }
}

#if 0
TI_STATUS rsn_reportAuthFailure(void * hRsn, EAuthStatus authStatus)
{
    TI_STATUS    status = TI_OK;
    rsn_t       *pRsn;
    TMacAddr    tCurrentBssid;

    if (hRsn==NULL)
    {
        return TI_NOK;
    }

    pRsn = (rsn_t*)hRsn;

    /* Remove AP from candidate list for a specified amount of time */
    roleSta_readCurrBssId(pRsn->pRoleDesc->hRoleHandle, tCurrentBssid);
    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "current station is banned from the roaming candidates list for %d Ms\n", RSN_AUTH_FAILURE_TIMEOUT);
    rsn_banSite(hRsn, tCurrentBssid, RSN_SITE_BAN_LEVEL_FULL, RSN_AUTH_FAILURE_TIMEOUT);

#ifdef CCX_MODULE_INCLUDED
    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "CALLING rougeAP, status= %d \n",authStatus);
    status = ccxMngr_SetRogueApDetected (pRsn->hCcxMngr, authStatus);
#endif /* CCX_MODULE_INCLUDED */
    TI_VOIDCAST(pRsn);
    return status;
}

/******
This is the CB function for mic failure event from the FW
 *******/
void rsn_reportMicFailure(void * hRsn, uint32_t link, uint8_t failureType)
{
    rsn_t                               *pRsn = (rsn_t *) hRsn;
    ERsnSiteBanLevel                    banLevel;
    TMacAddr                            tCurrentBssid;
    tiwdrv_external_event_t             tEvent;

    if (((pRsn->unicastSuite == TWD_CIPHER_TKIP) && (failureType == KEY_TKIP_MIC_PAIRWISE)) ||
            ((pRsn->broadcastSuite == TWD_CIPHER_TKIP) && (failureType == KEY_TKIP_MIC_GROUP)))
    {
        /* check if the MIC failure is group and group key update */
        /* was performed during the last 3 seconds */
        if ((failureType == KEY_TKIP_MIC_GROUP) &&
                (pRsn->eGroupKeyUpdate == GROUP_KEY_UPDATE_TRUE))
        {
            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, ": Group MIC failure ignored, key update was performed within the last 3 seconds.\n");
            return;
        }

        /* check if the MIC failure is pairwise and pairwise key update */
        /* was performed during the last 3 seconds */
        if ((failureType == KEY_TKIP_MIC_PAIRWISE) &&
                (pRsn->ePairwiseKeyUpdate == PAIRWISE_KEY_UPDATE_TRUE))
        {
            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, ": Pairwise MIC failure ignored, key update was performed within the last 3 seconds.\n");
            return;
        }



        roleSta_readCurrBssId(pRsn->pRoleDesc->hRoleHandle, (uint8_t *)tEvent.event_data.micfailure.src_addr);

        if (failureType == KEY_TKIP_MIC_PAIRWISE)
        {
            tEvent.event_data.micfailure.flags = MICFAILURE_GROUP;
        }
        else
        {
            tEvent.event_data.micfailure.flags = MICFAILURE_PAIRWISE;
        }

        evHandler_HandleEvent (pRsn->hEvHandler,
                pRsn->pRoleDesc->uNetIfId,
                TIW_DRV_EV_MIC_FAILURE,
                (uint8_t *)&tEvent,
                sizeof(tEvent));

        /* Update and check the ban level to decide what actions need to take place */
        banLevel = rsn_banSite (hRsn, tCurrentBssid, RSN_SITE_BAN_LEVEL_HALF, RSN_MIC_FAILURE_TIMEOUT);
        if (banLevel == RSN_SITE_BAN_LEVEL_FULL)
        {
            /* Site is banned so prepare to disconnect */
            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, ": Second MIC failure, closing Rx port...\n");

            udata_SetRxState(pRsn->hUdata, link, LINK_STATE_CLOSED);

            /* stop the mic failure Report timer and start a new one for 0.5 seconds */
            tmr_StopTimer (pRsn->hMicFailureReportWaitTimer);
            apConn_setDeauthPacketReasonCode(pRsn->hAPConn, STATUS_MIC_FAILURE);
            tmr_StartTimer (pRsn->hMicFailureReportWaitTimer,
                    micFailureReportTimeout,
                    (void *)pRsn,
                    RSN_MIC_FAILURE_REPORT_TIMEOUT,
                    TI_FALSE);
        }
        else
        {
            /* Site is only half banned so nothing needs to be done for now */
            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, ": First MIC failure, business as usual for now...\n");
        }
    }
}

#endif

#if 0
// ----------------------------------------------------------------------------
void groupReKeyTimeout()
{
    gRsnDB.groupKeyUpdate = FALSE;
}

// ----------------------------------------------------------------------------
void pairwiseReKeyTimeout()
{
    gRsnDB.pairwiseKeyUpdate = FALSE;
}

// ----------------------------------------------------------------------------
void micFailureReportTimeout ()
{

    GTRACE(GRP_DRIVER_CC33, "MIC failure reported, disassociating...");

    // TODO - report CME
//    apConn_reportRoamingEvent (pRsn->hAPConn, ROAMING_TRIGGER_SECURITY_ATTACK, NULL);
    ASSERT_GENERAL(0);
}
#endif

#if 0
void rsn_debugFunc(void * hRsn)
{
    rsn_t *pRsn = (rsn_t*)hRsn;

    if (pRsn == NULL)
    {
        return;
    }

}

#endif

// ----------------------------------------------------------------------------
#if 0
static void preAuthTimeout(void* pParam)
{
    GTRACE(GRP_DRIVER_CC33, "preAuthTimeout: PREAUTH EXPIRED !!!!!!!!");

    /* Send PRE-AUTH end event to External Application */
    notifyPreAuthStatus(RSN_PRE_AUTH_END);
    gRsnDB.numberOfPreAuthCandidates = 0;
}
#endif

#if 0

uint32_t  rsn_parseSuiteVal(rsn_t *pRsn, uint8_t* suiteVal, uint32_t maxVal, uint32_t unknownVal)
{
    uint32_t  suite;

    if ((pRsn==NULL) || (suiteVal==NULL))
    {
        return TWD_CIPHER_UNKNOWN;
    }
    if (!os_memoryCompare(pRsn->hOs, suiteVal, wpa2IeOuiIe, 3))
    {
        suite =  (ECipherSuite)((suiteVal[3]<=maxVal) ? suiteVal[3] : unknownVal);
    } else
    {
        suite = unknownVal;
    }
    return  suite;

}


/**
*
* rsn_parseRsnIe  - Parse an WPA information element.
*
* \b Description:
*
* Parse an WPA information element.
* Builds a structure of the unicast adn broadcast cihper suites,
* the key management suite and the capabilities.
*
* \b ARGS:
*
*  I   - pRsn - pointer to admCtrl context
*  I   - pWpa2Ie  - pointer to WPA IE (RSN IE) buffer  \n
*  O   - pWpa2Data - WPA2 IE (RSN IE) structure after parsing
*
*
* \b RETURNS:
*
* TI_OK on success, TI_NOK on failure.
*
* \sa
*/
TI_STATUS rsn_parseRsnIe(rsn_t *pRsn, uint8_t *pWpa2Ie, wpa2IeData_t *pWpa2Data)
{
    dot11_RSN_t      *wpa2Ie       =  (dot11_RSN_t *)pWpa2Ie;
    uint16_t            temp2bytes =0, capabilities;
    uint8_t             dataOffset = 0, i = 0, j = 0, curKeyMngSuite = 0;
    ECipherSuite     curCipherSuite = TWD_CIPHER_NONE;

    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "Wpa2_IE: DEBUG: admCtrlWpa2_parseIe\n\n");

    if ((pWpa2Data == NULL) || (pWpa2Ie == NULL))
    {
        return TI_NOK;
    }

    COPY_WLAN_WORD(&temp2bytes, wpa2Ie->rsnIeData);
    dataOffset += 2;

    /* Check the header fields and the version */
    if((wpa2Ie->hdr[0] != RSN_IE_ID) || (wpa2Ie->hdr[1] < WPA2_IE_MIN_LENGTH) ||
       (temp2bytes != WPA2_OUI_MAX_VERSION))
    {
        TRACE(pRsn->hReport, REPORT_SEVERITY_ERROR, "Wpa2_ParseIe Error: length=0x%x, elementid=0x%x, version=0x%x\n", wpa2Ie->hdr[1], wpa2Ie->hdr[0], temp2bytes);

        return TI_NOK;
    }


    /* Set default values */
    os_memoryZero(pRsn->hOs, pWpa2Data, sizeof(wpa2IeData_t));

    pWpa2Data->broadcastSuite = TWD_CIPHER_AES_CCMP;
    pWpa2Data->unicastSuiteCnt = 1;
    pWpa2Data->unicastSuite[0] = TWD_CIPHER_AES_CCMP;
    pWpa2Data->KeyMngSuiteCnt = 1;
    pWpa2Data->KeyMngSuite[0] = WPA2_IE_KEY_MNG_801_1X;

    /* If we've reached the end of the received RSN IE */
    if(wpa2Ie->hdr[1] < WPA2_IE_GROUP_SUITE_LENGTH)
        return TI_OK;

    /* Processing of Group Suite field - 4 bytes*/
    pWpa2Data->broadcastSuite = (ECipherSuite)rsn_parseSuiteVal(pRsn, (uint8_t *)wpa2Ie->rsnIeData + dataOffset,
                                                          TWD_CIPHER_WEP104, TWD_CIPHER_UNKNOWN);
    dataOffset +=4;
    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "Wpa2_IE: GroupSuite %x \n", pWpa2Data->broadcastSuite);


    /* Processing of Pairwise (Unicast) Cipher Suite - 2 bytes counter and list of 4-byte entries */
    if(wpa2Ie->hdr[1] < WPA2_IE_MIN_PAIRWISE_SUITE_LENGTH)
        return TI_OK;

    COPY_WLAN_WORD(&pWpa2Data->unicastSuiteCnt, wpa2Ie->rsnIeData + dataOffset);
    dataOffset += 2;

    if(pWpa2Data->unicastSuiteCnt > MAX_WPA2_UNICAST_SUITES)
    {
        /* something wrong in the RSN IE */
        TRACE(pRsn->hReport, REPORT_SEVERITY_ERROR, "Wpa2_ParseIe Error: Pairwise cipher suite count is  %d \n", pWpa2Data->unicastSuiteCnt);
        return TI_NOK;
    }

    /* Get unicast cipher suites */
    for(i = 0; i < pWpa2Data->unicastSuiteCnt; i++)
    {
        curCipherSuite = (ECipherSuite)rsn_parseSuiteVal(pRsn, (uint8_t *)wpa2Ie->rsnIeData + dataOffset,
                                                   TWD_CIPHER_WEP104, TWD_CIPHER_UNKNOWN);
        if(curCipherSuite == TWD_CIPHER_NONE)
            curCipherSuite = pWpa2Data->broadcastSuite;

        pWpa2Data->unicastSuite[i] = curCipherSuite;
        dataOffset +=4;

        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "Wpa_IE: unicast suite %x \n", curCipherSuite);
    }

    /* Sort all the unicast suites supported by the AP in the decreasing order */
    /* (so the best cipher suite will be the first)                            */
    if(pWpa2Data->unicastSuiteCnt > 1)
    {
       for(i = 0; i < (pWpa2Data->unicastSuiteCnt -1); i ++)
       {
           for(j = 0; j < i; j ++)
           {
               if(pWpa2Data->unicastSuite[j] > pWpa2Data->unicastSuite[j + 1])
               {
                   curCipherSuite               = pWpa2Data->unicastSuite[j];
                   pWpa2Data->unicastSuite[j]   = pWpa2Data->unicastSuite[j+1];
                   pWpa2Data->unicastSuite[j+1] = curCipherSuite;
               }
           }
       }
    }

    /* If we've reached the end of the received RSN IE */
    if (wpa2Ie->hdr[1] == dataOffset)
        return TI_OK;

     /* KeyMng Suite */
    COPY_WLAN_WORD(&(pWpa2Data->KeyMngSuiteCnt), wpa2Ie->rsnIeData + dataOffset);

     dataOffset += 2;
     // pRsn->wpaAkmExists = TI_FALSE;

    if(pWpa2Data->KeyMngSuiteCnt > MAX_WPA2_KEY_MNG_SUITES)
    {
        /* something wrong in the RSN IE */
        TRACE(pRsn->hReport, REPORT_SEVERITY_ERROR, "Wpa2_ParseIe Error: Management cipher suite count is  %d \n", pWpa2Data->KeyMngSuiteCnt);
        return TI_NOK;
    }

     for(i = 0; i < pWpa2Data->KeyMngSuiteCnt; i++)
     {
#ifdef CCX_MODULE_INCLUDED
            curKeyMngSuite = admCtrlCcx_parseCckmSuiteVal4Wpa2(pRsn, (uint8_t *)(wpa2Ie->rsnIeData + dataOffset));
            if (curKeyMngSuite == WPA2_IE_KEY_MNG_CCKM)
            {  /* CCKM is the maximum AKM */
                pWpa2Data->KeyMngSuite[i] = curKeyMngSuite;
            }
            else
#endif /* CCX_MODULE_INCLUDED */
            {
                curKeyMngSuite = rsn_parseSuiteVal(pRsn, (uint8_t *)wpa2Ie->rsnIeData + dataOffset,
                            WPA2_IE_KEY_MNG_PSK_801_1X, WPA2_IE_KEY_MNG_NA);
            }


        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "Wpa2_IE: authKeyMng %x  \n", curKeyMngSuite);

         if ((curKeyMngSuite != WPA2_IE_KEY_MNG_NA) &&
             (curKeyMngSuite != WPA2_IE_KEY_MNG_CCKM))
         {
             pWpa2Data->KeyMngSuite[i] = curKeyMngSuite;
         }

//         if (curKeyMngSuite==WPA2_IE_KEY_MNG_801_1X)
//         {   /* If 2 AKM exist, save also the second priority */
//             pRsn->wpaAkmExists = TI_TRUE;
//         }

         dataOffset += 4;

         /* Include all AP key management supported suites in the wpaData structure */
         /* pWpa2Data->KeyMngSuite[i+1] = curKeyMngSuite;*/

     }

    /* If we've reached the end of the received RSN IE */
    if (wpa2Ie->hdr[1] == dataOffset)
        return TI_OK;

    /* Parse capabilities */
    COPY_WLAN_WORD(&capabilities, wpa2Ie->rsnIeData + dataOffset);
    pWpa2Data->bcastForUnicatst  = (uint8_t)(capabilities & WPA2_GROUP_4_UNICAST_CAPABILITY_MASK)>>
                                           WPA2_GROUP_4_UNICAST_CAPABILITY_SHIFT;
    pWpa2Data->ptkReplayCounters = (uint8_t)(capabilities &  WPA2_PTK_REPLAY_COUNTERS_CAPABILITY_MASK)>>
                                           WPA2_PTK_REPLAY_COUNTERS_CAPABILITY_SHIFT;

    switch (pWpa2Data->ptkReplayCounters)
    {
    case 0: pWpa2Data->ptkReplayCounters=1;
            break;
    case 1: pWpa2Data->ptkReplayCounters=2;
            break;
    case 2: pWpa2Data->ptkReplayCounters=4;
            break;
    case 3: pWpa2Data->ptkReplayCounters=16;
            break;
    default: pWpa2Data->ptkReplayCounters=1;
            break;
   }
   pWpa2Data->gtkReplayCounters = (uint8_t)(capabilities &
                                        WPA2_GTK_REPLAY_COUNTERS_CAPABILITY_MASK) >>
                                        WPA2_GTK_REPLAY_COUNTERS_CAPABILITY_SHIFT;
   switch (pWpa2Data->gtkReplayCounters)
   {
   case 0: pWpa2Data->gtkReplayCounters=1;
            break;
   case 1: pWpa2Data->gtkReplayCounters=2;
            break;
   case 2: pWpa2Data->gtkReplayCounters=4;
            break;
   case 3: pWpa2Data->gtkReplayCounters=16;
            break;
   default: pWpa2Data->gtkReplayCounters=1;
            break;
   }

   pWpa2Data->preAuthentication = (uint8_t)(capabilities & WPA2_PREAUTH_CAPABILITY_MASK);

   dataOffset += 2;

   pWpa2Data->lengthWithoutPmkid = dataOffset + 2; /* +2 for IE header */

   TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "Wpa2_IE: capabilities %x, preAuthentication = %x, bcastForUnicatst %x, ptk = %x, gtk = %x, lengthWithoutPmkid = %d\n", capabilities, pWpa2Data->preAuthentication, pWpa2Data->bcastForUnicatst, pWpa2Data->ptkReplayCounters, pWpa2Data->gtkReplayCounters, pWpa2Data->lengthWithoutPmkid);


   return TI_OK;
}


/**
*
* rsn_buildAndSendPreAuthCandList
*
* \b Description:
*
* New Candidate List of APs with the same SSID as the STA is connected to
* is generated and sent after the delay to the supplicant
* in order to perform pre auth with suitable APs.
*
* \b ARGS:
*  I   - pRsn - pointer to rsn context
*
* \b RETURNS:
*
* TI_OK on success, TI_NOK on failure.
*
* \sa
*/

static void rsn_buildAndSendPreAuthCandList (void * hHandle, TBssidList4PreAuth *apList)
{
    rsn_t             *pRsn = (rsn_t*)hHandle;
    uint8_t          candIndex =0, apIndex = 0;
    paramInfo_t       *pParam;
    uint8_t          memBuff[PREAUTH_CAND_LIST_MEMBUFF_SIZE];
    OS_802_11_PMKID_CANDIDATELIST  *pCandList;
    dot11_RSN_t       *rsnIE = 0;
    wpa2IeData_t      wpa2Data;
    TI_STATUS         status = TI_NOK;
    tiwdrv_external_event_t tEvent;
    uint8_t i;

    pParam = (paramInfo_t *)os_memoryAlloc(pRsn->hOs, sizeof(paramInfo_t));
    if (!pParam)
    {
        return;
    }

    /* Get SSID that the STA is associated with    */
    pParam->paramType = TI_PARAM_CONNECT_REQUIRED;
    status          = sme_GetParam (pRsn->hSmeSm, pParam);
    if(status != TI_OK) {
        os_memoryFree(pRsn->hOs, pParam, sizeof(paramInfo_t));
        return;
    }

    /* If the existing cache table contains information for not relevant */
    /* ssid (i.e. ssid was changed), clean up the cache table and update */
    /* it with the new ssid */
    if ((pRsn->preAuthCache.ssid.len != pParam->content.smeDesiredSSID.len) ||
         (os_memoryCompare(pRsn->hOs, (uint8_t *)pRsn->preAuthCache.ssid.str,
          (uint8_t *) pParam->content.smeDesiredSSID.str,
          pRsn->preAuthCache.ssid.len) != 0))
    {
        rsn_resetPreAuthCache(pRsn);

        os_memoryCopy(pRsn->hOs, (void *)pRsn->preAuthCache.ssid.str,
                      (void *)pParam->content.smeDesiredSSID.str,
                      pParam->content.roleStaCurrentSSID.len);
        pRsn->preAuthCache.ssid.len = pParam->content.smeDesiredSSID.len;
    }


    os_memoryFree(pRsn->hOs, pParam, sizeof(paramInfo_t));
    if((apList == NULL) || (apList->NumOfItems == 0))
        return;

    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "rsn_buildAndSendPreAuthCandList - Entry \n");

    /* Build the pre-auth candidate list */
    pCandList = (OS_802_11_PMKID_CANDIDATELIST *)(memBuff);
    pCandList->Version = 1;
    for (apIndex=0; apIndex<pRsn->preAuthCache.entriesNumber; apIndex++)
    {
        pRsn->preAuthCache.preAuthTbl[apIndex].preAuthenticate = TI_FALSE;
    }

    /* Go over AP list and find APs supporting pre-authentication */
    for(apIndex = 0; apIndex < apList->NumOfItems && candIndex < PREAUTH_CAND_LIST_MAX_SIZE; apIndex++)
    {
        uint8_t *bssidMac, i = 0;

        status = TI_NOK;

        if (apList->bssidList[apIndex].pRsnIEs==NULL)
        {
            continue;
        }
        /* Check is there RSN IE in this site */
        rsnIE = 0;
        while(!rsnIE && (i < MAX_RSN_IE))
        {
            if(apList->bssidList[apIndex].pRsnIEs[i].hdr[0] == RSN_IE_ID)
            {
                rsnIE  = &apList->bssidList[apIndex].pRsnIEs[i];
                status = TI_OK;
            }
            i ++;
        }
        if (rsnIE)
        {
            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "rsn_buildAndSendPreAuthCandList - rsnIE-hdr.eleId = %x \n", rsnIE->hdr[0]);
        }

        if(status == TI_OK)
           status = rsn_parseRsnIe(pRsn, (uint8_t *)rsnIE, &wpa2Data);

        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "rsn_buildAndSendPreAuthCandList - parseIe status = %d \n", status);
        if(status == TI_OK)
        {
            TI_BOOL        preAuthStatus;
            uint8_t       cacheIndex;

            preAuthStatus = rsn_GetPreAuthStatus(pRsn, &apList->bssidList[apIndex].bssId, &cacheIndex);

            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "rsn_buildAndSendPreAuthCandList, preAuthStatus=%d  - Adding to candidate list for supp\n", preAuthStatus);

            if (preAuthStatus)
            {
                pRsn->preAuthCache.preAuthTbl[cacheIndex].preAuthenticate = TI_TRUE;
            }

            bssidMac = (uint8_t *)apList->bssidList[apIndex].bssId;
            MAC_COPY (pCandList->CandidateList[candIndex].BSSID, bssidMac);
            candIndex ++;
        }
    }

    /* Add candidates that are in the pre auth cache table, but were not in the list */
    for (apIndex=0; apIndex<pRsn->preAuthCache.entriesNumber && candIndex < PREAUTH_CAND_LIST_MAX_SIZE; apIndex++)
    {
        if (!pRsn->preAuthCache.preAuthTbl[apIndex].preAuthenticate)
        {
            MAC_COPY (pCandList->CandidateList[candIndex].BSSID,
                      pRsn->preAuthCache.preAuthTbl[apIndex].bssId);
            candIndex++;
        }
    }

    pCandList->NumCandidates = candIndex;

    /* Store the number of candidates sent - needed for pre-auth finish event */
    pRsn->numberOfPreAuthCandidates = candIndex;
    /* Start the pre-authentication finish event timer */
    /* If the pre-authentication process is not over by the time it expires - we send an event */
    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION , "Starting PREAUTH timer (%d mSec)\n",pRsn->preAuthTimeout*candIndex);
    tmr_StartTimer (pRsn->hPreAuthTimerWpa2,
                    rsn_preAuthTimerExpire,
                    (void *)pRsn,
                    pRsn->preAuthTimeout * candIndex,
                    TI_FALSE);


    os_memorySet (pRsn->hOs,&tEvent.event_data.pmkid_cand, 0, sizeof(tiwdrv_sta_pmkid_candidate_t));

    tEvent.event_data.pmkid_cand.flags |= WEXT_PMKID_CAND_PREAUTH;
    for (i = 0; i < pCandList->NumCandidates; i++)
    {
        tEvent.event_data.pmkid_cand.index = i;

        MAC_COPY (tEvent.event_data.pmkid_cand.bssid, pCandList->CandidateList[i].BSSID);

        evHandler_HandleEvent(pRsn->hEvHandler,
                           pRsn->pRoleDesc->uNetIfId,
                           TIW_DRV_EV_PMKID_CANDIDATE,
                           (uint8_t *)&tEvent, sizeof(tEvent));
    }

    /* Send PRE-AUTH start event to External Application */
    notifyPreAuthStatus (pRsn, RSN_PRE_AUTH_START);
    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "RSN:  Pre Auth Candidate List with %d entries has been built and sent for ssid  \n", candIndex);

    return;

}

/**
*
* rsn_startPreAuth -
*
* \b Description:
*
* Start pre-authentication on a list of given BSSIDs.
*
* \b ARGS:
*
*  I   - hRsn - RSN SM context  \n
*  I/O - pBssidList - list of BSSIDs that require Pre-Auth \n
*
* \b RETURNS:
*
*  TI_OK if successful, TI_NOK otherwise.
*
* \sa
*/
TI_STATUS rsn_startPreAuth(void * hRsn, TBssidList4PreAuth *pBssidList)
{
    rsn_t       *pRsn;

    if ( (NULL == hRsn) || (NULL == pBssidList) )
    {
        return TI_NOK;
    }

    pRsn = (rsn_t*)hRsn;

    if ((pRsn->externalAuthMode == RSN_EXT_AUTH_MODE_WPA2) ||
            (pRsn->externalAuthMode == RSN_EXT_AUTH_MODE_WPA2PSK)) {

        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, "rsn_startPreAuth \n");
        rsn_buildAndSendPreAuthCandList(pRsn, pBssidList);
    }

    return TI_OK;
}




/**
 *
 * isSiteBanned -
 *
 * \b Description:
 *
 * Returns whether or not the site with the specified Bssid is banned or not.
 *
 * \b ARGS:
 *
 *  I   - hRsn - RSN module context \n
 *  I   - siteBssid - The desired site's bssid \n
 *
 * \b RETURNS:
 *
 *  TI_NOK iff site is banned.
 *
 */
TI_BOOL rsn_isSiteBanned(void * hRsn, TMacAddr siteBssid)
{
    rsn_t * pRsn = (rsn_t *) hRsn;
    rsn_siteBanEntry_t * entry;

    /* Check if site is in the list */
    if ((entry = findBannedSiteAndCleanup(hRsn, siteBssid)) == NULL)
    {
        return TI_FALSE;
    }

    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, ": Site %02X-%02X-%02X-%02X-%02X-%02X found with ban level %d...\n", siteBssid[0], siteBssid[1], siteBssid[2], siteBssid[3], siteBssid[4], siteBssid[5], entry->banLevel);

    return (entry->banLevel == RSN_SITE_BAN_LEVEL_FULL);
}

#endif

void rsn_setPortStatus(uint32_t aRoleId, int32_t aConnected)
{
//    ROCParameters_t *pCmdParams;
//    Command_t cmd;

    HOOK(HOOK_RSN);

    gRsnDB.portStatus = aConnected;

    if (!aConnected)
        return;

    //
    // MCP sends CROC commmand regardless of operation result
    //
//    cmd.cmdID = CMD_CANCEL_REMAIN_ON_CHANNEL;
//    pCmdParams = (ROCParameters_t *)cmd.parameters;
//    pCmdParams->roleID = aRoleId;
//
//    GTRACE(GRP_DRIVER_CC33, "Cancel remain on channel for role %d", aRoleId);

    // Send the command and wait blocking for response.
    // When the below returns, CROC sequence is completed.
//    CME_SendCmd2WlanServices(&cmd);


    // The code in the if statement is based on MCP rsn_reportStatus code
    if (aConnected) // && (TRUE == gRsnDB.waitRsnSuccess))
    {
//        gRsnDB.waitRsnSuccess = FALSE;
//TODO - remove obsolete code
        // From all MCP legacy code only the direct call to legacy FW API should remain.
        // Legacy FW activated SetLinkState which sets WMM and calls the below.
        // In cc33xx FW manages WMM state so setting WMM is irrelevant.
        // Links_SetConnectionState(apLink, LINK_CONNECTION_STATE_CONNECTED);   -> moved to the caller function

        //GTRACE(GRP_CME, "Update RSN state to completed for role ID %d", aRoleId);

//        if (rsnStatus == TI_OK)
//        {
//            encrypt = (TWD_CIPHER_NONE != gRsnDB.unicastSuite);
//            dropBcast = (gRsnDB.mixedMode) ? FALSE : encrypt;

//            udata_SetDataEncryption(pRsn->hUdata, uApLink, bEncrypt, dropBcast, encrypt);
//            {
//                txCtrlParams_SetDataEncryptMode(pUdata->hTxCtrl, link, enabled);
//                {
                      // This field is used to set the protected frame bit in frame control of 802.11 header.
                      // For cc33xx this is set by PMAC
//                    pTxCtrl->aEncryptData[uHlid] = bEncryptMode;
//                }
//                rxData_SetExcludeUnencrypted(pUdata->hRxData, link, bDropBcast, bDropUcast);
//                {
                      // The below fields define how none encrypted received packets are handled.
                      // Default behavior is if enctyption is on, drop.
                      // In any case it should be managed by cc33xx data path
//                    pRxData->aRxLinkInfo[uHlid].bRxDataExcludeUnencryptedBroadcast = bDropBcast;
//                    pRxData->aRxLinkInfo[uHlid].bRxDataExcludeUnencryptedUnicast = bDropUcast;    // = encrypt
//                }
//            }

//            wlanLinks_SetLinkDataEncryption(pRsn->hWlanLinks, uApLink, bEncrypt);
//            {
                    // The state is used for building ARP response - TODO
//                pWlanLinks->aLinks[uHlid].info.bDataEncrypted = bEncrypted;
//            }
//        }
//        else
//        {
//            rsnStatus = (TI_STATUS)STATUS_SECURITY_FAILURE;
//        }
//
//        status = connInfra_reportRsnStatus(pRsn->hConn, (mgmtStatus_e)rsnStatus);
//        // connInfra SM calls the below
//        static TI_STATUS configureFwAfterRsn(connInfra_t *pConn, TI_BOOL bRecovery)
//        {
//            TRoleSta *pRoleSta = (TRoleSta *)pConn->pRoleDesc->hRoleHandle;
//            SetPeerState_t tPeerStateParams;
//            TI_STATUS status;
//            uint32_t uHlid;
//            TI_BOOL   bWme;
//            dot11_ACParameters_t *pWmeAcParam = NULL;
//
            // TODO - check where we have to add functionality
//            status = qosMngr_connect(pConn->hQosMngr, bRecovery);
//            if (status != TI_OK)
//            {
//                 TRACE(pConn->hReport, REPORT_SEVERITY_ERROR, "Infra Conn status=%d, have to return (%d)\n",status,__LINE__);
//                 return status;
//            }
//
//
//            uHlid = roleSta_GetApLinkId(pConn->pRoleDesc->hRoleHandle);
//
//            roleSta_GetPeerWmeParams(pRoleSta, &bWme, &pWmeAcParam);
//
//            /* Send peer state command */
//            tPeerStateParams.HLID = (uint8_t)uHlid;
//            tPeerStateParams.WMM = bWme;
//            tPeerStateParams.peerState = STA_STATE_CONNECTED;
//
//            TWD_SendCmd(pConn->hTWD,
//                        CMD_SET_PEER_STATE,
//                        &tPeerStateParams,
//                        sizeof(tPeerStateParams),
//                        (void *)conn_ConfigHwFinishCb,
//                        pConn);
//            return TI_OK;
//        }

          // No one uses this event in WL8
//        if (rsnStatus == TI_OK)
//        {
//            evHandler_HandleEvent (pRsn->hEvHandler, pRsn->pRoleDesc->uNetIfId, TIW_DRV_EV_AUTH_SUCC, NULL, 0);
//        }

        // TODO the below should be handled in data path
        /* for wpa2, encrypt eapols after port is open */
//        if ( (RSN_EXT_AUTH_MODE_WPA2 == gRsnDB.externalAuthMode) ||
//             (RSN_EXT_AUTH_MODE_WPA2PSK == gRsnDB.externalAuthMode))
//        {
//            udata_SetEapolEncryption(pRsn->hUdata, uApLink, TI_TRUE);
//            {
//                txCtrlParams_SetEapolEncryptionStatus(pUdata->hTxCtrl, link, enabled /* TRUE */);
//                {
                      // The below is used when preparing EAPOL packets for TX.
//                    pTxCtrl->aEncryptEapol[uHlid] = bEapolEncryptionStatus;   /* TRUE */
//                }
//            }
//        }
    }
}

CipherSuite_e rsn_getPairwiseSuite()
{
    HOOK(HOOK_RSN);

    return gRsnDB.unicastSuite;
}

#if 0

/**
 *
 * rsn_banSite -
 *
 * \b Description:
 *
 * Bans the specified site from being associated to for the specified duration.
 * If a ban level of WARNING is given and no previous ban was in effect the
 * warning is marked down but other than that nothing happens. In case a previous
 * warning (or ban of course) is still in effect
 *
 * \b ARGS:
 *
 *  I   - hRsn - RSN module context \n
 *  I   - siteBssid - The desired site's bssid \n
 *  I   - banLevel - The desired level of ban (Warning / Ban)
 *  I   - durationMs - The duration of ban in milliseconds
 *
 * \b RETURNS:
 *
 *  The level of ban (warning / banned).
 *
 */
ERsnSiteBanLevel rsn_banSite(void * hRsn, TMacAddr siteBssid, ERsnSiteBanLevel banLevel, uint32_t durationMs)
{
    rsn_t * pRsn = (rsn_t *) hRsn;
    rsn_siteBanEntry_t * entry;

    /* Try finding the site in the list */
    if ((entry = findBannedSiteAndCleanup(hRsn, siteBssid)) != NULL)
    {
        /* Site found so a previous ban is still in effect */
        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, ": Site %02X-%02X-%02X-%02X-%02X-%02X found and has been set to ban level full!\n", siteBssid[0], siteBssid[1], siteBssid[2], siteBssid[3], siteBssid[4], siteBssid[5]);

        entry->banLevel = RSN_SITE_BAN_LEVEL_FULL;
    }
    else
    {
        /* Site doesn't appear in the list, so find a place to insert it */
        TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, ": Site %02X-%02X-%02X-%02X-%02X-%02X added with ban level %d!\n", siteBssid[0], siteBssid[1], siteBssid[2], siteBssid[3], siteBssid[4], siteBssid[5], banLevel);

        entry = findEntryForInsert (hRsn);

        MAC_COPY (entry->siteBssid, siteBssid);
        entry->banLevel = banLevel;

        pRsn->numOfBannedSites++;
    }

    entry->banStartedMs = os_timeStampMs (pRsn->hOs);
    entry->banDurationMs = durationMs;

    return entry->banLevel;
}


/**
 *
 * findEntryForInsert -
 *
 * \b Description:
 *
 * Returns a place to insert a new banned site.
 *
 * \b ARGS:
 *
 *  I   - hRsn - RSN module context \n
 *
 * \b RETURNS:
 *
 *  A pointer to a suitable site entry.
 *
 */
static rsn_siteBanEntry_t * findEntryForInsert(void * hRsn)
{
    rsn_t * pRsn = (rsn_t *) hRsn;

    /* In the extreme case that the list is full we overwrite an old entry */
    if (pRsn->numOfBannedSites == RSN_MAX_NUMBER_OF_BANNED_SITES)
    {
        TRACE(pRsn->hReport, REPORT_SEVERITY_ERROR, ": No room left to insert new banned site, overwriting old one!\n");

        return &(pRsn->bannedSites[0]);
    }

    return &(pRsn->bannedSites[pRsn->numOfBannedSites]);
}


/**
 *
 * findBannedSiteAndCleanup -
 *
 * \b Description:
 *
 * Searches the banned sites list for the desired site while cleaning up
 * expired sites found along the way.
 *
 * Note that this function might change the structure of the banned sites
 * list so old iterators into the list might be invalidated.
 *
 * \b ARGS:
 *
 *  I   - hRsn - RSN module context \n
 *  I   - siteBssid - The desired site's bssid \n
 *
 * \b RETURNS:
 *
 *  A pointer to the desired site's entry if found,
 *  NULL otherwise.
 *
 */
static rsn_siteBanEntry_t * findBannedSiteAndCleanup(void * hRsn, TMacAddr siteBssid)
{
    rsn_t * pRsn = (rsn_t *) hRsn;
    int iter;

    for (iter = 0; iter < pRsn->numOfBannedSites; iter++)
    {
        /* If this entry has expired we'd like to clean it up */
        if (os_timeStampMs(pRsn->hOs) - pRsn->bannedSites[iter].banStartedMs >= pRsn->bannedSites[iter].banDurationMs)
        {
            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, ": Found expired entry at index %d, cleaning it up...\n", iter);

            /* Replace this entry with the last one */
            pRsn->bannedSites[iter] = pRsn->bannedSites[pRsn->numOfBannedSites - 1];
            pRsn->numOfBannedSites--;

            /* we now repeat the iteration on this entry */
            iter--;

            continue;
        }

        /* Is this the entry for the site we're looking for? */
        if (MAC_EQUAL (siteBssid, pRsn->bannedSites[iter].siteBssid))
        {
            TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, ": Site %02X-%02X-%02X-%02X-%02X-%02X found at index %d!\n", siteBssid[0], siteBssid[1], siteBssid[2], siteBssid[3], siteBssid[4], siteBssid[5], iter);

            return &pRsn->bannedSites[iter];
        }
    }

    /* Entry not found... */
    TRACE(pRsn->hReport, REPORT_SEVERITY_INFORMATION, ": Site %02X-%02X-%02X-%02X-%02X-%02X not found...\n", siteBssid[0], siteBssid[1], siteBssid[2], siteBssid[3], siteBssid[4], siteBssid[5]);

    return NULL;
}

/**
 *
 * rsn_getPortStatus -
 *
 * \b Description:
 *
 * Returns the extrenalSec port status
 *
 * \b ARGS:
 *
 *  pRsn - pointer to RSN module context \n
 *
 * \b RETURNS:
 *
 *  TI_BOOL - the port status True = Open , False = Close
 *
 */
TI_BOOL rsn_getPortStatus(rsn_t *pRsn)
{
    return pRsn->bPortStatus;
}


#endif


