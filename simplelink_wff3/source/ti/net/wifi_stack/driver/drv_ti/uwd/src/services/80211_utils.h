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
/** \file 80211_utils.h
 *  \brief 802.11 utils services
 *
 */
 
#include "public_types.h"


/* ----------------------------------------------------------------------------
 channel_to_freq
      This function translates channel number to frequency

 Parameters:    aChannel - channel to be translated
 Return code:   frequency on success (valid channel number), -1 else
---------------------------------------------------------------------------- */
int32_t channel_to_freq(uint32_t aChannel);

/* ----------------------------------------------------------------------------
 freq_to_chan
      This function translates frequency to channel number, as a by product
      it also returns the band type

 Parameters:    aFreq - frequency to be translated
                apChan - pointer to translated channel
                apBand - pointer to frequency band (2.4/5)
 Return code:   0 on success (legal frequency), -1 else
---------------------------------------------------------------------------- */
int32_t freq_to_chan(int32_t aFreq, Channel_e *apChan, uint8_t/*RadioBand_e*/ *apBand);

/* ----------------------------------------------------------------------------
 is_bg_channel
      This function finds the band a channel belongs to.

 Parameters:    aChan - channel number to check
 Return code:   1 - BG band, 0 - A band, -1 - invalid channel number
---------------------------------------------------------------------------- */
int32_t is_bg_channel(int32_t aChan);

/* Functions */

