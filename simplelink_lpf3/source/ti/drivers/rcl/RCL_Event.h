/*
 * Copyright (c) 2020-2025, Texas Instruments Incorporated
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

#ifndef ti_drivers_rcl_RCL_Event__include
#define ti_drivers_rcl_RCL_Event__include

#include <stdint.h>

#define RCL_EventNone                  ((RCL_Events){ .value = (0U << 0U)})   /*!< No events */
#define RCL_EventCmdStarted            ((RCL_Events){ .value = (1U << 0U)})   /*!< Command handler has accepted and started executing */
#define RCL_EventLastCmdDone           ((RCL_Events){ .value = (1U << 1U)})   /*!< The RCL is finished with the command */
#define RCL_EventRxEntryAvail          ((RCL_Events){ .value = (1U << 2U)})   /*!< An RX entry has been made available */
#define RCL_EventRxBufferFinished      ((RCL_Events){ .value = (1U << 3U)})   /*!< An RX multi-buffer is finished */
#define RCL_EventTxBufferFinished      ((RCL_Events){ .value = (1U << 4U)})   /*!< A TX buffer is finished */
#define RCL_EventSoftwareTriggered     ((RCL_Events){ .value = (1U << 5U)})   /*!< Handler is triggered from software */
#define RCL_EventTimerStart            ((RCL_Events){ .value = (1U << 6U)})   /*!< Timer-based start signalled */
#define RCL_EventDescheduleStop        ((RCL_Events){ .value = (1U << 7U)})   /*!< Deschedule-type stop signalled */
#define RCL_EventGracefulStop          ((RCL_Events){ .value = (1U << 8U)})   /*!< Timer-based graceful-stop signalled */
#define RCL_EventHardStop              ((RCL_Events){ .value = (1U << 9U)})   /*!< Timer-based hard-stop signalled */
#define RCL_EventStopDelayed           ((RCL_Events){ .value = (1U << 10U)})  /*!< Command was not stopped */
#define RCL_EventStopRejected          ((RCL_Events){ .value = (1U << 11U)})  /*!< Command was not stopped */
#define RCL_EventStartDelayed          ((RCL_Events){ .value = (1U << 12U)})  /*!< Command start is delayed, may still happen within allowDelay */
#define RCL_EventStartRejected         ((RCL_Events){ .value = (1U << 13U)})  /*!< Command start is not possible within scheduling parameters */
#define RCL_EventSetup                 ((RCL_Events){ .value = (1U << 14U)})  /*!< Setup has been performed */
#define RCL_EventPartialSetup          ((RCL_Events){ .value = (1U << 15U)})  /*!< Partial setup has been performed or is required by the running command */
#define RCL_EventRxBufferUpdate        ((RCL_Events){ .value = (1U << 16U)})  /*!< RX buffer has been updated */
#define RCL_EventTxBufferUpdate        ((RCL_Events){ .value = (1U << 17U)})  /*!< TX buffer has been updated */
#define RCL_EventHandlerCmdUpdate      ((RCL_Events){ .value = (1U << 18U)})  /*!< A property of a running command has been updated, to be detailed by handler */
#define RCL_EventCmdStepDone           ((RCL_Events){ .value = (1U << 19U)})  /*!< A step of the command has been done; details are command specific */
#define RCL_EventStopTimesUpdated      ((RCL_Events){ .value = (1U << 20U)})  /*!< A change was made to the stop times */
#define RCL_EventPacketTimeout         ((RCL_Events){ .value = (1U << 21U)})  /*!< A manually set packet-specific timeout has expired */
#define RCL_EventSilentlyRestartRadio  ((RCL_Events){ .value = (1U << 22U)})  /*!< Restart radio to perform updates, to be detailed by handler */
#define RCL_EventCmdUpdateDone         ((RCL_Events){ .value = (1U << 23U)})  /*!< An update of the running command is finished */
#define RCL_EventCoexNoTx              ((RCL_Events){ .value = (1U << 24U)})  /*!< A transmission was refused or aborted by coexistence procedure; command continues */
#define RCL_EventCmdScheduleDone       ((RCL_Events){ .value = (1U << 25U)})  /*!< Queued command has been scheduled  */
#define RCL_EventCmdStopDone           ((RCL_Events){ .value = (1U << 26U)})  /*!< Queued command has been scheduled  */

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
        uint32_t silentlyRestartRadio: 1; /*!< Restart radio to perform updates, to be detailed by handler */
        uint32_t cmdUpdateDone       : 1; /*!< An update of the running command is finished */
        uint32_t coexNoTx            : 1; /*!< A transmission was refused or aborted by coexistence procedure; command continues */
        uint32_t cmdScheduleDone     : 1; /*!< Queued command has been scheduled */
        uint32_t cmdStopDone         : 1; /*!< Scheduled command has been stopped */
    };
    uint32_t value;
};

#endif /* ti_drivers_rcl_RCL_Event__include */
