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
/* Module:      tiQosTypes.h*/
/**/
/* Purpose:     */
/**/
/*--------------------------------------------------------------------------*/

#ifndef TI_QOS_TYPES_H
#define TI_QOS_TYPES_H

#include "osi_type.h"
#define MAX_NUM_OF_802_1d_TAGS          8
#define MAX_USER_PRIORITY               7

/*
 * This enum defines the protocol modes of the QOS management object
 */
typedef enum
{
    QOS_WME,
    QOS_NONE

} EQosProtocol;


/*
 * This enum includes the header converting modes configured to dataCtrl object.
 */
typedef enum
{
    HDR_CONVERT_NONE,
    HDR_CONVERT_QOS,
    HDR_CONVERT_LEGACY

} EHeaderConvertMode;


typedef enum
{
    QOS_AC_BE = 0,
    QOS_AC_BK,
    QOS_AC_VI,
    QOS_AC_VO,
    QOS_HIGHEST_AC_INDEX = QOS_AC_VO,

    // Force enum to 32 bit
    QOS_MAX = 0xFFFFFFFF

} EAcTrfcType;


#define FIRST_AC_INDEX                  QOS_AC_BE
#define AC_PARAMS_MAX_TSID              15
#define MAX_APSD_CONF                   0xffff


typedef enum
{
    DROP_NEW_PACKET = 0,
    DROP_OLD_PACKET

} EQOverflowPolicy;


typedef enum
{
    AC_NOT_ADMITTED,
    AC_WAIT_ADMISSION,
    AC_ADMITTED

} ETrafficAdmState;


/* 
 * This enum defines the admission state configured to dataCtrl object.
 */
typedef enum
{
    ADMISSION_NOT_REQUIRED,
    ADMISSION_REQUIRED

} EAdmissionState;


typedef struct
{
    /* Power save mode */
    uint8_t                PsMode;             
    uint16_t               TxQueueSize;
    uint8_t                QueueIndex;
    EQOverflowPolicy        QueueOvFlowPolicy;
    uint8_t                ackPolicy;
    uint32_t               MsduLifeTime;

} TAcTrfcCtrl;

typedef struct
{
    ETrafficAdmState        admissionState; /**< AC admission state */
    EAdmissionState         admissionRequired;      /**< AC admission is mandatory */
    EAcTrfcType             tag_ToAcClsfrTable[MAX_NUM_OF_802_1d_TAGS]; /**< Tag to AC classification */

} TQosParams;


typedef struct
{
    uint8_t                *tsrsArr;
    uint8_t                tsrsArrLen;
    uint8_t                acID;
} TTsrsQosParams;


typedef struct _OS_802_11_QOS_PARAMS
{
    uint32_t               acID;
    uint32_t               MaxLifeTime;
    uint32_t               PSDeliveryProtocol;
	uint32_t				VoiceDeliveryProtocol;

} OS_802_11_QOS_PARAMS;


typedef struct  
{
    uint32_t               psPoll; /**< The maximum time the device waits to receive traffic from the AP after transmission of PS-poll	*/
    uint32_t               UPSD;   /**< The maximum time the device waits to receive traffic from the AP after transmission from UPSD
									 * enabled queue */

} OS_802_11_QOS_RX_TIMEOUT_PARAMS;


typedef struct _OS_802_11_AC_QOS_PARAMS
{
    uint32_t               uAC;
    uint32_t               uAssocAdmissionCtrlFlag;
    uint32_t               uAIFS;
    uint32_t               uCwMin;
    uint32_t               uCwMax;
    uint32_t               uTXOPLimit;

} OS_802_11_AC_QOS_PARAMS;


typedef struct _OS_802_11_AP_QOS_CAPABILITIES_PARAMS
{
    uint32_t               uQOSFlag;
    uint32_t               uAPSDFlag;

} OS_802_11_AP_QOS_CAPABILITIES_PARAMS;


typedef struct _OS_802_11_QOS_TSPEC_PARAMS
{
	uint32_t uTid;
	uint32_t eDirection;
	uint32_t uAPSDFlag;
	uint32_t uUserPriority;
	uint32_t uNominalMSDUsize; /* in bytes */
	uint32_t bFixedMsduSize; /* boolean (0 � No, 1 � Yes) */
	uint32_t uMeanDataRate; /* bits per second */
	uint32_t uMinimumPHYRate; /* 1,2,5,6,9,11,12,18,......*/
	uint32_t uSurplusBandwidthAllowance;
	uint32_t uMaxiMsduSize; /* optional */
	uint32_t uMaxBurstSize; /* optional */
	uint32_t uMinDataRate; /* optional */
	uint32_t uPeakDataRate; /* optional */
	uint32_t uMediumTime;
	uint32_t uReasonCode;
} OS_802_11_QOS_TSPEC_PARAMS;


typedef struct _OS_802_11_QOS_DELETE_TSPEC_PARAMS
{
    uint32_t               uUserPriority;
    uint32_t               uReasonCode;
} OS_802_11_QOS_DELETE_TSPEC_PARAMS;


typedef struct _OS_802_11_QOS_DESIRED_PS_MODE
{
    uint32_t               uDesiredPsMode;	/**< Power save mode according to PSScheme_e */
    uint32_t               uDesiredWmeAcPsMode[QOS_HIGHEST_AC_INDEX + 1];	/**< Power save mode, per AC, according to PSScheme_e */

} OS_802_11_QOS_DESIRED_PS_MODE;


/* When this value is added to reason code in TSPEC events, it indicates a TSPEC response which was unexpected at the time */
/* For example, a TSPEC response arrives after a TSPEC timeout */
#define TSPEC_RESPONSE_UNEXPECTED      0x1000   


typedef enum
{
    ADDTS_RESPONSE_ACCEPT = 0,
    ADDTS_RESPONSE_REJECT = 3,
    ADDTS_RESPONSE_AP_PARAM_INVALID = 253,
    ADDTS_RESPONSE_TIMEOUT = 254,
    TSPEC_DELETED_BY_AP = 255

} ETspecStatus;


typedef struct _OS_802_11_AC_UPSD_STATUS_PARAMS
{
   uint32_t                uAC;
   uint32_t                uCurrentUAPSDStatus;
   uint32_t                pCurrentAdmissionStatus;

} OS_802_11_AC_UPSD_STATUS_PARAMS;


typedef struct OS_802_11_THRESHOLD_CROSS_INDICATION_PARAMS
{
    uint32_t               uAC;
    uint32_t               uHighOrLowThresholdFlag;  /* According to thresholdCross_e enum */
    uint32_t               uAboveOrBelowFlag;        /* According to thresholdCrossDirection_e enum */

} OS_802_11_THRESHOLD_CROSS_INDICATION_PARAMS;


typedef enum
{
    HIGH_THRESHOLD_CROSS,
    LOW_THRESHOLD_CROSS

} EThresholdCross;


typedef enum
{
    CROSS_ABOVE,
    CROSS_BELOW

} EThresholdCrossDirection;


typedef struct
{
   uint32_t                dstIpAddress;
   uint32_t                dstPort;
   uint32_t                PktTag;
   uint32_t                userPriority;

} TStreamTrafficProperties;


typedef enum
{
   UPLINK_DIRECTION = 0,
   DOWNLINK_DIRECTION = 1,
   RESERVED_DIRECTION = 2,
   BI_DIRECTIONAL = 3

} EStreamDirection;


/* classification algorithms: 
  0) D-tag to D-tag
  1) DSCP to D-tag
  2) Destination port number to D-tag 
  3) Destination IP&Port to D-tag
*/
typedef enum
{
    D_TAG_CLSFR    = 0,
    DSCP_CLSFR     = 1,
    PORT_CLSFR     = 2,
    IPPORT_CLSFR   = 3,
    CLSFR_MAX_TYPE = IPPORT_CLSFR

} EClsfrType;



/*************************/
/*   classifier params   */
/*************************/

/* Destination IP address and port number */
typedef struct 
{
    uint32_t               DstIPAddress;
    uint16_t               DstPortNum;

} TIpPort;

/* Classification mapping table */
typedef struct 
{
    union   
    {
        TIpPort            DstIPPort;  /* for destination IP&Port classifier*/
        uint16_t           DstPortNum; /* for destination Port classifier*/
        uint8_t            CodePoint;  /* for DSCP classifier*/
    } Dscp;

    uint8_t                DTag;

} TClsfrTableEntry;

/* number of classifier entries in the classification table */
#define NUM_OF_CLSFR_TABLE_ENTRIES  8

typedef struct
{
    EClsfrType              eClsfrType; /* The type of the classifier: D-tag, DSCP, Port or IP&Port */
    uint32_t               uNumActiveEntries; /* The number of active entries in the classification table */
    TClsfrTableEntry        ClsfrTable[NUM_OF_CLSFR_TABLE_ENTRIES]; /* Classification table - size changed from 15 to 16*/

} TClsfrParams;

typedef struct{
	uint8_t                       voiceTspecConfigure;
	uint8_t                       videoTspecConfigure;
}TSpecConfigure;


/* Init classification mapping table - used only for INIT table at set defaults! */
typedef struct 
{
    /* For IP & Port classifier*/
    struct   
    {
        uint32_t           DstIPAddress;
        uint16_t           DstPortNum;
        uint8_t            DTag;
    } IpPort;

    /* For Port classifier*/
    struct   
    {
        uint16_t           DstPortNum; 
        uint8_t            DTag;
    } Port;

    /* For DSCP classifier*/
    struct   
    {
        uint8_t            CodePoint;
        uint8_t            DTag;
    } Dscp;

} TInitClsfrTableEntry;

typedef struct
{
    EClsfrType              eClsfrType; /* The type of the classifier: D-tag, DSCP, Port or IP&Port */
    uint32_t               uNumActiveEntries; /* The number of active entries in the classification table */
    TInitClsfrTableEntry    ClsfrTable[NUM_OF_CLSFR_TABLE_ENTRIES]; /* Classification table - size changed from 15 to 16*/

} TClsfrInitParams;

#endif /* TI_QOS_TYPES_H */

