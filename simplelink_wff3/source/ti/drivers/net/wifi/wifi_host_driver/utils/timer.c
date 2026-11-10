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
/** \file   timer.c 
 *  \brief  The timers services OS-Independent layer over the OS-API timer services which are OS-Dependent.
 *  
 *  \see    timer.h, osapi.c
 */


#define __FILE_ID__  FILE_ID_0
#include "osi_kernel.h"
#include "w_queue.h"
#include "trnspt_thread.h"
#include "timer.h"
#include "trnspt_if.h"
#include "wlan_if.h"
#include "host_event_if.h"
#include "errors.h"


#define EXPIRY_QUE_SIZE  QUE_UNLIMITED_SIZE

/* The timer module structure (common to all timers) */
typedef struct 
{
    uint32_t   uContextId;     /* The ID allocated to this module on registration to context module */
    void *     hOperQueue;     /* Handle of the Operational-Queue */
    uint32_t   uTimersCount;   /* Number of created timers */
} TTimerModule;	

/* Per timer structure */
typedef struct 
{
    OsiTimer_t   hOsTimerObj;              /* The OS-API timer object handle */
    TQueNodeHdr  tQueNodeHdr;              /* The header used for queueing the timer */
    TTimerCbFunc fExpiryCbFunc;            /* The CB-function provided by the timer user for expiration */
    void *       hExpiryCbHndl;            /* The CB-function handle */
    uint32_t     uIntervalMsec;            /* The timer duration in Msec */
    uint32_t     bPeriodic;                /* If TRUE, restarted after each expiry */
} TTimerInfo;	


TTimerModule *gTimerModule = NULL;

/** 
 * \fn     tmr_Init 
 * \brief  Init required handles 
 * 
 * Init required handles and module variables, create the init-queue and 
 *     operational-queue, and register as the context-engine client.
 * 
 * \note    
 * \param  hOs       - Handle to Os Abstraction Layer
 * \param  hReport   - Handle to report module
 * \param  hContext  - Handle to context module
 * \return void        
 * \sa     
 */ 
int tmr_Init ()
{
    uint32_t     uNodeHeaderOffset;
    uint32_t ret = 0;
    /* allocate module object */
    gTimerModule = os_zalloc (sizeof(TTimerModule));

    if (!gTimerModule)
    {
        ASSERT_GENERAL(0);
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__TIMER, WLAN_ERROR_TYPE__MALLOC);
    }

    gTimerModule->uTimersCount  = 0;

    /* The offset of the queue-node-header from timer structure entry is needed by the queue */
    uNodeHeaderOffset = FIELD_OFFSET(TTimerInfo, tQueNodeHdr);

    gTimerModule->hOperQueue = que_Create (EXPIRY_QUE_SIZE,uNodeHeaderOffset);

    /* Register to the context engine and get the client ID */
    gTimerModule->uContextId = trnspt_RegisterClient (tmr_HandleExpiry,TRUE);
    TRANSPORT_PRINT_INIT("\n\rRegister Client:tmr_HandleExpiry uContextId :%d",gTimerModule->uContextId);

    return ret;

}


/** 
 * \fn     tmr_Destroy
 * \brief  Destroy the module.
 *
 * Free the module's queues and object.
 *
 * \note   This is NOT a specific timer destruction! (see tmr_DestroyTimer)
 * \return 0 on success or -1 on failure
 * \sa     tmr_Init
 */
int tmr_Destroy()
{
    TTimerInfo   *pDequeue = NULL;
    int ret;

    if (gTimerModule)
    {
        if (gTimerModule->hOperQueue)
        {
            /* Dequeue and free all queued timers */
            while (1)
            {
                trnspt_EnterCriticalSection ();
                pDequeue = (TTimerInfo   *)que_Dequeue (gTimerModule->hOperQueue);
                trnspt_LeaveCriticalSection();
                if (pDequeue == NULL)
                {
                    break;
                }
                else
                {
                    ret = tmr_DestroyTimer(pDequeue);
                    if (ret < 0)
                    {
                        return -1;
                    }
                    pDequeue = NULL;
                }
            }

            /* Delete timer */
            trnspt_EnterCriticalSection ();
            que_Destroy(gTimerModule->hOperQueue);
            trnspt_LeaveCriticalSection();
            gTimerModule->hOperQueue = NULL;
        }

        /* Free module object */
        os_free(gTimerModule);
        gTimerModule = NULL;
    }

    return 0;
}

/**
 * \fn     tmr_CreateTimer
 * \brief  Create a new timer
 * 
 * Create a new timer object, icluding creating a timer in the OS-API.  
 * 
 * \return void *    - The created timer handle
 * \sa     tmr_DestroyTimer
 */ 
void * tmr_CreateTimer ()
{
	TTimerModule *pTimerModule = (TTimerModule *)gTimerModule; /* The timer module handle */
    TTimerInfo   *pTimerInfo;  /* The created timer handle */


	/* Allocate timer object */
	pTimerInfo = os_zalloc(sizeof(TTimerInfo));

	if(NULL == pTimerInfo)
	{
	    return NULL;
	}

    /* Allocate OS-API timer, providing the common expiry callback with the current timer handle */
    osi_TimerCreate(&(pTimerInfo->hOsTimerObj), "TTimer", tmr_GetExpiry,(void *)pTimerInfo);

    /* Save the timer module handle in the created timer object (needed for the expiry callback) */
    pTimerModule->uTimersCount++;  /* count created timers */

    /* Return the created timer handle */
    return (void *)pTimerInfo;
}


/** 
 * \fn     tmr_DestroyTimer
 * \brief  Destroy the specified timer
 * 
 * Destroy the specified timer object, icluding the timer in the OS-API.  
 * 
 * \note   This timer destruction function should be used before tmr_Destroy() is executed!!
 * \param  hTimerInfo - The timer handle
 * \return 0 on success or -1 on failure
 * \sa     tmr_CreateTimer
 */ 
int tmr_DestroyTimer (void * hTimerInfo)
{
    TTimerInfo   *pTimerInfo   = (TTimerInfo *)hTimerInfo;                 /* The timer handle */     
    TTimerModule *pTimerModule = gTimerModule;                  /* The timer module handle */
    if (!pTimerInfo)
    {
        return -1;
    }


    osi_TimerDelete(&(pTimerInfo->hOsTimerObj));

    if (pTimerModule->uTimersCount>0)
    {
        pTimerModule->uTimersCount--;  /* update created timers number */
    }
    else
    {
        ASSERT_GENERAL(0);
        return -1;
    }

    /* Free the timer object */
    os_free (hTimerInfo);
	

    return 0;
}



/** 
 * \fn     tmr_StartTimer
 * \brief  Start a timer
 * 
 * Start the specified timer running.
 * 
 * \note   Periodic-Timer may be used by applications that serve the timer expiry 
 *           in a single context.
 *         If an application can't finish serving the timer expiry in a single context, 
 *           e.g. periodic scan, then it isn't recommended to use the periodic timer service.
 *         If such an application uses the periodic timer then it should protect itself from cases
 *            where the timer expires again before the previous timer expiry processing is finished!!
 * \param  hTimerInfo    - The specific timer handle
 * \param  fExpiryCbFunc - The timer's expiry callback function.
 * \param  paramsForCallbackFunc - The client's expiry callback function handle.
 * \param  uIntervalMsec - The timer's duration in Msec.
 * \param  bPeriodic     - If TRUE, the timer is restarted after expiry.
 * \return void
 * \sa     tmr_StopTimer, tmr_GetExpiry
 */ 
void tmr_StartTimer (void *       hTimerInfo,
                     TTimerCbFunc fExpiryCbFunc,
                     void *       paramsForCallbackFunc,
                     uint32_t     uIntervalMsec,
                     uint32_t         bPeriodic)
{
    TTimerInfo   *pTimerInfo   = (TTimerInfo *)hTimerInfo;                 /* The timer handle */     
    WlanEventError_t  error_event;
    int retVal = 0;

    /* Save the timer parameters. */
    pTimerInfo->fExpiryCbFunc            = fExpiryCbFunc;
    pTimerInfo->hExpiryCbHndl            = paramsForCallbackFunc;
    pTimerInfo->uIntervalMsec            = uIntervalMsec;
    pTimerInfo->bPeriodic                = bPeriodic;


    //the period is false as it is being retriggered through the generic callback
    retVal = osi_TimerStart(&(pTimerInfo->hOsTimerObj), uIntervalMsec, FALSE);
    if(OSI_OK != retVal)
    {
        Report("\n\r tmr_StartTimer: Failed to start timer. error number: %d", retVal);
        error_event.error_num = WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TIMER, WLAN_ERROR_TYPE__TIMER_START);
        error_event.module = WLAN_MODULE_TMR;
        error_event.severity = WLAN_SEVERITY_MID;
        Wlan_HostSendEvent(WLAN_EVENT_ERROR, (uint8_t*)&error_event, sizeof(WlanEventError_t));
    }
}


/** 
 * \fn     tmr_StopTimer
 * \brief  Stop a running timer
 * 
 * Stop the specified timer.
 * 
 * \note   When using this function, it must be considered that timer expiry may happen
 *           right before the timer is stopped, so it can't be assumed that this completely 
 *           prevents the timer expiry event!
 * \param  hTimerInfo - The specific timer handle
 * \return void
 * \sa     tmr_StartTimer
 */ 
void tmr_StopTimer (void * hTimerInfo)
{
    TTimerInfo   *pTimerInfo   = (TTimerInfo *)hTimerInfo;                 /* The timer handle */     
	TTimerModule *pTimerModule = gTimerModule; /* The timer module handle */
	WlanEventError_t  error_event;
	int retVal;

    if (!pTimerModule)
    {
        return;
    }
    /* Stop OS-API timer running */

    retVal = osi_TimerStop(&(pTimerInfo->hOsTimerObj));
    if (OSI_OK != retVal)
    {
         Report("\n\tmr_StopTimer: Failed to stop timer. error number: %d",retVal);
         error_event.error_num = WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TIMER, WLAN_ERROR_TYPE__TIMER_STOP);
         error_event.module = WLAN_MODULE_TMR;
         error_event.severity = WLAN_SEVERITY_MID;
         Wlan_HostSendEvent(WLAN_EVENT_ERROR, (uint8_t*)&error_event, sizeof(WlanEventError_t));
    }
    /* Clear periodic flag to prevent timer restart if we are in tmr_HandleExpiry context. */
    pTimerInfo->bPeriodic = FALSE;
}

/**
 * \fn     tmr_GetExpiry
 * \brief  Called by OS-API upon any timer expiry
 * 
 * This is the common callback function called upon expiartion of any timer.
 * It is called by the OS-API in timer expiry context and handles the transition
 *   to the driver's context for handling the expiry event.
 * 
 * \note   
 * \return void
 * \sa     tmr_HandleExpiry
 */ 
void tmr_GetExpiry (void * hTimerInfo)
{
	TTimerModule *pTimerModule = gTimerModule; /* The timer module handle */
	uint32_t key;

    /* Enter critical section */
	key = osi_EnterCritical();

    /* 
     * If the expired timer was started when the driver's state was Operational,
     *   insert it to the Operational-queue 
     */
    que_Enqueue (pTimerModule->hOperQueue, hTimerInfo);

    /* Leave critical section */
    osi_ExitCritical(key);


    /* Request switch to driver context for handling timer events */
    trnspt_RequestSchedule (pTimerModule->uContextId,FALSE);//perform tmr_HandleExpiry
}


/** 
 * \fn     tmr_HandleExpiry
 * \brief  Handles queued expiry events in driver context
 * 
 * This is the Timer module's callback that is registered to the ContextEngine module to be invoked
 *   from the driver task (after requested by tmr_GetExpiry through trnspt_RequestSchedule ()).
 * It dequeues all expiry events from the queue that correlates to the current driver state,
 *   and calls their users callbacks.
 * 
 * \note
 * \return void
 * \sa     tmr_GetExpiry
 */ 
void tmr_HandleExpiry ()
{
	TTimerModule *pTimerModule = gTimerModule; /* The timer module handle */
    TTimerInfo   *pTimerInfo;      /* The timer handle */
    uint32_t key;

    while (1)
    {
        /* Enter critical section */
        key = osi_EnterCritical();
    
        /* If current driver state is Operational, dequeue timer object from Operational-queue */
        pTimerInfo = (TTimerInfo *) que_Dequeue (pTimerModule->hOperQueue);

        osi_ExitCritical(key);

        /* If no more objects in queue, exit */
        if (!pTimerInfo) 
        {
            return;  /** EXIT Point **/
        }


        /* Call specific timer callback function */
        pTimerInfo->fExpiryCbFunc (pTimerInfo->hExpiryCbHndl);

        /* If the expired timer is periodic, start it again. */
        if (pTimerInfo->bPeriodic) 
        {
            tmr_StartTimer ((void *)pTimerInfo,
                            pTimerInfo->fExpiryCbFunc,
                            pTimerInfo->hExpiryCbHndl,
                            pTimerInfo->uIntervalMsec,
                            pTimerInfo->bPeriodic);
        }
    }
}


/** 
 * \fn     tmr_PrintModule / tmr_PrintTimer
 * \brief  Print module / timer information
 * 
 * Print the module's information / a specific timer information.
 * 
 * \note   
 * \param  The module / timer handle
 * \return void
 * \sa     
 */ 

#ifdef TI_DBG

void tmr_PrintModule (void * hTimerModule)
{
	TTimerModule *pTimerModule = (TTimerModule *)hTimerModule;

    if (!pTimerModule)
    {
        WLAN_OS_REPORT (("tmr_PrintModule(): ERROR - NULL timer!\n"));
        return;
    }
    /* Print module parameters */
    WLAN_OS_REPORT(("tmr_PrintModule(): uContextId=%d, bOperState=%d, uTwdInitCount=%d, uTimersCount=%d\n", 
        pTimerModule->uContextId, pTimerModule->bOperState, 
        pTimerModule->uTwdInitCount, pTimerModule->uTimersCount));

    /* Print Init Queue Info */
    WLAN_OS_REPORT(("tmr_PrintModule(): Init-Queue:\n")); 
    que_Print(pTimerModule->hInitQueue);

    /* Print Operational Queue Info */
    WLAN_OS_REPORT(("tmr_PrintModule(): Operational-Queue:\n")); 
    que_Print(pTimerModule->hOperQueue);
}

void tmr_PrintTimer (void * hTimerInfo)
{
#ifdef REPORT_LOG
    TTimerInfo   *pTimerInfo   = (TTimerInfo *)hTimerInfo;                 /* The timer handle */     

    WLAN_OS_REPORT(("tmr_PrintTimer(): uIntervalMs=%d, bPeriodic=%d, bOperStateWhenStarted=%d, uTwdInitCountWhenStarted=%d, hOsTimerObj=0x%x, fExpiryCbFunc=0x%x\n", 
        pTimerInfo->uIntervalMsec, pTimerInfo->bPeriodic, pTimerInfo->bOperStateWhenStarted, 
        pTimerInfo->uTwdInitCountWhenStarted, (uint32_t)pTimerInfo->hOsTimerObj, (uint32_t)pTimerInfo->fExpiryCbFunc));
#endif
}

#endif /* TI_DBG */

