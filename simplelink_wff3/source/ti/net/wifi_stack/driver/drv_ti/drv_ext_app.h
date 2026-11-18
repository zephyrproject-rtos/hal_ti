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
#ifndef _DRV_EX_APP_
#define _DRV_EX_APP_

#include "wlan_if.h"
#include "wlan_links.h"
#include "../../wpa_supplicant/wpa_supplicant_i.h"

int32 ext_p2p_process_prov_disc_req(WlanProvDiscResp_t* actionBuff);

int ext_wps_registrar_button_pushed(struct wpa_supplicant *wpa_s, const u8 *p2p_dev_addr);
int ext_wps_registrar_add_pin(struct wpa_supplicant *wpa_s, const u8 *addr,
			                  const u8 *uuid, const u8 *pin, size_t pin_len,
			                  int timeout);

void extAppDeinit();

uint32_t isextP2P();
uint32_t isextWPS();
uint32_t isextDPP();
uint32_t isextWPSDone();
uint32_t isextWPSInProgress();
void set_extP2P(uint8_t val);
void set_extWPS(uint8_t val);
void set_extDPP(uint8_t val);
void set_extWPSDone(uint8_t val);

uint32_t isExtWpsInProgress();
uint32_t isExtWpsScanning();
void extWpsClear();
void extWpsClearScanning();
int32_t extWpsScan(uint8_t is_pin);
int32_t extWpsConnect(char *ssid, uint32_t ssidLen, uint8_t *bssid, uint8_t is_pin);
int32_t extWpsConnectAfter(uint8_t *ssid, uint32_t ssidLen, uint16_t secType, uint8_t *password, uint32_t passwordLen);
uint32_t extWpsIsLinkWps(uint32_t hlid, uint8_t *netifId);
void extWpsCancelAuthTimeout();
void extWpsRestoreEapolSM();


typedef struct
{
    uint8_t extWps;
    uint8_t extP2P;
    uint8_t extWpsDone;
    uint8_t extDPP;
}externalApp_t;

#endif //_DRV_EX_APP_
