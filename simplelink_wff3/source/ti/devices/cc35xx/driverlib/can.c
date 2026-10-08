/******************************************************************************
 *  Filename:       can.c
 *
 *  Description:    Driver for CAN peripheral.
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

#include "can.h"

//*****************************************************************************
//
// Sets the CAN Subsystem end of interrupt register.
//
//*****************************************************************************
void CANSSSetEndOfInt(uint32_t eoi)
{
    HWREG(DCAN_BASE + DCAN_O_SSEOI) = eoi;
}

//*****************************************************************************
//
// Clears the specified CAN line interrupt(s).
//
//*****************************************************************************
void CANClearInt(uint8_t lineNum, uint32_t flags)
{
    uint32_t offset = (lineNum == CAN_INT_LINE0) ? DCAN_O_ICLR0 : DCAN_O_ICLR1;

    HWREG(DCAN_BASE + offset) = flags;
}

//*****************************************************************************
//
// Sets the CAN Subsystem clock stop control feature flag(s).
//
//*****************************************************************************
void CANSSSetClkStopCtrl(uint32_t flags)
{
    HWREG(DCAN_BASE + DCAN_O_CLKCTL) |= flags;
}

//*****************************************************************************
//
// Clears the CAN Subsystem clock stop control feature flag(s).
//
//*****************************************************************************
void CANSSClearClkStopCtrl(uint32_t flags)
{
    HWREG(DCAN_BASE + DCAN_O_CLKCTL) &= (uint32_t)~flags;
}