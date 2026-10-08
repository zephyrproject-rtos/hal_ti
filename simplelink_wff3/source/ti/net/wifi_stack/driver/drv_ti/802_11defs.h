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
/****************************************************************************
 *
 *   MODULE:  802_11defs.h
 *   PURPOSE: Contains 802.11 defines/structures
 *
 ****************************************************************************/

#ifndef _802_11_INFO_DEFS_H
#define _802_11_INFO_DEFS_H

#include "osi_type.h"
#include "cc3xxx_public_types.h"
#include "macro_utils.h"
#include "tx.h"


#define BASE_FREQ_2_4   (2407)
#define BASE_FREQ_5_0   (5000)
#define FREQ_CH_14      (2484)

#define DOT11_OUI_LEN                       4
#define DOT11_COUNTRY_STRING_LEN            3
#define DOT11_COUNTRY_TRIPLETS_SIZE         3
#define DOT11_MAX_SUPPORTED_RATES           32

/* Maximum size of beacon or probe-request information element */
#define DOT11_WSC_PROBE_REQ_MAX_LENGTH 80

/* Maximum size of beacon or probe-request variable information elements */
#define DOT11_MAX_VARIABLE_IES_LEN  256


/* FrameControl field of the 802.11 header  */

/**/
/* bit 15    14     13     12     11     10      9     8     7-4     3-2      1-0*/
/* +-------+-----+------+-----+-------+------+------+----+---------+------+----------+*/
/* | Order | WEP | More | Pwr | Retry | More | From | To | Subtype | Type | Protocol |*/
/* |       |     | Data | Mgmt|       | Frag | DS   | DS |         |      | Version  |*/
/* +-------+-----+------+-----+-------+------+------+----+---------+------+----------+*/
/*     1      1      1     1      1       1      1     1       4       2        2*/


#define DOT11_FC_PROT_VERSION_MASK   ( 3 << 0 )
#define DOT11_FC_PROT_VERSION        ( 0 << 0 )

#define DOT11_FC_TYPE_MASK           ( 3 << 2 )
typedef enum
{
  DOT11_FC_TYPE_MGMT         = ( 0 << 2 ),
  DOT11_FC_TYPE_CTRL         = ( 1 << 2 ),
  DOT11_FC_TYPE_DATA         = ( 2 << 2 )
} dot11_Fc_Type_e;

#define DOT11_FC_SUB_MASK           ( 0x0f << 4 )
typedef enum
{
  /* Management subtypes */
  DOT11_FC_SUB_ASSOC_REQ     = (    0 << 4 ),
  DOT11_FC_SUB_ASSOC_RESP    = (    1 << 4 ),
  DOT11_FC_SUB_REASSOC_REQ   = (    2 << 4 ),
  DOT11_FC_SUB_REASSOC_RESP  = (    3 << 4 ),
  DOT11_FC_SUB_PROBE_REQ     = (    4 << 4 ),
  DOT11_FC_SUB_PROBE_RESP    = (    5 << 4 ),
  DOT11_FC_SUB_BEACON        = (    8 << 4 ),
  DOT11_FC_SUB_ATIM          = (    9 << 4 ),
  DOT11_FC_SUB_DISASSOC      = (   10 << 4 ),
  DOT11_FC_SUB_AUTH          = (   11 << 4 ),
  DOT11_FC_SUB_DEAUTH        = (   12 << 4 ),
  DOT11_FC_SUB_ACTION        = (   13 << 4 ),

  /* Control subtypes */
  DOT11_FC_SUB_BAR                    = (    8 << 4 ),
  DOT11_FC_SUB_BA                     = (    9 << 4 ),
  DOT11_FC_SUB_PS_POLL                = (   10 << 4 ),
  DOT11_FC_SUB_RTS                    = (   11 << 4 ),
  DOT11_FC_SUB_CTS                    = (   12 << 4 ),
  DOT11_FC_SUB_ACK                    = (   13 << 4 ),
  DOT11_FC_SUB_CF_END                 = (   14 << 4 ),
  DOT11_FC_SUB_CF_END_CF_ACK          = (   15 << 4 ),

  /* Data subtypes */
  DOT11_FC_SUB_DATA                   = (    0 << 4 ),
  DOT11_FC_SUB_DATA_CF_ACK            = (    1 << 4 ),
  DOT11_FC_SUB_DATA_CF_POLL           = (    2 << 4 ),
  DOT11_FC_SUB_DATA_CF_ACK_CF_POLL    = (    3 << 4 ),
  DOT11_FC_SUB_NULL_FUNCTION          = (    4 << 4 ),
  DOT11_FC_SUB_CF_ACK                 = (    5 << 4 ),
  DOT11_FC_SUB_CF_POLL                = (    6 << 4 ),
  DOT11_FC_SUB_CF_ACK_CF_POLL         = (    7 << 4 ),
  DOT11_FC_SUB_DATA_QOS               = (    8 << 4 ),
  DOT11_FC_SUB_DATA_NULL_QOS          = (   12 << 4 )
} dot11_Fc_Sub_Type_e;

#define  DOT11_FC_TYPESUBTYPE_MASK    ( DOT11_FC_TYPE_MASK | DOT11_FC_SUB_MASK )
typedef enum
{
  DOT11_FC_ASSOC_REQ           = ( DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_ASSOC_REQ           ),
  DOT11_FC_ASSOC_RESP          = ( DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_ASSOC_RESP          ),
  DOT11_FC_REASSOC_REQ         = ( DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_REASSOC_REQ         ),
  DOT11_FC_REASSOC_RESP        = ( DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_REASSOC_RESP        ),
  DOT11_FC_PROBE_REQ           = ( DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_PROBE_REQ           ),
  DOT11_FC_PROBE_RESP          = ( DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_PROBE_RESP          ),
  DOT11_FC_BEACON              = ( DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_BEACON              ),
  DOT11_FC_ATIM                = ( DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_ATIM                ),
  DOT11_FC_DISASSOC            = ( DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_DISASSOC            ),
  DOT11_FC_AUTH                = ( DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_AUTH                ),
  DOT11_FC_DEAUTH              = ( DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_DEAUTH              ),
  DOT11_FC_ACTION              = ( DOT11_FC_TYPE_MGMT | DOT11_FC_SUB_ACTION              ),
  DOT11_FC_PS_POLL             = ( DOT11_FC_TYPE_CTRL | DOT11_FC_SUB_PS_POLL             ),
  DOT11_FC_RTS                 = ( DOT11_FC_TYPE_CTRL | DOT11_FC_SUB_RTS                 ),
  DOT11_FC_CTS                 = ( DOT11_FC_TYPE_CTRL | DOT11_FC_SUB_CTS                 ),
  DOT11_FC_ACK                 = ( DOT11_FC_TYPE_CTRL | DOT11_FC_SUB_ACK                 ),
  DOT11_FC_CF_END              = ( DOT11_FC_TYPE_CTRL | DOT11_FC_SUB_CF_END              ),
  DOT11_FC_CF_END_CF_ACK       = ( DOT11_FC_TYPE_CTRL | DOT11_FC_SUB_CF_END_CF_ACK       ),
  DOT11_FC_DATA                = ( DOT11_FC_TYPE_DATA | DOT11_FC_SUB_DATA                ),
  DOT11_FC_DATA_CF_ACK         = ( DOT11_FC_TYPE_DATA | DOT11_FC_SUB_DATA_CF_ACK         ),
  DOT11_FC_DATA_CF_POLL        = ( DOT11_FC_TYPE_DATA | DOT11_FC_SUB_DATA_CF_POLL        ),
  DOT11_FC_DATA_CF_ACK_CF_POLL = ( DOT11_FC_TYPE_DATA | DOT11_FC_SUB_DATA_CF_ACK_CF_POLL ),
  DOT11_FC_DATA_NULL_FUNCTION  = ( DOT11_FC_TYPE_DATA | DOT11_FC_SUB_NULL_FUNCTION       ),
  DOT11_FC_CF_ACK              = ( DOT11_FC_TYPE_DATA | DOT11_FC_SUB_CF_ACK              ),
  DOT11_FC_CF_POLL             = ( DOT11_FC_TYPE_DATA | DOT11_FC_SUB_CF_POLL             ),
  DOT11_FC_CF_ACK_CF_POLL      = ( DOT11_FC_TYPE_DATA | DOT11_FC_SUB_CF_ACK_CF_POLL      ),
  DOT11_FC_DATA_QOS            = ( DOT11_FC_TYPE_DATA | DOT11_FC_SUB_DATA_QOS            ),
  DOT11_FC_DATA_NULL_QOS       = ( DOT11_FC_TYPE_DATA | DOT11_FC_SUB_DATA_NULL_QOS       )
} dot11_Fc_Type_Sub_Type_e;

typedef enum
{
  DOT11_FC_TO_DS               = ( 1 << 8  ),//To the distribution system
  DOT11_FC_FROM_DS             = ( 1 << 9  ),//Exit From the distribution system
  DOT11_FC_MORE_FRAG           = ( 1 << 10 ),//Last or unfragmented Frame
  DOT11_FC_RETRY               = ( 1 << 11 ),//Re-transmission
  DOT11_FC_PWR_MGMT            = ( 1 << 12 ),//Power management
  DOT11_FC_MORE_DATA           = ( 1 << 13 ),//More data
  DOT11_FC_WEP                 = ( 1 << 14 ),//protected frame
  DOT11_FC_ORDER               = ( 1 << 15 ) //strict order
} dot11_Fc_Other_e;

typedef enum
{
  DOT11_CAPABILITY_ESS               = ( 1 ),
  DOT11_CAPABILITY_IESS              = ( 1 << 1 ),
  DOT11_CAPABILITY_CF_POLLABE        = ( 1 << 2 ),
  DOT11_CAPABILITY_CF_POLL_REQ       = ( 1 << 3 ),
  DOT11_CAPABILITY_PRIVACY           = ( 1 << 4 ),
  DOT11_CAPABILITY_PREAMBLE          = ( 1 << 5 ),
  DOT11_CAPABILITY_PBCC              = ( 1 << 6 ),
  DOT11_CAPABILITY_AGILE             = ( 1 << 7 )
} dot11_Capability_e;

#define  DOT11_FC_TO_DS_SHIFT        8
#define  DOT11_FC_FROM_DS_SHIFT      9
#define  DOT11_FC_MORE_FRAG_SHIFT   10
#define  DOT11_FC_RETRY_SHIFT       11
#define  DOT11_FC_PWR_MGMT_SHIFT    12
#define  DOT11_FC_MORE_DATA_SHIFT   13
#define  DOT11_FC_WEP_SHIFT         14
#define  DOT11_FC_ORDER_SHIFT       15


#define IS_WEP_ON(fc)       ((1 << DOT11_FC_WEP_SHIFT) & (fc))
#define IS_HT_ON(fc)        ((1 << DOT11_FC_ORDER_SHIFT) & (fc))



#define IS_DATA(fc) (((DOT11_FC_TYPE_MASK) & (fc)) == DOT11_FC_TYPE_DATA)
#define IS_CTRL(fc)         (((DOT11_FC_TYPE_MASK) & (fc)) == DOT11_FC_TYPE_CTRL)
#define IS_MGMT(fc)         (((DOT11_FC_TYPE_MASK) & (fc)) == DOT11_FC_TYPE_MGMT)
#define IS_LEGACY_DATA(fc)  (((DOT11_FC_TYPESUBTYPE_MASK) & (fc)) == DOT11_FC_DATA)
#define IS_AUTH(fc)         (((DOT11_FC_AUTH) & (fc)) == DOT11_FC_AUTH)
#define IS_QOS_FRAME(fc)    ((((fc) & (DOT11_FC_TYPESUBTYPE_MASK)) == DOT11_FC_DATA_QOS)   ||   \
                             (((fc) & (DOT11_FC_TYPESUBTYPE_MASK)) == DOT11_FC_DATA_NULL_QOS) )
#define IS_HT_FRAME(fc)      (((DOT11_FC_ORDER) & (fc)) == DOT11_FC_ORDER)
#define IS_PROTECTED_FRAME(fc)    (((DOT11_FC_WEP) & (fc)) == DOT11_FC_WEP)

#define TUs_TO_MSECs(x)     (((x) << 10) / 1000)

#define TIME_STAMP_LEN  8
#define BEACON_PROBRESP_FIXED_LENGTH_FIELDS  12

/* SequenceControl field of the 802.11 header */
/**/
/* bit    15 - 4           3 - 0*/
/* +-------------------+-----------+*/
/* |  Sequence Number  | Fragment  |*/
/* |                   |  Number   |*/
/* +-------------------+-----------+*/
/*         12                4*/

typedef enum
{
  DOT11_SC_FRAG_NUM_MASK = ( 0xf   << 0 ),
  DOT11_SC_SEQ_NUM_MASK  = ( 0xfff << 4 )
} dot11_Sc_t;

/* QoS Control field of the 802.11 header */
#define DOT11_QOS_CONTROL_FIELD_TID_BITS            0x0007 /* changed from 0x000f due to WMM supports only 3 out of the 4 bits */
#define DOT11_QOS_CONTROL_FIELD_A_MSDU_BITS         0x0080
#define DOT11_QOS_CONTROL_FIELD_ACK_POLICY_BITS     0x0060

#define DOT11_QOS_CONTROL_ACK                       0x0000
#define DOT11_QOS_CONTROL_DONT_ACK                  0x0020
#define DOT11_QOS_CONTROL_BLOCK_ACK                 0x0060

#define MAC_ADDR_LEN         (6)   /* In Bytes */

typedef uint8_t   macAddress_t [MAC_ADDR_LEN];

typedef struct
{
    uint16_t        fc;//    FrameType_t frameType; FrameCtrl_t frameCtrl;
    uint16_t        duration;
    macAddress_t  address1;
    macAddress_t  address2;
    macAddress_t  address3;
    uint16_t        seqCtrl;
    uint16_t        qosControl;//this field exists only if qos is enabled
/*  TMacAddr    address4;*/
}dot11_header_t;

typedef struct
{
    uint8_t    pn0;
    uint8_t    pn1;
    uint8_t    reserved;
    uint8_t    extIVkeyID;
    uint8_t    pn2;
    uint8_t    pn3;
    uint8_t    pn4;
    uint8_t    pn5;
} dot11_rsn_header_t;

typedef struct
{
    uint16_t        fc;
    uint16_t        duration;
    macAddress_t  address1;
    macAddress_t  address2;
    macAddress_t  address3;
    uint16_t        seqCtrl;
} legacy_dot11_header_t;

/* changed to fit double buffer size - S.G */
/*#define MAX_MANAGEMENT_FRAME_BODY_LEN 2312*/
#define MAX_MANAGEMENT_FRAME_BODY_LEN   1476

typedef struct
{
    uint16_t          fc;
    uint16_t          duration;
    macAddress_t    DA;
    macAddress_t    SA;
    macAddress_t    BSSID;
    uint16_t          seqCtrl;
}__attribute__ ((packed)) dot11_mgmtHeader_t;


typedef struct
{
    uint8_t     DSAP;
    uint8_t     SSAP;
    uint8_t     Control;
    uint8_t     OUI[3];
    uint16_t    Type;
}Wlan_LlcHeader_T;

typedef struct
{
    uint16_t        fc;
    uint16_t        AID;
    macAddress_t  BSSID;
    macAddress_t  TA;
} dot11_PsPollFrameHeader_t;

typedef struct
{
    uint16_t        fc;
    uint16_t        duration;
    macAddress_t  RA;
    macAddress_t  TA;
} dot11_BarFrameHeader_t;

#define IEEE80211_HT_CTL_LEN                     4

#define FCS_SIZE    4

#define WLAN_HDR_LEN                            24
#define WLAN_HT_HDR_LEN                         28

#ifndef WLAN_QOS_HDR_LEN
#define WLAN_QOS_HDR_LEN                        26
#endif
#ifndef WLAN_QOS_HT_HDR_LEN
#define WLAN_QOS_HT_HDR_LEN                     30
#endif
#ifndef WLAN_MAX_HDR_SIZE
#define WLAN_MAX_HDR_SIZE                       30
#endif
#ifndef WLAN_QOS_CONTROL_FIELD_LEN
#define WLAN_QOS_CONTROL_FIELD_LEN              2
#endif
#ifndef WLAN_HT_CONTROL_FIELD_LEN
#define WLAN_HT_CONTROL_FIELD_LEN               4
#endif
#ifndef WLAN_SNAP_HDR_LEN
#define WLAN_SNAP_HDR_LEN                       8
#endif
#ifndef WLAN_WITH_SNAP_HEADER_MAX_SIZE
#define WLAN_WITH_SNAP_HEADER_MAX_SIZE          (WLAN_HDR_LEN + WLAN_SNAP_HDR_LEN)
#endif
#ifndef WLAN_WITH_SNAP_QOS_HEADER_MAX_SIZE
#define WLAN_WITH_SNAP_QOS_HEADER_MAX_SIZE      (WLAN_QOS_HDR_LEN + WLAN_SNAP_HDR_LEN)
#endif

#define GET_MAX_HEADER_SIZE(macHeaderPointer,headerSize)                                \
    if (IS_QOS_FRAME(*(uint16_t*)(macHeaderPointer)))      \
        {                                                                               \
       if (IS_HT_ON(*(uint16_t*)(macHeaderPointer)))    \
           *headerSize = WLAN_QOS_HT_HDR_LEN;               \
       else                                                 \
                 *headerSize = WLAN_QOS_HDR_LEN;                                        \
     }\
     else                                                   \
     {\
       if (IS_HT_ON(*(uint16_t*)(macHeaderPointer)))    \
           *headerSize = WLAN_HT_HDR_LEN;                   \
       else                                                 \
           *headerSize = WLAN_HDR_LEN;                      \
     }

/****************************************************************************************
    The next table is defined in 802.11 spec section 7.2.2 for the address field contents :
    To DS   From DS     Address 1    Address 2  Address 3    Address 4
    -------------------------------------------------------------------
    0           0           DA          SA          BSSID       N/A
    0           1           DA          BSSID       SA          N/A
    1           0           BSSID       SA          DA          N/A
    1           1           RA          TA          DA          SA

NOTE: We only support packets coming from within the DS (i.e. From DS = 0)
*****************************************************************************************/
/* return the destination address used in *dot11_header_t */
#define GET_DA_FROM_DOT11_HEADER_T(pDot11Hdr)   ((pDot11Hdr->fc & DOT11_FC_TO_DS) ? (pDot11Hdr->address3) : (pDot11Hdr->address1))


/*
 * MANAGEMENT
 * -----------------
 */

/* mgmt body max length */
#define MAX_MGMT_BODY_LENGTH                2312
/* maximal length of beacon body - increased to 1600 to support WiFi certification
   tests that require handling beacons up to 1500 bytes (e.g., test 10957) */
   #define MAX_BEACON_BODY_LENGTH              1600

/* length of standart beacon body (maximum for .11N ~230)- note that actual beacons may actually be longer
   than this size, at least according to the spec, but so far no larger beacon was seen */

#define STANDART_BEACON_BODY_LENGTH         400

#define ASSOC_RESP_FIXED_DATA_LEN           6
#define ASSOC_REQ_FIXED_DATA_LEN            4

#define ASSOC_RESP_AID_MASK                 0x3FFF  /* The AID is only in 14 LS bits. */

/* general mgmt frame structure */
typedef struct
{
    dot11_mgmtHeader_t  hdr;
    uint8_t               body[MAX_MGMT_BODY_LENGTH];
}  dot11_mgmtFrame_t;

/* Capabilities Information Field - IN THE AIR */
/**/
/*  bit  15      14       13         12        11         10      9      8      7   -   0*/
/* +----------+------+----------+---------+----------+---------+------+-----+---------------+*/
/* |  Channel |      |  Short   | Privacy | CF Poll  |   CF    |      |     |   RESERVED    |   */
/* |  Agility | PBCC | Preamble |         | Request  | Pollable| IBSS | ESS |               |*/
/* +----------+------+----------+---------+----------+---------+------+-----+---------------+   */
/*       1        1       1          1         1          1       1      1*/


/* Capabilities Information Field - IN THE MGMT SOFTWARE AFTER THE SWAP */
/**/
/* bit 15 - 8         7        6       5          4         3          2       1      0*/
/* +------------+----------+------+----------+---------+----------+---------+------+-----+*/
/* |            |  Channel |      |  Short   | Privacy | CF Poll  |   CF    |      |     |*/
/* |  Reserved  |  Agility | PBCC | Preamble |         | Request  | Pollable| IBSS | ESS |*/
/* +------------+----------+------+----------+---------+----------+---------+------+-----+*/
/*       8            1        1       1          1         1          1       1      1*/

/* Capabilities Information Field - IN THE MGMT SOFTWARE AFTER THE SWAP */
/**/
/*     15        14       13      12      11      10         9       8       */
/* +--------+---------+-------+-------+-------+-----------+------+----------+*/
/* | Immed. | Delayed | DSSS- | Radio | APSD  | short     | QOS  | spectrum |*/
/* | BA     | BA      | OFDM  | Mng   |       | slot time |      | mgmt     |*/
/* +--------+---------+-------+-------+-------+-----------+------+----------+*/




typedef enum
{ 
  DOT11_CAPS_ESS             = ( 1 << 0 ),
  DOT11_CAPS_IBSS            = ( 1 << 1 ),
  DOT11_CAPS_CF_POLLABLE     = ( 1 << 2 ),
  DOT11_CAPS_CF_POLL_REQUEST = ( 1 << 3 ),
  DOT11_CAPS_PRIVACY         = ( 1 << 4 ),
  DOT11_CAPS_SHORT_PREAMBLE  = ( 1 << 5 ),
  DOT11_CAPS_PBCC            = ( 1 << 6 ),
  DOT11_CAPS_CHANNEL_AGILITY = ( 1 << 7 ),
  DOT11_SPECTRUM_MANAGEMENT  = ( 1 << 8 ),
  DOT11_CAPS_QOS_SUPPORTED   = ( 1 << 9 ),
  DOT11_CAPS_SHORT_SLOT_TIME = (1  << 10),

  DOT11_CAPS_APSD_SUPPORT    = ( 1 << 11),
  DOT11_CAPS_RRM_ENABLED     = ( 1 << 12),
  DOT11_CAPS_DELAYED_BA      = ( 1 << 14),
  DOT11_CAPS_IMMEDIATE_BA    = ( 1 << 15)

} dot11_capabilities_e;

typedef enum 
{
    /* ESS */
    CAP_ESS_MASK            = 1,
    CAP_ESS_SHIFT           = 0,

    /* IBSS */
    CAP_IBSS_MASK           = 1,
    CAP_IBSS_SHIFT          = 1,

    /* CF Pollable */
    CAP_CF_POLL_MASK        = 1,
    CAP_CF_POLL_SHIFT       = 2,

    /* CF Poll request */
    CAP_CF_REQ_MASK         = 1,
    CAP_CF_REQ_SHIFT        = 3,

    /* Privacy */
    CAP_PRIVACY_MASK        = 1,
    CAP_PRIVACY_SHIFT       = 4,

    /* Short Preamble*/
    CAP_PREAMBLE_MASK       = 1,
    CAP_PREAMBLE_SHIFT      = 5,

    /* PBCC */
    CAP_PBCC_MASK           = 1,
    CAP_PBCC_SHIFT          = 6,

    /* Agile */
    CAP_AGILE_MASK          = 1,
    CAP_AGILE_SHIFT         = 7,

    /* Slot time */
    CAP_SLOT_TIME_MASK      = 1,
    CAP_SLOT_TIME_SHIFT     = 10,

    /* APSD */
    CAP_APSD_MASK           = 1,
    CAP_APSD_SHIFT          = 11


} wdrv_mgmtCapabilities_e;


/*
 * 802.11 Information elements
 * ---------------------------
 */
typedef struct __PACKED__
{
    uint8_t eleId;
    uint8_t eleLen;
}dot11_eleHdr_t;


#define HDR_ELE_ID_FIELD    (0)
#define HDR_LENGTH_FIELD    (1)

/* fixed fields lengths, except of currentAP & timestamp*/
#define FIX_FIELD_LEN       (2)

/* SSID Information Element */
//#define DOT11_SSID_ELE_ID (0)

/* Max SSID length */
#define DOT11_SSID_MAX_LEN             (32)
#define DOT11_MAX_WPSIE_SIZE           (350)
#define DOT11_MAX_ERPIE_SIZE            (1)


typedef struct __PACKED__
{
    uint8_t       len;                    /**< SSID Length        */
    char        str[ DOT11_SSID_MAX_LEN ];  /**< SSID string buffer */

}  ssid_t;

typedef struct  __PACKED__
{
  dot11_eleHdr_t    hdr;
  char              serviceSetId[DOT11_SSID_MAX_LEN];
}  dot11_SSID_t;

typedef struct  __PACKED__
{
  dot11_eleHdr_t    hdr;
  char              wpsIeData[DOT11_MAX_WPSIE_SIZE];
}  dot11_wps_t;

typedef struct  __PACKED__
{
  dot11_eleHdr_t    hdr;
  char              erpIeData[DOT11_MAX_ERPIE_SIZE];
}  dot11_erp_t;


/* Supportted rates Information Element */
#define DOT11_SUPPORTED_RATES_ELE_ID        1
#define DOT11_EXT_SUPPORTED_RATES_ELE_ID        50
typedef struct  __PACKED__
{
  dot11_eleHdr_t hdr;
  uint8_t rates[DOT11_MAX_SUPPORTED_RATES];
}dot11_RATES_t;


/* ERP Information Element */
#define ERP_PARAMS_ELE_LEN                    1

#define DOT11_ERP_IE_ID 42
typedef struct __PACKED__
{
    dot11_eleHdr_t  hdr;
    uint8_t           ctrl;
}  dot11_ERP_t;


#define ERP_NON_ERP_PRESENT_BITMASK            (0x01)
#define ERP_PROTECTION_BITMASK                 (0x02)
#define ERP_BARKER_REAMBLE_MOD_BITMASK         (0x04)

#define ERP_NON_ERP_PRESENT(ctrl)  (ctrl & ERP_NON_ERP_PRESENT_BITMASK   )
#define ERP_PROT(ctrl)            ((ctrl & ERP_PROTECTION_BITMASK        ) >> 1)
#define ERP_BARKER(ctrl)          ((ctrl & ERP_BARKER_REAMBLE_MOD_BITMASK) >> 2)

#define ERP_PROTECTION_DISABLED             0
#define ERP_PROTECTION_ENABLED              1



/* RSN Information Element */
#define MAX_RSN_IE                          3
#define DOT11_RSN_MAX                       255
typedef struct __PACKED__ //Just make sure it is in continues memory since the info element is being sent as is to the supplicant
{
  dot11_eleHdr_t hdr;
  uint8_t rsnIeData[DOT11_RSN_MAX];
}  dot11_RSN_t;

/* RSN Override Information Elements */
#define DOT11_RSN_OVERRIDE_OUI          {0x50, 0x6f, 0x9a, 0x29}
#define DOT11_RSN_OVERRIDE_2_OUI        {0x50, 0x6f, 0x9a, 0x2a}

/* DS params Information Element */
#define DOT11_DS_PARAMS_ELE_ID      3
#define DOT11_DS_PARAMS_ELE_LEN     1
typedef struct 
{
  dot11_eleHdr_t hdr;
  uint8_t  currChannel;
}  dot11_DS_PARAMS_t;


/* DS params Information Element */
#define DOT11_IBSS_PARAMS_ELE_ID    6
#define DOT11_IBSS_PARAMS_ELE_LEN   2
typedef struct 
{
    dot11_eleHdr_t  hdr;
    uint16_t          atimWindow;
}  dot11_IBSS_PARAMS_t;

#define DOT11_FH_PARAMS_ELE_ID      2
#define DOT11_FH_PARAMS_ELE_LEN     5
typedef struct 
{
    dot11_eleHdr_t  hdr;
    uint16_t          dwellTime;
    uint8_t           hopSet;
    uint8_t           hopPattern;
    uint8_t           hopIndex;
}  dot11_FH_PARAMS_t;




#define DOT11_PARTIAL_VIRTUAL_BITMAP_MAX    3   // 27-8-11, changed from 251 to 2,as we currently don't use more than that.
                                                // (22.2.2018), increased to 3 to support up to 16 peers (aid 1 starts from index 1)
/* tim Information Element */
#define DOT11_TIM_ELE_ID                (5)
#define DOT11_TIM_ELE_LEN               (3 + DOT11_PARTIAL_VIRTUAL_BITMAP_MAX) //1 byte DTIM count + 1 byte DTIM Period +
                                                                               //1 byte bitmap control + 3 bytes partial virtual bitmap
#define DOT11_TIM_SHORT_PARAMS_ELE_LEN  (3 + 1) //Short version of TIM element
                                                //According to the spec - used when all bits in the partial virtual are 0
                                                //1 byte DTIM count + 1 byte DTIM Period + 1 byte bitmap control + 1 byte partial virtual bitmap


typedef struct
{
    unsigned char        aid0_traffic_present    :   1       ;
    unsigned char        partial_vbm_offset      :   7       ;
}   BeaconTimBitmapControl_t                                ;


typedef struct
{
    dot11_eleHdr_t              hdr;
    uint8_t                       dtimCount;
    uint8_t                       dtimPeriod;
    BeaconTimBitmapControl_t    bmapControl;
    uint8_t                       partialVirtualBmap[DOT11_PARTIAL_VIRTUAL_BITMAP_MAX];
}  dot11_TIM_t;
    

typedef struct 
{
    dot11_eleHdr_t  hdr;
    uint8_t           dtimCount;
    uint8_t           dtimPeriod;
    uint8_t           bmapControl;
    uint8_t           partialVirtualBmap;
}  dot11_TIM_Short_t;

/* tim Information Element */
#define DOT11_CF_ELE_ID             4
#define DOT11_CF_PARAMS_ELE_LEN     6
typedef struct 
{
    dot11_eleHdr_t  hdr;
    uint8_t           cfpCount;
    uint8_t           cfpPeriod;
    uint16_t          cfpMaxDuration;
    uint16_t          cfpDurRemain;
}  dot11_CF_PARAMS_t;

/* Challenge text Information Element */
#define DOT11_CHALLENGE_TEXT_ELE_ID     16
#define DOT11_CHALLENGE_TEXT_MAX        253
typedef struct 
{
    dot11_eleHdr_t  hdr;
    uint8_t           text[ DOT11_CHALLENGE_TEXT_MAX ];
}  dot11_CHALLENGE_t;


#define DOT11_NUM_OF_MAX_TRIPLET_CHANNEL    37

typedef struct
{
    uint8_t           firstChannelNumber;  /* the lowest channel number in the sub band*/
    uint8_t           numberOfChannels;    /* number of channels in the sub band */
    uint8_t           maxTxPowerLevel;     /* maximum power, in dBm, allowed to be transmitted */
} dot11_TripletChannel_t;

typedef struct
{
    uint8_t                CountryString[DOT11_COUNTRY_STRING_LEN];            /* This attribute identifies the country in which the station is operating */
    dot11_TripletChannel_t  tripletChannels[DOT11_NUM_OF_MAX_TRIPLET_CHANNEL];  /* sub band triplets */
} dot11_countryIE_t;


/* Country Inforamtion Element */
#define DOT11_COUNTRY_ELE_ID        7
#define DOT11_COUNTRY_ELE_LEN_MAX   ( ((DOT11_NUM_OF_MAX_TRIPLET_CHANNEL+1)*3) + !((DOT11_NUM_OF_MAX_TRIPLET_CHANNEL&0x1)))
typedef struct 
{
    dot11_eleHdr_t  hdr;
    dot11_countryIE_t countryIE;
}  dot11_COUNTRY_t;


/* Power Constraint Information Element */
#define DOT11_POWER_CONSTRAINT_ELE_ID       (32)
#define DOT11_POWER_CONSTRAINT_ELE_LEN      (1)
typedef struct 
{
    dot11_eleHdr_t  hdr;
    uint8_t           powerConstraint;
}  dot11_POWER_CONSTRAINT_t;



/* Power Capability Information Element */
#define DOT11_CAPABILITY_ELE_ID         (33)
#define DOT11_CAPABILITY_ELE_LEN        (2)
typedef struct 
{
    dot11_eleHdr_t  hdr;
    int8_t           minTxPower;
    uint8_t           maxTxPower;
}  dot11_CAPABILITY_t;

/* TPC request Information Element */
#define DOT11_TPC_REQUEST_ELE_ID        (34)
#define DOT11_TPC_REQUEST_ELE_LEN       (0)
typedef struct 
{
    dot11_eleHdr_t  hdr;
}  dot11_TPC_REQUEST_t;

/* TPC report Information Element */
#define DOT11_TPC_REPORT_ELE_ID         (35)
#define DOT11_TPC_REPORT_ELE_LEN        (2)
typedef struct 
{
    dot11_eleHdr_t  hdr;
    uint8_t           transmitPower;
    uint8_t           linkMargin;
}  dot11_TPC_REPORT_t;


// #ifdef  CCX_MODULE_INCLUDED

/* Cell Transmit Power Information Element */
#define DOT11_CELL_TP_ELE_ID            (150)
#define DOT11_CELL_TP_ELE_LEN           (6)

typedef struct
{
    dot11_eleHdr_t  hdr;
    uint8_t           oui[4];
    uint8_t           power;
    uint8_t           reserved;
} dot11_CELL_TP_t;

#define   DOT11_CELL_TP \
    dot11_CELL_TP_t         *cellTP;

// #else   /* CCX_MODULE_INCLUDED */

// #define   DOT11_CELL_TP

// #endif  /* CCX_MODULE_INCLUDED */


/* Channel Supported Information Element */
#define DOT11_CHANNEL_SUPPORTED_ELE_ID  (36)
#define DOT11_CHANNEL_SUPPORTED_ELE_LEN (26)
typedef struct 
{
    dot11_eleHdr_t  hdr;
    uint8_t           supportedChannel[DOT11_CHANNEL_SUPPORTED_ELE_LEN];

}  dot11_CHANNEL_SUPPORTED_t;

/* Channel Switch Announcement Information Element */
#define DOT11_CHANNEL_SWITCH_ELE_ID      (37)
#define DOT11_CHANNEL_SWITCH_ELE_LEN     (3)
#define DOT11_CHANNEL_SWITCH_ACTION_CODE (4)

typedef struct
{
    dot11_eleHdr_t  hdr;
    uint8_t           channelSwitchMode;
    uint8_t           channelNumber;
    uint8_t           channelSwitchCount;
}  dot11_CHANNEL_SWITCH_IE_t;

typedef struct
{
    uint8_t         channelSwitchMode;
    uint8_t         channelNumber;
    uint8_t         channelSwitchCount;
} dot11_CHANNEL_SWITCH_ACTION_FRAME_t;

/* Extended Channel Switch Announcement Information Element */
#define DOT11_EXT_CHANNEL_SWITCH_ELE_ID         (60)
#define DOT11_EXT_CHANNEL_SWITCH_ACTION_CODE    (4)

typedef struct
{
    dot11_eleHdr_t  hdr;
    uint8_t         channelSwitchMode;
    uint8_t         newOperatingClass;
    uint8_t         channelNumber;
    uint8_t         channelSwitchCount;
} dot11_EXT_CHANNEL_SWITCH_IE_t;

typedef struct
{
    uint8_t         actionCode;
    uint8_t         channelSwitchMode;
    uint8_t         newOperatingClass;
    uint8_t         channelNumber;
    uint8_t         channelSwitchCount;
} dot11_EXT_CHANNEL_SWITCH_ACTION_FRAME_t;

#define MAX_NUM_REQ (16)

/* Measurement request Information Element */
#define DOT11_MEASUREMENT_REQUEST_ELE_ID        (38)
#define DOT11_MEASUREMENT_REQUEST_LEN           (2)
#define DOT11_MEASUREMENT_REQUEST_ELE_LEN       (3 + DOT11_MEASUREMENT_REQUEST_LEN*MAX_NUM_REQ)
typedef struct 
{
    dot11_eleHdr_t  hdr;
    uint8_t           measurementToken;
    uint8_t           measurementMode;
    uint8_t           measurementType;
    uint8_t           measurementRequests[DOT11_MEASUREMENT_REQUEST_LEN*MAX_NUM_REQ];
}  dot11_MEASUREMENT_REQUEST_t;


/* Quiet Information Element */
#define DOT11_QUIET_ELE_ID              (40)
#define DOT11_QUIET_ELE_LEN             (6)
typedef struct 
{
    dot11_eleHdr_t  hdr;
    uint8_t           quietCount;
    uint8_t           quietPeriod;
    uint16_t          quietDuration;
    uint16_t          quietOffset;
}  dot11_QUIET_t;


/* QoS Capability Information Element */
#define DOT11_QOS_CAPABILITY_ELE_ID     (46)
#define DOT11_QOS_CAPABILITY_ELE_LEN    (1)

#define AC_APSD_FLAGS_MASK              (1)
#define Q_ACK_BITG_MASK                 (1)
#define MAX_SP_LENGTH_MASK              (3)
#define MORE_DATA_ACK_MASK              (1)

#define AC_VO_APSD_FLAGS_SHIFT          (0)
#define AC_VI_APSD_FLAGS_SHIFT          (1)
#define AC_BK_APSD_FLAGS_SHIFT          (2)
#define AC_BE_APSD_FLAGS_SHIFT          (3)
#define Q_ACK_FLAGS_SHIFT               (4)
#define MAX_SP_LENGTH_SHIFT             (5)
#define MORE_DATA_ACK_SHIFT             (7)

#define QOS_CONTROL_UP_SHIFT            (0)

#define AP_QOS_INFO_UAPSD_MASK          (1)
#define AP_QOS_INFO_UAPSD_SHIFT         (7)

typedef struct
{   
    dot11_eleHdr_t  hdr;
    uint8_t           QosInfoField;
}  dot11_QOS_CAPABILITY_IE_t;


/* P2P Information Element */
#define DOT11_P2P_ELE_ID    (221)
#define DOT11_P2P_OUI       {0x50, 0x6F, 0x9A, 0x09}
#define DOT11_P2P_OUI_LEN   4

/* WME Information Element */
#define DOT11_WME_ELE_ID                (221)
#define DOT11_WME_ELE_LEN               (7)
typedef struct
{
    dot11_eleHdr_t  hdr;
    uint8_t           OUI[3];
    uint8_t           OUIType;
    uint8_t           OUISubType;
    uint8_t           version;
    uint8_t           ACInfoField;
}  dot11_WME_IE_t;



/* WPA Information Element */
#define DOT11_WPA_ELE_ID                (221)
#define DOT11_WPA_OUI                   {0x00, 0x50, 0xF2, 0x01}
#define DOT11_WPA_OUI_LEN               4

//TODO: It is wrong to use dot11_WPA_IE_t since it assumes only one pairwaise suite and one auth key suite
typedef struct
{
    dot11_eleHdr_t  hdr;
    uint8_t                oui[DOT11_OUI_LEN];
    uint8_t                ouiType;
    uint16_t               version;
    uint8_t                groupSuite[DOT11_OUI_LEN+1];
    uint16_t               pairwiseSuiteCnt;
    uint8_t                pairwiseSuite[DOT11_OUI_LEN+1];
    uint16_t               authKeyMngSuiteCnt;
    uint8_t                authKeyMngSuite[DOT11_OUI_LEN+1];
    uint16_t               capabilities;
} dot11_WPA_IE_t;


typedef struct
{
    uint8_t           ACI_AIFSN;
    uint8_t           ECWmin_ECWmax;
    uint16_t          TXOPLimit;
} dot11_QOS_AC_IE_Params_t;

typedef struct
{
    dot11_QOS_AC_IE_Params_t        ACBEParametersRecord;
    dot11_QOS_AC_IE_Params_t        ACBKParametersRecord;
    dot11_QOS_AC_IE_Params_t        ACVIParametersRecord;
    dot11_QOS_AC_IE_Params_t        ACVOParametersRecord;
} dot11_ACParameters_t;


/* WME Parameter Information Element */
#define DOT11_WME_PARAM_ELE_ID          (221)
#define DOT11_WME_PARAM_ELE_LEN         (24)
typedef struct 
{
    dot11_eleHdr_t      hdr;
    uint8_t               OUI[3];
    uint8_t               OUIType;
    uint8_t               OUISubType;
    uint8_t               version;
    uint8_t               ACInfoField;
    uint8_t               reserved;
    dot11_ACParameters_t   WME_ACParameteres;
}  dot11_WME_PARAM_t;


/* 802.11n HT Information Element */
#define DOT11_HT_CAPABILITIES_ELE_LEN    (26)
#define DOT11_HT_INFORMATION_ELE_LEN     (22)

#define DOT11_HT_CAPABILITIES_MCS_RATE_OFFSET   (3)
#define DOT11_HT_INFORMATION_MCS_RATE_OFFSET    (6)

// HT capabilities bit masks
#define HT_CAP_AMPDU_SPACING_BITMASK            (BIT_2 | BIT_3 |BIT_4)
#define HT_CAP_AMPDU_MAX_SIZE_BITMASK           (BIT_0 | BIT_1 )
#define HT_CAP_AMPDU_PARAMETERS_FIELD_OFFSET    (2)           /* Offset of ampdu params' field in HT info element     */
#define HT_CAP_AMPDU_SPACING_OFFSET             (2)           /* Offset of ampdu spacing param in ampdu params' field */

/* 802.11ax HE Information Elements */
#define DOT11_HE_CAPABILITIES_ELE_MIN_LEN    (21)   //this len Excludes the Extension ID byte! elements only
#define DOT11_HE_CAPABILITIES_MIN_TOTAL_LEN  (22)   //Total len includes the Extension ID byte! will be the elemnt len field

#define DOT11_HE_OPERATION_ELE_MIN_LEN       (6)    //this len Excludes the Extension ID byte! elements only
#define DOT11_HE_OPERATION_MIN_TOTAL_LEN     (7)    //Total len includes the Extension ID byte! will be the elemnt len field

#define DOT11_HE_MU_EDCA_ELE_MIN_LEN         (13) //this len Excludes the Extension ID byte! elements only
#define DOT11_HE_MU_EDCA_MIN_TOTAL_LEN       (14) //Total len includes the Extension ID byte! will be the elemnt len field

#define DOT_11_WMM_LEN                       (24) // the length of the WMM IE

#define DOT11_MAX_RSNE_SIZE                  (257)
typedef struct __PACKED__
{
    dot11_eleHdr_t  eleHdr;
    uint8_t           htCapabilitiesIe[DOT11_HT_CAPABILITIES_ELE_LEN];   /* HT capabilities IE unparsed */
}  dot11HtCapabilitiesUnparse_t;

typedef struct
{
    dot11_eleHdr_t  eleHdr;
    uint8_t           htInformationIe[DOT11_HT_INFORMATION_ELE_LEN];     /* HT Information IE unparsed */
}  dot11HtInformationUnparse_t;

typedef union heMacCapabilities_s
{
    #define HE_MAC_CAP_LEN_IN_BYTES                                 6
    #define HE_MAC_CAP_BITS_MASK                                    0x0000FFFF

    struct __PACKED__
    {
        unsigned int          HTC_HE_Support                        : 1 ; // bits: [ 0:   0 ]
        unsigned int          twtRequesterSupport                   : 1 ; // bits: [ 1:   1 ]
        unsigned int          twtResponderSupport                   : 1 ; // bits: [ 2:   2 ]
        unsigned int          DynamicFragSupport                    : 2 ; // bits: [ 4:   3 ] *
        unsigned int          maxFragMsduAmsduExp                   : 3 ; // bits: [ 7:   5 ] *
        unsigned int          minFragSize                           : 2 ; // bits: [ 9:   8 ] *
        unsigned int          triggerFrameMACPaddingDuration        : 2 ; // bits: [ 11: 10 ]
        unsigned int          multiTIDAggregationRxSupport          : 3 ; // bits: [ 14: 12 ]
        unsigned int          heLinkAdaptationSupport               : 2 ; // bits: [ 16: 15 ]
        unsigned int          allAckSupport                         : 1 ; // bits: [ 17: 17 ] *
        unsigned int          trsSupport                            : 1 ; // bits: [ 18: 18 ]
        unsigned int          bsrSupport                            : 1 ; // bits: [ 19: 19 ] *
        unsigned int          broadcastTWTSupport                   : 1 ; // bits: [ 20: 20 ]
        unsigned int          bitmap32bitBASupport                  : 1 ; // bits: [ 21: 21 ] *
        unsigned int          muCascadingSupport                    : 1 ; // bits: [ 22: 22 ]
        unsigned int          ackEnabledAggregationSupport          : 1 ; // bits: [ 23: 23 ] *
        unsigned int          reserved                              : 1 ; // bits: [ 24: 24 ]
        unsigned int          omControlSupport                      : 1 ; // bits: [ 25: 25 ]
        unsigned int          ofdmaRASupport                        : 1 ; // bits: [ 26: 26 ] *
        unsigned int          maximumAMPDUlenExpExt                 : 2 ; // bits: [ 28: 27 ]
        unsigned int          amsduFragmentationSupport             : 1 ; // bits: [ 29: 29 ]
        unsigned int          flexibleTWTScheduleSupport            : 1 ; // bits: [ 30: 30 ] *
        unsigned int          rxControlFrametoMultiBSS              : 1 ; // bits: [ 31: 31 ]
        unsigned int          bsrpBqrpAmpduAggregation              : 1 ; // bits: [ 32: 32 ]
        unsigned int          qtpSupport                            : 1 ; // bits: [ 33: 33 ] *
        unsigned int          bqrSupport                            : 1 ; // bits: [ 34: 34 ]
        unsigned int          srpResponder                          : 1 ; // bits: [ 35: 35 ]
        unsigned int          ndpFeedbackReportSupport              : 1 ; // bits: [ 36: 36 ]
        unsigned int          opsSupport                            : 1 ; // bits: [ 37: 37 ]
        unsigned int          amsduInAckEnabledAmpduSupport         : 1 ; // bits: [ 38: 38 ]
        unsigned int          multiTidAggregationTxSupport          : 3 ; // bits: [ 41: 39 ]
        unsigned int          heSubchannelSelectiveTransSupport     : 1 ; // bits: [ 42: 42 ]
        unsigned int          ul2x996ToneRUSupport                  : 1 ; // bits: [ 44: 43 ]
        unsigned int          omControlULMUDataDisableRXSupport     : 1 ; // bits: [ 44: 44 ]
        unsigned int          heDynamicSmPowerSave                  : 1 ; // bits: [ 45: 45 ]
        unsigned int          puncturedSoundingSupport              : 1 ; // bits: [ 46: 46 ]
        unsigned int          htAndVhtTriggerFrameRxSupport         : 1 ; // bits: [ 47: 47 ]
    };
    uint32_t   _w32[2];
} heMacCapabilities_t;


typedef union heOperationParameters_s
{
    #define HE_OPERATION_FIELD_BYTES                               3

    struct __PACKED__
    {
        unsigned int          defaultPeDuration                  : 3  ; // bits: [ 2:   0 ]
        unsigned int          twtRequired                        : 1  ; // bits: [ 3:   3 ]
        unsigned int          txopDurRtsThresh                   : 10 ; // bits: [ 13:  4 ]
        unsigned int          vhtOperInfoPresent                 : 1  ; // bits: [ 14: 14 ]
        unsigned int          coHostedBSS                        : 1  ; // bits: [ 15: 15 ]
        unsigned int          erSUDisable                        : 1  ; // bits: [ 16: 16 ]
        unsigned int          gHz6OperInfoPresent                : 1  ; // bits: [ 17: 17 ]
        unsigned int          Reserved                           : 6  ; // bits: [ 23: 18 ]

    };
    uint8_t _byte[3];
}heOperationParameters_t;

typedef union bssColorInformation_s
{
    #define HE_OPERATION_BSS_OFSET                               3

    struct __PACKED__
    {
        unsigned int          bssColor                  : 6 ; // bits: [ 5:   0 ]
        unsigned int          partialBssColor           : 1 ; // bits: [ 6:   6 ]
        unsigned int          bssColorDisabled          : 1 ; // bits: [ 7:   7 ]
    };
    uint8_t _byte;
} bssColorInformation_t;


typedef union heMuEdcaAcParams_s
{
    #define HE_MU_EDCA_FIELD_BYTES                         3
    #define HE_MU_EDCA_AC_OFFSET                           1
    struct __PACKED__
    {
        unsigned int          aifsn                  : 4 ; // bits: [ 3:   0 ]
        unsigned int          acm                    : 1 ; // bits: [ 4:   4 ]
        unsigned int          aci                    : 2 ; // bits: [ 6:   5 ]
        unsigned int          reserved               : 1 ; // bits: [ 7:   6 ]
        unsigned int          eCWmin                 : 4 ; // bits: [ 3:   0 ]
        unsigned int          eCWmax                 : 4 ; // bits: [ 7:   4 ]
        unsigned int          muEcaTimer             : 8 ; // bits: [ 7:   0 ]

    };
    uint8_t _byte[3];
} heMuEdcaAcParams_t;


/*
 * HE Capabilities element- An HE STA declares that it is an HE STA by transmitting the HE Capabilities element.
 * The HE Capabilities element contains a number of fields that are used to advertise the HE capabilities of an
 * HE STA.
 *
 *      ======================================================================================================
 *      | Element ID |  Length | Element ID | HE MAC       |   HE PHY       |   Supported    |   PPE         |
 *      |            |         | Extension  | Capabilities |   Capabilities |   HE-MCS And   |   Thresholds  |
 *      |            |         |            | Information  |   Information  |   NSS Set      |   (optional)  |
 *      =====================================================================================================
 *Octets:       1          1          1             6               11            4, 8 or 12       variable
 *
 */
typedef union hePhyCapabilities_s
{
    #define HE_PHY_CAP_LEN_IN_BYTES                                         11

    struct __PACKED__
    {
        unsigned int      reserved1                                         : 1 ; // bits: [  0: 0  ]
        unsigned int      channelWidthSet                                   : 7 ; // bits: [  7: 1  ]
        unsigned int      puncturedPreambleRx                               : 4 ; // bits: [ 11: 8  ]
        unsigned int      deviceClass                                       : 1 ; // bits: [ 12: 12 ]
        unsigned int      ldpcCodingInPayload                               : 1 ; // bits: [ 13: 13 ]
        unsigned int      heSuPPDUWith1xHeLTFand08usGI                      : 1 ; // bits: [ 14: 14 ]
        unsigned int      midambleTxRxMaxNSTS                               : 2 ; // bits: [ 16: 15 ]
        unsigned int      ndpWith4xHeLTFand32msGI                           : 1 ; // bits: [ 17: 17 ]
        unsigned int      stbcTxSmallerEqu80MHz                             : 1 ; // bits: [ 18: 18 ]
        unsigned int      stbcRxSmallerEqu80MHz                             : 1 ; // bits: [ 19: 19 ]
        unsigned int      dopplerTx                                         : 1 ; // bits: [ 20: 20 ]
        unsigned int      dopplerRx                                         : 1 ; // bits: [ 21: 21 ]
        unsigned int      fullBandwidthULmuMIMO                             : 1 ; // bits: [ 22: 22 ]
        unsigned int      partialBandwidthULmuMIMO                          : 1 ; // bits: [ 23: 23 ]
        unsigned int      dcmMaxConstellationTx                             : 2 ; // bits: [ 25: 24 ]
        unsigned int      dcmMaxNSStx                                       : 1 ; // bits: [ 26: 26 ]
        unsigned int      dcmMaxConstellationRx                             : 2 ; // bits: [ 28: 27 ]
        unsigned int      dcmMaxNSSrx                                       : 1 ; // bits: [ 29: 29 ]
        unsigned int      rxHEmuPPDUfromNonAPsta                            : 1 ; // bits: [ 30: 30 ]
        unsigned int      suBeamformer                                      : 1 ; // bits: [ 31: 31 ]
        unsigned int      suBeamformee                                      : 1 ; // bits: [ 32: 32 ]
        unsigned int      muBeamformer                                      : 1 ; // bits: [ 33: 33 ]
        unsigned int      beamformeeSTSsmallEqu80mHz                        : 3 ; // bits: [ 36: 34 ]
        unsigned int      beamformeeSTSbigger80mHz                          : 3 ; // bits: [ 39: 37 ]
        unsigned int      numberOfSoundingDimensionsSmallEqu80mHz           : 3 ; // bits: [ 42: 40 ]
        unsigned int      numberOfSoundingDimensionsBigger80mHz             : 3 ; // bits: [ 45: 43 ]
        unsigned int      ng16SUfeedback                                    : 1 ; // bits: [ 46: 46 ]
        unsigned int      ng16MUfeedback                                    : 1 ; // bits: [ 47: 47 ]
        unsigned int      codebookSize42SUfeedback                          : 1 ; // bits: [ 48: 48 ]
        unsigned int      codebookSize75mufeedback                          : 1 ; // bits: [ 49: 49 ]
        unsigned int      triggeredSUbeamformingfeedback                    : 1 ; // bits: [ 50: 50 ]
        unsigned int      triggeredMUbeamformingPartialBWfeedback           : 1 ; // bits: [ 51: 51 ]
        unsigned int      triggeredCQIFeedback                              : 1 ; // bits: [ 52: 52 ]
        unsigned int      partialBandwidthExtendedRange                     : 1 ; // bits: [ 53: 53 ]
        unsigned int      partialBandwidthDLmuMIMO                          : 1 ; // bits: [ 54: 54 ]
        unsigned int      ppeThresholdPresent                               : 1 ; // bits: [ 55: 55 ]
        unsigned int      srpBasedSRsupport                                 : 1 ; // bits: [ 56: 56 ]
        unsigned int      powerBoostFactorSupport                           : 1 ; // bits: [ 57: 57 ]
        unsigned int      heSUppduAndHEmuPPDUwith4xHEltfAnd08GI             : 1 ; // bits: [ 58: 58 ]
        unsigned int      maxNc                                             : 3 ; // bits: [ 61: 59 ]
        unsigned int      stbcTxBigger80MHz                                 : 1 ; // bits: [ 62: 62 ]
        unsigned int      stbcRxBigger80MHz                                 : 1 ; // bits: [ 63: 63 ]
        unsigned int      heERsuPPDUwith4xHEltfAnd08GI                      : 1 ; // bits: [ 64: 64 ]
        unsigned int      mHz20in40mHzHEppduIn24gHzBand                     : 1 ; // bits: [ 65: 65 ]
        unsigned int      mHz20in160or80plus80mHzHEppdu                     : 1 ; // bits: [ 66: 66 ]
        unsigned int      mHz80in160or80plus80mHzHEppdu                     : 1 ; // bits: [ 67: 67 ]
        unsigned int      heERsuPPDUwith1xHEltfAnd08GI                      : 1 ; // bits: [ 68: 68 ]
        unsigned int      midambleTxOrRx2xand1xHEltf                        : 1 ; // bits: [ 69: 69 ]
        unsigned int      dcmMaxBW                                          : 2 ; // bits: [ 71: 70 ]
        unsigned int      longerThan16heSIGbOFDMsymbolsSupport              : 1 ; // bits: [ 72: 72 ]
        unsigned int      nonTriggeredCQIfeedback                           : 1 ; // bits: [ 73: 73 ]
        unsigned int      tx1024QAM242toneRUsupport                         : 1 ; // bits: [ 74: 74 ]
        unsigned int      rx1024QAM242toneRUSupport                         : 1 ; // bits: [ 75: 75 ]
        unsigned int      rxFullBWsuUsingHEmuPPDUwithCompressedSIGB         : 1 ; // bits: [ 76: 76 ]
        unsigned int      rxFullBWsuUsingHEmuPPDUWithNonCompressedSIGB      : 1 ; // bits: [ 77: 77 ]
        unsigned int      nominalPacketPadding                              : 2 ; // bits: [ 79: 78 ]
        unsigned int      reserved2                                         : 8 ; // bits: [ 87: 80 ]
    };
    uint32_t   _w32[3];
} hePhyCapabilities_t;


typedef struct __PACKED__
{
    #define HE_MSC_CAP_LEN_IN_BYTES                                 4
    #define HE_MSC_CAP_MCS_0_TO_7                                   0xFFFC

    uint16_t  rxHeMcsMap80MHz;
    uint16_t  txHeMcsMap80MHz;
}heMcsCapabilities;




/* EHtCapabilitesFwBitMask mapping */

typedef enum
{
    HT_CAP_LDPC_CODING                         = BIT_0,
    HT_CAP_SUPP_CHANNEL_WIDTH_SET              = BIT_1,
    HT_CAP_SMPS_DYNAMIC                        = BIT_2 |BIT_3,
    HT_CAP_GREEN_FIELD                         = BIT_4,
    HT_CAP_SHORT_GI20MHZ                       = BIT_5,
    HT_CAP_SHORT_GI40MHZ                       = BIT_6,
    HT_CAP_TX_STBC                             = BIT_7,
    HT_CAP_RX_STBC                             = BIT_8 | BIT_9,
    HT_CAP_DELAYED_BA                          = BIT_10,
    HT_CAP_MAX_AMSDU_SIZE                      = BIT_11,
    HT_CAP_DSSS_CCK40MHZ                       = BIT_12,
    HT_CAP_PSMP_SUPP                           = BIT_13,
    HT_CAP_40MHZ_INTOLERANT                    = BIT_14,
    HT_CAP_LSIG_TXOP_PROTECT_SUPPORT           = BIT_15,
    HT_CAP_HT_OPERRATION                       = BIT_16
} EHtCapabilitesFwBitMask;


/* structs to parse dot11HeCapabilities and dot11HeOperation ,
 * This used only in the scan phase, were we copy only minimum len for each element */
typedef struct __PACKED__
{
    dot11_eleHdr_t  eleHdr;
    uint8_t           eleIdExt;
    uint8_t           heCapabilitiesIe[DOT11_HE_CAPABILITIES_ELE_MIN_LEN];   /* HE capabilities IE unparsed */
}  dot11HeCapabilitiesUnparse_t;

typedef struct __PACKED__
{
    dot11_eleHdr_t  eleHdr;
    uint8_t           eleIdExt;
    uint8_t           heOperationIe[DOT11_HE_OPERATION_ELE_MIN_LEN];     /* HE Operation IE unparsed */
}  dot11HeOperationUnparse_t;


typedef struct __PACKED__
{
    dot11_eleHdr_t               eleHdr;
    uint8_t                      eleIdExt;
    uint8_t                      qos_information;
    heMuEdcaAcParams_t           heMuEdcaAcParamsIe[NUM_ACCESS_CATEGORIES];     /* HE Operation IE unparsed */
}  dot11HeMuEdcaAcParams_t;

/* macros to parse dot11HtInformationUnparse.htInformationIe */
//BYTE #1
#define HT_INF_RIFS_MOD_BITMASK                 (0x08)

//BYTE #2
#define HT_INF_PROTECTION_MOD_BITMASK            (0x03)
#define HT_INF_NON_GF_PRES_BITMASK              (0x04)
#define HT_INF_OBSS_NON_HT_STA_PRESENT_BITMASK  (0x10)
#define HT_INF_TX_BURST_LIMIT_BITMASK           (0x08)

//BYTE #4
#define HT_INF_DUAL_CTS_PROTECTION_BITMASK      (0x80)

#define HT_RIFS_MODE(htinfo)        (((htinfo)->htInformationIe[1] & HT_INF_RIFS_MOD_BITMASK) >> 3)
#define HT_PROT(htinfo)              ((htinfo)->htInformationIe[2] & HT_INF_PROTECTION_MOD_BITMASK)
#define HT_GF_PROT(htinfo)          (((htinfo)->htInformationIe[2] & HT_INF_NON_GF_PRES_BITMASK) >> 2)
#define HT_OBSS_NON_HT_PROT(htinfo) (((htinfo)->htInformationIe[2] & HT_INF_OBSS_NON_HT_STA_PRESENT_BITMASK) >> 4)
//#define HT_TX_BURST_LIMIT(htinfo)   (((htinfo)->htInformationIe[2] & HT_INF_TX_BURST_LIMIT_BITMASK) >> 3) //not found in 2016 spec
#define HT_DUAL_CTS_PROT(htinfo)    (((htinfo)->htInformationIe[4] & HT_INF_DUAL_CTS_PROTECTION_BITMASK) >> 7)

//HT_INF_PROTECTION_MOD_BITMASK - BYTE 2
#define HT_PROTECTION_NO_PROTECTION_MODE            0
#define HT_PROTECTION_NON_MEMBER_PROTECTION_MODE    1
#define HT_PROTECTION_20_MHZ_PROTECTION_MODE        2
#define HT_PROTECTION_NON_HT_MIXED_MODE             3

//HT_INF_OBSS_NON_HT_STA_PRESENT - BYTE 2
#define HT_PROTECTION_OBSS_PROTECTION               BIT_4

//GREENFIELD - BYTE 2
#define HT_GREENFIELD_ALL_STA_CAPABLE               0
#define HT_NON_GREENFIELD_STA_PRESENTED             1

//HT_OBSS_NON_HT_PROT - BYTE 2
#define HT_OBSS_ALL_STA_CAPABLE                     0
#define HT_OBSS_NON_HT_STA_PRESENTED                1


/* ------------ BA definitions -------------------- */

#define HT_BA_POLICY_INITIATOR_BIT                  BIT_0
#define HT_BA_POLICY_RX_BIT                         BIT_1

/* BA session bits mask */
#define DOT11_BAR_CONTROL_FIELD_TID_BITS            0xf000
#define DOT11_BA_PARAMETER_SET_FIELD_TID_BITS       0x003C
#define DOT11_BA_PARAMETER_SET_FIELD_WINSIZE_BITS   0xffC0


/* DELBA */
#define SET_TID_IN_DELBA_PARAMETER_SET(delba, tid)                      (delba = (delba & 0xFFF)  | (tid << 12))
#define SET_INITIATOR_ROLE_IN_DELBA_PARAMETER_SET(delba, initiator)     (delba = (delba & 0xF7FF) | (initiator << 11))

#define DOT11_DELBA_PARAMETER_FIELD_TID_BITS            0xf000
#define DOT11_DELBA_PARAMETER_FIELD_INITIATOR_BIT       0x800

#define DOT11_DELBA_PARAMETER_INITIATOR                 1
#define DOT11_DELBA_PARAMETER_RECIPIENT                 0

/* ADDBA response */
#define SET_WIN_SIZE_IN_ADDBA_PARAMETER_SET(ba, winSize)                (ba = (ba  | (winSize << 6)))
#define SET_TID_IN_ADDBA_PARAMETER_SET(ba, tid)                         (ba = (ba  | (tid << 2)))
#define SET_BA_POLICY_IN_ADDBA_PARAMETER_SET(ba, policy)                (ba = (ba  | (policy << 1)))
#define SET_AMSDU_IN_AMPDU_PARAMETER_SET(ba, amsdu_support)             (ba = (ba  |  (amsdu_support)))


#define DOT11_ADDBA_ACK_POLICY_ACK          1
#define DOT11_ADDBA_ACK_POLICY_NACK         0

#define DOT11_CATEGORY_BLOCK_ACK            3
#define DOT11_ACTION_ADDBA_RESPONSE         1
#define DOT11_ACTION_DELBA                  2

#define DOT11_FRAME_BODY_LENGTH_ADDBA_RESPONSE      9
#define DOT11_FRAME_BODY_LENGTH_DELBA               6

#define RSN_SEC_LEN 8


typedef enum
{
    DOT11_BA_ACTION_ADDBA           = 0,
    DOT11_BA_ACTION_DELBA           = 2
} Edot11BaAction;

typedef enum
{
    DOT11_DELBA_REASON_CODE_UNSPECIFIED         = 1,
    DOT11_DELBA_REASON_CODE_INACTIVITY          = 4,
    DOT11_DELBA_REASON_CODE_END_BA_REASON       = 37
} Edot11DelbaReasonCode;

typedef enum
{
    DOT11_ADDBA_RESPONSE_STATUS_CODE_SUCCESSFUL     = 0,
    DOT11_ADDBA_RESPONSE_STATUS_CODE_DECLINE        = 37
} Edot11AddbaStatusCode;

typedef struct __PACKED__
{
    uint8_t   uCategory;
    uint8_t   uAction;
    uint16_t  DELBAParameterSet;
    uint16_t  reasonCode;

} TDelbaFrame;

typedef struct __PACKED__
{
    uint8_t   uCategory;
    uint8_t   uAction;
    uint8_t   dialogToken;
    uint16_t  status;
    uint16_t  BlockAckParameterSet;
    uint16_t  BlockAckTimeoutValue;

} TAddbaResFrame;

typedef struct __PACKED__
{
    uint8_t   uCategory;
    uint8_t   uAction;
    uint8_t   dialogToken;
    uint16_t  BlockAckParameterSet;
    uint16_t  BlockAckTimeoutValue;
    uint16_t  BlockAckStartingSequenceControl;
} TAddbaReqFrame;

typedef struct
{
    unsigned    ackPolicy   : 1;
    unsigned    multiTid    : 1;
    unsigned    compressed  : 1;
    unsigned    reserved    : 9;
    unsigned    tid         : 4;
}BarCtl_t;

typedef struct __PACKED__
{
    BarCtl_t     barCtl;
    uint16_t      ssn;
} TBarFrame;

/* --------------FILS discovery defenitions-------------------- */

//FILS Discovery frame details,defines and structs
#define FILS_DISCOVERY_PUBLIC_ACTION_ID     34

typedef struct
{
    unsigned int      ssidLen       : 5;
    unsigned int      capability    : 1;
    unsigned int      shortSsid     : 1;
    unsigned int      apCsn         : 1;
    unsigned int      ano           : 1;
    unsigned int      channelCenter : 1;
    unsigned int      primaryChannel: 1;
    unsigned int      rsnInfo       : 1;
    unsigned int      length        : 1;
    unsigned int      md            : 1;
    unsigned int      reserved      : 2;
} FilsDiscCtrllField_t;

/* WiFi Simple Config Information Element */
#define DOT11_WSC_PARAM_ELE_ID          (221)

/* WPS Information Element */
/* WPS == WSC */
#define DOT11_WPS_ELE_ID                (221)
#define DOT11_WPS_OUI                   {0x00, 0x50, 0xF2, 0x04}
#define DOT11_WPS_OUI_LEN               4

#define DOT11_WSC_SELECTED_REGISTRAR_CONFIG_METHODS      0x1053
#define DOT11_WSC_SELECTED_REGISTRAR_CONFIG_METHODS_PIN  0xC
#define DOT11_WSC_SELECTED_REGISTRAR_CONFIG_METHODS_PBC  0x80

#define DOT11_WSC_DEVICE_PASSWORD_ID      0x1012
#define DOT11_WSC_DEVICE_PASSWORD_ID_PIN  0x0000
#define DOT11_WSC_DEVICE_PASSWORD_ID_PBC  0x0004

/* WiFi Simple Config Parameter Information Element */
#define DOT11_WSC_PROBE_REQ_PARAM_ELE_LEN           (22)
#define DOT11_WSC_BEACON_MAX_LENGTH 251




typedef struct
{
    dot11_eleHdr_t              hdr;
    uint8_t                        OUI[3];
    uint8_t                        OUIType;
    uint8_t WSCBeaconOrProbIE[DOT11_WSC_BEACON_MAX_LENGTH];
}  dot11_WSC_t;

#define dot11_WPA_OUI_TYPE                  (1)
#define dot11_WME_OUI_TYPE                  (2)
#define dot11_WSC_OUI_TYPE                  (4)
#define dot11_WME_OUI_SUB_TYPE_IE           (0)
#define dot11_WME_OUI_SUB_TYPE_PARAMS_IE    (1)
#define dot11_WME_VERSION                   (1)
#define dot11_WME_ACINFO_MASK               0x0f

/* -------------------- TSPEC ----------------- */

typedef struct
{
    uint8_t   tsInfoArr[3];

}  tsInfo_t;



/* This structure is part of the TSPEC structure. It was seperated since there are some cases (such as DEL_TS), which we dont need
to send ALL the TSPEC structure, but only as far as TsInfo. The TSPEC structure contains this smaller structure */
typedef struct 
{
    dot11_eleHdr_t      hdr;

    uint8_t   OUI[3];
    uint8_t   oui_type;
    uint8_t   oui_subtype;
    uint8_t   version;

    tsInfo_t tsInfoField;
}  dot11_WME_TSPEC_IE_hdr_t;

typedef struct
{

    dot11_WME_TSPEC_IE_hdr_t eleHdr;

    uint16_t  nominalMSDUSize;
    uint16_t  maximumMSDUSize;
    uint32_t  minimumServiceInterval;
    uint32_t  maximumServiceInterval;
    uint32_t  inactivityInterval;
    uint32_t  suspensionInterval;
    uint32_t  serviceStartTime;
    uint32_t  minimumDataRate;
    uint32_t  meanDataRate;
    uint32_t  peakDataRate;
    uint32_t  maximumBurstSize;
    uint32_t  delayBound;
    uint32_t  minimumPHYRate;
    uint16_t  surplusBandwidthAllowance;
    uint16_t  mediumTime;

} dot11_WME_TSPEC_IE_t;


#define WME_TSPEC_IE_ID                         221
#define WME_TSPEC_IE_LEN                        61
#define WME_TSPEC_IE_TSINFO_LEN                 9
#define WME_TSPEC_IE_OUI_TYPE                   0x02
#define WME_TSPEC_IE_OUI_SUB_TYPE               0x02
#define WME_TSPEC_IE_VERSION                    0x01

/* OUI TYPE values that can be present in management packets inside Cisco vendor specific IE */
typedef enum
{
    TS_METRIX_OUI_TYPE = 0x07,
    TS_RATE_SET_OUI_TYPE = 0x08,
    EDCA_LIFETIME_OUI_TYPE = 0x09
} CCX_IE_OUI_TYPE_t;

#define ADDTS_REQUEST_ACTION                    0x00
#define ADDTS_RESPONSE_ACTION                   0x01
#define DELTS_ACTION                            0x02

#define ADDTS_STATUS_CODE_SUCCESS               0x00
#define ADDTS_STATUS_CODE_INVALID_PARAMS        0x01
#define ADDTS_STATUS_CODE_REFUSED               0x03

#define DELTS_CODE_SUCCESS                      0x00


#define TS_INFO_0_TRAFFIC_TYPE_MASK             0x01
#define TS_INFO_0_TSID_MASK                     0x1E
#define TS_INFO_0_DIRECTION_MASK                0x60
#define TS_INFO_0_ACCESS_POLICY_MASK            0x80

#define TS_INFO_1_ACCESS_POLICY_MASK            0x01
#define TS_INFO_1_AGGREGATION_MASK              0x02
#define TS_INFO_1_APSD_MASK                     0x04
#define TS_INFO_1_USER_PRIORITY_MASK            0x38
#define TS_INFO_1_TSINFO_ACK_POLICY_MASK        0xC0

#define TS_INFO_2_SCHEDULE_MASK                 0x01
#define TS_INFO_2_RESERVED_MASK                 0xF7

#define TRAFFIC_TYPE_SHIFT                      0
#define TSID_SHIFT                              1
#define DIRECTION_SHIFT                         5
#define ACCESS_POLICY_SHIFT                     7
#define AGGREGATION_SHIFT                       1
#define APSD_SHIFT                              2
#define USER_PRIORITY_SHIFT                     3
#define TSINFO_ACK_POLICY_SHIFT                 6
#define SCHEDULE_SHIFT                          0
#define RESERVED_SHIFT                          1
#define SURPLUS_BANDWIDTH_ALLOW                 13

#define TS_INFO_0_ACCESS_POLICY_EDCA            0x1
#define NORMAL_ACKNOWLEDGEMENT                  0x00
#define NO_SCHEDULE                             0x00
#define PS_UPSD                                 0x01
#define EDCA_MODE                               0x08
#define FIX_MSDU_SIZE                           0x8000

#define WPA_IE_OUI                              {0x00, 0x50, 0xf2}
#define CCX_OUI                                 {0x00, 0x40, 0x96}

#define SUPPORTED_RATES_MAX_IE_LEN              8

/* Action field structure
    used for extended management action such as spectrum management */
typedef uint8_t dot11_ACTION_FIELD_t[2];


/* Management frames sub types */
typedef enum
{
    ASSOC_REQUEST       = 0,
    ASSOC_RESPONSE      = 1,
    RE_ASSOC_REQUEST    = 2,
    RE_ASSOC_RESPONSE   = 3,
    PROBE_REQUEST       = 4,
    PROBE_RESPONSE      = 5,
    BEACON              = 8,
    ATIM                = 9,
    DIS_ASSOC           = 10,
    AUTH                = 11,
    DE_AUTH             = 12,
    ACTION              = 13
} dot11MgmtSubType_e;

/* Management frames element IDs */
typedef enum
{
    SSID_IE_ID                          = 0,
    SUPPORTED_RATES_IE_ID               = 1,
    FH_PARAMETER_SET_IE_ID              = 2,
    DS_PARAMETER_SET_IE_ID              = 3,
    CF_PARAMETER_SET_IE_ID              = 4,
    TIM_IE_ID                           = 5,
    IBSS_PARAMETER_SET_IE_ID            = 6,
    COUNTRY_IE_ID                       = 7,
    CHALLANGE_TEXT_IE_ID                = 16,
    POWER_CONSTRAINT_IE_ID              = 32,
    TPC_REPORT_IE_ID                    = 35,
    CHANNEL_SWITCH_ANNOUNCEMENT_IE_ID   = 37,
    QUIET_IE_ID                         = 40,
    ERP_IE_ID                           = 42,
    HT_CAPABILITIES_IE_ID               = 45,
    QOS_CAPABILITY_IE_ID                = 46,
    RSN_IE_ID                           = 48,
    EXT_SUPPORTED_RATES_IE_ID           = 50,
    MOBILITY_DOMAIN_IE_ID               = 54,
    FAST_TRANSITION_IE_ID               = 55,
    HT_INFORMATION_IE_ID                = 61,
    RRM_ENABLED_CAPABILITIES_IE_ID      = 70,
    MULTIPLE_BSSID                      = 71,   
    MULTIPLE_BSSID_INDEX                = 85,   
    CCX_EXT_1_IE_ID                     = 133,
    CCX_EXT_2_IE_ID                     = 149,
    CELL_POWER_IE                       = 150, /*CCX*/
    ADDBA_EXTENSION                     = 159,
    VHT_CAPABILITY_IE_ID                = 191,
    OPMODE_NOTIF_IE_ID                  = 199,
    VENDOR_SPECIFIC_IE_ID               = 221,
    EID_EXTENSION                       = 255

} dot11MgmtIeId_e;

/* element IDs using the Element ID Extension field */
typedef enum
{
    HE_CAPABILITIES_IE_ID             = 35,
    HE_OPERATION_IE_ID                = 36,
    MU_EDCA_PARAMETER_SET_IE_ID       = 38
} dot11ExtendedIeId_e;

/* Spectrum Management Action fields */
typedef enum
{
    MEASUREMENT_REQUEST             = 0,
    MEASUREMENT_REPORT              = 1,
    TPC_REQUEST                     = 2,
    TPC_REPORT                      = 3,
    CHANNEL_SWITCH_ANNOUNCEMENT     = 4
} dot11ActionFrameTypes_e;


typedef enum
{
    RRM_MEASUREMENT_REQUEST = 0,
    RRM_MEASUREMENT_REPORT,
    LINK_MEASUREMENT_REQUEST,
    LINK_MEASUREMENT_REPORT,
    NEIGHBOR_MEASUREMENT_REQUEST,
    NEIGHBOR_MEASUREMENT_REPORT
} rrmActionFrameTypes_e;




typedef struct
{
    dot11_eleHdr_t  hdr;
    uint8_t        OUI[3];
    uint8_t        OUIType;
    uint8_t        OUISubType;
    uint8_t        transmitPower;
    uint8_t        linkMargin;
}  dot11_TPC_REPORT_VS_IE_t;


/*
 * Management templates to set to the HAL:
 */

#ifdef CCX_MODULE_INCLUDED

typedef struct
{
        dot11_mgmtHeader_t  hdr;
        char                infoElements[sizeof( dot11_SSID_t ) +
                                         sizeof( dot11_RATES_t ) +
                                         sizeof( dot11_RATES_t ) +
                                         sizeof( dot11HtCapabilitiesUnparse_t ) +
                                         DOT11_MAX_VARIABLE_IES_LEN +
                                         sizeof( ccx_radioManagmentCapability_IE_t )
                                        ];
    } probeReqTemplate_t;

#else /* CCX_MODULE_INCLUDED */

typedef struct
{
    char                        timestamp[TIME_STAMP_LEN];
    uint16_t                      beaconInerval;
    uint16_t                      capabilities;
} BeaconProbeRsp_hdr_t;

typedef struct  
{
    dot11_mgmtHeader_t  hdr;
    char                infoElements[sizeof( dot11_SSID_t ) +

                                     sizeof( dot11_RATES_t ) +
                                         sizeof( dot11_RATES_t ) +
                                         sizeof( dot11HtCapabilitiesUnparse_t ) +
                                         DOT11_MAX_VARIABLE_IES_LEN +
                                         sizeof( dot11_DS_PARAMS_t) +
                                         sizeof( dot11_TPC_REPORT_VS_IE_t)
                                        ];
}  probeReqTemplate_t;

#endif /* CCX_MODULE_INCLUDED */


typedef struct 
{
    dot11_mgmtHeader_t  hdr;
    uint8_t               timeStamp[TIME_STAMP_LEN];
    uint16_t              beaconInterval;
    uint16_t              capabilities;
    char                infoElements[ sizeof( dot11_SSID_t ) +
                                      sizeof( dot11_RATES_t ) +
                                      sizeof( dot11_RATES_t ) +
                                      sizeof( dot11_DS_PARAMS_t ) +
                                      sizeof( dot11_COUNTRY_t)  +
                                      DOT11_MAX_VARIABLE_IES_LEN];
}  probeRspTemplate_t;

typedef struct
{
    dot11_mgmtHeader_t  hdr;
    uint8_t               timeStamp[TIME_STAMP_LEN];
    uint16_t              beaconInterval;
    uint16_t              capabilities;
    char                infoElements[ sizeof( dot11_SSID_t ) +
                                      sizeof( dot11_RATES_t ) +
                                      sizeof( dot11_RATES_t ) +
                                      sizeof( dot11_DS_PARAMS_t ) +
                                      sizeof( dot11_TIM_Short_t) +
                                      sizeof( dot11_COUNTRY_t)      ];
}  beaconTemplate_t;


typedef struct 
{
    dot11_mgmtHeader_t  hdr;
}  nullDataTemplate_t;

typedef struct
{
    dot11_mgmtHeader_t  hdr;
    uint16_t disconnReason;
} deauthTemplate_t;

//typedef struct
//{
//    dot11_header_t   hdr;
//    Wlan_LlcHeader_T LLC;
//    uint16_t     hardType;
//    uint16_t     protType;
//    uint8_t      hardSize;
//    uint8_t      protSize;
//    uint16_t     op;
//    macAddress_t  StaMac;
//    TIpAddr       StaIp;
//    macAddress_t  TargMac;
//    TIpAddr       TargIp;
//} ArpRspTemplate_t; /* for auto ArpRsp sending by FW */

typedef struct
{
   dot11_PsPollFrameHeader_t   hdr;
} psPollTemplate_t;

typedef struct
{
   dot11_header_t   hdr;
}  QosNullDataTemplate_t;

/* Traffic Stream Rate Set (TSRS) info-elements */
typedef struct
{
    dot11_eleHdr_t  hdr;
    uint8_t           OUI[3];
    uint8_t           oui_type;
    uint8_t           tsid;
    uint8_t           tsNominalRate;
} dot11_TSRS_STA_IE_t;

typedef struct
{
    dot11_eleHdr_t  hdr;
    uint8_t           OUI[3];
    uint8_t           oui_type;
    uint8_t           tsid;
    uint8_t           tsRates[8];
}  dot11_TSRS_IE_t;

/* MSDU lifetime info-element */
typedef struct
{
    dot11_eleHdr_t  hdr;
    uint8_t           OUI[3];
    uint8_t           oui_type;
    uint8_t           tsid;
    uint16_t          msduLifeTime;
}  dot11_MSDU_LIFE_TIME_IE_t;

typedef struct
{
    dot11_eleHdr_t  hdr;
    uint8_t           OUI[3];
    uint8_t           oui_type;
    uint8_t           tsid;
    uint8_t           state;
    uint16_t          measureInterval;
}  dot11_TS_METRICS_IE_t;

typedef struct
{
    dot11_TSRS_IE_t             *trafficStreamParameter;
    dot11_MSDU_LIFE_TIME_IE_t   *edcaLifetimeParameter;
    dot11_TS_METRICS_IE_t       *tsMetrixParameter;
} CCXv4IEs_t;


#define MAX_NEIGHBOR_REPORT_SUB_ELEMENTS (50)
#define NEIGHBOR_REPORT_ELE_ID           (52)
#define RRM_ENABLED_CAPABILITIES_ELE_ID  (70)
#define RRM_ENABLED_CAPABILITIES_ELE_LEN  5


typedef struct
{
    dot11_eleHdr_t  hdr;
    uint8_t        capabilities[5];
}  dot11_RM_ENABLED_CAPABILITIES_IE_t;

/* Mobility Domain Information Element (802.11r)*/
#define DOT11_MOBILITY_DOMAIN_ELE_ID    54
#define DOT11_MOBILITY_DOMAIN_ELE_LEN   3
typedef struct
{
    dot11_eleHdr_t     hdr;
    uint16_t          mdId;
    uint8_t           ftCapaAndPolicy;
} dot11_MOBILITY_DOMAIN_IE_t;

typedef struct
{
    dot11_eleHdr_t     hdr;
    uint8_t           body[256];
} dot11_FAST_TRANSITION_IE_t;

typedef struct
{
    dot11_eleHdr_t  hdr;
    macAddress_t    bssid;
    uint8_t        bssidInfo[4];
    uint8_t        regulatoryClass;
    uint8_t        channelNumber;
    uint8_t        phyType;
}  dot11_NEIGHBOR_REPORT_IE_t;



/* Wi-Fi TPC Report Element  Information Element */
#define DOT11_TPC_REPORT_VS_ELE_ID              (221)
#define DOT11_TPC_REPORT_VS_ELE_LEN             (7)
#define DOT11_TPC_REPORT_VS_ELE_OUI             {0x00, 0x50, 0xf2}
#define DOT11_TPC_REPORT_VS_ELE_OUI_TYPE        (0x08)
#define DOT11_TPC_REPORT_VS_ELE_OUI_SUB_TYPE    (0x00)

#define DOT11_OUI_TYPE_LEN                      (3)



typedef struct
{
    uint8_t        category;
    uint8_t        action;
    uint8_t        dialogToken;
}  RadioMeasurementHdr_t;


typedef struct
{
    RadioMeasurementHdr_t measHdr;
    dot11_SSID_t          ssid;
}  NeighborMeasurementRequest_t;


/* 802.11k action frame Link measurement report template  - FW shall respond
with this frame upon receiving link measu request */
typedef struct
{
    dot11_mgmtHeader_t    hdr;
    RadioMeasurementHdr_t hdrRRM;
    dot11_TPC_REPORT_t    TPCIE;
    uint8_t              recvAntennaID;
    uint8_t              transmitAntennaID;
    uint8_t              RCPI;
    uint8_t              RSNI;
} LinkMeasurementReportTemplate_t; /* for auto ArpRsp sending by FW */

/* Measurement Report message frame structure */
#define DOT11_MEASUREMENT_REPORT_ELE_ID     (39)
#define DOT11_MAX_MEASUREMENT_REPORT_LEN    (4)
#define DOT11_MIN_MEASUREMENT_REPORT_IE_LEN (3)
#define DOT11_MEASUREMENT_REPORT_ELE_IE_LEN (DOT11_MIN_MEASUREMENT_REPORT_IE_LEN + DOT11_MAX_MEASUREMENT_REPORT_LEN*MAX_NUM_REQ)

typedef struct
{
    dot11_ACTION_FIELD_t    actionField;
    uint8_t   dialogToken;

    dot11_eleHdr_t  hdr;
    uint8_t            measurementToken;
    uint8_t            measurementMode;
    uint8_t            measurementType;
    uint8_t            measurementReports[DOT11_MAX_MEASUREMENT_REPORT_LEN*MAX_NUM_REQ];
}  MeasurementReportFrame_t;



typedef enum 
{
    STATUS_SUCCESSFUL                                               =   0,
    STATUS_UNSPECIFIED,
    STATUS_AUTH_REJECT,
    STATUS_ASSOC_REJECT,
    STATUS_SECURITY_FAILURE,
    STATUS_AP_DEAUTHENTICATE,
    STATUS_AP_DISASSOCIATE,
    STATUS_ROAMING_TRIGGER,
    STATUS_DISCONNECT_DURING_CONNECT,
    STATUS_SG_RESELECT,
    STATUS_ROC_FAILURE,
    STATUS_FW_RESET,
    STATUS_MIC_FAILURE = 14,
    MGMT_STATUS_MAX_NUM = 15
} mgmtStatus_e;

/* Used as a status code in case of STATUS_AUTH_REJECT or STATUS_ASSOC_REJECT that was not received at all */
#define STATUS_PACKET_REJ_TIMEOUT   0xFFFF

/* As defined in 802.11 spec section 7.3.1 - status codes for deAuth packet */
#define STATUS_CODE_802_1X_AUTHENTICATION_FAILED 23

/* map field included in measurement report IE (only in basic report) */
typedef enum
{
  DOT11_BSS_ONLY                    = (0x01),
  DOT11_OFDM_ONLY                   = (0x02),
  DOT11_RADAR_AND_UNIDENTIFIED      = (0x0C)
} dot11_Map_Sub_Field_e;


typedef struct
{
   legacy_dot11_header_t dot11Header;
   Wlan_LlcHeader_T   snapHeader;
}  legacy_dot11_DataMsduHeader_t;


#define WLAN_HEADER_TYPE_CONCATENATION 0x01
#define WLAN_CONCAT_HEADER_LEN 2

// The below is used to configure device supported band and 802.11 mode.
// Before association starts, supported bands is limited to peer band.
// Advanced specs (11n, 11ax) can come ontop of DOT11_A_MODE, DOT11_G_MODE, DOT11_DUAL_MODE
typedef enum
{
    DOT11_B_MODE    = 1,    // Band is 2.4 GHz; Device supports only 11b
    DOT11_A_MODE    = 2,    // Band is 5GHz; Device supports oly 11g
    DOT11_G_MODE    = 3,    // Band is 2.4 GHz; Device supports also 11g (ontop ob 11b)
    DOT11_DUAL_MODE = 4,    // Device supports both bands; 2.4 or 5, supports both 11b 11g
    DOT11_MAX_MODE
} dot11Mode_e;

typedef enum n {
    DOT11_,
    DOT11_BAND_5GHZ,
    DOT11_BAND_60GHZ,
    DOT11_BAND_6GHZ,
    DOT11_BAND_S1GHZ,

    NUM_NL80211_BANDS,
}dot11_band;
#endif   /* _802_11_INFO_DEFS_H */

