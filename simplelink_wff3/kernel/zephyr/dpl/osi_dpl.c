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
#include <zephyr/kernel.h>
#include <zephyr/multi_heap/shared_multi_heap.h>
#include <sys/types.h>
#include <stdlib.h>
#include <osi_kernel.h>
#include "ti/drivers/dpl/SemaphoreP.h"
#include "ti/drivers/dpl/TaskP.h"
#include "ti/drivers/dpl/MutexP.h"
#include "ti/drivers/dpl/MessageQueueP.h"
#include "ti/drivers/dpl/ClockP.h"
#include "ti/drivers/dpl/HwiP.h"

/*******************************************************************************

    DEFINES and SETTINGS

********************************************************************************/

#define TICK_PERIOD_nS (1000000000 / configTICK_RATE_HZ)
#define TICK_PERIOD_US (1000000 / configTICK_RATE_HZ)
/* System tick period in microseconds */
#define TICK_PERIOD_MS (1000 / configTICK_RATE_HZ)


#ifdef COLLECT_HEAP_DEBUG_INFO //OSPREY_MX-17
heap_debug_t heapdebug[HEAP_DBG_SIZE];
heap_debug_vport_t heapDebugVport[HEAP_DBG_VPORT_SIZE];
uint32_t dbg_offset = 0;
uint32_t dbg_vport_offset = 0;
uint32_t heapDbg_alloc_fail = 0;
int64_t heapDbg_total_alloc = 0;
#endif

/*******************************************************************************

    MISCELLANEOUS

********************************************************************************/
/*!
    \brief  convert tick to msec
*/
uint32_t TICK_TO_mSEC(uint32_t Tick)
{
    return ((Tick) * 1000U / CONFIG_SYS_CLOCK_TICKS_PER_SEC);
}

/*!
    \brief  convert msec to tick
*/
uint32_t mSEC_TO_TICK(uint32_t mSec)
{
    return ((mSec) * CONFIG_SYS_CLOCK_TICKS_PER_SEC / 1000U);
}

/*!
    \brief  assert function for the upper mac library

    \param  condition   -   if TRUE, assert will occur

    \return
    \note
    \warning
*/
void ASSERT_GENERAL(uint32_t condition)
{
    uint32_t lr;

    lr = (uint32_t)__get_LR();

    if(FALSE == condition)
    {
	printf(">>>> ASSERT\n");
        osi_EnterCriticalSection();
        Report("\n\rASSSSEEEERRRTTT!!!! in 0x%x\n\r",lr);
        while(1);
    }
}

/*******************************************************************************

    Critical section

********************************************************************************/

uint32_t osi_EnterCritical(void)
{
    uint32_t ulKey = HwiP_disable(); 
    TaskP_disableScheduler();
    return ulKey;
}

uint32_t osi_ExitCritical(uint32_t ulKey)
{
    TaskP_restoreScheduler((uintptr_t)ulKey);
    HwiP_restore(ulKey);
    return 0;
}

/*******************************************************************************

    SYNC

********************************************************************************/


/*!
	\brief 	This function creates a sync object

	The sync object is used for synchronization between different thread or ISR and
	a thread.

	\param	pSyncObj	-	pointer to the sync object control block

	\return upon successful creation the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
OsiReturnVal_e osi_SyncObjCreate(OsiSyncObj_t* pSyncObj)
{
	*pSyncObj = SemaphoreP_createBinary(0);

	return *pSyncObj ? OSI_OK : OSI_OPERATION_FAILED;
}

/*!
	\brief 	This function deletes a sync object

	\param	pSyncObj	-	pointer to the sync object control block

	\return upon successful deletion the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
OsiReturnVal_e osi_SyncObjDelete(OsiSyncObj_t* pSyncObj)
{
	SemaphoreP_delete(*pSyncObj);

	return OSI_OK;
}

/*!
	\brief 		This function generates a sync signal for the object.

	All suspended threads waiting on this sync object are resumed

	\param		pSyncObj	-	pointer to the sync object control block

	\return 	upon successful signaling the function should return 0
				Otherwise, a negative value indicating the error code shall be returned
	\note		the function could be called from ISR context
	\warning
*/

OsiReturnVal_e osi_SyncObjSignal(OsiSyncObj_t* pSyncObj)
{
	SemaphoreP_post(*pSyncObj);

	return OSI_OK;
}

/*!
	\brief 		This function generates a sync signal for the object
				from ISR context.

	All suspended threads waiting on this sync object are resumed

	\param		pSyncObj	-	pointer to the sync object control block

	\return 	upon successful signalling the function should return 0
				Otherwise, a negative value indicating the error code shall be returned
	\note		the function is called from ISR context
	\warning
*/
OsiReturnVal_e osi_SyncObjSignalFromISR(OsiSyncObj_t* pSyncObj)
{

   return osi_SyncObjSignal(pSyncObj);
}

/*!
	\brief 	This function waits for a sync signal of the specific sync object

	\param	pSyncObj	-	pointer to the sync object control block
	\param	Timeout		-	numeric value specifies the maximum number of mSec to
							stay suspended while waiting for the sync signal
							Currently, the simple link driver uses only two values:
								- OSI_WAIT_FOREVER
								- OSI_NO_WAIT

	\return upon successful reception of the signal within the timeout window return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/


OsiReturnVal_e osi_SyncObjWait(OsiSyncObj_t* pSyncObj , OsiTime_t Timeout)
{
	return osi_LockObjLock(pSyncObj, Timeout);
}

/*!
	\brief 	This function clears a sync object

	\param	pSyncObj	-	pointer to the sync object control block

	\return upon successful clearing the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/

OsiReturnVal_e osi_SyncObjClear(OsiSyncObj_t* pSyncObj)
{
	return osi_SyncObjWait(pSyncObj, 0);
}

/*******************************************************************************

    LOCK

********************************************************************************/
/*!
	\brief 	This function creates a locking object.

	The locking object is used for protecting a shared resources between different
	threads. Allow only one thread to access a section of code at a time.

	\param	pLockObj	-	pointer to the locking object control block

	\return upon successful creation the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
OsiReturnVal_e osi_LockObjCreate(OsiLockObj_t *pLockObj)
{
	SemaphoreP_Params params = {};

	if (!pLockObj)
		return OSI_INVALID_PARAMS;

	*pLockObj = SemaphoreP_create(1, &params);

	return *pLockObj ? OSI_OK : OSI_OPERATION_FAILED;
}

/*!
	\brief 	This function deletes a locking object.

	\param	pLockObj	-	pointer to the locking object control block

	\return upon successful deletion the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/

OsiReturnVal_e osi_LockObjDelete(OsiLockObj_t* pLockObj)
{
	SemaphoreP_delete(*pLockObj);

	return OSI_OK;
}

/*!
	\brief 	This function locks a locking object.

	All other threads that call this function before this thread calls
	the osi_LockObjUnlock would be suspended

	\param	pLockObj	-	pointer to the locking object control block
	\param	Timeout		-	numeric value specifies the maximum number of mSec to
							stay suspended while waiting for the locking object
							Currently, the simple link driver uses only two values:
								- OSI_WAIT_FOREVER
								- OSI_NO_WAIT


	\return upon successful reception of the locking object the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
OsiReturnVal_e osi_LockObjLock(OsiLockObj_t* pLockObj , OsiTime_t Timeout)
{
	if (Timeout != OSI_WAIT_FOREVER)
		Timeout = (Timeout * 1000) / ClockP_getSystemTickPeriod();

	return SemaphoreP_pend(*pLockObj, Timeout) ? OSI_OPERATION_FAILED :
						     OSI_OK;
}

/*!
	\brief 	This function unlock a locking object.

	\param	pLockObj	-	pointer to the locking object control block

	\return upon successful unlocking the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/

OsiReturnVal_e osi_LockObjUnlock(OsiLockObj_t* pLockObj)
{
	SemaphoreP_post(*pLockObj);

	return OSI_OK;
}

/*******************************************************************************

    MESSAGE QUEUE

********************************************************************************/
/*!
	\brief 	This function is used to create the MsgQ

	\param	pMsgQ	-	pointer to the message queue
	\param	pMsgQName	-	msg queue name
	\param	MsgSize	-	size of message on the queue
	\param	MaxMsgs	-	max. number of msgs that the queue can hold

	\return - OsiReturnVal_e
	\note
	\warning
*/
OsiReturnVal_e osi_MsgQCreate(OsiMsgQ_t*         pMsgQ ,
                              char*              pMsgQName,
                              uint32_t             MsgSize,
                              uint32_t             MaxMsgs)
{
	*pMsgQ = MessageQueueP_create(MsgSize, MaxMsgs);

	return *pMsgQ ? OSI_OK : OSI_OPERATION_FAILED;
}

/*!
	\brief 	This function is used to delete the MsgQ

	\param	pMsgQ	-	pointer to the message queue

	\return - OsiReturnVal_e
	\note
	\warning
*/
OsiReturnVal_e osi_MsgQDelete(OsiMsgQ_t* pMsgQ)
{
	MessageQueueP_delete(*pMsgQ);

	return OSI_OK;
}

/*!
	\brief 	This function is used to write data to the MsgQ

	\param	pMsgQ	-	pointer to the message queue
	\param	pMsg	-	pointer to the Msg strut to read into
	\param	Timeout	-	timeout to wait for the Msg to be available

	\return - OsiReturnVal_e
	\note
	\warning
*/
OsiReturnVal_e osi_MsgQWrite(OsiMsgQ_t* pMsgQ, void* pMsg , OsiTime_t Timeout, uint8_t flags)
{
	MessageQueueP_Status ret;

	ret = MessageQueueP_post(*pMsgQ, pMsg, Timeout);
	return ret == MessageQueueP_OK ? OSI_OK : OSI_OPERATION_FAILED;
}

/*!
	\brief 	This function is used to read data from the MsgQ

	\param	pMsgQ	-	pointer to the message queue
	\param	pMsg	-	pointer to the Msg strut to read into
	\param	Timeout	-	timeout to wait for the Msg to be available

	\return - OsiReturnVal_e
	\note
	\warning
*/

OsiReturnVal_e osi_MsgQRead(OsiMsgQ_t* pMsgQ, void* pMsg , OsiTime_t Timeout)
{
	Timeout = Timeout == OSI_WAIT_FOREVER ? MessageQueueP_WAIT_FOREVER :
						Timeout * 1000;

	return MessageQueueP_pend(*pMsgQ, pMsg, Timeout) ? OSI_OPERATION_FAILED :
							   OSI_OK;
}

/*!
	\brief 	This function returns the number of messages ready in the Queue.

	\param	pMsgQ	-	pointer to the message queue

	\return - The number of messages available in the queue.
	\note
	\warning
*/
uint32_t osi_MsgQCount(OsiMsgQ_t* pMsgQ)
{
	return MessageQueueP_getPendingCount(*pMsgQ);
}

/*!
	\brief 	This function returns whether there are any messages ready in the Queue.

	\param	pMsgQ	-	pointer to the message queue

	\return - BOOLEAN
	\note
	\warning
*/
BOOLEAN osi_MsgQIsEmpty(OsiMsgQ_t* pMsgQ)
{
    return (osi_MsgQCount(pMsgQ) == 0);
}


/*******************************************************************************

    Memory

********************************************************************************/

void *os_malloc(size_t size)
{
	return shared_multi_heap_alloc(SMH_REG_ATTR_NON_CACHEABLE, size);
}

void os_free(void *ptr)
{
	shared_multi_heap_free(ptr);
}

void *os_realloc(void *ptr, size_t newsize)
{
	void *p;

	if (newsize == 0) {
		os_free(ptr);
		return NULL;
	}

	if (ptr == NULL) {
		return os_malloc(newsize);
	}

	p = os_zalloc(newsize);

	if (p) {
		if (ptr != NULL) {
			memcpy(p, ptr, newsize);
			os_free(ptr);
		}
	}

	return p;
}

void * os_realloc_array(void *ptr, size_t nmemb, size_t size)
{
    if (size && nmemb > (~(size_t) 0) / size)
        return NULL;
    return os_realloc(ptr, nmemb * size);
}

void * os_calloc(size_t nmemb, size_t size)
{
	if (size && nmemb > (~(size_t) 0) / size)
		return NULL;
	return os_zalloc(nmemb * size);
}

void *os_zalloc(size_t size)
{
	void *p = os_malloc(size);

	if (p != NULL) {
		(void)memset(p, 0, size);
	}
	return p;
}

#ifdef COLLECT_HEAP_DEBUG_INFO //OSPREY_MX-17

void os_printHeapdbg()
{
	/* TODO */
	return 0;
}
#endif


/*******************************************************************************

    Clocks / Timers

********************************************************************************/
/*!
    \brief  Put the thread to sleep
    \param  sec
    \return - OSI_OK
    \note
    \warning
*/

OsiReturnVal_e osi_Sleep(OsiTime_t sec)
{
    ClockP_sleep(sec);
    return OSI_OK;
}

/*-----------------------------------------------------------*/

/*!
    \brief  Put the thread to sleep in micro seconds
    \param  usec - time in micro seconds
    \return - OSI_OK
    \note
    \warning
*/
OsiReturnVal_e osi_uSleep(OsiTime_t usec)
{

    ClockP_usleep(usec);
    return OSI_OK;
}

/*-----------------------------------------------------------*/
/*!
    \brief  Get free running time in mili seconds
    \param
    \return - time in mili seconds
    \note
    \warning
*/
uint32_t osi_GetTimeMS()
{
    uint32_t Ticks = (uint32_t)ClockP_getSystemTicks();//tx_time_get();
    return TICK_TO_mSEC(Ticks);
}

/*******************************************************************************

    TIMERS

*******************************************************************************/

/*-----------------------------------------------------------*/

/*!
    \brief  Creates a timer in the OS
    \param pTimer - timer object preallocated allocated
    \param pTimerName - timer name
    \param pExpiryFunc - expiry callback function
    \param pParam - expiry callback parameters
    \return - OSI_xxx
    \note
    \warning
*/
OsiReturnVal_e osi_TimerCreate(OsiTimer_t*                      pTimer,
                               char*                            pTimerName, //NOT USED - remnant from freertos
                               P_TIMER_EXPIRY_LEGACY_FUNCTION   pExpiryFunc,
                               void*                            pParam)
{
    if ((NULL == pTimer) ||
        (NULL == pExpiryFunc))
    {
        return OSI_INVALID_PARAMS;
    }

    ClockP_Fxn pl_ExpiryFunc = (ClockP_Fxn)pExpiryFunc;
    uintptr_t pl_Param = (uintptr_t)pParam;

    ClockP_Params clock_params;
    clock_params.startFlag = 0;                 //will not start immediately
    clock_params.period    = 0xFFFFFFFF;
    clock_params.arg       = pl_Param;

    pTimer->osTimerHandler = ClockP_create (pl_ExpiryFunc,
                                            0xFFFFFFFF,
                                            &clock_params);


    pTimer->callBackFunc = pExpiryFunc;
    pTimer->params = pParam;

    if (NULL == pTimer->osTimerHandler)
    {
        return OSI_OPERATION_FAILED;
    }
    else
    {
        return OSI_OK;
    }
}

/*-----------------------------------------------------------*/

/*!
    \brief Deletes a timer in the OS
    \param pTimer - timer object
    \return - OSI_xxx
    \note
    \warning
*/
OsiReturnVal_e osi_TimerDelete(OsiTimer_t* pTimer)
{
    if (NULL == pTimer)
    {
        return OSI_INVALID_PARAMS;
    }
    ClockP_delete(pTimer->osTimerHandler);
    
    return OSI_OK;
}

/*-----------------------------------------------------------*/

/*!
    \brief Start a created timer
    \param pTimer - timer object
    \param DurationMiliSec
    \param Periodic - is this timer periodic
    \return - OSI_xxx
    \note
    \warning
*/
OsiReturnVal_e osi_TimerStart(OsiTimer_t*     pTimer,
                              OsiTime_t       DurationMiliSec,
                              BOOLEAN         Periodic)
{
    uint32_t DurationInTicks;

    // ensure that the timer is not running by calling to the deactivate function
    osi_TimerStop(pTimer);

    DurationInTicks = mSEC_TO_TICK(DurationMiliSec);
    ClockP_setTimeout(pTimer->osTimerHandler,DurationInTicks);
    ClockP_start(pTimer->osTimerHandler);
    return OSI_OK;
}

/*-----------------------------------------------------------*/
/*!
    \brief Stops a created timer
    \param pTimer - timer object
    \return - OSI_xxx
    \note
    \warning
*/
OsiReturnVal_e osi_TimerStop(OsiTimer_t* pTimer)
{
    if (NULL == pTimer)
    {
        return OSI_INVALID_PARAMS;
    }

   ClockP_stop(pTimer->osTimerHandler);
   return OSI_OK;
}

/*!
    \brief  Check if given timer is active
    \param pTimer - timer object
    \return - OSI_xxx
    \note
    \warning
*/
OsiReturnVal_e osi_TimerIsActive(OsiTimer_t* pTimer)
{
    uint32_t RetVal;

    if (NULL == pTimer)
    {
        return OSI_INVALID_PARAMS;
    }

    RetVal = ClockP_isActive(pTimer->osTimerHandler);

    if (RetVal > 0)
    {
        return OSI_OK;
    }
    else
    {
        return OSI_OPERATION_FAILED;
    }
}

/*

This function return the remaining duration untill the next expiry in mSec

Parameters:

    pTimer        -    pointer to the timer control block

*/
OsiTime_t osi_TimerGetRemainingTime(OsiTimer_t* pTimer)
{
    uint32_t       RetVal;
    uint32_t       RemainingTicks;
    OsiTime_t    RemainingDuration = 0;

    if (NULL != pTimer)
    {
        RetVal = ClockP_getTimeout(pTimer->osTimerHandler);

        if (RetVal > 0)
        {
            RemainingTicks = RetVal;
            RemainingDuration = TICK_TO_mSEC(RemainingTicks);
        }
    }

    return RemainingDuration;
}

/*******************************************************************************

    THREADS

********************************************************************************/
/*!
    \brief  Creates a thread in the OS
    \param pThread - return handler for the created thread
    \param pThreadName - thread name
    \param StackSize - stack size to be dynamically allocated inside the create function
    \param Priority - priority - 0 is lowest (IDLE) and (configMAX_PRIORITIES - 1) max
    \param pEntryFunc - thread entry function
    \param pParam - parameters to move to the thread entry function
    \return - OSI_xxx
    \note
    \warning
*/
OsiReturnVal_e osi_ThreadCreate(OsiThread_t*                 pThread,
                                char*                        pThreadName,
                                uint32_t                       StackSize,
                                uint32_t                       Priority,
                                P_THREAD_ENTRY_FUNCTION      pEntryFunc,
                                void*                        pParam
                                )
{
	TaskP_Params params = {
		.name = pThreadName,
		.arg = pParam,
		.priority = Priority,
		.stackSize = StackSize,
		.stack = NULL,
	};

	if (StackSize < OSI_MIN_THREAD_STACK_SIZE || Priority >= 32)
		return OSI_INVALID_PARAMS;

	*pThread = TaskP_create(pEntryFunc, &params);

	return OSI_OK;
}

/*!
    \brief  Deletes a thread in the OS
    \param pThread - return handler for the created thread
    \return - OSI_xxx
    \note
    \warning thread should to be in a safe code - while (1) loop for example
             in order to be deleted
*/
OsiReturnVal_e osi_ThreadDelete(OsiThread_t* pThread)
{
    TaskP_delete((TaskP_Handle)*pThread);

    return OSI_OK;
}

/*!
    \brief  Get currently running thread
    \param
    \return - currently running thread
    \note
    \warning
*/
OsiThread_t osi_GetCurrentThread()
{
    return (OsiThread_t)TaskP_getCurrentTask();
}

/*!
    \brief  Get the current  available heap size
    \param
    \return - currently running thread
    \note
    \warning
*/
size_t osi_GetFreeHeapSize()
{
    /* TODO */
    return 0;
}

/*******************************************************************************

    SEMAPHORE

********************************************************************************/

/*!
    \brief  This function creates a Semaphore object
            The Semaphore object is used for accounting resources which can be shared
            and obtained/released in different contexts, as well as having multicplicity of more than 1.

    \param  pSemaphoreObj        -   pointer to the Semaphore object (area allocated by the caller and remains in scope
                                                                      throughout the lifetime of the object).
            pSemaphoreObjName    -   pointer to the name of the semaphore object
            initialCount         -   count of the semaphore at creation.
                                     (the amount of resources available).
            maxCount             -   Max multiplicity of the semaphore.
                             Cannot release to a value which is larger than this value.

    \return upon successful unlocking the function should return 0
            Otherwise, a negative value indicating the error code shall be returned
*/
OsiReturnVal_e osi_SemaphoreObjCreate(OsiSemaphoreObj_t*      pSemaphoreObj     ,
                                      const char*             pSemaphoreObjName ,
                                      const uint32            initialCount      ,
                                      const uint32            maxCount          )
{
    //Check for NULL
    if(NULL == pSemaphoreObj)
    {
        return OSI_INVALID_PARAMS;
    }

    pSemaphoreObj->max_count = maxCount;

    SemaphoreP_Handle handle = 0;

    SemaphoreP_Params params;
    params.mode     = SemaphoreP_Mode_COUNTING;
    params.callback = NULL;

    handle = SemaphoreP_create((unsigned int)initialCount, &params);

    pSemaphoreObj->Semaphore = handle;
    if((SemaphoreP_Handle)(pSemaphoreObj->Semaphore) != NULL)
    {
        return OSI_OK;
    }
    else
    {
        return OSI_OPERATION_FAILED;
    }
}

/*!
    \brief This function deletes a Semaphore object.
           After this function is called, the area holding the semaphore objetc is no longer
           in used and can be reused.

    \param  pSemaphoreObj        -   pointer to the semaphore object to release

    \return upon successful unlocking the function should return 0
            Otherwise, a negative value indicating the error code shall be returned
*/
OsiReturnVal_e osi_SemaphoreObjDelete(OsiSemaphoreObj_t* pSemaphoreObj)
{
    //Check for NULL
    if(NULL == pSemaphoreObj)
    {
        return OSI_INVALID_PARAMS;
    }
    SemaphoreP_Handle *pl_SemaphoreObj = (SemaphoreP_Handle *)pSemaphoreObj->Semaphore;
    SemaphoreP_delete(*pl_SemaphoreObj);
    return OSI_OK;
}

/*!
    \brief This function attempts to obtain a semaphore instance.
           If no instance is available, it waits for the designated timeout.

    \param pSemaphoreObj   -   pointer semaphore object to obtain instance of.
           Timeout         -   numeric value specifies the maximum number of mSec to
                               stay suspended while waiting for an instance to become available.
    \return upon successful unlocking the function should return 0
            Otherwise, a negative value indicating the error code shall be returned
*/
OsiReturnVal_e osi_SemaphoreObjObtain(OsiSemaphoreObj_t* pSemaphoreObj , OsiTime_t Timeout)
{
   
    if(OSI_WAIT_FOREVER != Timeout)
    {
        Timeout = (Timeout * 1000) / ClockP_getSystemTickPeriod();
    }
    //Check for NULL
    if(NULL == pSemaphoreObj)
    {
        return OSI_INVALID_PARAMS;
    }

    SemaphoreP_Handle *pl_SemaphoreObj = (SemaphoreP_Handle *)pSemaphoreObj->Semaphore;
    if(SemaphoreP_OK == SemaphoreP_pend(*pl_SemaphoreObj, (uint32_t)Timeout))
    {
        return OSI_OK;
    }
    else
    {
        return OSI_OPERATION_FAILED;
    }
}

/*!
    \brief This function releases an instance of a semaphore.
           Note that if the available multiplicity of the semaphore is already at its
           maximal value, this function would fail.

    \param pSemaphoreObj        -   pointer to the semaphore object to release.

    \return upon successful unlocking the function should return 0
            Otherwise, a negative value indicating the error code shall be returned
*/
OsiReturnVal_e osi_SemaphoreObjRelease(OsiSemaphoreObj_t* pSemaphoreObj)
{
    //Check for NULL
    if(NULL == pSemaphoreObj)
    {
        return OSI_INVALID_PARAMS;
    }

    SemaphoreP_Handle *pl_SemaphoreObj = (SemaphoreP_Handle *)pSemaphoreObj->Semaphore;
    SemaphoreP_post( *pl_SemaphoreObj );
    return OSI_OK;
}

/*!
    \brief This function returns the current count of an instance of a semaphore.
           Note that if the available multiplicity of the semaphore is already at its
           maximal value, this function would fail.

    \param pSemaphoreObj        -   pointer to the semaphore object to get count for.

    \return the function should return the count of a semaphore
*/
uint32_t osi_SemaphoreObjGetCount(OsiSemaphoreObj_t* pSemaphoreObj)
{
    //Check for NULL
    if(NULL == pSemaphoreObj)
    {
        return OSI_INVALID_PARAMS;
    }
    MessageQueueP_Handle *pl_SemaphoreObj = (MessageQueueP_Handle *)pSemaphoreObj->Semaphore;
    return MessageQueueP_getPendingCount( *pl_SemaphoreObj );
}
