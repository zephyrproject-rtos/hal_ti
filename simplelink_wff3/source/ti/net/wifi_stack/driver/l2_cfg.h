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

  FILENAME:       l2_cfg.h

  DESCRIPTION:    L2 configuration module, contains configurable L2 parameters.
                  The module is responsible for setting default values based on
                  static, hard coded values as well as ini files when available.
                  It is also responsible for updating configuration dynamically
                  during WLAN connection, based on peer capabilities.

  HISTORY:
                 09/15 - Creation

  ----------------------------------------------------------------------------- */
#ifndef _L2_CFG_H_
#define _L2_CFG_H_
#include "utils/common.h"
#include "rates.h"
#include "802_11defs.h"
#include "wpa_supplicant/config.h"
#include "wlan_if.h"

// add struct\define start -----------------------------------------------------------------------------
#if 1

// Disable WiFi 6 (802.11ax/HE) support at compile time
//#define DISABLE_WIFI6

/* 802.11n HT Information Element */
#define DOT11_HT_CAPABILITIES_ELE_LEN    (26)
#define DOT11_HE_CAPABILITIES_MIN_TOTAL_LEN  (22)   //Total len includes the Extension ID byte! will be the elemnt len field

/* 802.11n HT Information Element */
#define DOT11_VHT_CAPABILITIES_ELE_LEN    (sizeof(uint8_t)*12)

#define DOT11_OPERATING_MOD_NOTIF_ELE_LEN (sizeof(uint8_t))

#define  L2_CFG_BAND_ONLY_2_4GHZ (0)
#define  L2_CFG_BAND_ONLY_5GHZ   (1)
#define  L2_CFG_BAND_BOTH        (2)

typedef struct
{
   unsigned int     reserved              :8;  // Reserved for future debugs
   unsigned int     tXMode                :2;  // EDCA/trigger based/both,                                         default: both
   unsigned int     txFrag                :2;  // Level (0,1,2),                                                   default: false

   unsigned int     mngInAggregation      :1;  // Add management frame to aggregation,                             default: false
   unsigned int     qosNullInAggr         :1;  // True/False ,                                                     default: false
   unsigned int     heHeaderInHtSupp      :1;  // Enable HE header (A-CTRL) in Ht Header- true/false,              default: true
   unsigned int     moreDataBit           :1;  // Declare support in more data bit in the qos Info feild or not,   default:

}heDebugParams_t; // 2 bytes

/* TX_RATE_MANAGEMENT_RATES_OVR */
typedef struct
{
    unsigned int rateMgmOverRateValue       :5; // Rate index using RateIndex_e.
    unsigned int rateMgmOverTxPwr           :5; // MEM_RM_TX_PWR_OVR_VAL , -10 to 20 [dBm] default: 0x1E - 20db
    unsigned int rateMgmOverPreamble        :4; // MEM_RM_PREAMBLE_OVR_VAL , 0: PREAMBLE_T_B_SHORT ,1: PREAMBLE_T_B_LONG - default: 0
                                                // 2: PREAMBLE_T_AG, 3: PREAMBLE_T_N_MIXED, 4: PREAMBLE_T_N_GF, 5: PREAMBLE_T_AX_SU
                                                // 6: PREAMBLE_T_AX_MU, 7: PREAMBLE_T_AX_SU_ER, 8: PREAMBLE_T_AX_TB , 9: PREAMBLE_T_AX_TB_NDP_FB , A: PREAMBLE_T_AC_VHT
    unsigned int reserved                   :4; // Reserved for future debugs

    unsigned int rateMgmOverGiHeLtfType     :3; // MEM_RM_GI_HE_LTF_TYPE_OVR_VAL   default: 3.2 and LTF×4

    unsigned int rateMgmOverEn              :1; // 0 - HW rate management is operational. 1 - HW decision is override.
    unsigned int rateMgmOverDCM             :1; // MEM_RM_DCM_OVR_VAL, Set 1 - dual carrier modulation is used,
                                                // Set 0 - DCM is not used/ Note: DCM is only applied to MCS0, MCS1, MCS3 and MCS
    unsigned int rateMgmOverBW              :1; // Set 0 - for 242-tone RU, Set 1 - for upper frequency 106-tone RU within the primary 20 MHz.

}rateOverride_t; //3 bytes

typedef struct
{
    heDebugParams_t heParams;
    rateOverride_t  rateParams;
    uint8_t mcsPreamble;  // MEM_RM_PREAMBLE_SELECT_OVR_VAL,  In case RM selects MCS rate, this field overrides only the 11n preamble,
                      // 0: USE 11N preamble recommended by RM  (PREAMBLE_T_N_GF/PREAMBLE_T_N_MIXED) - default
                      // 1: Replace by PREAMBLE_T_AX_SU
                      // 2: Replace by PREAMBLE_T_AX_SU_ER
                      // 3: Replace by PREAMBLE_T_AC_VHT
    uint8_t heSupport;                  // Supports HE or not. true/false
    uint8_t txAmpdu;                    // True/False , default: false
    uint8_t baTxSessionSupport;         // TRUE / FALSE - (BA management)
    uint8_t baRxSessionSupport;         // TRUE / FALSE - (BA management)

    uint8_t gStaFlashMacAddress[6];     // MAC_ADDR_LEN - 6
    uint8_t gApFlashMacAddress[6];
    uint8_t gDeviceFlashMacAddress[6];
    uint8_t gTransceiverFlashMacAddress[6];
    uint8_t gIsPersistent;
    uint8_t gApiTimeoutDurationType;
    uint8_t lpdsAllowd;
    uint8_t oclaRamSize;                // 0: 0KB, 1: 32KB, 2: 64 KB, 3: 128 KB, 4: entire
    uint8_t beaconWakeup;   //0: beacon. 1 - dtim. 2 - nDtim
    uint8_t beaconWakeup_n_DtimInterval;// nDtimInterval
    uint8_t fastWakeupEnabled;          // 1 - Fast Wake up Enabled
    uint8_t flashFTLVersion[3];         // flash FTL version
    //must be aligned to 32 bits

} DeviceParams_t;

/************************************************************
 *         EXTERNAL
*************************************************************/
extern DeviceParams_t   g_DeviceParams;
#endif
// add struct\define end-----------------------------------------------------------------------------



// AMPDU capabilities - enumeration order complies with 802.11 spec
typedef enum
{
    AMPDU_SPC_NO_RESTRCITION =  0,  // No Restriction on AMPDU Time Spacing
    AMPDU_SPC_1_4_MICROSECONDS,     // 1/4 usecs
    AMPDU_SPC_1_2_MICROSECONDS,     // 1/2 usecs
    AMPDU_SPC_1_MICROSECOND,        // 1 usecs
    AMPDU_SPC_2_MICROSECONDS,       // 2 usecs
    AMPDU_SPC_4_MICROSECONDS,       // 4 usecs
    AMPDU_SPC_8_MICROSECONDS,       // 8 usecs
    AMPDU_SPC_16_MICROSECONDS       // 16 usecs
} AMPDUSpacing_e;

typedef enum
{
    MAX_MPDU_8191_OCTETS,                   // 8191
    MAX_MPDU_16383_OCTETS,                  // 16383
    MAX_MPDU_32767_OCTETS,                  // 32767
    MAX_MPDU_65535_OCTETS,                  // 65535
    MAX_MPDU_MAX_VALUE = MAX_MPDU_65535_OCTETS
} AMPDUMaxSize_e;

//-----------------------------------------------------------------------------//
// Mx PG2 SystemInfo indexes: gSystemInfo index definitions, used for get/set values
//-----------------------------------------------------------------------------//
typedef enum
{
    SYSTEM_INFO_PAPER_SPIN_DISABLE_5GHZ_IDX                = 0,
    SYSTEM_INFO_PAPER_SPIN_DISABLE_6GHZ_IDX                = 1,
    SYSTEM_INFO_PAPER_SPIN_DISABLE_BLE_IDX                 = 2,
    SYSTEM_INFO_PAPER_SPIN_DISABLE_BLE_M0PLUS_IDX          = 3,
    SYSTEM_INFO_PAPER_SPIN_DISABLE_M33_IDX                 = 4,
    SYSTEM_INFO_SUPPORTED_TEMPERATURE_IDX                  = 5,
    SYSTEM_INFO_PG_VERSION_IDX                             = 6,
    SYSTEM_INFO_METAL_VERSION_IDX                          = 7,
    SYSTEM_INFO_BOOT_ROM_VERSION_IDX                       = 8,
    SYSTEM_INFO_TI_FUSE_ROM_STRUCTURE_VERSION_IDX          = 9,
    SYSTEM_INFO_MAC_ADDRESS_LOW_IDX                        = 10,
    SYSTEM_INFO_MAC_ADDRESS_HIGH_IDX                       = 11,
    SYSTEM_INFO_PART_NUMBER_IDX                            = 12,
    SYSTEM_INFO_PACKAGE_TYPE_IDX                           = 13,
    SYSTEM_INFO_GPADC_OFFSET_IDX                           = 14,
    SYSTEM_INFO_OTP_STRUCTURE_VERSION_IDX                  = 15,
    SYSTEM_INFO_VENDOR_RESTRICTED_INI_IDX                  = 16,
    SYSTEM_INFO_CRDA_CODE_IDX                              = 17,
    SYSTEM_INFO_CRDA_CODE_ENABLE_IDX                       = 18,
    SYSTEM_INFO_MAC_ADDRESS_OV_LOW_IDX                     = 19,
    SYSTEM_INFO_MAC_ADDRESS_OV_HIGH_IDX                    = 20,
    SYSTEM_INFO_WIFI6_DISABLE_IDX                          = 21,
    SYSTEM_INFO_CONF_KEY_IDX                               = 22,
    SYSTEM_INFO_WORLDWIDE_RESTRICTION                      = 23,
    SYSTEM_INFO_COUNTRY_CODE                               = 24,
    SYSTEM_INFO_PMCIO_TEMPERATURE_SENSOR_1ST_INSERTION_IDX = 25,
    SYSTEM_INFO_PMCIO_TEMPERATURE_SENSOR_2ND_INSERTION_IDX = 26,
    SYSTEM_INFO_RFCIO_TEMPERATURE_SENSOR_1ST_INSERTION_IDX = 27,
    SYSTEM_INFO_RFCIO_TEMPERATURE_SENSOR_2ND_INSERTION_IDX = 28,
    SYSTEM_INFO_PA_LDO_IN_MONITOR_IDX                      = 29,

    SYSTEM_INFO_MAX_IDX                                    = 62

}SystemInfoIdx_e;

#define RX_MCS_BITMASK_SIZE                      (10)
#define RX_HIGHEST_SUPP_DATA_RATE_BM_SIZE        (2)

#define FRAG_THRESHOLD_MAX          4096
#define FRAG_THRESHOLD_DEFUALT      2352

#define MAX_TX_RETRIES_THRESHOLD_DEFAULT_STA    (50)  
#define MAX_TX_RETRIES_THRESHOLD_DEFAULT_AP     (100) 

#define SECOND_CHANCE_TX_TIMER_PERIOD_STA_USEC  (1000000)
#define SECOND_CHANCE_TX_TIMER_PERIOD_AP_USEC   (1000000)

#define AP_DEFAULT_MAX_NUM_OF_STATIONS          (4)
#define AP_DEFAULT_CHANNEL_NUMBER               (1)
#define AP_DEFAULT_MAX_STA_AGING                (300)

#define WPS_OS_VERSION_LEN  4

// From MCP for AP role
// ========================================================

//typedef struct
//{
//    uint8_t                        uBeaconTxTimeout;   // in mSecs, #define ROLE_AP_BEACON_TX_TIMEOUT_DEF     20, used for beaconExpiry in RoleStartBssOwnerParameters_t when starting AP role
//    EDot11Mode                   eDesiredDot11Mode;  // set to dual mode, looks like it isn't used
//    TArpIpFilterInitParams       tArpIpFilter;       // ARP filter configuration
//    TMacAddrFilterInitParams     tMacAddrFilter;     // MAC filter configuration
//
//    uint8_t                        aBaPolicy[MAX_NUM_OF_802_1d_TAGS];          // Both initiator and Rx BA policy, default is enable both just for TID0.
//    uint16_t                       aBaInactivityTimeout;                       // Initiator inactivity timeout, defalt: #define  HT_BA_INACTIVITY_TIMEOUT_DEF 10000, sent to FW using ACX_BA_SESSION_INITIATOR_POLICY when role is started
//    uint16_t                       uRtsThreshold;             // default: #define RTS_THRESHOLD_DEF   4096, sent to FW when role is enabled
//
//    RssiSnrAverageWeights_t         tWeightsParam;          // sent to FW when role is enabled
//
//    TRxTimeOut                      tRxTimeOut;             // default: #define  QOS_RX_TIMEOUT_UPSD_DEF     15
//                                                            //          #define  QOS_RX_TIMEOUT_PS_POLL_DEF  15
//                                                            // sent to FW when role is enabled, ACX_SERVICE_PERIOD_TIMEOUT
//
//}TRoleApInitParams;

//AP enable role parameters:
//
//-   MAC address
//-   Power mode (auto)
//-   Send enable role (parameters are irrelevant to cc33xx – role type & MAC address)
//-   Set default parameters using several commands:
//    o   Set rates related parameters on TBssCapabilities, nothing is sent to FW as it is sent in start role
//    o   Configure ARP address
//    o   Configure MAC filters
//    o   Set RTS threshold to FW (DOT11_RTS_THRESHOLD)
//    o   Configure RSSI weights (ACX_RSSI_SNR_WEIGHTS
//    o   Configure service period timeouts (ACX_SERVICE_PERIOD_TIMEOUT)

// AP start role parameters
//
//- ACX_PREAMBLE_TYPE -
//- ACX_SLOT - default is short slot - received from supplicant in set_ap API
//- ACX_AC_CFG -received from supplicant when interface is initialized
//- ACX_CTS_PROTECTION - received from supplicant when interface is initialized
//- DOT11_CUR_TX_PWR - based on regulatory domain
//- MAX_TX_FAILURE_THRESHOLD_CFG - default is 200, hard coded can't be changed
//- ACX_BA_SESSION_INITIATOR_POLICY - PolicyBitmap - taken from hard coded; WinSize - default, hard coded is 32;
//                                    InactivityTimeout - defalt: #define  HT_BA_INACTIVITY_TIMEOUT_DEF 10000

// CMD_ROLE_START - RoleStartParameters_t
// set security keys

// Role start parameters
//typedef struct
//{
//    uint8_t               globalHLID;     // moved to role enable
//    uint8_t               broadcastHLID;  // moved to role enable
//
//    uint16_t              beaconInterval; // received from supplicant in set_ap API
//    uint8_t               dtimInterval;   // received from supplicant in set_ap API
//    RoleSsid_t          ssid;           // received from supplicant when interface is initialized
//    Bool_e              WMM;            // received from supplicant in set_ap API
//
//    uint8_t               beaconExpiry;   // default:   #define ROLE_AP_BEACON_TX_TIMEOUT_DEF     20
//    uint8_t               bssIndex;       // 0 by default
//    EHwRateBitFiled     basicRateSet;   // hard coded to 6, 12, 24
//    EHwRateBitFiled     localSupportedRates; // hard coded to all BG rates, if HT is enabled MCS rates are added as well
//    uint8_t               resetTsf;       // hard coded, FALSE, unused by MCP & FW
//
//    uint8_t               broadcast_session_id;   // incremented in MCP for every new start role, should it be managed by FW?
//    uint8_t               global_session_id;      // should it be managed by FW?
//
//} RoleStartBssOwnerParameters_t;


// ========================================================

// A-MPDU parameters
typedef struct
{
    uint8_t          maxPackSize : 2;      // Maximum A-MPDU length exponent, 2^(13 + maxPackSize) - 1
    AMPDUSpacing_e spacing     : 3;      // Minimum time between the start of adjacent
                                         // MPDUs within an AMPDU that the STA can receive
} htAmpduCfg_t;

// MCS Set field structure acording 802.11n SPEC
typedef struct
{
    uint8_t    txSettingBM;                           // Bit mask of TX settings
    uint8_t    rxMscBitmask[RX_MCS_BITMASK_SIZE];     // Supported RX MCS rates from MCS0 to MCS76
    uint16_t   highestSupportedDataRate;              // Highest supported MCS rate in 1Mbps units
} htSuppMcsSet_t;

// HT capabilities
typedef struct
{
    htAmpduCfg_t   ampduCfg;          // (8192/16384, 8/16) Holds maximal size & spacing
    htSuppMcsSet_t suppMcsSet;        // MCS configuration as defined in spec (8.4.2.58.4 Supported MCS Set field)
    uint16_t         htCapabBM;         // Field structure complies with 802.11 HT capabilities field
    uint8_t          aselCapabilities;  // Set to 0, same as WL8
    uint16_t         extCapabilities;   // Set to 0, same as WL8
    uint32_t         txBfCapabilities;  // Set to 0, same as WL8
} htCapabilities_t;


struct ieee80211_vht_mcs_info {
	uint16_t rx_mcs_map;
	uint16_t rx_highest;
	uint16_t tx_mcs_map;
	uint16_t tx_highest;
} __PACKED__;

// VHT capabilities
typedef struct
{
	//bool vht_supported;
	u32 cap; /* use IEEE80211_VHT_CAP_ */
	struct ieee80211_vht_mcs_info vht_mcs;
} vhtCapabilities_t;

// HE capabilities
typedef struct
{
    heMacCapabilities_t         heMacCapabilities;
    hePhyCapabilities_t         hePhyCapabilities;
}heCapabilities_t;

// WPS default static parameters
typedef struct
{
    uint8_t uuid[WPS_UUID_LEN]; // Universally Unique IDentifier (UUID; see RFC 4122) of the device
    char *device_name; // User-friendly description of device (up to 32 octets encoded in UTF-8)
    char *manufacturer; // The manufacturer of the device (up to 64 ASCII characters)
    char *model_name; // Model of the device (up to 32 ASCII characters)
    char *model_number; // Additional device description (up to 32 ASCII characters)
    char *serial_number; // Serial number of the device (up to 32 characters)
    uint8_t device_type[WPS_DEV_TYPE_LEN]; // Primary Device Type (WPS)
    uint8_t os_version[WPS_OS_VERSION_LEN]; // 4-octet operating system version number
    char *config_methods; // space-separated list of supported WPS configuration methods
} wpsParameters_t;

typedef struct
{
    wpsParameters_t *wpsParams;
    Bool_e wpsDisabled;
} SupplicantCfg_t;

// P2P default static parameters
typedef struct
{
    uint8_t p2pListenRegClass;
    uint8_t p2pListenChannel;
    uint8_t p2pOperRegClass;
    uint8_t p2pOperChannel;
    uint8_t p2pGoIntent; // 0 - 15
    uint8_t p2pPersistent; // 0/1
    char *p2pSsidPostfix;
    uint32_t reserved;
} P2pParameters_t;

typedef struct
{
    P2pParameters_t *p2pParams;
    Bool_e p2pDisabled;
} P2pSupplicantCfg_t;

// Hold device default configuration
// Default values are stated in () for every parameter
typedef struct
{
    uint32_t deviceSupportedBandsBM;  // bitmask, based on RadioBand_e indicate bands capability of device,
                                      // set by INI configurations and fuses
    Bool_e iniIs5GHzEnabled;          // indicates INI user-configuration support of 5 GHz
    Bool_e iniMixedModeEnabled;       // indicates INI user-configuration support of mixed mode security type
    Bool_e dot11nEnabled;             // (TRUE) indicates device supports 11n features
    Bool_e band40MHzEnabled;          // (FALSE) indicates device supports 40MHz
    Bool_e mimoEnabled;               // (FALSE) used for adding MCS 8-15 to HT capabilities & device capabilities
    Bool_e channelWidth40MHzEnabled;  // (FALSE) support only 20MHz channels

    htCapabilities_t  htCapabilities;
    vhtCapabilities_t vhtCapabilities;
    heCapabilities_t  heCapabilities;


    uint16_t  fragThreshold;
    wpsParameters_t wpsParameters;

    heDebugParams_t heParams;
    uint8_t     heSupport;                  // Supports HE or not. true/false
} l2CfgCommon_t;



// ============================================================================
//  STA/P2P CL configuration
//     STA specific parameters or parameters which are used by both STA & AP
//     but may get different values
// ============================================================================


typedef struct
{
    Bool_e wmeEnable;              // (TRUE) may be set to FALSE for debug
                                   // affects FW - before association ACX_PEER_CAP, ACX_HT_BSS_OPERATION
                                   //            - beacon/probe response parsing - ACX_HT_BSS_OPERATION
    Bool_e trafficAdmCtrlEnable;   // (FALSE) used for adsmission request. cc33xx doesn't support TSPEC at least for a start.
    uint8_t  packetBurstEnable;      // (FALSE) used for setting TXOP limit
//    uint32_t packetBurstTxOpLimit;   // sent to FW using ACX_AC_CFG, same value is used for all ACs
    uint8_t  psPollTimeoutMS;        // Maximal time a device waits for traffic from the AP after transmission of PS-poll
    uint8_t  upsdTimeoutMS;          // Maximal time a device waits for traffic from the AP after transmission of trigger
                                   // affects FW - ACX_SERVICE_PERIOD_TIMEOUT, set after connection is established
    uint8_t ackPolicy[NUM_ACCESS_CATEGORIES];  // ack policy per AC, default is immediate ack
                                               // used for setting QOS control field in 802.11
                                               // do we really want to control it?
    AcCfg_t acCfg[NUM_ACCESS_CATEGORIES];
    Bool_e burstModeEnabled ;       // ACX_BURST_MODE, default is FALSE

    uint16_t baPolicy;                // BA policy for all TIDs, 2 bits for each packed into 16 bits
                                    // ACX_BA_SESSION_INITIATOR_POLICY
    uint16_t baInactivityTimeout;

} qosCfgSta_t;

// Hold STA specific configuration - no need to expose this in API - shall be moved to C file
typedef struct
{
    uint32_t  basicRatesBM;       // (ANY_B_RATE)
    uint32_t  supportedRatesBM;   // (ANY_RATE)
    uint32_t  rtsThreshold;       // (4096)
    uint32_t  secondChanceTxTimePeriod; // Time in usec to wait for second chance transmission after max TX retries occured.

    const char * sched_scan_default_plan; // Scan plans for scheduled scan,
                                          // format: <interval:iterations> <interval2:iterations2> ... <interval> (see config.h)

    Bool_e  shortPreamble;      // (TRUE)
    Bool_e  shortSlot;          // (TRUE)
    dot11Mode_e dot11Mode;      // (DUAL) 802.11 supported mode/modes
    uint8_t   consecutivePsPollDeliveryFailureThreshold;    // 4 ACX_BCN_DTIM_OPTIONS
    uint8_t   maxTxRetriesThreshold;  // Max TX retries threshold

    Bool_e  pmf;                      //management frame protection
    Bool_e  pbac;                   //indicates if we support pbac in case we have a pmf connection
    // ------------------------------------------------------------------------
    // The below are set by MCP/NLCP drivers in WL8.
    // Have to review and update when relevant modules code is updated
//    RssiSnrTriggerCfg_t roamingTriggersLowDir;
//    RssiSnrTriggerCfg_t roamingTriggersHighDir;
//
//    ACXBeaconFilterOptions_t        beaconFilterOptions;
//    ACXBeaconFilterIETable_t        beaconFilterTable;
//    ACXBeaconAndBroadcastOptions_t  beaconOptions;
    // ------------------------------------------------------------------------

} cfgSta_t;

typedef struct
{
    const cfgSta_t      *pStaCfg;
    const qosCfgSta_t   *pQosCfg;
    const l2CfgCommon_t *pCommonCfg;
} l2cfgSta_t;

// API for getting parameters is supplied by roles.h
// Roles module shall configure itself directly from l2 cfg structures or by supplying a stuctures to be filled

// ============================================================================
//  AP/P2P GO configuration
//     AP specific parameters or parameters which are used by both STA & AP
//     but may get different values
// ============================================================================

typedef struct
{
    uint32_t secondChanceTxTimePeriod; // Time in usec to wait for second chance transmission after max TX retries occured.
    uint32_t basicRateSetBM;      // 6, 12, 24
    uint32_t supportedRatesBM;    // All BG rates + MCS rates in case HT is enabled
    uint16_t beaconIntervalTU;    // time between two consecutive beacons, measured in TUs (1024usecs)
    uint8_t  maxTxRetriesThreshold;  // Max TX retries threshold
    uint8_t  dtimInterval;

    Bool_e  pmf;                      //management frame protection


    // MCP defines beacon expiry and sends it in AP start role, it looks like FW doesn't use it.
    // #define ROLE_AP_BEACON_TX_TIMEOUT_DEF       20
    // TODO - can we remove it?
} cfgAp_t;

typedef struct
{
    const cfgAp_t       *pApCfg;
    const qosCfgSta_t   *pQosCfg;       // Strat w/ the same cfg for AP & STA role
    const l2CfgCommon_t *pCommonCfg;
} l2cfgAp_t;


// ============================================================================
// Dynamic configuration - This structure contains the parameters for L2 cfg
// that can be configured by the host or for testing / debug
// ============================================================================

typedef struct
{
    uint8_t  wmeAcPsMode[NUM_ACCESS_CATEGORIES];  // wme per ac power save mode
                                                     // needed for PS configuration and for building assoc request
                                                     // MCP default is legacy for all ACs except of video
} AcPsMode_t; //PS scheme mode per access category

typedef struct
{
    AcPsMode_t  acPsMode;           // wme //PS scheme mode per access category
                                    // used for building QOS IE

//TODO: PS scheme for AP role
//    uint8_t/*PSScheme_e*/  psMode;             // The desired PS mode of the station, MCP default is UPSD
//                                    // used for building QOS IE
    uint8_t  maxSpLen;                // (1) used for building QOS IE
    uint8_t  ApMaxNumStations;        //current host configuration of maximum number of stations supported on this AP
    uint8_t  ApMaxNumStationsFromConfIni;  // Maximum number of stations supported on this AP, for the conf ini

    uint8_t selectedBand;             // Selected Band for PHY config
    uint8_t wirelessProtocol;
} l2DynamicCfg_t;



extern l2CfgCommon_t *gpL2CommonCfg;
extern l2cfgSta_t    *gpL2StaBasedCfg;
extern l2cfgAp_t     *gpL2ApBasedCfg;

// This structure contains the parameters for L2 cfg that can be configured by the host or for testing / debug
extern l2DynamicCfg_t gL2DynamicCfg;

void l2_cfg_Init();

int l2_cfg_GetStaHeSupport();

Bool32 l2_cfg_isStaHeEnabled(void);
Bool32 l2_cfgIsStaWmeEnabled(void);

// ============================================================================
//      The APIs below are used for fetching common configurations
// ============================================================================

/* ----------------------------------------------------------------------------
 cfgIs11nEnabled
      This function checks whether HT is enabled

 Parameters:
     none

 return: TRUE - HT enabled, FALSE not enabled
---------------------------------------------------------------------------- */
Bool32 cfgIs11nEnabled();


/* ----------------------------------------------------------------------------
 cfgIs40MHzEnabled
      This function checks whether 40MHz channel is enabled

 Parameters:
     none

 return: TRUE - 40MHz channel enabled, FALSE not enabled
---------------------------------------------------------------------------- */
Bool32 cfgIs40MHzEnabled();

/* ----------------------------------------------------------------------------
 cfgIsMimoEnabled
      This function checks whether HT is enabled

 Parameters:
     none

 return: TRUE - HT enabled, FALSE not enabled
---------------------------------------------------------------------------- */
Bool32 cfgIsMimoEnabled();


/* ----------------------------------------------------------------------------
 cfgGetRates
      This function fills default basic rates and supported rates on caller memory.
      Result is returned in BM, based on rates.h definitions, convertBitmapToRatesIe
      can be used to construct IEs.

 Parameters:
      aRoleType - selects the correct cfg structure
      apBasicRatesBM - pointer to basic rates BM
      apSupportedRatesBM - pointer to supported rates BM

 return: none
---------------------------------------------------------------------------- */
void cfgGetRates(RoleType_e aRoleType, uint32_t *apBasicRatesBM, uint32_t *apSupportedRatesBM);

/* ----------------------------------------------------------------------------
 cfgGetWpsParameters
      This function returns a pointer to the default WPS parameters

 Parameters:
     OUT wpsParameters_t **pWpsParameters - Pointer to callers' wps parameters

 return: TRUE - WPS parameters are valid, FALSE parameters not available
---------------------------------------------------------------------------- */
Bool32 cfgGetWpsParameters(wpsParameters_t **pWpsParameters);

/* ----------------------------------------------------------------------------
 cfgGetWmmParameters
      This function returns a pointer to the default WMM parameters

 Parameters:
     OUT AcCfg_t **pAcCfg- Pointer to callers' wmm parameters

 return: TRUE - WMM parameters are valid, FALSE parameters not available
---------------------------------------------------------------------------- */
Bool32 cfgGetWmmParameters(const AcCfg_t **pAcCfg);

/* ----------------------------------------------------------------------------
 cfgGetHtCapabilities
      This function fills default HT capabilities on caller memory

 Parameters:
     OUT apHtCapabilities - pointer to caller's HT capabilities

 return: TRUE - HT capabilities are valid, FALSE HT not supported
---------------------------------------------------------------------------- */
Bool32 l2_cfgGetHtCapabilities(const htCapabilities_t **apHtCapabilities);


/* ----------------------------------------------------------------------------
 cfgGetMaxTxRetriesThreshold
     returns max tx retries threshold

 Parameters:
     IN aRoleId - role Id

 return: max tx retries threshold
---------------------------------------------------------------------------- */
uint8_t cfgGetMaxTxRetriesThreshold (RoleType_e aRoleType);

/* ----------------------------------------------------------------------------
 cfgGetsecondChanceTxTimePeriod
     returns the time in usec to wait for the before starting transmission for
     the second chance.

 Parameters:
     IN aRoleId - role Id

 return: second chance timer period in usec
---------------------------------------------------------------------------- */
uint32_t cfgGetsecondChanceTxTimePeriod (RoleType_e aRoleType);

/* ----------------------------------------------------------------------------
 cfgGetHtCapabilities
      This function fills HT capabilities IE; can be used for constructing
      probe response, association request/response ...

 Parameters:
     IN aRoleId - to be used in case we defined different behavior for
                  different role types.
     OUT apHtCapsIE - pointer to buffer to be filled

 return: number of bytes added to the buffer or 0 if HT isn't supported
---------------------------------------------------------------------------- */
uint32_t l2_cfgBuildHtCapabilitiesIe(uint32_t aRoleId, uint8_t *apHtCapsIE);


#ifndef DISABLE_WIFI6
uint32_t l2_cfgBuildVhtCapabilitiesIe(uint32_t aRoleId, uint8_t *apVhtCapsIE);
#endif

uint32_t l2_cfgBuildOperatingModeNotifcationIe(uint32_t aRoleId, uint8_t *operatingModeNotifIE);


#ifndef DISABLE_WIFI6
/* ----------------------------------------------------------------------------
 cfgGetHeCapabilities
      This function fills HE capabilities IE; can be used for constructing
      probe response, association request/response ...

 Parameters:
     IN aRoleId - to be used in case we defined different behavior for
                  different role types.
     OUT apHeCapsIE - pointer to buffer to be filled

 return: number of bytes added to the buffer or 0 if HE isn't supported
---------------------------------------------------------------------------- */
uint32_t l2_cfgBuildHeCapabilitiesIe(uint32_t aRoleId, uint8_t *apHeCapsIE);
#endif

/* ----------------------------------------------------------------------------
 cfgGetApMaxNumStations
     returns the maximum number of stations supporte by AP

 Parameters:
           none

 return: max number of stations
---------------------------------------------------------------------------- */
uint8_t cfgGetApMaxNumStations (void);

/* ----------------------------------------------------------------------------
 cfgSetApMaxNumStations
     Set the maximum number of stations supporte by AP

 Parameters:    max number of stations


 return: none
---------------------------------------------------------------------------- */
void cfgSetApMaxNumStations(uint8_t apMaxNumStations);

/* ----------------------------------------------------------------------------
 cfgGetApMaxNumStationsFromConfIni
     returns the maximum number of stations supporte by AP
     as was configured on the conf.ini

 Parameters:
           none

 return: max number of stations
---------------------------------------------------------------------------- */

uint8_t cfgGetApMaxNumStationsFromConfIni (void);

/* ----------------------------------------------------------------------------
 cfgSetApMaxNumStationsFromConfIni
     Set the maximum number of stations supporte by AP
     as was configured on the conf.ini

 Parameters:    max number of stations


 return: none
---------------------------------------------------------------------------- */

void cfgSetApMaxNumStationsFromConfIni(uint8_t apMaxNumStationsFromConfIni);


/* ----------------------------------------------------------------------------
 cfgSetFragThreshold
      This function sets the Fragmentation Threshold

 Parameters:
     number of bytes of Fragmentation Threshold

 return: none
---------------------------------------------------------------------------- */
void cfgSetFragThreshold(uint16_t aFragThreshold);

/* ----------------------------------------------------------------------------
 cfgGetFragThreshold
      This function retrieves the Fragmentation Threshold

 Parameters:
     none

 return: number of bytes of Fragmentation Threshold
---------------------------------------------------------------------------- */
uint16_t cfgGetFragThreshold();


/*----------------------------------------------------------------------------
 * l2_cfg_is5GhzSupported
 *      This function checks whether the device supports 5GHz band.

 * Parameters:
 *     none

 * return: TRUE if device supports the band, FALSE otherwise

---------------------------------------------------------------------------- */

Bool32 l2_cfg_is5GhzSupported(void);


/*----------------------------------------------------------------------------
 * l2_cfg_isMixedModeSupported
 *      This function checks whether the device supports mixed mode security
 *      type (WPA2/WPA3).

 * Parameters:
 *     none

 * return: TRUE if device supports mixed mode security, FALSE otherwise

---------------------------------------------------------------------------- */
Bool32 l2_cfg_isMixedModeSupported(void);

// ============================================================================
//      The APIs below are used for fetching STA based configurations
// ============================================================================

/* ----------------------------------------------------------------------------
 cfgIsStaWmeEnabled
      This function checks whether WME is enabled for STA based roles.
      (For AP based roles, WME support is defined by supplicant configuration.

 Parameters:
     none

 return: TRUE - WME enabled, FALSE not enabled
---------------------------------------------------------------------------- */
Bool32 cfgIsStaWmeEnabled();

/* ----------------------------------------------------------------------------
 cfgIsApWmeEnabled
      This function checks whether WME is enabled for AP based roles.
      (For AP based roles, WME support is defined by supplicant configuration.

 Parameters:
     none

 return: TRUE - WME enabled, FALSE not enabled
---------------------------------------------------------------------------- */
Bool32 cfgIsApWmeEnabled();

/* ----------------------------------------------------------------------------
 cfgIsApMfpEnabled
      This function checks whether PMF is enabled for AP based roles.

 Parameters:
     none

 return: TRUE - PMF enabled, FALSE not enabled
---------------------------------------------------------------------------- */
Bool32 cfgIsApPmfEnabled();

/* ----------------------------------------------------------------------------
 cfgIsStaPmfEnabled
      This function checks whether PMF is enabled for STA based roles.

 Parameters:
     none

 return: TRUE - PMF enabled, FALSE not enabled
---------------------------------------------------------------------------- */
Bool32 cfgIsStaPmfEnabled();

/* ----------------------------------------------------------------------------
 cfgIsStaPbacEnabled
      This function checks whether PBAC is enabled for STA based roles.

 Parameters:
     none

 return: TRUE - Pbac enabled, FALSE not enabled
---------------------------------------------------------------------------- */
Bool32 cfgIsStaPbacEnabled();



/* ----------------------------------------------------------------------------
 cfgGetCwMin/cfgGetCwMax
      These functions return the default values for QOS parameters

 Parameters:
     none

 return: TRUE - WME enabled, FALSE not enabled
---------------------------------------------------------------------------- */
const AcCfg_t * cfgGetDefaultAcCfg(uint8_t ac);

/* ----------------------------------------------------------------------------
 cfgGetStaDefaultSchedScanPlans
      This function returns the default scan plans for scheduled scan.

 Parameters:
     none

 return: default sched scan plans
 ---------------------------------------------------------------------------- */
const char* cfgGetStaDefaultSchedScanPlans();

/* ----------------------------------------------------------------------------
 cfgIsStaShortPreambleEnabled
      This function checks whether short preamble is enabled for B rates for
      STA based roles.
      If default preamble is short and peer requires long peramble, it is updated
      on role's DB. TODO - verify where exactly.
      (For AP based roles, preamble type is defined by supplicant configuration).

 Parameters:
     none

 return: TRUE - WME enabled, FALSE not enabled
---------------------------------------------------------------------------- */
Bool32 cfgIsStaShortPreambleEnabled();

/* ----------------------------------------------------------------------------
 cfgGetStadot11Mode
      This function returns the 802.11 supported mode/modes for STA based role

 Parameters:
     none

 return: STA supported modes
---------------------------------------------------------------------------- */
dot11Mode_e cfgGetStadot11Mode();

/* ----------------------------------------------------------------------------
 cfgIsStaShortSlotEnabled
      This function checks whether short slot is enabled for STA based roles.
      If default slot is short and peer requires long slot, it is updated
      on role's DB. TODO - verify where exactly.
      (For AP based roles, slot type is defined by supplicant configuration).

 Parameters:
     none

 return: TRUE - WME enabled, FALSE not enabled
---------------------------------------------------------------------------- */
Bool32 cfgIsStaShortSlotEnabled();

// ============================================================================
//      The APIs below are used for fetching AP based configurations
// ============================================================================

/* ----------------------------------------------------------------------------
 cfgGetApCfg
      This function retruns AP configuration

 Parameters:
     apCfg - OUT pointer to AP configuration

 return:
---------------------------------------------------------------------------- */
const cfgAp_t * cfgGetApCfg();

// Enumeration below define the different fields in l2DynamicCfg_t,
// enabling us to configure the required fields.
//TODO: put in device.h?
typedef enum
{
    L2_AC_PS_MODE   = 0,
//    L2_PS_MODE      ,
    L2_MAX_SP_LEN
} l2DynamicCfgParamId_e;


void l2_cfg_Dynamic_set(l2DynamicCfgParamId_e paramIndex, uint8_t *paramValue);

/* ----------------------------------------------------------------------------
 cfgSetWpsParameters
      Set WPA Supplicant WPS configurations

 Parameters:
     params - WPS parameters

 return: none
---------------------------------------------------------------------------- */
void cfgSetWpsParameters(const WpsParams_t *params);

/* ----------------------------------------------------------------------------
 cfgSetWpsParametersCleanUp
      Cleans up the previopusly set WPS params

 Parameters:
     none

 return: none
---------------------------------------------------------------------------- */
void cfgSetWpsParametersCleanUp();

/* ----------------------------------------------------------------------------
 cfgSetWpsMode
      Set WPS mode

 Parameters:
     wpsDisabled - False for WPS support, True otherwise

 return: none
---------------------------------------------------------------------------- */
void cfgSetWpsMode(Bool_e wpsDisabled);

/* ----------------------------------------------------------------------------
 cfgGetWpsMode
      Get WPS mode

 Parameters: none

 return: True if enabled, false if disabled
---------------------------------------------------------------------------- */
Bool_e cfgGetWpsMode();

/* ----------------------------------------------------------------------------
 cfgGetP2pParameters
      This function returns a pointer to the default P2P parameters

 Parameters:
     OUT P2pParameters_t **pP2pParameters - Pointer to callers' p2p parameters

 return: TRUE - P2p parameters are valid, FALSE parameters not available
---------------------------------------------------------------------------- */
Bool32 cfgGetP2pParameters(const P2pParameters_t **pP2pParameters);
/* ----------------------------------------------------------------------------
 cfgSetP2pParameters
    Set WPA Supplicant P2P configurations

 Parameters:
    params - P2P parameters

 return: none
---------------------------------------------------------------------------- */
void cfgSetP2pParameters(const P2pParams_t *params);
/* ----------------------------------------------------------------------------
 cfgSetP2pDevice
    Set P2P Device 

 Parameters:
    p2pDevDisable - False for p2p device support, True otherwise

 return: none
---------------------------------------------------------------------------- */
void cfgSetP2pDevice(Bool_e p2pDevDisable);
/* ----------------------------------------------------------------------------
 cfgGetP2pDeviceEnable
      Get P2P device enable/disabled

 Parameters: none

 return: True if enabled, false if disabled
---------------------------------------------------------------------------- */
Bool_e cfgGetP2pDeviceEnable();
/* ----------------------------------------------------------------------------
 cfgGetP2pOperChannel
      Gets a P2P operational channel from config

 Parameters: none

Return: oper channel
---------------------------------------------------------------------------- */
uint8_t cfgGetP2pOperChannel();
/* ----------------------------------------------------------------------------
 cfgGetP2pOperRegClass
      Gets a P2P operational class from config

 Parameters: none

Return: oper channel
---------------------------------------------------------------------------- */
uint8_t cfgGetP2pOperRegClass();

/* ----------------------------------------------------------------------------
 l2_StoreWirelessProto
      Stores HP selected Wireless Protocol

 Parameters: proto

Return: 
---------------------------------------------------------------------------- */
void l2_StoreWirelessProto(uint8_t proto);

/* ----------------------------------------------------------------------------
 l2_GetWirelessProto
      Gets HP selected Wireless Protocol

 Parameters: none

Return: wireless protocol
---------------------------------------------------------------------------- */
uint8_t l2_GetWirelessProto();

/* ----------------------------------------------------------------------------
 l2_StorePhyConfig
      Stores HP selected Phy Config

 Parameters: band_cfg

Return: 
---------------------------------------------------------------------------- */
void l2_StorePhyConfig(uint8_t band_cfg);

/* ----------------------------------------------------------------------------
 l2_GetPhyConfig
      Gets HP Phy CONFIG

 Parameters: none

Return: band_cfg
---------------------------------------------------------------------------- */
uint8_t l2_GetPhyConfig();

/* ----------------------------------------------------------------------------
 l2_cfg_setDevice5GhzSupport
      Configure whether the device supports 5 GHz or not and store configuration
      in a retrievable global variable.
      5 GHz support is indicated by reading the device fuses and reading the
      according INI configuration.

 Parameters: none

Return: negative value on error, 0 otherwise
---------------------------------------------------------------------------- */
int8_t l2_cfg_setDevice5GhzSupport();


/* ----------------------------------------------------------------------------
 cfgSetApSaeAntiCloggingThreshold
      Sets AP SAE anti-clogging threshold

Return: none
---------------------------------------------------------------------------- */
void cfgSetApSaeAntiCloggingThreshold(uint8_t apSaeAntiCloggingThreshold);

/* ----------------------------------------------------------------------------
 cfgGetApSaeAntiCloggingThreshold
      Gets AP SAE anti-clogging threshold

Return: AP SAE anti-clogging threshold
---------------------------------------------------------------------------- */
uint8_t cfgGetApSaeAntiCloggingThreshold(void);

/* ----------------------------------------------------------------------------
 cfgGetDeviceSupportedBandsBM
      Get the bitmask of the user-config (INI) and device fuses bands support

 Parameters: none

Return: supported bands bitmask (based on RadioBand_e enum)
---------------------------------------------------------------------------- */
uint32_t cfgGetDeviceSupportedBandsBM();

/* ----------------------------------------------------------------------------
 cfgSetDeviceSupportedBandsBM
      Set the bitmask of the user-config (INI) and device fuses bands support

 Parameters: supported bands bitmask (based on RadioBand_e enum)

Return: none
---------------------------------------------------------------------------- */
void cfgSetDeviceSupportedBandsBM(uint32_t supportedBandsBM);

#endif // _L2_CFG_H_
