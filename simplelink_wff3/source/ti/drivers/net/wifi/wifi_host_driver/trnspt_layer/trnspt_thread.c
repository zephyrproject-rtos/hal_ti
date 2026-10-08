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
/** \file   Transport.c
 *  \brief  The Transport-Engine is an OS independent module, which provides the
 *            infrustracture for switching from external Transports to the driver's Transport.
 *          This includes also the driver task itself (workqueue in Linux), which invokes the 
 *            driver specific handlers in the driver's Transport.
 *          The OS specific implementation under this module (e.g. task-switching or 
 *            protection-locking) is provided by the OS abstraction layer (osapi.c).
 * 
 *  \see    Transport.h, osapi.c
 */


#define __FILE_ID__  FILE_ID_90
#include "osi_type.h"
#include "osi_kernel.h"
#include "trnspt_thread.h"
#include "trnspt_if.h"
#include "errors.h"


#ifdef TI_DBG
typedef struct 
{
    uint32_t       uSize;                  /* Clients' name string size */
    char            sName [MAX_NAME_SIZE];  /* Clients' name string      */
} TClientName;	
#endif /* TI_DBG */



TTransport *gTransportCB = NULL;
OsiThread_t gTrnsptThreadTcb = NULL;//if threads are created by external app this may not be used

uint8_t      gContRunThrdLoopTrnspt = TRUE;
OsiSyncObj_t gThrdLoopStoppedTrnsptSync = NULL;
OsiSyncObj_t trnsptThrdDummySleep = NULL;      /* sync object for kill the thread  */


/** 
 * \fn     trnspt_Create
 * \brief  Create the module 
 * 
 * Allocate and clear the module object.
 * 
 * \note    
 * \param  hOs      - Handle to Os Abstraction Layer
 * \return Handle of the allocated object 
 * \sa     trnspt_Destroy
 */ 
TTransport *trnspt_Create()
{
    TTransport *TransportCB;

	/* allocate module object */
    TransportCB = os_malloc(sizeof(TTransport));
	
	if (!TransportCB)
	{
		return NULL;
	}
	
    os_memset (TransportCB,0, (sizeof(TTransport)));
    TransportCB->isAlive = 1;
	return (TransportCB);
}


/** 
 * \fn     trnspt_Destroy
 * \brief  Destroy the module. 
 * 
 * Free the module memory.
 * 
 * \note   
 * \param  hTransport - The module object
 * \return 0 on success or 1 on failure
 * \sa     trnspt_Create
 */ 
int trnspt_Destroy(uint32_t uDestroyClientId)
{
    int32_t ret = 0;
    if (gTransportCB)
    {
        // mark stop for transport thread
		ret = osi_SyncObjCreate(&(gTransportCB->trnsptThrdRunStopSyncObject));
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED to create sync object,trnsptThrdRunStopSyncObject \n\r");
            return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__SYNC_OBJ_CREATE);
        }

        ret = osi_SyncObjCreate(&gThrdLoopStoppedTrnsptSync);
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED to create sync object,gThrdLoopStoppedTrnsptSync \n\r");
            return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__SYNC_OBJ_CREATE);
        }

        ret = osi_SyncObjCreate(&trnsptThrdDummySleep);
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED to create sync object,trnsptThrdDummySleep \n\r");
            return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__SYNC_OBJ_CREATE);
        }

        gTransportCB->isAlive = 0;


        trnspt_RequestSchedule(uDestroyClientId, 0);

		ret = osi_SyncObjWait(&(gTransportCB->trnsptThrdRunStopSyncObject), OSI_WAIT_FOREVER);
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED osi_SyncObjWait,trnsptThrdRunStopSyncObject \n\r");
            ASSERT_GENERAL(0);
            return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__SYNC_OBJ_WAIT);
        }

        /* Delete transport Thread*/
       ret = osi_ThreadDelete(&gTrnsptThreadTcb);
       if( OSI_OK != ret)
       {
           TWIF_PRINT_ERROR("trnspt_Destroy: FAILED to delete the transport thread,gTrnsptThreadTcb \n\r");
           return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__THREAD_DELETE);
       }

        ret = osi_SyncObjDelete(&(gTransportCB->trnsptThrdRunStopSyncObject));
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED to delete sync object ,gTransportCB->trnsptThrdRunStopSyncObject\n\r");
            return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__SYNC_OBJ_DELETE);
        }

        /* Delete sync obj that signal the thread */
        ret = osi_SyncObjDelete(&(gTransportCB->syncObj));
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED to delete sync object,gTransportCB->syncObj \n\r");
            return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__SYNC_OBJ_DELETE);
        }

        ret = osi_LockObjDelete(&(gTransportCB->lockObj));
        /* Destroy the protection handle */
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED to delete lock object,gTransportCB->lockObj \n\r");
            return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__LOCK_OBJ_DELETE);
        }

        ret = osi_LockObjDelete(&(gTransportCB->lockTxQueue));
        /* Destroy the protection handle */
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED to delete lock object,gTransportCB->lockTxQueue \n\r");
            return ret;
        }
        ret = osi_LockObjDelete(&(gTransportCB->lockTxCtrlAlloc));
        /* Destroy the protection handle */
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED to delete lock object,gTransportCB->lockTxCtrlAlloc \n\r");
            return ret;
        }
        ret = osi_LockObjDelete(&(gTransportCB->lockTTxXfer));
        /* Destroy the protection handle */
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED to delete lock object,gTransportCB->lockTTxXfer \n\r");
            return ret;
        }

        ret = osi_LockObjDelete(&(gTransportCB->lockTxReqSched));
        /* Destroy the protection handle */
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED to delete lock object,gTransportCB->lockTxReqSched \n\r");
            return ret;
        }
        ret = osi_SyncObjDelete(&gThrdLoopStoppedTrnsptSync);
        /* Destroy the protection handle */
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED to delete sync object ,gThrdLoopStoppedTrnsptSync \n\r");
            return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__SYNC_OBJ_DELETE);
        }
        gThrdLoopStoppedTrnsptSync  = NULL;

        ret = osi_SyncObjDelete(&trnsptThrdDummySleep);
        if( OSI_OK != ret)
        {
            TRANSPORT_PRINT_ERROR("trnspt_Destroy: FAILED to delete sync object ,trnsptThrdDummySleep\n\r");
            return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__SYNC_OBJ_DELETE);
        }
        trnsptThrdDummySleep = NULL;

        uint32_t i;
        for(i=0;i<gTransportCB->uNumClients;i++)
        {
            gTransportCB->aClientCbFunc[i]  = NULL;
            gTransportCB->aClientEnabled[i] = 0;
            gTransportCB->aClientPending[i] = FALSE;
        }
        os_free(gTransportCB);
        gTransportCB = NULL;
    }

    return OSI_OK;
}


/**
 * \fn     trnspt_DriverTask
 * \brief  The driver task
 *
 * This function is the driver's main task that always runs in the driver's
 * single Transport, scheduled through the OS (the driver's workqueue in Linux).
 * Only one instantiation of this task may run at a time!
 *
 * \note
 * \param  hTransport   - The module handle
 * \return void
 * \sa     trnspt_RequestSchedule
 */
void trnspt_Task(void* pParam)
{
    TTransport       *pTransport;
    TTransportCbFunc  fCbFunc;
    void *       hCbHndl = NULL;
    uint32_t       i;

    while(gContRunThrdLoopTrnspt)
    {
        pTransport = gTransportCB;

        if(pTransport->isAlive)
        {
            TRANSPORT_PRINT_THRD_INIT("\n\rTransport_Thread: thrd is running\n");
        }
        else
        {
            //wait forever until the thread is deleted
            //or  when thread implementation is disconnect and not delete, this will be signaled
            //Report("\n\r transport thread , thread on wait loop to be deleted or disconnected !!!");
            if(OSI_OK != osi_SyncObjWait(&trnsptThrdDummySleep,OSI_WAIT_FOREVER))
            {
                Report("\n\rerror!!! transport ;failed to wait   trnsptThrdDummySleep ; 0x%x",(uint32)&trnsptThrdDummySleep);
            }
        }
        while(pTransport->isAlive)
        {
            if( OSI_OK == osi_SyncObjWait(&(pTransport->syncObj), OSI_WAIT_FOREVER))
            {
                /* For all registered clients do: */
                for (i = 0; i < pTransport->uNumClients; i++)
                {
                    /* If client is pending and enabled */
                    if (pTransport->aClientPending[i]  &&  pTransport->aClientEnabled[i])
                    {
                        TRANSPORT_PRINT_IRQ("\n\rtrnspt_Task: Received event for client:%d aClientEnabled:%d",i,pTransport->aClientEnabled[i]);
                        /* Clear client's pending flag */
                        pTransport->aClientPending[i] = FALSE;

                       /* Call client's callback function */
                       fCbFunc = pTransport->aClientCbFunc[i];
                       if(pTransport->aClientCbHndl[i])
                       {
                           hCbHndl = pTransport->aClientCbHndl[i];
                       }
                       fCbFunc(hCbHndl);
                       TRANSPORT_PRINT_IRQ("\n\rtrnspt_Task: done handle event:%d",i);
                    }
                }
            }
        }
        osi_SyncObjSignal(&(gTransportCB->trnsptThrdRunStopSyncObject));
    }//while(cont)
    Report("\n\r transport thread , exit from thread loop !!!");
    osi_SyncObjSignal(&gThrdLoopStoppedTrnsptSync);//for application which wait on the osi_thread delete
}



/** 
 * \fn     trnspt_Init
 * \brief  Init required handles 
 * 
 * Init required handles.
 * 
 * \note    
 * \param  hTransport  - The queue object
 * \param  hOs       - Handle to Os Abstraction Layer
 * \param  hReport   - Handle to report module
 * \return void        
 * \sa     
 */ 
int trnspt_Init(uint32_t TrnsptThrdPrior)
{
    int retVal = 0;
    gTransportCB = trnspt_Create();

    //create protection lock
    retVal = osi_LockObjCreate(&(gTransportCB->lockObj));
    if(retVal != OSI_OK)
    {
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__LOCK_OBJ_CREATE);
    }

    retVal = osi_LockObjCreate(&(gTransportCB->lockTxQueue));
    if(retVal < 0)
    {
        return -1;
    }

    retVal = osi_LockObjCreate(&(gTransportCB->lockTxCtrlAlloc));
    if(retVal < 0)
    {
        return -1;
    }
    retVal = osi_LockObjCreate(&(gTransportCB->lockTTxXfer));
    if(retVal < 0)
    {
        return -1;
    }
    retVal = osi_LockObjCreate(&(gTransportCB->lockTxReqSched));
    if(retVal < 0)
    {
        return -1;
    }
    //create sync obj to signal the thread
    retVal = osi_SyncObjCreate(&(gTransportCB->syncObj));
    if(retVal != OSI_OK)
    {
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__SYNC_OBJ_CREATE);
    }

   //Create Task
   retVal = osi_ThreadCreate(&gTrnsptThreadTcb, "transport", TRANSPORT_THRD_STACK_SIZE, TrnsptThrdPrior, trnspt_Task, NULL);
   if(retVal != OSI_OK)
   {
       TWIF_PRINT_ERROR("\n\r trnspt_Init:transport ThreadCreate failed !!!");
       return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__THREAD_CREATE);
    }

    return 0;
}


/** 
 * \fn     trnspt_RegisterClient
 * \brief  Save client's parameters
 * 
 * This function is used by the Transport clients in their init process, for registering
 *   their information, 
 * This includes their callback function that should be invoked from the driver Transport
 *   when they are pending. 
 * 
 * \note   
 * \param  hTransport - The module handle
 * \param  fCbFunc  - The client's callback function.
 * \param  hCbHndl  - The client's callback function handle.
 * \param  bEnable  - TRUE = Enabled.
 * \return uint32_t - The index allocated for the client
 * \sa     
 */ 
uint32_t trnspt_RegisterClient(TTransportCbFunc  fCbFunc, uint32_t bEnable)
{
	TTransport       *pTransport = gTransportCB;
    uint32_t uClientId = pTransport->uNumClients;

    /* If max number of clients is exceeded, report error and exit. */
    if (uClientId == MAX_CLIENTS) 
    {
        return 0;
    }

    /* Save the new client's parameters. */
    pTransport->aClientCbFunc[uClientId]  = fCbFunc;
    pTransport->aClientEnabled[uClientId] = bEnable;
    pTransport->aClientPending[uClientId] = FALSE;
    pTransport->aClientCbHndl[uClientId] = NULL;


    /* Increment clients number and return new client ID. */
    pTransport->uNumClients++;

    return uClientId;
}




/** 
 * \fn     trnspt_RequestSchedule
 * \brief  Handle client's switch to driver's Transport.
 * 
 * This function is called by a client from external Transport event.
 * It sets the client's Pending flag and requests the driver's task scheduling.
 * Thus, the client's callback will be called afterwards from the driver Transport.
 * 
 * \note   
 * \param  hTransport   - The module handle
 * \param  uClientId  - The client's index
 * \return void 
 * \sa     trnspt_DriverTask
 */ 
void trnspt_RequestSchedule(uint32_t uClientId, uint32_t isFromISR)
{
	TTransport       *pTransport = gTransportCB;


    /* Set client's Pending flag and request driver task scheduling */
    pTransport->aClientPending[uClientId] = TRUE;

    if(TRUE == isFromISR)
    {
        //we would like to reschedule from ISR if the WLAN IRQ handler was triggered
        osi_SyncObjSignalFromISR(&(pTransport->syncObj));
    }
    else
    {
        TRANSPORT_PRINT("\n\rtrnspt_RequestSchedule Transfer: requested schedule client %d\n\r",uClientId);
        osi_SyncObjSignal(&(pTransport->syncObj));
    }
}


/**
 * \fn     trnspt_RequestScheduleWithinWlanThread
 * \brief  Set client in driver Transport.
 *
 * This function is called by a client from signal Transport event.
 * It sets the client's Pending flag.
 * The Transport switch will be managed by OS.
 * Thus, the client's callback will be called afterwards from the driver Transport.
 *
 * \note
 * \param  hTransport   - The module handle
 * \param  uClientId  - The client's index
 * \return void
 * \sa     trnspt_DriverTask
 */
void trnspt_RequestScheduleWithinWlanThread(uint32_t uClientId)
{
	TTransport       *pTransport = gTransportCB;

    /* Set client's Pending flag */
    pTransport->aClientPending[uClientId] = TRUE;
}


/** 
 * \fn     trnspt_EnterCriticalSection / trnspt_LeaveCriticalSection
 * \brief  Lock / Unlock Transport related critical sections
 * 
 * The Transport clients should use these functions for protecting their critical sections
 *   when handling Transport transition to driver Transport.
 * 
 * \note   
 * \param  hTransport   - The module handle
 * \return void 
 * \sa     
 */ 
void trnspt_EnterCriticalSection()
{
	TTransport       *pTransport = gTransportCB;

    /* Start critical section protection */
    osi_LockObjLock(&(pTransport->lockObj), OSI_WAIT_FOREVER);
}

void trnspt_LeaveCriticalSection()
{
	TTransport       *pTransport = gTransportCB;

    /* Stop critical section protection */
    osi_LockObjUnlock(&(pTransport->lockObj));
}

void trnspt_lockTxQueue()
{
    TTransport       *pTransport = gTransportCB;

    /* Start critical section protection */
    osi_LockObjLock(&(pTransport->lockTxQueue), OSI_WAIT_FOREVER);
}

void trnspt_unlockTxQueue()
{
    TTransport       *pTransport = gTransportCB;

    /* Stop critical section protection */
    osi_LockObjUnlock(&(pTransport->lockTxQueue));
}

void trnspt_lockTxReqSched()
{
    TTransport       *pTransport = gTransportCB;

    /* Start critical section protection */
    osi_LockObjLock(&(pTransport->lockTxReqSched), OSI_WAIT_FOREVER);
}

void trnspt_unlockTxReqSched()
{
    TTransport       *pTransport = gTransportCB;

    /* Stop critical section protection */
    osi_LockObjUnlock(&(pTransport->lockTxReqSched));
}

void trnspt_lockTxCtrlAlloc()
{
    TTransport       *pTransport = gTransportCB;

    /* Start critical section protection */
    osi_LockObjLock(&(pTransport->lockTxCtrlAlloc), OSI_WAIT_FOREVER);
}

void trnspt_unlockTxCtrlAlloc()
{
    TTransport       *pTransport = gTransportCB;

    /* Stop critical section protection */
    osi_LockObjUnlock(&(pTransport->lockTxCtrlAlloc));
}
void trnspt_lockTxXfer()
{
    TTransport       *pTransport = gTransportCB;

    /* Start critical section protection */
    osi_LockObjLock(&(pTransport->lockTTxXfer), OSI_WAIT_FOREVER);
}

void trnspt_unlockTxXfer()
{
    TTransport       *pTransport = gTransportCB;

    /* Stop critical section protection */
    osi_LockObjUnlock(&(pTransport->lockTTxXfer));
}

