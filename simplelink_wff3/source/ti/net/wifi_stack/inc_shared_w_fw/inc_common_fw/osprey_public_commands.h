/***************************************************************************
**+----------------------------------------------------------------------+**
**|                                ****                                  |**
**|                                ****                                  |**
**|                                ******o***                            |**
**|                          ********_///_****                           |**
**|                           ***** /_//_/ ****                          |**
**|                            ** ** (__/ ****                           |**
**|                                *********                             |**
**|                                 ****                                 |**
**|                                  ***                                 |**
**|                                                                      |**
**|     Copyright (c) 1998 - 2009 Texas Instruments Incorporated         |**
**|                        ALL RIGHTS RESERVED                           |**
**|                                                                      |**
**| Permission is hereby granted to licensees of Texas Instruments       |**
**| Incorporated (TI) products to use this computer program for the sole |**
**| purpose of implementing a licensee product based on TI products.     |**
**| No other rights to reproduce, use, or disseminate this computer      |**
**| program, whether in part or in whole, are granted.                   |**
**|                                                                      |**
**| TI makes no representation or warranties with respect to the         |**
**| performance of this computer program, and specifically disclaims     |**
**| any responsibility for any damages, special or consequential,        |**
**| connected with the use of this program.                              |**
**|                                                                      |**
**+----------------------------------------------------------------------+**
***************************************************************************/
/**********************************************************************************************************************

  FILENAME:       osprey_public_commands.h

  DESCRIPTION:    Command definitions shared with host



***********************************************************************************************************************/
#ifndef OSPREY_PUBLIC_COMMANDS_H
#define OSPREY_PUBLIC_COMMANDS_H


#include "osprey_public_types.h"
#include "802_11defs.h"

typedef enum
{
    CMD_EMPTY,
    CMD_SET_KEYS                        = 1,
    CMD_SET_LINK_CONNECTION_STATE       = 2,

    CMD_CHANNEL_SWITCH                  = 3,
    CMD_STOP_CHANNEL_SWITCH             = 4,

    CMD_REMAIN_ON_CHANNEL               = 5,
    CMD_CANCEL_REMAIN_ON_CHANNEL        = 6,

    CMD_START_DHCP_MGMT_SEQ             = 7,
    CMD_STOP_DHCP_MGMT_SEQ              = 8,

    CMD_START_SECURITY_MGMT_SEQ         = 9,
    CMD_STOP_SECURITY_MGMT_SEQ          = 10,

    CMD_START_ARP_MGMT_SEQ              = 11,
    CMD_STOP_ARP_MGMT_SEQ               = 12,

    CMD_START_DNS_MGMT_SEQ              = 13,
    CMD_STOP_DNS_MGMT_SEQ               = 14,

    /* Access point commands */
    CMD_ADD_PEER                        = 15,
    CMD_REMOVE_PEER                     = 16,

    /* Role API */
    CMD_ROLE_ENABLE                     = 17,
    CMD_ROLE_DISABLE                    = 18,
    CMD_ROLE_START                      = 19,
    CMD_ROLE_STOP                       = 20,

    CMD_AP_SET_BEACON_INFO              = 21,              /* Set AP beacon template */

    // Managed sequence of sending deauth / disassoc frame
    CMD_SEND_DEAUTH_DISASSOC            = 22,

    CMD_SCHED_STATE_EVENT               = 23,
    CMD_SCAN                            = 24,
    CMD_STOP_SCAN                       = 25,
    CMD_SET_PROBE_IE                    = 26,

    CMD_CONFIGURE                       = 27,    /*use this to write information elements*/
    CMD_INTERROGATE                     = 28,    /*use this to read information elements*/
    CMD_DEBUG                           = 29,      
    CMD_DEBUG_READ                      = 30,


    CMD_TEST                            = 31,
    CMD_PLT_ENABLE                      = 32,
    CMD_PLT_DISABLE                     = 33,
    CMD_CONNECTION_SCAN_SSID_CFG        = 34,
    CMD_UPPER_MAC_COMMANDS              = 35,
    CMD_CONTAINER_DOWNLOADS             = 36,
    CMD_DOWNLOAD_INI_PARAMS             = 37,
    CMD_SET_BD_ADDR                     = 38,
    CMD_BLE_COMMANDS                    = 39,

    CMD_LAST_COMMAND,                   // must be the last


    MAX_COMMAND_ID_OSPREY = 0x7FFF
}Command_e;

typedef enum
{
    CMD_MAILBOX_IDLE              =  0,
    CMD_STATUS_SUCCESS            =  1,
    CMD_STATUS_UNKNOWN_CMD        =  2,
    CMD_STATUS_UNKNOWN_IE         =  3,
    CMD_STATUS_REJECT_MEAS_SG_ACTIVE =  11,
    CMD_STATUS_RX_BUSY            = 13,
    CMD_STATUS_INVALID_PARAM      = 14,
    CMD_STATUS_TEMPLATE_TOO_LARGE = 15, 
    CMD_STATUS_OUT_OF_MEMORY      = 16, 
    CMD_STATUS_STA_TABLE_FULL     = 17,
    CMD_STATUS_RADIO_ERROR        = 18,
    CMD_STATUS_WRONG_NESTING      = 19,
    CMD_STATUS_TIMEOUT            = 21, /* Driver internal use.*/
    CMD_STATUS_FW_RESET           = 22, /* Driver internal use.*/
    CMD_STATUS_TEMPLATE_OUT_OF_TEMPORARY_MEMORY = 23,
    CMD_STATUS_NO_RX_BA_SESSION   = 24,
    CMD_GENERAL_STATUS_ERROR      = 25,
    CMD_WRONG_STATE               = 26,
    MAX_COMMAND_STATUS            = 0x7FFF
} CommandStatus_e;

/******************************************************************************/

/******************************************************************************

    ID:       CMD_REMAIN_ON_CHANNEL
    Desc:     Command remain on channel

******************************************************************************/
/**
 * struct ROCParameters_t - Command remain on channel
 *
 * @roleID:         role ID
 *
 * @Channel:        Channel
 *
 * @Band:           Channel band
 *
*/
typedef struct __PACKED__
{
    RoleID_t                roleID;
    Channel_e               Channel;            /* Channel */ //should be removed in the future
    uint8_t /*RadioBand_e*/ Band;               /* Band */ //should be removed in the future
    uint8                   padding[1];
} ROCParameters_t;


/****************************** Upper MAC sub dispatcher ***********************/
/******************************************************************************

    ID:       CMD_UPPER_MAC_COMMANDS
    Desc:     Sub dispatcher for the upper mac

******************************************************************************/
typedef enum
{
    WLAN_START,
    WLAN_STOP,
    WLAN_ROLE_UP,
    WLAN_ROLE_DOWN,
    WLAN_SCAN,
    WLAN_CONNECT,
    WLAN_DISCONNECT,
    WLAN_GET,
    WLAN_SET,
    WLAN_GET_PS,
    WLAN_SET_PS,
    WLAN_CMD_MAX
}UpperMacCommandID_e;



/**
 * struct UpperMacCommand_t - upper mac sub dispatcher
 *
 * @uppermacCommandID:         upper mac command ID
 * @params:                    parameters of the specific command
 *
*/
typedef struct
{
    uint32 uppermacCommandID;
    uint8_t params[];
}UpperMacCommand_t;

typedef struct
{
    int internalStatus;
    void *params;
}UpperMacReturnCommand_t;


/****************************** Upper MAC sub dispatcher - END ***********************/


/****************************** BLE sub dispatcher - Start ***********************/
/******************************************************************************
* ** ***                                                               *** ** *
* ** ***                          BLE CMD                              *** ** *
* ** ***                                                               *** ** *
*******************************************************************************/
typedef  struct __PACKED__
{
    uint8       BdAddr[6];
    uint8_t     padding[2];
} SetBdAddrParam_t;

typedef struct __PACKED__
{
    uint16_t cmdLen;
    uint8_t cmdData[];
} BleCommandParams_t;
/****************************** BLE sub dispatcher - End ***********************/


/******************************************************************************

    ID:       CMD_START_SECURITY_MGMT_SEQ
    Desc:     Command start security management sequence

******************************************************************************/
/**
 * struct StartMgmtSeqParameters_t - start security management sequence
 *
 * @roleID:         role ID
 *
*/
typedef struct __PACKED__
{
    RoleID_t    roleID;
    uint8       padding[3];
} StartMgmtSeqParameters_t;

/******************************************************************************

    ID:       CMD_STOP_SECURITY_MGMT_SEQ
    Desc:     Command stop security management sequence

******************************************************************************/
/**
 * struct StopMgmtSeqParameters_t - stop security management sequence
 *
 * @roleID:         role ID
 *
*/
typedef struct __PACKED__
{
    RoleID_t    roleID;
    uint8       padding[3];
} StopMgmtSeqParameters_t;


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
typedef struct __PACKED__
{
/* 4 bytes */
    uint8_t          lid;
    uint8_t/*LidKeyType_e*/    lidKeyType;
    uint8_t           keyId;

    uint8_t           reserved;
/* 4 bytes */
    uint16_t/*KeyAction_e*/   action;
    uint8_t/*KeySize_e*/      keySize;
    uint8_t /*CipherSuite_e*/   cipher_type;

/* 32 bytes */
    uint8_t           key[MAX_KEY_SIZE];

/* 2 bytes */
    uint16_t          AcSeqNum16;

/* 4 bytes */
    uint32_t          AcSeqNum32;

} SetKey_t;

/******************************************************************************

    ID:       CMD_CHANNEL_SWITCH
    Desc:     This command instructs the WiLink to switch serving channel at the given
              time. Once the channel switch is performed, the Channel Switch Complete
              event is raised to the host.  
    Params:   ChannelSwitchStartParameters_t - see below.

******************************************************************************/
typedef struct __PACKED__
{
    RoleID_t                RoleID;                 /* The role ID */
    Channel_e               channel;                /* The new serving channel */
    uint8                   switchTime;             /* Number of beacons on the serving channel until the channel switch */
    Bool_e                  stopTx;                 /* Stop the role TX, should expect it after radar detection on the channel */
    uint32                  local_supported_rates;
    uint8                   channel_type;             /* Number of beacons on the serving channel until the channel switch */
    uint8_t /*RadioBand_e*/ band;
    uint8_t                 isDfsChannel;
    uint8                   padding[2];

} ChannelSwitchStartParameters_t;

/******************************************************************************

    ID:       CMD_STOP_CHANNEL_SWITCH
    Desc:     This command instructs the WiLink device to cancel performing a 
              pending channel switch event command. 
    Params:   None.
    
******************************************************************************/
typedef struct __PACKED__
{
    RoleID_t        RoleID;                 /* The role ID */
    uint8           viaStopRole;
    uint8           padding[2];
} ChannelSwitchStopParameters_t;

/******************************************************************************

    ID:       CMD_ADD_PEER
    Desc:     This command is used when working as AP. It adds a new station to
              the links context database.
    Params:   See AddPeer_t.
    
******************************************************************************/
/**
 * struct AddLink_t - This structure is used for adding new link
 *                    to existing role. Can be used locally
 *                    by FW (for example adding link to station role),
 *                    or externally (for example adding new peer to AP role).
 *
 * @roleID:           Id of the local role owing this link
 *
 * @roleType:         Type of the local role owing this link
 *
 * @linkType:         Type of the new link
 *
*/
typedef struct __PACKED__
{
    RoleID_t               roleID;
    uint8_t/*RoleType_e*/  roleType;
    uint8_t/*linkType_e*/  linkType;
} AddLink_t;

/**
 * struct ConfigureLink_t -  Configuration for new link. Can be used locally
 *                           by FW (for example adding link to station role),
 *                           or externally (for example adding new peer to AP role).
 *
 * @macAddress:           Peer address
 *
 * @AID:                  AID (our AID for station role, peer AID for AP link)
 *
 * @PSDType:              PS type per AC
 *
 * @supportedRatesBM:     Bitmask of supported rates in terms of RateIndex_e
 *
 * @BSSIndex:             BSS index ( should removed in the future? )
 *
 * @WMM:                  WMM enable/disable
 *
 * @htCapabilities:       HT capabilities
 *
 * @ampduParams:          AMPDU parametes
*/
typedef struct __PACKED__
{
    uint8       macAddress[MAC_ADDR_LEN];
    uint16       AID;
    uint8_t/*PSScheme_e*/  PSDType[NUM_ACCESS_CATEGORIES];
    uint32      supportedRatesBM;
    uint8       BSSIndex;
    uint8       SPLen;
    Bool_e      WMM;

    // 03.02.16 Added HT capabilities to link configuration
    // HT capabilities & AMPDU parameters are handled in WL8 FW in Links_WriteHtPeerCap
    // ToDo missing handling in links module
    uint32      htCapabilities;
    uint8       ampduParams;
    
    Bool_e      has_he;
#ifndef THICK_MAC_COMPILE
    Bool_e      mfp;
    uint8       padding[2];
#endif
} ConfigureLink_t;

/**
 * struct AddPeer_t - Used for adding new peer in AP mode.
 *                    Include both structures above.
 *
 * @addPeer:          Add peer info
 *
 * @configurePeer:    Peer configuration info
 *
*/
typedef struct __PACKED__
{
    AddLink_t       addPeer;
    ConfigureLink_t configurePeer;
} AddPeer_t;

/**
 * struct AddPeer_t - Holds peer parameters + connection state indication which is used by WLAN
 *                    services to set link state.
 *
 * @isConnected:      Connected state
 *
 * @peerInfo:         Peer information
 *
*/
typedef struct __PACKED__ AddPeerCmd_t 
{
    Bool_e    isConnected;
    AddPeer_t peerInfo;
    struct AddPeerCmd_t *next; //Used only by the cc33xx driver to keep a linked list of commands.
                               //Commands are allocated when Supplicant calls .sta_add but are buffered and then being sent to FW
                               //only when Supplicant calls .sta_set_flags.
                               //Note: .sta is called before sending the assoc response, maybe this is the reason we delay the add peer(?)
} AddPeerCmd_t;

/**
 * struct AddPeerReturn_t - Add peer command complete parameters
 *
 * @linkId:       Link ID
 *
 * @sessionId:    Session ID
 *
*/
typedef struct __PACKED__
{
    uint8       linkId;
    uint8       sessionId;

}AddPeerReturn_t;

/******************************************************************************

    ID:       CMD_REMOVE_PEER
    Desc:     This command is used will cause the FW to send de-authentication 
              packet to a STA (if the driver asks for it), and remove the STA's
              context from the FW's database.
    Params:   See RemovePeer_t.
    
******************************************************************************/
/**
 * struct RemovePeer_t - Remove peer command
 *
 * @linkId:       Link ID
 *
 * @roleID:       role ID
 *
*/
typedef struct __PACKED__
{
    uint8 linkID;
    RoleID_t roleID;
} RemovePeer_t;


/******************************************************************************

    ID:       CMD_SET_LINK_CONNECTION_STATE
    Desc:     This command is used to set the link state.
    Params:   See SetLinkConnectionState_t.

******************************************************************************/
/**
 * struct SetLinkConnectionState_t - Command set link connection state
 *
 * @flid:               Link ID
 *
 * @connectionState:    Connection state
 *
*/
typedef struct __PACKED__
{
    uint8 flid;
    uint8_t /*LinkState_e*/ connectionState;
} SetLinkConnectionState_t;


/******************************************************************************
* ** ***                                                               *** ** *
* ** ***                          ROLE API                             *** ** *
* ** ***                                                               *** ** *
*******************************************************************************/

/******************************************************************************
        ID:     CMD_ROLE_ENABLE
        Desc:   This command adds a new role to Role DB. The role will be
                identified in further commands by Role ID.
        Return: roleID
******************************************************************************/
/**
 * struct RoleEnableParameters_t - Role Enable Parameters
 *
 * @roleType:        Role type
 *
 * @macAddress:      MAC address - configured per role type
*/
typedef struct __PACKED__
{
    uint8_t/*RoleType_e*/          roleType;
    uint8                          macAddress[MAC_ADDR_LEN];
    uint8                          staRoleIdx; // relevant for sta role type
} RoleEnableParameters_t;


/**
 * struct RoleEnableReturn_t- Role Enable return Parameters
 *
 * @roleID:         Role ID
*/
typedef struct __PACKED__
{
    RoleID_t          roleID;
} RoleEnableReturn_t;
/*****************************************************************************/

/******************************************************************************
        ID:     CMD_ROLE_DISABLE
        Desc:   This command disable a (previously started) role,
        Return: CMD_COMPLETE
******************************************************************************/
typedef struct __PACKED__
{
    RoleID_t            roleID;
} RoleDisableParameters_t;
/*****************************************************************************/

/******************************************************************************
        ID:     CMD_ROLE_STOP
        Desc:   This command stops a (previously started) role,
                so the F/W can on longer select to activate it.
        Return: CMD_COMPLETE
******************************************************************************/
/**
 * struct RoleStopParameters_t- Role Stop Parameters
 *
 * @roleID:          Role ID
*/
typedef struct __PACKED__
{
    RoleID_t           roleID;
} RoleStopParameters_t;

/******************************************************************************
        ID:     CMD_ROLE_START
        Desc:   This command starts (a previously enabled) role. Started roles
                are selected by the F/W (one at a time on a time sharing basis)
                to be activated. Therefore, the actual activation of the newly
                started role can take place either immediately or in a later
                event on the time line, depends on other started roles.
        Return: linkID
******************************************************************************/

/******************************************************************************
                           station specific
******************************************************************************/
/**
 * struct RoleStartParameters_t- Role Start Parameters
 *
 * @bssId:                      bssid
 *
 * @session:                    Session ids -  It should be saved in the linkd DB.
 *
 * @basicRateSetBM:             Basic rates
 *
 * @localSupportedRatesBM:      Local rates
 *
 * @remotePeerSupportedRatesBM: Supported rates
 *
 * @ssid:                       SSID structure - type, length and, ssid
 *
 * @beaconInterval:             Beacon interval
*/
typedef struct __PACKED__
{
    uint8           bssId[MAC_ADDR_LEN];
    uint32          remotePeerSupportedRatesBM;
    uint32          basicRateSetBM;
    uint32          localSupportedRatesBM;
    RoleSsid_t      ssid;
    uint16          beaconInterval;
} RoleStartStaBasedParameters_t;
/**
 * struct RoleStartStaBasedReturn_t- Role Start Station based return parameters
 *
 * @linkId:                      Link ID
 *
 * @session:                     Session ID
*/
typedef struct __PACKED__
{
    uint8           linkId;
    uint8           session;
} RoleStartStaBasedReturn_t;
/******************************************************************************
                           Device specific
******************************************************************************/
typedef struct __PACKED__
{
    uint8               reserved[56];
} RoleStartDeviceParameters_t;

/******************************************************************************
                           AP specific
******************************************************************************/
/**
 * struct RoleAPBasedParameteres_t- Role Start AP based parameters
 *
 * @beaconInterval:         Beacon interval
 *
 * @basicRateSetBM:         Basic rate
 *
 * @localSupportedRatesBM:  Local supported rate
 *
 * @dtimInterval:           DTIM interval
 *
 * @WMM:                    WMM enable/disable
*/
typedef struct __PACKED__
{

    uint16       beaconInterval;
    uint32       basicRateSetBM;
    uint32       localSupportedRatesBM;
    uint8        dtimInterval;

    Bool_e       WMM;

} RoleAPBasedParameteres_t;

/**
 * struct RoleStartApBasedReturn_t- Role Start AP based return parameters
 *
 * @globalHLID:         Global Link ID
 *
 * @broadcastHLID:      Broadcast Link ID
 *
 * @globalSession:      Global Session ID
 *
 * @broadcastSession:   Broadcast Session ID
*/
typedef struct __PACKED__
{
    uint8           globalHLID;
    uint8           broadcastHLID;

    uint8           globalSession;
    uint8           broadcastSession;
} RoleStartApBasedReturn_t;

/******************************************************************************/
/**
 * union RoleStartReturnParameters_t - external return param per device
 *
 * @staBased:        Station type
 *
 * @apBased:         AP type
 *
 * @device:          Device type
*/
typedef struct __PACKED__
{
    union
    {
        RoleStartStaBasedReturn_t       staBased;
        RoleStartApBasedReturn_t        apBased;
    }u;
}RoleStartReturnParameters_t;


/**
 * union RoleStartExtendedParameters_u - external param per device
 *
 * @staBased:        Station type
 *
 * @apBased:         AP type
 *
 * @device:          Device type
*/
typedef union
{
    RoleStartStaBasedParameters_t   staBased;
    RoleAPBasedParameteres_t        apBased;
    RoleStartDeviceParameters_t     device;
} RoleStartExtendedParameters_u;
/******************************************************************************/

/**
 * struct RoleStartParameters_t- Role Start Parameters
 *
 * @roleID:          Role ID - return value
 *
 * @roleType:        Role type
 *
 * @band:            2.4Ghz/5Ghz/6Ghz
 *
 * @channelNumber    Channel of the start role
 *
 * @bandwidth        Band width - 20/40 Mhz
*/
typedef struct __PACKED__
{
    RoleID_t                        roleID;
    uint8_t/*RoleType_e*/           roleType;

    // RF related
    uint8_t /*RadioBand_e*/         band;
    Channel_e                       channelNumber;
    uint8_t                         isDfsChannel;
    uint8_t/*BandWidthSettings_e */ bandwidth;

    // Role related parameters
    RoleStartExtendedParameters_u   ex;
} RoleStartParameters_t;

/*****************************************************************************/



/******************************************************************************
* ** ***                                                               *** ** *
* ** ***                          SCAN API                             *** ** *
* ** ***                                                               *** ** *
*******************************************************************************/
/******************************************************************************
        ID:     CMD_SCAN
        Desc:   This command will start scan process depending scan request
                type
        Return: CMD_COMPLETE
******************************************************************************/
/**
* struct ConnScanSSID_t - SSIDs connection scan description
*
* @ssidType:    SSID type - SCAN_SSID_TYPE_HIDDEN/SCAN_SSID_TYPE_PUBLIC
*
* @secType:     NONE - no security type in configured, other -  the secuirty type
*
* @ssidLength:  length of the ssid
*
* @ssid:        the SSID
*/
typedef struct __PACKED__
{
    uint8 /*SsidType_e*/ ssidType;
    uint8               ssidLength;
    uint8               ssid[32];
    uint8               padding[2];
} ConnScanSSID_t;

/**
 * struct ConnScanSSIDList_t - scan SSID list description
 *
 * @numOfSSIDEntries:   Number of SSID in the list. MAX 16 entries
 *
 * @SSIDList:           SSIDs to scan for (active scan only)
*/
typedef struct __PACKED__
{
    uint8               numOfSSIDEntries;
    ConnScanSSID_t      *SSIDList;
} ConnScanSSIDList_t;

/**
 * struct configureSSID_t - SSID list description
 *
 * @numOfSSIDEntries:   Number of SSID in the list. MAX 16 entries
 *
 * @SSIDList:           SSIDs to scan for (active scan only)
*/

typedef struct __PACKED__
{
    uint8                   roleid;
    uint8                   scantype;
    uint8                   numofSsids;
    ConnScanSSID_t          ssid_list[CONN_SCAN_MAX_NUMBER_OF_SSID_ENTRIES];
    uint8                   padding;
} configureSSID_t;
/**
 * struct ChannelDwellInfo_t - Channels duration info per band
 *
 * @scanMinDuration:        Min duration (in ms)
 *
 * @scanMaxDuration:        Max duration (in ms)
 *
 * @passiveScanDuration:    Duration to use for passive scans (in ms)
*/
typedef struct __PACKED__
{
    uint16  scanMinDuration;
    uint16  scanMaxDuration;
    uint16  passiveScanDuration;
} ChannelDwellInfo_t;

/**
 * struct ChannelInfo_t - Channels info
 *
 * @channel:            channel number (channel_e)
 *
 * @txPowerLevelDbm:    TX power level in dbm
 *
 * @channelFlags:       0 - DFS channel, 1 - DFS enabled (to be included in active scan)
*/
typedef struct __PACKED__
{
    uint8   channel;
    uint8   txPowerLevelDbm;
    uint8   channelFlags;
} ChannelInfo_t;

/**
 * struct oneShotScanParams_t - ONE_SHOT scan param
 *
 * @numOfPassive:           Number of passive scan channels in bands BG,A
 *
 * @numOfActive:            Number of active scan channels in bands BG,A
 *
 * @numOfDfs:               number of DFS channels in A band
 *
 * @channelList:            Channel list info
 *                          channels that are belonged to BG band are set from place 0 and forward.
 *                          channels that are belonged to A band are set from place CONN_SCAN_MAX_CHANNELS_BG (14) and forward.
 *                          channels that are belonged to 6Ghz band are set from place
 *                          CONN_SCAN_MAX_CHANNELS_A_BG(14+32) and forward.
 * @dwellCfg                Scan duration time info per band
 *
 * @scanResultsFilterCfg    Scan results filtering configuration
 *                          SCAN_RESULTS_PASS_ALL | SCAN_RESULTS_PASS_WPS | SCAN_RESULTS_PASS_P2P
*/
typedef struct __PACKED__
{
    uint8                   numOfPassive[CONN_SCAN_MAX_BAND];
    uint8                   numOfActive[CONN_SCAN_MAX_BAND];
    uint8                   numOfDfs[1];
    ChannelInfo_t           channelList[ CONN_SCAN_MAX_CHANNELS_ALL_BANDS ];
    ChannelDwellInfo_t      dwellCfg[CONN_SCAN_MAX_BAND];
    uint8_t/*scanResultsFilterCfg_e*/  scanResultsFilterCfg;
} oneShotParams_t;

/**
 * sched_scan_plans - Scan plans for scheduled scan
 *
 * Each scan plan consists of the number of iterations to scan and the
 * interval between scans. When a scan plan finishes (i.e., it was run
 * for the specified number of iterations), the next scan plan is
 * executed. The scan plans are executed in the order they appear in
 * the array (lower index first). The last scan plan will run infinitely
 * (until requested to stop), thus must not specify the number of
 * iterations. All other scan plans must specify the number of
 * iterations.
 */
typedef struct
{
     uint32 interval; /* In seconds */
     uint32 iterations; /* Zero to run infinitely */
}osprey_sched_scan_plan_t;

/**
 * struct periodicScanParams_t - Periodic scan param
 *
 * @sched_scan_plans:       Scan plans for a scheduled scan (defined in supplicant's driver.h)
 *                          interval and iterations
 *
 * @sched_scan_plans_num    Number of scan plans in sched_scan_plans array
 *
 * @numOfPassive:           Number of passive scan channels in bands BG,A
 *
 * @numOfActive:            Number of active scan channels in bands BG,A
 *
 * @numOfDfs:               number of DFS channels in A band
 *
 * @channelList:            Channel list info
 *                          channels that are belonged to BG band are set from place 0 and forward.
 *                          channels that are belonged to A band are set from place CONN_SCAN_MAX_CHANNELS_BG (14) and forward.
 *                          channels that are belonged to 6Ghz band are set from place
 *                          CONN_SCAN_MAX_CHANNELS_A_BG(14+32) and forward.
 * @dwellCfg                Scan duration time info per band
 *
*/
typedef struct __PACKED__
{
    osprey_sched_scan_plan_t sched_scan_plans[SCAN_MAX_SCHED_SCAN_PLANS];
    uint16                   sched_scan_plans_num;
    uint8                    numOfPassive[CONN_SCAN_MAX_BAND];
    uint8                    numOfActive[CONN_SCAN_MAX_BAND];
    uint8                    numOfDfs[1];
    ChannelInfo_t            channelList[ CONN_SCAN_MAX_CHANNELS_ALL_BANDS ];
    ChannelDwellInfo_t       dwellCfg[CONN_SCAN_MAX_BAND];
} periodicParams_t;

/**
 * struct ScanParams_t - union for ONE_SHOT/PERIODIC scan param
 *
 * @tScanInfo:          ONE_SHOT scan param
 *
 * @tConnScanInfo       Periodic scan param
*/
typedef struct __PACKED__
{
    union
    {
        oneShotParams_t     tScanInfo;
        periodicParams_t    tConnScanInfo;
    } u;
} ScanParams_t;

/**
 * struct ScanReqStartCmdParam_t - scan configured param
 *
 * @scanParams:         Scan parameter for ONE_SHOT/PERIODIC Scan
 *
 * @roleID:             role ID
 *
 * @scanRequestType:    ONE_SHOT/PERIODIC scan
 *
 * @ssidList:           List of SSIDs entries.
 *
 * @rssiThreshold:      RSSI threshold for basic filter
 *
 * @snrThreshold:       SNR threshold for basic filter
 *
 * @useList:            0 - if there is more than 5 SSIDs entries, 1 - else
 *
 * @ssidRXFilter:       0 - not using filter and all the beacons/probe response frame
 *                      forward to upper mac,  1 - using filter
*/
typedef struct __PACKED__
{
    uint8_t/*EScanRequestType*/        scanRequestType;
    RoleID_t                roleID;
    ScanParams_t            scanParams;
    int8                    rssiThreshold;
    int8                    snrThreshold;
    uint8                   bssid[6];
    uint8                   pad[2];
    uint8                   useList;
    uint8                   ssidRXFilter;
    uint8                   numOfSSIDEntries;
}ScanReqStartCmdParam_t;

/******************************************************************************
        ID:     CMD_STOP_SCAN
        Desc:   This command will stop scan process depending scan request
                type, and if early termination is on
        Return: CMD_COMPLETE
******************************************************************************/
/**
 * struct ScanStopCmdParam_t - scan stop param
 *
 * @scanRequestType:    Scan request type
 *
 * @roleId:             role ID
 *
 * @isET:               TRUE - Early termination is on, FALSE - no ET
*/
typedef struct __PACKED__
{
    uint8_t/*EScanRequestType*/        scanRequestType;
    RoleID_t                roleId;
    Bool_e                  isET;
}ScanStopCmdParam_t;

/******************************************************************************
        ID:     CMD_SET_PROBE_IE
        Desc:   This command will  set the Info elements data for
                probe request
        Return: CMD_COMPLETE
******************************************************************************/
/**
 * struct IesScanProbeReq_t - Probe request info elements
 *
 * @scanRequestType:    ONE_SHOT/PERIODIC scan
 *
 * @roleID       roleID
 *
 * @iesBuffer:          info element buffer
 *
 * @iesLen:             info element length
*/
typedef struct __PACKED__
{
    uint8_t/*EScanRequestType*/  scanRequestType;
    RoleID_t                roleID;
    uint16_t                iesLen;
    uint8_t                  iesBuffer[MAX_EXTRA_IES_LEN];
} IesScanProbeReq_t;


/******************************************************************************/

/******************************************************************************

    ID:       CMD_AP_SET_BEACON_INFO
    Desc:     This command is used to set beacon template

******************************************************************************/
/**
 * struct SetBeaconInfo_t - Set Beacon info command
 *
 * @roleID:        Role ID
 *
 * @beacon_len:    Beacon info length
 *
 * @beacon:        Beacon info
 *
*/
typedef struct __PACKED__
{
    RoleID_t    roleID;
    uint16      beacon_len;
    uint8       beacon[MAX_SIZE_BEACON_TEMP];
} SetBeaconInfo_t;


/******************************************************************************
        ID:     CMD_SEND_DEAUTH_DISASSOC
        Desc:   This command is used to send deauthentication/dissociation
                from the Host/Driver to FW.
******************************************************************************/
/**
 * struct SendDeauthDisassocParameters_t - Command send deauth/disassoc
 *
 * @roleID:     role ID
 *
 * @destAddr:   Destination address
 *
 * @frameType:  frame type
 *
 * @reason:     deauth/disassoc reason
*/
typedef struct __PACKED__
{
    RoleID_t            roleID;
    uint8               destAddr[MAC_ADDR_LEN]; // Destination Address
    uint32              frameType;
    uint16              reason;

} SendDeauthDisassocParameters_t;

/******************************************************************************
        ID:     CMD_SCHED_STATE_EVENT
        Desc:   This command is used to send scheduler state event
******************************************************************************/
/**
 * struct SchedStateEventParameters_t - Command send scheduler state event
 *
 * @roleID:     role ID
 *
 * @event:      event
*/
typedef struct __PACKED__
{
    RoleID_t            roleID;
    uint8               event; //schedStateEvent_e
    uint8               padding[2];
} SchedStateEventParameters_t;

/******************************************************************************
* ** ***                                                               *** ** *
* ** ***                    CONFIGURATION                              *** ** *
* ** ***                                                               *** ** *
*******************************************************************************/
/**
 * enum Cfg_e - Configuration id
 *
 * @CTS_PROTECTION_CFG: Configure ERP Protection Mode for an associated STA,
 *                      handled by the Driver
 *
 * @TX_PARAMS_CFG: Configures the TX parameters
 *
 * @ASSOC_INFO_CFG: Configurations that are set after association
 *
 * @PEER_CAP_CFG:   Configures HT/HE peer capabilities
 *
 * @BSS_OPERATION_CFG: Configures HT/HE bss capabilities
 *
 * @SLOT_CFG:          Configures slot time
 *
 * @PREAMBLE_TYPE_CFG  Sets preamble type - SHORT/LONG
*/
typedef enum
{
	CTS_PROTECTION_CFG              = 0,
    TX_PARAMS_CFG                   = 1,
    ASSOC_INFO_CFG                  = 2,
    PEER_CAP_CFG                    = 3,
    BSS_OPERATION_CFG               = 4,
    SLOT_CFG                        = 5,
    PREAMBLE_TYPE_CFG               = 6,
    DOT11_GROUP_ADDRESS_TBL         = 7, 
    BA_SESSION_RX_SETUP             = 8,
    ACX_SLEEP_AUTH                  = 9,    
    STATIC_CALIBRATION_CFG          = 10,
    AP_RATES_CFG                    = 11,
    SET_ANTENNA_SELECT_CFG          = 13,
    TX_POWER_CFG                    = 14,
    VENDOR_IE_CFG                   = 15,
    START_COEX_STATISTICS_CFG       = 16,
    BEACON_FILTER_OPT			    = 17,
	BEACON_FILTER_TABLE             = 18,
	ACX_ENABLE_RX_DATA_FILTER       = 19,
	ACX_SET_RX_DATA_FILTER          = 20,
	ACX_GET_DATA_FILTER_STATISTICS  = 21,
    TWT_SETUP                       = 22,
    TWT_TERMINATE                   = 23,
    TWT_SUSPEND                     = 24,
    TWT_RESUME                      = 25,
    ANT_DIV_ENABLE                  = 26,
	ANT_DIV_SET_RSSI_THRESHOLD      = 27,
    ANT_DIV_SELECT_DEFAULT_ANTENNA  = 28,
    RESET_DECRYPT_PACKETS_COUNT     = 29,
    ENABLE_CHANNEL_UTILIZATION_NEXT_SCAN = 30,

    LAST_CFG_VALUE                  ,
    MAX_DOT11_CFG = LAST_CFG_VALUE  ,

    MAX_CFG = 0xFFFF   /*force enumeration to 16bits*/
} Cfg_e;

/**
 * enum cmdDebug_e - Debug Configuration id
*/
typedef enum
{
    UPLINK_MULTI_USER_CFG       ,
    UPLINK_MULTI_USER_DATA_CFG  ,
    OPERATION_MODE_CTRL_CFG     ,
    UPLINK_POWER_HEADER_CFG     ,
    MCS_FIXED_RATE_CFG          ,
    GI_LTF_CFG                  ,
    TRANSMIT_OMI_CFG            ,
    TB_ONLY_CFG                 ,
    BA_SESSION_CFG              ,
	FORCE_PS_CFG                ,
	RATE_OVERRRIDE_CFG			,
	BLS_CFG                     ,
    BLE_ENABLE                  ,
    SET_TSF                     ,
    RTS_TH_CFG                  ,
    LINK_ADAPT_CFG              ,
    CALIB_BITMAP_CFG            ,
    PWR_PARTIAL_MODES_CFG       ,
    TRIGGER_FW_ASSERT           ,
    BURST_MODE_CFG              ,
    LAST_DEBUG_VALUE                  ,
    MAX_DOT11_DEBUG = LAST_DEBUG_VALUE  ,

}cmdDebug_e;

/******************************************************************************
        ID:     CTS_PROTECTION_CFG
        Desc:   Configure ERP Protection Mode for an associated STA,
                handled by the Driver
        Type:   Configuration
******************************************************************************/
/**
 * struct CtsProtectionCfg_t - Command configure -  ERP Protection
 *
 * @roleID:                 Role ID
 *
 * @erpProtectionEnabled:   This field is a flag enabling or disabling the
 *                          CTS-to-self protection mechanism:
 *                          FALSE - disable, TRUE - enable
*/
typedef struct __PACKED__
{
    RoleID_t          roleID;
    Bool_e            erpProtectionEnabled;
}CtsProtectionCfg_t;

/******************************************************************************
        ID:     TX_PARAMS_CFG
        Desc:   Configures the TX parameters for a specific access category.
        Type:   Configuration
******************************************************************************/
/**
 * struct heMuEdcaParam_t - MU EDCA parameters
 *
 * @aifs:                 The AIF value (in slots) for the access class
 *
 * @ecw_min_max:          4 lower bit - minimum windows size,
 *                        4 higher bit - maximum windows size.
 *
 * @mu_edca_timer:        MU EDCA timer
*/
typedef struct __PACKED__
{
    uint8   aifs;
    uint8   ecw_min_max;
    uint8   mu_edca_timer;

}heMuEdcaParam_t;

/**
 * struct TxParamCfg_t - Command configure
 *
 * @roleID:         Role ID
 *
 * @ac:             Access Category - The TX queue's access category
 *
 * @aifsn:          The AIF value (in slots) for the access class
 *
 * @cwMin:          The contention window minimum size (in slots) for
 *                  the access class
 *
 * @cwMax:          The contention window maximum size (in slots) for
 *                  the access class
 *
 * @txopLimit:      The TX OP Limit (in microseconds) for the access class
 *
 * @acm:            Admission control mandatory required
 *
 * @psScheme:       The power save scheme of the link. in our implementation
 *                  all AC queues uses the same power scheme
 *
 * @isMuEdca        is MU EDCA configured
 *
 * @muEdca:         MU EDCA parameters
*/
typedef struct __PACKED__
{
    RoleID_t             roleID;

    uint8                ac;
    uint8                aifsn;
    uint8                cwMin;

    uint16               cwMax;
    uint16               txopLimit;
    uint16               acm;

    uint8_t/*PSScheme_e*/           psScheme;

    Bool_e               isMuEdca;
    heMuEdcaParam_t      muEdca;

}TxParamCfg_t;

/******************************************************************************
        ID:     ASSOC_INFO_CFG
        Desc:   This command will include only configurations that are
                set after association, and that are not change during the
                lifetime of the connection
        Type:   Configuration
******************************************************************************/
/**
 * struct TxParamCfg_t - Command configure
 *
 * @roleID:          Role ID
 *
 * @aid:             Access Category - The TX queue's access category
 *
 * @wmeEnabled:      TRUE - wmm enabled, FALSE - wmm disabled
 *
 * @nonTransmitted:  TRUE - connected to non TX BSSID AP, False - multiple bssid disabled
 *
 * @bssidIndex:      Multiple BSSID Index
 *
 * @bssidIndicator:  BSSID Indicator - 2^n is the maximum number of BSSIDs in the Multiple BSSID set
 *
 * @transBssid:      MAC Address of Transmitting BSSID AP
 *
 */
typedef struct __PACKED__
{
    RoleID_t        roleID;
    uint16          aid;
    Bool_e          wmeEnabled;
    Bool_e          nonTransmitted;
    uint8           bssidIndex;
    uint8           bssidIndicator;
    uint8           transBssid[MAC_ADDR_LEN];
    Bool_e          ht_supported;
    Bool_e          vht_supported;
    Bool_e          has_he;
    //uint8_t         padding[3]; total size of struct in bits should be a multiple of 32 incase not add padding 
}AssocInfoCfg_t;

/******************************************************************************
        ID:     PEER_CAP_CFG
        Desc:   Configures HT/HE peer capabilities
        Type:   Configuration
******************************************************************************/
/**
 * struct htPeerCap_t - HT peer capabilities configuration
 *
 * @htCapabilites:      HT capabilities
 *
 * @uAmpduMaxLength:    This the maximum a-mpdu length supported by the AP.
 *                      The FW may not exceed this length when sending A-MPDUs
 *
 * @uAmpduMinSpacing:   This is the minimal spacing required when sending A-MPDUs to the AP.
*/
typedef struct __PACKED__
{
    uint32 htCapabilites;      /*
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


     uint8  uAmpduMaxLength;




     uint8  uAmpduMinSpacing;


} htPeerCap_t;

/**
 * struct hePeerCap_t - HE peer capabilities configuration
 *
 * @heMacCap:               HE capabilities
 *
 * @nominalPacketPadding:   Nominal packet padding value, used for determining
 *                          the packet extension duration
 *
 * @peerHeSupport:          HE peer support
*/
typedef struct __PACKED__
{
    uint32 heMacCap[2];
    uint8  nominalPacketPadding;    /* From the PHY capabilities element we only need the nominalPacketPadding. */
                                    /* In case more PHY parameters will be required                             */
                                    /* consider sending the entire hePhyCapabilities_t to the post association. */
    uint8  peerHeSupport;
} hePeerCap_t;

/**
 * struct PeerCap_t - Peer Cap
 * can be declared by an AP and a STA, included HT and HE cap,
 * currently only MAC Cap for HE
 *
 * @htPeerCap:          HT peer capabilities structure
 *
 * @hePeerCap:          HE peer capabilities structure
 *
 * TODO: gilsho, if we need more the MAC change to structure htPeerCap_t and add MAC and PHY is needed
 */
typedef struct __PACKED__
{
    htPeerCap_t             htPeerCap;
    hePeerCap_t             hePeerCap;
} PeerCap_t;

/**
 * struct PeerCapCfg_t - Command configure
 *
 * @roleID:                 Role ID
 *
 * @supportedRatesBM:       Bitmask of supported rates in terms of RateIndex_e
 *
 * @PeerCap_t:              Peer for HE and HT capability structure
*/
typedef struct __PACKED__
{
    RoleID_t        roleID;
    uint32          supportedRatesBM;
    PeerCap_t       peerCap;
}PeerCapCfg_t;

/******************************************************************************
        ID:     BSS_OPERATION_CFG
        Desc:   Configure HT/HE BSS operation parameters
        Type:   Configuration
******************************************************************************/
/*
*   HE BSS Cap - can be declared by an AP only
*   The operation of HE STAs in an HE BSS is controlled by the following:
*    the HT Operation element and the HE Operation element if operating in the 2.4 GHz band
*    the HT Operation element, VHT Operation element and the HE Operation element if operating in the 5 GHz band
*    The HE Operation element if operating in the 6 GHz band
*
*      ==================================================================================================================
*      | Element | Length | Element ID | HE         | BSS Color   | Basic      |  VHT         | Max Co-   | 6 GHz       |
*      | ID      |        | Extension  | Operation  | Information | HE-MCS And |  Operation   | Hosted    | Operation   |
*      |         |        |            | Parameters |             | NSS Set    |  Information | BSSID     | Information |
*      |         |        |            |            |             |            |              | Indicator |             |
*      ==================================================================================================================
*Octets:    1         1         1             3             1           2           0 or 3        0 or 1       0 or 4
*
*/

/**
 * struct heBssCap_t - HE BSS Cap
 *
 * @heOperationCfg:             HE BSS operation configuration
 *
 * @bssColorInfo:               HE BSS color info
 *
 * @bssBasicMcsSet:             HE BSS basic MCS set - for RX and TX
 *
 * @qosInfo_moreDataAckBit:     HE BSS QOS info
 *
 * TODO:gilsho, need to add VHY operation, may be in sync with the htBSS primary channel field, also optional relatively to bit 15 in heOperationCfg
 * TODO:gilsho, handle markers
 * TODO:gilsho, Should we add phy cap as well? ask oren if the parameters are configurable based on the AP behavior, if so need to add it to the post association
*/
typedef struct
{
    #define HE_OPERATION_MCS_OFFSET         4

    uint32      heOperationCfg;
    uint16      bssBasicMcsSet;
    uint8       qosInfo_moreDataAckBit;
} heBssCap_t;

/**
 * struct BssCap_t - Bss Cap
 * can be declared by an AP and a STA, included HT and HE cap
 *
 * @htCfgInBss:          HT BSS capabilities structure
 *
 * @heCfgInBss:          HE BSS capabilities structure
 *
*/
typedef struct __PACKED__
{
    htBssCap_t      htCfgInBss;
    heBssCap_t      heCfgInBss;
} BssCap_t;

/**
 * struct BssOperationCfg_t - Command configure
 *
 * @roleID:         Role ID
 *
 * @BssCap:         BSS for HE and HT capability structure
*/
typedef struct __PACKED__
{
    RoleID_t        roleID;
    BssCap_t        BssCap;
}BssOperationCfg_t;

/******************************************************************************
        ID:     SLOT_CFG
        Desc:   Configure slot time
        Type:   Configuration
******************************************************************************/
/**
 * struct SlotTimeCfg_t - Command configure
 *
 * @roleID:         Role ID
 *
 * @slotTime:       slot time
*/
typedef struct __PACKED__
{
    RoleID_t        roleID;
    uint8_t /*SlotTime_e*/      slotTime;
}SlotTimeCfg_t;

/******************************************************************************
        ID:     PREAMBLE_TYPE_CFG
        Desc:   Configure preamble type
        Type:   Configuration
******************************************************************************/
/**
 * struct SlotTimeCfg_t - Command configure
 *
 * @roleID:                     Role ID
 *
 * @shortBPreambleSupported:    Short preamble
 *                              TRUE - supported, FALSE, not supported
*/
typedef struct __PACKED__
{
    RoleID_t        roleID;
    Bool_e          shortBPreambleSupported;
}PreambleTypeCfg_t;

/******************************************************************************
        ID:     UPLINK_MULTI_USER_CFG 
        Desc:   Uplink Multiuser enable/disable
        Type:   Configuration
******************************************************************************/
/**
 * struct UplinkMUCfg_t - Command configure
 *
 * @enable_val:         enable/disable
*/
typedef struct __PACKED__
{ 
    uint8 enable_val;
    uint8 padding[3];
} UplinkMUCfg_t;
/******************************************************************************
        ID:     UPLINK_MULTI_USER_DATA_CFG 
        Desc:   Uplink Multiuser data enable/disable
        Type:   Configuration
******************************************************************************/
/**
 * struct UplinkMUDataCfg_t - Command configure
 *
 * @enable_val:         enable/disable
*/
typedef struct __PACKED__
{ 
    uint8 enable_val;
    uint8 padding[3];
} UplinkMUDataCfg_t;

/******************************************************************************
        ID:     OPERATION_MODE_CTRL_CFG 
        Desc:   Operation mode control enable/disable
        Type:   Configuration
******************************************************************************/
/**
 * struct OperModeCTRLCfg_t - Command configure
 *
 * @enable_val:         enable/disable
*/
typedef struct __PACKED__
{ 
    uint8 enable_val;
    uint8 padding[3];
} OperModeCTRLCfg_t;

/******************************************************************************
        ID:     UPLINK_POWER_HEADER_CFG 
        Desc:   Uplink power header enable/disable
        Type:   Configuration
******************************************************************************/
/**
 * struct UplinkPWRHDRCfg_t - Command configure
 *
 * @enable_val:         enable/disable
*/
typedef struct __PACKED__
{ 
    uint8 enable_val;
    uint8 padding[3];
} UplinkPWRHDRCfg_t;

/******************************************************************************
        ID:     MCS_FIXED_RATE_CFG 
        Desc:   MCS rate value
        Type:   Configuration
******************************************************************************/
/**
 * struct MSCRateCfg_t - Command configure
 *
 * @rate_val:         rate value
*/
typedef struct __PACKED__
{ 
    uint8 rate_val;
    uint8 padding[3];
} MSCRateCfg_t;

/******************************************************************************
        ID:     GI_LTF_CFG 
        Desc:   GI_LTF configured value
        Type:   Configuration
******************************************************************************/
/**
 * struct GiLtfCfg_t - Command configure
 *
 * @value:         value
*/
typedef struct __PACKED__
{ 
    uint8 value;
    uint8 padding[3];
} GiLtfCfg_t;

/******************************************************************************
        ID:     TRANSMIT_OMI_CFG 
        Desc:   Transmit OMI enable/disable
        Type:   Configuration
******************************************************************************/
/**
 * struct TransmitOMICfg_t - Command configure
 *
 * @enable_val:         enable/disable
*/
typedef struct __PACKED__
{ 
    uint8 enable_val;
    uint8 padding[3];
} TransmitOMICfg_t;
/******************************************************************************
        ID:     TB_ONLY_CFG 
        Desc:   TB only enable/disable
        Type:   Configuration
******************************************************************************/
/**
 * struct TBOnlyCfg_t - Command configure
 *
 * @enable_val:         enable/disable
*/
typedef struct __PACKED__
{ 
    uint8 enable_val;
    uint8 padding[3];
} TBOnlyCfg_t;

/******************************************************************************
        ID:     BA_SESSION_CFG 
        Desc:   Block ack session configure
        Type:   Configuration
******************************************************************************/
/**
 * struct BASessionCfg_t - Command configure
 *
 * @block_ack_rx:         block ack session rx
 * 
 * @block_ack_tx:         block ack session tx
*/
typedef struct __PACKED__
{ 
    uint8 block_ack_rx;
    uint8 block_ack_tx;
    uint8 padding[2];
} BASessionCfg_t;

/******************************************************************************
        ID:     BLS_CFG
        Desc:   Beacon Late Synchronization configure
        Type:   Configuration
******************************************************************************/
/**
 * struct BLSCfg_t - Command configure
 *
 * @enable_val:         enable/disable
*/
typedef struct __PACKED__
{
    uint8 enable_val;
    uint8 padding[3];
} BLSCfg_t;

/******************************************************************************
        ID:     LINK_ADAPT_CFG
        Desc:   Debug capabilities for link adaptation
        Type:   Configuration
******************************************************************************/
/**
 * struct LinkAdaptDebugCfg_t - Command configure
 *
*/
typedef struct __PACKED__
{
    uint32  param1;
    uint32  param2;
    uint8   type;
    uint8   padding[3];
} LinkAdaptDebugCfg_t;

/******************************************************************************
        ID:     DOT11_GROUP_ADDRESS_TBL 
        Desc:   The variable lengths of MAC addresses that are define as listening for
                multicast. The field Number of groups identifies how many MAC Addresses 
                are relevant in that information element.
        Type:   Configuration
******************************************************************************/
#define ACX_MC_ADDRESS_GROUP_MAX    (8)
#define ADDRESS_GROUP_MAX_LEN       (MAC_ADDR_LEN * ACX_MC_ADDRESS_GROUP_MAX)
/**
 * struct GrpAddrTblCfg_t - Command configure
 *
 * @roleID:         Role ID
 * 
 * @enabled:        Enable
 * 
 * @numGroups:      Number of groups
 * 
 * @pad:
 * 
 * @macTable:       Mac address table
*/
typedef struct __PACKED__
{

    RoleID_t    roleID;
    uint8       enabled;
    uint8       numGroups;
    uint8       pad[1];
    uint8       macTable[ADDRESS_GROUP_MAX_LEN];
} GrpAddrTblCfg_t;

/******************************************************************************
        ID:     FORCE_PS_CFG 
        Desc:   Power save configuration
        Type:   Configuration
******************************************************************************/
/**
 * struct GrpAddrTblCfg_t - Command configure
 *
 *  @paramIndex - TrafficModule_parameters_e -
                                    ACTIVE_MODE_RX_TH  = 0,
                                    ACTIVE_MODE_TX_TH  = 1,
                                    ACTIVE_MODE_RX_TO  = 2,
                                    ACTIVE_MODE_TX_TO  = 3,
                                    FORCE_POWER_MODE   = 4
 * 
 * @paramValue: value to configure.
                For the last parameter (force power mode):  0 - no force
                                                            1 - force active
                                                            2 - force power save     Enable
*/
typedef struct __PACKED__
{
    uint8       paramIndex;
    uint32      paramValue;

    uint8       pad[3];
} ForcePsCfg_t;

/******************************************************************************
        ID:     BA_SESSION_RX_SETUP
        Desc:   Open BA session
        Type:   Configuration
******************************************************************************/
typedef struct __PACKED__
{
    uint8        linkId;
    uint8        tid;
    uint8        enable;
    uint8        win_size;
    uint16       ssn;
    uint8        padding[2];
} RxBaSessionCfg_t;

/*****************************************************************************/


/******************************************************************************
        ID:     ACX_SLEEP_AUTH
        Desc:   Sets the lowest power mode available to the device
        Type:   Configuration
******************************************************************************/
typedef struct __PACKED__
{
    /* 0 - Always active*/
    /* 1 - Power down mode: light / fast sleep*/
    /* 2 - ELP mode: Deep / Max sleep*/
    uint8  sleep_auth;
    uint8  padding[3];
} SleepAuthCfg_t;

/*****************************************************************************/

/******************************************************************************
        ID:     PMAC_HW_RATE_OVERRIDE
        Desc:   Override Pmac HW rate
        Type:   Configuration
******************************************************************************/
typedef struct __PACKED__
{
    uint8 overEnable;
    uint8 bw;
    uint8 preamble;
    uint8 rate;
    uint8 dcm;
    uint8 txPower;
    uint8 giLTF;
    uint8 padding;
} PmacHwRateMngOverrideCfg_t;

/*****************************************************************************/

/******************************************************************************
        ID:     STATIC_CALIBRATION_CFG
        Desc:   Static calibration configuration
        Type:   Configuration
******************************************************************************/
typedef struct __PACKED__
{
    uint8   chipId[MAC_ADDR_LEN];
    uint16  length;
} calibrationHeader_t;

typedef struct __PACKED__
{
    Bool_e                  validData;
    uint8                   file_version;
    uint8                   payload_version;
    uint8                   padding;
    calibrationHeader_t     calibrationHeader;
} StaticCalibrationCfg_t;

typedef struct __PACKED__
{
    uint16                   calibration_bitmap;
    uint8                    padding[2];
} ManualCalibrationCfg_t;


/******************************************************************************/

/*******************************************************************************
        ID:     AP_RATES_CFG
        Desc:   configure ap rates/update ap rates
        Type:   Configuration
*****************************************************************************/
typedef struct __PACKED__
{
    RoleID_t roleId;
    uint32 basic_rates_set;
    uint32 supported_rates;
    uint8 padding[3];

}ApRatesCfg_t;


/******************************************************************************
        ID:     ENABLE_NOTIFY
        Desc:   Enable Flow control Notify
        Type:   Configuration
        NOTE:   Not yet implemented!!! (TBD)
******************************************************************************/
typedef struct __PACKED__
{
    uint8 enable;
    uint8 padding[3];
} EnableNotifyInt_t;
/*****************************************************************************/

/******************************************************************************
* ** ***                                                               *** ** *
* ** ***                  CONFIGURE CMD                                *** ** *
* ** ***                                                               *** ** *
*******************************************************************************/
/******************************************************************************
        ID:     CMD_CONFIGURE
        Desc:   This command is used to setting configuration that coming
                from the Host/Driver.
        Return: CMD_STATUS
******************************************************************************/
typedef union
{
    CtsProtectionCfg_t          CtsProtection;
    TxParamCfg_t                TxParam;
    AssocInfoCfg_t              AssocInfo;
    PeerCapCfg_t                PeerCap;
    BssOperationCfg_t           BssCap;
    SlotTimeCfg_t               SlotTime;
    PreambleTypeCfg_t           PreambleType;
    GrpAddrTblCfg_t             GrpAddrTbl;
    RxBaSessionCfg_t            RxBaSession;
    SleepAuthCfg_t              SleepAuth;
    ApRatesCfg_t                ApRates;
    StaticCalibrationCfg_t      StaticCalibration;
} Cfg_u;
/**
 * struct Cfg_t - Command configure
 *
 * @id:              Configuration identification
 *
 * @length:          Length/reserved
 *
 * @ex:              Configuration parameters
*/
typedef struct
{
    uint16_t /*Cfg_e*/          id;
    uint16          length;
    Cfg_u           ex;
} Cfg_t;

/******************************************************************************
* ** ***                                                               *** ** *
* ** ***                      DEBUG CMD                                *** ** *
* ** ***                                                               *** ** *
*******************************************************************************/
/******************************************************************************
        ID:     DEBUG CMD
        Desc:   This command is used to setting debug configuration that coming
                from the Host/Driver.
        Return: CMD_STATUS
******************************************************************************/
typedef union
{
    UplinkMUCfg_t       UplinkMU;
    UplinkMUDataCfg_t   UplinkMUData;
    OperModeCTRLCfg_t   OperModeCTRL;
    UplinkPWRHDRCfg_t   UplinkPWRHDR;
    MSCRateCfg_t        MSCRate;
    GiLtfCfg_t          GiLtf;
    TransmitOMICfg_t    TransmitOMI;
    TBOnlyCfg_t         TBOnly;
    BASessionCfg_t      BASession;
    ForcePsCfg_t        ForcePs;
    PmacHwRateMngOverrideCfg_t  RateMngOverride;
    BLSCfg_t            BlsData;
}cmdDebug_u;
/**
 * struct cmdDebug_t - Command debug configure
 *
 * @id:              Debug Configuration identification
 *
 * @length:          Length/reserved
 *
 * @ex:              Configuration parameters
*/
typedef struct
{
    cmdDebug_e           id;
    uint16               length;
    cmdDebug_u           ex;
} cmdDebug_t;


/******************************************************************************
* ** ***                                                               *** ** *
* ** ***                     INTERROGATE                               *** ** *
* ** ***                                                               *** ** *
*******************************************************************************/
/**
 * enum Interrogate_e - Interrogate Element id
 *
 * @MEM_MAP_INTR:               Read the memory map from the FW
 *
 * @GET_FW_VERSIONS_INTR:       Read the FW versions from the FW
 *
 * @RSSI_INTR:                  Read beacon rssi value
 * 
 * @GET_ANTENNA_SELECT_INTR:    Read the antenna selection value from the FW
 *
 * @GET_PREAMBLE_AND_TX_RATE_INTR:  Read the preamble and the tx rate from the FW
*/
typedef enum
{
    MEM_MAP_INTR                  = 0,
    GET_FW_VERSIONS_INTR          = 1,
    RSSI_INTR                     = 2,
    GET_ANTENNA_SELECT_INTR       = 3,
    GET_PREAMBLE_AND_TX_RATE_INTR = 4,
    GET_MAC_ADDRESS               = 5,
    READ_COEX_STATISTICS          = 6,
    GET_ANT_DIV_STATUS            = 7,
    GET_ANT_DIV_RSSI_THRESHOLD    = 8,
    GET_ANT_DIV_DEFAULT_ANTENNA   = 9,
    GET_LATEST_CHANNEL_UTILIZATION_SURVEY        = 10,
    GET_DECRYPT_PACKETS_COUNTS    = 11,
    GET_ROLE_CHANNEL_NUMBER       = 12,
    GET_LINK_INACTIVITY           = 13,

    LAST_INTR_VALUE                  ,
    MAX_DOT11_INTR = LAST_INTR_VALUE   ,

    MAX_INTR = 0xFFFF   /*force enumeration to 16bits*/
} Interrogate_e;

/******************************************************************************
        ID:     MEM_MAP_INTR
        Desc:   Read the memory map from the FW
        Type:   Interrogate
******************************************************************************/
/**
 * struct MemoryMap_t - Read the memory map from the FW
 *
 * @numTxMemBlks:    Number of blocks that FW allocated for TX packets.
 *
 * @numRxMemBlks:    Number of blocks that FW allocated for RX packets.
 *
 * @numTxDescriptor: Number of TX descriptor that allocated.
*/
typedef struct
{
    /* Number of blocks FW allocated for TX packets */
    uint32 numTxMemBlks;
    /* Number of blocks FW allocated for RX packets */
    uint32 numRxMemBlks;
    /* Number of TX descriptor that allocated. */
    uint32 numTxDescriptor;
}MemoryMap_t;

/******************************************************************************
        ID:     GET_FW_VERSIONS_INTR
        Desc:   Read the FW versions from the FW
        Type:   Interrogate
******************************************************************************/
/**
 * struct GetFWVersion_t - Read the FW versions from the FW
 *
 * @major_version:    major version part of FW sw version.
 *
 * @minor_version:    minor version part of FW sw version.
 *
 * @api_version:      api version part of FW sw version.
 *
 * @build_version:    build version part of FW sw version.
 *
 * @phy_version:      phy_version.
*/
typedef struct
{
    uint16 major_version;
    uint16 minor_version;
    uint16 api_version;
    uint16 build_version;

    uint8 phy_version[6];
    uint8 pad[2];
}FWVersions_t;

/******************************************************************************
        ID:     RSSI_INTR
        Desc:   Read the beacon rssi
        Type:   Interrogate
******************************************************************************/
typedef struct __PACKED__
{
    uint8       role_id;
    uint8       pad[3];
    uint32      missed_beacons;
    uint8       snr_data;
    uint8       snr_beacon;
    int8        rssi_data;
    int8        rssi_beacon;
} BeaconRssi_t;



/******************************************************************************
        ID:     GET_ANTENNA_SELECT_INTR
        Desc:   Read the antenna selection value from the FW
        Type:   Interrogate
******************************************************************************/
/**
 * struct AntennaSelect_t - Read the antenna selection value from the FW
 *
 * @selection:     Antenna selection value
*/
typedef struct
{
    uint8 selection;
}AntennaSelect_t;

/******************************************************************************
        ID:     GET_PREAMBLE_AND_TX_RATE_INTR
        Desc:   Read the preamble and the tx rate
        Type:   Interrogate
******************************************************************************/
typedef struct __PACKED__
{
    uint16 tx_rate;
    uint8 preamble;
    uint8 role_id;
} PreambleAndTxRate_t;

/******************************************************************************
        ID:     BEACON_RSSI_INTR
        Desc:   Read the beacon rssi
        Type:   Debug Interrogate
******************************************************************************/
/**
 * struct BeaconRSSI_t - Read beacon rssi
 *
 * @beaconRssi:    Beacon RSSI
 *
*/
typedef struct __PACKED__
{
    uint8 beaconRssi;
    uint8 padding[3];
} DebugBeaconRssi_t;

/******************************************************************************
        ID:     GET_MAC_ADDRESS
        Desc:   Read the mac address
        Type:   Interrogate
******************************************************************************/
typedef struct __PACKED__
{
    uint8   role_id;
    uint8   macAddress[MAC_ADDR_LEN];
    uint8   padding[1];
} Macaddress_t;

/******************************************************************************
        ID:     GET_LINK_INACTIVITY
        Desc:   Get inactivity duration for a given link
        Type:   Interrogate
******************************************************************************/
typedef struct
{
    int   inactivityDuration;
    uint8 macAddress[MAC_ADDR_LEN];
    uint8 padding[2];
} LinkInactivity_t;

/******************************************************************************
* ** ***                                                               *** ** *
* ** ***                  INTERROGATE CMD                              *** ** *
* ** ***                                                               *** ** *
*******************************************************************************/
#define BASE_SIZE_CMD_INTERROGATE   (4)
/******************************************************************************
        ID:     CMD_INTERROGATE
        Desc:   Processes read access requests to information elements
        Return: CMD_STATUS
******************************************************************************/
typedef union
{
    MemoryMap_t                MemoryMap;      // MEM_MAP_INTR
    FWVersions_t               FWVersions;     // GET_FW_VERSIONS_INTR
    BeaconRssi_t               BeaconRssi;     // RSSI_INTR
    NoiseFloor_t               NoiseFloor;     // NOISE_FLOOR_INTR
    AntennaSelect_t            AntennaSelect;  // GET_ANTENNA_SELECT_INTR
    PreambleAndTxRate_t        PreambleAndTxRate;         // GET_PREAMBLE_AND_TX_RATE_INTR
    Macaddress_t               Macaddress;     // GET_MAC_ADDRESS


}Interrogate_u;
/**
 * struct Interrogate_t -Read Interrogate command
 *
 * @id:              Configuration identification
 *
 * @length:          Length/reserved
 *
 * @ex:              Interrogate parameters
*/
typedef struct
{
    uint16/*Interrogate_e*/           id;
    uint16                  length;
    Interrogate_u           ex;
} Interrogate_t;

typedef struct __PACKED__
{
    uint8_t channel;
    uint8_t band;
    uint8_t bandwidth;
    uint8_t padding[1];
}TTestCmd_channelTune_t;

typedef enum{
    CONSTVALUE = 0,
    INCREAMENT = 1,
    RANDOM_VALUE = 2,
}dataMode_e;

typedef struct __PACKED__
{
    uint32_t    bitmask;
    uint8_t     preambleType;
    uint8_t     PhyRate;
    int8_t      TxPower;
    uint8_t     GI_LTF_Type;
    uint8_t     DCM;
    uint16_t    start_length;
    uint16_t    end_length;
    uint32_t    delay;
    uint8_t     packetMode;
    uint16_t    numberOfPackets;
    uint8_t     dataMode;
    uint8_t     dataConstValue;
    uint8_t     enableCCA;
    uint8_t     BSSColor;
    uint16_t    SU_ER_Bandwidth;
    uint8_t     partialAID;
    uint8_t     src_addr[MAC_ADDR_LEN];
    uint8_t     dst_addr[MAC_ADDR_LEN];
    uint8_t     nominalPacketExtension;
    uint8_t     feedbackStatus;
    uint16_t    aid;
    uint8_t     group_id;
    uint8_t     ltf_mode;
    uint8_t     he_ltf_num;
    uint8_t     pre_fec_padding_factor;
    uint16_t    common_info_len;
    uint16_t    ru_alloc;
    uint8_t     ul_bw;
    uint8_t     starts_sts_num;
    uint8_t     tb_auto_mode;
    uint8_t     disamb;
    uint8_t     padding[1];//padding
}TTestCmd_StartTX_t;

typedef enum {
    /*  0x0    */   PREAMBLE_TYPE = 0x0,
    /*  0x1    */   PHY_RATE = 0x1,
    /*  0x2    */   TX_POWER = 0x2,
    /*  0x3    */   GI_LTF_TYPE = 0x3,
    /*  0x4    */   DCM  =0x4,
    /*  0x5    */   LENGTH = 0x5,
    /*  0x6    */   DELAY = 0x06,
    /*  0x7    */   PACKET_MODE = 0x07,
    /*  0x8    */   NUMBER_OF_PACKETS = 0x8,
    /*  0x9    */   DATA_MODE = 0x9,
    /*  0xA    */   DATA_CONST_VALUE = 0xA,
    /*  0xB    */   ENABLE_CCA = 0xB,
    /*  0xC    */   BSS_COLOR = 0xC,
    /*  0xD    */   SU_ER_BANDWIDTH = 0xD,
    /*  0xE    */   PARTIAL_AID = 0xE,
    /*  0xF    */   SRC_ADDR = 0xF,
    /*  0x10   */   DST_ADDR = 0x10,
    /*  0x11   */   NOMINAL_PACKET_EXTENSION = 0x11,
    /*  0x12   */   FEEDBACK_STATUS = 0x12,
    /*  0x13   */   AID = 0x13,
    /*  0x14   */   GROUP_ID = 0x14,
    /*  0x15   */   LTF_MODE = 0x15,
    /*  0x16   */   HE_LTF_NUM = 0x16,
    /*  0x17   */   PRE_FEC_PADDING_FACTOR = 0x17,
    /*  0x18   */   COMMON_INFO_LEN = 0x18,
    /*  0x19   */   RU_ALLOC = 0x19,
    /*  0x1A   */   UL_BW = 0x1A,
    /*  0x1B   */   STARTS_STS_NUM = 0x1B,
    /*  0x1C   */   TB_AUTO_MODE = 0x1C,
    /*  0x1D   */   TB_DISAMB_MODE = 0x1D,


}TTestCmd_StartTX_e;


typedef struct __PACKED__
{
    uint32 dummy;
}TTestCmd_StopTX_t;


typedef struct __PACKED__
{
    uint8_t   AckEnable;
    uint8_t   macAddress[MAC_ADDR_LEN];
    uint16_t  aid;
    uint8_t   preambleType;
    uint8_t   rate;
    uint8_t   padding;
}TTestCmd_StartRX_t;

typedef struct __PACKED__
{
    uint32 dummy;
}TTestCmd_ResetRXStats_t;


typedef struct __PACKED__
{
    uint32 dummy;
}TTestCmd_StopRX_t;

typedef struct __PACKED__
{
    uint8_t ant;
    uint8_t padding[3];
}TTestCmd_SwitchAnt_t;

typedef struct __PACKED__
{
    uint32  ReceivedTotalPacketsNumber;                           /* sum of the packets that been received OK (include filtered) */
    uint32  ReceivedFcsErrorPacketsNumber;                        /* sum of the packets that been dropped due to FCS error */
    uint32  ReceivedAddressMismatchPacketsNumber;                 /* sum of the packets that been received but filtered out by one of the HW filters */
    uint32  ReceivedGoodPackets;                                  /* sum of all the good packets received */
    int16   AverageDataCtrlRssi;                                  /* average RSSI for all valid data packets received */
    int16   AverageDataCtrlSNR;                                   /* average SNR for all valid data packets received */
}TransceiverRxStatCounters_t;

/* Cmd Test commands (used for for PLT/Transceiver) */


typedef enum {
    /*  0x1    */   CC33XX_TEST_CMD_CHANNEL_TUNE = 0x1,
    /*  0x2    */   CC33XX_TEST_CMD_TX_START = 0x2,
    /*  0x3    */   CC33XX_TEST_CMD_TX_TONE_START = 0x3,
    /*  0x4    */   CC33XX_TEST_CMD_TX_STOP  =0x4,
    /*  0x5    */   CC33XX_TEST_CMD_START_RX_SIMULATION = 0x5,
    /*  0x6    */   CC33XX_TEST_CMD_RESET_RX_STATS = 0x06,
    /*  0x7    */   CC33XX_TEST_CMD_STOP_RX_STATS = 0x07,
    /*  0x8    */   CC33XX_TEST_CMD_GET_RX_STATS = 0x8,
    /*  0x9    */   CC33XX_TEST_CMD_SWITCH_ANT = 0x9,
    /*  0xA    */   CC33XX_TEST_CMD_GET_VERSION = 0xA,
    /*  0xB    */   CC33XX_TEST_CMD_GET_MAC_ADDRESS = 0xB,                
    /*  0xC    */   CC33XX_TEST_CMD_SET_PARAMS = 0xC,
    /*  0xD    */   CC33XX_TEST_CMD_GET_PARAMS = 0xD,
    /*  0xE    */   CC33XX_TEST_CMD_STATIC_CALIBRATION = 0xE,
    /*  0xF    */   CC33XX_TEST_CMD_GET_PHY_CPE_VERSION = 0xF,
    /*  0x10   */   CC3XX_TEST_CMD_MANUAL_CALIBRATION = 0x10,
    /*  0x11   */   CC3XX_TEST_CMD_GET_CALIBRATION_STATUS = 0x11,
    /*  0x12   */   CC3XX_TEST_CMD_GET_SYSTEM_INFO = 0x12,

}TestCmdID_e;


typedef struct
{
    TestCmdID_e     testCmdId;
    int8            padding[3];

    /* Efil -   when adding parameter here fill the switch case sentence in function
            "cmdBld_CmdIeTest" in module "TWD\Ctrl\CmdBldCmdIE.c" */
    union
    {
           TTestCmd_channelTune_t           ChannelTune;
           TTestCmd_StartTX_t               StartTX;
           TTestCmd_StopTX_t                StopTX;
           TTestCmd_StartRX_t               StartRX;
           TTestCmd_ResetRXStats_t          ResetRXStats;
           TTestCmd_SwitchAnt_t             SwitchAnt;
           TransceiverRxStatCounters_t      GetRXStats;
           ManualCalibrationCfg_t           ManualCalibration;
           StaticCalibrationCfg_t           StaticCalibration;

    }testCmd_u;
}TTestCmd;


/******************************************************************************
* ** ***                                                               *** ** *
* ** ***                  DEBUG READ CMD                               *** ** *
* ** ***                                                               *** ** *
*******************************************************************************/
/******************************************************************************
        ID:     CMD_DEBUG_READ
        Desc:   Processes read access requests to information elements
        Return: CMD_STATUS
******************************************************************************/
/**
 * enum DebugInterrogate_e - Interrogate Element id
 * 
 * @BEACON_RSSI_INTR: Read beacon rssi value
*/
typedef enum
{
    BEACON_RSSI_INTR                ,

    LAST_DEBUG_READ_VALUE           ,

    MAX_DEBUG_READ = 0xFFFF   /*force enumeration to 16bits*/
} DebugInterrogate_e;

typedef union
{
    BeaconRssi_t BeaconRssi;
}DebugInterrogate_u;
/**
 * struct DebugInterrogate_t -Read Interrogate command
 *
 * @id:              Configuration identification
 *
 * @length:          Length/reserved
 *
 * @ex:              Interrogate parameters
*/
typedef struct
{
    DebugInterrogate_e      id;
    uint16                  length;
    DebugInterrogate_u      ex;
} DebugInterrogate_t;

/******************************************************************************
* ** ***                                                               *** ** *
* ** ***                  Command Dispatcher                           *** ** *
* ** ***                                                               *** ** *
*******************************************************************************/
#define MAX_MBOX_SIZE_BTL   (700)
#define MAX_MBOX_SIZE_FW   (896)
#define MAX_MBOX_SIZE       MAX_MBOX_SIZE_FW
/******************************************************************************

        CommandParam_t  a structure for command parameters.
                                 This structure is forwarded from the driver
                                 to the dispatcher.
******************************************************************************/
/**
 * structure CommandParam_t- Command Dispatcher parameters
 *
 * @cmdID:        Command ID
 *
 * @reserved:
 *
 * @param:        Command parameters
*/
//TODO ,JIRA OSPREY_MSB-3 ,this structure is temporary solution to the alignment issue between M3 and M33
//need to be changed when issue solved
typedef  struct __PACKED__
{
    //Command_e   cmdID;//2 bytes
    uint32      cmdID;
    uint8       param[MAX_MBOX_SIZE];
} CommandParam_t;

#ifdef TODO
typedef struct
{
    Command_e   cmdID;
    uint32_t    reserved;
    uint8_t     param[MAX_MBOX_SIZE];
} CommandParam_t;
#endif
/******************************************************************************

        CommandComplete_t  a structure for command complete parameters.
                            This structure is forwarded from the
                            dispatcher to the driver
******************************************************************************/


#ifdef THICK_MAC_COMPILE
#define MAX_COMPLETE 100
#else
#define MAX_COMPLETE  MAX_MBOX_SIZE
#endif

/**
 * structure CommandCompleteInfo_t- Command complete info
 *
 * @status:        Command complete status
 *
 * @param:        command parameters complete
*/
typedef struct
{
    uint16 /*CommandStatus_e*/     status;
    uint8               param[MAX_COMPLETE];
} CommandCompleteInfo_t;
/**
 * structure CommandComplete_t - Command complete parameters
 *
 * @cmdID:        Command ID
 *
 * @info:         Command complete info
*/
typedef struct
{
    uint16/*Command_e*/     cmdID;
    CommandCompleteInfo_t   info;
} CommandComplete_t;


// short CommandComplete_t only for failures
typedef struct
{
    uint16/*Command_e*/               cmdID;
    uint16 /*CommandStatus_e*/         status;
} CommandCompleteFailure_t;



#endif /* CC33xx_PUBLIC_COMMANDS_H*/
