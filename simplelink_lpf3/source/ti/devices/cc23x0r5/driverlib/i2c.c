/******************************************************************************
 *  Filename:       i2c.c
 *
 *  Description:    Driver for I2C.
 *
 *  Copyright (c) 2022 Texas Instruments Incorporated
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

#include "i2c.h"

//*****************************************************************************
//
// Initializes the I2C Controller module
//
//*****************************************************************************
void I2CControllerInitExpClk(uint32_t base, bool fast)
{
    uint32_t sclFreq;
    uint32_t tpr;

    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Must enable the device before doing anything else.
    I2CControllerEnable(base);

    // Get the desired SCL speed.
    if (fast == true)
    {
        sclFreq = 400000;
    }
    else
    {
        sclFreq = 100000;
    }

    // Compute the clock divider that achieves the fastest speed less than or
    // equal to the desired speed. The numerator is biased to favor a larger
    // clock divider so that the resulting clock is always less than or equal
    // to the desired clock, never greater.
    tpr                      = ((I2C_CLK_FREQ + (2 * 10 * sclFreq) - 1) / (2 * 10 * sclFreq)) - 1;
    HWREG(base + I2C_O_CTPR) = tpr;
}

//*****************************************************************************
//
// Gets the error status of the I2C Controller module
//
//*****************************************************************************
uint32_t I2CControllerError(uint32_t base)
{
    uint32_t err;

    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Get the raw error state.
    err = HWREG(base + I2C_O_CSTA);

    // If the I2C controller is busy, then all the other status bits are invalid,
    // and there is no error to report.
    if (err & I2C_CSTA_BUSY_M)
    {
        return (I2C_CONTROLLER_ERR_NONE);
    }

    // Check for errors.
    if (err & (I2C_CSTA_ERR_M | I2C_CSTA_ARBLST_M))
    {
        return (err & (I2C_CSTA_ARBLST_M | I2C_CSTA_DATACKN_M | I2C_CSTA_ADRACKN_M));
    }
    else
    {
        return (I2C_CONTROLLER_ERR_NONE);
    }
}
