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
/****************************************************************************
 *
 *   MODULE:  rxXfer.c
 *
 *   PURPOSE: Rx Xfer module implementation.Responsible for reading Rx from the FW
 *              and forward it to the upper layers.
 * 
 ****************************************************************************/

#define __FILE_ID__  FILE_ID_76
#if 0
#include "public_types.h"
#endif

#include "osi_kernel.h"
#include "trnspt_thread.h"
#ifdef CC33xx
#include "public_share.h"
#else
#include "wl18xx_public_infoele.h"
#include "init_wl18xx.h"
#endif
#include "bus_if.h"
//#include "wl18xx_public_host_int.h"
#include "fw_event_handle.h"

//#include "wl18xx_register.h"
#include "TwIf.h"
#include "commands.h"

#include "TWDriver.h"
#include "rxXfer_api.h"
#include "txn_defs.h"

#if 0
#define PLCP_HEADER_LENGTH 8
#define WORD_SIZE   4
#define UNALIGNED_PAYLOAD   0x1
#define RX_DESCRIPTOR_SIZE          (sizeof(RxIfDescriptor_t))
#define MAX_PACKETS_NUMBER          8
#define MAX_CONSECUTIVE_READ_TXN    16
#define MAX_PACKET_SIZE             16384    /* Max Txn size */
#define MAX_CONSECUTIVE_READS       8

#define ALIGNMENT_SIZE(desc)            ((RX_DESC_GET_UNALIGNED(desc) & UNALIGNED_PAYLOAD) ? 2 : 0)

#if (NUM_RX_PKT_DESC & (NUM_RX_PKT_DESC - 1))
    #error  NUM_RX_PKT_DESC is not a power of 2 which may degrade performance when we calculate modulo!!
#endif


#ifdef DBG_Report

/* 
 * Debug trace
 * -----------
 */
#define DBG_TBL_SIZE        256
typedef struct 
{
    uint32_t       uEvent;
    uint32_t       uData1;
    uint32_t       uData2;
} TTraceEntry;  
static TTraceEntry aDbgTrace[DBG_TBL_SIZE];
static uint32_t aDbgIndex;
#define ADD_DBG_Report(a_uEvent, a_uData1, a_uData2) do { \
        aDbgTrace[aDbgIndex].uEvent = (uint32_t)(a_uEvent); \
        aDbgTrace[aDbgIndex].uData1 = (uint32_t)(a_uData1); \
        aDbgTrace[aDbgIndex].uData2 = (uint32_t)(a_uData2); \
        aDbgIndex = (aDbgIndex+1)%DBG_TBL_SIZE; \
    } while (0)

#else  /* DBG_TRACE */

#define ADD_DBG_Report(a_uEvent, a_uData1, a_uData2)

#endif


#ifdef TI_DBG
typedef struct 
{
    uint32_t           uCountFwEvents; 
    uint32_t           uCountPktsForward; 
    uint32_t           uCountBufPend; 
    uint32_t           uCountBufNoMem; 
    uint32_t           uCountPktAggreg[MAX_XFER_BUFS]; 

} TRxXferDbgStat;
#endif

typedef struct 
{   
    uint32_t            aRxPktsDesc[NUM_RX_PKT_DESC];               /* Save Rx packets short descriptors from FwStatus */
    uint32_t            uFwRxCntr;                                  /* Save last FW packets counter from FwStatus */
    uint32_t            uDrvRxCntr;                                 /* The current driver processed packets counter */
    uint32_t            uPacketMemoryPoolStart;                     /* The FW mem-blocks area base address */
    uint32_t            uMaxAggregLen;                              /* The max length in bytes of aggregated packets transaction */
    uint32_t            uMaxAggregPkts;                             /* The max number of packets that may be aggregated in one transaction */
    TRequestForBufferCb RequestForBufferCB;                         /* Upper layer CB for allocating buffers for packets */
    void               *RequestForBufferCB_handle;                  /* The upper layer CB handle (for allocating buffers for packets) */
    TPacketReceiveCb    ReceivePacketCB;                            /* Upper layer CB for passing rx packets */
    void               *ReceivePacketCB_handle;                     /* The upper layer CB handle */
    //TFwLogPacketReceiveCb ReceiveFwLoggerPacketContinuousCB;          /* Upper layer CB for passing FwLogger packets */ 
    //void*             ReceiveFwLoggerPacketContinuousCB_handle;   /* The upper layer CB FwLogger handle */             
    Bool_e              bPendingBuffer;                             /* If TRUE, we exited the Rx handler upon pending-buffer */
        
    uint32_t            uCurrTxnIndex;                              /* The current Txn structures index to use */
    uint32_t            uAvailableTxn;                              /* Number of Txn structures currently available */
    TTxnStruct          aTxnStruct[MAX_CONSECUTIVE_READ_TXN];       /* Txn structures for reading the Rx packets */

    uint8_t             aTempBuffer[MAX_PACKET_SIZE];               /* Dummy buffer to use if we couldn't get a buffer for the packet (so drop the packet) */
    TFailureEventCb     fErrCb;                                     /* The upper layer CB function for error handling */
    void*               hErrCb;                                     /* The CB function handle */
    uint32_t            uSdioBlkSizeShift;                          /* In block-mode:  uBlkSize = (1 << uBlkSizeShift)   */
    uint32_t            uHostIfCfgBitmap;                           /* Host interface configuration bitmap */

} TRxXfer;

TRxXfer *gRxXferCB = NULL;

/************************ static function declaration *****************************/
static uint8_t      rxXfer_Handle(void);
static void         rxXfer_TxnDoneCb (TTxnStruct* pTxn);
static void         rxXfer_PktDropTxnDoneCb (TTxnStruct *pTxn);
static ETxnStatus   rxXfer_IssueTxn (uint32_t uRxDesc);
static void         rxXfer_ForwardPacket (TRxXfer* pRxXfer, TTxnStruct* pTxn, uint8_t *extraBytesArray);

/****************************************************************************
 *                      RxXfer_Create()
 ****************************************************************************
 * DESCRIPTION: Create the RxXfer module object 
 * 
 * INPUTS:  None
 * 
 * OUTPUT:  None
 * 
 * RETURNS: The Created object
 ****************************************************************************/
TRxXfer * rxXfer_Create(void)
{
    gRxXferCB = os_zalloc (sizeof(TRxXfer));
    if (gRxXferCB == NULL)
    {
        return NULL;
    }

    return gRxXferCB;
}


/****************************************************************************
 *                      RxXfer_Destroy()
 ****************************************************************************
 * DESCRIPTION: Destroy the RxXfer module object 
 * 
 * INPUTS:  hRxXfer - The object to free
 * 
 * OUTPUT:  None
 * 
 * RETURNS: 
 ****************************************************************************/
void rxXfer_Destroy (void)
{
    TRxXfer *pRxXfer = gRxXferCB;

    if (pRxXfer)
    {
        os_free (pRxXfer);
    }
}


/****************************************************************************
 *                      rxXfer_init()
 ****************************************************************************
 * DESCRIPTION: Init the module object 
 * 
 * INPUTS:      hRxXfer - module handle;
 *              other modules handles.
 * 
 * OUTPUT:  None
 * 
 * RETURNS: None
 ****************************************************************************/
uint32_t rxXfer_Init(void)
{
    TRxXfer *pRxXfer = rxXfer_Create();
    if (pRxXfer == NULL)
    {
        return NOK;
    }

    rxXfer_Restart();

#ifdef TI_DBG   
    rxXfer_ClearStats (pRxXfer);
#endif
    return OK;
}

/****************************************************************************
 *                      rxXfer_SetDefaults()
 ****************************************************************************
 * DESCRIPTION: Set module parameters default setting
 * 
 * INPUTS:      hRxXfer - module handle;
 * 
 * OUTPUT:  None
 * 
 * RETURNS: None
 ****************************************************************************/
// TODO: set defaults params
void rxXfer_SetDefaults(void)
{
    TRxXfer *pRxXfer = gRxXferCB;

    pRxXfer->uMaxAggregPkts    = TWD_RX_AGGREG_PKTS_LIMIT_DEF;//pInitParams->tGeneral.uRxAggregPktsLimit;
    pRxXfer->uHostIfCfgBitmap  = TWD_HOST_IF_CFG_BITMAP_DEF;//pInitParams->tGeneral.uHostIfCfgBitmap;
    pRxXfer->uSdioBlkSizeShift = SDIO_BLK_SIZE_SHIFT_DEF;//pInitParams->tGeneral.uSdioBlkSizeShift;
}


/****************************************************************************
 *                      rxXfer_SetBusParams()
 ****************************************************************************
 * DESCRIPTION: Configure bus driver DMA-able buffer length to be used as a limit to the aggragation length.
 * 
 * INPUTS:      hRxXfer    - module handle
 *              uDmaBufLen - The bus driver DMA-able buffer length
 * 
 * OUTPUT:  None
 * 
 * RETURNS: None
 ****************************************************************************/
void rxXfer_SetBusParams (uint32_t uDmaBufLen)
{
    TRxXfer *pRxXfer = gRxXferCB;

    pRxXfer->uMaxAggregLen = uDmaBufLen;
}


/****************************************************************************
 *                      rxXfer_Register_CB()
 ****************************************************************************
 * DESCRIPTION: Register the function to be called for request for buffer.
 * 
 * INPUTS:      hRxXfer       - RxXfer handle;
 * 
 * OUTPUT:  None
 * 
 * RETURNS: None
 ****************************************************************************/
void rxXfer_Register_CB (uint32_t CallBackID, void *CBFunc, void *CBObj)
{
    TRxXfer *pRxXfer = gRxXferCB;

    //Report(REPORT_SEVERITY_INFORMATION , "rxXfer_Register_CB (Value = 0x%x)\r\n", CallBackID);

    switch(CallBackID)
    {
        case TWD_INT_REQUEST_FOR_BUFFER:
            pRxXfer->RequestForBufferCB = (TRequestForBufferCb)CBFunc;
            pRxXfer->RequestForBufferCB_handle = CBObj;
            break;

        case TWD_INT_RECEIVE_PACKET:
            pRxXfer->ReceivePacketCB = (TPacketReceiveCb)CBFunc;
            pRxXfer->ReceivePacketCB_handle = CBObj;
            break;
#if 0
        case TWD_INT_RECEIVE_FWLOGGER_PACKET: 
            pRxXfer->ReceiveFwLoggerPacketContinuousCB = (TFwLogPacketReceiveCb)CBFunc;
            pRxXfer->ReceiveFwLoggerPacketContinuousCB_handle = CBObj;
            break;
#endif
        default:
           //Report(pRxXfer->hReport, REPORT_SEVERITY_ERROR, "rxXfer_Register_CB - Illegal value\r\n");
            return;
    }
}

/****************************************************************************
 *                      rxXfer_ForwardPacket()
 ****************************************************************************
 * DESCRIPTION:  Forward received packet(s) to the upper layers.
 *
 * INPUTS:      
 * 
 * OUTPUT:      
 * 
 * RETURNS:     
 ****************************************************************************/
#ifdef DEBUG_GPIO
extern void debug_gpio_set_dataout(void);
#endif    
static void rxXfer_ForwardPacket (TRxXfer *pRxXfer, TTxnStruct *pTxn, uint8_t *extraBytesArray)
{
    uint32_t uBufNum;
    RxIfDescriptor_t *pRxInfo;
#ifdef TI_DBG   /* for packet sanity check */
    uint16_t        uLenFromRxInfo;
#endif

    /* Go over all occupied Txn buffers and forward their Rx packets upward */
    for (uBufNum = 0; uBufNum < MAX_XFER_BUFS; uBufNum++) 
    {
        /* If no more buffers, exit the loop */
        if (pTxn->aLen[uBufNum] == 0 || pTxn->aBuf[uBufNum] == NULL)
        {
            break;
        }
        /* Get length from RxInfo, handle endianess and convert to length in bytes */
        pRxInfo = (RxIfDescriptor_t*)(pTxn->aBuf[uBufNum]);
#ifdef TI_DBG   /* Packet sanity check */

        uLenFromRxInfo = pRxInfo->length;//ENDIAN_HANDLE_WORD(pRxInfo->length);

        ADD_DBG_Report(50, 999, uLenFromRxInfo);

        /* Alignment of WLAN packets to SDIO blocks by padding packets & reducing SDIO block size */
        if (pRxXfer->uHostIfCfgBitmap & HOST_IF_CFG_BITMAP_RX_PAD_TO_SDIO_BLK)
        {
            uint32_t uBlockMask = ((1 << pRxXfer->uSdioBlkSizeShift) - 1);
            /* Add extra bytes of padding for alignment to SDIO blocks if needed */
            uLenFromRxInfo = (uLenFromRxInfo + uBlockMask) & (~uBlockMask);
        }

        /* If the length in the RxInfo is different than in the short descriptor, set error status */
        if (pTxn->aLen[uBufNum] != uLenFromRxInfo) 
        {
            ADD_DBG_Report(55, pTxn->aLen[uBufNum], uLenFromRxInfo);
           //Report(pRxXfer->hReport, REPORT_SEVERITY_ERROR , "rxXfer_ForwardPacket: Bad Length!! RxInfoLength=%d, ShortDescLen=%d, RxInfoStatus=0x%x, Len0=%d, Len1=%d, Len2=%d, Len3=%d, Len4=%d\r\n", uLenFromRxInfo, pTxn->aLen[uBufNum], pRxInfo->status, pTxn->aLen[0], pTxn->aLen[1], pTxn->aLen[2], pTxn->aLen[3], pTxn->aLen[4]);
#ifdef DEBUG_GPIO
            debug_gpio_set_dataout();
#endif    
            report_PrintDump(pTxn->aBuf[0], 128 /*pTxn->aLen[0]*/);
    
            pRxInfo->status &= ~RX_DESC_STATUS_MASK;
            pRxInfo->status |= RX_DESC_STATUS_DRIVER_RX_Q_FAIL;
            pRxInfo->length = (pTxn->aLen[uBufNum] >> 2);//ENDIAN_HANDLE_WORD(pTxn->aLen[uBufNum] >> 2);

            /* If error CB available, trigger recovery !! */
            if (pRxXfer->fErrCb)
            {
                pRxXfer->fErrCb (pRxXfer->hErrCb, RX_XFER_FAILURE);
            }
        }
        else 
        {
           //Report(pRxXfer->hReport, REPORT_SEVERITY_INFORMATION , "rxXfer_ForwardPacket: RxInfoLength=%d, RxInfoStatus=0x%x\r\n", uLenFromRxInfo, pRxInfo->status);
            if (extraBytesArray)
            {
                pRxInfo->extraBytes = extraBytesArray[uBufNum];
            }
        }
        pRxXfer->tDbgStat.uCountPktsForward++;
#endif

        /* This is the last packet in the Burst so mark its EndOfBurst flag */
        if (TXN_PARAM_GET_END_OF_BURST(pTxn) && (uBufNum == (MAX_XFER_BUFS - 1) || pTxn->aLen[uBufNum + 1] == 0))
        {
            TXN_PARAM_SET_END_OF_BURST(pTxn, 0);
            pRxInfo->driverFlags |= DRV_RX_FLAG_END_OF_BURST;
        }
        if (TAG_CLASS_LOGGER == pRxInfo->packet_class_tag)   
        {
            /* Forward the FwLogger packet to upper layer */
#if 0 // TODO: needed?
            pRxXfer->ReceiveFwLoggerPacketContinuousCB(pRxXfer->ReceiveFwLoggerPacketContinuousCB_handle, 
                                (const void *)pTxn->aBuf[uBufNum], MEM_BLOCK_SIZE, FWLOG_CONTINUES, FALSE);
#endif
        }
        else /* Forward received packet to the upper layers */
        {
            pRxXfer->ReceivePacketCB((const void *)pTxn->aBuf[uBufNum]);
        }
    }

    /* reset the aBuf field for clean on recovery purpose */
    pTxn->aBuf[0] = 0;
    pTxn->aLen[0] = 0;

}


/****************************************************************************
 *                      rxXfer_RxEvent()
 ****************************************************************************
 * DESCRIPTION: Called upon Rx event from the FW.calls the SM  
 * 
 * INPUTS:      hRxXfer       - RxXfer handle;
 * 
 * OUTPUT:  None
 * 
 * RETURNS: TWIF_OK in case of Synch mode, or TWIF_PENDING in case of Asynch mode
 *          (when returning TWIF_PENDING, FwEvent module expects the FwEvent_EventComplete()
 *          function call to finish the Rx Client handling 
 *
 ****************************************************************************/
ETxnStatus rxXfer_RxEvent (void *FwStatus)
{
    TRxXfer        *pRxXfer = gRxXferCB;
    FwStatus_t     *pFwStatus = (FwStatus_t*)FwStatus;
    uint32_t        uTempCounters;
    FwStatCntrs_t  *pFwStatusCounters;
    uint32_t        i;
  
    uTempCounters = pFwStatus->counters;//ENDIAN_HANDLE_LONG (pFwStatus->counters);
    pFwStatusCounters = (FwStatCntrs_t*)(&uTempCounters);

    ADD_DBG_Report(10, ((uint32_t)pFwStatusCounters->fwRxCntr), pRxXfer->uFwRxCntr);

    //Report(pRxXfer->hReport, REPORT_SEVERITY_INFORMATION , "rxXfer_RxEvent: NewFwCntr=%d, OldFwCntr=%d\r\n", pFwStatusCounters->fwRxCntr, pRxXfer->uFwRxCntr);

    /* If no new Rx packets - exit */
    if ((pFwStatusCounters->fwRxCntr % NUM_RX_PKT_DESC) == (pRxXfer->uFwRxCntr % NUM_RX_PKT_DESC))
    {
        return TXN_STATUS_COMPLETE;
    }

#ifdef TI_DBG
    pRxXfer->tDbgStat.uCountFwEvents++;
#endif

    /* Save current FW counter and Rx packets short descriptors for processing */
    pRxXfer->uFwRxCntr = pFwStatusCounters->fwRxCntr;
    for (i = 0; i < NUM_RX_PKT_DESC; i++)
    {
        pRxXfer->aRxPktsDesc[i] = pFwStatus->rxPktsDesc[i];//ENDIAN_HANDLE_LONG (pFwStatus->rxPktsDesc[i]); 
    }

    /* Handle all new Rx packets */
    rxXfer_Handle ();

    return TXN_STATUS_COMPLETE;
}


/****************************************************************************
 *                      rxXfer_Handle()
 ****************************************************************************
 * DESCRIPTION: 
 *
 * INPUTS:      hRxXfer       - RxXfer handle;
 * 
 * OUTPUT:      
 * 
 * RETURNS:     
 ****************************************************************************/
static uint8_t rxXfer_Handle()
{
#ifndef _VLCT_
    TRxXfer *        pRxXfer          = gRxXferCB;
    Bool_e           bIssueTxn        = FALSE; /* If TRUE transact current aggregated packets */
    Bool_e           bDropLastPkt     = FALSE; /* If TRUE, need to drop last packet (RX_BUF_ALLOC_OUT_OF_MEM) */
    Bool_e           bExit            = FALSE; /* If TRUE, can't process further packets so exit (after serving the other flags) */
    uint32_t         uAggregPktsNum   = 0;        /* Number of aggregated packets */
    uint32_t         uRxDesc          = 0;
    uint32_t         uBuffSize        = 0;
    uint32_t         uTotalAggregLen  = 0;
    uint32_t         uDrvIndex;
    uint32_t         uFwIndex;
    uint8_t *        pHostBuf;
    TTxnStruct *     pTxn = NULL;
    ETxnStatus       eTxnStatus;
    ERxBufferStatus  eBufStatus;
    PacketClassTag_e eRxPacketType;
    uint32_t         uBlockMask;
    uint8_t          aExtraBytesArray[MAX_XFER_BUFS];



    /* If no Txn structures available exit!! (fatal error - not expected to happen) */
    if (pRxXfer->uAvailableTxn == 0 )
    {
        //Report(pRxXfer->hReport, REPORT_SEVERITY_ERROR, "rxXfer_Handle: No available Txn structures left!\r\n");
        return NOK;
    }

    uFwIndex = pRxXfer->uFwRxCntr % NUM_RX_PKT_DESC;

    /* Loop while Rx packets can be transfered from the FW */
    while (1)
    {
        uDrvIndex = pRxXfer->uDrvRxCntr % NUM_RX_PKT_DESC;
        
        /* If there are unprocessed Rx packets */
        if (uDrvIndex != uFwIndex)
        {
            /* Get next packet info */
            uRxDesc       = pRxXfer->aRxPktsDesc[uDrvIndex];
            ADD_DBG_Report(20, uDrvIndex, uRxDesc);
            uBuffSize     = RX_DESC_GET_LENGTH(uRxDesc);
            eRxPacketType = (PacketClassTag_e)RX_DESC_GET_PACKET_CLASS_TAG (uRxDesc);
            aExtraBytesArray[uAggregPktsNum] = ALIGNMENT_SIZE(uRxDesc);

            /* Alignment of WLAN packets to SDIO blocks by padding packets & reducing SDIO block size */
            uBlockMask = ((1 << pRxXfer->uSdioBlkSizeShift) - 1);
            if (pRxXfer->uHostIfCfgBitmap & HOST_IF_CFG_BITMAP_RX_PAD_TO_SDIO_BLK)
            {
                /* Add extra bytes of padding for alignment to SDIO blocks if needed */
                uBuffSize = (uBuffSize + uBlockMask) & (~uBlockMask); 
            }

            /* If new packet exceeds max aggregation length, set flag to send previous packets (postpone it to next loop) */
            if ((uTotalAggregLen + uBuffSize) > pRxXfer->uMaxAggregLen)
            {
                bIssueTxn = TRUE;
            }
            /* No length limit so try to aggregate new packet */
            else
            {
                /* Allocate host read buffer */
                /* The RxBufAlloc() add an extra word for MAC header alignment in case of QoS MSDU */

                eBufStatus = pRxXfer->RequestForBufferCB((void**)&pHostBuf,
                                                         uBuffSize,
                                                         (uint32_t)NULL,
                                                         eRxPacketType);


                //Report(pRxXfer->hReport, REPORT_SEVERITY_INFORMATION , "rxXfer_Handle: Index=%d, RxDesc=0x%x, DrvCntr=%d, FwCntr=%d, BufStatus=%d, BuffSize=%d\r\n", uDrvIndex, uRxDesc, pRxXfer->uDrvRxCntr, pRxXfer->uFwRxCntr, eBufStatus, uBuffSize);

                /* If buffer allocated, add it to current Txn (up to 4 packets aggregation) */
                if (eBufStatus == RX_BUF_ALLOC_COMPLETE)
                {
                    /* If first aggregated packet prepare the next Txn struct */
                    if (uAggregPktsNum == 0)
                    {
                        pTxn = (TTxnStruct*)&(pRxXfer->aTxnStruct[pRxXfer->uCurrTxnIndex]);
                        pTxn->uHwAddr = SLV_MEM_DATA;
                    }
                    
                    pTxn->aBuf[uAggregPktsNum] = pHostBuf;
                    pTxn->aLen[uAggregPktsNum] = uBuffSize;
                    uAggregPktsNum++;
                    uTotalAggregLen += uBuffSize;
                    if (uAggregPktsNum >= pRxXfer->uMaxAggregPkts)
                    {
                        bIssueTxn = TRUE;
                    }
                    pRxXfer->uDrvRxCntr++;
                }
    
                /* If buffer pending until freeing previous buffer, set Exit flag and if needed set IssueTxn flag. */
                else if (eBufStatus == RX_BUF_ALLOC_PENDING)
                {
                    bExit = TRUE;
                    pRxXfer->bPendingBuffer = TRUE;
                    if (uAggregPktsNum > 0)
                    {
                        bIssueTxn = TRUE;
                    }
#ifdef TI_DBG
                    pRxXfer->tDbgStat.uCountBufPend++;
#endif
                }
    
                /* If no buffer due to out-of-memory, set DropLastPkt flag and if needed set IssueTxn flag. */
                else
                {
                    bDropLastPkt = TRUE;
                    if (uAggregPktsNum > 0)
                    {
                        bIssueTxn = TRUE;
                    }
#ifdef TI_DBG
                    pRxXfer->tDbgStat.uCountBufNoMem++;
#endif
                }
            }
        }

        /* If no more packets, set Exit flag and if needed set IssueTxn flag. */
        else 
        {
            bExit = TRUE;
            
            if (uAggregPktsNum > 0)
            {
                bIssueTxn = TRUE;
            }
        }


        /* If required to send Rx packet(s) transaction */
        if (bIssueTxn) 
        {

            if (bExit)
            {
                TXN_PARAM_SET_END_OF_BURST(pTxn, 1);
            }
            /* If not all Txn buffers are used, reset first unused buffer length for indication */
            if (uAggregPktsNum < MAX_XFER_BUFS)
            {
                pTxn->aLen[uAggregPktsNum] = 0;
            }

            ADD_DBG_Report(25, uAggregPktsNum, uTotalAggregLen);
            eTxnStatus = rxXfer_IssueTxn (uRxDesc);

            if (eTxnStatus == TXN_STATUS_COMPLETE)
            {
                /* Forward received packet to the upper layers */
                rxXfer_ForwardPacket (pRxXfer, pTxn, aExtraBytesArray);
            }
            else if (eTxnStatus == TXN_STATUS_PENDING) 
            {
                /* Decrease the number of available txn structures */
                pRxXfer->uAvailableTxn--;
            }
            else 
            {
                //Report(pRxXfer->hReport, REPORT_SEVERITY_ERROR , "rxXfer_Handle: Status=%d, DrvCntr=%d, RxDesc=0x%x\r\n", eTxnStatus, pRxXfer->uDrvRxCntr, uRxDesc);
            }

#ifdef TI_DBG
            pRxXfer->tDbgStat.uCountPktAggreg[uAggregPktsNum - 1]++;
#endif

            uAggregPktsNum  = 0;
            uTotalAggregLen = 0;
            bIssueTxn       = FALSE;
            pRxXfer->uCurrTxnIndex = (pRxXfer->uCurrTxnIndex + 1) % MAX_CONSECUTIVE_READ_TXN;
        }

        /* If last packet should be dropped (no memory for host buffer) */
        if (bDropLastPkt)
        {
            /* Increment driver packets counter before calling rxXfer_IssueTxn() */
            pRxXfer->uDrvRxCntr++;

            /* Read packet to dummy buffer and ignore it (no callback needed) */
            pTxn = (TTxnStruct*)&pRxXfer->aTxnStruct[pRxXfer->uCurrTxnIndex];
            BUILD_TTxnStruct(pTxn, SLV_MEM_DATA, pRxXfer->aTempBuffer, uBuffSize, (TTxnDoneCb)rxXfer_PktDropTxnDoneCb, pRxXfer)
            eTxnStatus = rxXfer_IssueTxn (uRxDesc);
            if (eTxnStatus == TXN_STATUS_PENDING) 
            {
                pRxXfer->uAvailableTxn--;
            }
            pRxXfer->uCurrTxnIndex = (pRxXfer->uCurrTxnIndex + 1) % MAX_CONSECUTIVE_READ_TXN;
            bDropLastPkt = FALSE;
        }

        /* Can't process more packets so exit */
        if (bExit)
        {
            return OK;
        }

    } /* End of while(1) */

    /* Unreachable code */

#endif
}


/****************************************************************************
 *                      rxXfer_IssueTxn()
 ****************************************************************************
 * DESCRIPTION: 
 *
 * INPUTS:      
 * 
 * OUTPUT:      
 * 
 * RETURNS:     
 ****************************************************************************/
static ETxnStatus rxXfer_IssueTxn (uint32_t uRxDesc)
{
    TRxXfer    *pRxXfer = gRxXferCB;
    uint32_t    uIndex  = pRxXfer->uCurrTxnIndex;
    TTxnStruct *pTxn;
    ETxnStatus  eStatus;

    /* Issue the packet(s) read transaction (prepared in rxXfer_Handle) */ 
    pTxn = &pRxXfer->aTxnStruct[uIndex];
    eStatus = twIf_Transact(pTxn);

    /* Return the status of the packet(s) transaction - COMPLETE, PENDING or ERROR */
    return eStatus;
}
  

/****************************************************************************
 *                      rxXfer_SetRxDirectAccessParams()
 ****************************************************************************
 * DESCRIPTION: 
 *
 * INPUTS:      
 * 
 * OUTPUT:      
 * 
 * RETURNS:     
 ****************************************************************************/
#if 0
void rxXfer_SetRxDirectAccessParams ( TDmaParams *pDmaParams)
{
    TRxXfer *pRxXfer = gRxXferCB;

    pRxXfer->uPacketMemoryPoolStart = pDmaParams->PacketMemoryPoolStart;
}
#endif

/****************************************************************************
 *                      rxXfer_TxnDoneCb()
 ****************************************************************************
 * DESCRIPTION: Forward the packet to the registered CB
 *
 * INPUTS:      
 * 
 * OUTPUT:      
 * 
 * RETURNS:     
 ****************************************************************************/
static void rxXfer_TxnDoneCb ( TTxnStruct *pTxn)
{
    TRxXfer *pRxXfer = gRxXferCB;
    
    ADD_DBG_Report(40, pRxXfer->uAvailableTxn, 0);
    /* Increase the number of available txn structures */
    pRxXfer->uAvailableTxn++;

    /* Forward received packet to the upper layers */
    rxXfer_ForwardPacket (pRxXfer, pTxn, NULL);

    /* If we exited the handler upon pending-buffer, call it again to handle further packets if any */
    if (pRxXfer->bPendingBuffer)
    {
        ADD_DBG_Report(60, pRxXfer->uAvailableTxn, 0);
        pRxXfer->bPendingBuffer = FALSE;
        rxXfer_Handle ();
    }

}


/****************************************************************************
 *                      rxXfer_PktDropTxnDoneCb()
 ****************************************************************************
 * DESCRIPTION: Dummy CB for case of dropping a packet due to out-of-memory.
 *
 * INPUTS:      
 * 
 * OUTPUT:      
 * 
 * RETURNS:     
 ****************************************************************************/
static void rxXfer_PktDropTxnDoneCb ( TTxnStruct *pTxn)
{
    TRxXfer *pRxXfer = gRxXferCB;
    
    /* Increase the number of available txn structures */
    pRxXfer->uAvailableTxn++;

    /* Restore the regular TxnDone callback to the used structure */
    pTxn->fTxnDoneCb = (TTxnDoneCb)rxXfer_TxnDoneCb;
    pTxn->hCbHandle  = gRxXferCB;
}


/****************************************************************************
 *                      rxXfer_Restart()
 ****************************************************************************
 * DESCRIPTION: rxXfer_Restart the RxXfer module object (called by the recovery)
 * 
 * INPUTS:  hRxXfer - The object to free
 * 
 * OUTPUT:  None
 * 
 * RETURNS: NONE 
 ****************************************************************************/
void rxXfer_Restart(void)
{
    TRxXfer    *pRxXfer = gRxXferCB;
    TTxnStruct *pTxn;
    uint8_t     i;

    pRxXfer->uFwRxCntr     = 0;
    pRxXfer->uDrvRxCntr    = 0;
    pRxXfer->uCurrTxnIndex = 0;
    pRxXfer->uAvailableTxn = MAX_CONSECUTIVE_READ_TXN - 1;

    /* Scan all transaction array and release only pending transaction */
    for (i = 0; i < MAX_CONSECUTIVE_READ_TXN; i++)
    {
        pTxn = &(pRxXfer->aTxnStruct[i]);

        /* Check if buffer allocated and not the dummy one (has a different callback) */
        if ((pTxn->aBuf[0] != 0) && (pTxn->fTxnDoneCb == (TTxnDoneCb)rxXfer_TxnDoneCb))
        {
            uint32_t uBufNum;
            RxIfDescriptor_t *pRxParams;

            /* Go over the Txn occupied  buffers and mark them as TAG_CLASS_UNKNOWN to be freed */
            for (uBufNum = 0; uBufNum < MAX_XFER_BUFS; uBufNum++) 
            {
                /* If no more buffers, exit the loop */
                if (pTxn->aLen[uBufNum] == 0)
                {
                    break;
                }

                pRxParams = (RxIfDescriptor_t *)(pTxn->aBuf[uBufNum]);
                pRxParams->packet_class_tag = TAG_CLASS_UNKNOWN;
            }

            /* Call upper layer only to release the allocated buffer */
            rxXfer_ForwardPacket (pRxXfer, pTxn, NULL);
        }
    }

    /* Fill the transaction structures fields that have constant values */
    for (i = 0; i < MAX_CONSECUTIVE_READ_TXN; i++)
    {
        /* The packet(s) read transaction */
        pTxn = &(pRxXfer->aTxnStruct[i]);
        TXN_PARAM_SET(pTxn, TXN_LOW_PRIORITY, TXN_FUNC_ID_WLAN, TXN_DIRECTION_READ, TXN_FIXED_ADDR)
        pTxn->fTxnDoneCb = (TTxnDoneCb)rxXfer_TxnDoneCb;
        pTxn->hCbHandle  = gRxXferCB;
    }

    rxXfer_SetBusParams(MAX_BUS_TXN_SIZE);
    rxXfer_SetDefaults();
}


/****************************************************************************
 *                      rxXfer_RegisterErrCb()
 ****************************************************************************
 * DESCRIPTION: Register Error CB
 *
 * INPUTS:  
 *          hRxXfer - The object
 *          ErrCb   - The upper layer CB function for error handling 
 *          hErrCb  - The CB function handle
 * 
 * OUTPUT:  None
 * 
 * RETURNS: void 
 ****************************************************************************/
void rxXfer_RegisterErrCb ( void *fErrCb, void * hErrCb)
{
    TRxXfer *pRxXfer = gRxXferCB;

    /* Save upper layer (health monitor) CB for recovery from fatal error */
    pRxXfer->fErrCb = (TFailureEventCb)fErrCb;
    pRxXfer->hErrCb = hErrCb;
}


#ifdef TI_DBG
/****************************************************************************
 *                      rxXfer_ClearStats()
 ****************************************************************************
 * DESCRIPTION: 
 *
 * INPUTS:  
 *          pRxXfer The object
 * 
 * OUTPUT:  None
 * 
 * RETURNS: TI_OK. 
 ****************************************************************************/
void rxXfer_ClearStats (void)
{
    TRxXfer *pRxXfer = gRxXferCB;

    os_memset(&pRxXfer->tDbgStat, 0, sizeof(TRxXferDbgStat));
}


/****************************************************************************
 *                      rxXfer_PrintStats()
 ****************************************************************************
 * DESCRIPTION: .
 *
 * INPUTS:  
 *          pRxXfer The object
 * 
 * OUTPUT:  None
 * 
 * RETURNS: TI_OK. 
 ****************************************************************************/
void rxXfer_PrintStats (void)
{
#ifdef REPORT_LOG
    TRxXfer *pRxXfer = gRxXferCB;
    
   //GTRACE(1, "Print RX Xfer module info\r\n"));
   //Report(("=========================\r\n"));
   //GTRACE(1, "uMaxAggregPkts     = %d\r\n", pRxXfer->uMaxAggregPkts));
   //GTRACE(1, "uMaxAggregLen      = %d\r\n", pRxXfer->uMaxAggregLen));
   //GTRACE(1, "FW counter         = %d\r\n", pRxXfer->uFwRxCntr));
   //GTRACE(1, "Drv counter        = %d\r\n", pRxXfer->uDrvRxCntr));
   //GTRACE(1, "AvailableTxn       = %d\r\n", pRxXfer->uAvailableTxn));
   //GTRACE(1, "uCountFwEvents     = %d\r\n", pRxXfer->tDbgStat.uCountFwEvents));
   //GTRACE(1, "uCountPktsForward  = %d\r\n", pRxXfer->tDbgStat.uCountPktsForward));
   //GTRACE(1, "uCountBufPend      = %d\r\n", pRxXfer->tDbgStat.uCountBufPend));
   //GTRACE(1, "uCountBufNoMem     = %d\r\n", pRxXfer->tDbgStat.uCountBufNoMem));
   //GTRACE(1, "uCountPktAggreg-1  = %d\r\n", pRxXfer->tDbgStat.uCountPktAggreg[0]));
   //GTRACE(1, "uCountPktAggreg-2  = %d\r\n", pRxXfer->tDbgStat.uCountPktAggreg[1]));
   //GTRACE(1, "uCountPktAggreg-3  = %d\r\n", pRxXfer->tDbgStat.uCountPktAggreg[2]));
   //GTRACE(1, "uCountPktAggreg-4  = %d\r\n", pRxXfer->tDbgStat.uCountPktAggreg[3]));
   //GTRACE(1, "uCountPktAggreg-5  = %d\r\n", pRxXfer->tDbgStat.uCountPktAggreg[4]));
   //GTRACE(1, "uCountPktAggreg-6  = %d\r\n", pRxXfer->tDbgStat.uCountPktAggreg[5]));
   //GTRACE(1, "uCountPktAggreg-7  = %d\r\n", pRxXfer->tDbgStat.uCountPktAggreg[6]));
   //GTRACE(1, "uCountPktAggreg-8  = %d\r\n", pRxXfer->tDbgStat.uCountPktAggreg[7]));
   //GTRACE(1, "uRxFifoWa          = %d\r\n", pRxXfer->uRxFifoWa));
#ifdef DBG_Report
    {
        uint32_t i;
       //GTRACE(1, "Indx: Event    Data1    Data2\r\n"));
        for (i = 0; i < DBG_TBL_SIZE; i++) 
        {
           //Report(("%04d: %05d %08x %08x\r\n", ((aDbgIndex + i) % DBG_TBL_SIZE), 
                   aDbgTrace[(aDbgIndex + i) % DBG_TBL_SIZE].uEvent,
                   aDbgTrace[(aDbgIndex + i) % DBG_TBL_SIZE].uData1,
                   aDbgTrace[(aDbgIndex + i) % DBG_TBL_SIZE].uData2));
        }
    }
#endif
#endif
}
#endif

#endif
