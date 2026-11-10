/*
 * hostapd / Driver interaction with TI WiLink AP driver
 * Copyright (c) 2010, Texas Instruments, Inc. - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name(s) of the above-listed copyright holder(s) nor the
 *  names of its contributors may be used to endorse or promote products
 *  derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "utils/includes.h"
#include "utils/eloop.h"
#include "utils/common.h"
#include "common/ieee802_11_defs.h"
#include "common/defs.h"

#include <sys/mman.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netpacket/packet.h>
#include <linux/filter.h>
#include <net/if_arp.h>
#include <execinfo.h>
#include "wireless_copy.h"

#include "driver.h"

#include "priv_netlink.h"

#include "netlink.h"
#include "linux_ioctl.h"
#include "ap/hostapd.h"
#include "ap/ap_config.h"
#include "ap/ieee802_1x.h"
#include "ap/ieee802_11.h"
#include "ap/sta_info.h"
#include "ap/hw_features.h"
#include "ap/beacon.h"
#include "ap/tkip_countermeasures.h"
#include "l2_packet/l2_packet.h"
#include "../../wpa_supplicant/config.h"
#include "../../wpa_supplicant/wpa_supplicant_i.h"
#include "wps/wps_i.h"
#include "p2p/p2p_i.h"

#include "TiwDrvExternalIf.h"
#include "common.h"
#include "STADExternalIf.h"
#include "initTableTypes.h"

#define WLAN_HDR_LEN 24
#define WILINK_DEF_PRI_DEV_TYPE "1-0050F204-1"
#define WILINK_DEF_SEC_DEV_TYPE "1-0050F204-1"
#define BASE_FREQ_2_4   2407
#define BASE_FREQ_5_0   5000
#define FREQ_CH_14      2484


#define WILINK_CTRL_HDR_GET_STATUS(c) ((c) & 0x07)

typedef struct 
{
	struct hostapd_hw_modes *modes;
    int    NumOfModes;
}RegDomainStruct_t;

struct wilink_driver_global_data
{
	char                        ifaces[TIWDRV_MAX_NUM_IFACES][IFNAMSIZ + 1];
	int                         num_active_ifaces;
	int                         cmd_sock;   /* socket for wext commands   */
	TScanRequestParams			tP2pScanParams;
    tiwdrv_ap_chan_hw_info_t    *pRegDomain;
    tiwdrv_ap_hw_ht_cap_info_t  *pHtCapInfo;
    RegDomainStruct_t 			*pRegDomainHandle;
    unsigned char               iface_counter;
};

struct wilink_driver_if_data
{
	struct wilink_driver_global_data *drv_global;
	struct wpa_supplicant *wpa_s;
	struct hostapd_data *hapd;
	void *ctx; /* holds wpa_s/hapd, according to operating mode */

	int we_version; /*WEXT compiled verion*/

	char iface[IFNAMSIZ + 1];
	int  ifindex; /*linux network device unique ifindex*/
	unsigned char mac_addr[ETH_ALEN];
	tiwdrv_if_mode_e drv_role; /*role of TI Wilink driver corresponding to that interface*/
    struct netlink_data * event_netlink; /* netlink socket for WEXT events */
	struct l2_packet_data *eapol_l2;  /* socket for EAPOL frames    */
	struct l2_packet_data  *mlme_l2;  /* socket for monitor         */

	struct wpa_driver_capa capa; /*driver capabilities*/
	int    has_capability;

	unsigned int country_updated;
    int dtim_int;
	int beacon_int;
    int if_disabled;
    u8 *assoc_req_ies;
    size_t assoc_req_ies_len;
    u8 *assoc_resp_ies;
    size_t assoc_resp_ies_len;
    u8 *beacon_ies;
    size_t beacon_ies_len;

    u8 target_ap[ETH_ALEN];

    int operstate;

    int add_sta_pending; /* Indicate if wilink_sta_add operation was called, so we wait for
                            wilink_sta_set_flags before sending it to driver */
	tiwdrv_ap_sation_params_t addStaParams; /* Save last wilink_sta_add params to send it
                                               upon wilink_sta_set_flags operation */
    unsigned long  uInactivity; /*for recovery */
    unsigned int assoc_freq;
    unsigned int nl_pid;
};

/*
 * Data structure for collecting WEXT scan results. This is needed to allow
 * the various methods of reporting IEs to be combined into a single IE buffer.
 */
struct wilink_scan_data {
	struct wpa_scan_res res;
	u8 *ie;
	size_t ie_len;
	u8 ssid[32];
	size_t ssid_len;
	int maxrate;
};

static int RateATbl[] = {60,90,120,180,240,360,480,540};
static int RateGTbl[] = {10,20,55,110,60,90,120,180,240,360,480,540};
static int RateBTbl[] = {10,20,55,110};

/*local functions prototypes*/
static int tiwdrv_rate_to_double_value (int rate);
static int tiwdrv_enable_role (struct wilink_driver_if_data *drv, tiwdrv_if_mode_e role_type);
static int tiwdrv_disable_role (struct wilink_driver_if_data *drv);
static int  tiwdrv_config_role(struct wilink_driver_if_data *drv);
static tiwdrv_if_mode_e tiwdrv_get_drv_role(struct wilink_driver_if_data *drv);
static int  tiwdrv_get_info(struct wilink_driver_if_data *drv);
static void tiwdrv_init_p2p_scan_params(struct wilink_driver_global_data *drv_global);
static int freq_to_channel(unsigned int freq, u32 *channel, unsigned int *is5GBand);
static int channel_to_freq(u32 channel, unsigned int *freq);
static int wilink_send_mgmt_frame(void *priv, const u8 *data, size_t data_len, int noack);
static int wilink_send_ti_private_cmd(struct wilink_driver_if_data *drv,
        int cmd, int flags, int ioctl_cmd, char *buffer, int len);
static void wilink_event_assoc_ies(struct wilink_driver_if_data *drv);
static void wilink_scan_timeout(void *eloop_ctx, void *timeout_ctx);
static void wilink_add_scan_entry(struct wpa_scan_results *res, struct wilink_scan_data *data);
static struct hostapd_data * tiwdrv_get_hapd_handle(struct wilink_driver_if_data *drv);
static int tiwdrv_is_if_p2pgroup(struct wilink_driver_if_data *drv);
static int translate_sta_flags_to_drv(unsigned int flags);
static int wilink_wireless_assocrespie(struct wilink_driver_if_data *drv, const unsigned char *assocRespBuff, int len);
static int wilink_wireless_assocreqie(struct wilink_driver_if_data *drv, const unsigned char *assocReqBuff, int len);
static int wilink_wireless_beaconie(struct wilink_driver_if_data *drv, const unsigned char *beaconBuff, int len);
static int wilink_toggle_events(struct wilink_driver_if_data *drv, int registration_mode);
static unsigned int wilink_generate_pid(struct wilink_driver_if_data *drv, unsigned char if_number);
static void build_single_mode_capability(struct hostapd_hw_modes *hwMode, tiwdrv_ap_chan_hw_info_t *pChanInfo,
										 tiwdrv_ap_hw_ht_cap_info_t *pHtCap, enum hostapd_hw_mode mode);
static void build_hw_capability(RegDomainStruct_t *pRegHandle, tiwdrv_ap_chan_hw_info_t *pChanStruct,
								tiwdrv_ap_hw_ht_cap_info_t *pHtCap, char current_channel, enum hostapd_hw_mode hostapd_mode);


static int tiwdrv_rate_to_double_value (int rate)
{
    switch (rate)
    {
        case TIW_DRV_RATE_1M:
            return 2;

        case TIW_DRV_RATE_2M:
            return 4;

        case TIW_DRV_RATE_5_5M:
            return 11;

        case TIW_DRV_RATE_11M:
            return 22;

        case TIW_DRV_RATE_22M:
            return 44;

        case TIW_DRV_RATE_6M:
            return 12;

        case TIW_DRV_RATE_9M:
            return 18;

        case TIW_DRV_RATE_12M:
            return 24;

        case TIW_DRV_RATE_18M:
            return 36;

        case TIW_DRV_RATE_24M:
            return 48;

        case TIW_DRV_RATE_36M:
            return 72;

        case TIW_DRV_RATE_48M:
            return 96;

        case TIW_DRV_RATE_54M:
            return 108;

        case TIW_DRV_RATE_MCS_0:
            return 13;

        case TIW_DRV_RATE_MCS_1:
            return 26;

        case TIW_DRV_RATE_MCS_2:
            return 39;

        case TIW_DRV_RATE_MCS_3:
            return 52;

        case TIW_DRV_RATE_MCS_4:
            return 78;

        case TIW_DRV_RATE_MCS_5:
            return 104;

        case TIW_DRV_RATE_MCS_6:
            return 117;

        case TIW_DRV_RATE_MCS_7:
            return 130;

        case TIW_DRV_RATE_MCS_8:
            return 26;

        case TIW_DRV_RATE_MCS_9:
            return 52;

        case TIW_DRV_RATE_MCS_10:
            return 78;

        case TIW_DRV_RATE_MCS_11:
            return 104;

        case TIW_DRV_RATE_MCS_12:
            return 156;

        case TIW_DRV_RATE_MCS_13:
            return 208;

        case TIW_DRV_RATE_MCS_14:
            return 234;

        case TIW_DRV_RATE_MCS_15:
            return 260;

        default:
            return 0;
    }
}

#ifdef HOSTAPD
static void wilink_hapd_tx_callback(struct hostapd_data *hapd, u8 *buf, size_t len,
		int ok)
{
	struct ieee80211_hdr *hdr;
	u16 fc, type, stype;

	wpa_printf(MSG_MSGDUMP, "HOSTAPTI %s: TX complete: %s", __func__, ok ? "OK" : "NOT OK");

	hdr = (struct ieee80211_hdr *) buf;
	fc = le_to_host16(hdr->frame_control);

	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);

	switch (type) {
	case WLAN_FC_TYPE_MGMT:
		wpa_printf(MSG_MSGDUMP, "HOSTAPTI %s: MGMT (TX callback) %s", __func__, ok ? "ACK" : "fail");
		ieee802_11_mgmt_cb(hapd, buf, len, stype, ok);
		break;
	default:
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: unknown TX callback frame type %d stype %d",
				__func__, type, stype);
		break;
	}
}


static void wilink_hapd_rx_eapol(void *ctx, const u8 *src_addr, const u8 *buf, size_t len)
{
    struct wilink_driver_if_data *drv = (struct wilink_driver_if_data *)ctx;

     
	wpa_printf(MSG_DEBUG, " HOSTAPTIW %s: received EAPOL with len %d from " MACSTR, __func__,
			(int) len, MAC2STR(src_addr));

	ieee802_1x_receive(drv->hapd, src_addr, buf, len);
}


static void wilink_hapd_rx_mgmt(void *ctx, const u8 *src_addr, const u8 *data, size_t len) {
	struct wilink_driver_if_data *drv = ctx;
	struct hostapd_data *hapd = drv->hapd;
	struct ieee80211_hdr *hdr;
	u16 fc, type, stype;
	size_t data_len = len;
	u8* buf;
	struct hostapd_frame_info fi;

    
    len -=  sizeof(tiwdrv_ctrl_hdr_t);
	buf = ((u8*) data) + sizeof(tiwdrv_ctrl_hdr_t);
	/* 'len' and 'buf' now refer to the actual frame less the WILINK hdr */
   

	wpa_printf(MSG_EXCESSIVE, "%s: received MGMT with len %d from " MACSTR, __func__,
			(int) len, MAC2STR(src_addr));
	wpa_hexdump(MSG_EXCESSIVE, "MGMT", data, data_len);
    wpa_printf(MSG_EXCESSIVE,"\n");

	hdr = (struct ieee80211_hdr *) buf;
	fc = le_to_host16(hdr->frame_control);

	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);

    if (type != WLAN_FC_TYPE_MGMT) {
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: frame is not mgmt frame", __func__);
		return;
	}

	switch (((tiwdrv_ctrl_hdr_t*)data)->uCtrlHdr) {
	case TIW_DRV_AP_CTRL_HDR_RX:
        wpa_printf(MSG_EXCESSIVE, "HOSTAPTI %s: processing management frame", __func__);
        memset(&fi, 0, sizeof(struct hostapd_frame_info));
        ieee802_11_mgmt(hapd, buf, len, &fi);
		break;
    case TIW_DRV_AP_CTRL_HDR_TX_SUCCESS: 		/* successful TX Complete event */
        wpa_printf(MSG_EXCESSIVE, "HOSTAPTI %s: GET TX SUCCSESS", __func__);
		wilink_hapd_tx_callback(hapd, buf, len, 1);
		return;
    case TIW_DRV_AP_CTRL_HDR_TX_FAIL: 			/* fail TX Complete event */
        wpa_printf(MSG_MSGDUMP, "HOSTAPTI %s: GET TX FAIL", __func__);
		wilink_hapd_tx_callback(hapd, buf, len, 0);
		return;
	}
}
#endif


static void wilink_wpa_rx_eapol(void *ctx, const u8 *src_addr, const u8 *buf, size_t len)
{
    wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: received EAPOL with len %d from " MACSTR, __func__,
			(int) len, MAC2STR(src_addr));

}


static void wilink_wpa_rx_mgmt(void *ctx, const u8 *src_addr, const u8 *data, size_t len)
{
	struct wilink_driver_if_data *drv = (struct wilink_driver_if_data *)ctx;
	union wpa_event_data ev_data;

	struct ieee80211_hdr *hdr;
	u16 fc, type, stype,chan;
	size_t data_len = len;
	u8* buf;
    
        
   	len -=  sizeof(tiwdrv_ctrl_hdr_t);
	buf = ((u8*) data) + sizeof(tiwdrv_ctrl_hdr_t);
    /* 'len' and 'buf' now refer to the actual frame less the WILINK hdr */

	wpa_printf(MSG_MSGDUMP, "%s: received MGMT with len %d from " MACSTR, __func__,
			(int) len, MAC2STR(src_addr));
	wpa_hexdump(MSG_MSGDUMP, "MGMT", data, data_len);
    wpa_printf(MSG_MSGDUMP,"\n");

	hdr = (struct ieee80211_hdr *) buf;
	fc = le_to_host16(hdr->frame_control);

	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);

    if (type != WLAN_FC_TYPE_MGMT) {
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: frame is not mgmt frame", __func__);
		return;
	}
	os_memset(&ev_data, 0, sizeof(ev_data));

	switch (((tiwdrv_ctrl_hdr_t*)data)->uCtrlHdr)
	{
    case TIWDRV_CTRL_HDR_RX:
           	wpa_printf(MSG_MSGDUMP, "HOSTAPTIW %s: processing management frame", __func__);
			if (stype == WLAN_FC_STYPE_ACTION)
			{
				struct ieee80211_mgmt *action = (struct ieee80211_mgmt *)buf;

				wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: action frame", __func__);

				ev_data.rx_action.da = action->da;
				ev_data.rx_action.sa = action->sa;
				ev_data.rx_action.bssid = action->bssid;
				ev_data.rx_action.category = action->u.action.category;
				ev_data.rx_action.data = &action->u.action.category + 1;
				ev_data.rx_action.len = buf + len - ev_data.rx_action.data;
                chan = ((tiwdrv_ctrl_hdr_t*)data)->uChannel;
                if (chan == 14)
                 ev_data.rx_action.freq = chan * 5 + FREQ_CH_14;
                else if (chan < 14)
                 ev_data.rx_action.freq = chan * 5 + BASE_FREQ_2_4; 
                else
                 ev_data.rx_action.freq = chan * 5 + BASE_FREQ_5_0; 
                 wpa_supplicant_event(drv->wpa_s, EVENT_RX_ACTION, &ev_data);
			}
			else
			{
				ev_data.rx_mgmt.frame = buf;
				ev_data.rx_mgmt.frame_len = len;
				wpa_supplicant_event(drv->wpa_s, EVENT_RX_MGMT, &ev_data);
			}
			break;
    case TIWDRV_CTRL_HDR_TX_SUCCESS: 		/* successful TX Complete event */
        	wpa_printf(MSG_MSGDUMP, "HOSTAPTIW %s: GET TX SUCCSESS", __func__);
			ev_data.tx_status.type = type;
			ev_data.tx_status.stype = stype;
			ev_data.tx_status.ack = 1;
			ev_data.tx_status.data = buf;
			ev_data.tx_status.data_len = len;
			ev_data.tx_status.dst = hdr->addr1;
            wpa_supplicant_event(drv->wpa_s, EVENT_TX_STATUS, &ev_data);
            return;
    case TIWDRV_CTRL_HDR_TX_FAIL: 			/* fail TX Complete event */
       		wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: GET TX FAIL", __func__);
			ev_data.tx_status.type = type;
			ev_data.tx_status.stype = stype;
			ev_data.tx_status.ack = 0;
			ev_data.tx_status.data = buf;
			ev_data.tx_status.data_len = len;
			ev_data.tx_status.dst = hdr->addr1;
			wpa_supplicant_event(drv->wpa_s, EVENT_TX_STATUS, &ev_data);
			return;
	}

}

static int wilink_get_we_version(struct wilink_driver_if_data *drv)
{
    drv->we_version = WIRELESS_EXT;
    return 0;
}

static int wilink_wireless_assocreqie(struct wilink_driver_if_data *drv, const unsigned char *assocReqBuff, int len)
{
	if (len < 0)
		return -1;

    wpa_hexdump(MSG_DEBUG, "AssocReq IE wireless event", (const u8 *) assocReqBuff, len);
	if ( NULL != drv->assoc_req_ies ) {
		os_free(drv->assoc_req_ies);
		drv->assoc_req_ies = NULL;
	}

	drv->assoc_req_ies = os_malloc(len);
	if (drv->assoc_req_ies == NULL) {
		drv->assoc_req_ies_len = 0;
		return -1;
	}
	os_memcpy(drv->assoc_req_ies, assocReqBuff, len);
	drv->assoc_req_ies_len = len;
   
	return 0;
}

static int wilink_wireless_assocrespie(struct wilink_driver_if_data *drv, const unsigned char *assocRespBuff, int len)
{
	if (len < 0)
		return -1;
    
   	wpa_hexdump(MSG_DEBUG, "AssocResp IE wireless event", (const u8 *) assocRespBuff, len);
	if ( NULL != drv->assoc_resp_ies ) {
		os_free(drv->assoc_resp_ies);
		drv->assoc_resp_ies = NULL;
	}

	drv->assoc_resp_ies = os_malloc(len);
	if (drv->assoc_resp_ies == NULL) {
		drv->assoc_resp_ies_len = 0;
		return -1;
	}
	os_memcpy(drv->assoc_resp_ies, assocRespBuff, len);
	drv->assoc_resp_ies_len = len;
	return 0;
}

static int wilink_wireless_beaconie(struct wilink_driver_if_data *drv, const unsigned char *iesBuff, int iesBuffLen)
{
    if (iesBuffLen < 0)
        return -1;
    wpa_hexdump(MSG_DEBUG, "Beacon IE wireless event", (const u8*) iesBuff, iesBuffLen);
    if (NULL != drv->beacon_ies)
    {
        os_free(drv->beacon_ies);
        drv->beacon_ies = NULL;
    }

    drv->beacon_ies = os_malloc(iesBuffLen);
    if (drv->beacon_ies == NULL)
    {
        drv->beacon_ies_len = 0;
        return -1;
    }

    os_memcpy(drv->beacon_ies, iesBuff, iesBuffLen);
    drv->beacon_ies_len = iesBuffLen;
    
    return 0;
}

static void wilink_wireless_event_custom(struct wilink_driver_if_data *drv, char *buf)
{
    tiwdrv_external_event_data_t *ipc_event = (tiwdrv_external_event_data_t *) buf;
    tiwdrv_external_event_t *drv_event;
    union wpa_event_data ev_data;

    /* Only handle relevant role events*/
    /* get sub-event */

    drv_event = (tiwdrv_external_event_t *)(ipc_event->uBuffer);

	wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: event=%u ",__func__, ipc_event->EvType);

	os_memset(&ev_data, 0, sizeof(ev_data));

    switch (ipc_event->EvType) {
	case TIW_DRV_EV_START_ROAM:
    {
        tiwdrv_roam_target_ap_t* pTargetAp = (tiwdrv_roam_target_ap_t*)ipc_event->uBuffer;
        struct wpa_scan_res *pScan_res = os_malloc(sizeof(struct wpa_scan_res) + pTargetAp->ies.length);

        os_memset(pScan_res, 0, sizeof(struct wpa_scan_res) + pTargetAp->ies.length);
        wpa_printf(MSG_DEBUG, "HOSTAPTIW: %s Start Roam: BSSID: %02x.%02x.%02x.%02x.%02x.%02x,  ies_length = %d\n", __func__,
                pTargetAp->BSSID[0],pTargetAp->BSSID[1],pTargetAp->BSSID[2],pTargetAp->BSSID[3],pTargetAp->BSSID[4],pTargetAp->BSSID[5],
                pTargetAp->ies.length);

        MAC_COPY(pScan_res->bssid, pTargetAp->BSSID);
        pScan_res->beacon_int = pTargetAp->beaconInterval;
        pScan_res->freq = pTargetAp->freq/1000;
        pScan_res->caps = pTargetAp->capabilities;
        pScan_res->level = pTargetAp->RSSI;
        pScan_res->tsf = pTargetAp->lastRxTSF;
        pScan_res->ie_len = pTargetAp->ies.length;


        drv->beacon_ies = os_malloc(pTargetAp->ies.length);
        drv->beacon_ies_len = pTargetAp->ies.length;
        os_memcpy(drv->beacon_ies, pTargetAp->ies.buff, pTargetAp->ies.length);

        os_memcpy(drv->target_ap, pTargetAp->BSSID, ETH_ALEN);

        os_memcpy((u8 *)(pScan_res + 1), (u8 *)pTargetAp->ies.buff, pTargetAp->ies.length);
        ev_data.target_ap.res = pScan_res;
        wpa_supplicant_event(drv->wpa_s, EVENT_ROAM_TO_SPECIFIC_AP, &ev_data);
        os_free(pScan_res);

        break;
    }

    case TIW_DRV_EV_REPORT_FT:
    {
        ev_data.ft_ies.ies = ipc_event->uBuffer;
        ev_data.ft_ies.ies_len = ipc_event->uBufferSize;

        os_memcpy(ev_data.ft_ies.target_ap, drv->target_ap, ETH_ALEN);
        ev_data.ft_ies.ric_ies_len = 0;
        ev_data.ft_ies.ft_action = 0;

        wpa_supplicant_event(drv->wpa_s, EVENT_FT_RESPONSE, &ev_data);
        break;
    }

	case TIW_DRV_EV_CONNECT_SCAN_COMPLETE:
    {
        wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: SCHED SCAN COMPLETE event", __func__);
        wpa_supplicant_event(drv->ctx, EVENT_SCHED_SCAN_STOPPED, NULL);
        break;
    }

    case TIW_DRV_EV_SCAN_COMPLETE:
    {
        ev_data.scan_info.sched_scan = 0;

        wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: SCAN_COMPLETE event", __func__);
        if ((drv->drv_role == TIWDRV_IF_MODE_STA) || (drv->drv_role == TIWDRV_IF_MODE_P2PCL) ||
	      (drv->drv_role == TIWDRV_IF_MODE_SAP) || (drv->drv_role == TIWDRV_IF_MODE_P2PGO))
        {
            eloop_cancel_timeout(wilink_scan_timeout, drv, drv->ctx);
        }
	
        wpa_supplicant_event(drv->ctx, EVENT_SCAN_RESULTS, &ev_data);
        break;
    }

    case TIW_DRV_EV_CONTINUOUS_SCAN_REPORT:
    {
        ev_data.scan_info.sched_scan = 1;

        wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: SCHED SCAN REPORT event", __func__);
        wpa_supplicant_event(drv->ctx, EVENT_SCAN_RESULTS, &ev_data);
        break;
    }

    case TIW_DRV_EV_REMAIN_ON_CH_STARTED:
        wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: TIW_DRV_EV_REMAIN_ON_CH_STARTED event, channel=%u, duration=%u", __func__,
                       drv_event->event_data.remain_on_ch.channel, drv_event->event_data.remain_on_ch.duration);
		channel_to_freq(drv_event->event_data.remain_on_ch.channel, &ev_data.remain_on_channel.freq);
        ev_data.remain_on_channel.duration = drv_event->event_data.remain_on_ch.duration;
        wpa_supplicant_event(drv->wpa_s, EVENT_REMAIN_ON_CHANNEL, &ev_data);
        break;

    case TIW_DRV_EV_REMAIN_ON_CH_COMPLETE:
        wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: TIW_DRV_EV_REMAIN_ON_CH_COMPLETE event, channel=%u", __func__,
                       drv_event->event_data.remain_on_ch.channel);
		channel_to_freq(drv_event->event_data.remain_on_ch.channel, &ev_data.remain_on_channel.freq);
        wpa_supplicant_event(drv->wpa_s, EVENT_CANCEL_REMAIN_ON_CHANNEL, &ev_data);
        break;

#if defined(HOSTAPD) || defined(CONFIG_AP)
    case TIW_DRV_EV_STA_AGING:
    {
        union wpa_event_data ed;
        wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: TIW_DRV_EV_STA_AGING event, disconnecting STA", __func__);
        os_memcpy(ed.low_ack.addr, drv_event->event_data.mac_addr, ETH_ALEN);
        wpa_supplicant_event(drv->ctx, EVENT_STATION_LOW_ACK, &ed);
        break;
    }
    case TIW_DRV_EV_TX_RETRY_FALIURE:
    {
        union wpa_event_data ed;
        wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: TIW_DRV_EV_TX_RETRY_FALIURE event, disconnecting STA", __func__);
        os_memcpy(ed.low_ack.addr, drv_event->event_data.mac_addr, ETH_ALEN);
        wpa_supplicant_event(drv->ctx, EVENT_STATION_LOW_ACK, &ed);
        break;
    }
#endif

    /* station events */

    case TIW_DRV_EV_ASSOCIATED:
        wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: TIW_DRV_EV_ASSOCIATED event", __func__);
        wilink_event_assoc_ies(drv);
        wpa_supplicant_event(drv->wpa_s, EVENT_ASSOC, NULL);
        break;

    case TIW_DRV_EV_DISASSOCIATED:
    {
        tiwdrv_deauth  *deauth = (tiwdrv_deauth *) &(drv_event->event_data.deauth);
        wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: TIW_DRV_EV_DISASSOCIATED event", __func__);
        os_free(drv->assoc_req_ies);
        drv->assoc_req_ies = NULL;
        os_free(drv->assoc_resp_ies);
        drv->assoc_resp_ies = NULL;
        os_memset(&ev_data, 0, sizeof(ev_data));
        ev_data.deauth_info.reason_code = deauth->reason_code;
        wpa_supplicant_event(drv->wpa_s, EVENT_DISASSOC, &ev_data);
        break;
    }

    case TIW_DRV_EV_ASSOC_RESP_IE:
        wilink_wireless_assocrespie(drv, ipc_event->uBuffer, ipc_event->uBufferSize);
        break;

    case TIW_DRV_EV_ASSOC_REQ_IE:
        wilink_wireless_assocreqie(drv, ipc_event->uBuffer, ipc_event->uBufferSize);
        break;

    case TIW_DRV_EV_BEACON_IE:
        wilink_wireless_beaconie(drv, ipc_event->uBuffer, ipc_event->uBufferSize);
        break;

    case TIW_DRV_EV_MIC_FAILURE:
        {
            tiwdrv_sta_micfailure_t *mic = (tiwdrv_sta_micfailure_t *) &(drv_event->event_data.micfailure);

            wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: TIW_DRV_EV_MIC_FAILURE event: "
                    "flags=0x%x src_addr=" MACSTR,  __func__, mic->flags, MAC2STR(mic->src_addr));

            os_memset(&ev_data, 0, sizeof(ev_data));
            ev_data.michael_mic_failure.unicast = !(mic->flags & MICFAILURE_GROUP);
            wpa_supplicant_event(drv->ctx, EVENT_MICHAEL_MIC_FAILURE, &ev_data);
        }
        break;

    case TIW_DRV_EV_PMKID_CANDIDATE:
    {
        tiwdrv_sta_pmkid_candidate_t *cand = (tiwdrv_sta_pmkid_candidate_t *) &(drv_event->event_data.pmkid_cand);
        u8 *addr = (u8 *) cand->bssid;

        wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: TIW_DRV_EV_PMKID_CANDIDATE event: "
                       "flags=0x%x index=%d bssid=" MACSTR, __func__,  cand->flags,
                       cand->index, MAC2STR(addr));

        os_memset(&ev_data, 0, sizeof(ev_data));
        os_memcpy(ev_data.pmkid_candidate.bssid, addr, ETH_ALEN);
        ev_data.pmkid_candidate.index = cand->index;
        ev_data.pmkid_candidate.preauth = cand->flags & WEXT_PMKID_CAND_PREAUTH;
        wpa_supplicant_event(drv->wpa_s, EVENT_PMKID_CANDIDATE, &ev_data);
        break;
    }
    case TIW_DRV_EV_WPS_SESSION_OVERLAP:
        wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: TIW_DRV_EV_WPS_SESSION_OVERLAP event", __func__);
        wps_pbc_overlap_event(drv->wpa_s->wps);
        break;

	case TIW_DRV_EV_CHANNEL_LIST_CHANGED:
		ev_data.channel_list_changed.initiator = REGDOM_SET_BY_DRIVER;
        wpa_supplicant_event(drv->ctx, EVENT_CHANNEL_LIST_CHANGED, &ev_data);
		break;

	case TIW_DRV_EV_CAC:
		ev_data.dfs_event.freq 		  = drv_event->event_data.dfs_params.freq;
		ev_data.dfs_event.ht_enabled  = drv_event->event_data.dfs_params.ht_enabled;
		ev_data.dfs_event.chan_offset = drv_event->event_data.dfs_params.channel_offset;
		ev_data.dfs_event.chan_width  = drv_event->event_data.dfs_params.chan_width;
		ev_data.dfs_event.cf1 		  = drv_event->event_data.dfs_params.cf1;
		ev_data.dfs_event.cf2 		  = drv_event->event_data.dfs_params.cf2;

		wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: DFS event on freq %d MHz, ht: %d, offset: %d, width: %d, cf1: %dMHz, cf2: %dMHz", __func__,
		   ev_data.dfs_event.freq, ev_data.dfs_event.ht_enabled, ev_data.dfs_event.chan_offset, 
		   ev_data.dfs_event.chan_width, ev_data.dfs_event.cf1, ev_data.dfs_event.cf2);
		
		switch(drv_event->event_data.dfs_params.cac_type)
		{
			case TIW_DRV_CAC_FINISHED:
				wpa_supplicant_event(drv->ctx, EVENT_DFS_CAC_FINISHED, &ev_data);
				break;
				
			case TIW_DRV_CAC_ABORTED:
				wpa_supplicant_event(drv->ctx, EVENT_DFS_CAC_ABORTED, &ev_data);
				break;

			case TIW_DRV_CAC_NOP_FINISHED:
				wpa_supplicant_event(drv->ctx, EVENT_DFS_NOP_FINISHED, &ev_data);
				break;
				
			case TIW_DRV_CAC_RADAR_DETECTED:
				wpa_supplicant_event(drv->ctx, EVENT_DFS_RADAR_DETECTED, &ev_data);
				break;

			default:
				wpa_printf(MSG_DEBUG, "HOSTAPTIWERR %s: unsupported dfs event type %u",__func__, drv_event->event_data.dfs_params.cac_type);
		}
		break;
	case TIW_DRV_EV_SWITCH_CHANNEL_COMPLETE:
		ev_data.ch_switch.freq 		  = drv_event->event_data.dfs_params.freq;
		ev_data.ch_switch.ht_enabled  = drv_event->event_data.dfs_params.ht_enabled;
		ev_data.ch_switch.ch_offset   = drv_event->event_data.dfs_params.channel_offset;
		ev_data.ch_switch.ch_width    = drv_event->event_data.dfs_params.chan_width;
		ev_data.ch_switch.cf1 		  = drv_event->event_data.dfs_params.cf1;
		ev_data.ch_switch.cf2 		  = drv_event->event_data.dfs_params.cf2;

		wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: Channel Switch Complete event on freq %d MHz, ht: %d, offset: %d, width: %d, cf1: %dMHz, cf2: %dMHz", __func__,
		   ev_data.ch_switch.freq, ev_data.ch_switch.ht_enabled, ev_data.ch_switch.ch_offset, 
		   ev_data.ch_switch.ch_width, ev_data.ch_switch.cf1, ev_data.ch_switch.cf2);
		
		wpa_supplicant_event(drv->ctx, EVENT_CH_SWITCH, &ev_data);
		break;
		
    default:
        wpa_printf(MSG_DEBUG, "HOSTAPTIWERR %s: unsupported event %u",__func__, ipc_event->EvType);
    }
}

static void wilink_wireless_event_rcv(struct wilink_driver_if_data *drv,char *data, int len)
{
	struct iw_event iwe_buf, *iwe = &iwe_buf;
	char *pos, *end, *custom;

   	wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: enter", __func__);

	pos = data;
	end = data + len;

	while (pos + IW_EV_LCP_LEN <= end) {
		/* Event data may be unaligned, so make a local, aligned copy
		 * before processing. */
		memcpy(&iwe_buf, pos, IW_EV_LCP_LEN);
		wpa_printf(MSG_DEBUG, "Wireless event: cmd=0x%x len=%d",
				iwe->cmd, iwe->len);
		if (iwe->len <= IW_EV_LCP_LEN)
			return;

		custom = pos + IW_EV_POINT_LEN;
		if (drv->we_version > 18 &&
				((iwe->cmd == IWEVCUSTOM || iwe->cmd == IWEVGENIE))) {
			/* WE-19 removed the pointer from struct iw_point */
			char *dpos = (char *) &iwe_buf.u.data.length;
			int dlen = dpos - (char *) &iwe_buf;
			memcpy(dpos, pos + IW_EV_LCP_LEN,
					sizeof(struct iw_event) - dlen);
		} else {
			memcpy(&iwe_buf, pos, sizeof(struct iw_event));
			custom += IW_EV_POINT_OFF;
		}

		switch (iwe->cmd) {
		case IWEVCUSTOM:
		case IWEVGENIE:
		/*case IWEVGENIE:*/
			if (custom + iwe->u.data.length > end)
				return;

			wilink_wireless_event_custom(drv, custom);

			break;
		}

		pos += iwe->len;
	}
    
}

static void wilink_event_link(struct wilink_driver_if_data *drv, char *buf,
        size_t len, int del)
{
    union wpa_event_data event;

    os_memset(&event, 0, sizeof(event));
    if (len > sizeof(event.interface_status.ifname))
        len = sizeof(event.interface_status.ifname) - 1;
    os_memcpy(event.interface_status.ifname, buf, len);
    event.interface_status.ievent = del ? EVENT_INTERFACE_REMOVED
            : EVENT_INTERFACE_ADDED;

    wpa_printf(MSG_DEBUG, "RTM_%sLINK, IFLA_IFNAME: Interface '%s' %s",
            del ? "DEL" : "NEW", event.interface_status.ifname, del ? "removed"
                    : "added");

    wpa_supplicant_event(drv->wpa_s, EVENT_INTERFACE_STATUS, &event);
    
}

static void wilink_wireless_event_rtm_dellink(void *ctx, struct ifinfomsg *ifi,
        u8 *buf, size_t len)
{
    struct wilink_driver_if_data *drv = ctx;
    int attrlen, rta_len;
    struct rtattr *attr;
      
    if (drv->drv_role != TIWDRV_IF_MODE_SAP)
    {
        attrlen = len;
        attr = (struct rtattr *) buf;

        rta_len = RTA_ALIGN(sizeof(struct rtattr));
        while (RTA_OK(attr, attrlen))
        {
            if (attr->rta_type == IFLA_IFNAME)
            {
                wilink_event_link(drv, ((char *) attr) + rta_len, attr->rta_len
                        - rta_len, 1);
            }
            attr = RTA_NEXT(attr, attrlen);
        }
    }
}


static void wilink_wireless_event_rtm_newlink(void *ctx, struct ifinfomsg *ifi, u8 *buf, size_t len)
{
	struct wilink_driver_if_data *drv = (struct wilink_driver_if_data *)ctx;
	int attrlen, rta_len;
	struct rtattr *attr;
    
    wpa_printf(MSG_DEBUG, " HOSTAPTIW %s: enter ", __func__);
    
  	if (len < (int) sizeof(struct ifinfomsg))
		return;
 
	/* Ignore events from different network interfaces */
    if (ifi->ifi_index != drv->ifindex)
    {
        wpa_printf(MSG_DEBUG, "HOSTAPTIW: Ignore event for foreign ifindex %d ", ifi->ifi_index);
        return;
    }
 
    if (drv->drv_role != TIWDRV_IF_MODE_SAP)
    {
        if (!drv->if_disabled && !(ifi->ifi_flags & IFF_UP))
        {
            wpa_printf(MSG_DEBUG, "HOSTAPTIW: Interface down");
            drv->if_disabled = 1;
            wpa_supplicant_event(drv->wpa_s, EVENT_INTERFACE_DISABLED, NULL);
        }

        if (drv->if_disabled && (ifi->ifi_flags & IFF_UP))
        {
            wpa_printf(MSG_DEBUG, "HOSTAPTIW: Interface up");
            drv->if_disabled = 0;
            wpa_supplicant_event(drv->wpa_s, EVENT_INTERFACE_ENABLED, NULL);
        }
    

        /*
         * Some drivers send the association event before the operup event--in
         * this case, lifting operstate in wpa_driver_wext_set_operstate()
         * fails. This will hit us when wpa_supplicant does not need to do
         * IEEE 802.1X authentication
         */
        if (drv->operstate == 1 && (ifi->ifi_flags & (IFF_LOWER_UP
                | IFF_DORMANT)) == IFF_LOWER_UP && !(ifi->ifi_flags
                & IFF_RUNNING))
            netlink_send_oper_ifla(drv->event_netlink, drv->ifindex, -1,
                    IF_OPER_UP);
                         
     }

    	attrlen = len;

	attr = (struct rtattr *)buf;
 
	rta_len = RTA_ALIGN(sizeof(struct rtattr));
    while (RTA_OK(attr, attrlen))
    {
        if (attr->rta_type == IFLA_WIRELESS)
        {
           wilink_wireless_event_rcv(drv, ((char *) attr) + rta_len,
					attr->rta_len - rta_len);
		}
        else if (attr->rta_type == IFLA_IFNAME)
        {
            if (drv->drv_role != TIWDRV_IF_MODE_SAP)
            {
                wilink_event_link(drv, ((char *) attr) + rta_len, attr->rta_len
                            - rta_len, 0);
            }
        }

        attr = RTA_NEXT(attr, attrlen);
    }

}

static void *wilink_global_init(void)
{
	struct wilink_driver_global_data *drv_global;

	wpa_printf(MSG_DEBUG, " HOSTAPTIW %s: enter", __func__);
    
	drv_global = os_zalloc(sizeof(struct wilink_driver_global_data));
	if (drv_global == NULL) {
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: Could not allocate memory for wilink driver global data", __func__);
		return NULL;
	}

    /* init WEXT commands socket */
	drv_global->cmd_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (drv_global->cmd_sock < 0) {
		perror("socket(PF_INET,SOCK_DGRAM)");
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error creating cmd_sock", __func__);
		goto failed;
	}

	tiwdrv_init_p2p_scan_params(drv_global);

    /* Init Reg Domain*/
    drv_global->pRegDomain = (tiwdrv_ap_chan_hw_info_t *) os_zalloc(sizeof(tiwdrv_ap_chan_hw_info_t));
	if (drv_global->pRegDomain == NULL) {
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: Could not allocate memory for RegDomain", __func__);
        goto failed;
	}
    drv_global->pRegDomainHandle = (RegDomainStruct_t *)os_zalloc(sizeof(RegDomainStruct_t));
    if (drv_global->pRegDomainHandle == NULL) {
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: Could not allocate memory for pRegDomainHandle", __func__);
        goto failed;
	}

	drv_global->pHtCapInfo = (tiwdrv_ap_hw_ht_cap_info_t *) os_zalloc(sizeof(tiwdrv_ap_hw_ht_cap_info_t));
	if (drv_global->pHtCapInfo == NULL) {
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: Could not allocate memory for pHtCapInfo", __func__);
		goto failed;
	}

	os_memset(drv_global->pHtCapInfo, 0, sizeof(tiwdrv_ap_hw_ht_cap_info_t));

	drv_global->iface_counter = 0;

	return drv_global;
failed:
    wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: failed", __func__);

	if (drv_global->cmd_sock > 0)
		close(drv_global->cmd_sock);
    if (drv_global->pRegDomain)
		free(drv_global->pRegDomain);
	if (drv_global->pHtCapInfo)
		free(drv_global->pHtCapInfo);
	if (drv_global->pRegDomainHandle)
		free(drv_global->pRegDomainHandle);
    free(drv_global);
	return NULL;
   
}


static void wilink_global_deinit(void *global_priv)
{
	struct wilink_driver_global_data *drv_global = (struct wilink_driver_global_data *)global_priv;

    wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: enter", __func__);

	if (!drv_global)
		return;

	if (drv_global->cmd_sock > 0)
		close(drv_global->cmd_sock);

	if (drv_global->pRegDomain)
		free(drv_global->pRegDomain);
	if (drv_global->pHtCapInfo)
		free(drv_global->pHtCapInfo);
	if (drv_global->pRegDomainHandle)
		free(drv_global->pRegDomainHandle);
    free(drv_global);
    return;
}


static void *wilink_if_init(void *ctx, const char *ifname, void *global_priv)
{
	struct wilink_driver_if_data *drv;
	struct wilink_driver_global_data *drv_global = (struct wilink_driver_global_data *)global_priv;
	struct netlink_config *netlink_cfg;
	unsigned char count = drv_global->iface_counter++;
      
	wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: enter ifname = %s ", __func__, ifname);
    
	drv = os_zalloc(sizeof(struct wilink_driver_if_data));

	if (drv == NULL) {
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: Could not allocate memory for wilink driver interface data", __func__);
		return NULL;
	}

   drv->wpa_s = ctx;
   drv->ctx = ctx;
   drv->drv_global = global_priv;

   os_memcpy(drv->iface, ifname, sizeof(drv->iface));
   drv->ifindex = if_nametoindex(ifname);
   drv->drv_role = tiwdrv_get_drv_role(drv);

   drv->nl_pid = wilink_generate_pid(drv,count);
   /* Bring up the network interface*/
   if (linux_set_iface_flags(drv_global->cmd_sock, drv->iface, 1) < 0) {
       wpa_printf(MSG_ERROR, "HOSTAPTIW: Could not set "
                  "interface '%s' UP", drv->iface);
       goto failed;
   }

   if ((drv->drv_role != TIWDRV_IF_MODE_STA) && (drv->drv_role != TIWDRV_IF_MODE_P2PCL))
   {
         /* init l2 sockets */
        drv->eapol_l2 = l2_packet_init(drv->iface,
                NULL,
                ETH_P_EAPOL,
                wilink_wpa_rx_eapol, drv, 0);

        drv->mlme_l2 = l2_packet_init(drv->iface,
                NULL,
                TIWDRV_MGMT_ETH_TYPE,
                wilink_wpa_rx_mgmt, drv, 0);
        if (!drv->eapol_l2 || !drv->mlme_l2) {
            wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error creating l2 sockets", __func__);
            goto failed;
        }

        l2_packet_get_own_addr(drv->mlme_l2, drv->mac_addr);
    }

	/*Init Wext events netlink socket*/
	netlink_cfg = os_zalloc(sizeof(struct netlink_config));
	if (netlink_cfg == NULL)
		goto failed;
	netlink_cfg->ctx = drv;
	netlink_cfg->newlink_cb = wilink_wireless_event_rtm_newlink;
	netlink_cfg->dellink_cb = wilink_wireless_event_rtm_dellink;
	drv->event_netlink = netlink_init(netlink_cfg, drv->nl_pid);
	if (drv->event_netlink == NULL) {
        os_free(netlink_cfg);
		goto failed;
	}
	
	/* get driver capabilites etc. from driver*/
	tiwdrv_get_info(drv);

	if (drv->drv_role != TIWDRV_IF_MODE_UNKNOWN)
	{
		wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: assigned driver role %d to the interface", __func__, drv->drv_role);

		if (tiwdrv_enable_role(drv, drv->drv_role))
		{
			goto failed;
		}

		if (tiwdrv_config_role(drv))
		{
			wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: failed to configure role ID %d in the driver", __func__, drv->drv_role);
			goto failed;
		}
	}
	else
	{
		wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: role corresponding the the interface is still unknown, delaying role enable", __func__);
	}

    netlink_send_oper_ifla(drv->event_netlink, drv->ifindex, 1, IF_OPER_DORMANT);
    return drv;

failed:
    wpa_printf(MSG_ERROR, " HOSTAPTIWERR %s: failed", __func__);

    /* Free of allocated resources will be performed in driver deinit() callback which shall
    be called when init() returns NULL*/
    if (drv->eapol_l2)
        l2_packet_deinit(drv->eapol_l2);
    if (drv->mlme_l2)
        l2_packet_deinit(drv->mlme_l2);
    netlink_deinit(drv->event_netlink);
    (void) linux_set_iface_flags(drv->drv_global->cmd_sock, drv->iface, 0);
    free(drv);
    return NULL;
}


static void wilink_deinit(void *priv) {
	struct wilink_driver_if_data *drv = priv;
    int ret;
       
	wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: enter",__func__);

	if (!drv)
		return;

     ret = tiwdrv_disable_role(drv);

    if (ret)
    {
        wpa_printf(MSG_ERROR,
                "HOSTAPTIERR %s: error sending TI_PARAM_DISABLE_ROLE command to the driver",
                __func__);
	   
    }

    if ((drv->drv_role == TIWDRV_IF_MODE_STA) || (drv->drv_role == TIWDRV_IF_MODE_P2PCL))
    {
        eloop_cancel_timeout(wilink_scan_timeout, drv, drv->wpa_s);
    }
 
	if (drv->eapol_l2)
		l2_packet_deinit(drv->eapol_l2);
	if (drv->mlme_l2)
		l2_packet_deinit(drv->mlme_l2);
     netlink_send_oper_ifla(drv->event_netlink, drv->ifindex, 0, IF_OPER_UP);
     netlink_deinit(drv->event_netlink);
    (void) linux_set_iface_flags(drv->drv_global->cmd_sock, drv->iface, 0);

     /* always stop the p2p-group when stopping the p2p-dev */
     if (drv->drv_role == TIWDRV_IF_MODE_P2PDEV)
	 	(void) linux_set_iface_flags(drv->drv_global->cmd_sock, NETIF_NAME(TIWLAN_DEV_NAME_P2PGROUP), 0);

     free(drv);
}

static void wilink_scan_timeout(void *eloop_ctx, void *timeout_ctx)
{
    wpa_printf(MSG_DEBUG, "Scan timeout - try to get results");
    wpa_supplicant_event(timeout_ctx, EVENT_SCAN_RESULTS, NULL);
}

/* Station functions*/
static void wilink_event_assoc_ies(struct wilink_driver_if_data *drv)
{
    union wpa_event_data data;

    if (drv->assoc_req_ies == NULL && drv->assoc_resp_ies == NULL)
        return;

    os_memset(&data, 0, sizeof(data));
    if (drv->assoc_req_ies)
    {
        data.assoc_info.req_ies = drv->assoc_req_ies;
        data.assoc_info.req_ies_len = drv->assoc_req_ies_len;
    }
    if (drv->assoc_resp_ies)
    {
        data.assoc_info.resp_ies = drv->assoc_resp_ies;
        data.assoc_info.resp_ies_len = drv->assoc_resp_ies_len;
    }

    if (drv->beacon_ies)
    {
        data.assoc_info.beacon_ies = drv->beacon_ies;
        data.assoc_info.beacon_ies_len = drv->beacon_ies_len;
    }

    data.assoc_info.freq = drv->assoc_freq;
	
    wpa_supplicant_event(drv->wpa_s, EVENT_ASSOCINFO, &data);

    os_free(drv->assoc_req_ies);
    drv->assoc_req_ies = NULL;
    os_free(drv->assoc_resp_ies);
    drv->assoc_resp_ies = NULL;
    os_free(drv->beacon_ies);
    drv->beacon_ies = NULL;
}

int tidrv_set_bssid(void *priv, const u8 *bssid)
{
    int ret;
    TMacAddr tBssid;

    /* If MAC address null -> connect to "ANY" BSSID */
    if (bssid)
    {
        MAC_COPY (tBssid, bssid);
    }
    else
    {
        MAC_COPY (tBssid, "\xff\xff\xff\xff\xff\xff");
    }

    /* also set it to the SME */
    ret = wilink_send_ti_private_cmd(priv, TI_PARAM_DESIRED_BSSID,
            TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, (char *) &tBssid,
            sizeof(tBssid));
    if (ret != 0)
    {
        wpa_printf(
                MSG_ERROR,
                "%s: error sending TI_PARAM_DESIRED_BSSID command to the driver",
                __func__);
        ret = -1;
    }
    return ret;
}

int wilink_get_bssid(void *priv, u8 *bssid)
{
    struct wilink_driver_if_data *drv = priv;
    struct iwreq iwr;
    TMacAddr tBssid;
    int ret;

    wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: enter",__func__);

    os_memset(&iwr, 0, sizeof(iwr));
    os_strlcpy(iwr.ifr_name, drv->iface, IFNAMSIZ);

    ret = wilink_send_ti_private_cmd(drv, TI_PARAM_CURRENT_BSSID,
            TIWDRV_CMD_GET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, (char *) &tBssid,
            sizeof(tBssid));
    if (ret != 0)
    {
        wpa_printf(
                MSG_ERROR,
                "%s: error sending TI_PARAM_CURRENT_BSSID command to the driver",
                __func__);
    }
    else
    {
        os_memcpy(bssid, tBssid, ETH_ALEN);
    }

    return ret;
}

int wilink_get_ssid(void *priv, u8 *ssid)
{
    struct wilink_driver_if_data *drv = priv;
    TSsid tSsid;
    int ret;

    wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: enter",__func__);

    ret = wilink_send_ti_private_cmd(drv, TI_PARAM_CURRENT_SSID,
            TIWDRV_CMD_GET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, (char *) &tSsid,
            sizeof(tSsid));
    if (ret == 0)
    {
        ret = tSsid.len;
        if (ret > 32)
        {
            ret = 32;
        }

        os_memcpy(ssid, tSsid.str, ret);
    }
    else
    {
        wpa_printf(
                MSG_ERROR,
                "%s: error sending TI_PARAM_CURRENT_SSID command to the driver",
                __func__);
        ;
    }

    return ret;
}

static int wilink_disassociate(void *priv, const u8 *addr, int reason_code)
{
    struct wilink_driver_if_data *drv = priv;
    int ret = 0;
    TSsid tSsid;
    int i;

    wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: enter",__func__);
	if ((drv->drv_role == TIWDRV_IF_MODE_STA) || (drv->drv_role == TIWDRV_IF_MODE_P2PCL))
	{
		/* In either case - we need to disconnect, so prepare "junk" SSID */
		for (i = 0; i < MAX_SSID_LEN; i++)
		{
			tSsid.str[i] = (i + 1);
		}
		tSsid.len = MAX_SSID_LEN;

		if (wilink_send_ti_private_cmd(drv, TI_PARAM_DESIRED_SSID,
				TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, (char *) &tSsid,
				sizeof(tSsid)) != 0)
		{
			wpa_printf(
					MSG_ERROR,
					"%s: error sending TI_PARAM_DESIRED_SSID command to the driver",
					__func__);
			return -1;
		}

	    if (wilink_send_ti_private_cmd(priv, TI_PARAM_DISCONNECT, TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, NULL, 0) != 0)
	    {
	        wpa_printf(
	                MSG_ERROR,
	                "%s: error sending TI_PARAM_DISCONNECT command to the driver",
	                __func__);
	        ret = -1;
	    }

	}
    return ret;
}

#ifndef CONFIG_P2P

static int wilink_add_pmkid(void *priv, const u8 *bssid, const u8 *pmkid)
{
    struct wilink_driver_if_data *drv = priv;
    OS_802_11_PMKID tRsnPmkidList;
    int ret;

    wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: enter",__func__);

    os_memset(&tRsnPmkidList, 0, sizeof(tRsnPmkidList));

    tRsnPmkidList.BSSIDInfoCount = 1;
    tRsnPmkidList.Length = 2 * sizeof(uint32_t) + MAC_ADDR_LEN + IW_PMKID_LEN;
    MAC_COPY (tRsnPmkidList.osBSSIDInfo[0].BSSID, bssid);
    os_memcpy(&tRsnPmkidList.osBSSIDInfo[0].PMKID, pmkid, IW_PMKID_LEN);

    ret = wilink_send_ti_private_cmd(drv, TI_PARAM_PREAUTH_LIST, TIWDRV_CMD_SET_FLAG,
            TIWDRV_PRIV_WEXT_IOCTL, (char *) &tRsnPmkidList,
            sizeof(tRsnPmkidList));
    if (ret != 0)
    {
        wpa_printf(MSG_ERROR,
                "%s: error sending TI_PARAM_PMKID_LIST command to the driver",
                __func__);
    }

    return ret;
}

static int wilink_flush_pmkid(void *priv)
{
    OS_802_11_PMKID tRsnPmkidList;
    int ret;

    wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: enter",__func__);

     /* By using info count=0, RSN knows to clear its tables */
      tRsnPmkidList.BSSIDInfoCount = 0;
      ret = wilink_send_ti_private_cmd(priv, TI_PARAM_PREAUTH_LIST, TIWDRV_CMD_SET_FLAG,
             TIWDRV_PRIV_WEXT_IOCTL, (char *) &tRsnPmkidList,
              sizeof(tRsnPmkidList));
       if (ret != 0)
       {
           wpa_printf(MSG_ERROR,
                 "%s: error sending TI_PARAM_PMKID_LIST command to the driver",
                 __func__);
       }


    return ret;
}

#endif

int wilink_set_operstate(void *priv, int state)
{
	struct wilink_driver_if_data *drv = priv;

	wpa_printf(MSG_DEBUG, "%s: operstate %d->%d (%s)", __func__,
			   drv->operstate, state, state ? "UP" : "DORMANT");

	drv->operstate = state;

	if (drv->drv_role != TIWDRV_IF_MODE_UNKNOWN)
	{
		if (wilink_send_ti_private_cmd(priv, TI_PARAM_PORT_STATUS,
									   TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, (char *) &state,
									   sizeof(state)) != 0)
		{
			wpa_printf(MSG_ERROR,
					   "%s: error sending TI_PARAM_PORT_STATUS command to the driver", __func__);
		}
	}

	return netlink_send_oper_ifla(drv->event_netlink, drv->ifindex, -1,
								  state ? IF_OPER_UP : IF_OPER_DORMANT);
}

/*static int wilink_set_probe_req_ie(void *priv, const u8 *ies, size_t ies_len)
{
    int ret;

    wpa_printf(MSG_ERROR, "enter: %s", __func__);

    ret = wilink_send_ti_private_cmd(priv, TI_PARAM_PROBE_REQ_EXTRA_IES,
            TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, (char *) ies, ies_len);
    if (ret != 0)
    {
        wpa_printf(
                MSG_ERROR,
                "%s: error sending TI_PARAM_PROBE_REQ_EXTRA_IES command to the driver",
                __func__);
    }

    return ret;
}*/

/*end of station functions */

#ifdef HOSTAPD

static void *wilink_hapd_init(struct hostapd_data *hapd, struct wpa_init_params *params)
{
    struct wilink_driver_global_data *drv_global;
	struct wilink_driver_if_data *drv;
    struct netlink_config *netlink_cfg;
    unsigned char count = 0; 

	wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter", __func__);

    /*Allocate global data*/
    drv_global = os_zalloc(sizeof(struct wilink_driver_global_data));
	if (drv_global == NULL) {
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: Could not allocate memory for wilink driver global data", __func__);
		return NULL;
	}

    /*Allocate interface data*/
	drv = os_zalloc(sizeof(struct wilink_driver_if_data));
	if (drv == NULL) {
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: Could not allocate memory for wilink driver data", __func__);
		return NULL;
	}

	drv->hapd = hapd;
	drv->ctx = hapd;
    drv->drv_global = drv_global;

    if (hapd->conf == NULL)
        wpa_printf(MSG_ERROR,"HOSTAPTIERR %s: hapd->conf null \n", __func__);
    else
        memcpy(drv->iface, params->ifname, sizeof(drv->iface));

    drv->ifindex = if_nametoindex(drv->iface);
    drv->drv_role = tiwdrv_get_drv_role(drv);

    drv->nl_pid = wilink_generate_pid(drv, count);

    if (drv->drv_role == TIWDRV_IF_MODE_UNKNOWN) {
        wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: failed to dermine TI Wilink driver role (probably invalid interface name: %s)", __func__, drv->iface);
        goto failed;
    }

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: assigned driver role %d to the interface", __func__, drv->drv_role);
   
	/* init cmd_sock */
	drv_global->cmd_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (drv_global->cmd_sock < 0) {
		perror("socket(PF_INET,SOCK_DGRAM)");
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: error creating cmd_sock", __func__);
		goto failed;
	}

	/* Bring up the network interface*/
   	if (linux_set_iface_flags(drv_global->cmd_sock, drv->iface, 1) < 0) 
	{
		wpa_printf(MSG_ERROR, "HOSTAPTIW: Could not set "
                  "interface '%s' UP", drv->iface);
       	goto failed;
   	}
   
    /* init l2 sockets */
    drv->eapol_l2 = l2_packet_init(drv->iface,
                                   NULL,
                                   ETH_P_EAPOL,
                                   wilink_hapd_rx_eapol, drv, 0);

    drv->mlme_l2 = l2_packet_init(drv->iface,
                                  NULL,
                                  TIWDRV_MGMT_ETH_TYPE,
                                  wilink_hapd_rx_mgmt, drv, 0);

    if (!drv->eapol_l2 || !drv->mlme_l2) {
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: error creating l2 sockets", __func__);
		goto failed;
	}

    if (l2_packet_get_own_addr(drv->eapol_l2, hapd->own_addr) ||
        l2_packet_get_own_addr(drv->eapol_l2, drv->mac_addr))
    {
        wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: cannot retrieve own hwdr addr", __func__);
        goto failed;
    }

    /* Init Reg Domain*/
	
    drv_global->pRegDomain = (tiwdrv_ap_chan_hw_info_t *) os_zalloc(sizeof(tiwdrv_ap_chan_hw_info_t));
	if (drv_global->pRegDomain == NULL) {
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: Could not allocate memory for RegDomain", __func__);
        goto failed;
	}
    drv_global->pRegDomainHandle = (RegDomainStruct_t *)os_zalloc(sizeof(RegDomainStruct_t));
    if (drv_global->pRegDomainHandle == NULL) {
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: Could not allocate memory for RegDomain", __func__);
        goto failed;
	}


    drv_global->pHtCapInfo = (tiwdrv_ap_hw_ht_cap_info_t *) os_zalloc(sizeof(tiwdrv_ap_hw_ht_cap_info_t));
    if (drv_global->pHtCapInfo == NULL) {
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: Could not allocate memory for pHtCapInfo", __func__);
        goto failed;
	}

    os_memset(drv_global->pHtCapInfo, 0, sizeof(tiwdrv_ap_hw_ht_cap_info_t));

    /* get driver capabilites etc. from driver*/
    tiwdrv_get_info(drv);

    /*Init Wext events netlink socket*/
    netlink_cfg = os_zalloc(sizeof(*netlink_cfg));
	if (netlink_cfg == NULL)
		goto failed;
	netlink_cfg->ctx = drv;
	netlink_cfg->newlink_cb = wilink_wireless_event_rtm_newlink;
	drv->event_netlink = netlink_init(netlink_cfg, drv->nl_pid);
	if (drv->event_netlink == NULL) {
		os_free(netlink_cfg);
		goto failed;
	}

	if (tiwdrv_enable_role(drv, TIWDRV_IF_MODE_SAP))
		goto failed;

    return drv;

failed:
    wpa_printf(MSG_ERROR, " HOSTAPTIERR %s: failed", __func__);

	/* Free of allocated resources will be performed in driver deinit() callback which shall
	be called when init() returns NULL*/
	(void) linux_set_iface_flags(drv->drv_global->cmd_sock, drv->iface, 0);
	if (drv->drv_global->cmd_sock > 0)
		close(drv->drv_global->cmd_sock);
	if (drv->eapol_l2)
		l2_packet_deinit(drv->eapol_l2);
	if (drv->mlme_l2)
		l2_packet_deinit(drv->mlme_l2);
    if (drv->drv_global->pRegDomain)
        free(drv->drv_global->pRegDomain);
    if (drv->drv_global->pHtCapInfo)
        free(drv->drv_global->pHtCapInfo);
    if (drv_global->pRegDomainHandle)
		free(drv_global->pRegDomainHandle);
    netlink_deinit(drv->event_netlink);
    free(drv);
    free(drv_global);
	return NULL;
}


static void wilink_hapd_deinit(void *priv)
{
	struct wilink_driver_if_data *drv = priv;
	int    ret;

	wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

	ret  = tiwdrv_disable_role(drv);

	if (ret)
		wpa_printf(MSG_ERROR, "HOSTAPTIERR %s: error sending TI_PARAM_DISABLE_ROLE command to the driver", __func__);

	(void) linux_set_iface_flags(drv->drv_global->cmd_sock, drv->iface, 0);
       if (drv->drv_global->cmd_sock > 0)
	   	close(drv->drv_global->cmd_sock);
	if (drv->eapol_l2)
		l2_packet_deinit(drv->eapol_l2);
	if (drv->mlme_l2)
		l2_packet_deinit(drv->mlme_l2);
    if (drv->drv_global->pRegDomain)
        free(drv->drv_global->pRegDomain);
    if (drv->drv_global->pHtCapInfo)
        free(drv->drv_global->pHtCapInfo);
	if (drv->drv_global->pRegDomainHandle)
		free(drv->drv_global->pRegDomainHandle);
    netlink_deinit(drv->event_netlink);
    free(drv->drv_global);
    free(drv);
}
#endif


static int wilink_flush(void *priv)
{
	struct wilink_driver_if_data *drv = priv;
	int ret = 0;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_REMOVE_ALL_STATION, TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, NULL,0);
	return ret;
}


static int wilink_read_sta_data(void *priv, struct hostap_sta_driver_data *data,
		const u8 *addr)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_station_info_t staDataStruct;
	int ret = 0;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    memcpy(staDataStruct.cMac,addr,TIW_DRV_MAC_ADDR);
	ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_STATION_DATA, TIWDRV_CMD_GET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, (char*)&staDataStruct,sizeof(staDataStruct));
	if(ret == 0)
	{
		data->rx_bytes = staDataStruct.iRxBytes;
		data->tx_bytes = staDataStruct.iTxBytes;
		data->inactive_msec = staDataStruct.iInactiveTime;
	}

	return ret;
}

static int wilink_sta_deauth(void *priv, const u8 *own_addr, const u8 *addr, int reason)
{
    struct wilink_driver_if_data *drv = priv;
    struct hostapd_data * hapd = tiwdrv_get_hapd_handle(drv);
    struct ieee80211_mgmt mgmt;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter", __func__);

    memset(&mgmt, 0, sizeof(mgmt));
    mgmt.frame_control = IEEE80211_FC(WLAN_FC_TYPE_MGMT,
            WLAN_FC_STYPE_DEAUTH);
    memcpy(mgmt.da, addr, ETH_ALEN);
    memcpy(mgmt.sa, hapd->own_addr, ETH_ALEN);
    memcpy(mgmt.bssid, hapd->own_addr, ETH_ALEN);
    mgmt.u.deauth.reason_code = host_to_le16(reason);
    return wilink_send_mgmt_frame(drv, (u8 *)&mgmt, IEEE80211_HDRLEN + sizeof(mgmt.u.deauth), 0);
}


static int wilink_sta_disassoc(void *priv, const u8 *own_addr, const u8 *addr, int reason)
{
	struct wilink_driver_if_data *drv = priv;
	struct ieee80211_mgmt mgmt;
	struct hostapd_data * hapd = tiwdrv_get_hapd_handle(drv);


	wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter", __func__);

	memset(&mgmt, 0, sizeof(mgmt));
	mgmt.frame_control = IEEE80211_FC(WLAN_FC_TYPE_MGMT,
			WLAN_FC_STYPE_DISASSOC);
	memcpy(mgmt.da, addr, ETH_ALEN);
	memcpy(mgmt.sa, hapd->own_addr, ETH_ALEN);
	memcpy(mgmt.bssid, hapd->own_addr, ETH_ALEN);
	mgmt.u.disassoc.reason_code = host_to_le16(reason);
	return  wilink_send_mgmt_frame(drv, (u8 *)&mgmt, IEEE80211_HDRLEN + sizeof(mgmt.u.disassoc), 0);
}

static int wilink_set_rts(void *priv, int rts)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_general_param_t GenStruct;
	int ret = 0;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    GenStruct.lValue = rts;
	ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_SET_RTS, TIWDRV_CMD_SET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenStruct,sizeof(GenStruct));
	return ret;
}

static int convertRatesToDrvBitmap(struct hostapd_rate_data *rates, int *basic_rates, tiwdrv_ap_rate_set_t  *pRateParams)
{
	int i;
	uint32_t uSuppRateBitFiled = 0;
	uint32_t uBasicRateBitFiled = 0;
	
    	wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);
	
	if ((rates != NULL) || (basic_rates != NULL))
	{
		if (rates != NULL)
		{
			for (i=0; i<TIW_DRV_MAX_SUPPORT_RATE && rates[i].rate>0;i++)
		  	{
		  		switch(rates[i].rate/10)
    				{
				        case 1:   uSuppRateBitFiled = DRV_RATE_MASK_1_BARKER; break;
				        case 2:   uSuppRateBitFiled = DRV_RATE_MASK_2_BARKER; break;
				        case 5:   uSuppRateBitFiled = DRV_RATE_MASK_5_5_CCK; break;
				        case 6:   uSuppRateBitFiled = DRV_RATE_MASK_6_OFDM; break;
				        case 9:   uSuppRateBitFiled = DRV_RATE_MASK_9_OFDM; break;
				        case 11:  uSuppRateBitFiled = DRV_RATE_MASK_11_CCK; break;
				        case 12:  uSuppRateBitFiled = DRV_RATE_MASK_12_OFDM; break;
				        case 18:  uSuppRateBitFiled = DRV_RATE_MASK_18_OFDM; break;
				        case 22:  uSuppRateBitFiled = DRV_RATE_MASK_22_PBCC; break;
				        case 24:  uSuppRateBitFiled = DRV_RATE_MASK_24_OFDM; break;
				        case 36:  uSuppRateBitFiled = DRV_RATE_MASK_36_OFDM; break;
				        case 48:  uSuppRateBitFiled = DRV_RATE_MASK_48_OFDM; break;
				        case 54:  uSuppRateBitFiled = DRV_RATE_MASK_54_OFDM; break;
				        default:  uSuppRateBitFiled = 0; break;
    				}
				pRateParams->uSupportedRatesBitmap |= uSuppRateBitFiled;
		  	}
		  	pRateParams->cSuppRateLen = i;
			wpa_printf(MSG_DEBUG, "HOSTAPTI %s: cSuppRateLen = %d,  uSupportedRatesBitmap = 0x%x", __func__, pRateParams->cSuppRateLen, pRateParams->uSupportedRatesBitmap);
		}
		
        	if (basic_rates != NULL)
		{
			for (i=0; (i < TIW_DRV_MAX_SUPPORT_RATE && basic_rates[i]>0) ;i++)
		  	{
		  		switch(basic_rates[i]/10)
    				{
				        case 1:   uBasicRateBitFiled = DRV_RATE_MASK_1_BARKER; break;
				        case 2:   uBasicRateBitFiled = DRV_RATE_MASK_2_BARKER; break;
				        case 5:   uBasicRateBitFiled = DRV_RATE_MASK_5_5_CCK; break;
				        case 6:   uBasicRateBitFiled = DRV_RATE_MASK_6_OFDM; break;
				        case 9:   uBasicRateBitFiled = DRV_RATE_MASK_9_OFDM; break;
				        case 11:  uBasicRateBitFiled = DRV_RATE_MASK_11_CCK; break;
				        case 12:  uBasicRateBitFiled = DRV_RATE_MASK_12_OFDM; break;
				        case 18:  uBasicRateBitFiled = DRV_RATE_MASK_18_OFDM; break;
				        case 22:  uBasicRateBitFiled = DRV_RATE_MASK_22_PBCC; break;
				        case 24:  uBasicRateBitFiled = DRV_RATE_MASK_24_OFDM; break;
				        case 36:  uBasicRateBitFiled = DRV_RATE_MASK_36_OFDM; break;
				        case 48:  uBasicRateBitFiled = DRV_RATE_MASK_48_OFDM; break;
				        case 54:  uBasicRateBitFiled = DRV_RATE_MASK_54_OFDM; break;
				        default:  uBasicRateBitFiled = 0; break;
    				}
				pRateParams->uBasicRatesBitmap |= uBasicRateBitFiled;
		  	}
		  	pRateParams->cBasicRateLen = i;
			wpa_printf(MSG_DEBUG, "HOSTAPTI %s: cBasicRateLen = %d,  uBasicRatesBitmap = 0x%x", __func__, pRateParams->cBasicRateLen, pRateParams->uBasicRatesBitmap);
		}

		return 0;
    	}
	
	return -1;
}

static int wilink_ap_set_rate_sets(void *priv, struct hostapd_rate_data *rates, int *basic_rates)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_rate_set_t  RateParams;
	int ret = 0;
	
    	wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

	memset(&RateParams, 0, sizeof(RateParams));

	if (convertRatesToDrvBitmap(rates, basic_rates, &RateParams) == 0)
	{
		ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_SET_RATE, TIWDRV_CMD_SET_FLAG,
                                          TIWDRV_PRIV_WEXT_IOCTL, (char*)&RateParams,sizeof(RateParams));
    	}

	return ret;
}

static int wilink_set_cts_protect(void *priv, int value)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_general_param_t GenStruct;
	int ret = 0;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    GenStruct.lValue = value;
	ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_USE_CTS_PROT, TIWDRV_CMD_SET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenStruct,sizeof(GenStruct));
	return ret;

}


static int wilink_set_preamble(void *priv, int value)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_general_param_t GenStruct;
	int ret = 0;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    GenStruct.lValue = value;
	ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_AP_SHORT_PREAMBLE, TIWDRV_CMD_SET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenStruct,sizeof(GenStruct));
	return ret;
}


static int wilink_set_short_slot_time(void *priv, int value)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_general_param_t GenStruct;
	int ret = 0;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    GenStruct.lValue = value;
	ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_USE_SHORT_SLOT_TIME, TIWDRV_CMD_SET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenStruct,sizeof(GenStruct));
	return ret;
}


static int wilink_set_tx_queue_params(void *priv, int queue, int aifs,
		int cw_min, int cw_max, int burst_time)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_tx_params_t TxParamStruct;
	int ret = 0;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    TxParamStruct.cQueueId = queue;
	TxParamStruct.cAifs = aifs;
	TxParamStruct.sCwmin = cw_min;
	TxParamStruct.sCwmax = cw_max;
	TxParamStruct.sTxop = burst_time;

	ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_AP_QOS_AC_ATTRIBUTES, TIWDRV_CMD_SET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, (char*)&TxParamStruct,sizeof(TxParamStruct));
	return ret;

}

static int wilink_set_country(void *priv, const char *country)
{
	struct wilink_driver_if_data *drv = priv;
	char tempCountry[DOT11_COUNTRY_STRING_LEN];

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    /* Mark country was set*/
	drv->country_updated = TRUE;

	os_memcpy(tempCountry, country, DOT11_COUNTRY_STRING_LEN);

    if (0 != wilink_send_ti_private_cmd(drv, TI_PARAM_COUNTRY, TIWDRV_CMD_SET_FLAG,
							   TIWDRV_PRIV_WEXT_IOCTL, tempCountry, DOT11_COUNTRY_STRING_LEN))
	{
		return -1;
    }

    return 0;
}

static int wilink_get_country(void *priv, char *alpha2)
{
	struct wilink_driver_if_data *drv = priv;
	char tempCountry[DOT11_COUNTRY_STRING_LEN+DOT11_COUNTRY_STRING_LEN];
	int ret;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    ret= wilink_send_ti_private_cmd(drv, TI_PARAM_COUNTRY, TIWDRV_CMD_GET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, 
									tempCountry, DOT11_COUNTRY_STRING_LEN+DOT11_COUNTRY_STRING_LEN);

	if (ret != 0)
    {
        wpa_printf(MSG_ERROR, "%s: error sending TI_PARAM_COUNTRY command to the driver", __func__);
    }
    else
    {
        os_memcpy(alpha2, tempCountry, DOT11_COUNTRY_STRING_LEN);
		alpha2[DOT11_COUNTRY_STRING_LEN] = '\0';
    }
	
    return ret;
}

static int wilink_hpad_send_eapol(void *priv, const u8 *addr, const u8 *data,
                             size_t data_len, int encrypt, const u8 *own_addr,
                             u32 flags)
{
	struct wilink_driver_if_data *drv = priv;

	wpa_printf(MSG_DEBUG, "HOSTAPTI %s: sending %d byte EAPOL packet to " MACSTR,	__func__,
			(int) data_len, MAC2STR(addr));

	return (l2_packet_send(drv->eapol_l2, addr, ETH_P_EAPOL, data, data_len) < 0);
}


static const u8 * wilink_get_mac_addr(void *priv)
{
	struct wilink_driver_if_data *drv = priv;

	return drv->mac_addr;
}

static int tiwdrv_p2p_search(struct wilink_driver_if_data *drv, struct wpa_driver_scan_params *params)
{
	TScanRequestParams tScanParams;
	int i;
	int ret;

	/* we need the p2p-group interface up to get its mac addr */
	(void)linux_set_iface_flags(drv->drv_global->cmd_sock, NETIF_NAME(TIWLAN_DEV_NAME_P2PGROUP), 1);

	/*initialize with global scan parameters*/
	os_memcpy(&tScanParams, &drv->drv_global->tP2pScanParams, sizeof(tScanParams));

	/*Fill in just scan parameters relevant for application P2P scan*/
	os_memcpy(tScanParams.u.tScanInfo.desiredSsid.str, params->ssids[0].ssid, params->ssids[0].ssid_len);
	tScanParams.u.tScanInfo.desiredSsid.len = params->ssids[0].ssid_len;
	tScanParams.u.tScanInfo.ssidFilterEnable = TI_FALSE;

	/* Update required channels for scan*/
    /* NOTE!!! We assume freqs list contains G channels followed by A channels and not mixed channels.
		In case of mixed list we need to do the work here. */
	if (params->freqs)
	{
		unsigned int channel = 0;
		unsigned int isABand = 0;

		tScanParams.u.tScanInfo.numOfGChannels = 0;
		tScanParams.u.tScanInfo.numOfAChannels = 0;

		for (i=0; params->freqs[i]; i++)
		{
			if (freq_to_channel(params->freqs[i], &channel, &isABand) != -1)
			{
				tScanParams.u.tScanInfo.channelEntry[i].channel = (unsigned char)channel;
				if (isABand == TRUE)
					tScanParams.u.tScanInfo.numOfAChannels++;
				else
					tScanParams.u.tScanInfo.numOfGChannels++;

				memset(tScanParams.u.tScanInfo.channelEntry[i].bssId, 0xff, 6);
                tScanParams.u.tScanInfo.channelEntry[i].minChannelDwellTime = 30;
				tScanParams.u.tScanInfo.channelEntry[i].maxChannelDwellTime = 60;
				tScanParams.u.tScanInfo.channelEntry[i].txPowerDbm = DEF_TX_POWER;
			}
		}

		if (tScanParams.u.tScanInfo.numOfAChannels == 0 && tScanParams.u.tScanInfo.numOfGChannels > 0)
			tScanParams.u.tScanInfo.band = RADIO_BAND_2_4_GHZ;
		if (tScanParams.u.tScanInfo.numOfAChannels > 0 && tScanParams.u.tScanInfo.numOfGChannels == 0)
		       tScanParams.u.tScanInfo.band = RADIO_BAND_5_0_GHZ;
		if (tScanParams.u.tScanInfo.numOfAChannels > 0 && tScanParams.u.tScanInfo.numOfGChannels > 0)
		       tScanParams.u.tScanInfo.band = RADIO_BAND_DUAL;
	}

       /*Add extra IE's for probe request*/
	if (params->extra_ies_len <= TI_MAX_EXTRA_IES_LEN)
	{
		os_memcpy(tScanParams.aExtraProbeRequestIes, params->extra_ies, params->extra_ies_len);
		tScanParams.uExtraIesLen = params->extra_ies_len;
	}
	else
	{
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error extra IE's buffer too small!!!", __func__);
	}

	/* Send the scan command*/
	if(params->freqs)
	{
		ret = wilink_send_ti_private_cmd(drv, TI_PARAM_START_APP_SCAN, TIWDRV_CMD_SET_FLAG,
										 TIWDRV_PRIV_WEXT_IOCTL, (char *)&tScanParams, sizeof(tScanParams));
		if (ret != 0)
		{
			wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error sending TI_PARAM_START_APP_SCAN command to the driver", __func__);
			ret = -1;
		}
	}
	else
	{
		ret = wilink_send_ti_private_cmd(drv, TI_PARAM_START_OS_SCAN, TIWDRV_CMD_SET_FLAG,
										 TIWDRV_PRIV_WEXT_IOCTL, (char *)&tScanParams, sizeof(tScanParams));
		if (ret != 0)
		{
			wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error sending TI_PARAM_START_OS_SCAN command to the driver", __func__);
			ret = -1;
		}
	}

	return 0;
}

static int tiwdrv_scan(struct wilink_driver_if_data *drv, struct wpa_driver_scan_params *params)
{
	int ret,i;
	int timeout;
	const u8 *ssid;
	size_t ssid_len;
	TRateSets rateSet;
	tiwdrv_gen_ies_t	tGenIes;
	unsigned int wmeEnable = TRUE;
	tiwdrv_ap_rate_set_t  RateParams;
	TScanRequestParams tScanParams;
	int band_2_4_cnt = 0, band_5_0_cnt = 0;
	char bssid[6] = {0xff,0xff,0xff,0xff,0xff,0xff};

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter", __func__);

	os_memset(&rateSet,0,sizeof(rateSet));
	os_memset(&RateParams,0,sizeof(RateParams));
	os_memset(&tScanParams,0,sizeof(tScanParams));

	/* Handle extra IEs */
	if(params->extra_ies_len)
	{
		/*Update probe request frame template with extra IEs*/
		tGenIes.frame_type = TIW_DRV_MGMT_FRAME_PROBE_REQ;
		os_memcpy(tGenIes.ies_buf, params->extra_ies, params->extra_ies_len);
		tGenIes.ies_len = params->extra_ies_len;
		ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_GEN_IE, TIWDRV_CMD_SET_FLAG,
										  TIWDRV_PRIV_WEXT_IOCTL, (char *)&tGenIes, sizeof(tGenIes));
		if (ret)
		{
			wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error sending TI_PARAM_GEN_IE command to the driver", __func__);
			return -1;
		}

		/* Update scan params with extra IEs */
		if (params->extra_ies_len <= TI_MAX_EXTRA_IES_LEN)
		{
			os_memcpy(tScanParams.aExtraProbeRequestIes, params->extra_ies, params->extra_ies_len);
			tScanParams.uExtraIesLen = params->extra_ies_len;
		}
		else
		{
			wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error extra IE's buffer too small!!!", __func__);
		}
	}

	/* Fill SSID */
	ssid = params->ssids[0].ssid;
	ssid_len = params->ssids[0].ssid_len;
	if (ssid_len > IW_ESSID_MAX_SIZE)
	{
		wpa_printf(MSG_ERROR, "%s: too long SSID (%lu)", __func__, (unsigned long) ssid_len);
		return -1;
	}
	if (ssid && ssid_len)
	{
		tScanParams.u.tScanInfo.desiredSsid.len = ssid_len;
		os_memcpy(tScanParams.u.tScanInfo.desiredSsid.str, ssid, ssid_len);
		tScanParams.u.tScanInfo.ssidFilterEnable = TRUE;

	}
	else
	{
		tScanParams.u.tScanInfo.desiredSsid.len = 0; /* scan all*/
		tScanParams.u.tScanInfo.ssidFilterEnable = FALSE;
	}

	/* Fill Channels to scan */
	if(params->freqs)
	{
		for (i=0;params->freqs[i];i++)
		{
			if (params->freqs[i]== FREQ_CH_14)
			{
				tScanParams.u.tScanInfo.channelEntry[i].channel = 14;
				band_2_4_cnt++;
			}
			else if (params->freqs[i]>= BASE_FREQ_5_0 )
			{
				tScanParams.u.tScanInfo.channelEntry[i].channel = (params->freqs[i] - BASE_FREQ_5_0)/5;
				band_5_0_cnt++;
			}
			else if (params->freqs[i]>= BASE_FREQ_2_4 )
			{
                tScanParams.u.tScanInfo.channelEntry[i].channel = (params->freqs[i] - BASE_FREQ_2_4)/5;
				band_2_4_cnt++;
			}
			else
			{
				wpa_printf(MSG_ERROR, "%s: illegal freq  (%d)", __func__, params->freqs[i]);
				return -1;
			}

			memcpy(tScanParams.u.tScanInfo.channelEntry[i].bssId,bssid,6); 
			tScanParams.u.tScanInfo.channelEntry[i].minChannelDwellTime = SCAN_DEFAULT_MIN_CHANNEL_DWELL_TIME;
			tScanParams.u.tScanInfo.channelEntry[i].maxChannelDwellTime = SCAN_DEFAULT_MAX_CHANNEL_DWELL_TIME;
			tScanParams.u.tScanInfo.channelEntry[i].txPowerDbm = DEF_TX_POWER;
			tScanParams.u.tScanInfo.channelEntry[i].ETMaxNumOfAPframes = 0;
			tScanParams.u.tScanInfo.channelEntry[i].earlyTerminationEvent = 0;
		}

		if (band_5_0_cnt == 0 && band_2_4_cnt > 0)
			tScanParams.u.tScanInfo.band = RADIO_BAND_2_4_GHZ;
		if (band_5_0_cnt > 0 && band_2_4_cnt == 0)
		       tScanParams.u.tScanInfo.band = RADIO_BAND_5_0_GHZ;
		if (band_5_0_cnt > 0 && band_2_4_cnt > 0)
		       tScanParams.u.tScanInfo.band = RADIO_BAND_DUAL;
			   
	       tScanParams.u.tScanInfo.numOfGChannels = band_2_4_cnt;
		   tScanParams.u.tScanInfo.numOfAChannels = band_5_0_cnt;
	}

	tScanParams.u.tScanInfo.scanType = SCAN_TYPE_ACTIVE;

       /* Update the Qos mode (Enable/Disable) and the desired rate set*/
	if((drv->drv_role == TIWDRV_IF_MODE_STA) || (drv->drv_role == TIWDRV_IF_MODE_P2PCL))
	{
		wilink_send_ti_private_cmd(drv, TI_PARAM_QOS_ENABLE, TIWDRV_CMD_GET_FLAG,
								   TIWDRV_PRIV_WEXT_IOCTL, (char*)&wmeEnable,sizeof(wmeEnable));
		wilink_send_ti_private_cmd(drv, TI_PARAM_DESIRED_RATE_SET, TIWDRV_CMD_GET_FLAG,
								   TIWDRV_PRIV_WEXT_IOCTL, (char*)&rateSet,sizeof(rateSet));
	}
	else /* For AP & P2PGO use conf file configured rates */
	{
		struct hostapd_data *hapd = tiwdrv_get_hapd_handle(drv);

		if (drv->drv_role == TIWDRV_IF_MODE_P2PGO)
		{
			rateSet.uSuppRatesBitMap = drv->drv_global->tP2pScanParams.tRateSet.uSuppRatesBitMap;
			rateSet.uBasicRatesBitMap = drv->drv_global->tP2pScanParams.tRateSet.uBasicRatesBitMap;
		}
		else
		{
			if( NULL == hapd ) 
            {
             	RateParams.uSupportedRatesBitmap = DRV_RATE_MASK_1_BARKER |
							                       DRV_RATE_MASK_2_BARKER |
							                       DRV_RATE_MASK_5_5_CCK |
							                       DRV_RATE_MASK_11_CCK |
							                       DRV_RATE_MASK_6_OFDM |
							                       DRV_RATE_MASK_9_OFDM |
							                       DRV_RATE_MASK_12_OFDM |
							                       DRV_RATE_MASK_18_OFDM |
							                       DRV_RATE_MASK_24_OFDM |
							                       DRV_RATE_MASK_36_OFDM |
							                       DRV_RATE_MASK_48_OFDM |
							                       DRV_RATE_MASK_54_OFDM;
				
                RateParams.uBasicRatesBitmap = DRV_RATE_MASK_1_BARKER |
						                       DRV_RATE_MASK_2_BARKER |
						                       DRV_RATE_MASK_5_5_CCK |
						                       DRV_RATE_MASK_11_CCK |
						                       DRV_RATE_MASK_6_OFDM |
						                       DRV_RATE_MASK_9_OFDM |
						                       DRV_RATE_MASK_12_OFDM |
						                       DRV_RATE_MASK_18_OFDM;
            }    
			else if(convertRatesToDrvBitmap(hapd->iconf->supported_rates, hapd->iconf->basic_rates, &RateParams) !=0)
			{
				wpa_printf(MSG_ERROR, "%s: No rates are configured", __func__);
				return -1;
			}
			rateSet.uSuppRatesBitMap = RateParams.uSupportedRatesBitmap;
			rateSet.uBasicRatesBitMap = RateParams.uBasicRatesBitmap;
		}
	}
	tScanParams.bWmeEnable = wmeEnable;
	tScanParams.tRateSet = rateSet;

	tScanParams.u.tScanInfo.probeReqNumber = 2;
	if (rateSet.uBasicRatesBitMap & DRV_RATE_MASK_6_OFDM)
		tScanParams.u.tScanInfo.probeRequestRate = PROB_REQ_6M;
	else if (rateSet.uBasicRatesBitMap & DRV_RATE_MASK_5_5_CCK)
		tScanParams.u.tScanInfo.probeRequestRate = PROB_REQ_5_5M;
	else if (rateSet.uBasicRatesBitMap & DRV_RATE_MASK_1_BARKER)
		tScanParams.u.tScanInfo.probeRequestRate = PROB_REQ_1M;
	else 
		tScanParams.u.tScanInfo.probeRequestRate = MAX_PROBE_RATE;

	/* Send the scan command*/
	if(params->freqs)
	{
		ret = wilink_send_ti_private_cmd(drv, TI_PARAM_START_APP_SCAN, TIWDRV_CMD_SET_FLAG,
										 TIWDRV_PRIV_WEXT_IOCTL, (char *)&tScanParams, sizeof(tScanParams));
		if (ret != 0)
		{
			wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error sending TI_PARAM_START_APP_SCAN command to the driver", __func__);
			ret = -1;
		}
	}
	else
	{
		ret = wilink_send_ti_private_cmd(drv, TI_PARAM_START_OS_SCAN, TIWDRV_CMD_SET_FLAG,
										 TIWDRV_PRIV_WEXT_IOCTL, (char *)&tScanParams, sizeof(tScanParams));
		if (ret != 0)
		{
			wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error sending TI_PARAM_START_OS_SCAN command to the driver", __func__);
			ret = -1;
		}
	}

	/*
	 * The driver seems to deliver SIOCGIWSCAN events to notify
	 * when scan is complete, so use longer timeout to avoid race
	 * conditions with scanning and following association request.
	 */
	timeout = 30;
	wpa_printf(MSG_DEBUG, "Scan requested (ret=%d) - scan timeout %d "
		"seconds", ret, timeout);

	eloop_cancel_timeout(wilink_scan_timeout, drv, drv->ctx);
	eloop_register_timeout(timeout, 0, wilink_scan_timeout, drv, drv->ctx);

	return 0;
}

static int wilink_scan(void *priv, struct wpa_driver_scan_params *params)
{
	struct wilink_driver_if_data *drv = (struct wilink_driver_if_data *)priv;

       wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter", __func__);
	/* Enable the role if needed */
	if (drv->drv_role==TIWDRV_IF_MODE_UNKNOWN)
	{
		/*Assume that if scan is called the role can be or STA or P2P Client - determine by ifname */
		int is_p2p = tiwdrv_is_if_p2pgroup(drv);

		drv->drv_role = (is_p2p ? TIWDRV_IF_MODE_P2PCL : TIWDRV_IF_MODE_STA);
		if (tiwdrv_enable_role(drv, drv->drv_role))
			return -1;
	}

	if (drv->drv_role == TIWDRV_IF_MODE_P2PDEV)
	{
		return tiwdrv_p2p_search(drv,params);
	}
	else if ((drv->drv_role == TIWDRV_IF_MODE_STA) || (drv->drv_role == TIWDRV_IF_MODE_P2PCL) ||
			 (drv->drv_role == TIWDRV_IF_MODE_SAP) || (drv->drv_role == TIWDRV_IF_MODE_P2PGO))
	{
		return tiwdrv_scan(drv,params);
	}
	else
	{
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: current driver role (%u) doesn't support scan", __func__, drv->drv_role);
		return -1;
	}
	
       return 0;
}

static int wilink_get_capa(void *priv, struct wpa_driver_capa *capa)
{
	struct wilink_driver_if_data *drv = priv;
	if (!drv->has_capability)
		return -1;
	os_memcpy(capa, &drv->capa, sizeof(*capa));
	return 0;
}


static int wilink_send_ti_private_cmd(struct wilink_driver_if_data *drv, int cmd, int flags,
                                      int ioctl_cmd, char *buffer, int len)
{
	struct iwreq iwr;
	ti_private_cmd_t private_cmd;
	struct wilink_driver_global_data *drv_global = drv->drv_global;

    os_memset(&private_cmd, 0, sizeof(private_cmd));

    private_cmd.cmd = cmd;
	private_cmd.flags = flags;
	private_cmd.in_buffer = buffer;
	private_cmd.in_buffer_len = len;

	if (flags & TIWDRV_CMD_GET_FLAG)
	{
		private_cmd.out_buffer = buffer;
		private_cmd.out_buffer_len = len;
	}

	os_memset(&iwr, 0, sizeof(iwr));
	os_strlcpy(iwr.ifr_name, drv->iface, IFNAMSIZ);

	iwr.u.data.pointer = &private_cmd;
	iwr.u.data.length = sizeof(ti_private_cmd_t);
	iwr.u.data.flags = 0;

    if (ioctl(drv_global->cmd_sock, ioctl_cmd, &iwr) < 0)
    {
		perror("ioctl[ioctl_cmd]");
		return -1;
    }
   return 0;
}

static int wilink_set_broadcast_ssid(void *priv, int value)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_general_param_t GenStruct;
	int ret = 0;

	GenStruct.lValue = (value == 1) ? TIW_DRV_AP_SSID_TYPE_HIDDEN : TIW_DRV_AP_SSID_TYPE_PUBLIC;
	ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_AP_SSID_TYPE, TIWDRV_CMD_SET_FLAG,
										TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenStruct,sizeof(GenStruct));
	return ret;
}


static int wilink_set_privacy(void *priv, int enabled)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_general_param_t GenStruct;
	int ret = 0;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    GenStruct.lValue = enabled;
	ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_SET_PRIVACY, TIWDRV_CMD_SET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenStruct,sizeof(GenStruct));
	return ret;
}


static int wilink_sta_set_flags(void *priv, const u8 *addr,
		int total_flags, int flags_or, int flags_and)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_general_param_t GenStruct;
	int ret = 0;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: total_flags = 0x%x, flags_or = 0x%x, flags_and = 0x%x" MACSTR,__func__, total_flags, flags_or, flags_and, MAC2STR(addr));

    /* If a sta_add command is pending, send it now with the flags */
    if(drv->add_sta_pending)
    {
        drv->add_sta_pending = 0;

        drv->addStaParams.flags = translate_sta_flags_to_drv(total_flags);
        ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_ADD_STATION, TIWDRV_CMD_SET_FLAG,
                                          TIWDRV_PRIV_WEXT_IOCTL, (char*)&drv->addStaParams, sizeof(drv->addStaParams));
    }

    memset(&GenStruct, 0, sizeof(tiwdrv_ap_general_param_t));

    if (addr == NULL)
        return ret;

    memcpy(GenStruct.cMac,addr, TIW_DRV_MAC_ADDR);

	if (flags_or & WPA_STA_AUTHORIZED)
    {
	    GenStruct.lValue = 1;
        ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_AP_PORT_STATUS, TIWDRV_CMD_SET_FLAG,
                                          TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenStruct,sizeof(GenStruct));
    }
	if (!(flags_and & WPA_STA_AUTHORIZED))
    {
	    GenStruct.lValue = 0;
        ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_AP_PORT_STATUS, TIWDRV_CMD_SET_FLAG,
                                          TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenStruct,sizeof(GenStruct));
    }

	if (ret)
    {
        return ret;
    }

	if (flags_or & WPA_STA_WMM)
    {
        GenStruct.lValue = 1;
        ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_SET_STA_WME, TIWDRV_CMD_SET_FLAG,
                                          TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenStruct,sizeof(GenStruct));
    }
	if (!(flags_and & WPA_STA_WMM))
    {
        GenStruct.lValue = 0;
        ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_SET_STA_WME, TIWDRV_CMD_SET_FLAG,
                                          TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenStruct,sizeof(GenStruct));
    }


	if (ret)
    {
        return ret;
    }

    return ret;
}


static int wilink_sta_add(void *priv, struct hostapd_sta_add_params *params)
{
	struct wilink_driver_if_data *drv = priv;
	int ret = 0;

    if (params == NULL)
       return ret;

    wpa_printf(MSG_DEBUG, " ************* HOSTAPTI %s: enter ***********",__func__);

	memcpy(drv->addStaParams.cMac,params->addr, TIW_DRV_MAC_ADDR);

    /* Check station supported length */
    if( params->supp_rates_len > TIW_DRV_MAX_SUPPORT_RATE )
    {
        wpa_printf(MSG_ERROR, "%s: Max supported rates %d from " MACSTR, __func__,
            (int) params->supp_rates_len, MAC2STR(params->addr));

        /*  Update supported rates according to the TIW_DRV_MAX_SUPPORT_RATE */
        params->supp_rates_len = TIW_DRV_MAX_SUPPORT_RATE;

    }

	memcpy(drv->addStaParams.cSupportedRates ,params->supp_rates,params->supp_rates_len);


	drv->addStaParams.cSupportedRatesLen = params->supp_rates_len;
	drv->addStaParams.ilistenInterval = params->listen_interval;
	drv->addStaParams.sAid = params->aid;
	drv->addStaParams.sCapability = params->capability;
	drv->addStaParams.acInfo = (char)params->qosinfo;

	drv->addStaParams.ht_capabilities_info 	= 0;
	drv->addStaParams.a_mpdu_params			= 0;
	os_memset(drv->addStaParams.supported_mcs_set, 0, TIW_DRV_NUM_MCS_SET_BYTES);

	if (params->ht_capabilities)
	{
		drv->addStaParams.ht_capabilities_info   = params->ht_capabilities->ht_capabilities_info;
	    drv->addStaParams.a_mpdu_params          = params->ht_capabilities->a_mpdu_params;
	    memcpy(drv->addStaParams.supported_mcs_set ,params->ht_capabilities->supported_mcs_set,TIW_DRV_NUM_MCS_SET_BYTES);
	}

	wpa_printf(MSG_DEBUG, "%s: "MACSTR, __func__,MAC2STR(params->addr));
	wpa_printf(MSG_DEBUG, "%s: addStaParams.ilistenInterval=%u\n",__func__,drv->addStaParams.ilistenInterval);
	wpa_printf(MSG_DEBUG, "%s: addStaParams.sAid=%u\n",__func__,drv->addStaParams.sAid);

    /* Indicate to issue sta_add command upon next sta_set_flags operation */
    drv->add_sta_pending = 1;

    return ret;
}

static int tiwdrv_init_channel_params(struct hostapd_freq_params *freq, tiwdrv_ap_channel_params_t *pChannelParams)
{
	wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    memset(pChannelParams, 0, sizeof(tiwdrv_ap_channel_params_t));
	pChannelParams->cChannel= freq->channel;

	/* HostAP currently does not support J mode - we only support B/G and A */
	switch(freq->mode)
	{
	case HOSTAPD_MODE_IEEE80211B:
	case HOSTAPD_MODE_IEEE80211G:
		pChannelParams->cBand = RADIO_BAND_2_4GHZ;
		break;
	case HOSTAPD_MODE_IEEE80211A:
		pChannelParams->cBand = RADIO_BAND_5GHZ;
		break;
	default:
		wpa_printf(MSG_ERROR, "HOSTAPTI %s: error invalid hw mode %d",__func__, freq->mode);
		return -1;
	}

	/* 40MHz support - set channel type */
    switch(freq->sec_channel_offset)
	{
	case 0:
		pChannelParams->cChannelType = NLCP_CHAN_HT20;
		break;
	case -1:
		pChannelParams->cChannelType = NLCP_CHAN_HT40MINUS;
		break;
	case 1:
		pChannelParams->cChannelType = NLCP_CHAN_HT40PLUS;
		break;
	default:
		wpa_printf(MSG_ERROR, "HOSTAPTI %s: error secondary channel offsete %d",__func__, freq->sec_channel_offset);
		return -1;
	}

	/* These params are needed to be sent back upon DFS event */
	pChannelParams->cDfsEventParams.freq			= freq->freq;
	pChannelParams->cDfsEventParams.ht_enabled 		= freq->ht_enabled;
	pChannelParams->cDfsEventParams.channel_offset 	= freq->sec_channel_offset;
	pChannelParams->cDfsEventParams.cf1 			= freq->center_freq1;
	pChannelParams->cDfsEventParams.cf2 			= freq->center_freq2;

	switch(freq->bandwidth)
	{
		case 20:
			pChannelParams->cDfsEventParams.chan_width = CHAN_WIDTH_20;
			break;
		case 40:
			pChannelParams->cDfsEventParams.chan_width = CHAN_WIDTH_40;
			break;
		case 80:
			pChannelParams->cDfsEventParams.chan_width = CHAN_WIDTH_80;
			break;
		case 160:
			pChannelParams->cDfsEventParams.chan_width = CHAN_WIDTH_160;
			break;
		default:
			wpa_printf(MSG_ERROR, "HOSTAPTI %s: error bandwidth %d",__func__, freq->bandwidth);
			return -1;
	}

	return 0;
}

static int wilink_set_channel(void *priv, struct hostapd_freq_params *freq)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_channel_params_t ChannelParams;
	int ret = 0;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

	ret  = tiwdrv_init_channel_params(freq, &ChannelParams);

	if(ret)
		return ret;
	
	ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_SET_CHANNEL, TIWDRV_CMD_SET_FLAG,
									  TIWDRV_PRIV_WEXT_IOCTL, (char*)&ChannelParams,sizeof(ChannelParams));

	return ret;

}


static int wilink_sta_remove(void *priv, const u8 *addr)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_general_param_t DelStationParams;
	int ret = 0;

    if (addr == NULL)
       return ret;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    memcpy(DelStationParams.cMac,addr, TIW_DRV_MAC_ADDR);
	ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_REMOVE_STATION, TIWDRV_CMD_SET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, (char*)&DelStationParams,sizeof(DelStationParams));
	return ret;

}


static int wilink_set_ap(void *priv, struct wpa_driver_ap_params *params)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_beacon_params_t BeaconParams;
    int ret = 0;
	struct hostapd_data *hapd = tiwdrv_get_hapd_handle(drv);

    if ((params->head == NULL) || (params->tail == NULL) || (hapd == NULL))
       return -1;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter ",__func__);

    memcpy(BeaconParams.cHead, params->head, params->head_len);
	memcpy(BeaconParams.cTail, params->tail, params->tail_len);
	BeaconParams.iHeadLen = params->head_len;
	BeaconParams.iTailLen = params->tail_len;
	BeaconParams.sBeaconIntval = (unsigned short)params->beacon_int;
	BeaconParams.iDtimIntval = params->dtim_period;

    if (params->proberesp_len > TIW_DRV_MAX_PROBE_RESP_LEN)
        return -1;

    memcpy(BeaconParams.cProbeResp, params->proberesp, params->proberesp_len);
    BeaconParams.iProbeRespLen = params->proberesp_len;

	ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_BEACON_ATTRIBUTES, TIWDRV_CMD_SET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, (char*)&BeaconParams,sizeof(BeaconParams));
    if (ret)
        return ret;

    ret = wilink_ap_set_rate_sets(priv, params->current_rates, params->basic_rates);
    if (ret)
        return ret;

    ret = wilink_set_preamble(priv, params->preamble);
    if (ret)
        return ret;

    ret = wilink_set_short_slot_time(priv, params->short_slot_time);
    if (ret)
        return ret;

    ret = wilink_set_cts_protect(priv, params->cts_protect);
    if (ret)
        return ret;

    ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_SET_AP_WME, TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,
									  (char*)&(hapd->conf->wmm_enabled),sizeof(hapd->conf->wmm_enabled));
	if (ret)
        return ret;

    ret = wilink_set_broadcast_ssid(priv, params->hide_ssid != NO_SSID_HIDING);
    return ret;
}


static int wilink_set_key(const char *ifname, void *priv, enum wpa_alg alg,
                          const u8 *addr, int key_idx, int set_tx,
                          const u8 *seq, size_t seq_len,
                          const u8 *key, size_t key_len)
{
	struct wilink_driver_if_data *drv = priv;
    tiwdrv_ap_general_param_t GenParams;
    TSecurityKeys tKey;
	int ret = 0;


    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

	if ((drv->drv_role == TIWDRV_IF_MODE_UNKNOWN) || (drv->drv_role == TIWDRV_IF_MODE_P2PDEV))
		return 0;

    memset(&tKey,0,sizeof(tKey));
    if (addr)
    {
        memcpy(tKey.macAddress,addr, TIW_DRV_MAC_ADDR);
    }
    else
    {
        memset(tKey.macAddress,0, TIW_DRV_MAC_ADDR);
    }

	if ((drv->drv_role == TIWDRV_IF_MODE_SAP) || (drv->drv_role == TIWDRV_IF_MODE_P2PGO))
    {
        if (alg == WPA_ALG_NONE)
        {
            ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_DEL_KEY, TIWDRV_CMD_SET_FLAG,
                                              TIWDRV_PRIV_WEXT_IOCTL, (char*)&tKey,sizeof(tKey));
        }
        else
        {
            switch (alg)
            {
            case WPA_ALG_TKIP:
                tKey.keyType  = KEY_TKIP;
                break;

            case WPA_ALG_CCMP:
                tKey.keyType  = KEY_AES;
                break;

            case WPA_ALG_IGTK:
                return -1; /* not supported */

            case WPA_ALG_WEP:
            default:
                tKey.keyType  = KEY_WEP;
                break;
            }

            tKey.keyIndex = key_idx;
            tKey.encLen = key_len;

            if ((alg == WPA_ALG_WEP)&& (set_tx))
            {
              GenParams.lValue = tKey.keyIndex;
               wilink_send_ti_private_cmd(drv,TI_PARAM_AP_SET_DEFAULT_KEY, TIWDRV_CMD_SET_FLAG,
                                          TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenParams,sizeof(GenParams));
            }

            if (alg == WPA_ALG_TKIP)
            {
                os_memcpy((tKey.encKey+24),(key+16),8);
                os_memcpy(tKey.micTxKey,(key+16),8);
                os_memcpy(tKey.micRxKey,(key+24),8);
                os_memcpy((tKey.encKey+16),(key+24),8);
                os_memcpy(&tKey.encKey,key,16);
            }
            else
                os_memcpy( tKey.encKey, key, key_len);

            ret = wilink_send_ti_private_cmd(drv, TI_PARAM_ADD_KEY, TIWDRV_CMD_SET_FLAG,
                                        TIWDRV_PRIV_WEXT_IOCTL, (char*) &tKey, sizeof(tKey));
        }
    }
    else /* Role station or P2P client*/
    {
        memset(&tKey, 0, sizeof(TSecurityKeys));

        switch (alg)
        {
        case WPA_ALG_NONE:
            tKey.keyType = KEY_NULL;
            break;
        case WPA_ALG_WEP:
            tKey.keyType = KEY_WEP;
            break;
        case WPA_ALG_TKIP:
            tKey.keyType = KEY_TKIP;
            break;
        case WPA_ALG_CCMP:
            tKey.keyType = KEY_AES;
            break;
		default:
			break;
        }

        tKey.encLen = key_len;
        os_memcpy(tKey.encKey, key, key_len);
        if (alg == WPA_ALG_TKIP)
        {
            os_memcpy(tKey.micRxKey, key+24, TKIP_MIC_LEN);
            os_memcpy(tKey.micTxKey, key+16, TKIP_MIC_LEN);
        }
        tKey.keyIndex = key_idx;

        if (alg != WPA_ALG_WEP)
        {
            if (addr)
                os_memcpy(&tKey.macAddress, addr, sizeof(tKey.macAddress));
        }
        else if (set_tx)
        {
            tKey.keyIndex |= TIWLAN_KEY_FLAGS_TRANSMIT;
        }

        if (seq && seq_len)
        {
            os_memcpy(tKey.keyRsc, seq, seq_len);
        }

        ret = wilink_send_ti_private_cmd(drv, TI_PARAM_ADD_KEY,
                TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, (char *) &tKey,
                sizeof(tKey));
        if (ret != 0)
        {
            wpa_printf(
                    MSG_ERROR,
                    "%s: error sending TI_PARAM_ADD_KEY command to the driver",
                    __func__);

        }

    }

    return ret;
}

static int wilink_commit(void *priv)
{
    struct wilink_driver_if_data *drv = priv;
    tiwdrv_ap_general_param_t GenStruct;
    int ret = 0;
	struct hostapd_data *hapd = tiwdrv_get_hapd_handle(drv);

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: COMMIT", __func__);

    GenStruct.lValue = drv->uInactivity = hapd->conf->ap_max_inactivity;

    ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_START_BSS, TIWDRV_CMD_SET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, (char*)&GenStruct,sizeof(tiwdrv_ap_general_param_t));
    return ret;

}


static int wilink_hapd_set_ssid(void *priv, const u8 *buf, int len)
{
    struct wilink_driver_if_data *drv = priv;
    int ret = 0;
    tiwdrv_ap_ssid_param_t ssidParam;

    if (buf == NULL)
      return ret;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

    if (len > TIW_DRV_MAX_SSID_LEN) {
        wpa_printf(MSG_ERROR, "%s: len is too big", __func__);
        return -1;
    }

    memcpy(ssidParam.cSsid, buf, len);
    ssidParam.iSsidLen = len;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: ssid %s",__func__,ssidParam.cSsid);

    ret  = wilink_send_ti_private_cmd(drv,TI_PARAM_AP_SSID, TIWDRV_CMD_SET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, (char *)&ssidParam,sizeof(ssidParam));
    return ret;
}

static struct hostapd_hw_modes *
 wilink_get_hw_feature_data(void *priv, u16 *num_modes, u16 *flags)
{
    struct wilink_driver_if_data *drv = priv;
    int ret;
    struct hostapd_data *hapd = tiwdrv_get_hapd_handle(drv);

    /* Role STA is managed by the driver*/
	if (drv->drv_role == TIWDRV_IF_MODE_STA)
		return NULL;

	/* Get HW capabilities from the driver*/
   	ret = wilink_send_ti_private_cmd(drv, TI_PARAM_GET_HW_CAP, TIWDRV_CMD_GET_FLAG,
                              TIWDRV_PRIV_WEXT_IOCTL, (char*)drv->drv_global->pRegDomain, sizeof(*drv->drv_global->pRegDomain));
    if (ret != 0)
    {
       wpa_printf(MSG_ERROR, "%s: TI_PARAM_AP_HW failed. returned with: %d",__func__, ret);
       return NULL;
    }

    /* Get HW supported HT capabilities  */
	ret = wilink_send_ti_private_cmd(drv, TI_PARAM_GET_HT_CAP, TIWDRV_CMD_GET_FLAG,
									 TIWDRV_PRIV_WEXT_IOCTL, (char*)drv->drv_global->pHtCapInfo, sizeof(*drv->drv_global->pHtCapInfo));
	if (ret != 0)
	{
		wpa_printf(MSG_ERROR, "%s: TI_PARAM_AP_HT_CAP failed. returned with: %d",__func__, ret);
		return NULL;
	}

    if (hapd)
		build_hw_capability(drv->drv_global->pRegDomainHandle, drv->drv_global->pRegDomain,
							drv->drv_global->pHtCapInfo, hapd->iconf->channel, hapd->iconf->hw_mode);
	else
		build_hw_capability(drv->drv_global->pRegDomainHandle, drv->drv_global->pRegDomain,
							drv->drv_global->pHtCapInfo, 0, NUM_HOSTAPD_MODES);

    *num_modes =  drv->drv_global->pRegDomainHandle->NumOfModes;
	*flags = 0;
    return drv->drv_global->pRegDomainHandle->modes;
}

static void wilink_add_scan_entry(struct wpa_scan_results *res,struct wilink_scan_data *data)
{
	struct wpa_scan_res **tmp;
	struct wpa_scan_res *r;
	size_t extra_len;
	u8 *pos, *end, *ssid_ie = NULL, *rate_ie = NULL;

	/* Figure out whether we need to fake any IEs */
	pos = data->ie;
	end = pos + data->ie_len;
	while (pos && pos + 1 < end) {
		if (pos + 2 + pos[1] > end)
			break;
		if (pos[0] == WLAN_EID_SSID)
			ssid_ie = pos;
		else if (pos[0] == WLAN_EID_SUPP_RATES)
			rate_ie = pos;
		else if (pos[0] == WLAN_EID_EXT_SUPP_RATES)
			rate_ie = pos;
		pos += 2 + pos[1];
	}

	extra_len = 0;
	if (ssid_ie == NULL)
		extra_len += 2 + data->ssid_len;
	if (rate_ie == NULL && data->maxrate)
		extra_len += 3;

	r = os_zalloc(sizeof(*r) + extra_len + data->ie_len);
	if (r == NULL)
		return;
	os_memcpy(r, &data->res, sizeof(*r));
	r->ie_len = extra_len + data->ie_len;
	pos = (u8 *) (r + 1);
	if (ssid_ie == NULL) {
		/*
		 * Generate a fake SSID IE since the driver did not report
		 * a full IE list.
		 */
		*pos++ = WLAN_EID_SSID;
		*pos++ = data->ssid_len;
		os_memcpy(pos, data->ssid, data->ssid_len);
		pos += data->ssid_len;
	}
	if (rate_ie == NULL && data->maxrate) {
		/*
		 * Generate a fake Supported Rates IE since the driver did not
		 * report a full IE list.
		 */
		*pos++ = WLAN_EID_SUPP_RATES;
		*pos++ = 1;
		*pos++ = data->maxrate;
	}
	if (data->ie)
		os_memcpy(pos, data->ie, data->ie_len);

	tmp = os_realloc(res->res,
			 (res->num + 1) * sizeof(struct wpa_scan_res *));
	if (tmp == NULL) {
		os_free(r);
		return;
	}
	tmp[res->num++] = r;
	res->res = tmp;
}



struct wpa_scan_results * wilink_get_scan_results(void *priv)
{
    struct wilink_driver_if_data *drv = (struct wilink_driver_if_data *) priv;
    int listSize, numEntries, j, i = 0;
    struct wpa_scan_results *res = 0;
    struct wilink_scan_data tmpData;
    int rates_allocated_size;
    OS_802_11_BSSID_LIST_EX *my_list = 0;
    OS_802_11_N_RATES *rate_list = 0;
    OS_802_11_BSSID_EX *my_current;
    uint8_t *current_rates;
    int offset;
    int maxrate;
    int tmpRate;

    wpa_printf(MSG_DEBUG, " HOSTAPTI %s: enter", __func__);


    /* First get the amount of memory required to hold the entire BSSID list by setting the length to 0 */
    if (wilink_send_ti_private_cmd(drv, TI_PARAM_BSSID_LIST_SIZE,
            TIWDRV_CMD_GET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, (char *) &listSize,
            sizeof(listSize)) != 0)
    {
        wpa_printf(
                MSG_ERROR,
                "%s: error sending TI_PARAM_BSSID_LIST_SIZE command to the driver",
                __func__);
        return 0;
    }


       /* Allocate required memory */
    my_list = os_malloc(listSize);
    if (!my_list)
    {
        wpa_printf(MSG_ERROR, "%s: error allocating memory for rate_list",
                __func__);
        return NULL;
    }

    /* Lock the scan results allocated buffer in RAM*/
    if (mlock(my_list, listSize) != 0)
    {
        wpa_printf(MSG_ERROR, "%s: mlock error", __func__);
        os_free(my_list);
        return NULL;
    }
    /* And retrieve the list */
    if (wilink_send_ti_private_cmd(drv, TI_PARAM_BSSID_LIST,
            TIWDRV_CMD_GET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, (char *) my_list,
            listSize) != 0)
    {
        wpa_printf(MSG_ERROR, "%s: error sending TI_PARAM_BSSID_LIST command to the driver", __func__);
        os_free(my_list);
        return NULL;
    }

    if (munlock(my_list, listSize) != 0)
    {
        wpa_printf(MSG_ERROR, "%s: munlock error", __func__);
        os_free(my_list);
        return NULL;
    }

    /* Get the number of entries in the scan result list and allocate enough memory to hold rate list
     for every entry. This rate list is extended to include 11n rates */
    if (wilink_send_ti_private_cmd(drv, TI_PARAM_NUM_BSSID_IN_LIST,
            TIWDRV_CMD_GET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, (char *) &numEntries,
            sizeof(numEntries)) != 0)
    {
        wpa_printf(
                MSG_ERROR,
                "%s: error sending TI_PARAM_NUM_BSSID_IN_LIST command to the driver",
                __func__);
        os_free(my_list);
        return NULL;
    }
    /* Populate wpa_scan_results with results */
	res = os_zalloc(sizeof(*res));
	if (res == NULL)
	{
		os_free(my_list);
		return NULL;
	}

	/* Check the amount of scan results, if no results return */
	if(0 == numEntries)
	{
		wpa_printf(MSG_DEBUG, "%s: no results from scan", __func__);
		os_free(my_list);
		return res;
	}

    rates_allocated_size = numEntries * sizeof(OS_802_11_N_RATES);

    /* Allocate required memory */
    rate_list = os_malloc(rates_allocated_size);
    if (!rate_list)
    {
        wpa_printf(MSG_ERROR, "%s: error allocating memory for rate_list",
                __func__);
        os_free(my_list);
        os_free(res);
        return NULL;
    }

    /* And retrieve the list */

    if (wilink_send_ti_private_cmd(drv, TI_PARAM_BSSID_RATE_LIST,
            TIWDRV_CMD_GET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, (char *) rate_list,
            rates_allocated_size) != 0)
    {
        wpa_printf(
                MSG_ERROR,
                "%s: error sending TI_PARAM_BSSID_RATE_LIST command to the driver",
                __func__);
        os_free(my_list);
        os_free(rate_list);
        os_free(res);
        return NULL;
    }

    my_current = &my_list->Bssid[0];

    for (i = 0; i < my_list->NumberOfItems; i++)
    {
        os_memset(&tmpData, 0, sizeof(tmpData));

        /* Add BSSID */
        os_memcpy(tmpData.res.bssid, my_current->MacAddress, ETH_ALEN);

        /* add mode (infrastructure or Adhoc) */
        if (my_current->InfrastructureMode == os802_11IBSS)
        {
            tmpData.res.caps |= IEEE80211_CAP_IBSS;
        }
        else if (my_current->InfrastructureMode == os802_11Infrastructure)
        {
            tmpData.res.caps |= IEEE80211_CAP_ESS;
        }

        /* Add SSID */
        tmpData.ssid_len
                = (my_current->Ssid.SsidLength < 32) ? my_current->Ssid.SsidLength
                        : 32;
        os_memcpy(tmpData.ssid, my_current->Ssid.Ssid, tmpData.ssid_len);

        /* add freq */
        tmpData.res.freq = my_current->Configuration.Union.channel / 1000;

        /* Add quality statistics */
        tmpData.res.qual = 0;
        tmpData.res.noise = 0;
        tmpData.res.level = my_current->Rssi;

        /* Add encryption capability */
        if ((my_current->Capabilities >> CAP_PRIVACY_SHIFT) & CAP_PRIVACY_MASK)
        {
            tmpData.res.caps |= IEEE80211_CAP_PRIVACY;
        }

        /* add rate */
        current_rates = (uint8_t *) (rate_list[i]);
        maxrate = 0;
        for (j = 0; j < 32; j++)
        {
            if (current_rates[j])
            {
                tmpRate = tiwdrv_rate_to_double_value(current_rates[j]);

                if (tmpRate > maxrate)
                {
                    maxrate = tmpRate;
                }
            }
        }
        tmpData.maxrate = maxrate;

        /* add ALL variable IEs */
        offset = sizeof(OS_802_11_FIXED_IEs);
        while (offset < my_current->IELength)
        {
            OS_802_11_VARIABLE_IEs *pIE;
            u8 *tmp;

            pIE = (OS_802_11_VARIABLE_IEs*) &(my_current->IEs[offset]);

            tmp = os_realloc(tmpData.ie, tmpData.ie_len + pIE->Length + 2);
            if (tmp == NULL)
            {
                wpa_printf(MSG_ERROR,
                        "%s: error allocating memory for tmpData->ie\n",
                        __func__);
                return 0;
            }

            os_memcpy(tmp + tmpData.ie_len, &(my_current->IEs[offset]), pIE->Length + 2);
            tmpData.ie = tmp;
            tmpData.ie_len += pIE->Length + 2;

            offset += pIE->Length + 2;
        }

        wilink_add_scan_entry(res, &tmpData);
        os_free(tmpData.ie);

        my_current = (OS_802_11_BSSID_EX *) (((char *) my_current)
                + my_current->Length);
    }

    os_free(my_list);
    os_free(rate_list);

    wpa_printf(MSG_DEBUG, "Received %lu bytes of scan results (%lu BSSes)",
            (unsigned long) listSize, (unsigned long) res->num);

    return res;
}


static int wilink_probe_req_report(void *priv, int report)
{
	struct wilink_driver_if_data *drv = (struct wilink_driver_if_data *)priv;
	int ret;

	if (drv->drv_role == TIWDRV_IF_MODE_P2PDEV)
	{
		ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_SET_PROBEREQ_REPORT, TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,
										  (char *)&report, sizeof(report));
		if (ret)
		{
			wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error sending TI_PARAM_SET_PROBEREQ_REPORT command to the driver", __func__);
			return -1;
		}
	}
	return 0;
}


static int wilink_remain_on_channel(void *priv, unsigned int freq, unsigned int duration)
{
	struct wilink_driver_if_data *drv = (struct wilink_driver_if_data *)priv;
	tiwdrv_p2p_remain_on_ch_params_t params;
	unsigned int isABand = 0;
	int ret;

	wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: frequency = %u", __func__, freq);

	ret = freq_to_channel(freq, &params.channel, &isABand);
	if (ret || !duration)
	{
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: failed to convert frequency %d to channel", __func__, freq);
		return -1;
	}

	params.duration = duration;
	params.band = isABand ? RADIO_BAND_5_0_GHZ: RADIO_BAND_2_4_GHZ;
	ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_REMAIN_ON_CH, TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,
                                      (char *)&params, sizeof(params));
	if (ret)
	{
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error sending TI_PARAM_REMAIN_ON_CH command to the driver", __func__);
		return -1;
	}

	return 0;
}


static int wilink_cancel_remain_on_channel(void *priv)
{
	struct wilink_driver_if_data *drv = (struct wilink_driver_if_data *)priv;
	int ret;

	ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_CANCEL_REMAIN_ON_CH, TIWDRV_CMD_SET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, NULL, 0);
	if (ret)
	{
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error sending TI_PARAM_CANCEL_REMAIN_ON_CH command to the driver", __func__);
		return -1;
	}
	return 0;
}


static int wilink_if_add(void *priv, enum wpa_driver_if_type type,
		      const char *ifname, const u8 *addr, void *bss_ctx,
		      void **drv_priv, char *force_ifname, u8 *if_addr,
		      const char *bridge, int use_existing)
{
	struct wilink_driver_if_data *drv = (struct wilink_driver_if_data *)priv;

   	wpa_printf(MSG_ERROR, "HOSTAPTIW %s: type = %u, ifname=%s\n", __func__, type, ifname);
	switch(type)
	{
	case WPA_IF_AP_BSS:
	case WPA_IF_AP_VLAN:
		os_strlcpy(force_ifname, NETIF_NAME(TIWLAN_DEV_NAME_SAP), IFNAMSIZ);
		break;
	case WPA_IF_P2P_CLIENT:
	case WPA_IF_P2P_GO:
	case WPA_IF_P2P_GROUP:
        /* we need the p2p-group interface up to get its mac addr */
		(void)linux_set_iface_flags(drv->drv_global->cmd_sock, NETIF_NAME(TIWLAN_DEV_NAME_P2PGROUP), 1);
		os_strlcpy(force_ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2PGROUP), IFNAMSIZ);
		break;
	case WPA_IF_STATION:
		os_strlcpy(force_ifname, NETIF_NAME(TIWLAN_DEV_NAME_STA), IFNAMSIZ);
		break;
	default:
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: unknown if type: %u, ifname=%s\n", __func__, type, ifname);
		return -1;
	}

	if (addr)
		os_memcpy(if_addr, addr, ETH_ALEN);

	if (!addr &&
		linux_get_ifhwaddr(drv->drv_global->cmd_sock, force_ifname, if_addr) < 0)
	{
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: failed to get HWADDR from interface %s\n", __func__, force_ifname);
		return -1;
	}

	return 0;
}

static int wilink_send_action(void *priv, unsigned int freq,
                              unsigned int wait_time,
                              const u8 *dst, const u8 *src,
                              const u8 *bssid,
                              const u8 *data, size_t data_len,
			      int no_cck)
{
	int ret;
	u8 *buf;
	struct ieee80211_hdr *hdr;

    wpa_printf(MSG_DEBUG, " HOSTAPTIW %s: sending %u byte action frame to " MACSTR, __func__, data_len, MAC2STR(dst));

	buf = os_zalloc(WLAN_HDR_LEN + data_len);
	if (buf == NULL)
		return -1;
	os_memcpy(buf + WLAN_HDR_LEN, data, data_len);
	hdr = (struct ieee80211_hdr *) buf;
	hdr->frame_control =
		IEEE80211_FC(WLAN_FC_TYPE_MGMT, WLAN_FC_STYPE_ACTION);
	os_memcpy(hdr->addr1, dst, ETH_ALEN);
	os_memcpy(hdr->addr2, src, ETH_ALEN);
	os_memcpy(hdr->addr3, bssid, ETH_ALEN);

	ret = wilink_send_mgmt_frame(priv, buf, data_len + WLAN_HDR_LEN, 0);
	if (ret)
	{
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: failed to send managment frame to the driver", __func__);
		os_free(buf);
		return ret;
	}

	os_free(buf);
	return 0;
}
static int wilink_update_ft_ies(void *priv, const u8 *md, const u8 *ies, size_t ies_len)
{
    struct wilink_driver_if_data *drv = priv;
    int ret;

    wpa_printf(MSG_ERROR, "HOSTAPTIW %s: enter, ies_len = %u",__func__, ies_len);

    if (wilink_send_ti_private_cmd(drv, TI_PARAM_UPDATE_FT_IES,
            TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,
            (char *) ies, ies_len) != 0)
    {
        wpa_printf(MSG_ERROR,
                "%s: error sending TI_PARAM_UPDATE_FT_IES command to the driver",
                __func__);
        ret = -1;
    }

    return 0;
}

static int wilink_associate(void *priv,struct wpa_driver_associate_params *params)
{
	struct wilink_driver_if_data *drv = priv;
    int ret = 0;
    rsnGenericIE_t tRsnGenericIe;
    EExternalAuthMode eExternalAuthMode;
    TrsnEncryptionStatus tCipherSuite;
    TSsid tDesiredSsid;
    int wps_enabled;

    wpa_printf(MSG_ERROR, "HOSTAPTIW %s: enter, mode = %u role %d iface %s",
    	       __func__, params->mode, drv->drv_role, drv->iface);

    /*Deterimine driver role if not known yet and enable it */
	if (drv->drv_role == TIWDRV_IF_MODE_UNKNOWN)
	{
		int is_p2p = tiwdrv_is_if_p2pgroup(drv);

		switch (params->mode)
		{
		case IEEE80211_MODE_AP:
			/*For AP-like role just enable role and return*/
			drv->drv_role = (is_p2p ? TIWDRV_IF_MODE_P2PGO : TIWDRV_IF_MODE_SAP);
			return tiwdrv_enable_role(drv, drv->drv_role);
		case IEEE80211_MODE_IBSS:
			return 0;
		default:
			drv->drv_role = (is_p2p ? TIWDRV_IF_MODE_P2PCL : TIWDRV_IF_MODE_STA);
			if (tiwdrv_enable_role(drv, drv->drv_role))
				return -1;
			break;
		}
	}

	/*Station associate comes here*/

	/* Change GENIE */
    tRsnGenericIe.length = params->wpa_ie_len;
    os_memcpy(tRsnGenericIe.data, params->wpa_ie, tRsnGenericIe.length);
    if (wilink_send_ti_private_cmd(drv, TI_PARAM_WPA_IE,
            TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,
            (char *) &tRsnGenericIe, sizeof(tRsnGenericIe)) != 0)
    {
        wpa_printf(MSG_ERROR,
                "%s: error sending TI_PARAM_WPA_IE command to the driver",
                __func__);
        ret = -1;
    }

    /* Set authentication mode */
    if (params->wpa_ie == NULL || params->wpa_ie_len == 0)
    {
        if (params->auth_alg & WPA_DRIVER_AUTH_SHARED)
        {
            if (params->auth_alg & WPA_DRIVER_AUTH_OPEN)
            {
                 eExternalAuthMode = RSN_EXT_AUTH_MODE_AUTO_SWITCH;
            }
            else
            {
                 eExternalAuthMode = RSN_EXT_AUTH_MODE_SHARED_KEY;
            }
        }
        else
        {
            eExternalAuthMode = RSN_EXT_AUTH_MODE_OPEN;
        }
    }
    else if (params->wpa_ie[0] == WLAN_EID_RSN)
    {
    	if (KEY_MGMT_PSK == params->key_mgmt_suite) {
        	eExternalAuthMode = RSN_EXT_AUTH_MODE_WPA2PSK;
    	} else {
    		eExternalAuthMode = RSN_EXT_AUTH_MODE_WPA2;
    	}
    }
    else
    {
    	if (KEY_MGMT_PSK == params->key_mgmt_suite) {
        	eExternalAuthMode = RSN_EXT_AUTH_MODE_WPAPSK;
		} else {
			eExternalAuthMode = RSN_EXT_AUTH_MODE_WPA;
		}
    }

    if (wilink_send_ti_private_cmd(priv, TI_PARAM_EXT_AUTHENTICATION_MODE,
            TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,
            (char *) &eExternalAuthMode, sizeof(eExternalAuthMode)) != 0)
    {
        wpa_printf(
                MSG_ERROR,
                "%s: error sending TI_PARAM_EXT_AUTHENTICATION_MODE command to the driver",
                __func__);
        ret = -1;
    }

    /* Change cipher type */
    switch (params->pairwise_suite)
    {
    case CIPHER_NONE:
        tCipherSuite.eRsnEncrPairwise = TWD_CIPHER_NONE;
        break;
    case CIPHER_WEP104:
    case CIPHER_WEP40:
        tCipherSuite.eRsnEncrPairwise = TWD_CIPHER_WEP;
        break;
    case CIPHER_TKIP:
        tCipherSuite.eRsnEncrPairwise = TWD_CIPHER_TKIP;
        break;
    case CIPHER_CCMP:
        tCipherSuite.eRsnEncrPairwise = TWD_CIPHER_AES_CCMP;
        break;
    }

    switch (params->group_suite)
    {
    case CIPHER_NONE:
        tCipherSuite.eRsnEncrGroup = TWD_CIPHER_NONE;
        break;
    case CIPHER_WEP104:
    case CIPHER_WEP40:
        tCipherSuite.eRsnEncrGroup = TWD_CIPHER_WEP;
        break;
    case CIPHER_TKIP:
        tCipherSuite.eRsnEncrGroup = TWD_CIPHER_TKIP;
        break;
    case CIPHER_CCMP:
        tCipherSuite.eRsnEncrGroup = TWD_CIPHER_AES_CCMP;
        break;
    }

     if (params->freq)
       drv->assoc_freq = params->freq;
	 else
		drv->assoc_freq = 0;

    if (wilink_send_ti_private_cmd(priv, TI_PARAM_ENCRYPTION_STATUS,
            TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,
            (char *) &tCipherSuite, sizeof(tCipherSuite)) != 0)
    {
        wpa_printf(
                MSG_ERROR,
                "%s: error sending TI_PARAM_ENCRYPTION_STATUS command to the driver",
                __func__);
        ret = -1;
    }


    /* configure WPS */
    if (params->key_mgmt_suite == KEY_MGMT_WPS)
        wps_enabled = 1;
    else
        wps_enabled = 0;


    if (wilink_send_ti_private_cmd(priv, TI_PARAM_SIMPLE_CONFIG_MODE,
            TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,
            (char *) &wps_enabled, sizeof(wps_enabled)) != 0)
    {
        wpa_printf(
                MSG_ERROR,
                "%s: error sending TI_PARAM_SIMPLE_CONFIG_MODE command to the driver",
                __func__);
        ret = -1;
    }

    if (!params->bssid || tidrv_set_bssid(drv, params->bssid) < 0)
    {
        wpa_printf(MSG_ERROR, "%s: error setting bssid", __func__);
        return -1;
    }

    tDesiredSsid.len = params->ssid_len;
    os_memcpy(tDesiredSsid.str, params->ssid, params->ssid_len);

    /* Change SSID */
    if (wilink_send_ti_private_cmd(priv, TI_PARAM_DESIRED_SSID,
            TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,
            (char *) &tDesiredSsid, sizeof(tDesiredSsid)) != 0)
    {
        wpa_printf(
                MSG_ERROR,
                "%s: error sending TI_PARAM_DESIRED_SSID command to the driver",
                __func__);
        ret = -1;
    }

    /* TODO: transfer this to the kernel and use it */
    if (drv->wpa_s->roaming_to_specific_ap)
        wpa_printf(MSG_DEBUG, "%s: connection due to roaming to specific AP",
                   __func__);

    /* also set it to the SME */
    if (wilink_send_ti_private_cmd(priv, TI_PARAM_CONNECT,
            TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,
            (char *) &tDesiredSsid, sizeof(tDesiredSsid)) != 0)
    {
        wpa_printf(
                MSG_ERROR,
                "%s: error sending TI_PARAM_CONNECT command to the driver",
                __func__);
        ret = -1;
    }

    return ret;
}


static int wilink_send_mgmt_frame(void *priv, const u8 *data, size_t data_len,
				  int noack)
{
	struct wilink_driver_if_data *drv = priv;
	const struct ieee80211_mgmt *mgmt = (struct ieee80211_mgmt *)data;

    wpa_printf(MSG_MSGDUMP, " HOSTAPTI %s: sending %d byte MGMT frame to " MACSTR, __func__,
			(int)data_len, MAC2STR(mgmt->da));
	wpa_hexdump(MSG_MSGDUMP, "MGMT", data, data_len);
    wpa_printf(MSG_MSGDUMP,"\n");

    return (l2_packet_send(drv->mlme_l2, mgmt->da, TIWDRV_MGMT_ETH_TYPE, data, data_len) < 0);
}


static int tiwdrv_get_info(struct wilink_driver_if_data *drv)
{
    drv->has_capability = 1;
    wilink_get_we_version(drv);

    drv->capa.key_mgmt |= WPA_DRIVER_CAPA_KEY_MGMT_WPA
            | WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK | WPA_DRIVER_CAPA_KEY_MGMT_WPA2
            | WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK
            | WPA_DRIVER_CAPA_KEY_MGMT_FT | WPA_DRIVER_CAPA_KEY_MGMT_FT_PSK;

    drv->capa.enc |= WPA_DRIVER_CAPA_ENC_WEP40 | WPA_DRIVER_CAPA_ENC_WEP104
            | WPA_DRIVER_CAPA_ENC_TKIP | WPA_DRIVER_CAPA_ENC_CCMP;

    drv->capa.auth = WPA_DRIVER_AUTH_OPEN | WPA_DRIVER_AUTH_SHARED
            | WPA_DRIVER_AUTH_LEAP;

    /* we support probe response offload */
    drv->capa.flags |= WPA_DRIVER_FLAGS_PROBE_RESP_OFFLOAD;
    drv->capa.probe_resp_offloads =
        WPA_DRIVER_PROBE_RESP_OFFLOAD_WPS |
        WPA_DRIVER_PROBE_RESP_OFFLOAD_WPS2 |
        WPA_DRIVER_PROBE_RESP_OFFLOAD_P2P;

    /* scan related settings */
    drv->capa.max_scan_ssids = 1;
    drv->capa.max_sched_scan_ssids = 16;
    drv->capa.max_match_sets = 16;
    drv->capa.sched_scan_supported = 1;
    drv->capa.sched_scan_intervals_supported = 1;

    /* p2p related settings */
    drv->capa.flags |= WPA_DRIVER_FLAGS_P2P_CAPABLE |
                       WPA_DRIVER_FLAGS_P2P_CONCURRENT |
		       WPA_DRIVER_FLAGS_P2P_MGMT_AND_NON_P2P;
    drv->capa.max_remain_on_chan = 5000;

    /* Tx status reporting support */
    drv->capa.flags |= WPA_DRIVER_FLAGS_DEAUTH_TX_STATUS;

    /* Trust driver association errors */
    drv->capa.flags |= WPA_DRIVER_FLAGS_SANE_ERROR_CODES;

    /* AP related settings */
    drv->capa.max_stations = 8;
    drv->capa.flags |= WPA_DRIVER_FLAGS_AP |
                       WPA_DRIVER_FLAGS_AP_UAPSD;
	drv->capa.flags |= WPA_DRIVER_FLAGS_RADAR;
	drv->capa.flags |= WPA_DRIVER_FLAGS_AP_CSA;

    wpa_printf(MSG_DEBUG, " HOSTAPTIW : driver capabilities: key_mgmt 0x%x enc 0x%x "
           "flags 0x%x", drv->capa.key_mgmt, drv->capa.enc, drv->capa.flags);

	return 0;
}


/* Get TI Wilink driver role by interface name */
static tiwdrv_if_mode_e tiwdrv_get_drv_role(struct wilink_driver_if_data *drv)
{
	if (!os_strcmp(drv->iface, NETIF_NAME(TIWLAN_DEV_NAME_P2PDEV)))
		return TIWDRV_IF_MODE_P2PDEV;

    if (!os_strcmp(drv->iface, NETIF_NAME(TIWLAN_DEV_NAME_SAP)))
		return TIWDRV_IF_MODE_SAP;

    if (!os_strcmp(drv->iface, NETIF_NAME(TIWLAN_DEV_NAME_STA)))
		return TIWDRV_IF_MODE_STA;

	return 	TIWDRV_IF_MODE_UNKNOWN;
}

#ifdef ENABLE_USER_DEFAULTS
static char* prepare_enable_role_buff (tiwdrv_if_mode_e role_type, size_t *length)
{
	FILE *f = NULL;
	char* buf;

	wpa_printf(MSG_ERROR, "In %s: roleType --> %d ",__func__, role_type);

	switch (role_type)
	{
	case TIWDRV_IF_MODE_STA:
		f = fopen(TLV_BIN_FILE_NAME_ROLE_STA, "rb");
		break;
	case TIWDRV_IF_MODE_SAP:
	case TIWDRV_IF_MODE_P2PGO:
		f = fopen(TLV_BIN_FILE_NAME_ROLE_AP, "rb");
		break;
	case TIWDRV_IF_MODE_P2PCL:
		f = fopen(TLV_BIN_FILE_NAME_ROLE_P2PCL, "rb");
		break;
	case TIWDRV_IF_MODE_P2PDEV:
	{
		buf = os_malloc(sizeof(tiwdrv_if_mode_e));
		*((tiwdrv_if_mode_e*)buf) = role_type;
		*length = sizeof(tiwdrv_if_mode_e);
		return buf;
	}

	default:
		wpa_printf(MSG_ERROR, "In %s, Unknown Role Type!!!!!! ", __func__);
		break;
	}

	if (f == NULL)
	{
		wpa_printf(MSG_ERROR, "In %s ,Failed to open bin file!!!!!! ", __func__);
		return NULL;
	}

	fseek(f, 0, SEEK_END);
	*length = ftell(f);

	fseek(f, 0, SEEK_SET);

	buf = os_malloc(*length + sizeof(tiwdrv_if_mode_e));

	if (buf == NULL) {
			fclose(f);
			return NULL;
		}

	*((tiwdrv_if_mode_e*)buf) = role_type;

	if (fread(buf + sizeof(tiwdrv_if_mode_e), 1, *length, f) != *length)
	{
		wpa_printf(MSG_ERROR, "In %s: Error while reading file. ",__func__);
		fclose(f);
		os_free(buf);
		return NULL;
	}

	*length += sizeof(tiwdrv_if_mode_e); /* the total size of the enable role command */
	fclose(f);

	return buf;
}
#endif


static int tiwdrv_enable_role (struct wilink_driver_if_data *drv, tiwdrv_if_mode_e role_type)
{
	int ret = 0;
#ifdef ENABLE_USER_DEFAULTS
	char* 	cmdBuff = NULL;
	size_t  cmdLen = 0;
#endif

   	wpa_printf(MSG_ERROR, "HOSTAPTIW %s: enter",__func__);

#ifdef ENABLE_USER_DEFAULTS
	cmdBuff = prepare_enable_role_buff(role_type, &cmdLen);

	if (cmdBuff != NULL)
	{
		ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_ENABLE_ROLE, TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL, cmdBuff, (int)cmdLen);
		os_free(cmdBuff);
	}
	else
	{
		wpa_printf(MSG_ERROR, "%s: Error while preparing enable role buff,  enableRole command will not be sent!! ",__func__);
	}

#else
	ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_ENABLE_ROLE, TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,(char *)&role_type, sizeof(role_type));
#endif

	if (ret){
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error sending ENABLE_ROLE command for type %u to the driver", __func__, role_type);
		return -1;
	}

	wilink_toggle_events(drv, TI_PARAM_REGISTER_EVENT);

	return 0;
}

static int tiwdrv_disable_role (struct wilink_driver_if_data *drv)
{
	unsigned int country_updated = drv->country_updated;

    /* unregister from events */
    wilink_toggle_events(drv, TI_PARAM_UNREGISTER_EVENT);

    /* send the command to the driver */
    return wilink_send_ti_private_cmd(drv, TI_PARAM_DISABLE_ROLE,
						TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,
						(char *)&country_updated, sizeof(country_updated));
}
/*Download configuration corresponding to the wilink driver role*/
static int tiwdrv_config_role(struct wilink_driver_if_data *drv)
{
	switch (drv->drv_role)
	{
	case TIWDRV_IF_MODE_P2PDEV:
	case TIWDRV_IF_MODE_STA:
	case TIWDRV_IF_MODE_SAP:
	case TIWDRV_IF_MODE_P2PCL:
	case TIWDRV_IF_MODE_P2PGO:
	case TIWDRV_IF_MODE_IBSS:
		break;
	default:
		wpa_printf(MSG_WARNING, "HOSTAPTIWERR %s: unknown TI Wilink driver role %d", __func__, drv->drv_role);
	}
	return 0;
}


static void tiwdrv_init_p2p_scan_params(struct wilink_driver_global_data *drv_global)
{
	int i,j;

	os_memset(&drv_global->tP2pScanParams, 0, sizeof(TScanRequestParams));

    drv_global->tP2pScanParams.u.tScanInfo.scanType = SCAN_TYPE_ACTIVE;
	drv_global->tP2pScanParams.u.tScanInfo.band = TIWDRV_RADIO_BAND_2_4_GHZ;
	drv_global->tP2pScanParams.u.tScanInfo.probeReqNumber = 3;
	drv_global->tP2pScanParams.bWmeEnable = FALSE;
	drv_global->tP2pScanParams.tRateSet.uBasicRatesBitMap = 
		DRV_RATE_MASK_6_OFDM |
		DRV_RATE_MASK_12_OFDM |
		DRV_RATE_MASK_24_OFDM;
	drv_global->tP2pScanParams.tRateSet.uSuppRatesBitMap =
		DRV_RATE_MASK_6_OFDM |
		DRV_RATE_MASK_9_OFDM |
		DRV_RATE_MASK_12_OFDM |
		DRV_RATE_MASK_18_OFDM |
		DRV_RATE_MASK_24_OFDM |
		DRV_RATE_MASK_36_OFDM |
		DRV_RATE_MASK_48_OFDM |
		DRV_RATE_MASK_54_OFDM;

    drv_global->tP2pScanParams.u.tScanInfo.probeRequestRate = PROB_REQ_6M;
	drv_global->tP2pScanParams.u.tScanInfo.numOfGChannels = 13; /* no p2p scan on channel 14 */
    for ( i = 0; i < 13; i++ )
	{
		for ( j = 0; j < 6; j++ )
		{
			drv_global->tP2pScanParams.u.tScanInfo.channelEntry[ i ].bssId[ j ] = 0xff;
		}
		drv_global->tP2pScanParams.u.tScanInfo.channelEntry[ i ].maxChannelDwellTime = 60;
		drv_global->tP2pScanParams.u.tScanInfo.channelEntry[ i ].minChannelDwellTime = 30;
		drv_global->tP2pScanParams.u.tScanInfo.channelEntry[ i ].txPowerDbm = DEF_TX_POWER;
		drv_global->tP2pScanParams.u.tScanInfo.channelEntry[ i ].channel = i + 1;
	}

}

static struct hostapd_data * tiwdrv_get_hapd_handle(struct wilink_driver_if_data *drv)
{
	if (drv->drv_role == TIWDRV_IF_MODE_SAP)
	{
		return drv->hapd;
	}
#ifndef HOSTAPD
#ifdef CONFIG_AP
	else if (drv->drv_role == TIWDRV_IF_MODE_P2PGO)
	{
		return drv->wpa_s->ap_iface->bss[0];
	}
#endif
#endif
	else
	{
		wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: hapd handle is NULL!!!", __func__);
		return NULL;
	}
}

static int tiwdrv_is_if_p2pgroup(struct wilink_driver_if_data *drv)
{
	if (!os_strcmp(drv->iface, NETIF_NAME(TIWLAN_DEV_NAME_P2PGROUP)))
		return 1;
	else
		return 0;
}

static int freq_to_channel(unsigned int freq, u32 *channel, unsigned int *is5GBand)
{
	if (freq >= 2412 && freq <= 2472) {
		*channel = (freq - BASE_FREQ_2_4) / 5;
		*is5GBand = FALSE;
        return 0;
	}

	if (freq == 2484) {
		*channel = 14;
		*is5GBand = FALSE;
		return 0;
	}

    if (freq >= 5180 && freq <= 5240) {
        *channel = (freq - BASE_FREQ_5_0) / 5;
		*is5GBand = TRUE;
        return 0;
    }

    if (freq >= 5745 && freq <= 5825) {
        *channel = (freq - BASE_FREQ_5_0) / 5;
		*is5GBand = TRUE;
        return 0;
    }
	return -1;
}

static int channel_to_freq(u32 channel, unsigned int *freq)
{
	if (channel < 14)
	{
		*freq = channel*5 + BASE_FREQ_2_4;
		return 0;
	}

	if (channel == 14)
	{
		*freq = 2484;
		return 0;
	}

	if (channel >= 36 && channel <= 165)
	{
		*freq = channel*5 + BASE_FREQ_5_0;
		return 0;
	}
	return -1;
}

static int translate_sta_flags_to_drv(unsigned int flags)
{
    int ret = 0;

    ret |= (flags & WPA_STA_AUTHORIZED)     ? TIW_DRV_STA_FLAG_AUTHORIZED     : 0;
    ret |= (flags & WPA_STA_WMM)            ? TIW_DRV_STA_FLAG_WMM            : 0;
    ret |= (flags & WPA_STA_SHORT_PREAMBLE) ? TIW_DRV_STA_FLAG_SHORT_PREAMBLE : 0;
    ret |= (flags & WPA_STA_MFP)            ? TIW_DRV_STA_FLAG_MFP            : 0;

    return ret;
}

static ERadioBand get_band_for_chan(int chan)
{
    if (chan >= 1 && chan <= 14)
        return RADIO_BAND_2_4_GHZ;
    else if (chan >= 36 && chan <= 165)
        return RADIO_BAND_5_0_GHZ;

    wpa_printf(MSG_DEBUG, "HOSTAPTIW %s:invalid chan %d",__func__, chan);
    return RADIO_BAND_2_4_GHZ;
}

static int get_chan_for_freq(int freq)
{
    if (freq >= 2400 && freq < 2500)
		return (freq - BASE_FREQ_2_4) / 5;
    else if (freq >= 4900 && freq < 6000)
		return (freq - BASE_FREQ_5_0) / 5;

    wpa_printf(MSG_DEBUG, "HOSTAPTIW %s:invalid freq %d",__func__, freq);
    return 0;
}

static int init_connection_scan_params(struct wilink_driver_if_data *drv,
                    TScanRequestParams * connScanParams,
					struct wpa_driver_scan_params *params,
					u32 long_interval,
					u32 short_interval,
					u8 num_short_intervals)
{

    unsigned int     i, j;
    int local_chans[] = PERIODIC_SCAN_CHANNELS_ARRAY_B_G_A_BAND;
	unsigned int wmeEnable = TRUE;
	TRateSets rateSet;
    TPeriodicScanParams * periodicScanParams = &connScanParams->u.tConnScanInfo;

	periodicScanParams->uSsidNum = 0;

    periodicScanParams->uCycleNum = 0; /* infinite number of cycles */

	/* Set cycle intervals */
	periodicScanParams->uLongInterval = long_interval;
	periodicScanParams->uShortInterval = short_interval;
	periodicScanParams->uShortCycleNum = num_short_intervals;

    /* set threshold and other parameters */
    periodicScanParams->bTerminateOnReport = FALSE;
    periodicScanParams->iRssiThreshold              = PERIODIC_SCAN_RSSI_THRESHOLD;
    periodicScanParams->iSnrThreshold               = PERIODIC_SCAN_SNR_THRESHOLD;
    periodicScanParams->uFrameCountReportThreshold  = PERIODIC_SCAN_FRAME_NUM_REPORT_THRESHODL;
    periodicScanParams->eBssType                    = BSS_ANY;
    periodicScanParams->uProbeRequestNum            = PERIODIC_SCAN_PROBE_REQUEST_NUM;

	/* No filter, no ssids or only bcast ssid */
	if (!params->num_filter_ssids &&
	    (!params->num_ssids ||
	     (params->num_ssids == 1 && params->ssids[0].ssid_len == 0))) {
        periodicScanParams->uSsidNum = 0;
	} else if (!params->num_filter_ssids) {
        periodicScanParams->uSsidListFilterEnabled = 0; /* no filtering */

        /* fill SSID list */
        for (i = 0; i < params->num_ssids; i++) {
            periodicScanParams->tDesiredSsid[i].eVisability =
                params->ssids[i].ssid_len ? SCAN_SSID_VISABILITY_HIDDEN :
                                            SCAN_SSID_VISABILITY_PUBLIC;
            periodicScanParams->tDesiredSsid[i].tSsid.len = params->ssids[i].ssid_len;
            os_memcpy(periodicScanParams->tDesiredSsid[i].tSsid.str,
                      params->ssids[i].ssid, params->ssids[i].ssid_len);
        }
        periodicScanParams->uSsidNum = params->num_ssids;
    } else {
        periodicScanParams->uSsidListFilterEnabled = 1; /* filter ssids */

        /* fill SSID list from filter */
        for (i = 0; i < params->num_filter_ssids; i++) {
            periodicScanParams->tDesiredSsid[i].eVisability = SCAN_SSID_VISABILITY_PUBLIC;
            periodicScanParams->tDesiredSsid[i].tSsid.len = params->filter_ssids[i].ssid_len;
            os_memcpy(periodicScanParams->tDesiredSsid[i].tSsid.str,
                      params->filter_ssids[i].ssid, params->filter_ssids[i].ssid_len);
        }
        periodicScanParams->uSsidNum = params->num_filter_ssids;

        if ((params->num_ssids > 1) ||
		    (params->num_ssids == 1 && params->ssids[0].ssid_len > 0)) {
			/*
			 * Mark all the SSIDs passed in the SSID list as HIDDEN,
			 * so they're used in probe requests.
			 */
			for (i = 0; i < params->num_ssids; i++) {
				if (!params->ssids[i].ssid_len)
					continue;

				for (j = 0; j < periodicScanParams->uSsidNum; j++) {
					if ((params->ssids[i].ssid_len ==
					     periodicScanParams->tDesiredSsid[j].tSsid.len) &&
					    !memcmp(params->ssids[i].ssid,
						   periodicScanParams->tDesiredSsid[j].tSsid.str,
						   params->ssids[i].ssid_len)) {
						periodicScanParams->tDesiredSsid[j].eVisability =
							SCAN_SSID_TYPE_HIDDEN;
						break;
					}
				}
			}
		}
    }
    
	/* set channels */

    /* use freqs if given */
    if (params->freqs != NULL) {
        int *cur_freq = params->freqs;
        i = 0;
        while (cur_freq && *cur_freq != 0 && i < PERIODIC_SCAN_MAX_CHANNEL_NUM)
		{
			local_chans[i++] = get_chan_for_freq(*cur_freq);
			cur_freq++;
		}
    }

    /* need 2.4Ghz channels first */
    j = 0;
    for (i = 0; i < PERIODIC_SCAN_MAX_CHANNEL_NUM; i++) {
        if (get_band_for_chan(local_chans[i]) != RADIO_BAND_2_4_GHZ)
            continue;

        periodicScanParams->tChannels[j].eBand              = RADIO_BAND_2_4_GHZ;
        periodicScanParams->tChannels[j].uChannel           = local_chans[i];
        periodicScanParams->tChannels[j].eScanType          = SCAN_TYPE_ACTIVE;
        periodicScanParams->tChannels[j].uMinDwellTimeMs    = PERIODIC_SCAN_MIN_2_4_CHANNEL_DWELL_TIME_MS;
        periodicScanParams->tChannels[j].uMaxDwellTimeMs    = PERIODIC_SCAN_MAX_2_4_CHANNEL_DWELL_TIME_MS;
        periodicScanParams->tChannels[j].uTxPowerLevelDbm   = MAX_TX_POWER;
        j++;
    }

    /* now A band channels */
    for (i = 0; i < PERIODIC_SCAN_MAX_CHANNEL_NUM; i++) {
        if (get_band_for_chan(local_chans[i]) != RADIO_BAND_5_0_GHZ)
            continue;

		periodicScanParams->tChannels[j].eBand              = RADIO_BAND_5_0_GHZ;
		periodicScanParams->tChannels[j].uChannel           = local_chans[i];
		periodicScanParams->tChannels[j].eScanType          = SCAN_TYPE_ACTIVE;
		periodicScanParams->tChannels[j].uMinDwellTimeMs    = PERIODIC_SCAN_MIN_5_CHANNEL_DWELL_TIME_MS;
		periodicScanParams->tChannels[j].uMaxDwellTimeMs    = PERIODIC_SCAN_MAX_5_CHANNEL_DWELL_TIME_MS;
		periodicScanParams->tChannels[j].uTxPowerLevelDbm   = MAX_TX_POWER;
        j++;
	}

    periodicScanParams->uChannelNum = i;
    wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: num channels %d",__func__, i);

    if (params->extra_ies_len <= TI_MAX_EXTRA_IES_LEN)
	{
		os_memcpy(connScanParams->aExtraProbeRequestIes, params->extra_ies, params->extra_ies_len);
		connScanParams->uExtraIesLen = params->extra_ies_len;
	}
	else
	{
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error extra IE's buffer too small!!!", __func__);
	}

	/* Get the Qos mode (Enable/Disable) and the desired rate set*/
	wilink_send_ti_private_cmd(drv, TI_PARAM_QOS_ENABLE, TIWDRV_CMD_GET_FLAG,
							   TIWDRV_PRIV_WEXT_IOCTL, (char*)&wmeEnable,sizeof(wmeEnable));
	wilink_send_ti_private_cmd(drv, TI_PARAM_DESIRED_RATE_SET, TIWDRV_CMD_GET_FLAG,
							   TIWDRV_PRIV_WEXT_IOCTL, (char*)&rateSet,sizeof(rateSet));
	connScanParams->bWmeEnable = wmeEnable;
	connScanParams->tRateSet = rateSet;

	/* Set probe request desired transmission rate*/
	if (rateSet.uBasicRatesBitMap & DRV_RATE_MASK_6_OFDM)
		periodicScanParams->probeRequestRate = PROB_REQ_6M;
	else if (rateSet.uBasicRatesBitMap & DRV_RATE_MASK_5_5_CCK)
		periodicScanParams->probeRequestRate = PROB_REQ_5_5M;
	else if (rateSet.uBasicRatesBitMap & DRV_RATE_MASK_1_BARKER)
		periodicScanParams->probeRequestRate = PROB_REQ_1M;
    else
		periodicScanParams->probeRequestRate = MAX_PROBE_RATE;

    return 0;
}

/*
 * wilink_events
 * register/unregister events according to registration mode
 * */
static int wilink_toggle_events(struct wilink_driver_if_data *drv, int registration_mode)
{
    unsigned int eventsArray[][2] = {
            {TIW_DRV_EV_START_ROAM, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL))},
            {TIW_DRV_EV_REPORT_FT, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL))},
            {TIW_DRV_EV_SCAN_COMPLETE,(BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL) | BIT(TIWDRV_IF_MODE_P2PDEV) | BIT(TIWDRV_IF_MODE_SAP) | BIT(TIWDRV_IF_MODE_P2PGO))},
			{TIW_DRV_EV_CONNECT_SCAN_COMPLETE,(BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL) | BIT(TIWDRV_IF_MODE_P2PDEV) | BIT(TIWDRV_IF_MODE_SAP) | BIT(TIWDRV_IF_MODE_P2PGO))},
            {TIW_DRV_EV_REMAIN_ON_CH_STARTED,(BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL) | BIT(TIWDRV_IF_MODE_P2PDEV))},
            {TIW_DRV_EV_REMAIN_ON_CH_COMPLETE, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL) | BIT(TIWDRV_IF_MODE_P2PDEV))},
            {TIW_DRV_EV_STA_AGING, BIT(TIWDRV_IF_MODE_SAP) | BIT(TIWDRV_IF_MODE_P2PGO)},
            {TIW_DRV_EV_TX_RETRY_FALIURE, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL) | BIT(TIWDRV_IF_MODE_SAP) | BIT(TIWDRV_IF_MODE_P2PGO))},
            {TIW_DRV_EV_DRV_RESET, (BIT(TIWDRV_IF_MODE_SAP) | BIT(TIWDRV_IF_MODE_P2PGO) | BIT(TIWDRV_IF_MODE_P2PDEV))},
            {TIW_DRV_EV_ASSOCIATED, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL))},
            {TIW_DRV_EV_DISASSOCIATED, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL))},
            {TIW_DRV_EV_ASSOC_RESP_IE, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL))},
            {TIW_DRV_EV_ASSOC_REQ_IE, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL))},
            {TIW_DRV_EV_BEACON_IE, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL))},
            {TIW_DRV_EV_iii_START, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL))},
            {TIW_DRV_EV_MIC_FAILURE, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL) | BIT(TIWDRV_IF_MODE_SAP) | BIT(TIWDRV_IF_MODE_P2PGO))},
            {TIW_DRV_EV_PMKID_CANDIDATE, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL))},
            {TIW_DRV_EV_WPS_SESSION_OVERLAP, (BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL))},
            {TIW_DRV_EV_CONTINUOUS_SCAN_REPORT,(BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL) | BIT(TIWDRV_IF_MODE_P2PDEV) | BIT(TIWDRV_IF_MODE_SAP) | BIT(TIWDRV_IF_MODE_P2PGO))},
			{TIW_DRV_EV_CHANNEL_LIST_CHANGED,(BIT(TIWDRV_IF_MODE_STA) | BIT(TIWDRV_IF_MODE_P2PCL) | BIT(TIWDRV_IF_MODE_P2PDEV) | BIT(TIWDRV_IF_MODE_SAP) | BIT(TIWDRV_IF_MODE_P2PGO))},
			{TIW_DRV_EV_CAC,(BIT(TIWDRV_IF_MODE_SAP) | BIT(TIWDRV_IF_MODE_P2PGO))},
            {TIW_DRV_EV_SWITCH_CHANNEL_COMPLETE,(BIT(TIWDRV_IF_MODE_SAP) | BIT(TIWDRV_IF_MODE_P2PGO))}, 

	};
    int i = 0;
    unsigned int pid;
    tiwdrv_event_register_params_t registerEvent;

    wpa_printf(MSG_DEBUG, "HOSTAPTIW %s: enter role = %d mode = %d",__func__, drv->drv_role, registration_mode);

    if(registration_mode != TI_PARAM_REGISTER_EVENT && registration_mode != TI_PARAM_UNREGISTER_EVENT)
        return -1;

    pid = drv->nl_pid;
    for (i = 0; i < (sizeof(eventsArray)/ sizeof(eventsArray[0])); i++ )
    {
        if (IS_BIT_SET(eventsArray[i][1], drv->drv_role))
        {
            registerEvent.uEventType = eventsArray[i][0];
            registerEvent.appObject = (void *)pid;

            wilink_send_ti_private_cmd(drv, registration_mode,
                    TIWDRV_CMD_SET_FLAG, TIWDRV_PRIV_WEXT_IOCTL,
                    (char *)&registerEvent, sizeof(registerEvent));
        }
    }

    return 0;

}

/*
 * wilink_generate_pid
 * generates a pid for netlink purposes. this pid is comprised of the process id and current role type.
 * @param ms_byte - the pid top byte
 * */
static unsigned int wilink_generate_pid(struct wilink_driver_if_data *drv, unsigned char ms_byte)
{
    /* bottom 3 bytes - pid, top byte - role type */
    return (getpid() | (ms_byte << 24));
}

static int wilink_driver_sched_scan(void *priv,
				    struct wpa_driver_scan_params *params,
				    u32 long_interval,
				    u32 short_interval,
				    u8 num_short_intervals)
{
	struct wilink_driver_if_data *drv = priv;
	int ret = 0;
	TScanRequestParams  tPeriodicScanParams;

	wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter", __func__);

	os_memset(&tPeriodicScanParams, 0, sizeof(tPeriodicScanParams));
	ret = init_connection_scan_params(drv, &tPeriodicScanParams, params, long_interval,
                                          short_interval, num_short_intervals);
        if (ret != 0) {
		wpa_printf(MSG_ERROR, "%s: could not init connection scan params", __func__);
		ret = -1;
		goto out;
	}

	wpa_printf(MSG_DEBUG, "tiwdrv_connection_scan. Scan params are set! uSsidNum = %d \n",tPeriodicScanParams.u.tConnScanInfo.uSsidNum);

	ret = wilink_send_ti_private_cmd(drv, TI_PARAM_START_CONNECTION_SCAN, TIWDRV_CMD_SET_FLAG,
				   TIWDRV_PRIV_WEXT_IOCTL, (char *)&tPeriodicScanParams, sizeof(tPeriodicScanParams));
	if (ret != 0)
	{
		wpa_printf(MSG_ERROR, "HOSTAPTIWERR %s: error sending TI_PARAM_START_CONNECTION_SCAN command to the driver", __func__);
		ret = -1;
		goto out;
	}

    wpa_printf(MSG_DEBUG, "HOSTAPTI: Sched scan requested (ret=%d) "
               "intervals: short=%d ms long=%d ms num_short_intervals=%d",
               ret, short_interval, long_interval, num_short_intervals);
out:
	return ret;
}


static int wilink_driver_stop_sched_scan(void *priv)
{
	struct wilink_driver_if_data *drv = priv;
	int ret;

	wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter", __func__);

	ret = wilink_send_ti_private_cmd(drv, TI_PARAM_STOP_CONNECTION_SCAN,
					 TIWDRV_CMD_SET_FLAG,
					 TIWDRV_PRIV_WEXT_IOCTL, NULL, 0);
	if (ret != 0) {
		wpa_printf(MSG_ERROR,
			   "HOSTAPTIWERR %s: error sending TI_PARAM_STTOP_CONNECTION_SCAN",
			   __func__);
		ret = -1;
	}

	return ret;
}

static int wilink_switch_channel(void *priv, struct csa_settings *csa_settings)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_csa_params_t		tCsaParams;
	tiwdrv_ap_beacon_params_t 	tCsaBeaconParams;
	int ret = 0;
	

	if ( (drv->drv_role != TIWDRV_IF_MODE_SAP) && (drv->drv_role != TIWDRV_IF_MODE_P2PGO) )
	{
		wpa_printf(MSG_ERROR, "HOSTAPTI %s: error invalid role %d for switch channel",__func__, drv->drv_role);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);


	/** Copy CSA Beacon and send command to driver **/
	memset(&tCsaBeaconParams, 0, sizeof(tCsaBeaconParams));
	
	if ( (csa_settings->beacon_csa.head == NULL) || (csa_settings->beacon_csa.tail == NULL) || 
		(csa_settings->beacon_csa.probe_resp_len> TIW_DRV_MAX_PROBE_RESP_LEN) )
	{
		wpa_printf(MSG_ERROR, "HOSTAPTI %s: error invalid CSA Beacon Params",__func__);
		return -1;
	}
	
	memcpy(tCsaBeaconParams.cHead, csa_settings->beacon_csa.head, csa_settings->beacon_csa.head_len);
	memcpy(tCsaBeaconParams.cTail, csa_settings->beacon_csa.tail, csa_settings->beacon_csa.tail_len);
	tCsaBeaconParams.iHeadLen = csa_settings->beacon_csa.head_len;
	tCsaBeaconParams.iTailLen = csa_settings->beacon_csa.tail_len;
    memcpy(tCsaBeaconParams.cProbeResp, csa_settings->beacon_csa.probe_resp, csa_settings->beacon_csa.probe_resp_len);
    tCsaBeaconParams.iProbeRespLen = csa_settings->beacon_csa.probe_resp_len;

	ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_BEACON_ATTRIBUTES, TIWDRV_CMD_SET_FLAG,
                                      TIWDRV_PRIV_WEXT_IOCTL, (char*)&tCsaBeaconParams,sizeof(tCsaBeaconParams));
    if (ret)
    {
    	wpa_printf(MSG_ERROR, "HOSTAPTI %s: Falied to send CSA Beacon Params command",__func__);
        return ret;
    }
	

    memset(&tCsaParams, 0, sizeof(tCsaParams));

	/** Copy general Swtich channel params **/
	tCsaParams.uCsCount = csa_settings->cs_count;
	tCsaParams.uBlockTx = csa_settings->block_tx;
	tCsaParams.uCounterOffsetBeacon = csa_settings->counter_offset_beacon;
	tCsaParams.uCounterOffsetPresp  = csa_settings->counter_offset_presp;


	/** Copy 'After' Beacon **/	
	memcpy(tCsaParams.tBeaconAfterParams.cHead, csa_settings->beacon_after.head, csa_settings->beacon_after.head_len);
	memcpy(tCsaParams.tBeaconAfterParams.cTail, csa_settings->beacon_after.tail, csa_settings->beacon_after.tail_len);
	tCsaParams.tBeaconAfterParams.iHeadLen = csa_settings->beacon_after.head_len;
	tCsaParams.tBeaconAfterParams.iTailLen = csa_settings->beacon_after.tail_len;
    memcpy(tCsaParams.tBeaconAfterParams.cProbeResp, csa_settings->beacon_after.probe_resp, csa_settings->beacon_after.probe_resp_len);
    tCsaParams.tBeaconAfterParams.iProbeRespLen = csa_settings->beacon_after.probe_resp_len;

	
	/** Copy New Channel Parameters **/
	ret  = tiwdrv_init_channel_params(&csa_settings->freq_params, &tCsaParams.tNewChannel);

	if(ret)
		return ret;
	
	
	ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_SWITCH_CHANNEL, TIWDRV_CMD_SET_FLAG,
									  TIWDRV_PRIV_WEXT_IOCTL, (char*)&tCsaParams,sizeof(tCsaParams));

	return ret;
		
}

static int wilink_start_dfs_cac(void *priv, struct hostapd_freq_params *freq)
{
	struct wilink_driver_if_data *drv = priv;
	tiwdrv_ap_channel_params_t		tCacParams;
	int ret = 0;

    wpa_printf(MSG_DEBUG, "HOSTAPTI %s: enter",__func__);

	ret  = tiwdrv_init_channel_params(freq, &tCacParams);

	if(ret)
		return ret;
	
    
	if(!drv->drv_global)
		wpa_printf(MSG_DEBUG, "HOSTAPTI %s: drv->drv_global is NULL ",__func__);
	
	wpa_printf(MSG_DEBUG, "HOSTAPTI %s: Sending TI_PARAM_START_CAC to driver ",__func__);
	
	ret  = wilink_send_ti_private_cmd(drv, TI_PARAM_START_CAC, TIWDRV_CMD_SET_FLAG,
									  TIWDRV_PRIV_WEXT_IOCTL, (char*)&tCacParams,sizeof(tCacParams));

	return ret;
}

static void build_hw_capability(RegDomainStruct_t *pRegHandle,
								tiwdrv_ap_chan_hw_info_t *pChanStruct,
								tiwdrv_ap_hw_ht_cap_info_t *pHtCap,
								char current_channel,
                                enum hostapd_hw_mode hostapd_mode)
{

    if (pChanStruct->mode == TIW_DRV_AP_DOT11_DUAL_MODE)
        pRegHandle->NumOfModes = 2;
    else
        pRegHandle->NumOfModes = 1;

    pRegHandle->modes = os_zalloc(pRegHandle->NumOfModes * sizeof(struct hostapd_hw_modes)); /* don't free this pointer it will be done by hostapd_free_hw_features */
    if (pRegHandle->modes == NULL)
    {
        wpa_printf(MSG_ERROR, "%s: allocation failed", __func__);
        return;
    }

    switch (pChanStruct->mode)
	{
		case DOT11_A_MODE:
            build_single_mode_capability(pRegHandle->modes, pChanStruct, pHtCap, HOSTAPD_MODE_IEEE80211A);
            break;

		case DOT11_B_MODE:
            build_single_mode_capability(pRegHandle->modes, pChanStruct, pHtCap, HOSTAPD_MODE_IEEE80211B);
            break;

		case DOT11_G_MODE:
            /* If required AP mode is B or if required AP channel is 14 - */
			if (hostapd_mode == HOSTAPD_MODE_IEEE80211B || current_channel == 14)
			{
				build_single_mode_capability(pRegHandle->modes, pChanStruct, pHtCap, HOSTAPD_MODE_IEEE80211B);
				if (current_channel == 14)
					pRegHandle->modes[0].mode = HOSTAPD_MODE_IEEE80211G;
			}
			else
			{
				build_single_mode_capability(pRegHandle->modes, pChanStruct, pHtCap, HOSTAPD_MODE_IEEE80211G);
			}
			break;

		case DOT11_DUAL_MODE:

            if (hostapd_mode == HOSTAPD_MODE_IEEE80211B || current_channel == 14)
			{
				build_single_mode_capability(pRegHandle->modes, pChanStruct, pHtCap, HOSTAPD_MODE_IEEE80211B);
				if (current_channel == 14)
					pRegHandle->modes[0].mode = HOSTAPD_MODE_IEEE80211G;
			}
			else
			{
				build_single_mode_capability(pRegHandle->modes, pChanStruct, pHtCap, HOSTAPD_MODE_IEEE80211G);
			}

            build_single_mode_capability(&pRegHandle->modes[1], pChanStruct, pHtCap, HOSTAPD_MODE_IEEE80211A);
			break;

		default:
			wpa_printf(MSG_ERROR, "%s: illegal Dot11 mode ", __func__);
	}
}


static void build_single_mode_capability(struct hostapd_hw_modes *hwMode, tiwdrv_ap_chan_hw_info_t *pChanInfo,
										 tiwdrv_ap_hw_ht_cap_info_t *pHtCap, enum hostapd_hw_mode mode)
{
    int NumOfRate;
	tiwdrv_ap_chan_data_t   *pChanList;
	int *pRateTbl;
	int i, freqBase;


	switch (mode)
	{
		case HOSTAPD_MODE_IEEE80211A:
            NumOfRate = sizeof(RateATbl)/ sizeof(RateATbl[0]);
			hwMode->mode = HOSTAPD_MODE_IEEE80211A;
			hwMode->num_channels = pChanInfo->numOfAChan;
			pChanList = pChanInfo->chan5List;
			pRateTbl = RateATbl;
			freqBase = BASE_FREQ_5_0;
			break;

		case HOSTAPD_MODE_IEEE80211G:
            NumOfRate = sizeof(RateGTbl)/ sizeof(RateGTbl[0]);
            hwMode->mode = HOSTAPD_MODE_IEEE80211G;
			hwMode->num_channels = pChanInfo->numOfGChan;
			pChanList = pChanInfo->chan24List;
			pRateTbl = RateGTbl;
			freqBase = BASE_FREQ_2_4;
			break;

		case HOSTAPD_MODE_IEEE80211B:
            NumOfRate = sizeof(RateBTbl)/ sizeof(RateBTbl[0]);
			hwMode->mode = HOSTAPD_MODE_IEEE80211B;
			hwMode->num_channels = pChanInfo->numOfBChan;
			pChanList = pChanInfo->chan24List;
			pRateTbl = RateBTbl;
			freqBase = BASE_FREQ_2_4;
			break;

		default:
            return;
	}

    /* If no HT capabilities required - pHtCap will be zero */
    if (pHtCap)
    {
		os_memset(hwMode->mcs_set, 0, TIW_DRV_NUM_MCS_SET_BYTES);
		os_memcpy(hwMode->mcs_set, pHtCap->mcs_set, TIW_DRV_NUM_MCS_SET_BYTES);
		hwMode->ht_capab = pHtCap->ht_cap_info;
		hwMode->a_mpdu_params = pHtCap->a_mpdu_params;
    }
    
    hwMode->num_rates = NumOfRate;
    hwMode->channels = os_zalloc(sizeof(struct hostapd_channel_data) * (hwMode->num_channels)) ;
    hwMode->rates = os_zalloc(sizeof(struct hostapd_rate_data) * (hwMode->num_rates));
    if (hwMode->channels == NULL || hwMode->rates == NULL)
    {
        wpa_printf(MSG_ERROR, "%s: allocation failed ", __func__);
        hostapd_free_hw_features(hwMode, 1);
        return ;
    }
	
    for (i=0; i < hwMode->num_channels; i++)
    {
        hwMode->channels[i].chan = pChanList[i].chan;
		hwMode->channels[i].freq = hwMode->channels[i].chan*5 + freqBase;
        hwMode->channels[i].max_tx_power = pChanList[i].max_tx_power;

		if (hwMode->ht_capab & HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET)
		{
			hwMode->channels[i].flag |= HOSTAPD_CHAN_HT40;
            if (pChanList[i].flags & TIW_REG_DOMAIN_HT40PLUS)
				hwMode->channels[i].flag |= HOSTAPD_CHAN_HT40PLUS;
			if (pChanList[i].flags & TIW_REG_DOMAIN_HT40MINUS)
				hwMode->channels[i].flag |= HOSTAPD_CHAN_HT40MINUS;
		}

		if(pChanList[i].flags & TIW_REG_DOMAIN_DFS)
		{
			hwMode->channels[i].flag |= HOSTAPD_CHAN_RADAR;

			switch(pChanList[i].flags & TIW_REG_DOMAIN_DFS_MASK)
			{
				case TIW_REG_DOMAIN_DFS_USABLE:
					hwMode->channels[i].flag |= HOSTAPD_CHAN_DFS_USABLE;
					break;
				case TIW_REG_DOMAIN_DFS_UNAVAILABLE:
					hwMode->channels[i].flag |= HOSTAPD_CHAN_DFS_UNAVAILABLE;
					break;
				case TIW_REG_DOMAIN_DFS_AVAILABLE:
					hwMode->channels[i].flag |= HOSTAPD_CHAN_DFS_AVAILABLE;
					break;
				default: 
					hwMode->channels[i].flag |= HOSTAPD_CHAN_DFS_UNKNOWN;
					break;
			}
		}
		
		if (hwMode->channels[i].chan == 14)
			hwMode->channels[i].freq = FREQ_CH_14;
    }

    /* TBD A mode Rates */
    for (i=0; i < NumOfRate; i++)
    {
        hwMode->rates[i] = pRateTbl[i];
	}
}


const struct wpa_driver_ops wpa_driver_wilink_ops =
{
    .name = "wilink",

    .global_init = wilink_global_init,
	.global_deinit = wilink_global_deinit,
    .init2 = wilink_if_init,
	.deinit = wilink_deinit,
	.get_capa = wilink_get_capa,
    .hapd_send_eapol = wilink_hpad_send_eapol,
    .send_mlme = wilink_send_mgmt_frame,
    .hapd_set_ssid = wilink_hapd_set_ssid,
    .set_freq = wilink_set_channel,
    .commit = wilink_commit,
    .sta_set_flags = wilink_sta_set_flags,
    .sta_remove = wilink_sta_remove,
    .sta_add = wilink_sta_add,
    .set_privacy = wilink_set_privacy,
    .set_key = wilink_set_key,
    .set_ap = wilink_set_ap,
    .if_add = wilink_if_add,
    .get_hw_feature_data = wilink_get_hw_feature_data,
#ifdef HOSTAPD
    .hapd_init = wilink_hapd_init,
    .hapd_deinit = wilink_hapd_deinit,
#endif /* HOSTAPD */
#if defined(HOSTAPD) || defined(CONFIG_AP)
    .set_country = wilink_set_country,
    .get_country = wilink_get_country,
    .flush = wilink_flush,
    .read_sta_data = wilink_read_sta_data,
    .set_rts = wilink_set_rts,
    .sta_deauth = wilink_sta_deauth,
    .sta_disassoc = wilink_sta_disassoc,
    .set_tx_queue_params = wilink_set_tx_queue_params,
#endif /* HOSTAPD || CONFIG_AP */
    .get_mac_addr = wilink_get_mac_addr,
    .scan2 = wilink_scan,
    .get_scan_results2 = wilink_get_scan_results,
    .sched_scan = wilink_driver_sched_scan,
    .stop_sched_scan = wilink_driver_stop_sched_scan,
    .send_action = wilink_send_action,
    .remain_on_channel = wilink_remain_on_channel,
    .cancel_remain_on_channel = wilink_cancel_remain_on_channel,
    .probe_req_report = wilink_probe_req_report,

    /* station operations */
    .get_bssid = wilink_get_bssid,
    .get_ssid = wilink_get_ssid,
    .deauthenticate = wilink_disassociate,
    .associate = wilink_associate,
#ifndef CONFIG_P2P
    .add_pmkid = wilink_add_pmkid,
    .flush_pmkid = wilink_flush_pmkid,
#endif

#ifndef HOSTAPD
    .set_operstate = wilink_set_operstate,
#endif	
    .update_ft_ies = wilink_update_ft_ies,
    /* AZ: TODO .set_probe_req_ie missing in CC version of drivers.h
     .set_probe_req_ie = wilink_set_probe_req_ie, */
	.switch_channel = wilink_switch_channel,
    .start_dfs_cac = wilink_start_dfs_cac,
};

