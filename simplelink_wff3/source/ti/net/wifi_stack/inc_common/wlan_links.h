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
/** \file wlanLinks.h
 *  \brief WlanLinks module API
 *
 *  \see wlanLinks.c
 */

/****************************************************************************
 *                                                                          *
 *   MODULE:  wlanLinks                                                     *
 *   PURPOSE: WlanLinks Module API                                          *
 *                                                                          *
 ****************************************************************************/

#ifndef _WLAN_LINKS_H_
#define _WLAN_LINKS_H_

#include "tw_driver.h"
#include "osi_kernel.h"
#include "public_types.h"


/* Constants */

#define WLANLINKS_SYSTEM_HLID     0   /* System HLID - common for all roles */


#define TX_SESSION_ID_INVALID     0
#define TX_SESSION_ID_MIN         1
#define TX_SESSION_ID_MAX         7


typedef struct
{
    TMacAddr    aMacAddr;
    //TSsid       tSsid;
    uint8_t    uBand;
    uint8_t    uChannel;
    uint16_t   uCapablities;
}TApRolePeerEntry;

/* Enumerations */
typedef enum
{
    WLANLINK_STATE_FREE,
    WLANLINK_STATE_IDLE,
    WLANLINK_STATE_DISCOVERY,
    WLANLINK_STATE_CONNECTING,
    WLANLINK_STATE_CONNECTED,
    WLANLINK_STATE_DISCONNECTING,
}EWlanLinkState;

/* Structures */
typedef struct
{
    uint32      rxPN32[NUM_TRAFFIC_CATEGORIES + 1];  // RX Packet Number Upper Counter
    uint16      rxPN16[NUM_TRAFFIC_CATEGORIES + 1];  // RX Packet Number Lower Counter
} AESKey_rxPN_Tid_t;

typedef struct
{
    linkType_e          eType;
    tiwdrv_if_mode_e    eIfMode;
    uint32_t           uHlid;
    EWlanLinkState      eState;
    uint32_t           uQuality;
    uint32_t           uTxPow;
    Bool_e             bInactive;
    uint32_t           uAid;
	//TRateSets			tLinkRates;
	uint32_t		   uDeauthReason;
	Bool_e             bDataEncrypted;  /* TI_TRUE iff data packets on this link are (received, and should be sent) encrypted */
	Bool_e             bPMFEncription; //is PMF enable for this link
	uint8_t            uNetIfId;
    uint8_t            uTxSessionId;   /* Tx Session ID, incremented when the link is started (cyclic - TX_SESSION_ID_MIN...TX_SESSION_ID_MAX) */
    uint16_t           SecuritySeqNumLow[NUM_TRAFFIC_CATEGORIES + 1];
    uint32_t           SecuritySeqNumHigh[NUM_TRAFFIC_CATEGORIES + 1];
    TMacAddr           tMacAddr;
    Bool_e             wps;
} TWlanLinkInfo;

/* Typedefs */


/* Structures */

typedef struct
{
    void                *pPeerDescr;     /* pointer to role private storage */
    uint32_t            uPeerDescSize;   /* size of role private storage */
    TWlanLinkInfo       info;            /* public link structure */
} TInternalWlanLinkInfo;

typedef struct
{
    uint32_t                    nFree;
    TInternalWlanLinkInfo       aLinks[WLANLINKS_MAX_LINKS];
} TWlanLinks;

/* Function prototypes */

/**
 * \fn     wlanLinks_Create
 * \brief  create WlanLinks module
 */
TWlanLinks *wlanLinks_Create();

/**
 * \fn     wlanLinks_Destroy
 * \brief  destroy WlanLinks module
 */
uint32_t wlanLinks_Destroy();

/**
 * \fn     wlanLinks_Init
 * \brief  init WlanLinks module
 */
void wlanLinks_Init ();


uint32_t wlanLinks_AddLink(  TWlanLinkInfo *pLinkInfo, uint32_t uHlid, uint32_t uSessionId, const uint8 *pMacAddr, uint8 wps);
uint32_t wlanLinks_RemoveLink(uint32_t uHild);
uint32_t wlanLinks_LinkMacFind(uint8 uNetIf, const uint8 *pMacAddr);
uint32_t wlanLinks_GetLink(uint32_t uHlid, TInternalWlanLinkInfo **pLinkInfo);
uint8_t  wlanLinks_ModetoFwRoleId(tiwdrv_if_mode_e eIfMode);
uint32_t wlanLinks_GetBroadcastLink();

Bool_e   wlanLinks_CheckLinkPn(uint32_t uHlid, dot11_rsn_header_t *pRsnHdr, uint8_t frameTId, Bool_e pnValidated);
void     wlanLinks_SetLinkPn(uint32_t uHlid, uint8_t KeyID, uint16_t pn0_15, uint32_t pn16_47);
void     wlanLinks_SetBroadcastPn(AESKey_rxPN_Tid_t *broadcastPn, uint16_t pn0_15, uint32_t pn16_47);

/**
 * \fn     wlanLinks_AllocateNew
 * \brief  Allocate new Wlan Link
 */
uint32_t wlanLinks_AllocateNew(TWlanLinkInfo *pLinkInfo, uint32_t *pHlid, uint32_t privSize);

/**
 * \fn     wlanLinks_UpdateLinkInfo
 * \brief  Update Wlan Link data except dynamic parameters
 */
uint32_t wlanLinks_UpdateLinkInfo(TWlanLinkInfo *pLinkInfo, uint32_t uHlid);

/**
 * \fn     wlanLinks_ReadLinkInfo
 * \brief  Read Wlan Link info
 */
uint32_t wlanLinks_ReadLinkInfo(TWlanLinkInfo *pLinkInfo, uint32_t uHlid);

/**
 * \fn     wlanLinks_UpdateLinkPMFEnabled
 * \brief  set  pmf enable link
 */
uint32_t wlanLinks_UpdateLinkPMFEnabled( uint32_t uHlid, Bool_e isPmfEnable);

/**
 * \fn     wlanLinks_FreeLink
 * \brief  Free Wlan Link
 */
uint32_t wlanLinks_FreeLink(uint32_t uHlid);

/**
 * \fn     wlanLinks_GetPeerDescr
 * \brief  Get Peer description of a link
 */
uint32_t wlanLinks_GetPeerDescr(void *pPeerDescr, uint32_t uHlid);

/**
 * \fn     wlanLinks_GetPeerDescr
 * \brief  Set Peer description of a link
 */
uint32_t wlanLinks_SetPeerDescr(void *pPeerDescr, uint32_t uHlid);

/**
 * \fn     wlanLinks_GetPeerDescrPointer
 * \brief  Get a pointer to the required peer description
 */
uint32_t wlanLinks_GetPeerDescrPointer( void **pPeerDescr, uint32_t uHlid);

/**
 * \fn     wlanLinks_PrintDB
 * \brief  Print WlanLinks DB
 */
void wlanLinks_PrintDB();

/**
 * \brief  Set Wlan Link state
 */
uint32_t wlanLinks_SetLinkState(EWlanLinkState eState, uint32_t uHlid);

/**
 * \fn     wlanLinks_GetLinkState
 * \brief  Get Wlan Link state
 */
uint32_t wlanLinks_GetLinkState(EWlanLinkState *eState, uint32_t uHlid);

/**
 * \fn     wlanLinks_SetLinkInactivity
 * \brief  Set Wlan Link inactivity status
 */
uint32_t wlanLinks_SetLinkInactivity(Bool_e bInactivity, uint32_t uHlid);

/**
 * \fn     wlanLinks_GetLinkInactivity
 * \brief  Get Wlan Link nactivity status
 */
uint32_t wlanLinks_GetLinkInactivity(Bool_e *pInactivity, uint32_t uHlid);

/**
 * \fn     wlanLinks_SetDeauthReason
 * \brief  Set Wlan Link deauthentication reason
 */
uint32_t wlanLinks_SetDeauthReason(uint32_t uReason, uint32_t uHlid);
/**
 * \fn     wlanLinks_GetDeauthReason
 * \brief  Get Wlan Link deauthentication reason
 */
uint32_t wlanLinks_GetDeauthReason(uint32_t *pReason, uint32_t uHlid);

/**
 * \fn     wlanLinks_GetLinkType
 * \brief  Get Wlan Link type
 */
uint32_t wlanLinks_GetLinkType(linkType_e *eType, uint32_t uHlid);

/**
 * \fn     wlanLinks_GetNetIf
 * \brief  Get the Link network if id
 */
uint32_t wlanLinks_GetNetifInfo(  uint32_t uHlid, uint8_t* pNetifId, tiwdrv_if_mode_e* pNetifMode);

/**
 * \fn     wlanLinks_GetLinkRates
 * \brief  Get Wlan Link rates
 *
 * \param hWlanLinks - A handle to wlanLinks object
 * \param pRates - A pointer to output rate sets structure
 * \param uHlid  - Link ID
 *
 * \return TI_OK/TI_NOK
 */
//uint32_t wlanLinks_GetLinkRates( TRateSets *pRates, uint32_t uHlid);

/**
 * \fn     wlanLinks_SetLinkRates
 * \brief  Set Wlan Link rates
 *
 * \param hWlanLinks - A handle to wlanLinks object
 * \param pRates - A pointer to rate sets structure
 * \param uHlid  - Link ID
 *
 * \return TI_OK/TI_NOK
 */
//uint32_t wlanLinks_SetLinkRates( TRateSets *pRates, uint32_t uHlid);

/**
 * \fn     wlanLinks_SetLinkAid
 * \brief  Set Wlan Link AID
 *
 * \param hWlanLinks - A handle to wlanLinks object
 * \param uAid - AID value
 * \param uHlid  - Link ID
 *
 * \return TI_OK/TI_NOK
 */
uint32_t wlanLinks_SetLinkAid( uint32_t uAid, uint32_t uHlid);

/**
 * \fn     wlanLinks_GetLinkAid
 * \brief  Get Wlan Link AID
 *
 * \param hWlanLinks - A handle to wlanLinks object
 * \param pAid -  pointer to AID
 * \param uHlid  - Link ID
 *
 * \return TI_OK/TI_NOK
 */
uint32_t wlanLinks_GetLinkAid(uint32_t *pAid, uint32_t uHlid);

/**
 * \brief  Sets whether data on a link is / should be encrypted
 *
 * \param  uHlid       - Link ID
 * \param  bEncrypted  - TI_TRUE if data packets on @uHlid should be sent / are received encrypted
 */
void wlanLinks_SetLinkDataEncryption(uint32_t uHlid, Bool_e bEncrypted);

/**
 * \brief  Returns whether data on a link is / should be encrypted
 *
 * \param  uHlid       - Link ID
 *
 * \return TI_TRUE if data packets on @uHlid should be sent / are received encrypted
 */
Bool_e wlanLinks_GetLinkDataEncryption(uint32_t uHlid);


typedef uint32_t (*TWlanLinkCmp)(TWlanLinkInfo *link, void *context);

/**
 * \fn     wlanLinks_FindLink
 * \brief  Traverse role specific links with a compare function. When TI_OK is
 *         returned from the compare function, we stop traversing the links.
 */
void wlanLinks_FindLink(uint8_t  netIfId,
                        TWlanLinkCmp linkCmp,
                        void *context);

/**
 * \fn     wlanLinks_GetNetIfId
 * \brief  Get Link NetIf ID
 *
 * \param hWlanLinks - A handle to wlanLinks object
 * \param uHlid  - Link ID
 *
 * \return The NetIf ID
 */
tiwdrv_netif_id_e wlanLinks_GetNetIfId(uint32_t uHlid);

/**
 * \fn     wlanLinks_IncrementSecuritySeqNum
 * \brief  Increment the link security sequence number by the given increment (needed after recovery
 *         for connection continuity)
 *
 * \param hWlanLinks - A handle to wlanLinks object
 * \param uHlid      - Link ID
 * \param uIncrement - The increment to add to the sequence number
 *
 * \return TI_OK/TI_NOK
 */
void wlanLinks_IncrementSecuritySeqNum(uint32_t uHlid, uint8_t uIncrement);

void wlanLinks_IncrementSecuritySeqNumMultiLink(uint32_t *aSeqNumIncrTable);

/**
 * \fn     wlanLinks_GetSecuritySeqNum
 * \brief  Get the link security sequence number (after recovery) 
 *
 * \param hWlanLinks - A handle to wlanLinks object
 * \param uHlid      - Link ID
 * \param pSecuritySeqNumLow - outputs the lower 16 bits of the seq-num 
 * \param pSecuritySeqNumLow - outputs the upper 32 bits of the seq-num 
 *
 * \return TI_OK/TI_NOK
 */
uint32_t wlanLinks_GetSecuritySeqNum( uint32_t uHlid,
                                      uint16_t *pSecuritySeqNumLow,
                                      uint32_t *pSecuritySeqNumHigh);

/**
 * \fn     wlanLinks_IncrementTxSessionId
 * \brief  Increment the link Tx session ID (cyclic) upon link start
 *
 * \param hWlanLinks - A handle to wlanLinks object
 * \param uHlid      - Link ID
 *
 * \return The Tx session ID after incremented
 */
uint8_t wlanLinks_IncrementTxSessionId(uint32_t uHlid);


/**
 * \fn     ResetLinkSecuritySeqNum
 * \brief  Reset WlanLink Security Sequence Number
 *
 * Note: The assumption here is that all accesses to WlanLink DB
 *       are performed in signle context
 * \param pwlanLinks - WlanLinks module pointer
 * \param uHlid - HLID of the link
 * \return none
 */
uint32_t wlanLinks_ResetLinkSecuritySeqNum(uint32_t uHlid);

#endif /*  _WLAN_LINKS_H_*/


