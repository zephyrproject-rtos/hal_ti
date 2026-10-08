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

  FILENAME:       public_types.h

  DESCRIPTION:    Basic types and macros definitions.

  ----------------------------------------------------------------------------- */
#ifndef PUBLIC_TYPES_H
#define PUBLIC_TYPES_H

/* Basic definitions are separated to host-NWP shared definitions and NWP
 * stand-alone definitions. Included file holds shared definitions.
 */
#include <cc3xxx_public_types.h>
#include "wlan_if.h"

#include "osi_type.h"
//#include "cc3xxx_public_commands.h"
/*-----------------------------------------------------------------------------
    Boolean definitions
	For efficiency, the 32 bit definition should be preferred whenever possible
  ----------------------------------------------------------------------------- */

#ifndef Bool_e
typedef uint8_t Bool_e;
#endif


#ifndef MIN
#define MIN(a,b) ( ((a)<(b)) ? (a) : (b) )
#endif

/*-----------------------------------------------------------------------------
    Commonly used types
  ----------------------------------------------------------------------------- */
#define MAC_ADDR_SIZE              6
#define IP_V4_ADDR_LEN             4
typedef uint8_t                    TMacAddr[MAC_ADDR_SIZE];
typedef uint8_t                    TIpAddr [IP_V4_ADDR_LEN];

typedef enum
{
/*  0   */  IP_VER_4 = 0,   /**< */
/*  1   */  IP_VER_6        /**< */

} EIpVer;

#define MEMORY_BLOCK_SIZE 272

#define MEMORY_BLOCK_DATA_SIZE      (MEMORY_BLOCK_SIZE - sizeof(uint32_t))
#define MEMORY_BLOCK_HEADER_SIZE    (MEMORY_BLOCK_SIZE - MEMORY_BLOCK_DATA_SIZE)



/**
 * \def BYTE_SWAP_WORD
 * \brief Macro which swaps Word's bytes. Used for Endian handling
 */
#define BYTE_SWAP_WORD(x)           ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8))

/*-----------------------------------------------------------------------------
    Basic macros
  ----------------------------------------------------------------------------- */
#ifdef SL_CC33XX_STATIC
#undef SL_CC33XX_STATIC
#endif

#ifndef SL_CC33XX_STATIC
//----------------------------------------------------------------------------------------------
// wolfssl integration
// replace the definition of STATIC (as it is also defined in misc.c) without touching the
// wolfssl package
#define SL_CC33XX_STATIC	 (static)

//----------------------------------------------------------------------------------------------
#endif

#ifndef INLINE
#define INLINE	 (inline)
#endif

#ifndef EXTERN
#define EXTERN	 (extern)
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#ifndef EXTERN
#define EXTERN	 (extern)
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#ifndef NULL
#define NULL          0
#endif

//#define MAC_ADDR_LEN							6   /* In Bytes */
//
////typedef struct
////{
////    uint8_t addr[MAC_ADDR_LEN];
////}macAddress_t;
//
//typedef uint8_t   macAddress_t [MAC_ADDR_LEN];
//
//typedef struct
//{
//    uint8_t       len;                    /**< SSID Length        */
//    char        str[ DOT11_SSID_MAX_LEN ];  /**< SSID string buffer */
//
//}  ssid_t;


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


#define INVALID_ROLE_ID            0xFF
//#define INVALID_LINK               0xFF
/******************************************************************************

    SET KEYS

******************************************************************************/
#define MAX_KEY_SIZE 32


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

#if 0
//Important: This enum is aligned to the definitions in the PMAC HW module.
typedef enum
{
  CIPHER_SUITE_NONE   = 0,
  CIPHER_SUITE_WEP    = 1,
  CIPHER_SUITE_TKIP   = 2,
  CIPHER_SUITE_AES    = 3,
  CIPHER_SUITE_GEM    = 4,

  // CC33XX TYPE
  CIPHER_BIP_CMAC_128 = 5,
  CIPHER_BIP_CMAC_256 = 6,
  CIPHER_BIP_GMAC_128 = 7,
  CIPHER_BIP_GMAC_256 = 8,

  MAX_KEY_TYPE
} CipherSuite_enum;
#endif



#define IS_BIP_CIPHER_SUITE(cipher)     (    (cipher == CIPHER_BIP_CMAC_128)    \
                                          || (cipher == CIPHER_BIP_CMAC_256)    \
                                          || (cipher == CIPHER_BIP_GMAC_128)    \
                                          || (cipher == CIPHER_BIP_GMAC_256)  )

#if 0
typedef enum
{
    NO_KEY            =  0,
    KEY_SIZE_WEP_64   =  5,
    KEY_SIZE_WEP_128  = 13,
    KEY_SIZE_WEP_256  = 29,
    KEY_SIZE_TKIP     = MAX_KEY_SIZE
} KeySize_enum;                      /* WEP keysizes reflect 3 bytes appended from IV.*/
#endif




/******************************************************************************

    ID:       CMD_SET_KEYS
    Desc:     Command set connection keys
    Params:   SetKey_t - see below.

******************************************************************************/

/**
 * struct SetKey_t - Set connection keys
 *
 * @lid:           Indicates whether the LID is a unicast key set
 *                 or broadcast key set. A special value 0xFF is
 *                 used to indicate that the lid is on WEP-default
 *                 (multi-hlids)
 *
 * @lidKeyType:   In WEP-default network (hlid == 0xFF) used to
 * @length:       indicate which network STA/IBSS/AP role should be   Length/reserved
 *                changed
 *
 * @keyId:        Key ID - For TKIP and AES key types, this field
 *                indicates the value that should be inserted into
 *                the KeyID field of frames transmitted using this
 *                key entry. For broadcast keys the index use as a
 *                marker for TX/RX key.
 *                For WEP default network (HLID=0xFF), this field
 *                indicates the ID of the key to add or remove.
 *
 * @action:       This field specifies the action to be performed.
 *                Refer to KeyAction_e.
 *
 * @keySize:      This field indicates the size of the key in bytes
 *                being added. Valid values are listed in the Valid Key
 *                Size column in the above "Key Size+Key Data table".
 *
 * @cipher_type:  This field indicates the type of key being added.
 *
 * @key:          This field holds the security key data to add to the
 *                STA table. The format of this field varies depending
 *                on the type field.
 *
 * @AcSeqNum16    This field indicates the lower part of the PN\IV
 *                sequence number that is received in the 4way handshake and is
 *                used in RX broadcast/unicast for the initial value for the replay detection
 *                (Same init value is used for the four Access).
 *
 * @AcSeqNum32    This field indicates the higher part of the PN\IV
 *                sequence number that is received in the 4way handshake and is
 *                used in RX broadcast/unicast for the initial value for the replay detection
 *                (Same init value is used for the four Access).
 *
*/
#if 0
typedef struct __PACKED__
{
/* 4 bytes */
    uint8_t           lid;
    uint8_t/*LidKeyType_e*/    lidKeyType;
    uint8_t           keyId;

    uint8_t           reserved;
/* 4 bytes */
    uint16_t/*KeyAction_e*/     action;
    uint8_t/*KeySize_e*/        keySize;
    uint8_t /*CipherSuite_e*/   cipher_type;

/* 32 bytes */
    uint8_t           key[MAX_KEY_SIZE];

/* 2 bytes */
    uint16_t          AcSeqNum16;

/* 4 bytes */
    uint32_t          AcSeqNum32;

} SetKey_t;
#endif

/******************************************************************************

    CHANNELS, BAND & REG DOMAINS definitions

******************************************************************************/


typedef uint8_t Channel_e;

#if 0
// Don't change the enumeration as it is use in other places !!!
typedef enum
{
    RADIO_BAND_2_4GHZ = 0,  /* 2.4 Ghz band */
    RADIO_BAND_5GHZ = 1,    /* 5 Ghz band */
    RADIO_BAND_JAPAN_4_9_GHZ = 2,
    DEFAULT_BAND = RADIO_BAND_2_4GHZ,
    INVALID_BAND = 0x7E,
    MAX_RADIO_BANDS = 0x7F
} RadioBand_e;



// 27-JUN-2011 Boaz: 40MHz bandwidth support
// according to the existing enum in NLCP: nl80211_channel_type
typedef enum
{
    NLCP_CHAN_NO_HT     ,   /* 40MHz disabled */
    NLCP_CHAN_HT20      ,   /* 40MHz disabled */
    NLCP_CHAN_HT40MINUS ,   /* 40MHz enabled, secondary channel is above the primary channel */
    NLCP_CHAN_HT40PLUS  ,   /* 40MHz enabled, secondary channel is below the primary channel */
    NLCP_CHAN_INVALID   = 0xFF
} BandWidthSettings_e;
#endif

/******************************************************************************
Role API
******************************************************************************/
typedef uint8_t RoleID_t;

/* CMD_PARAMS_HOST_ROLE_DEFINITION - A macro to make sure all RoleID parameters use the same convention */
#define CMD_PARAMS_HOST_ROLE_DEFINITION RoleID_t RoleID;
#if 0
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
#endif


typedef uint8_t Role_e;


/*************************************************
 *     MACROS
 *************************************************/


#define ROLE_IS_TYPE_DEVICE(roleType)              (ROLE_DEVICE == (roleType))

#define ROLE_IS_TYPE_TRANSCEIVER(roleType)         (ROLE_TRANSCEIVER == (roleType))

#define ROLE_IS_TYPE_P2P_CLIENT(roleType)          (ROLE_P2P_CL == (roleType))

#define ROLE_IS_TYPE_P2P_GO(roleType)              (ROLE_P2P_GO == (roleType))

#define ROLE_IS_TYPE_P2P(roleType)              ( ROLE_IS_TYPE_P2P_CLIENT(roleType) || ROLE_IS_TYPE_P2P_GO(roleType) )

#define ROLE_IS_TYPE_STA(roleType)               (ROLE_STA == (roleType))

#define ROLE_IS_TYPE_AP(roleType)               (ROLE_AP == (roleType))

#define ROLE_IS_TYPE_AP_BASED(roleType)          ((ROLE_AP == (roleType))||(ROLE_P2P_GO == (roleType)))

#define ROLE_IS_TYPE_STA_BASED(roleType)        ((ROLE_P2P_CL == (roleType))||(ROLE_STA == (roleType)))

#define ROLE_IS_TYPE_STA_BASED_OR_DEVICE(roleType) ((ROLE_P2P_CL == (roleType))||(ROLE_STA == (roleType)) || (ROLE_DEVICE == (roleType)))

#define ROLE_IS_TYPE_AP_BASED_OR_DEVICE(roleType) ((ROLE_P2P_GO == (roleType))||(ROLE_AP == (roleType)) || (ROLE_DEVICE == (roleType)))


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



/** \enum EScanResultTag
 * \brief Scan Debug Tags
 *
 * \par Description
 * Enumeration of the differnet Scan Result Tags possible
 *
 * \sa
 */
typedef enum
{
/*  0   */  SCAN_RESULT_TAG_CURENT_BSS = 0,         /**< */
/*  1   */  SCAN_RESULT_TAG_P2P_DISCOVERY,          /**< */
/*  2   */  SCAN_RESULT_TAG_PERIODIC,               /**< */
/*  3   */  SCAN_RESULT_TAG_MEASUREMENT,            /**< */
/*  4   */  SCAN_RESULT_TAG_ONE_SHOT,               /**< */
 /* 5   */  SCAN_RESULT_TAG_MAX_NUMBER              /**< */
} EScanResultTag;

#define IS_SITE_SRUVEY_SCAN(scan_type)  ( (SCAN_REQUEST_SURVEY_SCAN == scan_type) || (SCAN_REQUEST_SURVEY_SCAN == scan_type) )
#define IS_ONE_SHOT_SCAN(scan_type)     ( (SCAN_REQUEST_ONE_SHOT == scan_type) || (SCAN_REQUEST_ONE_SHOT == scan_type) )


#if 0
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
#endif

// Maximum number of supported scan plans for scheduled scan, supported by the driver
#define SCAN_MAX_SCHED_SCAN_PLANS           (12)


#if 0
typedef enum
{
    WLANLINK_TYPE_SYSTEM,       // TODO - remove if not in use
    WLANLINK_TYPE_SPECIFIC,     // Serves for connection
    WLANLINK_TYPE_BRCST,
    WLANLINK_TYPE_GLOBAL
} linkType_e;
#endif

#if 0
typedef enum
{
    SLOT_TIME_LONG = 0,     /* the WiLink uses long (20 us) slots*/
    SLOT_TIME_SHORT = 1,    /* the WiLink uses short (9 us) slots*/
    DEFAULT_SLOT_TIME = SLOT_TIME_SHORT,
    MAX_SLOT_TIMES = 0xFF
} SlotTime_e;
#endif


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






#define IS_MCS_PREAMBLE(preamble)   ((preamble >= PREAMBLE_TYPE_N_MIXED_MODE) && (preamble <= PREAMBLE_TYPE_AC_VHT))


#define ROLE_ID_NONE 0xFF



/******************************************************************************

Transmit-Descriptor RATE-SET field definitions...

******************************************************************************/

typedef uint32_t EHwRateBitFiled;/* set with EHwBitRate values */

typedef struct
{

    uint32_t       uInactivity;
    uint32_t       basicRateSetBM;
    uint32_t       localSupportedRatesBM;
    uint32_t       remotePeerSupportedRatesBM;
    uint16_t       beaconInterval;
    uint8_t        dtimInterval;

    Bool_e          WMM;


}RoleCommonParam_t;
#if 0
typedef struct
{
    // RF related
    uint8_t/*RadioBand_e*/          band;
    Channel_e                       channelNumber;
    BandWidthSettings_e             bandwidth;
}ApRFParam_t;
#endif
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
#define REG_DOMAIN_MAX_REG_CLASS_NUM       10
#define NUM_OF_CHANNELS_24              14
#define A_BAND_CHANNEL_COUNT            26
#define TWD_CALIBRATION_CHANNEL_2_4_MIN 1

#define GET_BAND_BY_CHANNEL(chan)      ( ((unsigned char)(chan) <= NUM_OF_CHANNELS_24) ? RADIO_BAND_2_4GHZ : RADIO_BAND_5GHZ )

/**
 * \def WLANTOHL
 * \brief  Handle endianness of Long in Little Endian host when opposing Big Endian data - swap bytes
 */
#define WLANTOHL(x)                 BYTE_SWAP_LONG (x)
/**
 * \def WLANTOHS
 * \brief  Handle endianness of Word in Little Endian host when opposing Big Endian data - swap bytes
 */
#define WLANTOHS(x)                 BYTE_SWAP_WORD (x)
/**
 * \def HTOWLANL
 * \brief  Handle endianness of Long in Little Endian host when opposing Big Endian data - swap bytes
 */
#define HTOWLANL(x)                 BYTE_SWAP_LONG (x)
/**
 * \def HTOWLANS
 * \brief  Handle endianness of Word in Little Endian host when opposing Big Endian data - swap bytes
 */
#define HTOWLANS(x)                 BYTE_SWAP_WORD (x)

#ifdef CC33xx

typedef struct
{
    // RF related
    uint8_t/*RadioBand_e*/          band;
    Channel_e                       channelNumber;
    BandWidthSettings_e             bandwidth;
}ApRFParam_t;



/* Shared Types */
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




/******************************************************************************
    ID:       CMD_SET_PS_MODE
    Desc:     This command turns ON/OFF Power save protocol on the WiLink. 
              After HW configuration, FW sends Null data packet to the AP with Power 
              Management bit set accordingly to the field "Mode" of this command 
              structure. After processing this command, the FW generates the 
              PS_COMPLETE event.
    Params:   PSModeParameters_t - see below.

******************************************************************************/

typedef enum
{
    STATION_AUTO_PS_MODE,
    STATION_ACTIVE_MODE,
    STATION_POWER_SAVE_MODE,
	STATION_NUM_OF_MODES
} StationPSMode_enum;

#ifdef HOST_COMPILE
typedef uint8_t StationPowerSaveMode_e;
#else
typedef StationPSMode_enum StationPowerSaveMode_e;
#endif


#else // CC33xx
/******************************************************************************

    RxIfDescriptor_t

    the structure of the Rx Descriptor recieved by HOST.

******************************************************************************/
typedef enum
{
    TAG_CLASS_UNKNOWN       = 0,
    TAG_CLASS_MANAGEMENT    = 1, /* other than Beacon or Probe Resp */
    TAG_CLASS_DATA          = 2,
    TAG_CLASS_QOS_DATA      = 3,
    TAG_CLASS_BCN_PRBRSP    = 4,
    TAG_CLASS_EAPOL         = 5,
    TAG_CLASS_BA_EVENT      = 6,
    TAG_CLASS_AMSDU         = 7,
    TAG_CLASS_LOGGER        = 8,
    TAG_CLASS_IAPP          = 9 /*USED BY MCP for CCX*/
} PacketClassTag_enum;

typedef struct
{    
    uint16_t              length;             /* Length of payload (including headers)*/
                                            
    uint8_t               status;             /* status is now a bit-field structure:         */
                                            /* Bits[7:6] = checsum status indication.       */
                                            /* Bits[5:3] = Process_ID_Tag                   */
                                            /* Bits[2:0] = Error code:                      */
                                            /*             0  ==> SUCCESS                   */
                                            /*             1  ==> RX_DECRYPT_FAIL           */
                                            /*             2  ==> RX_MIC_FAIL               */
                                            /*             3  ==> STA_NOT_FOUND             */
                                            /*             4  ==> KEY_NOT_FOUND             */
                                            /*                                              */
                                            
    uint8_t               flags;              /* See RX_DESC_xxx above */
                                            
    uint8_t/*TxRateIndex_t*/  rate;               /* Recevied Rate:at ETxRateClassId format */
                                            
    uint8_t               channel;            /* The received channel*/
                                            
    int8_t                rx_level;           /* The computed RSSI value in db of current frame */  
                                            
    uint8_t               rx_snr;             /* The computed SNR value in db of current frame */
                                            
    uint32_t              timestamp;          /* Timestamp in microseconds,     */

    uint8_t/*PacketClassTag_enum*/   packet_class_tag;   /* Packet classification tagging info */
    uint8_t               hlid;               /* Host Link ID associated with the source of the frame  */
    uint8_t               extraBytes;         /* Number of padding bytes added to actual packet length */

    uint8_t               driverFlags;        /* holds the driver flags to be used internally */

} RxIfDescriptor_t;
#endif

#endif /* PUBLIC_TYPES_H*/
