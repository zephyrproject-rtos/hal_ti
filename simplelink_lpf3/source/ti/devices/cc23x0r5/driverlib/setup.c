/******************************************************************************
 *  Filename:       setup.c
 *
 *  Description:    Setup file for CC23x0R5 devices.
 *
 *  Copyright (c) 2022-2023 Texas Instruments Incorporated
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
#include "../inc/hw_types.h"
#include "../inc/hw_ckmd.h"
#include "../inc/hw_fcfg.h"
#include "setup.h"

void SetupTrimDevice(void)
{
    uint8_t trimState;

    // Read out the layout revision number
    if (fcfg->appTrims.revision >= 4)
    {
        // Hard coded address for fcfg->appTrimsExt.cc23x0r5.ateFtRev.trimState
        // to be independent of fcfg layout revision
        trimState = HWREGB(0x4E00032F);
    }
    else
    {
        // Hard coded address for fcfg->appTrimsExt.cc23x0r5.ateFtRev.trimState
        // to be independent of fcfg layout revision
        trimState = HWREGB(0x4E0003AF);
    }

    if (trimState > 0xFC)
    {
        // Override HFXT trims on state D and earlier devices. Without this
        // override, HFXT startup will alternate between 20us and 1.5ms.
        HWREG(CKMD_BASE + CKMD_O_HFXTINIT) = (0x23 << CKMD_HFXTINIT_Q1CAP_S) | (0x23 << CKMD_HFXTINIT_Q2CAP_S) |
                                             (0x8 << CKMD_HFXTINIT_IREF_S) | (0x12 << CKMD_HFXTINIT_AMPTHR_S) |
                                             (0x7F << CKMD_HFXTINIT_IDAC_S);

        HWREG(CKMD_BASE + CKMD_O_HFXTTARG) = (0x23 << CKMD_HFXTTARG_Q1CAP_S) | (0x23 << CKMD_HFXTTARG_Q2CAP_S) |
                                             (0x3 << CKMD_HFXTTARG_IREF_S) | (0x12 << CKMD_HFXTTARG_AMPTHR_S) |
                                             (0x7F << CKMD_HFXTTARG_IDAC_S) | (0x1 << CKMD_HFXTTARG_AMPHYST_S);
    }
}
