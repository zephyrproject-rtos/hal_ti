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
/*--------------------------------------------------------------------------*/
/* Module:		osDot11.h */
/**/
/* Purpose:		*/
/**/
/*--------------------------------------------------------------------------*/
#ifndef __OSDOT11_H__
#define __OSDOT11_H__

#include <public_types.h>


//#define	OS_STATUS_MEDIA_SPECIFIC_INDICATION	((NDIS_STATUS)0x40010012L)
//
//#define OS_802_11_REQUEST_REAUTH					0x01
//#define OS_802_11_REQUEST_KEYUPDATE					0x02
//#define OS_802_11_REQUEST_PAIRWISE_ERROR			0x06
//#define OS_802_11_REQUEST_GROUP_ERROR				0x0E
//
//#define OS_802_11_SSID_FIRST_VALID_CHAR             32
//
//#define OS_802_11_SSID_JUNK(str,len)                   \
//        ((len) > 2 &&                                  \
//         (unsigned char)(str)[0] < OS_802_11_SSID_FIRST_VALID_CHAR && \
//         (unsigned char)(str)[1] < OS_802_11_SSID_FIRST_VALID_CHAR && \
//         (unsigned char)(str)[2] < OS_802_11_SSID_FIRST_VALID_CHAR)
//
//
///**/
///*  Per-packet information for Ieee8021QInfo.*/
///**/
//typedef struct _OS_PACKET_8021Q_INFO
//{
//    union
//    {
//        struct
//        {
//            uint32_t      UserPriority:3;         /* 802.1p priority */
//            uint32_t      CanonicalFormatId:1;    /* always 0*/
//            uint32_t      VlanId:12;              /* VLAN Identification*/
//            uint32_t      Reserved:16;            /* set to 0*/
//        }   TagHeader;
//
//        void*  Value;
//    }u;
//} OS_PACKET_8021Q_INFO, *POS_PACKET_8021Q_INFO;
//
//
//typedef uint64 OS_802_11_KEY_RSC;
//
typedef struct _OS_802_11_SSID
{
    uint32_t SsidLength;
    uint8_t  Ssid[32];
} OS_802_11_SSID, *POS_802_11_SSID;
//
typedef enum _OS_802_11_NETWORK_TYPE
{
  os802_11FH,
  os802_11DS,
  os802_11OFDM5,
  os802_11OFDM24,
  os802_11Automode,
  os802_11NetworkTypeMax
} OS_802_11_NETWORK_TYPE;
//
//typedef struct _OS_802_11_NETWORK_TYPE_LIST
//{
//  uint32_t                  NumberOfItems;
//  OS_802_11_NETWORK_TYPE NetworkType [1];
//} OS_802_11_NETWORK_TYPE_LIST, *POS_802_11_NETWORK_TYPE_LIST;
//
//typedef enum _OS_802_11_POWER_MODE
//{
//  /*Continuous access mode (CAM). */
//  /*When the power mode is set to CAM, the device is always on. */
//  os802_11PowerModeCAM,
//
//  /*Specifies maximum (MAX) power saving. A power mode of MAX */
//  /*results in the greatest power savings for the 802.11 NIC radio. */
//  os802_11PowerModeMAX_PSP,
//
//  /*Specifies fast power-saving mode. This power mode provides */
//  /*the best combination of network performance and power usage. */
//  os802_11PowerModeFast_PSP,
//  os802_11PowerModeMax
//} OS_802_11_POWER_MODE;
//
///*specified in milliwatts (mW).*/
//typedef uint32_t OS_802_11_TX_POWER_LEVEL;
///*Normal value from -10 and -200*/
typedef int32_t OS_802_11_RSSI;

/*Length */

/*  Specifies the length of the OS_802_11_CONFIGURATION_FH structure in bytes. */
/*HopPattern*/
/*  Specifies the hop pattern used to determine the hop sequence. */
/*  As defined by the 802.11 standard, the layer management entity (LME) of */
/*  the physical layer uses a hop pattern to determine the hop sequence. */
/*HopSet*/
/*  Specifies a set of patterns. The LME of the physical layer uses these */
/*  patterns to determine the hop sequence. */
/*DwellTime*/
/*  Specifies the maximum period of time during which the transmitter */
/*  should remain fixed on a channel. This interval is described in Kµsec (1024 µsec). */
typedef struct _OS_802_11_CONFIGURATION_FH
{
    uint32_t  Length;
    uint32_t  HopPattern;
    uint32_t  HopSet;
    uint32_t  DwellTime;
} OS_802_11_CONFIGURATION_FH, *POS_802_11_CONFIGURATION_FH;

typedef struct _OS_802_11_CONFIGURATION

{
    uint32_t Length;               /**<  Specifies the length of the NDIS_802_11_CONFIGURATION structure in bytes. */
    uint32_t BeaconPeriod;         /**<  Specifies the interval between beacon message transmissions. This value is specified in Kµsec(1024 µsec). */
    uint32_t ATIMWindow;           /**<  Specifies the announcement traffic information message (ATIM) window in Kµsec (1024 µsec).
                                          The ATIM window is a short time period immediately after the transmission of each beacon in an IBSS configuration.
                                          During the ATIM window, any station can indicate the need to transfer data to another station
                                         during the following data-transmission window. */
  union
  {
    uint32_t DSConfig;         /**<  Specifies the frequency of the selected channel in kHz. */
    uint32_t channel;          /**<  Specifies the selected channel */
  } Union;
  OS_802_11_CONFIGURATION_FH FHConfig;    /**<  Specifies the frequency hopping configuration in an OS_802_11_CONFIGURATION_FH structure. */
} OS_802_11_CONFIGURATION, *POS_802_11_CONFIGURATION;
//
//
///*Ndis802_11IBSS */
///*  Specifies the independent basic service set (IBSS) mode. */
///*  This mode is also known as ad hoc mode. */
///*Ndis802_11Infrastructure */
///*  Specifies the infrastructure mode. */
///*Ndis802_11AutoUnknown */
///*  Specifies an automatic mode. In this mode, the 802.11 NIC can switch */
///*  between ad hoc and infrastructure modes as required. */
///*Ndis802_11HighSpeedIBSS*/
///*  Specifies proprietary ad hoc mode that works only PBCC.*/
typedef enum _OS_802_11_NETWORK_MODE
{
  os802_11IBSS,
  os802_11Infrastructure,
  os802_11AutoUnknown,
  os802_11HighSpeedIBSS,
  os802_11InfrastructureMax
} OS_802_11_NETWORK_MODE, OS_802_11_NETWORK_INFRASTRUCTURE,*POS_802_11_NETWORK_INFRASTRUCTURE;
//
///**/
///*The rates array contains a set of eight octets. */
///*Each octet contains a desired data rate in units of .5 Mbps.*/
///**/
//typedef uint8_t OS_802_11_RATES[8];

typedef uint8_t OS_802_11_RATES_EX[16];

//typedef uint8_t OS_802_11_N_RATES[32];
//
//typedef struct _OS_802_11_FIXED_IEs
//{
//	uint8_t  TimeStamp[8];
//	uint16_t BeaconInterval;
//	uint16_t Capabilities;
//} OS_802_11_FIXED_IEs, *POS_802_11_FIXED_IEs;
//
//typedef struct _OS_802_11_VARIABLE_IEs
//{
//	uint8_t ElementID;
//	uint8_t Length;	/* Number of bytes in data field*/
//	uint8_t data[1];
//}  OS_802_11_VARIABLE_IEs, *POS_802_11_VARIABLE_IEs;
//
//typedef struct _OS_802_11_BSSID
//{
//  uint32_t Length;
//  TMacAddr                  MacAddress;
//  uint16_t					Capabilities;
//  OS_802_11_SSID            Ssid;
//  uint32_t                 Privacy;
//  OS_802_11_RSSI            Rssi;
//  OS_802_11_NETWORK_TYPE    NetworkTypeInUse;
//  OS_802_11_CONFIGURATION   Configuration;
//  OS_802_11_NETWORK_MODE    InfrastructureMode;
//  OS_802_11_RATES           SupportedRates;
//}  OS_802_11_BSSID, *POS_802_11_BSSID;
//
//typedef struct _OS_802_11_BSSID_LIST
//{
//    uint32_t          NumberOfItems;
//  OS_802_11_BSSID  Bssid[1];
//}  OS_802_11_BSSID_LIST, *POS_802_11_BSSID_LIST;


//typedef struct _OS_802_11_BSSID_EX
//{
//  uint32_t					Length;       /** BSSID length */
//  TMacAddr		            MacAddress;   /** BSSID mac address */
//  uint16_t					Capabilities; /**< According to details in wdrv_mgmtCapabilities_e */
//  OS_802_11_SSID            Ssid;
//  uint32_t                 Privacy;      /** Privecy enable/disable         */
//  OS_802_11_RSSI            Rssi;
//  OS_802_11_NETWORK_TYPE    NetworkTypeInUse;
//  OS_802_11_CONFIGURATION   Configuration;
//  OS_802_11_NETWORK_MODE    InfrastructureMode;
//  OS_802_11_RATES_EX        SupportedRates;
//  uint32_t                 IELength;    /** info elements length */
//  uint8_t                  IEs[1];      /** info elements data */
//} OS_802_11_BSSID_EX/*, *POS_802_11_BSSID_EX, OS_WLAN_BSSID_EX, *POS_WLAN_BSSID_EX*/;

//typedef struct _OS_802_11_BSSID_LIST_EX
//{
//  uint32_t                 NumberOfItems;	/**< Number of BSSIDs in the list	*/
//  OS_802_11_BSSID_EX        Bssid[1];		/**< Each entry represents BSSID	*/
//}  OS_802_11_BSSID_LIST_EX, *POS_802_11_BSSID_LIST_EX;
//
//
//typedef uint32_t OS_802_11_FRAGMENTATION_THRESHOLD;
//typedef uint32_t OS_802_11_RTS_THRESHOLD;
//typedef uint32_t OS_802_11_ANTENNA;
//
//
///*Length */
///*  Specifies the length of the NDIS_802_11_WEP structure in bytes. */
///*KeyIndex */
///*  Specifies which key to add or remove. The global keys are represented */
///*  by values of zero to n. When the most significant bit is set to 1, */
///*  it indicates the key used to transmit to the access point. */
///*KeyLength */
///*  Specifies the length of the KeyMaterial character array in bytes. */
///*KeyMaterial */
///*  Specifies an arraythat identifies the WEP key. The length of this array is */
///*  variable and depends upon the value of the KeyLength member. */
//
//typedef uint32_t OS_802_11_KEY_INDEX;
//typedef struct _OS_802_11_WEP
//{
//    uint32_t Length;
//    uint32_t KeyIndex;
//    uint32_t KeyLength;
//    uint8_t  KeyMaterial [32];
//} OS_802_11_WEP, *POS_802_11_WEP;
//
///* Key mapping keys require a BSSID*/
///*typedef tiUINT64 OS_802_11_KEY_RSC;*/
//
//typedef struct _OS_802_11_KEY
//{
//    uint32_t                  Length;             /* Length of this structure*/
//    uint32_t                  KeyIndex;
//    uint32_t                  KeyLength;          /* length of key in bytes*/
//    TMacAddr                   BSSID;
//    OS_802_11_KEY_RSC          KeyRSC;
//    uint8_t                   KeyMaterial[32];     /* variable length depending on above field*/
//}  OS_802_11_KEY, *POS_802_11_KEY;
//
//typedef struct _OS_802_11_REMOVE_KEY
//{
//    uint32_t                  Length;             /* Length of this structure*/
//    uint32_t                  KeyIndex;
//    TMacAddr                   BSSID;
//} OS_802_11_REMOVE_KEY, *POS_802_11_REMOVE_KEY;
//
//#define OS_802_11_AI_REQFI_CAPABILITIES     1
//#define OS_802_11_AI_REQFI_LISTENINTERVAL   2
//#define OS_802_11_AI_REQFI_CURRENTAPADDRESS 4
//
//
//#define OS_802_11_AI_RESFI_CAPABILITIES     1
//#define OS_802_11_AI_RESFI_STATUSCODE       2
//#define OS_802_11_AI_RESFI_ASSOCIATIONID    4
//
//typedef struct _OS_802_11_AI_REQFI
//{
//	uint16_t Capabilities;
//	uint16_t ListenInterval;
//	TMacAddr  CurrentAPAddress;
//#ifndef _WINDOWS
//    uint16_t reserved; /* added for packing */
//#endif
//} OS_802_11_AI_REQFI;
//
//typedef struct _OS_802_11_AI_RESFI
//{
//	uint16_t Capabilities;
//	uint16_t StatusCode;
//	uint16_t AssociationId;
//#ifndef _WINDOWS
//    uint16_t reserved; /* added for packing */
//#endif
//} OS_802_11_AI_RESFI;
//
//typedef struct _OS_802_11_ASSOCIATION_INFORMATION
//{
//    uint32_t Length;                     /** associasion IE length */
//    uint16_t AvailableRequestFixedIEs;   /** bit map of available request IE (capability, listen interval) */
//    OS_802_11_AI_REQFI RequestFixedIEs;   /** copy of the request Ie */
//    uint32_t RequestIELength;            /** length of Info elements in assoc request  */
//    uint32_t OffsetRequestIEs;           /** Offset to request IEs */
//    uint16_t AvailableResponseFixedIEs;  /** bit map of response Ie (capability , status code, id) */
//    OS_802_11_AI_RESFI ResponseFixedIEs;  /** copy of response Ie */
//    uint32_t ResponseIELength;           /** length of Info elements in assoc response */
//    uint32_t OffsetResponseIEs;          /** Offset to response IEs */
//
//}  OS_802_11_ASSOCIATION_INFORMATION, *POS_802_11_ASSOCIATION_INFORMATION;
//
//
///* supported EAP types*/
//typedef enum _OS_802_11_EAP_TYPES
//{
//    OS_EAP_TYPE_NONE                = -1,
//	OS_EAP_TYPE_MD5_CHALLENGE		= 4,
//	OS_EAP_TYPE_GENERIC_TOKEN_CARD	= 6,
//	OS_EAP_TYPE_TLS					= 13,
//	OS_EAP_TYPE_LEAP				= 17,
//	OS_EAP_TYPE_TTLS				= 21,
//	OS_EAP_TYPE_PEAP				= 25,
//	OS_EAP_TYPE_MS_CHAP_V2			= 26,
//    OS_EAP_TYPE_FAST                = 43
//} OS_802_11_EAP_TYPES;
//
///* encryption type*/
//typedef enum _OS_802_11_ENCRYPTION_TYPES
//{
//	OS_ENCRYPTION_TYPE_NONE = 0,
//	OS_ENCRYPTION_TYPE_WEP,
//	OS_ENCRYPTION_TYPE_TKIP,
//	OS_ENCRYPTION_TYPE_AES
//} OS_802_11_ENCRYPTION_TYPES;
//
///* Key type*/
//typedef enum _OS_802_11_KEY_TYPES
//{
//    OS_KEY_TYPE_STATIC = 0,
//    OS_KEY_TYPE_DYNAMIC
//} OS_802_11_KEY_TYPES;
//
///* ELP mode*/
//typedef enum _OS_802_11_ELP_MODES
//{
//	OS_ELP_MODE_DISABLE,
//	OS_ELP_MODE_SYNC,
//    OS_ELP_MODE_NON_SYNC
//} OS_802_11_ELP_MODES;
//
///* Roaming mode*/
//typedef enum _OS_802_11_ROAMING_MODES
//{
//	OS_ROAMING_MODE_DISABLE,
//	OS_ROAMING_MODE_ENABLE
//} OS_802_11_ROAMING_MODES;
//
//typedef enum _OS_802_11_POWER_LEVELS
//{
//    OS_POWER_LEVEL_ELP,
//    OS_POWER_LEVEL_PD,
//    OS_POWER_LEVEL_AWAKE
//} OS_802_11_POWER_LEVELS;
//
//
//typedef enum _OS_802_11_BEACON_FILTER_MODE
//{
//    OS_BEACON_FILTER_MODE_INACTIVE,
//    OS_BEACON_FILTER_MODE_ACTIVE
//} OS_802_11_BEACON_FILTER_MODE;
//
//
//typedef enum _OS_802_11_SCAN_TYPES
//{
//    OS_SCAN_TYPE_PASSIVE,
//    OS_SCAN_TYPE_BROADCAST,
//    OS_SCAN_TYPE_UNICAST
//} OS_802_11_SCAN_TYPES;
//
//typedef enum _OS_802_11_VOICE_DELIVERY_PROTOCOL
//{
//    OS_VOICE_DELIVERY_PROTOCOL_DISABLED,
//    OS_VOICE_DELIVERY_PROTOCOL_PS_POLL
//} OS_802_11_VOICE_DELIVERY_PROTOCOL;
//
//typedef uint8_t   OS_802_11_PMKID_VALUE[16];
//
///** \struct OS_BSSIDInfo
// * \brief Single PMKID context
// *
// * \par Description
// * PMK record resulting from successful 8021.X authentication
// *
// * \sa
// */
//typedef struct _OS_BSSIDInfo
//{
//    TMacAddr   BSSID;              /* BSSID of the Authenticating AP */
//    OS_802_11_PMKID_VALUE   PMKID; /* PMK ID */
//}  OS_BSSIDInfo, *POS_BSSIDInfo;
//
///** \struct OS_802_11_PMKID
// * \brief PMKID list
// *
// * \par Description
// * List of cached PMKIDs
// *
// * \sa
// */
//typedef struct _OS_802_11_PMKID
//{
//    uint32_t        Length;          /* List length in bytes */
//    uint32_t        BSSIDInfoCount;  /* Number of entries in the list */
//    OS_BSSIDInfo    osBSSIDInfo[1];   /* PMKID list */
//}  OS_802_11_PMKID, *POS_802_11_PMKID;
//
//typedef enum _OS_802_11_WEP_STATUS
//{
//  os802_11WEPEnabled = 0,
//  os802_11Encryption1Enabled = os802_11WEPEnabled,
//  os802_11WEPDisabled,
//  os802_11EncryptionDisabled = os802_11WEPDisabled,
//  os802_11WEPKeyAbsent,
//  os802_11Encryption1KeyAbsent = os802_11WEPKeyAbsent,
//  os802_11WEPNotSupported,
//  os802_11EncryptionNotSupported = os802_11WEPNotSupported,
//  os802_11Encryption2Enabled,
//  os802_11Encryption2KeyAbsent,
//  os802_11Encryption3Enabled,
//  os802_11Encryption3KeyAbsent
//} OS_802_11_WEP_STATUS, OS_802_11_ENCRYPTION_STATUS;
//
///*os802_11AuthModeOpen */
///*  Specifies 802.11 open authentication mode. There are no checks when accepting */
///*  clients in this mode. */
///*os802_11AuthModeShared */
///*  Specifies 802.11 shared authentication that uses a pre-shared wired equivalent */
///*  privacy (WEP) key. */
///*os802_11AuthModeAutoSwitch */
///*  Specifies auto-switch mode. When using auto-switch mode, the NIC tries 802.11 shared */
///*  authentication mode first. If shared mode fails, the NIC attempts to use 802.11 open */
///*  authentication mode. */
//
//typedef enum _OS_802_11_AUTHENTICATION_MODE
//{
//    os802_11AuthModeOpen,
//    os802_11AuthModeShared,
//    os802_11AuthModeAutoSwitch,
//    os802_11AuthModeWPA,
//    os802_11AuthModeWPAPSK,
//    os802_11AuthModeWPANone,
//    os802_11AuthModeWPA2,
//    os802_11AuthModeWPA2PSK,
//    os802_11AuthModeMax
//} OS_802_11_AUTHENTICATION_MODE;
//
//
///*os802_11PrivFilterAcceptAll */
///*  Specifies an open mode. In this mode, the NIC accepts any packet if the packet */
///*  is not encrypted or if the NIC successfully decrypts it. */
///*os802_11PrivFilter8021xWEP */
///*  Specifies a filtering mode. In the 802.1X filtering mode, 802.1X packets are */
///*  accepted even if they are not encrypted. However, the NIC accepts nothing else */
///*  unless it is encrypted using WEP. */
//typedef enum _OS_802_11_PRIVACY_FILTER
//{
//  os802_11PrivFilterAcceptAll,
//  os802_11PrivFilter8021xWEP
//} OS_802_11_PRIVACY_FILTER;
//
//typedef enum _OS_802_11_RELOAD_DEFAULTS
//{
//  os802_11ReloadWEPKeys
//} OS_802_11_RELOAD_DEFAULTS, *POS_802_11_RELOAD_DEFAULTS;
//
//typedef enum _OS_802_11_STATUS_TYPE
//{
//    os802_11StatusType_Authentication,
//    os802_11StatusType_PMKID_CandidateList = 2,
//    os802_11StatusTypeMax       /* not a real type, defined as an upper bound */
//} OS_802_11_STATUS_TYPE, *POS_802_11_STATUS_TYPE;
//
//typedef struct _OS_802_11_STATUS_INDICATION
//{
//    OS_802_11_STATUS_TYPE StatusType;
//} OS_802_11_STATUS_INDICATION, *POS_802_11_STATUS_INDICATION;
//
//
//typedef struct _OS_802_11_AUTHENTICATION_REQUEST
//{
//    uint32_t           	Length;             /* Length of this structure*/
//    TMacAddr 	            BSSID;
//	uint32_t				Flags;
//}  OS_802_11_AUTHENTICATION_REQUEST, *POS_802_11_AUTHENTICATION_REQUEST;
//
//typedef enum
//{
//	OS_DISASSOC_STATUS_UNSPECIFIED      		=   0,
//	OS_DISASSOC_STATUS_AUTH_REJECT				=   1,
//	OS_DISASSOC_STATUS_ASSOC_REJECT				=   2,
//	OS_DISASSOC_STATUS_SECURITY_FAILURE 		=   3,
//	OS_DISASSOC_STATUS_AP_DEAUTHENTICATE		=   4,
//	OS_DISASSOC_STATUS_AP_DISASSOCIATE			=   5,
//	OS_DISASSOC_STATUS_ROAMING_TRIGGER			=   6
//
//}	OS_802_11_DISASSOCIATE_REASON_E;
//
//typedef struct
//{
//	OS_802_11_DISASSOCIATE_REASON_E  eDisAssocType;
//	uint32_t						 uStatusCode;
//} OS_802_11_DISASSOCIATE_REASON_T;
//
//
//
//#define OS_802_11_PMKID_CANDIDATE_PREAUTH_ENABLE   0x01
//
//typedef struct _OS_802_11_PMKID_CANDIDATE
//{
//    TMacAddr               BSSID;
//    uint32_t              Flags;
//}  OS_802_11_PMKID_CANDIDATE, *POS_802_11_PMKID_CANDIDATE;
//
//typedef struct _OS_802_11_PMKID_CANDIDATELIST
//{
//    uint32_t                   Version;       /* Version of the structure*/
//    uint32_t                   NumCandidates; /* No. of pmkid candidates*/
//    OS_802_11_PMKID_CANDIDATE  CandidateList[1];
//}  OS_802_11_PMKID_CANDIDATELIST, *POS_802_11_PMKID_CANDIDATELIST;
//
//
//typedef uint8_t OS_802_11_MAC_PMKID_VALUE[16];
//
//typedef struct _OS_802_11_BSSIDInfo
//{
//    TMacAddr 	               BSSID;
//    OS_802_11_MAC_PMKID_VALUE  PMKID;
//}  OS_802_11_BSSIDInfo, *POS_802_11_BSSIDInfo;
//
//
//typedef struct _OS_802_11_AUTH_ENCRYPTION
//{
//    OS_802_11_AUTHENTICATION_MODE AuthModeSupported;
//    OS_802_11_ENCRYPTION_STATUS   EncryptionStatusSupported;
//} OS_802_11_AUTH_ENCRYPTION, *POS_802_11_AUTH_ENCRYPTION;
//
//
//typedef struct _OS_802_11_CAPABILITY
//{
//    uint32_t Length;
//    uint32_t Version;
//    uint32_t NoOfPmKIDs;
//    uint32_t NoOfAuthEncryptPairsSupported;
//    OS_802_11_AUTH_ENCRYPTION AuthEncryptionSupported[1];
//
//} OS_802_11_CAPABILITY, *POS_802_11_CAPABILITY;
//
//#define OID_CAPABILITY_VERSION 2
//
//
//
//typedef enum _OS_802_11_REG_DOMAIN
//{
//  os802_11_Domain_FCC = 0x10,
//  os802_11_Domain_IC = 0x20,
//  os802_11_Domain_ETSI = 0x30,
//  os802_11_Domain_Spain = 0x31,
//  os802_11_Domain_France = 0x32,
//  os802_11_Domain_MKK = 0x40,
//  os802_11_Domain_MKK1 = 0x41,
//  os802_11_Domain_US	= 0x50,
//  os802_11_Domain_WB	= 0x51,
//  os802_11_Domain_EXWB	= 0x52
//} OS_802_11_REG_DOMAIN;
//
//
//
//#define OID_TI_VERSION							0xFF080001
//
//
///* propritary OIDs used by FUNK supplicant for WPA Mixed mode support*/
///* WPA2 MIxed mode OIDs */
//#define CGUID_FSW_802_11_AVAILABLE_OPTIONS      {0x1a905534, 0xe71f, 0x46d1, {0xa2, 0xcb, 0xa5, 0x57, 0x01, 0x76, 0x38, 0xfd}}
//#define CGUID_FSW_802_11_OPTIONS 				{0xdc7a51b7, 0x2236, 0x467d, {0xb1, 0x55, 0x03, 0x50, 0x42, 0x04, 0xcf, 0x30}}
//
//#define OID_FSW_802_11_AVAILABLE_OPTIONS        0xFF010237
//#define OID_FSW_802_11_OPTIONS                  0xFF010238
//
//
//
///**/
///* IEEE 802.11 OIDs*/
///**/
//#define OID_802_11_BSSID                        0x0D010101
//#define OID_802_11_SSID                         0x0D010102
//#define OID_802_11_INFRASTRUCTURE_MODE          0x0D010108
//#define OID_802_11_ADD_WEP                      0x0D010113
//#define OID_802_11_REMOVE_WEP                   0x0D010114
//#define OID_802_11_DISASSOCIATE                 0x0D010115
//#define OID_802_11_AUTHENTICATION_MODE          0x0D010118
//#define OID_802_11_PRIVACY_FILTER               0x0D010119
//#define OID_802_11_BSSID_LIST_SCAN              0x0D01011A
//#define OID_802_11_WEP_STATUS                   0x0D01011B
//#define OID_802_11_RELOAD_DEFAULTS              0x0D01011C
//#define OID_802_11_ADD_KEY                      0x0D01011D
//#define OID_802_11_REMOVE_KEY                   0x0D01011E
//#define OID_802_11_ASSOCIATION_INFORMATION      0x0D01011F
//#define OID_802_11_NETWORK_TYPES_SUPPORTED      0x0D010203
//#define OID_802_11_NETWORK_TYPE_IN_USE          0x0D010204
//#define OID_802_11_TX_POWER_LEVEL               0x0D010205
//#define OID_802_11_RSSI                         0x0D010206
//#define OID_802_11_RSSI_TRIGGER                 0x0D010207
//#define OID_802_11_FRAGMENTATION_THRESHOLD      0x0D010209
//#define OID_802_11_RTS_THRESHOLD                0x0D01020A
//#define OID_802_11_NUMBER_OF_ANTENNAS           0x0D01020B
//#define OID_802_11_RX_ANTENNA_SELECTED          0x0D01020C
//#define OID_802_11_TX_ANTENNA_SELECTED          0x0D01020D
//#define OID_802_11_SUPPORTED_RATES              0x0D01020E
//#define OID_802_11_DESIRED_RATES                0x0D010210
//#define OID_802_11_CONFIGURATION                0x0D010211
//#define OID_802_11_STATISTICS                   0x0D020212
//#define OID_802_11_POWER_MODE                   0x0D010216
//#define OID_802_11_BSSID_LIST                   0x0D010217
//
//
//#ifndef _USER_MODE
//	#include "osdot11nousermode.h"
//#endif
//
//
//
//
///* AnyWPA mode flags used in propritary FUNK suplicant OIDs*/
//
//#define     OS_802_11_OPTION_ENABLE_PROMOTE_MODE        0x00000001 /*bit 0*/
//#define     OS_802_11_OPTION_ENABLE_PROMOTE_CIPHER      0x00000002 /*bit 1*/
//#define		OS_802_11_OPTION_DISABLE_PROMOTE_MODE		0
//#define     OS_802_11_OPTION_ENABLE_ALL                 0x00000003

#endif

