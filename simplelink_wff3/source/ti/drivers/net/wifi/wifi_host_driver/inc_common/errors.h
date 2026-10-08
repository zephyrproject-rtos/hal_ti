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
#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WLAN_RET_CODE_OK                                  (0L)    /* Success */

//----------------------------------------------------------------------
// Error Type:
// Specific error description. Can be updated as needed.
//----------------------------------------------------------------------
typedef enum
{
    WLAN_ERROR_TYPE__WLAN_ALREADY_STARTED = 1,
    WLAN_ERROR_TYPE__LOCK_OBJ_CREATE,
    WLAN_ERROR_TYPE__LOCK_OBJ_DELETE,
    WLAN_ERROR_TYPE__SYNC_OBJ_CREATE,
    WLAN_ERROR_TYPE__SYNC_OBJ_WAIT,
    WLAN_ERROR_TYPE__SYNC_OBJ_DELETE,
    WLAN_ERROR_TYPE__THREAD_CREATE,
    WLAN_ERROR_TYPE__THREAD_DELETE,
    WLAN_ERROR_TYPE__MSG_QUEUE_CREATE,
    WLAN_ERROR_TYPE__MALLOC,
    WLAN_ERROR_TYPE__ENQUEUE,
    WLAN_ERROR_TYPE__REQUEUE,
    WLAN_ERROR_TYPE__QUEUE_FULL,
    WLAN_ERROR_TYPE__DRIVER_DEINIT,
    WLAN_ERROR_TYPE__RAM_LOADER_INIT,
    WLAN_ERROR_TYPE__ROM_LOADER_INIT,
    WLAN_ERROR_TYPE__FOPEN,
    WLAN_ERROR_TYPE__WSOC_FW_INIT,
    WLAN_ERROR_TYPE__INI_PARAMS_INIT,
    WLAN_ERROR_TYPE__RX_SM,
    WLAN_ERROR_TYPE__RX_SM_LENGTH_OF_FRAME_IS_INVALID_FROM_FW,
    WLAN_ERROR_TYPE__TRANSCEIVER_ALREADY_ON,
    WLAN_ERROR_TYPE__TRANSCEIVER_NOT_SET,
    WLAN_ERROR_TYPE__CMD_GENERAL,
    WLAN_ERROR_TYPE__CMD_NOT_SUPPORTED,
    WLAN_ERROR_TYPE__CMD_DEINIT,
    WLAN_ERROR_TYPE__CMD_CB_NOT_INITIALIZED,
    WLAN_ERROR_TYPE__CMD_NOT_INITIALIZED,
    WLAN_ERROR_TYPE__CMD_REACHED_MAX_SIZE,
    WLAN_ERROR_TYPE__TIMEOUT,
    WLAN_ERROR_TYPE__PLT_ALREADY_ON,
    WLAN_ERROR_TYPE__PLT_NOT_STARTED,
    WLAN_ERROR_TYPE__CALIBRATOR_OFF,
    WLAN_ERROR_TYPE__CALIBRATOR_ALREADY_ON,
    WLAN_ERROR_TYPE__TX_ILLEGAL_ID,
    WLAN_ERROR_TYPE__TX_WRITE,
    WLAN_ERROR_TYPE__TIMER_START,
    WLAN_ERROR_TYPE__TIMER_STOP,
    WLAN_ERROR_TYPE__TRANSACTION,
    WLAN_ERROR_TYPE__TRANSACTION_NOT_DONE,
    WLAN_ERROR_TYPE__REACHED_MAX_CLIENTS,
    WLAN_ERROR_TYPE__EXT_APP_NOT_ENABLED,
    WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS,
    WLAN_ERROR_TYPE__ROLE_NOT_SUPPORTED,
    WLAN_ERROR_TYPE__ROLE_IS_NOT_UP,
    WLAN_ERROR_TYPE__ROLE_TRANCIEVER_IS_UP,
    WLAN_ERROR_TYPE__OTHER_ROLE_IS_UP,
    WLAN_ERROR_TYPE__SET_MAC_ROLE_STA,
    WLAN_ERROR_TYPE__SET_MAC_ROLE_AP,
    WLAN_ERROR_TYPE__SET_MAC_ROLE_P2P,
    WLAN_ERROR_TYPE__SET_MAC_ROLE_DEVICE,
    WLAN_ERROR_TYPE__WLAN_SET_ROLE_IS_UP,
    WLAN_ERROR_TYPE__SET_CUSTOM_DOMAIN_BEFORE_SET_ENTRY,
    WLAN_ERROR_TYPE__NULL_BUF,
    WLAN_ERROR_TYPE__INVALID_ROLE,
    WLAN_ERROR_TYPE__INVALID_PARAM_NAME,
    WLAN_ERROR_TYPE__INVALID_PARAM_SEC_TYPE,
    WLAN_ERROR_TYPE__INVALID_PARAM_PASSWRD,
    WLAN_ERROR_TYPE__INVALID_PARAM_GET_TYPE,
    WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE,
    WLAN_ERROR_TYPE__INVALID_PARAM_CALIBRATOR,
    WLAN_ERROR_TYPE__INVALID_PARAM_CHANNEL,
    WLAN_ERROR_TYPE__FW_RESPONSE_RET_CODE_MALLOC,
    WLAN_ERROR_TYPE__FW_RESPONSE_RET_CODE_DEV_NOT_STARTED,
    WLAN_ERROR_TYPE__FW_RESPONSE_RET_CODE_ZALLOC,
    WLAN_ERROR_TYPE__FW_RESPONSE_INVALID_ROLE,
    WLAN_ERROR_TYPE__FW_RESPONSE_INVALID_SECURITY_TYPE,
    WLAN_ERROR_TYPE__FW_RESPONSE_PASSPHRASE_TOO_LONG,
    WLAN_ERROR_TYPE__FW_RESPONSE_PASSWORD,
    WLAN_ERROR_TYPE__FW_RESPONSE_SSID_LEN,
    WLAN_ERROR_TYPE__FW_RESPONSE_NO_ROLE_ACTIVE,
    WLAN_ERROR_TYPE__FW_RESPONSE_ACTIVE_ROLE_SWITCH,
    WLAN_ERROR_TYPE__FW_RESPONSE_SITE_SURVEY_RUNNING,
    WLAN_ERROR_TYPE__FW_RESPONSE_INVALID_MAC_ADDR,
    WLAN_ERROR_TYPE__FW_RESPONSE_NULL_BUF,
    WLAN_ERROR_TYPE__FW_RESPONSE_INVALID_PARAM,
    WLAN_ERROR_TYPE__FW_RESPONSE_EXCEED_MAX_NUM_OF_ENTRIES,
    WLAN_ERROR_TYPE__FW_RESPONSE_GENERAL,
    WLAN_ERROR_TYPE__HOST_RESPONSE_RET_CODE_DEV_NOT_STARTED,
    WLAN_ERROR_TYPE__HOST_RESPONSE_SITE_SURVEY_RUNNING,
    WLAN_ERROR_TYPE__HOST_RESPONSE_NO_ROLE_ACTIVE,
    WLAN_ERROR_TYPE__HOST_RESPONSE_ACTIVE_ROLE_SWITCH,
    WLAN_ERROR_TYPE__HOST_RESPONSE_SSID_LEN,
    WLAN_ERROR_TYPE__HOST_RESPONSE_PASSWORD,
    WLAN_ERROR_TYPE__HOST_RESPONSE_PASSPHRASE_TOO_LONG,
    WLAN_ERROR_TYPE__HOST_RESPONSE_INVALID_SECURITY_TYPE,
    WLAN_ERROR_TYPE__HOST_RESPONSE_INVALID_PARAM,
    WLAN_ERROR_TYPE__HOST_RESPONSE_INVALID_MAC_ADDR,
    WLAN_ERROR_TYPE__HOST_RESPONSE_TIMEOUT_IN_PRGRESS,
    WLAN_ERROR_TYPE__HOST_RESPONSE_STATUS_ERROR,
    WLAN_ERROR_TYPE__CSI,
    WLAN_ERROR_TYPE__CSI_ALREADY_STARTED,
    WLAN_ERROR_TYPE__HOST_RESPONSE_GET_PROFILE_INVALID_INDEX,
    WLAN_ERROR_TYPE__HOST_ADD_REMOVE_PROFILE_FAILED_WPS_IN_PROGRESS,


    WLAN_ERROR_TYPE__MAX       = 0xFF

} wlanErrorType_e;


//----------------------------------------------------------------------
// Error Module:
// Module in which the error is caused
//----------------------------------------------------------------------
typedef enum
{
    WLAN_ERROR_MODULE__DEVICE      = 0x00,
    WLAN_ERROR_MODULE__COMMANDS    = 0x01,
    WLAN_ERROR_MODULE__FW_EVENTS   = 0x02,
    WLAN_ERROR_MODULE__FW_RESPONSE = 0x03,
    WLAN_ERROR_MODULE__TX          = 0x04,
    WLAN_ERROR_MODULE__RX          = 0x05,
    WLAN_ERROR_MODULE__TRANSPORT   = 0x06,
    WLAN_ERROR_MODULE__BUS         = 0x07,
    WLAN_ERROR_MODULE__CMD_CTRL    = 0x08,
    WLAN_ERROR_MODULE__EVENTS      = 0x09,
    WLAN_ERROR_MODULE__TIMER       = 0x0A,
    WLAN_ERROR_MODULE__CME         = 0x0B,
    WLAN_ERROR_MODULE__L2_CFG      = 0x0C,

    WLAN_ERROR_MODULE__MAX       = 0x0F

} wlanErrorModule_e;


//----------------------------------------------------------------------
// Error Severity:
// LOW  - Errors that may be recovered easily
// MID  - Errors that may be recovered by WiFi host driver reset
// HIGH - Non-recoverable errors, device reset recommended
//----------------------------------------------------------------------
typedef enum
{
    WLAN_ERROR_SEVERITY__LOW  = 0x00,
    WLAN_ERROR_SEVERITY__MID  = 0x01,
    WLAN_ERROR_SEVERITY__HIGH = 0x02,

    WLAN_ERROR_SEVERITY__MAX  = 0x03

} wlanErrorSeverity_e;

//----------------------------------------------------------------------
// Error structure:
//
//       +---------------------------------------------------------+
//       |   |                |            |           |           |
//       | 1 |    RESERVED    |  SEVERITY  |  MODULE   |   TYPE    |
//       |   |                |            |           |           |
//       +---+----------------+------------+-----------+-----------¦
// Bits:   1         15              2           4          10
//
// For more information: https://confluence.itg.ti.com/x/OeKQQQ
//----------------------------------------------------------------------
typedef union wlanError_u
{
    struct __attribute__((packed))
    {
        uint32_t type     : 10 ; // bits: [  9 :  0 ]
        uint32_t module   : 4 ;  // bits: [ 13 : 10 ]
        uint32_t severity : 2 ;  // bits: [ 15 : 14 ]
        uint32_t reserved : 15 ; // bits: [ 30 : 16 ]
        uint32_t sign     : 1 ;  // bits: [ 31 : 31 ]
    };

    int32_t word;

} wlanError_u;


#define WLAN_ERROR(severity,module,type)( (1<<31) | (0<<16) | (severity << 14) | (module << 10) | (type) )

//this is required for the application
#define WLAN_RET_OPER_IN_PROGRESS (WLAN_ERROR(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS))
#define WLAN_RET_TIMEOUT  (WLAN_ERROR(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__TIMEOUT))
#define WLAN_RET_COMMAND_GENERAL   (WLAN_ERROR(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__CMD_GENERAL))
#define WLAN_RET_COMMAND_CMD_NOT_INITIALIZED   (WLAN_ERROR(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__CMD_NOT_INITIALIZED))
#define WLAN_RET_COMMAND_ERROR_TYPE__MALLOC    (WLAN_ERROR(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__MALLOC))
#define WLAN_RET_COMMAND_ERROR_MID_TYPE__SYNC_OBJ_CREATE    (WLAN_ERROR(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__SYNC_OBJ_CREATE))
#define WLAN_RET_COMMAND_ERROR_MID_TYPE__MSG_QUEUE_CREATE (WLAN_ERROR(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__TRANSPORT, WLAN_ERROR_TYPE__MSG_QUEUE_CREATE))
#define WLAN_RET_COMMAND_ERROR_MID_TYPE__TIMER_STOP (WLAN_ERROR(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__TIMER_STOP))
#define WLAN_RET_COMMAND_ERROR_MID_TYPE__CMD_GENERAL (WLAN_ERROR(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__CMD_GENERAL))


int32_t  WlanError(wlanErrorSeverity_e severity, wlanErrorModule_e module, wlanErrorType_e type);
uint32_t WlanError_GetType(int32_t error);
uint32_t WlanError_GetModule(int32_t error);
uint32_t WlanError_GetSeverity(int32_t error);
wlanErrorType_e WlanError_ConvertWsocError(int error);


#ifdef  __cplusplus
}
#endif /*  __cplusplus */

#endif  /*  __ERROR_H__ */
