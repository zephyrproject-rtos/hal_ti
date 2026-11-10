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

  FILENAME:       drv_ti_internal.h

  DESCRIPTION:    This files defines the APIs between ti driver supplicant driver
  	  	  	  	  (driver_ti_wifi) and its service files.

  ----------------------------------------------------------------------------- */
#ifndef _DRV_SUPPLICANT_API_H_
#define _DRV_SUPPLICANT_API_H_

#include <802_11defs.h>
#include "common.h"
#include "drivers/driver.h"
#include "cme_defs.h"
#include "config_ssid.h"
#include <rsn.h>            // for securityKeys_t
#include <rates.h>
#include "cme_scan_api.h"
#include "common/ieee802_11_common.h"
#include <driver/drv_core.h>
#include "public_share.h"
#include "udata_api.h"
#include "drivers/driver.h"


// ============================================================================
//	Type definitions
// ============================================================================

// Forward declarations
struct CC33_FrameTxDesc_t;

// -----------------------------------------
// temporary declarations
// -----------------------------------------
#define TI_PARAM_DISABLE_ROLE        (1)
#define TIWDRV_CMD_SET_FLAG          (1)

// -----------------------------------------
// Packet allocation related definitions
// -----------------------------------------

// Offset from allocated descriptor address to the first byte of
// packet payload. The offset takes into account:
//		o descriptor length,
//		o 802.11 header (including optional HT control),
//      o possible encryption of management, (AES security header)
//		o some spare
#define CC33_DRV_PAYLOAD_START_OFFSET  						\
		(													\
			  ALIGN_TO_4_BYTE(sizeof(CC33_FrameTxDesc_t)) 	\
			+ sizeof(TxIfDescriptor_t)                      \
			+ WLAN_MAX_HDR_SIZE                             \
			+ WLAN_SNAP_HDR_LEN                             \
			+ AES_RSN_HEADER_LEN                            \
		)

// Offset from allocated descriptor address to the first byte of
// 802.11 header. The offset takes into account:
//      o descriptor length,
//      o possible encryption of management,
//      o some spare
#define CC33_DRV_HEADER_START_OFFSET                        \
        (                                                   \
              ALIGN_TO_4_BYTE(sizeof(CC33_FrameTxDesc_t))   \
            + sizeof(TxIfDescriptor_t)                      \
            + WLAN_SNAP_HDR_LEN                             \
        )

// Size of 802.11 footer, includes FCS and optional encryption info (AES MIC).
#define CC33_DRV_PACKET_FOOTER_SIZE		(FCS_SIZE + WLAN_SNAP_HDR_LEN + AES_MIC_LEN)

// Minimal size for management packet, includes everything but management payload
#define CC33_DRV_MNG_PACKET_MIN_SIZE	(CC33_DRV_PAYLOAD_START_OFFSET + CC33_DRV_PACKET_FOOTER_SIZE)

// Minimal size for data packet
#define CC33_DRV_DATA_PACKET_MIN_SIZE   (CC33_DRV_PAYLOAD_START_OFFSET + CC33_DRV_PACKET_FOOTER_SIZE)

// Maximal length of supported rates IES the device is expected to send
#define CC33_DRV_SUPPORTED_RATES_IE_MAX_SIZE			(8)
#define CC33_DRV_EXT_SUPPORTED_RATES_IE_MAX_SIZE	   (16)
#define CC33_DRV_RATES_IES_MAX_SIZE	\
	(CC33_DRV_SUPPORTED_RATES_IE_MAX_SIZE + CC33_DRV_EXT_SUPPORTED_RATES_IE_MAX_SIZE)


// Defines type of SW master for allocating a packet from MMU.
#define CC33_DRIVER_MMU_ALLOC_MASTER_TYPE (MMU_SW_MASTER_ALLOC_APP_HIGH)

// Define the management authentication header length (not including the challenge text)
#define CC33_DRV_MNG_AUTH_HEADER_SIZE                   (6)

// Define the management authentication challenge text header (element ID and length)
#define CC33_DRV_MNG_AUTH_CHALLENGE_HEADER_SIZE         (2)

#define CC33_ROC_ENDLESS_TIMOUT                         (0xFFFFFF)
// Define array entry for the Broadcast keys (for now up to 2 broadcast keys are used)
typedef enum
{
    AES_BROADCAST1_ENTRY,
    AES_BROADCAST2_ENTRY,
    AES_NUM_BROADCAST_KEYS

} aesBroadcastKeysArrEntry_e;


typedef enum
{
    AUTH_ALG_TYPE_OPEN_SYSTEM,
    AUTH_ALG_TYPE_SHARED_KEY,
    AUTH_ALG_TYPE_FT,
    AUTH_ALG_TYPE_SAE,
    AUTH_ALG_TYPE_LEAP,
    AUTH_ALG_TYPE_AUTO
} authType_e;

typedef enum 
{
    P2P_GROUP_ROLE_CLIENT = 0x00,
    P2P_GROUP_ROLE_GO     = 0x01,
    P2P_GROUP_ROLE_NONE   = 0xFF
} p2pGroupRole_e;
typedef struct
{
    // Driver sets the access parameters for 4 access categories.
    // FW initialize default values for the CTS to self 5th category.
    AcCfg_t                     acParameters[NUM_ACCESS_CATEGORIES];

    uint8_t/*PSScheme_e*/       psScheme;   /* The power save scheme of the link. in our implelentation all ac queues uses the same power scheme.*/


    heMuEdcaAcParams_t          muEdca[NUM_ACCESS_CATEGORIES];

} RolePostAssocParameters_t;


// This enumeration defines the requested operation following handling of
// received management packet.
typedef enum
{
	/* no action required */
	RX_MGMT_NONE,

	/* caller must call cfg80211_send_deauth() */
	RX_MGMT_DEAUTH,

	/* caller must call send_disassoc() */
	RX_MGMT_DISASSOC,

     /* caller must call handler for unprotected deauth event */
     RX_MGMT_UNPROT_DEAUTH,

     /* caller must call handler for unprotected disassoc event */
     RX_MGMT_UNPROT_DISASSOC,

	/* caller must call send_rx_auth() */
	RX_MGMT_AUTH,

	/* caller must call send_rx_assoc() */
	RX_MGMT_RX_ASSOC,

	/* caller must call send_assoc_timeout() */
	RX_MGMT_ASSOC_TIMEOUT,

	/* caller must call send_rx mgmt frame event to supplicant */
	RX_MGMT_SEND_RX_MGMT_EVENT,

	/* probe request was received, for the device it may be as result of P2P listen */
	RX_SEND_RX_PROBE_REQ,

     /* don't release the packet yet, it will be handled later */
     RX_DONT_FREE
} rxMngPackNextOperation_e;

// This enumeration defines possible states of the association request packet
typedef enum
{
    ASSOC_REQ_DESC_SENT_TO_PMAC,        // Allocated and handed to PMAC
    ASSOC_REQ_DESC_PENDING_TX,          // Received assoc response or timeout occured,
                                        // descriptor is still under PMAC control
    ASSOC_REQ_DESC_PENDING_ASSOC_RESP,  // TX exchange CB returned descriptor to SW
                                        // control; waiting for assoc response or timeout
                                        // in order to be released
    ASSOC_REQ_DESC_OK2RELEASE,          // Assoc request was received, packet can be released
    ASSOC_REQ_DESC_INVALID              // not allocated/released

} assocReqDescState_e;

// Forward declaration
struct wpa_driver_auth_params;
struct ieee80211_mgmt;

typedef struct
{
    uint32_t supportedRatesBM;
    uint32_t basicRatesBM;
    uint32_t suppRateNum;
    uint32_t basicRateNum;
} apRatesSets_t;

// Specific driver information and state.
typedef struct
{
    char            cMac[MAC_ADDR_LEN];                    /** Station mac address            */
    char            cSupportedRates[MAX_NUM_BG_RATES]; /** rate list                      */
    char            cSupportedRatesLen;                        /** num of rates                   */
    int             ilistenInterval;
    unsigned short  sAid;                                      /** station Id                     */
    unsigned short  sCapability;                               /** bit  map of station capability */
	unsigned short  ht_capabilities_info;                      /** capability info                */
	char            a_mpdu_params;
	unsigned char   supported_mcs_set[MAX_NUM_MCS_RATES]; /** 11n  mcs_set info  */
    int             flags;                                        /** STA's link WME mode in Tx path  */
    char 			acInfo;                                       /** AC info bitmap */
} apSationParams_t;

// replaces struct cfg80211_bss
typedef struct
{
	struct ieee80211_channel *channel;

    u64    tsfOffset;
	uint8_t  bssid[ETH_ALEN];
	uint16_t  beacon_interval;
	uint8_t  capability;
	uint8_t  *beacon_ies;
	size_t len_beacon_ies;
	uint8_t  *proberesp_ies;
	size_t len_proberesp_ies;

	s32 signal;

//	void (*free_priv)(struct cfg80211_bss *bss);
	uint8_t priv[0] __attribute__((__aligned__(sizeof(void *))));
} peerInfo_t;

// Autentication information, valid only from authentication start till
// authentication response is received and handled
typedef struct
{
	peerInfo_t 		peerInfo;		// peer information is kept in case another
									// authentication request should be sent
	unsigned int 	timeoutMS;		// timeout for another activation (in msecs)
	authType_e 		authType;		// open, shared key ...
	uint8_t  			tries;			// number of driver autonomous reties
									// (may happen due to reject if AP can't accept more STAs)
	uint8_t           expectedTransaction;

     /**
	 * auth_data - Additional elements for Authentication frame
	 *
	 * This buffer starts with the Authentication transaction sequence
	 * number field. If no special handling of such elements is needed, this
	 * pointer is %NULL. This is used with SAE and FILS.
	 */
	uint8_t *auth_data;

	/**
	 * auth_data_len - Length of auth_data buffer in octets
	 */
	size_t auth_data_len;


// In case of WEP shared authentication, the key is set in cc33_driver_authenticate and not sent to try2authenticate
//	uint8_t  			key[WEP104_HEX_KEY_LENGTH]; 		// [WLAN_KEY_LEN_WEP104];	is it the correct definition? TODO
//	uint8_t   		key_len, key_idx;
	Bool_e  		priority;
	Bool_e  		done;

	size_t  		ie_len;
	uint8_t   		ie[];

} authInfo_t;

typedef struct
{
	peerInfo_t 		peerInfo;
	const uint8_t     *supp_rates;

	unsigned long timeoutMS;
	int32_t tries;

	uint8_t  *pDescriptor;         // ID of association request packet, for SW retransmissions
	assocReqDescState_e descriptorState;

	uint16_t capability;
	uint8_t  prev_bssid[ETH_ALEN];
	uint8_t  ssid[SSID_MAX_LEN];
	uint8_t  ssid_len;
	uint8_t  supp_rates_len;

	Bool32 wmm, uapsd;
	Bool32 have_beacon;
	Bool32 sent_assoc;
	Bool32 synced;

	uint8_t ap_ht_param;

	size_t ie_len;
	uint8_t ie[];
} assocInfo_t;


typedef struct
{
    OsiLockObj_t p_off_channel_mutex;
    OsiLockObj_t p_remain_channel_mutex;
    Bool_e off_channel_dev_timer_was_set;
    Bool_e   off_channel_is_mgmt_packet_to_send;
    uint32_t off_channel_mgmt_datalen;
    const uint8_t* p_off_channel_mgmt_data;
    uint32_t off_channel_duration;
    uint32_t off_channel_freq;
    Bool_e RocInitiateExplicitly;
}off_channel_t;


typedef struct
{
    uint32      rxPN32[NUM_TRAFFIC_CATEGORIES + 1];  // RX Packet Number Upper Counter
    uint16      rxPN16[NUM_TRAFFIC_CATEGORIES + 1];  // RX Packet Number Lower Counter
} aes_pn_tid_t;

typedef struct
{
     uint8_t TransmittingBssid[ETH_ALEN]; // Holds the actual transmitting address from non-transmitting bssids.
	uint8_t mbssidIndex;
	uint8_t mbssidIndicator;

}mbssidData_t;

typedef struct
{
    uint16_t    vendor_elements_length;
    uint8_t     *vendor_elements;  //[WLAN_BEACON_MAX_SIZE];
}vendorIEInfo_t;
#define DENY_LIST_MAX_ENTRIES 10 // Maximum number of entries in the deny list. If compiled as 0 then the deny list feature is disabled.
#define DENY_LIST_EN    (DENY_LIST_MAX_ENTRIES > 0)
#define DENY_LIST_DEFAULT_EXPIRY_TIME 10*1000 // 10 seconds in milliseconds
#define DENY_LIST_TIMER_TIMEOUT_SECONDS 5*60 // Timer timeout for clearing the deny list, in seconds. Currently 5 minutes.

// Node structure
typedef struct DenyList_Node_t
{
    uint32_t expiryTime;
    struct DenyList_Node_t* next;
    uint8_t macAddr[MAC_ADDR_LEN];
} DenyList_Node_t;

// Linked list structure
typedef struct 
{
    DenyList_Node_t* head;
    int size;
} DenyList_LinkedList_t;

// TODO - Booleans currently waste 8 bits, later on can be replaced with bitmask.
typedef struct
{
	struct wpa_supplicant 	*wpa_s;
	struct hostapd_data 	*hapd;
	void 					*ctx; /* holds wpa_s/hapd, according to operating mode */

	char 		iface[IFNAMSIZ + 1];	// Interface name, set by supplicant, indicates role type
	RoleType_e 	roleType;				// Type of role corresponding to this interface
	RoleID_t 	roleId;					// Role ID related to the interface.
										// Allocated by FW in response to enable role command
	uint8_t 	roleStarted:1;	        // Indicates whether role already was started. Cleared when a role is										// enbaled/disabled, set when role is first started.
	uint8_t		roleEnabled:1;          // Indicates whether role already was enabled. Cleared when the role is disabled.
	uint8_t     beacon_set:1;           //AP is transmitting beacons

	uint8_t 		macAddr[ETH_ALEN];		// role related MAC address

	struct wpa_driver_capa capa;			// driver capabilities, set on init
											// and reported to supplicant.
											// Tested during supplicant operation.

	unsigned int 	countryUpdated;			// 1 indicates supplicant has set country,
											// WL8 - regulatrory domain should be informed
											// when role is disabled.
											// cc3100 - setting country from supplicant isn't supported. It is set only from host API.
											// TODO - if not needed, remove this field and cc33_driver_set_country

	uint32_t			retry_auth;				// If 1, the transmitted authentication packet is a retry.

	uint8_t *assoc_req_ies;						// Hold association request IEs
	size_t assoc_req_ies_len;
	uint8_t *assoc_resp_ies;						// Hold association response IEs
	size_t assoc_resp_ies_len;
	uint8_t *beacon_ies;
	size_t beacon_ies_len;

	int operstate;
	int deauthReason;           // Keeps deauth reason code to be sent to CME
	                            // along with disconnection notification.

	//AddPeerCmd_t *pAddStaParams;
	void *pAddStaParams;  // see AddPeerCmd_t ,Keeps STA parameters received in sta_add API,
	                            // until sta_set_flags API is activated and
	                            // CMD_ADD_PEER can be set to FW.
	                            //We keep a linked list of commands since multiple peers can be connected at the same time.
	                            //In this case Supplicant will send several sta_add and then several sta_set_flags.

	uint32_t assocFreq;			// Candidate frequency, reported to supplicant
	                            // in EVENT_ASSOC

	// Hold informtion related to the authentication sequence
	authInfo_t	*pAuthInfo;
	assocInfo_t	*pAssocInfo;

	Bool_e       associated;		// If TRUE, STA is associated with remote AP
	Bool_e       connected;			// Set to TRUE when connection sequence is fully completed.
	Bool_e       connectTimeout;    // Set to TRUE on authentication/association timeout
	                                // Used for notifying CME in case of supplicant transition
	                                // to disconnected state.
	Bool_e       rocActive;         // Indicates ROC is ongoing. Used to send CROC in case
	                                // role is stopped before conenction is established.

    uint8_t       ssid[SSID_MAX_LEN]; // Hold SSID of currently connected AP.
    size_t        ssid_len;           // Hold SSID Len of currently connected AP.
    int32_t       freq;               // Hold Freq of currently connected AP.

	uint8_t currBssid[ETH_ALEN];    // FOR STA Hold BSSID of currently connected AP.
	                                // Set when association response is
	                                // successfully received and handled
	                                // TODO - can be read of roles module and save 6 ULL bytes
	                                // Use Links_GetPeerAddress(lid)
	                                // if descriptor of packet received from peer is available lid
	                                // can be taken from pDesc->link_role_queue.link_id

	mbssidData_t mbssidData;

	// Use the BSSIDs below to verify received deauth/disassoc packets are from
	// valid peer.
	uint8_t authBssid[ETH_ALEN];

	uint32_t     roleSession;

	uint8_t      activeOneShotScanBM; // Bit mask indicating which type of one
	                                // shot scan is active. Used for setting
	                                // scan type for stop scan command.

	ApRFParam_t ApRfParams;
	const struct drv_cmd_ops *ops;


    Bool_e wmeEnabled;//used after connection to configure the FW
    Bool32 useProtection;//used after connection to configure the FW
    PeerCap_t peerCap;//used after connection to configure the FW
    BssCap_t bssCap;//used after connection to configure the FW
    uint32_t link;//used after connection to configure the FW
    RolePostAssocParameters_t assocParams;//used after connection to configure the FW

    //those fields are for  off channel device
    Bool_e devWasCreatedForOffChannel:1; //the private data was created as for temporary off channel
    Bool_e offChannel_role_enabled:1;
    Bool_e offChannel_role_started:1;
    Bool_e offChannel_roc_started:1;
    //off channel device  end

    uint32_t pRemainOnChannelDuration; //how much time to wait on remain on channel
    OsiTimer_t   pRemainOnChannelTimer;

    // p2p connect params - stored for p2p_connect()
    uint8_t     p2pPeerAddr[ETH_ALEN];      // mac address of p2p peer
    uint8_t     p2pWpsMethod; 
    uint8_t     p2pPin[P2P_PIN_CODE_SIZE];   // an 8-digit number + \n: PIN[7 digits + last digit is a checksum]
    Bool_e 	    p2pConnectionStarted:1;     // Indicates whether connection is started
    Bool_e 	    p2pPeerCandidateIsFound:1;  // Indicates if desired peer was found while p2p discovery
    Bool_e      p2pReportProbeRequestRx:1;  // TRUE/FALSE - Indicates if supplicant ask us to report probe request rx 
    Bool_e      p2pFindReportScanResults:1; // TRUE - if called from get scan results, FALSE - from connection scan
    uint16_t    p2pChannel; 
    Bool_e      p2pCapabGroupOwnerBit:1;    // if desired peer is GO
    
    RoleCommonParam_t apRate;// Relevant only for STA role, the rates supported by the connected AP combined with the rates that the STA is supporting
    uint8_t security_key_idx_mc2;        // Key id of broadcast key in index 1 of array
    uint8_t security_key_idx_mc1;        // Key id of broadcast key in index 0 of array
    uint8_t broadcastNextKeyArrEntry;    // Next entry in broadcast key array to be updated
    aes_pn_tid_t broadcastPn[AES_NUM_BROADCAST_KEYS];

    int8_t fwMaxTxPower; // Role`s effective max TX power, as sent to FW (dBm).
    int8_t apPowerLevel; // AP`s regulatory max TX power (dBm), including TPC for STA.
    int8_t configuredApTxPower; // User-configured AP TX power (dBm).

    heMuEdcaAcParams_t apHeMuEdcaAcParams[NUM_ACCESS_CATEGORIES]; 
    dot11_ACParameters_t apAcParameters;

    vendorIEInfo_t vendorIEInfo ;//vendor IEs

    OsiTimer_t timerPeerAgingSample; //timer to sample and send event regarding peer aging
    uint32_t peerAgingTimeout;// in Mili seconds
    DenyList_LinkedList_t denyList; // STA's list of MAC addresses that have denied connection
} ti_driver_ifData_t;

typedef struct
{
    dot11_eleHdr_t *pRatesIe;
    dot11_eleHdr_t *pExtRatesIe;
    dot11_eleHdr_t *pHtCapsIe;
    dot11_eleHdr_t *pHtInfoIe;
} ti_driver_parsedIes_t;


#ifdef CC33XX_DRIVER_DEBUG
typedef struct
{
    uint32_t numAuthAttempts;
    uint32_t numRoc;
    uint32_t numCroc;
    uint32_t gForceDisconnectState;	// For simulating disconnect command in different connection phases,
                                    // Can be set from serial watch during run time.
                                    // TODO - can be removed after CME SM is defined as fully tested
} cc33drv_staDebugInfo_t;

typedef struct
{
    uint32_t numAddSta;
    uint32_t numRemoveSta;
} cc33drv_apDebugInfo_t;

typedef struct
{
        uint32_t numPnReplayDetected;
        uint32_t numMicFailureAes;
        uint32_t numMicFailureTkip;
        uint32_t numAesSwDecryptionNeeded;
        uint32_t numRxFromUnknown;

} cc33drv_commonDebugInfo_t;

typedef struct
{
    cc33drv_staDebugInfo_t sta;     // STA section
    cc33drv_apDebugInfo_t  ap;      // AP section
    cc33drv_commonDebugInfo_t common; //Common section

} cc33drv_debugInfo_t;

extern cc33drv_debugInfo_t gSuppDrvDebugInfo_ull;
#endif

// ============================================================================
//  Driver shared data
// ============================================================================
int cc33xx_cfg_erp_protection (RoleID_t roleID,
                                   Bool_e erpProtectionEnabled);

int cc33xx_config_tx_param  (void *apPriv, AcCfg_t *pParamAc, uint8_t psScheme,
                            Bool_e isMuEdca, uint8_t *pParamMuEdca, uint8_t currAc);

int8_t cc33xx_cfg_assoc_info (RoleID_t roleID,
                                 uint16_t   aid,
                                 Bool_e   wmeEnabled);

int8_t cc33xx_cfg_peer_cap       (RoleID_t roleID,
                                   PeerCap_t* pParam,
                                   uint32_t localSupportedRates);

int8_t cc33xx_cfg_bss_cap        (RoleID_t roleID,
                                   BssCap_t* pParam);

int cc33xx_cfg_slot_time      (RoleID_t roleID,
                                   SlotTime_e slotTime);

int cc33xx_cfg_preamble (RoleID_t roleID,
                             Bool_e shortBPreambleSupported);

int cc33xx_set_beacon_info(uint32_t aRoleId,
                                   struct wpa_driver_ap_params *beacon);

int cc33xx_set_key (SetKey_t *pParam);

// ============================================================================
//  Packets parsing utilities
// ============================================================================
void readErpFlag(struct ieee802_11_elems *apParsedElems,    // IN  - points to parsed received packet
                 Bool32 *apUseProtection,                   // OUT - whether protection is required
                 Bool32 *apShortBarkerPreamble);            // OUT - whether short barker is required

int32_t getWmmConfig(struct ieee802_11_elems *apParsedElems,  // IN  - points to parsed received packet
                  dot11_WME_PARAM_t *apWMEParamIE,          // OUT - QOS parsed params
                  dot11_WSC_t       *apWSCIE);              // OUT - QOS parsed params

// ============================================================================
//  Driver internal utilities
// ============================================================================

/* ----------------------------------------------------------------------------
 drv_getDrvRoleType
    Translate interface name to role type

 Parameters:    apDrv - pointer to driver DB
 Return code:   role type
---------------------------------------------------------------------------- */
RoleType_e drv_getDrvRoleType(ti_driver_ifData_t *apDrv);

/* ----------------------------------------------------------------------------
 cc33drv_getDriverData
    Returns pointer to the driver data corresponding to the specific interface.
    If interface does not exists, return NULL

 Parameters:    ifname - interface name
 Return code:   driver interface data pointer
---------------------------------------------------------------------------- */
ti_driver_ifData_t * drv_getDriverData(const char *ifname);

/* ----------------------------------------------------------------------------
 drv_getDriverFromDescriptor
      This function return pointer for driver from descriptor.

 Parameters: 	aDescriptorId - received packet descriptor
 Return code:	pointer to drive instance
---------------------------------------------------------------------------- */
ti_driver_ifData_t * drv_getDriverFromDescriptor(void *descriptor);

/* ----------------------------------------------------------------------------
 ti_drv_setApAssocInfo
    After associate and connect configure the FW with the associate data

 Parameters:    apDrv - pointer to driver DB
 Return code:   none
---------------------------------------------------------------------------- */
void ti_drv_setApAssocInfo(ti_driver_ifData_t    *apDrv);

/* ----------------------------------------------------------------------------
 ti_drv_setApInfo
    Keep AP info received in asociation response to local STA DB

 Parameters:    apDrv - pointer to driver DB
                apParsedElems - parsed received IEs
                apMngPack - received assoc response packet
                aPackLen - packet length
 Return code:   none
---------------------------------------------------------------------------- */
void ti_drv_setApInfo(ti_driver_ifData_t    *apDrv,
                       struct ieee802_11_elems *apParsedElems,
                       struct ieee80211_mgmt   *apMngPack,
                       uint32_t                  aPackLen);

/* ----------------------------------------------------------------------------
 utilsDumpHex
    Utility for dumping TX/RX packets

 Parameters:    apBuff - pointer to buffer to be printed
                aLen - number of bytes to print
 Return code:   0 - success
---------------------------------------------------------------------------- */
void utilsDumpHex(const uint8_t *apBuff, uint32_t aLen);

/* ----------------------------------------------------------------------------
 utilsDumpScanResult
    Dump scan result fields

 Parameters:    apResult - pointer to scan result
 Return code:   none
---------------------------------------------------------------------------- */
void utilsDumpScanResult(struct wpa_scan_res *apResult);

/* ----------------------------------------------------------------------------
 convertRatesToBitmap
    This API converts rates array to rates bitmaps (defined in rates.h)

 Parameters:  IN  apSupportedRates - supplicant supported rates
              IN  apBasicRates - supplicant basic rates
              OUT apRateParams - conversion product in terms of rates bit masks

 Return code: 0 - OK, -1 - missing parameters
---------------------------------------------------------------------------- */
int32_t convertRatesToBitmap(struct hostapd_rate_data *apSupportedRates,
                           int           *apBasicRates,
                           apRatesSets_t *apRateParams);

/* ----------------------------------------------------------------------------
 convertBitmapToRatesIe
    This API creates rates IE from rates bitmask (defined in rates.h).
    Created IE includes element ID, length and an array of rates (in terms of
    500kbps).

 Parameters:  IN  aSupportedRatesBM - bitmap of supported rates
              IN  aBasicRatesBM - bitmap of basic rates
              OUT apRatesBuff - buffer for conversion result (size must be DOT11_MAX_SUPPORTED_RATES)

 Return code: number of bytes added to IE
---------------------------------------------------------------------------- */
uint32_t convertBitmapToRatesIe(uint32_t aSupportedRatesBM,
                              uint32_t aBasicRatesBM,
                              uint8_t *apRatesBuff);

/* ----------------------------------------------------------------------------
 convertBitmapToSupplicantRates
    This API translates rates bitmask (defined in rates.h) to an array of rates
    described in 100kbps terms.

 Parameters:  IN  aSupportedRatesBM - bitmap of supported rates
              OUT apRatesBuff - buffer for conversion result (size must be DOT11_MAX_SUPPORTED_RATES)

 Return code: total number of supported rates
---------------------------------------------------------------------------- */
uint32_t convertBitmapToSupplicantRates(uint32_t aSupportedRatesBM,
                                      int    *apRatesBuff);

/* ----------------------------------------------------------------------------
 convertNetRatesToBitmap
    This API converts network rates array to rates bit mask (nased on RateIndex_e)

 Parameters:  IN apRatesIe - pointer to rates array
              IN aNumRates - number of rates in array

 Return code: rates bit mask
---------------------------------------------------------------------------- */
uint32_t convertNetRatesToBitmap(const uint8_t *apRatesIe, uint32_t aNumRates);

/* ----------------------------------------------------------------------------
 validateRateVsBand
    This API verifies supported and based rates are correct:
       - For A band it removes B rates from supported rates BM
       - If basic rate set empty (no shared rates between us & peer) it sets
         a subset of basic rates.

 Parameters:  IN  aBand - peer's band
              OUT aSupportedRatesBM - supported rate BM
              OUT aBasicRatesBM - basic rate BM

 Return code: number of bytes added to IE
---------------------------------------------------------------------------- */
void validateRateVsBand (RadioBand_e aBand,
                         uint32_t *aSupportedRatesBM,
                         uint32_t *aBasicRatesBM);

/* ----------------------------------------------------------------------------
 getPeerRates
    This API supplies peer rates based on received rates IE, ext rates IE & HT IEs
    and on chip STA supported rates.

 Parameters:  IN  apCandidateDesc - scan result holding peer IEs
              OUT apLinkRates - peer basic & supported rates

 Return code: none
---------------------------------------------------------------------------- */
void getPeerRates(cmeScanCandidateDesc_t *apCandidateDesc, rateSets_t *apLinkRates);

/* ----------------------------------------------------------------------------
 getPeerIes
    This API parses received beacon/probe response and retruns a structure with
    pointers to rates IE, ext rates IE & HT IEs. These IEs are parsed when
    building start role parameters.

 Parameters:  IN  apCandidateDesc - scan result holding peer IEs
              IN/OUT apPeerIes - pointer to a stucture with required IEs pointers

 Return code: none
---------------------------------------------------------------------------- */
void getPeerIes(cmeScanCandidateDesc_t *apCandidateDesc, ti_driver_parsedIes_t *apPeerIes);


/**********************************************************************************/
/**
 * \brief   fills the nab tx header
 * *
 * \param   TMgmtPktDesc    pkt
---------------------------------------------------------------------------- */

void set_nab_tx_header(NAB_tx_header_t *pNabTxHeader, uint32_t total_len );


// ============================================================================
//  Packets allocation and initialization
// ============================================================================

/* ----------------------------------------------------------------------------
 cc33drv_AllocAndConfigTXDataPack
      Allocate a packet descriptor and set TX parameters
      (role ID, packet type, payload size)
      Allocation takes into account also payload size and optional security fields.

 Parameters:    IN aRoleId
                IN apPayload - pointer to payload buffer
                OUT apSendReq - pointer to sender structure, to be handed to LTXP
 Return code:   on sucees - 0
                on failure - -1
---------------------------------------------------------------------------- */
// TODO: need to implement
#if 0
int32_t cc33drv_AllocAndConfigTXDataPack(uint32_t aRoleId,
                                       const uint8_t  *apPayload,
                                       uint32_t aPayloadSize,
                                       ltxpSendFrameRequest_t *apSendReq);

/* ----------------------------------------------------------------------------
 cc33drv_AllocAndConfigMngPack
      Allocate a packet descriptor and set TX parameters
      (role ID, packet type, payload size)
      Allocation takes into account also payload size and optional security fields.
      For convinience, caller gets a pointer to 802.11 header.

 Parameters:    IN Role ID
                IN Payload size
                IN Packet type
                IN Indication to PMAC whether to Keep packet after TX exchange
                (TRUE - keep, FALSE - release)
                OUT apDescId - pointer to allocated descriptor ID
                OUT Pointer to management packet header
                OUT Pointer to packet descriptor
                OUT apSendReq - pointer to sender structure, to be handed to LTXP

 Return code:   on sucees - 0
                on failure - -1
---------------------------------------------------------------------------- */

int32_t cc33drv_AllocAndConfigMngPack(uint32_t aRoleId,
                                    uint32_t aPayloadSize,
                                    uint32_t aType,
                                    Bool32 aKeepAfterTx,
                                    uint8_t  *apDescId,
                                    struct  ieee80211_mgmt **apMngPack,
                                    CC33_FrameTxDesc_t     **apDescriptor,
                                    ltxpSendFrameRequest_t *apSendReq);
#endif
// ============================================================================
//	Management packets transmission
// ============================================================================

// missing handling for packet types:
//	AP only
//	 WLAN_FC_STYPE_ASSOC_RESP
//	 WLAN_FC_STYPE_REASSOC_RESP
//	 WLAN_FC_STYPE_PROBE_RESP
//	 WLAN_FC_STYPE_BEACON

//	 WLAN_FC_STYPE_PROBE_REQ - packet is constructed in wlcore as part scan handling
//	 WLAN_FC_STYPE_ACTION - TODO - define how we send BA related packets
//	 WLAN_FC_STYPE_ATIM - ibss, irrelevant

/* ----------------------------------------------------------------------------
 ti_drv_AuthTimeout
    This function handles timeout event on reception of expected authentication
    response packet.

 Parameters:    apDrv - pointer to driver instance
                apData2 - aPointer to optional second pointer
                          (defined by eloop timeout handler prototype)
 Return code:   none
---------------------------------------------------------------------------- */
void ti_drv_AuthTimeout(void *apDrv, void *apData2);

/* ----------------------------------------------------------------------------
 ti_drv_AssocTimeout
    This function handles timeout event on reception of expected association
    response packet.

 Parameters:    apDrv - pointer to driver instance
                apData2 - aPointer to optional second pointer
                          (defined by eloop timeout handler prototype)
 Return code:   none
---------------------------------------------------------------------------- */
void ti_drv_AssocTimeout(void *apDrv, void *apData2);

/* ----------------------------------------------------------------------------
 ti_drv_txAuthReqPacket
	Build and send the authentication request packet (w/o 802.11 header).
	Packet is constucted on MMU memory in order to avoid extra copy operations.
	Code is based on NLCP code for wpa_drv_authenticate

 Parameters: 	apDrv - pointer to driver instance
				aAuthType - authentication type (in 802.11 terms, see authType_e)
 Return code:   status
---------------------------------------------------------------------------- */
int32_t ti_drv_txAuthReqPacket(ti_driver_ifData_t *apDrv, uint16_t aAuthType);

/* ----------------------------------------------------------------------------
 ti_drv_txAuthResPacket
    Build and send the authentication response packet (w/o 802.11 header).
    Packet is constucted on MMU memory in order to avoid extra copy operations.

 Parameters:    apDrv - pointer to driver instance
                uint8_t* destAddr - destination address
                uint16_t authType - authentication type (in 802.11 terms, see authType_e)
                uint16_t auth_transaction - authentication transaction
                uint16_t statusCode  - WLAN status code
                const uint8_t* extra - const pointer to the extra element (the challenge)
                size_t extra_len - length of the data pointed to by extra (includes element ID, length, and value)
                int encrypt - Set to 1 if encryption of the data pointed to by extra is required
 Return code:   status
---------------------------------------------------------------------------- */
int32_t ti_drv_txAuthResPacket(ti_driver_ifData_t *apDrv, uint8_t* destAddr, uint16_t authType, uint16_t auth_transaction, uint16_t statusCode,
                             const uint8_t* extra, size_t extra_len, int encrypt);

/* ----------------------------------------------------------------------------
 ti_drv_txAssocReqPacket
	Build and send the association request packet (w/o 802.11 header).
	Packet is constucted on MMU memory in order to avoid extra copy operations.

 Parameters: 	apDrv - pointer to driver instance
                apParams - association parameters
 Return code:   status
---------------------------------------------------------------------------- */
int32_t ti_drv_txAssocReqPacket(ti_driver_ifData_t *apDrv,
                              struct wpa_driver_associate_params *apParams);

/* ----------------------------------------------------------------------------
 ti_drv_AssocReqCB
    A call back function used by PMAC to notify association request packet was
    completed (either sent or timeout)

 Parameters:    aDescId - transmitted descriptor ID

 Return code:   TRUE - caller should release the packet
                FALSE - packet should be kept for further usage
---------------------------------------------------------------------------- */
Bool32 ti_drv_AuthReqCB(void *aDesc, void *apDrv);
Bool32 ti_drv_AssocReqCB(void *aDesc, void *apDrv);


/* ----------------------------------------------------------------------------
 ti_drv_txDeauthDisassocPacket
	Build and send the deauthentication/disassociation packet (w/o 802.11 header).
	Packet is constucted on MMU packet in order to avoid extra copy operations.

 Parameters: 	apDrv - pointer to driver instance
 	 	 	 	apBssid - BSSID of the AP to disconnect from
 	 	 	 	aType - type of disconnection packet (deauth/disassoc)
 	 	 	 	aReason - reason code

 Return code:   0 on success, -1 otherwise
---------------------------------------------------------------------------- */
int32_t ti_drv_txDeauthDisassocPacket(ti_driver_ifData_t *apDrv,
                                    uint8_t  *apBssid,
                                    uint32_t aType,
                                    uint16_t aReason);


// ============================================================================
//	Management packets reception
// ============================================================================

// missing handling for packet types:
//	AP mode
//		WLAN_FC_STYPE_ASSOC_REQ
//		WLAN_FC_STYPE_REASSOC_REQ
//		WLAN_FC_STYPE_AUTH
//		WLAN_FC_STYPE_DEAUTH
//		WLAN_FC_STYPE_PROBE_REQ
//	WLAN_FC_STYPE_PROBE_RESP
//	WLAN_FC_STYPE_BEACON
//	WLAN_FC_STYPE_ATIM - ibss, irrelevant
//	WLAN_FC_STYPE_ACTION

/* ----------------------------------------------------------------------------
 ti_drv_rxAuthResponsePacket
	Parse received authentication response packet (w/o 802.11 header).
	Code is based on NLCP code, mlme_event_auth

 Parameters: 	apDrv - pointer to driver instance
 	 	 	 	apMngPack - pointer to received packet header
 	 	 	 	aPackLen - number of bytes in packet, including 80211 header

 Return code:   operation result, indicating what should happen next
---------------------------------------------------------------------------- */
rxMngPackNextOperation_e ti_drv_rxAuthResponsePacket(
									ti_driver_ifData_t  *apDrv,
                           	   	    struct ieee80211_mgmt *apMngPack,
                           	   	    uint32_t                aPackLen);

/* ----------------------------------------------------------------------------
 ti_drv_rxAssocResponsePacket
	Parse received association response packet (w/o 802.11 header).
	Code is based on NLCP code, mlme_event_auth

 Parameters: 	apDrv - pointer to driver instance
 	 	 	 	apMngPack - pointer to received packet header
 	 	 	 	aPackLen - number of bytes in packet, including 80211 header
 	 	 	 	aIsReassoc - TRUE indicates reassociation

 Return code:   operation result, indicating what should happen next
---------------------------------------------------------------------------- */
rxMngPackNextOperation_e ti_drv_rxAssocResponsePacket(
									ti_driver_ifData_t  *apDrv,
                           	   	    struct ieee80211_mgmt *apMngPack,
                           	   	    uint32_t                aPackLen,
                           	   	    Bool32                aIsReassoc,
                           	   	    void*                 desc);

/* ----------------------------------------------------------------------------
 ti_drv_checkUnprotectedDeauthDisassocEventCriteria
	Checks if the criteria for sending an unprotected deauthentication or 
     disassociation event are met for the received frame. 
     This occurs when a station receives an individually addressed unprotected 
     deauthentication or disassociation frame with reason code 
     WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA or 
     WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA while PMF is enabled for the connection.

 Parameters: 	apDrv - pointer to driver instance
 	 	 	 	apMngPack - pointer to received packet header

 Return code:   TRUE if the criteria are met, FALSE otherwise
---------------------------------------------------------------------------- */
Bool_e ti_drv_checkUnprotectedDeauthDisassocEventCriteria(
                                             ti_driver_ifData_t  *apDrv,
						               struct ieee80211_mgmt *apMngPack);

/* ----------------------------------------------------------------------------
 ti_drv_rxDeauthPacket
	Parse received deauthentication packet (w/o 802.11 header).
	Code is based on NLCP code, mlme_event_auth

 Parameters: 	apDrv - pointer to driver instance
 	 	 	 	apMngPack - pointer to received packet header
 	 	 	 	aPackLen - number of bytes in packet, including 80211 header

 Return code:   operation result, indicating what should happen next
---------------------------------------------------------------------------- */
rxMngPackNextOperation_e ti_drv_rxDeauthPacket(
								   ti_driver_ifData_t  *apDrv,
								   struct ieee80211_mgmt *apMngPack,
								   uint32_t                aPackLen);

/* ----------------------------------------------------------------------------
 ti_drv_rxDisassocPacket
	Code is based on NLCP code, mlme_event_auth

 Parameters: 	apDrv - pointer to driver instance
 	 	 	 	apMngPack - pointer to received packet header
 	 	 	 	aPackLen - number of bytes in packet, including 80211 header

 Return code:   operation result, indicating what should happen next
---------------------------------------------------------------------------- */
rxMngPackNextOperation_e ti_drv_rxDisassocPacket(
								   ti_driver_ifData_t  *apDrv,
								   struct ieee80211_mgmt *apMngPack,
								   uint32_t                aPackLen);


/* ----------------------------------------------------------------------------
 cc33drv_ti_drv_rxSaQueryPacket


 Parameters:    apDrv - pointer to driver instance
                apMngPack - pointer to received packet header
                aPackLen - number of bytes in packet, including 80211 header

 Return code:   operation result, indicating what should happen next
---------------------------------------------------------------------------- */
/*static*/ rxMngPackNextOperation_e ti_drv_rxSaQueryPacket(
                                            ti_driver_ifData_t  *apDrv,
                                            struct ieee80211_mgmt *apMngPack,
                                            uint32_t                aPackLen);

/* ----------------------------------------------------------------------------
 drv_sendConnectTimeoutEvent
    Send association/authentication timeout event to supplicant.
    Association timeout:
        activated when association timer expires or if received response is not
        complete (no rates IE).
    Authentication timeout:
        activated when authentication timer expires and number of auth retries
        exceeds maximal reties

 Parameters:    apDrv - pointer to driver instance
                aType - event type (association/authentication)
                apBssid - peer BSSID

 Return code:   none
---------------------------------------------------------------------------- */
void drv_sendConnectTimeoutEvent(ti_driver_ifData_t  *apDrv,
                                     enum wpa_event_type        aType,
                                     uint8_t                 *apBssid);


/* ----------------------------------------------------------------------------
 drv_handleGroupRole

 Parameters:    apDrv - pointer to driver instance of device type

 Return code:   none
---------------------------------------------------------------------------- */
void drv_handleGroupRole(struct wpa_supplicant *wpa_s, Bool_e isGroupRoleGo);



// ============================================================================
//	Internal management functions
// ============================================================================

/* ----------------------------------------------------------------------------
 destroyAuthData
      This function disconnects from current AP (if needed) and frees auth info
      memory.

 Parameters: 	apDrv - pointer to drive instance
 	 	 	 	aClearBssid - when TRUE, clear current BSSID
 Return code:	none
---------------------------------------------------------------------------- */
void destroyAuthData(ti_driver_ifData_t *apDrv, Bool32 aClearBssid);

/* ----------------------------------------------------------------------------
 destroyAssocData
      This function disconnects from current AP (if needed) and frees assoc info
      memory.
      Based on NLCP mac80211\mlme.c, ieee80211_destroy_assoc_data
      Activated from:
      	  - ieee80211_rx_mgmt_assoc_resp in case of:
      	  	  	 o   success indication
      	  	  	 o   complete failure (for temporary failure there's another trial)
      	  - ieee80211_sta_work:
      	         o   if assoc timeout & no beacon was received from the AP or
      	             number of assoc retries exceeds maximal reties
      	  - interface is stopped

 Parameters: 	apDrv - pointer to drive instance
 	 	 	 	aDisassoc - when TRUE, deauthenticae from current AP
 Return code:	none
---------------------------------------------------------------------------- */
void destroyAssocData(ti_driver_ifData_t *apDrv, Bool32 aDisassoc);

/* ----------------------------------------------------------------------------
 clear_assoc_req_ies
      This function frees the association request IEs buffer and resets its length.

 Parameters: 	apDrv - pointer to drive instance

 Return code:	none
---------------------------------------------------------------------------- */
void clear_assoc_req_ies(ti_driver_ifData_t *apDrv);

/* ----------------------------------------------------------------------------
 finalizeStaDisconnect
      This function completes the disassociation process in FW layer.
      In NLCP this includes:
       	   - stop polling connection state
       	   - tear down BA session
       	   - stopping TX queues
       	   - sending deauth/disassoc packet
       	   - resetting HT capabilities
       	   - stopping ARP filtering
       	   - deleting related timers
      Based on NLCP mac80211\mlme.c, ieee80211_set_disassoc

 Parameters: 	apDrv - pointer to drive instance
                aCaller - debug info

 Return code:	none
---------------------------------------------------------------------------- */
void finalizeStaDisconnect(ti_driver_ifData_t *apDrv, uint32_t aCaller);

/* ----------------------------------------------------------------------------
 markDisconnected
      This function marks on driver DB that the specified role is dosconnected.
      It is imported from driver_nl80211.c

 Parameters: 	apDrv - pointer to drive instance
 	 	 	 	aCaller - for debug
 Return code:	none
---------------------------------------------------------------------------- */
void markDisconnected(ti_driver_ifData_t *apDrv, uint32_t aCaller);

/* ----------------------------------------------------------------------------
 try2authenticate
	Manage authentication trials:
       	   - manage retires (counter & arming a timer for retry)
       	   - if missing peer probe response, send probe request

 Parameters: 	apDrv
 Return code:   0 - handling succeeded, -1 - for max retries
---------------------------------------------------------------------------- */
int32_t try2authenticate(ti_driver_ifData_t *apDrv);

/* ----------------------------------------------------------------------------
 try2associate
    Manage association trials:
           - manage retires (counter & arming a timer for retry)

 Parameters:    apDrv
                apParams - association parameters
 Return code:   0 - handling succeeded, -1 - for max retries
---------------------------------------------------------------------------- */
int32_t try2associate(ti_driver_ifData_t *apDrv, struct wpa_driver_associate_params *apParams);



/* ----------------------------------------------------------------------------
 setWmeSiteParams
    Set Wmm site Params 

 Parameters:    apWmeParamIE - WMM params
                apParams - association parameters
 Return code:   0 - handling succeeded, -1 - for fail
---------------------------------------------------------------------------- */
int32_t setWmeSiteParams(dot11_WME_PARAM_t *apWmeParamIE, RolePostAssocParameters_t *apParams);

/* ----------------------------------------------------------------------------
 stopStaRole
	Prepare and send the stop role command.
	The code is based on WL8 NLCP driver. Command is originated in wlcore\main.c
	when handling BSS info changed notification:
		if BSS_CHANGED_BSSID is set and BSSID equals zero - move to minimal
		supported rates and stop the role.
	Notifier may be ieee80211_destroy_auth_data or ieee80211_destroy_assoc_data
	which clear BSSID from sdata->u.mgd.bssid just before notifying the wlcore layer.

 Parameters: 	apDrv
 Return code:   0 - success, -1 - error in memory allocation
---------------------------------------------------------------------------- */
int32_t stopStaRole(ti_driver_ifData_t *apDrv);

/* ----------------------------------------------------------------------------
 startDevOffchannelRole

 for off channel , create device role, enable the role and send action frame if required

 Parameters:    apDrv - the private data of the AP
 Parameters:    aFreq  -- the required freq of the device role

 Return code:   0 - success, -1 - error in memory allocation
---------------------------------------------------------------------------- */
int32_t startDevOffchannelRole(void *apPriv, uint32_t aFreq);

/* ----------------------------------------------------------------------------
 stopDevOffchannelRole

 for off channel , stop device role and free all allocations

 Parameters:    apDevPriv - the private data of the off channel device

 Return code:   0 - success, -1 - error in memory allocation
---------------------------------------------------------------------------- */
int32_t stopDevOffchannelRole(void *apDevPriv);

/* ----------------------------------------------------------------------------
 startDeviceRole
    Device start role command.

 Parameters:    apDrv - pointer to device driver
                aFreq - frequency channel of operational channel (0 - autoselection)
 Return code:   0 - on success, -1 - error in memory allocation
---------------------------------------------------------------------------- */
int32_t startDeviceRole(void *apPriv, uint32_t aFreq);

/* ----------------------------------------------------------------------------
 stopDeviceRole
    Send stop Device role to WLAN services and wait blocking till operation is
    fully completed and all role resources are released

 Parameters:    apDrv
 Return code:   0 - success
---------------------------------------------------------------------------- */
int32_t stopDeviceRole(ti_driver_ifData_t *apDrv);
/* ----------------------------------------------------------------------------
 cc33_driver_remain_on_channel

 Parameters:    apPriv - pointer to driver private data
                aFreq
                aDuration
 Return code:   0 - success
---------------------------------------------------------------------------- */
int cc33_driver_remain_on_channel(void *apPriv, unsigned int aFreq, unsigned int aDuration);

/* ----------------------------------------------------------------------------
 cc33_driver_cancel_remain_on_channel

 Parameters:    apPriv - pointer to driver private data
 Return code:   0 - success
---------------------------------------------------------------------------- */
int cc33_driver_cancel_remain_on_channel(void *apPriv);

/* ----------------------------------------------------------------------------
 cc33_driver_start_security_mgmt_seq

 Parameters:    apPriv - pointer to driver private data
 Return code:   0 - success
---------------------------------------------------------------------------- */
int cc33_driver_start_security_mgmt_seq(RoleID_t    aRoleId);

/* ----------------------------------------------------------------------------
 ti_driver_start_security_mgmt_seq

 Parameters:    apPriv - pointer to driver private data
 Return code:   0 - success
---------------------------------------------------------------------------- */
int ti_driver_start_security_mgmt_seq(RoleID_t    aRoleId);

// ============================================================================
//      STA role related APIs
// ============================================================================

/* ----------------------------------------------------------------------------
 ti_driver_authenticate
      This function handles authentication request from wpa_supplicant.
      Flow is based on NLCP driver.

 Parameters:    apPriv - pointer to drive instance
                apParams - peer parameters
 Return code:   0 - on success, -1 - failure in sanity tests

 MCP note:
      There's no equivalent code in driver_wilink since connection is managed by
      MCP internal SME.
      The auth packet is constructed in mlme_authMsgBuild.
      All management packets are sent using mlmeBuilder_sendFrame which allocates
      a management packet and builds the 802.11 header (sets mng type, MAC addresses, flags ...)
---------------------------------------------------------------------------- */
int ti_driver_authenticate(void *apPriv, struct wpa_driver_auth_params *apParams);

/* ----------------------------------------------------------------------------
 ti_driver_deauthenticate
      This function handles a deauthentication request from wpa_supplicant.
      Flow is based on NLCP driver.

 Parameters:    apPriv - pointer to drive instance
                apBssid - BSSID to connect from
                aReasonCode - reason to be sent to peer
 Return code:   0 - on success, -1 - failure in sanity tests
---------------------------------------------------------------------------- */
int ti_driver_deauthenticate(void *apPriv, const u8 *apBssid, u16 aReasonCode);

/* ----------------------------------------------------------------------------
 cc33_driver_associate
      This function sends association request packet based on supplciant parameters

 Parameters:    apPriv - pointer to drive instance
                apParams - peer parameters
 Return code:   0 - on success, -1 - failure in sanity tests
---------------------------------------------------------------------------- */
int ti_driver_associate(void *apPriv,struct wpa_driver_associate_params *apParams);

/* ----------------------------------------------------------------------------
 ti_driver_get_bssid
      This API serves for STA role only.
      If STA is connected, it returns the BSSID of currently connected AP.
      Else it returns 00:00:00:00:00:00

 Parameters:    IN  apPriv - Pointer to driver object
                OUT apBssid - Pointer to current BSSID
 Return code:   0 - BSSID is valid; -1 - else
---------------------------------------------------------------------------- */
int ti_driver_get_bssid(void *apPriv, u8 *apBssid);

/* ----------------------------------------------------------------------------
 ti_driver_get_ssid
      This API serves for STA role only.
      If STA is connected, it returns the SSID of currently connected AP.
      Else it returns NULL

 Parameters:    IN  apPriv - Pointer to driver object
                OUT apSsid - Pointer to current SSID string
 Return code:   SSID length - if STA is associated; 0 - else
---------------------------------------------------------------------------- */
int ti_driver_get_ssid(void *apPriv, u8 *apSsid);

/* ----------------------------------------------------------------------------
 ti_driver_add_pmkid
    This API serves for STA role only.
    If STA is connected with WPA3 to the AP, it returns the PMKID.
    Else it returns NULL

 Parameters:    IN  apPriv - Pointer to driver object
                OUT pmkid  - Pointer to current PMKID cache
 Return code:   
---------------------------------------------------------------------------- */
int ti_driver_add_pmkid(void *apPriv, struct wpa_pmkid_params *pmkid);

// ============================================================================
//      AP role related APIs
// ============================================================================

/* ----------------------------------------------------------------------------
 ti_driver_set_ap
      This function stores AP configuration local DB.
      Configuration is set on role DB just before starting the role (in commit API)

 Parameters:    apPriv - pointer to drive instance
                apParams - peer parameters
 Return code:   0 - on success, -1 - failure in sanity tests
---------------------------------------------------------------------------- */
int ti_driver_set_ap(void *apPriv, struct wpa_driver_ap_params *apParams);

/* ----------------------------------------------------------------------------
 cc33_driver_commit
      This function kicks the AP role upon supplicant request.
      AP configuration should be ready at this point as supplicant configured
      parameters are stored directly to role DB.

 Parameters:    apPriv - pointer to private driver DB
 Return code:   0 (success)
---------------------------------------------------------------------------- */
int cc33_driver_commit(void *apPriv);

/* ----------------------------------------------------------------------------
 ti_driver_set_channel
      This function configures AP's operating channel

 Parameters:    apPriv - pointer to private driver DB
                apFreq -pointer to channel and BW configuration
 Return code:   0 on success, -1 on failure (illegal parameters)
---------------------------------------------------------------------------- */
int ti_driver_set_channel(void *apPriv, struct hostapd_freq_params *apFreq);

/* ----------------------------------------------------------------------------
 ti_driver_update_channel_max_tx_power
      Updates mode->channels[].max_tx_power for the specified channel.
      Used to ensure Country IE reflects the configured TX power.

 Parameters:    pDrv - pointer to driver instance
                channel - channel number to update
                max_tx_power - TX power in dBm
 Return code:   none
---------------------------------------------------------------------------- */
void ti_driver_update_channel_max_tx_power(ti_driver_ifData_t *pDrv, uint8_t channel, int8_t max_tx_power);

/* ----------------------------------------------------------------------------
 ti_driver_set_tx_queue_params
      This function sets TX parameters for a specific queue ID

 Parameters:    apPriv - pointer to private driver DB
                queue - Queue number (0 = VO, 1 = VI, 2 = BE, 3 = BK)
                parameters to set
 Return code:   0
---------------------------------------------------------------------------- */
int ti_driver_set_tx_queue_params(void *apPriv, int queue, int aifs,
                                    int cw_min, int cw_max, int burst_time);

/* ----------------------------------------------------------------------------
 ti_driver_set_rts
      This function set RTS threshold for AP role

 Parameters:    apPriv - pointer to private driver DB
                aRts - Desired RTS threshold
 Return code:   0 - OK, role found -1 - else
---------------------------------------------------------------------------- */
int ti_driver_set_rts(void *apPriv, int aRts);

/* ----------------------------------------------------------------------------
 ti_driver_hapd_set_ssid
      This function stores the SSID received from supplicant in role AP DB.

 Parameters:    apPriv - pointer to private driver DB
                apBuf - pointer to SSID string
                aLen - SSID length
 Return code:   0 on success, -1 on failure (illegal parameters)
---------------------------------------------------------------------------- */
int ti_driver_hapd_set_ssid(void *apPriv, const u8 *apBuf, int aLen);

/* ----------------------------------------------------------------------------
 ti_driver_sta_add
      This function starts the sequence of adding a new peer to AP.
      This API sets peer configuration on driver DB.

 Parameters:    apPriv - pointer to private driver DB
                apParams - peer parameters
 Return code:   0 - parameters OK, -1 - error indication
---------------------------------------------------------------------------- */
int ti_driver_sta_add(void *apPriv, struct hostapd_sta_add_params *apParams);

/* ----------------------------------------------------------------------------
 ti_driver_sta_set_flags
      This function kicks the operation of adding an already configured STA to AP.
      The command is handled in WLAN services context.

 Parameters:    apPriv - pointer to private driver DB
                apAddr - peer MAC address
                flags
 Return code:   0 - parameters OK, -1 - error indication
---------------------------------------------------------------------------- */
int ti_driver_sta_set_flags(void *apPriv, const u8 *apAddr,
                              unsigned int total_flags, unsigned int flags_or, unsigned int flags_and);

/* ----------------------------------------------------------------------------
 ti_driver_sta_remove
      This function removes a peer from AP

 Parameters:    apPriv - pointer to private driver DB
                apAddr - peer MAC address
 Return code:   0 - parameters OK, -1 - error indication
---------------------------------------------------------------------------- */
int ti_driver_sta_remove(void *apPriv, const u8 *apAddr);

/* ----------------------------------------------------------------------------
 ti_driver_inact_sec
      AP only: This function returns the inactivity duration for a specific sta (in seconds).

 Parameters:    priv - pointer to private driver DB
                addr - peer MAC address

 Return code:   0 - parameters OK, -1 - error indication
---------------------------------------------------------------------------- */
int ti_driver_inact_sec(void *priv, const u8 *addr);

/* ----------------------------------------------------------------------------
 ti_driver_poll_client
      AP only: This function polls a specific station by sending null data to it

 Parameters:    apPriv - pointer to private driver DB
                own_addr - own MAC address
                addr - peer MAC address
                qos - Indicates whether station is QoS station

 Return code:   None
---------------------------------------------------------------------------- */
void ti_driver_poll_client(void *priv, const u8 *own_addr, const u8 *addr, int qos);

/* ----------------------------------------------------------------------------
 ti_driver_sta_deauth
      This function sends deauth packet to a STA connected to local AP

 Parameters:    apPriv - pointer to private driver DB
                own_addr - AP local address
                addr - peer address
                reason - reason to deauthenticate (set on deauth packet)
 Return code:   0 - packet sent to L2, -1 - else
---------------------------------------------------------------------------- */
int ti_driver_sta_deauth(void *apPriv,   const u8 *own_addr,
                           const u8 *addr, u16 reason);

/* ----------------------------------------------------------------------------
 ti_driver_sta_disassoc
      This function sends disassoc packet to a STA connected to local AP

 Parameters:    apPriv - pointer to private driver DB
                own_addr - AP local address
                addr - peer address
                reason - reason to disassociate (set on disassoc packet)
 Return code:   0 - OK, role found -1 - else
---------------------------------------------------------------------------- */
int ti_driver_sta_disassoc(void *apPriv,   const u8 *own_addr,
                             const u8 *addr, u16 reason);

/* ----------------------------------------------------------------------------
 ti_driver_hpad_send_eapol
      This function sends EAPOL packet directly to data path for AP role

 Parameters:
 Return code:   0 on success, -1 on failure (illegal parameters)
---------------------------------------------------------------------------- */
int ti_driver_hpad_send_eapol(void *apPriv, const u8 *apAddr, const u8 *apData,
                                size_t aDataLen, int aEncrypt, const u8 *apOwnAddr,
                                u32 aFlags);

/* -----------------------------------------------------------------------------
 deinit_ap - Deinitialize the AP mode
 @priv: Private driver interface data
 Returns: 0 on success, -1 on failure (or if not supported)

 This function Performs ap role stop.
 --------------------------------------------------------------------------------- */
int ti_driver_deinit_ap(void *apPriv);

/* ----------------------------------------------------------------------------
 * cc33_RxFrame_CheckSessionIsValid
 *      Check if session of a RX packet is valid and the session ID of the packet matches the
 *      session ID of the matched link.
 *      If not, it is a packet received from a previous or closed session.
 * ---------------------------------------------------------------------------*/
// TODO need to implement
#if 0
Bool_e cc33_RxFrame_CheckSessionIsValid(CC33_FrameRxDesc_t *pDesc);

/* ----------------------------------------------------------------------------
 * cc33_TxResult_CheckSessionIsValid
 *      Check if session of a TX result packet is valid and the session ID of the packet matches the
 *      session ID of the matched link.
 *      If not, it is a packet received from a previous or closed session.
 * ---------------------------------------------------------------------------*/
Bool_e cc33_TxResult_CheckSessionIsValid(CC33_FrameTxDesc_t *pDesc);
#endif

/* ----------------------------------------------------------------------------
 ti_driver_send_l2_data
      This function sends an l2 data frame to LTXP.
      802.11 is constructed here, LXTP should not change the packet.

 Parameters:    pDrv - pointer to private driver DB
                dst_addr - destination address
                proto - l2 protocol used
                *pData - data
                dataLen

 Return code:   0 - OK, -1 - failure
---------------------------------------------------------------------------- */
int ti_driver_send_l2_data(ti_driver_ifData_t *pDrv, const u8 *dst_addr,
                             u16 proto, const u8 *pData, size_t dataLen);


/* ----------------------------------------------------------------------------
 cc33_driver_sendSetLinkConnectionState
      Send set Link connection state command to the low priority thread

 Parameters:    lid - link id
                linkConnectionState

 Return code:   0 - OK, -1 - failure
---------------------------------------------------------------------------- */
void cc33_driver_sendSetLinkConnectionState(uint8_t lid, LinkConnectionState_e linkConnectionState);


/*!
    \brief      Send deauthentication / disassociation command to FW

    Send Deauth / disassoc command to wlan lp thread, starting a managed sequence
    of sending a deauth / disassoc frame.
    This is a blocking function. Waits till sequence is completed.

    \param      apDrv - IN/OUT pointer to the driver DB
                pDestAddr - destination address
                frameType - FRAME_TYPE_AUTHENTICATION / FRAME_TYPE_DEAUTHENTICATION
                reason - deauth / disassoc reason

    \return     0 on success, -1 otherwise
*/
int32_t cc33drv_sendDeauthDisassoc(ti_driver_ifData_t *pDrv,
                                 uint8_t  *pDestAddr,
                                 uint32_t frameType,
                                 uint16_t reason);

/* ----------------------------------------------------------------------------
 ti_driver_send_action
      This function sends an action frame to LTXP.
      802.11 is constructed here, LXTP should not change the packet.

 Parameters:    pDrv - pointer to private driver DB
                pDest - destination address
                pData - data
                dataLen

                rest of parameters are not used

 Return code:   0 - OK, -1 - failure
---------------------------------------------------------------------------- */
int ti_driver_send_action(void *pDrv,
                            unsigned int freq,
                            unsigned int waitTime,
                            const u8 *pDest,
                            const u8 *pSrc,
                            const u8 *pBssid,
                            const u8 *pData,
                            size_t dataLen,
                            int    noCck);

int ti_driver_ext_set_CROC(uint8_t calledFromCmeThread,uint32_t is_croc_performed_due_to_timeout);

int ti_driver_ext_set_ROC( uint32_t    channel,
                           uint8_t* countryDomain);

int ti_driver_ext_tx_send_action(
                            const uint8_t  *apDst,            // Destination address
                            const uint8_t  *actionBuff,
                            uint32_t       actionBuffLen);

void ti_driver_send_action_cancel_wait(void *apPriv);
int ti_driver_cancel_remain_on_channel(void *apPriv);
int ti_driver_remain_on_channel(void *apPriv, uint32_t aFreq, uint32_t aDuration);
int ti_driver_stop_remain_on_channel(void *apPriv);
int ti_driver_start_remain_on_channel(void *apPriv, unsigned int aFreq, unsigned int aDuration);
int ti_driver_probe_req_report(void *apPriv, int aReport);
int ti_driver_if_add(void *apPriv, enum wpa_driver_if_type type,
                    const char *ifname, const u8 *addr, void *bss_ctx,
                    void **drv_priv, char *force_ifname, u8 *if_addr,
                    const char *bridge, int use_existing, int setup_ap);
void drv_handleRemainOnChannelEvent(void *apDrv, Bool32 aIsRoc, uint32_t aDurationMS, uint32_t freq);

int32_t  setHtInfoFromBeacon(uint8_t *apBuff, uint32_t aSize, htBssCap_t *htInfo);
uint32_t fillBeaconTemplate(struct wpa_driver_ap_params *apParams, uint8_t *apBuffer);
uint32_t fillProbeRespTemplate(struct wpa_driver_ap_params *apParams, uint8_t *apBuffer);
void* ti_driver_off_channel_device_init(void* apPriv,const char *ifname);
uint32_t fillDeauthTemplate(uint8_t *apBuffer);

int DenyList_initList(DenyList_LinkedList_t* list);
void DenyList_clearList(DenyList_LinkedList_t* list);
int DenyList_elementExists(DenyList_LinkedList_t* list, uint8_t macAddr[MAC_ADDR_LEN], DenyList_Node_t** node);
int DenyList_addElement(DenyList_LinkedList_t* list, uint8_t macAddr[MAC_ADDR_LEN], uint32_t expiryTime);
void DenyList_verifyAndRemoveExpiredElements(DenyList_LinkedList_t* list); 

#endif // _DRV_SUPPLICANT_API_H_



#if 0
enum wpa_event_type {

	mlme_event_assoc - successful assoc response - cc33xx done
	mlme_event_connect net\wireless\sme.c __cfg80211_connect_result - should we use this sme?
	wpa_supplicant_gen_assoc_event - if ap_scan=0, should not happen in cc33xx
EVENT_ASSOC,

	mac802.11\mlme.c - send/receive disassociation packet - cc33xx done
EVENT_DISASSOC,

/**
 * EVENT_MICHAEL_MIC_FAILURE - Michael MIC (TKIP) detected
 *
 * This event must be delivered when a Michael MIC error is detected by
 * the local driver. Additional data for event processing is
 * provided with union wpa_event_data::michael_mic_failure. This
 * information is used to request new encyption key and to initiate
 * TKIP countermeasures if needed.
 */
EVENT_MICHAEL_MIC_FAILURE,

	cc33xx - done
EVENT_SCAN_RESULTS,

	cc33xx - not used, all information is sent in the assoc event
EVENT_ASSOCINFO,

/**
 * EVENT_INTERFACE_STATUS - Report interface status changes
 *
 * This optional event can be used to report changes in interface
 * status (interface added/removed) using union
 * wpa_event_data::interface_status. This can be used to trigger
 * wpa_supplicant to stop and re-start processing for the interface,
 * e.g., when a cardbus card is ejected/inserted.
 */
EVENT_INTERFACE_STATUS,

/**
 * EVENT_PMKID_CANDIDATE - Report a candidate AP for pre-authentication
 *
 * This event can be used to inform wpa_supplicant about candidates for
 * RSN (WPA2) pre-authentication. If wpa_supplicant is not responsible
 * for scan request (ap_scan=2 mode), this event is required for
 * pre-authentication. If wpa_supplicant is performing scan request
 * (ap_scan=1), this event is optional since scan results can be used
 * to add pre-authentication candidates. union
 * wpa_event_data::pmkid_candidate is used to report the BSSID of the
 * candidate and priority of the candidate, e.g., based on the signal
 * strength, in order to try to pre-authenticate first with candidates
 * that are most likely targets for re-association.
 *
 * EVENT_PMKID_CANDIDATE can be called whenever the driver has updates
 * on the candidate list. In addition, it can be called for the current
 * AP and APs that have existing PMKSA cache entries. wpa_supplicant
 * will automatically skip pre-authentication in cases where a valid
 * PMKSA exists. When more than one candidate exists, this event should
 * be generated once for each candidate.
 *
 * Driver will be notified about successful pre-authentication with
 * struct wpa_driver_ops::add_pmkid() calls.
 */
EVENT_PMKID_CANDIDATE,

/**
 * EVENT_STKSTART - Request STK handshake (MLME-STKSTART.request)
 *
 * This event can be used to inform wpa_supplicant about desire to set
 * up secure direct link connection between two stations as defined in
 * IEEE 802.11e with a new PeerKey mechanism that replaced the original
 * STAKey negotiation. The caller will need to set peer address for the
 * event.
 */
EVENT_STKSTART,

/**
 * EVENT_TDLS - Request TDLS operation
 *
 * This event can be used to request a TDLS operation to be performed.
 */
EVENT_TDLS,

/**
 * EVENT_FT_RESPONSE - Report FT (IEEE 802.11r) response IEs
 *
 * The driver is expected to report the received FT IEs from
 * FT authentication sequence from the AP. The FT IEs are included in
 * the extra information in union wpa_event_data::ft_ies.
 */
EVENT_FT_RESPONSE,

	cc33xx - IBSS is not supported
EVENT_IBSS_RSN_STAR

	cc33xx - sucessfully received auth packet
EVENT_AUTH,

	net\wireless\sme.c - __cfg80211_disconnected
	mac80211\mlme.c:
		- connection loss
		- RX deauth - cc33xx done
		- ieee80211_sta_connection_lost
		- send deauth and immediately report to supplicant - cc33xx done
EVENT_DEAUTH,

	mlme_event_connect - TODO
	receive association response with status != OK	- cc33xx done
	receive association response with status = OK but response is incomplete - cc33xx done
EVENT_ASSOC_REJECT,

	in case of recurrent failure to send auth packet to L2 - cc33xx done
	timeout event - cc33xx done
EVENT_AUTH_TIMED_OUT,

	timeout event - received assoc response but couldnt keep peer parameters, for example no rates IE - cc33xx done
EVENT_ASSOC_TIMED_OUT,

NLCP & MCP - not supported
EVENT_FT_RRB_RX,

NLCP & MCP - not supported
EVENT_WPS_BUTTON_PUSHED,

cc33xx - when sending the packet have to set TX exchange CB + ask not to release the packet.
		 when notified, send the event to supplicant - partially done.
EVENT_TX_STATUS,

/**
 * EVENT_RX_FROM_UNKNOWN - Report RX from unknown STA
 */
EVENT_RX_FROM_UNKNOWN,

supplicant handles received management packets only if AP is defined, leave it for now
EVENT_RX_MGMT,

send for registered packets types. It appears no one is registering on management frames.
In any case, only P2P API is activated for this event. Leave it unhandled for now.
EVENT_RX_ACTION,

handled by wpa_supplicant for P2P only.
In NLCP, ROC frequency and duration are retrieved from NLCP DB.
In MCP STA - ROC is sent by connInfra, the SM waits for FW to ack the request.
	cc33xx STA - wait on sync object for lower SW layer to ack the request, no need for this event. Similar to MCP.
For cc33xx we can take the parameters from FW DB.
cc33xx P2P - added CME API + activate driver API + send event to supplicant.
		     Still have to take duration & channel from FW or keep it on driver DB. TODO.
EVENT_REMAIN_ON_CHANNEL,

EVENT_CANCEL_REMAIN_ON_CHANNEL,

MCP & NLCP dont handle this test event
EVENT_MLME_RX,

/**
 * EVENT_RX_PROBE_REQ - Indicate received Probe Request frame
 *
 * This event is used to indicate when a Probe Request frame has been
 * received. Information about the received frame is included in
 * union wpa_event_data::rx_probe_req. The driver is required to report
 * these events only after successfully completed probe_req_report()
 * commands to request the events (i.e., report parameter is non-zero)
 * in station mode. In AP mode, Probe Request frames should always be
 * reported.
 */
not supported by MCP & NLCP.Will not be supported in cc33xx as well.
EVENT_RX_PROBE_REQ,

/**
 * EVENT_NEW_STA - New wired device noticed
 *
 * This event is used to indicate that a new device has been detected
 * in a network that does not use association-like functionality (i.e.,
 * mainly wired Ethernet). This can be used to start EAPOL
 * authenticator when receiving a frame from a device. The address of
 * the device is included in union wpa_event_data::new_sta.
 */
not supported by MCP & NLCP.Will not be supported in cc33xx as well.
EVENT_NEW_STA,

not supported in MCP & NLCP, supported in cc33xx - done
EVENT_EAPOL_RX,

/**
 * EVENT_SIGNAL_CHANGE - Indicate change in signal strength
 *
 * This event is used to indicate changes in the signal strength
 * observed in frames received from the current AP if signal strength
 * monitoring has been enabled with signal_monitor().
 */
EVENT_SIGNAL_CHANGE,

Supported both in NLCp & MCP, related to network interface.
cc33xx - have to understand when exactly the events are sent. TODO.
EVENT_INTERFACE_ENABLED,
EVENT_INTERFACE_DISABLED,

/**
 * EVENT_CHANNEL_LIST_CHANGED - Channel list changed
 *
 * This event is used to indicate that the channel list has changed,
 * e.g., because of a regulatory domain change triggered by scan
 * results including an AP advertising a country code.
 */
Supported only in MCP, event is issued by regulatory domain module when county IE is received or when set county command is received.
cc33xx - is it needed?
EVENT_CHANNEL_LIST_CHANGED,

/**
 * EVENT_INTERFACE_UNAVAILABLE - Notify that interface is unavailable
 *
 * This event is used to indicate that the driver cannot maintain this
 * interface in its operation mode anymore. The most likely use for
 * this is to indicate that AP mode operation is not available due to
 * operating channel would need to be changed to a DFS channel when
 * the driver does not support radar detection and another virtual
 * interfaces caused the operating channel to change. Other similar
 * resource conflicts could also trigger this for station mode
 * interfaces.
 */

NLCP - sent when stop AP command is received, looks irrelevant for cc33xx
EVENT_INTERFACE_UNAVAILABLE,

/**
 * EVENT_BEST_CHANNEL
 *
 * Driver generates this event whenever it detects a better channel
 * (e.g., based on RSSI or channel use). This information can be used
 * to improve channel selection for a new AP/P2P group.
 */
not supported by MCP & NLCP.Will not be supported in cc33xx as well.
EVENT_BEST_CHANNEL,

/**
 * EVENT_UNPROT_DEAUTH - Unprotected Deauthentication frame received
 *
 * This event should be called when a Deauthentication frame is dropped
 * due to it not being protected (MFP/IEEE 802.11w).
 * union wpa_event_data::unprot_deauth is required to provide more
 * details of the frame.
 */
not supported by MCP & NLCP.Will not be supported in cc33xx as well.
EVENT_UNPROT_DEAUTH,

/**
 * EVENT_UNPROT_DISASSOC - Unprotected Disassociation frame received
 *
 * This event should be called when a Disassociation frame is dropped
 * due to it not being protected (MFP/IEEE 802.11w).
 * union wpa_event_data::unprot_disassoc is required to provide more
 * details of the frame.
 */
not supported by MCP & NLCP.Will not be supported in cc33xx as well.
EVENT_UNPROT_DISASSOC,

/**
 * EVENT_STATION_LOW_ACK
 *
 * Driver generates this event whenever it detected that a particular
 * station was lost. Detection can be through massive transmission
 * failures for example.
 */
MCP/NLCP send this event in AP mode for aged STAs or in case of FW TX retry failure indication.
cc33xx - done
EVENT_STATION_LOW_ACK,

/**
 * EVENT_P2P_DEV_FOUND - Report a discovered P2P device
 *
 * This event is used only if the driver implements P2P management
 * internally. Event data is stored in
 * union wpa_event_data::p2p_dev_found.
 */
EVENT_P2P_DEV_FOUND,

/**
 * EVENT_P2P_GO_NEG_REQ_RX - Report reception of GO Negotiation Request
 *
 * This event is used only if the driver implements P2P management
 * internally. Event data is stored in
 * union wpa_event_data::p2p_go_neg_req_rx.
 */
EVENT_P2P_GO_NEG_REQ_RX,

/**
 * EVENT_P2P_GO_NEG_COMPLETED - Report completion of GO Negotiation
 *
 * This event is used only if the driver implements P2P management
 * internally. Event data is stored in
 * union wpa_event_data::p2p_go_neg_completed.
 */
EVENT_P2P_GO_NEG_COMPLETED,

EVENT_P2P_PROV_DISC_REQUEST,
EVENT_P2P_PROV_DISC_RESPONSE,
EVENT_P2P_SD_REQUEST,
EVENT_P2P_SD_RESPONSE,

/**
 * EVENT_IBSS_PEER_LOST - IBSS peer not reachable anymore
 */
EVENT_IBSS_PEER_LOST,

/**
 * EVENT_DRIVER_GTK_REKEY - Device/driver did GTK rekey
 *
 * This event carries the new replay counter to notify wpa_supplicant
 * of the current EAPOL-Key Replay Counter in case the driver/firmware
 * completed Group Key Handshake while the host (including
 * wpa_supplicant was sleeping).
 */
EVENT_DRIVER_GTK_REKEY,

cc33xx - as in MCP, sent when periodic scan is stopped
EVENT_SCHED_SCAN_STOPPED,

/**
 * EVENT_DRIVER_CLIENT_POLL_OK - Station responded to poll
 *
 * This event indicates that the station responded to the poll
 * initiated with @poll_client.
 */
Supported only in NLCP, alternativly TX result is sent via TX management result.
cc33xx - wont be supported.
EVENT_DRIVER_CLIENT_POLL_OK,

/**
 * EVENT_EAPOL_TX_STATUS - notify of EAPOL TX status
 */
Support only in NLCP.
cc33xx - ask PMAC to notify (callback) when EAPOL TX ends
TODO - why isnt it sent in MCP, see xmitMgmtOrEapolPacket where CB for TX EAPOL is set to NULL
EVENT_EAPOL_TX_STATUS,

/**
 * EVENT_CH_SWITCH - AP or GO decided to switch channels
 *
 * Described in wpa_event_data.ch_switch
 * */
EVENT_CH_SWITCH,

MCP/NLCP dont support this event
EVENT_WNM,

/**
 * EVENT_CONNECT_FAILED_REASON - Connection failure reason in AP mode
 *
 * This event indicates that the driver reported a connection failure
 * with the specified client (for example, max client reached, etc.) in
 * AP mode.
 */
Supported only in NLCP,
EVENT_CONNECT_FAILED_REASON,


Supported in NLCP
EVENT_DFS_RADAR_DETECTED,
EVENT_DFS_CAC_FINISHED,
EVENT_DFS_CAC_ABORTED,
EVENT_DFS_NOP_FINISHED,

NLCP - respond to get_survey API. This API is not supported in MCP.
Serves for AP mode only.
EVENT_SURVEY,

Supported only in NLCP, sent in response to beacon loss event.	TODO - is this what we want to do in cc33xx?
EVENT_START_ROAMING,

Supported only in MCP, used to notify supplicant of hand-over
cc33xx -TODO - if roaming is managed by supplicant this event is irrelevant
EVENT_ROAM_TO_SPECIFIC_AP,

Supported only in NLCP ???
cc33xx - should not affect supplicant code.
Have to copy functionality to CME. TODO.
EVENT_SMART_CONFIG_SYNC,
EVENT_SMART_CONFIG_DECODE,



#endif
