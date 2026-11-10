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
/** \file wlanLinks.c
 *  \brief Wlan Links database
 *
 *  \see wlanLinks.h
 */


#include "tx_hw_queue_api.h"
#include "tw_driver.h"
#include "wlan_links.h"
#include "802_11defs.h"
#include "paramOut.h"
#include "gtrace.h"
#include "osi_kernel.h"
#include "wlan_links.h"
#include "common.h"
#include "cme_defs.h"
/* Constants */

TWlanLinks *ghWlanLinks = NULL;

/* Enumerations */


/* Typedefs */

/* Internal functions prototypes */
static void ResetLinkInfo(TWlanLinks *pWlanLinks, uint32_t uHlid);
static void SetLinkInfo(TWlanLinks *pWlanLinks, TWlanLinkInfo *pLinkInfo, uint32_t uHlid, uint8_t wps);

/* Public functions implementation */

/**
 * \fn     wlanLinks_Create
 * \brief  create WlanLinks module
 */
TWlanLinks *wlanLinks_Create()
{
    HOOK(HOOK_WLAN_LINKS);

    if ((ghWlanLinks = os_zalloc(sizeof(TWlanLinks))) == NULL)
    /* Failed to allocate control block */
    {
        Report("ERROR ! TWlanLinks alloc failed");
        ASSERT_GENERAL(0);
        return NULL;
    }

    return ghWlanLinks;
}

/**
 * \fn     wlanLinks_Destroy
 * \brief  destroy WlanLinks module
 */
uint32_t wlanLinks_Destroy()
{
    TWlanLinks   *pWlanLinks;
    uint32_t    status = OK;

    HOOK(HOOK_WLAN_LINKS);

    if (ghWlanLinks != NULL)
    {
        pWlanLinks = ghWlanLinks;

        /* Free pre-allocated control block */
        os_free(pWlanLinks);
    }
    return status;
}

/**
 * \fn     wlanLinks_Init
 * \brief  init WlanLinks module
 */
void wlanLinks_Init ()
{
    int i;
    TWlanLinks *pWlanLinks = wlanLinks_Create();

    pWlanLinks->nFree = WLANLINKS_MAX_LINKS;
    for (i=0; i < WLANLINKS_MAX_LINKS; i++)
    {
        ResetLinkInfo(pWlanLinks, i);
    }
}

uint32_t wlanLinks_AddLink(  TWlanLinkInfo *pLinkInfo, uint32_t uHlid, uint32_t uSessionId, const uint8 *pMacAddr, uint8 wps)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    TInternalWlanLinkInfo  *pLinks = pWlanLinks->aLinks;

    if(pLinks[uHlid].info.eState != WLANLINK_STATE_FREE)
    {
        return NOK;
    }
    GTRACE(GRP_DRIVER_CC33, "wlanLinks_AddLink(): link entry %u ", uHlid);


    /* Fill link info */
    SetLinkInfo(pWlanLinks, pLinkInfo, uHlid, wps);

    /*set link dynamic parameters*/
    pLinks[uHlid].info.eState = WLANLINK_STATE_IDLE;
    pLinks[uHlid].info.bInactive = FALSE;
    pLinks[uHlid].info.uTxSessionId = uSessionId;


    /* Copy MAC address */
    MAC_COPY (pLinks[uHlid].info.tMacAddr, pMacAddr);


    return OK;
}

uint32_t wlanLinks_RemoveLink(uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_RemoveLink(): Failed to free link entry - Invalid uHlid %d!", uHlid);
        return NOK;
    }
    GTRACE(GRP_DRIVER_CC33, " wlanLinks_FreeLink(): link entry %u ", uHlid);


    if (pWlanLinks->aLinks[uHlid].info.eState == WLANLINK_STATE_FREE)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_FreeLink(): Failed to free link entry %u - the entry is already free!", uHlid);
        Report("\n\rwlanLinks_FreeLink(): Failed to free link entry %u - the entry is already free!", uHlid);
        return NOK;
    }

    ResetLinkInfo(pWlanLinks, uHlid);

    return OK;
}

uint8_t wlanLinks_ModetoFwRoleId(tiwdrv_if_mode_e eIfMode)
{
    if(eIfMode == TIWDRV_IF_MODE_STA)
    {
        return (__FW_STA_ROLE_ID__);
    }
    else if(eIfMode == TIWDRV_IF_MODE_SAP)
    {
        return(__FW_AP_ROLE_ID__);
    }
    else
    {
        return (eIfMode-1);
    }
}


uint32_t wlanLinks_GetLink(uint32_t uHlid, TInternalWlanLinkInfo **pLinkInfo)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    if (uHlid >= WLANLINKS_MAX_LINKS)//17 is AP broadcast link
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_ReadLinkInfo():  Invalid uHlid : %u!", uHlid);
        Report("\n\rwlanLinks_ReadLinkInfo():  Invalid uHlid : %u!\n\r", uHlid);
        return NOK;
    }

    if (pWlanLinks->aLinks[uHlid].info.eState == WLANLINK_STATE_FREE)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_ReadLinkInfo(): The link %u doesn't free!", uHlid);
        Report("\n\rERROR !! wlanLinks_ReadLinkInfo(): The link %u doesn't free eState: %d!\n\r", uHlid,pWlanLinks->aLinks[uHlid].info.eState);
        return NOK;
    }
    //GTRACE(GRP_DRIVER_CC33, "wlanLinks_GetLink(): link entry %u ", uHlid);

    *pLinkInfo = &(pWlanLinks->aLinks[uHlid]);
    return OK;
}

uint32_t wlanLinks_LinkMacFind(uint8 uNetIf, const uint8 *pMacAddr)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    TInternalWlanLinkInfo  *pLinks = pWlanLinks->aLinks;
    int i;
    int j;

    HOOK(HOOK_WLAN_LINKS);

    for (i=0; i<WLANLINKS_MAX_LINKS; i++)
    {
        if (pLinks[i].info.uNetIfId != uNetIf)
        {          
            /* netif must be the same */
            continue;
        }

        for (j=MAC_ADDR_LEN-1; j>=0; j--)
        {
            if (pLinks[i].info.tMacAddr[j] != pMacAddr[j])
            {
                /* different MAC, skip to next entry */
                break;
            }
        }
        if (j < 0)
        {
            /* Found, return index */
            return i;

        }
    }

    return INVALID_LINK; /* invalid */
}

uint32_t wlanLinks_GetBroadcastLink()
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    uint32_t i;

    HOOK(HOOK_WLAN_LINKS);

    for (i=WLANLINKS_MAX_LINKS - 1; i != 0; i--)
    {
        if(pWlanLinks->aLinks[i].info.eType == WLANLINK_TYPE_BRCST)
        {
            return i;
        }
    }

    return INVALID_LINK; /* invalid */
}

void wlanLinks_getPeerList(int32_t* numOfPeers, uint8_t** mac_addr_peer_list)
{
    int i=0, link = 0;
    TWlanLinks *pWlanLinks = ghWlanLinks;
    uint8_t *p_mac_addr_peer_list = NULL;//[MAX_NUM_OF_AP_UNICAST_LINKS][6];

    *numOfPeers = 0;
    p_mac_addr_peer_list = os_malloc(WLANLINKS_MAX_LINKS * MAC_ADDR_LEN);
    if (p_mac_addr_peer_list == NULL)
    {
        Report("\n\rERROR !! allocation for addr_peer_list failed\n\r");
        *mac_addr_peer_list = NULL;
        return;
    }

    for (link = 0; link < WLANLINKS_MAX_LINKS; link++)
    {
        if ((pWlanLinks->aLinks[link].info.eState == WLANLINK_STATE_IDLE) &&
            (pWlanLinks->aLinks[link].info.eIfMode == TIWDRV_IF_MODE_SAP) &&
            (pWlanLinks->aLinks[link].info.uNetIfId == TIWDRV_NETIF_ID_SAP) &&
            (pWlanLinks->aLinks[link].info.eType == WLANLINK_TYPE_SPECIFIC ))
        {
            MAC_COPY((uint8_t*)&p_mac_addr_peer_list[i], pWlanLinks->aLinks[link].info.tMacAddr);

            i += MAC_ADDR_LEN;
            (*numOfPeers)++;
        }
    }
    *mac_addr_peer_list = p_mac_addr_peer_list;
}

#ifdef WLANLINKS_ALLOCATE_NEW
/**
 * \fn     wlanLinks_AllocateNew
 * \brief  Allocate new Wlan Link
 */
uint32_t wlanLinks_AllocateNew(  TWlanLinkInfo *pLinkInfo, uint32_t *pHlid, uint32_t privSize)
{
    int i;
    TWlanLinks *pWlanLinks = ghWlanLinks;
    TInternalWlanLinkInfo  *pLinks = pWlanLinks->aLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (!pWlanLinks->nFree)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_AllocateNew(): Failed to allocate new link - WlanLinks DB is Full!");
        *pHlid = WLANLINKS_INVALID_HLID;
        return NOK;
    }

    if (pLinkInfo->eType == WLANLINK_TYPE_SYSTEM)
    {
        i = WLANLINKS_SYSTEM_HLID;
    }
    else
    {
        for (i = WLANLINKS_SYSTEM_HLID + 1; i < WLANLINKS_MAX_LINKS; i++)
        {
            if (pLinks[i].info.eState == WLANLINK_STATE_FREE)
                break;
        }
    }

    /* This shouldn't happen, just if the DB is inconsistent*/
    if (i == WLANLINKS_MAX_LINKS)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_AllocateNew(): Failed to allocate new link - inconsistency in WlanLinks DB!");
        *pHlid = WLANLINKS_INVALID_HLID;
        return NOK;
    }

    pLinks[i].pPeerDescr = NULL;
    pLinks[i].uPeerDescSize = 0;
    if (privSize > 0) {
        pLinks[i].pPeerDescr = os_zalloc(privSize);
        if (!pLinks[i].pPeerDescr) {
            GTRACE(GRP_DRIVER_CC33,
                   "wlanLinks_AllocateNew(): Failed to allocate %d private "
                   "memory for link", privSize);
            *pHlid = WLANLINKS_INVALID_HLID;
            return NOK;
        }
        os_memset(pLinks[i].pPeerDescr, 0,privSize);
        pLinks[i].uPeerDescSize = privSize;
    }

    pWlanLinks->nFree--;
    /* Fill link info */
    SetLinkInfo(pWlanLinks, pLinkInfo, i, 0);

    /*set link dynamic parameters*/
    pLinks[i].info.eState = WLANLINK_STATE_IDLE;
    pLinks[i].info.bInactive = FALSE;
    pLinks[i].info.uSecuritySeqNumLow = 0;
    pLinks[i].info.uSecuritySeqNumHigh = 0;

    *pHlid = pLinks[i].info.uHlid;

#ifndef CC33xx
    /* Update TWD for TxHwQueue optimizations (not written to FW) */
    txHwQueue_AddLink(pLinks[i].info.uHlid, (pLinks[i].info.eType == WLANLINK_TYPE_SPECIFIC));
#endif
    return OK;
}
#endif
/**
 * \fn     wlanLinks_UpdateLinkInfo
 * \brief  Update Wlan Link data except dynamic parameters
 */
uint32_t wlanLinks_UpdateLinkInfo(  TWlanLinkInfo *pLinkInfo, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    TInternalWlanLinkInfo  *pLinks = pWlanLinks->aLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_UpdateLinkInfo(): Failed to update link entry - Invalid uHlid - %u!", uHlid);
        return NOK;
    }

    if (pLinks[uHlid].info.eState == WLANLINK_STATE_FREE)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_UpdateLinkInfo(): Failed to update link entry - the link %u doesn't exist!", uHlid);
        return NOK;
    }

    SetLinkInfo(pWlanLinks,pLinkInfo,uHlid, 0);

    return OK;
}

/**
 * \fn     wlanLinks_ReadLinkInfo
 * \brief  Read Wlan Link data
 */
uint32_t wlanLinks_ReadLinkInfo(  TWlanLinkInfo *pLinkInfo, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_ReadLinkInfo():  Invalid uHlid : %u!", uHlid);
        return NOK;
    }

    if (pWlanLinks->aLinks[uHlid].info.eState == WLANLINK_STATE_FREE)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_ReadLinkInfo(): The link %u doesn't exist!", uHlid);
        return NOK;
    }

    os_memcpy(pLinkInfo, &pWlanLinks->aLinks[uHlid].info, sizeof(TWlanLinkInfo));
    return OK;
}

uint32_t wlanLinks_UpdateLinkPMFEnabled( uint32_t uHlid, Bool_e isPmfEnable)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    TInternalWlanLinkInfo  *aLinks = pWlanLinks->aLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_UpdateLinkPMFEnabled(): Failed to update link entry - Invalid uHlid - %u!", uHlid);
        //CME_PRINT_REPORT_ERROR("\r\nwlanLinks_UpdateLinkPMFEnabled(): Failed to update link entry - Invalid uHlid - %u!", uHlid);
        return NOK;
    }

    if (aLinks[uHlid].info.eState == WLANLINK_STATE_FREE)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_UpdateLinkPMFEnabled(): Failed to update link entry - the link %u doesn't exist!", uHlid);
        //CME_PRINT_REPORT_ERROR("\r\nwlanLinks_UpdateLinkPMFEnabled(): Failed to update link entry - the link %u doesn't exist!", uHlid);
        return NOK;
    }

    aLinks[uHlid].info.bPMFEncription = isPmfEnable;

    return OK;
}

#if 0
/**
 * \fn     wlanLinks_FreeLink
 * \brief  Free Wlan Link
 */
uint32_t wlanLinks_FreeLink(  uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_FreeLink(): Failed to free link entry - Invalid uHlid %d!", uHlid);
        return NOK;
    }

    if (pWlanLinks->nFree == WLANLINKS_MAX_LINKS)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_FreeLink(): Failed to free link entry %u - WlanLinks DB inconsistency detected!", uHlid);
        return NOK;
    }

    if (pWlanLinks->aLinks[uHlid].info.eState == WLANLINK_STATE_FREE)
    {
        GTRACE(GRP_DRIVER_CC33, " wlanLinks_FreeLink(): Failed to free link entry %u - the entry is already free!", uHlid);
        return NOK;
    }

    if (pWlanLinks->aLinks[uHlid].pPeerDescr != NULL) {
        os_free(pWlanLinks->aLinks[uHlid].pPeerDescr);
        pWlanLinks->aLinks[uHlid].pPeerDescr = NULL;
        pWlanLinks->aLinks[uHlid].uPeerDescSize = 0;
    }

    pWlanLinks->nFree++;
    ResetLinkInfo(pWlanLinks, uHlid);
#ifndef CC33xx
    /* Update TWD for TxHwQueue optimizations (not written to FW) */
    txHwQueue_RemoveLink(uHlid);
#endif
    return OK;
}

/**
 * \fn     wlanLinks_GetPeerDescr
 * \brief  Get Peer description of a link
 */
uint32_t wlanLinks_GetPeerDescr(  void *pPeerDesc, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        GTRACE(GRP_DRIVER_CC33, "wlanLinks_GetPeerDescr(): Failed to get Peer Description for HLID %u - Invalid uHlid!", uHlid);
        return NOK;
    }

    if (pWlanLinks->aLinks[uHlid].info.eState == WLANLINK_STATE_FREE) {
        GTRACE(GRP_DRIVER_CC33, "wlanLinks_GetPeerDescr(): Link %d is not allocated!", uHlid);
        return NOK;
    }

    if (!pPeerDesc)
    {
        GTRACE(GRP_DRIVER_CC33, "wlanLinks_GetPeerDescr(): Input Peer Description is NULL (HLID %u)!", uHlid);
        return NOK;
    }
    if(!pWlanLinks->aLinks[uHlid].pPeerDescr)
    {
        GTRACE(GRP_DRIVER_CC33, "wlanLinks_GetPeerDescr(): Failed to get Peer Description for HLID %u!", uHlid);
        return NOK;
    }
    os_memcpy(pPeerDesc, pWlanLinks->aLinks[uHlid].pPeerDescr, pWlanLinks->aLinks[uHlid].uPeerDescSize);

    return OK;
}

/**
 * \fn     wlanLinks_SetPeerDescr
 * \brief  Set Peer description of link
 */
uint32_t wlanLinks_SetPeerDescr(  void *pPeerDesc, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        GTRACE(GRP_DRIVER_CC33, "wlanLinks_SetPeerDescr(): Failed to get Peer Description for HLID %u - Invalid uHlid!", uHlid);
        return NOK;
    }

    if (pWlanLinks->aLinks[uHlid].info.eState == WLANLINK_STATE_FREE) {
        GTRACE(GRP_DRIVER_CC33, "wlanLinks_SetPeerDescr(): Link %d is not allocated!", uHlid);
        return NOK;
    }

    if (!pPeerDesc || !pWlanLinks->aLinks[uHlid].pPeerDescr)
    {
        GTRACE(GRP_DRIVER_CC33, "wlanLinks_SetPeerDescr(): Failed to get Peer Description for HLID %u - Input pointer is NULL!", uHlid);
        return NOK;
    }

    os_memcpy(pWlanLinks->aLinks[uHlid].pPeerDescr, pPeerDesc, pWlanLinks->aLinks[uHlid].uPeerDescSize);

    return OK;
}

/**
 * \fn     wlanLinks_GetPeerDescrPointer
 * \brief  Get a pointer to the required peer description
 */
uint32_t wlanLinks_GetPeerDescrPointer(  void **pPeerDesc, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        GTRACE(GRP_DRIVER_CC33, "wlanLinks_GetPeerDescrPointer(): Failed to get Peer Description for HLID %u - Invalid uHlid!", uHlid);
        return NOK;
    }

    if (pWlanLinks->aLinks[uHlid].info.eState == WLANLINK_STATE_FREE) {
        GTRACE(GRP_DRIVER_CC33, "wlanLinks_GetPeerDescrPointer(): Link %d is not allocated!", uHlid);
        return NOK;
    }

    if (!pPeerDesc)
    {
        GTRACE(GRP_DRIVER_CC33, "wlanLinks_GetPeerDescrPointer(): Failed to get Peer Description for HLID %u - Input pointer is NULL!",
             uHlid);
        return NOK;
    }

    *pPeerDesc = pWlanLinks->aLinks[uHlid].pPeerDescr;

    return OK;
}
#endif

#if  0
/**
 * \fn     wlanLinks_SetLinkState
 * \brief  Set Wlan Link state
 */
uint32_t wlanLinks_SetLinkState(  EWlanLinkState eState, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return NOK;

    pWlanLinks->aLinks[uHlid].info.eState = eState;

    return OK;

}
#endif
/**
 * \fn     wlanLinks_GetLinkState
 * \brief  Get Wlan Link state
 */
uint32_t wlanLinks_GetLinkState(  EWlanLinkState *eState, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return NOK;

    if (!eState)
        return NOK;

    *eState = pWlanLinks->aLinks[uHlid].info.eState;

    return OK;

}

/**
 * \fn     wlanLinks_SetLinkInactivity
 * \brief  Set Wlan Link inactivity status
 */
uint32_t wlanLinks_SetLinkInactivity(  Bool_e bInactivity, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return NOK;

    pWlanLinks->aLinks[uHlid].info.bInactive = bInactivity;

    return OK;
}

/**
 * \fn     wlanLinks_GetLinkInactivity
 * \brief  Get Wlan Link nactivity status
 */
uint32_t wlanLinks_GetLinkInactivity(  Bool_e *pInactivity, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return NOK;

    if (!pInactivity)
        return NOK;

    *pInactivity = pWlanLinks->aLinks[uHlid].info.bInactive;

    return OK;

}

/**
 * \fn     wlanLinks_SetDeauthReason
 * \brief  Set Wlan Link deauthentication reason
 */
uint32_t wlanLinks_SetDeauthReason(  uint32_t uReason, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return NOK;

    pWlanLinks->aLinks[uHlid].info.uDeauthReason = uReason;

    return OK;
}

/**
 * \fn     wlanLinks_GetDeauthReason
 * \brief  Get Wlan Link deauthentication reason
 */
uint32_t wlanLinks_GetDeauthReason(  uint32_t *pReason, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return NOK;

    if (!pReason)
        return NOK;

    *pReason = pWlanLinks->aLinks[uHlid].info.uDeauthReason;

    return OK;

}

/**
 * \fn     wlanLinks_GetLinkType
 * \brief  Get Wlan Link type
 */
uint32_t wlanLinks_GetLinkType(  linkType_e *eType, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return NOK;

    if (!eType)
        return NOK;

    *eType = pWlanLinks->aLinks[uHlid].info.eType;

    return OK;
}

/**
 * \fn     wlanLinks_GetNetIfId
 * \brief  Get the Link network if id
 */
uint32_t wlanLinks_GetNetifInfo(  uint32_t uHlid, uint8_t* pNetifId, tiwdrv_if_mode_e* pNetifMode)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return NOK;

    if ((NULL == pNetifId) || (NULL == pNetifMode))
        return NOK;

    *pNetifId   = pWlanLinks->aLinks[uHlid].info.uNetIfId;
    *pNetifMode = pWlanLinks->aLinks[uHlid].info.eIfMode;

    return OK;
}
#if 0 // TODO: check if need to implement
/**
 * \fn     wlanLinks_SetLinkRates
 * \brief  Set Wlan Link rates
 */
uint32_t wlanLinks_SetLinkRates(  TRateSets *pRates, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    if (uHlid >= WLANLINKS_MAX_LINKS || !pRates)
        return NOK;

    pWlanLinks->aLinks[uHlid].info.tLinkRates = *pRates;

    return OK;
}

/**
 * \fn     wlanLinks_GetLinkRates
 * \brief  Get Wlan Link rates
 */
uint32_t wlanLinks_GetLinkRates(  TRateSets *pRates, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    if (uHlid >= WLANLINKS_MAX_LINKS || !pRates)
        return NOK;

    *pRates = pWlanLinks->aLinks[uHlid].info.tLinkRates;

    return OK;
}
#endif

uint32_t wlanLinks_GetLinkAid(  uint32_t *pAid, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS || !pAid)
            return NOK;

    *pAid = pWlanLinks->aLinks[uHlid].info.uAid;

    return OK;
}


uint32_t wlanLinks_SetLinkAid(  uint32_t uAid, uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
                return NOK;

    pWlanLinks->aLinks[uHlid].info.uAid = uAid;

    return OK;
}

void wlanLinks_SetBroadcastPn(AESKey_rxPN_Tid_t *broadcastPn, uint16_t pn0_15, uint32_t pn16_47)
{
    uint8_t i = 0;

    for (i=0; i < NUM_TRAFFIC_CATEGORIES + 1; i++)
    {
        broadcastPn->rxPN16[i] = pn0_15;
        broadcastPn->rxPN32[i] = pn16_47;
    }

    return;
}

void wlanLinks_SetLinkPn(uint32_t uHlid, uint8_t KeyID, uint16_t pn0_15, uint32_t pn16_47)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    uint8_t i = 0;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return;
    if (KeyID >= 4)
        return;
    
    for (i = 0; i < NUM_TRAFFIC_CATEGORIES + 1; i++)
    {
        pWlanLinks->aLinks[uHlid].info.SecuritySeqNumLow[i] = pn0_15;
        pWlanLinks->aLinks[uHlid].info.SecuritySeqNumHigh[i] = pn16_47;
    }

    return;
}

Bool_e wlanLinks_CheckLinkPn(uint32_t uHlid, dot11_rsn_header_t *pRsnHdr, uint8_t frameTId, Bool_e pnValidated)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    uint16_t pn0_15 = WPA_GET_LE16 (&(pRsnHdr->pn0));
    uint32_t pn16_47 = WPA_GET_LE32 (&(pRsnHdr->pn2));

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return FALSE;

    if (!pnValidated)
    {
        if (pWlanLinks->aLinks[uHlid].info.SecuritySeqNumHigh[frameTId] > pn16_47)
        {
            return FALSE;
        }
        if (pWlanLinks->aLinks[uHlid].info.SecuritySeqNumHigh[frameTId] == pn16_47)
        {
            if (pWlanLinks->aLinks[uHlid].info.SecuritySeqNumLow[frameTId] >= pn0_15)
            {
                return FALSE;
            }
        }
    }
    else
    {
        CME_PRINT_REPORT("\n\rre-key: starting to use new key. New PN: 0x%08x%04x\n\r", pn16_47, pn0_15);
    }

    pWlanLinks->aLinks[uHlid].info.SecuritySeqNumHigh[frameTId] = pn16_47;
    pWlanLinks->aLinks[uHlid].info.SecuritySeqNumLow[frameTId] = pn0_15;
    
    return TRUE;
}

void wlanLinks_SetLinkDataEncryption(  uint32_t uHlid, Bool_e bEncrypted)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return;

    pWlanLinks->aLinks[uHlid].info.bDataEncrypted = bEncrypted;
}

Bool_e wlanLinks_GetLinkDataEncryption(  uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return FALSE;

    return pWlanLinks->aLinks[uHlid].info.bDataEncrypted;
}

/**
 * \fn     wlanLinks_FindLink
 * \brief  Traverse role specific links with a compare function. When OK is
 *         returned from the compare function, we stop traversing the links.
 */
void wlanLinks_FindLink(uint8_t  netIfId,
                        TWlanLinkCmp linkCmp,
                        void *context)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    int i;

    HOOK(HOOK_WLAN_LINKS);

    for (i = 0; i < WLANLINKS_MAX_LINKS; i++)
    {
        if ((pWlanLinks->aLinks[i].info.eState == WLANLINK_STATE_FREE) ||
                (pWlanLinks->aLinks[i].info.uNetIfId != netIfId))
            continue;

        if (OK == linkCmp(&pWlanLinks->aLinks[i].info, context))
            return;
    }
}

tiwdrv_netif_id_e wlanLinks_GetNetIfId(  uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;

    HOOK(HOOK_WLAN_LINKS);

    return pWlanLinks->aLinks[uHlid].info.uNetIfId;
}
#ifdef COMPILE_DEAD_FUNC
void wlanLinks_IncrementSecuritySeqNum( uint32_t uHlid, uint8_t uIncrement)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    TWlanLinkInfo *info;
    uint16_t uNewSeqNumLow;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        return;
    }

    info = &pWlanLinks->aLinks[uHlid].info;

    /* Add increment to low 16 bit, and if wrapped then increment the high 32 bit by 1 */
    uNewSeqNumLow = info->uSecuritySeqNumLow + uIncrement;
    if (uNewSeqNumLow < info->uSecuritySeqNumLow)
    {
        info->uSecuritySeqNumHigh++;
    }
    info->uSecuritySeqNumLow = uNewSeqNumLow;

    return;
}

void wlanLinks_IncrementSecuritySeqNumMultiLink(uint32_t *aSeqNumIncrTable)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    TWlanLinkInfo *info;
    uint16_t uNewSeqNumLow;
    uint32_t i;

    HOOK(HOOK_WLAN_LINKS);

    for (i=0 ; i<WLANLINKS_MAX_LINKS; i++)
    {
        if (aSeqNumIncrTable[i])
        {

            info = &pWlanLinks->aLinks[i].info;

            /* Add increment to low 16 bit, and if wrapped then increment the high 32 bit by 1 */
            uNewSeqNumLow = info->uSecuritySeqNumLow + aSeqNumIncrTable[i];
            if (uNewSeqNumLow < info->uSecuritySeqNumLow)
            {
                info->uSecuritySeqNumHigh++;
            }
            info->uSecuritySeqNumLow = uNewSeqNumLow;
        }
    }

    return;
}

uint32_t wlanLinks_GetSecuritySeqNum(uint32_t uHlid,
                                     uint16_t *pSecuritySeqNumLow,
                                     uint32_t *pSecuritySeqNumHigh)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    TWlanLinkInfo *info;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return NOK;

    info = &pWlanLinks->aLinks[uHlid].info;

    *pSecuritySeqNumLow  = info->uSecuritySeqNumLow;
    *pSecuritySeqNumHigh = info->uSecuritySeqNumHigh;
    return OK;
}
#endif
uint8_t wlanLinks_IncrementTxSessionId(  uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    TWlanLinkInfo *pLinkInfo;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        return TX_SESSION_ID_INVALID;
    }

    pLinkInfo = &pWlanLinks->aLinks[uHlid].info;
    pLinkInfo->uTxSessionId++;
    if (pLinkInfo->uTxSessionId > TX_SESSION_ID_MAX)
    {
        pLinkInfo->uTxSessionId = TX_SESSION_ID_MIN;
    }

    return pLinkInfo->uTxSessionId;
}

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
uint32_t wlanLinks_ResetLinkSecuritySeqNum(  uint32_t uHlid)
{
    TWlanLinks *pWlanLinks = ghWlanLinks;
    TWlanLinkInfo *info;
    uint8_t i = 0;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        return NOK;
    }

    info = &pWlanLinks->aLinks[uHlid].info;

    // initialize PN: MAX_KEYS_NUM=4
    for (i=0; i<NUM_TRAFFIC_CATEGORIES+1; i++)
    {
        info->SecuritySeqNumLow[i] = 0;
        info->SecuritySeqNumHigh[i] = 0;
    }

    return OK;
}



/**************************************************************************/
/*      LOCAL FUNCTIONS                                                   */
/**************************************************************************/

/**
 * \fn     ResetLinkInfo
 * \brief  Reset WlanLink entry data
 *
 * Note: The assumption here is that all accesses to WlanLink DB
 *       are performed in signle context
 * \param pwlanLinks - WlanLinks module pointer
 * \param uHlid - HLID of the link
 * \return none
 */
static void ResetLinkInfo(TWlanLinks *pWlanLinks, uint32_t uHlid)
{
    os_memset(&(pWlanLinks->aLinks[uHlid].info), 0, sizeof(pWlanLinks->aLinks[uHlid].info));
    pWlanLinks->aLinks[uHlid].info.uHlid = uHlid;
    pWlanLinks->aLinks[uHlid].info.eState = WLANLINK_STATE_FREE;
}

/**
 * \fn     SetLinkInfo
 * \brief  Set Wlan Link date
 *
 * Note 1: The assumption here is that all accesses to WlanLink
 *       DB are performed in signle context
 * Note 2: The function doesn't set dynamic parameters of a
 * link, such as state
 * \param pWlanLinks - WlanLinks module pointer
 * \param pLinkInfo - input Link Info
 * \param uHlid - HLID of the link
 * \return none
 */
static void SetLinkInfo(TWlanLinks *pWlanLinks, TWlanLinkInfo *pLinkInfo, uint32_t uHlid, uint8_t wps)
{
    TInternalWlanLinkInfo  *aLinks = pWlanLinks->aLinks;

    HOOK(HOOK_WLAN_LINKS);

    aLinks[uHlid].info.eIfMode  = pLinkInfo->eIfMode;
    aLinks[uHlid].info.eType = pLinkInfo->eType;
    aLinks[uHlid].info.uTxPow = pLinkInfo->uTxPow;
    aLinks[uHlid].info.uQuality = pLinkInfo->uQuality;
    aLinks[uHlid].info.uAid = pLinkInfo->uAid;
    //aLinks[uHlid].info.tLinkRates = pLinkInfo->tLinkRates;
    aLinks[uHlid].info.uNetIfId = pLinkInfo->uNetIfId;
	// This flag indicates that this link is currently created using WPS
    aLinks[uHlid].info.wps = wps;

}
