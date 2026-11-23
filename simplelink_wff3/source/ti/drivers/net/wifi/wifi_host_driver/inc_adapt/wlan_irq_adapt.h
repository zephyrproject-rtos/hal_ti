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
#ifndef ADAPTATION_WLAN_IRQ_ADAPT_H_
#define ADAPTATION_WLAN_IRQ_ADAPT_H_
#include <stddef.h>
#include <stdint.h>
#include <string.h>

typedef void (*IRQCallbackFnType)(void);

/**
 * @brief Initialize the WLAN IRQ callback.
 *
 * @param cb Callback to be called when the interrupt occurs.
 */
extern void wlan_IRQInit(void (*cb));

/**
 * @brief Initialize the WLAN IRQ callback, called before module start to receive the init interrupt of the FW.
 *
 * @param cb Callback to be called when the interrupt occurs.
 */
extern void wlan_IRQInitBeforeHwInit(void (*cb));

/**
 * @brief Deinitialize the WLAN IRQ callback.
 */
extern void wlan_IRQDeinit(void);

/**
 * @brief Enable the WLAN IRQ interrupt.
 */
extern void wlan_IRQEnableInt(void);

/**
 * @brief Disable the WLAN IRQ interrupt.
 */
extern void wlan_IRQDisableInt(void);

/**
 * @brief Clear pending interrupts.
 */
extern void wlan_IRQClearInt(void);

/**
 * @brief Turn off the WiFi module.
 */
extern void wlan_TurnOffWlan(void);

/**
 * @brief Turn on the WiFi module.
 */
extern void wlan_TurnOnWlan(void);

/**
 * @brief Get the state of the WiFi module.
 *
 * @return State of the WiFi module.
 */
extern int wlan_GetStateWlan(void);

/**
 * @brief Disable the IRQ when on IRQ handler.
 */
void wlan_IRQDisableOnIRQHandler(void);


#endif /* ADAPTATION_WLAN_IRQ_ADAPT_H_ */
