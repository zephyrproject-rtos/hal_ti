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
/***************************************************************************/
/*                                                                         */
/*      MODULE: Rx.c                                                       */
/*    PURPOSE:  Rx module functions                                        */
/*                                                                         */
/***************************************************************************/
#define __FILE_ID__  FILE_ID_28


#include "cc3xxx_public_types.h"
#include "paramOut.h"
#include "osi_kernel.h"
#include <trnspt_thread.h>
#include "public_share.h"
#include <data_path/ethernet.h>
#include "timer.h"
#include "802_11defs.h"
#include "tw_driver.h"
#include "udata_api.h"
#include "udata.h"
#include "tx_ctrl_api.h"
#include "tx_data_queue_api.h"
#include "rx_api.h"
#include "tx_ctrl.h"
#include "tw_driver.h"
#include "inc_common/rx.h"
#include "mpdu.h"
#include "rx.h"
#include "drv_ti_internal.h"
#include "udata_net_api.h"
//
#define PADDING_INTERNAL_USE_SIZE   16
#define PADDING_ETH_PACKET_SIZE     8
#define PADDING_NEXT_AND_DATA_SIZE  8

#define MSDU_DATA_LEN_LIMIT         5000  /* some arbitrary big number to protect from buffer overflow */
#define FW_TRACE_MSG_MAX_LENGTH     19

#define TWD_CB_TYPE_MASK            0x00ff
extern void _recvNetworkPacket(uint32_t netifid,uint8_t *inbuf, uint32_t inbuf_len);

static int rxData_RequestForBuffer (uint8_t **pBuf, uint32_t aLength);

static uint32_t rxData_ConvertWlanToEthHeader(void *pBuffer, uint16_t *etherType);
static uint32_t rxData_ConvertAmsduToEthPackets(void *pBuffer,ELinkState eLinkConnState);
static void rxData_DataPacketDisptcher(void *pBuffer);
static void rxData_DiscardPacket(void *pBuffer);
static void rxData_RcvPacketInOpenNotify(void *pBuffer);
static void rxData_RcvPacketEapol(void *pBuffer);
static void rxData_RcvPacketData(void *pBuffer);
static uint32_t sendDataPacketToTx(void *pBuffer, uint16_t uLength, uint32_t uHlid);
static void rxData_ReceivePacketFromWlan(void *pBuffer);
uint8_t isEthernet2frame(Wlan_LlcHeader_T* pWlanSnapHeader);
extern void rxData_MissingPktTimeout_task();
extern void InactivityTimerExpire_task();



rxData_t *gRxDataCB = NULL;

typedef struct _rx_head_
{
  void *packet_addr;
} rx_head_t;

typedef struct _padding_next_pkt_size_
{
  uint32_t NextMsduAddr;
  uint8_t  DataPktType;
  uint8_t  padding[3];
} padding_next_pkt_size_t;

#define RX_HEAD_LEN_ALIGNED ((sizeof(rx_head_t) + 0x3) & ~0x3)
#define WSPI_PAD_BYTES          	16     /* Add padding before data buffer for WSPI overhead -- NAB_rx_header_t*/
#define PAYLOAD_ALIGN_PAD_BYTES   	4      /* Add an extra word for alignment the MAC payload in case of QoS MSDU */

/*--------------------------------------------------------------------------------------*/
/* 
 * Allocate BUF Rx packets.
 * Add 16 bytes before the data buffer for WSPI overhead!
 */
void* RxBufAlloc(uint32_t len)
{
    RxIfDescriptor_t *pRxPkt;
    uint8_t          *data;
    uint32_t          alloc_len = len + WSPI_PAD_BYTES + RX_HEAD_LEN_ALIGNED;

    //if Transceiver is on, allocate only from the data pool, even if the packet is MGMNT,
	//because all the packets in that mode are considered data because all of them goes to host.
	pRxPkt = os_zalloc(alloc_len+10);//see OSPREY_MX-13
    if (pRxPkt == NULL)
    {
        /* No error intentionally: this is legal situation. */
        RX_PRINT_HIGH_PRIORITY("\n\rWARNING RxBufAlloc: failed to allocate %d",alloc_len);
        return NULL;
    }

    /* save pkt address, used RxBufFree */
    data = (uint8_t *)pRxPkt;
    data += WSPI_PAD_BYTES+RX_HEAD_LEN_ALIGNED;
    pRxPkt->length = len;
   
    return (void *)data;
}

void  RxBufFree(void* pBuf)		
{
    uint8_t    *data   = pBuf;/*(uint8_t *)((uint32_t)pBuf & ~(uint32_t)0x3)*/;
    RxIfDescriptor_t *pPkt;

    /* restore pkt address */
    data -= (WSPI_PAD_BYTES+RX_HEAD_LEN_ALIGNED);
    pPkt = (RxIfDescriptor_t *)((uint32_t *)data);
    //just to make sure that pkt is freed and not been used later on
    os_memset(data,0,sizeof(uint32_t));
    os_free(pPkt);
}

uint32_t rate_PolicyToDrv (ETxRateClassId ePolicyRate, tiwdrv_rate_e *eAppRate)
{
    tiwdrv_rate_e Rate   = TIW_DRV_RATE_AUTO;
    uint32_t  status     = OK;

    switch (ePolicyRate)
    {
        case txPolicy1    :   Rate =  TIW_DRV_RATE_1M   ;    break;
        case txPolicy2    :   Rate =  TIW_DRV_RATE_2M   ;    break;
        case txPolicy5_5  :   Rate =  TIW_DRV_RATE_5_5M ;    break;
        case txPolicy11   :   Rate =  TIW_DRV_RATE_11M  ;    break;
        case txPolicy22   :   Rate =  TIW_DRV_RATE_22M  ;    break;
        case txPolicy6    :   Rate =  TIW_DRV_RATE_6M   ;    break;
        case txPolicy9    :   Rate =  TIW_DRV_RATE_9M   ;    break;
        case txPolicy12   :   Rate =  TIW_DRV_RATE_12M  ;    break;
        case txPolicy18   :   Rate =  TIW_DRV_RATE_18M  ;    break;
        case txPolicy24   :   Rate =  TIW_DRV_RATE_24M  ;    break;
        case txPolicy36   :   Rate =  TIW_DRV_RATE_36M  ;    break;
        case txPolicy48   :   Rate =  TIW_DRV_RATE_48M  ;    break;
        case txPolicy54   :   Rate =  TIW_DRV_RATE_54M  ;    break;
        case txPolicyMcs0 :   Rate =  TIW_DRV_RATE_MCS_0;    break;
        case txPolicyMcs1 :   Rate =  TIW_DRV_RATE_MCS_1;    break;
        case txPolicyMcs2 :   Rate =  TIW_DRV_RATE_MCS_2;    break;
        case txPolicyMcs3 :   Rate =  TIW_DRV_RATE_MCS_3;    break;
        case txPolicyMcs4 :   Rate =  TIW_DRV_RATE_MCS_4;    break;
        case txPolicyMcs5 :   Rate =  TIW_DRV_RATE_MCS_5;    break;
        case txPolicyMcs6 :   Rate =  TIW_DRV_RATE_MCS_6;    break;
        case txPolicyMcs7 :   Rate =  TIW_DRV_RATE_MCS_7;    break;
        case txPolicyMcs8 :   Rate =  TIW_DRV_RATE_MCS_8;    break;
        case txPolicyMcs9 :   Rate =  TIW_DRV_RATE_MCS_9;    break;
        case txPolicyMcs10 :  Rate =  TIW_DRV_RATE_MCS_10;   break;
        case txPolicyMcs11 :  Rate =  TIW_DRV_RATE_MCS_11;   break;
        case txPolicyMcs12 :  Rate =  TIW_DRV_RATE_MCS_12;   break;
        case txPolicyMcs13 :  Rate =  TIW_DRV_RATE_MCS_13;   break;
        case txPolicyMcs14 :  Rate =  TIW_DRV_RATE_MCS_14;   break;
        case txPolicyMcs15 :  Rate =  TIW_DRV_RATE_MCS_15;   break;
        default:
            status = NOK;
            break;
    }

    if (status == OK)
        *eAppRate = Rate;
    else
        *eAppRate = TIW_DRV_RATE_INVALID;

    return status;
}

/*************************************************************************
*                        rxData_create                                   *
**************************************************************************
* DESCRIPTION:  This function initializes the Rx data module.
*
* INPUT:        hOs - handle to Os Abstraction Layer
*
* OUTPUT:
*
* RETURN:       Handle to the allocated Rx data control block
************************************************************************/
rxData_t* rxData_create (void)
{
    /* alocate Rx module control block */
    gRxDataCB = os_zalloc(sizeof(rxData_t));
    rxData_t *pRxData = gRxDataCB;

    if (!gRxDataCB)
    {
        Report("\n\rERROR rxData_create: failed to allocate");

       //GTRACE(1, "FATAL ERROR: rxData_create(): Error Creating Rx Module - Aborting\r\n"));
        return NULL;
    }

    pRxData->uMissingPktTimeoutContextId = trnspt_RegisterClient (rxData_MissingPktTimeout_task,TRUE);
    pRxData->uInactivityTimeoutContextId = trnspt_RegisterClient (InactivityTimerExpire_task,TRUE);


    return gRxDataCB;
}

void rx_callback(uint32_t hlid, uint8_t *in, uint32_t len)
{
    RxQueue_ReceivePacket(in,len);
}

/***************************************************************************
*                           rxData_config                                  *
****************************************************************************
* DESCRIPTION:  This function configures the Rx Data module
*
* INPUTS:       pStadHandles  - The driver modules handles
*
* OUTPUT:
*
* RETURNS:      void
***************************************************************************/
void rxData_init(TUdata *pUdata)
{
    rxData_t *pRxData = gRxDataCB;
    TRxLinkInfo *pLinkInfo;
    uint32_t uHlid;
    uint32_t i;


    pRxData->pUdata             = pUdata;

    for (i = 0; i < WLANLINKS_MAX_LINKS; i++)
    {
        pRxData->aRxLinkInfo[i].eState = DEF_RX_PORT_STATUS;
        pRxData->aRxLinkInfo[i].bRxDataExcludeUnencryptedUnicast = DEF_EXCLUDE_UNENCYPTED;
        pRxData->aRxLinkInfo[i].bRxDataExcludeUnencryptedBroadcast = DEF_EXCLUDE_UNENCYPTED;
    }

    /*
     * configure rx data dispatcher
     */

    /* port status close */
    pRxData->rxData_dispatchBuffer[LINK_STATE_CLOSED][DATA_DATA_PACKET] = &rxData_DiscardPacket;        /* data  */
    pRxData->rxData_dispatchBuffer[LINK_STATE_CLOSED][DATA_EAPOL_PACKET]= &rxData_DiscardPacket;        /* eapol */

    /* port status open notify */
    pRxData->rxData_dispatchBuffer[LINK_STATE_MGMT][DATA_DATA_PACKET]   = &rxData_RcvPacketInOpenNotify;/* data  */
    pRxData->rxData_dispatchBuffer[LINK_STATE_MGMT][DATA_EAPOL_PACKET]  = &rxData_RcvPacketInOpenNotify;/* eapol */

    /* port status open eapol */
    pRxData->rxData_dispatchBuffer[LINK_STATE_EAPOL][DATA_DATA_PACKET]  = &rxData_DiscardPacket;        /* data  */
    pRxData->rxData_dispatchBuffer[LINK_STATE_EAPOL][DATA_EAPOL_PACKET] = &rxData_RcvPacketEapol;       /* eapol */

    /* port status open */
    pRxData->rxData_dispatchBuffer[LINK_STATE_OPEN][DATA_DATA_PACKET]   = &rxData_RcvPacketData;        /* data  */
    pRxData->rxData_dispatchBuffer[LINK_STATE_OPEN][DATA_EAPOL_PACKET]  = &rxData_RcvPacketEapol;       /* eapol */

    /*
     * init information per link
     */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        pLinkInfo = &pRxData->aRxLinkInfo[uHlid];
        pLinkInfo->eState = LINK_STATE_CLOSED; /* default is link closed */
    }

    RxQueue_Init();


    rx_RegisterAllocationFunction(rxData_RequestForBuffer,pRxData);

    rx_RegisterNextLayerRecvFunction(rx_callback,pRxData,RX_NEXT_LAYER_WLAN);


}

uint32_t rxData_NotifyFwReset(void)
{
    return RxQueue_NotifyFwReset();
}


/***************************************************************************
*                           rxData_unLoad                                  *
****************************************************************************
* DESCRIPTION:  This function unload the Rx data module.
*
* INPUTS:       pRxData - the object
*
* OUTPUT:
*
* RETURNS:      OK - Unload succesfull
*               NOK - Unload unsuccesfull
***************************************************************************/
uint32_t rxData_unLoad(void)
{
    rxData_t *pRxData = gRxDataCB;

    /* check parameters validity */
    if (pRxData == NULL)
    {
        return NOK;
    }

    if (pRxData->hMissingPktTimer.osTimerHandler)
    {
        osi_TimerDelete (&pRxData->hMissingPktTimer);
    }

    RxQueue_DeInit();

    /* free Rx Data controll block */
    os_free(pRxData);
    gRxDataCB = NULL;

    return OK;
}

/******************************************************************************

    GET_SIZE_MPDU_HDR

    DESCRIPTION:    Get MPDU header size.

    PARAMETERS:     hPtr - Pointer to the MPDU header.

    RETURNS:        The header size in bytes.

******************************************************************************/
uint32 GET_SIZE_MPDU_HDR(MPDUHeader_t *hPtr)
{
    uint32_t headerSize = sizeof(MPDUHeader_t);    /* default header size */

    if (IS_MPDU_TYPE_DATA_QOS((hPtr)->frameType))
    {
        if (CHK_FRAME_AP_TO_AP(hPtr) != FALSE)
        {
            headerSize = sizeof(QOS_AP_MPDUHeader_t);
        }
        else
        {
            headerSize = sizeof(QOS_MPDUHeader_t);
        }
    }
    else
    {
        if (CHK_FRAME_AP_TO_AP(hPtr) != FALSE)
        {
            headerSize = sizeof(AP_TO_AP_MPDUHeader_t);
        }

        else if (GET_MPDU_TYPE_SUBTYPE(hPtr->frameType) == FRAME_TYPE_PS_POLL)
        {
            headerSize = sizeof(PsPollHeader_t);
        }

        else if (GET_MPDU_TYPE_SUBTYPE(hPtr->frameType) == FRAME_TYPE_BLOCK_ACK_REQ)
        {
            headerSize = sizeof(BarCompressedFrame_t);
        }

        else if (GET_MPDU_TYPE_SUBTYPE(hPtr->frameType) == FRAME_TYPE_CTS)
        {
            headerSize = sizeof(CTSFrame_t);
        }
    }

    return (headerSize);
}



#define EAPOL_ETHER_TYPE                    0x888E

const LLC_SNAP_Header_t gEapol =
    {
        SNAP_CHANNEL_ID,
        SNAP_CHANNEL_ID,
        LLC_CONTROL_UNNUMBERED_INFORMATION,
        {
            SNAP_OUI_RFC1042_BYTE0,
            SNAP_OUI_RFC1042_BYTE1,
            SNAP_OUI_RFC1042_BYTE2
        },
        HTOWLANS(EAPOL_ETHER_TYPE)
    };

/**********************************************************************************************************************

    SetRxClassification

    DESCRIPTION:    Sets the class of the packet in order to route it to particular host queue.
                    The packet class tag is attached here.

    PARAMETERS:     pointer to RX frame.

    RETURNS:        None.

***********************************************************************************************************************/
PacketClassTag_enum rxData_GetCRxClassification(void *pBuffer)
{
    MPDUHeader_t *rxMPDUHdr = (MPDUHeader_t*) RX_BUF_DATA(pBuffer);
    blockAckActionFrameWitoutHdr_t *baActionFrame;
    uint16_t fc;
    uint8_t  SecureHdrLength = 0;

    fc = le_to_host16((uint16_t)(*((uint16_t*)&rxMPDUHdr->frameType)));


    /************************************************************************/
    /*  A-MSDU frame and QoS                                                */
    /************************************************************************/
    if (IS_MPDU_TYPE_DATA_QOS(rxMPDUHdr->frameType))
    {
        QosControl_t qosCtrl;

        if (CHK_FRAME_AP_TO_AP(rxMPDUHdr))
        {
            QOS_AP_MPDUHeader_t *qosHdr = (QOS_AP_MPDUHeader_t *)RX_BUF_DATA(pBuffer);
            qosCtrl = qosHdr->qosCtrl;
        }
        else
        {
            QOS_MPDUHeader_t *qosHdr = (QOS_MPDUHeader_t *)RX_BUF_DATA(pBuffer);
            qosCtrl = qosHdr->qosCtrl;
        }

        if (qosCtrl & BIT_7)
        {

            return TAG_CLASS_AMSDU;
        }
    }

    /************************************************************************/
    /*  QoS (short frames or during join \ roaming)                         */
    /************************************************************************/
    if ((IS_MPDU_TYPE_DATA_QOS(rxMPDUHdr->frameType)))
    {
        LLC_SNAP_Header_t *lLChdr;
        SecureHdrLength = 0;
        if (IS_WEP_ON(fc) != 0)
        {
            SecureHdrLength = RSN_SEC_LEN;
        }
        /* Advance 4 extra bytes in IEEE80211 header if order bit is on (mostly 11ax support) */
        if (IS_HT_ON(fc))
        {
            SecureHdrLength += IEEE80211_HT_CTL_LEN;
        }

        lLChdr = (LLC_SNAP_Header_t *) (     (uint32_t)rxMPDUHdr
                                        +   GET_SIZE_MPDU_HDR(rxMPDUHdr)
                                        +   SecureHdrLength
                                      );

        if (os_memcmp(lLChdr,&gEapol, sizeof(gEapol)) == 0)
        {
            return TAG_CLASS_EAPOL;
        }
        return TAG_CLASS_QOS_DATA;
    }

    /************************************************************************/
    /*  DATA OR EAPOL                                                               */
    /************************************************************************/
    if (IS_MPDU_TYPE_DATA(rxMPDUHdr->frameType))
    {
        SecureHdrLength = 0;
        if (IS_WEP_ON(fc) != 0)
        {
            SecureHdrLength = RSN_SEC_LEN;
        }
        /* Advance 4 extra bytes in IEEE80211 header if order bit is on (mostly 11ax support) */
        if (IS_HT_ON(fc))
        {
            SecureHdrLength += IEEE80211_HT_CTL_LEN;
        }
        LLC_SNAP_Header_t *lLChdr;
        lLChdr = (LLC_SNAP_Header_t *) (     (uint32_t)rxMPDUHdr
                                        +   GET_SIZE_MPDU_HDR(rxMPDUHdr)
                                        +   SecureHdrLength
                                      );
        if (os_memcmp(lLChdr,&gEapol, sizeof(gEapol)) == 0)
        {
            return TAG_CLASS_EAPOL;
        }
        return TAG_CLASS_DATA;

    }

    if (IS_MPDU_TYPE_CTRL(rxMPDUHdr->frameType))
    {
        /************************************************************************/
        /*  BAR frames                                                          */
        /************************************************************************/
        if (GET_MPDU_TYPE_SUBTYPE(rxMPDUHdr->frameType) == FRAME_TYPE_BLOCK_ACK_REQ)
        {
            return TAG_CLASS_BA_EVENT;
        }
    }
    if (IS_MPDU_TYPE_MGMT(rxMPDUHdr->frameType))
    {
        /************************************************************************/
        /*  BEACON OR PROBE RESPONSE                                            */
        /************************************************************************/
        if ((GET_MPDU_TYPE_SUBTYPE(rxMPDUHdr->frameType)
                == FRAME_TYPE_PROBE_RESPONSE)
                || (GET_MPDU_TYPE_SUBTYPE(rxMPDUHdr->frameType) == FRAME_TYPE_BEACON))
        {
            return TAG_CLASS_BCN_PRBRSP;

        }

        /************************************************************************/
        /*  BA MANAGEMENT                                                       */
        /************************************************************************/
        if (GET_MPDU_TYPE_SUBTYPE(rxMPDUHdr->frameType) == FRAME_TYPE_ACTION)
        {
            SecureHdrLength = 0;
            if (IS_WEP_ON(fc) != 0)
            {
                SecureHdrLength = RSN_SEC_LEN;
            }
            if (IS_HT_ON(fc))
            {
                SecureHdrLength += IEEE80211_HT_CTL_LEN;
            }

            baActionFrame = (blockAckActionFrameWitoutHdr_t*) (((uint32_t)rxMPDUHdr)
                                                           + sizeof(MGMT_Header_t)
                                                           + SecureHdrLength);

            if ((baActionFrame->category == BLOCK_ACK_ACTION_FRAME_CATEGORY)
                    && ((baActionFrame->action == BA_ACTION_DELBA)
                            || (baActionFrame->action == BA_ACTION_ADDBA_REQUEST)))
            {
                return TAG_CLASS_BA_EVENT;
            }
        }
        if ( (!(IS_MPDU_TYPE_DATA_QOS((rxMPDUHdr)->frameType)) &&
                GET_MPDU_TYPE_SUBTYPE(rxMPDUHdr->frameType) == FRAME_TYPE_BLOCK_ACK_REQ))
        {
            BLOCK_ACK_PRINT_REPORT("\n\r RxQueue_ReceivePacket: FRAME_TYPE_BLOCK_ACK_REQ");

            return TAG_CLASS_BA_EVENT;//frame is block-ack request
        }
        /******************************************************************************/
        /*  MANAGEMENT - default for managment frames (not beacon, not BA management) */
        /******************************************************************************/
        return TAG_CLASS_MANAGEMENT;
    }
    return TAG_CLASS_UNKNOWN;
}


/***************************************************************************
*                       rxData_receivePacketFromWlan                       *
****************************************************************************
* DESCRIPTION:  This function is called for each received packet.
*               It distributes management packets to the UWD and 
*                   data packets to the network stack.
*
* INPUTS:       pRxData - the object
*               pBuffer - the received Buffer.
*
* OUTPUT:
*
* RETURNS:
***************************************************************************/
static void rxData_ReceivePacketFromWlan(void *pBuffer)
{
    rxData_t *pRxData = gRxDataCB;
    RxIfDescriptor_t *pRxParams  = (RxIfDescriptor_t *)pBuffer;
    uint8_t          uHlid = pRxParams->hlid;
    PacketClassTag_enum class;

    if (uHlid >= WLANLINKS_MAX_LINKS)
    {
        RX_PRINT_ERROR("\n\rERROR rxData_ReceivePacketFromWlan:illegal uHlid=%d, status=0x%x\r\n", uHlid, pRxParams->status);
        pRxData->rxDataLinkCounters[0].discardWrongHlid++;
        rxData_DiscardPacket(pBuffer);
        return;
    }
    pRxData->rxDataLinkCounters[uHlid].recvFromWlan++;
    pRxData->rxDataLinkCounters[uHlid].recvBytesFromWlan += RX_BUF_LEN(pBuffer);
    class = rxData_GetCRxClassification(pBuffer);

    switch (class)
    {
    case TAG_CLASS_MANAGEMENT:
    case TAG_CLASS_BCN_PRBRSP:
    case TAG_CLASS_IAPP:
#if 0 //the fw does filter the probe response and beacons , only scan or BCN_PRBRSP in device mac will come from the fw
        if(class == TAG_CLASS_BCN_PRBRSP)//OSPREY_MX-18
        {
            EScanRequestType scanTag = (uint8_t)((pRxParams->status) & 0x38) >> 3; // scan tag bit 3:5
            if( scanTag == SCAN_REQUEST_NONE || scanTag > SCAN_NUM_OF_REQUEST_TYPE)//OSPREY_MX-18
            {
                RX_MGMT_PRINT_DETAIL("\n\rrxData_ReceivePacketFromWlan drop beacons and PRBRSP without scan tag");
                RxBufFree(pBuffer);//OSPREY_MX-15
                break;
            }
        }
#endif
        //Report(REPORT_SEVERITY_INFORMATION, "rxData_receivePacketFromWlan(): Forwarding Mgmt packet to UWD, len = %d\r\n", RX_BUF_LEN(pBuffer));
        RX_PRINT("\n\rrxData_receivePacketFromWlan(): Forwarding Mgmt packet to UWD, len = %d", RX_BUF_LEN(pBuffer));
        pRxData->rxDataLinkCounters[uHlid].sendToUwd++;

        /* Forward all management packets to the UWD via callback */
        if (pRxData->pUdata->fMgmtRxCb)
        {
            RX_MGMT_PRINT("\n\rrxData_receivePacketFromWlan(): call CME_NotifyRxMngPack");
            pRxData->pUdata->fMgmtRxCb(pBuffer);//call CME_NotifyRxMngPack
        }
        else 
        {
            //Report(REPORT_SEVERITY_ERROR, "rxData_receivePacketFromWlan(): fMgmtRxCb callback is NULL!!\r\n");
            RX_PRINT_ERROR("n\rERROR rxData_receivePacketFromWlan(): fMgmtRxCb callback is NULL!!");
            RxBufFree(pBuffer);//OSPREY_MX-15
        }
        break;

    case TAG_CLASS_DATA:
    case TAG_CLASS_QOS_DATA:
    case TAG_CLASS_AMSDU:
    case TAG_CLASS_EAPOL:
        {
            //CL_TRACE_START_L3();
            if (class==TAG_CLASS_EAPOL)
            {
                RX_PRINT("\n\rrxData_receivePacketFromWlan() of type  EAPOL or QOS_EAPOL");
            }
            else
            {
                RX_PRINT("\n\rrxData_receivePacketFromWlan(): data packet, dispatch class:%d",class);
            }
            pRxData->rxDataLinkCounters[uHlid].sendToDataDispatcher++;
            rxData_DataPacketDisptcher(pBuffer);
            //CL_TRACE_END_L3("tiwlan_drv.ko", "INHERIT", "RX", ".DataPacket");
            break;
        }

        /* in case of BA event no need to pass it to the network stack - we just free the buffer */
    case TAG_CLASS_BA_EVENT:
        //Report(REPORT_SEVERITY_INFORMATION, " rxData_receivePacketFromWlan(): Received BA event packet type - free the buffer \r\n");
        RX_PRINT("\n\rrxData_receivePacketFromWlan(): Received BA event packet type - free the buffer");
        pRxData->rxDataLinkCounters[uHlid].discardBaEvent++;
        RxBufFree(pBuffer);
        break;

    default:
        //Report(REPORT_SEVERITY_ERROR, " rxData_receivePacketFromWlan(): Received unspecified packet type: %d !!! \r\n", pRxParams->packet_class_tag);
        RX_PRINT_ERROR("\n\rrxData_receivePacketFromWlan(): Received unspecified packet type: %d !!!", class);
        pRxData->rxDataLinkCounters[uHlid].discardUnknownClass++;
        RxBufFree(pBuffer);
        break;
    }
}


void rxData_GetCounters(dbg_cntr_trnspt_t* pCounters)
{
    rxData_t  *pRxData = gRxDataCB;

    pCounters->rxstat_RecvOk = pRxData->rxDataCounters.RecvOk;
    pCounters->rxstat_DirectedBytesRecv = pRxData->rxDataCounters.DirectedBytesRecv;
    pCounters->rxstat_DirectedFramesRecv = pRxData->rxDataCounters.DirectedFramesRecv;
    pCounters->rxstat_MulticastBytesRecv = pRxData->rxDataCounters.MulticastBytesRecv;
    pCounters->rxstat_MulticastFramesRecv = pRxData->rxDataCounters.MulticastFramesRecv;
    pCounters->rxstat_BroadcastBytesRecv = pRxData->rxDataCounters.BroadcastBytesRecv;
    pCounters->rxstat_BroadcastFramesRecv = pRxData->rxDataCounters.BroadcastFramesRecv;
}

void rxData_ResetCounters()
{
    rxData_t  *pRxData = gRxDataCB;

    memset(&pRxData->rxDataCounters, 0, sizeof(TGlobalRxStats) );
}


void rxData_GetLinkDataCounters(uint32_t link, TLinkDataCounters *pLinksDataCounters)
{
    rxData_t  *pRxData = gRxDataCB;

    pLinksDataCounters->recvPktsFromWlan = pRxData->rxDataLinkCounters[link].recvFromWlan;
    pLinksDataCounters->recvBytesFromWlan = pRxData->rxDataLinkCounters[link].recvBytesFromWlan;
}

void rxData_SetExcludeUnencrypted(uint32_t uHlid, Bool_e bDropBcast, Bool_e bDropUcast)
{
    rxData_t *pRxData = gRxDataCB;

    pRxData->aRxLinkInfo[uHlid].bRxDataExcludeUnencryptedBroadcast = bDropBcast;
    pRxData->aRxLinkInfo[uHlid].bRxDataExcludeUnencryptedUnicast = bDropUcast;
}

tiwdrv_rate_e rxData_GetCurrentRate(uint32_t uHlid)
{
    rxData_t *pRxData = gRxDataCB;

    return pRxData->eLastDataPktRate[uHlid];
}

/***************************************************************************
*                       rxData_DataPacketDisptcher                         *
****************************************************************************
* DESCRIPTION:  this function is called upon receving data Buffer,
*               it dispatches the packet to the approciate function according to
*               data packet type and rx port status.
*
* INPUTS:       pRxData - the object
*               pBuffer - the received Buffer.
*
* OUTPUT:
*
* RETURNS:
***************************************************************************/
static void rxData_DataPacketDisptcher(void *pBuffer)
{
    rxData_t *pRxData = gRxDataCB;
    ELinkState eLinkConnState;
    rxDataPacketType_e DataPacketType;
    tiwdrv_rate_e eAppRate;
    RxIfDescriptor_t *pRxParams = (RxIfDescriptor_t*)pBuffer;
    uint8_t uHlid = pRxParams->hlid;

    /* get rx port status */
    eLinkConnState = pRxData->aRxLinkInfo[uHlid].eState;

    if (eLinkConnState == LINK_STATE_CLOSED)
    {
        pRxData->rxDataLinkCounters[uHlid].discardHlidClose++;

        rxData_DiscardPacket(pBuffer);
        return;
    }

    /* save Rx packet rate for statistics */
    if (rate_PolicyToDrv((ETxRateClassId)(pRxParams->rate), &eAppRate) != OK)
    {
        //Report(REPORT_SEVERITY_ERROR , "rxData_DataPacketDisptcher: can't convert hwRate=0x%x\r\n", pRxParams->rate);
    }
    pRxData->eLastDataPktRate[uHlid] = eAppRate;  

    /* A-MSDU ? */
    if (TAG_CLASS_AMSDU == rxData_GetCRxClassification(pBuffer))
    {
        RX_PRINT("\n\rxData_DataPacketDisptcher: rxData_ConvertAmsduToEthPackets");
        rxData_ConvertAmsduToEthPackets(pBuffer,eLinkConnState);
    }
    else
    {
       uint16_t etherType = 0;
       TEthernetHeader * pEthernetHeader;

       /* if Host processes received packets, the header translation from WLAN to ETH is done here */
       rxData_ConvertWlanToEthHeader(pBuffer, &etherType);

       pEthernetHeader = (TEthernetHeader *)RX_ETH_PKT_DATA(pBuffer);

       if (etherType == ETHERTYPE_802_1D)
       {
           //Report(REPORT_SEVERITY_INFORMATION, "rxData_DataPacketDisptcher(): Received VLAN packet - drop it\r\n");
           RX_PRINT_ERROR("\n\rERROR rxData_DataPacketDisptcher(): Received VLAN packet - drop it");
           pRxData->rxDataDbgCounters.rxDroppedDueToVLANIncludedCnt++;
           rxData_DiscardPacket(pBuffer);
           return;
       }
       else if ((BYTE_SWAP_WORD(pEthernetHeader->type) == ETHERTYPE_EAPOL) ||
                (BYTE_SWAP_WORD(pEthernetHeader->type) == pRxData->pUdata->uGenericEthertype))
       {
           //GTRACE(1, "rxData_DataPacketDisptcher(): Received Eapol packet  \r\n");
           RX_PRINT("\n\rxData_DataPacketDisptcher: : Received EAPOL packet");

           DataPacketType = DATA_EAPOL_PACKET;
       }
       else
       {
           RX_PRINT("\n\rxData_DataPacketDisptcher: : Received DATA_DATA_PACKET");
           DataPacketType = DATA_DATA_PACKET;
       }

       RX_PRINT("\n\rxData_DataPacketDisptcher: eLinkConnState=%d, DataPacketType=%d uHlid=%d",
         eLinkConnState, DataPacketType, uHlid);
       /* dispatch Buffer according to packet type and current rx data port status */
       pRxData->rxData_dispatchBuffer[eLinkConnState][DataPacketType] (pBuffer);//rxData_RcvPacketData
    }
}

/***************************************************************************
*                       rxData_DiscardPacket                               *
****************************************************************************
* DESCRIPTION:  this function is called to discard Buffer
*
* INPUTS:       pRxData - the object
*               pBuffer - the received Buffer.
*
* OUTPUT:
*
* RETURNS:
***************************************************************************/
static void rxData_DiscardPacket(void *pBuffer)
{
    rxData_t *pRxData = gRxDataCB;
    //RxIfDescriptor_t *pRxParams = (RxIfDescriptor_t *)pBuffer;

    //Report(REPORT_SEVERITY_INFORMATION, " rxData_DiscardPacket: rx conn state = %d , Buffer status = %d  \r\n", pRxData->aRxLinkInfo[pRxParams->hlid].eState, pRxParams->status);

    pRxData->rxDataDbgCounters.excludedFrameCounter++;

    /* free Buffer */
    RxBufFree(pBuffer);

}


/***************************************************************************
*                       rxData_RcvPacketInOpenNotify                         *
****************************************************************************
* DESCRIPTION:  this function is called upon receving data Eapol packet type
*               while rx port status is "open notify"
*
* INPUTS:       pRxData - the object
*               pBuffer - the received Buffer.
*
* OUTPUT:
*
* RETURNS:
***************************************************************************/
static void rxData_RcvPacketInOpenNotify(void *pBuffer)
{
    rxData_t *pRxData = gRxDataCB;

    //Report(REPORT_SEVERITY_ERROR, " rxData_RcvPacketInOpenNotify: receiving data packet while in rx port status is open notify\r\n");

    pRxData->rxDataDbgCounters.rcvUnicastFrameInOpenNotify++;

    /* free Buffer */
    RxBufFree(pBuffer);
}


/***************************************************************************
*                       rxData_RcvPacketEapol                               *
****************************************************************************
* DESCRIPTION:  this function is called upon receving data Eapol packet type
*               while rx port status is "open  eapol"
*
* INPUTS:       pRxData - the object
*               pBuffer - the received Buffer.
*
* OUTPUT:
*
* RETURNS:
***************************************************************************/
static void rxData_RcvPacketEapol(void *pBuffer)
{
    rxData_t *pRxData = gRxDataCB;

    //Report(REPORT_SEVERITY_INFORMATION, "rxData_RcvPacketEapol(): Received an EAPOL frame tranferred to OS\r\n");

    //((RxIfDescriptor_t*)pBuffer)->packet_class_tag = TAG_CLASS_EAPOL;

    /* Forward EAPOL packets to the UWD via the Rx eapol packets callback */
    if (pRxData->pUdata->fEapolRxCb)
    {
        pRxData->pUdata->fEapolRxCb(pBuffer);//CME_RxEapol
    }
    else 
    {
        //Report(REPORT_SEVERITY_ERROR, "rxData_RcvPacketEapol(): fMgmtRxCb callback is NULL!!\r\n");
        RxBufFree(pBuffer);
    }
}

uint8_t isEthernet2frame(Wlan_LlcHeader_T* pWlanSnapHeader)
{
    uint8_t createEtherIIHeader = FALSE;
    uint16_t            swapedTypeLength;

    swapedTypeLength = WLANTOHS (pWlanSnapHeader->Type);


   /* See if the LLC header in the frame shows the SAP SNAP... */
   if((SNAP_CHANNEL_ID == pWlanSnapHeader->DSAP) &&
      (SNAP_CHANNEL_ID == pWlanSnapHeader->SSAP) &&
      (LLC_CONTROL_UNNUMBERED_INFORMATION == pWlanSnapHeader->Control))
   {
       /* Check for the Bridge Tunnel OUI in the SNAP Header... */
       if((SNAP_OUI_802_1H_BYTE0 == pWlanSnapHeader->OUI[ 0 ]) &&
          (SNAP_OUI_802_1H_BYTE1 == pWlanSnapHeader->OUI[ 1 ]) &&
          (SNAP_OUI_802_1H_BYTE2 == pWlanSnapHeader->OUI[ 2 ]))
       {
           /* Strip the SNAP header by skipping over it.                  */
           /* Start moving data from the Ethertype field in the SNAP      */
           /* header.  Move to the TypeLength field in the 802.3 header.  */
           createEtherIIHeader = TRUE;
       }
       /* Check for the RFC 1042 OUI in the SNAP Header   */
       else
       {
           /* Check for the RFC 1042 OUI in the SNAP Header   */
           if( (SNAP_OUI_RFC1042_BYTE0 == pWlanSnapHeader->OUI[ 0 ]) &&
               (SNAP_OUI_RFC1042_BYTE1 == pWlanSnapHeader->OUI[ 1 ]) &&
               (SNAP_OUI_RFC1042_BYTE2 == pWlanSnapHeader->OUI[ 2 ]))
           {
               /* See if the Ethertype is in our selective translation table  */
               /* (Appletalk AARP and DIX II IPX are the two protocols in     */
               /* our 'table')                                                */
                   if((ETHERTYPE_APPLE_AARP != swapedTypeLength) &&
                       (ETHERTYPE_DIX_II_IPX != swapedTypeLength))
               {
                   /* Strip the SNAP header by skipping over it. */
                   createEtherIIHeader = TRUE;
               }
           }
       }
   }
   return createEtherIIHeader;
}
/***************************************************************************
*                       rxData_RcvPacketData                                 *
****************************************************************************
* DESCRIPTION:  this function is called upon receving data "data" packet type
*               while rx port status is "open"
*
* INPUTS:       pRxData - the object
*               pBuffer - the received Buffer.
*
* OUTPUT:
*
* RETURNS:
***************************************************************************/
static void rxData_RcvPacketData(void *pBuffer)
{
    rxData_t         *pRxData = gRxDataCB;
    RxIfDescriptor_t *pRxParams = (RxIfDescriptor_t*)pBuffer;
    TUdataLinkInfo   *pLinkInfo = &(pRxData->pUdata->aLinkInfo[pRxParams->hlid]);
    TEthernetHeader  *pEthernetHeader = (TEthernetHeader *)RX_ETH_PKT_DATA(pBuffer);

    /* Unicast frame */
    if (!MAC_MULTICAST(pEthernetHeader->dst))
    {
        /* Drop unencripted unicast packets if required */
        if ((pRxData->aRxLinkInfo[pRxParams->hlid].bRxDataExcludeUnencryptedUnicast) && 
            (!(pRxParams->flags & RX_DESC_ENCRYPT_MASK)))
        {
            pRxData->rxDataDbgCounters.excludedFrameCounter++;
            /* free Buffer */
            //Report(REPORT_SEVERITY_WARNING, " rxData_rcvPacketData() : exclude unicast unencrypted is TRUE & packet encryption is OFF\r\n");

            RxBufFree(pBuffer);
            return;
        }

        pRxData->rxDataCounters.RecvOk++;
        pRxData->rxDataCounters.DirectedFramesRecv++;
        pRxData->rxDataCounters.DirectedBytesRecv += RX_ETH_PKT_LEN(pBuffer);

        /* AP-role BSS unicast Bridge handling */
        if (IS_ROLE_TYPE_AP_OR_P2PGO(pLinkInfo->eRoleType) && pRxData->pUdata->aIntraBssBridgeEnable[pLinkInfo->eFwRoleId])
        {
            uint8_t uMacLink;

            /* If dest MAC is ours, unicast bridge is required so send to Tx and drop Rx packet */
            if (txDataQ_LinkMacFind(&uMacLink, pEthernetHeader->dst) == OK)
            {
                sendDataPacketToTx(RX_ETH_PKT_DATA(pBuffer), (uint16_t)RX_ETH_PKT_LEN(pBuffer), uMacLink);

                RxBufFree(pBuffer);
                return;
            }
        }
        RX_PRINT("\n\r rxData_rcvPacketData(): pRxParams->flags = 0x%x bRxDataExcludeUnencryptedUnicast = %d eRoleType = %d\r\n",
            pRxParams->flags, pRxData->aRxLinkInfo[pRxParams->hlid].bRxDataExcludeUnencryptedUnicast, pLinkInfo->eRoleType);

        //the link is unencrypted (like global) but data frame has arrived protected - rx from unknown 
        //case example: during AP role, when station has initiated a disconnection 
        //              and continues to send a protected data - this is no more a known host
        if (IS_ROLE_TYPE_AP_OR_P2PGO(pLinkInfo->eRoleType) && 
            (pRxParams->flags & RX_DESC_ENCRYPT_MASK) && 
            (pRxData->aRxLinkInfo[pRxParams->hlid].bRxDataExcludeUnencryptedUnicast == 0) )
        {
            //protected unicast  to ap role
            if (pRxData->pUdata->fRxFromUnknownCb)
            {
                uint16_t etherType = 0;
                rxData_ConvertWlanToEthHeader(pBuffer, &etherType);

                pRxData->pUdata->fRxFromUnknownCb(pBuffer);  /* CB handles buffer free */
                return;
            }
        }
    }
    /* Broadcast/Multicast frame */
    else
    {
        // The below fields define how none encrypted received packets are handled.
        // Default behavior is if enctyption is on, drop broadcast.
        if ((pRxData->aRxLinkInfo[pRxParams->hlid].bRxDataExcludeUnencryptedBroadcast) && 
            (!(pRxParams->flags & RX_DESC_ENCRYPT_MASK)))
        {
            pRxData->rxDataDbgCounters.excludedFrameCounter++;
            /* free Buffer */
            Report("\n\r !!!rxData_rcvPacketData(): exclude broadcast unencrypted is TRUE & packet encryption is OFF\r\n");

            RxBufFree(pBuffer);
            return;
        }

        pRxData->rxDataCounters.RecvOk++;

        /* AP-role BSS broadcat Bridge handling */
        if (IS_ROLE_TYPE_AP_OR_P2PGO(pLinkInfo->eRoleType) && pRxData->pUdata->aIntraBssBridgeEnable[pLinkInfo->eFwRoleId])
        {
            /* send to TX (also sent to Rx - see below) */
            sendDataPacketToTx(RX_ETH_PKT_DATA(pBuffer), (uint16_t)RX_ETH_PKT_LEN(pBuffer),
                               pRxData->pUdata->aBcastHlid[pLinkInfo->uNetIfId]);
        }

        if (MAC_BROADCAST (pEthernetHeader->dst))
        {
            /* Broadcast frame */
            pRxData->rxDataCounters.BroadcastFramesRecv++;
            pRxData->rxDataCounters.BroadcastBytesRecv += RX_ETH_PKT_LEN(pBuffer);
        }
        else
        {
            /* Multicast Address */
            pRxData->rxDataCounters.MulticastFramesRecv++;
            pRxData->rxDataCounters.MulticastBytesRecv += RX_ETH_PKT_LEN(pBuffer);
        }
    }

// To do
    /* deliver packet to os 
    wlanDrvIf_ReceivePacket (pRxData->hDrv,
                            pLinkInfo->uNetIfId,
                             (struct RxIfDescriptor_t*)pBuffer,
                             RX_ETH_PKT_DATA(pBuffer),
                            (uint16_t)RX_ETH_PKT_LEN(pBuffer)); */


    _recvNetworkPacket(pLinkInfo->uNetIfId, RX_ETH_PKT_DATA(pBuffer), (uint32_t)RX_ETH_PKT_LEN(pBuffer));
    RxBufFree(pBuffer);

}


/****************************************************************************
*                       rxData_ConvertWlanToEthHeader                       *
*****************************************************************************
* DESCRIPTION:  this function convert the Packet header from 802.11 header
*               format to ethernet format
*
* INPUTS:       pRxData - the object
*               pBuffer - the received pBuffer in 802.11 format
*
* OUTPUT:       pEthPacket  - pointer to the received pBuffer in ethernet format
*               uEthLength - ethernet packet length
*
* RETURNS:      OK/NOK
***************************************************************************/

static uint32_t rxData_ConvertWlanToEthHeader(void *pBuffer, uint16_t *etherType)
{
    TEthernetHeader    EthHeader;
    Wlan_LlcHeader_T  *pWlanSnapHeader;
    dot11_header_t    *pDot11Header;
    int32_t           lengthDelta = 0,rsnHeader = 0;
    uint16_t           swapedTypeLength;
    uint32_t           headerLength;
    uint8_t            createEtherIIHeader;
    uint8_t           *dataBuf = (uint8_t *)RX_BUF_DATA(pBuffer);

    /* Setting the mac header len according to the received FrameControl field in the Mac Header */
    GET_MAX_HEADER_SIZE (dataBuf, &headerLength);
    pDot11Header = (dot11_header_t*) dataBuf;
    if(BYTE_SWAP_WORD(pDot11Header->fc) & FCTL_PROTECTED)//if secure packet remove RAN header
    {
        //remove RSN header
        rsnHeader = WLAN_RSN_HEADER;
    }
    pWlanSnapHeader = (Wlan_LlcHeader_T*)((uint8_t*)dataBuf + headerLength+ rsnHeader);

    swapedTypeLength = WLANTOHS (pWlanSnapHeader->Type);
    *etherType = swapedTypeLength;

    /* Prepare the Ethernet header. */
    if( (pDot11Header->fc) & DOT11_FC_FROM_DS)//if( ENDIAN_HANDLE_WORD(pDot11Header->fc) & DOT11_FC_FROM_DS)
    {   /* Infrastructure  bss */
        MAC_COPY (EthHeader.dst, pDot11Header->address1);
        MAC_COPY (EthHeader.src, pDot11Header->address3);
    }
    else
    {   /* Independent bss */
        if( (pDot11Header->fc) & DOT11_FC_TO_DS)//if( ENDIAN_HANDLE_WORD(pDot11Header->fc) & DOT11_FC_TO_DS)
        {
            /* STA to AP in Infrastructure  bss */
            MAC_COPY (EthHeader.dst, pDot11Header->address3);
            MAC_COPY (EthHeader.src, pDot11Header->address2);
        }
        else
        {
            /* Independent bss */
            MAC_COPY (EthHeader.dst, pDot11Header->address1);
            MAC_COPY (EthHeader.src, pDot11Header->address2);
        }
    }

    createEtherIIHeader = isEthernet2frame(pWlanSnapHeader);

    if( createEtherIIHeader == TRUE )
    {
        /* The LEN/TYPE bytes are set to TYPE, the entire WLAN+SNAP is removed.*/
        lengthDelta = headerLength + rsnHeader + WLAN_SNAP_HDR_LEN - ETHERNET_HDR_LEN;
        EthHeader.type = pWlanSnapHeader->Type;
    }
    else
    {
        /* The LEN/TYPE bytes are set to frame LEN, only the WLAN header is removed, */
        /* the entire 802.3 or 802.2 header is not removed.*/
        lengthDelta = headerLength + rsnHeader - ETHERNET_HDR_LEN;
        EthHeader.type = WLANTOHS((uint16_t)(RX_BUF_LEN(pBuffer) - (headerLength+rsnHeader)));
    }

    /* Replace the 802.11 header and the LLC with Ethernet packet. */
    dataBuf += lengthDelta;
    os_memcpy(dataBuf, (void*)&EthHeader, ETHERNET_HDR_LEN);
    RX_ETH_PKT_DATA(pBuffer) = dataBuf;
    RX_ETH_PKT_LEN(pBuffer)  = RX_BUF_LEN(pBuffer) - lengthDelta;

    return OK;
}


/**
 * \brief convert A-MSDU to several ethernet packets
 *
 * \param pRxData - the object
 * \param pBuffer - the received Buffer in A-MSDU 802.11n format
 * \param pRxAttr - Rx attributes
 * \return OK on success or NOK on failure
 *
 * \par Description
 * Static function
 * This function convert the A-MSDU Packet from A-MSDU 802.11n packet
 * format to several ethernet packets format and pass them to the OS layer
 *
 * \sa
 */
static uint32_t rxData_ConvertAmsduToEthPackets(void *pBuffer,ELinkState eLinkConnState)
{
    rxData_t           *pRxData = gRxDataCB;
    TEthernetHeader    *pMsduEthHeader;
    TEthernetHeader    *pEthHeader;
    Wlan_LlcHeader_T   *pWlanSnapHeader;
    uint8_t            *pAmsduDataBuf;
    uint16_t            uAmsduDataLen;
    uint8_t            *pDataBuf;
    uint8_t            *pListMsdu = NULL;
    uint8_t            *pPrevMsdu;
    padding_next_pkt_size_t   NextMsdu;
    uint16_t            uDataLen;
    uint32_t            lengthDelta,rsnHeader = 0;
    uint16_t            swapedTypeLength;
    uint32_t            headerLength;
    dot11_header_t     *pDot11Header;
    rxDataPacketType_e  DataPacketType;
    const unsigned char rfc1042_hdr[ETH_ALEN] =	{ 0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00 };
    uint8_t            createEtherIIHeader;
    uint32_t           packet_len;

    /* total AMPDU header */
    pAmsduDataBuf = (uint8_t *)RX_BUF_DATA(pBuffer);

    /* Setting the mac header len according to the received FrameControl field in the Mac Header */
    GET_MAX_HEADER_SIZE (pAmsduDataBuf, &headerLength);
    pDot11Header = (dot11_header_t*) pAmsduDataBuf;

    if(IS_WEP_ON(pDot11Header->fc))//if secure packet remove RAN header
    {
        //remove  RSN header
        rsnHeader = WLAN_RSN_HEADER;
    }

    /*
     * init loop setting
     */
    /* total AMPDU size */
    uAmsduDataLen = (uint16_t)(RX_BUF_LEN(pBuffer) - headerLength - rsnHeader);
    /* ETH header */
    pMsduEthHeader = (TEthernetHeader *)((uint8_t*)pAmsduDataBuf + headerLength + rsnHeader);
    /* ETH length, in A-MSDU the MSDU header type contain the MSDU length and not the type */
    uDataLen = WLANTOHS(pMsduEthHeader->type);//include snap header
    //Report(REPORT_SEVERITY_INFORMATION, "rxData_ConvertAmsduToEthPackets(): A-MSDU received in length %d \r\n",uAmsduDataLen);
    /* if we have another packet at the AMSDU */
    while((uDataLen < uAmsduDataLen) && (uAmsduDataLen > ETHERNET_HDR_LEN))//FCS is not received from MAC
    {
        if ((uDataLen < WLAN_SNAP_HDR_LEN) || (uDataLen > MSDU_DATA_LEN_LIMIT))
        {
            //Report(REPORT_SEVERITY_ERROR, "rxData_ConvertAmsduToEthPackets(): MSDU Length out of bounds = %d\r\n",uDataLen);
            RX_PRINT_ERROR("\n\rERROR rxData_ConvertAmsduToEthPackets(): MSDU Length out of bounds = %d",uDataLen);
            rxData_DiscardPacket(pBuffer);
            return NOK;
        }

        /* read packet type from LLC */
        pWlanSnapHeader = (Wlan_LlcHeader_T*)((uint8_t*)pMsduEthHeader+ETHERNET_HDR_LEN);
        swapedTypeLength = WLANTOHS (pWlanSnapHeader->Type);

        createEtherIIHeader = isEthernet2frame(pWlanSnapHeader);

        if(createEtherIIHeader)
        {
            /* The LEN/TYPE bytes are set to TYPE, the entire WLAN+SNAP is removed.*/

            /* allocate a new buffer */
            /* RxBufAlloc() add an extra word for alignment the MAC payload */
            rxData_RequestForBuffer(&pDataBuf, sizeof(RxIfDescriptor_t) + PADDING_INTERNAL_USE_SIZE + ETHERNET_HDR_LEN + uDataLen - WLAN_SNAP_HDR_LEN + 4);
            if (NULL == pDataBuf)
            {
                RX_PRINT_ERROR("\n\rrxData_ConvertAmsduToEthPackets(): cannot alloc MSDU packet. length %d \r\n",uDataLen);
                goto fail;
            }

            /* copy the RxIfDescriptor */
            os_memcpy(pDataBuf, pBuffer, sizeof(RxIfDescriptor_t));

            /* update length, in the RxIfDescriptor the Len in words (4B) */
            ((RxIfDescriptor_t *)pDataBuf)->length = ((sizeof(RxIfDescriptor_t) + PADDING_INTERNAL_USE_SIZE + ETHERNET_HDR_LEN + uDataLen - WLAN_SNAP_HDR_LEN + ALIGN_4BYTE_MASK)& ~ALIGN_4BYTE_MASK);
            ((RxIfDescriptor_t *)pDataBuf)->extraBytes = (4-((sizeof(RxIfDescriptor_t) + PADDING_INTERNAL_USE_SIZE + ETHERNET_HDR_LEN + uDataLen - WLAN_SNAP_HDR_LEN) & ALIGN_4BYTE_MASK));
            /* Prepare the Ethernet header pointer. */
            /* add padding in the start of the buffer in order to align ETH payload */
            pEthHeader = (TEthernetHeader *)((uint8_t *)((uint8_t*)RX_BUF_DATA(pDataBuf)) +
                                             PADDING_INTERNAL_USE_SIZE);

            /* copy the Ethernet header */
            os_memcpy(pEthHeader, pMsduEthHeader, ETHERNET_HDR_LEN);

            /* The LEN/TYPE bytes are set to TYPE */
            pEthHeader->type = pWlanSnapHeader->Type;

            /* copy the packet payload */
            os_memcpy((((uint8_t*)pEthHeader) + ETHERNET_HDR_LEN),
                      ((uint8_t*)pMsduEthHeader) + ETHERNET_HDR_LEN + WLAN_SNAP_HDR_LEN,
                      uDataLen - WLAN_SNAP_HDR_LEN);

            packet_len = (uDataLen + ETHERNET_HDR_LEN - WLAN_SNAP_HDR_LEN);

        }
        else// not ethrnet 2
        {
            /* The LEN/TYPE bytes are set to frame LEN, only the WLAN header is removed, */
            /* the entire 802.3 or 802.2 header is not removed.*/

            /* allocate a new buffer */
            /* RxBufAlloc() add an extra word for alignment the MAC payload */
            rxData_RequestForBuffer(&pDataBuf, sizeof(RxIfDescriptor_t) + PADDING_INTERNAL_USE_SIZE+ ETHERNET_HDR_LEN + uDataLen + 4);
            if (NULL == pDataBuf)
            {
                RX_PRINT_ERROR("\n\rrxData_ConvertAmsduToEthPackets(): cannot alloc MSDU packet. length %d \r\n",uDataLen);
                goto fail;
            }

            /* copy the RxIfDescriptor */
            os_memcpy(pDataBuf, pBuffer, sizeof(RxIfDescriptor_t));

            /* update length, in the RxIfDescriptor the Len in words (4B) */
            ((RxIfDescriptor_t *)pDataBuf)->length = ((sizeof(RxIfDescriptor_t) + PADDING_INTERNAL_USE_SIZE + ETHERNET_HDR_LEN + uDataLen + ALIGN_4BYTE_MASK) & ~ALIGN_4BYTE_MASK );
            ((RxIfDescriptor_t *)pDataBuf)->extraBytes = 4-((sizeof(RxIfDescriptor_t) + PADDING_INTERNAL_USE_SIZE + ETHERNET_HDR_LEN + uDataLen) & ALIGN_4BYTE_MASK);

            /* Prepare the Ethernet header pointer. */
            /* add padding in the start of the buffer in order to align ETH payload */
            pEthHeader = (TEthernetHeader *)(((uint8_t*)RX_BUF_DATA(pDataBuf)) +
                                             PADDING_INTERNAL_USE_SIZE);

            /* copy the Ethernet header */
            os_memcpy(pEthHeader, pMsduEthHeader, ETHERNET_HDR_LEN);

            /* The LEN/TYPE bytes are set to frame LEN, only the WLAN header is removed, */
            /* the entire 802.3 or 802.2 header is not removed.*/
            pEthHeader->type = WLANTOHS(uDataLen);

            /* copy the packet payload */
            os_memcpy((((uint8_t*)pEthHeader) + ETHERNET_HDR_LEN),
                      ((uint8_t*)pMsduEthHeader) + ETHERNET_HDR_LEN,
                      uDataLen);

            packet_len = (uDataLen + ETHERNET_HDR_LEN);

        }

        /* mitigate A-MSDU aggregation injection attacks */
        if (IRQ_UtilCompareMacAddress(pEthHeader->dst, rfc1042_hdr))
        {
            goto fail;    
        }

        /* set the packet type */
        if (BYTE_SWAP_WORD(pEthHeader->type) == ETHERTYPE_EAPOL)
        {
            //Report(REPORT_SEVERITY_INFORMATION, " rxData_ConvertAmsduToEthPackets() : Received Eapol pBuffer  \r\n");
            RX_PRINT("\n\rrxData_ConvertAmsduToEthPackets() : Received Eapol pBuffer");

            DataPacketType = DATA_EAPOL_PACKET;
        }
        else
        {
            //Report(REPORT_SEVERITY_INFORMATION, " rxData_ConvertAmsduToEthPackets() : Received Data pBuffer  \r\n");
            RX_PRINT("\n\rrxData_ConvertAmsduToEthPackets() : Received Data pBuffer  \r\n");

            DataPacketType = DATA_DATA_PACKET;
        }

        /* update buffer setting */
        /* save the ETH packet address */
        RX_ETH_PKT_DATA(pDataBuf) = (uint8_t*)pEthHeader;
        /* save the ETH packet size */
        RX_ETH_PKT_LEN(pDataBuf) = packet_len;


        /* Delta length for the next packet */
        lengthDelta = ETHERNET_HDR_LEN + uDataLen;
        /* star of MSDU packet always align acceding to 11n spec */
        lengthDelta = (lengthDelta + ALIGN_4BYTE_MASK) & ~ALIGN_4BYTE_MASK;
        pMsduEthHeader = (TEthernetHeader *)(((uint8_t*)pMsduEthHeader) + lengthDelta);
        
        if (pListMsdu == NULL)
        {
            pListMsdu = pDataBuf;
        }
        else
        {
            RX_PKT_NEXT_MSDU(pPrevMsdu) = (uint8_t*)pDataBuf;
        }

        if(uAmsduDataLen > lengthDelta)
        {
            /* swich to the next MSDU */
            uAmsduDataLen = uAmsduDataLen - lengthDelta;

            /* Clear the EndOfBurst flag for all packets except the last one */
           // ((RxIfDescriptor_t *)pDataBuf)->driverFlags &= ~DRV_RX_FLAG_END_OF_BURST;

            /* in A-MSDU the MSDU header type contain the MSDU length and not the type */
            uDataLen = WLANTOHS(pMsduEthHeader->type);
        }
        else
        {
            /* no more MSDU */
            uAmsduDataLen = 0;
            os_memset((uint32_t*)((uint8_t*)pDataBuf + sizeof(RxIfDescriptor_t) + PADDING_ETH_PACKET_SIZE), 0, sizeof(uint32_t));
        }

        os_memset((uint8_t*)((uint8_t*)pDataBuf + sizeof(RxIfDescriptor_t) + PADDING_ETH_PACKET_SIZE + 4/*32 bits pointer of next msdu address*/), DataPacketType, sizeof(uint8_t));
        pPrevMsdu = pDataBuf;
    } /* while end */

    //Report(REPORT_SEVERITY_INFORMATION, "rxData_ConvertAmsduToEthPackets(): A-MSDU Packe conversion done.\r\n");
    while(pListMsdu != NULL)
    {
        memcpy(&NextMsdu, (uint8_t*)(pListMsdu + sizeof(RxIfDescriptor_t) + PADDING_ETH_PACKET_SIZE), sizeof(padding_next_pkt_size_t));
        pRxData->rxData_dispatchBuffer[eLinkConnState][NextMsdu.DataPktType](pListMsdu);//for data packet rxData_RcvPacketData
        if (NextMsdu.NextMsduAddr == 0)
        {
            pListMsdu = NULL;
            break;
        }
        else
        {
            pListMsdu = (uint8_t*)NextMsdu.NextMsduAddr;
        }
    }
    /* free the A-MSDU packet */
    RxBufFree(pBuffer);

    return OK;
    
    fail:
        while(pListMsdu != NULL)
        {
            memcpy(&NextMsdu, (uint8_t*)(pListMsdu + sizeof(RxIfDescriptor_t) + PADDING_ETH_PACKET_SIZE), sizeof(NextMsdu.NextMsduAddr));
            rxData_DiscardPacket(pListMsdu);
            pListMsdu = (uint8_t*)NextMsdu.NextMsduAddr;
        }

        RxBufFree(pBuffer);
        return NOK;

}

/****************************************************************************************
 *                        rxData_ReceivePacket                                              *
 ****************************************************************************************
DESCRIPTION:    receive packet CB from RxXfer.
                parse the status and other parameters and forward the frame to
                rxData_ReceivePacket()

INPUT:          Rx frame with its parameters

OUTPUT:

RETURN:

************************************************************************/
void rxData_ReceivePacket (void  *pBuffer)
{
    rxData_t            *pRxData    = gRxDataCB;
    RxIfDescriptor_t    *pRxParams  = (RxIfDescriptor_t*)pBuffer;
    dot11_header_t      *pHdr;
    RoleType_e       eRoleType = pRxData->pUdata->aLinkInfo[pRxParams->hlid].eRoleType;

        /*
         * First thing we do is getting the dot11_header, and than we check the status, since the header is
         * needed for RX_MIC_FAILURE_ERROR
         */
        pHdr = (dot11_header_t *)RX_BUF_DATA(pBuffer);

        /* Check status */
        switch (pRxParams->status & RX_DESC_STATUS_MASK)
        {
            case RX_DESC_STATUS_SUCCESS:
                break;

            case RX_DESC_STATUS_DECRYPT_FAIL:
            {
                /* This error is not important before the Connection, so we ignore it when portStatus is not OPEN */
                if (pRxData->aRxLinkInfo[pRxParams->hlid].eState == LINK_STATE_OPEN)
                {
                    RX_PRINT_ERROR("\n\rrxData_ReceivePacket: Received Packet with RX_DESC_DECRYPT_FAIL\r\n");
                }

                RxBufFree(pBuffer);
                return;
            }
            break;
            case RX_DESC_STATUS_MIC_FAIL:
            {
                if (IS_ROLE_TYPE_AP_OR_P2PGO(eRoleType))
                {
                    if (pRxData->pUdata->fMicFailureCb)
                    {
                        pRxData->pUdata->fMicFailureCb(pRxData->pUdata->hMicFailureHandle, pRxParams->hlid, KEY_TKIP_MIC_PAIRWISE);
                    }
                    RX_PRINT_ERROR("\n\rrxData_ReceivePacket: ROLE_TYPE_AP_OR_P2PGO, Received Packet with RX_DESC_STATUS_MIC_FAIL\r\n");
                    RxBufFree(pBuffer);
                    return;
                }
                else if (IS_ROLE_TYPE_STA_OR_P2PCL(eRoleType))
                {
                    uint8_t uKeyType;
                    TMacAddr* pMac = &pHdr->address1; /* hold the first mac address */

                    /* BSS type is infrastructure*/
                    /* For multicast/broadcast frames or in IBSS the key used is GROUP, else - it's Pairwise */
                    if (MAC_MULTICAST(*pMac))
                    {
                        uKeyType = (uint8_t)KEY_TKIP_MIC_GROUP;
                        //Report(REPORT_SEVERITY_ERROR, "rxData_ReceivePacket: Received Packet MIC failure. Type = Group\r\n");
                    }
                    /* Unicast on infrastructure */
                    else
                    {
                        uKeyType = (uint8_t)KEY_TKIP_MIC_PAIRWISE;
                        //Report(REPORT_SEVERITY_ERROR, "rxData_ReceivePacket: Received Packet MIC failure. Type = Pairwise\r\n");
                    }

                    if (pRxData->pUdata->fMicFailureCb)
                    {
                        pRxData->pUdata->fMicFailureCb(pRxData->pUdata->hMicFailureHandle, pRxParams->hlid, uKeyType);
                    }
                    RX_PRINT_ERROR("\n\rrxData_ReceivePacket: Received Packet with RX_DESC_STATUS_MIC_FAIL\r\n");

                    RxBufFree(pBuffer);
                    return;
                }
                break;
            }

            case RX_DESC_STATUS_DRIVER_RX_Q_FAIL:
            {
                /* Rx queue error - free packet and return */
                RX_PRINT( "\n\rrxData_ReceivePacket: Received Packet with Rx queue error \r\n");//it is with RX_PRINT since it happens a lot
                GTRACE(GRP_DRIVER_CC33, "rxData_ReceivePacket: Received Packet with Rx queue error");
                RxBufFree(pBuffer);
                return;
            }
            break;
            default:
            {
                /* Unknown error - free packet and return */
                RX_PRINT_ERROR("\n\rrxData_ReceivePacket: Received Packet with unknown status = %d\r\n", (pRxParams->status & RX_DESC_STATUS_MASK));

                RxBufFree(pBuffer);
                return;
            }
            break;
        }

    //Report("\n\rrxData_ReceivePacket: channel=%d, flags=0x%x,  rate=0x%x, RSSI=%d, SNR=%d, status=%d, scan tag=%d\r\n", pRxParams->channel, pRxParams->flags, pRxParams->rate, pRxParams->rx_level, pRxParams->rx_snr, pRxParams->status, (pRxParams->status >> RX_DESC_STATUS_PROC_ID_TAG_SHFT) & RX_DESC_STATUS_PROC_ID_TAG_MASK);

    rxData_ReceivePacketFromWlan(pBuffer);
}
#if 0
// Dan - Check remove
/* CallBack for recieving FwLogger packet from rxXfer or dump packets */
static void rxData_ReceiveFwLoggerPacket (void  *pBuffer, uint32_t uLength, uint8_t fwLogMode, Bool_e RecoveryReading)
{
    rxData_t          *pRxData = gRxDataCB;
    uint8_t           *pBuf;
    uint32_t          i;       
    uint8_t           *pMsgData; 
    uint32_t          uMsgLen;
    uint8_t           aMsg[FW_TRACE_MSG_MAX_LENGTH + 1];
    uint32_t          numOfBytesInMemBlk = MEM_BLOCK_SIZE;

    if(fwLogMode == FWLOG_INT_FW_DUMP) 
    {
        /* the RecoveryReading == FALSE flag indicates that the fw dump read is over */
        if(RecoveryReading == FALSE) 
        {
            evHandler_HandleEvent(pRxData->hEvHandler, ROLE_ID_NONE, TIW_DRV_EV_FW_DUMP_COMPLETE, 0, 0);
            return;
        }
    
        //Report(REPORT_SEVERITY_INFORMATION , " rxData_ReceiveFwLoggerPacket: build FW Dump packet \r\n");

        /* Send the dump packet to the logger proxy */
        evHandler_HandleEvent(pRxData->hEvHandler, ROLE_ID_NONE, TIW_DRV_EV_FW_DUMP, pBuffer, uLength);
    }
    else /* FW logger trace */
    {
        aMsg[0] = FW_TRACE_TAG; /* 2 indicates that this is a FW Trace,  not Driver Trace */

        if(fwLogMode == FWLOG_INT_CONTINUOUS)
        {
            numOfBytesInMemBlk = MEM_BLOCK_SIZE - sizeof(RxIfDescriptor_t); /* in continuous mode 16 bytes for the Descriptor */                                                                
            pBuf = (uint8_t*)pBuffer + sizeof(RxIfDescriptor_t);

            if(RecoveryReading)
            {
                numOfBytesInMemBlk -= 4;
                pBuf += 4;
            }
    }
    else /* On_Demand mode */
    {
        numOfBytesInMemBlk = MEM_BLOCK_SIZE - 4;/* in On_Demand Mode the 4 bytes for the address of the next MemBlk*/
        pBuf = (uint8_t*)pBuffer + 4;
    }

    for (i=0; i < numOfBytesInMemBlk; i += uMsgLen+1)
    {
        /* Initialization of the Msg struct */
        os_memset(&aMsg[1], 0, FW_TRACE_MSG_MAX_LENGTH);
        pMsgData    = &aMsg[1];
        if(pBuf[i] == 0)
        {
            break;
        }

        uMsgLen = pBuf[i];

        if(uMsgLen > FW_TRACE_MSG_MAX_LENGTH)
        {
            //Report(REPORT_SEVERITY_ERROR , " uMsgLen too large %d \r\n", uMsgLen);
            break;
        }
        os_memcpy(pMsgData, &pBuf[i+1], uMsgLen);
        /* Send the trace message to the logger */
        report_FwTrace//Report(aMsg, (uMsgLen + 1));              
    }

    if((fwLogMode == FWLOG_CONTINUES) && (!RecoveryReading)) 
    {
            wlanDrvIf_RxBufFree(pRxData->hOs, pBuffer); 
    }
    }

}
#endif
/****************************************************************************************
 *                        rxData_RequestForBuffer                                              *
 ****************************************************************************************
DESCRIPTION:     RX request for buffer
                uEncryptionflag API are for GWSI use.
INPUT:

OUTPUT:

RETURN:

************************************************************************/
static int rxData_RequestForBuffer (uint8_t **pBuf, uint32_t aLength)
{
    //Report(REPORT_SEVERITY_INFORMATION , " RequestForBuffer, length = %d \r\n",aLength);

    *pBuf = RxBufAlloc(aLength);

    if (*pBuf)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}


/*******************************************************************
*                        DEBUG FUNCTIONS                           *
*******************************************************************/


/***************************************************************************
*                        rxData_resetCounters                              *
****************************************************************************
* DESCRIPTION:  This function reset the Rx Data module counters
*
* INPUTS:       pRxData - the object
*
* OUTPUT:
*
* RETURNS:      void
***************************************************************************/
void rxData_resetCounters(void)
{
    rxData_t *pRxData = gRxDataCB;

    os_memset(&pRxData->rxDataCounters, 0, sizeof(TGlobalRxStats));
}

/***************************************************************************
*                        rxData_resetDbgCounters                           *
****************************************************************************
* DESCRIPTION:  This function reset the Rx Data module debug counters
*
* INPUTS:       pRxData - the object
*
* OUTPUT:
*
* RETURNS:      void
***************************************************************************/

void rxData_resetDbgCounters(void)
{
    rxData_t *pRxData = gRxDataCB;

    os_memset(&pRxData->rxDataDbgCounters, 0, sizeof(rxDataDbgCounters_t));
    os_memset(&pRxData->rxDataLinkCounters, 0, sizeof(rxDataLinkCounters_t)* WLANLINKS_MAX_LINKS);
}



/***************************************************************************
*                            test functions                                *
***************************************************************************/
void rxData_printRxCounters (void)
{
#ifdef REPORT_LOG
    rxData_t *pRxData = gRxDataCB;
    uint32_t uHlid;

    if (pRxData)
    {
       //GTRACE(1, "RecvOk = %d\r\n", pRxData->rxDataCounters.RecvOk));
       //GTRACE(1, "DirectedBytesRecv = %d\r\n", pRxData->rxDataCounters.DirectedBytesRecv));
       //GTRACE(1, "DirectedFramesRecv = %d\r\n", pRxData->rxDataCounters.DirectedFramesRecv));
       //GTRACE(1, "MulticastBytesRecv = %d\r\n", pRxData->rxDataCounters.MulticastBytesRecv));
       //GTRACE(1, "MulticastFramesRecv = %d\r\n", pRxData->rxDataCounters.MulticastFramesRecv));
       //GTRACE(1, "BroadcastBytesRecv = %d\r\n", pRxData->rxDataCounters.BroadcastBytesRecv));
       //GTRACE(1, "BroadcastFramesRecv = %d\r\n", pRxData->rxDataCounters.BroadcastFramesRecv));

        /* debug counters */
       //GTRACE(1, "excludedFrameCounter = %d\r\n", pRxData->rxDataDbgCounters.excludedFrameCounter));
       //GTRACE(1, "rxDroppedDueToVLANIncludedCnt = %d\r\n", pRxData->rxDataDbgCounters.rxDroppedDueToVLANIncludedCnt));
       //GTRACE(1, "rxWrongBssTypeCounter = %d\r\n", pRxData->rxDataDbgCounters.rxWrongBssTypeCounter));
       //GTRACE(1, "rxWrongBssIdCounter = %d\r\n", pRxData->rxDataDbgCounters.rxWrongBssIdCounter));
       //GTRACE(1, "rcvUnicastFrameInOpenNotify = %d\r\n", pRxData->rxDataDbgCounters.rcvUnicastFrameInOpenNotify));
       //GTRACE(1, "rxTidHlidInvalidCounter = %d\r\n", pRxData->rxDataDbgCounters.rxTidHlidInvalidCounter));

        /* link counters */
       //GTRACE(1, "Links counters ---------\r\n"));
        for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
        {
            rxDataLinkCounters_t *pCnt = &pRxData->rxDataLinkCounters[uHlid];
           //Report(("---------Link=%01d: eState=%d\r\n", uHlid, pRxData->aRxLinkInfo[uHlid].eState));
           //GTRACE(1, "    recvFromWlan         = %d\r\n", pCnt->recvFromWlan));
           //GTRACE(1, "    recvBytesFromWlan    = %d\r\n", pCnt->recvBytesFromWlan));
           //GTRACE(1, "    sendToUwd            = %d\r\n", pCnt->sendToUwd));
           //GTRACE(1, "    sendToDataDispatcher = %d\r\n", pCnt->sendToDataDispatcher));
           //GTRACE(1, "    discardWrongHlid     = %d, discardHlidClose=%d, discardBaEvent=%d, discardUnknownClass=%d, \r\n", pCnt->discardWrongHlid, pCnt->discardHlidClose, pCnt->discardBaEvent, pCnt->discardUnknownClass));
        }
    }
#endif
}


void rxData_printRxBlock(void)
{
#ifdef REPORT_LOG
    rxData_t *pRxData = gRxDataCB;
    TRxLinkInfo *pLinkInfo;
    uint32_t uHlid;

    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        pLinkInfo = &pRxData->aRxLinkInfo[uHlid];
       //GTRACE(1, "Link=%01d: eState=%d, ExcludeUnencryptedUnicast=%d, ExcludeUnencryptedBroadcast=%d, RxBaPolicy=0x%x, uHandoverLink=%d\r\n", 
                        uHlid, 
                        pLinkInfo->eState, 
                        pLinkInfo->bRxDataExcludeUnencryptedUnicast,
                        pLinkInfo->bRxDataExcludeUnencryptedBroadcast,
                        pRxData->uRxBaPolicy[uHlid],
                        pRxData->pUdata->aLinkInfo[uHlid].uHandoverLink));
    }
#endif
}





/***************************************************************************
*                        rxData_ResetLinkCounters                          *
****************************************************************************
* DESCRIPTION:  This function reset the Rx Link counters
*
* INPUTS:       pRxData - the object
*               uHlid   - Link Id to reset
*
* OUTPUT:
*
* RETURNS:      void
***************************************************************************/
void rxData_ResetLinkCounters(uint32_t uHlid)
{
    rxData_t *pRxData = gRxDataCB;

    if (uHlid < WLANLINKS_MAX_LINKS)
        os_memset(&(pRxData->rxDataLinkCounters[uHlid]), 0, sizeof(rxDataLinkCounters_t));

}

/****************************************************************************
* DESCRIPTION:  This function reset the Rx Link counters
*
* INPUTS:       pRxData - the object
*               uHlid   - Link Id to reset
*
* OUTPUT:
*
* RETURNS:      void
***************************************************************************/
void rxData_GetLinkCounters(uint32_t uHlid, dbg_cntr_trnspt_t* buf)
{
    rxData_t *pRxData = gRxDataCB;

    if (uHlid < WLANLINKS_MAX_LINKS)
    {
        buf->link_rx_recvFromWlan  = pRxData->rxDataLinkCounters[uHlid].recvFromWlan;
        buf->link_rx_recvBytesFromWlan  = pRxData->rxDataLinkCounters[uHlid].recvBytesFromWlan;
        buf->link_rx_sendToUwd  = pRxData->rxDataLinkCounters[uHlid].sendToUwd;
        buf->link_rx_sendToDataDispatcher  = pRxData->rxDataLinkCounters[uHlid].sendToDataDispatcher;
        buf->link_rx_discardWrongHlid  = pRxData->rxDataLinkCounters[uHlid].discardWrongHlid;
        buf->link_rx_discardHlidClose  = pRxData->rxDataLinkCounters[uHlid].discardHlidClose;
        buf->link_rx_discardBaEvent  = pRxData->rxDataLinkCounters[uHlid].discardBaEvent;
        buf->link_rx_discardUnknownClass  = pRxData->rxDataLinkCounters[uHlid].discardUnknownClass;
    }
}

/**
 * \fn     rxData_SetLinkState
 * \brief  set link state (enable/not)
 *
 * \note
 * \param  pRxData     - The module's object
 * \param  uHlid        - link id
 * \param  eRxLinkState - The new link state
 * \return void
 */
void rxData_SetLinkState (uint32_t uHlid, ELinkState eRxConnState)
{
    rxData_t *pRxData = gRxDataCB;
    TRxLinkInfo *pLinkInfo;

    pLinkInfo = &pRxData->aRxLinkInfo[uHlid];
    pLinkInfo->eState = eRxConnState;

    //Report(REPORT_SEVERITY_INFORMATION, "rxData_SetLinkState: link %d, LinkState %d\r\n", uHlid, pLinkInfo->eState);
}


/**
 * \fn     sendDataPacketToTx
 * \brief  allocate TxCtrlBlk for a data packet, copy it to a 
 *         raw buffer and insert it to the txDataQ
 *  for BssBridgeEnable
 * \param  pRxData     - The module's object
 * \param pBuffer     - the buffer from the rx (sent to the TX)
 * \param uLength     - the buffer's length
 * \param uNetifId    - the network Interface ID 
 * \param pIntraBssBridgeParam - bridge parameters for the
 *        txDataQ
 * \return OK/NOK
 */

static uint32_t sendDataPacketToTx(void *pBuffer, uint16_t uLength, uint32_t uHlid)
{
    rxData_t   *pRxData = gRxDataCB;
    TTxCtrlBlk *pPktCtrlBlk;
    TEthernetHeader *pEthHead= NULL;
    uint32_t dataLen = uLength-ETHERNET_HDR_LEN,total_len = 0;
    uint8_t* pData;
    uint32_t status = NOK;
    uint32_t uNetIfId = 0;
    uint8_t roleType;

    roleType = (uint8_t)(pRxData->pUdata->aLinkInfo[uHlid].eRoleType);

    if(ROLE_STA == roleType)
    {
         uNetIfId = TIWDRV_NETIF_ID_STA;
    }
    else if(ROLE_AP == roleType)
    {
         uNetIfId = TIWDRV_NETIF_ID_SAP;
    }
    else if(ROLE_DEVICE == roleType)
    {
         uNetIfId = TIWDRV_NETIF_ID_P2PDEV;
    }
    else
    {
        ASSERT_GENERAL(0);
    }

    if ((uHlid == INVALID_LINK) ||(pBuffer == NULL))
    {
        //Report(REPORT_SEVERITY_WARNING, "sendDataPacketToTx: hlid is 0!\r\n");
        return NOK;
    }

    pData = (uint8_t *)pBuffer + ETHERNET_HDR_LEN;
    pEthHead  = os_malloc(sizeof(TEthernetHeader));
    if (!pEthHead)
    {
        TX_DATA_SEND_PRINT("sendDataPacketToTx: Failed to allocate TEthernetHeader for Tx data packet:%s\n\r", __FUNCTION__);
        status = NOK;
        goto fail;
    }

    os_memcpy((uint8_t*)pEthHead, pBuffer, ETHERNET_HDR_LEN);

    total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + ETHERNET_HDR_LEN + dataLen;

    /* Allocate a TxCtrlBlk for the Tx packet and save timestamp, length and packet handle */
    pPktCtrlBlk = udata_AllocTxDataPacket(dataLen,ETHERNET_HDR_LEN,pEthHead);

    if (!pPktCtrlBlk)
    {
        TX_DATA_SEND_PRINT_ERROR("\n\rERROR sendDataPacketToTx: Failed to allocate TxCtrlBlk");
        status = NOK;
        os_free(pEthHead);
        goto fail;
    }
    
    set_nab_tx_header(&pPktCtrlBlk->aPktNabHdr, total_len );

    /* copy payload to new buffers - the Ethernet header is dropped later on and replaced with wlan header*/
    os_memcpy(pPktCtrlBlk->tTxPktParams.pInputPkt, pData, dataLen);

#if 0 // TODO: Need to implement
    if (skb->ip_summed == CHECKSUM_PARTIAL)
    {
            pPktCtrlBlk->tTxDescriptor.csumData = *((TI_UINT8*)(skb_network_header(skb) + IP_PROTOCOL_OFFSET));
    }
    else
#endif
    {
           pPktCtrlBlk->tTxDescriptor.csumData = 0;
     }

    /* Send the packet to the driver for transmission. */
    status = udataNet_InsertDataPacket(pPktCtrlBlk, uNetIfId, D_TAG_CLSFR /* TODO: need to implement */);
    return status; // no need to free pEthHead, it will be free by lower layers

    fail:
        return status;
}
