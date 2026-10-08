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
/** \file   timer.h 
 *  \brief  timer module header file.                                  
 *
 *  \see    timer.c
 */

#ifndef _TIMER_H_
#define _TIMER_H_


/* The callback function type for timer clients */
typedef void (*TTimerCbFunc)(void *hCbHndl);


void tmr_ClearOperQueue (void * hTimerModule);


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
int tmr_Init ();

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
int tmr_Destroy();


/**
 * \fn     tmr_CreateTimer
 * \brief  Create a new timer
 *
 * Create a new timer object, icluding creating a timer in the OS-API.
 *
 * \note   This timer creation may be used only after tmr_Create() and tmr_Init() were executed!!
 * \return void *    - The created timer handle
 * \sa     tmr_DestroyTimer
 */
void * tmr_CreateTimer ();



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
int tmr_DestroyTimer (void * hTimerInfo);




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
                     uint32_t         bPeriodic);



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
void tmr_StopTimer (void * hTimerInfo);

/**
 * \fn     tmr_isStopped
 * \brief  verify if timer was stopped
 *
 * Stop the specified timer.
 *
 * \param  hTimerInfo - The specific timer handle
 * \return void
 * \sa     tmr_StartTimer
 */
int32_t tmr_isStopped(void * hTimerInfo);

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
void tmr_GetExpiry (void * hTimerInfo);


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
void tmr_HandleExpiry ();




#ifdef TI_DBG
void      tmr_PrintModule (void *hTimerModule);
void      tmr_PrintTimer (void *hTimerInfo);
#endif /* TI_DBG */


long long current_timestamp();
#endif  /* _TIMER_H_ */


