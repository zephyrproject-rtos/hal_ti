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
/**********************************************************************************************************************

  FILENAME:       cc3xxx_public_infoele.h

  DESCRIPTION:    Contains information element defines/structures used by the FW and host.



***********************************************************************************************************************/
#ifndef PUBLIC_INFOELE_H
#define PUBLIC_INFOELE_H


#include "cc3xxx_public_types.h"

#define NOISE_HIST_LEN 8

typedef struct
{
    uint16_t id;
    uint16_t len;
} EleHdrStruct;


#ifdef HOST_COMPILE
#define INFO_ELE_HDR    EleHdrStruct    EleHdr;
#else
#define INFO_ELE_HDR
#endif
/******************************************************************************

    Name:   ACX_WAKE_UP_CONDITIONS
    Type:   Configuration
    Access: Write Only
    Length: 2

******************************************************************************/
typedef enum
{
    WAKE_UP_EVENT_BEACON_BITMAP     = 0x01, /* Wake on every Beacon*/
    WAKE_UP_EVENT_DTIM_BITMAP       = 0x02, /* Wake on every DTIM*/
    WAKE_UP_EVENT_N_DTIM_BITMAP     = 0x04, /* Wake on every Nth DTIM (Listen interval)*/
    WAKE_UP_EVENT_MAX               = WAKE_UP_EVENT_N_DTIM_BITMAP,
    //not supported
    //WAKE_UP_EVENT_N_BEACONS_BITMAP  = 0x08, /* Wake on every Nth Beacon (Nx Beacon)*/
    WAKE_UP_EVENT_BITS_MASK         = 0x0F
} WakeUpEventBitMask_e;

typedef struct
{
                                    /* Offset Size */
    INFO_ELE_HDR                    /*      0    4 */
    CMD_PARAMS_HOST_ROLE_DEFINITION /*      4    1  - host RoleID */
    uint8_t  wakeUpConditionBitmap;   /*      5    1  - The host can set one bit only. */
                                    /*                WakeUpEventBitMask_e describes the Possible */
                                    /*                Wakeup configuration bits*/

    uint8_t  listenInterval;          /*      6    1  - 0 for Beacon and Dtim, */
                                    /*                xDtims (1-10) for Listen Interval and */
                                    /*                xBeacons (1-255) for NxBeacon*/
    uint8_t  padding[1];              /*      7    1  - alignment to 32bits boundry   */
}WakeUpCondition_t;


/******************************************************************************

    Name:   ACX_MEM_CFG
    Type:   Configuration
    Access: Write Only
    Length: 12

******************************************************************************/

typedef struct
{
    INFO_ELE_HDR
    uint8_t   rxMemblockNumber;           /* specifies the number of memory buffers that */
                                        /* is allocated to the Rx memory pool. The */
                                        /* actual number allocated may be less than*/
                                        /* this number if there are not enough memory */
                                        /* blocks left over for the Minimum Number of */
                                        /* Tx Blocks. Returns the actual number of RX */
                                        /* buffers allocated in the memory map*/

    uint8_t   txMinimumMemblockNumber;    /* specifies the minimum number of blocks that */
                                        /* must be allocated to the TX pool. Follows */
                                        /* this limit even if the Number of Rx Memory */
                                        /* Blocks parameter is ignored.*/

    uint8_t   numStations;                /* The number of STAs supported in IBSS mode. */
                                        /* The FW uses this field to allocate memory */
                                        /* for STA context data such as security keys*/

    uint8_t   numSsidProfiles;            /* The number of SSID profiles used in IBSS mode */
                                        /* Enables different profiles for different STAs */

    uint32_t  totalTxDescriptors;         /* Total TX Descriptors - in the past it was configured per AC */

    uint8_t    dynMemEnable;              /* 0 - not supported */

    uint8_t    txFreeReq;                 /*minimum required free memory blocks in TX pool*/

    uint8_t    rxFreeReq;                 /*minimum required free memory blocks in TX pool*/

    uint8_t    txMin;                     /*minimum required total TX memory blocks in TX pool*/
    uint8_t   loggerFreeReq;              /*minimum required free memory blocks in FW Logger pool, 0 for disable feature*/

    uint8_t   reserved[3];                /* DWORD alignment padding */
} ACXConfigMemory_t;


/******************************************************************************

    Name:   ACX_SLOT
    Type:   Configuration
    Access: Write Only
    Length: 8

******************************************************************************/



typedef struct
{
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION     /* host RoleID */
    uint8_t      woneIndex;               /* reserved*/

    uint8_t/*SlotTime_e*/ slotTime;                /* The slot size to be used. refer to SlotTime_enum.    */
    uint8_t      reserved[5];
} ACXSlot_t;


/******************************************************************************

    Name:   ACX_MEM_MAP
    Type:   Configuration
    Access: Read Only
    Length: 72
    Note:   Except for the numTxMemBlks, numRxMemBlks fields, this is
            used in MASTER mode only!!!
    
******************************************************************************/
#define MEM_MAP_NUM_FIELDS  24

typedef struct 
{
    uint32_t *controlBlock; /* array of two 32-bit entries in the following order:
                            1. Tx-Result entries counter written by the FW
                            2. Tx-Result entries counter read by the host */
    void   *txResultQueueStart; /* points t first descriptor in TRQ */
} TxResultPointers_t;


/******************************************************************************

    Name:   ACX_AID
    Type:   Configuration
    Access: Write Only
    Length: 2
    
******************************************************************************/

typedef struct
{
                                    /* Offset Size */
    INFO_ELE_HDR                    /*      0    4 */
    CMD_PARAMS_HOST_ROLE_DEFINITION /*      4    1 - host RoleID */
    uint8_t  reserved;                /*      5    1 - alignment to 32bits boundary   */
    uint16_t  Aid;                    /*      6    2 - The Association ID to the WiLink. The WiLink uses this */
                    /* field to determine when the STA's AID bit is set in a */
                    /* received beacon and when a PS Poll frame should be */
                    /* transmitted to the AP. The host configures this information */
                    /* element after it has associated with an AP. This information */
                    /* element does not need to be set in Ad Hoc mode.*/
} ACXAid_t;


/******************************************************************************

    Name:   ACX_ERROR_CNT
    Type:   Operation
    Access: Read Only
    Length: 12
    
******************************************************************************/
typedef struct
{
    INFO_ELE_HDR
    uint32_t PLCPErrorCount;  /* The number of PLCP errors since the last time this */
                            /* information element was interrogated. This field is */
                            /* automatically cleared when it is interrogated.*/
    
    uint32_t FCSErrorCount;   /* The number of FCS errors since the last time this */
                            /* information element was interrogated. This field is */
                            /* automatically cleared when it is interrogated.*/
    
    uint32_t validFrameCount; /* The number of MPDUs without PLCP header errors received*/
                            /* since the last time this information element was interrogated. */
                            /* This field is automatically cleared when it is interrogated.*/

    uint32_t seqNumMissCount; /* the number of missed sequence numbers in the squentially */
                            /* values of frames seq numbers */

} ACXErrorCounters_t;

/******************************************************************************

    Name:   ACX_MEDIUM_USAGE
    Type:   Configuration
    Access: Read Only
    Length: 8

******************************************************************************/

typedef struct
{
    INFO_ELE_HDR
    uint32_t mediumUsage; /* report to the host the value of medium usage registers*/
    uint32_t period;      /* report to the host the value of medium period registers*/
} ACXMediumUsage_t;


/******************************************************************************

    Name:   ACX_BEACON_FILTER_OPT
    Desc:   This information element enables the host to activate beacon filtering. 
            The filter can only be activated when the STA is in PS mode. 
            When activated, either the host is not notified about beacons whose 
            unicast TIM bit is not set, or these beacons are buffered first and 
            the host is notified only after the buffer reaches a predetermined size.
            The host should not activate the filter if it configures the firmware 
            to listen to broadcasts (see the VBM Options field in the 
            ACXPowerMgmtOptions information element). The filter only affects beacons, 
            and not other MSDUs - the firmware notifies the host immediately about 
            their arrival.
    Type:   Filtering Configuration
    Access: Write Only
    Length: 2
 
******************************************************************************/
typedef struct  
{
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION/* host RoleID */
    uint8_t   enable;                /* Indicates whether the filter is enabled. */
                                   /* 1 - enabled, 0 - disabled. */
    uint8_t   maxNumOfBeaconsStored; /* The number of beacons without the unicast TIM */
                                   /* bit set that the firmware buffers before */
                                   /* signaling the host about ready frames. */
                                   /* When set to 0 and the filter is enabled, beacons */
                                   /* without the unicast TIM bit set are dropped.*/
    uint8_t  padding[1];             /* alignment to 32bits boundry   */
} ACXBeaconFilterOptions_t;


/******************************************************************************

    Name:   ACX_BEACON_FILTER_TABLE
    Desc:   This information element configures beacon filtering handling for the
            set of information elements. An information element in a beacon can be 
            set to be: ignored (never compared, and changes will not cause beacon 
            transfer), checked (compared, and transferred in case of a change), or 
            transferred (transferred to the host for each appearance or disappearance).
            The table contains all information elements that are subject to monitoring 
            for host transfer. 
            All information elements that are not in the table should be ignored for 
            monitoring.
            This functionality is only enabled when beacon filtering is enabled by 
            ACX_BEACON_FILTER_OPT.
    Type:   Filtering Configuration
    Access: Write Only
    Length: 101
    Notes:  the field measuring the value of received beacons for which the device 
            wakes up the host in ACX_BEACON_FILTER_OPT does not affect 
            this information element.
    
******************************************************************************/

/*
    ACXBeaconFilterEntry (not 221)
    Byte Offset     Size (Bytes)    Definition 
    ===========     ============    ==========
    0               1               IE identifier
    1               1               Treatment bit mask

    ACXBeaconFilterEntry (221)
    Byte Offset     Size (Bytes)    Definition 
    ===========     ============    ==========
    0               1               IE identifier
    1               1               Treatment bit mask
    2               3               OUI
    5               1               Type
    6               2               Version


    Treatment bit mask - The information element handling:
                         bit 0 - The information element is compared and transferred
                                 in case of change.
                         bit 1 - The information element is transferred to the host 
                                 with each appearance or disappearance.
                         Note that both bits can be set at the same time.
*/
#define BEACON_FILTER_TABLE_MAX_IE_NUM                      (32)
#define BEACON_FILTER_TABLE_MAX_VENDOR_SPECIFIC_IE_NUM      (6)
#define BEACON_FILTER_TABLE_IE_ENTRY_SIZE                   (2)
#define BEACON_FILTER_TABLE_EXTRA_VENDOR_SPECIFIC_IE_SIZE   (6)
#define BEACON_FILTER_TABLE_MAX_SIZE    ((BEACON_FILTER_TABLE_MAX_IE_NUM * BEACON_FILTER_TABLE_IE_ENTRY_SIZE) + \
                                         (BEACON_FILTER_TABLE_MAX_VENDOR_SPECIFIC_IE_NUM * BEACON_FILTER_TABLE_EXTRA_VENDOR_SPECIFIC_IE_SIZE))

typedef struct ACXBeaconFilterIETableStruct {
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION             /* host RoleID */
    uint8_t NumberOfIEs;                          /* The number of IE's in the table*/
                                                /* 0 - clears the table.*/

    uint8_t padding[2];  /* alignment to 32bits boundry   */
    uint8_t IETable[BEACON_FILTER_TABLE_MAX_SIZE];
} ACXBeaconFilterIETable_t;

/******************************************************************************

    Name:   ACX_COEX_ACTIVITY_TABLE
    
******************************************************************************/

typedef enum
{
    COEX_IP_BT = 0,
    COEX_IP_WLAN, 
    COEX_IP_DUAL_MODE,   /* That define isn't valid value in DR&FW interface and use just in the FW */
    MAX_COEX_IP
} CoexIp_enum;

#ifdef HOST_COMPILE
typedef uint8_t CoexIp_e;
#else
typedef CoexIp_enum CoexIp_e;
#endif

typedef struct ACXCoexActivityIEStruct {
    INFO_ELE_HDR
    CoexIp_e coexIp;         /* 0-BT, 1-WLAN (according to CoexIp_e in FW) */
    uint8_t  activityId;       /* According to BT/WLAN activity numbering in FW */ 
    uint8_t  defaultPriority;  /* 0-255, activity default priority */
    uint8_t  raisedPriority;   /* 0-255, activity raised priority */
    uint16_t minService;       /* 0-65535, The minimum service requested either in
                                requests or in milliseconds depending on activity ID */
    uint16_t maxService;       /* 0-65535, The maximum service allowed either in
                            requests or in milliseconds depending on activity ID */
} ACXCoexActivityIE_t;

/******************************************************************************

    Name:   ACX_ARP_IP_FILTER 
    Type:   Filtering Configuration
    Access: Write Only
    Length: 20

******************************************************************************/

#define ARP_FILTER_DISABLED                    (0)
#define ARP_FILTER_ENABLED                  (0x01)
#define ARP_FILTER_AUTO_ARP_ENABLED         (0x02)

#define ARP_FILTER_SUSPENDED_BY_FW          (0x80)      // Bit set/cleared by FW to indicate temporary suspention of Auto-ARP 
                                                        // (due to join, before template is configured)
                                                        // This is NEVER used by the Host itself

#define ARP_FILTER_HOST_ENABLE_MASK         (0x03)      // Take only two lower bits of host configuration

typedef struct  
{    
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION /* host RoleID */
    uint8_t     ipVersion;            /* The IP version of the IP address: 4 - IPv4, 6 - IPv6.*/
    uint8_t     arpFilterEnable;      /* BITMAP (!) field containing all "enabled" ARP features */
                                    /* 0x00 - No ARP features */
                                    /* 0x01 - Only ARP filtering */
                                    /* 0x02 - Same as 3: Both ARP filtering and Auto-ARP (kept for backwards compatibility) */
                                    /* 0x03 - Both ARP filtering and Auto-ARP */
    uint8_t     padding[1];           /* alignment to 32bits boundry   */
    uint8_t     address[16];          /* The IP address used to filter ARP packets. ARP packets */
                                    /* that do not match this address are dropped. */
                                    /* When the IP Version is 4, the last 12 bytes of */
                                    /* the address are ignored.*/
} ACXConfigureIP_t;


/******************************************************************************

  Name:     ACX_IBSS_FILTER
  Type:     Filtering Configuration
  Access:   Write Only
  Length:   1
  
******************************************************************************/
typedef struct  
{
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION /* host RoleID */
    uint8_t   enable;                 /* if set (i.e. IBSS mode), forward beacons from the same SSID*/
                                    /* (also from different BSSID), with bigger TSF then the this of */
                                    /* the current BSS.*/
    uint8_t   padding[2];             /* alignment to 32bits boundry   */
} ACXIBSSFilterOptions_t;


/******************************************************************************

  Name:     ACX_SERVICE_PERIOD_TIMEOUT
  Type:     Configuration
  Access:   Write Only
  Length:   1
  
******************************************************************************/
typedef struct 
{    
                                    /* Offset Size */
    INFO_ELE_HDR                    /*      0    4 */
    CMD_PARAMS_HOST_ROLE_DEFINITION /*      4    1 - host RoleID */
    uint8_t  Reserved;                /*      5    1 */
    uint16_t PsPollTimeout;           /*      6    2 - the maximum time that the device will wait to receive */
                                                    /* traffic from the AP after transmission of PS-poll.*/
    
    uint16_t UpsdTimeout;             /*      8    2 - the maximum time that the device will wait to receive */
                                                    /* traffic from the AP after transmission from UPSD enabled*/
                                                    /* queue.*/
    uint8_t  Padding[2];              /*      10   2 - 32-bit align */
} ACXRxTimeout_t;

/******************************************************************************

    Name:   ACX_TX_QUEUE_CFG
    Type:   Configuration
    Access: Write Only
    Length: 8
    
******************************************************************************/
typedef struct
{
    INFO_ELE_HDR
    uint8_t   qID;                        /* The TX queue ID number.*/
    uint8_t   padding[3];                 /* alignment to 32bits boundry   */
    uint16_t  numberOfBlockHighThreshold; /* The maximum memory blocks allowed in the */
                                        /* queue.*/
    uint16_t  numberOfBlockLowThreshold;  /* The minimum memory blocks that are */
                                        /* guaranteed for this queue.*/
} ACXTxQueueCfg_t;


/******************************************************************************

    Name:   ACX_STATISTICS
    Type:   Statistics
    Access: Write Only
    Length: 
    Note:   Debug API

******************************************************************************/
typedef struct 
{
    uint32_t  debug1;
    uint32_t  debug2;
    uint32_t  debug3;
    uint32_t  debug4;
    uint32_t  debug5;
    uint32_t  debug6;
}DbgStatistics_t;

typedef struct
{
    uint32_t IRQs;              /* irqisr() */
} IsrStatistics_t;

#define PWR_STAT_MAX_CONT_MISSED_BCNS_SPREAD 10
typedef struct PwrStatistics_t
{
    uint32_t MissingBcnsCnt;      /* Count the amount of missing beacon interrupts to the host.*/
    uint32_t RcvdBeaconsCnt;      /* Count the number of received beacons.*/
    uint32_t ConnectionOutOfSync;         /* Count the number of times TSF Out Of Sync occures, meaning we lost more consecutive beacons that defined by the host's threshold.*/
    uint32_t ContMissBcnsSpread[PWR_STAT_MAX_CONT_MISSED_BCNS_SPREAD];  /* Gives statistics about the spread continuous missed beacons.*/
                                    /* The 16 LSB are dedicated for the PS mode.*/
                                    /* The 16 MSB are dedicated for the PS mode.*/
                                    /* ContMissBcnsSpread[0] - single missed beacon.*/
                                    /* ContMissBcnsSpread[1] - two continuous missed beacons.*/
                                    /* ContMissBcnsSpread[2] - three continuous missed beacons.*/
                                    /* ...*/
                                    /* ContMissBcnsSpread[9] - ten and more continuous missed beacons.*/
    uint32_t RcvdAwakeBeaconsCnt; /* Count the number of beacons in awake mode.*/
} PwrStatistics_t;

typedef struct PsPollUpsdStatistics_t
{
    uint32_t psPollTimeOuts;
    uint32_t upsdTimeOuts;
    uint32_t upsdMaxAPturn;
    uint32_t psPollMaxAPturn;
    uint32_t psPollUtilization;
    uint32_t upsdUtilization;
} PsPollUpsdStatistics_t;

typedef struct 
{
    uint32_t  numOfTxProcs;
    uint32_t  numOfPreparedDescs;
    uint32_t  numOfTxXfr;
    uint32_t  numOfTxDma;    
    uint32_t  numOfTxCmplt;
    uint32_t  numOfRxProcs;
    uint32_t  numOfRxData;
}RingStatistics_t;

typedef struct
{
    uint32_t numOfTxTemplatePrepared;
    uint32_t numOfTxDataPrepared;
    uint32_t numOfTxTemplateProgrammed;
    uint32_t numOfTxDataProgrammed;
    uint32_t numOfTxBurstProgrammed;
    uint32_t numOfTxStarts;
    uint32_t numOfTxImmResp;
    uint32_t numOfTxStartTempaltes;
    uint32_t numOfTxStartIntTemplate;
    uint32_t numOfTxStartFwGen;
    uint32_t numOfTxStartData;
    uint32_t numOfTxStartNullFrame;
    uint32_t numOfTxExch;
    uint32_t numOfTxRetryTemplate;
    uint32_t numOfTxRetryData;
    uint32_t numOfTxExchPending;
    uint32_t numOfTxExchExpiry;
    uint32_t numOfTxExchMismatch;
    uint32_t numOfTxDoneTemplate;
    uint32_t numOfTxDoneData;
    uint32_t numOfTxDoneIntTemplate;
    uint32_t numOfTxPreXfr;
    uint32_t numOfTxXfr;
    uint32_t numOfTxXfrOutOfMem;
    uint32_t numOfTxDmaProgrammed;
    uint32_t numOfTxDmaDone;
} TxStatistics_t;


typedef struct
{
    uint32_t RxOutOfMem;
    uint32_t RxHdrOverflow;
    uint32_t RxHWStuck;
    uint32_t RxDroppedFrame;
    uint32_t RxCompleteDroppedFrame;
    uint32_t RxAllocFrame;
    uint32_t RxDoneQueue;
    uint32_t RxDone;
    uint32_t RxDefrag;
    uint32_t RxDefragEnd;
    uint32_t RxMic;
    uint32_t RxMicEnd;
    uint32_t RxXfr;
    uint32_t RxXfrEnd;
    uint32_t RxCmplt;
    uint32_t RxPreCmplt;
    uint32_t RxCmpltTask;
    uint32_t RxPhyHdr;
    uint32_t RxTimeout;
} RxStatistics_t;


typedef struct
{
    uint32_t RxDMAErrors;
    uint32_t TxDMAErrors;
} DMAStatistics_t;

typedef struct WepStatistics_t
{
    uint32_t WepAddrKeyCount;      /* Count of WEP address keys configured*/
    uint32_t WepDefaultKeyCount;   /* Count of default keys configured*/
    uint32_t WepKeyNotFound;       /* count of number of times that WEP key not found on lookup*/
    uint32_t WepDecryptFail;       /* count of number of times that WEP key decryption failed*/
    uint32_t WepEncryptFail;       /* count of number of times that WEP key encryption failed*/
    uint32_t WepDecPackets;        /* WEP Packets Decrypted*/
    uint32_t WepDecInterrupt;      /* WEP Decrypt Interrupts*/
    uint32_t WepEnPackets;         /* WEP Packets Encrypted*/
    uint32_t WepEnInterrupt;       /* WEP Encrypt Interrupts*/
} WepStatistics_t;

typedef struct MicStatistics_t
{
    uint32_t MicRxPkts;
    uint32_t MicCalcFailure;
} MicStatistics_t;


typedef struct AesStatisticsStruct
{
    uint32_t AesEncryptFail;
    uint32_t AesDecryptFail;
    uint32_t AesEncryptPackets;
    uint32_t AesDecryptPackets;
    uint32_t AesEncryptInterrupt;
    uint32_t AesDecryptInterrupt;
} AesStatistics_t;

typedef struct GemStatisticsStruct
{
    uint32_t GemEncryptFail;
    uint32_t GemDecryptFail;
    uint32_t GemEncryptPackets;
    uint32_t GemDecryptPackets;
    uint32_t GemEncryptInterrupt;
    uint32_t GemDecryptInterrupt;
} GemStatistics_t;

typedef struct EventStatistics_t
{
    uint32_t calibration;
    uint32_t rxMismatch;
    uint32_t rxMemEmpty;
} EventStatistics_t;

typedef struct RxFilterStatistics_t
{
    uint32_t beaconFilter;
    uint32_t arpFilter;
    uint32_t MCFilter;
    uint32_t dupFilter;
    uint32_t dataFilter;
    uint32_t ibssFilter;
    uint32_t protectionFilter;
} RxFilterStatistics_t;

typedef struct ClaibrationFailStatistics_t
{
    uint32_t initCalTotal;
    uint32_t initRadioBandsFail;
    uint32_t initSetParams;
    uint32_t initTxClpcFail;
    uint32_t initRxIqMmFail;
    uint32_t tuneCalTotal;
    uint32_t tuneDrpwRTrimFail;
    uint32_t tuneDrpwPdBufFail;
    uint32_t tuneDrpwTxMixFreqFail;
    uint32_t tuneDrpwTaCal;
    uint32_t tuneDrpwRxIf2Gain;
    uint32_t tuneDrpwRxDac;
    uint32_t tuneDrpwChanTune;
    uint32_t tuneDrpwRxTxLpf;
    uint32_t tuneDrpwLnaTank;
    uint32_t tuneTxLOLeakFail;
    uint32_t tuneTxIqMmFail;
    uint32_t tuneTxPdetFail;
    uint32_t tuneTxPPAFail;
    uint32_t tuneTxClpcFail;
    uint32_t tuneRxAnaDcFail;
    uint32_t tuneRxIqMmFail;
    uint32_t calStateFail;
}ClaibrationFailStatistics_t;

typedef struct ACXStatisticsStruct
{
    INFO_ELE_HDR
    RingStatistics_t ringStat;
    DbgStatistics_t  debug;
    TxStatistics_t   tx;
    RxStatistics_t   rx;
    DMAStatistics_t  dma;
    IsrStatistics_t  isr;
    WepStatistics_t  wep;
    PwrStatistics_t  pwr;
    AesStatistics_t  aes;
    MicStatistics_t  mic;
    EventStatistics_t event;
    PsPollUpsdStatistics_t ps;
    RxFilterStatistics_t rxFilter;
    ClaibrationFailStatistics_t radioCal;
    GemStatistics_t  gem;
} ACXStatistics_t;

/******************************************************************************

    Name:   ACX_ROAMING_STATISTICS_TBL
    Desc:   This information element reads the current roaming triggers 
            counters/metrics. 
    Type:   Statistics
    Access: Read Only
    Length: 6

******************************************************************************/
typedef struct 
{
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION
    uint8_t  padding[3];
    uint32_t MissedBeacons; /* The current number of consecutive lost beacons*/
    uint8_t  snrData;       /* The current average SNR in db - For Data Packets*/
    uint8_t  snrBeacon;     /* The current average SNR in db - For Beacon Packets*/
    int8_t   rssiData;      /* The current average RSSI  - For Data Packets*/
    int8_t   rssiBeacon;    /* The current average RSSI - For Beacon Packets*/
}ACXRoamingStatisticsTable_t;


/******************************************************************************

    Name:   ACX_FEATURE_CFG
    Desc:   Provides expandability for future features
    Type:   Configuration
    Access: Write Only
    Length: 8
    
******************************************************************************/

/* bit defines for Option: */
#define FEAT_PCI_CLK_RUN_ENABLE     0x00000002  /* Enable CLK_RUN on PCI bus */

/* bit defines for dataflowOptions: */
#define DF_ENCRYPTION_DISABLE       0x00000001  /* When set, enable encription in FW.*/
                                                /* when clear, disable encription. */
#define DF_SNIFF_MODE_ENABLE        0x00000080  /* When set, enable decryption in FW.*/
                                                /* when clear, disable decription. */
typedef struct
{
                                    /* Offset Size */
    INFO_ELE_HDR                    /*      0    4 */
    CMD_PARAMS_HOST_ROLE_DEFINITION /*      4    1 - host RoleID */
    uint8_t  padding[3];              /*      5    3 - for 32-bit align */
    uint32_t Options;                 /*      8    4 - Data flow options - refer to above definitions*/
    uint32_t dataflowOptions;         /*     12    4 - Data flow options - refer to above definitions*/
} ACXFeatureConfig_t;




/******************************************************************************

    Name:	ACX_PS_RX_STREAMING
    Type:   Configuration
    Access: Write Only
	Length: 64
    
******************************************************************************/
typedef struct
{
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION /* host RoleID */
    uint8_t     TID;                  /* The TID index*/
    Bool_e     rxPSDEnabled;        /* indicates if this traffic stream requires */
                                    /* employing an RX Streaming delivery mechanism for the TID*/

    uint16_t   streamPeriod;           /* the time period for which a trigger needs to be transmitted*/
                                    /* in case no data TX triggers are sent by host*/
    uint16_t   txTimeout;              /* the timeout from last TX trigger after which FW*/
                                    /* starts generating triggers by itself*/
    uint8_t   padding[1];             /* for 32-bit align */
}ACXPsRxStreaming_t;

/************************************************************
*      MULTIPLE RSSI AND SNR                                *
*************************************************************/

typedef enum
{
    RX_QUALITY_EVENT_LEVEL = 0,  /* The event is a "Level" indication which keeps */
                               /* triggering as long as the average RSSI is below*/
                               /* the threshold.*/

    RX_QUALITY_EVENT_EDGE = 1    /* The event is an "Edge" indication which triggers*/
                               /* only when the RSSI threshold is crossed from above.*/
}rxQualityEventType_enum;

/* The direction in which the trigger is active */
typedef enum
{
    RSSI_EVENT_DIR_LOW = 0,
    RSSI_EVENT_DIR_HIGH = 1,
    RSSI_EVENT_DIR_BIDIR = 2
}RssiEventDir_e;

/******************************************************************************

    RSSI/SNR trigger configuration:

    ACX_RSSI_SNR_TRIGGER
    ACX_RSSI_SNR_WIGHTS

******************************************************************************/
#define NUM_OF_RSSI_SNR_TRIGGERS 8
typedef struct
{
                                    /* Offset Size */
    CMD_PARAMS_HOST_ROLE_DEFINITION /*      4    1 - host RoleID */
    uint8_t  metric;                  /*      5    1 - RSSI Beacon, RSSI Packet, SNR Beacon, SNR Packet */
    uint8_t  type;                    /*      6    1 - Level / Edge */
    uint8_t  direction;               /*      7    1 - Low, High, Bidirectional */
    int16_t  threshold;               /*      8    2 */
    uint16_t pacing;                  /*     10    2 - Minimum delay between consecutive triggers in milliseconds (0 - 60000) */
    uint8_t  hystersis;               /*     12    1 - Hysteresis range in dB around the threshold value (0 - 255) */
    uint8_t  index;                   /*     13    1 - Index of Event. Values 0 - 7 */
    uint8_t  enable;                  /*     14    1 - 1 - Configured, 2 - Not Configured;  (for recovery using) */
    uint8_t  padding[1];              /*     15    1 - for 32-bit alignment */
}RssiSnrTriggerCfg_t;

typedef struct
{
                                /* Offset Size */
    INFO_ELE_HDR                /*      0    4 */
    RssiSnrTriggerCfg_t param;  /*      4   12 */
}ACXRssiSnrTriggerCfg_t;

/* Filter Weight for every one of 4 RSSI /SNR Trigger Metrics  */
typedef struct
{
                                    /* Offset Size */
    uint8_t rssiBeaconAverageWeight;  /*      8    1 */
    uint8_t rssiPacketAverageWeight;  /*      9    1 */
    uint8_t snrBeaconAverageWeight;   /*     10    1 */
    uint8_t snrPacketAverageWeight;   /*     11    1 */
}RssiSnrAverageWeights_t;

typedef struct
{
                                    /* Offset Size */
    INFO_ELE_HDR                    /*      0    4 */
    CMD_PARAMS_HOST_ROLE_DEFINITION /*      4    1 - host RoleID*/
    uint8_t padding[3];               /*      5    3 - for 32-bit alignment */
    RssiSnrAverageWeights_t param;  /*      8    4 */
}ACXRssiSnrAverageWeights_t;

typedef enum
{
    METRIC_EVENT_RSSI_BEACON = 0,
    METRIC_EVENT_RSSI_DATA   = 1,
    METRIC_EVENT_SNR_BEACON  = 2,
    METRIC_EVENT_SNR_DATA     = 3, 
    METRIC_EVENT_TRIGGER_SIZE = 4
}MetricEvent_e;

/******************************************************************************

    Name:   ACX_NOISE_HIST
    Desc:   Noise Histogram activation is done by special command from host which
            is responsible to read the results using this IE.
    Type:   Configuration
    Access: Read Only
    Length: 48 (NOISE_HIST_LEN=8)
    
******************************************************************************/

typedef struct
{
    INFO_ELE_HDR
    uint32_t counters[NOISE_HIST_LEN]; /* This array of eight 32 bit counters describes */
                                     /* the histogram created by the FW noise */
                                     /* histogram engine.*/

    uint32_t numOfLostCycles;          /* This field indicates the number of measurement */
                                     /* cycles with failure because Tx was active.*/

    uint32_t numOfTxHwGenLostCycles;   /* This field indicates the number of measurement */
                                     /* cycles with failure because Tx (FW Generated)*/
                                     /* was active.*/

    uint32_t numOfRxLostCycles;        /* This field indicates the number of measurement */
                                     /* cycles because the Rx CCA was active. */
} NoiseHistResult_t;

/******************************************************************************

    Name:   ACX_PD_THRESHOLD
    Type:   Configuration
    Access: Write Only
    Length: 4

******************************************************************************/

typedef struct
{
    INFO_ELE_HDR
    uint32_t pdThreshold; /* The packet detection threshold in the PHY.*/
} ACXPacketDetection_t;


/******************************************************************************

    Name:   ACX_RATE_POLICY
    Type:   Configuration
    Access: Write Only
    Length: 132

******************************************************************************/

#define HOST_MAX_RATE_POLICIES       (16)

typedef struct 
{
    INFO_ELE_HDR
    uint32_t        ratePolicyIndex;                      /* The index of the rate policy */
    txAttrClass_t ratePolicy;                           /* Rate Policies table*/
} ACXTxAttrRatePolicy_t;


/******************************************************************************

    Name:   ACX_CTS_PROTECTION
    Type:   Configuration
    Access: Write Only
    Length: 1
    
******************************************************************************/

typedef struct 
{
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION /* host RoleID */
    uint8_t   ctsProtectMode;         /* This field is a flag enabling or disabling the*/
                                    /* CTS-to-self protection mechanism:*/
                                    /* 0 - disable, 1 - enable*/
    uint8_t  padding[2];              /* alignment to 32bits boundry   */
}ACXCtsProtection_t;

/******************************************************************************

    ACX_FRAG_CFG

******************************************************************************/

typedef struct
{
    INFO_ELE_HDR
    uint16_t  fragThreshold;
    uint8_t   padding[2];          /* alignment toIE_RTS_CTS_CFG 32bits boundry   */
   
} ACXFRAGThreshold_t;


/******************************************************************************

    ACX_RX_CONFIG_OPT

******************************************************************************/
typedef enum  
{
    RX_QUEUE_TYPE_RX_LOW_PRIORITY,    /* All except the high priority */
    RX_QUEUE_TYPE_RX_HIGH_PRIORITY,   /* Management and voice packets */
    RX_QUEUE_TYPE_NUM,
    RX_QUEUE_TYPE_MAX = MAX_POSITIVE8
} RxQueueType_enum;


#ifdef HOST_COMPILE
    typedef uint8_t RxQueueType_e;
#else
    typedef RxQueueType_enum RxQueueType_e;
#endif


typedef struct 
{
    INFO_ELE_HDR
    uint16_t         rxMblkThreshold;   /* Occupied Rx mem-blocks number which requires interrupting the host (0 = no buffering) */
    uint16_t         rxPktThreshold;    /* Rx packets number which requires interrupting the host  (0 = no buffering) */ 
    uint16_t         rxCompleteTimeout; /* Max time in msec the FW may delay Rx-Complete interrupt */
    RxQueueType_e  rxQueueType;       /* see above */   
    uint8_t          reserved;
} ACXRxBufferingConfig_t;


/******************************************************************************

    FW_GEN_CMD

******************************************************************************/

#define GEN_FW_CMD_SIZE    16

typedef struct 
{
    INFO_ELE_HDR
    uint8_t         genFwCmdBytes[GEN_FW_CMD_SIZE];   
} ACXGenFwCmd_t;

/******************************************************************************

    HOST_IF_CFG_BITMAP

******************************************************************************/

#define HOST_IF_CFG_BITMAP_NO_CHANGE          0x00000000
#define HOST_IF_CFG_BITMAP_RX_FIFO_ENABLE     0x00000001 //BIT_0
#define HOST_IF_CFG_BITMAP_TX_EXTRA_BLKS_SWAP 0x00000002 //BIT_1
#define HOST_IF_CFG_BITMAP_RX_AGGR_WA_ENABLE  0x00000004 //BIT_2
#define HOST_IF_CFG_BITMAP_TX_PAD_TO_SDIO_BLK 0x00000008 //BIT_3
#define HOST_IF_CFG_BITMAP_RX_PAD_TO_SDIO_BLK 0x00000010 //BIT_4   
#define HOST_IF_CFG_BITMAP_USE_EOT            0x00000020 //BIT_5   // using EOT interrupts for FW status reading, command & events mailbox
#define HOST_IF_CFG_BITMAP_ADD_RX_ALIGNMENT   0x00000040 //BIT_6   // for QOS frames HW will add 2 extra bytes between rx info and mac header.



typedef struct 
{
    INFO_ELE_HDR
    uint32_t         hostIfCfgBitmap;   
    uint32_t         hostSdioBlockSize;
    uint32_t         extraMemBlocks;      // default 2 - extra mem blocks per frame in TX.
    uint32_t         lengthFieldSize;     // number of bits of the length field in the first TX word (up to 15 - for using the entire 16 bits).
} ACXHostIfCfgBitmap_t;

/******************************************************************************

    Name:   ACX_SLEEP_AUTH
    Desc:   configuration of sleep authorization level
    Type:   System Configuration
    Access: Write Only
    Length: 1

******************************************************************************/

typedef struct 
{
    INFO_ELE_HDR
    uint8_t   sleepAuth; /* The sleep level authorization of the device. */
                       /* 0 - Always active*/
                       /* 1 - Power down mode: light / fast sleep*/
                       /* 2 - ELP mode: Deep / Max sleep*/
        
    uint8_t  padding[3]; /* alignment to 32bits boundry   */
}ACXSleepAuth_t;

/******************************************************************************

    Name:   ACX_PM_CONFIG
    Desc:   configuration of power management
    Type:   System Configuration
    Access: Write Only
    Length: 1

******************************************************************************/

typedef struct 
{
    INFO_ELE_HDR
    uint32_t  hostClkSettlingTime;    /* Host CLK settling time (in uSec units) */
    uint8_t   hostFastWakeupSupport;  /* 0 - not supported */
                                    /* 1 - supported */
    uint8_t  padding[3];              /* alignment to 32bits boundry   */
}ACXPMConfig_t;

/******************************************************************************

    Name:   ACX_PREAMBLE_TYPE
    Type:   Configuration
    Access: Write Only
    Length: 1
    
******************************************************************************/


typedef struct
{
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION     /* host RoleID */
    PreambleType_e preamble;                /* When set, the WiLink transmits beacon, probe response, */
                                        /* RTS and PS Poll frames with a short preamble. */
                                        /* When clear, the WiLink transmits the frame with a long */
                                        /* preamble.*/
    uint8_t  padding[2];                  /* alignment to 32bits boundry   */
} ACXPreamble_t;


/******************************************************************************

    Name:   ACX_CCA_THRESHOLD
    Type:   Configuration
    Access: Write Only
    Length: 2
    
******************************************************************************/

typedef struct
{
    INFO_ELE_HDR
    uint16_t rxCCAThreshold; /* The Rx Clear Channel Assessment threshold in the PHY*/
                           /* (the energy threshold).*/
    Bool_e txEnergyDetection;  /* The Tx ED value for TELEC Enable/Disable*/
    uint8_t  padding;
} ACXEnergyDetection_t;
      

/******************************************************************************

    Name:   ACX_EVENT_MBOX_MASK
    Type:   Operation
    Access: Write Only
    Length: 8
    
******************************************************************************/

typedef struct
{
    INFO_ELE_HDR
    uint32_t lowEventMask;   /* Indicates which events are masked and which are not*/
                           /* Refer to EventMBoxId_enum in public_event_mbox.h.*/
    
    uint32_t highEventMask;  /* Not in use (should always be set to 0xFFFFFFFF).*/
} ACXEventMboxMask_t;

/******************************************************************************

    Name:   MAX_TX_FAILURE_THRESHOLD_CFG
    Desc:   This information element configures the number of frames transmission
            failures before issuing the "Max Tx Retry" event. The counter is 
            incremented only for unicast frames or frames that require Ack.
            The host will act according to the corresponding role: roam on STA and
            mark station as inactive on AP/GO.
    Type:   Configuration
    Access: Write Only
    Length: 1
    
******************************************************************************/

typedef struct
{
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION        /* host RoleID */
    uint8_t reserved;
    uint16_t maxTxRetry; /* the number of frames transmission failures before */
                      /* issuing the aging event*/
    
} ACXTxFailureThresholdParameters_t;

/******************************************************************************

    Name:   ACX_SG_ENABLE
    Desc:   This command instructs the WiLink to set the Soft Gemini (BT co-existence)
            state to either enable/disable or sense mode. 
    Type:   Configuration
    Access: Write Only
    Length: 1
    
******************************************************************************/
typedef struct
{
    INFO_ELE_HDR
    uint8_t   coexOperationMode; /* 0- Co-ex operation is Disabled
                                  1- Co-ex operation is Disabled
                                  
                                  Default Value: 0- Co-ex operation is Disabled
                                */

    uint8_t  padding[3];  /* alignment to 32bits boundry   */

} ACXBluetoothWlanCoEnableStruct;
  
/******************************************************************************

    Name:   ACX_FM_COEX_CFG
    Desc:   This command instructs the WiLink to set the FM co-existence
            parameters to the desired values. 
    Type:   Configuration
    Access: Write
    Length: 
    
******************************************************************************/
typedef struct

{
    INFO_ELE_HDR
    
    uint8_t   enable;                     /* enable(1) / disable(0) the FM Coex feature */

    uint8_t   swallowPeriod;              /* Swallow period used in COEX PLL swallowing mechanism,
                                           Range: 0-0xFF,  0xFF = use FW default
                                        */

    uint8_t   nDividerFrefSet1;           /* The N divider used in COEX PLL swallowing mechanism for Fref of 38.4/19.2 Mhz.  
                                           Range: 0-0xFF,  0xFF = use FW default
                                        */

    uint8_t   nDividerFrefSet2;           /* The N divider used in COEX PLL swallowing mechanism for Fref of 26/52 Mhz.
                                           Range: 0-0xFF,  0xFF = use FW default
                                        */

    uint16_t  mDividerFrefSet1;           /* The M divider used in COEX PLL swallowing mechanism for Fref of 38.4/19.2 Mhz.
                                           Range: 0-0x1FF,  0xFFFF = use FW default
                                        */

    uint16_t  mDividerFrefSet2;           /* The M divider used in COEX PLL swallowing mechanism for Fref of 26/52 Mhz.
                                           Range: 0-0x1FF,  0xFFFF = use FW default
                                        */

    uint32_t  coexPllStabilizationTime;   /* The time duration in uSec required for COEX PLL to stabilize.
                                           0xFFFFFFFF = use FW default
                                        */

    uint16_t  ldoStabilizationTime;       /* The time duration in uSec required for LDO to stabilize.
                                           0xFFFFFFFF = use FW default
                                        */

    uint8_t   fmDisturbedBandMargin;      /* The disturbed frequency band margin around the disturbed 
                                             frequency center (single sided). 
                                           For example, if 2 is configured, the following channels 
                                             will be considered disturbed channel: 
                                             80 +- 0.1 MHz, 91 +- 0.1 MHz, 98 +- 0.1 MHz, 102 +- 0.1 MHz
                                           0xFF = use FW default
                                        */

    uint8_t   swallowClkDif;              /* The swallow clock difference of the swallowing mechanism.
                                           0xFF = use FW default
                                        */

} ACXWlanFmCoexStruct;
  


/******************************************************************************

    Name:   ACX_TSF_INFO
    Type:   Operation
    Access: Read Only
    Length: 20

******************************************************************************/
typedef struct ACX_fwTSFInformation
{
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION
    uint8_t  paddind1[3];  /* alignment to 32bits boundry   */   
    uint32_t CurrentTSFHigh;
    uint32_t CurrentTSFLow;
    uint32_t lastTBTTHigh;
    uint32_t lastTBTTLow;
    uint8_t LastDTIMCount;
    uint8_t  padding2[3];  /* alignment to 32bits boundry   */
}ACX_fwTSFInformation_t;

/******************************************************************************

Name:   ACX_BET_ENABLE
Desc:   Enable or Disable the Beacon Early Termination module. In addition initialized the
        Max Dropped beacons parameter
Type:   Configuration
Access: Write 
Length: 6
Note:  
******************************************************************************/
typedef struct

{
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION         /* host RoleID */
    uint8_t           Enable;                 /* specifies if beacon early termination procedure is enabled or disabled: 0 - disabled, 1 - enabled */
    uint8_t           MaximumConsecutiveET;   /* specifies the maximum number of consecutive beacons that may be early terminated. After this number is reached 
                                                at least one full beacon must be correctly received in FW before beacon ET resumes.  Legal range: 0 - 255 */
    uint8_t           padding[1];
}ACXBet_Enable_t;


/******************************************************************************

    Name:   DOT11_RX_MSDU_LIFE_TIME
    Type:   Operation
    Access: Write Only
    Length: 4
    
******************************************************************************/

typedef struct
{
    INFO_ELE_HDR
    uint32_t RxMsduLifeTime; /* The maximum amount of time, in TU, that the WiLink */
                           /* should attempt to collect fragments of an MSDU before */
                           /* discarding them. */
                           /* The default value for this field is 512.*/
} dot11RxMsduLifeTime_t;


/******************************************************************************

    Name:   DOT11_CUR_TX_PWR
    Desc:   This IE indicates the maximum TxPower in Dbm/10 currently being used to transmit data.
    Type:   Operation
    Access: Write Only
    Length: 1
    
******************************************************************************/

typedef struct
{ 
    INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION /* host RoleID */
    uint8_t dot11CurrentTxPower;      /* the max Power in Dbm/10 to be used to transmit data.*/
    uint8_t  padding[2];              /* alignment to 32bits boundry   */
} dot11CurrentTxPowerStruct ;


/******************************************************************************

    Name:   DOT11_RX_DOT11_MODE
    Desc:   This IE indicates the current Rx Mode used by DSSS PHY.
    Type:   Configuration
    Access: Write Only
    Length: 4
    
******************************************************************************/
/*
Possible values for Rx DOT11 Mode are the following:
Value   Description
=====   ===========
3       11g - processing of both a and b packet formats is enabled
2       11b - processing of b packet format is enabled
1       11a - processing of a packet format is enabled
0       undefined
*/

typedef struct
{
    INFO_ELE_HDR
    uint32_t dot11RxDot11Mode; /* refer to above table*/
} dot11RxDot11ModeStruct;


/******************************************************************************

    Name:   DOT11_RTS_THRESHOLD 
    Type:   Configuration
    Access: Write Only
    Length: 2

******************************************************************************/

typedef struct 
{
                                    /* Offset Size */
    INFO_ELE_HDR                    /*      0    4 */
    CMD_PARAMS_HOST_ROLE_DEFINITION /*      4    1 - host RoleID */
    uint8_t  reserved;                /*      5    1 - alignment to 32bits boundary   */
    uint16_t  RTSThreshold;           /*      6    2 - The number of octets in an MPDU, below which an */
                                                /* RTS/CTS handshake is not performed.*/
}dot11RTSThreshold_t;


/******************************************************************************

   ACX_CONFIG_PS_WMM (Patch for Wi-Fi Bug)

******************************************************************************/

typedef struct 
{    
    INFO_ELE_HDR
    uint32_t      ConfigPsOnWmmMode;  /* TRUE  - Configure PS to work on WMM mode - do not send the NULL/PS_POLL 
                                               packets even if TIM is set.
                                       FALSE - Configure PS to work on Non-WMM mode - work according to the 
                                               standard. */
} ACXConfigPsWmm_t;

/******************************************************************************
    Name:   ACX_KEEP_ALIVE_MODE
    Desc:   Set/Get the Keep Alive feature mode.
    Type:   Configuration
    Access: Write
    Length: 4 - 1 for the mode + 3 for padding.

******************************************************************************/

typedef struct
{
INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION        /* host RoleID */
    Bool_e  modeEnabled;
    uint8_t padding [2];
}AcxKeepAliveMode;


/******************************************************************************

    Name:   ACX_SET_KEEP_ALIVE_CONFIG
    Desc:   Configure a KLV template parameters.
    Type:   Configuration
    Access: Write Only
    Length: 8

******************************************************************************/

typedef enum
{
    NO_TX = 0,
    PERIOD_ONLY
} KeepAliveTrigger_enum;

#ifdef HOST_COMPILE
typedef uint8_t KeepAliveTrigger_e;
#else
typedef KeepAliveTrigger_enum KeepAliveTrigger_e;
#endif

typedef enum
{
    KLV_TEMPLATE_INVALID = 0,
    KLV_TEMPLATE_VALID,
} KeepAliveTemplateValidation_enum;

#ifdef HOST_COMPILE
typedef uint8_t KeepAliveTemplateValidation_e;
#else
typedef KeepAliveTemplateValidation_enum KeepAliveTemplateValidation_e;
#endif

typedef struct
{
                                            /* Offset Size */
    INFO_ELE_HDR                            /*      0    4 */
    CMD_PARAMS_HOST_ROLE_DEFINITION         /*      4    1 - host RoleID */
    uint8_t index;                            /*      5    1 */
    KeepAliveTemplateValidation_e   valid;  /*      6    1 */
    KeepAliveTrigger_e  trigger;            /*      7    1 */
    uint32_t period;                          /*      8    4 - at range 1000-3600000 (msec). (To allow better range for debugging)*/
} AcxSetKeepAliveConfig_t;

/*
 * BA session interface structure
 */

typedef struct
{
    INFO_ELE_HDR
    uint8_t hLid;                     /* Specifies Link Id, Range 0-31*/
    uint8_t Tid;                     /* TID */
    uint8_t state;                    /* SET/CLEAR */
    uint8_t WinSize;                /* windows size in num of packet */
    uint16_t SSN;                    /* BA session starting sequence number.  RANGE 0-FFF */
    uint8_t Padding[2];
    
} TAxcBASessionRxSetupConfigure;



typedef struct
{
    INFO_ELE_HDR
    uint8_t roleId;                   /* Specifies role Id, Range 0-7, FF means ANY role    */
    uint8_t PolicyBitmap;                  /* per TID bitmap either BA is allowed or not allowed */
    uint8_t WinSize;                 /* windows size of the BA session */
    uint8_t padding_1[1];
    uint16_t InactivityTimeout;       /* as initiator inactivity timeout in time units(TU) of 1024us /
                                       as receiver reserved */
    uint8_t padding_2[2];
} TAxcBaSessionInitiatorPolicy;



/******************************************************************************

    Name:   ACX_PEER_HT_CAP
    Desc:   Configure HT capabilities - declare the capabilities of the peer
            we are connected to.
    Type:   Configuration
    Access: Write Only
    Length:

******************************************************************************/

typedef struct
{
    INFO_ELE_HDR
    uint32_t uHtCapabilites;      /*
                                 * bit 16  -  Allow HT Operation.
                                 * bit 0   -  Indicates support for receiving LDPC coded packets.
                                 * bit 1   -  Set to 0 if only 20 MHz operation is supported.
                                              Set to 1 if both 20 MHz and 40 MHz operation is supported.
                                 * bit 2|3 -  Indicates the spatial multiplexing power save mode.
                                              Set to 0 for static SM power save mode.
                                              Set to 1 for dynamic SM power save mode.
                                              Set to 3 for SM Power Save disabled.
                                 * bit 4   -  Indicates support for the reception of PPDUs with HT-greenfield format.
                                 * bit 5   -  Indicates short GI support for the reception of packets with BW of 20Mhz.
                                 * bit 6   -  Indicates short GI support for the reception of packets with BW of 40Mhz.
                                 * bit 7   -  Indicates support for the transmission of PPDUs using STBC.
                                 * bit 8|9 -  Indicates support for the reception of PPDUs using STBC
                                              Set to 0 for no support.
                                              Set to 1 for support of one spatial stream.
                                              Set to 2 for support of one and two spatial streams.
                                              Set to 3 for support of one, two and three spatial streams.
                                 * bit 10  -  Indicates support for HTdelayed Block Ack operation.
                                 * bit 11  -  Indicates maximum AMSDU length.
                                              Set to 0 for 3839 octets
                                              Set to 1 for 7935 octets
                                 * bit 12  -  Indicates use of DSSS/CCK mode in a 20/40 MHz BSS.
                                              In Beacon and Probe Response frames:
                                                Set to 0 if the BSS does not allow use of DSSS/CCK in 40 MHz.
                                                Set to 1 if the BSS does allow use of DSSS/CCK in 40 MHz.
                                              Otherwise:
                                                Set to 0 if the STA does not use DSSS/CCK in 40 MHz.
                                                Set to 1 if the STA uses DSSS/CCK in 40 MHz.
                                 * bit 13  - Indicates support for PSMP mechanism.
                                 * bit 14  - Indicates whether APs receiving this information or reports of this
                                             information are required to prohibit 40 MHz transmissions.
                                 * bit 15  - Indicates support for the LSIG TXOP protection mechanism.
                                 */


     uint8_t  hlid;               /*
                                 * Indicates to which peer these capabilities are relevant.
                                 * Note, currently this value will be set to FFFFFFFFFFFF to indicate it is
                                 * relevant for all peers since we only support HT in infrastructure mode.
                                 * Later on this field will be relevant to IBSS/DLS operation
                                 */

     uint8_t  uAmpduMaxLength;    /*
                                 * This the maximum a-mpdu length supported by the AP. The FW may not
                                 * exceed this length when sending A-MPDUs
                                 */

     uint8_t  uAmpduMinSpacing;   /* This is the minimal spacing required when sending A-MPDUs to the AP. */

} TAxcHtCapabilitiesIeFwInterface;

/******************************************************************************

    Name:   ACX_PEER_CAP
    Desc:   Configure HT capabilities - declare the capabilities of the peer
            we are connected to.
    Type:   Configuration
    Access: Write Only
    Length:

******************************************************************************/



/******************************************************************************
 FwStaticData_t - information stored in command mailbox area after the Init 
                  process is complete

 Note:  This structure is passed to the host via the mailbox at Init-Complete
        without host request!!
        The host reads this structure before sending any configuration to the FW.
******************************************************************************/
#define SIZE_OF_PHY_VERSION_STRING 20
typedef struct
{
    /* dot11StationIDStruct */
    uint8_t dot11StationID[6]; /* The MAC address for the STA.*/
    uint8_t padding[2];       /* alignment to 32bits boundry   */
    /* ACXRevision_t */
    char FWVersion[20];     /* The WiLink firmware version, an ASCII string x.x.x.x.x */
                            /* that uniquely identifies the current firmware. */
                            /* The left most digit is incremented each time a */
                            /* significant change is made to the firmware, such as */
                            /* WLAN new project.*/
                            /* The second and third digit is incremented when major enhancements*/
                            /* are added or major fixes are made.*/
                            /* The fourth digit is incremented for each SP release */
                            /* and it indicants the costumer private branch */
                            /* The fifth digit is incremented for each build.*/
        
    uint32_t HardWareVersion; /* This 4 byte field specifies the WiLink hardware version. */
                            /* bits 0  - 15: Reserved.*/
                            /* bits 16 - 23: Version ID - The WiLink version ID  */
                            /*              (1 = first spin, 2 = second spin, and so on).*/
                            /* bits 24 - 31: Chip ID - The WiLink chip ID. */
      //  uint8_t txPowerTable[NUMBER_OF_SUB_BANDS_E][NUM_OF_POWER_LEVEL]; /* Maximun Dbm in Dbm/10 units */
        char FwPhyVersion[SIZE_OF_PHY_VERSION_STRING];
} FwStaticData_t;

/******************************************************************************



    ACX_TX_CONFIG_OPT

 

******************************************************************************/

typedef struct 
{
    INFO_ELE_HDR
    uint16_t  txCompleteTimeout;   /* Max time in msec the FW may delay frame Tx-Complete interrupt */
    uint16_t  txCompleteThreshold; /* Tx-Complete packets number which requires interrupting the host (0 = no buffering) */
} ACXTxConfigOptions_t;


/******************************************************************************

Name:   ACX_PWR_CONSUMPTION_STATISTICS
Desc:   Retrieve time statistics of the different power states.
Type:   Configuration
Access: Read Only
Length: 20 

******************************************************************************/

// Power Statistics
typedef struct
{
    INFO_ELE_HDR
    uint32_t awakeTimeCnt_Low;
    uint32_t awakeTimeCnt_Hi;
    uint32_t powerDownTimeCnt_Low;
    uint32_t powerDownTimeCnt_Hi;
    uint32_t elpTimeCnt_Low;
    uint32_t elpTimeCnt_Hi;
    uint32_t ListenMode11BTimeCnt_Low;
    uint32_t ListenMode11BTimeCnt_Hi;
    uint32_t ListenModeOFDMTimeCnt_Low;
    uint32_t ListenModeOFDMTimeCnt_Hi;
}ACXPowerConsumptionTimeStat_t;


/******************************************************************************
    Name:   ACX_BURST_MODE
    Desc:   enable/disable burst mode in case TxOp limit != 0.
    Type:   Configuration
    Access:    Write
    Length: 1 - 2 for the mode + 3 for padding.

******************************************************************************/

typedef struct
{
INFO_ELE_HDR
    CMD_PARAMS_HOST_ROLE_DEFINITION        /* host RoleID */
    Bool_e  enable;
    uint8_t padding [2];
}AcxBurstMode;


/******************************************************************************
    Name:   ACX_SET_RATE_MAMAGEMENT_PARAMS
    Desc:   configure one of the configurable parameters in rate management module.
    Type:   Configuration
    Access:    Write
    Length: 8 bytes

******************************************************************************/
typedef enum
{
    RATE_MGMT_RETRY_SCORE_PARAM,
    RATE_MGMT_PER_ADD_PARAM,
    RATE_MGMT_PER_TH1_PARAM,
    RATE_MGMT_PER_TH2_PARAM,
    RATE_MGMT_MAX_PER_PARAM,
    RATE_MGMT_INVERSE_CURIOSITY_FACTOR_PARAM,
    RATE_MGMT_TX_FAIL_LOW_TH_PARAM,
    RATE_MGMT_TX_FAIL_HIGH_TH_PARAM,
    RATE_MGMT_PER_ALPHA_SHIFT_PARAM,
    RATE_MGMT_PER_ADD_SHIFT_PARAM,
    RATE_MGMT_PER_BETA1_SHIFT_PARAM,
    RATE_MGMT_PER_BETA2_SHIFT_PARAM,
    RATE_MGMT_RATE_CHECK_UP_PARAM,
    RATE_MGMT_RATE_CHECK_DOWN_PARAM,
    RATE_MGMT_RATE_RETRY_POLICY_PARAM,
    RATE_MGMT_PER_WEIGHT_SHIFT_PARAM,
    RATE_MGMT_TP_WEIGHT_SHIFT_PARAM,
    RATE_MGMT_ALL_PARAMS = 0xff
} rateAdaptParam_enum;

#ifdef HOST_COMPILE
typedef uint8_t rateAdaptParam_e;
#else
typedef rateAdaptParam_enum rateAdaptParam_e;
#endif

#define RATE_MGMT_NUM_OF_UC     (2)
#define RATE_MGMT_NUM_OF_RATES  (13)


/* NEW STRUCTURE */
typedef struct
{
    INFO_ELE_HDR
    rateAdaptParam_e paramIndex;
    uint16_t RateRetryScore;
    uint16_t PerAdd;
    uint16_t PerTh1;
    uint16_t PerTh2;
    uint16_t MaxPer;
    uint8_t InverseCuriosityFactor[RATE_MGMT_NUM_OF_UC];
    uint8_t TxFailLowTh;
    uint8_t TxFailHighTh;
    uint8_t PerAlphaShift;
    uint8_t PerAddShift;
    uint8_t PerBeta1Shift;
    uint8_t PerBeta2Shift;
    uint8_t RateCheckUp;
    uint8_t RateCheckDown;
    uint8_t RateRetryPolicy[RATE_MGMT_NUM_OF_RATES]; 
    uint8_t PerWeightShift[RATE_MGMT_NUM_OF_UC];          // 2 weights, 1 per UC
    uint8_t TpWeightShift[RATE_MGMT_NUM_OF_UC];               // 2 weights, 1 per UC
}AcxRateAdaptParams;

/******************************************************************************
    Name:   ACX_GET_RATE_MAMAGEMENT_PARAMS
    Desc:   read the configurable parameters of rate management module.
    Type:   
    Access: read
    Length: 8 bytes

******************************************************************************/
typedef struct
{
    INFO_ELE_HDR
    int32_t  SNRCorrectionHighLimit;
    int32_t  SNRCorrectionLowLimit;
    int32_t  PERErrorTH;
    int32_t  attemptEvaluateTH;
    int32_t  goodAttemptTH;
    int32_t  curveCorrectionStep;
}AcxRateMangeReadParams;


/******************************************************************************

    Name:   ACX_SET_DCO_ITRIM_PARAMS    
    Desc:   Configure DCO Itrim operational parameters:               
            1. Enable/disable of the entire feature.                                     
            2. Moderation timeout (usec) - how much time to wait from last TX
            until DCO Itrim can be set low.
    Type:   Configuration
    Access: Write Only
    Length: 

******************************************************************************/

typedef struct
{
    INFO_ELE_HDR
    Bool_e enable;
    uint32_t moderation_timeout_usec;
}ACXDCOItrimParams_t ;


/******************************************************************************

    Name:   ACX_UPDATE_INCONNECTION_STA_LIST    
    Desc:   Configure In Connection STA List.
            Add/Remove STA from In Connection List according to mac address.
    Type:   Configuration
    Access: Write Only
    Length: 

******************************************************************************/

typedef struct  
{
    INFO_ELE_HDR                    
    uint8_t   mac_address[6];         /* STA mac address  */
    CMD_PARAMS_HOST_ROLE_DEFINITION /* host RoleID */
    uint8_t   padding[1];
} ACXInConnectionSTA_t;


/******************************************************************************
    Name:   ACX_CONFIG_PS    
    Desc:   Configure PS operational parameters:               
            numOfEnterPsRetries        -  Number of retries attempts when enter to PS.
            numOfExitPsRetries         -  Number of retries attempts when exit from PS.
            RequestedRateForNullDataTx - Rates requested for sending the Null Data packet.
    Type:   Configuration
    Access: Write Only
    Length: 

******************************************************************************/

typedef struct
{
    INFO_ELE_HDR
    uint8_t   numOfExitPsRetries;
    uint8_t   numOfEnterPsRetries;
    uint8_t   temp1;
    uint8_t   temp2;
    uint32_t  RequestedRateForNullDataTx;
}ACXConfigPsParams_t ;

/******************************************************************************

    Name:   dot11ERPProtectionMode    
    Desc:   Configure PS operational parameters:               
            numOfEnterPsRetries        -  Number of retries attempts when enter to PS.
            numOfExitPsRetries         -  Number of retries attempts when exit from PS.
            RequestedRateForNullDataTx - Rates requested for sending the Null Data packet.
    Type:   Configuration
    Access: Write Only
    Length: 

******************************************************************************/
#define PROTECTION_MODE_DISABLE     (0)
#define PROTECTION_MODE_FW          (1)
#define PROTECTION_MODE_DRIVER      (2)


typedef struct
{                                   /* Offset Size */
    INFO_ELE_HDR                    /*      0    4 */
    CMD_PARAMS_HOST_ROLE_DEFINITION /*      4    1 - host RoleID */
    uint8_t    ProtectionMode;        /*      5    1 - operation mode for beacon erp filtering */
    uint8_t    reserved[2];           /*      6    2 - alignment to 32bits boundary   */
}dot11ProtectionModeParams_t;

/******************************************************************************

    Name:   ACX_CONFIG_HANGOVER    
    Desc:   Configure Hangover operational parameters:               
            
            bDynamicHangoverMode-          Enable/Disable dynamic hangover algorithm.
            maxHangOverPeriod-             max time that hangover can be.
            minHangOverPeriod-             min time that hangover can be.
                                           hangover is decreased to the next time: max hangover inside sliding
                                           window + this parameter
            increaseDelatTimeFromHangover- if the time stamp of the last RX packet is bigger 
                                           than (hangover - IncreaseDelatTimeFromHangover) means
                                           the hangover is increased. 
            decreaseDelatTimeFromHangover- if the time stamp of the last RX packet is smaller than 
                                           (hangover - DecreaseDelatTimeFromHangover) during all sliding window
                                           means the hangover is decreased. 
            recoverTime-                   how often to return to the original hangover.If time is zero means
                                           recover hangover feature is disabled
            bEarlyTerminationMode-         Enable/Disable early termination in dynamic hangover algorithm.
            quietTimeForEarlyTermination-  Duration that should be "quite" in the air in order to do early termination.
            IncreaseHangoverTime-          hangover is increased by this time
            SlidingWindowSize-             the size of sliding window the decision is based on sliding window
            hangOverPeriod-                original hangover - hangover time if bDynamicHangoverMode is disable,
                                           hangover every restart of the algorithm(every join command)
                                           hangover every recovery time
                                           

            NOTE -PAY ATTENTION  
            all the times and periods are in units of half MSEC.
            1  = 0.5 MSEC
            2  = 1   MSEC
            3  = 1.5 MSEC
                    
            for example:
            if IncreaseDelatTimeFromHangover = 1 (value of host command) that means that the hangover will be
            increase with 0.5 MSEC each time.
            Because the module parameters are with USEC units 
            there is a multiply by 500 to each host parameters which describes time
            so in the the module IncreaseDelatTimeFromHangover will be 500 (500 USEC means 0.5 MSEC
            means 1 in half MSEC units).

  
    Type:   Configuration
    Access: Write Only
    Length: 

******************************************************************************/
typedef struct
{
  INFO_ELE_HDR
  uint32_t recoverTime;
  uint8_t  hangOverPeriod;
  Bool_e bDynamicHangoverMode;
  Bool_e bEarlyTerminationMode;
  uint8_t  maxHangOverPeriod;
  uint8_t  minHangOverPeriod;
  uint8_t  increaseDelatTimeFromHangover;
  uint8_t  decreaseDelatTimeFromHangover;
  uint8_t  quietTimeForEarlyTermination;
  uint8_t  increaseHangoverTime;
  uint8_t  slidingWindowSize;
  uint8_t  spare1;
  uint8_t  spare2;

}ACXConfigHangOverParams_t ;

#endif /* PUBLIC_INFOELE_H */

