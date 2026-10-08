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
/** \file   txMgmtQueue.c
 *  \brief  The Tx Mgmt Queues module.
 *
 *  DESCRIPTION:
 *  ============
 *  The Management-Queues module is responsible for the following tasks:
 *      1.  Queue the driver generated Tx packets, including management,
 *          EAPOL and null packets until they are transmitted.
 *          The management packets are buffered in the management-queue,
 *          and the others in the EAPOL-queue.
 *      2.  Maintain a state machine that follows the queues state and
 *          the connection states and enables specific transmission types
 *          accordingly (e.g. only management).
 *      3.  Gain access to the Tx path when the management queues are not
 *          empty, and return the access to the data queues when the
 *          management queues are empty.
 *      4.  Schedule packets transmission with strict priority of the
 *          management queue over the EAPOL queue, and according to the
 *          backpressure controls from the Port (all queues) and from the
 *          Tx-Ctrl (per queue).
 *
 *  \see    txMgmtQueue.h
 */

#define __FILE_ID__  FILE_ID_36
#include "paramOut.h"
#include "osi_kernel.h"
#include <trnspt_thread.h>
#include "public_share.h"
#include "tw_driver.h"
#include "ethernet.h"
#include "w_queue.h"
#include "udata_api.h"
#include "udata.h"
#include "tx_ctrl_api.h"
#include "tx_data_queue_api.h"
#include "tx_mgmt_queue_api.h"
#include "tx_hw_queue_api.h"
#include "nab.h"
#include "tx.h"
#include "trnspt_if.h"
#include "udata.h"

#define DUMMY_PKT_BUF_LEN   1400


/* State-Machine Events */
typedef enum
{
    SM_EVENT_CLOSE,         /* All Tx types should be closed. */
    SM_EVENT_MGMT,          /* Allow only mgmt packets. */
    SM_EVENT_EAPOL,         /* Allow mgmt and EAPOL packets. */
    SM_EVENT_OPEN,          /* Allow all packets. */
    SM_EVENT_QUEUES_EMPTY,  /* Mgmt-aQueues are now both empty. */
    SM_EVENT_QUEUES_NOT_EMPTY /* At least one of the Mgmt-aQueues is now not empty. */
} ESmEvent;


/* State-Machine Actions */
typedef enum
{
    SM_ACTION_NULL,
    SM_ACTION_ENABLE_DATA,
    SM_ACTION_ENABLE_MGMT,
    SM_ACTION_RUN_SCHEDULER,
    SM_ACTION_STOP_ALL
} ESmAction;

/* TRUE if both aQueues are empty. */
#define ARE_LINK_MGMT_QUEUES_EMPTY(aQueues) ( (que_Size(aQueues[QUEUE_TYPE_MGMT] ) == 0)  &&  \
                                              (que_Size(aQueues[QUEUE_TYPE_EAPOL]) == 0) )



#define LINK_MGMT_QUEUES_DEPTH MGMT_QUEUES_DEPTH


/* The module internal functions */
static void mgmtQueuesSM (uint32_t uHlid, ESmEvent smEvent);
static void runSchedulerNotFromSm (void);
static void runScheduler (void);
static void txMgmtQ_DisableLink (uint32_t uHlid);
static void txMgmtQ_EnableLink (uint32_t uHlid);

void dummyPktReqCB(char *str , uint32_t strLen, uint32_t uEventId);

/**
 * \brief   fills the nab tx header
 * *
 * \param   TMgmtPktDesc    pkt
 */

void set_nab_tx_header(NAB_tx_header_t *pNabTxHeader, uint32_t total_len )
{
    pNabTxHeader->sync = HOST_SYNC_PATTERN;
    pNabTxHeader->opcode = NAB_SEND_CMD;
    pNabTxHeader->len = total_len - sizeof(NAB_header_t); // length should include the following 4 bytes of the NAB comand.
    pNabTxHeader->desc_length = total_len - sizeof(NAB_tx_header_t);
    pNabTxHeader->sd = 0;
    pNabTxHeader->flags = NAB_SEND_FLAGS;
}

/*******************************************************************************
*                       PUBLIC  FUNCTIONS  IMPLEMENTATION                      *
********************************************************************************/

TTxMgmtQ *gTxMgmtQCB = NULL;

/**
 * \fn     txMgmtQ_Create
 * \brief  Create the module and its queues
 *
 * Create the Tx Mgmt Queue module and its queues.
 *
 * \note
 * \param  hOs - Handle to the Os Abstraction Layer
 * \return Handle to the allocated Tx Mgmt Queue module (NULL if failed)
 * \sa
 */
TTxMgmtQ* txMgmtQ_Create (void)
{
    /* allocate TxMgmtQueue module */
    gTxMgmtQCB = (TTxMgmtQ *)os_zalloc(sizeof(TTxMgmtQ));

    if(!gTxMgmtQCB)
    {
       //GTRACE(1, "Error allocating the TxMgmtQueue Module\r\n"));
        return NULL;
    }

    return gTxMgmtQCB;
}


/**
 * \fn     txMgmtQ_Init
 * \brief  Configure module with default settings
*
 * Get other modules handles.
 * Init the Tx Mgmt queues.
 * Register as the context-engine client.
 *
 * \note
 * \param  pStadHandles  - The driver modules handles
 * \return void
 * \sa
 */
void txMgmtQ_Init (TUdata *pUdata)
{
    TTxMgmtQ   *pTxMgmtQ = gTxMgmtQCB;
    uint32_t    uNodeHeaderOffset = TI_FIELD_OFFSET(TTxnStruct, tTxnQNode);
    int         uQueId;
    TMgmtLinkQ *pLinkQ;
    uint32_t    uHlid;

    /* configure modules handles */
    pTxMgmtQ->pUdata    = pUdata;

    pTxMgmtQ->bMgmtPortEnable = TRUE;   /* Port Default status is open (data-queues are disabled). */
    pTxMgmtQ->bMgmtAcBusy = FALSE;       /* Init busy flag for Mgmt access category (same for MGMT and EAPOL)  */
    
    /*
     * init all queues in all links
     */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link queues */
        pLinkQ->eTxConnState = LINK_STATE_CLOSED;
        pLinkQ->eState = SM_STATE_CLOSE; /* SM default state is CLOSE. */
        pLinkQ->bSendEventNotEmpty = FALSE;
        pLinkQ->bBusy = FALSE; /* default is not busy */
        pLinkQ->bEnabled = FALSE; /* default is not enabled */

        for (uQueId = 0; uQueId < NUM_OF_MGMT_QUEUES; uQueId++)
        {
            pLinkQ->aQueues[uQueId] = que_Create (LINK_MGMT_QUEUES_DEPTH,
                                                  uNodeHeaderOffset);

            /* If any Queues' allocation failed, print error, free TxMgmtQueue module and exit */
            if (pLinkQ->aQueues[uQueId] == NULL)
            {
               //Report(REPORT_SEVERITY_CONSOLE , "Failed to create queue for link %d\r\n", uHlid);
               //GTRACE(1, "Failed to create queue for link %d\r\n", uHlid));
                os_free (pTxMgmtQ);
                return;
            }

            pLinkQ->aQenabled[uQueId] = FALSE; /* Queue is disabled */
        }
    }
    pTxMgmtQ->uLastHlid = 0; /* scheduler starts from first link */

    /* Register to the context engine and get the client ID */
    pTxMgmtQ->uContextId = trnspt_RegisterClient ((TTransportCbFunc)txMgmtQ_QueuesNotEmpty, TRUE);
   //Report(REPORT_SEVERITY_INIT, ".....Tx Mgmt Queue configured successfully\r\n");
    TRANSPORT_PRINT_INIT("\n\rRegister Client:txMgmtQ_QueuesNotEmpty uContextId :%d",pTxMgmtQ->uContextId);

}

static uint32_t txMgmtQ_configureFw(void)
{
#if 0
    return TWD_RegisterEvent(pTxMgmtQ->hTWD,
                             TWD_OWN_EVENT_DUMMY_PKT_REQ,
                             dummyPktReqCB,
                             pTxMgmtQ,
                             ROLE_NONE);
#endif
    return OK;
}


/**
 * \fn     txMgmtQ_SetDefaults
 * \brief  Configure this modules default settings
 *
 * \note
 * \param  hTxMgmtQ - The module's object
 * \return NOK if failed. OK otherwise
 * \sa
 */
uint32_t txMgmtQ_SetDefaults (void)
{
    uint32_t  status;

    /* Register for the Dummy Packet Request event */
    status = txMgmtQ_configureFw();
    if (OK != status)
    {
        return NOK;
    }

    return OK;
}

uint32_t txMgmtQ_NotifyFwReset(void)
{

    return txMgmtQ_configureFw();
}

/**
 * \fn     txMgmtQ_Destroy
 * \brief  Destroy the module and its queues
 *
 * Clear and destroy the queues and then destroy the module object.
 *
 * \note
 * \param  hTxMgmtQ - The module's object
 * \return OK - Unload succesfull, NOK - Unload unsuccesfull
 * \sa
 */
uint32_t txMgmtQ_Destroy (void)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    uint32_t  eStatus = OK;
    int        uQueId;
    TMgmtLinkQ *pLinkQ;
    uint32_t  uHlid;

    if (pTxMgmtQ == NULL)
    {
        return NOK;
    }

    /* Dequeue and free all queued packets */
    txMgmtQ_ClearQueues ();

    /*
     * init all queues in all links
     */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link queues */

        for (uQueId = 0 ; uQueId < NUM_OF_MGMT_QUEUES ; uQueId++)
        {
            if (que_Destroy(pLinkQ->aQueues[uQueId]) != OK)
            {
               //Report(REPORT_SEVERITY_ERROR, "txMgmtQueue_unLoad: fail to free Mgmt Queue number: %d in link %d\r\n",uQueId, uHlid);
                eStatus = NOK;
            }
        }
    }

    /* free Tx Mgmt Queue Module */
    os_free (pTxMgmtQ);

    return eStatus;
}


/**
 * \fn     txMgmtQ_ClearQueues
 * \brief  Clear all queues
 *
 * Dequeue and free all queued packets.
 *
 * \note
 * \param  hTxMgmtQ - The object
 * \return void
 * \sa
 */
void txMgmtQ_ClearQueues ()
{
    uint32_t  uHlid;

    /*
     * flush all queues in all links
     */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        TxMgmtQ_FlushLinkQueues(uHlid);
    }
}


/**
 * \fn     txMgmtQ_Xmit
 * \brief  Insert non-data packet for transmission
 *
 * This function is used by the driver applications to send Tx packets other than the
 *   regular data traffic, including the following packet types:
*               - Management
*               - EAPOL
*               - NULL
*               - IAPP
 * The managment packets are enqueued to the Mgmt-queue and the others to the Eapol-queue.
 * EAPOL packets may be inserted from the network stack context, so it requires switching
 *   to the driver's context (after the packet is enqueued).
 * If the selected queue was empty before the packet insertion, the SM is called
 *   with QUEUES_NOT_EMPTY event (in case of external context, only after the context switch).
 *
 * \note
 * \param  hTxMgmtQ         - The module's object
 * \param  pPktCtrlBlk      - Pointer to the packet CtrlBlk
 * \param  bExternalContext - Indicates if called from non-driver context
 * \return OK - if the packet was queued, NOK - if the packet was dropped.
 * \sa     txMgmtQ_QueuesNotEmpty
 */
uint32_t txMgmtQ_Xmit(TTxCtrlBlk *pPktCtrlBlk, Bool_e bExternalContext)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    int32_t   eStatus = 0;
    uint32_t uQueId;
    uint32_t uQueSize;
    uint32_t  uHlid   = pPktCtrlBlk->tTxDescriptor.hlid;
    TMgmtLinkQ *pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link queues */
    uint8_t isDataFrame =0;

   //Report(REPORT_SEVERITY_INFORMATION, "txMgmtQ_Xmit: link %d, RoleType %d\r\n", uHlid, pTxMgmtQ->pUdata->aLinkInfo[uHlid].eRoleType);

    /* Select queue according to the packet type */
    uQueId = (pPktCtrlBlk->tTxPktParams.uPktType == TX_PKT_TYPE_MGMT) ? QUEUE_TYPE_MGMT : QUEUE_TYPE_EAPOL ;

    UDATA_PRINT("\n\rtxMgmtQ_Xmit : receive packet to send");

    /* Enter critical section to protect queue access */
    trnspt_lockTxQueue();

    /* Check resources per LINK and per MGMT AC (VOICE)*/
    if (txDataQ_AllocCheckResources(pPktCtrlBlk,isDataFrame) != OK)
    {
#ifdef ENABLE_TRAFFIC_STATITIC
        pLinkQ->tDbgCounters.aDroppedPackets[uQueId]++;
        pLinkQ->tDbgCounters.uNoResourcesCount++;
#endif
        /* Leave critical section */
        trnspt_unlockTxQueue();

        txCtrl_FreePacket (pPktCtrlBlk, NOK);
        UDATA_PRINT_ERROR("\n\rERROR txMgmtQ_Xmit ! No resource for the link, drop packet");
        return NOK;
    }

    /* Enqueue the packet in the appropriate Queue, see runScheduler */
    if((eStatus = que_Enqueue (pLinkQ->aQueues[uQueId], (void *)pPktCtrlBlk))< 0)
    {
        uQueSize = que_Size (pLinkQ->aQueues[uQueId]);
        TX_DATA_SEND_PRINT_ERROR("\n\rERROR txMgmtQ_Xmit,que_Enqueue, No room in queue uQueId:%d uHlid:%d uQueSize:%d",uQueId, uHlid,uQueSize);
    }

    /* Get number of packets in current queue */
    uQueSize = que_Size (pLinkQ->aQueues[uQueId]);

    /* Leave critical section */
    trnspt_unlockTxQueue();

    /* If packet enqueued successfully */
    if (eStatus == OK)
    {
        pLinkQ->tDbgCounters.aEnqueuePackets[uQueId]++;
        trnspt_lockTxReqSched();
        pTxMgmtQ->txMgmtReqScheduleCount++;
        trnspt_unlockTxReqSched();

        /* If selected queue was empty before packet insertion */
        if (uQueSize >= 1)
        {
            /* If called from external context (EAPOL from network), request switch to the driver's context. */
            if (bExternalContext)
            {
                UDATA_PRINT("\n\rtxMgmtQ_Xmit , replace context:%d uHlid:%d",pTxMgmtQ->uContextId, uHlid);
                /* Set bSendEvent_NotEmpty flag to use in driver context */
                pLinkQ->bSendEventNotEmpty = TRUE;
                trnspt_RequestSchedule (pTxMgmtQ->uContextId, FALSE);//function txMgmtQ_QueuesNotEmpty will be called
            }

            /* If already in the driver's context, call the SM with QUEUES_NOT_EMPTY event. */
            else
            {
                UDATA_PRINT("\n\rtxMgmtQ_Xmit ! call mgmtQueuesSM");
                mgmtQueuesSM(uHlid, SM_EVENT_QUEUES_NOT_EMPTY);
            }
        }
    }

    else
    {
        /* If the packet can't be queued so drop it */
        UDATA_PRINT_ERROR("\n\rERROR!!!txMgmtQ_Xmit ! failed to queue,uQueId:%d uQueSize:%d",uQueId,uQueSize);

        /* We failed to queue this packet, but host driver counted in it txDataQ_AllocCheckResources. 
        Hence - decrement in txDataQ_FreeFwAllocated*/
        txDataQ_FreeFwAllocated (pPktCtrlBlk); 
        txCtrl_FreePacket (pPktCtrlBlk, NOK);
#ifdef ENABLE_TRAFFIC_STATITIC
        pLinkQ->tDbgCounters.aDroppedPackets[uQueId]++;
#endif
    }

    return eStatus;
}


/**
 * \fn     txMgmtQ_QueuesNotEmpty
 * \brief  Context-Engine Callback
 *
 * Context-Engine Callback for processing queues in driver's context.
 * Called after driver's context scheduling was requested in txMgmtQ_Xmit().
 * Calls the SM with QUEUES_NOT_EMPTY event.
 *
 * \note
 * \param  hTxMgmtQ - The module's object
 * \return void
 * \sa     txMgmtQ_Xmit
 */
void txMgmtQ_QueuesNotEmpty (void* hCbHndl)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    uint32_t uHlid;

    /* Call the SM with QUEUES_NOT_EMPTY event. */
    for (uHlid=0; uHlid<WLANLINKS_MAX_LINKS; uHlid++)
    {
        TX_PRINT("\n\rtxMgmtQ_QueuesNotEmpty, loop uHlid:%d bSendEventNotEmpty:%d", uHlid,pTxMgmtQ->aMgmtLinkQ[uHlid].bSendEventNotEmpty);
        //trnspt_EnterCriticalSection ();
        /* Call every link that is not in CLOSE state */
        if (pTxMgmtQ->aMgmtLinkQ[uHlid].bSendEventNotEmpty)
        {
            /* reset bSendEvent_NotEmpty flag to use in driver context */
            pTxMgmtQ->aMgmtLinkQ[uHlid].bSendEventNotEmpty = FALSE;
			
            TX_PRINT("\n\rtxMgmtQ_QueuesNotEmpty, mgmtQueuesSM, receive mgmt TX uHlid:%d bSendEventNotEmpty:%d", uHlid,pTxMgmtQ->aMgmtLinkQ[uHlid].bSendEventNotEmpty);

            /* handle the event in the link state machine */
            mgmtQueuesSM(uHlid, SM_EVENT_QUEUES_NOT_EMPTY);
        }
    }
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
void txMgmtQ_ReqToRunTxScheduler (void)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;

    /* Run the scheduler */
    //Report("txMgmtQ_ReqToRunTxScheduler: Called\r\n");
    trnspt_RequestSchedule(pTxMgmtQ->uContextId, FALSE);
}

/**
 * \fn     txMgmtQ_UpdateBusyMap
 * \brief  Update the queues busy map
 *
 * This function is called by the txCtrl if the backpressure map per AC is changed.
 * This could be as a result of FW update, admission change or association.
 * The function modifies the internal queues Busy indication and calls the scheduler.
 *
 * \param  hTxMgmtQ          - The module's object
 * \param  pBackpressure     - the regular backpressure bitmaps                  
 * 
 * \sa     txMgmtQ_StopQueue
 */
void txMgmtQ_UpdateBusyMap(TTxHwBackpressure *pBackpressure)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    uint32_t uHlid;

    /* Go over the LinkBitMap and update the related queue busy state */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        if (IS_BIT_SET(pBackpressure->uLinkBusyBitmap, uHlid))
        {
            pTxMgmtQ->aMgmtLinkQ[uHlid].bBusy = TRUE;
        }
        else
        {
            pTxMgmtQ->aMgmtLinkQ[uHlid].bBusy = FALSE;
        }
    }

    /* Set the queues busy indication on or off according to the highest AC bit (1 = busy). */
    if (IS_BIT_SET(pBackpressure->uAcBusyBitmap, QOS_AC_VO))
    {
        pTxMgmtQ->bMgmtAcBusy = TRUE;
    }
    else
    {
        pTxMgmtQ->bMgmtAcBusy = FALSE;
    }
}

/**
 * \fn     txMgmtQ_SuspendTx
 * \brief  Stop all Tx
 *
 * \param  hTxMgmtQ   - The module's object
 */
void txMgmtQ_SuspendTx (void)
{
    txMgmtQ_StopAll();
    txDataQ_StopAll();
}

/**
 * \fn     txMgmtQ_ResumeTx
 * \brief  Resume all Tx
 *
 * \param  hTxMgmtQ   - The module's object
 */
void txMgmtQ_ResumeTx (void)
{
    txMgmtQ_WakeAll();
    txDataQ_WakeAll();//enable send data packets
}

/**
 * \fn     txMgmtQ_StopAll
 * \brief  Stop all queues transmission
 *
 * This function is called by the Tx-Port when the whole Mgmt-queue is stopped.
 * It clears the common queues enable indication.
 *
 * \note
 * \param  hTxMgmtQ   - The module's object
 * \return void
 * \sa     txMgmtQ_WakeAll
 */
void txMgmtQ_StopAll (void)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;

    /* Disable the Mgmt Tx port */
    pTxMgmtQ->bMgmtPortEnable = FALSE;
}

/**
 * \fn     txMgmtQ_WakeAll
 * \brief  Enable all queues transmission
 *
 * This function is called by the Tx-Port when the whole Mgmt-queue is enabled.
 * It sets the common queues enable indication and calls the scheduler.
 *
 * \note
 * \param  hTxMgmtQ   - The module's object
 * \return void
 * \sa     txMgmtQ_StopAll
 */
void txMgmtQ_WakeAll (void)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;

    /* Enable the Mgmt Tx port */
    pTxMgmtQ->bMgmtPortEnable = TRUE;

    /* If the queues are not empty, run the scheduler and if they become empty update the SM. */
    runSchedulerNotFromSm ();
}

/**
 * \fn     txMgmtQ_DisableLink
 * \brief  Disable all queues transmission for the link
 *
 * \param  hTxMgmtQ   - The module's object
 * \return void
 */
static void txMgmtQ_DisableLink (uint32_t uHlid)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    TMgmtLinkQ *pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid];

    pLinkQ->bEnabled = FALSE;
}

/**
 * \fn     txMgmtQ_EnableLink
 * \brief  Enable all queues transmission for the link
 *
 * \param  hTxMgmtQ   - The module's object
 * \return void
 * \sa     txMgmtQ_DisableLink
 */
static void txMgmtQ_EnableLink (uint32_t uHlid)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    TMgmtLinkQ *pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid];

    pLinkQ->bEnabled = TRUE;
}


/**
 * \fn     txMgmtQ_SetLinkState
 * \brief  set link state (enable/not)
 *
 * \note
 * \param  hTxMgmtQ     - The module's object
 * \param  uHlid        - link id
 * \param  eTxConnState - The new Tx connection state
 * \return void
 * \sa     mgmtQueuesSM
 */
void txMgmtQ_SetLinkState(uint32_t uHlid, ELinkState eTxConnState)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    TMgmtLinkQ *pLinkQ;

    pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link's queues */
    pLinkQ->eTxConnState = eTxConnState;

   //Report(REPORT_SEVERITY_INFORMATION,"txMgmtQ_SetLinkState: link %d, LinkState %d, ConnState %d\r\n", uHlid, pLinkQ->eState, pLinkQ->eTxConnState);

    /* Call the SM with the current event. */
    switch (eTxConnState)
    {
        case LINK_STATE_CLOSED: mgmtQueuesSM(uHlid, SM_EVENT_CLOSE);      break;
        case LINK_STATE_MGMT:   mgmtQueuesSM(uHlid, SM_EVENT_MGMT);       break;
        case LINK_STATE_EAPOL:  mgmtQueuesSM(uHlid, SM_EVENT_EAPOL);      break;
        case LINK_STATE_OPEN:   mgmtQueuesSM(uHlid, SM_EVENT_OPEN);       break;

        default:
            break;
           //Report(REPORT_SEVERITY_ERROR, "txMgmtQ_SetLinkState: Unknown eTxConnState = %d, for link %d\r\n", eTxConnState, uHlid);
    }
}

/**
 * \fn     txMgmtQ_GetLinkState
 * \brief  set link state
 *
 * \note
 * \param  hTxMgmtQ - Handle of the Tx Mgmt Queue module
 * \param  uHlid        - link id
 * \return Connection SM current state
 * \sa
 */

ELinkState txMgmtQ_GetLinkState(uint32_t uHlid)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    TMgmtLinkQ *pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid];

    return pLinkQ->eTxConnState;
}

/**
 * \fn     txMgmtQ_ClearLink
 * \brief  Clear link params
 *
 * \note
 * \param  hTxMgmtQ     - The module's object
 * \param  uHlid        - link id
 * \return void
 */
void txMgmtQ_ClearLink(uint32_t uHlid)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    TMgmtLinkQ *pLinkQ;

    pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link queues */

    pLinkQ->bSendEventNotEmpty = FALSE;
    pLinkQ->bBusy = FALSE;
    pLinkQ->eTxConnState = LINK_STATE_CLOSED;
    pLinkQ->eState = SM_STATE_CLOSE;
    pLinkQ->bEnabled = FALSE; /* default is not enabled */
}


/*******************************************************************************
*                       INTERNAL  FUNCTIONS  IMPLEMENTATION                    *
********************************************************************************/


/**
 * \fn     mgmtQueuesSM
 * \brief  The module state-machine (static function)
 *
 * The SM follows the system management states (see ETxConnState) and the Mgmt queues
 *   status (empty or not), and contorls the Tx queues flow accordingly (mgmt and data queues).
 * For detailed explanation, see the Tx-Path LLD document!
 *
 * \note   To avoid recursion issues, all SM actions are done at the end of the function,
 *            since some of them may invoke the SM again.
 * \param  pTxMgmtQ - The module's object
 * \param  eSmEvent - The event to act upon
 * \return void
 * \sa     txMgmtQ_SetConnState
 */
static void mgmtQueuesSM (uint32_t uHlid, ESmEvent eSmEvent)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    TMgmtLinkQ *pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link queues */
    ESmState  ePrevState = pLinkQ->eState;
    ESmAction eSmAction  = SM_ACTION_NULL;

    switch(eSmEvent)
    {
        case SM_EVENT_CLOSE:
            /*
             * Tx link is closed (expected in any state), so disable both mgmt queues
             *   and if data-queues are active disable them via txPort module.
             */
            pLinkQ->eState = SM_STATE_CLOSE;
            pLinkQ->aQenabled[QUEUE_TYPE_MGMT]  = FALSE;
            pLinkQ->aQenabled[QUEUE_TYPE_EAPOL] = FALSE;
            eSmAction = SM_ACTION_STOP_ALL;
            break;

        case SM_EVENT_MGMT:
            /*
             * Only Mgmt packets are permitted (expected from any state):
             *   - Enable the mgmt queue and disable the Eapol queue.
             *   - If data-queues are active disable them (this will run the scheduler).
             *   - Else run the scheduler (to send mgmt packets if waiting).
             */
            pLinkQ->eState = SM_STATE_MGMT;
            pLinkQ->aQenabled[QUEUE_TYPE_MGMT]  = TRUE;
            pLinkQ->aQenabled[QUEUE_TYPE_EAPOL] = FALSE;
            eSmAction = SM_ACTION_ENABLE_MGMT;
            break;

        case SM_EVENT_EAPOL:
            /*
             * EAPOL packets are also permitted, so enable the
             *   EAPOL queue and run the scheduler (to send packets from EAPOL queue if waiting).
             */
            pLinkQ->eState = SM_STATE_EAPOL;
            pLinkQ->aQenabled[QUEUE_TYPE_MGMT]  = TRUE;
            pLinkQ->aQenabled[QUEUE_TYPE_EAPOL] = TRUE;
            eSmAction = SM_ACTION_ENABLE_MGMT;
            break;

        case SM_EVENT_OPEN:
            /*
             * All packets are now permitted, so if the mgmt-queues
             *   are empty disable them and enable the data queues via txPort module.
             */
            if ( ARE_LINK_MGMT_QUEUES_EMPTY(pLinkQ->aQueues) )
            {
                pLinkQ->eState = SM_STATE_OPEN_DATA;
                pLinkQ->aQenabled[QUEUE_TYPE_MGMT]  = FALSE;
                pLinkQ->aQenabled[QUEUE_TYPE_EAPOL] = FALSE;
                eSmAction = SM_ACTION_ENABLE_DATA;
            }
            else
            {
                pLinkQ->eState = SM_STATE_OPEN_MGMT;
                pLinkQ->aQenabled[QUEUE_TYPE_MGMT]  = TRUE;
                pLinkQ->aQenabled[QUEUE_TYPE_EAPOL] = TRUE;
                eSmAction = SM_ACTION_ENABLE_MGMT;
            }
            break;

        case SM_EVENT_QUEUES_EMPTY:
            /*
             * The mgmt-queues are empty, so if in OPEN_MGMT state disable the
             *   mgmt-queues and enable the data-queues via txPort module.
             */
            if (ePrevState == SM_STATE_OPEN_MGMT)
            {
                pLinkQ->eState = SM_STATE_OPEN_DATA;
                pLinkQ->aQenabled[QUEUE_TYPE_MGMT]  = FALSE;
                pLinkQ->aQenabled[QUEUE_TYPE_EAPOL] = FALSE;
                eSmAction = SM_ACTION_ENABLE_DATA;
            }
            break;

        case SM_EVENT_QUEUES_NOT_EMPTY:

            /* A packet was inserted to the mgmt-queues */

            /* If in OPEN_DATA state, enable mgmt-queues, disable data-queues and run scheduler. */
            if (ePrevState == SM_STATE_OPEN_DATA)
            {
                pLinkQ->eState = SM_STATE_OPEN_MGMT;
                pLinkQ->aQenabled[QUEUE_TYPE_MGMT]  = TRUE;
                pLinkQ->aQenabled[QUEUE_TYPE_EAPOL] = TRUE;
                eSmAction = SM_ACTION_ENABLE_MGMT;
            }
            /* Else if not in CLOSE state, run the scheduler */
            else if (ePrevState != SM_STATE_CLOSE)
            {
                eSmAction = SM_ACTION_RUN_SCHEDULER;
            }
            break;

        default:
           //Report(REPORT_SEVERITY_ERROR, "mgmtQueuesSM: Unknown SmEvent = %d, hlid = %d\r\n", eSmEvent, uHlid);
            TX_PRINT_ERROR("\n\rError mgmtQueuesSM: Unknown SmEvent = %d, hlid = %d\r\n", eSmEvent, uHlid);
            break;
    }

    TX_PRINT("\n\r****mgmtQueuesSM(hlid=%d): <currentState = %d, event = %d> --> nextState = %d, action = %d, MgmtQueEnbl=%d, EapolQueEnbl=%d\r\n", uHlid, ePrevState, eSmEvent, pLinkQ->eState, eSmAction, pLinkQ->aQenabled[0], pLinkQ->aQenabled[1]);

    /*
     * Execute the required action.
     * Note: This is done at the end of the SM because it may start a sequence that will call the SM again!
     */
    switch (eSmAction)
    {
        case SM_ACTION_NULL:
            break;

        case SM_ACTION_ENABLE_DATA:
            TX_PRINT("\n\rmgmtQueuesSM:enable data");
            //txMgmtQ_DisableLink (uHlid);
            txDataQ_EnableLink (uHlid);
            TX_PRINT("\n\rmgmtQueuesSM:enable data done");
            break;

        case SM_ACTION_ENABLE_MGMT:
            TX_PRINT("\n\rmgmtQueuesSM:SM_ACTION_ENABLE_MGMT and runScheduler");
            //txDataQ_DisableLink (uHlid);
            txMgmtQ_EnableLink (uHlid);
            runSchedulerNotFromSm ();
            TX_PRINT("\n\rmgmtQueuesSM:SM_ACTION_ENABLE_MGMT done");
            break;

        case SM_ACTION_RUN_SCHEDULER:
            TX_PRINT("\n\rmgmtQueuesSM:runScheduler");
            runScheduler();
            TX_PRINT("\n\rmgmtQueuesSM:runScheduler doen");
            break;
        case SM_ACTION_STOP_ALL:
            TX_PRINT("\n\rSM_ACTION_STOP_ALL");
            txMgmtQ_DisableLink(uHlid);
            txDataQ_DisableLink (uHlid);
            txDataQ_FlushLinkQueues(uHlid);
            txDataQ_noticeRemoveHlid();
            TxMgmtQ_FlushLinkQueues(uHlid);
            TX_PRINT("\n\rSM_ACTION_STOP_ALL done");
        break;
        default:
            //Report(REPORT_SEVERITY_ERROR, "mgmtQueuesSM: Unknown SmAction = %d, hlid = %d\r\n", eSmAction, uHlid);
            TX_PRINT_ERROR("\n\rERROR mgmtQueuesSM: Unknown SmAction = %d, hlid = %d\r\n", eSmAction, uHlid);
            break;
    }
}


/**
 * \fn     runSchedulerNotFromSm
 * \brief  Run scheduler due to other events then from SM (static function)
 *
 * To comply with the SM behavior, this function is used for any case where the
 *    Mgmt-Queues scheduler may have work to do due to events external to the SM.
 * If the queues are not empty, this function runs the scheduler.
*               If the scheduler emptied the queues, update the SM.
 *
 * \note
 * \param  pTxMgmtQ - The module's object
 * \return void
 * \sa
 */
static void runSchedulerNotFromSm (void)
{
    TTxMgmtQ   *pTxMgmtQ = gTxMgmtQCB;
    TMgmtLinkQ *pLinkQ;
    uint32_t    uHlid;
    Bool_e      aNotEmptyLink[WLANLINKS_MAX_LINKS] = {0};
    Bool_e      bRunSched = FALSE;

    for (uHlid=0; uHlid<WLANLINKS_MAX_LINKS; uHlid++)
    {
        pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link queues */

        /* If the queues are not empty, run the scheduler. */
        if ( !ARE_LINK_MGMT_QUEUES_EMPTY(pLinkQ->aQueues) )
        {
            aNotEmptyLink[uHlid] = TRUE;
            bRunSched = TRUE;
        }
    }

    if (bRunSched)
    {
        runScheduler ();
    }

    for (uHlid=0; uHlid<WLANLINKS_MAX_LINKS; uHlid++)
    {
        pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link queues */

        if (aNotEmptyLink[uHlid] && ARE_LINK_MGMT_QUEUES_EMPTY(pLinkQ->aQueues))
        {
            /* If the queues are now both empty, call the SM with QUEUES_EMPTY event. */
            mgmtQueuesSM (uHlid, SM_EVENT_QUEUES_EMPTY);
        }
    }
}


/**
 * \fn     runScheduler
 * \brief  The scheduler processing (static function)
 *
 * Loops over the mgmt-queues (high priority first) and if queue enabled and
 *   has packets, dequeue a packet and send it to the TxCtrl.
*               Exit if the port level is disabled or if couldn't send anything from both queues.
 *
 * \note   Protect the queues access against preemption from external context (EAPOL).
 * \param  pTxMgmtQ - The module's object
 * \return void
 * \sa
 */
static void runScheduler (void)
{
    TTxMgmtQ   *pTxMgmtQ = gTxMgmtQCB;
    uint32_t    eStatus;
    TTxCtrlBlk *pPktCtrlBlk;
    uint32_t    uQueId = 0; /* start from highest priority queue */
    TMgmtLinkQ *pLinkQ;
    uint32_t    uHlid = 0;
    Bool_e      bQueueActive;
    Bool_e      bLinkActive;
    Bool_e      bLinkAcActive;
    uint8_t     uBackpressureMap = 0;
    int32_t     eQueStatus = 0;
    int32_t     scheduleCount = 0;
    int32_t     CountTxMgmtFrames = 0;


    trnspt_lockTxReqSched();
    scheduleCount = pTxMgmtQ->txMgmtReqScheduleCount;
    trnspt_unlockTxReqSched();

    while(1)
    {
        /* If the Mgmt port is closed exit. */
        if (!pTxMgmtQ->bMgmtPortEnable)
        {
            TX_PRINT("\n\rrunScheduler:bMgmtPortEnable port disable");
            return;
        }

        //the loops goes over all hlids and all queue id
        pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link queues */
        bLinkActive = (!pLinkQ->bBusy && pLinkQ->bEnabled);
        bQueueActive = pLinkQ->aQenabled[uQueId];
        bLinkAcActive = !pTxMgmtQ->bMgmtAcBusy;
        
        /* Check that the current link and current queue are not busy and are enabled */
        if (bLinkActive && bQueueActive && bLinkAcActive)
        {
            TX_PRINT("\n\rrunScheduler:send MGMT packet? bLinkActive:%d bQueueActive:%d bLinkAcActive:%d",bLinkActive,bQueueActive, bLinkAcActive);
            TX_PRINT("\n\rSend MGMT packet? uHlid:%d uQueId:%d", uHlid,uQueId);
            /* Dequeue a packet in a critical section */
            trnspt_lockTxQueue();
            pPktCtrlBlk = (TTxCtrlBlk *) que_Dequeue (pLinkQ->aQueues[uQueId]);
            trnspt_unlockTxQueue();

            if (pPktCtrlBlk)
            {
                TX_PRINT("\n\rrunScheduler:send MGMT packet");
                trnspt_lockTxReqSched();
                CountTxMgmtFrames++;
                trnspt_unlockTxReqSched();

#ifdef ENABLE_TRAFFIC_STATITIC
                pLinkQ->tDbgCounters.aDequeuePackets[uQueId]++;
#endif
                /* Send the packet */
                eStatus = txCtrl_XmitMgmt(pPktCtrlBlk, &uBackpressureMap);

                /* Update current AC and Link busy state (change may only be from not busy to busy) */
                if (uBackpressureMap & TX_HW_CURRENT_AC_STOP)
                {
                    pTxMgmtQ->bMgmtAcBusy = TRUE;
                }
                if (uBackpressureMap & TX_HW_CURRENT_LINK_STOP)
                {
                    pLinkQ->bBusy = TRUE;
                }

                /* In case the return status is busy it means that the packet wasn't handled
                     so we need to requeue the packet for future try. */
                if(eStatus == STATUS_XMIT_BUSY)
                {
                    eQueStatus = NOK;
                    TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rMgmt frame: re-queue\r\n");
                    /* Requeue the packet in a critical section */
                   //trnspt_lockTxQueue();
                   //eQueStatus = que_Requeue (pLinkQ->aQueues[uQueId], (void *)pPktCtrlBlk);
                   //trnspt_unlockTxQueue();


                    if (eQueStatus == OK)
                    {
                        pLinkQ->tDbgCounters.aRequeuePackets[uQueId]++;
                        pLinkQ->bSendEventNotEmpty = TRUE;
                        trnspt_RequestSchedule (pTxMgmtQ->uContextId, FALSE);//function txMgmtQ_QueuesNotEmpty will be called
                    }
                    else
                    {
                        TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rERROR!mgmt frame: dropped\r\n");
                        txCtrl_FreePacket(pPktCtrlBlk, NOK);
                    }

                }

                /* The packet was handled by the lower Tx layers. */
                else //(eQueStatus == OK)
                {
                    pLinkQ->tDbgCounters.aXmittedPackets[uQueId]++;
                    TX_FRAME_FLOW_CNTRL_PRINT("\n\rMgmt frame: success,CountTxMgmtFrames:%d\r\n",CountTxMgmtFrames);

                    /* Successful delivery so start next tx from the high priority queue (mgmt),
                     *   giving it strict priority over the lower queue.
                     */
                    continue;//finish to send all the queue
                }
            }
        }

        /* If we got here we couldn't deliver a packet from current queue, so progress to lower
         *   priority queue and if already in lowest queue exit.
         */
        if (bLinkActive) /* Continue to next queue only if the link is active */
        {
            uQueId++;
            if (uQueId < NUM_OF_MGMT_QUEUES)
            {
                continue;   /* Try sending from next queue (i.e. the EAPOL queue). */
            }
        }

        /*
         * continue to next link
         */
        uHlid++;
        if (uHlid < WLANLINKS_MAX_LINKS)
        {
            uQueId = 0;
            continue;
        }
        else
        {
            /* We couldn't send from both queues so indicate end of packets and exit. */

            trnspt_lockTxReqSched();
            pTxMgmtQ->txMgmtReqScheduleCount-=CountTxMgmtFrames;
            if( pTxMgmtQ->txMgmtReqScheduleCount < 0)
            {
                //this doesn't suppose to happen, just in case
                pTxMgmtQ->txMgmtReqScheduleCount =0;
            }
            trnspt_unlockTxReqSched();

            return;
        }

    } /* End of while */
    /* Unreachable code */
}


/**
 * \fn     TxMgmtQ_FlushLinkQueues
 * \brief  Flush management queues the specific link
 *
 * * \note
 * \param  hTxMgmtQ   - The module's object
 * \param  uHlid - link id
 * \return void
 * \sa
 */
void TxMgmtQ_FlushLinkQueues(uint32_t uHlid)
{
    TTxMgmtQ   *pTxMgmtQ = gTxMgmtQCB;
    TTxCtrlBlk *pPktCtrlBlk;
    uint32_t  uQueId;
    TMgmtLinkQ *pLinkQ;

    pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link queues */

    /* Dequeue and free all queued packets */
    for (uQueId = 0 ; uQueId < NUM_OF_MGMT_QUEUES ; uQueId++)
    {
        while (1)
        {
            trnspt_lockTxQueue();
            pPktCtrlBlk = (TTxCtrlBlk *) que_Dequeue (pLinkQ->aQueues[uQueId]);
            trnspt_unlockTxQueue();
            if (pPktCtrlBlk == NULL)
            {
                break;
            }
            trnspt_lockTxReqSched();
            pTxMgmtQ->txMgmtReqScheduleCount--;
            if( pTxMgmtQ->txMgmtReqScheduleCount < 0)
            {
                //this doesn't suppose to happen, just in case
                pTxMgmtQ->txMgmtReqScheduleCount =0;
            }
            trnspt_unlockTxReqSched();

            txHwQueue_free_allocated_mem_blocks(pPktCtrlBlk);
            TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rTxMgmtQ_FlushLinkQueues descID:%d\r\n", pPktCtrlBlk->tTxDescriptor.descID);
            txCtrl_FreePacket (pPktCtrlBlk, NOK);
        }
    }
}

/****************************************************************************************
 *                               dummyPktReqCB                                          *
 ****************************************************************************************
DESCRIPTION: Callback for the TWD_OWN_EVENT_DUMMY_PKT_REQ event - transmits a dummy packet

INPUT:      - hTxMgmtQ      - Handle to the TxMgmtQ module
            - str           - Buffer containing the event data (not relevant here)
            - strLen        - Event data length
OUTPUT:
RETURN:    void.\n
****************************************************************************************/
void dummyPktReqCB(char *str , uint32_t strLen, uint32_t uEventId)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    TMgmtPktDesc    *pkt;
    TMacAddr        daBssid;
    uint16_t       fc;
    uint32_t       uHlid = pTxMgmtQ->pUdata->uSystemHlid,total_len,extra;
    TUdataLinkInfo  *pLinkInfo = &(pTxMgmtQ->pUdata->aLinkInfo[uHlid]);
    RoleType_e   eRoleType = pLinkInfo->eRoleType;
    dot11_mgmtHeader_t *pDot11Header;

   //Report(REPORT_SEVERITY_INFORMATION, "dummyPktReqCB: Called\r\n");
    /* allocate descriptor and payload */
    extra = IEEE80211_HT_CTL_LEN; // Add 4 bytes gap, may be filled later on by the PMAC
    total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + sizeof(dot11_mgmtHeader_t) + extra + DUMMY_PKT_BUF_LEN;

    pkt = udata_AllocTxMgmtPacket(sizeof(dot11_mgmtHeader_t) + extra,DUMMY_PKT_BUF_LEN ,NULL);
    if (!pkt)
    {
       //Report(REPORT_SEVERITY_ERROR, "dummyPktReqCB: TMgmtPktDesc allocation failed!\r\n");
        return;
    }
    set_nab_tx_header(pkt->nabHeader, total_len );

    pTxMgmtQ->uDummyPackets++;

    /* prepare descriptor */
    pkt->link = uHlid;
    pkt->ePktType = UDATA_TX_PKT_TYPE_DUMMY;

    /* prepare WLAN header */

    pDot11Header = (dot11_mgmtHeader_t *)pkt->header;

    fc = DOT11_FC_DATA_NULL_FUNCTION | DOT11_FC_TO_DS;
    pDot11Header->fc = fc;//COPY_WLAN_WORD(&pDot11Header->fc, &fc);

    txDataQ_GetMacFromLink(pkt->link, daBssid);
    MAC_COPY(pDot11Header->DA, daBssid);                      
    MAC_COPY(pDot11Header->SA, pTxMgmtQ->pUdata->aRoleLocalMac[pLinkInfo->eFwRoleId]); 
    if (IS_ROLE_TYPE_AP_OR_P2PGO(eRoleType))
    {
        MAC_COPY(pDot11Header->BSSID, pTxMgmtQ->pUdata->aRoleLocalMac[pLinkInfo->eFwRoleId]);
    }
    else
    {
        MAC_COPY(pDot11Header->BSSID, daBssid);
    }

    /* submit for tx */
    if (udata_SendTxMgmtPacket(pkt) != OK)
    {
       //Report(REPORT_SEVERITY_ERROR, "dummyPktReqCB: xmit failed!\r\n");
    }
}


/*******************************************************************************
*                       DEBUG  FUNCTIONS  IMPLEMENTATION                       *
********************************************************************************/

#ifdef TI_DBG

/**
 * \fn     txMgmtQ_PrintModuleParams
 * \brief  Print module's parameters (debug)
 *
 * This function prints the module's parameters.
 *
 * \note
 * \param  hTxMgmtQ - The module's object
 * \return void
 * \sa
 */
void txMgmtQ_PrintModuleParams (void)
{
#ifdef REPORT_LOG
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    uint32_t uQueId;
    TMgmtLinkQ *pLinkQ;
    uint32_t  uHlid;

   //Report(("-------------- txMgmtQueue Module Params -----------------\r\n"));
   //Report(("==========================================================\r\n"));
   //GTRACE(1, "bMgmtPortEnable = %d\r\n", pTxMgmtQ->bMgmtPortEnable));
   //GTRACE(1, "uContextId      = %d\r\n", pTxMgmtQ->uContextId));
   //GTRACE(1, "bMgmtAcBusy                = %d\r\n", pTxMgmtQ->bMgmtAcBusy));
    
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link queues */

       //GTRACE(1, "Link %3d--------------------------------------------------\r\n", uHlid));
       //GTRACE(1, "  eState=%01d, bEnabled=%1d, bBusy=%1d\r\n", pLinkQ->eState, pLinkQ->bEnabled, pLinkQ->bBusy));
        if (pLinkQ->eState == SM_STATE_CLOSE)
            continue;
       //GTRACE(1, "  bSendEventNotEmpty = %d\r\n", pLinkQ->bSendEventNotEmpty));
       //GTRACE(1, "  eTxConnState        = %d\r\n", pLinkQ->eTxConnState));
       //GTRACE(1, "  aQenabled %2d %2d\r\n", pLinkQ->aQenabled[0], pLinkQ->aQenabled[1]));

        for(uQueId = 0; uQueId < NUM_OF_MGMT_QUEUES; uQueId++)
        {
           //GTRACE(1, "  Que %d: ", uQueId));
            que_Print (pLinkQ->aQueues[uQueId]);
        }
    }

   //Report(("==========================================================\n\r\n"));
#endif
}


/**
 * \fn     txMgmtQ_PrintQueueStatistics
 * \brief  Print queues statistics (debug)
 *
 * This function prints the module's Tx statistics per Queue.
 *
 * \note
 * \param  hTxMgmtQ - The module's object
 * \return void
 * \sa
 */
void txMgmtQ_PrintQueueStatistics (void)
{
#ifdef REPORT_LOG
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    TMgmtLinkQ *pLinkQ;
    uint32_t  uHlid;

   //Report(("-------------- Mgmt Queues Statistics  -------------------\r\n"));
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link queues */
       //GTRACE(1, "Link %3d--------------------------------------------------\r\n", uHlid));
       //GTRACE(1, "  eState=%01d, bEnabled=%1d, bBusy=%1d\r\n", pLinkQ->eState, pLinkQ->bEnabled, pLinkQ->bBusy));
        if (pLinkQ->eState == SM_STATE_CLOSE)
            continue;

       //GTRACE(1, "  aEnqueuePackets: %8d %8d\r\n", pLinkQ->tDbgCounters.aEnqueuePackets[0], pLinkQ->tDbgCounters.aEnqueuePackets[1] ));
       //GTRACE(1, "  aDequeuePackets: %8d %8d\r\n", pLinkQ->tDbgCounters.aDequeuePackets[0], pLinkQ->tDbgCounters.aDequeuePackets[1] ));
       //GTRACE(1, "  aRequeuePackets: %8d %8d\r\n", pLinkQ->tDbgCounters.aRequeuePackets[0], pLinkQ->tDbgCounters.aRequeuePackets[1] ));
       //GTRACE(1, "  aXmittedPackets: %8d %8d\r\n", pLinkQ->tDbgCounters.aXmittedPackets[0], pLinkQ->tDbgCounters.aXmittedPackets[1] ));
       //GTRACE(1, "  aDroppedPackets: %8d %8d\r\n", pLinkQ->tDbgCounters.aDroppedPackets[0], pLinkQ->tDbgCounters.aDroppedPackets[1] ));
       //GTRACE(1, "  uNoResourcesCount(before enqueue) = %d \r\n", pLinkQ->tDbgCounters.uNoResourcesCount));
    }

   //Report (("\"Dummy Blocks\" packets generated: %d\r\n", pTxMgmtQ->uDummyPackets));
#endif
}


/**
 * \fn     txMgmtQ_ResetQueueStatistics
 * \brief  Reset queues statistics (debug)
 *
 * This function Resets the module's Tx statistics per Queue.
 *
 * \note
 * \param  hTxMgmtQ - The module's object
 * \return void
 * \sa
 */
void txMgmtQ_ResetQueueStatistics (void)
{
    TTxMgmtQ *pTxMgmtQ = gTxMgmtQCB;
    TMgmtLinkQ *pLinkQ;
    uint32_t  uHlid;

    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
            pLinkQ = &pTxMgmtQ->aMgmtLinkQ[uHlid]; /* Link queues */
            os_memset((void *)&(pLinkQ->tDbgCounters), 0, sizeof(TDbgCount));
    }
}


#endif /* TI_DBG */

