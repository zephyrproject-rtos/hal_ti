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
/** \file   txDataQueue.c
 *  \brief  The Tx Data Queues module.
 *
 *  \see    txDataQueue.h
 */


#define __FILE_ID__  FILE_ID_35
#include "osi_kernel.h"
#include <trnspt_thread.h>
#include "ethernet.h"
#include "paramOut.h"
#include "timer.h"
#include "w_queue.h"
#include "tw_driver.h"
#include "tx_ctrl_api.h"
#include "tx_data_queue_api.h"
#include "tx_data_queue.h"
#include "tx_hw_queue_api.h"
#include <default_params.h>
#include "cc3xxx_public_types.h"
#include "osi_kernel.h"
#include "trnspt_if.h"
#include "tx.h"
#include "udata.h"

typedef enum
{
    AC_PRIORITY_BK = 0,
    AC_PRIORITY_BE,
    AC_PRIORITY_VI,
    AC_PRIORITY_VO,
    AC_PRIORITY_HIGHEST = AC_PRIORITY_VO
} EAcPriority;


const static EAcTrfcType acPriorityToAcIdTable[MAX_NUM_OF_AC] = {QOS_AC_BK, QOS_AC_BE, QOS_AC_VI, QOS_AC_VO};
const static uint32_t MinGuarantee_PerAc[MAX_NUM_OF_AC] = {TX_DATA_MIN_GUARANTEE_BE_DEF, 
                                                              TX_DATA_MIN_GUARANTEE_BK_DEF,
                                                              TX_DATA_MIN_GUARANTEE_VI_DEF,
                                                              TX_DATA_MIN_GUARANTEE_VO_DEF};



//#define DEBUG_TX_QUEUE_TABLE

#ifdef DEBUG_TX_QUEUE_TABLE
typedef struct 
{
    uint32_t uSchedReqCallsCount;
    uint32_t uHostAcQCount[4];
    uint32_t uFwAcQCount[4];
    uint32_t uExitFrameSentCount;
    uint32_t uFwTotal;
    uint32_t uErrBusy;
    uint32_t uErrFail;
    uint32_t uErrNull;
    uint32_t tsf;
}debugTxQ;

debugTxQ gDebugTxQ[100];
uint8_t  gDebugIndex = 0;
uint32_t gErrorBusy = 0; // not enough resoures
uint32_t gErrorFailed = 0; // failed to transmit
uint32_t gErrorNullBlk = 0;
#endif


/* Internal Functions prototypes */
static void txDataQ_RunScheduler (void* hCbHndl);
static void txDataQ_TxSendPaceTimeout (Bool_e bTwdInitOccured);
static void txDataQ_PrintResources (void);
static void txDataQ_InitResources (void);
static void scheduleQueuesPerPriority( int32_t *pCountTxDataFrames);


TTxDataQ *gTxDataQCB = NULL;

/*
 * \brief  Try to send a packet from specified queue
 *
 * \par Description
 *  If the specified queueu isn't empty, send a packet from it.
 *  If the packet couldn't be sent (no room in FW), requeue it for future try.
 *
 * \param  pTxDataQ - The module's object
 * \param  uHlid    - The Link of the queue to send from
 * \param  uAcId    - The AC of the queue to send from
 *
 * \return TRUE if sent packet successfully, FALSE if not
 *
 * \sa
 */
int32_t sendPacket(uint32_t uHlid, uint32_t uQueId)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;
    TTxCtrlBlk *pPktCtrlBlk = NULL; /* Pointer to the packet to be dequeued and sent */
    uint8_t    uBackpressureMap = 0;
    EStatusXmit eXmitStatus;  /* The return status of the txCtrl_xmitData function */
    TDataLinkQ *pLinkQ = &pTxDataQ->aDataLinkQ[uHlid];

    /* Dequeue a packet in a critical section */
    trnspt_lockTxQueue();
    pPktCtrlBlk = (TTxCtrlBlk *)que_Dequeue(pLinkQ->aQueues[uQueId]);
    /* If the queue is empty return FALSE */
    if (pPktCtrlBlk == NULL)
    {
#ifdef DEBUG_TX_QUEUE_TABLE
        gErrorNullBlk++;
#endif
        trnspt_unlockTxQueue();
        return NO_FRAMES_IN_QUEUE;
    }

    trnspt_unlockTxQueue();

    /* once packet is dequeued - decrement host driver AC counter.
     From here this packet is about to be sent and will not return to queue
     Hence - we completed to count this packet*/
    txDataQ_FreeFwAllocated (pPktCtrlBlk);

    pLinkQ->aQueueCounters[uQueId].uDequeuePacket++;

    TX_DATA_SEND_PRINT("\n\rDequeue: data packet uQueId:%d ", uQueId);    
    //Report("\n\rSendPacket: data packet uQueId:%d ", uQueId);


    /* Send the packet */
    eXmitStatus = txCtrl_XmitData (pPktCtrlBlk, &uBackpressureMap);

    if (eXmitStatus == STATUS_XMIT_SUCCESS)
    {
        /* If packet sent to FW successfully return TRUE */
        return FRAME_SEND_SUCCESFULY;
    }
    /* If status is BUSY (couldn't send packet), requeue it for future try. */
    else if (eXmitStatus == STATUS_XMIT_BUSY)
    {
        uint32_t eQueStatus = NOK;
#ifdef DEBUG_TX_QUEUE_TABLE
        gErrorBusy++;
#endif
        TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rData frame: requeue\r\n");

        if (eQueStatus == OK)
        {
            trnspt_RequestSchedule (pTxDataQ->uContextId, FALSE);
            pLinkQ->aQueueCounters[uQueId].uRequeuePacket++;
            return ERROR_SEND_FRAME_FAILED;
        }
        else
        {
            //Report("\n\r dbg_tx. warning !!! failed to send frame,eXmitStatus == STATUS_XMIT_BUSY !!!!!");//dbg_tx
            TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rERROR! Data frame: dropped\r\n");
            /* If the packet can't be queued drop it */
            /* Note: may happen only if this thread was preempted between the
               dequeue and requeue and new packets were inserted into this quque */
            txHwQueue_free_allocated_mem_blocks(pPktCtrlBlk);

            txCtrl_FreePacket (pPktCtrlBlk, NOK);
            pLinkQ->aQueueCounters[uQueId].uDroppedPacket++;
        }
   

    }
#ifdef DEBUG_TX_QUEUE_TABLE
    else if (eXmitStatus == STATUS_XMIT_ERROR)
    {
        gErrorFailed++;
    }
#endif
    Report("\n\rSendPacket Failed: data packet uQueId:%d ", uQueId);
    /* Packet wasn't sent so return FALSE */
    return ERROR_SEND_FRAME_FAILED;
}

/***************************************************************************
*                      PUBLIC  FUNCTIONS  IMPLEMENTATION                   *
****************************************************************************/

/**
 * \fn     txDataQ_Create
 * \brief  Create the module and its queues
 *
 * Create the Tx Data module and its queues.
 *
 * \note
 * \param  hOs - Handle to the Os Abstraction Layer
 * \return Handle to the allocated Tx Data Queue module (NULL if failed)
 * \sa
 */
TTxDataQ* txDataQ_Create(void)
{
    /* allocate TxDataQueue module */
    gTxDataQCB = (TTxDataQ *)os_zalloc(sizeof(TTxDataQ));

    if (!gTxDataQCB)
    {
       //GTRACE(1, "Error allocating the TxDataQueue Module\r\n"));
        return NULL;
    }

    return gTxDataQCB;
}


/**
 * \fn     txDataQ_Init
 * \brief  Save required modules handles
 *
 * Save other modules handles.
 *
 * \note
 * \param  pStadHandles  - The driver modules handles
 * \return void
 * \sa
 */
void txDataQ_Init(TUdata *pUdata)
{
    TTxDataQ  *pTxDataQ = gTxDataQCB;
    uint32_t  uNodeHeaderOffset = TI_FIELD_OFFSET(TTxnStruct, tTxnQNode);
    uint8_t   uQueId;
    TDataLinkQ *pLinkQ;
    uint32_t  uHlid;

    /* save modules handles */
    pTxDataQ->pUdata    = pUdata;

    pTxDataQ->bDataPortEnable = FALSE;
    pTxDataQ->uNextToServeLink = 0;
    pTxDataQ->uMaxEnabledHlid = 0;
    
    /* init the max size of the Data queues */
    pTxDataQ->aQueueMaxSize[QOS_AC_BE] = DATA_QUEUE_DEPTH_BE;
    pTxDataQ->aQueueMaxSize[QOS_AC_BK] = DATA_QUEUE_DEPTH_BK;
    pTxDataQ->aQueueMaxSize[QOS_AC_VI] = DATA_QUEUE_DEPTH_VI;
    pTxDataQ->aQueueMaxSize[QOS_AC_VO] = DATA_QUEUE_DEPTH_VO;


    /*
     * init all queues in all links
     */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        pLinkQ = &pTxDataQ->aDataLinkQ[uHlid]; /* Link queues */
        CLEAR_BIT_BY_IDX(pTxDataQ->uLinkBusyBitmap, uHlid); /* default is not busy */
        pLinkQ->bEnabled = FALSE; /* default is not enabled */

        /* Create the tx data queues */
        for (uQueId = 0; uQueId < MAX_NUM_OF_AC; uQueId++)
        {
            pLinkQ->aQueues[uQueId] = que_Create (pTxDataQ->aQueueMaxSize[uQueId],
                                                uNodeHeaderOffset);

            /* If any Queues' allocation failed, print error, free TxDataQueue module and exit */
            if (pLinkQ->aQueues[uQueId] == NULL)
            {
                //Report(REPORT_SEVERITY_CONSOLE , "Failed to create queue\r\n");
               //GTRACE(1, "Failed to create queue\r\n"));
                os_free (pTxDataQ);
                return;
            }
        }
    }

    /* Register to the context engine and get the client ID */
    pTxDataQ->uContextId = trnspt_RegisterClient((TTransportCbFunc)txDataQ_RunScheduler, TRUE);
    TRANSPORT_PRINT_INIT("\n\rRegister Client:txDataQ_RunScheduler uContextId :%d",pTxDataQ->uContextId);

#ifdef DEBUG_TX_QUEUE_TABLE
    memset(gDebugTxQ, 0, sizeof(gDebugTxQ));
#endif
}

void txDataQ_SetClsfrInitParams(TClsfrInitParams   *ClsfrInitParam)
{
    ClsfrInitParam->eClsfrType = CLSFR_TYPE_DEF;
    ClsfrInitParam->uNumActiveEntries = NUM_OF_CODE_POINTS_DEF;
    ClsfrInitParam->ClsfrTable[0].Dscp.DTag = DSCP_CLASSIFIER_DTAG_00;
    ClsfrInitParam->ClsfrTable[0].Dscp.CodePoint = DSCP_CLASSIFIER_CODE_POINT_00;
    ClsfrInitParam->ClsfrTable[1].Dscp.DTag = DSCP_CLASSIFIER_DTAG_01;
    ClsfrInitParam->ClsfrTable[1].Dscp.CodePoint = DSCP_CLASSIFIER_CODE_POINT_01;
    ClsfrInitParam->ClsfrTable[2].Dscp.DTag = DSCP_CLASSIFIER_DTAG_02;
    ClsfrInitParam->ClsfrTable[2].Dscp.CodePoint = DSCP_CLASSIFIER_CODE_POINT_02;
    ClsfrInitParam->ClsfrTable[3].Dscp.DTag = DSCP_CLASSIFIER_DTAG_03;
    ClsfrInitParam->ClsfrTable[3].Dscp.CodePoint = DSCP_CLASSIFIER_CODE_POINT_03;
    ClsfrInitParam->ClsfrTable[4].Dscp.DTag = DSCP_CLASSIFIER_DTAG_04;
    ClsfrInitParam->ClsfrTable[4].Dscp.CodePoint = DSCP_CLASSIFIER_CODE_POINT_04;
    ClsfrInitParam->ClsfrTable[5].Dscp.DTag = DSCP_CLASSIFIER_DTAG_05;
    ClsfrInitParam->ClsfrTable[5].Dscp.CodePoint = DSCP_CLASSIFIER_CODE_POINT_05;
    ClsfrInitParam->ClsfrTable[6].Dscp.DTag = DSCP_CLASSIFIER_DTAG_06;
    ClsfrInitParam->ClsfrTable[6].Dscp.CodePoint = DSCP_CLASSIFIER_CODE_POINT_06;
    ClsfrInitParam->ClsfrTable[7].Dscp.DTag = DSCP_CLASSIFIER_DTAG_07;
    ClsfrInitParam->ClsfrTable[7].Dscp.CodePoint = DSCP_CLASSIFIER_CODE_POINT_07;
    ClsfrInitParam->ClsfrTable[0].Port.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[0].Port.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[1].Port.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[1].Port.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[2].Port.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[2].Port.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[3].Port.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[3].Port.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[4].Port.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[4].Port.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[5].Port.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[5].Port.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[6].Port.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[6].Port.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[7].Port.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[7].Port.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[0].IpPort.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[0].IpPort.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[0].IpPort.DstIPAddress = CLASSIFIER_IPADDRESS_DEF;
    ClsfrInitParam->ClsfrTable[1].IpPort.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[1].IpPort.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[1].IpPort.DstIPAddress = CLASSIFIER_IPADDRESS_DEF;
    ClsfrInitParam->ClsfrTable[2].IpPort.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[2].IpPort.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[2].IpPort.DstIPAddress = CLASSIFIER_IPADDRESS_DEF;
    ClsfrInitParam->ClsfrTable[3].IpPort.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[3].IpPort.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[3].IpPort.DstIPAddress = CLASSIFIER_IPADDRESS_DEF;
    ClsfrInitParam->ClsfrTable[4].IpPort.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[4].IpPort.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[4].IpPort.DstIPAddress = CLASSIFIER_IPADDRESS_DEF;
    ClsfrInitParam->ClsfrTable[5].IpPort.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[5].IpPort.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[5].IpPort.DstIPAddress = CLASSIFIER_IPADDRESS_DEF;
    ClsfrInitParam->ClsfrTable[6].IpPort.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[6].IpPort.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[6].IpPort.DstIPAddress = CLASSIFIER_IPADDRESS_DEF;
    ClsfrInitParam->ClsfrTable[7].IpPort.DTag = CLASSIFIER_DTAG_DEF;
    ClsfrInitParam->ClsfrTable[7].IpPort.DstPortNum = CLASSIFIER_PORT_DEF;
    ClsfrInitParam->ClsfrTable[7].IpPort.DstIPAddress = CLASSIFIER_IPADDRESS_DEF;
}
/**
 * \fn     txDataQ_Set
 * \brief  Configure module
 *
 * Init the Tx Data queues.
 * Register as the context-engine client.
 *
 * \note
 * \param  pTxDataQ - The object
 * \param  Other modules handles
 * \return OK on success or NOK on failure
 * \sa
 */
uint32_t txDataQ_Set(TUdataInitParams TUdataParams)
{
    TTxDataQ  *pTxDataQ = gTxDataQCB;
    uint32_t  eStatus;

    /* configure the classifier sub-module */
    TClsfrInitParams    ClsfrInitParam;

    txDataQ_SetClsfrInitParams(&ClsfrInitParam);

    eStatus = txDataClsfr_Config(&ClsfrInitParam);
    if (eStatus != OK)
    {
        //Report(REPORT_SEVERITY_CONSOLE ,"FATAL ERROR: txDataQ_Set(): txDataClsfr_Config failed - Aborting\r\n");
       //GTRACE(1, "FATAL ERROR: txDataQ_Set(): txDataClsfr_Config failed - Aborting\r\n"));
        return eStatus;
    }


    /* configure the classifier sub-module */
    txDataQ_InitResources();

    //Report(REPORT_SEVERITY_INIT, ".....Tx Data Queue configured successfully\r\n");

    return OK;
}


/**
 * \fn     txDataQ_Destroy
 * \brief  Destroy the module and its queues
 *
 * Clear and destroy the queues and then destroy the module object.
 *
 * \note
 * \param  pTxDataQ - The object
 * \return OK - Unload succesfull, NOK - Unload unsuccesfull
 * \sa
 */
uint32_t txDataQ_Destroy (void)
{
    TTxDataQ  *pTxDataQ = gTxDataQCB;
    uint32_t  status = OK;
    uint32_t  uQueId;
    TDataLinkQ *pLinkQ;
    uint32_t  uHlid;

    if (pTxDataQ == NULL)
    {
        return NOK;
    }

    /* Dequeue and free all queued packets */
    txDataQ_ClearQueues ();

    /*
     * init all queues in all links
     */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        pLinkQ = &pTxDataQ->aDataLinkQ[uHlid]; /* Link queues */

        /* Free Data queues */
        for (uQueId = 0; uQueId < MAX_NUM_OF_AC; uQueId++)
        {
            if (que_Destroy(pLinkQ->aQueues[uQueId]) != OK)
            {
                //Report(REPORT_SEVERITY_ERROR, "txDataQueue_unLoad: fail to free Data Queue number: %d\r\n",uQueId);
                status = NOK;
            }
        }
    }

    /* Free Tx Data Queue Module */
    os_free (pTxDataQ);

    return status;
}


/**
 * \fn     txDataQ_ClearQueues
 * \brief  Clear all queues
 *
 * Dequeue and free all queued packets.
 *
 * \note
 * \param  pTxDataQ - The object
 * \return void
 * \sa
 */
void txDataQ_ClearQueues (void)
{
    uint32_t  uHlid;

    /*
     * init all queues in all links
     */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        txDataQ_FlushLinkQueues(uHlid);
    }
}


/**
 * \fn     txDataQ_FlushLinkQueues
 * \brief  Flush all queues of the specific link
 *
 * Free all pending packets in link queue
 *
 * \note
 * \param  pTxDataQ - The object
 * \param  uHlid - Link ID
 * \return void
 * \sa
 */
void txDataQ_FlushLinkQueues (uint32_t uHlid)
{
    TTxDataQ   *pTxDataQ = gTxDataQCB;
    TTxCtrlBlk *pPktCtrlBlk;
    uint32_t  uQueId;
    TDataLinkQ *pLinkQ;

    pLinkQ = &pTxDataQ->aDataLinkQ[uHlid]; /* Link queues */

    /* Dequeue and free all queued packets */
    for (uQueId = 0; uQueId < MAX_NUM_OF_AC; uQueId++)
    {
        do
        {
            trnspt_lockTxQueue();
            pPktCtrlBlk = (TTxCtrlBlk *) que_Dequeue (pLinkQ->aQueues[uQueId]);
            if (pPktCtrlBlk == NULL)
            {
                trnspt_unlockTxQueue();
                break;
            }
            trnspt_unlockTxQueue();

            txHwQueue_free_allocated_mem_blocks(pPktCtrlBlk);
            TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rTxDataQ_FlushLinkQueues descID:%d\r\n", pPktCtrlBlk->tTxDescriptor.descID);
            txCtrl_FreePacket (pPktCtrlBlk, NOK);
        }
        while(1);
    }
}

/**
 * \fn     txDataQ_ClearLink
 * \brief  Clear the link
 *
 * \note
 * \param  pTxDataQ     - The module's object
 * \param  uHlid        - link id
 * \return void
 */
void txDataQ_ClearLink(uint32_t uHlid)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;
    TDataLinkQ *pLinkQ = &pTxDataQ->aDataLinkQ[uHlid];

    CLEAR_BIT_BY_IDX(pTxDataQ->uLinkBusyBitmap, uHlid);
    pLinkQ->bEnabled = FALSE;
    pLinkQ->bEncrypt = FALSE;
}

/**
 * \fn     txDataQ_InsertPacket
 * \brief  Insert packet in queue and schedule task
 *
 * This function is called by the hard_start_xmit() callback function.
 * If the packet it an EAPOL, forward it to the Mgmt-Queue.
 * Otherwise, classify the packet, enqueue it and request
 *   context switch for handling it in the driver's context.
 *
 * \note
 * \param  pTxDataQ    - The object
 * \param  pPktCtrlBlk - Pointer to the packet
 * \param  uPacketDtag - The packet priority optionaly set by the OAL
 * \return OK - if the packet was queued, NOK - if the packet was dropped.
 * \sa     txDataQ_Run
 */
uint32_t txDataQ_InsertPacket(TTxCtrlBlk *pPktCtrlBlk, uint8_t uPacketDtag)
{
    TTxDataQ       *pTxDataQ = gTxDataQCB;
    int32_t        eStatus,bitAcBusy;
    uint32_t        uQueId;
    Bool_e          bRequestSchedule = FALSE;
    uint32_t        uHlid = pPktCtrlBlk->tTxDescriptor.hlid;
    TDataLinkQ     *pLinkQ = &pTxDataQ->aDataLinkQ[uHlid];
    uint8_t        isDataFrame =1;
    //CL_TRACE_START_L3();


   // pPktCtrlBlk->tTxDescriptor.startTime = osi_GetTimeMS();

    SET_PKT_RATE_POLICY(pPktCtrlBlk, pTxDataQ->pUdata->aLinkInfo[uHlid].uDataRatePolicyIdx);

    pPktCtrlBlk->tTxPktParams.uPktType = TX_PKT_TYPE_ETHER;

    /* Enter critical section to protect classifier data and queue access */
    trnspt_lockTxQueue();

    /* Call the Classify function to set the TID field */
    if (txDataClsfr_ClassifyTxPacket (pPktCtrlBlk, uPacketDtag) != OK)
    {
#ifdef TI_DBG
        pTxDataQ->uClsfrMismatchCount++;
        //Report(REPORT_SEVERITY_WARNING, "txDataQ_InsertPacket: No matching classifier found \r\n");
#endif /* TI_DBG */
    }

    uQueId = txCtrl_SelectAcForTid(uHlid, &(pPktCtrlBlk->tTxDescriptor.tid));

    /* Set resources per LINK and per AC */
    if (txDataQ_AllocCheckResources(pPktCtrlBlk,isDataFrame) != OK)
    {
#ifdef TI_DBG
        pLinkQ->aQueueCounters[uQueId].uDroppedPacket++;
        pTxDataQ->uNoResourcesCount++;
#endif /* TI_DBG */

        /* Leave critical section */
        trnspt_unlockTxQueue();
        /* We failed to alloc this packet, but host driver counted in it txDataQ_AllocCheckResources. 
            Hence - decrement in txDataQ_FreeFwAllocated*/
        txDataQ_FreeFwAllocated (pPktCtrlBlk);
        //Report("\n\rtxDataQ_InsertPacket: No resources, TID=%d, AC=%d, Link=%d\r\n", pPktCtrlBlk->tTxDescriptor.tid, uQueId, uQueId);

        /* If the packet can't be queued drop it */
        txCtrl_FreePacket (pPktCtrlBlk, NOK);
        TX_DATA_SEND_PRINT_ERROR("\n\rError! txDataQ_AllocCheckResources failed");
        return NOK;
    }

    //Report("\n\r dbg_tx. que_Enqueue, uHlid:%d, uQueId:%d", uHlid , uQueId);

    /* Enqueue the packet in the appropriate Queue */
    eStatus = que_Enqueue (pLinkQ->aQueues[uQueId], (void *)pPktCtrlBlk);
    /* Get number of packets in current queue */
    if(eStatus < 0)
    {
        TX_DATA_SEND_PRINT("\n\rNotice txDataQ_InsertPacket:que_Enqueue, No room in queue uQueId:%d limit :%d eStatus=%d",
            uQueId, que_GetLimit(pLinkQ->aQueues[uQueId]),eStatus);
        eStatus = NOK;
    }

    bitAcBusy = IS_BIT_SET(pTxDataQ->uAcBusyBitmap, uQueId); //currently not in use bitAcBusy=0, used by backprasure

    /* Leave critical section */
    trnspt_unlockTxQueue();

    if (!bitAcBusy)
    {
        /* If the queue has the desired number of packets, request switch to driver context for handling them */
        bRequestSchedule = TRUE;
        /* If below Tx-Send pacing threshold, start timer to trigger packets handling if expired */
    }


    if (eStatus == OK)
    {
        TX_DATA_SEND_PRINT("\n\r txDataQ_InsertPacket , bRequestSchedule:%d uQueId:%d",
               bRequestSchedule, uQueId);

        /* Protection of txData Request Schedule counter*/
        pLinkQ->aQueueCounters[uQueId].uEnqueuePacket++;

        /* If needed, schedule Tx handling */
        if (bRequestSchedule)
        {
            TX_DATA_SEND_PRINT("\n\rtxDataQ_InsertPacket , replace context:%d",pTxDataQ->uContextId);
            trnspt_RequestSchedule (pTxDataQ->uContextId, FALSE);
    
        }
    }
    else //if (eStatus != OK)
    {
        /* We failed to enqueue this packet, but host driver counted in it txDataQ_AllocCheckResources. 
        Hence - decrement in txDataQ_FreeFwAllocated*/
        txDataQ_FreeFwAllocated (pPktCtrlBlk); 
        /* If the packet can't be queued drop it */
        txCtrl_FreePacket (pPktCtrlBlk, NOK);
        //Report(REPORT_SEVERITY_WARNING, "txDataQ_InsertPacket: Packet dropped\r\n");
        pLinkQ->aQueueCounters[uQueId].uDroppedPacket++;

        TX_DATA_SEND_PRINT("\n\rNotice! txDataQ_InsertPacket,tx queue failed, drop the frame");

    }

    //CL_TRACE_END_L3 ("tiwlan_drv.ko", "INHERIT", "TX", "");

    return eStatus;
}


/**
 * \fn     txDataQ_UpdateBusyMap
 * \brief  Set queue's busy indication
 *
 * This function is called by the txCtrl if the backpressure map per TID is changed.
 * This could be as a result of Tx-Complete, admission change or association.
 * The function modifies the internal queue's Busy indication and calls the scheduler.
 *
 * \note
 * \param  pTxDataQ - The object
 * \param  pBackpressure     - the regular backpressure bitmaps
 * \return void
 * \sa     
 */
void txDataQ_UpdateBusyMap(TTxHwBackpressure  *pBackpressure)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;

    /* Update the ACs and Links busy states and priorities */
    pTxDataQ->uAcBusyBitmap       = pBackpressure->uAcBusyBitmap;
    pTxDataQ->uLinkBusyBitmap     = pBackpressure->uLinkBusyBitmap;
    pTxDataQ->uLinkPriorityBitmap = pBackpressure->uLinkPriorityBitmap;
    

    pTxDataQ->aAcQueueLen[AC_PRIORITY_BK] = pBackpressure->aAcQueueLen[QOS_AC_BK];
    pTxDataQ->aAcQueueLen[AC_PRIORITY_BE] = pBackpressure->aAcQueueLen[QOS_AC_BE];
    pTxDataQ->aAcQueueLen[AC_PRIORITY_VI] = pBackpressure->aAcQueueLen[QOS_AC_VI];
    pTxDataQ->aAcQueueLen[AC_PRIORITY_VO] = pBackpressure->aAcQueueLen[QOS_AC_VO];

#if 0
    /* Run the scheduler */
    if (pBackpressure->TransmitQOnTxComplete)
    {
        txDataQ_ReqToRunTxScheduler();
    }
#endif

}


/**
 * \fn     txDataQ_StopAll
 * \brief  Disable Data-Queue module access to Tx path.
 *
 * Called by the Tx-Port when the data-queue module can't access the Tx path.
 * Sets stop-all-queues indication.
 *
 * \note
 * \param  pTxDataQ - The object
 * \return void
 * \sa     txDataQ_WakeAll
 */
void txDataQ_StopAll (void)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;

    //Report(REPORT_SEVERITY_INFORMATION, "txDataQ_StopAll: Called\r\n");

    /* Disable the data Tx port */
    pTxDataQ->bDataPortEnable = FALSE;
}


/**
 * \fn     txDataQ_WakeAll
 * \brief  Enable Data-Queue module access to Tx path.
 *
 * Called by the Tx-Port when the data-queue module can access the Tx path.
 * Clears the stop-all-queues indication and calls the scheduler.
 *
 * \note
 * \param  pTxDataQ - The object
 * \return void
 * \sa     txDataQ_StopAll
 */
void txDataQ_WakeAll (void)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;

    //Report(REPORT_SEVERITY_INFORMATION, "txDataQ_WakeAll: Called\r\n");

    /* Enable the data Tx port */
    pTxDataQ->bDataPortEnable = TRUE;

    //Report("\n\r dbg_tx. txDataQ_WakeAll, txDataQ_ReqToRunTxScheduler");

    /* Run the scheduler */
    txDataQ_ReqToRunTxScheduler();
}

/**
 * \fn     txDataQ_ReqToRunTxScheduler
 * \brief  Notify Request Scheduler on Tx Complete
 *
 * Called by the Tx Complete when there is more frames pending for Tx in queue
 *
 * \note
 * \param  pTxDataQ - The object
 * \return void
 * \sa    txDataQ_ReqToRunTxScheduler
 */
void txDataQ_ReqToRunTxScheduler (void)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;

    /* Run the scheduler */
    //Report("\n\r dbg_tx. txDataQ_ReqToRunTxScheduler: Called\r\n");
    trnspt_RequestSchedule(pTxDataQ->uContextId, FALSE);
}

/**
 * \fn     txDataQ_DisableLink
 * \brief  Disable Data-Queue module access to Tx link.
 *
 * Called by the Tx-Port when the data-queue module can't access the Tx link.
 *
 * \note
 * \param  pTxDataQ - The object
 * \return void
 * \sa     txDataQ_EnableLink
 */
void txDataQ_DisableLink (uint32_t uHlid)
{
    TTxDataQ   *pTxDataQ = gTxDataQCB;
    TDataLinkQ *pLinkQ = &pTxDataQ->aDataLinkQ[uHlid];

    pLinkQ->bEnabled = FALSE;
    //Report(REPORT_SEVERITY_INFORMATION, "txDataQ_DisableLink: link=%d\r\n", uHlid);
}


void txDataQ_noticeRemoveHlid ()
{
    TTxDataQ   *pTxDataQ = gTxDataQCB;
    pTxDataQ->txDataLinkRemoved = TRUE;
}

void txDataQ_removeHlidFromScheduler ()
{
    TTxDataQ   *pTxDataQ = gTxDataQCB;
    uint32_t   i;
    uint32_t uHlid = pTxDataQ->uMaxEnabledHlid;

    for (i = uHlid; i > 0; i--)
    {
        if (pTxDataQ->aDataLinkQ[i].bEnabled)
        {
                break;
        }
    }
    pTxDataQ->uMaxEnabledHlid = i;
    if (pTxDataQ->uNextToServeLink > pTxDataQ->uMaxEnabledHlid)
    {
        pTxDataQ->uNextToServeLink = 0;
    }

}

/**
 * \fn     txDataQ_EnableLink
 * \brief  Enable Data-Queue module access to Tx link.
 *
 * Called by the Tx-Port when the data-queue module can access the Tx link.
 *
 * \note
 * \param  pTxDataQ - The object
 * \return void
 * \sa     txDataQ_StopLink
 */
void txDataQ_EnableLink (uint32_t uHlid)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;
    TDataLinkQ *pLinkQ = &pTxDataQ->aDataLinkQ[uHlid];

    pLinkQ->bEnabled = TRUE;

    if (uHlid > pTxDataQ->uMaxEnabledHlid)
    {
        pTxDataQ->uMaxEnabledHlid = uHlid;
    }

    //Report(REPORT_SEVERITY_INFORMATION, "txDataQ_EnableLink: link=%d\r\n", uHlid);

    //Report("\n\r dbg_tx. txDataQ_EnableLink, txDataQ_ReqToRunTxScheduler uHlid:%d uMaxEnabledHlid:%d", uHlid,pTxDataQ->uMaxEnabledHlid);
    /* Run the scheduler */
    txDataQ_ReqToRunTxScheduler();
}

/**
 * \fn     txDataQ_LinkMacAdd
 * \brief  Set MAC address for the link id.
 *
  * \return void
 * \sa     txDataQ_LinkMacAdd
 */
uint32_t txDataQ_LinkMacAdd (uint32_t uHlid, const TMacAddr tMacAddr)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;

    if (uHlid >= LINK_MAC_TABLE_SIZE)
    {
       //Report(("%s: illegal uHlid = %d\r\n", __FUNCTION__, uHlid));
        return NOK;
    }
    /* Enter critical section to protect links data */
    trnspt_EnterCriticalSection ();

    pTxDataQ->aLinkMac[uHlid].uValid = TRUE;
    MAC_COPY (pTxDataQ->aLinkMac[uHlid].tMacAddr, tMacAddr);

    trnspt_LeaveCriticalSection ();

    return OK;
}

/**
 * \fn     txDataQ_LinkMacRemove
 * \brief  Set LinkMac table entry as invalid
 *
 * \return void
 * \sa     txDataQ_LinkMacRemove
 */
void txDataQ_LinkMacRemove (uint32_t uHlid)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;

    if (uHlid >= LINK_MAC_TABLE_SIZE)
    {
       //Report(("%s: illegal uHlid = %d\r\n", __FUNCTION__, uHlid));
        return;
    }
    /* Enter critical section to protect links data */
    trnspt_EnterCriticalSection ();
    pTxDataQ->aLinkMac[uHlid].uValid = FALSE;
    trnspt_LeaveCriticalSection ();
}



/**
 * \fn     txDataQ_LinkMacFind
 * \brief  Find entry with MAC address
 *
 * \return status
 * \sa     txDataQ_LinkMacFind
 */
uint32_t txDataQ_LinkMacFind (uint8_t *uHlid, TMacAddr tMacAddr)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;
    int i;
    int j;

    /* Enter critical section to protect links data */
    trnspt_EnterCriticalSection ();
    for (i=0; i<LINK_MAC_TABLE_SIZE; i++)
    {
        if (!pTxDataQ->aLinkMac[i].uValid)
        {
            /* entry not valid, skip to next entry */
            continue;
        }

        for (j=MAC_ADDR_LEN-1; j>=0; j--)
        {
            if (pTxDataQ->aLinkMac[i].tMacAddr[j] != tMacAddr[j])
            {
                /* different MAC, skip to next entry */
                break;
            }
        }
        if (j < 0)
        {
            /* Found, return index */
            *uHlid = i;
            trnspt_LeaveCriticalSection ();
            return OK;
        }
    }
    trnspt_LeaveCriticalSection ();

    /* Not found */
    *uHlid = INVALID_LINK; /* for debug */
    return NOK;
}


uint32_t txDataQ_GetMacFromLink (uint8_t uHlid, TMacAddr tMacAddr)
{
    TTxDataQ    *pTxDataQ = gTxDataQCB;

    if (!pTxDataQ->aLinkMac[uHlid].uValid)
    {
        /* entry not valid */
        return NOK;
    }

    MAC_COPY(tMacAddr, pTxDataQ->aLinkMac[uHlid].tMacAddr);

    return OK;
}

/**
 * \fn     txDataQ_CheckResources
 * \brief  Check resources per Link and per Ac
 *
 * NOTE: the caller only will protect with critical section
 *
 * \return uint32_t NOK when there are no resources
 */
uint32_t txDataQ_AllocCheckResources (TTxCtrlBlk *pPktCtrlBlk, uint8_t isDataFrame)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;
    TDataResources *pDataRsrc = &pTxDataQ->tDataRsrc;
    uint32_t uHlid = pPktCtrlBlk->tTxDescriptor.hlid;
    uint32_t uAc = WMEQosTagToACTable[pPktCtrlBlk->tTxDescriptor.tid];
    Bool_e bPktInUseAboveAcMin = FALSE;
    Bool_e bPktInUseAboveLinkMin = FALSE;
    Bool_e bEnqueuePacket;

    if(uAc >= MAX_NUM_OF_AC)
    {
        TX_PRINT_ERROR("\n\r error num of ac exceeded, uAc:%d tid:%d", uAc, pPktCtrlBlk->tTxDescriptor.tid);
        return NOK;
    }


    //made under trnspt_lockTxQueue
    // new packet, Increment packet in use counters
    if(isDataFrame)
    {
        pPktCtrlBlk->tTxPktParams.uAcPendTXDataDone = 1;
        pDataRsrc->uPktPendTXDataPerAc[uAc]++;
    }

    pDataRsrc->uPktInUsePerAc[uAc]++;
    pDataRsrc->uPktInUsePerLink[uHlid]++;

    /* set RSRC_ALLOCATED flag, used in txDataQ_FreeResources */
    SET_TX_CTRL_FLAG_RSRC_ALLOCATED(pPktCtrlBlk);

/*
    // Update Effective totals = Sum of Max ( PktInUse_PerAc [uAc],  Min_PerAc[uAc] ), uAc=0..MAX_AC
    // no need to calculate Sum of Max on every packet, just small check for this ac only
    if (pDataRsrc->uPktInUsePerAc[uAc] > pDataRsrc->uMinGuaranteePerAc[uAc])
    {
        pDataRsrc->uEffectiveTotalAc++;
        bPktInUseAboveAcMin = TRUE;
    }

    // Update Effective totals = Sum of Max ( PktInUse_PerLik [uHlid],  Min_PerLink[uHlid] ), uHlid=0..MAX_LINK
    // no need to calculate Sum of Max on every packet, just small check for this link only
    if (pDataRsrc->uPktInUsePerLink[uHlid] > pDataRsrc->uMinGuaranteePerLink)
    {
        pDataRsrc->uEffectiveTotalLink++;
        bPktInUseAboveLinkMin = TRUE;
    }

    // if both effective total are above Max total, enqueue the packet
    if ( (pDataRsrc->uEffectiveTotalAc < pDataRsrc->uMaxTotal) && (pDataRsrc->uEffectiveTotalLink < pDataRsrc->uMaxTotal) )
    {
        bEnqueuePacket = TRUE;
    }
    else if ( (pDataRsrc->uEffectiveTotalAc >= pDataRsrc->uMaxTotal) && (bPktInUseAboveAcMin) )
    {
        // In this point one of the EffectiveTotal reach the MaxTotal
        // if uEffectiveTotal_Ac reach Max total, check if also ac counter above min
        bEnqueuePacket = FALSE;
        TX_PRINT_ERROR("\n\r packet will not be enqueue: uEffectiveTotalAc:%u uMaxTotal:%u bPktInUseAboveAcMin:%u ", pDataRsrc->uEffectiveTotalAc, pDataRsrc->uMaxTotal,bPktInUseAboveAcMin);
    }
    else if ( (pDataRsrc->uEffectiveTotalLink >= pDataRsrc->uMaxTotal) && (bPktInUseAboveLinkMin) )
    {
        // if uEffectiveTotal_Link reach Max total, check if also link counter above min
        bEnqueuePacket = FALSE;
        TX_PRINT_ERROR("\n\r packet will not be enqueue: uEffectiveTotalLink:%u uMaxTotal:%u bPktInUseAboveLinkMin:%u ", pDataRsrc->uEffectiveTotalAc, pDataRsrc->uMaxTotal,bPktInUseAboveLinkMin);
    }
    else
    {
        // both reach Max total, but al least one is below the MinGuarantee threshold
        bEnqueuePacket = TRUE;
    }

    // save AC in tx ctrl block, it may change when QOS is disabled and by AC downgrade algo, used in txDataQ_FreeResources
    SET_TX_CTRL_FLAG_RSRC_AC(pPktCtrlBlk, uAc);

    if (!bEnqueuePacket)
    {
        // In case of failure, the caller will free the resources
        TX_PRINT_ERROR("\n\rerror txDataQ_AllocCheckResources failed");
        return NOK;
    }
*/
    return OK;
}

/**
 * \fn     txDataQ_FreeResources
 * \brief  Free resources per Link and per Ac
 *
 */
void txDataQ_FreeResources (TTxCtrlBlk *pPktCtrlBlk)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;
    TDataResources *pDataRsrc = &pTxDataQ->tDataRsrc;
    uint32_t uHlid = pPktCtrlBlk->tTxDescriptor.hlid;
    uint32_t uAc = WMEQosTagToACTable[pPktCtrlBlk->tTxDescriptor.tid];

    /* Enter critical section to protect classifier data and queue access */
    trnspt_lockTxQueue();

    /* Free TxData resources only if previous allocated by txDataQ_AllocCheckResources */
    if (!IS_TX_CTRL_FLAG_RSRC_ALLOCATED(pPktCtrlBlk))
    {
        //Report("\n\r dbg_tx. txDataQ_FreeResources, resources were not allocate");//dbg_tx
        trnspt_unlockTxQueue();
        return;
    }
    CLEAR_TX_CTRL_FLAG_RSRC_ALLOCATED(pPktCtrlBlk);


    /* new packet, decrement packet in use counters */
    pDataRsrc->uPktInUsePerAc[uAc]--;
    pDataRsrc->uPktInUsePerLink[uHlid]--;

    /*
    // Update Effective totals = Sum of Max ( PktInUse_PerAc [uAc],  Min_PerAc[uAc] ), uAc=0..MAX_AC
    // no need to calculate Sum of Max on every packet, just small check for this ac only
    if (pDataRsrc->uPktInUsePerAc[uAc] >= pDataRsrc->uMinGuaranteePerAc[uAc])
    {
    	if(pDataRsrc->uEffectiveTotalAc >0)
    	{
    		pDataRsrc->uEffectiveTotalAc--;
    	}
#ifdef TI_DBG
        // sanity check
        if (pDataRsrc->uEffectiveTotalAc < pDataRsrc->uEffectiveTotalAcMin )
        {
            //Report(REPORT_SEVERITY_ERROR, "txDataQ_FreeResources(): uEffectiveTotalAc=%d is below MIN=%d\r\n", pDataRsrc->uEffectiveTotalAc, pDataRsrc->uEffectiveTotalAcMin);
        }
#endif
    }

    // Update Effective totals = Sum of Max ( PktInUse_PerLik [uHlid],  Min_PerLink[uHlid] ), uHlid=0..MAX_LINK
    // no need to calculate Sum of Max on every packet, just small check for this link only
    if (pDataRsrc->uPktInUsePerLink[uHlid] >= pDataRsrc->uMinGuaranteePerLink)
    {
    	if( pDataRsrc->uEffectiveTotalLink > 0)
    	{
    		pDataRsrc->uEffectiveTotalLink--;
    	}
#ifdef TI_DBG
        // sanity check
        if (pDataRsrc->uEffectiveTotalLink < pDataRsrc->uEffectiveTotalLinkMin )
        {
            //Report(REPORT_SEVERITY_ERROR, "txDataQ_FreeResources(): uEffectiveTotal_Ac=%d is below MIN=%d\r\n", pDataRsrc->uEffectiveTotalLink, pDataRsrc->uEffectiveTotalLinkMin);
        }
#endif
    }

    // Leave critical section
    */

    trnspt_unlockTxQueue();
}


void txDataQ_FreeFwAllocated (TTxCtrlBlk *pPktCtrlBlk)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;
    TDataResources *pDataRsrc = &pTxDataQ->tDataRsrc;
    uint32_t uHlid = pPktCtrlBlk->tTxDescriptor.hlid;
    uint32_t uAc = WMEQosTagToACTable[pPktCtrlBlk->tTxDescriptor.tid];

    /* Enter critical section to protect classifier data and queue access */
    trnspt_lockTxQueue();


    /* new packet, decrement packet in use counters */
    if(pPktCtrlBlk->tTxPktParams.uAcPendTXDataDone )
    {
        //Report("\n\r dbg_tx. txDataQ_FreeFwAllocated, txDataQ_ReqToRunTxScheduler uAc:%d uPktPendTXDataPerAc:%d", uAc, pDataRsrc->uPktPendTXDataPerAc[uAc]);
        pDataRsrc->uPktPendTXDataPerAc[uAc]--;
        pPktCtrlBlk->tTxPktParams.uAcPendTXDataDone =0;
    }

    if (pDataRsrc->uPktPendTXDataPerAc[uAc] < 0)
    {
        TX_PRINT_ERROR("\n\rError: uPktPendTXDataPerAc < 0");
        ASSERT_GENERAL(0);
    }
    /* Leave critical section */
    trnspt_unlockTxQueue();
}



/**
 * \fn     txDataQ_InitResources
 * \brief  Init resources counters per Link and per Ac
 *
 */
static void txDataQ_InitResources (void)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;
    TDataResources *pDataRsrc = &pTxDataQ->tDataRsrc;
    uint32_t uHlid;
    uint32_t uAc;

    /* Init counters per AC */
    pDataRsrc->uEffectiveTotalAc = 0;
    for (uAc=0; uAc<MAX_NUM_OF_AC; uAc++)
    {
        pDataRsrc->uPktInUsePerAc[uAc] = 0;
        pDataRsrc->uPktPendTXDataPerAc[uAc] = 0;
        pDataRsrc->uMinGuaranteePerAc[uAc] = MinGuarantee_PerAc[uAc];
        pDataRsrc->uEffectiveTotalAc += pDataRsrc->uMinGuaranteePerAc[uAc];
    }

    /* Init counters per LINK */
    pDataRsrc->uEffectiveTotalLink = 0;
    pDataRsrc->uMinGuaranteePerLink = TX_DATA_MIN_GUARANTEE_LINK_DEF;
    for (uHlid=0; uHlid<WLANLINKS_MAX_LINKS; uHlid++)
    {
        pDataRsrc->uPktInUsePerLink[uHlid] = 0;
        pDataRsrc->uEffectiveTotalLink += pDataRsrc->uMinGuaranteePerLink;
    }
#ifdef TI_DBG
    /* for sanity check */
    pDataRsrc->uEffectiveTotalAcMin += pDataRsrc->uEffectiveTotalAc;
    pDataRsrc->uEffectiveTotalLinkMin += pDataRsrc->uEffectiveTotalLink;
#endif

    pDataRsrc->uMaxTotal = CTRL_BLK_ENTRIES_NUM; /* Max total is the MAX tx ctrl blocks */
}


/***************************************************************************
*                       DEBUG  FUNCTIONS  IMPLEMENTATION                   *
****************************************************************************/

#ifdef TI_DBG

/**
 * \fn     txDataQ_PrintModuleParams
 * \brief  Print Module Parameters
 *
 * Print Module Parameters
 *
 * \note
 * \param  pTxDataQ - The object
 * \return void
 * \sa
 */
void txDataQ_PrintModuleParams (void)
{
    TTxDataQ   *pTxDataQ = gTxDataQCB;
    uint32_t    qIndex;
    TDataLinkQ *pLinkQ;
    uint32_t    uHlid;

   //Report(("--------- txDataQueue_printModuleParams ----------\n\r\n"));

   //GTRACE(1, "bDataPortEnable     = %d\r\n",pTxDataQ->bDataPortEnable));
   //GTRACE(1, "uContextId          = %d\r\n",pTxDataQ->uContextId));
   //GTRACE(1, "uNoResourcesCount   = %d\r\n",pTxDataQ->uNoResourcesCount));
   //GTRACE(1, "uMaxEnabledHlid     = %d\r\n",pTxDataQ->uMaxEnabledHlid));
   //GTRACE(1, "aQueueMaxSize       = %2d %2d %2d %2d\r\n", pTxDataQ->aQueueMaxSize[0], pTxDataQ->aQueueMaxSize[1], pTxDataQ->aQueueMaxSize[2], pTxDataQ->aQueueMaxSize[3]));
   //GTRACE(1, "uAcBusyBitmap       = 0x%x\r\n", pTxDataQ->uAcBusyBitmap));
   //GTRACE(1, "uLinkBusyBitmap     = 0x%x\r\n", pTxDataQ->uLinkBusyBitmap));
   //GTRACE(1, "uLinkPriorityBitmap = 0x%x\r\n", pTxDataQ->uLinkPriorityBitmap));
    /*
     * init all queues in all links
    */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        uint8_t *pMacAddr = pTxDataQ->aLinkMac[uHlid].tMacAddr;
        pLinkQ = &pTxDataQ->aDataLinkQ[uHlid]; /* Link queues */

       //GTRACE(1, "Link %3d ----------------------------------------\r\n", uHlid));
       //GTRACE(1, "  bEnabled=%1d\r\n", pLinkQ->bEnabled));
        if (!pLinkQ->bEnabled)
            continue;
       //GTRACE(1, "  MAC(valid=%01d) = %02x:%02x:%02x:%02x:%02x:%02x\r\n", pTxDataQ->aLinkMac[uHlid].uValid, pMacAddr[0], pMacAddr[1], pMacAddr[2], pMacAddr[3], pMacAddr[4], pMacAddr[5] ));

        for (qIndex = 0; qIndex < MAX_NUM_OF_AC; qIndex++)
        {
           //GTRACE(1, "  Que %d: ", qIndex));
            que_Print (pLinkQ->aQueues[qIndex]);
        }
    }
}


/**
 * \fn     txDataQ_PrintQueueStatistics
 * \brief  Print queues statistics
 *
 * Print queues statistics
 *
 * \note
 * \param  pTxDataQ - The object
 * \return void
 * \sa
 */
void txDataQ_PrintQueueStatistics (void)
{
#ifdef REPORT_LOG
    TTxDataQ *pTxDataQ = gTxDataQCB;
    TDataLinkQ     *pLinkQ;
    uint32_t      uHlid;

   //Report(("-------------- txDataQueue_printStatistics -------\n\r\n"));

   //GTRACE(1, "uClsfrMismatchCount      = %d\r\n",pTxDataQ->uClsfrMismatchCount));
   //GTRACE(1, "uTxSendPaceTimeoutsCount = %d\r\n",pTxDataQ->uTxSendPaceTimeoutsCount));

    /*
     * init all queues in all links
    */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        uint8_t *pMacAddr = pTxDataQ->aLinkMac[uHlid].tMacAddr;
        pLinkQ = &pTxDataQ->aDataLinkQ[uHlid]; /* Link queues */

       //GTRACE(1, "Link %3d, Enabled=%1d--------------------------\r\n", uHlid, pLinkQ->bEnabled));
        if (!pLinkQ->bEnabled)
            continue;
       //GTRACE(1, "  MAC(valid=%01d) = %02x:%02x:%02x:%02x:%02x:%02x\r\n", pTxDataQ->aLinkMac[uHlid].uValid, pMacAddr[0], pMacAddr[1], pMacAddr[2], pMacAddr[3], pMacAddr[4], pMacAddr[5] ));
       //GTRACE(1, "  uEnqueuePacket: %8d %8d %8d %8d\r\n", pLinkQ->aQueueCounters[0].uEnqueuePacket, pLinkQ->aQueueCounters[1].uEnqueuePacket, pLinkQ->aQueueCounters[2].uEnqueuePacket, pLinkQ->aQueueCounters[3].uEnqueuePacket ));
       //GTRACE(1, "  uDequeuePacket: %8d %8d %8d %8d\r\n", pLinkQ->aQueueCounters[0].uDequeuePacket, pLinkQ->aQueueCounters[1].uDequeuePacket, pLinkQ->aQueueCounters[2].uDequeuePacket, pLinkQ->aQueueCounters[3].uDequeuePacket ));
       //GTRACE(1, "  uRequeuePacket: %8d %8d %8d %8d\r\n", pLinkQ->aQueueCounters[0].uRequeuePacket, pLinkQ->aQueueCounters[1].uRequeuePacket, pLinkQ->aQueueCounters[2].uRequeuePacket, pLinkQ->aQueueCounters[3].uRequeuePacket ));
       //GTRACE(1, "  uXmittedPacket: %8d %8d %8d %8d\r\n", pLinkQ->aQueueCounters[0].uXmittedPacket, pLinkQ->aQueueCounters[1].uXmittedPacket, pLinkQ->aQueueCounters[2].uXmittedPacket, pLinkQ->aQueueCounters[3].uXmittedPacket ));
       //GTRACE(1, "  uDroppedPacket: %8d %8d %8d %8d\r\n", pLinkQ->aQueueCounters[0].uDroppedPacket, pLinkQ->aQueueCounters[1].uDroppedPacket, pLinkQ->aQueueCounters[2].uDroppedPacket, pLinkQ->aQueueCounters[3].uDroppedPacket ));
       //GTRACE(1, "  uAcStopped:     %8d %8d %8d %8d\r\n", pLinkQ->aQueueCounters[0].uAcStopped, pLinkQ->aQueueCounters[1].uAcStopped, pLinkQ->aQueueCounters[2].uAcStopped, pLinkQ->aQueueCounters[3].uAcStopped ));
       //GTRACE(1, "  uLinkStopped:   %8d %8d %8d %8d\r\n", pLinkQ->aQueueCounters[0].uLinkStopped, pLinkQ->aQueueCounters[1].uLinkStopped, pLinkQ->aQueueCounters[2].uLinkStopped, pLinkQ->aQueueCounters[3].uLinkStopped ));
    }

    /* Print data resouces counters */
    txDataQ_PrintResources();
#endif
}

/**
 * \fn     txDataQ_ResetQueueStatistics
 * \brief  Reset queues statistics
 *
 * Reset queues statistics
 *
 * \note
 * \param  pTxDataQ - The object
 * \return void
 * \sa
 */
void txDataQ_ResetQueueStatistics (void)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;
    TDataLinkQ *pLinkQ;
    uint32_t  uHlid;

    /*
     * init all queues in all links
    */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
            pLinkQ = &pTxDataQ->aDataLinkQ[uHlid]; /* Link queues */

            os_memset(&pLinkQ->aQueueCounters, 0, sizeof(pLinkQ->aQueueCounters));
    }
    pTxDataQ->uTxSendPaceTimeoutsCount = 0;
}

/**
 * \fn     txDataQ_PrintResources
 * \brief  Print resources counters per Link and per Ac
 *
 */
static void txDataQ_PrintResources (void)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;
    TDataResources *pDataRsrc = &pTxDataQ->tDataRsrc;
    uint32_t uHlid;

   //GTRACE(1, "txDataQ_PrintResources ---------------------------------------------\r\n"));
    /* Print counters per AC */
   //GTRACE(1, "uPktInUsePerAc  = %8d %8d %8d %8d\r\n", pDataRsrc->uPktInUsePerAc[0], pDataRsrc->uPktInUsePerAc[1], pDataRsrc->uPktInUsePerAc[2], pDataRsrc->uPktInUsePerAc[3]));
   //GTRACE(1, "MinGuare_PerAc  = %8d %8d %8d %8d\r\n", pDataRsrc->uMinGuaranteePerAc[0], pDataRsrc->uMinGuaranteePerAc[1], pDataRsrc->uMinGuaranteePerAc[2], pDataRsrc->uMinGuaranteePerAc[3]));
   //GTRACE(1, "EffectivTotal_Ac= %d\r\n", pDataRsrc->uEffectiveTotalAc));

    /* Print counters per Link */
   //GTRACE(1, "PktInUse_PerLink= "));
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
       //Report(("%8d, ", pDataRsrc->uPktInUsePerLink[uHlid]));
    }
   //Report(("\r\n"));
   //GTRACE(1, "uMinGuaranteePerLink = %d\r\n", pDataRsrc->uMinGuaranteePerLink));
   //GTRACE(1, "uEffectiveTotalLink  = %d\r\n", pDataRsrc->uEffectiveTotalLink));
}


#endif /* TI_DBG */



/***************************************************************************
*                      INTERNAL  FUNCTIONS  IMPLEMENTATION                 *
****************************************************************************/

//#define AC_DEBUG_REPORT


/**
 * \fn     txDataQ_RunScheduler
 * \brief  The module's Tx scheduler
 *
 * This function is the Data-Queue scheduler.
 * It selects a packet to transmit from the tx queues and sends it to the TxCtrl.
 * The queues are selected in a round-robin order.
 * The function is called by one of:
 *     txDataQ_Run()
 *     txDataQ_UpdateBusyMap()
 *     txDataQ_WakeAll()
 *
 * \note
 * \param  pTxDataQ - The object
 * \return void
 * \sa
 */
static void txDataQ_RunScheduler (void* hCbHndl)
{
    TTxDataQ   *pTxDataQ = gTxDataQCB;
    TDataResources *pDataRsrc = &pTxDataQ->tDataRsrc; //add- on for debug
    uint32_t watchDogcount = 0;
    int32_t retVal = 0;
    // Read the current counter of request schedule calls

#ifdef DEBUG_TX_QUEUE_TABLE
    gErrorBusy = 0;
    gErrorFailed = 0;
    gErrorNullBlk = 0;
    if (gDebugIndex >= 99)
    {
        Report("\n\r ------------ txDataQ_RunScheduler ------");
        Report("\n\r #   | SchdReqs |   Ac 0  |   Ac 1  |   Ac 2  |   Ac 3  | sentPkts | crntFw | Err | Busy | Null|");
        for (i=0; i < gDebugIndex; i++)
        {
            //print all
            Report("\n\r %3d |    %2d    |  %2d/%2d |  %2d/%2d  |  %2d/%2d  |  %2d/%2d  | %7d | %6d | %2d | %2d | %2d | 0x%x",
            i, gDebugTxQ[i].uSchedReqCallsCount, 
            gDebugTxQ[i].uHostAcQCount[0], gDebugTxQ[i].uFwAcQCount[0],
            gDebugTxQ[i].uHostAcQCount[1], gDebugTxQ[i].uFwAcQCount[1],
            gDebugTxQ[i].uHostAcQCount[2], gDebugTxQ[i].uFwAcQCount[2],
            gDebugTxQ[i].uHostAcQCount[3], gDebugTxQ[i].uFwAcQCount[3],
            gDebugTxQ[i].uExitFrameSentCount, gDebugTxQ[i].uFwTotal,
            gDebugTxQ[i].uErrFail, gDebugTxQ[i].uErrBusy, gDebugTxQ[i].uErrNull,
            gDebugTxQ[i].tsf);
        }
        gDebugIndex = 0;
        memset(gDebugTxQ, 0, sizeof(gDebugTxQ));
    }

    gDebugTxQ[gDebugIndex].uHostAcQCount[0] = pDataRsrc->uPktPendTXDataPerAc[0];
    gDebugTxQ[gDebugIndex].uFwAcQCount[0] = txHwQueue_GetTxAcPktsCount(0);
    gDebugTxQ[gDebugIndex].uHostAcQCount[1] = pDataRsrc->uPktPendTXDataPerAc[1];
    gDebugTxQ[gDebugIndex].uFwAcQCount[1] = txHwQueue_GetTxAcPktsCount(1);
    gDebugTxQ[gDebugIndex].uHostAcQCount[2] = pDataRsrc->uPktPendTXDataPerAc[2];
    gDebugTxQ[gDebugIndex].uFwAcQCount[2] = txHwQueue_GetTxAcPktsCount(2);
    gDebugTxQ[gDebugIndex].uHostAcQCount[3] = pDataRsrc->uPktPendTXDataPerAc[3];
    gDebugTxQ[gDebugIndex].uFwAcQCount[3] = txHwQueue_GetTxAcPktsCount(3);
    gDebugTxQ[gDebugIndex].tsf = txHwQueue_GetlastFWTsf();
#endif
     

    while(1)
    {
        scheduleQueuesPerPriority(&retVal);

        if(retVal < 0)//means that there are no available mem-blocks
        {
            break;// the data scheduler will run again after receiving of Tx complete
        }
        watchDogcount++;
        if(watchDogcount > 0xFFFF)
        {
            TX_PRINT_ERROR("\r\n WARNING !!!!! , no frames to transmit !!! watchDogcount=%d numIterOnSameHlid=%d uNextToServeLink=%d uMaxEnabledHlid=%d pendAc0=%d pendAc1=%d pendAc2=%d pendAc3=%d",
                watchDogcount, retVal,
                pTxDataQ->uNextToServeLink, pTxDataQ->uMaxEnabledHlid,
                pTxDataQ->tDataRsrc.uPktPendTXDataPerAc[0],
                pTxDataQ->tDataRsrc.uPktPendTXDataPerAc[1],
                pTxDataQ->tDataRsrc.uPktPendTXDataPerAc[2],
                pTxDataQ->tDataRsrc.uPktPendTXDataPerAc[3]);
            { int i; for(i=0; i<=pTxDataQ->uMaxEnabledHlid; i++)
                TX_PRINT_ERROR("\r\n   HLID[%d]: bEnabled=%d", i, pTxDataQ->aDataLinkQ[i].bEnabled); }
            break;
        }
        if(pTxDataQ->txDataLinkRemoved)
        {
            pTxDataQ->txDataLinkRemoved = FALSE;
            txDataQ_removeHlidFromScheduler();

        }
    }

    //Report("\n\r dbg_tx. exit from the loop watchDogcount:%d "",watchDogcount);

#ifdef DEBUG_TX_QUEUE_TABLE
    gDebugTxQ[gDebugIndex].uExitFrameSentCount = i;
    gDebugTxQ[gDebugIndex].uFwTotal = txHwQueue_GetTxTotalPktsCount();
    gDebugTxQ[gDebugIndex].uErrFail = gErrorFailed;
    gDebugTxQ[gDebugIndex].uErrBusy = gErrorBusy;
    gDebugTxQ[gDebugIndex].uErrNull = gErrorNullBlk;
    gDebugIndex++;
#endif
}

const static EAcTrfcType getAcQueueTable[MAX_NUM_OF_AC] = {QOS_AC_VO, QOS_AC_VI, QOS_AC_BE, QOS_AC_BK};

static int txDataQ_SelectAc(void)
{
    TTxDataQ   *pTxDataQ = gTxDataQCB;
    TDataResources *pDataRsrc = &pTxDataQ->tDataRsrc;
    int i, chosendAc =-1, ac;
    uint32_t min_pkts = 0xffffffff;
    uint32_t TxAcPktsCount = 0;

    /*
	 * Find a non-empty ac where:
	 * 1. There are packets to transmit > 0 
	 * 2. The FW has the least allocated packets in this AC 
	 *
	 * We prioritize the ACs according to VO>VI>BE>BK
	 */
	for (i = 0; i < MAX_NUM_OF_AC; i++) 
    {
		ac = getAcQueueTable[i];

		TxAcPktsCount = txHwQueue_GetTxAcPktsCount(ac);
#ifdef AC_DEBUG_REPORT        
        Report("\r\nAc Debug , selectAC::: check for ac=%d, TxWaitForAckCount=%d chosendAc=%d, pDataRsrc->uPktInUsePerAc[ac]=%d, min_pkts=%d",
            ac, TxAcPktsCount, chosendAc, pDataRsrc->uPktPendTXDataPerAc[ac], min_pkts);
#endif

        //Report("\n\r dbg_tx. , selectAC::: check for ac=%d, TxAcPktsCount=%d chosendAc=%d, pDataRsrc->uPktInUsePerAc[ac]=%d, min_pkts=%d", ac, TxAcPktsCount, chosendAc, pDataRsrc->uPktPendTXDataPerAc[ac], min_pkts);

		if ((pDataRsrc->uPktPendTXDataPerAc[ac]) && //driver has data frames allocated on this ac
		    (TxAcPktsCount < min_pkts))
        {
		    chosendAc = ac;
			min_pkts = TxAcPktsCount;
		}
	}
#ifdef AC_DEBUG_REPORT  
    Report("\r\nAc Debug , Selected::::::  q=%d", chosendAc);
#endif
	return chosendAc;

}

#if 0
static Bool_e txDataQ_isLinkPriority(uint32_t uLinkPriorityToServe, uint32_t uHlid, uint32_t uFwAllocatedPkts) 
{
    uint8_t uThold;
    uint32_t suspendBM, fastBM, psBM;
    uint8_t txSuspendThold, txFastThold, txSlowThold, txStopFastThold, txStopSlowThold;

    txHwQueue_GetTxFlowControlLinkBitmaps(&suspendBM, &fastBM, &psBM);

    txHwQueue_GetTxFlowControlThresholds(&txSuspendThold, &txFastThold, &txSlowThold,
                                         &txStopFastThold, &txStopSlowThold);

#ifdef AC_DEBUG_REPORT  
    Report("\r\n Ac Debug ,thresholds: %d %d %d %d %d", txSuspendThold, txFastThold, txSlowThold,
                                                txStopFastThold, txStopSlowThold);
    Report("\r\nAc Debug , suspend_bm=0x%x fast_bm=0x%x ps_bm=0x%x", suspendBM, fastBM, psBM);
#endif
    
    if (uLinkPriorityToServe == HIGH_PRIORITY_LINK_LIST)
    {
        if (IS_BIT_SET(suspendBM, uHlid))
        {
            return FALSE;
        }

        if (IS_BIT_SET(fastBM, uHlid) &&
            !IS_BIT_SET(psBM, uHlid))
        {
            uThold = txFastThold;
        }
        else
        {
            uThold = txSlowThold;
        }
    }
    else
    {
        if (IS_BIT_SET(suspendBM, uHlid))
        {
            uThold = txSuspendThold;
        }
        else if (IS_BIT_SET(fastBM, uHlid) &&
                 !IS_BIT_SET(psBM, uHlid))
        {
            uThold = txStopFastThold;
        }
        else
        {
            uThold = txStopSlowThold;
        }
    }

#ifdef AC_DEBUG_REPORT 
    Report ("\r\nAc Debug , ::::: Link Priority %d - is served %d ", uLinkPriorityToServe, uFwAllocatedPkts < uThold);
#endif
    return uFwAllocatedPkts < uThold;
}
#endif

static void scheduleQueuesPerPriority(int32_t *retVal)
{
    TTxDataQ   *pTxDataQ = gTxDataQCB;
    TDataResources *pDataRsrc = &pTxDataQ->tDataRsrc;
    TDataLinkQ *pLinkQ = NULL;
    uint32_t    uHlid = pTxDataQ->uNextToServeLink;
    int32_t     uAcId;
    uint32_t    uLastServedHlid = 0;
    int32_t     numIterationOnSameHlid = 0;
    int32_t     ret;
    int32_t     bAnyHlidEnabled = 0; /* track if any HLID was enabled during this scheduling round */
    int32_t     bFoundAnyFrames = 0; /* track if any frame was actually sent this round */

    *retVal = -1;

#ifdef AC_DEBUG_REPORT 
    Report ("\r\n Ac Debug ,scheduleQueuesPerPriority, Link Priority %d ", uLinkPriorityToServe);
#endif
    if (pTxDataQ->bDataPortEnable)
    {

        /**
         * choose ac
         *          start with highest AC
         *          if there is data to send - check FW pkts allocated counter
         * choose link
         *          check if not suspended
         * send
         **/
        uAcId = txDataQ_SelectAc();
        if (uAcId < 0)
        {
            //Report("\n\r dbg_tx. scheduleQueuesPerPriority,select AC failed ,uHlid:%d ,exit func", uHlid);
            *retVal = -1;
            return;
        }

        //Report("\n\r dbg_tx. scheduleQueuesPerPriority, start loop, uHlid for start :%d chosen uAcId:%d", uHlid, uAcId);

        do
        {
            pLinkQ = &pTxDataQ->aDataLinkQ[uHlid];
#ifdef AC_DEBUG_REPORT 
            Report("\r\n Ac Debug , scheduleQueuesPerPriority uHlid=%d[0x%x], uAcId=%d[0x%x], enabled=%d, uLinkPriorityBitmap=0x%x linkP=%d pktsInUsePerLink=%d thres = %d > %d!!!!",
                uHlid, pTxDataQ->uLinkBusyBitmap, uAcId, 
                pTxDataQ->uAcBusyBitmap, pLinkQ->bEnabled, 
                pTxDataQ->uLinkPriorityBitmap, uLinkPriorityToServe,
                pDataRsrc->uPktInUsePerLink[uHlid],
                txHwQueue_GetLinkPrioThreshold(uHlid, uLinkPriorityToServe),
                txHwQueue_GetTxAcPktsCount(uAcId));
#endif
            do
            {
            /**
             * Choose link
             * 1. link enabled
             * 2. Check if link is not suspended
             * 3. Check if link is high/low prio accordingly 
             */
            if (pLinkQ->bEnabled &&
                   ( txHwQueue_GetHwBlocks() > txHwQueue_GetHwBlocksRequireForAvgFrame()) /*minimum frame size is 3 blocks */
                )
            {
                bAnyHlidEnabled = 1;
                //frame is send only from the chosen AC
                if ((ret= sendPacket(uHlid, uAcId))== FRAME_SEND_SUCCESFULY)
                {
                    /* Packet sent event*/
#ifdef AC_DEBUG_REPORT 
                    /* Ac Queue Statistics*/
                    Report("\r\n Ac Debug ,scheduleQueuesPerPriority"
                            "\r\n                 |     [0]     |     [1]     |     [2]     |     [3]   |"
                           "\r\nQueueCounters De |  %8d   |  %8d   |  %8d   |  %8d  |"
                           "\r\nQueueCounters En |  %8d   |  %8d   |  %8d   |  %8d  |"
                           "\r\nLeft             |  %8d   |  %8d   |  %8d   |  %8d  |"
                           "\r\n               -------------------------------  ",
                            pLinkQ->aQueueCounters[0].uDequeuePacket, // BK
                            pLinkQ->aQueueCounters[1].uDequeuePacket, // BE
                            pLinkQ->aQueueCounters[2].uDequeuePacket,
                            pLinkQ->aQueueCounters[3].uDequeuePacket,
                            pLinkQ->aQueueCounters[0].uEnqueuePacket,
                            pLinkQ->aQueueCounters[1].uEnqueuePacket,
                            pLinkQ->aQueueCounters[2].uEnqueuePacket,
                            pLinkQ->aQueueCounters[3].uEnqueuePacket,
                            pLinkQ->aQueueCounters[0].uEnqueuePacket - pLinkQ->aQueueCounters[0].uDequeuePacket,
                            pLinkQ->aQueueCounters[1].uEnqueuePacket - pLinkQ->aQueueCounters[1].uDequeuePacket,
                            pLinkQ->aQueueCounters[2].uEnqueuePacket - pLinkQ->aQueueCounters[2].uDequeuePacket,
                            pLinkQ->aQueueCounters[3].uEnqueuePacket - pLinkQ->aQueueCounters[3].uDequeuePacket
                            );
#endif
                    uLastServedHlid = uHlid;
                    numIterationOnSameHlid++;
                    bFoundAnyFrames = 1;
                    //Report("\n\r dbg_tx. packet was send uHlid:%d uAcId:%d", uHlid,uAcId );
                }
                else
                {
                    if( ret == NO_FRAMES_IN_QUEUE)
                    {
                        uLastServedHlid = uHlid;
                        //Report("\n\r dbg_tx. no more frames on queue  uHlid:%d uAcId:%d", uHlid,uAcId );
                        break;//continue to next Hlid, maybe there are frames in there
                    }
                    else //ERROR_SEND_FRAME_FAILED, probably due to no HW resource
                    {
                        uLastServedHlid = uHlid;
                        //numIterationOnSameHlid++;
       	                numIterationOnSameHlid = -2; //stop the iteration
                        //Report("\n\r dbg_tx. packet send error!  uHlid:%d uAcId:%d", uHlid,uAcId );
                        break;

                    }
                }
            }
            else//no HW resources
            {
			    if(pLinkQ->bEnabled)///it means that no resources for sending frame
				{
	                numIterationOnSameHlid = -3; //stop the iteration
	                uLastServedHlid = uHlid;//for the fairness lets move on on next call to the schedule to the next link
	                break;
				}
				else
				{
				    //link disabled continue to next link
				    uLastServedHlid = uHlid;
					break;
				}

            }
            }while(numIterationOnSameHlid);//continue on same Hlid until there are no frames in the queues or no FW resources

            if(numIterationOnSameHlid < 0)// there are no resources on FW, can stop
            {
                   break;
            }

            uHlid++;
            if (uHlid > pTxDataQ->uMaxEnabledHlid)
            {
                uHlid = 0;
            }

#ifdef AC_DEBUG_REPORT 
            Report("\r\n Ac Debug ,scheduleQueuesPerPriority ,uNextToServeLink=%d, uMaxEnabledHlid=%d pPacketSent:%d ",
                pTxDataQ->uNextToServeLink, pTxDataQ->uMaxEnabledHlid, numIterationOnSameHlid);
#endif
        }
        while (uHlid != pTxDataQ->uNextToServeLink);

        //Report("\n\r dbg_tx. scheduleQueuesPerPriority, end loop uMaxEnabledHlid:%d numIterationOnSameHlid:%d uLastServedHlid:%d",pTxDataQ->uMaxEnabledHlid,numIterationOnSameHlid,uLastServedHlid);

        /* Update the NextToServeHlid*/
        pTxDataQ->uNextToServeLink = uLastServedHlid + 1;
        if (pTxDataQ->uNextToServeLink > pTxDataQ->uMaxEnabledHlid)
        {
            pTxDataQ->uNextToServeLink = 0;
        }

    }
    /* Detect counter inconsistency: AC was selected (counter says frames exist)
     * and HLIDs had resources, but no frames found in any queue. This indicates
     * a mismatch between queue counters and actual queue state. */
    if (bAnyHlidEnabled && !bFoundAnyFrames && numIterationOnSameHlid >= 0)
    {
        TX_PRINT_ERROR("\r\n[TX_ERROR] AC selected but no frames in any HLID queue - counter inconsistency!"
                       " uAcId=%d pendAc0=%d pendAc1=%d pendAc2=%d pendAc3=%d uNextToServeLink=%d uMaxEnabledHlid=%d",
                       uAcId,
                       pDataRsrc->uPktPendTXDataPerAc[0],
                       pDataRsrc->uPktPendTXDataPerAc[1],
                       pDataRsrc->uPktPendTXDataPerAc[2],
                       pDataRsrc->uPktPendTXDataPerAc[3],
                       pTxDataQ->uNextToServeLink,
                       pTxDataQ->uMaxEnabledHlid);
    }

    /* Return -1 if no frames were actually sent this round (empty queues or all links disabled),
     * so the outer scheduler loop stops instead of spinning waiting for data that doesn't exist. */
    *retVal = (bAnyHlidEnabled && bFoundAnyFrames) ? numIterationOnSameHlid : -1;

}


/*
 * \brief   Handle Tx-Send-Pacing timeout.
 *
 * \param  pTxDataQ        - Module handle
 * \param  bTwdInitOccured - Indicate if TWD restart (recovery) occured
 * \return void
 *
 * \par Description
 * Call the Tx scheduler to handle the queued packets.
 *
 * \sa
 */
static void txDataQ_TxSendPaceTimeout (Bool_e bTwdInitOccured)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;

    pTxDataQ->uTxSendPaceTimeoutsCount++;

    txDataQ_ReqToRunTxScheduler();
}

