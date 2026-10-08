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
/* for apps that would make some of the WFD/WPS connection procedure by themselves */

#include <802_11defs.h>
#include "common.h"
#include "drivers/driver.h"
#include "cme_defs.h"
#include "config_ssid.h"
#include <rsn.h>            // for securityKeys_t
#include <rates.h>
#include "cme_common.h"
#include "common/ieee802_11_common.h"
#include <driver/drv_core.h>
#include "public_share.h"
#include "udata_api.h"
#include "drv_ext_app.h"

#include "ethernet.h"
#include "tw_driver.h"
#include "udata_api.h"
#include "udata_net_api.h"
#include "rx_defs.h"
//#include "rx.h"
#include "tx_data_queue_api.h"
#include "public_types.h"

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
#include "wps/wps_i.h"
#include "p2p/p2p_i.h"
#include "scan.h"
#include "scan_result_table.h"


#include "bss.h"
#include "cme_supplicant_api.h"
#include "cme_dispatcher_api.h"
#include "cme_internal_api.h"
#include "cme_fw_api.h"
#include "cme_defs.h"
#include "802_11defs.h"

#include "gtrace.h"

#include "mpdu.h"

#include "80211_utils.h"
#include "regulatory_domain_api.h"
#include "common.h"
#include "driver/drv_core.h"
#include "rsn.h"
#include "public_share.h"
#include "l2_cfg.h"
#include "lower_mac_if.h"
#include "drv_ti_internal.h"
#include "rx.h"

#include "wlan_if.h"

#include "eap_wsc_common.h"

extern int32_t  extSetSecurityParams(CMEWlanAddGetProfile_t *apCmd,
                                     _cme_minimized_wpa_ssid_t       *apSsid,
                                     int8_t                  *apPassword);
externalApp_t gExternalApp = {0};


struct wps_registrar {
	struct wps_context *wps;

	int pbc;
	int selected_registrar;

	int (*new_psk_cb)(void *ctx, const u8 *mac_addr, const u8 *p2p_dev_addr,
			  const u8 *psk, size_t psk_len);
	int (*set_ie_cb)(void *ctx, struct wpabuf *beacon_ie,
			 struct wpabuf *probe_resp_ie);
	void (*pin_needed_cb)(void *ctx, const u8 *uuid_e,
			      const struct wps_device_data *dev);
	void (*reg_success_cb)(void *ctx, const u8 *mac_addr,
			       const u8 *uuid_e, const u8 *dev_pw,
			       size_t dev_pw_len);
	void (*set_sel_reg_cb)(void *ctx, int sel_reg, u16 dev_passwd_id,
			       u16 sel_reg_config_methods);
	void (*enrollee_seen_cb)(void *ctx, const u8 *addr, const u8 *uuid_e,
				 const u8 *pri_dev_type, u16 config_methods,
				 u16 dev_password_id, u8 request_type,
				 const char *dev_name);
	int (*lookup_pskfile_cb)(void *ctx, const u8 *mac_addr, const u8 **psk);
	void *cb_ctx;

	struct dl_list pins;
	struct dl_list nfc_pw_tokens;
	struct wps_pbc_session *pbc_sessions;

	int skip_cred_build;
	struct wpabuf *extra_cred;
	int disable_auto_conf;
	int sel_reg_union;
	int sel_reg_dev_password_id_override;
	int sel_reg_config_methods_override;
	int dualband;
	int force_per_enrollee_psk;

	struct wps_registrar_device *devices;

	int force_pbc_overlap;

	u8 authorized_macs[WPS_MAX_AUTHORIZED_MACS][ETH_ALEN];
	u8 authorized_macs_union[WPS_MAX_AUTHORIZED_MACS][ETH_ALEN];

	u8 p2p_dev_addr[ETH_ALEN];

	u8 pbc_ignore_uuid[WPS_UUID_LEN];
#ifdef WPS_WORKAROUNDS
	struct os_reltime pbc_ignore_start;
#endif /* WPS_WORKAROUNDS */

	/**
	 * multi_ap_backhaul_ssid - SSID to supply to a Multi-AP backhaul
	 * enrollee
	 *
	 * This SSID is used by the Registrar to fill in information for
	 * Credentials when the enrollee advertises it is a Multi-AP backhaul
	 * STA.
	 */
	u8 multi_ap_backhaul_ssid[SSID_MAX_LEN];

	/**
	 * multi_ap_backhaul_ssid_len - Length of multi_ap_backhaul_ssid in
	 * octets
	 */
	size_t multi_ap_backhaul_ssid_len;

	/**
	 * multi_ap_backhaul_network_key - The Network Key (PSK) for the
	 * Multi-AP backhaul enrollee.
	 *
	 * This key can be either the ASCII passphrase (8..63 characters) or the
	 * 32-octet PSK (64 hex characters).
	 */
	u8 *multi_ap_backhaul_network_key;

	/**
	 * multi_ap_backhaul_network_key_len - Length of
	 * multi_ap_backhaul_network_key in octets
	 */
	size_t multi_ap_backhaul_network_key_len;
};

struct wps_uuid_pin {
	struct dl_list list;
	u8 uuid[WPS_UUID_LEN];
	int wildcard_uuid;
	u8 *pin;
	size_t pin_len;
#define PIN_LOCKED BIT(0)
#define PIN_EXPIRES BIT(1)
	int flags;
	struct os_reltime expiration;
	u8 enrollee_addr[ETH_ALEN];
};


static int p2ps_validate_pd_req(struct p2p_data *p2p, struct p2p_message *msg,
                const u8 *addr);

static void p2ps_add_new_group_info(struct p2p_data *p2p,
                    struct p2p_device *dev,
                    struct wpabuf *buf);


static struct wpabuf * p2p_build_prov_disc_resp(struct p2p_data *p2p,
                        struct p2p_device *dev,
                        u8 dialog_token,
                        enum p2p_status_code status,
                        u16 config_methods,
                        u32 adv_id,
                        const u8 *group_id,
                        size_t group_id_len,
                        const u8 *persist_ssid,
                        size_t persist_ssid_len,
                        const u8 *fcap,
                        u16 fcap_len);

static void p2p_build_wps_ie_config_methods(struct wpabuf *buf,
                        u16 config_methods);


static u8 p2ps_own_preferred_cpt(const u8 *cpt_priority, u8 req_cpt_mask);

static int p2ps_setup_p2ps_prov(struct p2p_data *p2p, u32 adv_id,
                u32 session_id, u16 method,
                const u8 *session_mac, const u8 *adv_mac);


static uint8_t gExtWpsInProgress = 0;
static uint8_t gExtWpsScanning = 0;
static void *gExtWpsWpaEapolSM = NULL;


uint32_t isextP2P()
{
    return((uint32_t)gExternalApp.extP2P);
}
uint32_t isextWPS()
{
    return((uint32_t)gExternalApp.extWps);
}

uint32_t isextDPP()
{
    return((uint32_t)gExternalApp.extDPP);
}

uint32_t isextWPSDone()
{
    return((uint32_t)gExternalApp.extWpsDone);
}

uint32_t isextWPSInProgress()
{
    return((uint32_t)isExtWpsInProgress());
}

void inline set_extP2P(uint8_t val)
{
    gExternalApp.extP2P = val;
}
void inline set_extWPS(uint8_t val)
{
    gExternalApp.extWps = val;
}

void extAppDeinit()
{
    gExtWpsScanning = 0;
    gExtWpsInProgress = 0;
    gExtWpsWpaEapolSM = NULL;
}

void inline set_extDPP(uint8_t val)
{
    gExternalApp.extDPP = val;
}

void set_extWPSDone(uint8_t val)
{
    gExternalApp.extWpsDone = val;
}

Bool_e extWpsIsApLinkWps(uint8_t hlid, TInternalWlanLinkInfo *pLinkInfo)
{
    wlanLinks_GetLink(hlid, &pLinkInfo);

    return pLinkInfo->info.wps;
}

static void wps_registrar_add_authorized_mac(struct wps_registrar *reg,
					     const u8 *addr)
{
    
	int i;
	wpa_printf(MSG_DEBUG, "WPS: Add authorized MAC " MACSTR,
		   MAC2STR(addr));
	for (i = 0; i < WPS_MAX_AUTHORIZED_MACS; i++)
		if (os_memcmp(reg->authorized_macs[i], addr, ETH_ALEN) == 0) {
			wpa_printf(MSG_DEBUG, "WPS: Authorized MAC was "
				   "already in the list");
			return; /* already in list */
		}
	for (i = WPS_MAX_AUTHORIZED_MACS - 1; i > 0; i--)
		os_memcpy(reg->authorized_macs[i], reg->authorized_macs[i - 1],
			  ETH_ALEN);
	os_memcpy(reg->authorized_macs[0], addr, ETH_ALEN);
	wpa_hexdump(MSG_DEBUG, "WPS: Authorized MACs",
		    (u8 *) reg->authorized_macs, sizeof(reg->authorized_macs));
}

// struct wps_registrar is internal to wps_registrar.c...
// This function was copied from wps_registrar_button_pushed()
// in order to use supplicant code without having to actually modifying
// the open source code.
#ifndef TI_STA_ONLY_BUILD
int ext_wps_registrar_button_pushed(struct wpa_supplicant *wpa_s,
				const u8 *p2p_dev_addr)
{
    if (!wpa_s->ap_iface)
		return -1;
	struct hostapd_data *hapd = wpa_s->ap_iface->bss[0];
    struct wps_registrar *reg = hapd->wps->registrar;

	if (p2p_dev_addr == NULL &&
	    wps_registrar_pbc_overlap(reg, NULL, NULL)) {
		wpa_printf(MSG_DEBUG, "WPS: PBC overlap - do not start PBC "
			   "mode");
		//wps_pbc_overlap_event(reg->wps);
		return -2;
	}
	wpa_printf(MSG_DEBUG, "WPS: Button pushed - PBC mode started");
	reg->force_pbc_overlap = 0;
	reg->selected_registrar = 1;
	reg->pbc = 1;
	if (p2p_dev_addr)
		os_memcpy(reg->p2p_dev_addr, p2p_dev_addr, ETH_ALEN);
	else
		os_memset(reg->p2p_dev_addr, 0, ETH_ALEN);
	wps_registrar_add_authorized_mac(reg,
					 (u8 *) "\xff\xff\xff\xff\xff\xff");
	wps_registrar_selected_registrar_changed(reg, 0);

	wps_pbc_active_event(reg->wps);
	//eloop_cancel_timeout(wps_registrar_set_selected_timeout, reg, NULL);
	//eloop_cancel_timeout(wps_registrar_pbc_timeout, reg, NULL);
	//eloop_register_timeout(WPS_PBC_WALK_TIME, 0, wps_registrar_pbc_timeout,
	//		       reg, NULL);
	return 0;
}


int ext_wps_registrar_add_pin(struct wpa_supplicant *wpa_s, const u8 *addr,
			  const u8 *uuid, const u8 *pin, size_t pin_len,
			  int timeout)
{
	struct wps_uuid_pin *p;
    struct hostapd_data *hapd = wpa_s->ap_iface->bss[0];
    struct wps_registrar *reg = hapd->wps->registrar;

    if (pin == NULL) {
        return -1;
    }

	p = os_zalloc(sizeof(*p));
	if (p == NULL)
		return -1;
	if (addr)
		os_memcpy(p->enrollee_addr, addr, ETH_ALEN);
	if (uuid == NULL)
		p->wildcard_uuid = 1;
	else
		os_memcpy(p->uuid, uuid, WPS_UUID_LEN);
	p->pin = os_memdup(pin, pin_len);
	if (p->pin == NULL) {
		os_free(p);
		return -1;
	}
	p->pin_len = pin_len;

	if (timeout) {
		p->flags |= PIN_EXPIRES;
		os_get_reltime(&p->expiration);
		p->expiration.sec += timeout;
	}

    // For now we don't use wildcard UUID
	//if (p->wildcard_uuid)
	//	wps_registrar_invalidate_unused(reg);

	dl_list_add(&reg->pins, &p->list);

	wpa_printf(MSG_DEBUG, "WPS: A new PIN configured (timeout=%d)",
		   timeout);
	wpa_hexdump(MSG_DEBUG, "WPS: UUID", uuid, WPS_UUID_LEN);
	wpa_hexdump_ascii_key(MSG_DEBUG, "WPS: PIN", pin, pin_len);
	reg->selected_registrar = 1;
	reg->pbc = 0;
	if (addr)
		wps_registrar_add_authorized_mac(reg, addr);
	else
		wps_registrar_add_authorized_mac(
			reg, (u8 *) "\xff\xff\xff\xff\xff\xff");
	wps_registrar_selected_registrar_changed(reg, 0);
	//eloop_cancel_timeout(wps_registrar_set_selected_timeout, reg, NULL);
	//eloop_register_timeout(WPS_PBC_WALK_TIME, 0,
	//		       wps_registrar_set_selected_timeout,
	//		       reg, NULL);

	return 0;
}
#endif

int32 ext_p2p_process_prov_disc_req(WlanProvDiscResp_t* pProvDiscResp)
{
    struct p2p_message msg;
    struct p2p_device *dev;
    int freq;
    enum p2p_status_code reject = P2P_SC_FAIL_INCOMPATIBLE_PARAMS;
    struct wpabuf *resp;
    u32 adv_id = 0;
    struct p2ps_advertisement *p2ps_adv = NULL;
    u8 conncap = P2PS_SETUP_NEW;
    u8 auto_accept = 0;
    u32 session_id = 0;
    u8 session_mac[ETH_ALEN] = { 0, 0, 0, 0, 0, 0 };
    u8 adv_mac[ETH_ALEN] = { 0, 0, 0, 0, 0, 0 };
    const u8 *group_mac;
    int passwd_id = DEV_PW_DEFAULT;
    u16 config_methods;
    u16 allowed_config_methods = WPS_CONFIG_DISPLAY | WPS_CONFIG_KEYPAD;
    struct p2ps_feature_capab resp_fcap = { 0, 0 };
    struct p2ps_feature_capab *req_fcap = NULL;
    u8 remote_conncap;
    u16 method;

    struct p2p_data *p2p;


    uint8_t   roleId            =  pProvDiscResp->roleId;
    uint8_t*  sa                =  &pProvDiscResp->provDiscReqSa[0];
    uint8_t*  data              =  pProvDiscResp->provDiscReqData;
    uint32_t  len               =  pProvDiscResp->provDiscReqLen;
    int32_t   rx_freq           =  pProvDiscResp->provDiscReqRxFreq;
    uint8_t   vendor_status     =  pProvDiscResp->status;


    if(!gExternalApp.extP2P)
    {
        return -1;
    }

    roleId = drv_getRoleIdFromType(gpSupplicantGlobals, (u8)pProvDiscResp->roleId);
    GTRACE(GRP_CME,"ext_p2p_process_prov_disc_req: %d",roleId);
    CME_PRINT_REPORT("\n\r ext_p2p_process_prov_disc_req",roleId);

    struct wpa_supplicant* wpa_s = drv_getIfaceFromRoleID(gpSupplicantGlobals, roleId);

    //role was not enabled
    if(wpa_s == NULL )
    {
        GTRACE(GRP_CME,"ERROR ! Send action frame to role id :%d which is not enabled",roleId);
        CME_PRINT_REPORT("\r\n ERROR ! Send action frame to role id :%d which is not enabled",roleId);
        return -1;
    }

    p2p = wpa_s->global->p2p;

    if (p2p_parse(data, len, &msg))
        return -1;

    p2p_dbg(p2p, "Received Provision Discovery Request from " MACSTR
        " with config methods 0x%x (freq=%d)",
        MAC2STR(sa), msg.wps_config_methods, rx_freq);
    group_mac = msg.intended_addr;

    dev = p2p_get_device(p2p, sa);
    if (dev == NULL || (dev->flags & P2P_DEV_PROBE_REQ_ONLY)) {
        p2p_dbg(p2p, "Provision Discovery Request from unknown peer "
            MACSTR, MAC2STR(sa));

        if (p2p_add_device(p2p, sa, rx_freq, NULL, 0, data + 1, len - 1,
                   0)) {
            p2p_dbg(p2p, "Provision Discovery Request add device failed "
                MACSTR, MAC2STR(sa));
            goto out;
        }

        dev = p2p_get_device(p2p, sa);
        if (!dev) {
            p2p_dbg(p2p,
                "Provision Discovery device not found "
                MACSTR, MAC2STR(sa));
            goto out;
        }
    } else if (msg.wfd_subelems) {
        wpabuf_free(dev->info.wfd_subelems);
        dev->info.wfd_subelems = wpabuf_dup(msg.wfd_subelems);
    }

    if (!msg.adv_id) {
        allowed_config_methods |= WPS_CONFIG_PUSHBUTTON;
        if (!(msg.wps_config_methods & allowed_config_methods)) {
            p2p_dbg(p2p,
                "Unsupported Config Methods in Provision Discovery Request");
            goto out;
        }

        /* Legacy (non-P2PS) - Unknown groups allowed for P2PS */
        if (msg.group_id) {
            size_t i;

            for (i = 0; i < p2p->num_groups; i++) {
                if (p2p_group_is_group_id_match(
                        p2p->groups[i],
                        msg.group_id, msg.group_id_len))
                    break;
            }
            if (i == p2p->num_groups) {
                p2p_dbg(p2p,
                    "PD request for unknown P2P Group ID - reject");
                goto out;
            }
        }
    } else {
        allowed_config_methods |= WPS_CONFIG_P2PS;

        /*
         * Set adv_id here, so in case of an error, a P2PS PD Response
         * will be sent.
         */
        adv_id = WPA_GET_LE32(msg.adv_id);
        if (p2ps_validate_pd_req(p2p, &msg, sa) < 0) {
            reject = P2P_SC_FAIL_INVALID_PARAMS;
            goto out;
        }

        req_fcap = (struct p2ps_feature_capab *) msg.feature_cap;

        os_memcpy(session_mac, msg.session_mac, ETH_ALEN);
        os_memcpy(adv_mac, msg.adv_mac, ETH_ALEN);

        session_id = WPA_GET_LE32(msg.session_id);

        if (msg.conn_cap)
            conncap = *msg.conn_cap;

        /*
         * We need to verify a P2PS config methog in an initial PD
         * request or in a follow-on PD request with the status
         * SUCCESS_DEFERRED.
         */
        if ((!msg.status || *msg.status == P2P_SC_SUCCESS_DEFERRED) &&
            !(msg.wps_config_methods & allowed_config_methods)) {
            p2p_dbg(p2p,
                "Unsupported Config Methods in Provision Discovery Request");
            goto out;
        }

        /*
         * TODO: since we don't support multiple PD, reject PD request
         * if we are in the middle of P2PS PD with some other peer
         */
    }

    dev->flags &= ~(P2P_DEV_PD_PEER_DISPLAY |
            P2P_DEV_PD_PEER_KEYPAD |
            P2P_DEV_PD_PEER_P2PS);

    if (msg.wps_config_methods & WPS_CONFIG_DISPLAY) {
        p2p_dbg(p2p, "Peer " MACSTR
            " requested us to show a PIN on display", MAC2STR(sa));
        dev->flags |= P2P_DEV_PD_PEER_KEYPAD;
        passwd_id = DEV_PW_USER_SPECIFIED;
    } else if (msg.wps_config_methods & WPS_CONFIG_KEYPAD) {
        p2p_dbg(p2p, "Peer " MACSTR
            " requested us to write its PIN using keypad",
            MAC2STR(sa));
        dev->flags |= P2P_DEV_PD_PEER_DISPLAY;
        passwd_id = DEV_PW_REGISTRAR_SPECIFIED;
    } else if (msg.wps_config_methods & WPS_CONFIG_P2PS) {
        p2p_dbg(p2p, "Peer " MACSTR " requesting P2PS PIN",
            MAC2STR(sa));
        dev->flags |= P2P_DEV_PD_PEER_P2PS;
        passwd_id = DEV_PW_P2PS_DEFAULT;
    }

    /* Remove stale persistent groups */
    if (p2p->cfg->remove_stale_groups) {
        p2p->cfg->remove_stale_groups(
            p2p->cfg->cb_ctx, dev->info.p2p_device_addr,
            msg.persistent_dev,
            msg.persistent_ssid, msg.persistent_ssid_len);
    }
    if(vendor_status != P2P_SC_SUCCESS)
    {
        p2p_dbg(p2p,
            "Reject status was set by external app status:%d", vendor_status);
        CME_PRINT_REPORT("\n\r p2p prov discovery request rejected by vendor roleId:%d status:%d",roleId, vendor_status);

        reject = vendor_status;
        goto out;
    }

    reject = P2P_SC_SUCCESS;


    /*
     * End of a legacy P2P PD Request processing, from this point continue
     * with P2PS one.
     */
    if (!msg.adv_id)
        goto out;

    remote_conncap = conncap;

    if (!msg.status) {
        unsigned int forced_freq, pref_freq;

        if (os_memcmp(p2p->cfg->dev_addr, msg.adv_mac, ETH_ALEN)) {
            p2p_dbg(p2p,
                "P2PS PD adv mac does not match the local one");
            reject = P2P_SC_FAIL_INCOMPATIBLE_PARAMS;
            goto out;
        }

        p2ps_adv = p2p_service_p2ps_id(p2p, adv_id);
        if (!p2ps_adv) {
            p2p_dbg(p2p, "P2PS PD invalid adv_id=0x%X", adv_id);
            reject = P2P_SC_FAIL_INCOMPATIBLE_PARAMS;
            goto out;
        }
        p2p_dbg(p2p, "adv_id: 0x%X, p2ps_adv: %p", adv_id, p2ps_adv);

        auto_accept = p2ps_adv->auto_accept;
        conncap = p2p->cfg->p2ps_group_capability(p2p->cfg->cb_ctx,
                              conncap, auto_accept,
                              &forced_freq,
                              &pref_freq);

        p2p_dbg(p2p, "Conncap: local:%d remote:%d result:%d",
            auto_accept, remote_conncap, conncap);

        p2p_prepare_channel(p2p, dev, forced_freq, pref_freq, 0);

        resp_fcap.cpt = p2ps_own_preferred_cpt(p2ps_adv->cpt_priority,
                               req_fcap->cpt);

        p2p_dbg(p2p, "cpt: service:0x%x remote:0x%x result:0x%x",
            p2ps_adv->cpt_mask, req_fcap->cpt, resp_fcap.cpt);

        if (!resp_fcap.cpt) {
            p2p_dbg(p2p,
                "Incompatible P2PS feature capability CPT bitmask");
            reject = P2P_SC_FAIL_INCOMPATIBLE_PARAMS;
        } else if (p2ps_adv->config_methods &&
               !(msg.wps_config_methods &
                 p2ps_adv->config_methods)) {
            p2p_dbg(p2p,
                "Unsupported config methods in Provision Discovery Request (own=0x%x peer=0x%x)",
                p2ps_adv->config_methods,
                msg.wps_config_methods);
            reject = P2P_SC_FAIL_INCOMPATIBLE_PARAMS;
        } else if (!p2ps_adv->state) {
            p2p_dbg(p2p, "P2PS state unavailable");
            reject = P2P_SC_FAIL_UNABLE_TO_ACCOMMODATE;
        } else if (!conncap) {
            p2p_dbg(p2p, "Conncap resolution failed");
            reject = P2P_SC_FAIL_INCOMPATIBLE_PARAMS;
        }

        if (msg.wps_config_methods & WPS_CONFIG_KEYPAD) {
            p2p_dbg(p2p, "Keypad - always defer");
            auto_accept = 0;
        }

        if ((remote_conncap & (P2PS_SETUP_NEW | P2PS_SETUP_CLIENT) ||
             msg.persistent_dev) && conncap != P2PS_SETUP_NEW &&
            msg.channel_list && msg.channel_list_len &&
            p2p_peer_channels_check(p2p, &p2p->channels, dev,
                        msg.channel_list,
                        msg.channel_list_len) < 0) {
            p2p_dbg(p2p,
                "No common channels - force deferred flow");
            auto_accept = 0;
        }

        if (((remote_conncap & P2PS_SETUP_GROUP_OWNER) ||
             msg.persistent_dev) && msg.operating_channel) {
            struct p2p_channels intersect;

            /*
             * There are cases where only the operating channel is
             * provided. This requires saving the channel as the
             * supported channel list, and verifying that it is
             * supported.
             */
            if (dev->channels.reg_classes == 0 ||
                !p2p_channels_includes(&dev->channels,
                           msg.operating_channel[3],
                           msg.operating_channel[4])) {
                struct p2p_channels *ch = &dev->channels;

                os_memset(ch, 0, sizeof(*ch));
                ch->reg_class[0].reg_class =
                    msg.operating_channel[3];
                ch->reg_class[0].channel[0] =
                    msg.operating_channel[4];
                ch->reg_class[0].channels = 1;
                ch->reg_classes = 1;
            }

            p2p_channels_intersect(&p2p->channels, &dev->channels,
                           &intersect);

            if (intersect.reg_classes == 0) {
                p2p_dbg(p2p,
                    "No common channels - force deferred flow");
                auto_accept = 0;
            }
        }

        if (auto_accept || reject != P2P_SC_SUCCESS) {
            struct p2ps_provision *tmp;

            if (p2ps_setup_p2ps_prov(p2p, adv_id, session_id,
                         msg.wps_config_methods,
                         session_mac, adv_mac) < 0) {
                reject = P2P_SC_FAIL_UNABLE_TO_ACCOMMODATE;
                goto out;
            }

            tmp = p2p->p2ps_prov;
            tmp->force_freq = forced_freq;
            tmp->pref_freq = pref_freq;
            if (conncap) {
                tmp->conncap = conncap;
                tmp->status = P2P_SC_SUCCESS;
            } else {
                tmp->conncap = auto_accept;
                tmp->status = P2P_SC_FAIL_INCOMPATIBLE_PARAMS;
            }

            if (reject != P2P_SC_SUCCESS)
                goto out;
        }
    }

    if (!msg.status && !auto_accept &&
        (!p2p->p2ps_prov || p2p->p2ps_prov->adv_id != adv_id)) {
        struct p2ps_provision *tmp;

        if (!conncap) {
            reject = P2P_SC_FAIL_INCOMPATIBLE_PARAMS;
            goto out;
        }

        if (p2ps_setup_p2ps_prov(p2p, adv_id, session_id,
                     msg.wps_config_methods,
                     session_mac, adv_mac) < 0) {
            reject = P2P_SC_FAIL_UNABLE_TO_ACCOMMODATE;
            goto out;
        }
        tmp = p2p->p2ps_prov;
        reject = P2P_SC_FAIL_INFO_CURRENTLY_UNAVAILABLE;
        tmp->status = reject;
    }

    /* Not a P2PS Follow-on PD */
    if (!msg.status)
        goto out;

    if (*msg.status && *msg.status != P2P_SC_SUCCESS_DEFERRED) {
        reject = *msg.status;
        goto out;
    }

    if (*msg.status != P2P_SC_SUCCESS_DEFERRED || !p2p->p2ps_prov)
        goto out;

    if (p2p->p2ps_prov->adv_id != adv_id ||
        os_memcmp(p2p->p2ps_prov->adv_mac, msg.adv_mac, ETH_ALEN)) {
        p2p_dbg(p2p,
            "P2PS Follow-on PD with mismatch Advertisement ID/MAC");
        goto out;
    }

    if (p2p->p2ps_prov->session_id != session_id ||
        os_memcmp(p2p->p2ps_prov->session_mac, msg.session_mac, ETH_ALEN)) {
        p2p_dbg(p2p, "P2PS Follow-on PD with mismatch Session ID/MAC");
        goto out;
    }

    method = p2p->p2ps_prov->method;

    conncap = p2p->cfg->p2ps_group_capability(p2p->cfg->cb_ctx,
                          remote_conncap,
                          p2p->p2ps_prov->conncap,
                          &p2p->p2ps_prov->force_freq,
                          &p2p->p2ps_prov->pref_freq);

    resp_fcap.cpt = p2ps_own_preferred_cpt(p2p->p2ps_prov->cpt_priority,
                           req_fcap->cpt);

    p2p_dbg(p2p, "cpt: local:0x%x remote:0x%x result:0x%x",
        p2p->p2ps_prov->cpt_mask, req_fcap->cpt, resp_fcap.cpt);

    p2p_prepare_channel(p2p, dev, p2p->p2ps_prov->force_freq,
                p2p->p2ps_prov->pref_freq, 0);

    /*
     * Ensure that if we asked for PIN originally, our method is consistent
     * with original request.
     */
    if (method & WPS_CONFIG_DISPLAY)
        method = WPS_CONFIG_KEYPAD;
    else if (method & WPS_CONFIG_KEYPAD)
        method = WPS_CONFIG_DISPLAY;

    if (!conncap || !(msg.wps_config_methods & method)) {
        /*
         * Reject this "Deferred Accept*
         * if incompatible conncap or method
         */
        reject = P2P_SC_FAIL_INCOMPATIBLE_PARAMS;
    } else if (!resp_fcap.cpt) {
        p2p_dbg(p2p,
            "Incompatible P2PS feature capability CPT bitmask");
        reject = P2P_SC_FAIL_INCOMPATIBLE_PARAMS;
    } else if ((remote_conncap & (P2PS_SETUP_NEW | P2PS_SETUP_CLIENT) ||
            msg.persistent_dev) && conncap != P2PS_SETUP_NEW &&
           msg.channel_list && msg.channel_list_len &&
           p2p_peer_channels_check(p2p, &p2p->channels, dev,
                       msg.channel_list,
                       msg.channel_list_len) < 0) {
        p2p_dbg(p2p,
            "No common channels in Follow-On Provision Discovery Request");
        reject = P2P_SC_FAIL_NO_COMMON_CHANNELS;
    } else {
        reject = P2P_SC_SUCCESS;
    }


    dev->oper_freq = 0;
    if (reject == P2P_SC_SUCCESS || reject == P2P_SC_SUCCESS_DEFERRED) {
        u8 tmp;

        if (msg.operating_channel)
            dev->oper_freq =
                p2p_channel_to_freq(msg.operating_channel[3],
                            msg.operating_channel[4]);

        if ((conncap & P2PS_SETUP_GROUP_OWNER) &&
            p2p_go_select_channel(p2p, dev, &tmp) < 0)
            reject = P2P_SC_FAIL_NO_COMMON_CHANNELS;
    }

    p2p->p2ps_prov->status = reject;
    p2p->p2ps_prov->conncap = conncap;

out:
    if (reject == P2P_SC_SUCCESS ||
        reject == P2P_SC_FAIL_INFO_CURRENTLY_UNAVAILABLE)
        config_methods = msg.wps_config_methods;
    else
        config_methods = 0;

    /*
     * Send PD Response for an initial PD Request or for follow-on
     * PD Request with P2P_SC_SUCCESS_DEFERRED status.
     */
    if (!msg.status || *msg.status == P2P_SC_SUCCESS_DEFERRED) {
        resp = p2p_build_prov_disc_resp(p2p, dev, msg.dialog_token,
                        reject, config_methods, adv_id,
                        msg.group_id, msg.group_id_len,
                        msg.persistent_ssid,
                        msg.persistent_ssid_len,
                        (const u8 *) &resp_fcap,
                        sizeof(resp_fcap));
        if (!resp) {
            p2p_parse_free(&msg);
            return -1;
        }
        p2p_dbg(p2p, "Sending Provision Discovery Response");
        if (rx_freq > 0)
            freq = rx_freq;
        else
            freq = p2p_channel_to_freq(p2p->cfg->reg_class,
                           p2p->cfg->channel);
        if (freq < 0) {
            p2p_dbg(p2p, "Unknown regulatory class/channel");
            wpabuf_free(resp);
            p2p_parse_free(&msg);
            return -1;
        }
        p2p->pending_action_state = P2P_PENDING_PD_RESPONSE;
        if (p2p_send_action(p2p, freq, sa, p2p->cfg->dev_addr,
                    p2p->cfg->dev_addr,
                    wpabuf_head(resp), wpabuf_len(resp),
                    50) < 0)
            p2p_dbg(p2p, "Failed to send Action frame");
        else
            p2p->send_action_in_progress = 1;

        wpabuf_free(resp);
    }

    if (!dev) {
        p2p_parse_free(&msg);
        return -1;
    }

    freq = 0;
    if (reject == P2P_SC_SUCCESS && conncap == P2PS_SETUP_GROUP_OWNER) {
        freq = p2p_channel_to_freq(p2p->op_reg_class,
                       p2p->op_channel);
        if (freq < 0)
            freq = 0;
    }

    if (!p2p->cfg->p2ps_prov_complete) {
        /* Don't emit anything */
    } else if (msg.status && *msg.status != P2P_SC_SUCCESS &&
           *msg.status != P2P_SC_SUCCESS_DEFERRED) {
        reject = *msg.status;
        p2p->cfg->p2ps_prov_complete(p2p->cfg->cb_ctx, reject,
                         sa, adv_mac, session_mac,
                         NULL, adv_id, session_id,
                         0, 0, msg.persistent_ssid,
                         msg.persistent_ssid_len,
                         0, 0, NULL, NULL, 0, freq,
                         NULL, 0);
    } else if (msg.status && *msg.status == P2P_SC_SUCCESS_DEFERRED &&
           p2p->p2ps_prov) {
        p2p->p2ps_prov->status = reject;
        p2p->p2ps_prov->conncap = conncap;

        if (reject != P2P_SC_SUCCESS)
            p2p->cfg->p2ps_prov_complete(p2p->cfg->cb_ctx, reject,
                             sa, adv_mac, session_mac,
                             NULL, adv_id,
                             session_id, conncap, 0,
                             msg.persistent_ssid,
                             msg.persistent_ssid_len, 0,
                             0, NULL, NULL, 0, freq,
                             NULL, 0);
        else
            p2p->cfg->p2ps_prov_complete(p2p->cfg->cb_ctx,
                             *msg.status,
                             sa, adv_mac, session_mac,
                             group_mac, adv_id,
                             session_id, conncap,
                             passwd_id,
                             msg.persistent_ssid,
                             msg.persistent_ssid_len, 0,
                             0, NULL,
                             (const u8 *) &resp_fcap,
                             sizeof(resp_fcap), freq,
                             NULL, 0);
    } else if (msg.status && p2p->p2ps_prov) {
        p2p->p2ps_prov->status = P2P_SC_SUCCESS;
        p2p->cfg->p2ps_prov_complete(p2p->cfg->cb_ctx, *msg.status, sa,
                         adv_mac, session_mac, group_mac,
                         adv_id, session_id, conncap,
                         passwd_id,
                         msg.persistent_ssid,
                         msg.persistent_ssid_len,
                         0, 0, NULL,
                         (const u8 *) &resp_fcap,
                         sizeof(resp_fcap), freq, NULL, 0);
    } else if (msg.status) {
    } else if (auto_accept && reject == P2P_SC_SUCCESS) {
        p2p->cfg->p2ps_prov_complete(p2p->cfg->cb_ctx, P2P_SC_SUCCESS,
                         sa, adv_mac, session_mac,
                         group_mac, adv_id, session_id,
                         conncap, passwd_id,
                         msg.persistent_ssid,
                         msg.persistent_ssid_len,
                         0, 0, NULL,
                         (const u8 *) &resp_fcap,
                         sizeof(resp_fcap), freq,
                         msg.group_id ?
                         msg.group_id + ETH_ALEN : NULL,
                         msg.group_id ?
                         msg.group_id_len - ETH_ALEN : 0);
    } else if (reject == P2P_SC_FAIL_INFO_CURRENTLY_UNAVAILABLE &&
           (!msg.session_info || !msg.session_info_len)) {
        p2p->p2ps_prov->method = msg.wps_config_methods;

        p2p->cfg->p2ps_prov_complete(p2p->cfg->cb_ctx, P2P_SC_SUCCESS,
                         sa, adv_mac, session_mac,
                         group_mac, adv_id, session_id,
                         conncap, passwd_id,
                         msg.persistent_ssid,
                         msg.persistent_ssid_len,
                         0, 1, NULL,
                         (const u8 *) &resp_fcap,
                         sizeof(resp_fcap), freq, NULL, 0);
    } else if (reject == P2P_SC_FAIL_INFO_CURRENTLY_UNAVAILABLE) {
        size_t buf_len = msg.session_info_len;
        char *buf = os_malloc(2 * buf_len + 1);

        if (buf) {
            p2p->p2ps_prov->method = msg.wps_config_methods;

            utf8_escape((char *) msg.session_info, buf_len,
                    buf, 2 * buf_len + 1);

            p2p->cfg->p2ps_prov_complete(
                p2p->cfg->cb_ctx, P2P_SC_SUCCESS, sa,
                adv_mac, session_mac, group_mac, adv_id,
                session_id, conncap, passwd_id,
                msg.persistent_ssid, msg.persistent_ssid_len,
                0, 1, buf,
                (const u8 *) &resp_fcap, sizeof(resp_fcap),
                freq, NULL, 0);

            os_free(buf);
        }
    }

    /*
     * prov_disc_req callback is used to generate P2P-PROV-DISC-ENTER-PIN,
     * P2P-PROV-DISC-SHOW-PIN, and P2P-PROV-DISC-PBC-REQ events.
     * Call it either on legacy P2P PD or on P2PS PD only if we need to
     * enter/show PIN.
     *
     * The callback is called in the following cases:
     * 1. Legacy P2P PD request, response status SUCCESS
     * 2. P2PS advertiser, method: DISPLAY, autoaccept: TRUE,
     *    response status: SUCCESS
     * 3. P2PS advertiser, method  DISPLAY, autoaccept: FALSE,
     *    response status: INFO_CURRENTLY_UNAVAILABLE
     * 4. P2PS advertiser, method: KEYPAD, autoaccept==any,
     *    response status: INFO_CURRENTLY_UNAVAILABLE
     * 5. P2PS follow-on with SUCCESS_DEFERRED,
     *    advertiser role: DISPLAY, autoaccept: FALSE,
     *    seeker: KEYPAD, response status: SUCCESS
     */
    if (p2p->cfg->prov_disc_req &&
        ((reject == P2P_SC_SUCCESS && !msg.adv_id) ||
         (!msg.status &&
         (reject == P2P_SC_SUCCESS ||
          reject == P2P_SC_FAIL_INFO_CURRENTLY_UNAVAILABLE) &&
          passwd_id == DEV_PW_USER_SPECIFIED) ||
         (!msg.status &&
          reject == P2P_SC_FAIL_INFO_CURRENTLY_UNAVAILABLE &&
          passwd_id == DEV_PW_REGISTRAR_SPECIFIED) ||
         (reject == P2P_SC_SUCCESS &&
          msg.status && *msg.status == P2P_SC_SUCCESS_DEFERRED &&
           passwd_id == DEV_PW_REGISTRAR_SPECIFIED))) {
        const u8 *dev_addr = sa;

        if (msg.p2p_device_addr)
            dev_addr = msg.p2p_device_addr;
        p2p->cfg->prov_disc_req(p2p->cfg->cb_ctx, sa,
                    msg.wps_config_methods,
                    dev_addr, msg.pri_dev_type,
                    msg.device_name, msg.config_methods,
                    msg.capability ? msg.capability[0] : 0,
                    msg.capability ? msg.capability[1] :
                    0,
                    msg.group_id, msg.group_id_len);
    }

    if (reject != P2P_SC_FAIL_INFO_CURRENTLY_UNAVAILABLE)
        p2ps_prov_free(p2p);

    if (reject == P2P_SC_SUCCESS) {
        switch (config_methods) {
        case WPS_CONFIG_DISPLAY:
            dev->wps_prov_info = WPS_CONFIG_KEYPAD;
            break;
        case WPS_CONFIG_KEYPAD:
            dev->wps_prov_info = WPS_CONFIG_DISPLAY;
            break;
        case WPS_CONFIG_PUSHBUTTON:
            dev->wps_prov_info = WPS_CONFIG_PUSHBUTTON;
            break;
        case WPS_CONFIG_P2PS:
            dev->wps_prov_info = WPS_CONFIG_P2PS;
            break;
        default:
            dev->wps_prov_info = 0;
            break;
        }

        if (msg.intended_addr)
            os_memcpy(dev->interface_addr, msg.intended_addr,
                  ETH_ALEN);
    }
    p2p_parse_free(&msg);
    return 0;
}




/*////////////////////////////////////////////////////////////////////////////*/
/*  Utilities                 */
/*  Utilities                 */
/*  Utilities                 */
/*////////////////////////////////////////////////////////////////////////////*/


/* Check if the message contains a valid P2PS PD Request */
static int p2ps_validate_pd_req(struct p2p_data *p2p, struct p2p_message *msg,
                const u8 *addr)
{
    u8 group_id = 0;
    u8 intended_addr = 0;
    u8 operating_channel = 0;
    u8 channel_list = 0;
    u8 config_timeout = 0;
    u8 listen_channel = 0;

#define P2PS_PD_REQ_CHECK(_val, _attr) \
do { \
    if ((_val) && !msg->_attr) { \
        p2p_dbg(p2p, "Not P2PS PD Request. Missing %s", #_attr); \
        return -1; \
    } \
} while (0)

    P2PS_PD_REQ_CHECK(1, adv_id);
    P2PS_PD_REQ_CHECK(1, session_id);
    P2PS_PD_REQ_CHECK(1, session_mac);
    P2PS_PD_REQ_CHECK(1, adv_mac);
    P2PS_PD_REQ_CHECK(1, capability);
    P2PS_PD_REQ_CHECK(1, p2p_device_info);
    P2PS_PD_REQ_CHECK(1, feature_cap);

    /*
     * We don't need to check Connection Capability, Persistent Group,
     * and related attributes for follow-on PD Request with a status
     * other than SUCCESS_DEFERRED.
     */
    if (msg->status && *msg->status != P2P_SC_SUCCESS_DEFERRED)
        return 0;

    P2PS_PD_REQ_CHECK(1, conn_cap);

    /*
     * Note 1: A feature capability attribute structure can be changed
     * in the future. The assumption is that such modifications are
     * backward compatible, therefore we allow processing of msg.feature_cap
     * exceeding the size of the p2ps_feature_capab structure.
     * Note 2: Verification of msg.feature_cap_len below has to be changed
     * to allow 2 byte feature capability processing if
     * struct p2ps_feature_capab is extended to include additional fields
     * and it affects the structure size.
     */
    if (msg->feature_cap_len < sizeof(struct p2ps_feature_capab)) {
        p2p_dbg(p2p, "P2PS: Invalid feature capability len");
        return -1;
    }

    switch (*msg->conn_cap) {
    case P2PS_SETUP_NEW:
        group_id = 1;
        intended_addr = 1;
        operating_channel = 1;
        channel_list = 1;
        config_timeout = 1;
        listen_channel = 1;
        break;
    case P2PS_SETUP_CLIENT:
        channel_list = 1;
        listen_channel = 1;
        break;
    case P2PS_SETUP_GROUP_OWNER:
        group_id = 1;
        intended_addr = 1;
        operating_channel = 1;
        break;
    case P2PS_SETUP_NEW | P2PS_SETUP_GROUP_OWNER:
        group_id = 1;
        operating_channel = 1;
        intended_addr = 1;
        channel_list = 1;
        config_timeout = 1;
        break;
    case P2PS_SETUP_CLIENT | P2PS_SETUP_GROUP_OWNER:
        group_id = 1;
        intended_addr = 1;
        operating_channel = 1;
        channel_list = 1;
        config_timeout = 1;
        break;
    default:
        p2p_dbg(p2p, "Invalid P2PS PD connection capability");
        return -1;
    }

    if (msg->persistent_dev) {
        channel_list = 1;
        config_timeout = 1;
        if (os_memcmp(msg->persistent_dev, addr, ETH_ALEN) == 0) {
            intended_addr = 1;
            operating_channel = 1;
        }
    }

    P2PS_PD_REQ_CHECK(group_id, group_id);
    P2PS_PD_REQ_CHECK(intended_addr, intended_addr);
    P2PS_PD_REQ_CHECK(operating_channel, operating_channel);
    P2PS_PD_REQ_CHECK(channel_list, channel_list);
    P2PS_PD_REQ_CHECK(config_timeout, config_timeout);
    P2PS_PD_REQ_CHECK(listen_channel, listen_channel);

#undef P2PS_PD_REQ_CHECK

    return 0;
}

static struct wpabuf * p2p_build_prov_disc_resp(struct p2p_data *p2p,
                        struct p2p_device *dev,
                        u8 dialog_token,
                        enum p2p_status_code status,
                        u16 config_methods,
                        u32 adv_id,
                        const u8 *group_id,
                        size_t group_id_len,
                        const u8 *persist_ssid,
                        size_t persist_ssid_len,
                        const u8 *fcap,
                        u16 fcap_len)
{
    struct wpabuf *buf;
    size_t extra = 0;
    int persist = 0;

#ifdef CONFIG_WIFI_DISPLAY
    struct wpabuf *wfd_ie = p2p->wfd_ie_prov_disc_resp;
    if (wfd_ie && group_id) {
        size_t i;
        for (i = 0; i < p2p->num_groups; i++) {
            struct p2p_group *g = p2p->groups[i];
            struct wpabuf *ie;
            if (!p2p_group_is_group_id_match(g, group_id,
                             group_id_len))
                continue;
            ie = p2p_group_get_wfd_ie(g);
            if (ie) {
                wfd_ie = ie;
                break;
            }
        }
    }
    if (wfd_ie)
        extra = wpabuf_len(wfd_ie);
#endif /* CONFIG_WIFI_DISPLAY */

    if (p2p->vendor_elem && p2p->vendor_elem[VENDOR_ELEM_P2P_PD_RESP])
        extra += wpabuf_len(p2p->vendor_elem[VENDOR_ELEM_P2P_PD_RESP]);

    buf = wpabuf_alloc(1000 + extra);
    if (buf == NULL)
        return NULL;

    p2p_buf_add_public_action_hdr(buf, P2P_PROV_DISC_RESP, dialog_token);

    /* Add P2P IE for P2PS */
    if (p2p->p2ps_prov && p2p->p2ps_prov->adv_id == adv_id) {
        u8 *len = p2p_buf_add_ie_hdr(buf);
        struct p2ps_provision *prov = p2p->p2ps_prov;
        u8 group_capab;
        u8 conncap = 0;

        if (status == P2P_SC_SUCCESS ||
            status == P2P_SC_SUCCESS_DEFERRED)
            conncap = prov->conncap;

        if (!status && prov->status != -1)
            status = prov->status;

        p2p_buf_add_status(buf, status);
        group_capab = P2P_GROUP_CAPAB_PERSISTENT_GROUP |
            P2P_GROUP_CAPAB_PERSISTENT_RECONN;
        if (p2p->cross_connect)
            group_capab |= P2P_GROUP_CAPAB_CROSS_CONN;
        if (p2p->cfg->p2p_intra_bss)
            group_capab |= P2P_GROUP_CAPAB_INTRA_BSS_DIST;
        p2p_buf_add_capability(buf, p2p->dev_capab &
                       ~P2P_DEV_CAPAB_CLIENT_DISCOVERABILITY,
                       group_capab);
        p2p_buf_add_device_info(buf, p2p, NULL);

        if (persist_ssid && p2p->cfg->get_persistent_group && dev &&
            (status == P2P_SC_SUCCESS ||
             status == P2P_SC_SUCCESS_DEFERRED)) {
            u8 ssid[SSID_MAX_LEN];
            size_t ssid_len;
            u8 go_dev_addr[ETH_ALEN];
            u8 intended_addr[ETH_ALEN];

            persist = p2p->cfg->get_persistent_group(
                p2p->cfg->cb_ctx,
                dev->info.p2p_device_addr,
                persist_ssid, persist_ssid_len, go_dev_addr,
                ssid, &ssid_len, intended_addr);
            if (persist) {
                p2p_buf_add_persistent_group_info(
                    buf, go_dev_addr, ssid, ssid_len);
                if (!is_zero_ether_addr(intended_addr))
                    p2p_buf_add_intended_addr(
                        buf, intended_addr);
            }
        }

        if (!persist && (conncap & P2PS_SETUP_GROUP_OWNER))
            p2ps_add_new_group_info(p2p, dev, buf);

        /* Add Operating Channel if conncap indicates GO */
        if (persist || (conncap & P2PS_SETUP_GROUP_OWNER)) {
            if (p2p->op_reg_class && p2p->op_channel)
                p2p_buf_add_operating_channel(
                    buf, p2p->cfg->country,
                    p2p->op_reg_class,
                    p2p->op_channel);
            else
                p2p_buf_add_operating_channel(
                    buf, p2p->cfg->country,
                    p2p->cfg->op_reg_class,
                    p2p->cfg->op_channel);
        }

        if (persist ||
            (conncap & (P2PS_SETUP_CLIENT | P2PS_SETUP_GROUP_OWNER)))
            p2p_buf_add_channel_list(buf, p2p->cfg->country,
                         &p2p->channels);

        if (!persist && conncap)
            p2p_buf_add_connection_capability(buf, conncap);

        p2p_buf_add_advertisement_id(buf, adv_id, prov->adv_mac);

        if (persist ||
            (conncap & (P2PS_SETUP_CLIENT | P2PS_SETUP_GROUP_OWNER)))
            p2p_buf_add_config_timeout(buf, p2p->go_timeout,
                           p2p->client_timeout);

        p2p_buf_add_session_id(buf, prov->session_id,
                       prov->session_mac);

        p2p_buf_add_feature_capability(buf, fcap_len, fcap);
        p2p_buf_update_ie_hdr(buf, len);
    } else if (status != P2P_SC_SUCCESS || adv_id) {
        u8 *len = p2p_buf_add_ie_hdr(buf);

        p2p_buf_add_status(buf, status);

        if (p2p->p2ps_prov)
            p2p_buf_add_advertisement_id(buf, adv_id,
                             p2p->p2ps_prov->adv_mac);

        p2p_buf_update_ie_hdr(buf, len);
    }

    /* WPS IE with Config Methods attribute */
    p2p_build_wps_ie_config_methods(buf, config_methods);

#ifdef CONFIG_WIFI_DISPLAY
    if (wfd_ie)
        wpabuf_put_buf(buf, wfd_ie);
#endif /* CONFIG_WIFI_DISPLAY */

    if (p2p->vendor_elem && p2p->vendor_elem[VENDOR_ELEM_P2P_PD_RESP])
        wpabuf_put_buf(buf, p2p->vendor_elem[VENDOR_ELEM_P2P_PD_RESP]);

    return buf;
}

static void p2p_build_wps_ie_config_methods(struct wpabuf *buf,
                        u16 config_methods)
{
    u8 *len;
    wpabuf_put_u8(buf, WLAN_EID_VENDOR_SPECIFIC);
    len = wpabuf_put(buf, 1);
    wpabuf_put_be32(buf, WPS_DEV_OUI_WFA);

    /* Config Methods */
    wpabuf_put_be16(buf, ATTR_CONFIG_METHODS);
    wpabuf_put_be16(buf, 2);
    wpabuf_put_be16(buf, config_methods);

    p2p_buf_update_ie_hdr(buf, len);
}

static void p2ps_add_new_group_info(struct p2p_data *p2p,
                    struct p2p_device *dev,
                    struct wpabuf *buf)
{
    int found;
    u8 intended_addr[ETH_ALEN];
    u8 ssid[SSID_MAX_LEN];
    size_t ssid_len;
    int group_iface;
    unsigned int force_freq;

    if (!p2p->cfg->get_go_info)
        return;

    found = p2p->cfg->get_go_info(
        p2p->cfg->cb_ctx, intended_addr, ssid,
        &ssid_len, &group_iface, &force_freq);
    if (found) {
        if (force_freq > 0) {
            p2p->p2ps_prov->force_freq = force_freq;
            p2p->p2ps_prov->pref_freq = 0;

            if (dev)
                p2p_prepare_channel(p2p, dev, force_freq, 0, 0);
        }
        p2p_buf_add_group_id(buf, p2p->cfg->dev_addr,
                     ssid, ssid_len);

        if (group_iface)
            p2p_buf_add_intended_addr(buf, p2p->intended_addr);
        else
            p2p_buf_add_intended_addr(buf, intended_addr);
    } else {
        if (!p2p->ssid_set) {
            p2p_build_ssid(p2p, p2p->ssid, &p2p->ssid_len);
            p2p->ssid_set = 1;
        }

        /* Add pre-composed P2P Group ID */
        p2p_buf_add_group_id(buf, p2p->cfg->dev_addr,
                     p2p->ssid, p2p->ssid_len);

        if (group_iface)
            p2p_buf_add_intended_addr(
                buf, p2p->intended_addr);
        else
            p2p_buf_add_intended_addr(
                buf, p2p->cfg->dev_addr);
    }
}

static u8 p2ps_own_preferred_cpt(const u8 *cpt_priority, u8 req_cpt_mask)
{
    int i;

    for (i = 0; cpt_priority[i]; i++)
        if (req_cpt_mask & cpt_priority[i])
            return cpt_priority[i];

    return 0;
}

static int p2ps_setup_p2ps_prov(struct p2p_data *p2p, u32 adv_id,
                u32 session_id, u16 method,
                const u8 *session_mac, const u8 *adv_mac)
{
    struct p2ps_provision *tmp;

    if (!p2p->p2ps_prov) {
        p2p->p2ps_prov = os_zalloc(sizeof(struct p2ps_provision) + 1);
        if (!p2p->p2ps_prov)
            return -1;
    } else {
        os_memset(p2p->p2ps_prov, 0, sizeof(struct p2ps_provision) + 1);
    }

    tmp = p2p->p2ps_prov;
    tmp->adv_id = adv_id;
    tmp->session_id = session_id;
    tmp->method = method;
    os_memcpy(tmp->session_mac, session_mac, ETH_ALEN);
    os_memcpy(tmp->adv_mac, adv_mac, ETH_ALEN);
    tmp->info[0] = '\0';

    return 0;
}

uint32_t isExtWpsInProgress()
{
    return gExternalApp.extWps && gExtWpsInProgress;
}

uint32_t isExtWpsScanning()
{
    return gExternalApp.extWps && gExtWpsScanning;
}

/******************************************************************************
  Function          : extWpsRemoveWpsNetworks

  Description       : Remove all WPS wpa_supplicant profiles.

  Input parameters  : wpa_s     - wpa_supplicant instance

  Output parameters : network

  Return value      : none.

******************************************************************************/
static void extWpsRemoveWpsNetworks(struct wpa_supplicant *wpa_s) 
{
    struct wpa_ssid *network = wpa_s->conf->ssid;
    struct wpa_ssid *next = NULL;

    while (network)
    {
        next = network->next;

        if (network->temporary && network->key_mgmt == WPA_KEY_MGMT_WPS)
        {
            wpa_config_remove_network(wpa_s->conf, network->id);
        }

        network = next;
    }
}

void extWpsClear()
{
    struct wpa_supplicant *wpa_s;
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    gExtWpsInProgress = 0;

    extern cmeProfileInfo_t gAdHocProfile_ull;
    gAdHocProfile_ull.profile.key_mgmt &= ~WPA_KEY_MGMT_WPS;

    extWpsRemoveWpsNetworks(wpa_s);

    // Restore the wpa_supplicant EAPOL SM after WPS connection is done/canceled
    extWpsRestoreEapolSM();
}

void extWpsClearScanning()
{
    struct wpa_supplicant *wpa_s;
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    gExtWpsScanning = 0;

    extern cmeProfileInfo_t gAdHocProfile_ull;
    gAdHocProfile_ull.profile.key_mgmt &= ~WPA_KEY_MGMT_WPS;

    extWpsRemoveWpsNetworks(wpa_s);
}


/******************************************************************************
  Function          : extWpsConfigureNetwork

  Description       : Configure a wpa_supplicant network profile for WPS scan or connection.

  Input parameters  : wpa_s     - wpa_supplicant instance
                      network   - previously created wpa_supplicant network profile
                      ssid      - Optinal character array
                      ssidLen   - Length of the ssid array
                      is_pin    - FALSE: PBC, TRUE: PIN

  Output parameters : network

  Return value      : none.

******************************************************************************/
static void extWpsConfigureNetwork(struct wpa_supplicant *wpa_s, struct wpa_ssid *network, uint8_t *ssid, uint32_t ssidLen, uint8_t is_pin)
{
    wpa_config_set_network_defaults(network);

    network->key_mgmt = WPA_KEY_MGMT_WPS;
	network->temporary = 1;
	network->p2p_group = 0;
    
    char phase1_pbc[] = "pbc=1";
    char phase1_pin[] = "pin=1";
    char *phase1 = !is_pin ? phase1_pbc : phase1_pin;

    network->eap.phase1 = os_strdup(phase1);
    ASSERT_GENERAL((uint32_t)network->eap.phase1);

    network->eap.identity = os_memdup(WSC_ID_ENROLLEE, WSC_ID_ENROLLEE_LEN);
    ASSERT_GENERAL((uint32_t)network->eap.identity);
    network->eap.identity_len = WSC_ID_ENROLLEE_LEN;

    if (ssid && ssidLen)
    {
        network->ssid = os_memdup(ssid, ssidLen);
        ASSERT_GENERAL((uint32_t)network->ssid);
        network->ssid_len = ssidLen;
    }

   	if (wpa_s->wps_fragment_size)
    {
		network->eap.fragment_size = wpa_s->wps_fragment_size;
    }
}

/******************************************************************************
  Function          : extWpsScan

  Description       : Initiate a WPS Scan using wpa_supplicant candidate scan.

  Input parameters  : is_pin    - FALSE: PBC, TRUE: PIN

  Output parameters : none.

  Return value      : none.

******************************************************************************/
int32_t extWpsScan(uint8_t is_pin)
{
    struct wpa_supplicant *wpa_s;
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    if (!(wpa_s->wpa_state == WPA_DISCONNECTED || wpa_s->wpa_state == WPA_COMPLETED))
    {
        return -1;
    }

    extern cmeProfileInfo_t gAdHocProfile_ull;
    gAdHocProfile_ull.uniqueProfileId = 0;
	gAdHocProfile_ull.profile.ssid_len = 0;
    CME_SetWPSAdHocConnection();

    // wpa_supplicant requires a WPS profile to be configured in order to perform WPS scan
    // This is because it gets the WPS method from the profiles and adds the proper IE to the probe reqs
    extWpsRemoveWpsNetworks(wpa_s);
    struct wpa_ssid *network = wpa_config_add_network(wpa_s->conf);
    extWpsConfigureNetwork(wpa_s, network, NULL, 0, is_pin);

    wpa_supplicant_cancel_sched_scan(wpa_s);
    wpa_supplicant_cancel_scan(wpa_s);
    
    // Set the supplicant scan result handler to "scan only" to prevent it
    // from trying to connect to the configured WPS proile
    wpa_s->scan_res_handler = scan_only_handler;
    wpa_s->scan_req = MANUAL_SCAN_REQ;
    gExtWpsScanning = 1;

    wpa_supplicant_req_scan(wpa_s, 0, 0);

    return 0;
}

/******************************************************************************
  Function          : extWpsConnect

  Description       : Initiate a WPS connect using wpa_supplicant.

  Input parameters  : ssid      - Optinal character array
                      ssidLen   - Length of the ssid array
                      bssid     - BSSID, not used for now
                      is_pin    - FALSE: PBC, TRUE: PIN

  Output parameters : none.

  Return value      : none.

******************************************************************************/
int32_t extWpsConnect(char *ssid, uint32_t ssidLen, uint8_t *bssid, uint8_t is_pin)
{
    if (!((ssid != NULL) && (ssidLen > 0)))
    {
        return -1;
    }

    if (gExtWpsInProgress)
    {
        return -1;
    }

    struct wpa_supplicant *wpa_s;
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    if (wpa_s->wpa_state != WPA_DISCONNECTED)
    {
        return -1;
    }

	if (wpa_s->last_scan_res_used == 0)
    {
		return -1;
    }

    struct os_reltime now = {0};
	os_get_reltime(&now);

    if (os_reltime_expired(&now, &wpa_s->last_scan, 10))
    {
		wpa_printf(MSG_DEBUG, "Fast associate: Old scan results");
		return -1;
	}

    struct wpa_ssid *network = wpa_config_add_network(wpa_s->conf);
    extWpsConfigureNetwork(wpa_s, network, (uint8_t*)ssid, ssidLen, is_pin);

    struct wpa_ssid *selected_network = network;
    struct wpa_bss *selected_bss = wpa_supplicant_pick_network(wpa_s, &selected_network);
    if (selected_bss == NULL)
    {
        extWpsRemoveWpsNetworks(wpa_s);
        return -1;
    }

    // Store a pointer to the wpa_supplicant instance EAPOL SM before setting it to NULL
    gExtWpsWpaEapolSM = wpa_s->eapol;

    // Set the EAPOL SM  pointer to NULL to stop the wpa_supplicant from initiating WPS enrolee registration
    // "eapol_sm_notify_eap_success()" is the wpa_supplicant function that starts the EAPOL SM, which calls: eapol_sm_step()"
    // It exits immediately if wpa->eapol == NULL, which prevents the SM from starting
    wpa_s->eapol = NULL; // this prevents EAP Start from getting trasmitted
    
    extern cmeProfileInfo_t gAdHocProfile_ull;
    gAdHocProfile_ull.uniqueProfileId = 0;
	gAdHocProfile_ull.profile.ssid_len = 0;
    CME_SetWPSAdHocConnection();

   	wpa_s->disconnected = 0;
	wpa_s->reassociate = 1;

    gExtWpsInProgress = 1;

    return wpa_supplicant_connect(wpa_s, selected_bss, network);
}

/******************************************************************************
  Function          : extWpsConnectAfter

  Description       : Initiate the regular connect with the creditials acquired
                      from a WPS connection.
                      We can't do this with the regular Wlan_Connect() because it uses adhoc profile.
                      This function creates a real supplicant profile that allows us to skip scanning
                      after the initial WPS scan/connection

  Input parameters  : ssid      - Optinal character array
                      ssidLen   - Length of the ssid array
                      secType   - Security type
                      password  - passphrase
                      passwordLen - passphrase length

  Output parameters : none.

  Return value      : none.

******************************************************************************/
int32_t extWpsConnectAfter(uint8_t *ssid, uint32_t ssidLen, uint16_t secType, uint8_t *password, uint32_t passwordLen)
{
    struct wpa_supplicant *wpa_s;
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    CMEWlanAddGetProfile_t apCmd;
    _cme_minimized_wpa_ssid_t apSsid;

    if (gExtWpsInProgress )
    {
        return -1;
    }

    if (wpa_s->wpa_state != WPA_DISCONNECTED)
    {
        return -1;
    }

    struct wpa_ssid *network = wpa_config_add_network(wpa_s->conf);
    
    memset(&apCmd, 0, sizeof(CMEWlanAddGetProfile_t));
    memset(&apSsid, 0, sizeof(_cme_minimized_wpa_ssid_t));

    apCmd.SecType = secType;
    apCmd.PasswordLen = passwordLen;
    apCmd.SsidLen = ssidLen;

    memcpy(apSsid.ssid, ssid, sizeof(apSsid.ssid));
    apSsid.ssid_len = ssidLen;

    extSetSecurityParams(&apCmd, &apSsid, (int8_t*)password);
    network->key_mgmt = apSsid.key_mgmt;
    network->pairwise_cipher = apSsid.pairwise_cipher;
    network->group_cipher = apSsid.group_cipher;
    network->proto = apSsid.proto;
    network->auth_alg = apSsid.auth_alg;
    network->psk_set = apSsid.psk_set;
    
    memcpy(network->psk, apSsid.psk, sizeof(network->psk));
    network->passphrase = apSsid.passphrase;

    network->ssid = os_malloc(ssidLen);
    memcpy(network->ssid, ssid, ssidLen);
    network->ssid_len = ssidLen;

    wpa_supplicant_select_network(wpa_s, network);

    return 0;
}

/******************************************************************************
  Function          : extWpsIsLinkWps

  Description       : Check if the link is using external WPS and WPS is in progress
                      This allow the Rx EAPOL handler to forward EAPOL 
                      to the application that implements the WPS regisration process.
                      
  Input parameters  : hlid      - wlan links link ID

  Output parameters : netifId   - network interface ID

  Return value      : is the link using external WPS and WPS connection is in progress

******************************************************************************/
uint32_t extWpsIsLinkWps(uint32_t hlid, uint8_t *netifId)
{
    TInternalWlanLinkInfo *linkInfo;
    
    uint32_t ret = FALSE;

    if (wlanLinks_GetLink(hlid, &linkInfo) == NOK)
    {
        return FALSE;
    }

    *netifId = linkInfo->info.uNetIfId;

    switch (linkInfo->info.eIfMode)
    {
        case TIWDRV_IF_MODE_SAP:
        case TIWDRV_IF_MODE_P2PGO:
        {
            if (linkInfo->info.eType == WLANLINK_TYPE_SPECIFIC)
            {
                ret = isextWPS() && extWpsIsApLinkWps(hlid, linkInfo);
            }
        }
        break;
        case TIWDRV_IF_MODE_STA:
        {
            ret = isextWPS() && isExtWpsInProgress();
        }
        break;
        default:
        {
            ret = FALSE;
        }
        break;
    }

    return ret;
}

/******************************************************************************
  Function          : extWpsCancelAuthTimeout

  Description       : Cancel the supplicant auth timeout that triggers if WPS registration doesn't start
                      
  Input parameters  : none.

  Output parameters : none.

  Return value      : none.

******************************************************************************/
void extWpsCancelAuthTimeout()
{
    if (!gExtWpsInProgress)
    {
        return;
    }

    struct wpa_supplicant *wpa_s;
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);
    
    // Cancel the auth timeout to prevent the supplicant from disconnecting when EAP conneciton times out
    wpa_supplicant_cancel_auth_timeout(wpa_s);
}


/******************************************************************************
  Function          : extWpsRestoreEapolSM

  Description       : Restore the EAPOL SM pointer to allow non-WPS authentication to occur
                      
  Input parameters  : none.

  Output parameters : none.

  Return value      : none.

******************************************************************************/
void extWpsRestoreEapolSM()
{
    struct wpa_supplicant *wpa_s;
    drv_getStaIface(gpSupplicantGlobals, &wpa_s);

    if ((gExtWpsWpaEapolSM != NULL) && (wpa_s->eapol == NULL))
    {
        wpa_s->eapol = gExtWpsWpaEapolSM;
        gExtWpsWpaEapolSM = NULL;
    }
}
