/******************************************************************************
 *  Filename:       evtsvt.c
 *
 *  Description:    Driver for the EVTSVT module.
 *
 *  Copyright (c) 2025 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1) Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2) Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *  3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#include "evtsvt.h"
#include "debug.h"

//*****************************************************************************
//
// Configure DMA channel for the given event publisher
//
//*****************************************************************************
void EVTSVTConfigureDma(uint32_t channel, uint32_t id)
{
    ASSERT((channel >= EVTSVT_DMA_CH_MIN_VAL) && (channel <= EVTSVT_DMA_CH_MAX_VAL));

    if (channel <= EVTSVT_DMA_CH5)
    {
        // Channel 0-5 accept IPIDs, minimum is 0.
        ASSERT(id <= EVTSVT_IPID_MAX_VAL);

        // Write register
        HWREG(EVTSVT_BASE + channel) = id;
    }
    else
    {
        // Channel 6-7 accept PUBIDs, minimum is 0.
        ASSERT(id <= EVTSVT_PUBID_MAX_VAL);

        // Write register. This also clears the EDGDETDIS bit, which means edge
        // detect is enabled.
        HWREG(EVTSVT_BASE + channel) = id;
    }
}

//*****************************************************************************
//
// Configure event publisher to be input to subscriber
//
//*****************************************************************************
void EVTSVTConfigureEvent(uint32_t subscriber, uint32_t pubId)
{
    ASSERT((subscriber >= EVTSVT_SUB_MIN_VAL) && (subscriber <= EVTSVT_SUB_MAX_VAL));
    ASSERT(pubId <= EVTSVT_PUBID_MAX_VAL);

    HWREG(EVTSVT_BASE + subscriber) = pubId;
}
