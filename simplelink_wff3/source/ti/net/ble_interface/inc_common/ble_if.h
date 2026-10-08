/*
 * ble_transport.h
 *
 * Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
#ifndef BLE_IF_C_
#define BLE_IF_C_

#include <stdio.h>
#include <stdint.h>

typedef int (*ble_cmd_cb_t)(uint8_t *data, uint16_t len);
typedef int (*ble_event_cb_t)(uint8_t* data, uint16_t len);
typedef int (*ble_event_cb_reg_t)(ble_event_cb_t cb);

typedef struct
{
    ble_cmd_cb_t cmd_cb;
    ble_event_cb_t event_cb;
    ble_event_cb_reg_t event_cb_reg;
} ble_if_cb_t;

typedef enum
{
    VENDOR_SPECIFIC_FORMAT_TI,
    VENDOR_SPECIFIC_FORMAT_NIMBLE
} vsFormat_e;

int BleIf_OpenTransport();
int BleIf_CloseTransport();
int BleIf_SendCommand(uint8_t* cmd, uint16_t cmdLen);
int BleIf_EventCbRegister(ble_event_cb_t cb);
int BleIf_VendorSpecificEventFormat(vsFormat_e vsFormat);
int BleIf_VendorSpecificEventHandler(uint8_t* data, uint16_t *len);
int BleIf_EnableBLE();
int BleIf_SetBdAddr(const unsigned char *pBdAddr);
int BleIf_SetSeed(uint8_t size);

#endif /* BLE_IF_C_ */
