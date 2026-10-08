/******************************************************************************
 *  Filename:       i2c.c
 *
 *  Description:    Driver for I2C.
 *
 *  Copyright (c) 2023-2024 Texas Instruments Incorporated
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
extern void I2CControllerInit(uint32_t base, uint32_t config, uint32_t mode)
{
    uint32_t functionalClockDivider;
    uint32_t tprVal;
    uint32_t gfctlVal;

    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));
    ASSERT(mode <= I2C_MODE_FAST_PLUS);
    ASSERT(config == (config & (I2C_CONTROLLER_CONFIG_CLOCK_STRETCHING_DETECTION |
                                I2C_CONTROLLER_CONFIG_MULTI_CONTROLLER_MODE | I2C_CONTROLLER_CONFIG_LOOPBACK)));

    // Set the desired SCL speed.
    // From documentation:
    // SCL_PERIOD = (1 + TPR ) x (SCL_LP + SCL_HP ) x INT_CLK_PRD,
    // SCL_LP=6
    // SCL_HP=4
    // Solve for TPR, and write in terms of frequencies instead of periods:
    // SCL_PERIOD = (1 + TPR ) x (6 + 4) x INT_CLK_PRD
    // (SCL_PERIOD/INT_CLK_PRD)/10 = 1 + TPR
    // TPR = ((INT_CLK_FREQ/SCL_FREQ)/10) - 1

    // The suggested functional clock rates are:
    // TODO: Verify that below table is correct (TIDRIVERS-5910)
    // Standard Mode: 4MHz
    // Fast Mode: 20MHz
    // Fast Mode Plus: 40MHz
    // If the table is ever changed, the minimum and maximum glitch pulse widths
    // documented in the header file, needs to be changed as well.
    switch (mode)
    {
        case I2C_MODE_STANDARD:
            functionalClockDivider = I2C_FCLKDIV_FCLKDIV_BY_20; // Set functional clock to 4MHz
            tprVal                 = 0x03;                      // ((4MHz/0.1MHz)/10) - 1 = 3
            gfctlVal               = I2C_GFCTL_GFSEL_DIS;       // TODO: TIDRIVERS-5910
            break;
        case I2C_MODE_FAST:
            functionalClockDivider = I2C_FCLKDIV_FCLKDIV_BY_4; // Set functional clock to 20MHz
            tprVal                 = 0x04;                     // ((20MHz/0.4MHz)/10) - 1 = 4
            gfctlVal               = I2C_GFCTL_GFSEL_DIS;      // TODO: TIDRIVERS-5910
            break;
        case I2C_MODE_FAST_PLUS:
            functionalClockDivider = I2C_FCLKDIV_FCLKDIV_BY_2; // Set functional clock to 40MHz
            tprVal                 = 0x03;                     // ((40MHz/1MHz)/10) - 1 = 3
            gfctlVal               = I2C_GFCTL_GFSEL_DIS;      // TODO: TIDRIVERS-5910
            break;
    }

    // Write the config to the MCR register. This will disable the controller,
    // but it will be (re)enabled at the end of the function.
    HWREG(base + I2C_O_CCR) = config;

    // Set configuration registers before enabling the I2C controller.
    HWREG(base + I2C_O_FCLKDIV) = functionalClockDivider;
    HWREG(base + I2C_O_CTPR)    = tprVal;
    HWREG(base + I2C_O_GFCTL)   = gfctlVal;

    // Enable I2C Controller
    I2CControllerEnable(base);
}

//*****************************************************************************
//
// Gets the error status of the I2C Controller module
//
//*****************************************************************************
uint32_t I2CControllerGetError(uint32_t base)
{
    uint32_t err;

    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Get the raw error state.
    err = HWREG(base + I2C_O_CSR);

    // Check for errors.
    // The ERR bit covers DATACK and ADRACK errors
    if (err & (I2C_CSR_ERR_M | I2C_CSR_ARBLST_M))
    {
        return (err & (I2C_CSR_ARBLST_M | I2C_CSR_DATACK_M | I2C_CSR_ADRACK_M));
    }
    else
    {
        return (I2C_CONTROLLER_ERR_NONE);
    }
}
