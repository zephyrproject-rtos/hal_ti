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
  FILENAME:       cme_mng.c

  DESCRIPTION:	  This is the CME manager module, it is responsible for handling
  	  	  	  	  connection and policy commands.
                  
  HISTORY:
                  04/15 Creation
  ----------------------------------------------------------------------------- */

// the below should be included by wpa_supplicant_i.h, added here in order to
// avoid changes in wpa_supplicant_i.h
#include <stdio.h>
#include "common.h"

#include <public_types.h>
#include "drv_ti_internal.h"
#include "wpa_supplicant_i.h"
#include "wpa_common.h"
#include "eap_defs.h"
#include "wpa.h"
#include "bss.h"
#include "eapol_supp_sm.h"
#include "wpa_supplicant/config.h"
#include "notify.h"
#include "drivers/driver.h"
#include "eloop.h"
#include "cme_defs.h"
#include "cme_internal_api.h"
#include "cme_dispatcher_api.h"
#include "cme_scan_api.h"
#include "scan.h"
#include "osi_kernel.h"
#include "cme_supplicant_api.h"
#include "wps_supplicant.h"
#include "wps.h"
#include "common/defs.h"
#include "sha1.h"
#include "eap_peer/eap.h"
#include "p2p_supplicant.h"
#include "p2p/p2p.h" 
#include "cme_tester.h"
#include "eap_common/eap_wsc_common.h"
#include "ap/sta_info.h"
#include "ap/hostapd.h"
#include "ap_drv_ops.h"
#include "cme_common.h"
#include "cme_defs.h"
#include "drv_ext_app.h"
#include "p2p_i.h"

#include "pmksa_cache.h"
#include "wpa_i.h"


// ============================================================================
//		Modules private definitions
// ============================================================================

// Points to wpa_supplicant interfaces
extern struct wpa_global *gpSupplicantGlobals;
/* TODO need implementation
extern CMEWlanEventDisconnect_t gLastDisconnectInfo_ull ;
*/
extern uint8_t  gCurrentSSID[MAXIMAL_SSID_LENGTH];
extern size_t gCurrentSSIDLen;
extern uint8_t cfgGetP2pOperChannel();
extern uint8_t cfgGetP2pOperRegClass();
extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t * args, uint16_t argsLen);
extern volatile uint8_t gFwCrashOccurred;


// TODO - R2 uses different values for AP+SC scan and stand alone scan
#define CME_SITE_SURVEY_SCAN_RESULTS_AGING_MS	(60*1000)

// supplicant command length for select netwrok
#define SELECT_NETWROK_CMD_LEN (14+SSID_MAX_LEN)

//WPS marker on ad hoc connection - just a note
// TODO = If we're using wpa_config_set, we'd better use here wpa_config_get
#define CME_IS_ONGOING_WPS_AD_HOC_CONNECTION() ((gAdHocProfile_ull.profile.key_mgmt & WPA_KEY_MGMT_WPS) ? 1 : 0)
#define CME_SET_WPS_AD_HOC_CONNECTION()        (gAdHocProfile_ull.profile.key_mgmt |= WPA_KEY_MGMT_WPS)
#define CME_CLEAR_WPS_AD_HOC_CONNECTION()      (gAdHocProfile_ull.profile.key_mgmt &= ~WPA_KEY_MGMT_WPS)

// Fast connection scan result validiy indication - score field = 0 indicates
// non valid result. Any other value indicates a valid result.
#define CME_IS_FAST_CANDIDATE_VALID()       (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.isFastConnectValid)
#define CME_VALIDATE_FAST_CANDIDATE()       (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.isFastConnectValid = 1)
#define CME_INVALIDATE_FAST_CANDIDATE()     (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.isFastConnectValid = 0)

//p2p defaults
#define DEFAULT_P2P_INTENT (3)  // change default p2p intent to mitigate issues related to re-negotiations to SL as GO
#define DEFAULT_P2P_FORCE_AUTO_GO (0)//not persistent
#define DEFAULT_P2P_NEG_INITIATOR (2)//Random Backoff

// OPEN policy profile default prioirty
// As this profile is created by CME, we have to set its priority to lowest value
#define CME_OPEN_POLICY_PROFILE_PRIORITY    (1)

//
//eap configuration simplelink dedicated (imported from cc31xx)
//
#define EAP_CONFIG_FLAGS_PHASE1_PEAP     BIT(1)
#define EAP_CONFIG_FLAGS_PHASE1_FAST     BIT(2)

#define EAP_CONFIG_FLAGS_PHASE2_MASK     (BIT(3)| BIT(4))
#define EAP_CONFIG_FLAGS_PHASE2_OFFSET   3

#define EAP_CONFIG_PHASE2_GET(Flags)     (((Flags) & EAP_CONFIG_FLAGS_PHASE2_MASK)>>EAP_CONFIG_FLAGS_PHASE2_OFFSET)
#define EAP_CONFIG_PHASE2_SET(Flags,Val) {Flags &= ~EAP_CONFIG_FLAGS_PHASE2_MASK; Flags |= ((Val<<EAP_CONFIG_FLAGS_PHASE2_OFFSET)&EAP_CONFIG_FLAGS_PHASE2_MASK);}

//
// other macros
//
#define CME_IS_SEC_TYPE_SAE(SecType)     ((SecType) == CME_SEC_TYPE_WPA3 || (SecType) == CME_SEC_TYPE_WPA2_WPA3 || \
                                          (SecType) == CME_SEC_TYPE_WPA3_FT || (SecType) == CME_SEC_TYPE_WPA2_WPA3_FT)
#define CME_IS_SEC_TYPE_TRANSITION_MODE(SecType)     ((SecType) == CME_SEC_TYPE_WPA2_WPA3 || (SecType) == CME_SEC_TYPE_WPA2_WPA3_FT)

#define CME_IS_ENT_KEY_MGMT_SUITE_B_TYPE(keyMgmt)  ((keyMgmt) & (WPA_KEY_MGMT_IEEE8021X_SUITE_B | WPA_KEY_MGMT_IEEE8021X_SUITE_B_192))

//compact scan frame structure for fast connection
typedef struct {
        struct wpa_scan_res     mScanResult;
        uint8_t                   mInfoElements[MAX_BEACON_BODY_LENGTH];
        int8_t                    mProfileId;
        uint8_t                   mScore;
} SerializedCompactScanframe;


// Holds copies of supplicant connection parameters for potential future use during reassociation
typedef struct {
    //--------------------------------
    //Params for internal use
    u8              valid; 
    u8              int_curr_ssid[WLAN_SSID_MAX_LENGTH]; 
    size_t          int_curr_ssid_len;
    int             int_key_mgmt;

    //--------------------------------
    // Parameters from wpa_s->sme (struct sme)
    u8              prev_bssid[ETH_ALEN];
    int             prev_bssid_set;
    int             ft_used;
    u8              mobility_domain[2];
    // Parameters from wpa_s->wpa (struct wpa_sm)
    int             ptk_set;
    int             tptk_set;
    size_t          pmk_len;
    u8              pmk[PMK_LEN_MAX];
    struct wpa_ptk  ptk;
    struct wpa_ptk  tptk;
    struct wpa_gtk  gtk;
    struct wpa_gtk  gtk_wnm_sleep;
    struct wpa_igtk igtk;
    struct wpa_igtk igtk_wnm_sleep;
#ifdef CONFIG_IEEE80211R
    u8              xxkey[PMK_LEN_MAX];
    size_t          xxkey_len;
    u8              pmk_r0[PMK_LEN_MAX];
    size_t          pmk_r0_len;
    u8              pmk_r1[PMK_LEN_MAX];
    size_t          pmk_r1_len;
#endif /* CONFIG_IEEE80211R */
} reassociation_params_t;

reassociation_params_t g_reassociation_params;

// ============================================================================
//		Modules data base
// ============================================================================



// The preferred networks list holds the profiles received from user application.
// The list is retrieved by scan context before every periodic scan cycle as it
// is assumed the device may switch to Sleep between scan cycles.
// !!! List is read from FS when needed therefore can be GLX'd !!!

cmeProfileInfo_t   *gPreferredNetworks = NULL;

uint8_t            gPreferredReadFromFS; //MEM_REGION_GLX, For connection creation, assumes GLX retention

uint8_t            gPreferredNetworksConnAttemptCnt_ull[CME_SCAN_MAX_PROFILES] ;

uint8_t            gConnectingIndex_ull ;//mark the current connection index for clearing blacklist once connected
uint8_t            gConnSecutiveScanCompletes_ull ;//Check for X consequtive scan completes with not connection to clear black list

// Holds the ID received from supplicant for ad-hoc connection.
// Should be used for profile removal.
//int32_t  gAdHocProfileId ;

cmeProfileInfo_t gAdHocProfile_ull ;

//ENT PMK Cache WA
_cme_wpa_pmkid_params_t gAdHocEapPmkidParams_ull;


// Unique profile ID attached to each new profile. Used for identifying the
// profile selected for connection by scan module during connection scan.
// Note: Indexes 0:5 are reserved for profile connection
//       indexes > 5: are for ad-hoc, WPS a,d p2p connection types
int8_t gUniqueProfileId_ull ;

//connection policy global parameters (including p2p negotiation parameters)
CmeConnectionPolicyParams_t gCmeConnectionPolicyParams_ull ;

//If true, it means the next disconnect is generated internally by supplicant right after the WPS negotiation
//to perform the fast connect, so the disconnect should be ignored.
Bool_e  gWPSfirstDisconnect_ull ;

//If true, it means the next disconnect is generated by the user 
Bool_e  gWPSkickDisconnect_ull ;

// Indicates the initiator of the ongoing ONE SHOT scan.
// In CME initiated ONE SHOT scans it is set to false.
// When set to true, it means the scan was initiated by the supplicant and not by the CME.
Bool_e gSupplicantInitiatedScanInProgress = FALSE;

// For MBO: BSS transition state machine.
Bss_transition_states_e gBssTransitionState;

//Decide whether to remove supplicant profile or not
Bool_e gSaveCurrentSupplicantProfile = FALSE;

uint8_t gPeerRemovedMacAddr_ull[MAC_ADDR_LEN] ;
// Controls early termination behavior in connection scans.
// When enabled, the scanning process stops after finding the first matching network.
// When disabled, all channels are scanned before selecting a network.
Bool_e gConnectionScanEarlyTerminationEnabled = FALSE;

// Profile related to current module
#define CC35XX_SUPPORT_P2P_PROFILE (0)   /* not supported */
#define CC35XX_SUPPORT_PROFILE_DISCONNECT_ON_REMOVAL (0) // check if this is needed


struct eap_method_type eap_peer_tls_methods[] = {
        { EAP_VENDOR_IETF, EAP_TYPE_TLS },
        { EAP_VENDOR_IETF, EAP_TYPE_NONE }
 };

uint32_t num_of_eap_methods_tls_methods = 2;

struct eap_method_type eap_peer_ttls_methods[] = {
        { EAP_VENDOR_IETF, EAP_TYPE_TTLS },
        { EAP_VENDOR_IETF, EAP_TYPE_NONE }
 };
uint32_t num_of_eap_methods_ttls_methods = 2;


struct eap_method_type eap_peer_peap_methods[] = {
        { EAP_VENDOR_IETF, EAP_TYPE_PEAP },
        { EAP_VENDOR_IETF, EAP_TYPE_NONE }
 };
uint32_t num_of_eap_methods_peap = 2;


struct eap_method_type eap_peer_fast_methods[] = {
        { EAP_VENDOR_IETF, EAP_TYPE_FAST },
        { EAP_VENDOR_IETF, EAP_TYPE_NONE }
 };


//fast connection network storage
typedef union
{
    struct
    {
        unsigned int    fastConnectScanFrameSet            :  1   ; // Bits[ 0: 0] = indicate whether fast connect scan frame was stored

        unsigned int    fastConnectProfileSsidSet          :  1   ; // Bits[ 1: 1] = indicate whether profile ssid was stored

        unsigned int    isFastConnectSecondChance          :  1   ; // Bits[ 2: 2] = flag indicating if this is the first fast connect trial or second

        unsigned int    isFastConnectValid                 :  1   ; // Bits[ 3: 3] = flag indicating if the connection was successful and full fast connect data is properly stored

        unsigned int    __pad_4_7__                      :  4   ; // Bits[ 4: 7] = TBD.
    };

    uint8_t  _w8 ;                                // Raw 8 bit access for all the fields at once.

}   _cmeFastConnectionStatusLabel_u;


typedef struct
{
    _cme_minimized_wpa_ssid_t       *cmeFastConnectionSsid;
    cmeScanCandidateDesc_t          *cmeFastConnFrame;
    _cmeFastConnectionStatusLabel_u cmeFastConnectStatusLabel;
    OsiTimer_t                      *gFastConnectTimer;
} _cmeFastConnectionCB_t;

_cmeFastConnectionCB_t gCmeFastConnectionCB_ull ;

uint8_t gEnableFastConnectionStoreToFlash = 0; //TODO: Add support for this by user configuration

#define CME_FAST_CONNECTION_TIMEOUT_MILI_SEC  (4000)

void wlan_calculate_pmk(int ssid_len,
                int8_t *ssid,
                int8_t *passphrase,
                unsigned int passphrase_length,
                u8   *pmk);

#ifdef PMK_SW_CONFIG_PATCH
Bool_e  pmk_on_ull   = 0;     //temp until pmk will be calculated by HW
                                            //it starve threads with lower priority as it
                                            //takes several seconds
#endif

// ============================================================================
//		Local Functions declarations
// ============================================================================

//static int32_t removeProfileFromDB(uint32_t aProfileId);
static int32_t removeProfileFromSupplicant(uint32_t aProfileId,int reason_code);

static void  setSharedSsidParams(CMEWlanAddGetProfile_t *apCmd,
                                 uint32_t               aKeyMgmt,
                                 _cme_minimized_wpa_ssid_t      *apSsid,
                                 int8_t                 *apSsidStr,
                                 int8_t                 *apPassword);
static int32_t  setSecurityParams(CMEWlanAddGetProfile_t *apCmd,
                                _cme_minimized_wpa_ssid_t       *apSsid,
                              int8_t                  *apPassword);

static void addAdHocProfile2DB(CMEWlanAddGetProfile_t  *apCmd, uint32_t aKeyMgmt,
        int8_t *apSsidStr, int8_t *apPassword, p2pProfile_e p2p_type,CMEEapWlanConnect_t *apEapCmd);

static void addProfileEap2DB(uint16_t    SecType,
                             unsigned char *anonymous_identity,
                             int anonymous_identity_len,
                             unsigned char *identity,
                             int identity_len,
                             unsigned char *passwd,
                             int passwd_len,
                             eap_phase1_val_t  eap_phase1_val,
                             eap_phase2_val_t  eap_phase2_val,
                             const uint8_t*    pEap_client_cert,
                             uint32_t    eap_client_cert_len,
                             const uint8_t*    pEap_ca_cert,
                             uint32_t    eap_ca_cert_len,
                             const uint8_t*    pEap_private_key,
                             uint32_t    eap_private_key_len,
                             uint32_t TLSKeyLength,
                             uint8_t  FastTransition,
                             cmeProfileInfo_t * inputProfile);

static struct wpa_ssid * addProfile2Supplicant(const _cme_minimized_wpa_ssid_t *apInputApSsid);

static void duplicateSharedSsidParams(const _cme_minimized_wpa_ssid_t *apInputApSsid,
                                      struct wpa_ssid       *apSsid);
static void duplicateEapProfile(struct wpa_supplicant *wpa_s,
                                      const _cme_minimized_wpa_ssid_t *apInputApSsid,
                                      struct wpa_ssid       *apSsid);
void duplicateWpaPmksaCache(cmeProfileInfo_t *pProfile, cmeScanCandidateDesc_t *apCandidate,
                             struct wpa_ssid *pSupplicantSsid);

static int8_t getUniqueProfileId();
static int shouldConnectToOpenAp();

//
// cmeReadFastConnectionData
//
// read fast connect files from FS and check if need to be re-written according
// to new parameters learned at last successful connection
//
static int cmeReadFastConnectionData(_cme_minimized_wpa_ssid_t **apSsid, cmeScanCandidateDesc_t **apCandidateInfo);

static void cmeUpdateCacheFastConnectionData(cmeScanCandidateDesc_t* scanInfo,
                                             _cme_minimized_wpa_ssid_t* selectedSSID
#if 0//P2P support
                           ,
                           int group_capab,
                           const u8 *p2p_addr,
                           int       p2p_level,
                           int       p2p_freq,
                           int       p2pProfile,
                           char     *p2p_pin
#endif
                           );

int cmeReadFastConnectionDataFromFlash();
int cmeWriteFastConnectionDataToFlash();
void cmeDeleteFastConnectionDataFromFlash();
void cmeCopyProfileToAdHocProfile(uint8_t index);

static int32_t add_or_update_blob(struct wpa_supplicant *wpa_s,
                        char *name,
                        uint8_t *data, size_t len);
static void remove_cert_blob(struct wpa_supplicant *wpa_s,
    const char *name);

int16_t entGetProfileParamsFromFlash(cmeEntProfileParams_t *pProfileParam);
int16_t entSetProfileParamsToFlash(cmeEntProfileParams_t *pProfileParam);

//eap consts

const char PROVISIONING_TYPE1[] = "fast_provisioning=1 fast_pac_format=binary";
const char PROVISIONING_TYPE2[] = "fast_provisioning=2 fast_pac_format=binary";

const char PHASE1_PEAPVER2[] = "peapver=2";
const char PHASE1_PEAPVER1[] = "peapver=1";
const char PHASE1_PEAPVER0[] = "peapver=0";
const char PHASE1_TLS_TTLS[] = "include_tls_length=1 tls_allow_sha1=1 tls_disable_time_checks=1";
const char PHASE1_TLS_TTLS_CA_CERT_VERIFICATION_NONE[] = "include_tls_length=1 tls_allow_sha1=1 tls_allow_illegal=1 tls_disable_time_checks=1";


const char PHASE2_AUTH_TYPE_MSCHAPV2[] = "auth=MSCHAPV2";//TTLS/MSCHAPV2 and PEAP/MSCHAPV@
const char PHASE2_AUTH_TYPE_GTC[] = "auth=GTC";//TTLS/MSCHAPV2 and PEAP/MSCHAPV@
const char PHASE2_AUTH_TYPE_TLS[] = "autheap=TLS";
const char PHASE2_AUTH_TYPE_PSK[] =  "autheap=PSK";


//
// CC33xx    -    now supporting 2 sets of ENT certificate files
//                which will be determined according to cert_index supplied by the user
//
#define SLINK_FILE_CA_CERT                       "/sys/cert/ca.pem"
#define SLINK_FILE_CLIENT_CERT                   "/sys/cert/client.pem"
#define SLINK_FILE_PRIVATE_KEY                   "/sys/cert/private.key"
#define SLINK_FILE_PAC                           "/tmp/pac.bin"
#define SLINK_FILE_CA_CERT2                       "/sys/cert/ca2.pem"
#define SLINK_FILE_CLIENT_CERT2                   "/sys/cert/client2.pem"
#define SLINK_FILE_PRIVATE_KEY2                   "/sys/cert/private2.key"
#define SLINK_FILE_PAC2                           "/tmp/pac2.bin"


//TODO: PAC (EAP_FAST), how supplicant uses this?, seems it needs to write to this file (?). Handle when eap_fast is added...
const char  SUPP_FILE_NAME_PAC[2][20]           = {SLINK_FILE_PAC,SLINK_FILE_PAC2};
const char  SUPP_PAC_FILE_MEMORY_BLOB[] = "blob://";

//static uint32_t getNumEnabledProfiles();

static int isBlackListed(uint32_t index);
static void cmeFastConnectAttempt(struct wpa_supplicant *wpa_s,_cme_minimized_wpa_ssid_t *ssid, int first_attempt);

#define CME_ENT_SUITE_B_PMK_CACHE_SUPPORT
#ifdef CME_ENT_SUITE_B_PMK_CACHE_SUPPORT
typedef struct 
{
    uint8_t kck[32];
    size_t kck_len;
    int kck_valid;
}kck_t;

static kck_t gCmeKck;
int cme_is_kck_available(void);

#endif //CME_ENT_SUITE_B_PMK_CACHE_SUPPORT

// ============================================================================
//		Exported Functions
// ============================================================================



extern const u8 * get_ie(const u8 *ies, size_t len, u8 eid);


int cme_is_p2p_role_configured ()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    uint32_t host_configured_roles_bitmap = CME_GetStartedRoleBitmap();

    return ( ((host_configured_roles_bitmap & BIT_x(ROLE_DEVICE)) != 0) ? 1 : 0);

    return 0;

}

void cmeMngInitStaDB(void)
{
    gPreferredNetworks = os_zalloc(sizeof(cmeProfileInfo_t) * CME_SCAN_MAX_PROFILES);
    
    if (gPreferredNetworks == NULL)
    {
        GTRACE(GRP_CME, "ERROR: Could not allocate memory for preferred network list");
        CME_PRINT_REPORT_ERROR("\n\rERROR: Could not allocate memory for preferred network list");
        ASSERT_GENERAL(0);
    }

    cmeMng_InitAfterSleep();

    //fast policy
    gCmeFastConnectionCB_ull.gFastConnectTimer = NULL;
    
    if (gCmeConnectionPolicyParams_ull.fastPersistent)
    {
        //If the memory is already allocated (i.e from previous fast connection cache), no need to alloc memory again.
        //Use the same memory

        if (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectScanFrameSet == 0)
        {
            gCmeFastConnectionCB_ull.cmeFastConnFrame = os_malloc(sizeof(cmeScanCandidateDesc_t));

            if (gCmeFastConnectionCB_ull.cmeFastConnFrame == NULL)
            {
                CME_PRINT_REPORT_ERROR("\n\rcmeMngInitStaDB: Allocation failure! (1)");
                return;
            }
            //set status bitmap of fast connection frame
            gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectScanFrameSet = 1;

            os_memset(gCmeFastConnectionCB_ull.cmeFastConnFrame, 0, sizeof(cmeScanCandidateDesc_t));
        }
        

        if (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectProfileSsidSet == 0)
        {
            gCmeFastConnectionCB_ull.cmeFastConnectionSsid = os_malloc(sizeof(_cme_minimized_wpa_ssid_t));
            if (gCmeFastConnectionCB_ull.cmeFastConnectionSsid == NULL)
            {
                CME_PRINT_REPORT_ERROR("\n\rcmeMngInitStaDB: Allocation failure! (2)");
                os_free(gCmeFastConnectionCB_ull.cmeFastConnFrame);
                return;
            }

            //set fast connect profile ssid set
            gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectProfileSsidSet = 1;
        }

        if (cmeReadFastConnectionDataFromFlash() != OSI_OK)
        {
            CME_PRINT_PROFILE_REPORT_ERROR("\n\rERROR: Could not read fast connection data from flash!");

            //release memory
            if (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectScanFrameSet != 0)
            {
                os_free(gCmeFastConnectionCB_ull.cmeFastConnFrame);
                //set status bitmap of fast connection frame
                gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectScanFrameSet = 0;
            }

            if (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectProfileSsidSet != 0)
            {
                if (gCmeFastConnectionCB_ull.cmeFastConnectionSsid != NULL)
                {
                    if (gCmeFastConnectionCB_ull.cmeFastConnectionSsid != &gAdHocProfile_ull.profile)
                    {
                        // Only free if it's NOT pointing to the static profile
                        os_free(gCmeFastConnectionCB_ull.cmeFastConnectionSsid);
                    }
                }
                //set fast connect profile ssid set
                gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectProfileSsidSet = 0;
            }

        }
    }
}

void cmeMngDeInitStaDB(void)
{
    os_free(gPreferredNetworks);
    gPreferredNetworks = NULL;
}

int16_t LoadConnectionPolicy_GetFromFlash(BOOLEAN isInternal, BOOLEAN runFromInit)
{
    // TODO need implementation
#if 0
    int8_t flashStatus;
    uint8_t priority;

    GTRACE(GRP_CME, "cmeMngSetConnectionPolicy: LoadConnectionPolicy_GetFromFlash");

    /* runFromInit should be TURE only when running the ElementRequest from Init Thread */

    if (TRUE == isInternal)
    {
        priority = FLASH_MANAGER_READ_INTERNAL_REQUEST_PRIORITY;
    }
    else
    {
        priority = FLASH_MANAGER_READ_EXTERNAL_REQUEST_PRIORITY;
    }

    flashStatus = FLASH_MANAGER_ElementRequest(runFromInit,
                                               FLASH_MNG_READ_ELEMENT_TYPE,
                                               FLASH_MULTI_ELEMENT_20_CONNECTION_POLICY_ID,
                                               FTL_MULTI_ELEMENT_20_CONNECTION_POLICY_SIZE,
                                               (uint32_t *)&gCmeConnectionPolicyParams_ull,
                                               priority,
                                               NULL);

    if (FLASH_MANAGER_REQUEST_SUCCESSFULLY_COMPLETED == flashStatus)
    {
        GTRACE(GRP_CME, "cmeMngSetConnectionPolicy: gCmeConnectionPolicyParams_ull Config valid in flash");
        return 0;
    }
    else if (FLASH_MANAGER_WARNING_READ_MULTI_ELEMENT_ELEMENT_NOT_IN_FLASH == flashStatus)
    {
        GTRACE(GRP_CME, "cmeMngSetConnectionPolicy: EWARNING - READ from flash failed since that gCmeConnectionPolicyParams_ull never saved to the flash");
    }
    else if (flashStatus > 0)
    {
        GTRACE(GRP_CME, "cmeMngSetConnectionPolicy: EWARNING - READ from flash failed, status = %d", flashStatus);
    }
    else
    {
        GTRACE(GRP_CME, "cmeMngSetConnectionPolicy: ERROR - READ from flash failed, status = %d", flashStatus);
    }

    /* Set default to the caller pointer */
    GTRACE(GRP_CME, "cmeMngSetConnectionPolicy: gCmeConnectionPolicyParams_ull Config is not valid, take default");

    memset(&gCmeConnectionPolicyParams_ull, 0, sizeof(gCmeConnectionPolicyParams_ull));

    // Fill up conneciton defaults
    gCmeConnectionPolicyParams_ull.autoStart = 1;/*auto start enabled by default*/
    //gCmeConnectionPolicyParams_ull.autoSmartConfig   = 0;
    //gCmeConnectionPolicyParams_ull.autoProvisioning   = 1/*auto provisioning enabled by default*/;
    gCmeConnectionPolicyParams_ull.shouldConnectToAnyP2P = 0;
    gCmeConnectionPolicyParams_ull.shouldConnectToOpenAp = 0;
    gCmeConnectionPolicyParams_ull.shouldUseFastConnect = 0;
#ifndef CC33XX_NO_CME_TEST
    //cmeIsFastTest();
#endif

    //p2p params
    gCmeConnectionPolicyParams_ull.intent = DEFAULT_P2P_INTENT;
    gCmeConnectionPolicyParams_ull.forceAutonomousGO = DEFAULT_P2P_FORCE_AUTO_GO;
    gCmeConnectionPolicyParams_ull.neginitiator = DEFAULT_P2P_NEG_INITIATOR;
#endif

    FILE *fConnPolicyFile = NULL;
    int retVal;

    CmeConnectionPolicyParams_t *policy = NULL;
    uint32_t cmdSize = sizeof(CmeConnectionPolicyParams_t);

    fConnPolicyFile = osi_fopen("conn_p", "rb");

    if(!fConnPolicyFile)
    {
        CME_PRINT_REPORT_ERROR("\n\rERROR: Cannot Open/Find connection policy file\n\r");
        ASSERT_GENERAL(0);
    }
    else
    {
        policy = (CmeConnectionPolicyParams_t *)os_zalloc(cmdSize);
        if (policy == NULL)
        {
            CME_PRINT_REPORT_ERROR("\n\rERROR: Cannot allocate memory for connection policy\n\r");
            ASSERT_GENERAL(0);
        }

        retVal = osi_fread(policy, cmdSize, 0, fConnPolicyFile);

        if (retVal == 0)
        {
            // Could not read file - assumtion that file didn't exist
            // Set default values
            CME_PRINT_REPORT("\n\r Setting default connection policy params\n\r");
            gCmeConnectionPolicyParams_ull.autoStart = 0;
            gCmeConnectionPolicyParams_ull.shouldConnectToAnyP2P = 0;
            gCmeConnectionPolicyParams_ull.shouldConnectToOpenAp = 0;
            gCmeConnectionPolicyParams_ull.shouldUseFastConnect = 0;
            gCmeConnectionPolicyParams_ull.fastPersistent = 0;

            os_free(policy);
            osi_fclose(fConnPolicyFile);
            return 0;
        }

        os_memcpy(&gCmeConnectionPolicyParams_ull, policy, sizeof(CmeConnectionPolicyParams_t));

        osi_fclose(fConnPolicyFile);
        os_free(policy);
    
    }
    return 1;

}


void SetConnectionPolicy_SetToFlash(BOOLEAN isInternal)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    // TODO need implementation
#if 0
    uint8_t priority;
    int8_t flashStatus;

    GTRACE(GRP_CME, "cmeMngSetConnectionPolicy: SetConnectionPolicy_SetToFlash");

    if (TRUE == isInternal)
    {
        priority = FLASH_MANAGER_WRITE_INTERNAL_REQUEST_PRIORITY;
    }
    else
    {
        priority = FLASH_MANAGER_WRITE_EXTERNAL_REQUEST_PRIORITY;
    }
    flashStatus = FLASH_MANAGER_ElementRequest(FALSE,
                                               FLASH_MNG_PROGRAM_ELEMENT_TYPE,
                                               FLASH_MULTI_ELEMENT_20_CONNECTION_POLICY_ID,
                                               FTL_MULTI_ELEMENT_20_CONNECTION_POLICY_SIZE,
                                               (uint32_t *)&gCmeConnectionPolicyParams_ull,
                                               priority,
                                               NULL);

    if ( (FLASH_MANAGER_REQUEST_SUCCESSFULLY_COMPLETED == flashStatus) || (FLASH_MANAGER_WARNING_PROGRAM_MULTI_ELEMENT_NOT_NEEDED_DATA_DOES_NOT_CHANGED == flashStatus) )
    {
        GTRACE(GRP_CME, "cmeMngSetConnectionPolicy: saved to flash");
    }
    else if (flashStatus > 0)
    {
        GTRACE(GRP_CME, "cmeMngSetConnectionPolicy: WARNING - failed to SAVE to flash, status = %d", flashStatus);
    }
    else
    {
        GTRACE(GRP_CME, "cmeMngSetConnectionPolicy: ERROR - failed to SAVE to flash, status = %d", flashStatus);
    }
#endif

    FILE *fConnPolicyFile = NULL;
    int retVal;

    uint32_t cmdSize = sizeof(CmeConnectionPolicyParams_t);

    fConnPolicyFile = osi_fopen("conn_p", "wb");

    if(!fConnPolicyFile)
    {
        CME_PRINT_REPORT_ERROR("\n\rERROR: Cannot Open/Find connection policy file\n\r");
        ASSERT_GENERAL(0);
    }
    else
    {
        retVal = osi_fwrite((uint32_t *)&gCmeConnectionPolicyParams_ull, cmdSize, 0, fConnPolicyFile);

        if (retVal == 0)
        {
            CME_PRINT_REPORT_ERROR("\n\r ERROR: Writing connection policy params to flash failed\n\r");
        }

        osi_fclose(fConnPolicyFile);
    }

}


// LoadPreferredNetworks_GetFromFlashToPointer - reads profiles from flash into preferredNetworks
// NOT into GLX (gPreferredNetworks).
int16_t LoadPreferredNetworks_GetFromFlashToPointer(cmeProfileInfo_t *preferredNetworks, BOOLEAN isInternal)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    // TODO need implementation
#if 0
    int8_t flashStatus;
    uint8_t priority;
    int i;

    GTRACE(GRP_CME, "PreferredNetworks: LoadPreferredNetworks_GetFromFlashToPointer");

    if (TRUE == isInternal)
    {
        priority = FLASH_MANAGER_READ_INTERNAL_REQUEST_PRIORITY;
    }
    else
    {
        priority = FLASH_MANAGER_READ_EXTERNAL_REQUEST_PRIORITY;
    }

    flashStatus = FLASH_MANAGER_ElementRequest(FALSE,
                                               FLASH_MNG_READ_ELEMENT_TYPE,
                                               FLASH_MULTI_ELEMENT_1_PREFERRED_NETWORKS_ID,
                                               FTL_MULTI_ELEMENT_1_PREFERRED_NETWORKS_SIZE,
                                               (uint32_t *)&preferredNetworks[0],
                                               priority,
                                               NULL);


    if (FLASH_MANAGER_REQUEST_SUCCESSFULLY_COMPLETED == flashStatus)
    {
        GTRACE(GRP_CME, "PreferredNetworks: preferredNetworks Config valid in flash");

        for (i = 0; i < CME_SCAN_MAX_PROFILES; i++)
        {

            //CC33XX Jan 1 2017 happy new years and mazaltov to my wife!!!!! and im here solving bugs!!
            //                         when reading from flash, after reset, the counter stays invalid
            //                         so every time we read from flash and fill the profiles, make sure to zero the counter
            //                         if it was already read since the original init
            if (gPreferredNetworksConnAttemptCnt_ull[i] == CONN_ATTEMPT_INVALID_CTR)
            {
                gPreferredNetworksConnAttemptCnt_ull[i] = 0;
            }
        }

        return 0;
    }
    else if (FLASH_MANAGER_WARNING_READ_MULTI_ELEMENT_ELEMENT_NOT_IN_FLASH == flashStatus)
    {
        GTRACE(GRP_CME, "PreferredNetworks: WARNING - READ from flash failed since profiles never saved to the flash, take default");
    }
    else if (flashStatus > 0)
    {
        GTRACE(GRP_CME, "PreferredNetworks: WARNING - READ from flash failed, status = %d , take default", flashStatus);
    }
    else
    {
        GTRACE(GRP_CME, "PreferredNetworks: ERROR - READ from flash failed, status = %d , take default", flashStatus);
    }

    return 1;
#endif

    int i;
    FILE *fProfileFile = NULL;
    int retVal;
    uint32_t cmdSize = sizeof(cmeProfileInfo_t) * CME_SCAN_MAX_PROFILES;

    fProfileFile = osi_fopen("profiles", "rb");

    if(!fProfileFile)
    {
        CME_PRINT_REPORT_ERROR("\n\rERROR: Cannot Open/Find profiles file\n\r");
        ASSERT_GENERAL(0);
    }
    else
    {
        if (preferredNetworks == NULL)
        {
            CME_PRINT_REPORT_ERROR("\n\rERROR: profiles buffer is NULL\n\r");
            ASSERT_GENERAL(0);
        }

        retVal = osi_fread((uint32_t *)&preferredNetworks[0], cmdSize, 0, fProfileFile);

        if (retVal == 0)
        {
            // Could not read file - assumtion that file didn't exist
            // Set default values
            CME_PRINT_REPORT("\n\r Init profiles file in flash\n\r");

            /* Set default to the caller pointer */
            os_memset(preferredNetworks, 0, cmdSize);

            for (i = 0; i < CME_SCAN_MAX_PROFILES; i++)
            {
                // Mark as free
                preferredNetworks[i].profile.id = CME_INVALID_PROFILE_ID;
                preferredNetworks[i].uniqueProfileId = CME_INVALID_PROFILE_ID;
                preferredNetworks[i].profile.passphrase = NULL;//should not be allocated
                preferredNetworks[i].profile.eap.eap_entProfileIndex = CME_INVALID_ENT_IDX;  

                //WPA3 cache
                preferredNetworks[i].pmkid_params.pmkid_set = 0;

                // Irrelevant if no profile exist
                gPreferredNetworksConnAttemptCnt_ull[i] = CONN_ATTEMPT_INVALID_CTR;
            }

            osi_fclose(fProfileFile);
            return 1;
        }

        GTRACE(GRP_CME, "PreferredNetworks: preferredNetworks File is valid in flash");
        if (isInternal)
        {
            for (i = 0; i < CME_SCAN_MAX_PROFILES; i++)
            {
                //when reading from flash, after reset, the counter stays invalid
                //so every time we read from flash and fill the profiles, make sure to zero the counter
                //if it was already read since the original init
                if (preferredNetworks[i].uniqueProfileId != CME_INVALID_PROFILE_ID)
                {
                    gPreferredNetworksConnAttemptCnt_ull[i] = 0;
                }
            }
        }

        osi_fclose(fProfileFile);

    }
    return 0;
    
}


// SetPreferredNetworks_SetToFlashFromPointer - sets profiles in flash from preferredNetworks
// NOT from GLX (gPreferredNetworks).
int16_t SetPreferredNetworks_SetToFlashFromPointer(cmeProfileInfo_t *preferredNetworks, BOOLEAN isInternal)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    // TODO need implementation
#if 0

    uint8_t priority;
    int8_t flashStatus;

    GTRACE(GRP_CME, "PreferredNetworks: SetPreferredNetworks_SetToFlashFromPointer");

    if (TRUE == isInternal)
    {
        priority = FLASH_MANAGER_WRITE_INTERNAL_REQUEST_PRIORITY;
    }
    else
    {
        priority = FLASH_MANAGER_WRITE_EXTERNAL_REQUEST_PRIORITY;
    }
    flashStatus = FLASH_MANAGER_ElementRequest(FALSE,
                                               FLASH_MNG_PROGRAM_ELEMENT_TYPE,
                                               FLASH_MULTI_ELEMENT_1_PREFERRED_NETWORKS_ID,
                                               FTL_MULTI_ELEMENT_1_PREFERRED_NETWORKS_SIZE,
                                               (uint32_t *)&preferredNetworks[0],
                                               priority,
                                               NULL);

    if ( (FLASH_MANAGER_REQUEST_SUCCESSFULLY_COMPLETED == flashStatus) || (FLASH_MANAGER_WARNING_PROGRAM_MULTI_ELEMENT_NOT_NEEDED_DATA_DOES_NOT_CHANGED == flashStatus) )
    {
        GTRACE(GRP_CME, "PreferredNetworks: saved to flash");
        return 0;
    }
    else if (flashStatus > 0)
    {
        GTRACE(GRP_CME, "PreferredNetworks: WARNING - failed to SAVE to flash, status = %d", flashStatus);
        return 1;
    }
    else
    {
        GTRACE(GRP_CME, "PreferredNetworks: ERROR - failed to SAVE to flash, status = %d", flashStatus);
        return 1;
    }
#endif

    FILE *fProfileFile = NULL;
    int retVal;
    uint32_t cmdSize = sizeof(cmeProfileInfo_t) * CME_SCAN_MAX_PROFILES;

    fProfileFile = osi_fopen("profiles", "wb");

    if(!fProfileFile)
    {
        CME_PRINT_REPORT_ERROR("\n\rERROR: Cannot Open/Find profiles file\n\r");
        ASSERT_GENERAL(0);
    }
    else
    {
        if (preferredNetworks == NULL)
        {
            CME_PRINT_REPORT_ERROR("\n\rERROR: profiles buffer is NULL\n\r");
            ASSERT_GENERAL(0);
        }

        retVal = osi_fwrite((uint32_t *)&preferredNetworks[0], cmdSize, 0, fProfileFile);

        if (retVal == 0)
        {
            CME_PRINT_REPORT_ERROR("\n\r ERROR: Writing profiles data to flash failed\n\r");
            return 1;
        }
        
        osi_fclose(fProfileFile);
    }

    return 0;
}

//
// ENT file system access API's
//

int16_t LoadEnterpriseProfile_GetFromFlash(cmeEntProfileParams_t *pProfileParam, BOOLEAN isInternal)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    // TODO need implementation
#if CC35XX_ADD_SUPPORT_ENT_PROFILE
    int8_t flashStatus;
    uint8_t priority;

    GTRACE(GRP_CME, "EnterpriseProfile: LoadEnterpriseProfile_GetFromFlash");

    if (TRUE == isInternal)
    {
        priority = FLASH_MANAGER_READ_INTERNAL_REQUEST_PRIORITY;
    }
    else
    {
        priority = FLASH_MANAGER_READ_EXTERNAL_REQUEST_PRIORITY;
    }

    flashStatus = FLASH_MANAGER_ElementRequest(FALSE,
                                               FLASH_MNG_READ_ELEMENT_TYPE,
                                               FLASH_MULTI_ELEMENT_21_ENTERPRISE_PROFILE_ID,
                                               FTL_MULTI_ELEMENT_21_ENTERPRISE_PROFILE_SIZE,
                                               (uint32_t *)pProfileParam,
                                               priority,
                                               NULL);


    if (FLASH_MANAGER_REQUEST_SUCCESSFULLY_COMPLETED == flashStatus)
    {
        GTRACE(GRP_CME, "EnterpriseProfile: pProfileParam Config valid in flash");
        return 0;
    }
    else if (FLASH_MANAGER_WARNING_READ_MULTI_ELEMENT_ELEMENT_NOT_IN_FLASH == flashStatus)
    {
        GTRACE(GRP_CME, "EnterpriseProfile: WARNING - READ from flash failed since that pProfileParam never saved to the flash, clear the struct");
    }
    else if (flashStatus > 0)
    {
        GTRACE(GRP_CME, "EnterpriseProfile: WARNING - READ from flash failed, status = %d , clear the struct", flashStatus);
    }
    else
    {
        GTRACE(GRP_CME, "EnterpriseProfile: ERROR - READ from flash failed, status = %d , clear the struct", flashStatus);
    }

    /* clear pProfileParam */
    memset(pProfileParam, 0, sizeof(cmeEntProfileParams_t) * CME_MAX_EAP_ENTRIES);
#endif
    return 1;

}


int16_t SetEnterpriseProfile_SetToFlash(cmeEntProfileParams_t *pProfileParam, BOOLEAN isInternal)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

#ifdef CC35XX_ADD_SUPPORT_ENT_PROFILE
    uint8_t priority;
    int8_t flashStatus;

    GTRACE(GRP_CME, "EnterpriseProfile: SetEnterpriseProfile_SetToFlash");

    if (TRUE == isInternal)
    {
        priority = FLASH_MANAGER_WRITE_INTERNAL_REQUEST_PRIORITY;
    }
    else
    {
        priority = FLASH_MANAGER_WRITE_EXTERNAL_REQUEST_PRIORITY;
    }
    flashStatus = FLASH_MANAGER_ElementRequest(FALSE,
                                               FLASH_MNG_PROGRAM_ELEMENT_TYPE,
                                               FLASH_MULTI_ELEMENT_21_ENTERPRISE_PROFILE_ID,
                                               FTL_MULTI_ELEMENT_21_ENTERPRISE_PROFILE_SIZE,
                                               (uint32_t *)pProfileParam,
                                               priority,
                                               NULL);

    if ( (FLASH_MANAGER_REQUEST_SUCCESSFULLY_COMPLETED == flashStatus) || (FLASH_MANAGER_WARNING_PROGRAM_MULTI_ELEMENT_NOT_NEEDED_DATA_DOES_NOT_CHANGED == flashStatus) )
    {
        GTRACE(GRP_CME, "EnterpriseProfile: saved to flash");
        return 0;
    }
    else if (flashStatus > 0)
    {
        GTRACE(GRP_CME, "EnterpriseProfile: WARNING - failed to SAVE to flash, status = %d", flashStatus);
        return 1;
    }
    else
    {
        GTRACE(GRP_CME, "EnterpriseProfile: ERROR - failed to SAVE to flash, status = %d", flashStatus);
        return 1;
    }
#endif
    return 0;

}












//wakeup after sleep sequence
void cmeMng_InitAfterSleep()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    gPreferredReadFromFS = FALSE;

}

//init sequence
void cmeMngInit()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

	int i;

	cmeMng_InitAfterSleep();

    GTRACE_NVIC(GRP_CME, "cmeMngInit: ConnectionPolicy: AutoStart=%d , FastConnect=%d , OpenAP=%d, ShouldConnectToAnyP2P=%d",
           gCmeConnectionPolicyParams_ull.autoStart ,
           gCmeConnectionPolicyParams_ull.shouldUseFastConnect,
           gCmeConnectionPolicyParams_ull.shouldConnectToOpenAp,
           gCmeConnectionPolicyParams_ull.shouldConnectToAnyP2P);
    CME_PRINT_PROFILE_REPORT("\n\r cmeMngInit: ConnectionPolicy: AutoStart=%d , FastConnect=%d , OpenAP=%d, ShouldConnectToAnyP2P=%d, fastPersistent=%d",
           gCmeConnectionPolicyParams_ull.autoStart ,
           gCmeConnectionPolicyParams_ull.shouldUseFastConnect,
           gCmeConnectionPolicyParams_ull.shouldConnectToOpenAp,
           gCmeConnectionPolicyParams_ull.shouldConnectToAnyP2P,
           gCmeConnectionPolicyParams_ull.fastPersistent);

	// Mark the fast connnection as invalid;
	os_memset(&gCmeFastConnectionCB_ull, 0, sizeof(gCmeFastConnectionCB_ull));


    for (i=0 ; i<CME_SCAN_MAX_PROFILES ; ++i)
    {
        //black list counter
        gPreferredNetworksConnAttemptCnt_ull[i] = CONN_ATTEMPT_INVALID_CTR;
    }

    //clear ad hoc connection profile db before loading from flash
    os_memset(&gAdHocProfile_ull, 0, sizeof(cmeProfileInfo_t));

    // clear the last peer connected
    //memset(gPeerRemovedMacAddr_ull, 0, MAC_ADDR_LEN);

    //ENT PMK Cache WA
    os_memset(&gAdHocEapPmkidParams_ull, 0, sizeof(_cme_wpa_pmkid_params_t));


	gAdHocProfile_ull.profile.id =  CME_INVALID_PROFILE_ID;
	gAdHocProfile_ull.uniqueProfileId = CME_INVALID_PROFILE_ID;
	gAdHocProfile_ull.profile.eap.eap_entProfileIndex = CME_INVALID_ENT_IDX;
	//gAdHocProfile_ull.profile.ssid = gAdHocProfile_ull.ssid;//ssid will be staticly allocated in profiles

    gUniqueProfileId_ull = CME_SCAN_MAX_PROFILES;

	gConnectingIndex_ull = CONN_ATTEMPT_INVALID_IDX;
    //WPA3 cache
    gAdHocProfile_ull.pmkid_params.pmkid_set = 0;   
    gAdHocEapPmkidParams_ull.pmkid_set = 0;


    HOOK(HOOK_IN_CME_CONNECTION_MNG);

}

void cmeMngAdaptPreferredNetworkData(cmeProfileInfo_t *pPreferredNetworks)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    if(CME_IS_SEC_TYPE_SAE(pPreferredNetworks->profile.secType))
    {
        pPreferredNetworks->profile.passphrase = (char*)pPreferredNetworks->profile.wep_key;
    }
    
}
//
// cmeMngReadPreferredNetworkFromFlash
//
// in order to save ULL memory, and because preferred network profiles are stored in the FS anyway
// lets maintain a FS read method to read the FS into gPreferredNetworks GLX parameter only when needed
// after read one time in wakeup sequence, doesnt need to read again (alligned with FS all along)
//
void cmeMngReadPreferredNetworkFromFlash()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int16_t flashStatus;

    GTRACE(GRP_CME_DEBUG, "cmeMngReadPreferredNetworkFromFlash ");

    if (gPreferredReadFromFS)
    {
        return;//already read from flash, meaning gPreferredNetworks GLX parameter is up to date
    }

    /* Init gPreferredNetworks - cache list of Profiles from NVMEM */
    flashStatus = LoadPreferredNetworks_GetFromFlashToPointer(gPreferredNetworks, TRUE);

    if (flashStatus == 0)
    {
        gPreferredReadFromFS = TRUE;
        cmeMngAdaptPreferredNetworkData(gPreferredNetworks);
    }

}


//
// cmeUpdateCacheFastConnectionApScanData
//
// store connection parameters in fast connect (regardless if policy is set or not- could be changed later)
// for future RESET fast connection attempt
//  this is a special method for cc33 driver call - only update scan info
//

void cmeUpdateCacheFastConnectionApScanData(cmeScanCandidateDesc_t* apScanInfo)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);
    cmeUpdateCacheFastConnectionData(apScanInfo,NULL);
}

//
// cmeUpdateCacheFastConnectionData
//
// store connection parameters in fast connect (regardless if policy is set or not- could be changed later)
// for future RESET fast connection attempt
//
static void cmeUpdateCacheFastConnectionData(cmeScanCandidateDesc_t* apScanInfo,
                                      _cme_minimized_wpa_ssid_t* apSelectedSSID
#if CC35XX_SUPPORT_P2P_PROFILE //P2P support
                           ,
                           int group_capab,
                           const u8 *p2p_addr,
                           int       p2p_level,
                           int       p2p_freq,
                           int       p2pProfile,
                           char     *p2p_pin
#endif //CC35XX_SUPPORT_P2P_PROFILE
                           )
{   // Called from supplicant
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    if(!gCmeConnectionPolicyParams_ull.shouldUseFastConnect)
    {
        //if no fast connect policy is set, no storing needed
        return;
    }
#if CC35XX_SUPPORT_P2P_PROFILE //P2P support
    if (cme_is_p2p_role_configured())
    {
        //TODO- support P2P
        ASSERT_GENERAL(0);
    }
#endif // CC35XX_SUPPORT_P2P_PROFILE

    if (apScanInfo != NULL
#if CC35XX_SUPPORT_P2P_PROFILE // P2P support
    && ((wilink_get_drv_role() != TIWDRV_ROLE_TYPE_P2PCL) && (wilink_get_drv_role() != TIWDRV_ROLE_TYPE_P2PGO))
#endif
        )
    {

        //If the memory is already allocated (i.e from previous fast connection cache), no need to alloc memory again.
        //Use the same memory
        if (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectScanFrameSet == 0)
        {
            gCmeFastConnectionCB_ull.cmeFastConnFrame = os_malloc(sizeof(cmeScanCandidateDesc_t));
        }
        os_memset(gCmeFastConnectionCB_ull.cmeFastConnFrame, 0, sizeof(cmeScanCandidateDesc_t));

        GTRACE(GRP_CME, "updateCacheFastConnectionData: Preparing supplicant EPROM. Frame size = %d",
               apScanInfo->mScanResult.ie_len + apScanInfo->mScanResult.beacon_ie_len);

        //set status bitmap of fast connection frame
        gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectScanFrameSet = 1;

#if CC35XX_SUPPORT_P2P_PROFILE // P2P support
        if (p2p_addr)//meaning it is p2p_find
        {
            SOC_TRACE4(WLINK_MSG, MSG_1285, "updateCacheFastConnectionData: P2P Store P2P Find parameters freq %d level %d addr %x:%x",
                    p2p_freq,
                    p2p_level,
                    p2p_addr[4],
                    p2p_addr[5]);


            memcpy(gFastConnFrame.bssid, p2p_addr, ETH_ALEN);
            gFastConnFrame.rssi = p2p_level;
            //gFastConnFrame.role_parameter.freq = p2p_freq;
            gFastConnFrame.bufferLength = ies_len;//os_strlen(p2p_msg);
            memcpy(gFastConnFrame.buffer, ies, ies_len);



        }
        else//sta scan
#endif // CC35XX_SUPPORT_P2P_PROFILE
        {
//            memcpy(&gFastConnFrame.mScanResult, &apScanInfo->mScanResult, sizeof(struct wpa_scan_res));
//            memcpy(&gFastConnFrame.mInfoElements, apScanInfo->mInfoElements, apScanInfo->mScanResult.ie_len + apScanInfo->mScanResult.beacon_ie_len);
//            gFastConnFrame.mProfileId = apScanInfo->mProfileId;

            //uint32_t isValid = gCmeFastConnectionCB_ull.gFastConnFrame.mScore;

            // Copy scan detected candidate as is to fast candidate,
            // validity is by default valid (candidate score is always > 0)
            os_memcpy(gCmeFastConnectionCB_ull.cmeFastConnFrame, apScanInfo, sizeof(cmeScanCandidateDesc_t));

            // Restore validity indication
            //gCmeFastConnectionCB_ull.gFastConnFrame.mScore = isValid;


            GTRACE(GRP_CME, "Stored fast connection scan result: IEs len %d beacon IE len %d is status label 0x%x",
                   gCmeFastConnectionCB_ull.cmeFastConnFrame->mScanResult.ie_len, gCmeFastConnectionCB_ull.cmeFastConnFrame->mScanResult.beacon_ie_len, gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel._w8);
            CME_PRINT_PROFILE_REPORT("\n\r Stored to cache fast connection scan result: IEs len %d beacon IE len %d is status label 0x%x",
                   gCmeFastConnectionCB_ull.cmeFastConnFrame->mScanResult.ie_len, gCmeFastConnectionCB_ull.cmeFastConnFrame->mScanResult.beacon_ie_len, gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel._w8);         
        }
    }

    // And copy ssid descriptor;
    if (apSelectedSSID !=NULL)
    {
        GTRACE(GRP_CME, "updateCacheFastConnectionData: Store connection SSID (station scan)");

        // Oct 25 - optimizing ad-hoc connect case:
        if (apSelectedSSID == &gAdHocProfile_ull.profile)
        {
            //If previous cache was a profile, we need to free the memory. We are going to point to the global ad-hoc profile.
            if ((gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectProfileSsidSet == 1) &&
                (gCmeFastConnectionCB_ull.cmeFastConnectionSsid!=  &gAdHocProfile_ull.profile))
            {
                //mem_Free_ull(gCmeFastConnectionCB_ull.cmeFastConnectionSsid);
            }

            //
            //ad hoc connection, since its object is ULL based, just point at it
            //
            gCmeFastConnectionCB_ull.cmeFastConnectionSsid = apSelectedSSID;

            GTRACE(GRP_CME, "updateCacheFastConnectionData: storing ad-hoc connection into fast, so just point at the profile, its ULL");
            CME_PRINT_PROFILE_REPORT("\n\r updateCacheFastConnectionData: storing ad-hoc connection into fast, so just point at the profile, its ULL");
        }
        else
        {
            //profile connection, we need to allocate this buffer

            //If the memory is already allocated (i.e from previous fast connection cache), no need to alloc memory again.
            //Use the same memory
            if (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectProfileSsidSet == 0)
            {
                gCmeFastConnectionCB_ull.cmeFastConnectionSsid = os_malloc(sizeof(_cme_minimized_wpa_ssid_t));
            }
            //os_memset(gCmeFastConnectionCB_ull.cmeFastConnectionSsid, 0, sizeof (_cme_minimized_wpa_ssid_t));
            os_memcpy(gCmeFastConnectionCB_ull.cmeFastConnectionSsid,apSelectedSSID,sizeof (_cme_minimized_wpa_ssid_t));
            gCmeFastConnectionCB_ull.cmeFastConnectionSsid->passphrase = NULL;

        }
        //store wpa3 
        if (CME_IS_SEC_TYPE_SAE(apSelectedSSID->secType))
        {
            if (apSelectedSSID->passphrase != NULL)
            {
                uint8_t passphrase_length = strlen(apSelectedSSID->passphrase);
                
                if (passphrase_length > MAX_PASSPHRASE_LEN)
                {
                    passphrase_length = MAX_PASSPHRASE_LEN;
                }
                os_memset(gCmeFastConnectionCB_ull.cmeFastConnectionSsid->wep_key,
                            0,
                            sizeof(gCmeFastConnectionCB_ull.cmeFastConnectionSsid->wep_key));
                os_memcpy(gCmeFastConnectionCB_ull.cmeFastConnectionSsid->wep_key, apSelectedSSID->passphrase, passphrase_length);
            }
        }

        //set fast connect profile ssid set
        gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectProfileSsidSet = 1;

#if CC35XX_SUPPORT_P2P_PROFILE // P2P support
        gFastConnectionSsid.p2pProfile = p2pProfile;


        if (wilink_get_drv_role() == TIWDRV_ROLE_TYPE_P2PCL )
        {

            memcpy(gFastConnectionSsid.bssid, gP2PactiveConneciton.device_peer_mac, ETH_ALEN);
            gFastConnectionSsid.disabled = 2;
            gFastConnectionSsid.p2p_persistent_group = (group_capab & P2P_GROUP_CAPAB_PERSISTENT_GROUP ? 1 : 0 );
            if (p2pProfile == P2P_PIN_CODE_KEYPAD || p2pProfile == P2P_PIN_CODE_DISPLAY)
                memcpy(gFastConnectionSsid.p2p_pin, p2p_pin, WPS_PIN_LEN);
            //update actual remote GO operating channel
            gFastConnFrame.role_parameter.freq = (2407 + 5 * scanInfo->channel);

            SOC_TRACE4(WLINK_MSG, MSG_1284, "updateCacheFastConnectionData: P2P Store connection SSID, persistent %d, p2pProfile %d, pin [%x:%x:...",
                    gFastConnectionSsid.p2p_persistent_group,p2pProfile,p2p_pin[0],p2p_pin[1]);
        }
        else if (wilink_get_drv_role() == TIWDRV_ROLE_TYPE_P2PGO)
        {
            gFastConnectionSsid.bssid_set = 1;
            memcpy(gFastConnectionSsid.bssid, p2p_addr, ETH_ALEN);
            gFastConnectionSsid.disabled = 2;
            gFastConnectionSsid.p2p_persistent_group = 1;
            //memcpy(gFastConnectionSsid.passphrase, selectedSSID->passphrase, os_strlen(selectedSSID->passphrase));

            memcpy(gFastConnectionSsid.p2p_pin, gP2PactiveConneciton.p2p_pin, WPS_PIN_LEN);

            SOC_TRACE4(WLINK_MSG, MSG_2534, "updateCacheFastConnectionData: P2P Store Persistent GO Parameters, address %x:%x:%x:%x",
                    p2p_addr[2],p2p_addr[3],p2p_addr[4],p2p_addr[5]);

            //For GO - keep passphrase in buffer
            gFastConnFrame.bufferLength = os_strlen(selectedSSID->passphrase);
            memcpy(gFastConnFrame.buffer, selectedSSID->passphrase, os_strlen(selectedSSID->passphrase));



        }
#endif // CC35XX_SUPPORT_P2P_PROFILE

    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);
}


//
// shouldUseFastConnect
//
// determine if fast connection policy is set + fast connection parameters are stored
// in flash, and matching input ssid/bssid requested, then attempt fast connection
//
static Bool_e shouldUseFastConnect(_cme_minimized_wpa_ssid_t **apSsid, cmeScanCandidateDesc_t **apCandidateInfo,
                                   CMEWlanConnectCommon_t *apCmd, CMEEapWlanConnect_t *apEapCmd, uint8_t profiles_connection)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    Bool_e MatchResult=FALSE;
    int8_t                   *fast_ssid = NULL;
    CMEWlanConnectCommon_t *common_wlan_connect_cmd = NULL;

    if(apEapCmd != NULL)
    {
        return 0;// EAP PROFILE not supported for fast connect
    }

#if CC35XX_SUPPORT_P2P_PROFILE
    //
    //p2p or sta flows, will be more relevant when p2p will be activated
    //
    if (cme_is_p2p_role_configured())
    {
        GTRACE(GRP_CME, "shouldUseFastConnect: cme_is_p2p_role_configured-> FAST = FALSE ");
        return FALSE;
        ASSERT_GENERAL(0);//handle P2P fast connect
    }
    else if (cme_is_sta_role_like_activated())
#else //CC35XX_SUPPORT_P2P_PROFILE
    if (cme_is_sta_role_like_activated())
#endif
    {
//
//        if (FALSE == gCmeConnectionPolicyParams_ull.autoStart)
//        {
//            GTRACE(GRP_CME, "shouldUseFastConnect: effective auto start = FALSE: ");
//            return FALSE;
//        }

        if (FALSE == gCmeConnectionPolicyParams_ull.shouldUseFastConnect)
        {
            GTRACE(GRP_CME, "shouldUseFastConnect: effective FAST = FALSE ");
            CME_PRINT_PROFILE_REPORT("\n\rshouldUseFastConnect: effective FAST = FALSE ");
            return FALSE;
        }

//        FileReadResult = cmeReadFastConnectionData(ssid, scan_res, info_ele, profile_id);
        if (cmeReadFastConnectionData(apSsid, apCandidateInfo)==0)
        {
            GTRACE(GRP_CME, "shouldUseFastConnect: couldnt find valid fast connection data stored ");
            return FALSE;
        }

        //so far looking good!
        MatchResult = TRUE;


        //profiles connection case - get profile
        if (profiles_connection)
        {
            //read preferred network from FS to GLX before making changes
            if ( (gCmeLastWlanProfileIdx >= 0) && (gCmeLastWlanProfileIdx < CME_SCAN_MAX_PROFILES) )
            {
                cmeMngReadPreferredNetworkFromFlash();

                fast_ssid = (int8_t *)gPreferredNetworks[gCmeLastWlanProfileIdx].profile.ssid;
                common_wlan_connect_cmd = os_malloc(sizeof(CMEWlanConnectCommon_t));
                common_wlan_connect_cmd->SsidLen = gPreferredNetworks[gCmeLastWlanProfileIdx].profile.ssid_len;
                IRQ_UtilCopyMacAddress(gPreferredNetworks[gCmeLastWlanProfileIdx].profile.bssid, common_wlan_connect_cmd->Bssid);
            }
            else
            {
                //this means that profile connection requested, but fast is not set on profile connection
                MatchResult = FALSE;
            }

            GTRACE(GRP_CME, "shouldUseFastConnect: profiles connection requested, gCmeLastWlanProfileIdx=%d, match=%d",gCmeLastWlanProfileIdx,MatchResult);

        }
        //look for a match between the requested wlan_connect ssid/bssid to the existing fast-connect
       else if (apEapCmd!=NULL)
        {
            //EAP connection
            fast_ssid = EAP_SSID_STRING(&apEapCmd->EapCommonConnect);
            common_wlan_connect_cmd = &apEapCmd->EapCommonConnect;

        }
        else if (apCmd!=NULL)
        {
            //regular connection
            fast_ssid = SSID_STRING(apCmd);
            common_wlan_connect_cmd = apCmd;

            //TODO once profile history table exist, + wlan_connect(PROFILES), in case PROFILES - lookup the "last connected" profile and bring its ssid/bssid

        }


        if (common_wlan_connect_cmd!=NULL)
        {
            //if profile command was inputted, then we must make sure it matches
            //start negative ("always so negative!!!!")
            MatchResult = FALSE;

            //ssid string case, verify both have ssid len !=0
            if (((*apSsid)->ssid_len!=0) && (common_wlan_connect_cmd->SsidLen!=0) )
            {
                //
                //look for match in length, and then compare
                //
                if (((*apSsid)->ssid_len == common_wlan_connect_cmd->SsidLen)
                        &&
                    (os_memcmp(fast_ssid,(*apSsid)->ssid,(*apSsid)->ssid_len)==0))
                {
                   //its a match
                    MatchResult = TRUE;
                }
                else
                {
                    //no match....
                    GTRACE(GRP_CME,"shouldUseFastConnect: ssid input (%s) but no match to fast connect data (%s)",fast_ssid,(*apSsid)->ssid);
                }
            }
            //bssid case, check if bssids are equal
            else if (((*apSsid)->bssid_set) &&
                    MAC_EQUAL((*apSsid)->bssid,common_wlan_connect_cmd->Bssid))
            {
                //its a match
                MatchResult = TRUE;
            }
            else
            {
                GTRACE(GRP_CME,"shouldUseFastConnect: no bssid match input ");
            }


            if (profiles_connection)
            {
                os_free(common_wlan_connect_cmd);
            }
        }


        if (MatchResult!=FALSE)
        {
            GTRACE(GRP_CME,"shouldUseFastConnect: Complete Match found! ");
        }
        else
        {
            //if we got here, then there is a fast connect entry but it doesnt match the current connection request
            GTRACE(GRP_CME,"shouldUseFastConnect: fast connect exist but no match, invalidate the entry! ");
            cmeMarkInvalidFastConnectionData();
        }
    }

    if(TRUE == MatchResult)
    {
        GTRACE(GRP_CONN_STATS,"shouldUseFastConnect: Using Fast Connect!");
        CME_PRINT_PROFILE_REPORT("\n\rshouldUseFastConnect: Using Fast Connect! Release Scan Results\n");

        CME_ReleaseScanResults(CALLER8);
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return MatchResult;
}


//
// readFastConnectionData
//
// called during INIt- in case fast connect is set, should read the fast connection information
// for quicker supplicant feeding and fast authentication
//
//int cmeReadFastConnectionData(struct wpa_ssid **ssid,struct wpa_scan_res **scan_res, uint8_t **info_ele, int8_t *profile_id)
static int cmeReadFastConnectionData(_cme_minimized_wpa_ssid_t **apSsid, cmeScanCandidateDesc_t **apCandidateInfo)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    // use cache parameter to allow working in nvmem-less mode
    if (!CME_IS_FAST_CANDIDATE_VALID())//(FS_OK != RetVal)
    {
        GTRACE(GRP_CME, "Fast connection data is invalid");
        CME_PRINT_PROFILE_REPORT("\n\rFast connection data is invalid");
        return 0;
    }

    ASSERT_GENERAL((gCmeFastConnectionCB_ull.cmeFastConnectionSsid!=NULL) && (gCmeFastConnectionCB_ull.cmeFastConnFrame!=NULL));
    if (NULL != apSsid)
    {
        *apSsid = gCmeFastConnectionCB_ull.cmeFastConnectionSsid;
        //restore wpa3
        if(CME_IS_SEC_TYPE_SAE(gCmeFastConnectionCB_ull.cmeFastConnectionSsid->secType))
        {
            gCmeFastConnectionCB_ull.cmeFastConnectionSsid->passphrase = (char*)gCmeFastConnectionCB_ull.cmeFastConnectionSsid->wep_key;
        }
    }

    if (NULL != apCandidateInfo)
    {
        *apCandidateInfo = gCmeFastConnectionCB_ull.cmeFastConnFrame;
    }

//    if (scan_res)
//    {
//        *scan_res = &gFastConnFrame.mScanResult;
//    }
//    if (info_ele)
//    {
//        *info_ele = gFastConnFrame.mInfoElements;
//    }
//    if (profile_id)
//    {
//        *profile_id = gFastConnFrame.mProfileId;
//    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return 1;
}

//
// Fast connection policy Flash Managed APIs
//
int cmeReadFastConnectionDataFromFlash()
{
    FILE *fFastDataFile = NULL;
    int retVal;
    uint32_t cmdSize = sizeof(_cme_minimized_wpa_ssid_t)
                     + sizeof(cmeScanCandidateDesc_t)
                     + sizeof(_cmeFastConnectionStatusLabel_u);
    uint8_t *cmdPayload = NULL;

    fFastDataFile = osi_fopen(".fast", "rb");
    if(!fFastDataFile)
    {
        CME_PRINT_REPORT_ERROR("\n\rERROR: NV failure\n\r");
        ASSERT_GENERAL(0);
        return -1;
    }

    Report("\n\r[FAST NV] Reading fast connection data from FS (size=%d)\n\r", cmdSize);

    cmdPayload = (uint8_t*)os_malloc(cmdSize);
    if (cmdPayload == NULL)
    {
        CME_PRINT_REPORT_ERROR("\n\rFAST ERROR: Cannot allocate memory\n\r");
        osi_fclose(fFastDataFile);
        ASSERT_GENERAL(0);
        return -1;
    }
    
    retVal = osi_fread(cmdPayload, cmdSize, 0, fFastDataFile);
    if (retVal == 0)
    {
        CME_PRINT_REPORT_ERROR("\n\rRead fast data file failed. Doesn't exist.\n\r");
        osi_fclose(fFastDataFile);
        os_free(cmdPayload);
        return -1;
    }
    
    //copy contents
    os_memcpy(gCmeFastConnectionCB_ull.cmeFastConnectionSsid, cmdPayload, sizeof(_cme_minimized_wpa_ssid_t));

    os_memcpy(gCmeFastConnectionCB_ull.cmeFastConnFrame,
                cmdPayload + sizeof(_cme_minimized_wpa_ssid_t),
                sizeof(cmeScanCandidateDesc_t));

    os_memcpy(&gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel, 
                cmdPayload + sizeof(_cme_minimized_wpa_ssid_t) + sizeof(cmeScanCandidateDesc_t), 
                sizeof(_cmeFastConnectionStatusLabel_u));
                
    osi_fclose(fFastDataFile);
    os_free(cmdPayload);
    return 0;
}


int cmeWriteFastConnectionDataToFlash()
{
    FILE *fFastDataFile = NULL;
    int retVal;
    uint32_t cmdSize = sizeof(_cme_minimized_wpa_ssid_t)
                            + sizeof(cmeScanCandidateDesc_t)
                            + sizeof(_cmeFastConnectionStatusLabel_u);

    uint8_t *cmdPayload = NULL;

    fFastDataFile = osi_fopen(".fast", "wb");
    if(!fFastDataFile)
    {
        CME_PRINT_REPORT_ERROR("\n\rERROR: NV Failure\n\r");
        ASSERT_GENERAL(0);
    }

    cmdPayload = (uint8_t*)os_malloc(cmdSize);
    if (cmdPayload == NULL)
    {
        CME_PRINT_REPORT_ERROR("\n\rFAST ERROR: Cannot allocate memory\n\r");
        osi_fclose(fFastDataFile);
        ASSERT_GENERAL(0);
    }

    Report("\n\r[FAST NV] Writing fast connection data to Flash size=%d\n\r", cmdSize);

    //prepare content
    os_memcpy(cmdPayload, gCmeFastConnectionCB_ull.cmeFastConnectionSsid, sizeof(_cme_minimized_wpa_ssid_t));
    os_memcpy(cmdPayload + sizeof(_cme_minimized_wpa_ssid_t), gCmeFastConnectionCB_ull.cmeFastConnFrame, sizeof(cmeScanCandidateDesc_t));
    os_memcpy(cmdPayload + sizeof(_cme_minimized_wpa_ssid_t) + sizeof(cmeScanCandidateDesc_t), 
                &gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel, sizeof(_cmeFastConnectionStatusLabel_u));
    
    
    retVal = osi_fwrite(cmdPayload, cmdSize, 0, fFastDataFile);
    if (retVal == 0)
    {
        //invalidate fast connection data
        CME_PRINT_REPORT_ERROR("\n\rFAST ERROR: file does not exist\n\r");
        osi_fclose(fFastDataFile);
        os_free(cmdPayload);
        return -1;
    }
    
    osi_fclose(fFastDataFile);
    os_free(cmdPayload);
    return 0;
}

void cmeDeleteFastConnectionDataFromFlash()
{
    FILE *fFastDataFile = NULL;

    Report("\n\r[FAST NV] Deleting fast connection data from Flash\n\r");

    fFastDataFile = osi_fopen(".fast", "rb");

    if(!fFastDataFile)
    {
        CME_PRINT_REPORT_ERROR("\n\rERROR: NV Failure\n\r");
        ASSERT_GENERAL(0);
    }
    else
    {
        if(osi_fremove(fFastDataFile) != OSI_OK)
        {
            CME_PRINT_REPORT_ERROR("\n\rERROR: Fast File remove failed\n\r");
        }
    }
    osi_fclose(fFastDataFile);
}

//
// cmeSaveFastConnectionData
//
// read fast connect files from FS and check if need to be re-written according
// to new parameters learned at last successful connection
//
int cmeSaveFastConnectionData()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    //validate if fast connection is valid
    if( (gCmeConnectionPolicyParams_ull.shouldUseFastConnect)
            &&
        (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectProfileSsidSet == 1)
            &&
         (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectScanFrameSet  == 1))
    {
        //set last profile idx
        CME_VALIDATE_FAST_CANDIDATE();

        GTRACE(GRP_CME, "Fast connection validated successfully ");
        CME_PRINT_PROFILE_REPORT("\n\r Fast connection validated successfully.");

        if (gCmeConnectionPolicyParams_ull.fastPersistent)
        {
            if(cmeWriteFastConnectionDataToFlash() != OSI_OK)
            {
                CME_PRINT_PROFILE_REPORT_ERROR("\n\rERROR: Could not write fast connection data to flash");
            }
        }

    }
    else
    {
        GTRACE(GRP_CME, "Fast connection not validated properly (label=0x%x), invalidating",gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel._w8);
        cmeMarkInvalidFastConnectionData();
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return 0;
}

//
// cmeMarkInvalidFastConnectionData
//
// invalidate fast connection frame to be used in future system bringup
//
int cmeMarkInvalidFastConnectionData()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    GTRACE(GRP_CME, "Invalidating fast connection data (label=0x%x)",gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel._w8);
    CME_PRINT_PROFILE_REPORT("\r\nFast: Invalidating fast connection data (label=0x%x)",gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel._w8);
    /* Note: no need to update SLINK_FILE_FAST_CONNECT_SSID */

    if (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectProfileSsidSet == 1)
    {
        //if only fast connect profile exist - release it

        // Oct 25 - optimizing ad-hoc connect case:
        if (gCmeFastConnectionCB_ull.cmeFastConnectionSsid != NULL)
        {
            if (gCmeFastConnectionCB_ull.cmeFastConnectionSsid != &gAdHocProfile_ull.profile)
            {
                GTRACE(GRP_CME, "Freeing fast connection ssid since it (was) profile connection and NOT ad-hoc");
                //profile connection, we need to free this buffer (if its ad-hoc so its pointing at gAdHocProfile_ull->profile)
                // Only free if it's NOT pointing to the static profile
                os_free(gCmeFastConnectionCB_ull.cmeFastConnectionSsid);
            }
        }
        gCmeFastConnectionCB_ull.cmeFastConnectionSsid = NULL;

    }

    if (gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.fastConnectScanFrameSet == 1)
    {
        //if only fast connect profile exist - release it

        os_free(gCmeFastConnectionCB_ull.cmeFastConnFrame);

        gCmeFastConnectionCB_ull.cmeFastConnFrame = NULL;

    }

    //unset all bits
    gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel._w8 = 0;


    if (gCmeConnectionPolicyParams_ull.fastPersistent)
    {
        cmeDeleteFastConnectionDataFromFlash();
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return 0;

}


// ----------------------------------------------------------------------------
void CME_GetConnectionPolicy(uint8_t* pConnectOpenAp,  // not supported
                             uint8_t* pUseFastConnect,
                             uint8_t* pAutoStart,
                             uint8_t* pConnectAnyP2P, //not supported
                             uint8_t* pFastPersistant) 
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    //avoid preempting this thread wihle reading the connection policy parameters
    //uint32_t old_preempt = osi_DisablePreemption();

    //*pConnectOpenAp     = gCmeConnectionPolicyParams_ull.shouldConnectToOpenAp;
    *pUseFastConnect    = gCmeConnectionPolicyParams_ull.shouldUseFastConnect;
    *pAutoStart         = gCmeConnectionPolicyParams_ull.autoStart;
    //*pConnectAnyP2P     = gCmeConnectionPolicyParams_ull.shouldConnectToAnyP2P;
    *pFastPersistant    = gCmeConnectionPolicyParams_ull.fastPersistent;
    //*pAutoSmartConfig   = gCmeConnectionPolicyParams_ull.autoSmartConfig;
    //*autoProvisioning   = gCmeConnectionPolicyParams_ull.autoProvisioning;

    //restore preemption
    //osi_RestorePreemption(old_preempt);

    GTRACE(GRP_CME, "CME_GetConnectionPolicy: AutoStart=%d , FastConnect=%d",
                 *pAutoStart ,
                 *pUseFastConnect);
    CME_PRINT_PROFILE_REPORT("\n\r CME_GetConnectionPolicy: AutoStart=%d , FastConnect=%d, FastPersistant=%d",
                 *pAutoStart ,
                 *pUseFastConnect,
                 *pFastPersistant);

}

//
// cmeMngSetConnectionPolicy
//
// connection policy settings from user / http server configuration
// handle fast connect storage in case connection is active, or invalidate already stored fast connection
// eventually, call profile manager re-evaluation to see if the new policies might affect the current connection method
//
// Setting policy and writing to flash is now from the dispatcher context. All the rest remains in cme.
void cmeMngSetConnectionPolicy(uint8_t   should_connect_to_any_p2p_device,
                               uint8_t   should_connect_to_open_ap,
                               uint8_t   should_use_fast_connect,
                               uint8_t   auto_start,
                               uint8_t   fast_persistant)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    gCmeConnectionPolicyParams_ull.shouldUseFastConnect = should_use_fast_connect;
    gCmeConnectionPolicyParams_ull.shouldConnectToOpenAp = 0; //not supported
    gCmeConnectionPolicyParams_ull.shouldConnectToAnyP2P = 0; //not supported
    gCmeConnectionPolicyParams_ull.autoStart = auto_start;
    gCmeConnectionPolicyParams_ull.fastPersistent = fast_persistant;

//    gCmeConnectionPolicyParams_ull.autoSmartConfig = auto_smart_config;
//    gCmeConnectionPolicyParams_ull.autoProvisioning = auto_provisioning;


    GTRACE(GRP_CME,"cmeMngSetConnectionPolicy: AutoStart=%d , FastConnect=%d , OpenAP=%d, ShouldConnectToAnyP2P=%d, ",
                    auto_start ,should_use_fast_connect, 0, 0);
    CME_PRINT_REPORT("\n\rcmeMngSetConnectionPolicy: AutoStart=%d , FastConnect=%d , OpenAP=%d, ShouldConnectToAnyP2P=%d, fastPersistant=%d",
                    auto_start ,should_use_fast_connect, 0, 0,
                    fast_persistant);

    //write new configuration to flash according to persistent configuration
    SetConnectionPolicy_SetToFlash(TRUE);
}

int cmeMngConnectionPolicyUpdated(uint8_t should_use_fast_connect)
{
//    int old_fast;
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int RetVal = 0;

    struct wpa_supplicant *wpa_s = NULL;

    // Get STA/P2P CL role is valid and select the correct iface
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);
    //
    //in case of invalidating the fast connect-see if buffers were allocated , free them and invalidate the indication flags
    //
    if (//(TRUE == old_fast) &&
       (FALSE == should_use_fast_connect))
    {
        RetVal |= cmeMarkInvalidFastConnectionData();
    }

    //  as part of the fast connect new intermittent module, set of fast-connect shouldnt
    //  store the current network, but will only apply for next time.
    //  so just see if profile manager shold be revisited
    //
    if ( !((wpa_s != NULL) &&
        (WPA_COMPLETED == wpa_s->wpa_state))
        )
    {
        cmeProfileManagerConfigChange(0, CALLER3);//wlan_apply_policy_upon_config_change();
    }
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return RetVal;
}

int cmeMngUpdateProfileKeyMgmt(int8_t index, int new_key_mgmt, int new_pmf)
{
    //overwrithe DB only 
    gPreferredNetworks[index].profile.key_mgmt = new_key_mgmt;
    gPreferredNetworks[index].profile.ieee80211w = new_pmf;

    return 0;
}

int cmeCheckCurrentIsTransitionMode()
{
    //get the connected profile details
    if (CME_INVALID_PROFILE_ID != gAdHocProfile_ull.uniqueProfileId)
    {
        //this is an ad-hoc connection
        if (CME_IS_SEC_TYPE_TRANSITION_MODE(gAdHocProfile_ull.profile.secType))
        {
            CME_PRINT_REPORT("\n\rcmeCheckCurrentIsTransitionMode: connected to a profile index=%d", gConnectingIndex_ull);
            
            if(CMEIsWPA3TransitionModeDisabled(gAdHocProfile_ull.profile.key_mgmt,
                                               gAdHocProfile_ull.profile.id))
            {
                //update AD-hoc profile data
                gAdHocProfile_ull.profile.key_mgmt = WPA_KEY_MGMT_SAE;
                gAdHocProfile_ull.profile.ieee80211w = MGMT_FRAME_PROTECTION_REQUIRED;
            }
        }
    }
    else
    {
        //this is a profile connection
        int profile_id = gPreferredNetworks[gConnectingIndex_ull].profile.id;
        int key_mgmt   = gPreferredNetworks[gConnectingIndex_ull].profile.key_mgmt;

        if (CME_IS_SEC_TYPE_TRANSITION_MODE(gPreferredNetworks[gConnectingIndex_ull].profile.secType))
        {
            CME_PRINT_REPORT("\n\rcmeCheckCurrentIsTransitionMode: connected to a profile index = %d", gConnectingIndex_ull);
            
            if(CMEIsWPA3TransitionModeDisabled(key_mgmt, profile_id))
            {
                //update profile data
                cmeMngUpdateProfileKeyMgmt(gConnectingIndex_ull,
                                                         WPA_KEY_MGMT_SAE,
                                                         MGMT_FRAME_PROTECTION_REQUIRED);
            }
        }

    }
    return 0;
}

BOOLEAN cmeAPIsPeerConnected(u8 *macAddr)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);
#ifdef CONFIG_AP
    struct wpa_supplicant *pApInterface;
    struct hostapd_data *hapd;
    struct sta_info *sta = NULL;

    GTRACE(GRP_CME,"cmeAPIsPeerConnected: MacAddr = %.2X-%.2X-%.2X-%.2X-%.2X-%.2X",
           macAddr[0],
           macAddr[1],
           macAddr[2],
           macAddr[3],
           macAddr[4],
           macAddr[5]);

    pApInterface = drv_getIfaceFromRoleID(gpSupplicantGlobals, drv_getRoleIdFromType(gpSupplicantGlobals,ROLE_AP));

    if (pApInterface)
    {
        hapd = pApInterface->ap_iface->bss[0];

        if (hapd)
        {
            sta = ap_get_sta(hapd, macAddr);

            if (sta)
            {
                GTRACE(GRP_CME,"cmeAPIsPeerConnected: Peer is connected to AP");
                return TRUE;
            }
        }
        else
        {
            GTRACE(GRP_CME,"cmeAPIsPeerConnected: WARNING!! ap_iface->bss is empty!");
        }
    }
    else
    {
        GTRACE(GRP_CME,"cmeAPIsPeerConnected: WARNING!! No AP Interface found!");

    }

    GTRACE(GRP_CME,"cmeAPIsPeerConnected: Peer is not connected to AP.");

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return FALSE;
#endif

    return TRUE;
}


int16_t cmeGetNumStaConnected(u8 *numStaConnected)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

#ifdef CONFIG_AP
    struct wpa_supplicant *pApInterface;
    struct hostapd_data *hapd;
    uint16_t retVal = -1;
    RoleID_t    roleId;

    *numStaConnected = 0;

    roleId = drv_getRoleIdFromType(gpSupplicantGlobals,ROLE_AP);

    if (roleId != ROLE_ID_NONE)
    {
        pApInterface = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);

        if (pApInterface)
        {
            hapd = pApInterface->ap_iface->bss[0];

            if (hapd)
            {
                *numStaConnected = hapd->num_sta;
                retVal = 0;
            }
        }
    }
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return retVal;
#endif
    return 0;
}


int cmeGetStaAddr(int index, unsigned char *sta_mac_addr, unsigned int *sta_ip_addr)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);
#ifdef CONFIG_AP
    struct wpa_supplicant *pApInterface;
    struct hostapd_data *hapd;
    RoleID_t    roleId;
    int i;

    roleId = drv_getRoleIdFromType(gpSupplicantGlobals,ROLE_AP);

    if (roleId != ROLE_ID_NONE)
    {
        pApInterface = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);

        if (pApInterface)
        {
            hapd = pApInterface->ap_iface->bss[0];

            if ((hapd) && (index >= 0) && (index < hapd->conf->max_num_sta))
            {
                struct sta_info *sta = hapd->sta_list;

                // Go through the AP STAs link list until reaching the requiered index
                for (i=0; i<index && sta != NULL; i++)
                {
                    sta = sta->next;
                }

                // Get the STA MAC address
                if (sta != NULL)
                {
                    os_memcpy(sta_mac_addr, sta->addr, 6);
                    if (sta_ip_addr)
                    {
                        *sta_ip_addr = sta->ipaddr;
                    }
                    return 0;
                }
            }

            // STA not found, return zero MAC
            os_memset(sta_mac_addr, 0, 6);
            return 0;
        }
        else
        {
            GTRACE(GRP_GENERAL_ERROR, "cmeGetStaAddr: FATAL ERROR!! No AP interface detected.");
            ASSERT_GENERAL(0);
        }
    }
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return -1;
#endif
    return 0;
}


// TODO need implementation
#if 0
int cmeApNetCfgStaInfo(int sta_index, SlNetCfgStaInfo_t *pApStaInfo)
{
    int status;
    unsigned int ip_addr=0;

    status = cmeGetStaAddr(sta_index, pApStaInfo->MacAddr, &ip_addr);
    if (status != SL_RET_CODE_OK)
    {
        return SL_ERROR_STATUS_ERROR;
    }

    // extract IP address from DHCP server
    status = netApp_Ip4_dhcp_server_get_info_by_mac(NX_IFC_AP, pApStaInfo->MacAddr, (unsigned int *)&pApStaInfo->Ip, pApStaInfo->Name);
    if (status != NX_SUCCESS)
    {
        // No IP from DHCP server, check if there is static IP from ARP table
        if (ip_addr == 0)
        {
            strcpy((char *)pApStaInfo->Name, "Unknown IP");
        }
        else
        {
            pApStaInfo->Ip = ip_addr;
            strcpy((char *)pApStaInfo->Name, "Static IP");
        }
        pApStaInfo->Status = 0;
        return SL_STATUS_OK;
    }

    pApStaInfo->Status = NET_CFG_STA_INFO_STATUS_DHCP_ADDR;

    return SL_STATUS_OK;
}
#endif

void cmeApRemoveAllPeers(struct hostapd_data *hapd, BOOLEAN isUserReq)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    u8 addr[ETH_ALEN];
   // SlWlanAsyncResponse_t AsyncEventResp;

    if (hostapd_drv_none(hapd) || hapd->drv_priv == NULL)
    {
        GTRACE(GRP_CME,"cmeApRemoveAllPeers: Warnning! hapd is not valid!");
        CME_CON_PRINT("\n\rcmeApRemoveAllPeers: Warnning! hapd is not valid!");
        return;
    }

    GTRACE(GRP_CME,"cmeApRemoveAllPeers: Deauthenticate all stations!!");
    CME_CON_PRINT("\n\rcmeApRemoveAllPeers: Deauthenticate all stations!!");
    os_memset(addr, 0xff, ETH_ALEN);
    hostapd_drv_sta_deauth(hapd, addr, WLAN_REASON_DEAUTH_LEAVING);
    hostapd_free_stas(hapd);

    // TODO need implementation
#if 0
    /* process completed successfully */
    if (isUserReq)
    {
        AsyncEventResp.Status = SL_STATUS_OK;

        sl_host_timeout_notify_process_completed(
                HOST_API_TIMEOUT_ID_WLAN_AP_REMOVE_PEER,
                (uint8_t*)&AsyncEventResp, sizeof(SlWlanAsyncResponse_t));
    }
#endif
}


//-----------------------------------------------------------------------------
void cmeApRemovePeer(uint8_t *macAddr, BOOLEAN isUserReq)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

#ifdef CONFIG_AP
    struct wpa_supplicant *pApInterface;
    struct hostapd_data *hapd;
    struct sta_info *sta = NULL;
    BOOLEAN isBroadcastMac = FALSE;

    GTRACE(GRP_CME,"AP Remove Peer Kicked. isUserReq=%d", isUserReq);

    uint32_t roleId = drv_getRoleIdFromType(gpSupplicantGlobals,ROLE_AP);
    pApInterface = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);

    GTRACE(GRP_SL_DISPATCH,"cmeApRemovePeer: MacAddr = %.2X-%.2X-%.2X-%.2X-%.2X-%.2X",
           macAddr[0],
           macAddr[1],
           macAddr[2],
           macAddr[3],
           macAddr[4],
           macAddr[5]);

    if (pApInterface)
    {
        hapd = pApInterface->ap_iface->bss[0];
    }
    else
    {
        GTRACE(GRP_CME,"cmeApRemovePeer: FATAL ERROR!! No AP interface detected.");
        ASSERT_GENERAL(0);
    }

    if (!hapd)
    {
        GTRACE(GRP_CME,"cmeApRemovePeer: FATAL ERROR!! No AP bss detected.");
        ASSERT_GENERAL(0);
    }

    // Broadcast like MAC - deauthenticate all stations 
    isBroadcastMac = is_broadcast_ether_addr(macAddr);

    if (cmeAPIsPeerConnected(macAddr))
    {
        sta = ap_get_sta(hapd, macAddr);

        if (sta)
        {
            GTRACE(GRP_CME,"cmeApRemovePeer: Disconnecting Peer");
            ap_sta_disconnect(hapd, sta, macAddr, WLAN_DISCONNECT_AP_REMOVE_PEER);
        }
        else
        {
            GTRACE(GRP_CME,"cmeApRemovePeer: No STA to remove!");
        }

        // Save the last peer removed.. 
        os_memcpy(gPeerRemovedMacAddr_ull, macAddr, MAC_ADDR_LEN);
    }
    else
    {
       // Broadcast like MAC - deauthenticate all stations
       if (isBroadcastMac)
       {
           GTRACE(GRP_CME,"cmeApRemovePeer: Call cmeApRemoveAllPeers");
           cmeApRemoveAllPeers(hapd, isUserReq);
           return;
       }
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);
#endif
}
// ----------------------------------------------------------------------------

void cmeWlanConnect(uint32_t aRoleId, CMEWlanConnectCommon_t *apCmd, CMEEapWlanConnect_t *apEapCmd, uint32_t aKeyMgmt, uint8_t profiles_connection)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    //int32_t  profileId;
	RoleType_e role = drv_getRoleTypeFromRoleId(gpSupplicantGlobals, aRoleId);
	struct wpa_supplicant  *wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, aRoleId);
	CMEWlanAddGetProfile_t  cmd;
 
    _cme_minimized_wpa_ssid_t *pSsid = NULL;
    cmeScanCandidateDesc_t *pFastCandidate = NULL;

    Bool_e isReassociate = FALSE;

	ASSERT_GENERAL((apCmd!= NULL) || (apEapCmd!=NULL));


	//indexing of the connecting profile - relevant for profile search only
	gConnectingIndex_ull = CONN_ATTEMPT_INVALID_IDX;
	//clear consecutive scan complete counter
	gConnSecutiveScanCompletes_ull = 0;

    if (NULL != gCandidatesInfo.pCandidateScanResults)
    {
        if (((isextWPS() && ((apCmd->SecType == CME_SEC_TYPE_WPS_PBC) ||
                            (apCmd->SecType == CME_SEC_TYPE_WPS_PIN) ||
                            isextWPSDone())))
            || (TRUE == gSaveCurrentSupplicantProfile)) //if it's a reconnect to the same network, do not release
        {
            // Don't release the scan results in external WPS mode, when WPS connection is required or has completed.
            // This allows the supplicant to skip scanning if the BSS already in the scan results
        }
        else
        {
            CME_PRINT_REPORT("\n\rCME:CME_ReleaseScanResults");
            CME_ReleaseScanResults(CALLER1); //Make sure we don't have any leftovers from previous scan.
        }
    }
    

    GTRACE(GRP_CME, "cmeWlanConnect: roleId=%d, secType=%d, keyMgmt=0x%x, profiles_connection=%d", 
                        aRoleId, apCmd->SecType, aKeyMgmt, profiles_connection);
    if(apCmd != NULL)
    {
        CME_CON_PRINT("\n\rcmeWlanConnect: roleId=%d, secType=%d, keyMgmt=%d, profiles_connection=%d",
                        aRoleId, apCmd->SecType, aKeyMgmt, profiles_connection);
    }
    else
    {
        CME_CON_PRINT("\n\rcmeWlanConnect: roleId=%d, secType=%d, keyMgmt=%d, profiles_connection=%d",
                        aRoleId, apEapCmd->EapCommonConnect.SecType, aKeyMgmt, profiles_connection);

    }

	//
	//wlan connect should be called necessarily after previous disconnection
	//

	if (wpa_s->wpa_state > WPA_INACTIVE )
	{
	    GTRACE(GRP_CME, "Error: Connect called when supplicant state is %d", wpa_s->wpa_state);
	}

	if (ROLE_IS_TYPE_STA_BASED(role))
	{
        if (isextWPS())
        {
            if ((apCmd->SecType == CME_SEC_TYPE_WPS_PBC) || (apCmd->SecType == CME_SEC_TYPE_WPS_PIN))
            {
                // Initiate the external WPS connection flow
                extWpsConnect((char*)SSID_STRING(apCmd), apCmd->SsidLen, apCmd->Bssid, apCmd->SecType == CME_SEC_TYPE_WPS_PIN);
                return;
            }
            else if (isextWPSDone())
            {
                // Initiate the external WPS connection after WPS registration.
                // The extWPSDone flag is raised through the WLAN_SET() function in a higer API
                set_extWPSDone(0);
                extWpsConnectAfter((uint8_t*)SSID_STRING(apCmd), apCmd->SsidLen, apCmd->SecType, (uint8_t*)PASSWORD_STRING(apCmd), apCmd->PasswordLen);
                return;
            }
        }

#ifdef CONFIG_WPS
	    if ((apEapCmd==NULL/*non-eap-connect*/) && (apCmd->SecType == CME_SEC_TYPE_WPS_PBC))
	    {
	        GTRACE(GRP_CME, "cmeWlanConnect: Start wps pbc");

	        gWPSfirstDisconnect_ull = FALSE;
	        gWPSkickDisconnect_ull = FALSE;

	        //mark ad hoc connection as WPS but leave SSID empty
	        gAdHocProfile_ull.uniqueProfileId = getUniqueProfileId();
	        gAdHocProfile_ull.profile.ssid_len = 0;
	        //wpa_config_set(&gAdHocProfile_ull.profile, "key_mgmt", "WPS", 0);
	        CME_SET_WPS_AD_HOC_CONNECTION(); //Mark the ad hoc is WPS so the next scan will be for WPS networks
	        gAdHocProfile_ull.profile.secType = CME_SEC_TYPE_WPS_PBC; //Just for completeness, not really used in WPS.

	        //Start wps pbc
	        wpas_wps_start_pbc(wpa_s, NULL, 0, 0);
	    }
	    else if ((apEapCmd==NULL/*non-eap-connect*/) && (apCmd->SecType == CME_SEC_TYPE_WPS_PIN))
	    {
	        uint8_t pin[WPS_PIN_LEN+1];
            uint8_t* pKey;

            if (apCmd->PasswordLen == WPS_PIN_LEN) // Pin supplied
            {
                GTRACE(GRP_CME, "cmeWlanConnect: Start wps pin");

                pKey = (uint8_t *)PASSWORD_STRING(apCmd); //Points to the pin key

                os_memset(pin, 0, sizeof (pin)); //Make sure pin is null terminated
                os_memcpy(pin, pKey, WPS_PIN_LEN);

                gWPSfirstDisconnect_ull = FALSE;
                gWPSkickDisconnect_ull = FALSE;

                //mark ad hoc connection as WPS
                gAdHocProfile_ull.uniqueProfileId = getUniqueProfileId();
                gAdHocProfile_ull.profile.ssid_len = 0;

                CME_SET_WPS_AD_HOC_CONNECTION(); //Mark the ad hoc is WPS so the next scan will be for WPS networks
                gAdHocProfile_ull.profile.secType = CME_SEC_TYPE_WPS_PIN; //Just for completeness, not really used in WPS.

                wpas_wps_start_pin(wpa_s, NULL, (char *) pin, 0, DEV_PW_DEFAULT);
            }
            else
            {
                GTRACE(GRP_CME, "ERROR: WPS PIN was NOT supplied or the pin length is different then 8!");
                wlanDispatcherSendEvent(WLAN_EVENT_WPS_INVALID_PIN, NULL, 0);
            }
        }
	    else if (shouldUseFastConnect(&pSsid,&pFastCandidate,apCmd,apEapCmd,profiles_connection))
	    {
#else//NOT CONFIG_WPS
	    if (shouldUseFastConnect(&pSsid,&pFastCandidate,apCmd,apEapCmd,profiles_connection))
	    {
#endif//CONFIG_WPS
	        // fast connect policy set + fast connection exist
	        ASSERT_GENERAL(NULL != pSsid);
	        ASSERT_GENERAL(NULL != pFastCandidate);

            //
            //make sure STA flow SM is back to idle before issuing FAST_CONNECT flow
            //
	        CME_PRINT_STATE_CHNGE_REPORT("\n\r cmeWlanConnect change state to :CME_STA_WLAN_DISCONNECT_COMPLETE_EVENT !!");

            if (0 != CmeStationFlowSM(CME_STA_WLAN_DISCONNECT_COMPLETE_EVENT,CmeStationFlow_GetCurrentUser()))
            {
                GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set sta result found in STA flow SM and failed!! ");
                ASSERT_GENERAL(0);
            }

	        // Push fast candidate to scan results DB. From this point it shall
	        // be treated in the system (mainly driver_cc) as valid result.
	        cmePushFast2ScanResult(pFastCandidate);


	        //
	        // store the connection in the pending element for case where fast connect fails and we wish to fallback to regular wlan_connect
	        //

            //Copy the command to a local buffer pending for case that fast connection fails
	        cmePendingWlanConnectStor(apCmd,apEapCmd,aKeyMgmt,profiles_connection);
            //

	        //trigger fast connect attempt:
	        cmeFastConnectAttempt(wpa_s, pSsid, 1);

	        //dont free the apCmd and apEapCmd in this case, will be released when fast connect completes
	        return;
	    }
	    else if (profiles_connection)
	    {

	        GTRACE(GRP_CME,"CME: cmeWlanConnect(); use profiles connection !! move state to CME_STA_WLAN_DISCONNECT_COMPLETE_EVENT!! ");
            CME_PRINT_REPORT("\n\rCME: cmeWlanConnect(); use profiles connection");         
            
#if 0       //initial example - why?
            //
            //make sure STA flow SM is back to idle before issuing AUTO_CONNECT flow
            //
            if (0 != CmeStationFlowSM(CME_STA_WLAN_DISCONNECT_COMPLETE_EVENT,CmeStationFlow_GetCurrentUser()))
            {
                GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set sta result found in STA flow SM and failed!! ");
                ASSERT_GENERAL(0);
            }
	        //issue one-time profiles connection
	        cmeProfileManagerConfigChange(1/*force profile-search*/, CALLER6);
#else
           //read preferred network from flash
           cmeMngReadPreferredNetworkFromFlash();

            //read index from command
            uint8_t index = apCmd->SecType;

            //Just make sure we don't have any leftovers from the previous ad-hoc connection
            if (gAdHocProfile_ull.profile.passphrase != NULL)
	        {
	            os_free (gAdHocProfile_ull.profile.passphrase);
	            gAdHocProfile_ull.profile.passphrase = NULL;
	        }

	        //clear ad hoc connection profile db before loading from flash
	        memset(&gAdHocProfile_ull, 0, sizeof(cmeProfileInfo_t));
	        gAdHocProfile_ull.profile.id =  CME_INVALID_PROFILE_ID;
	        gAdHocProfile_ull.uniqueProfileId = CME_INVALID_PROFILE_ID;
	        gAdHocProfile_ull.profile.eap.eap_entProfileIndex = CME_INVALID_ENT_IDX;  
            gAdHocProfile_ull.p2pProfile = P2P_NONE;

            //copy profile to ad-hoc profile
            cmeCopyProfileToAdHocProfile(index);

            // Mark this entry is in use
            gAdHocProfile_ull.uniqueProfileId = getUniqueProfileId();

            CME_CON_PRINT("\n\rAdded from profile index %d to ad-hoc profile (unique ID %d) Security type %d",
                    index, gAdHocProfile_ull.uniqueProfileId, gAdHocProfile_ull.profile.secType);
                
            wpa_bss_flush(wpa_s);
            wpa_s->cc33xx_initiated_select_network = 1;
            wpa_supplicant_select_network(wpa_s, NULL);
            CME_PRINT_REPORT("\n\rCME:wpa_supplicant_select_network done\n\r");
#endif
        }
	    else
	    {//non-wps non-fast connection (just a regular ad-hoc)


	        GTRACE(GRP_CME,"CME: cmeWlanConnect(); ad-hoc connect !! ");
            CME_PRINT_REPORT("\n\rCME: cmeWlanConnect(); ad-hoc connect !! \n");

            //Just make sure we don't have any leftovers from the previous ad-hoc connection
            if (gAdHocProfile_ull.profile.passphrase != NULL)
	        {
	            os_free (gAdHocProfile_ull.profile.passphrase);
	            gAdHocProfile_ull.profile.passphrase = NULL;
	        }

	        //clear ad hoc connection profile db before loading from flash
	        memset(&gAdHocProfile_ull, 0, sizeof(cmeProfileInfo_t));

	        gAdHocProfile_ull.profile.id =  CME_INVALID_PROFILE_ID;
	        gAdHocProfile_ull.uniqueProfileId = CME_INVALID_PROFILE_ID;
	        //gAdHocProfile_ull.profile.ssid = gAdHocProfile_ull.ssid;//ssid will be staticly allocated in profiles
	        gAdHocProfile_ull.profile.eap.eap_entProfileIndex = CME_INVALID_ENT_IDX;     

	        if (apEapCmd!=NULL)
            {
	            //EAP connection

	            GTRACE(GRP_CME, "cmeWlanConnect: Start eap connection");
                CME_PRINT_REPORT("\n\rCME: EAP connection");

                // Set network parameters to the add profile structure
                cmd.PasswordLen = apEapCmd->EapCommonConnect.PasswordLen;
                cmd.SecType = apEapCmd->EapCommonConnect.SecType;
                cmd.SsidLen = apEapCmd->EapCommonConnect.SsidLen;
                cmd.FastTransition = apEapCmd->EapCommonConnect.FastTransition;
                // ad-hoc connection has non priority, set here from CME instead
                cmd.Priority = 1;
                IRQ_UtilCopyMacAddress((uint8_t *)apEapCmd->EapCommonConnect.Bssid, (uint8_t *)&cmd.Bssid);

                // As in cc3100, set WepKeyId to 0 - TODO - should be available in connect command
                cmd.WepKeyId = 0;

                addAdHocProfile2DB(&cmd, aKeyMgmt, EAP_SSID_STRING(apEapCmd), EAP_PASSWORD_STRING(apEapCmd), P2P_NONE, apEapCmd);
            }
	        else if (apCmd != NULL)
	        {
	            GTRACE(GRP_CME, "cmeWlanConnect: Start connection");
	            CME_PRINT_REPORT("\n\rCME: cmeWlanConnect: Start connection");

                // Set network parameters to the add profile structure
                cmd.PasswordLen = apCmd->PasswordLen;
                cmd.SecType = apCmd->SecType;
                cmd.SsidLen = apCmd->SsidLen;
                cmd.FastTransition = apCmd->FastTransition;
                // ad-hoc connection has non priority, set here from CME instead
                cmd.Priority = 1;
                IRQ_UtilCopyMacAddress((uint8_t *)apCmd->Bssid, (uint8_t *)&cmd.Bssid);

                // As in cc3100, set WepKeyId to 0 - TODO - should be available in connect command
                cmd.WepKeyId = 0;

                addAdHocProfile2DB(&cmd, aKeyMgmt, SSID_STRING(apCmd), PASSWORD_STRING(apCmd), P2P_NONE,NULL);

	        }
	        else
	        {
	            ASSERT_GENERAL(0);//command must have at least one of the pointers
	        }

	        // If the connection candidate wasn't a candidate in the last connection
	        // supplicant scan results should be flushed. Otherwise, supplicant
	        // issues a periodic scan and immediately after a one shot scan.
	        // We'd like to avoid these two concurrent scans.
            GTRACE(GRP_CME, "Connecting to a new network, flushing supplicant scan result");
            CME_PRINT_REPORT("\n\rCME:Connecting to a new network,flushing supplicant scan result");
            wpa_bss_flush(wpa_s);


	        // ================================================================
	        //  The below Kicks supplicant connection the below logic is used:
	        //      - reset supplicant scan state (to INITIAL_SCAN_REQ)
	        //        this allows supplicant to start scanning even when there
	        //        aren't any enabled profiles.
	        //        See scan condiftions in scan.c, wpa_supplicant_scan:
	        //              if (!wpa_supplicant_enabled_networks(wpa_s) && wpa_s->scan_req == NORMAL_SCAN_REQ)
	        //      - invoke supplicant select API with NULL (meaning any) SSID.
	        //      - supplciant starts a one shot scan
	        //      - when scan successfully completes (and there's a valid scan
	        //        result, the related profile is added to supplicant DB and
	        //        only then the result is forwarded to supplicant and
	        // ================================================================

            //wpa_s->scan_req = INITIAL_SCAN_REQ; //TODO: temp - to remove
            // cc33xx initiated connection
            wpa_s->cc33xx_initiated_select_network = 1;
            //TODO: set 'wpa_s->scan_min_time' to 0 or get current rel time?
            CME_PRINT_REPORT("\n\rCME:wpa_supplicant_select_network");
            wpa_supplicant_select_network(wpa_s, NULL);
            CME_PRINT_REPORT("\n\rCME:wpa_supplicant_select_network done");
	    }
	}

#ifndef TI_STA_ONLY_BUILD
	else if (ROLE_IS_TYPE_DEVICE(role))
	{

        cmeHandleP2pConnection(apCmd, aKeyMgmt);

        if (gCmeP2pInfo.p2pConnectPending != FALSE)
        {
            //do not delete apCmd since p2p connect is pending
            return;
        }
	}
#endif

	// Everything done, free the connection info memory

	if (apEapCmd!=NULL)
    {
	    os_free(apEapCmd);
	    os_free(apCmd);
    }
	else
    {
	    os_free(apCmd);
    }
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

}

// ----------------------------------------------------------------------------
/* ----------------------------------------------------------------------------
 cmeWlanDisconnect
    Handle disconnection command

 Parameters:    none
 Return code:   0 - if disconnect completely served (was in < AUTHENTICATED state)
                1 - if deauth sent and wpa disconnect event is pending (was in > AUTHENTICATED state)
---------------------------------------------------------------------------- */
uint8_t cmeWlanDisconnect(int reason_code)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

	RoleType_e role;
	struct wpa_supplicant *wpa_s;
	uint8_t rc = 0;
    ti_driver_ifData_t *pDrv = NULL;

    GTRACE(GRP_CME, "CME: cmeWlanDisconnect with reason = %d", reason_code);
	// Get STA/P2P CL role is valid and select the correct iface
	role = drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    //save reason code
	pDrv->deauthReason = reason_code;

    // The code below was taken from ctrl_interface.c.
	// wpa_supplicant_ctrl_iface_process handling for DISCONNECT command.
	wpa_s->reassociate = 0;
	wpa_s->disconnected = 1;
	wpa_s->cc33xx_initiated_select_network = 0;

	// cc3100 code ------------------------------------------------------------
	// PTC_BYPASS(PTC_BYPASS_IN_SUPPL_WLAN_DISCONNECT);
	// Bug: MCS00087594: reset the scan counter used for interval of 10 seconds after the 4 scans
    // gRescanCount = 0;

    //	M_CLEAR_PREF_NETWORKS_LIST_CACHE();
    //	gWlanConnectCmd = FALSE;

	// ilya: here, if Fast connect is configured, clean it's data.
    //	if(TRUE == gEPROMShadowParams.shouldUseFastConnect)
    //	{
    //		markInvalidFastConnectionData();
    //	}
	// cc3100 code ------------------------------------------------------------

#if 0 // role p2p
	if (ROLE_IS_TYPE_P2P(role))
	{
//		p2p_go_autonomous_mode = 0;
//
//		int role = wilink_get_drv_role();
//		notifyP2PconnectState(3,NULL,NULL);
//		wpas_p2p_stop_find(wpa_s);
//		wpas_p2p_disconnect(wpa_s);
//
//		if (role==TIWDRV_ROLE_TYPE_P2PGO)
//		{
//			wlan_apply_policy_upon_reset_disconn();
//		}
		// TODO - add P2P support
		ASSERT_GENERAL(0);
	}
   else
#endif

	//stop scan, and get result
	//if result is 1 - we wait for SCAN_COMPLETE
	//so we will notify back that DISCONECTING state will be set
	//until end of scan
	rc = drv_stopConnectionScans(wpa_s);
    //GTRACE(GRP_CME, "drv_stopConnectionScans ret = %d", rc);
    //CME_PRINT_REPORT("\r\ndrv_stopConnectionScans ret = %d", rc);


    //at any case - if state was >scanning, we should wait for WPA_DISCONNECT
	//so we will notify back that DISCONECTING
    //for wpa_s->wpa_state == WPA_SCANNING waits for SCAN_COMPLETE_EVENT_ID from FW
    GTRACE(GRP_CME, "wpa_s->wpa_state = %d, ret = %d (auto_reconnect_disabled=%d)", wpa_s->wpa_state, rc, wpa_s->auto_reconnect_disabled);
    CME_PRINT_REPORT("\r\ncmeWlanDisconnect: wpa_state=%d, drv_stopConnectionScans ret=%d gSaveCurrentSupplicantProfile=%d", 
        wpa_s->wpa_state, rc, gSaveCurrentSupplicantProfile);

    if (wpa_s->wpa_state >= WPA_SCANNING)
    {
        rc = 1;
    }
       

    wpa_supplicant_deauthenticate(wpa_s, reason_code);
    


	   // TODO - handle profiles based connection supplicant profiles

	   // cc3100 code ------------------------------------------------------------
//		enum wps_request_type req_type;
//
//		// If auto-start in on, connect from preferred network, otherwise, just try to do a fast connection if set.
//		if (wpa_supplicant_wps_in_use(&req_type))
//		   wpas_wps_cancel(wpa_s);

//	   if (wpa_s->wpa_state > WPA_SCANNING)
//	   {
//		   SOC_TRACE3(DBG_MSG, MSG_883, "SimpleManager: wlan_disconnect: wpa_state = %1, %2, line = %d", wpa_s->wpa_state, DBG_deauthenticate, __LINE__);
//		   wpa_supplicant_deauthenticate(wpa_s, 0);
//	   }
//	   else if(wpa_s->wpa_state == WPA_SCANNING)
//	   {
//		   SOC_TRACE3(DBG_MSG, MSG_883, "SimpleManager: wlan_disconnect: wpa_state = %1, %2, line = %d", wpa_s->wpa_state, DBG_stop_scan, __LINE__);
//		   wpa_supplicant_set_state(wpa_s,WPA_DISCONNECTED);
//		   wpa_supplicant_stop_scan(wpa_s, __LINE__);
//	   }
//	   else
//	   {
//		   SOC_TRACE3(DBG_MSG, MSG_883, "SimpleManager: wlan_disconnect: wpa_state = %1, %2, line = %d", wpa_s->wpa_state, DBG_do_nothing, __LINE__);
//	   }
	   // cc3100 code ------------------------------------------------------------
   

    // If Fast connect is configured, clean it's data.
	//CC3300 - wlan disconnect doesnt mean that fast connect data shouldnt be kept
//    if(TRUE == gCmeConnectionPolicyParams_ull.shouldUseFastConnect)
//    {
//        cmeMarkInvalidFastConnectionData();
//    }

	return rc;
}


// ----------------------------------------------------------------------------
//int32_t prepareProfileInfo(cmeScanSharedInfo_t *apSharedInfo)
//{
//    int32_t  rc = 0;
//    uint32_t i, k = 0;
//
//    apSharedInfo->mNumProfiles = 0; // TODO set actual number of profiles
//    apSharedInfo->mIsOpenProfileSupported = CME_OPEN_POLICY_ENABLED;        // TODO - Use open policy is bit
//
//    // TODO - prepare profiles, make sure they're not in the black list
//    for (i=0 ; i<CME_SCAN_MAX_PROFILES ; ++i)
//    {
//        if (TRUE == gPreferredNetworks[i].inUse)
//        {
//            ++apSharedInfo->mNumProfiles;
//        }
//    }
//
//    if (0 != apSharedInfo->mNumProfiles)
//    {
//        uint32_t allocSize = apSharedInfo->mNumProfiles * sizeof(cmeScanProfiles_t);
//        apSharedInfo->mpProfiles = os_malloc(allocSize);
//
//        if (NULL != apSharedInfo->mpProfiles)
//        {
//            GTRACE(GRP_CME, "Allocated %d bytes for %d profiles", allocSize, apSharedInfo->mNumProfiles);
//
//            for (i=0 ; i<CME_SCAN_MAX_PROFILES ; ++i)
//            {
//                if (TRUE == gPreferredNetworks[i].inUse)
//                {
//                    memcpy(apSharedInfo->mpProfiles[k].mSSID,
//                            gPreferredNetworks[i].profile.ssid,
//                            gPreferredNetworks[i].profile.ssid_len);
//                    apSharedInfo->mpProfiles[k].ssid.mHidden = CME_ALL_PROFILES_ARE_HIDDEN;
//                    apSharedInfo->mpProfiles[k].ssid.mPriority = 1;
//                    apSharedInfo->mpProfiles[k].ssid.mSsidLen = gPreferredNetworks[i].profile.ssid_len;
//
//                    if (gPreferredNetworks[i].profile.bssid_set)
//                    {
//                        IRQ_UtilCopyMacAddress(gPreferredNetworks[i].profile.bssid, apSharedInfo->mpProfiles[k].mBssid);
//                    }
//
//                    //advance setting counter
//                    k++;
//                }
//            }
//        }
//        else
//        {
//            GTRACE(GRP_CME, "ERROR, failed to allocated %d bytes for %d profiles", allocSize, apSharedInfo->mNumProfiles);
//            apSharedInfo->mNumProfiles = 0;
//
//            // As we failed to allocate memory for profiles, free also the candidates memory
//            mem_Free_glx(apSharedInfo->mpCandidateScanResults);
//
//            // Set error indication
//            rc = -1;
//        }
//    }
//
//    return rc;
//}

// ----------------------------------------------------------------------------
int32_t prepareProfileInfo(cmeScanSharedInfo_t *apSharedInfo, EScanRequestType aScanType, struct wpa_driver_scan_params *apParams)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int32_t  rc = 0;
    uint32_t i, k = 0;
    cmeScanProfilesParams_t *pProfilesParams;

    // Prepare profiles for the newly starting scan.
    // As one shot & periodic scans may run concurrently touch the profiles of
    // one scan type at a type.
    if (SCAN_REQUEST_CONNECT_PERIODIC_SCAN == aScanType)
    {
        pProfilesParams = &apSharedInfo->mPeriodicProfiles;
    }
    else
    {
        pProfilesParams = &apSharedInfo->mOneShotProfiles;
    }
    pProfilesParams->mNumProfiles = 0;
    pProfilesParams->mpProfiles = NULL;

    // Set scan guidelines on shared info
    apSharedInfo->mIsOpenProfileSupported = gCmeConnectionPolicyParams_ull.shouldConnectToOpenAp;

    //Supplicant scan
    if (gSupplicantInitiatedScanInProgress)
    {
        pProfilesParams->mNumProfiles = apParams->num_ssids;
    }
    //Ad hoc ssid handling (single mpProfile entry)
    else if (CME_INVALID_PROFILE_ID != gAdHocProfile_ull.uniqueProfileId)
    {
       ++pProfilesParams->mNumProfiles;
    }
    else
    {
        //read preferred network from FS now if not previously read
        cmeMngReadPreferredNetworkFromFlash();

        apSharedInfo->mIsProfileListExist = 0;

        //profile search handler
        for (i=0 ; i<CME_SCAN_MAX_PROFILES ; ++i)
        {

            if (    (CME_INVALID_PROFILE_ID != gPreferredNetworks[i].uniqueProfileId)
                 && (0 == isBlackListed(i)) )
            {
                ++pProfilesParams->mNumProfiles;

                apSharedInfo->mIsProfileListExist = 1;
            }
        }

        if (apSharedInfo->mIsOpenProfileSupported)
        {
            ++pProfilesParams->mNumProfiles; // One extra slot for broadcast entry.
        }
    }

    if (0 != pProfilesParams->mNumProfiles)
    {
        HOOK(HOOK_IN_CME_CONNECTION_MNG);

        uint32_t allocSize = pProfilesParams->mNumProfiles * sizeof(cmeScanProfiles_t);

        pProfilesParams->mpProfiles = os_zalloc(allocSize);

        if (NULL != pProfilesParams->mpProfiles)
        {
            GTRACE(GRP_CME, "Allocated %d bytes for %d profiles list; memory 0x%x, ENUM(EScanRequestType, %d)",
                   allocSize, pProfilesParams->mNumProfiles, (uint32_t)pProfilesParams->mpProfiles, aScanType);

            //Supplicant scan
            if (gSupplicantInitiatedScanInProgress)
            {
                for (int i = 0; i < apParams->num_ssids; i++)
                {
                    if(apParams->ssids[i].ssid_len > 0)
                    {
                        pProfilesParams->mpProfiles[i].ssid.mSsidLen = apParams->ssids[i].ssid_len;

                        os_memcpy(pProfilesParams->mpProfiles[i].mSSID,
                                            apParams->ssids[i].ssid,
                                            apParams->ssids[i].ssid_len);
                        
                        pProfilesParams->mpProfiles[i].ssid.mHidden = SSID_TYPE_HIDDEN;

                        if (NULL != apParams->bssid)
                        {
                            IRQ_UtilCopyMacAddress(apParams->bssid, pProfilesParams->mpProfiles[i].mBssid);
                        }
                    }

                    GTRACE(GRP_CME, "Profile %d: SSID %s, SSID len %d, BSSID " MACSTR,
                                 i,
                                 pProfilesParams->mpProfiles[i].mSSID,
                                 (uint32_t)pProfilesParams->mpProfiles[i].ssid.mSsidLen,
                                 MAC2STR(pProfilesParams->mpProfiles[i].mBssid));
                }
            }
            //Ad hoc ssid handling (single mpProfile entry)
            else if (CME_INVALID_PROFILE_ID != gAdHocProfile_ull.uniqueProfileId)
            {
                HOOK(HOOK_IN_CME_CONNECTION_MNG);

                os_memcpy(pProfilesParams->mpProfiles[k].mSSID,
                       gAdHocProfile_ull.profile.ssid,
                       gAdHocProfile_ull.profile.ssid_len);

#if GRP_CME
                if (gAdHocProfile_ull.profile.ssid_len < DOT11_SSID_MAX_LEN)
                {
                    pProfilesParams->mpProfiles[k].mSSID[gAdHocProfile_ull.profile.ssid_len] = 0; //for debug traces
                }
#endif
                pProfilesParams->mpProfiles[k].ssid.mHidden = CME_ALL_PROFILES_ARE_HIDDEN;
                pProfilesParams->mpProfiles[k].ssid.mPriority = 1;
                pProfilesParams->mpProfiles[k].ssid.mSsidLen = gAdHocProfile_ull.profile.ssid_len;
                pProfilesParams->mpProfiles[k].mProfileId = gAdHocProfile_ull.uniqueProfileId;
                pProfilesParams->mpProfiles[k].secType = gAdHocProfile_ull.profile.secType;

                IRQ_UtilCopyMacAddress(gAdHocProfile_ull.profile.bssid, pProfilesParams->mpProfiles[k].mBssid);

                GTRACE(GRP_CME, "Profile unique ID %d, SSID %s, SSID len %d, security type ENUM(CMESecType_e, %d), BSSID " MACSTR,
                                 pProfilesParams->mpProfiles[k].mProfileId,
                                 pProfilesParams->mpProfiles[k].mSSID,
                                 (uint32_t)pProfilesParams->mpProfiles[k].ssid.mSsidLen,
                                 (CMESecType_e) pProfilesParams->mpProfiles[k].secType,
                                 MAC2STR(pProfilesParams->mpProfiles[k].mBssid));
                //CME_CON_PRINT("\n\rProfile unique ID %d, SSID len %d, security type ENUM(CMESecType_e, %d)",
                //               pProfilesParams->mpProfiles[k].mProfileId,
                //               (uint32_t)pProfilesParams->mpProfiles[k].ssid.mSsidLen,
                //               (CMESecType_e) pProfilesParams->mpProfiles[k].secType);


                // TODO - for ENT (EAP) scan should we fill out something special?
#ifdef SIMULATE_NO_SCAN_RESULTS
                if (gAdHocProfile_ull.numWrongSsid)
                {
                    pProfilesParams->mpProfiles[k].mSSID[0] = 'X';
                    --gAdHocProfile_ull.numWrongSsid;
                }
#endif

                //advance setting counter
                k++;

                //
                // Nov 7 2016 - scan early termination threshold handling - AD HOC CONNECTION case
                //

                //In WPS connection, don't perform early termination anyway. Need to complete the scan and pass all results to supplicant
                //Set only if not in WPS
                if (!CME_IS_ONGOING_WPS_AD_HOC_CONNECTION())
                {
                    cmeScanEarlyTermThresholdSet(apSharedInfo,gCmeConnectionPolicyParams_ull.shouldUseFastConnect,-1/*indicate ad-hoc*/,0/*secured is dont care in this case*/);
                }
            }
            else
            {
                int highest_priority = -1;
                int is_highest_profile_secured = 0;
                //profile search handler
                for (i=0 ; i<CME_SCAN_MAX_PROFILES ; ++i)
                {
                    if ((CME_INVALID_PROFILE_ID != gPreferredNetworks[i].uniqueProfileId)
                       &&                             //validate network not in blacklist
                        (0 == isBlackListed(i)))
                    {
                        os_memcpy(pProfilesParams->mpProfiles[k].mSSID,
                                gPreferredNetworks[i].profile.ssid,
                                gPreferredNetworks[i].profile.ssid_len);
#if GRP_CME
                        if (gPreferredNetworks[i].profile.ssid_len < DOT11_SSID_MAX_LEN)
                        {
                            pProfilesParams->mpProfiles[k].mSSID[gPreferredNetworks[i].profile.ssid_len] = 0; //for debug traces
                        }
#endif
                        pProfilesParams->mpProfiles[k].ssid.mHidden = gPreferredNetworks[i].profile.scan_ssid;
                        pProfilesParams->mpProfiles[k].ssid.mPriority = gPreferredNetworks[i].profile.priority;// Nov 2 2016 bug fix- used to be fixed 1.

                        pProfilesParams->mpProfiles[k].ssid.mSsidLen = gPreferredNetworks[i].profile.ssid_len;
                        pProfilesParams->mpProfiles[k].mProfileId = gPreferredNetworks[i].uniqueProfileId;
                        pProfilesParams->mpProfiles[k].secType = gPreferredNetworks[i].profile.secType;

                        //Isri need to imlement ??IRQ_UtilCopyMacAddress(gPreferredNetworks[i].profile.bssid, pProfilesParams->mpProfiles[k].mBssid);
                        os_memcpy(pProfilesParams->mpProfiles[k].mBssid, gPreferredNetworks[i].profile.bssid, MAC_ADDR_LEN);

                        GTRACE(GRP_CME, "Profile unique ID %d, SSID %s, SSID len %d, security type ENUM(CMESecType_e, %d),  priority %d",
                                         pProfilesParams->mpProfiles[k].mProfileId,
                                         pProfilesParams->mpProfiles[k].mSSID,
                                         (uint32_t)pProfilesParams->mpProfiles[k].ssid.mSsidLen,
                                         (CMESecType_e) pProfilesParams->mpProfiles[k].secType,
                                         gPreferredNetworks[i].profile.priority);

                        CME_CON_PRINT("\n\rProfile unique ID %d, SSID %s, SSID len %d, security type ENUM(CMESecType_e, %d),  priority %d",
                                         pProfilesParams->mpProfiles[k].mProfileId,
                                         pProfilesParams->mpProfiles[k].mSSID,
                                         (uint32_t)pProfilesParams->mpProfiles[k].ssid.mSsidLen,
                                         (CMESecType_e) pProfilesParams->mpProfiles[k].secType,
                                         gPreferredNetworks[i].profile.priority);

                        //mark highest priority out of all list, and its security attribute
                        //two conditions for updating:
                        if (//1 - if highest priority profile first encoutered
                             (gPreferredNetworks[i].profile.priority >  highest_priority)
                             || //OR
                            //2  - if priority was already encountered AND security is ON (for a case where this priority is stored when the security was off)
                             ((gPreferredNetworks[i].profile.priority == highest_priority)
                              && (CME_SEC_TYPE_OPEN != gPreferredNetworks[i].profile.secType))
                           )
                        {
                            highest_priority = gPreferredNetworks[i].profile.priority;
                            is_highest_profile_secured = ((CME_SEC_TYPE_OPEN != gPreferredNetworks[i].profile.secType) ? 1 : 0);
                        }
                        // TODO - for ENT (EAP) scan should we fill out something special?

                        //advance setting counter
                        k++;
                    }
                }

                if (apSharedInfo->mIsOpenProfileSupported)
                {
                    unsigned char broadcastMacAddr[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


                    // Open profile requires sending a broadcast probe request w/o any SSID.
                    //TODO Isri need to implement IRQ_UtilCopyMacAddress(broadcastMacAddr, pProfilesParams->mpProfiles[k].mBssid);
                    os_memcpy(pProfilesParams->mpProfiles[k].mBssid, broadcastMacAddr, MAC_ADDR_LEN);
                    pProfilesParams->mpProfiles[k].ssid.mSsidLen = 0;
                    pProfilesParams->mpProfiles[k].mSSID[0]=0;

                    // Fill remaining parameters as a good practice, they arn't used.
                    pProfilesParams->mpProfiles[k].ssid.mPriority = 15;
                    pProfilesParams->mpProfiles[k].ssid.mHidden = CME_ALL_PROFILES_ARE_HIDDEN;
                    pProfilesParams->mpProfiles[k].secType = CME_SEC_TYPE_OPEN;
                    pProfilesParams->mpProfiles[k].mProfileId = CME_INVALID_PROFILE_ID;
                }

                //
                // Nov 7 2016 - scan early termination threshold handling - PROFILE CONNECTION case
                //

                if (!CME_IS_ONGOING_WPS_AD_HOC_CONNECTION())
                {
                    cmeScanEarlyTermThresholdSet(apSharedInfo,
                                                 gCmeConnectionPolicyParams_ull.shouldUseFastConnect,
                                                 highest_priority, is_highest_profile_secured);
                }
            }
        }
        else
        {
            GTRACE(GRP_CME, "ERROR, failed to allocated %d bytes for %d profiles", allocSize, pProfilesParams->mNumProfiles);
            CME_CON_PRINT("\n\rERROR, failed to allocated %d bytes for %d profiles", allocSize, pProfilesParams->mNumProfiles);
            pProfilesParams->mNumProfiles = 0;

            // As we failed to allocate memory for profiles, free also the candidates memory
            CME_ReleaseScanResults(CALLER2);
            apSharedInfo->mpCandidateScanResults = NULL;

            // Set error indication
            rc = -1;
        }
    }
    else
    {
        CME_PRINT_PROFILE_REPORT_ERROR("\n\r Error: no profile found!");
    }

    return rc;
}

// ----------------------------------------------------------------------------
int32_t addProfileIdToSupplicant(cmeScanCandidateDesc_t *apCandidate)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    Bool_e adHocProfile = FALSE;
    uint32_t i=CME_SCAN_MAX_PROFILES;
    struct wpa_ssid *pSupplicantSsid;
    cmeProfileInfo_t *pProfile = NULL;
    Bool_e openProfile = FALSE;
    cmeProfileInfo_t *pOpenProfile = NULL;
    const u8 *ssid; //Pointer to ssid ie

    //indexing of the connecting profile - relevant for profile search only
    gConnectingIndex_ull = CONN_ATTEMPT_INVALID_IDX;
    //clear consecutive scan complete counter
    gConnSecutiveScanCompletes_ull = 0;

    if (apCandidate->mProfileId == CME_INVALID_PROFILE_ID)
    {
        // Check if this is an open AP and that we can connect to it
        if ((shouldConnectToOpenAp()) &&
            ((apCandidate->mScanResult.caps & DOT11_CAPABILITY_PRIVACY) == 0))
        {
            // Prepare the profile for transferring it to the supplicant
            pOpenProfile = os_zalloc(sizeof (cmeProfileInfo_t)); //Can use glx since buffer is freed at end of the function
            if (pOpenProfile)
            {
                //Set bssid
                IRQ_UtilCopyMacAddress (apCandidate->mScanResult.bssid, pOpenProfile->profile.bssid);
                pOpenProfile->profile.bssid_set = 1;

                //Set SSID
                //Get ssid from scan result
                ssid = get_ie( (const u8 *) apCandidate->mInfoElements, apCandidate->mScanResult.ie_len, WLAN_EID_SSID);
                if ((ssid != NULL) && (ssid[1] <= SSID_MAX_LEN))
                {
                    pOpenProfile->profile.ssid_len = ssid[1]; //ssid len
                    os_memcpy (pOpenProfile->profile.ssid, (int8_t *)(ssid + 2), ssid[1]); //Copy the SSID
                }

                //Set security to open
                pOpenProfile->profile.key_mgmt = WPA_KEY_MGMT_NONE; //No need to set pOpenProfile->profile.secType since it is not used after this point (and it is anyway 0)

                pOpenProfile->profile.mode = WPAS_MODE_INFRA;
                pOpenProfile->uniqueProfileId = CME_INVALID_PROFILE_ID; //Just to be on the safe side. There is no matching profile anyway.

                pProfile = pOpenProfile;
                openProfile = TRUE;
            }
        }
    }
    else
    {
        // Search for the profile in profiles DB, starting from the ad-hoc profile
        if (apCandidate->mProfileId == gAdHocProfile_ull.uniqueProfileId)
        {
            //For WPS, no profile is added to supplicant. Supplicant gets all the wps scan results and chooses by itself.
            if (!CME_IS_ONGOING_WPS_AD_HOC_CONNECTION())
            {
                pProfile = &gAdHocProfile_ull;
                adHocProfile = TRUE;
                if((pProfile->profile.key_mgmt & WPA_KEY_MGMT_SAE) != WPA_KEY_MGMT_SAE)
                {
                    //Calculate PSK, in case it was not already calculate (i.e. in add hoc with bssid, ssid is known only here)
                    if ((pProfile->profile.passphrase) && (!pProfile->profile.psk_set))
                    {
                        //Get ssid from scan result
                        ssid = get_ie( (const u8 *) apCandidate->mInfoElements, apCandidate->mScanResult.ie_len, WLAN_EID_SSID);
                        if ((ssid != NULL) && (ssid[1] <= SSID_MAX_LEN))
                        {
                            //Calc PMK
                            wlan_calculate_pmk(ssid[1] ,                                //ssid len
                                            (int8_t *)(ssid + 2),                       //ssid
                                            (int8_t *)pProfile->profile.passphrase,     //passphrase
                                            strlen (pProfile->profile.passphrase),   //passphrase len
                                            pProfile->profile.psk);                  //psk result

                            pProfile->profile.psk_set = 1;
                        }
                    }

                    if (pProfile->profile.passphrase)
                    {
                        os_free (pProfile->profile.passphrase);
                        pProfile->profile.passphrase = NULL;
                    }

                }
            }

            // Debug code
    #ifdef SIMULATE_NO_SCAN_RESULTS
            gAdHocProfile_ull.numWrongSsid = 3;
    #endif
        }
        else
        {
            //Preferred networks should be valid at this point (was read in prepareProfileInfo),
            //besides the case where we just got a disconnect command from user,
            //in the middle of a ad-hoc connect or profile connect.
            if (gPreferredReadFromFS)
            {
                for (i=0 ; i<CME_SCAN_MAX_PROFILES ; ++i)
                {
                    if (apCandidate->mProfileId == gPreferredNetworks[i].uniqueProfileId)
                    {
                        pProfile = &gPreferredNetworks[i];

                        cmeBlackListConnectionAttempt(i);

                        adHocProfile = FALSE;
                        break;
                    }
                }
            }
        }
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    // If no profile was found, this may be a WPS connection based, no valid
    // profile at this stage but no error as well
    if (NULL == pProfile)
    {
        if (!CME_IS_ONGOING_WPS_AD_HOC_CONNECTION())
        {
            GTRACE(GRP_CME, "ERROR: scan found a match for unique profile ID %d, can't find this profile",
                             apCandidate->mProfileId);
            CME_CON_PRINT_ERROR("\n\rERROR: scan found a match for unique profile ID %d, can't find this profile",
                             apCandidate->mProfileId);
            return -1;
        }

        GTRACE(GRP_CME, "This is a WPS ongoing connection:no valid profile at this stage but no error as well - profile ID %d",
                         apCandidate->mProfileId);
        return 0;
    }
    GTRACE(GRP_CME, "pProfile-psk_set %d",pProfile->profile.psk_set);

        if ( cmeAreReassociationParamsValid(&pProfile->profile))
        {
            // Profile is valid, add it to supplicant
            //restore reassociation params if:
            //1. valid AND
            //2. same ssid ()
            //3 check security
            //We restore the reassiciation params before adding profile to supplicant
            cmeReassociationParamsRestore();
        }
        else
        {
            //clear - not same network
            cmeReassociationParamsClear();
        }


    pSupplicantSsid = addProfile2Supplicant(&pProfile->profile);
    pProfile->profile.id = pSupplicantSsid->id;
    //mark last connected profile index attempt
    gCmeLastWlanProfileIdx = i;

    duplicateWpaPmksaCache(pProfile, apCandidate, pSupplicantSsid);

    GTRACE(GRP_CME, "Is ad-hoc profile %d, is open profile %d, unique profile ID %d, supplicant profile ID %d",
                     adHocProfile, openProfile, apCandidate->mProfileId, pProfile->profile.id);

    CME_CON_PRINT("\n\rIs ad-hoc profile %d, is open profile %d, unique profile ID %d, supplicant profile ID %d",
                     adHocProfile, openProfile, apCandidate->mProfileId, pProfile->profile.id);

    //fast connect store in global  buffers for possible file system storage in successful connection
    cmeUpdateCacheFastConnectionData(NULL,&pProfile->profile);

    //Release temporary profile in case of open AP
    if (openProfile)
    {
        os_free (pOpenProfile);
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return 0;
}


//
// cmeProfileIndexSearchByUniqueId
//
// given supplicant unique profile id, search for matching profile
// if exis return the wlan profile index
// else - return CME_SCAN_MAX_PROFILES
//

//int cmeProfileIndexSearchByUniqueId(int8_t profile_id)
//{
//    int i;
//    for (i=0 ; i<CME_SCAN_MAX_PROFILES ; ++i)
//    {
//        if (profile_id == gPreferredNetworks[i].profile.id)
//        {
//            GTRACE(GRP_IP_CONFIG,"Wlan profile index is %d", i);
//            break;
//        }
//    }
//
//    if (i == CME_SCAN_MAX_PROFILES)
//    {
//        GTRACE(GRP_IP_CONFIG,"Wlan profile index is CME_SCAN_MAX_PROFILES");
//    }
//
//    return i;
//}
//************************************************************************************
// CONNECTION BLACK LIST METHODS
//************************************************************************************


//
// cmeClearCurrentConnectionAttemptCtr
//
// successful connection notifier - clear connection attempt for not black-listing this network
// and clear the connecting index as it is not
//
void cmeClearCurrentConnectionAttemptCtr()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    if (gConnectingIndex_ull != CONN_ATTEMPT_INVALID_IDX)
    {
        //clear attempts counter (successfully connected)
        gPreferredNetworksConnAttemptCnt_ull[gConnectingIndex_ull] = 0;
    }

    //clear consecutive scan compelte counter
    gConnSecutiveScanCompletes_ull = 0;
}


//
// cmeClearAllBlackList
//
// clear all valid network black list counters
//
static void cmeClearAllBlackList()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int i;
    for (i=0;i<CME_SCAN_MAX_PROFILES;i++)
    {
        if (gPreferredNetworksConnAttemptCnt_ull[i] != CONN_ATTEMPT_INVALID_CTR)
        {
            gPreferredNetworksConnAttemptCnt_ull[i] = 0;
        }
    }

    //clear consecutive scan compelte counter
    gConnSecutiveScanCompletes_ull = 0;
}

//
// cmeConsequtiveScanCompletesNoCandidate
//
// allow X amounts of consequtive scan completes with no candidate found
// before clearing black list that might preventing from black listed profiles
// to enter the scan list
//
void cmeConsequtiveScanCompletesNoCandidate()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    gConnSecutiveScanCompletes_ull++;

    if (gConnSecutiveScanCompletes_ull >=CLEAR_BLACK_LIST_CONSEQ_SCAN_COMPLETES)
    {
        //reached maximum consequitve scans, we can avoid blacklisting cause nothing else seems to be found
        cmeClearAllBlackList();

        gConnectingIndex_ull = CONN_ATTEMPT_INVALID_IDX;
    }
}

//
// cmeZeroConnectionIndex
//
void cmeZeroConnectionIndex()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    gConnectingIndex_ull = CONN_ATTEMPT_INVALID_IDX;
}

static int isBlackListed(uint32_t index)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return (gPreferredNetworksConnAttemptCnt_ull[index] >= MAX_JOIN_RETRIES ? 1 : 0);
}


//
// cmeBlackListConnectionAttempt
//
// increment connection attempt counter for network
// then evaluate if all networks are blacklisted then we should clear all counters
//
void cmeBlackListConnectionAttempt(uint32_t index)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int i,allInBlackList;

    if (cme_is_p2p_role_configured())
    {
        //black list not relevant for P2P role, only STA
        return;
    }
    //increment connection attempt for this network
    gPreferredNetworksConnAttemptCnt_ull[index]++;

    gConnectingIndex_ull = index;
    allInBlackList = 1;//assume all in black list, clear in the loop according to the counters

    for (i=0;i<CME_SCAN_MAX_PROFILES;i++)
    {
        if (gPreferredNetworksConnAttemptCnt_ull[i] == CONN_ATTEMPT_INVALID_CTR)
        {
            continue;
        }
        //--else
        if (gPreferredNetworksConnAttemptCnt_ull[i] < MAX_JOIN_RETRIES)
        {
            allInBlackList = 0;
            GTRACE(GRP_CME,"cmeBlackListConnectionAttempt: at least one network not in blacklist - carry on");
            CME_PRINT_PROFILE_REPORT("\r\ncmeBlackListConnectionAttempt: at least one network not in blacklist - carry on");
            break;
        }
    }

    if (allInBlackList)
    {
        GTRACE(GRP_CME,"cmeBlackListConnectionAttempt: ALL networks are blacklisted - clear blacklist");
        CME_PRINT_PROFILE_REPORT("\r\ncmeBlackListConnectionAttempt: ALL networks are blacklisted - clear blacklist");
        cmeClearAllBlackList();
        //re-increment the conn attempt counter we are about to connect to after the clearall
        gPreferredNetworksConnAttemptCnt_ull[index]++;


    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

}

// ============================================================================
//		Local Functions
// ============================================================================

/* ----------------------------------------------------------------------------
 compareProfiles
    This function checks if a profile already exists in DB.
    If it is but parameter/parameters is/are changed, profile is updated.

 Parameters:    apCmd - new profile parameters
                apProfile - existing profile
 Return code:   TRUE if profile is found, FALSE else
---------------------------------------------------------------------------- */
#if 0
static Bool32 compareProfiles(_WlanAddGetProfile_t *apCmd,
                                        uint32_t aKeyMgmt,
                                        struct wpa_ssid *apProfile)
{
    // If SSID length doesn't match, profiles don't match for sure
    if (apCmd->SsidLen != apProfile->ssid_len)
        return FALSE;

    if (os_memcmp(SSID_STRING(apCmd), apProfile->ssid, apCmd->SsidLen))
        return FALSE;

    // SSID match found, compare BSSID
    if (0 == IRQ_UtilCompareMacAddress(apCmd->Bssid, apProfile->bssid))
        return FALSE;

    // BSSIDs also match, compare security type
    if (aKeyMgmt != apProfile->key_mgmt)
        return FALSE;

    // Security type matches, checks from this point depend on security parameters.
    // Code is based on cc3100, SimpleManager.c, locateAndFillStandardNetwork

    // New added profile is of security type WPA/WPA2
    if (WPA_KEY_MGMT_PSK == aKeyMgmt)
    {
        // When a new added profile of WPA/WPA2 has the same SSID & BSSID of
        // a profile in gPreferredNetworks, the profile is re-used.
        // Profile security parameters are updated, although it is possible that all security
        // parameters are the same (we would like to avoid matching the current gPreferredNetworks[]
        // passphrase and new profile passphrase).
        // The reason we do that is to avoid storing in RAM and FS the passphrase of each WPA profile
        // (7profiles x 32Bytes) in the expense of re-calculation time of the PSK key and FS store
        // time, every time a fully the same WPA/WPA2 profile is being added by the user.
        return TRUE;
    }

    // New added profile is of security type OPEN/WEP
    if (WPA_KEY_MGMT_NONE == aKeyMgmt)
    {
        int32_t wep_key_len = ( (apCmd->WepKeyId & 0xff) | (apCmd->PasswordLen << 8) ) & 0xff;

        // Both new profile and existing one have WEP key length !0, hence
        // both use WEP
        if ( (0 != wep_key_len) &&
             (0 != apProfile->wep_key_len[0]) )
        {
            // When a new added profile of WEP has the same SSID & BSSID of a
            // profile in gPreferredNetworks we won't check for a match of the
            // WEP security parameters (same as done in WPA/WPA2 case).
            // The existing profile is re-used and updated with new WEP parameters.
            // The reason is that we don't distinguish today in WEP case in the key_id
            // and its keys, meaning, once we find the AP's SSID and BSSID and see
            // that it is of WEP type, we will try to connect to it regardless the differnt keys
            // of the two similar profiles since we don't try to find a match for key and key_id
            // in WEP connection.
            // In this case, we might have a second profile which is redundant
            // and therefore, we deicde to override the current profile security parameters
            // with the new added one.
            return TRUE;
        }
        else if (apProfile->wep_key_len[0] != wep_key_len)
        {
            // No match in security types between new added profile and existing profile.
            // Either current profile in DB is OPEN (wep_key_len[0]==0) and new added profile
            // is WEP (wep_key_len != 0) or vise versa.
            // Thus, we need to move to next profile index in the DB and find another match, if any.
            return FALSE;
        }

        // Both new & current profile are of security type OPEN

        // --------------------------------------------------------------------
        // debug code, can be removed

        // At this point we have a full match between SSID & BSSID & Security
        // type OPEN. Compare priority just for logging.
        // Note that 3100 also compares scan tyepe (hidden or not). Since there's
        // no API for setting scan type, this comaprison is ommited.
        if (apProfile->priority != apCmd->Priority)
        {
            GTRACE(GRP_CME, "OPEN profile already exists, priority is updated; old %d, new %d",
                             apProfile->priority, apCmd->Priority);
            return TRUE;
        }

        // Exactly the same profile already exists in DB
        GTRACE(GRP_CME, "OPEN profile already exists, won't be changed");

        // --------------------------------------------------------------------

        return TRUE;
    }
    else if (aKeyMgmt == WPA_KEY_MGMT_IEEE8021X)
    {
        // When the new enterprise profile has the same SSID & BSSID of an existing
        // profile, the existing profile is re-used and security parameters are updated.
        return TRUE;
    }

    // We should not get here, just for debug ASSERT_GENERAL here
    ASSERT_GENERAL(0);
    return FALSE;
}
#endif

/* ----------------------------------------------------------------------------
 addAdHocProfile2DB
    This function adds a new profile to ad hoc DB.
    Function invoked on wlanConnect command

 Parameters:    apCmd - profile parameters
                aKeyMgmt - management type, WPA_KEY_MGMT_xxx
                apSsid - pointer to SSID
                apPassword - pointer to password
                p2p type if relevant
 Return code:   none
---------------------------------------------------------------------------- */
static void addAdHocProfile2DB(CMEWlanAddGetProfile_t  *apCmd, uint32_t aKeyMgmt,
        int8_t *apSsidStr, int8_t *apPassword, p2pProfile_e p2p_type, CMEEapWlanConnect_t *apEapCmd)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    // set all parameters even if profile is matching
    setSharedSsidParams(apCmd, aKeyMgmt, &gAdHocProfile_ull.profile, apSsidStr, apPassword);

    // Mark this entry is in use
    gAdHocProfile_ull.uniqueProfileId = getUniqueProfileId();

    // get p2p type
    gAdHocProfile_ull.p2pProfile = p2p_type;

    if (apEapCmd!=NULL)
    {

        {
            int i;
            CME_PRINT_REPORT("ssid: ");
            for(i=0;i<apEapCmd->EapCommonConnect.SsidLen;i++)
            {
                CME_PRINT_REPORT("%c",apSsidStr[i]);
            }
        }
        addProfileEap2DB(
                apCmd->SecType,
                (unsigned char *)apEapCmd->eapAnonymous,
                apEapCmd->eapAnonUserLen,
                (unsigned char *)apEapCmd->eapIdentity,
                apEapCmd->eapIdentityLen,
                (unsigned char *)apPassword,
                apEapCmd->EapCommonConnect.PasswordLen,
                apEapCmd->eap_phase1_val,
                apEapCmd->eap_phase2_val,
                apEapCmd->pEap_client_cert,
                apEapCmd->eap_client_cert_len,
                apEapCmd->pEap_ca_cert,
                apEapCmd->eap_ca_cert_len,
                apEapCmd->pEap_private_key,
                apEapCmd->eap_private_key_len,
                apEapCmd->TLSKeyLength,
                apEapCmd->EapCommonConnect.FastTransition,
                &gAdHocProfile_ull);
    }
    else
    {
        //legacy security connect
        if (setSecurityParams(apCmd, &gAdHocProfile_ull.profile, apPassword) < 0)
        {
            // TODO - have to remove the profile from DB
            ASSERT_GENERAL(0);
        }
    }

    GTRACE(GRP_CME, "Added profile (unique ID %d) to Ad Hoc ssid: Security type %d password len %d",
                    gAdHocProfile_ull.uniqueProfileId, aKeyMgmt, apCmd->PasswordLen);
}

#if 0
/* ----------------------------------------------------------------------------
 scanResult2SupplicantProfile
    This function is used only when OPEN policy is enabled.
    It creates a new profile from the selected candidate and adds it to profiles DB.

    Note: if OPEN policy is disabled, this profile should be removed

 Parameters:    apScanResult - pointer to candidate parameters

 Return code:   none
---------------------------------------------------------------------------- */
void addScanResProfile2Supplicant(struct wpa_scan_res *apScanResult)
{
    cmeProfileInfo_t profile;
    uint8_t  *pSsidIe = (uint8_t *)(apScanResult + 1);
    uint32_t ssidLen = pSsidIe[1];

    // Start from a clean profile - no p2p, security, WPAS_MODE_INFRA
    memset(&profile, 0, sizeof(cmeProfileInfo_t));

    // SSID IE is set after struct wpa_scan_res, copy from there
    memcpy(profile.profile.ssid, &pSsidIe[2], ssidLen);

    //profile.profile.ssid = profile.ssid;
    profile.profile.ssid_len = ssidLen;
    profile.profile.priority = CME_OPEN_POLICY_PROFILE_PRIORITY;
    profile.profile.auth_alg = WPA_AUTH_ALG_OPEN;
    profile.profile.key_mgmt = WPA_KEY_MGMT_NONE;

    // see note in setSharedSsidParams
    profile.profile.scan_ssid = CME_ALL_PROFILES_ARE_HIDDEN;

    GTRACE(GRP_CME, "Created open profile (SSID len %d SSID %s, unique ID %d) from scan resuld",
                    ssidLen, profile.profile.ssid, profile.uniqueProfileId);

    addProfile2Supplicant(&profile.profile);
}
#endif

/* ----------------------------------------------------------------------------
 duplicateEapProfile
    This function duplicates EAP related parameters

 Parameters:    apReferenceSsid - EAP ssid profile reference
                apInputApSsid - pointer to ssid profile need should be updated
 Return code:   none
---------------------------------------------------------------------------- */
// TODO need to implement
#if 0
static void duplicateEapProfile(const _cme_minimized_wpa_ssid_t       *apReferenceSsid,
                                     struct wpa_ssid *apInputApSsid)
{
    cmeEntProfileParams_t pEntProfile[CME_MAX_EAP_ENTRIES]; //TODO: move to heap?
    //set EAP network defaults
    apInputApSsid->proto             = apReferenceSsid->proto;
    apInputApSsid->pairwise_cipher   = apReferenceSsid->pairwise_cipher;
    apInputApSsid->group_cipher      = apReferenceSsid->group_cipher;
    apInputApSsid->key_mgmt          = apReferenceSsid->key_mgmt;
#ifdef IEEE8021X_EAPOL
    apInputApSsid->eapol_flags       = apReferenceSsid->eapol_flags;
    apInputApSsid->eap_workaround    = apReferenceSsid->eap_workaround;
    apInputApSsid->eap.fragment_size = apReferenceSsid->eap.fragment_size;
#endif /* IEEE8021X_EAPOL */

    //common configurations
    apInputApSsid->auth_alg          = apReferenceSsid->auth_alg;

    //get the current ENT profiles from FS
    LoadEnterpriseProfile_GetFromFlash(pEntProfile, TRUE);


    /*
     * Copy all eap config
     */

    //TODO: supplicant expects to get a list of all supported TLS methods. For now we save only one.
    //allocate and copy eap method types
    apInputApSsid->eap.eap_methods = mem_Zalloc_ull(sizeof(struct eap_method_type) * 2); //The last item in the list should be empty
    if (apInputApSsid->eap.eap_methods)
    {
        memcpy(apInputApSsid->eap.eap_methods,&pEntProfile[apReferenceSsid->eap.eap_entProfileIndex].eap_method,sizeof(struct eap_method_type));
    }

    //allocate and copy eap identity if exist
    if (apReferenceSsid->eap.identity_len > 0)
    {
        //update pointer in the array
        apInputApSsid->eap.identity = os_malloc(apReferenceSsid->eap.identity_len);
        if (apInputApSsid->eap.identity)
        {
            memcpy(apInputApSsid->eap.identity,pEntProfile[apReferenceSsid->eap.eap_entProfileIndex].Identity, apReferenceSsid->eap.identity_len);
            apInputApSsid->eap.identity_len = apReferenceSsid->eap.identity_len;
        }

    }
    //allocate and copy eap anonymous identity if exist
    if (apReferenceSsid->eap.anonymous_identity_len > 0)
    {
       //update pointer in the array
       apInputApSsid->eap.anonymous_identity = os_malloc(apReferenceSsid->eap.anonymous_identity_len);
       if (apInputApSsid->eap.anonymous_identity)
       {
           memcpy(apInputApSsid->eap.anonymous_identity,pEntProfile[apReferenceSsid->eap.eap_entProfileIndex].Anonymous, apReferenceSsid->eap.anonymous_identity_len);
           apInputApSsid->eap.anonymous_identity_len = apReferenceSsid->eap.anonymous_identity_len;
       }
    }

    if(0 < apReferenceSsid->eap.password_len)
    {
        apInputApSsid->eap.password = os_malloc(apReferenceSsid->eap.password_len);
        if (apInputApSsid->eap.password)
        {
            memcpy(apInputApSsid->eap.password,pEntProfile[apReferenceSsid->eap.eap_entProfileIndex].Password, apReferenceSsid->eap.password_len);
            apInputApSsid->eap.password_len = apReferenceSsid->eap.password_len;
        }
    }

    // Points to const strings
    //TODO: GLX or ull - Need to check WPS as well!!! (currently ull since wps is ull as well (?? not sure it is correct, config.c is using glx!!)
    apInputApSsid->eap.phase1 = os_strdup(apReferenceSsid->eap.phase1);
    apInputApSsid->eap.phase2 = os_strdup(apReferenceSsid->eap.phase2);

    apInputApSsid->eap.pac_file = os_strdup (apReferenceSsid->eap.pac_file);

    // Points to const strings
    //TODO: Probably need to be updated once we hande the certificates (?)
    apInputApSsid->eap.ca_cert = apReferenceSsid->eap.ca_cert;
    apInputApSsid->eap.client_cert = apReferenceSsid->eap.client_cert;
    apInputApSsid->eap.private_key = apReferenceSsid->eap.private_key;
    apInputApSsid->eap.private_key_passwd = ""; //TODO: temporary

    //TODO: what about private key password??

    //TODO: Probably need to be updated once we hande the certificates (?)
    //TODO: Currently uses the same certificates as in phase 1 (?)
    apInputApSsid->eap.ca_cert2 = apReferenceSsid->eap.ca_cert2;
    apInputApSsid->eap.client_cert2 = apReferenceSsid->eap.client_cert2;
    apInputApSsid->eap.private_key2 = apReferenceSsid->eap.private_key2;
    apInputApSsid->eap.private_key2_passwd = ""; //TODO: temporary
}
#endif

void entSaveIdentity (unsigned char *identity, int identity_len,
                      cmeEntProfileParams_t *eap_profile_entry, cmeProfileInfo_t * inputProfile)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    //Save EAP identity
    os_memset(&eap_profile_entry->Identity[0], 0, MAX_USER_LEN);
    if ((identity_len > 0) && (identity_len < MAX_USER_LEN))
    {
        os_memcpy(&eap_profile_entry->Identity[0], identity, identity_len);
        os_memcpy(&inputProfile->profile.eap.identity[0], identity, identity_len);
        inputProfile->profile.eap.identity_len      = identity_len;
    }
    else
    {
        inputProfile->profile.eap.identity_len = 0;
    }
}


void entSaveAnonymousIdentity (unsigned char *anonymous_identity, int anonymous_identity_len,
                               cmeEntProfileParams_t *eap_profile_entry, cmeProfileInfo_t * inputProfile)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    //Save EAP anonymous identity
    os_memset(&eap_profile_entry->Anonymous[0], 0, MAX_ANON_LEN);
    if ((anonymous_identity_len > 0) && (anonymous_identity_len < MAX_ANON_LEN) && anonymous_identity)
    {
       os_memcpy(&eap_profile_entry->Anonymous[0],  anonymous_identity, anonymous_identity_len);
       os_memcpy(&inputProfile->profile.eap.Anonymous[0],  anonymous_identity, anonymous_identity_len);
       inputProfile->profile.eap.anonymous_identity_len = anonymous_identity_len;
    }
    else
    {
        inputProfile->profile.eap.anonymous_identity_len = 0;
    }
}


void entSavePassword (unsigned char *passwd, int passwd_len,
                      cmeEntProfileParams_t *eap_profile_entry, cmeProfileInfo_t * inputProfile)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    //Save EAP password
    os_memset(&eap_profile_entry->Password[0], 0, MAX_PASS_LEN);
    os_memset(inputProfile->profile.eap.password, 0, MAX_PASS_LEN);
    if ((0 < passwd_len) && (passwd_len < MAX_PASS_LEN))
    {
        os_memcpy(&eap_profile_entry->Password[0], passwd, passwd_len);
        inputProfile->profile.eap.password_len = passwd_len;
        os_memcpy(inputProfile->profile.eap.password, passwd, passwd_len);
    }
    else
    {
        GTRACE(GRP_CME, "addProfileEap2DB: Bad passwd len");
        inputProfile->profile.eap.password_len = 0;
    }
}

/* ----------------------------------------------------------------------------
 addProfileEap2DB
    This function updated EAP related parameters to the inputed profile entry.

 Parameters:    apEapCmd - EAP profile parameters
                inputProfile - pointer to SSID need to be updated
 Return code:   none
---------------------------------------------------------------------------- */

static void addProfileEap2DB(uint16_t    SecType,
                             unsigned char *anonymous_identity,
                             int anonymous_identity_len,
                             unsigned char *identity,
                             int identity_len,
                             unsigned char *passwd,
                             int passwd_len,
                             eap_phase1_val_t  eap_phase1_val,
                             eap_phase2_val_t  eap_phase2_val,
                             const uint8_t*    pEap_client_cert,
                             uint32_t    eap_client_cert_len,
                             const uint8_t*    pEap_ca_cert,
                             uint32_t    eap_ca_cert_len,
                             const uint8_t*    pEap_private_key,
                             uint32_t    eap_private_key_len,
                             uint32_t    TLSKeyLength,
                             uint8_t     FastTransition,
                             cmeProfileInfo_t * inputProfile)
{
    int32_t i;
    //get shared input commands
    int32_t fast_provisioning                   = 0; //not supported
    cmeEntProfileParams_t *eap_profile_entry=NULL;

    //currently this array is not used.
    cmeEntProfileParams_t pEntProfile[CME_MAX_EAP_ENTRIES] = {0};//ENT profile
    uint8_t version = 0;



    //get the current ENT profiles from FS
    LoadEnterpriseProfile_GetFromFlash(pEntProfile, TRUE);

#if 0
    //allocate profile entry for this ENT network:
    for (i=0;i<CME_MAX_EAP_ENTRIES;i++)
    {
        if (pEntProfile[i].is_in_use == 0)
        {
            eap_profile_entry = &pEntProfile[i];
            eap_profile_entry->is_in_use = 1;
            inputProfile->profile.eap.eap_entProfileIndex = i;//store ENT profile index

        }
    }
#endif

    inputProfile->profile.eap.eap_entProfileIndex = 0;
    eap_profile_entry = &pEntProfile[inputProfile->profile.eap.eap_entProfileIndex];
    //free entry should be validated in command context (EAP add hoc or profile add)
    ASSERT_GENERAL(eap_profile_entry!=NULL);

    //set EAP network defaults

#ifdef IEEE8021X_EAPOL
    inputProfile->profile.eapol_flags = DEFAULT_EAPOL_FLAGS;
    inputProfile->profile.eap_workaround = DEFAULT_EAP_WORKAROUND;
    inputProfile->profile.eap.fragment_size = DEFAULT_FRAGMENT_SIZE;
#endif /* IEEE8021X_EAPOL */


    inputProfile->profile.group_mgmt_cipher = 0;

    switch(SecType)
    {
        case WLAN_SEC_TYPE_WPA_WPA2://WPA2
            inputProfile->profile.pairwise_cipher       = WPA_CIPHER_CCMP|WPA_CIPHER_GCMP|WPA_CIPHER_TKIP|WPA_CIPHER_GCMP_256;

            inputProfile->profile.group_cipher          = WPA_CIPHER_CCMP| WPA_CIPHER_GCMP|WPA_CIPHER_TKIP|WPA_CIPHER_GCMP_256;

            inputProfile->profile.key_mgmt              = WPA_KEY_MGMT_IEEE8021X|WPA_KEY_MGMT_IEEE8021X_SHA256;

            inputProfile->profile.ieee80211w = NO_MGMT_FRAME_PROTECTION;

            break;
        case WLAN_SEC_TYPE_WPA2_PLUS://with PMF optional
            inputProfile->profile.pairwise_cipher       = WPA_CIPHER_CCMP|WPA_CIPHER_GCMP|WPA_CIPHER_TKIP|WPA_CIPHER_GCMP_256;


            inputProfile->profile.group_cipher          = WPA_CIPHER_CCMP| WPA_CIPHER_GCMP|WPA_CIPHER_TKIP|WPA_CIPHER_GCMP_256;


            inputProfile->profile.key_mgmt              = WPA_KEY_MGMT_IEEE8021X|WPA_KEY_MGMT_IEEE8021X_SHA256;

            inputProfile->profile.ieee80211w = MGMT_FRAME_PROTECTION_OPTIONAL;

            inputProfile->profile.group_mgmt_cipher |= WPA_CIPHER_AES_128_CMAC|WPA_CIPHER_BIP_CMAC_256|WPA_CIPHER_BIP_GMAC_128|WPA_CIPHER_BIP_GMAC_256|WPA_CIPHER_BIP_CMAC_256;

            break;
        case WLAN_SEC_TYPE_WPA3:

            if((eap_phase1_val == TLS) && (TLSKeyLength == 192))
            {
                inputProfile->profile.pairwise_cipher       =  WPA_CIPHER_GCMP_256;

                inputProfile->profile.group_cipher          =  WPA_CIPHER_GCMP_256;

                inputProfile->profile.key_mgmt              =  WPA_KEY_MGMT_IEEE8021X_SUITE_B_192;

                inputProfile->profile.group_mgmt_cipher |= WPA_CIPHER_BIP_CMAC_256| WPA_CIPHER_BIP_GMAC_256;

                //inputProfile->profile.isSuiteb192  = 1;
                inputProfile->profile.eapol_flags |= EAPOL_FLAG_SUITEB_ONLY;
                CME_PRINT_REPORT("\n\r TLS WPA3 SUITEB192 only");

            }
            else
            {
                //WPA_CIPHER_CCMP_256 not allowed for wPA3
                inputProfile->profile.pairwise_cipher       =  WPA_CIPHER_CCMP|WPA_CIPHER_GCMP|WPA_CIPHER_GCMP_256;

                inputProfile->profile.group_cipher          =  WPA_CIPHER_CCMP|WPA_CIPHER_GCMP|WPA_CIPHER_GCMP_256;


                inputProfile->profile.key_mgmt              =  WPA_KEY_MGMT_IEEE8021X| WPA_KEY_MGMT_IEEE8021X_SHA256
                                                               |WPA_KEY_MGMT_IEEE8021X_SUITE_B|WPA_KEY_MGMT_IEEE8021X_SUITE_B_192;
                inputProfile->profile.group_mgmt_cipher |= WPA_CIPHER_AES_128_CMAC | WPA_CIPHER_BIP_CMAC_256|WPA_CIPHER_BIP_GMAC_128 | WPA_CIPHER_BIP_GMAC_256;

            }
            inputProfile->profile.ieee80211w = MGMT_FRAME_PROTECTION_REQUIRED;


            break;
        case WLAN_SEC_TYPE_WPA2_WPA3:
            inputProfile->profile.pairwise_cipher       = WPA_CIPHER_CCMP|WPA_CIPHER_GCMP|WPA_CIPHER_GCMP_256|
                                                           WPA_CIPHER_TKIP;

            inputProfile->profile.group_cipher          =  WPA_CIPHER_CCMP|WPA_CIPHER_GCMP|WPA_CIPHER_GCMP_256|
                                                           WPA_CIPHER_TKIP;

            inputProfile->profile.key_mgmt              =  WPA_KEY_MGMT_IEEE8021X| WPA_KEY_MGMT_IEEE8021X_SHA256
                                                           | WPA_KEY_MGMT_IEEE8021X_SUITE_B|WPA_KEY_MGMT_IEEE8021X_SUITE_B_192;


            inputProfile->profile.group_mgmt_cipher |= WPA_CIPHER_AES_128_CMAC|WPA_CIPHER_BIP_CMAC_256 |WPA_CIPHER_BIP_GMAC_128 | WPA_CIPHER_BIP_GMAC_256|WPA_CIPHER_BIP_CMAC_256;
            inputProfile->profile.ieee80211w = MGMT_FRAME_PROTECTION_OPTIONAL;
            break;
    }

    //common configurations
    inputProfile->profile.proto                 = WPA_PROTO_RSN;
    inputProfile->profile.auth_alg              = WPA_AUTH_ALG_OPEN;
    inputProfile->profile.secType               = CME_SEC_TYPE_WPA_ENT;
    inputProfile->profile.auth_alg = WPA_AUTH_ALG_OPEN;


    eap_profile_entry->eap_method.vendor         = EAP_VENDOR_IETF;

    entSaveIdentity (identity, identity_len, eap_profile_entry, inputProfile);

    inputProfile->profile.eap.ca_cert = (u8 *) pEap_ca_cert;
    inputProfile->profile.eap.client_cert = (u8 *) pEap_client_cert;
    inputProfile->profile.eap.private_key = (u8 *) pEap_private_key;
    inputProfile->profile.eap.ca_cert_len = eap_ca_cert_len;
    inputProfile->profile.eap.client_cert_len = eap_client_cert_len;
    inputProfile->profile.eap.private_key_len = eap_private_key_len;

    if (FastTransition)
    {
        inputProfile->profile.key_mgmt |= WPA_KEY_MGMT_FT_IEEE8021X; // | WPA_KEY_MGMT_FT_IEEE8021X_SHA384;
        inputProfile->profile.auth_alg |= WPA_AUTH_ALG_FT;
    }


    switch (eap_phase1_val)
    {
        case TLS: // TLS


             CME_PRINT_REPORT("\n\r addProfileEap2DB: Connecting TLS");
             eap_profile_entry->eap_method.method = EAP_TYPE_TLS;
             inputProfile->profile.eap.eap_method = eap_peer_tls_methods;
             inputProfile->profile.eap.num_of_eap_methods = num_of_eap_methods_tls_methods;

             if(inputProfile->profile.eap.ca_cert != NULL)
             {
                 inputProfile->profile.eap.phase1 = (char *)PHASE1_TLS_TTLS;
             }
             else
             {
                 inputProfile->profile.eap.phase1 = (char *)PHASE1_TLS_TTLS_CA_CERT_VERIFICATION_NONE;
             }


             entSaveAnonymousIdentity (anonymous_identity, anonymous_identity_len,
                                            eap_profile_entry, inputProfile);


            break; //TLS
        case TTLS: // TTLS

            eap_profile_entry->eap_method.method = EAP_TYPE_TTLS;
            inputProfile->profile.eap.eap_method = eap_peer_ttls_methods;
            inputProfile->profile.eap.num_of_eap_methods = num_of_eap_methods_ttls_methods;

            entSaveAnonymousIdentity (anonymous_identity, anonymous_identity_len, eap_profile_entry, inputProfile);
            inputProfile->profile.eap.phase1 = (char *)PHASE1_TLS_TTLS;


            // Phase 2
            switch (eap_phase2_val)
            {
                case MSCHAPV2_TYPE:
                    GTRACE(GRP_CME,"addProfileEap2DB: Connecting EAP TTLS-MSCHAPV2");
                    CME_PRINT_REPORT("\n\r ENT TTLS MSCHAPV2 build prof");

                    inputProfile->profile.eap.phase2 = (char *)PHASE2_AUTH_TYPE_MSCHAPV2;
                    EAP_CONFIG_PHASE2_SET(inputProfile->profile.eap.flags ,MSCHAPV2_TYPE);


                    entSavePassword (passwd, passwd_len, eap_profile_entry, inputProfile);
                    break;

                case TLS_TYPE:
                {
                    GTRACE(GRP_CME,"addProfileEap2DB: Connecting EAP TTLS-TLS");
                    CME_PRINT_REPORT("\n\r ENT TTLS TLS_TYPE build prof");

                    inputProfile->profile.eap.phase2 = (char *)PHASE2_AUTH_TYPE_TLS;
                    //Save phase2 configuration
                    EAP_CONFIG_PHASE2_SET(inputProfile->profile.eap.flags,TLS_TYPE);
                    //Set pointers. supplicast receive pointers to these variables and these values need to be saved after reset
                    //therefore saved in the file itself. Pointers will be updated again when reading the file (in case address was changed).
                    inputProfile->profile.eap.ca_cert2 = (u8 *) pEap_ca_cert;
                    inputProfile->profile.eap.client_cert2 = (u8 *)  pEap_client_cert;
                    inputProfile->profile.eap.private_key2 = (u8 *) pEap_private_key;

                    inputProfile->profile.eap.ca_cert_len = eap_ca_cert_len;
                    inputProfile->profile.eap.private_key_len = eap_private_key_len;


                    break;
                }
                case PSK_TYPE:
                    GTRACE(GRP_CME,"addProfileEap2DB: Connecting EAP TTLS-PSK");
                    CME_PRINT_REPORT("\n\r ENT TTLS PSK_TYPE build prof");

                    inputProfile->profile.eap.phase2 = (char *)PHASE2_AUTH_TYPE_PSK;
                    //Save phase2 configuration
                    EAP_CONFIG_PHASE2_SET(inputProfile->profile.eap.flags,PSK_TYPE);

                    //Save PSK password
                    // Password must be 16 bytes hex! TODO: is it necessary to check?
                    entSavePassword (passwd, passwd_len, eap_profile_entry, inputProfile);

                    break;

                default:
                    break;
            }

            break; //TTLS
        case PEAP0: // PEAP
        case PEAP1: // PEAP
        case PEAP2:
            eap_profile_entry->eap_method.method = EAP_TYPE_PEAP;
            inputProfile->profile.eap.eap_method = eap_peer_peap_methods;
            inputProfile->profile.eap.num_of_eap_methods = num_of_eap_methods_peap;
            inputProfile->profile.eap.ca_cert = (u8 *) pEap_ca_cert;
            inputProfile->profile.eap.ca_cert_len = eap_ca_cert_len;


            entSaveAnonymousIdentity (anonymous_identity, anonymous_identity_len, eap_profile_entry, inputProfile);


            if (PEAP0 == eap_phase1_val)
            {
                inputProfile->profile.eap.phase1 = (char *)PHASE1_PEAPVER0;
                //Save phase1 configuration
                inputProfile->profile.eap.flags &= ~EAP_CONFIG_FLAGS_PHASE1_PEAP;

                version = 0;
            }
            else if (PEAP1 == eap_phase1_val)
            {
                inputProfile->profile.eap.phase1 = (char *)PHASE1_PEAPVER1;
                //Save phase1 configuration
                inputProfile->profile.eap.flags |= EAP_CONFIG_FLAGS_PHASE1_PEAP;

                version = 1;
            }
            else if (PEAP2 == eap_phase1_val)
            {
                inputProfile->profile.eap.phase1 = (char *)PHASE1_PEAPVER2;
                //Save phase1 configuration
                inputProfile->profile.eap.flags |= EAP_CONFIG_FLAGS_PHASE1_PEAP;

                version = 2;
            }


            // Phase 2
            switch (eap_phase2_val)
            {
                case MSCHAPV2_TYPE:// for peap0 peap2
                    CME_PRINT_REPORT("\n\r addProfileEap2DB: Connecting EAP PEAP v%d-MSCHAPV2", version);

                    GTRACE(GRP_CME,"addProfileEap2DB: Connecting EAP PEAP v%d-MSCHAPV2", version);

                    inputProfile->profile.eap.phase2 = (char *)PHASE2_AUTH_TYPE_MSCHAPV2;
                    EAP_CONFIG_PHASE2_SET(inputProfile->profile.eap.flags,MSCHAPV2_TYPE);

                    //Save password
                    entSavePassword (passwd, passwd_len, eap_profile_entry, inputProfile);
                    break;

                case GTC_TYPE://only for peap0 peap2

                    CME_PRINT_REPORT("\n\r addProfileEap2DB: Connecting EAP PEAP v%d-GTC", version);

                    GTRACE(GRP_CME,"addProfileEap2DB: Connecting EAP PEAP v%d-GTC", version);

                    inputProfile->profile.eap.phase2 = (char *)PHASE2_AUTH_TYPE_GTC;
                    EAP_CONFIG_PHASE2_SET(inputProfile->profile.eap.flags,GTC_TYPE);

                    //Save password
                    entSavePassword (passwd, passwd_len, eap_profile_entry, inputProfile);
                    break;

                case TLS_TYPE:
                    CME_PRINT_REPORT("\n\r ENT PEAP0|PEAP1 TLS_TYPE build prof");
                    GTRACE(GRP_CME,"addProfileEap2DB,simplemanager: Connecting EAP PEAP v%d-TLS", version);

                    inputProfile->profile.eap.phase2 = (char *)PHASE2_AUTH_TYPE_TLS;
                    //Save phase2 configuration
                    EAP_CONFIG_PHASE2_SET(inputProfile->profile.eap.flags,TLS_TYPE);
                    inputProfile->profile.eap.ca_cert2 = (u8 *) pEap_ca_cert;
                    inputProfile->profile.eap.client_cert2 = (u8 *) pEap_client_cert;
                    inputProfile->profile.eap.private_key2 = (u8 *) pEap_private_key;

                    inputProfile->profile.eap.ca_cert_len = eap_ca_cert_len;
                    inputProfile->profile.eap.private_key_len = eap_private_key_len;


                    break;
                case PSK_TYPE:
                    CME_PRINT_REPORT("\n\r ENT PEAP0|PEAP1 PSK_TYPE build prof");
                    GTRACE(GRP_CME,"addProfileEap2DB Connecting EAP PEAP v%d-PSK", version);

                    inputProfile->profile.eap.phase2 = (char *)PHASE2_AUTH_TYPE_PSK;
                    //Save phase2 configuration
                    EAP_CONFIG_PHASE2_SET(inputProfile->profile.eap.flags,PSK_TYPE);

                    //Save password
                    // Password must be 16 bytes hex! TODO: is it necessary to check?
                    entSavePassword (passwd, passwd_len, eap_profile_entry, inputProfile);
                    break;

                default:
                    break;
            }
            break;
        case FAST: // FAST
             eap_profile_entry->eap_method.method = EAP_TYPE_FAST;
             inputProfile->profile.eap.eap_method = eap_peer_fast_methods;


             entSaveAnonymousIdentity (anonymous_identity, anonymous_identity_len, eap_profile_entry, inputProfile);

             switch(fast_provisioning)
             {
                 case 0:
                     break;
                 case 1:
                     inputProfile->profile.eap.phase1 = (char *)PROVISIONING_TYPE1;
                     //Save phase1 configuration (0)
                     inputProfile->profile.eap.flags &= ~EAP_CONFIG_FLAGS_PHASE1_FAST;
                     break;
                 case 2:
                     inputProfile->profile.eap.phase1 = (char *)PROVISIONING_TYPE2;
                     //Save phase1 configuration (1)
                     inputProfile->profile.eap.flags |= EAP_CONFIG_FLAGS_PHASE1_FAST;
                     break;
                 case 3:
                     break;
                 default:
                     break;
             }

             //Save password
             entSavePassword (passwd, passwd_len, eap_profile_entry, inputProfile);

             //Set pac file
             //TODO: for now, tell the supplicant to use a blob in memory. Need to handle file per network??
#if 0
             //Set pointers. supplicast receive pointers to these variables and these values need to be saved after reset
             //therefore saved in the file itself. Pointers will be updated again when reading the file (in case address was changed).
             inputProfile->profile.eap.pac_file = (char *)SUPP_FILE_NAME_PAC[cert_index];
#endif
             inputProfile->profile.eap.pac_file = (char *) SUPP_PAC_FILE_MEMORY_BLOB;


             break;
        default:
            ASSERT_GENERAL(0);//should have been checked in command recieval already
    }

    //store updated ent profile to file system
    SetEnterpriseProfile_SetToFlash(pEntProfile, TRUE);

}


/* ----------------------------------------------------------------------------
 addProfile2DB
    This function adds a new profile to local DB. Function may be invoked when
    a new profile is added or when ad-hoc conection is started.
    API should support both.

 Parameters:    apCmd - profile parameters
                aKeyMgmt - management type, WPA_KEY_MGMT_xxx
                apSsid - pointer to SSID
                apPassword - pointer to password
 Return code:   ID of the allocated profile - if everything is OK,
                -1 - if no free entry can be found
---------------------------------------------------------------------------- */
//static int32_t addProfile2DB(_WlanAddGetProfile_t  *apCmd, uint32_t aKeyMgmt,
//                           int8_t *apSsidStr, int8_t *apPassword,
//                           Bool32 aIsAdHoc)
//{
//    Bool32 newProfile = TRUE;
//    uint32_t i, newProfileIndex = CME_SCAN_MAX_PROFILES;
//
//    // Search for new network profile index; can be either an index of a matching
//    // profile or an index of a free entry.
//    for (i=0 ; i<CME_SCAN_MAX_PROFILES ; ++i)
//    {
//        if (CME_INVALID_PROFILE_ID == gPreferredNetworks[i].uniqueProfileId)
//        {
//            // Keep a free index, to be used if no matching profile exists.
//            // If no match is found, profile is added to highest free index.
//            newProfileIndex = i;
//            continue;
//        }
//
//        if (TRUE == compareProfiles(apCmd, aKeyMgmt, &gPreferredNetworks[i].profile))
//        {
//            newProfileIndex = i;
//            newProfile = FALSE;
//            break;
//        }
//    }
//
//    // No free or matching profile was found, can't add the new profile
//    if (CME_SCAN_MAX_PROFILES == newProfileIndex)
//    {
//        GTRACE(GRP_CME, "ERROR: No free entry to add a new profile");
//        return -1;
//    }
//
//    // A free or matching profile was found, for simplicity just set all
//    // parameters even if profile is matching
//    setSharedSsidParams(apCmd, aKeyMgmt, &gPreferredNetworks[newProfileIndex].profile, apSsidStr, apPassword);
//
//    // Mark this entry is in use
//    gPreferredNetworks[newProfileIndex].uniqueProfileId = gUniqueProfileId_ull++;
//
//    // Mark profile isn't a P2P one; for P2P it is updated when setting other
//    // P2P parameters
//    gPreferredNetworks[newProfileIndex].p2pProfile = P2P_NONE;
//
//    if (setSecurityParams(apCmd, &gPreferredNetworks[newProfileIndex].profile, apPassword) < 0)
//    {
//        // TODO - have to remove the profile from DB
//        return -1;
//    }
//
//    GTRACE(GRP_CME, "Added profile to profiles DB; id %d (new %d, ad-hoc %d)", newProfileIndex, newProfile, aIsAdHoc);
//    GTRACE(GRP_CME, "Security type %d password len %d", aKeyMgmt, apCmd->PasswordLen);
//    return newProfileIndex;
//}

/* ----------------------------------------------------------------------------
 addProfile2Supplicant
	This function adds a profile to wpa_supplicant conf data base.
	Implementation is based on ctrl_iface.c functions:
		wpa_supplicant_ctrl_iface_add_network
		wpa_supplicant_ctrl_iface_set_network
		wpa_supplicant_ctrl_iface_select_network
	Instead of filling string buffers with commands all functionality is copied
	to this function.

	The function may be invoked when a new profile is added or when ad-hoc
	conection is started. API should support both.

 Parameters: 	apCmd - profile parameters
                aKeyMgmt - management type, WPA_KEY_MGMT_xxx
 	 	 	 	apSsid - pointer to SSID
 	 	 	 	apPassword - pointer to password
 Return code:   if everything is OK - pointer to new SSID, else - NULL
---------------------------------------------------------------------------- */
//static struct wpa_ssid * addProfile2Supplicant(_WlanAddGetProfile_t  *apCmd, uint32_t aKeyMgmt,
//											   int8_t *apSsidStr, int8_t *apPassword)
//{
//	struct wpa_ssid *pSsid;
//	struct wpa_supplicant *wpa_s;
//
//	// Get STA/P2P CL role is valid and select the correct iface
//	drv_getStaIface(gpSupplicantGlobals, &wpa_s);
//
//	// ----------------------------------------------------------------------------
//	// Add a new network to profiles DB
//	// The add command returns netwrok ID which can be used to disable/remove the network.
//	// Note that supplicant zeros the allocated structure
//	// ----------------------------------------------------------------------------
//	pSsid = wpa_config_add_network(wpa_s->conf);
//	if (NULL == pSsid)
//		return NULL;
//
//	wpas_notify_network_added(wpa_s, pSsid);
//
//	pSsid->disabled = 1;
//	wpa_config_set_network_defaults(pSsid);
//
//	GTRACE(GRP_CME, "Added profile to supplicant conf. SSID %s, supp. profile id %d", (char *)apSsidStr, pSsid->id);
//
//	setSharedSsidParams(apCmd, aKeyMgmt, pSsid, apSsidStr, apPassword);
//
////	// ----------------------------------------------------------------------------
////	// Set network parameters in the DB (based on cc3100 code):
////	// ----------------------------------------------------------------------------
////	switch (apCmd->SecType)
////	{
////		case SL_SEC_TYPE_OPEN:
////
////			break;
////
////		case SL_SEC_TYPE_WEP:
////            setSharedSsidParams(apCmd, WPA_KEY_MGMT_NONE, pSsid, apSsidStr, apPassword);
////			break;
////
////		case SL_SEC_TYPE_WPA_WPA2:
////            setSharedSsidParams(apCmd, WPA_KEY_MGMT_PSK, pSsid, apSsidStr, apPassword);
////			break;
////
////		case SL_SEC_TYPE_WPS_PBC:
////		    // TODO - still missing
////		    ASSERT_GENERAL(0);
////			break;
////
////		case SL_SEC_TYPE_WPS_PIN:
////		    // TODO - still missing
////		    ASSERT_GENERAL(0);
////			break;
////	}
//
//	// NEW
//	if (WPA_KEY_MGMT_PSK == aKeyMgmt)
//	{
//	    char buff[WPA_MAX_PASSPHRASE_LEN + 1];
//
//        if (wpa_config_set(pSsid, "key_mgmt", "WPA-PSK", 0) < 0)
//        {
//            GTRACE(GRP_CME, "ERROR: Failed to set network key mgmt");
//            ASSERT_GENERAL(0);
//        }
//
//        // Set NULL termination to password string
////        memset(buff, 0, WPA_MAX_PASSPHRASE_LEN+1);
////        memcpy(buff, apPassword, apCmd->PasswordLen);
////        if (wpa_config_set(pSsid, "psk", buff, 0) < 0)
////        {
////            GTRACE(GRP_CME, "ERROR: Failed to set network psk");
////            ASSERT_GENERAL(0);
////        }
//	}
//
//	// NEW
////	if (os_strcmp(name, "bssid") != 0 &&
////        os_strcmp(name, "priority") != 0)
//    wpa_sm_pmksa_cache_flush(wpa_s->wpa, pSsid);
//
//	if ( (wpa_s->current_ssid == pSsid) || (NULL == wpa_s->current_ssid) )
//	{
//		/*
//		 * Invalidate the EAP session cache if anything in the current
//		 * or previously used configuration changes.
//		 */
//		eapol_sm_invalidate_cached_session(wpa_s->eapol);
//	}
//
//	// NEW
//	if (WPA_KEY_MGMT_PSK == aKeyMgmt)
//	{
//	    wpa_config_update_psk(pSsid);
//	}
////    else if (os_strcmp(name, "priority") == 0)
//	wpa_config_update_prio_list(wpa_s->conf);
//
//	return pSsid;
//}

/* ----------------------------------------------------------------------------
 removeProfileFromDB
    This function removes a profile from CME DB

    The function may be invoked when a profile is removed or when when ad-hoc
    connection is terminated by the host application.
    If host application removes all profiles, this function is activated in
    a loop.

 Parameters: 	aProfileId - profile ID in supplicant terms

 Return code:   none
---------------------------------------------------------------------------- */

static int32_t removeProfileFromDB(uint32_t aProfileId)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    uint32_t i;
    int32_t  id = -1;
    cmeProfileInfo_t *pProfile;

    //read preferred network from FS now if not previously read
    cmeMngReadPreferredNetworkFromFlash();

    // Look for the the profile, search is based on supplicant profile ID
    for (i=0 ; i<CME_SCAN_MAX_PROFILES ; ++i)
    {
        if (CME_INVALID_PROFILE_ID == gPreferredNetworks[i].uniqueProfileId)
            continue;

        if (aProfileId == gPreferredNetworks[i].profile.id)
        {
            id = i;
            break;
        }
    }

    if (id < 0)
    {
        GTRACE(GRP_CME, "ERROR: Could not find profile id %d in CME DB", aProfileId);
        return -1;
    }

    pProfile = &gPreferredNetworks[i];
    pProfile->uniqueProfileId = CME_INVALID_PROFILE_ID;
    //invalidate blacklist for network
    gPreferredNetworksConnAttemptCnt_ull[i] = CONN_ATTEMPT_INVALID_CTR;
    memset(&pProfile->profile, 0, sizeof(cmeProfileInfo_t));
    pProfile->profile.id = CME_INVALID_PROFILE_ID;

    pProfile->profile.eap.eap_entProfileIndex = CME_INVALID_ENT_IDX;

	GTRACE(GRP_CME, "Successfully removed profile from global DB; supp. id %d profiles DB id %d from CME DB",
	                aProfileId, id);

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

	return 0;
}


/* ----------------------------------------------------------------------------
 removeProfileFromSupplicant
    This function removes a profile from wpa_supplicant conf data base

    The function may be invoked when a profile is removed or when when ad-hoc
    connection is terminated by the host application.
    If host application removes all profiles, this function is activated in
    a loop.

 Parameters:    aProfileId - used to find the profile in supplicant DB

 Return code:   none
---------------------------------------------------------------------------- */
static int32_t removeProfileFromSupplicant(uint32_t aProfileId,int reason_code)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    struct wpa_ssid *pSsid;
    struct wpa_supplicant *wpa_s;

    // Get STA/P2P CL role is valid and select the correct iface
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    pSsid = wpa_config_get_network(wpa_s->conf, aProfileId);
    if (NULL == pSsid)
    {
        GTRACE(GRP_CME, "Failed to get ssid for supplicant profile id %d from supplicant conf", aProfileId);
        return -1;
    }

    // The code below is based on supplicant code, ctrl_iface.c,
    // wpa_supplicant_ctrl_iface_remove_network
    wpas_notify_network_removed(wpa_s, pSsid);

    if (pSsid == wpa_s->current_ssid || wpa_s->current_ssid == NULL)
    {
        /*
         * Invalidate the EAP session cache if the current or
         * previously used network is removed.
         */
#ifdef IEEE8021X_EAPOL
        eapol_sm_invalidate_cached_session(wpa_s->eapol);
#endif
    }

    if (pSsid == wpa_s->current_ssid)
    {
        CME_CON_PRINT("\n\rCME:perform wpa_supplicant_deauthenticate");
        wpa_sm_set_config(wpa_s->wpa, NULL);
#ifdef IEEE8021X_EAPOL
        eapol_sm_notify_config(wpa_s->eapol, NULL, NULL);
#endif
        wpa_supplicant_deauthenticate(wpa_s, reason_code/*WLAN_REASON_DEAUTH_LEAVING*/);
    }

    if (wpa_config_remove_network(wpa_s->conf, aProfileId) < 0)
    {
        GTRACE(GRP_CME, "Failed to remove supplicant profile id %d from supplicant conf", aProfileId);
        return -1;
    }

    GTRACE(GRP_CME, "Successfully removed supplicant profile id %d, # priority lists %d, reason code %d", aProfileId, wpa_s->conf->num_prio,reason_code);
    CME_CON_PRINT("\n\rSuccessfully removed supplicant profile id %d, # priority lists %d, reason code %d", aProfileId, wpa_s->conf->num_prio,reason_code);


    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return 0;
}

void cmeSuppCallbackRemoveNetwork(void *reason_code, struct wpa_ssid *ssid)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    if((ssid->key_mgmt ==  WPA_KEY_MGMT_IEEE8021X)||
            (ssid->key_mgmt ==   WPA_KEY_MGMT_IEEE8021X_SUITE_B_192))
    {
        return;//ENT profile
    }
    removeProfileFromSupplicant(ssid->id,(int)reason_code/*reason_code*/);
}


/**
 * cmeRemoveAllProfilesFromSupplicant - Remove all configured networks
 * @wpa_s: wpa_supplicant structure for a network interface
 * Returns: none
 *
 * Handler function for "RemoveAllNetworks" method call of a network interface.
 */
void cmeRemoveAllProfilesFromSupplicant(struct wpa_supplicant *wpa_s, int reason_code)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    GTRACE(GRP_CME_DEBUG, "Remove all profiles from Supplicant");
    CME_PRINT_REPORT("\n\rRemove all profiles from Supplicant");


    /* NB: could check for failure and return an error */
    wpa_config_foreach_network(wpa_s->conf, cmeSuppCallbackRemoveNetwork, (void *)reason_code);
}

// =============================================
// policy settings API's
// =============================================
static int shouldConnectToOpenAp()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return (!cme_is_p2p_role_configured() && (gCmeConnectionPolicyParams_ull.shouldConnectToOpenAp));
}

static int shouldConnectToAnyP2Pdevice()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return (cme_is_p2p_role_configured() && (gCmeConnectionPolicyParams_ull.shouldConnectToAnyP2P));

}
//
// getPreferredNetworksDbInfo
//
// get number of profiles stored in DB, according to following policy:
// input active_role_entries_only:
//   0 - all entries
//   1 - return entries matching the current active role
// returns: number of preffered networks configured according to input policy (active_role_entries_only)
//
// Added pointer to preferredNetworks, to parameters list
uint8_t getPreferredNetworksDbInfo(cmeProfileInfo_t *preferredNetworks, int active_role_entries_only)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int i;
    uint8_t EnabledEntriesNum = 0;

    for (i = 0; i < CME_SCAN_MAX_PROFILES; i++)
    {
        if((CME_INVALID_PROFILE_ID != preferredNetworks[i].uniqueProfileId) &&
                (
                   (!active_role_entries_only)
                   ||
                   (
                    active_role_entries_only &&
                    ( (cme_is_p2p_role_configured() && WPAS_SSID_IS_P2P_PROFILE(preferredNetworks[i].p2pProfile)) ||
                     (!cme_is_p2p_role_configured() && !WPAS_SSID_IS_P2P_PROFILE(preferredNetworks[i].p2pProfile)))
                   )
                )
          )
        {
            EnabledEntriesNum++;
        }
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return EnabledEntriesNum;
}

//
// isAutoStart
//
// determine if following conditions met:
//    autostart policy is enabled
// AND
//    not in ad hoc connection
// AND
//    active role preffered network profiles exist in DB (STA or P2P)     --- OR --- openAP (for STA) / AnyP2P (for P2P) policy is enabled
//
int isAutoStart(int ignore_auto_start)
{   // Called from supplicant
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    uint32_t anyProfileFound = FALSE;

    if((!ignore_auto_start) && (FALSE == gCmeConnectionPolicyParams_ull.autoStart))
    {
        GTRACE(GRP_CME, "CME isAutoStart: effective AUTO = FALSE, autostart disabled");
        CME_PRINT_PROFILE_REPORT("\r\nCME isAutoStart: effective AUTO = FALSE, autostart disabled");
        return FALSE;
    }

    if(CME_INVALID_PROFILE_ID != gAdHocProfile_ull.uniqueProfileId)
    {
        GTRACE(GRP_CME, "CME isAutoStart: effective AUTO = FALSE: , ad hoc connection active");
        CME_PRINT_PROFILE_REPORT("\r\nCME isAutoStart: effective AUTO = FALSE: , ad hoc connection active");
        return FALSE;
    }

    anyProfileFound = (getPreferredNetworksDbInfo(gPreferredNetworks, 1/*check profiles for active role (P2P or STA)*/) > 0) ? TRUE : FALSE;

    CME_PRINT_PROFILE_REPORT("\n\rCME isAutoStart: anyProfileFound = %d", anyProfileFound);

    if(anyProfileFound == FALSE)
    {
#if CC35XX_SUPPORT_P2P_PROFILE //P2P support or Open AP (depricated)   
        if (shouldConnectToAnyP2Pdevice() || shouldConnectToOpenAp())
        {//connect to any P2P / Open AP forces auto start
            return TRUE;
        }
        GTRACE(GRP_CME, "isAutoStart: effective AUTO = FALSE: no preffered networks found for active role");
#endif // CC35XX_SUPPORT_P2P_PROFILE
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return anyProfileFound;
}

//
// cmeFastConnectionDeAuthHandler
//
// fast connect wpa_disconnected event handler, according to the fast connect state do the following:
// CC33XX Oct 18 - no more! invalidate entry while connected where needed (i.e remote disconnection and not local)
// if was during authentication attempt then:
// 1. if it was the first attempt, issue a second auth attempt (iop issue)
// 2. if it was the second attempt. invalidate the entry and release fast connection timer resources
//
// return 0 if fast connect handling is done
// return 1 if fast connect is continueing to second chance
//
int cmeFastConnectionDeAuthHandler(struct wpa_supplicant *wpa_s)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    _cme_minimized_wpa_ssid_t *pSsid = NULL;
    cmeScanCandidateDesc_t *pFastCandidate = NULL;

    GTRACE(GRP_CME,"cmeFastConnectionDeAuthHandler: gCmeFastConnectionCB_ull.isFastConnectSecondChance=%d ",(uint32_t)gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.isFastConnectSecondChance);
    CME_PRINT_PROFILE_REPORT("\n\rcmeFastConnectionDeAuthHandler: gCmeFastConnectionCB_ull.isFastConnectSecondChance=%d ",(uint32_t)gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.isFastConnectSecondChance);
    // if this is a quick deauth, we give it a second chance
    if ((gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.isFastConnectSecondChance == 1) && shouldUseFastConnect(&pSsid,&pFastCandidate,NULL,NULL,0))
    {//Second chance fast connect
        ASSERT_GENERAL(pSsid!=NULL);
        cmeFastConnectionTimerReleaseResources();
        cmePushFast2ScanResult(pFastCandidate);
        cmeFastConnectAttempt(wpa_s, pSsid, 0);
        return 1; //so that profile manager wont be triggered yet
    }
    else
    {
        //otherwise we invalidate the fast connect and carry on
        cmeMarkInvalidFastConnectionData();

        // Free scan results memory
        // A partial scan results DB was allocated for duplication of fast candidate.
        // Since fast connection failed, revert CME scan ifo to out of reset state.
        CME_ReleaseScanResults(CALLER3);

        //cancel fast connect and fast connect timer
        cmeFastConnectionTimerReleaseResources();

        //release the pending wlan connect command (were not released in the original wlanConnect command)
        //cmeFreePendingWlanConnectResources();
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return 0;
}
//
// cmeFastConnectionTimerReleaseResources
//
// cme fast connect release resources
// called from CME context
//
void cmeFastConnectionTimerReleaseResources()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    if (gCmeFastConnectionCB_ull.gFastConnectTimer!=NULL)
    {
        //kick timer for fast connection
        if (OSI_OK!=osi_TimerStop(gCmeFastConnectionCB_ull.gFastConnectTimer))
        {
            GTRACE(GRP_CME,  "cmeProfileManagerConfigChange: ERROR! Fast connect timer stop failure");
        }

        if (OSI_OK!= osi_TimerDelete(gCmeFastConnectionCB_ull.gFastConnectTimer))
        {
            GTRACE(GRP_CME,  "cmeProfileManagerConfigChange: ERROR! Fast connect timer deletion failure");
        }
#ifndef CC33xx
        os_free(gCmeFastConnectionCB_ull.gFastConnectTimer);
#endif

        gCmeFastConnectionCB_ull.gFastConnectTimer = NULL;
    }

    //disable second chance attempt so that disconnection of fast connect will invalidate and carry on
    gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.isFastConnectSecondChance = 0;

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    GTRACE(GRP_CME,"cmeFastConnectionTimerReleaseResources");
    CME_PRINT_PROFILE_REPORT("\n\rFast connect timer released");


}
//
// cmeFastConnectionTimeoutHandler
//
// cme fast connect timeout frame
// called from timer context
//
void cmeFastConnectionTimeoutHandler(void *param)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    //GTRACE(GRP_CME, "cmeFastConnectionTimeoutHandler: called!");
    //CME_PRINT_REPORT("\n\rFast connect timer expired!");

    CME_fastConnectTimerRelease();

#if 0//handle P2P
    {
        wpas_p2p_disconnect(wpa_s);

        wlanDrvIf_changeCurrentNetDev(TIWDRV_NETIF_ID_P2PDEV);

        markInvalidFastConnectionData();
        wlan_apply_policy_upon_reset_disconn();

    }
#endif
}

//
// cmeFastConnectAttempt
//
// inject supplicant with scan results of the stored ssid
// while faking driver cc33 get scan results as well
//
static void cmeFastConnectAttempt(struct wpa_supplicant *wpa_s,_cme_minimized_wpa_ssid_t *ssid, int first_attempt)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    //allocate timer resources

    gCmeFastConnectionCB_ull.gFastConnectTimer = os_malloc(sizeof(OsiTimer_t));

    if (OSI_OK!= osi_TimerCreate(gCmeFastConnectionCB_ull.gFastConnectTimer,
                    "FastConnectTimer",
                    cmeFastConnectionTimeoutHandler,
                    NULL))
    {
        GTRACE(GRP_CME,  "cmeProfileManagerConfigChange: Fast connect timer creation failure");
        ASSERT_GENERAL(0);
    }

    //kick timer for fast connection
    if (OSI_OK!=osi_TimerStart (gCmeFastConnectionCB_ull.gFastConnectTimer,
                    CME_FAST_CONNECTION_TIMEOUT_MILI_SEC,
                    FALSE))
    {
        GTRACE(GRP_CME,  "cmeProfileManagerConfigChange: Fast connect timer kick failure");
        ASSERT_GENERAL(0);
    }

    CME_PRINT_PROFILE_REPORT("\n\rFast connect timer started for %d ms", CME_FAST_CONNECTION_TIMEOUT_MILI_SEC);

    if (first_attempt)
    {
        //give fast connect a second chance for auth - will be disabled if timedout or if successfully connected
        gCmeFastConnectionCB_ull.cmeFastConnectStatusLabel.isFastConnectSecondChance= 1;
    }

    //first - add profile to supplicant
    addProfile2Supplicant(ssid);

    //set state in STA flow SM with profile manager user
    CME_PRINT_STATE_CHNGE_REPORT("\n\rcmeFastConnectAttempt, change state to CME_STA_FAST_CONNECT_REQ_EVENT !!");

    if (0 != CmeStationFlowSM(CME_STA_FAST_CONNECT_REQ_EVENT,CME_STA_FAST_CONNECT_USER))
    {
        GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set scan in STA flow SM and failed!! ");
        ASSERT_GENERAL(0);
    }

    // force supplicant state to scanning before pushing the results
    wpa_s->wpa_state = WPA_SCANNING;

    wpa_s->disconnected = 0;

    // fake scan results, driver knows how to pull the results from the fast connect
    drv_handleScanCompleteEvent(wpa_s->drv_priv,
                                    SCAN_REQUEST_CONNECT_PERIODIC_SCAN /*fake as it is periodic scan*/,
                                    1 /* one network is detected*/);

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

}
//
// cmeProfileManagerNetworkSearch
//
// profile manager build list and kick scan with ssid list
// for scan module to find highest grade network and ask CME for network selection
//
void cmeProfileManagerNetworkSearch()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    struct wpa_supplicant *wpa_s;

    // Get STA/P2P CL role is valid and select the correct iface
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    ASSERT_GENERAL(wpa_s!=NULL);

    CME_PRINT_STATE_CHNGE_REPORT("\n\rcmeProfileManagerNetworkSearch: change state to :CME_STA_NETWORK_SEARCH_EVENT !!");

    //set state in STA flow SM with profile manager user
    if (0 != CmeStationFlowSM(CME_STA_NETWORK_SEARCH_EVENT,CME_STA_PROFILE_MANAGER_USER))
    {
        GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set scan in STA flow SM and failed!! ");
        ASSERT_GENERAL(0);

    }

    // ================================================================
    //  The below Kicks supplicant connection the below logic is used:
    //      - reset supplicant scan state (to INITIAL_SCAN_REQ)
    //        this allows supplicant to start scanning even when there
    //        aren't any enabled profiles.
    //        See scan conditions in scan.c, wpa_supplicant_scan:
    //              if (!wpa_supplicant_enabled_networks(wpa_s) && wpa_s->scan_req == NORMAL_SCAN_REQ)
    //      - invoke supplicant select API with NULL (meaning any) SSID.
    //      - supplciant starts a one shot scan
    //      - when scan successfully completes (and there's a valid scan
    //        result, the related profile is added to supplicant DB and
    //        only then the result is forwarded to supplicant and
    // ================================================================
    //wpa_s->scan_req = INITIAL_SCAN_REQ; //TODO: temp - to remove
    //cc33xx initiated connection
    wpa_s->cc33xx_initiated_select_network = 1;
    //TODO: set 'wpa_s->scan_min_time' to 0 or get current rel time?
    wpa_supplicant_select_network(wpa_s, NULL);

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

}
//
// cmeProfileManagerConfigChange
//
// profile manager evaluate state and activate scans and connection sequences according to system state
// and to connection poilcies
//
// input: none
//
void cmeProfileManagerConfigChange(int force_one_shot_profile_search, uint8_t caller)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    struct wpa_supplicant *wpa_s;
    GTRACE(GRP_CME,"cmeProfileManagerConfigChange: consider profile search");


#if CC35XX_SUPPORT_P2P_PROFILE
    if (cme_is_p2p_role_configured())
    {//P2P profile manager handler
        
    GTRACE(GRP_CME,"cmeProfileManagerConfigChange: [p2p profile manager]: TBD");
    return;
 
        struct wpa_supplicant * wpa_s = wpa_supplicant_get_current_iface();

        if (wilink_get_drv_role() == TIWDRV_ROLE_TYPE_P2PDEV && wpa_s->wpa_state != WPA_SCANNING &&
                (FALSE == isUnicastConnInProgress()))
        {

            //TODO p2p - block in case of connected P2P-CL or operational P2P-GO link
            SOC_TRACE3(DBG_MSG, MSG_933, "SimpleManager: policy/config changed, wpa_state = %d, isUnicastConnInProgress = %d, isAutoStart = %d",
                                        wpa_s->wpa_state,
                                        isUnicastConnInProgress(),
                                        isAutoStart());
            if(isAutoStart())
            {
                wlan_sta_p2p_manager_auto_start();
            }
        }

        ASSERT_GENERAL(0);//P2P not supported yet
    }
    else if (cme_is_sta_role_like_activated())
#else // CC35XX_SUPPORT_P2P_PROFILE 
    if (cme_is_sta_role_like_activated())
#endif
    {
        CME_PRINT_PROFILE_REPORT("\r\nCME: cmeProfileManagerConfigChange: force_one_shot_profile_search=%d caller=%d",
                             force_one_shot_profile_search, caller);
        //indexing of the connecting profile - relevant for profile search only
        gConnectingIndex_ull = CONN_ATTEMPT_INVALID_IDX;

        //clear consecutive scan compelte counter
        gConnSecutiveScanCompletes_ull = 0;

        //read preferred network from FS now if not previously read
        cmeMngReadPreferredNetworkFromFlash();

        GTRACE(GRP_CME,"cme_is_sta_role_like_activated");
        // Get STA/P2P CL role is valid and select the correct iface
        if(drv_getStaIface(gpSupplicantGlobals, &wpa_s) == ROLE_TYPE_NONE)
        {
            GTRACE(GRP_CME,"drv_getStaIface is ROLE_TYPE_NONE");
            CME_PRINT_PROFILE_REPORT("\r\ncmeProfileManagerConfigChange: Role STA is activated "
                                         "but drv_getStaIface returned ROLE_TYPE_NONE");
            return;
        }

        ASSERT_GENERAL(wpa_s!=NULL);
//
//CC33XX Oct 6 2016- well, its time for some changes around here in the fast connect domain
//                          start adapting to intermittent mode.
//                          from now on, fast connect will be triggered after warm boot (with a command or internally)
//                          and not make an automatic attempt after cold boot
//
#if 1
        _cme_minimized_wpa_ssid_t *pSsid = NULL;
        cmeScanCandidateDesc_t *pFastCandidate = NULL;

        // FAST connect handler in case it is INIT call + fast connect policy set + fast connection is stored in FS
        //if ( (init_caller!=FALSE) && shouldUseFastConnect(&pSsid,&pFastCandidate) )
        if ( (CALLER1 == caller) && shouldUseFastConnect(&pSsid, &pFastCandidate, NULL, NULL, 0) )
        {
            ASSERT_GENERAL(NULL != pSsid);
            ASSERT_GENERAL(NULL != pFastCandidate);

            // Push fast candidate to scan results DB. From this point it shall
            // be treated in the system (mainly driver_cc) as valid result.
            cmePushFast2ScanResult(pFastCandidate);

            //trigger fast connect attempt:
            cmeFastConnectAttempt(wpa_s, pSsid, 1);
        }
        else
#endif
        {
            if ( CmeStationFlowIsSMIdle() )
            {

                GTRACE(GRP_CME,"CmeStationFlowIsSMIdle");
                CME_PRINT_PROFILE_REPORT("\r\n ProfileManagerConfig: CmeStationFlow is IDLE, force_one_shot_profile_search=%d",
                                         force_one_shot_profile_search);                         
                if((!gFwCrashOccurred) && isAutoStart(force_one_shot_profile_search))
                {

                    //
                    //only if STA is in idle state AND auto start policy is enabled we can issue network search request action on wlan connect user
                    //

                    cmeProfileManagerNetworkSearch();
                }

            }
            //cme not in idle - ask if wpa in scanning
            else if((wpa_s->wpa_state == WPA_SCANNING)
                     &&
                     (gAdHocProfile_ull.uniqueProfileId == CME_INVALID_PROFILE_ID) //make sure not ad hoc connection scan
    #ifndef SL_DISABLE_PROVISIONING
                            &&
                            !smartConfigCB.smart_config_in_sync
    #endif
                   )  //and not scanning during smart config
            {
                /* stop scan only if it is not unicast scan!
                   I.e. only if we're in in scan for prefrerred network.
                   If AUTO == FALSE or no preferred networks -
                   no scan will be done,
                   If both are TRUE -scan will be started from
                   wpa_supplicant_event_scan_complete */

                GTRACE(GRP_CME,"send CME_STA_WLAN_DISCONNECT_REQ_EVENT");
                CME_PRINT_STATE_CHNGE_REPORT("\r\nCME:  cmeProfileManagerConfigChange ,change state to :CME_STA_WLAN_DISCONNECT_REQ_EVENT");
                if (0 != CmeStationFlowSM(CME_STA_WLAN_DISCONNECT_REQ_EVENT,CME_STA_PROFILE_MANAGER_USER))
                {
                   GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set disconnect in STA flow SM and failed!! ");
                   ASSERT_GENERAL(0);
                }

                //if state was scanning and disconnect called - 2 cases:
                //1 - scan was immediately stopped - sm is idle - determine if auto start profile search should be triggered

                if (CmeStationFlowIsSMIdle())
                {
                    GTRACE(GRP_CME, "CME: policy/config changes, stopped connection scan, issue network search if needed");
                    CME_PRINT_PROFILE_REPORT("\r\nCME: policy/config changes, stopped connection scan, issue network search if needed");

                    if((!gFwCrashOccurred) && isAutoStart(force_one_shot_profile_search))
                    {
                        cmeProfileManagerNetworkSearch();
                    }
                }
                else
                {
                    //else -
                    //2 - scan was immediately stopped - sm is idle - determine if auto start profile search should be triggered
                    GTRACE(GRP_CME, "CME: policy/config changes, connection scan stop request sent - wait for scan complete to carry on");
                    CME_PRINT_PROFILE_REPORT("\r\nCME: policy/config changes, connection scan stop request sent - wait for scan complete to carry on");
                }

            } // if supplicant is in scanning state
            else
            {
                GTRACE(GRP_CME, "CME: policy/config changed, wpa_state = %d, uniqueProfileId = 0x%x, policy change not applied",
                                   wpa_s->wpa_state, gAdHocProfile_ull.uniqueProfileId);
                CME_PRINT_PROFILE_REPORT("\r\nCME: policy/config changed, wpa_state = %d, uniqueProfileId = 0x%x, policy change not applied",
                                   wpa_s->wpa_state, gAdHocProfile_ull.uniqueProfileId);

            }
        }
    }
    else
    {
        GTRACE(GRP_CME,"SimpleManager: Profile Changed although current role != STA and != P2P ");
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

}

/* ----------------------------------------------------------------------------
 convertAsciiString2Hex
    Imported from cc3100 (SimpleManager.c)
    Converts a string that contains Hex characters to Hex format.
    Example: The string: "12345ABCED" (0x31,0x32,0x33,0x34,0x35,0x41,0x42,0x43,0x44,0x45)
             Will be changed to: (0x12,0x34,0x5A,0xBC,0xDE)

 Parameters:    OUT pDest - destination for converted string
                IN  pString - string to be converted
                IN  length - input string length
 Return code:   none
---------------------------------------------------------------------------- */
void convertAsciiString2Hex(int8_t *dest, int8_t *pString, uint32_t aLength)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    char tempString[PMK_LEN+1];
    uint32_t i;

    for(i = 0 ; i < aLength/2 ; i++)
    {
        if(pString[i*2] > '9')
        {
            tempString[i] = (((pString[i*2] - 0x37) << 4) & 0xF0);
        }
        else
        {
            tempString[i] = (((pString[i*2] - 0x30) << 4) & 0xF0);
        }

        if(pString[i*2+1] > '9')
        {
            tempString[i] |= ((pString[i*2+1] - 0x37) & 0x0F);
        }
        else
        {
            tempString[i] |= ((pString[i*2+1] - 0x30) & 0x0F);
        }
    }

    os_memcpy(dest, tempString, aLength/2);
}


/* ----------------------------------------------------------------------------
 setSharedSsidParams
         Write all shared profile parameters to a new profile.

         Note: profiles are reset (all fields are set to 0) on CME init.
               A profile is reset when removed from DB.

 Parameters:    IN apCmd - pointer to the add profile command
                IN aKeyMgmt - type of management key
                OUT apSsid - pointer to the profile to be updated
                IN apSsidStr - pointer to profile SSID
                IN apPassword - pointer to the profile password

 Return code:   none
---------------------------------------------------------------------------- */
static void setSharedSsidParams(CMEWlanAddGetProfile_t *apCmd,
                                uint32_t               aKeyMgmt,
                                _cme_minimized_wpa_ssid_t 	 *apSsid,
								int8_t 				 *apSsidStr,
								int8_t 				 *apPassword)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

	char macStr[MAC_STR_LEN];

	os_memcpy(apSsid->ssid, apSsidStr, apCmd->SsidLen);
	apSsid->ssid_len = apCmd->SsidLen;
	apSsid->priority = apCmd->Priority;
	apSsid->mode = WPAS_MODE_INFRA;

	// Set password, if valid
#if 0//S - passphrase should not be dynamically allocated
	if (apCmd->PasswordLen && NULL != apPassword)
	{
	    if (apSsid->passphrase == NULL)
	    {
	        //allocate the first time only
	        apSsid->passphrase = os_malloc(apCmd->PasswordLen);
	    }

        if (NULL == apSsid->passphrase)
        {
            GTRACE(GRP_CME, "failed to allocate memory for profile password");
            ASSERT_GENERAL(0);
        }
        memcpy(apSsid->passphrase, apPassword, apCmd->PasswordLen);
	}
#endif

	// When set, scan_ssid field indicates hidden SSID.
	// Currently (cc3100, R2) there's no user application API for controlling
	// this field. Unicast probe requests are transmitted in order to reduce
	// the amount of probe response packets.
	apSsid->scan_ssid = CME_ALL_PROFILES_ARE_HIDDEN;

	if (IRQ_UtilIsZeroMacAddress((const uint8_t *)apCmd->Bssid) == FALSE)
	{
		IRQ_UtilCopyMacAddress(apCmd->Bssid, apSsid->bssid);
		apSsid->bssid_set = 1;

		// debug - remove 25/6
		GET_MAC_STR(apSsid->bssid, macStr);
		GTRACE(GRP_CME, "setting bssid_set, BSSID is %s", macStr);
	}
	else
	{
	    IRQ_UtilZeroMacAddress(apSsid->bssid);
	    apSsid->bssid_set = 0;
	}

	apSsid->key_mgmt = aKeyMgmt;
	apSsid->secType  = (u8) apCmd->SecType;

    HOOK(HOOK_IN_CME_CONNECTION_MNG);
}

/* ----------------------------------------------------------------------------
 setSecurityParams
         Add security specific parameters to a new profile.

 Parameters:    apCmd - pointer to the add profile command
                apSsid - pointer to the profile to be updated
                apPassword - pointer to the profile password

 Return code:   0 - on success
---------------------------------------------------------------------------- */
static int32_t duplicateSecurityParams(const _cme_minimized_wpa_ssid_t *apInputApSsid,
                                     struct wpa_ssid       *apSsid
                              )
{
    uint32_t pass_len;
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    if (apInputApSsid->auth_alg == WPA_AUTH_ALG_OPEN || apInputApSsid->auth_alg == WPA_AUTH_ALG_SHARED)
    {
        uint32_t i;
        //WEP/WEP_SHARED
        apSsid->auth_alg = apInputApSsid->auth_alg;
        apSsid->wep_tx_keyidx = apInputApSsid->wep_tx_keyidx;

        for (i = 0; i < NUM_WEP_KEYS; i++)
        {
            os_memcpy(apSsid->wep_key[i], apInputApSsid->wep_key[i], sizeof(apInputApSsid->wep_key[i]));
            apSsid->wep_key_len[i] = apInputApSsid->wep_key_len[i];
        }
    }
    GTRACE(GRP_CME, "if apInputApSsid->key_mgmt %d, psk_set = %d",((apInputApSsid->key_mgmt) & (WPA_KEY_MGMT_PSK|WPA_KEY_MGMT_PSK_SHA256)));
    GTRACE(GRP_CME, "WPA_KEY_MGMT_PSK (%d),WPA_KEY_MGMT_PSK_SHA256 (%d), WPA_KEY_MGMT_PSK|WPA_KEY_MGMT_PSK_SHA256 (%d) -psk_set",
        WPA_KEY_MGMT_PSK, WPA_KEY_MGMT_PSK_SHA256, WPA_KEY_MGMT_PSK|WPA_KEY_MGMT_PSK_SHA256);

    // 22/12/15 - duplicate key mng anyway
    // 18/03/19 - Added support for SHA256 for pmf
    if (((apInputApSsid->key_mgmt) & (WPA_KEY_MGMT_PSK|WPA_KEY_MGMT_PSK_SHA256|WPA_KEY_MGMT_SAE)) > 0)
    {
        //WPA2
        apSsid->key_mgmt = apInputApSsid->key_mgmt;

        apSsid->pairwise_cipher = apInputApSsid->pairwise_cipher;
        apSsid->group_cipher = apInputApSsid->group_cipher;
        apSsid->proto = apInputApSsid->proto;
        apSsid->auth_alg = apInputApSsid->auth_alg;
        GTRACE(GRP_CME, "apInputApSsid-psk_set %d",apInputApSsid->psk_set);

        if (apInputApSsid->psk_set)
        {
            os_memcpy(apSsid->psk, apInputApSsid->psk, PMK_LEN);
            apSsid->psk_set = 1;
        }
        if((apInputApSsid->key_mgmt & WPA_KEY_MGMT_SAE) == WPA_KEY_MGMT_SAE)
        {
            pass_len = os_strlen(apInputApSsid->passphrase);
            apSsid->sae_password = os_zalloc(pass_len + 1);
            os_memcpy(apSsid->sae_password , apInputApSsid->passphrase, pass_len);
            apSsid->sae_password[pass_len] = 0;

            GTRACE(GRP_CME, "set passphrase for wpa3");
        }

        GTRACE(GRP_CME, "pSsid-psk_set %d",apSsid->psk_set);

        apSsid->group_mgmt_cipher   = apInputApSsid->group_mgmt_cipher;
        apSsid->ieee80211w          = apInputApSsid->ieee80211w;

    }
//    else
//    {
//        GTRACE(GRP_CME,"duplicateSecurityParams: no security found of type WPA2 / WEP for duplication");
//    }

    GTRACE(GRP_CME,"duplicateSecurityParams: auth alg 0x%x key mgmt 0x%x",
                    apInputApSsid->auth_alg, apInputApSsid->key_mgmt);

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return 0;
}



/* ----------------------------------------------------------------------------
 setSecurityParams
         Add security specific parameters to a new profile.

 Parameters:    apCmd - pointer to the add profile command
                apSsid - pointer to the profile to be updated
                apPassword - pointer to the profile password

 Return code:   0 - on success
---------------------------------------------------------------------------- */
static int32_t setSecurityParams(CMEWlanAddGetProfile_t *apCmd,
                               _cme_minimized_wpa_ssid_t      *apSsid,
                              int8_t                 *apPassword)
{
    int32_t rc = 0;

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    switch (apCmd->SecType)
    {
        case CME_SEC_TYPE_WEP:
        case CME_SEC_TYPE_WEP_SHARED:
        {
            uint32_t keyLen = apCmd->PasswordLen;
            uint32_t i;

            HOOK(HOOK_IN_CME_CONNECTION_MNG);

            apSsid->auth_alg = WPA_AUTH_ALG_OPEN;
            if (CME_SEC_TYPE_WEP_SHARED == apCmd->SecType)
                apSsid->auth_alg = WPA_AUTH_ALG_SHARED;

            if ( (WEP40_HEX_KEY_LENGTH == keyLen) || (WEP104_HEX_KEY_LENGTH == keyLen) )
            {
                // string contains Hex password, convert it to Hex format
                convertAsciiString2Hex(apPassword, apPassword, keyLen);
                keyLen = keyLen/2;
            }

            apSsid->wep_tx_keyidx = apCmd->WepKeyId;

            for (i = 0; i < NUM_WEP_KEYS; i++)
            {
                os_memcpy(apSsid->wep_key[i], apPassword, keyLen);
                apSsid->wep_key_len[i] = keyLen;
            }
        }
        break;

        case CME_SEC_TYPE_WPA2_FT:
        case CME_SEC_TYPE_WPA_WPA2:
        {
            uint8_t ft = (apCmd->SecType == CME_SEC_TYPE_WPA2_FT) || apCmd->FastTransition;
            uint32_t passPhraseLen = apCmd->PasswordLen;

            HOOK(HOOK_IN_CME_CONNECTION_MNG);

            // TODO - 23.07.15 - remove key mng from API and set sharedssid and set it here

            // 18/03/19 - Added support for SHA256 for pmf
			apSsid->key_mgmt = WPA_KEY_MGMT_PSK | WPA_KEY_MGMT_PSK_SHA256;
            apSsid->pairwise_cipher = CME_STA_WPA_DEFAULT_CIPHER;
            apSsid->group_cipher = CME_STA_WPA_DEFAULT_CIPHER;
            apSsid->proto = DEFAULT_PROTO;
            apSsid->auth_alg = WPA_AUTH_ALG_OPEN;
            apSsid->psk_set = 0;
            //apSsid->ieee80211w = MGMT_FRAME_PROTECTION_OPTIONAL;

            if (ft)
            {
                apSsid->key_mgmt |= WPA_KEY_MGMT_FT_PSK;
                apSsid->auth_alg |= WPA_AUTH_ALG_FT;
            }

            if (WPA_HEX_PASSPHRASE_LENGTH == passPhraseLen)
            {
                // string contains Hex password, convert it to Hex format
                convertAsciiString2Hex(apPassword, apPassword, passPhraseLen);
                os_memcpy(apSsid->psk, apPassword, PMK_LEN);
                apSsid->psk_set = 1;
            }
            else
            {
                if (apCmd->SsidLen > 0)
                {
                    // 05.01.15 bug fix - apCmd doesn't contain SSID & password,
                    // hence they should be taken from explicit parameters
                    // wlan_calculate_pmk(apCmd->SsidLen, SSID_STRING(apCmd), PASSWORD_STRING(apCmd), passPhraseLen, apSsid->psk);
                    CME_PRINT_REPORT("\n\rCME: wlan_calculate_pmk :SsidLen: %d ssid[0]:%c apPassword:%s passPhraseLen:%d apSsid->psk:%s",
                                     apCmd->SsidLen,apSsid->ssid[0],apPassword,passPhraseLen,apSsid->psk);
                    wlan_calculate_pmk(apCmd->SsidLen, (int8_t *)apSsid->ssid, (int8_t *)apPassword, passPhraseLen, apSsid->psk);

                    apSsid->psk_set = 1;
                }
                else
                {
                    // SSID not known yet, save password for calculating PMK on scan result.
                    apSsid->passphrase = os_malloc(passPhraseLen+1);
                    if (apSsid->passphrase)
                    {
                        os_memset (apSsid->passphrase,0,  passPhraseLen+1);
                        os_memcpy (apSsid->passphrase, apPassword, passPhraseLen);
                    }
                }
            }

        }
        break;
        case CME_SEC_TYPE_WPA2_PLUS_FT:
        case CME_SEC_TYPE_WPA2_PLUS:
        {
            uint8_t ft = (apCmd->SecType == CME_SEC_TYPE_WPA2_PLUS_FT) || apCmd->FastTransition;
            uint32_t passPhraseLen = apCmd->PasswordLen;

            HOOK(HOOK_IN_CME_CONNECTION_MNG);

            // TODO - 23.07.15 - remove key mng from API and set sharedssid and set it here

            // 18/03/19 - Added support for SHA256 for pmf
            apSsid->key_mgmt = WPA_KEY_MGMT_PSK | WPA_KEY_MGMT_PSK_SHA256;
            apSsid->pairwise_cipher = CME_STA_WPA_DEFAULT_CIPHER; // TODO
            apSsid->group_cipher = CME_STA_WPA_DEFAULT_CIPHER;
            apSsid->proto = DEFAULT_PROTO;
            apSsid->auth_alg = WPA_AUTH_ALG_OPEN;

            if (ft)
            {
                apSsid->key_mgmt |= WPA_KEY_MGMT_FT_PSK;
                apSsid->auth_alg |= WPA_AUTH_ALG_FT;
            }

            if (WPA_HEX_PASSPHRASE_LENGTH == passPhraseLen)
            {
                // string contains Hex password, convert it to Hex format
                convertAsciiString2Hex(apPassword, apPassword, passPhraseLen);
                os_memcpy(apSsid->psk, apPassword, PMK_LEN);
                apSsid->psk_set = 1;
            }
            else
            {
                if (apCmd->SsidLen > 0)
                {
                    // 05.01.15 bug fix - apCmd doesn't contain SSID & password,
                    // hence they should be taken from explicit parameters
                    // wlan_calculate_pmk(apCmd->SsidLen, SSID_STRING(apCmd), PASSWORD_STRING(apCmd), passPhraseLen, apSsid->psk);
                    wlan_calculate_pmk(apCmd->SsidLen, (int8_t *)apSsid->ssid, (int8_t *)apPassword, passPhraseLen, apSsid->psk);

                    apSsid->psk_set = 1;
                }
                else
                {
                    // SSID not known yet, save password for calculating PMK on scan result.
                    apSsid->passphrase = os_malloc(passPhraseLen+1);
                    if (apSsid->passphrase)
                    {
                        os_memset (apSsid->passphrase,0,  passPhraseLen+1);
                        os_memcpy (apSsid->passphrase, apPassword, passPhraseLen);
                    }
                }
            }

            //apSsid->group_mgmt_cipher   = WPA_CIPHER_AES_128_CMAC;
            apSsid->ieee80211w          = MGMT_FRAME_PROTECTION_OPTIONAL;

        }
        break;

#ifdef CONFIG_SAE
        case CME_SEC_TYPE_WPA3_FT:
        case CME_SEC_TYPE_WPA3:
        {
            uint8_t ft = (apCmd->SecType == CME_SEC_TYPE_WPA3_FT) || apCmd->FastTransition;
            uint32_t passPhraseLen = apCmd->PasswordLen;

            HOOK(HOOK_IN_CME_CONNECTION_MNG);

            // Added support for SHA256 for WPA3
			apSsid->key_mgmt            = WPA_KEY_MGMT_SAE;
            apSsid->pairwise_cipher     = CME_STA_WPA_DEFAULT_CIPHER; // TODO
            apSsid->group_cipher        = CME_STA_WPA_DEFAULT_CIPHER;
            apSsid->proto               = DEFAULT_PROTO;
            apSsid->auth_alg            = WPA_AUTH_ALG_OPEN; //WPA_AUTH_ALG_SAE;
            apSsid->group_mgmt_cipher   = WPA_CIPHER_AES_128_CMAC;

            apSsid->ieee80211w          = MGMT_FRAME_PROTECTION_REQUIRED;

            if (ft)
            {
                apSsid->key_mgmt |= WPA_KEY_MGMT_FT_SAE;
                apSsid->auth_alg |= WPA_AUTH_ALG_FT;
            }

            apSsid->passphrase = os_malloc(passPhraseLen+1);
            if (apSsid->passphrase)
            {
                os_memset (apSsid->passphrase,0,  passPhraseLen+1);
                os_memcpy (apSsid->passphrase, apPassword, passPhraseLen);
            }
            else
            {
                ASSERT_GENERAL(0);
            }

            apSsid->psk_set = 0;
        }
        break;

        case CME_SEC_TYPE_WPA2_WPA3_FT:
        case CME_SEC_TYPE_WPA2_WPA3:
        {
            uint8_t ft = (apCmd->SecType == CME_SEC_TYPE_WPA2_WPA3_FT) || apCmd->FastTransition;
            uint32_t passPhraseLen = apCmd->PasswordLen;

            HOOK(HOOK_IN_CME_CONNECTION_MNG);

            // TODO - 23.07.15 - remove key mng from API and set sharedssid and set it here

            // 18/03/19 - Added support for SHA256 for pmf
            apSsid->key_mgmt = WPA_KEY_MGMT_PSK | WPA_KEY_MGMT_PSK_SHA256 | WPA_KEY_MGMT_SAE;
            apSsid->pairwise_cipher = CME_STA_WPA_DEFAULT_CIPHER; // WPA_CIPHER_CCMP; // TODO
            apSsid->group_cipher = CME_STA_WPA_DEFAULT_CIPHER; //WPA_CIPHER_CCMP;
            apSsid->proto = DEFAULT_PROTO;
            apSsid->auth_alg = WPA_AUTH_ALG_OPEN;
            apSsid->psk_set = 0;
            apSsid->ieee80211w = MGMT_FRAME_PROTECTION_OPTIONAL;
            //apSsid->group_mgmt_cipher   = WPA_CIPHER_AES_128_CMAC;

            if (ft)
            {
                apSsid->key_mgmt |= WPA_KEY_MGMT_FT_PSK | WPA_KEY_MGMT_FT_SAE;
                apSsid->auth_alg |= WPA_AUTH_ALG_FT;
            }

            if (WPA_HEX_PASSPHRASE_LENGTH == passPhraseLen)
            {
                // string contains Hex password, convert it to Hex format
                convertAsciiString2Hex(apPassword, apPassword, passPhraseLen);
                os_memcpy(apSsid->psk, apPassword, PMK_LEN);
                apSsid->psk_set = 1;
            }
            else
            {
                if (apCmd->SsidLen > 0)
                {
                    // 05.01.15 bug fix - apCmd doesn't contain SSID & password,
                    // hence they should be taken from explicit parameters
                    // wlan_calculate_pmk(apCmd->SsidLen, SSID_STRING(apCmd), PASSWORD_STRING(apCmd), passPhraseLen, apSsid->psk);
                    wlan_calculate_pmk(apCmd->SsidLen, (int8_t *)apSsid->ssid, (int8_t *)apPassword, passPhraseLen, apSsid->psk);

                    apSsid->psk_set = 1;
                }
                
                // Set passphrase for WPA3
                apSsid->passphrase = os_malloc(passPhraseLen+1);
                if (apSsid->passphrase)
                {
                    os_memset(apSsid->passphrase,0,  passPhraseLen+1);
                    os_memcpy(apSsid->passphrase, apPassword, passPhraseLen);
                }
            }

        }
        break;
#endif


// TODO need implementation
#if 0
        case CME_SEC_TYPE_WPS_PBC:
            // Note: WPS is used only in connect command

//            rc = wpas_wps_start_pbc(wpa_supplicant_get_current_iface(), NULL, 0);
            // TODO - still missing
            ASSERT_GENERAL(0);
            break;

        case SL_SEC_TYPE_WPS_PIN:
            // Note: WPS is used only in connect command
            {
                // Make sure correct key is supplied
                if (NULL != apPassword)
                {
                    //TODO: memory overight? what if the len is exactly the PIN len?
                    //apPassword[P2P_PIN_CODE_LEN] = NULL; // WPS pin has a constant length, make sure it's null-terminated.

                    if (WPS_PIN_LEN == os_strlen((const char *)apPassword))
                    {
                        // TODO
                        // rc = wpas_wps_start_pin(wpa_supplicant_get_current_iface(), NULL, (char *)pKey, 0, DEV_PW_DEFAULT);
                    }
                }
#ifdef WPS_DEBUG
                else //No pin supplied. Use default pin
                {
                    sl_error_handler_report(SL_ERR_DISPATCHER,SL_ERROR_WPS_NO_PIN_OR_WRONG_PIN_LEN);
                    pin = atoi(defaultPinBuff);
                    SOC_TRACE1(WLINK_MSG, MSG_2621, "WPS PIN=%d", pin);
                    rc = wpas_wps_start_pin(wpa_supplicant_get_current_iface(), NULL, defaultPinBuff, 0, DEV_PW_DEFAULT);
                }
#else
                else //In case no pin supplied, notify host
                     // This could be filtered profile sanity check; as in cc3100
                     // do it here to allow WPA debug.
                {
                    GTRACE(GRP_CME, "ERROR: WPS PIN was NOT supplied or the pin length is different then 8!");
                    sl_error_handler_report(SL_DEVICE_SOURCE_WLAN,SL_ERROR_WPS_NO_PIN_OR_WRONG_PIN_LEN);
                    rc = SL_ERROR_WLAN_WPS_NO_PIN_OR_WRONG_PIN_LEN;
                }
#endif
            }
            // TODO - still missing
            ASSERT_GENERAL(0);
            break;
#endif
        case CME_SEC_TYPE_OPEN:
        default:
            HOOK(HOOK_IN_CME_CONNECTION_MNG);
            // nothing to do here
            break;
    } // switch (apCmd->SecType)

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    CME_PRINT_REPORT("\n\r[ti_drv] Set security for %.*s: Alg=%x, kMgmt=%x \n",
        apSsid->ssid_len, apSsid->ssid, apSsid->auth_alg, apSsid->key_mgmt); 
    return rc;
}

/* ----------------------------------------------------------------------------
duplicateSharedSsidParams
         Duplicate all shared profile parameters to a new profile.

Parameters:
        IN  apInputApSsid - pointer to the profile to be copied from
        OUT apSsid - pointer to the profile to be updated

Return code:   none
---------------------------------------------------------------------------- */
static void duplicateSharedSsidParams(const _cme_minimized_wpa_ssid_t *apInputApSsid,
                                      struct wpa_ssid       *apSsid)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    // Set SSID
    if (0 != apInputApSsid->ssid_len)
    {
        //for supplicant we must allocate the ssid
        apSsid->ssid = os_zalloc(apInputApSsid->ssid_len + 1);
        if (NULL == apSsid->ssid)
        {
            GTRACE(GRP_CME, "failed to allocate %d bytes for SSID", apInputApSsid->ssid_len);
            ASSERT_GENERAL(0);
            return;
        }
        os_memcpy(apSsid->ssid, apInputApSsid->ssid, apInputApSsid->ssid_len);
        apSsid->ssid[apInputApSsid->ssid_len] = '\0';//for print purpose
    }
    apSsid->ssid_len = apInputApSsid->ssid_len;
    apSsid->priority = apInputApSsid->priority;
    apSsid->mode = apInputApSsid->mode;

    // TODO Set password, if valid - this is a string, sizeof won't work here
#if 0
    if (apInputApSsid->passphrase != NULL)
    {
        apSsid->passphrase = os_malloc(sizeof(apInputApSsid->passphrase));
        if (NULL == apSsid->passphrase)
        {
            GTRACE(GRP_CME, "failed to allocate memory for profile password");
            ASSERT_GENERAL(0);
        }
        memcpy(apSsid->passphrase, apInputApSsid->passphrase, sizeof(apInputApSsid->passphrase));
    }
#endif

    apSsid->scan_ssid = apInputApSsid->scan_ssid ;

    //check init bssid
    if(IRQ_UtilIsZeroMacAddress(apInputApSsid->bssid) == FALSE)
    {
        IRQ_UtilCopyMacAddress(apInputApSsid->bssid, apSsid->bssid);
        apSsid->bssid_set = apInputApSsid->bssid_set;
    }

    apSsid->key_mgmt = apInputApSsid->key_mgmt;

    apSsid->group_mgmt_cipher = apInputApSsid->group_mgmt_cipher;
    apSsid->ieee80211w       = apInputApSsid->ieee80211w;//PMF enable/disable

    CME_PRINT_REPORT("\n\rAdding profile to the supplicant: %s ssid_len: %d priority: %d mode: %d"
            " scan_ssid: %d key_mgmt: 0x%x \n\rgroup_mgmt_cipher: 0x%x ieee80211w: %d\n\r",
            apSsid->ssid,
            apSsid->ssid_len,
            apSsid->priority,
            apSsid->mode,
            apSsid->scan_ssid,
            apSsid->key_mgmt,//for LTS:WPA_KEY_MGMT_IEEE8021X
            apSsid->group_mgmt_cipher,
            apSsid->ieee80211w);

    if(apSsid->bssid_set)
    {
        CME_PRINT_REPORT("bssid:"MACSTR "\n\r",MAC2STR(apInputApSsid->bssid));
    }


    HOOK(HOOK_IN_CME_CONNECTION_MNG);
}


/* ----------------------------------------------------------------------------
duplicateEapProfile
         Duplicate all eap params

Parameters:
        IN  apInputApSsid - pointer to the profile to be copied from
        OUT apSsid - pointer to the profile to be updated

Return code:   none
---------------------------------------------------------------------------- */

static void duplicateEapProfile( struct wpa_supplicant *wpa_s,
                                 const _cme_minimized_wpa_ssid_t *apInputApSsid,
                                 struct wpa_ssid       *apSsid)
{

    int len =0;
    os_memset(&apSsid->eap,0, sizeof(apSsid->eap));
    apSsid->proto = apInputApSsid->proto;//WPA_PROTO_RSN
    apSsid->key_mgmt = apInputApSsid->key_mgmt;
    apSsid->group_cipher = apInputApSsid->group_cipher;//WPA_CIPHER_CCMP for TLS
    apSsid->pairwise_cipher = apInputApSsid->pairwise_cipher;//WPA_CIPHER_CCMP for TLS
    apSsid->auth_alg = apInputApSsid->auth_alg;//WPA_AUTH_ALG_OPEN = 1

    #ifdef IEEE8021X_EAPOL
    apSsid->eap.fragment_size = apInputApSsid->eap.fragment_size;
    apSsid->eapol_flags = apInputApSsid->eapol_flags;
    apSsid->eap_workaround = apInputApSsid->eap_workaround;
    #endif /* IEEE8021X_EAPOL */

    //if(apInputApSsid->isSuiteb192)
    if(apInputApSsid->eapol_flags & EAPOL_FLAG_SUITEB_ONLY)
    {

        // this will be transfered to tls_mbedtls_set_params and will set the ciphers
        // that will be publish on client hello"
        apSsid->eap.openssl_ciphers = os_zalloc(strlen("SUITEB192") + 1);
        if(apSsid->eap.openssl_ciphers == NULL)
        {
            CME_ENT_PRINT_REPORT_ERROR("\n\r ERROR! pSsid->eap.penssl_ciphers allocation failed");
        }
        else
        {
            os_memcpy(apSsid->eap.openssl_ciphers,"SUITEB192",strlen("SUITEB192"));
        }
    }

    if(apInputApSsid->eap.eap_method != NULL)
    {
        len = sizeof(struct eap_method_type) * apInputApSsid->eap.num_of_eap_methods;
        apSsid->eap.eap_methods = os_zalloc(len);
        if(apSsid->eap.eap_methods == NULL)
        {
            CME_ENT_PRINT_REPORT_ERROR("\n\r ERROR! pSsid->eap.eap_methods allocation failed");
        }
        else
        {
            os_memcpy(apSsid->eap.eap_methods,apInputApSsid->eap.eap_method,len);
        }
    }
    //apSsid->eap.eap_methods = apInputApSsid->eap.eap_method;//points to const global

    if( apInputApSsid->eap.phase1 != NULL)
    {
        apSsid->eap.phase1 = (char *) os_strdup((const char *)&apInputApSsid->eap.phase1[0]);
        if(apSsid->eap.phase1 == NULL)
        {
            CME_ENT_PRINT_REPORT_ERROR("\n\r ERROR! apSsid->eap.phase1 allocation failed");
        }
    }

    if(apInputApSsid->eap.phase2 != NULL)
    {
        apSsid->eap.phase2 = (char *) os_strdup((const char *)&apInputApSsid->eap.phase2[0]);
        if(apSsid->eap.phase2 == NULL)
        {
            CME_ENT_PRINT_REPORT_ERROR("\n\r ERROR! apSsid->eap.phase2 allocation failed");
        }
    }


    if(apInputApSsid->eap.identity_len == 0)
    {
        apSsid->eap.identity = NULL;
    }
    else
    {
        apSsid->eap.identity = (u8 *) os_strdup((const char *)&apInputApSsid->eap.identity[0]);
        if(apSsid->eap.identity == NULL)
        {
            CME_ENT_PRINT_REPORT_ERROR("\n\r ERROR! apSsid->eap.identity allocation failed");
        }
    }
    apSsid->eap.identity_len = apInputApSsid->eap.identity_len;


    if(apInputApSsid->eap.anonymous_identity_len == 0)
    {
        apSsid->eap.anonymous_identity = NULL;
    }
    else
    {
        apSsid->eap.anonymous_identity = (u8 *) os_strdup((const char *)&apInputApSsid->eap.Anonymous[0]);
        if(apSsid->eap.anonymous_identity == NULL)
        {
            CME_ENT_PRINT_REPORT_ERROR("\n\r ERROR! apSsid->eap.anonymous_identity allocation failed");
        }
    }

    apSsid->eap.anonymous_identity_len = apInputApSsid->eap.anonymous_identity_len;


    if(apInputApSsid->eap.password_len == 0)
    {
        apSsid->eap.password  = NULL;
        apSsid->eap.password_len = 0;
    }
    else
    {
        apSsid->eap.password = (u8 *) os_strdup((const char *)&apInputApSsid->eap.password[0]);
        if(apSsid->eap.password == NULL)
        {
            CME_ENT_PRINT_REPORT_ERROR("\n\r ERROR! apSsid->eap.password allocation failed");
        }
    }
    apSsid->eap.password_len = apInputApSsid->eap.password_len;


    apSsid->psk_set = 0;//mgmt key is not psk


    /* Load certificates into blobs */
    if ((apInputApSsid->eap.ca_cert == NULL) || (apInputApSsid->eap.ca_cert_len == 0))
    {
        CME_ENT_PRINT_REPORT_ERROR("\n\rWARNING !  no ca cert verification");
        apSsid->eap.cert.ca_cert = os_strdup("/dev/null");

    }
    else
    {
        if(add_or_update_blob(wpa_s, "ca_blob", apInputApSsid->eap.ca_cert, apInputApSsid->eap.ca_cert_len) == 0)
        {
            // Root CA certificate (server validation)
            apSsid->eap.cert.ca_cert = os_strdup("blob://ca_blob");
        }
    }
    if(apSsid->eap.cert.ca_cert == NULL)
    {
        CME_ENT_PRINT_REPORT_ERROR("\n\r ERROR! apSsid->eap.cert.ca_cert allocation failed");
    }


    if ((apInputApSsid->eap.client_cert == NULL)||(apInputApSsid->eap.client_cert_len == 0))
    {
        CME_ENT_PRINT_REPORT_ERROR("\n\rNOTICE ! apInputApSsid->eap.client_cert is null");
    }
    else
    {
        if(add_or_update_blob(wpa_s, "client_blob", apInputApSsid->eap.client_cert, apInputApSsid->eap.client_cert_len) == 0)
        {
            // Client-side certificate & key
            apSsid->eap.cert.client_cert = os_strdup("blob://client_blob");
            if(apSsid->eap.cert.client_cert == NULL)
            {
                CME_ENT_PRINT_REPORT_ERROR("\n\r ERROR! apSsid->eap.cert.client_cert allocation failed");
            }

        }
    }


    if((apInputApSsid->eap.private_key == NULL) || (apInputApSsid->eap.private_key_len == 0))
    {
        CME_ENT_PRINT_REPORT_ERROR("\n\rNOTICE ! apInputApSsid->eap.private_key is null");
    }
    else
    {
        if(add_or_update_blob(wpa_s, "key_blob", apInputApSsid->eap.private_key, apInputApSsid->eap.private_key_len) == 0)
        {
            apSsid->eap.cert.private_key = os_strdup("blob://key_blob");
            if(apSsid->eap.cert.private_key == NULL)
            {
                CME_ENT_PRINT_REPORT_ERROR("\n\r ERROR! aapSsid->eap.cert.private_key allocation failed");
            }
        }
    }    


    apSsid->eap.cert.private_key_passwd = NULL;//not supported

    CME_ENT_PRINT_REPORT("\n\rAdding profile to the supplicant ,proto: %d key_mgmt:0x%x group_cipher: 0x%x pairwise_cipher: 0x%x ",
            apSsid->proto,
            apSsid->key_mgmt,
            apSsid->group_cipher,
            apSsid->pairwise_cipher
    );

    CME_ENT_PRINT_REPORT("\n\r fragment_size:%d eapol_flags:%d eap_workaround:%d",
    apSsid->eap.fragment_size,
    apSsid->eapol_flags,
    apSsid->eap_workaround);


    CME_ENT_PRINT_REPORT("\n\r eap_methods[0].method: %d apSsid.eap.eap_methods[0].vendor: %d",
            apSsid->eap.eap_methods[0].method,//EAP_TYPE_TLS
            apSsid->eap.eap_methods[0].vendor
    );

    CME_ENT_PRINT_REPORT("\n\r "
            "eap_methods[1].method: %d apSsid.eap.eap_methods[1].vendor: %d "
            "eap.identity_len: %d eap.identity: %s",
            apSsid->eap.eap_methods[1].method,//EAP_TYPE_NONE
            apSsid->eap.eap_methods[1].vendor,
            apSsid->eap.identity_len,
            apSsid->eap.identity
    );

    CME_ENT_PRINT_REPORT("\n\r "
            "anonymous_identity_len: %d auth_alg: %d",
            apSsid->eap.anonymous_identity_len,
            apSsid->auth_alg
    );

    CME_ENT_PRINT_REPORT("\n\r "
            "eap.phase1:%s eap.phase2:%s ",
            apSsid->eap.phase1,
            apSsid->eap.phase2
    );


    CME_ENT_PRINT_REPORT("\n\r "
            "eap.password_len:%d eap.password: %s\n\r",
            apSsid->eap.password_len,
            apSsid->eap.password
    );

}

/* ----------------------------------------------------------------------------
add_or_update_ca_blob
         helper function to add a blob to wpa_supplicant

Parameters:

Return code:   none
---------------------------------------------------------------------------- */
static int32_t add_or_update_blob(struct wpa_supplicant *wpa_s,
    char *blob_name,
    uint8_t *cert_data, size_t cert_len)
{

    {
        const struct wpa_config_blob* blob;
        blob = wpa_config_get_blob(wpa_s->conf, blob_name);

        if (blob) {
            CME_ENT_PRINT_REPORT("\n\rUpdating existing blob: %s", blob_name);
            wpa_config_remove_blob(wpa_s->conf, blob_name);
        }
    }
    {
        struct wpa_config_blob* blob;
        blob = os_zalloc(sizeof(*blob));
        if (!blob)
        {
            CME_ENT_PRINT_REPORT_ERROR("\n\r ERROR! Failed to allocate BLOB");
            return -1;
        }

        blob->name = os_strdup(blob_name);
        blob->data = os_memdup(cert_data, cert_len+1);//copy also the null termination
        blob->len = cert_len;

        if (!blob->name || !blob->data) {
            wpa_config_free_blob(blob);
            CME_ENT_PRINT_REPORT_ERROR("\n\r ERROR! BLOB name or date is null");
            return -1;
        }
        /* Add to config (supplicant now owns it) */
        wpa_config_set_blob(wpa_s->conf, blob);
    }
    CME_ENT_PRINT_REPORT("\n\rAdded blob: %s (%u bytes)", blob_name, (unsigned)cert_len);
    return 0;

}

/* ----------------------------------------------------------------------------
remove_cert_blob
         helper function to add a blob to wpa_supplicant

Parameters:

Return code:   none
---------------------------------------------------------------------------- */
static void remove_cert_blob(struct wpa_supplicant *wpa_s,
    const char *blob_name)
{
    const struct wpa_config_blob* blob;
    blob = wpa_config_get_blob(wpa_s->conf, blob_name);

    if (blob) {
        CME_PRINT_REPORT("\n\rremoving existing blob: %s", blob_name);
        wpa_config_remove_blob(wpa_s->conf, blob_name);
    }
}

/* ----------------------------------------------------------------------------
duplicateWpaPmksaCache
         helper function to add a pmksa cache to wpa_supplicant

Parameters:

Return code:   none
---------------------------------------------------------------------------- */
void duplicateWpaPmksaCache(cmeProfileInfo_t *pProfile, cmeScanCandidateDesc_t *apCandidate,
                             struct wpa_ssid *pSupplicantSsid)
{
    struct wpa_supplicant *wpa_s;
    struct wpa_sm *wpa = NULL;
    RoleType_e roleType;

    // Get STA role iface
    roleType = drv_getStaIface(gpSupplicantGlobals, &wpa_s);
    ASSERT_GENERAL(roleType != ROLE_TYPE_NONE);

    wpa = wpa_s->wpa;

    if (CME_IS_SEC_TYPE_SAE(pProfile->profile.secType) // WPA3 Connection Type
        && (pProfile->pmkid_params.pmkid_set)) // if pmkid is set
    {
        //if pmkid is set, check if same bssid:
        if (TRUE == IRQ_UtilCompareMacAddress(pProfile->pmkid_params.bssid, apCandidate->mScanResult.bssid))
        {
            CME_PRINT_REPORT("\n\radd profile to supplicant - pmkid is set and Peer mac is same! Copy it\n\r");
            //CME_CON_PRINT("\n\r apCandidate MAC Peer " MACSTR, MAC2STR(apCandidate->mScanResult.bssid));

           // wpa_s->wpa->key_mgmt = WPA_KEY_MGMT_SAE;
            wpa_s->wpa->key_mgmt = pProfile->pmkid_params.key_mgmt;
            wpa->cur_pmksa = pmksa_cache_add(wpa->pmksa, pProfile->pmkid_params.pmk, pProfile->pmkid_params.pmk_len,
                                            pProfile->pmkid_params.pmkid, NULL, 0, pProfile->pmkid_params.bssid,
                                            wpa->own_addr, pSupplicantSsid, wpa_s->wpa->key_mgmt, NULL);
        }
        else
        {
            //peer mac and scan candidate bssid are different, remove pmksa entry
            cmeRemoveWpaPmkCache();
        }

    }
    else if ((pProfile->profile.eap.eap_entProfileIndex != CME_INVALID_ENT_IDX) && //Valid ENT index
            (pProfile->profile.secType == CME_SEC_TYPE_WPA_ENT) &&                 // WPA-ENT
            (gAdHocEapPmkidParams_ull.pmkid_set == TRUE) &&                        // pmkid is set
            (pProfile->profile.key_mgmt & gAdHocEapPmkidParams_ull.key_mgmt))     // key mgmt is same
    {
            //check if same bssid
            if (TRUE == IRQ_UtilCompareMacAddress(gAdHocEapPmkidParams_ull.bssid, apCandidate->mScanResult.bssid))
            {
                uint8_t *kck = NULL;
                size_t kck_len = 0;

                CME_PRINT_REPORT("\n\radd eap profile to supplicant - pmkid is set and bssid is same! Copy it\n\r");
#if 0 // debug logs
                Report("\n\rsaved bssid: %x:%x:%x:%x:%x:%x\n\r",
                    gAdHocEapPmkidParams_ull.bssid[0], gAdHocEapPmkidParams_ull.bssid[1],
                    gAdHocEapPmkidParams_ull.bssid[2], gAdHocEapPmkidParams_ull.bssid[3],
                    gAdHocEapPmkidParams_ull.bssid[4], gAdHocEapPmkidParams_ull.bssid[5]);
                Report("\n\rcandidate bssid: %x:%x:%x:%x:%x:%x\n\r",
                    apCandidate->mScanResult.bssid[0], apCandidate->mScanResult.bssid[1],
                    apCandidate->mScanResult.bssid[2], apCandidate->mScanResult.bssid[3],
                    apCandidate->mScanResult.bssid[4], apCandidate->mScanResult.bssid[5]);
#endif
                wpa_s->wpa->key_mgmt = gAdHocEapPmkidParams_ull.key_mgmt;

#ifdef CME_ENT_SUITE_B_PMK_CACHE_SUPPORT
                if (CME_IS_ENT_KEY_MGMT_SUITE_B_TYPE(pProfile->profile.key_mgmt))
                {
                    // Suite B requires KCK for PMKID derivation
                    if (cme_is_kck_available())
                    {
                        kck = gCmeKck.kck;
                        kck_len = gCmeKck.kck_len;
                        CME_PRINT_REPORT("\n\rSuite B PMK cache: restoring with KCK len=%d", kck_len);

                        wpa->cur_pmksa = pmksa_cache_add(wpa->pmksa,
                                                gAdHocEapPmkidParams_ull.pmk,
                                                gAdHocEapPmkidParams_ull.pmk_len,
                                                gAdHocEapPmkidParams_ull.pmkid,
                                                kck, kck_len,
                                                gAdHocEapPmkidParams_ull.bssid,
                                                wpa->own_addr,
                                                pSupplicantSsid,
                                                wpa_s->wpa->key_mgmt,
                                                NULL);
                        if (wpa->cur_pmksa == NULL)
                        {
                            CME_PRINT_REPORT_ERROR("\n\rSuite B PMK cache add failed!");
                        }
                    }
                    else
                    {
                        // KCK not available - cannot use PMK cache for Suite B
                        CME_PRINT_REPORT("\n\rSuite B PMK cache: KCK not available, full auth required");

                        cmeRemoveWpaPmkCache();
                    }
                }
                else
#endif // CME_ENT_SUITE_B_PMK_CACHE_SUPPORT
                {
                    // Non-Suite B EAP (standard 802.1X)
                    wpa->cur_pmksa = pmksa_cache_add(wpa->pmksa, gAdHocEapPmkidParams_ull.pmk, gAdHocEapPmkidParams_ull.pmk_len,
                                            gAdHocEapPmkidParams_ull.pmkid, kck, kck_len, gAdHocEapPmkidParams_ull.bssid,
                                            wpa->own_addr, pSupplicantSsid, wpa_s->wpa->key_mgmt, NULL);
                }
            }
            else
            {
                //peer mac and scan candidate bssid are different, remove pmksa entry
                cmeRemoveWpaPmkCache();
            }
    }
}

// locateAndFillStandardNetwork - add new profile common method
//                      verify if profile already exist, and if its a new entry fill all relevant fields
//                      to the first avaialable entry
//
int locateAndFillStandardNetwork(int scan_ssid,
                int priority,
                int ssid_len,
                int ssid_is_prefix,
                int8_t *ssid,
                unsigned char* bssid,
                int key_mgmt,
                uint8_t secType,
                u16 key_len_and_id,
                int8_t *wep_keys,
                cmeProfileInfo_t *preferredNetworks)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int currentProfileIndex;
    int selectedProfileIndex = CME_SCAN_MAX_PROFILES;
    cmeProfileInfo_t *pCurrentMatchedProfile;
    int wep_key_len = key_len_and_id & 0xFF;

    //Check if the added new profile is already configured in the preferredNetworks DB.
    //We will check the new profile existence even if the selectedProfileIndex above shows that there is no free index for this new profile.
    //We do that in case the new profile already exists in the DB but either priority or scan_ssid parameters were changed compare to the
    //existing profile, so we could update the existing profile.
    for (currentProfileIndex = 0; currentProfileIndex < CME_SCAN_MAX_PROFILES; currentProfileIndex++)
    {
        pCurrentMatchedProfile = &preferredNetworks[currentProfileIndex];

        if (pCurrentMatchedProfile->uniqueProfileId != CME_INVALID_PROFILE_ID)//Check if profile is active
        {
            //Check if the SSID of the new added profile already exists
            if ((pCurrentMatchedProfile->profile.ssid_len == ssid_len) &&
                            (os_memcmp(pCurrentMatchedProfile->profile.ssid, ssid, ssid_len) == 0))
            {

#ifdef C35XX_PROFILE_CHECK_BSSID_AND_SECURITY_TO_REMOVE //?

#ifdef SL_PROFILE_STRUCT_REDUCTION
                //Check if ssid prefix needed and if so if already exists
                if ( (ssid_is_prefix && (pCurrentMatchedProfile->profile.ssid_prefix_len == ssid_len) &&
                                (os_memcmp(pCurrentMatchedProfile->profile.ssid_prefix, ssid, ssid_len) == 0))
                                ||
                                ((ssid_is_prefix == 0) && (pCurrentMatchedProfile->profile.ssid_prefix_len == 0))
                )
#endif
                {
                    //Check if the BSSID of the new added profile already exists
                    if (os_memcmp(pCurrentMatchedProfile->profile.bssid, bssid, ETH_ALEN) == 0)
                    {
                        //At this point we have a match of SSID & BSSID between the new added profile
                        //and current preferredNetworks[currentProfileIndex] profile.

                        //Check for same security type
                        if (pCurrentMatchedProfile->profile.key_mgmt == key_mgmt)
                        {
                            /*------- New added profile is of security type WPA/WPA2 -------*/
                            if (WPA_KEY_MGMT_PSK == key_mgmt)
                            {
                                //When a new added profile of WPA/WPA2 has the same SSID & BSSID & ssid_prefix_len of current
                                //profile in preferredNetworks[currentProfileIndex], we will re-use the currentProfileIndex
                                //and update the new profile security parameters, although it is possible that all security
                                //parameters are the same (we would like to avoid matching the current preferredNetworks[]
                                //passphrase and new profile passphrase).
                                //The reason we do that is to avoid storing in RAM and FS the passphrase of each WPA profile
                                //(7profiles x 32Bytes) in the expense of re-calculation time of the PSK key and FS store
                                //time, every time a fully the same WPA/WPA2 profile is being added by the user.
                                selectedProfileIndex = currentProfileIndex;//We exit the for loop and continue to update the WPA profile using the existing profile index
                                break;
                            }
                            /*------- New added profile is of security type OPEN/WEP -------*/
                            else if (WPA_KEY_MGMT_NONE == key_mgmt)
                            {
                                /*--- New added profile is of security type WEP ----*/
                                if ((wep_key_len != 0)//wep_key_len should be !=0 only in WEP case!!!!
                                                &&
                                    (pCurrentMatchedProfile->profile.wep_key_len[0] != 0))//Current profile in DB is of type WEP
                                {
                                    //In case of WEP security type, when we a full match of SSID&BSSID,
                                    //we won't check for a match of the WEP security parameters between the new
                                    //profile and current profile, same as done in WPA/WPA2 case.
                                    //In this case we will re-use the index and update the new WEP profile's parameters.
                                    //The reason is that we don't distinguish today in WEP case in the key_id
                                    //and its keys, meaning, once we find the AP's SSID and BSSID and see
                                    //that it is of WEP type, we will try to connect to it regardless the differnt keys
                                    //of the two similar profiles since we don't try to find a match for key and key_id
                                    //in WEP connection.
                                    //In this case, we might have a second profile which is redundant
                                    //and therefore, we decide to override the current profile security parameters
                                    //with the new added one.
                                    selectedProfileIndex = currentProfileIndex;//We exit the for loop and continue to update the WEP profile using the existing profile index
                                    break;
                                }
                                else if (pCurrentMatchedProfile->profile.wep_key_len[0] != wep_key_len)
                                {
                                    //No match in security types between new added profile and
                                    //preferredNetworks[currentProfileIndex].
                                    //Either current profile in DB is OPEN (wep_key_len[0]==0) and new added profile
                                    //is WEP (wep_key_len != 0) or vise versa.
                                    //Thus, we need to move to next profile index in the DB and find another match, if any.
                                    continue;
                                }

                                /*--- Both new added profile AND current profile are of security type OPEN ---*/

                                //At this point we have a full match between SSID & BSSID & Security Type OPEN.
                                //Check if the priority is the same, if not, then change the priority according to the latest one received
                                if ((pCurrentMatchedProfile->profile.priority != priority) ||
                                                (pCurrentMatchedProfile->profile.scan_ssid != scan_ssid))
                                {
                                    GTRACE(GRP_CME, "locateAndFillStandardNetwork: New Profile Already Exists in Index %d. Old Priority=%d/Scan_Ssid=%d , have changed and need to be updated to 0x%x",
                                                    currentProfileIndex,
                                                    pCurrentMatchedProfile->profile.priority,
                                                    pCurrentMatchedProfile->profile.scan_ssid,
                                                    (priority<<16)|scan_ssid);

                                    //New priority and/or scan_ssid parameters value will be updated after exiting the for loop.
                                    //Need to re-build gBestProfile, gSelectedProfile and gProfiles due to the parameter change compared to
                                    //the existing profile.
                                    //This will be done by invoking the wlan_apply_policy_upon_config_change() after returning from locateAndFillStandardNetwork()

                                }

                                //Exactly the same profile already exists in DB - No need to update it!!!! and no need to re-build gBestProfile, gSelectedProfile and gProfiles
                                //by invoking wlan_apply_policy_upon_config_change()
                                GTRACE(GRP_CME, "locateAndFillStandardNetwork: New Profile Already Exists in Index %d. No Change in Profile.",currentProfileIndex);
                                CME_PRINT_REPORT("\n\rlocateAndFillStandardNetwork: New Profile Already Exists in Index %d. No Change in Profile.",currentProfileIndex);
                                selectedProfileIndex = currentProfileIndex;//We exit the for loop and continue to update the OPEN profile using the existing profile index
                                break;
                            }
                            else if (WPA_KEY_MGMT_IEEE8021X == key_mgmt)
                            {
                                //When a new enterprise profile added which has the same SSID & BSSID of current
                                //profile in preferredNetworks[currentProfileIndex], we will re-use the currentProfileIndex
                                //and update the new profile security parameters.
                                selectedProfileIndex = currentProfileIndex;//We exit the for loop and continue to update the WPA profile using the existing profile index
                                break;
                            }
                            else if (((WPA_KEY_MGMT_PSK | WPA_KEY_MGMT_PSK_SHA256) == key_mgmt)
                                    || (WPA_KEY_MGMT_SAE == key_mgmt)
                                    || ((WPA_KEY_MGMT_PSK | WPA_KEY_MGMT_PSK_SHA256 | WPA_KEY_MGMT_SAE) == key_mgmt))

                            {
                                selectedProfileIndex = currentProfileIndex;
                                break;
                            }
                            
                            else//Illegal
                            {
                                GTRACE(GRP_CME, "ERROR: locateAndFillStandardNetwork: Illegal key_mgmt value - %d  Configured by User", key_mgmt);
                                CME_PRINT_REPORT("\n\rlocateAndFillStandardNetwork: Illegal key_mgmt value - %d  Configured by User", key_mgmt);
                            }
                        }
                    }
                }
#endif //C35XX_PROFILE_CHECK_BSSID_AND_SECURITY_TO_REMOVE
                //ssid exist
                selectedProfileIndex = currentProfileIndex;
                break;
            }
        }
        //currentProfileIndex is free and can be used
        else if (CME_SCAN_MAX_PROFILES == selectedProfileIndex)
        {
            //Store in selectedProfileIndex only the first free index found
            selectedProfileIndex = currentProfileIndex;
            break;
        }
    }//for()

    //No free space in DB - Do nothing
    if (selectedProfileIndex == CME_SCAN_MAX_PROFILES)
    {
        GTRACE(GRP_CME, "ERROR: locateAndFillStandardNetwork: Add New Profile Failed - No Free Index Available");
        return CME_SCAN_MAX_PROFILES;
    }

    // Fill shared params
    os_memset(&preferredNetworks[selectedProfileIndex], 0, sizeof(cmeProfileInfo_t));
    preferredNetworks[selectedProfileIndex].profile.id = CME_INVALID_PROFILE_ID;
    preferredNetworks[selectedProfileIndex].uniqueProfileId = selectedProfileIndex;//getUniqueProfileId();
    preferredNetworks[selectedProfileIndex].profile.eap.eap_entProfileIndex = CME_INVALID_ENT_IDX;
    preferredNetworks[selectedProfileIndex].profile.disabled = 0;
    preferredNetworks[selectedProfileIndex].profile.priority = priority;
    preferredNetworks[selectedProfileIndex].profile.mode = WPAS_MODE_INFRA;
    preferredNetworks[selectedProfileIndex].profile.ssid_len = ssid_len;
    //preferredNetworks[selectedProfileIndex].profile.ssid = preferredNetworks[selectedProfileIndex].ssid;


    // This is the time to allocate memory for profile SSID, can't be done earlier
    // since SSID lengthis unknown (and we don't want to reserve SSID_MAX_LEN

    os_memcpy(preferredNetworks[selectedProfileIndex].profile.ssid, ssid, ssid_len);

    GTRACE(GRP_CME, "Added a new profile to DB, index %d unique ID %d, priority %d, SSID %s",
                     selectedProfileIndex,
                     preferredNetworks[selectedProfileIndex].uniqueProfileId,
                     preferredNetworks[selectedProfileIndex].profile.priority,
                     preferredNetworks[selectedProfileIndex].profile.ssid);

    //zero blacklist for this network
    gPreferredNetworksConnAttemptCnt_ull[selectedProfileIndex] = 0;
#ifdef SL_PROFILE_STRUCT_REDUCTION
    // Set up prefix
    if (ssid_is_prefix)
    {
        preferredNetworks[selectedProfileIndex].ssid_prefix_len = ssid_len;
        memcpy(preferredNetworks[selectedProfileIndex].ssid_prefix, ssid, ssid_len);
    } else
    {
        preferredNetworks[selectedProfileIndex].ssid_prefix_len = 0;
    }
#endif

    preferredNetworks[selectedProfileIndex].profile.scan_ssid = scan_ssid;
    if ( bssid && (FALSE == IRQ_UtilIsZeroMacAddress(bssid)) )
    {
        IRQ_UtilCopyMacAddress(bssid, preferredNetworks[selectedProfileIndex].profile.bssid);
        preferredNetworks[selectedProfileIndex].profile.bssid_set = 1;
    }

    preferredNetworks[selectedProfileIndex].profile.key_mgmt = key_mgmt;
    preferredNetworks[selectedProfileIndex].profile.secType = secType;
    preferredNetworks[selectedProfileIndex].p2pProfile = P2P_NONE;

    CME_PRINT_REPORT("\n\rAdded a new profile to DB, index %d unique ID %d, priority %d, SSID %s auth_alg %d secType %d key_mgmt %d",
                     selectedProfileIndex,
                     preferredNetworks[selectedProfileIndex].uniqueProfileId,
                     preferredNetworks[selectedProfileIndex].profile.priority,
                     (char*)preferredNetworks[selectedProfileIndex].profile.ssid, 
                     preferredNetworks[selectedProfileIndex].profile.auth_alg,
                     preferredNetworks[selectedProfileIndex].profile.secType,
                     preferredNetworks[selectedProfileIndex].profile.key_mgmt);

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return selectedProfileIndex;
}

int locateAndFillStandardNetworkNew(_cme_minimized_wpa_ssid_t *apSsid,
                                    cmeProfileInfo_t *preferredNetworks)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int currentProfileIndex;
    int selectedProfileIndex = CME_SCAN_MAX_PROFILES;
    cmeProfileInfo_t *pCurrentMatchedProfile;

    //Check if the added new profile is already configured in the preferredNetworks DB.
    //We will check the new profile existence even if the selectedProfileIndex above shows that there is no free index for this new profile.
    //We do that in case the new profile already exists in the DB but either priority or scan_ssid parameters were changed compare to the
    //existing profile, so we could update the existing profile.
    for (currentProfileIndex = 0; currentProfileIndex < CME_SCAN_MAX_PROFILES; currentProfileIndex++)
    {
        pCurrentMatchedProfile = &preferredNetworks[currentProfileIndex];

        if (pCurrentMatchedProfile->uniqueProfileId != CME_INVALID_PROFILE_ID)//Check if profile is active
        {
            //Check if the SSID of the new added profile already exists
            if ((pCurrentMatchedProfile->profile.ssid_len == apSsid->ssid_len) &&
                (os_memcmp(pCurrentMatchedProfile->profile.ssid, apSsid->ssid, apSsid->ssid_len) == 0))
            {
                //ssid exist
                selectedProfileIndex = currentProfileIndex;
                break;
            }
        }
        //currentProfileIndex is free and can be used
        else if (CME_SCAN_MAX_PROFILES == selectedProfileIndex)
        {
            //Store in selectedProfileIndex only the first free index found
            selectedProfileIndex = currentProfileIndex;
            break;
        }
    }//for()

    //No free space in DB - Do nothing
    if (selectedProfileIndex == CME_SCAN_MAX_PROFILES)
    {
        GTRACE(GRP_CME, "ERROR: locateAndFillStandardNetwork: Add New Profile Failed - No Free Index Available");
        return CME_SCAN_MAX_PROFILES;
    }

    // Fill shared params
    os_memset(&preferredNetworks[selectedProfileIndex], 0, sizeof(cmeProfileInfo_t));

    /* Copy the apSsid into preferredNetworks */
    os_memcpy(&preferredNetworks[selectedProfileIndex].profile, apSsid, sizeof(_cme_minimized_wpa_ssid_t));

    preferredNetworks[selectedProfileIndex].profile.id = CME_INVALID_PROFILE_ID;
    preferredNetworks[selectedProfileIndex].uniqueProfileId = selectedProfileIndex;//getUniqueProfileId();
    preferredNetworks[selectedProfileIndex].profile.eap.eap_entProfileIndex = CME_INVALID_ENT_IDX;
    preferredNetworks[selectedProfileIndex].profile.disabled = 0;
    preferredNetworks[selectedProfileIndex].profile.priority = apSsid->priority;
    preferredNetworks[selectedProfileIndex].profile.mode = WPAS_MODE_INFRA;
    preferredNetworks[selectedProfileIndex].profile.ssid_len = apSsid->ssid_len;

    // This is the time to allocate memory for profile SSID, can't be done earlier
    // since SSID lengthis unknown (and we don't want to reserve SSID_MAX_LEN

    os_memcpy(preferredNetworks[selectedProfileIndex].profile.ssid, apSsid->ssid, apSsid->ssid_len);

    GTRACE(GRP_CME, "Added a new profile to DB, index %d unique ID %d, priority %d, SSID %s",
                     selectedProfileIndex,
                     preferredNetworks[selectedProfileIndex].uniqueProfileId,
                     preferredNetworks[selectedProfileIndex].profile.priority,
                     preferredNetworks[selectedProfileIndex].profile.ssid);

    //zero blacklist for this network
    gPreferredNetworksConnAttemptCnt_ull[selectedProfileIndex] = 0;
#ifdef SL_PROFILE_STRUCT_REDUCTION
    // Set up prefix
    if (ssid_is_prefix)
    {
        preferredNetworks[selectedProfileIndex].ssid_prefix_len = ssid_len;
        memcpy(preferredNetworks[selectedProfileIndex].ssid_prefix, ssid, ssid_len);
    } else
    {
        preferredNetworks[selectedProfileIndex].ssid_prefix_len = 0;
    }
#endif

    preferredNetworks[selectedProfileIndex].profile.scan_ssid = apSsid->scan_ssid;
    if (FALSE == IRQ_UtilIsZeroMacAddress(apSsid->bssid)) 
    {
        IRQ_UtilCopyMacAddress(apSsid->bssid, preferredNetworks[selectedProfileIndex].profile.bssid);
        preferredNetworks[selectedProfileIndex].profile.bssid_set = 1;
    }

    preferredNetworks[selectedProfileIndex].profile.key_mgmt = apSsid->key_mgmt;
    preferredNetworks[selectedProfileIndex].profile.secType = apSsid->secType;
    preferredNetworks[selectedProfileIndex].p2pProfile = P2P_NONE;

    preferredNetworks[selectedProfileIndex].pmkid_params.pmkid_set = 0;

    CME_PRINT_REPORT("\n\rAdded a new profile to DB, index %d unique ID %d, priority %d," 
                     "SSID %s auth_alg %d secType %d key_mgmt %d scan_ssid %d",
                     selectedProfileIndex,
                     preferredNetworks[selectedProfileIndex].uniqueProfileId,
                     preferredNetworks[selectedProfileIndex].profile.priority,
                     (char*)preferredNetworks[selectedProfileIndex].profile.ssid, 
                     preferredNetworks[selectedProfileIndex].profile.auth_alg,
                     preferredNetworks[selectedProfileIndex].profile.secType,
                     preferredNetworks[selectedProfileIndex].profile.key_mgmt,
                     preferredNetworks[selectedProfileIndex].profile.scan_ssid);

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return selectedProfileIndex;
}

#if 0 // No P2P MCU Attached supproted
unsigned int wlan_generate_p2p_pin_code_from_mac()
{
    unsigned int val;
    uint8_t *mac;
    uint8_t role_id;

    role_id = Roles_GetRoleIdFromRoleType(ROLE_DEVICE);

    mac = Roles_GetLocalMacFromRoleId(role_id);

    val = mac[3]*1000000 +
          mac[4]*1000 +
          mac[5];

    val %= 10000000;
    /* Append checksum digit */
    return val * 10 + wps_pin_checksum(val);
}
#endif

void wlan_calculate_pmk(int ssid_len,
                int8_t *ssid,
                int8_t *passphrase,
                unsigned int passphrase_length,
                u8   *pmk)
{   // Called from supplicant

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    char passphraseBuff[WPA_MAX_PASSPHRASE_LEN + 1];

    if (passphrase_length > WPA_MAX_PASSPHRASE_LEN)
    {
        // passphrase too long
        ASSERT_GENERAL(0);
    }

// TODO need to implement #ifdef PMK_SW_CONFIG_PATCH
#if 0
    uint32_t  pmk_duration;
    pmk_on_ull = TRUE;
    pmk_duration = TimersMng_GetFreeRunningLowTsf();
#endif
    // We copy the passphrase locally and ensure that it is null terminated.
    os_memcpy(passphraseBuff, passphrase, passphrase_length);
    passphraseBuff[passphrase_length] = 0;
    pbkdf2_sha1(passphraseBuff, (const u8*)ssid, ssid_len, 4096, pmk, PMK_LEN);

// TODO need to implement #ifdef PMK_SW_CONFIG_PATCH
#if 0
    GTRACE(GRP_CME_DEBUG, "pmk duration %d usec", TimersMng_GetFreeRunningLowTsf() - pmk_duration);
    pmk_on_ull = FALSE;
#endif
}


int add_preferred_network_wpa(int scan_ssid,
                int priority,
                int ssid_len,
                int ssid_is_prefix,
                int isPassphraseIsPMK,
                int passphrase_length,
                int pairwise_cipher,
                int group_cipher,
                int key_mgmt,
                int protocol,
                int8_t *ssid,
                unsigned char* bssid,
                int8_t *passphrase,
                cmeProfileInfo_t *preferredNetworks)
{

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int index;
    int16_t flashStatus;


    //S 16/7/2013 - WPS profile for P2P doesn't need to be stored since its a one-time ssid+credintials
    //                    obviously handle differently for connection to persistant GO (stored in fast connect SSID)

    if(cme_is_p2p_role_configured() )
    {
        GTRACE(GRP_CME, "WPS add_preferred_network_wpa: P2P do not store credentials in flash ssid name %s", ssid);
        return 0;
    }

    index = locateAndFillStandardNetwork(scan_ssid, priority, ssid_len, ssid_is_prefix, ssid, bssid, key_mgmt, CME_SEC_TYPE_WPA_WPA2, 0, NULL, preferredNetworks);
    if (index == CME_SCAN_MAX_PROFILES)
    {
        // TODO need return code
        //sl_error_handler_report(SL_DEVICE_SOURCE_WLAN,SL_ERROR_WLAN_PREFERRED_NETWORK_LIST_FULL);
        return -1;
    }

    preferredNetworks[index].profile.pairwise_cipher = pairwise_cipher;
    preferredNetworks[index].profile.group_cipher = group_cipher;
    preferredNetworks[index].profile.proto = protocol;
    preferredNetworks[index].profile.auth_alg = WPA_AUTH_ALG_OPEN;

    if(WPA_HEX_PASSPHRASE_LENGTH == passphrase_length)
    {// string contains Hex password, convert it to Hex format
        convertAsciiString2Hex((int8_t *)passphrase, (int8_t *)passphrase, passphrase_length);
        passphrase_length = PMK_LEN;
        isPassphraseIsPMK = TRUE;
    }

    if (isPassphraseIsPMK)
    {
        if (passphrase_length != PMK_LEN)
        {
            // Error!
            return -1;
        }
        os_memcpy(preferredNetworks[index].profile.psk, passphrase, PMK_LEN);
    } else
    {
        // TODO: CC3XXX-2955, wlan_calculate_pmk causes stack to grow to 1100. Change back to 1024 when transferred to Security Subsystem
        wlan_calculate_pmk(ssid_len, ssid, passphrase, passphrase_length, preferredNetworks[index].profile.psk);
    }
    preferredNetworks[index].profile.psk_set = 1;

    flashStatus =  SetPreferredNetworks_SetToFlashFromPointer(preferredNetworks, TRUE);

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    if (flashStatus == 0)
    {
        return index;
    }

    //else - something went wrong with the flash
    return -1;

}


int add_preferred_network_wep(int scan_ssid,
                int priority,
                int ssid_len,
                int ssid_is_prefix,
                int auth_alg,
                int tx_key_id,
                int key_len,
                int8_t *ssid,
                unsigned char* bssid,
                int8_t *keys,
                cmeProfileInfo_t *preferredNetworks)
{

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int i;
    int index;
    int16_t flashStatus;
    u8 secType;

    if ((key_len == WEP40_HEX_KEY_LENGTH) || (key_len == WEP104_HEX_KEY_LENGTH))
    {// string contains Hex password, convert it to Hex format
        convertAsciiString2Hex((int8_t *)keys, (int8_t *)keys, key_len);
        key_len = key_len/2;
    }

    if (tx_key_id >= NUM_WEP_KEYS)
    {
        GTRACE(GRP_CME,"ERROR: add_preferred_network_wep: Illegal WEP Key Index %d Configured by User", tx_key_id);
    }

    if (auth_alg == WPA_AUTH_ALG_SHARED)
    {
        secType = CME_SEC_TYPE_WEP_SHARED;
    }
    else
    {
        secType = CME_SEC_TYPE_WEP;
    }


    index = locateAndFillStandardNetwork(scan_ssid, priority, ssid_len, ssid_is_prefix, ssid, bssid, WPA_KEY_MGMT_NONE, secType, (key_len&0xFF)|(tx_key_id<<8), keys, preferredNetworks);
    if (index == CME_SCAN_MAX_PROFILES)
    {
        // TODO need return code
       // sl_error_handler_report(SL_DEVICE_SOURCE_WLAN,SL_ERROR_WLAN_PREFERRED_NETWORK_LIST_FULL);
        return -1;
    }


    preferredNetworks[index].profile.wep_tx_keyidx = tx_key_id;
    preferredNetworks[index].profile.auth_alg = auth_alg;


    for (i = 0; i < NUM_WEP_KEYS; i++)
    {
        os_memcpy(preferredNetworks[index].profile.wep_key[i], keys, key_len);
        preferredNetworks[index].profile.wep_key_len[i] = key_len;
    }


    flashStatus =  SetPreferredNetworks_SetToFlashFromPointer(preferredNetworks, TRUE);

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    if (flashStatus == 0)
    {
        return index;
    }

    //else - something went wrong with the flash
    return -1;

}



//
// add_preferred_network_open
//
//          add preferred network of type security open
//

int add_preferred_network_open(int scan_ssid,
                int priority,
                int ssid_len,
                int ssid_is_prefix,
                int8_t *ssid,
                unsigned char* bssid,
                cmeProfileInfo_t *preferredNetworks)
{

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int index;
    int16_t flashStatus;

    index = locateAndFillStandardNetwork(scan_ssid, priority, ssid_len, ssid_is_prefix, ssid, bssid, WPA_KEY_MGMT_NONE, CME_SEC_TYPE_OPEN, 0, NULL, preferredNetworks);
    if (index == CME_SCAN_MAX_PROFILES)
    {
        // TODO need return code
       // sl_error_handler_report(SL_DEVICE_SOURCE_WLAN,SL_ERROR_WLAN_PREFERRED_NETWORK_LIST_FULL);
        return -1;
    }


    flashStatus =  SetPreferredNetworks_SetToFlashFromPointer(preferredNetworks, TRUE);

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    if (flashStatus == 0)
    {
        return index;
    }
    //else - something went wrong with the flash
    return -1;

}


int32_t add_preferred_network_common(CMEWlanAddGetProfile_t   *apProfileCmd,
                                      cmeProfileInfo_t *preferredNetworks)
{

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    _cme_minimized_wpa_ssid_t      *apSsid = NULL;
    int i;
    int index;
    int16_t flashStatus;
    int32_t status;
    int8_t *passphrase = NULL;//PROFILE_PASSWORD_STRING(apProfileCmd);
    int ssid_is_prefix = 0;
    int passphrase_length = apProfileCmd->PasswordLen;
    int isPassphraseIsPMK = 0;

    apSsid = (_cme_minimized_wpa_ssid_t *)os_zalloc(sizeof(_cme_minimized_wpa_ssid_t));
    if (apSsid == NULL)
    {
        CME_PRINT_REPORT_ERROR("\n\r[ERROR] add_preferred_network_common: apSsid allocation failed");
        return -1;
    }

    /* --- prepare apSsid buffer --- */

    /* Copy SSID */
    os_memcpy(apSsid->ssid, PROFILE_SSID_STRING(apProfileCmd), apProfileCmd->SsidLen);
    apSsid->ssid_len = apProfileCmd->SsidLen;
    //apSsid->ssid_is_prefix = ssid_is_prefix;

    /* Copy common params */
    apSsid->priority = apProfileCmd->Priority;
    apSsid->scan_ssid = apProfileCmd->Hidden; //CME_ALL_PROFILES_ARE_HIDDEN;

    /* Copy security Params */
    apSsid->secType = apProfileCmd->SecType;

    if (apProfileCmd->SecType != CME_SEC_TYPE_OPEN)
    {
        passphrase = PROFILE_PASSWORD_STRING(apProfileCmd);

        if (setSecurityParams(apProfileCmd, apSsid, passphrase) < 0)
        {
            CME_PRINT_REPORT_ERROR("\n\rERROR: add_preferred_network_common: setSecurityParams failed");
            //Need to free apSsid cmd buffer and if passphrase is not NULL free it too
            if (apSsid->passphrase != NULL)
            {   
                os_free(apSsid->passphrase); 
            }

            os_free(apSsid);   
            return -1;
        }

    }
    else
    {
        apSsid->auth_alg = WPA_AUTH_ALG_OPEN;
        apSsid->key_mgmt = WPA_KEY_MGMT_NONE;
    }
    
    /* Copy BSSID */
    if (FALSE == IRQ_UtilIsZeroMacAddress((const uint8_t *)apProfileCmd->Bssid))
	{
		IRQ_UtilCopyMacAddress(apProfileCmd->Bssid, apSsid->bssid);
		apSsid->bssid_set = 1;
	}
	else
	{
	    IRQ_UtilZeroMacAddress(apSsid->bssid);
	    apSsid->bssid_set = 0;
	}

    /* Check if duplicated and fill preferredNetworks DB */
    index = locateAndFillStandardNetworkNew(apSsid, preferredNetworks);

    if (index == CME_SCAN_MAX_PROFILES)
    {
        // TODO need return code
        // sl_error_handler_report(SL_DEVICE_SOURCE_WLAN,SL_ERROR_WLAN_PREFERRED_NETWORK_LIST_FULL);
        os_free(apSsid);
        CME_PRINT_REPORT_ERROR("\n\radd_preferred_network_common: locateAndFillStandardNetwork failed");
        return -1;
    }

    if (apProfileCmd->SecType != CME_SEC_TYPE_OPEN)
    {

        CME_PRINT_REPORT("\n\rCopy preferredNetworks index %d ssid %s: pssid %s len=%d, pairwise_cipher=%d, group_cipher=%d, proto=%d auth=%d key_mgmt=%d sectype=%d\n\r",
             index, (char*)apSsid->ssid,
              (char*)preferredNetworks[index].profile.ssid, preferredNetworks[index].profile.ssid_len,
             preferredNetworks[index].profile.pairwise_cipher, preferredNetworks[index].profile.group_cipher,
             preferredNetworks[index].profile.proto, preferredNetworks[index].profile.auth_alg,
            preferredNetworks[index].profile.key_mgmt, preferredNetworks[index].profile.secType);
        
    }

    if ((passphrase != NULL) &&
        (CME_IS_SEC_TYPE_SAE(apProfileCmd->SecType)))
    {
        os_memset(preferredNetworks[index].profile.wep_key, 0, passphrase_length+1);
        os_memcpy(preferredNetworks[index].profile.wep_key, passphrase, passphrase_length);
    }

    flashStatus =  SetPreferredNetworks_SetToFlashFromPointer(preferredNetworks, TRUE);

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    if (flashStatus == 0)
    {
        os_free(apSsid);
        return index;
    }
    os_free(apSsid);
    //else - something went wrong with the flash
    CME_PRINT_REPORT_ERROR("\n\radd_preferred_network_common: something went wrong with the flash?");
    return -1;

}


//
// add_preferred_network_p2p
//
//          add preferred network of type P2P
//
#if CC35XX_SUPPORT_P2P_PROFILE // No P2P MCU Attached supproted
int add_preferred_network_p2p(p2pProfile_e sectype,//1-P2P_PBC or 2-P2P_PIN_KEPAD, 3-- P2P_PIN_DISPLAY
                              int priority,
                              int ssid_len,
                              int8_t *ssid,
                              unsigned char* bssid,
                              int8_t *pin_code,
                              cmeProfileInfo_t *preferredNetworks)
{   // Called from CLI
    char pin_c[10];
    unsigned int pin = 0;

    int index;
    int16_t flashStatus;

    index = locateAndFillStandardNetwork(0, priority, ssid_len, 0, ssid, bssid, WPA_KEY_MGMT_NONE, P2P_WPS_TO_SL_PROTOCOL_TYPE(sectype), 0, NULL, preferredNetworks);
    if (index == CME_SCAN_MAX_PROFILES)
    {
        //need return code
        return -1;
    }

    //Mark P2P Profile
    preferredNetworks[index].p2pProfile = sectype;//1-P2P_PBC or 2-P2P_PIN or 3-P2P_PIN_DISPLAY

    if (sectype==P2P_PIN_CODE_KEYPAD || sectype==P2P_PIN_CODE_DISPLAY)//if PIN-Code only
    {
         if (0 != pin_code) //Pin supplied
         {
                os_memcpy(preferredNetworks[index].p2p_pin, pin_code, WPS_PIN_LEN);
         }
         else //No pin supplied. Use default pin
         {


                 pin = wlan_generate_p2p_pin_code_from_mac();

                 sprintf(pin_c, "%d", pin);

                //pin = atoi(defaultPinBuff);
                //SOC_TRACE1(WLINK_MSG, MSG_2621, "WPS PIN=%d", pin);
                os_memcpy(preferredNetworks[index].p2p_pin, pin_c, WPS_PIN_LEN);
         }
         }
    else
    {
        memset(preferredNetworks[index].p2p_pin, 0, WPS_PIN_LEN);
    }


    flashStatus =  SetPreferredNetworks_SetToFlashFromPointer(preferredNetworks, TRUE);

    if (flashStatus == 0)
    {
        return index;
    }


    //else - something went wrong in flash
    return -1;

}
#endif


//
//preferred networks command API's
//

// ADD NETWORK
/*
    The cmeAddPreferredNetwork function adds a network to the preferred network list. 
    It handles both legacy and Enterprise (ENT) profiles, 
    and supports various security types such as WEP, WPA, and WPA2.

    Parameters: pProfile - A pointer to a CMEWlanAddGetProfile_t structure containing
                             the legacy profile parameters.
                index_profile_ptr - A pointer to an index of the added profile.
                pEapProfile - A pointer to an ENT profile structure.
                index_eap_profile_ptr - A pointer to an index of the added ENT profile.
    
    Return: Positive value indicating index og the added profile, negative on failure

    Context: WLAN_IF thread
*/
int16_t cmeAddPreferredNetwork(
                             //legacy profile parameters
                             CMEWlanAddGetProfile_t *pProfile,
                             int16_t *index_profile_ptr,
                             //ent profile parameters
                             void *pEapProfile,
                             int16_t *index_eap_profile_ptr)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int16_t status =  -1;
    uint8_t auth_alg;
    CMEWlanAddGetProfile_t *cme_wlan_add_profile_args = pProfile;//(sl_wlan_add_profile_cmd_t *)&pScmd->func_args_start;

    //read preferred network from FS
    cmeProfileInfo_t *preferredNetworks;
    preferredNetworks = os_malloc(sizeof(cmeProfileInfo_t) * CME_SCAN_MAX_PROFILES);
    LoadPreferredNetworks_GetFromFlashToPointer(preferredNetworks, TRUE);

#if CC35XX_SUPPORT_ENT_PROFILE
    if (pEapProfile!=NULL)
    {
        //
        //ENT profile configuration - allocate and fill ENT security parameters
        //
        status = SL_STATUS_OK;
        int index = locateAndFillStandardNetwork(1/*scanSsid*/, pEapProfile->Common.Priority, pEapProfile->Common.SsidLen,
                                                 0/*no prefix*/,EAP_PROFILE_SSID_STRING(pEapProfile) , pEapProfile->Common.Bssid,
                                                 WPA_KEY_MGMT_IEEE8021X, CME_SEC_TYPE_WPA_ENT, 0, NULL, preferredNetworks);
        if (index == CME_SCAN_MAX_PROFILES)
        {
            sl_error_handler_report(SL_DEVICE_SOURCE_WLAN,SL_ERROR_WLAN_PREFERRED_NETWORK_LIST_FULL);
            status =  SL_ERROR_STATUS_ERROR;

            //update allocated profile index
            *index_eap_profile_ptr = status;
        }
        else
        {
            addProfileEap2DB(
                    (unsigned char *)EAP_PROFILE_ANON_USER_STRING(pEapProfile),
                    pEapProfile->AnonUserLen,
                    (unsigned char *)EAP_PROFILE_USER_STRING(pEapProfile),
                    pEapProfile->UserLen,
                    (unsigned char *)EAP_PROFILE_PASSWORD_STRING(pEapProfile),
                    pEapProfile->Common.PasswordLen,
                    pEapProfile->eap_method,
                    pEapProfile->CertIndex,
                    &preferredNetworks[index]);


            status =  SetPreferredNetworks_SetToFlashFromPointer(preferredNetworks, TRUE);

            if (status == 0)
            {
                status = index;
                *index_eap_profile_ptr = index;
            }
            else
            {
                *index_eap_profile_ptr = -1;
            }

        }
    }
    else
#endif //CC35XX_SUPPORT_ENT_PROFILE
    {
        //
        //Legacy profile configuration - allocate and fill security parameters accordingly
        //
#if 0 // moving to common code for all security types
        switch (cme_wlan_add_profile_args->SecType)
        {
#if CC35XX_SUPPORT_P2P_PROFILE
            case SL_SEC_TYPE_P2P_PBC: // P2P_PBC
            case SL_SEC_TYPE_P2P_PIN_DISPLAY: // P2P_PIN
            case SL_SEC_TYPE_P2P_PIN_KEYPAD: // P2P_PIN
                    status = add_preferred_network_p2p(P2P_SL_PROTOCOL_TYPE_TO_WPS(sl_wlan_add_profile_args->SecType),// == SL_SEC_TYPE_P2P_PBC ? P2P_PUSH_BUTTON : P2P_PIN_CODE_KEYPAD),
                                                    sl_wlan_add_profile_args->Priority,
                                                    sl_wlan_add_profile_args->SsidLen,//Remote Device Name Length
                                                    PROFILE_SSID_STRING(sl_wlan_add_profile_args), // Remote Device Name
                                                    sl_wlan_add_profile_args->Bssid,//Remote Device MAC address
                                                    PROFILE_PASSWORD_STRING(sl_wlan_add_profile_args),//pin-code
                                                    preferredNetworks);// not working directly on GLX global from dispatcher


                break;
#endif // CC35XX_SUPPORT_P2P_PROFILE
            case CME_SEC_TYPE_OPEN: // Open
                status = add_preferred_network_open(1, // scan_ssid
                                                    cme_wlan_add_profile_args->Priority,
                                                    cme_wlan_add_profile_args->SsidLen,
                                                    0, // ssid_is_prefix
                                                    PROFILE_SSID_STRING(cme_wlan_add_profile_args), // here ssid
                                                    cme_wlan_add_profile_args->Bssid,
                                                    preferredNetworks);// not working directly on GLX global from dispatcher
                break;
            case CME_SEC_TYPE_WEP: // WEP
            case CME_SEC_TYPE_WEP_SHARED:
                {
                    if (cme_wlan_add_profile_args->SecType == CME_SEC_TYPE_WEP_SHARED)
                    {
                        auth_alg = WPA_AUTH_ALG_SHARED;
                    }
                    else
                    {
                        auth_alg = WPA_AUTH_ALG_OPEN;
                    }

                    status = add_preferred_network_wep(1, // scan_ssid
                                                        cme_wlan_add_profile_args->Priority,
                                                        cme_wlan_add_profile_args->SsidLen,
                                                        0, // ssid_is_prefix
                                                        auth_alg,
                                                        cme_wlan_add_profile_args->WepKeyId,
                                                        cme_wlan_add_profile_args->PasswordLen,
                                                        PROFILE_SSID_STRING(cme_wlan_add_profile_args), // ssid
                                                        cme_wlan_add_profile_args->Bssid,
                                                        PROFILE_PASSWORD_STRING(cme_wlan_add_profile_args), // keys
                                                        preferredNetworks); // not working directly on GLX global from dispatcher


                    break;
                } //case 1: // WEP
            case CME_SEC_TYPE_WPA_WPA2: // WPA2
                {

                    status = add_preferred_network_wpa( 1, // scan_ssid
                                                        cme_wlan_add_profile_args->Priority,
                                                        cme_wlan_add_profile_args->SsidLen,
                                                        0, //ssid_is_prefix,
                                                        0, //isPassphraseIsPMK,
                                                        cme_wlan_add_profile_args->PasswordLen,
                                                        CME_STA_WPA_DEFAULT_CIPHER, // pArgs->sec_params.Wpa.pairwise_cipher,
                                                        CME_STA_WPA_DEFAULT_CIPHER, // pArgs->sec_params.Wpa.group_cipher,
                                                        WPA_KEY_MGMT_PSK,      // pArgs->sec_params.Wpa.key_mgmt,
                                                        DEFAULT_PROTO,         // protocol
                                                        PROFILE_SSID_STRING(cme_wlan_add_profile_args), // ssid
                                                        cme_wlan_add_profile_args->Bssid,
                                                        PROFILE_PASSWORD_STRING(cme_wlan_add_profile_args), // passphrase
                                                        preferredNetworks); // not working directly on GLX global from dispatcher

                    break;
                } //  case 3: // WPA2
            case CME_SEC_TYPE_WPA2_PLUS: 
                    //TBD
                break;
            default:
                // TODO need return code
                status = -1;
                break;
        } // switch (pArgs->sec_type)
#else // 
        status = add_preferred_network_common(cme_wlan_add_profile_args, preferredNetworks);
#endif
        //update index (or error) for command return code
        *index_profile_ptr = status;
    }


    if ( status >= 0) //meaning successful profile index allocation
    {
        // We need to count free entries in preferredNetworks not in GLX.
        uint8_t freeEntriesNum = CME_SCAN_MAX_PROFILES - getPreferredNetworksDbInfo(preferredNetworks, 0);

        GTRACE(GRP_CME, "add_preferred_network: Add profile succeeded, index = %d, free entries number = %d",
                        status, freeEntriesNum);
        CME_PRINT_PROFILE_REPORT("\n\radd_preferred_network: Add profile succeeded, index = %d, free entries number = %d",
                        status, freeEntriesNum);
    }
    else
    {
        GTRACE(GRP_CME,"ERROR! add_preferred_network got status = 0x%x",status);
        CME_PRINT_REPORT_ERROR("\r\nadd_preferred_network: Add profile failed, status = 0x%x",status);
    }

    if (preferredNetworks->profile.passphrase != NULL)
    {
        //
        //since we might have allocated passphrase in setSecurityParams()
        //let's free passphrase here
        // 
        os_free(preferredNetworks->profile.passphrase);
    }
    os_free(preferredNetworks);

    return status;

}

//
//preferred networks command API's
//

// DELETE NETWORK
int16_t cmeDeletePreferredNetwork(int index)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    int16_t status = 0;
    uint8_t freeEntriesNum;

    //read preferred network from FS
    cmeProfileInfo_t *preferredNetworks;
    preferredNetworks = os_malloc(sizeof(cmeProfileInfo_t) * CME_SCAN_MAX_PROFILES);
    LoadPreferredNetworks_GetFromFlashToPointer(preferredNetworks, TRUE);

    if (WLAN_DEL_ALL_PROFILES == index)
    {
        //delete all profiles request
        int i;
#if CC35XX_SUPPORT_ENT_PROFILE
        //release possible ENT profile
        for (i = 0; i < CME_SCAN_MAX_PROFILES; i++)
        {

            if (preferredNetworks[i].profile.eap.eap_entProfileIndex != CME_INVALID_ENT_IDX)//meaning ent profile
            {

               //unset "in-use" bit for that entry
                cmeEntProfileParams_t pEntProfile[CME_MAX_EAP_ENTRIES];
                //get the current ENT profiles from FS
                LoadEnterpriseProfile_GetFromFlash(pEntProfile, TRUE);
                pEntProfile[preferredNetworks[i].profile.eap.eap_entProfileIndex].is_in_use = 0;
                SetEnterpriseProfile_SetToFlash(pEntProfile, TRUE);
            }

        }
#endif //CC35XX_SUPPORT_ENT_PROFILE

        CME_PRINT_PROFILE_REPORT("\n\rInitialize a preferred networks buffer");
        os_memset(preferredNetworks, 0, (sizeof(cmeProfileInfo_t) * CME_SCAN_MAX_PROFILES));
        for (i = 0; i < CME_SCAN_MAX_PROFILES; i++)
        {
            // Mark as free
            preferredNetworks[i].profile.id = CME_INVALID_PROFILE_ID;
            preferredNetworks[i].uniqueProfileId = CME_INVALID_PROFILE_ID;
            preferredNetworks[i].profile.disabled = 1;
            gPreferredNetworksConnAttemptCnt_ull[i] = CONN_ATTEMPT_INVALID_CTR;
            preferredNetworks[i].profile.eap.eap_entProfileIndex = CME_INVALID_ENT_IDX;
            preferredNetworks[i].pmkid_params.pmkid_set = 0;

        }
    }
    else
    {
#if CC35XX_SUPPORT_ENT_PROFILE
        //release possible ENT profile
        if (preferredNetworks[index].profile.eap.eap_entProfileIndex != CME_INVALID_ENT_IDX)//meaning ent profile
        {
            //unset "in-use" bit for that entry
            cmeEntProfileParams_t pEntProfile[CME_MAX_EAP_ENTRIES];
            //get the current ENT profiles from FS
            LoadEnterpriseProfile_GetFromFlash(pEntProfile, TRUE);
            pEntProfile[preferredNetworks[index].profile.eap.eap_entProfileIndex].is_in_use = 0;
            SetEnterpriseProfile_SetToFlash(pEntProfile, TRUE);
        }
#endif //CC35XX_SUPPORT_ENT_PROFILE
        //delete a specific profile
        os_memset(preferredNetworks + index, 0, sizeof(cmeProfileInfo_t));
        preferredNetworks[index].profile.disabled = 1;
        preferredNetworks[index].uniqueProfileId = CME_INVALID_PROFILE_ID;
        preferredNetworks[index].profile.id = CME_INVALID_PROFILE_ID;
        gPreferredNetworksConnAttemptCnt_ull[index] = CONN_ATTEMPT_INVALID_CTR;
        preferredNetworks[index].profile.eap.eap_entProfileIndex = CME_INVALID_ENT_IDX;
        preferredNetworks[index].pmkid_params.pmkid_set = 0;
    }



    status =  SetPreferredNetworks_SetToFlashFromPointer(preferredNetworks, TRUE);

    if (status != 0)
    {
        status = -1;
    }


    // We need to count free entries in preferredNetworks not in GLX.
    freeEntriesNum = CME_SCAN_MAX_PROFILES - getPreferredNetworksDbInfo(preferredNetworks, 0);

    GTRACE(GRP_CME, "cmeDeletePreferredNetwork: Delete profile with index %d, Flash delete status = %d, free entries number = %d",
                    index, (OK == status), freeEntriesNum);
    CME_PRINT_REPORT("\n\r cmeDeletePreferredNetwork: Delete profile with index %d, Flash delete status = %d, free entries number = %d",
                    index, (OK == status), freeEntriesNum);

    os_free(preferredNetworks);

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return status;
}

// DELETE NETWORK
void cmeIsCurrentlyConnectedProfileDeleted(int index)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    //
    //verify if currently connecting/connected profile is the deleted profile
    //if it is, issue disconnect request for this profile and delete it from fast connection if exist as well
    //
    if (cme_is_p2p_role_configured())
    {
#ifdef CC35XX_SUPPORT_P2P_PROFILE
        //TODO - P2P - support this logic for P2P as well?
        //ASSERT_GENERAL(0);
        return;
#endif
    }
    else if (cme_is_sta_role_like_activated())
    {
        struct wpa_supplicant *wpa_s;
        cmeMngReadPreferredNetworkFromFlash();
        // Get STA/P2P CL role is valid and select the correct iface
        drv_getStaIface(gpSupplicantGlobals, &wpa_s);
        
        //verify wpa_s is valid
        ASSERT_GENERAL(wpa_s!=NULL);
#if CC35XX_SUPPORT_PROFILE_DISCONNECT_ON_REMOVAL
        if ((CmeStationFlow_GetCurrentUser() ==  CME_STA_PROFILE_MANAGER_USER) /*make sure station flow is now under profile search*/
                &&
            (wpa_s->wpa_state > WPA_SCANNING)
                &&
                //determine if index removed is the index connected
            ((WLAN_DEL_ALL_PROFILES == index) || (gConnectingIndex_ull == index))
             /*profile connection that is currently >AUTHENTICATING*/)
        {

            GTRACE(GRP_CME, "cmeDeletePreferredNetwork: Deleted profile is the connected profile (index deleted is %d) - disconnect this network!",
                            index);
            CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: cmeIsCurrentlyConnectedProfileDeleted: CME_STA_WLAN_DISCONNECT_REQ_EVENT !!");

            //issue disconnection on user profile manager
            if (0 != CmeStationFlowSM(CME_STA_WLAN_DISCONNECT_REQ_EVENT,CME_STA_PROFILE_MANAGER_USER))
            {
               GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set disconnect in STA flow SM and failed!! ");
               ASSERT_GENERAL(0);
            }

            //WPA_DISCONNECT event will re-issue the cmeProfileManagerConfigChange
        }
        else
#endif //  CC35XX_SUPPORT_PROFILE_DISCONNECT_ON_REMOVAL
        {
            //Invoke in eloop context
            cmeProfileManagerConfigChange(0, CALLER5);
        }
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

}

//
//preferred networks command API's
//

// GET NETWORK
//
//Note: Passwords aren't returned since for WPA the pre-shared key is not stored - only the calculated one.
int16_t cmeGetPreferredNetwork(uint8_t Index, CMEWlanAddGetEapProfile_t *Args)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    CMESecType_e SecType = CME_SEC_TYPE_OPEN;
    cmeEntProfileParams_t pEntProfile[CME_MAX_EAP_ENTRIES];

    //read preferred network from FS
    cmeProfileInfo_t *preferredNetworks;
    uint32_t            preferredNetworksSize = sizeof(cmeProfileInfo_t) * CME_SCAN_MAX_PROFILES;
    preferredNetworks = os_malloc(preferredNetworksSize);
    LoadPreferredNetworks_GetFromFlashToPointer(preferredNetworks, FALSE);

    //get the current ENT profiles from FS
    LoadEnterpriseProfile_GetFromFlash(pEntProfile, FALSE);

    GTRACE(GRP_CME, "cmeGetPreferredNetwork: Done getting entGetProfileParamsFromFlash");

    if (Index > (preferredNetworksSize/sizeof(preferredNetworks[0])))
    {
        os_free(preferredNetworks);
        return -1;//FAILED
    }
    if (CME_INVALID_PROFILE_ID == preferredNetworks[Index].uniqueProfileId)
    {
        os_free(preferredNetworks);
        CME_PRINT_PROFILE_REPORT_ERROR("\n\rcmeGetPreferredNetwork index not found");
        return -1;//FAILED
    }
    //set security type
#if CC35XX_SUPPORT_P2P_PROFILE 
    if (WPAS_SSID_IS_P2P_PROFILE(preferredNetworks[Index].p2pProfile))
    {
        if (P2P_PUSH_BUTTON == preferredNetworks[Index].p2pProfile)
        {
            SecType = SL_SEC_TYPE_P2P_PBC;
        }
        else if(P2P_PIN_CODE_KEYPAD == preferredNetworks[Index].p2pProfile)
        {
            SecType = SL_SEC_TYPE_P2P_PIN_KEYPAD;
        }
        else if (P2P_PIN_CODE_DISPLAY == preferredNetworks[Index].p2pProfile)
        {
            SecType = SL_SEC_TYPE_P2P_PIN_DISPLAY;
        }
    }
    else
#endif //CC35XX_SUPPORT_P2P_PROFILE

    //Set Sectype
    SecType = preferredNetworks[Index].profile.secType;
    
//need implementation
#if CC35XX_SUPPORT_ENT_PROFILE
    else if (WPA_KEY_MGMT_IEEE8021X == preferredNetworks[Index].profile.key_mgmt)  // key_mgmt=WPA-EAP)
    {
        //SecType = CME_SEC_TYPE_WPA_ENT;
    }
#endif //CC35XX_SUPPORT_ENT_PROFILE


    //set security type
    Args->CommonAddProf.SecType = SecType;

    //set priority
    Args->CommonAddProf.Priority = preferredNetworks[Index].profile.priority;

    //copy SSID
    if (0 < preferredNetworks[Index].profile.ssid_len)
    {
        //set SSID length
        Args->CommonAddProf.SsidLen = preferredNetworks[Index].profile.ssid_len;
        os_memcpy(EAP_PROFILE_SSID_STRING(Args), preferredNetworks[Index].profile.ssid, preferredNetworks[Index].profile.ssid_len);
    }
    else
    {
        Args->CommonAddProf.SsidLen = 0;
    }
    // copy Bssid
    if(IRQ_UtilIsZeroMacAddress(preferredNetworks[Index].profile.bssid) == FALSE)
    {
        os_memcpy(Args->CommonAddProf.Bssid, preferredNetworks[Index].profile.bssid, ETH_ALEN);
    }

    //copy scan_ssid
    Args->CommonAddProf.Hidden = preferredNetworks[Index].profile.scan_ssid;

    //copy Identity
#if CC35XX_SUPPORT_ENT_PROFILE
    if(0 < preferredNetworks[Index].profile.eap.identity_len)
    {
        Args->UserLen = preferredNetworks[Index].profile.eap.identity_len;
        memcpy(EAP_PROFILE_USER_STRING(Args), pEntProfile[preferredNetworks[Index].profile.eap.eap_entProfileIndex].Identity, Args->UserLen);
    }
    //copy Anonymous
    if(0 < preferredNetworks[Index].profile.eap.anonymous_identity_len)
    {
        Args->AnonUserLen = preferredNetworks[Index].profile.eap.anonymous_identity_len;
        memcpy(EAP_PROFILE_ANON_USER_STRING(Args), pEntProfile[preferredNetworks[Index].profile.eap.eap_entProfileIndex].Anonymous,  Args->AnonUserLen);
    }
#endif // CC35XX_SUPPORT_ENT_PROFILE
    //set password length to zero since password is not transferred in getprofile
    Args->CommonAddProf.PasswordLen = 0;

#if CC35XX_SUPPORT_ENT_PROFILE
    Args->EapBitmask = 0;
    Args->EapBitmask |=  (preferredNetworks[Index].profile.pairwise_cipher << EAPBITMASK_PAIRWISE_CIPHER_SHIFT);
    Args->EapBitmask |=  (preferredNetworks[Index].profile.group_cipher << EAPBITMASK_GROUP_CIPHER_SHIFT);


    // added this check because when profile wasn't eap, we would fail here.
    if (preferredNetworks[Index].profile.eap.eap_entProfileIndex != CME_INVALID_ENT_IDX)
    {
        switch (pEntProfile[preferredNetworks[Index].profile.eap.eap_entProfileIndex].eap_method.method)
        {
        case EAP_TYPE_TLS:
            Args->EapBitmask |= (TLS);
            break;
        case EAP_TYPE_TTLS:
            Args->EapBitmask |= (TTLS);
            break;
        case EAP_TYPE_PEAP:

            if (preferredNetworks[Index].profile.eap.flags & EAP_CONFIG_FLAGS_PHASE1_PEAP)
            {
                Args->EapBitmask |= (PEAP1);
            }
            else
            {
                Args->EapBitmask |= (PEAP0);
            }

            break;
        case EAP_TYPE_FAST:
            Args->EapBitmask |= (FAST);
            break;
        default:
            break;
        }

    }

    Args->EapBitmask |= (EAP_CONFIG_PHASE2_GET(preferredNetworks[Index].profile.eap.flags) << EAPBITMASK_PHASE2_SHIFT);
#endif //CC35XX_SUPPORT_ENT_PROFILE
    os_free(preferredNetworks);

    return 0;
}

//
// cmeCopyProfileToAdHocProfile
//
void cmeCopyProfileToAdHocProfile(uint8_t index)
{
    os_memcpy(&gAdHocProfile_ull ,&gPreferredNetworks[index].profile, sizeof(_cme_minimized_wpa_ssid_t));

    gAdHocProfile_ull.profile.priority = 1; //set as high priority
    gAdHocProfile_ull.profile.scan_ssid = CME_ALL_PROFILES_ARE_HIDDEN;
    
}

//Add credentials received by WPS to the prefered networks
//Important!!!: This function is called AFTER the supplicant process and saves the credentials to the current network (Code in supplicant was changed)
//so it is safe to access wpa_s->current_ssid params.
int16_t cmeAddWpsCredentials2PreferredNetworks(struct wpa_supplicant *wpa_s, const struct wps_credential *cred)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    struct wpa_ssid *ssid = wpa_s->current_ssid;
    int16_t status =  -1;
    unsigned char bssid[ETH_ALEN];

    IRQ_UtilZeroMacAddress(bssid);

    //Read preferred network from FS to GLX before making changes
    cmeMngReadPreferredNetworkFromFlash();



    //Add the profile
    if ((cred->auth_type == WPS_AUTH_WPAPSK) || (cred->auth_type == WPS_AUTH_WPA2PSK))
    {
        status = add_preferred_network_wpa( 1, // scan_ssid
                                            CME_OPEN_POLICY_PROFILE_PRIORITY, //priority
                                            cred->ssid_len,
                                            0, // ssid_is_prefix
                                            1, //isPassphraseIsPMK,
                                            PMK_LEN, //passphrase lenght
                                            ssid->pairwise_cipher,
                                            ssid->group_cipher,  //TODO: , is this OK? It is not updated in the supplicant use DEFAULT_GROUP?
                                            ssid->key_mgmt,
                                            DEFAULT_PROTO,  // protocol
                                            (int8_t *) cred->ssid, // ssid
                                            bssid, //bssid is zero
                                            (int8_t *)ssid->psk, // passphrase
                                            gPreferredNetworks); //working directly on GLX global only in WPS
    }
    else if (cred->encr_type == WPS_ENCR_WEP)
    {
        status = add_preferred_network_wep( 1, // scan_ssid
                                            CME_OPEN_POLICY_PROFILE_PRIORITY, //priority
                                            cred->ssid_len,
                                            0, // ssid_is_prefix
                                            ssid->auth_alg,
                                            ssid->wep_tx_keyidx,
                                            ssid->wep_key_len[ssid->wep_tx_keyidx],
                                            (int8_t *) cred->ssid, // ssid
                                            bssid, //bssid is zero
                                            (int8_t *)ssid->wep_key, // keys
                                            gPreferredNetworks); //working directly on GLX global only in WPS
    }
    else if ((cred->auth_type == WPS_AUTH_OPEN) || (cred->auth_type == WPS_AUTH_SHARED))
    {
        status = add_preferred_network_open(1, // scan_ssid
                                            CME_OPEN_POLICY_PROFILE_PRIORITY,
                                            cred->ssid_len,
                                            0, // ssid_is_prefix
                                            (int8_t *) cred->ssid,
                                            bssid, //Bssid is zero
                                            gPreferredNetworks); //working directly on GLX global only in WPS
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    return (status);
}
#ifdef COMPILE_DEAD_FUNC
enum wpa_states getWpaState()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    struct wpa_supplicant * wpa_s ;

    // Get STA/P2P CL role is valid and select the correct iface
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    if(NULL == wpa_s)
    {
        /* wpa_supplicant_get_current_iface() must return valid pointer */
        GTRACE(GRP_CME, "getWpaState: shouldProtectConnect: wpa_supplicant_get_current_iface returned NULL on STA interface!");
        return WPA_INTERFACE_DISABLED;
    }
    else
    {

        return wpa_s->wpa_state;
    }
}
#endif

/* ----------------------------------------------------------------------------
 addProfile2Supplicant
                This function adds a profile to wpa_supplicant conf data base.
                Implementation is based on ctrl_iface.c functions:
                                wpa_supplicant_ctrl_iface_add_network
                                wpa_supplicant_ctrl_iface_set_network
                                wpa_supplicant_ctrl_iface_select_network
                Instead of filling string buffers with commands all functionality is copied
                to this function.

                The function may be invoked when a new profile is added or when ad-hoc
                conection is started. API should support both.

 Parameters:      input profile ssid to be duplicated into supplicant

 Return code:   if everything is OK - pointer to new SSID, else - NULL
---------------------------------------------------------------------------- */
struct wpa_ssid * addProfile2Supplicant(const _cme_minimized_wpa_ssid_t *apInputApSsid)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    struct wpa_ssid *pSsid;
    struct wpa_supplicant *wpa_s;

    // Get STA/P2P CL role is valid and select the correct iface
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    if (!CME_IS_ONGOING_WPS_AD_HOC_CONNECTION())
    {
        // ----------------------------------------------------------------------------
        // Add a new network to profiles DB
        // The add command returns netwrok ID which can be used to disable/remove the network.
        // Note that supplicant zeros the allocated structure
        // ----------------------------------------------------------------------------
 

        pSsid = wpa_config_add_network(wpa_s->conf);
        if (NULL == pSsid)
            return NULL;

        pSsid->disabled = 0;
        wpa_config_set_network_defaults(pSsid);

        GTRACE(GRP_CME, "Adding profile to supplicant conf. supp. profile id %d",pSsid->id);
        CME_CON_PRINT("\n\rAdding profile to supplicant conf. supp. profile id %d",pSsid->id);


        duplicateSharedSsidParams(
                apInputApSsid,
                pSsid/*update ssid*/);

        if ((apInputApSsid->eap.eap_entProfileIndex != CME_INVALID_ENT_IDX))
        {
            //eap profile duplication
            duplicateEapProfile(
                            wpa_s,
                            apInputApSsid,
                            pSsid/*update ssid*/);

        }
        else
        {
            GTRACE(GRP_CME, "apInputApSsid-psk_set %d",apInputApSsid->psk_set);

            //legacy (non-eap) security
            duplicateSecurityParams(
                    apInputApSsid,
                    pSsid/*update ssid*/);
            GTRACE(GRP_CME, "pSsid-psk_set %d",pSsid->psk_set);

        }
        wpas_notify_network_added(wpa_s, pSsid);

    }
    else
    {
        // For WPS supplicant allocates a network when WPS is started.
        // Take this network from wpa_s DB and use it from this point and on.
        pSsid = wpa_s->conf->ssid;

        // Currently shared parameetrs are set in addProfileIdToSupplicant
        // TODO - use duplicateSharedSsidParams
    }
//    else
//    {
//        if (NULL == pSsid->eap.phase1)
//        {
//            int registrar=0;
//
//            GTRACE(GRP_CME, "Set EAP phase1");
//            pSsid->eap.phase1 = os_malloc(sizeof("pbc=1"));
//            os_memcpy(pSsid->eap.phase1, "pbc=1", sizeof("pbc=1"));
//
//            if (wpa_config_set(pSsid, "key_mgmt", "WPS", 0) < 0 ||
//                wpa_config_set(pSsid, "eap", "WSC", 0) < 0 ||
//                wpa_config_set(pSsid, "identity", registrar ?
//                       "\"" WSC_ID_REGISTRAR "\"" :
//                       "\"" WSC_ID_ENROLLEE "\"", 0) < 0)
//            {
//                GTRACE(GRP_CME, "Error in setting WPS on supplicant profile");
//            }
//        }
//        else
//        {
//            GTRACE(GRP_CME, "EAP phase1 %s", pSsid->eap.phase1);
//        }
//    }


    //            // ----------------------------------------------------------------------------
    //            // Set network parameters in the DB (based on cc3100 code):
    //            // ----------------------------------------------------------------------------
    //            switch (apCmd->SecType)
    //            {
    //                            case SL_SEC_TYPE_OPEN:
    //
    //                                            break;
    //
    //                            case SL_SEC_TYPE_WEP:
    //            setSharedSsidParams(apCmd, WPA_KEY_MGMT_NONE, pSsid, apSsidStr, apPassword);
    //                                            break;
    //
    //                            case SL_SEC_TYPE_WPA_WPA2:
    //            setSharedSsidParams(apCmd, WPA_KEY_MGMT_PSK, pSsid, apSsidStr, apPassword);
    //                                            break;
    //
    //                            case SL_SEC_TYPE_WPS_PBC:
    //                                // TODO - still missing
    //                                ASSERT_GENERAL(0);
    //                                            break;
    //
    //                            case SL_SEC_TYPE_WPS_PIN:
    //                                // TODO - still missing
    //                                ASSERT_GENERAL(0);
    //                                            break;
    //            }

    // NEW
    //        if (WPA_KEY_MGMT_PSK == aKeyMgmt)
    //        {
    //            char buff[WPA_MAX_PASSPHRASE_LEN + 1];
    //
    //            if (wpa_config_set(pSsid, "key_mgmt", "WPA-PSK", 0) < 0)
    //            {
    //                GTRACE(GRP_CME, "ERROR: Failed to set network key mgmt");
    //                ASSERT_GENERAL(0);
    //            }
    //
    //            // Set NULL termination to password string
    //            //        memset(buff, 0, WPA_MAX_PASSPHRASE_LEN+1);
    //            //        memcpy(buff, apPassword, apCmd->PasswordLen);
    //            //        if (wpa_config_set(pSsid, "psk", buff, 0) < 0)
    //            //        {
    //            //            GTRACE(GRP_CME, "ERROR: Failed to set network psk");
    //            //            ASSERT_GENERAL(0);
    //            //        }
    //        }

    // NEW
    //            if (os_strcmp(name, "bssid") != 0 &&
    //        os_strcmp(name, "priority") != 0)
    wpa_sm_pmksa_cache_flush(wpa_s->wpa, pSsid);

    if ( (wpa_s->current_ssid == pSsid) || (NULL == wpa_s->current_ssid) )
    {
        /*
         * Invalidate the EAP session cache if anything in the current
         * or previously used configuration changes.
         */
        eapol_sm_invalidate_cached_session(wpa_s->eapol);
    }

    // NEW
    //        if (WPA_KEY_MGMT_PSK == aKeyMgmt)
    //        {
    //            wpa_config_update_psk(pSsid);
    //        }
    //    else if (os_strcmp(name, "priority") == 0)
    wpa_config_update_prio_list(wpa_s->conf);


    return pSsid;
}

static int8_t getUniqueProfileId()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    ++gUniqueProfileId_ull;

    //what should we do with wraparounds?
    if (gUniqueProfileId_ull < 0)
    {
        gUniqueProfileId_ull = CME_SCAN_MAX_PROFILES;
    }

    return gUniqueProfileId_ull;
}

#if 0
static uint32_t getNumEnabledProfiles()
{
    uint32_t i, numProfiles = 0;

    if (CME_INVALID_PROFILE_ID != gAdHocProfile_ull.uniqueProfileId)
        return 1;

    for (i=0 ; i<CME_SCAN_MAX_PROFILES ; ++i)
    {
        if (CME_INVALID_PROFILE_ID != gPreferredNetworks[i].uniqueProfileId)
            ++numProfiles;
    }

    return numProfiles;
}
#endif

scanResultsFilterCfg_e CME_GetScanResultsFilterCfg()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    scanResultsFilterCfg_e cfg = SCAN_RESULTS_PASS_ALL;

    if (CME_INVALID_PROFILE_ID != gAdHocProfile_ull.uniqueProfileId)
    {
        if (CME_IS_ONGOING_WPS_AD_HOC_CONNECTION())
        {
            cfg = SCAN_RESULTS_PASS_WPS;
        }
    }

    // TODO - add p2p support

    return cfg;
}

Bool_e CME_IsOngoingWPSAdHocConnection()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);
    return (CME_IS_ONGOING_WPS_AD_HOC_CONNECTION());
}

void CME_ClearWPSAdHocConnection()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    if ((CME_INVALID_PROFILE_ID != gAdHocProfile_ull.uniqueProfileId) && (CME_IS_ONGOING_WPS_AD_HOC_CONNECTION()))
    {
        //clean WPS flag
        gAdHocProfile_ull.profile.key_mgmt &= ~WPA_KEY_MGMT_WPS;
        gAdHocProfile_ull.uniqueProfileId = CME_INVALID_PROFILE_ID;
    }
}


void CME_SetWPSAdHocConnection()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    CME_SET_WPS_AD_HOC_CONNECTION();
}


void cmeClearAdHocProfile(struct wpa_supplicant *wpa_s)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    GTRACE(GRP_CME,"CME: cmeClearAdHocProfile uid=%d", 
        gAdHocProfile_ull.uniqueProfileId);  
    if (CME_INVALID_PROFILE_ID != gAdHocProfile_ull.uniqueProfileId)
    {
        // If we're disconnecting from an ad-hoc connection, remove the network
        // from supplicant profiles DB
        if (CME_IS_ONGOING_WPS_AD_HOC_CONNECTION())
        {
            //clean WPS flag
            gAdHocProfile_ull.profile.key_mgmt &= ~WPA_KEY_MGMT_WPS;
#ifdef CONFIG_WPS
            wpas_wps_cancel(wpa_s); //TODO:  - this is not always true
#endif
        }
        else
        {
            GTRACE(GRP_CME, "Removing unique profile id %d supplicant profile ID %d from supplicant conf",
                   gAdHocProfile_ull.uniqueProfileId, gAdHocProfile_ull.profile.id);

            gAdHocProfile_ull.profile.id = CME_INVALID_PROFILE_ID;
        }

        if (gAdHocProfile_ull.profile.passphrase)
        {
            os_free (gAdHocProfile_ull.profile.passphrase);
            gAdHocProfile_ull.profile.passphrase = NULL;
        }

        gAdHocProfile_ull.uniqueProfileId = CME_INVALID_PROFILE_ID;
    }

    //release possible ENT profile
    //release possible ENT profile
   if (gAdHocProfile_ull.profile.eap.eap_entProfileIndex != CME_INVALID_ENT_IDX)//meaning ent profile
   {
       //if there are Blobs remove them
       remove_cert_blob(wpa_s,"ca_blob");
       remove_cert_blob(wpa_s,"client_blob");
       remove_cert_blob(wpa_s,"key_blob");
       //unset "in-use" bit for that entry
       cmeEntProfileParams_t pEntProfile[CME_MAX_EAP_ENTRIES];
       //get the current ENT profiles from FS
       LoadEnterpriseProfile_GetFromFlash(pEntProfile, TRUE);
       pEntProfile[gAdHocProfile_ull.profile.eap.eap_entProfileIndex].is_in_use = 0;
       SetEnterpriseProfile_SetToFlash(pEntProfile, TRUE);
       gAdHocProfile_ull.profile.eap.eap_entProfileIndex = CME_INVALID_ENT_IDX;
   }
   HOOK(HOOK_IN_CME_CONNECTION_MNG);

}




/**
 * \fn     cmeSendConnectionStatusAsyncEvent
 * \brief  send connection state as event to host
 *
 * \param  connect_status - connected(1), disconnected(0) + set of connection parameters for both P2P and STA
 * \param  Reason_Code - for disconnection event, reason to disconnect  TODO - what values are expected by driver?
 * \param  roleId - ID of the reporting role
 * \return void
 *
 * \sa
 */

#if 0
void cmeSendConnectionStatusAsyncEvent(int connect_status, uint32_t Reason_Code, uint8_t roleId, uint8_t *bssidAddr)
{

    //CmdParserRetVal_e   RetVal;

    WlanEventConnect_t*  pArgs;
    uint16_t                Opcode;
    //struct p2p_device   *dev;
    //int dev_name_len    =0;
    //struct wpa_supplicant *wpa_s;
    RoleSsid_t*             pRoleSsid;
    pRoleSsid = Roles_GetSsId(roleId);
    SlWlanAsyncResponse_t AsyncEventResp;
    uint8_t apiId;
    uint8_t ssidName[33];//For debug print


    GTRACE(GRP_CME, "In cmeSendConnectionStatusAsyncEvent >> connect_status=%d, Reason_Code=%d",
           connect_status, Reason_Code);


    // allocate the wlan connect/disconenct legacy event to be sent
    pArgs = (WlanEventConnect_t*)os_zalloc(sizeof(WlanEventConnect_t));
    ASSERT_GENERAL(NULL != pArgs);




    if (connect_status)
    {

        if (GRP_CONN_MEASUREMENT_DEBUG || GRP_CONN_STATS)
        {
            uint64 t_entry = TimersMng_GetFreeRunningTsf64();
            uint32_t t_entryHigh = t_entry >> 32;
            uint32_t t_entryLow  = t_entry & 0xFFFFFFFF;
            GTRACE(GRP_CONN_MEASUREMENT_DEBUG || GRP_CONN_STATS,
                  "GRP_CONN_MEASUREMENT_DEBUG: Done WLAN connect command: TSF t_entryHigh=%d t_entryLow=%d ", t_entryHigh, t_entryLow);
        }
        //------------------------------------------------
        // stop measure measure measure
        RTA_GPIO_CLR(RTA_GROUP_CONN_MEASUREMENT_DEBUG,DBG_EVENT_ID_GPIO_WLAN_CONNECT,0);
        //------------------------------------------------


        /* --------------------------------*/
        /* Copy the ssid_len/ssid/bssid    */
        /* --------------------------------*/

        pArgs->Connect.SsidLen = pRoleSsid->ssidLength;

        os_memcpy(pArgs->Connect.SsidName, pRoleSsid->ssid,pRoleSsid->ssidLength);

        /* copy the mac address */
        os_memcpy(pArgs->Connect.Bssid, bssidAddr, ETH_ALEN);


        /* Set profile index on the padding field, for debug. It is printed on host side. */
        pArgs->Connect.Status = SL_WLAN_CONNECT_EVENT_STATUS_SUCCESS;

        /* connect event */
        Opcode = (cme_is_p2p_role_configured()) ? SL_OPCODE_WLAN_P2PCL_ASYNCCONNECTEDRESPONSE : SL_OPCODE_WLAN_STA_ASYNCCONNECTEDRESPONSE;
        //TODO cc33xx - should we support for tls?
        //gEnableDisableAuthentication = 1;
    }
    else
    {
        if (GRP_CONN_MEASUREMENT_DEBUG)
        {
            uint64 t_entry = TimersMng_GetFreeRunningTsf64();
            uint32_t t_entryHigh = t_entry >> 32;
            uint32_t t_entryLow  = t_entry & 0xFFFFFFFF;
            GTRACE(GRP_CONN_MEASUREMENT_DEBUG,"GRP_CONN_MEASUREMENT_DEBUG: Done WLAN disconnect command: TSF t_entryHigh=%d t_entryLow=%d ", t_entryHigh, t_entryLow);
        }
        //------------------------------------------------
        // stop measure measure measure
        RTA_GPIO_CLR(RTA_GROUP_CONN_MEASUREMENT_DEBUG,DBG_EVENT_ID_GPIO_WLAN_DISCONNECT,0);
        //------------------------------------------------

        pArgs->Disconnect.ReasonCode = gLastDisconnectInfo_ull.ReasonCode;

        /* copy the mac address */
        os_memcpy(pArgs->Disconnect.Bssid, gLastDisconnectInfo_ull.Bssid, ETH_ALEN);

        pArgs->Disconnect.SsidLen = gLastDisconnectInfo_ull.SsidLen;

        /* copy ssid if exits in the last disconnect info ..*/
        if (pArgs->Disconnect.SsidLen > 0)
        {
            os_memcpy(pArgs->Disconnect.SsidName, gLastDisconnectInfo_ull.SsidName, pArgs->Disconnect.SsidLen);
        }
        else
        {  /* take the ssid from the global current ssid one..*/

            pArgs->Disconnect.SsidLen = gCurrentSSIDLen;

            os_memcpy(pArgs->Disconnect.SsidName, gCurrentSSID, pArgs->Disconnect.SsidLen);
        }


        GTRACE(GRP_CME, "sl_async_event_send_connect_status: REASON_CODES: Reason_Code=%d, Reason_Code_Orig=%d",
               Reason_Code, pArgs->Disconnect.ReasonCode);

        /* disconnect event */
        if (0 == pArgs->Disconnect.ReasonCode)
        {
            pArgs->Disconnect.ReasonCode = WLAN_REASON_UNSPECIFIED;
        }


        Opcode = (cme_is_p2p_role_configured()) ? SL_OPCODE_WLAN_P2PCL_ASYNCDISCONNECTEDRESPONSE : SL_OPCODE_WLAN_STA_ASYNCDISCONNECTEDRESPONSE;
    }

    /* copy there device name */
    if (cme_is_p2p_role_configured())
    {
        //TODO cc33xx - support for P2P
        ASSERT_GENERAL(0);
//        if (gP2PactiveConneciton.active!=0)
//        {
//           wpa_s = wpa_supplicant_get_current_iface();
//           dev = p2p_get_device_name_from_peer_mac(wpa_s->global->p2p, gP2PactiveConneciton.device_peer_mac);
//
//           if (dev!=NULL)
//           {
//               dev_name_len = os_strlen(dev->device_name);
//               os_memcpy(pArgs->p2pcl_connect.go_peer_device_name, dev->device_name,dev_name_len);
//           }
//        }
//
//        pArgs->p2pcl_connect.go_peer_device_name_len = dev_name_len;
    }


    GTRACE(GRP_CME, "sl_async_event_send_connect_status: %d, role %x, mac ends with %x:%x",
            connect_status,
            roleId,
            pArgs->Connect.Bssid[4],
            pArgs->Connect.Bssid[5]);

    os_memcpy(ssidName, pArgs->Connect.SsidName, pArgs->Connect.SsidLen);
    ssidName[pArgs->Connect.SsidLen] = 0; //Null termination

    GTRACE(GRP_CME, "sl_async_event_send_connect_status: ssid %s", ssidName);

    /* send the user legacy registered event */
    RetVal = sl_dispatcher_sendEvent(Opcode, (uint8_t*)pArgs, sizeof(SlWlanEventData_u));

    if (RetVal != CMD_PARSER_OK)
    {
        GTRACE(GRP_CME, "sl_async_event_send: ERROR =0x%x", RetVal);
    }


    /* set the correct api id connect/disconnect event */
    apiId = (connect_status == 0) ?  HOST_API_TIMEOUT_ID_WLAN_DISCONNECT : HOST_API_TIMEOUT_ID_WLAN_CONNECT;


    /* specify that connect completed successfully, otherwise
     * API in progress is expected to be sent upon timeout expiry*/
    AsyncEventResp.Status = SL_STATUS_OK;

    /* -----------------------------------------------------------------------*/
    /* notify the host api timeout module on successfull process completion.  */
    /* internal async event with the data will be considered                  */
    /* -----------------------------------------------------------------------*/
    sl_host_timeout_notify_process_completed (apiId, (uint8_t*)&AsyncEventResp, sizeof(SlWlanAsyncResponse_t));

}
#endif

void cmeInvalidateLastPeerRemoved()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    GTRACE(GRP_CME, "cmeInvalidateLastPeerRemoved entry");

    // zero last peer removed mac address
    IRQ_UtilZeroMacAddress(gPeerRemovedMacAddr_ull);

}


BOOLEAN cmeIsLastPeerRemovedValid()
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    BOOLEAN isValid = !IRQ_UtilIsZeroMacAddress(gPeerRemovedMacAddr_ull);

    GTRACE(GRP_CME, "cmeIsLastPeerRemovedValid = %d", isValid);

    return isValid;
}

BOOLEAN cmeIsThisPeerInRemovalProgress(uint8_t *pMacAddr)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    BOOLEAN isPeerRemovalInProgress = FALSE;


    // if the last peer address is a valid one
    if (!IRQ_UtilIsZeroMacAddress(gPeerRemovedMacAddr_ull))
    {
        isPeerRemovalInProgress = !(memcmp(gPeerRemovedMacAddr_ull, pMacAddr, MAC_ADDR_LEN));
    }
    else
    {
        GTRACE(GRP_CME, "cmeIsPeerRemoveInProgress - LastPeer is invalid (zeros) ");
    }

    GTRACE(GRP_CME, "cmeIsPeerRemovalInProgress = %d ", isPeerRemovalInProgress);

    return isPeerRemovalInProgress;
}

// TODO need implementation
#if 0
void cmeFillProcessTimeoutData (SlWlanEventProcessTimeout_t *pMsg, uint8_t id)
{

    struct wpa_supplicant *wpa_s;

    /* Get STA/P2P CL role is valid and select the correct iface */
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);


    GTRACE(GRP_CME, "CME_WlanFillProcessTimeoutData - building process timeout event (id=%d)", id);


    // handle connect/disconnect timeouts
    if ((id == HOST_API_TIMEOUT_ID_WLAN_CONNECT) || (id == HOST_API_TIMEOUT_ID_WLAN_DISCONNECT))
    {
        /*
         * copy the required fields
         * please note that connect/disconnect structure share
         * the same ssid/bssid fields
         * */
        if (wpa_s->current_ssid != NULL)
        {

           GTRACE(GRP_CME, "CME_WlanFillProcessTimeoutData - building process timeout event");

           pMsg->Data.Connect.SsidLen = wpa_s->current_ssid->ssid_len;

           /* copy the ssid info */
           if (wpa_s->current_ssid->ssid != NULL)
           {
               if (wpa_s->current_ssid->ssid_len <= MAXIMAL_SSID_LENGTH)
               {
                   memcpy(pMsg->Data.Connect.SsidName, wpa_s->current_ssid->ssid, wpa_s->current_ssid->ssid_len);
               }
           }

           /* copy the bssid info */
           memcpy(pMsg->Data.Connect.Bssid, wpa_s->current_ssid->bssid, MAC_ADDR_LEN);

        }
        else
        {
            pMsg->Data.Connect.SsidLen = gAdHocProfile_ull.profile.ssid_len;

           /* copy the ssid info */
           memcpy(pMsg->Data.Connect.SsidName, gAdHocProfile_ull.profile.ssid, gAdHocProfile_ull.profile.ssid_len);

           /* copy the bssid info */
           memcpy(pMsg->Data.Connect.Bssid, gAdHocProfile_ull.profile.bssid, MAC_ADDR_LEN);

        }

    }
    else if (id == HOST_API_TIMEOUT_ID_WLAN_AP_REMOVE_PEER)
    {
        /* copy the mac address of the sta that has been removed */
        memcpy(pMsg->Data.STARemoved.Mac, gPeerRemovedMacAddr_ull, MAC_ADDR_LEN);
    }
    else
    {
        GTRACE(GRP_CME, "CME_WlanFillProcessTimeoutData - Unexpected id=%d", id);
        ASSERT_GENERAL(0);
    }

}
#endif

BOOLEAN cmeCompareLastAdHocConnParams(CMEWlanConnectCommon_t *pCmdbuffer)
{
    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    BOOLEAN IsDifferent = FALSE;

    BOOLEAN noCheck = TRUE; // Neither SSID nor BSSID where check;

    /* compare the conn params */
    if (pCmdbuffer->SsidLen > 0)
    {
        IsDifferent |= (pCmdbuffer->SsidLen != gAdHocProfile_ull.profile.ssid_len);
        IsDifferent |= !!(memcmp(SSID_STRING(pCmdbuffer), gAdHocProfile_ull.profile.ssid, pCmdbuffer->SsidLen));

        noCheck = FALSE;
    }

    /* if bssid is not fully null compare it as well */
    if ( pCmdbuffer->Bssid[0] ||
         pCmdbuffer->Bssid[1] ||
         pCmdbuffer->Bssid[2] ||
         pCmdbuffer->Bssid[3] ||
         pCmdbuffer->Bssid[4] ||
         pCmdbuffer->Bssid[5] )
    {

       /* compare the BSSID */
        IsDifferent |= !!(os_memcmp(pCmdbuffer->Bssid, gAdHocProfile_ull.profile.bssid, MAC_ADDR_LEN));

        noCheck = FALSE;
    }

    HOOK(HOOK_IN_CME_CONNECTION_MNG);

    if (noCheck)
    {
        IsDifferent = TRUE;
    }

    return IsDifferent;
}
Bool_e CMEisSameConnectParams(CMEWlanConnectCommon_t *pCmdbuffer, int8_t* ssidName, Bool_e checkBssid)
{
    struct wpa_supplicant *wpa_s;
    int temp = 0;
    Bool_e ret = FALSE;
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);
    if ( (pCmdbuffer->SecType != WLAN_SEC_TYPE_WPS_PBC) && (pCmdbuffer->SecType != WLAN_SEC_TYPE_WPS_PIN)
            && (pCmdbuffer->SecType != WLAN_SEC_TYPE_P2P_PBC) && (pCmdbuffer->SecType != WLAN_SEC_TYPE_P2P_PIN_KEYPAD)
            && (pCmdbuffer->SecType != WLAN_SEC_TYPE_P2P_PIN_DISPLAY) && (pCmdbuffer->SecType != WLAN_SEC_TYPE_P2P_PIN_AUTO) )
    {
        GTRACE(GRP_CME, "CME: Now compare ssid/bssid...");
        if ((pCmdbuffer->SsidLen > 0)
            && (gAdHocProfile_ull.profile.ssid_len))
        {
            if ((checkBssid == TRUE)
                && (!IRQ_UtilIsZeroMacAddress(gAdHocProfile_ull.profile.bssid))
                && ( pCmdbuffer->Bssid[0] ||
                    pCmdbuffer->Bssid[1] ||
                    pCmdbuffer->Bssid[2] ||
                    pCmdbuffer->Bssid[3] ||
                    pCmdbuffer->Bssid[4] ||
                    pCmdbuffer->Bssid[5] ))
            {
                GTRACE(GRP_CME, "CME: bssid params exist! Now compare if are the same");
                Report("\n\rCME: bssid params exist! Now compare if are the same");
                temp = os_memcmp(pCmdbuffer->Bssid, gAdHocProfile_ull.profile.bssid, MAC_ADDR_LEN);
            }
            if (pCmdbuffer->SsidLen == gAdHocProfile_ull.profile.ssid_len)
            {
                temp |= os_memcmp(ssidName, gAdHocProfile_ull.profile.ssid, pCmdbuffer->SsidLen);
                GTRACE(GRP_CME, "CME: same ssid len, ssid compare = %d, gSectype = %d, cmdSectype=%d key_mgmt=0x%x",
                    temp,  gAdHocProfile_ull.profile.secType, pCmdbuffer->SecType, gAdHocProfile_ull.profile.key_mgmt);
                    
                if ((0 == temp)
                    && (gAdHocProfile_ull.profile.secType == pCmdbuffer->SecType))
                {
                    ret = TRUE;
                }
            }
        }
    }
    return ret;
}
Bool_e CMEIsWPA3TransitionModeDisabled(uint32_t keyMgmt, int32_t profileId)
{
    struct wpa_supplicant *wpa_s;
    struct wpa_ssid *pSsid;
    RoleType_e roleType;
    roleType = drv_getStaIface(gpSupplicantGlobals, &wpa_s);
    if (ROLE_IS_TYPE_STA(roleType))
    {
        pSsid = wpa_config_get_network(wpa_s->conf, profileId);
        if (pSsid)
        {
            CME_PRINT_REPORT("\r\n CME: existing supplicant profile_id=%d, supp. keymgmt=0x%x, init keymgmt=0x%x",
                profileId, pSsid->key_mgmt, keyMgmt); 

            if (((keyMgmt - pSsid->key_mgmt) != 0)
                && (((keyMgmt & pSsid->key_mgmt) == WPA_KEY_MGMT_SAE) ||
                    ((keyMgmt & pSsid->key_mgmt) == WPA_KEY_MGMT_FT_SAE) ||
                    ((keyMgmt & pSsid->key_mgmt) == (WPA_KEY_MGMT_SAE | WPA_KEY_MGMT_FT_SAE))))
            {
                CME_PRINT_REPORT("\n\rCME: WPA3-Personal Transition Mode DISABLE is Required");
                return TRUE;
            }
        }
    }
    return FALSE;
}

const char *cmeWlanGetKeyMgmt(void)
{
    struct wpa_supplicant *wpa_s;
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);
    return wpa_key_mgmt_txt(wpa_s->key_mgmt,
					     wpa_s->current_ssid->proto);   
}

void cmeWlanConnectDigest(CMEWlanConnectCommon_t *pConnectCmd, CMEEapWlanConnect_t* pEapConnectCmd, uint32_t keyMgmtType, uint16_t connectReq, Bool_e bReconnect)
{
    uint8_t secType = WLAN_SEC_TYPE_OPEN;
    struct wpa_supplicant *wpa_s;
    RoleType_e roleType = ROLE_TYPE_NONE;
    uint32 roleId = ROLE_ID_NONE;
    ti_driver_ifData_t *pDrv = NULL;

    if(pConnectCmd)
    {
        secType = pConnectCmd->SecType;
    }

    // find role that requested connection : STA/CL or P2P DEVICE
    if (pConnectCmd && (secType >= WLAN_SEC_TYPE_P2P_PBC)
        && (secType <= WLAN_SEC_TYPE_P2P_PIN_AUTO))
    {
        wpa_s = drv_getP2pDeviceSupplicant();
        if (wpa_s == NULL)
        {
            GTRACE(GRP_CME, "CME: No P2P Device found!!!");
            ASSERT_GENERAL(0);
        }
        pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
        roleType = pDrv->roleType;
        roleId = pDrv->roleId;
        CME_PRINT_REPORT("\r\n CME: P2P search for peer bssid %x:%x:%x:%x:%x:%x", pConnectCmd->Bssid[0],
            pConnectCmd->Bssid[1], pConnectCmd->Bssid[2], pConnectCmd->Bssid[3], pConnectCmd->Bssid[4], pConnectCmd->Bssid[5]);
    }
    else
    {
         
        /* Get STA/P2P CL role is valid and select the correct iface - we don't check for
        * either wpa_s validity nor BSSID validity, since we are already connected.       */
        roleType = drv_getStaIface(gpSupplicantGlobals, &wpa_s);
        pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
        roleId = pDrv->roleId;

    }

    //deal each roleType separelty 

    /*  For STA role */
    /* specifiy this cmd requested by the user */
    if (ROLE_IS_TYPE_STA_BASED(roleType)
        && (connectReq & CME_GENERAL_DATA_CONNECT_IS_USER_REQ))
    {
        /* sta is connected and host is waiting for a response*/
        if (CmeStationFlowIsConnected() )//&& sl_host_timeout_is_api_running(HOST_API_TIMEOUT_ID_WLAN_CONNECT))
        {

            GTRACE(GRP_CME, "CME: cmeWlanConnectDigest(): bReconnect=%d", bReconnect);
#if 0 //TODO why this code of wlan connect was remarked out
                            if (bReconnect == FALSE)
                            {
                                uint16_t                 opcode;
                                CmdParserRetVal_e      RetVal;
                                struct wpa_supplicant *wpa_s;

                                GTRACE(GRP_CME, "CME: We already CONNECTED to the desired AP. Nothing to do.. !!");

                                /* --------------------------------------------------------------------------------*/
                                /* Prepare external (Host connect user event, with 'Already connected' status. )   */
                                /* --------------------------------------------------------------------------------*/

                                /* Get STA/P2P CL role is valid and select the correct iface - we don't check for
                                 * either wpa_s validity nor BSSID validity, since we are already connected.       */
                                drv_getStaIface(gpSupplicantGlobals, &wpa_s);


                                //Check if we are really connected (race condition between CME_MESSAGE_ID_WLAN_CONNECT and CME_MESSAGE_ID_WPA_SUPP_DISCONNECTED)
                                if (wpa_s->current_ssid != NULL)
                                {
                                    SlWlanEventData_u* pArgs =
                                            (SlWlanEventData_u*)AllocateEvent(sizeof(SlWlanEventData_u), __LINE__);

                                    /* copy the ssid */
                                    memset(pArgs->Connect.SsidName, 0, SSID_MAX_LEN);
                                    pArgs->Connect.SsidLen = wpa_s->current_ssid->ssid_len;

                                    if ((pArgs->Connect.SsidLen > 0) && (pArgs->Connect.SsidLen < SSID_MAX_LEN))
                                    {
                                        os_memcpy(pArgs->Connect.SsidName, wpa_s->current_ssid->ssid, pArgs->Connect.SsidLen);

                                    }

                                    pArgs->Connect.Status = SL_WLAN_CONNECT_EVENT_STATUS_ALREADY_CONNECTED;

                                    /* copy the mac address */
                                    os_memcpy(&pArgs->Connect.Bssid[0], wpa_s->bssid, ETH_ALEN);

                                    /* connect event */
                                     opcode = (cme_is_p2p_role_configured()) ? SL_OPCODE_WLAN_P2PCL_ASYNCCONNECTEDRESPONSE :
                                                                               SL_OPCODE_WLAN_STA_ASYNCCONNECTEDRESPONSE   ;

                                     /* send the user legacy registered event */
                                     RetVal = sl_dispatcher_sendEvent(opcode, (uint8_t*)pArgs, sizeof(SlWlanEventData_u));

                                     if (RetVal != CMD_PARSER_OK)
                                     {
                                         GTRACE(GRP_CME, "sl_async_event_send: ERROR =0x%x", RetVal);
                                     }
                                }

                                 /* --------------------------------------------------------------------------------*/
                                 /* Prepare internal (driver registered connect event, with 'success' status. )     */
                                 /* --------------------------------------------------------------------------------*/
                                 opcode = SL_OPCODE_WLAN_STAP2PCL_ASYNCCONNECTEDRESPONSE;

                                 /* allocate the internal event */
                                 SlWlanAsyncResponse_t* pEvent = (SlWlanAsyncResponse_t*)AllocateEvent(sizeof(SlWlanAsyncResponse_t), __LINE__);
                                 ASSERT_GENERAL(NULL != pEvent);

                                 /* specify that STA is connected */
                                 pEvent->Status = SL_STATUS_OK;

                                 sl_host_timeout_api_stop(HOST_API_TIMEOUT_ID_WLAN_CONNECT);

                                 /* ------------------------------------------------------------*/
                                 /* ok, we are already connected, so just send the conn event   */
                                 /* to host (will release the blocking host api)                */
                                 /* ------------------------------------------------------------*/
                                 RetVal = sl_dispatcher_sendEvent(opcode, (uint8_t*)pEvent, sizeof(SlWlanAsyncResponse_t));

                                 if (RetVal != CMD_PARSER_OK)
                                 {
                                     GTRACE(GRP_CME, "sl_async_event_send: ERROR =0x%x", RetVal);
                                 }

                                 /* cancel process timeout monitoring that already started */
                                 sl_host_timeout_process_stop(HOST_API_TIMEOUT_ID_WLAN_CONNECT);

                                 // Everything done, free the connection info memory
                                 if (msg.un.wlanConnect.pConnectEapCmd != NULL)
                                 {
                                     os_free(msg.un.wlanConnect.pConnectEapCmd);
                                 }
                                 else
                                 {
                                     os_free(msg.un.wlanConnect.pConnectCmd);
                                 }

                                 break; /* exit point */
                            }
#endif
        } /* end of cme is in connected state and API timeout is monitored */

        else if((CmeStationFlowHostStatusGet() == WLAN_STATUS_SCANNING)
                &&
                //S May 15 2017 - CC3XXX-187
                // we must make sure the current scan is serving ad-hoc connect command and not profile connections
                (CME_STA_WLAN_CONNECT_USER == CmeStationFlow_GetCurrentUser()))
        {

            GTRACE(GRP_CME, "CME: STA in scanning state... (bReconnect=%d) ", bReconnect);

            if (bReconnect == FALSE)
            {

                GTRACE(GRP_CME, "CME: same connect request is in progress - do not disturbe! *****");
                CME_PRINT_REPORT("\n\rCME: same connect request is in progress - do not disturbe! *****");
#if 0 // EAP command
                                // Everything done, free the connection info memory
                                if (msg.un.wlanConnect.pConnectEapCmd != NULL)
                                {
                                    os_free(msg.un.wlanConnect.pConnectEapCmd);
                                }
                                else
#endif
                {

                    if(pConnectCmd)
                    {
                        os_free(pConnectCmd);
                    }
                    if(pEapConnectCmd)
                    {
                        os_free((void *)pEapConnectCmd);
                    }
                }

                /* same connect request is in progress
                * so just let the current running request to continue... */
                    return; /* exit point */
            }
        }
    } /* end of if it is a user iniated request */

    /* check if disconnection / stop-scan needed before connection */
    if (!CmeStationFlowIsSMIdle() && ROLE_IS_TYPE_STA_BASED(roleType))
    {

        GTRACE(GRP_CME, "CME: Disconnecting previous connection / stopping scans upon ad-hoc wlanconnect command user=%d",
             CmeStationFlow_GetCurrentUser());
        CME_PRINT_REPORT("\n\rCME: Disconnecting previous connection / stopping scans upon ad-hoc wlanconnect command");
        CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: cmeWlanConnectDigest, change state to :CME_STA_WLAN_DISCONNECT_REQ_EVENT");
        if (0 != CmeStationFlowSM(CME_STA_WLAN_DISCONNECT_REQ_EVENT,CmeStationFlow_GetCurrentUser()))
        {
            GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set disconnect in STA flow SM and failed!! ");
            ASSERT_GENERAL(0);
            //exit point
        }

    }

    /*
     * here, we already consider to send disconnect event to SM, and now if
     * STA is disconnected we need to keep going with the connection sequence
     *
     * */
    if (ROLE_IS_TYPE_STA_BASED(roleType))
    {
        if ( CmeStationFlowIsSMIdle())
        {
            if (FALSE == gSaveCurrentSupplicantProfile)
            {
                GTRACE(GRP_CME,"CME: cmeWlanConnect need to remove old profile from supplicant"); 
                cmeRemoveAllProfilesFromSupplicant(wpa_s, WLAN_REASON_DEAUTH_LEAVING);
            }
            //
            //only if STA is in idle state we can issue network search request action on wlan connect user
            //
        	CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: cmeWlanGetKeyMgmt: change state to : CME_STA_NETWORK_SEARCH_EVENT !!");

            //set state in STA flow SM with wlanConnect User
            if (0 != CmeStationFlowSM(CME_STA_NETWORK_SEARCH_EVENT,CME_STA_WLAN_CONNECT_USER))
            {
                GTRACE(GRP_CME,"CME: ERROR!CmeStationFlowSM tried to set scan in STA flow SM and failed!! ");
                CME_PRINT_REPORT_ERROR("\r\nCME: ERROR!CmeStationFlowSM tried to set scan in STA flow SM and failed!! ");
                ASSERT_GENERAL(0);
                //exit point
            }


            //TODO:  - ssid is not null terminated string!! fix the trace.
            //GTRACE(GRP_CME, "CME: Got connect command, key %d, ssid %s", msg.un.wlanConnect.keyMgmtType, (eapCmd!=NULL ? (char *)SSID_STRING(&eapCmd->Common) : (char *)SSID_STRING(msg.un.wlanConnect.pConnectCmd) ));

            //send the actual connect command with the relevant ssid
            cmeWlanConnect(roleId,
                                pConnectCmd,
                                pEapConnectCmd,
                                keyMgmtType,
                                !!(connectReq & CME_GENERAL_DATA_CONNECT_IS_PROFILES));
        }
        else
        {
            //STA deauth requested - waiting for wpa disconnect request

            //Copy the command to a local buffer pending for disconnect event

            cmePendingWlanConnectStor(pConnectCmd,
                                       pEapConnectCmd,
                                        keyMgmtType,
                                        !!(connectReq & CME_GENERAL_DATA_CONNECT_IS_PROFILES));

        }
    }
    else if (ROLE_IS_TYPE_DEVICE(roleType))
    {
        cmeWlanConnect(roleId, 
                        pConnectCmd,
                        NULL,
                        keyMgmtType,
                        !!(connectReq & CME_GENERAL_DATA_CONNECT_IS_PROFILES));
    }
    else
    {
        ASSERT_GENERAL(0);
    }

}

//==================================================================
//  PMK caching support  
//==================================================================

#ifdef CME_ENT_SUITE_B_PMK_CACHE_SUPPORT

int cme_store_kck(const u8 *kck, size_t kck_len)
{
    if (!kck || kck_len == 0 || kck_len > sizeof(gCmeKck.kck)) 
    {
        os_memset(gCmeKck.kck, 0, sizeof(gCmeKck.kck));
        gCmeKck.kck_len = 0;
        gCmeKck.kck_valid = 0;
        return -1;
    }

    os_memcpy(gCmeKck.kck, kck, kck_len);
    gCmeKck.kck_len = kck_len;
    gCmeKck.kck_valid = 1;
    
    return 0;
}
/**
 * is_kck_available - Check if a valid KCK is available
 * Returns: 1 if valid KCK is available, 0 otherwise
 */
int cme_is_kck_available(void)
{
    return gCmeKck.kck_valid;
}

/**
 * clear_stored_kck - Clear the stored KCK
 */
void cme_clear_stored_kck(void)
{
    os_memset(gCmeKck.kck, 0, sizeof(gCmeKck.kck));
    gCmeKck.kck_len = 0;
    gCmeKck.kck_valid = 0;
}
void cme_get_kck(struct wpa_supplicant *wpa_s)
{
    struct wpa_sm *sm = wpa_s->wpa;
    if (sm != NULL)
    {
        size_t kck_len = sm->ptk.kck_len;
        Report("\n\r CME: derive kck. len=%d", kck_len);
        if (kck_len > 0)
        {
            cme_store_kck(sm->ptk.kck, sm->ptk.kck_len);
        }
    }

}
#endif //CME_ENT_SUITE_B_PMK_CACHE_SUPPORT
void cmeAddWpaPmkCache(struct wpa_supplicant *wpa_s, const uint8_t *pmkid, uint8_t *pmk, uint8_t pmk_len, uint8_t *bssid, int key_mgmt)
{
    _cme_wpa_pmkid_params_t *pmkid_params;
    if (gAdHocProfile_ull.uniqueProfileId == CME_INVALID_PROFILE_ID)
    {
        if ((gConnectingIndex_ull != CONN_ATTEMPT_INVALID_IDX) &&
            (gConnectingIndex_ull < CME_MAX_SCAN_SSID))
        {
            CME_PRINT_REPORT("\n\r cmeAddWpaPmkCache: it's a profile connection index = %d", gConnectingIndex_ull);
            pmkid_params = &gPreferredNetworks[gConnectingIndex_ull].pmkid_params;
        }
        else
        {
            CME_PRINT_REPORT("\n\r Not a valid Profile index!!!");
            return;
        }
    }
    else
    {
        CME_PRINT_REPORT("\n\r cmeAddWpaPmkCache: it's ad-hoc connection");
        pmkid_params = &gAdHocProfile_ull.pmkid_params;
        if (gAdHocProfile_ull.profile.eap.eap_entProfileIndex != CME_INVALID_ENT_IDX)
        {
            CME_PRINT_REPORT("\n\r cmeAddWpaPmkCache: it's an ENT ad-hoc connection");

            pmkid_params = &gAdHocEapPmkidParams_ull;

#ifdef CME_ENT_SUITE_B_PMK_CACHE_SUPPORT
            if(CME_IS_ENT_KEY_MGMT_SUITE_B_TYPE(gAdHocProfile_ull.profile.key_mgmt))
            {
                CME_PRINT_REPORT("\n\r cmeAddWpaPmkCache: it's an ENT ad-hoc suite B profile derive kck");
                cme_get_kck(wpa_s);
            }
#endif // CME_ENT_SUITE_B_PMK_CACHE_SUPPORT
        }

    }

    pmkid_params->pmkid_set = 1;
    
    os_memset(pmkid_params->pmkid, 0, PMKID_LEN);
    os_memset(pmkid_params->pmk, 0, PMK_LEN_MAX);

    os_memcpy(pmkid_params->pmkid, pmkid, PMKID_LEN);
    os_memcpy(pmkid_params->bssid, bssid, ETH_ALEN);
    pmkid_params->pmk_len = pmk_len;
    os_memcpy(pmkid_params->pmk, pmk, pmk_len);

    //keep the selected key_mgmt
    pmkid_params->key_mgmt = key_mgmt;
    
}

void cmeRemoveWpaPmkCache(void)
{
    // Check and clear ENT ad-hoc PMK cache
    if (gAdHocEapPmkidParams_ull.pmkid_set)
    {
        CME_PRINT_REPORT("\n\r cmeRemoveWpaPmkCache: clearing ENT ad-hoc PMK cache");
#ifdef CME_ENT_SUITE_B_PMK_CACHE_SUPPORT
        if (CME_IS_ENT_KEY_MGMT_SUITE_B_TYPE(gAdHocEapPmkidParams_ull.key_mgmt))
        {
            cme_clear_stored_kck();
        }
#endif //CME_ENT_SUITE_B_PMK_CACHE_SUPPORT
        gAdHocEapPmkidParams_ull.pmkid_set = 0;
    }

    // Check and clear regular ad-hoc PMK cache
    if (gAdHocProfile_ull.pmkid_params.pmkid_set)
    {
        CME_PRINT_REPORT("\n\r cmeRemoveWpaPmkCache: clearing ad-hoc PMK cache");
        gAdHocProfile_ull.pmkid_params.pmkid_set = 0;
    }

    // Check and clear profile PMK cache
    if ((gConnectingIndex_ull < CME_SCAN_MAX_PROFILES) &&
        (gPreferredNetworks[gConnectingIndex_ull].pmkid_params.pmkid_set))
    {
        CME_PRINT_REPORT("\n\r cmeRemoveWpaPmkCache: clearing profile PMK cache index=%d", gConnectingIndex_ull);
        gPreferredNetworks[gConnectingIndex_ull].pmkid_params.pmkid_set = 0;
    }
}

void cmeReassociationParamsStore()
{
    struct wpa_supplicant *wpa_s;
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);
    CME_PRINT_REPORT("\r\ncmeReassociationParamsStore - store activated");

    if ((wpa_s == NULL) || (wpa_s->wpa == NULL))
    {
        GTRACE(GRP_CME, "cmeReassociationParamsStore: wpa_s or wpa_s->wpa is NULL");
        return;
    }

    os_memset(&g_reassociation_params, 0, sizeof(g_reassociation_params));


    g_reassociation_params.valid = TRUE;
    //save current ssid & keymgmt
    os_memcpy(g_reassociation_params.int_curr_ssid, wpa_s->current_ssid->ssid, wpa_s->current_ssid->ssid_len);
    g_reassociation_params.int_curr_ssid_len = wpa_s->current_ssid->ssid_len;
    g_reassociation_params.int_key_mgmt = wpa_s->current_ssid->key_mgmt;

    os_memcpy(g_reassociation_params.prev_bssid, wpa_s->sme.prev_bssid, ETH_ALEN);
    g_reassociation_params.prev_bssid_set = wpa_s->sme.prev_bssid_set;

    g_reassociation_params.ft_used = wpa_s->sme.ft_used;
    os_memcpy(g_reassociation_params.mobility_domain, wpa_s->sme.mobility_domain, MOBILITY_DOMAIN_ID_LEN);

    g_reassociation_params.ptk_set = wpa_s->wpa->ptk_set;
    g_reassociation_params.tptk_set = wpa_s->wpa->tptk_set;
    g_reassociation_params.pmk_len = wpa_s->wpa->pmk_len;
    // For buffers with associated length variables: copy data only when length is valid.
    // If length is invalid, the buffer remains untouched, and zeroed data will be used during restoration.
    if (wpa_s->wpa->pmk_len <= PMK_LEN_MAX)
    {
        os_memcpy(g_reassociation_params.pmk, wpa_s->wpa->pmk, PMK_LEN_MAX);
    }
    os_memcpy(&g_reassociation_params.ptk, &wpa_s->wpa->ptk, sizeof(struct wpa_ptk));
    os_memcpy(&g_reassociation_params.tptk, &wpa_s->wpa->tptk, sizeof(struct wpa_ptk));
    os_memcpy(&g_reassociation_params.gtk, &wpa_s->wpa->gtk, sizeof(struct wpa_gtk));
    os_memcpy(&g_reassociation_params.gtk_wnm_sleep, &wpa_s->wpa->gtk_wnm_sleep, sizeof(struct wpa_gtk));
    os_memcpy(&g_reassociation_params.igtk, &wpa_s->wpa->igtk, sizeof(struct wpa_igtk));
    os_memcpy(&g_reassociation_params.igtk_wnm_sleep, &wpa_s->wpa->igtk_wnm_sleep, sizeof(struct wpa_igtk));
#ifdef CONFIG_IEEE80211R
    if (wpa_s->wpa->xxkey_len <= PMK_LEN_MAX)
    {
        os_memcpy(g_reassociation_params.xxkey, wpa_s->wpa->xxkey, PMK_LEN_MAX);
    }
    g_reassociation_params.xxkey_len = wpa_s->wpa->xxkey_len;
    if (wpa_s->wpa->pmk_r0_len <= PMK_LEN_MAX)
    {
        os_memcpy(g_reassociation_params.pmk_r0, wpa_s->wpa->pmk_r0, PMK_LEN_MAX);
    }
    g_reassociation_params.pmk_r0_len = wpa_s->wpa->pmk_r0_len;
    if (wpa_s->wpa->pmk_r1_len <= PMK_LEN_MAX)
    {
        os_memcpy(g_reassociation_params.pmk_r1, wpa_s->wpa->pmk_r1, PMK_LEN_MAX);
    }
    g_reassociation_params.pmk_r1_len = wpa_s->wpa->pmk_r1_len;
#endif /* CONFIG_IEEE80211R */
}

void cmeReassociationParamsRestore()
{
    struct wpa_supplicant* wpa_s;
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    if ((wpa_s == NULL) || (wpa_s->wpa == NULL))
    {
        GTRACE(GRP_CME, "cmeReassociationParamsRestore: wpa_s or wpa_s->wpa is NULL");
        return;
    }

    os_memcpy(wpa_s->sme.prev_bssid, g_reassociation_params.prev_bssid, ETH_ALEN);
    wpa_s->sme.prev_bssid_set = g_reassociation_params.prev_bssid_set;

    wpa_s->sme.ft_used = g_reassociation_params.ft_used;
    os_memcpy(wpa_s->sme.mobility_domain, g_reassociation_params.mobility_domain, MOBILITY_DOMAIN_ID_LEN);

    wpa_s->wpa->ptk_set = g_reassociation_params.ptk_set;
    wpa_s->wpa->tptk_set = g_reassociation_params.tptk_set;
    wpa_s->wpa->pmk_len = g_reassociation_params.pmk_len;
    os_memcpy(wpa_s->wpa->pmk, g_reassociation_params.pmk, PMK_LEN_MAX);
    os_memcpy(&wpa_s->wpa->ptk, &g_reassociation_params.ptk, sizeof(struct wpa_ptk));
    os_memcpy(&wpa_s->wpa->tptk, &g_reassociation_params.tptk, sizeof(struct wpa_ptk));
    os_memcpy(&wpa_s->wpa->gtk, &g_reassociation_params.gtk, sizeof(struct wpa_gtk));
    os_memcpy(&wpa_s->wpa->gtk_wnm_sleep, &g_reassociation_params.gtk_wnm_sleep, sizeof(struct wpa_gtk));
    os_memcpy(&wpa_s->wpa->igtk, &g_reassociation_params.igtk, sizeof(struct wpa_igtk));
    os_memcpy(&wpa_s->wpa->igtk_wnm_sleep, &g_reassociation_params.igtk_wnm_sleep, sizeof(struct wpa_igtk));
#ifdef CONFIG_IEEE80211R
    os_memcpy(wpa_s->wpa->xxkey, g_reassociation_params.xxkey, PMK_LEN_MAX);
    wpa_s->wpa->xxkey_len = g_reassociation_params.xxkey_len;
    os_memcpy(wpa_s->wpa->pmk_r0, g_reassociation_params.pmk_r0, PMK_LEN_MAX);
    wpa_s->wpa->pmk_r0_len = g_reassociation_params.pmk_r0_len;
    os_memcpy(wpa_s->wpa->pmk_r1, g_reassociation_params.pmk_r1, PMK_LEN_MAX);
    wpa_s->wpa->pmk_r1_len = g_reassociation_params.pmk_r1_len;
#endif /* CONFIG_IEEE80211R */
CME_CON_PRINT("\r\ncmeReassociationParamsRestore - restore activated");
}

void cmeReassociationParamsClear()
{
    CME_CON_PRINT("cmeReassociationParamsClear - clearing g_reassociation_params");
    os_memset(&g_reassociation_params, 0, sizeof(g_reassociation_params));
}

Bool_e cmeAreReassociationParamsValid(const _cme_minimized_wpa_ssid_t *apInputApSsid)
{
    if(g_reassociation_params.valid)
    {
        if (!(apInputApSsid->key_mgmt & g_reassociation_params.int_key_mgmt))
            return FALSE;
        if (apInputApSsid->ssid_len != g_reassociation_params.int_curr_ssid_len)
            return FALSE;
        if (os_memcmp(apInputApSsid->ssid, g_reassociation_params.int_curr_ssid,
                      apInputApSsid->ssid_len) != 0)
            return FALSE;
        return TRUE;
    }
    return FALSE;
}

//==================================================================
//  P2P Related:
//==================================================================

Bool_e CME_IsP2PConnectionRequired(uint8_t secType)
{
    if ((secType >= WLAN_SEC_TYPE_P2P_PBC) 
        && (secType <= WLAN_SEC_TYPE_P2P_PIN_AUTO))
    {
        return TRUE;
    }
    return FALSE;
}


#ifndef TI_STA_ONLY_BUILD
void cmeHandleP2pConnection(CMEWlanConnectCommon_t *apCmd, uint32_t aKeyMgmt)
{
    ti_driver_ifData_t *pDevDrv = drv_getDriverData(NETIF_NAME(TIWLAN_DEV_NAME_P2PDEV));
    struct wpa_supplicant *wpas = NULL;
    struct p2p_data *p2p = NULL; //gets P2P State
    uint8_t p2pState = 0xF; //Invalid state

    if (pDevDrv == NULL)
    {
        //should not happen - since checked earlier
        GTRACE(GRP_CME, "CME: Connection received for P2P Security, but p2p device role isn't enabled!!!");
        ASSERT_GENERAL(0);
    }

    wpas = pDevDrv->wpa_s;
    p2p = wpas->global->p2p;
    p2pState = p2p->state;

    GTRACE(GRP_CME, "CME: Manage p2p connection request here. P2P_SEC=%d (Current P2P State=%d) wpas->wpa_state=%d", 
                    apCmd->SecType, p2p->state, wpas->wpa_state);

    switch(p2pState)
    {
        case P2P_SEARCH:
        case P2P_LISTEN_ONLY:
            GTRACE(GRP_CME, "CME: P2P is already during Find");
            cmeStopP2pFind(wpas);
            cmePendingWlanConnectStor(apCmd,NULL,aKeyMgmt,0);
            // we will trigger new p2p_find anyway
            gCmeP2pInfo.p2pConnectPending = TRUE;
            return;
            break;
        case P2P_CONNECT:
        case P2P_CONNECT_LISTEN:
            GTRACE(GRP_CME, "CME: P2P GO Negotiation is already started!");
            CME_PRINT_REPORT_ERROR("\r\nCME: ERROR! P2P GO Negotiation is already started!");
            cmeP2pCancel();
            return;
            break;
    }


        //if pDevDrv exist - that mean p2p device role is enabled
        // store connection params on  driver priv
        pDevDrv->p2pConnectionStarted = TRUE; 
        pDevDrv->p2pWpsMethod = apCmd->SecType;

        //add adhoc profile for scan
        switch(apCmd->SecType)
        {
            case WLAN_SEC_TYPE_P2P_PBC:
                gAdHocProfile_ull.p2pProfile = P2P_PUSH_BUTTON;
                gAdHocProfile_ull.profile.secType = CME_SEC_TYPE_WPS_PBC;
                break;

            case WLAN_SEC_TYPE_P2P_PIN_KEYPAD:
                gAdHocProfile_ull.p2pProfile = P2P_PIN_CODE_KEYPAD;
                gAdHocProfile_ull.profile.secType = CME_SEC_TYPE_WPS_PIN;
                if (apCmd->PasswordLen != 0)
                {
                    //now copy PIN password - used for PIN_K /PIN_D
                    //Note: it's assumed that app has validated the PIN
                    //Note2: a P2P PIN is a 8 digit long number!

                    //clear before copy
                    os_memset(pDevDrv->p2pPin, 0, P2P_PIN_CODE_LEN);
                os_memcpy(pDevDrv->p2pPin, PASSWORD_STRING(apCmd), P2P_PIN_CODE_SIZE);
                //convertAsciiString2Hex((int8_t *)pDevDrv->p2pPin, PASSWORD_STRING(apCmd), P2P_PIN_CODE_LEN);
                }
                break;
            
            case WLAN_SEC_TYPE_P2P_PIN_DISPLAY:
                gAdHocProfile_ull.p2pProfile = P2P_PIN_CODE_DISPLAY;
                gAdHocProfile_ull.profile.secType = CME_SEC_TYPE_WPS_PIN;
                if (apCmd->PasswordLen != 0)
                {
                    //now copy PIN password - used for PIN_K /PIN_D
                    //Note: it's assumed that app has validated the PIN
                    //Note2: a P2P PIN is a 8 digit long number!

                    //clear before copy
                    os_memset(pDevDrv->p2pPin, 0, P2P_PIN_CODE_LEN);
                os_memcpy(pDevDrv->p2pPin, PASSWORD_STRING(apCmd), P2P_PIN_CODE_SIZE);
                }
                break;

            default:
                ASSERT_GENERAL(0);
                break;

        }

        IRQ_UtilCopyMacAddress(apCmd->Bssid, pDevDrv->p2pPeerAddr);
        GTRACE(GRP_CME, "CME: Peer mac=%x:%x:%x:%x:%x:%x", 
                            apCmd->Bssid[0], apCmd->Bssid[1],apCmd->Bssid[2],apCmd->Bssid[3],apCmd->Bssid[4],apCmd->Bssid[5]);
        gAdHocProfile_ull.uniqueProfileId = getUniqueProfileId();
	    gAdHocProfile_ull.profile.ssid_len = 0;

        //about to find the peer candidate
        pDevDrv->p2pPeerCandidateIsFound = 0;
        // now we finally call p2p_find()
    cmeStartP2pFind(wpas, NULL, CME_P2P_CONNECTION_FIND_TIMEOUT, FALSE);

}
#endif // TI_STA_ONLY_BUILD

#ifndef TI_STA_ONLY_BUILD
/* ----------------------------------------------------------------------------
 cmeP2pConnect

 Description: This function calls for suplicant to perform p2p_connect()

 Parameters: 	apPriv - driver context

 Returns: None

---------------------------------------------------------------------------- */
void cmeP2pConnect(void *apPriv)
{
    int32_t ret = 0;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    struct wpa_supplicant *wpa_s = pDrv->wpa_s;
    enum p2p_wps_method wps_method = WPS_PBC;
    u8 addr[ETH_ALEN] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    char *pin = NULL; //PIN to use during provisioning or %NULL to indicate PBC mode
                      //enum p2p_wps_method wps_method = 3; //WPS_PBC;
    int new_pin;
    int persistent_group = 0;
    int persistent_id = -1;   // generate new values (SSID/passphrase)
    int auto_join = 0;        //Whether to select join vs. GO Negotiation automatically
    int join = 0;
	int auth = 0;
	int go_intent = -1; //-1 to use default
    if (cme_is_sta_role_like_activated())
    {
        go_intent = 15; // STA+P2P_CL is unsupported; maximize our GO intent to avoid client outcome
        GTRACE(GRP_CME, "CME: cmeP2pConnect: STA role active - forcing go_intent=15");
        CME_PRINT_REPORT("\r\nCME: cmeP2pConnect: STA role active - go_intent forced to 15");
    }
	int freq = 0; // frequency for the Group or 0 for auto-selection
	int pd = 0; // Whether to send Provision Discovery prior to GO Negotiation as an
                // interoperability workaround when initiating group formation
                // when there is aGO -> pd = 1 may be needed
	int ht40=0, vht=0, max_oper_chwidth =0 , chwidth = 0, freq2 = 0;
	int edmg = 0;
	int he = 0;
	bool allow_6ghz = false;


    //copy a desired peer macAddr from roleDB
    IRQ_UtilCopyMacAddress(pDrv->p2pPeerAddr, addr);
    CME_PRINT_REPORT("\r\nCME: P2P try to connect to bssid: %x:%x:%x:%x:%x:%x", 
                            addr[0], addr[1],addr[2],addr[3],addr[4],addr[5]);
    
    //set frequency for the group channel (relevant in case of GO)
    pDrv->p2pChannel = cfgGetP2pOperChannel();

    freq = ieee80211_chan_to_freq(NULL, cfgGetP2pOperRegClass(), pDrv->p2pChannel);
    if (freq < 0)
    {
        GTRACE(GRP_CME, "CME: WARNING freq=%d, will auto select", freq);
        freq = 0; //for auto-selection
    }

    //set wps method for connection
    switch(pDrv->p2pWpsMethod)
    {
        case WLAN_SEC_TYPE_P2P_PBC:
           wps_method = WPS_PBC;
           break; 
        
        case WLAN_SEC_TYPE_P2P_PIN_KEYPAD:
            wps_method = WPS_PIN_KEYPAD;
            pin = (char*)pDrv->p2pPin;
            break;

        case WLAN_SEC_TYPE_P2P_PIN_DISPLAY:
            wps_method = WPS_PIN_DISPLAY;
            pin = (char*)pDrv->p2pPin;
            break;
            
        default:
            GTRACE(GRP_CME, "CME: ERROR - Bad wps_method!!!");
            ASSERT_GENERAL(0);
            break;
    }

    join = pDrv->p2pCapabGroupOwnerBit;

    GTRACE(GRP_CME, "CME: call P2P connect. roleId=%d, roleType=%d freq=%d, auto join=%d, join=%d, pd=%d, pDrv->p2pChannel=%d isbitset=%d", 
            pDrv->roleId, pDrv->roleType, freq, auto_join, join, pd, pDrv->p2pChannel, pDrv->p2pCapabGroupOwnerBit);
    CME_PRINT_REPORT("\r\nCME: call P2P connect. roleId=%d, roleType=%d freq=%d, auto join=%d, join=%d, pd=%d, pDrv->p2pChannel=%d isbitset=%d", 
            pDrv->roleId, pDrv->roleType, freq, auto_join, join, pd, pDrv->p2pChannel, pDrv->p2pCapabGroupOwnerBit);

    new_pin = wpas_p2p_connect(wpa_s, addr, pin, wps_method,
				   persistent_group, auto_join, join,
				   auth, go_intent, freq, freq2, persistent_id,
				   pd, ht40, vht, max_oper_chwidth, he, edmg,
				   NULL, 0, allow_6ghz);

    CME_SET_WPS_AD_HOC_CONNECTION(); //Mark the ad hoc is WPS so the next scan will be for WPS networks
    GTRACE(GRP_CME, "CME: after call P2P wpas_p2p_connect: CME_SET_WPS_AD_HOC_CONNECTION");
}
#endif // TI_STA_ONLY_BUILD

#ifndef TI_STA_ONLY_BUILD
void cmeP2pClearAll()
{
    struct wpa_supplicant *wpa_s = NULL;
    ti_driver_ifData_t *pDrv = NULL;

    gCmeP2pInfo.p2pConnectPending = FALSE;

    wpa_s = drv_getP2pDeviceSupplicant();
    if (wpa_s == NULL)
    {
        CME_PRINT_REPORT("\n\r Note: No p2p device role is active");
        return;
    }

    pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    pDrv->p2pConnectionStarted = FALSE;
    memset(pDrv->p2pPeerAddr, 0, 6);
    pDrv->p2pPeerCandidateIsFound = 0;
    pDrv->p2pCapabGroupOwnerBit = 0;

}
void cmeP2pGroupRemove()
{
    uint32_t roleId;
    struct wpa_supplicant *wpa_s = NULL;
    ti_driver_ifData_t *pDrv = NULL; 
    p2pGroupRoleType_e p2pGroupRole = CmeGetP2pGroupRoleType();
    uint8_t allowRemoveGroup = FALSE;

    switch(p2pGroupRole)
    {
        case NOT_IN_GROUP:
        {
            GTRACE(GRP_CME, "CME: No Group is formed!!!");
            CME_PRINT_REPORT("\r\n CME: No Group is formed!!!");

            //Maybe negotiation in process - try to get role device
            wpa_s = drv_getP2pDeviceSupplicant();
            if (wpa_s != NULL)
            {
                allowRemoveGroup = TRUE;
            }
            else
            {
                allowRemoveGroup = FALSE;
            }
        }
        break;
        case CLIENT_IN_GROUP:
        {
            roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_P2P_CL);
            if (roleId != INVALID_ROLE_ID)
            {
                wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);
                allowRemoveGroup = TRUE;
            }
            else
            {
                CME_PRINT_REPORT_ERROR("\r\n CME: P2P CL Role ID is NONE!!!");
                ASSERT_GENERAL(0);
            }
        }
        break;
        case GO_IN_GROUP:
        {
            roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_P2P_GO);
            if (roleId != INVALID_ROLE_ID)
            {
                wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);
                allowRemoveGroup = TRUE;
            }
            else
            {
                CME_PRINT_REPORT_ERROR("\r\n CME: P2P GO Role ID is NONE!!!");
                ASSERT_GENERAL(0);
            }
        }
        break;
        default:
            break;
    }

    if ((wpa_s != NULL) && (allowRemoveGroup))
    {
        int ret;
        pDrv = (ti_driver_ifData_t *)wpa_s->drv_priv;
    
        //clean all flags
        cmeP2pClearAll();
        //call p2p group remove
        ret = wpas_p2p_group_remove(wpa_s, wpa_s->ifname);
        if (ret < 0)
        {
            CME_PRINT_REPORT("\r\n [role:%d] Group Removed Command returned -1. \r\nGroup was not formed but group command arrive.\r\n",
                       pDrv->roleType);

            if (pDrv != NULL)
            {
                CmeP2pGroupRemovedNotify(pDrv->roleType);                
            }
            else
            {
                CME_PRINT_REPORT_ERROR("\r\nERROR: pDrv is NULL!");
            }
        }
    }
    else
    {
        GTRACE(GRP_CME, "CME: No Group is formed!!!");
        CME_PRINT_REPORT("\r\n CME: No Group is formed!!!");
    }

}
#endif // TI_STA_ONLY_BUILD

#ifndef TI_STA_ONLY_BUILD
void cmeP2pListen()
{
    uint32_t roleId;
    struct wpa_supplicant *wpa_s = NULL;
    ti_driver_ifData_t *pDrv = NULL;
    ti_driver_ifData_t *pDevDrv = drv_getDriverData(NETIF_NAME(TIWLAN_DEV_NAME_P2PDEV));
    struct wpa_supplicant *wpas = NULL;
    wpas = pDevDrv->wpa_s;
    wpas_p2p_listen(wpas, 0);
}
void cmeP2pCancel()
{
    ti_driver_ifData_t *pDevDrv = drv_getDriverData(NETIF_NAME(TIWLAN_DEV_NAME_P2PDEV));
    struct wpa_supplicant *wpas = NULL;
    int retVal;

    wpas = pDevDrv->wpa_s;
    retVal = wpas_p2p_cancel(wpas);
    if (retVal < 0)
    {
        CME_PRINT_REPORT_ERROR("\r\n CME WARN: P2P cancel return %d - No ongoing group formation", retVal);
    }
}
#endif /* TI_STA_ONLY_BUILD */

#ifndef TI_STA_ONLY_BUILD
void cmeP2pGroupAdd(const char *ssidPostfix, int32_t freq)
{
    int ret;
    int persistent = 0; /* Not supported - optional in cert.*/
    size_t postfixLen;
    struct wpa_supplicant *wpa_s = drv_getP2pDeviceSupplicant();

    if (wpa_s == NULL)
    {
        CME_PRINT_REPORT_ERROR("\r\n CME: cmeP2pGroupAdd - no P2P device wpa_s");

        return;
    }

    GTRACE(GRP_CME, "CME: cmeP2pGroupAdd ssidPostfix=%s freq=%d", ssidPostfix, freq);
    CME_PRINT_REPORT("\r\n CME: cmeP2pGroupAdd ssidPostfix=%s freq=%d", ssidPostfix, freq);

    /* Set or clear the SSID postfix in the P2P module before forming the group */
    if ((ssidPostfix != NULL) && (ssidPostfix[0] != '\0'))
    {
        postfixLen = strlen(ssidPostfix);
        p2p_set_ssid_postfix(wpa_s->global->p2p, (const u8 *)ssidPostfix, postfixLen);
    }
    else
    {
        p2p_set_ssid_postfix(wpa_s->global->p2p, NULL, 0);
    }

    ret = wpas_p2p_group_add(wpa_s, persistent, freq, 0, 0, 0, 0, 0, 0, false);

    if (ret < 0)
    {
        CME_PRINT_REPORT_ERROR("\r\n CME: cmeP2pGroupAdd failed ret=%d", ret);
    }
}
#endif

int32_t  extSetSecurityParams(CMEWlanAddGetProfile_t *apCmd,
                                _cme_minimized_wpa_ssid_t       *apSsid,
                                int8_t                  *apPassword)
{
    return setSecurityParams(apCmd,
                             apSsid,
                             apPassword);
}
