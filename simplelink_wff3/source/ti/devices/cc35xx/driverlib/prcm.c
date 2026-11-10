/******************************************************************************
 *  Filename:       prcm.c
 *
 *  Description:    Driver for the PRCM module
 *
 *  Copyright (c) 2026 Texas Instruments Incorporated
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

#include "prcm.h"

#define PRCM_LFXT_ITRIM 4 //!< IBIASITRIM value for LFXT

#define PRCM_LFXT_RTRIM 7 //!< IBIASITRIM value for LFXT

#define PRCM_AON_LFXTSPARE_SLICEREN 0x10 //!< mask for enabling slicer

#define PRCM_AON_LFXTSPARE_OSCEN 0x1 //!< mask for enabling LFXT oscillator

//*****************************************************************************
//
// Enable LFXT oscillator core and set trim values
//
//*****************************************************************************
void PRCMEnableLFXT(void)
{
    HWREG(PRCM_AON_BASE + PRCM_AON_O_LFXTCTL) |= PRCM_AON_LFXTCTL_OSCEN;
    HWREG(PRCM_AON_BASE + PRCM_AON_O_LFXTCTL) |= PRCM_AON_LFXTCTL_IBIASEN;
    HWREG(PRCM_AON_BASE + PRCM_AON_O_LFXTCTL) |= PRCM_AON_LFXTCTL_CPHPMODEN;
    HWREG(PRCM_AON_BASE + PRCM_AON_O_LFXTSPARE) |= PRCM_AON_LFXTSPARE_SLICEREN | PRCM_AON_LFXTSPARE_OSCEN;
}

//*****************************************************************************
//
// Turn off LFOSC
//
//*****************************************************************************
void PRCMDisableLFOSC(void)
{
    HWREG(PRCM_AON_BASE + PRCM_AON_O_LFOSC) |= PRCM_AON_LFOSC_OVOSCSTOPEN;
}

//*****************************************************************************
//
// Set LFXT GOOD bit
//
//*****************************************************************************
void PRCMSetLFXTGood(void)
{
    HWREG(PRCM_AON_BASE + PRCM_AON_O_SCLKCTL) |= PRCM_AON_SCLKCTL_GOOD;
}

//*****************************************************************************
//
// Set LFXT Trim values
//
//*****************************************************************************
void PRCMSetLFXTTrims(void)
{
    /* Since this function only should run once at startup, we can assume these
     * fields are set to their reset value 0h. Therefore we don't have to
     * consider if the register contains pre-existing non-zero values
     */
    HWREG(PRCM_AON_BASE + PRCM_AON_O_LFXTCTL) |= PRCM_LFXT_ITRIM << PRCM_AON_LFXTCTL_IBIASITRIM_S;
    HWREG(PRCM_AON_BASE + PRCM_AON_O_LFXTCTL) |= PRCM_LFXT_RTRIM << PRCM_AON_LFXTCTL_IBIASRTRIM_S;
}

//*****************************************************************************
//
// Return status of LFXT detection
//
//*****************************************************************************
bool PRCMLFXTStatusGood(void)
{
    return (HWREG(PRCM_AON_BASE + PRCM_AON_O_SCLKCTL) & PRCM_AON_SCLKCTL_DETGOOD_M) == PRCM_AON_SCLKCTL_DETGOOD;
}

//*****************************************************************************
//
// Configure muxes to select LFXT as LFCLK source
//
//*****************************************************************************
void PRCMSelectLFXT(void)
{
    HWREG(PRCM_AON_BASE + PRCM_AON_O_SCLKCTL) |= PRCM_AON_SCLKCTL_LFOSCSEL;
}
