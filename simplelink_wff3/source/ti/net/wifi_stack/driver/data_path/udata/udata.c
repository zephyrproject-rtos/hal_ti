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
/** \file   udata.c 
 *  \brief  The API functions of the upper data path (UDATA) component (Tx & Rx previously included in the UWD).
 * 
 *  \see    udata.h, udata_Api.h
 */

#define __FILE_ID__  FILE_ID_55
#include <osi_kernel.h>
#include <trnspt_thread.h>
#include "public_share.h"
#include "802_11defs.h"
#include "ti_qos_types.h"
#include "ethernet.h"
#include "paramOut.h"
#include "udata_api.h"
#include "udata_net_api.h"
#include "udata.h"
#include "rx_api.h"
#include "tx_ctrl_api.h"
#include "tx_mgmt_queue_api.h"
#include "tx_data_queue_api.h"
#include "wlan_links.h"
#include "cme_fw_api.h"
#include "udata_api.h"
#include "tx_ctrl_api.h"
#include "default_params.h"
#include "rx.h"
#include "cme_defs.h"

/* mapping table : interface mode to fw role */
const RoleType_e UdataNetIfToRole[TIWDRV_IF_MODE_MAX] = 
{
    [TIWDRV_IF_MODE_SYS]    = ROLE_ID_NONE,
    [TIWDRV_IF_MODE_STA]    = ROLE_STA,
    [TIWDRV_IF_MODE_SAP]    = ROLE_AP,
    [TIWDRV_IF_MODE_P2PDEV] = ROLE_DEVICE,
    [TIWDRV_IF_MODE_P2PCL]  = ROLE_P2P_CL,
    [TIWDRV_IF_MODE_P2PGO]  = ROLE_P2P_GO,
    [TIWDRV_IF_MODE_IBSS]   = ROLE_IBSS,
    [TIWDRV_IF_MODE_NETMON] = ROLE_NONE
};

TUdata *gUdataCB = NULL;
extern dbg_cntr_trnspt_t g_stat_trnpt;

/* ======================== Common Module API ======================== */

/* \brief  Create the module 
 */ 
TUdata * udata_Create(void)
{
    uint32_t i;

    HOOK(HOOK_UDATA);
    /* Allocate module object */
    gUdataCB = (TUdata *)os_zalloc(sizeof(TUdata));

    if (!gUdataCB)
    {
       //GTRACE(1, "udata_Create(): Allocation failed!!\r\n"));
        return NULL;
    }

    /* Enable intra-BSS bridge by default for all roles (allows AP clients to communicate) */
    for (i = 0; i < MAX_NUM_WLAN_ROLE_IDS; i++)
    {
        gUdataCB->aIntraBssBridgeEnable[i] = 1;
    }

    /* Create internal modules */
    if (NULL == rxData_create())
    {
        udata_Destroy();
        return NULL;
    }

    if (NULL == txCtrl_Create())
    {
        udata_Destroy();
        return NULL;
    }

    if (NULL == txDataQ_Create())
    {
        udata_Destroy();
        return NULL;
    }
    if (NULL == txMgmtQ_Create())
    {
        udata_Destroy();
        return NULL;
    }
    return gUdataCB;
}


/* \brief  Destroy the module. 
 */ 
uint32_t udata_Destroy(void)
{
    TUdata *pUdata = gUdataCB;

    HOOK(HOOK_UDATA);

    if (pUdata == NULL)
    {
        return NOK;
    }

    /* Destroy internal modules */
    txCtrl_Unload();
    txDataQ_Destroy();
    txMgmtQ_Destroy();
    rxData_unLoad();

    /* Free module object */
    os_free(pUdata);
    
    return OK;
}


/* \brief  Init required handles 
 */ 
uint32_t udata_Init(TUdata *pUdata)
{
    /* Initialize internal modules */
    rxData_init(pUdata);
    txCtrl_Init(pUdata);
    txDataQ_Init(pUdata);
    txMgmtQ_Init(pUdata);

    /* Save modules handles */
    pUdata->uGenericEthertype = ETHERTYPE_EAPOL;
    udata_RegisterMgmtRxHandler((TMgmtRxHandler)CME_NotifyRxMngPack, (TMgmtRxHandler)CME_RxEapol);
    udata_RegisterRxFromUnknownHandler((TMgmtRxHandler)CME_RxFromUnknownData);
    pUdata->udataparams.TxSendPaceThresh = TX_SEND_PACE_THRESH_DEF;
    pUdata->udataparams.TxSendPaceTimeoutMsec = TX_SEND_PACE_TIMEOUT_MSEC_DEF;
    udata_SetParam(pUdata);
    txCtrl_SetDefaults();
    txMgmtQ_SetDefaults();
	return OK;
}


/* \brief   Set the udata main parameters
 */
uint32_t udata_SetParam(TUdata *pUdata)
{
    TUdataInitParams TUdataSetParams;
    TUdataSetParams.TxSendPaceThresh = pUdata->udataparams.TxSendPaceThresh;
    TUdataSetParams.TxSendPaceTimeoutMsec = pUdata->udataparams.TxSendPaceTimeoutMsec;

    txDataQ_Set(TUdataSetParams);

    return OK;
}

#if 0 //TODO can it be removed?
/* \brief   generic getter API for non-UWD modules
 */
uint32_t udata_GetParam(paramInfo_t *param)
{
    TUdata *pUdata = gUdataCB ;
    uint32_t err = 0;

   //Report(REPORT_SEVERITY_INFORMATION, "udata_GetParam(): param=0x%x \r\n", param->paramType);

    switch (param->paramType)
    {
    case TI_PARAM_CLSFR_TYPE:
        txDataClsfr_GetClsfrType(&(param->content.ctrlDataClsfrType));
        break;

    case TI_PARAM_TX_CTRL_COUNTERS:
        txCtrlParams_GetTxCtrlCounters(param->content.pTxDataCounters);
        break;

    case TI_PARAM_GENERIC_ETHERTYPE:
        param->content.uGenericEthertype = pUdata->uGenericEthertype;
        break;

    default:
       //Report(REPORT_SEVERITY_ERROR, "udata_GetParam(): PARAMETER NOT SUPPORTED\r\n");
        err = PARAM_NOT_SUPPORTED;
        break;
    }

    return err;
}


/* \brief   generic setter API for non-UWD modules
 */
uint32_t udata_SetParam(paramInfo_t *param)
{
    TUdata *pUdata = gUdataCB ;
    uint32_t err = 0;

   //Report(REPORT_SEVERITY_INFORMATION, "udata_SetParam(): param=0x%x \r\n", param->paramType);

    switch (param->paramType)
    {
    case TI_PARAM_CLSFR_CONFIG:
        err = txDataClsfr_InsertClsfrEntry(&param->content.ctrlDataClsfrInsertTable);
        break;

    case TI_PARAM_CLSFR_REMOVE_ENTRY:
        err = txDataClsfr_RemoveClsfrEntry(&param->content.ctrlDataClsfrInsertTable);
        break;

    case TI_PARAM_TX_CTRL_RESET_COUNTERS:
        txCtrlParams_ResetCounters();
        break;

    case TI_PARAM_GENERIC_ETHERTYPE:
        pUdata->uGenericEthertype = param->content.uGenericEthertype;
        break;

    default:
       //Report(REPORT_SEVERITY_ERROR, "udata_SetParam(): PARAMETER NOT SUPPORTED\r\n");
        return PARAM_NOT_SUPPORTED;
    }

    return err;
}
#endif

/* ======================== General UData Control ======================== */

/* \brief   discards all queued packets
 */
void udata_ClearQueues(void)
{
    HOOK(HOOK_UDATA);

    txDataQ_ClearQueues();
    txMgmtQ_ClearQueues();
}
#if 0
/* \brief   Notify the udata that chip recovery process was done
 */
void udata_NotifyRecovery(void)
{
    HOOK(HOOK_UDATA);

    rxData_NotifyFwReset();
    txMgmtQ_NotifyFwReset();
    txCtrl_NotifyFwReset ();
}
#endif
/* \brief   registers a callback to be invoked (in UWD context) upon a MIC Failure
 */
void udata_RegisterMicFailureHandler(TMicFailureHandler cb, void *ctx)
{
    TUdata *pUdata = gUdataCB ;

    HOOK(HOOK_UDATA);

    pUdata->fMicFailureCb     = cb;
    pUdata->hMicFailureHandle = ctx;
}
/* \brief   adds a link (links with type specific also require udata_SetPeerParams() to be able to xmit).
 */
void udata_AddLink(uint32_t         link, 
                   uint32_t         uHandoverLink, 
                   linkType_e       eLinkType,
                   tiwdrv_if_mode_e eIfMode,
                   RoleID_t         eLmacRoleId,
                   uint32_t         uRxTag,
                   uint8_t          uMgmtRatePolicyIdx, 
                   uint8_t          uDataRatePolicyIdx)
{
    TUdata *pUdata = gUdataCB ;

    HOOK(HOOK_UDATA);

    pUdata->aLinkInfo[link].bIsAllocated       = TRUE;   
    pUdata->aLinkInfo[link].uHandoverLink      = uHandoverLink;   
    pUdata->aLinkInfo[link].eLinkType          = eLinkType;   
    /* convert if mode to fw role */
    pUdata->aLinkInfo[link].eRoleType = (RoleType_e)UdataNetIfToRole[eIfMode];

    pUdata->aLinkInfo[link].eFwRoleId          = eLmacRoleId;
    pUdata->aLinkInfo[link].uNetIfId           = uRxTag;
    pUdata->aLinkInfo[link].uMgmtRatePolicyIdx = uMgmtRatePolicyIdx;
    pUdata->aLinkInfo[link].uDataRatePolicyIdx = uDataRatePolicyIdx;

    pUdata->aNetidToMode[uRxTag] = eIfMode;
    pUdata->aNetToRoleId[uRxTag] = eLmacRoleId;

    /* If it's a system, global or bcast link, save its ID for quick retrieval */
    if (eLinkType == WLANLINK_TYPE_SYSTEM)
    {
        pUdata->uSystemHlid = link;
    }
    else if (eLinkType == WLANLINK_TYPE_GLOBAL)
    {
        pUdata->aGlobalHlids[eLmacRoleId] = link;
    }
    else if (eLinkType == WLANLINK_TYPE_BRCST)
    {
        /* TODO - this setting for STA should be fixed for "make before break" feature!! */
        pUdata->aBcastHlid[uRxTag] = link;
    }
}
/* \brief   sets the MAC address of an LMAC role
 */
void udata_SetRoleMac(RoleID_t eLmacRoleId, TMacAddr mac)
{
    TUdata *pUdata = gUdataCB ;

    HOOK(HOOK_UDATA);

    MAC_COPY(pUdata->aRoleLocalMac[eLmacRoleId], mac);
}

/* \brief   updates the link's peer parameters 
 */
void udata_SetPeerParams(uint32_t link, const TMacAddr mac, Bool_e bWmeEnabled)
{
    TUdata *pUdata = gUdataCB ;

    HOOK(HOOK_UDATA);

    /* Update the link attributes */
    pUdata->aWmeEnabled[link] = bWmeEnabled;
    txDataQ_LinkMacAdd((uint8_t)link, mac);

    /* Update the UP-downgrade mapping. */
    txCtrl_UpdateQueuesMapping();
}

/* \brief   updates the link's peer parameters 
 */
void udata_SetTxSessionId(uint32_t link, uint8_t uSessionId)
{
    TUdata *pUdata = gUdataCB ;
    pUdata->aSessionId[link] = uSessionId;
}

/* \brief   closes the link and cleans up any resources allocated by udata_AddLink
 */
void udata_RemoveLink(uint32_t link)
{
    TUdata *pUdata = gUdataCB ;
    uint32_t i;

    HOOK(HOOK_UDATA);

    udata_SetTxState(link, LINK_STATE_CLOSED);
    udata_SetRxState(link, LINK_STATE_CLOSED);
    pUdata->aLinkInfo[link].bIsAllocated = FALSE;   
    pUdata->aWmeEnabled[link] = FALSE;

    txMgmtQ_ClearLink(link);
    txDataQ_ClearLink(link);

    /* Clear the link from Bcast and Global link arrays if found there */
    for (i = 0; i < TIWDRV_NETIF_NUM; i++) 
    {
        if (pUdata->aBcastHlid[i] == link)
        {
            pUdata->aBcastHlid[i] = 0;
        }
    }
    for (i = 0; i < MAX_NUM_WLAN_ROLE_IDS; i++)
    {
        if (pUdata->aGlobalHlids[i] == link)
        {
            pUdata->aGlobalHlids[i] = 0;
        }
    }

    /* Update the UP-downgrade mapping after the WME update. */
    txCtrl_UpdateQueuesMapping();
}


/* \brief   toggles encryption for EAPOL packets
 */
void udata_SetEapolEncryption(uint32_t link, Bool_e enabled)
{
    HOOK(HOOK_UDATA);

    txCtrlParams_SetEapolEncryptionStatus(link, enabled);
}

/* \brief   toggles encryption for data packets
 */
void udata_SetDataEncryption(uint32_t link, Bool_e enabled, Bool_e bDropBcast, Bool_e bDropUcast)
{
    HOOK(HOOK_UDATA);

    txCtrlParams_SetDataEncryptMode(link, enabled);
    rxData_SetExcludeUnencrypted(link, bDropBcast, bDropUcast);
}


/* \brief   toggles pmf encryption for mgmt packets
 */
void udata_SetMgmtEncryption(uint32_t link, Bool_e bPMFEncrypt)
{
    HOOK(HOOK_UDATA);

    txCtrlParams_SetMgmtEncryptMode(link, bPMFEncrypt);
}


/* \brief   sets the link security type
 */
void udata_SetEncryptionType(uint32_t link, EKeyType eKeyType)
{
    TUdata *pUdata = gUdataCB ;

    HOOK(HOOK_UDATA);

    pUdata->aLinkInfo[link].eKeyType = eKeyType;   
}

/* \brief   get the link security type
 */
EKeyType udata_GetEncryptionType(uint32_t link)
{
    TUdata *pUdata = gUdataCB ;

    HOOK(HOOK_UDATA);

    return pUdata->aLinkInfo[link].eKeyType;
}

/* \brief   toggles the intra-BSS bridge (to forward packet within the same BSS)
 */
void udata_SetIntraBssBridge(RoleID_t eLmacRoleId, Bool_e enabled)
{
    TUdata *pUdata = gUdataCB ;

    HOOK(HOOK_UDATA);

    pUdata->aIntraBssBridgeEnable[eLmacRoleId] = enabled;
}

/* \brief   sets the lifetime of an MSDU
 */
void udata_SetMsduLifetime(RoleID_t eLmacRoleId, uint8_t ac, uint32_t lifetime)
{
    txCtrlParams_setAcMsduLifeTime(eLmacRoleId, ac, lifetime);
}

/* \brief   sets the ACK policy for TX on a specific link
 */
void udata_SetTxAckPolicy(uint32_t link, uint8_t ac, AckPolicy_e policy)
{
    HOOK(HOOK_UDATA);

    txCtrlParams_setAcAckPolicy(link, ac, policy);
}

/* \brief   sets the ACK policy for RX on a specific link
 */
void udata_SetRxBaPolicy(uint32_t link, uint8_t uPolicyMap)
{
    BLOCK_ACK_PRINT_REPORT("\r\n BLOCK ACK :SetRxBaPolicy link :%d uPolicyMap:%d\n", link,uPolicyMap);
    GTRACE(GRP_DRIVER_CC33, "BLOCK ACK :SetRxBaPolicy link :%d uPolicyMap:%d\n", link,uPolicyMap);

    RxQueue_SetInternalRxBaPolicy(link, uPolicyMap);
}

/* \brief   sets the TX state of a link
 */
void udata_SetTxState(uint32_t link, ELinkState state)
{
    TUdata *pUdata = gUdataCB ;

    HOOK(HOOK_UDATA);

    if (state == LINK_STATE_CLOSED) 
    {
        txDataQ_LinkMacRemove(link);
        if (pUdata->aLinkInfo[link].eRoleType == ROLE_STA || pUdata->aLinkInfo[link].eRoleType == ROLE_P2P_CL)
            pUdata->aBcastHlid[pUdata->aLinkInfo[link].uNetIfId] = 0;
    }
    else if (state == LINK_STATE_OPEN && 
             (pUdata->aLinkInfo[link].eRoleType == ROLE_STA || pUdata->aLinkInfo[link].eRoleType == ROLE_P2P_CL))
    {
        /* For STA based roles, OPEN state is when we set the bcast link*/
        pUdata->aBcastHlid[pUdata->aLinkInfo[link].uNetIfId] = link;
    }

    txMgmtQ_SetLinkState(link, state);
}

/* \brief   gets the TX state of a link
 */
ELinkState udata_GetTxState(uint32_t link)
{
    HOOK(HOOK_UDATA);

    return txMgmtQ_GetLinkState(link);
}

/* \brief   sets the RX state of a link
 */
void udata_SetRxState(uint32_t link, ELinkState state)
{
    HOOK(HOOK_UDATA);

    if (state == LINK_STATE_CLOSED) 
    {
        RxQueue_CloseAllLinkBaSessions(link);
    }
    rxData_SetLinkState(link, state);
}

/* ======================== QoS Control ======================== */

/* \brief   sets whether Admission Control is allowed, and required, on the specific AC
 */
void udata_SetAdmissionStatus(uint8_t link, uint8_t ac, EAdmissionState required, ETrafficAdmState state)
{
    txCtrlParams_SetAcAdmissionStatus(link, ac, required, state);
}

/* \brief   sets the allocated medium time for the specified AC
 */
uint32_t udata_SetMediumTime(uint32_t link, uint8_t ac, uint16_t uMediumTime)
{
    return txCtrlParams_SetAdmissionCtrlParams(link, ac, uMediumTime, (uMediumTime!=0));
}

/* \brief   starts a Traffic Stream measurement
 */
uint32_t udata_StartTsMeasurement(uint32_t link, TTsmParams* params)
{
    return txCtrl_UpdateTSMParameters(link, params);
}


/* ======================== Tx/Rx ======================== */

/* \brief   registers a callback the UData can invoke to dispatch an RX management packet
 */
void udata_RegisterMgmtRxHandler(TMgmtRxHandler mgmtcb , TMgmtRxHandler eapolcb)
{
    TUdata *pUdata = gUdataCB ;

    HOOK(HOOK_UDATA);

    pUdata->fMgmtRxCb     = mgmtcb;
    pUdata->fEapolRxCb    = eapolcb;
}

void udata_RegisterRxFromUnknownHandler(TMgmtRxHandler cb)
{
    TUdata *pUdata = gUdataCB;

    HOOK(HOOK_UDATA);

    pUdata->fRxFromUnknownCb = cb;
}

void udata_RegisterSecuritySeqHandler(TSecuritySeqHandler cb, void *ctx)
{
    HOOK(HOOK_UDATA);

    txCtrl_RegisterSecuritySeqHandler(cb, ctx);
}

TTxCtrlBlk *udata_AllocTxDataPacket(uint32_t uPayloadLen,uint32_t uHeaderLen,TEthernetHeader *pEthHead )
{

    TTxCtrlBlk   *pPktCtrlBlk;
    uint8_t      *pPktBuffer;
    uint32_t      payloadLenAligned;

    HOOK(HOOK_UDATA);

    if (uHeaderLen > MAX_HEADER_SIZE)
    {
       //Report(REPORT_SEVERITY_ERROR, "udata_AllocMgmtPacket: uHeaderLen(= %d) is bigger than MAX_HEADER_SIZE(= %d)\r\n", uHeaderLen, MAX_HEADER_SIZE);
        return NULL;
    }

    payloadLenAligned = M_ALIGN_TO_4_BYTES(uPayloadLen);

    /* Allocate a TxCtrlBlk */
    pPktCtrlBlk = TWD_txCtrlBlk_Alloc(0);
    if (pPktCtrlBlk == NULL)
    {
        TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rWarning !udata_AllocTxDataPacket: TWD_txCtrlBlk_Alloc failed\r\n");
        return NULL;
    }

    /* allocate payload buffer */
    pPktBuffer = txCtrl_AllocPacketBuffer(pPktCtrlBlk, payloadLenAligned);
    if ((pPktBuffer == NULL) && (payloadLenAligned != 0))
    {
       //Report(REPORT_SEVERITY_ERROR, "udata_AllocMgmtPacket: txCtrl_AllocPacketBuffer failed\r\n");
        TWD_txCtrlBlk_Free (pPktCtrlBlk);
        os_free(pPktCtrlBlk);
        return NULL;
    }

    BUILD_TX_TWO_BUF_PKT_BDL( pPktCtrlBlk,//OSPREY_MX-7
                              pEthHead,
                              sizeof(pPktCtrlBlk->aPktNabHdr),sizeof(TxIfDescriptor_t),uHeaderLen,
                              pPktBuffer,payloadLenAligned,uPayloadLen);



    /* Fill pointers and lengths (some are already filled in txCtrl_AllocPacketBuffer and BUILD_TX_TWO_BUF_PKT_BDL) */
    pPktCtrlBlk->tTxPktParams.pInputPkt = (void *)pPktBuffer;

    /* Return the allocated descriptor */
    return pPktCtrlBlk;
}


/* \brief   allocate a Tx management packet descriptor plus related buffers
 */
TMgmtPktDesc *udata_AllocTxMgmtPacket(uint32_t uHeaderLen,uint32_t uPayloadLen,TEthernetHeader *pEthHead)
{

    TMgmtPktDesc  *pPktDesc;
    TTxCtrlBlk    *pPktCtrlBlk;
    uint8_t      *pPktBuffer;
    uint32_t      payloadLenAligned;

    HOOK(HOOK_UDATA);

    if (uHeaderLen > MAX_HEADER_SIZE)
    {
        CME_PRINT_REPORT_ERROR("\r\n Error ! udata_AllocMgmtPacket: uHeaderLen(= %d) is bigger than MAX_HEADER_SIZE(= %d)\r\n", uHeaderLen, MAX_HEADER_SIZE);
        return NULL;
    }

    payloadLenAligned = M_ALIGN_TO_4_BYTES(uPayloadLen);

    /* allocate packet descriptor */
    pPktDesc = (TMgmtPktDesc *)os_zalloc(sizeof(TMgmtPktDesc));
    if (!pPktDesc)
    {
        CME_PRINT_REPORT_ERROR("\r\n Warning !udata_AllocMgmtPacket: TMgmtPktDesc allocation failed\r\n");
        return NULL;
    }


    /* Allocate a TxCtrlBlk */
    pPktCtrlBlk = TWD_txCtrlBlk_Alloc(1);
    if (pPktCtrlBlk == NULL)
    {
        CME_PRINT_REPORT_ERROR("\n\rError !udata_AllocMgmtPacket: TWD_txCtrlBlk_Alloc failed\r\n");
        os_free(pPktDesc);
        return NULL;
    }

    /* allocate payload buffer */
    pPktBuffer = txCtrl_AllocPacketBuffer(pPktCtrlBlk, payloadLenAligned);
    if (pPktBuffer == NULL)
    {
        TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rError !udata_AllocMgmtPacket: txCtrl_AllocPacketBuffer failed\r\n");
        TWD_txCtrlBlk_Free (pPktCtrlBlk);
        os_free(pPktDesc);
        return NULL;
    }


    if(pEthHead ==NULL) //mgmt packet, this is the common case
    {
        /* Fill the bus-transaction structure and descriptor length fields */
        BUILD_TX_TWO_BUF_PKT_BDL( pPktCtrlBlk,//OSPREY_MX-7
                                  &(pPktCtrlBlk->aPktNabHdr),
                                  sizeof(pPktCtrlBlk->aPktNabHdr),sizeof(TxIfDescriptor_t),uHeaderLen,
                                  pPktBuffer,payloadLenAligned,uPayloadLen);
    }
    else//data packet which is send as mngmt from host point of view like EAPOL
    {
        /* Fill the bus-transaction structure and descriptor length fields */
        BUILD_TX_TWO_BUF_PKT_BDL( pPktCtrlBlk,//OSPREY_MX-7
                                  pEthHead,
                                  sizeof(pPktCtrlBlk->aPktNabHdr),sizeof(TxIfDescriptor_t),uHeaderLen,
                                  pPktBuffer,payloadLenAligned,uPayloadLen);

    }

    /* Fill pointers and lengths (some are already filled in txCtrl_AllocPacketBuffer and BUILD_TX_TWO_BUF_PKT_BDL) */
    pPktCtrlBlk->tTxPktParams.pInputDesc = (void *)pPktDesc;
    pPktDesc->nabHeader = &(pPktCtrlBlk->aPktNabHdr);
    pPktDesc->uNabHeaderLen = sizeof(pPktCtrlBlk->aPktNabHdr);
    pPktDesc->header = &(pPktCtrlBlk->aPktHdr);
    pPktDesc->uHeaderLen = uHeaderLen;
    pPktDesc->payload = pPktBuffer;
    pPktDesc->uPayloadLen = uPayloadLen;

    /* Return the allocated descriptor */
    return pPktDesc;
}

/* \brief   submits a management packet for transmission
 */
uint32_t udata_SendTxMgmtPacket(TMgmtPktDesc *pkt)
{
    Bool_e       bIsExternalContext = (pkt->flags & PKTF_EXTERNAL_CONTEXT) ? TRUE : FALSE;
    TTxCtrlBlk  *pPktCtrlBlk;
    TInternalWlanLinkInfo *pLinkInfo;
    TUdata *pUdata = gUdataCB ;


    if(wlanLinks_GetLink(pkt->link, &pLinkInfo) != 0)
    {
        return NOK;
    }

    /* Extract the PktCtrlBlk address from the packet descriptor (allocated in udata_AllocMgmtPacket) */
    pPktCtrlBlk = udataNet_ExtractTxCtrlBlkFromDesc(pkt);

    /* Translate packet type to udata internal type */
    switch (pkt->ePktType)
    {
    case UDATA_TX_PKT_TYPE_WLAN_MGMT:
        pPktCtrlBlk->tTxPktParams.uPktType = TX_PKT_TYPE_MGMT;
        break;
    case UDATA_TX_PKT_TYPE_ETHER_EAPOL:
        pPktCtrlBlk->tTxPktParams.uPktType = TX_PKT_TYPE_EAPOL;
        break;
    case UDATA_TX_PKT_TYPE_WLAN_DATA:
        pPktCtrlBlk->tTxPktParams.uPktType = TX_PKT_TYPE_WLAN_DATA;
        break;
    case UDATA_TX_PKT_TYPE_DUMMY:
        pPktCtrlBlk->tTxPktParams.uPktType = TX_PKT_TYPE_DUMMY_BLKS;
        break;
    default:
        Report("\n\rudata_SendMgmtPacket: Bad packet type = %d\r\n", pkt->ePktType);
        GTRACE(1, "udata_SendMgmtPacket: Bad packet type = %d", pkt->ePktType);
        return NOK;
    }

    /* Set the other packet attributes */
    //pPktCtrlBlk->tTxDescriptor.startTime = osi_GetTimeMS();
    pPktCtrlBlk->tTxDescriptor.hlid      = (uint8_t)pkt->link;
    pPktCtrlBlk->tTxDescriptor.tid       = MAX_USER_PRIORITY; /* Always set highest TID for mgmt-queues packets. */
    pPktCtrlBlk->tTxPktParams.uFwRoleId  = wlanLinks_ModetoFwRoleId(pLinkInfo->info.eIfMode);
    pPktCtrlBlk->tTxPktParams.uRoleType  = (uint8_t)UdataNetIfToRole[pLinkInfo->info.eIfMode];//pLinkInfo->info.eType;
    pPktCtrlBlk->tTxPktParams.fCb        = pkt->fTxCompleteCb;
    pPktCtrlBlk->tTxPktParams.hCb        = pkt->hTxCompleteCtx;
    pPktCtrlBlk->tTxPktParams.extraSpareKeyCount = 0;


#if 0
    SET_PKT_RATE_POLICY(pPktCtrlBlk, pUdata->aLinkInfo[pkt->link].uMgmtRatePolicyIdx);
#endif
    //Report("\n\rudata_SendMgmtPacket: packet type = %d role:%d uMgmtRatePolicyIdx:%d\r\n", pkt->ePktType,pPktCtrlBlk->tTxPktParams.uFwRoleId, pUdata->aLinkInfo[pkt->link].uMgmtRatePolicyIdx);
    //GTRACE(1, "udata_SendMgmtPacket: packet type = %d role:%d", pkt->ePktType, pPktCtrlBlk->tTxPktParams.uFwRoleId);
    /* Enqueue packet in the mgmt-queues and run the scheduler. */
    return txMgmtQ_Xmit(pPktCtrlBlk, bIsExternalContext);
}

/* \brief   Upon FW reset (recovery) suspends the transmission of packets (may be queued, but will not be handled
 *          until udata_Resume() is called). Also closes all Rx BA sessions without notifying the FW
 */
void udata_Suspend(void)
{

    txMgmtQ_SuspendTx();

    /* Close all Rx BA sessions without notifying the FW (we are turning it off) */
    RxQueue_CloseAllBaSessions();
}

/* \brief   resumes the transmission of packets. Packets that were queued since a call
 *          to udata_SuspendTx() will be processed
 */
void udata_Resume(void)
{
    HOOK(HOOK_UDATA);

    txMgmtQ_ResumeTx();
}

/* \brief   Temporarily suspends the transmission of packets (may be queued, but will not be handled
 *          until udata_ResumeTx() is called).
 */
void udata_SuspendTx(void)
{
    HOOK(HOOK_UDATA);

    txMgmtQ_SuspendTx();
}

/* \brief   resumes the transmission of packets after suspended by a call to udata_Suspend()
 */
void udata_ResumeTx(void)
{
    txMgmtQ_ResumeTx();
}


/* ======================== Statistics ======================== */

/* \brief   reads a link's TX/RX statistics
 */
uint32_t udata_GetLinkStats(uint32_t link, TLinkDataCounters* stats)
{
    HOOK(HOOK_UDATA);

    /* Get Rx Link Counters*/
    rxData_GetLinkDataCounters(link, stats);

    /* Get Rx Link Counters*/
    txCtrlParams_GetDataLinkCounter(link, stats);

    return OK;
}

/* \brief   resets a link's TX/RX statistics
 */
void udata_ResetLinkStats(uint32_t link)
{
    HOOK(HOOK_UDATA);

    rxData_ResetLinkCounters(link);
    txCtrlParams_resetLinkCounters(link);
}

/* \brief   reads the RX statistics (global, not per-link)
 */
uint32_t udata_GetGlobalRxStats(dbg_cntr_trnspt_t *buf)
{
    HOOK(HOOK_UDATA);

    rxData_GetCounters(buf);
    return OK;
}

void udata_ResetGlobalRxStats()
{
    rxData_ResetCounters();
}
/* \brief   Provides the link current Rx rate
 */
tiwdrv_rate_e udata_GetRxRate(uint32_t link)
{
    if (link < WLANLINKS_MAX_LINKS)
    {
        return rxData_GetCurrentRate(link);
    }
    else
        return TIW_DRV_RATE_INVALID;
}

/* \brief   Provides the link current Tx rate
 */
tiwdrv_rate_e udata_GetTxRate(uint32_t link)
{
    if (link < WLANLINKS_MAX_LINKS)
    {
        return txCtrlParams_GetTxRate(link);
    }
    else
        return TIW_DRV_RATE_INVALID;
}


/**********************************************************************************************************
 
                            Network Interface API Functions
                            ===============================

 Functions published in udataNet_Api.h to be used only from network interface (wlanDrvIf) and not from UWD.
 
 **********************************************************************************************************/

#if 0
/* \brief   Provides the Net-IF related to the specified link ID
 */
uint32_t udataNet_GetNetIfByLink(uint32_t link)
{
    TUdata *pUdata = gUdataCB ;

    HOOK(HOOK_UDATA);

    return pUdata->aLinkInfo[link].uNetIfId;
}
#endif

/* \brief   Provides the link ID related to a Tx management packet from the network stack
 */
uint32_t udataNet_GetTxMgmtLink(uint32_t uNetIfId, TMacAddr mac)
{
    TUdata    *pUdata = gUdataCB ;
    uint8_t uHlid = 0xFF;

    HOOK(HOOK_UDATA);

    if (txDataQ_LinkMacFind(&uHlid, mac) != 0)//if there is no link for this mac address, use the global link
    {
        RoleID_t eFwRoleId = pUdata->aNetToRoleId[uNetIfId];

        if (MAC_MULTICAST(mac))
        {
            uHlid = pUdata->aBcastHlid[eFwRoleId];
        }
        else
        {
            uHlid = pUdata->aGlobalHlids[eFwRoleId];
        }
    }

    return uHlid;
}

/* \brief   Inserts a Tx data packet from the network stack to the driver Tx-data path
 */
uint32_t udataNet_InsertDataPacket(TTxCtrlBlk *pPktCtrlBlk, uint32_t uNetIfId, uint8_t uPacketDtag)
{
    TUdata           *pUdata = gUdataCB ;
    tiwdrv_if_mode_e  eIfMode = pUdata->aNetidToMode[uNetIfId];
    TEthernetHeader  *pEthHead;
    uint32_t          uHlid;
    
    /* At this stage, the first buffer pointer points to the packet Ethernet header */
    pEthHead = (TEthernetHeader *)(pPktCtrlBlk->tTxnStruct.aBuf[TX_BUF_HDR_OFFSET]);

    /* For AP or P2P-GO role, find link ID by dest MAC address. If not found drop the packet */
    if ((TIWDRV_IF_MODE_SAP == eIfMode) || (TIWDRV_IF_MODE_P2PGO == eIfMode))
    {
   //TODO see OSPREY_MX-10 will be solved whne wlan_links is change back to udata links
        if (TI_UNLIKELY(MAC_MULTICAST(pEthHead->dst)))
        {
            uHlid = pUdata->aBcastHlid[uNetIfId];
        }
//        else if (txDataQ_LinkMacFind(&uHlid, pEthHead->dst) != 0)//TODO this line should replace the below line
        else
        {
            uHlid = wlanLinks_LinkMacFind(uNetIfId, (uint8 *)pEthHead->dst);
        }

        if (uHlid == INVALID_LINK)
        {
            /* If the packet can't be queued drop it */
            txCtrl_FreePacket(pPktCtrlBlk, NOK);
            //TX_DATA_SEND_PRINT_ERROR("\n\Error! Wlan_EtherPacketSend txDataQ_LinkMacFind failed :uNetIfId:%d",uNetIfId);
            return NOK;
        }
    }
    /* For STA or P2P-CL, the broadcast and unicast links are the same */
    else
    {
        uHlid = pUdata->aBcastHlid[uNetIfId];
    }

    pPktCtrlBlk->tTxDescriptor.hlid = uHlid;

    /* convert if mode to fw role */
    pPktCtrlBlk->tTxPktParams.uRoleType = UdataNetIfToRole[eIfMode];
    pPktCtrlBlk->tTxPktParams.uFwRoleId = pUdata->aLinkInfo[uHlid].eFwRoleId;
    pPktCtrlBlk->tTxPktParams.extraSpareKeyCount = 0;


    return txDataQ_InsertPacket(pPktCtrlBlk, uPacketDtag);
}


TTxCtrlBlk *udataNet_ExtractTxCtrlBlkFromDesc(TMgmtPktDesc *pkt)
{
    uint32_t    uCtrlBlkHdrOffset; /* offset of aPktHdr field from start of the TxCtrlBlk structure */
    TTxCtrlBlk   *pPktCtrlBlk;

    HOOK(HOOK_UDATA);

    /* Get the PktCtrlBlk address from the header address */
    uCtrlBlkHdrOffset = TI_FIELD_OFFSET(TTxCtrlBlk, aPktHdr[0]);
    pPktCtrlBlk = (TTxCtrlBlk *)((uint32_t)pkt->header - uCtrlBlkHdrOffset);

    return pPktCtrlBlk;
}


/*
 *     Data Path Debug Functions:
 */

#ifdef TI_DBG  

static void printTxRxDbgFunctions(void)
{
    HOOK(HOOK_UDATA);

   //Report(("\n          Tx Dbg Functions        \r\n"));
   //Report(("--------------------------------------\r\n"));

   //GTRACE(1, "301 - Print TxCtrl info.\r\n"));
   //GTRACE(1, "302 - Print TxCtrl Statistics.\r\n"));
   //GTRACE(1, "303 - Print TxDataQueue info.\r\n"));
   //GTRACE(1, "304 - Print TxDataQueue Statistics.\r\n"));
   //GTRACE(1, "305 - Print TxMgmtQueue info.\r\n"));
   //GTRACE(1, "306 - Print TxMgmtQueue Statistics.\r\n"));
   //GTRACE(1, "307 - Print TxCtrlBlk table.\r\n"));
   //GTRACE(1, "308 - Print TxHwQueue info.\r\n"));
   //GTRACE(1, "309 - Print TxXfer info.\r\n"));
   //GTRACE(1, "310 - Print TxResult info.\r\n"));
   //GTRACE(1, "311 - Print TxDataClsfr Classifier Table.\r\n"));

   //GTRACE(1, "320 - Reset TxCtrl Statistics.\r\n"));
   //GTRACE(1, "321 - Reset TxDataQueue Statistics.\r\n"));
   //GTRACE(1, "322 - Reset TxDataClsfr Classifier Table.\r\n"));
   //GTRACE(1, "323 - Reset TxMgmtQueue Statistics.\r\n"));
   //GTRACE(1, "324 - Reset TxResult Statistics.\r\n"));
   //GTRACE(1, "325 - Reset TxXfer Statistics.\r\n"));

   //Report(("\n          Rx Dbg Functions   \r\n"));
   //Report(("--------------------------------------\r\n"));
   //GTRACE(1, "350 - Print Rx block.\r\n"));
   //GTRACE(1, "351 - Print Rx counters.\r\n"));
   //GTRACE(1, "352 - Reset Rx counters.\r\n"));
}

/* \brief   Tx/Rx debug functions distribution
 */
void udataNet_RxTxDebug(uint32_t funcType, void *pParam)
{
    TUdata *pUdata = gUdataCB ;

    HOOK(HOOK_UDATA);

    switch ((ERxTxDbgFunc)funcType)
    {
    case TX_RX_DBG_FUNCTIONS:
        printTxRxDbgFunctions();
        break;

    /*  TX DEBUG FUNCTIONS:
     *  ===================
     */
    case PRINT_TX_CTRL_INFO:
        txCtrlParams_printInfo();
        break;
    case PRINT_TX_CTRL_COUNTERS:
        txCtrlParams_printDebugCounters();
        break;
    case PRINT_TX_DATA_QUEUE_INFO:
        txDataQ_PrintModuleParams();
        break;
    case PRINT_TX_DATA_QUEUE_COUNTERS:
        txDataQ_PrintQueueStatistics();
        break;
    case PRINT_TX_MGMT_QUEUE_INFO:
        txMgmtQ_PrintModuleParams();
        break;
    case PRINT_TX_MGMT_QUEUE_COUNTERS:
        txMgmtQ_PrintQueueStatistics();
        break;
    case PRINT_TX_CTRL_BLK_INFO:
        TWD_PrintTxInfo(TWD_PRINT_TX_CTRL_BLK_TBL);
        break;
    case PRINT_TX_HW_QUEUE_INFO:
        TWD_PrintTxInfo(TWD_PRINT_TX_HW_QUEUE_INFO);
        break;
    case PRINT_TX_XFER_INFO:
        TWD_PrintTxInfo(TWD_PRINT_TX_XFER_INFO);
        break;
    case PRINT_TX_RESULT_INFO:
        TWD_PrintTxInfo(TWD_PRINT_TX_RESULT_INFO);
        break;
    case PRINT_TX_DATA_CLSFR_TABLE:
        txDataClsfr_PrintClsfrTable();
        break;
    case RESET_TX_CTRL_COUNTERS:
        txCtrlParams_resetDbgCounters();
        break;
    case RESET_TX_DATA_QUEUE_COUNTERS:
        txDataQ_ResetQueueStatistics();
        break;
    case RESET_TX_DATA_CLSFR_TABLE:
       //GTRACE(1, "RESET_TX_DATA_CLSFR_TABLE - Not supported!\r\n"));
        break;
    case RESET_TX_MGMT_QUEUE_COUNTERS:
        txMgmtQ_ResetQueueStatistics();
        break;
    case RESET_TX_RESULT_COUNTERS:
        TWD_PrintTxInfo(TWD_CLEAR_TX_RESULT_INFO);
        break;
        case RESET_TX_XFER_COUNTERS:
        TWD_PrintTxInfo(TWD_CLEAR_TX_XFER_INFO);
        break;

    /*  RX DEBUG FUNCTIONS:
     *  ===================
     */
    case PRINT_RX_BLOCK:
       //GTRACE(1, "RX DBG - Print Rx Block \n\r\n"));
        rxData_printRxBlock();
        break;
    case PRINT_RX_COUNTERS:
       //GTRACE(1, "RX DBG - Print Rx counters \n\r\n"));
        rxData_printRxCounters();
        break;
    case RESET_RX_COUNTERS:
       //GTRACE(1, "RX DBG - Reset Rx counters \n\r\n"));
        rxData_resetCounters();
        rxData_resetDbgCounters();
        break;
    default:
        HOOK(HOOK_UDATA);
       //GTRACE(1, "Invalid function type in Debug Tx Function Command: %d\n\r\n", funcType));
        break;
    }
}

#endif /* TI_DBG */



