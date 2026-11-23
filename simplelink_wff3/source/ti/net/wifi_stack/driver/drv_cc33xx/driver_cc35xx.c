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
/* Standard includes */
#include <stdint.h>

#include "osi_type.h"
#include "cme/cme_scan_api.h"
#include "cme/cme_fw_api.h"
#include "drv_ti_internal.h"
#include "../../wpa_supplicant/wpa_supplicant_i.h"
#include "nab.h"
#include "commands.h"
#include "wlan_links.h"
#include "80211_utils.h"
#include "cme_supplicant_api.h"
#include "cme_internal_api.h"
#include "cme_dispatcher_api.h"
#include "driver_osprey_mx_scan.h"
#include "macro_utils.h"
#include "udata_api.h"
#include "ti_qos_types.h"
#include "tx_hw_queue_api.h"
#include "cme_defs.h"
#include "udata_api.h"
#include "l2_cfg.h"
#include "cme_defs.h"
#include "cc3xxx_public_types.h"
#include "../../hostap/src/ap/sta_info.h"
#include "drv_ext_app.h"
#include "cc3xxx_public_types.h"
#include "regulatory_domain_api.h"
#include "csi.h"
#include "control_cmd_fw.h"
#include "ble_if.h"
#include "errors.h"

extern int wlanDispatcherSendEvent(uint16_t opcode, uint8_t *args, uint16_t argsLen);


// ============================================================================
//      Modules private definitions
// ============================================================================
//TODO: rename the  file  the cc35xx shouldn't appear on file name
//TODO: rename all the function the cc33xx need to be removed
typedef struct {
    NAB_header_t    nabHeader;
    CommandParam_t  commandParam ;
}CommandParamContol_t;
// ============================================================================
//      Modules globals
// ============================================================================

extern  cmeScanSharedInfo_t*    scanResultTable_GetCmeScanDbPointer();
extern  Bool_e                  scanResultTable_NotifyScanPriodStart(uint8  scanTag);
extern  OsiSyncObj_t            ScanResultTableSyncObj_ull;

extern  WlanScanDwellTime_t scanDwellTimeParams;
extern ti_driver_ifData_t * getDriverForRoleId(uint32_t aRoleId, struct wpa_global *apGlobal);
#ifndef TI_STA_ONLY_BUILD
extern int cc3xxx_trnspt_cmd_if_sta_remove(void *apPriv, const u8 *apAddr);
#endif
extern int WLSendFW_DebugCommand(uint32_t id, void *cmd, uint32_t len, void *out, uint32_t outLen);
// ============================================================================
//		 Functions declarations which are not interface
// ============================================================================


int cc3xxx_trnspt_cmd_if_send_stop_scan (uint8_t roleID,
                                  EScanRequestType scanRequestType,
                                  Bool_e isET);
static int8_t trnspt_cmd_send_ies(uint32_t roleID,
                        EScanRequestType scanType,
                        struct wpa_driver_scan_params *apSuppParams,
                        RoleType_e roleType);
void trnspt_cmd_get_mac_addr(uint8 *macAddr, RoleType_e aRoleType);
static int  trnspt_cmd_cfg_erp_protection (RoleID_t roleID, Bool_e erpProtectionEnabled);
static int  trnspt_cmd_cfg_preamble (RoleID_t roleID, Bool_e shortBPreambleSupported);
static int  trnspt_cmd_cfg_slot_time (RoleID_t roleID, SlotTime_e slotTime);

// ============================================================================
//      Supplicant Functions declarations
// ============================================================================
/* Roles command */
int cc3xxx_trnspt_cmd_if_enable_role   (void *apDrv, Role_e aRoleType);
int cc3xxx_trnspt_cmd_if_disable_role  (void *apDrv);
int cc3xxx_trnspt_cmd_if_stop_role     (void *apDrv);
int cc3xxx_trnspt_cmd_if_start_role    (void *apDrv, void * apParams, RoleCommonParam_t *apRates, SlotTime_e aSlotTime);
int cc3xxx_trnspt_cmd_if_set_peer_state (uint8_t lid, uint8_t /*LinkState_e*/ linkConnectionState, Bool_e WMM);
int cc3xxx_trnspt_cmd_if_change_role_type (void *apDrv, Role_e aRoleType);

/* Scan Functions */
int cc3xxx_trnspt_cmd_if_one_shot_scan(void *apPriv, struct wpa_driver_scan_params *apParams);
int cc3xxx_trnspt_cmd_if_sched_scan(void *apPriv, struct wpa_driver_scan_params *apParams);
int cc3xxx_trnspt_cmd_if_site_survey(uint8_t roleID, CMEWlanScanCommon_t* pScanCommon) ;//wlan_scan command
int8_t cc3xxx_trnspt_cmd_if_stop_sched_scan(void *apPriv);
#ifndef TI_STA_ONLY_BUILD
int cc3xxx_trnspt_cmd_if_sta_remove(void *apPriv, const uint8_t *apAddr);
#endif


// ============================================================================
//      Local services APIs
// ============================================================================

// ============================================================================
//      Events
// ============================================================================
void cc3xxx_trnspt_cmd_if_event_handle(EventMailBox_t *pWlanFwEvent)
{
   //

    EventMBoxId_e eventId = (EventMBoxId_e)(uint32_t)pWlanFwEvent->eventsVector;


    if(eventId & SCAN_COMPLETE_EVENT_ID)
    {
        CME_CC3XX_EVENT_PRINT("\n\rFW event received , SCAN_COMPLETE_EVENT_ID,NumberOfScanResults:%d\n\r", pWlanFwEvent->NumberOfScanResults);
        GTRACE(GRP_DRIVER_CC33, "SCAN_COMPLETE_EVENT_ID event number of scan results %d", pWlanFwEvent->NumberOfScanResults);
        /* Get profiles/ad-hoc connection list */
        cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();
        CmeScan_ScanDone(SCAN_REQUEST_ONE_SHOT, pCmeScanDB->roleId, pCmeScanDB, CME_SCAN_STATUS_COMPLETE, 0, 0);
    }

    if(eventId & PERIODIC_SCAN_REPORT_EVENT_ID)
    {
        CME_CC3XX_EVENT_PRINT("\n\rFW event received , PERIODIC_SCAN_REPORT_EVENT_ID NumberOfPeriodicScanResults:%d\n\r",pWlanFwEvent->NumberOfPeriodicScanResults);

        /* Get profiles/ad-hoc connection list */
        cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();
        CmeScan_ScanPeriodDone(pCmeScanDB->roleId, pCmeScanDB, CME_SCAN_STATUS_COMPLETE);
    }

    if(eventId & PERIODIC_SCAN_COMPLETE_EVENT_ID)
    {
        CME_CC3XX_PORT_PRINT("\n\rFW event received , PERIODIC_SCAN_COMPLETE_EVENT_ID\n\r");
        /* Get profiles/ad-hoc connection list */
        cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();
        CmeScan_ScanDone(SCAN_REQUEST_CONNECT_PERIODIC_SCAN, pCmeScanDB->roleId, pCmeScanDB, CME_SCAN_STATUS_COMPLETE, 0, 0);
    }

    if(eventId & BSS_LOSS_EVENT_ID)
    {
        CME_CC3XX_PORT_PRINT("\n\r FW event received , BSS_LOSS_EVENT_ID BssLossRoleIdBitMap 0x%x \n\r",pWlanFwEvent->BssLossRoleIdBitMap);
        if(pWlanFwEvent->BssLossRoleIdBitMap & 0x1) //role_sta
        {
            CME_BssLoss(0);
        }
        if(pWlanFwEvent->BssLossRoleIdBitMap & 0x2) //role_ap
        {
            CME_BssLoss(1);
        }
    }
    
    if(eventId & CHANNEL_SWITCH_COMPLETE_EVENT_ID)
    {
        CME_CC3XX_EVENT_PRINT("\n\rFW event received , CHANNEL_SWITCH_COMPLETE_EVENT_ID\n\r");
        pWlanFwEvent->ChannelSwitchRoleIdBitMap |= BIT_x(0); //role_sta
        //WlanFwEvent->ChannelSwitchRoleIdBitMap |= BIT_x(data->roleID); // should be if MR-STA is supported 
        CME_ChannelSwitchDone(0);
        //CME_ChannelSwitchDone(data->roleID); // should be if MR-STA is supported 
    }

    if(eventId & CSI_EVENT_ID)
    {
        WlanGetCSIData_t csiData = {0};
    
        //need to copy the data from FW csiData into WlanGetCSIData_t by each parameter
        CME_CC3XX_EVENT_PRINT("\n\rCSI_EVENT_ID:  ts=0x%x pktLen=%d csiInfoLen=%d rssi=%d rate=%d sig=%d mcs=%d sgi=%d ch=%u ant=%u cw=%u \n\r",
             pWlanFwEvent->csiData.timestamp, pWlanFwEvent->csiData.packetLength, pWlanFwEvent->csiData.csiInfoLength,
             pWlanFwEvent->csiData.rssi, pWlanFwEvent->csiData.rate, pWlanFwEvent->csiData.sig_mode, pWlanFwEvent->csiData.mcs,
             pWlanFwEvent->csiData.sgi, pWlanFwEvent->csiData.channel, pWlanFwEvent->csiData.ant, pWlanFwEvent->csiData.cw);

        CME_CC3XX_EVENT_PRINT("\n\r rMac=%02x:%02x:%02x:%02x:%02x:%02x tMac=%02x:%02x:%02x:%02x:%02x:%02x\n\r",
             pWlanFwEvent->csiData.rMacAddr[0], pWlanFwEvent->csiData.rMacAddr[1], pWlanFwEvent->csiData.rMacAddr[2],
             pWlanFwEvent->csiData.rMacAddr[3], pWlanFwEvent->csiData.rMacAddr[4], pWlanFwEvent->csiData.rMacAddr[5],
             pWlanFwEvent->csiData.tMacAddr[0], pWlanFwEvent->csiData.tMacAddr[1], pWlanFwEvent->csiData.tMacAddr[2],
             pWlanFwEvent->csiData.tMacAddr[3], pWlanFwEvent->csiData.tMacAddr[4], pWlanFwEvent->csiData.tMacAddr[5]);

        /* Copy fields that match */
        csiData.timestamp = pWlanFwEvent->csiData.timestamp;
        csiData.packetLength = pWlanFwEvent->csiData.packetLength;
        csiData.csiInfoLength = pWlanFwEvent->csiData.csiInfoLength;
        os_memcpy(csiData.csiDataBuf, pWlanFwEvent->csiData.csiDataBuf, sizeof(uint32_t) * CSI_FW_MAX_DATA_LENGTH);
        os_memcpy(csiData.tMacAddr, pWlanFwEvent->csiData.tMacAddr, MAC_ADDR_LEN);
        os_memcpy(csiData.rMacAddr, pWlanFwEvent->csiData.rMacAddr, MAC_ADDR_LEN);
        csiData.rssi = pWlanFwEvent->csiData.rssi;
        csiData.rate = pWlanFwEvent->csiData.rate;
        csiData.sig_mode = pWlanFwEvent->csiData.sig_mode;
        csiData.mcs = pWlanFwEvent->csiData.mcs;
        csiData.sgi = pWlanFwEvent->csiData.sgi;
        csiData.channel = pWlanFwEvent->csiData.channel;

        /* Copy fields that don't match */
        csiData.ant = 0;
        csiData.cw = 0;
        csiData.seqNum =  ((uint16_t)pWlanFwEvent->csiData.cw << 8) |
                           (uint16_t)pWlanFwEvent->csiData.ant;
        
        CSI_PushMessage(&csiData);
    }

    if(eventId & RESEED_EVENT_ID)
    {
        CME_CC3XX_EVENT_PRINT("\n\rFW event received , RESEED_EVENT_ID with size %d\n\r",pWlanFwEvent->reseedRequestSize);
#ifdef CC35XX

        BleIf_SetSeed(MAX_SEED_SIZE);
#endif
    }

    if(eventId & FW_CRASH_EVENT_ID)
    {
        CME_PRINT_REPORT("\n\r [cmd_if_event_handle] FW event received , FW_CRASH_EVENT_ID");

        wlanDispatcherSendEvent(WLAN_EVENT_FW_CRASH, NULL, 0);
    }
    if(eventId & ERROR_EVENT_ID)
    {
        CME_PRINT_REPORT("\n\r [cmd_if_event_handle ] FW event received , ERROR_EVENT_ID");
        wlanDispatcherSendEvent(WLAN_EVENT_ERROR, NULL, 0);
    }
}
/******************************************************************************

    FUNCTION:		trnspt_cmd_get_mac_addr

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Set the MAC address to the role type
                    First get the MAC address from FLASH if saved
                    (override), if not saved hard-coded MAC address set

    CALLER:         cc3xxx_trnspt_cmd_if_if_init

    PARAMETERS:     macAddr - pointer MAC address
                    aRoleType - type of role that should be enabled

    RETURNS:        NONE
******************************************************************************/
extern TMacAddr     g_fuse_mac_addr[];


void trnspt_cmd_get_mac_addr(uint8_t *macAddr, RoleType_e aRoleType)
{
    //override the mac address
    if (ROLE_IS_TYPE_STA(aRoleType))
    {
        IRQ_UtilCopyMacAddress((uint8_t *)&g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_STA], macAddr);
    }
    else if (ROLE_IS_TYPE_AP(aRoleType))
    {
       IRQ_UtilCopyMacAddress((uint8_t *)&g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_AP], macAddr);
    }
    else if (ROLE_IS_TYPE_P2P(aRoleType))//P2P GO or P2P CL
    {
        IRQ_UtilCopyMacAddress((uint8_t *)&g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_AP], macAddr);
    }
    else if (ROLE_IS_TYPE_DEVICE(aRoleType))//Device -- off-channel device interface
    {
        IRQ_UtilCopyMacAddress((uint8_t *)&g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_DEVICE], macAddr);
    }


    // Check if MAC address is not zero. Otherwise allocate.
    if (IRQ_UtilIsZeroMacAddress(macAddr))
    {
        // Allocate Mac address
       ASSERT_GENERAL(0);// ASSERT_GENERAL(0);//  changed to ASSERT_GENERAL(0)
       /*CME_CC3XX_PORT_PRINT("\n\rDEVICE_PARAMS: MAC address is Zero, take the hard-coded MAC address 0x%x 0x%x 0x%x",
               macAddr[0],
               macAddr[1],
               macAddr[2]);*/
    }
    else
    {
        /*CME_CC3XX_PORT_PRINT( "\n\rDEVICE_PARAMS: MAC address is not Zero, take the flash 0x%x 0x%x 0x%x",
               macAddr[0],
               macAddr[1],
               macAddr[2]);*/
    }

}
// ============================================================================
//      Set APIs
// ============================================================================
/******************************************************************************

    FUNCTION:       cc3xxx_trnspt_cmd_if_set_key

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    This command set connection keys

    CALLER:         setKey()
                    setDefaultKeyId()

    PARAMETERS:     pParam - pointer to set key structure param

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_set_key (SetKey_t *pParam) //called from ti_driver_set_key->rsn_addKey->rsn_setKey
{
    CommandParamContol_t cmd;
    CommandComplete_t    cmdComplete;
    int32_t              retVal = 0;
    int8_t               rc;

    GTRACE(GRP_DRIVER_MX,"Setting security keys: link ID %d, type ENUM(LidKeyType_e, %d), cipher suite ENUM(CipherSuite_e,%d), key ID %d, action ENUM(KeyAction_e,%d)",
                          pParam->lid,
                          pParam->lidKeyType,
                          pParam->cipher_type,
                          pParam->keyId,
                          pParam->action);

    if(pParam->action == KEY_REMOVE)
    {
        CME_CC3XX_PORT_PRINT("\n\rCMD KEY_REMOVE  security keys: link ID %d, type ENUM(LidKeyType_e, %d), cipher suite ENUM(CipherSuite_e,%d), key ID %d\n",
                         pParam->lid,
                         pParam->lidKeyType,
                         pParam->cipher_type,
                         pParam->keyId);
    }
    else
    {
        CME_CC3XX_PORT_PRINT("\n\rCMD_SET_KEYS Setting security keys: link ID %d, type ENUM(LidKeyType_e, %d), cipher suite ENUM(CipherSuite_e,%d), key ID %d, action ENUM(KeyAction_e,%d)\n",
                             pParam->lid,
                             pParam->lidKeyType,
                             pParam->cipher_type,
                             pParam->keyId,
                             pParam->action);
    }
    // --------------------------
    //  Prepare CMD
    // --------------------------

    cmd.nabHeader.opcode = CMD_SET_KEYS;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID =CMD_SET_KEYS;
    //cmd.status = 0;

    memcpy(&cmd.commandParam.param, pParam, sizeof(SetKey_t));
    cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + (sizeof(SetKey_t)));

    // --------------------------
    //  Send CMD
    // --------------------------
    retVal  = cmd_Send((char *)&cmd, cmd.nabHeader.len, (char *)&(cmdComplete.info.param), 0);
    cmdComplete.info.status = retVal;
    //    need to return this val cmdComplete.info.status
    if(retVal == 0) //&& cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
        rc = cmdComplete.info.status;   //rc = 0;
    }
    else
    {
        CME_CC3XX_PORT_PRINT("\n\rCMD_SET_KEYS Failed !!!");
        rc =  CMD_GENERAL_STATUS_ERROR;
        //GTRACE(GRP_DRIVER_MX, "Not enable to set keys, status = ENUM(CommandStatus_e,%d)", cmdComplete.info.status);
        //rc = -1;
    }
    return rc;
}
/******************************************************************************

    FUNCTION:       cc3xxx_trnspt_cmd_if_set_peer_state

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    This command set link connection state

    CALLER:         caller

    PARAMETERS:     lid                 - link ID
                    linkConnectionState - requested link connection state

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_set_peer_state (uint8_t lid,
                                         uint8_t /*LinkState_e*/ linkConnectionState,
                                         Bool_e WMM)
{
    CommandParamContol_t cmd;
    CommandComplete_t       cmdComplete;
    int                  retVal = 0;
    int8_t                    rc;

    SetLinkConnectionState_t *cmdParams = (SetLinkConnectionState_t*)&cmd.commandParam.param;

    GTRACE(GRP_DRIVER_MX, "set link connection state ENUM(LinkState_e,%d)", linkConnectionState);
    CME_CC3XX_PORT_PRINT("\n\r\n\r CMD_SET_LINK: lid:%d_CONNECTION_STATE ENUM(LinkState_e,%d)", lid,linkConnectionState);
    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.nabHeader.opcode = CMD_SET_LINK_CONNECTION_STATE;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID                   = CMD_SET_LINK_CONNECTION_STATE;
    cmdParams->connectionState  = linkConnectionState;
    cmdParams->flid             = lid;

    cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(SetLinkConnectionState_t));

    // --------------------------
    //  Send CMD
    // --------------------------
   // retVal = g_stub_func.CommandDispatch(&cmd, &cmdComplete);//  gstube replace
    retVal = cmd_Send((char *)&cmd, cmd.nabHeader.len, (char *)&(cmdComplete.info.param), 0);
    cmdComplete.info.status = retVal;
    //    need to return this val cmdComplete.info.status
    if(retVal >= 0) //&& cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
        rc = cmdComplete.info.status;   //rc = 0;

    }
    else
    {   rc =  CMD_GENERAL_STATUS_ERROR;
        //GTRACE(GRP_DRIVER_MX, "Not enable to set link connection, status = ENUM(CommandStatus_e,%d)", cmdComplete.info.status);
        //rc = -1;
    }

    return rc;
}

#ifndef TI_STA_ONLY_BUILD
/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_set_beacon_info

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Set beacon information for AP role

    CALLER:         cc3xxx_trnspt_cmd_if_set_ap

    PARAMETERS:     aRoleId      - role ID
                    beacon       - pointer for beacon template

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_set_beacon_info(uint32_t aRoleId,
                                   struct wpa_driver_ap_params *beacon)
{
    CommandParamContol_t cmd;
    CommandComplete_t       cmdComplete;
    int                  retVal = 0;
    int8_t                    rc     = 0;

    SetBeaconInfo_t  *cmdParams = (SetBeaconInfo_t*)&cmd.commandParam.param;

    GTRACE(GRP_DRIVER_MX, "Set beacon template roleID %d", aRoleId);
    CME_CC3XX_PORT_PRINT("\n\r CMD_AP_SET_BEACON_INFO Set beacon template roleID %d", aRoleId);
    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.nabHeader.opcode = CMD_AP_SET_BEACON_INFO;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID           = CMD_AP_SET_BEACON_INFO;
    cmdParams->roleID   = aRoleId;

#ifdef CONFIG_AP
    cmdParams->beacon_len = fillBeaconTemplate(beacon, cmdParams->beacon);
#endif 
 cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(SetBeaconInfo_t));
    // --------------------------
    //  Send CMD
    // --------------------------
    //retVal = g_stub_func.CommandDispatch(&cmd, &cmdComplete);//  gstube replace
    retVal = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), 0);
    cmdComplete.info.status = retVal;
    if(retVal >= 0)// && cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
        rc = cmdComplete.info.status;   //rc = 0;

    }
    else
    {
        rc =  CMD_GENERAL_STATUS_ERROR;
        GTRACE(GRP_DRIVER_MX, "Not enable to set beacon template, status = ENUM(CommandStatus_e,%d)", cmdComplete.info.status);
        CME_CC3XX_PORT_PRINT_ERROR("\r\n ERROR! Not enable to set beacon template, status = ENUM(CommandStatus_e,%d)", cmdComplete.info.status);
       //rc = -1;
    }

    return rc;
}
#endif // TI_STA_ONLY_BUILD

// ============================================================================
//      Roles APIs
// ============================================================================

/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_enable_role

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Send enable role command to FW, wait for FW to
                    allocate a role and set role ID on driver DB.
                    This role ID shall be used for any further access to
                    this role.

    CALLER:         cc3xxx_trnspt_cmd_if_if_init

    PARAMETERS:     apPriv - IN/OUT pointer to the driver DB
                    aRoleType - type of role that should be enabled

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_enable_role (void *apDrv, Role_e aRoleType)
{
    ti_driver_ifData_t      *pDrv = (ti_driver_ifData_t *)apDrv;
    CommandParamContol_t     cmd;
    CommandComplete_t        cmdComplete;
    int                      retVal = 0;
    int8_t                   rc     = 0;

    RoleEnableParameters_t   *cmdParams = (RoleEnableParameters_t*)&cmd.commandParam.param;
    RoleEnableReturn_t       *cmdReturn = (RoleEnableReturn_t*)&cmdComplete.info.param;

    GTRACE(GRP_WPA_SUPPLICANT, "CMD_ROLE_ENABLE ENUM(RoleType_e, %d) ", aRoleType);
    CME_CC3XX_PORT_PRINT("\n\r CMD_ROLE_ENABLE, Enable role ENUM(RoleType_e, %d) ", aRoleType);

    // Init Deny List
    DenyList_initList(&(pDrv->denyList));

    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.nabHeader.opcode = CMD_ROLE_ENABLE;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID       = CMD_ROLE_ENABLE;
    cmdParams->roleType = (uint8_t)aRoleType;
    cmdParams->staRoleIdx = 0; //TODO Add as parameter in application
    trnspt_cmd_get_mac_addr((uint8_t *)cmdParams->macAddress, aRoleType);
    cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(RoleEnableParameters_t));

    // --------------------------
    //  Send CMD
    // --------------------------
    retVal = cmd_Send((char *)&cmd, cmd.nabHeader.len, (char *)&(cmdComplete.info.param), sizeof(RoleEnableReturn_t) );
    cmdComplete.info.status = retVal;
    if(retVal == CMD_OK)// && cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
        rc = cmdComplete.info.status;
        // Mark role wasn't started yet
        pDrv->roleStarted = FALSE;
        pDrv->roleEnabled = TRUE;

        // Set received parameters on role DB
        GTRACE(GRP_WPA_SUPPLICANT, "Enabled role ,allocated roleId: %d", cmdReturn->roleID);
        CME_CC3XX_PORT_PRINT("\n\rEnabled role ,allocated roleId: %d", cmdReturn->roleID);

        pDrv->roleId = cmdReturn->roleID;
        // copy the MAC address to the driver param
        IRQ_UtilCopyMacAddress(cmdParams->macAddress, pDrv->macAddr);
        udata_SetRoleMac( pDrv->roleId, cmdParams->macAddress);
    }
    else
    {
       GTRACE(GRP_WPA_SUPPLICANT, "Failed to allocated role ID ret = %d status = ENUM(CommandStatus_e, %d)",
               retVal,
               cmdComplete.info.status);
       CME_CC3XX_PORT_PRINT_ERROR("\n\rFailed to allocated role ID ret = %d status = ENUM(CommandStatus_e, %d)",
               retVal,
               cmdComplete.info.status);

        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
    }

    return rc;
}
/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_disable_role

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Send disable role command to FW, wait for FW to
                    complete the operation.

    CALLER:         cc3xxx_trnspt_cmd_if_deinit

    PARAMETERS:     apDrv - IN/OUT pointer to the driver DB

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_disable_role (void *apDrv)
{
   //

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apDrv;
    //CommandParamContol_t          cmd;
    CommandParamContol_t cmd;
    CommandComplete_t       cmdComplete;
    int                  retVal;
    int8_t                    rc;
    RoleDisableParameters_t *cmdParams = (RoleDisableParameters_t*)&cmd.commandParam.param;

    // Clear Deny List
    DenyList_clearList(&(pDrv->denyList));

    GTRACE(GRP_WPA_SUPPLICANT, "CMD_ROLE_DISABLE roleid=%d", pDrv->roleId);
    CME_CC3XX_PORT_PRINT("\n\r CMD_ROLE_DISABLE roleid=%d \r\n", pDrv->roleId);
    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.nabHeader.opcode = CMD_ROLE_DISABLE;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID           = CMD_ROLE_DISABLE;
    cmdParams->roleID   = pDrv->roleId;
    cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(RoleDisableParameters_t));

    // --------------------------
    //  Send CMD
    // --------------------------
   // retVal = g_stub_func.CommandDispatch(&cmd, &cmdComplete);//  gstube replace
    retVal = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), 0 );
    cmdComplete.info.status = retVal;
    //in case of FW crash , the code will disable the role
    if(retVal >= 0 || (retVal == WLAN_RET_TIMEOUT))//&& cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
         pDrv->roleEnabled = FALSE;
         rc = cmdComplete.info.status;//rc = 0;
    }
    else
    {
        GTRACE(GRP_DRIVER_MX, "Not enable to disable role id %d status = ENUM(CommandStatus_e,%d)",
                pDrv->roleId,
                cmdComplete.info.status);
        CME_CC3XX_PORT_PRINT_ERROR("\n\r CMD_ROLE_DISABLE failed , roleId:%d status:%d\n\r", pDrv->roleId, retVal);
         rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
    }

   //

    return rc;
}

/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_stop_role

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    This command stops a (previously started) role,
                    so the F/W can on longer select to activate it.

    CALLER:         caller

    PARAMETERS:     apDrv - IN/OUT pointer to the driver DB

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_stop_role (void *apDrv)
{
   //

    ti_driver_ifData_t      *pDrv = (ti_driver_ifData_t *)apDrv;
    //CommandParamContol_t          cmd;
    CommandParamContol_t cmd;
    CommandComplete_t       cmdComplete;
    int                retVal;
    int                  rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;

    if(pDrv->roleStarted == FALSE)
    {
        //GTRACE(GRP_DRIVER_MX, "Role %d already stopped!", pDrv->roleId);
        goto out;
    }
    CME_CC3XX_PORT_PRINT("\n\r Send command CMD_ROLE_STOP %d",pDrv->roleId);

    RoleStopParameters_t *cmdParams = (RoleStopParameters_t*)&cmd.commandParam.param;

    GTRACE(GRP_DRIVER_MX, "CMD_ROLE_STOP role id %d", pDrv->roleId);

    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.nabHeader.opcode = CMD_ROLE_STOP;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID           = CMD_ROLE_STOP;
    cmdParams->roleID   = pDrv->roleId;
    cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(RoleStopParameters_t));
    // --------------------------
    //  Send CMD
    // --------------------------
    retVal = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), 0 );

    cmdComplete.info.status = retVal;

    //in case fW crashed  make graceful stop
    if((retVal >= 0) || (retVal == WLAN_RET_TIMEOUT))
    {
        rc = cmdComplete.info.status;//rc = 0;
        // Mark role was stopped (should be used to avoid restarting an active role)
        pDrv->roleStarted = FALSE;
        pDrv->freq = 0;
        if(ROLE_IS_TYPE_STA_BASED(pDrv->roleType))
        {
            // Remove link 
            uint32_t    uHlid;
            EWlanLinkState eState;
            for (uHlid=0; uHlid<WLANLINKS_MAX_LINKS; uHlid++)
            {
                wlanLinks_GetLinkState(&eState, uHlid);
                if((TIWDRV_NETIF_ID_STA == wlanLinks_GetNetIfId(uHlid)) && (WLANLINK_STATE_FREE != eState))
                {
                    if (wlanLinks_RemoveLink(uHlid) != OK)
                    {
                        //GTRACE(GRP_DRIVER_MX,"cc3xxx_trnspt_cmd_if_stop_role(): Failed to free link, HLID=%u", uHlid);
                        ASSERT_GENERAL(0);// ASSERT_GENERAL(0);//  changed to ASSERT_GENERAL(0)
                        return -NOK;
                    }
                    /* Reset Rx & Tx Link counters*/
                    udata_ResetLinkStats(uHlid);
                    CME_CC3XX_PORT_PRINT("\n\r UDATA remove STA link uHlid:%d",uHlid);
                    udata_RemoveLink(uHlid);
                    break; // only one link to STATION ROLE
                }

            }
        }
        else if(ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
        {
            // Remove link
            uint32_t    uHlid;
            linkType_e eLinkType;
            EWlanLinkState eState;

            for (uHlid=0; uHlid<WLANLINKS_MAX_LINKS; uHlid++)
            {
                wlanLinks_GetLinkState(&eState, uHlid);
                if((TIWDRV_NETIF_ID_SAP == wlanLinks_GetNetIfId(uHlid)) && WLANLINK_STATE_FREE != eState)
                {
                    if (wlanLinks_GetLinkType(&eLinkType, uHlid) != OK)
                    {
                        ASSERT_GENERAL(0);
                        return -NOK;
                    }

                    if ((eLinkType != WLANLINK_TYPE_SPECIFIC))
                    {
                        udata_ResetLinkStats(uHlid);
                        if (wlanLinks_RemoveLink(uHlid) != OK)
                        {
                            //GTRACE(GRP_DRIVER_MX,"cc3xxx_trnspt_cmd_if_stop_role(): Failed to free link, HLID=%u", uHlid);
                            ASSERT_GENERAL(0);// ASSERT_GENERAL(0);//  changed to ASSERT_GENERAL(0)
                            return -NOK;
                        }
                    }
                    else
                    {
                        TInternalWlanLinkInfo* linkInfo;
                        wlanLinks_GetLink(uHlid, &linkInfo);

#ifndef TI_STA_ONLY_BUILD
                        if (cc3xxx_trnspt_cmd_if_sta_remove(apDrv, linkInfo->info.tMacAddr) != OK)
                        {
                           ASSERT_GENERAL(0);
                           CME_CC3XX_PORT_PRINT("\n\r RemoveBssLinks(): Failed to remove STA with HLID %u from FW DB\n\r", uHlid);
                        }
#endif
                    }
                }

            }
        }
        else if(ROLE_DEVICE == pDrv->roleType)
        {
            // Remove link
            uint32_t    uHlid;
            linkType_e eLinkType;
            EWlanLinkState eState;
            for (uHlid=0; uHlid<WLANLINKS_MAX_LINKS; uHlid++)
            {
                wlanLinks_GetLinkState(&eState, uHlid);
                if((TIWDRV_NETIF_ID_P2PDEV == wlanLinks_GetNetIfId(uHlid)) &&
                        WLANLINK_STATE_FREE != eState)
                {
                    if (wlanLinks_GetLinkType(&eLinkType, uHlid) != OK)
                    {
                        ASSERT_GENERAL(0);
                        return -NOK;
                    }

                    if ((eLinkType != WLANLINK_TYPE_SPECIFIC))
                    {
                        udata_ResetLinkStats(uHlid);
                        if (wlanLinks_RemoveLink(uHlid) != OK)
                        {
                            //GTRACE(GRP_DRIVER_MX,"cc3xxx_trnspt_cmd_if_stop_role(): Failed to free link, HLID=%u", uHlid);
                            ASSERT_GENERAL(0);// ASSERT_GENERAL(0);//  changed to ASSERT_GENERAL(0)
                            return -NOK;
                        }
                    }
                }
            }
        }
    }
    else
    {
        GTRACE(GRP_DRIVER_MX, "Not enable to stop role id %d status = ENUM(CommandStatus_e,%d)",
                pDrv->roleId,
                cmdComplete.info.status);
        CME_CC3XX_PORT_PRINT_ERROR("\n\r CMD_ROLE_STOP failed roleId:%d, status:%d\n\r", pDrv->roleId, retVal);
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
    }

out:
   //

    return rc;
}

/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_start_role

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    This command stops a (previously started) role,
                    so the F/W can on longer select to activate it.

    CALLER:         caller

    PARAMETERS:     pParam - pointer to Role Start parameters
                    pRetunParam - pointer to Role Start return parameters

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_start_role(void *apDrv, void *apParams, RoleCommonParam_t *apRates, SlotTime_e aSlotTime)
{
    int ret = 0;
    int                retVal;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apDrv;
    RoleStartParameters_t *pParam;
    //CommandParamContol_t    cmd;
    CommandParamContol_t cmd;
    CommandComplete_t cmdComplete;
    uint32_t          uAcId;
    TWlanLinkInfo *pLinkInfo = NULL;

    memset (&cmdComplete, 0xFF , sizeof(CommandComplete_t));
    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.nabHeader.opcode = CMD_ROLE_START;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID = CMD_ROLE_START;
    pParam = (RoleStartParameters_t *)cmd.commandParam.param;


    CME_CC3XX_PORT_PRINT("\n\r CMD_ROLE_START : roleType:%d roleID:%d ",(uint8_t)pDrv->roleType, (uint8_t)pDrv->roleId);
    GTRACE(GRP_WPA_SUPPLICANT, "CMD_ROLE_START : roleType:%d roleID:%d ",(uint8_t)pDrv->roleType, (uint8_t)pDrv->roleId);

    if(!pParam)
    {
        /* unable to allocate command params */
        ret = -1;
        GTRACE(GRP_WPA_SUPPLICANT, "CMD_ROLE_START: ERROR unable to allocate command params!!!"); 
        goto out;
    }

    pParam->roleID = pDrv->roleId;
    pParam->roleType = (uint8_t)pDrv->roleType;

    //clear isDfs configuration - set when appropriate
    pParam->isDfsChannel = 0;

    if(ROLE_IS_TYPE_STA_BASED(pDrv->roleType))// ROLE_STA or P2P_ROLE_CL
    {
        struct wpa_driver_auth_params *pParams = apParams;
        //
        // Set RF related parameters
        //

        if(wlanLinks_LinkMacFind( TIWDRV_NETIF_ID_STA, pParams->bssid) != INVALID_LINK)
        {
            //role sta for this mac is already running
            GTRACE(GRP_WPA_SUPPLICANT,"\n\r ERROR!! start_role STA, STA already started: %02x:%02x:%02x:%02x:%02x:%02x",
                    pParams->bssid[0],
                    pParams->bssid[1],
                    pParams->bssid[2],
                    pParams->bssid[3],
                    pParams->bssid[4],
                    pParams->bssid[5]);
            ret =  CMD_GENERAL_STATUS_ERROR; 
            goto out;
        }

        cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(RoleStartParameters_t)+sizeof(RoleStartStaBasedReturn_t));

        if(freq_to_chan(pDrv->assocFreq, &pParam->channelNumber, &pParam->band) < 0)
        {
            ASSERT_GENERAL(0);// ASSERT_GENERAL(0);//  changed to ASSERT_GENERAL(0)
        }
        // set isDfsChannel if needed
        regulatoryDomain_IsChannelSupported(pParam->channelNumber, (Bool32 *)&(pParam->isDfsChannel));
        pParam->bandwidth = (uint8_t)NLCP_CHAN_NO_HT;
        // Station role

        // --------------------------
        //  Prepare RATES
        // --------------------------
        pParam->ex.staBased.basicRateSetBM = apRates->basicRateSetBM;
        pParam->ex.staBased.localSupportedRatesBM = apRates->localSupportedRatesBM;
        pParam->ex.staBased.remotePeerSupportedRatesBM = apRates->remotePeerSupportedRatesBM;


        GTRACE(GRP_DRIVER_CC33, "Peer basic rate 0x%x supported rates 0x%x local rates 0x%x",
                                 pParam->ex.staBased.basicRateSetBM,
                                 pParam->ex.staBased.remotePeerSupportedRatesBM,
                                 pParam->ex.staBased.localSupportedRatesBM);
        
        CME_PRINT_REPORT("\r\nPeer basicRateSetBM:0x%x remotePeerSupportedRatesBM(remote):0x%x localSupportedRatesBM:0x%x",
                                 pParam->ex.staBased.basicRateSetBM,
                                 pParam->ex.staBased.remotePeerSupportedRatesBM,
                                 pParam->ex.staBased.localSupportedRatesBM);

        // --------------------------
        //  Prepare BEACON
        // --------------------------
        pParam->ex.staBased.beaconInterval = pDrv->pAuthInfo->peerInfo.beacon_interval;

        // --------------------------
        //  Prepare SSID & BSSID
        // --------------------------
        /*GTRACE(GRP_DRIVER_CC33, "Beacon interval %d SSID len %d",
                                 pParam->ex.staBased.beaconInterval,
                                 pParams->ssid_len);
        */
        IRQ_UtilCopyMacAddress(pParams->bssid, pParam->ex.staBased.bssId);
        os_memcpy(pParam->ex.staBased.ssid.ssid, pParams->ssid, pParams->ssid_len);
        pParam->ex.staBased.ssid.ssidLength = pParams->ssid_len;
        pParam->ex.staBased.ssid.ssidType = SSID_TYPE_ANY;

        //CMD_ROLE_START STA
        retVal = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), sizeof(RoleStartStaBasedReturn_t));
        cmdComplete.info.status = retVal;
        if(retVal < 0)
        {
            /* failed */
            CME_CC3XX_PORT_PRINT_ERROR("\n\r ERROR!! start_role no command complete failed");
            GTRACE(GRP_WPA_SUPPLICANT, "ERROR!! start_role no command complete failed");
             ret =  CMD_GENERAL_STATUS_ERROR;//ret = -1;
            goto out;
        }
        else if ((((RoleStartStaBasedReturn_t *)cmdComplete.info.param))->linkId == 0xFF)
        {
            /* failed */
            CME_CC3XX_PORT_PRINT_ERROR("\n\r ERROR!! start_role no command complete");
            GTRACE(GRP_WPA_SUPPLICANT, "ERROR!! start_role no command complete");
            ret =  CMD_GENERAL_STATUS_ERROR;//ret = -1;
            goto out;

        }
        else //STILL ON ROLE_STA
        {
            pLinkInfo = (TWlanLinkInfo *)os_malloc(sizeof(TWlanLinkInfo));
             RoleStartStaBasedReturn_t *pRetParam = (RoleStartStaBasedReturn_t *)cmdComplete.info.param;

             pDrv->freq = pDrv->assocFreq;
             // --------------------------
             //  Prepare Link and session ID
             // --------------------------
             pLinkInfo->eIfMode = TIWDRV_IF_MODE_STA;
             pLinkInfo->eType = WLANLINK_TYPE_SPECIFIC;
             pLinkInfo->uNetIfId = TIWDRV_NETIF_ID_STA;

             //For STA
             if(wlanLinks_AddLink(pLinkInfo, pRetParam->linkId, pRetParam->session, pParam->ex.staBased.bssId, 0))
             {
                 ASSERT_GENERAL(0);
                 ret = NOK;
                 goto out_free;
             }
             CME_CC3XX_PORT_PRINT("\n\r CMD_ROLE_START: STA ,command complete, linkId:%d session:%d",pRetParam->linkId,pRetParam->session);
             GTRACE(GRP_WPA_SUPPLICANT, "CMD_ROLE_START: STA ,command complete, linkId:%d session:%d",pRetParam->linkId,pRetParam->session);

             /* Add the STA link to the Rx and Tx */
             udata_AddLink(pRetParam->linkId,
                           pRetParam->linkId,
                           (linkType_e)WLANLINK_TYPE_SPECIFIC,
                           (tiwdrv_if_mode_e)TIWDRV_IF_MODE_STA,
                           (RoleID_t)pDrv->roleId,
                           pLinkInfo->uNetIfId,
                           0/*MGMT_RATE_POLICY_INDEX(pRoleSta->pRoleDesc->uActiveIfId)*/,
                           0/*DATA_RATE_POLICY_BASE_INDEX(pRoleSta->pRoleDesc->uActiveIfId)*/);


             /* By default set all ACs of both links as not required for admission control (updated after connection) */
             for (uAcId = 0; uAcId < MAX_NUM_OF_AC; uAcId++)
             {
                 udata_SetAdmissionStatus(pRetParam->linkId, uAcId, ADMISSION_NOT_REQUIRED, AC_ADMITTED);
             }

             /* Get a new Tx-Session-ID and set to udata and to the Start-Role command */
             //uSessionId = wlanLinks_IncrementTxSessionId(cmd->ex.sta.dataHLID);
             udata_SetTxSessionId(pRetParam->linkId, pRetParam->session);

             udata_SetPeerParams(pRetParam->linkId, pParam->ex.staBased.bssId, apRates->WMM);
             udata_SetRxBaPolicy(pRetParam->linkId, 1);

             /* open Tx path only for MGMT packets. */
             udata_SetRxState(pRetParam->linkId, LINK_STATE_CLOSED);
             udata_SetTxState(pRetParam->linkId, LINK_STATE_OPEN);

             udata_ResumeTx();

             //cc3xxx_cmd_set_ps_mode(cmd->roleID, CME_GetPowerSaveMode());
             //cc3xxx_config_slot_time(cmd->roleID, aSlotTime);
             //cc3xxx_config_tx_th(cmd->roleID,  STA_MAX_TX_RETRY);
        }
    }
    else if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
        struct wpa_driver_ap_params *apDriverParams = apParams;

        cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(RoleStartParameters_t)+sizeof(RoleStartApBasedReturn_t));

        // AP role
        //
        // Set RF related parameters
        //
        if(freq_to_chan(apDriverParams->freq->freq, &pParam->channelNumber, &pParam->band) < 0)
        {
            ASSERT_GENERAL(0);// ASSERT_GENERAL(0);//  changed to ASSERT_GENERAL(0)
        }
        // set isDfsChannel if needed
        regulatoryDomain_IsChannelSupported(pParam->channelNumber, (Bool32 *)&(pParam->isDfsChannel));
        pParam->bandwidth = NLCP_CHAN_NO_HT;
        pParam->ex.apBased.basicRateSetBM           = apRates->basicRateSetBM;
        pParam->ex.apBased.beaconInterval           = apRates->beaconInterval;
        pParam->ex.apBased.dtimInterval             = apRates->dtimInterval;
        pParam->ex.apBased.localSupportedRatesBM    = apRates->localSupportedRatesBM;
        pParam->ex.apBased.WMM                      = apRates->WMM;


        GTRACE(GRP_DRIVER_CC33, " AP ROLE:  Peer basic rate 0x%x beacon interval %d local rates 0x%x",
                                 pParam->ex.apBased.basicRateSetBM,
                                 pParam->ex.apBased.beaconInterval,
                                 pParam->ex.apBased.localSupportedRatesBM);
        

        //CMD_ROLE_START AP
        retVal = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), sizeof(RoleStartApBasedReturn_t));
        cmdComplete.info.status = retVal;
        if(retVal < 0)
        {
            /* failed */
            CME_CC3XX_PORT_PRINT_ERROR("\n\r ERROR!! start_role AP no command complete failed");
             ret =  CMD_GENERAL_STATUS_ERROR;//ret = -1;
            goto out;
        }
        else if ((((RoleStartApBasedReturn_t *)cmdComplete.info.param))->globalHLID == 0xFF)
        {
            /* failed */
            CME_CC3XX_PORT_PRINT_ERROR("\n\r ERROR!! start_role AP , invalid  globalHLID ");
             ret =  CMD_GENERAL_STATUS_ERROR;//ret = -1;
            goto out;

        }
        else //ROLE_AP CONT
        {
            pLinkInfo = (TWlanLinkInfo *)os_malloc(sizeof(TWlanLinkInfo));
            struct wpa_driver_ap_params *apDriverParams = apParams;
            Bool_e  enable;
            RoleStartApBasedReturn_t *pRetParam = (RoleStartApBasedReturn_t *)cmdComplete.info.param;

            CME_CC3XX_PORT_PRINT("\n\r CMD_ROLE_START : AP ");

            pDrv->freq = apDriverParams->freq->freq;

            // --------------------------
            //  Prepare Link and session ID
            // --------------------------
            pLinkInfo->eIfMode = TIWDRV_IF_MODE_SAP;
            pLinkInfo->uNetIfId = TIWDRV_NETIF_ID_SAP;
            // Broadcast link
            pLinkInfo->eType = WLANLINK_TYPE_BRCST;
            //FOr AP Broadcast
            if(wlanLinks_AddLink(pLinkInfo, pRetParam->broadcastHLID, pRetParam->broadcastSession, apDriverParams->ssid, 0))
            {
                ASSERT_GENERAL(0);
                ret = NOK;
                goto out_free;
            }

            /* WLANLINK_TYPE_BRCST Add the new link in  Rx and Tx */
            udata_AddLink(pRetParam->broadcastHLID,
                          pRetParam->broadcastHLID,
                          (linkType_e)pLinkInfo->eType,
                          (tiwdrv_if_mode_e)pLinkInfo->eIfMode,
                          (RoleID_t)pDrv->roleId,
                          pLinkInfo->uNetIfId,
                          0/*MGMT_RATE_POLICY_INDEX(pRoleSta->pRoleDesc->uActiveIfId)*/,
                          0/*DATA_RATE_POLICY_BASE_INDEX(pRoleSta->pRoleDesc->uActiveIfId)*/);

            /* By default set all ACs of both links as not required for admission control (updated after connection) */
            for (uAcId = 0; uAcId < MAX_NUM_OF_AC; uAcId++)
            {
                udata_SetAdmissionStatus(pRetParam->broadcastHLID, uAcId, ADMISSION_NOT_REQUIRED, AC_ADMITTED);
            }
            udata_SetTxSessionId(pRetParam->broadcastHLID, pRetParam->broadcastSession);

            if (apDriverParams->auth_algs != WPA_AUTH_ALG_OPEN)
            {
                udata_SetDataEncryption(pRetParam->broadcastHLID, TRUE, FALSE, FALSE);
                wlanLinks_SetLinkDataEncryption(pRetParam->broadcastHLID, TRUE);
            }
            else
            {
                udata_SetDataEncryption(pRetParam->broadcastHLID, FALSE, FALSE, FALSE);
                wlanLinks_SetLinkDataEncryption(pRetParam->broadcastHLID, FALSE);
            }

            udata_SetTxSessionId(pRetParam->broadcastHLID, pRetParam->broadcastSession);

            /* open Tx path only for MGMT packets. */
            udata_SetRxState(pRetParam->broadcastHLID, LINK_STATE_OPEN);
            udata_SetTxState(pRetParam->broadcastHLID, LINK_STATE_OPEN);

            //////// Global link
            pLinkInfo->eType = WLANLINK_TYPE_GLOBAL;
            //for AP global
            if(wlanLinks_AddLink(pLinkInfo, pRetParam->globalHLID, pRetParam->globalSession, apDriverParams->ssid, 0))
            {
                ASSERT_GENERAL(0);
                ret = NOK;
            }

            /* WLANLINK_TYPE_GLOBAL Add the new link in  Rx and Tx */
            udata_AddLink(pRetParam->globalHLID,//OSPREY_MX-10
                          pRetParam->globalHLID,
                          (linkType_e)pLinkInfo->eType,
                          (tiwdrv_if_mode_e)pLinkInfo->eIfMode,
                          (RoleID_t)pDrv->roleId,
                          pLinkInfo->uNetIfId,
                          0/*MGMT_RATE_POLICY_INDEX(pRoleSta->pRoleDesc->uActiveIfId)*/,
                          0/*DATA_RATE_POLICY_BASE_INDEX(pRoleSta->pRoleDesc->uActiveIfId)*/);

            CME_CC3XX_PORT_PRINT("\r\n AP broadcastHLID:%d globalHLID:%d", pRetParam->broadcastHLID, pRetParam->globalHLID);

            /* By default set all ACs of both links as not required for admission control (updated after connection) */
            for (uAcId = 0; uAcId < MAX_NUM_OF_AC; uAcId++)
            {
                udata_SetAdmissionStatus(pRetParam->globalHLID, uAcId, ADMISSION_NOT_REQUIRED, AC_ADMITTED);
            }
            udata_SetTxSessionId(pRetParam->globalHLID, pRetParam->globalSession);


            /* open Tx path only for MGMT packets. */
            udata_SetRxState(pRetParam->globalHLID, LINK_STATE_OPEN);
            udata_SetTxState(pRetParam->globalHLID, LINK_STATE_OPEN);

            udata_ResumeTx();
            // --------------------------
            //  ERP PROTECTION
            // --------------------------
            enable = apDriverParams->cts_protect? ERP_PROTECTION_ENABLED: ERP_PROTECTION_ENABLED;
            ret = trnspt_cmd_cfg_erp_protection(pDrv->roleId, enable);//CTS_PROTECTION_CFG
            if (ret < 0)
            {
                GTRACE(GRP_DRIVER_CC33, "Set ctsprotect failed %d", ret);
                CME_CC3XX_PORT_PRINT_ERROR("\n\rError: failed to cfg cts protection");
                goto out_free;
            }
            // --------------------------
            //  PREAMBLE -
            //  TRUE - SHORT PREAMBLE
            //  FALSE - LONG PREAMBLE
            // --------------------------
            enable = apDriverParams->preamble? TRUE: FALSE;
            ret = trnspt_cmd_cfg_preamble(pDrv->roleId, enable);
            if (ret < 0)
            {
            //GTRACE(GRP_DRIVER_CC33, "Set preamble failed %d", ret);
                goto out_free;
            }
            // --------------------------
            //  SLOT TIME
            // --------------------------
            ret = trnspt_cmd_cfg_slot_time(pDrv->roleId, aSlotTime);
            if (ret < 0)
            {
            //GTRACE(GRP_DRIVER_CC33, "Set slot time failed %d", ret);
                goto out_free;
            }
            goto out_free;
        }
    }
    else if(pDrv->roleType == ROLE_DEVICE)
    {

        struct wpa_driver_ap_params *apDriverParams = apParams;

        cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(RoleStartParameters_t)+sizeof(RoleStartStaBasedReturn_t));
        GTRACE(GRP_WPA_SUPPLICANT, "CMD_ROLE_START DEVICE, freq = %d", apDriverParams->freq->freq);
                                    
        if(freq_to_chan(apDriverParams->freq->freq, &pParam->channelNumber, &pParam->band) < 0)
        {
            GTRACE(GRP_WPA_SUPPLICANT, "CMD_ROLE_START: Assert in freq_to_chan");
            //ASSERT_GENERAL(0);// ASSERT_GENERAL(0);//  changed to ASSERT_GENERAL(0)
        }
        else
        {
            // set isDfsChannel if needed
            regulatoryDomain_IsChannelSupported(pParam->channelNumber, (Bool32 *)&(pParam->isDfsChannel));
        }
        GTRACE(GRP_WPA_SUPPLICANT, "after freq_to_chan");
        pParam->bandwidth = (uint8_t)NLCP_CHAN_NO_HT;
        // device role


        // --------------------------
        //  Prepare SSID & BSSID
        // --------------------------
        /*GTRACE(GRP_DRIVER_CC33, "Beacon interval %d SSID len %d",
                                 pParam->ex.staBased.beaconInterval,
                                 pParams->ssid_len);
        */


        //CMD_ROLE_START DEVICE
        GTRACE(GRP_WPA_SUPPLICANT, "send CMD_ROLE_START DEVICE");
        retVal = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), sizeof(RoleStartStaBasedReturn_t));
        cmdComplete.info.status = retVal;
        if(retVal < 0)
        {
            /* failed */
            CME_CC3XX_PORT_PRINT_ERROR("\n\r ERROR!! start_role device no command complete failed");
            GTRACE(GRP_WPA_SUPPLICANT, "ERROR!! start_role device no command complete failed");
            ret =  CMD_GENERAL_STATUS_ERROR;//ret = -1;
            goto out;
        }
        else if ((((RoleStartStaBasedReturn_t *)cmdComplete.info.param))->linkId == 0xFF)
        {
            /* failed */
            CME_CC3XX_PORT_PRINT_ERROR("\n\r ERROR!! start_role device no command complete");
            GTRACE(GRP_WPA_SUPPLICANT, "ERROR!! start_role device no command complete");
            ret =  CMD_GENERAL_STATUS_ERROR;//ret = -1;
            goto out;

        }
        else //STILL ON ROLE_DEVICE
        {
            pLinkInfo = (TWlanLinkInfo *)os_malloc(sizeof(TWlanLinkInfo));
            RoleStartStaBasedReturn_t *pRetParam = (RoleStartStaBasedReturn_t *)cmdComplete.info.param;

            pDrv->freq = apDriverParams->freq->freq;
            pDrv->roleStarted = TRUE;
             // --------------------------
             //  Prepare Link and session ID
             // --------------------------
             pLinkInfo->eIfMode = TIWDRV_IF_MODE_P2PDEV;
             pLinkInfo->eType = WLANLINK_TYPE_GLOBAL;
             pLinkInfo->uNetIfId = TIWDRV_NETIF_ID_P2PDEV;

             //For DEVICE
             if(wlanLinks_AddLink(pLinkInfo, pRetParam->linkId, pRetParam->session, pDrv->macAddr, 0))
             {
                 ASSERT_GENERAL(0);
                 ret = NOK;
                 goto out_free;
             }
             CME_CC3XX_PORT_PRINT("\n\r CMD_ROLE_START: DEVICE ,command complete, linkId:%d session:%d",pRetParam->linkId,pRetParam->session);
             GTRACE(GRP_WPA_SUPPLICANT, "CMD_ROLE_START: DEVICE ,command complete, linkId:%d session:%d",pRetParam->linkId,pRetParam->session);
             /* Add the DEVICE link to the Rx and Tx */
             udata_AddLink(pRetParam->linkId,
                           pRetParam->linkId,
                           (linkType_e)pLinkInfo->eType,
                           (tiwdrv_if_mode_e)pLinkInfo->eIfMode,
                           (RoleID_t)pDrv->roleId,
                           pLinkInfo->uNetIfId,
                           0/*MGMT_RATE_POLICY_INDEX(pRoleSta->pRoleDesc->uActiveIfId)*/,
                           0/*DATA_RATE_POLICY_BASE_INDEX(pRoleSta->pRoleDesc->uActiveIfId)*/);


             /* By default set all ACs of both links as not required for admission control (updated after connection) */
             for (uAcId = 0; uAcId < MAX_NUM_OF_AC; uAcId++)
             {
                 udata_SetAdmissionStatus(pRetParam->linkId, uAcId, ADMISSION_NOT_REQUIRED, AC_ADMITTED);
             }

             /* Get a new Tx-Session-ID and set to udata and to the Start-Role command */
             //uSessionId = wlanLinks_IncrementTxSessionId(cmd->ex.sta.dataHLID);
             udata_SetTxSessionId(pRetParam->linkId, pRetParam->session);

             udata_SetPeerParams(pRetParam->linkId, pDrv->macAddr, cfgIsStaWmeEnabled());
             udata_SetRxBaPolicy(pRetParam->linkId, 0);

             /* open Tx path only for MGMT packets. */
             udata_SetRxState(pRetParam->linkId, LINK_STATE_CLOSED);
             udata_SetTxState(pRetParam->linkId, LINK_STATE_OPEN);

             udata_ResumeTx();

             //cc3xxx_cmd_set_ps_mode(cmd->roleID, CME_GetPowerSaveMode());
             //cc3xxx_config_slot_time(cmd->roleID, aSlotTime);
             //cc3xxx_config_tx_th(cmd->roleID,  STA_MAX_TX_RETRY);

        }
    }
out_free:

    os_free(pLinkInfo);
out:
    return ret;


}

/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_change_role_type

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Send disable role command to FW 
                    and enable with different roleType
                    used for changing from sta role type to p2p client
                    while keeping same wpa_s priv 

    CALLER:         

    PARAMETERS:     apPriv - IN/OUT pointer to the driver DB
                    aRoleType - type of role that should be enabled

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_change_role_type (void *apDrv, Role_e aRoleType)
{
    ti_driver_ifData_t      *pDrv = (ti_driver_ifData_t *)apDrv;
    int                      retVal = 0;

    retVal = cc3xxx_trnspt_cmd_if_disable_role(apDrv);
    if (retVal != 0)
    {
        GTRACE(GRP_WPA_SUPPLICANT, "Disable roleid (%d) failed!", pDrv->roleId);
        CME_PRINT_REPORT_ERROR("\n\rDisable roleid (%d) failed!", pDrv->roleId);
        return -1;
    } 
    retVal = cc3xxx_trnspt_cmd_if_enable_role(apDrv, aRoleType);
    if (retVal != 0)
    {
        GTRACE(GRP_WPA_SUPPLICANT, "Enable roleid (%d) failed!", pDrv->roleId);
        CME_PRINT_REPORT_ERROR("\n\rEnable roleid (%d) failed!", pDrv->roleId);
        return -1;
    } 

    CME_PRINT_REPORT("\n\rcc3xxx_trnspt_cmd_if_change_role_type,from RoleType:%d to RoleType: %d",pDrv->roleType,aRoleType);

    //change role_type
    pDrv->roleType = aRoleType;

    return 0;
}

/******************************************************************************/
// ============================================================================
//      Configure APIs
// ============================================================================
/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_cfg

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Firmware configuration command

    PARAMETERS:     pBuf  - pointer to configuration param
                    cfgID - command configuration ID
                    len   - command lengt

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_cfg(uint8_t *pBuf, Cfg_e cfgID, size_t len)
{
    CommandParamContol_t cmd;
    CommandComplete_t cmdComplete;
    Cfg_t cmdParams;
    int retVal;
    int rc = 0;

    os_memset(&cmdParams, 0x0, sizeof(Cfg_t));
    
    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.nabHeader.opcode       = CMD_CONFIGURE;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID     = CMD_CONFIGURE;
    cmdParams.id               = cfgID;
    cmdParams.length           = len;
    
    /* Check if the buffer is big enough */
    if (len > sizeof(Cfg_u))
    {
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR!! trnspt_cmd_if_cfg failed: %d\n\r", cfgID);
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR!! len of trnspt_cmd_if_cfg = %d, "
                                   "exceeds sizeof(Cfg_u) = %d\n\r",
                                   len, sizeof(Cfg_u));
        return CMD_GENERAL_STATUS_ERROR;
    }
    os_memcpy(&(cmdParams.ex), pBuf, len);
    os_memcpy(cmd.commandParam.param, &cmdParams, sizeof(Cfg_t));

    cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(Cfg_t));

    // --------------------------
    //  Send CMD
    // --------------------------
    retVal = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), 0);
    cmdComplete.info.status = retVal;
    if(cmdComplete.info.status == 0 )
    {
        rc = CMD_STATUS_SUCCESS;
    }
    else
    {
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR!! trnspt_cmd_if_cfg failed:%d retVal:%d", cfgID, retVal);

        /*GTRACE(GRP_DRIVER_MX, "Not enable to ENUM(Cfg_e,%d), status = ENUM(CommandStatus_e,%d)",
                       cfgID,
                       cmdComplete.info.status);*/
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
    }

    return rc;

}
/******************************************************************************

    FUNCTION:       trnspt_cmd_cfg_erp_protection

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    Configure ERP Protection Mode for an associated STA,
                    handled by the Driver

    PARAMETERS:     roleID  - role ID
                    erpProtectionEnabled - ERP Protection mode

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int  trnspt_cmd_cfg_erp_protection (RoleID_t roleID, Bool_e erpProtectionEnabled)
{
   //

    CtsProtectionCfg_t param;
    int retVal = CMD_STATUS_SUCCESS;
    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID               = roleID;
    param.erpProtectionEnabled = erpProtectionEnabled;
    CME_CC3XX_PORT_PRINT("\n\r CMD_CONFIGURE: CTS_PROTECTION_CFG roleID:%d erpProtectionEnabled:%d", param.roleID, erpProtectionEnabled);


    retVal = cc3xxx_trnspt_cmd_if_cfg((uint8_t*)&param, CTS_PROTECTION_CFG, sizeof(CtsProtectionCfg_t));

    return retVal;
}

/******************************************************************************

    FUNCTION:       cc3xxx_trnspt_cmd_if_config_tx_param

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    Configure TX parameters

    PARAMETERS:     roleID       - role ID
                    pParamAc     - pointer to AC param
                    psScheme     - ps scheme
                    isMuEdca     - is MU EDCA configured
                    pParamMuEdca - pointer to MU EDCA param


    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_config_tx_param (void *apPriv, AcCfg_t *pParamAc, uint8_t psScheme,
                            Bool_e isMuEdca, uint8_t *pParamMuEdca, uint8_t currAc)
{
   //

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    int8_t retVal =0 ;
    TxParamCfg_t  param;

    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID   = pDrv->roleId;
    param.psScheme = (uint8_t)(PSScheme_e)psScheme;
#ifndef DISABLE_WIFI6
    param.isMuEdca = isMuEdca;
#else
    param.isMuEdca = FALSE;
#endif


    param.ac = currAc;

    param.aifsn = pParamAc->aifsn;
    param.acm   = pParamAc->acm;
    param.cwMax = pParamAc->cwMax;
    param.cwMin = pParamAc->cwMin;
    param.txopLimit = pParamAc->txopLimit;

    /*GTRACE(GRP_DRIVER_MX, "TX param: ac %d, aifsn %d, acm %d, cwMax %d, cwMin %d, tx op %d",
                           param.ac,
                           param.aifsn,
                           param.acm,
                           param.cwMax,
                           param.cwMin,
                           param.txopLimit);
    */
    CME_CC3XX_PORT_PRINT("\n\r CMD_CONFIGURE: TX_PARAMS_CFG: ac: %d, aifsn: %d, acm: %d, cwMax: %d, cwMin: %d, txopLimit: %d\n\r",
                           param.ac,
                           param.aifsn,
                           param.acm,
                           param.cwMax,
                           param.cwMin,
                           param.txopLimit);

#ifndef DISABLE_WIFI6
    // set MU EDCA
    if(FALSE != param.isMuEdca)
    {
        param.muEdca.aifs           = pParamMuEdca[0];
        param.muEdca.ecw_min_max    = pParamMuEdca[1];
        param.muEdca.mu_edca_timer  = pParamMuEdca[2];
    }
#endif


    retVal = cc3xxx_trnspt_cmd_if_cfg((uint8_t*)&param, TX_PARAMS_CFG, sizeof(TxParamCfg_t));

    return retVal;
}
/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_cfg_assoc_info

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Configuration for post association

    CALLER:         caller

    PARAMETERS:     roleID - role id
                    aid    - aid value, as received in the association
                    wmeEnabled - Defines if wmm is enabled

    RETURNS:        return

 ******************************************************************************/
int8_t cc3xxx_trnspt_cmd_if_cfg_assoc_info (RoleID_t roleID, uint16_t aid, Bool_e wmeEnabled,
                                            mbssidData_t *mbssidData)
{
   //

    int8_t retVal;

    AssocInfoCfg_t  param = {0};
    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID = roleID;
    param.aid    = aid;
    param.wmeEnabled = wmeEnabled;
    param.nonTransmitted = (mbssidData->mbssidIndex > 0);
    param.bssidIndex = mbssidData->mbssidIndex;
    param.bssidIndicator = mbssidData->mbssidIndicator;
    IRQ_UtilCopyMacAddress(mbssidData->TransmittingBssid, param.transBssid);

    CME_CC3XX_PORT_PRINT("\n\r CMD_CONFIGURE: ASSOC_INFO_CFG "
        "non-transmitted bssid=%d, index=%d, transmitting addr=" MACSTR, 
        param.nonTransmitted, param.bssidIndex, MAC2STR(param.transBssid));


    retVal = cc3xxx_trnspt_cmd_if_cfg((uint8_t*)&param, ASSOC_INFO_CFG, sizeof(AssocInfoCfg_t));

    return retVal;
}

/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_cfg_peer_cap

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Configures HT/HE peer capabilities

    CALLER:         caller

    PARAMETERS:     roleID - role id
                    pParam - pointer to peer capabilities
                    localSupportedRates - local supported rates

    RETURNS:        return

******************************************************************************/
int8_t cc3xxx_trnspt_cmd_if_cfg_peer_cap (RoleID_t roleID,
                             PeerCap_t *pParam,
                             uint32_t supportedRates)
{
   //

    int8_t retVal = 0;

    PeerCapCfg_t param;
    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID = roleID;
    param.supportedRatesBM = supportedRates;

    os_memcpy(&param.peerCap, pParam, sizeof(PeerCap_t));

    CME_CC3XX_PORT_PRINT("\n\r CMD_CONFIGURE: PEER_CAP_CFG supportedRates: 0x%x", param.supportedRatesBM);

    retVal = cc3xxx_trnspt_cmd_if_cfg((uint8_t*)&param, PEER_CAP_CFG, sizeof(PeerCapCfg_t));

    return retVal;
}

/******************************************************************************

    FUNCTION:       cc3xxx_trnspt_cmd_if_cfg_bss_cap

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    Configures HT/HE bss capabilities

    CALLER:         caller

    PARAMETERS:     roleID - role id
                    pParam - pointer to bss capbilities

    RETURNS:        return

******************************************************************************/
int8_t cc3xxx_trnspt_cmd_if_cfg_bss_cap (RoleID_t roleID, BssCap_t *pParam)
{
   //

    int8_t retVal;

    BssOperationCfg_t param;
    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID = roleID;

    os_memcpy(&param.BssCap, pParam, sizeof(BssCap_t));

    CME_CC3XX_PORT_PRINT("\n\r CMD_CONFIGURE: BSS_OPERATION_CFG");
    retVal = cc3xxx_trnspt_cmd_if_cfg((uint8_t*)&param, BSS_OPERATION_CFG, sizeof(BssOperationCfg_t));

    return retVal;
}

/******************************************************************************

    FUNCTION:       trnspt_cmd_cfg_slot_time

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    Set slot time

    CALLER:         caller

    PARAMETERS:     roleID - role id
                    slotTime - slotTime

    RETURNS:        return

******************************************************************************/
int trnspt_cmd_cfg_slot_time (RoleID_t roleID, SlotTime_e slotTime)
{
   //

    int retVal;

    SlotTimeCfg_t param;
    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID = roleID;

    param.slotTime = slotTime;
    CME_CC3XX_PORT_PRINT("\n\r CMD_CONFIGURE: SLOT_CFG");

    retVal = cc3xxx_trnspt_cmd_if_cfg((uint8_t*)&param, SLOT_CFG, sizeof(SlotTimeCfg_t));
    return retVal;
}

/******************************************************************************

    FUNCTION:       trnspt_cmd_cfg_preamble

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    Configured pramble

    CALLER:         caller

    PARAMETERS:     roleID - role id
                    shortBPreambleSupported - is short preamble supported

    RETURNS:        return

******************************************************************************/
int  trnspt_cmd_cfg_preamble (RoleID_t roleID, Bool_e shortBPreambleSupported)
{
   //

    int retVal;

    PreambleTypeCfg_t param;
    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID = roleID;

    param.shortBPreambleSupported = shortBPreambleSupported;
    CME_CC3XX_PORT_PRINT("\n\r CMD_CONFIGURE: PREAMBLE_TYPE_CFG");

    retVal = cc3xxx_trnspt_cmd_if_cfg((uint8_t*)&param, PREAMBLE_TYPE_CFG, sizeof(PreambleTypeCfg_t));

    return retVal;
}
/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_send_stop_scan

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Send the CMD_STOP_SCAN

    CALLER:         cc3xxx_trnspt_cmd_if_stop_sched_scan

    PARAMETERS:     roleID - role ID
                    scanRequestType - scan request type to stop
                    isET - it is stop by early termination

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_send_stop_scan (uint8_t roleID,
                              EScanRequestType scanRequestType,
                              Bool_e isET)
{
    CommandParamContol_t    cmd;
    CommandComplete_t       cmdComplete;
    int16_t                 retVal =0;
    ScanStopCmdParam_t      *cmdParams = (ScanStopCmdParam_t*)&cmd.commandParam.param;

    /*GTRACE(GRP_DRIVER_MX, "Scan stop cmd: role %d, scan type: ENUM(EScanRequestType,%d) is ET %d",
           roleID,
           scanRequestType,
           isET);
    */
    CME_CC3XX_PORT_PRINT("\n\r CMD_STOP_SCAN");

    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.nabHeader.opcode = CMD_STOP_SCAN;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID = CMD_STOP_SCAN;
    cmdParams->roleId = roleID;
    cmdParams->scanRequestType = scanRequestType;
    cmdParams->isET = isET;
    cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(ScanStopCmdParam_t));

    // --------------------------
    //  Send CMD
    // --------------------------
    retVal = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param),0 );
    cmdComplete.info.status = retVal;
    if(retVal <  0 )//|| cmdComplete.info.status != CMD_STATUS_SUCCESS)
    {
    /*    GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed stop scan status ENUM(CommandStatus_e,%d)",
                                           cmdComplete.info.status);*/
        return CMD_GENERAL_STATUS_ERROR;//return -1;
    }

    return cmdComplete.info.status;//0;
}


/******************************************************************************

    FUNCTION:		trnspt_cmd_send_ies

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    This function set the Info elements data for probe req

    CALLER:         cc3xxx_trnspt_cmd_if_one_shot_scan | cc3xxx_trnspt_cmd_if_sched_scan

    PARAMETERS:     roleID - role ID
                    scanType - scan type
                    apSuppParams - Pointer to supplicant parameters
                    This parameters contain the extra info elements
                    roleType - role Type

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t trnspt_cmd_send_ies(uint32_t roleID,
                        EScanRequestType scanType,
                        struct wpa_driver_scan_params *apSuppParams,
                        RoleType_e roleType)
{
    IesScanProbeReq_t   *iesProbeReq;
    //CommandParamContol_t       cmd;
    CommandParamContol_t cmd;
    CommandComplete_t    cmdComplete;
    uint16_t             retVal;
    uint16_t              size = 0;
    dot11_RATES_t        *pDot11Rates;
    uint16_t             len = 0;
    uint8_t              ratesBuf[DOT11_MAX_SUPPORTED_RATES];
    uint32_t            supportedRatesMask, basicRatesMask;
    uint8_t              bWmeEnable = FALSE;
    uint8_t              axEnable   = FALSE;
    uint8_t              *pBuf= NULL;
    int8_t               rc;

    GTRACE(GRP_DRIVER_MX, "trnspt_cmd_send_ies: configuration for probe request role ID = %d", roleID);
    CME_CC3XX_PORT_PRINT("\n\rCMD_SET_PROBE_IE roleID:%d",roleID );


    memset(ratesBuf, 0, DOT11_MAX_SUPPORTED_RATES);//OSPREY_MX-28


    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.nabHeader.opcode = CMD_SET_PROBE_IE;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID = CMD_SET_PROBE_IE;
    cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(IesScanProbeReq_t));

    pBuf = &(cmd.commandParam.param[0]);
    iesProbeReq = (IesScanProbeReq_t*)pBuf;

    if(NULL == iesProbeReq)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed to allocate memory for iesProbeReq");
        CME_CC3XX_PORT_PRINT_ERROR("\n\r ERROR: Failed to allocate memory for iesProbeReq");
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
        goto out;
    }
    memset(iesProbeReq, 0, sizeof(IesScanProbeReq_t));


    // --------------------------
    //  Prepare ies
    // --------------------------
    iesProbeReq->roleID          = roleID;
    iesProbeReq->scanRequestType = (uint8_t)scanType;


    /* Rates */
    pBuf = (uint8_t*)iesProbeReq->iesBuffer;

    pDot11Rates = (dot11_RATES_t *) pBuf;

    cfgGetRates(roleType, &basicRatesMask, &supportedRatesMask);
    basicRatesMask = 0; // probe request should not publish basic rates, so removing the default initialization 
    //convert the rates from bitmask to values
    os_memset(ratesBuf, 0, DOT11_MAX_SUPPORTED_RATES);
    len = convertBitmapToRatesIe(supportedRatesMask, basicRatesMask, ratesBuf);

    GTRACE(GRP_DRIVER_MX, "buildProbeReq: supportedRatesMask = 0x%X, basicRatesMask = 0x%X, len = %d",
              supportedRatesMask,
              basicRatesMask,
              len);
    GTRACE(GRP_GENERAL_ERROR, "buildProbeReq: supportedRatesMask = 0x%X, basicRatesMask = 0x%X, len = %d",
              supportedRatesMask,
              basicRatesMask,
              len);

    ASSERT_GENERAL(len <= DOT11_MAX_SUPPORTED_RATES );//  changed ASSERT_GENERAL to assert

    if(len > DOT11_MAX_SUPPORTED_RATES)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Len > DOT11_MAX_SUPPORTED_RATES");
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR: Len > DOT11_MAX_SUPPORTED_RATES\n");
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
        goto out;
    }

    // fill in the supported rates
   if (len <= SUPPORTED_RATES_MAX_IE_LEN)
   {
       pDot11Rates->hdr.eleLen = len;
   }
   else
   {
       pDot11Rates->hdr.eleLen = SUPPORTED_RATES_MAX_IE_LEN;
   }

   pDot11Rates->hdr.eleId = SUPPORTED_RATES_IE_ID;


   memcpy((void *)pDot11Rates->rates, ratesBuf, pDot11Rates->hdr.eleLen);
   size += sizeof(dot11_eleHdr_t) + pDot11Rates->hdr.eleLen;
   pBuf += sizeof(dot11_eleHdr_t) + pDot11Rates->hdr.eleLen;


   // fill in the extended supported rates
   if (len > SUPPORTED_RATES_MAX_IE_LEN)
   {
       pDot11Rates = (dot11_RATES_t *) pBuf;
       pDot11Rates->hdr.eleId  = EXT_SUPPORTED_RATES_IE_ID;
       pDot11Rates->hdr.eleLen = len - SUPPORTED_RATES_MAX_IE_LEN;
       memcpy((void *)pDot11Rates->rates, &ratesBuf[SUPPORTED_RATES_MAX_IE_LEN], pDot11Rates->hdr.eleLen);
       size += sizeof(dot11_eleHdr_t) + pDot11Rates->hdr.eleLen;
       pBuf += sizeof(dot11_eleHdr_t) + pDot11Rates->hdr.eleLen;

   }
    if(ROLE_IS_TYPE_STA_BASED(roleType))
    {
        bWmeEnable = l2_cfgIsStaWmeEnabled();
#ifndef DISABLE_WIFI6
        axEnable = l2_cfg_isStaHeEnabled() && !(l2_GetWirelessProto());
#endif
    }

    if (bWmeEnable)
    {
        len = l2_cfgBuildHtCapabilitiesIe(roleID, pBuf);

    }
    else
    {
        //GTRACE(GRP_SCAN_MODULE, "802.11n disable due to WME init flag");
        len = 0;
    }
    size += len;
    pBuf += len;

#ifndef DISABLE_WIFI6
    //HE Caps
    if (axEnable)
    {
        len = l2_cfgBuildHeCapabilitiesIe(roleType, pBuf);
        size += len;
        pBuf += len;

    }
#endif

    if(apSuppParams != NULL)
    {
        // Adding the extra info elements from supplicant
        if (apSuppParams->extra_ies_len != 0)
        {

            memcpy(pBuf, apSuppParams->extra_ies, apSuppParams->extra_ies_len);
            size += apSuppParams->extra_ies_len;
            pBuf += apSuppParams->extra_ies_len;

        }
    }

    /*GTRACE(GRP_DRIVER_MX, "buildProbeReq: bWmeEnable = %d, axEnable = %d, Total len = %d",
                   bWmeEnable,
                   axEnable,
                   size);
    */
    CME_CC3XX_PORT_PRINT("\n\rbuildProbeReq: bWmeEnable = %d, axEnable = %d, Total len = %d\n",
                   bWmeEnable,
                   axEnable,
                   size);

    iesProbeReq->iesLen  = size;
    // --------------------------
    //  Prepare buffer to send
    // --------------------------

    //trnspt_cmd_send_ies
    retVal = cmd_Send((char *)&cmd, cmd.nabHeader.len, (char *)&(cmdComplete.info.param), 0);//trnspt_cmd_send_ies

    cmdComplete.info.status = retVal;

    if(retVal == 0 )//&& cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
        rc = (int8_t)cmdComplete.info.status;   //rc = 0;
    }
    else
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed end IE  ENUM(CommandStatus_e,%d)",
                                           cmdComplete.info.status);
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR: Failed end IE  ENUM(CommandStatus_e,%d",cmdComplete.info.status);
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
    }

out:
   //

    return rc;
}

// ============================================================================
//      Supplicant APIs
// ============================================================================

/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_stop_sched_scan

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Stop a periodic scan; command is handled in WLAN
                    services context, when completed a
                    CME_MESSAGE_ID_SCAN_COMPLETE message is pushed
                    to CME queue.

    CALLER:         .stop_sched_scan (supplicant)

    PARAMETERS:     apPriv - pointer to private driver DB

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t cc3xxx_trnspt_cmd_if_stop_sched_scan(void *apPriv)
{
   //

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    GTRACE(GRP_DRIVER_DEBUG, "Scan stop cmd: scanning %d, sched_scanning %d", pDrv->wpa_s->scanning, pDrv->wpa_s->sched_scanning);

    return (cc3xxx_trnspt_cmd_if_send_stop_scan (pDrv->roleId, SCAN_REQUEST_CONNECT_PERIODIC_SCAN, FALSE));
}

/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_one_shot_scan

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    This function is prepares and sends a scan command
                    to the scan module via the transport bus
                    This function also build the info elements for probe
                    request, fill the channel list (reg domain), and
                    the SSID list. this function is handler for ONE_SHOT
                    scan.

    CALLER:         supplicant (.scan2)

    PARAMETERS:     apDrv - Pointer to driver object
                    apParams - Pointer to scan configuration
                    (set by supplicant)

    RETURNS:        status code  -
                    CMD_STATUS_SUCCESS - request was successfully handed
                    to scan module
                    Other status -  request was unsuccessfully handed
                    to scan module

******************************************************************************/
int cc3xxx_trnspt_cmd_if_one_shot_scan(void *apPriv, struct wpa_driver_scan_params *apParams)
{
   
    ti_driver_ifData_t         *apDrv = (ti_driver_ifData_t *)apPriv;
        
    CommandParamContol_t       cmd;
    CommandComplete_t          cmdComplete;//  removed old
    int                        retVal;
    ScanReqStartCmdParam_t     *pScanCmd;      // Scan command parameters
    uint16_t                   n_ssid;         // Number of SSIDs entries
    uint16_t                   allocSize = 0;  // Dynamic allocation, len for pSSIDList

    int8_t                     i, status, rc;

    RoleType_e                 roleType;
    Bool_e                     isWiFiDirectScan = FALSE;

    GTRACE(GRP_DRIVER_MX, "CMD_SCAN: start ONE_SHOT scan roleId=%d, RoleType=%d, iface=%s",
                            apDrv->roleId, apDrv->roleType, apDrv->iface);
    GTRACE(GRP_DRIVER_MX, "[Scan CMD] Params: num_ssids=%d, num_filter_ssids=%d, p2p_probe=%d, extra_ies_len=%d, ssid[0]=%s, ssid[0].ssid_len=%d", 
                            apParams->num_ssids, 
                            apParams->num_filter_ssids,
                            apParams->p2p_probe,
                            apParams->extra_ies_len,
                            apParams->ssids[0],
                            apParams->ssids[0].ssid_len);
    CME_PRINT_SCAN_DEBUG_REPORT("\n\r[Scan CMD] Params: num_ssids=%d, num_filter_ssids=%d, p2p_probe=%d, extra_ies_len=%d, ssid[0]=%s, ssid[0].ssid_len=%d", 
                            apParams->num_ssids, 
                            apParams->num_filter_ssids,
                            apParams->p2p_probe,
                            apParams->extra_ies_len,
                            apParams->ssids[0],
                            apParams->ssids[0].ssid_len);

    CME_PRINT_SCAN_REPORT("\n\rScan CMD: start one shot connection scan roleId=%d, RoleType=%d, iface=%s",
                            apDrv->roleId, apDrv->roleType, apDrv->iface);

    // check whether the scan was triggered by the supplicant or by the CME.
    // when triggered by the CME, the CME state is CME_STA_SUPPLICANT_MANAGED_STATE.
    if (CmeStationFlow_GetCurrentState() != CME_STA_SUPPLICANT_MANAGED_STATE)
    {
        gSupplicantInitiatedScanInProgress = TRUE;
    }

    if ((apParams->num_ssids > 0) && (apParams->p2p_probe))
    {
        //if scan request come for wifi direct, i.e: p2p_probe & ssid is "DIRECT-""
        if (strncmp((const char *)apParams->ssids[0].ssid, P2P_WILDCARD_SSID, P2P_WILDCARD_SSID_LEN) == 0)
        {
            isWiFiDirectScan = TRUE; 
            GTRACE(GRP_DRIVER_MX, "[Scan CMD] isWiFiDirectScan=%d", isWiFiDirectScan);
            CME_PRINT_SCAN_REPORT("\n\r[Scan CMD] isWiFiDirectScan=%d", isWiFiDirectScan);
        }
    }


    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.nabHeader.opcode = CMD_SCAN;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID =CMD_SCAN;

#ifdef TI_CONSIDER_TO_REMOVE
    /* Clean all network profiles from Supplicant when starting a connection scan
     * In case of WPS, supplicant allocated by itself a general network for WPS and clear it at the end of the wps process. */
    // + do not remove profiles for STA role in case it's a p2p_find() request / scan request from the supplicant.
    
    if (!CME_IsOngoingWPSAdHocConnection() 
        && ROLE_IS_TYPE_STA_BASED(apDrv->roleType) 
        && !gSupplicantInitiatedScanInProgress
        && !gSaveCurrentSupplicantProfile)
    {
        cmeRemoveAllProfilesFromSupplicant(apDrv->wpa_s,WLAN_REASON_DEAUTH_LEAVING);
    }
#endif
    /* Get profiles/ad-hoc connection list */
    cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();

    pCmeScanDB->roleId = apDrv->roleId;

    // Allocate survey scan digest to be populated during candidate scan
    if (isextWPS() && isExtWpsScanning())
    {
        cmeSetScanCmeInfo(pCmeScanDB,
                          SCAN_REQUEST_SURVEY_SCAN,    //scan tag is scan request tag
                          &ScanResultTableSyncObj_ull,
                          apParams);
    }

    //part of p2p_find as part of get scan results to report to host
    if (ROLE_IS_TYPE_DEVICE(apDrv->roleType) &&
       (apDrv->p2pFindReportScanResults != FALSE))
    {
        cmeSetScanCmeInfo(pCmeScanDB,
                          SCAN_REQUEST_SURVEY_SCAN,    //scan tag is scan request tag
                          &ScanResultTableSyncObj_ull,
                          apParams);
    }

    cmeSetScanCmeInfo(pCmeScanDB,
                              SCAN_REQUEST_ONE_SHOT,    //scan tag is scan request tag
                              &ScanResultTableSyncObj_ull,
                              apParams);

    scanResultTable_NotifyScanPriodStart(SCAN_REQUEST_ONE_SHOT);
    if(pCmeScanDB->mOneShotProfiles.mNumProfiles > 0)
    {
        n_ssid = pCmeScanDB->mOneShotProfiles.mNumProfiles;
        allocSize = n_ssid * sizeof(ConnScanSSID_t);
    }
    else
    {
        n_ssid = 0;
    }

    // For p2p related we use ssid scan if FW
    if ((ROLE_IS_TYPE_P2P_CLIENT(apDrv->roleType) || ROLE_IS_TYPE_DEVICE(apDrv->roleType)) &&
        (apParams->num_ssids > 0))
    {
        if(apParams->ssids[0].ssid_len > 0)
        {
            pCmeScanDB->mOneShotProfiles.mpProfiles[0].ssid.mSsidLen = apParams->ssids[0].ssid_len;

            os_memcpy(pCmeScanDB->mOneShotProfiles.mpProfiles[0].mSSID,
                                apParams->ssids[0].ssid,
                                apParams->ssids[0].ssid_len);
            pCmeScanDB->mOneShotProfiles.mpProfiles[0].ssid.mHidden = SSID_TYPE_HIDDEN;
            GTRACE(GRP_DRIVER_MX, "pCmeScanDB - add ssid to scan params");
        }
    }


    //GTRACE(GRP_DRIVER_MX, "cc3xxx_trnspt_cmd_if_one_shot_scan: number of profiles %d", n_ssid);
    allocSize += sizeof(ScanReqStartCmdParam_t);
    allocSize = ALIGNN_TO_4(allocSize);
    //allocSize += sizeof(CommandParamContol_t);    //allocSize += sizeof(cmd_header_t);
    /* Allocate scan command & scan parameters memory & SSIDs list */
    pScanCmd = os_zalloc(allocSize);
    if (NULL == pScanCmd)
    {
        //GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed to allocate memory for scan command");
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR: Failed to allocate memory for scan command\n");
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
        goto out;
    }
    cmd.nabHeader.len = sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + allocSize ;

    CME_CC3XX_PORT_PRINT("\n\r SCAN_REQUEST_ONE_SHOT ,n_ssid:%d\n", n_ssid);

    // --------------------------
    //  Prepare scan message
    // --------------------------

    pScanCmd->roleID            = apDrv->roleId;
    pScanCmd->scanRequestType   = SCAN_REQUEST_ONE_SHOT;
    pScanCmd->rssiThreshold     = -127;
    pScanCmd->snrThreshold      = 0;
    pScanCmd->useList           = TRUE;

    /* Do not use Rx Filter in the following cases: */
    /* 1. Open AP is supported*/
    /* 2. For WPS, supplicant makes the filter  */
    /* 3. For P2P Find - scan triggered by the supplicant  */
    /* 4. If we have a profile list  */
    /* 5. If we enable non-transmit MBSSID connection scan  */
    /* For other scenarios, you can consider setting ssidRXFilter to true */
    pScanCmd->ssidRXFilter = FALSE;
  
    pScanCmd->numOfSSIDEntries = n_ssid ? n_ssid : 0;
    GTRACE(GRP_DRIVER_MX, "[Scan CMD] numOfSSIDs=%d, ssidRXFilter=%d n_ssid=%d",
                            pScanCmd->numOfSSIDEntries, pScanCmd->ssidRXFilter, n_ssid);
    CME_PRINT_SCAN_DEBUG_REPORT("\n\r[Scan CMD] numOfSSIDs=%d, ssidRXFilter=%d n_ssid=%d",
                            pScanCmd->numOfSSIDEntries, pScanCmd->ssidRXFilter, n_ssid);
    if (isWiFiDirectScan)
    {
        // P2P filter flag configuration
        // using this flag will make FW filter the probe responces before sending to driver
        pScanCmd->scanParams.u.tScanInfo.scanResultsFilterCfg = SCAN_RESULTS_PASS_P2P;
        gCmeP2pInfo.p2pFindStopping = FALSE;
    }
                   
    // --------------------------
    //  Prepare the IEs
    // --------------------------

    roleType = apDrv->roleType;
    status = trnspt_cmd_send_ies(pScanCmd->roleID,
                                SCAN_REQUEST_ONE_SHOT,
                                apParams,
                                roleType);


    if(OK != status)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed send info elements\n");
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR: Failed send info elements\n");
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
        goto out_free;
    }

    // --------------------------
    //  Prepare the SSID List
    // --------------------------
    if(n_ssid)
    {
        ConnScanSSID_t *pSSIDList = (ConnScanSSID_t*)((uint8_t*)pScanCmd + sizeof(ScanReqStartCmdParam_t));

        for (i = 0; i < pScanCmd->numOfSSIDEntries; ++i)
        {
            /* SSID len */
            pSSIDList[i].ssidLength = pCmeScanDB->mOneShotProfiles.mpProfiles[i].ssid.mSsidLen;
            /* Copy the SSID */
            memcpy(pSSIDList[i].ssid,
                   pCmeScanDB->mOneShotProfiles.mpProfiles[i].mSSID,
                   pSSIDList[i].ssidLength);

            /* Unicast/broadcast probe request */
            pSSIDList[i].ssidType =
                    pCmeScanDB->mOneShotProfiles.mpProfiles[i].ssid.mHidden?
                            SSID_TYPE_HIDDEN:SSID_TYPE_PUBLIC;

            CME_CC3XX_PORT_PRINT("\n\r SCAN_REQUEST_ONE_SHOT ,[%d] ssidType:%d ssid:%s\n", i, pSSIDList[i].ssidType,pSSIDList[i].ssid);
            GTRACE(GRP_DRIVER_MX,   "SCAN_REQUEST_ONE_SHOT ,[%d] ssidType:%d ssid:%s\n", 
                                i, pSSIDList[i].ssidType,pSSIDList[i].ssid);

        }

        //in case of p2p scan - add SSID "DIRECT-" and scan type hidden
        if ((apDrv->roleType == ROLE_DEVICE) || 
            (apDrv->roleType == ROLE_P2P_CL))
        {
            //take index 0
            pSSIDList[0].ssidLength = apParams->ssids[0].ssid_len;
            memcpy(pSSIDList[0].ssid, apParams->ssids[0].ssid, apParams->ssids[0].ssid_len);
            pSSIDList[0].ssidType = SSID_TYPE_HIDDEN;
            GTRACE(GRP_DRIVER_MX, "P2P SCAN_REQUEST_ONE_SHOT SsidType:%d ssid:%s", 
                                pSSIDList[0].ssidType, pSSIDList[0].ssid);
        }
    }

    // --------------------------
    // Build channel list
    // --------------------------
    status = trnspt_cmd_build_scan_channel_list(&pScanCmd->scanParams,
                                 SCAN_REQUEST_ONE_SHOT,
                                 apParams,
                                 0,pCmeScanDB->wifi_band_cfg);
    if(OK != status)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed build channel list");
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR: Failed build channel list");
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
        goto out_free;
    }


    // --------------------------
    //  Duration time
    // --------------------------

    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].passiveScanDuration    = scanDwellTimeParams.max_dwell_time_passive_msec;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].scanMaxDuration        = scanDwellTimeParams.max_dwell_time_active_msec;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].scanMinDuration        = scanDwellTimeParams.min_dwell_time_active_msec;

    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_5GHZ].passiveScanDuration      = scanDwellTimeParams.dwell_time_dfs_passive_msec;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_5GHZ].scanMaxDuration          = scanDwellTimeParams.max_dwell_time_active_msec;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_5GHZ].scanMinDuration          = scanDwellTimeParams.min_dwell_time_active_msec;

    // --------------------------
    //  Prepare buffer to send
    // --------------------------

    memcpy((void*)cmd.commandParam.param, (void*)pScanCmd, allocSize);//changed param to data
    //cc3xxx_trnspt_cmd_if_one_shot_scan
    retVal  = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), 0);//
    cmdComplete.info.status = retVal;
    if (retVal < 0)//|| cmdComplete.info.status != CMD_STATUS_SUCCESS)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed start scan status ENUM(CommandStatus_e,%d)",
                        retVal);
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR: Failed start scan status ENUM(CommandStatus_e,%d)",
                        retVal);

        rc = -1;
    }
    else
    {
        rc = 0;
    }


out_free:
    os_free(pScanCmd);

out:
   //

    return rc;
}


/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_sched_scan

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Configure and start periodic scan.
                    This function is prepares and sends a scan command
                    to the scan module via the transport bus
                    This function also build the info elements for probe
                    request, fill the channel list (reg domain), and
                    the SSID list. this function is handler for
                    PERIODIC_SCAN
    CALLER:         supplicant (.sched_scan)

    PARAMETERS:     apDrv - Pointer to driver object
                    apParams - Pointer to scan configuration
                    (set by supplicant)

    RETURNS:        status code  -
                    CMD_STATUS_SUCCESS - request was successfully handed
                    to scan module
                    Other status -  request was unsuccessfully handed
                    to scan module

******************************************************************************/
int cc3xxx_trnspt_cmd_if_sched_scan(void *apPriv,
                                    struct wpa_driver_scan_params *apParams)
{
   //

    ti_driver_ifData_t    *apDrv = (ti_driver_ifData_t *)apPriv;
    //CommandParamContol_t          cmd;
    CommandParamContol_t cmd;
    CommandComplete_t       cmdComplete;
    int                  retVal;
    ScanReqStartCmdParam_t  *pScanCmd;      // Scan command parameters
    uint16_t                  n_ssid;         // Number of SSIDs entries
    uint16_t                  allocSize = 0;  // Dynamic allocation, len for pSSIDList

    int8_t                     i, status, rc;

    //GTRACE(GRP_DRIVER_MX, "Scan CMD: start periodic scan");
    CME_CC3XX_PORT_PRINT("\n\rCMD_SCAN :SCAN_REQUEST_CONNECT_PERIODIC_SCAN");

    // check whether the scan was triggered by the supplicant or by the CME.
    // when triggered by the CME, the CME state is CME_STA_SUPPLICANT_MANAGED_STATE.
    if (CmeStationFlow_GetCurrentState() != CME_STA_SUPPLICANT_MANAGED_STATE)
    {
        gSupplicantInitiatedScanInProgress = TRUE;
    }

    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.nabHeader.opcode = CMD_SCAN;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID = CMD_SCAN;
    
#ifdef TI_CONSIDER_TO_REMOVE
    /* Clean all network profiles from Supplicant when starting a connection scan
     * In case of WPS, supplicant allocated by itself a general network for WPS and clear it at the end of the wps process. */

    if (!CME_IsOngoingWPSAdHocConnection())
    {
        cmeRemoveAllProfilesFromSupplicant(apDrv->wpa_s,WLAN_REASON_DEAUTH_LEAVING);
    }
#endif
    /* Get profiles/ad-hoc connection list */
    cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();

    pCmeScanDB->roleId = apDrv->roleId;

    cmeSetScanCmeInfo(pCmeScanDB,
                      SCAN_REQUEST_CONNECT_PERIODIC_SCAN,    //scan tag is scan request tag
                      &ScanResultTableSyncObj_ull,
                      apParams);

    scanResultTable_NotifyScanPriodStart(SCAN_REQUEST_CONNECT_PERIODIC_SCAN);
    if(pCmeScanDB->mPeriodicProfiles.mNumProfiles > 0)
    {
        n_ssid = pCmeScanDB->mPeriodicProfiles.mNumProfiles;
        allocSize = n_ssid * sizeof(ConnScanSSID_t);
    }
    else
    {
        n_ssid = 0;
    }

    //GTRACE(GRP_DRIVER_MX, "cc3xxx_trnspt_cmd_if_sched_scan: number of profiles %d", n_ssid);
    allocSize += sizeof(ScanReqStartCmdParam_t);
    allocSize = ALIGNN_TO_4(allocSize);
    /* Allocate scan command & scan parameters memory & SSIDs list */
    pScanCmd = os_zalloc(allocSize);
    if (NULL == pScanCmd)
    {
       // GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed to allocate memory for scan command");
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR: Failed to allocate memory for scan command");
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
        goto out;
    }
    cmd.nabHeader.len = sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + allocSize;
    /*************************************************************************************/

    // --------------------------
    //  Prepare scan message
    // --------------------------

    pScanCmd->roleID            = apDrv->roleId;
    pScanCmd->scanRequestType   = SCAN_REQUEST_CONNECT_PERIODIC_SCAN;
    pScanCmd->rssiThreshold     = -127;
    pScanCmd->snrThreshold      = 0;
    pScanCmd->useList           = TRUE;

    // /* Open AP is supported - do not using Rx Filter */
    // if(pCmeScanDB->mIsOpenProfileSupported != 0 && n_ssid != 0)
    // {
    //     pScanCmd->ssidRXFilter = FALSE;
    // }
    // else
    // {
    //     pScanCmd->ssidRXFilter = n_ssid ? TRUE : FALSE;
    // }

    // FW filter is not enabled because it does not support MBSSID
    pScanCmd->ssidRXFilter = FALSE;

    pScanCmd->numOfSSIDEntries = n_ssid ? n_ssid : 0;

    // --------------------------
    //  Prepare the IEs
    // --------------------------

    RoleType_e roleType;
    roleType = apDrv->roleType;


    status = trnspt_cmd_send_ies(pScanCmd->roleID,
                                SCAN_REQUEST_CONNECT_PERIODIC_SCAN,
                                apParams,
                                roleType);

    if(OK != status)
    {
        //GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed send info elements");
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
        goto out_free;
    }

    // --------------------------
    //  Prepare the SSID List
    // --------------------------
    if(n_ssid)
    {
        ConnScanSSID_t *pSSIDList = (ConnScanSSID_t*)((uint8_t*)pScanCmd + sizeof(ScanReqStartCmdParam_t));

        for (i = 0; i < pScanCmd->numOfSSIDEntries; ++i)
        {
            /* SSID len */
            pSSIDList[i].ssidLength = pCmeScanDB->mPeriodicProfiles.mpProfiles[i].ssid.mSsidLen;
            /* Copy the SSID */
            memcpy(pSSIDList[i].ssid,
                   pCmeScanDB->mPeriodicProfiles.mpProfiles[i].mSSID,
                   pSSIDList[i].ssidLength);

            /* Unicast/broadcast probe request */
            pSSIDList[i].ssidType =
                    pCmeScanDB->mPeriodicProfiles.mpProfiles[i].ssid.mHidden?
                            SSID_TYPE_HIDDEN:SSID_TYPE_PUBLIC;
        }
    }


    // --------------------------
    // Build channel list
    // --------------------------
    status = trnspt_cmd_build_scan_channel_list(&pScanCmd->scanParams,
                                          SCAN_REQUEST_CONNECT_PERIODIC_SCAN,
                                          apParams,
                                          SCAN_MAX_SCHED_SCAN_PLANS,pCmeScanDB->wifi_band_cfg);
    if(OK != status)
    {
        //GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed build channel list");
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
        goto out_free;
    }


    // --------------------------
    //  Duration time
    // --------------------------

    pScanCmd->scanParams.u.tConnScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].passiveScanDuration    = scanDwellTimeParams.max_dwell_time_passive_msec;
    pScanCmd->scanParams.u.tConnScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].scanMaxDuration        = scanDwellTimeParams.max_dwell_time_active_msec;
    pScanCmd->scanParams.u.tConnScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].scanMinDuration        = scanDwellTimeParams.min_dwell_time_active_msec;

    pScanCmd->scanParams.u.tConnScanInfo.dwellCfg[RADIO_BAND_5GHZ].passiveScanDuration      = scanDwellTimeParams.dwell_time_dfs_passive_msec;
    pScanCmd->scanParams.u.tConnScanInfo.dwellCfg[RADIO_BAND_5GHZ].scanMaxDuration          = scanDwellTimeParams.max_dwell_time_active_msec;
    pScanCmd->scanParams.u.tConnScanInfo.dwellCfg[RADIO_BAND_5GHZ].scanMinDuration          = scanDwellTimeParams.min_dwell_time_active_msec;

    // --------------------------
    //  Prepare buffer to send
    // --------------------------
    //GTRACE(GRP_DRIVER_MX, "Scheduled scan requested! Number of plans = %d", pScanCmd->scanParams.u.tConnScanInfo.sched_scan_plans_num);

    memcpy((void*)cmd.commandParam.param, (void*)pScanCmd, allocSize);
    //cc3xxx_trnspt_cmd_if_sched_scan

    retVal  = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), 0);
    cmdComplete.info.status = retVal;

    if (retVal < 0)//|| cmdComplete.info.status != CMD_STATUS_SUCCESS)
    {
       /* GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed start scan status ENUM(CommandStatus_e,%d)",
                                   cmdComplete.info.status);*/
        rc = -1;
    }
    else
    {
        rc = 0;
    }

out_free:
    os_free(pScanCmd);

out:
   //

    return rc;

}

/******************************************************************************

    FUNCTION:		cc3xxx_trnspt_cmd_if_site_survey

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    A site survey is managed by CME,
                    the supplicant is unaware of this one-shot scan.
                    This function is prepares and sends a scan command
                    to the scan module via the transport bus
                    This function also build the info elements for probe
                    request, fill the channel list (reg domain), and
                    the SSID list. this function is handler for
                    ONE_SHOT scan without connection

    CALLER:         CME_startSiteSurvey

    PARAMETERS:     roleID - role ID for the scan command

    RETURNS:        status code  -
                    CMD_STATUS_SUCCESS - request was successfully handed
                    to scan module
                    Other status -  request was unsuccessfully handed
                    to scan module

******************************************************************************/
int cc3xxx_trnspt_cmd_if_site_survey(uint8_t roleID, CMEWlanScanCommon_t* pScanCommon) //wlan_scan command
{
    CommandParamContol_t cmd;
    CommandComplete_t       cmdComplete;
    int                     retVal, i;
    ScanReqStartCmdParam_t *pScanCmd;      // Scan command parameters
    int8_t                  status, rc;
    uint16_t                aligned_length;
    uint8_t                 n_ssid;
    uint32_t                allocSize;

    // --------------------------
    //  Prepare CMD
    // --------------------------
    CME_CC3XX_PORT_PRINT("\n\r CMD_SCAN :start site_survey");

    cmd.nabHeader.opcode = CMD_SCAN;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID = CMD_SCAN;

    //GTRACE(GRP_DRIVER_MX, "Scan CMD:  start site survey scan");

    /* Get profiles/ad-hoc connection list */
    cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();

    pCmeScanDB->roleId = roleID;

    cmeSetScanCmeInfo(pCmeScanDB,
                      SCAN_REQUEST_SURVEY_SCAN,    //scan tag is scan request tag
                      &ScanResultTableSyncObj_ull,
                      NULL);

    scanResultTable_NotifyScanPriodStart(SCAN_REQUEST_SURVEY_SCAN);

    //find how many ssid exists on the params
    n_ssid = 0 ;
    for(i=0; i<CME_MAX_SCAN_SSID; i++)
    {
        if(pScanCommon->CMEWlanSsid[i].ssidLen != 0)
        {
            n_ssid++;
        }
        else
        {
            break;//no more ssid in the list
        }
    }

    /* Allocate scan command */
    allocSize = 0;
    allocSize += n_ssid * sizeof(ConnScanSSID_t);
    allocSize += sizeof(ScanReqStartCmdParam_t);
    allocSize = ALIGNN_TO_4(allocSize);

    CME_CC3XX_PORT_PRINT("\n\r SCAN_REQUEST_SURVEY_SCAN ,allocSize:%d n_ssid:%d\n",allocSize,n_ssid);

    pScanCmd = os_zalloc(allocSize);
    if (NULL == pScanCmd)
    {
        //GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed to allocate memory for scan command");
        CME_CC3XX_PORT_PRINT_ERROR("\n\r ERROR: Failed to allocate memory for scan command");
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
        goto out_fail;
    }
    cmd.nabHeader.len = sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + allocSize;
    aligned_length = ALIGNN_TO_4(cmd.nabHeader.len);
    /*************************************************************************************/

    // --------------------------
    //  Prepare scan message
    // --------------------------
    pScanCmd->roleID            = roleID;
    pScanCmd->scanRequestType   = SCAN_REQUEST_ONE_SHOT;
    pScanCmd->rssiThreshold     = -127;
    pScanCmd->snrThreshold      = 0;
    if(n_ssid)
    {
        pScanCmd->useList           = TRUE;
    }
    else
    {
        pScanCmd->useList           = FALSE;
    }
    pScanCmd->ssidRXFilter = n_ssid ? TRUE : FALSE;
    pScanCmd->numOfSSIDEntries = n_ssid;

    // --------------------------
    //  Prepare the SSID List
    // --------------------------

    if(n_ssid)
    {
        ConnScanSSID_t *pSSIDList = (ConnScanSSID_t*)((uint8_t*)pScanCmd + sizeof(ScanReqStartCmdParam_t));

        for (i = 0; i <n_ssid; i++)
        {
            /* SSID len */
            pSSIDList[i].ssidLength = pScanCommon->CMEWlanSsid[i].ssidLen;
            /* Copy the SSID */
            memcpy(pSSIDList[i].ssid,
                    pScanCommon->CMEWlanSsid[i].pSsid,
                    pScanCommon->CMEWlanSsid[i].ssidLen);

            /* Unicast/broadcast probe request */
            pSSIDList[i].ssidType =
                    pScanCommon->CMEWlanSsid[i].mHidden?
                            SSID_TYPE_HIDDEN:SSID_TYPE_PUBLIC;

            CME_CC3XX_PORT_PRINT("\n\r SCAN_REQUEST_SURVEY_SCAN ,[%d] ssidType:%d ssid:%s ssidLen:%d\n", i, pSSIDList[i].ssidType,pSSIDList[i].ssid, pScanCommon->CMEWlanSsid[i].ssidLen);

        }
    }


    // --------------------------
    //  Prepare the IEs
    // --------------------------
    ti_driver_ifData_t *apDrv;
    RoleType_e roleType;
    // Extract the driver object related to this role
    apDrv = getDriverForRoleId(roleID, gpSupplicantGlobals);
    roleType = apDrv->roleType;

    status = trnspt_cmd_send_ies(pScanCmd->roleID,
                                SCAN_REQUEST_ONE_SHOT,
                                NULL,
                                roleType);

    if(OK != status)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed send info elements");
        CME_CC3XX_PORT_PRINT_ERROR("\n\r ERROR: survey scan Failed send info elements");
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
        goto out_fail;
    }

    // --------------------------
    // Build channel list
    // --------------------------
    status = trnspt_cmd_build_scan_channel_list(&pScanCmd->scanParams,
                                 SCAN_REQUEST_ONE_SHOT,
                                 NULL,
                                 0,pScanCommon->Band);
    if(OK != status)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed build channel list");
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR: survey scan ERROR: Failed build channel list");
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
        goto out_fail;
    }



    // --------------------------
    //  Duration time
    // --------------------------
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].passiveScanDuration    = scanDwellTimeParams.max_dwell_time_passive_msec;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].scanMaxDuration        = scanDwellTimeParams.max_dwell_time_active_msec;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].scanMinDuration        = scanDwellTimeParams.min_dwell_time_active_msec;

    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_5GHZ].passiveScanDuration      = scanDwellTimeParams.dwell_time_dfs_passive_msec;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_5GHZ].scanMaxDuration          = scanDwellTimeParams.max_dwell_time_active_msec;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_5GHZ].scanMinDuration          = scanDwellTimeParams.min_dwell_time_active_msec;

    // --------------------------
    //  Prepare buffer to send
    // --------------------------
    memcpy((void*)cmd.commandParam.param, (void*)pScanCmd, allocSize);
    //cc3xxx_trnspt_cmd_if_site_survey
    retVal  = cmd_Send((char *)&cmd,aligned_length, (char *)&(cmdComplete.info.param), 0);
    cmdComplete.info.status = retVal;
    if(retVal <  0)//|| cmdComplete.info.status != CMD_STATUS_SUCCESS)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed start scan status ENUM(CommandStatus_e,%d)",
                                   cmdComplete.info.status);
        CME_CC3XX_PORT_PRINT_ERROR("\n\r ERROR:Failed start scan status ENUM(CommandStatus_e,%d)",cmdComplete.info.status);
        rc = -1;
        goto out_fail;
    }
    else
    {
        rc = 0;
        goto out_success;
    }

out_fail:
out_success:
    if( pScanCmd != NULL )
    {
        os_free(pScanCmd);
    }
    return rc;
}

/******************************************************************************

    FUNCTION:       cc3xxx_trnspt_cmd_if_roc

    DESCRIPTION:    Send the CMD_REMAIN_ON_CHANNEL

    Parameters:     apPriv - pointer to private driver DB
                    aFreq - indicates the channel to remain on

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_roc(void *apPriv, unsigned int aFreq)
{
   //

    int rc, retVal;
    ti_driver_ifData_t       *pDrv = (ti_driver_ifData_t *)apPriv;
    ROCParameters_t          *cmdParams;
    CommandParamContol_t     cmd;
    CommandComplete_t        cmdComplete;
    

    cmd.nabHeader.opcode = CMD_REMAIN_ON_CHANNEL;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID = CMD_REMAIN_ON_CHANNEL;
    cmdParams = (ROCParameters_t*)&cmd.commandParam.param;
    cmdParams->roleID = pDrv->roleId;
    cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(ROCParameters_t));

    if (freq_to_chan(aFreq, &cmdParams->Channel, &cmdParams->Band))
    {
        /*GTRACE(GRP_GENERAL_ERROR, "ERROR: failed to get channel from freq %d for role %d",
                                       aFreq, pDrv->roleId);*/
        return -1;
    }

    // Send the command and wait blocking for response.
    // When the below returns, ROC sequence is completed.
    //cc3xxx_trnspt_cmd_if_roc
    CME_CC3XX_PORT_PRINT("\n\r CMD_REMAIN_ON_CHANNEL : roleID:%d Channel:%d  Band:%d ",cmdParams->roleID, cmdParams->Channel,cmdParams->Band);
    GTRACE(GRP_DRIVER_MX, "CMD_REMAIN_ON_CHANNEL:  roleID:%d Channel:%d  Band:%d ",cmdParams->roleID, cmdParams->Channel,cmdParams->Band);
    retVal  = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), 0);
    cmdComplete.info.status = retVal;
    if(retVal <  0)// || cmdComplete.info.status != CMD_STATUS_SUCCESS)
    {
        //GTRACE(GRP_GENERAL_ERROR, "ERROR: Remain on channel status %d", cmdComplete.info.status);
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
    }
    else
    {
        rc = cmdComplete.info.status;//rc = 0;
    }
    // Mark ROC was activated by driver
    pDrv->rocActive = TRUE;

   //

    return rc;
}

/******************************************************************************

    FUNCTION:       cc3xxx_trnspt_cmd_if_cancel_roc

    DESCRIPTION:    Send the CMD_CANCEL_REMAIN_ON_CHANNEL

    Parameters:     apPriv - pointer to private driver DB

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_cancel_roc(void *apPriv)
{
   //

    int rc, retVal;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    ROCParameters_t         *cmdParams;
    CommandParamContol_t cmd;
    CommandComplete_t       cmdComplete;

    CME_CC3XX_PORT_PRINT("\n\r CMD_CANCEL_REMAIN_ON_CHANNEL,roleId:%d",pDrv->roleId);
    GTRACE(GRP_DRIVER_MX, "CMD_CANCEL_REMAIN_ON_CHANNEL,roleId:%d",pDrv->roleId);

    cmd.nabHeader.opcode = CMD_CANCEL_REMAIN_ON_CHANNEL;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID = CMD_CANCEL_REMAIN_ON_CHANNEL;
    cmdParams = (ROCParameters_t*)&cmd.commandParam.param;
    cmdParams->roleID = pDrv->roleId;
    cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(ROCParameters_t));
    //cc3xxx_trnspt_cmd_if_cancel_roc
    retVal  = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), 0);
    cmdComplete.info.status = retVal;
    if(retVal <  0)// || cmdComplete.info.status != CMD_STATUS_SUCCESS)
    {
        //GTRACE(GRP_GENERAL_ERROR, "ERROR: Remain on channel status %d", cmdComplete.info.status);
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
    }
    else
    {
        rc = cmdComplete.info.status;   ////rc = 0;
    }

    // Mark ROC was deactivated by driver
    pDrv->rocActive = FALSE;

   //

    return rc;
}


/******************************************************************************

    FUNCTION:       cc3xxx_config_assoc_peer- for STA

    DESCRIPTION:    Send ACX_HT_BSS_OPERATION
                         ACX_PEER_CAP
                         ACX_AID
                         ACX_ARP_IP_FILTER
                         CMD_SET_TEMPLATE
                         ACX_CTS_PROTECTION

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_config_assoc_peer(void *apDrv, PeerCap_t *aPeerCap,
                             BssCap_t *aBssCap, uint32_t localSupportedRates,
                             uint32_t link, uint8_t wmmEnable, uint16_t useProtection)
{

    ti_driver_ifData_t *pDrv        = (ti_driver_ifData_t *)apDrv;
    uint32_t                        uAid;
    RoleID_t                        RoleId = pDrv->roleId;

    // TODO
//    PktTemplate_t           tTemplateCfg;
//    ArpRspTemplate_t        tArpRspTemplate;
//    ACXConfigureIP_t        tArpIpFilter;

/**************************************************************************/
    // Set CTS protection (enabled/disabled)
    if(trnspt_cmd_cfg_erp_protection(RoleId, useProtection) != CMD_STATUS_SUCCESS)  //< 0)
	{
        GTRACE(GRP_DRIVER_CC33, "Warning: failed to cfg cts protection");
        CME_CC3XX_PORT_PRINT_ERROR("\n\rError: assert: failed to cfg cts protection useProtection:%d", useProtection);
        ASSERT_GENERAL(0);
	}

/**************************************************************************/

	wlanLinks_GetLinkAid(&uAid, link);

	if(cc3xxx_trnspt_cmd_if_cfg_assoc_info(RoleId, uAid, wmmEnable, &pDrv->mbssidData) != CMD_STATUS_SUCCESS)  //< 0)
	{
		GTRACE(GRP_DRIVER_CC33, "Error: failed to set association info uAid:%d",uAid);
		CME_CC3XX_PORT_PRINT_ERROR("\n\rError: failed to set association info uAid:%d",uAid);
		 ASSERT_GENERAL(0);
	}

/**************************************************************************/
    // Set the default HT capabilities parameters
    if(cc3xxx_trnspt_cmd_if_cfg_peer_cap(RoleId, aPeerCap, localSupportedRates) != CMD_STATUS_SUCCESS)  //< 0)
    {
        GTRACE(GRP_DRIVER_CC33, "Warning: failed to set peer cap");
        CME_CC3XX_PORT_PRINT_ERROR("\n\rError: failed to set peer cap RoleId:%d",RoleId);
        ASSERT_GENERAL(0);
    }
/**************************************************************************/

    if(cc3xxx_trnspt_cmd_if_cfg_bss_cap(RoleId, aBssCap) != CMD_STATUS_SUCCESS)  //< 0)
    {
        GTRACE(GRP_DRIVER_CC33, "Warning: failed to set bss cap");
        CME_CC3XX_PORT_PRINT_ERROR("\n\rError: failed cc3xxx_trnspt_cmd_if_cfg_bss_cap RoleId:%d",RoleId);
        ASSERT_GENERAL(0);
    }

    CME_CON_PRINT("\n\rEnable BA policy for linkId:%d",link);

    return CMD_STATUS_SUCCESS;//0;
}

#ifndef TI_STA_ONLY_BUILD
/******************************************************************************

    FUNCTION:       cc3xxx_trnspt_cmd_if_sta_add

    DESCRIPTION:    This function starts the sequence of adding a new peer to AP.
                    This API sets peer configuration on driver DB.


    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_sta_add(void *apPriv, struct hostapd_sta_add_params *apParams)
{
   //

    ti_driver_ifData_t *pDrv        = (ti_driver_ifData_t *)apPriv;
    char macStr[MAC_STR_LEN];
    uint32_t i;
    uint32_t basicRatesBM = 0;
	uint32_t supportedRatesBM = 0;
    ConfigureLink_t *pPeerCfg;
    AddPeerCmd_t *pStaParams;

    //CME_CC3XX_PORT_PRINT("\n\rcmd_if_sta_add: Add STA");
    // Sanity checks on received parameters
    if ( (NULL == pDrv) || (NULL == apParams) )
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: got NULL pointer from supplicant");
        ASSERT_GENERAL(0);//ASSERT_DRV_CC33(0);  changed
        return 0;
    }

    GET_MAC_STR(apParams->addr, macStr);

    if (MAX_NUM_BG_RATES < apParams->supp_rates_len)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Got too many supported rates %d from %s",
                                  (int) apParams->supp_rates_len, macStr);

        // Truncate number of supported rates
        apParams->supp_rates_len = MAX_NUM_BG_RATES;
    }

    // Allocate memory for ADD PEER command, shall be released after command is
    // handled by WLAN services
    // Allocated commands are kept in a linked list (pDrv->pAddStaParams) till handled in ti_driver_sta_set_flags()

    pStaParams = os_zalloc(sizeof(AddPeerCmd_t));
    if (NULL == pStaParams)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: failed to allocated memory for new peer parameters");
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR: failed to allocated memory for new peer parameters");
        return -1;
    }

    //Insert allocated command in linked list
    pStaParams->next = pDrv->pAddStaParams;
    pDrv->pAddStaParams = pStaParams;

    GTRACE(GRP_DRIVER_DEBUG, "Peer %s, Add Command pending till 'set flags', add to list.", macStr);
    //CME_CC3XX_PORT_PRINT_ERROR("\n\rPeer %s, Add Command pending till 'set flags', add to list aid:%d.", macStr, apParams->aid);

    // set MFP flag for WPA2_PLUS \ WPA3
    if(apParams->flags & WPA_STA_MFP) 
    {
        pStaParams->peerInfo.configurePeer.mfp = TRUE;
    }
    else
    {
        pStaParams->peerInfo.configurePeer.mfp = FALSE;
    }

    //
    // Keep peer parameters on the allocated command
    //
    pPeerCfg = &pStaParams->peerInfo.configurePeer;
    IRQ_UtilCopyMacAddress(apParams->addr, pPeerCfg->macAddress);
    pPeerCfg->AID = apParams->aid;
    pPeerCfg->supportedRatesBM = convertNetRatesToBitmap(apParams->supp_rates, apParams->supp_rates_len);

    // Set UAPSD parameters according to the AC info bitmap
    for (i=0 ; i< NUM_ACCESS_CATEGORIES ; ++i)
    {
        if (IS_BIT_SET(apParams->qosinfo, i))
        {
            pPeerCfg->PSDType[NUM_ACCESS_CATEGORIES - 1 - i] = PS_SCHEME_UPSD_TRIGGER;
        }
        else
        {
            pPeerCfg->PSDType[NUM_ACCESS_CATEGORIES - 1 - i] = PS_SCHEME_LEGACY;
        }
    }
    pPeerCfg->SPLen = (apParams->qosinfo >> 5) & 0x3; // SPLen is in bits 5,6

    // Note: capabitlity & listen inetrval fields are unused in MCP and here as well

    if (apParams->ht_capabilities)
    {
        // TODO 02.02.16 - HT capabilities & AMPDU params are not handled yet in links module
        // Should be completed when Michal returns.
        pPeerCfg->htCapabilities = apParams->ht_capabilities->ht_capabilities_info;
        pPeerCfg->ampduParams = apParams->ht_capabilities->a_mpdu_params;

        // Add any supported MCS0-7 rate to the supported rates bitmask
        pPeerCfg->supportedRatesBM |= apParams->ht_capabilities->supported_mcs_set[0] << RATE_INDEX_MCS0;

#define CC33XX_HT_CAP_HT_OPERATION BIT(16)

        pPeerCfg->htCapabilities |= (uint32_t)(CC33XX_HT_CAP_HT_OPERATION);
        // TODO
        // rates.h maximal defined rate is MCS7, if in the future the device
        // supports higher rates the below should be enabled.
//        pPeerCfg->supportedRatesBM |= apParams->ht_capabilities->supported_mcs_set[1] << RATE_INDEX_MCS8;
    }

    // Limit peer supported rates to the rates supported by our local AP
    GTRACE(GRP_DRIVER_CC33, "Add STA: peer supported rates 0x%x local basic rates 0x%x supported 0x%x",
                             pPeerCfg->supportedRatesBM, basicRatesBM, supportedRatesBM);

    // Get AP Supported Rates
    cfgGetRates(ROLE_AP, &basicRatesBM, &supportedRatesBM);

    //Mask With AP Supported Rates
    pPeerCfg->supportedRatesBM &= (basicRatesBM | supportedRatesBM);

    GTRACE(GRP_DRIVER_CC33, "Add STA %s, AID %d supported rates 0x%x SP length %d",
                            macStr, apParams->aid, pPeerCfg->supportedRatesBM, pPeerCfg->SPLen);

    CME_CC3XX_PORT_PRINT("\n\rrcmd_if_sta_add: Add pending STA %s, AID %d supported rates 0x%x SP length %d",
                            macStr, apParams->aid, pPeerCfg->supportedRatesBM, pPeerCfg->SPLen);

   //

    return 0;

}
#endif // TI_STA_ONLY_BUILD

#ifndef TI_STA_ONLY_BUILD
/******************************************************************************

    FUNCTION:       cc3xxx_trnspt_cmd_if_sta_remove

    DESCRIPTION:    This function is invoked by supplicant in order to remove a peer from AP.
                    This can happen in several cases:

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_sta_remove(void *apPriv, const uint8_t *apAddr)
{
   //

    ti_driver_ifData_t      *pDrv = (ti_driver_ifData_t *)apPriv;

    //CommandParamContol_t          cmd;
    CommandParamContol_t cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                retVal;
    int                     rc;
    char                    macStr[MAC_STR_LEN];

    RemovePeer_t            *cmdParams   = (RemovePeer_t*)&cmd.commandParam.param;

    AddPeerCmd_t *pStaParams;
    AddPeerCmd_t *pPrevCmd; //Previous in link list (NULL if pStaParams is first)

    uint32_t lid;

    GTRACE(GRP_WPA_SUPPLICANT, "CMD_REMOVE_PEER roleid=%d", pDrv->roleId);
    CME_CC3XX_PORT_PRINT("\n\r CMD_REMOVE_PEER  roleid=%d", pDrv->roleId);

    if (NULL == apAddr)
        return -1;

    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: NULL driver pointer");
        ASSERT_GENERAL(0);//ASSERT_DRV_CC33(0);  changed
        return -1;
    }

    GET_MAC_STR(apAddr, macStr);
    GTRACE(GRP_DRIVER_CC33, "AP is removing STA %s", macStr);

    //Check if there is a sta_add pending command for this mac address in the linked list, if yes, remove it.
    pStaParams = pDrv->pAddStaParams;
    pPrevCmd = NULL;

    while (pStaParams!=NULL)
    {
        if (IRQ_UtilCompareMacAddress (pStaParams->peerInfo.configurePeer.macAddress, apAddr))
        {
            if (pPrevCmd == NULL) //first entry on list
            {
                pDrv->pAddStaParams = pStaParams->next;
            }
            else
            {
                pPrevCmd->next = pStaParams->next;
            }
            os_free(pStaParams);

            GTRACE(GRP_DRIVER_DEBUG, "Peer %s, Add Command handled, remove from list.", macStr);
            break;
        }
        pPrevCmd = pStaParams;
        pStaParams = pStaParams->next;
    }


    lid = wlanLinks_LinkMacFind(TIWDRV_NETIF_ID_SAP, (uint8 *)apAddr);


    // Supplicant always tries to remove the STA just before sending association
    // response. If there's no valid link don't send a remove command:
    //      - not needed, as there's nothing to remove
    //      - we get an ASSERT_GENERAL as the link ID is invalid
    if (INVALID_LINK == lid)
    {
        GTRACE(GRP_DRIVER_CC33, "NOTIFY: Can't find link ID for peer %s", macStr);
        return -1;
    }
    CME_PRINT_REPORT("\n\r CMD_REMOVE_PEER :%s", macStr);

    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.nabHeader.opcode = CMD_REMOVE_PEER;
    cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd.commandParam.cmdID = CMD_REMOVE_PEER;

    cmdParams->roleID = pDrv->roleId;
    cmdParams->linkID = lid;
    cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(RemovePeer_t));

    // --------------------------
    //  Send CMD
    // --------------------------
    retVal  = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), 0);
    cmdComplete.info.status = retVal;
    if(retVal == 0)
    {
        CmeApPeerDisConnectedNotify((uint8 *)apAddr);

        udata_SetRxState(lid, LINK_STATE_CLOSED);
        udata_SetTxState(lid, LINK_STATE_CLOSED);

        //udata_SetRxBaPolicy(lid, 0);//disable BA policy
        udata_ResetLinkStats(lid);
        udata_RemoveLink(lid);

        rc = wlanLinks_RemoveLink(lid);
        if(rc < 0)
        {
            GTRACE(GRP_DRIVER_MX, "Not enable to remove link lid %d", lid);
            ASSERT_GENERAL(0);// ASSERT_GENERAL(0);//  changed to ASSERT_GENERAL(0)
        }

        rc = cmdComplete.info.status;//rc = 0;

    }
    else
    {
        GTRACE(GRP_DRIVER_MX, "Not enable to remove peer , status = ENUM(CommandStatus_e,%d)", cmdComplete.info.status);
        CME_CC3XX_PORT_PRINT_ERROR("\n\rNot enable to remove peer , status = ENUM(CommandStatus_e,%d)", cmdComplete.info.status);
        rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
    }

   //

    return rc;
}
#endif // TI_STA_ONLY_BUILD

#ifndef TI_STA_ONLY_BUILD
/******************************************************************************

    FUNCTION:       cc3xxx_trnspt_cmd_if_sta_set_flags

    DESCRIPTION:   This function kicks the operation of adding an
                   already configured STA to AP.


    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_trnspt_cmd_if_sta_set_flags(void *apPriv, const u8 *apAddr, unsigned int total_flags,
                         unsigned int flags_or, unsigned int flags_and)
{
    int                     rc = 0;
    CommandParamContol_t    cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                retVal;
    char                    macStr[MAC_STR_LEN];
    ti_driver_ifData_t      *pDrv = (ti_driver_ifData_t *)apPriv;
    AddPeerCmd_t            *pStaParams;
    AddPeerCmd_t            *pPrevCmd; //Previous in link list (NULL if pStaParams is first)
    Bool_e                  foundCmd = FALSE;
    uint32_t                uAcId;

    if (NULL == apAddr)
        return -1;

    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: NULL driver pointer");
        return -1;
    }

    GET_MAC_STR(apAddr, macStr);
    GTRACE(GRP_DRIVER_CC33, "Set STA flags: total_flags = 0x%x, flags_or = 0x%x, flags_and = 0x%x, peer %s",
                             total_flags, flags_or, flags_and, macStr);
    CME_CC3XX_PORT_PRINT("\n\rsta_set_flags: CMD_ADD_PEER total_flags = 0x%x, flags_or = 0x%x, flags_and = 0x%x, peer %s",
            total_flags, flags_or, flags_and, macStr);


    //Check if there is a sta_add pending command for this mac address in the linked list
    pStaParams = pDrv->pAddStaParams;
    pPrevCmd = NULL;


    while (pStaParams!=NULL)
    {
        if (IRQ_UtilCompareMacAddress (pStaParams->peerInfo.configurePeer.macAddress, apAddr))
        {
            foundCmd = TRUE;
            break;
        }
        pPrevCmd = pStaParams;
        pStaParams = pStaParams->next;
    }

    /* If a sta_add command is pending, send it now with the flags */
    if (foundCmd)
    {
        GTRACE(GRP_DRIVER_MX, "************** Add STA with flags **************");

        AddPeerCmd_t    *cmdParams = (AddPeerCmd_t*)&cmd.commandParam.param;
        AddPeerReturn_t *cmdReturn = (AddPeerReturn_t*)&cmdComplete.info.param;

        // Use addr field in sta_info struct to get a pointer to the container of it.
        size_t memberOffset = offsetof(struct sta_info, addr);
        struct sta_info *staInfo = (struct sta_info *)((const uint8_t *)apAddr - memberOffset);
        uint8_t wps = 0;

        // Extract WPS flag from sta_info struct in order to detect a WPS connection attempt
        if (isextWPS())
        {
            wps = (staInfo->flags & WLAN_STA_WPS) >> 12;
            GTRACE(GRP_DRIVER_DEBUG, "Peer %02x:%02x:%02x:%02x:%02x:%02x, wps connection %d",
                                    staInfo->addr[0],
                                    staInfo->addr[1],
                                    staInfo->addr[2],
                                    staInfo->addr[3],
                                    staInfo->addr[4],
                                    staInfo->addr[5],
                                    wps);
            
            // Turning off STA`s WPS flag in order to manipulate ieee802_1x EAPOLs SM
            // we don't need it to start since we wish to forward these EAPOLs to
            // an external WPS agent. We don't want to forget this flag was set, so
            // later in this function we store it on the link DB.
            staInfo->flags &= ~WLAN_STA_WPS;
        }
        //CME_CC3XX_PORT_PRINT("\n\r ************** CMD_ADD_PEER with flags (recv pending command) **************");

        // --------------------------
        //  Prepare CMD
        // --------------------------
        cmd.nabHeader.opcode = CMD_ADD_PEER;
        cmd.nabHeader.sync_pattern = HOST_SYNC_PATTERN;
        cmd.commandParam.cmdID = CMD_ADD_PEER;



        // Set local parameters
        cmdParams->peerInfo.addPeer.roleID = pDrv->roleId;
        cmdParams->peerInfo.addPeer.roleType = pDrv->roleType;
        cmdParams->peerInfo.addPeer.linkType = WLANLINK_TYPE_SPECIFIC;

        cmdParams->isConnected = ((flags_or & WPA_STA_AUTHORIZED) ? 1 : 0 );

        memcpy((void *)&cmdParams->peerInfo.configurePeer,
               (void *)&pStaParams->peerInfo.configurePeer,
               sizeof(ConfigureLink_t));

        // Set peer WMM
        cmdParams->peerInfo.configurePeer.WMM = ((total_flags & WPA_STA_WMM) ? 1 : 0);

        // --------------------------
        //  Send CMD
        // --------------------------
        cmd.nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd.commandParam.cmdID) + sizeof(ConfigureLink_t)+sizeof(AddPeerReturn_t));

        retVal  = cmd_Send((char *)&cmd,cmd.nabHeader.len, (char *)&(cmdComplete.info.param), sizeof(AddPeerReturn_t));
        cmdComplete.info.status = retVal;
        if(retVal == CMD_OK )//&& cmdComplete.info.status == CMD_STATUS_SUCCESS)
        {
            // When addStation returns FW has completed handling the command, its
            // memory can be released.
            // Remove it first from the linked list.
            if (pPrevCmd == NULL) //first entry on list
            {
                pDrv->pAddStaParams = pStaParams->next;
            }
            else
            {
                pPrevCmd->next = pStaParams->next;
            }

            os_free(pStaParams);

            // --------------------------
            //  Prepare Link and session ID
            // --------------------------
            TWlanLinkInfo *pLinkInfo = (TWlanLinkInfo *)os_malloc(sizeof(TWlanLinkInfo));

            pLinkInfo->eIfMode = TIWDRV_IF_MODE_SAP;
            pLinkInfo->uNetIfId = TIWDRV_NETIF_ID_SAP;
            pLinkInfo->eType = WLANLINK_TYPE_SPECIFIC;


            //For AP
            // wps parameter is sent in order to store the WPS flag in wps connection attempt
            if(wlanLinks_AddLink(pLinkInfo, (uint32_t)cmdReturn->linkId, cmdReturn->sessionId, cmdParams->peerInfo.configurePeer.macAddress, wps))
            {
                os_free(pLinkInfo);
                ASSERT_GENERAL(0);
                return NOK;
            }

            /* Add the new link in  Rx and Tx */
            udata_AddLink(cmdReturn->linkId,//OSPREY_MX-10
                          cmdReturn->linkId,
                          (linkType_e)pLinkInfo->eType,
                          (tiwdrv_if_mode_e)pLinkInfo->eIfMode,
                          (RoleID_t)pDrv->roleId,
                          pLinkInfo->uNetIfId,
                          0/*MGMT_RATE_POLICY_INDEX(pRoleSta->pRoleDesc->uActiveIfId)*/,
                          0/*DATA_RATE_POLICY_BASE_INDEX(pRoleSta->pRoleDesc->uActiveIfId)*/);

            os_free(pLinkInfo);

            /* Update the link Tx Session ID to UDATA */
            udata_SetTxSessionId(cmdReturn->linkId, cmdReturn->sessionId);

            udata_SetPeerParams(cmdReturn->linkId, apAddr, cmdParams->peerInfo.configurePeer.WMM);

            //Set Rx State according to station authorization
            if (total_flags & (WPA_STA_AUTHENTICATED | WPA_STA_ASSOCIATED))
            {
                if (flags_or & WPA_STA_AUTHORIZED)
                {
                    //Station is associated and authorized
                    udata_SetRxState(cmdReturn->linkId, LINK_STATE_OPEN);
                }
                else
                {
                    //Station is associated but not authorized yet
                    udata_SetRxState(cmdReturn->linkId, LINK_STATE_EAPOL);
                }
            }
            //Set Tx State
            udata_SetTxState(cmdReturn->linkId, LINK_STATE_OPEN);

            // If ap set pmf enabled based on peer mfp config attach to linkId
            if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
            {
                Bool_e isPmfEnable = FALSE;

                if (pStaParams->peerInfo.configurePeer.mfp)
                {
                        isPmfEnable = TRUE;
                }
                udata_SetMgmtEncryption(cmdReturn->linkId, isPmfEnable);
            }

            /* By default set all ACs of both links as not required for admission control (updated after connection) */
            for (uAcId = 0; uAcId < MAX_NUM_OF_AC; uAcId++)
            {
                udata_SetAdmissionStatus(cmdReturn->linkId, uAcId, ADMISSION_NOT_REQUIRED, AC_ADMITTED);
            }

            udata_SetRxBaPolicy(cmdReturn->linkId, 1);//enable BA policy

            CmeApPeerConnectedNotify(cmdParams->peerInfo.configurePeer.macAddress,
                                     cmdParams->peerInfo.configurePeer.AID, wps);

            rc = cmdComplete.info.status; //rc = 0;

            GTRACE(GRP_DRIVER_DEBUG, "Peer %s link id %d session id %d , Add Command handled, remove from list.",
                   macStr,
                   cmdReturn->linkId,
                   cmdReturn->sessionId);

            CME_PRINT_REPORT("\n\rPeer was added successfully macstr: %s link id %d session id %d.\n\r",
                   macStr,
                   cmdReturn->linkId,
                   cmdReturn->sessionId);


        }
        else
        {
            GTRACE(GRP_DRIVER_MX, "Not enable to add peer status = ENUM(CommandStatus_e,%d)",
                   cmdComplete.info.status);
            CME_CC3XX_PORT_PRINT ("\n\rEROR!!! Not enable to add peer status = ENUM(CommandStatus_e,%d)",
                            cmdComplete.info.status);
            rc =  CMD_GENERAL_STATUS_ERROR;//rc = -1;
        }

    }
    else
    {
        uint32_t lid;
        LinkState_e connectionState;
        Bool32 sendStateChanged = 0;

        lid = wlanLinks_LinkMacFind(TIWDRV_NETIF_ID_SAP, (uint8 *)apAddr);

        if (INVALID_LINK == lid)
        {
            return -1;
        }

        if (flags_or & WPA_STA_AUTHORIZED) //Turn on authorized
        {
            //CME_CC3XX_PORT_PRINT("\n\r update peer, peer: %s  link id:%d WPA_STA_AUTHORIZED *********",macStr,lid);
            GTRACE(GRP_DRIVER_MX, "update peer, peer: %s link id:%d WPA_STA_AUTHORIZED ",macStr, lid);
            udata_SetRxState(lid, LINK_STATE_OPEN);
            connectionState = LINK_STATE_CONNECTED;
            sendStateChanged = TRUE;
        }

        if (!(flags_and & WPA_STA_AUTHORIZED)) //Turn off authorized
        {
            if ((total_flags & WPA_STA_ASSOCIATED) || (total_flags & WPA_STA_AUTHENTICATED))
            {
                connectionState = LINK_STATE_CONNECTED;
            }
            else
            {
                connectionState = LINK_STATE_DISCONNECTED;
            }
            sendStateChanged = TRUE;

        }


        if (sendStateChanged)
        {
            /* Set peer's connection state in FW */
            pDrv->ops->set_peer_state(lid, (uint8_t)connectionState, (total_flags & WPA_STA_WMM) );
        }
    }

    return rc;

}
#endif // TI_STA_ONLY_BUILD

void WlanEventHandler(void *pWlanFwEvent)
{
    if(!pWlanFwEvent)
    {
        CME_CC3XX_PORT_PRINT_ERROR("\n\rERROR [WLAN FW EVENT HANDLER] error pWlanFwEvent is NULL\n\r");
        return;
    }

    cc3xxx_trnspt_cmd_if_event_handle((EventMailBox_t*)pWlanFwEvent);
}

int cc3xxx_trnspt_cmd_set_ps(RoleID_t roleId, uint8_t power)
{
    int ret;
    cmd_debug_psm_dbg_t cmdPsmCfg;
    
    cmdPsmCfg.forcePsmParams.paramIndex = 4;
    cmdPsmCfg.forcePsmParams.paramValue = power;

    CME_CON_PRINT("\n\rSet PS Mode %d\n\r", power);

    ret = WLSendFW_DebugCommand(FORCE_PS_CFG,
                                &cmdPsmCfg,
                                sizeof(cmd_debug_psm_dbg_t),
                                NULL,
                                0);
    return ret;
}
// ============================================================================
//     SetDefault
// ============================================================================
int cc3xxx_config_mem_map();
/******************************************************************************

    FUNCTION:       cc3xxx_set_defaults

    DESCRIPTION:    init defaults

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int32_t cc3xxx_set_defaults()
{
    int ret;
    ret = cc3xxx_config_mem_map();

    CME_CC3XX_PORT_PRINT("\n\rset_defaults configuration DONE! status = %d\n", ret);
    return ret;
}

/******************************************************************************

    FUNCTION:       cc3xxx_config_mem_map

    DESCRIPTION:    Send ACX_MEM_MAP

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int cc3xxx_config_mem_map()
{
#if 0
    MemoryMap_t             tMemMap;
#endif
    int ret = 0;

#if 0
    TDmaParams     pDmaParams;

    pDmaParams.NumTxBlocks = 44;//tMemMap.numTxMemBlks;
    pDmaParams.uHostTxDescriptors = NUM_TX_DESCRIPTORS;

    txHwQueue_SetHwInfo(&pDmaParams);
#endif
    return ret;
}

/* ----------------------------------------------------------------------------
 cc33xx_driver_wps_success
     This function notifies that WPS was successfull

 Parameters:    struct wpa_supplicant *wpa_s

 Return code:   0
---------------------------------------------------------------------------- */
void cc33xx_driver_wps_success(struct wpa_supplicant *wpa_s)
{
    GTRACE(GRP_DRIVER_CC33, "CC33 Driver - WPS event Success");
    CME_ClearWPSAdHocConnection();
    gWPSfirstDisconnect_ull = TRUE; //Disregard the next supplicant disconnect event since it is genarated internaly by the supplicant which is about to perform fast connect with the new credentials.
}

/* ----------------------------------------------------------------------------
 cc33xx_driver_wps_fail
     This function notifies that WPS process failed

 Parameters:    struct wpa_supplicant *wpa_s

 Return code:   0
---------------------------------------------------------------------------- */
void cc33xx_driver_wps_fail(struct wpa_supplicant *wpa_s)
{
    GTRACE(GRP_DRIVER_CC33, "CC33 Driver - WPS event Fail");
    //CME_ClearWPSAdHocConnection();
}

/* ----------------------------------------------------------------------------
 cc33xx_driver_wps_cleared
     This function notifies that WPS process was cleared, either due tue timeout or cancelletion

 Parameters:    struct wpa_supplicant *wpa_s

 Return code:   0
---------------------------------------------------------------------------- */
void cc33xx_driver_wps_cleared(struct wpa_supplicant *wpa_s)
{
    GTRACE(GRP_DRIVER_CC33, "CC33 Driver - WPS Cleared");

    CME_ClearWPSAdHocConnection();
}

/* ----------------------------------------------------------------------------
 cc33xx_driver_wps_credential
     This function pass the credentials of the new network after a successfull WPS negotiation.
     Assumption: This function is called after the supplicant processed internally the credentials so we have the parameters
                 available in wpa_s->current_ssid (used in cmeAddWpsCredentials2PreferredNetworks).

 Parameters:    struct wpa_supplicant *wpa_s
                const struct wps_credential *cred

 Return code:   0
---------------------------------------------------------------------------- */
void cc33xx_driver_wps_credential(struct wpa_supplicant *wpa_s, const struct wps_credential *cred)
{
    int16_t status;

    GTRACE(GRP_DRIVER_CC33, "CC33 Driver - WPS Credentials received, auth type: %d, enc type: %d", cred->auth_type, cred->encr_type);

    status = cmeAddWpsCredentials2PreferredNetworks(wpa_s, cred);

    if (status >=0 )
    {
        GTRACE(GRP_DRIVER_CC33, "CC33 Driver - WPS Credentials, Add profile success, index = %d", status);
        gCmeLastWlanProfileIdx = status;
    }
    else
    {
        GTRACE(GRP_DRIVER_CC33, "CC33 Driver - WPS Credentials, Add profile failed, status = %d", status);
    }
}


// ============================================================================
//     cc3xxx_trnspt_cmd_if_ops
// ============================================================================
const struct drv_cmd_ops cc3xxx_trnspt_cmd_if_ops = {

    // Role related APIs
    .enable_role                 = cc3xxx_trnspt_cmd_if_enable_role,
    .disable_role                = cc3xxx_trnspt_cmd_if_disable_role,
    .start_role                  = cc3xxx_trnspt_cmd_if_start_role,
    .stop_role                   = cc3xxx_trnspt_cmd_if_stop_role,
    .change_type                 = cc3xxx_trnspt_cmd_if_change_role_type,

    // Scan related APIs
    .site_survey                 = cc3xxx_trnspt_cmd_if_site_survey,
    .one_shot                    = cc3xxx_trnspt_cmd_if_one_shot_scan,
    .sched_scan                  = cc3xxx_trnspt_cmd_if_sched_scan,
    .send_scan_stop              = cc3xxx_trnspt_cmd_if_send_stop_scan,
    .scan_tag                    = cc3xxx_trnspt_cmd_if_check_scan_tagged_frame,

    .set_key                     = cc3xxx_trnspt_cmd_if_set_key,

    .remain_on_channel          = cc3xxx_trnspt_cmd_if_roc,
    .cancel_remain_on_channel   = cc3xxx_trnspt_cmd_if_cancel_roc,

    .set_peer_state             = cc3xxx_trnspt_cmd_if_set_peer_state,
    .assoc_peer                 = cc3xxx_trnspt_cmd_if_config_assoc_peer,
    .tx_param                   = cc3xxx_trnspt_cmd_if_config_tx_param,

    // AP related APIs
#ifndef TI_STA_ONLY_BUILD
    .set_ap_template            = cc3xxx_trnspt_cmd_if_set_beacon_info,
    .sta_add                    = cc3xxx_trnspt_cmd_if_sta_add,
    .sta_remove                 = cc3xxx_trnspt_cmd_if_sta_remove,
    .sta_set_flags              = cc3xxx_trnspt_cmd_if_sta_set_flags,
#endif

    .set_ps                     = cc3xxx_trnspt_cmd_set_ps,

};
