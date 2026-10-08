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

#include <trnspt_if.h>
#include <trnspt_thread.h>
#include <txn_bus_drv.h>
#include "osi_kernel.h"
#include "commands.h"
#include "w_queue.h"
#include "trnspt_if.h"
#include "macro_utils.h"
#include "wlan_if.h"
#include "host_event_if.h"
#include "errors.h"


#define CMD_SEND_TIMEOUT_MS (120000) //2 minutes

extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t * args, uint16_t argsLen);

/* internal commands return value from FW that will convert to a command status above
 * This should never change and it is copied from the cc3xxx_public_commands.h
 */
typedef enum
{
    CMD_MAILBOX_IDLE              =  0,
    CMD_STATUS_SUCCESS            =  1,
    CMD_STATUS_UNKNOWN_CMD        =  2,
    CMD_STATUS_UNKNOWN_IE         =  3,
    CMD_STATUS_REJECT_MEAS_SG_ACTIVE =  11,
    CMD_STATUS_RX_BUSY            = 13,
    CMD_STATUS_INVALID_PARAM      = 14,
    CMD_STATUS_TEMPLATE_TOO_LARGE = 15,
    CMD_STATUS_OUT_OF_MEMORY      = 16,
    CMD_STATUS_STA_TABLE_FULL     = 17,
    CMD_STATUS_RADIO_ERROR        = 18,
    CMD_STATUS_WRONG_NESTING      = 19,
    CMD_STATUS_TIMEOUT            = 21, /* Driver internal use.*/
    CMD_STATUS_FW_RESET           = 22, /* Driver internal use.*/
    CMD_STATUS_TEMPLATE_OUT_OF_TEMPORARY_MEMORY = 23,
    CMD_STATUS_NO_RX_BA_SESSION   = 24,
    CMD_GENERAL_STATUS_ERROR      = 25,
    CMD_WRONG_STATE               = 26,
    MAX_COMMAND_STATUS            = 0x7FFF
} CommandStatus_e;

typedef struct
{
    //currentCommand;
    //command queue;
    TQueNodeHdr queueHeader;
    char *inputBuffer; //holds the input buffer of the command
    uint32_t inputBufferLen; //holds the length of the input buffer
    char *outputBuffer; //holds the output buffer of the command
    uint32_t outputBufferLen; //holds the length of the outputBuffer
    OsiSyncObj_t *pSyncObjComplete; //holds the syncObj to signal when command complete
    int cmdStatus;                //holds return status from lower layers
    CmdCallbackFunction_t commandcallBack;
    void *commandcallBackPt;
} cmdNode_t;

typedef struct
{
    //currentCommand;
    //command queue;
    TTxnStruct cmdTxn;
    uint32_t MBOXAdder; //address to the commands mailbox
    char *scratchBuffer; //address for scrachpad
    void *pMsgQ; //message queue for the commands
    cmdNode_t *currentCommand; //current handle command
    uint32_t clientID; //holds the transport thread client ID
    OsiTimer_t timer; //holds the cmd mailbox timer
    uint32_t timeout; //holds the command timeout
    uint32_t maxCMDSize; //holds the maximum command size
    OsiLockObj_t  cmd_lockObj;                          /* protection from cross calls      */
} cmdCB_t;

cmdCB_t *cmdCB = NULL;

void cmd_lock();
void cmd_unlock();

int cmd_SendInTransport(char *in, uint32_t len, CmdCallbackFunction_t cb, void *fb)
{
    cmdNode_t *cmdNode = NULL;
    int retVal;

    if (NULL == cmdCB)
    {
        retVal = WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__CMD_CB_NOT_INITIALIZED);
        goto free;
    }

    cmdNode = os_zalloc(sizeof(cmdNode_t));
    if (NULL == cmdNode)
    {
        COMMAND_PRINT_ERROR("\n\rERROR cmd_SendInTransport allocation failed");
        retVal = WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__MALLOC);
        goto free;
    }

    cmdNode->outputBuffer = NULL;
    cmdNode->outputBufferLen = 0;
    cmdNode->inputBuffer = in;
    cmdNode->inputBufferLen = len;
    cmdNode->pSyncObjComplete = NULL;
    cmdNode->commandcallBack = cb;
    cmdNode->commandcallBackPt = fb;

    cmd_lock();
    if (que_Enqueue(cmdCB->pMsgQ, cmdNode) < 0)
    {
        retVal = WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__ENQUEUE);
        cmd_unlock();
        COMMAND_PRINT_ERROR("\n\rERROR cmd_SendInTransport***No room in queue pMsgQ*** line:%d\n", __LINE__);
        goto free;
    }
    cmd_unlock();

    COMMAND_PRINT("\n\rcmd_SendInTransport: new command, waiting\n\r");

    trnspt_RequestSchedule(cmdCB->clientID, FALSE);

    retVal = CMD_OK;


    free:
    if ((NULL != cmdNode) && (retVal != CMD_OK))
    {
        os_free(cmdNode);
    }

    return retVal;
}

int Transfer(char *in, uint32_t len)
{
    TTxnStruct *pCmdTxn = &(cmdCB->cmdTxn);
    ETxnStatus ret = TXN_STATUS_OK;
    int retVal = 0;

    if(len > cmdCB->maxCMDSize)
    {
        Report("\n\rTransfer: error exceeded maxCMDSize:%d len:%d",cmdCB->maxCMDSize,len);
        ASSERT_GENERAL(0);
        return WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__CMD_REACHED_MAX_SIZE);
    }

    memcpy(cmdCB->scratchBuffer, in, len);
    memset(cmdCB->scratchBuffer + len, 0, cmdCB->maxCMDSize - len);

    /* start the CmdMbox timer */
    retVal = osi_TimerStart(&(cmdCB->timer), cmdCB->timeout, FALSE);
    if(OSI_OK != retVal)
    {
        Report("\n\r Transfer: Failed to start timer. error number: %d", retVal);
        return WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__TIMER_START);
    }

    /* Build the command TxnStruct */
    TXN_PARAM_SET_AGGREGATE(pCmdTxn,TXN_AGGREGATE_OFF);
    TXN_PARAM_SET(pCmdTxn, TXN_LOW_PRIORITY, TXN_FUNC_ID_WLAN,
                  TXN_DIRECTION_WRITE, TXN_INC_ADDR)
    BUILD_TTxnStruct(pCmdTxn, cmdCB->MBOXAdder, cmdCB->scratchBuffer,
                     cmdCB->maxCMDSize, NULL, NULL)

    /* Send the command */
    ret = twIf_Transact(pCmdTxn);
    if(ret != TXN_STATUS_COMPLETE)
    {
        ASSERT_GENERAL(0);
        return WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__TRANSACTION);
    }

	
	return 0;
}	
void cmd_ReadCompleteExternal(uint8_t *inBuf)
{
    uint16_t commandStatus;
    uint8_t *payload;
    char *out;
    uint32_t outLen ;

    if (NULL != cmdCB->currentCommand)
    {
        out = cmdCB->currentCommand->outputBuffer;
        outLen = cmdCB->currentCommand->outputBufferLen;
        //if no output buffer was given, set the read length to the command header only
        if (NULL == out)
        {
            outLen = CMD_HEADER_SIZE;
        }
        else
        {
            //read the command header
            outLen += CMD_HEADER_SIZE;
        }

        //read the command status from the mailbox - command is sitting in the Mbox as follows
        // | CMD ID - 2 Bytes | CMD STATUS - 2 Bytes | Payload - Max 736 Bytes |
        uint16_t cmdId;
        COPY_WLAN_WORD(&cmdId,inBuf );//for debug purpose
        COPY_WLAN_WORD(&commandStatus,inBuf + 2);

        //if we got command success status from FW convert it to CMD_OK
        if (CMD_STATUS_SUCCESS == commandStatus)
        {
            cmdCB->currentCommand->cmdStatus = CMD_OK;
        }
        else if (CMD_BOOT_ERROR_WORKAROUND == commandStatus)
        {
            /* Workaround for known ROM bug: In certain cases, the ROM firmware returns
               an invalid status code CMD_BOOT_ERROR_WORKAROUND(17760) due to a known issue. This workaround checks
               for this specific erroneous status value and treats it as a success to
               ensure proper functionality.
               Note: This workaround is necessary due to the current hardware limitations
               and will be removed once the issue is resolved in future hardware revisions. */
            cmdCB->currentCommand->cmdStatus = CMD_OK;
        }
        else
        {
            COMMAND_PRINT_ERROR("\r\n commandStatus: 0x%x change to WLAN_RET_COMMAND_GENERAL :0x%x", commandStatus,WLAN_RET_COMMAND_GENERAL);
           cmdCB->currentCommand->cmdStatus = WLAN_RET_COMMAND_GENERAL;
           //cmdCB->currentCommand->cmdStatus = CMD_MAX_COMMAND_ERROR - commandStatus;// to open issue, we need to have the FW status
        }

        payload = (inBuf + 4);

        if (NULL != out)
        {
            memcpy(out, payload, outLen - CMD_HEADER_SIZE);
        }
    }
}

/**
 * cmd_SM - is the state machine of sending commands to the FW
 * @param flag reserved
 */
void cmd_SM(void* hCbHndl)
{
    int retVal;
    WlanEventError_t  error_event;
    static uint8_t cmdState = CMD_SM_AVAILABLE;

    //currently no command is being handled
    if (cmdState == CMD_SM_AVAILABLE)
    {
        cmd_lock();
        //see if there is something in the queue
        cmdCB->currentCommand = que_Dequeue(cmdCB->pMsgQ);

        //queue is empty, return without nothing
        if (NULL == cmdCB->currentCommand)
        {
            cmd_unlock();
            //COMMAND_PRINT("\n\rCommandSM: no commands in queue, return\n\r");
            twIf_Sleep();// this is not really sleeps
            return;
        }
        else
        {
            //set the status of this command is general error, will be changed to OK
            //upon command complete
            cmdCB->currentCommand->cmdStatus = WLAN_RET_COMMAND_GENERAL;

            twIf_Awake();
            COMMAND_PRINT("\n\rCommandSM: transfer command\n\r");
            cmdState = CMD_SM_TRANSFERED;//wait for the command complete
            cmd_unlock();
            //just to make sure no timer was left
            retVal = osi_TimerStop(&(cmdCB->timer));
            if (OSI_OK != retVal)
            {
                COMMAND_PRINT_ERROR("\n\rrCommandSM: Failed to stop timer. error number: %d",retVal);
                error_event.error_num = WLAN_RET_COMMAND_ERROR_MID_TYPE__TIMER_STOP;
                error_event.module = WLAN_MODULE_TMR;
                error_event.severity = WLAN_SEVERITY_MID;
                Wlan_HostSendEvent(WLAN_EVENT_ERROR, (uint8_t*)&error_event, sizeof(WlanEventError_t));
            }
            COMMAND_PRINT("\n\rCommandSM: transfer command\n\r");
            retVal = Transfer(cmdCB->currentCommand->inputBuffer,
                     cmdCB->currentCommand->inputBufferLen);
            if (retVal < 0)
            {
                COMMAND_PRINT_ERROR("\n\rrCommandSM: Failed to transfer command. error number: %d",retVal);
                error_event.error_num = retVal;
                error_event.module = WLAN_MODULE_CMDSM;
                error_event.severity = WLAN_SEVERITY_HIGH;
                Wlan_HostSendEvent(WLAN_EVENT_ERROR, (uint8_t*)&error_event, sizeof(WlanEventError_t));
            }
            return;
        }
    }
    //hCbHndl != NULL means that it was called from the event system as a response
    else if ((cmdState ==CMD_SM_TRANSFERED)&&
            ((hCbHndl != NULL)|| 
			    (WLAN_RET_TIMEOUT == cmdCB->currentCommand->cmdStatus)))
    {
        cmdState = CMD_SM_COMPLETE;
        retVal = osi_TimerStop(&(cmdCB->timer));
        if (OSI_OK != retVal)
        {
             COMMAND_PRINT_ERROR("\n\rrCommandSM: Failed to stop timer. error number: %d",retVal);
             error_event.error_num = WLAN_RET_COMMAND_ERROR_MID_TYPE__TIMER_STOP;
             error_event.module = WLAN_MODULE_TMR;
             error_event.severity = WLAN_SEVERITY_MID;
             Wlan_HostSendEvent(WLAN_EVENT_ERROR, (uint8_t*)&error_event, sizeof(WlanEventError_t));
        }
        //general error means no error was returned from the send module and timeout
        //now we go and read the status, we assume device is awake because this is called from the FwEvents
        if (WLAN_RET_TIMEOUT == cmdCB->currentCommand->cmdStatus)
        {
            COMMAND_PRINT_ERROR("\n\rCommandSM: cmdStatus: CMD_ERR_TIMEOUT \n\r");
            wlanDispatcherSendEvent(WLAN_EVENT_COMMAND_TIMEOUT, NULL, 0);
        }
        else if (WLAN_RET_COMMAND_GENERAL == cmdCB->currentCommand->cmdStatus)
        {
            COMMAND_PRINT("\n\rCommandSM: cmdStatus: WLAN_RET_COMMAND_GENERAL was unsuccessful, reading complete\n\r");
        }
        else
        {
            //COMMAND_PRINT("\n\rCommandSM:  cmdStatus: %d was successful\n\r",cmdCB->currentCommand->cmdStatus);
        }

        //if there is a callback set, call it
        if(NULL != cmdCB->currentCommand->commandcallBack)
        {
            cmdCB->currentCommand->commandcallBack(cmdCB->currentCommand->cmdStatus,cmdCB->currentCommand->commandcallBackPt);
        }

        //set status on current command
        if (cmdCB->currentCommand->pSyncObjComplete != NULL)
        {
            COMMAND_PRINT("\n\rCommandSM: pSyncObjComplete \n\r");
            osi_SyncObjSignal(cmdCB->currentCommand->pSyncObjComplete);
        }
        //if sync obj is NULL it means we sent a command within the transport layer context and we
        //didn't free the command node in the send command, so we free it here
        else
        {
            os_free(cmdCB->currentCommand);
        }
        cmdCB->currentCommand = NULL;
        cmdState = CMD_SM_AVAILABLE;
        COMMAND_PRINT("\n\rCommandSM: cmdCB->currentCommand = NULL \n\r");

        COMMAND_PRINT("\n\rCommandSM: replace context to :%d \n\r",cmdCB->clientID);
        trnspt_RequestSchedule(cmdCB->clientID, FALSE);


}


}

void Timeout(void *params)
{
    if (NULL != cmdCB->currentCommand)
    {
        COMMAND_PRINT("timer interrupt function :timeout :%d !\n\r",cmdCB->clientID);
        cmdCB->currentCommand->cmdStatus = WLAN_RET_TIMEOUT;
        trnspt_RequestSchedule(cmdCB->clientID, 0);
    }
    else
    {
        ASSERT_GENERAL(0);
    }
}

extern uint32_t g_cmd_box_addr;
/**
 * cmd_Deinit - deinitialize the commands transfer module
 * @return CMD_ERR_XXX code
 */
int cmd_Deinit()
{
    cmdNode_t *pDequeue = NULL;
    if (NULL != cmdCB)
    {
        if (NULL != cmdCB->pMsgQ)
        {
            /* Dequeue and free all queued Commands */
            while (1)
            {
                cmd_lock();
                pDequeue = (cmdNode_t*) que_Dequeue(cmdCB->pMsgQ);
                cmd_unlock();
                if (pDequeue == NULL)
                {
                    break;
                }
                else
                {
                    osi_SyncObjDelete(pDequeue->pSyncObjComplete);
                    os_free(pDequeue->pSyncObjComplete);
                    os_free(pDequeue);
                    pDequeue = NULL;
                }
            }
            /* Queue destroy */
            que_Destroy(cmdCB->pMsgQ);
        }
        /* Delete timer */
        osi_TimerDelete(&(cmdCB->timer));

        osi_LockObjDelete(&cmdCB->cmd_lockObj);

        /* Free memory */
        os_free(cmdCB->scratchBuffer);
        os_free(cmdCB);
        cmdCB = NULL;

    }

    return CMD_OK;
}


void cmd_SetTimeoutMs(uint32_t timeMS)
{
    if(0 != timeMS)
    {
        cmdCB->timeout = timeMS;
    }
    else
    {
        cmdCB->timeout = CMD_TIMEOUT_MS;
    }
}


/**
 * cmd_Init - initialize the commands transfer module
 * @return CMD_ERR_XXX code
 */
int cmd_Init()
{
    void *pMsgQ;

    //allocate control block
    cmdCB = os_malloc(sizeof(cmdCB_t));
    if (NULL == cmdCB)
    {
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__MALLOC);
    }

    os_memset(cmdCB, 0, sizeof(cmdCB_t));

    cmdCB->maxCMDSize = CMD_MAX_SIZE;
    cmdCB->scratchBuffer = os_malloc(cmdCB->maxCMDSize);
    cmdCB->timeout = CMD_TIMEOUT_MS;

    if (NULL == cmdCB->scratchBuffer)
    {
        os_free(cmdCB);
        cmdCB = NULL;
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__MALLOC);
    }

    //cmdCB->pMsgQ create command queue
    pMsgQ = que_Create(CMD_MAX_QUEUE_SIZE, 0);

    if (NULL == pMsgQ)
    {
        os_free(cmdCB->scratchBuffer);
        os_free(cmdCB);
        cmdCB = NULL;
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__MSG_QUEUE_CREATE);
    }
    osi_LockObjCreate(&cmdCB->cmd_lockObj);

    cmdCB->pMsgQ = pMsgQ;
    cmdCB->MBOXAdder = g_cmd_box_addr;
    cmdCB->clientID = trnspt_RegisterClient((TTransportCbFunc) cmd_SM, TRUE);
    TRANSPORT_PRINT_INIT("\n\rRegister Client:cmd_SM uContextId :%d",cmdCB->clientID);
    osi_TimerCreate(&(cmdCB->timer), "commands", Timeout, (void *)cmdCB);
    return CMD_OK;
}


int cmd_SetBufferSize(uint32_t size)
{
    cmd_lock();

    if(cmdCB->scratchBuffer != NULL)
    {
        os_free(cmdCB->scratchBuffer);
        cmdCB->scratchBuffer = NULL;
    }
    
    if(size == 0)
    {
        cmdCB->scratchBuffer =  os_malloc(CMD_MAX_SIZE);
        cmdCB->maxCMDSize = CMD_MAX_SIZE;
    }
    else
    {
        cmdCB->scratchBuffer =  os_malloc(size);
        cmdCB->maxCMDSize = size;
    }

    if (NULL == cmdCB->scratchBuffer)
    {
        cmd_unlock();
        COMMAND_PRINT_ERROR("\n\rcan't allocate scratchBuffer");
        os_free(cmdCB);
        cmdCB = NULL;
        return WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__MALLOC);
    }
    
    cmd_unlock();
    return 0;
}


/**
 *
 * cmd_Send - send command to device
 *
 * @param in - input buffer for the command - will be copied
 * @param inLen - input length of the command
 * @param out - output buffer, could be NULL if no read from FW needed
 * @param outLen - output len
 * @return - 0 on success, CMD_ERR_XXX on fail
 *
 */
int cmd_Send(char *in, uint32_t inLen, char *out, uint32_t outLen)
{
    cmdNode_t *cmdNode = NULL;
    OsiSyncObj_t *cmdSyncObjComplete = NULL;
    int retVal = 0;

    if (NULL == cmdCB)
    {
        retVal = WLAN_RET_COMMAND_CMD_NOT_INITIALIZED;
        goto free;
    }

    cmdNode = os_zalloc(sizeof(cmdNode_t));
    if (NULL == cmdNode)
    {
        COMMAND_PRINT_ERROR("\n\rERROR cmd_Send allocation failed");
        retVal = WLAN_RET_COMMAND_ERROR_TYPE__MALLOC;
        goto free;
    }

    cmdSyncObjComplete = os_malloc(sizeof(OsiSyncObj_t));
    if (NULL == cmdSyncObjComplete)
    {
        COMMAND_PRINT_ERROR("\n\rERROR CMD_ERR_OUT_OF_MEMORY");
        retVal = WLAN_RET_COMMAND_ERROR_TYPE__MALLOC;
        goto free;
    }

    if (osi_SyncObjCreate(cmdSyncObjComplete) != OSI_OK)
    {
        COMMAND_PRINT_ERROR("\n\rERROR CMD_ERR_SYNC_OBJ");
        retVal = WLAN_RET_COMMAND_ERROR_MID_TYPE__SYNC_OBJ_CREATE;
        goto free;
    }

    cmdNode->outputBuffer = out;
    cmdNode->outputBufferLen = outLen;
    cmdNode->inputBuffer = in;
    cmdNode->inputBufferLen = inLen;
    cmdNode->pSyncObjComplete = cmdSyncObjComplete;
    cmdNode->commandcallBack = NULL;
    cmdNode->commandcallBackPt = NULL;


    cmd_lock();
    if (que_Enqueue(cmdCB->pMsgQ, cmdNode) < 0)
    {
        retVal = WLAN_RET_COMMAND_ERROR_MID_TYPE__MSG_QUEUE_CREATE;
        cmd_unlock();
        COMMAND_PRINT_ERROR("\n\rERROR cmd_SendInTransport***No room in queue pMsgQ*** line:%d\n", __LINE__);
        goto free;
    }
    cmd_unlock();

    //Only if there is no current command in process, ask for reschedule
    //because if there is command in process the SM needs to be triggered only from fwEvent upon command complete
    //or from timeout
    //after receiving the command complete or timeout, it will ask for reschedule
    COMMAND_PRINT("Command: cmd_Send, replace context :%d !\n\r",cmdCB->clientID);
    trnspt_RequestSchedule(cmdCB->clientID, 0);


    COMMAND_PRINT("\n\rcmd_Send Command: new command, waiting...\n\r");
    if (osi_SyncObjWait(cmdNode->pSyncObjComplete, CMD_SEND_TIMEOUT_MS) != OSI_OK)
    {
        COMMAND_PRINT_ERROR("\n\rcmd_Send Command: new command, failed waiting !!!!\n\r");
        retVal = WLAN_RET_COMMAND_ERROR_MID_TYPE__SYNC_OBJ_CREATE;
    }
    else
    {
        COMMAND_PRINT("\n\r cmd_Send: command done! cmdStatus:%d\n\r",cmdNode->cmdStatus);
        if((cmdNode->cmdStatus != CMD_OK))
        {
            COMMAND_PRINT_ERROR("\n\r cmd_Send: command done with error! cmdStatus:0x%x\n\r",cmdNode->cmdStatus);
        }
        retVal = cmdNode->cmdStatus;
    }

    //after finish to handle command, make sure that command sm will be performed again
    COMMAND_PRINT("Command: cmd_Send, replace context :%d !\n\r",cmdCB->clientID);
    trnspt_RequestSchedule(cmdCB->clientID, 0);


    free:
    if (NULL != cmdNode)
    {
        os_free(cmdNode);
    }
    if (NULL != cmdSyncObjComplete)
    {
        osi_SyncObjDelete(cmdSyncObjComplete);
        os_free(cmdSyncObjComplete);
    }

    return retVal;
}
void cmd_lock()
{
    /* Start critical section protection */
    osi_LockObjLock(&(cmdCB->cmd_lockObj), OSI_WAIT_FOREVER);
}

void cmd_unlock()
{
    /* Stop critical section protection */
    osi_LockObjUnlock(&(cmdCB->cmd_lockObj));
}
