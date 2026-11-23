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
 * hostdriver.h
 *
 *  Created on: 18 Oct 2021
 *      Author: a0387677
 */

#ifndef CONTROL_CMD_FW_H_
#define CONTROL_CMD_FW_H_

#include "wlan_if.h"
#include "nab.h"
#include "osi_type.h"
#include "fw_event_handle.h"
#include "conf.h"
#include "macro_utils.h"


#define MSG_QUEUE_SIZE (4)
#define EVENT_STACK_SIZE (1200)
#define EVENT_TRANSPORT_THREAD_PRIORITY (8)


#define OSPREY_INTERNAL_DESC_SIZE   200
#define NAB_EXTRA_BYTES 4

#define CALIBRATION_FILE_HEADER_SIZE (4)
#define STATIC_CALIBRATION_CFG (10)
#define WAKE_UP_CONDITIONS_CFG (12)
#define ACX_SLEEP_AUTH (9)
#define BLE_ENABLE (12)

#define MAC_ADDR_SIZE              6

#define CMD_INI_DOWNLOAD_COMMAND_SIZE (sizeof(cmd_ini_params_download_t))
#define CMD_INI_FILE_SIZE (ALIGNN_TO_4(CC33X_CONF_SIZE + CMD_HEADER_SIZE + CMD_HEADER_SIZE + CMD_INI_DOWNLOAD_COMMAND_SIZE))



typedef struct
{
    NAB_header_t NAB_header;
    uint16_t id;
    uint16_t status;
    uint32_t uppermacCommandID;
    /* payload */
    uint8_t data[0];
}cmd_header_t;

typedef struct
{
    NAB_header_t NAB_header;
    uint16_t id;
    uint16_t status;
    uint8_t data[0];
}cmd_header_generic_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    BleCommandParams_t   bleCmdParams;
}cmd_ble_hci_command_t;

typedef struct __attribute__((packed))
{
    uint8_t cmdTestId;
    uint8_t padding[3];
}cmd_test_header_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    uint16_t id;
    uint16_t len;
}cmd_generic_cfg_t; /* acx equivalent */

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    uint16_t id;
    uint16_t len;
}cmd_debug_header_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    uint16_t id;
    uint16_t len;
}cmd_interrogate_header_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    cmd_test_header_t cmdTestHeader;

    TransceiverRxStatCounters_t rxStats;
}cmd_test_get_rx_stats_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    cmd_test_header_t cmdTestHeader;

    uint32_t dummy;
}cmd_test_stop_rx_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    cmd_test_header_t cmdTestHeader;

    TTestCmd_StartRX_t startRxParams;
}cmd_test_start_rx_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    cmd_test_header_t cmdTestHeader;

    uint32_t dummy;
}cmd_test_stop_tx_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    cmd_test_header_t cmdTestHeader;

    TTestCmd_StartTX_t setTxParams;
}cmd_test_set_tx_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    cmd_test_header_t cmdTestHeader;

    TTestCmd_StartTX_t startTxParams;
}cmd_test_start_tx_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    cmd_test_header_t cmdTestHeader;

    TTestCmd_StartTXTone_t startTxToneParams;
}cmd_test_start_tx_tone_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    cmd_test_header_t cmdTestHeader;

    TTestCmd_channelTune_t tuneParams;
}cmd_test_channel_tune_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    RoleID_t roleId;
    uint8_t padding[3];
}cmd_role_disable_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    uint8_t csi_Enable;
    uint8_t csi_samples_decimation;
    uint8_t csi_phase;
    uint8_t csi_expansion_Enable;
    uint8_t csi_extra_params[4]; // Saving room for future configuration

}cmd_csi_enable_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    uint8_t csiSolEnable;
    uint8_t csiSolPeriod;
    uint8_t csiSolExpiry;
}cmd_cfg_csi_solicitation_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    uint8_t csiSolAddRemoveMac;
    uint8_t csiSolMacAddress[MAC_ADDR_SIZE];
}cmd_cfg_csi_sol_edit_mac_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    RoleEnableParameters_t roleEnableParams;
    uint8_t padding;
}cmd_role_enable_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    RoleID_t roleId;
    uint8_t padding[3];
}cmd_role_stop_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    RoleStartParameters_t roleStartParams;
}cmd_role_start_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    uint32_t dummy;
}cmd_plt_disable_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    uint32_t dummy;
}cmd_plt_enable_t;

typedef struct
{
    NAB_header_t NAB_header;
    uint16_t id;
    uint16_t status;
    uint32_t length;
    uint8_t payload[0];
}cmd_download_t;

typedef struct __attribute__((packed)){
    cmd_header_generic_t cmdHeader;
    cmd_test_header_t cmdTestHeader;
    uint16_t calibration_bitmap;
    uint8_t padding[2];
}cmd_test_set_manual_calib_t;


typedef struct
{
    /* chip id to assign each chip with its appropriate data */
    uint8_t chipId[MAC_ADDR_SIZE];
    /* payload can be of different length, chosen by user*/
    uint16_t length;
}calibration_header_fw_t;

/* Used for traveling through the calibration file */
typedef struct
{
    /* preamble static pattern */
    uint16_t staticPattern;

    calibration_header_fw_t calHeaderFw;
}calibration_header_t;


typedef struct
{
    uint8_t     fileVersion;
    uint8_t     payloadStructVersion;
    uint16_t    entriesCount;
}calibration_file_header_t;

typedef struct
{
    cmd_generic_cfg_t       cmdGeneric;

    Bool_e                  validData;
    uint8_t                 fileVersion;
    uint8_t                 payloadStructVersion;
    uint8_t                 padding;
    calibration_header_fw_t calHeader;
    uint8_t                 payload[0];

}static_calibration_cmd_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    TransmitOMICfg_t transmitOmiParams;
}cmd_debug_transmit_omi_dbg_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    UplinkPWRHDRCfg_t powerHeaderParams;
}cmd_debug_uplink_power_header_dbg_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    ForcePsCfg_t forcePsmParams;
}cmd_debug_psm_dbg_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    UplinkMUDataCfg_t uplinkMuDataParams;
}cmd_debug_uplink_mu_data_dbg_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    MSCRateCfg_t mcsRateParams;
}cmd_debug_mcs_rate_dbg_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    OperModeCTRLCfg_t operationModeControlParams;
}cmd_debug_operation_mode_control_dbg_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    UplinkMUCfg_t uplinkMuParams;
}cmd_debug_uplink_mu_dbg_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    GiLtfCfg_t giLtfParams;
}cmd_debug_gi_ltf_dbg_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugInterrogateHeader;
    BeaconRssi_t beaconRssiParams;
}cmd_debug_beacon_rssi_dbg_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    PmacHwRateMngOverrideCfg_t rateOverrideParams;
}cmd_debug_rate_override_dbg_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    ThermalCbCfg_t thermalCbParams;
}cmd_debug_thermal_cfg_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    BASessionCfg_t BASessionParams;
}cmd_ba_session_debug_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    LinkAdaptDebugCfg_t linkAdaptParams;
}cmd_link_adapt_debug_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugInterrogateHeader;
    TemperatureGet_t temperatureGetParams;
}cmd_debug_temperature_get_t;

typedef struct __attribute__((packed))
{
    cmd_debug_header_t cmdDebugHeader;
    LinkRobustnessBitmapCfg_t linkRobustnessBitmapParams;
}cmd_debug_link_robustness_bitmap_t;

typedef struct __attribute__((packed))
{
	cmd_header_generic_t header;
	uint32_t length;
	uint8_t payload[0];
}cmd_ini_params_download_t;

typedef struct
{
    cmd_header_t hdr;
}EnableBLE_cmd_t;

typedef struct
{
    cmd_header_generic_t hdr;
    SetBdAddrParam_t setBdAddrCmd;
}cmd_set_bd_addr_t;

typedef struct
{
    cmd_generic_cfg_t    cmdGeneric;
    uint8_t              sleep_auth;
    uint8_t              padding[3];
}enable_sleep_mode_cmd_t;

typedef struct __attribute__((packed))
{
    cmd_generic_cfg_t       cmdGeneric;
    WlanLongSleepInterval   LsiParams;
    uint8_t                 padding[2];
}cmd_set_lsi_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    MemoryMap_t                 memMap;
}cmd_interrogate_get_memoryMap_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    FWVersions_t                FWVersions;
}cmd_interrogate_get_fwversion_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    SPVersions_t                SPVersions;
}cmd_interrogate_get_spversion_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    DeviceSystemInfo_t                SysInfo;
}cmd_interrogate_get_sysinfo_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    BeaconRssi_t                BeaconRssi;
}cmd_interrogate_get_rssi_t;

#ifdef NOISE_FLOOR //not defined on CC3xxx
typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    NoiseFloor_t                NoiseFloor;
}cmd_interrogate_get_noise_floor_t;
#endif
typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    LinkInactivity_t            linkInactivity;
}cmd_interrogate_get_LinkInactivity_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    uint8_t                     status;
    uint8_t                     padding[3];
}cmd_interrogate_antenna_diversity_status_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    int8_t                      threshold;
    uint8_t                     padding[3];
}cmd_interrogate_antenna_diversity_rssi_threshold_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    uint8_t                     default_antenna;
    uint8_t                     padding[3];
}cmd_interrogate_get_default_antenna_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    uint8_t                     selection;
    uint8_t                     padding[3];
}cmd_interrogate_get_antenna_select_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    WlanChannel_utilize_res_t   theResult[CHANNELS_COUNT];
}cmd_interrogate_get_channel_utilization_results_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    WlanRole_current_channel_number roleChannel;
} cmd_interrogate_get_role_channel_number_cmd_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    WlanDecrypted_packetsCounters_t  count;
} cmd_interrogate_get_decrypt_packets_status_count_t;

typedef struct __attribute__((packed))
{
    cmd_generic_cfg_t       cmdGeneric;
    uint8_t                 roleId;
    uint8_t                 padding[3];
}cmd_cfg_reset_decrypted_packets_counter_cmd_t;

typedef struct __attribute__((packed))
{
    cmd_generic_cfg_t       cmdGeneric;
    uint8_t                 enable;
    uint8_t                 padding[3];
}cmd_cfg_antenna_status_t;

typedef struct __attribute__((packed))
{
    cmd_generic_cfg_t       cmdGeneric;
    int8_t                  threshold;
    uint8_t                 padding[3];
}cmd_cfg_antenna_diversity_rssi_threshold_t;

typedef struct __attribute__((packed))
{
    cmd_generic_cfg_t       cmdGeneric;
    uint8_t                 default_antenna;
    uint8_t                 padding[3];
}cmd_cfg_antenna_diversity_default_antenna_t;

typedef struct __attribute__((packed))
{
    cmd_generic_cfg_t       cmdGeneric;
    uint8_t                 selection;
    uint8_t                 padding[3];
}cmd_cfg_antenna_select_t;

typedef struct __attribute__((packed))
{
    cmd_interrogate_header_t    cmdInterrogateHeader;
    Macaddress_t                Macaddress;
}cmd_interrogate_get_mac_address_t;

typedef struct __attribute__((packed))
{
    cmd_generic_cfg_t           cmdGeneric;
    RxBaSessionCfg_t            RxBaSessionCfg;
}cmd_set_block_ack_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t cmdHeader;
    ChannelSwitchStartParameters_t channelSwitchParams;
}cmd_channel_switch_t;

typedef struct __attribute__((packed))
{
    cmd_generic_cfg_t   cmdGeneric;
    RoleID_t roleId;
    int8_t    tx_power;
    uint8_t     padding[2];
}cmd_cfg_tx_power_t;

typedef struct __attribute__((packed))
{
    cmd_generic_cfg_t   cmdGeneric;

    uint8_t     role_type;
    uint16_t    length;
    uint8_t     data[MAX_BEACON_LENGTH];
    uint8_t     padding[3];
}cmd_cfg_vendor_ie_t;

typedef struct
{
    cmd_generic_cfg_t       cmdGeneric;
    uint8_t                 seed[MAX_SEED_SIZE];
}cmd_cfg_seed_t;

#define   CMD_FIRST_TYPE_CORE_ADDR     0x00
#define   CMD_FIRST_TYPE_END           0xFF

typedef struct __attribute__((packed))
{
    uint8_t  type;
    uint8_t length;
}generic_header_t;

typedef struct __attribute__((packed))
{
    generic_header_t header;
    uint32_t addr;
}first_cmd_core_status_addr_t;

typedef struct __attribute__((packed))
{
    generic_header_t header;
    uint8_t data[254];
}first_cmd_reserved_t;

typedef struct __attribute__((packed))
{
    cmd_header_generic_t header;
    first_cmd_core_status_addr_t core_status;
    first_cmd_reserved_t data;
    //must be last
    generic_header_t end_of_cmd;
}cmd_first_params_download_t;


int  ctrlCmdFw_DownloadStaticCalibration();
int  ctrlCmdFw_DownloadIniParams();
int  ctrlCmdFw_FirstCommand();
void ctrlCmdFw_LockHostDriver();
void ctrlCmdFw_UnlockHostDriver();
void ctrlCmdFw_CreateMsgQueue();
void ctrlCmdFw_DeleteMsgQueue();
void ctrlCmdFw_CreateEventThread();
void ctrlCmdFw_DeleteEventThread();
int  ctrlCmdFw_ContainerDownload(char *containerName);
int  ctrlCmdFw_CalibratorCommand(CalibratorAction_e calibratorAction, void *calibratorCmdParams);
int  ctrlCmdFw_pltInit();
int  ctrlCmdFw_pltStop();
int  ctrlCmdFw_GetCmdSize();
int  ctrlCmdFw_TriggerFwAssert();
int  ctrlCmdFw_EnableCsiCmd(uint8_t enable);
int ctrlCmdFw_CfgCsiSolicitation(uint8_t enable, uint8_t period, uint8_t expiry);
int ctrlCmdFw_CfgCsiSolSetMac(uint8_t csiSolAddRemoveMac, uint8_t csiSolMacAddress[MAC_ADDR_LEN]);
int  ctrlCmdFw_GetChannelUtilizationResults(WlanChannel_utilize_res_t* res);
int  ctrlCmdFw_GetDecryptedPacketCounts(WlanDecrypted_packetsCounters_t * packets_count);
int  ctrlCmdFw_GetRoleChannelNumber(WlanRole_current_channel_number* currentRoleChannelParam);
int  ctrlCmdFw_GetDefaultAntenna(uint8_t* selection);
int  ctrlCmdFw_SelectDefaultAntenna(uint8_t selection);
int  ctrlCmdFw_ResetDecryptedPacketsCounter(uint8_t* roleType);
int  ctrlCmdFw_SetRoleMaxTxPower(RoleID_t roleId, int8_t max_tx_power);
int  ctrlCmdFw_SetVendorIE(wlanSetVendorInfo_t *beacon_info);
int  ctrlCmdFw_GetRssi(BeaconRssi_t* rssi);
#ifdef NOISE_FLOOR //not defined on CC3xxx
int  ctrlCmdFw_GetNoiseFloor(NoiseFloor_t* noiseFloor);
#endif
int  ctrlCmdFw_GetMemMap(MemoryMap_t *mem_map);
int  ctrlCmdFw_GetFwVersion(FWVersions_t* FwVersion);
int  ctrlCmdFw_GetSpVersion(SPVersions_t* SpVersion);
int  ctrlCmdFw_GetSysInfo(DeviceSystemInfo_t* SpVersion);
int  ctrlCmdFw_GetLinkInactivity(LinkInactivity_t *linkInactivity);
int  cmdChannelSwitchStart(RoleID_t roleId, uint8_t channel, uint8_t count, Bool_e block_tx);
int  ctrlCmdFw_SetSleepAuth(WlanPowerManagement_e sleep_auth);
int  ctrlCmdFw_SetLSI(WlanLongSleepInterval lsi_param);
int  ctrlCmdFw_GetAntennaStatus(uint8_t *status);
int  ctrlCmdFw_SetAntennaStatus(uint8_t enable);
int  ctrlCmdFw_GetAntennaRssiThreshold(int8_t *threhold);
int  ctrlCmdFw_SetAntennaRssiThreshold(int8_t threshold);
int  ctrlCmdFw_EnableChannelUtilization();
int  ctrlCmdFw_EnableBLECmd();
int  ctrlCmdFw_SetBdAddrCmd(const unsigned char *pBdAddr);
int  ctrlCmdFw_SetSeedCmd(uint8_t *pSeed, uint8_t size);


#endif /* HOST_DRIVER_INIT_DEVICE_H_ */
