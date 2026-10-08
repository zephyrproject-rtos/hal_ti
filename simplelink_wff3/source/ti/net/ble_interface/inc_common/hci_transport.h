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
#ifndef __HCI_TRANSPORT_H__
#define __HCI_TRANSPORT_H__

#include <stdio.h>
#include <stdint.h>
#include "ble_if.h"
#include "osi_kernel.h"

/*****************************************************************************/
/* DEFINITIONS                                                               */
/*****************************************************************************/
#define HCI_TRANSPORT_UART_BLE      0
#define HCI_TRANSPORT_UART_NPI      1
#define HCI_TRANSPORT_NUM_INSTANCES 2


/*****************************************************************************/
/* TYPEDEFS                                                               */
/*****************************************************************************/
typedef int (*hcitrans_rx_cb_t)(uint8_t *data, uint16_t len);

typedef int (*hcitrans_Read)(uint8_t* buf, uint16_t len);
typedef int (*hcitrans_Write)(uint8_t* buf, uint16_t len);

typedef struct
{
    hcitrans_Read read;
    hcitrans_Write write;
    hcitrans_rx_cb_t rx_cb;
}hciTransport_t;

typedef struct
{
    OsiThread_t threadTcb;
    char*       pThreadName;
    uint32_t    stackSize;
    uint32_t    priority;
    P_THREAD_ENTRY_FUNCTION      pEntryFunc;
    uint8_t     instance;
    Bool_e      threadRunning;
}hciThread_t;

//*****************************************************************************
/* INTERFACE                                                                 */
//*****************************************************************************
void HciTransport_Init(uint8_t instance, const hciTransport_t* const pTransport);
void HciTransport_Release(uint8_t instance);
int HciTransport_IsInitialized(uint8_t instance);
int HciTransport_WriteHciPacketToNpi(uint8_t* pHciPacket, uint16_t hciLen);
int HciTransport_WriteHciPacketToCtrl(uint8_t* pHciPacket, uint16_t hciLen);
int HciTransport_ReadHciPacket(uint8_t instance, uint8_t* pHciPacket, uint16_t* hciLen);
int HciTransport_RxCallbackbRegister(uint8_t instance, hcitrans_rx_cb_t cb);
int HciTransport_HciRxCallbackbRegister(hcitrans_rx_cb_t cb);
int HciTransport_NpiRxCallbackbRegister(hcitrans_rx_cb_t cb);

#endif // __HCI_TRANSPORT_H__
