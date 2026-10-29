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
#if 0
#include "common.h"
#include "l2_cfg.h"
#include "utils/eloop.h"
#include "utils/common.h"
#include "common/ieee802_11_defs.h"
#include "common/defs.h"

#include "drivers/driver.h"

#include "ap/hostapd.h"
#include "ap/ap_config.h"
#include "ap/ieee802_1x.h"
#include "ap/ieee802_11.h"
#include "ap/sta_info.h"
#include "ap/hw_features.h"
#include "ap/beacon.h"
#include "ap/tkip_countermeasures.h"
#include "../../wpa_supplicant/config.h"
#include "../../wpa_supplicant/wpa_supplicant_i.h"
#include "wps/wps_i.h"
#include "p2p/p2p_i.h"
#include "scan.h"


#include "cme_supplicant_api.h"
#include "cme_dispatcher_api.h"
#include "cme_internal_api.h"
#include "cme_fw_api.h"
#include "cme_defs.h"
#include "802_11defs.h"


#include "drv_ti_internal.h"
#include "fw_utils.h"

#include "mpdu.h"
#include "80211_utils.h"

#include "driver_osprey_mx.h"
#include "driver_osprey_mx_scan.h"
#include "regulatory_domain.h"

#include "cme_internal_api.h"


#include "cc3xxx_public_commands.h"
#include "osi_type.h"

// ============================================================================
//      Modules private definitions
// ============================================================================

// ============================================================================
//      Modules globals
// ============================================================================

extern  cmeScanSharedInfo_t*    scanResultTable_GetCmeScanDbPointer();
extern  Bool_e                  scanResultTable_NotifyScanPriodStart(uint8_t  scanTag);
extern  OsiSyncObj_t            ScanResultTableSyncObj_ull;

// ============================================================================
//		Local Functions declarations
// ============================================================================

int8_t mx_driver_send_ies(uint32_t roleID,
                        EScanRequestType scanType,
                        struct wpa_driver_scan_params *apSuppParams,
                        RoleType_e roleType);

int8_t mx_driver_send_scan_stop_cmd (uint32_t roleID,
                                  EScanRequestType scanRequestType,
                                  Bool_e isET);

void mx_driver_get_mac_addr(uint8_t *macAddr, RoleType_e aRoleType);

/* Roles command */
int8_t mx_driver_enable_role   (ti_driver_ifData_t *apDrv, RoleType_e aRoleType);
int8_t mx_driver_disable_role  (ti_driver_ifData_t *apDrv);
int8_t mx_driver_stop_role     (ti_driver_ifData_t *apDrv);
int8_t mx_driver_start_role    (RoleStartParameters_t *pParam, void *pReturnParam);
int8_t mx_driver_set_link_connection_state (uint8_t lid, LinkState_e linkConnectionState);
// ============================================================================
//      Supplicant Functions declarations
// ============================================================================

/* Scan Functions */
int8_t mx_driver_one_shot_scan(void *apPriv,
                                       struct wpa_driver_scan_params *apParams);
int8_t mx_driver_sched_scan(void *apPriv,
                                    struct wpa_driver_scan_params *apParams);

int8_t mx_driver_site_survey_scan(uint8_t roleID);

int8_t mx_driver_stop_sched_scan(void *apPriv);

// ============================================================================
//      Local services APIs
// ============================================================================

/******************************************************************************

    FUNCTION:		mx_driver_get_mac_addr

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Set the MAC address to the role type
                    First get the MAC address from FLASH if saved
                    (override), if not saved hard-coded MAC address set

    CALLER:         mx_driver_if_init

    PARAMETERS:     macAddr - pointer MAC address
                    aRoleType - type of role that should be enabled

    RETURNS:        NONE
******************************************************************************/
void mx_driver_get_mac_addr(uint8_t *macAddr, RoleType_e aRoleType)
{
    GTRACE(GRP_DRIVER_MX, "mx_driver_set_mac_addr: Try get the MAC address from flash ENUM(RoleType_e,%d)", aRoleType);

    /* read mac address from flash - g_DeviceParams_ull */
        // TODO: need to implement
    LoadDeviceParams_GetParamsFromFlash(TRUE, FALSE);
    //override the mac address
    if (ROLE_IS_TYPE_STA_BASED(aRoleType))
    {

        IRQ_UtilCopyMacAddress((uint8_t *)g_DeviceParams_ull.gStaFlashMacAddress, macAddr);
    }
    else if (ROLE_IS_TYPE_AP_BASED(aRoleType))
    {
        IRQ_UtilCopyMacAddress((uint8_t *)g_DeviceParams_ull.gApFlashMacAddress, macAddr);

    }
    else if (ROLE_DEVICE == aRoleType)
    {
        IRQ_UtilCopyMacAddress((uint8_t *)g_DeviceParams_ull.gDeviceFlashMacAddress, macAddr);
    }
    else if (ROLE_TRANSCEIVER == aRoleType)
    {
        IRQ_UtilCopyMacAddress((uint8_t *)g_DeviceParams_ull.gTransceiverFlashMacAddress, macAddr);
    }

    // Check if MAC address is not zero. Otherwise allocate.
    if (IRQ_UtilIsZeroMacAddress(macAddr))
    {
        // Allocate Mac address
        Roles_allocateMacAddress(aRoleType, macAddr);
        GTRACE(GRP_DRIVER_MX, "DEVICE_PARAMS: MAC address is Zero, take the hard-coded MAC address 0x%x 0x%x 0x%x",
               macAddr[0],
               macAddr[1],
               macAddr[2]);

    }
    else
    {
        GTRACE(GRP_DRIVER_MX, "DEVICE_PARAMS: MAC address is not Zero, take the flash 0x%x 0x%x 0x%x",
               macAddr[0],
               macAddr[1],
               macAddr[2]);
    }
}
// ============================================================================
//      Set APIs
// ============================================================================
/******************************************************************************

    FUNCTION:       mx_driver_set_keys

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    This command set connection keys

    CALLER:         setKey()
                    setDefaultKeyId()

    PARAMETERS:     pParam - pointer to set key structure param

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t mx_driver_set_keys (SetKey_t *pParam)
{
    CommandParam_t          cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                  retVal;
    int8_t                    rc;

    GTRACE(GRP_DRIVER_MX,"Setting security keys: link ID %d, type ENUM(LidKeyType_e, %d), cipher suite ENUM(CipherSuite_e,%d), key ID %d, action ENUM(KeyAction_e,%d)",
                          pParam->lid,
                          pParam->lidKeyType,
                          pParam->cipher_type,
                          pParam->keyId,
                          pParam->action);

    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID = CMD_SET_KEYS;

    memcpy(&cmd.param, pParam, sizeof(SetKey_t));

    // --------------------------
    //  Send CMD
    // --------------------------
    // TODO Send command handler

    if(retVal > 0 && cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
        rc = 0;

    }
    else
    {
        GTRACE(GRP_DRIVER_MX, "Not enable to set keys, status = ENUM(CommandStatus_e,%d)", cmdComplete.info.status);
        rc = -1;
    }

    return rc;
}
/******************************************************************************

    FUNCTION:       mx_driver_set_link_connection_state

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    This command set link connection state

    CALLER:         caller

    PARAMETERS:     lid                 - link ID
                    linkConnectionState - requested link connection state

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t mx_driver_set_link_connection_state (uint8_t lid,
                                          LinkState_e linkConnectionState)
{
    CommandParam_t          cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                  retVal;
    int8_t                    rc;

    SetLinkConnectionState_t *cmdParams = (SetLinkConnectionState_t*)&cmd.param;

    GTRACE(GRP_DRIVER_MX, "set link connection state ENUM(LinkConnectionState_e,%d)", linkConnectionState);

    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID                   = CMD_SET_LINK_CONNECTION_STATE;
    cmdParams->connectionState  = (uint8_t)linkConnectionState;
    cmdParams->flid             = lid;

    // --------------------------
    //  Send CMD
    // --------------------------
    // TODO Send command handler

    if(retVal > 0 && cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
        rc = 0;

    }
    else
    {
        GTRACE(GRP_DRIVER_MX, "Not enable to set link connection, status = ENUM(CommandStatus_e,%d)", cmdComplete.info.status);
        rc = -1;
    }

    return rc;
}

/******************************************************************************

    FUNCTION:		mx_driver_set_beacon_info

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Set beacon information for AP role

    CALLER:         mx_driver_set_ap

    PARAMETERS:     aRoleId      - role ID
                    beacon       - pointer for beacon template

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t mx_driver_set_beacon_info(uint32_t aRoleId,
                                   struct wpa_driver_ap_params *beacon)
{
    CommandParam_t          cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                  retVal = 0;
    int8_t                    rc     = 0;

    SetBeaconInfo_t  *cmdParams = (SetBeaconInfo_t*)&cmd.param;

    GTRACE(GRP_DRIVER_MX, "Set beacon template roleID %d", aRoleId);

    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID           = CMD_AP_SET_BEACON_INFO;
    cmdParams->roleID   = aRoleId;


    cmdParams->beacon_len = fillBeaconTemplate(beacon, cmdParams->beacon);

    // --------------------------
    //  Send CMD
    // --------------------------
    // TODO Send command handler

    if(retVal > 0 && cmdComplete.info.status == CMD_STATUS_SUCCESS)
   {
       rc = 0;

   }
   else
   {
       GTRACE(GRP_DRIVER_MX, "Not enable to set beacon template, status = ENUM(CommandStatus_e,%d)", cmdComplete.info.status);
       rc = -1;
   }

   return rc;
}

// ============================================================================
//      Roles APIs
// ============================================================================

/******************************************************************************

    FUNCTION:		mx_driver_enable_role

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Send enable role command to FW, wait for FW to
                    allocate a role and set role ID on driver DB.
                    This role ID shall be used for any further access to
                    this role.

    CALLER:         mx_driver_if_init

    PARAMETERS:     apPriv - IN/OUT pointer to the driver DB
                    aRoleType - type of role that should be enabled

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t mx_driver_enable_role (ti_driver_ifData_t *apDrv, RoleType_e aRoleType)
{

    CommandParam_t          cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                  retVal = 0;
    int8_t                    rc     = 0;

    RoleEnableParameters_t  *cmdParams = (RoleEnableParameters_t*)&cmd.param;
    RoleEnableReturn_t      *cmdReturn = (RoleEnableReturn_t*)&cmdComplete.info.param;

    GTRACE(GRP_WPA_SUPPLICANT, "Enable role ENUM(RoleType_e, %d) ", aRoleType);
#ifdef CC33XX_DRIVER_DEBUG
    // Reset debug info
    if (ROLE_IS_TYPE_STA_BASED(aRoleType))
    {
        memset(&gSuppDrvDebugInfo_ull.sta, 0, sizeof(cc33drv_staDebugInfo_t));
        gSuppDrvDebugInfo_ull.sta.gForceDisconnectState = 100;
    }
    else if (ROLE_IS_TYPE_AP_BASED(aRoleType))
    {
        memset(&gSuppDrvDebugInfo_ull.ap, 0, sizeof(cc33drv_apDebugInfo_t));
    }
#endif
    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID       = CMD_ROLE_ENABLE;
    cmdParams->roleType = aRoleType;
    mx_driver_get_mac_addr((uint8_t *)cmdParams->macAddress, aRoleType);

    // --------------------------
    //  Send CMD
    // --------------------------
    // TODO Send command handler


    if(retVal > 0 && cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {

        // Mark role wasn't started yet
        apDrv->roleStarted = FALSE;

        // Set received parameters on role DB
        GTRACE(GRP_WPA_SUPPLICANT, "Enable role allocated role ID %d", cmdReturn->roleID);
        apDrv->roleId = cmdReturn->roleID;
        // copy the MAC address to the driver param
        IRQ_UtilCopyMacAddress(cmdParams->macAddress, apDrv->macAddr);

    }
    else
    {
        GTRACE(GRP_WPA_SUPPLICANT, "Failed to allocated role ID ret = %d status = ENUM(CommandStatus_e, %d)",
               retVal,
               cmdComplete.info.status);
        rc = -1;
    }

    return rc;
}
/******************************************************************************

    FUNCTION:		mx_driver_disable_role

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Send disable role command to FW, wait for FW to
                    complete the operation.

    CALLER:         mx_driver_deinit

    PARAMETERS:     apDrv - IN/OUT pointer to the driver DB

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t mx_driver_disable_role (ti_driver_ifData_t *apDrv)
{
    CommandParam_t          cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                  retVal;
    int8_t                    rc;
    RoleDisableParameters_t *cmdParams = (RoleDisableParameters_t*)&cmd.param;

    GTRACE(GRP_WPA_SUPPLICANT, "Disable role ");
    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID           = CMD_ROLE_DISABLE;
    cmdParams->roleID   = apDrv->roleId;

    // --------------------------
    //  Send CMD
    // --------------------------
    // TODO Send command handler

    if(retVal > 0 && cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
        rc = 0;
    }
    else
    {
        GTRACE(GRP_DRIVER_MX, "Not enable to disable role id %d status = ENUM(CommandStatus_e,%d)",
                apDrv->roleId,
                cmdComplete.info.status);
        rc = -1;
    }

    return rc;
}

/******************************************************************************

    FUNCTION:		mx_driver_stop_role

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    This command stops a (previously started) role,
                    so the F/W can on longer select to activate it.

    CALLER:         caller

    PARAMETERS:     apDrv - IN/OUT pointer to the driver DB

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t mx_driver_stop_role (ti_driver_ifData_t *apDrv)
{
    CommandParam_t          cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                  retVal;
    int8_t                    rc;

    RoleStopParameters_t *cmdParams = (RoleStopParameters_t*)&cmd.param;

    GTRACE(GRP_DRIVER_MX, "Stop role id %d", apDrv->roleId);

    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID           = CMD_ROLE_STOP;
    cmdParams->roleID   = apDrv->roleId;

    // --------------------------
    //  Send CMD
    // --------------------------
    // TODO Send command handler

    if(retVal > 0 && cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
        rc = 0;
        // Mark role was stopped (should be used to avoid restarting an active role)
        apDrv->roleStarted = FALSE;
    }
    else
    {
        GTRACE(GRP_DRIVER_MX, "Not enable to stop role id %d status = ENUM(CommandStatus_e,%d)",
                apDrv->roleId,
                cmdComplete.info.status);
        rc = -1;
    }

    return rc;
}

/******************************************************************************

    FUNCTION:		mx_driver_start_role

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    This command stops a (previously started) role,
                    so the F/W can on longer select to activate it.

    CALLER:         caller

    PARAMETERS:     pParam - pointer to Role Start parameters
                    pRetunParam - pointer to Role Start return parameters

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t mx_driver_start_role (RoleStartParameters_t *pParam, void *pReturnParam)
{
    CommandParam_t          cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                  retVal;
    int8_t                    rc = 0;


    GTRACE(GRP_DRIVER_MX, "Start role ENUM(RoleType_e,%d)", pParam->roleType);

    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID                 = CMD_ROLE_START;

    memcpy(cmd.param, pParam, sizeof(RoleStartParameters_t));

    // --------------------------
    //  Send CMD
    // --------------------------
    // TODO Send command handler

    if(retVal > 0 && cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
        if(ROLE_IS_TYPE_STA_BASED(pParam->roleType))
        {
            memcpy(pReturnParam, cmdComplete.info.param, sizeof(RoleStartStaBasedReturn_t));
        }
        else if(ROLE_IS_TYPE_AP_BASED(pParam->roleType))
        {
            memcpy(pReturnParam, cmdComplete.info.param, sizeof(RoleStartApBasedReturn_t));
        }
        rc = 0;
    }
    else
    {
        GTRACE(GRP_DRIVER_MX, "Not enable to start role ENUM(RoleType_e,%d), status = ENUM(CommandStatus_e,%d)",
               pParam->roleType,
               cmdComplete.info.status);
        rc = -1;
    }
    return rc;
}
/******************************************************************************/
// ============================================================================
//      Configure APIs
// ============================================================================
/******************************************************************************

    FUNCTION:		mx_driver_cfg

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Firmware configuration command

    PARAMETERS:     pBuf  - pointer to configuration param
                    cfgID - command configuration ID
                    len   - command lengt

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t  mx_driver_cfg (uint8_t *pBuf, Cfg_e cfgID, size_t len)
{
    CommandParam_t          cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                  retVal;
    int8_t                    rc = 0;

    Cfg_t                   *cmdParams   = (Cfg_t *)&cmd.param;

    GTRACE(GRP_DRIVER_MX, "Command Configure ENUM(Cfg_e,%d)", cfgID);
    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID                 = CMD_CONFIGURE;
    cmdParams->id             = cfgID;
    cmdParams->length         = len;

    memcpy(&cmdParams->ex, pBuf, len);


    // --------------------------
    //  Send CMD
    // --------------------------
    // TODO Send command handler

    if(retVal > 0 && cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
        rc = 0;
    }
    else
    {
        GTRACE(GRP_DRIVER_MX, "Not enable to ENUM(Cfg_e,%d), status = ENUM(CommandStatus_e,%d)",
                       cfgID,
                       cmdComplete.info.status);
        rc = -1;
    }
    return rc;

}
/******************************************************************************

    FUNCTION:       mx_driver_cfg_erp_protection

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    Configure ERP Protection Mode for an associated STA,
                    handled by the Driver

    PARAMETERS:     roleID  - role ID
                    erpProtectionEnabled - ERP Protection mode

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t  mx_driver_cfg_erp_protection (RoleID_t roleID, Bool_e erpProtectionEnabled)
{
    CtsProtectionCfg_t param;
    int8_t retVal;
    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID               = roleID;
    param.erpProtectionEnabled = erpProtectionEnabled;

    retVal = mx_driver_cfg((uint8*)&param, CTS_PROTECTION_CFG, sizeof(CtsProtectionCfg_t));

    return retVal;
}

/******************************************************************************

    FUNCTION:       mx_driver_cfg_tx_param

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    Configure TX parameters

    PARAMETERS:     roleID       - role ID
                    pParamAc     - pointer to AC param
                    psScheme     - ps scheme
                    isMuEdca     - is MU EDCA configured
                    pParamMuEdca - pointer to MU EDCA param


    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t  mx_driver_cfg_tx_param (RoleID_t roleID,
                              AcCfg_t *pParamAc,
                              PSScheme_e psScheme,
                              Bool_e isMuEdca,
                              heMuEdcaAcParams_t *pParamMuEdca,
                              uint8_t currAc)
{
    int8_t retVal;
    TxParamCfg_t  param;

    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID   = roleID;
    param.psScheme = psScheme;
    param.isMuEdca = isMuEdca;


    param.ac = currAc;

    param.aifsn = pParamAc->aifsn;
    param.acm   = pParamAc->acm;
    param.cwMax = pParamAc->cwMax;
    param.cwMin = pParamAc->cwMin;
    param.txopLimit = pParamAc->txopLimit;

    GTRACE(GRP_DRIVER_MX, "TX param: ac %d, aifsn %d, acm %d, cwMax %d, cwMin %d, tx op %d",
                           param.ac,
                           param.aifsn,
                           param.acm,
                           param.cwMax,
                           param.cwMin,
                           param.txopLimit);
    // set MU EDCA
    if(FALSE != param.isMuEdca)
    {
        param.muEdca.aifs           = pParamMuEdca->_byte[0];
        param.muEdca.ecw_min_max    = pParamMuEdca->_byte[1];
        param.muEdca.mu_edca_timer  = pParamMuEdca->_byte[2];
    }


    retVal = mx_driver_cfg((uint8*)&param, TX_PARAMS_CFG, sizeof(TxParamCfg_t));


    return retVal;
}
/******************************************************************************

    FUNCTION:		mx_driver_cfg_assoc_info

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Configuration for post association

    CALLER:         caller

    PARAMETERS:     roleID - role id
                    aid    - aid value, as received in the association
                    wmeEnabled - Defines if wmm is enabled

    RETURNS:        return

******************************************************************************/
int8_t mx_driver_cfg_assoc_info (RoleID_t roleID, uint16_t aid, Bool_e wmeEnabled)
{
    int8_t retVal;

    AssocInfoCfg_t  param;
    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID = roleID;
    param.aid    = aid;
    param.wmeEnabled = wmeEnabled;

    retVal = mx_driver_cfg((uint8*)&param, ASSOC_INFO_CFG, sizeof(AssocInfoCfg_t));

    return retVal;
}

/******************************************************************************

    FUNCTION:		mx_driver_cfg_peer_cap

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Configures HT/HE peer capabilities

    CALLER:         caller

    PARAMETERS:     roleID - role id
                    pParam - pointer to peer capabilities
                    localSupportedRates - local supported rates

    RETURNS:        return

******************************************************************************/
int8_t mx_driver_cfg_peer_cap (RoleID_t roleID,
                             PeerCap_t *pParam,
                             uint32_t localSupportedRates)
{
    int8_t retVal;

    PeerCapCfg_t param;
    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID = roleID;
    param.supportedRatesBM = localSupportedRates;

    os_memcpy(&param.peerCap, pParam, sizeof(PeerCap_t));

    retVal = mx_driver_cfg((uint8*)&param, PEER_CAP_CFG, sizeof(PeerCapCfg_t));

    return retVal;
}

/******************************************************************************

    FUNCTION:       mx_driver_cfg_bss_cap

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    Configures HT/HE bss capabilities

    CALLER:         caller

    PARAMETERS:     roleID - role id
                    pParam - pointer to bss capbilities

    RETURNS:        return

******************************************************************************/
int8_t mx_driver_cfg_bss_cap (RoleID_t roleID, BssCap_t *pParam)
{
    int8_t retVal;

    BssOperationCfg_t param;
    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID = roleID;

    os_memcpy(&param.BssCap, pParam, sizeof(BssCap_t));

    retVal = mx_driver_cfg((uint8*)&param, BSS_OPERATION_CFG, sizeof(BssOperationCfg_t));

    return retVal;
}

/******************************************************************************

    FUNCTION:       mx_driver_cfg_slot_time

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    Set slot time

    CALLER:         caller

    PARAMETERS:     roleID - role id
                    slotTime - slotTime

    RETURNS:        return

******************************************************************************/
int8_t mx_driver_cfg_slot_time (RoleID_t roleID, SlotTime_e slotTime)
{
    int8_t retVal;

    SlotTimeCfg_t param;
    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID = roleID;

    param.slotTime = slotTime;

    retVal = mx_driver_cfg((uint8*)&param, SLOT_CFG, sizeof(SlotTimeCfg_t));

    return retVal;
}

/******************************************************************************

    FUNCTION:       mx_driver_cfg_preamble

    PROTOTYPE:      driver_osprey_mx

    DESCRIPTION:    Configured pramble

    CALLER:         caller

    PARAMETERS:     roleID - role id
                    shortBPreambleSupported - is short preamble supported

    RETURNS:        return

******************************************************************************/
int8_t mx_driver_cfg_preamble (RoleID_t roleID, Bool_e shortBPreambleSupported)
{
    int8_t retVal;

    PreambleTypeCfg_t param;
    // --------------------------
    //  Prepare param
    // --------------------------
    param.roleID = roleID;

    param.shortBPreambleSupported = shortBPreambleSupported;

    retVal = mx_driver_cfg((uint8*)&param, PREAMBLE_TYPE_CFG, sizeof(PreambleTypeCfg_t));

    return retVal;
}
/******************************************************************************

    FUNCTION:		mx_driver_send_scan_stop_cmd

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Send the CMD_STOP_SCAN

    CALLER:         mx_driver_stop_sched_scan

    PARAMETERS:     roleID - role ID
                    scanRequestType - scan request type to stop
                    isET - it is stop by early termination

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t mx_driver_send_scan_stop_cmd (uint32_t roleID,
                                   EScanRequestType scanRequestType,
                                   Bool_e isET)
{

    CommandParam_t          cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                  retVal;
    ScanStopCmdParam_t      *cmdParams = (ScanStopCmdParam_t*)&cmd.param;


    GTRACE(GRP_DRIVER_MX, "Scan stop cmd: role %d, scan type: ENUM(EScanRequestType,%d) is ET %d",
           roleID,
           scanRequestType,
           isET);


    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID = CMD_STOP_SCAN;
    cmdParams->roleId = roleID;
    cmdParams->scanRequestType = scanRequestType;
    cmdParams->isET = isET;

    // --------------------------
    //  Send CMD
    // --------------------------
    // TODO Send command handler

    if(retVal != 0 || cmdComplete.info.status != CMD_STATUS_SUCCESS)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed stop scan status ENUM(CommandStatus_e,%d)",
                                           cmdComplete.info.status);
        return -1;
    }

    return 0;


}

/******************************************************************************

    FUNCTION:		mx_driver_send_ies

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    This function set the Info elements data for probe req

    CALLER:         mx_driver_one_shot_scan | mx_driver_sched_scan

    PARAMETERS:     roleID - role ID
                    scanType - scan type
                    apSuppParams - Pointer to supplicant parameters
                    This parameters contain the extra info elements
                    roleType - role Type

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t mx_driver_send_ies(uint32_t roleID,
                        EScanRequestType scanType,
                        struct wpa_driver_scan_params *apSuppParams,
                        RoleType_e roleType)
{
    IesScanProbeReq_t   *iesProbeReq;
    CommandParam_t       cmd;
    CommandComplete_t    cmdComplete;
    uint16_t               retVal;
    uint16_t               size = 0;
    dot11_RATES_t       *pDot11Rates;
    uint32_t               len = 0;
    uint8_t                ratesBuf[DOT11_MAX_SUPPORTED_RATES];
    uint32_t               supportedRatesMask, basicRatesMask;
    uint8_t                bWmeEnable = FALSE;
    uint8_t                axEnable   = FALSE;
    uint8_t               *pBuf;

    int8_t rc;

    GTRACE(GRP_DRIVER_MX, "mx_driver_send_ies: configuration for probe request role ID = %d", roleID);

    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID = CMD_SET_PROBE_IE;

    iesProbeReq = os_zalloc(sizeof(IesScanProbeReq_t));
    if(NULL == iesProbeReq)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed to allocate memory for iesProbeReq");
        report("\n\rERROR: Failed to allocate memory for iesProbeReq");
        rc = -1;
        goto out;
    }

    pBuf = (uint8*)iesProbeReq->iesBuffer;
    // --------------------------
    //  Prepare ies
    // --------------------------
    iesProbeReq->roleID          = roleID;
    iesProbeReq->scanRequestType = scanType;


    /* Rates */
    pDot11Rates = (dot11_RATES_t *) pBuf;

    // TODO need to implement
    cfgGetRates(roleType, &basicRatesMask, &supportedRatesMask);
    //convert the rates from bitmask to values
    len = g_stub_func.FWUtils_convertBitmapToRatesIe(supportedRatesMask, basicRatesMask, ratesBuf);

    GTRACE(GRP_DRIVER_MX, "buildProbeReq: supportedRatesMask = 0x%X, basicRatesMask = 0x%X, len = %d",
              supportedRatesMask,
              basicRatesMask,
              len);

    ASSERT_GENERAL(len <= DOT11_MAX_SUPPORTED_RATES );

    if(len > DOT11_MAX_SUPPORTED_RATES)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Len > DOT11_MAX_SUPPORTED_RATES");
        rc = -1;
        goto out;
    }

    /* fill in the supported rates */
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

   /* fill in the extended supported rates */
   if (len > SUPPORTED_RATES_MAX_IE_LEN)
   {
       pDot11Rates = (dot11_RATES_t *) pBuf;
       pDot11Rates->hdr.eleId  = EXT_SUPPORTED_RATES_IE_ID;
       pDot11Rates->hdr.eleLen = len - SUPPORTED_RATES_MAX_IE_LEN;
       memcpy((void *)pDot11Rates->rates, &ratesBuf[SUPPORTED_RATES_MAX_IE_LEN], pDot11Rates->hdr.eleLen);
       size += sizeof(dot11_eleHdr_t) + pDot11Rates->hdr.eleLen;
       pBuf += sizeof(dot11_eleHdr_t) + pDot11Rates->hdr.eleLen;
   }

    if((ROLE_P2P_CL == (roleType))||(ROLE_STA == (roleType)))
    {
        bWmeEnable = cfgIsStaWmeEnabled();// TODO need to implement cfgIsStaWmeEnabled();
        axEnable = l2_cfg_isStaHeEnabled();// TODO need to implement l2_cfg_isStaHeEnabled();
    }

    if (bWmeEnable)
    {
        len = 0;// TODO need to implement cfgBuildHtCapabilitiesIe(roleID, pBuf);
    }
    else
    {
        GTRACE(GRP_SCAN_MODULE, "802.11n disable due to WME init flag");
        len = 0;
    }
    size += len;
    pBuf += len;

    //HE Caps
    if (axEnable)
    {
        len = 0;// TODO need to implement cfgBuildHeCapabilitiesIe(roleType, pBuf);
        size += len;
        pBuf += len;

    }

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

    GTRACE(GRP_DRIVER_MX, "buildProbeReq: bWmeEnable = %d, axEnable = %d, Total len = %d",
                   bWmeEnable,
                   axEnable,
                   size);

    iesProbeReq->iesLen  = size;
    // --------------------------
    //  Prepare buffer to send
    // --------------------------

    memcpy((void*)cmd.param, (void*)iesProbeReq, sizeof(IesScanProbeReq_t));

    // TODO Send command handler

    if(retVal > 0 && cmdComplete.info.status == CMD_STATUS_SUCCESS)
    {
        rc = 0;
    }
    else
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed start scan status ENUM(CommandStatus_e,%d)",
                                           cmdComplete.info.status);
        rc = -1;
    }

    os_free(iesProbeReq);
out:
    return rc;
}

// ============================================================================
//      Supplicant APIs
// ============================================================================

/******************************************************************************

    FUNCTION:		mx_driver_stop_sched_scan

    PROTOTYPE:		driver_osprey_mx

    DESCRIPTION:    Stop a periodic scan; command is handled in WLAN
                    services context, when completed a
                    CME_MESSAGE_ID_SCAN_COMPLETE message is pushed
                    to CME queue.

    CALLER:         .stop_sched_scan (supplicant)

    PARAMETERS:     apPriv - pointer to private driver DB

    RETURNS:        0 - successfully, other - unsuccessfully

******************************************************************************/
int8_t mx_driver_stop_sched_scan(void *apPriv)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    GTRACE(GRP_DRIVER_CC33_DEBUG, "Scan stop cmd: scanning %d, sched_scanning %d", pDrv->wpa_s->scanning, pDrv->wpa_s->sched_scanning);

    return (mx_driver_send_scan_stop_cmd (pDrv->roleId, SCAN_REQUEST_CONNECT_PERIODIC_SCAN, FALSE));
}
/******************************************************************************

    FUNCTION:		mx_driver_one_shot_scan

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
int8_t mx_driver_one_shot_scan(void *apPriv,
                                       struct wpa_driver_scan_params *apParams)
{
    ti_driver_ifData_t    *apDrv = (ti_driver_ifData_t *)apPriv;
    CommandParam_t          cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                  retVal;
    ScanReqStartCmdParam_t  *pScanCmd;      // Scan command parameters
    uint16_t                  n_ssid;         // Number of SSIDs entries
    uint16_t                  allocSize = 0;  // Dynamic allocation, len for pSSIDList

    int8_t                     i, status, rc;

    GTRACE(GRP_DRIVER_MX, "Scan CMD: start one shot connection scan");
    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID = CMD_SCAN;

    /* Clean all network profiles from Supplicant when starting a connection scan
     * In case of WPS, supplicant allocated by itself a general network for WPS and clear it at the end of the wps process. */
    if (!CME_IsOngoingWPSAdHocConnection())
    {
        cmeRemoveAllProfilesFromSupplicant(apDrv->wpa_s,WLAN_REASON_DEAUTH_LEAVING);
    }

    /* Get profiles/ad-hoc connection list */
    cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();

    cmeSetScanCmeInfo(pCmeScanDB,
                      SCAN_REQUEST_ONE_SHOT,    //scan tag is scan request tag
                      &ScanResultTableSyncObj_ull);

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

    GTRACE(GRP_DRIVER_MX, "mx_driver_one_shot_scan: number of profiles %d", n_ssid);
    allocSize += sizeof(ScanReqStartCmdParam_t);
    /* Allocate scan command & scan parameters memory & SSIDs list */
    pScanCmd = os_zalloc(allocSize);
    if (NULL == pScanCmd)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed to allocate memory for scan command");
        rc = -1;
        goto out;
    }

    /*************************************************************************************/

    // --------------------------
    //  Prepare scan message
    // --------------------------

    pScanCmd->roleID            = apDrv->roleId;
    pScanCmd->scanRequestType   = SCAN_REQUEST_ONE_SHOT;
    pScanCmd->rssiThreshold     = -127;
    pScanCmd->snrThreshold      = 0;
    pScanCmd->useList           = FALSE;

    /* Open AP is supported - do not using Rx Filter */
    if(pCmeScanDB->mIsOpenProfileSupported != 0 && n_ssid != 0)
    {
        pScanCmd->ssidRXFilter = FALSE;
    }
    else
    {
        pScanCmd->ssidRXFilter = n_ssid ? TRUE : FALSE;
    }

    pScanCmd->numOfSSIDEntries = n_ssid ? n_ssid : 0;

    // --------------------------
    //  Prepare the IEs
    // --------------------------

    RoleType_e roleType;

    roleType = drv_getDrvRoleType(apDrv);
    status = mx_driver_send_ies(pScanCmd->roleID,
                                SCAN_REQUEST_ONE_SHOT,
                                apParams,
                                roleType);

    if(OK != status)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed send info elements");
        rc = -1;
        goto out_free;
    }

    // --------------------------
    //  Prepare the SSID List
    // --------------------------
    if(n_ssid)
    {
        ConnScanSSID_t *pSSIDList = (ConnScanSSID_t*)((uint8*)pScanCmd + sizeof(ScanReqStartCmdParam_t));

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
        }
    }


    // --------------------------
    // Build channel list
    // --------------------------
    status = trnspt_cmd_build_scan_channel_list(&pScanCmd->scanParams,
                                 SCAN_REQUEST_ONE_SHOT,
                                 apParams,
                                 NULL);
    if(OK != status)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed build channel list");
        rc = -1;
        goto out_free;
    }


    // --------------------------
    //  Duration time
    // --------------------------

    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].passiveScanDuration    = SCAN_MAX_DWELL_TIME_PASSIVE_MSEC;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].scanMaxDuration        = SCAN_MAX_DWELL_TIME_ACTIVE_MSEC;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].scanMinDuration        = SCAN_MIN_DWELL_TIME_ACTIVE_MSEC;

    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_5GHZ].passiveScanDuration      = SCAN_DFS_DWELL_TIME_PASSIVE_MSEC;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_5GHZ].scanMaxDuration          = SCAN_MAX_DWELL_TIME_ACTIVE_MSEC;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_5GHZ].scanMinDuration          = SCAN_MIN_DWELL_TIME_ACTIVE_MSEC;

    // --------------------------
    //  Prepare buffer to send
    // --------------------------
    memcpy((void*)cmd.param, (void*)pScanCmd, allocSize);

    // TODO Send command handler

    if(retVal != 0 || cmdComplete.info.status != CMD_STATUS_SUCCESS)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed start scan status ENUM(CommandStatus_e,%d)",
                                   cmdComplete.info.status);
        rc = -1;
    }
    else
    {
        rc = 0;
    }

out_free:
    os_free(pScanCmd);

out:
    return rc;
}

/******************************************************************************

    FUNCTION:		mx_driver_sched_scan

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
int8_t mx_driver_sched_scan(void *apPriv,
                                    struct wpa_driver_scan_params *apParams)
{
    ti_driver_ifData_t    *apDrv = (ti_driver_ifData_t *)apPriv;
    CommandParam_t          cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                  retVal;
    ScanReqStartCmdParam_t  *pScanCmd;      // Scan command parameters
    uint16_t                  n_ssid;         // Number of SSIDs entries
    uint16_t                  allocSize = 0;  // Dynamic allocation, len for pSSIDList

    int8_t                     i, status, rc;

    GTRACE(GRP_DRIVER_MX, "Scan CMD: start periodic scan");
    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID = CMD_SCAN;

    /* Clean all network profiles from Supplicant when starting a connection scan
     * In case of WPS, supplicant allocated by itself a general network for WPS and clear it at the end of the wps process. */
    if (!CME_IsOngoingWPSAdHocConnection())
    {
        cmeRemoveAllProfilesFromSupplicant(apDrv->wpa_s,WLAN_REASON_DEAUTH_LEAVING);
    }

    /* Get profiles/ad-hoc connection list */
    cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();

    cmeSetScanCmeInfo(pCmeScanDB,
                      SCAN_REQUEST_CONNECT_PERIODIC_SCAN,    //scan tag is scan request tag
                      &ScanResultTableSyncObj_ull);

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

    GTRACE(GRP_DRIVER_MX, "mx_driver_sched_scan: number of profiles %d", n_ssid);
    allocSize += sizeof(ScanReqStartCmdParam_t);
    /* Allocate scan command & scan parameters memory & SSIDs list */
    pScanCmd = os_zalloc(allocSize);
    if (NULL == pScanCmd)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed to allocate memory for scan command");
        rc = -1;
        goto out;
    }

    /*************************************************************************************/

    // --------------------------
    //  Prepare scan message
    // --------------------------

    pScanCmd->roleID            = apDrv->roleId;
    pScanCmd->scanRequestType   = SCAN_REQUEST_CONNECT_PERIODIC_SCAN;
    pScanCmd->rssiThreshold     = -127;
    pScanCmd->snrThreshold      = 0;
    pScanCmd->useList           = FALSE;

    /* Open AP is supported - do not using Rx Filter */
    if(pCmeScanDB->mIsOpenProfileSupported != 0 && n_ssid != 0)
    {
        pScanCmd->ssidRXFilter = FALSE;
    }
    else
    {
        pScanCmd->ssidRXFilter = n_ssid ? TRUE : FALSE;
    }

    pScanCmd->numOfSSIDEntries = n_ssid ? n_ssid : 0;

    // --------------------------
    //  Prepare the IEs
    // --------------------------

    RoleType_e roleType;
    roleType = drv_getDrvRoleType(apDrv);

    status = mx_driver_send_ies(pScanCmd->roleID,
                                SCAN_REQUEST_CONNECT_PERIODIC_SCAN,
                                apParams,
                                roleType);

    if(OK != status)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed send info elements");
        rc = -1;
        goto out_free;
    }

    // --------------------------
    //  Prepare the SSID List
    // --------------------------
    if(n_ssid)
    {
        ConnScanSSID_t *pSSIDList = (ConnScanSSID_t*)((uint8*)pScanCmd + sizeof(ScanReqStartCmdParam_t));

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
                                          SCAN_MAX_SCHED_SCAN_PLANS);
    if(OK != status)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed build channel list");
        rc = -1;
        goto out_free;
    }


    // --------------------------
    //  Duration time
    // --------------------------

    pScanCmd->scanParams.u.tConnScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].passiveScanDuration    = SCAN_MAX_DWELL_TIME_PASSIVE_MSEC;
    pScanCmd->scanParams.u.tConnScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].scanMaxDuration        = SCAN_MAX_DWELL_TIME_ACTIVE_MSEC;
    pScanCmd->scanParams.u.tConnScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].scanMinDuration        = SCAN_MIN_DWELL_TIME_ACTIVE_MSEC;

    pScanCmd->scanParams.u.tConnScanInfo.dwellCfg[RADIO_BAND_5GHZ].passiveScanDuration      = SCAN_DFS_DWELL_TIME_PASSIVE_MSEC;
    pScanCmd->scanParams.u.tConnScanInfo.dwellCfg[RADIO_BAND_5GHZ].scanMaxDuration          = SCAN_MAX_DWELL_TIME_ACTIVE_MSEC;
    pScanCmd->scanParams.u.tConnScanInfo.dwellCfg[RADIO_BAND_5GHZ].scanMinDuration          = SCAN_MIN_DWELL_TIME_ACTIVE_MSEC;

    // --------------------------
    //  Prepare buffer to send
    // --------------------------
    GTRACE(GRP_DRIVER_MX, "Scheduled scan requested! Number of plans = %d", pScanCmd->scanParams.u.tConnScanInfo.sched_scan_plans_num);

    memcpy((void*)cmd.param, (void*)pScanCmd, allocSize);

    // TODO Send command handler

    if(retVal != 0 || cmdComplete.info.status != CMD_STATUS_SUCCESS)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed start scan status ENUM(CommandStatus_e,%d)",
                                   cmdComplete.info.status);
        rc = -1;
    }
    else
    {
        rc = 0;
    }

out_free:
    os_free(pScanCmd);

out:
    return rc;

}

/******************************************************************************

    FUNCTION:		mx_driver_site_survey_scan

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
int8_t mx_driver_site_survey_scan(uint8_t roleID)
{

    CommandParam_t          cmd;
    CommandComplete_t       cmdComplete;
    uint16_t                  retVal;
    ScanReqStartCmdParam_t *pScanCmd;      // Scan command parameters
    int8_t                    status, rc;


    // --------------------------
    //  Prepare CMD
    // --------------------------
    cmd.cmdID = CMD_SCAN;

    GTRACE(GRP_DRIVER_MX, "Scan CMD:  start site survey scan");

    /* Get profiles/ad-hoc connection list */
    cmeScanSharedInfo_t *pCmeScanDB = scanResultTable_GetCmeScanDbPointer();

    cmeSetScanCmeInfo(pCmeScanDB,
                      SCAN_REQUEST_SURVEY_SCAN,    //scan tag is scan request tag
                      &ScanResultTableSyncObj_ull);

    scanResultTable_NotifyScanPriodStart(SCAN_REQUEST_SURVEY_SCAN);


    /* Allocate scan command */
    pScanCmd = os_zalloc(sizeof(ScanReqStartCmdParam_t));
    if (NULL == pScanCmd)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed to allocate memory for scan command");
        rc = -1;
        goto out;
    }

    /*************************************************************************************/

    // --------------------------
    //  Prepare scan message
    // --------------------------

    pScanCmd->roleID            = roleID;
    pScanCmd->scanRequestType   = SCAN_REQUEST_ONE_SHOT;
    pScanCmd->rssiThreshold     = -127;
    pScanCmd->snrThreshold      = 0;
    pScanCmd->useList           = FALSE;
    pScanCmd->ssidRXFilter      = FALSE;
    pScanCmd->numOfSSIDEntries = 0;

    // --------------------------
    //  Prepare the IEs
    // --------------------------

    RoleType_e roleType = ROLE_STA;
    //roleType = Roles_GetRoleTypeFromRoleId(pScanCmd->roleID);

    status = mx_driver_send_ies(pScanCmd->roleID,
                                SCAN_REQUEST_ONE_SHOT,
                                NULL,
                                roleType);

    if(OK != status)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed send info elements");
        rc = -1;
        goto out_free;
    }

    // --------------------------
    // Build channel list
    // --------------------------
    status = trnspt_cmd_build_scan_channel_list(&pScanCmd->scanParams,
                                 SCAN_REQUEST_ONE_SHOT,
                                 NULL,
                                 NULL);
    if(OK != status)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed build channel list");
        rc = -1;
        goto out_free;
    }


    // --------------------------
    //  Duration time
    // --------------------------

    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].passiveScanDuration    = SCAN_MAX_DWELL_TIME_PASSIVE_MSEC;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].scanMaxDuration        = SCAN_MAX_DWELL_TIME_ACTIVE_MSEC;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_2_4GHZ].scanMinDuration        = SCAN_MIN_DWELL_TIME_ACTIVE_MSEC;

    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_5GHZ].passiveScanDuration      = SCAN_DFS_DWELL_TIME_PASSIVE_MSEC;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_5GHZ].scanMaxDuration          = SCAN_MAX_DWELL_TIME_ACTIVE_MSEC;
    pScanCmd->scanParams.u.tScanInfo.dwellCfg[RADIO_BAND_5GHZ].scanMinDuration          = SCAN_MIN_DWELL_TIME_ACTIVE_MSEC;

    // --------------------------
    //  Prepare buffer to send
    // --------------------------
    memcpy((void*)cmd.param, (void*)pScanCmd, sizeof(ScanReqStartCmdParam_t));

    // TODO Send command handler

    if(retVal != 0 || cmdComplete.info.status != CMD_STATUS_SUCCESS)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: Failed start scan status ENUM(CommandStatus_e,%d)",
                                   cmdComplete.info.status);
        rc = -1;
    }
    else
    {
        rc = 0;
    }

out_free:
    os_free(pScanCmd);

out:
    return rc;
}
#endif
