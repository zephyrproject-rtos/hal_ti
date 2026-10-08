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
/*
 * hostdriver.c
 *
 *  Created on: 18 Oct 2021
 *      Author: a0387677
 */
#include <stdio.h>
#include <stdint.h>
#include "wlan_if.h"
#include "trnspt_thread.h"
#include "trnspt_if.h"
#include "commands.h"
#include "timer.h"
#include "bus_if.h"
#include <control_cmd_fw.h>
#include "fw_event_if.h"
#include <wlan_irq_adapt.h>
#include "errors.h"
#include "rx.h"
#include "tx.h"
#include "osi_kernel.h"
#include "cc3xxx_public_commands.h"
#include "fw_event_handle.h"
//#include "macro_utils.h"
#include "conf.h"
#include "public_types.h"
#include "drv_ti_internal.h"
#include "cme_supplicant_api.h"
#include "cme_dispatcher_api.h"
#include "init_host_if.h"
#include "cme_internal_api.h"

/*this is the NAB address for MX cmd APP2NAB_ADDR, it is not used on MX, because the SDIO wrapper is not there
 * so for passing the validation on twIf_Transact function, it is set the same as in LX */
uint32_t g_cmd_box_addr = NAB_DATA_ADDR ;
OsiLockObj_t driverLock = NULL;
OsiMsgQ_t eventMsgQueue = NULL;
OsiThread_t eventThread = NULL; //if threads are created by external app this may not be used
WlanEventHandlerCB_t userHandler = NULL;


/* WLAN event dispatcher to host */
extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t * args, uint16_t argsLen);

void eventEntryThread(void *params);


#define IS_WLAN_EVENT_MESSAGE_STOP_RUN(eventMessage)    ((*((uint8_t *)(eventMessage)) == 0xFF) && (*(((uint8_t *)(eventMessage)) + 1) == 0xFF))

#define CMD_UPPER_MAC_COMMANDS 35 //this can be any number, only rx and tx goes to specific location
#define CMD_CONTAINER_COMMANDS 36 //this can be any number, only rx and tx goes to specific location
#define CMD_BM_READ_DEVICE_INFO (CMD_UPPER_MAC_COMMANDS)

#define CASTED_MIN_TX_POWER ((int8_t)(WLAN_MIN_TX_POWER_DBM))
#define CASTED_MAX_TX_POWER ((int8_t)(WLAN_MAX_TX_POWER_DBM))

Bool_e gPlt = FALSE;
CalibratorPowerModes_e gPltState = PLT_OFF;
RoleID_t gTransceiverRoleId = INVALID_ROLE_ID;


uint8_t      gContRunThrdLoopEvent = TRUE;
OsiSyncObj_t gEventThrdRunStopSyncObject = NULL;
OsiSyncObj_t gThrdLoopStoppedEventSync = NULL;
OsiSyncObj_t gEventThrdDummySleep = NULL;

extern struct wpa_global *gpSupplicantGlobals;



int WLSendFW_CfgOrDebugCommand(uint16_t opcode, uint32_t id, void *cmd, uint32_t len, void *out, uint32_t outLen)
{
    int ret = 0;

    /* cmd cfg header is the same size as cmd debug header */
    cmd_generic_cfg_t *cmdHdr = (cmd_generic_cfg_t *)cmd;
    cmdHdr->cmdHeader.NAB_header.len = len;
    cmdHdr->cmdHeader.NAB_header.opcode = opcode;
    cmdHdr->cmdHeader.NAB_header.sync_pattern = HOST_SYNC_PATTERN;
    cmdHdr->cmdHeader.id = opcode;
    cmdHdr->cmdHeader.status = 0;
    cmdHdr->id = id;
    cmdHdr->len = len - sizeof(cmd_generic_cfg_t);


    ret = cmd_Send(cmd, len, out, outLen);

    return ret;
}

int WLSendFWGetDeviceInfoCommand(void *out, uint32_t outLen)
{
    cmd_download_t cmd_dnld;
    cmd_download_t* cmd = &cmd_dnld;
    int len = sizeof(cmd_dnld);

    int ret = 0;
    cmd_download_t *cmdHdr = (cmd_download_t *)cmd;
    cmdHdr->NAB_header.len = len + sizeof(cmd_download_t);
    cmdHdr->NAB_header.opcode = CMD_BM_READ_DEVICE_INFO;
    cmdHdr->NAB_header.sync_pattern = HOST_SYNC_PATTERN;
    cmdHdr->id = CMD_BM_READ_DEVICE_INFO;
    cmdHdr->status = 0;
    cmdHdr->length = len;

    ret = cmd_Send((char *)cmd, len + sizeof(cmd_download_t), out, outLen);

    return ret;
}

int WLSendFW_ConfigureCommand(uint32_t id, void *cmd, uint32_t len, void *out, uint32_t outLen)
{
    return WLSendFW_CfgOrDebugCommand(CMD_CONFIGURE, id, cmd, len, out, outLen);
}

int WLSendFW_InterrogateCommand(uint32_t id, void *cmd, uint32_t len, void *out, uint32_t outLen)
{
    return WLSendFW_CfgOrDebugCommand(CMD_INTERROGATE, id, cmd, len, out, outLen);
}

int WLSendFW_DebugCommand(uint32_t id, void *cmd, uint32_t len, void *out, uint32_t outLen)
{
    return WLSendFW_CfgOrDebugCommand(CMD_DEBUG, id, cmd, len, out, outLen);
}

int WLSendFW_DebugInterrogateCommand(uint32_t id, void *cmd, uint32_t len, void *out, uint32_t outLen)
{
    return WLSendFW_CfgOrDebugCommand(CMD_DEBUG_READ, id, cmd, len, out, outLen);
}

int WLSendFW_Command(uint16_t opcode, uint32_t id, void *cmd, uint32_t len, void *out, uint32_t outLen)
{
    int ret = 0;

    cmd_header_generic_t *cmdHdr = (cmd_header_generic_t *)cmd;
    cmdHdr->NAB_header.len = len;
    cmdHdr->NAB_header.opcode = opcode;
    cmdHdr->NAB_header.sync_pattern = HOST_SYNC_PATTERN;
    cmdHdr->id = opcode;
    cmdHdr->status = 0;
    ret = cmd_Send(cmd, len, out, outLen);

    return ret;
}


int ctrlCmdFw_GetCmdSize()
{
    return sizeof(cmd_download_t);
}

int WLSendFWDownloadCommand(void *cmd, uint32_t len, void *out,uint32_t outLen)
{
    int ret = 0;
    cmd_download_t *cmdHdr = (cmd_download_t *)cmd;
    cmdHdr->NAB_header.len = len + sizeof(cmd_download_t);
    cmdHdr->NAB_header.opcode = CMD_CONTAINER_COMMANDS;
    cmdHdr->NAB_header.sync_pattern = HOST_SYNC_PATTERN;
    cmdHdr->id = CMD_BM_CODE_DOWNLOAD;
    cmdHdr->status = 0;
    cmdHdr->length = len;

    ret = cmd_Send(cmd, len + sizeof(cmd_download_t), out, outLen);

    return ret;
}

int ctrlCmdFw_WLSendCommand(uint32_t id, void *cmd, uint32_t len, void *out,uint32_t outLen)
{
    int ret = 0;
    cmd_header_t *cmdHdr = (cmd_header_t *)cmd;
    cmdHdr->NAB_header.len = len;
    cmdHdr->NAB_header.opcode = CMD_UPPER_MAC_COMMANDS;
    cmdHdr->NAB_header.sync_pattern = HOST_SYNC_PATTERN;
    cmdHdr->id = CMD_UPPER_MAC_COMMANDS;
    cmdHdr->status = 0;
    cmdHdr->uppermacCommandID = id;

    ret = cmd_Send(cmd, len, out, outLen);

    return ret;
}

int cmdRoleDisable(RoleID_t *roleId)
{
    int ret = 0;
    cmd_role_disable_t cmdRoleDisable;

    if (*roleId == INVALID_ROLE_ID)
    {
        Report("\r\nCan't disable an invalid role");
    }

    cmdRoleDisable.roleId = *roleId;

    ret = WLSendFW_Command(CMD_ROLE_DISABLE,
                           CMD_ROLE_DISABLE,
                           (void *)&cmdRoleDisable,
                           sizeof(cmd_role_disable_t),
                           NULL,
                           0);

    *roleId = INVALID_ROLE_ID;

    return ret;
}

int cmdRoleEnable(RoleID_t *roleId, uint8_t *macAddress, RoleType_e roleType)
{
    int8_t rc, retVal;
    cmd_role_enable_t roleEnableCmd;
    CommandComplete_t cmdComplete;

    RoleEnableReturn_t *cmdReturn = (RoleEnableReturn_t*)&cmdComplete.info.param;
    RoleEnableParameters_t *cmdEnableParams = (RoleEnableParameters_t *)&roleEnableCmd.roleEnableParams;

    cmdEnableParams->roleType = roleType;
    cmdEnableParams->staRoleIdx = 0;
    os_memcpy(cmdEnableParams->macAddress, macAddress, MAC_ADDR_LEN);

    retVal = WLSendFW_Command(CMD_ROLE_ENABLE,
                              CMD_ROLE_ENABLE,
                              (void *)&roleEnableCmd,
                              sizeof(cmd_role_enable_t),
                              (char *)&(cmdComplete.info.param),
                              sizeof(RoleEnableReturn_t));

    cmdComplete.info.status = retVal;
    if (retVal >= 0)
    {
        rc = cmdComplete.info.status;
        *roleId = cmdReturn->roleID; // Save on global context and not in ptr?
        // Mark role wasn't started yet ?
    }
    else
    {
        rc =  -1;
    }

    return rc;
}

int cmdRoleStop(RoleID_t roleId)
{
    int ret = 0;
    cmd_role_stop_t cmdRoleStop;

    cmdRoleStop.roleId = roleId;

    ret = WLSendFW_Command(CMD_ROLE_STOP,
                           CMD_ROLE_STOP,
                           (void *)&cmdRoleStop,
                           sizeof(cmd_role_stop_t),
                           NULL,
                           0);
    return ret;
}

int transceiverRoleStop(RoleID_t roleId)
{
    int ret = 0;

    if (!gPlt)
    {
        return -1;
    }

    ret = cmdRoleStop(roleId);

    return ret;
}

int cmdRoleStart(RoleID_t roleId, RoleType_e roleType, uint8_t band, uint8_t channel)
{
    int ret = 0;
    cmd_role_start_t cmdRoleStart;

    cmdRoleStart.roleStartParams.roleType = roleType;
    cmdRoleStart.roleStartParams.roleID = roleId;
    cmdRoleStart.roleStartParams.band = band;
    cmdRoleStart.roleStartParams.channelNumber = channel;

    ret = WLSendFW_Command(CMD_ROLE_START,
                           CMD_ROLE_START,
                           (void *)&cmdRoleStart,
                           sizeof(cmd_role_start_t),
                           NULL,
                           0);
    return ret;
}

int cmdPltDisable()
{
    int ret = 0;
    cmd_plt_disable_t cmdPltDisable;

    ret = WLSendFW_Command(CMD_PLT_DISABLE,
                           CMD_PLT_DISABLE,
                           (void *)&cmdPltDisable,
                           sizeof(cmd_plt_disable_t),
                           NULL,
                           0);
    return ret;
}

int cmdPltEnable()
{
    int ret = 0;
    cmd_plt_enable_t cmdPltEnable;

    ret = WLSendFW_Command(CMD_PLT_ENABLE,
                           CMD_PLT_ENABLE,
                           (void *)&cmdPltEnable,
                           sizeof(cmd_plt_enable_t),
                           NULL,
                           0);
    return ret;
}

int ctrlCmdFw_pltInit()
{
    int ret = 0;
    RoleID_t roleId;
    uint8_t broadcastAddress[MAC_ADDR_LEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    if (gPltState == PLT_ON)
    {
        Report("\r\nPLT already on");
        return -1;
    }

    ret = cmdRoleEnable(&roleId, broadcastAddress, ROLE_TRANSCEIVER);
    gTransceiverRoleId = roleId;

    if (ret < 0)
    {
        Report("\r\nPLT role enable failed");
        return ret;
    }

    /* Default values are 2.4GHz and channel 6 */
    ret = cmdRoleStart(roleId, ROLE_TRANSCEIVER, 0, 6);

    if (ret < 0)
    {
        Report("\r\nPLT role start failed");
        cmdRoleDisable(&roleId);
        return ret;
    }

    ret = cmdPltEnable();
    if (ret < 0)
    {
        Report("\r\nPLT enable failed");

        ret = cmdRoleDisable(&roleId);
        if (ret < 0)
        {
            Report("\r\nPLT role disable failed");
        }

        ret = transceiverRoleStop(gTransceiverRoleId);
        return ret;
    }

    gPlt = TRUE;
    gPltState = PLT_ON;

    return ret;
}

int ctrlCmdFw_pltStop()
{
    int ret = 0;

    ret = transceiverRoleStop(gTransceiverRoleId);
    if (ret < 0)
    {
        return ret;
    }

    ret = cmdRoleDisable(&gTransceiverRoleId);

    if (ret < 0)
    {
        return ret;
    }

    cmdPltDisable();
    if (ret < 0)
    {
        return -1;
    }

    gPlt = FALSE;
    gPltState = PLT_OFF;

    return ret;
}

Bool_e isCalibratorPowerNeeded(CalibratorAction_e calibratorAction)
{
    Bool_e needed = FALSE;

    switch (calibratorAction)
    {
        case (CALIBRATOR_ACTION_RATE_OVERRIDE):
        case (CALIBRATOR_ACTION_GET_BEACON_RSSI):
        case (CALIBRATOR_ACTION_SET_GI_LTF):
        case (CALIBRATOR_ACTION_SET_UPLINK_MU):
        case (CALIBRATOR_ACTION_SET_OPERATION_MODE_CONTROL):
        case (CALIBRATOR_ACTION_SET_MCS_RATE):
        case (CALIBRATOR_ACTION_SET_UPLINK_MU_DATA):
        case (CALIBRATOR_ACTION_SET_PSM):
        case (CALIBRATOR_ACTION_SET_UPLINK_POWER_HEADER):
        case (CALIBRATOR_ACTION_SET_TRANSMIT_OMI):
        case (CALIBRATOR_ACTION_BA_SESSION):
        case (CALIBRATOR_ACTION_LINK_ADAPT):
        case (CALIBRATOR_ACTION_MANUAL_CALIBRATION):
        case (CALIBRATOR_ACTION_THERMAL_PROTECTION):
        case (CALIBRATOR_ACTION_GET_TEMPERATURE):
        case (CALIBRATOR_ACTION_LINK_ROBUSTNESS_BITMAP):
            needed = FALSE;
            break;
        default:
            needed = TRUE;
            break;
    }

    return needed;
}

int ctrlCmdFw_CalibratorCommand(CalibratorAction_e calibratorAction, void *calibratorCmdParams)
{
    int ret = 0;
    CommandComplete_t cmdComplete;

    if ((isCalibratorPowerNeeded(calibratorAction)) &&
        (FALSE == gPlt))
    {
        Report("\r\nError! Turn on calibrator first!");
        return -1;
    }

    switch (calibratorAction)
    {
    case (CALIBRATOR_ACTION_CHANNEL_TUNE):
    {
        CalibratorChannelTuneParams_t *tuneParams;
        cmd_test_channel_tune_t cmdChannelTune;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        tuneParams = (CalibratorChannelTuneParams_t *)calibratorCmdParams;

        os_memcpy(&cmdChannelTune.tuneParams, tuneParams, sizeof(CalibratorChannelTuneParams_t));

        cmdChannelTune.cmdTestHeader.cmdTestId = CC33XX_TEST_CMD_CHANNEL_TUNE;

        ret = WLSendFW_Command(CMD_TEST,
                               CMD_TEST,
                               &cmdChannelTune,
                               sizeof(cmd_test_channel_tune_t),
                               NULL,
                               0);
    }
        break;
    case (CALIBRATOR_ACTION_TX_START):
    {
        cmd_test_start_tx_t cmdStartTx;

        os_memset(&cmdStartTx.startTxParams, 0, sizeof(CalibratorStartTxParams_t));
        cmdStartTx.cmdTestHeader.cmdTestId = CC33XX_TEST_CMD_TX_START;

        ret = WLSendFW_Command(CMD_TEST,
                               CMD_TEST,
                               &cmdStartTx,
                               sizeof(cmd_test_start_tx_t),
                               NULL,
                               0);
    }
        break;
    case (CALIBRATOR_ACTION_TX_STOP):
    {
        cmd_test_stop_tx_t cmdStopTx;

        cmdStopTx.cmdTestHeader.cmdTestId = CC33XX_TEST_CMD_TX_STOP;

        ret = WLSendFW_Command(CMD_TEST,
                               CMD_TEST,
                               &cmdStopTx,
                               sizeof(cmd_test_stop_tx_t),
                               NULL,
                               0);
    }
        break;
    case (CALIBRATOR_ACTION_TX_TONE_START):
    {
        CalibratorStartTxToneParams_t *txToneParams;
        cmd_test_start_tx_tone_t cmdStartTxTone;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        txToneParams = (CalibratorStartTxToneParams_t *)calibratorCmdParams;

        os_memcpy(&cmdStartTxTone.startTxToneParams, txToneParams, sizeof(CalibratorStartTxToneParams_t));

        cmdStartTxTone.cmdTestHeader.cmdTestId = CC33XX_TEST_CMD_TX_TONE_START;

        ret = WLSendFW_Command(CMD_TEST,
                               CMD_TEST,
                               &cmdStartTxTone,
                               sizeof(cmd_test_start_tx_tone_t),
                               NULL,
                               0);
    }
        break;
    case (CALIBRATOR_ACTION_TX_TONE_STOP):
    {
        cmd_test_stop_tx_t cmdStopTxTone;

        cmdStopTxTone.cmdTestHeader.cmdTestId = CC33XX_TEST_CMD_TX_TONE_STOP;

        ret = WLSendFW_Command(CMD_TEST,
                               CMD_TEST,
                               &cmdStopTxTone,
                               sizeof(cmd_test_stop_tx_t),
                               NULL,
                               0);
    }
        break;
    case (CALIBRATOR_ACTION_SET_TX_PARAMS):
    case (CALIBRATOR_ACTION_SET_TB_TX_PARAMS):
    {
        CalibratorStartTxParams_t *setTxParams;
        cmd_test_set_tx_t cmdSetTx;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        setTxParams = (CalibratorStartTxParams_t *)calibratorCmdParams;

        os_memcpy(&cmdSetTx.setTxParams, setTxParams, sizeof(CalibratorStartTxParams_t));
        cmdSetTx.cmdTestHeader.cmdTestId = CC33XX_TEST_CMD_SET_PARAMS;

        ret = WLSendFW_Command(CMD_TEST,
                               CMD_TEST,
                               &cmdSetTx,
                               sizeof(cmd_test_set_tx_t),
                               NULL,
                               0);
    }
        break;
    case (CALIBRATOR_ACTION_GET_TX_PARAMS):
    {
        CalibratorStartTxParams_t *getTxParams;
        cmd_test_start_tx_t cmdGetTx;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        getTxParams = (CalibratorStartTxParams_t *)calibratorCmdParams;

        cmdGetTx.cmdTestHeader.cmdTestId = CC33XX_TEST_CMD_GET_PARAMS;

        ret = WLSendFW_Command(CMD_TEST,
                               CMD_TEST,
                               &cmdGetTx,
                               sizeof(cmd_test_start_tx_t),
                               &cmdComplete,
                               sizeof(uint16_t)/*sizeof(Command_e)*/ + \
                               sizeof(uint16_t)/*sizeof(CommandStatus_e)*/ + \
                               sizeof(TTestCmd_StartTX_t));

        os_memcpy(getTxParams, cmdComplete.info.param, sizeof(TTestCmd_StartTX_t));
    }
        break;
    case (CALIBRATOR_ACTION_START_RX):
    {
        CalibratorStartRxParams_t *startRxParams;
        cmd_test_start_rx_t cmdStartRx;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        startRxParams = (CalibratorStartRxParams_t *)calibratorCmdParams;

        os_memcpy(&cmdStartRx.startRxParams, startRxParams, sizeof(CalibratorStartRxParams_t));
        cmdStartRx.cmdTestHeader.cmdTestId = CC33XX_TEST_CMD_START_RX_SIMULATION;

        ret = WLSendFW_Command(CMD_TEST,
                               CMD_TEST,
                               &cmdStartRx,
                               sizeof(cmd_test_start_rx_t),
                               NULL,
                               0);
    }
    break;
    case (CALIBRATOR_ACTION_STOP_RX):
    {
        cmd_test_stop_rx_t cmdStopRx;
        cmdStopRx.cmdTestHeader.cmdTestId = CC33XX_TEST_CMD_STOP_RX_STATS;

        ret = WLSendFW_Command(CMD_TEST,
                               CMD_TEST,
                               &cmdStopRx,
                               sizeof(cmd_test_stop_rx_t),
                               NULL,
                               0);
    }
        break;
    case (CALIBRATOR_ACTION_GET_RX_STATS):
    {
        CalibratorGetRxParams_t *getRxParams;
        cmd_test_get_rx_stats_t cmdGetRxStats;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        getRxParams = (CalibratorGetRxParams_t *)calibratorCmdParams;

        cmdGetRxStats.cmdTestHeader.cmdTestId = CC33XX_TEST_CMD_GET_RX_STATS;

        ret = WLSendFW_Command(CMD_TEST,
                               CMD_TEST,
                               &cmdGetRxStats,
                               sizeof(cmd_test_get_rx_stats_t),
                               &cmdComplete,
                               sizeof(uint16_t)/*sizeof(Command_e)*/ + \
                               sizeof(uint16_t)/*sizeof(CommandStatus_e)*/ + \
                               sizeof(TransceiverRxStatCounters_t));

        os_memcpy(getRxParams, cmdComplete.info.param, sizeof(TransceiverRxStatCounters_t));
    }
        break;
    case(CALIBRATOR_ACTION_MANUAL_CALIBRATION):
    {
        uint16_t* pCalibration_bitmap;
        cmd_test_set_manual_calib_t cmdManualCalib;

        if (NULL == calibratorCmdParams)
        {
            return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__CMD_CTRL, WLAN_ERROR_TYPE__INVALID_PARAM_CALIBRATOR);
        }
        pCalibration_bitmap = (uint16_t*)(calibratorCmdParams);

        os_memcpy(&cmdManualCalib.calibration_bitmap, pCalibration_bitmap, sizeof(uint16_t));
        cmdManualCalib.cmdTestHeader.cmdTestId = CC33XX_TEST_CMD_MANUAL_CALIBRATION;

        ret = WLSendFW_Command(CMD_TEST,
                               CMD_TEST,
                               &cmdManualCalib,
                               sizeof(cmd_test_set_manual_calib_t),
                               NULL,
                               0);

    }
    break;
    case (CALIBRATOR_ACTION_RATE_OVERRIDE):
    {
        CalibratorRateOverrideParams_t *rateOverrideParams;
        cmd_debug_rate_override_dbg_t cmdRateOverride;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        rateOverrideParams = (CalibratorRateOverrideParams_t *)calibratorCmdParams;

        os_memcpy(&cmdRateOverride.rateOverrideParams, rateOverrideParams, sizeof(CalibratorRateOverrideParams_t));

        ret = WLSendFW_DebugCommand(RATE_OVERRRIDE_CFG,
                                    &cmdRateOverride,
                                    sizeof(cmd_debug_rate_override_dbg_t),
                                    NULL,
                                    0);
    }
        break;
    case (CALIBRATOR_ACTION_GET_BEACON_RSSI):
    {
        CalibratorBeaconRssiParams_t *beaconRssiParams;
        cmd_debug_beacon_rssi_dbg_t cmdGetBeaconRssi;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        beaconRssiParams = (CalibratorBeaconRssiParams_t *)calibratorCmdParams;

        ret = WLSendFW_DebugInterrogateCommand(BEACON_RSSI_INTR,
                                               &cmdGetBeaconRssi,
                                               sizeof(cmd_debug_beacon_rssi_dbg_t),
                                               &cmdComplete,
                                               sizeof(Command_e) + \
                                               sizeof(CommandStatus_e) + \
                                               sizeof(BeaconRssi_t));

        os_memcpy(beaconRssiParams, cmdComplete.info.param, sizeof(BeaconRssi_t));
    }
        break;
    case (CALIBRATOR_ACTION_SET_GI_LTF):
    {
        CalibratorGiLtfModeParams_t *giLtfParams;
        cmd_debug_gi_ltf_dbg_t cmdGiLtfCfg;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        giLtfParams = (CalibratorGiLtfModeParams_t *)calibratorCmdParams;

        os_memcpy(&cmdGiLtfCfg.giLtfParams, giLtfParams, sizeof(CalibratorGiLtfModeParams_t));

        ret = WLSendFW_DebugCommand(GI_LTF_CFG,
                                    &cmdGiLtfCfg,
                                    sizeof(cmd_debug_gi_ltf_dbg_t),
                                    NULL,
                                    0);
    }
        break;
    case (CALIBRATOR_ACTION_SET_UPLINK_MU):
    {
        CalibratorUplinkMuParams_t *uplinkMuParams;
        cmd_debug_uplink_mu_dbg_t cmdUplinkMuCfg;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        uplinkMuParams = (CalibratorUplinkMuParams_t *)calibratorCmdParams;

        os_memcpy(&cmdUplinkMuCfg.uplinkMuParams, uplinkMuParams, sizeof(CalibratorUplinkMuParams_t));

        ret = WLSendFW_DebugCommand(UPLINK_MULTI_USER_CFG,
                                    &cmdUplinkMuCfg,
                                    sizeof(cmd_debug_uplink_mu_dbg_t),
                                    NULL,
                                    0);
    }
        break;
    case (CALIBRATOR_ACTION_SET_OPERATION_MODE_CONTROL):
    {
        CalibratorOperationModeControlParams_t *operationModeControlParams;
        cmd_debug_operation_mode_control_dbg_t cmdOperationModeCfg;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        operationModeControlParams = (CalibratorOperationModeControlParams_t *)calibratorCmdParams;

        os_memcpy(&cmdOperationModeCfg.operationModeControlParams, operationModeControlParams, sizeof(CalibratorOperationModeControlParams_t));

        ret = WLSendFW_DebugCommand(OPERATION_MODE_CTRL_CFG,
                                    &cmdOperationModeCfg,
                                    sizeof(cmd_debug_operation_mode_control_dbg_t),
                                    NULL,
                                    0);
    }
        break;
    case (CALIBRATOR_ACTION_SET_MCS_RATE):
    {
        CalibratorSetMcsRateParams_t *mcsRateParams;
        cmd_debug_mcs_rate_dbg_t cmdMcsRateCfg;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        mcsRateParams = (CalibratorSetMcsRateParams_t *)calibratorCmdParams;

        os_memcpy(&cmdMcsRateCfg.mcsRateParams, mcsRateParams, sizeof(CalibratorSetMcsRateParams_t));

        ret = WLSendFW_DebugCommand(MCS_FIXED_RATE_CFG,
                                    &cmdMcsRateCfg,
                                    sizeof(cmd_debug_mcs_rate_dbg_t),
                                    NULL,
                                    0);
    }
        break;
    case (CALIBRATOR_ACTION_SET_UPLINK_MU_DATA):
    {
        CalibratorSetUplinkMuDataParams_t *uplinkMuDataParams;
        cmd_debug_uplink_mu_data_dbg_t cmdUplinkMuDataCfg;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        uplinkMuDataParams = (CalibratorSetUplinkMuDataParams_t *)calibratorCmdParams;

        os_memcpy(&cmdUplinkMuDataCfg.uplinkMuDataParams, uplinkMuDataParams, sizeof(CalibratorSetUplinkMuDataParams_t));

        ret = WLSendFW_DebugCommand(UPLINK_MULTI_USER_DATA_CFG,
                                    &cmdUplinkMuDataCfg,
                                    sizeof(cmd_debug_uplink_mu_data_dbg_t),
                                    NULL,
                                    0);
    }
        break;
    case (CALIBRATOR_ACTION_SET_PSM):
    {
        CalibratorSetPsmParams_t *setPsmParams;
        cmd_debug_psm_dbg_t cmdPsmCfg;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        setPsmParams = (CalibratorSetPsmParams_t *)calibratorCmdParams;

        os_memcpy(&cmdPsmCfg.forcePsmParams, setPsmParams, sizeof(CalibratorSetPsmParams_t));

        ret = WLSendFW_DebugCommand(FORCE_PS_CFG,
                                    &cmdPsmCfg,
                                    sizeof(cmd_debug_psm_dbg_t),
                                    NULL,
                                    0);
    }
        break;
    case (CALIBRATOR_ACTION_SET_UPLINK_POWER_HEADER):
    {
        CalibratorSetPowerHeaderParams_t *setPowerHeaderParams;
        cmd_debug_uplink_power_header_dbg_t cmdPowerHeaderCfg;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        setPowerHeaderParams = (CalibratorSetPowerHeaderParams_t *)calibratorCmdParams;

        os_memcpy(&cmdPowerHeaderCfg.powerHeaderParams, setPowerHeaderParams, sizeof(CalibratorSetPowerHeaderParams_t));

        ret = WLSendFW_DebugCommand(UPLINK_POWER_HEADER_CFG,
                                    &cmdPowerHeaderCfg,
                                    sizeof(cmd_debug_uplink_power_header_dbg_t),
                                    NULL,
                                    0);
    }
        break;
    case (CALIBRATOR_ACTION_SET_TRANSMIT_OMI):
    {
        CalibratorSetTransmitOmiParams_t *setTransmitOmiParams;
        cmd_debug_transmit_omi_dbg_t cmdTransmitOmiCfg;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        setTransmitOmiParams = (CalibratorSetTransmitOmiParams_t *)calibratorCmdParams;

        os_memcpy(&cmdTransmitOmiCfg.transmitOmiParams, setTransmitOmiParams, sizeof(CalibratorSetTransmitOmiParams_t));

        ret = WLSendFW_DebugCommand(TRANSMIT_OMI_CFG,
                                    &cmdTransmitOmiCfg,
                                    sizeof(cmd_debug_transmit_omi_dbg_t),
                                    NULL,
                                    0);
    }
        break;
    case (CALIBRATOR_ACTION_BA_SESSION):
    {
        CalibratorBASessionparams_t *BASessionParams;
        cmd_ba_session_debug_t cmdBASession;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        BASessionParams = (CalibratorBASessionparams_t *)calibratorCmdParams;

        os_memcpy(&cmdBASession.BASessionParams, BASessionParams, sizeof(BASessionCfg_t));

        ret = WLSendFW_DebugCommand(BA_SESSION_CFG,
                                    &cmdBASession,
                                    sizeof(cmd_ba_session_debug_t),
                                    NULL,
                                    0);
    }
        break;
    case (CALIBRATOR_ACTION_LINK_ADAPT):
    {
        CalibratorLinkAdaptParams_t *linkAdaptParams;
        cmd_link_adapt_debug_t cmdLinkAdapt;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        linkAdaptParams = (CalibratorLinkAdaptParams_t *)calibratorCmdParams;

        os_memcpy(&cmdLinkAdapt.linkAdaptParams, linkAdaptParams, sizeof(LinkAdaptDebugCfg_t));

        ret = WLSendFW_DebugCommand(LINK_ADAPT_CFG,
                                    &cmdLinkAdapt,
                                    sizeof(cmd_link_adapt_debug_t),
                                    NULL,
                                    0);
    }
        break;
    case (CALIBRATOR_ACTION_THERMAL_PROTECTION):
    {
        CalibratorThermalParams_t *thermalParams;
        cmd_debug_thermal_cfg_t cmdThermalCfg;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        thermalParams = (CalibratorThermalParams_t *)calibratorCmdParams;

        os_memcpy(&cmdThermalCfg.thermalCbParams, thermalParams, sizeof(ThermalCbCfg_t));

        ret = WLSendFW_DebugCommand(THERMAL_PROTECTION_CFG,
                                    &cmdThermalCfg,
                                    sizeof(cmd_debug_thermal_cfg_t),
                                    NULL,
                                    0);
    }
        break;
    case (CALIBRATOR_ACTION_GET_TEMPERATURE):
    {
        CalibratorGetTemperature_t *temperatureGetParams;
        cmd_debug_temperature_get_t cmdTemperatureGet;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        temperatureGetParams = (CalibratorGetTemperature_t *)calibratorCmdParams;

        ret = WLSendFW_DebugInterrogateCommand(TEMPERATURE_GET_INTR,
                                               &cmdTemperatureGet,
                                               sizeof(cmd_debug_temperature_get_t),
                                               &cmdComplete,
                                               sizeof(Command_e) + \
                                               sizeof(CommandStatus_e) + \
                                               sizeof(TemperatureGet_t));

        os_memcpy(temperatureGetParams, cmdComplete.info.param, sizeof(TemperatureGet_t));
    }
        break;
    case (CALIBRATOR_ACTION_LINK_ROBUSTNESS_BITMAP):
    {
        CalibratorLinkRobustnessBitmap_t *linkRobustnessBitmapParams;
        cmd_debug_link_robustness_bitmap_t cmdLinkRobustnessBitmap;

        if (NULL == calibratorCmdParams)
        {
            return -1;
        }
        linkRobustnessBitmapParams = (CalibratorLinkRobustnessBitmap_t *)calibratorCmdParams;

        os_memcpy(&cmdLinkRobustnessBitmap.linkRobustnessBitmapParams, linkRobustnessBitmapParams, sizeof(LinkRobustnessBitmapCfg_t));

        ret = WLSendFW_DebugCommand(LINK_ROBUSTNESS_BITMAP_CFG,
                                    &cmdLinkRobustnessBitmap,
                                    sizeof(cmd_debug_link_robustness_bitmap_t),
                                    NULL,
                                    0);
    }
        break;
    default:
        Report("\r\nUnknown calibrator action requested.");
        break;
    }

    return ret;
}

Bool_e FindCalibrationData(uint8_t *mac, FILE *fileHandle, uint32_t *offset, uint16_t entriesNum, uint16_t *payloadLen)
{
    calibration_header_t *headerBuffer;
    calibration_header_fw_t *fwHeaderBuffer;
    Bool_e match = FALSE;
    uint16_t entriesTraveled = 0;
    uint8_t defaultMac[MAC_ADDR_SIZE] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uint32_t defaultOffset = 0;
    uint16_t defaultPayloadLen = 0;

    uint32_t entryHeaderSize = sizeof(calibration_header_t);
    headerBuffer = os_malloc(entryHeaderSize);
    if (NULL == headerBuffer)
    {
        Report("\n\rCouldn't allocate memory for entry header\n\r");
        ASSERT_GENERAL(0);
    }

    do {
        // Cast to a struct for convenient fields reading
        osi_fread(headerBuffer, entryHeaderSize, *offset, fileHandle);
        fwHeaderBuffer = &(headerBuffer->calHeaderFw);

        if (headerBuffer->staticPattern != 0x7F7F)
        {
            break;
        }

        if (0 == os_memcmp(fwHeaderBuffer->chipId, mac, MAC_ADDR_SIZE))
        {
            // If match found, update the offset related to the file beginning.
            match = TRUE;
            *payloadLen = fwHeaderBuffer->length;
            *offset += sizeof(headerBuffer->staticPattern);  // Skip static pattern in offset
            break;
        }
        // If encountered default calibration values, save an offset to it, but keep searching for a match
        else if (0 == os_memcmp(fwHeaderBuffer->chipId, defaultMac, MAC_ADDR_SIZE))
        {
            defaultPayloadLen = fwHeaderBuffer->length;
            defaultOffset = *offset + sizeof(headerBuffer->staticPattern);
        }

        *offset += fwHeaderBuffer->length + entryHeaderSize;
        entriesTraveled++;
    } while (entriesTraveled < entriesNum);

    // If there's no mac match, but default calibration values exist, use default
    if ((FALSE == match) && (defaultPayloadLen != 0))
    {
         match = TRUE;
         *payloadLen = defaultPayloadLen;
         *offset = defaultOffset;
         Report("\n\rStatic Calibration: WARNING! No MAC address match, using default calibration!\n\r");
    }

    os_free(headerBuffer);
    return match;
}

Bool_e GetDeviceCalibrationData(uint8_t *mac, FILE *fileHandle, uint32_t *offset, uint16_t *payloadLen)
{
    char fileHeaderBuffer[CALIBRATION_FILE_HEADER_SIZE];
    Bool_e match = FALSE;
    calibration_file_header_t *fileHeader;

    osi_fread(fileHeaderBuffer, CALIBRATION_FILE_HEADER_SIZE, *offset, fileHandle);
    *offset += CALIBRATION_FILE_HEADER_SIZE;
    fileHeader = (calibration_file_header_t *)fileHeaderBuffer;

    match = FindCalibrationData(mac, fileHandle, offset, fileHeader->entriesCount, payloadLen);

    return match;
}

int SendCalibrationCmd(FILE *calibrationFile, uint32_t offset, uint16_t payloadLen, Bool_e validData)
{
    // Send cmd to FW
    char fileHeaderBuffer[CALIBRATION_FILE_HEADER_SIZE];
    calibration_file_header_t *fileHeader;
    static_calibration_cmd_t *cmd = NULL;
    uint32_t cmdSize;
    int ret = 0;

    if (validData)
    {
        cmdSize = sizeof(static_calibration_cmd_t) + payloadLen;
    }
    else
    {
        cmdSize = sizeof(static_calibration_cmd_t);
    }

    ALIGNN_TO_4(cmdSize);

    cmd = os_malloc(cmdSize);

    if (NULL == cmd)
    {
        Report("\n\rCouldn't allocate memory for calibration command\n\r");
        ASSERT_GENERAL(0);
    }
    
    osi_fread(fileHeaderBuffer, CALIBRATION_FILE_HEADER_SIZE, 0, calibrationFile);
    fileHeader = (calibration_file_header_t *)fileHeaderBuffer;

    cmd->validData = validData;
    cmd->fileVersion = fileHeader->fileVersion;
    cmd->payloadStructVersion = fileHeader->payloadStructVersion;

    if (validData)
    {
        osi_fread(&(cmd->calHeader), sizeof(calibration_header_fw_t) + payloadLen, offset, calibrationFile);
    }

    ctrlCmdFw_LockHostDriver();

    ret = WLSendFW_ConfigureCommand(STATIC_CALIBRATION_CFG, cmd, cmdSize, NULL, 0);

    ctrlCmdFw_UnlockHostDriver();

    os_free(cmd);

    return ret;
}

int ctrlCmdFw_DownloadStaticCalibration()
{
    uint32_t offset = 0;
    uint16_t payloadLen = 0;
    Bool_e match = FALSE;
    int ret = 0;
    int i;

    unsigned char staticCalMacAddress[MAC_ADDR_SIZE] = { 0 };

    WlanMacAddress_t macAddressParams;
    memset(&macAddressParams, 0, sizeof(WlanMacAddress_t));

    CME_GetMacAddress(WLAN_ROLE_STA, macAddressParams.pMacAddress);


    for (i = 0; i < MAC_ADDR_SIZE; i++)
    {
        staticCalMacAddress[i] = macAddressParams.pMacAddress[MAC_ADDR_SIZE - 1 - i];
    }

    FILE *calibrationFileHandle = osi_fopen("static_calibration", "rb");


    match = GetDeviceCalibrationData(staticCalMacAddress, calibrationFileHandle, &offset, &payloadLen);

    if (FALSE == match)
    {
        Report("\n\rStatic Calibration: WARNING! No MAC address match and no default calibration!\n\r");
    }


    ret = SendCalibrationCmd(calibrationFileHandle, offset, payloadLen, match);

    osi_fclose(calibrationFileHandle);
    return ret;
}



int ctrlCmdFw_DownloadIniParams()
{
    // Send cmd to FW
    cmd_ini_params_download_t *cmd = NULL;
    uint32_t cmdIniSize;
    uint32_t cmdSizeForIni = CMD_MAX_SIZE;
    FILE *iniFileHandle = NULL;
    int ret = 0;

    if (CMD_INI_FILE_SIZE > CMD_MAX_SIZE)
    {
        cmdSizeForIni = CMD_INI_FILE_SIZE;
    }

    cmd_SetBufferSize(cmdSizeForIni);

    cmdIniSize = sizeof(cmd_ini_params_download_t) + CC33X_CONF_SIZE;

    cmdIniSize = ALIGNN_TO_4(cmdIniSize);

    cmd = os_malloc(cmdIniSize);

    if (NULL == cmd)
    {
        Report("\n\rCouldn't allocate memory for configuration command\n\r");
        ASSERT_GENERAL(0);
    }

    iniFileHandle = osi_fopen("cc35xx-conf", "rb");
    if (!iniFileHandle)
    {
        Report("\n\rERROR: Can't open/find cc35xx-conf.bin file\n\r");
        ASSERT_GENERAL(0);
    }
    else
    {
        size_t bytesRead = 0;
        bytesRead = osi_fread((cmd->payload), CC33X_CONF_SIZE, 0, iniFileHandle);
        if (bytesRead != CC33X_CONF_SIZE)
        {
            Report("\n\rERROR: Failed to read complete configuration file");
            ASSERT_GENERAL(0);
        }
        cmd->length = CC33X_CONF_SIZE;
        osi_fclose(iniFileHandle);
    }

    InitIniParamsHost(cmd);

    ctrlCmdFw_LockHostDriver();

    WLSendFW_Command(CMD_DOWNLOAD_INI_PARAMS, CMD_DOWNLOAD_INI_PARAMS, cmd, cmdIniSize, NULL, 0);

    ctrlCmdFw_UnlockHostDriver();


    os_free(cmd);

    //return cmd buffer to default buffer with buffer size = CMD_MAX_SIZE
    ret = cmd_SetBufferSize(0);
    if(ret < 0)
    {
        Report("\r\nERROR ! Failed to Allocate Memory for cmd Buffer: %d", ret);
    }

    return ret;

}

int ctrlCmdFw_FirstCommand()
{
    // Send cmd to FW
    cmd_first_params_download_t *cmd = NULL;
    uint32_t cmdSize;
    uint32_t cmdSizeForCommand = CMD_MAX_SIZE;
    int ret = 0;

    cmd_SetBufferSize(cmdSizeForCommand);

    cmdSize = sizeof(cmd_first_params_download_t);
    
    cmdSize = ALIGNN_TO_4(cmdSize);

    if (cmdSize > CMD_MAX_SIZE)
    {
        Report("\n\rERROR: Cmd size (%d) exceeds the max size (%d)!\n\r", cmdSize, CMD_MAX_SIZE);
        ASSERT_GENERAL(0);
    }
    if (cmdSize != sizeof(cmd_first_params_download_t))
    {
        Report("\n\rCmd size is not 4 byte aligned!!! %d (%d)\n\r", cmdSize, sizeof(cmd_first_params_download_t));
    }

    cmd = os_malloc(cmdSize);

    //Set Core status address
    cmd->core_status.header.type = CMD_FIRST_TYPE_CORE_ADDR; 
    cmd->core_status.header.length = sizeof(cmd->core_status.addr);
    cmd->core_status.addr = 0x41C40000;

    cmd->data.header.type = 0x01; // Reserved
    cmd->data.header.length = 254;

    os_memset(cmd->data.data, 5, 254); // Initialize data to zero

    //must be last command
    cmd->end_of_cmd.type = CMD_FIRST_TYPE_END; // End of command
    cmd->end_of_cmd.length = 0x00; // Length of the value (0 bytes for end of command)


    if (NULL == cmd)
    {
        Report("\n\rCouldn't allocate memory for calibration command\n\r");
        ASSERT_GENERAL(0);
        return OSI_MEMORY_ALLOCATION_FAILURE;
    }

    ctrlCmdFw_LockHostDriver();

    WLSendFW_Command(CMD_DOWNLOAD_FIRST_CMD, CMD_DOWNLOAD_FIRST_CMD, cmd, cmdSize, NULL, 0);

    ctrlCmdFw_UnlockHostDriver();

    os_free(cmd);

    //return cmd buffer to default buffer with buffer size = CMD_MAX_SIZE
    ret = cmd_SetBufferSize(0);
    if(ret < 0)
    {
        Report("Failed to Allocate Memory for cmd Buffer");
        ASSERT_GENERAL(0);
        return OSI_MEMORY_ALLOCATION_FAILURE;
    }

    return ret;
}


int ctrlCmdFw_EnableBLECmd()
{
    // Send cmd to FW
    EnableBLE_cmd_t *cmd = NULL;
    uint32_t cmdSize = sizeof(EnableBLE_cmd_t);
    int ret = 0;

    cmd = os_malloc(cmdSize);

    if (NULL == cmd)
    {
        Report("\n\rCouldn't allocate memory for BLE enable command\n\r");
        ASSERT_GENERAL(0);
    }

    ctrlCmdFw_LockHostDriver();

    ret = WLSendFW_DebugCommand(BLE_ENABLE, cmd, cmdSize, NULL, 0);

    ctrlCmdFw_UnlockHostDriver();

    os_free(cmd);

    wlanDispatcherSendEvent(WLAN_EVENT_BLE_ENABLED, (void*)(&ret), sizeof(ret));

    return ret;
}

int ctrlCmdFw_TriggerFwAssert()
{
    int ret = 0;
    cmd_debug_header_t cmdDebugHeader;

    ret = WLSendFW_DebugCommand(TRIGGER_FW_ASSERT,
                                &cmdDebugHeader,
                                sizeof(cmd_debug_header_t),
                                NULL,
                                0);
    
    return ret;
}

int ctrlCmdFw_EnableCsiCmd(uint8_t enable)
{
    int ret = 0;
    cmd_csi_enable_t cmdCsiEnable;
    cmdCsiEnable.csi_Enable = enable;

    ret = WLSendFW_Command(CMD_CSI_ENABLE,
                           CMD_CSI_ENABLE,
                           (void *)&cmdCsiEnable,
                           sizeof(cmd_csi_enable_t),
                           NULL,
                           0);

    return ret;
}

int ctrlCmdFw_CfgCsiSolicitation(uint8_t enable, uint8_t period, uint8_t expiry)
{
    int ret = 0;
    cmd_cfg_csi_solicitation_t cmd;

    cmd.csiSolEnable = enable;
    cmd.csiSolPeriod = period;
    cmd.csiSolExpiry = expiry;

    ret = WLSendFW_Command(CMD_CSI_SOL_ENABLE,
                           CMD_CSI_SOL_ENABLE,
                           (void *)&cmd,
                           sizeof(cmd_cfg_csi_solicitation_t),
                           NULL,
                           0);

    return ret;
}  

int ctrlCmdFw_CfgCsiSolSetMac(uint8_t csiSolAddRemoveMac, uint8_t csiSolMacAddress[MAC_ADDR_LEN])
{
    int ret = 0;
    cmd_cfg_csi_sol_edit_mac_t cmd;
    
    cmd.csiSolAddRemoveMac = csiSolAddRemoveMac;
    os_memcpy(cmd.csiSolMacAddress, csiSolMacAddress, sizeof(uint8_t) * MAC_ADDR_LEN);

    ret = WLSendFW_Command(CMD_CSI_SOL_MAC_EDIT,
                           CMD_CSI_SOL_MAC_EDIT,
                           (void *)&cmd,
                           sizeof(cmd_cfg_csi_sol_edit_mac_t),
                           NULL,
                           0);

    return ret;
}  

int ctrlCmdFw_SetBdAddrCmd(const unsigned char *pBdAddr)
{
    int ret = 0;
    cmd_set_bd_addr_t cmd;

    os_memcpy(cmd.setBdAddrCmd.BdAddr, pBdAddr, MAC_ADDR_LEN);

    ret = WLSendFW_Command(CMD_SET_BD_ADDR,
                           CMD_SET_BD_ADDR,
                           (void *)&cmd,
                           sizeof(cmd_set_bd_addr_t),
                           NULL,
                           0);

    return ret;
}

int ctrlCmdFw_GetMemMap(MemoryMap_t *mem_map)
{
    cmd_interrogate_get_memoryMap_t cmdMemMap;
    CommandComplete_t cmdComplete;
    int ret = 0;

    cmdMemMap.cmdInterrogateHeader.id = MEM_MAP_INTR;

    ret = WLSendFW_InterrogateCommand(MEM_MAP_INTR,
                                      &cmdMemMap,
                                      sizeof(cmdMemMap),
                                      &cmdComplete,
                                      sizeof(uint16_t)/*sizeof(Command_e)*/ + \
                                      sizeof(uint16_t)/*sizeof(CommandStatus_e)*/ + \
                                      sizeof(MemoryMap_t));


    os_memcpy(mem_map, cmdComplete.info.param, sizeof(MemoryMap_t));
    return ret;
}

int ctrlCmdFw_SetSeedCmd(uint8_t *pSeed, uint8_t size)
{
    cmd_cfg_seed_t cmd;

    os_memcpy(cmd.seed, pSeed, size);

    return WLSendFW_ConfigureCommand(SET_SEED_CFG,
                                     &cmd,
                                     sizeof(cmd_cfg_seed_t),
                                     NULL,
                                     0);
}

int ctrlCmdFw_GetFwVersion(FWVersions_t* FwVersion)
{
    cmd_interrogate_get_fwversion_t cmdGetFwVersion;
    CommandComplete_t cmdComplete;
    int ret;

    cmdGetFwVersion.cmdInterrogateHeader.id = GET_FW_VERSIONS_INTR;

    ret = WLSendFW_InterrogateCommand(GET_FW_VERSIONS_INTR,
                                      &cmdGetFwVersion,
                                      sizeof(cmdGetFwVersion),
                                      &cmdComplete,
                                      sizeof(uint16_t)/*sizeof(Command_e)*/ + \
                                      sizeof(uint16_t)/*sizeof(CommandStatus_e)*/ + \
                                      sizeof(FWVersions_t));


    os_memcpy(FwVersion, cmdComplete.info.param, sizeof(FWVersions_t));
    return ret;
}

int ctrlCmdFw_GetSpVersion(SPVersions_t* SpVersion)
{
    cmd_interrogate_get_spversion_t cmdGetSpVersion;
    CommandComplete_t cmdComplete;
    int ret;

    cmdGetSpVersion.cmdInterrogateHeader.id = GET_SP_VERSIONS_INTR;

    ret = WLSendFW_InterrogateCommand(GET_SP_VERSIONS_INTR,
                                      &cmdGetSpVersion,
                                      sizeof(cmdGetSpVersion),
                                      &cmdComplete,
                                      sizeof(uint16_t)/*sizeof(Command_e)*/ + \
                                      sizeof(uint16_t)/*sizeof(CommandStatus_e)*/ + \
                                      sizeof(SPVersions_t));


    os_memcpy(SpVersion, cmdComplete.info.param, sizeof(SPVersions_t));
    return ret;
}

int ctrlCmdFw_GetRssi(BeaconRssi_t* rssi)
{
    cmd_interrogate_get_rssi_t cmdGetRssi;
    CommandComplete_t cmdComplete;
    int ret;

    cmdGetRssi.BeaconRssi.role_id = WLAN_ROLE_STA;
    cmdGetRssi.cmdInterrogateHeader.id = RSSI_INTR;

    ret = WLSendFW_InterrogateCommand(RSSI_INTR,
                                      &cmdGetRssi,
                                      sizeof(cmdGetRssi),
                                      &cmdComplete,
                                      sizeof(uint16_t)/*sizeof(Command_e)*/ + \
                                      sizeof(uint16_t)/*sizeof(CommandStatus_e)*/ + \
                                      sizeof(BeaconRssi_t));


    os_memcpy(rssi, cmdComplete.info.param, sizeof(BeaconRssi_t));
    return ret;
}

#ifdef NOISE_FLOOR //not defined on CC3xxx
int ctrlCmdFw_GetNoiseFloor(NoiseFloor_t* noiseFloor)
{
    cmd_interrogate_get_noise_floor_t cmdGetNoiseFloor;
    CommandComplete_t cmdComplete;
    int ret;

    uint32_t roleId;
    roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_STA);

    if (roleId == ROLE_ID_NONE)
    {
        Report("\n\rError: Role Does Not Exist!!, Role Type %d\n\r", ROLE_STA);
        return -1;
    }

    int is_sta_connected = CmeStationFlow_GetCurrentState() == CME_STA_CONFIGURED_STATE;

    if (is_sta_connected)
    {
        cmdGetNoiseFloor.NoiseFloor.role_id = roleId;
    }
    else
    {
        Report("\n\rError: STA is not connected!!\n\r");
        return -1;
    }
    cmdGetNoiseFloor.NoiseFloor.noise_floor_avg = 0;

    ret = WLSendFW_InterrogateCommand(NOISE_FLOOR_INTR,
                                      &cmdGetNoiseFloor,
                                      sizeof(cmdGetNoiseFloor),
                                      &cmdComplete,
                                      sizeof(uint16_t)/*sizeof(Command_e)*/ + \
                                      sizeof(uint16_t)/*sizeof(CommandStatus_e)*/ + \
                                      sizeof(NoiseFloor_t));

    os_memcpy(noiseFloor, cmdComplete.info.param, sizeof(NoiseFloor_t));
    return ret;
}
#endif

int ctrlCmdFw_GetChannelUtilizationResults(WlanChannel_utilize_res_t* res)
{
    cmd_interrogate_get_channel_utilization_results_t cmdGetScanCUResult;
    CommandComplete_t cmdComplete;
    WlanChannel_utilize_res_t *channel_util = NULL;
    int ret;

    cmdGetScanCUResult.cmdInterrogateHeader.id = GET_LATEST_CHANNEL_UTILIZATION_SURVEY;

    ret = WLSendFW_InterrogateCommand(GET_LATEST_CHANNEL_UTILIZATION_SURVEY, 
                                      &cmdGetScanCUResult, 
                                      sizeof(cmdGetScanCUResult), 
                                      &cmdComplete,
                                      sizeof(uint16_t) + sizeof(uint16_t) + (sizeof(WlanChannel_utilize_res_t) * CHANNELS_COUNT));

    os_memcpy(res, cmdComplete.info.param, sizeof(WlanChannel_utilize_res_t) * CHANNELS_COUNT);
    
    return ret;
}

int ctrlCmdFw_GetRoleChannelNumber(WlanRole_current_channel_number* currentRoleChannelParam)
{
    cmd_interrogate_get_role_channel_number_cmd_t cmdGetCurrentRoleChannelParam;
    CommandComplete_t cmdComplete;
    int ret;
    cmdGetCurrentRoleChannelParam.cmdInterrogateHeader.id = GET_ROLE_CHANNEL_NUMBER;

    uint32_t role_bitmap = CME_GetStartedRoleBitmap();
    if (!(role_bitmap & BIT_x(ROLE_AP)))
    {
        Report("\n\rAP role is not up!\n\r");
        ret = -1;
        return ret;
    }

    uint8_t roleId = drv_getRoleIdFromType(gpSupplicantGlobals, currentRoleChannelParam->roleType);
    if(roleId == ROLE_ID_NONE)
    {
        Report("\n\rError: Role Does Not Exist!!, Role Type %d\n\r",currentRoleChannelParam->roleType);
        ret = -1;
        return ret ;
    }

    cmdGetCurrentRoleChannelParam.roleChannel.roleId = roleId;

    ret = WLSendFW_InterrogateCommand(GET_ROLE_CHANNEL_NUMBER, 
                                      &cmdGetCurrentRoleChannelParam, 
                                      sizeof(cmdGetCurrentRoleChannelParam), 
                                      &cmdComplete,
                                      sizeof(uint16_t) + sizeof(uint16_t) + (sizeof(WlanRole_current_channel_number)));

    
    os_memcpy(currentRoleChannelParam, cmdComplete.info.param, sizeof(WlanRole_current_channel_number));
    return ret;
}

int ctrlCmdFw_GetDecryptedPacketCounts(WlanDecrypted_packetsCounters_t * packets_count)
{
    cmd_interrogate_get_decrypt_packets_status_count_t cmdGetDecryptPacketCount;
    CommandComplete_t cmdComplete;
    int ret;

    uint8_t roleId = drv_getRoleIdFromType(gpSupplicantGlobals, ROLE_STA);

    if(roleId == ROLE_ID_NONE)
    {
        Report("\n\rError: Role Does Not Exist!!, Role Type %d\n\r", ROLE_STA);
        os_memset(packets_count, 0, sizeof(WlanDecrypted_packetsCounters_t ));
        ret = -1;
        return ret ;
    }

    cmdGetDecryptPacketCount.cmdInterrogateHeader.id = GET_DECRYPT_PACKETS_COUNTS;
    cmdGetDecryptPacketCount.count.roleid = roleId;

    ret = WLSendFW_InterrogateCommand(GET_DECRYPT_PACKETS_COUNTS, 
                                      &cmdGetDecryptPacketCount, 
                                      sizeof(cmdGetDecryptPacketCount), 
                                      &cmdComplete,
                                      sizeof(uint16_t) + sizeof(uint16_t) + (sizeof(WlanDecrypted_packetsCounters_t ) ));

    
    os_memcpy(packets_count, cmdComplete.info.param, sizeof(WlanDecrypted_packetsCounters_t ));
    return ret;
}

int ctrlCmdFw_GetAntennaStatus(uint8_t *status)
{
    cmd_interrogate_antenna_diversity_status_t cmdGetAntennaStatus;
    CommandComplete_t cmdComplete;
    int ret;

    cmdGetAntennaStatus.cmdInterrogateHeader.id = GET_ANT_DIV_STATUS;

    ret = WLSendFW_InterrogateCommand(GET_ANT_DIV_STATUS,
                                      &cmdGetAntennaStatus,
                                      sizeof(cmdGetAntennaStatus),
                                      &cmdComplete,
                                      sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint8_t));

    *status = cmdComplete.info.param[0];
    return ret;
}

int ctrlCmdFw_SetAntennaStatus(uint8_t enable)
{
    cmd_cfg_antenna_status_t cmd;

    cmd.enable = enable;

    return WLSendFW_ConfigureCommand(ANT_DIV_ENABLE, &cmd, sizeof(cmd), NULL, 0);
}

int ctrlCmdFw_GetAntennaRssiThreshold(int8_t *threhold)
{
    cmd_interrogate_antenna_diversity_rssi_threshold_t cmdGetAntennaRssiThreshold;
    CommandComplete_t cmdComplete;
    int ret;

    cmdGetAntennaRssiThreshold.cmdInterrogateHeader.id = GET_ANT_DIV_RSSI_THRESHOLD;

    ret = WLSendFW_InterrogateCommand(GET_ANT_DIV_RSSI_THRESHOLD,
                                      &cmdGetAntennaRssiThreshold,
                                      sizeof(cmdGetAntennaRssiThreshold),
                                      &cmdComplete,
                                      sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint8_t));

    *threhold = cmdComplete.info.param[0];
    return ret;
}

int ctrlCmdFw_SetAntennaRssiThreshold(int8_t threshold)
{
    cmd_cfg_antenna_diversity_rssi_threshold_t cmd;

    cmd.threshold = threshold;

    return WLSendFW_ConfigureCommand(ANT_DIV_SET_RSSI_THRESHOLD, &cmd, sizeof(cmd), NULL, 0);
}

int ctrlCmdFw_GetDefaultAntenna(uint8_t *antenna)
{
    cmd_interrogate_get_default_antenna_t cmdGetDefaultAntenna;
    CommandComplete_t cmdComplete;
    int ret;

    cmdGetDefaultAntenna.cmdInterrogateHeader.id = GET_ANT_DIV_DEFAULT_ANTENNA;

    ret = WLSendFW_InterrogateCommand(GET_ANT_DIV_DEFAULT_ANTENNA, 
                                      &cmdGetDefaultAntenna, 
                                      sizeof(cmdGetDefaultAntenna), 
                                      &cmdComplete,
                                      sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint8_t));
                                      
    *antenna = cmdComplete.info.param[0];
    return ret;
}

int ctrlCmdFw_SelectDefaultAntenna(uint8_t selection)
{
    cmd_cfg_antenna_select_t cmd;

    cmd.selection = selection;

    return WLSendFW_ConfigureCommand(ANT_DIV_SELECT_DEFAULT_ANTENNA, 
                                     &cmd, 
                                     sizeof(cmd_cfg_antenna_select_t),
                                     NULL,
                                     0);
}

int ctrlCmdFw_ResetDecryptedPacketsCounter(uint8_t* roleType)
{
    cmd_cfg_reset_decrypted_packets_counter_cmd_t cmd;

    uint8_t roleId = drv_getRoleIdFromType(gpSupplicantGlobals, *roleType);

    if(roleId == ROLE_ID_NONE)
    {
        Report("\n\rError: Role Does Not Exist!!, Role Type %d\n\r", WLAN_ROLE_STA);
        return -1;
    }

    cmd.roleId = roleId;

    return WLSendFW_ConfigureCommand(RESET_DECRYPT_PACKETS_COUNT, 
                                     &cmd, 
                                     sizeof(cmd_cfg_reset_decrypted_packets_counter_cmd_t),
                                     NULL,
                                     0);
}

int ctrlCmdFw_EnableChannelUtilization()
{
    cmd_cfg_reset_decrypted_packets_counter_cmd_t cmd;
    
    return WLSendFW_ConfigureCommand(ENABLE_CHANNEL_UTILIZATION_NEXT_SCAN, 
                                     &cmd, 
                                     sizeof(cmd_cfg_reset_decrypted_packets_counter_cmd_t),
                                     NULL,
                                     0);
}

int ctrlCmdFw_GetSysInfo(DeviceSystemInfo_t* SysInfo)
{
    // Return value of fuse from gSystemInfo
    cmd_interrogate_get_sysinfo_t cmdGetSysInfo;
    CommandComplete_t cmdComplete;
    int ret;

    cmdGetSysInfo.cmdInterrogateHeader.id = GET_DEVICE_SYSTEM_INFO;
    cmdGetSysInfo.SysInfo.systemInfoIdx = SysInfo->systemInfoIdx;
    ret = WLSendFW_InterrogateCommand(GET_DEVICE_SYSTEM_INFO,
                                      &cmdGetSysInfo,
                                      sizeof(cmdGetSysInfo),
                                      &cmdComplete,
                                      sizeof(uint16_t)/*sizeof(Command_e)*/ + \
                                      sizeof(uint16_t)/*sizeof(CommandStatus_e)*/ + \
                                      sizeof(DeviceSystemInfo_t));
    os_memcpy(SysInfo, cmdComplete.info.param, sizeof(DeviceSystemInfo_t));
    return ret;
}

int ctrlCmdFw_SetRoleMaxTxPower(RoleID_t roleId, int8_t max_tx_power)
{
    int ret = 0;
    cmd_cfg_tx_power_t cmd;

    if (max_tx_power < CASTED_MIN_TX_POWER)
    {
        GTRACE(GRP_REG_DOMAIN, "Configured Tx power %d dBm. "
                               "Increasing to minimum %d dBm",
                               max_tx_power, CASTED_MIN_TX_POWER);
        max_tx_power = CASTED_MIN_TX_POWER;
    }
    else if (max_tx_power > CASTED_MAX_TX_POWER)
    {
        GTRACE(GRP_REG_DOMAIN, "Configured Tx power %d dBm is bigger " 
                               "than upper limit: %d dBm. Attenuating to "
                               "max limit",
                               max_tx_power, CASTED_MAX_TX_POWER);
        max_tx_power = CASTED_MAX_TX_POWER;
    }

    cmd.roleId = roleId;
    cmd.tx_power = max_tx_power;

    ret = WLSendFW_ConfigureCommand(TX_POWER_CFG, &cmd, sizeof(cmd), NULL, 0);

    return ret;
}

int ctrlCmdFw_SetVendorIE(wlanSetVendorInfo_t *vendor_info)
{
    cmd_cfg_vendor_ie_t cmd;

    cmd.role_type = vendor_info->role_type;
    cmd.length = vendor_info->length;
    os_memcpy(cmd.data, vendor_info->data, vendor_info->length);

    return WLSendFW_ConfigureCommand(VENDOR_IE_CFG, &cmd, sizeof(cmd), NULL, 0);
}

int  ctrlCmdFw_SetSleepAuth(WlanPowerManagement_e sleep_auth)
{
    // Send cmd to FW
    enable_sleep_mode_cmd_t cmd;

    cmd.sleep_auth = sleep_auth;

    return WLSendFW_ConfigureCommand(ACX_SLEEP_AUTH, &cmd, sizeof(enable_sleep_mode_cmd_t), NULL, 0);
}

int  ctrlCmdFw_SetLSI(WlanLongSleepInterval lsi_param)
{
    // Send cmd to FW
    cmd_set_lsi_t cmd;

    cmd.LsiParams = lsi_param;

    return WLSendFW_ConfigureCommand(WAKE_UP_CONDITIONS_CFG, &cmd, sizeof(cmd_set_lsi_t), NULL, 0);
}

int ctrlCmdFw_GetMacAddress(Macaddress_t* macaddress)
{
    cmd_interrogate_get_mac_address_t cmdGetMacAddress;
    CommandComplete_t cmdComplete;
    int ret;

    cmdGetMacAddress.cmdInterrogateHeader.id = GET_MAC_ADDRESS;

    ret = WLSendFW_InterrogateCommand(GET_MAC_ADDRESS,
                                      &cmdGetMacAddress,
                                      sizeof(cmdGetMacAddress),
                                      &cmdComplete,
                                      sizeof(uint16_t) + sizeof(uint16_t) + sizeof(Macaddress_t));

    os_memcpy(macaddress, cmdComplete.info.param, sizeof(Macaddress_t));
    return ret;
}

int ctrlCmdFw_GetLinkInactivity(LinkInactivity_t *linkInactivity)
{
    cmd_interrogate_get_LinkInactivity_t cmdGetLinkInactivity;
    CommandComplete_t cmdComplete;
    int ret = 0;

    cmdGetLinkInactivity.cmdInterrogateHeader.id = GET_LINK_INACTIVITY;
    os_memcpy(&cmdGetLinkInactivity.linkInactivity, linkInactivity, sizeof(LinkInactivity_t));

    ret = WLSendFW_InterrogateCommand(GET_LINK_INACTIVITY,
                                      &cmdGetLinkInactivity,
                                      sizeof(cmdGetLinkInactivity),
                                      &cmdComplete,
                                      sizeof(uint16_t)/*sizeof(Command_e)*/ + \
                                      sizeof(uint16_t)/*sizeof(CommandStatus_e)*/ + \
                                      sizeof(LinkInactivity_t));


    os_memcpy(linkInactivity, cmdComplete.info.param, sizeof(LinkInactivity_t));
    return ret;
}

void ctrlCmdFw_LockHostDriver()
{
   // osi_LockObjLock(&driverLock, OSI_WAIT_FOREVER);
}

void ctrlCmdFw_UnlockHostDriver()
{
   // osi_LockObjUnlock(&driverLock);
}
void ctrlCmdFw_CreateMsgQueue()
{
    osi_MsgQCreate(&eventMsgQueue, "eventQueue", sizeof(EventMessage_t), MSG_QUEUE_SIZE);
}

void ctrlCmdFw_DeleteMsgQueue()
{
    osi_MsgQDelete(&eventMsgQueue);
}

void ctrlCmdFw_CreateEventThread()
{
    int ret = 0;

    ret = osi_SyncObjCreate(&gEventThrdRunStopSyncObject);
    if(ret != 0)
    {
        Report("\n\rerror!!! failed to create syn object gEventThrdRunStopSyncObject");
    }
    ret = osi_SyncObjCreate(&gThrdLoopStoppedEventSync);
    if(ret != 0)
    {
        Report("\n\rerror!!! failed to create syn object gThrdLoopStoppedEventSync");
    }
    ret = osi_SyncObjCreate(&gEventThrdDummySleep);
    if(ret != 0)
    {
        Report("\n\rerror!!! failed to create syn object gEventThrdDummySleep");
    }


     osi_ThreadCreate(&eventThread, "eventThread", EVENT_STACK_SIZE, EVENT_TRANSPORT_THREAD_PRIORITY, eventEntryThread, NULL);

}

void ctrlCmdFw_DeleteEventThread()
{
    int ret;
    EventMessage_t event;

    //send message to stop the thread
    event.len = 2;
    event.message = os_malloc(event.len);
    {
        uint8_t* pMsg = event.message;
        *pMsg = 0xFF;
        *(pMsg+1) = 0xFF;
    }
    if(OSI_OK != osi_MsgQWrite(&eventMsgQueue, &event, OSI_WAIT_FOREVER,OSI_FLAG_NOT_FROM_INTR))
    {
        Report("\n\rerror!!! ctrlCmdFw_DeleteEventThread, failed to osi_MsgQWrite");
    }

    //wait for the thread to be stopped
    ret = osi_SyncObjWait(&gEventThrdRunStopSyncObject,OSI_WAIT_FOREVER);
    if(ret != 0)
    {
        Report("\n\rerror!!! failed to wait  syn object gEventThrdRunStopSyncObject");
    }

    os_free(event.message);

    osi_ThreadDelete(&eventThread);


    //this is on purpose after thread delete, in the osi_ThreadDelete it may be used
    ret = osi_SyncObjDelete(&gThrdLoopStoppedEventSync);
    if(ret != 0)
    {
        Report("\n\rerror!!! failed to delete syn object gThrdLoopStoppedEventSync");
    }
    ret = osi_SyncObjDelete(&gEventThrdRunStopSyncObject);
    if(ret != 0)
    {
        Report("\n\rerror!!! failed to delete syn object gEventThrdRunStopSyncObject");
    }

    ret = osi_SyncObjDelete(&gEventThrdDummySleep);
    if(ret != 0)
    {
        Report("\n\rerror!!! failed to delete syn object gEventThrdDummySleep");
    }

}


extern void WlanEventHandler(void *pWlanEvent);
extern void BleTransport_BleEventHandler(void *pBleFwEvent);
void eventEntryThread(void *params)
{
    EventMessage_t *event = NULL;
    EventMBoxId_e eventId = 0;
    int ret;
    uint8_t eventThrdRunning = 1;

    while(gContRunThrdLoopEvent)
    {
        if(eventThrdRunning)
        {
            Report("\n\rEvent_Thread: thrd is running\n\r");
        }
        else
        {
            //wait forever until the thread is deleted
            //or  when thread implementation is disconnect and not delete, this will be signaled
            //Report("\n\r event thread , thread on wait loop to be deleted or disconnected !!!");
            ret = osi_SyncObjWait(&gEventThrdDummySleep,OSI_WAIT_FOREVER);
            if(ret != 0)
            {
                Report("\n\rerror!!! failed to wait   gEventThrdDummySleep");
            }
        }
        event = os_malloc(sizeof(EventMessage_t));
        while(eventThrdRunning)
        {
            if(OSI_OK == osi_MsgQRead(&eventMsgQueue, event, OSI_WAIT_FOREVER))
            {
                if ((event->len == 2) && (IS_WLAN_EVENT_MESSAGE_STOP_RUN(event->message)))
                {
                    Report("\n\r receive event to deinit event thread\r\n");
                    //this message means that the thread is requested to stop run
                    eventThrdRunning = 0;
                }
                else//handle the event
                {
                    //determine the event id in order to call the corresponding handler
                    eventId = (EventMBoxId_e)((EventMailBox_t*)event->message)->eventsVector;
                    if (eventId & BLE_EVENT_ID)
                    {
                        BleTransport_BleEventHandler(event->message);
                    }
                    if (eventId & ~BLE_EVENT_ID)
                    {
                        WlanEventHandler(event->message);
                    }
                    os_free(event->message);
                }
            }
        }
        os_free(event);

        ret = osi_SyncObjSignal(&gEventThrdRunStopSyncObject);
        if(ret != 0)
        {
            Report("\n\rerror!!! failed to signal gEventThrdRunStopSyncObject");
        }

    }//while(gContRunThrdLoopEvent)

    Report("\n\r Event thread , exit from thread loop !!");

    ret = osi_SyncObjSignal(&gThrdLoopStoppedEventSync);
    if(ret != 0)
    {
        Report("\n\rerror!!! failed to signal gThrdLoopStoppedEventSync");
    }


}



