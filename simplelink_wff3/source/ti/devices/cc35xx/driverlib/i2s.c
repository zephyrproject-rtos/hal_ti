/******************************************************************************
 *  Filename:       i2s.c
 *
 *  Description:    Driver for I2S.
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

#include "i2s.h"

//*****************************************************************************
//
// Get the current value of a sample stamp counter
//
//*****************************************************************************
uint32_t I2SGetSampleStamp(uint32_t base, uint32_t channel)
{
    uint32_t frameClkCnt;
    uint32_t sysClkCnt;
    uint32_t periodSysClkCnt;
    uint32_t sampleStamp;

    // Get the number of Frame clock counts since last stamp.
    frameClkCnt = HWREG(I2S_BASE + I2S_O_STMPWCPT0);

    // Get the number of system clock ticks since last frame clock edge.
    sysClkCnt = HWREG(I2S_BASE + I2S_O_STMPXCPT0);

    // Get the number system clock ticks in the last frame clock period.
    periodSysClkCnt = HWREG(I2S_BASE + I2S_O_STMPXPER);

    // Calculate the sample stamp.
    sampleStamp = (sysClkCnt << 16) / periodSysClkCnt;
    sampleStamp = (sampleStamp > I2S_STMP_SATURATION) ? I2S_STMP_SATURATION : sampleStamp;
    sampleStamp |= (frameClkCnt << 16);

    return sampleStamp;
}
