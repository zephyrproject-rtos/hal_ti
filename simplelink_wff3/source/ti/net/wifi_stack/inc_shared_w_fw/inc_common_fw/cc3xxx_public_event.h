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
 *    its contributors may bcsie used to endorse or promote products derived
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

  FILENAME:       public_event_mbox.h
 
  DESCRIPTION:    Public header for the Event Mailbox FW<->Driver interface



***********************************************************************************************************************/
#ifndef PUBLIC_EVENT_MBOX_H
#define PUBLIC_EVENT_MBOX_H

/******************************************************************************

	EVENT MBOX
	 
    The event mechanism is based on a pair of event buffers (buffers "A" and "B") in fixed locations
    in the device's memory. The host processes one buffer (buffer "A") while the other buffer 
    (buffer "B") continues to collect events. When the host is finished, it begins processing the 
    other buffer ("B") while the first buffer ("A") collects, and so on.
    Once the host finishes processing events from one buffer,
    it signals with an acknowledge interrupt (bit 0 in the INT_TRIG register) that the event buffer
    is free. This interrupt triggers the device to send the next event structure if there are any 
    collected events in it.

    Note: Only one instance (the last) of each type of event is collected.
       
******************************************************************************/


#include "cc3xxx_public_types.h"
#include "cc3xxx_public_commands.h"
#include "cc3xxx_public_infoele.h"

#ifdef THICK_MAC_COMPILE
#include "./upper_mac/upper_mac/user_interface/wlan_if.h"
#endif

//#include "public_mac_phy_api.h"
// from public_mac_phy_api.h
typedef enum{
    NO_RADAR_E      = 0,
    REGULAR_RADAR_E = 1,
    CHIRP_RADAR_E   = 2

}RadarType_enum;
typedef RadarType_enum RadarType_e;


/*************************************************************************

  Events Enumeration 

**************************************************************************/
typedef enum 
{
    /* 
        change BITS to numbers to allow the events to be parsed by the Logger to Text.
     */ 
    RSSI_SNR_TRIGGER_0_EVENT_ID                     = 0x00000001,//   BIT_0,
    RSSI_SNR_TRIGGER_1_EVENT_ID                     = 0x00000002,//   BIT_1,
    RSSI_SNR_TRIGGER_2_EVENT_ID                     = 0x00000004,//   BIT_2,
    RSSI_SNR_TRIGGER_3_EVENT_ID                     = 0x00000008,//   BIT_3,
    RSSI_SNR_TRIGGER_4_EVENT_ID                     = 0x00000010,//   BIT_4,
    RSSI_SNR_TRIGGER_5_EVENT_ID                     = 0x00000020,//   BIT_5,
    RSSI_SNR_TRIGGER_6_EVENT_ID                     = 0x00000040,//   BIT_6,
    RSSI_SNR_TRIGGER_7_EVENT_ID                     = 0x00000080,//   BIT_7,
    SCAN_COMPLETE_EVENT_ID                          = 0x00000100,//   BIT_8,
    RADAR_DETECTED_EVENT_ID                         = 0x00000200,//   BIT_9,
    CHANNEL_SWITCH_COMPLETE_EVENT_ID                = 0x00000400,//   BIT_10,
    BSS_LOSS_EVENT_ID                               = 0x00000800,//   BIT_11,
    MAX_TX_FAILURE_EVENT_ID                         = 0x00001000,//   BIT_12,
    DUMMY_PACKET_ID                                 = 0x00002000,//   BIT_13,
    INACTIVE_STA_EVENT_ID                           = 0x00004000,//   BIT_14,
    PEER_REMOVE_COMPLETE_EVENT_ID                   = 0x00008000,//   BIT_15,
    PERIODIC_SCAN_COMPLETE_EVENT_ID                 = 0x00010000,//   BIT_16,
    BA_SESSION_RX_CONSTRAINT_EVENT_ID               = 0x00020000,//   BIT_17,
    REMAIN_ON_CHANNEL_COMPLETE_EVENT_ID             = 0x00040000,//   BIT_18,
    REG_DOMAIN_CHANNELS_CONFIG_COMPLETE_EVENT_ID    = 0x00080000,//   BIT_19,
    PERIODIC_SCAN_REPORT_EVENT_ID                   = 0x00100000,//   BIT_20,
    RX_BA_WIN_SIZE_CHANGE_EVENT_ID                  = 0x00200000,//   BIT_21,
    SMART_CONFIG_SYNC_EVENT_ID                      = 0x00400000,//   BIT_22,
    SMART_CONFIG_DECODE_EVENT_ID                    = 0x00800000,//   BIT_23,
    TIME_SYNC_TSF_EVENT_ID                          = 0x01000000,//   BIT_24,
    FW_LOGGER_INDICATION			                = 0x02000000,//   BIT_25,
    UPPERMAC_EVENT_ID                               = 0x04000000,//   BIT_26,
    BLE_EVENT_ID                                    = 0x08000000,//   BIT_27,
    RESEED_EVENT_ID                                 = 0x10000000,//   BIT_28,
    CSI_EVENT_ID                                    = 0x20000000,//   BIT_29,
    FW_CRASH_EVENT_ID                               = 0x40000000,//   BIT_30,
    ERROR_EVENT_ID                                  = 0x80000000,//   BIT_31,

    EVENT_MBOX_ALL_EVENT_ID                     = MAX_POSITIVE32
} EventMBoxId_e;

/*************************************************************************

  Specific Event Parameters 

**************************************************************************/
typedef enum
{
    RX_BA_SESSION_NOT_ALLOWED   = 0,
    RX_BA_SESSION_ALLOWED       = 1,
    RX_BA_SESSION_NUM_OF_STATES = MAX_POSITIVE8
}RxBaSessionState_enum;

typedef RxBaSessionState_enum RxBaSessionState_e;


/* RADAR_DETECTED_EVENT_ID event struct */
typedef struct
{
    Channel_e   radarDetectedChannel;       /* radar detected channel */
    uint8_t /*RadarType_e*/ radarDetectedType;        /* radar detected type */

} RadarDetected_t;

/* BA_SESSION_RX_CONSTRAINT event struct */
typedef struct
{
    uint16_t	roleIdBitMap;		/* multi-role event bit map, 0xFFFF == any-role*/
	uint16_t  stateBitMap;        /* multi-role event state bit map:  stateBiMap:BIT_X is relevant to roleId X *//* NOT_ALLOWED = 0, ALLOWED = 1 */ 
								
} BaSessionRxConstraint_t;

/* RX_BA_WIN_SIZE_CHANGE_EVENT_ID event struct */
typedef struct
{
    uint8_t  roleId;		   
    uint8_t  linkId;
    uint8_t  rxBaWinSize;
    uint8_t  padding;            /* for alignment to 32 bits boundary*/
    								
} RxBaWinSizeChange_t;

typedef struct
{
    uint8_t   channel;
    uint8_t   band;
} SmartConfigSyncEvent_t;

typedef struct
{
    uint8_t   ssidLen;
    uint8_t   pwdLen;
    uint8_t   privateTokenLen;
    uint8_t   status;
    uint8_t   ssid[32];
    uint8_t   pwd[64];
    uint8_t   privateToken[32];
} SmartConfigDecodeEvent_t;

typedef struct
{
    uint32_t   timeSyncMacTimestampHigh;
    uint32_t   timeSyncMacTimestamp;
}timeSyncMac_t;

typedef enum
{
    SMART_CONFIG_DECODE_COMPLETE_OK,
    SMART_CONFIG_DECODE_COMPLETE_ERROR
} SmartConfigDecodeStatus_enum;

typedef struct
{
    uint8_t   data[MAX_BLE_PKT_LEN];
    uint16_t  dataLen;
    uint16_t  padding;
}bleEvent_t;

#define CSI_FW_MAX_DATA_LENGTH                             27//126

typedef struct
{
    uint32_t  timestamp;
    uint16_t  packetLength;    // length of packet including Frame Check Sequence(FCS)
    uint16_t  csiInfoLength;
    uint8_t   tMacAddr[MAC_ADDR_LEN]; // transmitter mac address
    uint8_t   rMacAddr[MAC_ADDR_LEN]; // receiver mac address
    int8_t    rssi;
    uint8_t   rate;       // Non HT, 11.b,g
    uint8_t   sig_mode;   // preamble
    uint8_t   mcs;
    uint8_t   sgi;
    uint8_t   channel;
    uint8_t   ant;
    uint8_t   cw;
    uint32_t  csiDataBuf[CSI_FW_MAX_DATA_LENGTH];

}CsiData_t;

/*************************************************************************

  The Event Mailbox structure in memory 

**************************************************************************/

#ifndef THICK_MAC_COMPILE
typedef struct __PACKED__
{                       
    /* Events Bit Mask */                          
    uint32_t eventsVector;

    /* Events Data */
    uint8_t                     NumberOfScanResults;                               /* how many scan results were parsed */
    uint8_t                     NumberOfPeriodicScanResults;                       /* how many periodic scan results were parsed */
    uint16_t                    ChannelSwitchRoleIdBitMap;                         /* channel switch multi-role event bit map*/
    int8_t                      RSSISNRTriggerMetric[NUM_OF_RSSI_SNR_TRIGGERS];    /* RSSI and SNR Multiple Triggers Array */
    uint32_t                    PeerRemovedLidBitMap;                              /* peer remove bit map*/
    BaSessionRxConstraint_t     BaSessionRxConstraint;                             /* role on whom to enable/disable Rx BA session */
    uint16_t                    RocCompleteRoleIdBitMap;                           /* remain on channel complete multi-role event bit map*/
    uint16_t                    BssLossRoleIdBitMap;                               /* bss loss multi-role event bit map*/
    uint16_t                    MaxTxFailureLidBitMap;                             /* max tx fail link event bit map*/
    uint16_t                    timeSyncMacTimestampHighMSB;
    uint16_t                    InactiveStaLidBitMap;                              /* inactive STA link event bit map*/
    uint16_t                    timeSyncMacTimestampHighLSB;
    RxBaWinSizeChange_t         RxBaWinSizeChange;                                 /* OritB - IOP: APs not respecting max ampdu rx size (16k) workaround */
    SmartConfigDecodeEvent_t    smartConfigDecode;                                 /* used by Smart Config Decode event */
    SmartConfigSyncEvent_t      smartConfigSync;                                   /* used by Smart Config Sync event */
    uint16_t                    timeSyncMacTimestampMSB;                           /* time sync Mac Timestamp MSB */
    RadarDetected_t             radarDetectedInfo;                                 /* The radar detection info */
    uint16_t                    timeSyncMacTimestampLSB;                           /* time sync Mac Timestamp LSB */
    bleEvent_t                  bleEvent;                                          /* ble event data */
    CsiData_t                   csiData;
    uint8                       reseedRequestSize;                                 /* reseed request size */
    uint8                       padding[3];                                        /* padding for future usage */
} EventMailBox_t;

#else
#if 0
#define WLAN_MAX_SCAN_COUNT                (20)
#define WLAN_BSSID_LENGTH                   (6)
#define WLAN_SSID_MAX_LENGTH               (32)

/*****************************************************************************/
/* EVENTS DEFINITIONS                                                        */
/*****************************************************************************/

typedef enum
{
    WLAN_EVENT_CONNECT = 1,
    WLAN_EVENT_DISCONNECT,
    WLAN_EVENT_SCAN_RESULT,
    WLAN_EVENT_MAX = 0xFFFF
} WlanEventId_e;

typedef struct
{
    uint8_t     SsidLen;
    uint8_t     SsidName[WLAN_SSID_MAX_LENGTH];
    uint8_t     Bssid[WLAN_BSSID_LENGTH];
    uint8_t     Channel;
} WlanEventConnect_t;

typedef struct
{
    uint8_t                 SsidLen;
    uint8_t                 SsidName[WLAN_SSID_MAX_LENGTH];
    uint8_t                 Bssid[WLAN_BSSID_LENGTH];
    int16_t                 ReasonCode;
} WlanEventDisconnect_t;

typedef struct
{
    uint8_t Ssid[WLAN_SSID_MAX_LENGTH];
    uint8_t Bssid[WLAN_BSSID_LENGTH];
    uint8_t SsidLen;
    int8_t  Rssi;
    int32_t SecurityInfo;
    uint8_t Channel;
    char    Reserved[1];
}WlanNetworkEntry_t;

typedef struct
{
    uint32_t           NetworkListResultLen;
    WlanNetworkEntry_t NetworkListResult[WLAN_MAX_SCAN_COUNT];

} WlanEventScanResult_t;

typedef union
{
    WlanEventConnect_t       Connect;    /* WLAN_EVENT_CONNECT */
    WlanEventDisconnect_t    Disconnect; /* WLAN_EVENT_DISCONNECT */
    WlanEventScanResult_t    ScanResult; /* WLAN_EVENT_DISCONNECT */
} WlanEventData_u;

typedef struct
{
    WlanEventId_e        Id;
    WlanEventData_u    Data;

} WlanEvent_t;
#endif

typedef struct __PACKED__
{
    /* Events Bit Mask */
    uint32_t eventsVector;

    /* Events Data */
    WlanEvent_t uppermacevent;
} EventMailBox_t;
#endif


#endif /* PUBLIC_EVENT_MBOX_H*/

