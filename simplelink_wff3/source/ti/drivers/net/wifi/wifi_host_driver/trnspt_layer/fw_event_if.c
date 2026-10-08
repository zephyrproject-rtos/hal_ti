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
/** \file  FwEvent.c
 *  \brief Handle firmware events
 * 
 *   
 * \par Description
 *      Call the appropriate event handler.
 *
 *  \see FwEvent.h
 */

#define __FILE_ID__  FILE_ID_74

#include <osi_type.h>
#include <osi_kernel.h>
#include "trnspt_thread.h"
#include <txn_bus_drv.h>
#include "wlan_irq_adapt.h"
#include "trnspt_if.h"
#include <fw_event_if.h>
#include "wlan_if.h"
#include "host_event_if.h"
#include "errors.h"


#define RX_BYTE_COUNT_MASK 0xFFFF

/*
 * Address of FW-Status structure in FW memory ==> Special mapping, see note!!
 *
 * Note: This structure actually includes two separate areas in the FW:
 *          1) Interrupt-Status register - a 32 bit register (clear on read).
 *          2) FW-Status structure - 64 bytes memory area
 *       The two areas are read in a single transaction thanks to a special memory 
 *           partition that maps them as contiguous memory.
 */


/* The FwEvent module's main structure */


static void       FwEvent_NewEvent       (void* hCbHndl);
void       FwEvent_StateMachine   ();
extern ETxnStatus FwEvent_SmHandleEvents (TFwEvent *pFwEvent);
extern ETxnStatus FwEvent_CallHandlers   (TFwEvent *pFwEvent);
extern ETxnStatus FwEvent_AllocateStatus (TFwEvent *pFwEvent);
extern void hostNabISR(void);

TFwEvent *gFwEvent = NULL;


#ifdef PRIODIC_INTERRUPT
static void FwEvent_HandlePollingIrq (void * hFwEvent);
#endif



/*
 * \brief   Read interrupt info from FW
 *
 * \param   hFwEvent  - FwEvent Driver handle
 * \return  void
 *
 * \par Description
 *
 * Indicate the TwIf that HW is available and initiate transactions for reading
 *     the Interrupt status and the FW status.
 *
 * \sa
 */
#if DEBUG_FW_EVENT
extern void printCoreStatus(void *core,int num);
#endif

ETxnStatus FwEvent_SmReadIntrInfo (TFwEvent *pFwEvent)
{
    ETxnStatus eStatus;

#ifdef TWIF_FW_NEED_WAKE_UP
    /* Indicate that the chip is awake (since it interrupted us) */
    twIf_HwAvailable();
#endif
    /*
     * Read FW-Status structure from HW ==> Special mapping, see note!!
     *
     * Note: This structure actually includes two separate areas in the FW:
     *          1) Interrupt-Status register - a 32 bit register (clear on read).
     *          2) FW-Status structure - 64 bytes memory area
     *       The two areas are read in a single transaction thanks to a special memory
     *           partition that maps them as contiguous memory.
     */
    eStatus = twIf_TransactReadFwStatus (&(pFwEvent->tFwStatusTxn.tTxnStruct));
#if DEBUG_FW_EVENT
    printCoreStatus(pFwEvent->tFwStatusTxn.tFwStatus,3);
#endif
    wlan_IRQEnableInt();

    /* Return the status of the FwStatus read (complete, pending or error) */
    return eStatus;
}

/*
 * \brief	Destroys the FwEvent object
 * 
 * \param  hFwEvent  - The object to free
 * \return 0
 * 
 * \par Description
 * Calling this function destroys a FwEvent object
 * 
 * \sa FwEvent_Create
 */
int fwEvent_Destroy()
{
    int i;

    if (gFwEvent)
    {
        for(i = 0 ; i < 4 ; i ++)
        {
            //free all threads waiting on this object
            osi_SyncObjSignal(&(gFwEvent->FwEventGeneralObj[i]));
            osi_SyncObjDelete(&(gFwEvent->FwEventGeneralObj[i]));
        }
        os_free(gFwEvent->rxTxBuffer);
        os_free(gFwEvent->tFwStatusTxn.tFwStatus);
        os_free (gFwEvent);
        gFwEvent = NULL;
    }

#ifdef PRIODIC_INTERRUPT
	if(pFwEvent->hPollTimer)
	{
		os_timerDestroy(pFwEvent->hOs, pFwEvent->hPollTimer);
	}
#endif

    return 0;
}


void fwEvent_Signal(uint32_t hint_mask)
{
    TFwEvent *pFwEvent = gFwEvent;
    uint8_t event;

    //hint_mask may contain more than one event
   if ( hint_mask & HINT_ROM_LOADER_INIT_COMPLETE)
   {
       event  = 0;
       osi_SyncObjSignal(&(pFwEvent->FwEventGeneralObj[event]));
   }
   if ( hint_mask & HINT_SECOND_LOADER_INIT_COMPLETE)
   {
       event  = 1;
       osi_SyncObjSignal(&(pFwEvent->FwEventGeneralObj[event]));
   }
   if( hint_mask & HINT_FW_WAKEUP_COMPLETE)
   {
       event  = 2;
       osi_SyncObjSignal(&(pFwEvent->FwEventGeneralObj[event]));
   }
   if( hint_mask & HINT_FW_DOWNLOADING_INI_PARAMS_COMPLETE)
   {
       event = 3;
       osi_SyncObjSignal(&(pFwEvent->FwEventGeneralObj[event]));
   }
}


/*
 * this function indicates if the driver is in init state
 * used to mask fwEvents that shouldn't be applied during init
 * isDuringInit - 1 during init - 0 not during init
 */

void fwEvent_SetDuringInit(uint8_t isDuringInit, uint32_t commandsEventsSize)
{
    gFwEvent->isDuringInit = isDuringInit;

    fwEvent_set_cmdEventSize(commandsEventsSize);
}




int fwEvent_Wait(int timeout, uint32_t event)
{
    TFwEvent *pFwEvent = gFwEvent;

    switch(event)
    {
    case HINT_ROM_LOADER_INIT_COMPLETE:
        event  = 0;
        break;
    case HINT_SECOND_LOADER_INIT_COMPLETE:
        event  = 1;
        break;
    case HINT_FW_WAKEUP_COMPLETE:
        event  = 2;
        break;
    case HINT_FW_DOWNLOADING_INI_PARAMS_COMPLETE:
        event = 3;
        break;
    }

    if( OSI_OPERATION_FAILED ==  osi_SyncObjWait(&(pFwEvent->FwEventGeneralObj[event]), timeout) )
    {
        return -1;
    }

    return 0;
}



/*
 * \brief   FW interrupt handler, just switch to WLAN context for handling
 *
 * \param   hFwEvent - FwEvent Driver handle
 * \return  void
 *
 * \par Description
 * Called by the FW-Interrupt ISR (external context!).
 * Requests the context engine to schedule the driver task for handling the FW-Events.
 *
 * \sa
 */
int FwEvent_irq_handler ()
{
    TFwEvent *pFwEvent = gFwEvent;

    if(pFwEvent->eSmState != FWEVENT_STATE_STOPPED)
    {
        trnspt_RequestSchedule(pFwEvent->uContextId, TRUE);
        wlan_IRQDisableOnIRQHandler();//call adaptation layer
    }
    else
    {
        ASSERT_GENERAL(0);
        return OSI_OPERATION_FAILED;
    }
    return OSI_OK;
}

uint8_t *fwEvent_GetRxTxBuffer()
{
    return gFwEvent->rxTxBuffer;
}

/*
 * \brief	Config the FwEvent module object
 * 
 * \param  hFwEvent  - FwEvent Driver handle
 * \param  hTWD  - Handle to TWD module
 * \return 0
 * 
 * \par Description
 * From hTWD we extract : hOs, hReport, hTwIf, hContext,
 *      hHealthMonitor, hEventMbox, hCmdMbox, hRxXfer, 
 *      hTxHwQueue, hTxResult
 * In this function we also register the FwEvent to the context engine
 * 
 * \sa
 */
int fwEvent_Init (uint32_t rxTxBufferSize, uint32_t commandsEventsSize)
{
    TFwEvent  *pFwEvent;
    int i;

    wlan_IRQDeinit();

    gFwEvent = os_malloc (sizeof(TFwEvent));
    if (gFwEvent == NULL)
    {
        ASSERT_GENERAL(0);
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__FW_EVENTS, WLAN_ERROR_TYPE__MALLOC);
    }

    os_memset (gFwEvent, 0, sizeof(TFwEvent));

    pFwEvent = gFwEvent;

    if(FwEvent_AllocateStatus(pFwEvent) != TXN_STATUS_OK)
    {
        ASSERT_GENERAL(0);
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__FW_EVENTS, WLAN_ERROR_TYPE__MALLOC);
    }
    pFwEvent->rxTxBuffer = os_malloc(rxTxBufferSize);
    if(NULL == pFwEvent->rxTxBuffer)
    {
        ASSERT_GENERAL(0);
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__FW_EVENTS, WLAN_ERROR_TYPE__MALLOC);
    }
    pFwEvent->rxTxBufSize = rxTxBufferSize;
    pFwEvent->eventSize = commandsEventsSize;
    pFwEvent->eSmState          = FWEVENT_STATE_IDLE;
    pFwEvent->bIntrPending      = FALSE;
    pFwEvent->uNumPendHndlrs    = 0;
    pFwEvent->uEventMask        = 0;
    pFwEvent->uEventVector      = 0;

    /* 
     *  Register the FwEvent to the context engine and get the client ID.
     *  The FwEvent() will be called from the context_DriverTask() after scheduled
     *    by a FW-Interrupt (see FwEvent_irq_handler()).
     */
    pFwEvent->uContextId = trnspt_RegisterClient(FwEvent_NewEvent,TRUE);
    TRANSPORT_PRINT_INIT("\n\rRegister Client: FwEvent_NewEvent uContextId :%d",pFwEvent->uContextId);

    fwEvent_SetInitMask(pFwEvent);

    for(i = 0 ; i < 4 ; i ++)
    {
        osi_SyncObjCreate(&(pFwEvent->FwEventGeneralObj[i]));
    }

    return 0;
}

/*
 * \brief   The CB sets the command size
 *
 * \param   commandsEventsSize - the new size to set
 * \return  void
 *
 * \par Description
 * the BTL require different command size than the FW,
 * this enables to replace the command size after SW dnld is finished.
 * \sa
 */
void fwEvent_set_cmdEventSize (uint32_t commandsEventsSize)
{
    TFwEvent  *pFwEvent;

    pFwEvent = gFwEvent;

    pFwEvent->eventSize = commandsEventsSize;
}




/*
 * \brief   The CB called in the driver context upon new interrupt
 * 
 * \param   hFwEvent - FwEvent Driver handle
 * \return  void
 * 
 * \par Description
 * Called by the context module after scheduled by FwEvent_irq_handler().
 * If IDLE, start the SM, and if not just indicate pending event for later.
 * 
 * \sa
 */
static void FwEvent_NewEvent (void* hCbHndl)
{
    TFwEvent *pFwEvent = gFwEvent;


    /* If the SM is idle, call it to start handling new events */
    if (pFwEvent->eSmState == FWEVENT_STATE_IDLE) 
    {
        FWEVENT_PRINT("\n\rFwEvent_NewEvent: Start SM\n\r");

        FwEvent_StateMachine();
        FWEVENT_PRINT("\n\rFwEvent_NewEvent: done SM\n\r");
    }
    /* Else - SM is busy so set flag to handle it when finished with current events */
    else 
    {
       pFwEvent->bIntrPending = TRUE;
        FWEVENT_PRINT("FwEvent_NewEvent: SM busy, set IntrPending flag bIntrPending:%d\n\r",pFwEvent->bIntrPending);

    }


}


/*
 * \brief	FW-Event state machine
 * 
 * \param  hFwEvent  - FwEvent Driver handle
 * \return void
 * 
 * \par Description
 * 
 * Process the current FW events in a sequence that may progress in the same context,
 *     or exit if pending an Async transaction, which will call back the SM when finished.
 *
 * \sa
 */
//this function is been called after any status read
void FwEvent_StateMachine ()
{
    TFwEvent *pFwEvent = gFwEvent;
    ETxnStatus  eStatus = TXN_STATUS_ERROR; /* Set to error to detect if used uninitialized */
    WlanEventError_t error_event;
    static uint32_t previous_hint = 0;
	/* 
	 * Loop through the states sequence as long as the process is synchronous.
	 * Exit when finished or if an Asynchronous process is required. 
     * In this case the SM will be called back upon Async operation completion. 
	 */
	while (1)
	{
		switch (pFwEvent->eSmState)
		{
			/* STOPPED: Shouldn't arrive here if stopped --> ERROR */
			case FWEVENT_STATE_STOPPED:
				eStatus = TXN_STATUS_ERROR;
				break;
            /* IDLE: Update TwIf and read interrupt info from FW */
            case FWEVENT_STATE_IDLE:
            {
                FwStatus_t *core_status = (FwStatus_t *)(pFwEvent->tFwStatusTxn.tFwStatus);
                previous_hint = core_status->host_interrupt_status;

                twIf_Awake();
                pFwEvent->eSmState = FWEVENT_STATE_WAIT_INTR_INFO;
                CORE_STATUS_PRINT("\n\rcore_status ! FWEVENT_STATE_IDLE, send read req core status ");
                eStatus = FwEvent_SmReadIntrInfo (pFwEvent);
                break;
            }
            /* WAIT_INTR_INFO: We have the interrupt info so call the handlers accordingly */
            case FWEVENT_STATE_WAIT_INTR_INFO:
            {
                FwStatus_t *core_status = (FwStatus_t *)(pFwEvent->tFwStatusTxn.tFwStatus);
                if ((core_status->host_interrupt_status | previous_hint) & HINT_COMMAND_COMPLETE )
                {
                    CORE_STATUS_PRINT("\n\rcore_status ! FWEVENT_STATE_WAIT_INTR_INFO, host_interrupt_status: 0x%x , rx_status :%d previous_hint:0x%x tsf:0x%x\n\r",
                            core_status->host_interrupt_status,
                            core_status->rx_status & RX_BYTE_COUNT_MASK,
                            previous_hint,
                            core_status->tsf);
                }

                core_status->host_interrupt_status |= previous_hint;

                eStatus = FwEvent_SmHandleEvents (pFwEvent);
                previous_hint = 0;
                /* If state was changed to IDLE by recovery or stop process, exit (process terminated) */
                if (pFwEvent->eSmState == FWEVENT_STATE_IDLE) 
                {
                    return;
                }
                pFwEvent->eSmState = FWEVENT_STATE_WAIT_HANDLE_COMPLT;
                break;
            }
            /* WAIT_HANDLE_COMPLT: Current handling is completed. */
            case FWEVENT_STATE_WAIT_HANDLE_COMPLT:
            {
                /* If pending interrupt, read interrupt info (back to WAIT_INTR_INFO state) */
                //in the scenario where FwEvent_StateMachine runs on the transport thread
                //bIntrPending will be always false
                if (pFwEvent->bIntrPending) 
                {
                    /* We are starting handling of pending interrupt request*/
                    /* Clear Pendig and Set InProgress flags*/
                    pFwEvent->bIntrPending = FALSE;
                    FWEVENT_PRINT("\n\r interrupt received bIntrPending:%d\n\r",pFwEvent->bIntrPending);
                    eStatus = FwEvent_SmReadIntrInfo (pFwEvent);
                    pFwEvent->eSmState = FWEVENT_STATE_WAIT_INTR_INFO;
                }
                /* Else - all done so release TwIf to sleep and exit */
                else 
                {
                    twIf_Sleep();
                    pFwEvent->eSmState = FWEVENT_STATE_IDLE;

                    FWEVENT_PRINT("FwEvent_StateMachine: Completed, NewState=%d, Status=%d, IntrPending=%d\n\r", pFwEvent->eSmState, eStatus, pFwEvent->bIntrPending);

                    /**** Finished all current events handling so exit ****/
                    return;
                }
                break;
            }

        }  /* switch */

		FWEVENT_PRINT("FwEvent_StateMachine: NewState=%d, Status=%d, IntrPending=%d\n\r", pFwEvent->eSmState, eStatus, pFwEvent->bIntrPending);
        
		/* If last status is Pending, exit the SM (to be called back upon Async operation completion) */
		if (eStatus == TXN_STATUS_PENDING)
		{
			return;
		}

        /* If error occured, stop the process and exit (should be cleaned by recovery process) */
		else if (eStatus == TXN_STATUS_ERROR)
		{
   		    FW_EVENT_HANDLE_PRINT_ERROR("FwEvent_StateMachine: NewState=%d, Status=%d, IntrPending=%d, EventVector=0x%x, EventMask=0x%x\n\r", pFwEvent->eSmState, eStatus, pFwEvent->bIntrPending, pFwEvent->uEventVector, pFwEvent->uEventMask);
            ASSERT_GENERAL(0);
            error_event.error_num = WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__FW_EVENTS, WLAN_ERROR_TYPE__TRANSACTION);
            error_event.module = WLAN_MODULE_FWEVENT;
            error_event.severity = WLAN_SEVERITY_MID;
            Wlan_HostSendEvent(WLAN_EVENT_ERROR, (uint8_t*)&error_event, sizeof(WlanEventError_t));
			return;
		}

        /* If we got here the status is COMPLETE so continue in the while loop to the next state */

	}  /* while */
}


/*
 * \brief	Called by any handler that completed after pending
 * 
 * \param  hFwEvent  - FwEvent Driver handle
 *
 * \par Description
 *
 * Decrement pending handlers counter and if 0 call the SM to complete its process.
 * 
 * \sa
 */
void FwEvent_HandlerCompleted ()
{
    TFwEvent *pFwEvent = gFwEvent;

    /* Decrement the pending handlers counter and if zero call the SM to complete the process */
    pFwEvent->uNumPendHndlrs--;
    if (pFwEvent->uNumPendHndlrs == 0) 
    {
        FwEvent_StateMachine ();
    }
}


/*
 * \brief	Translate host to FW time (Usec)
 * 
 * \param  hFwEvent  - FwEvent Driver handle
 * \param  uHostTime - The host time in MS to translate
 *
 * \return FW Time in Usec
 * 
 * \par Description
 * 
 * \sa
 */
uint32_t FwEvent_TranslateToFwTime (uint32_t uHostTime)
{
    TFwEvent *pFwEvent = gFwEvent;
    uint32_t ret = (uHostTime * 1000) - pFwEvent->uFwTimeOffset;
    return ret;
}




/*
 * \brief	Stop & reset FwEvent (called by the driver stop process)
 * 
 * \param  hFwEvent  - FwEvent Driver handle
 * \return 0
 * 
 * \par Description
 *
 * \sa
 */
int FwEvent_Stop ()
{
    TFwEvent *pFwEvent = gFwEvent;

    pFwEvent->eSmState       = FWEVENT_STATE_STOPPED;
    pFwEvent->bIntrPending  = FALSE;
    pFwEvent->uNumPendHndlrs = 0;
    pFwEvent->uEventMask     = 0;
    pFwEvent->uEventVector   = 0;    

    /* Allow the system to sleep in case we kept it awake */
    twIf_Sleep();

    return 0;
}


#ifdef TI_DBG

void FwEvent_PrintStat (void * hFwEvent)
{
#ifdef REPORT_LOG
    TFwEvent *pFwEvent = gFwEvent;
    FwStatus_t *fwStat = &pFwEvent->tFwStatusTxn.tFwStatus; 
	int i;

    
    WLAN_OS_REPORT(("Print FW event module info\n"));
    WLAN_OS_REPORT(("==========================\n"));
    WLAN_OS_REPORT(("uEventVector   = 0x%x\n", pFwEvent->uEventVector));
    WLAN_OS_REPORT(("uEventMask     = 0x%x\n", pFwEvent->uEventMask));
    WLAN_OS_REPORT(("eSmState       = %d\n",   pFwEvent->eSmState));
    WLAN_OS_REPORT(("bIntrPending   = %d\n",   pFwEvent->bIntrPending));
    WLAN_OS_REPORT(("uNumPendHndlrs = %d\n",   pFwEvent->uNumPendHndlrs));
    WLAN_OS_REPORT(("uFwTimeOffset  = %d\n",   pFwEvent->uFwTimeOffset));
    WLAN_OS_REPORT(("------------- Last FwStatus ----------\n"));
    WLAN_OS_REPORT(("counters   = 0x%08x\n", fwStat->counters));
    for (i = 0; i < NUM_RX_PKT_DESC; i++)
    {
		WLAN_OS_REPORT(("rxPktsDesc[%1d] = 0x%08x\n", i, fwStat->rxPktsDesc[i]));
    }

    WLAN_OS_REPORT(("fwLocalTime = 0x%08x\n", fwStat->fwLocalTime));
    WLAN_OS_REPORT(("LinkPsBitmap      = 0x%08x\n", fwStat->linkPsBitmap));

#endif /*REPORT_LOG*/
}

#endif  /* TI_DBG */


  
