/*
 * Copyright (c) 2020-2023, Texas Instruments Incorporated
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

#ifndef __rcl_events_h__
#define __rcl_events_h__

#include <stdint.h>

#define RCL_EventNone                  ((RCL_Events){ .value = (0 << 0)})   /*!< No events */
#define RCL_EventCmdStarted            ((RCL_Events){ .value = (1 << 0)})   /*!< Command handler has accepted and started executing */
#define RCL_EventLastCmdDone           ((RCL_Events){ .value = (1 << 1)})   /*!< The RCL is finished with the command */
#define RCL_EventRxEntryAvail          ((RCL_Events){ .value = (1 << 2)})   /*!< An RX entry has been made available */
#define RCL_EventRxBufferFinished      ((RCL_Events){ .value = (1 << 3)})   /*!< An RX multi-buffer is finished */
#define RCL_EventTxBufferFinished      ((RCL_Events){ .value = (1 << 4)})   /*!< A TX buffer is finished */
#define RCL_EventSoftwareTriggered     ((RCL_Events){ .value = (1 << 5)})   /*!< Handler is triggered from software */
#define RCL_EventTimerStart            ((RCL_Events){ .value = (1 << 6)})   /*!< Timer-based start signalled */
#define RCL_EventDescheduleStop        ((RCL_Events){ .value = (1 << 7)})   /*!< Deschedule-type stop signalled */
#define RCL_EventGracefulStop          ((RCL_Events){ .value = (1 << 8)})   /*!< Timer-based graceful-stop signalled */
#define RCL_EventHardStop              ((RCL_Events){ .value = (1 << 9)})   /*!< Timer-based hard-stop signalled */
#define RCL_EventStopDelayed           ((RCL_Events){ .value = (1 << 10)})  /*!< Command was not stopped */
#define RCL_EventStopRejected          ((RCL_Events){ .value = (1 << 11)})  /*!< Command was not stopped */
#define RCL_EventStartDelayed          ((RCL_Events){ .value = (1 << 12)})  /*!< Command start is delayed, may still happen within allowDelay */
#define RCL_EventStartRejected         ((RCL_Events){ .value = (1 << 13)})  /*!< Command start is not possible within scheduling parameters */
#define RCL_EventSetup                 ((RCL_Events){ .value = (1 << 14)})  /*!< Setup has been performed */
#define RCL_EventPartialSetup          ((RCL_Events){ .value = (1 << 15)})  /*!< Partial setup has been performed or is required by the running command */
#define RCL_EventRxBufferUpdate        ((RCL_Events){ .value = (1 << 16)})  /*!< RX buffer has been updated */
#define RCL_EventTxBufferUpdate        ((RCL_Events){ .value = (1 << 17)})  /*!< TX buffer has been updated */
#define RCL_EventHandlerCmdUpdate      ((RCL_Events){ .value = (1 << 18)})  /*!< A property of a running command has been updated, to be detailed by handler */
#define RCL_EventCmdStepDone           ((RCL_Events){ .value = (1 << 19)})  /*!< A step of the command has been done; details are command specific */
#define RCL_EventStopTimesUpdated      ((RCL_Events){ .value = (1 << 20)})  /*!< A change was made to the stop times */
#define RCL_EventPacketTimeout         ((RCL_Events){ .value = (1 << 21)})  /*!< A manually set packet-specific timeout has expired */

union RCL_Events_u {
    struct {
        uint32_t cmdStarted          : 1; /*!< Command handler has accepted and started executing */
        uint32_t lastCmdDone         : 1; /*!< The RCL is finished with the command */
        uint32_t rxEntryAvail        : 1; /*!< An RX entry has been made available */
        uint32_t rxBufferFinished    : 1; /*!< An RX multi-buffer is finished */
        uint32_t txBufferFinished    : 1; /*!< A TX buffer is finished */
        uint32_t swTriggered         : 1; /*!< Handler is triggered from software */
        uint32_t timerStart          : 1; /*!< Timer-based start signalled */
        uint32_t descheduleStop      : 1; /*!< Deschedule-type stop signalled */
        uint32_t gracefulStop        : 1; /*!< Timer/api-based graceful-stop signalled */
        uint32_t hardStop            : 1; /*!< Timer/api-based hard-stop signalled */
        uint32_t stopDelayed         : 1; /*!< Command was not stopped */
        uint32_t stopRejected        : 1; /*!< Command was not stopped */
        uint32_t startDelayed        : 1; /*!< Command start is delayed, may still happen within allowDelay */
        uint32_t startRejected       : 1; /*!< Command start is not possible within scheduling parameters */
        uint32_t setup               : 1; /*!< Setup has been performed */
        uint32_t partialSetup        : 1; /*!< Partial setup has been performed or is required by the running command */
        uint32_t rxBufferUpdate      : 1; /*!< RX buffer has been updated */
        uint32_t txBufferUpdate      : 1; /*!< TX buffer has been updated */
        uint32_t handlerCmdUpdate    : 1; /*!< A property of a running command has been updated, to be detailed by handler */
        uint32_t cmdStepDone         : 1; /*!< A step of the command has been done; details are command specific */
        uint32_t stopTimesUpdated    : 1; /*!< A change was made to the stop times */
        uint32_t packetTimeout       : 1; /*!< A manually set packet-specific timeout has expired */
    };
    uint32_t value;
};

#endif
