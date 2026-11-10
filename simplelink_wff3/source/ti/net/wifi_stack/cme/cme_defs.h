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

  FILENAME:       cme_defs.h

  DESCRIPTION:    CME private definitions

  HISTORY:
                 04/15 - Creation

  ----------------------------------------------------------------------------- */
#ifndef _CME_DEFS_H_
#define _CME_DEFS_H_

#include "common.h"
#include "config_ssid.h"
#include "eap_peer/eap.h"
#include "wlan_if.h"


// #define CME_LOG_REPORT
#ifdef CME_LOG_REPORT
#define CME_PRINT_REPORT Report
#define CME_PRINT_REPORT_ERROR Report
#else
#define CME_PRINT_REPORT(...)
#define CME_PRINT_REPORT_ERROR Report
#endif

//#define CME_LOG_STATE_CHANGE_REPORT
#ifdef CME_LOG_STATE_CHANGE_REPORT
#define CME_PRINT_STATE_CHNGE_REPORT Report
#else
#define CME_PRINT_STATE_CHNGE_REPORT(...)
#endif


// #define CME_ROLE_LOG_REPORT
#ifdef CME_ROLE_LOG_REPORT
#define CME_ROLE_PRINT_REPORT Report
#define CME_ROLE_PRINT_ERROR_REPORT Report
#else
#define CME_ROLE_PRINT_REPORT(...)
#define CME_ROLE_PRINT_ERROR_REPORT Report
#endif


// #define CME_CONNECT_LOG_REPORT
#ifdef CME_CONNECT_LOG_REPORT
#define CME_CON_PRINT Report
#define CME_CON_PRINT_ERROR Report
#else
#define CME_CON_PRINT(...)
#define CME_CON_PRINT_ERROR Report
#endif

//#define CME_CC3XX_PORT_LOG_REPORT
#ifdef CME_CC3XX_PORT_LOG_REPORT
#define CME_CC3XX_PORT_PRINT Report
#define CME_CC3XX_PORT_PRINT_ERROR Report
#else
#define CME_CC3XX_PORT_PRINT(...)
#define CME_CC3XX_PORT_PRINT_ERROR Report
#endif


//#define CME_CC3XX_EVENT_LOG_REPORT
#ifdef CME_CC3XX_EVENT_LOG_REPORT
#define CME_CC3XX_EVENT_PRINT Report
#define CME_CC3XX_EVENT_PRINT_ERROR Report
#else
#define CME_CC3XX_EVENT_PRINT(...)
#define CME_CC3XX_EVENT_PRINT_ERROR Report
#endif


// #define CME_LOG_SCAN_REPORT
#ifdef CME_LOG_SCAN_REPORT
#define CME_PRINT_SCAN_REPORT Report
#define CME_PRINT_SCAN_REPORT_ERROR Report
#else
#define CME_PRINT_SCAN_REPORT(...)
#define CME_PRINT_SCAN_REPORT_ERROR Report
#endif

//#define CME_LOG_SCAN_DEBUG_REPORT
#ifdef CME_LOG_SCAN_DEBUG_REPORT
#define CME_PRINT_SCAN_DEBUG_REPORT Report
#define CME_PRINT_SCAN_DEBUG_REPORT_ERROR Report
#else
#define CME_PRINT_SCAN_DEBUG_REPORT(...)
#define CME_PRINT_SCAN_DEBUG_REPORT_ERROR Report
#endif

//#define CME_LOG_ROC_REPORT
#ifdef CME_LOG_ROC_REPORT
#define CME_PRINT_ROC_REPORT Report
#define CME_PRINT_ROC_REPORT_ERROR Report
#else
#define CME_PRINT_ROC_REPORT(...)
#define CME_PRINT_ROC_REPORT_ERROR Report
#endif

// #define CME_LOG_PROFILE_REPORT
#ifdef CME_LOG_PROFILE_REPORT
#define CME_PRINT_PROFILE_REPORT Report
#define CME_PRINT_PROFILE_REPORT_ERROR Report
#else
#define CME_PRINT_PROFILE_REPORT(...)
#define CME_PRINT_PROFILE_REPORT_ERROR Report
#endif

//#define CME_ENT_LOG_REPORT
#ifdef CME_ENT_LOG_REPORT
#define CME_ENT_PRINT_REPORT Report
#define CME_ENT_PRINT_REPORT_ERROR Report
#else
#define CME_ENT_PRINT_REPORT(...)
#define CME_ENT_PRINT_REPORT_ERROR Report
#endif

//#define CME_LOG_STATE_CHANGE_REPORT
#ifdef CME_LOG_STATE_CHANGE_REPORT
#define CME_PRINT_STATE_CHNGE_REPORT Report
#else
#define CME_PRINT_STATE_CHNGE_REPORT(...)
#endif


// --------------------------
// CME configurations
// --------------------------

// Debug only - open to enable logs of memory state, printed for every role removal.
//#define CME_MEM_ESTIMATION

// Maximal number of scan results in digest format
#define CME_SCAN_MAX_DIGEST_RESULTS    (18)

// Number of scan results required for connection scan; scan module selects
// the best result (based on profile prioirty, security type, RSSI)
#define CME_SCAN_MAX_CANDIDATES			(1)

// Max number of scan results for WPS/P2P/MBO scan
//#define CME_SCAN_WPS_P2P_MBO_MAX_CANDIDATES     (32) //( NOTE: this will consume 25856 bytes per each scan result !!!)
#define CME_SCAN_WPS_P2P_MBO_MAX_CANDIDATES     (18)

// Size of memory buffer allocated for connection candidates
#define CME_CONNECTION_SCAN_MEM_SIZE	(CME_SCAN_MAX_CANDIDATES*sizeof(cmeScanCandidateDesc_t))

// Maximal number of profiles.
#define CME_SCAN_MAX_PROFILES           (WLAN_MAX_PROFILES)

// Maximum number of supported scan plans for scheduled scan, supported by the driver
#define CME_SCAN_MAX_SCHED_SCAN_PLANS           (12)

// Maximum interval in a scan plan, that supported by the driver (In seconds)
#define CME_SCAN_MAX_SCHED_SCAN_PLAN_INTERVAL   (4096)

// Maximum number of iterations in a single scan plan, that is suported by the driver
#define CME_MAX_SCHED_SCAN_PLAN_ITERATION       (255)

// currently supporting maximum 1 ENT in the system (ad hoc and preferred together)
#define CME_MAX_EAP_ENTRIES             (1)

// When set, periodic scan uses unicast probe requests.
// When cleared, wildcard probe requests are used.
#define CME_ALL_PROFILES_ARE_HIDDEN		(1)

// Size (in bytes) of the flash element holding WLAN configuration
#define CME_WLAN_FLASH_ELEMENT_SIZE  (sizeof(cmeWlanConfigFlashElement_t))


#define CME_BW_MAX_MAC_ENTRIES          (16)
#define CME_BW_LIST_MAX_SIZE            (CME_BW_MAX_MAC_ENTRIES * MAC_ADDR_LEN) //// Max size (in bytes) of the B/W MAC list
#define CME_BW_MAX_WILDCARD_ENTRIES     (2)
#define CME_BW_WILDCARD_MASK_LEN        (6)
#define CME_BW_LIST_TYPE_MAC            (0)
#define CME_BW_LIST_TYPE_WILDCARD       (1)



// Imported from cc3100 R2 (V61)
#define WPA_MAX_PASSPHRASE_LEN    (64)
#define WEP40_ASCII_KEY_LENGTH     (5)
#define WEP40_HEX_KEY_LENGTH      (10)
#define WEP104_ASCII_KEY_LENGTH   (13)
#define WEP104_HEX_KEY_LENGTH     (26)
#define WPA_HEX_PASSPHRASE_LENGTH (64)
#define WPA_HEX_MIN_PASSPHRASE_LENGTH (8)

#define WPS_PIN_LEN         (8)
#define WPS_PIN_STR_LEN     (WPS_PIN_LEN + 1)  // +1 for null termination

// P2P profile definitions
// Pin code length is taken from cc3100 documentation
#define P2P_PIN_CODE_LEN     (8)    // Null termination location
#define P2P_PIN_CODE_SIZE    (9)    // Array size

//preffered networks define
#define WLAN_DEL_ALL_PROFILES       (0xff)

#define CME_INVALID_PROFILE_ID        (-1)

#define CME_INVALID_ENT_IDX (0xFF)

//connection blakclist threshold
#define MAX_JOIN_RETRIES         2
#define CLEAR_BLACK_LIST_CONSEQ_SCAN_COMPLETES 8
#define CONN_ATTEMPT_INVALID_CTR 0xFF
#define CONN_ATTEMPT_INVALID_IDX 0xFF

//default cipher suites for WPA
//#define CME_WPA_DEFAULT_CIPHER (WPA_CIPHER_CCMP | WPA_CIPHER_TKIP)
#define CME_AP_WPA_DEFAULT_CIPHER (WPA_CIPHER_CCMP)
#define CME_STA_WPA_DEFAULT_CIPHER (WPA_CIPHER_CCMP | WPA_CIPHER_TKIP)
#define CME_STA_WPA2_AES_ONLY_DEFAULT_CIPHER (WPA_CIPHER_CCMP)
#define CME_AP_WPA_SAE_PWE_H2E_AND_HUNTING_AND_PECKING (2) //both hunting-and-pecking loop and hash-to-element enabled


#define    _CME_THR_NAME                    "CmeThread"
#define     CME_THR_IDX                     CME_THR_IDX
#define     CME_THR_NAME                    M_THREAD_NAME(CME_THR_IDX)
#define     CME_THR_STACK_SIZE              ((1024 * 7) + 256) //Was 1024*5,was not enough (1024*10)
#define     CME_THREAD_PRIORITY                (8)

//import from eap config
#define MAX_USER_LEN 32
#define MAX_ANON_LEN 32
#define MAX_PASS_LEN 32
#define MAXIMAL_SSID_LENGTH                     (32)
#define MAXIMAL_PASSWORD_LENGTH                 (64)

// Used to differentiate P2P Profile values to indicate P2P Stored Profile
// (meaning SSID=REMOTE_DEVICE_NAME when connecting)
#define WPAS_SSID_IS_P2P_PROFILE(p2pProfile) (p2pProfile > P2P_NONE)

typedef enum
{
    P2P_NONE            =  0,
    P2P_PUSH_BUTTON     =  1,
    P2P_PIN_CODE_KEYPAD =  2,
    P2P_PIN_CODE_DISPLAY = 3
} p2pProfile_e;


// Hold probe request extra IEs location and size
typedef struct
{
    uint8_t  *pExtraIesBuffer;
    uint32_t extraIesLength;
} ProbeRequestInfo_t;



// hold connection policy information:
typedef struct {
    /* Note: this structure is used to store information in Flash
     - Please DO NOT change the legacy fields.*/
    uint8_t shouldConnectToOpenAp; // not suppoted
    uint8_t shouldConnectToAnyP2P; // not supported
    uint8_t shouldUseFastConnect;
    uint8_t autoStart;
    uint8_t fastPersistent;        // either to store fast frame into flash or not
    uint8_t padding[3];
} CmeConnectionPolicyParams_t;




typedef struct
{
    /* Note: this structure is used to store information in Flash
     - Please DO NOT change the legacy fields.*/
        //EAP parameters
        struct eap_method_type* eap_method;
        uint32_t   num_of_eap_methods;

        uint8_t     eap_entProfileIndex;
        int32_t     fragment_size;
        uint8_t     *ca_cert;
        uint8_t     *client_cert;
        uint8_t     *private_key;
        uint32_t    client_cert_len;
        uint32_t    ca_cert_len;
        uint32_t    private_key_len;
        uint8_t     identity[MAX_USER_LEN];
        uint8_t     Anonymous[MAX_ANON_LEN];
        size_t      identity_len;
        size_t      anonymous_identity_len;
        char        *phase1;
        char        *phase2;
        uint32_t    flags;
        uint8_t     password[MAX_PASS_LEN];
        size_t      password_len;
        uint8_t     *client_cert2;
        uint8_t     *ca_cert2;
        uint8_t     *private_key2;
        char        *pac_file;
}_cme_minimized_wpa_ssid_eap_t;

typedef struct
{
    /* Note: this structure is used to store information in Flash
     - Please DO NOT change the legacy fields.*/
        int id;
        uint8_t  ssid[SSID_MAX_LEN];
        size_t ssid_len;
        char *passphrase;
        u8  secType; // Security type as set by the user (scan module uses security type and not key_mgm (as before) since it does not contain all the needed information (i.e. wep, in which key mgmt is none))
        int key_mgmt;
        u8 bssid[ETH_ALEN];
        int priority;
        int auth_alg;
        int scan_ssid;
        int eapol_flags;
        unsigned int eap_workaround;
        int pairwise_cipher;
        int group_cipher;
        int proto;
        size_t wep_key_len[NUM_WEP_KEYS];
        int disabled;
        enum wpas_mode mode;
        int bssid_set;
        u8 psk[32];
        int psk_set;
        int wep_tx_keyidx;
        u8 wep_key[NUM_WEP_KEYS][MAX_WEP_KEY_LEN];
#ifdef CONFIG_IEEE80211W        
        int group_mgmt_cipher;
        enum mfp_options ieee80211w;
#endif
        //EAP parameters
        _cme_minimized_wpa_ssid_eap_t eap;
        //int isSuiteb192; // this variable was moved to eapol flags in order to preserve backward compatibility
}_cme_minimized_wpa_ssid_t;

// Hold profiles information: profile as received from user application + management information

// WPA3 cache 
#define CME_PMKID_LEN      (16)
#define CME_PMK_LEN_MAX    (64)
typedef struct 
{
    /* Note: this structure is used to store information in Flash
     - Please DO NOT change the legacy fields.*/
    uint8_t pmkid_set;
    uint8_t pmkid [CME_PMKID_LEN];
    uint8_t pmk [CME_PMK_LEN_MAX];
    uint8_t pmk_len;
    uint8_t bssid [ETH_ALEN];
    int     key_mgmt;
} _cme_wpa_pmkid_params_t;


typedef struct
{
    /* Note: this structure is used to store information in Flash
     - Please DO NOT change the legacy fields.*/
    _cme_minimized_wpa_ssid_t profile;                   // Holds peer information
    //uint8_t                     ssid[SSID_MAX_LEN];
    p2pProfile_e              p2pProfile;                  // Indicates if profile is for P2P;
                                                 // if it is holds connection type
    char                      p2p_pin[P2P_PIN_CODE_SIZE];  // p2p pin code (in case of P2P_PIN)

    int8_t                    uniqueProfileId;             // Unique profile ID, assigned when
                                                 // profile is added.
                                                 // For unused profile ID is CME_INVALID_PROFILE_ID

    _cme_wpa_pmkid_params_t   pmkid_params;

#ifdef SIMULATE_NO_SCAN_RESULTS
    uint32_t          numWrongSsid;                // Debug only, force scan failure
#endif
} cmeProfileInfo_t;

//Hold ENT security related parameters, for each  cmeProfileInfo_t that is type ENT
typedef struct
{
    uint8_t       is_in_use;
    //eapol profile parameters
    //TODO: , supplicant expects to get a list of all supported TLS methods. Also, server can support multiple tls methods.
    //For now we save only one (?), needs to be changed.
    struct eap_method_type eap_method;
    //3 arrays in size of 32 which holds the user name, anonymous name and password (in case of Enterprise only)
    u8 Identity[MAX_USER_LEN];
    u8 Anonymous[MAX_ANON_LEN];
    u8 Password[MAX_PASS_LEN];
}cmeEntProfileParams_t;


typedef struct
{
    // When changing this structure, make sure init values of
    // gDefaultWlanParameters are properly aligned.
    u8  Ssid[MAXIMAL_SSID_LENGTH + 1];
    u8  SsidLen;
    u8  Password[MAXIMAL_PASSWORD_LENGTH + 1];
    u8  PasswordLen;
    u8  SecurityType;
    u8  Channel;
    u8  Hidden;
    u8  ApMaxNumOfStations;
    u16 ApMaxStaAging;
    u8  ApTxPowerLevel;
    u8  StaTxPowerLevel;
    u8  CountryCode[3];   // US / JP / EU
    u8  P2pDeviceType[17];
    u8  P2pListenChannel;
    u8  P2pListenRegClass;
    u8  P2pOperChannel;
    u8  P2pOperRegClass;
    u32 ScanChannelGbandMask;
    u32 ScanChannelAbandMask;
    u8  ScanChannelJbandMask;
    s32 ScanRssiThreshold;
}cmeWlanConfigFlashElement_t;


typedef struct
{
    u8  ListMode;
    u8  macListNumEntries;
    u8  wildcardListNumEntries;
}BwListHeader_t;


typedef struct
{
    u8  Id;
    u8  Oui[3];
    u16 Length;
    u16 ElementOffset;
}PrivateIeHeader_t;

typedef struct
{
    uint8_t macAddr[6];

}BwList_macEntry;

typedef struct
{
    uint8_t macAddr[6];
    u8 mask[CME_BW_WILDCARD_MASK_LEN];

}BwList_wildcardEnry;

typedef struct
{
    PrivateIeHeader_t   PrivatInfoElementHeader[8]; // One for each element
    u8                  PrivatInfoElement [300+160]; // 300 bytes for AP + 160 bytes for P2P
    BwListHeader_t      ApBwListHeader;
    u8                  ApBwMacList [CME_BW_MAX_MAC_ENTRIES * sizeof(BwList_macEntry)]; // (16 MAC addresses) x 6 bytes
    u8                  ApBwWildcardList [CME_BW_MAX_WILDCARD_ENTRIES * sizeof(BwList_wildcardEnry)]; //2 wildcard x 12 bytes (MAC + MASK)
}cmePrivateIeAndBwListFlashElement_t;

typedef struct
{
    BwListHeader_t          Header;
    BwList_macEntry*        pMacList;
    BwList_wildcardEnry*    pWildcardList;

}cmeBwListCB_t;

typedef struct
{
    PrivateIeHeader_t   Header[8];
    u8*                 pElements[8];
}cmePrivateIeCB_t;

typedef enum
{
    NOT_IN_GROUP = 0,
    CLIENT_IN_GROUP,
    GO_IN_GROUP
} p2pGroupRoleType_e;

#define CME_SIGNAL_ROLE_CHNGE_STATUS_OK      (0)
#define CME_SIGNAL_ROLE_CHNGE_STATUS_FAILED  (-1)
#define CME_SIGNAL_ROLE_CHNGE_STATUS_TIMEOUT (-2)

typedef struct
{
    uint8_t cme_signalWhenRoleStateChanged;
    int32_t cme_signalWhenRoleStateChanged_status;
}signal_role_change_state_done_t;

#endif // _CME_DEFS_H_
