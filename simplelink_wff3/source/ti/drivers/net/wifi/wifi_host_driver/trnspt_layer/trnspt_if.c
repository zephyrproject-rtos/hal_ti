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
/** \file   TwIf.c 
 *  \brief  Device interface control, including wakeup, address partition and transactions interfaces. 
 *
 * The TwIf module presents a common interface to all Xfer modules towards the device.
 * It is responsible for the common functionalities related to device access, which includes:
 *    - transactions submission
 *    - interface power control (wake the chip and let it return to ELP)
 *    - address translation (paging) when needed.
 * The TwIf has no OS, platform or bus type dependencies.
 * 
 *  \see    TwIf.h
 */

#define __FILE_ID__  FILE_ID_86
#include <osi_kernel.h>
#include <trnspt_thread.h>
#include "txn_defs.h"
#include <txn_bus_drv.h>
#include <trnspt_if.h>
#include "errors.h"

/************************************************************************
 * Defines
 ************************************************************************/
#define TXN_QUE_SIZE            QUE_UNLIMITED_SIZE

/* Values to write to the ELP register for sleep/awake */
#define ELP_CTRL_REG_SLEEP      0
#define ELP_CTRL_REG_AWAKE      1

/* 
 * Device interface-control registers addresses (at the end ot the 17-bit address space):
 */
#define PARTITION_REGISTERS_ADDR        (0x1FFC0)   /* Start address of the chip memory regions partition (see also HwInit) */
                                                    /* 4 couples of registers: region start address & region size */

#define ELP_CTRL_REG_ADDR		        (0x1FFFC)   /* ELP control register address */
#define REGISTER_SIZE               4

//#define TI_DBG_TRANSACATION_SINGLE_THREAD_TEST

/************************************************************************
 * Types
 ************************************************************************/

/* TwIf SM States */
typedef enum
{
	SM_STATE_AWAKE,           /* HW is awake and Txn-Queue is running */
	SM_STATE_SLEEP,           /* HW is asleep and Txn-Queue is stopped */
	SM_STATE_WAIT_HW          /* Waiting for HW to wake up (after triggering it), Txn-Queue is stopped */
} ESmState;

/* TwIf SM Events */
typedef enum
{
	SM_EVENT_START,           /* Need to wake up the device to handle transactions */
	SM_EVENT_HW_AVAILABLE,    /* The device woke up */
	SM_EVENT_SLEEP            /* Need to let the device go to sleep */
} ESmEvent;

/* The addresses partitioning configuration Txn data */
typedef struct 
{
    uint32_t       uMemSize;        /* The HW memory region size. */
    uint32_t       uMemAddr;        /* The HW memory region address. */
    uint32_t       uRegSize;        /* The HW registers region size. */
    uint32_t       uRegAddr;        /* The HW registers region address. */

} TPartitionTxnData;

/* The addresses partitioning configuration Txn */
typedef struct 
{
    TTxnStruct          tHdr;        /* The generic transaction structure */
    TPartitionTxnData   tData;       /* The addresses partitioning configuration data */

} TPartitionTxn;

/* The addresses partitioning configuration Txn */
typedef struct 
{
    TTxnStruct      tHdr;           /* The generic transaction structure */
    uint32_t       tData;       /* The addresses partitioning configuration data for one register */

} TPartitionRegTxn;

/* The addresses partitioning configuration Txn */
typedef struct 
{
    TTxnStruct      tHdr;           /* The generic transaction structure */
    uint8_t        uElpData;       /* The value to write to the ELP register */

} TElpTxn;

/* FW Roles state table entry */
typedef struct 
{
    uint32_t         bIsStarted;     /* The role is currently started */
#if 0 //PS optimization not available
    StationPowerSaveMode_e   ePmMode;
#endif/* The role power-mgmt mode from driver point of view */

} TFwRoleState;

/* The TwIf module Object */
typedef struct _TTwIfObj
{
    ESmState         eState;             /* SM current state */
    void *           hTransactionsQueue; /* Local queue for transactions to be sent */
    uint32_t         uAwakeReqCount;     /* Wake requests counts  */
    TElpTxn          tElpTxnSleep;       /* Transaction structure for writing sleep to ELP register  */
    TElpTxn          tElpTxnAwake;       /* Transaction structure for writing awake to ELP register  */
    uint32_t         bSendingTransactions;/* Indicates we are in the loop that sends transactions - to prevent recursion */
    /* HW Addresses partitioning */
    uint32_t       uMemAddr1;          /* The HW memory region start address. */
    uint32_t       uMemSize1;          /* The HW memory region end address. */
    uint32_t       uMemAddr2;          /* The HW registers region start address. */
    uint32_t       uMemSize2;          /* The HW registers region end address. */
    uint32_t       uMemAddr3;          /* The INT Status registers region start address. */
    uint32_t       uMemSize3;          /* The INT Status registers region end address. */
    uint32_t       uMemAddr4;          /* The FW Status mem registers region start address. */
   
} TTwIfObj;

TTwIfObj *gTwIF = NULL;

extern uint32_t gIsRecovery;

/************************************************************************
 * Internal functions prototypes
 ************************************************************************/
#ifdef TWIF_FW_NEED_WAKE_UP
static void        WriteElpReg        ();
#endif
static ETxnStatus  InsertTransaction  (TTwIfObj *pTwIf, TTxnStruct *pTxn);
static ETxnStatus  SendTransactions   (TTwIfObj *pTwIf, TTxnStruct *pCurrContextTxn);
#ifdef TWIF_FW_NEED_WAKE_UP
static void        HandleSmEvent      (TTwIfObj *pTwIf, ESmEvent eEvent);
#endif



/************************************************************************
 *
 *   Module functions implementation
 *
 ************************************************************************/



/** 
 * \fn     twIf_Destroy
 * \brief  Destroy the module. 
 * 
 * Free the Txn-queue, the BusDrv and the module's object.
 * 
 * \note   
 * \param  The module's object
 * \return 0
 * \sa     twIf_Create
 */ 
int twIf_Destroy()
{
    TTwIfObj *pTwIf = gTwIF;

    if (pTwIf)
    {
        busDrv_Destroy();

#ifdef TRANSACTION_SUPPORT_MULTI_THREAD
        if (pTwIf->hTransactionsQueue)
        {
            que_Destroy(pTwIf->hTransactionsQueue);
        }
#endif
        os_free(gTwIF);
        gTwIF = NULL;
    }

    return 0;
}


/** 
 * \fn     twIf_Restart
 * \brief  Restart module upon driver stop or recovery
 *
 * Called upon driver stop command or upon recovery.
 * Clear the transactions queue.
 * The status in transactions that were dropped due to restart is TXN_STATUS_RECOVERY,
 *     and its originator (Xfer module) handles it if required (if its CB was written in the Txn).
 *
 * \note
 * \param  hTwIf - The module's object
 * \return void
 * \sa
 */
void twIf_Restart()
{
    TTwIfObj *pTwIf = gTwIF;

    /*
     * Initialize all parameters to low power values.
     * The upper layers should update their awake requirements if needed after recovery!
     */
    pTwIf->eState               = SM_STATE_SLEEP;
    pTwIf->bSendingTransactions = FALSE;
#ifdef TRANSACTION_SUPPORT_MULTI_THREAD
    trnspt_EnterCriticalSection();
    /* Clear Txn queue */
    while (que_Dequeue(pTwIf->hTransactionsQueue) != NULL)  { }
    trnspt_LeaveCriticalSection();
#endif

}



/**
 * \fn     twIf_Init 
 * \brief  Init module 
 * 
 * - Init required handles and module variables
 * - Init the BusDrv module
 * - Create the transactions-queue
 * 
 * \note    
 * \param  hTwIf       - The module's object
 * \param  hReport     - Handle to report module
 * \param  hTimer     - Handle to timer module
 * \return void        
 * \sa     
 */ 
int twIf_Init()
{
    TTwIfObj   *pTwIf;
#ifdef TRANSACTION_SUPPORT_MULTI_THREAD
    uint32_t   uNodeHeaderOffset;
#endif
    TTxnStruct *pTxnHdr;   /* The ELP transactions header (as used in the BusDrv API) */

    gTwIF = os_malloc(sizeof(TTwIfObj));

    if (gTwIF == NULL)
    {
        ASSERT_GENERAL(0);
        return OSI_MEMORY_ALLOCATION_FAILURE;
    }

    os_memset(gTwIF, 0, sizeof(TTwIfObj));

    pTwIf = gTwIF;

    pTwIf->uAwakeReqCount = 0;

    /* Prepare ELP sleep transaction */
    pTwIf->tElpTxnSleep.uElpData = ELP_CTRL_REG_SLEEP;
    pTxnHdr = &(pTwIf->tElpTxnSleep.tHdr);
    TXN_PARAM_SET(pTxnHdr, TXN_LOW_PRIORITY, TXN_FUNC_ID_WLAN, TXN_DIRECTION_WRITE, TXN_INC_ADDR)
    TXN_PARAM_SET_MORE(pTxnHdr, 0);         /* Sleep is the last transaction! */
    /* NOTE: Function id for single step will be replaced to 0 by the bus driver */
    TXN_PARAM_SET_SINGLE_STEP(pTxnHdr, 1);  /* ELP write is always single step (use bytes transaction)! */
    BUILD_TTxnStruct(pTxnHdr, ELP_CTRL_REG_ADDR, &(pTwIf->tElpTxnSleep.uElpData), sizeof(uint8_t), NULL, NULL)

    /* Prepare ELP awake transaction */
    pTwIf->tElpTxnAwake.uElpData = ELP_CTRL_REG_AWAKE;
    pTxnHdr = &(pTwIf->tElpTxnAwake.tHdr);
    TXN_PARAM_SET(pTxnHdr, TXN_LOW_PRIORITY, TXN_FUNC_ID_WLAN, TXN_DIRECTION_WRITE, TXN_INC_ADDR)
    TXN_PARAM_SET_MORE(pTxnHdr, 1);         
    /* NOTE: Function id for single step will be replaced to 0 by the bus driver */
    TXN_PARAM_SET_SINGLE_STEP(pTxnHdr, 1);  /* ELP write is always single step (use bytes transaction)! */
    BUILD_TTxnStruct(pTxnHdr, ELP_CTRL_REG_ADDR, &(pTwIf->tElpTxnAwake.uElpData), sizeof(uint8_t), NULL, NULL)


#ifdef TRANSACTION_SUPPORT_MULTI_THREAD
    /* Create the transactions queue. */
    uNodeHeaderOffset = FIELD_OFFSET(TTxnStruct, tTxnQNode);
    pTwIf->hTransactionsQueue = que_Create(TXN_QUE_SIZE, uNodeHeaderOffset);
    if (pTwIf->hTransactionsQueue == NULL)
    {
        ASSERT_GENERAL(0);
        return OSI_MEMORY_ALLOCATION_FAILURE;
    }
#endif
    /* Restart TwIf */
    twIf_Restart();

	busDrv_Init();

#ifdef TWIF_FW_NEED_WAKE_UP
	twIf_Awake();
	//signal HW available because this is the begining of the world
	//sleep will be available once sleep command will be raised
    twIf_HwAvailable();
#endif
    return OSI_OK;
}



#ifdef TWIF_FW_NEED_WAKE_UP
/** 
 * \fn     WriteElpReg
 * \brief  write ELP register
 * 
 * \note   
 * \return void
 * \sa     
 */ 
static void WriteElpReg()
{
 //reserved for future use
}
#endif


/** 
 * \fn     twIf_SetPartition
 * \brief  Set HW addresses partition
 * 
 * Called by the HwInit module to set the HW address ranges for download or working access.
 * Generate and configure the bus access address mapping table.
 * The partition is split between register (fixed partition of 24KB size, exists in all modes), 
 *     and memory (dynamically changed during init and gets constant value in run-time, 104KB size).
 * The TwIf configures the memory mapping table on the device by issuing write transaction to 
 *     table address (note that the bus driver see this as a regular transaction). 
 * 
 * \note In future versions, a specific bus may not support partitioning (as in wUART), 
 *       In this case the HwInit module shall not call this function (will learn the bus 
 *       configuration from the INI file).
 *
 * \param  hTwIf          - The module's object
 * \param  uMemAddr  - The memory partition base address
 * \param  uMemSize  - The memory partition size
 * \param  uRegAddr  - The registers partition base address
 * \param  uRegSize  - The register partition size
 * \return void
 * \sa     
 */ 

void twIf_SetPartition ( const TPartition *pPartition)
{
    TTwIfObj *pTwIf = gTwIF;

    /* Save partition information for translation and validation. */
    pTwIf->uMemAddr1 = pPartition[0].uMemAdrr;
    pTwIf->uMemSize1 = pPartition[0].uMemSize;
    pTwIf->uMemAddr2 = pPartition[1].uMemAdrr;
    pTwIf->uMemSize2 = pPartition[1].uMemSize;
    pTwIf->uMemAddr3 = pPartition[2].uMemAdrr;
    pTwIf->uMemSize3 = pPartition[2].uMemSize;
    pTwIf->uMemAddr4 = pPartition[3].uMemAdrr;
}



/** 
 * \fn     twIf_Awake
 * \brief  Request to keep the device awake
 * 
 * Used by the Xfer modules to request to keep the device awake until twIf_Sleep() is called.
 * Each call to this function increments AwakeReq counter. Once the device is awake (upon transaction),
 *     the TwIf SM keeps it awake as long as this counter is not zero.
 * 
 * \note   
 * \param  hTwIf - The module's object
 * \return void
 * \sa     twIf_Sleep
 */ 
void twIf_Awake()
{
    TTwIfObj *pTwIf = gTwIF;

    /* Increment awake requests counter */
    pTwIf->uAwakeReqCount++;
}


/** 
 * \fn     twIf_Sleep
 * \brief  Remove request to keep the device awake
 * 
 * Each call to this function decrements AwakeReq counter.
 * Once this counter is zeroed, if the transactions queue is empty, the TwIf SM is
 *     invoked to enable the device to sleep (write 0 to ELP register).
 * 
 * \note   
 * \param  hTwIf - The module's object
 * \return void
 * \sa     twIf_Awake
 */ 
void twIf_Sleep()
{
    TTwIfObj *pTwIf = gTwIF;

    /* Decrement awake requests counter */
    if (pTwIf->uAwakeReqCount > 0) /* in case of redundant call after recovery */
    {   
        pTwIf->uAwakeReqCount--;
    }
    else
    {
        TWIF_PRINT("twIf_Sleep: uAwakeReqCount was already 0!!\n\r");
    }
}


/** 
 * \fn     twIf_HwAvailable
 * \brief  Indicate the device is awake
 * 
 * This is an indication from the FwEvent that the device is awake.
 * Issue HW_AVAILABLE event to the SM.
 * 
 * \note   
 * \param  hTwIf - The module's object
 * \return void
 * \sa     
 */ 
#ifdef TWIF_FW_NEED_WAKE_UP
void twIf_HwAvailable()
{
    TTwIfObj *pTwIf = gTwIF;

    TWIF_PRINT("twIf_HwAvailable: HW is Available\n\r");

    /* Issue HW_AVAILABLE event to the SM */
    HandleSmEvent(pTwIf, SM_EVENT_HW_AVAILABLE);
}
#endif

/** 
 * \fn     twIf_Transact
 * \brief  Issue a transaction
 * 
 * This method is used by the Xfer modules to issue all transaction types.
 * Translate HW address according to bus partition and call InsertTransaction().
 * 
 * \note   
 * \param  hTwIf - The module's object
 * \param  pTxn  - The transaction object 
 * \return COMPLETE if the transaction was completed in this context, PENDING if not, ERROR if failed
 * \sa     InsertTransaction
 */ 
ETxnStatus twIf_Transact( TTxnStruct *pTxn)
{
    TTwIfObj *pTwIf = gTwIF;

	if ((pTxn->uHwAddr >= pTwIf->uMemAddr1) && (pTxn->uHwAddr <= pTwIf->uMemAddr1 + pTwIf->uMemSize1))
	{     
		pTxn->uHwAddr = pTxn->uHwAddr - pTwIf->uMemAddr1;
	}
	else if ((pTxn->uHwAddr >= pTwIf->uMemAddr2) && (pTxn->uHwAddr <= pTwIf->uMemAddr2 + pTwIf->uMemSize2))
	{     
		pTxn->uHwAddr = pTxn->uHwAddr - pTwIf->uMemAddr2 + pTwIf->uMemSize1;
	}
    else if ((pTxn->uHwAddr >= pTwIf->uMemAddr3) && (pTxn->uHwAddr <= pTwIf->uMemAddr3 + pTwIf->uMemSize3))
	{     
		pTxn->uHwAddr = pTxn->uHwAddr - pTwIf->uMemAddr3 + pTwIf->uMemSize1 + pTwIf->uMemSize2;
	}
	else
	{
	    return TXN_STATUS_ERROR;
	}

    /* Regular transaction are not the last and are not single step (only ELP write is) */
    TXN_PARAM_SET_MORE(pTxn, 1);         
    TXN_PARAM_SET_SINGLE_STEP(pTxn, 0);

    /* Handle the transaction and update the SM if needed. */  
    return InsertTransaction(pTwIf, pTxn);
}


ETxnStatus twIf_TransactReadFwStatus( TTxnStruct *pTxn)
{
    TTwIfObj *pTwIf = gTwIF;

    /* Regular transaction are not the last and are not single step (only ELP write is) */
    TXN_PARAM_SET_MORE(pTxn, 1);         
    TXN_PARAM_SET_SINGLE_STEP(pTxn, 0);

    /* Handle the transaction and update the SM if needed. */  
    return InsertTransaction(pTwIf, pTxn);
}


/** 
 * \fn     InsertTransaction
 * \brief  Handle new transaction
 * 
 * Enqueue current transaction, and if device is awake, send the queued transactions to it.
 * If asleep, issue Start event to the SM to awake the device.
 * 
 * \note   
 * \param  pTwIf - The module's object
 * \param  pTxn  - The transaction object 
 * \return COMPLETE if the transaction was completed in this context, PENDING if not, ERROR if failed
 * \sa     
 */ 
static ETxnStatus InsertTransaction(TTwIfObj *pTwIf, TTxnStruct *pTxn)
{
    ETxnStatus eStatus;
#ifdef TI_DBG_TRANSACATION_SINGLE_THREAD_TEST
    static void* owner = NULL;
    void* currentTask  = NULL;
#endif

#ifdef TI_DBG
    /* Verify that the Txn HW-Address is 4-bytes aligned */
	if (pTxn->uHwAddr & 0x3)
	{
        TRACE(pTwIf->hReport, REPORT_SEVERITY_ERROR, "InsertTransaction: Unaligned HwAddr! HwAddr=0x%x, Params=0x%x\n", pTxn->uHwAddr, pTxn->uTxnParams);
		return TXN_STATUS_ERROR;
	}	
    pTwIf->uDbgCountTxn++;
#endif
#ifdef TI_DBG_TRANSACATION_SINGLE_THREAD_TEST
    //the function is written with the assumption that it is been called  only be the same thread
    {
        currentTask = (void *)osi_GetCurrentThread();

        if (owner == NULL) {
            owner = currentTask;   // first caller becomes the owner
        } else {
            if(owner != currentTask)
            {
                TWIF_PRINT_ERROR("\n\rERROR function is been called from different threads");
            }
            ASSERT_GENERAL(owner == currentTask);
        }

    }
#endif
#ifdef TRANSACTION_SUPPORT_MULTI_THREAD
    trnspt_EnterCriticalSection();
    /* Enqueue current transaction */
    if(que_Enqueue(pTwIf->hTransactionsQueue, (void *)pTxn)< 0)
    {
        TWIF_PRINT_ERROR("\n\rERROR InsertTransaction***No room in queue hTransactionsQueue");
    }
    trnspt_LeaveCriticalSection();
#endif

#ifdef TWIF_FW_NEED_WAKE_UP

    /* If SM state is AWAKE, send all queued transactions */
    if (pTwIf->eState == SM_STATE_AWAKE)
#endif
    {
        eStatus = SendTransactions(pTwIf, pTxn);
        if(eStatus != TXN_STATUS_COMPLETE)
        {
            TWIF_PRINT_ERROR("\n\rERROR SendTransactions failed! eStatus: %d", eStatus);
        }
        return eStatus;
    }

#ifdef TWIF_FW_NEED_WAKE_UP
    /* Else if state is SLEEP, issue Start event to the SM to awake the device */
    else if (pTwIf->eState == SM_STATE_SLEEP)
    {
        HandleSmEvent(pTwIf, SM_EVENT_START);
    }
#endif
    /* If we are here (not awake), the current transaction is not sent yet, so return PENDING */
    return TXN_STATUS_PENDING;
}


/** 
 * \fn     SendTransactions
 * \brief  Send all queued transactions
 * 
 * If called in recursion (from the Xfer callback), return PENDING.
 * Dequeue and send all queued transactions, and call their callbacks if required.
 * When finished, if not required to remain awake, issue sleep evnent to the SM.
 * Note that the SDIO driver completes the transaction before returning (blocking us if DMA is used)!!
 * 
 * \note   
 * \param  pTwIf            - The module's object
 * \param  pCurrContextTxn  - The transaction that was inserted in the current context (could be NULL) 
 * \return COMPLETE if the current transaction was completed, PENDING if not, ERROR if failed
 * \sa     
 */ 
static ETxnStatus SendTransactions(TTwIfObj *pTwIf, TTxnStruct *pCurrContextTxn)
{
    ETxnStatus  eReturnStatus = TXN_STATUS_COMPLETE;
    TTxnStruct *pTxn;
    ETxnStatus eCurrStatus;

    /* While we have transactions in the queue */
#ifdef TRANSACTION_SUPPORT_MULTI_THREAD
    trnspt_EnterCriticalSection();//critical section is important in here see OSPREY_LDB-2074
    while ((pTxn = (TTxnStruct *)que_Dequeue(pTwIf->hTransactionsQueue)) != NULL)
#else
    pTxn = pCurrContextTxn;
#endif
    {
        /* Send the dequeued transaction to the BusDrv */
        if(!gIsRecovery)
        {
            eCurrStatus = busDrv_Transact(pTxn);
        }
        else
        {
            TWIF_PRINT("\n\rSendTransactions: Transaction is not allow while recovery");
            eCurrStatus = TXN_STATUS_ERROR;
            return eCurrStatus;
        }

        /* If Txn failed and error CB available, call it to initiate recovery */
        if (eCurrStatus == TXN_STATUS_ERROR)
        {
            TWIF_PRINT("\n\rSendTransactions: Txn failed!!  Params=0x%x, HwAddr=0x%x, Len0=%d, Len1=%d, Len2=%d, Len3=%d", pTxn->uTxnParams, pTxn->uHwAddr, pTxn->aLen[0], pTxn->aLen[1], pTxn->aLen[2], pTxn->aLen[3]);
            ASSERT_GENERAL(0);
            return eCurrStatus;
        }
#ifdef TRANSACTION_SUPPORT_MULTI_THREAD

        /* If the sent Txn is the one inserted in the current context, save status for the return value */
        if (pTxn == pCurrContextTxn)
        {
            eReturnStatus = eCurrStatus;
        }
#endif
        /* Else, the sent Txn was PENDING so if Xfer CB is available call it */
        /* Note: From the CB, more transactions may be issued, so we prevent recursion - see above */
        else if (pTxn->fTxnDoneCb != NULL)
        {
#ifdef TRANSACTION_SUPPORT_MULTI_THREAD
            trnspt_LeaveCriticalSection();
#endif
            ((TTxnDoneCb)(pTxn->fTxnDoneCb))(pTxn->hCbHandle, pTxn);
#ifdef TRANSACTION_SUPPORT_MULTI_THREAD
            trnspt_EnterCriticalSection();
#endif

        } 

        TWIF_PRINT("\n\rSendTransactions: Status = %d, Params=0x%x, HwAddr=0x%x, Len0=%d, Len1=%d, Len2=%d, Len3=%d", eCurrStatus, pTxn->uTxnParams, pTxn->uHwAddr, pTxn->aLen[0], pTxn->aLen[1], pTxn->aLen[2], pTxn->aLen[3]);
    } 


#ifdef TRANSACTION_SUPPORT_MULTI_THREAD
    trnspt_LeaveCriticalSection();
#endif
    /* Return the status of current context transaction (COMPLETE or ERROR) */
    return eReturnStatus;
}


/** 
 * \fn     HandleSmEvent
 * \brief  The TwIf SM implementation
 * 
 * Handle SM event.
 * Control the device awake/sleep states according to the event.
 *  
 * \note   
 * \param  hTwIf - The module's object
 * \return void
 * \sa     
 */ 
#ifdef TWIF_FW_NEED_WAKE_UP
static void HandleSmEvent(TTwIfObj *pTwIf, ESmEvent eEvent)
{
	ESmState eState = pTwIf->eState;  /* The state before handling the event */

    /* Switch by current state and handle event */
    switch (eState)
    {
    case SM_STATE_AWAKE:
        /* SLEEP event:  AWAKE ==> SLEEP,  set ELP reg to sleep */
        if (eEvent == SM_EVENT_SLEEP)
        {
            pTwIf->eState = SM_STATE_SLEEP;
            WriteElpReg();
        }
        break;
    case SM_STATE_SLEEP:
        /* START event:  SLEEP ==> WAIT_HW,  set ELP reg to wake-up */
        if (eEvent == SM_EVENT_START)
        {
            pTwIf->eState = SM_STATE_WAIT_HW;
            WriteElpReg();
        }

        /* HW_AVAILABLE event:  SLEEP ==> AWAKE,  set ELP reg to wake-up */
        else if (eEvent == SM_EVENT_HW_AVAILABLE)
        {
            pTwIf->eState = SM_STATE_AWAKE;
            WriteElpReg();
        }
        break;
    case SM_STATE_WAIT_HW:
        /* HW_AVAILABLE event:  WAIT_HW ==> AWAKE,  send queued transactions */
        if (eEvent == SM_EVENT_HW_AVAILABLE)
        {
            pTwIf->eState = SM_STATE_AWAKE;
            SendTransactions(pTwIf, NULL);
        }
        break;
    }

	TWIF_PRINT("HandleSmEvent: <currentState = %d, event = %d> --> nextState = %d\n\r", eState, eEvent, pTwIf->eState);
}
#endif

uint32_t twIf_IsValidMemoryAddr( uint32_t Address, uint32_t Length)
{
    TTwIfObj *pTwIf = gTwIF;

    if ((Address >= pTwIf->uMemAddr1) &&
        (Address + Length < pTwIf->uMemAddr1 + pTwIf->uMemSize1))
    {
        return TRUE;
    }

    return FALSE;
}

uint32_t twIf_IsValidRegAddr( uint32_t Address)
{
    TTwIfObj *pTwIf = gTwIF;

    if ((Address >= pTwIf->uMemAddr2 ) &&
        (Address < pTwIf->uMemAddr2 + pTwIf->uMemSize2))
    {
        return TRUE;
    }

    return FALSE;
}


/**
 * \fn     twIf_IsChipAwake
 * \brief  Is the chip awake
 *
 * Return TRUE if the chip is currently AWAKE (can be accessed).
 *
 * \note
 * \param  hTwIf - The module's object
 * \return TRUE if the chip is awake and FALSE if not
 * \sa
 */
uint32_t twIf_IsChipAwake()
{
    TTwIfObj *pTwIf = gTwIF;

    return (pTwIf->eState == SM_STATE_AWAKE);
}



/*******************************************************************************
*                       DEBUG  FUNCTIONS  IMPLEMENTATION					   *
********************************************************************************/

#ifdef TI_DBG

/** 
 * \fn     twIf_PrintModuleInfo
 * \brief  Print module's parameters (debug)
 * 
 * This function prints the module's parameters.
 * 
 * \note   
 * \param  hTwIf - The module's object                                          
 * \return void 
 * \sa     
 */ 
void twIf_PrintModuleInfo()
{
#ifdef REPORT_LOG
    TTwIfObj *pTwIf = gTwIF;
    uint32_t i;
	
	WLAN_OS_REPORT(("---------------- TwIf Module Info---------------------------\n"));
	WLAN_OS_REPORT(("============================================================\n"));
	WLAN_OS_REPORT(("uMemAddr             = 0x%x\n", pTwIf->uMemAddr1               ));
	WLAN_OS_REPORT(("uMemSize             = 0x%x\n", pTwIf->uMemSize1               ));
	WLAN_OS_REPORT(("uRegAddr             = 0x%x\n", pTwIf->uMemAddr2               ));
	WLAN_OS_REPORT(("uRegSize             = 0x%x\n", pTwIf->uMemSize2               ));
	WLAN_OS_REPORT(("uRegAddr             = 0x%x\n", pTwIf->uMemAddr3               ));
	WLAN_OS_REPORT(("uRegSize             = 0x%x\n", pTwIf->uMemSize3               ));
	WLAN_OS_REPORT(("uRegAddr             = 0x%x\n", pTwIf->uMemAddr4               ));
	WLAN_OS_REPORT(("------------------------------------------------------------\n"));
	WLAN_OS_REPORT(("uDbgCountAwake       = %d\n",   pTwIf->uDbgCountAwake          ));
	WLAN_OS_REPORT(("uDbgCountSleep       = %d\n",   pTwIf->uDbgCountSleep          ));
	WLAN_OS_REPORT(("uDbgCountElpRegAwake = %d\n",   pTwIf->uDbgCountElpRegAwake    ));
	WLAN_OS_REPORT(("uDbgCountElpRegSleep = %d\n",   pTwIf->uDbgCountElpRegSleep    ));
	WLAN_OS_REPORT(("uDbgCountWakeLock    = %d\n",   pTwIf->uDbgCountWakeLock       ));
	WLAN_OS_REPORT(("uDbgCountWakeUnlock  = %d\n",   pTwIf->uDbgCountWakeUnlock     ));
	WLAN_OS_REPORT(("uDbgCountTxn         = %d\n",   pTwIf->uDbgCountTxn            ));
	WLAN_OS_REPORT(("uDbgCountRecursion   = %d\n",   pTwIf->uDbgCountRecursion      ));
	WLAN_OS_REPORT(("------------------------------------------------------------\n"));
	WLAN_OS_REPORT(("eSmState             = %d\n",   pTwIf->eState					));
	WLAN_OS_REPORT(("bIsWakeLock          = %d\n",   pTwIf->bIsWakeLock             ));
	WLAN_OS_REPORT(("bIsPwrOptimized      = %d\n",   pTwIf->bIsPwrOptimized         ));
	WLAN_OS_REPORT(("bInactivityTimerExp  = %d\n",   pTwIf->bInactivityTimerExpired ));
	WLAN_OS_REPORT(("uInactivityPeriod    = %d\n",   pTwIf->uInactivityPeriod       ));
	WLAN_OS_REPORT(("------------------------------------------------------------\n"));
	WLAN_OS_REPORT(("uAwakeReqVector      = 0x%x\n", pTwIf->uAwakeReqVector         ));
	WLAN_OS_REPORT(("------------------------------------------------------------\n"));
    for (i = 0; i < MAX_NUM_WLAN_ROLE_IDS; i++)
    {
        WLAN_OS_REPORT(("FwRole %d:  bIsStarted = %d,  ePmMode = %d\n", 
                        i, pTwIf->aFwRoleStateTbl[i].bIsStarted, pTwIf->aFwRoleStateTbl[i].ePmMode));
    }
	WLAN_OS_REPORT(("==========================================================\n\n"));
#endif
} 

#endif /* TI_DBG */
