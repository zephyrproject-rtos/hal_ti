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
/** \file 80211_utils.c
 *  \brief 802.11 utils services
 *
 *  \see 80211_services.h
 */


/***************************************************************************/
/*                                                                         */
/*      MODULE: 80211_utils.c                                              */
/*    PURPOSE:  802.11 MLME Parser                                        */
/*                                                                         */
/***************************************************************************/

#include "802_11defs.h"
#include "gtrace.h"

/* Constants */

/* Enumerations */

/* Typedefs */

/* Structures */

/* External data definitions */


/* External functions definitions */

/* Local function prototypes */


/**
 * \fn     channel_to_freq
 * \brief  convert 802.11 channel to frequency
 *
 * convert 802.11 channel to frequency
 *
 * \param  channel - 802.11 channel
 * \param  freq - pointer to output frequency
 * \return 0 - if success, -1 if failed
 * \sa
 */
int32_t channel_to_freq(uint32_t aChannel)
{
    if ((0 < aChannel) && (aChannel < 14))
    {
        return (aChannel*5 + BASE_FREQ_2_4);
    }

    if (14 == aChannel)
    {
        return 2484;
    }

    if ((aChannel >= 36) && (aChannel <= 165))
    {
        return (aChannel*5 + BASE_FREQ_5_0);
    }

    GTRACE(GRP_GENERAL_ERROR, "ERROR: invalid channel %d", aChannel);
    return -1;
}

// ----------------------------------------------------------------------------
int32_t freq_to_chan(int32_t aFreq, Channel_e *apChan, uint8_t/*RadioBand_e*/ *apBand)
{

    int32_t rc = 0;

    if (aFreq >= 2400 && aFreq < 2500)
    {
        if (apChan)
        {
            *apChan = (aFreq - BASE_FREQ_2_4) / 5;
        }
        if (apBand)
        {
            *apBand = (uint8_t)RADIO_BAND_2_4GHZ;
        }
    }
    else if (aFreq >= 4900 && aFreq < 6000)
    {
        if (apChan)
        {
            *apChan = (aFreq - BASE_FREQ_5_0) / 5;
        }
        if (apBand)
        {
            *apBand = (uint8_t)RADIO_BAND_5GHZ;
        }
    }
    else
    {
        rc = -1;
        GTRACE(GRP_GENERAL_ERROR, "ERROR: invalid freq %d",aFreq);
    }

    return rc;
}

// ----------------------------------------------------------------------------
int32_t is_bg_channel(int32_t aChan)
{

    if (aChan >= 1 && aChan <= 14)
        return 1;
    else if (aChan >= 36 && aChan <= 165)
        return 0;

    GTRACE(GRP_GENERAL_ERROR, "HOSTAPTIW %s:invalid chan %d",__func__, aChan);
    return -1;
}

// ----------------------------------------------------------------------------

/* Functions */


