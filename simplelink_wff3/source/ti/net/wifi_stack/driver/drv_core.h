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
 * drv_core.h
 *
 *  Created on: Mar 7, 2021
 *      Author: a0220079
 */

#ifndef HOST_IF_DRV_CORE_H_
#define HOST_IF_DRV_CORE_H_


#include <inc_common_fw/cc3xxx_public_commands.h>
#include <stdio.h>

#include "common.h"
#include "drivers/driver.h"
#include "public_types.h"
#include "cme_common.h"

struct drv_cmd_ops {

    int (*enable_role)(void *apDrv, Role_e aRoleType);
    int (*disable_role)(void *apDrv);
    int (*start_role)(void *apDrv, void * apParams, RoleCommonParam_t *apRates, SlotTime_e aSlotTime);
    int (*stop_role)(void *apDrv);
    int (*change_type)(void *apDrv, Role_e aRoleType);
    int (*site_survey)(uint8_t aRoleId, CMEWlanScanCommon_t* pScanCommon);
    int (*one_shot)(void *apDrv, struct wpa_driver_scan_params *apParams);
    int (*set_key)(SetKey_t *pParam);
    int (*site_survey_scan)(uint8_t roleID);
    int (*send_scan_stop)(uint8_t roleID, EScanRequestType scanRequestType, Bool_e isET);
    int (*sched_scan)(void *apDrv, struct wpa_driver_scan_params *apParams);
    int (*scan_tag)(uint32_t aRoleId, void *desc);
    int (*set_beacon_info)(void *apDrv, struct wpa_driver_scan_params *apParams);
    int (*send_deauth_disassoc)(void *apDrv, uint8_t  *pDestAddr, uint32_t frameType, uint16_t reason);
    int (*remain_on_channel)(void *apDrv, unsigned int aFreq);
    int (*cancel_remain_on_channel)(void *apDrv);
    int (*set_peer_state)(uint8_t lid, uint8_t linkConnectionState, Bool_e WMM);
    int (*assoc_peer)(void *apDrv, PeerCap_t *aPeerCap, BssCap_t* aBssCap, uint32_t localSupportedRates, uint32_t link, uint8_t wmmEnable, uint16_t useProtection);
    int (*tx_param)(void *apDrv, AcCfg_t *pParamAc, uint8_t psScheme, Bool_e isMuEdca, uint8_t *pParamMuEdca, uint8_t currAc);
    int (*set_ap_template)(uint32_t aRoleId,struct wpa_driver_ap_params *apParams);
    int (*sta_add)(void *apPriv, struct hostapd_sta_add_params *apParams);
    int (*sta_remove)(void *apPriv, const u8 *apAddr);
    int (*sta_set_flags)(void *apPriv, const u8 *apAddr,unsigned int total_flags, unsigned int flags_or, unsigned int flags_and);
    int (*set_ps)(uint8_t aRoleId, uint8_t aMode);

};



/* NULL terminated array of linked in driver wrappers */
extern const struct drv_cmd_ops *const device_cmd_ops[];


#endif /* HOST_IF_DRV_CORE_H_ */
