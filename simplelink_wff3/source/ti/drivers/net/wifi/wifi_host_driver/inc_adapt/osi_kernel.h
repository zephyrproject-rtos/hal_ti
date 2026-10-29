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
/*-----------------------------------------------------------------------------

  FILENAME:       osi.h

  DESCRIPTION:    freertos wrapper, includes freertos definitions, macros and APIs

  ----------------------------------------------------------------------------- */
#ifndef __OSI_H__
#define __OSI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#if defined(__clang__) || (__GNUC__)
#include <sys/types.h>
#endif
#include "user_errno.h"
#include <osi_type.h>

#include "gtrace.h"

#define HOOK(a)

#define ATTRIBUTE __attribute__ ((used))

extern int Report(const char *pcFormat,...);
extern int ReportWithTime(const char *pcFormat,...);


#ifndef assert
extern void assert(unsigned int condition);
#endif

//#define ASSERT_GENERAL assert
extern void ASSERT_GENERAL(unsigned int condition);

/************************************************************************
 *                                                                      *
 *              DEBUG SECTION FOR MALLOC/FREE                           *
 *                                                                      *
 ************************************************************************/
//#define PRINT_DBG_MALLOC_FREE
//#define PRINT_DBG_TOTAL_MALLOC_FREE
//#define COLLECT_HEAP_DEBUG_INFO //this is for analyzing heap corruption, can be remarked after stabilize the app
//#define ASSERT_ON_MALLOC_FAIL
#undef ASSERT_ON_MALLOC_FAIL


#ifdef COLLECT_HEAP_DEBUG_INFO

#define HEAP_DBG_SIZE 60
#define HEAP_DBG_VPORT_SIZE 100

typedef struct
{
    uint32_t size;
    uint32_t lr;
    uint32_t ptr;
    uint32_t dbg_offset;
}heap_debug_vport_t;

typedef struct
{
    uint8_t isFree:1;
    uint8_t isUsed:1;
    uint8_t isfinshed:1;
    uint8_t allocFail:1;
    uint8_t funcId:4;
    uint32_t size;
    uint32_t lr;
    uint32_t ptr;
    uint32_t ptrOld;
}heap_debug_t;


extern heap_debug_t heapdebug[];
extern heap_debug_vport_t heapDebugVport[];

extern uint32_t dbg_offset;
extern uint32_t dbg_vport_offset;


extern int ReportNoLock(const char *pcFormat,...);
#endif


/*-----------------------------------------------------------------------------
    Basic macros
  ----------------------------------------------------------------------------- */

#ifdef NULL
#else
#define NULL     0
#endif /* NULL */

#ifdef FALSE
#else
#define FALSE  0
#endif /* FALSE */

#ifdef TRUE
#else
#define TRUE   (!FALSE)
#endif /* TRUE */


#ifdef OK
#else
#define OK  (0)
#endif /* OK */

#ifdef NOK
#else
#define NOK  (1)
#endif /* NOK */


#ifdef _UINT8
#else
#define _UINT8
typedef unsigned char   UINT8;
#endif

#ifdef _UINT16
#else
#define _UINT16
typedef unsigned short  UINT16;
#endif

#ifdef _WIN32
typedef unsigned int    UINT32, *PUINT32;
typedef signed   int    INT32, *PINT32;
#else
#ifdef _UINT32
#else
#define _UINT32
typedef unsigned long   UINT32;
#endif

#ifdef _UINT64
#else
#define _UINT64
typedef unsigned long long   UINT64;
#endif

#ifdef _INT32
#else
#define _INT32
typedef signed   long   INT32;
#endif

#endif /* _WIN32 */

#ifdef _INT8
#else
#define _INT8
typedef signed   char   INT8;
#endif

#ifdef _INT16
#else
#define _INT16
typedef signed   short  INT16;
#endif

#ifdef _INT64
#else
#define _INT64
typedef signed   long   INT64;
#endif


#ifdef _BOOLEAN
#else
#define _BOOLEAN
typedef unsigned char   BOOLEAN;
#endif


#ifdef __arm
#define PACKED  __packed
#ifndef INLINE
#define INLINE  __inline
#endif
#else
#define PACKED
#ifndef INLINE
#define INLINE inline
#endif /* INLINE */
#endif /* __arm */


/*-----------------------------------------------------------------------------
    Prototypes
  ----------------------------------------------------------------------------- */

/*******************************************************************************

    GENERAL

*******************************************************************************/
uint32_t osi_EnterCritical(void);
uint32_t osi_ExitCritical(uint32_t ulKey);
#define osi_EnterCriticalSection(void)               osi_EnterCritical(void)
#define osi_ExitCriticalSection(RestoreValue) osi_ExitCritical (RestoreValue)

/************************** GET LR HELPER FUNCTION ************************/
#define __ASM __asm /*!< asm keyword for GNU Compiler */
#define __INLINE inline /*!< inline keyword for GNU Compiler */

#if defined(__clang__) || (__GNUC__)
#define __STATIC_INLINE static inline

/**
\brief Get Link Register
\details Returns the current value of the Link Register (LR).
\return LR Register value
*/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_LR(void)
{
    uint32_t result;

    __ASM volatile ("MOV %0, LR\n" : "=r" (result) );
    return(result);
}
#endif

/************************************************************************/

/*******************************************************************************

    Operating System Configuration

********************************************************************************/
// Periodic/one shot configuration (to be used in StartTimer API)
#define OSI_ONE_SHOT_TIMER                      (0)


/*******************************************************************************

    Types and Constants

********************************************************************************/
typedef enum
{
  OSI_OK,
  OSI_OPERATION_FAILED,
  OSI_ABORTED,
  OSI_INVALID_PARAMS,
  OSI_MEMORY_ALLOCATION_FAILURE,
  OSI_TIMEOUT,
  OSI_EVENTS_IN_USE,
  OSI_EVENT_OPEARTION_FAILURE,
  OSI_NO_SEMAPHORE_INSTANCE_AVAILABLE,
  OSI_EXCEEDED_SEMAPHORE_COUNT,
  OSI_DELETED,
  OSI_FILESYS_FAILURE
}OsiReturnVal_e;


typedef void* OsiThread_t;

typedef struct
{
    void *osTimerHandler; //os timer handler
    void *callBackFunc; //callback function for the expiry - as some OS's like freeRTOS gives the handle to the timer in the callback function parameters
    void *params; //parameters for the callback functions - as some OS's like freeRTOS gives the handle to the timer in the callback function parameters
}OsiTimer_t;

typedef long os_time_t;
/**
 * os_sleep - Sleep (sec, usec)
 * @sec: Number of seconds to sleep
 * @usec: Number of microseconds to sleep
 */
void os_sleep(os_time_t sec, os_time_t usec);

struct os_time {
    os_time_t sec;
    os_time_t usec;
};

struct os_tm {
    int sec; /* 0..59 or 60 for leap seconds */
    int min; /* 0..59 */
    int hour; /* 0..23 */
    int day; /* 1..31 */
    int month; /* 1..12 */
    int year; /* Four digit year */
};

struct os_reltime {
    os_time_t sec;
    os_time_t usec;
};

typedef enum
{
    OSI_FLASH_CONNECTIVITY_FW_SLOT_1 = 1,
    OSI_FLASH_CONNECTIVITY_FW_SLOT_2
}osiFlashFwSlot_e;

typedef enum
{
    OSI_FILESYSTEM_SET_CONNECTIVITY_FW_CONTAINER
}osiFileSetType;

typedef enum
{
    OSI_FILESYSTEM_GET_CONNECTIVITY_FW_CONTAINER
}osiFileGetType;

typedef void (*P_OSI_TASK_ENTRY)(void* pValue);
typedef void (*P_THREAD_ENTRY_FUNCTION)(void* pParam);
typedef void (*P_TIMER_EXPIRY_LEGACY_FUNCTION)(void* pParam);

#define OSI_WAIT_FOREVER            (0xFFFFFFFF)
#define OSI_NO_WAIT                 (0x00000000)
#define OSI_WAIT_FOR_SECOND         (1000)
#define OSI_MIN_THREAD_STACK_SIZE   (256)
#define OSI_WAIT_FOR_MINUTES        (60000)
#define OSI_WAIT_FOR_COMMAND_COMPLETE (100)
#define OSI_WAIT_FOR_SCAN_MS        (30000)



#define OSI_FLAG_FROM_INTR            (0)
#define OSI_FLAG_NOT_FROM_INTR        (1)

typedef uint32_t OsiTime_t;
typedef void* OsiMsgQ_t;
typedef void* OsiSyncObj_t;
typedef void* OsiLockObj_t;
typedef void* OsiTaskHandle;

typedef struct
{
    void           *Semaphore;
    uint32          max_count;  // Max multiplicity of the semaphore.
                                // For some reason, ThreadX does not implement max_count
                                // in its own implementation, so we do this here..
}OsiSemaphoreObj_t;



/**
 * Returns the values of the system clock in milliseconds.
 * The system clock is set to 0 during initialization.
 *
 * @note This value can be used for timestamping, but please note that
 *       the accuracy of the value depends on the system tick interval,
 *       which is usually set to 10 milliseconds.
 *
 * @param none
 * @return OsiTime_t, the current time in milliseconds
 */
OsiTime_t osi_GetTimeMS();


/**
 * @brief Creates an application thread.
 *
 * @param pThread Pointer to the thread control block.
 * @param pThreadName Pointer to the name of the thread.
 * @param StackSize The size of the stack in bytes.
 * @param Priority The priority of the thread.
 *                 0 = Highest Priority Level.
 *                 31 = Lowest Priority Level.
 * @param pEntryFunc The entry function of the thread.
 *                   A thread that returns from this function enters the "complete" state.
 *                   The osi_ThreadDelete function must be called to release all resources properly.
 * @param pParam Parameter that will be passed to the entry function.
 * @param AutoStart Specify if the thread starts at the ready state or suspended state.
 *                  If this value is FALSE, the thread will be in a suspended state after creation and won't run.
 *                  The osi_ThreadResume function should be called to run the thread.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_ThreadCreate(OsiThread_t* pThread,
                                char* pThreadName,
                                uint32_t StackSize,
                                uint32_t Priority,
                                P_THREAD_ENTRY_FUNCTION pEntryFunc,
                                void* pParam);

/**
 * @brief Deletes a thread.
 *
 * Before calling this function, the thread must terminate by returning from its entry function.
 * This function cannot be called from a thread attempting to delete itself.
 *
 * @param pThread Pointer to the thread control block.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_ThreadDelete(OsiThread_t* pThread);

/**
 * @brief Gets a thread handle of the current thread that is running.
 *
 * @return OsiThread_t The thread handle of the current thread.
 */
OsiThread_t osi_GetCurrentThread(void);

/**
 * @brief Gets the current free size of the heap.
 *
 * @return size_t the number of free bytes on the heap.
 */
size_t osi_GetFreeHeapSize();

/**
 * @brief Gets the minimum free stack words remaining for the current task since it started.
 *
 * @return uint32_t high watermark in words (minimum free stack remaining).
 */
uint32_t osi_GetStackHighWaterMark(void);

/**
 * @brief Suspends the calling thread for the specified number of seconds.
 *
 * @param sec The number of seconds to suspend the calling thread.
 *            Note that this value is in seconds, but the actual resolution of the sleep depends on the interval of the operating system timer.
 *            In all cases, the sleep duration won't be less than this number.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_Sleep(OsiTime_t sec);

/**
 * @brief Suspends the calling thread for the specified number of microseconds.
 *
 * @param usec The number of microseconds to suspend the calling thread.
 *             Note that this value is in microseconds, but the actual resolution of the sleep depends on the interval of the operating system timer.
 *             In all cases, the sleep duration won't be less than this number.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_uSleep(OsiTime_t usec);

/**
 * @brief Creates an application timer.
 *
 * @param pTimer Pointer to the timer control block.
 * @param pTimerName Pointer to the name of the timer.
 * @param pExpiryFunc Function to call when the timer expires.
 * @param pParam Parameter that would be passed to the function.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_TimerCreate(OsiTimer_t* pTimer,
                               char* pTimerName,
                               P_TIMER_EXPIRY_LEGACY_FUNCTION pExpiryFunc,
                               void* pParam);

/**
 * @brief Deletes an application timer.
 *
 * @param pTimer Pointer to the timer control block.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_TimerDelete(OsiTimer_t* pTimer);

/**
 * @brief Starts an application timer.
 *
 * @param pTimer Pointer to the timer control block.
 * @param DurationMiliSec The number of milliseconds for timer expiration.
 *                        Note that this value is in milliseconds, but the actual resolution of the duration depends on the interval of the operating system timer.
 *                        In all cases, the duration won't be less than this value.
 * @param Periodic Determines whether this execution should run the timer repeatedly (periodic timer).
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_TimerStart(OsiTimer_t* pTimer,
                              OsiTime_t DurationMiliSec,
                              BOOLEAN Periodic);

/**
 * @brief Stops an application timer.
 *
 * @param pTimer Pointer to the timer control block.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_TimerStop(OsiTimer_t* pTimer);

/**
 * @brief Return if timer is active or not.
 *
 * @param pTimer Pointer to the timer control block.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_TimerIsActive(OsiTimer_t* pTimer);

/**
 * @brief Returns the remaining duration until the next expiry in milliseconds.
 *
 * @param pTimer Pointer to the timer control block.
 *
 * @return OsiTime_t The remaining duration in milliseconds.
 */
OsiTime_t osi_TimerGetRemainingTime(OsiTimer_t* pTimer);

/**
 * @brief Creates a message queue, typically used for inter-thread communication.
 *
 * @param pMsgQ Pointer to the message queue control block.
 * @param pMsgQName Pointer to the name of the message queue.
 * @param MsgSize The size of the message.
 *                NOTICE: The message size must be smaller than 16.
 * @param MaxMsgs The maximum number of messages.
 * @param pQueue Pointer to the message queue memory (MsgSize * MaxMsgs).
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_MsgQCreate(OsiMsgQ_t* pMsgQ,
                              char* pMsgQName,
                              uint32_t MsgSize,
                              uint32_t MaxMsgs);

/**
 * @brief Deletes a specific message queue.
 *
 * All threads suspended waiting for a message from this queue are resumed with an error return value.
 *
 * @param pMsgQ Pointer to the message queue control block.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_MsgQDelete(OsiMsgQ_t* pMsgQ);

/**
 * @brief Writes a message to a specific message queue.
 *
 * Notice that the message is copied to the queue from the memory area specified by the pMsg pointer.
 * THIS FUNCTION COULD BE CALLED FROM ISR AS LONG AS THE TIMEOUT PARAMETER IS SET TO "OSI_NO_WAIT".
 *
 * @param pMsgQ Pointer to the message queue control block.
 * @param pMsg Pointer to the message.
 * @param Timeout Numeric value specifies the maximum number of milliseconds to stay suspended while waiting for available space for the message.
 * @param  flags, currently unused
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_MsgQWrite(OsiMsgQ_t* pMsgQ, void* pMsg , OsiTime_t Timeout, uint8_t flags);
/**
 * @brief Retrieves a message from the specified message queue.
 *
 * The retrieved message is copied from the queue into the memory area specified by the pMsg pointer.
 *
 * @param pMsgQ Pointer to the message queue control block.
 * @param pMsg Pointer that specifies the location where to copy the message.
 * @param Timeout Numeric value specifies the maximum number of milliseconds to stay suspended while waiting for a message to be available.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_MsgQRead(OsiMsgQ_t* pMsgQ, void* pMsg, OsiTime_t Timeout);

/**
 * @brief Deletes all messages stored in the specified message queue.
 *
 * @param pMsgQ Pointer to the message queue control block.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_MsgQFlush(OsiMsgQ_t* pMsgQ);

/**
 * @brief Returns the number of messages ready in the queue.
 *
 * @param pMsgQ Pointer to the message queue control block.
 *
 * @return uint32_t The number of messages ready in the queue.
 */
uint32_t osi_MsgQCount(OsiMsgQ_t* pMsgQ);

/**
 * @brief Returns whether there are any messages ready in the queue.
 *
 * @param pMsgQ Pointer to the message queue control block.
 *
 * @return BOOLEAN TRUE if the queue is empty, FALSE otherwise.
 */
BOOLEAN osi_MsgQIsEmpty(OsiMsgQ_t* pMsgQ);

/**
 * @brief Creates a synchronization object.
 *
 * The sync object is used for synchronization between different threads or ISR and a thread.
 *
 * @param pSyncObj Pointer to the sync object control block.
 * @param pSyncObjName Pointer to the name of the sync object.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_SyncObjCreate(OsiSyncObj_t* pSyncObj);

/**
 * @brief Deletes a synchronization object.
 *
 * @param pSyncObj Pointer to the sync object control block.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_SyncObjDelete(OsiSyncObj_t* pSyncObj);

/**
 * @brief Generates a sync signal for the object.
 *
 * All suspended threads waiting on this sync object are resumed.
 *
 * @param pSyncObj Pointer to the sync object control block.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_SyncObjSignal(OsiSyncObj_t* pSyncObj);

/**
 * @brief Generates a sync signal for the object from ISR context.
 *
 * @param p

SyncObj Pointer to the sync object control block.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_SyncObjSignalFromISR(OsiSyncObj_t* pSyncObj);

/**
 * @brief Waits for a sync signal of the specific sync object.
 *
 * @param pSyncObj Pointer to the sync object control block.
 * @param Timeout Numeric value specifies the maximum number of milliseconds to stay suspended while waiting for the sync signal.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_SyncObjWait(OsiSyncObj_t* pSyncObj, OsiTime_t Timeout);

/**
 * @brief Clears a sync object.
 *
 * @param pSyncObj Pointer to the sync object control block.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_SyncObjClear(OsiSyncObj_t* pSyncObj);

/**
 * @brief Creates a locking object.
 *
 * The locking object is used for protecting shared resources between different threads.
 *
 * @param pLockObj Pointer to the locking object control block.
 * @param pLockObjName Pointer to the name of the locking object.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_LockObjCreate(OsiLockObj_t* pLockObj);

/**
 * @brief Deletes a locking object.
 *
 * @param pLockObj Pointer to the locking object control block.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_LockObjDelete(OsiLockObj_t* pLockObj);

/**
 * @brief Locks a locking object.
 *
 * All other threads that call this function before this thread calls osi_LockObjUnlock will be suspended.
 *
 * @param pLockObj Pointer to the locking object control block.
 * @param Timeout Numeric value specifies the maximum number of milliseconds to stay suspended while waiting for the locking object.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_LockObjLock(OsiLockObj_t* pLockObj, OsiTime_t Timeout);

/**
 * @brief Unlocks a locking object.
 *
 * @param pLockObj Pointer to the locking object control block.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_LockObjUnlock(OsiLockObj_t* pLockObj);


/*******************************************************************************
    SEMAPHORE FUNCTIONS
********************************************************************************/

/**
 * @brief Creates a Semaphore object.
 *
 * The Semaphore object is used for accounting resources which can be shared
 * and obtained/released in different contexts, with a multiplicity greater than 1.
 *
 * @param pSemaphoreObj Pointer to the Semaphore object (allocated by the caller and
 *                      remains in scope throughout the lifetime of the object).
 * @param pSemaphoreObjName Pointer to the name of the semaphore object.
 * @param initialCount The initial count of the semaphore at creation (i.e., the number of resources available).
 * @param maxCount The maximum multiplicity of the semaphore.
 *                 Cannot release to a value greater than this.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_SemaphoreObjCreate(OsiSemaphoreObj_t*      pSemaphoreObj     ,
                                      const char*             pSemaphoreObjName ,
                                      const uint32            initialCount      ,
                                      const uint32            maxCount          );

/**
 * @brief Deletes a Semaphore object.
 *
 * After this function is called, the area holding the semaphore object is no longer in use
 * and can be reused.
 *
 * @param pSemaphoreObj Pointer to the semaphore object to be released.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_SemaphoreObjDelete(OsiSemaphoreObj_t* pSemaphoreObj);

/**
 * @brief Attempts to obtain a semaphore instance.
 *
 * If no instance is available, it waits for the designated timeout.
 *
 * @param pSemaphoreObj Pointer to the semaphore object to obtain an instance of.
 * @param Timeout The maximum number of milliseconds to stay suspended while waiting
 *                for an instance to become available.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_SemaphoreObjObtain(OsiSemaphoreObj_t* pSemaphoreObj , OsiTime_t Timeout);

/**
 * @brief Releases an instance of a semaphore.
 *
 * Note that if the available multiplicity of the semaphore is already at its
 * maximum value, this function will fail.
 *
 * @param pSemaphoreObj Pointer to the semaphore object to be released.
 *
 * @return OsiReturnVal_e The return value of the function.
 */
OsiReturnVal_e osi_SemaphoreObjRelease(OsiSemaphoreObj_t* pSemaphoreObj);

/**
 * @brief Returns the current count of instances of a semaphore.
 *
 * @param pSemaphoreObj Pointer to the semaphore object to get the count for.
 *
 * @return uint32_t The current count of the semaphore instances.
 */
uint32_t osi_SemaphoreObjGetCount(OsiSemaphoreObj_t* pSemaphoreObj);


/*******************************************************************************
    MISCELLANEOUS
********************************************************************************/
/*!
    \brief  convert tick to msec
*/
uint32_t TICK_TO_mSEC(uint32_t Tick);

/*!
    \brief  convert msec to tick
*/
uint32_t mSEC_TO_TICK(uint32_t mSec);

/**
 * os_get_time - Get current time (sec, usec)
 * @t: Pointer to buffer for the time
 * Returns: 0 on success, -1 on failure
 */
int os_get_time(struct os_time *t);

/**
 * os_get_reltime - Get relative time (sec, usec)
 * @t: Pointer to buffer for the time
 * Returns: 0 on success, -1 on failure
 */
int os_get_reltime(struct os_reltime *t);



/* Helpers for handling struct os_time */
static inline int os_time_before(struct os_time *a, struct os_time *b)
{
    return (a->sec < b->sec) ||
           (a->sec == b->sec && a->usec < b->usec);
}


static inline void os_time_sub(struct os_time *a, struct os_time *b,
                   struct os_time *res)
{
    res->sec = a->sec - b->sec;
    res->usec = a->usec - b->usec;
    if (res->usec < 0) {
        res->sec--;
        res->usec += 1000000;
    }
}


/* Helpers for handling struct os_reltime */
static inline int os_reltime_before(struct os_reltime *a,
                    struct os_reltime *b)
{
    return (a->sec < b->sec) ||
           (a->sec == b->sec && a->usec < b->usec);
}


static inline void os_reltime_sub(struct os_reltime *a, struct os_reltime *b,
                  struct os_reltime *res)
{
    res->sec = a->sec - b->sec;
    res->usec = a->usec - b->usec;
    if (res->usec < 0) {
        res->sec--;
        res->usec += 1000000;
    }
}


static inline void os_reltime_age(struct os_reltime *start,
                  struct os_reltime *age)
{
    struct os_reltime now;

    os_get_reltime(&now);
    os_reltime_sub(&now, start, age);
}


static inline int os_reltime_expired(struct os_reltime *now,
                     struct os_reltime *ts,
                     os_time_t timeout_secs)
{
    struct os_reltime age;

    os_reltime_sub(now, ts, &age);
    return (age.sec > timeout_secs) ||
           (age.sec == timeout_secs && age.usec > 0);
}


static inline int os_reltime_initialized(struct os_reltime *t)
{
    return t->sec != 0 || t->usec != 0;
}



int os_gmtime(os_time_t t, struct os_tm *tm);

/**
 * os_daemonize - Run in the background (detach from the controlling terminal)
 * @pid_file: File name to write the process ID to or %NULL to skip this
 * Returns: 0 on success, -1 on failure
 */
int os_daemonize(const char *pid_file);

/**
 * os_daemonize_terminate - Stop running in the background (remove pid file)
 * @pid_file: File name to write the process ID to or %NULL to skip this
 */
void os_daemonize_terminate(const char *pid_file);

/**
 * os_get_random - Get cryptographically strong pseudo random data
 * @buf: Buffer for pseudo random data
 * @len: Length of the buffer
 * Returns: 0 on success, -1 on failure
 */
int os_get_random(unsigned char *buf, size_t len);

/**
 * os_random - Get pseudo random value (not necessarily very strong)
 * Returns: Pseudo random value
 */
unsigned long os_random(void);

//-----------------------------------------------------------
// Replaces the TI lib implementation

int rand(void);
extern int ATTRIBUTE osi_fclose(FILE *_fp);
extern FILE * ATTRIBUTE osi_fopen(const char *_fname, const char *_mode);
extern size_t ATTRIBUTE osi_fread(void *_ptr, size_t len, size_t offset, FILE *_fp);
extern size_t osi_fwrite(const void *_ptr, size_t _size, size_t _count, FILE *_fp);
extern int ATTRIBUTE osi_fset(osiFileSetType containerType, void *params);
extern int ATTRIBUTE osi_fget(osiFileGetType containerType, void *params);
extern size_t ATTRIBUTE osi_filelength(const char * FileName);
extern int osi_fremove(FILE *_fp);
int fprintf(FILE *_fp, const char *_format, ...);
int fputc(int _c, FILE *_fp);
char *fgets(char *_ptr, int _size, FILE *_fp);
int rename(const char *_old, const char *_new);
//-----------------------------------------------------------



/**
 * os_rel2abs_path - Get an absolute path for a file
 * @rel_path: Relative path to a file
 * Returns: Absolute path for the file or %NULL on failure
 *
 * This function tries to convert a relative path of a file to an absolute path
 * in order for the file to be found even if current working directory has
 * changed. The returned value is allocated and caller is responsible for
 * freeing it. It is acceptable to just return the same path in an allocated
 * buffer, e.g., return strdup(rel_path). This function is only used to find
 * configuration files when os_daemonize() may have changed the current working
 * directory and relative path would be pointing to a different location.
 */
char * os_rel2abs_path(const char *rel_path);

/**
 * os_program_init - Program initialization (called at start)
 * Returns: 0 on success, -1 on failure
 *
 * This function is called when a programs starts. If there are any OS specific
 * processing that is needed, it can be placed here. It is also acceptable to
 * just return 0 if not special processing is needed.
 */
int os_program_init(void);

/**
 * os_program_deinit - Program deinitialization (called just before exit)
 *
 * This function is called just before a program exists. If there are any OS
 * specific processing, e.g., freeing resourced allocated in os_program_init(),
 * it should be done here. It is also acceptable for this function to do
 * nothing.
 */
void os_program_deinit(void);

/**
 * os_setenv - Set environment variable
 * @name: Name of the variable
 * @value: Value to set to the variable
 * @overwrite: Whether existing variable should be overwritten
 * Returns: 0 on success, -1 on error
 *
 * This function is only used for wpa_cli action scripts. OS wrapper does not
 * need to implement this if such functionality is not needed.
 */
int os_setenv(const char *name, const char *value, int overwrite);

/**
 * os_unsetenv - Delete environent variable
 * @name: Name of the variable
 * Returns: 0 on success, -1 on error
 *
 * This function is only used for wpa_cli action scripts. OS wrapper does not
 * need to implement this if such functionality is not needed.
 */
int os_unsetenv(const char *name);

/**
 * os_readfile - Read a file to an allocated memory buffer
 * @name: Name of the file to read
 * @len: For returning the length of the allocated buffer
 * Returns: Pointer to the allocated buffer or %NULL on failure
 *
 * This function allocates memory and reads the given file to this buffer. Both
 * binary and text files can be read with this function. The caller is
 * responsible for freeing the returned buffer with os_free().
 */
char * os_readfile(const char *name, size_t *len);



/*
 * The following functions are wrapper for standard ANSI C or POSIX functions.
 * By default, they are just defined to use the standard function name and no
 * os_*.c implementation is needed for them. This avoids extra function calls
 * by allowing the C pre-processor take care of the function name mapping.
 *
 * If the target system uses a C library that does not provide these functions,
 * build_config.h can be used to define the wrappers to use a different
 * function name. This can be done on function-by-function basis since the
 * defines here are only used if build_config.h does not define the os_* name.
 * If needed, os_*.c file can be used to implement the functions that are not
 * included in the C library on the target system. Alternatively,
 * OS_NO_C_LIB_DEFINES can be defined to skip all defines here in which case
 * these functions need to be implemented in os_*.c file for the target system.
 */



/**
 * os_malloc - Allocate dynamic memory
 * @size: Size of the buffer to allocate
 * Returns: Allocated buffer or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer with os_free().
 */
// void * os_malloc(size_t size);
void *os_malloc(size_t size);

/**
 * os_calloc - Allocate and zero memory
 * @size: Number of bytes to allocate
 * Returns: Pointer to allocated and zeroed memory or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer with os_free().
 */
void *os_calloc(size_t nmemb, size_t size);

/**
 * os_zalloc - Allocate and zero memory
 * @size: Number of bytes to allocate
 * Returns: Pointer to allocated and zeroed memory or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer with os_free().
 */
void* os_zalloc(size_t size);

/**
 * os_realloc - Re-allocate dynamic memory
 * @ptr: Old buffer from os_malloc() or os_realloc()
 * @size: Size of the new buffer
 * Returns: Allocated buffer or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer with os_free().
 * If re-allocation fails, %NULL is returned and the original buffer (ptr) is
 * not freed and caller is still responsible for freeing it.
 *
 */
void* os_realloc(void *ptr, size_t newsize);



/**
 * os_realloc - Re-allocate dynamic memory array
 * @ptr: Old buffer from os_malloc() or os_realloc()
 * @nmemb: Size of the new buffer
 * @size: size of each block
 * Returns: Allocated buffer or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer with os_free().
 * If re-allocation fails, %NULL is returned and the original buffer (ptr) is
 * not freed and caller is still responsible for freeing it.
 *
 */
void * os_realloc_array(void *ptr, size_t nmemb, size_t size);




/**
 * os_free - Free dynamic memory
 * @ptr: Old buffer from os_malloc() or os_realloc(); can be %NULL
 */
void os_free(void *ptr);

/**
 * os_memcpy - Copy memory area
 * @dest: Destination
 * @src: Source
 * @n: Number of bytes to copy
 * Returns: dest
 *
 * The memory areas src and dst must not overlap. os_memmove() can be used with
 * overlapping memory.
 */
//void * os_memcpy(void *dest, const void *src, size_t n);
#ifndef os_memcpy
#define os_memcpy(d, s, n) (memcpy((d), (s), (n)))
#endif


/**
 * os_memmove - Copy memory area
 * @dest: Destination
 * @src: Source
 * @n: Number of bytes to copy
 * Returns: dest
 *
 * The memory areas src and dst may overlap.
 */
//void * os_memmove(void *dest, const void *src, size_t n);
#ifndef os_memmove
#define os_memmove(d, s, n) memmove((d), (s), (n))
#endif

/**
 * os_memset - Fill memory with a constant byte
 * @s: Memory area to be filled
 * @c: Constant byte
 * @n: Number of bytes started from s to fill with c
 * Returns: s
 */
#ifndef os_memset
#define os_memset(s, c, n) memset(s, c, n)
#endif



/**
 * os_memcmp - Compare memory areas
 * @s1: First buffer
 * @s2: Second buffer
 * @n: Maximum numbers of octets to compare
 * Returns: An integer less than, equal to, or greater than zero if s1 is
 * found to be less than, to match, or be greater than s2. Only first n
 * characters will be compared.
 */
#ifndef os_memcmp
#define os_memcmp(s1, s2, n) memcmp((s1), (s2), (n))
#endif

/**
 * os_strdup - Duplicate a string
 * @s: Source string
 * Returns: Allocated buffer with the string copied into it or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer with os_free().
 */
char * os_strdup(const char *s);


/**
 * os_strlen - Calculate the length of a string
 * @s: '\0' terminated string
 * Returns: Number of characters in s (not counting the '\0' terminator)
 */
//size_t os_strlen(const char *s);
#ifndef os_strlen
#define os_strlen(s) strlen(s)
#endif

/**
 * os_memdup - Allocate duplicate of passed memory chunk
 * @src: Source buffer to duplicate
 * @len: Length of source buffer
 * Returns: %NULL if allocation failed, copy of src buffer otherwise
 *
 * This function allocates a memory block like os_malloc() would, and
 * copies the given source buffer into it.
 */
void * os_memdup(const void *src, size_t len);

/**
 * os_strcasecmp - Compare two strings ignoring case
 * @s1: First string
 * @s2: Second string
 * Returns: An integer less than, equal to, or greater than zero if s1 is
 * found to be less than, to match, or be greatred than s2
 */
int os_strcasecmp(const char *s1, const char *s2);

/**
 * os_strncasecmp - Compare two strings ignoring case
 * @s1: First string
 * @s2: Second string
 * @n: Maximum numbers of characters to compare
 * Returns: An integer less than, equal to, or greater than zero if s1 is
 * found to be less than, to match, or be greater than s2. Only first n
 * characters will be compared.
 */
int os_strncasecmp(const char *s1, const char *s2, size_t n);

/**
 * os_strchr - Locate the first occurrence of a character in string
 * @s: String
 * @c: Character to search for
 * Returns: Pointer to the matched character or %NULL if not found
 */
char * os_strchr(const char *s, int c);

/**
 * os_strrchr - Locate the last occurrence of a character in string
 * @s: String
 * @c: Character to search for
 * Returns: Pointer to the matched character or %NULL if not found
 */
#ifndef os_strrchr
#define os_strrchr(s, c) strrchr((s), (c))
#endif

/**
 * os_strcmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 * Returns: An integer less than, equal to, or greater than zero if s1 is
 * found to be less than, to match, or be greatred than s2
 */
#ifndef os_strcmp
#define os_strcmp(s1, s2) strcmp((s1), (s2))
#endif

/**
 * os_strncmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 * @n: Maximum numbers of characters to compare
 * Returns: An integer less than, equal to, or greater than zero if s1 is
 * found to be less than, to match, or be greater than s2. Only first n
 * characters will be compared.
 */
#ifndef os_strncmp
#define os_strncmp(s1, s2, n) strncmp((s1), (s2), (n))
#endif

/**
 * os_strstr - Locate a substring
 * @haystack: String (haystack) to search from
 * @needle: Needle to search from haystack
 * Returns: Pointer to the beginning of the substring or %NULL if not found
 */
#ifndef os_strstr
#define os_strstr(haystack, needle) strstr((haystack), (needle))
#endif


/**
 * os_strncpy - Copy string
 * @dest: Destination
 * @src: Source
 * @n: Number of bytes to copy
 * Returns: dest
 *  */
#ifndef os_strncpy
#define os_strncpy(d,s,n)  (strncpy((d),(s),(n)))
#endif

/**
 * os_strncpy - concatanate to a string
 * @dest: Destination
 * @src: Source
 * @n: Number of bytes to copy
 * Returns: dest
 *  */
#ifndef os_strncat
#define os_strncat(d,s,n)  (strncat((d),(s),(n)))
#endif

/**
 * os_snprintf - Print to a memory buffer
 * @str: Memory buffer to print into
 * @size: Maximum length of the str buffer
 * @format: printf format
 * Returns: Number of characters printed (not including trailing '\0').
 *
 * If the output buffer is truncated, number of characters which would have
 * been written is returned. Since some C libraries return -1 in such a case,
 * the caller must be prepared on that value, too, to indicate truncation.
 *
 * Note: Some C library implementations of snprintf() may not guarantee null
 * termination in case the output is truncated. The OS wrapper function of
 * os_snprintf() should provide this guarantee, i.e., to null terminate the
 * output buffer if a C library version of the function is used and if that
 * function does not guarantee null termination.
 *
 * If the target system does not include snprintf(), see, e.g.,
 * http://www.ijs.si/software/snprintf/ for an example of a portable
 * implementation of snprintf.
 */
#ifndef os_snprintf
#define os_snprintf(str, size, format, ...) snprintf((str), (size), (format), ##__VA_ARGS__)
#endif

/**
 * @brief Tokenizes a string with a delimiter and remembers the last position.
 *
 * This function is a reentrant version of `strtok()` needed by one of the
 * wolfSSL TLS extensions (look for XSTRTOK). The description is based on
 * the Linux man page for `strtok()` and the implementation is based on
 * FreeBSD's `strtok_r()` implementation.
 *
 * The `strtok_r()` function parses a string into a sequence of tokens.
 * On the first call to `strtok_r()`, the string to be parsed should be
 * specified in `str`. In each subsequent call that should parse the same
 * string, `str` should be `NULL`.
 *
 * The `delim` argument specifies a set of bytes that delimit the tokens
 * in the parsed string. The caller may specify different strings in `delim`
 * in successive calls that parse the same string.
 *
 * Each call to `strtok_r()` returns a pointer to a null-terminated string
 * containing the next token. This string does not include the delimiting byte.
 * If no more tokens are found, `strtok_r()` returns `NULL`.
 *
 * A sequence of two or more contiguous delimiter bytes in the parsed string
 * is considered to be a single delimiter. Delimiter bytes at the start or
 * end of the string are ignored. In other words, the tokens returned by
 * `strtok_r()` are always non-empty strings.
 *
 * The `strtok_r()` function uses the `saveptr` argument, which is a pointer
 * to a `char *` variable that is used internally by `strtok_r()` to maintain
 * context between successive calls that parse the same string.
 *
 * On the first call to `strtok_r()`, `str` should point to the string to be parsed,
 * and the value of `saveptr` is ignored. In subsequent calls, `str` should be `NULL`,
 * and `saveptr` should be unchanged since the previous call.
 *
 * Different strings may be parsed concurrently using sequences of calls to
 * `strtok_r()` that specify different `saveptr` arguments.
 *
 * @param s Pointer to the string to be tokenized (or NULL for subsequent calls).
 * @param delim The set of delimiters to use for tokenizing the string.
 * @param last Pointer to a `char *` variable used internally to maintain context.
 *
 * @return char* A pointer to the next token, or `NULL` if there are no more tokens.
 */
char *os_strtok_r(char *s, const char *delim, char **last);



#ifndef inet_ntop
extern int inet_ntop(int af, const void *src, void *dst, size_t size);
#endif



/**
 * os_strlcpy - Copy a string with size bound and NUL-termination
 * @dest: Destination
 * @src: Source
 * @siz: Size of the target buffer
 * Returns: Total length of the target string (length of src) (not including
 * NUL-termination)
 *
 * This function matches in behavior with the strlcpy(3) function in OpenBSD.
 */
size_t os_strlcpy(char *dest, const char *src, size_t siz);

/**
 * os_memcmp_const - Constant time memory comparison
 * @a: First buffer to compare
 * @b: Second buffer to compare
 * @len: Number of octets to compare
 * Returns: 0 if buffers are equal, non-zero if not
 *
 * This function is meant for comparing passwords or hash values where
 * difference in execution time could provide external observer information
 * about the location of the difference in the memory buffers. The return value
 * does not behave like os_memcmp(), i.e., os_memcmp_const() cannot be used to
 * sort items into a defined order. Unlike os_memcmp(), execution time of
 * os_memcmp_const() does not depend on the contents of the compared memory
 * buffers, but only on the total compared length.
 */
int os_memcmp_const(const void *a, const void *b, size_t len);


#ifdef COLLECT_HEAP_DEBUG_INFO
void os_printHeapdbg();
#endif

/*-----------------------------------------------------------*/
/*!
    \brief  Get time from the operating system
    \brief
    \brief t
    \param
    \return - time in seconds
    \note
    \warning
*/
uint64_t osi_GetDateTimeS();

/*-----------------------------------------------------------*/
/*!
    \brief  Set time from the operating system
    \brief
    \brief t
    \param
    \return - time in  seconds
    \note
    \warning
*/
void osi_SetDateTimeS(uint64_t time);

#ifdef __cplusplus
}
#endif

#endif //__OSI_H__


