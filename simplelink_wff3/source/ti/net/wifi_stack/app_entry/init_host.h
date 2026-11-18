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
#ifndef INIT_H_
#define INIT_H_

#include "stdio.h"
#include "osi_kernel.h"


//#define PLT_MODE 1

/******************************************************************************
                      LOCAL FUNCTION PROTOTYPES
******************************************************************************/
void    DeinitCB(void * hCbHndl);
int32_t InitFW(void);
int32_t DeinitFW(void);
int32_t HwInit(void);
int32_t DeHwInit(void);
int32_t ChipWakeUp(void);

/******************************************************************************
                      EXTERN GLOBAL
******************************************************************************/


/******************************************************************************
                                    STRUCTUS 
******************************************************************************/
typedef struct {
    uint32_t n;
    uint32_t m;
    uint32_t p;
    uint32_t q;
    uint8_t swallow;
}ClkCfg_t;

typedef struct   {
    uint8_t phy_standalone;
    uint8_t spare0;
    uint8_t enable_clpc;
    uint8_t enable_tx_low_pwr_on_siso_rdl;
    uint8_t auto_detect;
    uint8_t dedicated_fem;

    uint8_t low_band_component;

    /* Bit 0: One Hot, Bit 1: Control Enable, Bit 2: 1.8V, Bit 3: 3V */
    uint8_t low_band_component_type;

    uint8_t high_band_component;

    /* Bit 0: One Hot, Bit 1: Control Enable, Bit 2: 1.8V, Bit 3: 3V */
    uint8_t high_band_component_type;
    uint8_t number_of_assembled_ant2_4;
    uint8_t number_of_assembled_ant5;
    uint8_t pin_muxing_platform_options[2];
    uint8_t external_pa_dc2dc;
    uint8_t tcxo_ldo_voltage;
    uint8_t xtal_itrim_val;
    uint8_t srf_state;
    uint8_t srf1[16];
    uint8_t srf2[16];
    uint8_t srf3[16];
    uint8_t io_configuration;
    uint8_t sdio_configuration;
    uint8_t settings;
    uint8_t rx_profile;
    uint8_t per_chan_pwr_limit_arr_11abg[150];
    uint8_t pwr_limit_reference_11_abg;
    uint8_t per_chan_pwr_limit_arr_11p[7];
    uint8_t pwr_limit_reference_11p;
    uint8_t spare1;
    uint8_t per_chan_bo_mode_11_abg[13];
    uint8_t per_chan_bo_mode_11_p[4];
    uint8_t primary_clock_setting_time;
    uint8_t clock_valid_on_wake_up;
    uint8_t secondary_clock_setting_time;
    uint8_t board_type;
    /* enable point saturation */
    uint8_t psat;
    /* low/medium/high Tx power in dBm for STA-HP BG */
    int8_t low_power_val;
    int8_t med_power_val;
    int8_t high_power_val;
    int8_t per_sub_band_tx_trace_loss[10];
    int8_t per_sub_band_rx_trace_loss[18];
    uint8_t tx_rf_margin;
    /* low/medium/high Tx power in dBm for other role */
    int8_t low_power_val_2nd;
    int8_t med_power_val_2nd;
    int8_t high_power_val_2nd;

    uint8_t padding[1];
} MacPhyParams_t;

/******************************************************************************
                                    DEFINE 
******************************************************************************/

/**
 * \def BYTE_SWAP_LONG
 * \brief Macro which swaps Long's bytes. Used for Endian handling
 */
#define BYTE_SWAP_LONG(x)           ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) | \
                                     (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))
#define TRANSPORT_THREAD_PRIORITY (7)
/******************************************************************************
                                    PROTOTYPE
******************************************************************************/

#endif /* INIT_H_ */
