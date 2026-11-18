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
  FILENAME:       cme_tester.c

  DESCRIPTION:    This file simulates CME events for testing CME & supplicant
                  integration.
                  This tester allows defining a sequence of simulated events,
                  including their timing.
                  A list of tests may run in a sequence.

  HISTORY:
                  07/15 Creation
  ----------------------------------------------------------------------------- */


#include "osi_kernel.h"
#include "common.h"
#include "drivers/driver.h"
#include "cme_dispatcher_api.h"
#include "cme_scan_api.h"
#include "cme_supplicant_api.h"
#include "cme_tester.h"
#include "ieee802_11_defs.h"
#include "drv_ti_internal.h"
#ifdef CC33xx
#include "fw_utils.h"
#endif
#include "cme_fw_api.h"
#ifndef CC33XX_NO_CME_TEST

// flows to test
//  auth OPEN
//  o connect/disconnect the same peer
//  o connect/disconnect, different peer each time          23/07/15
//  o connect failure - no auth response                    23/07/15
//  o connect failure - auth response with failure status   23/07/15
//  o connect failure - no assoc response
//  o connect failure - assoc response with no rates IE


//  o add/remove profile
//  o add a number of profiles

// ============================================================================
//      Test configurations definitions
// ============================================================================
#define MAX_TEST_EVENTS     (3)
#define MAX_TESTS           (10)
#define MAX_TEST_NAME_LEN   (50)
#define MAX_TEST_LOOPS      (2)

// Initial peer SSID, BSSID
#define CME_TEST_PEER_SSID       ("shaul_apn")//("jigal_kaka_2.4") // ("guym-mcp8-ap")  ("michal_ap")  ("shaul_apn")
#define CME_TEST_PEER_PASSWORD   ("12345678")
#define CME_TEST_PEER_BSSID      {0xf8, 0x66, 0xf2, 0xc1, 0x59, 0x40}//("123456")
#define CME_TEST_SET_PEER_PARAMS(str, index, value)  // (str[index] = '0' + value)

#define CME_TEST_NEAR_AP_SSID    ("StamApDontConnect")
#define CME_TEST_NEAR_AP_BSSID   ("ABCDEF")

// Defines type of SW master for allocating a packet from MMU.
#define CC33_DRIVER_MMU_ALLOC_MASTER_TYPE (MMU_SW_MASTER_ALLOC_APP_HIGH)

// ============================================================================
//      Test type definitions
// ============================================================================
typedef enum
{
    CME_TEST_HOST_CONNECT_OPEN_CMD,      // May be to last connected peer or a new peer
    CME_TEST_HOST_ADD_OPEN_PROFILE,
    CME_TEST_HOST_CONNECT_WPA_CMD,       // May be to last connected peer or a new peer
    CME_TEST_HOST_CONNECT_WPS_PBC_CMD,
    CME_TEST_HOST_CONNECT_WPS_PIN_CMD,
    CME_TEST_HOST_DISCONNECT_CMD,
    CME_TEST_RX_DEAUTH,
    CME_TEST_RX_DISASSOC,
    CME_TEST_RX_AUTH_RESPONSE,
    CME_TEST_HOST_REMOVE_PROFILE,
    CME_TEST_BEACON_LOSS_NOTIFICATION,

    // AP section
    CME_TEST_RX_AUTH_REQ,

    CME_TEST_SITE_SURVEY_SCAN,
    CME_TEST_DISCONNECT_WHILE_CONNECTING,

    // Roles management
    CME_TEST_HOST_CFG_ROLE,

    CME_TEST_PLACE_HOLDER

} cmeTesterEvents_e;

typedef struct
{
    uint32_t nextEventDelayMS;        // time till next simulated event in msecs
                                    // accuracy depends on ThreadX timer accuracy
    cmeTesterEvents_e event;        // event to simulate
    uint32_t            eventParam;   // event specific info
} cmeTesterEvent_t;


typedef struct
{
    cmeTesterEvent_t       testEvents[MAX_TEST_EVENTS];   // Array of events to be simulated
    cmeTesterConnectResp_e authResponse;
    cmeTesterConnectResp_e assocResponse;
    uint32_t                 numEvents;                     // Actual number of events in the script
    uint32_t                 num2Repeat;                    // Number of times the script should be repeated
    char                   testName[MAX_TEST_NAME_LEN];
} cmeTesterScript_t;

typedef struct
{
    // Number of times peer info was simulated, used for constructing BSSID & SSID
    uint32_t numSimulatedPeers;

    // Number of current script
    uint32_t currentScriptId;

    // Index of current event in the script
    int32_t  currentEventId;

    // Counter of test interations
    uint32_t numScriptIter;

    // Counter of whole test repetitions
    uint32_t numTestCycles;

    // Number of authentication/association timeouts.
    // Test may use the count to send response after a few timeouts.
    uint32_t numAuthTimeouts;
    uint32_t numAssocTimeouts;
    uint32_t maxAuthTimeouts;
    uint32_t maxAssocTimeouts;

    uint32_t testProfileIds[CME_SCAN_MAX_PROFILES];
    uint32_t numAddedProfiles;

    Bool_e blockTest;       // Used to sync test & CME SM

    Bool_e testFastConnection;  // When TRUE, fast policy is tested.
                                // Used to simulate init in fast state in CME SM

} cmeTesterState_t;

// ============================================================================
//      Test globals
// ============================================================================

#ifndef CC33XX_NO_CME_TEST
// Simulation timer object, used for triggering external events
OsiTimer_t gCmeTesterTimer;

cmeTesterState_t gCmeTester;

// SSID counters for simulating different SSID for each itteration
uint32_t gCmeTesterSsidCount;
uint32_t gCmeTesterSsid2ScanRes;

Bool32 gCmeTestScanSuccess;
Bool32 gCmeTesterSetRsnIe;

uint32_t gRolesBitMask;
#endif

// If FALSE, test
#ifndef CC33XX_NO_CME_TEST
extern Bool32 gInitRoleViaSupplicant;
#endif

extern int8_t gUniqueProfileId;

extern Bool_e cmeIsStaSMIdle();
extern Bool_e cmeIsStaConnected();
extern Bool_e cmeIsStaSMSuppManaged();

// select test to run (one at a time)
#ifndef TEST_AP_ROLE
//#define TEST_AUTH_REQ_TIMEOUT
#define TEST_CONNECT_DISCONNECT
//#define TEST_STOP_SCAN
#endif

#ifdef TEST_STOP_SCAN
const cmeTesterScript_t cmeTesterScripts[] =
{
    // Always start with connect disconnect for sanity
    {
        6000, CME_TEST_HOST_CONNECT_OPEN_CMD, 0,
        8000, CME_TEST_HOST_DISCONNECT_CMD, 0,
        1000, CME_TEST_PLACE_HOLDER, 0,
        CME_TEST_RESP_OK,                   // Auth request response
        CME_TEST_RESP_OK,                   // Assoc request response
        2,                                  // Number of events in the test
        4,                                  // Number of iterations to run
        "Connect/disconnect open auth OK"
    },
    {
        6000, CME_TEST_HOST_CONNECT_OPEN_CMD, 0,
        1000, CME_TEST_HOST_DISCONNECT_CMD, 0,
        1000, CME_TEST_PLACE_HOLDER, 0,
        CME_TEST_RESP_OK,                   // Auth request response
        CME_TEST_RESP_OK,                   // Assoc request response
        2,                                  // Number of events in the test
        4,                                  // Number of iterations to run
        "Stop active one shot scan"
    },
    {
        6000, CME_TEST_HOST_CONNECT_OPEN_CMD, 0,
        8000, CME_TEST_HOST_DISCONNECT_CMD, 0,
        1000, CME_TEST_PLACE_HOLDER, 0,
        CME_TEST_RESP_OK,                   // Auth request response
        CME_TEST_RESP_OK,                   // Assoc request response
        2,                                  // Number of events in the test
        4,                                  // Number of iterations to run
        "Stop active periodic scan"
    }
};
#endif  // TEST_STOP_SCAN

#ifdef TEST_AUTH_REQ_TIMEOUT
const cmeTesterScript_t cmeTesterScripts[] =
{
    {
        6000, CME_TEST_HOST_CONNECT_OPEN_CMD, 0,
        8000, CME_TEST_HOST_DISCONNECT_CMD, 0,
        1000, CME_TEST_PLACE_HOLDER, 0,
        CME_TEST_RESP_OK,                   // Auth request response
        CME_TEST_RESP_OK,                   // Assoc request response
        2,                                  // Number of events in the test
        5,                                 // Number of iterations to run
        "Connect/disconnect open auth OK"
    },
    {
        6000, CME_TEST_HOST_CONNECT_OPEN_CMD, 10,
        30, CME_TEST_RX_AUTH_RESPONSE, 0,
        8000, CME_TEST_HOST_DISCONNECT_CMD, 0,
        CME_TEST_RESP_OK,                 // Auth request response
        CME_TEST_RESP_OK,                   // Assoc request response
        3,                                  // Number of events in the test
        1,                                  // Number of iterations to run
        "Auth resp. while waiting auth req. exchange"
    },
    {
        6000, CME_TEST_HOST_CONNECT_OPEN_CMD, 10,
        8000, CME_TEST_HOST_DISCONNECT_CMD, 0,
        1000, CME_TEST_PLACE_HOLDER, 0,
        CME_TEST_RESP_NONE,                 // Auth request response
        CME_TEST_RESP_OK,                   // Assoc request response
        2,                                  // Number of events in the test
        1,                                  // Number of iterations to run
        "No Auth response"
    }
};
#endif  // TEST_AUTH_REQ_TIMEOUT

#ifdef TEST_CONNECT_DISCONNECT
const cmeTesterScript_t cmeTesterScripts[] =
{
//        {
//            2000, CME_TEST_DISCONNECT_WHILE_CONNECTING, 0,
//            6000, CME_TEST_PLACE_HOLDER, 0,
//            CME_TEST_RESP_OK,
//            CME_TEST_RESP_OK,
//            2,
//            1,
//            "Disconnect while connecting"
//        },
//        {
//            3000, CME_TEST_SITE_SURVEY_SCAN, 0,
//            6000, CME_TEST_PLACE_HOLDER, 0,
//            //            9000, CME_TEST_RX_DEAUTH, 0,
//            CME_TEST_RESP_OK,                   // Auth request response
//            CME_TEST_RESP_OK,                   // Assoc request response
//            2,                                  // Number of events in the test
//            1,                                  // Number of iterations to run
//            "Site survey scan"
//        },
//        {
//            8000, CME_TEST_HOST_ADD_OPEN_PROFILE, 4,   // number of profiles to add
//            30000, CME_TEST_RX_DEAUTH, 0,
//            CME_TEST_RESP_OK,                   // Auth request response
//            CME_TEST_RESP_OK,                   // Assoc request response
//            2,                                  // Number of events in the test
//            1,                                 // Number of iterations to run
//            "Add profiles"
//        },
        {
            6000, CME_TEST_HOST_CONNECT_OPEN_CMD, 0,
            8000, CME_TEST_HOST_DISCONNECT_CMD, 0,
            1000, CME_TEST_PLACE_HOLDER, 0,     // remain connected forever
            CME_TEST_RESP_OK,                   // Auth request response
            CME_TEST_RESP_OK,                   // Assoc request response
            2,                                  // Number of events in the test
            32,                                 // Number of iterations to run
            "Connect/disconnect open"
        }
//        {
//            8000, CME_TEST_HOST_CONNECT_WPA_CMD, 0,
//            1000, CME_TEST_HOST_DISCONNECT_CMD, 0,
//            CME_TEST_RESP_OK,                   // Auth request response
//            CME_TEST_RESP_OK,                   // Assoc request response
//            2,                                  // Number of events in the test
//            10,                                 // Number of iterations to run
//            "Connect/disconnect wpa"
//        },
//        {
//            9000, CME_TEST_HOST_CONNECT_OPEN_CMD, 0,
//            12000, CME_TEST_HOST_DISCONNECT_CMD, 0,
//            CME_TEST_RESP_NONE,          // Auth request response
//            CME_TEST_RESP_OK,                   // Assoc request response
//            2,                                  // Number of events in the test
//            1,                                  // Number of iterations to run
//            "Connect/disconnect open, auth timeout"
//        },
//        {
//            8000, CME_TEST_HOST_CONNECT_OPEN_CMD, 0,
//            9000, CME_TEST_HOST_DISCONNECT_CMD, 0,
//            CME_TEST_RESP_NONE,                 // Auth request response
//            CME_TEST_RESP_OK,                   // Assoc request response
//            2,                                  // Number of events in the test
//            1,                                  // Number of iterations to run
//            "Connect auth timeout"
//        }
};// Tests DB
#endif // TEST_CONNECT_DISCONNECT

#ifdef TEST_AP_ROLE
const cmeTesterScript_t cmeTesterScripts[] =
{
        {
            2000, CME_TEST_RX_AUTH_REQ, 0,
            1000, CME_TEST_PLACE_HOLDER, 0,
            1000, CME_TEST_PLACE_HOLDER, 0,
            CME_TEST_RESP_NONE,                 // Auth request response
            CME_TEST_RESP_OK,                   // Assoc request response
            1,                                  // Number of events in the test
            1,                                  // Number of iterations to run
            "Send auth req to AP"
        }
};
#endif // TEST_AP_ROLE


#ifdef CC33XX_NO_CME_TEST
#else
// ----------------------------------------------------------------------------
static void sendOpenConnectCmd(uint32_t aSimNum, Bool32 aSetBssid)
{
    char   ssidStr[] = CME_TEST_PEER_SSID;
    uint32_t ssidLen = strlen(CME_TEST_PEER_SSID);
    uint32_t allocLen = sizeof(CMEWlanConnectCommon_t) + ssidLen;
    CMEWlanConnectCommon_t *pCmd = mem_Zalloc_glx(allocLen);

    ASSERT_GENERAL(NULL != pCmd);

    pCmd->SecType = SL_SEC_TYPE_OPEN;
    pCmd->PasswordLen = 0;
    pCmd->SsidLen = ssidLen;
    //ssidStr[8] = '0' + aSimNum;
    CME_TEST_SET_PEER_PARAMS(ssidStr, 8, aSimNum);
    memcpy(SSID_STRING(pCmd), ssidStr, ssidLen);

    if (FALSE == aSetBssid)
    {
        GTRACE(GRP_CME, "CME tester: connect command, SSID %s", ssidStr);
        IRQ_UtilZeroMacAddress(pCmd->Bssid);
    }
    else
    {        

        uint8_t bssidStr[6] = CME_TEST_PEER_BSSID;
        //bssidStr[0] = '0' + aSimNum;
        CME_TEST_SET_PEER_PARAMS(bssidStr, 0, aSimNum);
        IRQ_UtilCopyMacAddress((uint8_t *)bssidStr, pCmd->Bssid);

        GTRACE(GRP_CME, "CME tester: connect command, SSID %s, BSSID %s", ssidStr, bssidStr);
    }

    CME_WlanConnect(pCmd, FALSE);
}

// ----------------------------------------------------------------------------
static void sendWpsPbcConnectCmd()
{
    uint32_t allocLen = sizeof(CMEWlanConnectCommon_t);
    CMEWlanConnectCommon_t *pCmd = mem_Zalloc_glx(allocLen);

    ASSERT_GENERAL(NULL != pCmd);

    pCmd->SecType = SL_SEC_TYPE_WPS_PBC;
    pCmd->PasswordLen = 0;
    pCmd->SsidLen = 0;

    CME_WlanConnect(pCmd, FALSE);
}

// ----------------------------------------------------------------------------
static void sendWpaConnectCmd(uint32_t aSimNum, Bool32 aSetBssid)
{
    char   ssidStr[] = CME_TEST_PEER_SSID;
    char   passwordStr[] = CME_TEST_PEER_PASSWORD;
    uint32_t ssidLen = strlen(CME_TEST_PEER_SSID);
    uint32_t passwordLen = strlen(CME_TEST_PEER_PASSWORD);
    uint32_t allocLen = sizeof(CMEWlanConnectCommon_t) + ssidLen + passwordLen;
    CMEWlanConnectCommon_t *pCmd = mem_Zalloc_glx(allocLen);

    ASSERT_GENERAL(NULL != pCmd);

    pCmd->SecType = SL_SEC_TYPE_WPA_WPA2;
    pCmd->PasswordLen = passwordLen;
    pCmd->SsidLen = ssidLen;
    //ssidStr[8] = '0' + aSimNum;
    CME_TEST_SET_PEER_PARAMS(ssidStr, 8, aSimNum);
    memcpy(SSID_STRING(pCmd), ssidStr, ssidLen);
    memcpy(PASSWORD_STRING(pCmd), passwordStr, passwordLen);

    if (FALSE == aSetBssid)
    {
        GTRACE(GRP_CME, "CME tester: connect command, SSID %s", ssidStr);
        IRQ_UtilZeroMacAddress(pCmd->Bssid);
    }
    else
    {
        uint8_t bssidStr[6] = CME_TEST_PEER_BSSID;

        //bssidStr[0] = '0' + aSimNum;
        CME_TEST_SET_PEER_PARAMS(bssidStr, 0, aSimNum);
        IRQ_UtilCopyMacAddress((uint8_t *)bssidStr, pCmd->Bssid);

        GTRACE(GRP_CME, "CME tester: connect command, SSID %s, BSSID %s", ssidStr, bssidStr);
    }

    CME_WlanConnect(pCmd, FALSE);
}

// ----------------------------------------------------------------------------
static void sendOpenDisconnectCmd()
{
    GTRACE(GRP_CME, "CME tester: disconnect command");

    CME_WlanDisconnect(FALSE);
}

// ----------------------------------------------------------------------------
static void sendAddOpenProfileCmd(uint32_t aNumProfiles2add, Bool32 aSetBssid)
{
    char   ssidStr[] = CME_TEST_PEER_SSID;
    uint32_t i;
    uint32_t ssidLen = strlen(CME_TEST_PEER_SSID);
    uint32_t allocLen = sizeof(CMEWlanAddGetProfile_t) + ssidLen;
    CMEWlanAddGetProfile_t *pCmd = mem_Zalloc_glx(allocLen);

    ASSERT_GENERAL(NULL != pCmd);

    pCmd->SecType = SL_SEC_TYPE_OPEN;
    pCmd->PasswordLen = 0;
    pCmd->SsidLen = ssidLen;

    for (i=0 ; i<aNumProfiles2add ; ++i)
    {
        // Leave first profile as is and increment a counter for the rest
        // so we have different SSIDs
        if (0 < i)
        {
            ssidStr[ssidLen-1] = '0' + i;
        }
        memcpy(PROFILE_SSID_STRING(pCmd), ssidStr, ssidLen);

        pCmd->Priority = i;

        if (FALSE == aSetBssid)
        {
            GTRACE(GRP_CME, "CME tester: add open profile command, SSID %s", ssidStr);
            IRQ_UtilZeroMacAddress(pCmd->Bssid);
        }
        else
        {

            uint8_t bssidStr[6] = CME_TEST_PEER_BSSID;
            bssidStr[0] += i;
            IRQ_UtilCopyMacAddress((uint8_t *)bssidStr, pCmd->Bssid);

            GTRACE(GRP_CME, "CME tester: connect command, SSID %s, BSSID %s", ssidStr, bssidStr);
        }

        CME_AddProfile(pCmd);
    }
}

// ----------------------------------------------------------------------------
static void sendRemoveProfileCmd()
{
    uint32_t profileId = gCmeTester.testProfileIds[gCmeTester.numAddedProfiles];

    CME_RemoveProfile(profileId);
}

// ----------------------------------------------------------------------------
static void notifyDeauthReceived()
{
    struct ieee80211_mgmt   *pDeauth;
    CC33_FrameRxDesc_t      *pDesc;
    uint32_t len = WLAN_HDR_LEN + sizeof(pDeauth->u.deauth);
    uint32_t allocSize;
    uint8_t  txDescId;
    uint8_t  bssidStr[MAC_ADDR_LEN] = CME_TEST_PEER_BSSID;
    int32_t  rc = 0;

    GTRACE(GRP_CME, "CME tester: simulate RX deauth packet");

    // Use packet RAM
    allocSize = CC33_DRV_MNG_PACKET_MIN_SIZE + len;
    rc = TxcAllocateNoWaitRequest(
            CC33_DRIVER_MMU_ALLOC_MASTER_TYPE,  // [in ] CC33xx master ID
            allocSize,                          // [in ] Allocation size, in bytes, for the entire thing
            MMU_ALLOC_OPCODE_ALLOCATE,          // [in ] Opcode = ALLOC (as opposed to REALLOC or DEALLOC)
            MMU_POOL_TYPE_MNGMT,                // [in ] Pool ID from which to allocate (TX/RX/MNG)
            &txDescId,                          // [out] -> CC33xx virtual descriptor index
            0);                                 // [in ] Reallocated descriptor index - irrelevant for ALLOCATE

    // If allocation failed, return with error indication
    if (0 != rc)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: failed to allocate %d bytes for management packet", allocSize);
        return;
    }

    // ------------------------------------------------------------------------
    // Allocation succeeded
    //  o Set packet information on descriptor
    //  o Construct payload
    // ------------------------------------------------------------------------
    pDesc = (struct CC33_FrameRxDesc_s *)MMU_GET_VIRTUAL_ADDR_FROM_DESC(txDescId);
    pDesc->link_role.role_id = 0;     // STA role ID
    pDesc->length_type.length = len;
    pDesc->address = (uint32_t)((uint8_t *)pDesc + CC33_DRV_PAYLOAD_START_OFFSET);

    pDeauth = (struct ieee80211_mgmt *)pDesc->address;

    // Set the packet type on header (as we don't set the 802.11 header)
    pDeauth->frame_control = FRAME_TYPE_DEAUTHENTICATION;

    pDeauth->u.deauth.reason_code = 1;

    CME_TEST_SET_PEER_PARAMS(bssidStr, 0, gCmeTesterSsid2ScanRes);
    IRQ_UtilCopyMacAddress((uint8_t *)bssidStr, pDeauth->bssid);
    IRQ_UtilCopyMacAddress((uint8_t *)bssidStr, pDeauth->sa);

    CME_NotifyRxMngPack(txDescId, 0);
}

// ----------------------------------------------------------------------------
static void notifyAuthResponseReceived()
{
    struct ieee80211_mgmt   *pPack;
    CC33_FrameRxDesc_t      *pDesc;
    uint32_t len = WLAN_HDR_LEN + sizeof(pPack->u.auth);
    uint32_t allocSize;
    uint8_t  txDescId;
    uint8_t  bssid[MAC_ADDR_LEN] = CME_TEST_PEER_BSSID;
    int32_t  rc = 0;

    GTRACE(GRP_CME, "CME tester: simulate RX auth response packet");

    // Use packet RAM
    allocSize = CC33_DRV_MNG_PACKET_MIN_SIZE + len;
    rc = TxcAllocateNoWaitRequest(
            CC33_DRIVER_MMU_ALLOC_MASTER_TYPE,  // [in ] CC33xx master ID
            allocSize,                          // [in ] Allocation size, in bytes, for the entire thing
            MMU_ALLOC_OPCODE_ALLOCATE,          // [in ] Opcode = ALLOC (as opposed to REALLOC or DEALLOC)
            MMU_POOL_TYPE_MNGMT,                // [in ] Pool ID from which to allocate (TX/RX/MNG)
            &txDescId,                          // [out] -> CC33xx virtual descriptor index
            0);                                 // [in ] Reallocated descriptor index - irrelevant for ALLOCATE

    // If allocation failed, return with error indication
    if (0 != rc)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: failed to allocate %d bytes for management packet", allocSize);
        return;
    }

    // ------------------------------------------------------------------------
    // Allocation succeeded
    //  o Set packet information on descriptor
    //  o Construct payload
    // ------------------------------------------------------------------------
    pDesc = (struct CC33_FrameRxDesc_s *)MMU_GET_VIRTUAL_ADDR_FROM_DESC(txDescId);
    pDesc->link_role.role_id = 0; // STA ID
    pDesc->length_type.length = len;
    pDesc->address = (uint32_t)((uint8_t *)pDesc + CC33_DRV_PAYLOAD_START_OFFSET);

    pPack = (struct ieee80211_mgmt *)pDesc->address;

    // Set the packet type on header (as we don't set the 802.11 header)
    pPack->frame_control = FRAME_TYPE_AUTHENTICATION;
    pPack->u.auth.auth_transaction = 2;
    pPack->u.auth.auth_alg = 0;     // OPEN
    pPack->u.auth.status_code = 0;

    IRQ_UtilCopyMacAddress(bssid, pPack->bssid);
    IRQ_UtilCopyMacAddress(bssid, pPack->sa);

    CME_NotifyRxMngPack(txDescId, 0);
}

// ----------------------------------------------------------------------------
static void notifyAuthReqReceived()
{
    struct ieee80211_mgmt   *pPack;
    CC33_FrameRxDesc_t      *pDesc;
    uint32_t len = WLAN_HDR_LEN + sizeof(pPack->u.auth);
    uint32_t allocSize;
    uint8_t  txDescId;
    uint8_t  bssid[MAC_ADDR_LEN];
    int32_t  rc = 0;

    GTRACE(GRP_CME, "CME tester: simulate RX auth request packet");

    Roles_allocateMacAddress(ROLE_AP, bssid);

    // Use packet RAM
    allocSize = CC33_DRV_MNG_PACKET_MIN_SIZE + len;
    rc = TxcAllocateNoWaitRequest(
            CC33_DRIVER_MMU_ALLOC_MASTER_TYPE,  // [in ] CC33xx master ID
            allocSize,                          // [in ] Allocation size, in bytes, for the entire thing
            MMU_ALLOC_OPCODE_ALLOCATE,          // [in ] Opcode = ALLOC (as opposed to REALLOC or DEALLOC)
            MMU_POOL_TYPE_MNGMT,                // [in ] Pool ID from which to allocate (TX/RX/MNG)
            &txDescId,                          // [out] -> CC33xx virtual descriptor index
            0);                                 // [in ] Reallocated descriptor index - irrelevant for ALLOCATE

    // If allocation failed, return with error indication
    if (0 != rc)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: failed to allocate %d bytes for management packet", allocSize);
        return;
    }

    // ------------------------------------------------------------------------
    // Allocation succeeded
    //  o Set packet information on descriptor
    //  o Construct payload
    // ------------------------------------------------------------------------
    pDesc = (struct CC33_FrameRxDesc_s *)MMU_GET_VIRTUAL_ADDR_FROM_DESC(txDescId);
    pDesc->link_role.role_id = 1; // AP ID
    pDesc->length_type.length = len;
    pDesc->address = (uint32_t)((uint8_t *)pDesc + CC33_DRV_PAYLOAD_START_OFFSET);

    pPack = (struct ieee80211_mgmt *)pDesc->address;

    // Set the packet type on header (as we don't set the 802.11 header)
    pPack->frame_control = FRAME_TYPE_AUTHENTICATION;
    pPack->u.auth.auth_transaction = 1;
    pPack->u.auth.auth_alg = 0;     // OPEN
    pPack->u.auth.status_code = 0;

    IRQ_UtilCopyMacAddress((uint8_t *)bssid, pPack->bssid);
    IRQ_UtilCopyMacAddress((uint8_t *)bssid, pPack->da);

    CME_NotifyRxMngPack(txDescId, 0);
}

// ----------------------------------------------------------------------------
static void cmeTestRunEvent()
{
    const cmeTesterEvent_t *pEvent;

    pEvent = &cmeTesterScripts[gCmeTester.currentScriptId].testEvents[gCmeTester.currentEventId];

    //
    // Since test is timer driven it is not synced with STA state
    //

    // Check whether connect command can be executed
    if (pEvent->event <= CME_TEST_HOST_CONNECT_WPS_PIN_CMD)
    {
        if ( (FALSE == cmeIsStaSMIdle()) && (FALSE == cmeIsStaSMSuppManaged()) )
        {
            GTRACE(GRP_CME, "Connect command, waiting for STA to be idle");
            ASSERT_GENERAL(OSI_OK == osi_TimerStart(&gCmeTesterTimer, 2000, OSI_ONE_SHOT_TIMER));
            gCmeTester.blockTest = 1;
            return;
        }
    }

    // Check whether disconnect command can be executed
#ifndef TEST_STOP_SCAN
    if ( (CME_TEST_HOST_DISCONNECT_CMD <= pEvent->event) &&
         (pEvent->event <= CME_TEST_RX_DISASSOC) )
    {
        if (FALSE == cmeIsStaConnected())
        {
            GTRACE(GRP_CME, "Disonnect command, waiting for STA to be connected");
            ASSERT_GENERAL(OSI_OK == osi_TimerStart(&gCmeTesterTimer, 2000, OSI_ONE_SHOT_TIMER));
            gCmeTester.blockTest = 1;
            return;
        }
    }
#endif

    switch (pEvent->event)
    {
        case CME_TEST_HOST_CONNECT_OPEN_CMD:
#ifdef TEST_AUTH_REQ_TIMEOUT
            gCmeTester.maxAuthTimeouts = pEvent->eventParam;
            GTRACE(GRP_CME, "Setting max auth retries to %d", pEvent->eventParam);
#endif
#ifdef TEST_ASSOC_REQ_TIMEOUT
            gCmeTester.maxAssocTimeouts = pEvent->eventParam;
#endif
            sendOpenConnectCmd(gCmeTesterSsidCount, FALSE);
            gCmeTesterSsid2ScanRes = gCmeTesterSsidCount;
            gCmeTesterSetRsnIe = FALSE;
            ++gCmeTesterSsidCount;
            break;

        case CME_TEST_HOST_CONNECT_WPA_CMD:
            sendWpaConnectCmd(gCmeTesterSsidCount, FALSE);
            gCmeTesterSsid2ScanRes = gCmeTesterSsidCount;
            gCmeTesterSetRsnIe = TRUE;
            ++gCmeTesterSsidCount;
            break;

        case CME_TEST_HOST_CONNECT_WPS_PBC_CMD:
            sendWpsPbcConnectCmd();
            break;

        case CME_TEST_HOST_CONNECT_WPS_PIN_CMD:
            break;

        case CME_TEST_HOST_DISCONNECT_CMD:
            sendOpenDisconnectCmd();
            break;

        case CME_TEST_HOST_ADD_OPEN_PROFILE:
            {
                SlWlanPolicySetGet_t policy;

                gCmeTester.testFastConnection = 0;
                policy.PolicyOption = SL_CONNECTION_POLICY(1, /*Auto*/
                                              gCmeTester.testFastConnection, /*Fast */
                                              0, /*Open*/
                                              0, /*anyP2P */
                                              0 /*autoProvisioning */);

                CME_SetConnPolicy(policy);
                sendAddOpenProfileCmd(pEvent->eventParam, FALSE);
            }
            break;

        case CME_TEST_HOST_REMOVE_PROFILE:
            sendRemoveProfileCmd();
            break;

        case CME_TEST_BEACON_LOSS_NOTIFICATION:
            break;

        case CME_TEST_RX_DEAUTH:
            notifyDeauthReceived();
            break;

        case CME_TEST_RX_DISASSOC:
            break;

        case CME_TEST_RX_AUTH_RESPONSE:
            notifyAuthResponseReceived();
            break;

        case CME_TEST_RX_AUTH_REQ:
            notifyAuthReqReceived();
            break;

        case CME_TEST_SITE_SURVEY_SCAN:
            {
                SlWlanGetNetworkListCommand_t cmd;

                cmd.Count = 5;  // maximal number of results
                cmd.Index = 0;  // starting index
                sl_cmd_wlan_scan_res_get((uint8_t *)&cmd);
            }
            break;

        case CME_TEST_PLACE_HOLDER:
            // this place holder just increments the script & iteration counters
            // in order to align test logs with application logs.
            break;

        case CME_TEST_DISCONNECT_WHILE_CONNECTING:
            sendOpenConnectCmd(gCmeTesterSsidCount, FALSE);
            sendOpenDisconnectCmd();
            break;

        case CME_TEST_HOST_CFG_ROLE:
            gRolesBitMask = pEvent->eventParam;
            GTRACE(GRP_CME, "Set roles BM to %d", gRolesBitMask);
            break;

        default:
            ASSERT_GENERAL(0);
    }
}

// ----------------------------------------------------------------------------
static void cmeTestRestart()
{
    gCmeTester.numSimulatedPeers = 0;
    gCmeTester.currentScriptId = 0;
    gCmeTester.currentEventId = 0;
    gCmeTester.numScriptIter = 0;
    gCmeTesterSsidCount = 0;
    gCmeTesterSsid2ScanRes = 0;
}

// ----------------------------------------------------------------------------
static void cmeTestTimerEvents(OsiTimer_t* apTimer)
{
    const cmeTesterEvent_t *pEvent;
    uint32_t numTests = sizeof(cmeTesterScripts)/sizeof(cmeTesterScript_t);

    ASSERT_GENERAL(numTests <= MAX_TESTS);

    if (gCmeTester.blockTest)
    {
        gCmeTester.blockTest = 0;

        // Hanlde current event
        cmeTestRunEvent();

        if (!gCmeTester.blockTest)
        {
            // Arm timer for next event
            pEvent = &cmeTesterScripts[gCmeTester.currentScriptId].testEvents[gCmeTester.currentEventId];
            GTRACE(GRP_CME, "CME tester: Start timer for next event within %d msecs", pEvent->nextEventDelayMS);
            ASSERT_GENERAL(OSI_OK == osi_TimerStart(&gCmeTesterTimer, pEvent->nextEventDelayMS, OSI_ONE_SHOT_TIMER));
        }

        return;
    }

    //
    // Update all counters for the new event
    //
    // If script has completed, move to next one or end test
    ++gCmeTester.currentEventId;
    if (gCmeTester.currentEventId == cmeTesterScripts[gCmeTester.currentScriptId].numEvents)
    {
        GTRACE(GRP_CME, "Completed iteration %d of script %d", gCmeTester.numScriptIter, gCmeTester.currentScriptId);
        gCmeTester.currentEventId = 0;
        ++gCmeTester.numScriptIter;

        if (gCmeTester.numScriptIter == cmeTesterScripts[gCmeTester.currentScriptId].num2Repeat)
        {
            GTRACE(GRP_CME, "Completed last iteration of script %d, # STA connect/disconnect %d/%d",
                             gCmeTester.currentScriptId, gNumStaConnection, gNumStaDisconnection);
            gCmeTester.numScriptIter = 0;
            ++gCmeTester.currentScriptId;
            gCmeTesterSsidCount = 0;

            if (gCmeTester.currentScriptId == numTests)
            {
                GTRACE(GRP_CME, "===== CME tester completed a full cycle, %d scripts =====", gCmeTester.currentScriptId);
                if (gCmeTester.numTestCycles)
                {
                    --gCmeTester.numTestCycles;
                    cmeTestRestart();
                }
                else
                {
                    GTRACE(GRP_CME, "===== CME tester completed all cycles, exiting =====");
                    return;
                }
            }
        }
    }

    //
    // Hanlde the new event
    //
    if (0 == gCmeTester.currentEventId)
    {
        GTRACE(GRP_CME, "===== Start a new CME tester script (%s %d/%d) interation (%d/%d) =====",
                        (char *)cmeTesterScripts[gCmeTester.currentScriptId].testName,
                        gCmeTester.currentScriptId+1,
                        numTests,
                        gCmeTester.numScriptIter+1, cmeTesterScripts[gCmeTester.currentScriptId].num2Repeat);
    }

    GTRACE(GRP_CME, "CME tester: gCmeTester.currentScriptId %d gCmeTester.numScriptIter %d gCmeTester.currentEventId %d",
                    gCmeTester.currentScriptId, gCmeTester.numScriptIter, gCmeTester.currentEventId);

    // Hanlde current event
    cmeTestRunEvent();

    // Arm timer for next event
    pEvent = &cmeTesterScripts[gCmeTester.currentScriptId].testEvents[gCmeTester.currentEventId];
    GTRACE(GRP_CME, "CME tester: Start timer for next event within %d msecs", pEvent->nextEventDelayMS);
    ASSERT_GENERAL(OSI_OK == osi_TimerStart(&gCmeTesterTimer, pEvent->nextEventDelayMS, OSI_ONE_SHOT_TIMER));
}

// ----------------------------------------------------------------------------
void cmeTestBuildScanResult(cmeScanSharedInfo_t *apSharedInfo, EScanRequestType aType)
{
    struct wpa_scan_res *apScanResult;
    uint8_t *pNextIe;
    uint32_t len, ieLen = 0;
    char   ssidStr[] = CME_TEST_PEER_SSID;
    uint8_t   bssidStr[6] = CME_TEST_PEER_BSSID;

    // Build site survey results
    if ( (aType == SCAN_REQUEST_SURVEY_ONE_SHOT_OS_SCAN) ||
         (aType == SCAN_REQUEST_SURVEY_ONE_SHOT_APP_SCAN) )
    {
        apScanResult = (struct wpa_scan_res *)apSharedInfo->mpDigestScanResults;
        pNextIe = (uint8_t *)apScanResult;

        apScanResult->caps = IEEE80211_CAP_ESS;
        pNextIe += sizeof(struct wpa_scan_res);

        // Set SSID
        pNextIe[0] = 0;   // WLAN_EID_SSID
        pNextIe[1] = strlen(CME_TEST_NEAR_AP_SSID);
        //ssidStr[8] = '0' + scanIndex;
        CME_TEST_SET_PEER_PARAMS(ssidStr, 8, scanIndex);
        memcpy(&pNextIe[2], CME_TEST_NEAR_AP_SSID, pNextIe[1]);

        // Set BSSID
        memcpy(apScanResult->bssid, CME_TEST_NEAR_AP_BSSID, 6);

        apSharedInfo->mNumDigestResultsFound = 1;

        GTRACE(GRP_CME,  "CME tester faked digest scan result SSID %s BSSID %s", CME_TEST_NEAR_AP_SSID, CME_TEST_NEAR_AP_BSSID);
        return;
    }

    apScanResult = &apSharedInfo->mpCandidateScanResults->mScanResult;

    // Build connection scan results
    apScanResult->caps = IEEE80211_CAP_ESS;
    if (TRUE == gCmeTesterSetRsnIe)
        apScanResult->caps |= IEEE80211_CAP_PRIVACY;
    pNextIe = apSharedInfo->mpCandidateScanResults->mInfoElements;

    if (FALSE == gCmeTestScanSuccess)
    {
        gCmeTestScanSuccess = TRUE;
    }

    // Simulate SSID
    pNextIe[0] = 0;   // WLAN_EID_SSID
    pNextIe[1] = strlen(CME_TEST_PEER_SSID);
    CME_TEST_SET_PEER_PARAMS(ssidStr, 8, ++gCmeTesterSsid2ScanRes);
    memcpy(&pNextIe[2], ssidStr, pNextIe[1]);
    len = pNextIe[1] + 2;
    ieLen += len;
    pNextIe += len;
    GTRACE(GRP_CME, "CME tester faked SSID IE, len %d", len-2);

    // Simulates rates IE
    pNextIe[0] = WLAN_EID_SUPP_RATES;
    pNextIe[1] = 4;
    pNextIe[2] = 0x82;
    pNextIe[3] = 0x84;
    pNextIe[4] = 0x8b;
    pNextIe[5] = 0x96;
    len = pNextIe[1] + 2;
    ieLen += len;
    pNextIe += len;
    GTRACE(GRP_CME, "CME tester faked rates IE, len %d", len-2);

    // Simulates ERP info
    pNextIe[0] = WLAN_EID_ERP_INFO;
    pNextIe[1] = 1;
    pNextIe[2] = 0;     // Non-ERP not present & not barker mode preamble
    len = pNextIe[1] + 2;
    ieLen += len;
    pNextIe += len;
    GTRACE(GRP_CME, "CME tester faked ERP info IE, len %d", len-2);

    // Simulates extended rates IE
    pNextIe[0] = WLAN_EID_EXT_SUPP_RATES;
    pNextIe[1] = 8;
    pNextIe[2] = 0xc;
    pNextIe[3] = 0x12;
    pNextIe[4] = 0x18;
    pNextIe[5] = 0x24;
    pNextIe[6] = 0x30;
    pNextIe[7] = 0x48;
    pNextIe[8] = 0x60;
    pNextIe[9] = 0x6c;
    len = pNextIe[1] + 2;
    ieLen += len;
    pNextIe += len;
    GTRACE(GRP_CME, "CME tester faked ext rates IE, len %d", len-2);

    // Simulates RSN IE
    if (TRUE == gCmeTesterSetRsnIe)
    {
        pNextIe[0] = WLAN_EID_RSN;
        pNextIe[1] = 20;
        pNextIe[2] = 1;
        pNextIe[3] = 0;
        pNextIe[4] = 0;
        pNextIe[5] = 0xf;
        pNextIe[6] = 0xac;
        pNextIe[7] = 4;
        pNextIe[8] = 1;
        pNextIe[9] = 0;
        pNextIe[10] = 0;
        pNextIe[11] = 0xf;
        pNextIe[12] = 0xac;
        pNextIe[13] = 4;
        pNextIe[14] = 1;
        pNextIe[15] = 0;
        pNextIe[16] = 0;
        pNextIe[17] = 0xf;
        pNextIe[18] = 0xac;
        pNextIe[19] = 2;
        pNextIe[20] = 0xc;
        pNextIe[21] = 0;

        len = pNextIe[1] + 2;
        ieLen += len;
        pNextIe += len;

        GTRACE(GRP_CME, "CME tester faked RSN IE, len %d", len-2);
    }

    // Simulates HT capabilities
    memset(pNextIe, 0, 28);
    pNextIe[0] = WLAN_EID_HT_CAP;
    pNextIe[1] = 26;
    pNextIe[2] = 0x2c;  // taken from Sniffer
    pNextIe[3] = 0x01;
    pNextIe[4] = 0x03;
    pNextIe[5] = 0xff;
    len = pNextIe[1] + 2;
    ieLen += len;
    pNextIe += len;
    GTRACE(GRP_CME, "CME tester faked HT capabilities IE, len %d", len-2);

    // Simulates HT information
    memset(pNextIe, 0, 24);
    pNextIe[0] = WLAN_EID_HT_OPERATION;
    pNextIe[1] = 22;
    pNextIe[2] = 6;  // primary channel
    len = pNextIe[1] + 2;
    ieLen += len;
    pNextIe += len;
    GTRACE(GRP_CME, "CME tester faked HT information IE, len %d", len-2);

    apScanResult->ie_len = ieLen;
    apScanResult->beacon_ie_len = 0;

    apScanResult->freq = BASE_FREQ_2_4 + 5;

    CME_TEST_SET_PEER_PARAMS(bssidStr, 0, ++gCmeTesterSsid2ScanRes);
    memcpy(apScanResult->bssid, bssidStr, 6);

    apSharedInfo->mpCandidateScanResults->mProfileId = gUniqueProfileId;

    apSharedInfo->mNumCandidatesFound = 1;

    GTRACE(GRP_CME,  "CME tester faked candidate scan result SSID %s BSSID %s ies length %d", ssidStr, bssidStr, ieLen);
    utilsDumpScanResult(apScanResult);
}
#endif

// ----------------------------------------------------------------------------
void cmeTestInit()
{

#ifdef CC33XX_NO_CME_TEST
    return;

#else

    OsiReturnVal_e rc;
    if (FALSE == gInitRoleViaSupplicant)
        return;

    memset(&gCmeTester, 0, sizeof(cmeTesterState_t));
//    gCmeTester.numSimulatedPeers = 0;
//    gCmeTester.currentScriptId = 0;
//    gCmeTester.numScriptIter = 0;
//    gCmeTester.numAuthTimeouts = 0;
//    gCmeTester.numAssocTimeouts = 0;
    gCmeTesterSsidCount = 0;
    gCmeTesterSsid2ScanRes = 0;
    gCmeTester.currentEventId = -1;
    gCmeTester.numTestCycles = MAX_TEST_LOOPS;
    gCmeTestScanSuccess = TRUE;    // Configure faked scan result: TRUE - fits scan request
    gCmeTesterSetRsnIe = FALSE;
    gRolesBitMask = ROLE_TYPE_NONE;

    if (OSI_OK != osi_TimerCreate(&gCmeTesterTimer, "cmeTesterTimer", cmeTestTimerEvents))
    {
        GTRACE(GRP_CME,  "os_timerCreate: osi_TimerCreate ERROR");
        ASSERT_GENERAL(0);
    }

    // Arm timer to start the test, from this point test runs on its own
    rc = osi_TimerStart(&gCmeTesterTimer, 1000, OSI_ONE_SHOT_TIMER);
    ASSERT_GENERAL(OSI_OK == rc);
#endif


}

// ----------------------------------------------------------------------------
#ifndef FPGA_PMAC_TX
cmeTesterConnectResp_e cmeTestConfigResponse(uint32_t aPackType)
{
    cmeTesterConnectResp_e response;

    switch (aPackType)
    {
        case FRAME_TYPE_AUTHENTICATION:
            response = cmeTesterScripts[gCmeTester.currentScriptId].authResponse;
            if (CME_TEST_RESP_NONE == response)
            {
                ++gCmeTester.numAuthTimeouts;
                if (gCmeTester.maxAuthTimeouts <= gCmeTester.numAuthTimeouts)
                    response = CME_TEST_RESP_OK;
            }
            break;

        case FRAME_TYPE_ASSOCIATION_REQ:
            response = cmeTesterScripts[gCmeTester.currentScriptId].assocResponse;
            if (CME_TEST_RESP_NONE == response)
            {
                ++gCmeTester.numAssocTimeouts;
                if (gCmeTester.maxAssocTimeouts <= gCmeTester.numAssocTimeouts)
                    response = CME_TEST_RESP_OK;
            }
            break;

        default:
            ASSERT_GENERAL(0);
    }

    return response;
}
#endif

#ifndef CC33XX_NO_CME_TEST
Bool_e cmeIsFastTest()
{
    return gCmeTester.testFastConnection;
}
#endif

#ifndef CC33XX_NO_CME_TEST
void cmeClearFastTest()
{
    gCmeTester.testFastConnection = 0;
}


void runCmeTesterFromIdle()
{
#ifdef CC33XX_NO_CME_TEST
    return;
#else
//    if (ROLE_TYPE_NONE != gRolesBitMask)
//    {
//        CME_WlanSetMode(gRolesBitMask);
//        gRolesBitMask = ROLE_TYPE_NONE;
//    }

    CME_WlanSetMode(gRolesBitMask,TX_WAIT_FOREVER);
    gRolesBitMask = ++gRolesBitMask & 1;
#endif
}

#endif
#endif // CC33XX_NO_CME_TEST
