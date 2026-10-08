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
/*-----------------------------------------------------------------------------
  FILENAME:       drv_cc33_ap_specific.c

  DESCRIPTION:	  This file handles AP role specific functionality 
  ----------------------------------------------------------------------------- */
#include "public_types.h"
#include "public_share.h"
#include "drv_ti_internal.h"
#include "fw_utils.h"
#include "cme_supplicant_api.h"
#include "drivers/driver.h"
#include "hostapd.h"
#include "wpa_supplicant_i.h"
#include "ieee802_11_defs.h"
#include "l2_cfg.h"
#include "802_11defs.h"
#include "cme_fw_api.h"
#include "cme_internal_api.h"
#include "gtrace.h"
#include "mpdu.h"
#include "mlme_parser.h" //for logs
#include "regulatory_domain_api.h"
#include "cme_defs.h"
#include "control_cmd_fw.h"
#ifdef CONFIG_AP


// ============================================================================
//      Modules private definitions
// ============================================================================

// Beacon & probe response maximal packet lengths
#define TIW_DRV_MAX_HEAD_BUFF         (256)
#define TIW_DRV_MAX_TAIL_BUFF         (512)
#define TIW_DRV_MAX_PROBE_RESP_LEN    (768)

#ifdef CC33XX_DRIVER_DEBUG
// Debug info - count number of STAs connections/disconnections
#define CC33_DRIVER_INC_NUM_STA_ADD()       (++gSuppDrvDebugInfo_ull.ap.numAddSta)
#define CC33_DRIVER_INC_NUM_STA_REM()       (++gSuppDrvDebugInfo_ull.ap.numRemoveSta)
#endif

// ============================================================================
//      AP globals
//      (all AP globals are stored in GLX memory, ap does not enter elp mode)
// ============================================================================


// TODO - parameters are received from supplicant in set_ap command and sent
// to AP role when started in commit command.
// We may prefer to set them directly to AP role DB.
// OR allocate/free memory on demand instead of keeping this static memory
RoleCommonParam_t gApRoleParams;



// Access categories order
const uint8_t gSuppQueueToAc[NUM_ACCESS_CATEGORIES] = {AC_VO, AC_VI, AC_BE, AC_BK};
extern signal_role_change_state_done_t g_signal_role_change_state_done;
// AP parameters which are stored on AP DB in MCP but seem to be redundant in cc33xx
// ACX_PREAMBLE_TYPE
// ACX_SLOT
// ACX_CTS_PROTECTION
// short/long  retry limit - shall not be used
// Beacon basic rate - should be selected in AP beacon

// ----------------------------------------------------------------------------
// Debug code



// Debug code
// ----------------------------------------------------------------------------

// ============================================================================
//      Local APIs
// ============================================================================

static int32_t  setApRates(uint32_t aRoleId, struct wpa_driver_ap_params *apParams);

/* ----------------------------------------------------------------------------
 ti_driver_update_channel_max_tx_power
      Updates mode->channels[].max_tx_power for the specified channel.
      Used to ensure Country IE reflects the configured TX power.

 Parameters:    pDrv - pointer to driver instance
                channel - channel number to update
                max_tx_power - TX power in dBm
 Return code:   none
---------------------------------------------------------------------------- */
void ti_driver_update_channel_max_tx_power(ti_driver_ifData_t *pDrv, uint8_t channel, int8_t max_tx_power)
{
    if (pDrv->wpa_s && pDrv->wpa_s->ap_iface && pDrv->wpa_s->ap_iface->bss[0])
    {
        struct hostapd_data *hapd = pDrv->wpa_s->ap_iface->bss[0];
        if (hapd->iface && hapd->iface->current_mode)
        {
            struct hostapd_hw_modes *mode = hapd->iface->current_mode;
            int i;
            for (i = 0; i < mode->num_channels; i++)
            {
                if (mode->channels[i].chan == channel)
                {
                    mode->channels[i].max_tx_power = max_tx_power;
                    GTRACE(GRP_DRIVER_CC33, "Updated channel %d max_tx_power to %d dBm",
                           channel, max_tx_power);
                    break;
                }
            }
        }
    }
}

// ============================================================================
//      Exported APIs
// ============================================================================

void drv_ti_ap_init(void)
{
    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    memset(&gApRoleParams, 0, sizeof(RoleCommonParam_t));
}

/* ----------------------------------------------------------------------------
 ti_driver_set_ap
      This function stores AP configuration local DB.
      Configuration is set on role DB just before starting the role (in commit API)

 Parameters:    apPriv - pointer to drive instance
                apParams - peer parameters
 Return code:   0 - on success, -1 - failure in sanity tests
---------------------------------------------------------------------------- */
int ti_driver_set_ap(void *apPriv, struct wpa_driver_ap_params *apParams)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;
    struct hostapd_data  *hapd = pDrv->wpa_s->ap_iface->bss[0];
    SlotTime_e slotTime;
    int ret = 0;
    int8_t max_tx_power = WLAN_MAX_TX_POWER_DBM;
    int8_t regulatory_max = WLAN_MAX_TX_POWER_DBM;
    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    CME_CC3XX_PORT_PRINT("\n\r enter ti_driver_set_ap");

    if ( (NULL == apParams) || (NULL == apParams->head) || (NULL == apParams->tail) || (NULL == hapd) )
    {
       CME_PRINT_REPORT_ERROR("\n\r ERROR ! got null params 0x%x 0x%x",(uint32_t)apParams , (uint32_t)hapd);
       return -1;
    }

    // set here anti-clogging threshold
    // since at this point hapd->conf is allocated and set with supplicants' default bss values
    // overwrite here if it is not the same
    if (wpa_key_mgmt_sae(apParams->key_mgmt_suites))
    {
        uint8_t antiCloggingThreshold = cfgGetApSaeAntiCloggingThreshold();
        CME_CC3XX_PORT_PRINT("\n\rti_driver_set_ap: anticlogging threshold=%d, new threashold=%d",
            hapd->conf->anti_clogging_threshold, antiCloggingThreshold);
        if (antiCloggingThreshold != hapd->conf->anti_clogging_threshold)
        {
            hapd->conf->anti_clogging_threshold = antiCloggingThreshold;
        }
    
    }

    //Prepare the ap params and beacon on the global gApRoleParams

    CME_CC3XX_PORT_PRINT("\n\r ti_driver_set_ap: setApRates");
    // Handle rates
    // MCP sets rates based on supplicant commnad. The rates in the command are
    // taken from hapd->iface which is set by CME. Since we set rates internally
    // anyway, it is set in lower layer and not via driver interface.
    if (setApRates(pDrv->roleId, apParams) < 0)
    {
        CME_PRINT_REPORT_ERROR("\n\r ERROR ! ti_driver_set_ap: setApRates failed");
        return -1;
    }

    // Store AP parameters, to be set when AP role is started
    gApRoleParams.WMM = hapd->conf->wmm_enabled;
    gApRoleParams.uInactivity = hapd->conf->ap_max_inactivity;


    GTRACE(GRP_DRIVER_CC33, "Set AP: beacon int %d dtim %d WMM %d",
               apParams->beacon_int, apParams->dtim_period, gApRoleParams.WMM);
    CME_CC3XX_PORT_PRINT("\r\nti_driver_set_ap: Set AP: beacon int %d dtim %d WMM %d",
               apParams->beacon_int, apParams->dtim_period, gApRoleParams.WMM);

    gApRoleParams.beaconInterval = apParams->beacon_int;
    gApRoleParams.dtimInterval   = apParams->dtim_period;

    CME_CC3XX_PORT_PRINT("\n\r ti_driver_set_ap: set_ap_template");
    ret = pDrv->ops->set_ap_template(pDrv->roleId, apParams);

    if (ret < 0)
    {
        CME_PRINT_REPORT_ERROR("\n\r error! ti_driver_set_ap: set_ap_template ret:%d", ret);
        goto out;
    }

    if (!pDrv->roleStarted)
    {
        if( 0 != apParams->short_slot_time )
        {
            slotTime = SLOT_TIME_SHORT;
        }
        else
        {
            slotTime = SLOT_TIME_LONG;
        }

        CME_PRINT_REPORT("\r\nti_driver_set_ap: slotTime:%d short-preamble :%d",slotTime,apParams->preamble);
        ret = pDrv->ops->start_role(pDrv, apParams, &gApRoleParams, slotTime);//cc3xxx_trnspt_cmd_if_start_role

        if(ret < 0)
            goto out;

        ret = 0; //success, hostapd assume 0 = suceess

        // mark role started
        pDrv->roleStarted = TRUE;
        pDrv->beacon_set = 1;

        if (!regulatoryDomain_getChMaxPower(apParams->freq->channel, &regulatory_max))
        {
            GTRACE(GRP_DRIVER_CC33, "AP TX power: channel %d not found in regulatory domain", apParams->freq->channel);
            ret = -1;
            goto out;
        }

        int8_t effective_max = (int8_t)MIN(regulatory_max, WLAN_MAX_TX_POWER_DBM);
        bool user_power_valid = (pDrv->configuredApTxPower >= WLAN_MIN_TX_POWER_DBM &&
                                 pDrv->configuredApTxPower <= effective_max);

        if (user_power_valid)
        {
            max_tx_power = pDrv->configuredApTxPower;
            GTRACE(GRP_DRIVER_CC33, "AP TX power: user-specified %d dBm, channel %d", max_tx_power, apParams->freq->channel);
        }
        else
        {
            max_tx_power = effective_max;
            GTRACE(GRP_DRIVER_CC33, "AP TX power: regulatory max %d dBm, channel %d", max_tx_power, apParams->freq->channel);
        }

        regulatoryDomain_setRoleMaxTxPower(pDrv, max_tx_power);
    }

#if 0 //TODO to remove, moved to cc3xxx_trnspt_cmd_if_start_role
    // --------------------------
    //  ERP PROTECTION
    // --------------------------
   // if (apParams->cts_protect)
      //  ret = mx_driver_cfg_erp_protection(pDrv->roleId, ERP_PROTECTION_ENABLED);
   // else
      //  ret = mx_driver_cfg_erp_protection(pDrv->roleId, ERP_PROTECTION_DISABLED);

    if (ret < 0)
    {
        GTRACE(GRP_DRIVER_CC33, "Set ctsprotect failed %d", ret);
        goto out;
    }

    // --------------------------
    //  PREAMBLE
    // --------------------------
//    if (apParams->preamble)
//        /* PREAMBLE_SHORT */
//        ret = mx_driver_cfg_preamble(pDrv->roleId, TRUE);
//    else
//        /* PREAMBLE_LONG */
//        ret = mx_driver_cfg_preamble(pDrv->roleId, FALSE);

    if (ret < 0)
    {
        GTRACE(GRP_DRIVER_CC33, "Set preamble failed %d", ret);
        goto out;
    }


    // --------------------------
    //  SLOT TIME
    // --------------------------
//    if (apParams->short_slot_time)
//        ret = mx_driver_cfg_slot_time(pDrv->roleId, SLOT_TIME_SHORT);
//    else
//        ret = mx_driver_cfg_slot_time(pDrv->roleId, SLOT_TIME_LONG);

    if (ret < 0)
    {
        GTRACE(GRP_DRIVER_CC33, "Set slot time failed %d", ret);
        goto out;
    }
#endif
out:
    return ret;
}

/* ----------------------------------------------------------------------------
 ti_driver_set_channel
      This function configures AP's operating channel

 Parameters:    apPriv - pointer to private driver DB
                apFreq -pointer to channel and BW configuration
 Return code:   0 on success, -1 on failure (illegal parameters)
---------------------------------------------------------------------------- */
int ti_driver_set_channel(void *apPriv, struct hostapd_freq_params *apFreq)
{
    RadioBand_e band;
    BandWidthSettings_e  bwSettings;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: NULL driver pointer");
        ASSERT_GENERAL(0);
        return -1;
    }

    // This API is activated before AP role is started so parameters can be stored
    // directly to FW DB. As a sanity check, verify AP role is enabled but not
    // started at this point.
    ASSERT_GENERAL(FALSE == pDrv->roleStarted);


    /* HostAP currently does not support J mode - we only support B/G and A */
    switch(apFreq->mode)
    {
        case HOSTAPD_MODE_IEEE80211B:
        case HOSTAPD_MODE_IEEE80211G:
            band = RADIO_BAND_2_4GHZ;
            break;
        case HOSTAPD_MODE_IEEE80211A:
            band = RADIO_BAND_5GHZ;
            break;
        default:
            GTRACE(GRP_GENERAL_ERROR, "ERROR: invalid hw mode ENUM(hostapd_hw_mode, %d)", apFreq->mode);
            return -1;
    }

    /* 40MHz support - set channel type */
    switch(apFreq->sec_channel_offset)
    {
        case 0:
            bwSettings = NLCP_CHAN_HT20;
            break;
        case -1:
            bwSettings = NLCP_CHAN_HT40MINUS;
            break;
        case 1:
            bwSettings = NLCP_CHAN_HT40PLUS;
            break;
        default:
            GTRACE(GRP_GENERAL_ERROR, "ERROR: secondary channel offset %d", apFreq->sec_channel_offset);
            return -1;
    }

    GTRACE(GRP_DRIVER_CC33, "Set AP channel cfg: bandwidth = ENUM(BandWidthSettings_e, %d), band = ENUM(RadioBand_e, %d), channel = %d",
                             bwSettings, band, apFreq->channel);

    pDrv->ApRfParams.channelNumber = apFreq->channel;
    pDrv->ApRfParams.band = band;
    pDrv->ApRfParams.bandwidth = bwSettings;

    /* Update channel's max_tx_power for Country IE generation
     * This is called before the beacon is built, so we update the channel structure's
     * to ensure the Country IE reflects the user-configured TX power.
     */
    if (pDrv->configuredApTxPower >= WLAN_MIN_TX_POWER_DBM && pDrv->configuredApTxPower <= WLAN_MAX_TX_POWER_DBM)
    {
        ti_driver_update_channel_max_tx_power(pDrv, apFreq->channel, pDrv->configuredApTxPower);
    }

    return 0;
}

/* ----------------------------------------------------------------------------
 ti_driver_set_tx_queue_params
      This function sets TX parameters for a specific queue ID on the global
      AP role structure.
      When role is started all parameters shall be sent using CMD_ROLE_START
      to FW.

 Parameters:    apPriv - pointer to private driver DB
                queue - Queue number (0 = VO, 1 = VI, 2 = BE, 3 = BK)
                parameters to set
 Return code:   0
---------------------------------------------------------------------------- */
int ti_driver_set_tx_queue_params(void *apPriv, int queue, int aifs,
                                    int cw_min, int cw_max, int burst_time)
{
    uint32_t ac;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    ASSERT_GENERAL(queue < NUM_ACCESS_CATEGORIES);

    ac = gSuppQueueToAc[queue];

    AcCfg_t acParameters;
    acParameters.aifsn  = aifs;
    acParameters.cwMax  = FIND_HIGHEST_BIT_SET(cw_max)+1; //Translate the CWmax to ECWmax since this is what PMAC needs (CWmax = 2^ECWmax -1)
    acParameters.cwMin  = FIND_HIGHEST_BIT_SET(cw_min)+1; //Translate the CWmax to ECWmin since this is what PMAC needs (CWmin = 2^ECWmin -1)
    acParameters.txopLimit = burst_time << 5;

    GTRACE(GRP_DRIVER_CC33, "Set AP TX parameters: role ID %d, queue %d, aifs %d, cw_min %d, cw max %d burst %d",
                            pDrv->roleId, ac, aifs, cw_min, cw_max, burst_time<<5);

    pDrv->ops->tx_param(pDrv, &acParameters, PS_SCHEME_LEGACY, FALSE, NULL, ac);//cc3xxx_trnspt_cmd_if_config_tx_param

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    return 0;
}

/* ----------------------------------------------------------------------------
 ti_driver_set_rts
      This function set RTS threshold for AP role

 Parameters:    apPriv - pointer to private driver DB
                aRts - Desired RTS threshold
 Return code:   0 - OK, role found -1 - else
---------------------------------------------------------------------------- */
int ti_driver_set_rts(void *apPriv, int aRts)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    GTRACE(GRP_DRIVER_CC33, "Set AP RTS: role ID %d, ENUM(RoleType_e, %d), rts %d",
                            pDrv->roleId, pDrv->roleType, aRts);

    // TODO - On one hand RTS configuration in L2 isn't define yet on the other
    // hand this API wan't activated yet. When first activated ASSERT_GENERAL and define
    // RTS handling.
    ASSERT_GENERAL(FALSE);

    return 0;
}

//TODO: Seems nobody is using the stored ssid and anyway this function is not called.
#if 0
/* ----------------------------------------------------------------------------
 ti_driver_hapd_set_ssid
      This function stores the SSID received from supplicant in role AP DB.

 Parameters:    apPriv - pointer to private driver DB
                apBuf - pointer to SSID string
                aLen - SSID length
 Return code:   0 on success, -1 on failure (illegal parameters)
---------------------------------------------------------------------------- */
int ti_driver_hapd_set_ssid(void *apPriv, const u8 *apBuf, int aLen)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: NULL driver pointer");
        ASSERT_GENERAL(0);
        return 0;
    }

    if (NULL == apBuf)
        return 0;

    if (SSID_MAX_LEN < aLen)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: SSID len is too big (%d)", aLen);
        return -1;
    }

    GTRACE(GRP_DRIVER_CC33, "Set AP SSID: %s !!!!!", apBuf);

    os_memcpy(gApRoleParams.ssid.ssid, apBuf, aLen);
    gApRoleParams.ssid.ssidLength = aLen;

    return 0;
}
#endif

/* ----------------------------------------------------------------------------
 ti_driver_sta_add
      This function starts the sequence of adding a new peer to AP.
      This API sets peer configuration on driver DB.

 Parameters:    apPriv - pointer to private driver DB
                apParams - peer parameters
 Return code:   0 - parameters OK, -1 - error indication
---------------------------------------------------------------------------- */
int ti_driver_sta_add(void *apPriv, struct hostapd_sta_add_params *apParams)
{

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    return pDrv->ops->sta_add(pDrv, apParams);

    return 0;
}

/* ----------------------------------------------------------------------------
 ti_driver_sta_set_flags
      This function kicks the operation of adding an already configured STA to AP.
      The command is handled in WLAN services context.

 Parameters:    apPriv - pointer to private driver DB
                apAddr - peer MAC address
                flags
 Return code:   0 - parameters OK, -1 - error indication
---------------------------------------------------------------------------- */
int ti_driver_sta_set_flags(void *apPriv, const u8 *apAddr,
                              unsigned int total_flags, unsigned int flags_or, unsigned int flags_and)
{

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    return pDrv->ops->sta_set_flags(pDrv, apAddr, total_flags, flags_or, flags_and);
}

/* ----------------------------------------------------------------------------
 ti_driver_sta_remove
      This function is invoked by supplicant in order to remove a peer from AP.
      This can happen in several cases:


 Parameters:    apPriv - pointer to private driver DB
                apAddr - peer MAC address
 Return code:   0 - parameters OK, -1 - error indication
---------------------------------------------------------------------------- */
int ti_driver_sta_remove(void *apPriv, const u8 *apAddr)
{
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    return pDrv->ops->sta_remove(pDrv, apAddr);

}

/* ----------------------------------------------------------------------------
 ti_driver_inact_sec
      AP only: This function returns the inactivity duration for a specific sta (in seconds).

 Parameters:    priv - pointer to private driver DB
                addr - peer MAC address

 Return code:   Number of seconds station has been inactive, -1 on failure
---------------------------------------------------------------------------- */
int ti_driver_inact_sec(void *priv, const u8 *addr)
{
    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    char macStr[MAC_STR_LEN];
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)priv;
    uint32_t lid;

    if (NULL == addr)
        return -1;

    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: NULL driver pointer");
        ASSERT_GENERAL(0);
        return -1;
    }

    GET_MAC_STR(addr, macStr);
    GTRACE(GRP_DRIVER_CC33_DEBUG, "Get inactivity time for STA %s", macStr);

    LinkInactivity_t linkInactivity;
    os_memset(&linkInactivity, 0, sizeof(LinkInactivity_t));
    os_memcpy(linkInactivity.macAddress, addr, MAC_ADDR_LEN);
    ctrlCmdFw_GetLinkInactivity(&linkInactivity);

    if (linkInactivity.inactivityDuration == -1)
    {
        return -1;
    }

    return linkInactivity.inactivityDuration / 1000000;
}

/* ----------------------------------------------------------------------------
 ti_driver_inact_sec
      AP only: This function returns the inactivity duration for a specific sta (in seconds).

 Parameters:    priv - pointer to private driver DB
                addr - peer MAC address

 Return code:   Number of seconds station has been inactive, -1 on failure
---------------------------------------------------------------------------- */
int ti_driver_inact_mili(void *priv, const u8 *addr)
{
    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    char macStr[MAC_STR_LEN];
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)priv;
    uint32_t lid;
    LinkInactivity_t linkInactivity;

    if (NULL == addr)
    {
        CME_PRINT_REPORT_ERROR("\n\r[ti_driver] ti_driver_inact_mili, null mac adder");
        return -1;
    }

    if (NULL == pDrv)
    {
        CME_PRINT_REPORT_ERROR("\n\r[ti_driver] ERROR: NULL driver pointer");
        GTRACE(GRP_DRIVER_CC33, "ERROR: NULL driver pointer");
        ASSERT_GENERAL(0);
        return -1;
    }

    GET_MAC_STR(addr, macStr);
    GTRACE(GRP_DRIVER_CC33_DEBUG, "Get inactivity time for STA %s", macStr);

    os_memset(&linkInactivity, 0, sizeof(LinkInactivity_t));
    os_memcpy(linkInactivity.macAddress, addr, MAC_ADDR_LEN);
    ctrlCmdFw_GetLinkInactivity(&linkInactivity);

    if (linkInactivity.inactivityDuration == -1)
    {
        return -1;
    }

    return linkInactivity.inactivityDuration / 1000;
}


/* ----------------------------------------------------------------------------
 ti_driver_poll_client
      AP only: This function polls a specific station by sending null data to it

 Parameters:    apPriv - pointer to private driver DB
                own_addr - own MAC address
                addr - peer MAC address
                qos - Indicates whether station is QoS station

 Return code:   None
---------------------------------------------------------------------------- */
void ti_driver_poll_client(void *priv, const u8 *own_addr, const u8 *addr, int qos)
{
    int rc = 0;
    char macStr[MAC_STR_LEN];
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)priv;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    if (NULL == addr)
        return;

    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: NULL driver pointer");
        ASSERT_GENERAL(0);
        return;
    }

    GET_MAC_STR(addr, macStr);
    GTRACE(GRP_DRIVER_CC33_DEBUG, "Poll STA %s", macStr);
    CME_PRINT_REPORT("\n\rPoll STA %s",macStr);



    ti_driver_send_l2_data(pDrv,
                            addr,
                            qos?FRAME_TYPE_QOS_NO_DATA_FRAME:FRAME_TYPE_NO_DATA_FRAME,
                            NULL,
                            0);
}

/* ----------------------------------------------------------------------------
 ti_driver_sta_deauth
      This function sends deauth packet to a STA connected to local AP

 Parameters:    apPriv - pointer to private driver DB
                own_addr - AP local address
                apAddr - peer address
                reason - reason to deauthenticate (set on deauth packet)
 Return code:   0 - packet sent to L2, -1 - else
---------------------------------------------------------------------------- */
int ti_driver_sta_deauth(void *apPriv,   const u8 *own_addr,
                           const u8 *apAddr, u16 reason)
{
    int32_t rc = 0;

    char peerMacStr[MAC_STR_LEN];
    ti_driver_ifData_t  *pDrv = (ti_driver_ifData_t *)apPriv;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    GET_MAC_STR(apAddr, peerMacStr);
    GTRACE(GRP_DRIVER_CC33, "Deauth STA: peer %s reason %d", peerMacStr, reason);

    CME_PRINT_REPORT("\r\nti driver : ti_driver_send_deauth_to_all_sta:%s", peerMacStr);

    if(FALSE == pDrv->roleStarted)
    {
        return 0;
    }

    MLME_REPORT_PRINT("\n\rti_driver_sta_deauth: roleType:%d peerMacStr %s, reason %d\n",
            pDrv->roleType,peerMacStr, reason);

    //Send deauth packet (blocking till sequence is completed)
    return ti_drv_txDeauthDisassocPacket(pDrv, (uint8_t *)apAddr, FRAME_TYPE_DEAUTHENTICATION, reason);

}

/* ----------------------------------------------------------------------------
 ti_driver_sta_disassoc
      This function sends disassoc packet to a STA connected to local AP

 Parameters:    apPriv - pointer to private driver DB
                own_addr - AP local address
                addr - peer address
                reason - reason to disassociate (set on disassoc packet)
 Return code:   0 - OK, role found -1 - else
---------------------------------------------------------------------------- */
int ti_driver_sta_disassoc(void *apPriv,   const u8 *own_addr,
                             const u8 *addr, u16 reason)
{
    int32_t rc;
    char ownMacStr[MAC_STR_LEN];
    char peerMacStr[MAC_STR_LEN];
    ti_driver_ifData_t  *pDrv = (ti_driver_ifData_t *)apPriv;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    GET_MAC_STR(own_addr, ownMacStr);
    GET_MAC_STR(addr, peerMacStr);

    GTRACE(GRP_DRIVER_CC33, "Disassoc STA: own addr %s peer addr %s", ownMacStr, peerMacStr);


    //Send disassoc packet (blocking till sequence is completed)
    return ti_drv_txDeauthDisassocPacket(pDrv, (uint8_t *)addr, FRAME_TYPE_DISASSOCIATION, reason);

}

/* ----------------------------------------------------------------------------
 ti_driver_hpad_send_eapol
      This function sends EAPOL packet directly to data path for AP role

 Parameters:
 Return code:   0 on success, -1 on failure (illegal parameters)
---------------------------------------------------------------------------- */
int ti_driver_hpad_send_eapol(void *apPriv, const u8 *apAddr, const u8 *apData,
                                size_t aDataLen, int aEncrypt, const u8 *apOwnAddr,
                                u32 aFlags)
{
    int rc = 0;
    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    if (NULL == pDrv)
    {
        GTRACE(GRP_DRIVER_CC33, "ERROR: NULL driver pointer");
        ASSERT_GENERAL(0);
        return -1;
    }

    ti_driver_send_l2_data(pDrv,
                            apAddr,
                            ETHERTYPE_EAPOL,
                            apData,
                            aDataLen);


    HOOK(HOOK_DRV_TI_AP_SPECIFIC);
    return 0;
}

/* -----------------------------------------------------------------------------
 deinit_ap - Deinitialize the AP mode
 @priv: Private driver interface data
 Returns: 0 on success, -1 on failure (or if not supported)

 This function Performs ap role stop.
 --------------------------------------------------------------------------------- */
int ti_driver_deinit_ap(void *apPriv)
{
    int rc = -1;

    ti_driver_ifData_t *pDrv = (ti_driver_ifData_t *)apPriv;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    if (apPriv==NULL)
    {
        return rc;
    }

    GTRACE(GRP_DRIVER_CC33, "Deinit ap role");
    CME_ROLE_PRINT_REPORT("\n\rDeinit ap role");

    if (ROLE_IS_TYPE_AP_BASED(pDrv->roleType))
    {
        if (TRUE == pDrv->roleStarted)
        {
            pDrv->ops->stop_role(pDrv);
            CME_PRINT_REPORT("\r\n ti driver :ti_driver_deinit_ap");
            pDrv->beacon_set = 0;
        }
        else
        {
            GTRACE(GRP_DRIVER_CC33, "WARNING: Role %d wasn't started yet or already stopped, can't stop it", pDrv->roleId);
        }
        rc = 0;
    }
    else
    {
        ASSERT_GENERAL(0); //TODO: debug - should not happen.
    }

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    return rc;
}
// ----------------------------------------------------------------------------
int32_t setHtInfoFromBeacon(uint8_t *apBuff, uint32_t aSize, htBssCap_t *htInfo)
{
    int32_t rc = 0;
    dot11_eleHdr_t *pEleHdr;
    dot11HtInformationUnparse_t *pHtIe;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    while (1 < aSize)
    {
        pEleHdr = (dot11_eleHdr_t *)apBuff;

        if (HT_INFORMATION_IE_ID == pEleHdr->eleId)
        {
            if ( aSize < pEleHdr->eleLen + sizeof(dot11_eleHdr_t) ||
                 pEleHdr->eleLen < DOT11_HT_INFORMATION_ELE_LEN  )
            {
                GTRACE(GRP_GENERAL_ERROR, "ERROR in parsing HT IE of supplicant originated beacon. IE len %d",
                                           pEleHdr->eleLen);
                rc = -1;
                break;
            }

            // Valid IE size, set HT info on global structure
            pHtIe = (dot11HtInformationUnparse_t *)pEleHdr;

            htInfo->rifsMode = HT_RIFS_MODE(pHtIe);
            htInfo->htProtection = HT_PROT(pHtIe);
            htInfo->gfProtection = HT_GF_PROT(pHtIe);
            htInfo->dualCtsProtection = HT_DUAL_CTS_PROT(pHtIe);

            break;

        }
        apBuff += pEleHdr->eleLen + sizeof(dot11_eleHdr_t);
        aSize -= pEleHdr->eleLen + sizeof(dot11_eleHdr_t);
    }

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    return rc;
}


// Based on MCP, roleAP.c, FillBeaconTemplate
// ----------------------------------------------------------------------------
uint32_t fillBeaconTemplate(struct wpa_driver_ap_params *apParams, uint8_t *apBuffer)
{
    uint8_t *pTimBuffer;
    beaconTemplate_t *pBeacon;
    dot11_TIM_Short_t *pTimIE;
    dot11_TIM_Short_t timBuffer;
    uint32_t len = 0;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    GTRACE(GRP_DRIVER_CC33, "before copy header len %d, tail len %d buffer 0x%x", apParams->head_len, apParams->tail_len, (uint32_t)apBuffer);
    CME_CC3XX_PORT_PRINT("\n\r fillBeaconTemplate ,before copy header len %d, tail len %d buffer 0x%x", apParams->head_len, apParams->tail_len, (uint32_t)apBuffer);
#ifndef CC33xx
    GTRACE(GRP_DRIVER_CC33, "dump head");
    utilsDumpHex(apParams->head, apParams->head_len);
    GTRACE(GRP_DRIVER_CC33, "dump tail");
    utilsDumpHex(apParams->tail, apParams->tail_len);
#endif
    os_memcpy(apBuffer, apParams->head, apParams->head_len);
    len += apParams->head_len;
    pTimBuffer = apBuffer + len;

    GTRACE(GRP_DRIVER_CC33, "after copy header len %d, tail len %d tim 0x%x", apParams->head_len, apParams->tail_len, (uint32_t)pTimBuffer);

    timBuffer.hdr.eleId = DOT11_TIM_ELE_ID;
    timBuffer.hdr.eleLen = DOT11_TIM_SHORT_PARAMS_ELE_LEN;
    timBuffer.dtimCount = 0;
    timBuffer.dtimPeriod = apParams->dtim_period;
    timBuffer.bmapControl = 0;
    timBuffer.partialVirtualBmap = 0;

    // Add TIM IE (Start with short style (no stations in PSD)- in case STA will enter PSD and data will be buffered, ap_beacon.c will update the TIM IE)
    pTimIE = (dot11_TIM_Short_t *)pTimBuffer;
    os_memcpy(pTimIE, &timBuffer, sizeof(dot11_TIM_Short_t));

    len += DOT11_TIM_SHORT_PARAMS_ELE_LEN + sizeof(dot11_eleHdr_t);

    // Copy the beacon's Tail section
    os_memcpy(apBuffer + len, apParams->tail, apParams->tail_len);
    len += apParams->tail_len;
#ifndef CC33xx
    GTRACE(GRP_DRIVER_CC33, "dump beacon");
    utilsDumpHex(apBuffer, len);
#endif
    // Debug - get published capabilities
    pBeacon = (beaconTemplate_t *)apBuffer;
    GTRACE(GRP_DRIVER_CC33, "Supplicant set beacon capabilities to 0x%x", pBeacon->capabilities);

    ((beaconTemplate_t*)apBuffer)->hdr.fc = DOT11_FC_BEACON;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    return len;
}
// Based on MCP, roleAP.c, fillProbeRespTemplate
// ----------------------------------------------------------------------------
uint32_t fillProbeRespTemplate(struct wpa_driver_ap_params *apParams, uint8_t *apBuffer)
{
    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    /* Fill the template based on beacon received from Hostapd */
    os_memcpy(apBuffer, apParams->proberesp, apParams->proberesp_len);
    ((probeRspTemplate_t*)apBuffer)->hdr.fc = DOT11_FC_PROBE_RESP;
    return apParams->proberesp_len;
}
// Based on MCP, roleAP.c, fillProbeRespTemplate
// ----------------------------------------------------------------------------
uint32_t fillDeauthTemplate(uint8_t *apBuffer)
{
    /* Fill the constant fields of the deauth template */

    uint32_t len  = sizeof(deauthTemplate_t);

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    os_memset(apBuffer, 0, len);

    ((deauthTemplate_t*)apBuffer)->hdr.fc = DOT11_FC_DEAUTH;
    ((deauthTemplate_t*)apBuffer)->disconnReason = 0; /* filled by firmware */
    return len;
}

// ----------------------------------------------------------------------------
static int32_t setApRates(uint32_t aRoleId, struct wpa_driver_ap_params *apParams)
{
    Bool32 htSupported;
    const htCapabilities_t *pHtCap = NULL;
    apRatesSets_t rateParams;

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    if (convertRatesToBitmap(apParams->current_rates, apParams->basic_rates, &rateParams))
    {
       CME_PRINT_REPORT_ERROR("\n\r ERROR !  setApRates failed");
       return -1;
    }

    gApRoleParams.basicRateSetBM = rateParams.basicRatesBM;
    gApRoleParams.localSupportedRatesBM = rateParams.supportedRatesBM;

    // Follow MCP behavior - supplicant doesn't set MCS rates, add them manually.
    // The MCS rates should fit with the rates reported to supplicant in
    // get_hw_feature_data API.
    htSupported = l2_cfgGetHtCapabilities(&pHtCap);
    if (htSupported)
    {
        // Add MCS0-7 if supported, MCS8 -15 aren't even defined in rates.h
        gApRoleParams.localSupportedRatesBM |= pHtCap->suppMcsSet.rxMscBitmask[0] << RATE_INDEX_MCS0;
    }

    // Note: MCP configures rate policies for management and broadcast frames.
    //       For cc33xx rate policies are managed in lower SW layers; policies
    //       are not affected directly by supplicant set rates.
    // TODO - double check FW indeed sets the correct rates

    GTRACE(GRP_DRIVER_CC33, "Set AP basic rates: number of rates %d rates 0x%x",
                             rateParams.basicRateNum, gApRoleParams.basicRateSetBM);
    GTRACE(GRP_DRIVER_CC33, "Set AP supported rates: number of BG rates %d (rates including MCS) 0x%x",
                             rateParams.suppRateNum, gApRoleParams.localSupportedRatesBM );

    HOOK(HOOK_DRV_TI_AP_SPECIFIC);

    return 0;
}

#if 0
static TI_STATUS AddStaToFW(TRoleAP *pRoleAP, uint32_t uHlid, tiwdrv_ap_sation_params_t *pStaParams)
{
    uint32_t i;
    uint32_t ratesBM;
    Bool32 wmeEnabled

    TAxcHtCapabilitiesIeFwInterface tHtCapParam;




    os_memoryCopy(pRoleAP->hOs, tAddStaParams.macAddress, pStaParams->cMac, MAC_ADDR_SIZE);
    tAddStaParams.roleID = pRoleAP->pRoleDesc->aFwRoleIds[0];
    tAddStaParams.HLID = uHlid;
    tAddStaParams.AID = pStaParams->sAid;
    tAddStaParams.BSSIndex = pRoleAP->tBssCapabilities.uBssIndex;
    tAddStaParams.WMM = (pStaParams->flags & TIW_DRV_STA_FLAG_WMM) ? TI_TRUE : TI_FALSE;
    wlanLinks_GetLinkRates(pRoleAP->hWlanLinks, &tRates, uHlid);
    tAddStaParams.supportedRates = tRates.uSuppRatesBitMap;
    tAddStaParams.sessionId = wlanLinks_IncrementTxSessionId(pRoleAP->hWlanLinks, uHlid);

    /* Update the link Tx Session ID to UDATA */
    udata_SetTxSessionId(pRoleAP->hUdata, uHlid, tAddStaParams.sessionId);

    /* Set the UAPSD parameters according to the AC info bitmap */
    for (i = 0; i < MAX_NUM_OF_AC; i++)
    {
        if (IS_BIT_SET(pStaParams->acInfo, i))
        {
            tAddStaParams.PSDType[MAX_NUM_OF_AC - 1 - i] = PS_SCHEME_UPSD_TRIGGER;
        }
        else
        {
            tAddStaParams.PSDType[MAX_NUM_OF_AC - 1 - i] = PS_SCHEME_LEGACY;
        }
    }
    tAddStaParams.SPLen = (pStaParams->acInfo >> 5) & 0x3; /* SPLen is in bits 5,6 */

    TRACE(pRoleAP->hReport, REPORT_SEVERITY_INFORMATION, "AddStaToFW(): HLID = %u, MAC "REPORT_MACSTR", AID=%u, Supp. rates=0x%x, ACInfo=0x%x\n", tAddStaParams.HLID, REPORT_MAC2STR(pStaParams->cMac),tAddStaParams.AID, tAddStaParams.supportedRates, pStaParams->acInfo);

    pRoleAP->aPendingAddPeerLinks[pRoleAP->uPendingAddPeerCount++] = uHlid;

    // Send the command and wait blocking for completion.
    // When the below returns, peer was added to role/link DBs.
    CME_SendCmd2WlanServices(&cmd);

    /* Set peer's connection state in FW */
    tPeerState.HLID = (uint8_t)uHlid;
    tPeerState.peerState = STA_STATE_CONNECTED;
    tPeerState.WMM = tAddStaParams.WMM;
    aStatus = TWD_SendCmd(pRoleAP->hTWD, CMD_SET_PEER_STATE, (void*)&tPeerState, sizeof(tPeerState), NULL, NULL);
    if (aStatus != TI_OK)
    {
        return aStatus;
    }

    /* Get STA's link WME mode to config FW accordingly */
    wmeEnabled = (pStaParams->flags & TIW_DRV_STA_FLAG_WMM) ? TI_TRUE : TI_FALSE;

    /* Config FW with new station's HT capabilities */
    tHtCapParam.hlid = (uint8_t)uHlid;
    tHtCapParam.uAmpduMaxLength = wmeEnabled ? (pStaParams->a_mpdu_params & HT_CAP_AMPDU_MAX_SIZE_BITMASK) : 0;
    tHtCapParam.uAmpduMinSpacing = wmeEnabled ? ((pStaParams->a_mpdu_params & HT_CAP_AMPDU_SPACING_BITMASK) >> HT_CAP_AMPDU_SPACING_OFFSET) : 0;
    tHtCapParam.uHtCapabilites = wmeEnabled ? pStaParams->ht_capabilities_info : 0;
    tHtCapParam.uHtCapabilites |= (wmeEnabled && pStaParams->ht_capabilities_info) ? HT_CAP_HT_OPERRATION : 0;

    aStatus = TWD_SendInfoEle(pRoleAP->hTWD, ACX_PEER_HT_CAP, (void*)&tHtCapParam, sizeof(tHtCapParam), NULL, NULL);

    return aStatus;

}
#endif

//static int32_t addStation(ti_driver_ifData_t *apDrv)
//{
//    Bool32 wmeEnabled;
//    Command_t cmd;
//
//    GTRACE(GRP_DRIVER_CC33, "************** Add STA **************");
//
//    // Update statistics
//    CC33_DRIVER_INC_NUM_STA_ADD();
//
//    cmd.cmdID = CMD_ADD_PEER;
//    cmd.pCmdParams = (void *)apDrv->pAddStaParams;
//
//    /*Check if the station already exists in WlanLinks DB*/
//    if (roleAP_FindLinkByMac(pRoleAP, pStaParams->cMac, &uHlid) == TI_OK)
//    {
//        TI_STATUS       eStatus = TI_OK;
//        TWlanLinkInfo   *linkInfo = (TWlanLinkInfo*)os_memoryAlloc(pRoleAP->hOs, sizeof(TWlanLinkInfo));
//
//        if(linkInfo == NULL)
//        {
//            TRACE( pRoleAP->hReport, REPORT_SEVERITY_FATAL_ERROR, "AddStation(): os_memoryAlloc failed\n");
//            goto err_sta;
//        }
//        else
//        {
//            TRACE(pRoleAP->hReport, REPORT_SEVERITY_WARNING, "AddStation(): Failed to add a STA" REPORT_MACSTR ", link with such MAC already exists under HLID=%u - updating parameters\n", REPORT_MAC2STR(pStaParams->cMac), uHlid);
//
//            wlanLinks_ReadLinkInfo(pRoleAP->hWlanLinks, linkInfo, uHlid);
//
//            FillLinkInfo(hRoleAP, WLANLINK_TYPE_SPECIFIC, pStaParams,linkInfo);
//
//            /* Update the station in WlanLinks DB*/
//            eStatus = wlanLinks_UpdateLinkInfo(pRoleAP->hWlanLinks, linkInfo, uHlid);
//
//            /*free allocated resources*/
//            os_memoryFree(pRoleAP->hOs, linkInfo, sizeof(TWlanLinkInfo));
//
//            if (eStatus != TI_OK)
//            {
//                TRACE(pRoleAP->hReport, REPORT_SEVERITY_ERROR, "AddStation(): Failed to update link (HLID=%u) data for STA" REPORT_MACSTR "\n", uHlid, REPORT_MAC2STR(pStaParams->cMac));
//                goto err_link;
//            }
//        }
//    }
//    else
//    {
//        /*Allocate new regular link in Wlan Links*/
//        if (AllocateWlanLink(hRoleAP, WLANLINK_TYPE_SPECIFIC, pStaParams, &uHlid) != TI_OK)
//        {
//            TRACE(pRoleAP->hReport, REPORT_SEVERITY_ERROR, "AddStation(): Failed to add a STA" REPORT_MACSTR "\n", REPORT_MAC2STR(pStaParams->cMac));
//            goto err_sta;
//        }
//        TRACE(pRoleAP->hReport, REPORT_SEVERITY_INFORMATION, "AddStation(): Added STA" REPORT_MACSTR ", to WlanLinks DB under HLID=%u\n", REPORT_MAC2STR(pStaParams->cMac),  uHlid);
//
//    }
//
//    /* Set link state CONNECTING till we receive port authorized notification from AP manager */
//    if (wlanLinks_SetLinkState(pRoleAP->hWlanLinks, WLANLINK_STATE_CONNECTING, uHlid) != TI_OK)
//    {
//        TRACE(pRoleAP->hReport, REPORT_SEVERITY_ERROR, "AddStation(): Failed to update link state, for STA" REPORT_MACSTR "under HLID=%u\n", REPORT_MAC2STR(pStaParams->cMac),  uHlid);
//        goto err_link;
//    }
//
//    /* open link for tx/rx */
//    udata_SetRxState(pRoleAP->hUdata, uHlid, LINK_STATE_OPEN);
//
//    // Set local parameters
//    apDrv->pAddStaParams->addPeer.roleID = apDrv->roleId;
//    apDrv->pAddStaParams->addPeer.roleType = apDrv->roleType;
//    apDrv->pAddStaParams->addPeer.linkType = WLANLINK_TYPE_SPECIFIC;
//
//    // Send the command for FW handling
//    CME_SendCmd2WlanServices(&cmd);
//
//    return 0;
//}
#endif
