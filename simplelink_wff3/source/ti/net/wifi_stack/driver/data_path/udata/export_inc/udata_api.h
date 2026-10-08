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
/*
 * udata_api.h
 *
 *  Created on: Jul 20, 2011
 *      Author: x0142655
 */

#ifndef UDATA_API_H_
#define UDATA_API_H_

#include "ti_qos_types.h"
#include "tw_driver.h"
#include "public_types.h"
#include "802_11defs.h"
#include "paramOut.h"
#include "init_table_types.h"
#include "udata.h"
#include "ethernet.h"
#include "wlan_if.h"

/* ======================== Common Module API ======================== */


#if 0
/* \brief   generic getter API for non-UWD modules
 * \param   param   describes the attribute to read
 * \return  a return code passed to the caller
 */
uint32_t udata_GetParam(paramInfo_t* param);

/* \brief   generic setter API for non-UWD modules
 * \param   param   describes the attribute to write
 * \return  a return code passed to the caller
 */
uint32_t udata_SetParam(paramInfo_t* param);
#endif
/* ======================== General UData Control ======================== */

/* \brief   invoked (in UWD context) upon a MIC Failure
 * \param   ctx context, as passed in registration
 * \param   link    link on which MIC Failure occurred
 * \param   uFailureType
 */
typedef void (*TMicFailureHandler) (void *ctx, uint32_t link, uint8_t uFailureType);

/* \brief   discards all queued packets
 */
void udata_ClearQueues(void);

/* \brief   Notify the udata that chip recovery process was done
 */
void udata_NotifyRecovery(void);

/* \brief   registers a callback UData can invoke (in UWD context) upon a MIC Failure
 * \param   cb          callback to register
 * \param   ctx         first argument to pass when invoking @cb
 * \return  OK if registration was successful
 */
void udata_RegisterMicFailureHandler(TMicFailureHandler cb, void *ctx);

/* ======================== Link Control ======================== */

typedef enum 
{
    LINK_STATE_CLOSED,  /* closed for all packets. */
    LINK_STATE_MGMT,    /* open only for mgmt packets. */
    LINK_STATE_EAPOL,   /* open only for mgmt or EAPOL packets. */
    LINK_STATE_OPEN,   /* open for all packets. */
    LINK_STATE_NUM
} ELinkState;

#define TSM_REPORT_NUM_OF_BINS_MAX                              6
#define TSM_REPORT_NUM_OF_TID_MAX                               8
#define TSM_REPORT_NUM_OF_MEASUREMENT_IN_PARALLEL_MAX           3

#define TSM_REQUEST_TRIGGER_CONDITION_AVERAGE                   BIT_0
#define TSM_REQUEST_TRIGGER_CONDITION_CONSECUTIVE               BIT_1
#define TSM_REQUEST_TRIGGER_CONDITION_DELAY                     BIT_2

typedef struct 
{
    uint32_t   binDelayThreshold[TSM_REPORT_NUM_OF_BINS_MAX];/* The thresholds for the delay histogram to be reported in the TSM  */
    uint32_t   binsDelayCounter[TSM_REPORT_NUM_OF_BINS_MAX]; /* Every packet delay will increase the corresponding bin counter */
    uint8_t    uMaxConsecutiveDelayedPktsThr;     /* The number of consecutive delayed packets threshold which will cause triggering TSM report */
    uint8_t    uMaxConsecutiveDelayedPktsCounter; /* The number of consecutive delayed packets counter  */

    /* bit field : bit0: average, bit1: consecutive, bit2: delay */
    uint8_t    uDelayThreshold; /* in TUs (1024 useconds)  */
    uint8_t    uAverageErrorThreshold;
    uint8_t    uConsecutiveErrorThreshold;

    uint8_t    uConsecutiveDiscardedMsduCounter;
    uint8_t    uAverageDiscardedMsduCredit;

    uint8_t    uPktCrossedDelayThrCounter;        /* The actual number of consecutive MSDUs crossed the Delay Threshold */
    uint32_t   uMsduTotalCounter;                 /* the number of MSDU that were successfully or not transmitted */
    uint32_t   uMsduTransmittedOKCounter;         /* the number of MSDU that were successfully transmitted */
    uint32_t   uMsduRetryExceededCounter;         /* the number of transmit attempts exceeding short/long retry limit */
    uint32_t   uMsduMultipleRetryCounter;         /* more than one retransmission attempt */
    uint32_t   uMsduLifeTimeExpiredCounter;       /* the number of transmit attempts with lifetime expired */
    Bool_e     bTSMInProgress;                    /* flag which specifies that the measurement for this TID has started */
    Bool_e     bIsTriggeredReport;
    uint8_t    measurementToken;
    uint8_t    measurementCount;
    uint16_t   measurementDuration;

    uint8_t    actualMeasurementTSF[TIME_STAMP_LEN];
    uint8_t    frameToken;
    uint16_t   frameNumOfRepetitions;
    TMacAddr   peerSTA;
    uint8_t    uTID;
    uint8_t    reportingReason;
    uint8_t    bin0Range;
    uint8_t    triggerCondition;
} TSMReportData_t;

/* Callback function definition for triggering the TSM report towards the RRM module */
typedef void (*TTsmReportHandler)(void *hMeasurementMgr, TSMReportData_t *pTSMReport);

typedef struct 
{
    uint8_t    triggerCondition;
    uint8_t    averageErrorThreshold;
    uint8_t    consecutiveErrorThreshold;
    uint8_t    delayThreshold;
    uint8_t    measuCount;
    uint8_t    triggerTimeout;
} TTsmTriggeredReportField;

/* Traffic Stream Measurement Parameters */
typedef struct 
{
    Bool_e                         bIsTriggeredReport;
    uint8_t                        frameToken;
    uint16_t                       frameNumOfRepetitions;
    uint8_t                        measurementToken;
    uint16_t                       randomInterval;
    uint16_t                       uDuration;
    uint8_t                        uTID;
    uint8_t                        uBin0Range;
    uint8_t                        uDelayedMsduRange;
    uint8_t                        uDelayedMsduCount;
    TMacAddr                       peerSTA;
    TTsmTriggeredReportField       tTriggerReporting;
    TTsmReportHandler              fCB;
    void                          *hCB;
    uint8_t                        aActualMeasurementTSF[TIME_STAMP_LEN];
} TTsmParams;



/* \brief   adds a link (links with type 'specific' also require calling
 *              udata_SetPeerParams() to be able to xmit).
 *          the link is initialized with:
 *              Rx State:               LINK_STATE_CLOSED
 *              Tx State:               LINK_STATE_CLOSED
 *              Rx Block-Ack Policy:    RX_BA_SESSION_NOT_ALLOWED
 *              Tx Ack Policy:          ACK_POLICY_LEGACY
 *              Peer MAC:               00-00-00-00-00-00
 *              Session ID:             0
 *              WME Enabled:            FALSE
 *              Management Encryption:  FALSE
 *              EAPOL Encryption:       FALSE
 *              Data Encryption:        FALSE
 *              Drop Unenc. Unicast:    FALSE
 *              Drop Unenc. Broadcast:  FALSE
 *              Medium Usage Time:      0 (for each AC)
 *              Admission State:        AC_ADMITTED (for each AC)
 *              Admission Required:     ADMISSION_NOT_REQUIRED (for each AC)
 *              MSDU Lifetime:          8000 (TU)
 *
 * \param   link                ID of link to update
 * \param   uHandoverLink       ID of link to use in case of handover (roaming, different than 'link' only for STA)
 * \param   eLinkType           type of link (system/specific/bcast/global)
 * \param   eRoleType           the type of role this link is used for (sta/ap/dev/p2pcl/p2pgo)
 * \param   eLmacRoleId         ID of role in LMAC
 * \param   uRxTag              used to tag RX packets on this link (e.g. network-interface ID)
 * \param   uMgmtRatePolicyIdx  TX rate policy for Management packets
 * \param   uDataRatePolicyIdx  TX rate policy for data packets
 * \see udata_SetPeerParams()
 */
void udata_AddLink(uint32_t         link, 
                   uint32_t         uHandoverLink, 
                   linkType_e       eLinkType,
                   tiwdrv_if_mode_e eIfMode,
                   RoleID_t         eLmacRoleId,
                   uint32_t         uRxTag,
                   uint8_t          uMgmtRatePolicyIdx, 
                   uint8_t          uDataRatePolicyIdx);

/* \brief   sets the local MAC address of an LMAC role
 * \param   eLmacRoleId ID of role in LMAC
 * \param   mac         MAC address of role
 */
void udata_SetRoleMac(RoleID_t eLmacRoleId, TMacAddr mac);

/* \brief   updates the link's peer parameters (needed to actually xmit on links
 *          with type 'specific'). May be called to override previously set peer parameters (e.g.
 *          when roaming)
 * \param   link        the link to update
 * \param   mac         MAC address of peer (e.g. of AP, for link between STA and AP)
 * \param   bWmeEnabled
 */
void udata_SetPeerParams(uint32_t link, const TMacAddr mac, Bool_e bWmeEnabled);

/* \brief   updates the link's Tx session ID
 * \param   link        the link to update
 * \param   uSessionId
 */
void udata_SetTxSessionId(uint32_t link, uint8_t uSessionId);

/* \brief   closes the link and cleans up any resources allocated by udata_AddLink()
 * \param   link    ID of link to remove
 */
void udata_RemoveLink(uint32_t link);

/* \brief   toggles encryption for EAPOL packets
 * \param   link        ID of link set EAPOL encryption for
 * \param   enabled     TRUE to encrypt EAPOL packets, FALSE to send them clear
 */
void udata_SetEapolEncryption(uint32_t link, Bool_e enabled);

/* \brief   toggles encryption for data packets
 * \param   link
 * \param   enabled     TRUE to encrypt data packets, FALSE to send them clear
 * \param   bDropBcast  TRUE to drop unencrypted broadcast packets
 * \param   bDropUcast  TRUE to drop unencrypted unicast packets
 */
void udata_SetDataEncryption(uint32_t link, Bool_e enabled, Bool_e bDropBcast, Bool_e bDropUcast);
/* \brief   toggles pmf encryption for mgmt packets
 * \param   link
 * \param   enabled     TRUE to encrypt data packets, FALSE to send them clear
 */
void udata_SetMgmtEncryption(uint32_t link, Bool_e bPMFEncrypt);

/* \brief   sets the link security type
 * \param   link
 * \param   eKeyType    the security type (WEP/TKIP/AES...)
 */
void udata_SetEncryptionType(uint32_t link, EKeyType eKeyType);

/* \brief   get the link security type
 * \param   link
 * \param   eKeyType    the security type (WEP/TKIP/AES...)
 */
EKeyType udata_GetEncryptionType(uint32_t link);

/* \brief   toggles the intra-BSS bridge (to forward packet within the same BSS)
 * \param   eLmacRoleId ID of role in LMAC
 * \param   enabled     TRUE to forward packets within the same BSS
 */
void udata_SetIntraBssBridge(RoleID_t eLmacRoleId, Bool_e enabled);

/* \brief   sets the minimum and maximum medium usage times for an AC in a link
 * \param   ac      Access Category to set thresholds for
 * \param   low     low threshold - crossing below this threshold will trigger an
 *                  TIW_DRV_EV_MEDIUM_TIME_CROSS event
 * \param   high    high threshold - crossing above this threshold will trigger an
 *                  TIW_DRV_EV_MEDIUM_TIME_CROSS event
 * \return  NOK if @ac is invalid; OK otherwise
 */
uint32_t udata_SetMediumUsageThresholds(uint8_t ac, uint32_t low, uint32_t high);

/* \brief   sets the lifetime of an MSDU
 * \param   eLmacRoleId  ID of role to set lifetime for
 * \param   ac           Access Category to set lifetime for
 * \param   lifetime    lifetime in TUs
 */
void udata_SetMsduLifetime(RoleID_t eLmacRoleId, uint8_t ac, uint32_t lifetime);

/* \brief   sets the ACK policy for TX on a specific link
 * \param   link        ID of link to set ACK policy for
 * \param   ac          Access Category to set ACK policy for
 * \param   policy      ACK policy to set
 */
void udata_SetTxAckPolicy(uint32_t link, uint8_t ac, AckPolicy_e policy);

/* \brief   sets the ACK policy for RX on a specific link
 * \param   link        ID of link to set BA policy for
 * \param   uPolicyMap  ACK policy to set: bit_N==1 implies Block Ack allowed on TID N
 */
void udata_SetRxBaPolicy(uint32_t link, uint8_t uPolicyMap);

/* \brief   sets the TX state of a link
 * \param   link
 * \param   state
 */
void udata_SetTxState(uint32_t link, ELinkState state);

/* \brief   gets the TX state of a link
 * \param   link
 */
ELinkState udata_GetTxState(uint32_t link);


/* \brief   sets the RX state of a link
 * \param   link
 * \param   state
 */
void udata_SetRxState(uint32_t link, ELinkState state);


/* ======================== QoS Control ======================== */

/* \brief   sets whether Admission Control is allowed, and required, on the specific AC
 * \param   link        ID of link to set Addmission Control in
 * \param   ac          Access Category to set Addmission Control on
 * \param   required    whether Admission Control is required on @ac
 * \param   state
 */
void udata_SetAdmissionStatus(uint8_t link, uint8_t ac, EAdmissionState required, ETrafficAdmState state);

/* \brief   sets the allocated medium time for the specified AC
 * \param   link
 * \param   ac          Access Category to set medium time for
 * \param   uMediumTime use 0 to reset the Admission Control parameters of @ac
 * \return  OK if successful
 */
uint32_t udata_SetMediumTime(uint32_t link, uint8_t ac, uint16_t uMediumTime);

/* \brief   starts a Traffic Stream measurement
 * \param   link
 * \param   params
 * \return  OK if measurement started, NOK otherwise
 */
uint32_t udata_StartTsMeasurement(uint32_t link, TTsmParams* params);

#ifndef CC33xx
/* ======================== Tx/Rx ======================== */

/* \brief Macro which gets a pointer to BUF packet header and returns the pointer to the start address of the WLAN packet's data
 */
#define RX_BUF_DATA(pBuf)   ( (((RxIfDescriptor_t *)pBuf)->driverFlags & RX_DESC_QOS_ALIGNMENT_FLAG) ?   \
                              ((void*)((uint8_t *)pBuf + sizeof(RxIfDescriptor_t) + 2)) :   \
                              ((void*)((uint8_t *)pBuf + sizeof(RxIfDescriptor_t))) )

/* \brief Macro which gets a pointer to BUF packet header and returns the buffer length (without Rx Descriptor) of the WLAN packet
 */
#define RX_BUF_LEN(pBuf)    ( (((RxIfDescriptor_t *)(pBuf))->length) -  \
                              ((RxIfDescriptor_t *)(pBuf))->extraBytes -     \
                              sizeof(RxIfDescriptor_t) )

/* \brief Macro which gets a pointer to BUF packet header and returns the pointer to the start address of the ETH packet's data
 */
#define RX_ETH_PKT_DATA(pBuf)   *((void **)(((uint32_t)pBuf + sizeof(RxIfDescriptor_t) + 2) & ~3))

/* \brief Macro which gets a pointer to BUF packet header and returns the buffer length (without Rx Descriptor) of the ETH packet
 */
#define RX_ETH_PKT_LEN(pBuf)    *((uint32_t *)(((uint32_t)pBuf + sizeof(RxIfDescriptor_t) + 6) & ~3))
#endif
/* Flags used in the flags field in TMgmtPktDesc */
#define PKTF_ENCRYPT            BIT_0 /* this packet should be encrypted */
#define PKTF_EXTERNAL_CONTEXT   BIT_1 /* this packet is inserted from external context (not driver task) */

/* the packet types to be used with udata_SendMgmtPacket */
typedef enum
{
    UDATA_TX_PKT_TYPE_WLAN_MGMT,   /* Management Packet (WLAN header) */
    UDATA_TX_PKT_TYPE_WLAN_DATA,   /* Driver generated Data type Packet (WLAN header, currently used for IAPP) */
    UDATA_TX_PKT_TYPE_ETHER_EAPOL, /* EAPOL packet (Ethernet header) */
    UDATA_TX_PKT_TYPE_DUMMY        /* Dummy packet for moving FW mem-blocks to Rx (MCP3 only) */
} EUdataTxPktType;

struct MgmtPktDesc;  /* See below */

/* information provided upon Tx completion if callback was provided upon sending the Tx packet */
typedef struct 
{
    uint8_t  uAckFailures;     /* the number of transmissions without successful ACK - needed for LINK_TEST frame */
    uint8_t  uDelBaTid;        /* the TID upon sending the packet (before downgrade) - needed for DELBA frame */
    uint32_t status;           /* the Tx result - 1 (success) or 0 (failure) */
    struct MgmtPktDesc *desc;  /* the descriptor that was allocated by UWD and passed in udata_SendMgmtPacket.
                                  Note: released by UData immediately after the CB is called (also the payload) */
} TMgmtPktReport;

/* \brief   dispatches an RX management packet. invoked in UWD thread
 * \param   ctx context that was passed on registration
 * \param   buf a buffer containing RxIfDescriptor_t  struct at its beginning, and the packet
 *          right after it. Owned by the handler - handler must free @buf when no
 *          longer needed (see RxBufFree())
 * \return  OK if packet dispatched successfully, NOK otherwise
 */
typedef int32_t(*TMgmtRxHandler)(void *buf);

/* \brief   invoked in UData context after packet was transmitted
 * \param   ctx context passed during registration
 * \param   report  .status indicates whether the packet was transmitted successfully
 *          .desc describes the transmitted packet (owned by UData)
 */
typedef int32_t (*TMgmtPacketCb)(TMgmtPktReport *report);

typedef void (*TSecuritySeqHandler)(void *ctx, uint32_t *hlid);

/* Tx Management Packet Descriptor:
 * Envelope to use for sending WLAN managment packets using udata_SendMgmtPacket().
 * Must be allocated by udata_AllocMgmtPacket!
 * Freed internally by the udata after Tx process completion.
 * Note that it may be used also for special data type packets (EAPOL or IAPP).
 */
typedef struct MgmtPktDesc 
{
  /* The NAB header. */
  void *nabHeader;
  uint32_t uNabHeaderLen;

  /* The WLAN header. */
  void *header;

  /* number of bytes in @header */
  uint32_t uHeaderLen;

  /* layer-2 payload (data which follows the WLAN header) */
  void *payload;

  /* number of bytes in @payload */
  uint32_t uPayloadLen;

  /* The packet specific type */
  EUdataTxPktType ePktType;

  /* link to send packet in */
  uint32_t link;

  /* misc. flags (bits 0-15). see PKTF_* defines */
  uint32_t flags;

  /* callback to invoke (in UWD context) after packet is transmitted. */
  TMgmtPacketCb fTxCompleteCb;

  /* context for @fTxCompleteCb */
  void *hTxCompleteCtx;

} TMgmtPktDesc;
/* Link attributes */
typedef struct
{
    uint8_t             bIsAllocated;       /* TRUE if this link is allocated for a role (udata_AddLink was called) */
    uint32_t            uHandoverLink;      /* ID of link to use in case of handover (roaming) */
    linkType_e          eLinkType;          /* Link type */
    uint32_t            uNetIfId;           /* Link Network Interface ID */
    RoleType_e          eRoleType;          /* Link Role type */
    RoleID_t            eFwRoleId;          /* Link related FW role Id */
    uint8_t             uMgmtRatePolicyIdx; /* Link Tx rate policy for mgmt packets */
    uint8_t             uDataRatePolicyIdx; /* Link Tx rate policy for data packets */
    EKeyType            eKeyType;           /* Link security type */

} TUdataLinkInfo;

/* The UDATA component object (shared by the UDATA modules) */
typedef struct
{
    TUdataLinkInfo      aLinkInfo[WLANLINKS_MAX_LINKS];     /* Link attributes */

    uint32_t            uGenericEthertype;
    uint32_t            uSystemHlid;                                  /* The system link ID */
    uint32_t            aGlobalHlids[MAX_NUM_WLAN_ROLE_IDS];          /* Array of global HLIDs per FW role */
    uint32_t            aBcastHlid[TIWDRV_NETIF_NUM];                 /* Broadcast Link ID per NetIf */
    TMacAddr            aRoleLocalMac[MAX_NUM_WLAN_ROLE_IDS];         /* Per role local MAC address */
    uint8_t             aIntraBssBridgeEnable[MAX_NUM_WLAN_ROLE_IDS]; /* Per role intra-BSS bridge enable/disable */
    tiwdrv_if_mode_e    aNetidToMode[TIWDRV_NETIF_NUM];                /* Network Interface id to mode Mapping Table */
    RoleID_t            aNetToRoleId[TIWDRV_NETIF_NUM];                /* Network Interface to FW Role ID Mapping Table */
    uint8_t             aWmeEnabled[WLANLINKS_MAX_LINKS];              /* Is link WME enabled */
    uint8_t             aSessionId[WLANLINKS_MAX_LINKS];               /* The link Tx session counter, updated upon connection */
    TMicFailureHandler  fMicFailureCb;                                 /* CB to call upon MIC failure */
    void               *hMicFailureHandle;                             /* MIC failure CB handle */
    TMgmtRxHandler      fMgmtRxCb;                                     /* CB to call for Rx Mgmt packet handling */
    TMgmtRxHandler      fEapolRxCb;                                    /* CB to call for Rx Eapol packet handling */
    TMgmtRxHandler      fRxFromUnknownCb;                              /* CB to call for Rx data from unknown/disconnected STA */
    TUdataInitParams    udataparams;                                   /* Struct that holds the TUdata parameters */
    //TODO: delete void               *hMgmtRxHandle;                                 /* Rx Mgmt packet CB handle */

} TUdata;


/* \brief   registers a callback the UData can invoke to dispatch an RX management packet
 *          (802.11 Management, scan- and measurement-results, EAPOLs and IAPP packets)
 * \param   cb  the callback to register
 * \param   ctx context for @cb (first argument to pass)
 */
void udata_RegisterMgmtRxHandler(TMgmtRxHandler mgmtcb , TMgmtRxHandler eapolcb);

/* \brief   register a callback the UData can invoke to dispatch an RX data packet
 *          from unkown host
 * \param   cb  the callback to register
 * \param   ctx context for @cb (first argument to pass)
 */
void udata_RegisterRxFromUnknownHandler(TMgmtRxHandler cb);

void udata_RegisterSecuritySeqHandler(TSecuritySeqHandler cb, void *ctx);

/* \brief   allocate a Tx management packet descriptor, including allocation of the header and
 *             payload buffers according to the specified length, and setting the length fields.
 * \param   uHeaderLen  - the header length to allocate in bytes
 * \param   uPayloadLen - the payload length to allocate in bytes
 * \return  the packet descriptor (freed by udata after Tx process completion). NULL if alloc failed.
 */
TMgmtPktDesc *udata_AllocTxMgmtPacket(uint32_t uHeaderLen,uint32_t uPayloadLen,TEthernetHeader *pEthHead);
TTxCtrlBlk *udata_AllocTxDataPacket( uint32_t uPayloadLen,uint32_t uHeaderLen,TEthernetHeader *pEthHead );


/* \brief   submits a management packet for transmission. The TMgmtPktDesc with its
 *             header and payload buffers is allocated by udata_AllocMgmtPacket.
 * \param   pkt describes the packet to submit (allocated by udata_AllocMgmtPacket and 
 *              freed by udata after Tx process completion)
 * \return  OK if packet was submitted successfully, NOK if dropped
 * \see @pkt.fTxCompleteCb (fTxCompleteCb in TMgmtPktDesc)
 */
uint32_t udata_SendTxMgmtPacket(TMgmtPktDesc *pkt);

/* \brief   suspends the transmission of packets (may be queued, but will not be handled
 *          until udata_Resume() is called). Also closes all Rx BA sessions without notifying the FW
 */
void udata_Suspend(void);

/* \brief   resumes the transmission of packets. Packets that were queued since a call
 *          to udata_SuspendTx() will be processed
 */
void udata_Resume(void);

/* \brief   Temporarily suspends the transmission of packets (may be queued, but will not be handled
 *          until udata_ResumeTx() is called).
 */
void udata_SuspendTx(void);

/* \brief   resumes the transmission of packets after suspended by a call to udata_Suspend()
 */
void udata_ResumeTx(void);


/* ======================== Statistics ======================== */

/* Global (aggregated) Statistics */
typedef struct 
{
    /* the number of frames that the NIC receives without errors */
    uint32_t      RecvOk;

    /* the number of bytes in directed packets that are received without errors */
    uint32_t      DirectedBytesRecv;

    /* the number of directed packets that are received without errors */
    uint32_t      DirectedFramesRecv;

    /* the number of bytes in multicast/functional packets that are received without errors */
    uint32_t      MulticastBytesRecv;

    /* the number of multicast/functional packets that are received without errors */
    uint32_t      MulticastFramesRecv;

    /* the number of bytes in broadcast packets that are received without errors. */
    uint32_t      BroadcastBytesRecv;

    /* the number of broadcast packets that are received without errors. */
    uint32_t      BroadcastFramesRecv;

} TGlobalRxStats;

/* \brief   reads a link's TX/RX statistics
 * \param   link    id of link to read its stats
 * \param   stats   a pre-allocated buffer to read into
 * \return  OK if contents of @stats are valid
 */
uint32_t udata_GetLinkStats(uint32_t link, TLinkDataCounters* stats);

/* \brief   resets a link's TX/RX statistics
 * \param   link    id of link to reset
 */
void udata_ResetLinkStats(uint32_t link);

/* \brief   reads the RX statistics (global, not per-link)
 * \param   buf a pre-allocagted buffer to copy the statistics into
 * \return  OK if contents of @buf are valid
 */
uint32_t udata_GetGlobalRxStats(dbg_cntr_trnspt_t* buf);
void udata_ResetGlobalRxStats();
/*
 * \param   link
 * \return  the last RX packet's rate
 */
tiwdrv_rate_e udata_GetRxRate(uint32_t link);

/*
 * \param   link
 * \return  the last TX packet's rate
 */
tiwdrv_rate_e udata_GetTxRate(uint32_t link);

/* \brief   Extract from pkt descriptor the TxCtrlBlk that was allocated by udata_AllocMgmtPacket()
 * \param   pkt         - The Tx Mgmt packet descriptor
 * \return  pPktCtrlBlk - The extracted TxCtrlBlk
 */
TTxCtrlBlk *udataNet_ExtractTxCtrlBlkFromDesc(TMgmtPktDesc *pkt);

TUdata * udata_Create(void);
uint32_t udata_Init(TUdata *pUdata);
uint32_t udata_SetParam(TUdata *pUdata);
uint32_t udata_Destroy(void);


#endif /* UDATA_API_H_ */
