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
 * driver_osprey_mx_scan.h
 *
 *  Created on: Jun 24, 2020
 *      Author: user
 */

#ifndef HOSTAP_SRC_DRIVERS_DRIVER_OSPREY_MX_SCAN_H_
#define HOSTAP_SRC_DRIVERS_DRIVER_OSPREY_MX_SCAN_H_

#include <inc_common_fw/cc3xxx_public_commands.h>
#include "driver_osprey_mx.h"
#include "cme_defs.h"
#include "rates.h"
#include "mlme_parser.h"
#include "public_types.h"



int8_t trnspt_cmd_build_scan_channel_list(ScanParams_t *scanParam,
                                        EScanRequestType scanType,
                                        struct wpa_driver_scan_params *apSuppParams,
                                        uint8_t max_sched_scan_plans,WlanBandCfg_e Band);


// TODO: need to implement
//int8_t cc3xxx_trnspt_cmd_if_check_scan_tagged_frame(CC33_FrameRxDesc_t *frame);
bool mx_driver_scan_is_scan_tagged_frame(void *pDesc);
int cc3xxx_trnspt_cmd_if_check_scan_tagged_frame(uint32_t aRoleId, void *desc);


#endif /* HOSTAP_SRC_DRIVERS_DRIVER_OSPREY_MX_SCAN_H_ */
