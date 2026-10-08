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
#include "ble_transport.h"
#include "ble_if.h"
#include "nab.h"
#include "control_cmd_fw.h"
#include "commands.h"


/*****************************************************************************/
/* DEFINITIONS & GLOBALS                                                     */
/*****************************************************************************/
ble_event_cb_t event_cb = NULL;


/*****************************************************************************/
/* IMPLEMENTATION                                                            */
/*****************************************************************************/
static int BleSendFW_Command(void *cmd, uint32_t len)
{
    int ret = 0;

    cmd_ble_hci_command_t *cmdHdr = (cmd_ble_hci_command_t *)cmd;
    cmdHdr->cmdHeader.NAB_header.len = len;
    cmdHdr->cmdHeader.NAB_header.opcode = CMD_BLE_COMMANDS;
    cmdHdr->cmdHeader.NAB_header.sync_pattern = HOST_SYNC_PATTERN;
    cmdHdr->cmdHeader.id = CMD_BLE_COMMANDS;
    cmdHdr->cmdHeader.status = 0;

    ret = cmd_Send(cmd, len, NULL, 0);

    return ret;
}


int BleTransport_SendCommand(uint8_t* pBleCommand, uint16_t bleCmdLen)
{
    int ret = 0;
    cmd_ble_hci_command_t *cmd = NULL;
    uint32_t cmdSize = bleCmdLen + sizeof(cmd_ble_hci_command_t);

    //Allocate command memory
    cmd = os_malloc(cmdSize);

    if (NULL == cmd)
    {
        Report("\n\rCouldn't allocate memory for BLE command\n\r");
        ASSERT_GENERAL(0);
        return -1;
    }

    //Copy command data and command length
    os_memcpy(cmd->bleCmdParams.cmdData,pBleCommand,bleCmdLen);
    cmd->bleCmdParams.cmdLen = bleCmdLen;

    //Send the command
    ctrlCmdFw_LockHostDriver();
    ret = BleSendFW_Command((void*)cmd, cmdSize);
    ctrlCmdFw_UnlockHostDriver();

    //Free command memory
    os_free(cmd);

    return ret;
}


int BleTransport_BleEventHandler(void *pBleFwEvent)
{
    EventMailBox_t* pEvent = (EventMailBox_t*)pBleFwEvent;
    uint16_t dataLen;

    if (NULL == pBleFwEvent)
    {
        Report("\n\rERROR [BLE FW EVENT HANDLER] error pBleFwEvent is NULL\n\r");
        return (-1);
    }

    // Use local variable to avoid taking address of potentially packed member
    dataLen = pEvent->bleEvent.dataLen;
    if (BleIf_VendorSpecificEventHandler(pEvent->bleEvent.data, &dataLen))
    {
        return (0);
    }
    // Write back modified length to preserve original behavior
    pEvent->bleEvent.dataLen = dataLen;

    if (NULL == event_cb)
    {
        Report("\n\rERROR [BLE FW EVENT HANDLER] No callback was set\n\r");
        return (-1);
    }

    return event_cb(pEvent->bleEvent.data, pEvent->bleEvent.dataLen);
}

int BleTransport_EventCallbackbRegister(ble_event_cb_t cb)
{
    if (cb == NULL)
    {
        Report("\n\rERROR [BLE FW EVENT HANDLER] Registered callback is NULL\n\r");
        return (-1);
    }

    event_cb = cb;

    return 0;
}
