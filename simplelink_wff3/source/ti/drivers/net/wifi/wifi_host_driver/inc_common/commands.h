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
#ifndef _COMMANDS_H_
#define _COMMANDS_H_

//#define DEBUG_COMMANDS
#ifdef DEBUG_COMMANDS
#define COMMAND_PRINT Report
#define COMMAND_PRINT_ERROR Report
#else
#define COMMAND_PRINT(...)
#define COMMAND_PRINT_ERROR Report
#endif



#define CMD_MAX_QUEUE_SIZE (10)
#define CMD_TIMEOUT_MS (5000)

#define CMD_PAYLOAD_SIZE (932)

#define CMD_HEADER_SIZE (4)
#define CMD_MAX_SIZE (CMD_PAYLOAD_SIZE + CMD_HEADER_SIZE)


#define CMD_OK (0)                     //command returned OK
#define CMD_ERR_TIMEOUT (-1)           //command has timed out
#define CMD_ERR_TOO_LONG (-2)          //command is too long
#define CMD_ERR_INVALID_PARAM (-3)     //command parameter is invalid
#define CMD_ERR_OUT_OF_MEMORY (-4)     //Allocation problem
#define CMD_ERR_QUEUE_IS_FULL (-5)     //command queue is full
#define CMD_ERR_NOT_INITIALIZED (-6)   //command module not initialized
#define CMD_ERR_QUEUE (-7)             //general error in commands message queue
#define CMD_ERR_SYNC_OBJ (-8)          //general error in sync obj
#define CMD_ERR_GENERAL (-9)           //general error
#define CMD_MAX_COMMAND_ERROR (CMD_ERR_GENERAL)

//will not return as command error
#define CMD_BOOT_ERROR_WORKAROUND (17760)

typedef enum
{
    CMD_SM_AVAILABLE,
    CMD_SM_TRANSFERED,
    CMD_SM_COMPLETE,
}cmd_sm_states_t;

/**
 * cmd_ReadCompleteExternal - in some devices (osprey) command complete read with eventMbox
 *                            so it is externally dealt
 * @param inBuf input read buffer
 */
void cmd_ReadCompleteExternal(uint8_t *inBuf);



/**
 * cmd_SM - is the state machine of sending commands to the FW
 * @param flag reserved
 */
void cmd_SM(void* hCbHndl);

/**
 * cmd_Deinit - deinitialize the commands transfer module
 * @return CMD_ERR_XXX code
 */
int cmd_Deinit();

/**
 * cmd_Init - initialize the commands transfer module
 * @return CMD_ERR_XXX code
 */
int cmd_Init();

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
int cmd_Send(char *in,uint32_t inLen, char *out, uint32_t outLen);

/**
 * cmd_SetTimeoutMs - Set timeout in cmd control block
 *
 * @param timeMS - Timeout to be set in mSec
 */
void cmd_SetTimeoutMs(uint32_t timeMS);


/**
 * CmdCallbackFunction_t - cmd function pointer Callback
 *
 * @param cmdStatus - Status of current cmd
 * @param ptr - Pointer of current cmd
 */
typedef void (* CmdCallbackFunction_t)(int cmdStatus,void *ptr);

/**
 *
 * cmd_SendInTransport - send command to device with the transport context
 *
 * @param in - input buffer for the command - will be copied
 * @param inLen - input length of the command
 * @param cb - call back that will be called upon command complete
 * @param fb - call back parameters
 * @return - 0 on success, CMD_ERR_XXX on fail
 *
 */
int cmd_SendInTransport(char *in, uint32_t len, CmdCallbackFunction_t cb, void *fb);


/**
 *
 * cmd_SetBufferSize - Set scratchBuffer Size
 *
 * @param size - size of buffer
 * @return 1 on success, CMD_ERR_XXX on fail
 *
 */
int cmd_SetBufferSize(uint32_t size);
#endif
