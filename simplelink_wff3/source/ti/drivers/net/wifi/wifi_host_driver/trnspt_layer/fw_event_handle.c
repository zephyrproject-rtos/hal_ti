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
/***************************************************************************/



#include "osi_kernel.h"
#include "fw_event_if.h"
#include "txn_bus_drv.h"
#include "nab.h"
#include "commands.h"
#include <wlan_irq_adapt.h>
#include "trnspt_if.h"
#include "trnspt_thread.h"
#include "rx.h"
#include "tx.h"
#include "macro_utils.h"
#include "bus_if.h"
#include "wlan_if.h"
#include "host_event_if.h"

extern ETxnStatus eventMbox_Handle();
extern void FwEvent_StateMachine ();
extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t * args, uint16_t argsLen);

volatile uint8_t gFwCrashOccurred = 0;


uint32_t wlan_FW_tsf;
#define __ALIGN_MASK(x,mask)    (((x)+(mask))&~(mask))

#define RX_BYTE_COUNT_MASK 0xFFFF
#define RX_NUM_OF_BYTE_TO_READ_MULTIPLIER 4
#define CC33XX_GENERAL_ERROR_READ_TIMEOUT_MSEC 	(3000)


enum control_message_type
{
    CTRL_MSG_NONE = 0,
    CTRL_MSG_EVENT = 1,
    CTRL_MSG_COMMND_COMPLETE = 2
};




//#define DEBUG_FW_EVENT
#ifdef DEBUG_FW_EVENT
UINT32 cores[10000][3]={0};
UINT32 coresNum = 0;



void printCoreStatus(void *core,int num)
{
    FwStatus_t *core_status = (FwStatus_t *)core;
    cores[coresNum][0] = num;
    cores[coresNum][1] = core_status->tsf;
    cores[coresNum][2] = (core_status->rx_status & RX_BYTE_COUNT_MASK);

    coresNum++;
    if(coresNum == 10000)
    {
        coresNum = 0;
    }

   // Report("cores 3 t %d r %d\r\n",core_status->tsf,(core_status->rx_status & RX_BYTE_COUNT_MASK));
}
#endif




/*
 * \brief   Unmask only cmd-cmplt and events interrupts (needed for init phase)
 *
 * \param  hFwEvent  - FwEvent Driver handle
 * \return Event mask
 *
 * \par Description
 * Unmask only cmd-cmplt and events interrupts (needed for init phase).
 *
 * \sa
 */
void fwEvent_SetInitMask (TFwEvent *pFwEvent)
{
}

/*
 * \brief   Unmask all interrupts
 *
 * \param  hFwEvent  - FwEvent Driver handle
 * \return void
 *
 * \par Description
 *
 * Called after driver Start or Recovery process are completed.
 * Unmask all interrupts.
 *
 * \sa
 */
void FwEvent_EnableExternalEvents (TFwEvent *pFwEvent)
{
}

/*
 * \brief   Mask all interrupts
 *
 * \param  hFwEvent  - FwEvent Driver handle
 * \return void
 *
 * \par Description
 *
 * Masks all interrupts from FW.
 *
 * \sa
 */
void FwEvent_MaskAllFwInterrupts(TFwEvent *pFwEvent )
{
}


TTxnStruct gCmdTxn;

int read_data_message(uint8_t *read_buffer, uint32_t buffer_size)
{
    TTxnStruct *pCmdTxn = &gCmdTxn;

    ETxnStatus ret = TXN_STATUS_OK;
    NAB_rx_header_t *nab_header;

    //pCmdTxn = os_zalloc(sizeof(TTxnStruct));

    memset(pCmdTxn,0,sizeof(TTxnStruct));

    /* Build the command TxnStruct */
    TXN_PARAM_SET(pCmdTxn, TXN_LOW_PRIORITY, TXN_FUNC_ID_WLAN, TXN_DIRECTION_READ, TXN_FIXED_ADDR)
    BUILD_TTxnStruct(pCmdTxn, NAB_DATA_ADDR, read_buffer, buffer_size, NULL, NULL)

    /* Send the command */
    ret = twIf_Transact(pCmdTxn);
    if(ret != TXN_STATUS_COMPLETE)
    {
        FW_EVENT_HANDLE_PRINT_ERROR("\n\r Error wrong status %d \n\r", ret);
        return -1;
    }

    nab_header = (NAB_rx_header_t *) read_buffer;

    if (nab_header->sync != DEVICE_SYNC_PATTERN)
    {
        FW_EVENT_HANDLE_PRINT_ERROR("\n\r Error wrong sync pattern 0x%x \n\r", nab_header->sync);
        return -1;
    }

    if ((nab_header->desc_len_or_error < 0) || (nab_header->opcode != DEVICE_RECV_OPCODE))
    {
        FW_EVENT_HANDLE_PRINT_ERROR("\n\r Error reading the packet , buffer_size:%d error_opcode :%d nab_header_opcode:0x%x\n\r",buffer_size, nab_header->desc_len_or_error,nab_header->opcode);
        return -1;
    }

    //nab_header->len ,includes  all what is after it. Including descriptor
    if ( (uint32_t) (nab_header->len + NAB_RX_HEADER_LEN_ADDITION) > buffer_size)
    {
        FW_EVENT_HANDLE_PRINT_ERROR("\n\r Error device_message_size %d  bigger than buffer_size: %d \n\r", nab_header->len,buffer_size);
        return -1;
    }

    FW_EVENT_HANDLE_PRINT("\n\r Read rx succeed, nab_header->opcode: 0x%x nab_header->len: %d\n\r",nab_header->opcode, nab_header->len);
    return nab_header->len;
}

int read_control_message(uint8_t *read_buffer, uint32_t buffer_size)
{
    TTxnStruct *pCmdTxn;
    ETxnStatus ret = TXN_STATUS_OK;
    NAB_header_t *nab_header;
    uint32_t device_message_size;

    pCmdTxn = os_zalloc(sizeof(TTxnStruct));

    if(pCmdTxn == NULL)
    {
        Report ("ERROR !! memory allocation failed");
        ASSERT_GENERAL(0);
        return -1;
    }

    /* Build the command TxnStruct */
    TXN_PARAM_SET(pCmdTxn, TXN_LOW_PRIORITY, TXN_FUNC_ID_WLAN, TXN_DIRECTION_READ, TXN_FIXED_ADDR)
    BUILD_TTxnStruct(pCmdTxn, NAB_CONTROL_ADDR, read_buffer, buffer_size, NULL, NULL)

    /* Send the command */
    ret = twIf_Transact(pCmdTxn);
    if(ret != TXN_STATUS_COMPLETE)
    {
        ASSERT_GENERAL(0);
        return -1;
    }

    nab_header = (NAB_header_t *) read_buffer;

    if (nab_header->sync_pattern != DEVICE_SYNC_PATTERN)
    {
        ASSERT_GENERAL(0);
        os_free(pCmdTxn);
        return -1;
    }

    device_message_size =   sizeof (NAB_header_t) +  NAB_EXTRA_BYTES + nab_header->len;

    if (device_message_size > buffer_size)
    {
        Report ("ERROR !! device_message_size > buffer_size\n");
        os_free(pCmdTxn);
        return -1;
    }

    os_free(pCmdTxn);

    return nab_header->len;
}

int general_error_event_get_log(TFwEvent *pFwEvent)
{
	int ret = 0; 
	const size_t buffer_size = 5000;
	unsigned long end_time = osi_GetTimeMS() + CC33XX_GENERAL_ERROR_READ_TIMEOUT_MSEC;
	uint8_t isGeneralError = 0;
	uint32_t isTimeout = 0;
	
    Report("\n\rAttempting to Get FW Crash Logs.");

	while((isGeneralError != true) && (isTimeout != true))
	{

		ret = read_control_message(pFwEvent->rxTxBuffer, buffer_size);
		if(ret > 0)
		{
			 NAB_header_t *nab_header = (NAB_header_t*) pFwEvent->rxTxBuffer;
			if(nab_header->opcode == NAB_GENERAL_ERROR_FW_LOGS_OPCODE)
			{
                Report("\n\rsuccessfully received NAB_GENERAL_ERROR_FW_LOGS_OPCODE");
				isGeneralError = 1;
				break;
			}
		}
        else
        {
            Report("\n\rUNSUCCESSFULLY received NAB_GENERAL_ERROR_FW_LOGS_OPCODE");
        }
		//should sleep here for 100ms if reading is zero 
		if(isGeneralError != true)
		{
			os_sleep(0,100000);
            if ((long)(osi_GetTimeMS() - end_time) >= 0)
            {
                // Passed the end time
                isTimeout = TRUE;
                ret = 0;
            }
        }
	}

	if(isTimeout)
	{
        Report("\n\rTimed Out Attempting to read CRASH FW LOGS");
	}

	goto out;

out:
	return ret; 
}

extern OsiMsgQ_t eventMsgQueue;
int parse_control_message(uint8_t *buffer, size_t buffer_length)
{
    uint8_t *end_of_payload = (uint8_t *) buffer + buffer_length;
    EventCompleteMboxTLV_t *control_info_descriptor;
    uint8_t *event_data, *cmd_result_data;
    EventMessage_t event;
    while(buffer < end_of_payload)
    {
        control_info_descriptor = (EventCompleteMboxTLV_t *) buffer;

        switch (control_info_descriptor->type)
        {
        case CTRL_MSG_EVENT:

            event_data = os_malloc(control_info_descriptor->length);
            if (NULL == event_data)
            {
                ASSERT_GENERAL(0);
                return -1;
            }
            os_memcpy(event_data, buffer + sizeof(EventCompleteMboxTLV_t), control_info_descriptor->length);
            event.len = control_info_descriptor->length;
            event.message = event_data;

            if(OSI_OK == osi_MsgQWrite(&eventMsgQueue, &event, OSI_WAIT_FOREVER,OSI_FLAG_NOT_FROM_INTR))
            {
                // sent message compelete
                CORE_STATUS_PRINT("parse_control_message: event msg  receive \n\r");
            }
            else
            {
                ASSERT_GENERAL(0);
            }
            //send to event mbox deffer_event(event_data, control_info_descriptor->length);
            break;

        case CTRL_MSG_COMMND_COMPLETE:
            cmd_result_data = buffer + sizeof(EventCompleteMboxTLV_t);

            CORE_STATUS_PRINT("parse_control_message: CTRL_MSG_COMMND_COMPLETE msg receive \n\r");
            cmd_ReadCompleteExternal(cmd_result_data);

            //trigger the command state machine
            cmd_SM((void *)0x111111);
            break;

        default:

            goto message_parse_error;
        }

        buffer += sizeof(EventCompleteMboxTLV_t);
        buffer += control_info_descriptor->length;
    }

    return 0;

message_parse_error:
    return -1;
}


uint32_t process_event_and_cmd_result(TFwEvent *pFwEvent)
{
    int ret;
    uint8_t *read_buffer, *message;
    const size_t buffer_size = pFwEvent->eventSize + sizeof(FwStatus_t);
    size_t message_length;
    FwStatus_t *new_core_status;
    FwStatus_t *core_status = (FwStatus_t *)(pFwEvent->tFwStatusTxn.tFwStatus);
    uint32_t previous_hint;

    read_buffer = os_malloc(buffer_size);
    if (!read_buffer)
    {
        FW_EVENT_HANDLE_PRINT_ERROR("\n\rERROR process_event_and_cmd_result: malloc failed , size :%d",buffer_size);
        return TXN_STATUS_ERROR;
    }

    ret = read_control_message(read_buffer, buffer_size);

    if (ret < 0)
    {
        FW_EVENT_HANDLE_PRINT_ERROR("\n\rERROR read_control_message buffer_size:%d",buffer_size);
        goto out;
    }

    message_length = ret - NAB_EXTRA_BYTES;
    message = read_buffer + sizeof(NAB_header_t) + NAB_EXTRA_BYTES;


    ret = parse_control_message(message, message_length);
    if (ret < 0)
    {
        FW_EVENT_HANDLE_PRINT_ERROR("\n\rERROR parse_control_message message_length:%d",message_length);
        goto out;
    }

    /* Each read transaction always carries an updated core status */
    previous_hint = core_status->host_interrupt_status & (~ HINT_COMMAND_COMPLETE);
    new_core_status = (FwStatus_t*)(read_buffer + buffer_size - sizeof(FwStatus_t));
    os_memcpy(core_status, new_core_status, sizeof(FwStatus_t));
#ifdef DEBUG_FW_EVENT
    printCoreStatus(core_status,2);
#endif
    /* Host interrupt filed is clear-on-read and we do not want
       to overrun previously unhandled bits. */
    core_status->host_interrupt_status |= previous_hint;

out:
    os_free(read_buffer);
    return ret;
}



/*
 * \brief   Call FwEvent clients event handlers
 *
 * \param  hFwEvent  - FwEvent Driver handle
 * \return void
 *
 * \par Description
 *
 * \sa
 */
ETxnStatus FwEvent_CallHandlers(TFwEvent *pFwEvent)
{
    uint32_t core_status_idle;
    FwStatus_t *core_status = (FwStatus_t*) (pFwEvent->tFwStatusTxn.tFwStatus);
    int ret;
    uint32_t rx_byte_count;
    uint32_t initEvents;
    uint32_t maxRxBytesToHandleAtOnce = pFwEvent->rxTxBufSize*RX_NUM_OF_BYTE_TO_READ_MULTIPLIER;
    uint32_t numRxBytesHandled = 0;
    static uint32_t debugLastReadDataLen = 0;
//    FWEVENT_PRINT("FwEvent_CallHandlers: uEventVector = 0x%x\n\r", pFwEvent->uEventVector);

    do
    {
        core_status_idle = TRUE;

        initEvents = core_status->host_interrupt_status
                & (HINT_ROM_LOADER_INIT_COMPLETE
                        | HINT_SECOND_LOADER_INIT_COMPLETE
                        | HINT_FW_WAKEUP_COMPLETE
                        | HINT_FW_DOWNLOADING_INI_PARAMS_COMPLETE);

        if (initEvents)
        {
            CORE_STATUS_PRINT("\n\rcore_status ! initEvents :0x%x tsf:0x%x", initEvents,core_status->tsf);
            core_status->host_interrupt_status &= ~
                                     (HINT_ROM_LOADER_INIT_COMPLETE
                                         | HINT_SECOND_LOADER_INIT_COMPLETE
                                         | HINT_FW_WAKEUP_COMPLETE
                                         | HINT_FW_DOWNLOADING_INI_PARAMS_COMPLETE);
            fwEvent_Signal(initEvents);

        }
        wlan_FW_tsf = core_status->tsf;

        // HINT_GENERAL_ERROR event is sent in case of FW assert
        if (core_status->host_interrupt_status & HINT_GENERAL_ERROR)
        {
            gFwCrashOccurred = 1;
            FW_EVENT_HANDLE_PRINT_ERROR("\n\rFwEvent_CallHandlers: GENERAL ERROR event received! FW is stuck\n\r");

            WlanEventFwCrash_t *pArgs;
            pArgs = os_zalloc(sizeof(WlanEventFwCrash_t));

            // Here we read the log buffer (from the rx tx buffer)
            if (general_error_event_get_log(pFwEvent) > 0)
            {
                pArgs->log_buffer = pFwEvent->rxTxBuffer + sizeof(NAB_header_t);
                pArgs->log_buffer_len = (uint32_t)CC33XX_MAX_FW_LOGS_BUFFER_SIZE;
            }
            else
            {
                pArgs->log_buffer = NULL;
                pArgs->log_buffer_len = 0;
            }
            FW_EVENT_HANDLE_PRINT_ERROR("\n\rSend to wlanDispatcherSendEvent\n\r");

            wlanDispatcherSendEvent(WLAN_EVENT_FW_CRASH, (uint8_t *)pArgs, sizeof(WlanEventFwCrash_t));
            core_status->host_interrupt_status &= ~HINT_GENERAL_ERROR;
            os_free(pArgs);
        }

        if (core_status->host_interrupt_status
                || (core_status->rx_status & RX_BYTE_COUNT_MASK))    //Handle RX
        {

            FW_EVENT_HANDLE_PRINT("\n\rFwEvent_CallHandlers:uEventVector :0x%x,rx_status:%d \n\r", pFwEvent->uEventVector,core_status->rx_status & RX_BYTE_COUNT_MASK);

            if (core_status->host_interrupt_status & HINT_COMMAND_COMPLETE) //For mgmt commands
            {
                /* We keep reading the core status and handle the command complete or events until core
                   status become 0.
                   Later on when there`s RX the core status is read again (and nulls).
                   Bug fix: We must take care of event and command complete on the same interrupt since
                   core status is cleared on the RX read. This occurs when there is an event from FW, command
                   complete, AND rx data */
                ret = process_event_and_cmd_result(pFwEvent);
                if (ret < 0)
                {
                    FW_EVENT_HANDLE_PRINT_ERROR(
                           "\n\r Error !!! process_event_and_cmd_result: 0x%x\n\r",core_status->host_interrupt_status);
                    memset(core_status, 0, sizeof *core_status);
                    ASSERT_GENERAL(0);
                    return TXN_STATUS_ERROR;
                }
                CORE_STATUS_PRINT("\n\rcore_status ! HINT_COMMAND_COMPLETE,host_interrupt_status :0x%x,rx_status:%d tsf:0x%x\n\r",
                        core_status->host_interrupt_status,
                        core_status->rx_status & RX_BYTE_COUNT_MASK,
                        core_status->tsf);
                if (core_status->host_interrupt_status)
                {
                    core_status_idle = FALSE;//keep the loop
                }
                else
                {
                    core_status_idle = TRUE;
                }
            }
            else
            {
                core_status_idle = TRUE;// get out from the loop if there are no events to handle unless there are RX to handle
            }

            wlan_FW_tsf = core_status->tsf;

            rx_byte_count = (core_status->rx_status & RX_BYTE_COUNT_MASK);

            if((rx_byte_count != 0) && (numRxBytesHandled > maxRxBytesToHandleAtOnce))
            {
                trnspt_RequestSchedule (pFwEvent->uContextId,FALSE);//perform rxData_MissingPktTimeout_task
            }

            else if (rx_byte_count != 0)
            {
                //handle RX packets
                uint8_t *read_buffer = pFwEvent->rxTxBuffer;
                FwStatus_t *new_core_stat;
                NAB_rx_header_t *NAB_rx_header;
                uint32_t read_headers_len;
                uint32_t read_data_len, actual_read_data_len;
                uint32_t previous_hint;

                core_status_idle = FALSE;
                read_headers_len = sizeof(FwStatus_t) + sizeof(NAB_rx_header_t);
                read_data_len = rx_byte_count + read_headers_len;
                read_data_len = bus_AlignLength(read_data_len);
                FW_EVENT_HANDLE_PRINT("\n\rRx_status count: %d, headers_len:%d, next read total length : %d read-unaligned size:%d!!!\n\r", rx_byte_count,read_headers_len,read_data_len-sizeof(FwStatus_t), rx_byte_count + read_headers_len);//FwStatus_t is read directly by lower layers and no from the nab

                //the maximum read is RX_TX_BUFFER
                //if the length exceeds that, we should do another read round so mark
                //the core idle status as false
                if (read_data_len > pFwEvent->rxTxBufSize)
                {
                    FW_EVENT_HANDLE_PRINT("\n\r Rx length before reduction,length: %d!!!\n\r", read_data_len);
                    read_data_len = pFwEvent->rxTxBufSize;
                }

                core_status->host_interrupt_status &= ~HINT_RX_DATA_PENDING;
                if (read_data_message(read_buffer, read_data_len) < 0)
                {
                    FW_EVENT_HANDLE_PRINT_ERROR("\n\r warning!read_data_message failed, no data, continue, read_data_len:%d debugLastReadDataLen:%d !!!\n\r", read_data_len, debugLastReadDataLen);
                }
                else // read data was succeeded
                {

                    debugLastReadDataLen = read_data_len;
                    new_core_stat = (FwStatus_t*) ((uint8_t*) read_buffer
                            + read_data_len - sizeof(FwStatus_t));

                    //host_interrupt_status it suppose to be zero in here
                    previous_hint = core_status->host_interrupt_status;
                    memcpy(core_status, new_core_stat, sizeof(FwStatus_t));

                    wlan_FW_tsf = core_status->tsf;
                    /* Host interrupt filed is clear-on-read and we do not want
                       to overrun previously unhandled bits. */
                    core_status->host_interrupt_status |= previous_hint;
                    CORE_STATUS_PRINT("\n\rcore_status ! Rx :host_interrupt_status :0x%x,rx_status:%d loopNum:%d tsf:0x%x\n\r",
                            core_status->host_interrupt_status,
                            core_status->rx_status & RX_BYTE_COUNT_MASK,
                            loopNum,
                            core_status->tsf);

    #ifdef DEBUG_FW_EVENT
                    printCoreStatus(core_status,1);
        #endif

                    NAB_rx_header = (NAB_rx_header_t*) read_buffer;

                    if (NAB_rx_header->len < NAB_RX_HEADER_LEN_SUBMISSION)
                    {
                        ASSERT_GENERAL(0);
                        actual_read_data_len = 0;
                        return TXN_STATUS_ERROR;
                    }
                    else
                    {
                        actual_read_data_len = NAB_rx_header->len
                                - NAB_RX_HEADER_LEN_SUBMISSION; ///the length contains part of the NAB_rx_header_t, so reduce 8 to get the real packet length
                    } FW_EVENT_HANDLE_PRINT("\n\rFrom nab hdr, Rx data_len:%d", actual_read_data_len);

                    if (actual_read_data_len != 0)
                    {
                        read_buffer = (uint8_t*) read_buffer
                                + sizeof(NAB_rx_header_t);
                        rx(read_buffer, actual_read_data_len);
                        numRxBytesHandled += actual_read_data_len;

                    }
                }
            }// else if (rx_byte_count != 0)
        }
        
        if(!pFwEvent->isDuringInit)
        {
            core_status->host_interrupt_status &= ~HINT_NEW_TX_RESULT;
            tx_ImmediateComplete(core_status);
        }

    }
    while (!core_status_idle);

    return TXN_STATUS_COMPLETE;
}


/*
 * \brief   Handle the Fw Status information
 *
 * \param  hFwEvent  - FwEvent Driver handle
 * \return void
 *
 * \par Description
 * This function is called from FwEvent_Handle on a sync read, or from TwIf as a CB on an async read.
 * It calls FwEvent_CallHandlers to handle the triggered interrupts.
 *
 * \sa FwEvent_Handle
 */
ETxnStatus FwEvent_SmHandleEvents (TFwEvent *pFwEvent)
{
    ETxnStatus eStatus;

    /* Save delta between driver and FW time (needed for Tx packets lifetime) */
    pFwEvent->uFwTimeOffset = (osi_GetTimeMS() * 1000) - ((FwStatus_t *)(pFwEvent->tFwStatusTxn.tFwStatus))->tsf;

    /* Call the interrupts handlers */
    eStatus = FwEvent_CallHandlers (pFwEvent);

//    FWEVENT_PRINT("FwEvent_SmHandleEvents: Status=%d, EventVector=0x%x, IntrPending=%d, NumPendHndlrs=%d, FwTimeOfst=%d\n\r", eStatus, pFwEvent->uEventVector, pFwEvent->bIntrPending, pFwEvent->uNumPendHndlrs, pFwEvent->uFwTimeOffset);

    /* Return the status of the handlers processing (complete, pending or error) */
    return eStatus;
}




ETxnStatus FwEvent_AllocateStatus (TFwEvent *pFwEvent)
{
    TTxnStruct* pTxn;

    pFwEvent->tFwStatusTxn.tFwStatus = os_zalloc(sizeof(FwStatus_t));

    if(pFwEvent->tFwStatusTxn.tFwStatus == NULL)
    {
        Report("\n\r FwEvent_AllocateStatus ERROR allocation failure ");
        return TXN_STATUS_ERROR;
    }

    /* Prepare FW status Txn structure (includes 4 bytes interrupt status reg and 64 bytes FW-status from memory area) */
    /* Note: This is the only transaction that is sent in high priority.
     *       The original reason was to lower the interrupt latency, but we may consider using the
     *         same priority as all other transaction for simplicity.
     */
    pTxn = (TTxnStruct*)&pFwEvent->tFwStatusTxn.tTxnStruct;
    TXN_PARAM_SET(pTxn, TXN_HIGH_PRIORITY, TXN_FUNC_ID_WLAN, TXN_DIRECTION_READ, TXN_FIXED_ADDR)
    BUILD_TTxnStruct(pTxn, FW_STATUS_ADDR, pFwEvent->tFwStatusTxn.tFwStatus, sizeof(FwStatus_t), NULL, pFwEvent) 
    return TXN_STATUS_OK;
}






