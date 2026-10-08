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
/****************************************************************************/
/*									    */
/*    MODULE:   paramOut.h						    */
/*    PURPOSE:								    */
/*									    */
/****************************************************************************/

#ifndef __PARAM_OUT_H__
#define __PARAM_OUT_H__


#include "ti_qos_types.h"
#include <public_types.h>


#define WLANLINKS_INVALID_HLID     0xff

#define REG_DOMAIN_MAX_CHAN_NUM            15
//#define REG_DOMAIN_MAX_REG_CLASS_NUM       10
//
//#define DOT11_MAX_DEFAULT_WEP_KEYS          4
//
//#define RX_LEVEL_TABLE_SIZE                 15
//
//#define RX_DATA_FILTER_MAX_FIELD_PATTERNS   8
//#define RX_DATA_FILTER_FILTER_BOUNDARY      256
//
///* Soft gemini  values */
//
///* Used by UtilInfoCodeQueryInformation , UtilInfoCodeSetInformation */
//#define VAL_TX_POWER_VALUE			100
//#define VAL_NETWORK_TYPE			101
//#define VAL_AP_TX_POWER_LEVEL	    102
///* #define VAL_COUNTRY_CODE    	        103 */
///* #define VAL_REG_DOMAIN_BAND_24	    104 */
///* #define VAL_REG_DOMAIN_BAND_50	    105 */
//#define VAL_PACKET_BURSTING			106
//#define VAL_MIXED_MODE				107
//#define VAL_PRIVACY_MODE			108
//#define VAL_CCX_SECURITY			109
//#define VAL_DEFAULT_KEY_ID			110
//#define VAL_AP_SUPPORT_CHANELS 		111
//
//#define MAX_AP_PARAM_LENGTH         800

//typedef struct
//{
//    tiwdrv_rate_e    maxBasic;
//    tiwdrv_rate_e    maxActive;
//} ratePair_t;
//
///* Parameters Structures Definitions per parameter type */
//typedef enum
//{
//    AUTH_LEGACY_OPEN_SYSTEM     = 0,
//    AUTH_LEGACY_SHARED_KEY      = 1,
//	AUTH_LEGACY_FT              = 2,
//    AUTH_LEGACY_AUTO_SWITCH     = 3,
//    AUTH_LEGACY_RESERVED1       = 128,
//    AUTH_LEGACY_NONE            = 255
//} legacyAuthType_e;

//typedef enum
//{
//    CONNECTION_NONE             = 0,
//    CONNECTION_INFRA            = 1,
//    CONNECTION_IBSS             = 2,
//    CONNECTION_SELF             = 3
//} connectionType_e;
//
//typedef enum
//{
//    RADIO_IN_STAND_BY           = 0,
//    RADIO_OUT_OF_STAND_BY       = 1
//}radioStandByState_t;
//
/**** Regulatory Domain module types ****/
typedef struct
{
	uint8_t		*listOfChannels;
	uint8_t		sizeOfList;
} supportedChannels_t;



///* Scan Control Table for 2.4-G band type */
//typedef struct
//{
//    uint8_t       aChannelsList[NUM_OF_CHANNELS_24];
//} scanControlTable24_t;
//
///* Scan Control Table for 5G-band type */
//typedef struct
//{
//    uint8_t       aChannelsList[A_5G_BAND_NUM_CHANNELS];
//} scanControlTable5_t;
//
///* Scan Control Table type */
//typedef struct
//{
//    ERadioBand             band;
//    scanControlTable5_t     ScanControlTable5;
//    scanControlTable24_t    ScanControlTable24;
//} scanControlTable_t;
//
///** \enum regulatoryDomain_scanOption_e
// * \brief Regulatory Domain Scan Options
// *
// * \par Description
// * Enumerates the scan type to used by regulatory domain queries
// *
// * \sa
// */
//typedef enum
//{
//    ACTIVE_SCANNING     = 0,	/**< The query is for active scanning (requires transmission on the channel)	*/
//    PASSIVE_SCANNING    = 1		/**< The query is for passive scanning (no transmission is required)			*/
//} regulatoryDomain_scanOption_e;
//
//typedef struct
//{
//    uint8_t*      pChannelBitMap;
//    uint8_t       channelCnt;
//    TI_INT8        txPower;
//} regulatoryDomainParam_t;
//
//typedef enum
//{
//    PHY_UNKNOWN         = 0,
//    PHY_FH              = 1,
//    PHY_DSS             = 2,
//    PHY_UN_USED         = 3,
//    PHY_OFDM            = 4,
//    PHY_HIGH_RATE_DSS   = 5,
//    PHY_ERP             = 6
//} phyType_e;
//
//typedef enum
//{
//    DRIVER_STATUS_IDLE              = 0,
//    DRIVER_STATUS_RUNNING           = 1
//} driverStatus_e;
//
///* enumerator for PRE_AUTH event */
//typedef enum
//{
//   RSN_PRE_AUTH_START,
//   RSN_PRE_AUTH_END
//} preAuthStatusEvent_e;
//
//
//typedef enum
//{
//    STATUS_SCANNING         = 0,
//    STATUS_SCAN_COMPLETE    = 1
//} scanStatus_e;
//
//typedef enum
//{
//    SCAN_DISABLED   = 0,	/* TI_FALSE*/
//    SCAN_ENABLED    = 1,	/* TI_TRUE*/
//	SKIP_NEXT_SCAN	= 2		/* Skip only one next coming scan, then set this parameter to TI_TRUE*/
//} scanEnabledOptions_e;
//
//typedef struct rxDataFilterFieldPattern_t
//{
//    uint16_t       offset; /*  Offset of the field to compare from the start of the packet*/
//    uint8_t       length; /* Size of the field pattern */
//    uint8_t       flag; /* Bit Mask flag */
//    uint8_t       pattern[RX_DATA_FILTER_MAX_PATTERN_SIZE]; /* expected pattern */
//    uint8_t       mask[RX_DATA_FILTER_MAX_PATTERN_SIZE]; /* bit-masking of the internal field content */
//} rxDataFilterFieldPattern_t;
//
//typedef struct
//{
//	void	*handler;
//	void	*callback;
//}QoS_renegVoiceTspecReq_t;
//
///* Authentication/encryption capability */
//#define MAX_AUTH_ENCR_PAIR 13
//
//typedef struct
//{
//	EExternalAuthMode   authenticationMode;
//	ECipherSuite        cipherSuite;
//
//} authEncrPairList_t;
//
//typedef struct
//{
//	uint32_t              NoOfPMKIDs;
//	uint32_t              NoOfAuthEncrPairSupported;
//	authEncrPairList_t     authEncrPairs[MAX_AUTH_ENCR_PAIR];
//
//} rsnAuthEncrCapability_t;
//
//typedef struct
//{
//	uint32_t       numOfPreAuthBssids;
//	TMacAddr     	*listOfPreAuthBssid;
//
//} rsnPreAuthBssidList_t;
//
//
//typedef struct
//{
//    TI_INT32       rssi;
//    uint8_t       snr;
//} signal_t;
//
//
//typedef struct
//{
//
//    uint8_t        *assocRespBuffer;
//    uint32_t       assocRespLen;
//    uint8_t        *assocReqBuffer;
//    uint32_t       assocReqLen;
//
//} assocInformation_t;
//
///************************************/
///*      QOS edcf params             */
///************************************/
//
///*
//#define CW_MIN_DEF                         15
//#define CW_MIN_MAX                         31
//#define CW_MAX_DEF                         1023
//*/
//#define CW_MIN_DEF                         4 /* the power of 2 - cwMin = 2^4-1 = 15 */
//#define CW_MIN_MAX                         5 /* the power of 2 - cwMax = 2^5-1 = 31 */
//#define CW_MAX_DEF                         10
//
//#define AIFS_DEF                            2
//#define NO_RX_TIME_OUT                      0
//#define NO_RX_ACK_POLICY                    0
//#define DATA_DCF                            0    /* MSDUs are sent completely including retrys - normal legacy traffic */
//#define QOS_DATA_EDCF                       1    /* MPDUs are sent according to TXOP limits - */
//#define RETRY_PREEMPTION_DISABLE            0
//#define QOS_CONTROL_TAG_MASK                0x0007
//#define QOS_CONTROL_EOSP_MASK                0x0010
//
//
//
//typedef enum{
//    AC_ACTIVE = 0,
//    AC_NOT_ACTIVE
//}acActive;
//
//
//
//
//
//
//typedef struct{
//	uint32_t		trafficAdmCtrlResponseTimeout;
//    TI_BOOL        trafficAdmCtrlUseFixedMsduSize;
//}trafficAdmCtrlInitParams_t;
//
//typedef struct{
//    TI_BOOL       wmeEnable;
//    TI_BOOL       trafficAdmCtrlEnable;
//    TI_BOOL       qosTagZeroConverHeader;
//	uint8_t      PacketBurstEnable;
//	uint32_t     PacketBurstTxOpLimit;
//    uint32_t     TxOpLimit[MAX_NUM_OF_AC];
//    uint32_t     MsduLifeTime[MAX_NUM_OF_AC];
//    TRxTimeOut    rxTimeOut;
//    uint8_t      ShortRetryLimit[MAX_NUM_OF_AC];
//    uint8_t      LongRetryLimit[MAX_NUM_OF_AC];
//    uint8_t      desiredWmeAcPsMode[MAX_NUM_OF_AC];        /* wme per ac power save mode */
//    EQOverflowPolicy QueueOvFlowPolicy[MAX_NUM_OF_AC];
//	uint8_t      acAckPolicy[MAX_NUM_OF_AC];               /* ack policy per AC */
//    trafficAdmCtrlInitParams_t	trafficAdmCtrlInitParams;
//	uint8_t	  desiredPsMode;						    /* The desired PS mode of the station */
//	uint8_t	  desiredMaxSpLen;
//
//    TI_BOOL      bCwFromUserEnable;  /* flag to use CwMin & CwMax user setting: 0 disable user setting (values from beacon) , 1 enable user setting (beacon cw ignore)*/
//    uint8_t     uDesireCwMin;		/**< The contention window minimum size (in slots) from ini file */
//    uint16_t    uDesireCwMax;		/**< The contention window maximum size (in slots) from ini file */
//	TI_BOOL		 bEnableBurstMode;
// /* Enable the Burst mode from ini file */
//    /* 802.11n BA session */
//    uint8_t               aBaPolicy[MAX_NUM_OF_802_1d_TAGS];	/* Both initiator and Rx BA policy */
//    uint16_t              aBaInactivityTimeout;				/* Initiator inactivity timeout */
//}QosMngrInitParams_t;
//
//
//
///*END OF MULTIPLE QUEUES STRUCTURE*/
//
//typedef struct
//{
//    TMacAddr	bssID;
//    uint16_t	channel;
//} apChannelPair_t;
//
//typedef struct
//{
//    apChannelPair_t	*apChannelPairs;
//    uint16_t      	numOfEntries;
//} neighbor_AP_t;
//
//typedef struct
//{
//    uint16_t          maxChannelDuration;		/* One channel max duration time. (time slot 0 - 65000) */
//    uint16_t          minChannelDuration;		/* One channel max duration time. (time slot 0 - 65000) */
//    uint8_t           earlyTerminationMode;	/**< 0 = Stay until max duration time. 1 = Terminate scan in
//												* a channel upon a reception of Prob-Res or Beacon. 2 = Terminate scan
//												* in a channel upon a reception of any frame
//												*/
//    uint8_t           eTMaxNumOfAPframes;		/**< number of AP frames (beacon/probe_resp) to trigger Early termination.
//												* Applicable only when EarlyTerminationMode = 1
//												*/
//    uint8_t           numOfProbeReq;			/* Number of probe request transmitted on each channel */
//
//} periodicScanParams_t;
//
//typedef struct
//{
//	TTxDataCounters 			*pTxDataCounters;
//	uint8_t				acID;
//}	reportTsStatisticsReq_t;
//
//
///* SME parameters definition */
//typedef enum
//{
//    CONNECT_MODE_AUTO = 0,
//    CONNECT_MODE_MANUAL
//} EConnectMode;
//
//typedef struct
//{
//    uint32_t       uNetIfId;           /* network interface we set the power for */
//    TI_INT8         desiredTxPower;		/* The desired Tx power inforced by the User (Utility) or OS */
//} TTxPowerParams;
//
///* Generic IE */
//#define RSN_MAX_GENERIC_IE_LENGTH 255
//
///** \struct paramInfo_t
// * \brief General Parameters Structure
// *
// * \par Description
// * This structure holds information for the regulatory domain (and other modules
// * that are outside of the scope of this document) queries
// *
// * \sa
// */
//typedef struct{
//    uint32_t              paramType;		/**< Parameter identification value */
//    uint32_t              paramLength;		/**< Parameter actual length (or the length allocated in content for parameter value) */
//    uint32_t              uNetIfId;		/**< Identification of source NetIf */
//    uint32_t              uFlags;          /**< Bit map: Bit[0] Set Cmd, Bit[1] Get Cmd, Bit[2] Alloc needed Cmd, Bit[3] STA async Cmd, Bit[4] AP async Cmd, */
//
//	/* Actual parameter value */
//    union
//    {
//        /* Role STA section */
//        TMacAddr                			    roleStaDesiredBSSID;
//        TSsid                   			    roleStaDesiredSSID;
//        TRateParam                 			    roleStaDesiredRateSetString;
//		TRateSets								roleStaDesiredRateSet;
//        uint8_t                			    roleStaCurrentTxRate;
//        uint8_t                			    roleStaCurrentRxRate;
//        EPreamble               			    roleStaDesiredPreambleType;
//        EPreamble               			    roleStaCurrentPreambleType;
//        OS_802_11_BSSID_EX                      *pRoleStaSelectedLinkInfo;
//        EDot11Mode              			    roleStaDot11Mode;
//        uint8_t                			    roleStaCurrentChannel;
//        TSsid                   			    roleStaCurrentSSID;
//		ScanBssType_e						    roleStaCurrentBSSType;
//        ESlotTime               			    roleStaSlotTime;
//        signal_t                			    roleStaCurrentSignal;
//        TIWLN_COUNTERS          			    roleStaCounters;
//        uint16_t               			    roleStaLinkCapability;
//        uint16_t               			    beaconInterval;
//        uint8_t                			    APTxPower;
//        TI_BOOL                 			    roleStaBeaconRecv;
//        uint8_t	               			    roleStaDtimPeriod;
//        TI_INT32                			    roleStaCurrentRssi;
//		uint8_t							    roleStaDesiredBeaconFilterState;
//
//        void                                    *pRoleStaCurrentLink;
//        TI_BOOL                                 bCurrentLinkHtSupport;
//
//		uint16_t								uRtsThreshold;
//
//        /* WiFI SimpleConfig */
//		TWscMode 							    roleStaWSCMode; /* used to set the WiFi Simple Config mode */
//		uint8_t							    *pProbeReqExtraIes;
//		TI_BOOL								    roleStaWpsEnabled;
//
//        /* SME SM section */
//        TMacAddr                			    smeDesiredBSSID;
//        TSsid                   			    smeDesiredSSID;
//        TI_BOOL                 			    smeRadioOn;
//        TIWLN_DOT11_STATUS      			    smeSmConnectionStatus;
//
//        /* auth SM section */
//        uint32_t               			    authResponseTimeout;
//
//        /* assoc SM section */
//        uint32_t               			    assocResponseTimeout;
//
//        OS_802_11_ASSOCIATION_INFORMATION  	    assocAssociationInformation;
//
//        /* RSN section */
//        TI_BOOL                 			    rsnPrivacyOptionImplemented;
//        EAuthSuite              			    rsnDesiredAuthType;
//        OS_802_11_KEY           			    rsnOsKey;
//        rsnAuthEncrCapability_t 			    *pRsnAuthEncrCapability;
//        uint32_t               			    rsnNoOfPMKIDs;
//        OS_802_11_PMKID         			    rsnPreAuthList;
//        uint32_t               			    rsnWPAPromoteFlags;
//        uint32_t               			    rsnWPAMixedModeSupport;
//        uint32_t               			    rsnAuthState; /* supp_1XStates */
//        TrsnEncryptionStatus            	    tRsnEncryptionStatus;
//        uint8_t                			    rsnHwEncDecrEnable; /* 0- disable, 1- enable*/
//        TSecurityKeys          				    *pRsnKey;
//        uint8_t                   			    rsnDefaultKeyID;
//
//        EExternalAuthMode      	 			    rsnExtAuthneticationMode;
//        TI_BOOL                    			    rsnMixedMode;
//		TMacAddr							    rsnApMac;
//        OS_802_11_EAP_TYPES     			    eapType;
//        TI_BOOL                    			    rsnPortStatus;
//		rsnGenericIE_t                          rsnGenericIE;
//		TI_BOOL                                 rsnExternalMode;
//
//
//        /* Rx Data section */
//        uint32_t							    rxDataExceptionsCount;
//		uint16_t                               rxGenericEthertype;
//
//        /* Tx Data section */
//        TTxDataCounters        				    *pTxDataCounters;
//        uint8_t                       		    txDataEncryptionFieldSize;
//		uint16_t                               uGenericEthertype;
//
//		/* Link Info section*/
//		TLinkDataCounters					    linkDataCounters[WLANLINKS_MAX_LINKS];
//
//        /* Ctrl Data section */
//        TI_BOOL                    			    ctrlDataPowerSaveEnable;
//        TI_BOOL                    			    ctrlDataPowerSaveForce;
//        TI_BOOL                    			    ctrlDatapowerSaveEnhanceAlgorithm;
//        TMacAddr                                ctrlDataCurrentBSSID;
//        tiwdrv_rate_e         				    ctrlDataCurrentActiveRate;
//        TMacAddr            				    ctrlDataDeviceMacAddress;
//        TStreamTrafficProperties   			    ctrlDataUpOfStream;
//		TClsfrTableEntry					    ctrlDataClsfrInsertTable;
//        EClsfrType              			    ctrlDataClsfrType;
//
//
//        connectionType_e        			    connType;
//
//        /* MLME SM section */
//        legacyAuthType_e        			    mlmeLegacyAuthType;
//        legacyAuthType_e        			    authLegacyAuthType;
//
//        TI_BOOL                    			    txDataCurrentPrivacyInvokedMode;
//        TI_BOOL 	               			    txDataEapolEncryptionStatus;
//        uint32_t                  			    txDataPollApPacketsFromACid;      /* AC to poll AP packets from */
//
//        /* regulatory Domain section */
//        regulatoryDomainParam_t 			    regulatoryDomainParam;
//        uint8_t*               			    pCountryString;
//        TI_BOOL                    			    spectrumManagementEnabled;
//        TI_BOOL                    			    regulatoryDomainEnabled;
//        uint8_t*                  			    pSupportedChannel;
//        ERadioBand                              eBand;
//        TTxPowerParams                 		    txPowerParams;		/* The desired Tx power inforced by the User (Utility),
//																	or The desired Tx power (in Dbm) as forced by teh OS */
//                                                                    /*for other extern elements that want
//																	to effect the transmit power*/
//		TpowerLevelTable_t					    powerLevelTable;
//        TI_BOOL                    			    enableDisable_802_11h;
//        /* Measurement Manager section */
//		uint32_t							    measurementEnableDisableStatus;
//		uint16_t							    measurementMaxDuration;
//		uint32_t								measurementMinTimeBetweenReqInSec;
//        TInterrogateCmdCbParams 			    interogateCmdCBParams;
//
//
//        /* soft Gemini section */
//        ESoftGeminiEnableModes				    SoftGeminiEnable;
//        uint32_t							    SoftGeminiParamArray[NUM_OF_CONFIG_PARAMS_IN_SG];
//        uint32_t							    CoexActivityParamArray[NUM_OF_COEX_ACTIVITY_PARAMS_IN_SG];
//
//		/* case CCX MODULE INCLUDED */
//		CCX_PARAM_FIELDS
//
//        /* Application Config Parameters Manager */
//		roamingMngrConfigParams_t			    roamingConfigBuffer;
//		uint32_t							    roamingTriggerType;
//		uint32_t							    roamingConnStatus;
//        bssList_t*              			    pScanBssList;
//		TScanPolicy*						    pScanPolicy;
//
//        /* Scan concnetrator application scan (periodic & one-shot) parameters */
//        TScanParams                 		    *pScanParams;
//        TPeriodicScanParams         		    *pPeriodicScanParams;
//        uint32_t                   		    uBssidListSize;
//		uint32_t                   		    uNumBssidInList;
//        OS_802_11_BSSID_LIST_EX     		    *pBssidList;
//		OS_802_11_N_RATES					    *pRateList;
//        TSsid                   			    tScanDesiredSSID;
//
//        uint32_t                               uSraThreshold;
//        TI_INT32                                nRssiThreshold;
//
//        /* QOS Manager */
//		TI_BOOL									bQosEnable;
//		EDot11Mode							    qosMngrOperationalMode;
//		uint8_t							    desiredPsMode;
//        TPsRxStreaming              		    tPsRxStreaming;
//		OS_802_11_QOS_RX_TIMEOUT_PARAMS		    rxTimeOut;
//        OS_802_11_QOS_PARAMS        		    qosOsParams;
//		OS_802_11_AC_QOS_PARAMS				    qosApQosParams;
//		uint8_t							    uBaPolicyBitmap;
//
//        /* AP Qos Capabilities */
//        OS_802_11_AP_QOS_CAPABILITIES_PARAMS    qosApCapabilities;
//
//        /* Qos current AC status */
//        OS_802_11_AC_UPSD_STATUS_PARAMS   	    qosCurrentAcStatus;
//
//        OS_802_11_QOS_DELETE_TSPEC_PARAMS       qosDelTspecRequest;
//        OS_802_11_QOS_TSPEC_PARAMS     		    qosAddTspecRequest;
//
//        OS_802_11_QOS_TSPEC_PARAMS     		    qosTspecParameters;
//
//		OS_802_11_QOS_DESIRED_PS_MODE		    qosDesiredPsMode;
//
//        /* Power Manager */
//		StationPowerSaveMode_e    			    PowerMode;
//		TPowerMgr_PowerMode   				    powerMngPowerMode;
//        PowerMgr_PowerSaveDozeMode_e            powerMngDozeMode;
//        TI_BOOL                 			    powerMgrKeepAliveEnaDis;
//
//		TIWLN_RADIO_RX_QUALITY 				    RxRadioQuality ;
//
//        /* Current BSS params - RSSI/SNR User Trigger */
//		TUserDefinedQualityTrigger 			    rssiSnrTrigger;
//
//        /* SDIO Validation Test */
//        SdioValidationTestParams_t              tSdioValidationTestParams;
//
//        /* StaCap params */
//        TI_BOOL                                 staCapRRMEnabled;
//
//
//		/* debug */
//		TDebugRegisterReq					    HwRegister;
//
//        TIpAddr    StationIP;
//
//        /* AP Role params */
//        uint8_t                                roleAPBssIndex;
//        uint8_t                                roleAPChannel;
//        uint16_t                               roleAPBeaconInterval;
//        uint8_t                                roleAPDtimPeriod;
//		TI_BOOL									roleAPWmeEnabled;
//        RoleSsidType_enum                       roleAPSsidType;
//        OS_802_11_SSID                          roleAPSsidName;
//        TRoleAPGenericCmdToFW                   tRoleAPGenericCmd;
//        tiwdrv_ap_beacon_params_t               tAPBeaconParams;
//
//        /* report */
//        /*
//         * Table which holds severity flag for every available LOG severity level.
//		 * This flag indicates for each severity - whether it is enabled for Logging or not.
//		 * User can Set/Get this Tabel
//		 */
//        uint8_t    						    aSeverityTable[8/*REPORT_SEVERITY_MAX*/];
//        /*
//         * Table which holds file flag for every available LOG file.
//		 * This flag indicates for each file - whether it is enabled for Logging or not.
//		 * User can Set/Get this Tabel
//		 */
//        uint8_t    						    aFileEnable[144/*REPORT_FILES_NUM*/];
//        /* Used by user for Indicating if Debug Module should be enabled/disabled  */
//        uint32_t   						    uReportPPMode;
//
//        uint32_t   						    uActiveRoles;
//
//		/* event registration */
//        tiwdrv_event_register_params_t          tRegistrationParams;
//
//        tiwdrv_if_mode_e                        eIfMode;
//        tiwdrv_gen_ies_t					    tGenIes;
//        tiwdrv_p2p_search_params_t              tP2PSearchParams;
//        uint32_t                               uP2PReportProbeReq;
//        tiwdrv_p2p_remain_on_ch_params_t        tRemainOnChParams;
//		uint8_t                                apParam[MAX_AP_PARAM_LENGTH];
//
//		/* FW Information */
//        TFwInfo             					tFwInfo;
//
//		/*  Holds the enable role command buffer (role type + TLV buff)  */
//		uint8_t                                *pEnableRoleBuff;
//
//        uint8_t                                mlme_extra_ies[800];
//
//        TGroupAddressTable                      tGroupAddressTable;
//        TDriverRoleCaps_t tRolesCaps;
//
//        ACXsimulationConfig_t                   TxRxSimCfg;
//        tiwdrv_if_mode_e                        tiwdrvIfMode;
//        tiwdrv_plt_mode_e                       ePltMode;
//
//		tiwdrv_ap_chan_hw_info_t				hwChannelInfo;
//    } content;
//}paramInfo_t;
//
//
//
//
///*-----------------------------------------------------*/
///*      EEPROM-less support                            */
///*-----------------------------------------------------*/
//#define MAX_CALL_DATA_REG_NUM                30
//#define HW_EEPROM_PRESENTED                  1
//#define HW_EEPROM_NOT_PRESENTED              0
//
//typedef struct
//{
//    uint16_t  RegAddress;
//    uint16_t  RegValue;
//
//} PhyRegisters_t;
//
//
//typedef enum
//{
//    PS_MODE_ELP         = 0,
//    PS_MODE_POWER_DOWN  = 1,
//    PS_MODE_ACTIVE      = 2,
//    PS_MODE_WAKE_TNET   = 3
//} powerSaveModes_e;
//
//
///**************************** Beginning of Init Params ************************************/
//
//
//typedef struct
//{
//    uint8_t                   siteMgr_radioRxLevel[RX_LEVEL_TABLE_SIZE];
//    uint8_t                   siteMgr_radioLNA[RX_LEVEL_TABLE_SIZE];
//    uint8_t                   siteMgr_radioRSSI[RX_LEVEL_TABLE_SIZE];
//    uint32_t                  factorRSSI; /* for RADIA only */
//}radioValues_t;
//
//typedef struct
//{
//    ERadioBand  eBand;
//    uint8_t    uChannel;
//} TSmeScanChannel;
//
//typedef struct
//{
//    TSsid           tDesiredSsid;
//    TMacAddr        tDesiredBssid;
//    EConnectMode    eConnectMode;
//    TI_BOOL         bProbeBeforeConnect;
//} TSmeModifiedInitParams;
//
//typedef struct
//{
//    uint32_t       uMinScanDuration;
//    uint32_t       uMaxScanDuration;
//    uint32_t       uProbeReqNum;
//    TI_INT8         iSnrThreshold;
//    TI_INT8         iRssiThreshold;
//    uint32_t       uCycleNum;
//    uint32_t       uChannelNum;
//    uint8_t		aScanGChannelList[PERIODIC_SCAN_MAX_CHANNEL_NUM];
//    uint8_t		aScanAChannelList[PERIODIC_SCAN_MAX_CHANNEL_NUM];
//} TSmeInitParams;
//
//typedef struct
//{
//    TI_BOOL  RoamingScanning_2_4G_enable;
//	uint8_t RoamingOperationalMode;
//    uint8_t bSendTspecInReassPkt;
//}   TRoamScanMngrInitParams;
//
//typedef struct
//{
//	uint32_t                  authResponseTimeout;
//    uint32_t                  authMaxRetryCount;
//	uint32_t                  assocResponseTimeout;
//    uint32_t                  assocMaxRetryCount;
//    uint16_t                  uListenInterval;
//} TMlmeInitParams;
//
//
//typedef struct
//{
//    uint8_t                   parseWSCInBeacons;
//} TMlmeParserInitParams;
//
//typedef struct
//{
//    uint32_t                  connSelfTimeout;
//} connInitParams_t;
//
//
//typedef struct
//{
//	uint8_t				highRateThreshold;
//	uint8_t				lowRateThreshold;
//	TI_BOOL				    enableEvent;
//}tspecsRateParameters_t;
//
//typedef struct
//{
//    TI_BOOL                    ctrlDataPowerSaveEnhanceAlgorithm;
//    uint16_t                  ctrlDataPowerSaveTimeOut;
//    uint8_t                   ctrlDataPowerSaveTxThreshold;
//    uint8_t                   ctrlDataPowerSaveRxThreshold;
//
//}powerSaveInitParams_t;
//
//
//typedef struct
//{
//    TI_BOOL                         ctrlDataPowerSaveEnable;
//    TI_BOOL                         ctrlDataSoftGeminiEnable;
//    powerSaveInitParams_t           powerSaveInitParams;
//} ctrlDataInitParams_t;
//
//typedef struct
//{
//    uint8_t                        uLongRetryLimit;
//	uint8_t                        uShortRetryLimit;
//
//	uint32_t		                uAcPolicyEnabledRates[MAX_NUM_OF_AC];
//    uint32_t		                uMgmtPolicyEnabledRates;
//
//} TRatePoliciesInitParams;
//
//
//
///* Tx Data resources */
#define MAX_NUM_OF_AC_PARAMOUT 4
typedef struct
{
	uint32_t uMinGuarantee_PerAc[MAX_NUM_OF_AC_PARAMOUT];
	uint32_t uMinGuarantee_PerLink;
} TTxDataResourcesParams_t;

typedef struct
{
    /* TxDataQueue Parameters */
    uint32_t                    TxSendPaceTimeoutMsec;
    uint32_t                    TxSendPaceThresh;
    TClsfrInitParams            ClsfrInitParam;
    TTxDataResourcesParams_t    tDataRsrcParam;
} TUdataInitParams;
//
//
//typedef enum
//{
//    RADIO_B_G_INDEX = 0,
//    RADIO_A_B_G_INDEX = 1,
//    NUM_OF_RADIO_TYPES = 2
//} regulatoryDomain_radioIndexType_e;
//
///* Regulatory Domain module init parameters */
//typedef struct
//{
//    uint8_t            desiredTxPower;
//	uint8_t            uTemporaryTxPower;
//	uint8_t			japanChannelsEnabled;
//} regulatoryDomainInitParams_t;
//
//#ifdef CCX_MODULE_INCLUDED
//typedef enum
//{
//    CCX_MODE_DISABLED,
//    CCX_MODE_ENABLED,
//    CCX_MODE_STANDBY
//} ccxMngr_mode_t;
//
//typedef struct
//{
//    ccxMngr_mode_t  ccxEnabled;
//} ccxMngrParams_t;
//#endif /* CCX_MODULE_INCLUDED */
//
///* Measurement module init parameters */
//typedef struct
//{
//    uint16_t           maxDurationOnNonServingChannel;
//    uint32_t		    measurementMinTimeBetweenReqInSec;
//#ifdef CCX_MODULE_INCLUDED
//    ccxMngr_mode_t      ccxEnabled;
//    TI_BOOL				measureOnlyServingChannel;
//#endif /* CCX_MODULE_INCLUDED */
//    TI_BOOL             rrmEnabled;
//} measurementInitParams_t;
//
///* Switch Channel Module module init parameters */
//typedef struct
//{
//    TI_BOOL              dot11SpectrumManagementRequired;
//
//} SwitchChannelInitParams_t;
//
//typedef struct
//{
//  uint32_t       qosClassifierTable[MAX_NUM_OF_802_1d_TAGS];
//}
//clsfrParams_t;
//
//
//typedef struct
//{
//    StationPowerSaveMode_e         powerMode;
//    uint32_t                      beaconReceiveTime;
//    uint8_t                       hangoverPeriod;
//    uint8_t                       beaconListenInterval;
//    uint8_t				       dtimListenInterval;
//    uint8_t                       nConsecutiveBeaconsMissed;
//    uint8_t                       HwPsPollResponseTimeout;
//    PowerMgr_PowerSaveDozeMode_e   powerSaveDozeMode;
//
//	/* powerMgmtConfig IE */
//    uint8_t						mode;
//    uint8_t						hangOverPeriod;
//    uint16_t						NullPktRateModulation;
//
//	/* PMConfigStruct */
//	uint32_t						ELPEnable;			/* based on "elpType" */
//	uint32_t						WakeOnGPIOenable;	/* based on "hwPlatformType" */
//	uint32_t						BaseBandWakeUpTime;	/* BBWakeUpTime */
//	uint32_t						PLLlockTime;
//
//	/* ACXWakeUpCondition */
//    uint8_t						listenInterval;
//    /* BET */
//    uint32_t  						MaximalFullBeaconReceptionInterval; /* maximal time between full beacon reception */
//    uint8_t   						BetEnable;
//    uint8_t   						MaximumConsecutiveET;
//
//	TI_BOOL							reAuthActivePriority;
//    uint16_t                       psTimeOut;
//}PowerMgrInitParams_t;
//
//
//typedef struct
//{
//	uint8_t  FullRecoveryEnable;
//	TI_BOOL   recoveryTriggerEnabled[ MAX_FAILURE_EVENTS ];
//} healthMonitorInitParams_t;
//
//typedef struct
//{
//    TI_BOOL   ignoreDeauthReason0;
//} apConnParams_t;
//
//typedef struct
//{
//    uint32_t       uDfsPassiveDwellTimeMs;
//    TI_BOOL	        bPushMode; /*  True means Push mode. False is the default mode, storing scan results in table. */
//    uint32_t       uSraThreshold;
//    TI_INT32        nRssiThreshold;
//	uint32_t       numberOfNoScanCompleteToRecovery;
//} TScanCncnInitParams;
//
//typedef struct
//{
//    uint8_t       uNullDataKeepAlivePeriod;
//    uint8_t	   RoamingOperationalMode;
//} TCurrBssInitParams;
//
//typedef struct
//{
//    uint32_t       uWlanDrvThreadPriority; /* Default setting of the WLAN driver task priority  */
//    uint32_t       uBusDrvThreadPriority;  /* Default setting of the bus driver thread priority */
//}TDrvMainParams;
//
//
//typedef struct
//{
//	TI_BOOL 	bRadioOn;
//    TDriverRoleCaps_t tRolesCaps;
//} TRolesMngrInitParams;
//
//typedef enum {
//	DEDICATED_FEM_NONE = 0x0,
//	DEDICATED_FEM_VENDOR_1 = 0x1,
//	DEDICATED_FEM_VENDOR_2 = 0x2,
//	DEDICATED_FEM_VENDOR_3 = 0x3
//}dedicated_fem_e;
//
//typedef enum
//{
//	LOW_BAND_COMPONENT_NO_SWITCH = 0x0,
//	LOW_BAND_COMPONENT_2_WAY_SWITCH = 0x1,
//	LOW_BAND_COMPONENT_3_WAY_SWITCH = 0x2,
//	LOW_BAND_COMPONENT_MACTCHING = 0x3
//}low_band_component_e;
//
//typedef enum
//{
//	HIGH_BAND_COMPONENT_NO_SWITCH = 0x0,
//	HIGH_BAND_COMPONENT_2_WAY_SWITCH = 0x1
//}high_band_component_e;
//
//typedef enum
//{
//	HW_BOARD_TYPE_EVB_18XX  = 0,
//	HW_BOARD_TYPE_DVP_18XX  = 1,
//	HW_BOARD_TYPE_HDK_18XX  = 2,
//	HW_BOARD_TYPE_FPGA_18XX = 3,
//	HW_BOARD_TYPE_COM8_18XX = 4,
//}board_type_e;
//
//
//typedef struct
//{
//	uint8_t                        uBeaconTxTimeout;	/* in msec */
//    EDot11Mode	                    eDesiredDot11Mode;
//    TArpIpFilterInitParams          tArpIpFilter;
//    TMacAddrFilterInitParams        tMacAddrFilter;
//
//    uint8_t		        		aBaPolicy[MAX_NUM_OF_802_1d_TAGS]; 			/* Both initiator and Rx BA policy */
//    uint16_t       				aBaInactivityTimeout;	 					/* Initiator inactivity timeout */
//    uint16_t                       uRtsThreshold;
//
//    RssiSnrAverageWeights_t         tWeightsParam;
//
//    TRxTimeOut                      tRxTimeOut;
//
//}TRoleApInitParams;
//
//typedef struct
//{
//	TSsid	                        tDesiredSsid;
//	EDot11Mode	                    eDesiredDot11Mode;
//    ERadioBand             			eSupportedRadioBand;
//    EDraftNumber					eDraftNum;
//
//    EPreamble               		eDesiredPreambleType;
//    ESlotTime               		eDesiredSlotTime;
//
//	/* TX Power Control parameters */
//    uint32_t                  		uTxPowerControlOn;
//    TI_INT32                   		iTxPowerRssiThresh;
//    TI_INT32                   		iTxPowerRssiRestoreThresh;
//
//    TBeaconFilterInitParams			tBeaconFilterInitParams;
//
//    TArpIpFilterInitParams          tArpIpFilter;
//    TMacAddrFilterInitParams        tMacAddrFilter;
//
//	TI_BOOL	                        bIncludeWscInProbeReq;
//
//    /* Role Station rate sets as configured by default or by application*/
//    TRateSets                       tStaRates;
//    uint16_t                       uRtsThreshold;
//
//    TBcnBrcOptions                  tBcnBrcOptions;
//    uint8_t       					uConsecutivePsPollDeliveryFailureThreshold;
//
//    RssiSnrAverageWeights_t         tWeightsParam;
//}TRoleStaInitParams;
//
//typedef struct
//{
//    EAuthSuite          authSuite;
//    TI_BOOL             privacyOn;
//    TI_BOOL             mixedMode;
//    TI_BOOL             WPAMixedModeEnable;
//    TI_BOOL             preAuthSupport;
//    uint32_t           preAuthTimeout;
//    TI_BOOL             bPairwiseMicFailureFilter;
//
//} TRsnInitParams;

// Taken from TWDriver.h
typedef enum
{
    PREAMBLE_LONG           = 0,    /**< Preamble type Long             */
    PREAMBLE_SHORT          = 1,    /**< Preamble type Short            */

    PREAMBLE_UNSPECIFIED    = 0xFF  /**< Preamble type Not Specified    */

} EPreamble;



#endif /* __PARAM_OUT_H__ */

