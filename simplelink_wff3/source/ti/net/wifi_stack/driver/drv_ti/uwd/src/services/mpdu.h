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
#ifndef MPDU_H
#define MPDU_H


#include <public_types.h>
#include <802_11defs.h>


/*****************************************************************************
             MAC Header Prototypes
******************************************************************************/


/* frameType bits                   */
/* bits 0-1 = protocol version = 0  */
/* bits 2-3 = type of frame         */
/* bits 4-7 = subtype of frame      */

/* frameCtrl bits                   */
/* bit 0 = To DS                    */
/* bit 1 = From DS                  */
/* bit 2 = More Fragments           */
/* bit 3 = Retry                    */
/* bit 4 = Power Management         */
/* bit 5 = More Data                */
/* bit 6 = WEP                      */
/* bit 7 = Order                    */


typedef uint8_t  FrameType_t;
typedef uint8_t  FrameCtrl_t;
typedef uint16_t QosControl_t;


typedef struct
{
    FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t      AID;
    uint8_t       BSSID[6];
    uint8_t       TA[6];
} PsPollHeader_t;


#define DATA_BYTES_CTS_FRAME 10 // old definition used here instead of sizeof()
#define DATA_BYTES_NULL_DATA_FRAME 24
#define DATA_BYTES_QOS_NULL_DATA_FRAME 26
#define DATA_BYTES_DISCONNECT_FRAME 26
#define DATA_BYTES_DEAUTH_AP_FRAME 30
#define DATA_BYTES_ACK_FRAME 10 // old definition used here instead of sizeof()
#define DATA_BYTES_PS_POLL_FRAME  16// 07/01/2012 - bug fix changed size to 16 (+4 FCS) from 20.
#define DATA_BYTES_CF_END_FRAME 16 // old definition used here instead of sizeof()
#define DATA_BYTES_BLOCK_ACK_FRAME 28 // old definition used here instead of sizeof()
#define DATA_BYTES_RTS_FRAME 16 // old definition used here instead of sizeof()
#define DATA_BYTES_BAR_FRAME 20 
#define DATA_BYTES_ERROR_FRAME 26 
#define DATA_BYTES_ADDBA_REQ_FRAME 33//(24 + 9)
#define DATA_BYTES_ADDBA_RES_FRAME 33//(24 + 9)
#define DATA_BYTES_DELBA_FRAME     30//(24 + 6)
#define DATA_BYTES_IBSS_BEACON_FRAME_MAX_SIZE   252 // 25-10-2010 - michal - the same value used by driver
                                                    // 24-08-2011 - jigal  - R4 merge: Mblk size > 255, and therefore, cannot be put in uint8_t.
                                                    //                       252B for an IBSS beacon is presumably enough (right??).
#define DATA_BYTES_TX_SIMULATION_FRAME 1600
// #define DATA_BYTES_WRAPPER_CTS_FRAME 16
// #define DATA_BYTES_WRAPPER_ACK_FRAME 16
// #define DATA_BYTES_WRAPPER_BLOCK_ACK_FRAME  34


typedef struct __PACKED__
{
    FrameType_t frameType;  //fc
    FrameCtrl_t frameCtrl; //fc
    uint16_t      duration;
    uint8_t       MACAddress1[6];
    uint8_t       MACAddress2[6];
    uint8_t       MACAddress3[6];
    uint16_t      seqCtrl;
//    uint16_t      qosControl; qosControl only applied to data see QOS_AP_MPDUHeader_t or QOS_MPDUHeader_t
/*  TMacAddr    address4;*/
} MPDUHeader_t;

 
typedef struct 
{
    uint16_t		linkAdaptCtrl;
	unsigned	calPosition 	: 2;
	unsigned	calSequence 	: 2;
	unsigned	feedbackReq 	: 2;
	unsigned	csi_steering 	: 2;
	unsigned	zlf_announce 	: 1;
	unsigned	reserved 		: 5;
	unsigned	ac_constraint 	: 1;
	unsigned	RDG_morePPDU 	: 1;
} HT_Control_t;


typedef struct 
{
    FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t      duration;
    uint8_t       MACAddress1[6];
    uint8_t       MACAddress2[6];
    uint8_t       MACAddress3[6];
    uint16_t      seqNum;
    uint8_t       MACAddress4[6];
} AP_TO_AP_MPDUHeader_t;


typedef struct 
{
    FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t      duration;
    uint8_t       MACAddress1[6];
    uint8_t       MACAddress2[6];
    uint8_t       MACAddress3[6];
    uint16_t      seqNum;
    QosControl_t qosCtrl;
} QOS_MPDUHeader_t;

typedef struct 
{
    FrameType_t		frameType;
    FrameCtrl_t		frameCtrl;
    uint16_t			duration;
    uint8_t			MACAddress1[6];
    uint8_t			MACAddress2[6];
    uint8_t			MACAddress3[6];
    uint16_t			seqNum;
    QosControl_t	qosCtrl;
	HT_Control_t	htControl;
} QoSHTMPDUHeader_t;


typedef struct 
{
    FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t      duration;
    uint8_t       MACAddress1[6];
    uint8_t       MACAddress2[6];
    uint8_t       MACAddress3[6];
    uint16_t      seqNum;
    uint8_t       MACAddress4[6];
    QosControl_t qosCtrl;
} QOS_AP_MPDUHeader_t;


typedef struct
{
    FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t      duration;
    uint8_t       da[6];
    uint8_t       sa[6];
    uint8_t       bssid[6];
    uint16_t      seqNum;
} MGMT_Header_t;


typedef struct
{
    uint8_t   DSAP    ;   // 0xAA for SNAP header
    uint8_t   SSAP    ;   // 0xAA for SNAP header
    uint8_t   Control ;   // 0x03 For standard unnumbered information without poll (see 802.2 spec).
    uint8_t   OUI[3]  ;   // 00-00-00 for standard 802.11 payloads. Could be some vendor ID for specific packets.
    uint16_t  Type    ;   // Ethertype (0x0800 for IPv4, 0x0806 for ARP, 0x86DD for IPv6, 0x888E for EAPol, etc.)
} LLC_SNAP_Header_t ;

typedef struct
{
    QOS_MPDUHeader_t    mpdu_header ;
    LLC_SNAP_Header_t   llc_snap    ;
    uint8_t               payload[0]  ;   // 1st payload byte begins here.
}   QOS_MPDU_LLC_DataFrame_t ;



/*****************************************************************************
             Frame Prototypes
******************************************************************************/
typedef struct
{
    FrameType_t		frameType;
    FrameCtrl_t		frameCtrl;
    uint16_t     		duration;
    uint8_t       	ra[6];
} CommonFrame_t;

#if 0
typedef struct
{
    FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t      duration;
    uint8_t       ra[6];    
} CTSFrame_t;
#endif 
typedef CommonFrame_t CTSFrame_t;

typedef struct
{
	/*--- CommonFrame_t ---*/
    FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t      duration;
    uint8_t       ra[6];  
	/*----------------------*/  
	uint8_t       ta_bssid[6];    
} RTSFrame_t, CfEndFrame_t;

#if 0
typedef struct
{
    FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t      duration;
    uint8_t       ra[6];    
} ACKFrame_t;
#endif 
typedef CommonFrame_t ACKFrame_t;

#if 0
typedef struct
{
    FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t      duration;
    uint8_t       ra[6];    
    uint8_t       BSSID[6];
} CfEndFrame_t;
#endif


typedef struct
{
	unsigned	ackPolicy	: 1; // 0
	unsigned	BaType   	: 4; // 1-4
    unsigned	reserved	: 7; // 5-11
	unsigned	tid			: 4; // 12-15
}BaCtl_t;

// BaTypeValues
typedef enum
{
    BASIC = 0,
    EXTENDED = 1,
    COMPRESSED = 2,  // supported
    MULTI_TID = 3,   // supported
    GCR = 6,
    GLK_GCR = 10
} BaType_e;


typedef struct
{
	/*-- RTSFrame_t -------*/
	/*--- CommonFrame_t ---*/
    FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t    duration;
    uint8_t     ra[6];    
	/*----------------------*/  
    uint8_t     ta_bssid[6];
	/*----------------------*/
    BaCtl_t 	baCtl;       
	uint16_t    ssn;
    uint64_t    bitmap;
} BaCompressedFrame_t;


typedef struct
{
 	/*--- CommonFrame_t ---*/
   FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t      duration;
    uint8_t       ra[6];    
	/*----------------------*/  
    uint8_t       ta[6];    
    BaCtl_t	    baCtl;
	uint16_t		tid1;
	uint16_t		ssn1;
    uint32_t		bitmap1[2];
	uint16_t		tid2;
	uint16_t		ssn2;
    uint32_t		bitmap2[2];
} BaMtidFrame_t;


typedef struct
{
	/*--- CommonFrame_t ---*/
    FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t      duration;
    uint8_t       ra[6];    
	/*--------------------*/
    uint8_t       ta[6];    
    BaCtl_t 	barCtl;
	uint16_t		ssn;
} BarCompressedFrame_t;

typedef struct
{
	/*--- CommonFrame_t ---*/
    FrameType_t frameType;
    FrameCtrl_t frameCtrl;
    uint16_t      duration;
    uint8_t       ra[6];    
	/*--------------------*/
    uint8_t       ta[6];    
    BaCtl_t	    barCtl;
	uint16_t		tid1;
	uint16_t		ssn1;
	uint16_t		tid2;
	uint16_t		ssn2;
} BarMtidFrame_t;


typedef struct
{
	/*--- CommonFrame_t ---*/
    FrameType_t     frameType;
    FrameCtrl_t     frameCtrl;
    uint16_t          duration;
    uint8_t           ra[6];    
	/*---------------------*/
    FrameType_t     realFrameType;
    FrameCtrl_t     realFrameCtrl;
    HT_Control_t    htControl;
} WrapperCTSFrame_t, WrapperACKFrame_t;

#if 0
typedef struct
{
    FrameType_t     frameType;
    FrameCtrl_t     frameCtrl;
    uint16_t          duration;
    uint8_t           ra[6];    
    
    FrameType_t     ackFrameType;
    FrameCtrl_t     ackFrameCtrl;
    HT_Control_t    htControl;
} WrapperACKFrame_t;
#endif

typedef struct
{
	/*-WrapperCTSFrame_t---*/
	/*--- CommonFrame_t ---*/
    FrameType_t     frameType;
    FrameCtrl_t     frameCtrl;
    uint16_t        duration;
    uint8_t         ra[6];    
	/*---------------------*/
    FrameType_t     realFrameType;
    FrameCtrl_t     realFrameCtrl;
    HT_Control_t    htControl;
	/*---------------------*/
    uint8_t         ta[6];    
    BaCtl_t 	    baCtl;       
	uint16_t	    ssn;
    uint64_t        bitmap;
} WrapperBaCompressedFrame_t;


typedef struct
{
    MGMT_Header_t   h                   ;   // Management MPDU header (no QoS nor HT control fields).
    uint32_t          tsf[2]              ;   // Payload begins with 64 bit TSF.
    uint16_t          beaconInterval      ;   // Beacon interval between successive beacons, in TU's (1TU = 1024usec).
    uint16_t          capabilityInfo      ;   // Various capabilities supported by the BSS/IBSS.
    uint8_t           infoElementStart[1] ;   // Start of dynamic section, with information elements (type/length/value).
}   BeaconFrame_t ;

typedef struct
{
    MGMT_Header_t   h                   ;   // Management MPDU header (no QoS nor HT control fields).
    uint8_t           infoElementStart[1] ;   // Start of dynamic section, with information elements (type/length/value).
}   ProbeRequest_t ;



// Trigger frame parsing

// For any trigger frame there are 8 bytes of common info.
// for MU GCR trigger type there are extra 4 bytes.
typedef union
{
    struct
    {
        unsigned int     trigger_type       : 4;    // 0-3
        unsigned int     UL_length          : 12;   // 4-15
        unsigned int     more_TF            : 1;    // 16
        unsigned int     CS_required        : 1;    // 17
        unsigned int     UL_BW              : 2;    // 18-19
        unsigned int     GI_LTF_type        : 2;    // 20-21
        unsigned int     MU_mimo_LTF        : 1;    // 22
        unsigned int     num_HE_LTF         : 3;    // 23-25
        unsigned int     UL_lpdc            : 1;    // 26
        unsigned int     LDPC_extra_symbol  : 1;    // 27
        unsigned int     AP_TX_power        : 6;    // 28-33
        unsigned int     PRE_FEC_pad_factor : 2;    // 34-35
        unsigned int     PE_disambiguity    : 1;    // 36
        unsigned int     sptial_reuse       :16;    // 37- 52
        unsigned int     doppler            : 1;    // 53
        unsigned int     HE_SIG_A2_reserve  : 9;    //54-62
        unsigned int     reserved           : 1;    // 63
    };
    uint32_t _w32[2];
} TriggerCommonInfo_t;

typedef union
{
    struct
    {
        unsigned int    aid12               :12; // 0-11
        unsigned int    RU_allocation       : 8; // 12-19
        unsigned int    UL_FEC_coding_type  : 1; // 20
        unsigned int    UL_MCS              : 4; // 21-24
        unsigned int    UL_DCM              : 1; // 25
        unsigned int    SS_aloc_RA_RU_info  : 6; // 26-31
        unsigned int    UL_target_RSSI      : 7; // 32-38
        unsigned int    reserved            : 1; // 39
    };
    uint8_t _w8[5];
} TriggerUserInfo_t;

typedef enum
{
    TRIG_BASIC    = 0,
    TRIG_BFRP,          // 1 - beam forming report
    TRIG_MU_BAR,        // 2
    TRIG_MU_RTS,        // 3
    TRIG_BSRP,          // 4 buffer status report
    TRIG_GCR_BAR,       // 5
    TRIG_BQRP,          // 6 bandwidth query report
    TRIG_NFRP           // 7 NDP feedback report poll
} trigType_e;


#define RANDOM_ACC_UN_ASSOC 2045
#define RANDOM_ACC_AID      0

typedef struct
{
    /*--- CommonFrame_t ---*/
    FrameType_t         frameType;
    FrameCtrl_t         frameCtrl;
    uint16_t              duration;
    uint8_t               ra[6];
    /*--------------------*/
    uint8_t               ta[6];
    TriggerCommonInfo_t commonInfo;
    TriggerUserInfo_t   userInfo; // for GCR trigger type there are additional bytes between the common info and user info
} TriggerFrame_t;



// MPDUHeader_t.frameType bit fields
#define FRAME_TYPE_MASK                     (0x000C)
#define FRAME_SUBTYPE_MASK                  (0x00F0)
#define FRAME_TYPE_SUBTYPE_MASK             (0x00FC)

// Management frames
#define FRAME_TYPE_ASSOCIATION_REQ          0x00
#define FRAME_TYPE_ASSOCIATION_RESPONSE     0x10
#define FRAME_TYPE_REASSOCIATION_REQ        0x20
#define FRAME_TYPE_REASSOCIATION_RESPONSE   0x30
#define FRAME_TYPE_PROBE_REQ                0x40
#define FRAME_TYPE_PROBE_RESPONSE           0x50
#define FRAME_TYPE_BEACON                   0x80
#define FRAME_TYPE_ATIM                     0x90
#define FRAME_TYPE_DISASSOCIATION           0xA0
#define FRAME_TYPE_AUTHENTICATION           0xB0
#define FRAME_TYPE_DEAUTHENTICATION         0xC0
#define FRAME_TYPE_ACTION                   0xD0

// Control frames
#define FRAME_TYPE_TRIGGER                  0x24
#define FRAME_TYPE_CONTROL_WRAPPER          0x74
#define FRAME_TYPE_BLOCK_ACK_REQ            0x84
#define FRAME_TYPE_BLOCK_ACK                0x94
#define FRAME_TYPE_PS_POLL                  0xA4
#define FRAME_TYPE_RTS                      0xB4
#define FRAME_TYPE_CTS                      0xC4
#define FRAME_TYPE_ACK                      0xD4
#define FRAME_TYPE_CF_END                   0xE4
#define FRAME_TYPE_CF_END_ACK               0xF4

// Data frames subtypes, frame type = 2(data frame)
#define FRAME_TYPE_DATA                     0x08
#define FRAME_TYPE_DATA_CF_ACK              0x18
#define FRAME_TYPE_DATA_CF_POLL             0x28
#define FRAME_TYPE_DATA_CF_ACK_POLL         0x38
#define FRAME_TYPE_NO_DATA_FRAME            0x48
#define FRAME_TYPE_CF_ACK                   0x58
#define FRAME_TYPE_CF_POLL                  0x68
#define FRAME_TYPE_CF_ACK_POLL              0x78
#define FRAME_TYPE_QOS_DATA                 0x88
#define FRAME_TYPE_QOS_DATA_CF_ACK          0x98
#define FRAME_TYPE_QOS_DATA_CF_POLL         0xA8
#define FRAME_TYPE_QOS_DATA_CF_ACK_POLL     0xB8
#define FRAME_TYPE_QOS_NO_DATA_FRAME        0xC8
#define FRAME_TYPE_QOS_CF_ACK               0xD8
#define FRAME_TYPE_QOS_CF_POLL              0xE8
#define FRAME_TYPE_QOS_CF_ACK_POLL          0xF8

#define FRAME_TYPE_ANY_QOS_DATA_MASK        0x80

/* Category fields (such as apectrum management)*/
typedef enum
{
    CATEGORY_SPECTRUM_MANAGEMENT        = 0,
    CATEGORY_QOS                        = 1, /* quality of service */
    CATEGORY_DLS                        = 2, /*direct link setup */
    CATEGORY_BLOCK_ACK                  = 3,
    CATEGORY_PUBLIC                     = 4,
    CATEGORY_RADIO_MEASUREMENT          = 5,
    CATEGORY_FAST_BSS_TRANSITION        = 6,
    CATEGORY_HT                         = 7, /* high throughput */
    CATEGORY_SA_QUERY                   = 8, /* security agreement */
    CATEGORY_PROTECTED_DUAL_OF_PUBLIC_ACTION = 9,
    CATEGORY_WNM                        = 10, /* wireless network management */
    CATEGORY_UNPROTECTED_WNM            = 11,
    CATEGORY_TDLS                       = 12, /* tunneled direct link setup */
    CATEGORY_MESH                       = 13,
    CATEGORY_MULTI_HOP                  = 14,
    CATEGORY_SELF_PROTECTED             = 15,
    CATEGORY_DMG                        = 16, /* directional multi gigabit */
    CATEGORY_RESERVED                   = 17,
    CATEGORY_FAST_SESSION_TRANSFER      = 18,
    CATEGORY_ROBUST_AV_STREAMING        = 19,
    CATEGORY_UNPROTECTED_DMG            = 20,
    CATEGORY_VHT                        = 21, /* very high throughput */
    CATEGORY_VENDOR_SPECIFIC_PROTECTED  = 126,
    CATEGORY_VENDOR_SPECIFIC            = 127
} dot11CategoryTypes_e;

//bitfiled of all robust action frames
#define ROBUST_ACTION_FRAME_BITMASK (   BIT_x(CATEGORY_SPECTRUM_MANAGEMENT)             \
                                      | BIT_x(CATEGORY_QOS)                             \
                                      | BIT_x(CATEGORY_DLS)                             \
                                      | BIT_x(CATEGORY_BLOCK_ACK)                       \
                                      | BIT_x(CATEGORY_RADIO_MEASUREMENT)               \
                                      | BIT_x(CATEGORY_FAST_BSS_TRANSITION)             \
                                      | BIT_x(CATEGORY_SA_QUERY)                        \
                                      | BIT_x(CATEGORY_PROTECTED_DUAL_OF_PUBLIC_ACTION) \
                                      | BIT_x(CATEGORY_WNM)                             \
                                      | BIT_x(CATEGORY_MESH)                            \
                                      | BIT_x(CATEGORY_MULTI_HOP)                       \
                                      | BIT_x(CATEGORY_DMG)                             \
                                      | BIT_x(CATEGORY_FAST_SESSION_TRANSFER)           \
                                      | BIT_x(CATEGORY_ROBUST_AV_STREAMING)             \
                                    )
//Management Action Frames
#define SPECTRUM_MANAGEMENT_ACTION_CATEGORY         0
#define QOS_ACTION_FRAME_CATEGORY                   1
#define DLS_ACTION_FRAME_CATEGORY                   2
#define BLOCK_ACK_ACTION_FRAME_CATEGORY             3
#define P2P_ACTION_FRAME_CATEGORY                   4
#define LINK_MEASUREMENT_FRAME_CATEGORY             5

//Block Ack Action frame details
#define BA_ACTION_ADDBA_REQUEST		0
#define BA_ACTION_ADDBA_RESPONSE	1
#define BA_ACTION_DELBA				2

//DELBA Parameter Set field
//bit 0-10 -> reserved. bit 11 -> initiator. bits 12-15 -> TID
#define GET_TID_FROM_DELBA_PARAMETER_SET(delba)	((delba >> 12) & 0x0F)
#define SET_TID_IN_DELBA_PARAMETER_SET(delba, tid)  (delba = (delba & 0xFFF) | (tid << 12))
#define GET_INITIATOR_ROLE_FROM_DELBA_PARAMETER_SET(delba) ((delba >> 11) & 1)
#define SET_INITIATOR_ROLE_IN_DELBA_PARAMETER_SET(delba, initiator) (delba = (delba & 0xF7FF) | (initiator << 11))
#define DELBA_PARAMETER_INITIATOR	1
#define DELBA_PARAMETER_RECIPIENT	0

//ADDBA RES/REQ Parameter Set field
//bit 0 -> reserved. bit 1 -> BA Policy. bit 2-5 -> TID. bits 6-15 -> buffer size
#define GET_BA_POLICY_FROM_BA_PARAMETER_SET(ba) ((ba >> 1) & 0x0001)
#define SET_BA_POLICY_IN_BA_PARAMETER_SET(ba, initiator) (ba = (ba & 0xFFFD) | (initiator << 1))
#define GET_TID_FROM_BA_PARAMETER_SET(ba)       ((ba >> 2) & 0x000F)
#define SET_TID_IN_BA_PARAMETER_SET(ba, tid)  (ba = (ba & 0xFFC3) | (tid << 2))
#define GET_WIN_SIZE_FROM_BA_PARAMETER_SET(ba)  ((ba >> 6) & 0x03FF)
#define SET_WIN_SIZE_IN_BA_PARAMETER_SET(ba, winSize)  (ba = (ba & 0x3F) | (winSize << 6))
#define ADDBA_RES_STATUS_SUCCESS        0
#define ADDBA_BA_POLICY_DELAYED         0
#define ADDBA_BA_POLICY_IMMEDIATE       1

//link measurment action frame details
#define LINK_MEASURE_ACTION_REQ    2  
#define LINK_MEASURE_ACTION_REP    3  


#define ADDBA_RES_STATUS_SUCCESS               0
#define BA_STATUS_REQUEST_HAS_BEEN_DECLINED   37
#define DELBA_REASON_CODE_UNSPECIFIED_REASON   1


typedef enum
{
    DELBA_REASON_CODE_STA_LEAVING = 36,
    DELBA_REASON_CODE_END_BA      = 37,
    DELBA_REASON_CODE_UNKNOWN_BA  = 38,
    DELBA_REASON_CODE_TIMEOUT     = 39
} delbaReasonCode_e;

//ADDBA REQ Block Ack Starting Sequence Control field
//bit 0-3 -> fragment number = 0. bits 4-15 -> ssn
#define GET_SSN_FROM_ADDBA_REQ(ssc)                   ((ssc >> 4) & 0x0FFF)


//management Block Ack frames

//
// BlockAck starting sequence field determines where a BlockAck session begins, in the space
// of MPDU sequence numbers. The fragment number is always set to zero.
// 
typedef struct
{
    unsigned int    fragmentNumber          :   4  ; //   Bits[ 3:0] should be "0000".
    unsigned int    startingSequenceNumber  :  12  ; //   Bits[15:4] reflect the starting sequence number.

} blockAckStartingSequenceControl_t ;

//
// A wrapping union.
// 
typedef union
{
    blockAckStartingSequenceControl_t   fields ;    
    uint16_t                              overlay;    // Cover the structure with a binary unsigned int image.
} blockAckStartingSequenceControl_u ;


typedef struct __PACKED__
{
    uint8_t	                            dialogToken                     ;
    uint16_t	                            BlockAckParameterSet            ;
    uint16_t	                            BlockAckTimeoutValue            ;
    blockAckStartingSequenceControl_u	BlockAckStartingSequenceControl ;
} addbaReq_t;

typedef struct __PACKED__ 
{
    uint8_t	dialogToken;
    uint16_t	status;
    uint16_t	BlockAckParameterSet;
    uint16_t	BlockAckTimeoutValue;
} addbaRes_t;

typedef struct  
{
    uint16_t	DELBAParameterSet;
    uint16_t	reasonCode;
} delba_t;

typedef struct
{
    MGMT_Header_t   mgmtHdr;

	uint8_t	        category;
	uint8_t	        action;
	uint8_t           dialogToken;
	uint8_t           transmitPower;
	uint8_t           maxTransmitPower;
} linkMReq_t ;

typedef struct 
{
	uint8_t           elementId;
	uint8_t           length;
	uint8_t           transmitPower;
	uint8_t           linkMargin;
} TPCElement_t ;

typedef struct  
{	
	MGMT_Header_t   mgmtHdr;

	uint8_t	        category;
	uint8_t	        action;

	uint8_t	        dialogToken;
	TPCElement_t    TpcReport;
	uint8_t           reciveAntennaId;
	uint8_t           transmitAntennaId;
	uint8_t           rssi;
	uint8_t           snr;
} linkMRep_t ;

typedef struct
{
    MGMT_Header_t   mgmtHdr;

	uint8_t	        category;
	uint8_t	        action;

	union{

        addbaReq_t  addbaReq;
        addbaRes_t  addbaRes;
        delba_t     delba;

	} baCmd;
} blockAckActionFrame_t;

typedef struct
{
    uint8_t         category;
    uint8_t         action;

    union{

        addbaReq_t  addbaReq;
        addbaRes_t  addbaRes;
        delba_t     delba;

    } baCmd;
} blockAckActionFrameWitoutHdr_t;


#define P2P_ACTION_FIELD            9

//P2P oui-sub-type
typedef enum
{
    P2P_ACTION_GO_NEGO_REQ          = 0,
    P2P_ACTION_GO_NEGO_RES          = 1,
    P2P_ACTION_GO_NEGO_CONFR        = 2,
    P2P_ACTION_P2P_INVITE_REQ       = 3,
    P2P_ACTION_P2P_INVITE_RES       = 4,
    P2P_ACTION_DEVICE_DISC_REQ      = 5,
    P2P_ACTION_DEVICE_DISC_RES      = 6,
    P2P_ACTION_PROVISION_DISC_REQ   = 7,
    P2P_ACTION_PROVISION_DISC_RES   = 8
}p2pOuiSubtype_e;



typedef struct
{
    MGMT_Header_t   mgmtHdr;

	uint8_t	        category;
	uint8_t	        action;
	uint8_t	        oui[3];
	uint8_t	        ouiType;
	uint8_t	        ouiSubtype;
	uint8_t	        dialogToken;

} p2pActionFrame_t;




// Macro that gets the type and subtype fields from the frame control byte
#define GET_MPDU_TYPE_SUBTYPE(frameCtrlVar)  ((frameCtrlVar) & FRAME_TYPE_SUBTYPE_MASK)

// Macros that check for a specific type of a frame
#define IS_MPDU_TYPE_MGMT(frameTypeVar)      (((frameTypeVar) & FRAME_TYPE_MASK) == 0x00)
#define IS_MPDU_TYPE_CTRL(frameTypeVar)      (((frameTypeVar) & FRAME_TYPE_MASK) == 0x04)
#define IS_MPDU_TYPE_DATA(frameTypeVar)      (((frameTypeVar) & FRAME_TYPE_MASK) == 0x08)

#define IS_NULL_DATA_SUBTYPE(frameTypeVar)   ((frameTypeVar == FRAME_TYPE_NO_DATA_FRAME) || (frameTypeVar == FRAME_TYPE_QOS_NO_DATA_FRAME))
#define IS_MPDU_TYPE_DATA_QOS(frameTypeVar)  (((frameTypeVar) & (FRAME_TYPE_MASK | FRAME_TYPE_ANY_QOS_DATA_MASK)) == (FRAME_TYPE_DATA | FRAME_TYPE_ANY_QOS_DATA_MASK))
#define REMOVE_QOS_INDICATION(frameTypeVar)  ((frameTypeVar) &= ~FRAME_TYPE_ANY_QOS_DATA_MASK)
#define ADD_QOS_INDICATION(frameTypeVar)     ((frameTypeVar) |= FRAME_TYPE_ANY_QOS_DATA_MASK)

#define GET_MPDU_QOS_DATA_SUBTYPE(frameCtrlVar)  ((frameCtrlVar) & FRAME_TYPE_QOS_DATA)

#define GET_PROTOCOL_VERSION(frameTypeVar)   ((frameTypeVar) & 0x03)

#define IS_A_MSDU_PRESENT(frmPtr) ((((((QOS_MPDUHeader_t *)(frmPtr))->frameCtrl) & \
                                  (FRAME_TYPE_QOS_DATA | FRAME_TYPE_QOS_DATA_CF_ACK | \
                                   FRAME_TYPE_QOS_DATA_CF_POLL | FRAME_TYPE_QOS_DATA_CF_ACK_POLL)) && \
                                  ((((QOS_MPDUHeader_t *)(frmPtr))->qosCtrl) & BIT_7)) ? (1) : (0))

#define DEFAULT_UP                      0           /* Default user priority (non QOS) */

// QOS subtypes in frameType
#define QOS_ACK_SUBTYPE_BIT      (0x0010)
#define QOS_POLL_SUBTYPE_BIT     (0x0020)
#define QOS_NON_DATA_SUBTYPE_BIT (0x0040)

#define QOS_GET_ACK(frameTypeVar)                ((frameTypeVar) & QOS_ACK_SUBTYPE_BIT)
#define QOS_GET_POLL(frameTypeVar)               ((frameTypeVar) & QOS_POLL_SUBTYPE_BIT)
#define QOS_GET_NON_DATA(frameTypeVar)           ((frameTypeVar) & QOS_NON_DATA_SUBTYPE_BIT)


// MPDUHeader_t.frameCtrl bit fields
#define FCTL_TO_DS        0x01
#define FCTL_FROM_DS      0x02
#define FCTL_AP_TO_AP     0x03
#define FCTL_MORE_FRAGS   0x04
#define FCTL_RETRY        0x08
#define FCTL_PWR_MGMT     0x10
#define FCTL_MORE_DATA    0x20
#define FCTL_PROTECTED    0x40
#define FCTL_ORDER        0x80  /* not used */

#define TEST_TO_DS_BIT(frameCtrlVar)         ((((frameCtrlVar) & FCTL_TO_DS) == FCTL_TO_DS) ? TRUE: FALSE)
#define TEST_FROM_DS_BIT(frameCtrlVar)       ((((frameCtrlVar) & FCTL_FROM_DS) == FCTL_FROM_DS) ? TRUE: FALSE)

#define TEST_TO_DS_BIT_ONLY(frameCtrlVar)    ((((frameCtrlVar) & FCTL_AP_TO_AP) == FCTL_TO_DS) ? TRUE: FALSE)
#define TEST_FROM_DS_BIT_ONLY(frameCtrlVar)  ((((frameCtrlVar) & FCTL_AP_TO_AP) == FCTL_FROM_DS) ? TRUE: FALSE)
#define TEST_AP_TO_AP(frameCtrlVar)          ((((frameCtrlVar) & FCTL_AP_TO_AP) == FCTL_AP_TO_AP) ? TRUE: FALSE)
#define TEST_MORE_FRAGS_BIT(frameCtrlVar)    (((frameCtrlVar) & FCTL_MORE_FRAGS) ? TRUE: FALSE)
#define TEST_RETRY_BIT(frameCtrlVar)         (((frameCtrlVar) & FCTL_RETRY     ) ? TRUE: FALSE)
#define TEST_PWR_MGMT_BIT(frameCtrlVar)      (((frameCtrlVar) & FCTL_PWR_MGMT  ) ? TRUE: FALSE)
#define TEST_MORE_DATA_BIT(frameCtrlVar)     (((frameCtrlVar) & FCTL_MORE_DATA ) ? TRUE: FALSE)
#define TEST_PROTECTED_BIT(frameCtrlVar)     (((frameCtrlVar) & FCTL_PROTECTED ) ? TRUE: FALSE)
#define TEST_FRAME_ORDER_BIT(frameCtrlVar)   (((frameCtrlVar) & FCTL_ORDER     ) ? TRUE: FALSE)

#define CLR_MORE_FRAGS_BIT(frameCtrlVar)   ((frameCtrlVar) &= ~FCTL_MORE_FRAGS)
#define SET_MORE_FRAGS_BIT(frameCtrlVar)   ((frameCtrlVar) |= FCTL_MORE_FRAGS)

#define CLR_MORE_DATA_BIT(frameCtrlVar)   { (frameCtrlVar) &= ~FCTL_MORE_DATA; } 
#define SET_MORE_DATA_BIT(frameCtrlVar)   { (frameCtrlVar) |=  FCTL_MORE_DATA; } 


// MPDUHeader_t.duration field 
#define FDUR_CTRL           (0x8000)  //bit 15 used to indicate field usage apart from frame subtypes
#define FDUR_DURATION_MASK  (0x7FFF)  //only bits 0 - 14 for duration value
#define FDUR_AID_MASK       (0x3FFF)  //only bits 0 - 13 for AID, only used for Power Save Poll frames

// this tests a duration field to see if it is a NAV update or an AID for a power save poll frame
#define TEST_DUR_UPDATE_VAL(dur)                        ((dur & FDUR_CTRL) ? TRUE: FALSE)


// MPDUHeader_t.seqNum field
#define GET_FRAG_NUM(seqNum)  ((seqNum) & 0x000F)
#define GET_SEQ_NUM(seqNum)   ((seqNum >> 4) & 0x0FFF)
#define SET_SEQ_NUM(hdr,seqnum)   (hdr->seqNum = (seqnum << 4)) /*Zero fragment num*/
#define SET_FRAG_NUM(hdr,fragNum)   (hdr->seqNum = ( hdr->seqNum & 0xFFF0) | fragNum)
#define INCREMENT_SEQ_NUM(seqNum) (((seqNum)+0x10) & 0xFFF0) /*Zero fragment num*/

// MPDUHeader_t MAC Address testing
#define TEST_UNICAST_ADDRESS(MACAddr)   ((MACAddr[0] & 0x01) ? FALSE : TRUE)
#define TEST_MULTICAST_ADDRESS(MACAddr) ((MACAddr[0] & 0x01) ? TRUE : FALSE)
#define TEST_BROADCAST_ADDRESS(MACAddr) (IRQ_UtilCompareMacAddress(MACAddr, (const u8 *)"\xff\xff\xff\xff\xff\xff"))


// Other fields using fPtr of MPDUHeader_t ptr
#define CHK_FRAME_TO_DS(hPtr)           (TEST_TO_DS_BIT((hPtr)->frameCtrl))
#define CHK_FRAME_FROM_DS(hPtr)         (TEST_FROM_DS_BIT((hPtr)->frameCtrl))

#define CHK_FRAME_TO_DS_ONLY(hPtr)      (TEST_TO_DS_BIT_ONLY((hPtr)->frameCtrl))
#define CHK_FRAME_FROM_DS_ONLY(hPtr)    (TEST_FROM_DS_BIT_ONLY((hPtr)->frameCtrl))
#define CHK_FRAME_AP_TO_AP(hPtr)        (TEST_AP_TO_AP((hPtr)->frameCtrl))
#define CHK_FRAME_PROTECTED(hPtr)       (TEST_PROTECTED_BIT((hPtr)->frameCtrl))

#define CHK_DUR_UPDATE_VAL(hptr)        (TEST_DUR_UPDATE_VAL((hPtr)->duration) ? TRUE: FALSE)

#define QOS_CTL_ACK_POLICY_MASK  (BIT_5 | BIT_6)
#define QOS_CTL_ACK              (0 << 5)
#define QOS_CTL_NOACK            (1 << 5)
#define QOS_CTL_NO_EXPLICIT_ACK  (2 << 5)
#define QOS_CTL_BLK_ACK          (3 << 5)
#define GET_MPDU_QOS_ACK_POLICY_FROM_QOS_CTL(qosCtrl)      (qosCtrl & 0x0060)
#define GET_MPDU_QOS_ACK_POLICY(hPtr)      (((QOS_MPDUHeader_t *)(hPtr))->qosCtrl & 0x0060)
#define SET_MPDU_QOS_ACK_POLICY(hPtr,ackPolicy)  (((QOS_MPDUHeader_t *)(hPtr))->qosCtrl = ((((QOS_MPDUHeader_t *)(hPtr))->qosCtrl & ~QOS_CTL_ACK_POLICY_MASK) | ackPolicy ))
												   

/* the size of the header in octets */
void appendMpdu(void* pMpdu, uint32_t mpduLen, const uint8_t *data, uint32_t dataSize);
void copyTailMpdu(const void* pMpdu, uint32_t mpduLen, uint8_t *data, uint32_t dataSize);

/*
    Addresses 

    From 
    "Draft Supplement to STANDARD FOR Telecommunications 
     and Information Exchange Between Systems - LAN/MAN Specific Requirements - 
     Part 11: Wireless Medium Access Control (MAC) and Physical Layer (PHY) specifications: 
     Medium Access Control (MAC) Enhancements for Quality of Service (QoS)"

    Saved at: \\Grumpy1\libraries\Technical Library\Standards - External\IEEE 802.11\Drafts\TGe-QoS_Enhancements
    and dated: Friday, November 15, 2002 4:51:56 AM


    Table 4, pg 29
      To   From   Addr    Addr    Addr    Addr   Usage 
      DS   DS      1       2       3       4
      ---  ---    ------  ------  ------  ------  ---------------------------------------
      0    0      DA      SA      BSSID   N/A     STA to STA traffic in an IBSS and QSTA-to-QSTA traffic in a QBSS
      0    1      DA      BSSID   SA      N/A     AP-to-STA traffic in a BSS
      1    0      BSSID   SA      DA      N/A     STA-to-AP traffic in a BSS
      1    1      RA      TA      DA      SA      WDS traffic between APs (AP to AP)

    (DA=DestAddr, SA=SrcAddr, RA=?, TA=?)
*/
#define GET_TX_ADDR_PTR(hPtr)     ((hPtr)->MACAddress2)
#define GET_RX_ADDR_PTR(hPtr)     ((hPtr)->MACAddress1)

#define GET_TRANSMITTER_ADDR_PTR(hPtr)     ((hPtr)->MACAddress2)
#define GET_RECEIVER_ADDR_PTR(hPtr)     ((hPtr)->MACAddress1)

#define GET_DEST_ADDR_PTR(hPtr)   (CHK_FRAME_TO_DS_ONLY(hPtr)                                 \
                                    ? ((hPtr)->MACAddress3)                              \
                                    : ((hPtr)->MACAddress1))
#define GET_SRC_ADDR_PTR(hPtr)    (CHK_FRAME_AP_TO_AP(hPtr)                              \
                                    ? (((AP_TO_AP_MPDUHeader_t *)hPtr)->MACAddress4)     \
                                    : (CHK_FRAME_FROM_DS_ONLY(hPtr)                           \
                                        ? ((hPtr)->MACAddress3)                          \
                                        : ((hPtr)->MACAddress2)))

/* Get BSSID address */
/* To DS | From DS | Address */
/*   0       0        Addr3  */
/*   0       1        Addr2  */
/*   1       0        Addr1  */
/*   1       1        Addr1  */
#define GET_BSSID_ADDR_PTR(hPtr)     (CHK_FRAME_TO_DS(hPtr) ? \
                                       ((hPtr)->MACAddress1) : \
                                       (CHK_FRAME_FROM_DS(hPtr) ? ((hPtr)->MACAddress2) : ((hPtr)->MACAddress3)))


//Duration stuff
#define GET_FRAME_DURATION(hPtr)         ((hPtr)->duration & FDUR_DURATION_MASK)
#define GET_PWR_SAVE_POLL_AID(hPtr)      ((hPtr)->duration & FDUR_AID_MASK)


// Quality of Service stuff, valid if the frame contains QoS header !!!
#define QOS_GET_UP(hPtr)                    (((((QOS_MPDUHeader_t *)(hPtr))->qosCtrl)) & 0x0007)
#define QOS_GET_UP_AP_TO_AP(hPtr)           (((((QOS_AP_MPDUHeader_t *)(hPtr))->qosCtrl)) & 0x0007)
#define QOS_GET_ACK_POLICY(hPtr)            ((((((QOS_MPDUHeader_t *)(hPtr))->qosCtrl)) & 0x0060) >> 5)
#define QOS_GET_ACK_POLICY_AP_TO_AP(hPtr)   ((((((QOS_AP_MPDUHeader_t *)(hPtr))->qosCtrl)) & 0x0060) >> 5)
#define QOS_GET_EOSP(hPtr)                  ((((((QOS_MPDUHeader_t *)(hPtr))->qosCtrl)) & 0x0010) >> 4)
#define QOS_GET_TID(hPtr)                   (((((QOS_MPDUHeader_t *)(hPtr))->qosCtrl)) & 0x000F)
#define QOS_SET_TID(hPtr,tid)				(((QOS_MPDUHeader_t *)(hPtr))->qosCtrl = ((((QOS_MPDUHeader_t *)(hPtr))->qosCtrl & 0xFFF0) | tid))

#define QOS_SET_EOSP(hPtr,eosp)                                                                     \
        {                                                                                           \
            const uint32_t qos_ctrl = ( (QOS_MPDUHeader_t*) (hPtr) )->qosCtrl                     ;   \
            ( (QOS_MPDUHeader_t*) (hPtr) )->qosCtrl = ( (qos_ctrl & ~0x0010) | ((eosp)<< 4)  )   ;   \
        } // MACRO QOS_SET_EOSP(). //

#define P2P_ACTION_FRAME_HEADER_SIZE (7) 
//BAR MPDU
#define BAR_MPDU_HEADER_SIZE				16	//frame control + duration + ra + ta (2+2+6+6)
#define BAR_MPDU_BAR_CONTROL_FIELD_SIZE		2
#define BAR_MPDU_SSN_FIELD_SIZE				2

#define GET_TID_FROM_BAR(hPtr)		        (((BarCompressedFrame_t *)(hPtr))->barCtl.tid)

//BA MPDU
#define BA_CTRL_BA_POLICY_NORMAL_ACK    0
#define BA_CTRL_BA_POLICY_NO_ACK        1

#define BA_CTRL_MTID_DISABLE        0
#define BA_CTRL_MTID_ENABLE         1

#define BA_CTRL_COMPRESSED_DISABLE  0
#define BA_CTRL_COMPRESSED_ENABLE   1

#define SET_SSN_IN_BA_SSN(ssn, baSsnField)  (baSsnField = (ssn << 4))
        
#define BA_COMPRESSED_BITMAP_LENGTH 8

//HT Control Fields
#define HT_GET_AC_CONSTRAINT(HT_Ctrl)   (((HT_Control_t)HT_Ctrl).ac_constraint)
#define HT_GET_RDG_MORE_PPDU(HT_Ctrl)   (((HT_Control_t)HT_Ctrl).RDG_morePPDU)

//when receiving frames, the bytes are in reverse order.
//use this to flip a MAC address before comparing it against a normally ordered one.


//
// 17-feb-2009 - jigal - code optimization (taken from Haim BT team).
//                       Flip and Compare MAC addresses are now written as ASM functions.
// 
#define FLIP_MAC_ADDRESS(addrPtr, flippedAddrPtr) \
    {                                                       \
        IRQ_UtilFlipMacAddress( addrPtr, flippedAddrPtr ) ; \
    } // MACRO FLIP_MAC_ADDRESS(). //

#define COMPARE_MAC_ADDRESSES(addrPtr1, addrPtr2)           \
    (                                                       \
        IRQ_UtilCompareMacAddress ( addrPtr1, addrPtr2 )    \
    ) // MACRO COMPARE_MAC_ADDRESSES() //

/******************** frame body **********************************/
//Wep encrypted frames have mpdu lengths that include the IV and ICV
#define WEP_IV_SIZE  4
#define WEP_ICV_SIZE 4

//TKIP packet is made up of WEP_IV_SIZE + TKIP_EIV_SIZE + TKIP_MIC_SIZE + WEP_ICV_SIZE
#define TKIP_EIV_SIZE	(4)
#define TKIP_MIC_SIZE	(8)
#define TKIP_TSC_SIZE	(6)

//TKIP IV FIELD
#define TKIP_IV_TSC1_OFFSET 	(0)
#define TKIP_IV_WEPSEED_OFFSET 	(8)
#define TKIP_IV_TSC0_OFFSET 	(16)
#define TKIP_IV_RESERVED_OFFSET	(24)
#define TKIP_IV_EIV_FLAG_OFFSET	(29)
#define TKIP_IV_KEYID_OFFSET	(30)

//TKIP EIV FIELD
#define TKIP_EIV_TSC2_OFFSET	(0)
#define TKIP_EIV_TSC3_OFFSET	(8)
#define TKIP_EIV_TSC4_OFFSET	(16)
#define TKIP_EIV_TSC5_OFFSET	(24)


//mpdu-length doesn't include this.
#define FCS_LENGTH  4

//the following parameter is declared in the main to allow the Gtrace to 
//parse ConnectionTracking_e 
//since no real variable is using this enum, it is not included in the bin file
//volatile ConnectionTracking_e ConnectionTracking= DEAUTHENTICATION;

typedef enum
{
    ASSOCIATION_REQUEST      = 0x00,
    ASSOCIATION_RESPONSE     = 0x10,
    REASSOCIATION_REQUEST    = 0x20,
    REASSOCIATION_RESPONSE   = 0x30,
    DISASSOCIATION           = 0xA0,
    AUTHENTICATION           = 0xB0,
    DEAUTHENTICATION         = 0xC0        
}ConnectionTracking_e;

//MACRO helper for tracing MAC
#define MAC_CHAR_TO_INT_HIGH(mac)                   ((mac[0]<<8) + mac[1])
#define MAC_CHAR_TO_INT_LOW(mac)                    ((mac[2]<<24) + (mac[3]<<16) + (mac[4]<<8) + mac[5])

// Bitmap definition for the OM field in the A-ctrl (HTC) field.
// The rest of the bits are always zero due to the limitations of the
#define     HTC_OM_UL_MU_DISABLE_BIT        BIT_5
#define     HTC_OM_ER_SU_DISABLE_BIT        BIT_9
#define     HTC_OM_UL_MU_DATA_DISABLE_BIT   BIT_11

#if GET_UP_FUNC
static uint8_t GetUP(MPDUHeader_t *hdr)
{
    uint8_t up = DEFAULT_UP;

    if (IS_MPDU_TYPE_DATA_QOS(hdr->frameType))
    {
        if (CHK_FRAME_AP_TO_AP(hdr))
        {
            up = QOS_GET_UP_AP_TO_AP(hdr);
        }
        else
        {
            up = QOS_GET_UP(hdr);
        }
    }
    return up;
}
#endif
#endif // MPDU_H
