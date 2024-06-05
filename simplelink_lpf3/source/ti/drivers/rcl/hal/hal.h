/*
 * Copyright (c) 2020-2024, Texas Instruments Incorporated
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

#ifndef __rcl_hal_h__
#define __rcl_hal_h__

#include <stdint.h>

void hal_init_fsm(void (*setupFsmCb)(void), void (*schedFsmCb)(void),
                  void (*commandFsmCb)(void));
void hal_trigger_command_fsm(void);
void hal_trigger_dispatch_fsm(void);
void hal_trigger_scheduler_fsm(void);
uint32_t hal_get_command_ifg_reg(void);
uint32_t hal_get_dispatch_ifg_reg(void);
uint32_t hal_get_current_time(void);
void hal_enable_setup_time_irq(void);
void hal_setup_setup_time(uint32_t setupTime);
void hal_setup_start_time(uint32_t startTime);
void hal_setup_packet_timeout(uint32_t stopTime);
void hal_setup_hard_stop_time(uint32_t stopTime);
void hal_enable_hard_stop_time_irq(void);
void hal_disable_hard_stop_time_irq(void);
void hal_setup_graceful_stop_time(uint32_t stopTime);
void hal_enable_graceful_stop_time_irq(void);
void hal_cancel_setup_time(void);
void hal_cancel_start_time(void);
void hal_cancel_packet_timeout(void);
void hal_cancel_hard_stop_time(void);
void hal_cancel_graceful_stop_time(void);
void hal_init_dispatch_radio_interrupts(uint32_t mask);
void hal_enable_command_radio_interrupt(uint32_t mask);
void hal_disable_command_radio_interrupt(uint32_t mask);
void hal_clear_command_radio_interrupt(uint32_t mask);
void hal_disable_all_command_radio_interrupts(void);
void hal_disable_all_dispatch_radio_interrupts(void);
void hal_temperature_init(void);
int16_t hal_get_temperature(void);
uint32_t hal_get_hfxt_ratio(void);
uint32_t hal_get_hfxt_ratio_default(void);

typedef enum {
    HAL_TIMER_EVT_NONE = 0,
    HAL_TIMER_EVT_SETUP = 1,
    HAL_TIMER_EVT_START = 2,
    HAL_TIMER_EVT_GRACEFUL_STOP = 3,
    HAL_TIMER_EVT_HARD_STOP = 4,
    HAL_TIMER_EVT_PACKET_TIMEOUT = 5,
} HalTimerEvent;

typedef enum {
    RCL_POWER_STANDBY_AWAKE = 0,
    RCL_POWER_XTAL_AVAILABLE = 1,
    RCL_POWER_STANDBY_ENTER = 2,
} RCL_PowerEvent;

HalTimerEvent hal_check_clear_timer_compare(void);
void hal_setup_cmd_start_cap(void);
void hal_arm_cmd_start_cap(void);
uint32_t hal_get_cmd_start_cap(void);
void hal_setup_sync_found_cap(void);
void hal_arm_sync_found_cap(void);
uint32_t hal_get_sync_found_cap(void);
void hal_setup_cmd_done_cap(void);
void hal_arm_cmd_done_cap(void);
uint32_t hal_get_cmd_done_cap(void);
void hal_set_rcl_clock_enable(uint16_t mask);
void hal_clear_rcl_clock_enable(uint16_t mask);
void hal_enable_clk_buffer(void);
void hal_power_set_constraint(void);
void hal_power_release_constraint(void);
void hal_power_open(void (*f)(RCL_PowerEvent));
void hal_power_close(void);
#endif
