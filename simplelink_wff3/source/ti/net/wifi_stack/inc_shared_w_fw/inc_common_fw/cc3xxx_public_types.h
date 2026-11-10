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

  FILENAME:       cc3xxx_public_types.h

  DESCRIPTION:    Basic types and macros definitions.
                  This file was created for osprey, based on WL8 FW public_types

  ----------------------------------------------------------------------------- */
#ifndef CC3XXX_PUBLIC_TYPES_H
#define CC3XXX_PUBLIC_TYPES_H

#include <stdint.h>

/*-----------------------------------------------------------------------------
    Boolean definitions
	For efficiency, the 32 bit definition should be preferred whenever possible
  ----------------------------------------------------------------------------- */
   
#ifndef Bool_e
typedef uint8_t Bool_e;
#endif
#ifndef Bool32
typedef uint32_t Bool32;
#endif


/* to align enum to 32/16 bits */
#define MAX_POSITIVE32 0x7FFFFFFF
#define MAX_POSITIVE16 0x7FFF
#define MAX_POSITIVE8  0x7F

/*-----------------------------------------------------------------------------
    Bits definitions
  ----------------------------------------------------------------------------- */

#define  BIT_0    0x00000001
#define  BIT_1    0x00000002
#define  BIT_2    0x00000004
#define  BIT_3    0x00000008
#define  BIT_4    0x00000010
#define  BIT_5    0x00000020
#define  BIT_6    0x00000040
#define  BIT_7    0x00000080
#define  BIT_8    0x00000100
#define  BIT_9    0x00000200
#define  BIT_10   0x00000400
#define  BIT_11   0x00000800
#define  BIT_12   0x00001000
#define  BIT_13   0x00002000
#define  BIT_14   0x00004000
#define  BIT_15   0x00008000
#define  BIT_16   0x00010000
#define  BIT_17   0x00020000
#define  BIT_18   0x00040000
#define  BIT_19   0x00080000
#define  BIT_20   0x00100000
#define  BIT_21   0x00200000
#define  BIT_22   0x00400000
#define  BIT_23   0x00800000
#define  BIT_24   0x01000000
#define  BIT_25   0x02000000
#define  BIT_26   0x04000000
#define  BIT_27   0x08000000
#define  BIT_28   0x10000000
#define  BIT_29   0x20000000
#define  BIT_30   0x40000000
#define  BIT_31   0x80000000


//higher bits - same as lower bits
#define  BIT_32   0x00000001
#define  BIT_33   0x00000002
#define  BIT_34   0x00000004
#define  BIT_35   0x00000008
#define  BIT_36   0x00000010
#define  BIT_37   0x00000020
#define  BIT_38   0x00000040
#define  BIT_39   0x00000080
#define  BIT_40   0x00000100
#define  BIT_41   0x00000200
#define  BIT_42   0x00000400
#define  BIT_43   0x00000800
#define  BIT_44   0x00001000
#define  BIT_45   0x00002000
#define  BIT_46   0x00004000
#define  BIT_47   0x00008000
#define  BIT_48   0x00010000
#define  BIT_49   0x00020000
#define  BIT_50   0x00040000
#define  BIT_51   0x00080000
#define  BIT_52   0x00100000
#define  BIT_53   0x00200000
#define  BIT_54   0x00400000
#define  BIT_55   0x00800000
#define  BIT_56   0x01000000
#define  BIT_57   0x02000000
#define  BIT_58   0x04000000
#define  BIT_59   0x08000000
#define  BIT_60   0x10000000
#define  BIT_61   0x20000000
#define  BIT_62   0x40000000
#define  BIT_63   0x80000000

#define  SET_ALL_32_BITS   (0xFFFFFFFF)
#define  SET_16_BITS       (0xFFFF)


/* Supported channels definitions */
#define CHANNELS_COUNT 40 /* 14 2.4GHz channels, 26 5GHz channels */
#define PER_CHANNEL_REG_RULE_BYTES 13
#define REG_RULES_COUNT (CHANNELS_COUNT * PER_CHANNEL_REG_RULE_BYTES) /* 520 */


/* Supported channels definitions */
#define CHANNELS_COUNT 40 /* 14 2.4GHz channels, 26 5GHz channels */
#define PER_CHANNEL_REG_RULE_BYTES 13
#define REG_RULES_COUNT (CHANNELS_COUNT * PER_CHANNEL_REG_RULE_BYTES) /* 520 */


/******************************************************************************
                            CMD_SET_KEYS
******************************************************************************/

#define MAX_KEY_SIZE 32

typedef enum
{
    KEY_ADD_OR_REPLACE = 1,             /* Add or replace a key in the WEP cache*/
    KEY_REMOVE         = 2,             /* Remove a key from the WEP cache*/
    KEY_SET_ID         = 3,             /* Set Key ID*/
    MAX_KEY_ACTION     = MAX_POSITIVE16 /* force this enum to be uint16_t*/
} KeyAction_e;

typedef enum
{
    KEY_TYPE_UNICAST      = 0,
    KEY_TYPE_BROADCAST    = 1,
    KEY_TYPE_WEP_DEFAULT  = 2
} LidKeyType_e;


/*
Key Size+Key Data table (valid value)
KeyType_e     Key Type                    Valid Key Size    Key Data Field Format
============  ========                    ==============    =====================
0x00          WEP default key             5, 13, 29         Key Size bytes of key data

0x01          WEP key mapping key         5, 13, 29         Key Size bytes of key data

0x04          AES Group Key               16                16 bytes of key data

0x05          AES Pairwise Key            16                16 bytes of key data

0x0A          TKIP and MIC Group Key      32                16 bytes of TKIP key data
                                                        8 bytes of Rx MIC key data
                                                        8 bytes of Tx MIC key data

0x0B          TKIP and MIC Pairwise Key   32                16 bytes of TKIP key data
                                                        8 bytes of Rx MIC key data
                                                        8 bytes of Tx MIC key data

0x0C          GEM and MIC Group Key      32                 16 bytes of GEM key data
                                                            16 bytes of MIC key data

0x0D          GEM and MIC Pairwise Key   32                 16 bytes of GEM key data
                                                            16 bytes of MIC key data

*/


//Important: This enum is aligned to the definitions in the PMAC HW module.
typedef enum
{
  CIPHER_SUITE_NONE    = 0,
  CIPHER_SUITE_WEP     = 1,
  CIPHER_SUITE_TKIP    = 2,
  CIPHER_SUITE_AES     = 3,
  CIPHER_SUITE_GEM     = 4,
  CIPHER_BIP_CMAC_128  = 5,
  CIPHER_BIP_CMAC_256  = 6,
  CIPHER_BIP_GMAC_128  = 7,
  CIPHER_BIP_GMAC_256  = 8,
  CIPHER_SUITE_GCMP256 = 9, 
  CIPHER_SUITE_CCMP256 = 10,
  CIPHER_SUITE_GCMP128 = 11,
  CIPHER_SUITE_CCMP_DMA= 12,
  MAX_KEY_TYPE
} CipherSuite_e;


#define IS_BIP_CIPHER_SUITE(cipher)     (    (cipher == CIPHER_BIP_CMAC_128)    \
                                          || (cipher == CIPHER_BIP_CMAC_256)    \
                                          || (cipher == CIPHER_BIP_GMAC_128)    \
                                          || (cipher == CIPHER_BIP_GMAC_256)  )


typedef enum
{
    NO_KEY            =  0,
    KEY_SIZE_WEP_64   =  5,
    KEY_SIZE_WEP_128  = 13,
    KEY_SIZE_WEP_256  = 29,
    KEY_SIZE_TKIP     = MAX_KEY_SIZE
} KeySize_e;                      /* WEP keysizes reflect 3 bytes appended from IV.*/

/******************************************************************************
                    CMD_SET_LINK_CONNECTION_STATE
******************************************************************************/
/* enum LinkState_e - Link state
 *
 * @LINK_STATE_DISCONNECTED: State disconnected
 *
 * @LINK_STATE_CONNECTED:    State connected
 *
*/
typedef enum
{
    LINK_STATE_DISCONNECTED = 0,
    LINK_STATE_CONNECTED = 1
}LinkState_e;

/******************************************************************************
                            CMD_AP_SET_BEACON_INFO
******************************************************************************/
#define MAX_BEACON_LENGTH   (750)

/******************************************************************************
                            Disconnect Type
******************************************************************************/
typedef enum
{
    DISCONNECT_IMMEDIATE,    /* Disconnect without sending any frame */
    DISCONNECT_DE_AUTH,      /* Send deauthentication frame upon disconnecting */
    DISCONNECT_DIS_ASSOC     /* Send disassociation frame upon disconnecting */
} DisconnectType_e;

/******************************************************************************
                            CMD_BLE_COMMANDS
******************************************************************************/
#define MAX_BLE_PKT_LEN     (300)

/******************************************************************************
                            CMD_SET_SEED
******************************************************************************/
#define MAX_SEED_SIZE       (32)

/******************************************************************************

    CHANNELS, BAND & REG DOMAINS definitions

******************************************************************************/


typedef uint8_t Channel_e;

typedef uint8_t Ant_e;


// Don't change the enumeration as it is use in other places !!!
typedef enum
{
    RADIO_BAND_2_4GHZ = 0,  /* 2.4 Ghz band */
    RADIO_BAND_5GHZ = 1,    /* 5 Ghz band */
    RADIO_BAND_6GHZ = 2,    /* 6 Ghz band */
    RADIO_BAND_JAPAN_4_9_GHZ = 3,
    DEFAULT_BAND = RADIO_BAND_2_4GHZ,
    INVALID_BAND = 0x7E,
    MAX_RADIO_BANDS = 0x7F
} RadioBand_e;

typedef enum
{
    NLCP_CHAN_NO_HT     ,   /* 40MHz disabled */
    NLCP_CHAN_HT20      ,   /* 40MHz disabled */
    NLCP_CHAN_HT40MINUS ,   /* 40MHz enabled, secondary channel is above the primary channel */
    NLCP_CHAN_HT40PLUS  ,   /* 40MHz enabled, secondary channel is below the primary channel */
    NLCP_CHAN_INVALID   = 0xFF
} BandWidthSettings_e;


/******************************************************************************
Role API
******************************************************************************/
typedef uint8_t RoleID_t;

#define DOT11_SSID_MAX_LEN  (32)

typedef enum
{
    SSID_TYPE_PUBLIC = 0,
    SSID_TYPE_HIDDEN = 1,
    SSID_TYPE_ANY = 2,
    MAX_SSID_TYPE = 0xFF
} SsidType_e;

/* CMD_PARAMS_HOST_ROLE_DEFINITION - A macro to make sure all RoleID parameters use the same convention */
#define CMD_PARAMS_HOST_ROLE_DEFINITION RoleID_t RoleID;

typedef enum
{
    ROLE_STA                    , /* 0  */
    ROLE_IBSS                   , /* 1  */
    ROLE_AP                     , /* 2  */
    ROLE_DEVICE                 , /* 3  */
    ROLE_P2P_CL                 , /* 4  */
    ROLE_P2P_GO                 , /* 5  */
    ROLE_TDLS                   , /* 6  */

    ROLE_WLAN_SCAN_SINGLE_SHOT  , /* 7  */
    ROLE_WLAN_SCAN_PERIODIC     , /* 8  */
    ROLE_WLAN_CALIBRATION       , /* 9  */
    ROLE_DUMMY                  , /* 10 */
    ROLE_WLAN_DFS_CAC           , /* 11 */
    ROLE_WLAN_MEASUREMENT       , /* 12 */

    /*non wlan roles*/
    ROLE_BT                     , /* 13 */
    ROLE_BT_CALIBRATION         , /* 14 */
    ROLE_ETH                    , /* 15 */
    ROLE_TRANSCEIVER            , /* 16 */
    /*multi role combinations*/
    ROLE_STA_AP                 , /* 17 multi-role*/
    ROLE_STA_ETH                , /* 18 multi-role*/
    ROLE_ETH_AP                 , /* 19 multi-role*/
    ROLE_STA_TRANSCEIVER        , /* 20 multi-role*/
    ROLE_AP_TRANSCEIVER         , /* 21 multi-role*/

    ROLE_NUM_OF_ROLE_TYPES      ,
    ROLE_TYPE_NONE = 0xff
} RoleType_e;

/******************************************************************************
SCAN API
******************************************************************************/
#define SCAN_MAX_BAND                      (3)         /* Maximum number of bands in scan configuration */

#define CONN_SCAN_DFS_CANDIDATE_CHANNEL     BIT_0
#define CONN_SCAN_DFS_ENABLED_CHANNEL       BIT_1

#define MAX_SSID_LEN                        (32)

/******************************************************************************/
/*                              OSPREY STRUCTURE                              */
/******************************************************************************/

#define CONN_SCAN_MAX_NUMBER_OF_SSID_ENTRIES        (16)
#define CONN_SCAN_MAX_BAND                          (2)
#define CONN_SCAN_MAX_CHANNELS_ALL_BANDS            (46)

// Maximum number of supported scan plans for scheduled scan, supported by the driver
#define SCAN_MAX_SCHED_SCAN_PLANS                   (12)

// Max length of extra IEs added to management frames (probe req, assoc req)
#define MAX_EXTRA_IES_LEN                           (512)

typedef enum
{
    ONE_SHOT_SCAN_TYPE      = 0,
    PERIODIC_SCAN_TYPE      = 1,
    NUM_OF_SCAN_TYPES       = 2,
    MAX_SCAN_TYPE           = 0xFF
} ScanType_e;
typedef enum
{
    SCAN_REQUEST_NONE,
    SCAN_REQUEST_CONNECT_PERIODIC_SCAN,
    SCAN_REQUEST_ONE_SHOT,
    SCAN_REQUEST_SURVEY_SCAN,
    SCAN_NUM_OF_REQUEST_TYPE
} EScanRequestType;

// Scan results filtering configuration
// For modes other than SCAN_RESULTS_PASS_ALL a bit mask may be used.
typedef enum
{
    SCAN_RESULTS_PASS_ALL = 0,           // deliver all scan results into scan results table module
                                         // results may be filtered according to their score.

    // For the below modes, none matching results are dropped.
    // Matching results are stored in scan results table and also delivered to supplicant.
    // Note: !!! the enumeration must support bit masking !!!
    SCAN_RESULTS_PASS_WPS = 1,   // Serves for WPS connection
    SCAN_RESULTS_PASS_P2P = 2    // Serves for P2P

} scanResultsFilterCfg_e;


#define CONN_SCAN_MAX_NUMBER_OF_SSID_ENTRIES        (16)
#define CONN_SCAN_MAX_BAND                          (2)
#define CONN_SCAN_MAX_CHANNELS_ALL_BANDS            (46)

// Maximum number of supported scan plans for scheduled scan, supported by the driver
#define SCAN_MAX_SCHED_SCAN_PLANS           (12)

typedef enum
{
    WLANLINK_TYPE_SYSTEM,
    WLANLINK_TYPE_SPECIFIC,     // Serves for connection
    WLANLINK_TYPE_BRCST,
    WLANLINK_TYPE_GLOBAL
} linkType_e;



typedef enum
{
    SLOT_TIME_LONG = 0,     /* the WiLink uses long (20 us) slots*/
    SLOT_TIME_SHORT = 1,    /* the WiLink uses short (9 us) slots*/
    DEFAULT_SLOT_TIME = SLOT_TIME_SHORT,
    MAX_SLOT_TIMES = 0xFF
} SlotTime_e;


/******************************************************************************

    Name:   ACX_AC_CFG
    Type:   Configuration
    Access: Write Only
    Length: 8

******************************************************************************/
typedef enum
{
    AC_BE = 0,          /* Best Effort/Legacy*/
    AC_BK = 1,          /* Background*/
    AC_VI = 2,          /* Video*/
    AC_VO = 3,          /* Voice*/
    /* AC_BCAST    = 4, */  /* Broadcast dummy access category      */
    AC_CTS2SELF = 4,        /* CTS2Self fictitious AC,              */
                            /* uses #4 to follow AC_VO, as          */
                            /* AC_BCAST does not seem to be in use. */
    AC_MGT  = 5,
    AC_ANY_TID = 0x1F,
    AC_INVALID = 0xFF,  /* used for gTxACconstraint */
    NUM_ACCESS_CATEGORIES = 4
} AccessCategory_e;

typedef enum
{
    TID0 = 0,           /* Best Effort/Legacy*/
    TID1 = 1,           /* Best Effort/Legacy*/
    TID2 = 2,           /* Background*/
    TID3 = 3,           /* Video*/
    TID4 = 4,           /* Voice*/
    TID5 = 5,       /* Broadcast dummy access category*/
    TID6 = 6,
    TID7 = 7,           /* managment */
    NUM_TRAFFIC_CATEGORIES = 8,
    NON_QOS = NUM_TRAFFIC_CATEGORIES
} TrafficCategory_enum;


#define AC_REQUEST                      0xfe    /* Special access category type for */
                                                /* requests*/


/* following are defult values for the IE fields*/
#define CWMIN_BK  4
#define CWMIN_BE  4
#define CWMIN_VI  3
#define CWMIN_VO  2
#define CWMAX_BK  10
#define CWMAX_BE  10
#define CWMAX_VI  4
#define CWMAX_VO  3
#define AIFS_PIFS 1 /* slot number setting to start transmission at PIFS interval */
#define AIFS_DIFS 2 /* slot number setting to start transmission at DIFS interval - */
                    /* normal DCF access */

#define AIFS_MIN AIFS_PIFS

#define AIFSN_BK  7
#define AIFSN_BE  3
#define AIFSN_VI  AIFS_DIFS
#define AIFSN_VO  AIFS_DIFS
#define TXOP_BK   0
#define TXOP_BE   0
#define TXOP_VI   3008/32
#define TXOP_VO   1504/32
#define DEFAULT_AC_SHORT_RETRY_LIMIT 7
#define DEFAULT_AC_LONG_RETRY_LIMIT 4

/* rxTimeout values */
#define NO_RX_TIMEOUT 0

typedef struct
{
    uint8_t   aifsn;       // The AIF value (in slots) for the access class
    uint8_t   cwMin;       // The contention window minimum size (in slots) for
                         // the access class
    uint8_t   cwMax;       // The contention window maximum size (in slots) for
                         // the access class
    uint16_t  txopLimit;   // The TX Op Limit (in microseconds) for the access class	
    uint8_t   acm;         // Admission control mandatory
} AcCfg_t;


typedef enum
{
    PS_SCHEME_LEGACY         = 0, /* Regular PS: simple sending of packets*/
    PS_SCHEME_UPSD_TRIGGER   = 1, /* UPSD: sending a packet triggers a UPSD downstream*/
    PS_SCHEME_MIXED_MODE     = 2, //Mixed mode is partially supported:
                                  //we are not going to sleep, and triggers (on APSD AC's) are not
                                  //sent when service period ends with more_data = 1.
    PS_SCHEME_LEGACY_PSPOLL  = 3, /* Legacy PSPOLL: a PSPOLL packet will be sent before */
                                  /* every data packet transmission in this queue.*/
    PS_SCHEME_SAPSD          = 4, /* Scheduled APSD mode.*/
    PS_SCHEME_NOPSPOLL       = 5, /* No PSPOLL: move to active after first packet. */
                                  /* no need to sent pspoll */
    MAX_PS_SCHEME = PS_SCHEME_NOPSPOLL
} PSScheme_e;



typedef enum
{
    ACK_POLICY_LEGACY = 0,   /* ACK immediate policy*/
    ACK_POLICY_NO_ACK = 1,   /* no ACK policy*/
    ACK_POLICY_BLOCK  = 2,   /* block ack policy*/
    MAX_ACK_POLICY = ACK_POLICY_BLOCK
} AckPolicy_e;


/*
aflag definition:
bit field       description
=========       ===========
0               Truncate - If set, then attempts to send a frame stop when the total
                valid per-rate attempts have been exhausted;
                otherwise transmissions will continue at the lowest available rate
                until the appropriate one of the Short Retry Limit, Long Retry Limit,
                dot11MaxTransmitMsduLifetime, or MAX TX Life Time (in ACXTIDConfig),
                if supported and supplied, is exhausted.
1               Preamble Override - Indicates if the preamble type should be used in TX.
2               Preamble Type - The type of the preamble to be used by the policy.
                0 - long preamble,
                1 - short preamble.
3-7             Reserved
*/

/* definition of single rate policy*/
typedef struct
{

    uint32_t              enabledRates;                 /* A Bit Mask which indicates which Rates are enabled */
                                                      /* The rates bitmap is defined in EHwBitRate. */
                                                      /* If set to RATE_MASK_UNSPECIFIED, the FW sets it internally */

    uint8_t               shortRetryLimit;              /* The dot11ShortRetryLimit used */
                                                      /* for Tx retries.*/

    uint8_t               longRetryLimit;               /* The dot11LongRetryLimit used */
                                                      /* for Tx retries.  */

    uint8_t               aflags;                       /* Flags controlling attributes */
                                                      /* of the transmission. */
                                                      /* see above description for the */
                                                      /* structure of this field.*/

    uint8_t               reserved;
}txAttrClass_t;

#ifdef PMAC_AX
typedef enum
{
    PREAMBLE_TYPE_SHORT          = 0,
    PREAMBLE_TYPE_LONG           = 1,
    PREAMBLE_TYPE_OFDM           = 2,
    PREAMBLE_TYPE_N_MIXED_MODE   = 3,
    PREAMBLE_TYPE_GREENFIELD     = 4,
    PREAMBLE_TYPE_AX_SU          = 5,
    PREAMBLE_TYPE_AX_MU          = 6,
    PREAMBLE_TYPE_AX_SU_ER       = 7,
    PREAMBLE_TYPE_AX_TB          = 8,
    PREAMBLE_TYPE_AX_TB_NDP_FB   = 9,
    PREAMBLE_TYPE_AC_VHT         = 10,
    PREAMBLE_TYPE_BE_EHT_MU      = 13,
    PREAMBLE_TYPE_BE_EHT_TB      = 14,
    PREAMBLE_TYPE_INVALID        = 0xFF
} PreambleType_e;
#else
typedef enum
{
    PREAMBLE_TYPE_LONG           = 0,
    PREAMBLE_TYPE_SHORT          = 1,
    PREAMBLE_TYPE_OFDM           = 4,
    PREAMBLE_TYPE_N_MIXED_MODE   = 6,
    PREAMBLE_TYPE_GREENFIELD     = 7,
    PREAMBLE_TYPE_INVALID        = 0xFF
} PreambleType_e;
#endif

#define IS_MCS_PREAMBLE(preamble)   ((preamble >= PREAMBLE_TYPE_N_MIXED_MODE) && (preamble <= PREAMBLE_TYPE_AC_VHT))
/******************************************************************************

    Name:   ACX_HT_BSS_OPERATION
    Desc:   Configure HT capabilities - AP rules for behavior in the BSS.
    Type:   Configuration
    Access: Write Only
    Length:

******************************************************************************/
typedef struct
{
    uint8_t rifsMode;            /* Values: 0 - RIFS not allowed, 1 - RIFS allowed */
    uint8_t htProtection;        /* Values: 0 - 3 like in spec */
    uint8_t gfProtection;        /* Values: 0 - GF protection not required, 1 - GF protection required */
    uint8_t dualCtsProtection;   /*
                                * Values: 0 - Dual CTS protection not required, 1 Dual CTS Protection required
                                *             Note: When this value is set to 1 FW will protect all TXOP with RTS
                                *             frame and will not use CTS-to-self regardless of the value of the
                                *             ACX_CTS_PROTECTION information element
                                */
} htBssCap_t;


/******************************************************************************

    Name:   ACX_TID_CFG
    Type:   Configuration
    Access: Write Only
    Length: 16

******************************************************************************/


/* Michal recommendation:
   in the ACXTIDConfig_t structure we need only the fields psScheme, and one other field for AC id (queue? tsid?).
   the rest are obsolete. see IEPsDeliveryTriggerType_t in CE2.0.
   */

typedef struct
{

    CMD_PARAMS_HOST_ROLE_DEFINITION /* host RoleID */

    uint8_t   acID;           /* The TX queue ID number (0-7).*/
    uint8_t   channelType;    /* Channel access type for the queue.*/
                            /* Refer to ChannelType_enum.*/
    uint8_t   tsid;           /* for EDCA - the AC Index (0-3, refer to*/
                            /* AccessCategory_enum).*/
                            /* For HCCA - HCCA Traffic Stream ID (TSID) of */
                            /* the queue (8-15).*/
    uint8_t/*AckPolicy_e*/ ackPolicy;  /* The TX queue ACK policy. */
    uint8_t  padding[2];      /* alignment to 32bits boundry   */
    uint32_t APSDConf[2];     /* Not supported in this version !!!*/
}ACXTIDConfig_t;



#define ROLE_ID_NONE 0xFF


/* Defines the connection state of the link
*/
typedef enum
{
    LINK_CONNECTION_STATE_DISCONNECTED = 0,  // When link is allocated but not active yet
    LINK_CONNECTION_STATE_CONNECTING      ,  // On start STA/P2P CL role, and after authorization and association, but still not authorized (before 4 way handshake).
    LINK_CONNECTION_STATE_DISCONNECTING   ,  //Deauth or disassoc frame were sent, we are about to remove the link (about to remove peer or stop role)
    LINK_CONNECTION_STATE_CONNECTED       ,  // When L2 authorization (security, after 4 way handshake) is completed (or not needed in case of open AP).
    LINK_CONNECTION_STATE_ASSOCIATED         // When Associated, before authorization
} LinkConnectionState_e;








////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//  following types should reside at other h files whcih are not included yet
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


//TODO: put in original files

//taken from public_radio.h
//First 2 lines are similar to RadioBand_e
//it looks like there is no real use for the dual band enum
//typedef enum
//{
//    RADIO_BAND_2_4_GHZ                  = 0,
//    RADIO_BAND_5_0_GHZ                  = 1,
//    RADIO_BAND_DUAL                     = 2,    /**< Both band 2.4GHz and band 5GHz */
//    RADIO_BAND_NUM_OF_BANDS             = 2
//} ERadioBand;

//taken from TWDriver.h
#define A_5G_BAND_MIN_CHANNEL       34
#define A_5G_BAND_MAX_CHANNEL       180
#define A_5G_BAND_NUM_CHANNELS      (A_5G_BAND_MAX_CHANNEL-A_5G_BAND_MIN_CHANNEL+1)
#define E6GHZ_BAND_MIN_CHANNEL      (1)//6GHZ
#define E6GHZ_BAND_MAX_CHANNEL      (233)//6GHZ
#define REG_DOMAIN_MAX_REG_CLASS_NUM       10
#define NUM_OF_CHANNELS_24              14
#define NUM_OF_CHANNELS_5               180
#define TWD_CALIBRATION_CHANNEL_2_4_MIN 1
//#define MAX_TX_POWER                    250
//#define MIN_TX_POWER                    0
//#define DEF_TX_POWER                    250
#define DBM_TO_TX_POWER_FACTOR          10


#define GET_BAND_BY_CHANNEL(chan)      ( ((unsigned char)(chan) <= NUM_OF_CHANNELS_24) ? RADIO_BAND_2_4GHZ : RADIO_BAND_5GHZ )


#endif /* CC33XX_PUBLIC_TYPES_H*/